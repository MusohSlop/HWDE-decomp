"""Parallel variant search over many functions: chunks are generated and compiled in parallel (the generator writes
its symbols to a side file, SYMOUT), and symbol updates are applied in batches by this process only.
usage: run_bands.py GENERATOR.py UNIT LO HI [KNOBFILE]   (GENERATOR must support SYMOUT)"""
import os as _os
GENDIR = _os.path.dirname(_os.path.abspath(__file__))
MATCHDIR = _os.path.dirname(_os.path.dirname(GENDIR))
ROOTDIR = _os.path.dirname(MATCHDIR)
import csv, json, os, re, subprocess, sys, time
from concurrent.futures import ThreadPoolExecutor
gen, unit, lo, hi = sys.argv[1], sys.argv[2], int(sys.argv[3]), int(sys.argv[4])
M = MATCHDIR
S = os.path.dirname(os.path.abspath(__file__))
TMP = os.path.join(MATCHDIR, "build", "rvtmp")
os.makedirs(TMP, exist_ok=True)
py = sys.executable
CH = int(os.environ.get("RV_CHUNK", "25"))
JOBS = int(os.environ.get("RV_JOBS", "6"))
TIMEOUT = int(os.environ.get("RV_TIMEOUT", "300"))
KNOBS = ["", "sink", "callinline", "sink+callinline", "revstores", "sink+revstores", "globalfirst", "globalfirst+sink",
         "swapif", "swapif+sink", "bytecast", "ptrloop", "narrowparam", "stackpad", "stackpad+sink", "forkjoin",
         "forkjoin+sink", "norange", "longconst", "argfirst", "argfirst+sink", "argfirst+callinline", "memberaddr",
         "sortstores", "memberaddr+sortstores+vptrlast", "sortstores+vptrlast", "inlmask_1", "inlmask_2"]
if len(sys.argv) > 5:
    KNOBS = [l.strip() for l in open(sys.argv[5], encoding="utf-8-sig")]
U0 = json.load(open(M + r"\data\units.json", encoding="utf-8"))
COMPILER = os.path.join(ROOTDIR, U0["compiler"])
FLAGS = U0["flags"]
SLOWLOG = os.path.join(MATCHDIR, "build", "rvpar_slow.txt")

def log(*a):
    print(*a, flush=True)

def log_slow(addrs, knobs, stage):
    with open(SLOWLOG, "a", encoding="utf-8") as f_:
        f_.write(f"{stage}\tknobs={knobs}\t" + ",".join("%x" % a for a in sorted(addrs)) + "\n")

def units():
    return json.load(open(M + r"\data\units.json", encoding="utf-8"))

def drop_units(names, remove_files=True):
    u = units()
    fn = [f for n in names for f in u["units"].get(n, {}).get("functions", {})]
    for i_ in range(0, len(fn), 200):
        subprocess.run([py, "-B", "-I", os.path.join(S, "rm_unit_names.py"), *fn[i_:i_ + 200]], cwd=M, capture_output=True)
    u = units()
    changed = False
    for n in names:
        if n in u["units"]:
            del u["units"][n]; changed = True
    if changed:
        open(M + r"\data\units.json", "w", encoding="utf-8", newline="\n").write(json.dumps(u, indent=2) + "\n")
    if remove_files:
        for n in names:
            p = os.path.join(M, "src", *n.split("/"))
            if os.path.exists(p):
                os.remove(p)

def run_timeout(cmd, timeout, env=None):
    pr = subprocess.Popen(cmd, cwd=M, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, env=env)
    try:
        out, _ = pr.communicate(timeout=timeout)
        return pr.returncode, out
    except subprocess.TimeoutExpired:
        subprocess.run(["taskkill", "/T", "/F", "/PID", str(pr.pid)], capture_output=True)
        try:
            out, _ = pr.communicate(timeout=30)
        except Exception:
            out = ""
        return None, out or ""

