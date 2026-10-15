"""Mismatch tally without touching data/units.json: generate unmatched functions into scratch units under build/,
compile them in parallel, and classify every function against the original.

usage: mm_tally.py GEN LO HI [--addr LO-HI] [--only FILE] [--knobs K] [--jobs N] [--chunk N] [--tsv FILE]
  LO HI          size band in bytes (as for gen.py and mm_probe.py)
  --addr LO-HI   image offset range (hex), e.g. 380000-800000
  --only FILE    only the functions listed in FILE (hex offsets, whitespace or comma separated)
  --knobs K      knob set (VARIANT) for the generator, e.g. sink+callinline
  --jobs N       parallel compiles (at most 6; default 6)
  --tsv FILE     write one line per function: offset, class, size, first differing pair
Also reached as `mm_probe.py GEN LO HI --classes [options]`.

Classes: match; size (our function has another length; split by the word difference and the first differing
instruction pair); regalloc (same instructions with registers abstracted); schedule (same instructions in another
order); other (split by the first differing pair). Functions that do not compile are counted and left out.
"""
import os as _os
GENDIR = _os.path.dirname(_os.path.abspath(__file__))
MATCHDIR = _os.path.dirname(_os.path.dirname(GENDIR))
ROOTDIR = _os.path.dirname(MATCHDIR)
import argparse, collections, csv, json, os, re, struct, subprocess, sys
# tools/gen/dis.py would shadow the standard dis module (imported by capstone through inspect)
sys.path[:] = [p_ for p_ in sys.path if os.path.abspath(p_ or os.curdir) != GENDIR]
from concurrent.futures import ThreadPoolExecutor
sys.path.insert(0, os.path.join(MATCHDIR, "tools"))
sys.path.insert(0, os.path.join(ROOTDIR, ".tools", "python"))
import capstone  # noqa: E402
import check_obj, check  # noqa: E402

WORK = os.path.join(MATCHDIR, "build", "mmtally")
BASE = 0x7100000000


def candidates(lo, hi, alo, ahi, only):
    man = json.load(open(os.path.join(MATCHDIR, "data", "units.json"), encoding="utf-8-sig"))
    taken = {check.address(a) for u in man["units"].values() for a in u.get("functions", {}).values()}
    out = []
    for r in csv.DictReader(open(os.path.join(MATCHDIR, "data", "functions.csv"), newline="")):
        a = check.address(r["Address"])
        if r["Quality"] == "U" and lo <= int(r["Size"]) <= hi and alo <= a < ahi and a not in taken \
                and (only is None or a in only):
            out.append(a)
    return out


def build_chunk(gen, addrs, knobs, tag):
    """Generate addrs into a scratch unit, dropping functions that do not compile. Returns (cpp, obj, symbols)."""
    man = json.load(open(os.path.join(MATCHDIR, "data", "units.json"), encoding="utf-8-sig"))
    cpp = os.path.join(WORK, f"t{tag}.cpp")
    obj = os.path.join(WORK, f"t{tag}.o")
    symf = os.path.join(WORK, f"t{tag}.json")
    keep = list(addrs)
    dropped = 0
    for _ in range(6):
        env = dict(os.environ, ONLY=",".join("%x" % a for a in keep), EXCLUDE="", VARIANT=knobs, VARIANT_MAP="",
                   DRYRUN="", FAILDUMP="", TRACE="", SYMOUT=symf, NEARMISS="")
        subprocess.run([sys.executable, "-B", "-I", gen, cpp, "misc/mm_tally.cpp", "8", "1000000"], cwd=MATCHDIR,
                       capture_output=True, text=True, env=env)
        if not os.path.exists(symf):
            return None
        c = subprocess.run([os.path.join(ROOTDIR, man["compiler"]), *man["flags"], "-ferror-limit=0",
                            "-I", os.path.join(MATCHDIR, "include"), "-c", cpp, "-o", obj], capture_output=True, text=True)
        if c.returncode == 0:
            return cpp, obj, json.load(open(symf, encoding="utf-8")), dropped
        lines = open(cpp, encoding="utf-8").read().split("\n")
        bad = set()
        for ln in {int(x) for x in re.findall(r"t%s\.cpp:(\d+):\d+: error" % re.escape(tag), c.stderr)}:
            for j in range(ln - 1, -1, -1):
                mm = re.match(r"// 0x71([0-9a-f]{8})", lines[j])
                if mm:
                    bad.add(int(mm.group(1), 16)); break
        if not bad:
            return None
        dropped += len(bad & set(keep))
        keep = [a for a in keep if a not in bad]
        if not keep:
            return None
    return None


def mine_bytes(obj, name, addr, mapping, image):
    data, sections, symbols, relocs = check_obj.read_elf(obj)
    s = next(x for x in symbols if x.name == name and not x.is_section)
    sec = sections[s.shndx]
    mine = bytearray(data[sec[4] + s.value: sec[4] + s.value + s.size])
    for k in range(0, s.size, 4):
        rel = relocs.get(s.shndx, {}).get(s.value + k)
        if not rel:
            continue
        rtype, symidx, addend = rel
        w, = struct.unpack_from("<I", mine, k)
        if rtype in (311, 312):
            slot = mapping.get("got:" + symbols[symidx].name)
            target = slot + addend if slot is not None else None
        else:
            target = check_obj.resolve(symbols, symbols[symidx], addend, mapping, data, sections, image)
        p = check_obj.apply(w, rtype, target, addr + k) if target is not None else None
        if p is not None:
            struct.pack_into("<I", mine, k, p)
    return bytes(mine)


