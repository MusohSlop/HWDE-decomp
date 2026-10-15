// Large functions from generated source, fixed by hand (third session). Struct, field and callee names are
// placeholders after the address and offset, as in the generated units. Status: matching/README.md.

int callee_ef31c(long);        // 0x71000ef31c
void callee_17224c(long);        // 0x710017224c
void callee_1ef52c(long);        // 0x71001ef52c
void callee_337bac(long);        // 0x7100337bac
void callee_387524(void*);        // 0x7100387524

inline void* operator new(unsigned long, void* where) noexcept { return where; }
inline void* operator new[](unsigned long, void* where) noexcept { return where; }

class Ctor_337bac {
public:
    Ctor_337bac();                                                         // 0x7100337bac
    unsigned char pad[0x30];
};

struct Arg1721b0_0 {
    long field_0;                // +0
};

struct Elem1721b0_r4 {
    unsigned char pad0[0x30];
};
// Reached through the GOT slot at 0x7100c22d38.
extern unsigned char gGlobalc22d38_1721b0[];

// 0x71001721b0
int call_1721b0(Arg1721b0_0* p0) {
    callee_387524(p0);
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc22d38_1721b0) + 0x10);
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2d460));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2d4a8));
    callee_17224c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2d4f0));
    new (reinterpret_cast<unsigned char*>(p0) + 0x2d9b8) Ctor_337bac[0x157c];
    return callee_ef31c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x6e100));
}

struct HandleState {
    long id;                  // +08
    short a;                  // +10
    short b;                  // +12

    HandleState() : id(-1), a(0), b(0) {}
};

// Layout handle; its vtable lives in the effect manager unit (GOT 0x7100c22f00).
class LayoutHandle : public HandleState {
public:
    virtual ~LayoutHandle();
    virtual void v10();
    virtual void release(void* root); // +18
};

class LayoutFrame {
public:
    LayoutFrame();                                                       // 0x71001f0140
    unsigned char pad[0x88];
};

class Class2900cc {
public:
    Class2900cc();

    void* f0;
    unsigned char pad8[0x8];
    LayoutHandle h10;
    unsigned char pad28[0x30];
    LayoutFrame m58;
    LayoutFrame me0;
    LayoutFrame m168;
    LayoutFrame m1f0;
    LayoutFrame m278;
    LayoutFrame m300;
    LayoutFrame m388;
    LayoutFrame m410;
    LayoutFrame m498;
    LayoutFrame m520;
    LayoutFrame m5a8;
    LayoutFrame m630;
    LayoutFrame m6b8;
    LayoutFrame m740;
    LayoutFrame m7c8;
    LayoutFrame m850;
    LayoutFrame m8d8;
    LayoutFrame m960;
    LayoutFrame m9e8;
    LayoutFrame ma70;
    LayoutFrame maf8;
    LayoutFrame mb80;
    LayoutFrame mc08;
    LayoutFrame mc90;
    LayoutFrame md18;
    LayoutFrame mda0;
    LayoutFrame me28;
    LayoutFrame meb0;
    LayoutFrame mf38;
    LayoutFrame mfc0;
    unsigned char f1048;
    unsigned char pad1049[0x3];
    int f104c;
    unsigned char f1050;
};

Class2900cc::Class2900cc()
    : f0(nullptr), f1048(0), f104c(0), f1050(1) {}

int callee2_1ef52c(long);        // 0x71001ef52c
void callee_5d2744(long);        // 0x71005d2744

struct Arg3c8578_0 {
    unsigned char field_0;       // +0
    unsigned char pad1[0x3];
    int field_4;                 // +4
    unsigned char pad8[0x228];
    void* field_230;               // +230
    void* field_238;               // +238
    unsigned char pad240[0x80];
    void* field_2c0;               // +2c0
    void* field_2c8;               // +2c8
    void* field_2d0;               // +2d0
    void* field_2d8;               // +2d8
    void* field_2e0;               // +2e0
    void* field_2e8;               // +2e8
    long field_2f0;                // +2f0
    long field_2f8;                // +2f8
    unsigned short field_300;      // +300
    unsigned short field_302;      // +302
    unsigned char pad304[0x4];
    long field_308;                // +308
    long field_310;                // +310
    int field_318;                 // +318
    unsigned char pad31c[0x4];
    long field_320;                // +320
    long field_328;                // +328
    int field_330;                 // +330
    unsigned char pad334[0x4];
    long field_338;                // +338
    long field_340;                // +340
    int field_348;                 // +348
    unsigned char pad34c[0x4];
    long field_350;                // +350
    long field_358;                // +358
    int field_360;                 // +360
    unsigned char pad364[0x4];
    long field_368;                // +368
    long field_370;                // +370
    int field_378;                 // +378
};
// Reached through the GOT slot at 0x7100c22f00.
extern unsigned char gGlobalc22f00_3c8578[];

// 0x71003c8578
int call_3c8578(Arg3c8578_0* p0) {
    p0->field_0 = 0;
    p0->field_4 = 0;
    callee_5d2744(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x10));
    callee_5d2744(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x120));
    p0->field_238 = nullptr;
    p0->field_230 = nullptr;
    p0->field_2e8 = nullptr;
    p0->field_2e0 = nullptr;
    p0->field_2d8 = nullptr;
    p0->field_2d0 = nullptr;
    p0->field_2c8 = nullptr;
    p0->field_2c0 = nullptr;
    new (reinterpret_cast<unsigned char*>(p0) + 0x2f0) LayoutHandle;
    new (reinterpret_cast<unsigned char*>(p0) + 0x308) LayoutHandle;
    new (reinterpret_cast<unsigned char*>(p0) + 0x320) LayoutHandle;
    new (reinterpret_cast<unsigned char*>(p0) + 0x338) LayoutHandle;
    new (reinterpret_cast<unsigned char*>(p0) + 0x350) LayoutHandle;
    new (reinterpret_cast<unsigned char*>(p0) + 0x368) LayoutHandle;
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x380));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3c8));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x410));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x458));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4a0));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4e8));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x530));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x578));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5c0));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x608));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x650));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x698));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x6e0));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x728));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x770));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x7b8));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x800));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x848));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x890));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x8d8));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x920));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x968));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x9b0));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x9f8));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xa40));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xa88));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xad0));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xb18));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xb60));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xba8));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xbf0));
    return callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xc38));
}

int callee_1e22e4(void*, int);        // 0x71001e22e4
void callee_1e2360(void*, long, int, void*);        // 0x71001e2360
void callee_1e26dc(void*, long, long);        // 0x71001e26dc
void callee_1e26e4(void*);        // 0x71001e26e4
void* callee_1e3770(void*, void*, int);        // 0x71001e3770
void callee_3af6e8(long, int, int, float);        // 0x71003af6e8
void callee_3c7674(void*);        // 0x71003c7674

class Node33f7c0_v17 {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();
    virtual void slot_4();
    virtual void slot_5();
    virtual void slot_6();
    virtual void slot_7();
    virtual void slot_8();
    virtual void slot_9();
    virtual void slot_10();
    virtual void slot_11();
    virtual void* slot_12(void*, int);
};

struct Node33f7c0_v16 {
    unsigned char pad0[0x18];
    Node33f7c0_v17* field_18;     // +18
};

struct Arg33f7c0_0 {
    long field_0;                // +0
    unsigned char pad8[0x78];
    void* field_80;               // +80
    unsigned short field_88;      // +88
    unsigned char pad8a[0x6];
    int field_90;                 // +90
    unsigned char pad94[0x11c];
    Node33f7c0_v16* field_1b0;     // +1b0
    void* field_1b8;               // +1b8
    void* field_1c0;               // +1c0
    void* field_1c8;               // +1c8
    int field_1d0;                 // +1d0
    unsigned char pad1d4[0x4];
    void* field_1d8;               // +1d8
    unsigned char pad1e0[0x18];
    void* field_1f8;               // +1f8
    void* field_200;               // +200
    long field_208;                // +208
    long field_210;                // +210
    unsigned short field_218;      // +218
    unsigned short field_21a;      // +21a
    unsigned char pad21c[0x4];
    unsigned short field_220;      // +220
    unsigned char pad222[0x6];
    void* field_228;               // +228
    void* field_230;               // +230
};

