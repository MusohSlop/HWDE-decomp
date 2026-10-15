"""topotry.py SPEC.json [--work DIR]: try every topological order of statements into {REGION} of a template.
SPEC: {"template": path, "addr": hex, "name": sym, "sym": json or null, "maps": [...],
       "stmts": [[id, text, [deps]], ...], "chains": [[id, id, ...], ...] (keep these in this relative order),
       "limit": N, "work": DIR (optional, as --work)}
A match is written to DIR/topo_match.cpp (DIR defaults to build/s3). Exit code 0 on a match, 1 without.
"""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
WORK = _os.path.join(M, "build", "s3")  # scratch files
import sys, json, os, subprocess, re
spec = json.load(open(sys.argv[1], encoding="utf-8-sig"))
if "--work" in sys.argv:
    WORK = os.path.abspath(sys.argv[sys.argv.index("--work") + 1])
elif spec.get("work"):
    WORK = os.path.abspath(spec["work"])
os.makedirs(WORK, exist_ok=True)
SP = os.path.dirname(os.path.abspath(__file__))
src = open(spec["template"], encoding="utf-8").read()
stmts = {s[0]: s for s in spec["stmts"]}
deps = {s[0]: set(s[2]) for s in spec["stmts"]}
for ch in spec.get("chains", []):
    for a, b in zip(ch, ch[1:]):
        deps[b].add(a)
maps = []
if spec.get("sym"):
    d = json.load(open(spec["sym"], encoding="utf-8"))
    for x in d["gsyms"] + d["imports"]:
        maps += ["--map", x]
for x in spec.get("maps", []):
    maps += ["--map", x]
orders = []
def rec(done, cur):
    if len(orders) >= spec.get("limit", 2000):
        return
    if len(cur) == len(stmts):
        orders.append(list(cur)); return
    for k in stmts:
        if k not in done and deps[k] <= done:
            done.add(k); cur.append(k)
            rec(done, cur)
            done.discard(k); cur.pop()
rec(set(), [])
print(len(orders), "orders", flush=True)
out = os.path.join(WORK, "topo_tmp.cpp")
best = None
for o in orders:
    t = src.replace("{REGION}", "".join(stmts[k][1] + "\n" for k in o))
    open(out, "w", encoding="utf-8", newline="\n").write(t)
    r = subprocess.run([sys.executable, "-B", "-I", os.path.join(SP, "try.py"), out, spec["addr"], "--name", spec["name"], *maps,
                        "--ctx", "0", "--work", WORK], capture_output=True, text=True)
    m = re.search(r"instr diff count (\d+)", r.stdout)
    n = int(m.group(1)) if m else 9999
    if best is None or n < best[0]:
        best = (n, o)
        print(n, o, flush=True)
    if "MATCH" in r.stdout.split("\n"):
        open(os.path.join(WORK, "topo_match.cpp"), "w", encoding="utf-8", newline="\n").write(t)
        print("MATCH", o)
        print("best", best)
        sys.exit(0)
print("best", best)
sys.exit(1)
