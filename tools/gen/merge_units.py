"""Merge two versions of matching/data/units.json: start from OURS and add every symbol and unit from THEIRS.
A symbol or unit function that both define with different values is an error (nothing is written).
usage: merge_units.py OURS THEIRS OUT"""
import os as _os
GENDIR = _os.path.dirname(_os.path.abspath(__file__))
MATCHDIR = _os.path.dirname(_os.path.dirname(GENDIR))
ROOTDIR = _os.path.dirname(MATCHDIR)
import json, sys
ours = json.load(open(sys.argv[1], encoding="utf-8-sig"))
theirs = json.load(open(sys.argv[2], encoding="utf-8-sig"))
conflicts = []
for k, v in theirs.items():
    if k not in ("symbols", "units") and ours.get(k) != v:
        conflicts.append(f"top-level {k}")
for n, a in theirs["symbols"].items():
    if n in ours["symbols"] and ours["symbols"][n] != a:
        conflicts.append(f"symbol {n}: {ours['symbols'][n]} vs {a}")
    ours["symbols"].setdefault(n, a)
for un, spec in theirs["units"].items():
    mine = ours["units"].setdefault(un, {})
    for part in ("map", "functions"):
        for n, a in spec.get(part, {}).items():
            have = mine.setdefault(part, {}).get(n)
            if have is not None and have != a:
                conflicts.append(f"{un} {part} {n}: {have} vs {a}")
            mine[part].setdefault(n, a)
    for k, v in spec.items():
        if k not in ("map", "functions"):
            mine.setdefault(k, v)
if conflicts:
    print("conflicts:\n  " + "\n  ".join(conflicts))
    sys.exit(1)
open(sys.argv[3], "w", encoding="utf-8", newline="\n").write(json.dumps(ours, indent=2) + "\n")
print("merged:", len(ours["symbols"]), "symbols,", len(ours["units"]), "units")
