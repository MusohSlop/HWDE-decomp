"""ours.py CPP ADDR [SYMJSON] [--name SYM] [--map ...] [--out FILE]: compile like try.py and write our relocated
disassembly of the function (address column as in the original image) to FILE or stdout."""
import os as _os
import sys, subprocess, re
args = sys.argv[1:]
out = None
if "--out" in args:
    k = args.index("--out"); out = args[k + 1]; del args[k:k + 2]
r = subprocess.run([sys.executable, "-B", "-I", _os.path.join(_os.path.dirname(_os.path.abspath(__file__)), "try.py"),
                    *args, "--all", "--ctx", "0"], capture_output=True, text=True)
res = []
for l in r.stdout.split("\n"):
    m = re.match(r"\s+([0-9a-f]+) ([- ]) (.*)$", l)
    if m:
        res.append(f"  {m.group(3)}")
base = int(args[1], 16)
text = "\n".join(f"  {base + 4 * k:6x}{l}" for k, l in enumerate(res)) + "\n"
if out:
    open(out, "w", encoding="utf-8").write(text)
else:
    sys.stdout.write(text)
