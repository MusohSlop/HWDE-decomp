// Panels written by hand (third session) on the panel base that 2defc0's screen also uses: two light resources and
// an owner, then the panel's own parts; and 2eb9d4, a panel of the same screen without that base. Names are
// descriptive placeholders. Status: matching/README.md.

extern "C" void* memset(void* dest, int value, unsigned long size);

struct LightResource {
    LightResource();             // 0x71005d2744
    void* data[0x22];
};

struct SlotPool2dee48 {
    SlotPool2dee48();            // 0x71002dee48
    void* data[0x221];
};

struct LayoutFrame {
    LayoutFrame();               // 0x71001f0140
    void* data[0x11];
};

struct Part287efc { Part287efc(); int data[0x28]; };                       // 0x7100287efc
struct Part2dd3d4 { explicit Part2dd3d4(int mode); void* data[0x5c]; };    // 0x71002dd3d4
struct Part379e44 { Part379e44(); void* data[3]; };                        // 0x7100379e44
struct Part2d6c5c { Part2d6c5c(); void* data[0x39]; };                      // 0x71002d6c5c
struct Part2e2a90 { Part2e2a90(); void* data[0x441]; };                     // 0x71002e2a90

// The base of 2defc0's panels (vtable GOT 0x7100c2abb0): two light resources and its owner.
class PanelBase2defc0 {
public:
    explicit PanelBase2defc0(void* owner_) : b230(false), owner(owner_) {}
    virtual ~PanelBase2defc0();

    unsigned char pad8[0x8];
    LightResource res10;         // +10
    LightResource res120;        // +120
    bool b230;                   // +230
    void* owner;                 // +238
};

// A group of four pointers and a flag.
struct Group368 {
    Group368() : p0(nullptr), p8(nullptr), p10(nullptr), p18(nullptr), flag(false) {}

    void* p0;                    // +00
    void* p8;                    // +08
    void* p10;                   // +10
    void* p18;                   // +18
    unsigned char pad20[0x38];
    bool flag;                   // +58
    unsigned char pad59[0x7];
};

// 0x71002e8c64: a panel (vtable GOT 0x7100c2abe0) with five groups of four pointers and a flag (each group's
// initialisers in declaration order), ten slot pools, and two pointers reset in the body.
class Panel2e8c64 : public PanelBase2defc0 {
public:
    explicit Panel2e8c64(void* owner);
    ~Panel2e8c64();

    bool b240;                   // +240
    Part287efc part244;          // +244
    void* p2e8;                  // +2e8
    void* p2f0;                  // +2f0
    void* p2f8;                  // +2f8
    void* p300;                  // +300
    void* p308;                  // +308
    void* p310;                  // +310
    unsigned char pad318[0x28];
    void* p340;                  // +340
    void* p348;                  // +348
    void* p350;                  // +350
    void* p358;                  // +358
    void* p360;                  // +360
    Group368 groups[5];          // +368
    short s548;                  // +548
    unsigned char b54a;
    unsigned char b54b[2];       // +54b
    unsigned char pad54d[0x1b];
    Part2dd3d4 part568;          // +568
    Part379e44 part848;          // +848
    SlotPool2dee48 pools[10];    // +860
    void* pb2b0;                 // +b2b0
    void* pb2b8;                 // +b2b8
    int ib2c0;                   // +b2c0
};

Panel2e8c64::Panel2e8c64(void* owner)
    : PanelBase2defc0(owner), b240(false), p2e8(nullptr), p2f0(nullptr), p2f8(nullptr), p300(nullptr), p308(nullptr),
      p310(nullptr), p340(nullptr), p348(nullptr), p350(nullptr), s548(0), b54b(), part568(1), pb2b0(nullptr),
      pb2b8(nullptr), ib2c0(0) {
    p360 = nullptr;
    p358 = nullptr;
}

// Seven pointers, a flag and a count of 3 (0x80 bytes). The middle four pointers are reset in the body: as
// initialisers all seven would be cleared as one block (stored high to low after the flag), where the original
// clears the first two and the middle four apart.
struct Group80 {
    Group80() : p0(nullptr), p8(nullptr), p30(nullptr), flag(false), count(3), extra(0) {
        p10 = nullptr;
        p18 = nullptr;
        p20 = nullptr;
        p28 = nullptr;
    }

