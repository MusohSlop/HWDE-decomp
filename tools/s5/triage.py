"""triage.py RANK.tsv OUT.tsv: for every function of a rank.py table that does not generate, count what makes hand
matching hard: float and vector instructions, backward branches (loops), calls, indirect jumps (jump tables),
stack frame size. Writes one row per function: addr size reason ninsn fp% loops calls blr jt frame."""
import os, re, sys, struct
M = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))  # the matching/ folder
ROOT = os.path.dirname(M)
sys.path.insert(0, os.path.join(ROOT, ".tools", "python"))
import capstone  # noqa
img = open(os.path.join(ROOT, "analysis", "extracted", "update", "decompressed", "main.memory.bin"), "rb").read()
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
rows = []
for line in open(sys.argv[1], encoding="utf-8"):
    p = line.rstrip("\n").split("\t")
    if len(p) < 3:
        continue
    a, size, cls = int(p[0], 16), int(p[1]), p[2]
    reason = p[6] if len(p) > 6 else ""
    ins = list(md.disasm(img[a:a + size], a))
    n = len(ins)
    fp = sum(1 for i in ins if re.search(r"\b[sdqvh]\d+\b", i.op_str))
    loops = sum(1 for i in ins if re.match(r"(b\.|b$|cbn?z|tbn?z)", i.mnemonic)
                and int(i.op_str.split("#")[-1], 16) <= i.address)
    calls = sum(1 for i in ins if i.mnemonic == "bl")
    blr = sum(1 for i in ins if i.mnemonic == "blr")
    jt = sum(1 for i in ins if i.mnemonic == "br")
    frame = 0
    for i in ins[:8]:
        m = re.match(r"sp, sp, #0x([0-9a-f]+)", i.op_str)
        if i.mnemonic == "sub" and m:
            frame = int(m.group(1), 16)
    rows.append((a, size, cls, reason, n, 100 * fp // max(n, 1), loops, calls, blr, jt, frame))
with open(sys.argv[2], "w", encoding="utf-8") as f:
    for r in rows:
        f.write("%x\t%d\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%x\n" % r)
print(len(rows), "rows")
