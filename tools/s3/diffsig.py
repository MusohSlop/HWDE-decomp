"""diffsig.py BATCH.tsv [MAXN]: for each function of a batchconv.py table whose best variant is at most MAXN instructions
off, compile that variant and print the differing instructions (ours '-', original '+'), registers abstracted, as
a one-line signature; for spotting shared causes."""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))
WORK = _os.path.join(M, "build", "s3")
import sys, subprocess, re
S3 = _os.path.dirname(_os.path.abspath(__file__))
maxn = int(sys.argv[2]) if len(sys.argv) > 2 else 6
B = _os.path.join(WORK, "conv", "b")
for l in open(sys.argv[1], encoding="utf-8"):
    a, size, gn, v, n = l.rstrip("\n").split("\t")
    if not n.isdigit() or not (0 < int(n) <= maxn):
        continue
    if v == "G":
        cpp, js, name = _os.path.join(B, f"g{a}.cpp"), _os.path.join(M, "build", "s3rank", f"r{a}_d.json"), None
    else:
        cpp, js = _os.path.join(B, f"{v.lower()}{a}f.cpp"), _os.path.join(B, f"{v.lower()}{a}.json")
        name = f"_ZN{len('Class' + a)}Class{a}C2E" + "v"
    args = [sys.executable, "-B", "-I", _os.path.join(S3, "try.py"), cpp, a, js, "--ctx", "0"]
    if name:
        args += ["--name", name]
    r = subprocess.run(args, capture_output=True, text=True)
    sig = []
    for x in r.stdout.split("\n"):
        m = re.match(r"\s+[0-9a-f]+ ([-+]) (.*)$", x)
        if m:
            ins = re.sub(r"\b([xwsdq])(\d+|zr)\b", r"\1", m.group(2))
            ins = re.sub(r"#0x7100[0-9a-f]+", "#A", ins)
            sig.append(m.group(1) + ins)
    print(f"{a}\t{size}\t{n}\t{v}\t" + " ; ".join(sig[:8]))