    void* p0;                    // +00
    void* p8;                    // +08
    void* p10;                   // +10
    void* p18;                   // +18
    void* p20;                   // +20
    void* p28;                   // +28
    void* p30;                   // +30
    unsigned char pad38[0x38];
    bool flag;                   // +70
    int count;                   // +74
    int extra;                   // +78
    unsigned char pad7c[0x4];
};

// 0x71002eeb18: a panel (vtable GOT 0x7100c2ac00) with twelve groups. Its first five bytes are separate fields: five
// zero stores become one cleared block, stored high to low (the byte at +244, then the word at +240), where an int and
// a bool would be stored in order; the four bytes at +2e9 likewise become one word store.
class Panel2eeb18 : public PanelBase2defc0 {
public:
    explicit Panel2eeb18(void* owner);
    ~Panel2eeb18();

    unsigned char b240;          // +240
    unsigned char b241;          // +241
    unsigned char b242;          // +242
    unsigned char b243;          // +243
    bool b244;                   // +244
    Part287efc part248;          // +248
    bool b2e8;                   // +2e8
    bool b2e9;                   // +2e9
    bool b2ea;                   // +2ea
    bool b2eb;                   // +2eb
    bool b2ec;                   // +2ec
    bool b2ed;                   // +2ed
    LightResource res2f0;        // +2f0
    LightResource res400;        // +400
    void* p510;                  // +510
    void* p518;                  // +518
    void* p520;                  // +520
    void* p528;                  // +528
    void* p530;                  // +530
    void* p538;                  // +538
    void* p540;                  // +540
    void* p548;                  // +548
    void* p550;                  // +550
    void* p558;                  // +558
    void* p560;                  // +560
    unsigned char pad568[0x28];
    void* p590;                  // +590
    Group80 groups[12];          // +598
    Part2dd3d4 partb98;          // +b98
    Part379e44 parte78;          // +e78
    SlotPool2dee48 pools_a[12];  // +e90
    LayoutFrame frames[128];     // +daf0
    int i11ef0;                  // +11ef0
    SlotPool2dee48 pools_b[9];   // +11ef8
};

Panel2eeb18::Panel2eeb18(void* owner)
    : PanelBase2defc0(owner), b240(0), b241(0), b242(0), b243(0), b244(false), b2e8(false), p510(nullptr),
      p518(nullptr), p520(nullptr), p528(nullptr), p550(nullptr), p558(nullptr), p560(nullptr), p590(nullptr),
      partb98(0), i11ef0(0) {
    b2ed = false;
    b2e9 = false;
    b2ea = false;
    b2eb = false;
    b2ec = false;
    p548 = nullptr;
    p540 = nullptr;
    p538 = nullptr;
    p530 = nullptr;
}

// 0x71002f1504: a panel (vtable GOT 0x7100c2ac08) with five pools that each have a flag and a pointer pair, twelve
// groups and 28 more pools. The pool fields are the panel's own: in a struct with its own constructor the pair would
// be cleared before the next pool's address is formed. The four bytes at +6559 are separate fields (one word store).
class Panel2f1504 : public PanelBase2defc0 {
public:
    explicit Panel2f1504(void* owner);
    ~Panel2f1504();