def gen_one(job):
    un, addrs, knobs, exclude = job
    src = os.path.join(M, "src", *un.split("/"))
    symf = os.path.join(TMP, un.replace("/", "_") + ".json")
    if os.path.exists(symf):
        os.remove(symf)
    env = dict(os.environ, ONLY=",".join("%x" % a for a in sorted(addrs)), EXCLUDE=",".join("%x" % e for e in sorted(exclude)),
               VARIANT=knobs, VARIANT_MAP="", DRYRUN="", FAILDUMP="", TRACE="", SYMOUT=symf)
    rc, out = run_timeout([py, "-B", "-I", gen, src, un, "8", "1000000"], TIMEOUT, env=env)
    if rc is None or not os.path.exists(symf):
        return un, None, out
    return un, json.load(open(symf, encoding="utf-8")), out

def apply_symbols(results):
    gs, imps, perunit, jtab = set(), set(), {}, {}
    for un, sy in results:
        if sy is None or not sy["funcs"]:
            continue
        gs |= set(sy["gsyms"]); imps |= set(sy["imports"]); perunit[un] = sy["funcs"]
        if sy.get("rodata"):
            jtab[un] = sy["rodata"]
    gl = sorted(gs)
    for i_ in range(0, len(gl), 200):
        subprocess.run([py, "-B", "-I", M + r"\tools\add_symbols.py", *gl[i_:i_ + 200]], cwd=M, capture_output=True)
    il = sorted(imps)
    for i_ in range(0, len(il), 200):
        subprocess.run([py, "-B", "-I", M + r"\tools\add_symbols.py", *il[i_:i_ + 200]], cwd=M, capture_output=True)
    for un, fl in perunit.items():
        for i_ in range(0, len(fl), 200):
            subprocess.run([py, "-B", "-I", M + r"\tools\add_symbols.py", "--unit", un, *fl[i_:i_ + 200]], cwd=M, capture_output=True)
    u = units()
    for un in perunit:
        if un in u["units"]:
            u["units"][un].setdefault("map", {})[".rodata.cst4"] = "0x710073b000"
            u["units"][un]["map"][".rodata.cst16"] = "0x710073dff0"
            if un in jtab:
                u["units"][un]["map"][".rodata"] = jtab[un]   # the unit's jump tables
    open(M + r"\data\units.json", "w", encoding="utf-8", newline="\n").write(json.dumps(u, indent=2) + "\n")
    return set(perunit)

def syntax_bad(src):
    if not os.path.exists(src):
        return set(), False
    rc, out = run_timeout([COMPILER, *FLAGS, "-ferror-limit=0", "-fsyntax-only", "-I", os.path.join(M, "include"), src], TIMEOUT)
    if rc is None:
        return None, True
    bad = set()
    errs = re.findall(r"\.cpp:(\d+):\d+: error", out)
    if errs:
        lines = open(src, encoding="utf-8").read().split("\n")
        marks = [(k, int(mm.group(1), 16)) for k, l in enumerate(lines) for mm in [re.match(r"// 0x71([0-9a-f]{8})", l)] if mm]
        ends = []
        for idx, (k, a_) in enumerate(marks):
            e_ = next((j for j in range(k + 1, len(lines)) if lines[j] == "}"), len(lines) - 1)
            ends.append(e_)
        for ln in errs:
            n = int(ln) - 1
            owner = None
            for idx, (k, a_) in enumerate(marks):
                if n <= ends[idx]:
                    owner = a_; break
            if owner is None and marks:
                owner = marks[-1][1]
            if owner is not None:
                bad.add(owner)
        if not bad:
            return None, True
    return bad, False

def check(un):
    rc, out = run_timeout([py, "-B", "-I", "tools/check.py", un], TIMEOUT)
    if rc is None or "COMPILE FAILED" in out:
        return None
    good = {int(x, 16) for x in re.findall(r"^\s+>?\s*([0-9a-f]+) \S+: MATCH", out, re.M)}
    bad = {int(x, 16) for x in re.findall(r"^\s+>?\s*([0-9a-f]+) \S+: (?:MISMATCH|SIZE MISMATCH|MISSING)", out, re.M)}
    return good, bad, ("unresolved" in out)

