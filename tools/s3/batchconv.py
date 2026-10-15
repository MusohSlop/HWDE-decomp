"""batchconv.py RANK.tsv OUT.tsv [--jobs N]: for every generated function in RANK.tsv (default knobs), try variants
and keep the best, all from the fixalign output: G = generated + genfix (loops, panes, handles); O = generated +
onceptr; C = class (full conversion) + genfix panes/handles; P = class prefix + body + genfix loops/panes/handles. Writes addr, size, gen ndiff, best variant, best ndiff; matches are copied to
conv/match_ADDR.cpp with conv/match_ADDR.json and conv/match_ADDR.name."""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
WORK = _os.path.join(M, "build", "s3")  # scratch files
_os.makedirs(WORK, exist_ok=True)
import sys, os, subprocess, re, json, shutil
from concurrent.futures import ThreadPoolExecutor
SP = os.path.dirname(os.path.abspath(__file__))
B = os.path.join(M, "build", "s3rank")
py = sys.executable
rank, outp = sys.argv[1], sys.argv[2]
jobs = int(sys.argv[sys.argv.index("--jobs") + 1]) if "--jobs" in sys.argv else 2
knob = sys.argv[sys.argv.index("--knob") + 1] if "--knob" in sys.argv else "d"
rows = []
for l in open(rank, encoding="utf-8"):
    p = l.rstrip("\n").split("\t")
    if p[3].isdigit() and p[2] != "match":
        rows.append((p[0], int(p[1]), int(p[3])))
os.makedirs(os.path.join(WORK, "conv", "b"), exist_ok=True)


def run(*a):
    return subprocess.run([py, "-B", "-I", *a], capture_output=True, text=True)


def trycpp(cpp, a, symj, name=None):
    args = [os.path.join(SP, "try.py"), cpp, a, symj, "--ctx", "0"]
    if name:
        args += ["--name", name]
    r = run(*args)
    m = re.search(r"instr diff count (\d+)", r.stdout)
    n = int(m.group(1)) if m else 99999
    ok = "MATCH" in r.stdout and "UNRESOLVED" not in r.stdout
    return (0 if ok else max(n, 1)), r.stdout


def one(row):
    a, size, gn = row
    src = os.path.join(B, f"r{a}_{knob}.cpp"); symj = os.path.join(B, f"r{a}_{knob}.json")
    if not os.path.exists(src):
        return a, size, gn, "-", None
    d = os.path.join(WORK, "conv", "b")
    res = []
    # fields the generator declared at offsets their types would not get stay there, packed (for every variant)
    fa = os.path.join(d, f"a{a}.cpp")
    run(os.path.join(SP, "fixalign.py"), src, fa)
    src = fa
    g = os.path.join(d, f"g{a}.cpp")
    run(os.path.join(SP, "genfix.py"), src, g)
    res.append(("G", g, None) + trycpp(g, a, symj))
    o = os.path.join(d, f"o{a}.cpp")
    if re.search(r"onceptr [1-9]", run(os.path.join(SP, "onceptr.py"), src, o).stdout):
        res.append(("O", o, None) + trycpp(o, a, symj))
    for mode in ("C", "P"):
        c = os.path.join(d, f"{mode.lower()}{a}.cpp")
        r = run(os.path.join(SP, "ctor2class.py"), src, a, c, *(["--prefix"] if mode == "P" else []))
        nm = re.search(r"^name (\S+)", r.stdout, re.M)
        mp = re.search(r"^maps (.*)$", r.stdout, re.M)
        if not nm:
            continue
        cf = os.path.join(d, f"{mode.lower()}{a}f.cpp")
        # the prefix form keeps the rest of the body as generated, so its element loops still need rewriting
        run(os.path.join(SP, "genfix.py"), c, cf, *(["loops"] if mode == "P" else []), "panes", "handles")
        # maps for the placeholder classes go into a copy of the symbol json
        sj = json.load(open(symj, encoding="utf-8"))
        for x in (mp.group(1).split() if mp else []):
            if x != "--map":
                sj["gsyms"].append(x)
        sjf = os.path.join(d, f"{mode.lower()}{a}.json")
        json.dump(sj, open(sjf, "w", encoding="utf-8"))
        res.append((mode, cf, nm.group(1)) + trycpp(cf, a, sjf, nm.group(1)) + (sjf,))
    best = min(res, key=lambda x: x[3])
    if best[3] == 0:
        shutil.copy(best[1], os.path.join(WORK, "conv", f"match_{a}.cpp"))
        shutil.copy(best[5] if len(best) > 5 else symj, os.path.join(WORK, "conv", f"match_{a}.json"))
        open(os.path.join(WORK, "conv", f"match_{a}.name"), "w").write(best[2] or "")
    return a, size, gn, best[0], best[3]


with ThreadPoolExecutor(jobs) as ex, open(outp, "w", encoding="utf-8") as f:
    for a, size, gn, v, n in ex.map(one, rows):
        f.write(f"{a}\t{size}\t{gn}\t{v}\t{n}\n"); f.flush()
        print(a, size, gn, v, n, flush=True)
