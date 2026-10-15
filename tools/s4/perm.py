"""perm.py TEMPLATE ADDR NAME OUTDIR [--sym SYMJSON] [--map NAME=ADDR ...] [--slot KEY=opt1|opt2|... [--sep S]]
          [--slots SLOTS.json]

Unattended permutation search: fills the {KEY} placeholders of TEMPLATE with every combination of slot options
(\\n in an option is a newline; SLOTS.json maps each KEY to a list of options, for multi-line ones), compiles each in OUTDIR with tools/s3/try.py and logs one line per combination to
OUTDIR/log.txt (instruction diffs, diffs with registers abstracted, the options). The best so far goes to
OUTDIR/best.cpp, a match to OUTDIR/match.cpp (and the search stops). OUTDIR/done.txt is written at the end.
Every scratch file stays in OUTDIR, so the search can run outside the git worktree; a hit still has to be put
into its unit and pass the full tools/check.py.
"""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
import itertools, json, os, re, subprocess, sys, time

args = sys.argv[1:]
tpl, addr, name, outdir = args[:4]
rest = args[4:]
SEP = rest[rest.index("--sep") + 1] if "--sep" in rest else "|"
maps, slots = [], []
i = 0
while i < len(rest):
    if rest[i] == "--map":
        maps += ["--map", rest[i + 1]]; i += 2
    elif rest[i] == "--sym":
        d = json.load(open(rest[i + 1], encoding="utf-8-sig"))
        for x in d["gsyms"] + d["imports"]:
            maps += ["--map", x]
        i += 2
    elif rest[i] == "--slot":
        k, v = rest[i + 1].split("=", 1)
        slots.append((k, v.split(SEP))); i += 2
    elif rest[i] == "--slots":
        for k, v in json.load(open(rest[i + 1], encoding="utf-8-sig")).items():
            slots.append((k, v))
        i += 2
    else:
        i += 2 if rest[i] == "--sep" else 1
os.makedirs(outdir, exist_ok=True)
src = open(tpl, encoding="utf-8-sig").read()
TRY = os.path.join(M, "tools", "s3", "try.py")
tmp = os.path.join(outdir, "perm_tmp.cpp")
log = open(os.path.join(outdir, "log.txt"), "a", encoding="utf-8")
total = 1
for _, o in slots:
    total *= len(o)
log.write("%s start %s %s: %d combinations\n" % (time.strftime("%Y-%m-%d %H:%M:%S"), addr, name, total)); log.flush()
best = None
for n_, pick in enumerate(itertools.product(*[range(len(o)) for _, o in slots])):
    combo = ["%s=%d" % (k, j) for (k, _), j in zip(slots, pick)]   # logged as option indices
    t = src
    for (k, o), j in zip(slots, pick):
        t = t.replace("{" + k + "}", o[j].replace("\\n", "\n"))
    open(tmp, "w", encoding="utf-8", newline="\n").write(t)
    r = subprocess.run([sys.executable, "-B", "-I", TRY, tmp, addr, "--name", name, *maps, "--ctx", "0"],
                       capture_output=True, text=True, cwd=M)
    m = re.search(r"instr diff count (\d+)", r.stdout)
    ma = re.search(r"abstract diff count (\d+)", r.stdout)
    n = int(m.group(1)) if m else None
    hit = "MATCH" in r.stdout and "UNRESOLVED" not in r.stdout
    log.write("%d/%d\t%s\t%s\t%s%s\n" % (n_ + 1, total, n, ma.group(1) if ma else "-", " ".join(combo), "\tMATCH" if hit else ""))
    log.flush()
    if n is not None and (best is None or n < best[0]):
        best = (n, combo)
        open(os.path.join(outdir, "best.cpp"), "w", encoding="utf-8", newline="\n").write(t)
    if hit:
        open(os.path.join(outdir, "match.cpp"), "w", encoding="utf-8", newline="\n").write(t)
        break
open(os.path.join(outdir, "done.txt"), "w", encoding="utf-8").write("best %s\n" % (best,))
log.write("%s done, best %s\n" % (time.strftime("%Y-%m-%d %H:%M:%S"), best)); log.flush()