    void* p240;                  // +240
    void* p248;                  // +248
    void* p250;                  // +250
    void* p258;                  // +258
    void* p260;                  // +260
    void* p268;                  // +268
    void* p270;                  // +270
    void* p278;                  // +278
    void* p280;                  // +280
    void* p288;                  // +288
    void* p290;                  // +290
    unsigned char pad298[0x30];
    void* p2c8;                  // +2c8
    void* p2d0;                  // +2d0
    unsigned char pad2d8[0x10];
    void* p2e8;                  // +2e8
    LightResource res2f0;        // +2f0
    LightResource res400;        // +400
    Part2d6c5c part510;          // +510
    Part2d6c5c part6d8;          // +6d8
    void* p8a0;                  // +8a0
    void* p8a8;                  // +8a8
    unsigned char pad8b0[0x28];
    SlotPool2dee48 pool8d8;      // +8d8
    void* p19e0;                 // +19e0
    bool b19e8;                  // +19e8
    unsigned char pad19e9[0xf];
    void* p19f8;                 // +19f8
    void* p1a00;                 // +1a00
    unsigned char pad1a08[0x28];
    SlotPool2dee48 pool1a30;     // +1a30
    void* p2b38;                 // +2b38
    bool b2b40;                  // +2b40
    unsigned char pad2b41[0xf];
    void* p2b50;                 // +2b50
    void* p2b58;                 // +2b58
    unsigned char pad2b60[0x28];
    SlotPool2dee48 pool2b88;     // +2b88
    void* p3c90;                 // +3c90
    bool b3c98;                  // +3c98
    unsigned char pad3c99[0xf];
    void* p3ca8;                 // +3ca8
    void* p3cb0;                 // +3cb0
    unsigned char pad3cb8[0x28];
    SlotPool2dee48 pool3ce0;     // +3ce0
    void* p4de8;                 // +4de8
    bool b4df0;                  // +4df0
    unsigned char pad4df1[0xf];
    void* p4e00;                 // +4e00
    void* p4e08;                 // +4e08
    unsigned char pad4e10[0x28];
    SlotPool2dee48 pool4e38;     // +4e38
    void* p5f40;                 // +5f40
    bool b5f48;                  // +5f48
    unsigned char pad5f49[0xf];
    Group80 groups[12];          // +5f58
    bool b6558;                  // +6558
    unsigned char b6559;         // +6559
    unsigned char b655a;         // +655a
    unsigned char b655b;         // +655b
    unsigned char b655c;         // +655c
    unsigned char pad655d[0x8];
    unsigned char b6565;         // +6565
    unsigned short s6566;        // +6566
    unsigned char b6568;         // +6568
    unsigned char b6569;         // +6569
    unsigned char b656a;         // +656a
    unsigned char pad656b[0xd];
    unsigned char b6578;         // +6578
    SlotPool2dee48 pools_a[24];  // +6580
    LayoutFrame frames[128];     // +1fe40
    int i24240;                  // +24240
    SlotPool2dee48 pools_b[4];   // +24248
};

Panel2f1504::Panel2f1504(void* owner)
    : PanelBase2defc0(owner), p240(nullptr), p260(nullptr), p268(nullptr), p270(nullptr), p278(nullptr),
      p280(nullptr), p288(nullptr), p290(nullptr), p2c8(nullptr), p2d0(nullptr), p2e8(nullptr), p8a0(nullptr),
      p8a8(nullptr), b19e8(false), p19f8(nullptr), p1a00(nullptr), b2b40(false), p2b50(nullptr), p2b58(nullptr),
      b3c98(false), p3ca8(nullptr), p3cb0(nullptr), b4df0(false), p4e00(nullptr), p4e08(nullptr), b5f48(false),
      b6558(true), b6559(0), b655a(0), b655b(0), b655c(0), b6565(0), s6566(0), b6568(0), b6569(0), b656a(0),
      b6578(0), i24240(0) {
    p248 = nullptr;
    p250 = nullptr;
    p258 = nullptr;
}

struct HandleState {
    long id;                     // +08
    short a;                     // +10
    short b;                     // +12

    HandleState() : id(-1), a(0), b(0) {}
};

// A layout handle (vtable GOT 0x7100c22f00).
class LayoutHandle : public HandleState {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
};

class Game;
Game* fetch_204728();                                                       // 0x7100204728
unsigned char flag_204614(Game* game);                                      // 0x7100204614

// An entry (0xf8 bytes): an id, pointers, a cleared buffer and two layout handles.
struct Entry2eb9d4 {
    Entry2eb9d4() : id(-1), p8(nullptr), p10(nullptr), p18(nullptr), p20(nullptr), p28(nullptr), pe0(nullptr),
                    bf0(false), bf1() {
        memset(buf, 0, sizeof(buf));
    }

