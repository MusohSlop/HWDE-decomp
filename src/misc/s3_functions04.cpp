// Large functions from generated source, fixed by hand (third session). Struct, field and callee names are
// placeholders after the address and offset, as in the generated units. Status: matching/README.md.

extern "C" void* memset(void*, int, unsigned long);

int callee_170c58();        // 0x7100170c58
void callee_1879e4(long);        // 0x71001879e4
void callee_18f14c(long);        // 0x710018f14c
void callee_193624(long);        // 0x7100193624
void callee_193e44(long);        // 0x7100193e44
void callee_194e44(long);        // 0x7100194e44
void callee_196238(long);        // 0x7100196238
void callee_1963c4(long);        // 0x71001963c4
void callee_196804(long);        // 0x7100196804
void callee_196bac(long);        // 0x7100196bac
void callee_1985a8(long);        // 0x71001985a8
void callee_199168(long);        // 0x7100199168
void callee_19a524(long);        // 0x710019a524
void callee_19b108(long);        // 0x710019b108
void callee_19be44(long);        // 0x710019be44
void callee_1a39a8(long);        // 0x71001a39a8
void callee_1a844c(long);        // 0x71001a844c
int callee_1a8510(void*);        // 0x71001a8510
void callee_25b394(long);        // 0x710025b394
void callee_25b394(void*);        // 0x710025b394
void* callee_45c458(int, int, long, int, int);        // 0x710045c458
int callee_45c96c();        // 0x710045c96c

inline void* operator new(unsigned long, void* where) noexcept { return where; }
inline void* operator new[](unsigned long, void* where) noexcept { return where; }

struct Arg187d78_0 {
    unsigned char pad0[0x78];
    void* field_78;               // +78
    void* field_80;               // +80
    void* field_88;               // +88
    void* field_90;               // +90
    unsigned char pad98[0xc8];
    void* field_160;               // +160
    void* field_168;               // +168
    void* field_170;               // +170
    void* field_178;               // +178
    void* field_180;               // +180
    unsigned char pad188[0xc8];
    void* field_250;               // +250
    void* field_258;               // +258
    void* field_260;               // +260
    void* field_268;               // +268
    void* field_270;               // +270
    unsigned char pad278[0x957a8];
    void* field_95a20;               // +95a20
    unsigned char pad95a28[0x3eb0];
    void* field_998d8;               // +998d8
    void* field_998e0;               // +998e0
    int field_998e8;                 // +998e8
    unsigned char field_998ec;       // +998ec
    unsigned char field_998ed;       // +998ed
    unsigned short field_998ee;      // +998ee
    int field_998f0;                 // +998f0
    unsigned char field_998f4;       // +998f4
    unsigned char pad998f5[0x4b3];
    void* field_99da8;               // +99da8
    int field_99db0;                 // +99db0
    unsigned char field_99db4;       // +99db4
    unsigned char field_99db5;       // +99db5
    unsigned short field_99db6;      // +99db6
    int field_99db8;                 // +99db8
    unsigned char field_99dbc;       // +99dbc
    unsigned char pad99dbd[0x46d77];
    int field_e0b34;                 // +e0b34
    unsigned char pade0b38[0x4];
    long field_e0b3c;                // +e0b3c
};

#define OBJ(name, size)                                                                                       \
    class name {                                                                                              \
    public:                                                                                                   \
        name();                                                                                               \
        unsigned char pad[size];                                                                              \
    };
OBJ(ResourceFrame, 0x28)
OBJ(Obj196bac, 0x338)
OBJ(Obj193e44, 0x160)
OBJ(Obj199168, 0x6d0)
OBJ(Obj19be44, 0x3eb0)
OBJ(Obj193624, 0x5a0)
OBJ(Obj1963c4, 0x8)
OBJ(Obj19b108, 0x5)
OBJ(Obj194e44, 0x310)
OBJ(Obj196238, 0x30)
OBJ(Obj1985a8, 0x50)
OBJ(Obj196804, 0x28)
OBJ(Obj1a39a8, 0x2488)
OBJ(Obj18f14c, 0xd0)
OBJ(Obj1a844c, 0x408)
OBJ(Obj19a524, 0x10)
OBJ(Obj1a8510, 0x3c)

