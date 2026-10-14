class DefaultHeap {
public:
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

// Complete-object destructors whose direct base is itself polymorphic with an inline destructor,
// so the base's vtable is stored again halfway through (found by a destructor-shape scan).
// Classes are named after the destructor's address. Status: matching/README.md.

struct Part5d27b4_110 { ~Part5d27b4_110(); unsigned char data[0x110]; };    // 0x71005d27b4
struct Part5d27b4_120 { ~Part5d27b4_120(); unsigned char data[0x120]; };    // 0x71005d27b4

class RootNode3ccc84 {
public:
    virtual ~RootNode3ccc84();                                              // 0x71003ccc84

    unsigned char pad8[8];
};

// Vtable through the GOT slot at 0x7100c2abb0.
class TwoPanelBase : public RootNode3ccc84 {
public:
    virtual ~TwoPanelBase() {}
    virtual void key_function();

    Part5d27b4_110 upper;     // +10
    Part5d27b4_120 lower;     // +120
};

struct Part287f38_324 { ~Part287f38_324(); unsigned char data[0x324]; };    // 0x7100287f38
struct Part2dd510_2e0 { ~Part2dd510_2e0(); unsigned char data[0x2e0]; };    // 0x71002dd510
struct Part379f30_10 { ~Part379f30_10(); unsigned char data[0x10]; };       // 0x7100379f30

// Vtable through the GOT slot at 0x7100c2abe0.
class Panel2e8e64 : public TwoPanelBase {
public:
    ~Panel2e8e64();
    virtual void key_function();

    unsigned char pad240[4];
    Part287f38_324 frame;     // +244
    Part2dd510_2e0 list;      // +568
    Part379f30_10 cursor;     // +848
};

// 0x71002e8e64
Panel2e8e64::~Panel2e8e64() {}

struct Part287f38_a8 { ~Part287f38_a8(); unsigned char data[0xa8]; };       // 0x7100287f38
struct Part5d27b4_110b { ~Part5d27b4_110b(); unsigned char data[0x110]; }; // 0x71005d27b4
struct Part5d27b4_798 { ~Part5d27b4_798(); unsigned char data[0x798]; };    // 0x71005d27b4
struct Part379f30_10b { ~Part379f30_10b(); unsigned char data[0x10]; };     // 0x7100379f30

// Vtable through the GOT slot at 0x7100c2ac00.
class Panel2eef80 : public TwoPanelBase {
public:
    ~Panel2eef80();
    virtual void key_function();

    unsigned char pad240[8];
    Part287f38_a8 frame;      // +248
    Part5d27b4_110b title;    // +2f0
    Part5d27b4_798 body;      // +400
    Part2dd510_2e0 list;      // +b98
    Part379f30_10b cursor;    // +e78
};

// 0x71002eef80
Panel2eef80::~Panel2eef80() {}

struct Part5d27b4_110c { ~Part5d27b4_110c(); unsigned char data[0x110]; }; // 0x71005d27b4
struct Part2d6e8c_1c8 { ~Part2d6e8c_1c8(); unsigned char data[0x1c8]; };    // 0x71002d6e8c
struct Part2d6e8c_10 { ~Part2d6e8c_10(); unsigned char data[0x10]; };       // 0x71002d6e8c

// Vtable through the GOT slot at 0x7100c2ac08.
class Panel2f1ab4 : public TwoPanelBase {
public:
    ~Panel2f1ab4();
    virtual void key_function();

    unsigned char pad240[0xb0];
    Part5d27b4_110c title;    // +2f0
    Part5d27b4_110c body;     // +400
    Part2d6e8c_1c8 left;      // +510
    Part2d6e8c_10 right;      // +6d8
};

// 0x71002f1ab4
Panel2f1ab4::~Panel2f1ab4() {}

struct Part4640c_4 { ~Part4640c_4(); unsigned char data[4]; };              // 0x710004640c
struct Part4640c_10 { ~Part4640c_10(); unsigned char data[0x10]; };         // 0x710004640c

// Vtable through the GOT slot at 0x7100c22978.
class HandleCell {
public:
    virtual ~HandleCell() {}
    virtual void key_function();

    unsigned char pad8[4];
    Part4640c_4 handle;       // +c
};

// Vtable through the GOT slot at 0x7100c22988.
class HandlePair : public HandleCell {
public:
    ~HandlePair();
    virtual void key_function();

    Part4640c_10 second;      // +10
};

// 0x71000cffb8
HandlePair::~HandlePair() {}

struct Part5c2c8c_78 { ~Part5c2c8c_78(); unsigned char data[0x78]; };       // 0x71005c2c8c
struct Part5c2c8c_10 { ~Part5c2c8c_10(); unsigned char data[0x10]; };       // 0x71005c2c8c

// Vtable through the GOT slot at 0x7100c21ee0.
class FrameOwner {
public:
    virtual ~FrameOwner() { detach(); }
    void detach() {}
    virtual void key_function();
    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }

    unsigned char pad8[0x20];
};

// Vtable through the GOT slot at 0x7100c21ed0.
class FramePair : public FrameOwner, public Part5c2c8c_78 {
public:
    ~FramePair();
    virtual void key_function();

    Part5c2c8c_10 second;     // +a0
};

// 0x710004b108 (deleting variant 0x710004b158)
FramePair::~FramePair() {}

struct Part4c084_220 { ~Part4c084_220(); unsigned char data[0x220]; };     // 0x710004c084
struct Part3ce10_18 { ~Part3ce10_18(); unsigned char data[0x18]; };         // 0x710003ce10
struct Part464fc_68 { ~Part464fc_68(); unsigned char data[0x68]; };         // 0x71000464fc

// Vtable through the GOT slot at 0x7100c21fa0.
class CellOwner {
public:
    virtual ~CellOwner() { detach(); }
    void detach() {}
    virtual void key_function();

    unsigned char pad8[0x18];
};

// Vtable through the GOT slot at 0x7100c21f98.
class CellGrid : public CellOwner, public Part4c084_220 {
public:
    ~CellGrid();
    virtual void key_function();

    Part3ce10_18 cell_240;        // +240
    Part3ce10_18 cell_258;        // +258
    Part3ce10_18 cell_270;        // +270
    Part3ce10_18 cell_288;        // +288
    Part3ce10_18 cell_2a0;        // +2a0
    Part3ce10_18 cell_2b8;        // +2b8
    Part3ce10_18 cell_2d0;        // +2d0
    Part3ce10_18 cell_2e8;        // +2e8
    Part3ce10_18 cell_300;        // +300
    Part3ce10_18 cell_318;        // +318
    Part3ce10_18 cell_330;        // +330
    Part3ce10_18 cell_348;        // +348
    Part3ce10_18 cell_360;        // +360
    Part464fc_68 slot_378;        // +378
    Part464fc_68 slot_3e0;        // +3e0
    Part464fc_68 slot_448;        // +448
    Part464fc_68 slot_4b0;        // +4b0
};

// 0x71000511c4
CellGrid::~CellGrid() {}