    int id;                      // +00
    void* p8;                    // +08
    void* p10;                   // +10
    void* p18;                   // +18
    void* p20;                   // +20
    void* p28;                   // +28
    unsigned char buf[0x80];     // +30
    LayoutHandle h1;             // +b0
    LayoutHandle h2;             // +c8
    void* pe0;                   // +e0
    unsigned char pade8[0x8];
    bool bf0;                    // +f0
    unsigned char bf1[2];        // +f1
    unsigned char padf3[0x5];
};

// Two pointers, a buffer and a last pointer, the last set first: its own constructor clears the pair (one block)
// after it, so the pair's block comes ahead of the pool set's header block.
struct PtrBlock24f0 {
    PtrBlock24f0() : p88(nullptr) {
        p8 = nullptr;
        p10 = nullptr;
    }

    void* p8;                    // +00
    void* p10;                   // +08
    unsigned char buf[0x70];     // +10
    void* p88;                   // +80
};

// Pools with a header (four fields, cleared as one block, stored high to low) and a pointer block in front; the
// pointer block's buffer is cleared after the pools.
struct PoolSet24e8 {
    PoolSet24e8() : s0(0), s2(0), s4(0), b6(false), s44b0(0), b44b2(false) {
        memset(ptrs.buf, 0, sizeof(ptrs.buf));
    }

    short s0;                    // +00
    short s2;                    // +02
    short s4;                    // +04
    bool b6;                     // +06
    PtrBlock24f0 ptrs;           // +08
    SlotPool2dee48 pools[4];     // +90
    short s44b0;                 // +44b0
    bool b44b2;                  // +44b2
};

// 0x71002eb9d4: a panel of the same screen without the panel base: two id tables set to -1, 25 entries, a pool set,
// frames, and a flag fetched last.
class Panel2eb9d4 {
public:
    explicit Panel2eb9d4(void* owner);

    bool b0;                     // +00
    int i4;                      // +04
    unsigned char b8;            // +08
    void* p10;                   // +10
    void* p18;                   // +18
    void* p20;                   // +20
    void* p28;                   // +28
    void* p30;                   // +30
    void* p38;                   // +38
    void* p40;                   // +40
    void* p48;                   // +48
    void* p50;                   // +50
    void* p58;                   // +58
    void* p60;                   // +60
    void* p68;                   // +68
    void* p70;                   // +70
    unsigned char pad78[0x60];
    void* pd8;                   // +d8
    unsigned char pade0[0x120];
    void* p200;                  // +200
    void* p208;                  // +208
    unsigned char pad210[0x50];
    void* p260;                  // +260
    void* p268;                  // +268
    void* p270;                  // +270
    void* p278;                  // +278
    int i280;                    // +280
    unsigned char pad284[0xc];
    LightResource res290;        // +290
    LightResource res3a0;        // +3a0
    int ids_a[255];              // +4b0
    int ids_b[255];              // +8ac
    bool bca8;                   // +ca8
    Entry2eb9d4 entries[25];     // +cb0
    PoolSet24e8 poolset;         // +24e8
    int i69a0;                   // +69a0
    LayoutFrame frames[128];     // +69a8
    int iada8;                   // +ada8
    Part2e2a90 partadb0;         // +adb0
    void* pcfb8;                 // +cfb8
    LayoutHandle hcfc0;          // +cfc0
    LayoutHandle hcfd8;          // +cfd8
    void* owner;                 // +cff0
    Part379e44 partcff8;         // +cff8
};

Panel2eb9d4::Panel2eb9d4(void* owner_)
    : b0(false), i4(0), b8(3), p10(nullptr), p18(nullptr), p20(nullptr), p28(nullptr), p58(nullptr), pd8(nullptr),
      p200(nullptr), p208(nullptr), p260(nullptr), p268(nullptr), p270(nullptr), p278(nullptr), i280(0), bca8(false),
      i69a0(0), iada8(0), pcfb8(nullptr), owner(owner_) {
    for (int i = 0; i < 255; i++) {
        ids_a[i] = -1;
        ids_b[i] = -1;
    }
    p48 = nullptr;
    p50 = nullptr;
    p30 = nullptr;
    p60 = nullptr;
    p38 = nullptr;
    p40 = nullptr;
    p68 = nullptr;
    p70 = nullptr;
    b8 = flag_204614(fetch_204728());
}
