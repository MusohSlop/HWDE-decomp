"""topotry.py SPEC.json: try every topological order of statements into {REGION} of a template.
SPEC: {"template": path, "addr": hex, "name": sym, "sym": json or null, "maps": [...],
       "stmts": [[id, text, [deps]], ...], "chains": [[id, id, ...], ...] (keep these in this relative order),
       "limit": N}
"""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
WORK = _os.path.join(M, "build", "s3")  # scratch files
_os.makedirs(WORK, exist_ok=True)
import sys, json, os, subprocess, re
spec = json.load(open(sys.argv[1], encoding="utf-8-sig"))
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
    r = subprocess.run([sys.executable, "-B", "-I", os.path.join(SP, "try.py"), out, spec["addr"], "--name", spec["name"], *maps, "--ctx", "0"],
                       capture_output=True, text=True)
    m = re.search(r"instr diff count (\d+)", r.stdout)
    n = int(m.group(1)) if m else 9999
    if best is None or n < best[0]:
        best = (n, o)
        print(n, o, flush=True)
    if "MATCH" in r.stdout:
        open(os.path.join(WORK, "topo_match.cpp"), "w", encoding="utf-8", newline="\n").write(t)
        print("MATCH", o)
        break
print("best", best)
