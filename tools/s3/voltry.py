"""voltry.py CPP ADDR SYMJSON [--max K] [--name SYM] [--work DIR]: mark struct fields of a generated (or
converted) source volatile, one subset at a time (up to K fields, default 2), and run try.py on each. A volatile
access keeps the machine scheduler from moving it past the function's other memory accesses (AArch64 only
reorders accesses it can prove disjoint, and never a volatile one), which is what some stores in the original
need. Stops at the first match, written to DIR/vol_match.cpp (DIR defaults to build/s3). Exit code 0 on a match,
1 without."""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
import sys, re, subprocess, itertools, argparse
S3 = _os.path.dirname(_os.path.abspath(__file__))
ap = argparse.ArgumentParser()
ap.add_argument("cpp"); ap.add_argument("addr"); ap.add_argument("symjson")
ap.add_argument("--max", type=int, default=2); ap.add_argument("--name")
ap.add_argument("--work", default=_os.path.join(M, "build", "s3"))
a = ap.parse_args()
WORK = _os.path.abspath(a.work)
_os.makedirs(WORK, exist_ok=True)
src = open(a.cpp, encoding="utf-8").read().split("\n")
# data members: indented 'type name;' lines inside a struct or class body, not functions or padding
fields = [i for i, l in enumerate(src)
          if re.match(r"^    (?!virtual|unsigned char pad)[A-Za-z_][\w:<>\*\s]*?[\s\*]+\w+(\[\w+\])?;", l) and "(" not in l]
print(len(fields), "fields")
best = None
for k in range(1, a.max + 1):
    for sub in itertools.combinations(fields, k):
        out = list(src)
        for i in sub:
            out[i] = "    volatile " + out[i][4:]
        path = _os.path.join(WORK, "vol_try.cpp")
        open(path, "w", encoding="utf-8").write("\n".join(out))
        args = [sys.executable, "-B", "-I", _os.path.join(S3, "try.py"), path, a.addr, a.symjson, "--ctx", "0", "--work", WORK]
        if a.name:
            args += ["--name", a.name]
        r = subprocess.run(args, capture_output=True, text=True)
        m = re.search(r"instr diff count (\d+)", r.stdout)
        n = int(m.group(1)) if m else None
        tag = " + ".join(src[i].strip() for i in sub)
        if n is not None and (best is None or n < best[0]):
            best = (n, tag)
        if "MATCH" in r.stdout.split("\n"):
            open(_os.path.join(WORK, "vol_match.cpp"), "w", encoding="utf-8").write("\n".join(out))
            print("MATCH with volatile:", tag)
            sys.exit(0)
print("no match; best", best)
sys.exit(1)
