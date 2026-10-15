"""handlify.py IN.cpp OUT.cpp [GOT=c22f00] [--array]: in generated source, replace each LayoutHandle store group
(vtable at X, -1 at X+8, zeros at X+0x10/X+0x12 or X+0x10 int) with a placement new of LayoutHandle at the
position of the group's first store. Adds the LayoutHandle declarations and a placement operator new."""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
WORK = _os.path.join(M, "build", "s3")  # scratch files
_os.makedirs(WORK, exist_ok=True)
import re, sys
src, out = sys.argv[1], sys.argv[2]
got = next((a for a in sys.argv[3:] if not a.startswith("--")), "c22f00")
t = open(src, encoding="utf-8").read()
lines = t.split("\n")
ST = re.compile(r"^\s+(\w+)->field_([0-9a-f]+) = (.*);$")
vt = {}
for k, l in enumerate(lines):
    m = ST.match(l)
    if m and re.fullmatch(r"reinterpret_cast<long>\(reinterpret_cast<unsigned char\*>\(gGlobal%s_\w+\) \+ 0x10\)" % got, m.group(3)):
        vt[(m.group(1), int(m.group(2), 16))] = k
handles = {}
for (base, x), k in vt.items():
    grp = {}
    for j, l in enumerate(lines):
        m = ST.match(l)
        if m and m.group(1) == base:
            o = int(m.group(2), 16)
            if o == x + 8 and m.group(3) == "-1" or o in (x + 0x10, x + 0x12) and m.group(3) == "0" or o == x:
                grp[o] = j
    if x + 8 in grp and x + 0x10 in grp:
        handles[(base, x)] = grp
drop = set()
first = {}
for (base, x), grp in handles.items():
    drop |= set(grp.values())
    first[min(grp.values())] = (base, x)
res = []
for k, l in enumerate(lines):
    if k in first:
        base, x = first[k]
        res.append(f"    new (reinterpret_cast<unsigned char*>({base}) + {x:#x}) LayoutHandle;")
    if k in drop:
        continue
    res.append(l)
t = "\n".join(res)
decl = """inline void* operator new(unsigned long, void* where) noexcept { return where; }

struct HandleState {
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

"""
if "operator new(unsigned long, void* where)" in t:
    decl = decl.split("\n", 2)[2]
if not handles or "struct HandleState {" in t:
    decl = ""
# insert the declarations before the first struct/class definition
m = re.search(r"^(struct|class) ", t, re.M)
t = t[:m.start()] + decl + t[m.start():]
open(out, "w", encoding="utf-8", newline="\n").write(t)
print(len(handles), "handles")
