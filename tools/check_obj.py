"""Compare functions in an AArch64 ELF object with main.memory.bin.

Usage: check_obj.py OBJECT [--map NAME=ADDRESS ...] SYMBOL=ADDRESS [...]

SYMBOL=ADDRESS pairs name functions to compare. --map gives the original
address of a relocation target (a symbol, or a section name such as .bss for
section-relative relocations); compared functions are mapped automatically.
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
                symbols.append((names[shndx] if is_section else name(st_name, s[6]), shndx, value, size))
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
            mapping.setdefault(n, pairs[-1][1])

    data, sections, symbols, relocs = read_elf(obj)
    image = IMAGE.read_bytes()
    md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
    by_name = {s[0]: s for s in symbols}
    failures, unresolved = 0, set()
    for sym, addr in pairs:
        _, shndx, value, size = by_name[sym]
        sec = sections[shndx]
        mine = bytearray(data[sec[4] + value: sec[4] + value + size])
        orig = image[addr: addr + size]
        srel = relocs.get(shndx, {})
        diffs = []
        for k in range(0, size, 4):
            a, = struct.unpack_from("<I", mine, k)
            b, = struct.unpack_from("<I", orig, k)
            mask = 0xFFFFFFFF
            rel = srel.get(value + k)
            if rel:
                rtype, symidx, addend = rel
                target = symbols[symidx][0]
                patched = apply(a, rtype, mapping[target] + addend, addr + k) if target in mapping else None
                if patched is None:
                    unresolved.add(f"{target} (type {rtype})")
                    mask = ~RELOC_MASKS.get(rtype, 0xFFFFFFFF) & 0xFFFFFFFF
                else:
                    a = patched
                    struct.pack_into("<I", mine, k, a)
            if (a & mask) != (b & mask):
                diffs.append(k)
        status = "MATCH" if not diffs else f"MISMATCH ({len(diffs)} of {size // 4} words)"
        print(f"{addr:x} {sym} size={size:#x}: {status}")
        if diffs:
            failures += 1
            for k in diffs:
                mi = next(md.disasm(bytes(mine[k:k + 4]), BASE + addr + k), None)
                oi = next(md.disasm(orig[k:k + 4], BASE + addr + k), None)
                fmt = lambda i: f"{i.mnemonic} {i.op_str}" if i else "?"
                print(f"  +{k:#05x}  ours: {mine[k:k+4].hex()} {fmt(mi):32} | orig: {orig[k:k+4].hex()} {fmt(oi)}")
    if unresolved:
        print("unresolved relocations (masked):", ", ".join(sorted(unresolved)))
    sys.exit(1 if failures else 0)


if __name__ == "__main__":
    main()
