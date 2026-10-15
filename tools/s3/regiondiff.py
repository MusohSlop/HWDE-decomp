"""regiondiff.py OURS.s ORIG.s START_PATTERN [END_PATTERN]: difflib side by side of two disassembly listings
(as written by ours.py and tools/gen/dis.py) from the first line matching START_PATTERN (a regex on the
instruction text) to END_PATTERN or the end, with registers kept."""
import re, sys, difflib
def load(p):
    out = []
    for l in open(p, encoding="utf-8", errors="replace"):
        m = re.match(r"\s+([0-9a-f]+)\s+(\S.*)$", l.rstrip())
        if m and not l.startswith("=="):
            out.append((m.group(1), re.sub(r"#0x71([0-9a-f]{8})", lambda x: "#0x%x" % int(x.group(1), 16), m.group(2)).strip()))
    return out
a, b = load(sys.argv[1]), load(sys.argv[2])
def cut(lst):
    s = next((k for k, (_, t) in enumerate(lst) if re.search(sys.argv[3], t)), 0)
    e = len(lst)
    if len(sys.argv) > 4 and not sys.argv[4].startswith("--"):
        e = next((k for k, (_, t) in enumerate(lst) if k > s and re.search(sys.argv[4], t)), len(lst))
    return lst[s:e]
a, b = cut(a), cut(b)
ABS = "--abs" in sys.argv
def norm(t):
    t = re.sub(r"#0x[0-9a-f]{5,}", "#ADDR", t)
    return re.sub(r"\b([xwqsdvbh])(\d+|zr)\b", r"\1", t) if ABS else t
ta = [norm(t) for _, t in a]
tb = [norm(t) for _, t in b]
sm = difflib.SequenceMatcher(None, ta, tb, autojunk=False)
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    if tag == "equal":
        print(f"   = {i2 - i1} equal ({a[i1][0]} / {b[j1][0]})")
        continue
    n = max(i2 - i1, j2 - j1)
    for k in range(n):
        x = f"{a[i1 + k][0]} {ta[i1 + k]}" if i1 + k < i2 else ""
        y = f"{b[j1 + k][0]} {tb[j1 + k]}" if j1 + k < j2 else ""
        print(f"   {x:48s} | {y}")
