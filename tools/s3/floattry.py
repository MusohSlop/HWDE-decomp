"""floattry.py CPP ADDR SYMJSON [--max K] [--name SYM] [--work DIR]: in a generated source, retype `int field_X`
fields that the function stores zero to as `float` (stored as 0.0f), every subset of up to K of them (default 2),
and run try.py on each. Clang merges adjacent int stores into one wider store, but not stores of different
memory types, so a field that is a float in the original keeps its own `str wzr` (3322ac). Stops at the first
match (DIR/float_match.cpp; DIR defaults to build/s3). Exit code 0 on a match, 1 without.

floattry.py --list FILE [--max K] [--work DIR]: the same for each line 'ADDR CPP SYMJSON [SYM]' of FILE; matches
go to DIR/float_match_ADDR.cpp. Exit code 0 when at least one matched."""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
import sys, re, subprocess, itertools, argparse
S3 = _os.path.dirname(_os.path.abspath(__file__))
ap = argparse.ArgumentParser()
ap.add_argument("cpp", nargs="?"); ap.add_argument("addr", nargs="?"); ap.add_argument("symjson", nargs="?")
ap.add_argument("--max", type=int, default=2); ap.add_argument("--name"); ap.add_argument("--list")
ap.add_argument("--work", default=_os.path.join(M, "build", "s3"))
a = ap.parse_args()
WORK = _os.path.abspath(a.work)
_os.makedirs(WORK, exist_ok=True)


def search(cpp, addr, symjson, name, match_path):
    src = open(cpp, encoding="utf-8").read()
    zeros = sorted(set(re.findall(r"p0->field_([0-9a-f]+) = 0;", src)))
    cands = [f for f in zeros if re.search(r"^\s+int field_%s\b" % f, src, re.M)]
    print(addr, len(cands), "int fields stored zero", flush=True)
    best = None
    for k in range(1, a.max + 1):
        for sub in itertools.combinations(cands, k):
            t = src
            for f in sub:
                t = re.sub(r"^(\s+)int (field_%s\b)" % f, r"\1float \2", t, flags=re.M)
                t = t.replace("p0->field_%s = 0;" % f, "p0->field_%s = 0.0f;" % f)
            path = _os.path.join(WORK, "float_try.cpp")
            open(path, "w", encoding="utf-8", newline="\n").write(t)
            args = [sys.executable, "-B", "-I", _os.path.join(S3, "try.py"), path, addr, symjson, "--ctx", "0", "--work", WORK]
            if name:
                args += ["--name", name]
            r = subprocess.run(args, capture_output=True, text=True)
            m = re.search(r"instr diff count (\d+)", r.stdout)
            n = int(m.group(1)) if m else None
            if n is not None and (best is None or n < best[0]):
                best = (n, sub)
            if "MATCH" in r.stdout.split("\n"):
                open(match_path, "w", encoding="utf-8", newline="\n").write(t)
                print(addr, "MATCH with float:", " ".join("+" + f for f in sub), flush=True)
                return True
    print(addr, "no match; best", best, flush=True)
    return False


if a.list:
    hits = 0
    for line in open(a.list, encoding="utf-8"):
        p = line.split()
        if len(p) >= 3:
            hits += search(p[1], p[0], p[2], p[3] if len(p) > 3 else None, _os.path.join(WORK, f"float_match_{p[0]}.cpp"))
    print("matched", hits)
    sys.exit(0 if hits else 1)
sys.exit(0 if search(a.cpp, a.addr, a.symjson, a.name, _os.path.join(WORK, "float_match.cpp")) else 1)
