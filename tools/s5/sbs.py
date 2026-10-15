"""Compile one scratch cpp and print a side-by-side diff of one function against the original.

usage: sbs.py CPP ADDR [SYMJSON] [--name SYM] [--map NAME=ADDR ...] [--all] [--ctx N] [--width W] [--abs]
Symbols resolve as in tools/s3/try.py (units.json, SYMJSON, --map, and placeholder names ending in _<hex address>).
Prints the instruction diff counts, MATCH for identical bytes, then ours | orig rows ('|' equal, '*' differing,
'<' only ours, '>' only orig), each run of equal rows outside the context collapsed (all of it with --all).
--abs compares with register numbers and large immediates abstracted (shows scheduling and size problems only).
"""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
import os, sys, json, re, subprocess, difflib, argparse, csv
ROOT = os.path.dirname(M)
GENDIR = os.path.join(M, "tools", "gen")
sys.path.insert(0, os.path.join(M, "tools"))
sys.path.insert(0, os.path.join(ROOT, ".tools", "python"))
import capstone  # noqa
import check_obj, check  # noqa
sys.path.append(GENDIR)
import mm_tally  # noqa

ap = argparse.ArgumentParser()
ap.add_argument("cpp"); ap.add_argument("addr"); ap.add_argument("symjson", nargs="?")
ap.add_argument("--name"); ap.add_argument("--all", action="store_true"); ap.add_argument("--ctx", type=int, default=2)
ap.add_argument("--map", action="append", default=[]); ap.add_argument("--width", type=int, default=44)
ap.add_argument("--abs", action="store_true"); ap.add_argument("--obj")
a = ap.parse_args()
addr = int(a.addr, 16) & 0xffffffff
man = json.load(open(os.path.join(M, "data", "units.json"), encoding="utf-8-sig"))
obj = a.obj or os.path.splitext(a.cpp)[0] + ".o"
if not a.obj:
    c = subprocess.run([os.path.join(ROOT, man["compiler"]), *man["flags"], "-I", os.path.join(M, "include"), "-c", a.cpp,
                        "-o", obj], capture_output=True, text=True)
    if c.returncode:
        print(c.stderr[-3000:]); sys.exit(1)
mapping = dict(check.collect_externals(man))
for u in man["units"].values():
    for n, v in u.get("functions", {}).items():
        mapping.setdefault(n, check.address(v))
if a.symjson:
    sy = json.load(open(a.symjson, encoding="utf-8"))
    for x in sy["gsyms"] + sy["imports"]:
        n, v = x.split("=")
        mapping[n] = check.address(v)
    if sy.get("rodata"):
        mapping[".rodata"] = check.address(sy["rodata"])
for x in a.map:
    n, v = x.split("=")
    mapping[n] = check.address(v)
mapping[".rodata.cst4"] = 0x73b000
mapping[".rodata.cst16"] = 0x73dff0
data, sections, symbols, relocs = check_obj.read_elf(obj)
for s in symbols:
    mm = re.search(r"_([0-9a-f]{5,6})(?=[A-Z]|$|E|P|v|i|f)", s.name) if not s.is_section and s.shndx == 0 else None
    if mm and s.name not in mapping:
        mapping[s.name] = int(mm.group(1), 16)
defined = [s.name for s in symbols if not s.is_section and s.shndx != 0 and s.size]
name = a.name or next((d for d in defined if re.search(r"_0*%x(?![0-9a-f])" % addr, d)), None)
if name is None:
    sys.exit("no function named after %x in %s" % (addr, defined[:20]))
mapping[name] = addr
for s in symbols:  # other defined functions named after their address
    if not s.is_section and s.shndx != 0 and s.size and s.name not in mapping:
        mm = re.search(r"_([0-9a-f]{5,6})(?=[A-Z]|$|E|P|v|i|f)", s.name)
        if mm:
            mapping[s.name] = int(mm.group(1), 16)
sizes = {check.address(r["Address"]): int(r["Size"]) for r in csv.DictReader(open(os.path.join(M, "data", "functions.csv"), newline=""))}
size = sizes[addr]
image = check_obj.IMAGE.read_bytes()
mine = mm_tally.mine_bytes(obj, name, addr, mapping, image)
orig = image[addr: addr + size]
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
fi = lambda i: f"{i.mnemonic} {i.op_str}".replace("#0x7100", "#0x")
mi = [fi(i) for i in md.disasm(mine, 0x7100000000 + addr)]
oi = [fi(i) for i in md.disasm(orig, 0x7100000000 + addr)]
res, unres = check_obj.compare(obj, [(name, addr)], mapping)
print(f"{name}: ours {len(mine)} bytes, orig {size}; word diffs {len(res[0][3]) if res[0][3] is not None else None}")
if unres:
    print("UNRESOLVED:", ", ".join(sorted(unres)))
_ab = lambda s: re.sub(r"#0x[0-9a-f]{5,}", "#ADDR", re.sub(r"\b([xwqsdvbh])(\d+|zr)\b", r"\1", s))
ma, oa = [_ab(x) for x in mi], [_ab(x) for x in oi]
def nd(x, y):
    sm = difflib.SequenceMatcher(None, x, y, autojunk=False)
    return max(len(x), len(y)) - sum(b.size for b in sm.get_matching_blocks())
print("instr diff count", nd(mi, oi), " abstract diff count", nd(ma, oa))
if mine == orig and not unres:
    print("MATCH")
    sys.exit(0)
W = a.width
ka, kb = (ma, oa) if a.abs else (mi, oi)
sm = difflib.SequenceMatcher(None, ka, kb, autojunk=False)
rows = []
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    if tag == "equal":
        for k in range(i2 - i1):
            rows.append(("|", i1 + k, j1 + k))
    elif tag == "replace":
        n = max(i2 - i1, j2 - j1)
        for k in range(n):
            rows.append(("*", i1 + k if i1 + k < i2 else None, j1 + k if j1 + k < j2 else None))
    elif tag == "delete":
        for k in range(i1, i2):
            rows.append(("<", k, None))
    else:
        for k in range(j1, j2):
            rows.append((">", None, k))
show = [a.all or any(r[0] != "|" for r in rows[max(0, i - a.ctx): i + a.ctx + 1]) for i in range(len(rows))]
skipped = 0
for (t, i, j), sh in zip(rows, show):
    if not sh:
        skipped += 1
        continue
    if skipped:
        print("      ... %d equal" % skipped)
        skipped = 0
    l = ("%4x %s" % (i * 4, mi[i]))[:W] if i is not None else ""
    r = ("%4x %s" % (j * 4, oi[j]))[:W] if j is not None else ""
    if t == "|" and mi[i] != oi[j]:
        t = "~"   # equal only when abstracted
    print(f"{l:<{W}} {t} {r}")
if skipped:
    print("      ... %d equal" % skipped)