struct C2033f7c0 {
    unsigned char pad0[0x58];
    unsigned char field_58;       // +58
};

struct C2633f7c0 {
    unsigned char pad0[0x58];
    unsigned char field_58;       // +58
};

struct C3233f7c0 {
    unsigned char pad0[0x58];
    unsigned char field_58;       // +58
};

struct C3933f7c0 {
    unsigned char pad0[0x58];
    unsigned char field_58;       // +58
};

struct C4533f7c0 {
    unsigned char pad0[0x58];
    unsigned char field_58;       // +58
};

struct C5133f7c0 {
    unsigned char pad0[0x58];
    unsigned char field_58;       // +58
};

struct C5733f7c0 {
    unsigned char pad0[0x58];
    unsigned char field_58;       // +58
};
// Reached through the GOT slot at 0x7100c22a00.
extern void* gGlobalc22a00_33f7c0;
// Reached through the GOT slot at 0x7100c2af10.
extern unsigned char gGlobalc2af10_33f7c0[];
// Reached through the GOT slot at 0x7100c22f00.
extern unsigned char gGlobalc22f00_33f7c0[];
extern unsigned char gLocal741e55_33f7c0[] __attribute__((visibility("hidden")));    // 0x7100741e55
extern unsigned char gLocal73fffb_33f7c0[] __attribute__((visibility("hidden")));    // 0x710073fffb
extern unsigned char gLocal7da3d0_33f7c0[] __attribute__((visibility("hidden")));    // 0x71007da3d0
extern unsigned char gLocal7da3d4_33f7c0[] __attribute__((visibility("hidden")));    // 0x71007da3d4
extern unsigned char gLocal741e7e_33f7c0[] __attribute__((visibility("hidden")));    // 0x7100741e7e
extern unsigned char gLocal741e95_33f7c0[] __attribute__((visibility("hidden")));    // 0x7100741e95
extern unsigned char gLocal741e70_33f7c0[] __attribute__((visibility("hidden")));    // 0x7100741e70
extern unsigned char gLocal7da3d9_33f7c0[] __attribute__((visibility("hidden")));    // 0x71007da3d9
extern unsigned char gLocal7da3ea_33f7c0[] __attribute__((visibility("hidden")));    // 0x71007da3ea
extern unsigned char gLocal7da3f6_33f7c0[] __attribute__((visibility("hidden")));    // 0x71007da3f6
extern unsigned char gLocal7da40a_33f7c0[] __attribute__((visibility("hidden")));    // 0x71007da40a

// 0x710033f7c0
int call_33f7c0(Arg33f7c0_0* p0) {
    callee_3c7674(p0);
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2af10_33f7c0) + 0x10);
    callee_5d2744(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xa0));
    p0->field_1b0 = nullptr;
    p0->field_1d8 = nullptr;
    p0->field_1f8 = nullptr;
    p0->field_200 = nullptr;
    long a2 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1b0);
    new (reinterpret_cast<unsigned char*>(p0) + 0x208) LayoutHandle;
    long a3 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1d8);
    p0->field_220 = 0;
    p0->field_230 = nullptr;
    p0->field_228 = nullptr;
    void* v4 = gGlobalc22a00_33f7c0;
    callee_1e26dc(v4, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xa0), 0);
    void* v6 = gGlobalc22a00_33f7c0;
    callee_1e2360(v6, a2, 0x41e7, gLocal741e55_33f7c0);
    void* v8 = gGlobalc22a00_33f7c0;
    callee_1e26e4(v8);
    Node33f7c0_v16* v10 = p0->field_1b0;
    void* c11 = callee_1e3770(v10, gLocal73fffb_33f7c0, 1);
    p0->field_1b8 = c11;
    Node33f7c0_v16* v12 = p0->field_1b0;
    void* c13 = callee_1e3770(v12, gLocal7da3d0_33f7c0, 1);
    p0->field_1c0 = c13;
    Node33f7c0_v16* v14 = p0->field_1b0;
    void* c15 = callee_1e3770(v14, gLocal7da3d4_33f7c0, 1);
    Node33f7c0_v16* v16 = p0->field_1b0;
    p0->field_1c8 = c15;
    Node33f7c0_v17* v17 = v16->field_18;
    C2033f7c0* c20 = static_cast<C2033f7c0*>(v17->slot_12(gLocal741e7e_33f7c0, 1));
    unsigned char v21 = c20->field_58;
    c20->field_58 = v21 & 0xfe;
    Node33f7c0_v16* v22 = p0->field_1b0;
    Node33f7c0_v17* v23 = v22->field_18;
    C2633f7c0* c26 = static_cast<C2633f7c0*>(v23->slot_12(gLocal741e95_33f7c0, 1));
    unsigned char v27 = c26->field_58;
    c26->field_58 = v27 & 0xfe;
    Node33f7c0_v16* v28 = p0->field_1b0;
    Node33f7c0_v17* v29 = v28->field_18;
    C3233f7c0* c32 = static_cast<C3233f7c0*>(v29->slot_12(gLocal741e70_33f7c0, 1));
    unsigned char v33 = c32->field_58;
    c32->field_58 = v33 & 0xfe;
    callee_3af6e8(a3, 0x18, 0, 0.0f);
    Node33f7c0_v16* v35 = p0->field_1b0;
    p0->field_1d0 = 0;
    p0->field_90 = 0;
    p0->field_88 = 0;
    p0->field_80 = nullptr;
    Node33f7c0_v17* v36 = v35->field_18;
    C3933f7c0* c39 = static_cast<C3933f7c0*>(v36->slot_12(gLocal7da3d9_33f7c0, 1));
    unsigned char v40 = c39->field_58;
    c39->field_58 = v40 | 1;
    Node33f7c0_v16* v41 = p0->field_1b0;
    Node33f7c0_v17* v42 = v41->field_18;
    C4533f7c0* c45 = static_cast<C4533f7c0*>(v42->slot_12(gLocal7da3ea_33f7c0, 1));
    unsigned char v46 = c45->field_58;
    c45->field_58 = v46 | 1;
    Node33f7c0_v16* v47 = p0->field_1b0;
    Node33f7c0_v17* v48 = v47->field_18;
    C5133f7c0* c51 = static_cast<C5133f7c0*>(v48->slot_12(gLocal7da3f6_33f7c0, 1));
    unsigned char v52 = c51->field_58;
    c51->field_58 = v52 | 1;
    Node33f7c0_v16* v53 = p0->field_1b0;
    Node33f7c0_v17* v54 = v53->field_18;
    C5733f7c0* c57 = static_cast<C5733f7c0*>(v54->slot_12(gLocal7da40a_33f7c0, 1));
    unsigned char v58 = c57->field_58;
    c57->field_58 = v58 | 1;
    void* v59 = gGlobalc22a00_33f7c0;
    return callee_1e22e4(v59, 0x41e7);
}

int callee_1f0140(long);        // 0x71001f0140

struct Arg1ddfe8_0 {
    void* field_0;               // +0
    int field_8;                 // +8
    unsigned char field_c;       // +c
    unsigned char padd[0x3];
    int field_10;                 // +10
    int field_14;                 // +14
    unsigned short field_18;      // +18
    unsigned char pad1a[0x2];
    int field_1c;                 // +1c
    unsigned char field_20;       // +20
    unsigned char pad21[0x3];
    int field_24;                 // +24
    unsigned char pad28[0x48];
    unsigned char field_70;       // +70
    unsigned char pad71[0x7];
    void* field_78;               // +78
    unsigned char pad80[0x140];
    long field_1c0;                // +1c0
    long field_1c8;                // +1c8
    int field_1d0;                 // +1d0
};
// Reached through the GOT slot at 0x7100c22f00.
extern unsigned char gGlobalc22f00_1ddfe8[];

