"""permtry.py TEMPLATE ADDR NAME [--map ...] [--sym SYMJSON] [--sep SEP] [--work DIR] --slot KEY=opt1|opt2|... :
try every combination of slot options. Template placeholders {KEY}. Prints instr diff count per combination,
stops at a match (written to DIR/perm_match.cpp; DIR defaults to build/s3). Exit code 0 on a match, 1 without."""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
WORK = _os.path.join(M, "build", "s3")  # scratch files
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
    elif rest[i] == "--work":
        WORK = os.path.abspath(rest[i + 1]); i += 2
    elif rest[i] == "--sep":
        i += 2
    else:
        i += 1
os.makedirs(WORK, exist_ok=True)
src = open(tpl, encoding="utf-8").read()
SP = os.path.dirname(os.path.abspath(__file__))
out = os.path.join(WORK, "perm_tmp.cpp")
best = None
for combo in itertools.product(*[o for _, o in slots]):
    t = src
    for (k, _), v in zip(slots, combo):
        t = t.replace("{" + k + "}", v.replace("\\n", "\n"))
    open(out, "w", encoding="utf-8", newline="\n").write(t)
    r = subprocess.run([sys.executable, "-B", "-I", os.path.join(SP, "try.py"), out, addr, "--name", name, *maps, "--ctx", "0",
                        "--work", WORK], capture_output=True, text=True)
    m = re.search(r"instr diff count (\d+)", r.stdout)
    n = int(m.group(1)) if m else None
    ma = re.search(r"abstract diff count (\d+)", r.stdout)
    hit = "MATCH" in r.stdout.split("\n")
    print(n, ma.group(1) if ma else "-", combo, "MATCH" if hit else ("" if m else r.stdout[-300:] + r.stderr[-300:]), flush=True)
    if n is not None and (best is None or n < best[0]):
        best = (n, combo)
    if hit:
        open(os.path.join(WORK, "perm_match.cpp"), "w", encoding="utf-8", newline="\n").write(t)
        print("best", best)
        sys.exit(0)
print("best", best)
sys.exit(1)
