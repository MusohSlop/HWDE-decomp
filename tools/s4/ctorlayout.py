"""Member layout of a constructor read from the original's code.

usage: ctorlayout.py ADDR [--size TARGET=BYTES ...] [--all]

Emulates the function from its entry: `this` (x0) and the registers derived from it, constants built with
mov/movk, and the two loops Clang emits for member arrays (a byte count counted down to zero, or a pointer compared
with the end address). Each call whose x0 is `this`+offset is a member constructor, each store through a
`this`-based address a field initialisation, and each loop an array (several calls per iteration: an array of
structs). The emulation stops at the first instruction it does not model (the start of the constructor body); the
listing then shows the members in order with the gaps between them, runs of equal constructors at their size
merged into arrays. Element sizes come from the strides of the loops and runs, from --size, or from the known
types below; an unknown size is shown as the gap to the next member, marked `?`. --all prints the raw events too.
"""
import os, re, sys, csv
M = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))  # the matching/ folder
ROOT = os.path.dirname(M)
sys.path.insert(0, os.path.join(ROOT, ".tools", "python"))
import capstone  # noqa

KNOWN = {0x1ef52c: ("LightSource", 0x48), 0x1f0140: ("TrackLightTarget", 0x88), 0x5d2744: ("LightResource", 0x110),
         0x1f18e8: ("InfoMarker", 0x20), 0x1305e4: ("InfoGauge", 0x410), 0xe05d4: ("InfoTimer", 0x290),
         0xe4ee0: ("InfoMapPanel", 0x13b8), 0xe510c: ("InfoIconSet", 0x618), 0xe51c8: ("InfoIconTable", 0x900),
         0x1f1cd8: ("LayoutRect", 0x28), 0x1f1e0c: ("LayoutBox", 0x10), 0x1f1594: ("LayoutLine", 0x28)}


def reg(name):
    if name in ("xzr", "wzr"):
        return "zr"
    m = re.fullmatch(r"[xw](\d+)", name)
    return int(m.group(1)) if m else name


def imm(s):
    return int(s.strip().lstrip("#"), 0)


