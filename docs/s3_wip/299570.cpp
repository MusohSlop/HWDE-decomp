// WIP (third session): 299570, the 0x21e80-byte singleton's constructor (1,696 bytes), 45 off with registers
// abstracted (30 with the int group at +21aec/+14/+21be0/+21bc8/+21bc0 between the +21be4 and +21be8 stores). The
// members and their initialisation match; left: the original computes the +7cd0 memset's address right after the
// first 128-cell loop and the +7918 one before the first body memset (one more callee-saved register), and it
// stores the int group after the +21b70..+21b50 pointers. +7910/+7914 are written as bit patterns so that
// 320.0f is derived from 240.0f's register; +2c4/+2c8 (-1, 8) merge into one 64-bit store.
// Maps: got:_ZTV12LayoutHandle=0x7100c22f00 _ZN12LayoutSpriteC1Ev=0x71001ef52c _ZN13LightResourceC1Ev=0x71005d2744
// _ZN10ScrollListC1Ev=0x71001f8700 _ZN8SlotList5resetEv=0x7100299c10, function _ZN15Singleton29b554C2Ev.

extern "C" void* memset(void*, int, unsigned long);

struct HandleState {
    long id;                     // +08
    short a;                     // +10
    short b;                     // +12

    HandleState() : id(-1), a(0), b(0) {}
};

class LayoutHandle : public HandleState {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
};

struct LayoutSprite {
    LayoutSprite();              // 0x71001ef52c
    virtual void v00();
    int flags;                   // +08
    unsigned char padc[0x3c];
};

struct LightResource {
    LightResource();             // 0x71005d2744
    void* data[0x22];
};

struct ScrollList {
    ScrollList();                // 0x71001f8700
    void* data[0x14];
};

// A slot: a pointer and a layout handle.
struct HandleSlot {
    void* p;                     // +00
    LayoutHandle handle;         // +08
};

// The list at +378: cleared by its reset (0x7100299c10), ten slots after its header.
struct SlotList {
    void reset();                // 0x7100299c10
    unsigned char header[0xa0];  // +00
    HandleSlot slots[10];        // +a0
};

class Singleton29b554 {
public:
    Singleton29b554();

    long l0;                     // +00
    bool b8;                     // +08
    int ic;                      // +0c
    int i10;                     // +10
    int i14;                     // +14
    unsigned char pad18[0x8];
    void* p20;                   // +20
    HandleSlot slots_a[4];       // +28
    unsigned char pada8[0x98];
    void* p140;                  // +140
    HandleSlot slots_b[4];       // +148
    unsigned char pad1c8[0x98];
    void* p260;                  // +260
    unsigned char pad268[0x8];
    void* p270;                  // +270
    unsigned char pad278[0x8];
    void* p280;                  // +280
    void* p288;                  // +288
    void* p290;                  // +290
    unsigned char pad298[0x20];
    bool b2b8;                   // +2b8
    int i2bc;                    // +2bc
    int i2c0;                    // +2c0
    int i2c4;                    // +2c4
    int i2c8;                    // +2c8
    int i2cc;                    // +2cc
    unsigned char block2d0[0x60]; // +2d0
    LayoutHandle h330;           // +330
    void* p348[6];               // +348
    SlotList list;               // +378
    unsigned char pad558[0xa0];
    LayoutSprite sprites_a[200]; // +5f8
    LayoutSprite sprites_b[200]; // +3e38
    unsigned char pad7678[0x78];
    LightResource light_a;       // +76f0
    LightResource light_b;       // +7800
    float w7910;                 // +7910
    float h7914;                 // +7914
    unsigned char block7918[0x100]; // +7918
    unsigned char pad7a18[0x20];
    ScrollList lists_a[4];       // +7a38
    LayoutHandle h7cb8;          // +7cb8
    unsigned char block7cd0[0x68]; // +7cd0
    unsigned char pad7d38[0x20];
    LayoutHandle h7d58;          // +7d58
    unsigned char block7d70[0xf8]; // +7d70
    LayoutSprite cells_a[128];   // +7e68
    LayoutSprite cells_b[128];   // +a268
    LayoutSprite cells_c[128];   // +c668
    LayoutSprite cells_d[128];   // +ea68
    int i10e68;                  // +10e68
    unsigned char pad10e6c[0xfc04];
    HandleSlot slots_c[128];     // +20a70
    bool b21a70;                 // +21a70
    int i21a74;                  // +21a74
    bool b21a78;                 // +21a78
    int i21a7c;                  // +21a7c
    int i21a80;                  // +21a80
    bool b21a84;                 // +21a84
    void* p21a88;                // +21a88
    void* p21a90;                // +21a90
    void* p21a98;                // +21a98
    void* p21aa0;                // +21aa0
    void* p21aa8;                // +21aa8
    LayoutHandle h21ab0;         // +21ab0
    void* p21ac8;                // +21ac8
    LayoutHandle h21ad0;         // +21ad0
    bool b21ae8;                 // +21ae8
    int i21aec;                  // +21aec
    void* p21af0;                // +21af0
    unsigned char pad21af8[0x8];
    void* p21b00;                // +21b00
    LayoutHandle h21b08;         // +21b08
    void* p21b20;                // +21b20
    unsigned char pad21b28[0x8];
    void* p21b30;                // +21b30
    LayoutHandle h21b38;         // +21b38
    void* p21b50;                // +21b50
    void* p21b58;                // +21b58
    void* p21b60;                // +21b60
    void* p21b68;                // +21b68
    void* p21b70;                // +21b70
    unsigned char pad21b78[0x8];
    void* p21b80;                // +21b80
    LayoutHandle h21b88;         // +21b88
    unsigned char pad21ba0[0x8];
    LayoutHandle h21ba8;         // +21ba8
    void* p21bc0;                // +21bc0
    int i21bc8;                  // +21bc8
    unsigned char pad21bcc[0x10];
    int i21bdc;                  // +21bdc
    int i21be0;                  // +21be0
    int i21be4;                  // +21be4
    int i21be8;                  // +21be8
    int i21bec;                  // +21bec
    ScrollList lists_b[4];       // +21bf0
    int i21e70;                  // +21e70
};