static inline void* heap_alloc(unsigned int size) {
    return callee_45c458(callee_45c96c(), 0x10, size, 1, 0);
}

struct TableHeader {
    void* data;               // +00
    void* value8;             // +08
    int value10;              // +10
    unsigned char value14;    // +14
    unsigned char value15;    // +15
    unsigned short value16;   // +16
    int value18;              // +18
    unsigned char value1c;    // +1c
    TableHeader() : value8(nullptr), value10(0), value14(0), value15(0), value16(0), value18(0), value1c(0) {}
};

struct CountTable : TableHeader {
    unsigned char pad20[0x4a8];
    TableHeader sub;          // +4c8
    CountTable() {
        unsigned int n = callee_170c58();
        unsigned long bytes = static_cast<unsigned long>(n) * 4;
        void* buffer = heap_alloc(bytes);
        memset(buffer, 0, bytes);
        data = buffer;
        callee_1879e4(reinterpret_cast<long>(this));
    }
};

// 0x7100187d78: a constructor: members in declaration order; the table at +998d8 zeroes its header fields, then its own constructor allocates and clears its buffer and initialises itself; the body allocates the 0x3c-byte items with placement new[] and clears three pointer arrays last to first.
class Class187d78 {
public:
    Class187d78();

    ResourceFrame frames0[3];   // +00000
    void* ptrs0[4];             // +00078
    ResourceFrame frames1[5];   // +00098
    void* ptrs1[5];             // +00160
    ResourceFrame frames2[5];   // +00188
    void* ptrs2[5];             // +00250
    Obj196bac m278[3];          // +00278
    Obj193e44 ac20[246];        // +00c20
    Obj199168 a15e60[300];      // +15e60
    Obj1a8510* a95a20;          // +95a20
    Obj19be44 m95a28;           // +95a28
    CountTable counts;          // +998d8
    Obj193624 a99dc0[128];      // +99dc0
    Obj1963c4 ac6dc0[4096];     // +c6dc0
    Obj19b108 acedc0[24];       // +cedc0
    unsigned char padcee38[8];
    Obj194e44 acee40[24];       // +cee40
    Obj196238 ad37c0[10];       // +d37c0
    Obj1985a8 ad39a0[64];       // +d39a0
    Obj196804 ad4da0[5];        // +d4da0
    Obj1a39a8 md4e68;           // +d4e68
    Obj18f14c md72f0;           // +d72f0
    Obj1a844c md73c0;           // +d73c0
    Obj19a524 md77c8;           // +d77c8
    unsigned char padd77d8[0x935c];
    int ve0b34;                 // +e0b34
    unsigned char pade0b38[4];
    int ve0b3c;                 // +e0b3c
    int ve0b40;                 // +e0b40
};

Class187d78::Class187d78() {
    unsigned int n = callee_170c58();
    unsigned long bytes = static_cast<unsigned long>(n) * sizeof(Obj1a8510);
    Obj1a8510* items = static_cast<Obj1a8510*>(heap_alloc(bytes));
    memset(items, 0, bytes);
    new (items) Obj1a8510[n];
    a95a20 = items;
    ve0b34 = 0;
    memset(ptrs2, 0, sizeof(ptrs2));
    memset(ptrs1, 0, sizeof(ptrs1));
    memset(ptrs0, 0, sizeof(ptrs0));
    ve0b3c = 246;
    ve0b40 = -1;
}


void callee_e25dc(long);        // 0x71000e25dc
void callee_1ef52c(long);        // 0x71001ef52c
void callee_1f0140(long);        // 0x71001f0140
void callee_1f1cd8(long);        // 0x71001f1cd8
void callee_1f1e0c(long);        // 0x71001f1e0c
void callee_3c7674(void*);        // 0x71003c7674

