"""xref.py ADDR [LO HI]: list instructions that reach a data address through adrp plus a lo12 add or load/store
(within a few instructions of the adrp), in the text range LO..HI (hex image offsets, default the whole text).
Prints the function (functions.csv start) and instruction of each reference."""
import bisect, csv, os, re, sys
M = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))  # the matching/ folder
ROOT = os.path.dirname(M)
sys.path.insert(0, os.path.join(ROOT, ".tools", "python"))
import capstone  # noqa
img = open(os.path.join(ROOT, "analysis", "extracted", "update", "decompressed", "main.memory.bin"), "rb").read()
target = int(sys.argv[1], 16) & 0xffffffff
lo = int(sys.argv[2], 16) if len(sys.argv) > 2 else 0
hi = int(sys.argv[3], 16) if len(sys.argv) > 3 else 0x601d10
starts = sorted((int(r["Address"], 16) & 0xffffffff, r["Name"]) for r in
                csv.DictReader(open(os.path.join(M, "data", "functions.csv"), newline="")))
keys = [s for s, _ in starts]
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
md.skipdata = True
page = target & ~0xfff
pending = {}
for i in md.disasm(img[lo:hi], lo):
    ops = [o.strip() for o in i.op_str.replace("[", "").replace("]", "").replace("!", "").split(",")]
    if i.mnemonic == "adrp" and len(ops) == 2 and int(ops[1].lstrip("#"), 16) == page:
        pending[ops[0]] = i.address
        continue
    for k, reg in enumerate(ops):
        if reg in pending and i.address - pending[reg] < 64:
            m = re.search(r"#0x([0-9a-f]+)", i.op_str)
            off = int(m.group(1), 16) if m else 0
            if page + off == target or (i.mnemonic == "add" and page + off <= target < page + off + 0x40):
                f = bisect.bisect_right(keys, i.address) - 1
                print("%x  %-24s %x %s %s" % (starts[f][0], starts[f][1][:24], i.address, i.mnemonic, i.op_str))
            if k == 0 and i.mnemonic not in ("str", "strb", "strh", "stp", "stur"):
                pending.pop(reg, None)
            break
