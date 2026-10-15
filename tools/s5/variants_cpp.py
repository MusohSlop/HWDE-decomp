"""Compile source variants of one function and print the distance of each to the original.

usage: variants_cpp.py TEMPLATE ADDR SYM [--map NAME=ADDR ...] --slot KEY=opt1|opt2|... [--slot ...] [--work DIR]
                       [--limit N] [--show K]

TEMPLATE has {KEY} placeholders; every combination of the slots' options (`\\n` for a newline, `||` separates
options when an option itself holds a '|') is compiled with the unit flags and compared like tools/s5/sbs.py.
Prints one line per variant (abstract instruction diffs, instruction diffs, word diffs, the options), sorted, best
last, and MATCH for identical bytes. Stops at the first match (exit 0).
"""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
import os, sys, json, re, subprocess, difflib, argparse, itertools, csv
ROOT = os.path.dirname(M)
sys.path.insert(0, os.path.join(M, "tools"))
sys.path.insert(0, os.path.join(ROOT, ".tools", "python"))
sys.path.append(os.path.join(M, "tools", "gen"))
import capstone  # noqa
import check_obj, check  # noqa
import mm_tally  # noqa


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("template"); ap.add_argument("addr"); ap.add_argument("sym")
    ap.add_argument("--map", action="append", default=[]); ap.add_argument("--slot", action="append", default=[])
    ap.add_argument("--work"); ap.add_argument("--limit", type=int, default=100000)
    ap.add_argument("--show", type=int, default=30)
    a = ap.parse_args()
    addr = int(a.addr, 16) & 0xffffffff
    work = a.work or os.path.join(M, "build", "s5", "var")
    os.makedirs(work, exist_ok=True)
    man = json.load(open(os.path.join(M, "data", "units.json"), encoding="utf-8-sig"))
    cc = os.path.join(ROOT, man["compiler"])
    mapping = dict(check.collect_externals(man))
    for u in man["units"].values():
        for n, v in u.get("functions", {}).items():
            mapping.setdefault(n, check.address(v))
    for x in a.map:
        n, v = x.split("=")
        mapping[n] = check.address(v)
    mapping.setdefault(".rodata.cst4", 0x73b000)
    mapping.setdefault(".rodata.cst16", 0x73dff0)
    mapping[a.sym] = addr
    sizes = {check.address(r["Address"]): int(r["Size"]) for r in csv.DictReader(open(os.path.join(M, "data", "functions.csv"), newline=""))}
    image = check_obj.IMAGE.read_bytes()
    orig = image[addr: addr + sizes[addr]]
    md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
    oi = [f"{i.mnemonic} {i.op_str}" for i in md.disasm(orig, 0x7100000000 + addr)]
    _ab = lambda s: re.sub(r"#0x7100[0-9a-f]+|#0x[0-9a-f]{5,}", "#ADDR", re.sub(r"\b([xwqsdvbh])(\d+|zr)\b", r"\1", s))
    oa = [_ab(x) for x in oi]
    tmpl = open(a.template, encoding="utf-8").read()
    keys, opts = [], []
    for s in a.slot:
        k, v = s.split("=", 1)
        keys.append(k)
        opts.append([o.replace("\\n", "\n") for o in (v.split("||") if "||" in v else v.split("|"))])
    res = []
    for n, combo in enumerate(itertools.product(*opts)):
        if n >= a.limit:
            break
        src = tmpl
        for k, o in zip(keys, combo):
            src = src.replace("{" + k + "}", o)
        cpp, obj = os.path.join(work, "var.cpp"), os.path.join(work, "var.o")
        open(cpp, "w", encoding="utf-8").write(src)
        r = subprocess.run([cc, *man["flags"], "-I", os.path.join(M, "include"), "-c", cpp, "-o", obj], capture_output=True, text=True)
        if r.returncode:
            print("compile error for", combo, r.stderr[-600:])
            continue
        mine = mm_tally.mine_bytes(obj, a.sym, addr, mapping, image)
        mi = [f"{i.mnemonic} {i.op_str}" for i in md.disasm(mine, 0x7100000000 + addr)]
        ma = [_ab(x) for x in mi]
        sm = difflib.SequenceMatcher(None, ma, oa, autojunk=False)
        nab = max(len(ma), len(oa)) - sum(b.size for b in sm.get_matching_blocks())
        sm = difflib.SequenceMatcher(None, mi, oi, autojunk=False)
        nd = max(len(mi), len(oi)) - sum(b.size for b in sm.get_matching_blocks())
        wd = sum(1 for k in range(0, min(len(mine), len(orig)), 4) if mine[k:k + 4] != orig[k:k + 4]) + abs(len(mine) - len(orig)) // 4
        res.append((nab, nd, wd, combo))
        if mine == orig:
            open(os.path.join(work, "match.cpp"), "w", encoding="utf-8").write(src)
            print("MATCH", combo)
            return 0
    res.sort(key=lambda r: (r[0], r[1], r[2]))
    for r in res[:a.show][::-1]:
        print(r[0], r[1], r[2], " | ".join(c.replace("\n", " / ")[:60] for c in r[3]))
    return 1


if __name__ == "__main__":
    sys.exit(main())
