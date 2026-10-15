"""permtry.py TEMPLATE ADDR NAME [--map ...] --slot KEY=opt1|opt2|... : try every combination of slot options.
Template placeholders {KEY}. Prints instr diff count per combination, stops at a match."""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
WORK = _os.path.join(M, "build", "s3")  # scratch files
_os.makedirs(WORK, exist_ok=True)
import sys, subprocess, itertools, os, re
args = sys.argv[1:]
tpl, addr, name = args[0], args[1], args[2]
rest = args[3:]
maps, slots = [], []
SEP = rest[rest.index("--sep") + 1] if "--sep" in rest else "|"
i = 0
while i < len(rest):
    if rest[i] == "--map":
        maps += ["--map", rest[i + 1]]; i += 2
    elif rest[i] == "--sym":
        import json as _j
        for x in (lambda d: d["gsyms"] + d["imports"])(_j.load(open(rest[i + 1], encoding="utf-8"))):
            maps += ["--map", x]
        i += 2
    elif rest[i] == "--slot":
        k, v = rest[i + 1].split("=", 1)
        slots.append((k, v.split(SEP))); i += 2
    elif rest[i] == "--sep":
        i += 2
    else:
        i += 1
src = open(tpl, encoding="utf-8").read()
SP = os.path.dirname(os.path.abspath(__file__))
out = os.path.join(WORK, "perm_tmp.cpp")
best = None
for combo in itertools.product(*[o for _, o in slots]):
    t = src
    for (k, _), v in zip(slots, combo):
        t = t.replace("{" + k + "}", v.replace("\\n", "\n"))
    open(out, "w", encoding="utf-8", newline="\n").write(t)
    r = subprocess.run([sys.executable, "-B", "-I", os.path.join(SP, "try.py"), out, addr, "--name", name, *maps, "--ctx", "0"],
                       capture_output=True, text=True)
    m = re.search(r"instr diff count (\d+)", r.stdout)
    n = int(m.group(1)) if m else None
    ma = re.search(r"abstract diff count (\d+)", r.stdout)
    print(n, ma.group(1) if ma else "-", combo, "MATCH" if "MATCH" in r.stdout else ("" if m else r.stdout[-300:] + r.stderr[-300:]), flush=True)
    if n is not None and (best is None or n < best[0]):
        best = (n, combo)
    if "MATCH" in r.stdout:
        open(os.path.join(WORK, "perm_match.cpp"), "w", encoding="utf-8", newline="\n").write(t)
        break
print("best", best)
