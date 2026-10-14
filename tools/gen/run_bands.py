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
JOBS = int(os.environ.get("RV_JOBS", str(max(2, (os.cpu_count() or 4) - 2))))
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
    gs, imps, perunit = set(), set(), {}
    for un, sy in results:
        if sy is None or not sy["funcs"]:
            continue
        gs |= set(sy["gsyms"]); imps |= set(sy["imports"]); perunit[un] = sy["funcs"]
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

def attempt_chunks(cands, knobs, tag):
    chunks = [sorted(cands)[i:i + CH] for i in range(0, len(cands), CH)]
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
    if os.environ.get("RV_ONLY"):
        # a file of hex image offsets (whitespace or comma separated): only these functions
        found &= {int(x, 16) for x in re.split(r"[\s,]+", open(os.environ["RV_ONLY"], encoding="utf-8").read()) if x}
    return found

def final_unit(best):
    """Write every winner into UNIT under its knobs; drop any that do not match there."""
    for rnd in range(4):
        drop_units([unit], remove_files=False)
        src = os.path.join(M, "src", *unit.split("/"))
        env = dict(os.environ, ONLY=",".join("%x" % a for a in sorted(best)), EXCLUDE="", VARIANT="",
                   VARIANT_MAP=";".join("%x:%s" % (a, k) for a, k in best.items()), DRYRUN="", FAILDUMP="", TRACE="", SYMOUT="")
        subprocess.run([py, "-B", "-I", gen, src, unit, "8", "1000000"], cwd=M, capture_output=True, text=True, env=env)
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
    final_unit(best)
else:
    log("no matches")
log(f"done in {int(time.time() - t0)}s")
