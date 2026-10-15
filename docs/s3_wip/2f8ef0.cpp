// WIP (third session): 2f8ef0, a composite screen's constructor (1,308 bytes) on the 3c7188 base, 5 off with
// registers abstracted. Its first member is 2defc0's screen; two panels on 2defc0's panel base (inline: vtable
// store, two light resources, owner), parts that know the screen, five layout handles and 255 frames. Left: the
// original computes the frames' address (x20) before the cursor stores at +abe30..+abe50 and the loop's byte count
// in the middle of them; ours computes both after the stores (ISel order). Maps: build/s3/m2f8ef0.txt.

struct Base3c7188 {
    Base3c7188();                // 0x71003c7188
    virtual ~Base3c7188();
    unsigned char pad8[0x20];
};

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

struct LayoutFrame {
    LayoutFrame();               // 0x71001f0140
    void* data[0x11];
};

struct LayoutLine {
    LayoutLine();                // 0x71001f1594
    void* data[5];
};

struct SlotPool2dee48 {
    SlotPool2dee48();            // 0x71002dee48
    void* data[0x221];
};

// 2defc0's screen, constructed out of line with its owner.
struct Screen2defc0 {
    explicit Screen2defc0(void* owner);   // 0x71002defc0
    unsigned char data[0x159d0];
};

struct Part2e245c { explicit Part2e245c(void* owner); unsigned char data[0x17790]; } __attribute__((aligned(16)));  // 0x71002e245c
struct Part2eb9d4 { explicit Part2eb9d4(void* owner); unsigned char data[0xd010]; };   // 0x71002eb9d4
struct Part2dbe5c { Part2dbe5c(); unsigned char data[0x290]; };                         // 0x71002dbe5c
struct Part2eeb18 { explicit Part2eeb18(void* owner); unsigned char data[0x1b840]; };  // 0x71002eeb18
struct Part2f1504 { explicit Part2f1504(void* owner); unsigned char data[0x28670]; };  // 0x71002f1504
struct Part2e8c64 { explicit Part2e8c64(void* owner); unsigned char data[0xb2d0]; };   // 0x71002e8c64
struct Part2d6c5c { Part2d6c5c(); unsigned char data[0x1c8]; };                         // 0x71002d6c5c
struct Part2f2370 { Part2f2370(); unsigned char data[0x1aeb0]; };                       // 0x71002f2370
struct Part2e2d30 { Part2e2d30(); unsigned char data[0x888]; };                         // 0x71002e2d30

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

// A panel (vtable GOT 0x7100c2abd0): a line, a slot pool and a part that knows the panel.
class PanelA2f8ef0 : public PanelBase2defc0 {
public:
    explicit PanelA2f8ef0(void* owner) : PanelBase2defc0(owner), b240(false), part(this), b18b10(false), p18b18(nullptr),
        p18b20(nullptr), p18b28(nullptr), p18b30(nullptr) {}
    ~PanelA2f8ef0();

    bool b240;                   // +240
    LayoutLine line;             // +248
    SlotPool2dee48 pool;         // +270
    Part2e245c part;             // +1380
    bool b18b10;                 // +18b10
    void* p18b18;                // +18b18
    void* p18b20;                // +18b20
    void* p18b28;                // +18b28
    void* p18b30;                // +18b30
    unsigned char pad18b38[0x58];
};

// A second panel (vtable GOT 0x7100c2abe8): five slot pools and a part that knows the panel.
class PanelB2f8ef0 : public PanelBase2defc0 {
public:
    explicit PanelB2f8ef0(void* owner) : PanelBase2defc0(owner), b240(false), part(this) {}
    ~PanelB2f8ef0();

    bool b240;                   // +240
    SlotPool2dee48 pools[5];     // +248
    Part2eb9d4 part;             // +5770
};

struct Cursorabe30 {
    Cursorabe30() {
        b6 = false;
        s4 = 0;
        i0 = 0;
        p20 = nullptr;
        p18 = nullptr;
        p10 = nullptr;
    }
    int i0;
    short s4;
    bool b6;
    unsigned char pad7[9];
    void* p10;
    void* p18;
    void* p20;
};

class Screen2f8ef0 : public Base3c7188 {
public:
    Screen2f8ef0();
    ~Screen2f8ef0();

    void* p28;                   // +28
    Screen2defc0 main;           // +30
    PanelA2f8ef0 panel_a;        // +15a00
    PanelB2f8ef0 panel_b;        // +2e590
    Part2dbe5c part40d10;        // +40d10
    Part2eeb18 part40fa0;        // +40fa0
    Part2f1504 part5c7e0;        // +5c7e0
    Part2e8c64 part84e50;        // +84e50
    Screen2defc0* main_ptr;      // +90120
    Part2d6c5c part90128;        // +90128
    void* p902f0;                // +902f0
    unsigned char pad902f8[0x8];
    LightResource light90300;    // +90300
    LightResource light90410;    // +90410
    Part2f2370 part90520;        // +90520
    void* pab3d0;                // +ab3d0
    void* pab3d8;                // +ab3d8
    void* pab3e0[4];             // +ab3e0
    void* pab400;                // +ab400
    void* pab408;                // +ab408
    void* pab410;                // +ab410
    void* pab418;                // +ab418
    void* pab420;                // +ab420
    void* pab428[6];             // +ab428
    void* pab458;                // +ab458
    void* pab460;                // +ab460
    void* pab468;                // +ab468
    unsigned char padab470[0xc0];
    LayoutHandle handles[5];     // +ab530
    Part2e2d30 partab5a8;        // +ab5a8
    Cursorabe30 cursor;          // +abe30
    LayoutFrame frames[255];     // +abe58
    int ib45d0;                  // +b45d0
    unsigned char padb45d4[4];
    bool bb45d8;                 // +b45d8
};

Screen2f8ef0::Screen2f8ef0()
    : p28(nullptr), main(this), panel_a(this), panel_b(this), part40fa0(this), part5c7e0(this), part84e50(this),
      main_ptr(&main), p902f0(nullptr), pab3d0(nullptr), pab3d8(nullptr), pab400(nullptr), pab408(nullptr),
      pab410(nullptr), pab418(nullptr), pab420(nullptr), pab458(nullptr), pab460(nullptr), pab468(nullptr),
      ib45d0(0), bb45d8(false) {
    pab3e0[3] = nullptr;
    pab3e0[2] = nullptr;
    pab3e0[1] = nullptr;
    pab3e0[0] = nullptr;
    pab428[5] = nullptr;
    pab428[4] = nullptr;
    pab428[3] = nullptr;
    pab428[2] = nullptr;
    pab428[1] = nullptr;
    pab428[0] = nullptr;
}
