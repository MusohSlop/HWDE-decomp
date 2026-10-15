"""variants.py SPEC.json: try source variants of one function and print the diff counts of each.

SPEC: {"base": "build/s5/x.cpp", "addr": "45a850", "args": ["--map", "N=A", ...],
       "variants": {"label": [["old", "new"], ...], ...}}
Each variant applies its replacements (exact text, each must occur at least once; every occurrence is replaced) to
the base file, writes build/s5/variant_LABEL.cpp and runs tools/s5/sbs.py on it. Prints label, size line and
counts, best first. An empty replacement list compiles the base file as it is.
"""
import json, os, re, subprocess, sys
M = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))  # the matching/ folder
spec = json.load(open(sys.argv[1], encoding="utf-8"))
base = open(os.path.join(M, spec["base"]), encoding="utf-8").read()
rows = []
for label, subs in spec["variants"].items():
    t = base
    missing = [o for o, n in subs if o not in t]
    if missing:
        rows.append((10 ** 9, label, "missing: " + missing[0][:60]))
        continue
    for o, n in subs:
        t = t.replace(o, n)
    path = os.path.join(M, "build", "s5", "variant_%s.cpp" % re.sub(r"\W", "_", label))
    open(path, "w", encoding="utf-8", newline="\n").write(t)
    r = subprocess.run([sys.executable, "-B", "-I", os.path.join(M, "tools", "s5", "sbs.py"), path, spec["addr"],
                        *spec.get("args", [])], capture_output=True, text=True, cwd=M)
    lines = r.stdout.split("\n")
    m = re.search(r"instr diff count (\d+)\s+abstract diff count (\d+)", r.stdout)
    if not m:
        rows.append((10 ** 8, label, (r.stdout + r.stderr).strip().split("\n")[-1][:120]))
        continue
    rows.append((int(m.group(1)), label, lines[0].split(":", 1)[-1].strip() + " | " + m.group(0) +
                 (" MATCH" if "MATCH" in r.stdout else "")))
for score, label, text in sorted(rows):
    print("%-16s %s" % (label, text))