Singleton29b554::Singleton29b554() {
    i21bdc = 0;
    p20 = nullptr;
    p140 = nullptr;
    p260 = nullptr;
    p270 = nullptr;
    b8 = false;
    l0 = 0;
    ic = 0;
    b2b8 = false;
    p290 = nullptr;
    p288 = nullptr;
    p280 = nullptr;
    i2bc = -1;
    i2c0 = -1;
    i2c4 = -1;
    i2c8 = 8;
    i2cc = 4;
    memset(block2d0, 0, sizeof(block2d0));
    p348[5] = nullptr;
    p348[4] = nullptr;
    p348[3] = nullptr;
    p348[2] = nullptr;
    p348[1] = nullptr;
    p348[0] = nullptr;
    list.reset();
    p21ac8 = nullptr;
    p21aa8 = nullptr;
    p21aa0 = nullptr;
    p21a98 = nullptr;
    p21a90 = nullptr;
    p21a88 = nullptr;
    *reinterpret_cast<int*>(&w7910) = 0x43a00000;
    *reinterpret_cast<int*>(&h7914) = 0x43700000;
    i10 = 0;
    b21a70 = false;
    i21a74 = 0;
    b21a78 = false;
    i21a7c = 0;
    i21a80 = 0;
    b21a84 = true;
    b21ae8 = false;
    p21af0 = nullptr;
    p21b00 = nullptr;
    p21b20 = nullptr;
    p21b30 = nullptr;
    p21b80 = nullptr;
    p21b70 = nullptr;
    p21b68 = nullptr;
    p21b60 = nullptr;
    p21b58 = nullptr;
    p21b50 = nullptr;
    i21aec = 0;
    i14 = 0;
    i21be0 = 0;
    i21bc8 = 0;
    p21bc0 = nullptr;
    i21be4 = 6;
    i21be8 = 0xff;
    i21bec = 0xff;
    memset(block7cd0, 0, sizeof(block7cd0));
    memset(block7d70, 0, sizeof(block7d70));
    memset(block7918, 0, sizeof(block7918));
    for (int i = 0; i < 128; i++) {
        cells_a[i].flags |= 0x80;
        cells_b[i].flags |= 0x80;
        cells_c[i].flags |= 0x80;
        cells_d[i].flags |= 0x80;
    }
    i10e68 = 0;
    i21e70 = 0;
}
