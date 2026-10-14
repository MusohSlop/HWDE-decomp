"""Generate near misses into a scratch unit under each knob set and report which would match.
usage: nm_probe.py GEN ADDRFILE   (ADDRFILE: hex address first on each line). Leaves units.json without the scratch unit."""
import os as _os
GENDIR = _os.path.dirname(_os.path.abspath(__file__))
MATCHDIR = _os.path.dirname(_os.path.dirname(GENDIR))
ROOTDIR = _os.path.dirname(MATCHDIR)
import json, os, re, subprocess, sys
gen, addrfile = sys.argv[1], sys.argv[2]
m = MATCHDIR
s = os.path.dirname(os.path.abspath(__file__))
py = sys.executable
unit = "misc/nm_probe.cpp"
src = os.path.join(m, "src", "misc", "nm_probe.cpp")
addrs = [l.split("\t")[0].strip() for l in open(addrfile, encoding="utf-8-sig") if l.strip()]
KNOBS = ["", "sink", "callinline", "sink+callinline", "revstores", "sink+revstores", "globalfirst", "globalfirst+sink", "swapif", "swapif+sink", "bytecast", "ptrloop", "narrowparam", "stackpad", "stackpad+sink", "forkjoin", "forkjoin+sink", "norange", "longconst", "argfirst", "argfirst+sink", "argfirst+callinline", "memberaddr", "sortstores", "memberaddr+sortstores+vptrlast", "sortstores+vptrlast", "inlmask_1", "inlmask_2", "sortstores+memberaddr", "sortstores+sink", "sortstores+callinline", "sortstores+globalfirst", "sortstores+argfirst", "sortstores+stackpad", "sortstores+forkjoin", "sortstores+swapif", "sortstores+bytecast", "sortstores+longconst", "memberaddr+sink", "memberaddr+callinline", "memberaddr+argfirst", "memberaddr+stackpad", "memberaddr+forkjoin", "memberaddr+swapif", "sortstores+memberaddr+sink", "sortstores+vptrlast+sink"]

def run(*a, **kw):
    return subprocess.run([py, "-B", "-I", *a], cwd=m, capture_output=True, text=True, **kw)
def reset():
    u = json.load(open(m + r"\data\units.json", encoding="utf-8"))
    names = list(u["units"].get(unit, {}).get("functions", {}))
    for i_ in range(0, len(names), 200):
        subprocess.run([py, "-B", "-I", os.path.join(s, "rm_unit_names.py"), *names[i_:i_ + 200]])
    u = json.load(open(m + r"\data\units.json", encoding="utf-8"))
    u["units"].pop(unit, None)
    open(m + r"\data\units.json", "w", encoding="utf-8", newline="\n").write(json.dumps(u, indent=2) + "\n")

won = {}
for knobs in KNOBS:
    todo = [a for a in addrs if a not in won]
    if not todo:
        break
    exclude = set()
    for rnd in range(5):
        reset()
        env = dict(os.environ, NEARMISS="1", ONLY=",".join(todo), EXCLUDE=",".join(sorted(exclude)), VARIANT=knobs, VARIANT_MAP="")
        subprocess.run([py, "-B", "-I", gen, src, unit, "8", "100000"], cwd=m, capture_output=True, text=True, env=env)
        u = json.load(open(m + r"\data\units.json", encoding="utf-8"))
        if unit not in u["units"]:
            break
        cc = subprocess.run([os.path.join(ROOTDIR, u["compiler"]), *u["flags"], "-ferror-limit=0", "-fsyntax-only",
                             "-I", os.path.join(m, "include"), src], capture_output=True, text=True)
        errs = re.findall(r"\.cpp:(\d+):\d+: error", cc.stdout + cc.stderr)
        if not errs:
            break
        lines = open(src, encoding="utf-8").read().split("\n")
        for ln in errs:
            for k in range(int(ln) - 1, -1, -1):
                mm = re.search(r"\bcall_([0-9a-f]+)\(", lines[k])
                if mm:
                    exclude.add(mm.group(1)); break
    u = json.load(open(m + r"\data\units.json", encoding="utf-8"))
    if unit not in u["units"]:
        print(f"knobs '{knobs}': nothing generated"); continue
    run("tools/check.py", unit); run(os.path.join(s, "fixnames.py"), unit); run(os.path.join(s, "autosym.py"), unit)
    c = run("tools/check.py", unit)
    hits = re.findall(r"^\s+>?\s*([0-9a-f]+) \S+: MATCH", c.stdout, re.M)
    for h in hits:
        won.setdefault(h, knobs)
    gen_n = len(u["units"][unit].get("functions", {}))
    print(f"knobs '{knobs}': generated {gen_n}, +{len([h for h in hits if won[h] == knobs])} new matches")
reset()
if os.path.exists(src):
    os.remove(src)
print("near misses that now match:", len(won))
for a_, k_ in sorted(won.items()):
    print(a_, k_)
