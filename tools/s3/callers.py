"""callers.py ADDR...: B/BL sites targeting each address, with the containing function (from functions.csv)."""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
WORK = _os.path.join(M, "build", "s3")  # scratch files
_os.makedirs(WORK, exist_ok=True)
import sys, struct, csv, bisect
IMG = _os.path.join(_os.path.dirname(M), "analysis", "extracted", "update", "decompressed", "main.memory.bin")
CSV = _os.path.join(M, "data", "functions.csv")
img = open(IMG, "rb").read()
rows = sorted((int(r["Address"], 16) & 0xffffffff, int(r["Size"]), r["Name"], r["Quality"]) for r in csv.DictReader(open(CSV, newline="")))
starts = [r[0] for r in rows]
targets = {int(a, 16): [] for a in sys.argv[1:]}
words = struct.unpack_from("<%dI" % (0x601d10 // 4), img, 0)
for i, w in enumerate(words):
    if (w & 0x7C000000) == 0x14000000:
        imm = w & 0x03FFFFFF
        if imm & (1 << 25):
            imm -= 1 << 26
        t = i * 4 + imm * 4
        if t in targets:
            targets[t].append(i * 4)
for t, sites in targets.items():
    print(f"{t:x}: {len(sites)} sites")
    for s in sites[:40]:
        k = bisect.bisect_right(starts, s) - 1
        f = rows[k] if k >= 0 else None
        print(f"   {s:x}  in {f[0]:x} {f[3]} {f[1]} {f[2]}" if f else f"   {s:x}")
