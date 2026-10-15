"""irsbatch.py: run tools/s5/irsearch.py --groups over a list of near misses, one after another.

usage: irsbatch.py LIST [--iters N] --work DIR

LIST has one function per line (blank lines and # comments skipped):
    ADDR CPP [SYMS] [FUNC] [NAME=ADDR ...]
CPP is the scratch source (relative to matching/); irsearch.py emits its IR itself, with -g and use-list order kept.
SYMS is a converter/rank .json whose gsyms and imports become --map arguments ('-' for none). FUNC is the mangled
name ('-' or left out: the one defined function whose name contains ADDR). NAME=ADDR adds a --map.
Each function works in DIR/ADDR (its log in DIR/ADDR/log.txt); a match is copied to DIR/irs_match_ADDR.ll.
One summary line per function: start score, best score, exit. Exit 0 when any function matched, else 1.
Made to run unattended through bgsearch.py (idle priority); irsearch.py is the fifth session's tool, used as is.
"""
import argparse, json, os, re, shutil, subprocess, sys

M = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))  # the matching/ folder


def find_func(cpp, addr, work, man, cc):
    ll = os.path.join(work, "names.ll")
    r = subprocess.run([cc, *man["flags"], "-I", os.path.join(M, "include"), "-S", "-emit-llvm", os.path.join(M, cpp),
                        "-o", ll], capture_output=True, text=True)
    if r.returncode:
        return None
    defs = re.findall(r"^define [^@]*@(\S+)\(", open(ll, encoding="utf-8").read(), re.M)
    hit = [d for d in defs if re.search(r"(?<![0-9a-f])%s(?![0-9a-f])" % addr, d)]
    return hit[0] if len(hit) == 1 else None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("list"); ap.add_argument("--iters", default="3000"); ap.add_argument("--work", required=True)
    a = ap.parse_args()
    man = json.load(open(os.path.join(M, "data", "units.json"), encoding="utf-8-sig"))
    cc = os.path.join(os.path.dirname(M), man["compiler"])
    matched = False
    for line in open(a.list, encoding="utf-8"):
        f = line.split("#")[0].split()
        if not f:
            continue
        addr, cpp = f[0], f[1]
        syms = f[2] if len(f) > 2 and "=" not in f[2] else "-"
        func = f[3] if len(f) > 3 and "=" not in f[3] else "-"
        extra = [x for x in f[2:] if "=" in x]
        work = os.path.join(a.work, addr)
        os.makedirs(work, exist_ok=True)
        if func == "-":
            func = find_func(cpp, addr, work, man, cc)
            if not func:
                print(addr, "no single function named for", addr, flush=True)
                continue
        maps = []
        if syms != "-":
            sy = json.load(open(os.path.join(M, syms), encoding="utf-8"))
            maps = [x for x in sy.get("gsyms", []) + sy.get("imports", []) if x]
        args = []
        for x in maps + extra:
            args += ["--map", x]
        with open(os.path.join(work, "log.txt"), "w", encoding="utf-8") as log:
            r = subprocess.run([sys.executable, "-B", "-I", os.path.join(M, "tools", "s5", "irsearch.py"),
                                os.path.join(M, cpp), func, addr, *args, "--groups", "--iters", a.iters, "--work", work],
                               cwd=M, stdout=log, stderr=subprocess.STDOUT)
        o = open(os.path.join(work, "log.txt"), encoding="utf-8", errors="replace").read()
        st = re.search(r"^start (\(.*\))", o, re.M)
        bs = re.findall(r"^best (\(.*\))", o, re.M)
        hit = os.path.join(work, "match.ll")
        if r.returncode == 0 and os.path.exists(hit):
            shutil.copy(hit, os.path.join(a.work, "irs_match_%s.ll" % addr))
            matched = True
        print(addr, func, "exit", r.returncode, "start", st.group(1) if st else "?", "best", bs[-1] if bs else "?",
              flush=True)
    return 0 if matched else 1


if __name__ == "__main__":
    sys.exit(main())
