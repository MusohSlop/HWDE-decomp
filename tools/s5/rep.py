"""rep.py SRC DST OLD NEW [OLD NEW ...]: copy SRC to DST with each OLD replaced by NEW (exact text, \\n for a
newline); stops with an error when an OLD is not found. DST may equal SRC. For quick source variants."""
import sys
src, dst, pairs = sys.argv[1], sys.argv[2], sys.argv[3:]
t = open(src, encoding="utf-8").read()
for old, new in zip(pairs[0::2], pairs[1::2]):
    old, new = old.replace("\\n", "\n"), new.replace("\\n", "\n")
    if old not in t:
        sys.exit("not found: " + old)
    t = t.replace(old, new)
open(dst, "w", encoding="utf-8", newline="\n").write(t)