struct Argef31c_0 {
    long field_0;                // +0
    unsigned char pad8[0x78];
    void* field_80;               // +80
    void* field_88;               // +88
    unsigned char pad90[0x408c0];
    void* field_40950;               // +40950
    unsigned char pad40958[0x49e4];
    unsigned char field_4533c;       // +4533c
    unsigned char pad4533d[0x73];
    int field_453b0;                 // +453b0
    int field_453b4;                 // +453b4
    int field_453b8;                 // +453b8
    int field_453bc;                 // +453bc
    unsigned char pad453c0[0x40];
    int field_45400;                 // +45400
    int field_45404;                 // +45404
    int field_45408;                 // +45408
    int field_4540c;                 // +4540c
    unsigned char pad45410[0x40];
    int field_45450;                 // +45450
    int field_45454;                 // +45454
    int field_45458;                 // +45458
    int field_4545c;                 // +4545c
    unsigned char pad45460[0x40];
    int field_454a0;                 // +454a0
    int field_454a4;                 // +454a4
    int field_454a8;                 // +454a8
    int field_454ac;                 // +454ac
    unsigned char pad454b0[0x40];
    int field_454f0;                 // +454f0
    int field_454f4;                 // +454f4
    int field_454f8;                 // +454f8
    int field_454fc;                 // +454fc
    unsigned char pad45500[0x40];
    int field_45540;                 // +45540
    int field_45544;                 // +45544
    int field_45548;                 // +45548
    int field_4554c;                 // +4554c
    unsigned char pad45550[0x40];
    int field_45590;                 // +45590
    long field_45594 __attribute__((packed));                // +45594
    int field_4559c;                 // +4559c
    unsigned char pad455a0[0x110];
    int field_456b0;                 // +456b0
    int field_456b4;                 // +456b4
    int field_456b8;                 // +456b8
    int field_456bc;                 // +456bc
    unsigned char pad456c0[0x40];
    int field_45700;                 // +45700
    int field_45704;                 // +45704
    int field_45708;                 // +45708
    int field_4570c;                 // +4570c
    unsigned char pad45710[0x40];
    int field_45750;                 // +45750
    int field_45754;                 // +45754
    int field_45758;                 // +45758
    int field_4575c;                 // +4575c
    unsigned char pad45760[0x40];
    int field_457a0;                 // +457a0
    int field_457a4;                 // +457a4
    int field_457a8;                 // +457a8
    int field_457ac;                 // +457ac
    unsigned char pad457b0[0x40];
    int field_457f0;                 // +457f0
    int field_457f4;                 // +457f4
    int field_457f8;                 // +457f8
    int field_457fc;                 // +457fc
    unsigned char pad45800[0x40];
    int field_45840;                 // +45840
    int field_45844;                 // +45844
    int field_45848;                 // +45848
    int field_4584c;                 // +4584c
    unsigned char pad45850[0x40];
    int field_45890;                 // +45890
    long field_45894 __attribute__((packed));                // +45894
    int field_4589c;                 // +4589c
};

struct Elemef31c_r57 {
    unsigned char pad0[0x48];
};
// Reached through the GOT slot at 0x7100c22bf8.
extern unsigned char gGlobalc22bf8_ef31c[];

class LayoutBox {
public:
    LayoutBox();                                                         // 0x71001f1e0c
    unsigned char pad[0x10];
};

class LayoutFrame {
public:
    LayoutFrame();                                                       // 0x71001f0140
    unsigned char pad[0x88];
};

class LayoutRect {
public:
    LayoutRect();                                                        // 0x71001f1cd8
    unsigned char pad[0x28];
};

class LayoutSprite {
public:
    LayoutSprite();                                                      // 0x71001ef52c
    unsigned char pad[0x48];
};

class Obj3c7674 {
public:
    Obj3c7674();                                                         // 0x71003c7674
    virtual ~Obj3c7674();
    unsigned char pad8[0x78];
};

class Obje25dc {
public:
    Obje25dc();                                                          // 0x71000e25dc
    unsigned char pad[0x408c0];
};

