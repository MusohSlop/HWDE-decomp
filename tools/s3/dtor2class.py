"""dtor2class.py ADDR OUT.cpp [--name CLASS]: write a destructor as a C++ class from the original's code alone (no
generator), for the destructors made of member destructor calls, layout handles and a base destructor.

The function is emulated from its entry with x0 = this: registers hold this+offset, constants, GOT slot addresses
and the values loaded through them; conditional branches on known values are taken as computed (so loops run
their iterations), on unknown values they fall through (the heap test of a handle release). Recorded events:
the class's own vtable store at +0, a layout handle (a store of the handle vtable, GOT 0x7100c22f00, then a call
through that vtable's +28 with x0 at the same address), a member destructor call `bl F` with x0 = this+offset,
and the final call with x0 = this (the base destructor, usually a tail call).

Members are laid out by offset with byte padding between them. Handles destroyed in one loop become an array of
slots (the slot's size is the loop's stride; a run of handles 0x18 apart inside one iteration is a handle array
in the slot); handles outside loops stay single members. Writes OUT.cpp (exit 0) and prints `name SYMBOL` and
`maps --map ...` for try.py; exits 1 when the code does not fit (an unknown call, an instruction it cannot follow).
"""
import os, re, sys, argparse, csv
M = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))  # the matching/ folder
sys.path.insert(0, os.path.join(M, "tools"))
sys.path.insert(0, os.path.join(os.path.dirname(M), ".tools", "python"))
import capstone, check_obj, check

HANDLE_GOT, HEAP_GOT = 0xc22f00, 0xc21db0
ap = argparse.ArgumentParser()
ap.add_argument("addr"); ap.add_argument("out"); ap.add_argument("--name")
a = ap.parse_args()
addr = int(a.addr, 16) & 0xffffffff
size = next(int(r["Size"]) for r in csv.DictReader(open(os.path.join(M, "data", "functions.csv"), newline=""))
            if check.address(r["Address"]) == addr)
image = check_obj.IMAGE.read_bytes()
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
ins = {i.address & 0xffffffff: i for i in md.disasm(image[addr:addr + size], 0x7100000000 + addr)}
X = lambda r: ("x" + r[1:]) if r[0] in "wx" and r[1:].isdigit() else r


def fail(msg):
    sys.exit("cannot convert: " + msg)


def imm(s):
    return int(s.strip().lstrip("#"), 0)


regs = {"x0": ("this", 0), "sp": ("sp", 0)}
stack = {}       # sp offset -> spilled value
events = []      # (kind, off, extra, loopiter)
vt_own = None
pc, steps = addr, 0
# loop heads (targets of backward branches) and the branches that close them: each pass through a head starts a
# new iteration number, and so does leaving the loop, so one iteration's events share a number of their own
heads, latches, ranges = set(), set(), []
for p_, i_ in ins.items():
    t_ = re.search(r"#0x71([0-9a-f]{8})$", i_.op_str)
    if (i_.mnemonic.startswith("b.") or i_.mnemonic in ("cbz", "cbnz", "b")) and t_ and int(t_.group(1), 16) <= p_:
        heads.add(int(t_.group(1), 16)); latches.add(p_); ranges.append((int(t_.group(1), 16), p_))
