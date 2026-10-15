"""Turn the generator's source of a constructor-like function into a class with members.

usage: ctor2class.py GEN.cpp ADDR OUT.cpp [--name CLASS] [--single-arrays]
Prints the --map arguments for try.py. Members: one-argument calls on this+off are member objects (consecutive
equal-stride calls become single members, loops become arrays), stores are initialised fields, a LayoutHandle
is recognised from its vtable/-1/0 stores.
"""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
WORK = _os.path.join(M, "build", "s3")  # scratch files
_os.makedirs(WORK, exist_ok=True)
import re, sys, json, os, argparse, collections

ap = argparse.ArgumentParser()
ap.add_argument("gen"); ap.add_argument("addr"); ap.add_argument("out")
ap.add_argument("--name"); ap.add_argument("--handle-got", default="c22f00")
ap.add_argument("--prefix", action="store_true", help="members from the leading statements, the rest is the ctor body")
a = ap.parse_args()
addr = int(a.addr, 16)
src = open(a.gen, encoding="utf-8").read()
man = json.load(open(os.path.join(M, "data/units.json"), encoding="utf-8-sig"))
byaddr = collections.defaultdict(list)
for n, v in man["symbols"].items():
    byaddr[int(v, 16) & 0xffffffff].append(n)
for u in man["units"].values():
    for n, v in u["functions"].items():
        byaddr[int(v, 16) & 0xffffffff].append(n)

KNOWN = {0x1ef52c: ("LayoutSprite", 0x48), 0x1f0140: ("LayoutFrame", 0x88)}


def class_for(t):
    if t in KNOWN:
        return KNOWN[t]
    for n in byaddr.get(t, []):
        m = re.fullmatch(r"_ZN(\d+)(\w+?)C[12]Ev", n)
        if m and int(m.group(1)) == len(m.group(2)):
            return m.group(2), None
    return "Obj%x" % t, None


# struct fields of p0
fn = re.search(r"// 0x71%08x\n(\w[\w\s\*]*?) call_%x\(([^)]*)\) \{\n(.*?)\n\}\n" % (addr, addr), src, re.S)
if not fn:
    sys.exit("function not found")
params = [p.strip() for p in fn.group(2).split(",")]
argstruct = re.match(r"(\w+)\* p0", params[0])
fields = {}
elems = {}
for sm in re.finditer(r"struct (\w+) \{\n(.*?)\n\};", src, re.S):
    body = sm.group(2)
    if sm.group(1).startswith("Elem"):
        pm = re.search(r"pad0\[0x([0-9a-f]+)\]", body)
        elems[sm.group(1)] = int(pm.group(1), 16) if pm else None
    if argstruct and sm.group(1) == argstruct.group(1):
        for fm in re.finditer(r"^\s+([\w\s\*]+?) field_([0-9a-f]+);", body, re.M):
            fields[int(fm.group(2), 16)] = fm.group(1).strip()

