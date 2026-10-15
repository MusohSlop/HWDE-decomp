"""argfix.py IN.cpp OUT.cpp ADDR [CALLEE...]: give back the `this`+offset argument the generator dropped from calls
written `callee_X();` (every callee declared without parameters when none is named). For each such callee the original's call sites are read in order (a linear pass over the
function that follows mov/movk/add/mov-register into x0 from the incoming `this`), and the N-th call in the
source gets `reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + OFF)`; its declaration becomes
`void callee_X(long);`. Fails (exit 1, nothing written) when a call site's x0 is not `this`+constant or the
counts differ. Prints the offsets."""
import os, re, sys, csv
M = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))  # the matching/ folder
sys.path.insert(0, os.path.join(M, "tools"))
sys.path.insert(0, os.path.join(os.path.dirname(M), ".tools", "python"))
import capstone, check_obj, check
src, out, addr = sys.argv[1], sys.argv[2], int(sys.argv[3], 16) & 0xffffffff
callees = [int(x, 16) & 0xffffffff for x in sys.argv[4:]]
if not callees:  # every callee declared without parameters
    callees = sorted({int(x, 16) for x in re.findall(r"^\S[^\n(]* callee_([0-9a-f]+)\(\);", open(src, encoding="utf-8").read(), re.M)})
    if not callees:
        print("no zero-argument callees")
        open(out, "w", encoding="utf-8", newline="\n").write(open(src, encoding="utf-8").read())
        sys.exit(0)
size = next(int(r["Size"]) for r in csv.DictReader(open(os.path.join(M, "data", "functions.csv"), newline=""))
            if check.address(r["Address"]) == addr)
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
code = check_obj.IMAGE.read_bytes()[addr:addr + size]
regs = {"x0": ("this", 0)}
sites = {c: [] for c in callees}
X = lambda r: "x" + r[1:] if r[0] in "wx" else r


def imm(s):
    s = s.strip().lstrip("#")
    return int(s, 0)


for i in md.disasm(code, addr):
    m, ops = i.mnemonic, [o.strip() for o in i.op_str.split(",")]
    if m == "mov" and len(ops) == 2:
        if ops[1].startswith("#"):
            regs[X(ops[0])] = ("const", imm(ops[1]) & (0xffffffff if ops[0][0] == "w" else (1 << 64) - 1))
        else:
            regs[X(ops[0])] = regs.get(X(ops[1]))
    elif m == "movk" and len(ops) >= 2:
        v = regs.get(X(ops[0]))
        sh = int(ops[2].split("#")[1], 0) if len(ops) > 2 and "lsl" in ops[2] else 0
        regs[X(ops[0])] = ("const", (v[1] & ~(0xffff << sh)) | (imm(ops[1]) << sh)) if v and v[0] == "const" else None
    elif m in ("add", "sub") and len(ops) >= 3:
        a = regs.get(X(ops[1]))
        if ops[2].startswith("#"):
            b = ("const", imm(ops[2]) << (12 if len(ops) > 3 and "lsl #12" in ops[3] else 0))
        else:
            b = regs.get(X(ops[2]))
        if a and b and a[0] == "this" and b[0] == "const":
            regs[X(ops[0])] = ("this", a[1] + b[1] if m == "add" else a[1] - b[1])
        else:
            regs[X(ops[0])] = None
    elif m in ("bl", "blr", "b"):
        if m in ("bl", "b") and int(ops[0].lstrip("#"), 16) & 0xffffffff in sites:  # calls and tail calls
            sites[int(ops[0].lstrip("#"), 16) & 0xffffffff].append(regs.get("x0"))
        if m != "b":
            for k in range(19):
                regs.pop("x%d" % k, None)
    elif m in ("ldr", "ldp", "ldrb", "ldrh", "ldrsw", "ldur", "ldrsb", "ldrsh") and ops:
        regs[X(ops[0])] = None
        if m == "ldp":
            regs[X(ops[1])] = None
t = open(src, encoding="utf-8").read()
for c in callees:
    name = "callee_%x" % c
    CALL = re.compile(r"^(\s+(?:return )?)%s\(\);" % name, re.M)
    calls = len(CALL.findall(t))
    offs = sites[c]
    print(name, "calls", calls, "sites", [("+%#x" % s[1]) if s and s[0] == "this" else str(s) for s in offs])
    if calls != len(offs) or any(not s or s[0] != "this" for s in offs):
        sys.exit("cannot fix %s" % name)
    it = iter(offs)
    t = CALL.sub(lambda m_: "%s%s(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + %#x));" % (m_.group(1), name, next(it)[1]), t)
    t = re.sub(r"^\S[^\n(]* %s\(\);" % name, "void %s(long);" % name, t, flags=re.M)
open(out, "w", encoding="utf-8", newline="\n").write(t)
