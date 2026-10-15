"""ordtry.py CPP ADDR SYMJSON [--name SYM] [--limit N] [--work DIR]: for a generated function whose body is
straight-line (one statement per line, no branches or loops), try orders of its statements: calls keep their
order and the statements between two calls are permuted, a statement that uses a local after the one that sets
it. Stops at a match (DIR/ord_match.cpp; DIR defaults to build/s3), at most N orders (default 5000). Exit code 0
on a match, 1 without, 2 when the body is not straight-line.

ordtry.py --list FILE [--limit N] [--work DIR]: the same for each line 'ADDR CPP SYMJSON [SYM]' of FILE; matches
go to DIR/ord_match_ADDR.cpp. Exit code 0 when at least one matched."""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
import sys, re, subprocess, itertools, argparse
S3 = _os.path.dirname(_os.path.abspath(__file__))
ap = argparse.ArgumentParser()
ap.add_argument("cpp", nargs="?"); ap.add_argument("addr", nargs="?"); ap.add_argument("symjson", nargs="?")
ap.add_argument("--name"); ap.add_argument("--limit", type=int, default=5000); ap.add_argument("--list")
ap.add_argument("--work", default=_os.path.join(M, "build", "s3"))
a = ap.parse_args()
WORK = _os.path.abspath(a.work)
_os.makedirs(WORK, exist_ok=True)
CALL = re.compile(r"\bcallee\d*_[0-9a-f]+\(|->slot_\d+\(|\)\)\(|\bmemset\(")


def orders_of(seg):
    """Orders of a segment's lines in which each line using a local comes after the line defining it."""
    defs = {}
    for k, l in enumerate(seg):
        m = re.match(r"\s*[\w:<>\*\s]+?\**\s*\b([a-z]\d+)\s*=", l)
        if m and not l.strip().startswith("p0->"):
            defs[m.group(1)] = k
    deps = [{defs[v] for v in re.findall(r"\b([a-z]\d+)\b", l) if v in defs and defs[v] != k} for k, l in enumerate(seg)]
    out = []

    def rec(done, cur):
        if len(out) >= a.limit:
            return
        if len(cur) == len(seg):
            out.append(list(cur)); return
        for k in range(len(seg)):
            if k not in done and deps[k] <= done:
                done.add(k); cur.append(k); rec(done, cur); done.discard(k); cur.pop()
    rec(set(), [])
    return out


def search(cpp, addr, symjson, name, match_path):
    src = open(cpp, encoding="utf-8").read()
    fa = int(addr, 16) & 0xffffffff
    m = re.search(r"(// 0x71%08x[^\n]*\n[^\n]*\bcall_%x\([^)]*\) \{\n)(.*?)(\n\}\n)" % (fa, fa), src, re.S)
    if not m:
        print(addr, "function not found", flush=True); return None
    body = m.group(2).split("\n")
    if any(re.search(r"\b(if|do|while|for|switch)\b|[{}]", l) for l in body):
        print(addr, "not straight-line", flush=True); return None
    tail = []
    while body and re.match(r"\s*return\b", body[-1]):
        tail.insert(0, body.pop())
    segs, cur = [], []
    for l in body:
        if CALL.search(l):
            segs.append(cur); segs.append([l]); cur = []
        else:
            cur.append(l)
    segs.append(cur)
    per = [orders_of(s) if len(s) > 1 else [list(range(len(s)))] for s in segs]
    n = 0
    best = None
    for combo in itertools.product(*per):
        if n >= a.limit:
            break
        n += 1
        lines = [segs[i][k] for i, o in enumerate(combo) for k in o] + tail
        t = src[:m.start(2)] + "\n".join(lines) + src[m.end(2):]
        path = _os.path.join(WORK, "ord_try.cpp")
        open(path, "w", encoding="utf-8", newline="\n").write(t)
        args = [sys.executable, "-B", "-I", _os.path.join(S3, "try.py"), path, addr, symjson, "--ctx", "0", "--work", WORK]
        if name:
            args += ["--name", name]
        r = subprocess.run(args, capture_output=True, text=True)
        mm = re.search(r"instr diff count (\d+)", r.stdout)
        d = int(mm.group(1)) if mm else None
        if d is not None and (best is None or d < best):
            best = d
        if "MATCH" in r.stdout.split("\n"):
            open(match_path, "w", encoding="utf-8", newline="\n").write(t)
            print(addr, "MATCH after", n, "orders", flush=True)
            return True
    print(addr, "no match in", n, "orders; best", best, flush=True)
    return False


if a.list:
    hits = 0
    for line in open(a.list, encoding="utf-8"):
        p = line.split()
        if len(p) >= 3:
            hits += bool(search(p[1], p[0], p[2], p[3] if len(p) > 3 else None, _os.path.join(WORK, f"ord_match_{p[0]}.cpp")))
    print("matched", hits)
    sys.exit(0 if hits else 1)
r = search(a.cpp, a.addr, a.symjson, a.name, _os.path.join(WORK, "ord_match.cpp"))
sys.exit(0 if r else (2 if r is None else 1))