// 0x71001ddfe8
int call_1ddfe8(Arg1ddfe8_0* p0) {
    p0->field_0 = nullptr;
    p0->field_8 = -1;
    p0->field_c = 1;
    p0->field_10 = -1;
    p0->field_14 = 0;
    p0->field_18 = 0;
    p0->field_1c = 0;
    p0->field_20 = 0;
    p0->field_24 = 0;
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x28));
    p0->field_70 = 0;
    p0->field_78 = nullptr;
    callee_5d2744(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x90));
    new (reinterpret_cast<unsigned char*>(p0) + 0x1c0) LayoutHandle;
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1e0));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x268));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2f0));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x378));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x400));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x488));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x510));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x598));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x620));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x6a8));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x730));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x7b8));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x840));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x8c8));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x950));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x9d8));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xa60));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xae8));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xb70));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xbf8));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xc80));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd08));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd90));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xe18));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xea0));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xf28));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xfb0));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1038));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x10c0));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1148));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x11d0));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1258));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x12e0));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1368));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x13f0));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1478));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1500));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1588));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1610));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1698));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1720));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x17a8));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1830));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x18b8));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1940));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x19c8));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1a50));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1ad8));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1b60));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1be8));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1c70));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1cf8));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1d80));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1e08));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1e90));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1f18));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1fa0));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2028));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x20b0));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2138));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x21c0));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2248));
    callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x22d0));
    return callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2358));
}



class LayoutSprite {
public:
    LayoutSprite();                                                      // 0x71001ef52c
    unsigned char pad[0x48];
};

class Class3980b8 {
public:
    Class3980b8();

    unsigned char pad0[0x40];
    LayoutHandle h40;
    unsigned char pad58[0x58];
    LayoutSprite ab0[544];
    LayoutSprite a99b0[544];
    LayoutSprite m132b0;
    LayoutSprite m132f8;
    LayoutSprite m13340;
    LayoutSprite m13388;
    LayoutSprite m133d0;
    LayoutSprite m13418;
    LayoutSprite m13460;
    LayoutSprite m134a8;
    LayoutSprite m134f0;
    LayoutSprite m13538;
    LayoutSprite m13580;
    LayoutSprite m135c8;
    LayoutSprite m13610;
    LayoutSprite m13658;
    LayoutSprite m136a0;
    LayoutSprite m136e8;
    LayoutSprite m13730;
    LayoutSprite m13778;
    LayoutSprite m137c0;
    LayoutSprite m13808;
    LayoutSprite m13850;
    LayoutSprite m13898;
    LayoutSprite m138e0;
    LayoutSprite m13928;
    LayoutSprite m13970;
    LayoutSprite m139b8;
    LayoutSprite m13a00;
    LayoutSprite m13a48;
    LayoutSprite m13a90;
    LayoutSprite m13ad8;
    LayoutSprite m13b20;
    LayoutSprite m13b68;
    LayoutSprite m13bb0;
    LayoutSprite m13bf8;
    LayoutSprite m13c40;
    LayoutSprite m13c88;
    LayoutSprite m13cd0;
    LayoutSprite m13d18;
    LayoutSprite m13d60;
    LayoutSprite m13da8;
    LayoutSprite m13df0;
    LayoutSprite m13e38;
    LayoutSprite m13e80;
    LayoutSprite m13ec8;
    LayoutSprite m13f10;
    LayoutSprite m13f58;
    LayoutSprite m13fa0;
    LayoutSprite m13fe8;
    LayoutSprite m14030;
    LayoutSprite m14078;
    LayoutSprite m140c0;
    LayoutSprite m14108;
    LayoutSprite m14150;
    LayoutSprite m14198;
    LayoutSprite m141e0;
    LayoutSprite m14228;
    LayoutSprite m14270;
    LayoutSprite m142b8;
    LayoutSprite m14300;
    LayoutSprite m14348;
    LayoutSprite m14390;
    LayoutSprite m143d8;
    LayoutSprite m14420;
    LayoutSprite m14468;
    LayoutSprite m144b0;
    LayoutSprite m144f8;
    LayoutSprite m14540;
};

Class3980b8::Class3980b8() {}

#include "event/layout_panes.h"

void callee_1e2360(void*, void*, int, void*);        // 0x71001e2360
void callee_1e26e8(void*);        // 0x71001e26e8
void callee2_1f0140(long);        // 0x71001f0140
void* callee_5d4380(int);        // 0x71005d4380
int callee_5da17c(void*, void*);        // 0x71005da17c
void callee_5dc664(void*);        // 0x71005dc664

class Node36983c_v87 {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();
    virtual void slot_4();
    virtual void slot_5();
    virtual void slot_6();
    virtual void slot_7();
    virtual void slot_8();
    virtual void slot_9();
    virtual void slot_10();
    virtual void slot_11();
    virtual void* slot_12(void*, int);
};

struct Node36983c_v86 {
    unsigned char pad0[0x18];
    Node36983c_v87* field_18;     // +18
};

struct Node36983c_v114 {
    unsigned char pad0[0x5b];
    unsigned char field_5b;       // +5b
};

struct Node36983c_v116 {
    unsigned char pad0[0x5b];
    unsigned char field_5b;       // +5b
};

struct Arg36983c_0 {
    Node36983c_v86* field_0;     // +0
    void* field_8;               // +8
    void* field_10;               // +10
    void* field_18;               // +18
    void* field_20;               // +20
    void* field_28;               // +28
    void* field_30;               // +30
    void* field_38;               // +38
    void* field_40;               // +40
    unsigned char pad48[0x2640];
    Node36983c_v114* field_2688;    // +2688
    Node36983c_v116* field_2690;    // +2690
    long field_2698;                // +2698
    long field_26a0;                // +26a0
    unsigned short field_26a8;      // +26a8
    unsigned short field_26aa;      // +26aa
    unsigned char pad26ac[0x4];
    int field_26b0;                 // +26b0
    unsigned char field_26b4;       // +26b4
};

struct C10136983c {
    long field_0;                // +0
    unsigned char pad8[0x158];
    void* field_160;               // +160
    void* field_168;               // +168
    void* field_170;               // +170
};

struct C10536983c {
    long field_0;                // +0
    unsigned char pad8[0x158];
    void* field_160;               // +160
    void* field_168;               // +168
    void* field_170;               // +170
};
// Reached through the GOT slot at 0x7100c22a00.
extern void* gGlobalc22a00_36983c;
// Reached through the GOT slot at 0x7100c22f00.
extern unsigned char gGlobalc22f00_36983c[];
extern unsigned char gLocal7daaac_36983c[] __attribute__((visibility("hidden")));    // 0x71007daaac
extern unsigned char gLocal73fffb_36983c[] __attribute__((visibility("hidden")));    // 0x710073fffb
extern unsigned char gLocal7d6062_36983c[] __attribute__((visibility("hidden")));    // 0x71007d6062
extern unsigned char gLocal740004_36983c[] __attribute__((visibility("hidden")));    // 0x7100740004
extern unsigned char gLocal74053d_36983c[] __attribute__((visibility("hidden")));    // 0x710074053d
extern unsigned char gLocal74056c_36983c[] __attribute__((visibility("hidden")));    // 0x710074056c
extern unsigned char gLocal7daac1_36983c[] __attribute__((visibility("hidden")));    // 0x71007daac1
extern unsigned char gLocal7daacf_36983c[] __attribute__((visibility("hidden")));    // 0x71007daacf
extern unsigned char gLocal7d7e75_36983c[] __attribute__((visibility("hidden")));    // 0x71007d7e75
// Reached through the GOT slot at 0x7100c22f68.
extern unsigned char gGlobalc22f68_36983c[];

