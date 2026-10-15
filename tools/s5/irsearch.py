"""Search instruction orders of one basic block of LLVM IR for the original's schedule.

usage: irsearch.py LL FUNC ADDR [--map NAME=ADDR ...] [--block LABEL] [--iters N] [--seed S] [--work DIR]
                   [--start ORDER.ll] [--fix-mem]

LL is clang's -S -emit-llvm output for a scratch file (the optimizer has already run), made with the unit flags
including -g and with -Xclang -emit-llvm-uselists: both the debug intrinsics and the use-list order change codegen
in some functions (3b4e98: 6 instructions off from source, 8 from IR without -g, 7 without the use-lists), so check
that the first score equals what sbs.py gives for the source. The function's numbered values
are renamed (%12 -> %v12, so any order stays valid IR) and the chosen block (default: the one with the most
instructions) is reordered at random, one instruction or one operand tree at a time, keeping SSA order and the
relative order of loads, stores and calls with side effects. Each order is compiled with the optimizer disabled
(-Xclang -disable-llvm-optzns, about 80 ms), and kept when its distance to the original (abstract instruction
diffs, then word diffs) does not grow. The best order goes to DIR/best.ll (default: next to LL); a match stops the
search (exit 0) and writes DIR/match.ll.

The point is to learn which IR order the original's schedule comes from, then write the source that gives it.
"""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
import os, sys, json, re, subprocess, difflib, argparse, random, csv, math, atexit, shutil
ROOT = os.path.dirname(M)
sys.path.insert(0, os.path.join(M, "tools"))
sys.path.insert(0, os.path.join(ROOT, ".tools", "python"))
sys.path.append(os.path.join(M, "tools", "gen"))
import capstone  # noqa
import check_obj, check  # noqa
import mm_tally  # noqa

LABEL = re.compile(r"^; <label>:(\d+):")
NAMED = re.compile(r"^([-\w.$]+):")
DEF = re.compile(r"^\s+(%[-\w.$]+) = ")
VAL = re.compile(r"%[-\w.$]+")


def rename(lines):
    """%N -> %vN in a function body; '; <label>:N:' -> 'vN:'."""
    out = []
    for l in lines:
        m = LABEL.match(l)
        if m:
            out.append("v%s:%s" % (m.group(1), l[m.end():]))
            continue
        out.append(re.sub(r"%(\d+)\b", r"%v\1", l))
    return out


def name_args(define):
    """Give unnamed parameters of a 'define' line the names %v0, %v1, ...; returns (line, count)."""
    p0 = define.index("(", define.index("@"))
    depth, k = 0, p0
    for k in range(p0, len(define)):
        c = define[k]
        depth += c in "(<{[" and 1 or 0
        depth -= c in ")>}]" and 1 or 0
        if depth == 0:
            break
    params, cur, depth = [], "", 0
    for c in define[p0 + 1: k]:
        if c == "," and depth == 0:
            params.append(cur); cur = ""
            continue
        depth += c in "(<{[" and 1 or 0
        depth -= c in ")>}]" and 1 or 0
        cur += c
    if cur.strip():
        params.append(cur)
    named, unnamed = [], 0
    for p in params:
        if re.search(r"%[-\w.$]+\s*$", p) or p.strip() == "...":
            named.append(p)
        else:
            named.append(p.rstrip() + " %%v%d" % unnamed)
            unnamed += 1
    return define[:p0 + 1] + ",".join(named) + define[k:], unnamed


def join_multiline(body):
    """One entry per instruction: a switch or indirectbr spans lines up to its closing ']'."""
    out, k = [], 0
    while k < len(body):
        l = body[k]
        if l.rstrip().endswith("[") and re.search(r"\b(switch|indirectbr)\b", l):
            parts = [l]
            k += 1
            while k < len(body) and body[k].strip() != "]":
                parts.append(body[k])
                k += 1
            if k < len(body):
                parts.append(body[k])
            out.append("\n".join(parts))
        else:
            out.append(l)
        k += 1
    return out


def split_blocks(body):
    """body: lines between 'define ... {' and '}'. Returns [(label_line or None, [instr lines])]."""
    body = join_multiline(body)
    blocks, cur, lab = [], [], None
    for l in body:
        if not l.strip():
            continue
        if NAMED.match(l):
            if cur or lab is not None:
                blocks.append((lab, cur))
            lab, cur = l, []
        else:
            cur.append(l)
    blocks.append((lab, cur))
    return blocks


