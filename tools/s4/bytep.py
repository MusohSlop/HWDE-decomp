"""bytep.py IN.cpp OUT.cpp ADDR [PARAM...]: rewrite a generated function's `long pN` parameters (default p0) as byte pointers,
so `pN + C` becomes a byte-pointer GEP (constant offsets are not hoisted) instead of integer arithmetic."""
import re, sys
src, out, addr = sys.argv[1:4]
params = sys.argv[4:] or ["p0"]
t = open(src, encoding="utf-8").read()
m = re.search(r"^(\w[\w\s\*]*?) call_%s\(([^)]*)\) \{\n(.*?)\n\}\n" % addr, t, re.S | re.M)
sig, body = m.group(2), m.group(3)
aliases = set(params)
for p in params:
    sig = re.sub(r"\blong %s\b" % p, "unsigned char* %s" % p, sig)
# locals initialised from a byte-pointer parameter become byte pointers too
for mm in re.finditer(r"long (r\d+) = (%s);" % "|".join(params), body):
    aliases.add(mm.group(1))
changed = True
while changed:
    changed = False
    for mm in re.finditer(r"long (next_r\d+) = (r\d+) \+ ", body):
        if mm.group(2) in aliases and mm.group(1) not in aliases:
            aliases.add(mm.group(1)); changed = True
names = "|".join(sorted(aliases, key=len, reverse=True))
body = re.sub(r"long (%s) = " % names, r"unsigned char* \1 = ", body)
CU = r"static_cast<unsigned long>\(static_cast<unsigned int>\((0x[0-9a-f]+)\)\)"
body = re.sub(r"\(\b(%s) \+ %s\) \+ (\w+)" % (names, CU), r"reinterpret_cast<long>(\1 + \2 + \3)", body)
body = re.sub(r"\b(%s) \+ %s" % (names, CU), r"reinterpret_cast<long>(\1 + \2)", body)
# remaining `alias + C` used as a value (not inside the declarations of next_ pointers)
body = re.sub(r"(?<!= )(?<![\w>(])\b(%s) \+ (0x[0-9a-f]+)\b(?!\))" % names, r"reinterpret_cast<long>(\1 + \2)", body)
body = re.sub(r"(\(|, )\b(%s) \+ (0x[0-9a-f]+)\)" % names, r"\1reinterpret_cast<long>(\2 + \3))", body)
body = re.sub(r"(\(|, )\b(%s)\)" % "|".join(params), r"\1reinterpret_cast<long>(\2))", body)
body = body.replace("reinterpret_cast<void*>(reinterpret_cast<long>(", "reinterpret_cast<void*>((")
t = t[:m.start(2)] + sig + t[m.end(2):m.start(3)] + body + t[m.end(3):]
open(out, "w", encoding="utf-8", newline="\n").write(t)
