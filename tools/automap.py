"""Derive the units.json "map" entries of rodata sections from the original code, checked against content.

Usage: automap.py [--write] UNIT [UNIT ...]

A unit whose functions load constants, read jump tables or strings refers to sections such as .rodata,
.rodata.cst4/.cst8/.cst16 or .rodata.<mangled> (a template instantiation's jump table). check.py resolves those
relocations only when the unit's "map" gives the section's original address; otherwise the relocated fields are
masked. This tool proposes the missing entries.

For each relocation pair (adrp + add/ldr) of a compared function into an unmapped rodata section, the original
target is decoded from the original instructions at the same offsets. Deriving an address from the instruction it
is then compared with would match any target, so an entry is proposed only when content confirms it:

- a mergeable constant section (.rodata.cstN): every constant the unit loads from it must equal the image's value
  at its derived address, and check_obj's forward search from the proposed base (the lowest derived address) must
  land on each derived address;
- any other rodata section: the section must carry no relocations of its own, every relocation into it must imply
  the same base, and the section's bytes must equal the image's bytes from that base.

A section failing a test gets no entry and stays masked. --write adds the entries to data/units.json (existing
entries are never changed).
"""
import json
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import check  # noqa: E402
import check_obj  # noqa: E402

ROOT = Path(__file__).resolve().parents[2]
MATCHING = ROOT / "matching"
UNITS = MATCHING / "data/units.json"
BUILD = MATCHING / "build"
PAGE, LO12 = 275, {277: 0, 278: 0, 284: 1, 285: 2, 286: 3, 299: 4}
PREL32 = 261
# the pools most units map their mergeable constants to; a unit's own lowest constant otherwise
POOLS = {".rodata.cst4": 0x73B000, ".rodata.cst16": 0x73DFF0}


def target_of(image, place_hi, place_lo, lo_type):
    """Original address an adrp at place_hi and an add/ldr at place_lo compute."""
    hi, = struct.unpack_from("<I", image, place_hi)
    lo, = struct.unpack_from("<I", image, place_lo)
    if (hi & 0x9F000000) != 0x90000000:
        return None
    imm = (((hi >> 5) & 0x7FFFF) << 2) | ((hi >> 29) & 3)
    if imm & (1 << 20):
        imm -= 1 << 21
    page = (place_hi & ~0xFFF) + (imm << 12)
    return page + (((lo >> 10) & 0xFFF) << LO12[lo_type])


