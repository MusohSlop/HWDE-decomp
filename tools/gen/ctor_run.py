"""Constructors as classes through the third session's converter (the ctorclass step).

usage: ctor_run.py UNIT FAILDUMP [--jobs N] [--lo HEX] [--hi HEX] [--skip FILE[;FILE...]]

Takes the unmatched addresses of docs/s3_scope.txt that generate (absent from FAILDUMP, a gen.py FAILDUMP of a dry
run over every function), drops those in the skip files (the hand sessions' claims), and runs tools/s3/rank.py
(generated source per function), tools/s3/batchconv.py (the generated version, the class conversion and the
class prefix, each through genfix) and tools/s3/addgen.py for every match, into UNIT. The converter logic stays in
tools/s3/; this only drives it. Run tools/check.py --update afterwards.
"""
import os as _os
GENDIR = _os.path.dirname(_os.path.abspath(__file__))
M = _os.path.dirname(_os.path.dirname(GENDIR))
import csv, json, os, re, subprocess, sys

args = sys.argv[1:]
unit, faildump = args[0], args[1]
opt = {k: args[args.index(k) + 1] for k in ("--jobs", "--lo", "--hi", "--skip") if k in args}
jobs = opt.get("--jobs", "4")
lo, hi = int(opt.get("--lo", "0"), 16), int(opt.get("--hi", "ffffffff"), 16)
S3 = os.path.join(M, "tools", "s3")
py = sys.executable


def hexset(path):
    out = set()
    if path and os.path.exists(path):
        for tok in re.findall(r"\b(?:0x)?([0-9a-f]{4,10})\b", open(path, encoding="utf-8-sig").read().lower()):
            v = int(tok, 16)
            out.add(v - 0x7100000000 if v >= 0x7100000000 else v)
    return out


scope = hexset(os.path.join(M, "docs", "s3_scope.txt"))
skip = set()
for f in opt.get("--skip", "").split(";"):
    skip |= hexset(f.strip())
fails = {int(l.split("\t")[0], 16) for l in open(faildump, encoding="utf-8")}
u = json.load(open(os.path.join(M, "data", "units.json"), encoding="utf-8"))
taken = {int(v, 16) - 0x7100000000 for x in u["units"].values() for v in x.get("functions", {}).values()}
rows = {int(r[0], 16) - 0x7100000000 for r in csv.reader(open(os.path.join(M, "data", "functions.csv")))
        if r[0].startswith("0x") and r[1] == "U"}
cands = sorted(a for a in scope & rows if lo <= a < hi and a not in fails and a not in taken and a not in skip)
print(len(cands), "generating constructors")
work = os.path.join(M, "build", "ctor_run")
os.makedirs(work, exist_ok=True)
open(os.path.join(work, "cands.txt"), "w").write(" ".join("%x" % a for a in cands))
rank, conv = os.path.join(work, "rank.tsv"), os.path.join(work, "conv.tsv")
subprocess.run([py, "-B", "-I", os.path.join(S3, "rank.py"), rank, "8", "1000000", "--jobs", jobs, "--only",
                os.path.join(work, "cands.txt")], cwd=M)
subprocess.run([py, "-B", "-I", os.path.join(S3, "batchconv.py"), rank, conv, "--jobs", jobs], cwd=M)
cdir = os.path.join(M, "build", "s3", "conv")
added = []
for a in cands:
    src = os.path.join(cdir, "match_%x.cpp" % a)
    if os.path.exists(src):
        r = subprocess.run([py, "-B", "-I", os.path.join(S3, "addgen.py"), src, "%x" % a,
                            os.path.join(cdir, "match_%x.json" % a), unit], cwd=M, capture_output=True, text=True)
        print("%x" % a, (r.stdout.strip().splitlines() or [""])[-1])
        added.append(a)
print(len(added), "added to", unit)
