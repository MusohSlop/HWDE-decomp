// Bit-set updates on the game object found by tools/family_scan.py --immediates (the setters
// paired with misc/bit_tests.cpp): each sets or clears one bit of a bit set at a fixed offset, after
// a range check on the id. They differ only in the limit and the offset; functions are named after
// their address. Status: matching/README.md.

struct BitField202730 {
    unsigned char pad[0x4];
    unsigned int bits[1];     // +4
};

// 0x7100202730: ids up to 0x7f
void set_bit_202730(BitField202730* set, int id, unsigned char on) {
    if (static_cast<unsigned int>(id) > 0x7f)
        return;
    if (on)
        set->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
    else
        set->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
}

struct BitField2029dc {
    unsigned char pad[0x18];
    unsigned int bits[1];     // +18
};

// 0x71002029dc: ids up to 0x45
void set_bit_2029dc(BitField2029dc* set, int id, unsigned char on) {
    if (static_cast<unsigned int>(id) > 0x45)
        return;
    if (on)
        set->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
    else
        set->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
}

struct BitField202a58 {
    unsigned char pad[0x24];
    unsigned int bits[1];     // +24
};

// 0x7100202a58: ids up to 0xf9
void set_bit_202a58(BitField202a58* set, int id, unsigned char on) {
    if (static_cast<unsigned int>(id) > 0xf9)
        return;
    if (on)
        set->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
    else
        set->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
}

struct BitField202ad4 {
    unsigned char pad[0x44];
    unsigned int bits[1];     // +44
};

// 0x7100202ad4: ids up to 0x3f
void set_bit_202ad4(BitField202ad4* set, int id, unsigned char on) {
    if (static_cast<unsigned int>(id) > 0x3f)
        return;
    if (on)
        set->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
    else
        set->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
}

struct BitField202c20 {
    unsigned char pad[0x60];
    unsigned int bits[1];     // +60
};

// 0x7100202c20: ids up to 0x8
void set_bit_202c20(BitField202c20* set, int id, unsigned char on) {
    if (static_cast<unsigned int>(id) > 0x8)
        return;
    if (on)
        set->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
    else
        set->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
}

struct BitField202db0 {
    unsigned char pad[0x1a08];
    unsigned int bits[1];     // +1a08
};

// 0x7100202db0: ids up to 0x63
void set_bit_202db0(BitField202db0* set, int id, unsigned char on) {
    if (static_cast<unsigned int>(id) > 0x63)
        return;
    if (on)
        set->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
    else
        set->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
}

struct BitField202e2c {
    unsigned char pad[0x68];
    unsigned int bits[1];     // +68
};

// 0x7100202e2c: ids up to 0x12b
void set_bit_202e2c(BitField202e2c* set, int id, unsigned char on) {
    if (static_cast<unsigned int>(id) > 0x12b)
        return;
    if (on)
        set->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
    else
        set->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
}

struct BitField2031b4 {
    unsigned char pad[0x140];
    unsigned int bits[1];     // +140
};

// 0x71002031b4: ids up to 0x9
void set_bit_2031b4(BitField2031b4* set, int id, unsigned char on) {
    if (static_cast<unsigned int>(id) > 0x9)
        return;
    if (on)
        set->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
    else
        set->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
}

struct BitField203230 {
    unsigned char pad[0x144];
    unsigned int bits[1];     // +144
};

// 0x7100203230: ids up to 0x9
void set_bit_203230(BitField203230* set, int id, unsigned char on) {
    if (static_cast<unsigned int>(id) > 0x9)
        return;
    if (on)
        set->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
    else
        set->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
}

struct BitField2032ac {
    unsigned char pad[0x148];
    unsigned int bits[1];     // +148
};

// 0x71002032ac: ids up to 0x9
void set_bit_2032ac(BitField2032ac* set, int id, unsigned char on) {
    if (static_cast<unsigned int>(id) > 0x9)
        return;
    if (on)
        set->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
    else
        set->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
}
