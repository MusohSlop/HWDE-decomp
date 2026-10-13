// Cleared singletons found by tools/family_scan.py --immediates: each allocates its block on the
// default heap the first time, keeps it in its global and clears it. They differ only in the block's
// size; the types and functions are named after the creating function's address.
// Status: matching/README.md.

class DefaultHeap {
public:
    void* allocate(unsigned int alignment, unsigned long size, int a, int b); // 0x710045c458
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

extern "C" void* memset(void* dest, int value, unsigned long size);

struct ClearedBlockd86d4 {
    unsigned char data[0x870];
};
extern ClearedBlockd86d4* gClearedBlockd86d4;

// 0x71000d86d4
void create_cleared_d86d4() {
    if (!gClearedBlockd86d4) {
        gClearedBlockd86d4 = static_cast<ClearedBlockd86d4*>(get_default_heap()->allocate(0x10, sizeof(ClearedBlockd86d4), 1, 0));
        memset(gClearedBlockd86d4, 0, sizeof(ClearedBlockd86d4));
    }
}

struct ClearedBlock1ff060 {
    unsigned char data[0x173c];
};
extern ClearedBlock1ff060* gClearedBlock1ff060;

// 0x71001ff060
void create_cleared_1ff060() {
    if (!gClearedBlock1ff060) {
        gClearedBlock1ff060 = static_cast<ClearedBlock1ff060*>(get_default_heap()->allocate(0x10, sizeof(ClearedBlock1ff060), 1, 0));
        memset(gClearedBlock1ff060, 0, sizeof(ClearedBlock1ff060));
    }
}

struct ClearedBlock204cb8 {
    unsigned char data[0x6ec];
};
extern ClearedBlock204cb8* gClearedBlock204cb8;

// 0x7100204cb8
void create_cleared_204cb8() {
    if (!gClearedBlock204cb8) {
        gClearedBlock204cb8 = static_cast<ClearedBlock204cb8*>(get_default_heap()->allocate(0x10, sizeof(ClearedBlock204cb8), 1, 0));
        memset(gClearedBlock204cb8, 0, sizeof(ClearedBlock204cb8));
    }
}

struct ClearedBlock209a44 {
    unsigned char data[0x6e];
};
extern ClearedBlock209a44* gClearedBlock209a44;

// 0x7100209a44
void create_cleared_209a44() {
    if (!gClearedBlock209a44) {
        gClearedBlock209a44 = static_cast<ClearedBlock209a44*>(get_default_heap()->allocate(0x10, sizeof(ClearedBlock209a44), 1, 0));
        memset(gClearedBlock209a44, 0, sizeof(ClearedBlock209a44));
    }
}

struct ClearedBlock20acc0 {
    unsigned char data[0xcf0];
};
extern ClearedBlock20acc0* gClearedBlock20acc0;

// 0x710020acc0
void create_cleared_20acc0() {
    if (!gClearedBlock20acc0) {
        gClearedBlock20acc0 = static_cast<ClearedBlock20acc0*>(get_default_heap()->allocate(0x10, sizeof(ClearedBlock20acc0), 1, 0));
        memset(gClearedBlock20acc0, 0, sizeof(ClearedBlock20acc0));
    }
}

struct ClearedBlock20b980 {
    unsigned char data[0xb40];
};
extern ClearedBlock20b980* gClearedBlock20b980;

// 0x710020b980
void create_cleared_20b980() {
    if (!gClearedBlock20b980) {
        gClearedBlock20b980 = static_cast<ClearedBlock20b980*>(get_default_heap()->allocate(0x10, sizeof(ClearedBlock20b980), 1, 0));
        memset(gClearedBlock20b980, 0, sizeof(ClearedBlock20b980));
    }
}

struct ClearedBlock214d98 {
    unsigned char data[0x5a];
};
extern ClearedBlock214d98* gClearedBlock214d98;

// 0x7100214d98
void create_cleared_214d98() {
    if (!gClearedBlock214d98) {
        gClearedBlock214d98 = static_cast<ClearedBlock214d98*>(get_default_heap()->allocate(0x10, sizeof(ClearedBlock214d98), 1, 0));
        memset(gClearedBlock214d98, 0, sizeof(ClearedBlock214d98));
    }
}