def is_mem(l):
    s = l.strip()
    if " load " in s or s.startswith("store ") or " = load " in s:
        return True
    if " call " in s or s.startswith("call ") or s.startswith("tail call "):
        return not re.search(r"@llvm\.(aarch64\.neon|fma|fabs|sqrt|copysign|minnum|maxnum|dbg)", s)
    return False


def is_load(l):
    return " = load " in l


class Block:
    def __init__(self, instrs, loads_free=False):
        self.instrs = instrs
        n = len(instrs)
        self.defs = {}
        for i, l in enumerate(instrs):
            m = DEF.match(l)
            if m:
                self.defs[m.group(1)] = i
        self.fixed_head = sum(1 for l in instrs if " = phi " in l)
        self.deps = [set() for _ in range(n)]
        for i, l in enumerate(instrs):
            m = DEF.match(l)
            rhs = l[m.end():] if m else l
            for v in VAL.findall(rhs):
                j = self.defs.get(v)
                if j is not None and j != i:
                    self.deps[i].add(j)
        mem = [i for i, l in enumerate(instrs) if is_mem(l)]
        if not loads_free:
            for a, b in zip(mem, mem[1:]):
                self.deps[b].add(a)
        else:  # loads move among themselves; stores and calls stay ordered with everything that touches memory
            last_barrier, since = None, []
            for i in mem:
                if is_load(instrs[i]):
                    if last_barrier is not None:
                        self.deps[i].add(last_barrier)
                    since.append(i)
                else:
                    for j in since:
                        self.deps[i].add(j)
                    if last_barrier is not None:
                        self.deps[i].add(last_barrier)
                    last_barrier, since = i, []
        self.users = [set() for _ in range(n)]
        self.real_users = [set() for _ in range(n)]  # without the debug intrinsics that describe the value
        for i, d in enumerate(self.deps):
            for j in d:
                self.users[j].add(i)
                if "@llvm.dbg." not in instrs[i]:
                    self.real_users[j].add(i)
        self.term = n - 1

    def valid(self, order):
        pos = {x: k for k, x in enumerate(order)}
        return all(pos[j] < pos[i] for i in range(len(order)) for j in self.deps[i])

    def tree(self, i):
        """i and the operands that have no other user (recursively): one expression's instructions."""
        t, todo = {i}, [i]
        while todo:
            for d in self.deps[todo.pop()]:
                if d not in t and d >= self.fixed_head and len(self.real_users[d]) == 1 and not is_mem(self.instrs[d]):
                    t.add(d)
                    todo.append(d)
        return t


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("ll"); ap.add_argument("func"); ap.add_argument("addr")
    ap.add_argument("--map", action="append", default=[])
    ap.add_argument("--block"); ap.add_argument("--iters", type=int, default=3000)
    ap.add_argument("--seed", type=int, default=1); ap.add_argument("--work")
    ap.add_argument("--start", help="an order to start from (a previous best.ll)")
    ap.add_argument("--minimize", help="an order (a best.ll) to move back toward LL's order while its abstract "
                                       "distance does not grow; writes DIR/min.ll and prints what stays moved")
    ap.add_argument("--strict", action="store_true", help="--minimize: the exact distance may not grow either")
    ap.add_argument("--groups", action="store_true",
                    help="move whole statements only (an instruction with several users or none, with the operands "
                         "only it uses), and swap the two halves of a statement with two calls: orders a source "
                         "file can give")
    ap.add_argument("--gmin", help="--groups: an order (gbest.ll) to move back toward LL's order statement by "
                                   "statement while neither distance grows; writes DIR/gmin.ll")
    ap.add_argument("--loads-free", action="store_true",
                    help="let loads move among themselves (only stores and calls stay ordered): source orders of "
                         "independent reads, such as the definitions of locals read from memory")
    ap.add_argument("--temp", type=float, default=1.0, help="--groups: annealing start temperature (one abstract "
                                                             "diff = 1, one word diff = 0.01)")
    ap.add_argument("--restart", type=int, default=400, help="--groups: iterations without a new best before going "
                                                              "back to the best order")
    a = ap.parse_args()
    addr = int(a.addr, 16) & 0xffffffff
    work = a.work or os.path.dirname(os.path.abspath(a.ll))
    os.makedirs(work, exist_ok=True)
    rnd = random.Random(a.seed)
    man = json.load(open(os.path.join(M, "data", "units.json"), encoding="utf-8-sig"))
    flags = [f for f in man["flags"] if not f.startswith(("-std=", "-stdlib", "-fno-exceptions", "-fstandalone", "-g"))]
    cc = os.path.join(ROOT, man["compiler"])
    mapping = dict(check.collect_externals(man))
    for x in a.map:
        n, v = x.split("=")
        mapping[n] = check.address(v)
    mapping.setdefault(".rodata.cst4", 0x73b000)
    mapping.setdefault(".rodata.cst16", 0x73dff0)
    mapping[a.func] = addr
    sizes = {check.address(r["Address"]): int(r["Size"]) for r in csv.DictReader(open(os.path.join(M, "data", "functions.csv"), newline=""))}
    image = check_obj.IMAGE.read_bytes()
    orig = image[addr: addr + sizes[addr]]
    md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
    oi = [f"{i.mnemonic} {i.op_str}" for i in md.disasm(orig, 0x7100000000 + addr)]
    _ab = lambda s: re.sub(r"#0x7100[0-9a-f]+|#0x[0-9a-f]{5,}", "#ADDR", re.sub(r"\b([xwqsdvbh])(\d+|zr)\b", r"\1", s))
    oa = [_ab(x) for x in oi]

    def compiles(ll):
        r = subprocess.run([cc, *flags, "-Xclang", "-disable-llvm-optzns", "-c", ll, "-o",
                            os.path.join(work, "irs_base.o")], capture_output=True, text=True)
        return r.returncode == 0, r.stderr

    if a.ll.endswith(".cpp"):  # emit the IR as the unit compile sees it: -g, use-list order kept
        ll = os.path.join(work, os.path.splitext(os.path.basename(a.ll))[0] + ".ll")
        for variant in ("-g", "no -g"):
            uflags = man["flags"] if variant == "-g" else [f for f in man["flags"] if not f.startswith(("-g", "-fstandalone"))]
            r = subprocess.run([cc, *uflags, "-I", os.path.join(M, "include"), "-S", "-emit-llvm", "-Xclang",
                                "-emit-llvm-uselists", a.ll, "-o", ll], capture_output=True, text=True)
            if r.returncode:
                sys.exit(r.stderr[-2000:])
            ok, err = compiles(ll)
            if ok:
                break
            # clang 3.9.1 crashes on some -g IR read back (761d8); the IR without debug info still compiles
            print(f"the IR emitted with {variant} does not compile back: {err.strip().splitlines()[-1] if err.strip() else ''}",
                  flush=True)
        else:
            sys.exit("irsearch: the IR of this function does not compile back, with or without -g")
        if variant != "-g":
            print("notice: searching the IR without -g; its first score may differ from sbs.py's", flush=True)
        a.ll = ll
    elif not a.start:
        ok, err = compiles(a.ll)
        if not ok:
            sys.exit("irsearch: %s does not compile back:\n%s" % (a.ll, err[-2000:]))
    text = open(a.start or a.ll, encoding="utf-8").read().split("\n")
    d0 = next(k for k, l in enumerate(text) if l.startswith("define ") and ("@" + a.func + "(") in l)
    d1 = next(k for k in range(d0, len(text)) if text[k] == "}")
    head = text[:d0]
    define, nargs = name_args(text[d0])
    define = re.sub(r"%(\d+)\b", r"%v\1", define)
    body = rename(text[d0 + 1: d1])
    if body and not NAMED.match(body[0]):
        body.insert(0, "v%d:" % nargs)  # the entry block's implicit number
    # use-list orders (-Xclang -emit-llvm-uselists) close the body; they stay there, whatever the order
    uselists = [l for l in body if l.strip().startswith("uselistorder")]
    body = [l for l in body if not l.strip().startswith("uselistorder")]
    tail = text[d1:]
    blocks = split_blocks(body)
    if a.block:
        bi = next(k for k, (lab, _) in enumerate(blocks) if lab and lab.startswith(a.block + ":"))
    else:
        bi = max(range(len(blocks)), key=lambda k: len(blocks[k][1]))
    blk = Block(blocks[bi][1], a.loads_free)
    a.block_label = blocks[bi][0]
    n = len(blk.instrs)
    print(f"block {blocks[bi][0] or '(entry)'}: {n} instructions")

    def emit(order):
        out = list(head) + [define]
        for k, (lab, ins) in enumerate(blocks):
            if lab is not None:
                out.append(lab)
            out.extend([blk.instrs[x] for x in order] if k == bi else ins)
        out.extend(uselists)
        out.extend(tail)
        return "\n".join(out)

    tmp_ll, tmp_o = os.path.join(work, "irs_tmp.ll"), os.path.join(work, "irs_tmp.o")
    failed = {"n": 0}

    def report_failures():
        if failed["n"]:
            print(f"{failed['n']} orders failed to compile (skipped); the first is kept as {tmp_ll}.fail", flush=True)
    atexit.register(report_failures)

    def score(order):
        open(tmp_ll, "w", encoding="utf-8").write(emit(order))
        r = subprocess.run([cc, *flags, "-Xclang", "-disable-llvm-optzns", "-c", tmp_ll, "-o", tmp_o], capture_output=True, text=True)
        if r.returncode:
            failed["n"] += 1
            if failed["n"] <= 3:
                print("compile failed:", r.stderr.strip()[-1500:], flush=True)
            if failed["n"] == 1:
                shutil.copyfile(tmp_ll, tmp_ll + ".fail")
            return None
        mine = mm_tally.mine_bytes(tmp_o, a.func, addr, mapping, image)
        mi = [f"{i.mnemonic} {i.op_str}" for i in md.disasm(mine, 0x7100000000 + addr)]
        ma = [_ab(x) for x in mi]
        sm = difflib.SequenceMatcher(None, ma, oa, autojunk=False)
        nab = max(len(ma), len(oa)) - sum(b.size for b in sm.get_matching_blocks())
        sm = difflib.SequenceMatcher(None, mi, oi, autojunk=False)
        nd = max(len(mi), len(oi)) - sum(b.size for b in sm.get_matching_blocks())
        return (nab, nd, 0 if mine == orig else 1)

    order = list(range(n))
    if a.minimize:
        return minimize(a, blk, blocks, bi, score, emit, work)
    if a.groups:
        return group_search(a, blk, score, emit, work, rnd)
    best = score(order)
    if best is None:
        sys.exit("irsearch: the starting order does not compile")
    print("start", best)
    cur = best
    best_order = list(order)
    for it in range(a.iters):
        if best[2] == 0:
            break
        new = list(order)
        i = rnd.randrange(blk.fixed_head, blk.term)
        grp = sorted(blk.tree(i)) if rnd.random() < 0.5 else [i]
        pos = {x: k for k, x in enumerate(new)}
        gset = set(grp)
        rest = [x for x in new if x not in gset]
        # valid insertion window for the group in `rest`
        lo = max([rest.index(d) + 1 for g in grp for d in blk.deps[g] if d not in gset] + [blk.fixed_head])
        hi = min([rest.index(u) for g in grp for u in blk.users[g] if u not in gset] + [len(rest) - 1])
        if hi < lo:
            continue
        p = rnd.randint(lo, hi)
        new = rest[:p] + [x for x in new if x in gset] + rest[p:]
        if new == order:
            continue
        s = score(new)
        if s is None:
            continue
        if s[:2] <= cur[:2]:
            order, cur = new, s
            if s < best:
                best, best_order = s, list(new)
                open(os.path.join(work, "best.ll"), "w", encoding="utf-8").write(emit(best_order))
                print(it, "best", best, flush=True)
    if best[2] == 0:
        open(os.path.join(work, "match.ll"), "w", encoding="utf-8").write(emit(best_order))
        print("MATCH")
        return 0
    print("best", best)
    return 1


