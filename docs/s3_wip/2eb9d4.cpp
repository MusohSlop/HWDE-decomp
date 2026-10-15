// WIP (third session): 2eb9d4, a panel-like object's constructor (588 bytes), 5 off: the pool set's header fields (int,
// short, byte at +24e8) are stored after its three pointers in the original, before them here. Maps in the try line of
// the round 16 notes; function _ZN11Panel2eb9d4C2EPv.

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

struct Part2e2a90 { Part2e2a90(); void* data[0x441]; };   // 0x71002e2a90
struct Part379e44 { Part379e44(); void* data[3]; };       // 0x7100379e44

class Game;
Game* fetch_204728();                                     // 0x7100204728
unsigned char flag_204614(Game* game);                             // 0x7100204614

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

// Pools with a cleared buffer in front (its constructor clears the buffer after its members).
struct PoolSet24e8 {
    PoolSet24e8() : i0(0), s4(0), b6(false), p8(nullptr), p10(nullptr), p88(nullptr), s44b0(0), b44b2(false) {
        memset(buf, 0, sizeof(buf));
    }

    int i0;                      // +00
    short s4;                    // +04
    bool b6;                     // +06
    void* p8;                    // +08
    void* p10;                   // +10
    unsigned char buf[0x70];     // +18
    void* p88;                   // +88
    SlotPool2dee48 pools[4];     // +90
    short s44b0;                 // +44b0
    bool b44b2;                  // +44b2
};

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

// 0x71002eb9d4
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