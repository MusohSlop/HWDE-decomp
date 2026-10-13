"""Rank unattempted functions as matching targets.

For each function still marked `U` in data/functions.csv (and at most --max-size bytes), this
disassembles the original and reports:
  size      bytes
  calls     distinct direct call targets (bl)
  named     how many of those already have a name in data/units.json
  caller    whether an already matched (`O`) function calls it
  near      distance in KiB to the closest function that belongs to a unit
The score favours small functions whose callees are known, that matched code calls, and that sit
near existing units. Run: python -B tools/rank_targets.py [--max-size N] [--top N]
"""
import argparse
import csv
import json
import sys
from pathlib import Path

MATCHING = Path(__file__).resolve().parents[1]
ROOT = MATCHING.parent
sys.path.insert(0, str(ROOT / ".tools/python"))
import capstone  # noqa: E402

BASE = 0x7100000000


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--max-size", type=int, default=600)
    parser.add_argument("--top", type=int, default=40)
    args = parser.parse_args()

    image = (ROOT / "analysis/extracted/update/decompressed/main.memory.bin").read_bytes()
    with (MATCHING / "data/functions.csv").open(newline="") as f:
        rows = list(csv.DictReader(f))
    manifest = json.loads((MATCHING / "data/units.json").read_text(encoding="utf-8-sig"))

    named = set()
    for name, text in manifest["symbols"].items():
        if not name.startswith("got:"):
            named.add(int(text, 16) - BASE)
    unit_addrs = []
    for spec in manifest["units"].values():
        for text in spec["functions"].values():
            addr = int(text, 16) - BASE
            named.add(addr)
            unit_addrs.append(addr)
    unit_addrs.sort()

    md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)

    def targets(addr, size):
        return [int(i.op_str[1:], 16) for i in md.disasm(image[addr:addr + size], addr)
                if i.mnemonic == "bl" and i.op_str.startswith("#")]

    called_by_matched = set()
    for row in rows:
        if row["Quality"] == "O":
            addr = int(row["Address"], 16) - BASE
            called_by_matched.update(targets(addr, int(row["Size"])))

    def distance(addr):
        import bisect
        i = bisect.bisect_left(unit_addrs, addr)
        best = min((abs(unit_addrs[j] - addr) for j in (i - 1, i) if 0 <= j < len(unit_addrs)),
                   default=1 << 40)
        return best

    results = []
    for row in rows:
        if row["Quality"] != "U":
            continue
        size = int(row["Size"])
        if size > args.max_size or size < 8:
            continue
        addr = int(row["Address"], 16) - BASE
        calls = set(targets(addr, size))
        known = len(calls & named)
        ratio = known / len(calls) if calls else 1.0
        caller = addr in called_by_matched
        near = distance(addr) / 1024
        score = 2.0 * ratio + (1.0 if caller else 0.0) + (1.0 if near < 64 else 0.0) - size / 400
        results.append((score, addr, size, len(calls), known, caller, near))

    results.sort(reverse=True)
    print(f"{'score':>6} {'address':>10} {'size':>5} {'calls':>5} {'named':>5} caller {'near KiB':>8}")
    for score, addr, size, calls, known, caller, near in results[:args.top]:
        print(f"{score:6.2f} {addr:10x} {size:5d} {calls:5d} {known:5d} {'yes' if caller else '   ':>6} {near:8.0f}")
    print(f"\n{len(results)} unattempted functions up to {args.max_size} bytes.")


if __name__ == "__main__":
    main()
