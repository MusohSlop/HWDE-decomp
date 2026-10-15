"""Generate the given addresses into a probe unit, build, print diffs and source. usage: probe_one.py GEN ADDR[,ADDR...]"""
import os as _os
GENDIR = _os.path.dirname(_os.path.abspath(__file__))
MATCHDIR = _os.path.dirname(_os.path.dirname(GENDIR))
ROOTDIR = _os.path.dirname(MATCHDIR)
import json, os, re, subprocess, sys
gen, addrs = sys.argv[1], sys.argv[2]
m = MATCHDIR
s = os.path.dirname(os.path.abspath(__file__))
py = sys.executable
unit = "misc/mm_probe.cpp"
src = os.path.join(m, "src", "misc", "mm_probe.cpp")
def run(*a, **kw):
    return subprocess.run([py, "-B", "-I", *a], cwd=m, capture_output=True, text=True, **kw)
subprocess.run([py, "-B", "-I", gen, src, unit, "8", "4000"], cwd=m, capture_output=True, text=True, env=dict(os.environ, ONLY=addrs, EXCLUDE=""))
run("tools/check.py", unit); run(os.path.join(s, "fixnames.py"), unit); run(os.path.join(s, "autosym.py"), unit)
c = run("tools/check.py", "--diff", unit, env=dict(os.environ, PROBE_LINES="12"))
print(c.stdout[-6000:])
print(open(src, encoding="utf-8").read()[-4000:])
u = json.load(open(m + r"\data\units.json", encoding="utf-8"))
names = list(u["units"].get(unit, {}).get("functions", {}))
if names:
    subprocess.run([py, "-B", "-I", os.path.join(s, "rm_unit_names.py"), *names])
u = json.load(open(m + r"\data\units.json", encoding="utf-8"))
u["units"].pop(unit, None)
open(m + r"\data\units.json", "w", encoding="utf-8", newline="\n").write(json.dumps(u, indent=2) + "\n")
