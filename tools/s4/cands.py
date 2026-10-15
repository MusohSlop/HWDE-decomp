"""cands.py OUT.txt [--lo HEX] [--hi HEX] [--min N] [--max N] [--skip FILE ...]: the fourth session's candidates.

Unmatched (U, in no unit) functions of more than MIN bytes (default 1500) at image offsets LO to HI (default 0 to
380000), minus constructor-shaped functions (a vtable, GOT slot + 0x10, stored into this: the same scan as
tools/s3/vtscan.py) and every address listed in a SKIP file (hex offsets or 0x71... addresses anywhere in the file,
as run_bands.py reads RV_SKIP). Writes 'addr size' lines sorted by size and prints the counts.
"""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
import argparse, csv, json, os, re, sys
sys.path.insert(0, os.path.join(os.path.dirname(M), ".tools", "python"))
import capstone  # noqa

ap = argparse.ArgumentParser()
ap.add_argument("out")
ap.add_argument("--lo", default="0"); ap.add_argument("--hi", default="380000")
ap.add_argument("--min", type=int, default=1500); ap.add_argument("--max", type=int, default=1 << 30)
ap.add_argument("--skip", action="append", default=[])
a = ap.parse_args()
lo, hi = int(a.lo, 16), int(a.hi, 16)

img = open(os.path.join(os.path.dirname(M), "analysis", "extracted", "update", "decompressed", "main.memory.bin"), "rb").read()
man = json.load(open(os.path.join(M, "data", "units.json"), encoding="utf-8-sig"))
taken = {int(v, 16) & 0xffffffff for u in man["units"].values() for v in u.get("functions", {}).values()}
skip = set()
for f in a.skip:
    for t in re.findall(r"\b(?:0x71)?([0-9a-f]{4,8})\b", open(f, encoding="utf-8-sig").read()):
        skip.add(int(t, 16) & 0xffffffff)
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
CALLEE = {"x19", "x20", "x21", "x22", "x23", "x24", "x25", "x26", "x27", "x28"}


def vtable_stores(code, a):
    """Count stores of a GOT vtable + 0x10 into this (x0 or a copy made before the first call), as vtscan.py."""
    state, nvt, this, calls = {}, 0, {"x0"}, 0
    for i in md.disasm(code, a):
        m, ops = i.mnemonic, i.op_str
        if m == "mov" and calls == 0:
            p = [x.strip() for x in ops.split(",")]
            if len(p) == 2 and p[1] in this:
                this.add(p[0])
            elif p[0] in this and p[0] != "x0":
                this.discard(p[0])
        if m == "adrp":
            state[ops.split(",")[0].strip()] = "page"
        elif m == "ldr" and ops.count("[") == 1:
            p = [x.strip() for x in ops.replace("[", "").replace("]", "").split(",")]
            if len(p) >= 2 and state.get(p[1]) == "page" and p[0].startswith("x"):
                state[p[0]] = "got"
            elif p[0] in state:
                state.pop(p[0], None)
        elif m == "add":
            p = [x.strip() for x in ops.split(",")]
            if len(p) == 3 and state.get(p[1]) == "got" and p[2] == "#0x10":
                state[p[0]] = "vt"
            elif p[0] in state:
                state.pop(p[0], None)
        elif m in ("str", "stp", "stur"):
            p = [x.strip() for x in ops.replace("[", "").replace("]", "").replace("!", "").split(",")]
            base = p[2] if m == "stp" else p[1]
            if (state.get(p[0]) == "vt" or (m == "stp" and state.get(p[1]) == "vt")) and base in this:
                nvt += 1
        elif m in ("bl", "blr", "b", "ret"):
            calls += 1
            this.discard("x0")
            state = {k: v for k, v in state.items() if k in CALLEE}
    return nvt


out, nctor, nskip = [], 0, 0
for r in csv.DictReader(open(os.path.join(M, "data", "functions.csv"), newline="")):
    ad = int(r["Address"], 16) & 0xffffffff; s = int(r["Size"])
    if r["Quality"] != "U" or ad in taken or not (lo <= ad < hi) or not (a.min < s <= a.max):
        continue
    if ad in skip:
        nskip += 1; continue
    if vtable_stores(img[ad:ad + s], ad):
        nctor += 1; continue
    out.append((s, ad))
out.sort()
with open(a.out, "w", encoding="utf-8") as f:
    for s, ad in out:
        f.write(f"{ad:x}\t{s}\n")
print(f"{len(out)} candidates ({sum(s for s, _ in out):,} B); {nctor} constructor-shaped and {nskip} skipped left out;"
      f" {sum(1 for s, _ in out if s > 6000)} over 6,000 B")
