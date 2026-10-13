"""Group unattempted functions into families of identical code, relocations masked.

    family_scan.py [--min-size N] [--max-size N] [--top N] [--members N]

Each function's words are compared with every relocated field masked:
  - bl/b immediates whose target lies outside the function (calls, tail calls);
  - adrp immediates, and the 12-bit offsets of add/ldr/str instructions whose base
    register was last set by an adrp in the same function (GOT slots, globals, constants).
Branches inside the function are kept, so the control flow must agree.

Families are listed by total size (members x size). A family with a matched member
(status O in functions.csv) is marked "seed": the matched source covers the rest once
the relocated names are filled in. Output columns: total bytes, member count, size,
seed, then the first member addresses (U members first).
"""
import argparse
import csv
import struct
from collections import defaultdict
from pathlib import Path

MATCHING = Path(__file__).resolve().parents[1]
ROOT = MATCHING.parent
IMAGE = ROOT / "analysis/extracted/update/decompressed/main.memory.bin"
FUNCTIONS = MATCHING / "data/functions.csv"
BASE = 0x7100000000


def masked_words(data, start, size):
    words = []
    adrp_regs = set()
    for off in range(0, size, 4):
        w = struct.unpack_from("<I", data, start + off)[0]
        if (w & 0x7C000000) == 0x14000000:  # b / bl imm26
            imm = w & 0x3FFFFFF
            if imm & 0x2000000:
                imm -= 1 << 26
            target = off + imm * 4
            if not 0 <= target < size:
                w &= 0xFC000000
        elif (w & 0x9F000000) == 0x90000000:  # adrp
            adrp_regs.add(w & 0x1F)
            w &= 0x9F00001F
        elif (w & 0x7F800000) == 0x11000000 and ((w >> 5) & 0x1F) in adrp_regs:  # add imm
            w &= 0xFFC003FF
        elif (w & 0x3B000000) == 0x39000000 and ((w >> 5) & 0x1F) in adrp_regs:  # ldr/str imm12
            w &= 0xFFC003FF
        else:
            # Any other write to a tracked register ends its adrp association.
            rd = w & 0x1F
            if rd in adrp_regs and (w & 0x3B000000) != 0x39000000:
                adrp_regs.discard(rd)
        words.append(w)
    return tuple(words)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--min-size", type=int, default=16)
    parser.add_argument("--max-size", type=int, default=4096)
    parser.add_argument("--top", type=int, default=40)
    parser.add_argument("--members", type=int, default=6)
    args = parser.parse_args()

    data = IMAGE.read_bytes()
    families = defaultdict(list)
    for row in csv.reader(FUNCTIONS.open(newline="")):
        if not row or not row[0].startswith("0x"):
            continue
        status, size = row[1], int(row[2])
        if not args.min_size <= size <= args.max_size:
            continue
        addr = int(row[0], 16) - BASE
        families[(size, masked_words(data, addr, size))].append((addr, status))

    ranked = []
    for (size, _), members in families.items():
        open_members = [m for m in members if m[1] == "U"]
        if len(members) < 2 or not open_members:
            continue
        seed = any(m[1] == "O" for m in members)
        ranked.append((size * len(open_members), len(open_members), size, seed, members))
    ranked.sort(key=lambda r: (-r[0], -r[2]))

    print(" total  open  size  seed  members")
    for total, count, size, seed, members in ranked[: args.top]:
        members = sorted(members, key=lambda m: (m[1] != "U", m[0]))
        shown = " ".join(f"{a:x}{'' if s == 'U' else '(' + s + ')'}" for a, s in members[: args.members])
        more = f" +{len(members) - args.members}" if len(members) > args.members else ""
        print(f"{total:6d} {count:5d} {size:5d}  {'seed' if seed else '    '}  {shown}{more}")
    print(f"\n{len(ranked)} families with two or more members and at least one open member.")


if __name__ == "__main__":
    main()
