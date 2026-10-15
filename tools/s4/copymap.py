"""copymap.py ADDR [SRCREG DSTREG]: for a straight-line copy function (loads from x0, stores to x1, or the given base
registers), list each copied piece as src offset, dst offset, width and their difference, in program order."""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
import csv, os, re, sys
sys.path.insert(0, os.path.join(os.path.dirname(M), ".tools", "python"))
import capstone  # noqa

img = open(os.path.join(os.path.dirname(M), "analysis", "extracted", "update", "decompressed", "main.memory.bin"), "rb").read()
sizes = {int(r["Address"], 16) & 0xffffffff: int(r["Size"]) for r in csv.DictReader(open(os.path.join(M, "data", "functions.csv"), newline=""))}
a = int(sys.argv[1], 16)
SRC, DST = (sys.argv[2], sys.argv[3]) if len(sys.argv) > 3 else ("x0", "x1")
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
regs = {}      # reg -> ("const", v) | ("src", off, width) | ("dst", off)
W = {"x": 8, "w": 4, "h": 2, "b": 1, "q": 16, "d": 8, "s": 4}
pieces = []
for i in md.disasm(img[a:a + sizes[a]], a):
    m, ops = i.mnemonic, [o.strip() for o in i.op_str.replace("[", "").replace("]", "").replace("!", "").split(",")]
    if m in ("mov", "movz") and ops[1].startswith("#"):
        regs[ops[0][1:]] = ("const", int(ops[1][1:], 0))
    elif m == "movk":
        v = regs.get(ops[0][1:])
        sh = int(ops[2].split("#")[1]) if len(ops) > 2 else 0
        regs[ops[0][1:]] = ("const", (v[1] if v else 0) | (int(ops[1][1:], 16) << sh))
    elif m == "add" and ops[1] == DST and ops[2].startswith("#"):
        regs[ops[0][1:]] = ("dst", int(ops[2][1:], 16))
    elif m == "add" and ops[1] == SRC and ops[2].startswith("#"):
        regs[ops[0][1:]] = ("srcb", int(ops[2][1:], 16))
    elif m.startswith("ld") and m not in ("ldp",):
        base, off = ops[1], 0
        if len(ops) > 2:
            if ops[2].startswith("#"):
                off = int(ops[2][1:], 16)
            else:
                off = regs.get(ops[2][1:], ("const", None))[1]
        if base != SRC:
            off = (regs.get(base[1:], ("srcb", None))[1] or 0) + off
        width = {"ldrb": 1, "ldrh": 2, "ldrsb": 1, "ldrsh": 2, "ldrsw": 4}.get(m, W[ops[0][0]])
        regs[ops[0][1:]] = ("src", off, width)
    elif m.startswith("st") and m not in ("stp",):
        base, off = ops[1], 0
        if len(ops) > 2:
            off = int(ops[2][1:], 16) if ops[2].startswith("#") else regs.get(ops[2][1:], ("const", None))[1]
        if base != DST:
            b = regs.get(base[1:])
            if not b or b[0] != "dst" or b[1] is None or off is None:
                continue                      # not a store through the destination base
            off = b[1] + off
        v = regs.get(ops[0][1:])
        width = {"strb": 1, "strh": 2}.get(m, W[ops[0][0]])
        pieces.append((v[1] if v and v[0] == "src" else None, off, width))
for s, d, w in pieces:
    print(f"src {s if s is None else hex(s)}\tdst {d:#x}\tw {w}\tdelta {None if s is None else hex(s - d)}")