body = fn.group(3).split("\n")
ev = []   # (kind, off, ...)
OFF = r"(?:reinterpret_cast<long>\(reinterpret_cast<unsigned char\*>\(p0\) \+ 0x([0-9a-f]+)\)|p0 \+ static_cast<unsigned long>\(static_cast<unsigned int>\(0x([0-9a-f]+)\)\)|p0 \+ 0x([0-9a-f]+)|reinterpret_cast<long>\(p0\)|p0)"
i = 0
bad = []
alias = {}
while i < len(body):
    l = body[i].strip()
    for an, ao in alias.items():
        l = re.sub(r"\b%s\b" % an, "p0 + 0x%x" % ao, l)
    m = re.fullmatch(r"long (a\d+) = reinterpret_cast<long>\(reinterpret_cast<unsigned char\*>\(p0\) \+ 0x([0-9a-f]+)\);", l)
    if m:
        alias[m.group(1)] = int(m.group(2), 16)
        i += 1; continue
    m = re.fullmatch(r"(?:void\* c\d+ = )?memset\(reinterpret_cast<void\*>\((?:reinterpret_cast<long>\(reinterpret_cast<unsigned char\*>\(p0\) \+ 0x([0-9a-f]+)\)|p0)\), (0|0xff|-1), (?:static_cast<unsigned long>\(static_cast<unsigned int>\()?(0x[0-9a-f]+|\d+)\)*;", l)
    if m:
        ev.append(("memset", int(m.group(1) or "0", 16), int(m.group(3), 0), m.group(2)))
        i += 1; continue
    m = re.fullmatch(r"(?:(?:int|long|void\*) c\d+ = |return )?callee_([0-9a-f]+)\(" + OFF + r"((?:, -?(?:0x[0-9a-f]+|\d+))*)\);", l)
    if m:
        off = next((int(g, 16) for g in m.groups()[1:4] if g), 0)
        cargs = [x.strip() for x in m.group(5).split(",") if x.strip()]
        ev.append(("call", off, int(m.group(1), 16), cargs))
        i += 1; continue
    m = re.fullmatch(r"p0->field_([0-9a-f]+) = (.*);", l)
    if m:
        ev.append(("store", int(m.group(1), 16), m.group(2)))
        i += 1; continue
    m = re.fullmatch(r"(Elem\w+)\* (r\d+) = reinterpret_cast<\1\*>\(p0\);", l)
    if m:
        j = i + 1
        blk = []
        while j < len(body) and not body[j].strip().startswith("} while"):
            blk.append(body[j].strip()); j += 1
        m1 = re.fullmatch(r"long (i\d+) = 0;", blk[0]) if blk else None
        calls = [re.fullmatch(r"(?:(?:int |long )?c\d+ = )?callee_([0-9a-f]+)\(reinterpret_cast<long>\(reinterpret_cast<unsigned char\*>\(&%s\[%s\]\)(?: \+ 0x([0-9a-f]+))?\)\);" % (m.group(2), m1.group(1)), x) for x in blk] if m1 else []
        calls = [c for c in calls if c]
        rest = [x for x in blk[1:] if not re.fullmatch(r"(?:int|long) c\d+;|do \{|i\d+ = i\d+ \+ 1;|(?:(?:int |long )?c\d+ = )?callee_.*", x)]
        m3 = re.fullmatch(r"\} while \(%s != 0x([0-9a-f]+)\);" % m1.group(1), body[j].strip()) if m1 and j < len(body) else None
        if m1 and len(calls) == 1 and m3 and not rest:
            m2 = calls[0]
            ev.append(("loop", int(m2.group(2) or "0", 16), int(m2.group(1), 16), int(m3.group(1), 16), elems[m.group(1)]))
            i = j + 1; continue
    m = re.fullmatch(r"long (r\d+) = (?:p0|reinterpret_cast<long>\(reinterpret_cast<unsigned char\*>\(p0\) \+ 0x([0-9a-f]+)\));", l)
    if m and i + 9 < len(body):
        blk = [x.strip() for x in body[i + 1:i + 10]]
        base0 = int(m.group(2) or "0", 16)
        m1 = re.fullmatch(r"long (r\d+) = 0x([0-9a-f]+);", blk[0])
        m2 = re.fullmatch(r"(?:(?:int |long )?c\d+ = )?callee_([0-9a-f]+)\(%s(?: \+ 0x([0-9a-f]+))?\);" % m.group(1), blk[2])
        m3 = re.fullmatch(r"long next_%s = %s \+ 0x([0-9a-f]+);" % (m.group(1), m.group(1)), blk[3])
        if m1 and m2 and m3 and blk[1] == "do {":
            total = int(m1.group(2), 16); stride = int(m3.group(1), 16)
            ev.append(("loop", base0 + int(m2.group(2) or "0", 16), int(m2.group(1), 16), total // stride, stride))
            j = i + 1
            while not body[j].strip().startswith("} while"):
                j += 1
            i = j + 1; continue
    if l.startswith("return c") or l == "return;" or l == "":
        i += 1; continue
    if a.prefix:
        break
    bad.append(l)
    i += 1
rest_body = body[i:] if a.prefix else []
# drop a trailing return of the incidental value
while rest_body and (not rest_body[-1].strip() or re.fullmatch(r"\s*return [^;]*;", rest_body[-1])):
    mret = re.fullmatch(r"(\s*)return ((?:callee\d*_[0-9a-f]+|\w+->slot_\d+)\(.*\));", rest_body[-1])
    if mret:
        rest_body[-1] = mret.group(1) + mret.group(2) + ";"
        break
    rest_body.pop()
if bad:
    print("UNHANDLED:"); [print("   ", b) for b in bad[:20]]
    sys.exit(1)

# LayoutHandle: vtable store of the handle GOT at X, -1 at X+8, zeros at X+0x10 (int) or X+0x10/X+0x12 (shorts)
stores = {e[1]: e for e in ev if e[0] == "store"}
handles = set()
vt_own = None
for e in ev:
    if e[0] == "store":
        g = re.fullmatch(r"reinterpret_cast<long>\(reinterpret_cast<unsigned char\*>\(gGlobal([0-9a-f]+)_\w+\) \+ 0x10\)", e[2])
        if g and g.group(1) == a.handle_got and stores.get(e[1] + 8, (0, 0, ""))[2] == "-1":
            handles.add(e[1])
        elif g and e[1] == 0:
            vt_own = int(g.group(1), 16)
hcover = set()
for h in handles:
    hcover |= {h, h + 8, h + 0x10, h + 0x12}

members = {}   # off -> (decl, size, init)
order_calls = []
for e in ev:
    if e[0] == "call":
        cls, size = class_for(e[2])
        order_calls.append(e[1])
        members[e[1]] = ["obj", cls, size, e[2], e[3]]
    elif e[0] == "loop":
        cls, size = class_for(e[2])
        order_calls.append(e[1])
        members[e[1]] = ["arr", cls, e[4], e[2], e[3]]
    elif e[0] == "memset":
        members[e[1]] = ["zero", e[2], e[3]]
    elif e[0] == "store" and e[1] not in hcover and not (e[1] == 0 and vt_own):
        t = fields.get(e[1], "long")
        v = e[2]
        if v == "p1":
            members[e[1]] = ["field", t, None, "p1"]
        else:
            members[e[1]] = ["field", t, None, v]
for h in handles:
    members[h] = ["handle"]
if order_calls != sorted(order_calls):
    print("WARNING: member calls are not in address order")
# sizes of unknown classes from spacing
offs = sorted(members)
sizes = {}
for k, o in enumerate(offs):
    mbr = members[o]
    if mbr[0] == "obj" and mbr[2] is None:
        nxt = offs[k + 1] if k + 1 < len(offs) else None
        sizes.setdefault(mbr[1], set()).add((nxt - o) if nxt else None)
csize = {}
for c, s in sizes.items():
    s2 = {x for x in s if x}
    csize[c] = min(s2) if s2 else 8
TSZ = {"int": 4, "unsigned int": 4, "long": 8, "unsigned long": 8, "short": 2, "unsigned short": 2,
       "unsigned char": 1, "signed char": 1, "char": 1, "float": 4, "double": 8, "bool": 1}
def msize(mbr):
    if mbr[0] == "obj":
        return mbr[2] or csize[mbr[1]]
    if mbr[0] == "arr":
        return mbr[2] * mbr[4]
    if mbr[0] == "handle":
        return 0x18
    if mbr[0] == "zero":
        return mbr[1]
    return 8 if mbr[1].endswith("*") else TSZ.get(mbr[1], 8)

name = a.name or "Class%x" % addr
out = []
decl_classes = {}
for o in offs:
    mbr = members[o]
    if mbr[0] in ("obj", "arr"):
        sz = mbr[2] if mbr[0] == "arr" else msize(mbr)
        decl_classes[mbr[1]] = (mbr[3], sz, len(mbr[4]) if mbr[0] == "obj" else 0)
maps = []
for cls, (t, sz, na) in sorted(decl_classes.items()):
    ps = ", ".join(["int"] * na)
    out.append(f"class {cls} {{\npublic:\n    {cls}({ps});{' ' * max(1, 66 - len(cls) - len(ps))}// 0x71{t:08x}\n    unsigned char pad[{sz:#x}];\n}};\n")
    maps.append(f"_ZN{len(cls)}{cls}C1E{'i' * na or 'v'}=0x71{t:08x}")
if handles:
    out.insert(0, """struct HandleState {
    long id;                  // +08
    short a;                  // +10
    short b;                  // +12

    HandleState() : id(-1), a(0), b(0) {}
};

// Layout handle; its vtable lives in the effect manager unit (GOT 0x7100c22f00).
class LayoutHandle : public HandleState {
public:
    virtual ~LayoutHandle();
    virtual void v10();
    virtual void release(void* root); // +18
};
""")
out.append(f"class {name} {{\npublic:\n    {name}({'void* p1' if any(m[0]=='field' and m[3]=='p1' for m in members.values()) else ''});")
if vt_own:
    out.append("    virtual void v00();")
    maps.append(f"got:_ZTV{len(name)}{name}=0x71{vt_own:08x}")
out.append("")
pos = 8 if vt_own else 0
inits = []
body_stmts = []
k = 0
offs_list = offs
idx = 0
while idx < len(offs_list):
    o = offs_list[idx]
    mbr = members[o]
    if o < pos:
        print(f"WARNING: overlap at {o:#x} (pos {pos:#x})")
        idx += 1; continue
    if o > pos:
        out.append(f"    unsigned char pad{pos:x}[{o - pos:#x}];")
    if mbr[0] == "obj":
        out.append(f"    {mbr[1]} m{o:x};")
        if mbr[4]:
            inits.append(f"m{o:x}({', '.join(mbr[4])})")
    elif mbr[0] == "arr":
        out.append(f"    {mbr[1]} a{o:x}[{mbr[4]}];")
    elif mbr[0] == "handle":
        out.append(f"    LayoutHandle h{o:x};")
    elif mbr[0] == "zero":
        out.append(f"    unsigned char z{o:x}[{mbr[1]:#x}];")
        if mbr[2] == "0":
            inits.append(f"z{o:x}()")
        else:
            body_stmts.append(f"__builtin_memset(z{o:x}, {mbr[2]}, sizeof(z{o:x}));")
    else:
        t = mbr[1]
        out.append(f"    {t} f{o:x};" if not t.endswith("*") else f"    {t[:-1].strip()}* f{o:x};")
        inits.append(f"f{o:x}({mbr[3]})")
    pos = o + msize(mbr)
    idx += 1
out.append("};\n")
has_p1 = any(m[0] == "field" and m[3] == "p1" for m in members.values()) or (a.prefix and any(re.search(r"\bp1\b", x) for x in rest_body))
if a.prefix and rest_body:
    pt = argstruct.group(1) + "*" if argstruct else "long"
    body_stmts.append(f"{pt} p0 = reinterpret_cast<{pt}>(this);")
    for an, ao in alias.items():
        if any(re.search(r"\b%s\b" % an, x) for x in rest_body):
            body_stmts.append(f"long {an} = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + {ao:#x});")
    body_stmts += [x[4:] if x.startswith("    ") else x for x in rest_body]
ctor_line = f"{name}::{name}({'void* p1' if has_p1 else ''})" + (f"\n    : {', '.join(inits)}" if inits else "") + (" {\n" + "".join("    %s\n" % s for s in body_stmts) + "}\n" if body_stmts else " {}\n")
out.append(ctor_line)
for k_, l_ in enumerate(out):
    if l_.startswith(f"class {name} {{"):
        out[k_] = l_.replace(f"    {name}();", f"    {name}({'void* p1' if has_p1 else ''});")
text = "\n".join(out)
if a.prefix:
    pre = src[:src.index("// 0x71%08x\n" % addr)]
    pre = "\n".join(l for l in pre.split("\n") if not l.startswith("// Small functions") and not l.startswith("// locals in") and not l.startswith("// address and"))
    text = pre + "\n" + text
open(a.out, "w", encoding="utf-8", newline="\n").write(text)
print("name", f"_ZN{len(name)}{name}C2E" + ("Pv" if has_p1 else "v"))
print("maps", " ".join("--map " + x for x in maps))