it = 0
LI = lambda: it if any(h <= pc <= l for h, l in ranges) else None   # the iteration number inside a loop
while True:
    steps += 1
    if steps > 400000:
        fail("too many steps")
    if pc in heads:
        it += 1
    i = ins.get(pc)
    if i is None:
        fail("pc outside the function %#x" % pc)
    m = i.mnemonic
    ops = [o.strip() for o in re.split(r",(?![^\[]*\])", i.op_str)] if i.op_str else []
    nxt = pc + 4
    spm = re.fullmatch(r"\[sp(?:, #(-?0x[0-9a-f]+|-?\d+))?\]!?", ops[1]) if len(ops) >= 2 and m in ("str", "ldr", "stur", "ldur") else None
    if m in ("stp", "ldp") and ops and "sp" in ops[-1] or (m in ("str", "ldr") and len(ops) == 3 and ops[1] == "[sp]"):
        pass  # frame save/restore (also str/ldr with sp writeback in the prologue/epilogue)
    elif spm and m in ("str", "stur") and not ops[1].endswith("!"):
        stack[int(spm.group(1), 0) if spm.group(1) else 0] = regs.get(X(ops[0]))   # a spill
    elif spm and m in ("ldr", "ldur"):
        regs[X(ops[0])] = stack.get(int(spm.group(1), 0) if spm.group(1) else 0)   # its reload
    elif m == "sub" and ops[0] == "sp" or m == "add" and ops[0] in ("sp", "x29"):
        pass
    elif m == "adrp":
        regs[X(ops[0])] = ("page", imm(ops[1]) & 0xffffffff)
    elif m == "mov" and len(ops) == 2:
        if ops[1].startswith("#"):
            regs[X(ops[0])] = ("const", imm(ops[1]))
        elif ops[1] in ("xzr", "wzr"):
            regs[X(ops[0])] = ("const", 0)
        else:
            regs[X(ops[0])] = regs.get(X(ops[1]))
    elif m == "movk":
        v = regs.get(X(ops[0]))
        sh = int(ops[2].split("#")[1], 0) if len(ops) > 2 else 0
        regs[X(ops[0])] = ("const", (v[1] & ~(0xffff << sh)) | (imm(ops[1]) << sh)) if v and v[0] == "const" else None
    elif m in ("add", "sub") and len(ops) >= 3:
        s = regs.get(X(ops[1]))
        o = ("const", imm(ops[2]) << (12 if len(ops) > 3 and "lsl #12" in ops[3] else 0)) if ops[2].startswith("#") else regs.get(X(ops[2]))
        sign = 1 if m == "add" else -1
        r = None
        if s and o and o[0] == "const":
            if s[0] in ("this", "const"):
                r = (s[0], s[1] + sign * o[1])
            elif s[0] == "sym" and sign == 1:
                r = ("vt", s[1], o[1])
        elif s and o and s[0] == "const" and o[0] == "this" and sign == 1:
            r = ("this", o[1] + s[1])
        regs[X(ops[0])] = r
    elif m in ("ldr", "ldur") and len(ops) == 2:
        mm = re.fullmatch(r"\[(\w+)(?:, #(-?0x[0-9a-f]+|-?\d+))?\]", ops[1])
        if not mm:
            fail("load form " + i.op_str)
        b = regs.get(X(mm.group(1))); off = int(mm.group(2), 0) if mm.group(2) else 0
        if b and b[0] == "page":
            regs[X(ops[0])] = ("sym", b[1] + off)                 # the GOT slot's symbol
        elif b and b[0] == "sym":
            regs[X(ops[0])] = ("load", b[1], off)                 # a value read through the symbol
        else:
            regs[X(ops[0])] = None
    elif m in ("str", "stur", "stp") and ops:
        mm = re.fullmatch(r"\[(\w+)(?:, #(-?0x[0-9a-f]+|-?\d+))?\](!?)", ops[-1]) or re.fullmatch(r"\[(\w+)\]", ops[-1])
        post = len(ops) >= 3 and m == "str" and re.fullmatch(r"#-?(0x[0-9a-f]+|\d+)", ops[-1]) is not None
        if post:  # post-indexed: str xA, [xB], #K
            base = X(re.fullmatch(r"\[(\w+)\]", ops[1]).group(1)); off = 0
        else:
            if not mm:
                fail("store form " + i.op_str)
            base = X(mm.group(1)); off = int(mm.group(2), 0) if mm.lastindex and mm.lastindex >= 2 and mm.group(2) else 0
        b = regs.get(base)
        vals = [regs.get(X(o)) for o in (ops[:2] if m == "stp" else ops[:1])]
        if b and b[0] == "this":
            for k, v in enumerate(vals):
                at = b[1] + off + k * (8 if ops[0][0] == "x" else 4)
                if v and v[0] == "vt":
                    if v[1] == HANDLE_GOT and v[2] == 0x10:
                        events.append(("hstore", at, None, LI()))
                    elif at == 0:
                        vt_own = v[1]
                    else:
                        fail("vtable store at +%#x" % at)
                else:
                    events.append(("store", at, v, LI()))
        if mm and mm.lastindex and mm.lastindex >= 3 and mm.group(3) == "!" and b and b[0] == "this":
            regs[base] = ("this", b[1] + off)
        if post and b and b[0] == "this":
            regs[base] = ("this", b[1] + int(ops[-1].lstrip("#"), 0))
    elif m in ("bl", "b") and ops[0].startswith("#0x71"):
        tgt = int(ops[0].lstrip("#"), 16) & 0xffffffff
        if addr <= tgt < addr + size:
            if m == "b":
                nxt = tgt
        else:
            x0 = regs.get("x0")
            if not x0 or x0[0] != "this":
                fail("call %x with x0 %s" % (tgt, x0))
            events.append(("call", x0[1], tgt, LI()))
            if m == "b":
                break
            for k in range(19):
                regs.pop("x%d" % k, None)
    elif m == "blr":
        f, x0 = regs.get(X(ops[0])), regs.get("x0")
        if f and f[0] == "load" and f[1] == HANDLE_GOT and f[2] == 0x28 and x0 and x0[0] == "this":
            events.append(("release", x0[1], None, LI()))
        else:
            fail("indirect call %s x0 %s" % (f, x0))
        for k in range(19):
            regs.pop("x%d" % k, None)
    elif m in ("cbz", "cbnz"):
        v = regs.get(X(ops[0])); tgt = int(ops[1].lstrip("#"), 16) & 0xffffffff
        if v and v[0] == "const":
            if (v[1] == 0) == (m == "cbz"):
                nxt = tgt
        # unknown: fall through (the heap test)
    elif m in ("cmp", "cmn"):
        v = regs.get(X(ops[0]))
        o = ("const", imm(ops[1]) << (12 if len(ops) > 2 and "lsl #12" in ops[2] else 0)) if ops[1].startswith("#") else regs.get(X(ops[1]))
        flags = (v[1] - o[1]) if m == "cmp" and v and o and v[0] == o[0] == "const" else \
                (v[1] + o[1]) if v and o and v[0] == o[0] == "const" else None
        regs["nzcv"] = flags
    elif m.startswith("b."):
        f = regs.get("nzcv"); tgt = int(ops[0].lstrip("#"), 16) & 0xffffffff
        if f is None:
            fail("branch on unknown flags at %x" % pc)
        cond = {"b.ne": f != 0, "b.eq": f == 0, "b.lt": f < 0, "b.ge": f >= 0, "b.gt": f > 0, "b.le": f <= 0}.get(m)
        if cond is None:
            fail(m)
        if cond:
            nxt = tgt
    elif m == "ret":
        break
    elif m == "nop":
        pass
    else:
        fail("instruction %s %s at %x" % (m, i.op_str, pc))
    if pc in latches and nxt > pc:  # the loop is left
        it += 1
    pc = nxt

