"""Add names to matching/data/units.json without remapping existing ones.

    add_symbols.py NAME=ADDRESS ...                  external symbols
    add_symbols.py --unit UNIT NAME=ADDRESS ...      functions of UNIT (created if new)
    add_symbols.py --map UNIT SECTION=ADDRESS ...    section anchors of UNIT

A name that already stands for a different address (in the symbols table or in
any unit) is refused, and nothing is written.
"""
import json
import sys
from pathlib import Path

UNITS = Path(__file__).resolve().parents[1] / "data/units.json"


def address(text):
    return int(text, 16) & 0xFFFFFFFF


def main():
    args = sys.argv[1:]
    unit = mapping = None
    if args[:1] == ["--unit"]:
        unit, args = args[1], args[2:]
    elif args[:1] == ["--map"]:
        mapping, args = args[1], args[2:]
    pairs = [a.split("=", 1) for a in args]
    if not pairs or any(len(p) != 2 for p in pairs):
        sys.exit(__doc__)

    manifest = json.loads(UNITS.read_text(encoding="utf-8-sig"))
    if mapping:
        manifest["units"][mapping].setdefault("map", {}).update(dict(pairs))
    else:
        known = {n: (a, "symbols") for n, a in manifest["symbols"].items()}
        for u, spec in manifest["units"].items():
            known.update({n: (a, u) for n, a in spec["functions"].items()})
        errors = [f"{n} is already {known[n][0]} in {known[n][1]}" for n, a in pairs
                  if n in known and address(known[n][0]) != address(a)]
        if errors:
            sys.exit("refused:\n  " + "\n  ".join(errors))
        if unit:
            target = manifest["units"].setdefault(unit, {"functions": {}})["functions"]
        else:
            target = manifest["symbols"]
        target.update({n: a for n, a in pairs})
    UNITS.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8", newline="\n")
    print(f"added {len(pairs)}")


if __name__ == "__main__":
    main()
