"""Generate a probe unit with a generator, build it, and classify the first difference of each mismatch.
usage: mm_probe.py GENERATOR.py LO HI"""
import os as _os
GENDIR = _os.path.dirname(_os.path.abspath(__file__))
MATCHDIR = _os.path.dirname(_os.path.dirname(GENDIR))
ROOTDIR = _os.path.dirname(MATCHDIR)
import json, os, re, subprocess, sys, collections
gen, lo, hi = sys.argv[1], sys.argv[2], sys.argv[3]
m = MATCHDIR
s = os.path.dirname(os.path.abspath(__file__))
py = sys.executable
unit = "misc/mm_probe.cpp"
src = os.path.join(m, "src", "misc", "mm_probe.cpp")

def run(*a, **kw):
    return subprocess.run([py, "-B", "-I", *a], cwd=m, capture_output=True, text=True, **kw)

def reset():
    u = json.load(open(m + r"\data\units.json", encoding="utf-8"))
    names = list(u["units"].get(unit, {}).get("functions", {}))
    if names:
        for i_ in range(0, len(names), 200):
            subprocess.run([py, "-B", "-I", os.path.join(s, "rm_unit_names.py"), *names[i_:i_ + 200]], check=True)

exclude = set()
for rnd in range(4):
    reset()
    env = dict(os.environ, EXCLUDE=",".join("%x" % e for e in sorted(exclude)))
    subprocess.run([py, "-B", "-I", gen, src, unit, lo, hi], cwd=m, capture_output=True, text=True, env=env)
    u = json.load(open(m + r"\data\units.json", encoding="utf-8"))
    cc = subprocess.run([os.path.join(ROOTDIR, u["compiler"]), *u["flags"], "-ferror-limit=0", "-fsyntax-only", "-I", os.path.join(m, "include"), src], capture_output=True, text=True)
    errs = re.findall(r"\.cpp:(\d+):\d+: error", cc.stdout + cc.stderr)
    if not errs:
        break
    lines = open(src, encoding="utf-8").read().split("\n")
    for ln in errs:
        for k in range(int(ln) - 1, -1, -1):
            mm = re.search(r"(?:leaf|forward|branch|call)_([0-9a-f]+)\(", lines[k])
            if mm:
                exclude.add(int(mm.group(1), 16)); break
run("tools/check.py", unit)
run(os.path.join(s, "fixnames.py"), unit)
run(os.path.join(s, "autosym.py"), unit)
c = run("tools/check.py", "--diff", unit, env=dict(os.environ, PROBE_LINES="3"))
out = c.stdout + c.stderr
pairs = collections.Counter()
examples = collections.defaultdict(list)
cur = None
for line in out.split("\n"):
    mm = re.match(r"\s*>?\s+([0-9a-f]+) \S+: MISMATCH \((\d+) of (\d+)", line)
    if mm:
        cur = mm.group(1); continue
    mm = re.match(r"\s+\+0x[0-9a-f]+\s+ours: \S+ (\S+)[^|]*\| orig: \S+ (\S+)", line)
    if mm and cur:
        key = (mm.group(1), mm.group(2))
        pairs[key] += 1
        examples[key].append(cur)
        cur = None
total = sum(pairs.values())
print("mismatches classified:", total)
for k, v in pairs.most_common(25):
    print(v, k, examples[k][:4])
reset()
u = json.load(open(m + r"\data\units.json", encoding="utf-8"))
if unit in u["units"]:
    del u["units"][unit]
    open(m + r"\data\units.json", "w", encoding="utf-8", newline="\n").write(json.dumps(u, indent=2) + "\n")
