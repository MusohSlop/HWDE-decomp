"""shapefind.py ADDR [QUAL]: functions of the same size whose instructions match ADDR's with registers, immediates and
addresses abstracted; prints quality, name and unit."""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
WORK = _os.path.join(M, "build", "s3")  # scratch files
_os.makedirs(WORK, exist_ok=True)
import csv, json, struct, sys, os, re
IMG = _os.path.join(_os.path.dirname(M), "analysis", "extracted", "update", "decompressed", "main.memory.bin")
sys.path.insert(0, os.path.join(os.path.dirname(M), ".tools", "python"))
import capstone
img = open(IMG, "rb").read()
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
rows = {int(r["Address"], 16) & 0xffffffff: r for r in csv.DictReader(open(os.path.join(M, "data/functions.csv"), newline=""))}
man = json.load(open(os.path.join(M, "data/units.json"), encoding="utf-8-sig"))
unit_of = {int(a, 16) & 0xffffffff: u for u, s in man["units"].items() for a in s["functions"].values()}
def shape(a, n, exact):
    out = []
    for i in md.disasm(img[a:a + n], a):
        o = i.op_str if exact else re.sub(r"#-?0x[0-9a-f]+|#-?\d+", "#I", i.op_str)
        out.append(i.mnemonic + " " + o)
    return out
a = int(sys.argv[1], 16)
qual = sys.argv[2] if len(sys.argv) > 2 else "O"
exact = "--exact" in sys.argv
n = int(rows[a]["Size"])
ref = shape(a, n, exact)
for b, r in rows.items():
    if b != a and int(r["Size"]) == n and r["Quality"] == qual and shape(b, n, exact) == ref:
        print(f"{b:x} {r['Quality']} {r['Name']} {unit_of.get(b, '')}")