def group_search(a, blk, score, emit, work, rnd):
    n = len(blk.instrs)
    # statements: runs of the block's order that end in an instruction and hold only operands that it alone uses
    # (so a statement stays one contiguous run, as a source statement's instructions are)
    owner = {}
    groups = []
    is_dbg = lambda x: "@llvm.dbg." in blk.instrs[x]
    i = blk.term - 1
    while i >= blk.fixed_head:
        t = blk.tree(i)
        k = i - 1
        # debug intrinsics between a statement's instructions belong to it (they move with it in the source)
        while k >= blk.fixed_head and (k in t or is_dbg(k)) and not is_mem(blk.instrs[k]):
            k -= 1
        g = list(range(k + 1, i + 1))
        for x in g:
            owner[x] = len(groups)
        groups.append(g)
        i = k
    groups.reverse()
    owner = {x: gi for gi, g in enumerate(groups) for x in g}
    gdeps = [set() for _ in groups]
    for gi, g in enumerate(groups):
        for x in g:
            for d in blk.deps[x]:
                if d in owner and owner[d] != gi:
                    gdeps[gi].add(owner[d])
    gusers = [set() for _ in groups]
    for gi, d in enumerate(gdeps):
        for j in d:
            gusers[j].add(gi)
    def independent_calls(g):
        c = [x for x in g if " call " in blk.instrs[x] and not is_dbg(x)]
        if len(c) != 2:
            return False
        seen, todo = set(), [c[1]]
        while todo:  # c[1]'s operands, transitively
            for d in blk.deps[todo.pop()]:
                if d not in seen:
                    seen.add(d)
                    todo.append(d)
        return c[0] not in seen

    calls = [gi for gi, g in enumerate(groups) if independent_calls(g)]
    print(f"{len(groups)} statements, {len(calls)} with two calls")

    def flat(gorder, flips):
        out = list(range(blk.fixed_head))
        for gi in gorder:
            g = list(groups[gi])
            if gi in flips:
                c = [x for x in g if " call " in blk.instrs[x] and not is_dbg(x)]
                # put the second call (and what only it feeds) first
                g = [c[1]] + [x for x in g if x != c[1]]
            out.extend(g)
        out.append(blk.term)
        return out

    gorder = sorted(range(len(groups)), key=lambda gi: groups[gi][0])
    flips = set()
    if a.gmin:
        return group_minimize(a, blk, groups, owner, gdeps, calls, flat, score, emit, work)
    cur = score(flat(gorder, flips))
    if cur is None:
        sys.exit("irsearch: the starting order does not compile")
    print("start", cur, flush=True)
    best, best_state = cur, (list(gorder), set(flips))
    energy = lambda s: s[0] + s[1] / 100.0
    since = 0
    for it in range(a.iters):
        if best[2] == 0:
            break
        temp = a.temp * (1 - it / max(1, a.iters)) + 0.02
        if since > a.restart:  # no progress for a while: go back to the best order
            (gorder, flips), cur, since = (list(best_state[0]), set(best_state[1])), best, 0
        ng, nf = list(gorder), set(flips)
        if calls and rnd.random() < 0.15:
            nf ^= {rnd.choice(calls)}
        else:
            gi = rnd.randrange(len(groups))
            rest = [x for x in ng if x != gi]
            lo = max([rest.index(d) + 1 for d in gdeps[gi]] + [0])
            hi = min([rest.index(u) for u in gusers[gi]] + [len(rest)])
            if hi < lo:
                continue
            if rnd.random() < 0.5:  # a short move
                p0 = ng.index(gi)
                lo, hi = max(lo, p0 - 3), min(hi, p0 + 3)
            p = rnd.randint(lo, hi)
            ng = rest[:p] + [gi] + rest[p:]
            if ng == gorder:
                continue
        s = score(flat(ng, nf))
        since += 1
        if s is None:
            continue
        de = energy(s) - energy(cur)
        if de <= 0 or rnd.random() < math.exp(-de / temp):
            gorder, flips, cur = ng, nf, s
            if s < best:
                best, best_state, since = s, (list(ng), set(nf)), 0
                open(os.path.join(work, "gbest.ll"), "w", encoding="utf-8").write(emit(flat(ng, nf)))
                print(it, "best", best, flush=True)
    gorder, flips = best_state
    print("best", best)
    for gi in gorder:
        root = max(groups[gi])
        print("  %s%s" % ("(flipped) " if gi in flips else "", blk.instrs[root].strip()[:100]))
    if best[2] == 0:
        open(os.path.join(work, "match.ll"), "w", encoding="utf-8").write(emit(flat(gorder, flips)))
        print("MATCH")
        return 0
    return 1


