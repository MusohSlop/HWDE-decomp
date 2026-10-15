"""Compile matching units with the pinned compiler and compare them.

Usage: check.py [--update] [--diff] [UNIT ...]

Units, their functions and the original addresses of external symbols are
listed in matching/data/units.json. With no UNIT arguments every unit is
checked. A function matches only when its size equals the inventory size in
functions.csv and every word is equal after relocations are applied.

--update writes results to functions.csv: matches become O, a former O that
no longer matches becomes m, other qualities are kept. Names are set to the
compiled symbol. --diff prints instruction diffs for mismatches.
"""
import csv
import json
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import check_obj  # noqa: E402

ROOT = Path(__file__).resolve().parents[2]
MATCHING = ROOT / "matching"
UNITS = MATCHING / "data/units.json"
FUNCTIONS = MATCHING / "data/functions.csv"
BUILD = MATCHING / "build"


def address(text):
    return int(text, 16) & 0xFFFFFFFF


def unique_pairs(pairs):
    """object_pairs_hook that rejects a key repeated within one JSON object."""
    result = {}
    for key, value in pairs:
        if key in result:
            sys.exit(f"units.json: duplicate key {key!r}")
        result[key] = value
    return result


def collect_externals(manifest):
    """Names of known addresses; a name may not stand for two addresses."""
    externals = {}
    owners = {}

    def add(name, text, owner):
        value = address(text)
        if name in externals and externals[name] != value:
            sys.exit(f"units.json: {name} is {hex(externals[name])} in {owners[name]} "
                     f"but {hex(value)} in {owner}")
        externals[name] = value
        owners[name] = owner

    for name, text in manifest["symbols"].items():
        add(name, text, "symbols")
    # Functions of every unit are known addresses for calls between units.
    for unit, spec in manifest["units"].items():
        for name, text in spec["functions"].items():
            add(name, text, unit)
    return externals


def main():
    args = sys.argv[1:]
    update = "--update" in args
    show_diff = "--diff" in args
    selected = [a for a in args if not a.startswith("--")]

    manifest = json.loads(UNITS.read_text(encoding="utf-8-sig"), object_pairs_hook=unique_pairs)
    compiler = ROOT / manifest["compiler"]
    flags = manifest["flags"]
    externals = collect_externals(manifest)

    with FUNCTIONS.open(newline="") as f:
        rows = list(csv.DictReader(f))
    by_address = {address(r["Address"]): r for r in rows}

    units = manifest["units"]
    unknown = [u for u in selected if u not in units]
    if unknown:
        sys.exit(f"unknown units: {', '.join(unknown)}")

    BUILD.mkdir(exist_ok=True)
    matched = total = failed_compiles = 0
    for unit in selected or units:
        spec = units[unit]
        source = MATCHING / "src" / unit
        obj = BUILD / (unit.replace("/", "_").rsplit(".", 1)[0] + ".o")
        cmd = [str(compiler), *flags, "-I", str(MATCHING / "include"), "-c", str(source), "-o", str(obj)]
        proc = subprocess.run(cmd, capture_output=True, text=True)
        if proc.returncode != 0:
            print(f"{unit}: COMPILE FAILED\n{proc.stderr}")
            failed_compiles += 1
            continue
        mapping = dict(externals)
        mapping.update({n: address(a) for n, a in spec.get("map", {}).items()})
        pairs = [(n, address(a)) for n, a in spec["functions"].items()]
        results, unresolved = check_obj.compare(obj, pairs, mapping)
        print(f"{unit}:")
        for name, addr, size, diffs, lines in results:
            total += 1
            row = by_address.get(addr)
            expected = int(row["Size"]) if row else None
            ok = diffs == [] and (expected is None or size == expected)
            if ok:
                status = "MATCH"
                matched += 1
            elif diffs is None:
                status = "MISSING"
            elif diffs == []:
                status = f"SIZE MISMATCH ({size} bytes, original {expected})"
            else:
                status = f"MISMATCH ({len(diffs)} of {size // 4} words; original {expected} bytes)"
            print(f"  {addr:x} {name}: {status}")
            if show_diff and not ok:
                for line in lines:
                    print("  " + line)
            if update and row and diffs is not None:
                if ok:
                    row["Quality"] = "O"
                elif row["Quality"] == "O":
                    print(f"  warning: {addr:x} was O and no longer matches; set to m")
                    row["Quality"] = "m"
                elif row["Quality"] == "U":
                    row["Quality"] = "m"  # attempted, compiles, does not match yet
                row["Name"] = name
        if unresolved:
            print("  unresolved relocations (masked):", ", ".join(sorted(unresolved)))

    if update:
        with FUNCTIONS.open("w", newline="") as f:
            writer = csv.DictWriter(f, fieldnames=["Address", "Quality", "Size", "Name"], lineterminator="\n")
            writer.writeheader()
            writer.writerows(rows)

    done = [r for r in rows if r["Quality"] == "O"]
    print(f"\n{matched} of {total} checked functions match.")
    print(f"functions.csv: {len(done)} of {len(rows)} functions, "
          f"{sum(int(r['Size']) for r in done)} of {sum(int(r['Size']) for r in rows)} bytes matched.")
    sys.exit(1 if failed_compiles or matched != total else 0)


if __name__ == "__main__":
    main()
