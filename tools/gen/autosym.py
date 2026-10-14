# usage: autosym.py UNIT -> add missing undefined symbols whose identifier ends in _<hexaddr>
import os as _os
GENDIR = _os.path.dirname(_os.path.abspath(__file__))
MATCHDIR = _os.path.dirname(_os.path.dirname(GENDIR))
ROOTDIR = _os.path.dirname(MATCHDIR)
import sys, json, re, subprocess
sys.path.insert(0, (MATCHDIR + r"\tools"))
import check_obj, check
m = json.load(open((MATCHDIR + r"\data\units.json"), encoding="utf-8-sig"))
ext = check.collect_externals(m)
unit = sys.argv[1]
ext.update({k: 0 for k in m["units"][unit].get("map", {})})
obj = (MATCHDIR + r"\build\\") + unit.replace("/", "_").rsplit(".", 1)[0] + ".o"
data, sections, symbols, relocs = check_obj.read_elf(obj)
add = []
for s in symbols:
    if not s.is_section and s.shndx == 0 and s.name and s.name not in ext and ("got:" + s.name) not in ext:
        addr = None
        pos = 2 if s.name.startswith("_Z") else 0
        if s.name.startswith("_ZN"): pos = 3
        while pos < len(s.name) and s.name[pos].isdigit():
            mm = re.match(r"\d+", s.name[pos:]); n = int(mm.group(0)); ident = s.name[pos + len(mm.group(0)): pos + len(mm.group(0)) + n]
            h = re.search(r"_([0-9a-f]{3,6})$", ident)
            if h: addr = int(h.group(1), 16)
            pos += len(mm.group(0)) + n
        if addr is None:
            print("NO ADDRESS", s.name); continue
        add.append(f"{s.name}=0x71{addr:08x}")
if add:
    print("\n".join(add))
    subprocess.run([sys.executable, "-B", "-I", (MATCHDIR + r"\tools\add_symbols.py"), *add], cwd=MATCHDIR)