def read_order(path, blk, lab):
    t = open(path, encoding="utf-8").read().split("\n")
    name = lab.split(":")[0] + ":"
    s = next(k for k, l in enumerate(t) if l.startswith(name))  # the label's comment may differ
    e = s + 1
    while e < len(t) and not NAMED.match(t[e]) and t[e] != "}":
        e += 1
    idx = {l: k for k, l in enumerate(blk.instrs)}
    return [idx[l] for l in t[s + 1: e] if l.strip()]


def inversions(order):
    """Pairs out of their source order: the distance a minimizer must strictly reduce (so it always ends)."""
    return sum(1 for i in range(len(order)) for j in range(i + 1, len(order)) if order[i] > order[j])


def group_minimize(a, blk, groups, owner, gdeps, calls, flat, score, emit, work):
    lab = a.block_label
    order = read_order(a.gmin, blk, lab)
    gorder, flips, seen = [], set(), set()
    for x in order:
        gi = owner.get(x)
        if gi is None or gi in seen:
            continue
        seen.add(gi)
        gorder.append(gi)
        c = [y for y in groups[gi] if " call " in blk.instrs[y] and "@llvm.dbg." not in blk.instrs[y]]
        if gi in calls and order.index(c[1]) < order.index(c[0]):
            flips.add(gi)
    cur = score(flat(gorder, flips))
    if cur is None:
        sys.exit("irsearch: the order in --gmin does not compile")
    print("start", cur, flush=True)

    def valid(go):
        pos = {g: k for k, g in enumerate(go)}
        return all(pos[d] < pos[g] for g in go for d in gdeps[g])

    changed = True
    while changed:
        changed = False
        for gi in list(flips):  # undo flips first
            nf = flips - {gi}
            s = score(flat(gorder, nf))
            if s is not None and s[:2] <= cur[:2]:
                flips, cur, changed = nf, s, True
                print("unflip", gi, s, flush=True)
        for gi in sorted(range(len(groups))):
            for anchor, after in ((gi - 1, True), (gi + 1, False)):
                if anchor < 0 or anchor >= len(groups):
                    continue
                rest = [g for g in gorder if g != gi]
                q = rest.index(anchor) + (1 if after else 0)
                new = rest[:q] + [gi] + rest[q:]
                if new == gorder or not valid(new) or inversions(new) >= inversions(gorder):
                    continue
                s = score(flat(new, flips))
                if s is not None and s[:2] <= cur[:2]:
                    gorder, cur, changed = new, s, True
                    print("back", gi, s, flush=True)
                    break
    open(os.path.join(work, "gmin.ll"), "w", encoding="utf-8").write(emit(flat(gorder, flips)))
    print("result", cur)
    for k, gi in enumerate(gorder):
        moved = k and gorder[k - 1] != gi - 1
        print("  %s%s%s" % ("* " if moved else "  ", "(flipped) " if gi in flips else "",
                            blk.instrs[max(groups[gi])].strip()[:100]))
    return 0 if cur[2] == 0 else 1


