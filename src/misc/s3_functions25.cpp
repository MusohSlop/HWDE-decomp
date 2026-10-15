// Constructors written by hand (third session): screens, a set of pools and a frame list built from many out-of-line
// parts. Names are descriptive placeholders. Status: matching/README.md.

extern "C" void* memset(void*, int, unsigned long);

// The panel base (0x40 bytes), constructed out of line.
class PanelBase_316a64 {
public:
    PanelBase_316a64();                                                     // 0x7100316a64
    virtual ~PanelBase_316a64();
    unsigned char pad8[0x38];
};

struct LayoutLine {
    LayoutLine();                                                           // 0x71001f1594
    unsigned char data[0x28];
};

// A sprite (0x48 bytes): flags at +08, bit 7 dirty.
struct LayoutSprite {
    LayoutSprite();                                                         // 0x71001ef52c
    virtual void v00();
    int flags;                   // +08
    unsigned char padc[0x3c];
};

struct LayoutFrame {
    LayoutFrame();                                                          // 0x71001f0140
    unsigned char data[0x88];
};

struct Part31de28 {
    Part31de28();                                                           // 0x710031de28
    unsigned char data[0xaa00];
};

struct Part31dfe4 {
    Part31dfe4();                                                           // 0x710031dfe4
    unsigned char data[0x1350];
};

struct Part32af38 {
    Part32af38();                                                           // 0x710032af38
    unsigned char data[0x3a140];
};

struct Part325b48 {
    Part325b48();                                                           // 0x7100325b48
    unsigned char data[0x1560];
};

struct Part325d10 {
    Part325d10();                                                           // 0x7100325d10
    unsigned char data[0x11b0];
};

// A slot: an id and a sprite, reset after construction.
struct Slot31d204 {
    void reset() {
        id = -1;
        sprite.flags |= 0x80;
        a50 = 0;
        a54 = 0;
        p70 = 0;
    }

    int id;                      // +00
    LayoutSprite sprite;         // +08
    int a50;                     // +50
    int a54;                     // +54
    unsigned char pad58[0x18];
    long p70;                    // +70
    unsigned char pad78[0x8];
};

struct Entry31d204 {
    Entry31d204() : a(-1), b(-1), c(3), d(0xf6) {}

    int a;                       // +00
    int b;                       // +04
    int c;                       // +08
    int d;                       // +0c
    unsigned char pad10[0x40];
};

struct Group31d204 {
    Group31d204() : bytes() {}

    Entry31d204 entries[7];      // +000
    unsigned char bytes[0xc9];   // +230
    unsigned char pad2f9[0x7];
};

// 0x710031d204: a screen on the panel base (vtable GOT 0x7100c2ae00): its parts constructed in member order, the slots
// reset and the names cleared by a loop (the memset LoopIdiom makes of it comes after tail-call marking, so it is a
// plain call before the return).
class Screen31d204 : public PanelBase_316a64 {
public:
    Screen31d204();
    ~Screen31d204();

    int i40;                     // +40
    int i44;                     // +44
    int i48;                     // +48
    int i4c;                     // +4c
    void* p50;                   // +50
    void* p58;                   // +58
    int i60;                     // +60
    int i64;                     // +64
    int i68;                     // +68
    bool b6c;                    // +6c
    unsigned char names[100];    // +6d
    int id4;                     // +d4
    int id8;                     // +d8
    int idc;                     // +dc
    bool be0;                    // +e0
    int ie4;                     // +e4
    LayoutLine lines[44];        // +e8
    Part31de28 boards[2];        // +7c8
    LayoutSprite sprites_a[8];   // +15bc8
    LayoutFrame frames[32];      // +15e08
    LayoutSprite sprites_b[10];  // +16f08
    LayoutSprite sprites_c[100]; // +171d8
    unsigned char pad18df8[0x8];
    Slot31d204 slots[4];         // +18e00
    Part31dfe4 cards[9];         // +19000
    Group31d204 groups[2];       // +23dd0
    LayoutSprite sprites_d[4];   // +243d0
    LayoutFrame frames_b[21];    // +244f0
    unsigned char pad25018[0x10];
    void* p25028;                // +25028
    unsigned char pad25030[0x10];
    int i25040;                  // +25040
    unsigned char pad25044[0xc];
    Part32af38 big;              // +25050
    Part325b48 rows[4];          // +5f190
    Part325d10 cols[6];          // +64710
};

Screen31d204::Screen31d204()
    : i40(0), i48(2), i4c(-1), p50(nullptr), p58(nullptr), i60(-1), i64(0), i68(0), b6c(false), id4(-1), id8(0),
      be0(false), ie4(0), p25028(nullptr), i25040(0) {
    for (int k = 0; k < 4; k++)
        slots[k].reset();
    for (int i = 0; i < 100; i++)
        names[i] = 0;
}

struct SubInit31364 {
    SubInit31364();                                                         // 0x7100031364
    void init();                                                            // 0x7100031378
    unsigned char data[0x10];
};

struct PoolItem {
    SubInit31364 sub;
    unsigned char pad10[0x8];
};

// 0x71000d04c4: four pools of items with byte tables (vtable GOT 0x7100c21d78) and three parts, the parts set up and
// the pools cleared again.
class PoolSet0d04c4 {
public:
    PoolSet0d04c4();
    virtual ~PoolSet0d04c4();

    void* p8;                         // +08
    SubInit31364 a;                   // +10
    SubInit31364 b;                   // +20
    SubInit31364 c;                   // +30
    PoolItem items_a[1260];           // +40
    unsigned char used_a[0x2790];     // +7660
    PoolItem items_b[60];             // +9df0
    unsigned char used_b[0x2790];     // +a390
    PoolItem items_c[210];            // +cb20
    unsigned char used_c[0x698];      // +ded0
    PoolItem items_d[10];             // +e568
    unsigned char used_d[0x698];      // +e658
};