def abstract(i):
    o = re.sub(r"\b([xwqsdv])(\d+|zr)\b", r"\1", i.op_str)
    o = re.sub(r"#0x7100[0-9a-f]+|#0x[0-9a-f]{5,}", "#ADDR", o)
    return f"{i.mnemonic} {o}"


def classify(built, sizes, image, md, base_map):
    cpp, obj, sy, _ = built
    mapping = dict(base_map)
    for x in sy["gsyms"] + sy["imports"]:
        n, a = x.split("=")
        mapping[n] = check.address(a)
    mapping[".rodata.cst4"] = 0x73b000
    mapping[".rodata.cst16"] = 0x73dff0
    data, sections, symbols, relocs = check_obj.read_elf(obj)
    for s in symbols:
        if s.is_section or s.shndx != 0 or s.name in mapping:
            continue
        # the address suffix of a placeholder name, read from the identifier its _Z<length> prefix delimits (a
        # parameter code right after it may itself be a hex letter or any lowercase letter)
        ml = re.match(r"_Z(\d+)", s.name)
        ident = s.name[ml.end():ml.end() + int(ml.group(1))] if ml else s.name
        mm = re.search(r"_([0-9a-f]{4,8})$", ident)
        if mm:
            mapping[s.name] = int(mm.group(1), 16)
    defined = [s.name for s in symbols if not s.is_section and s.shndx != 0 and s.size]
    out = []
    for f in sy["funcs"]:
        addr = check.address(f.split("=")[1])
        name = next((d for d in defined if re.search(r"call_0*%x(?![0-9a-f])" % addr, d)), None)
        if name is None:
            continue
        mapping.setdefault(name, addr)
        mine = mine_bytes(obj, name, addr, mapping, image)
        size = sizes[addr]
        orig = image[addr: addr + size]
        mi = [abstract(i) for i in md.disasm(mine, addr)]
        oi = [abstract(i) for i in md.disasm(orig, addr)]
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
        delta = (len(mine) - size) // 4
        out.append((addr, cls, size, delta, pair))
    return out


def main(argv):
    ap = argparse.ArgumentParser()
    ap.add_argument("gen"); ap.add_argument("lo", type=int); ap.add_argument("hi", type=int)
    ap.add_argument("--addr", default="0-ffffffff"); ap.add_argument("--only")
    ap.add_argument("--knobs", default=""); ap.add_argument("--jobs", type=int, default=6)
    ap.add_argument("--chunk", type=int, default=100); ap.add_argument("--tsv")
    a = ap.parse_args(argv)
    alo, ahi = (int(x, 16) for x in a.addr.split("-"))
    only = None
    if a.only:
        only = {int(x, 16) for x in re.split(r"[\s,]+", open(a.only, encoding="utf-8-sig").read()) if x}
    addrs = candidates(a.lo, a.hi, alo, ahi, only)
    os.makedirs(WORK, exist_ok=True)
    gen = os.path.abspath(a.gen)
    chunks = [addrs[i:i + a.chunk] for i in range(0, len(addrs), a.chunk)]
    with ThreadPoolExecutor(max(1, min(6, a.jobs))) as ex:
        built = list(ex.map(lambda k: build_chunk(gen, chunks[k], a.knobs, f"_{k}"), range(len(chunks))))
    image = check_obj.IMAGE.read_bytes()
    md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
    man = json.load(open(os.path.join(MATCHDIR, "data", "units.json"), encoding="utf-8-sig"))
    base_map = dict(check.collect_externals(man))
    sizes = {check.address(r["Address"]): int(r["Size"]) for r in csv.DictReader(open(os.path.join(MATCHDIR, "data", "functions.csv"), newline=""))}
    rows, failed_chunks, dropped = [], 0, 0
    for b in built:
        if b is None:
            failed_chunks += 1
            continue
        dropped += b[3]
        rows += classify(b, sizes, image, md, base_map)
    cls_n, cls_b, cls_ex = collections.Counter(), collections.Counter(), collections.defaultdict(list)
    sub_n, sub_b, sub_ex = collections.Counter(), collections.Counter(), collections.defaultdict(list)
    for addr, cls, size, delta, pair in rows:
        cls_n[cls] += 1; cls_b[cls] += size; cls_ex[cls].append(f"{addr:x}")
        if cls in ("size", "other"):
            dk = ("%+d" % delta if abs(delta) <= 3 else ("+more" if delta > 0 else "-more")) if cls == "size" else ""
            key = (cls, dk) + pair
            sub_n[key] += 1; sub_b[key] += size; sub_ex[key].append(f"{addr:x}")
    print(f"{len(addrs)} candidates, {len(rows)} classified, {dropped} did not compile, {failed_chunks} chunks failed")
    for c, n in cls_n.most_common():
        print(f"  {c:9s} {n:5d} {cls_b[c]:8d}  e.g. {' '.join(cls_ex[c][:3])}")
    print("size and other, by word difference and first differing pair (ours, orig):")
    for k, n in sub_n.most_common(30):
        print(f"  {n:4d} {sub_b[k]:7d}  {k}  e.g. {' '.join(sub_ex[k][:3])}")
    if a.tsv:
        with open(a.tsv, "w", encoding="utf-8") as f:
            for addr, cls, size, delta, pair in rows:
                f.write(f"{addr:x}\t{cls}\t{size}\t{delta}\t{pair[0]},{pair[1]}\n")


if __name__ == "__main__":
    main(sys.argv[1:])
