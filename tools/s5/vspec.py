"""Compile source variants described by a Python spec file and print each one's distance to the original.

usage: vspec.py SPEC.py [--show K] [--keep]

SPEC.py defines BASE (a scratch .cpp), ADDR (hex), SYM (the compiled symbol), MAPS (a list of NAME=ADDR) and
SLOTS, a list of (old_text, [option, ...]) pairs: old_text must occur exactly once in BASE and every combination
of the options replaces it. Options may hold any text (the command line of variants_cpp.py cannot carry `||`).
Optional: WORK (scratch folder, default build/s5/var). Prints abstract instruction diffs, instruction diffs and
word diffs per variant, best last, with the option indexes; stops at a match (WORK/match.cpp). --keep writes
every variant to WORK/vNNN.cpp.
"""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
import os, sys, json, re, subprocess, difflib, itertools, csv, runpy
ROOT = os.path.dirname(M)
sys.path.insert(0, os.path.join(M, "tools"))
sys.path.insert(0, os.path.join(ROOT, ".tools", "python"))
sys.path.append(os.path.join(M, "tools", "gen"))
import capstone  # noqa
import check_obj, check  # noqa
import mm_tally  # noqa


def main():
    args = sys.argv[1:]
    show = 30
    if "--show" in args:
        i = args.index("--show")
        show = int(args[i + 1])
        del args[i:i + 2]
    keep = "--keep" in args
    args = [a for a in args if a != "--keep"]
    spec = runpy.run_path(args[0])
    addr = int(spec["ADDR"], 16) & 0xffffffff
    work = spec.get("WORK") or os.path.join(M, "build", "s5", "var")
    os.makedirs(work, exist_ok=True)
    man = json.load(open(os.path.join(M, "data", "units.json"), encoding="utf-8-sig"))
    cc = os.path.join(ROOT, man["compiler"])
    mapping = dict(check.collect_externals(man))
    for u in man["units"].values():
        for n, v in u.get("functions", {}).items():
            mapping.setdefault(n, check.address(v))
    for x in spec.get("MAPS", []):
        n, v = x.split("=")
        mapping[n] = check.address(v)
    mapping.setdefault(".rodata.cst4", 0x73b000)
    mapping.setdefault(".rodata.cst16", 0x73dff0)
    sym = spec["SYM"]
    mapping[sym] = addr
    sizes = {check.address(r["Address"]): int(r["Size"]) for r in csv.DictReader(open(os.path.join(M, "data", "functions.csv"), newline=""))}
    image = check_obj.IMAGE.read_bytes()
    orig = image[addr: addr + sizes[addr]]
    md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
    oi = [f"{i.mnemonic} {i.op_str}" for i in md.disasm(orig, 0x7100000000 + addr)]
    _ab = lambda s: re.sub(r"#0x7100[0-9a-f]+|#0x[0-9a-f]{5,}", "#ADDR", re.sub(r"\b([xwqsdvbh])(\d+|zr)\b", r"\1", s))
    oa = [_ab(x) for x in oi]
    base = open(spec["BASE"], encoding="utf-8").read()
    for old, _ in spec["SLOTS"]:
        if base.count(old) != 1:
            sys.exit("slot text found %d times: %r" % (base.count(old), old[:80]))
    res = []
    combos = list(itertools.product(*[range(len(o)) for _, o in spec["SLOTS"]]))
    for n, combo in enumerate(combos):
        src = base
        for (old, opts), k in zip(spec["SLOTS"], combo):
            src = src.replace(old, opts[k])
        cpp, obj = os.path.join(work, "vs.cpp"), os.path.join(work, "vs.o")
        open(cpp, "w", encoding="utf-8").write(src)
        if keep:
            open(os.path.join(work, "v%03d.cpp" % n), "w", encoding="utf-8").write(src)
        r = subprocess.run([cc, *man["flags"], "-I", os.path.join(M, "include"), "-c", cpp, "-o", obj], capture_output=True, text=True)
        if r.returncode:
            print("compile error for", combo, r.stderr[-600:])
            continue
        mine = mm_tally.mine_bytes(obj, sym, addr, mapping, image)
        mi = [f"{i.mnemonic} {i.op_str}" for i in md.disasm(mine, 0x7100000000 + addr)]
        ma = [_ab(x) for x in mi]
        sm = difflib.SequenceMatcher(None, ma, oa, autojunk=False)
        nab = max(len(ma), len(oa)) - sum(b.size for b in sm.get_matching_blocks())
        sm = difflib.SequenceMatcher(None, mi, oi, autojunk=False)
        nd = max(len(mi), len(oi)) - sum(b.size for b in sm.get_matching_blocks())
        wd = sum(1 for k in range(0, min(len(mine), len(orig)), 4) if mine[k:k + 4] != orig[k:k + 4]) + abs(len(mine) - len(orig)) // 4
        res.append((nab, nd, wd, combo, len(mine)))
        if mine == orig:
            open(os.path.join(work, "match.cpp"), "w", encoding="utf-8").write(src)
            print("MATCH", combo)
            return 0
    res.sort(key=lambda r: (r[0], r[1], r[2]))
    for r in res[:show][::-1]:
        print(r[0], r[1], r[2], r[4], "options", " ".join(str(c) for c in r[3]))
    return 1


if __name__ == "__main__":
    sys.exit(main())
