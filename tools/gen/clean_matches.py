"""Which functions of an already built unit match exactly with every relocation resolved.
usage: clean_matches.py UNIT  -> prints one hex address per clean match (the unit must have been built by check.py)."""
import os as _os
GENDIR = _os.path.dirname(_os.path.abspath(__file__))
MATCHDIR = _os.path.dirname(_os.path.dirname(GENDIR))
ROOTDIR = _os.path.dirname(MATCHDIR)
import csv, json, sys
M = MATCHDIR
sys.path.insert(0, M + r"\tools")
import check_obj, check
unit = sys.argv[1]
manifest = json.loads(open(M + r"\data\units.json", encoding="utf-8-sig").read())
spec = manifest["units"][unit]
mapping = dict(check.collect_externals(manifest))
mapping.update({n: check.address(a) for n, a in spec.get("map", {}).items()})
pairs = [(n, check.address(a)) for n, a in spec["functions"].items()]
for n, a in pairs:
    mapping.setdefault(n, a)
sizes = {check.address(r["Address"]): int(r["Size"]) for r in csv.DictReader(open(M + r"\data\functions.csv", newline=""))}
obj = M + "\\build\\" + unit.replace("/", "_").rsplit(".", 1)[0] + ".o"
for n, a in pairs:
    results, unresolved = check_obj.compare(obj, [(n, a)], mapping)
    name, addr, size, diffs, lines = results[0]
    if diffs is not None and not diffs and not unresolved and sizes.get(addr) == size:
        print("%x" % addr)
