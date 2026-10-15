"""Rank big unmatched functions by how close the generated source compiles to the original.

usage: rank.py OUTTSV LO HI [--jobs N] [--knobs K] [--only FILE] [--limit N]
One function per scratch unit (so jump tables map), compile timeout, difflib instruction diff count.
Writes rows: addr size cls ndiff nabs delta first_pair  (ndiff: instructions differing incl. registers,
nabs: with registers abstracted).
"""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
WORK = _os.path.join(M, "build", "s3")  # scratch files
_os.makedirs(WORK, exist_ok=True)
import os, sys, json, csv, re, subprocess, difflib, time, argparse
ROOT = os.path.dirname(M)
GENDIR = os.path.join(M, "tools", "gen")
sys.path.insert(0, os.path.join(M, "tools"))
sys.path.insert(0, os.path.join(ROOT, ".tools", "python"))
import capstone  # noqa
import check_obj, check  # noqa
sys.path.append(GENDIR)
import mm_tally  # noqa  (removes GENDIR from sys.path itself)
from concurrent.futures import ThreadPoolExecutor

WORK = os.path.join(M, "build", "s3rank")
os.makedirs(WORK, exist_ok=True)
GEN = os.path.join(GENDIR, "gen.py")


def build_one(a, knobs):
    tag = "%x_%s" % (a, (knobs or "d").replace("+", "_"))
    cpp = os.path.join(WORK, f"r{tag}.cpp"); obj = os.path.join(WORK, f"r{tag}.o"); symf = os.path.join(WORK, f"r{tag}.json")
    for p in (cpp, obj, symf):
        if os.path.exists(p):
            os.remove(p)
    env = dict(os.environ, ONLY="%x" % a, EXCLUDE="", VARIANT=knobs, VARIANT_MAP="", DRYRUN="", TRACE="",
               SYMOUT=symf, NEARMISS="", FAILDUMP=os.path.join(WORK, f"r{tag}.fail"))
    t0 = time.time()
    try:
        g = subprocess.run([sys.executable, "-B", "-I", GEN, cpp, "misc/s3rank.cpp", "8", "1000000"], cwd=M,
                           capture_output=True, text=True, env=env, timeout=600)
    except subprocess.TimeoutExpired:
        return a, "gen-timeout", None
    if not os.path.exists(symf):
        return a, "gen-crash", g.stderr[-300:]
    sy = json.load(open(symf, encoding="utf-8"))
    if not sy["funcs"]:
        fr = open(os.path.join(WORK, f"r{tag}.fail"), encoding="utf-8").read().strip() if os.path.exists(os.path.join(WORK, f"r{tag}.fail")) else ""
        return a, "nogen", fr.split("\t", 2)[-1][:120]
    man = json.load(open(os.path.join(M, "data", "units.json"), encoding="utf-8-sig"))
    try:
        c = subprocess.run([os.path.join(ROOT, man["compiler"]), *man["flags"], "-ferror-limit=0",
                            "-I", os.path.join(M, "include"), "-c", cpp, "-o", obj], capture_output=True, text=True, timeout=900)
    except subprocess.TimeoutExpired:
        return a, "cc-timeout", None
    if c.returncode != 0:
        err = next((l for l in c.stderr.split("\n") if "error" in l), "")
        return a, "ccfail", err[-160:]
    return a, "built", (cpp, obj, sy, time.time() - t0)


