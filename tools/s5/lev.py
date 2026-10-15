"""lev.py CPP ADDR SYM [--map NAME=ADDR ...] [--sbs [--regs]]: edit distances (insert, delete or replace one instruction) between a
scratch file's function and the original, with registers abstracted and exact. Unlike difflib's longest-block
alignment (sbs.py, variants), the edit distance cannot pair a block with a duplicate elsewhere in the function, so it
stays meaningful in functions with repeated code (two copies of the same inline loop). --sbs prints the aligned
listing around the abstract differences (* changed, < ours only, > original only); --regs also around register-only
differences (~). Also importable: lev.distance(a, b), lev.align(a, b)."""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
import os, sys, json, re, subprocess, csv
ROOT = os.path.dirname(M)


def distance(a, b):
    """Levenshtein distance between two sequences of hashable items (two-row DP)."""
    if len(a) < len(b):
        a, b = b, a
    prev = list(range(len(b) + 1))
    for i, x in enumerate(a, 1):
        cur = [i] + [0] * len(b)
        for j, y in enumerate(b, 1):
            c = prev[j - 1] + (x != y)
            d = prev[j] + 1
            if d < c:
                c = d
            d = cur[j - 1] + 1
            if d < c:
                c = d
            cur[j] = c
        prev = cur
    return prev[-1]


def align(a, b):
    """Edit-distance alignment of a and b: a list of (i, j) pairs, None for a gap."""
    n, m = len(a), len(b)
    D = [[0] * (m + 1) for _ in range(n + 1)]
    for i in range(n + 1):
        D[i][0] = i
    for j in range(m + 1):
        D[0][j] = j
    for i in range(1, n + 1):
        Di, Dp, x = D[i], D[i - 1], a[i - 1]
        for j in range(1, m + 1):
            c = Dp[j - 1] + (x != b[j - 1])
            d = Dp[j] + 1
            if d < c:
                c = d
            d = Di[j - 1] + 1
            if d < c:
                c = d
            Di[j] = c
    out = []
    i, j = n, m
    while i or j:
        if i and j and D[i][j] == D[i - 1][j - 1] + (a[i - 1] != b[j - 1]):
            out.append((i - 1, j - 1)); i -= 1; j -= 1
        elif i and D[i][j] == D[i - 1][j] + 1:
            out.append((i - 1, None)); i -= 1
        else:
            out.append((None, j - 1)); j -= 1
    return out[::-1]


ABSTRACT = lambda s: re.sub(r"#0x7100[0-9a-f]+|#0x[0-9a-f]{5,}", "#ADDR", re.sub(r"\b([xwqsdvbh])(\d+|zr)\b", r"\1", s))


def main():
    sys.path.insert(0, os.path.join(M, "tools"))
    sys.path.insert(0, os.path.join(ROOT, ".tools", "python"))
    sys.path.append(os.path.join(M, "tools", "gen"))
    import capstone  # noqa
    import check_obj, check  # noqa
    import mm_tally  # noqa
    args = sys.argv[1:]
    show = "--sbs" in args
    show_regs = "--regs" in args
    ctx = 2
    args = [a for a in args if a not in ("--sbs", "--regs")]
    maps = []
    while "--map" in args:
        i = args.index("--map")
        maps.append(args[i + 1])
        del args[i:i + 2]
    cpp, addr, sym = args[0], int(args[1], 16) & 0xffffffff, args[2]
    man = json.load(open(os.path.join(M, "data", "units.json"), encoding="utf-8-sig"))
    obj = os.path.join(M, "build", "s5", "lev.o")
    r = subprocess.run([os.path.join(ROOT, man["compiler"]), *man["flags"], "-I", os.path.join(M, "include"), "-c", cpp,
                        "-o", obj], capture_output=True, text=True)
    if r.returncode:
        sys.exit(r.stderr[-2000:])
    mapping = dict(check.collect_externals(man))
    for x in maps:
        n, v = x.split("=")
        mapping[n] = check.address(v)
    mapping.setdefault(".rodata.cst4", 0x73b000)
    mapping.setdefault(".rodata.cst16", 0x73dff0)
    mapping[sym] = addr
    sizes = {check.address(r["Address"]): int(r["Size"]) for r in csv.DictReader(open(os.path.join(M, "data", "functions.csv"), newline=""))}
    image = check_obj.IMAGE.read_bytes()
    orig = image[addr: addr + sizes[addr]]
    mine = mm_tally.mine_bytes(obj, sym, addr, mapping, image)
    md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
    mi = [f"{i.mnemonic} {i.op_str}" for i in md.disasm(mine, 0x7100000000 + addr)]
    oi = [f"{i.mnemonic} {i.op_str}" for i in md.disasm(orig, 0x7100000000 + addr)]
    ma, oa = [ABSTRACT(x) for x in mi], [ABSTRACT(x) for x in oi]
    print(f"{sym}: ours {len(mine)} bytes, orig {len(orig)}; edit distance abstract {distance(ma, oa)}, exact {distance(mi, oi)}")
    if show:
        pairs = align(ma, oa)
        marks = []
        for i, j in pairs:
            if i is None or j is None:
                marks.append("<" if j is None else ">")
            elif ma[i] != oa[j]:
                marks.append("*")
            elif mi[i] != oi[j]:
                marks.append("~")
            else:
                marks.append("|")
        keep = set()
        for k, mk in enumerate(marks):
            if mk in "<>*" or (show_regs and mk == "~"):
                keep.update(range(max(0, k - ctx), min(len(marks), k + ctx + 1)))
        last = -1
        for k in sorted(keep):
            if k != last + 1:
                print("      ...")
            last = k
            i, j = pairs[k]
            left = f"{i * 4:4x} {mi[i]}" if i is not None else ""
            right = f"{j * 4:4x} {oi[j]}" if j is not None else ""
            print(f"{left:42s} {marks[k]} {right}")


if __name__ == "__main__":
    main()
