"""vtscan.py OUT: unmatched (U) functions with vtable stores: adrp xN; ldr xN,[xN,#lo] (a GOT slot); add xN,xN,#0x10;
str xN,[xB,#off]. Writes 'addr size nvt' sorted by size."""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
WORK = _os.path.join(M, "build", "s3")  # scratch files
_os.makedirs(WORK, exist_ok=True)
import csv, json, struct, sys, os
IMG = _os.path.join(_os.path.dirname(M), "analysis", "extracted", "update", "decompressed", "main.memory.bin")
sys.path.insert(0, os.path.join(os.path.dirname(M), ".tools", "python"))
import capstone
img = open(IMG, "rb").read()
man = json.load(open(os.path.join(M, "data/units.json"), encoding="utf-8-sig"))
taken = {int(a, 16) & 0xffffffff for u in man["units"].values() for a in u.get("functions", {}).values()}
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
md.detail = False
out = []
for r in csv.DictReader(open(os.path.join(M, "data/functions.csv"), newline="")):
    a = int(r["Address"], 16) & 0xffffffff; s = int(r["Size"])
    if r["Quality"] != "U" or a in taken:
        continue
    code = img[a:a + s]
    regs_got = {}   # reg -> page (adrp), then reg -> 'got' after ldr
    state = {}
    nvt = 0
    this = {"x0"}
    calls = 0
    for i in md.disasm(code, a):
        m, ops = i.mnemonic, i.op_str
        if m == "mov" and calls == 0:
            p = [x.strip() for x in ops.split(",")]
            if len(p) == 2 and p[1] in this:
                this.add(p[0])
            elif p[0] in this and p[0] != "x0":
                this.discard(p[0])
        if m == "adrp":
            rd = ops.split(",")[0].strip()
            state[rd] = "page"
        elif m == "ldr" and ops.count("[") == 1:
            p = [x.strip() for x in ops.replace("[", "").replace("]", "").split(",")]
            if len(p) >= 2 and state.get(p[1]) == "page" and p[0].startswith("x"):
                tgt = None
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
            state = {k: v for k, v in state.items() if k in ("x19", "x20", "x21", "x22", "x23", "x24", "x25", "x26", "x27", "x28")}
    if nvt:
        out.append((s, a, nvt))
out.sort()
with open(sys.argv[1], "w") as f:
    for s, a, n in out:
        f.write(f"{a:x}\t{s}\t{n}\n")
print(len(out), "functions;", sum(1 for s, a, n in out if s <= 1500), "<=1500;", sum(1 for s, a, n in out if a >= 0x380000), "in s2 range")
