"""Compare functions in an AArch64 ELF object with main.memory.bin.

Usage: check_obj.py OBJECT [--map NAME=ADDRESS ...] SYMBOL=ADDRESS [...]

SYMBOL=ADDRESS pairs name functions to compare. --map gives the original
address of a relocation target: a symbol name (including file-static
variables, which are found through their section-relative relocations) or a
section name such as .bss. Compared functions are mapped automatically.
Relocations whose target is mapped are applied and the full word compared;
unmapped ones are compared with the relocated field masked and reported.
"""
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / ".tools" / "python"))
import capstone  # noqa: E402

IMAGE = ROOT / "analysis/extracted/update/decompressed/main.memory.bin"
BASE = 0x7100000000

# Relocation type -> mask of the bits the relocation fills in.
RELOC_MASKS = {
    275: 0x60FFFFE0,  # ADR_PREL_PG_HI21
    277: 0x003FFC00,  # ADD_ABS_LO12_NC
    278: 0x003FFC00,  # LDST8_ABS_LO12_NC
    284: 0x003FFC00,  # LDST16_ABS_LO12_NC
    285: 0x003FFC00,  # LDST32_ABS_LO12_NC
    286: 0x003FFC00,  # LDST64_ABS_LO12_NC
    299: 0x003FFC00,  # LDST128_ABS_LO12_NC
    311: 0x60FFFFE0,  # ADR_GOT_PAGE
    312: 0x003FFC00,  # LD64_GOT_LO12_NC
    282: 0x03FFFFFF,  # JUMP26
    283: 0x03FFFFFF,  # CALL26
}
LO12_SHIFT = {277: 0, 278: 0, 284: 1, 285: 2, 286: 3, 299: 4}


class Symbol:
    def __init__(self, name, shndx, value, size, is_section):
        self.name, self.shndx, self.value, self.size, self.is_section = name, shndx, value, size, is_section


def read_elf(path):
    data = Path(path).read_bytes()
    shoff, = struct.unpack_from("<Q", data, 0x28)
    shentsize, shnum, shstrndx = struct.unpack_from("<HHH", data, 0x3A)
    sections = [struct.unpack_from("<IIQQQQIIQQ", data, shoff + i * shentsize) for i in range(shnum)]

    def name(off, strtab):
        start = sections[strtab][4] + off
        return data[start:data.index(b"\0", start)].decode()

    names = [name(s[0], shstrndx) for s in sections]
    symbols, relocs = [], {}
    for s in sections:
        if s[1] == 2:  # SYMTAB
            for j in range(s[5] // 24):
                st_name, info, _, shndx, value, size = struct.unpack_from("<IBBHQQ", data, s[4] + j * 24)
                is_section = (info & 0xF) == 3
                symbols.append(Symbol(names[shndx] if is_section else name(st_name, s[6]),
                                      shndx, value, size, is_section))
    for s in sections:
        if s[1] == 4:  # RELA
            for j in range(s[5] // 24):
                off, info, addend = struct.unpack_from("<QQq", data, s[4] + j * 24)
                relocs.setdefault(s[7], {})[off] = (info & 0xFFFFFFFF, info >> 32, addend)
    return data, sections, symbols, relocs


def apply(word, rtype, value, place):
    """Fill the relocated field of word for target address value at place."""
    if rtype == 275:
        page = ((value >> 12) - (place >> 12)) & 0x1FFFFF
        return (word & ~0x60FFFFE0 & 0xFFFFFFFF) | ((page & 3) << 29) | ((page >> 2) << 5)
    if rtype in LO12_SHIFT:
        return (word & ~0x003FFC00 & 0xFFFFFFFF) | (((value & 0xFFF) >> LO12_SHIFT[rtype]) << 10)
    if rtype in (282, 283):
        return (word & 0xFC000000) | (((value - place) >> 2) & 0x03FFFFFF)
    return None  # GOT relocations need the original GOT slot; not handled yet.


def resolve(symbols, sym, addend, mapping):
    """Original address for a relocation target, or None."""
    if sym.is_section:
        for other in symbols:
            if (not other.is_section and other.shndx == sym.shndx and other.name in mapping
                    and other.value <= addend < other.value + max(other.size, 1)):
                return mapping[other.name] + addend - other.value
    if sym.name in mapping:
        return mapping[sym.name] + addend
    return None


def compare(obj, pairs, mapping):
    """Compare (symbol, address) pairs. Returns (results, unresolved).

    Each result is (symbol, address, size, diffs, lines) where diffs is the
    list of differing word offsets and lines describe them.
    """
    mapping = dict(mapping)
    for sym, addr in pairs:
        mapping.setdefault(sym, addr)
    data, sections, symbols, relocs = read_elf(obj)
    image = IMAGE.read_bytes()
    md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
    by_name = {s.name: s for s in symbols if not s.is_section}
    results, unresolved = [], set()
    for name, addr in pairs:
        if name not in by_name:
            results.append((name, addr, 0, None, [f"  symbol {name} not found in object"]))
            continue
        s = by_name[name]
        sec = sections[s.shndx]
        mine = bytearray(data[sec[4] + s.value: sec[4] + s.value + s.size])
        orig = image[addr: addr + s.size]
        srel = relocs.get(s.shndx, {})
        diffs = []
        for k in range(0, s.size, 4):
            a, = struct.unpack_from("<I", mine, k)
            b, = struct.unpack_from("<I", orig, k)
            mask = 0xFFFFFFFF
            rel = srel.get(s.value + k)
            if rel:
                rtype, symidx, addend = rel
                target = resolve(symbols, symbols[symidx], addend, mapping)
                patched = apply(a, rtype, target, addr + k) if target is not None else None
                if patched is None:
                    unresolved.add(f"{symbols[symidx].name}+{addend:#x} (type {rtype})")
                    mask = ~RELOC_MASKS.get(rtype, 0xFFFFFFFF) & 0xFFFFFFFF
                else:
                    a = patched
                    struct.pack_into("<I", mine, k, a)
            if (a & mask) != (b & mask):
                diffs.append(k)
        lines = []
        for k in diffs:
            mi = next(md.disasm(bytes(mine[k:k + 4]), BASE + addr + k), None)
            oi = next(md.disasm(orig[k:k + 4], BASE + addr + k), None)
            fmt = lambda i: f"{i.mnemonic} {i.op_str}" if i else "?"
            lines.append(f"  +{k:#05x}  ours: {mine[k:k+4].hex()} {fmt(mi):32} | orig: {orig[k:k+4].hex()} {fmt(oi)}")
        results.append((name, addr, s.size, diffs, lines))
    return results, unresolved


def main():
    args = sys.argv[1:]
    obj = args.pop(0)
    mapping, pairs = {}, []
    while args:
        a = args.pop(0)
        if a == "--map":
            n, v = args.pop(0).split("=")
            mapping[n] = int(v, 16) & 0xFFFFFFFF
        else:
            n, v = a.split("=")
            pairs.append((n, int(v, 16) & 0xFFFFFFFF))
    results, unresolved = compare(obj, pairs, mapping)
    failures = 0
    for name, addr, size, diffs, lines in results:
        ok = diffs == []
        failures += not ok
        status = "MATCH" if ok else ("MISSING" if diffs is None else f"MISMATCH ({len(diffs)} of {size // 4} words)")
        print(f"{addr:x} {name} size={size:#x}: {status}")
        for line in lines:
            print(line)
    if unresolved:
        print("unresolved relocations (masked):", ", ".join(sorted(unresolved)))
    sys.exit(1 if failures else 0)


if __name__ == "__main__":
    main()