# pair handle stores with releases
handles = []
pend = {}
for k, (kind, off, extra, li) in enumerate(events):
    if kind == "hstore":
        pend[off] = li
    elif kind == "release":
        if off not in pend:
            fail("release of +%#x without its vtable store" % off)
        handles.append((off, pend.pop(off)))
calls = [(off, tgt, li) for kind, off, tgt, li in events if kind == "call"]
base = None
if calls and calls[-1][0] == 0:
    base = calls.pop()[1]
stores = [e for e in events if e[0] == "store"]
if stores:
    fail("plain stores in a destructor: " + ", ".join("+%#x" % e[1] for e in stores[:4]))

# loop iterations: handles of one loop (same iteration set) with a constant stride between iterations
members = []   # (off, decl, size)
loops = {}
for off, li in handles:
    if li is not None:
        loops.setdefault(li, []).append(off)
loop_runs = []
iters = sorted(loops)
used = set()
# group consecutive iterations whose handle patterns repeat at a constant stride
k = 0
while k < len(iters):
    pat = sorted(loops[iters[k]])
    run = [iters[k]]
    while k + len(run) < len(iters):
        nxt = sorted(loops[iters[k + len(run)]])
        if len(nxt) != len(pat):
            break
        d = [x - y for x, y in zip(nxt, pat)]
        if len(set(d)) != 1 or (len(run) > 1 and d[0] != stride):
            break
        stride = d[0]
        pat = nxt
        run.append(iters[k + len(run)])
    if len(run) >= 2:
        loop_runs.append(run)
        used.update(run)
    k += len(run)

if os.environ.get("DTOR_DEBUG"):
    for run in loop_runs:
        print("run", [(r, [hex(x) for x in sorted(loops[r])]) for r in run][:3], "...", len(run), file=sys.stderr)
cls_name = a.name or "Class%x" % addr
decls = []
slot_types = []
for off, li in handles:
    if li in used:
        continue
    members.append((off, f"DtorHandle h{off:x};", 0x18))
parts = {}
for off, tgt, li in calls:
    parts[tgt] = True
    members.append((off, f"Part{tgt:x} m{off:x};", None))