// 0x710036983c
int call_36983c(Arg36983c_0* p0) {
    p0->field_0 = nullptr;
    p0->field_30 = nullptr;
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x48));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x158));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1e0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x268));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2f0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x378));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x400));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x488));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x510));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x598));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x620));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x6a8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x730));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x7b8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x840));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x8c8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x950));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x9d8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xa60));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xae8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xb70));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xbf8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xc80));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd08));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd90));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xe18));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xea0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xf28));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xfb0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1038));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x10c0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1148));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x11d0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1258));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x12e0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1368));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x13f0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1478));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1500));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1588));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1610));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1698));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1720));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x17a8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1830));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x18b8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1940));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x19c8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1a50));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1ad8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1b60));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1be8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1c70));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1cf8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1d80));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1e08));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1e90));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1f18));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1fa0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2028));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x20b0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2138));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x21c0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2248));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x22d0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2358));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x23e0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2468));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x24f0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2578));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2600));
    new (reinterpret_cast<unsigned char*>(p0) + 0x2698) LayoutHandle;
    p0->field_26b0 = 0;
    p0->field_26b4 = 0;
    void* v72 = gGlobalc22a00_36983c;
    callee_1e2360(v72, p0, 0x4203, gLocal7daaac_36983c);
    void* v74 = gGlobalc22a00_36983c;
    callee_1e26e8(v74);
    Node36983c_v86* v76 = p0->field_0;
    void* c77 = callee_1e3770(v76, gLocal73fffb_36983c, 0);
    p0->field_8 = c77;
    Node36983c_v86* v78 = p0->field_0;
    void* c79 = callee_1e3770(v78, gLocal7d6062_36983c, 0);
    p0->field_10 = c79;
    Node36983c_v86* v80 = p0->field_0;
    void* c81 = callee_1e3770(v80, gLocal740004_36983c, 0);
    p0->field_18 = c81;
    Node36983c_v86* v82 = p0->field_0;
    void* c83 = callee_1e3770(v82, gLocal74053d_36983c, 0);
    p0->field_20 = c83;
    Node36983c_v86* v84 = p0->field_0;
    void* c85 = callee_1e3770(v84, gLocal74056c_36983c, 0);
    Node36983c_v86* v86 = p0->field_0;
    p0->field_28 = c85;
    Node36983c_v87* v87 = v86->field_18;
    void* c90 = v87->slot_12(gLocal7daac1_36983c, 1);
    Node36983c_v86* v91 = p0->field_0;
    p0->field_30 = c90;
    Node36983c_v87* v92 = v91->field_18;
    void* c95 = v92->slot_12(gLocal7daacf_36983c, 1);
    Node36983c_v86* v96 = p0->field_0;
    p0->field_38 = c95;
    Node36983c_v87* v97 = v96->field_18;
    void* c100 = v97->slot_12(gLocal7d7e75_36983c, 1);
    p0->field_40 = c100;
    PanelPane* m103 = new PanelPane;
    p0->field_2688 = reinterpret_cast<Node36983c_v114*>(m103);
    PanelPane* c105 = new PanelPane;
    void* v108 = p0->field_30;
    Node36983c_v114* v109 = p0->field_2688;
    p0->field_2690 = reinterpret_cast<Node36983c_v116*>(c105);
    callee_5da17c(v108, v109);
    void* v111 = p0->field_38;
    Node36983c_v116* v112 = p0->field_2690;
    int c113 = callee_5da17c(v111, v112);
    Node36983c_v114* v114 = p0->field_2688;
    unsigned char v115 = v114->field_5b;
    v114->field_5b = (v115 & 0xf3) | 8;
    Node36983c_v116* v116 = p0->field_2690;
    unsigned char v117 = v116->field_5b;
    v116->field_5b = (v117 & 0xf3) | 8;
    return c113;
}

void callee_339098(long);        // 0x7100339098
int callee_339154(void*);        // 0x7100339154
void callee_37cd6c(long);        // 0x710037cd6c
void callee_37dc14(long, int);        // 0x710037dc14
void callee_37f568(long);        // 0x710037f568
void callee_5d27b4(long);        // 0x71005d27b4

struct Arg33b748_0 {
    long field_0;                // +0
    unsigned char pad8[0x3a8];
    long field_3b0;                // +3b0
};
// Reached through the GOT slot at 0x7100c2aef8.
extern unsigned char gGlobalc2aef8_33b748[];
// Reached through the GOT slot at 0x7100c2aef0.
extern unsigned char gGlobalc2aef0_33b748[];

// 0x710033b748: the call at +0x3b8 passes a second argument, 0 (the generator had dropped it).
int call_33b748(Arg33b748_0* p0) {
    long a0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3b0);
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2aef8_33b748) + 0x10);
    callee_37dc14(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3b8), 0);
    p0->field_3b0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2aef0_33b748) + 0x10);
    callee_37cd6c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3b8));
    callee_5d27b4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3f0));
    callee_37f568(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3b8));
    callee_339098(a0);
    return callee_339154(p0);
}

void callee_1f16ec(long);        // 0x71001f16ec
int callee_1f69b8(long);        // 0x71001f69b8

struct Arg1ec528_0 {
    long field_0;                // +0
    unsigned char pad8[0x166d0];
    int field_166d8;                 // +166d8
    unsigned char pad166dc[0x44];
    void* field_16720;               // +16720
    unsigned char pad16728[0x18];
    void* field_16740;               // +16740
    void* field_16748;               // +16748
    unsigned char field_16750;       // +16750
    unsigned char pad16751[0x3];
    int field_16754;                 // +16754
    int field_16758;                 // +16758
    unsigned char field_1675c;       // +1675c
    unsigned char pad1675d[0x3];
    void* field_16760;               // +16760
    int field_16768;                 // +16768
    unsigned char pad1676c[0x1c];
    void* field_16788;               // +16788
    unsigned char field_16790;       // +16790
    unsigned char pad16791[0x3];
    int field_16794;                 // +16794
    int field_16798;                 // +16798
    unsigned char pad1679c[0x80];
    unsigned short field_1681c;      // +1681c
};

struct Elem1ec528_r9 {
    unsigned char pad0[0x88];
};
// Reached through the GOT slot at 0x7100c230e0.
extern unsigned char gGlobalc230e0_1ec528[];

// 0x71001ec528: the layout constructor's leading sprites as an array of nine, so the vtable store post-increments to the second sprite
class Class1ec528 {
public:
    Class1ec528();
    virtual void v00();

    LayoutSprite a8[9];
    LayoutFrame a290[128];
    LayoutSprite m4690;
};

Class1ec528::Class1ec528() {
    Arg1ec528_0* p0 = reinterpret_cast<Arg1ec528_0*>(this);
    long r13 = 0;
    do {
        callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x46d8) + r13);
        r13 = r13 + 0x48;
    } while (r13 != 0x12000);
    p0->field_166d8 = 0;
    callee_1f16ec(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x166e0));
    callee_1f16ec(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x16700));
    p0->field_16720 = nullptr;
    p0->field_16760 = nullptr;
    p0->field_16768 = 0;
    p0->field_16750 = 0;
    p0->field_16748 = nullptr;
    p0->field_16740 = nullptr;
    p0->field_1675c = 0;
    p0->field_16754 = 0;
    p0->field_16758 = 0;
    int c17 = callee_1f69b8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x16770));
    p0->field_16794 = 0;
    p0->field_16798 = 0;
    p0->field_1681c = 0;
    p0->field_16790 = 0;
    p0->field_16788 = nullptr;
}

struct Arg5f80bc_0 {
    long field_0;                // +0
    void* field_8;               // +8
    volatile int field_10;                 // +10
};
// Reached through the GOT slot at 0x7100c2de10.
extern unsigned char gGlobalc2de10_5f80bc[];

// 0x71005f80bc: one field volatile: the original keeps its store after the vtable store
void call_5f80bc(Arg5f80bc_0* p0) {
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2de10_5f80bc) + 0x10);
    p0->field_8 = nullptr;
    p0->field_10 = 0;
}

struct Arg5f37e8_0 {
    long field_0;                // +0
    void* field_8;               // +8
    void* field_10;               // +10
    int field_18;                 // +18
    unsigned char pad1c[0xc];
    volatile int field_28;                 // +28
};
// Reached through the GOT slot at 0x7100c2dde8.
extern unsigned char gGlobalc2dde8_5f37e8[];

// 0x71005f37e8: one field volatile: the original keeps its store after the vtable store
void call_5f37e8(Arg5f37e8_0* p0) {
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2dde8_5f37e8) + 0x10);
    p0->field_8 = nullptr;
    p0->field_10 = nullptr;
    p0->field_18 = 0;
    p0->field_28 = 0;
}

void callee_1f8720(long);        // 0x71001f8720
void callee_37b09c(void*);        // 0x710037b09c

struct Arg37af54_0 {
    unsigned char pad0[0x10];
    void* field_10;               // +10
    unsigned char pad18[0x50];
    long field_68;                // +68
};

