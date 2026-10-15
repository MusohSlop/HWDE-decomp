"""onceptr.py IN.cpp OUT.cpp: in generated source, a store `p0->field_X = V;` whose address p0+X is later passed
again as `reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xX)` becomes one pointer used by both
(`long* hX = ...; *hX = V; ... reinterpret_cast<long>(hX)`). That is one value in the IR, so Clang folds the
store into a pre-indexed `str xA, [xB, #X]!` and passes xB on, as the original does where an inlined handle
destructor stores its vtable and then releases itself. Only stores at the start of a line and the next use of
the same address are rewritten. Exit code 0 (also when nothing changed); prints the number of rewrites."""
import re, sys
src, out = sys.argv[1], sys.argv[2]
t = open(src, encoding="utf-8").read()
lines = t.split("\n")
n = 0
for i, l in enumerate(lines):
    m = re.fullmatch(r"(\s+)p0->field_([0-9a-f]+) = (.+);", l)
    if not m:
        continue
    use = "reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x%s)" % m.group(2)
    for j in range(i + 1, min(i + 16, len(lines))):
        if re.search(r"p0->field_%s\b" % m.group(2), lines[j]):
            break
        if use in lines[j]:
            h = "h" + m.group(2)
            ind = m.group(1)
            lines[i] = (f"{ind}long* {h} = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x{m.group(2)});\n"
                        f"{ind}*{h} = {m.group(3)};")
            lines[j] = lines[j].replace(use, f"reinterpret_cast<long>({h})", 1)
            n += 1
            break
open(out, "w", encoding="utf-8", newline="\n").write("\n".join(lines))
print("onceptr", n)
