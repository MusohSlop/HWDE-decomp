"""Find inventory entries in data/functions.csv that cover more than one function, and optionally split them.

usage: audit_bounds.py OUT.tsv [--apply]

For every unmatched entry, a split point is an instruction that follows a ret or an unconditional branch (b, br)
and that no conditional branch inside the entry reaches (an unconditional b to a prologue is a tail call into
the next function), where either a prologue starts (a pre-indexed store of callee-saved
registers or of x29/x30 to the stack, or sub sp, sp, #N) or a bl elsewhere in the image calls it. A split is
proposed only when every piece decodes completely and ends in ret, b or br. Points that already start another
entry end the entry there instead of making a new one. OUT.tsv lists every proposal (entry, size, pieces); with
--apply the entries are replaced by their pieces (named FUN_<address>, unmatched). Matched entries are never
touched.
"""
import csv
import os
import re
import struct
import sys

M = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(os.path.dirname(M), ".tools", "python"))
import capstone  # noqa: E402

IMAGE = os.path.join(os.path.dirname(M), "analysis", "extracted", "update", "decompressed", "main.memory.bin")
CSV = os.path.join(M, "data", "functions.csv")
BASE = 0x7100000000


def main():
    out, apply_ = sys.argv[1], "--apply" in sys.argv[2:]
    d = open(IMAGE, "rb").read()
    md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
    lines = open(CSV, encoding="utf-8").read().split("\n")
    rows = [l.split(",") for l in lines if l.startswith("0x")]
    starts = {int(r[0], 16) - BASE for r in rows}
    extents = sorted((int(r[0], 16) - BASE, int(r[0], 16) - BASE + int(r[2])) for r in rows)

    def inside_other(s, own):
        """True when s starts or lies inside another entry than own."""
        return any(b <= s < e and b != own for b, e in extents if b <= s)
    lo = min(starts)
    hi = min(len(d) - 4, max(int(r[0], 16) - BASE + int(r[2]) for r in rows))
    # bl targets over the code the inventory covers
    called = set()
    for off in range(lo, hi, 4):
        w, = struct.unpack_from("<I", d, off)
        if (w & 0xFC000000) == 0x94000000:
            imm = w & 0x03FFFFFF
            called.add(off + ((imm - (1 << 26) if imm & (1 << 25) else imm) << 2))
    prologue = re.compile(r"(x(19|2[0-9]|30)|d(8|9|1[0-5])), \[sp, #-0x[0-9a-f]+\]!$")
    proposals = {}
    for r in rows:
        if r[1] != "U":
            continue
        a, n = int(r[0], 16) - BASE, int(r[2])
        if a + n > len(d):
            continue
        ins = list(md.disasm(d[a:a + n], a))
        if len(ins) * 4 != n:
            continue
        targets, jumps = set(), {}
        for i in ins:
            if (i.mnemonic in ("cbz", "cbnz", "tbz", "tbnz") or i.mnemonic.startswith("b.")) and "#" in i.op_str:
                targets.add(int(i.op_str.split("#")[-1], 0))
            elif i.mnemonic == "b" and "#" in i.op_str:
                jumps.setdefault(int(i.op_str.split("#")[-1], 0), set()).add(i.address)
        cuts = []
        for k in range(1, len(ins)):
            prev, cur = ins[k - 1], ins[k]
            if prev.mnemonic not in ("ret", "b", "br") or cur.address in targets:
                continue
            pro = (cur.mnemonic in ("stp", "str") and prologue.search(cur.op_str)) or \
                  (cur.mnemonic == "sub" and cur.op_str.startswith("sp, sp, #"))
            # an unconditional b to a prologue from the instruction just before it is a tail call into the next
            # function; any other b to it (a late prologue after a fast path) keeps it inside this one
            if cur.address in jumps and (not pro or jumps[cur.address] != {prev.address}):
                continue
            if pro or cur.address in called or cur.address in starts:
                cuts.append(cur.address)
        if not cuts:
            continue
        bounds = [a] + cuts + [a + n]
        pieces = [(bounds[j], bounds[j + 1] - bounds[j]) for j in range(len(bounds) - 1)]
        pieces = [p for p in pieces if p[0] == a or not inside_other(p[0], a)]
        ok = True
        for s, sz in pieces:
            pi = list(md.disasm(d[s:s + sz], s))
            if len(pi) * 4 != sz or pi[-1].mnemonic not in ("ret", "b", "br"):
                ok = False
                break
        if ok and (len(pieces) > 1 or pieces[0][1] != n):
            proposals[a] = (n, pieces)
    with open(out, "w", encoding="utf-8") as f:
        for a, (n, pieces) in sorted(proposals.items()):
            f.write("%x\t%d\t%s\n" % (a, n, " ".join("%x:%d" % p for p in pieces)))
    new_rows = sum(len(pieces) for a, (n, pieces) in proposals.items())
    print("%d entries to split into %d pieces (%d new entries)" % (len(proposals), new_rows,
                                                                   new_rows - len(proposals)))
    if not apply_:
        return
    res = []
    for l in lines:
        if not l.startswith("0x"):
            res.append(l)
            continue
        r = l.split(",")
        a = int(r[0], 16) - BASE
        if a not in proposals:
            res.append(l)
            continue
        for s, sz in proposals[a][1]:
            if s == a:
                res.append(",".join([r[0], r[1], str(sz)] + ["FUN_%010x" % (BASE + s)] + r[4:]))
            else:
                res.append(",".join(["0x%010x" % (BASE + s), "U", str(sz), "FUN_%010x" % (BASE + s)] + r[4:]))
    open(CSV, "w", encoding="utf-8", newline="\n").write("\n".join(res))


if __name__ == "__main__":
    main()