struct Globalc22f00_37af54 {
    unsigned char pad0[0x28];
    void* field_28;               // +28
};

struct Bytes37af54_0 {
    unsigned char pad0[0x400];
    long field_400;                // +400
    unsigned char pad408[0x10];
    long field_418;                // +418
    unsigned char pad420[0x10];
    long field_430;                // +430
    unsigned char pad438[0x10];
    long field_448;                // +448
};

struct Node37af54_v6 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};
// Reached through the GOT slot at 0x7100c22f00.
extern Globalc22f00_37af54 gGlobalc22f00_37af54;
// Reached through the GOT slot at 0x7100c21db0.
extern Node37af54_v6* gGlobalc21db0_37af54;

// 0x710037af54: the last handle's address computed once, for its vtable store and the release call (the original's pre-indexed store)
int call_37af54(Arg37af54_0* p0) {
    void* v0 = p0->field_10;
    if (v0 != 0) {
        callee_37b09c(p0);
    }
    void* v3 = gGlobalc22f00_37af54.field_28;
    long r4 = 0;
    Node37af54_v6* v6;
    long m8;
    void* v7;
    Node37af54_v6* v10;
    long m12;
    void* v11;
    Node37af54_v6* v14;
    long m16;
    void* v15;
    Node37af54_v6* v18;
    long m20;
    void* v19;
    do {
        callee_1f8720(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + r4 + 0x460));
        reinterpret_cast<Bytes37af54_0*>(reinterpret_cast<unsigned char*>(p0) + r4)->field_448 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_37af54) + 0x10);
        v6 = gGlobalc21db0_37af54;
        if (v6 != 0) {
            v7 = v6->field_2af8;
            m8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v7) + 0x10);
        } else {
            m8 = 0;
        }
        reinterpret_cast<void (*)(long, long)>(v3)(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + r4 + 0x448), m8);
        reinterpret_cast<Bytes37af54_0*>(reinterpret_cast<unsigned char*>(p0) + r4)->field_430 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_37af54) + 0x10);
        v10 = gGlobalc21db0_37af54;
        if (v10 != 0) {
            v11 = v10->field_2af8;
            m12 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v11) + 0x10);
        } else {
            m12 = 0;
        }
        reinterpret_cast<void (*)(long, long)>(v3)(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + r4 + 0x430), m12);
        reinterpret_cast<Bytes37af54_0*>(reinterpret_cast<unsigned char*>(p0) + r4)->field_418 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_37af54) + 0x10);
        v14 = gGlobalc21db0_37af54;
        if (v14 != 0) {
            v15 = v14->field_2af8;
            m16 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v15) + 0x10);
        } else {
            m16 = 0;
        }
        reinterpret_cast<void (*)(long, long)>(v3)(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + r4 + 0x418), m16);
        reinterpret_cast<Bytes37af54_0*>(reinterpret_cast<unsigned char*>(p0) + r4)->field_400 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_37af54) + 0x10);
        v18 = gGlobalc21db0_37af54;
        if (v18 != 0) {
            v19 = v18->field_2af8;
            m20 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v19) + 0x10);
        } else {
            m20 = 0;
        }
        reinterpret_cast<void (*)(long, long)>(v3)(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + r4 + 0x400), m20);
        r4 = r4 - 0x120;
    } while (r4 != -0x480);
    long* h68 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x68);
    *h68 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_37af54) + 0x10);
    Node37af54_v6* v22 = gGlobalc21db0_37af54;
    long m24;
    if (v22 != 0) {
        void* v23 = v22->field_2af8;
        m24 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v23) + 0x10);
    } else {
        m24 = 0;
    }
    return reinterpret_cast<int (*)(long, long)>(v3)(reinterpret_cast<long>(h68), m24);
}

void callee_2d6e8c(long);        // 0x71002d6e8c
void callee_2f2ae4(long);        // 0x71002f2ae4
void callee_317288(long);        // 0x7100317288

struct Arg3527e8_0 {
    long field_0;                // +0
    unsigned char pad8[0x2ac28];
    long field_2ac30;                // +2ac30
    unsigned char pad2ac38[0x30728];
    long field_5b360;                // +5b360
    unsigned char pad5b368[0x30];
    long field_5b398;                // +5b398
    unsigned char pad5b3a0[0x10];
    long field_5b3b0;                // +5b3b0
    unsigned char pad5b3b8[0x10];
    long field_5b3c8;                // +5b3c8
};

struct Globalc22f00_3527e8 {
    unsigned char pad0[0x28];
    void* field_28;               // +28
};

struct Node3527e8_v1 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};
// Reached through the GOT slot at 0x7100c22f00.
extern Globalc22f00_3527e8 gGlobalc22f00_3527e8;
// Reached through the GOT slot at 0x7100c21db0.
extern Node3527e8_v1* gGlobalc21db0_3527e8;
// Reached through the GOT slot at 0x7100c2afc0.
extern unsigned char gGlobalc2afc0_3527e8[];

// 0x71003527e8
int call_3527e8(Arg3527e8_0* p0) {
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2afc0_3527e8) + 0x10);
    void* v0 = gGlobalc22f00_3527e8.field_28;
    p0->field_5b3c8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3527e8) + 0x10);
    Node3527e8_v1* v1 = gGlobalc21db0_3527e8;
    long m3;
    if (v1 != 0) {
        void* v2 = v1->field_2af8;
        m3 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v2) + 0x10);
    } else {
        m3 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5b3c8), m3);
    p0->field_5b3b0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3527e8) + 0x10);
    Node3527e8_v1* v5 = gGlobalc21db0_3527e8;
    long m7;
    if (v5 != 0) {
        void* v6 = v5->field_2af8;
        m7 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v6) + 0x10);
    } else {
        m7 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5b3b0), m7);
    p0->field_5b398 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3527e8) + 0x10);
    Node3527e8_v1* v9 = gGlobalc21db0_3527e8;
    long m11;
    if (v9 != 0) {
        void* v10 = v9->field_2af8;
        m11 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v10) + 0x10);
    } else {
        m11 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5b398), m11);
    p0->field_5b360 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3527e8) + 0x10);
    Node3527e8_v1* v13 = gGlobalc21db0_3527e8;
    long m15;
    if (v13 != 0) {
        void* v14 = v13->field_2af8;
        m15 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v14) + 0x10);
    } else {
        m15 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5b360), m15);
    callee_317288(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x45cc0));
    callee_2f2ae4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2ae10));
    callee_2d6e8c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2ac48));
    p0->field_2ac30 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3527e8) + 0x10);
    Node3527e8_v1* v20 = gGlobalc21db0_3527e8;
    long m22;
    if (v20 != 0) {
        void* v21 = v20->field_2af8;
        m22 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v21) + 0x10);
    } else {
        m22 = 0;
    }
    return reinterpret_cast<int (*)(long, long)>(v0)(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2ac30), m22);
}

void callee_287f38(long);        // 0x7100287f38

struct Arg2f2ae4_0 {
    unsigned char pad0[0x2a8];
    long field_2a8;                // +2a8
};

struct Globalc22f00_2f2ae4 {
    unsigned char pad0[0x28];
    void* field_28;               // +28
};

struct Node2f2ae4_v2 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};
// Reached through the GOT slot at 0x7100c22f00.
extern Globalc22f00_2f2ae4 gGlobalc22f00_2f2ae4;
// Reached through the GOT slot at 0x7100c21db0.
extern Node2f2ae4_v2* gGlobalc21db0_2f2ae4;

// 0x71002f2ae4: a stored address computed once and passed on (the original's pre-indexed store)
int call_2f2ae4(Arg2f2ae4_0* p0) {
    callee_287f38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x50cc));
    long* h2a8 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x2a8);
    *h2a8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2f2ae4) + 0x10);
    void* v1 = gGlobalc22f00_2f2ae4.field_28;
    Node2f2ae4_v2* v2 = gGlobalc21db0_2f2ae4;
    long m4;
    if (v2 != 0) {
        void* v3 = v2->field_2af8;
        m4 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v3) + 0x10);
    } else {
        m4 = 0;
    }
    return reinterpret_cast<int (*)(long, long)>(v1)(reinterpret_cast<long>(h2a8), m4);
}

