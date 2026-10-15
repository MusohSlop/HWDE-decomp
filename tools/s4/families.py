"""families.py OUT.txt [--lo HEX] [--hi HEX] [--min N] [--skip FILE ...] [--wide]: template families of unmatched functions.

Takes the unmatched functions (quality U, in no unit) at image offsets LO to HI (default 0 to 380000) of at least
MIN bytes (default 0), minus the constructor-shaped ones (a vtable, GOT slot + 0x10, stored into this: the scan of
tools/s3/vtscan.py and tools/s4/cands.py) and every address in a SKIP file (hex offsets or 0x71... addresses
anywhere in the file, as run_bands.py reads RV_SKIP; pass docs/s3_scope.txt for the third session's scope). Near
misses (quality m) are never U, so they are left out as well.

Each function is reduced to its opcode sequence with registers and relocation targets abstracted: register numbers
go (x5 -> x), calls and branches out of the function become one token, branches inside it keep their distance in
instructions, adrp pages, adr and literal-load addresses become one token, and so does the immediate of the first
add/ldr/str through a register an adrp set (the :lo12: half). Other immediates (field offsets, constants) stay, so
two functions in a family differ only in registers, callees and data addresses: one source (a template, a macro or
the same inline code) can close every copy. Families of two or more are written to OUT sorted by total bytes:
total, copies, size, then the addresses; the counts are printed. With --wide the functions of the whole image are
grouped and every family with a copy in LO-HI is kept, its copies outside the range listed after a |. With --relaxed
every other immediate (field offsets, constants, shift amounts) becomes one token as well, so instantiations of one
template over different types (other sizes, offsets and vtables) group together.
"""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
import argparse, collections, csv, json, os, re, sys
sys.path.insert(0, os.path.join(os.path.dirname(M), ".tools", "python"))
import capstone  # noqa

ap = argparse.ArgumentParser()
ap.add_argument("out")
ap.add_argument("--lo", default="0"); ap.add_argument("--hi", default="380000")
ap.add_argument("--min", type=int, default=0)
ap.add_argument("--skip", action="append", default=[])
ap.add_argument("--relaxed", action="store_true", help="also abstract every other immediate (field offsets, constants)")
ap.add_argument("--wide", action="store_true", help="group with the unmatched functions of the whole image and keep "
                "the families with a copy in LO-HI (the copies outside are listed after a |)")
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
REG = re.compile(r"\b([xwqsdvbh])(\d+|zr)\b")
BRANCH = re.compile(r"^(b|bl|b\..+|cbz|cbnz|tbz|tbnz)$")


def vtable_stores(code, ad):
    """Stores of a GOT vtable + 0x10 into this (x0 or a copy made before the first call), as tools/s4/cands.py."""
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
    """The abstracted opcode sequence of one function (a tuple of strings)."""
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
            # the :lo12: half of an adrp pair: add/ldr/str through a register an adrp set
            base = None
            if m == "add" and len(regs) == 3 and regs[2].startswith("#"):
                base = regs[1]
            elif "[" in ops:
                base = ops.split("[")[1].split(",")[0].split("]")[0].strip()
            if base and base[1:] in page:
                ops = re.sub(r"#(-?0x[0-9a-f]+|-?\d+)\]?", lambda mm: "#LO12" + ("]" if mm.group(0).endswith("]") else ""), ops, count=1)
        # a register written here is no longer an adrp page
        if regs and not m.startswith(("str", "stp", "stur", "cmp", "cmn", "tst", "b", "cb", "tb", "ret")) and m != "adrp":
            page.discard(regs[0][1:])
        if a.relaxed and not BRANCH.match(m):
            ops = re.sub(r"#-?(0x[0-9a-f]+|\d+)", "#I", ops)
        out.append(m + " " + REG.sub(r"\1", ops))
    return tuple(out)


cands, nctor, nskip = [], 0, 0
for r in csv.DictReader(open(os.path.join(M, "data", "functions.csv"), newline="")):
    ad = int(r["Address"], 16) & 0xffffffff; s = int(r["Size"])
    if r["Quality"] != "U" or ad in taken or not (a.wide or lo <= ad < hi) or s < a.min:
        continue
    if ad in skip:
        nskip += 1; continue
    if vtable_stores(img[ad:ad + s], ad):
        nctor += 1; continue
    cands.append((ad, s))
groups = collections.defaultdict(list)
for ad, s in cands:
    groups[shape(img[ad:ad + s], ad, s)].append((ad, s))
fams = [v for v in groups.values() if len(v) >= 2 and any(lo <= ad < hi for ad, _ in v)]
fams.sort(key=lambda v: (-sum(s for _, s in v), v[0][0]))
with open(a.out, "w", encoding="utf-8", newline="\n") as f:
    f.write(f"# Template families among unmatched functions {lo:x}-{hi:x} (tools/s4/families.py{' --wide' if a.wide else ''}{' --relaxed' if a.relaxed else ''}): identical\n"
            f"# opcode sequences with registers and relocation targets abstracted, constructor-shaped functions and"
            f" {len(skip)} skipped addresses left out.\n# total bytes, copies, size, addresses{' (copies outside the range after |)' if a.wide else ''}.\n")
    for v in fams:
        inside = ' '.join(f'{ad:x}' for ad, _ in sorted(v) if lo <= ad < hi)
        outside = ' '.join(f'{ad:x}' for ad, _ in sorted(v) if not lo <= ad < hi)
        f.write(f"{sum(s for _, s in v)}\t{len(v)}\t{v[0][1]}\t{inside}{' | ' + outside if outside else ''}\n")
print(f"{len(cands)} functions scanned ({nctor} constructor-shaped and {nskip} skipped left out); {len(fams)} families of"
      f" 2 or more, {sum(len(v) for v in fams)} functions, {sum(s for v in fams for _, s in v):,} B;"
      f" {sum(1 for v in fams if len(v) >= 3)} of 3 or more")
