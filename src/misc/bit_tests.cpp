// Bit-set tests on the game object found by tools/family_scan.py --immediates (the same shape as
// game_has_flag and Progress::has in misc/accessors.cpp): each tests one bit of a bit set at a fixed
// offset, after a range check on the id. They differ only in the limit and the offset; functions are
// named after their address. Status: matching/README.md.

struct BitSet2029a8 {
    unsigned char pad[0x18];
    unsigned int bits[1];     // +18
};

// 0x71002029a8: ids up to 0x45
unsigned char has_bit_2029a8(BitSet2029a8* set, int id) {
    if (static_cast<unsigned int>(id) <= 0x45)
        return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
    return 0;
}

struct BitSet202a24 {
    unsigned char pad[0x24];
    unsigned int bits[1];     // +24
};

// 0x7100202a24: ids up to 0xf9
unsigned char has_bit_202a24(BitSet202a24* set, int id) {
    if (static_cast<unsigned int>(id) <= 0xf9)
        return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
    return 0;
}

struct BitSet202aa0 {
    unsigned char pad[0x44];
    unsigned int bits[1];     // +44
};

// 0x7100202aa0: ids up to 0x3f
unsigned char has_bit_202aa0(BitSet202aa0* set, int id) {
    if (static_cast<unsigned int>(id) <= 0x3f)
        return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
    return 0;
}

struct BitSet202b1c {
    unsigned char pad[0x4c];
    unsigned int bits[1];     // +4c
};

// 0x7100202b1c: ids up to 0x4a
unsigned char has_bit_202b1c(BitSet202b1c* set, int id) {
    if (static_cast<unsigned int>(id) <= 0x4a)
        return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
    return 0;
}

struct BitSet202bec {
    unsigned char pad[0x60];
    unsigned int bits[1];     // +60
};

// 0x7100202bec: ids up to 0x8
unsigned char has_bit_202bec(BitSet202bec* set, int id) {
    if (static_cast<unsigned int>(id) <= 0x8)
        return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
    return 0;
}

struct BitSet202c68 {
    unsigned char pad[0x64];
    unsigned int bits[1];     // +64
};

// 0x7100202c68: ids up to 0x4
unsigned char has_bit_202c68(BitSet202c68* set, int id) {
    if (static_cast<unsigned int>(id) <= 0x4)
        return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
    return 0;
}

struct BitSet202cec {
    unsigned char pad[0x1a00];
    unsigned int bits[1];     // +1a00
};

// 0x7100202cec: ids up to 0x3f
unsigned char has_bit_202cec(BitSet202cec* set, int id) {
    if (static_cast<unsigned int>(id) <= 0x3f)
        return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
    return 0;
}

struct BitSet202d7c {
    unsigned char pad[0x1a08];
    unsigned int bits[1];     // +1a08
};

// 0x7100202d7c: ids up to 0x63
unsigned char has_bit_202d7c(BitSet202d7c* set, int id) {
    if (static_cast<unsigned int>(id) <= 0x63)
        return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
    return 0;
}

struct BitSet202df8 {
    unsigned char pad[0x68];
    unsigned int bits[1];     // +68
};

// 0x7100202df8: ids up to 0x12b
unsigned char has_bit_202df8(BitSet202df8* set, int id) {
    if (static_cast<unsigned int>(id) <= 0x12b)
        return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
    return 0;
}

struct BitSet2031fc {
    unsigned char pad[0x144];
    unsigned int bits[1];     // +144
};

// 0x71002031fc: ids up to 0x9
unsigned char has_bit_2031fc(BitSet2031fc* set, int id) {
    if (static_cast<unsigned int>(id) <= 0x9)
        return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
    return 0;
}

struct BitSet203278 {
    unsigned char pad[0x148];
    unsigned int bits[1];     // +148
};

// 0x7100203278: ids up to 0x9
unsigned char has_bit_203278(BitSet203278* set, int id) {
    if (static_cast<unsigned int>(id) <= 0x9)
        return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
    return 0;
}

struct BitSet20341c {
    unsigned char pad[0x138];
    unsigned int bits[1];     // +138
};

// 0x710020341c: ids up to 0x31f
unsigned char has_bit_20341c(BitSet20341c* set, int id) {
    if (static_cast<unsigned int>(id) <= 0x31f)
        return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
    return 0;
}

struct BitSet204444 {
    unsigned char pad[0x255c];
    unsigned int bits[1];     // +255c
};

// 0x7100204444: ids up to 0x45
unsigned char has_bit_204444(BitSet204444* set, int id) {
    if (static_cast<unsigned int>(id) <= 0x45)
        return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
    return 0;
}