def propose(unit, spec, manifest, image):
    compiler = ROOT / manifest["compiler"]
    obj = BUILD / ("automap_" + unit.replace("/", "_").rsplit(".", 1)[0] + ".o")
    cmd = [str(compiler), *manifest["flags"], "-I", str(MATCHING / "include"), "-c", str(MATCHING / "src" / unit),
           "-o", str(obj)]
    if subprocess.run(cmd, capture_output=True, text=True).returncode != 0:
        return None, "compile failed"
    data, sections, symbols, relocs = check_obj.read_elf(obj)
    shstr = sections[struct.unpack_from("<H", data, 0x3E)[0]]
    names = [data[shstr[4] + s[0]: data.index(b"\0", shstr[4] + s[0])].decode() for s in sections]
    rel_of = {s[7] for s in sections if s[1] == 4}       # sections that carry relocations of their own
    have = spec.get("map", {})
    mapping = dict(check.collect_externals(manifest))
    mapping.update({n: check.address(a) for n, a in have.items()})
    mapping.update({n: check.address(a) for n, a in spec["functions"].items()})
    by_name = {s.name: s for s in symbols if not s.is_section}
    uses = {}                                            # section name -> [(addend, derived target)]
    for fname, faddr in spec["functions"].items():
        s = by_name.get(fname)
        if s is None:
            continue
        addr = int(faddr, 16) & 0xFFFFFFFF
        srel = relocs.get(s.shndx, {})
        hi_at = {}
        for off in sorted(srel):
            rtype, symidx, addend = srel[off]
            sym = symbols[symidx]
            if not sym.is_section or not sym.name.startswith(".rodata") or sym.name in have:
                continue
            k = off - s.value
            if not 0 <= k < s.size:
                continue
            if rtype == PAGE:
                hi_at[(symidx, addend)] = k
            elif rtype in LO12 and (symidx, addend) in hi_at:
                t = target_of(image, addr + hi_at[(symidx, addend)], addr + k, rtype)
                if t is not None:
                    uses.setdefault(sym.name, []).append((addend, t))
    out, notes = {}, []
    for name, lst in sorted(uses.items()):
        shndx = names.index(name)
        sec = sections[shndx]
        body = data[sec[4]: sec[4] + sec[5]]
        if name.startswith(".rodata.cst"):
            width = int(name[len(".rodata.cst"):] or 4)
            # constants equal to the original's confirm a base; one that differs (a near miss loading another
            # value) stays a mismatch as long as check_obj's resolution of it, its fallback included, does not
            # land on the original's address
            eq = [(a, t) for a, t in lst if image[t:t + width] == body[a:a + width]]
            ne = [(a, t) for a, t in lst if image[t:t + width] != body[a:a + width]]
            if not eq:
                notes.append(f"{name}: no constant equals the original's")
                continue
            def search(a):
                # check_obj.resolve for a mergeable constant
                for k in range(0, max(a + width, check_obj.MERGE_SEARCH), width):
                    if image[base + k: base + k + width] == body[a:a + width]:
                        return base + k
                return base + a
            for base in ([POOLS[name]] if name in POOLS else []) + [min(t for a, t in eq)]:
                if all(search(a) == t for a, t in eq) and all(search(a) != t for a, t in ne):
                    out[name] = base
                    break
            else:
                notes.append(f"{name}: an equal value lies before a constant's original address")
        else:
            bases = {t - a for a, t in lst}
            if len(bases) != 1:
                notes.append(f"{name}: relocations imply different bases")
                continue
            base = bases.pop()
            if sec[1] == 8:
                notes.append(f"{name}: no content to compare")
                continue
            body = bytearray(body)
            if shndx in rel_of:
                # jump tables: each 32-bit entry is a code label minus its table's start (`.word .LBB - .LJTI`, a
                # PREL32 whose addend carries the entry's distance from the table start). The table starts are
                # the offsets the code refers to; the label lies in a function of the unit, whose original
                # address gives the entry's value
                starts = sorted({a for a, t in lst})
                bad = None
                for off, (rtype, symidx, addend) in sorted(relocs.get(shndx, {}).items()):
                    js = max((s_ for s_ in starts if s_ <= off), default=None)
                    sym = symbols[symidx]
                    fn = None
                    if rtype == PREL32 and js is not None and sym.is_section and off + 4 <= len(body):
                        lbb = addend - (off - js)
                        fn = next((o for o in symbols if not o.is_section and o.shndx == sym.shndx and o.name in mapping
                                   and o.value <= lbb < o.value + o.size), None)
                    if fn is None:
                        bad = f"{sym.name}+{addend:#x} (type {rtype})"
                        break
                    struct.pack_into("<I", body, off, (mapping[fn.name] + lbb - fn.value - (base + js)) & 0xFFFFFFFF)
                if bad:
                    notes.append(f"{name}: relocation {bad} cannot be resolved")
                    continue
            if image[base: base + len(body)] != bytes(body):
                notes.append(f"{name}: content differs from the image at {check_obj.BASE + base:#x}")
                continue
            out[name] = base
    return out, notes


def main():
    args = sys.argv[1:]
    write = "--write" in args
    units = [a for a in args if not a.startswith("--")]
    manifest = json.loads(UNITS.read_text(encoding="utf-8-sig"))
    image = check_obj.IMAGE.read_bytes()
    BUILD.mkdir(exist_ok=True)
    changed = False
    for unit in units:
        spec = manifest["units"].get(unit)
        if spec is None:
            print(f"{unit}: unknown unit")
            continue
        out, notes = propose(unit, spec, manifest, image)
        if out is None:
            print(f"{unit}: {notes}")
            continue
        for n, b in out.items():
            print(f"{unit}: {n} = {check_obj.BASE + b:#x}")
        for n in notes:
            print(f"{unit}: no entry, {n}")
        if write and out:
            m = spec.setdefault("map", {})
            for n, b in out.items():
                m.setdefault(n, f"{check_obj.BASE + b:#x}")
            changed = True
    if changed:
        UNITS.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8", newline="\n")


if __name__ == "__main__":
    main()