struct Entry50 {
    int a;                    // +00
    int b;                    // +04
    int c;                    // +08
    int d;                    // +0c
    unsigned char pad10[0x40];
    Entry50() : a(-1), b(-1), c(3), d(0xf6) {}
};

struct EntryGroup {
    Entry50 entries[7];       // +000
    unsigned char flags[0xc9]; // +230
    unsigned char pad2f9[7];
    EntryGroup() : flags() {}
};

class Classef31c : public Obj3c7674 {
public:
    Classef31c();
    virtual void v00();

    void* f80;
    void* f88;
    Obje25dc m90;
    void* f40950;
    unsigned char pad40958[0x10];
    LayoutSprite m40968;
    LayoutSprite m409b0;
    LayoutSprite m409f8;
    LayoutSprite m40a40;
    LayoutSprite m40a88;
    LayoutSprite m40ad0;
    LayoutSprite m40b18;
    LayoutSprite m40b60;
    LayoutSprite m40ba8;
    LayoutSprite m40bf0;
    LayoutSprite m40c38;
    LayoutSprite m40c80;
    LayoutSprite m40cc8;
    LayoutSprite m40d10;
    LayoutSprite m40d58;
    LayoutSprite m40da0;
    LayoutSprite m40de8;
    LayoutSprite m40e30;
    LayoutSprite m40e78;
    LayoutSprite m40ec0;
    LayoutSprite m40f08;
    LayoutSprite m40f50;
    LayoutSprite m40f98;
    LayoutSprite m40fe0;
    LayoutSprite m41028;
    LayoutSprite m41070;
    LayoutSprite m410b8;
    LayoutSprite m41100;
    LayoutSprite m41148;
    LayoutSprite m41190;
    LayoutSprite m411d8;
    LayoutSprite m41220;
    LayoutSprite m41268;
    LayoutSprite m412b0;
    LayoutSprite m412f8;
    LayoutSprite m41340;
    LayoutSprite m41388;
    LayoutSprite m413d0;
    LayoutSprite m41418;
    LayoutSprite m41460;
    LayoutSprite m414a8;
    LayoutSprite m414f0;
    LayoutSprite m41538;
    LayoutSprite m41580;
    LayoutSprite m415c8;
    LayoutSprite m41610;
    LayoutSprite m41658;
    LayoutSprite m416a0;
    LayoutSprite m416e8;
    LayoutSprite m41730;
    LayoutSprite m41778;
    LayoutSprite m417c0;
    LayoutSprite m41808;
    LayoutSprite m41850;
    LayoutSprite m41898;
    unsigned char pad418e0[0x8];
    LayoutSprite a418e8[128];
    LayoutFrame m43ce8;
    LayoutFrame m43d70;
    LayoutFrame m43df8;
    LayoutFrame m43e80;
    LayoutFrame m43f08;
    LayoutFrame m43f90;
    LayoutFrame m44018;
    LayoutFrame m440a0;
    LayoutFrame m44128;
    LayoutFrame m441b0;
    LayoutFrame m44238;
    LayoutFrame m442c0;
    LayoutFrame m44348;
    LayoutFrame m443d0;
    LayoutFrame m44458;
    LayoutFrame m444e0;
    LayoutFrame m44568;
    LayoutFrame m445f0;
    LayoutFrame m44678;
    LayoutFrame m44700;
    LayoutFrame m44788;
    LayoutFrame m44810;
    LayoutFrame m44898;
    LayoutFrame m44920;
    LayoutFrame m449a8;
    LayoutFrame m44a30;
    LayoutFrame m44ab8;
    LayoutFrame m44b40;
    LayoutFrame m44bc8;
    LayoutFrame m44c50;
    unsigned char pad44cd8[0x664];
    unsigned char f4533c;
    unsigned char pad4533d[0x3];
    LayoutRect m45340;
    LayoutRect m45368;
    LayoutBox m45390;
    LayoutBox m453a0;
    EntryGroup g453b0;          // +453b0
    EntryGroup g456b0;          // +456b0
};

Classef31c::Classef31c() {
    f40950 = nullptr;
    f4533c = 0;
    f80 = nullptr;
    f88 = nullptr;
}