def classify(a, built, size, image, md, base_map):
    cpp, obj, sy, dt = built
    mapping = dict(base_map)
    for x in sy["gsyms"] + sy["imports"]:
        n, v = x.split("=")
        mapping[n] = check.address(v)
    mapping[".rodata.cst4"] = 0x73b000
    mapping[".rodata.cst16"] = 0x73dff0
    if sy.get("rodata"):
        mapping[".rodata"] = check.address(sy["rodata"])
    data, sections, symbols, relocs = check_obj.read_elf(obj)
    for s in symbols:
        mm = re.search(r"_([0-9a-f]{5,6})(?=[A-Z]|$|E|P|v|i|f)", s.name) if not s.is_section and s.shndx == 0 else None
        if mm and s.name not in mapping:
            mapping[s.name] = int(mm.group(1), 16)
    defined = [s.name for s in symbols if not s.is_section and s.shndx != 0 and s.size]
    name = next((d for d in defined if re.search(r"call_0*%x(?![0-9a-f])" % a, d)), None)
    if name is None:
        name = next((d for d in defined if re.search(r"_0*%x(?![0-9a-f])" % a, d)), None)
    if name is None:
        return None
    mapping.setdefault(name, a)
    mine = mm_tally.mine_bytes(obj, name, a, mapping, image)
    orig = image[a: a + size]
    fi = lambda i: f"{i.mnemonic} {i.op_str}"
    mi_full = [fi(i) for i in md.disasm(mine, a)]
    oi_full = [fi(i) for i in md.disasm(orig, a)]
    mi = [mm_tally.abstract(i) for i in md.disasm(mine, a)]
    oi = [mm_tally.abstract(i) for i in md.disasm(orig, a)]
    def nd(x, y):
        sm = difflib.SequenceMatcher(None, x, y, autojunk=False)
        return max(len(x), len(y)) - sum(b.size for b in sm.get_matching_blocks())
    k = next((j for j in range(min(len(mi), len(oi))) if mi[j] != oi[j]), min(len(mi), len(oi)))
    pair = (mi[k].split()[0] if k < len(mi) else "END", oi[k].split()[0] if k < len(oi) else "END")
    if mine == orig:
        cls = "match"
    elif len(mine) != size:
        cls = "size"
    elif mi == oi:
        cls = "regalloc"
    elif sorted(mi) == sorted(oi):
        cls = "schedule"
    else:
        cls = "other"
    return cls, nd(mi_full, oi_full), nd(mi, oi), (len(mine) - size) // 4, "%s,%s@%d" % (pair[0], pair[1], k), dt


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("out"); ap.add_argument("lo", type=int); ap.add_argument("hi", type=int)
    ap.add_argument("--jobs", type=int, default=2); ap.add_argument("--knobs", default="")
    ap.add_argument("--only"); ap.add_argument("--limit", type=int, default=0)
    a = ap.parse_args()
    only = None
    if a.only:
        only = {int(x, 16) for x in re.split(r"[\s,]+", open(a.only, encoding="utf-8-sig").read()) if x}
    addrs = mm_tally.candidates(a.lo, a.hi, 0, 0xffffffff, only)
    sizes = {check.address(r["Address"]): int(r["Size"]) for r in csv.DictReader(open(os.path.join(M, "data", "functions.csv"), newline=""))}
    addrs.sort(key=lambda x: sizes[x])
    if a.limit:
        addrs = addrs[:a.limit]
    done = set()
    if os.path.exists(a.out):
        done = {int(l.split("\t")[0], 16) for l in open(a.out, encoding="utf-8") if l.strip()}
    addrs = [x for x in addrs if x not in done]
    print(len(addrs), "to do", flush=True)
    image = check_obj.IMAGE.read_bytes()
    md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
    man = json.load(open(os.path.join(M, "data", "units.json"), encoding="utf-8-sig"))
    base_map = dict(check.collect_externals(man))
    out = open(a.out, "a", encoding="utf-8")
    with ThreadPoolExecutor(a.jobs) as ex:
        for addr, st, info in ex.map(lambda x: build_one(x, a.knobs), addrs):
            if st == "built":
                try:
                    r = classify(addr, info, sizes[addr], image, md, base_map)
                except Exception as e:  # noqa
                    r = None
                    st = "classerr"; info = str(e)[:100]
                if r:
                    cls, n1, n2, d, pair, dt = r
                    line = f"{addr:x}\t{sizes[addr]}\t{cls}\t{n1}\t{n2}\t{d}\t{pair}\t{dt:.0f}s"
                else:
                    line = f"{addr:x}\t{sizes[addr]}\t{st if st != 'built' else 'noname'}\t-\t-\t-\t{info if st!='built' else ''}"
            else:
                line = f"{addr:x}\t{sizes[addr]}\t{st}\t-\t-\t-\t{info or ''}"
            out.write(line.replace("\n", " ") + "\n"); out.flush()
            print(line, flush=True)


if __name__ == "__main__":
    main()
