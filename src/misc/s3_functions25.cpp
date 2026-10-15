// Screen constructors written by hand (third session): large screens built from many out-of-line parts. Names are
// descriptive placeholders. Status: matching/README.md.

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
