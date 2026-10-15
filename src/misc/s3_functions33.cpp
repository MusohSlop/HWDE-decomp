// Panels written by hand (third session) on the panel base that 2defc0's screen also uses: two light resources and
// an owner, then the panel's own parts. Names are descriptive placeholders. Status: matching/README.md.

struct LightResource {
    LightResource();             // 0x71005d2744
    void* data[0x22];
};

struct SlotPool2dee48 {
    SlotPool2dee48();            // 0x71002dee48
    void* data[0x221];
};

struct Part287efc { Part287efc(); int data[0x29]; };                       // 0x7100287efc
struct Part2dd3d4 { explicit Part2dd3d4(int mode); void* data[0x5c]; };    // 0x71002dd3d4
struct Part379e44 { Part379e44(); void* data[3]; };                        // 0x7100379e44

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
