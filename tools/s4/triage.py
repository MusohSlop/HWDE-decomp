"""triage.py LIST.txt [OUT.tsv]: shape metrics of the functions in LIST (hex offsets, first column), to pick the ones
that are quick to write by hand. Columns: addr, size, instructions, conditional branches, backward branches (loops),
float/vector instructions, calls, indirect calls, jump tables (br), stack frame size, and a rough score
(branches and loops weigh most). Sorted by score."""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
import csv, os, re, sys
sys.path.insert(0, os.path.join(os.path.dirname(M), ".tools", "python"))
import capstone  # noqa

img = open(os.path.join(os.path.dirname(M), "analysis", "extracted", "update", "decompressed", "main.memory.bin"), "rb").read()
sizes = {int(r["Address"], 16) & 0xffffffff: int(r["Size"]) for r in csv.DictReader(open(os.path.join(M, "data", "functions.csv"), newline=""))}
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
rows = []
for line in open(sys.argv[1], encoding="utf-8-sig"):
    if not line.strip():
        continue
    a = int(line.split()[0], 16)
    s = sizes[a]
    n = cb = back = fl = calls = icalls = br = 0
    frame = 0
    for i in md.disasm(img[a:a + s], a):
        n += 1
        m, ops = i.mnemonic, i.op_str
        if m.startswith("b.") or m in ("cbz", "cbnz", "tbz", "tbnz"):
            cb += 1
            t = re.search(r"#0x([0-9a-f]+)$", ops)
            if t and int(t.group(1), 16) <= i.address:
                back += 1
        elif m == "b":
            t = re.search(r"#0x([0-9a-f]+)$", ops)
            if t and int(t.group(1), 16) <= i.address and int(t.group(1), 16) >= a:
                back += 1
        elif m == "bl":
            calls += 1
        elif m == "blr":
            icalls += 1
        elif m == "br":
            br += 1
        if re.search(r"\b[sdvq]\d+\b", ops) and m not in ("stp", "ldp", "str", "ldr") or m.startswith("f"):
            fl += 1
        fm = re.fullmatch(r"sp, sp, #0x([0-9a-f]+)", ops) if m == "sub" else None
        if fm:
            frame = max(frame, int(fm.group(1), 16))
        mm = re.match(r"(?:stp|str) \w+, (?:\w+, )?\[sp, #-0x([0-9a-f]+)\]!", f"{m} {ops}")
        if mm:
            frame = max(frame, int(mm.group(1), 16))
    score = cb * 3 + back * 15 + fl + br * 20 + icalls
    rows.append((score, a, s, n, cb, back, fl, calls, icalls, br, frame))
rows.sort()
out = open(sys.argv[2], "w", encoding="utf-8") if len(sys.argv) > 2 else sys.stdout
out.write("addr\tsize\tinstr\tcbr\tloops\tfloat\tcalls\ticalls\tjt\tframe\tscore\n")
for score, a, s, n, cb, back, fl, calls, icalls, br, frame in rows:
    out.write(f"{a:x}\t{s}\t{n}\t{cb}\t{back}\t{fl}\t{calls}\t{icalls}\t{br}\t{frame:#x}\t{score}\n")