taken = [(off, off + (sz or 1)) for off, decl, sz in members]
loop_handles = {r: [(h, h + 0x18) for h in loops[r]] for run in loop_runs for r in run}
for run in loop_runs:
    first = sorted(loops[run[0]])
    stride = abs(first[0] - sorted(loops[run[1]])[0])
    n = len(run)
    lo = min(min(loops[r]) for r in run)
    hs = sorted(first)
    inner = len(hs)
    span = hs[-1] - hs[0] + 0x18
    if inner > 1 and any(hs[j + 1] - hs[j] != 0x18 for j in range(inner - 1)):
        fail("handles in one iteration are not adjacent")
    # the handles at the end of each slot, or at its start when that would overlap another member
    for pos in (stride - span, 0):
        rng = (lo - pos, lo - pos + stride * n)
        others = taken + [x for r, hs_ in loop_handles.items() if r not in run for x in hs_]
        if rng[0] >= 8 and not any(s < rng[1] and rng[0] < e for s, e in others):
            break
    else:
        fail("no place for the slots of the loop at +%#x" % lo)
    taken.append(rng)
    sname = "Slot%x_%x" % (stride, addr)
    hdecl = "DtorHandle h;" if inner == 1 else "DtorHandle hs[%d];" % inner
    tail = stride - pos - span
    body = (f"unsigned char pad0[{pos:#x}]; " if pos else "") + hdecl + (f" unsigned char pad{pos + span:x}[{tail:#x}];" if tail else "")
    slot_types.append(f"struct {sname} {{ {body} }};{' ' * 4}// {stride:#x}")
    members.append((lo - pos, f"{sname} slots{lo - pos:x}[{n}];", stride * n))
members.sort()
out = []
out.append(open(os.path.join(os.path.dirname(os.path.abspath(__file__)), "dtor_prelude.h"), encoding="utf-8").read().rstrip() + "\n")
for tgt in sorted(parts):
    out.append(f"struct Part{tgt:x} {{ ~Part{tgt:x}(); unsigned char data[0x8]; }};{' ' * 10}// 0x71{tgt:08x}")
out += slot_types
if base:
    out.append(f"\nclass Base{base:x} {{\npublic:\n    virtual ~Base{base:x}();{' ' * 10}// 0x71{base:08x}\n}};")
out.append(f"\nclass {cls_name}{' : public Base%x' % base if base else ''} {{\npublic:\n    {'' if base else 'virtual '}~{cls_name}();\n")
pos = 8
for k, (off, decl, sz) in enumerate(members):
    if off < pos:
        fail("members overlap at +%#x" % off)
    if off > pos:
        out.append(f"    unsigned char pad{pos:x}[{off - pos:#x}];")
    out.append(f"    {decl}{' ' * max(1, 40 - len(decl))}// +{off:x}")
    if sz is None:  # a member destructor's object: up to the next member, at most 8 bytes here
        nxt = members[k + 1][0] if k + 1 < len(members) else off + 8
        sz = min(8, nxt - off)
        if sz < 8:
            out[-1] = out[-1].replace("m%x;" % off, "m%x;" % off)
    pos = off + sz
out.append("};\n")
out.append(f"{cls_name}::~{cls_name}() {{}}\n")
text = "\n".join(out)
# Part sizes: the smallest gap after any of its members, so nothing overlaps
for tgt in parts:
    gaps = [((members[k + 1][0] if k + 1 < len(members) else off + 8) - off) for k, (off, decl, sz) in enumerate(members)
            if decl.startswith("Part%x " % tgt)]
    text = text.replace(f"struct Part{tgt:x} {{ ~Part{tgt:x}(); unsigned char data[0x8]; }};",
                        f"struct Part{tgt:x} {{ ~Part{tgt:x}(); unsigned char data[{max(1, min(gaps + [8])):#x}]; }};")
open(a.out, "w", encoding="utf-8", newline="\n").write(text)
maps = [f"got:gHandleHeapOwner=0x71{HEAP_GOT:08x}", f"got:_ZTV10DtorHandle=0x71{HANDLE_GOT:08x}"]
if vt_own:
    maps.append(f"got:_ZTV{len(cls_name)}{cls_name}=0x71{vt_own:08x}")
for tgt in parts:
    maps.append(f"_ZN{len('Part%x' % tgt)}Part{tgt:x}D1Ev=0x71{tgt:08x}")
if base:
    maps.append(f"_ZN{len('Base%x' % base)}Base{base:x}D2Ev=0x71{base:08x}")
print("name", f"_ZN{len(cls_name)}{cls_name}D2Ev")
print("maps", " ".join("--map " + x for x in maps))
