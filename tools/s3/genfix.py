"""genfix.py IN.cpp OUT.cpp [fix ...]: source rewrites on generated code.
fixes:
  loops    index loops `do { callee(&rN[i] + B); i++; } while (i != N)` over a p0-based element array become a
           byte-pointer loop from p0+B to p0+B+N*S (Clang's array-construction loop, which counts down the bytes)
  panes    `new` of a PanelPane (operator new 0x5d4380 of 0x180 bytes, PaneBase ctor, vtable c22f68, three null
           fields) becomes `new PanelPane` from event/layout_panes.h
  handles  LayoutHandle store groups become placement new (see handlify.py)
"""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
WORK = _os.path.join(M, "build", "s3")  # scratch files
_os.makedirs(WORK, exist_ok=True)
import re, sys, subprocess, os
src, out = sys.argv[1], sys.argv[2]
fixes = sys.argv[3:] or ["loops", "panes", "handles"]
t = open(src, encoding="utf-8").read()
SP = os.path.dirname(os.path.abspath(__file__))

if "loops" in fixes:
    elems = {m.group(1): int(m.group(2), 16) for m in re.finditer(r"struct (Elem\w+) \{\n    unsigned char pad0\[0x([0-9a-f]+)\];\n\};", t)}
    pat = re.compile(r"(?P<ind>[ ]+)(?P<et>Elem\w+)\* (?P<r>r\d+) = reinterpret_cast<(?P=et)\*>\(p0\);\n"
                     r"(?P=ind)long (?P<i>i\d+) = 0;\n"
                     r"(?P<pre>(?:(?P=ind)(?:int|long|void\*) c\d+;\n)?)"
                     r"(?P=ind)do \{\n"
                     r"(?P=ind)    (?P<asg>(?:c\d+ = )?)callee_(?P<t>[0-9a-f]+)\(reinterpret_cast<long>\(reinterpret_cast<unsigned char\*>\(&(?P=r)\[(?P=i)\]\)(?: \+ 0x(?P<b>[0-9a-f]+))?\)\);\n"
                     r"(?P=ind)    (?P=i) = (?P=i) \+ 1;\n"
                     r"(?P=ind)\} while \((?P=i) != 0x(?P<n>[0-9a-f]+)\);\n")
    KNOWN = {"1ef52c": "LayoutSprite", "1f0140": "LayoutFrame"}
    used = {}
    def rep(m):
        s = elems[m.group("et")]
        b = int(m.group("b") or "0", 16); n = int(m.group("n"), 16)
        ind = m.group("ind")
        cls = KNOWN.get(m.group("t"), "Ctor_" + m.group("t"))
        used[cls] = (m.group("t"), s)
        return f"{ind}new (reinterpret_cast<unsigned char*>(p0) + {b:#x}) {cls}[{n:#x}];\n"
    t, k = pat.subn(rep, t)
    print("loops", k)
    if used:
        decl = "inline void* operator new(unsigned long, void* where) noexcept { return where; }\ninline void* operator new[](unsigned long, void* where) noexcept { return where; }\n\n"
        for cls, (tt, s) in sorted(used.items()):
            decl += f"class {cls} {{\npublic:\n    {cls}();{' ' * max(1, 68 - len(cls))}// 0x71{tt:0>8}\n    unsigned char pad[{s:#x}];\n}};\n\n"
        mm = re.search(r"^(struct|class|extern) ", t, re.M)
        t = t[:mm.start()] + decl + t[mm.start():]

if "panes" in fixes:
    pat = re.compile(r"(?P<ind>[ ]+)(?P<ct>C\w+)\* (?P<c>c\d+) = static_cast<(?P=ct)\*>\(callee_5d4380\(0x180\)\);\n"
                     r"(?:(?P=ind)(?P=ct)\* (?P<m>m\d+);\n)?"
                     r"(?P=ind)if \((?P=c) != 0\) \{\n"
                     r"(?P=ind)    callee_5dc664\((?P=c)\);\n"
                     r"(?P<body>(?:(?P=ind)    (?P=c)->field_(?:0|160|168|170) = [^;]+;\n){4})"
                     r"(?:(?P=ind)    (?P=m) = (?P=c);\n"
                     r"(?P=ind)\} else \{\n"
                     r"(?P=ind)    (?P=m) = nullptr;\n)?"
                     r"(?P=ind)\}\n")
    def rep2(m):
        return f"{m.group('ind')}PanelPane* {m.group('m') or m.group('c')} = new PanelPane;\n"
    t, k = pat.subn(rep2, t)
    print("panes", k)
    if k and '#include "event/layout_panes.h"' not in t:
        mm = re.search(r"^(struct|class|extern|void|int|long|unsigned|float|namespace) ", t, re.M)
        t = t[:mm.start()] + '#include "event/layout_panes.h"\n\n' + t[mm.start():]

open(out, "w", encoding="utf-8", newline="\n").write(t)
if "handles" in fixes:
    r = subprocess.run([sys.executable, "-B", "-I", os.path.join(SP, "handlify.py"), out, out], capture_output=True, text=True)
    print(r.stdout.strip(), r.stderr.strip())
