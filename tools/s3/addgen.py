"""addgen.py SRC.cpp ADDR SYM.json UNIT [NOTE]: append a generated-style function (its declarations and body) to a unit,
register its symbols and the function, then build the unit and run autosym. NOTE goes in a comment over the function."""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
WORK = _os.path.join(M, "build", "s3")  # scratch files
_os.makedirs(WORK, exist_ok=True)
import sys, os, json, re, subprocess
src, addr, symf, unit = sys.argv[1:5]
note = sys.argv[5] if len(sys.argv) > 5 else ""
a = int(addr, 16)
t = open(src, encoding="utf-8").read()
# drop the generator's file header (comment lines at the top)
lines = t.split("\n")
k = 0
while k < len(lines) and (lines[k].startswith("//") or not lines[k].strip()):
    k += 1
body = "\n".join(lines[k:]).rstrip() + "\n"
if note:
    if ("// 0x71%08x\n" % a) in body:
        body = body.replace("// 0x71%08x\n" % a, "// 0x71%08x: %s\n" % (a, note), 1)
    else:
        body = re.sub(r"^class (Class%x) \{" % a, lambda m_: "// 0x71%08x: %s\nclass %s {" % (a, note, m_.group(1)), body, count=1, flags=re.M)
path = os.path.join(M, "src", unit)
old = open(path, encoding="utf-8").read() if os.path.exists(path) else (
    "// Large functions from generated source, fixed by hand (third session). Struct, field and callee names are\n"
    "// placeholders after the address and offset, as in the generated units. Status: matching/README.md.\n")
# callee declarations whose name and parameters are already declared with another return type get the next free
# prefix (callee2_, callee3_, ...), as gen.py does inside one unit; identical declarations are dropped
DECL = re.compile(r"^(\S[^=(]*?) (callee\d*)_([0-9a-f]+)\(([^()]*)\);(\s+// 0x71[0-9a-f]+)?$", re.M)
have = {}
for m in DECL.finditer(old):
    have.setdefault((m.group(3), m.group(4)), {})[m.group(2)] = m.group(1)
ren = {}
out_lines = []
for line in body.split("\n"):
    m = DECL.match(line)
    if m:
        key = (m.group(3), m.group(4))
        prefs = have.get(key, {})
        if prefs.get(m.group(2)) == m.group(1):
            continue                                  # same declaration already in the unit
        if m.group(2) in prefs:
            k = 2
            while ("callee%d" % k) in prefs and prefs["callee%d" % k] != m.group(1):
                k += 1
            new = "callee%d" % k
            ren[(m.group(2), m.group(3), m.group(4))] = new
            if prefs.get(new) == m.group(1):
                continue
            line = line.replace("%s_%s(" % (m.group(2), m.group(3)), "%s_%s(" % (new, m.group(3)), 1)
            prefs[new] = m.group(1)
    out_lines.append(line)
body = "\n".join(out_lines)
for (pref, t_, params), new in ren.items():
    # rename the uses: every call of pref_t_ in this function (a function only uses one overload per name)
    body = re.sub(r"\b%s_%s\(" % (pref, t_), "%s_%s(" % (new, t_), body)
    print("renamed", pref, t_, "->", new)
# extern globals already declared in the unit are dropped
EXT = re.compile(r"^extern .*;.*$", re.M)
olds = set(EXT.findall(old))
body = "\n".join(l for l in body.split("\n") if l not in olds)
# identical struct/class definitions, includes and operator new lines already in the unit are dropped; a
# different definition under a name the unit already has is an error
BLK = re.compile(r"^(?:// [^\n]*\n)*(?:struct|class|union) (\w+)(?: : [^{\n]+)? \{\n.*?^\};\n", re.M | re.S)
oldblocks = {m.group(1): m.group(0) for m in BLK.finditer(old)}
def dedupe(m):
    n = m.group(1)
    if n in oldblocks:
        strip = lambda s: "\n".join(l for l in s.split("\n") if not l.startswith("//"))
        if strip(oldblocks[n]) == strip(m.group(0)):
            return ""
        sys.exit("type %s already defined differently in the unit" % n)
    return m.group(0)
body = BLK.sub(dedupe, body)
body = "\n".join(l for l in body.split("\n")
                 if not ((l.startswith("#include") or l.startswith("inline void* operator new")) and l in old))
body = re.sub(r"\n{3,}", "\n\n", body)
open(path, "w", encoding="utf-8", newline="\n").write(old.rstrip("\n") + "\n\n" + body)
sy = json.load(open(symf, encoding="utf-8"))
py = sys.executable
run = lambda *x: subprocess.run([py, "-B", "-I", *x], cwd=M, capture_output=True, text=True)
if sy["gsyms"] or sy["imports"]:
    print(run("tools/add_symbols.py", *(sy["gsyms"] + sy["imports"])).stdout.strip())
# function symbol: find its mangled name after compiling
r = run("tools/check.py", unit)
fn = re.search(r"\b(\w+) call_%x\(" % a, body)
man = json.load(open(os.path.join(M, "data/units.json"), encoding="utf-8-sig"))
compiler = os.path.join(os.path.dirname(M), man["compiler"])
obj = os.path.join(M, "build", "addgen_tmp.o")
c = subprocess.run([compiler, *man["flags"], "-I", os.path.join(M, "include"), "-c", path, "-o", obj], capture_output=True, text=True)
if c.returncode:
    print(c.stderr[-3000:]); sys.exit(1)
sys.path.insert(0, os.path.join(M, "tools"))
import check_obj
_, _, symbols, _ = check_obj.read_elf(obj)
names = [s.name for s in symbols if not s.is_section and s.shndx != 0 and s.size and re.search(r"(?:call_|Class)%x(?![0-9a-f])" % a, s.name)]
names.sort(key=lambda n: (0 if "C2E" in n or "call_" in n else 1, n))
print("function", names)
print(run("tools/add_symbols.py", "--unit", unit, "%s=0x71%08x" % (names[0], a)).stdout.strip())
if "map" not in man["units"].get(unit, {}):
    print(run("tools/add_symbols.py", "--map", unit, ".rodata.cst4=0x710073b000", ".rodata.cst16=0x710073dff0").stdout.strip())
run("tools/check.py", unit)
print(run("tools/gen/autosym.py", unit).stdout.strip())
print(run("tools/check.py", unit).stdout.strip())
