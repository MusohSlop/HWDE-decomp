// Clamped weekday-style lookups found by tools/family_scan.py --immediates: each reads one of seven
// byte settings, falling back to the last one for an index out of range. They differ only in the
// table; types and functions are named after their address. The original tests the index twice
// (an unsigned range test, then the sign again), which only this form reproduces.
// Status: matching/README.md.

struct SevenBytes205670 {
    unsigned char pad[0x67f];
    unsigned char values[7];  // +67f
};

// 0x7100205670
unsigned char seven_byte_205670(SevenBytes205670* table, int index) {
    bool valid = index >= 0 ? (unsigned)index < 7 : false;
    return valid && index >= 0 ? table->values[index] : table->values[6];
}

struct SevenBytes205694 {
    unsigned char pad[0x671];
    unsigned char values[7];  // +671
};

// 0x7100205694
unsigned char seven_byte_205694(SevenBytes205694* table, int index) {
    bool valid = index >= 0 ? (unsigned)index < 7 : false;
    return valid && index >= 0 ? table->values[index] : table->values[6];
}

struct SevenBytes2056b8 {
    unsigned char pad[0x678];
    unsigned char values[7];  // +678
};

// 0x71002056b8
unsigned char seven_byte_2056b8(SevenBytes2056b8* table, int index) {
    bool valid = index >= 0 ? (unsigned)index < 7 : false;
    return valid && index >= 0 ? table->values[index] : table->values[6];
}

struct SevenBytes2056dc {
    unsigned char pad[0x686];
    unsigned char values[7];  // +686
};

// 0x71002056dc
unsigned char seven_byte_2056dc(SevenBytes2056dc* table, int index) {
    bool valid = index >= 0 ? (unsigned)index < 7 : false;
    return valid && index >= 0 ? table->values[index] : table->values[6];
}

struct SevenBytes205734 {
    unsigned char pad[0x694];
    unsigned char values[7];  // +694
};

// 0x7100205734
unsigned char seven_byte_205734(SevenBytes205734* table, int index) {
    bool valid = index >= 0 ? (unsigned)index < 7 : false;
    return valid && index >= 0 ? table->values[index] : table->values[6];
}

struct SevenBytes20578c {
    unsigned char pad[0x6a2];
    unsigned char values[7];  // +6a2
};

// 0x710020578c
unsigned char seven_byte_20578c(SevenBytes20578c* table, int index) {
    bool valid = index >= 0 ? (unsigned)index < 7 : false;
    return valid && index >= 0 ? table->values[index] : table->values[6];
}
