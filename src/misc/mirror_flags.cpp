// Mirrored flag updates found by tools/family_scan.py --immediates: each sets or clears one bit in a
// bit set of the given save block and in the matching bit set of the live game object. They differ
// only in the bit set; types and functions are named after their address. Status: matching/README.md.

struct SaveFlags203d40 {
    unsigned char pad[0x1994];
    unsigned int bits[1];     // +1994
};
struct GameFlags203d40 {
    unsigned char pad[0x34764];
    unsigned int bits[1];     // +34764
};
struct SaveFlags203e30 {
    unsigned char pad[0x19a0];
    unsigned int bits[1];     // +19a0
};
struct GameFlags203e30 {
    unsigned char pad[0x34770];
    unsigned int bits[1];     // +34770
};
struct SaveFlags203f08 {
    unsigned char pad[0x19ac];
    unsigned int bits[1];     // +19ac
};
struct GameFlags203f08 {
    unsigned char pad[0x3477c];
    unsigned int bits[1];     // +3477c
};

// Reached through the GOT slot at 0x7100c23258.
extern void* gGame;

// 0x7100203d40
void mirror_flag_203d40(SaveFlags203d40* save, int id, unsigned char on) {
    if (on) {
        save->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
        static_cast<GameFlags203d40*>(gGame)->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
    } else {
        save->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
        static_cast<GameFlags203d40*>(gGame)->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
    }
}

// 0x7100203e30
void mirror_flag_203e30(SaveFlags203e30* save, int id, unsigned char on) {
    if (on) {
        save->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
        static_cast<GameFlags203e30*>(gGame)->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
    } else {
        save->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
        static_cast<GameFlags203e30*>(gGame)->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
    }
}

// 0x7100203f08
void mirror_flag_203f08(SaveFlags203f08* save, int id, unsigned char on) {
    if (on) {
        save->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
        static_cast<GameFlags203f08*>(gGame)->bits[id / 32] |= static_cast<unsigned int>(1ul << (id % 32));
    } else {
        save->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
        static_cast<GameFlags203f08*>(gGame)->bits[id / 32] &= ~static_cast<unsigned int>(1ul << (id % 32));
    }
}
