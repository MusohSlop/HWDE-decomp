import os as _os
GENDIR = _os.path.dirname(_os.path.abspath(__file__))
MATCHDIR = _os.path.dirname(_os.path.dirname(GENDIR))
ROOTDIR = _os.path.dirname(MATCHDIR)
import os
"""Generate small functions with calls (and forward branches) by forking symbolic execution.
Loads and used call results become named locals in their original order; x19-x28 survive calls.
usage: gen_calls.py OUT.cpp UNIT LO HI   (EXCLUDE env: comma-separated hex addresses)"""
import csv, sys, re, subprocess, json, os, struct
sys.path.insert(0, (ROOTDIR + r"\.tools\python"))
import capstone
out, unit, lo, hi = sys.argv[1], sys.argv[2], int(sys.argv[3]), int(sys.argv[4])
root = ROOTDIR
d = open(root + r"\analysis\extracted\update\decompressed\main.memory.bin", "rb").read()
rows = [r for r in csv.reader(open(root + r"\matching\data\functions.csv")) if r[0].startswith("0x")]
fnames = {int(r[0], 16) - 0x7100000000: r[3] for r in rows}
NEAR_ = bool(os.environ.get("NEARMISS"))
U = [(int(r[2]), int(r[0], 16) - 0x7100000000) for r in rows if (r[1] == "U" or (NEAR_ and r[1] == "m")) and lo <= int(r[2]) <= hi]
units = json.load(open(root + r"\matching\data\units.json", encoding="utf-8"))
taken = {int(v, 16) - 0x7100000000 for u in units["units"].values() for v in u.get("functions", {}).values()}
exclude = {int(x, 16) for x in os.environ.get("EXCLUDE", "").split(",") if x}
U = [x for x in U if (x[1] not in taken or NEAR_) and x[1] not in exclude]
only = {int(x, 16) for x in os.environ.get("ONLY", "").split(",") if x}
DEFAULT_KNOBS = set(x for x in os.environ.get("VARIANT", "").split("+") if x)
KNOB_MAP = {}
for part in os.environ.get("VARIANT_MAP", "").split(";"):
    if ":" in part:
        a_, ks = part.split(":")
        KNOB_MAP[int(a_, 16)] = set(x for x in ks.split("+") if x)
if only:
    U = [x for x in U if x[1] in only]
PLT = json.load(open(_os.path.join(GENDIR, "plt_names.json")))
# imports declared with their real signatures: mangled name -> (call name, return type, parameter types, declaration lines)
NN_DECLS = {
    "os": ["struct MutexType;", "struct EventType;", "void LockMutex(MutexType* mutex);", "void UnlockMutex(MutexType* mutex);",
           "void InitializeMutex(MutexType* mutex, bool recursive, int lockLevel);", "void FinalizeMutex(MutexType* mutex);",
           "void SignalEvent(EventType* event);", "bool TryWaitEvent(EventType* event);"],
    "oe": ["void Initialize();"],
    "util": ["void ReferSymbol(const void* symbol);"],
}
IMPORTS = {
    "_ZN2nn2os9LockMutexEPNS0_9MutexTypeE": ("nn::os::LockMutex", "void", ["nn::os::MutexType*"], "os"),
    "_ZN2nn2os11UnlockMutexEPNS0_9MutexTypeE": ("nn::os::UnlockMutex", "void", ["nn::os::MutexType*"], "os"),
    "_ZN2nn2os15InitializeMutexEPNS0_9MutexTypeEbi": ("nn::os::InitializeMutex", "void", ["nn::os::MutexType*", "bool", "int"], "os"),
    "_ZN2nn2os13FinalizeMutexEPNS0_9MutexTypeE": ("nn::os::FinalizeMutex", "void", ["nn::os::MutexType*"], "os"),
    "_ZN2nn2os11SignalEventEPNS0_9EventTypeE": ("nn::os::SignalEvent", "void", ["nn::os::EventType*"], "os"),
    "_ZN2nn2os12TryWaitEventEPNS0_9EventTypeE": ("nn::os::TryWaitEvent", "bool", ["nn::os::EventType*"], "os"),
    "_ZN2nn2oe10InitializeEv": ("nn::oe::Initialize", "void", [], "oe"),
    "_ZN2nn4util11ReferSymbolEPKv": ("nn::util::ReferSymbol", "void", ["const void*"], "util"),
}
C_PROTOS = {
    "memset": ("void*", ["void*", "int", "unsigned long"]), "memcpy": ("void*", ["void*", "const void*", "unsigned long"]),
    "memmove": ("void*", ["void*", "const void*", "unsigned long"]), "memcmp": ("int", ["const void*", "const void*", "unsigned long"]),
    "strcmp": ("int", ["const char*", "const char*"]), "strlen": ("unsigned long", ["const char*"]),
    "strcpy": ("char*", ["char*", "const char*"]), "strchr": ("char*", ["const char*", "int"]),
    "strncmp": ("int", ["const char*", "const char*", "unsigned long"]), "strncpy": ("char*", ["char*", "const char*", "unsigned long"]),
    "atan2f": ("float", ["float", "float"]), "tanf": ("float", ["float"]), "cosf": ("float", ["float"]), "sinf": ("float", ["float"]),
    "sqrtf": ("float", ["float"]), "acosf": ("float", ["float"]), "atanf": ("float", ["float"]), "asinf": ("float", ["float"]),
    "powf": ("float", ["float", "float"]), "fmodf": ("float", ["float", "float"]), "expf": ("float", ["float"]), "logf": ("float", ["float"]),
}
def import_of(target):
    nm = PLT.get("%x" % target)
    if nm in IMPORTS:
        return ("cpp", nm) + IMPORTS[nm]
    if nm in C_PROTOS:
        return ("c", nm, nm) + C_PROTOS[nm] + (None,)
    return None
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
md.detail = True

def frw(i):
    reads, writes = i.regs_access()
    def num(r):
        n = i.reg_name(r)
        mm = re.fullmatch(r"[sdqbhv](\d+)", n)
        return int(mm.group(1)) if mm else None
    return {num(r) for r in reads} - {None}, {num(r) for r in writes} - {None}

RW_FIX = [True]
BFM_FIX = [True]
# aliases of ubfm/sbfm: capstone reports the destination as read, as it does for bfm
BFM_ALIASES = {"lsl", "lsr", "asr", "ubfx", "sbfx", "ubfiz", "sbfiz", "sxtb", "sxth", "sxtw", "uxtb", "uxth"}
def rw(i):
    reads, writes = i.regs_access()
    def num(r):
        n = i.reg_name(r)
        mm = re.fullmatch(r"[wx](\d+)", n)
        return int(mm.group(1)) if mm else None
    r_, w_ = {num(r) for r in reads} - {None}, {num(r) for r in writes} - {None}
    if BFM_FIX[0] and i.mnemonic in BFM_ALIASES:
        ops_ = [o_.strip() for o_ in i.op_str.split(",")]
        md_ = re.fullmatch(r"[wx](\d+)", ops_[0]) if ops_ else None
        if md_ and not any(re.fullmatch(r"[wx]%s" % md_.group(1), o_) for o_ in ops_[1:]):
            r_.discard(int(md_.group(1)))
    if RW_FIX[0] and i.mnemonic in ("cmp", "cmn", "tst"):
        # capstone reports the first operand of a compare as written; it is only read
        mm = re.match(r"[wx](\d+)", i.op_str)
        if mm:
            w_.discard(int(mm.group(1))); r_.add(int(mm.group(1)))
    return r_, w_

class Fail(Exception):
    pass

class SpinPseudo_:
    """One instruction standing for an LL/SC compare-exchange loop (kind "spinlock_") or a piece of it ("nop_")."""
    def __init__(self, kind, first, ld=None, st=None):
        self._first, self._ld, self._st = first, ld, st
        self.mnemonic = kind
        self.address = first.address
        if kind == "spinlock_":
            lops_ = [o_.strip() for o_ in ld.op_str.split(",")]
            sops_ = [o_.strip() for o_ in st.op_str.split(",")]
            self.spin = (sops_[2].strip("[]"), sops_[1], lops_[0], sops_[0])   # base, value, loaded, status
            self.op_str = ", ".join(self.spin)
        else:
            self.op_str = ""
    def regs_access(self):
        if self.mnemonic != "spinlock_":
            return [], []
        r1, w1 = self._ld.regs_access()
        r2, w2 = self._st.regs_access()
        return list(r1) + list(r2), list(w1) + list(w2)
    def reg_name(self, r):
        return self._ld.reg_name(r)
    def __getattr__(self, n):
        return getattr(self._first, n)

def spin_rewrite_(ins):
    out_ = list(ins)
    for k_ in range(1, len(ins) - 4):
        b_, cl_, ld_, c1_, st_, c2_ = ins[k_ - 1:k_ + 5]
        if not (cl_.mnemonic == "clrex" and ld_.mnemonic in ("ldaxr", "ldxr") and st_.mnemonic in ("stlxr", "stxr")
                and c1_.mnemonic == "cbnz" and c2_.mnemonic == "cbnz" and b_.mnemonic == "b"):
            continue
        lops_ = [o_.strip() for o_ in ld_.op_str.split(",")]
        sops_ = [o_.strip() for o_ in st_.op_str.split(",")]
        c1o_ = [o_.strip() for o_ in c1_.op_str.split(",")]
        c2o_ = [o_.strip() for o_ in c2_.op_str.split(",")]
        if not (imm(b_.op_str) == ld_.address and c1o_[0] == lops_[0] and imm(c1o_[1]) == cl_.address
                and c2o_[0] == sops_[0] and imm(c2o_[1]) == ld_.address and lops_[1] == sops_[2]):
            continue
        out_[k_ - 1] = SpinPseudo_("spinlock_", b_, ld_, st_)
        for j_ in range(k_, k_ + 5):
            out_[j_] = SpinPseudo_("nop_", ins[j_])
    return out_

def imm(s):
    return int(s.strip().lstrip("#"), 0)

def hx_(n):
    """Hex for a name: a negative offset becomes mNN."""
    return f"{n:x}" if n >= 0 else f"m{-n:x}"

def mangled_arity(name):
    """(integer args, float args) of an Itanium-mangled function name, `this` included for a member; None if unsure."""
    if not name.startswith("_Z") or any(x_ in name for x_ in ("St", "Sa", "Sb", "Ss", "Si", "So", "Sd", "Dp", "z")):
        return None
    s, pos = name[2:], 0
    member = False
    def ident(p):
        q = p
        while q < len(s) and s[q].isdigit():
            q += 1
        if q == p:
            return None
        n = int(s[p:q])
        return q + n
    def skip_template(p):
        depth = 0
        while p < len(s):
            if s[p] == "I":
                depth += 1
            elif s[p] == "E":
                depth -= 1
                if depth == 0:
                    return p + 1
            p += 1
        return None
    try:
        if s[pos] == "N":
            member = True
            pos += 1
            while s[pos] in "KVr":
                pos += 1
            while s[pos] != "E":
                if s[pos].isdigit():
                    pos = ident(pos)
                elif s[pos] in "CD" and pos + 1 < len(s) and s[pos + 1].isdigit():
                    pos += 2
                elif s[pos] == "S":
                    pos = s.index("_", pos) + 1
                elif s[pos] == "I":
                    pos = skip_template(pos)
                else:
                    return None
                if pos is None:
                    return None
            pos += 1
        elif s[pos].isdigit():
            pos = ident(pos)
            if pos < len(s) and s[pos] == "I":
                pos = skip_template(pos)
        else:
            return None
        rest = s[pos:]
        if rest == "v":
            return (1 if member else 0, 0)
        ni, nf = (1 if member else 0), 0
        p = pos
        while p < len(s):
            ptr = False
            while p < len(s) and s[p] in "PRKVO":
                ptr = ptr or s[p] in "PRO"
                p += 1
            c = s[p]
            if c in "bcahstijlmxynow" or (c == "v" and ptr):
                p += 1; kind = "i"
            elif c in "fd":
                p += 1; kind = "f"
            elif c.isdigit():
                p = ident(p); kind = "i" if ptr else None
                if p < len(s) and s[p] == "I":
                    p = skip_template(p)
            elif c == "S":
                p = s.index("_", p) + 1; kind = "i" if ptr else None
            elif c == "N":
                p = s.index("E", p) + 1; kind = "i" if ptr else None
            elif c == "D" and p + 1 < len(s) and s[p + 1] == "n":
                p += 2; kind = "i"
            else:
                return None
            if ptr:
                kind = "i"
            if kind is None:
                return None  # a class passed by value
            if kind == "i":
                ni += 1
            else:
                nf += 1
        return (ni, nf)
    except (IndexError, ValueError, TypeError):
        return None

KNOWN_ARITY = {}
ARITY_USED = [False]
PAIR_USED = [False]
HOIST_USED = [False]
for _n, _a in list(units["symbols"].items()) + [(_n2, _a2) for _u in units["units"].values() for _n2, _a2 in _u.get("functions", {}).items()]:
    if _n.startswith("got:") or re.search(r"(callee\d?|call|placeholder)_[0-9a-f]+", _n):
        continue
    _ar = mangled_arity(_n)
    if _ar is not None:
        _t = int(_a, 16) - 0x7100000000
        if KNOWN_ARITY.get(_t, _ar) != _ar:
            KNOWN_ARITY[_t] = None  # two names disagree
        else:
            KNOWN_ARITY[_t] = _ar
# a function that never reads an argument register (an empty body, a constant return) shows no parameters: the
# parameter list of its name is a guess
TRIVIAL_ = set()
TRIVIAL_USED = [False]
for _r in rows:
    _t = int(_r[0], 16) - 0x7100000000
    if KNOWN_ARITY.get(_t) is not None and int(_r[2]) <= 8:
        _ins = list(md.disasm(d[_t:_t + int(_r[2])], _t))
        if all(not _i.mnemonic.startswith("b") and not any(re.search(r"\b[xwsdqv][0-7]\b", _o)
               for _o in _i.op_str.split(", ")[1:]) for _i in _ins):
            TRIVIAL_.add(_t)

# a hand-written name with fewer parameters than the callee reads (x0-x7 read before they are written in its first
# block), or a thunk that only branches on, does not limit the calls to it: trust the callee
READ_OVER_ = set()
READ_OVER0_ = set()     # names with no parameters at all for a callee that reads x0: never a cap
for _r in rows:
    _t = int(_r[0], 16) - 0x7100000000
    _ka = KNOWN_ARITY.get(_t)
    if _ka is None:
        continue
    _ins = list(md.disasm(d[_t:_t + min(int(_r[2]), 256)], _t))
    if _ins and _ins[0].mnemonic in ("b", "br"):
        READ_OVER_.add(_t)
        continue
    _wr, _rd = set(), set()
    for _i in _ins:
        _mk = _i.mnemonic
        if _mk in ("b", "br", "bl", "blr", "ret", "cbz", "cbnz", "tbz", "tbnz") or _mk.startswith("b."):
            if _mk in ("cbz", "cbnz", "tbz", "tbnz"):
                _m = re.match(r"[wx](\d+)", _i.op_str)
                if _m and int(_m.group(1)) < 8 and int(_m.group(1)) not in _wr:
                    _rd.add(int(_m.group(1)))
            break
        _r_, _w_ = rw(_i)
        _rd |= {x for x in _r_ if x < 8 and x not in _wr}
        _wr |= _w_
    if _rd and max(_rd) + 1 > _ka[0]:
        READ_OVER_.add(_t)
        if _ka[0] == 0 and 0 in _rd:
            READ_OVER0_.add(_t)

def regname(r):
    if r in ("wzr", "xzr"):
        return None, r[0]
    m = re.fullmatch(r"([wx])(\d+)", r)
    if not m:
        raise Fail("reg " + r)
    return int(m.group(2)), m.group(1)

LOAD = {"ldr": None, "ldrb": "unsigned char", "ldrh": "unsigned short", "ldrsb": "signed char", "ldrsh": "short", "ldrsw": "int"}
STORE = {"str": None, "strb": "unsigned char", "strh": "unsigned short"}
BIN = {"add": "+", "sub": "-", "and": "&", "orr": "|", "eor": "^", "lsl": "<<", "lsr": ">>", "asr": ">>", "mul": "*"}
# literal pools: 4-byte floats and 16-byte vectors (merged .rodata.cst4 / .rodata.cst16)
POOL4 = (0x73b000, 0x73ca00)
POOL16 = (0x73dff0, 0x73e7a0)
SIZE = {"Vec4f": 16, "int": 4, "unsigned int": 4, "long": 8, "void*": 8, "unsigned char": 1, "signed char": 1, "unsigned short": 2, "short": 2, "float": 4}
CC = {"eq": "==", "ne": "!=", "lt": "<", "le": "<=", "gt": ">", "ge": ">=", "lo": "<", "ls": "<=", "hi": ">", "hs": ">="}
SAVED = {"x19", "x20", "x21", "x22", "x23", "x24", "x25", "x26", "x27", "x28", "x29", "x30",
         "d8", "d9", "d10", "d11", "d12", "d13", "d14", "d15"}

def is_frame(i):
    m, o = i.mnemonic, i.op_str
    if m in ("stp", "ldp"):
        regs = [r.strip() for r in o.split(",")[:2]]
        return all(r in SAVED for r in regs) and "[sp" in o
    if m in ("str", "ldr") and "[sp" in o:
        return o.split(",")[0].strip() in SAVED
    if m == "mov" and o == "x29, sp":
        return True
    if m == "add" and o.startswith("x29, sp, #"):
        return True
    if m in ("sub", "add") and o.startswith("sp, sp, #"):
        return True
    return False

defs, funcs = [], []
skipped = 0
reasons = {}
internal = {}

VA_SAVES = {"q6, q7, [sp, #0x60]", "x6, x7, [sp, #0xb0]", "x4, x5, [sp, #0xa0]", "x2, x3, [sp, #0x90]",
            "x0, x1, [sp, #0x80]", "q4, q5, [sp, #0x40]", "q2, q3, [sp, #0x20]", "q0, q1, [sp]"}
def gen_function(a, ins):
    knobs = KNOB_MAP.get(a, DEFAULT_KNOBS)
    RW_FIX[0] = "oldrw" not in knobs
    BFM_FIX[0] = "oldbfm" not in knobs
    if ("novastub" not in knobs and len(ins) == 11 and (ins[0].mnemonic, ins[0].op_str) == ("sub", "sp, sp, #0xc0")
            and all(i_.mnemonic == "stp" for i_ in ins[1:9]) and {i_.op_str for i_ in ins[1:9]} == VA_SAVES
            and (ins[9].mnemonic, ins[9].op_str) == ("add", "sp, sp, #0xc0") and ins[10].mnemonic == "ret"):
        body_ = (f"\n\n// 0x71{a:08x}\nvoid call_{a:x}(...) {{\n    __builtin_va_list args;\n"
                 "    __builtin_va_start(args, 0);\n    __builtin_va_end(args);\n}\n")
        return body_, {}, []
    structs, pwidth, arith = {}, {}, set()
    gobjs = {}
    letbase, vtables, vslots, skip_lets = {}, {}, {}, set()
    store_typed = set()
    used_imports = set()
    elemkinds, elemsizes = {}, {}
    loopelem, elemsize = {}, {}
    over_ = {}          # target -> {parameter types: return type}
    mergestructs = {}
    bytekinds = {}
    vars_ = {}          # name -> type (or 'w'/'x' pending, or struct name)
    callees = {}        # target -> [arg types, ret type]
    counter = [0]
    if "nosqrtpair" not in knobs:
        # move `fcmp sD, sD` down to its b.vc/b.vs over instructions that neither use sD nor the flags
        tg_ = set()
        for i_ in ins:
            if i_.mnemonic in ("b", "bl", "cbz", "cbnz", "tbz", "tbnz") or i_.mnemonic.startswith("b."):
                m_ = re.search(r"#(0x[0-9a-f]+|\d+)$", i_.op_str)
                if m_:
                    tg_.add(int(m_.group(1), 0))
        k_ = 0
        while k_ < len(ins) - 1:
            i_ = ins[k_]
            ops_ = [o_.strip() for o_ in i_.op_str.split(",")]
            if i_.mnemonic == "fcmp" and len(ops_) == 2 and ops_[0] == ops_[1] and re.fullmatch(r"s\d+", ops_[0]) \
                    and ins[k_ + 1].mnemonic not in ("b.vc", "b.vs"):
                n_ = int(ops_[0][1:])
                kb_ = None
                for j_ in range(k_ + 1, min(len(ins), k_ + 10)):
                    ij_ = ins[j_]
                    if ij_.mnemonic in ("b.vc", "b.vs"):
                        kb_ = j_
                        break
                    if ij_.address in tg_ or ij_.mnemonic in ("b", "bl", "blr", "br", "ret", "cbz", "cbnz", "tbz", "tbnz") \
                            or ij_.mnemonic.startswith(("b.", "cmp", "cmn", "tst", "fcmp", "ccmp", "fccmp", "subs", "adds", "ands", "bics")):
                        break
                    r_, w_ = frw(ij_)
                    if n_ in r_ or n_ in w_:
                        break
                if kb_ is not None:
                    ins = ins[:k_] + ins[k_ + 1:kb_] + [ins[k_]] + ins[kb_:]
            k_ += 1
    if "nospinlock" not in knobs:
        ins = spin_rewrite_(ins)
    addr_index = {i.address: k for k, i in enumerate(ins)}
    ivec_loads_ = {}
    if "noicvt" not in knobs:
        for k_, i_ in enumerate(ins):
            mm_ = re.fullmatch(r"([shb])(\d+), \[.*", i_.op_str) if i_.mnemonic in ("ldr", "ldur") else None
            if not mm_ or i_.op_str.endswith("!") or re.search(r"\[(sp|x29)\b", i_.op_str):
                continue
            kind_, n_ = mm_.group(1), int(mm_.group(2))
            for ij_ in ins[k_ + 1:k_ + 16]:
                if kind_ == "h" and ij_.mnemonic in ("sshll", "ushll") and re.fullmatch(r"v\d+\.4s, v%d\.4h, #0" % n_, ij_.op_str):
                    ivec_loads_[k_] = "short" if ij_.mnemonic == "sshll" else "unsigned short"
                    break
                if ij_.mnemonic in ("scvtf", "ucvtf") and re.fullmatch(r"s\d+, s%d" % n_, ij_.op_str):
                    # a load of h or b zero-extends into the s register
                    if kind_ == "s":
                        ivec_loads_[k_] = "int" if ij_.mnemonic == "scvtf" else "unsigned int"
                    elif ij_.mnemonic == "ucvtf":
                        ivec_loads_[k_] = "unsigned short" if kind_ == "h" else "unsigned char"
                    break
                r_, w_ = frw(ij_)
                if n_ in r_ or n_ in w_ or ij_.mnemonic in ("bl", "blr", "b", "br", "ret") or ij_.mnemonic.startswith("b."):
                    break
    copy_skip_, copy_emit_ = set(), {}
    cstore1_ = set()       # (struct, offset, size) written by a single constant store
    stack_min_, stack_al_ = {}, {}     # stack structs: the size and alignment their block copies need
    valinit_imp_ = set()
    if "nostructcopy" not in knobs:
        MEMC_ = re.compile(r"([wxqds])(\d+), \[(x\d+%s)(?:, #(-?0x[0-9a-f]+|-?\d+)|, (x\d+))?\]$"
                           % ("" if "nostackcopy" in knobs else "|sp"))
        starts_c_ = sorted({imm(i_.op_str.split(",")[2]) for i_ in ins if i_.mnemonic == "add"
                            and re.fullmatch(r"x(\d+), sp, #(0x[0-9a-f]+|\d+)", i_.op_str) and not i_.op_str.startswith("x29")}
                           | {0 for i_ in ins if i_.mnemonic == "mov" and re.fullmatch(r"x\d+, sp", i_.op_str)
                              and not i_.op_str.startswith("x29")})
        fp_c_ = None
        for i_ in ins[:8]:
            if i_.mnemonic == "mov" and i_.op_str == "x29, sp":
                fp_c_ = 0
            elif i_.mnemonic == "add" and i_.op_str.startswith("x29, sp, #"):
                fp_c_ = imm(i_.op_str.split(",")[2])
        if fp_c_ is not None and "nofpcopy" not in knobs and "nostackcopy" not in knobs:
            starts_c_ = sorted(set(starts_c_) | {fp_c_ - imm(i_.op_str.split(",")[2]) for i_ in ins if i_.mnemonic == "sub"
                                                 and re.fullmatch(r"x(\d+), x29, #(0x[0-9a-f]+|\d+)", i_.op_str)})
        SZC_ = {"w": 4, "x": 8, "q": 16, "d": 8, "s": 4}
        def is_br_(i_):
            return i_.mnemonic in ("bl", "blr", "b", "br", "ret") or i_.mnemonic.startswith(("b.", "cbz", "cbnz", "tbz", "tbnz"))
        def flush_(groups_):
            for (bsk_, bdk_, dl_), g_ in groups_.items():
                bs_, bd_ = bsk_[0], bdk_[0]
                def stk_ok_(g2_):
                    # a stack side lies in one addressed stack object
                    r0_ = min(so_ for so_, _, _, _ in g2_)
                    r1_ = max(so_ + sz_ for so_, sz_, _, _ in g2_)
                    for b_, sh_ in ((bs_, 0), (bd_, dl_)):
                        if b_ == "sp" and (not any(s_ <= r0_ + sh_ for s_ in starts_c_)
                                           or any(r0_ + sh_ < s_ < r1_ + sh_ for s_ in starts_c_)):
                            return False
                    return True
                def vok_(g2_):
                    # both bases hold the versions the pieces used where the copy is emitted
                    v_ = vsnap_.get(min(ks2_ for _, _, _, ks2_ in g2_), {})
                    return v_.get(bs_, 0) == bsk_[1] and v_.get(bd_, 0) == bdk_[1]
                if len(g_) < 2 and not ("copy1" in knobs and g_[0][1] >= 8):
                    continue
                ivs_ = sorted((so_, so_ + sz_) for so_, sz_, _, _ in g_)
                lo_, hi_ = ivs_[0][0], ivs_[0][1]
                ok_ = True
                runs_ = [[lo_, hi_]]
                for s0_, s1_ in ivs_[1:]:
                    if s0_ > hi_:
                        ok_ = False
                        runs_.append([s0_, s1_])
                    else:
                        runs_[-1][1] = max(runs_[-1][1], s1_)
                    hi_ = max(hi_, s1_)
                if not ok_ and "nocopystride" not in knobs and len(runs_) >= 2:
                    # records with gaps: equal runs at one stride, each copied with the same pieces
                    C_, S_ = runs_[0][1] - runs_[0][0], runs_[1][0] - runs_[0][0]
                    pats_ = {}
                    for so_, sz_, _, _ in g_:
                        pats_.setdefault((so_ - lo_) // S_, []).append(((so_ - lo_) % S_, sz_))
                    if C_ >= 12 and all(r1_ - r0_ == C_ for r0_, r1_ in runs_) \
                            and all(runs_[j_ + 1][0] - runs_[j_][0] == S_ for j_ in range(len(runs_) - 1)) \
                            and len(pats_) == len(runs_) and len({tuple(sorted(v_)) for v_ in pats_.values()}) == 1 \
                            and len(next(iter(pats_.values()))) >= 2:
                        al_ = 16
                        for so_, sz_, _, _ in g_:
                            for x_ in (so_ - lo_, so_ + dl_):
                                while al_ > 1 and x_ % al_:
                                    al_ //= 2
                        ks_ = [kk_ for _, _, kl_, ks2_ in g_ for kk_ in (kl_, ks2_)]
                        if not vok_(g_) or not stk_ok_(g_):
                            continue
                        copy_skip_.update(ks_)
                        copy_emit_[min(ks2_ for _, _, _, ks2_ in g_)] = (bs_, bd_, lo_, lo_ + dl_, C_, len(runs_), al_, S_)
                    continue
                if not ok_ or hi_ - lo_ < (8 if "copy1" in knobs else 12):
                    continue
                total_ = hi_ - lo_
                pieces_ = sorted((so_ - lo_, sz_) for so_, sz_, _, _ in g_)
                def rec_of_(ps_, tot_):
                    for cand_ in range(max(sz_ for _, sz_ in ps_), tot_):
                        if tot_ % cand_:
                            continue
                        recs_ = {}
                        good_ = True
                        for rel_, sz_ in ps_:
                            if rel_ // cand_ != (rel_ + sz_ - 1) // cand_:
                                good_ = False
                                break
                            recs_.setdefault(rel_ // cand_, []).append((rel_ % cand_, sz_))
                        if good_ and len(recs_) == tot_ // cand_ and len({tuple(sorted(v_)) for v_ in recs_.values()}) == 1 \
                                and len(next(iter(recs_.values()))) >= 2:
                            return cand_
                    return None
                R_, h_, e_ = rec_of_(pieces_, total_), 0, total_
                if R_ is None and "nocopycut" not in knobs:
                    # fields copied before or after a run of records (a count, then the array) stay fields
                    cuts_ = [c_ for c_ in sorted({r_ for r_, _ in pieces_} | {total_}) if not any(r_ < c_ < r_ + s_ for r_, s_ in pieces_)]
                    best_ = None
                    for h2_ in [c_ for c_ in cuts_ if c_ < total_][:4]:
                        for e2_ in sorted([c_ for c_ in cuts_ if c_ > h2_], reverse=True)[:4]:
                            ps_ = [(r_ - h2_, s_) for r_, s_ in pieces_ if h2_ <= r_ < e2_]
                            if (h2_ or e2_ < total_) and e2_ - h2_ >= 12 and ps_:
                                R2_ = rec_of_(ps_, e2_ - h2_)
                                if R2_ is None:
                                    continue
                                # Clang copies a record largest pieces first: prefer the cut whose records start so
                                rec0_ = sorted((r_, s_) for r_, s_ in ps_ if r_ < R2_)
                                canon_ = all(rec0_[j_][1] >= rec0_[j_ + 1][1] for j_ in range(len(rec0_) - 1))
                                sc_ = (e2_ - h2_, canon_, -h2_)
                                if best_ is None or sc_ > best_[0]:
                                    best_ = (sc_, R2_, h2_, e2_)
                    if best_ is not None:
                        _, R_, h_, e_ = best_
                if R_ is None:
                    R_ = total_
                g_ = [p_ for p_ in g_ if h_ <= p_[0] - lo_ < e_]
                lo_, total_ = lo_ + h_, e_ - h_
                al_ = 16
                for so_, sz_, _, _ in g_:
                    for x_ in (so_ - lo_, so_ + dl_):
                        while al_ > 1 and x_ % al_:
                            al_ //= 2
                ks_ = [kk_ for _, _, kl_, ks2_ in g_ for kk_ in (kl_, ks2_)]
                if not vok_(g_) or not stk_ok_(g_):
                    continue
                first_st_ = min(ks2_ for _, _, _, ks2_ in g_)
                copy_skip_.update(ks_)
                copy_emit_[first_st_] = (bs_, bd_, lo_, lo_ + dl_, R_, total_ // R_, al_, R_)
        res_c_, vsnap_, ver_ = {}, {}, {}
        addk_, constk_ = {}, {}
        ADDI_ = re.compile(r"(x\d+), (x\d+), #(0x[0-9a-f]+|\d+)(?:, lsl #(\d+))?$")
        MOVR_ = re.compile(r"(x\d+), (x\d+)$")
        MOVI_ = re.compile(r"[wx](\d+), #(0x[0-9a-f]+|\d+)$")
        MOVK_ = re.compile(r"[wx](\d+), #(0x[0-9a-f]+|\d+)(?:, lsl #(\d+))?$")
        for k_, i_ in enumerate(ins):
            if is_br_(i_):
                addk_, constk_ = {}, {}
                continue
            m_ = MEMC_.match(i_.op_str) if i_.mnemonic in ("ldr", "ldur", "str", "stur") else None
            if m_:
                b_, o_ = m_.group(3), int(m_.group(4), 0) if m_.group(4) else 0
                if m_.group(5) and m_.group(5) not in constk_:
                    b_ = None
                elif m_.group(5):
                    o_ += constk_[m_.group(5)]
                if b_ in addk_:
                    b_, o2_ = addk_[b_]
                    o_ += o2_
                if b_ == "x29" and "nofpcopy" not in knobs:
                    # the frame pointer: a stack offset, or no base
                    if fp_c_ is not None and "nostackcopy" not in knobs:
                        b_, o_ = "sp", fp_c_ + o_
                    else:
                        b_ = None
                if b_ is not None and (b_ == m_.group(3) or b_ == "sp" or "nocopybase" not in knobs):
                    res_c_[k_] = (b_, o_)
                vsnap_[k_] = dict(ver_)
            new_ = None
            ma_ = ADDI_.match(i_.op_str) if i_.mnemonic == "add" else (MOVR_.match(i_.op_str) if i_.mnemonic == "mov" else None)
            if ma_:
                r_, o3_ = addk_.get(ma_.group(2), (ma_.group(2), 0))
                if r_ != ma_.group(1):
                    new_ = (ma_.group(1), (r_, o3_ + ((int(ma_.group(3), 0) << int(ma_.group(4) or 0)) if i_.mnemonic == "add" else 0)))
            mk_ = MOVK_.match(i_.op_str) if i_.mnemonic == "movk" else None
            newc_ = None
            if mk_ and "x" + mk_.group(1) in constk_:
                sh_ = int(mk_.group(3)) if mk_.group(3) else 0
                newc_ = (constk_["x" + mk_.group(1)] & ~(0xffff << sh_)) | (int(mk_.group(2), 0) << sh_)
            w4_ = {"x%d" % w_ for w_ in rw(i_)[1]}
            for w_ in w4_:
                ver_[w_] = ver_.get(w_, 0) + 1
            for w_ in w4_:
                addk_.pop(w_, None); constk_.pop(w_, None)
            for d_ in [d_ for d_, (r_, _) in addk_.items() if r_ in w4_]:
                addk_.pop(d_)
            if new_ is not None:
                addk_[new_[0]] = new_[1]
            if newc_ is not None:
                constk_["x" + mk_.group(1)] = newc_
            mm_ = MOVI_.match(i_.op_str) if i_.mnemonic == "mov" else None
            if mm_:
                constk_["x" + mm_.group(1)] = int(mm_.group(2), 0)
        groups_ = {}
        written_c_ = set()
        for k_, i_ in enumerate(ins):
            if is_br_(i_):
                flush_(groups_); groups_ = {}; written_c_ = set()
                continue
            m_ = MEMC_.match(i_.op_str) if i_.mnemonic in ("ldr", "ldur") else None
            if m_ and k_ in res_c_ and (res_c_[k_][0] not in written_c_ or "nocopyver" not in knobs):
                rk_, rn_ = m_.group(1), m_.group(2)
                rb_, so_ = res_c_[k_]
                rpat_ = re.compile(r"\b[%s]%s\b" % ("wx" if rk_ in "wx" else "qdsvbh", rn_))
                for j_ in range(k_ + 1, min(len(ins), k_ + 8)):
                    ij_ = ins[j_]
                    mj_ = MEMC_.match(ij_.op_str) if ij_.mnemonic in ("str", "stur") else None
                    if mj_ and mj_.group(1) == rk_ and mj_.group(2) == rn_ and j_ in res_c_ \
                            and (res_c_[j_][0] not in written_c_ or "nocopyver" not in knobs) \
                            and (res_c_[j_][0] == "sp" or not any(int(res_c_[j_][0][1:]) in rw(ins[jw_])[1] for jw_ in range(k_, j_))):
                        # the value must not be read again before it is overwritten
                        dead_ = True
                        for jj_ in range(j_ + 1, len(ins)):
                            ix_ = ins[jj_]
                            if is_br_(ix_):
                                dead_ = ix_.mnemonic not in ("ret", "b", "br") or True
                                break
                            r2_, w2_ = (frw(ix_) if rk_ not in "wx" else rw(ix_))
                            if int(rn_) in r2_:
                                dead_ = False
                                break
                            if int(rn_) in w2_:
                                break
                        if dead_:
                            rd_, do_ = res_c_[j_]
                            groups_.setdefault(((rb_, vsnap_[k_].get(rb_, 0)), (rd_, vsnap_[j_].get(rd_, 0)), do_ - so_), []) \
                                .append((so_, SZC_[rk_], k_, j_))
                        break
                    if rpat_.search(ij_.op_str) or is_br_(ij_):
                        break
            r3_, w3_ = rw(i_)
            written_c_ |= {"x%d" % w_ for w_ in w3_}
        flush_(groups_)
    hoist_adds_ = set()
    for k_, i_ in enumerate(ins):
        ops_h_ = [o_.strip() for o_ in re.split(r",(?![^\[]*\])", i_.op_str)]
        if i_.mnemonic != "add" or len(ops_h_) != 3 or not re.fullmatch(r"x(19|2[0-8])", ops_h_[0]) \
                or not re.fullmatch(r"x\d+", ops_h_[1]) or ops_h_[1] in ("x29", ops_h_[0]) \
                or not (ops_h_[2].startswith("#") or re.fullmatch(r"x([89]|1[0-7])", ops_h_[2])):
            continue
        rn_ = ops_h_[0][1:]
        rp_ = re.compile(r"\b[xw]%s\b" % rn_)
        calls_ = uses_ = 0
        ok_ = True
        for ij_ in ins[k_ + 1:]:
            ops_j_ = [o_.strip() for o_ in re.split(r",(?![^\[]*\])", ij_.op_str)]
            mj_ = ij_.mnemonic
            if mj_ == "mov" and len(ops_j_) == 2 and re.fullmatch(r"x[0-7]", ops_j_[0]) and ops_j_[1] == "x" + rn_:
                if not calls_:
                    ok_ = False
                    break
                uses_ += 1
                continue
            writes_ = not (mj_.startswith(("st", "cbz", "cbnz", "tbz", "tbnz", "cmp", "cmn", "tst", "b.", "fcmp", "ccmp", "ccmn"))
                           or mj_ in ("b", "bl", "blr", "br", "ret"))
            dsts_ = ops_j_[:2] if mj_ in ("ldp", "ldnp", "ldpsw") else ops_j_[:1]
            reads_ = ops_j_[len(dsts_):] if writes_ else ops_j_
            if any(rp_.search(o_) for o_ in reads_):
                ok_ = False
                break
            if writes_ and any(rp_.fullmatch(o_) for o_ in dsts_):
                break
            if mj_ in ("bl", "blr"):
                calls_ += 1
            if mj_ in ("ret", "br") or (mj_ == "b" and not ij_.op_str.startswith("#")):
                break
        if ok_ and uses_:
            hoist_adds_.add(k_)
    pair_loads_ = set()
    for k_, i_ in enumerate(ins):
        mm_ = re.fullmatch(r"x(\d+), \[(x\d+)(?:, #(0x[0-9a-f]+|\d+))?\]", i_.op_str) if i_.mnemonic in ("ldr", "ldur") else None
        if not mm_ or mm_.group(1) in ("29", "30") or mm_.group(2) in ("x29", "x" + mm_.group(1)):
            continue
        rn_ = mm_.group(1)
        xp_ = re.compile(r"\bx%s\b" % rn_)
        wp_ = re.compile(r"\bw%s\b" % rn_)
        hi_ = False
        ok_ = True
        hif_ = False
        if "nopairflow" not in knobs:
            todo_, seen_p_ = [k_ + 1], set()
            while todo_ and ok_:
                j_ = todo_.pop()
                while j_ < len(ins) and j_ not in seen_p_ and len(seen_p_) < 200:
                    seen_p_.add(j_)
                    ij_ = ins[j_]
                    ops_j_ = [o_.strip() for o_ in re.split(r",(?![^\[]*\])", ij_.op_str)]
                    if ij_.mnemonic in ("lsr", "asr") and len(ops_j_) == 3 and xp_.fullmatch(ops_j_[1]) and ops_j_[2] in ("#0x20", "#32"):
                        hi_ = True
                        if "noibits" not in knobs and j_ + 1 < len(ins) and ins[j_ + 1].mnemonic == "fmov" \
                                and ins[j_ + 1].op_str.endswith(", w" + ops_j_[0][1:]):
                            hif_ = True
                        if xp_.fullmatch(ops_j_[0]):
                            break
                        j_ += 1; continue
                    if ij_.mnemonic == "ubfx" and len(ops_j_) == 4 and xp_.fullmatch(ops_j_[1]) and ops_j_[2] in ("#0x20", "#32") \
                            and ops_j_[3] in ("#0x20", "#32"):
                        hi_ = True
                        if "noibits" not in knobs and j_ + 1 < len(ins) and ins[j_ + 1].mnemonic == "fmov" \
                                and ins[j_ + 1].op_str.endswith(", w" + ops_j_[0][1:]):
                            hif_ = True
                        if xp_.fullmatch(ops_j_[0]):
                            break
                        j_ += 1; continue
                    reads_ = ops_j_[1:] if ops_j_ and not ij_.mnemonic.startswith(("st", "cb", "tb", "cmp", "cmn", "tst")) else ops_j_
                    if any(xp_.search(o_) for o_ in reads_):
                        ok_ = False
                        break
                    if ops_j_ and (xp_.fullmatch(ops_j_[0]) or wp_.fullmatch(ops_j_[0])) \
                            and not ij_.mnemonic.startswith(("st", "cb", "tb", "cmp", "cmn", "tst")):
                        break  # redefined
                    if ij_.mnemonic in ("ret", "br", "bl", "blr"):
                        break
                    isb_ = ij_.mnemonic == "b" or ij_.mnemonic.startswith("b.") or ij_.mnemonic in ("cbz", "cbnz", "tbz", "tbnz")
                    tg_ = imm(ij_.op_str.split(", ")[-1]) if isb_ and ij_.op_str.split(", ")[-1].startswith("#") else None
                    if ij_.mnemonic == "b":
                        if tg_ not in addr_index:
                            break
                        j_ = addr_index[tg_]; continue
                    if ij_.mnemonic.startswith("b.") or ij_.mnemonic in ("cbz", "cbnz", "tbz", "tbnz"):
                        if tg_ in addr_index:
                            todo_.append(addr_index[tg_])
                    j_ += 1
            if ok_ and hi_ and not hif_:
                pair_loads_.add(k_)
            continue
        for j_ in range(k_ + 1, min(len(ins), k_ + 40)):
            ij_ = ins[j_]
            ops_j_ = [o_.strip() for o_ in re.split(r",(?![^\[]*\])", ij_.op_str)]
            if ij_.mnemonic in ("lsr", "asr") and len(ops_j_) == 3 and xp_.fullmatch(ops_j_[1]) and ops_j_[2] in ("#0x20", "#32"):
                hi_ = True
                if xp_.fullmatch(ops_j_[0]):
                    break
                continue
            if ij_.mnemonic == "ubfx" and len(ops_j_) == 4 and xp_.fullmatch(ops_j_[1]) and ops_j_[2] in ("#0x20", "#32") \
                    and ops_j_[3] in ("#0x20", "#32"):
                hi_ = True
                if xp_.fullmatch(ops_j_[0]):
                    break
                continue
            reads_ = ops_j_[1:] if ops_j_ and not ij_.mnemonic.startswith(("st", "cb", "tb", "cmp", "cmn", "tst")) else ops_j_
            if any(xp_.search(o_) for o_ in reads_):
                ok_ = False
                break
            if ops_j_ and (xp_.fullmatch(ops_j_[0]) or wp_.fullmatch(ops_j_[0])) \
                    and not ij_.mnemonic.startswith(("st", "cb", "tb", "cmp", "cmn", "tst")):
                break  # redefined
            if ij_.mnemonic in ("ret", "b", "br", "bl", "blr"):
                break
        if ok_ and hi_:
            pair_loads_.add(k_)
    jump_targets_ = set()
    for i_ in ins:
        if (i_.mnemonic in ("b", "cbz", "cbnz", "tbz", "tbnz") or i_.mnemonic.startswith("b.")) and "#" in i_.op_str:
            jump_targets_.add(imm(i_.op_str.split(", ")[-1]))
    sret_ = False
    if "nosret" not in knobs:
        for i_ in ins:
            if is_frame(i_):
                continue
            r_, w_ = rw(i_)
            if i_.mnemonic in ("bl", "blr", "br", "ret", "b") or i_.mnemonic.startswith("b.") or i_.mnemonic in ("cbz", "cbnz", "tbz", "tbnz"):
                sret_ = 8 in r_ and i_.mnemonic not in ("bl", "blr", "br")
                break
            if 8 in r_:
                sret_ = True
                break
            if 8 in w_:
                break
    RETN_ = f"Ret{a:x}"
    jt_, jt_skip_, jt_idx_ = {}, {}, {}
    jtabs_ = []         # (address, size) of each jump table, in emission order
    for kb_, ib_ in enumerate(ins):
        if "noswitch" in knobs or ib_.mnemonic != "br" or kb_ < 1:
            continue
        rn_ = ib_.op_str
        mA_ = re.fullmatch(r"(x\d+), (x\d+), (x\d+)", ins[kb_ - 1].op_str) if ins[kb_ - 1].mnemonic == "add" else None
        if not mA_ or mA_.group(1) != rn_ or mA_.group(2) != rn_:
            continue
        rt_ = mA_.group(3)
        kl_ = ri_ = ka_ = None
        for j_ in range(kb_ - 2, max(-1, kb_ - 8), -1):
            ml_ = re.fullmatch(r"(x\d+), \[(x\d+), (x\d+), lsl #2\]", ins[j_].op_str) if ins[j_].mnemonic == "ldrsw" else None
            if ml_ and ml_.group(1) == rn_ and ml_.group(2) == rt_:
                kl_, ri_ = j_, ml_.group(3)
                break
        if kl_ is None:
            continue
        for j_ in range(kl_ - 1, max(0, kl_ - 8), -1):
            if (ins[j_].mnemonic == "add" and re.fullmatch(r"%s, %s, #(0x[0-9a-f]+|\d+)" % (rt_, rt_), ins[j_].op_str)
                    and ins[j_ - 1].mnemonic == "adrp" and ins[j_ - 1].op_str.startswith(rt_ + ",")):
                ka_ = j_
                break
        if ka_ is None:
            continue
        T_ = imm(ins[ka_ - 1].op_str.split(", ")[1]) + imm(ins[ka_].op_str.split(", ")[2])
        jt_[kb_] = (T_, regname(ri_)[0])
        for j_ in (ka_ - 1, ka_, kl_, kb_ - 1):
            jt_skip_[j_] = kb_
    copy_loads_ = set()
    for k_, i_ in enumerate(ins):
        mm_ = re.fullmatch(r"x(\d+), \[(x\d+|sp)(?:, #(-?0x[0-9a-f]+|-?\d+))?\]", i_.op_str) if i_.mnemonic in ("ldr", "ldur") else None
        if not mm_ or mm_.group(1) in ("29", "30") or mm_.group(2) == "x" + mm_.group(1):
            continue
        rn_ = mm_.group(1)
        pat_ = re.compile(r"\b[xw]%s\b" % rn_)
        stores_ = 0
        for j_ in range(k_ + 1, len(ins)):
            ij_ = ins[j_]
            ops_j_ = [o_.strip() for o_ in re.split(r",(?![^\[]*\])", ij_.op_str)]
            if ij_.mnemonic in ("str", "stur") and ops_j_[0] == "x" + rn_ and not pat_.search(ops_j_[1]) and re.fullmatch(r"\[(x\d+|sp)(, #-?(0x[0-9a-f]+|\d+))?\]", ops_j_[1]):
                stores_ += 1
                continue
            if pat_.search(ij_.op_str):
                if ij_.mnemonic.startswith("ld") and ops_j_ and pat_.fullmatch(ops_j_[0]) and not pat_.search(ops_j_[-1]):
                    break  # redefined
                if ij_.mnemonic in ("mov", "add", "sub", "and", "orr", "lsr", "lsl", "asr", "ubfx", "sbfx", "movz", "movk", "mov") \
                        and pat_.fullmatch(ops_j_[0]) and not any(pat_.search(o_) for o_ in ops_j_[1:]):
                    break  # redefined
                stores_ = -1
                break
            if ij_.mnemonic in ("bl", "blr", "ret", "br", "b") or ij_.mnemonic.startswith("b.") or ij_.mnemonic in ("cbz", "cbnz", "tbz", "tbnz"):
                stores_ = -1
                break
            if ij_.address in jump_targets_:
                stores_ = -1
                break
        if stores_ > 0:
            copy_loads_.add(k_)
    loop_info = []
    CONT_ = {}          # instruction index of a back edge that continues a loop -> its header
    INF_ = set()        # headers of loops whose latch is an unconditional branch
    back_edges_ = []
    epi_ = set()
    fwdjump_ = set()
    def raw_succ_(kk):
        i_ = ins[kk]; mk = i_.mnemonic
        if mk in ("ret", "br"):
            return []
        if mk == "b":
            tv_ = imm(i_.op_str)
            return [addr_index[tv_]] if tv_ in addr_index else []
        if mk.startswith("b.") or mk in ("cbz", "cbnz", "tbz", "tbnz"):
            t2_ = addr_index.get(imm(i_.op_str.split(",")[-1]))
            return [x_ for x_ in (kk + 1, t2_) if x_ is not None and x_ < len(ins)]
        return [kk + 1] if kk + 1 < len(ins) else []
    def reaches_(src_, dst_):
        seen_, todo_ = set(), [src_]
        while todo_:
            n_ = todo_.pop()
            if n_ == dst_:
                return True
            if n_ in seen_:
                continue
            seen_.add(n_)
            todo_.extend(raw_succ_(n_))
        return False
    for i in ins:
        m = i.mnemonic
        if (m.startswith("b.") or m in ("cbz", "cbnz", "tbz", "tbnz") or (m == "b" and imm(i.op_str) in addr_index)):
            t = imm(i.op_str.split(",")[-1])
            if t not in addr_index:
                raise Fail("outside")
            if t <= i.address:
                # a target running straight to a ret is a shared epilogue; otherwise one do/while loop
                k2 = addr_index[t]
                straight_ = True
                while k2 < len(ins) and ins[k2].mnemonic not in ("ret",):
                    mk = ins[k2].mnemonic
                    if (mk.startswith("b") and mk != "bl") or mk in ("cbz", "cbnz", "tbz", "tbnz"):
                        straight_ = False; break
                    k2 += 1
                if straight_:
                    epi_.add(addr_index[t])
                if not straight_ and "nofwdjump" not in knobs and not reaches_(addr_index[t], addr_index[i.address]):
                    fwdjump_.add(addr_index[i.address])
                    continue
                if not straight_ and "nocont" not in knobs and "noloop" not in knobs:
                    # collected first: the back edges to one header make one loop
                    back_edges_.append((addr_index[t], addr_index[i.address], m == "b"))
                    continue
                if not straight_:
                    if m == "b" or "noloop" in knobs:
                        raise Fail("loop shape")
                    H0, L0 = addr_index[t], addr_index[i.address]
                    for H1, L1 in loop_info:
                        disjoint_ = L0 < H1 or H0 > L1
                        nested_ = (H1 < H0 and L0 < L1) or (H0 < H1 and L1 < L0)
                        if not (disjoint_ or (nested_ and "nonest" not in knobs)):
                            raise Fail("nested loop")
                    loop_info.append((H0, L0))
    # the last back edge to a header is the loop's latch (a conditional branch); the earlier ones continue the loop
    groups_ = {}
    for H0, L0, ub_ in back_edges_:
        groups_.setdefault(H0, []).append((L0, ub_))
    for H0 in sorted(groups_):
        lst_ = sorted(groups_[H0])
        L0, ub_ = lst_[-1]
        if ub_:
            if "noinfloop" in knobs:
                raise Fail("loop shape")
            INF_.add(H0)    # for (;;) left only through returns
        for Lc_, _ in lst_[:-1]:
            CONT_[Lc_] = H0
        for H1, L1 in loop_info:
            disjoint_ = L0 < H1 or H0 > L1
            nested_ = (H1 < H0 and L0 < L1) or (H0 < H1 and L1 < L0)
            if not (disjoint_ or (nested_ and "nonest" not in knobs)):
                raise Fail("nested loop")
        loop_info.append((H0, L0))
    # immediate post-dominators over the forward graph (loop back edges removed; returns and tail calls exit)
    EXIT_ = len(ins)
    latches_ = {L_ for H_, L_ in loop_info}
    def succs_(kk):
        i_ = ins[kk]; mk = i_.mnemonic
        if mk == "ret" or mk == "br":
            return [EXIT_]
        if mk == "b":
            tv_ = imm(i_.op_str)
            if tv_ not in addr_index:
                return [EXIT_]
            t2_ = addr_index[tv_]
            return [t2_] if (t2_ > kk or kk in fwdjump_) else [EXIT_]
        if mk.startswith("b.") or mk in ("cbz", "cbnz", "tbz", "tbnz"):
            t2_ = addr_index.get(imm(i_.op_str.split(",")[-1]))
            if kk in latches_ or t2_ is None or (t2_ <= kk and kk not in fwdjump_):
                return [kk + 1] if kk + 1 < len(ins) else [EXIT_]
            return [kk + 1, t2_]
        return [kk + 1] if kk + 1 < len(ins) else [EXIT_]
    # post-dominators to a fixpoint (jumps back to earlier blocks make the order not topological)
    ALL_ = frozenset(range(len(ins) + 1))
    pdom_ = {EXIT_: frozenset({EXIT_})}
    for kk in range(len(ins)):
        pdom_[kk] = ALL_
    succ_cache_ = {kk: succs_(kk) for kk in range(len(ins))}
    for _ in range(len(ins) + 2):
        changed_ = False
        for kk in range(len(ins) - 1, -1, -1):
            new_ = frozenset({kk}) | frozenset.intersection(*[pdom_[s_] for s_ in succ_cache_[kk]])
            if new_ != pdom_[kk]:
                pdom_[kk] = new_; changed_ = True
        if not changed_:
            break
    for kk in range(len(ins)):
        if pdom_[kk] == ALL_:
            pdom_[kk] = None
    def ipdom_(kk):
        p_ = pdom_.get(kk)
        if not p_:
            return None
        cands_ = p_ - {kk}
        if not cands_:
            return None
        best_ = max(cands_, key=lambda d_: len(pdom_.get(d_) or ()))
        return best_
    frameless_ = not any((i_.mnemonic == "sub" and i_.op_str.startswith("sp, sp")) or (i_.op_str.endswith("]!") and "[sp" in i_.op_str)
                         for i_ in ins)
    frame_total_ = 0
    for i_ in ins[:8]:
        if i_.op_str.endswith("]!") and "[sp, #-" in i_.op_str:
            frame_total_ += imm(i_.op_str.split("#-")[1].rstrip("]!"))
        elif i_.mnemonic == "sub" and i_.op_str.startswith("sp, sp, #"):
            frame_total_ += imm(i_.op_str.split(",")[2])
    fp_off = None
    starts = set()
    for i in ins:
        m, o = i.mnemonic, i.op_str
        if m == "mov" and o == "x29, sp":
            fp_off = 0
        elif m == "add" and o.startswith("x29, sp, #"):
            fp_off = imm(o.split(",")[2])
    for i in ins:
        m, o = i.mnemonic, i.op_str
        ops_ = [x.strip() for x in o.split(",")]
        if is_frame(i):
            continue
        if m == "add" and len(ops_) == 3 and ops_[1] == "sp" and ops_[2].startswith("#"):
            starts.add(imm(ops_[2]))
        elif m == "mov" and len(ops_) == 2 and ops_[1] == "sp":
            starts.add(0)
        elif m == "sub" and len(ops_) == 3 and ops_[1] == "x29" and ops_[2].startswith("#"):
            if fp_off is None:
                raise Fail("no fp")
            starts.add(fp_off - imm(ops_[2]))
        elif ("[sp" in o or "[x29" in o) and m not in ("ldr", "str", "ldrb", "strb", "ldrh", "strh", "ldrsw", "stp", "ldur", "stur", "ldp"):
            raise Fail("stack form")
    starts = sorted(starts)
    stackobjs = {}      # start -> {off: ctype}
    cstore_typed_ = set()   # (struct, off) typed only by constant stores so far
    bitfields_ = {}         # (struct, off) -> {(first bit, width)} written as bitfields
    BFW_ = {"unsigned char": 8, "signed char": 8, "unsigned short": 16, "short": 16, "int": 32, "unsigned int": 32}
    def bitfield_of_(sn_, off_, val_):
        """(first bit, width, inserted value) when val_ rewrites some bits of the field it was loaded from."""
        W_ = BFW_.get(structs[sn_].get(off_, ("",))[0])
        if W_ is None or val_[0] != "bin" or val_[1] != "|":
            return None
        for keep_, x_ in ((val_[2], val_[3]), (val_[3], val_[2])):
            if not (keep_[0] == "bin" and keep_[1] == "&" and keep_[3][0] == "const"):
                continue
            l_ = keep_[2]
            lt_ = vars_.get(l_[1]) if l_[0] == "var" else None
            if not (isinstance(lt_, tuple) and lt_[0] == "load" and lt_[1] == sn_ and lt_[2] == off_):
                continue
            hole_ = ~keep_[3][1] & ((1 << W_) - 1)
            if hole_ == 0:
                continue
            s_ = (hole_ & -hole_).bit_length() - 1
            w_ = bin(hole_).count("1")
            if hole_ != ((1 << w_) - 1) << s_ or w_ == W_:
                continue
            if x_[0] == "const":
                continue  # setting constant bits compiles the same either way
            if s_:
                if not (x_[0] == "bin" and x_[1] == "<<" and x_[3][0] == "const" and x_[3][1] == s_):
                    continue
                x_ = x_[2]
            if x_[0] == "bin" and x_[1] == "&" and x_[3][0] == "const" and x_[3][1] == (1 << w_) - 1:
                x_ = x_[2]
            if x_[0] == "bin" and (x_[1] == "|" or (x_[1] == "&" and x_[2][0] == "bin" and x_[2][1] == "&")):
                return None  # several fields written at once: keep the explicit form
            return s_, w_, x_
        return None
    def u32_(v_):
        """The 32-bit unsigned value v_ stands for, or None."""
        if v_[0] == "ext" and v_[1] == "unsigned int":
            return v_[2]
        if v_[0] == "bin" and v_[4] == "w":
            return v_
        if v_[0] == "var":
            tv_ = vars_.get(v_[1])
            if tv_ == "w" or (isinstance(tv_, tuple) and tv_[0] == "load" and len(tv_) > 3 and tv_[3] in ("int", "unsigned int")):
                return v_
            if isinstance(tv_, tuple) and tv_[0] == "load" and len(tv_) == 3 and structs[tv_[1]].get(tv_[2], ("",))[0] in ("int", "unsigned int"):
                return v_
        if v_[0] == "param" and pwidth.get(v_[1]) == "w":
            return v_
        return None
    def strip_u32_(v_):
        return v_[2] if v_[0] == "ext" and v_[1] == "unsigned int" else v_
    def times_(y_):
        """(value, factor) when y_ is value * factor written with mul, shifts and adds."""
        if y_[0] == "bin" and y_[1] == "*" and y_[3][0] == "const":
            return y_[2], y_[3][1]
        if y_[0] == "bin" and y_[1] == "*" and y_[2][0] == "const":
            return y_[3], y_[2][1]
        if y_[0] == "bin" and y_[1] == "<<" and y_[3][0] == "const":
            return y_[2], 1 << y_[3][1]
        if y_[0] == "bin" and y_[1] in ("+", "-"):
            a_ = times_(y_[2]) or (y_[2], 1)
            b_ = times_(y_[3]) or (y_[3], 1)
            if a_[0] == b_[0]:
                return a_[0], a_[1] + b_[1] if y_[1] == "+" else a_[1] - b_[1]
        return None
    def i32_(v_):
        """The 32-bit signed value v_ stands for (sign-extended operand of smull), or None."""
        if v_[0] == "ext" and v_[1] == "int":
            return v_[2]
        return None
    def smagic_ok_(M_, sh_):
        """d when x * M >> sh (with the sign fix) is x / d for 32-bit signed x, else None."""
        if M_ <= 0:
            return None
        d_ = round((1 << sh_) / M_)
        if d_ < 2:
            return None
        import random as _r
        rng_ = _r.Random(d_ * 7919 + sh_)
        xs_ = [0, 1, -1, d_ - 1, d_, -d_, d_ + 1, -d_ - 1, (1 << 31) - 1, -(1 << 31), -(1 << 31) + 1] + \
              [rng_.randrange(-(1 << 31), 1 << 31) for _ in range(2000)]
        for x_ in xs_:
            # both forms compute floor(x * M / 2**sh) plus one for a negative x
            q_ = ((x_ * M_) >> sh_) + (1 if x_ < 0 else 0)
            if q_ != abs(x_) // d_ * (1 if x_ >= 0 else -1):
                return None
        return d_
    def sdivmagic_(v_):
        """x / d and x % d for the signed multiply-high forms."""
        if v_[0] != "bin" or v_[1] != "+" or v_[4] != "w":
            return v_
        for a_, b_ in ((v_[2], v_[3]), (v_[3], v_[2])):
            # small magic: asr of the product, plus its sign bit
            if a_[0] == "bin" and a_[1] == ">>" and a_[5] == "asr" and a_[4] == "x" and a_[3][0] == "const" and a_[3][1] >= 32 \
                    and b_[0] == "bin" and b_[1] == ">>" and b_[5] == "lsr" and b_[3][0] == "const" and b_[3][1] == 63 \
                    and a_[2] == b_[2] and a_[2][0] == "bin" and a_[2][1] == "*":
                p_ = a_[2]
                for x0_, m0_ in ((p_[2], p_[3]), (p_[3], p_[2])):
                    x_ = i32_(x0_); mc_ = i32_(m0_) if m0_[0] == "ext" else m0_
                    if x_ is None or mc_ is None or mc_[0] != "const":
                        continue
                    M_ = mc_[1] & 0xffffffff
                    M_ = M_ - (1 << 32) if M_ >= 1 << 31 else M_
                    d_ = smagic_ok_(M_, a_[3][1])
                    if d_:
                        return ("sdiv", x_, d_)
            # large magic: ((hi(P) + x) >> s) + sign
            if a_[0] == "bin" and a_[1] == ">>" and a_[5] == "asr" and a_[4] == "w" and a_[3][0] == "const" \
                    and b_[0] == "bin" and b_[1] == ">>" and b_[5] == "lsr" and b_[3][0] == "const" and b_[3][1] == 31 \
                    and a_[2] == b_[2] and a_[2][0] == "bin" and a_[2][1] == "+":
                t_ = a_[2]
                for h_, x0_ in ((t_[2], t_[3]), (t_[3], t_[2])):
                    if not (h_[0] == "bin" and h_[1] == ">>" and h_[5] == "lsr" and h_[3][0] == "const" and h_[3][1] == 32
                            and h_[2][0] == "bin" and h_[2][1] == "*"):
                        continue
                    p_ = h_[2]
                    for xx_, m0_ in ((p_[2], p_[3]), (p_[3], p_[2])):
                        x_ = i32_(xx_); mc_ = i32_(m0_) if m0_[0] == "ext" else m0_
                        if x_ is None or mc_ is None or mc_[0] != "const" or x_ != x0_:
                            continue
                        M_ = mc_[1] & 0xffffffff  # x * (M - 2**32) + x * 2**32
                        d_ = smagic_ok_(M_, 32 + a_[3][1])
                        if d_:
                            return ("sdiv", x_, d_)
        return v_
    def divmagic_(v_):
        """x / d and x % d for the multiply-high forms of an unsigned 32-bit division by a constant."""
        if v_[0] != "bin":
            return v_
        if v_[1] == ">>" and v_[5] == "lsr" and v_[4] == "x" and v_[3][0] == "const" and v_[2][0] == "umulh" \
                and "noudiv64" not in knobs:
            s_ = v_[3][1]
            for a_, b_ in ((v_[2][1], v_[2][2]), (v_[2][2], v_[2][1])):
                if b_[0] != "const":
                    continue
                M_ = b_[1] & ((1 << 64) - 1)
                pre_ = 0
                x_ = a_
                if a_[0] == "bin" and a_[1] == ">>" and a_[5] == "lsr" and a_[3][0] == "const":
                    pre_, x_ = a_[3][1], a_[2]
                if M_ == 0:
                    continue
                d_ = round((1 << (64 + s_ + pre_)) / M_)
                if d_ < 2:
                    continue
                import random as _r
                rng_ = _r.Random(d_)
                xs_ = [0, 1, d_ - 1, d_, d_ + 1, (1 << 64) - 1, (1 << 63), (1 << 32) - 1] + [rng_.getrandbits(64) for _ in range(3000)] \
                      + [rng_.getrandbits(64) // d_ * d_ + k_ for k_ in (-1, 0, 1) for _ in range(300)]
                if all((((x2_ & ((1 << 64) - 1)) >> pre_) * M_ >> (64 + s_)) == (x2_ & ((1 << 64) - 1)) // d_ for x2_ in xs_):
                    return ("udiv64", x_, d_)
            return v_
        if v_[1] == ">>" and v_[5] == "lsr" and v_[4] == "x" and v_[3][0] == "const" and v_[3][1] >= 32 \
                and v_[2][0] == "bin" and v_[2][1] == "*":
            sh_ = v_[3][1]
            for a_, b_ in ((v_[2][2], v_[2][3]), (v_[2][3], v_[2][2])):
                bm_ = strip_u32_(b_)
                if bm_[0] != "const" or (bm_[1] & 0xffffffff) == 0:
                    continue
                x_ = u32_(a_)
                if x_ is None:
                    continue
                M_ = bm_[1] & 0xffffffff
                d_ = round((1 << sh_) / M_)
                if d_ >= 2 and M_ == -(-(1 << sh_) // d_) and 0 <= M_ * d_ - (1 << sh_) <= 1 << (sh_ - 32):
                    return ("udiv", x_, d_)
            return v_
        if v_[1] == "-" and v_[4] in ("x", "w") and "noudiv64" not in knobs:
            m_ = times_(v_[3])
            if m_ is not None and m_[0][0] == "udiv64" and m_[0][2] == m_[1] and m_[0][1] == v_[2]:
                return ("urem64", m_[0][1], m_[1])
        if v_[1] == "-" and v_[4] == "w":
            m_ = times_(v_[3])
            if m_ is not None and m_[0][0] == "udiv" and m_[0][2] == m_[1] and strip_u32_(m_[0][1]) == strip_u32_(v_[2]):
                return ("urem", m_[0][1], m_[1])
            if m_ is not None and m_[0][0] == "sdiv" and m_[0][2] == m_[1] and m_[0][1] == v_[2] and "nosdivmagic" not in knobs:
                return ("srem", m_[0][1], m_[1])
        return v_
    def bf_lines_(sn_, off_, t_):
        W_ = BFW_[t_]
        out_ = ["    union {", f"        {t_} field_{off_:x};", "        struct {"]
        pos_ = 0
        for s_, w_ in sorted(bitfields_[(sn_, off_)]):
            if s_ < pos_:
                raise Fail("bitfield overlap")
            if s_ > pos_:
                out_.append(f"            {t_} bfpad{off_:x}_{pos_} : {s_ - pos_};")
            out_.append(f"            {t_} bf{off_:x}_{s_} : {w_};")
            pos_ = s_ + w_
        if pos_ < W_:
            out_.append(f"            {t_} bfpad{off_:x}_{pos_} : {W_ - pos_};")
        out_ += ["        };", f"    }};{' ' * 16}// +{off_:x}"]
        return out_
    confirmed_ = set()      # (struct, off) typed by a load or a value store
    def note_access_(sn_, off_, cstore):
        if cstore:
            if (sn_, off_) not in confirmed_:
                cstore_typed_.add((sn_, off_))
        else:
            confirmed_.add((sn_, off_))
            cstore_typed_.discard((sn_, off_))
    INTS_ = ("long", "void*", "int", "unsigned int", "short", "unsigned short", "signed char", "unsigned char")
    def widen_(sn_, off_, prev_, ct_):
        """Type for one field read at off_ as prev_ and as ct_ (integers of two widths), or None."""
        if prev_[0] not in INTS_ or ct_ not in INTS_ or "nowiden" in knobs:
            return None
        wide_ = prev_[0] if SIZE[prev_[0]] >= SIZE[ct_] else ct_
        if wide_ == "void*":
            if prev_[0] == "void*" and prev_[1]:
                return None  # a pointer to a known struct
            wide_ = "long"
        if any(off_ < o2_ < off_ + SIZE[wide_] for o2_ in structs[sn_]):
            return None
        return wide_
    def widen_field_(sn_, off_, prev_, ct_):
        wide_ = widen_(sn_, off_, prev_, ct_)
        if wide_ is None:
            return False
        if wide_ != prev_[0]:
            for vn_, vt_ in list(vars_.items()):
                if isinstance(vt_, tuple) and vt_[0] == "load" and vt_[1] == sn_ and vt_[2] == off_ and len(vt_) == 3:
                    vars_[vn_] = vt_ + (prev_[0],)
            structs[sn_][off_] = (wide_, None)
        return True
    def spun_(a_, b_):
        """An int and a float in one stack slot: the slot keeps its first type and the other access is a pun."""
        return "nostackpun" not in knobs and a_ in ("int", "unsigned int", "float") and b_ in ("int", "unsigned int", "float") \
            and "float" in (a_, b_)
    def retype_ok_(sn_, off_, prev_t, ct_):
        """A field typed only by 8-byte constant stores may become a narrower scalar."""
        return ((sn_, off_) in cstore_typed_ and prev_t in ("void*", "long") and not ct_.startswith("ARRAY:")
                and ct_ in SIZE and SIZE[ct_] < 8)
    def const_pieces_(sn_, off_, width_, value_, base_):
        """Store items for an aligned constant of width_ bytes at off_, cut at the struct's field bounds."""
        WT_ = {1: "unsigned char", 2: "unsigned short", 4: "int", 8: "long"}
        fl_ = structs[sn_]
        cuts_ = {off_, off_ + width_}
        for o2_, (ct2_, _) in fl_.items():
            if ct2_.startswith("ARRAY:") or ct2_ not in SIZE:
                if off_ <= o2_ < off_ + width_:
                    raise Fail("constant over array")
                continue
            e2_ = o2_ + SIZE[ct2_]
            if o2_ < off_ < e2_ or o2_ < off_ + width_ < e2_:
                raise Fail("constant across field")
            if off_ <= o2_ < off_ + width_:
                cuts_ |= {o2_, e2_}
        out_ = []
        cuts_ = sorted(c_ for c_ in cuts_ if off_ <= c_ <= off_ + width_)
        val_ = value_ & ((1 << (8 * width_)) - 1)
        for lo_, hi_ in zip(cuts_, cuts_[1:]):
            pos_ = lo_
            while pos_ < hi_:
                for w_ in (8, 4, 2, 1):
                    if pos_ % w_ == 0 and pos_ + w_ <= hi_:
                        break
                ft_ = fl_.get(pos_, (WT_[w_], None))[0]
                if SIZE.get(ft_) != w_:
                    ft_ = WT_[w_]
                fl_.setdefault(pos_, (ft_, None))
                pv_ = (val_ >> (8 * (pos_ - off_))) & ((1 << (8 * w_)) - 1)
                if ft_ == "float":
                    if pv_:
                        raise Fail("constant over float")
                    out_.append(("store", sn_, pos_, base_, ("fconst", 0.0)))
                else:
                    if w_ <= 4 and pv_ >= 1 << (8 * w_ - 1) and ft_ in ("int", "short", "signed char"):
                        pv_ -= 1 << (8 * w_)
                    out_.append(("store", sn_, pos_, base_, ("const", pv_, "x" if w_ == 8 else "w")))
                pos_ += w_
        return out_
    def stack_obj(off):
        cands = [s0 for s0 in starts if s0 <= off]
        if not cands:
            raise Fail("unaddressed stack slot")
        return cands[-1]
    def struct_for(v):
        if v[0] == "retobj":
            structs.setdefault(RETN_, {})
            return RETN_
        if v[0] == "param":
            cur = pwidth.get(v[1])
            if cur in (None, "x"):
                name = f"Arg{a:x}_{v[1]}"
                structs.setdefault(name, {})
                pwidth[v[1]] = name
                return name
            if cur == "w":
                raise Fail("int as pointer")
            return cur
        if v[0] in ("bytes", "select"):
            key = v
            if key not in bytekinds:
                bytekinds[key] = f"{'Bytes' if v[0] == 'bytes' else 'Picked'}{a:x}_{len(bytekinds)}"
                structs[bytekinds[key]] = {}
            return bytekinds[key]
        if v[0] == "elem":
            key = (v[1], v[3])
            if key not in elemkinds:
                elemkinds[key] = f"Elem{a:x}_{len(elemkinds)}"
                structs[elemkinds[key]] = {}
                elemsizes[elemkinds[key]] = v[3]
            return elemkinds[key]
        if v[0] == "stackobj":
            name = f"Stack{hx_(v[1])}_{a:x}"
            structs.setdefault(name, {})
            stackobjs[v[1]] = name
            return name
        if v[0] in ("gotaddr", "local"):
            name = f"{'Global' if v[0] == 'gotaddr' else 'Local'}{v[1]:x}_{a:x}"
            structs.setdefault(name, {})
            gobjs[name] = v
            return name
        if v[0] == "var":
            cur = vars_[v[1]]
            if isinstance(cur, tuple) and cur[0] == "loopvar":
                if v[1] not in loopelem:
                    loopelem[v[1]] = f"Elem{a:x}_{v[1]}"
                    structs[loopelem[v[1]]] = {}
                return loopelem[v[1]]
            if isinstance(cur, tuple) and cur[0] == "merge" and "nomergebase" not in knobs:
                if v[1] not in mergestructs:
                    mergestructs[v[1]] = f"{v[1].capitalize()}{a:x}"
                    structs[mergestructs[v[1]]] = {}
                return mergestructs[v[1]]
            if isinstance(cur, tuple) and cur[0] != "load":
                raise Fail("merged base")
            if isinstance(cur, tuple):
                sn0, off0 = cur[1], cur[2]
                ct0, child0 = structs[sn0][off0]
                if ct0 == "ARRAY:void*" and len(cur) > 3 and cur[3] != "void*":
                    raise Fail("non-pointer load base")
                if ct0 == "long" and "nolongbase" not in knobs and off0 != 0 and (len(cur) == 3 or cur[3] in ("void*", "long")):
                    # an address kept in an 8-byte field: a pointer
                    structs[sn0][off0] = ("void*", child0)
                    ct0 = "void*"
                if ct0 not in ("void*", "ARRAY:void*"):
                    raise Fail("non-pointer load base")
                if child0 is None:
                    child0 = f"Node{a:x}_{v[1]}"
                    structs[child0] = {}
                    structs[sn0][off0] = (ct0, child0)
                return child0
            if cur == "?":
                cur = "x"
            if cur in ("x", "void*"):
                name = f"{v[1].capitalize()}{a:x}"
                structs.setdefault(name, {})
                vars_[v[1]] = name
                return name
            if cur in ("w", "int"):
                raise Fail("int var as pointer")
            if cur in structs:
                return cur
            raise Fail("var base")
        if v[0] == "bin" and v[1] in ("+", "-", "|") and "noaddrbase" not in knobs:
            if v not in bytekinds:
                bytekinds[v] = f"Addr{a:x}_{len(bytekinds)}"
                structs[bytekinds[v]] = {}
            return bytekinds[v]
        raise Fail("base kind")
    def use(regs, r):
        n, w = regname(r)
        if n is None:
            return ("const", 0, w)
        v = regs.get(n)
        if v is None:
            raise Fail("undefined x%d" % n)
        if v[0] == "pair32":
            if w == "w":
                return v[1]
            raise Fail("paired load as 64 bits")
        if v[0] == "param":
            cur = pwidth.get(v[1])
            if cur is None:
                pwidth[v[1]] = w
            elif cur == "w" and w == "x" and n != v[1]:
                # a 32-bit copy of an int parameter read as 64 bits is its zero extension
                return ("ext", "unsigned int", v)
            elif cur in ("w", "x") and cur != w:
                raise Fail("mixed width")
            elif cur in ("short", "unsigned short", "signed char", "unsigned char"):
                if w == "x":
                    raise Fail("narrow param as x")
            elif cur not in ("w", "x") and w == "w":
                raise Fail("pointer as int")
        if v[0] == "var" and vars_[v[1]] == "?":
            vars_[v[1]] = w
        if w == "x" and is_narrow(v):
            return ("ext", "unsigned int", v)
        return v
    fparams = set()
    def fregname(r):
        m_ = re.fullmatch(r"s(\d+)", r)
        if not m_:
            raise Fail("freg " + r)
        return int(m_.group(1))
    def is_vecval_(v, seen_=None):
        """A 128-bit float vector value (Vec4f)."""
        if v is None:
            return False
        if v[0] in ("vconst", "vbin", "vsplat", "vfma", "vneg", "vparam", "vins", "vundef", "vcomb", "vecuv"):
            return True
        if v[0] == "var":
            tv_ = vars_.get(v[1])
            if isinstance(tv_, tuple) and tv_[0] == "merge" and "novecmerge" not in knobs:
                # a merge of vectors (a loop variable's own update counts as one)
                seen_ = seen_ or set()
                if v[1] in seen_:
                    return True
                seen_.add(v[1])
                return is_vecval_(tv_[1], seen_) and is_vecval_(tv_[2], seen_)
            return tv_ == "Vec4f" or (isinstance(tv_, tuple) and tv_[0] == "load" and (
                (len(tv_) == 3 and structs[tv_[1]].get(tv_[2], ("",))[0] in ("Vec4f", "ARRAY:Vec4f"))
                or (len(tv_) > 3 and tv_[3] == "Vec4f")))
        return False
    def lane_(fregs, n, i):
        """Lane i of register n: a lane of a vector, or the scalar itself for lane 0 of a scalar register."""
        v = fregs.get(n)
        if v is None:
            raise Fail("undefined v%d" % n)
        if is_vecval_(v):
            if "novec" in knobs:
                raise Fail("vector arithmetic")
            return ("vlane", v, i)
        if i == 0 and v[0] not in ("fsqrtp",):
            if v[0] == "fparam":
                fparams.add(v[1])
            return v
        raise Fail("lane of scalar")
    fmerges_ = set()    # merges in float registers: their untyped call results are floats once the merge is used
    def fmerge_side_(x_, seen_=None):
        """'f' for a float value, 'q' for an untyped call result (or a merge of them), 'i' for an int or pointer."""
        if x_[0] != "var":
            return "f"
        t_ = vars_.get(x_[1])
        if t_ == "?":
            return "q"
        if t_ in ("f", "Vec4f", "Float2", "VecU"):
            return "f"
        if isinstance(t_, str):
            return "i"
        if isinstance(t_, tuple) and t_[0] == "merge":
            seen_ = seen_ or set()
            if x_[1] in seen_:
                return "f"
            seen_.add(x_[1])
            s_ = {fmerge_side_(t_[1], seen_), fmerge_side_(t_[2], seen_)}
            return "i" if "i" in s_ else ("q" if s_ == {"q"} else "f")
        if isinstance(t_, tuple) and t_[0] == "load":
            ct_ = t_[3] if len(t_) > 3 else structs[t_[1]][t_[2]][0]
            return "f" if ct_ in ("float", "Vec4f", "ARRAY:float", "ARRAY:Vec4f") else "i"
        return "f"
    def floatize_(x_, seen_=None):
        if x_[0] != "var":
            return
        t_ = vars_.get(x_[1])
        if t_ == "?":
            vars_[x_[1]] = "f"
        elif isinstance(t_, tuple) and t_[0] == "merge":
            seen_ = seen_ or set()
            if x_[1] not in seen_:
                seen_.add(x_[1])
                floatize_(t_[1], seen_); floatize_(t_[2], seen_)
    def f2_type_(x_):
        if x_ is not None and x_[0] == "f2y":
            if vars_.get(x_[1][1]) not in ("?", "f", "Float2"):
                raise Fail("float pair of an int")
            vars_[x_[1][1]] = "Float2"
    def fuse(fregs, r):
        ml_ = re.fullmatch(r"v(\d+)\.s\[(\d)\]", r)
        if ml_:
            return lane_(fregs, int(ml_.group(1)), int(ml_.group(2)))
        n = fregname(r)
        v = fregs.get(n)
        if v is None:
            raise Fail("undefined s%d" % n)
        if v[0] == "fparam":
            fparams.add(v[1])
        if is_vecval_(v):
            return lane_(fregs, n, 0)
        if v[0] == "vconst":
            raise Fail("vector constant lane")
        if v[0] == "fsqrtp":
            raise Fail("fsqrt")
        if v[0] == "ivec":
            raise Fail("int in a vector register")
        if v[0] == "f2y":
            f2_type_(v)
            return v
        if v[0] == "var" and vars_.get(v[1]) == "?":
            vars_[v[1]] = "f"
        return v
    def stride_of(ix):
        """(index value, stride) for a scaled index expression, or None."""
        if ix[0] == "bin" and ix[1] == "<<" and ix[3][0] == "const":
            return ix[2], 1 << ix[3][1]
        if ix[0] == "bin" and ix[1] == "*" and ix[3][0] == "const":
            return ix[2], ix[3][1]
        if ix[0] == "bin" and ix[1] == "*" and ix[2][0] == "const":
            return ix[3], ix[2][1]
        return None
    def is_narrow(v):
        """True for values that are 32 bits or narrower (written through a w register)."""
        if v[0] == "const":
            return v[2] == "w"
        if v[0] in ("bin", "select"):
            return v[-2] == "w" if v[0] == "bin" else v[4] == "w"
        if v[0] == "cond":
            return v[2] == "w"
        if v[0] == "var":
            tv = vars_.get(v[1])
            if isinstance(tv, tuple) and tv[0] == "load":
                ct = tv[3] if len(tv) > 3 else structs[tv[1]][tv[2]][0]
                return ct in ("int", "unsigned char", "signed char", "unsigned short", "short")
            return tv == "w"
        return False
    def cval_(e):
        if e[0] == "const":
            return e[1]
        if e[0] == "ext" and e[2][0] == "const":
            v_ = e[2][1] & 0xffffffff
            if e[1] == "int" and v_ >= 1 << 31:
                v_ -= 1 << 32
            return v_
        return None
    def fold(base, off):
        while base is not None and base[0] == "bin" and base[1] == "+" and cval_(base[3]) is not None and base[4] == "x":
            off += cval_(base[3])
            base = base[2]
        if base is not None and base[0] == "page":
            base = ("local", base[1])
        if base is not None and base[0] == "stackaddr" and "nobasefix" not in knobs:
            st_ = stack_obj(base[1])
            off += base[1] - st_
            base = ("stackobj", st_)
        if base is not None and base[0] == "select":
            arm_a, arm_b = base[2], base[3]
            for x_, y_, swap in ((arm_a, arm_b, False), (arm_b, arm_a, True)):
                if x_[0] == "bin" and x_[1] == "+" and x_[2] == y_:
                    st_ = stride_of(x_[3])
                    if st_:
                        idx_ = ("pick", base[1], st_[0], swap)
                        return ("elem", y_, idx_, st_[1]), off

        if base is not None and base[0] == "bin" and base[1] == "+" and base[4] == "x":
            for b_, ix in ((base[2], base[3]), (base[3], base[2])):
                st = stride_of(ix) or ((ix, 1) if ix[0] == "ext" and b_[0] == "bin" else None)
                if st and st[1] > 0 and b_[0] == "bin":
                    c_, core_ = 0, b_
                    while core_[0] == "bin" and core_[1] == "+" and core_[3][0] == "const" and core_[4] == "x":
                        c_ += core_[3][1]; core_ = core_[2]
                    if core_[0] == "bin" and core_[1] == "+" and core_[4] == "x":
                        for B_, ix1 in ((core_[2], core_[3]), (core_[3], core_[2])):
                            st1 = stride_of(ix1)
                            if st1 and st1[1] > st[1] and B_[0] in ("param", "var", "local", "gotaddr"):
                                return ("sub", ("elem", B_, st1[0], st1[1]), c_ + off, st[0], st[1]), 0
                if (st and st[1] > 0 and "nobasefix" not in knobs and b_[0] == "bin" and b_[1] == "+" and b_[4] == "x"
                        and cval_(b_[3]) is not None and b_[2][0] in ("param", "var", "local", "gotaddr")):
                    base = ("elem", b_, st[0], st[1])
                    break
                if st and st[1] > 0 and b_[0] in ("param", "var", "local", "gotaddr"):
                    if st[1] <= off:
                        shift_ = (off // st[1]) * st[1]
                        b_ = ("bin", "+", b_, ("const", shift_, "x"), "x", "add")
                        off -= shift_
                    base = ("elem", b_, st[0], st[1])
                    break
            else:
                lhs, rhs = base[2], base[3]
                def pointerish(v_):
                    if v_[0] in ("local", "gotaddr"):
                        return True
                    if v_[0] == "param":
                        return pwidth.get(v_[1]) not in ("w",)
                    if v_[0] == "var":
                        tv_ = vars_.get(v_[1])
                        if "nobasefix" not in knobs and tv_ in ("?", "x") and v_[1].startswith("c"):
                            return True
                        return isinstance(tv_, tuple) and tv_[0] == "load" and (len(tv_) > 3 and tv_[3] == "void*" or structs[tv_[1]][tv_[2]][0] == "void*")
                    return False
                if base[0] == "bin" and pointerish(lhs) and not pointerish(rhs):
                    base = ("bytes", lhs, rhs)
                elif base[0] == "bin" and pointerish(rhs) and not pointerish(lhs):
                    base = ("bytes", rhs, lhs)
                elif base[0] == "bin" and base[1] == "+" and pointerish(lhs) and pointerish(rhs) and rhs[0] == "var":
                    # two loaded 64-bit values added: the second is a byte offset (a used size), not a pointer
                    tv_ = vars_.get(rhs[1])
                    if isinstance(tv_, tuple) and tv_[0] == "load" and structs[tv_[1]][tv_[2]] == ("void*", None):
                        structs[tv_[1]][tv_[2]] = ("long", None)
                        if len(tv_) > 3:
                            vars_[rhs[1]] = ("load", tv_[1], tv_[2], "long")
                        base = ("bytes", lhs, rhs)
        return base, off
    bytecast_fields_ = set()   # byte arrays made only by byte-offset accesses of wider values
    arr_scalar_ = {}           # (struct, offset) -> element type of an array indexed through a scalar field
    vu_slots_ = set()          # (struct, offset) of 16-byte slots used as a vector and as lanes or halves
    VU_T_ = {"float": 4, "int": 4, "unsigned int": 4, "void*": 8, "long": 8}
    def vu_check_(sn_, o_, ct_):
        """True when an access of type ct_ at o_ is a view of a vector slot (which becomes a VecU union)."""
        if "novecunion" in knobs:
            return False
        fl_ = structs[sn_]
        for u_ in (o_, o_ - 4, o_ - 8, o_ - 12):
            if u_ >= 0 and fl_.get(u_, ("",))[0] == "Vec4f" and not (ct_ == "Vec4f" and u_ == o_):
                if ct_ not in VU_T_ or (o_ - u_) % VU_T_[ct_]:
                    return False
                if any(u_ < o2_ < u_ + 16 and fl_[o2_][0] not in VU_T_ for o2_ in fl_):
                    return False
                vu_slots_.add((sn_, u_))
                return True
        if ct_ == "Vec4f":
            inner_ = [o2_ for o2_ in fl_ if o_ <= o2_ < o_ + 16]
            if inner_ and all(fl_[o2_][0] in VU_T_ and (o2_ - o_) % VU_T_[fl_[o2_][0]] == 0 for o2_ in inner_):
                fl_[o_] = ("Vec4f", None)
                vu_slots_.add((sn_, o_))
                return True
        return False
    def vu_of_(sn_, o_):
        return next((u_ for (s_, u_) in vu_slots_ if s_ == sn_ and u_ <= o_ < u_ + 16), None)
    def vu_view_(ty_, d_):
        if ty_ == "Vec4f" and d_ == 0:
            return "v", "Vec4f"
        if ty_ == "float":
            return f"f[{d_ // 4}]", "float"
        if ty_ in ("int", "unsigned int"):
            return f"i[{d_ // 4}]", "int"
        if ty_ in ("long", "void*"):
            return f"l[{d_ // 8}]", "long"
        raise Fail("vector slot view")
    def field(regs, base_reg, off, ct, base=None, cstore=False, bytecast=False):
        if base is None and base_reg is not None:
            bn, _ = regname(base_reg)
            base = regs.get(bn)
        if base is None:
            raise Fail("undefined base")
        base, off = fold(base, off)
        if off < 0 and "nonegoff" not in knobs and base[0] in ("param", "var", "local", "gotaddr", "stackobj"):
            base = ("bytes", base, ("const", off, "x")); off = 0
        elif off < 0 and "nonegoff" not in knobs and base[0] == "bytes":
            # a byte offset already: the field's offset joins it
            base = ("bytes", base[1], ("bin", "-", base[2], ("const", -off, "x"), "x", "sub")); off = 0
        elif off < 0 and "nonegoff" not in knobs and "noaddrbase" not in knobs and base[0] == "bin" and base[1] == "+":
            # a computed address (noaddrbase): the field's offset joins it
            base = ("bin", "-", base, ("const", -off, "x"), "x", "sub"); off = 0
        if off < 0:
            raise Fail("negative offset")
        if base[0] == "sub" and SIZE.get(ct) != base[4]:
            st2_ = base[4]
            k_ = base[2] % st2_
            cc_ = base[2] - k_
            outer_ = base[1]
            h_ = cc_ - cc_ % outer_[3]
            cc_ -= h_
            if h_:
                outer_ = ("elem", ("bin", "+", outer_[1], ("const", h_, "x"), "x", "add"), outer_[2], outer_[3])
            if k_ + SIZE.get(ct, 8) > st2_:
                raise Fail("inner element field")
            e1_ = struct_for(outer_)
            key2_ = ("inner", e1_, cc_)
            if key2_ not in elemkinds:
                elemkinds[key2_] = f"Elem{a:x}_{len(elemkinds)}"
                structs[elemkinds[key2_]] = {}
                elemsizes[elemkinds[key2_]] = st2_
                SIZE[elemkinds[key2_]] = st2_
            e2_ = elemkinds[key2_]
            prev_ = structs[e1_].get(cc_)
            if prev_ and prev_[0] != "ARRAY:" + e2_:
                raise Fail("field clash")
            structs[e1_][cc_] = ("ARRAY:" + e2_, None)
            prev_ = structs[e2_].get(k_)
            if prev_ and prev_[0] != ct:
                raise Fail("field clash")
            structs[e2_].setdefault(k_, (ct, None))
            return e2_, ("sub2", outer_, cc_, base[3], e2_), k_
        if base[0] == "sub" and SIZE.get(ct) == base[4] and base[2] >= base[1][3]:
            # the array lies past the first element: move whole elements into the outer base
            h_ = base[2] - base[2] % base[1][3]
            outer_ = ("elem", ("bin", "+", base[1][1], ("const", h_, "x"), "x", "add"), base[1][2], base[1][3])
            base = ("sub", outer_, base[2] - h_, base[3], base[4])
        if base[0] == "sub":
            if SIZE.get(ct) != base[4] or base[2] >= base[1][3]:
                raise Fail("inner array stride")
            sn_ = struct_for(base[1])
            prev_ = structs[sn_].get(base[2])
            if prev_ and prev_[0] != "ARRAY:" + ct:
                raise Fail("field clash")
            structs[sn_][base[2]] = ("ARRAY:" + ct, None)
            return sn_, base, base[2]
        sn = struct_for(base)
        prev = structs[sn].get(off)
        if prev and prev[0] != ct and not cstore and retype_ok_(sn, off, prev[0], ct):
            structs[sn][off] = (ct, None)
            prev = structs[sn][off]
        if "noarrscalar" not in knobs and prev and prev[0] != ct and not bytecast and not prev[1] \
                and (ct.startswith("ARRAY:") != prev[0].startswith("ARRAY:")):
            # an array also accessed as a scalar at its start: the scalar keeps the field
            el_ = (ct if ct.startswith("ARRAY:") else prev[0])[6:]
            if el_ in SIZE and (sn, off) not in bytecast_fields_:
                arr_scalar_[(sn, off)] = el_
                if ct.startswith("ARRAY:"):
                    note_access_(sn, off, cstore)
                    return sn, base, off
                structs[sn][off] = (ct, None)
                prev = structs[sn][off]
        if "nobytearr" not in knobs:
            # a byte-offset access into a typed field: the field keeps (or takes) the other type
            if bytecast and prev and prev[0] != ct:
                note_access_(sn, off, cstore)
                return sn, base, off
            if bytecast and not prev:
                bytecast_fields_.add((sn, off))
            elif prev and prev[0] == "ARRAY:unsigned char" and (sn, off) in bytecast_fields_:
                bytecast_fields_.discard((sn, off))
                if ct != "ARRAY:unsigned char":
                    structs[sn][off] = (ct, None)
                    prev = structs[sn][off]
        if not ct.startswith("ARRAY:") and vu_check_(sn, off, ct):
            prev = None if structs[sn].get(off) is None else structs[sn][off]
            if prev and prev[0] != ct:
                note_access_(sn, off, cstore)
                return sn, base, off
        if prev and prev[0] != ct:
            groups = [{"long", "void*"}, {"unsigned char", "signed char"}, {"unsigned short", "short"}]
            pun_ = prev[0] in ("int", "unsigned int", "float") and ct in ("int", "unsigned int", "float") and "float" in (prev[0], ct) and "nopun" not in knobs
            if not pun_ and not any(prev[0] in g and ct in g for g in groups):
                if not widen_field_(sn, off, prev, ct):
                    raise Fail("field clash")
                prev = structs[sn][off]
            if ct in ("short", "signed char") and (sn, off) in store_typed:
                structs[sn][off] = (ct, prev[1])
                store_typed.discard((sn, off))
                prev = structs[sn][off]
        if not prev:
            structs[sn][off] = (ct, None)
        note_access_(sn, off, cstore)
        return sn, base, off
    def page_base(regs, op):
        """True when op is [xN, #off] on a register holding an adrp page."""
        if op.endswith("!"):
            return False
        parts = [p_.strip() for p_ in op.strip("[]").split(",")]
        if len(parts) > 2 or (len(parts) == 2 and not parts[1].startswith("#")):
            return False
        mm_ = re.fullmatch(r"x(\d+)", parts[0])
        if not mm_:
            return False
        v_ = regs.get(int(mm_.group(1)))
        return v_ is not None and v_[0] == "page"
    def memop(op):
        if op.endswith("!"):
            raise Fail("writeback")
        parts = [p.strip() for p in op.strip("[]").split(",")]
        if len(parts) > 2 or (len(parts) == 2 and not parts[1].startswith("#")):
            raise Fail("indexed")
        return parts[0], (imm(parts[1]) if len(parts) == 2 else 0)
    def memop2(op, extra):
        """(base, offset, index, shift, ext, pre, post) for any addressing form."""
        pre = op.endswith("!")
        parts = [p.strip() for p in op.strip("[]!").split(",")]
        post = imm(extra) if extra else None
        if len(parts) >= 2 and not parts[1].startswith("#"):
            idx = parts[1]
            ext, sh = "x", 0
            if len(parts) == 3:
                kind = parts[2].split()
                ext = kind[0]
                sh = imm(kind[1]) if len(kind) > 1 else 0
            elif len(parts) > 3:
                raise Fail("addressing")
            return parts[0], 0, idx, sh, ext, False, None
        off = imm(parts[1]) if len(parts) == 2 else 0
        return parts[0], off, None, 0, None, pre, post
    def index_value(regs, idx, ext):
        n_, w_ = regname(idx)
        v = use(regs, idx)
        if ext in ("uxtw",):
            return ("ext", "unsigned int", v)
        if ext in ("sxtw",):
            return ("ext", "int", v)
        if ext in ("lsl", "x"):
            return v
        raise Fail("index ext")
    returns = []
    UNDEF_ = set()      # argument registers passed uninitialised
    FUNDEF_ = set()     # float argument registers passed uninitialised
    UINTLOOP_ = set()   # int loop counters used as unsigned indexes
    PAIRS_ = set()      # calls whose result is a 16-byte struct (its high half in x1 is used)
    calls_by_target_ = {}
    call_k_ = [None]
    def freg_read_next_(k_, n_):
        """Float register n_ is read before it is written after instruction k_ (straight-line code, following
        unconditional jumps, up to the next call or return)."""
        j_, steps_ = k_ + 1, 0
        while j_ < len(ins) and steps_ < 200:
            steps_ += 1
            i_ = ins[j_]
            if i_.mnemonic in ("bl", "blr", "br", "ret"):
                return False
            if i_.mnemonic == "b":
                t_ = addr_index.get(imm(i_.op_str))
                if t_ is None or t_ <= j_:
                    return False
                j_ = t_
                continue
            r_, w_ = frw(i_)
            if n_ in r_:
                return True
            if n_ in w_:
                return False
            j_ += 1
        return False
    def farg_count_(k_):
        """One more than the highest float register written in the straight-line code before instruction k_ and not
        read after its last write."""
        seen_read_, args_ = set(), set()
        decided_ = set()
        for j_ in range(k_ - 1, -1, -1):
            i_ = ins[j_]
            mj_ = i_.mnemonic
            if mj_ in ("bl", "blr", "b", "br", "ret", "cbz", "cbnz", "tbz", "tbnz") or mj_.startswith("b."):
                break
            r_, w_ = frw(i_)
            for n_ in w_:
                if n_ < 8 and n_ not in decided_:
                    decided_.add(n_)
                    if n_ not in seen_read_:
                        args_.add(n_)
            seen_read_ |= r_
        return max(args_) + 1 if args_ else 0
    def epilogue_next_(k_):
        """Only the epilogue (restores from the stack, the stack pointer, a jump to it) follows instruction k_."""
        j_, seen_ = k_ + 1, set()
        while j_ < len(ins) and j_ not in seen_:
            seen_.add(j_)
            i_ = ins[j_]
            if i_.mnemonic == "ret":
                return True
            if i_.mnemonic == "b" and imm(i_.op_str) in addr_index:
                j_ = addr_index[imm(i_.op_str)]; continue
            if i_.mnemonic in ("ldp", "ldr") and "[sp" in i_.op_str and not (set(rw(i_)[1]) & set(range(19))) \
                    and not (set(frw(i_)[1]) & set(range(8))):
                j_ += 1; continue
            if i_.mnemonic in ("add", "sub", "mov") and i_.op_str.startswith("sp, "):
                j_ += 1; continue
            return False
        return False
    def s0_read_next_(k_):
        """s0 is read before it is written after instruction k_ (up to the next call, jump or return)."""
        for j_ in range(k_ + 1, len(ins)):
            i_ = ins[j_]
            if i_.mnemonic in ("bl", "blr", "b", "br", "ret"):
                return False
            r_, w_ = frw(i_)
            if 0 in r_:
                return True
            if 0 in w_:
                return False
        return False
    def call(regs, written, target, items, tail):
        fw = regs.get("fw", set())
        nf = max(fw) + 1 if fw else 0
        n = max(written) + 1 if written else (1 if regs.get(0) is not None else 0)
        ka_ = KNOWN_ARITY.get(target) if "noknownarity" not in knobs else None
        if ka_ is not None and target in READ_OVER_ and "readarity" in knobs:
            ka_ = None
        if ka_ is not None and target in READ_OVER0_ and "noread0" not in knobs:
            ka_ = None
        if ka_ is not None and target in TRIVIAL_ and "trivialarity" not in knobs:
            # the name of a trivial callee does not show its parameters
            if ka_[0] < n or ka_[1] < nf:
                TRIVIAL_USED[0] = True
            ka_ = None
        if ka_ is not None and (ka_[0] < n or ka_[1] < nf):
            n, nf = min(n, ka_[0]), min(nf, ka_[1])
            ARITY_USED[0] = True
        args = []
        for k in range(n):
            v = regs.get(k)
            if v is not None and v[0] == "hi":
                v = None
            if v is None and "noundefarg" not in knobs and k < n - 1 and k in range(8):
                UNDEF_.add(k)
                v = ("undef", k)
            if v is None:
                raise Fail("undefined arg")
            if v[0] == "param":
                cur = pwidth.get(v[1])
                if cur is None:
                    pwidth[v[1]] = "x"
            args.append(v)
        fargs = []
        ck_ = call_k_[0]
        call_k_[0] = None
        if "nofargscan" not in knobs and ck_ is not None and any(regs["f"].get(k) is None for k in range(nf)):
            nf = min(nf, farg_count_(ck_))
        for k in range(nf):
            v = regs["f"].get(k)
            if v is None:
                raise Fail("undefined float arg")
            if v[0] == "fparam":
                fparams.add(v[1])
            fargs.append(v)
        merged_ = []
        k_ = 0
        while k_ < len(args):
            a0_ = args[k_]
            if a0_[0] == "vpart" and k_ + 1 < len(args) and args[k_ + 1][0] == "vpart" and args[k_ + 1][1] == a0_[1] \
                    and a0_[2] == 0 and args[k_ + 1][2] == 1:
                merged_.append(("vecu", a0_[1])); k_ += 2
            elif a0_[0] == "vpart":
                raise Fail("vector half argument")
            else:
                merged_.append(a0_); k_ += 1
        args = merged_ + fargs
        name = f"c{counter[0]}"; counter[0] += 1
        vars_[name] = "?"
        imp0_ = import_of(target)
        if imp0_:
            ir_ = imp0_[3]
            if ir_.endswith("*"):
                vars_[name] = "x"
            elif ir_ in ("long", "unsigned long"):
                vars_[name] = ir_
            elif ir_ == "float":
                vars_[name] = "f"
        prev = callees.get(target)
        snap_ = {k_: (None if (regs.get(k_) or ("",))[0] == "hi" else regs.get(k_)) for k_ in range(8)}
        fsnap_ = {k_: regs["f"].get(k_) for k_ in range(8)}
        ni_ = len(args) - len(fargs)
        if (prev and "nofarity" not in knobs and (nf or any(c_[2] for c_ in calls_by_target_.get(target, [])))
                and not any(x_[0] == "vecu" for x_ in args)
                and (len(prev[0]) != len(args) or any(c_[2] != nf for c_ in calls_by_target_.get(target, [])))):
            calls_ = calls_by_target_.get(target, []) + [(args, snap_, nf, fsnap_, ni_)]
            if any(len(c_) < 5 for c_ in calls_):
                raise Fail("callee arity")
            want_i_ = max(c_[4] for c_ in calls_)
            want_f_ = max(c_[2] for c_ in calls_)
            for alist_, snap0_, nf0_, fsnap0_, ni0_ in calls_:
                ints_, flts_ = alist_[:ni0_], alist_[ni0_:]
                for k_ in range(ni0_, want_i_):
                    v_ = snap0_.get(k_)
                    if v_ is None:
                        UNDEF_.add(k_)
                        v_ = ("undef", k_)
                    elif v_[0] == "param" and pwidth.get(v_[1]) is None:
                        pwidth[v_[1]] = "x"
                    ints_.append(v_)
                for k_ in range(nf0_, want_f_):
                    v_ = fsnap0_.get(k_)
                    if v_ is None:
                        FUNDEF_.add(k_)
                        v_ = ("fundef", k_)
                    elif v_[0] == "fparam":
                        fparams.add(v_[1])
                    flts_.append(v_)
                alist_[:] = ints_ + flts_
            callees[target][0] = args
            calls_by_target_.setdefault(target, []).append((args, snap_, want_f_, fsnap_, want_i_))
            for j_, c_ in enumerate(calls_by_target_[target]):
                calls_by_target_[target][j_] = (c_[0], c_[1], want_f_, c_[3], want_i_)
            items.append(("call", name, target, args, tail))
            return ("var", name)
        if prev and len(prev[0]) != len(args):
            def extend_(alist_, snap0_, nf0_, want_):
                if nf0_ or nf:
                    raise Fail("callee arity")
                for k_ in range(len(alist_), want_):
                    v_ = snap0_.get(k_)
                    if v_ is None and "noundefext" not in knobs and k_ < 8:
                        # the register was clobbered: this call passes an uninitialised value the callee ignores
                        UNDEF_.add(k_)
                        v_ = ("undef", k_)
                    if v_ is None:
                        raise Fail("callee arity")
                    if v_[0] == "param" and pwidth.get(v_[1]) is None:
                        pwidth[v_[1]] = "x"
                    alist_.append(v_)
            if "noarity" in knobs:
                raise Fail("callee arity")
            if len(args) > len(prev[0]):
                for c_ in calls_by_target_.get(target, []):
                    extend_(c_[0], c_[1], c_[2], len(args))
                callees[target][0] = args
            else:
                extend_(args, snap_, nf, len(prev[0]))
        callees.setdefault(target, [args, None])
        calls_by_target_.setdefault(target, []).append((args, snap_, nf, fsnap_, ni_))
        items.append(("call", name, target, args, tail))
        return ("var", name)
    def copyregs(r):
        c = dict(r)
        c["f"] = dict(r["f"])
        return c
    def plain(kk):
        mk = ins[kk].mnemonic
        return not (mk.startswith("b.") or mk in ("cbz", "cbnz", "tbz", "tbnz", "b", "ret", "br", "blr"))
    LIVE_ = {}
    def live_dataflow_():
        n_ = len(ins)
        ui_, di_, uf_, df_, succ_ = [], [], [], [], []
        for kk_, ii in enumerate(ins):
            r_, w_ = rw(ii); fr_, fw_ = frw(ii)
            r_, w_, fr_, fw_ = set(r_), set(w_), set(fr_), set(fw_)
            mk = ii.mnemonic
            if mk in ("bl", "blr"):
                r_ |= set(range(8)); fr_ |= set(range(8))
                w_ |= set(range(19)); fw_ |= set(range(8)) | set(range(16, 32))
            elif mk == "ret":
                r_ |= {0}; fr_ |= {0}
            elif mk == "br" or (mk == "b" and imm(ii.op_str) not in addr_index):
                r_ |= set(range(8)); fr_ |= set(range(8))
            ui_.append(r_); di_.append(w_); uf_.append(fr_); df_.append(fw_)
            succ_.append(raw_succ_(kk_))
        li_ = [set() for _ in range(n_)]; lf_ = [set() for _ in range(n_)]
        changed_ = True
        while changed_:
            changed_ = False
            for kk_ in range(n_ - 1, -1, -1):
                oi_, of_ = set(), set()
                for s_ in succ_[kk_]:
                    oi_ |= li_[s_]; of_ |= lf_[s_]
                ni_ = ui_[kk_] | (oi_ - di_[kk_]); nf_ = uf_[kk_] | (of_ - df_[kk_])
                if ni_ != li_[kk_] or nf_ != lf_[kk_]:
                    li_[kk_], lf_[kk_] = ni_, nf_; changed_ = True
        LIVE_["i"], LIVE_["f"] = li_, lf_
    def live_at(kk, inloop=True):
        # dataflow liveness at every join; the old linear scan (fallthrough only, up to the first ret) is the
        # linlive knob, and outside loops also with oldlive
        if "oldlive" not in knobs and (inloop or "linlive" not in knobs):
            if not LIVE_:
                live_dataflow_()
            if kk >= len(ins):
                return set(), set()
            return set(LIVE_["i"][kk]), set(LIVE_["f"][kk])
        live, written_, flive, fwritten = set(), set(), set(), set()
        while kk < len(ins):
            ii = ins[kk]
            if ii.mnemonic in ("bl", "blr"):
                # arguments are read; x0-x7/s0-s7 may be read by the callee
                live |= {r for r in range(8) if r not in written_}
                flive |= {r for r in range(8) if r not in fwritten}
                written_ |= set(range(19)); fwritten |= set(range(8)) | set(range(16, 32))
            reads_, writes_ = rw(ii)
            live |= {r for r in reads_ if r not in written_}
            written_ |= writes_
            freads, fwrites = frw(ii)
            flive |= {r for r in freads if r not in fwritten}
            fwritten |= fwrites
            if ii.mnemonic == "ret":
                live |= {0} - written_
                flive |= {0} - fwritten
                break
            if "oldtaillive" not in knobs and (ii.mnemonic == "br" or (ii.mnemonic == "b" and imm(ii.op_str) not in addr_index)):
                # a tail call passes the argument registers on
                live |= set(range(8)) - written_
                flive |= set(range(8)) - fwritten
                break
            kk += 1
        return live, flive
    def returns_straight(kk):
        while kk < len(ins):
            mk = ins[kk].mnemonic
            if mk == "ret":
                return True
            if mk.startswith("b") and mk != "bl" or mk in ("cbz", "cbnz", "tbz", "tbnz"):
                return mk == "b" and imm(ins[kk].op_str) not in addr_index
            kk += 1
        return False
    def region_ok(lo, hi, join_=None):
        """Every branch in [lo, hi) stays inside [lo, hi] (or goes to join_) or leaves through a return or tail call."""
        for kk in range(lo, hi):
            mk = ins[kk].mnemonic
            if mk.startswith("b.") or mk in ("cbz", "cbnz", "tbz", "tbnz") or mk == "b":
                tv = imm(ins[kk].op_str.split(",")[-1])
                t2 = addr_index.get(tv)
                if t2 is None:
                    if mk != "b":
                        return False
                    continue
                if lo <= t2 <= hi and t2 > kk:
                    continue
                if join_ is not None and t2 == join_ and t2 > kk:
                    continue
                if returns_straight(t2):
                    continue
                return False
            if mk in ("br",):
                return False
        return True
    def diamond(k, tgt):
        """For a conditional branch at k to tgt: (then range, else range, join) or None."""
        if tgt is None or tgt <= k + 1:
            return None
        for H_, L_ in loop_info:
            inside = H_ <= k and tgt <= L_
            outside = (tgt <= H_ or k > L_) and not (H_ <= k <= L_ and tgt > L_)
            if not (inside or outside):
                return None
        last = ins[tgt - 1]
        if last.mnemonic == "b" and imm(last.op_str) in addr_index and addr_index[imm(last.op_str)] > tgt:
            join = addr_index[imm(last.op_str)]
            if any(k < H_ <= join for H_, L_ in loop_info):
                return None
            if region_ok(k + 1, tgt - 1, join) and region_ok(tgt, join):
                return (k + 1, tgt - 1), (tgt, join), join
            return None
        if region_ok(k + 1, tgt):
            return (k + 1, tgt), None, tgt
        return None
    def straight(rng, regs, flags, written, alt=None):
        """Run a branch-free region; returns (items, regs, flags, written)."""
        lt = {}
        its = walk(rng[0], regs, flags, written, 0, stop=rng[1], latch=lt, region=True, alt=alt)
        if "regs" not in lt:
            return its, None, None, None
        return its, lt["regs"], lt["flags"], lt["written"]
    in_loop = set()
    def walk(k, regs, flags, written, depth, stop=None, latch=None, region=False, alt=None):
        if depth > (6 if "deep6" in knobs else 8):
            raise Fail("deep")
        items = []
        while True:
            if k >= len(ins):
                raise Fail("fell off")
            i = ins[k]; m = i.mnemonic
            ops = [o.strip() for o in re.split(r",(?![^\[]*\])", i.op_str)] if i.op_str else []
            if m.startswith("ldur") or m.startswith("stur"):
                m = "ldr" + m[4:] if m.startswith("ldur") else "str" + m[4:]
            if stop is not None and (k == stop or (alt is not None and k == alt)) and region:
                latch["regs"] = regs; latch["flags"] = flags; latch["written"] = set(written)
                return items
            if region and stop is not None and k > stop and k != alt:
                if "noloopjoin" in knobs or not (ins[k].mnemonic == "ret" or returns_straight(k)):
                    raise Fail("escaped region")
            if m == "nop_":
                k += 1; continue
            if m == "spinlock_" and not (stop is not None and k == stop):
                bs_, vs_, ts_, ss_ = i.spin
                sn, base, off2 = field(regs, bs_, 0, "long" if ts_.startswith("x") else "int")
                val_ = use(regs, vs_)
                if val_[0] == "ext" and val_[2][0] == "const":
                    val_ = ("const", val_[2][1], ts_[0])    # a 32-bit mov of the constant, read as 64 bits
                items.append(("spin", sn, off2, base, val_, ts_[0]))
                regs[regname(ts_)[0]] = None; regs[regname(ss_)[0]] = None
                k += 1; continue
            if stop is not None and k == stop and not region:
                if m.startswith("b."):
                    if flags is None or (m[2:] not in CC and not (flags[0] == "fcmp" and m[2:] in ("mi", "pl"))):
                        raise Fail("latch flags")
                    cnd = (flags, m[2:])
                elif m in ("cbz", "cbnz"):
                    x = use(regs, ops[0])
                    cnd = (("cmp", x, ("const", 0, regname(ops[0])[1]), regname(ops[0])[1]), "eq" if m == "cbz" else "ne")
                elif m in ("tbz", "tbnz"):
                    x = use(regs, ops[0]); bit = imm(ops[1])
                    cnd = (("tst", x, ("const", 1 << bit, regname(ops[0])[1]), regname(ops[0])[1]), "eq" if m == "tbz" else "ne")
                elif m == "b" and imm(ops[0]) in addr_index and addr_index[imm(ops[0])] in INF_:
                    cnd = None
                else:
                    raise Fail("latch kind")
                latch["cnd"] = cnd; latch["regs"] = copyregs(regs); latch["flags"] = flags; latch["written"] = set(written)
                return items
            if any(k == H_ for H_, L_ in loop_info) and k not in in_loop:
                H, L = next((H_, L_) for H_, L_ in loop_info if H_ == k)
                wr_in, first = set(), set()
                for kk in range(H, L + 1):
                    reads_, writes_ = rw(ins[kk])
                    first |= {r for r in reads_ if r not in wr_in}
                    wr_in |= writes_
                after, wa = set(), set()
                for kk in range(L + 1, len(ins)):
                    reads_, writes_ = rw(ins[kk])
                    after |= {r for r in reads_ if r not in wa}
                    wa |= writes_
                carried = sorted(r for r in wr_in & first if r < 31)
                inits = []
                shifts_ = {}
                for r in carried:
                    v = regs.get(r)
                    if v is None:
                        raise Fail("carried undefined")
                    name = f"r{counter[0]}"; counter[0] += 1
                    c_ = 0
                    if "ptrloop" not in knobs and v[0] == "bin" and v[1] == "+" and cval_(v[3]) is not None and v[4] == "x" and 0 < cval_(v[3]) < 0x1000000 \
                            and v[2][0] in ("param", "var", "local", "gotaddr"):
                        c_ = cval_(v[3]); v = v[2]
                    vars_[name] = ("loopvar", v)
                    inits.append((name, v, r))
                    regs[r] = ("var", name) if not c_ else ("bin", "+", ("var", name), ("const", c_, "x"), "x", "add")
                    shifts_[name] = c_
                in_loop.add(H)
                lt = {}
                body = walk(H, regs, flags, written, depth + 1, stop=L, latch=lt)
                in_loop.discard(H)
                if "cnd" not in lt or "regs" not in lt:
                    raise Fail("latch unreached")
                lregs = lt["regs"]
                def lin_(e):
                    s_ = 0
                    while e is not None and e[0] == "bin" and e[1] == "+" and e[3][0] == "const" and e[4] == "x":
                        s_ += e[3][1]; e = e[2]
                    return e, s_
                updates = []
                for name, v, r in inits:
                    nv = lregs.get(r)
                    if nv is None:
                        raise Fail("carried lost")
                    if shifts_.get(name):
                        core_, s_ = lin_(nv)
                        if core_ != ("var", name):
                            raise Fail("rebased loop variable")
                        s_ -= shifts_[name]
                        nv = ("bin", "+", ("var", name), ("const", s_, "x"), "x", "add") if s_ else ("var", name)
                        lregs[r] = nv
                    if nv != ("var", name):
                        updates.append((name, nv))
                for ix_, (name, v, r) in enumerate(inits):
                    nv_ = dict(updates).get(name)
                    if nv_ is not None and nv_[0] == "bin" and nv_[4] == "x" and v[0] == "const" and v[2] == "w":
                        v2_ = ("const", v[1], "x")
                        inits[ix_] = (name, v2_, r)
                        vars_[name] = ("loopvar", v2_)
                upd_names = {n for n, _ in updates}
                newmap = {nv: ("var", n) for n, nv in updates}
                pre = [False]
                def subst(e):
                    if e in newmap:
                        return newmap[e]
                    if e[0] == "var" and e[1] in upd_names:
                        pre[0] = True
                        return e
                    if e[0] == "bin":
                        return (e[0], e[1], subst(e[2]), subst(e[3])) + tuple(e[4:])
                    return e
                if lt["cnd"] is None:
                    lt["cnd"] = (("cmp", ("const", 1, "w"), ("const", 0, "w"), "w"), "ne")  # for (;;)
                if lt["cnd"][0] is None or lt["cnd"][0][0] not in ("cmp", "tst"):
                    raise Fail("loop condition kind")
                (fk, fx, fy, fw_), cc = lt["cnd"]
                def norm_(e):
                    core_, s_ = lin_(e)
                    if core_ is not None and core_[0] == "var" and shifts_.get(core_[1]):
                        s2_ = s_ - shifts_[core_[1]]
                        e2_ = ("bin", "+", core_, ("const", s2_, "x"), "x", "add") if s2_ else core_
                        if e2_ in newmap:
                            r_ = newmap[e2_]
                            return ("bin", "+", r_, ("const", shifts_[core_[1]], "x"), "x", "add")
                    return e
                fx, fy = norm_(fx), norm_(fy)
                cond_new = ((fk, subst(fx), subst(fy), fw_), cc)
                if pre[0]:
                    cond_new = lt["cnd"]
                def fix_conts_(its_, inner_):
                    out_ = []
                    for it_ in its_:
                        if it_[0] == "cont" and it_[2] == H:
                            if inner_:
                                raise Fail("continue from an inner loop")
                            if any(shifts_.get(n_) for n_, v_, r_ in inits):
                                raise Fail("continue rebased")
                            asg_ = []
                            for n_, v_, r_ in inits:
                                nv_ = it_[1].get(r_)
                                if nv_ is None:
                                    raise Fail("continue carried lost")
                                if nv_ != ("var", n_):
                                    asg_.append((n_, nv_))
                            it_ = ("contassign", asg_)
                        elif it_[0] == "if":
                            it_ = ("if", it_[1], fix_conts_(it_[2], inner_))
                        elif it_[0] == "diamond":
                            it_ = (it_[0], it_[1], it_[2], fix_conts_(it_[3], inner_), fix_conts_(it_[4], inner_))
                        elif it_[0] == "loop":
                            it_ = (it_[0], it_[1], fix_conts_(it_[2], True)) + tuple(it_[3:])
                        out_.append(it_)
                    return out_
                body = fix_conts_(body, False)
                if H in INF_:
                    body = body + [("contassign", [(n_, nv_) for n_, nv_ in updates])]
                    items.append(("loop", inits, body, [], (("cmp", ("const", 1, "w"), ("const", 0, "w"), "w"), "ne"), False))
                    return items
                items.append(("loop", inits, body, updates, cond_new, pre[0]))
                for name, v, r in inits:
                    lregs[r] = ("var", name) if not shifts_.get(name) else ("bin", "+", ("var", name), ("const", shifts_[name], "x"), "x", "add")
                regs = lregs
                flags = None
                written = set()
                k = L + 1
                continue
            if is_frame(i):
                k += 1; continue
            if m == "ret" and sret_:
                structs.setdefault(RETN_, {})
                items.append(("return", ("retval",)))
                returns.append(("retval",))
                return items
            if k in jt_skip_:
                if i.mnemonic == "ldrsw":
                    jt_idx_[jt_skip_[k]] = regs.get(jt_[jt_skip_[k]][1])
                k += 1; continue
            if m == "br" and k in jt_:
                # a switch: the bound check in front is its default; each table entry is a case
                T_ = jt_[k][0]
                idx_ = jt_idx_.get(k)
                if stop is not None or idx_ is None or not items or items[-1][0] != "if":
                    raise Fail("switch shape")
                f_, cc_ = items[-1][1]
                if f_ is None or f_[0] != "cmp" or cc_ != "hi" or f_[2][0] != "const" or f_[1] != idx_:
                    raise Fail("switch bound")
                kh_ = next((kk for kk in range(k - 1, -1, -1) if ins[kk].mnemonic == "b.hi"), None)
                if kh_ is None:
                    raise Fail("switch bound")
                D_ = addr_index[imm(ins[kh_].op_str)]
                n_ = f_[2][1] + 1
                if idx_[0] == "bin" and idx_[1] in ("-", "+") and cval_(idx_[3]) is not None:
                    sv_ = idx_[2]; lo_ = cval_(idx_[3]) if idx_[1] == "-" else -cval_(idx_[3])
                elif idx_[0] == "range":
                    sv_, lo_ = idx_[1], idx_[2]
                else:
                    sv_, lo_ = idx_, 0
                if sv_[0] == "param" and pwidth.get(sv_[1]) is None:
                    pwidth[sv_[1]] = f_[3]
                default_ = items.pop()[2]
                groups_ = {}
                for j_ in range(n_):
                    tv_ = T_ + struct.unpack_from("<i", d, T_ + 4 * j_)[0]
                    if tv_ not in addr_index:
                        raise Fail("switch target outside")
                    if addr_index[tv_] != D_:
                        groups_.setdefault(addr_index[tv_], []).append(j_ + lo_)
                body_ = []
                # a case landing on a bare ret (its value set before the jump) comes first, then the rest in layout order
                for t_ in sorted(set(groups_) | {D_}, key=lambda t2_: (ins[t2_].mnemonic != "ret" or t2_ == D_, t2_)):
                    body_.append(("case", groups_.get(t_)))
                    body_.extend(default_ if t_ == D_ else walk(t_, copyregs(regs), flags, set(written), depth + 1))
                jtabs_.append((T_, 4 * n_))
                items.append(("if", (("switch", sv_, ("const", 0, f_[3])), "switch"), body_))
                return items
            if m == "ret" and "novecu" not in knobs and (regs.get(0) or ("",))[0] == "vpart" and (regs.get(1) or ("",))[0] == "vpart" \
                    and regs[0][1] == regs[1][1] and regs[0][2] == 0 and regs[1][2] == 1:
                items.append(("return", ("vecu", regs[0][1])))
                returns.append(items[-1][1])
                return items
            if m == "ret":
                v = regs.get(0)
                fv = regs["f"].get(0)
                def computed_float(x):
                    if x is None or x == ("fparam", 0):
                        return False
                    if x[0] in ("fbin", "fconst", "i2f", "funary", "fselect", "vlane", "f2y"):
                        return True
                    if x[0] == "var":
                        tv = vars_.get(x[1])
                        if isinstance(tv, tuple) and tv[0] == "merge":
                            return computed_float(tv[1]) or computed_float(tv[2])
                        return tv == "f" or (isinstance(tv, tuple) and tv[0] == "load" and len(tv) > 3 and tv[3] == "float")
                    return False
                def weak_int(x):
                    if x is None or x == ("param", 0):
                        return True
                    if x[0] == "var":
                        tv = vars_.get(x[1])
                        if tv in ("?", "w", "x") and x[1].startswith("c"):
                            return True
                        if tv == "f" and x[1].startswith("c") and "novcallf" not in knobs:
                            return True
                        if isinstance(tv, tuple) and tv[0] == "merge":
                            return weak_int(tv[1]) and weak_int(tv[2])
                    return False
                fv1 = regs["f"].get(1)
                def is_vec_(x):
                    tv_ = vars_.get(x[1]) if x is not None and x[0] == "var" else None
                    return isinstance(tv_, tuple) and tv_[0] == "load" and structs[tv_[1]][tv_[2]][0] == "Vec4f"
                if is_vec_(fv):
                    fv = None
                if is_vec_(fv1):
                    fv1 = None
                if fv is not None and fv[0] != "fparam" and fv1 is not None and fv1[0] != "fparam" and weak_int(v):
                    # s1 written and not read again before the return: two floats returned as one struct
                    last_w = None
                    for kk_ in range(k - 1, -1, -1):
                        if 1 in frw(ins[kk_])[1]:
                            last_w = kk_; break
                    if last_w is not None and not any(1 in frw(ins[kk_])[0] for kk_ in range(last_w + 1, k)):
                        if fv[0] == "var" and vars_.get(fv[1]) == "?":
                            vars_[fv[1]] = "f"
                        if fv1[0] == "var" and vars_.get(fv1[1]) == "?":
                            vars_[fv1[1]] = "f"
                        items.append(("return", ("pair", fv, fv1)))
                        returns.append(items[-1][1])
                        return items
                if "noretthis" not in knobs and v == ("param", 0) and 0 in written:
                    # x0 set back to the incoming first argument since the last call (mov x0, x19): the function
                    # returns it, as a placement constructor returns this
                    items.append(("return", ("param", 0)))
                    returns.append(items[-1][1])
                    return items
                if v != ("param", 0) and computed_float(fv) and weak_int(v):
                    v = ("param", 0)
                if v == ("param", 0) and fv is not None and fv != ("fparam", 0):
                    v = fv
                    if v[0] == "var" and vars_.get(v[1]) == "?":
                        vars_[v[1]] = "f"
                f2_type_(v)
                items.append(("return", v if v != ("param", 0) else None))
                returns.append(items[-1][1])
                return items
            if m == "b" and imm(ops[0]) not in addr_index:
                t = imm(ops[0])
                call_k_[0] = k
                r = call(regs, written, t, items, True)
                items.append(("return", r))
                returns.append(r)
                return items
            wl_ = (next((L_ for H_, L_ in loop_info if H_ == k + 1), None)
                   if m == "b" and "nowhile" not in knobs and imm(ops[0]) in addr_index and (k + 1) not in in_loop else None)
            if wl_ is not None and k + 1 < addr_index[imm(ops[0])] <= wl_ and ins[wl_].mnemonic != "b":
                H, L, C = k + 1, wl_, addr_index[imm(ops[0])]
                ltg_ = {}
                g_items_ = walk(C, copyregs(regs), flags, set(written), depth + 1, stop=L, latch=ltg_)
                if "cnd" not in ltg_ or ltg_["cnd"] is None:
                    raise Fail("while guard")
                items.extend(g_items_)
                gregs_ = ltg_["regs"]
                lt2_ = {}
                l_items_ = walk(H, copyregs(gregs_), None, set(ltg_["written"]), depth + 1, stop=L + 1, latch=lt2_, region=True)
                if "regs" not in lt2_:
                    raise Fail("while exit")
                lregs_ = lt2_["regs"]
                live_i, live_f = live_at(L + 1, any(H_ <= L + 1 <= L_ for H_, L_ in loop_info))
                merged = copyregs(gregs_)
                decls_, asg_l_, asg_g_ = [], [], []
                keys = sorted([(n, None) for n in set(gregs_) | set(lregs_) if isinstance(n, int)]
                              + [(n, "f") for n in set(gregs_["f"]) | set(lregs_["f"])], key=lambda k_: (k_[1] or "", k_[0]))
                for n, kind in keys:
                    a_ = (gregs_["f"] if kind else gregs_).get(n)
                    b_ = (lregs_["f"] if kind else lregs_).get(n)
                    if a_ == b_:
                        continue
                    if a_ is None or b_ is None or n not in (live_f if kind else live_i) \
                            or any((x_ or ("",))[0] == "hi" for x_ in (a_, b_)):
                        (merged["f"] if kind else merged)[n] = None
                        continue
                    name = f"m{counter[0]}"; counter[0] += 1
                    vars_[name] = ("merge", b_, a_)
                    if kind:
                        fmerges_.add(name)
                    decls_.append((name, b_))
                    asg_l_.append((name, b_)); asg_g_.append((name, a_))
                    (merged["f"] if kind else merged)[n] = ("var", name)
                for n in [n for n in set(gregs_) | set(lregs_) if isinstance(n, tuple) and n[0] == "spill"]:
                    if gregs_.get(n) != lregs_.get(n):
                        merged[n] = None
                if decls_:
                    items.append(("diamond", ltg_["cnd"], decls_, l_items_ + [("assign", n_, v_) for n_, v_ in asg_l_],
                                  [("assign", n_, v_) for n_, v_ in asg_g_]))
                else:
                    items.append(("if", ltg_["cnd"], l_items_))
                regs = merged
                regs["fw"] = set()
                flags = None
                written = set(ltg_["written"]) & set(lt2_.get("written", set()))
                k = L + 1
                continue
            if m == "b" and CONT_.get(k) == addr_index[imm(ops[0])] and addr_index[imm(ops[0])] in in_loop:
                items.append(("cont", copyregs(regs), addr_index[imm(ops[0])]))
                return items
            if m == "b":
                k = addr_index[imm(ops[0])]; continue
            if m == "bl" and "novalinit" not in knobs and PLT.get(f"{imm(ops[0]):x}") == "memset" and epilogue_next_(k):
                d_, v_, n_ = regs.get(0), regs.get(1), regs.get(2)
                if d_ is not None and d_[0] != "hi" and v_ is not None and v_[0] == "const" and n_ is not None and n_[0] == "const":
                    if d_[0] == "param" and pwidth.get(d_[1]) is None:
                        pwidth[d_[1]] = "x"
                    items.append(("valinit", d_, n_[1], v_[1] & 0xff))
                    valinit_imp_.add(imm(ops[0]))
                    for n in list(regs):
                        if isinstance(n, int) and n < 19:
                            regs[n] = None
                    regs["f"] = {n2: v2 for n2, v2 in regs["f"].items() if 8 <= n2 <= 15}
                    regs["fw"] = set()
                    written = set()
                    flags = None
                    k += 1; continue
            if m == "bl":
                call_k_[0] = k
                r = call(regs, written, imm(ops[0]), items, False)
                for n in list(regs):
                    if isinstance(n, int) and n < 19:
                        regs[n] = None
                regs[0] = r
                if "nopair16" not in knobs and r is not None and r[0] == "var":
                    regs[1] = ("hi", r[1])
                regs["f"] = {n2: v2 for n2, v2 in regs["f"].items() if 8 <= n2 <= 15}
                regs["f"][0] = r
                if "nof2call" not in knobs and r is not None and r[0] == "var" and freg_read_next_(k, 1):
                    regs["f"][1] = ("f2y", r)
                regs["fw"] = set()
                written = set()
                flags = None
                k += 1; continue
            if (m.startswith("b.") or m in ("cbz", "cbnz", "tbz", "tbnz")) and stop is None or ((m.startswith("b.") or m in ("cbz", "cbnz", "tbz", "tbnz")) and stop is not None and k != stop):
                tgt = addr_index.get(imm(ops[-1]))
                dregion = None; alt_inner_ = None
                if "forkjoin" not in knobs and tgt is not None and tgt > k:
                    J_ = ipdom_(k)
                    lj_ = stop is not None and not region and "noloopjoin" not in knobs
                    def block_start_(e_):
                        def isbr_(mk_):
                            return mk_ == "b" or mk_.startswith("b.") or mk_ in ("cbz", "cbnz", "tbz", "tbnz")
                        targets_ = {addr_index.get(imm(x_.op_str.split(",")[-1])) for x_ in ins if isbr_(x_.mnemonic)}
                        s_ = e_
                        while s_ - 1 > k and s_ not in targets_:
                            pm_ = ins[s_ - 1].mnemonic
                            if isbr_(pm_) or pm_ in ("ret", "br"):
                                break
                            s_ -= 1
                        return s_
                    if J_ == EXIT_ or J_ is None:
                        J_ = (block_start_(stop) if lj_ else stop) if (stop is not None and (region or lj_)) else None
                    elif stop is not None and J_ > stop:
                        J_ = block_start_(stop) if lj_ else None
                    if J_ is not None and J_ > k + 1 and tgt <= J_:
                        dregion = ((k + 1, J_), (tgt, J_) if tgt < J_ else None, J_)
                if dregion is None and region and alt is not None and tgt == alt and stop is not None and stop > k + 1 and region_ok(k + 1, stop, alt):
                    dregion = ((k + 1, stop), None, stop)
                    alt_inner_ = alt
                elif dregion is None:
                    dregion = diamond(k, tgt) if tgt is not None else None
                    if dregion is not None and region and stop is not None and dregion[2] > stop:
                        dregion = None
                if dregion is not None:
                    then_rng, else_rng, join = dregion
                    if m.startswith("b."):
                        if flags is None or (m[2:] not in CC and not (flags[0] == "fcmp" and m[2:] in ("mi", "pl"))
                                             and not (flags[0] == "ccmp" and flags[3][0] == "fcmp" and m[2:] in ("mi", "pl") and "nofccmp" not in knobs)):
                            raise Fail("flags")
                        cnd = (flags, m[2:])
                    elif m in ("cbz", "cbnz"):
                        x = use(regs, ops[0])
                        cnd = (("cmp", x, ("const", 0, regname(ops[0])[1]), regname(ops[0])[1]), "eq" if m == "cbz" else "ne")
                    else:
                        x = use(regs, ops[0]); bit = imm(ops[1])
                        cnd = (("tst", x, ("const", 1 << bit, regname(ops[0])[1]), regname(ops[0])[1]), "eq" if m == "tbz" else "ne")
                    r1 = copyregs(regs); w1 = set(written)
                    its1, r1, f1, w1 = straight(then_rng, r1, flags, w1, alt=join if else_rng else alt_inner_)
                    r2 = copyregs(regs); w2 = set(written)
                    if else_rng:
                        its2, r2, f2, w2 = straight(else_rng, r2, flags, w2)
                    else:
                        its2 = []
                    if r1 is None and r2 is None:
                        items.append(("diamond", cnd, [], its2, its1))
                        return items
                    if r1 is None or r2 is None:
                        live = r2 if r1 is None else r1
                        items.append(("diamond", cnd, [], its2, its1))
                        regs = live
                        regs["fw"] = set()
                        written = (w2 if r1 is None else w1) or set()
                        flags = None
                        k = join
                        continue
                    merged = copyregs(regs)
                    assigns1, assigns2, decls_ = [], [], []
                    live_i, live_f = live_at(alt_inner_ if alt_inner_ is not None else join,
                                             any(H_ <= k <= L_ for H_, L_ in loop_info))
                    keys = [(n, None) for n in set(r1) | set(r2) if isinstance(n, int)] + [(n, "f") for n in set(r1["f"]) | set(r2["f"])]
                    if "nosortjoin" not in knobs:
                        keys = sorted(keys, key=lambda k_: (k_[1] or "", k_[0]))
                    # spill slots are carried across the join like registers (a value saved before the branch and
                    # reloaded after it); they are memory, so no liveness test applies
                    if "nospillmerge" not in knobs:
                        keys += sorted([(n, "s") for n in set(r1) | set(r2) if isinstance(n, tuple) and n[0] == "spill"], key=repr)
                    for n, kind in keys:
                        a_ = (r1["f"] if kind == "f" else r1).get(n)
                        b_ = (r2["f"] if kind == "f" else r2).get(n)
                        if a_ != b_ and ((a_ or ("",))[0] == "hi" or (b_ or ("",))[0] == "hi"):
                            a_ = b_ = None
                        if a_ == b_:
                            (merged["f"] if kind == "f" else merged)[n] = a_
                            continue
                        if a_ is None or b_ is None or (kind != "s" and n not in (live_f if kind else live_i)):
                            (merged["f"] if kind == "f" else merged)[n] = None
                            continue
                        if kind == "f" and "vlanemerge" in knobs and is_vecval_(a_) != is_vecval_(b_) \
                                and not any(x_[0] in ("ivec", "fbits") for x_ in (a_, b_)):
                            # a vector on one arm and a scalar on the other: the scalar is lane 0
                            a_, b_ = [("vlane", x_, 0) if is_vecval_(x_) else x_ for x_ in (a_, b_)]
                        if kind == "f" and "nofmerge" not in knobs:
                            # a float register holds floats: an untyped call result merged there is one, and an
                            # int or pointer side (or a call result merged in a general register at this join too)
                            # is the stale s0 of an int call
                            if "i" in (fmerge_side_(a_), fmerge_side_(b_)):
                                merged["f"][n] = None
                                continue
                        if any(x_[0] == "f2y" and vars_.get(x_[1][1]) not in ("?", "f", "Float2") for x_ in (a_, b_)):
                            # the .y of an int call result: not a float pair, so not carried over the join
                            (merged["f"] if kind == "f" else merged)[n] = None
                            continue
                        name = f"m{counter[0]}"; counter[0] += 1
                        vars_[name] = ("merge", a_, b_)
                        f2_type_(a_); f2_type_(b_)
                        if kind == "f":
                            fmerges_.add(name)
                        decls_.append((name, a_))
                        assigns1.append((name, a_)); assigns2.append((name, b_))
                        (merged["f"] if kind == "f" else merged)[n] = ("var", name)
                    items.append(("diamond", cnd, decls_, its2 + [("assign", n_, v_) for n_, v_ in assigns2],
                                  its1 + [("assign", n_, v_) for n_, v_ in assigns1]))
                    regs = merged
                    regs["fw"] = set()
                    written = w1 & w2
                    flags = None
                    k = join
                    continue
            if m.startswith("b.") or m in ("cbz", "cbnz", "tbz", "tbnz"):
                t = addr_index[imm(ops[-1])]
                if m.startswith("b."):
                    if flags is None or (m[2:] not in CC and not (flags[0] == "fcmp" and m[2:] in ("mi", "pl"))
                                         and not (flags[0] == "ccmp" and flags[3][0] == "fcmp" and m[2:] in ("mi", "pl") and "nofccmp" not in knobs)):
                        raise Fail("flags")
                    cnd = (flags, m[2:])
                elif m in ("cbz", "cbnz"):
                    x = use(regs, ops[0])
                    cnd = (("cmp", x, ("const", 0, regname(ops[0])[1]), regname(ops[0])[1]), "eq" if m == "cbz" else "ne")
                else:
                    x = use(regs, ops[0]); bit = imm(ops[1])
                    cnd = (("tst", x, ("const", 1 << bit, regname(ops[0])[1]), regname(ops[0])[1]), "eq" if m == "tbz" else "ne")
                if CONT_.get(k) == t and t in in_loop:
                    items.append(("if", cnd, [("cont", copyregs(regs), t)]))
                    k += 1; continue
                if t <= k and t not in epi_ and k not in fwdjump_:
                    raise Fail("backward branch in loop")
                body = walk(t, copyregs(regs), flags, set(written), depth + 1)
                items.append(("if", cnd, body))
                k += 1; continue
            sbase = None
            if len(ops) >= 2 and ops[-1].startswith("[") and (ops[-1].startswith("[sp") or ops[-1].startswith("[x29")):
                parts_ = [p.strip() for p in ops[-1].strip("[]!").split(",")]
                rel = imm(parts_[1]) if len(parts_) > 1 else 0
                if ops[-1].endswith("!"):
                    raise Fail("stack writeback")
                if parts_[0] == "x29":
                    if fp_off is None:
                        raise Fail("no fp")
                    rel += fp_off
                sbase = rel
            if m == "mov" and len(ops) == 2 and re.fullmatch(r"v\d+\.(16|8)b", ops[0]) and re.fullmatch(r"v\d+\.(16|8)b", ops[1]):
                fd_ = int(ops[0][1:].split(".")[0]); fs_ = int(ops[1][1:].split(".")[0])
                v_ = regs["f"].get(fs_)
                if v_ is None:
                    raise Fail("undefined vector copy")
                if v_[0] == "fparam":
                    fparams.add(v_[1])
                regs["f"][fd_] = v_
                if fd_ < 8: regs.setdefault("fw", set()).add(fd_)
                k += 1; continue
            if "novecins" not in knobs and "novec" not in knobs and len(ops) == 2 and m in ("mov", "ins") \
                    and re.fullmatch(r"v\d+\.s\[\d\]", ops[0]) and (re.fullmatch(r"v\d+\.s\[\d\]", ops[1]) or re.fullmatch(r"w\d+|wzr", ops[1])):
                # set one lane of a vector (a vector built lane by lane starts undefined, lane 0 the scalar in sD)
                mi_ = re.fullmatch(r"v(\d+)\.s\[(\d)\]", ops[0])
                dn_, li_ = int(mi_.group(1)), int(mi_.group(2))
                if ops[1].startswith("v"):
                    sv_ = fuse(regs["f"], ops[1])
                elif ops[1] == "wzr":
                    sv_ = ("fconst", 0.0)
                else:
                    iv_ = use(regs, ops[1])
                    if iv_[0] != "const":
                        raise Fail("lane insert of an integer")
                    import struct as _st
                    sv_ = ("fconst", _st.unpack("<f", _st.pack("<I", iv_[1] & 0xffffffff))[0])
                base_ = regs["f"].get(dn_)
                if base_ is None:
                    base_ = ("vundef",)
                elif not is_vecval_(base_):
                    if base_[0] == "fsqrtp":
                        raise Fail("fsqrt")
                    base_ = ("vins", ("vundef",), base_, 0)
                regs["f"][dn_] = ("vins", base_, sv_, li_)
                if dn_ < 8: regs.setdefault("fw", set()).add(dn_)
                k += 1; continue
            if "novecu" not in knobs and len(ops) == 2 and m in ("fmov", "mov") and (
                    (m == "fmov" and re.fullmatch(r"d\d+", ops[0]) and re.fullmatch(r"x\d+", ops[1])) or
                    (m == "mov" and re.fullmatch(r"v\d+\.d\[1\]", ops[0]) and re.fullmatch(r"x\d+", ops[1])) or
                    (m == "fmov" and re.fullmatch(r"x\d+", ops[0]) and re.fullmatch(r"d\d+", ops[1])) or
                    (m == "mov" and re.fullmatch(r"x\d+", ops[0]) and re.fullmatch(r"v\d+\.d\[1\]", ops[1]))):
                # a 16-byte vector moved between two x registers and a q register
                if ops[0][0] in "dv":
                    fn_ = int(re.match(r"[dv](\d+)", ops[0]).group(1))
                    xv_ = regs.get(regname(ops[1])[0])
                    if xv_ is None:
                        raise Fail("undefined vector half")
                    if ops[0][0] == "d":
                        regs["f"][fn_] = ("vlo", xv_)
                    else:
                        lo_ = regs["f"].get(fn_)
                        if lo_ is None or lo_[0] != "vlo":
                            raise Fail("vector high half alone")
                        lo_ = lo_[1]
                        if lo_[0] == "param" and xv_ == ("param", lo_[1] + 1) and pwidth.get(lo_[1]) in (None, "x") \
                                and pwidth.get(lo_[1] + 1) in (None, "x"):
                            pwidth[lo_[1]] = "VecU"; pwidth[lo_[1] + 1] = "VecU_hi"
                            regs["f"][fn_] = ("vparam", lo_[1])
                        elif lo_[0] == "vpart" and xv_[0] == "vpart" and lo_[1] == xv_[1] and lo_[2] == 0 and xv_[2] == 1:
                            regs["f"][fn_] = lo_[1]
                        elif "novcomb" not in knobs and lo_[0] == "var" and xv_ == ("hi", lo_[1]) and vars_.get(lo_[1]) in ("?", "VecU"):
                            # a call returning a 16-byte vector in x0 and x1
                            vars_[lo_[1]] = "VecU"
                            regs["f"][fn_] = ("vecuv", lo_)
                        elif "novcomb" not in knobs and lo_[0] not in ("vpart", "hi") and xv_[0] not in ("vpart", "hi"):
                            regs["f"][fn_] = ("vcomb", lo_, xv_)
                        else:
                            raise Fail("vector halves")
                    if fn_ < 8: regs.setdefault("fw", set()).add(fn_)
                else:
                    xn_ = regname(ops[0])[0]
                    fn_ = int(re.match(r"[dv](\d+)", ops[1]).group(1))
                    vv_ = regs["f"].get(fn_)
                    if not is_vecval_(vv_):
                        raise Fail("vector half of a scalar")
                    regs[xn_] = ("vpart", vv_, 0 if ops[1][0] == "d" else 1)
                    if xn_ < 8: written.add(xn_)
                k += 1; continue
            if k in copy_skip_:
                if k in copy_emit_:
                    bs_, bd_, slo_, dlo_, R_, n_, al_, st_ = copy_emit_[k]
                    def stk_base_(o_):
                        s0_ = stack_obj(o_)
                        sn0_ = struct_for(("stackobj", s0_))
                        stack_min_[sn0_] = max(stack_min_.get(sn0_, 0), o_ - s0_ + (n_ - 1) * st_ + R_)
                        stack_al_[sn0_] = max(stack_al_.get(sn0_, 1), al_)
                        return ("stackaddr", s0_), o_ - s0_
                    if bs_ == "sp":
                        sv_, slo_ = stk_base_(slo_)
                    else:
                        sv_ = use(regs, bs_) if regs.get(regname(bs_)[0]) is not None else None
                    if bd_ == "sp":
                        dv_, dlo_ = stk_base_(dlo_)
                    else:
                        dv_ = use(regs, bd_) if regs.get(regname(bd_)[0]) is not None else None
                    if sv_ is None or dv_ is None:
                        raise Fail("copy base")
                    items.append(("blkcopy", dv_, dlo_, sv_, slo_, R_, n_, al_, st_))
                k += 1; continue
            ml1_ = re.fullmatch(r"\{v(\d+)\.([sd])\}\[(\d)\], (\[x\d+\])(?:, #(0x[0-9a-f]+|\d+))?", i.op_str) if m in ("ld1", "st1") and "nold1" not in knobs else None
            if ml1_ and not (m == "st1" and ml1_.group(2) == "d") and not (ml1_.group(2) == "d" and ml1_.group(3) != "0"):
                vn_, lk_, li_ = int(ml1_.group(1)), ml1_.group(2), int(ml1_.group(3))
                b, off, idx, sh, ext, pre, post = memop2(ml1_.group(4), ("#" + ml1_.group(5)) if ml1_.group(5) else None)
                bnl_ = regname(b)[0]
                if m == "ld1" and lk_ == "s":
                    sn, base, off2 = field(regs, b, off, "float")
                    name = f"v{counter[0]}"; counter[0] += 1
                    vars_[name] = ("load", sn, off2, "float")
                    items.append(("let", name, sn, off2, base))
                    letbase[name] = base
                    old_ = regs["f"].get(vn_)
                    if old_ is None or not is_vecval_(old_):
                        old_ = ("vundef",)
                    regs["f"][vn_] = ("vins", old_, ("var", name), li_)
                elif m == "ld1":
                    sn, base, off2 = field(regs, b, off, "long")
                    name = f"v{counter[0]}"; counter[0] += 1
                    vars_[name] = ("load", sn, off2, "long")
                    items.append(("let", name, sn, off2, base))
                    letbase[name] = base
                    regs["f"][vn_] = ("vlo", ("var", name))
                else:
                    vv_ = regs["f"].get(vn_)
                    if not is_vecval_(vv_):
                        raise Fail("lane store of a scalar")
                    sn, base, off2 = field(regs, b, off, "float")
                    items.append(("store", sn, off2, base, ("vlane", vv_, li_)))
                if vn_ < 8 and m == "ld1": regs.setdefault("fw", set()).add(vn_)
                if post is not None:
                    regs[bnl_] = ("bin", "+", regs.get(bnl_), ("const", post, "x"), "x", "add")
                k += 1; continue
            if m in ("ldr", "ldur") and k in ivec_loads_ and len(ops) == 2:
                # an int field loaded into a vector register for a conversion to float
                ty_ = ivec_loads_[k]
                fd = int(ops[0][1:])
                b, off, idx, sh, ext, pre, post = memop2(ops[1], None)
                if idx is not None:
                    if sh not in (0, {"int": 2, "unsigned int": 2, "short": 1, "unsigned short": 1, "unsigned char": 0}[ty_]):
                        raise Fail("int vector addressing")
                    basev_ = regs.get(regname(b)[0])
                    sn, base, off2 = field(regs, None, off, "ARRAY:unsigned char" if sh == 0 else "ARRAY:" + ty_, base=basev_, bytecast=sh == 0 and ty_ != "unsigned char")
                    iv = index_value(regs, idx, ext)
                    name = f"v{counter[0]}"; counter[0] += 1
                    vars_[name] = ("load", sn, off2, ty_)
                    items.append(("leti", name, sn, off2, base, iv, ty_) if sh == 0 else ("leti", name, sn, off2, base, iv))
                else:
                    sn, base, off2 = field(regs, b, off, ty_)
                    name = f"v{counter[0]}"; counter[0] += 1
                    vars_[name] = ("load", sn, off2, ty_)
                    items.append(("let", name, sn, off2, base))
                    letbase[name] = base
                regs["f"][fd] = ("ivec", ("var", name))
                if fd < 8: regs.setdefault("fw", set()).add(fd)
                k += 1; continue
            if m in ("sshll", "ushll") and len(ops) == 3 and ops[2] in ("#0", "#0x0") and "noicvt" not in knobs \
                    and re.fullmatch(r"v\d+\.4s", ops[0]) and re.fullmatch(r"v\d+\.4h", ops[1]) \
                    and (regs["f"].get(int(ops[1][1:].split(".")[0])) or ("",))[0] == "ivec":
                fd = int(ops[0][1:].split(".")[0])
                regs["f"][fd] = regs["f"][int(ops[1][1:].split(".")[0])]
                if fd < 8: regs.setdefault("fw", set()).add(fd)
                k += 1; continue
            if m in ("scvtf", "ucvtf") and len(ops) == 2 and re.fullmatch(r"s\d+", ops[0]) and re.fullmatch(r"s\d+", ops[1]) \
                    and (regs["f"].get(int(ops[1][1:])) or ("",))[0] == "ivec":
                fd = int(ops[0][1:])
                regs["f"][fd] = ("i2f", m == "ucvtf", regs["f"][int(ops[1][1:])][1], "w")
                if fd < 8: regs.setdefault("fw", set()).add(fd)
                k += 1; continue
            vd_ = re.fullmatch(r"v(\d+)\.(4s|2d|16b)", ops[0]) if ops else None
            if vd_ and m in ("fadd", "fsub", "fmul", "fmla", "fmls", "fneg", "dup", "movi", "fmov") and "novec" not in knobs:
                dn_ = int(vd_.group(1))
                def vec_(o_):
                    mv_ = re.fullmatch(r"v(\d+)\.4s", o_)
                    if not mv_:
                        raise Fail("vector operand " + o_)
                    v_ = regs["f"].get(int(mv_.group(1)))
                    if not is_vecval_(v_):
                        raise Fail("scalar as vector")
                    return v_
                def lane_op_(o_):
                    ml2_ = re.fullmatch(r"v(\d+)\.s\[(\d)\]", o_)
                    return lane_(regs["f"], int(ml2_.group(1)), int(ml2_.group(2))) if ml2_ else None
                if m in ("fadd", "fsub", "fmul") and len(ops) == 3 and vd_.group(2) == "4s":
                    b_ = lane_op_(ops[2]) if m == "fmul" else None
                    regs["f"][dn_] = ("vbin", {"fadd": "+", "fsub": "-", "fmul": "*"}[m], vec_(ops[1]), b_ if b_ is not None else vec_(ops[2]))
                elif m in ("fmla", "fmls") and len(ops) == 3 and vd_.group(2) == "4s":
                    ml3_ = re.fullmatch(r"v(\d+)\.s\[(\d)\]", ops[2])
                    if ml3_:
                        lv_ = regs["f"].get(int(ml3_.group(1)))
                        if not is_vecval_(lv_):
                            raise Fail("lane of scalar")
                        regs["f"][dn_] = ("vfma", m == "fmls", vec_(ops[0]), vec_(ops[1]), lv_, int(ml3_.group(2)))
                    else:
                        regs["f"][dn_] = ("vfma", m == "fmls", vec_(ops[0]), vec_(ops[1]), vec_(ops[2]), None)
                elif m == "fneg" and len(ops) == 2 and vd_.group(2) == "4s":
                    regs["f"][dn_] = ("vneg", vec_(ops[1]))
                elif m == "dup" and len(ops) == 2 and vd_.group(2) == "4s":
                    if re.fullmatch(r"w\d+", ops[1]):
                        iv_ = use(regs, ops[1])
                        if iv_[0] != "const":
                            raise Fail("dup of a variable")
                        import struct as _st
                        regs["f"][dn_] = ("vsplat", ("fconst", _st.unpack("<f", _st.pack("<I", iv_[1] & 0xffffffff))[0]))
                    else:
                        lo_ = lane_op_(ops[1])
                        if lo_ is None:
                            raise Fail("dup form")
                        regs["f"][dn_] = ("vsplat", lo_)
                elif m == "fmov" and len(ops) == 2 and vd_.group(2) == "4s" and ops[1].startswith("#") and "novecsplat" not in knobs:
                    regs["f"][dn_] = ("vsplat", ("fconst", float(ops[1].lstrip("#"))))
                elif m == "movi" and len(ops) == 2 and re.fullmatch(r"#0+|#0x0+", ops[1]):
                    regs["f"][dn_] = ("vsplat", ("fconst", 0.0))
                else:
                    raise Fail("vector form " + m)
                if dn_ < 8: regs.setdefault("fw", set()).add(dn_)
                k += 1; continue
            if m == "mov" and len(ops) == 2 and re.fullmatch(r"s\d+", ops[0]) and re.fullmatch(r"v\d+\.s\[\d\]", ops[1]):
                fd = fregname(ops[0])
                regs["f"][fd] = fuse(regs["f"], ops[1])
                if fd < 8: regs.setdefault("fw", set()).add(fd)
                k += 1; continue
            fdst = ops[0] if ops and re.fullmatch(r"s\d+", ops[0]) else None
            if fdst and m in ("fmov",) and len(ops) == 2:
                fd = fregname(fdst)
                if ops[1].startswith("#"):
                    regs["f"][fd] = ("fconst", float(ops[1].lstrip("#")))
                elif ops[1] == "wzr":
                    regs["f"][fd] = ("fconst", 0.0)
                elif re.fullmatch(r"s\d+", ops[1]):
                    regs["f"][fd] = fuse(regs["f"], ops[1])
                elif re.fullmatch(r"w\d+", ops[1]) and "nofbits" not in knobs:
                    iv_ = use(regs, ops[1])
                    if iv_[0] == "fbits":
                        regs["f"][fd] = iv_[1]
                    elif iv_[0] == "const":
                        import struct as _st
                        regs["f"][fd] = ("fconst", _st.unpack("<f", _st.pack("<I", iv_[1] & 0xffffffff))[0])
                    elif iv_[0] == "var" and isinstance(vars_.get(iv_[1]), tuple) and vars_[iv_[1]][0] == "load" \
                            and structs[vars_[iv_[1]][1]].get(vars_[iv_[1]][2], ("",))[0] in ("int", "unsigned int"):
                        # an int load that is really a float field
                        vt_ = vars_[iv_[1]]
                        structs[vt_[1]][vt_[2]] = ("float", None)
                        vars_[iv_[1]] = ("load", vt_[1], vt_[2])
                        regs["f"][fd] = iv_
                    elif "noibits" not in knobs and iv_[0] not in ("hi", "vpart", "undef", "fparam"):
                        # the float whose bits an integer value holds (a union passed or returned as integers)
                        regs["f"][fd] = ("ibits", iv_)
                    else:
                        raise Fail("fmov form")
                else:
                    raise Fail("fmov form")
                regs.setdefault("fw", set()).add(fd) if fd < 8 else None
                k += 1; continue
            if fdst and m in ("fadd", "fsub", "fmul", "fdiv") and len(ops) == 3:
                fd = fregname(fdst)
                regs["f"][fd] = ("fbin", {"fadd": "+", "fsub": "-", "fmul": "*", "fdiv": "/"}[m], fuse(regs["f"], ops[1]), fuse(regs["f"], ops[2]))
                if fd < 8: regs.setdefault("fw", set()).add(fd)
                k += 1; continue
            if fdst and m == "fsqrt" and len(ops) == 2:
                # the result may only be read by the NaN check of sqrtf (see the fcmp below)
                regs["f"][fregname(fdst)] = ("fsqrtp", fuse(regs["f"], ops[1]))
                k += 1; continue
            if fdst and m in ("fneg", "fabs") and len(ops) == 2:
                fd = fregname(fdst)
                regs["f"][fd] = ("funary", m, fuse(regs["f"], ops[1]))
                if fd < 8: regs.setdefault("fw", set()).add(fd)
                k += 1; continue
            if fdst and m in ("scvtf", "ucvtf") and len(ops) == 2 and re.fullmatch(r"[wx]\d+", ops[1]):
                fd = fregname(fdst)
                src_ = use(regs, ops[1])
                regs["f"][fd] = ("i2f", m == "ucvtf", src_, regname(ops[1])[1])
                if fd < 8: regs.setdefault("fw", set()).add(fd)
                k += 1; continue
            if m in ("fcvtms", "fcvtmu", "fcvtps", "fcvtpu", "fcvtas", "fcvtau") and len(ops) == 2 and re.fullmatch(r"s\d+", ops[1]) \
                    and re.fullmatch(r"[wx]\d+", ops[0]) and "nofround" not in knobs:
                dn, w = regname(ops[0])
                rnd_ = {"m": "floor", "p": "ceil", "a": "round"}[m[4]]
                regs[dn] = ("f2i", m.endswith("u"), ("funary", rnd_, fuse(regs["f"], ops[1])), w)
                if dn < 8: written.add(dn)
                k += 1; continue
            if fdst and m in ("frintm", "frintp", "frinta", "frintz") and len(ops) == 2 and "nofround" not in knobs:
                fd = fregname(fdst)
                regs["f"][fd] = ("funary", {"m": "floor", "p": "ceil", "a": "round", "z": "trunc"}[m[5]], fuse(regs["f"], ops[1]))
                if fd < 8: regs.setdefault("fw", set()).add(fd)
                k += 1; continue
            if fdst and m == "fnmul" and len(ops) == 3 and "nofround" not in knobs:
                fd = fregname(fdst)
                regs["f"][fd] = ("funary", "fneg", ("fbin", "*", fuse(regs["f"], ops[1]), fuse(regs["f"], ops[2])))
                if fd < 8: regs.setdefault("fw", set()).add(fd)
                k += 1; continue
            if m in ("fcvtzs", "fcvtzu") and len(ops) == 2 and re.fullmatch(r"s\d+", ops[1]):
                dn, w = regname(ops[0])
                regs[dn] = ("f2i", m == "fcvtzu", fuse(regs["f"], ops[1]), w)
                if dn < 8: written.add(dn)
                k += 1; continue
            if m == "fcmp" and len(ops) == 2 and ops[0] == ops[1] and re.fullmatch(r"s\d+", ops[0]) \
                    and (regs["f"].get(fregname(ops[0])) or ("",))[0] == "fsqrtp":
                # sqrtf(x) with errno: the inline square root, and the library call when it gives NaN
                fd = fregname(ops[0])
                x_ = regs["f"][fd][1]
                br_ = ins[k + 1] if k + 1 < len(ins) else None
                if br_ is None or br_.mnemonic not in ("b.vc", "b.vs") or imm(br_.op_str) not in addr_index:
                    raise Fail("fsqrt")
                tgt_ = imm(br_.op_str)
                def skip_moves_(jj_, end_=None):
                    while jj_ < len(ins) and (end_ is None or ins[jj_].address < end_) and (ins[jj_].mnemonic in ("mov", "fmov") or (
                            ins[jj_].mnemonic in ("str", "ldr", "stur", "ldur") and "nosqrtspill" not in knobs and re.fullmatch(r"[qds]\d+, \[(sp|x29)(, #-?(0x[0-9a-f]+|\d+))?\]", ins[jj_].op_str)) or (
                            ins[jj_].mnemonic in ("stp", "ldp") and "nosqrtpair" not in knobs and re.fullmatch(r"([qds])\d+, \1\d+, \[(sp|x29)(, #-?(0x[0-9a-f]+|\d+))?\]", ins[jj_].op_str))):
                        jj_ += 1
                    return jj_
                def is_sqrtf_(i_, mn_):
                    if i_.mnemonic != mn_ or not i_.op_str.startswith("#"):
                        return None
                    t_ = imm(i_.op_str)
                    imp_ = import_of(t_)
                    return t_ if imp_ and imp_[1] == "sqrtf" else None
                if br_.mnemonic == "b.vc":
                    jj_ = skip_moves_(k + 2, tgt_)
                    sq_ = is_sqrtf_(ins[jj_], "bl") if jj_ < len(ins) else None
                    jj_ = skip_moves_(jj_ + 1, tgt_)
                    if sq_ is None or jj_ >= len(ins) or ins[jj_].address != tgt_:
                        raise Fail("fsqrt")
                    r_ = call({"f": {0: x_}, "fw": {0}}, set(), sq_, items, False)
                    for n2 in list(regs):
                        if isinstance(n2, int) and n2 < 19:
                            regs[n2] = None
                    kept_ = set()
                    if "nosqrtpair" not in knobs:
                        for i_ in ins[k + 2:addr_index[tgt_]]:
                            if i_.mnemonic in ("ldr", "ldp", "ldur") and re.search(r"\[(sp|x29)\b", i_.op_str):
                                kept_ |= {int(r2_[1:]) for r2_ in re.findall(r"\b[qds]\d+\b", i_.op_str.split("[")[0])}
                    regs["f"] = {n3: v3 for n3, v3 in regs["f"].items() if 8 <= n3 <= 15 or n3 in kept_}
                    regs["f"][fd] = r_
                    regs["fw"] = {fd} if fd < 8 else set()
                    written = set()
                    flags = None
                    k = addr_index[tgt_]; continue
                jj_ = skip_moves_(k + 2)
                ss_ = skip_moves_(addr_index[tgt_])
                sq_ = is_sqrtf_(ins[ss_], "b") if ss_ < len(ins) else None
                if sq_ is None or jj_ >= len(ins) or ins[jj_].mnemonic != "ret":
                    raise Fail("fsqrt")
                r_ = call({"f": {0: x_}, "fw": {0}}, set(), sq_, items, True)
                items.append(("return", r_))
                returns.append(r_)
                return items
            if m in ("fccmp", "fccmpe") and len(ops) == 4 and "nofccmp" not in knobs:
                if flags is None:
                    raise Fail("fccmp without flags")
                x = fuse(regs["f"], ops[0])
                y = fuse(regs["f"], ops[1])
                flags = ("ccmp", flags, ops[3], ("fcmp", x, y, "s"), imm(ops[2]))
                k += 1; continue
            if m == "fcmp" and len(ops) == 2:
                x = fuse(regs["f"], ops[0])
                y = ("fconst", 0.0) if ops[1].startswith("#") else fuse(regs["f"], ops[1])
                flags = ("fcmp", x, y, "s")
                k += 1; continue
            if fdst and m == "fcsel" and len(ops) == 4:
                fd = fregname(fdst)
                regs["f"][fd] = ("fselect", (flags, ops[3]), fuse(regs["f"], ops[1]), fuse(regs["f"], ops[2]))
                if fd < 8: regs.setdefault("fw", set()).add(fd)
                k += 1; continue
            if fdst and m in ("ldr", "ldur") and len(ops) == 2 and page_base(regs, ops[1]):
                fd = fregname(fdst)
                b, off, idx, sh, ext, pre, post = memop2(ops[1], None)
                addr_ = regs[regname(b)[0]][1] + off
                if not (POOL4[0] <= addr_ < POOL4[1]):
                    raise Fail("constant outside pool")
                import struct as _st
                regs["f"][fd] = ("fconst", _st.unpack("<f", d[addr_:addr_ + 4])[0])
                if fd < 8: regs.setdefault("fw", set()).add(fd)
                k += 1; continue
            if fdst and m in ("ldr", "ldur") and (len(ops) == 2 or (len(ops) == 3 and ops[2].startswith("#") and ops[1].endswith("]")
                                                                     and "nofpost" not in knobs)) \
                    and not (ops[1].startswith("[sp") or ops[1].startswith("[x29")):
                fd = fregname(fdst)
                b, off, idx, sh, ext, pre, post = memop2(ops[1], ops[2] if len(ops) == 3 else None)
                if post is not None:
                    # the load at the base, then the base advanced
                    bnp_ = regname(b)[0]
                    sn, base, off2 = field(regs, b, off, "float")
                    name = f"v{counter[0]}"; counter[0] += 1
                    vars_[name] = ("load", sn, off2, "float")
                    items.append(("let", name, sn, off2, base))
                    letbase[name] = base
                    regs["f"][fd] = ("var", name)
                    if fd < 8: regs.setdefault("fw", set()).add(fd)
                    regs[bnp_] = ("bin", "+", regs.get(bnp_), ("const", post, "x"), "x", "add")
                    k += 1; continue
                if idx is not None:
                    # a float read through a byte offset, or a float array element
                    if sh not in (0, 2):
                        raise Fail("float addressing")
                    basev_ = regs.get(regname(b)[0])
                    sn, base, off2 = field(regs, None, off, "ARRAY:unsigned char" if sh == 0 else "ARRAY:float", base=basev_, bytecast=sh == 0)
                    iv = index_value(regs, idx, ext)
                    name = f"v{counter[0]}"; counter[0] += 1
                    vars_[name] = ("load", sn, off2, "float")
                    items.append(("leti", name, sn, off2, base, iv, "float") if sh == 0 else ("leti", name, sn, off2, base, iv))
                    regs["f"][fd] = ("var", name)
                    if fd < 8: regs.setdefault("fw", set()).add(fd)
                    k += 1; continue
                if pre:
                    bn_ = regname(b)[0]
                    regs[bn_] = ("bin", "+", regs.get(bn_), ("const", off, "x"), "x", "add")
                    off = 0
                sn, base, off2 = field(regs, b, off, "float")
                name = f"v{counter[0]}"; counter[0] += 1
                vars_[name] = ("load", sn, off2, "float")
                items.append(("let", name, sn, off2, base))
                letbase[name] = base
                regs["f"][fd] = ("var", name)
                if fd < 8: regs.setdefault("fw", set()).add(fd)
                k += 1; continue
            qregs_ = [o_ for o_ in ops if re.fullmatch(r"q\d+", o_)]
            qpost_ = None
            if qregs_ and m in ("ldr", "str") and len(ops) == 3 and ops[2].startswith("#") and ops[1].startswith("[") \
                    and "novecaddr" not in knobs:
                qpost_ = imm(ops[2]); ops = ops[:2]
            if qregs_ and m in ("ldr", "str", "ldp", "stp") and len(ops) == len(qregs_) + 1 and not (ops[-1].startswith("[sp") or ops[-1].startswith("[x29")):
                b, off, idx, sh, ext, pre, post = memop2(ops[-1], None)
                if "novecaddr" not in knobs and len(qregs_) == 1 and idx is not None and sh in (0, 4) and not pre:
                    # a Vec4f array element, or a Vec4f through a byte offset
                    qn_ = int(qregs_[0][1:])
                    basev_ = regs.get(regname(b)[0])
                    sn, base, off2 = field(regs, None, off, "ARRAY:unsigned char" if sh == 0 else "ARRAY:Vec4f", base=basev_, bytecast=sh == 0)
                    iv = index_value(regs, idx, ext)
                    if m == "ldr":
                        name = f"v{counter[0]}"; counter[0] += 1
                        vars_[name] = ("load", sn, off2, "Vec4f")
                        items.append(("leti", name, sn, off2, base, iv, "Vec4f") if sh == 0 else ("leti", name, sn, off2, base, iv))
                        regs["f"][qn_] = ("var", name)
                    else:
                        val_ = regs["f"].get(qn_)
                        if not is_vecval_(val_):
                            raise Fail("vector store source")
                        items.append(("storei", sn, off2, base, iv, val_, "Vec4f") if sh == 0 else ("storei", sn, off2, base, iv, val_))
                    k += 1; continue
                if "novecaddr" not in knobs and pre and idx is None:
                    bn_ = regname(b)[0]
                    regs[bn_] = ("bin", "+", regs.get(bn_), ("const", off, "x"), "x", "add")
                    off = 0; pre = False
                if m == "ldr" and len(qregs_) == 1 and idx is None and not pre and page_base(regs, ops[-1]):
                    # a 16-byte constant from the literal pool
                    addr_ = regs[regname(b)[0]][1] + off
                    if not (POOL16[0] <= addr_ < POOL16[1]) or addr_ % 16:
                        raise Fail("vector constant outside pool")
                    import struct as _st
                    regs["f"][int(qregs_[0][1:])] = ("vconst", _st.unpack("<4f", d[addr_:addr_ + 16]))
                    k += 1; continue
                if idx is not None or pre or page_base(regs, ops[-1]):
                    raise Fail("vector addressing")
                for j_, qr_ in enumerate(qregs_):
                    if (off + 16 * j_) % 16:
                        raise Fail("unaligned vector field")
                    sn, base, off2 = field(regs, b, off + 16 * j_, "Vec4f")
                    qn_ = int(qr_[1:])
                    if m in ("ldr", "ldp"):
                        name = f"v{counter[0]}"; counter[0] += 1
                        vars_[name] = ("load", sn, off2)
                        items.append(("let", name, sn, off2, base))
                        letbase[name] = base
                        regs["f"][qn_] = ("var", name)
                    else:
                        val_ = regs["f"].get(qn_)
                        if val_ is not None and (val_[0] == "vconst" or (is_vecval_(val_) and val_[0] != "var" and "novec" not in knobs)):
                            items.append(("store", sn, off2, base, val_))
                            continue
                        if val_ is None or val_[0] != "var" or not (isinstance(vars_.get(val_[1]), tuple) and vars_[val_[1]][0] == "load" and structs[vars_[val_[1]][1]][vars_[val_[1]][2]][0] == "Vec4f"):
                            raise Fail("vector store source")
                        items.append(("store", sn, off2, base, val_))
                if qpost_ is not None:
                    bn_ = regname(b)[0]
                    regs[bn_] = ("bin", "+", regs.get(bn_), ("const", qpost_, "x"), "x", "add")
                k += 1; continue
            if m in ("ldp", "stp") and len(ops) == 3 and re.fullmatch(r"s\d+", ops[0]) and re.fullmatch(r"s\d+", ops[1]) and not (ops[2].startswith("[sp") or ops[2].startswith("[x29")):
                # float pairs are two neighbouring float fields
                b, off, idx, sh, ext, pre, post = memop2(ops[2], None)
                if idx is not None or pre:
                    raise Fail("float addressing")
                for j_, fr_ in enumerate(ops[:2]):
                    sn, base, off2 = field(regs, b, off + 4 * j_, "float")
                    if m == "ldp":
                        fd = fregname(fr_)
                        name = f"v{counter[0]}"; counter[0] += 1
                        vars_[name] = ("load", sn, off2)
                        items.append(("let", name, sn, off2, base))
                        letbase[name] = base
                        regs["f"][fd] = ("var", name)
                        if fd < 8: regs.setdefault("fw", set()).add(fd)
                    else:
                        items.append(("store", sn, off2, base, fuse(regs["f"], fr_)))
                k += 1; continue
            if ops and re.fullmatch(r"s\d+", ops[0]) and m in ("str", "stur") and (len(ops) == 2 or (len(ops) == 3 and ops[2].startswith("#")
                                                                                      and ops[1].endswith("]") and "nofpost" not in knobs)) \
                    and not (ops[1].startswith("[sp") or ops[1].startswith("[x29")):
                val = fuse(regs["f"], ops[0])
                b, off, idx, sh, ext, pre, post = memop2(ops[1], ops[2] if len(ops) == 3 else None)
                if post is not None:
                    bnp_ = regname(b)[0]
                    sn, base, off2 = field(regs, b, off, "float")
                    items.append(("store", sn, off2, base, val))
                    regs[bnp_] = ("bin", "+", regs.get(bnp_), ("const", post, "x"), "x", "add")
                    k += 1; continue
                if idx is not None:
                    if sh not in (0, 2):
                        raise Fail("float addressing")
                    basev_ = regs.get(regname(b)[0])
                    sn, base, off2 = field(regs, None, off, "ARRAY:unsigned char" if sh == 0 else "ARRAY:float", base=basev_, bytecast=sh == 0)
                    iv = index_value(regs, idx, ext)
                    items.append(("storei", sn, off2, base, iv, val, "float") if sh == 0 else ("storei", sn, off2, base, iv, val))
                    k += 1; continue
                if pre:
                    bn_ = regname(b)[0]
                    regs[bn_] = ("bin", "+", regs.get(bn_), ("const", off, "x"), "x", "add")
                    off = 0
                sn, base, off2 = field(regs, b, off, "float")
                items.append(("store", sn, off2, base, val))
                k += 1; continue
            fregs_ = [o_ for o_ in ops[:-1] if re.fullmatch(r"[sq]\d+", o_)] if sbase is not None else []
            if fregs_ and len(fregs_) == len(ops) - 1 and m in ("ldr", "str", "ldur", "stur", "ldp", "stp"):
                # float and vector stack slots: fields of an address-taken stack object, or spill slots
                if any(r_[0] != fregs_[0][0] for r_ in fregs_):
                    raise Fail("mixed float pair")
                vec_ = fregs_[0][0] == "q"
                width_ = 16 if vec_ else 4
                ct_ = "Vec4f" if vec_ else "float"
                load_ = m in ("ldr", "ldur", "ldp")
                for j_, r_ in enumerate(fregs_):
                    off_ = sbase + width_ * j_
                    rn_ = int(r_[1:])
                    if not any(s0 <= off_ for s0 in starts):
                        if load_:
                            if ("fspill", off_) not in regs:
                                raise Fail("float reload")
                            regs["f"][rn_] = regs[("fspill", off_)]
                            if rn_ < 8: regs.setdefault("fw", set()).add(rn_)
                        else:
                            v_ = regs["f"].get(rn_)
                            if v_ is None:
                                raise Fail("undefined float spill")
                            regs[("fspill", off_)] = v_
                        continue
                    st = stack_obj(off_)
                    sv = ("stackobj", st)
                    sn = struct_for(sv)
                    prev = structs[sn].get(off_ - st)
                    if prev and prev[0] != ct_ and retype_ok_(sn, off_ - st, prev[0], ct_):
                        structs[sn][off_ - st] = (ct_, None)
                        prev = structs[sn][off_ - st]
                    if prev and prev[0] != ct_ and not spun_(prev[0], ct_) and not vu_check_(sn, off_ - st, ct_):
                        raise Fail("stack field clash")
                    vu_check_(sn, off_ - st, ct_)
                    note_access_(sn, off_ - st, False)
                    structs[sn].setdefault(off_ - st, (ct_, None))
                    if load_:
                        name = f"v{counter[0]}"; counter[0] += 1
                        vars_[name] = ("load", sn, off_ - st) if vec_ else ("load", sn, off_ - st, "float")
                        items.append(("let", name, sn, off_ - st, sv))
                        letbase[name] = sv
                        regs["f"][rn_] = ("var", name)
                        if rn_ < 8: regs.setdefault("fw", set()).add(rn_)
                    else:
                        if vec_:
                            v_ = regs["f"].get(rn_)
                            if v_ is None or not (v_[0] == "vconst" or (is_vecval_(v_) and v_[0] != "var" and "novec" not in knobs) or (v_[0] == "var" and isinstance(vars_.get(v_[1]), tuple)
                                                                         and vars_[v_[1]][0] == "load" and structs[vars_[v_[1]][1]][vars_[v_[1]][2]][0] == "Vec4f")):
                                raise Fail("vector store source")
                        else:
                            v_ = fuse(regs["f"], "s%d" % rn_)
                        items.append(("store", sn, off_ - st, sv, v_))
                k += 1; continue
            if "copy64" in knobs and k in copy_loads_:
                b_, off_ = ops[1].strip("[]").split(", #") if ", #" in ops[1] else (ops[1].strip("[]"), "0")
                off_ = imm("#" + off_) if not off_.startswith("#") else imm(off_)
                if b_ == "sp":
                    if not any(s0 <= off_ for s0 in starts):
                        raise Fail("copy from spill")
                    st_ = stack_obj(off_)
                    struct_for(("stackobj", st_))
                    src_ = (("stackobj", st_), off_ - st_)
                else:
                    src_ = (regs.get(regname(b_)[0]), off_)
                    if src_[0] is None:
                        raise Fail("undefined base")
                regs[int(ops[0][1:])] = ("copy", src_[0], src_[1])
                k += 1; continue
            if m in ("str", "stur") and len(ops) == 2 and re.fullmatch(r"x\d+", ops[0]) and (regs.get(int(ops[0][1:])) or ("",))[0] == "copy":
                cv_ = regs[int(ops[0][1:])]
                b_, off_ = ops[1].strip("[]").split(", #") if ", #" in ops[1] else (ops[1].strip("[]"), "0")
                off_ = imm("#" + off_) if not off_.startswith("#") else imm(off_)
                if b_ in ("sp", "x29"):
                    if b_ == "x29":
                        off_ += fp_off
                    if not any(s0 <= off_ for s0 in starts):
                        raise Fail("copy to spill")
                    st_ = stack_obj(off_)
                    struct_for(("stackobj", st_))
                    dst_ = (("stackobj", st_), off_ - st_)
                else:
                    dst_ = (regs.get(regname(b_)[0]), off_)
                    if dst_[0] is None:
                        raise Fail("undefined base")
                items.append(("copy8", dst_[0], dst_[1], cv_[1], cv_[2]))
                k += 1; continue
            if m == "mov" and len(ops) == 2 and ops[1] == "sp":
                dn, _ = regname(ops[0]); regs[dn] = ("stackaddr", 0)
                if dn < 8: written.add(dn)
            elif m == "add" and len(ops) == 3 and ops[1] == "sp":
                dn, _ = regname(ops[0]); regs[dn] = ("stackaddr", imm(ops[2]))
                if dn < 8: written.add(dn)
            elif m == "sub" and len(ops) == 3 and ops[1] == "x29":
                dn, _ = regname(ops[0]); regs[dn] = ("stackaddr", fp_off - imm(ops[2]))
                if dn < 8: written.add(dn)
            elif sbase is not None and (m in LOAD or m == "ldur") and sbase >= frame_total_ and (sbase - frame_total_) % 8 == 0 \
                    and (frameless_ or frame_total_ > 0):
                dn, w = regname(ops[0])
                mm2 = "ldr" if m == "ldur" else m
                ct = LOAD[mm2] or ("x" if w == "x" else "w")
                pn_ = 8 + (sbase - frame_total_) // 8
                want_ = {"int": "w"}.get(ct, ct)
                if want_ == "void*":
                    want_ = "x"
                if pwidth.get(pn_) not in (None, want_):
                    raise Fail("stack argument width")
                pwidth[pn_] = want_
                regs[dn] = ("param", pn_)
                if dn < 8: written.add(dn)
            elif ("nospillpair" not in knobs and sbase is not None and (m in LOAD or m == "ldur")
                    and not any(s0 <= sbase for s0 in starts) and ("spill", sbase) in regs):
                dn, w = regname(ops[0])
                regs[dn] = regs[("spill", sbase)]
                if dn < 8: written.add(dn)
            elif ("nostackldp" not in knobs and sbase is not None and m == "ldp" and len(ops) == 3
                    and all(re.fullmatch(r"[wx]\d+", o_) for o_ in ops[:2]) and ops[0][0] == ops[1][0]):
                step_ = 8 if ops[0][0] == "x" else 4
                for j_, rr_ in enumerate(ops[:2]):
                    dn, w = regname(rr_)
                    off_ = sbase + j_ * step_
                    if not any(s0 <= off_ for s0 in starts) and ("spill", off_) in regs:
                        regs[dn] = regs[("spill", off_)]
                        if dn < 8: written.add(dn)
                        continue
                    ct = "void*" if w == "x" else "int"
                    st = stack_obj(off_)
                    sv = ("stackobj", st)
                    sn = struct_for(sv)
                    prev = structs[sn].get(off_ - st)
                    if prev and prev[0] != ct and retype_ok_(sn, off_ - st, prev[0], ct):
                        structs[sn][off_ - st] = (ct, None)
                        prev = structs[sn][off_ - st]
                    if prev and prev[0] != ct and not ({prev[0], ct} <= {"long", "void*"}) and not spun_(prev[0], ct) \
                            and not vu_check_(sn, off_ - st, ct) and not widen_field_(sn, off_ - st, prev, ct):
                        raise Fail("stack field clash")
                    vu_check_(sn, off_ - st, ct)
                    note_access_(sn, off_ - st, False)
                    structs[sn].setdefault(off_ - st, (ct, None))
                    name = f"v{counter[0]}"; counter[0] += 1
                    vars_[name] = ("load", sn, off_ - st) if structs[sn][off_ - st][0] == ct else ("load", sn, off_ - st, ct)
                    items.append(("let", name, sn, off_ - st, sv))
                    letbase[name] = sv
                    regs[dn] = ("var", name)
                    if dn < 8: written.add(dn)
            elif sbase is not None and (m in LOAD or m == "ldur"):
                dn, w = regname(ops[0])
                mm2 = "ldr" if m == "ldur" else m
                ct = LOAD[mm2] or ("void*" if w == "x" else "int")
                st = stack_obj(sbase)
                sv = ("stackobj", st)
                sn = struct_for(sv)
                prev = structs[sn].get(sbase - st)
                if prev and prev[0] != ct and retype_ok_(sn, sbase - st, prev[0], ct):
                    structs[sn][sbase - st] = (ct, None)
                    prev = structs[sn][sbase - st]
                if prev and prev[0] != ct and not ({prev[0], ct} <= {"long", "void*"}) and not spun_(prev[0], ct) \
                        and not vu_check_(sn, sbase - st, ct) and not widen_field_(sn, sbase - st, prev, ct):
                    raise Fail("stack field clash")
                vu_check_(sn, sbase - st, ct)
                note_access_(sn, sbase - st, False)
                structs[sn].setdefault(sbase - st, (ct, None))
                name = f"v{counter[0]}"; counter[0] += 1
                vars_[name] = ("load", sn, sbase - st) if structs[sn][sbase - st][0] == ct else ("load", sn, sbase - st, ct)
                items.append(("let", name, sn, sbase - st, sv))
                letbase[name] = sv
                regs[dn] = ("var", name)
                if dn < 8: written.add(dn)
            elif ("nospillpair" not in knobs and sbase is not None and m in ("stp", "str", "stur")
                    and all(re.fullmatch(r"[wx](\d+|zr)", o_) for o_ in ops[:2 if m == "stp" else 1])
                    and (m == "stp" or ops[0][1:] == "zr")
                    and not any(s0 <= sbase + (8 if ops[0][0] == "x" else 4) * (m == "stp") for s0 in starts)):
                step_ = 8 if ops[0][0] == "x" else 4
                for j_, rr_ in enumerate(ops[:2] if m == "stp" else ops[:1]):
                    n_, w_ = regname(rr_)
                    regs[("spill", sbase + j_ * step_)] = use(regs, rr_) if n_ is not None else ("const", 0, w_)
            elif ("nospillpair" not in knobs and sbase is not None and m == "ldp" and len(ops) == 3
                    and all(re.fullmatch(r"[wx]\d+", o_) for o_ in ops[:2])
                    and ("spill", sbase) in regs and ("spill", sbase + (8 if ops[0][0] == "x" else 4)) in regs):
                step_ = 8 if ops[0][0] == "x" else 4
                for j_, rr_ in enumerate(ops[:2]):
                    dn, w = regname(rr_)
                    regs[dn] = regs[("spill", sbase + j_ * step_)]
                    if dn < 8: written.add(dn)
            elif sbase is not None and (m in STORE or m == "stur") and m != "stp" and not any(s0 <= sbase for s0 in starts) \
                    and regname(ops[0])[0] is not None:
                regs[("spill", sbase)] = use(regs, ops[0])
            elif sbase is not None and (m in LOAD or m == "ldur") and not any(s0 <= sbase for s0 in starts) and ("spill", sbase) in regs:
                dn, w = regname(ops[0])
                regs[dn] = regs[("spill", sbase)]
                if dn < 8: written.add(dn)
            elif sbase is not None and (m in STORE or m == "stur" or m == "stp"):
                pairs = [(ops[0], 0)]
                if m == "stp":
                    w0 = regname(ops[0])[1]
                    pairs = [(ops[0], 0), (ops[1], 8 if w0 == "x" else 4)]
                for rr, add_ in pairs:
                    n_, w = regname(rr)
                    val = use(regs, rr) if n_ is not None else ("const", 0, w)
                    mm2 = "str" if m in ("stur", "stp") else m
                    ct = STORE[mm2] or ("long" if w == "x" else "int")
                    if mm2 == "str" and w == "x" and (val[0] in ("param", "var", "stackaddr", "gotaddr", "local") or (val[0] == "const" and val[1] == 0)):
                        ct = "void*"
                    off_ = sbase + add_
                    st = stack_obj(off_)
                    sv = ("stackobj", st)
                    sn = struct_for(sv)
                    prev = structs[sn].get(off_ - st)
                    if prev and prev[0] != ct and val[0] == "const" and w == "x" and SIZE.get(prev[0], 8) < 8 \
                            and vu_of_(sn, off_ - st) is None:
                        items.extend(const_pieces_(sn, off_ - st, 8, val[1], sv))
                        continue
                    if prev and prev[0] != ct and val[0] != "const" and retype_ok_(sn, off_ - st, prev[0], ct):
                        structs[sn][off_ - st] = (ct, None)
                        prev = structs[sn][off_ - st]
                    if prev and prev[0] != ct and not ({prev[0], ct} <= {"long", "void*"}) and not spun_(prev[0], ct) \
                            and not vu_check_(sn, off_ - st, ct):
                        raise Fail("stack field clash")
                    vu_check_(sn, off_ - st, ct)
                    structs[sn].setdefault(off_ - st, (ct, None))
                    note_access_(sn, off_ - st, val[0] == "const")
                    items.append(("store", sn, off_ - st, sv, val))
            elif m == "mov":
                dn, w = regname(ops[0])
                regs[dn] = ("const", imm(ops[1]), w) if ops[1].startswith("#") else use(regs, ops[1])
                if dn < 8: written.add(dn)
            elif m in ("sxtw", "sxth", "sxtb", "uxtb", "uxth") and len(ops) == 2:
                dn, w = regname(ops[0])
                src_ = use(regs, ops[1])
                ty_ = {"sxtw": "int", "sxth": "short", "sxtb": "signed char", "uxtb": "unsigned char", "uxth": "unsigned short"}[m]
                if w == "x":
                    regs[dn] = ("ext", ty_, src_)
                elif m in ("uxtb", "uxth"):
                    regs[dn] = ("bin", "&", src_, ("const", 0xff if m == "uxtb" else 0xffff, "w"), "w", "and")
                elif "nonarrowsext" not in knobs:
                    # a 32-bit sign extension of a byte or halfword: the value through the narrow signed type
                    regs[dn] = ("ext", ty_, src_)
                else:
                    raise Fail("narrow sign extend")
                if dn < 8: written.add(dn)
            elif m in ("umaddl", "smaddl", "madd") and len(ops) == 4:
                dn, w = regname(ops[0])
                xi = use(regs, ops[1]); y_ = use(regs, ops[2]); z_ = use(regs, ops[3])
                if m == "umaddl":
                    xi = ("ext", "unsigned int", xi)
                elif m == "smaddl":
                    xi = ("ext", "int", xi)
                regs[dn] = ("bin", "+", z_, ("bin", "*", xi, y_, w, "mul"), w, "add")
                if dn < 8: written.add(dn)
            elif m == "adrp":
                dn, _ = regname(ops[0]); regs[dn] = ("page", imm(ops[1]))
            elif m == "movk":
                dn, w = regname(ops[0]); v0 = regs.get(dn)
                if not v0 or v0[0] != "const":
                    raise Fail("movk")
                sh = int(ops[2].split("#")[1]) if len(ops) > 2 else 0
                regs[dn] = ("const", (v0[1] & ~(0xffff << sh)) | (imm(ops[1]) << sh), w)
            elif m == "ubfx" and len(ops) == 4:
                dn, w = regname(ops[0])
                x = use(regs, ops[1]); lsb, width = imm(ops[2]), imm(ops[3])
                shifted = ("bin", ">>", x, ("const", lsb, w), w, "lsr") if lsb else x
                regs[dn] = ("bin", "&", shifted, ("const", (1 << width) - 1, w), w, "and")
                if dn < 8: written.add(dn)
            elif m == "add" and len(ops) == 3 and ops[2].startswith("#") and regs.get(regname(ops[1])[0]) is not None and regs[regname(ops[1])[0]][0] == "page":
                dn, _ = regname(ops[0]); regs[dn] = ("local", regs[regname(ops[1])[0]][1] + imm(ops[2]))
                if dn < 8: written.add(dn)
            elif m == "ldr" and len(ops) == 2 and page_base(regs, ops[1]):
                dn, w = regname(ops[0])
                b, off = memop(ops[1])
                addr = regs[regname(b)[0]][1] + off
                if w == "x" and addr < 0xc2f000:
                    regs[dn] = ("gotaddr", addr)
                else:
                    tmp = ("local", addr)
                    ct = "void*" if w == "x" else "int"
                    sn = struct_for(tmp)
                    prev = structs[sn].get(0)
                    if prev and prev[0] != ct:
                        raise Fail("field clash")
                    structs[sn].setdefault(0, (ct, None))
                    name = f"v{counter[0]}"; counter[0] += 1
                    vars_[name] = ("load", sn, 0)
                    items.append(("let", name, sn, 0, tmp))
                    regs[dn] = ("var", name)
                if dn < 8: written.add(dn)
            elif "nopair32" not in knobs and k in pair_loads_:
                # two neighbouring int fields read by one 64-bit load
                mm_ = re.fullmatch(r"x(\d+), \[(x\d+)(?:, #(0x[0-9a-f]+|\d+))?\]", i.op_str)
                dn = int(mm_.group(1))
                off_ = int(mm_.group(3), 0) if mm_.group(3) else 0
                basev_ = regs.get(regname(mm_.group(2))[0])
                halves_ = []
                for o_ in (off_, off_ + 4):
                    sn, base, off2 = field(regs, None, o_, "int", base=basev_)
                    name = f"v{counter[0]}"; counter[0] += 1
                    vars_[name] = ("load", sn, off2, "int")
                    items.append(("let", name, sn, off2, base))
                    letbase[name] = base
                    halves_.append(("var", name))
                regs[dn] = ("pair32", halves_[0], halves_[1])
                PAIR_USED[0] = True
                if dn < 8: written.add(dn)
            elif "nopair32" not in knobs and m in ("lsr", "asr", "ubfx") and len(ops) >= 3 and re.fullmatch(r"x\d+", ops[1]) \
                    and (regs.get(int(ops[1][1:])) or ("",))[0] == "pair32" and ops[2] in ("#0x20", "#32"):
                dn, w = regname(ops[0])
                regs[dn] = regs[int(ops[1][1:])][2]
                if dn < 8: written.add(dn)
            elif m in LOAD or m == "ldp":
                pair = m == "ldp"
                dests = [ops[0], ops[1]] if pair else [ops[0]]
                memo = ops[2] if pair else ops[1]
                extra = (ops[3] if len(ops) > 3 else None) if pair else (ops[2] if len(ops) > 2 else None)
                b, off, idx, sh, ext, pre, post = memop2(memo, extra)
                if idx is not None and ext in ("x", "lsl") and regs.get(regname(idx)[0]) is not None and regs[regname(idx)[0]][0] == "const":
                    # a constant in the index register is a field offset too large for the immediate form
                    off += regs[regname(idx)[0]][1] << (sh or 0); idx = None
                bn_, _ = regname(b)
                basev = regs.get(bn_)
                if pre:
                    basev = ("bin", "+", basev, ("const", off, "x"), "x", "add"); off = 0
                w0 = regname(dests[0])[1]
                for j, dreg in enumerate(dests):
                    dn, w = regname(dreg)
                    mm = "ldr" if pair else m
                    ct = LOAD[mm] or ("void*" if w == "x" else "int")
                    step = (8 if w == "x" else 4) * j
                    if idx is not None:
                        if pair:
                            raise Fail("indexed pair")
                        esz = SIZE[ct]
                        if sh == 0 and esz > 1:
                            sn, base, off2 = field(regs, None, off, "ARRAY:unsigned char", base=basev, bytecast=True)
                            iv = index_value(regs, idx, ext)
                            name = f"v{counter[0]}"; counter[0] += 1
                            vars_[name] = ("load", sn, off2, ct)
                            items.append(("leti", name, sn, off2, base, iv, ct))
                            regs[dn] = ("var", name)
                            if dn < 8: written.add(dn)
                            continue
                        if (1 << sh) != esz and not (sh == 0 and esz == 1):
                            raise Fail("index scale")
                        sn, base, off2 = field(regs, None, off, "ARRAY:" + ct, base=basev)
                        iv = index_value(regs, idx, ext)
                        name = f"v{counter[0]}"; counter[0] += 1
                        vars_[name] = ("load", sn, off2)
                        items.append(("leti", name, sn, off2, base, iv))
                    else:
                        sn, base, off2 = field(regs, None, off + step, ct, base=basev)
                        name = f"v{counter[0]}"; counter[0] += 1
                        vars_[name] = ("load", sn, off2, ct)
                        items.append(("let", name, sn, off2, base))
                        letbase[name] = base
                    regs[dn] = ("var", name)
                    if w == "x" and mm in ("ldrsw", "ldrsh", "ldrsb"):
                        regs[dn] = ("ext", {"ldrsw": "int", "ldrsh": "short", "ldrsb": "signed char"}[mm], ("var", name))
                    if dn < 8: written.add(dn)
                if pre:
                    regs[bn_] = basev
                if post is not None:
                    regs[bn_] = ("bin", "+", regs.get(bn_), ("const", post, "x"), "x", "add")
            elif m in ("blr", "br"):
                fn = regs.get(regname(ops[0])[0])
                if fn and fn[0] == "param" and "noparamfn" not in knobs:
                    pwidth.setdefault(fn[1], "x")
                    if pwidth[fn[1]] != "x":
                        raise Fail("indirect target")
                    tn_ = regname(ops[0])[0]
                    n = tn_ if tn_ < 8 else (max(written) + 1 if written else 0)
                    args = [regs.get(k2) for k2 in range(n)]
                    if any(x is None for x in args):
                        raise Fail("undefined arg")
                    for x in args:
                        if x[0] == "param" and pwidth.get(x[1]) is None:
                            pwidth[x[1]] = "x"
                    name = f"c{counter[0]}"; counter[0] += 1
                    vars_[name] = "?"
                    items.append(("vcall", name, None, None, fn, args, m == "br"))
                    if m == "br":
                        items.append(("return", ("var", name)))
                        returns.append(("var", name))
                        return items
                    for n2 in list(regs):
                        if isinstance(n2, int) and n2 < 19:
                            regs[n2] = None
                    regs["f"] = {n3: v3 for n3, v3 in regs["f"].items() if 8 <= n3 <= 15}
                    regs["fw"] = set()
                    regs[0] = ("var", name)
                    if "novcallf" not in knobs and s0_read_next_(k):
                        regs["f"][0] = ("var", name)
                    if "nof2call" not in knobs and freg_read_next_(k, 1):
                        regs["f"][0] = ("var", name)
                        regs["f"][1] = ("f2y", ("var", name))
                    written = set()
                    flags = None
                    k += 1; continue
                if not fn or fn[0] != "var" or not isinstance(vars_[fn[1]], tuple):
                    raise Fail("indirect target")
                _, node, off = vars_[fn[1]][:3]
                lb = letbase.get(fn[1])
                vp = lb[1] if lb and lb[0] == "var" else None
                if vp is None or off % 8 or not isinstance(vars_.get(vp), tuple) or vars_[vp][0] != "load" or vars_[vp][2] != 0:
                    # a plain function pointer: the compiler picks the first free register for the target,
                    # so a target in x1-x7 gives the argument count
                    tn_ = regname(ops[0])[0]
                    n = tn_ if tn_ < 8 else (max(written) + 1 if written else 0)
                    args = [regs.get(k2) for k2 in range(n)]
                    if any(x is None for x in args):
                        raise Fail("undefined arg")
                    for x in args:
                        if x[0] == "param" and pwidth.get(x[1]) is None:
                            pwidth[x[1]] = "x"
                    if regs["fw"] if "fw" in regs else False:
                        raise Fail("float fp args")
                    name = f"c{counter[0]}"; counter[0] += 1
                    vars_[name] = "?"
                    items.append(("vcall", name, None, None, fn, args, m == "br"))
                    if m == "br":
                        items.append(("return", ("var", name)))
                        returns.append(("var", name))
                        return items
                    for n2 in list(regs):
                        if isinstance(n2, int) and n2 < 19:
                            regs[n2] = None
                    regs["f"] = {n3: v3 for n3, v3 in regs["f"].items() if 8 <= n3 <= 15}
                    regs["fw"] = set()
                    regs[0] = ("var", name)
                    if "novcallf" not in knobs and s0_read_next_(k):
                        regs["f"][0] = ("var", name)
                    if "nof2call" not in knobs and freg_read_next_(k, 1):
                        regs["f"][0] = ("var", name)
                        regs["f"][1] = ("f2y", ("var", name))
                    written = set()
                    flags = None
                    k += 1; continue
                obj = letbase[vp]
                if regs.get(0) != obj:
                    raise Fail("this differs")
                objsn = vars_[vp][1]
                vtables[objsn] = node
                skip_lets.update((vp, fn[1]))
                real = [k2 for k2 in written if regs.get(k2) not in (("var", vp), ("var", fn[1]))]
                n = max(real) + 1 if real else 1
                args = [regs.get(k) for k in range(1, n)]
                if any(x is None for x in args):
                    raise Fail("undefined arg")
                name = f"c{counter[0]}"; counter[0] += 1
                vars_[name] = "?"
                items.append(("vcall", name, objsn, off // 8, obj, args, m == "br"))
                if m == "br":
                    items.append(("return", ("var", name)))
                    returns.append(("var", name))
                    return items
                for n2 in list(regs):
                    if isinstance(n2, int) and n2 < 19:
                        regs[n2] = None
                regs["f"] = {n3: v3 for n3, v3 in regs["f"].items() if 8 <= n3 <= 15}
                regs["fw"] = set()
                regs[0] = ("var", name)
                if "novcallf" not in knobs and s0_read_next_(k):
                    regs["f"][0] = ("var", name)
                if "nof2call" not in knobs and freg_read_next_(k, 1):
                    regs["f"][0] = ("var", name)
                    regs["f"][1] = ("f2y", ("var", name))
                written = set()
                flags = None
                k += 1; continue
            elif m in STORE or m == "stp":
                pair = m == "stp"
                srcs = [ops[0], ops[1]] if pair else [ops[0]]
                memo = ops[2] if pair else ops[1]
                extra = (ops[3] if len(ops) > 3 else None) if pair else (ops[2] if len(ops) > 2 else None)
                b, off, idx, sh, ext, pre, post = memop2(memo, extra)
                if idx is not None and ext in ("x", "lsl") and regs.get(regname(idx)[0]) is not None and regs[regname(idx)[0]][0] == "const":
                    # a constant in the index register is a field offset too large for the immediate form
                    off += regs[regname(idx)[0]][1] << (sh or 0); idx = None
                bn_, _ = regname(b)
                basev = regs.get(bn_)
                if pre:
                    basev = ("bin", "+", basev, ("const", off, "x"), "x", "add"); off = 0
                zsize = {"xzr": 8, "wzr": 4}.get(srcs[0]) if not pair and m == "str" else ({"wzr": 2}.get(srcs[0]) if not pair and m == "strh" else None)
                if zsize and idx is None and not pre and post is None and off % zsize:
                    # an unaligned zero store is Clang merging narrower zero stores: split it into aligned pieces
                    pieces, pos_ = [], off
                    end_ = off + zsize
                    while pos_ < end_:
                        for wdt in (8, 4, 2, 1):
                            if pos_ % wdt == 0 and pos_ + wdt <= end_:
                                pieces.append((pos_, wdt)); pos_ += wdt; break
                    for pos_, wdt in pieces:
                        ct_ = {8: "long", 4: "int", 2: "unsigned short", 1: "unsigned char"}[wdt]
                        sn, base, off2 = field(regs, None, pos_, ct_, base=basev)
                        items.append(("store", sn, off2, base, ("const", 0, "x" if wdt == 8 else "w")))
                    k += 1
                    continue
                for j, sreg in enumerate(srcs):
                    n_, w = regname(sreg)
                    val = use(regs, sreg) if n_ is not None else ("const", 0, w)
                    mm = "str" if pair else m
                    ct = STORE[mm] or ("long" if w == "x" else "int")
                    if mm == "str" and w == "x" and (val[0] in ("param", "var", "gotaddr", "local", "stackaddr") or (val[0] == "const" and val[1] == 0)):
                        ct = "void*"
                    if val[0] == "fbits" and w == "w" and mm == "str":
                        ct = "float"; val = val[1]
                    step = (8 if w == "x" else 4) * j
                    if idx is not None:
                        if pair:
                            raise Fail("indexed pair")
                        esz = SIZE[ct]
                        if sh == 0 and esz > 1:
                            sn, base, off2 = field(regs, None, off, "ARRAY:unsigned char", base=basev, bytecast=True)
                            items.append(("storei", sn, off2, base, index_value(regs, idx, ext), val, ct))
                            continue
                        if (1 << sh) != esz and not (sh == 0 and esz == 1):
                            raise Fail("index scale")
                        sn, base, off2 = field(regs, None, off, "ARRAY:" + ct, base=basev)
                        items.append(("storei", sn, off2, base, index_value(regs, idx, ext), val))
                    else:
                        existed = None
                        try:
                            sn, base, off2 = field(regs, None, off + step, ct, base=basev, cstore=val[0] == "const")
                        except Fail as e_:
                            if str(e_) != "field clash" or val[0] != "const":
                                raise
                            if "longconst" in knobs and w == "x":
                                fb_, fo_ = fold(basev, off + step)
                                sn_ = struct_for(fb_)
                                have_ = structs[sn_].get(fo_)
                                if have_ and have_[0] in ("int", "unsigned int") and fo_ + 4 not in structs[sn_]:
                                    structs[sn_][fo_] = ("long", None)
                                    for vn_, vt_ in list(vars_.items()):
                                        if isinstance(vt_, tuple) and vt_[0] == "load" and vt_[1] == sn_ and vt_[2] == fo_:
                                            vars_[vn_] = ("load", sn_, fo_, "int")
                                    sn, base, off2 = field(regs, None, off + step, "long", base=basev)
                                    items.append(("store", sn, off2, base, val))
                                    continue
                            pieces_ = [(off + step, val[1] & 0xffffffff), (off + step + 4, (val[1] >> 32) & 0xffffffff)] if w == "x" else [(off + step, val[1] & 0xffffffff)]
                            for po_, pv_ in pieces_:
                                fb_, fo_ = fold(basev, po_)
                                have_ = structs.get(struct_for(fb_), {}).get(fo_)
                                if have_ and have_[0] == "float":
                                    if pv_ != 0:
                                        raise
                                    sn, base, off2 = field(regs, None, po_, "float", base=basev)
                                    items.append(("store", sn, off2, base, ("fconst", 0.0)))
                                else:
                                    sn, base, off2 = field(regs, None, po_, "int", base=basev)
                                    pv_s_ = pv_ - (1 << 32) if pv_ >= 1 << 31 else pv_
                                    items.append(("store", sn, off2, base, ("const", pv_s_, "w")))
                            continue
                        bf_ = bitfield_of_(sn, off2, val) if "nobitfield" not in knobs else None
                        if bf_ is not None:
                            bitfields_.setdefault((sn, off2), set()).add(bf_[:2])
                            items.append(("bfstore", sn, off2, base, bf_[2], bf_[0], bf_[1]))
                            continue
                        if structs[sn][off2][0] == ct and ct in ("unsigned char", "unsigned short") and not any(
                                it_[0] in ("let", "leti") and it_[2] == sn and it_[3] == off2 for it_ in items):
                            store_typed.add((sn, off2))
                        if not pair and val[0] == "const" and SIZE.get(ct, 8) <= 4:
                            cstore1_.add((sn, off2, SIZE[ct]))
                        items.append(("store", sn, off2, base, val))
                if pre:
                    regs[bn_] = basev
                if post is not None:
                    regs[bn_] = ("bin", "+", regs.get(bn_), ("const", post, "x"), "x", "add")
            elif m in ("neg", "mvn") and len(ops) == 2 and not ops[1].startswith("#"):
                dn, w = regname(ops[0])
                x = use(regs, ops[1])
                regs[dn] = ("bin", "-", ("const", 0, w), x, w, "sub") if m == "neg" else ("bin", "^", x, ("const", -1, w), w, "eor")
                if dn < 8: written.add(dn)
            elif m in ("cmp", "cmn") and len(ops) == 3:
                # compares with a shifted immediate or an extended register operand
                x = use(regs, ops[0])
                kind3_ = ops[2].split()
                if ops[1].startswith("#") and kind3_[0] == "lsl":
                    y = ("const", (imm(ops[1]) << imm(kind3_[1])) * (-1 if m == "cmn" else 1), regname(ops[0])[1])
                elif not ops[1].startswith("#") and m == "cmp" and kind3_[0] in ("uxtb", "uxth", "sxtb", "sxth", "uxtw", "sxtw"):
                    y = ("ext", {"uxtb": "unsigned char", "uxth": "unsigned short", "sxtb": "signed char", "sxth": "short",
                                 "uxtw": "unsigned int", "sxtw": "int"}[kind3_[0]], use(regs, ops[1]))
                    if len(kind3_) > 1 and imm(kind3_[1]):
                        raise Fail("cmp form")
                elif not ops[1].startswith("#") and m == "cmp" and kind3_[0] in ("lsl", "lsr", "asr") and len(kind3_) > 1:
                    y = ("bin", "<<" if kind3_[0] == "lsl" else ">>", use(regs, ops[1]), ("const", imm(kind3_[1]), regname(ops[0])[1]),
                         regname(ops[0])[1], kind3_[0])
                else:
                    raise Fail("cmp form")
                flags = ("cmp", x, y, regname(ops[0])[1])
            elif m in ("cmp", "cmn", "tst") and len(ops) == 2:
                x = use(regs, ops[0])
                if ops[1].startswith("#"):
                    y = ("const", imm(ops[1]) * (-1 if m == "cmn" else 1), regname(ops[0])[1])
                elif m == "cmn":
                    raise Fail("cmn reg")
                else:
                    y = use(regs, ops[1])
                flags = ("tst" if m == "tst" else "cmp", x, y, regname(ops[0])[1])
            elif m in ("ccmp", "ccmn") and len(ops) == 4:
                if flags is None:
                    raise Fail("ccmp without flags")
                x = use(regs, ops[0])
                if ops[1].startswith("#"):
                    y = ("const", imm(ops[1]) * (-1 if m == "ccmn" else 1), regname(ops[0])[1])
                elif m == "ccmn":
                    raise Fail("ccmn reg")
                else:
                    y = use(regs, ops[1])
                flags = ("ccmp", flags, ops[3], ("cmp", x, y, regname(ops[0])[1]), imm(ops[2]))
            elif m in ("cset", "csetm") and len(ops) == 2:
                dn, w = regname(ops[0])
                regs[dn] = ("cond", (flags, ops[1]), w, m == "csetm")
                if dn < 8: written.add(dn)
            elif m in ("subs", "adds") and len(ops) == 3:
                # arithmetic that also sets the flags: the flags compare the operands (subs) or the result with zero (adds)
                dn, w = regname(ops[0])
                x = use(regs, ops[1])
                y = ("const", imm(ops[2]), w) if ops[2].startswith("#") else use(regs, ops[2])
                res_ = ("bin", "-" if m == "subs" else "+", x, y, w, "sub" if m == "subs" else "add")
                flags = ("cmp", x, y, w) if m == "subs" else ("cmp", res_, ("const", 0, w), w)
                if dn is not None:
                    regs[dn] = res_
                    if dn < 8: written.add(dn)
            elif m == "cinc" and len(ops) == 3:
                dn, w = regname(ops[0])
                x = use(regs, ops[1])
                regs[dn] = ("select", (flags, ops[2]), ("bin", "+", x, ("const", 1, w), w, "add"), x, w)
                if dn < 8: written.add(dn)
            elif m in ("umull", "smull") and len(ops) == 3:
                dn, w = regname(ops[0])
                x = ("ext", "unsigned int" if m == "umull" else "int", use(regs, ops[1]))
                y = ("ext", "unsigned int" if m == "umull" else "int", use(regs, ops[2]))
                regs[dn] = ("bin", "*", x, y, "x", "mul")
                if dn < 8: written.add(dn)
            elif m == "umulh" and len(ops) == 3 and "noudiv64" not in knobs:
                dn, w = regname(ops[0])
                regs[dn] = ("umulh", use(regs, ops[1]), use(regs, ops[2]))
                if dn < 8: written.add(dn)
            elif m == "msub" and len(ops) == 4 and "nodivmagic" not in knobs:
                dn, w = regname(ops[0])
                x_ = use(regs, ops[1]); y_ = use(regs, ops[2]); z_ = use(regs, ops[3])
                regs[dn] = divmagic_(("bin", "-", z_, ("bin", "*", x_, y_, w, "mul"), w, "sub"))
                if dn < 8: written.add(dn)
            elif m == "bfi" and len(ops) == 4:
                dn, w = regname(ops[0])
                old_ = use(regs, ops[0]); src_ = use(regs, ops[1]); lsb_, wd_ = imm(ops[2]), imm(ops[3])
                mask_ = (1 << wd_) - 1
                kept_ = ("bin", "&", old_, ("const", ~(mask_ << lsb_) & ((1 << (64 if w == "x" else 32)) - 1), w), w, "and")
                ins_ = ("bin", "&", src_, ("const", mask_, w), w, "and")
                if lsb_:
                    ins_ = ("bin", "<<", ins_, ("const", lsb_, w), w, "lsl")
                regs[dn] = ("bin", "|", kept_, ins_, w, "orr")
                if dn < 8: written.add(dn)
            elif m in ("csel", "csinc", "csinv") and len(ops) == 4:
                dn, w = regname(ops[0])
                x = use(regs, ops[1]); y = use(regs, ops[2])
                if m == "csinc":
                    y = ("bin", "+", y, ("const", 1, w), w, "add")
                elif m == "csinv":
                    y = ("bin", "^", y, ("const", -1, w), w, "eor")
                regs[dn] = ("select", (flags, ops[3]), x, y, w)
                if dn < 8: written.add(dn)
            elif m == "fmov" and len(ops) == 2 and re.fullmatch(r"w\d+", ops[0]) and re.fullmatch(r"s\d+", ops[1]) \
                    and "nofbits" not in knobs:
                dn, w = regname(ops[0])
                regs[dn] = ("fbits", fuse(regs["f"], ops[1]))
                if dn < 8: written.add(dn)
            elif m in ("eor", "and") and len(ops) == 3 and ops[2].startswith("#") and re.fullmatch(r"w\d+", ops[0]) \
                    and (regs.get(regname(ops[1])[0]) or ("",))[0] == "fbits" \
                    and (m, imm(ops[2]) & 0xffffffff) in (("eor", 0x80000000), ("and", 0x7fffffff)):
                dn, w = regname(ops[0])
                regs[dn] = ("fbits", ("funary", "fneg" if m == "eor" else "fabs", regs[regname(ops[1])[0]][1]))
                if dn < 8: written.add(dn)
            elif m in BIN and len(ops) in (3, 4):
                dn, w = regname(ops[0])
                x = use(regs, ops[1])
                y = ("const", imm(ops[2]), w) if ops[2].startswith("#") else use(regs, ops[2])
                if len(ops) == 4:
                    kind = ops[3].split()
                    sh = imm(kind[1]) if len(kind) > 1 else 0
                    if kind[0] in ("uxtw", "sxtw"):
                        y = ("ext", "unsigned int" if kind[0] == "uxtw" else "int", y)
                    elif kind[0] in ("uxtb", "uxth", "sxtb", "sxth"):
                        nt_ = {"uxtb": "unsigned char", "uxth": "unsigned short", "sxtb": "signed char", "sxth": "short"}[kind[0]]
                        if y[0] == "param" and regname(ops[2])[0] == y[1] and pwidth.get(y[1]) in (None, "w") and "narrowparam" not in knobs:
                            pwidth[y[1]] = nt_
                        y = ("ext", nt_, y)
                    elif kind[0] in ("lsr", "asr") and sh:
                        y = ("bin", ">>", y, ("const", sh, w), w, kind[0])
                        sh = 0
                    elif kind[0] != "lsl":
                        raise Fail("operand shift")
                    if sh:
                        y = ("bin", "<<", y, ("const", sh, w), w, "lsl")
                regs[dn] = ("bin", BIN[m], x, y, w, m)
                if "nodivmagic" not in knobs:
                    regs[dn] = divmagic_(regs[dn])
                if "nosdivmagic" not in knobs:
                    regs[dn] = sdivmagic_(regs[dn])
                if m == "and" and y[0] == "const" and y[1] in (0xff, 0xffff) and x[0] == "bin" and x[1] in ("-", "+") \
                        and x[2][0] == "param" and x[3][0] == "const" and pwidth.get(x[2][1]) in (None, "w") and "norange" not in knobs:
                    nty_ = "unsigned short" if y[1] == 0xffff else "unsigned char"
                    pwidth[x[2][1]] = nty_
                    lo_ = x[3][1] if x[1] == "-" else -x[3][1]
                    regs[dn] = ("range", x[2], lo_ & y[1], nty_)
                if "nohoistaddr" not in knobs and k in hoist_adds_ and m == "add" and w == "x" and x[0] in ("param", "var") \
                        and (y[0] == "const" or (y[0] == "ext" and y[2][0] == "const")) and regs[dn][0] == "bin":
                    # an address computed early into a callee-saved register: a local declared here
                    name = f"a{counter[0]}"; counter[0] += 1
                    vars_[name] = "long"
                    items.append(("lete", name, regs[dn]))
                    regs[dn] = ("var", name)
                    HOIST_USED[0] = True
                if dn < 8: written.add(dn)
            else:
                raise Fail(m)
            k += 1
    regs0 = {n: ("param", n) for n in range(8)}
    regs0["f"] = {n: ("fparam", n) for n in range(8)}
    if sret_:
        regs0[8] = ("retobj",)
    items = walk(0, regs0, None, set(), 0)
    def arg_first(its):
        out_ = list(its)
        for ci_, it in enumerate(list(out_)):
            if it[0] in ("if", "diamond", "loop"):
                continue
            if it[0] != "call":
                continue
            args_ = list(it[3])
            changed_ = False
            for ai_, x_ in enumerate(args_):
                if not (x_[0] == "bin" and x_[1] == "+" and x_[2][0] == "var" and (x_[3][0] == "const" or (x_[3][0] == "ext" and x_[3][2][0] == "const"))):
                    continue
                pos_ = next((p_ for p_, y_ in enumerate(out_) if y_[0] == "let" and y_[1] == x_[2][1]), None)
                ci2_ = out_.index(it) if it in out_ else None
                if pos_ is None or ci2_ is None or not any(y_[0] in ("store", "storei") for y_ in out_[pos_ + 1:ci2_]):
                    continue
                nm_ = f"a{counter[0]}"; counter[0] += 1
                vars_[nm_] = "long"
                out_.insert(pos_ + 1, ("lete", nm_, x_))
                args_[ai_] = ("var", nm_)
                changed_ = True
            if changed_:
                k_ = out_.index(it)
                out_[k_] = (it[0], it[1], it[2], args_, it[4])
        return out_
    if "argfirst" in knobs:
        items[:] = arg_first(items)
    def load_first(its):
        def refs_(obj, acc_):
            if isinstance(obj, tuple):
                if len(obj) == 2 and obj[0] == "var" and isinstance(obj[1], str):
                    acc_.add(obj[1])
                    return acc_
                for x_ in obj:
                    refs_(x_, acc_)
            elif isinstance(obj, list):
                for x_ in obj:
                    refs_(x_, acc_)
            return acc_
        out_ = []
        for it in its:
            if it[0] == "if":
                it = ("if", it[1], load_first(it[2]))
            elif it[0] == "diamond":
                it = (it[0], it[1], it[2], load_first(it[3]), load_first(it[4]))
            elif it[0] == "loop":
                it = (it[0], it[1], load_first(it[2])) + tuple(it[3:])
            if it[0] in ("call", "vcall"):
                k_ = len(out_)
                while k_ > 0 and out_[k_ - 1][0] == "let":
                    k_ -= 1
                run_ = out_[k_:]
                if len(run_) > 1:
                    cu_ = refs_(it[3] if it[0] == "call" else (it[4], it[5]), set())
                    late_ = [x_ for x_ in run_ if x_[1] not in cu_]
                    early_ = [x_ for x_ in run_ if x_[1] in cu_]
                    new_ = late_ + early_
                    seen_, ok_ = set(), True
                    names_ = {x_[1] for x_ in run_}
                    for x_ in new_:
                        if (refs_(x_[4], set()) & names_) - seen_:
                            ok_ = False
                            break
                        seen_.add(x_[1])
                    if ok_ and new_ != run_:
                        out_[k_:] = new_
            out_.append(it)
        return out_
    if "loadfirst" in knobs:
        items[:] = load_first(items)
    def split_merged_stores():
        uses_ = {}
        def scan(its):
            for it in its:
                if it[0] in ("let", "leti"):
                    uses_.setdefault((it[2], it[3]), set()).add("load")
                elif it[0] == "store" and len(it) == 5:
                    uses_.setdefault((it[1], it[2]), set()).add("const" if it[4][0] == "const" else "value")
                elif it[0] == "storei":
                    uses_.setdefault((it[1], it[2]), set()).add("value")
                if it[0] == "if":
                    scan(it[2])
                elif it[0] == "diamond":
                    scan(it[3]); scan(it[4])
                elif it[0] == "loop":
                    scan(it[2])
        scan(items)
        WT = {1: "unsigned char", 2: "unsigned short", 4: "int", 8: "long"}
        plan_ = {}
        for sn_, fl_ in structs.items():
            for o_, (ct_, ch_) in list(fl_.items()):
                if ct_.startswith("ARRAY:") or ct_ not in SIZE:
                    continue
                sz_ = SIZE[ct_]
                inner_ = [o2 for o2 in fl_ if o_ < o2 < o_ + sz_]
                if not inner_ or uses_.get((sn_, o_)) != {"const"}:
                    continue
                if any(o2 + SIZE.get(fl_[o2][0], 99) > o_ + sz_ for o2 in inner_):
                    continue
                cuts_ = sorted({o_, o_ + sz_} | set(inner_) | {o2 + SIZE[fl_[o2][0]] for o2 in inner_})
                pieces_ = []
                for lo_, hi_ in zip(cuts_, cuts_[1:]):
                    pos_ = lo_
                    while pos_ < hi_:
                        for w_ in (8, 4, 2, 1):
                            if pos_ % w_ == 0 and pos_ + w_ <= hi_:
                                pieces_.append((pos_, w_)); pos_ += w_; break
                plan_[(sn_, o_)] = (sz_, pieces_)
        if not plan_:
            return
        def rewrite(its):
            out_ = []
            for it in its:
                if it[0] == "store" and len(it) == 5 and (it[1], it[2]) in plan_ and it[4][0] == "const":
                    sz_, pieces_ = plan_[(it[1], it[2])]
                    val_ = it[4][1] & ((1 << (8 * sz_)) - 1)
                    for po_, w_ in pieces_:
                        pv_ = (val_ >> (8 * (po_ - it[2]))) & ((1 << (8 * w_)) - 1)
                        ft_ = structs[it[1]].get(po_, (WT[w_], None))[0]
                        if SIZE.get(ft_) != w_:
                            ft_ = WT[w_]
                        structs[it[1]].setdefault(po_, (ft_, None))
                        if w_ <= 4 and pv_ >= 1 << (8 * w_ - 1) and ft_ in ("int", "short", "signed char"):
                            pv_ -= 1 << (8 * w_)
                        out_.append(("store", it[1], po_, it[3], ("const", pv_, "x" if w_ == 8 else "w")))
                    continue
                if it[0] == "if":
                    it = ("if", it[1], rewrite(it[2]))
                elif it[0] == "diamond":
                    it = (it[0], it[1], it[2], rewrite(it[3]), rewrite(it[4]))
                elif it[0] == "loop":
                    it = (it[0], it[1], rewrite(it[2])) + tuple(it[3:])
                out_.append(it)
            return out_
        for (sn_, o_) in plan_:
            structs[sn_].pop(o_, None)
        items[:] = rewrite(items)
    def split_wide_const_stores(its):
        out_ = []
        for it in its:
            if it[0] == "store" and len(it) == 5 and it[4][0] == "const" and it[4][2] == "x" and vu_of_(it[1], it[2]) is None:
                ft_ = structs[it[1]].get(it[2], ("long", None))[0]
                if SIZE.get(ft_, 8) < 8:
                    out_.extend(const_pieces_(it[1], it[2], 8, it[4][1], it[3]))
                    continue
            if it[0] == "if":
                it = ("if", it[1], split_wide_const_stores(it[2]))
            elif it[0] == "diamond":
                it = (it[0], it[1], it[2], split_wide_const_stores(it[3]), split_wide_const_stores(it[4]))
            elif it[0] == "loop":
                it = (it[0], it[1], split_wide_const_stores(it[2])) + tuple(it[3:])
            out_.append(it)
        return out_
    items[:] = split_wide_const_stores(items)
    if "nosplitstores" not in knobs:
        split_merged_stores()
    # usage of call results and variable widths
    used = set()
    def flag_values(f):
        if f is None:
            return []
        if f[0] == "ccmp":
            return flag_values(f[1]) + flag_values(f[3])
        return [f[1], f[2]]
    def mark(v, as_arith=False):
        if v is None:
            return
        if v[0] == "hi":
            used.add(v[1]); PAIRS_.add(v[1])
            return
        if v[0] == "var":
            used.add(v[1])
        if v[0] == "param" and as_arith:
            arith.add(v[1])
        kids = []
        if v[0] in ("fbin",):
            kids = [v[2], v[3]]
        if v[0] in ("funary", "i2f", "f2i"):
            kids = [v[2]]
        if v[0] == "fselect":
            kids = ([v[1][0][1], v[1][0][2]] if "nomarkfix" in knobs else flag_values(v[1][0])) + [v[2], v[3]]
        if v[0] == "elem":
            kids = [v[1], v[2]]
        if v[0] in ("sub", "sub2"):
            kids = [v[1], v[3]]
        if v[0] == "pick":
            kids = flag_values(v[1][0]) + [v[2]]
        if v[0] == "bytes":
            kids = [v[1], v[2]]
        if v[0] == "ext":
            kids = [v[2]]
        if v[0] == "pair":
            kids = [v[1], v[2]]
        if v[0] == "range":
            kids = [v[1]]
        if v[0] == "copy":
            kids = [v[1]]
        if v[0] in ("vlane", "vecu", "vpart", "udiv", "urem", "sdiv", "srem", "udiv64", "urem64", "f2y"):
            kids = [v[1]]
        if v[0] in ("vins", "vcomb"):
            kids = [v[1], v[2]]
        if v[0] in ("fbits", "ibits"):
            kids = [v[1]]
        if v[0] == "vecuv":
            kids = [v[1]]
        if v[0] == "vbin":
            kids = [v[2], v[3]]
        if v[0] in ("vneg", "vsplat"):
            kids = [v[1]]
        if v[0] == "vfma":
            kids = [x_ for x_ in v[2:5]]
        if v[0] == "bin":
            kids = [v[2], v[3]]
        elif v[0] in ("cond", "select"):
            kids = flag_values(v[1][0]) + ([v[2], v[3]] if v[0] == "select" else [])
        for x in kids:
            mark(x, True)
        if "nomarkfix" not in knobs and v[0] not in ("var", "hi"):
            mark_vars_(v)
    def mark_vars_(v):
        for x in v[1:]:
            if isinstance(x, (tuple, list)):
                if len(x) == 2 and x[0] == "var" and isinstance(x[1], str):
                    used.add(x[1])
                else:
                    mark_vars_(x)
    def mark_items(its):
        for it in its:
            if it[0] == "bfstore":
                mark(it[3]); mark(it[4])
            if it[0] == "copy8":
                mark(it[1]); mark(it[3])
            if it[0] == "blkcopy":
                mark(it[1]); mark(it[3])
            if it[0] == "valinit":
                mark(it[1])
            if it[0] == "store":
                mark(it[3]); mark(it[4])
            elif it[0] == "let":
                mark(it[4])
            elif it[0] == "leti":
                mark(it[4]); mark(it[5], True)
            elif it[0] == "storei":
                mark(it[3]); mark(it[4], True); mark(it[5])
            elif it[0] == "call":
                for x in it[3]:
                    mark(x)
            elif it[0] == "vcall":
                mark(it[4])
                for x in it[5]:
                    mark(x)
            elif it[0] == "return":
                mark(it[1])
            elif it[0] == "if":
                f, cc = it[1]
                for fv_ in flag_values(f):
                    mark(fv_, True)
                mark_items(it[2])
            elif it[0] == "diamond":
                f, cc = it[1]
                for fv_ in flag_values(f):
                    mark(fv_, True)
                mark_items(it[3]); mark_items(it[4])
            elif it[0] == "assign":
                mark(it[2])
            elif it[0] == "spin":
                mark(it[3]); mark(it[4])
            elif it[0] == "contassign":
                for n_, v_ in it[1]:
                    mark(v_)
            elif it[0] == "lete":
                mark(it[2], True)
            elif it[0] == "loop":
                for name, v, r in it[1]:
                    mark(v)
                mark_items(it[2])
                for name, nv in it[3]:
                    mark(nv)
                f, cc = it[4]
                mark(f[1], True); mark(f[2], True)
    arith0 = set(arith)
    mark_items(items)
    def prune_merges(its):
        out_, changed = [], False
        for it in its:
            if it[0] == "diamond":
                keep = [d_ for d_ in it[2] if d_[0] in used]
                dead = {d_[0] for d_ in it[2]} - {d_[0] for d_ in keep}
                a3, c3 = prune_merges([x for x in it[3] if not (x[0] == "assign" and x[1] in dead)])
                a4, c4 = prune_merges([x for x in it[4] if not (x[0] == "assign" and x[1] in dead)])
                changed = changed or bool(dead) or c3 or c4
                it = (it[0], it[1], keep, a3, a4)
            elif it[0] == "if":
                b_, c_ = prune_merges(it[2])
                changed = changed or c_
                it = ("if", it[1], b_)
            elif it[0] == "loop" and "noloopprune" not in knobs:
                b_, c_ = prune_merges(it[2])
                changed = changed or c_
                it = (it[0], it[1], b_) + tuple(it[3:])
            out_.append(it)
        return out_, changed
    for _ in range(4):
        items_, changed_ = prune_merges(items)
        if not changed_:
            break
        items[:] = items_
        used.clear(); arith.clear(); arith |= arith0
        mark_items(items)
    # values that also reach a used merge outside the float registers (a call result is in x0 and s0) stay as
    # they are
    def merge_leaves_(x_, acc_):
        if not isinstance(x_, tuple) or x_[0] != "var" or x_[1] in acc_:
            return acc_
        acc_.add(x_[1])
        tv_ = vars_.get(x_[1])
        if isinstance(tv_, tuple) and tv_[0] == "merge":
            merge_leaves_(tv_[1], acc_); merge_leaves_(tv_[2], acc_)
        return acc_
    int_side_ = set()
    for nm_, tv_ in list(vars_.items()):
        if isinstance(tv_, tuple) and tv_[0] == "merge" and nm_ not in fmerges_:
            merge_leaves_(("var", nm_), int_side_)
    if arr_scalar_:
        def arr_vars_(its):
            for it_ in its:
                if it_[0] == "leti" and len(it_) == 6 and (it_[2], it_[3]) in arr_scalar_ and isinstance(vars_.get(it_[1]), tuple) \
                        and len(vars_[it_[1]]) == 3:
                    vars_[it_[1]] = vars_[it_[1]] + (arr_scalar_[(it_[2], it_[3])],)
                elif it_[0] == "if":
                    arr_vars_(it_[2])
                elif it_[0] == "diamond":
                    arr_vars_(it_[3]); arr_vars_(it_[4])
                elif it_[0] == "loop":
                    arr_vars_(it_[2])
        arr_vars_(items)
    callee_of_ = {}
    def calls_in_(its):
        for it_ in its:
            if it_[0] == "call":
                callee_of_[it_[1]] = it_[2]
            elif it_[0] == "if":
                calls_in_(it_[2])
            elif it_[0] == "diamond":
                calls_in_(it_[3]); calls_in_(it_[4])
            elif it_[0] == "loop":
                calls_in_(it_[2])
    calls_in_(items)
    # the float merges connected to a used one (sharing values) are typed together
    fl_all_ ={n_: merge_leaves_(("var", n_), set()) for n_ in fmerges_} if "nofmerge" not in knobs else {}
    done_ = set()
    for start_ in sorted(set(fl_all_) & used):
        if start_ in done_:
            continue
        comp_, members_ = set(fl_all_[start_]), {start_}
        grew_ = True
        while grew_:
            grew_ = False
            for n_, lv_ in fl_all_.items():
                if n_ not in members_ and (lv_ & comp_):
                    members_.add(n_); comp_ |= lv_; grew_ = True
        done_ |= members_
        if comp_ & int_side_:
            continue
        if any(isinstance(vars_.get(x_), str) and vars_.get(x_) not in ("?", "f") for x_ in comp_):
            continue
        # a callee whose result is an int at another call keeps its type
        if any(x_ in callee_of_ and any(callee_of_.get(y_) == callee_of_[x_] and y_ not in comp_ and vars_.get(y_) != "f"
                                       for y_ in callee_of_) for x_ in comp_):
            continue
        for x_ in sorted(comp_):
            if vars_.get(x_) == "?":
                vars_[x_] = "f"
    def ptype(n):
        p = pwidth.get(n, "x")
        if p == "VecU":
            return "VecU"
        if p == "w":
            return "int"
        if p in ("short", "unsigned short", "signed char", "unsigned char"):
            return p
        if p == "x":
            return "long" if n in arith else "void*"
        return f"{p}*"
    def vtype(v):
        if v[0] == "fbits":
            return "unsigned int"
        if v[0] == "ibits":
            return "float"
        if v[0] == "hi" or (v[0] == "var" and v[1] in PAIRS_) or v[0] == "undef":
            return "long"
        if v[0] == "fundef":
            return "float"
        if v[0] == "retobj":
            return f"{RETN_}*"
        if v[0] == "retval":
            return RETN_
        if v[0] in ("fparam", "fconst", "fbin", "funary", "i2f", "fselect", "vlane"):
            return "float"
        if v[0] in ("vconst", "vbin", "vsplat", "vfma", "vneg", "vparam", "vins", "vundef", "vcomb", "vecuv"):
            return "Vec4f"
        if v[0] == "vecu":
            return "VecU"
        if v[0] == "vpart" and "novcomb" not in knobs:
            return "long"
        if v[0] in ("udiv", "urem", "sdiv", "srem"):
            return "int"
        if v[0] in ("udiv64", "urem64"):
            return "unsigned long"
        if v[0] == "umulh":
            raise Fail("umulh")  # below 2**31: the divisor is at least 2
        if v[0] == "f2i":
            return "long" if v[3] == "x" else "int"
        if v[0] == "stackaddr":
            st = stack_obj(v[1]); sn = stackobjs.get(st)
            if sn is None:
                raise Fail("unused stack object")
            if set(structs[sn]) == {0} and v[1] == st and sn not in stack_min_:
                return structs[sn][0][0] + "*"
            if v[1] == st:
                return f"{sn}*"
            fld = structs[sn].get(v[1] - st)
            if not fld:
                raise Fail("stack field address")
            return fld[0] + "*"
        if v[0] in ("gotaddr", "local"):
            sn = f"{'Global' if v[0] == 'gotaddr' else 'Local'}{v[1]:x}_{a:x}"
            return f"{sn}*" if structs.get(sn) else "unsigned char*"
        if v[0] == "param":
            return ptype(v[1])
        if v[0] == "const":
            return "long" if v[2] == "x" else "int"
        if v[0] == "var":
            t = vars_[v[1]]
            if isinstance(t, tuple) and t[0] == "load":
                ct, child = structs[t[1]][t[2]]
                if ct == "ARRAY:void*" and child and (len(t) <= 3 or t[3] == "void*"):
                    return f"{child}*"
                if ct.startswith("ARRAY:") and len(t) > 3:
                    return t[3]
                if ct.startswith("ARRAY:"):
                    return ct[6:]
                if child:
                    return f"{child}*"
                if len(t) > 3 and t[3] != ct:
                    return t[3]
                return ct
            if isinstance(t, tuple) and t[0] == "loopvar":
                if v[1] in loopelem:
                    return f"{loopelem[v[1]]}*"
                if v[1] in UINTLOOP_:
                    return "unsigned int"
                return vtype(t[1])
            if isinstance(t, tuple) and t[0] == "merge" and v[1] in mergestructs:
                return f"{mergestructs[v[1]]}*"
            if isinstance(t, tuple) and t[0] == "merge" and v[1] in int_merges_:
                return "int"
            if isinstance(t, tuple) and t[0] == "merge":
                ta, tb = vtype(t[1]), vtype(t[2])
                if ta == tb:
                    return ta
                if {ta, tb} <= {"int", "bool", "unsigned char", "signed char", "unsigned short", "short"} or \
                        ("nouintloop" not in knobs and {ta, tb} == {"int", "unsigned int"}):
                    return "int"
                if {ta, tb} <= {"int", "bool", "long"}:
                    return "long"
                if ta.endswith("*") and t[2][0] == "const" and t[2][1] == 0:
                    return ta
                if tb.endswith("*") and t[1][0] == "const" and t[1][1] == 0:
                    return tb
                if ta.endswith("*") and tb.endswith("*"):
                    return "void*"
                if "float" in (ta, tb):
                    if os.environ.get("DBG"): print("DBG merge", t, vars_.get(t[1][1]) if t[1][0]=="var" else None, vars_.get(t[2][1]) if t[2][0]=="var" else None)
                    raise Fail(f"merge types: {ta}|{tb}")
                if ta.endswith("*") or tb.endswith("*"):
                    return "long"
                raise Fail(f"merge types: {ta}|{tb}")
            if t == "f":
                return "float"
            if t == "Float2":
                return "float"
            if t in ("w", "int"):
                return "int"
            if t in ("long", "unsigned long", "short", "signed char", "unsigned short"):
                return t
            if t == "VecU":
                return "VecU"
            if t in ("x", "void*", "?"):
                return "void*" if t != "?" else "int"
            return f"{t}*"
        if v[0] == "bin":
            return "long" if v[4] == "x" else "int"
        if v[0] == "ext":
            return "long"
        if v[0] == "pair":
            return "Float2"
        if v[0] == "f2y":
            return "float"
        if v[0] == "maddr":
            return "unsigned char*" if v[3] else "void*"
        if v[0] == "range":
            return "int"
        if v[0] == "cond":
            return "int" if v[3] else "bool"
        if v[0] == "select":
            return "long" if v[4] == "x" else "int"
        if v[0] == "vconst":
            return "Vec4f"
        raise Fail("vtype")
    # loaded pointers used as bases got their own struct in struct_for via vars_ -> name
    structs_of_vars = {}
    for name, t in list(vars_.items()):
        pass
    def gname(v):
        sn = f"{'Global' if v[0] == 'gotaddr' else 'Local'}{v[1]:x}_{a:x}"
        return f"g{sn}"
    IDX_ = {}
    ESHIFT_ = {}
    def member_arg(x):
        if "memberaddr" not in knobs or x[0] != "bin" or x[1] != "+":
            return x
        c_ = x[3]
        if c_[0] == "ext" and c_[2][0] == "const":
            c_ = c_[2]
        if c_[0] != "const" or c_[1] <= 0 or x[2][0] not in ("param", "var"):
            return x
        try:
            bt_ = vtype(x[2])
        except Fail:
            return x
        if not bt_.endswith("*") or bt_ in ("void*", "unsigned char*") or bt_[:-1] not in structs:
            return x
        sn_ = bt_[:-1]
        have_ = structs[sn_].get(c_[1])
        if have_ is None:
            structs[sn_][c_[1]] = ("ARRAY:unsigned char", None)
            return ("maddr", x[2], c_[1], True)
        return ("maddr", x[2], c_[1], have_[0].startswith("ARRAY:"))
    def acc(base, off):
        if base[0] == "sub2":
            return f"{acc(base[1], base[2])}[{iexpr_(base[3])}].field_{off:x}"
        if base[0] == "sub":
            return f"{acc(base[1], base[2])}[{iexpr_(base[3])}]"
        if base[0] == "var" and base[1] in ESHIFT_ and base[1] not in IDX_:
            return f"{base[1]}->field_{off - ESHIFT_[base[1]]:x}"
        if base[0] == "var" and base[1] in IDX_:
            return f"{base[1]}[{IDX_[base[1]]}].field_{off - ESHIFT_.get(base[1], 0):x}"
        if base[0] == "bytes":
            sn_ = bytekinds[base]
            if base[2][0] == "const" and base[2][1] < 0:
                return f"reinterpret_cast<{sn_}*>(reinterpret_cast<unsigned char*>({expr(base[1])}) - {hex(-base[2][1])})->field_{off:x}"
            return f"reinterpret_cast<{sn_}*>(reinterpret_cast<unsigned char*>({expr(base[1])}) + {expr(base[2], 'noaddrparen' in knobs)})->field_{off:x}"
        if base[0] == "bin" and base in bytekinds:
            sn_ = bytekinds[base]
            e_ = expr(base)
            if vtype(base).endswith("*"):
                return f"reinterpret_cast<{sn_}*>({e_})->field_{off:x}"
            return f"reinterpret_cast<{sn_}*>(static_cast<long>({e_}))->field_{off:x}"
        if base[0] == "select":
            sn_ = bytekinds[base]
            a_ = f"reinterpret_cast<{sn_}*>({expr(base[2])})->field_{off:x}"
            b_ = f"reinterpret_cast<{sn_}*>({expr(base[3])})->field_{off:x}"
            return f"({cond(*base[1])} ? {a_} : {b_})"
        if base[0] == "elem":
            en = elemkinds[(base[1], base[3])]
            if base[2][0] == "pick":
                pk = base[2]
                arr_ = f"reinterpret_cast<{en}*>({expr(base[1])})"
                hit_, miss_ = f"&{arr_}[{iexpr_(pk[2])}]", f"&{arr_}[0]"
                a_, b_ = (miss_, hit_) if pk[3] else (hit_, miss_)
                return f"({cond(*pk[1])} ? {a_} : {b_})->field_{off:x}"
            b1_ = base[1]
            if "noelemaddr" not in knobs and b1_[0] == "bin" and b1_[1] == "+" and b1_[4] == "x" and cval_(b1_[3]) is not None \
                    and b1_[2][0] != "const" and vtype(b1_[2]).endswith("*") and not vtype(base[2]).endswith("*"):
                # base + i*stride + const as one byte-pointer expression, the constant last
                c_ = cval_(b1_[3])
                return f"reinterpret_cast<{en}*>(reinterpret_cast<unsigned char*>({expr(b1_[2])}) + static_cast<long>({expr(base[2])}) * {hex(base[3])}" \
                    f" {'+' if c_ >= 0 else '-'} {hex(abs(c_))})->field_{off:x}"
            return f"reinterpret_cast<{en}*>({expr(base[1])})[{iexpr_(base[2])}].field_{off:x}"
        if base[0] == "stackobj":
            sn = stackobjs[base[1]]
            if set(structs[sn]) == {0} and sn not in stack_min_:
                return f"local_{hx_(base[1])}"
            return f"local_{hx_(base[1])}.field_{off:x}"
        if base[0] == "retobj":
            return f"r.field_{off:x}"
        if base[0] in ("gotaddr", "local"):
            sn = f"{'Global' if base[0] == 'gotaddr' else 'Local'}{base[1]:x}_{a:x}"
            if set(structs[sn]) == {0}:
                return gname(base)
            return f"{gname(base)}.field_{off:x}"
        return f"{expr(base)}->field_{off:x}"
    def sexpr_(v_, top_=False):
        """A scalar float operand: a value typed Vec4f is its lane 0."""
        if "noscalarlane" not in knobs and v_[0] not in ("fconst", "fparam") and vtype(v_) == "Vec4f":
            return f"{expr(v_, False)}[0]"
        return expr(v_, top_)
    sdst_cache_ = []
    def store_dsts_():
        """Variables used as the base of a store (destinations)."""
        if not sdst_cache_:
            acc_ = set()
            def walk_(its_):
                for it_ in its_:
                    if not isinstance(it_, tuple) or not it_:
                        continue
                    if it_[0] in ("store", "storei") and len(it_) > 3 and isinstance(it_[3], tuple) and it_[3][0] == "var":
                        acc_.add(it_[3][1])
                    for x_ in it_:
                        if isinstance(x_, list):
                            walk_(x_)
            walk_(items)
            sdst_cache_.append(acc_)
        return sdst_cache_[0]
    def iexpr_(v_):
        """An index: a pointer-typed value goes through reinterpret_cast<long>."""
        e_ = expr(v_)
        if "noptridx" not in knobs and vtype(v_).endswith("*"):
            return f"reinterpret_cast<long>({e_})"
        return e_
    def expr(v, top=True):
        if v[0] == "undef":
            return f"u{v[1]}"
        if v[0] == "fundef":
            return f"uf{v[1]}"
        if v[0] == "hi":
            return f"{v[1]}.b"
        if v[0] == "var" and v[1] in PAIRS_:
            return f"{v[1]}.a"
        if v[0] == "retobj":
            return "&r"
        if v[0] == "retval":
            return "r"
        if v[0] == "pick":
            c_ = cond(*v[1])
            s_ = f"{c_} ? 0 : {expr(v[2], False)}" if v[3] else f"{c_} ? {expr(v[2], False)} : 0"
            return s_ if top else f"({s_})"
        if v[0] == "fparam":
            if "nolateparam" not in knobs:
                fparams.add(v[1])
            return f"f{v[1]}"
        if v[0] == "vconst":
            return "(Vec4f){" + ", ".join(expr(("fconst", x_)) for x_ in v[1]) + "}"
        if v[0] == "vlane":
            if v[1][0] != "var":
                return f"({expr(v[1], False)})[{v[2]}]"
            return f"{expr(v[1], False)}[{v[2]}]"
        if v[0] == "vparam":
            return f"p{v[1]}.v"
        if v[0] == "udiv64":
            xs_ = expr(v[1])
            if vtype(v[1]).endswith("*"):
                xs_ = f"reinterpret_cast<unsigned long>({xs_})"
            s_ = f"static_cast<unsigned long>({xs_}) / {v[2]}ul"
            return s_ if top else f"({s_})"
        if v[0] == "urem64":
            xs_ = expr(v[1])
            if vtype(v[1]).endswith("*"):
                xs_ = f"reinterpret_cast<unsigned long>({xs_})"
            s_ = f"static_cast<unsigned long>({xs_}) % {v[2]}ul"
            return s_ if top else f"({s_})"
        if v[0] == "umulh":
            raise Fail("umulh")
        if v[0] in ("sdiv", "srem"):
            if vtype(v[1]).endswith("*"):
                raise Fail("division of a pointer")
            s_ = f"static_cast<int>({expr(v[1])}) {'/' if v[0] == 'sdiv' else '%'} {v[2]}"
            return s_ if top else f"({s_})"
        if v[0] in ("udiv", "urem"):
            xs_ = expr(v[1])
            if vtype(v[1]).endswith("*"):
                raise Fail("division of a pointer")
            s_ = f"static_cast<unsigned int>({xs_}) {'/' if v[0] == 'udiv' else '%'} {v[2]}u"
            return s_ if top else f"({s_})"
        if v[0] == "vins":
            return f"vins({expr(v[1])}, {expr(v[2])}, {v[3]})"
        if v[0] == "fbits":
            return f"[&] {{ unsigned int b_; float f_ = {expr(v[1])}; __builtin_memcpy(&b_, &f_, 4); return b_; }}()"
        if v[0] == "ibits":
            return f"[&] {{ unsigned int b_ = static_cast<unsigned int>({fit(expr(v[1]), vtype(v[1]), 'long')}); float f_; __builtin_memcpy(&f_, &b_, 4); return f_; }}()"
        if v[0] == "vecuv":
            return f"{expr(v[1])}.v"
        if v[0] == "vpart" and "novcomb" not in knobs:
            return f"vecu({expr(v[1])}).l[{v[2]}]"
        if v[0] == "vcomb":
            def u64_(x_):
                tx_ = vtype(x_)
                return f"reinterpret_cast<unsigned long>({expr(x_)})" if tx_.endswith("*") else f"static_cast<unsigned long>({expr(x_)})"
            return f"((Vec4f)vcombine_f32(vcreate_f32({u64_(v[1])}), vcreate_f32({u64_(v[2])})))"
        if v[0] == "vundef":
            return "vundef()"
        if v[0] == "vecu":
            return f"vecu({expr(v[1])})"
        if v[0] in ("vpart", "vlo"):
            raise Fail("vector half used")
        if v[0] == "vbin":
            s_ = f"{expr(v[2], False)} {v[1]} {expr(v[3], False)}"
            return s_ if top else f"({s_})"
        if v[0] == "vneg":
            return f"-{expr(v[1], False)}"
        if v[0] == "vsplat":
            return f"(Vec4f)({expr(v[1])})"
        if v[0] == "vfma":
            _, sub_, acc_, a_, b_, lane_i = v
            q_ = lambda x_: f"(float32x4_t)({expr(x_)})"
            if lane_i is None:
                return f"(Vec4f)vf{'ms' if sub_ else 'ma'}q_f32({q_(acc_)}, {q_(a_)}, {q_(b_)})"
            return f"(Vec4f)vf{'ms' if sub_ else 'ma'}q_laneq_f32({q_(acc_)}, {q_(a_)}, {q_(b_)}, {lane_i})"
        if v[0] == "fconst":
            import struct as _st
            val_ = float(v[1])
            s_ = None
            if val_ != val_ or val_ in (float("inf"), float("-inf")):
                raise Fail("special float")
            for digits in range(1, 10):
                cand = "%.*g" % (digits, val_)
                try:
                    if _st.unpack("<f", _st.pack("<f", float(cand)))[0] == _st.unpack("<f", _st.pack("<f", val_))[0]:
                        s_ = cand
                        break
                except OverflowError:
                    continue
            s_ = s_ or "%.9g" % val_
            if "e" not in s_ and "." not in s_ and "inf" not in s_ and "nan" not in s_:
                s_ += ".0"
            return s_ + "f"
        if v[0] == "fbin":
            s_ = f"{sexpr_(v[2])} {v[1]} {sexpr_(v[3])}"
            return s_ if top else f"({s_})"
        if v[0] == "funary":
            if v[1] in ("floor", "ceil", "round", "trunc"):
                return f"__builtin_{v[1]}f({sexpr_(v[2], True)})"
            return f"-{sexpr_(v[2])}" if v[1] == "fneg" else f"__builtin_fabsf({sexpr_(v[2], True)})"
        if v[0] == "i2f":
            ut = ("unsigned long" if v[3] == "x" else "unsigned int") if v[1] else ("long" if v[3] == "x" else "int")
            return f"static_cast<float>(static_cast<{ut}>({expr(v[2])}))"
        if v[0] == "f2i":
            ut = ("unsigned long" if v[3] == "x" else "unsigned int") if v[1] else ("long" if v[3] == "x" else "int")
            return f"static_cast<{ut}>({sexpr_(v[2], True)})"
        if v[0] == "fselect":
            s_ = f"{cond(*v[1])} ? {expr(v[2], False)} : {expr(v[3], False)}"
            return s_ if top else f"({s_})"
        if v[0] == "pair":
            return f"Float2{{{expr(v[1])}, {expr(v[2])}}}"
        if v[0] == "maddr":
            arr_ = v[3]
            if "nobytearr" not in knobs:
                try:
                    st_ = vtype(v[1])[:-1]
                    arr_ = structs.get(st_, {}).get(v[2], ("ARRAY:",))[0].startswith("ARRAY:")
                except Fail:
                    pass
            return f"{expr(v[1])}->field_{v[2]:x}" if arr_ else f"&{expr(v[1])}->field_{v[2]:x}"
        if v[0] == "range":
            return f"static_cast<{v[3]}>({expr(v[1])} - {v[2]:#x})"
        if v[0] == "ext":
            wide_ = "unsigned long" if v[1].startswith("unsigned") else "long"
            return f"static_cast<{wide_}>(static_cast<{v[1]}>({expr(v[2])}))"
        if v[0] == "stackaddr":
            st = stack_obj(v[1]); sn = stackobjs.get(st)
            if sn is None:
                raise Fail("unused stack object")
            if v[1] == st:
                return f"&local_{hx_(st)}"
            return f"&local_{hx_(st)}.field_{v[1] - st:x}"
        if v[0] in ("gotaddr", "local"):
            sn = f"{'Global' if v[0] == 'gotaddr' else 'Local'}{v[1]:x}_{a:x}"
            if sn not in structs:
                structs[sn] = {}
                gobjs[sn] = v
            return f"&{gname(v)}" if structs[sn] else gname(v)
        if v[0] == "param":
            if "nolateparam" not in knobs and v[1] not in pwidth:
                pwidth[v[1]] = "x"
            return f"p{v[1]}"
        if v[0] == "var":
            if v[1] in IDX_:
                return f"&{v[1]}[{IDX_[v[1]]}]" if top else f"(&{v[1]}[{IDX_[v[1]]}])"
            if vars_.get(v[1]) == "Float2":
                return f"({inline_map[v[1]]}).x" if v[1] in inline_map else f"{v[1]}.x"
            if v[1] in inline_map:
                return inline_map[v[1]] if top else f"({inline_map[v[1]]})"
            return v[1]
        if v[0] == "f2y":
            n_ = v[1][1]
            return f"({inline_map[n_]}).y" if n_ in inline_map else f"{n_}.y"
        if v[0] == "const":
            val = v[1]
            if v[2] == "w" and val >= 1 << 31:
                val -= 1 << 32
            return str(val) if -10 < val < 10 else (hex(val) if val > 0 else f"-{hex(-val)}")
        if v[0] == "bin" and "bytecast" in knobs and v[1] == "&" and v[3][0] == "const" and v[3][1] in (0xff, 0xffff) and not vtype(v[2]).endswith("*"):
            return f"static_cast<{'unsigned char' if v[3][1] == 0xff else 'unsigned short'}>({expr(v[2])})"
        cv_ = (v[3][1] if v[3][0] == "const" else (v[3][2][1] & 0xffffffff if v[3][0] == "ext" and v[3][1] == "unsigned int" and v[3][2][0] == "const" else None)) \
            if v[0] == "bin" and len(v) > 3 and isinstance(v[3], tuple) else None
        if v[0] == "bin" and v[1] in ("+", "-") and v[4] == "x" and "noelemaddr" not in knobs and cv_ is not None \
                and v[2][0] == "bin" and v[2][1] == "+" and v[2][4] == "x":
            pi_ = [(p_, i_) for p_, i_ in ((v[2][2], v[2][3]), (v[2][3], v[2][2]))
                   if p_[0] != "const" and vtype(p_).endswith("*") and cval_(i_) is None and not vtype(i_).endswith("*")]
            if pi_:
                # (pointer + index) + constant as one byte-pointer expression, the constant last
                p_, i_ = pi_[0]
                c_ = cv_ if v[1] == "+" else -cv_
                return f"reinterpret_cast<long>(reinterpret_cast<unsigned char*>({expr(p_)}) + {expr(i_, False)} {'+' if c_ >= 0 else '-'} {hex(abs(c_))})"
        if v[0] == "bin" and v[1] in ("+", "-") and v[4] == "x" and "noptradd" not in knobs and cv_ is not None \
                and vtype(v[2]).endswith("*") and v[2][0] != "const":
            c_ = cv_ if v[1] == "+" else -cv_
            s = f"reinterpret_cast<long>(reinterpret_cast<unsigned char*>({expr(v[2])}) {'+' if c_ >= 0 else '-'} {hex(abs(c_))})"
            return s
        if v[0] == "bin":
            x, y = expr(v[2], False), expr(v[3], False)
            if vtype(v[2]).endswith("*"):
                x = f"reinterpret_cast<long>({expr(v[2])})"
            if vtype(v[3]).endswith("*"):
                y = f"reinterpret_cast<long>({expr(v[3])})"
            s = f"{x} {v[1]} {y}"
            if v[5] == "lsr":
                s = f"{'reinterpret' if vtype(v[2]).endswith('*') else 'static'}_cast<unsigned {'long' if v[4] == 'x' else 'int'}>({expr(v[2])}) >> {y}"
            return s if top else f"({s})"
        if v[0] == "cond":
            c = cond(*v[1]); s = f"-({c})" if v[3] else c
            return s if top else f"({s})"
        if v[0] == "select" and v[4] == "x":
            for x_, y_, swap in ((v[2], v[3], False), (v[3], v[2], True)):
                if x_[0] == "bin" and x_[1] == "+" and x_[2] == y_ and y_[0] in ("param", "var", "local", "gotaddr", "bin"):
                    st_ = stride_of(x_[3])
                    if st_:
                        en = struct_for(("elem", y_, st_[0], st_[1]))
                        arr_ = f"reinterpret_cast<{en}*>({expr(y_)})"
                        hit_, miss_ = f"&{arr_}[{iexpr_(st_[0])}]", f"&{arr_}[0]"
                        a_, b_ = (miss_, hit_) if swap else (hit_, miss_)
                        s_ = f"reinterpret_cast<long>({cond(*v[1])} ? {a_} : {b_})"
                        return s_
        if v[0] == "select":
            if "notypefit" not in knobs:
                t_ = vtype(v)
                s = f"{cond(*v[1])} ? {fit(expr(v[2], False), vtype(v[2]), t_)} : {fit(expr(v[3], False), vtype(v[3]), t_)}"
            else:
                s = f"{cond(*v[1])} ? {expr(v[2], False)} : {expr(v[3], False)}"
            return s if top else f"({s})"
        raise Fail("expr")
    FCC = {"eq": "{x} == {y}", "ne": "{x} != {y}", "mi": "{x} < {y}", "gt": "{x} > {y}", "ge": "{x} >= {y}",
           "ls": "{x} <= {y}", "lt": "!({x} >= {y})", "le": "!({x} > {y})", "hi": "!({x} <= {y})", "pl": "!({x} < {y})",
           "vs": None}
    def nzcv_holds(nzcv, cc):
        N, Z, C, V = (nzcv >> 3) & 1, (nzcv >> 2) & 1, (nzcv >> 1) & 1, nzcv & 1
        return {"eq": Z, "ne": not Z, "hs": C, "lo": not C, "mi": N, "pl": not N, "hi": C and not Z,
                "ls": (not C) or Z, "ge": N == V, "lt": N != V, "gt": (not Z) and N == V, "le": Z or N != V}[cc]
    def cond(f, cc):
        if f is not None and f[0] == "ccmp":
            _, prev, pcc, second, nzcv = f
            if cc not in CC and not (second[0] == "fcmp" and FCC.get(cc) and "nofccmp" not in knobs):
                raise Fail("ccmp cc")
            first_s = cond(prev, pcc)
            second_s = cond(second, cc)
            if nzcv_holds(nzcv, cc):
                return f"!({first_s}) || {second_s}"
            return f"({first_s}) && {second_s}"
        if f is not None and f[0] == "fcmp":
            form = FCC.get(cc)
            if not form:
                raise Fail("fcc")
            return form.format(x=sexpr_(f[1]), y=sexpr_(f[2]))
        if f is None or cc not in CC:
            raise Fail("cond")
        kind, x, y, w = f
        if kind == "cmp" and x[0] == "range" and y[0] == "const" and cc in ("ls", "hi", "lo", "hs"):
            lo_, hi_ = x[2], x[2] + (y[1] if cc in ("ls", "hi") else y[1] - 1)
            p_ = expr(x[1])
            if cc in ("ls", "lo"):
                return f"({p_} >= {lo_:#x} && {p_} <= {hi_:#x})"
            return f"({p_} < {lo_:#x} || {p_} > {hi_:#x})"
        if kind == "tst":
            if cc not in ("eq", "ne"):
                raise Fail("tst cc")
            xs_ = f"reinterpret_cast<long>({expr(x)})" if vtype(x).endswith("*") else expr(x, False)
            if "bytecast" in knobs and y[0] == "const" and y[1] in (0xff, 0xffff) and not vtype(x).endswith("*"):
                return f"static_cast<{'unsigned char' if y[1] == 0xff else 'unsigned short'}>({expr(x)}) {CC[cc]} 0"
            return f"({xs_} & {expr(y, False)}) {CC[cc]} 0"
        xs, ys = expr(x, False), expr(y, False)
        px_, py_ = vtype(x).endswith("*"), vtype(y).endswith("*")
        if cc in ("lo", "ls", "hi", "hs"):
            ut = "unsigned long" if w == "x" else "unsigned int"
            xs = (f"static_cast<{ut}>(reinterpret_cast<unsigned long>({expr(x)}))" if px_ and ut == "unsigned int"
                  else f"{'reinterpret' if px_ else 'static'}_cast<{ut}>({expr(x)})")
            if y[0] != "const":
                ys = (f"static_cast<{ut}>(reinterpret_cast<unsigned long>({expr(y)}))" if py_ and ut == "unsigned int"
                      else f"{'reinterpret' if py_ else 'static'}_cast<{ut}>({expr(y)})")
        elif px_ != py_ and not (y[0] == "const" and y[1] == 0) and not (x[0] == "const" and x[1] == 0):
            if px_:
                xs = f"reinterpret_cast<long>({expr(x)})"
            else:
                ys = f"reinterpret_cast<long>({expr(y)})"
        elif px_ and py_ and vtype(x) != vtype(y) and "notypefit" not in knobs:
            xs, ys = f"reinterpret_cast<long>({expr(x)})", f"reinterpret_cast<long>({expr(y)})"
        return f"{xs} {CC[cc]} {ys}"
    def fit(e, have, want):
        ptr = lambda t: t.endswith("*")
        if e == "0" and ptr(want):
            return "nullptr"
        if ptr(have) and want in ("int", "unsigned int", "short", "unsigned short", "signed char", "unsigned char", "bool"):
            return f"static_cast<{want}>(reinterpret_cast<long>({e}))"
        if ptr(want) != ptr(have) or (ptr(want) and want != have):
            if ptr(want) and ptr(have) and have == "void*":
                return f"static_cast<{want}>({e})"
            return f"reinterpret_cast<{want}>({e})"
        return e
    def ftype(sn, off):
        ct, child = structs[sn][off]
        if ct.startswith("ARRAY:"):
            return f"{child}*" if child else ct[6:]
        return f"{child}*" if child else ct
    # struct types for loaded pointers used as bases
    for name, t in list(vars_.items()):
        if isinstance(t, str) and t in structs and name.startswith("v"):
            pass
    # returns
    returns0 = list(returns)
    rk = [r for r in returns if r is not None]
    if rk and len(rk) != len(returns):
        def fill(its):
            out_ = []
            for it in its:
                if it[0] == "return" and it[1] is None:
                    it = ("return", ("param", 0))
                elif it[0] == "if":
                    it = ("if", it[1], fill(it[2]))
                elif it[0] == "loop":
                    it = (it[0], it[1], fill(it[2])) + tuple(it[3:])
                out_.append(it)
            return out_
        items[:] = fill(items)
        pwidth.setdefault(0, "x")
        returns[:] = [r if r is not None else ("param", 0) for r in returns]
        rk = list(returns)
    NARROW_ = {"unsigned char", "signed char", "short", "unsigned short", "bool", "char"}
    int_merges_ = set()   # merged values typed int because the return is (see noretint below)
    rtypes = {vtype(r) for r in rk}
    if len(rtypes) > 1:
        rtypes = {("int" if x in NARROW_ else x) for x in rtypes}
    def tail_vars(its, acc_):
        for it in its:
            if it[0] == "call" and it[4]:
                acc_.add(it[1])
            elif it[0] == "vcall" and it[6]:
                acc_.add(it[1])
            elif it[0] == "if":
                tail_vars(it[2], acc_)
            elif it[0] == "diamond":
                tail_vars(it[3], acc_); tail_vars(it[4], acc_)
        return acc_
    tails_ = tail_vars(items, set())
    def incidental(r):
        if r is None or r[0] == "param":
            return True
        return r[0] == "var" and r[1] not in tails_ and isinstance(vars_.get(r[1]), tuple) and vars_[r[1]][0] == "load"
    void_ok = (len(rtypes) > 1 and any(r is not None and r[0] == "var" and r[1] in tails_ for r in returns0)
               and all(incidental(r) or (r[0] == "var" and r[1] in tails_ and vars_.get(r[1]) in ("?", "w", "x")) for r in returns0))
    if "voidret" in knobs and returns0:
        # a variant: the function returns nothing and x0 at each ret is incidental
        void_ok = True
    if void_ok:
        def devoid(its):
            out_ = []
            for it in its:
                if it[0] == "return" and it[1] is not None and not (it[1][0] == "var" and it[1][1] in tails_):
                    it = ("return", None)
                elif it[0] == "if":
                    it = ("if", it[1], devoid(it[2]))
                elif it[0] == "diamond":
                    it = (it[0], it[1], it[2], devoid(it[3]), devoid(it[4]))
                out_.append(it)
            return out_
        items[:] = devoid(items)
        rtypes = {"void"}
        rk = []
    if len(rtypes) > 1:
        ptrs = {x for x in rtypes if x.endswith("*")}
        consts0 = all(vtype(r).endswith("*") or (r[0] == "const" and r[1] == 0) for r in rk)
        if rtypes <= {"int", "bool"}:
            rtype = "int"
        elif rtypes <= {"int", "bool", "long"}:
            rtype = "long"
        elif len(ptrs) == 1 and consts0:
            rtype = ptrs.pop()
        elif ptrs and rtypes <= ptrs | {"long"}:
            rtype = "void*"
        else:
            raise Fail("return types: " + "|".join(sorted(rtypes)))
    else:
        rtype = rtypes.pop() if rtypes and rtypes != {"void"} else "void"
    if rtype in ("short", "signed char"):
        rtype = "int"
    if rtype == "long" and "noretint" not in knobs:
        def int_parts_(v, seen_, merges_):
            """True when v, or a part of a merged v, is a 32-bit int; collects the merges on the way."""
            if v is None or not isinstance(v, tuple):
                return False
            if v[0] == "var":
                if v[1] in seen_:
                    return False
                seen_.add(v[1])
                tv_ = vars_.get(v[1])
                if isinstance(tv_, tuple) and tv_[0] == "merge":
                    found_ = [int_parts_(x_, seen_, merges_) for x_ in tv_[1:] if isinstance(x_, tuple)]
                    if any(found_):
                        merges_.add(v[1])
                        return True
                    return False
                if tv_ == "w":
                    return True
            try:
                return vtype(v) in ("int", "unsigned int", "bool")
            except Fail:
                return False
        merges_ = set()
        if any([int_parts_(r, set(), merges_) for r in rk]) and not any(
                i_.mnemonic == "sxtw" and i_.op_str.startswith("x0,") for i_ in ins):
            rtype = "int"
            int_merges_.update(merges_)
    # callee signatures
    for t, (args, _) in callees.items():
        pass
    NEGCC = {"eq": "ne", "ne": "eq", "lt": "ge", "ge": "lt", "le": "gt", "gt": "le", "lo": "hs", "hs": "lo", "ls": "hi",
             "hi": "ls", "mi": "pl", "pl": "mi"}
    use_count = {}
    def count(v):
        if v is None or not isinstance(v, tuple):
            return
        if v[0] == "hi":
            use_count[v[1]] = use_count.get(v[1], 0) + 2
            return
        if v[0] == "var":
            use_count[v[1]] = use_count.get(v[1], 0) + 1
            return
        for x in v[1:]:
            if isinstance(x, tuple):
                count(x)
    def count_items(its):
        for it in its:
            if it[0] == "bfstore":
                count(it[3]); count(it[4])
            if it[0] == "copy8":
                count(it[1]); count(it[3])
            if it[0] == "blkcopy":
                count(it[1]); count(it[3])
            if it[0] == "valinit":
                count(it[1])
            if it[0] in ("let",):
                count(it[4])
            elif it[0] == "leti":
                count(it[4]); count(it[5])
            elif it[0] == "store":
                count(it[3]); count(it[4])
            elif it[0] == "storei":
                count(it[3]); count(it[4]); count(it[5])
            elif it[0] in ("call",):
                for x in it[3]:
                    count(x)
            elif it[0] == "vcall":
                count(it[4])
                for x in it[5]:
                    count(x)
            elif it[0] == "return":
                count(it[1])
            elif it[0] == "if":
                for fv_ in flag_values(it[1][0]):
                    count(fv_)
                count_items(it[2])
            elif it[0] == "diamond":
                for fv_ in flag_values(it[1][0]):
                    count(fv_)
                count_items(it[3]); count_items(it[4])
            elif it[0] == "assign":
                count(it[2])
            elif it[0] == "spin":
                count(it[3]); count(it[4])
            elif it[0] == "contassign":
                for n_, v_ in it[1]:
                    count(v_)
            elif it[0] == "lete":
                count(it[2])
            elif it[0] == "loop":
                for name, v, r in it[1]:
                    count(v)
                count_items(it[2])
                for name, nv in it[3]:
                    count(nv)
                count(it[4][0][1]); count(it[4][0][2])
    count_items(items)
    inline_map = {}
    inl_seen_ = [0]
    inl_mask_ = next((int(k_.split("_")[1]) for k_ in knobs if k_.startswith("inlmask_")), None)
    def ovarg_(target_, n_, j_, text_, at_):
        if "noovcast" in knobs or at_ not in ("int", "long", "unsigned int", "unsigned long", "short", "unsigned short",
                                              "unsigned char", "signed char", "bool", "float", "void*"):
            return text_
        return f"\x01{target_:x}/{n_}/{j_}\x03{at_}\x03{text_}\x02"
    PTRRET_ = set()     # callees whose result is used as a pointer somewhere
    def want_inline(name, local_rts, rts):
        if not (name in used and use_count.get(name, 0) == 1 and local_rts == rts):
            return False
        if inl_mask_ is None:
            return "callinline" in knobs
        bit_ = inl_seen_[0]; inl_seen_[0] += 1
        return bool((inl_mask_ >> bit_) & 1)
    def var_refs(obj, acc_):
        if isinstance(obj, tuple):
            if len(obj) == 2 and obj[0] == "var" and isinstance(obj[1], str):
                acc_[obj[1]] = acc_.get(obj[1], 0) + 1
                return acc_
            for x_ in obj:
                var_refs(x_, acc_)
        elif isinstance(obj, list):
            for x_ in obj:
                var_refs(x_, acc_)
        return acc_
    all_refs_ = var_refs(items, {})
    index_cache_ = {}
    HALFB_ = {}
    def halve_body(items_, p_, half_):
        """(kept statements, offsets of the dropped twins) when every statement on p_ has a twin half_ further on."""
        def off_of(x_):
            return x_[3] if x_[0] == "let" else x_[2]
        def base_of(x_):
            return x_[4] if x_[0] == "let" else x_[3]
        if not items_ or any(x_[0] not in ("let", "store") or len(x_) != 5 or base_of(x_) != ("var", p_) for x_ in items_):
            return None
        used_, pairs_ = set(), []
        for i_, x_ in enumerate(items_):
            if i_ in used_:
                continue
            j_ = next((j_ for j_, y_ in enumerate(items_) if j_ not in used_ and j_ != i_ and y_[0] == x_[0] and y_[1 if x_[0] == "store" else 2] == x_[1 if x_[0] == "store" else 2]
                       and off_of(y_) == off_of(x_) + half_), None)
            if j_ is None:
                return None
            used_ |= {i_, j_}; pairs_.append((i_, j_))
        mp_ = {items_[i_][1]: items_[j_][1] for i_, j_ in pairs_ if items_[i_][0] == "let"}
        def same(a_, b_):
            if isinstance(a_, tuple) and isinstance(b_, tuple):
                if len(a_) == 2 and a_[0] == "var" and b_[0] == "var":
                    return mp_.get(a_[1], a_[1]) == b_[1]
                return len(a_) == len(b_) and all(same(x_, y_) for x_, y_ in zip(a_, b_))
            return a_ == b_
        for i_, j_ in pairs_:
            if items_[i_][0] == "store" and not same(items_[i_][4], items_[j_][4]):
                return None
        low_ = {i_ for i_, j_ in pairs_}
        for i_, j_ in pairs_:
            if items_[j_][0] == "let" and all_refs_.get(items_[j_][1], 0) != var_refs(items_, {}).get(items_[j_][1], 0):
                return None
        return [items_[i_] for i_ in range(len(items_)) if i_ in low_], {off_of(items_[j_]) for i_, j_ in pairs_}
    def index_form(it):
        key_ = id(it)
        if key_ in index_cache_:
            return index_cache_[key_]
        index_cache_[key_] = None
        _, inits, body, updates, cnd, pre = it
        upd = dict(updates)
        initv = {n_: v_ for n_, v_, r_ in inits}
        in_loop_refs = var_refs((body, updates, cnd), {})
        def step_of(n_):
            nv_ = upd.get(n_)
            if nv_ is not None and nv_[0] == "bin" and nv_[1] in ("+", "-") and nv_[2] == ("var", n_) and nv_[3][0] == "const":
                return nv_[3][1] if nv_[1] == "+" else -nv_[3][1]
            return None
        def pointer_init(v_):
            try:
                return vtype(v_).endswith("*")
            except Fail:
                return False
        ptrs = [n_ for n_ in initv if step_of(n_) and step_of(n_) > 0 and (n_ in loopelem or pointer_init(initv[n_]))]
        if not ptrs or pre:
            return None
        for p_ in ptrs:
            if all_refs_.get(p_, 0) != in_loop_refs.get(p_, 0):
                return None
        for p_ in ptrs:
            if p_ not in loopelem:
                loopelem[p_] = f"Elem{a:x}_{p_}"
                structs[loopelem[p_]] = {}
        halved_ = None
        if len(ptrs) == 1 and "nounroll" not in knobs:
            p_ = ptrs[0]; S_ = step_of(p_)
            (fk0, fx0, fy0, fw0), cc0 = cnd
            ctr_ = next((n_ for n_ in initv if n_ != p_ and initv[n_][0] == "const" and initv[n_][1] > 0 and step_of(n_) == -2
                         and fk0 == "cmp" and fx0 == ("var", n_) and fy0[0] == "const" and fy0[1] == 0 and cc0 == "ne"), None)
            if ctr_ is not None and S_ % 2 == 0:
                hb_ = halve_body(body, p_, S_ // 2)
                if hb_ is not None:
                    keep_, dropped_offs_ = hb_
                    halved_ = (keep_, S_ // 2, initv[ctr_][1], ctr_)
                    for o_ in dropped_offs_:
                        structs[loopelem[p_]].pop(o_, None)
                    HALFB_[key_] = keep_
        def step_of(n_, _orig=step_of):
            if halved_ is not None and n_ == ptrs[0]:
                return halved_[1]
            if halved_ is not None and n_ == halved_[3]:
                return -1
            return _orig(n_)
        for p_ in ptrs:
            st_ = step_of(p_)
            offs_ = list(structs[loopelem[p_]])
            if offs_ and min(offs_) >= st_ and p_ not in ESHIFT_:
                h_ = (min(offs_) // st_) * st_
                if "arrmember" in knobs:
                    h_ = min(offs_)
                    if max(o_ + SIZE.get(structs[loopelem[p_]][o_][0], 8) for o_ in offs_) - h_ > st_:
                        h_ = (min(offs_) // st_) * st_
                ESHIFT_[p_] = h_
        if not ptrs or pre:
            return None
        for p_ in ptrs:
            # the pointer must not be needed after the loop
            if all_refs_.get(p_, 0) != in_loop_refs.get(p_, 0):
                return None
            elemsize[p_] = step_of(p_)
        others = [n_ for n_ in initv if n_ not in ptrs]
        ix, newix, drop, cnd2 = None, False, set(), cnd
        for n_ in others:
            v_ = initv[n_]
            if v_[0] == "const" and v_[1] == 0 and step_of(n_) == 1:
                ix = n_; break
        (fk, fx, fy, fw_), cc = cnd
        if ix is None:
            newix = True
            ix = f"i{counter[0]}"; counter[0] += 1
            vars_[ix] = "long"
            # a down-counter tested against zero
            for n_ in others:
                v_ = initv[n_]
                k_ = -(step_of(n_) or 0)
                if v_[0] == "const" and v_[1] > 0 and k_ > 0 and v_[1] % k_ == 0 and fk == "cmp" and fx == ("var", n_) and fy[0] == "const" \
                        and fy[1] == 0 and cc == "ne" and in_loop_refs.get(n_, 0) == 2 and all_refs_.get(n_, 0) == 2:
                    drop.add(n_)
                    cnd2 = (("cmp", ("var", ix), ("const", v_[1] // k_, "x"), "x"), "ne")
                    break
            else:
                # the pointer tested against an end address a whole number of elements away
                def lin2_(e_):
                    s_ = 0
                    while e_[0] == "bin" and e_[1] == "+" and e_[3][0] == "const":
                        s_ += e_[3][1]; e_ = e_[2]
                    return e_, s_
                for p_ in ptrs:
                    cx_, sx_ = lin2_(fx) if fk == "cmp" else (None, 0)
                    if cx_ == ("var", p_) and cc == "ne":
                        e_, s_ = lin2_(fy)
                        k_ = s_ - sx_
                        if e_ == initv[p_] and k_ > 0 and k_ % step_of(p_) == 0:
                            cnd2 = (("cmp", ("var", ix), ("const", k_ // step_of(p_), "x"), "x"), "ne")
                            break
                else:
                    return None
        index_cache_[key_] = (ptrs, ix, newix, drop, cnd2)
        return index_cache_[key_]
    hoist_stack = []
    blk_types_ = set()
    zero_types_ = set()
    def declare_line(pad, typ, name, rhs):
        if hoist_stack:
            hoist_stack[-1].append((typ, name))
            return f"{pad}{name} = {rhs};"
        return f"{pad}{typ} {name} = {rhs};"
    MORE_ = []
    class RetHoist_(list):
        pass
    def ends_in_return_(its_):
        if not its_:
            return False
        l_ = its_[-1]
        if l_[0] == "return" or (l_[0] == "call" and l_[4]):
            return True
        if l_[0] == "diamond":
            return ends_in_return_(l_[3]) and ends_in_return_(l_[4])
        return False
    def unhoist_(ls_):
        out_ = list(ls_)
        k_ = 0
        while k_ < len(out_):
            l_ = out_[k_]
            if "\x04" not in l_:
                k_ += 1
                continue
            pad_, rest_ = l_.split("\x04")
            typ_, name_ = rest_.split("\x05")
            if_ = k_ + 1
            while "\x04" in out_[if_]:
                if_ += 1
            end_ = next((j_ for j_ in range(if_ + 1, len(out_)) if out_[j_] == pad_ + "}"), None)
            if end_ is None:
                raise Fail("hoisted diamond end")
            if any(re.search(rf"\b{name_}\b", x_) for x_ in out_[end_ + 1:]):
                out_[k_] = f"{pad_}{typ_} {name_};"
                k_ += 1
                continue
            for j_ in range(if_, end_):
                mm_ = re.match(rf"^(\s*){name_} = ", out_[j_])
                if mm_:
                    out_[j_] = f"{mm_.group(1)}{typ_} {out_[j_][len(mm_.group(1)):]}"
                    break
            del out_[k_]
        return out_
    def has_cont_(its_):
        for it_ in its_:
            if it_[0] == "contassign":
                return True
            if it_[0] == "if" and has_cont_(it_[2]):
                return True
            if it_[0] == "diamond" and (has_cont_(it_[3]) or has_cont_(it_[4])):
                return True
        return False
    def render(its, indent):
        outl = []
        pad = "    " * indent
        for it in its:
            if it[0] == "let" and it[1] in skip_lets:
                continue
            if it[0] == "vcall":
                _, name, objsn, slot, obj, args, tail = it
                atypes = [vtype(x) for x in args]
                rts = "void"
                rt = vars_[name]
                if name in used or tail:
                    if tail:
                        rts = rtype
                    elif isinstance(rt, str) and rt in structs:
                        rts = f"{rt}*"
                    else:
                        rts = {"w": "int", "x": "void*", "?": "int", "f": "float"}.get(rt, rt)
                atypes = ["void*" if x.endswith("*") else x for x in atypes]
                if "nosextarg" not in knobs:
                    atypes = ["int" if x_ in ("short", "signed char") else x_ for x_ in atypes]
                local_rts = rts
                rts = "void*" if rts.endswith("*") else rts
                if objsn is None:
                    calltext = f"reinterpret_cast<{rts} (*)({', '.join(atypes)})>({expr(obj)})({', '.join(expr(x) for x in args)})"
                else:
                    prev = vslots.setdefault(objsn, {}).get(slot)
                    if prev and prev != (atypes, rts):
                        raise Fail("slot signature")
                    vslots[objsn][slot] = (atypes, rts)
                    calltext = f"{expr(obj)}->slot_{slot}({', '.join(expr(x) for x in args)})"
                if tail:
                    outl.append(f"{pad}{'return ' if rtype != 'void' else ''}{calltext};")
                elif want_inline(name, local_rts, rts):
                    inline_map[name] = calltext
                elif name in used and local_rts != rts:
                    outl.append(declare_line(pad, local_rts, name, f"static_cast<{local_rts}>({calltext})"))
                elif name in used:
                    outl.append(declare_line(pad, rts, name, f"{calltext}"))
                else:
                    outl.append(f"{pad}{calltext};")
                continue
            if it[0] == "return" and it[1] is not None and it[1][0] == "var" and any(x[0] == "vcall" and x[1] == it[1][1] and x[6] for x in its):
                continue
            if it[0] == "leti" and len(it) > 6:
                _, name, sn, off, base, iv, wt = it
                bp_ = acc(base, off) if structs[sn].get(off, ("",))[0] == "ARRAY:unsigned char" else f"reinterpret_cast<unsigned char*>(&{acc(base, off)})"
                outl.append(declare_line(pad, wt, name, f"*reinterpret_cast<{wt}*>(&{bp_}[{iexpr_(iv)}])") if "declare_line" in dir() else f"{pad}{wt} {name} = *reinterpret_cast<{wt}*>(&{bp_}[{iexpr_(iv)}]);")
                continue
            if it[0] == "storei" and len(it) > 6:
                _, sn, off, base, iv, val, wt = it
                bp_ = acc(base, off) if structs[sn].get(off, ("",))[0] == "ARRAY:unsigned char" else f"reinterpret_cast<unsigned char*>(&{acc(base, off)})"
                outl.append(f"{pad}*reinterpret_cast<{wt}*>(&{bp_}[{iexpr_(iv)}]) = {fit(expr(val), vtype(val), wt)};")
                continue
            if it[0] == "leti":
                _, name, sn, off, base, iv = it[:6]
                if (sn, off) in arr_scalar_:
                    el_ = arr_scalar_[(sn, off)]
                    outl.append(declare_line(pad, el_, name, f"reinterpret_cast<{el_}*>(&{acc(base, off)})[{iexpr_(iv)}]"))
                    continue
                outl.append(declare_line(pad, ftype(sn, off), name, f"{acc(base, off)}[{iexpr_(iv)}]"))
                continue
            if it[0] == "storei":
                _, sn, off, base, iv, val = it[:6]
                if (sn, off) in arr_scalar_:
                    el_ = arr_scalar_[(sn, off)]
                    outl.append(f"{pad}reinterpret_cast<{el_}*>(&{acc(base, off)})[{iexpr_(iv)}] = {fit(expr(val), vtype(val), el_)};")
                    continue
                outl.append(f"{pad}{acc(base, off)}[{iexpr_(iv)}] = {fit(expr(val), vtype(val), ftype(sn, off))};")
                continue
            if it[0] == "let" and "sink" in knobs and use_count.get(it[1], 0) == 1 and not (isinstance(vars_[it[1]], str) and vars_[it[1]] in structs) \
                    and not ("dstfirst" in knobs and it[1] in store_dsts_()):
                lt0 = vars_[it[1]]
                if not (isinstance(lt0, tuple) and len(lt0) > 3 and lt0[3] != ftype(it[2], it[3])):
                    inline_map[it[1]] = acc(it[4], it[3])
                    continue
            if it[0] == "let" and vu_of_(it[2], it[3]) is not None:
                _, name, sn, off, base = it
                u_ = vu_of_(sn, off)
                lt_ = vars_[name]
                ty_ = lt_[3] if isinstance(lt_, tuple) and len(lt_) > 3 else structs[sn][off][0]
                view_, vt_ = vu_view_(ty_, off - u_)
                rhs_ = f"{acc(base, u_)}.{view_}"
                outl.append(declare_line(pad, ty_, name, rhs_ if ty_ == vt_ or ty_ == "unsigned int" else fit(rhs_, vt_, ty_)))
                continue
            if it[0] == "let":
                _, name, sn, off, base = it
                t = ftype(sn, off)
                lt_ = vars_[name]
                if isinstance(lt_, tuple) and len(lt_) > 3 and lt_[3] != t and t in ("int", "unsigned int", "float") and lt_[3] in ("int", "unsigned int", "float") and "float" in (t, lt_[3]):
                    outl.append(declare_line(pad, lt_[3], name, f"*reinterpret_cast<{lt_[3]}*>(&{acc(base, off)})"))
                    continue
                if isinstance(lt_, tuple) and len(lt_) > 3 and lt_[3] != t and not t.endswith("*") or (isinstance(lt_, tuple) and len(lt_) > 3 and lt_[3] == "long" and t == "void*"):
                    want = lt_[3]
                    outl.append(declare_line(pad, want, name, f"{fit(acc(base, off), t, want)}"))
                    continue
                if isinstance(vars_[name], str) and vars_[name] in structs:
                    t = f"{vars_[name]}*"
                    outl.append(declare_line(pad, t, name, f"{fit(acc(base, off), ftype(sn, off), t)}"))
                else:
                    outl.append(declare_line(pad, t, name, f"{acc(base, off)}"))
            elif it[0] == "bfstore":
                _, sn, off, base, val, s_, w_ = it
                a_ = acc(base, off)
                nm_ = f"field_{off:x}"
                if not a_.endswith(nm_):
                    raise Fail("bitfield access")
                outl.append(f"{pad}{a_[:-len(nm_)]}bf{off:x}_{s_} = {expr(val)};")
            elif it[0] == "copy8":
                def byte_addr_(b_, o_):
                    if b_[0] == "stackobj":
                        bs_ = f"&local_{hx_(b_[1])}"
                    elif b_[0] in ("param", "var", "gotaddr", "local"):
                        bs_ = expr(b_)
                    elif b_[0] in ("bin", "stackaddr", "elem", "maddr", "select", "ext"):
                        bs_ = expr(b_)
                    else:
                        raise Fail("copy base")
                    return f"reinterpret_cast<unsigned char*>({bs_}) + {o_:#x}" if o_ else f"reinterpret_cast<unsigned char*>({bs_})"
                outl.append(f"{pad}__builtin_memcpy({byte_addr_(it[1], it[2])}, {byte_addr_(it[3], it[4])}, 8);")
            elif it[0] == "valinit":
                _, dv_, n_, v_ = it
                db_ = f"reinterpret_cast<unsigned char*>({expr(dv_)})"
                if v_ == 0 and "zeroloop" in knobs:
                    outl.append(f"{pad}for (int i = 0; i < {n_:#x}; i++) {db_}[i] = 0;")
                elif v_ == 0:
                    zero_types_.add(n_)
                    outl.append(f"{pad}*reinterpret_cast<Zero{n_:x}_{a:x}*>({db_}) = Zero{n_:x}_{a:x}{{}};")
                else:
                    outl.append(f"{pad}for (long i = 0; i < {n_:#x}; ++i) {db_}[i] = {v_:#x};")
            elif it[0] == "blkcopy":
                _, dv_, dlo_, sv_, slo_, R_, n_, al_, st_ = it
                bn_ = f"Blk{R_:x}_{al_}_{a:x}"
                blk_types_.add((R_, al_))
                def baddr_(b_, o_):
                    bs_ = f"reinterpret_cast<unsigned char*>({expr(b_)})"
                    return f"({bs_} + {o_:#x})" if o_ else bs_
                if n_ == 1:
                    outl.append(f"{pad}*reinterpret_cast<{bn_}*>({baddr_(dv_, dlo_)}) = *reinterpret_cast<const {bn_}*>({baddr_(sv_, slo_)});")
                elif st_ != R_:
                    outl.append(f"{pad}for (long i = 0; i < {n_}; ++i) *reinterpret_cast<{bn_}*>({baddr_(dv_, dlo_)} + i * {st_:#x}) = *reinterpret_cast<const {bn_}*>({baddr_(sv_, slo_)} + i * {st_:#x});")
                else:
                    outl.append(f"{pad}for (long i = 0; i < {n_}; ++i) reinterpret_cast<{bn_}*>({baddr_(dv_, dlo_)})[i] = reinterpret_cast<const {bn_}*>({baddr_(sv_, slo_)})[i];")
            elif it[0] == "store" and vu_of_(it[1], it[2]) is not None:
                _, sn, off, base, val = it
                u_ = vu_of_(sn, off)
                vt0_ = vtype(val)
                view_, want_ = vu_view_("Vec4f" if vt0_ == "Vec4f" else ("float" if vt0_ == "float" else ("long" if vt0_ in ("long", "void*") or vt0_.endswith("*") else "int")), off - u_)
                outl.append(f"{pad}{acc(base, u_)}.{view_} = {fit(expr(val), vt0_, want_)};")
            elif it[0] == "store":
                _, sn, off, base, val = it
                vt_, ft_ = vtype(val), ftype(sn, off)
                if vt_ != ft_ and vt_ in ("int", "unsigned int", "float") and ft_ in ("int", "unsigned int", "float") and "float" in (vt_, ft_) and not (val[0] == "const" and val[1] == 0):
                    outl.append(f"{pad}*reinterpret_cast<{vt_}*>(&{acc(base, off)}) = {expr(val)};")
                    continue
                outl.append(f"{pad}{acc(base, off)} = {fit(expr(val), vt_, ft_)};")
            elif it[0] == "call":
                _, name, target, args, tail = it
                args = [member_arg(x_) for x_ in args]
                cname = f"callee_{target:x}"
                imp_ = import_of(target)
                atypes = [vtype(x) for x in args]
                rt = vars_[name]
                rts = "void"
                if name in PAIRS_:
                    if tail or imp_:
                        raise Fail("pair return")
                    rt = "Pair16"
                if name in used or tail:
                    if tail:
                        rts = rtype
                    elif isinstance(rt, str) and rt in structs:
                        rts = f"{rt}*"
                    else:
                        rts = {"w": "int", "x": "void*", "?": "int", "f": "float"}.get(rt, rt)
                atypes = ["void*" if x.endswith("*") else x for x in atypes]
                if "nosextarg" not in knobs:
                    atypes = ["int" if x_ in ("short", "signed char") else x_ for x_ in atypes]
                local_rts = rts
                rts = "void*" if rts.endswith("*") else rts
                if target in PTRRET_ and rts == "int" and rt in ("?", "w") and not tail and not imp_:
                    rts = "void*"
                ov_ = over_.setdefault(target, {})
                pr_ = ov_.get(tuple(atypes))
                if pr_ is not None and pr_ != rts:
                    if rts == "void":
                        rts = pr_
                    elif pr_ != "void":
                        raise Fail("callee ret")
                if imp_ and ov_ and tuple(atypes) not in ov_:
                    raise Fail("callee types")
                ov_[tuple(atypes)] = rts
                callees[target][1] = (atypes, rts)
                argtext = ", ".join(ovarg_(target, len(args), j_, expr(x), at_) for j_, (x, at_) in enumerate(zip(args, atypes)))
                if imp_:
                    kind_, mangled_, qname_, iret_, iparams_ = imp_[0], imp_[1], imp_[2], imp_[3], imp_[4]
                    if len(iparams_) != len(args):
                        raise Fail("import arity")
                    cname = qname_
                    argtext = ", ".join(fit(expr(x), vtype(x), pt) if not pt.endswith("*") or vtype(x).endswith("*") or vtype(x) in ("long", "int")
                                        else expr(x) for x, pt in zip(args, iparams_))
                    argtext = ", ".join(
                        (f"reinterpret_cast<{pt}>({expr(x)})" if pt.endswith("*") and vtype(x) in ("long",) else
                         (f"{'static' if vtype(x) == 'void*' else 'reinterpret'}_cast<{pt}>({expr(x)})" if pt.endswith("*") and vtype(x).endswith("*") and pt != vtype(x)
                          and ("const" not in pt or ("noconstarg" not in knobs and not vtype(x).startswith("const"))) else
                          (expr(x) if pt.endswith("*") else fit(expr(x), vtype(x), pt))))
                        for x, pt in zip(args, iparams_))
                    used_imports.add(mangled_)
                    if name in used and iret_ == "void":
                        raise Fail("void import used")
                if tail:
                    continue
                if want_inline(name, local_rts, rts):
                    inline_map[name] = f"{cname}({argtext})"
                    continue
                if name in used:
                    if local_rts != rts and rts == "void*" and local_rts == "int":
                        outl.append(declare_line(pad, local_rts, name, f"static_cast<int>(reinterpret_cast<long>({cname}({argtext})))"))
                    elif local_rts != rts:
                        outl.append(declare_line(pad, local_rts, name, f"static_cast<{local_rts}>({cname}({argtext}))"))
                    else:
                        outl.append(declare_line(pad, rts, name, f"{cname}({argtext})"))
                else:
                    outl.append(f"{pad}{cname}({argtext});")
            elif it[0] == "return":
                v = it[1]
                if v is None:
                    outl.append(f"{pad}return;")
                elif v[0] == "var" and any(x[0] == "call" and x[1] == v[1] and x[4] for x in its):
                    call_it = next(x for x in its if x[0] == "call" and x[1] == v[1])
                    tat_ = ["void*" if vtype(member_arg(x)).endswith("*") else vtype(member_arg(x)) for x in call_it[3]]
                    if "nosextarg" not in knobs:
                        tat_ = ["int" if x_ in ("short", "signed char") else x_ for x_ in tat_]
                    argtext = ", ".join(ovarg_(call_it[2], len(tat_), j_, expr(member_arg(x)), at_)
                                        for j_, (x, at_) in enumerate(zip(call_it[3], tat_)))
                    pre = "return " if rtype != "void" else ""
                    if import_of(call_it[2]):
                        raise Fail("import tail call")
                    outl.append(f"{pad}{pre}callee_{call_it[2]:x}({argtext});")
                else:
                    outl.append(f"{pad}return {fit(expr(v), vtype(v), rtype)};")
            elif it[0] == "if" and it[1][1] == "switch":
                outl.append(f"{pad}switch ({expr(it[1][0][1], False)}) {{")
                segs_ = []
                for x_ in it[2]:
                    if x_[0] == "case":
                        segs_.append((x_[1], []))
                    else:
                        segs_[-1][1].append(x_)
                for labels_, its_ in segs_:
                    heads_ = [f"case {v_}:" for v_ in labels_] if labels_ is not None else ["default:"]
                    for h_ in heads_[:-1]:
                        outl.append(f"{pad}{h_}")
                    outl.append(f"{pad}{heads_[-1]} {{")
                    outl.extend(render(its_, indent + 1))
                    outl.append(f"{pad}}}")
                outl.append(f"{pad}}}")
            elif it[0] == "if":
                outl.append(f"{pad}if ({cond(*it[1])}) {{")
                outl.extend(render(it[2], indent + 1))
                outl.append(f"{pad}}}")
            elif it[0] == "diamond":
                _, cnd, decls_, taken_its, fall_its = it
                for name, v in decls_:
                    if hoist_stack and not isinstance(hoist_stack[-1], RetHoist_):
                        # declared in front of the enclosing loop, so the value is still in scope after it
                        hoist_stack[-1].append((vtype(('var', name)), name))
                    else:
                        outl.append(f"{pad}{vtype(('var', name))} {name};")
                f_, cc_ = cnd
                if cc_ not in NEGCC:
                    raise Fail("negate")
                hoist_ = ("nohoistret" not in knobs and not hoist_stack and taken_its
                          and (ends_in_return_(fall_its) or ends_in_return_(taken_its)))
                if_at_ = len(outl)
                if hoist_:
                    hoist_stack.append(RetHoist_())
                if f_ is not None and f_[0] == "ccmp":
                    outl.append(f"{pad}if (!({cond(f_, cc_)})) {{")
                else:
                    outl.append(f"{pad}if ({cond(f_, NEGCC[cc_])}) {{")
                outl.extend(render(fall_its, indent + 1))
                if taken_its:
                    outl.append(f"{pad}}} else {{")
                    outl.extend(render(taken_its, indent + 1))
                outl.append(f"{pad}}}")
                if hoist_:
                    outl[if_at_:if_at_] = [f"{pad}\x04{typ}\x05{name}" for typ, name in hoist_stack.pop()]
            elif it[0] == "spin":
                _, sn, off, base, val, w_ = it
                ft_ = ftype(sn, off)
                want_ = "long" if w_ == "x" else "int"
                ptr_ = f"&{acc(base, off)}" if ft_ == want_ else f"reinterpret_cast<{want_}*>(&{acc(base, off)})"
                outl.append(f"{pad}while (!__sync_bool_compare_and_swap({ptr_}, 0, {fit(expr(val), vtype(val), want_)})) {{")
                outl.append(f"{pad}}}")
            elif it[0] == "contassign":
                if len(it[1]) > 1:
                    for n_, v_ in it[1]:
                        outl.append(f"{pad}{vtype(('var', n_))} next_{n_} = {fit(expr(v_), vtype(v_), vtype(('var', n_)))};")
                    for n_, v_ in it[1]:
                        outl.append(f"{pad}{n_} = next_{n_};")
                else:
                    for n_, v_ in it[1]:
                        outl.append(f"{pad}{n_} = {fit(expr(v_), vtype(v_), vtype(('var', n_)))};")
                outl.append(f"{pad}continue;")
            elif it[0] == "loop" and "ptrloop" not in knobs and not has_cont_(it[2]) and index_form(it) is not None:
                _, inits, body, updates, cnd, pre = it
                ptrs_, ix_, newix_, drop_, cnd2_ = index_form(it)
                body = HALFB_.get(id(it), body)
                for name, v, r in inits:
                    if name in drop_:
                        continue
                    if name in ptrs_:
                        if "arrmember" in knobs and ESHIFT_.get(name) and v[0] in ("param", "var"):
                            try:
                                osn_ = struct_for(v)
                            except Fail:
                                osn_ = None
                            h_ = ESHIFT_[name]
                            if osn_ is not None and structs[osn_].get(h_, ("ARRAY:" + loopelem[name], None))[0] == "ARRAY:" + loopelem[name]:
                                structs[osn_][h_] = ("ARRAY:" + loopelem[name], None)
                                SIZE[loopelem[name]] = elemsize[name]
                                outl.append(f"{pad}{loopelem[name]}* {name} = {expr(v)}->field_{h_:x};")
                                continue
                        v_ = ("bin", "+", v, ("const", ESHIFT_[name], "x"), "x", "add") if ESHIFT_.get(name) else v
                        outl.append(f"{pad}{loopelem[name]}* {name} = {fit(expr(v_), vtype(v_), loopelem[name] + '*')};")
                    else:
                        outl.append(f"{pad}{'unsigned int' if name in UINTLOOP_ else vtype(v)} {name} = {expr(v)};")
                if newix_:
                    outl.append(f"{pad}long {ix_} = 0;")
                for p_ in ptrs_:
                    IDX_[p_] = ix_
                hoist_stack.append([])
                body_lines = render(body, indent + 1)
                hoisted = hoist_stack.pop()
                for typ, name in hoisted:
                    outl.append(f"{pad}{typ} {name};")
                # the condition computed before the updates lives outside the body: a name declared in a do body is
                # not in scope in its while
                mn_ = f"more{len(MORE_)}"
                if pre:
                    MORE_.append(mn_)
                    outl.append(f"{pad}bool {mn_};")
                outl.append(f"{pad}do {{")
                outl.extend(body_lines)
                inner = "    " * (indent + 1)
                ups_ = [(n_, nv_) for n_, nv_ in updates if n_ not in ptrs_ and n_ not in drop_]
                if newix_:
                    ups_.append((ix_, None))
                if pre:
                    outl.append(f"{inner}{mn_} = {cond(*cnd2_)};")
                def upd2_(name, nv):
                    if nv is None:
                        return f"{name} + 1"
                    return fit(expr(nv), vtype(nv), vtype(('var', name)))
                if len(ups_) > 1:
                    for name, nv in ups_:
                        outl.append(f"{inner}{'long' if nv is None else vtype(('var', name))} next_{name} = {upd2_(name, nv)};")
                    for name, nv in ups_:
                        outl.append(f"{inner}{name} = next_{name};")
                else:
                    for name, nv in ups_:
                        outl.append(f"{inner}{name} = {upd2_(name, nv)};")
                outl.append(f"{pad}}} while ({mn_ if pre else cond(*cnd2_)});")
                for p_ in ptrs_:
                    IDX_.pop(p_, None)
            elif it[0] == "loop":
                _, inits, body, updates, cnd, pre = it
                for name, nv in updates:
                    if name in loopelem and nv[0] == "bin" and nv[1] == "+" and nv[2] == ("var", name) and nv[3][0] == "const" and nv[3][1] > 0:
                        offs_ = list(structs[loopelem[name]])
                        if offs_ and min(offs_) >= nv[3][1] and name not in ESHIFT_:
                            ESHIFT_[name] = (min(offs_) // nv[3][1]) * nv[3][1]
                for name, v, r in inits:
                    if name in loopelem and ESHIFT_.get(name):
                        v_ = ("bin", "+", v, ("const", ESHIFT_[name], "x"), "x", "add")
                        outl.append(f"{pad}{loopelem[name]}* {name} = {fit(expr(v_), vtype(v_), loopelem[name] + '*')};")
                        continue
                    if name in loopelem:
                        outl.append(f"{pad}{loopelem[name]}* {name} = {fit(expr(v), vtype(v), loopelem[name] + '*')};")
                    else:
                        outl.append(f"{pad}{'unsigned int' if name in UINTLOOP_ else vtype(v)} {name} = {expr(v)};")
                hoist_stack.append([])
                body_lines = render(body, indent + 1)
                hoisted = hoist_stack.pop()
                for typ, name in hoisted:
                    outl.append(f"{pad}{typ} {name};")
                mn_ = f"more{len(MORE_)}"
                if pre:
                    MORE_.append(mn_)
                    outl.append(f"{pad}bool {mn_};")
                do_at_ = len(outl)
                outl.append(f"{pad}do {{")
                outl.extend(body_lines)
                inner = "    " * (indent + 1)
                if pre:
                    outl.append(f"{inner}{mn_} = {cond(*cnd)};")
                def upd_text(name, nv):
                    if name in loopelem:
                        if not (nv[0] == "bin" and nv[1] == "+" and nv[2] == ("var", name) and nv[3][0] == "const"):
                            raise Fail("pointer step")
                        elemsize[name] = nv[3][1]
                        return f"{name} + 1"
                    return fit(expr(nv), vtype(nv), vtype(('var', name)))
                if len(updates) > 1:
                    for name, nv in updates:
                        outl.append(f"{inner}{vtype(('var', name))} next_{name} = {upd_text(name, nv)};")
                    for name, nv in updates:
                        outl.append(f"{inner}{name} = next_{name};")
                else:
                    for name, nv in updates:
                        outl.append(f"{inner}{name} = {upd_text(name, nv)};")
                if has_cont_(body):
                    # continues jump straight back to the header: for (;;) with the condition at the bottom
                    outl[do_at_] = f"{pad}for (;;) {{"
                    outl.append(f"{inner}if (!({mn_ if pre else cond(*cnd)})) {{")
                    outl.append(f"{inner}    break;")
                    outl.append(f"{inner}}}")
                    outl.append(f"{pad}}}")
                else:
                    outl.append(f"{pad}}} while ({mn_ if pre else cond(*cnd)});")
            elif it[0] == "lete":
                outl.append(declare_line(pad, vtype(it[2]), it[1], expr(it[2])))
            elif it[0] == "assign":
                _, name, v = it
                outl.append(f"{pad}{name} = {fit(expr(v), vtype(v), vtype(('var', name)))};")
        return outl
    def reverse_runs(its):
        out_, run = [], []
        for it in its:
            if it[0] == "store":
                run.append(it); continue
            out_.extend(reversed(run)); run = []
            if it[0] == "if":
                it = ("if", it[1], reverse_runs(it[2]))
            elif it[0] == "diamond":
                it = (it[0], it[1], it[2], reverse_runs(it[3]), reverse_runs(it[4]))
            out_.append(it)
        out_.extend(reversed(run))
        return out_
    if "revstores" in knobs:
        items[:] = reverse_runs(items)
    def vptr_first(its):
        def is_vp_(v_):
            return v_[0] == "bin" and v_[1] == "+" and v_[2][0] == "gotaddr" and v_[3][0] == "const" and v_[3][1] == 0x10
        out_ = []
        for it in its:
            if it[0] == "if":
                it = ("if", it[1], vptr_first(it[2]))
            elif it[0] == "diamond":
                it = (it[0], it[1], it[2], vptr_first(it[3]), vptr_first(it[4]))
            elif it[0] == "loop":
                it = (it[0], it[1], vptr_first(it[2])) + tuple(it[3:])
            if it[0] == "store" and len(it) == 5 and is_vp_(it[4]):
                k_, j_ = len(out_), len(out_)
                while j_ > 0 and (out_[j_ - 1][0] == "lete" or (out_[j_ - 1][0] == "let" and out_[j_ - 1][4] == it[3]
                                                                 and out_[j_ - 1][2] == it[1] and out_[j_ - 1][3] >= it[2])):
                    j_ -= 1
                    if out_[j_][0] == "let":
                        k_ = j_
                out_.insert(k_, it)
                continue
            out_.append(it)
        return out_
    if "vptrfirst" in knobs:
        items[:] = vptr_first(items)
    def sort_runs(its):
        # knob 'sortstores': a run of plain stores is written in field order (member initialisers in declaration order)
        out_, run = [], []
        def is_vptr(v_):
            return v_[0] == "bin" and v_[1] == "+" and v_[2][0] == "gotaddr" and v_[3][0] == "const" and v_[3][1] == 0x10
        def flush():
            srt_ = sorted(run, key=lambda it_: (str(it_[3]), it_[2]))
            if "vptrlast" in knobs:
                # knob 'vptrlast': each embedded object's fields are set by its base before its vtable pointer
                grp_, cur_ = [], []
                for it_ in srt_:
                    if is_vptr(it_[4]) and cur_:
                        grp_.append(cur_); cur_ = []
                    cur_.append(it_)
                if cur_:
                    grp_.append(cur_)
                srt_ = [x_ for g_ in grp_ for x_ in ((g_[1:] + g_[:1]) if is_vptr(g_[0][4]) else g_)]
            out_.extend(srt_)
            run.clear()
        for it in its:
            if it[0] == "store" and len(it) == 5:
                run.append(it); continue
            flush()
            if it[0] == "if":
                it = ("if", it[1], sort_runs(it[2]))
            elif it[0] == "diamond":
                it = (it[0], it[1], it[2], sort_runs(it[3]), sort_runs(it[4]))
            out_.append(it)
        flush()
        return out_
    if "sortstores" in knobs:
        items[:] = sort_runs(items)
    NEG_ = {"eq": "ne", "ne": "eq", "lt": "ge", "ge": "lt", "le": "gt", "gt": "le", "lo": "hs", "hs": "lo", "ls": "hi",
            "hi": "ls", "mi": "pl", "pl": "mi"}
    def ends_return(its):
        return bool(its) and its[-1][0] == "return"
    def swap_ifs(its):
        for idx_, it in enumerate(its):
            if it[0] == "if" and ends_return(it[2]) and ends_return(its[idx_ + 1:]) and it[1][1] in NEG_:
                rest = swap_ifs(its[idx_ + 1:])
                return its[:idx_] + [("if", (it[1][0], NEG_[it[1][1]]), rest)] + swap_ifs(it[2])
        return its
    if "swapif" in knobs:
        items[:] = swap_ifs(items)
    def has_global(v):
        if not isinstance(v, tuple):
            return False
        if v[0] in ("gotaddr", "local"):
            return True
        return any(has_global(x) for x in v[1:] if isinstance(x, tuple))
    def global_first(its):
        out_, run = [], []
        def flush():
            out_.extend([x for x in run if has_global(x[4])] + [x for x in run if not has_global(x[4])])
            run.clear()
        for it in its:
            if it[0] == "store":
                run.append(it); continue
            flush()
            if it[0] == "if":
                it = ("if", it[1], global_first(it[2]))
            elif it[0] == "diamond":
                it = (it[0], it[1], it[2], global_first(it[3]), global_first(it[4]))
            out_.append(it)
        flush()
        return out_
    if "globalfirst" in knobs:
        items[:] = global_first(items)
    def got_first(its):
        # GOT slots loaded before the first branch
        early_, pages_ = set(), {}
        for i_ in ins:
            mk_ = i_.mnemonic
            if mk_ in ("b", "br", "ret", "cbz", "cbnz", "tbz", "tbnz") or mk_.startswith("b."):
                break
            mm_ = re.fullmatch(r"(x\d+), #(0x[0-9a-f]+|\d+)", i_.op_str) if mk_ == "adrp" else None
            if mm_:
                pages_[mm_.group(1)] = int(mm_.group(2), 0)
                continue
            mm_ = re.fullmatch(r"(x\d+), \[(x\d+), #(0x[0-9a-f]+|\d+)\]", i_.op_str) if mk_ == "ldr" else None
            if mm_ and mm_.group(2) in pages_:
                early_.add(pages_[mm_.group(2)] + int(mm_.group(3), 0))
            for w_ in rw(i_)[1]:
                pages_.pop("x%d" % w_, None)
        if not early_:
            return its
        def reads_(x_, acc_):
            # global reads in item order, nested ones with the path of nested lists that holds them
            for it_ in x_:
                if it_[0] == "let" and isinstance(it_[4], tuple) and it_[4][0] == "gotaddr":
                    acc_.append((it_[4][1], it_))
                for sub_ in ((it_[2],) if it_[0] == "if" else (it_[3], it_[4]) if it_[0] == "diamond" else ()):
                    reads_(sub_, acc_)
            return acc_
        def drop_(x_, victim_):
            out2_ = []
            for it_ in x_:
                if it_ is victim_:
                    continue
                if it_[0] == "if":
                    it_ = ("if", it_[1], drop_(it_[2], victim_))
                elif it_[0] == "diamond":
                    it_ = (it_[0], it_[1], it_[2], drop_(it_[3], victim_), drop_(it_[4], victim_))
                out2_.append(it_)
            return out2_
        out_, seen_ = [], set()
        for it in its:
            if it[0] == "let" and isinstance(it[4], tuple) and it[4][0] == "gotaddr":
                seen_.add(it[4][1])
            if it[0] in ("if", "diamond"):
                for g_, rd_ in reads_([it], []):
                    if g_ in early_ and g_ not in seen_:
                        seen_.add(g_)
                        it = drop_([it], rd_)[0]
                        # before the loads that feed the test too
                        k_ = len(out_)
                        while k_ > 0 and out_[k_ - 1][0] == "let" and not (isinstance(out_[k_ - 1][4], tuple) and out_[k_ - 1][4][0] == "gotaddr"):
                            k_ -= 1
                        out_.insert(k_, rd_)
            out_.append(it)
        return out_
    if "gotfirst" in knobs:
        items[:] = got_first(items)
    def scan_uint_(o):
        if isinstance(o, tuple):
            if (len(o) >= 3 and o[0] == "ext" and o[1] == "unsigned int" and isinstance(o[2], tuple) and o[2][0] == "var"
                    and isinstance(vars_.get(o[2][1]), tuple) and vars_[o[2][1]][0] == "loopvar"
                    and o[2][1] not in loopelem and vtype(vars_[o[2][1]][1]) == "int"):
                UINTLOOP_.add(o[2][1])
            for x_ in o:
                scan_uint_(x_)
        elif isinstance(o, list):
            for x_ in o:
                scan_uint_(x_)
    if "nouintloop" not in knobs:
        scan_uint_(items)
    NARROW_EXT_ = {"short": "short", "signed char": "signed char", "unsigned short": "unsigned short"}
    narrow_seen_ = {}
    def scan_narrow_(o):
        if isinstance(o, tuple):
            if len(o) >= 3 and o[0] == "ext" and o[1] in NARROW_EXT_ and isinstance(o[2], tuple):
                x_ = o[2]
                if x_[0] == "var" and vars_.get(x_[1]) in ("?", "w") and x_[1].startswith("c"):
                    narrow_seen_.setdefault(("v", x_[1]), set()).add(o[1])
                elif x_[0] == "param" and pwidth.get(x_[1]) in (None, "w"):
                    narrow_seen_.setdefault(("p", x_[1]), set()).add(o[1])
            for y_ in o:
                scan_narrow_(y_)
        elif isinstance(o, list):
            for y_ in o:
                scan_narrow_(y_)
    if "noshortidx" not in knobs:
        scan_narrow_(items)
        for (kind_, key_), tys_ in narrow_seen_.items():
            if len(tys_) != 1:
                continue
            ty_ = tys_.pop()
            if kind_ == "v":
                vars_[key_] = ty_
            else:
                pwidth[key_] = ty_
    def ptr_targets_(obj, acc_):
        if isinstance(obj, (list, tuple)):
            if (len(obj) == 5 and obj[0] == "call" and isinstance(obj[1], str) and isinstance(obj[2], int)
                    and obj[1] in used and (vars_.get(obj[1]) == "x" or vars_.get(obj[1]) in structs)):
                acc_.add(obj[2])
            for x_ in obj:
                ptr_targets_(x_, acc_)
    if "noretunify" not in knobs:
        ptr_targets_(items, PTRRET_)
    lines = render(items, 1)
    lines = unhoist_(lines)
    for p_, h_ in ESHIFT_.items():
        structs[loopelem[p_]] = {o_ - h_: v_ for o_, v_ in structs[loopelem[p_]].items()}
    decl_lines = []
    # clang 3.9 gives the first declared local the highest address: stackdesc declares them from the top down
    for st in sorted(stackobjs, reverse="stackdesc" in knobs):
        sn = stackobjs[st]
        if set(structs[sn]) == {0} and sn not in stack_min_:
            decl_lines.append(f"    {structs[sn][0][0]} local_{hx_(st)};")
        else:
            decl_lines.append(f"    {sn} local_{hx_(st)};")
    if sret_:
        decl_lines.insert(0, f"    {RETN_} r;")
    for k_ in sorted(UNDEF_, reverse=True):
        decl_lines.insert(0, f"    long u{k_};")
    for k_ in sorted(FUNDEF_, reverse=True):
        decl_lines.insert(0, f"    float uf{k_};")
    lines = decl_lines + lines
    if rtype == "void" and lines and lines[-1].strip() == "return;":
        lines.pop()
    order = []
    def visit(sn):
        for off, (ct, child) in sorted(structs[sn].items()):
            if child and child not in order:
                visit(child)
            if ct.startswith("ARRAY:") and ct[6:] in structs and ct[6:] not in order:
                visit(ct[6:])
        if sn not in order:
            order.append(sn)
    for sn in list(structs):
        visit(sn)
    sdefs, gdecls, gsyms = [], [], []
    for sn, v in gobjs.items():
        fields = structs[sn]
        hidden = ' __attribute__((visibility("hidden")))' if v[0] == "local" else ""
        sym = f"{'got:' if v[0] == 'gotaddr' else ''}g{sn}=0x71{v[1]:08x}"
        note = f"// Reached through the GOT slot at 0x71{v[1]:08x}.\n" if v[0] == "gotaddr" else ""
        tail = "" if v[0] == "gotaddr" else f"{' ' * 4}// 0x71{v[1]:08x}"
        if not fields:
            gdecls.append(f"{note}extern unsigned char g{sn}[]{hidden};{tail}")
        elif set(fields) == {0} and fields[0][0].startswith("ARRAY:") and not fields[0][1]:
            gdecls.append(f"{note}extern {fields[0][0][6:]} g{sn}[]{hidden};{tail}")
        elif set(fields) == {0}:
            ct, child = fields[0]
            gdecls.append(f"{note}extern {child + '*' if child else ct} g{sn}{hidden};{tail}")
        else:
            gdecls.append(f"{note}extern {sn} g{sn}{hidden};{tail}")
        gsyms.append(sym)
    vol_fields_ = set()
    if "volstores" in knobs:
        for sn_, off_, sz_ in cstore1_:
            if any((sn_, off_ + sz_, s2_) in cstore1_ for s2_ in (1, 2, 4)) \
                    or any((sn_, off_ - s2_, s2_) in cstore1_ for s2_ in (1, 2, 4)):
                vol_fields_.add((sn_, off_))
    def pack_(ct_, off_):
        """The attribute that keeps a field of type ct_ at an offset its type is not aligned to."""
        sz_ = SIZE.get(ct_[6:] if ct_.startswith("ARRAY:") else ct_)
        if "nopackfield" in knobs or sz_ not in (2, 4, 8) or off_ % sz_ == 0:
            return ""
        return f" __attribute__((packed, aligned({off_ & -off_})))"
    for sn in order:
        if sn in gobjs and set(structs[sn]) <= {0}:
            continue
        if sn in stackobjs.values() and set(structs[sn]) <= {0} and sn not in stack_min_:
            continue
        if sn in elemsizes:
            fl, pos = [], 0
            for off, (ct, child) in sorted(structs[sn].items()):
                if off < pos:
                    raise Fail("overlap")
                if off > pos:
                    fl.append(f"    unsigned char pad{pos:x}[0x{off - pos:x}];")
                tt_ = (f"{child}*" if child else ct[6:]) if ct.startswith("ARRAY:") else (f"{child}*" if child else ct)
                fl.extend(bf_lines_(sn, off, tt_)) if (sn, off) in bitfields_ and tt_ in BFW_ and not ct.startswith("ARRAY:") else \
                    fl.append(f"    {tt_} field_{off:x}{'[1]' if ct.startswith('ARRAY:') else ''}{pack_(ct, off)};{' ' * max(1, 20 - len(tt_))}// +{off:x}")
                pos = off + SIZE[ct[6:] if ct.startswith("ARRAY:") else ct]
            if pos > elemsizes[sn]:
                raise Fail("element too small")
            if pos < elemsizes[sn]:
                fl.append(f"    unsigned char pad{pos:x}[0x{elemsizes[sn] - pos:x}];")
            sdefs.append(f"struct {sn} {{\n" + "\n".join(fl) + "\n};\n")
            continue
        if sn in vtables.values():
            continue
        if sn in vtables:
            slots = vslots.get(sn, {})
            top = max(slots) if slots else 0
            ml = []
            for k2 in range(top + 1):
                if k2 in slots:
                    at, rt2 = slots[k2]
                    ml.append(f"    virtual {rt2} slot_{k2}({', '.join(at)});")
                else:
                    ml.append(f"    virtual void slot_{k2}();")
            fl, pos = [], 8
            vu_end_ = -1
            for off, (ct, child) in sorted(structs[sn].items()):
                if off == 0:
                    continue
                if off < vu_end_:
                    continue
                if off < pos:
                    raise Fail("overlap")
                if off > pos:
                    fl.append(f"    unsigned char pad{pos:x}[0x{off - pos:x}];")
                if (sn, off) in vu_slots_:
                    fl.append(f"    VecU field_{off:x};               // +{off:x}")
                    pos = vu_end_ = off + 16
                    continue
                if ct.startswith("ARRAY:"):
                    et_ = f"{child}*" if child else ct[6:]
                    fl.append(f"    {et_} field_{off:x}[1]{pack_(ct, off)};{' ' * max(1, 17 - len(et_))}// +{off:x}")
                    pos = off + SIZE[ct[6:]]
                    continue
                t2 = f"{child}*" if child else ct
                if (sn, off) in vol_fields_:
                    t2 = "volatile " + t2
                fl.extend(bf_lines_(sn, off, t2)) if (sn, off) in bitfields_ and t2 in BFW_ else \
                    fl.append(f"    {t2} field_{off:x}{pack_(ct, off)};{' ' * max(1, 20 - len(t2))}// +{off:x}")
                pos = off + SIZE[ct]
            sdefs.append(f"class {sn} {{\npublic:\n" + "\n".join(ml) + ("\n\n" + "\n".join(fl) if fl else "") + "\n};\n")
            continue
        fl, pos = [], 0
        vu_end_ = -1
        for off, (ct, child) in sorted(structs[sn].items()):
            if off < vu_end_:
                continue
            if off < pos:
                raise Fail("overlap")
            if off > pos:
                fl.append(f"    unsigned char pad{pos:x}[0x{off - pos:x}];")
            if (sn, off) in vu_slots_:
                fl.append(f"    VecU field_{off:x}{pack_('Vec4f', off) if False else ''};               // +{off:x}")
                pos = vu_end_ = off + 16
                continue
            if ct.startswith("ARRAY:"):
                et_ = f"{child}*" if child else ct[6:]
                fl.append(f"    {et_} field_{off:x}[1]{pack_(ct, off)};{' ' * max(1, 17 - len(et_))}// +{off:x}")
                pos = off + SIZE[ct[6:]]
                continue
            t = f"{child}*" if child else ct
            if (sn, off) in vol_fields_:
                t = "volatile " + t
            fl.extend(bf_lines_(sn, off, t)) if (sn, off) in bitfields_ and t in BFW_ else \
                fl.append(f"    {t} field_{off:x}{pack_(ct, off)};{' ' * max(1, 20 - len(t))}// +{off:x}")
            pos = off + SIZE[ct]
        if sn in stack_min_ and pos < stack_min_[sn]:
            fl.append(f"    unsigned char pad{pos:x}[0x{stack_min_[sn] - pos:x}];")
            pos = stack_min_[sn]
        if "stackpad" in knobs and stackobjs and sn == stackobjs[max(stackobjs)]:
            local_ = None
            for i_ in ins[:8]:
                if i_.mnemonic == "sub" and i_.op_str.startswith("sp, sp, #"):
                    local_ = imm(i_.op_str.split(",")[2])
            st_ = max(stackobjs)
            if local_ is None or pos > local_ - st_:
                raise Fail("stack pad")
            if pos < local_ - st_:
                fl.append(f"    unsigned char pad{pos:x}[0x{local_ - st_ - pos:x}];")
        if sn in loopelem.values():
            nm = next(n for n, e in loopelem.items() if e == sn)
            size = elemsize.get(nm)
            if size is None or pos > size:
                raise Fail("element size")
            if pos < size:
                fl.append(f"    unsigned char pad{pos:x}[0x{size - pos:x}];")
        if sn == RETN_ and sret_:
            # a user-declared copy makes the type non-trivial, so it is returned through x8 whatever its size
            fl = [f"    {sn}() {{}}", f"    {sn}(const {sn}&);"] + fl
        al2_ = f"__attribute__((aligned({stack_al_[sn]}))) " if stack_al_.get(sn, 1) > 1 else ""
        sdefs.append(f"struct {al2_}{sn} {{\n" + "\n".join(fl) + "\n};\n")
    sigs = {}
    for t, (args, sig) in list(callees.items()):
        if import_of(t):
            continue
        if sig is None:
            raise Fail("unrendered callee")
        if fnames.get(t, "").startswith("<EXTERNAL>") and not import_of(t):
            raise Fail("library callee")
        for ak_, rt_ in over_.get(t, {tuple(sig[0]): sig[1]}).items():
            sigs[(t, ak_)] = (list(ak_), rt_)

    nparams = (max(pwidth) + 1) if pwidth else 0
    params = ", ".join([f"{ptype(n)} p{n}" for n in range(nparams) if pwidth.get(n) != "VecU_hi"] + [f"float f{n}" for n in range(max(fparams) + 1 if fparams else 0)])
    sdefs += [f"struct alignas({al_}) Blk{R_:x}_{al_}_{a:x} {{\n    unsigned char b[{R_}];\n}};\n" for R_, al_ in sorted(blk_types_)]
    sdefs += [f"struct Zero{n_:x}_{a:x} {{\n    unsigned char b[{n_:#x}];\n}};\n" for n_ in sorted(zero_types_)]
    body = "\n".join(sdefs) + "\n".join(gdecls) + f"\n\n// 0x71{a:08x}\n{rtype} call_{a:x}({params}) {{\n" + "\n".join(lines) + "\n}\n"
    return body, sigs, gsyms + ["IMPORT=%s=%x" % (import_of(tt)[1], tt) for tt in list(callees) + sorted(valinit_imp_ - set(callees)) if import_of(tt)] \
        + ["JTAB=%x=%x" % jt for jt in jtabs_]

CALLEES = {}
IMPORTS_USED = {}
GSYMS = set()
JT = [None, None]   # first jump table address, end of the last
APART = []          # functions left out because their jump tables do not follow the unit's
for size, a in sorted(U, key=lambda x: x[1]):
    ins = list(md.disasm(d[a:a + size], a))
    try:
        if len(ins) * 4 != size:
            raise Fail("decode")
        if False:
            raise Fail("no call")
        ARITY_USED[0] = False
        PAIR_USED[0] = False
        HOIST_USED[0] = False
        TRIVIAL_USED[0] = False
        try:
            try:
                text, sigs, gsyms = gen_function(a, ins)
            except Fail as e_:
                kn_ = KNOB_MAP.get(a, DEFAULT_KNOBS)
                if str(e_) in ("field clash", "overlap") and not {"copy1", "nocopy1", "nostructcopy"} & set(kn_):
                    # a field typed by a copy clashes: single-piece copies as block copies
                    KNOB_MAP[a] = set(kn_) | {"copy1"}
                    try:
                        text, sigs, gsyms = gen_function(a, ins)
                    except Fail:
                        KNOB_MAP[a] = set(kn_)
                        raise e_
                elif not ("merge types" in str(e_) and "Vec4f" in str(e_) and "float" in str(e_)
                        and "vlanemerge" not in KNOB_MAP.get(a, DEFAULT_KNOBS) and "novlanemerge" not in KNOB_MAP.get(a, DEFAULT_KNOBS)):
                    raise
                else:
                    # a vector and a scalar merged in one float register: the vector side is lane 0
                    KNOB_MAP[a] = set(KNOB_MAP.get(a, DEFAULT_KNOBS)) | {"vlanemerge"}
                    text, sigs, gsyms = gen_function(a, ins)
        except Fail:
            if not (ARITY_USED[0] or PAIR_USED[0] or HOIST_USED[0] or TRIVIAL_USED[0]):
                raise
            done_ = False
            if TRIVIAL_USED[0]:
                # without the argument counts of trivial callees' names the function failed: use them
                KNOB_MAP[a] = set(KNOB_MAP.get(a, DEFAULT_KNOBS)) | {"trivialarity"}
                ARITY_USED[0] = PAIR_USED[0] = HOIST_USED[0] = False
                try:
                    text, sigs, gsyms = gen_function(a, ins)
                    done_ = True
                except Fail:
                    if not (ARITY_USED[0] or PAIR_USED[0] or HOIST_USED[0]):
                        raise
            if not done_:
                # known argument counts, a split 64-bit load or a hoisted address made this function fail: generate
                # it as before
                KNOB_MAP[a] = set(KNOB_MAP.get(a, DEFAULT_KNOBS)) | ({"noknownarity"} if ARITY_USED[0] else set()) \
                    | ({"nopair32"} if PAIR_USED[0] else set()) | ({"nohoistaddr"} if HOIST_USED[0] else set())
                text, sigs, gsyms = gen_function(a, ins)
        if len(text) > 2000000:
            raise Fail("output too large")
        # jump tables share the unit's .rodata, so one anchor maps them only while they follow each other as
        # in the original
        jt_end_ = JT[1]
        for x in gsyms:
            if x.startswith("JTAB="):
                _, ta_, ts_ = x.split("=")
                if jt_end_ is not None and int(ta_, 16) != jt_end_:
                    raise Fail("switch table apart")
                jt_end_ = int(ta_, 16) + int(ts_, 16)
        upd_ = {}
        for (t_, _ak), sig_ in sigs.items():
            # a return type that clashes with an earlier declaration gets another name for the same address
            for nm_ in ("callee", "callee2", "callee3"):
                key_ = (t_, tuple(sig_[0]), nm_)
                have_ = upd_.get(key_, CALLEES.get(key_))
                if have_ is None or have_ == sig_[1] or sig_[1] == "void":
                    upd_[key_] = have_ if have_ is not None else sig_[1]
                    break
                if have_ == "void":
                    upd_[key_] = sig_[1]
                    break
            else:
                raise Fail(f"callee signature: {have_} vs {sig_}")
            if nm_ != "callee":
                text = re.sub(rf"\bcallee_{t_:x}\(", f"{nm_}_{t_:x}(", text)
        if any(sym.split("=")[0] in {x.split("=")[0] for x in GSYMS} and sym not in GSYMS for sym in gsyms):
            raise Fail("global clash")
        gnames = {x.split("=")[0].replace("got:", "") for x in GSYMS}
        text = "\n".join(l for l in text.split("\n") if not any(l.startswith("extern ") and f" {gn}" in l for gn in gnames))
        for x in gsyms:
            if x.startswith("IMPORT="):
                _, mn_, ad_ = x.split("=")
                IMPORTS_USED[mn_] = int(ad_, 16)
        for x in gsyms:
            if x.startswith("JTAB="):
                if JT[0] is None:
                    JT[0] = int(x.split("=")[1], 16)
                JT[1] = jt_end_
        gsyms = [x for x in gsyms if not x.startswith("IMPORT=") and not x.startswith("JTAB=")]
        CALLEES.update(upd_)
        GSYMS.update(gsyms)
        defs.append(text)
        funcs.append(f"placeholder_{a:x}=0x71{a:08x}")
    except (Fail, ValueError, KeyError, IndexError, RecursionError, TypeError, ZeroDivisionError) as e:
        if os.environ.get("TRACE") and not isinstance(e, Fail):
            raise
        skipped += 1
        if str(e) == "switch table apart":
            APART.append(a)
        if os.environ.get("FAILDUMP"):
            with open(os.environ["FAILDUMP"], "a", encoding="utf-8") as fd_:
                fd_.write(f"{a:x}\t{size}\t{type(e).__name__}\t{e}\n")
        if isinstance(e, Fail):
            k = str(e).split(":")[0][:20]
            reasons[k] = reasons.get(k, 0) + 1
        else:
            k = f"{type(e).__name__}: {str(e)[:40]}"
            internal[k] = internal.get(k, 0) + 1
def resolve_ovcasts(d_):
    """Replace each argument marker: a cast where the callee's overloads of that arity differ in that position."""
    pat_ = re.compile("\x01([0-9a-f]+)/(\\d+)/(\\d+)\x03([^\x01\x02\x03]*)\x03([^\x01\x02]*)\x02")
    def one_(mm_):
        t_, n_, j_ = int(mm_.group(1), 16), int(mm_.group(2)), int(mm_.group(3))
        at_, text_ = mm_.group(4), mm_.group(5)
        if len({a_[j_] for (tt_, a_, nm_) in CALLEES if tt_ == t_ and len(a_) == n_}) < 2:
            return text_
        if at_ == "void*":
            return f"reinterpret_cast<void*>({text_})"
        return f"static_cast<{at_}>({text_})"
    while "\x01" in d_:
        d2_ = pat_.sub(one_, d_)
        if d2_ == d_:
            break
        d_ = d2_
    return d_.replace("\x01", "").replace("\x02", "").replace("\x03", "")
VEC4_DECL = "typedef float Vec4f __attribute__((ext_vector_type(4)));\n\n"
FLOAT2_DECL = "struct Float2 {\n    float x;\n    float y;\n};\n\n"
PAIR16_DECL = "// A 16-byte struct returned in x0 and x1.\nstruct Pair16 {\n    long a;\n    long b;\n};\n\n"
VINS_DECL = ("static inline Vec4f vins(Vec4f v, float s, int i) {\n    v[i] = s;\n    return v;\n}\n"
             "static inline Vec4f vundef() {\n    Vec4f v;\n    return v;\n}\n\n")
VECU_DECL = ("// A 16-byte vector passed and returned in two x registers.\nunion VecU {\n    Vec4f v;\n    long l[2];\n    float f[4];\n    int i[4];\n};\n"
             "static inline VecU vecu(Vec4f v) {\n    VecU u;\n    u.v = v;\n    return u;\n}\n\n")
head = ("// Small functions generated by symbolic execution (calls, virtual calls, stack locals, guards, arrays, floats): loads and call results are named\n"
        "// locals in their original order. Struct, field and callee names are placeholders after the\n"
        "// address and offset. Status: matching/README.md.\n\n")
imp_lines = []
if any(mn in IMPORTS for mn in IMPORTS_USED):
    imp_lines.append("namespace nn {")
    for ns_ in sorted({IMPORTS[mn][3] for mn in IMPORTS_USED if mn in IMPORTS}):
        imp_lines.append(f"namespace {ns_} {{")
        imp_lines.extend(NN_DECLS[ns_])
        imp_lines.append(f"}}  // namespace {ns_}")
    imp_lines.append("}  // namespace nn")
for mn in sorted(IMPORTS_USED):
    if mn in C_PROTOS:
        r_, ps_ = C_PROTOS[mn]
        imp_lines.append(f'extern "C" {r_} {mn}({", ".join(ps_)});')
defs = [resolve_ovcasts(d_) for d_ in defs]
cdecl_text = "\n".join(imp_lines) + "\n\n" + "\n".join(f"{rts} {nm}_{t:x}({', '.join(atypes)});{' ' * 8}// 0x71{t:08x}" for (t, atypes, nm), rts in sorted(CALLEES.items())
                       if not any(x.endswith("*") and x != "void*" for x in list(atypes) + [rts]))
open(out, "w", encoding="utf-8", newline="\n").write(head + ("#include <arm_neon.h>\n\n" if any("float32x4_t" in d_ or "vcombine_f32" in d_ for d_ in defs) else "") + (VEC4_DECL if any("Vec4f" in d_ or "VecU" in d_ or "vins(" in d_ for d_ in defs) else "") + (FLOAT2_DECL if any("Float2" in d_ for d_ in defs) else "") + (PAIR16_DECL if any("Pair16" in d_ for d_ in defs) else "") + (VECU_DECL if any("VecU" in d_ for d_ in defs) else "") + (VINS_DECL if any("vins(" in d_ for d_ in defs) else "") + cdecl_text + "\n\n" + "\n".join(defs))
m = MATCHDIR
if os.environ.get("SYMOUT"):
    json.dump({"unit": unit, "gsyms": sorted(GSYMS),
               "imports": ["%s=0x71%08x" % (mn, ad) for mn, ad in sorted(IMPORTS_USED.items())],
               "funcs": funcs, "rodata": "0x71%08x" % JT[0] if JT[0] is not None else None,
               "apart": ["%x" % x for x in APART]},
              open(os.environ["SYMOUT"], "w", encoding="utf-8"))
    print("generated", len(funcs), "skipped", skipped)
    print(sorted(reasons.items(), key=lambda x: -x[1])[:16])
    print("internal errors:", sum(internal.values()), sorted(internal.items(), key=lambda x: -x[1])[:8])
    sys.exit(0)
if os.environ.get("APARTOUT"):
    open(os.environ["APARTOUT"], "w", encoding="utf-8").write(" ".join("%x" % x for x in APART))
if os.environ.get("DRYRUN"):
    GSYMS, IMPORTS_USED, funcs = set(), {}, funcs if False else []
if GSYMS:
    gl_ = sorted(GSYMS)
    for i_ in range(0, len(gl_), 200):
        subprocess.run([sys.executable, "-B", "-I", m + r"\tools\add_symbols.py", *gl_[i_:i_ + 200]], cwd=m, capture_output=True)
if IMPORTS_USED:
    subprocess.run([sys.executable, "-B", "-I", m + r"\tools\add_symbols.py", *["%s=0x71%08x" % (mn, ad) for mn, ad in sorted(IMPORTS_USED.items())]], cwd=m, capture_output=True)
for i_ in range(0, len(funcs), 200):
    subprocess.run([sys.executable, "-B", "-I", m + r"\tools\add_symbols.py", "--unit", unit, *funcs[i_:i_ + 200]], cwd=m, capture_output=True)
if funcs and JT[0] is not None:
    subprocess.run([sys.executable, "-B", "-I", m + r"\tools\add_symbols.py", "--map", unit, ".rodata=0x71%08x" % JT[0]], cwd=m, capture_output=True)
print("generated", len(funcs), "skipped", skipped)
print(sorted(reasons.items(), key=lambda x: -x[1])[:16])
print("internal errors:", sum(internal.values()), sorted(internal.items(), key=lambda x: -x[1])[:8])
