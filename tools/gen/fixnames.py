# usage: fixnames.py UNIT -> rename the unit's function names that are missing from the built object
# to the defined object symbol carrying the same address suffix. Prints every rename.
import os as _os
GENDIR = _os.path.dirname(_os.path.abspath(__file__))
MATCHDIR = _os.path.dirname(_os.path.dirname(GENDIR))
ROOTDIR = _os.path.dirname(MATCHDIR)
import sys, json, re
sys.path.insert(0, (MATCHDIR + r"\tools"))
import check_obj
p = (MATCHDIR + r"\data\units.json")
text = open(p, encoding="utf-8").read()
m = json.loads(text)
unit = sys.argv[1]
obj = (MATCHDIR + r"\build\\") + unit.replace("/", "_").rsplit(".", 1)[0] + ".o"
data, sections, symbols, relocs = check_obj.read_elf(obj)
defined = [s.name for s in symbols if not s.is_section and s.shndx != 0 and s.name.startswith("_Z")]
for name, addr in m["units"][unit]["functions"].items():
    if name in defined: continue
    suffix = "%x" % (int(addr, 16) & 0xFFFFFFFF)
    cands = [d for d in defined if re.search(r"_0*" + suffix + r"(?![0-9a-f])", d)]
    if len(cands) == 1:
        print("rename", name, "->", cands[0])
        text = text.replace('"%s"' % name, '"%s"' % cands[0])
    else:
        print("unresolved", name, cands)
open(p, "w", encoding="utf-8", newline="\n").write(text)