void callee_5c3774(long, void*);        // 0x71005c3774
int callee2_5d27b4(long);        // 0x71005d27b4
void callee_5d4408(void*, long);        // 0x71005d4408

class Node1ef064_v5 {
public:
    virtual void slot_0();
    virtual void slot_1();
};

struct Arg1ef064_0 {
    unsigned char pad0[0x120];
    Node1ef064_v5* field_120;      // +120
    unsigned char pad128[0x8];
    long field_130;                // +130
    unsigned char pad138[0x10];
    long field_148;                // +148
};

struct Node1ef064_v2 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};

struct Globalc22f00_1ef064 {
    unsigned char pad0[0x28];
    void* field_28;               // +28
};
// Reached through the GOT slot at 0x7100c22a00.
extern void* gGlobalc22a00_1ef064;
// Reached through the GOT slot at 0x7100c21db0.
extern Node1ef064_v2* gGlobalc21db0_1ef064;
// Reached through the GOT slot at 0x7100c22f00.
extern Globalc22f00_1ef064 gGlobalc22f00_1ef064;

// 0x71001ef064: a stored address computed once and passed on (the original's pre-indexed store)
int call_1ef064(Arg1ef064_0* p0) {
    Node1ef064_v5* v0 = p0->field_120;
    if (v0 != 0) {
        void* v1 = gGlobalc22a00_1ef064;
        Node1ef064_v2* v2 = gGlobalc21db0_1ef064;
        void* v3 = v2->field_2af8;
        callee_5d4408(v0, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v3) + 0x10));
        Node1ef064_v5* v5 = p0->field_120;
        v5->slot_1();
        Node1ef064_v5* v9 = p0->field_120;
        callee_5c3774(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0x68), v9);
        p0->field_120 = nullptr;
    }
    long* h148 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x148);
    *h148 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_1ef064) + 0x10);
    void* v12 = gGlobalc22f00_1ef064.field_28;
    Node1ef064_v2* v13 = gGlobalc21db0_1ef064;
    long m15;
    if (v13 != 0) {
        void* v14 = v13->field_2af8;
        m15 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v14) + 0x10);
    } else {
        m15 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v12)(reinterpret_cast<long>(h148), m15);
    long* h130 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x130);
    *h130 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_1ef064) + 0x10);
    Node1ef064_v2* v17 = gGlobalc21db0_1ef064;
    long m19;
    if (v17 != 0) {
        void* v18 = v17->field_2af8;
        m19 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v18) + 0x10);
    } else {
        m19 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v12)(reinterpret_cast<long>(h130), m19);
    return callee2_5d27b4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x10));
}

void callee2_5c3774(long, void*);        // 0x71005c3774

class Node1f2124_v5 {
public:
    virtual void slot_0();
    virtual void slot_1();
};

struct Arg1f2124_0 {
    unsigned char pad0[0x120];
    Node1f2124_v5* field_120;      // +120
    unsigned char pad128[0x8];
    long field_130;                // +130
    unsigned char pad138[0x10];
    long field_148;                // +148
};

struct Node1f2124_v2 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};

struct Globalc22f00_1f2124 {
    unsigned char pad0[0x28];
    void* field_28;               // +28
};
// Reached through the GOT slot at 0x7100c22a00.
extern void* gGlobalc22a00_1f2124;
// Reached through the GOT slot at 0x7100c21db0.
extern Node1f2124_v2* gGlobalc21db0_1f2124;
// Reached through the GOT slot at 0x7100c22f00.
extern Globalc22f00_1f2124 gGlobalc22f00_1f2124;

// 0x71001f2124: a stored address computed once and passed on (the original's pre-indexed store)
int call_1f2124(Arg1f2124_0* p0) {
    Node1f2124_v5* v0 = p0->field_120;
    if (v0 != 0) {
        void* v1 = gGlobalc22a00_1f2124;
        Node1f2124_v2* v2 = gGlobalc21db0_1f2124;
        void* v3 = v2->field_2af8;
        callee_5d4408(v0, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v3) + 0x10));
        Node1f2124_v5* v5 = p0->field_120;
        v5->slot_1();
        Node1f2124_v5* v9 = p0->field_120;
        callee2_5c3774(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0x68), v9);
        p0->field_120 = nullptr;
    }
    long* h148 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x148);
    *h148 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_1f2124) + 0x10);
    void* v12 = gGlobalc22f00_1f2124.field_28;
    Node1f2124_v2* v13 = gGlobalc21db0_1f2124;
    long m15;
    if (v13 != 0) {
        void* v14 = v13->field_2af8;
        m15 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v14) + 0x10);
    } else {
        m15 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v12)(reinterpret_cast<long>(h148), m15);
    long* h130 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x130);
    *h130 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_1f2124) + 0x10);
    Node1f2124_v2* v17 = gGlobalc21db0_1f2124;
    long m19;
    if (v17 != 0) {
        void* v18 = v17->field_2af8;
        m19 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v18) + 0x10);
    } else {
        m19 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v12)(reinterpret_cast<long>(h130), m19);
    return callee2_5d27b4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x10));
}

void callee_1e2218(void*, long, int);        // 0x71001e2218
void callee3_5c3774(long, void*);        // 0x71005c3774
void callee_5da1b0(void*, void*);        // 0x71005da1b0

struct Node2b349c_v1 {
    unsigned char pad0[0x18];
    void* field_18;               // +18
};

class Node2b349c_v0 {
public:
    virtual void slot_0();
    virtual void slot_1();

    unsigned char pad8[0x10];
    Node2b349c_v1* field_18;      // +18
};

struct Arg2b349c_0 {
    unsigned char pad0[0x10];
    Node2b349c_v0* field_10;      // +10
    unsigned char pad18[0x8];
    long field_20;                // +20
};

struct Node2b349c_v6 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};

struct Globalc22f00_2b349c {
    unsigned char pad0[0x28];
    void* field_28;               // +28
};
// Reached through the GOT slot at 0x7100c22a00.
extern void* gGlobalc22a00_2b349c;
// Reached through the GOT slot at 0x7100c21db0.
extern Node2b349c_v6* gGlobalc21db0_2b349c;
// Reached through the GOT slot at 0x7100c22f00.
extern Globalc22f00_2b349c gGlobalc22f00_2b349c;

// 0x71002b349c: a stored address computed once and passed on (the original's pre-indexed store)
int call_2b349c(Arg2b349c_0* p0) {
    Node2b349c_v0* v0 = p0->field_10;
    if (v0 != 0) {
        Node2b349c_v1* v1 = v0->field_18;
        void* v2 = v1->field_18;
        if (v2 != 0) {
            callee_5da1b0(v2, v1);
            Node2b349c_v0* v4 = p0->field_10;
            if (v4 != 0) {
                void* v5 = gGlobalc22a00_2b349c;
                Node2b349c_v6* v6 = gGlobalc21db0_2b349c;
                void* v7 = v6->field_2af8;
                long a8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v7) + 0x10);
                callee_1e2218(v5, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v5) + 0x7b8), 0x4213);
                Node2b349c_v0* v10 = p0->field_10;
                callee_5d4408(v10, a8);
                Node2b349c_v0* v12 = p0->field_10;
                v12->slot_1();
                Node2b349c_v0* v16 = p0->field_10;
                callee3_5c3774(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v5) + 0xd8), v16);
                p0->field_10 = nullptr;
            }
        } else {
            void* v19 = gGlobalc22a00_2b349c;
            Node2b349c_v6* v20 = gGlobalc21db0_2b349c;
            void* v21 = v20->field_2af8;
            long a22 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v21) + 0x10);
            callee_1e2218(v19, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v19) + 0x7b8), 0x4213);
            Node2b349c_v0* v24 = p0->field_10;
            callee_5d4408(v24, a22);
            Node2b349c_v0* v26 = p0->field_10;
            v26->slot_1();
            Node2b349c_v0* v30 = p0->field_10;
            callee3_5c3774(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v19) + 0xd8), v30);
            p0->field_10 = nullptr;
        }
    }
    long* h20 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x20);
    *h20 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2b349c) + 0x10);
    void* v34 = gGlobalc22f00_2b349c.field_28;
    Node2b349c_v6* v35 = gGlobalc21db0_2b349c;
    long m37;
    if (v35 != 0) {
        void* v36 = v35->field_2af8;
        m37 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v36) + 0x10);
    } else {
        m37 = 0;
    }
    return reinterpret_cast<int (*)(long, long)>(v34)(reinterpret_cast<long>(h20), m37);
}

