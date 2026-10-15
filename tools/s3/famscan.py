"""famscan.py OUT.txt [--skip FILE ...] [--keep HEX ...]: template families among the functions tools/s4/families.py
leaves out (the third session's scope, constructor-shaped functions, functions over 1,500 bytes).

Groups every unmatched function of the image (quality U or m, in no unit) by the abstracted opcode sequence of
tools/s4/families.py (registers, callees and data addresses abstracted; field offsets and constants kept; the shape
code is copied from there, as is its vtable-store test) and keeps the families of two or more with a copy in
docs/s3_scope.txt, a constructor-shaped copy or a copy over 1,500 bytes. A family is dropped when any copy is in a
SKIP file (hex offsets or 0x71... addresses anywhere in it) or is one of the --keep addresses (families another
session holds). Each line: total bytes, copies, size, where (s3: every copy in the scope or constructor-shaped;
mixed: some copies outside), the addresses (a * marks a copy in the scope, a + a constructor-shaped one).
"""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
import argparse, collections, csv, json, os, re, sys
sys.path.insert(0, os.path.join(os.path.dirname(M), ".tools", "python"))
import capstone  # noqa

ap = argparse.ArgumentParser()
ap.add_argument("out")
ap.add_argument("--skip", action="append", default=[])
ap.add_argument("--keep", nargs="*", default=[])
a = ap.parse_args()

img = open(os.path.join(os.path.dirname(M), "analysis", "extracted", "update", "decompressed", "main.memory.bin"), "rb").read()
man = json.load(open(os.path.join(M, "data", "units.json"), encoding="utf-8-sig"))
taken = {int(v, 16) & 0xffffffff for u in man["units"].values() for v in u.get("functions", {}).values()}


def offsets(path):
    return {int(t, 16) & 0xffffffff for t in re.findall(r"\b(?:0x71)?([0-9a-f]{4,8})\b",
                                                          open(path, encoding="utf-8-sig").read())}


scope = {int(l.strip(), 16) for l in open(os.path.join(M, "docs", "s3_scope.txt"), encoding="utf-8-sig")
         if l.strip() and not l.startswith("#")}
skip = set()
for f in a.skip:
    skip |= offsets(f)
keep = {int(x, 16) & 0xffffffff for x in a.keep}
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
CALLEE = {"x19", "x20", "x21", "x22", "x23", "x24", "x25", "x26", "x27", "x28"}
REG = re.compile(r"\b([xwqsdvbh])(\d+|zr)\b")
BRANCH = re.compile(r"^(b|bl|b\..+|cbz|cbnz|tbz|tbnz)$")


def vtable_stores(code, ad):
    """Stores of a GOT vtable + 0x10 into this (as tools/s4/families.py)."""
    state, nvt, this, calls = {}, 0, {"x0"}, 0
    for i in md.disasm(code, ad):
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


def shape(code, ad, size):
    """The abstracted opcode sequence of one function (as tools/s4/families.py)."""
    out, page = [], set()
    for i in md.disasm(code, ad):
        m, ops = i.mnemonic, i.op_str
        regs = [x.strip() for x in re.split(r"[,\[\]!]", ops) if x.strip()]
        if BRANCH.match(m):
            t = re.search(r"#0x([0-9a-f]+)$", ops)
            if t:
                dst = int(t.group(1), 16)
                tok = f"@{(dst - i.address) // 4:+d}" if ad <= dst < ad + size else "#FN"
                ops = ops[:t.start()] + tok
        elif m in ("adrp", "adr"):
            ops = re.sub(r"#0x[0-9a-f]+$", "#PAGE", ops)
            if m == "adrp":
                page.add(regs[0][1:])
                out.append(m + " " + REG.sub(r"\1", ops))
                continue
        elif m.startswith("ldr") and re.search(r"#0x[0-9a-f]+$", ops) and "[" not in ops:
            ops = re.sub(r"#0x[0-9a-f]+$", "#LIT", ops)
        else:
            base = None
            if m == "add" and len(regs) == 3 and regs[2].startswith("#"):
                base = regs[1]
            elif "[" in ops:
                base = ops.split("[")[1].split(",")[0].split("]")[0].strip()
            if base and base[1:] in page:
                ops = re.sub(r"#(-?0x[0-9a-f]+|-?\d+)\]?",
                             lambda mm: "#LO12" + ("]" if mm.group(0).endswith("]") else ""), ops, count=1)
        if regs and not m.startswith(("str", "stp", "stur", "cmp", "cmn", "tst", "b", "cb", "tb", "ret")) and m != "adrp":
            page.discard(regs[0][1:])
        out.append(m + " " + REG.sub(r"\1", ops))
    return tuple(out)


groups = collections.defaultdict(list)
ctor = set()
n = 0
for r in csv.DictReader(open(os.path.join(M, "data", "functions.csv"), newline="")):
    ad = int(r["Address"], 16) & 0xffffffff
    s = int(r["Size"])
    if r["Quality"] not in ("U", "m") or ad in taken or s < 8:
        continue
    code = img[ad:ad + s]
    if vtable_stores(code, ad):
        ctor.add(ad)
    groups[shape(code, ad, s)].append((ad, s))
    n += 1
fams = []
for v in groups.values():
    ads = {ad for ad, _ in v}
    if len(v) < 2 or ads & (skip | keep):
        continue
    if not any(ad in scope or ad in ctor or s > 1500 for ad, s in v):
        continue
    fams.append(sorted(v))
fams.sort(key=lambda v: (-sum(s for _, s in v), v[0][0]))
with open(a.out, "w", encoding="utf-8", newline="\n") as f:
    f.write("# Template families with a copy in the third session's scope, a constructor-shaped copy or a copy over 1,500 B\n"
            "# (tools/s3/famscan.py): total bytes, copies, size, s3 (every copy in the scope or constructor-shaped) or mixed,\n"
            "# addresses (* in docs/s3_scope.txt, + constructor-shaped).\n")
    for v in fams:
        mine = all(ad in scope or ad in ctor for ad, _ in v)
        f.write("%d\t%d\t%d\t%s\t%s\n" % (sum(s for _, s in v), len(v), v[0][1], "s3" if mine else "mixed",
                " ".join("%x%s%s" % (ad, "*" if ad in scope else "", "+" if ad in ctor else "") for ad, _ in v)))
mine = [v for v in fams if all(ad in scope or ad in ctor for ad, _ in v)]
print("%d unmatched functions grouped; %d families kept (%d functions, %s B); %d all in scope or constructor-shaped "
      "(%d functions, %s B)" % (n, len(fams), sum(len(v) for v in fams), format(sum(s for v in fams for _, s in v), ","),
                               len(mine), sum(len(v) for v in mine), format(sum(s for v in mine for _, s in v), ",")))