PoolSet0d04c4::PoolSet0d04c4() : p8(nullptr), used_a(), used_b(), used_c(), used_d() {
    a.init();
    b.init();
    c.init();
    unsigned char* bytes = reinterpret_cast<unsigned char*>(items_a);
    for (int i = 0; i < 0xecb0; i++)
        bytes[i] = 0;
}

// The base of 2d14dc's screen (0x28 bytes), constructed out of line.
class Base3c7188 {
public:
    Base3c7188();                                                           // 0x71003c7188
    virtual ~Base3c7188();
    unsigned char pad8[0x20];
};

// 0x71002d14dc: a screen on the 3c7188 base (vtable GOT 0x7100c2aaa0): a sprite, eleven icons (unrolled) and 256
// cells (a loop counting bytes, as the array constructor's loop becomes).
class Screen2d14dc : public Base3c7188 {
public:
    Screen2d14dc();
    ~Screen2d14dc();

    int i28;                     // +28
    int i2c;                     // +2c
    int i30;                     // +30
    int i34;                     // +34
    LayoutSprite sprite;         // +38
    int i80;                     // +80
    void* p88;                   // +88
    void* p90;                   // +90
    LayoutSprite icons[11];      // +98
    LayoutSprite cells[256];     // +3b0
    int i4bb0;                   // +4bb0
};

Screen2d14dc::Screen2d14dc() : i28(0), i30(0), i80(0), p88(nullptr), p90(nullptr), i4bb0(0) {}

struct HandleState {
    long id;                     // +08
    short a;                     // +10
    short b;                     // +12

    HandleState() : id(-1), a(0), b(0) {}
};

// Layout handle; its vtable lives in the effect manager unit (GOT 0x7100c22f00).
class LayoutHandle : public HandleState {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
};

struct LightResource {
    LightResource();                                                        // 0x71005d2744
    void* data[0x22];
};

class EffectManager {
public:
    void attach(LightResource* res, void* owner);                           // 0x71001e26dc
};
// Reached through the GOT slot at 0x7100c22a00.
extern EffectManager* gEffectManager;
extern const char kMid2cfc60Name[] __attribute__((visibility("hidden")));  // 0x71007d82d4

struct Tail2cf74c {
    Tail2cf74c();                                                           // 0x71002cf74c
    void* data[2];
};

// A pointer's index and sprite. The index starts a struct of its own: as a plain member right after the sprite
// array, its address would be the array's end and stay live across the array's loop.
struct Pointer4970 {
    Pointer4970() : index(0) {}

    int index;                   // +00
    LayoutSprite sprite;         // +08
};

// The middle base of 2cff80's family (vtable GOT 0x7100c2aa68), inline here: a light resource attached to the
// effect manager, 256 sprites and a pointer.
class Mid2cfc60 : public Base3c7188 {
public:
    Mid2cfc60() : i28(0), p140(nullptr), p160(nullptr), p168(nullptr), i49c0(0) {
        p49d0 = nullptr;
        p49c8 = nullptr;
        b49d8 = true;
        i49e0 = 0x41e9;
        b49e4 = true;
        i49e8 = 1;
        name = kMid2cfc60Name;
        b49f8 = false;
        p158 = nullptr;
        p148 = nullptr;
        p150 = nullptr;
        gEffectManager->attach(&res, nullptr);
    }
    virtual ~Mid2cfc60();

    int i28;                     // +28
    LightResource res;           // +30
    void* p140;                  // +140
    void* p148;                  // +148
    void* p150;                  // +150
    void* p158;                  // +158
    void* p160;                  // +160
    void* p168;                  // +168
    LayoutSprite sprites[256];   // +170
    Pointer4970 pointer;         // +4970
    int i49c0;                   // +49c0
    void* p49c8;                 // +49c8
    void* p49d0;                 // +49d0
    bool b49d8;                  // +49d8
    unsigned char pad49d9[7];
    int i49e0;                   // +49e0
    bool b49e4;                  // +49e4
    int i49e8;                   // +49e8
    const char* name;            // +49f0
    bool b49f8;                  // +49f8
};

// 0x71002cfc60: a screen on the middle base (vtable GOT 0x7100c2aa98): 256 cells, 35 icons (unrolled), a layout
// handle, a second light resource and a last part (its constructor a tail call).
class Screen2cfc60 : public Mid2cfc60 {
public:
    Screen2cfc60();
    ~Screen2cfc60();

    unsigned char pad4a00[0x68];
    LayoutSprite cells[256];     // +4a68
    LayoutSprite icons[35];      // +9268
    LayoutHandle handle;         // +9c40
    void* p9c58;                 // +9c58
    void* p9c60;                 // +9c60
    short s9c68;                 // +9c68
    LightResource res2;          // +9c70
    Tail2cf74c tail;             // +9d80
};

Screen2cfc60::Screen2cfc60() : p9c58(nullptr), p9c60(nullptr), s9c68(1) {}

// 0x710033be48: fifty layout frames (unrolled) and a layout handle; the list in front is cleared last, by a body
// memset.
class Frames33be48 {
public:
    Frames33be48();

    void* items[7];              // +00
    void* p38;                   // +38
    void* p40;                   // +40
    LayoutFrame frames[50];      // +48
    bool b1ad8;                  // +1ad8
    void* p1ae0;                 // +1ae0
    LayoutHandle handle;         // +1ae8
};

Frames33be48::Frames33be48() : p38(nullptr), p40(nullptr), b1ad8(false), p1ae0(nullptr) {
    memset(items, 0, sizeof(items));
}