void callee2_1e2218(void*, long, int);        // 0x71001e2218

struct Node2b81b4_v1 {
    unsigned char pad0[0x18];
    void* field_18;               // +18
};

class Node2b81b4_v0 {
public:
    virtual void slot_0();
    virtual void slot_1();

    unsigned char pad8[0x10];
    Node2b81b4_v1* field_18;      // +18
};

struct Arg2b81b4_0 {
    unsigned char pad0[0x10];
    Node2b81b4_v0* field_10;      // +10
    unsigned char pad18[0x8];
    long field_20;                // +20
};

struct Node2b81b4_v6 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};

struct Globalc22f00_2b81b4 {
    unsigned char pad0[0x28];
    void* field_28;               // +28
};
// Reached through the GOT slot at 0x7100c22a00.
extern void* gGlobalc22a00_2b81b4;
// Reached through the GOT slot at 0x7100c21db0.
extern Node2b81b4_v6* gGlobalc21db0_2b81b4;
// Reached through the GOT slot at 0x7100c22f00.
extern Globalc22f00_2b81b4 gGlobalc22f00_2b81b4;

// 0x71002b81b4: a stored address computed once and passed on (the original's pre-indexed store)
int call_2b81b4(Arg2b81b4_0* p0) {
    Node2b81b4_v0* v0 = p0->field_10;
    if (v0 != 0) {
        Node2b81b4_v1* v1 = v0->field_18;
        void* v2 = v1->field_18;
        if (v2 != 0) {
            callee_5da1b0(v2, v1);
            Node2b81b4_v0* v4 = p0->field_10;
            if (v4 != 0) {
                void* v5 = gGlobalc22a00_2b81b4;
                Node2b81b4_v6* v6 = gGlobalc21db0_2b81b4;
                void* v7 = v6->field_2af8;
                long a8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v7) + 0x10);
                callee2_1e2218(v5, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v5) + 0x7b8), 0x4213);
                Node2b81b4_v0* v10 = p0->field_10;
                callee_5d4408(v10, a8);
                Node2b81b4_v0* v12 = p0->field_10;
                v12->slot_1();
                Node2b81b4_v0* v16 = p0->field_10;
                callee3_5c3774(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v5) + 0xd8), v16);
                p0->field_10 = nullptr;
            }
        } else {
            void* v19 = gGlobalc22a00_2b81b4;
            Node2b81b4_v6* v20 = gGlobalc21db0_2b81b4;
            void* v21 = v20->field_2af8;
            long a22 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v21) + 0x10);
            callee2_1e2218(v19, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v19) + 0x7b8), 0x4213);
            Node2b81b4_v0* v24 = p0->field_10;
            callee_5d4408(v24, a22);
            Node2b81b4_v0* v26 = p0->field_10;
            v26->slot_1();
            Node2b81b4_v0* v30 = p0->field_10;
            callee3_5c3774(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v19) + 0xd8), v30);
            p0->field_10 = nullptr;
        }
    }
    long* h20 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x20);
    *h20 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2b81b4) + 0x10);
    void* v34 = gGlobalc22f00_2b81b4.field_28;
    Node2b81b4_v6* v35 = gGlobalc21db0_2b81b4;
    long m37;
    if (v35 != 0) {
        void* v36 = v35->field_2af8;
        m37 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v36) + 0x10);
    } else {
        m37 = 0;
    }
    return reinterpret_cast<int (*)(long, long)>(v34)(reinterpret_cast<long>(h20), m37);
}


struct Arg3c8724_0 {
    unsigned char pad0[0x2f0];
    long field_2f0;                // +2f0
    unsigned char pad2f8[0x10];
    long field_308;                // +308
    unsigned char pad310[0x10];
    long field_320;                // +320
    unsigned char pad328[0x10];
    long field_338;                // +338
    unsigned char pad340[0x10];
    long field_350;                // +350
    unsigned char pad358[0x10];
    long field_368;                // +368
};

struct Globalc22f00_3c8724 {
    unsigned char pad0[0x28];
    void* field_28;               // +28
};

struct Node3c8724_v1 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};
// Reached through the GOT slot at 0x7100c22f00.
extern Globalc22f00_3c8724 gGlobalc22f00_3c8724;
// Reached through the GOT slot at 0x7100c21db0.
extern Node3c8724_v1* gGlobalc21db0_3c8724;

// 0x71003c8724: a stored address computed once and passed on (the original's pre-indexed store)
int call_3c8724(Arg3c8724_0* p0) {
    long* h368 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x368);
    *h368 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3c8724) + 0x10);
    void* v0 = gGlobalc22f00_3c8724.field_28;
    Node3c8724_v1* v1 = gGlobalc21db0_3c8724;
    long m3;
    if (v1 != 0) {
        void* v2 = v1->field_2af8;
        m3 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v2) + 0x10);
    } else {
        m3 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h368), m3);
    long* h350 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x350);
    *h350 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3c8724) + 0x10);
    Node3c8724_v1* v5 = gGlobalc21db0_3c8724;
    long m7;
    if (v5 != 0) {
        void* v6 = v5->field_2af8;
        m7 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v6) + 0x10);
    } else {
        m7 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h350), m7);
    long* h338 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x338);
    *h338 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3c8724) + 0x10);
    Node3c8724_v1* v9 = gGlobalc21db0_3c8724;
    long m11;
    if (v9 != 0) {
        void* v10 = v9->field_2af8;
        m11 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v10) + 0x10);
    } else {
        m11 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h338), m11);
    long* h320 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x320);
    *h320 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3c8724) + 0x10);
    Node3c8724_v1* v13 = gGlobalc21db0_3c8724;
    long m15;
    if (v13 != 0) {
        void* v14 = v13->field_2af8;
        m15 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v14) + 0x10);
    } else {
        m15 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h320), m15);
    long* h308 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x308);
    *h308 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3c8724) + 0x10);
    Node3c8724_v1* v17 = gGlobalc21db0_3c8724;
    long m19;
    if (v17 != 0) {
        void* v18 = v17->field_2af8;
        m19 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v18) + 0x10);
    } else {
        m19 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h308), m19);
    long* h2f0 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x2f0);
    *h2f0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3c8724) + 0x10);
    Node3c8724_v1* v21 = gGlobalc21db0_3c8724;
    long m23;
    if (v21 != 0) {
        void* v22 = v21->field_2af8;
        m23 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v22) + 0x10);
    } else {
        m23 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h2f0), m23);
    callee2_5d27b4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x120));
    return callee2_5d27b4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x10));
}


struct Globalc22f00_2a6fd0 {
    unsigned char pad0[0x28];
    void* field_28;               // +28
};

struct Arg2a6fd0_0 {
    unsigned char pad0[0x128];
    long field_128;                // +128
    unsigned char pad130[0x18];
    long field_148;                // +148
    unsigned char pad150[0x18];
    long field_168;                // +168
    unsigned char pad170[0x18];
    long field_188;                // +188
    unsigned char pad190[0x18];
    long field_1a8;                // +1a8
    unsigned char pad1b0[0x18];
    long field_1c8;                // +1c8
    unsigned char pad1d0[0x18];
    long field_1e8;                // +1e8
    unsigned char pad1f0[0x18];
    long field_208;                // +208
    unsigned char pad210[0x18];
    long field_228;                // +228
    unsigned char pad230[0x18];
    long field_248;                // +248
    unsigned char pad250[0x18];
    long field_268;                // +268
    unsigned char pad270[0x18];
    long field_288;                // +288
    unsigned char pad290[0x18];
    long field_2a8;                // +2a8
    unsigned char pad2b0[0x18];
    long field_2c8;                // +2c8
    unsigned char pad2d0[0x18];
    long field_2e8;                // +2e8
};

