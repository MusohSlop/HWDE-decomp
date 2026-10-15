"""Merge two versions of matching/data/units.json: start from OURS and add every symbol and unit from THEIRS.
A symbol or unit function that both define with different values is an error (nothing is written).
With BASE (the common ancestor's version), entries THEIRS deleted and OURS left unchanged are deleted too, so a
function moved from one unit to another (or a unit removed) on the other branch merges cleanly, and a unit entry
(a section map, a function's address) one side changed and the other left at its base value takes the change.
usage: merge_units.py OURS THEIRS OUT [BASE]"""
import json, sys
ours = json.load(open(sys.argv[1], encoding="utf-8-sig"))
theirs = json.load(open(sys.argv[2], encoding="utf-8-sig"))
base = json.load(open(sys.argv[4], encoding="utf-8-sig")) if len(sys.argv) > 4 else None
conflicts = []
for k, v in theirs.items():
    if k not in ("symbols", "units") and ours.get(k) != v:
        conflicts.append(f"top-level {k}")
if base is not None:
    # deletions on THEIRS side of entries OURS did not touch
    for n, a in base["symbols"].items():
        if n not in theirs["symbols"] and ours["symbols"].get(n) == a:
            del ours["symbols"][n]
    for un, spec in base["units"].items():
        if un not in theirs["units"]:
            if ours["units"].get(un) == spec:
                del ours["units"][un]
            continue
        for part in ("map", "functions"):
            for n, a in spec.get(part, {}).items():
                if n not in theirs["units"][un].get(part, {}) and ours["units"].get(un, {}).get(part, {}).get(n) == a:
                    del ours["units"][un][part][n]
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
                was = (base or {}).get("units", {}).get(un, {}).get(part, {}).get(n)
                if base is not None and was == a:
                    continue  # THEIRS kept the base value and OURS changed it: keep ours
                if base is not None and was == have:
                    mine[part][n] = a  # OURS kept the base value and THEIRS changed it: take theirs
                    continue
                conflicts.append(f"{un} {part} {n}: {have} vs {a}")
            mine[part].setdefault(n, a)
    for k, v in spec.items():
        if k not in ("map", "functions"):
            mine.setdefault(k, v)
# a function address may belong to one unit only
owners = {}
for un, spec in ours["units"].items():
    for n, a in spec.get("functions", {}).items():
        if (n, a) in owners and owners[(n, a)] != un:
            conflicts.append(f"{n} ({a}) in both {owners[(n, a)]} and {un}")
        owners[(n, a)] = un
if conflicts:
    print("conflicts:\n  " + "\n  ".join(conflicts))
    sys.exit(1)
open(sys.argv[3], "w", encoding="utf-8", newline="\n").write(json.dumps(ours, indent=2) + "\n")
print("merged:", len(ours["symbols"]), "symbols,", len(ours["units"]), "units")
