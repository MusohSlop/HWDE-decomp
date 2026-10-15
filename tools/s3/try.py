"""Compile one scratch cpp and diff one function against the original.

usage: try.py CPP ADDR [SYMJSON] [--name SYM] [--map NAME=ADDR ...] [--all] [--ctx N] [--work DIR]
Placeholder externals (callee_XXXX etc.) resolve from their address suffix, symbols from SYMJSON
(gen.py SYMOUT format) and units.json. Prints the difflib opcodes with instructions.
"""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
WORK = _os.path.join(M, "build", "s3")  # scratch files
_os.makedirs(WORK, exist_ok=True)
import os, sys, json, re, subprocess, difflib, argparse
ROOT = os.path.dirname(M)
GENDIR = os.path.join(M, "tools", "gen")
sys.path.insert(0, os.path.join(M, "tools"))
sys.path.insert(0, os.path.join(ROOT, ".tools", "python"))
import capstone  # noqa
import check_obj, check  # noqa
sys.path.append(GENDIR)
import mm_tally  # noqa
import csv

ap = argparse.ArgumentParser()
ap.add_argument("cpp"); ap.add_argument("addr"); ap.add_argument("symjson", nargs="?")
ap.add_argument("--name"); ap.add_argument("--all", action="store_true"); ap.add_argument("--ctx", type=int, default=2)
ap.add_argument("--map", action="append", default=[])
ap.add_argument("--work", help="folder for the object file (default build/s3)")
a = ap.parse_args()
addr = int(a.addr, 16) & 0xffffffff
man = json.load(open(os.path.join(M, "data", "units.json"), encoding="utf-8-sig"))
os.makedirs(a.work or WORK, exist_ok=True)
obj = os.path.join(a.work or WORK, os.path.splitext(os.path.basename(a.cpp))[0] + ".o")
c = subprocess.run([os.path.join(ROOT, man["compiler"]), *man["flags"], "-I", os.path.join(M, "include"), "-c", a.cpp, "-o", obj],
                   capture_output=True, text=True)
if c.returncode:
    print(c.stderr[-3000:]); sys.exit(1)
mapping = dict(check.collect_externals(man))
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


def placeholder_address(name):
    """The address suffix of a placeholder name (callee_X, Class_X, ...). For a mangled free function the
    identifier is cut at its length prefix, so a parameter code after the address (callee_33840cl) is not read
    as part of it."""
    mm = re.match(r"_Z(\d+)", name)
    if mm:
        ident = name[mm.end():mm.end() + int(mm.group(1))]
        mi = re.search(r"_([0-9a-f]{5,6})$", ident)
        if mi:
            return int(mi.group(1), 16)
    mm = re.search(r"_([0-9a-f]{5,6})(?=[A-Z]|$|E|P|v|i|f)", name)
    return int(mm.group(1), 16) if mm else None


for s in symbols:
    va = placeholder_address(s.name) if not s.is_section and s.shndx == 0 else None
    if va is not None and s.name not in mapping:
        mapping[s.name] = va
defined = [s.name for s in symbols if not s.is_section and s.shndx != 0 and s.size]
name = a.name or next((d for d in defined if re.search(r"_0*%x(?![0-9a-f])" % addr, d)), None)
mapping.setdefault(name, addr)
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
fi = lambda i: f"{i.mnemonic} {i.op_str}"
mi = [fi(i) for i in md.disasm(mine, 0x7100000000 + addr)]
oi = [fi(i) for i in md.disasm(orig, 0x7100000000 + addr)]
# unresolved relocations
res, unres = check_obj.compare(obj, [(name, addr)], mapping)
print(f"{name}: ours {len(mine)} bytes, orig {size}; word diffs {len(res[0][3]) if res[0][3] is not None else None}")
if unres:
    print("UNRESOLVED:", ", ".join(sorted(unres)))
sm = difflib.SequenceMatcher(None, mi, oi, autojunk=False)
nd = max(len(mi), len(oi)) - sum(b.size for b in sm.get_matching_blocks())
print("instr diff count", nd)
_ab = lambda s: re.sub(r"#0x7100[0-9a-f]+|#0x[0-9a-f]{5,}", "#ADDR", re.sub(r"\b([xwqsdvbh])(\d+|zr)\b", r"\1", s))
_ma, _oa = [_ab(x) for x in mi], [_ab(x) for x in oi]
_sma = difflib.SequenceMatcher(None, _ma, _oa, autojunk=False)
print("abstract diff count", max(len(_ma), len(_oa)) - sum(b.size for b in _sma.get_matching_blocks()))
if mine == orig and not unres:
    print("MATCH")
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    if tag == "equal":
        if a.all:
            for k in range(i1, i2):
                print(f"  {k*4:5x}   {mi[k]}")
        continue
    lo = max(0, i1 - a.ctx)
    for k in range(lo, i1):
        print(f"  {k*4:5x}   {mi[k]}")
    print(f"  --- {tag} ours[{i1}:{i2}] orig[{j1}:{j2}]")
    for k in range(i1, i2):
        print(f"  {k*4:5x} - {mi[k]}")
    for k in range(j1, j2):
        print(f"  {k*4:5x} + {oi[k]}")
