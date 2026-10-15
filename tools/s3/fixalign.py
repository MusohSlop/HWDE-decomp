"""fixalign.py IN.cpp OUT.cpp: in generated structs, a field declared at an offset its type's alignment would not
give (a long at +...4, say, which C++ would pad to the next multiple of 8) gets __attribute__((packed)), so it
stays at the offset the generator meant (the `// +OFF` comment). Prints the fields it changed."""
import re, sys
SIZES = {"long": 8, "unsigned long": 8, "double": 8, "int": 4, "unsigned int": 4, "float": 4, "short": 2,
         "unsigned short": 2}
src, out = sys.argv[1], sys.argv[2]
t = open(src, encoding="utf-8").read()
FIELD = re.compile(r"^(\s+)([\w\s\*]+?) (field_[0-9a-f]+);(\s*// \+([0-9a-f]+))$", re.M)
n = 0
def rep(m):
    global n
    ty, off = m.group(2).strip(), int(m.group(5), 16)
    size = 8 if ty.endswith("*") else SIZES.get(ty)
    if size and off % size:
        n += 1
        print("packed", ty, m.group(3), hex(off))
        return f"{m.group(1)}{m.group(2)} {m.group(3)} __attribute__((packed));{m.group(4)}"
    return m.group(0)
t = FIELD.sub(rep, t)
open(out, "w", encoding="utf-8", newline="\n").write(t)
print(n, "fields")
