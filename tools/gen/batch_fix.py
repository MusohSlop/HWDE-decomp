"""fixnames + autosym for many units in one process. usage: batch_fix.py UNIT [UNIT...]"""
import os as _os
GENDIR = _os.path.dirname(_os.path.abspath(__file__))
MATCHDIR = _os.path.dirname(_os.path.dirname(GENDIR))
ROOTDIR = _os.path.dirname(MATCHDIR)
import sys, json, re, subprocess, os
M = MATCHDIR
sys.path.insert(0, M + r"\tools")
import check_obj, check
P = M + r"\data\units.json"
py = sys.executable

def obj_of(unit):
    return M + "\\build\\" + unit.replace("/", "_").rsplit(".", 1)[0] + ".o"

units = sys.argv[1:]
# fixnames: rename the unit's function names that the object does not define to the defined symbol with the same address
text = open(P, encoding="utf-8").read()
m = json.loads(text)
syms = {}
for unit in units:
    if unit not in m["units"] or not os.path.exists(obj_of(unit)):
        continue
    data, sections, symbols, relocs = check_obj.read_elf(obj_of(unit))
    syms[unit] = symbols
    defined = [s.name for s in symbols if not s.is_section and s.shndx != 0 and s.name.startswith("_Z")]
    for name, addr in m["units"][unit]["functions"].items():
        if name in defined:
            continue
        suffix = "%x" % (int(addr, 16) & 0xFFFFFFFF)
        cands = [d for d in defined if re.search(r"_0*" + suffix + r"(?![0-9a-f])", d)]
        if len(cands) == 1:
            text = text.replace('"%s"' % name, '"%s"' % cands[0])
open(P, "w", encoding="utf-8", newline="\n").write(text)
# autosym: add undefined symbols whose identifier ends in _<hexaddr>
m = json.loads(text)
ext = check.collect_externals(m)
add = {}
for unit, symbols in syms.items():
    known = set(ext) | set(m["units"][unit].get("map", {}))
    for s in symbols:
        if s.is_section or s.shndx != 0 or not s.name or s.name in known or ("got:" + s.name) in known or s.name in add:
            continue
        addr = None
        pos = 2 if s.name.startswith("_Z") else 0
        if s.name.startswith("_ZN"):
            pos = 3
        while pos < len(s.name) and s.name[pos].isdigit():
            mm = re.match(r"\d+", s.name[pos:]); n = int(mm.group(0))
            ident = s.name[pos + len(mm.group(0)): pos + len(mm.group(0)) + n]
            h = re.search(r"_([0-9a-f]{3,6})$", ident)
            if h:
                addr = int(h.group(1), 16)
            pos += len(mm.group(0)) + n
        if addr is not None:
            add[s.name] = f"{s.name}=0x71{addr:08x}"
items = sorted(add.values())
for i in range(0, len(items), 200):
    subprocess.run([py, "-B", "-I", M + r"\tools\add_symbols.py", *items[i:i + 200]], cwd=M, capture_output=True)
print("fixed", len(syms), "units, added", len(items), "symbols")