struct Node2a6fd0_v1 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};
// Reached through the GOT slot at 0x7100c22f00.
extern Globalc22f00_2a6fd0 gGlobalc22f00_2a6fd0;
// Reached through the GOT slot at 0x7100c21db0.
extern Node2a6fd0_v1* gGlobalc21db0_2a6fd0;

// 0x71002a6fd0: a stored address computed once and passed on (the original's pre-indexed store)
int call_2a6fd0(Arg2a6fd0_0* p0) {
    void* v0 = gGlobalc22f00_2a6fd0.field_28;
    long* h2e8 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x2e8);
    *h2e8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2a6fd0) + 0x10);
    Node2a6fd0_v1* v1 = gGlobalc21db0_2a6fd0;
    long m3;
    if (v1 != 0) {
        void* v2 = v1->field_2af8;
        m3 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v2) + 0x10);
    } else {
        m3 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h2e8), m3);
    long* h2c8 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x2c8);
    *h2c8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2a6fd0) + 0x10);
    Node2a6fd0_v1* v5 = gGlobalc21db0_2a6fd0;
    long m7;
    if (v5 != 0) {
        void* v6 = v5->field_2af8;
        m7 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v6) + 0x10);
    } else {
        m7 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h2c8), m7);
    long* h2a8 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x2a8);
    *h2a8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2a6fd0) + 0x10);
    Node2a6fd0_v1* v9 = gGlobalc21db0_2a6fd0;
    long m11;
    if (v9 != 0) {
        void* v10 = v9->field_2af8;
        m11 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v10) + 0x10);
    } else {
        m11 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h2a8), m11);
    long* h288 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x288);
    *h288 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2a6fd0) + 0x10);
    Node2a6fd0_v1* v13 = gGlobalc21db0_2a6fd0;
    long m15;
    if (v13 != 0) {
        void* v14 = v13->field_2af8;
        m15 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v14) + 0x10);
    } else {
        m15 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h288), m15);
    long* h268 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x268);
    *h268 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2a6fd0) + 0x10);
    Node2a6fd0_v1* v17 = gGlobalc21db0_2a6fd0;
    long m19;
    if (v17 != 0) {
        void* v18 = v17->field_2af8;
        m19 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v18) + 0x10);
    } else {
        m19 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h268), m19);
    long* h248 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x248);
    *h248 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2a6fd0) + 0x10);
    Node2a6fd0_v1* v21 = gGlobalc21db0_2a6fd0;
    long m23;
    if (v21 != 0) {
        void* v22 = v21->field_2af8;
        m23 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v22) + 0x10);
    } else {
        m23 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h248), m23);
    long* h228 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x228);
    *h228 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2a6fd0) + 0x10);
    Node2a6fd0_v1* v25 = gGlobalc21db0_2a6fd0;
    long m27;
    if (v25 != 0) {
        void* v26 = v25->field_2af8;
        m27 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v26) + 0x10);
    } else {
        m27 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h228), m27);
    long* h208 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x208);
    *h208 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2a6fd0) + 0x10);
    Node2a6fd0_v1* v29 = gGlobalc21db0_2a6fd0;
    long m31;
    if (v29 != 0) {
        void* v30 = v29->field_2af8;
        m31 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v30) + 0x10);
    } else {
        m31 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h208), m31);
    long* h1e8 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x1e8);
    *h1e8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2a6fd0) + 0x10);
    Node2a6fd0_v1* v33 = gGlobalc21db0_2a6fd0;
    long m35;
    if (v33 != 0) {
        void* v34 = v33->field_2af8;
        m35 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v34) + 0x10);
    } else {
        m35 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h1e8), m35);
    long* h1c8 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x1c8);
    *h1c8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2a6fd0) + 0x10);
    Node2a6fd0_v1* v37 = gGlobalc21db0_2a6fd0;
    long m39;
    if (v37 != 0) {
        void* v38 = v37->field_2af8;
        m39 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v38) + 0x10);
    } else {
        m39 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h1c8), m39);
    long* h1a8 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x1a8);
    *h1a8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2a6fd0) + 0x10);
    Node2a6fd0_v1* v41 = gGlobalc21db0_2a6fd0;
    long m43;
    if (v41 != 0) {
        void* v42 = v41->field_2af8;
        m43 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v42) + 0x10);
    } else {
        m43 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h1a8), m43);
    long* h188 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x188);
    *h188 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2a6fd0) + 0x10);
    Node2a6fd0_v1* v45 = gGlobalc21db0_2a6fd0;
    long m47;
    if (v45 != 0) {
        void* v46 = v45->field_2af8;
        m47 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v46) + 0x10);
    } else {
        m47 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h188), m47);
    long* h168 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x168);
    *h168 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2a6fd0) + 0x10);
    Node2a6fd0_v1* v49 = gGlobalc21db0_2a6fd0;
    long m51;
    if (v49 != 0) {
        void* v50 = v49->field_2af8;
        m51 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v50) + 0x10);
    } else {
        m51 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h168), m51);
    long* h148 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x148);
    *h148 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2a6fd0) + 0x10);
    Node2a6fd0_v1* v53 = gGlobalc21db0_2a6fd0;
    long m55;
    if (v53 != 0) {
        void* v54 = v53->field_2af8;
        m55 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v54) + 0x10);
    } else {
        m55 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h148), m55);
    long* h128 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x128);
    *h128 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2a6fd0) + 0x10);
    Node2a6fd0_v1* v57 = gGlobalc21db0_2a6fd0;
    long m59;
    if (v57 != 0) {
        void* v58 = v57->field_2af8;
        m59 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v58) + 0x10);
    } else {
        m59 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h128), m59);
    return callee2_5d27b4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x10));
}

void callee3_1e2218(void*, long, int);        // 0x71001e2218

class Node34d974_v8 {
public:
    virtual void slot_0();
    virtual void slot_1();
};

struct Arg34d974_0 {
    unsigned char pad0[0x10];
    Node34d974_v8* field_10;      // +10
    unsigned char pad18[0x60];
    long field_78;                // +78
    unsigned char pad80[0x10];
    long field_90;                // +90
};

struct Node34d974_v2 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};

struct Globalc22f00_34d974 {
    unsigned char pad0[0x28];
    void* field_28;               // +28
};
// Reached through the GOT slot at 0x7100c22a00.
extern void* gGlobalc22a00_34d974;
// Reached through the GOT slot at 0x7100c21db0.
extern Node34d974_v2* gGlobalc21db0_34d974;
// Reached through the GOT slot at 0x7100c22f00.
extern Globalc22f00_34d974 gGlobalc22f00_34d974;

// 0x710034d974: the two handles' addresses computed once, for each vtable store and release call (the original's pre-indexed stores)
int call_34d974(Arg34d974_0* p0) {
    Node34d974_v8* v0 = p0->field_10;
    if (v0 != 0) {
        void* v1 = gGlobalc22a00_34d974;
        Node34d974_v2* v2 = gGlobalc21db0_34d974;
        void* v3 = v2->field_2af8;
        long a4 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v3) + 0x10);
        callee3_1e2218(v1, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0x7b8), 0x41ff);
        Node34d974_v8* v6 = p0->field_10;
        callee_5d4408(v6, a4);
        Node34d974_v8* v8 = p0->field_10;
        v8->slot_1();
        Node34d974_v8* v12 = p0->field_10;
        callee3_5c3774(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd8), v12);
        p0->field_10 = nullptr;
    }
    long* h90 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x90);
    *h90 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_34d974) + 0x10);
    void* v15 = gGlobalc22f00_34d974.field_28;
    Node34d974_v2* v16 = gGlobalc21db0_34d974;
    long m18;
    if (v16 != 0) {
        void* v17 = v16->field_2af8;
        m18 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v17) + 0x10);
    } else {
        m18 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v15)(reinterpret_cast<long>(h90), m18);
    long* h78 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x78);
    *h78 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_34d974) + 0x10);
    Node34d974_v2* v20 = gGlobalc21db0_34d974;
    long m22;
    if (v20 != 0) {
        void* v21 = v20->field_2af8;
        m22 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v21) + 0x10);
    } else {
        m22 = 0;
    }
    return reinterpret_cast<int (*)(long, long)>(v15)(reinterpret_cast<long>(h78), m22);
}