def minimize(a, blk, blocks, bi, score, emit, work):
    """Move instructions of the order in a.minimize back to their places in LL's order (each just after its
    predecessor or just before its successor there) while the abstract distance does not grow."""
    t = open(a.minimize, encoding="utf-8").read().split("\n")
    lab = blocks[bi][0]
    name = lab.split(":")[0] + ":"
    s = next(k for k, l in enumerate(t) if l.startswith(name))  # the label's comment may differ
    e = s + 1
    while e < len(t) and not NAMED.match(t[e]) and t[e] != "}":
        e += 1
    lines = [l for l in t[s + 1: e] if l.strip()]
    idx = {l: k for k, l in enumerate(blk.instrs)}
    order = [idx[l] for l in lines]
    n = len(order)
    cur = score(order)
    if cur is None:
        sys.exit("irsearch: the order in --minimize does not compile")
    print("start", cur)
    target = cur[0]

    def valid(o):
        pos = {x: k for k, x in enumerate(o)}
        return all(pos[j] < pos[i] for i in range(n) for j in blk.deps[i])

    changed = True
    while changed:
        changed = False
        for x in range(blk.fixed_head, n - 1):
            p = order.index(x)
            for anchor, after in ((x - 1, True), (x + 1, False)):
                if anchor < blk.fixed_head or anchor >= n - 1 and not after:
                    continue
                rest = [y for y in order if y != x]
                q = rest.index(anchor) + (1 if after else 0)
                new = rest[:q] + [x] + rest[q:]
                if new == order or not valid(new) or inversions(new) >= inversions(order):
                    continue
                s2 = score(new)
                if s2 is not None and s2[0] <= target and (not a.strict or s2[1] <= cur[1]):
                    order, cur, changed = new, s2, True
                    print("back", x, s2, flush=True)
                    break
    open(os.path.join(work, "min.ll"), "w", encoding="utf-8").write(emit(order))
    print("result", cur)
    # what stays out of LL's order: the instructions whose predecessor in the result is not the one in LL
    for k, x in enumerate(order):
        if k and order[k - 1] != x - 1:
            print("  %4d after %4d: %s" % (x, order[k - 1], blk.instrs[x].strip()[:110]))
    return 0 if cur[2] == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
