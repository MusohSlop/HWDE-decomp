// Unchecked bit-set tests and updates on the game object found by tools/family_scan.py --immediates
// (the shape of Game::unlocked in misc/accessors.cpp): each tests, sets or clears one bit of a bit
// set at a fixed offset. They differ only in the offset; functions are named after their address.
// Status: matching/README.md.

struct Flags203d0c {
    unsigned char pad[0x1994];
    unsigned int bits[1];     // +1994
};

// 0x7100203d0c
unsigned char test_flag_203d0c(Flags203d0c* set, int id) {
    return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
}

struct Flags203dfc {
    unsigned char pad[0x19a0];
    unsigned int bits[1];     // +19a0
};

// 0x7100203dfc
unsigned char test_flag_203dfc(Flags203dfc* set, int id) {
    return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
}

struct Flags203ed4 {
    unsigned char pad[0x19ac];
    unsigned int bits[1];     // +19ac
};

// 0x7100203ed4
unsigned char test_flag_203ed4(Flags203ed4* set, int id) {
    return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
}

struct Flags203fac {
    unsigned char pad[0x19b8];
    unsigned int bits[1];     // +19b8
};

// 0x7100203fac
unsigned char test_flag_203fac(Flags203fac* set, int id) {
    return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
}

struct Flags204034 {
    unsigned char pad[0x19c8];
    unsigned int bits[1];     // +19c8
};

// 0x7100204034
unsigned char test_flag_204034(Flags204034* set, int id) {
    return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
}

struct Flags2040bc {
    unsigned char pad[0x19d8];
    unsigned int bits[1];     // +19d8
};

// 0x71002040bc
unsigned char test_flag_2040bc(Flags2040bc* set, int id) {
    return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
}

struct Flags2045a0 {
    unsigned char pad[0x2588];
    unsigned int bits[1];     // +2588
};

// 0x71002045a0
unsigned char test_flag_2045a0(Flags2045a0* set, int id) {
    return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
}

struct Flags204674 {
    unsigned char pad[0x26d4];
    unsigned int bits[1];     // +26d4
};

// 0x7100204674
unsigned char test_flag_204674(Flags204674* set, int id) {
    return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
}

struct Flags206368 {
    unsigned char pad[0x40];
    unsigned int bits[1];     // +40
};

// 0x7100206368
unsigned char test_flag_206368(Flags206368* set, int id) {
    return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
}

struct Flags203fe0 {
    unsigned char pad[0x19b8];
    unsigned int bits[1];     // +19b8
};

// 0x7100203fe0
void update_flag_203fe0(Flags203fe0* set, int id, unsigned char on) {
    if (on)
        set->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
    else
        set->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
}

struct Flags204068 {
    unsigned char pad[0x19c8];
    unsigned int bits[1];     // +19c8
};

// 0x7100204068
void update_flag_204068(Flags204068* set, int id, unsigned char on) {
    if (on)
        set->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
    else
        set->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
}

struct Flags20454c {
    unsigned char pad[0x2588];
    unsigned int bits[1];     // +2588
};

// 0x710020454c
void update_flag_20454c(Flags20454c* set, int id, unsigned char on) {
    if (on)
        set->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
    else
        set->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
}

struct Flags204620 {
    unsigned char pad[0x26d4];
    unsigned int bits[1];     // +26d4
};

// 0x7100204620
void update_flag_204620(Flags204620* set, int id, unsigned char on) {
    if (on)
        set->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
    else
        set->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
}

struct Flags206314 {
    unsigned char pad[0x40];
    unsigned int bits[1];     // +40
};

// 0x7100206314
void update_flag_206314(Flags206314* set, int id, unsigned char on) {
    if (on)
        set->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
    else
        set->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
}
