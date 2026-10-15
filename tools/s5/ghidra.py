"""ghidra.py ADDR [--base]: print Ghidra's pseudocode of one function from decompiled/update/main/main.c (the
committed export; --base for the 1.0.0 export). The function is found by its FUN_71xxxxxxxx name or, for named
functions, by the address comment Ghidra puts above it; printing stops at the closing brace in column 0."""
import os, re, sys
M = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))  # the matching/ folder
ROOT = os.path.dirname(M)
rev = "base" if "--base" in sys.argv else "update"
args = [a for a in sys.argv[1:] if not a.startswith("--")]
a = int(args[0], 16) & 0xffffffff
path = os.path.join(ROOT, "decompiled", rev, "main", "main.c")
text = open(path, encoding="utf-8", errors="replace").read()
name = "FUN_71%08x" % a
m = re.search(r"^[^\n;]*\b%s\(" % name, text, re.M)
if not m:
    m = re.search(r"^// .*\b71%08x\b.*\n(?:[^\n]*\n){0,3}?([^\n;]*\()" % a, text, re.M)
if not m:
    sys.exit("not found: " + name)
start = text.rfind("\n\n", 0, m.start()) + 2
end = text.find("\n}\n", m.start())
print(text[start:end + 3])