def main():
    args = sys.argv[1:]
    addr = int(args[0], 16)
    sizes = {}
    for k, a in enumerate(args):
        if a == "--size":
            t, v = args[k + 1].split("=")
            sizes[int(t, 16)] = int(v, 0)
    show_all = "--all" in args
    img = open(os.path.join(ROOT, "analysis", "extracted", "update", "decompressed", "main.memory.bin"), "rb").read()
    fsize = {int(r[0], 16) - 0x7100000000: int(r[2]) for r in csv.reader(open(os.path.join(M, "data", "functions.csv")))
             if r[0].startswith("0x")}[addr]
    md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
    ins = list(md.disasm(img[addr:addr + fsize], addr))
    index = {i.address: k for k, i in enumerate(ins)}
    st = {0: ("this", 0)}       # register -> ("this", off) | ("const", value)
    events = []                 # ("call", off, target, args) | ("store", off, width, value) | ("loop", start, n, stride, tmpl)
    ev_at = {}
    k = 0
    stop = None
    last_cmp = None
    while k < len(ins):
        i = ins[k]
        ev_at[i.address] = len(events)
        mn, ops = i.mnemonic, [o.strip() for o in i.op_str.split(",")]
        try:
            if mn in ("stp",) and ops[0].startswith("x29") or (mn == "stp" and "sp" in i.op_str) or \
                    (mn in ("str", "sub", "add") and "sp" in ops[:2] and mn != "add") or (mn == "add" and ops[0] == "x29"):
                k += 1; continue                                   # prologue
            if mn == "str" and "[sp" in i.op_str:
                k += 1; continue
            if mn == "mov" and ops[1].startswith("#"):
                v = imm(ops[1])
                st[reg(ops[0])] = ("const", v & (0xffffffff if ops[0][0] == "w" else (1 << 64) - 1))
            elif mn == "mov":
                s = reg(ops[1])
                st[reg(ops[0])] = ("const", 0) if s == "zr" else st.get(s)
            elif mn == "movk":
                d = reg(ops[0]); sh = int(ops[2].split("#")[1], 0) if len(ops) > 2 else 0
                old = st.get(d)
                if not old or old[0] != "const":
                    raise ValueError
                v = (old[1] & ~(0xffff << sh)) | (imm(ops[1]) << sh)
                st[d] = ("const", v)
            elif mn in ("add", "sub") and len(ops) >= 3:
                d, s = reg(ops[0]), reg(ops[1])
                if ops[2].startswith("#"):
                    v = imm(ops[2]) << (12 if len(ops) > 3 and "lsl #12" in ops[3] else 0)
                else:
                    o = st.get(reg(ops[2]))
                    if not o or o[0] != "const":
                        raise ValueError
                    v = o[1]
                b = st.get(s)
                if not b:
                    raise ValueError
                st[d] = (b[0], b[1] + v if mn == "add" else b[1] - v)
            elif mn in ("str", "strb", "strh", "stp"):
                m = re.search(r"\[(\w+)(?:, (#?[-\w]+))?\]", i.op_str)
                base = st.get(reg(m.group(1)))
                if not base or base[0] != "this":
                    raise ValueError
                if m.group(2) and m.group(2).startswith("#"):
                    off = base[1] + imm(m.group(2))
                elif m.group(2):
                    o = st.get(reg(m.group(2)))
                    if not o or o[0] != "const":
                        raise ValueError
                    off = base[1] + o[1]
                else:
                    off = base[1]
                width = {"strb": 1, "strh": 2}.get(mn, 8 if ops[0][0] in "xd" else (16 if ops[0][0] == "q" else 4))
                vals = [("const", 0) if reg(o) == "zr" else (("fp", o) if o[0] in "sdq" else st.get(reg(o)))
                        for o in ops[:2 if mn == "stp" else 1]]
                for n_, v in enumerate(vals):
                    events.append(("store", off + n_ * width, width, v))
            elif mn == "bl":
                t = imm(ops[0])
                x0 = st.get(0)
                if not x0 or x0[0] != "this":
                    raise ValueError
                events.append(("call", x0[1], t, [st.get(r) for r in (1, 2, 3)]))
                for r in list(st):
                    if isinstance(r, int) and r <= 18:
                        st.pop(r)
            elif mn == "cmp":
                last_cmp = (reg(ops[0]), reg(ops[1]))
            elif mn in ("cbnz", "b.ne") and imm(ops[-1]) < i.address and imm(ops[-1]) >= addr:
                head = imm(ops[-1])
                body = ins[index[head]:k]
                steps = {}
                for b in body:
                    bo = [o.strip() for o in b.op_str.split(",")]
                    if b.mnemonic in ("add", "sub") and len(bo) == 3 and bo[0][1:] == bo[1][1:] and bo[2].startswith("#"):
                        steps[reg(bo[0])] = imm(bo[2]) * (1 if b.mnemonic == "add" else -1)
                if mn == "cbnz":
                    c = reg(ops[0])
                    n = (st[c][1] - steps[c]) // -steps[c]     # the count was decremented once already
                    ptrs = [r for r, s in steps.items() if r != c and st.get(r) and st[r][0] == "this"]
                    p = ptrs[0]
                else:
                    a_, b_ = last_cmp
                    p, e = (a_, b_) if a_ in steps else (b_, a_)
                    n = (st[e][1] - (st[p][1] - steps[p])) // steps[p]
                stride = steps[p]
                start = st[p][1] - stride
                tmpl = [(ev[1] - start,) + ev[2:] for ev in events[ev_at[head]:] if ev[0] in ("call", "store")]
                del events[ev_at[head]:]
                events.append(("loop", start, n, stride, tmpl))
                st[p] = ("this", start + n * stride)
                if mn == "cbnz":
                    st[c] = ("const", 0)
            elif mn in ("b",) and not (addr <= imm(ops[0]) < addr + fsize):
                x0 = st.get(0)
                if x0 and x0[0] == "this":
                    events.append(("call", x0[1], imm(ops[0]), [st.get(r) for r in (1, 2, 3)]))
                stop = i.address; break
            elif mn in ("ldp", "ldr") and "sp" in i.op_str:
                k += 1; continue
            else:
                raise ValueError
        except (ValueError, KeyError, TypeError, IndexError, AttributeError):
            stop = i.address
            break
        k += 1
    if show_all:
        for e in events:
            print("  ", e)
    # sizes: loops give strides; runs of one constructor give their spacing
    for e in events:
        if e[0] == "loop" and len(e[4]) == 1 and e[4][0][0] == 0 and e[4][0][1] > 0x1000:
            sizes.setdefault(e[4][0][1], e[3])
    calls = [e for e in events if e[0] == "call"]
    for a_, b_ in zip(calls, calls[1:]):
        if a_[2] == b_[2] and a_[2] not in sizes and a_[2] not in KNOWN and b_[1] > a_[1]:
            sizes[a_[2]] = b_[1] - a_[1]

    def size_of(t):
        return sizes.get(t) or KNOWN.get(t, (None, None))[1]

    def name_of(t):
        return KNOWN.get(t, ("Obj%x" % t, None))[0]

    # merge runs of equal constructors into arrays
    items = []   # (off, end, text)
    for e in events:
        if e[0] == "call":
            t, off = e[2], e[1]
            sz = size_of(t)
            if items and items[-1][3] == t and sz and items[-1][1] == off:
                o, _, _, _, n = items[-1]
                items[-1] = (o, off + sz, None, t, n + 1)
            else:
                items.append((off, off + (sz or 0), None, t, 1))
        elif e[0] == "loop":
            start, n, stride, tmpl = e[1], e[2], e[3], e[4]
            desc =", ".join(("%s@%x" % (name_of(x[1]), x[0])) if len(x) == 3 and isinstance(x[1], int) and x[1] > 0x1000
                             else "store@%x" % x[0] for x in tmpl)
            items.append((start, start + n * stride, "LOOP %d x %#x {%s}" % (n, stride, desc), None, n))
        else:
            off, width, val = e[1], e[2], e[3]
            v = ("%#x" % val[1] if val[0] == "const" else str(val)) if val else "?"
            items.append((off, off + width, "store%d = %s" % (width * 8, v), None, 1))
    if "--cpp" in args:
        # member declarations: arrays and single members by their constructors, a struct per multi-call loop,
        # stores and gaps as byte pads (the stores listed in a comment, to be turned into fields by hand)
        end, structs, lines, pend = 0, [], [], []
        for e in events:
            if e[0] == "store":
                pend.append("+%x %d=%s" % (e[1], e[2] * 8, ("%#x" % e[3][1]) if e[3] and e[3][0] == "const" else "?"))
        for off, e_, text, t, n in items:
            if text is not None and text.startswith("store"):
                continue
            if off > end:
                lines.append("    unsigned char pad%x[%#x];" % (end, off - end))
            if text is None:
                lines.append("    %s m%x%s;" % (name_of(t), off, "[%d]" % n if n > 1 else ""))
            else:
                ev = next(x for x in events if x[0] == "loop" and x[1] == off)
                tmpl = ev[4]
                if len(tmpl) == 1 and tmpl[0][0] == 0:
                    lines.append("    %s a%x[%d];" % (name_of(tmpl[0][1]), off, ev[2]))
                else:
                    sname = "Elem%x" % off
                    body, pos = [], 0
                    for x in tmpl:
                        if x[0] > pos:
                            body.append("    unsigned char pad%x[%#x];" % (pos, x[0] - pos))
                        body.append("    %s m%x;" % (name_of(x[1]), x[0]))
                        pos = x[0] + (size_of(x[1]) or 0)
                    if pos < ev[3]:
                        body.append("    unsigned char pad%x[%#x];" % (pos, ev[3] - pos))
                    structs.append("struct %s {\n%s\n};" % (sname, "\n".join(body)))
                    lines.append("    %s a%x[%d];" % (sname, off, ev[2]))
            end = max(end, e_)
        print("\n\n".join(structs))
        print("// stores: " + ", ".join(pend))
        print("\n".join(lines))
        return
    end = 0
    for off, e_, text, t, n in items:
        gap = off - end
        g = ("gap %#x" % gap) if gap > 0 else ("OVERLAP %#x" % -gap if gap < 0 and text and not text.startswith("store") else "")
        if text is None:
            sz = size_of(t)
            text = "%s%s%s" % (name_of(t), "[%d]" % n if n > 1 else "", "" if sz else " (size ?)")
        print("%-12s %8x  %s" % (g, off, text))
        end = max(end, e_) if e_ else off
    print("stopped at %x (%d of %d instructions modelled)" % (stop or 0, index.get(stop, len(ins)), len(ins)))


if __name__ == "__main__":
    main()