IMG = open(os.path.join(os.path.dirname(M), "analysis", "extracted", "update", "decompressed", "main.memory.bin"), "rb").read()
SIZES = {int(r_[0], 16) - 0x7100000000: int(r_[2]) for r_ in csv.reader(open(M + r"\data\functions.csv")) if r_[0].startswith("0x")}
def has_br(a):
    """True when the function has a br (a switch jump table or a computed jump)."""
    return any((int.from_bytes(IMG[a + k:a + k + 4], "little") & 0xFFFFFC1F) == 0xD61F0000 for k in range(0, SIZES.get(a, 0), 4))

def attempt_chunks(cands, knobs, tag):
    # a unit's jump tables share one .rodata anchor, so each chunk takes at most one function with a br
    jt = sorted(a for a in cands if has_br(a))
    rest = sorted(set(cands) - set(jt))
    n = max(len(jt), (len(cands) + CH - 1) // CH)
    chunks = [[] for _ in range(n)]
    for i, a in enumerate(jt):
        chunks[i].append(a)
    for i, a in enumerate(rest):
        chunks[i % n].append(a)
    chunks = [sorted(c) for c in chunks if c]
    names = [f"misc/rvpar_{tag}_{i}.cpp" for i in range(len(chunks))]
    excl = [set() for _ in chunks]
    dropped = set()
    live = list(range(len(chunks)))
    for rnd in range(5):
        drop_units([names[i] for i in live])
        with ThreadPoolExecutor(JOBS) as ex:
            res = list(ex.map(gen_one, [(names[i], set(chunks[i]) - excl[i], knobs, excl[i]) for i in live]))
        for un, sy, out in res:
            if sy is None:
                i = names.index(un)
                log_slow(set(chunks[i]) - excl[i], knobs, "generation timeout")
                dropped |= set(chunks[i]) - excl[i]; excl[i] |= set(chunks[i])
        apply_symbols([(un, sy) for un, sy, out in res])
        srcs = {i: os.path.join(M, "src", *names[i].split("/")) for i in live}
        with ThreadPoolExecutor(JOBS) as ex:
            sres = dict(zip(live, ex.map(lambda i: syntax_bad(srcs[i]), live)))
        nxt = []
        for i, (bad, slow) in sres.items():
            if slow:
                log_slow(set(chunks[i]) - excl[i], knobs, "syntax timeout")
                dropped |= set(chunks[i]) - excl[i]; excl[i] |= set(chunks[i])
            elif bad:
                excl[i] |= bad; dropped |= bad; nxt.append(i)
        if not nxt:
            break
        live = nxt
    u = units()
    active = [i for i in range(len(chunks)) if names[i] in u["units"] and u["units"][names[i]].get("functions")]
    with ThreadPoolExecutor(JOBS) as ex:
        first = dict(zip(active, ex.map(lambda i: check(names[i]), active)))
    ok, timed_out = [], []
    for i in active:
        if first[i] is None:
            log_slow(set(chunks[i]) - excl[i], knobs, "compile timeout (chunk, bisecting)")
            dropped |= set(chunks[i]) - excl[i]
            timed_out.append(i)
        else:
            ok.append(i)
    for j in range(0, len(ok), 40):
        subprocess.run([py, "-B", "-I", os.path.join(S, "batch_fix.py"), *[names[i] for i in ok[j:j + 40]]], cwd=M, capture_output=True)
    with ThreadPoolExecutor(JOBS) as ex:
        second = dict(zip(ok, ex.map(lambda i: check(names[i]), ok)))
    good, badm = set(), set()
    for i, r in second.items():
        if r is None:
            log_slow(set(chunks[i]) - excl[i], knobs, "compile timeout (chunk, bisecting)")
            dropped |= set(chunks[i]) - excl[i]; timed_out.append(i); continue
        g_, b_, unres = r
        if unres:
            cm = subprocess.run([py, "-B", "-I", os.path.join(S, "clean_matches.py"), names[i]], cwd=M, capture_output=True, text=True)
            clean_ = {int(x, 16) for x in cm.stdout.split()} & g_
            b_ |= g_ - clean_; g_ = clean_
        good |= g_; badm |= b_
    drop_units(names)
    # chunks that timed out: split them and retry the halves, so only the function that hangs is lost
    lost = set()
    for i in timed_out:
        g_, b_, l_ = bisect(sorted(set(chunks[i]) - excl[i]), knobs, f"{tag}_{i}", 0)
        good |= g_; badm |= b_; lost |= l_
        dropped -= (set(chunks[i]) - excl[i]) - l_
    LOST[0] += len(lost)
    return good, badm, dropped

def bisect(addrs, knobs, tag, depth):
    """Generate, compile and check addrs in one unit; on a timeout split in two. Returns (good, bad, lost)."""
    if not addrs:
        return set(), set(), set()
    un = f"misc/rvbis_{tag}_{depth}_{addrs[0]:x}.cpp"
    drop_units([un])
    excl_ = set()
    for _ in range(4):
        r = gen_one((un, set(addrs) - excl_, knobs, excl_))
        if r[1] is None:
            break
        apply_symbols([(r[0], r[1])])
        bad, slow = syntax_bad(os.path.join(M, "src", *un.split("/")))
        if slow or not bad:
            break
        excl_ |= bad
    res = None if (r[1] is None or slow) else check(un)
    if res is not None:
        subprocess.run([py, "-B", "-I", os.path.join(S, "batch_fix.py"), un], cwd=M, capture_output=True)
        res = check(un)
    if res is None:
        drop_units([un])
        if len(addrs) == 1:
            log_slow(set(addrs), knobs, "single function timeout")
            return set(), set(), set(addrs)
        h = len(addrs) // 2
        a1 = bisect(addrs[:h], knobs, tag, depth + 1)
        a2 = bisect(addrs[h:], knobs, tag, depth + 1)
        return a1[0] | a2[0], a1[1] | a2[1], a1[2] | a2[2]
    g_, b_, unres = res
    if unres:
        cm = subprocess.run([py, "-B", "-I", os.path.join(S, "clean_matches.py"), un], cwd=M, capture_output=True, text=True)
        clean_ = {int(x, 16) for x in cm.stdout.split()} & g_
        b_ |= g_ - clean_; g_ = clean_
    drop_units([un])
    return g_, b_, set()

def candidates():
    rows = [r for r in csv.reader(open(M + r"\data\functions.csv")) if r[0].startswith("0x")]
    taken = {int(v, 16) - 0x7100000000 for u_ in units()["units"].values() for v in u_.get("functions", {}).values()}
    alo = int(os.environ.get("RV_ADDR_LO", "0"), 16); ahi = int(os.environ.get("RV_ADDR_HI", "ffffffff"), 16)
    found = {int(r[0], 16) - 0x7100000000 for r in rows if r[1] == "U" and lo <= int(r[2]) <= hi
             and alo <= int(r[0], 16) - 0x7100000000 < ahi} - taken
    skips_ = [f_ for f_ in os.environ.get("RV_SKIP", "").split(";") if f_.strip()]
    if not os.environ.get("RV_NODEFAULTSKIP"):
        # every hand session's scope and claims, from this checkout and each session's worktree, so a function belongs
        # to exactly one session's pass; RV_OWN (for example s3) keeps that session's own files out of the list
        own_ = os.environ.get("RV_OWN", "").strip()
        root_ = os.path.dirname(M)      # project1, or project1\worktrees\sN when run from a worktree
        if os.path.basename(os.path.dirname(root_)) == "worktrees":
            root_ = os.path.dirname(os.path.dirname(root_))
        for f_ in ("s3_scope.txt", "s3_claims.txt", "s4_claims.txt", "s5_claims.txt"):
            if own_ and f_.startswith(own_ + "_"):
                continue
            skips_.append(os.path.join(M, "docs", f_))
            skips_.append(os.path.join(root_, "worktrees", f_[:2], "matching", "docs", f_))
    n0_ = len(found)
    for skipf in skips_:
        # addresses other sessions are hand-matching (hex image offsets or full 0x71... addresses); a file that does
        # not exist yet is skipped
        if not os.path.exists(skipf.strip()):
            continue
        for tok in re.findall(r"\b(?:0x)?([0-9a-f]{4,10})\b", open(skipf.strip(), encoding="utf-8-sig").read().lower()):
            v_ = int(tok, 16)
            found.discard(v_ - 0x7100000000 if v_ >= 0x7100000000 else v_)
    print(f"skipped {n0_ - len(found)} candidates listed by other sessions", flush=True)
    if os.environ.get("RV_ONLY"):
        # a file of hex image offsets (whitespace or comma separated): only these functions
        found &= {int(x, 16) for x in re.split(r"[\s,]+", open(os.environ["RV_ONLY"], encoding="utf-8-sig").read()) if x}
    return found

def final_units(best):
    """Write the winners into UNIT, and those whose jump tables do not follow the unit's into UNIT_2, UNIT_3, ..."""
    pending, n, out = dict(best), 1, {}
    while pending and n < 300:
        un = unit if n == 1 else unit[:-4] + f"_{n}.cpp"
        apart = set()
        out.update(final_unit(pending, un, apart))
        pending = {a: k for a, k in best.items() if a in apart}
        n += 1
    return out

def final_unit(best, unit, apart):
    """Write every winner into UNIT under its knobs; drop any that do not match there."""
    best = dict(best)
    for rnd in range(4):
        drop_units([unit], remove_files=False)
        src = os.path.join(M, "src", *unit.split("/"))
        env = dict(os.environ, ONLY=",".join("%x" % a for a in sorted(best)), EXCLUDE="", VARIANT="",
                   VARIANT_MAP=";".join("%x:%s" % (a, k) for a, k in best.items()), DRYRUN="", FAILDUMP="", TRACE="", SYMOUT="",
                   APARTOUT=os.path.join(TMP, "apart.txt"))
        subprocess.run([py, "-B", "-I", gen, src, unit, "8", "1000000"], cwd=M, capture_output=True, text=True, env=env)
        apart.clear()
        apart |= {int(x, 16) for x in open(os.path.join(TMP, "apart.txt"), encoding="utf-8").read().split()}
        for a in apart:
            best.pop(a, None)
        bad, slow = syntax_bad(src)
        if slow or bad:
            for a in (bad or set()):
                best.pop(a, None)
            if slow:
                log("final unit syntax timeout"); return {}
            continue
        subprocess.run([py, "-B", "-I", "tools/add_symbols.py", "--map", unit, ".rodata.cst4=0x710073b000", ".rodata.cst16=0x710073dff0"], cwd=M, capture_output=True)
        check(unit)
        subprocess.run([py, "-B", "-I", os.path.join(S, "batch_fix.py"), unit], cwd=M, capture_output=True)
        r = check(unit)
        if r is None:
            log("final unit timed out"); return {}
        g_, b_, unres = r
        log(f"final {unit}: {len(g_)} match, {len(b_)} mismatch{', unresolved' if unres else ''}")
        if not b_ and not unres:
            return best
        for a in b_:
            best.pop(a, None)
        if not best:
            drop_units([unit]); return {}
    return best

LOST = [0]
t0 = time.time()
best = {}
remaining = candidates()
log(f"{len(remaining)} candidates, chunks of {CH}, {JOBS} parallel jobs, timeout {TIMEOUT}s")
for n_, knobs in enumerate(KNOBS):
    if not remaining:
        break
    good, badm, dropped = attempt_chunks(remaining, knobs, n_)
    for a in good:
        best.setdefault(a, knobs)
    remaining = (remaining & (badm | dropped)) - set(best)
    log(f"knobs '{knobs}': +{len(good)} matched ({len(best)} total), {len(remaining)} left, {len(dropped)} dropped, "
        f"{LOST[0]} lost to chunk failures so far ({int(time.time() - t0)}s)")
    json.dump({"%x" % a: k for a, k in best.items()}, open(os.path.join(TMP, "best.json"), "w"))
if best:
    final_units(best)
else:
    log("no matches")
log(f"done in {int(time.time() - t0)}s")
