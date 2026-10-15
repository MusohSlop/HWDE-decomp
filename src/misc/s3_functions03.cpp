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

struct Argc5df8_0 {
    long field_0;                // +0
    int field_8;                 // +8
    int field_c;                 // +c
    int field_10;                 // +10
    long field_14 __attribute__((packed));                // +14
};
// Reached through the GOT slot at 0x7100c22860.
extern unsigned char gGlobalc22860_c5df8[];

// 0x71000c5df8: the int pair at +14 as one packed 8-byte field, stored after the vtable
void call_c5df8(Argc5df8_0* p0) {
    p0->field_8 = -1;
    p0->field_c = -1;
    p0->field_10 = 0;
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc22860_c5df8) + 0x10);
    p0->field_14 = static_cast<unsigned long>(static_cast<unsigned int>(-1));
}

struct Arg1f18e8_0 {
    long field_0;                // +0
    int field_8;                 // +8
    int field_c;                 // +c
};
// Reached through the GOT slot at 0x7100c23148.
extern unsigned char gGlobalc23148_1f18e8[];

// 0x71001f18e8: stores in the original's order
void call_1f18e8(Arg1f18e8_0* p0) {
    p0->field_8 = -0x5fcffffb;
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc23148_1f18e8) + 0x10);
    p0->field_c = 0;
}

int callee_1e26e0(void*, long);        // 0x71001e26e0
void callee_3c7188(void*);        // 0x71003c7188

struct Arg3aa468_0 {
    long field_0;                // +0
    unsigned char pad8[0x20];
    void* field_28;               // +28
    void* field_30;               // +30
    int field_38;                 // +38
    unsigned char pad3c[0x4];
    void* field_40;               // +40
    void* field_48;               // +48
    void* field_50;               // +50
    void* field_58;               // +58
    void* field_60;               // +60
    void* field_68;               // +68
    unsigned char pad70[0x220];
    volatile int field_290;                 // +290
    unsigned char pad294[0x4];
    void* field_298;               // +298
    void* field_2a0;               // +2a0
    unsigned char pad2a8[0x18];
    void* field_2c0;               // +2c0
    void* field_2c8;               // +2c8
    long field_2d0;                // +2d0
    long field_2d8;                // +2d8
    int field_2e0;                 // +2e0
    unsigned char pad2e4[0x4];
    unsigned short field_2e8;      // +2e8
    unsigned char pad2ea[0x6];
    void* field_2f0;               // +2f0
    void* field_2f8;               // +2f8
    void* field_300;               // +300
    int field_308;                 // +308
    unsigned char pad30c[0x4];
    void* field_310;               // +310
};
// Reached through the GOT slot at 0x7100c22a00.
extern void* gGlobalc22a00_3aa468;
// Reached through the GOT slot at 0x7100c2adb8.
extern unsigned char gGlobalc2adb8_3aa468[];
// Reached through the GOT slot at 0x7100c22f00.
extern unsigned char gGlobalc22f00_3aa468[];

// 0x71003aa468: one field volatile: the original keeps its store in source order
int call_3aa468(Arg3aa468_0* p0) {
    callee_3c7188(p0);
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2adb8_3aa468) + 0x10);
    p0->field_28 = nullptr;
    p0->field_30 = nullptr;
    p0->field_38 = 2;
    callee_5d2744(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x70));
    callee_5d2744(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x180));
    p0->field_2c8 = nullptr;
    p0->field_2c0 = nullptr;
    p0->field_290 = 0;
    p0->field_2a0 = nullptr;
    p0->field_298 = nullptr;
    new (reinterpret_cast<unsigned char*>(p0) + 0x2d0) LayoutHandle;
    p0->field_2e8 = 0;
    p0->field_308 = 0;
    p0->field_300 = nullptr;
    p0->field_2f8 = nullptr;
    p0->field_2f0 = nullptr;
    void* v3 = gGlobalc22a00_3aa468;
    callee_1e26dc(v3, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x70), 0);
    void* v5 = gGlobalc22a00_3aa468;
    int c6 = callee_1e26e0(v5, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x180));
    p0->field_310 = nullptr;
    p0->field_60 = nullptr;
    p0->field_68 = nullptr;
    p0->field_50 = nullptr;
    p0->field_58 = nullptr;
    p0->field_40 = nullptr;
    p0->field_48 = nullptr;
    return c6;
}

struct Arg1f1c8c_0 {
    long field_0;                // +0
    int field_8;                 // +8
    int field_c;                 // +c
};
// Reached through the GOT slot at 0x7100c23150.
extern unsigned char gGlobalc23150_1f1c8c[];

// 0x71001f1c8c: stores in the original's order
void call_1f1c8c(Arg1f1c8c_0* p0) {
    p0->field_8 = -0x5fcffffa;
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc23150_1f1c8c) + 0x10);
    p0->field_c = 2;
}

struct Arg75bd4_0 {
    long field_0;                // +0
    void* field_8;               // +8
    void* field_10;               // +10
    void* field_18;               // +18
    int field_20;                 // +20
    unsigned char pad24[0x4];
    void* field_28;               // +28
    int field_30;                 // +30
};
// Reached through the GOT slot at 0x7100c221a0.
extern unsigned char gGlobalc221a0_75bd4[];

// 0x7100075bd4: stores in the original's order
void call_75bd4(Arg75bd4_0* p0) {
    p0->field_10 = nullptr;
    p0->field_18 = nullptr;
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc221a0_75bd4) + 0x10);
    p0->field_20 = 0;
    p0->field_8 = nullptr;
    p0->field_28 = nullptr;
    p0->field_30 = 0;
}

// 0x7100053958: converted to a class, with a field at an offset its type would not get declared packed
class Class53958 {
public:
    Class53958();
    virtual void v00();

    void* f8;
    void* f10;
    int f18;
    int f1c;
    int f20;
    long f24 __attribute__((packed));
};

Class53958::Class53958()
    : f8(nullptr), f10(nullptr), f18(-1), f1c(-1), f20(0), f24(-1) {}

// 0x7100441a44: converted to a class, with a field at an offset its type would not get declared packed
class Class441a44 {
public:
    Class441a44();
    virtual void v00();

    void* f8;
    void* f10;
    int f18;
    int f1c;
    unsigned char pad20[0x810];
    void* f830;
    unsigned char pad838[0x48];
    void* f880;
    void* f888;
    void* f890;
    void* f898;
    unsigned char pad8a0[0x8];
    int f8a8;
    void* f8ac __attribute__((packed));
    void* f8b4 __attribute__((packed));
};

Class441a44::Class441a44()
    : f8(nullptr), f10(nullptr), f18(0), f1c(-1), f830(nullptr), f880(nullptr), f888(nullptr), f890(nullptr), f898(nullptr), f8a8(0x64), f8ac(nullptr), f8b4(nullptr) {}

struct Arg1f69c8_0 {
    long field_0;                // +0
    int field_8;                 // +8
    int field_c;                 // +c
    void* field_10;               // +10
    void* field_18;               // +18
};
// Reached through the GOT slot at 0x7100c231d8.
extern unsigned char gGlobalc231d8_1f69c8[];

// 0x71001f69c8: stores in the original's order
void call_1f69c8(Arg1f69c8_0* p0) {
    p0->field_10 = nullptr;
    p0->field_18 = nullptr;
    p0->field_8 = 0x10000302;
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc231d8_1f69c8) + 0x10);
    p0->field_c = -1;
}

struct Arg58a28_0 {
    long field_0;                // +0
    void* field_8;               // +8
    void* field_10;               // +10
    int field_18;                 // +18
    int field_1c;                 // +1c
    int field_20;                 // +20
    unsigned char pad24[0x4];
    void* field_28;               // +28
    void* field_30;               // +30
};
// Reached through the GOT slot at 0x7100c22028.
extern unsigned char gGlobalc22028_58a28[];

// 0x7100058a28: stores in the original's order
void call_58a28(Arg58a28_0* p0) {
    p0->field_10 = nullptr;
    p0->field_18 = -1;
    p0->field_1c = -1;
    p0->field_28 = nullptr;
    p0->field_30 = nullptr;
    p0->field_8 = nullptr;
    p0->field_20 = 0;
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc22028_58a28) + 0x10);
}

struct Arg5b0124_0 {
    long field_0;                // +0
    int field_8;                 // +8
    int field_c;                 // +c
    int field_10;                 // +10
    unsigned char pad14[0x4];
    void* field_18;               // +18
    void* field_20;               // +20
    void* field_28;               // +28
};
// Reached through the GOT slot at 0x7100c2d930.
extern unsigned char gGlobalc2d930_5b0124[];

// 0x71005b0124: stores in the original's order
void call_5b0124(Arg5b0124_0* p0) {
    p0->field_8 = 0;
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2d930_5b0124) + 0x10);
    p0->field_c = 0;
    p0->field_10 = 0;
    p0->field_20 = nullptr;
    p0->field_28 = nullptr;
    p0->field_18 = nullptr;
}

void callee_1f4704(int);        // 0x71001f4704
int callee_316aa4(void*);        // 0x7100316aa4

struct Arg3322ac_0 {
    long field_0;                // +0
    unsigned char pad8[0x58];
    int field_60;                 // +60
    unsigned char pad64[0x4];
    int field_68;                 // +68
    unsigned char pad6c[0x4];
    void* field_70;               // +70
    int field_78;                 // +78
    unsigned char pad7c[0x18484];
    float field_18500;                 // +18500
    int field_18504;                 // +18504
    unsigned char pad18508[0x8];
    int field_18510;                 // +18510
    unsigned char pad18514[0x27c];
    long field_18790;                // +18790
};

struct Globalc22f00_3322ac {
    unsigned char pad0[0x28];
    void* field_28;               // +28
};

struct Node3322ac_v2 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};
// Reached through the GOT slot at 0x7100c22f00.
extern Globalc22f00_3322ac gGlobalc22f00_3322ac;
// Reached through the GOT slot at 0x7100c21db0.
extern Node3322ac_v2* gGlobalc21db0_3322ac;
// Reached through the GOT slot at 0x7100c2ae30.
extern unsigned char gGlobalc2ae30_3322ac[];

// 0x71003322ac: the field at +18500 is a float: a zero stored as float is not merged with the int at +18504
int call_3322ac(Arg3322ac_0* p0) {
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2ae30_3322ac) + 0x10);
    p0->field_18500 = 0.0f;
    p0->field_18510 = 0;
    p0->field_18504 = 0;
    callee_1f4704(0x11);
    p0->field_18790 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3322ac) + 0x10);
    void* v1 = gGlobalc22f00_3322ac.field_28;
    Node3322ac_v2* v2 = gGlobalc21db0_3322ac;
    long m4;
    if (v2 != 0) {
        void* v3 = v2->field_2af8;
        m4 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v3) + 0x10);
    } else {
        m4 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x18790), m4);
    callee_5d27b4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x18640));
    callee_5d27b4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x18530));
    p0->field_60 = 0;
    p0->field_68 = 0;
    p0->field_70 = nullptr;
    p0->field_78 = 0;
    callee_1f4704(0x11);
    callee_37f568(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x18468));
    callee_5d27b4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x90));
    return callee_316aa4(p0);
}

struct Arg2d6e8c_0 {
    unsigned char field_0;       // +0
    unsigned char pad1[0x37];
    long field_38;                // +38
    unsigned char pad40[0x10];
    long field_50;                // +50
    unsigned char pad58[0x10];
    long field_68;                // +68
    unsigned char pad70[0x10];
    long field_80;                // +80
    unsigned char pad88[0x10];
    long field_98;                // +98
    unsigned char pada0[0x10];
    long field_b0;                // +b0
    unsigned char padb8[0x10];
    long field_c8;                // +c8
    unsigned char padd0[0x10];
    long field_e0;                // +e0
    unsigned char pade8[0x10];
    long field_f8;                // +f8
    unsigned char pad100[0x10];
    long field_110;                // +110
    unsigned char pad118[0x10];
    long field_128;                // +128
    unsigned char pad130[0x10];
    long field_140;                // +140
    unsigned char pad148[0x10];
    long field_158;                // +158
    unsigned char pad160[0x10];
    long field_170;                // +170
    unsigned char pad178[0x10];
    long field_188;                // +188
    unsigned char pad190[0x10];
    long field_1a0;                // +1a0
};

struct Globalc22f00_2d6e8c {
    unsigned char pad0[0x28];
    void* field_28;               // +28
};

struct Node2d6e8c_v3 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};
// Reached through the GOT slot at 0x7100c2ab08.
extern unsigned char gGlobalc2ab08_2d6e8c;
// Reached through the GOT slot at 0x7100c2ab30.
extern unsigned char gGlobalc2ab30_2d6e8c[];
// Reached through the GOT slot at 0x7100c22f00.
extern Globalc22f00_2d6e8c gGlobalc22f00_2d6e8c;
// Reached through the GOT slot at 0x7100c21db0.
extern Node2d6e8c_v3* gGlobalc21db0_2d6e8c;

// 0x71002d6e8c: handle addresses computed once; the global counter decremented with --
int call_2d6e8c(Arg2d6e8c_0* p0) {
    gGlobalc2ab08_2d6e8c--;
    unsigned char v1 = p0->field_0;
    gGlobalc2ab30_2d6e8c[static_cast<unsigned long>(static_cast<unsigned int>(v1))] = 0;
    long* h1a0 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x1a0);
    *h1a0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2d6e8c) + 0x10);
    void* v2 = gGlobalc22f00_2d6e8c.field_28;
    Node2d6e8c_v3* v3 = gGlobalc21db0_2d6e8c;
    long m5;
    if (v3 != 0) {
        void* v4 = v3->field_2af8;
        m5 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v4) + 0x10);
    } else {
        m5 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v2)(reinterpret_cast<long>(h1a0), m5);
    long* h188 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x188);
    *h188 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2d6e8c) + 0x10);
    Node2d6e8c_v3* v7 = gGlobalc21db0_2d6e8c;
    long m9;
    if (v7 != 0) {
        void* v8 = v7->field_2af8;
        m9 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v8) + 0x10);
    } else {
        m9 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v2)(reinterpret_cast<long>(h188), m9);
    long* h170 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x170);
    *h170 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2d6e8c) + 0x10);
    Node2d6e8c_v3* v11 = gGlobalc21db0_2d6e8c;
    long m13;
    if (v11 != 0) {
        void* v12 = v11->field_2af8;
        m13 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v12) + 0x10);
    } else {
        m13 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v2)(reinterpret_cast<long>(h170), m13);
    long* h158 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x158);
    *h158 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2d6e8c) + 0x10);
    Node2d6e8c_v3* v15 = gGlobalc21db0_2d6e8c;
    long m17;
    if (v15 != 0) {
        void* v16 = v15->field_2af8;
        m17 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v16) + 0x10);
    } else {
        m17 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v2)(reinterpret_cast<long>(h158), m17);
    long* h140 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x140);
    *h140 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2d6e8c) + 0x10);
    Node2d6e8c_v3* v19 = gGlobalc21db0_2d6e8c;
    long m21;
    if (v19 != 0) {
        void* v20 = v19->field_2af8;
        m21 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v20) + 0x10);
    } else {
        m21 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v2)(reinterpret_cast<long>(h140), m21);
    long* h128 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x128);
    *h128 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2d6e8c) + 0x10);
    Node2d6e8c_v3* v23 = gGlobalc21db0_2d6e8c;
    long m25;
    if (v23 != 0) {
        void* v24 = v23->field_2af8;
        m25 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v24) + 0x10);
    } else {
        m25 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v2)(reinterpret_cast<long>(h128), m25);
    long* h110 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x110);
    *h110 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2d6e8c) + 0x10);
    Node2d6e8c_v3* v27 = gGlobalc21db0_2d6e8c;
    long m29;
    if (v27 != 0) {
        void* v28 = v27->field_2af8;
        m29 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v28) + 0x10);
    } else {
        m29 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v2)(reinterpret_cast<long>(h110), m29);
    long* hf8 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0xf8);
    *hf8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2d6e8c) + 0x10);
    Node2d6e8c_v3* v31 = gGlobalc21db0_2d6e8c;
    long m33;
    if (v31 != 0) {
        void* v32 = v31->field_2af8;
        m33 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v32) + 0x10);
    } else {
        m33 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v2)(reinterpret_cast<long>(hf8), m33);
    long* he0 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0xe0);
    *he0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2d6e8c) + 0x10);
    Node2d6e8c_v3* v35 = gGlobalc21db0_2d6e8c;
    long m37;
    if (v35 != 0) {
        void* v36 = v35->field_2af8;
        m37 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v36) + 0x10);
    } else {
        m37 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v2)(reinterpret_cast<long>(he0), m37);
    long* hc8 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0xc8);
    *hc8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2d6e8c) + 0x10);
    Node2d6e8c_v3* v39 = gGlobalc21db0_2d6e8c;
    long m41;
    if (v39 != 0) {
        void* v40 = v39->field_2af8;
        m41 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v40) + 0x10);
    } else {
        m41 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v2)(reinterpret_cast<long>(hc8), m41);
    long* hb0 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0xb0);
    *hb0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2d6e8c) + 0x10);
    Node2d6e8c_v3* v43 = gGlobalc21db0_2d6e8c;
    long m45;
    if (v43 != 0) {
        void* v44 = v43->field_2af8;
        m45 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v44) + 0x10);
    } else {
        m45 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v2)(reinterpret_cast<long>(hb0), m45);
    long* h98 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x98);
    *h98 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2d6e8c) + 0x10);
    Node2d6e8c_v3* v47 = gGlobalc21db0_2d6e8c;
    long m49;
    if (v47 != 0) {
        void* v48 = v47->field_2af8;
        m49 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v48) + 0x10);
    } else {
        m49 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v2)(reinterpret_cast<long>(h98), m49);
    long* h80 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x80);
    *h80 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2d6e8c) + 0x10);
    Node2d6e8c_v3* v51 = gGlobalc21db0_2d6e8c;
    long m53;
    if (v51 != 0) {
        void* v52 = v51->field_2af8;
        m53 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v52) + 0x10);
    } else {
        m53 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v2)(reinterpret_cast<long>(h80), m53);
    long* h68 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x68);
    *h68 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2d6e8c) + 0x10);
    Node2d6e8c_v3* v55 = gGlobalc21db0_2d6e8c;
    long m57;
    if (v55 != 0) {
        void* v56 = v55->field_2af8;
        m57 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v56) + 0x10);
    } else {
        m57 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v2)(reinterpret_cast<long>(h68), m57);
    long* h50 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x50);
    *h50 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2d6e8c) + 0x10);
    Node2d6e8c_v3* v59 = gGlobalc21db0_2d6e8c;
    long m61;
    if (v59 != 0) {
        void* v60 = v59->field_2af8;
        m61 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v60) + 0x10);
    } else {
        m61 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v2)(reinterpret_cast<long>(h50), m61);
    long* h38 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x38);
    *h38 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2d6e8c) + 0x10);
    Node2d6e8c_v3* v63 = gGlobalc21db0_2d6e8c;
    long m65;
    if (v63 != 0) {
        void* v64 = v63->field_2af8;
        m65 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v64) + 0x10);
    } else {
        m65 = 0;
    }
    return reinterpret_cast<int (*)(long, long)>(v2)(reinterpret_cast<long>(h38), m65);
}

struct Globalc22f00_29b370 {
    unsigned char pad0[0x28];
    void* field_28;               // +28
};

struct Arg29b370_0 {
    unsigned char pad0[0xa8];
    long field_a8;                // +a8
    unsigned char padb0[0x18];
    long field_c8;                // +c8
    unsigned char padd0[0x18];
    long field_e8;                // +e8
    unsigned char padf0[0x18];
    long field_108;                // +108
    unsigned char pad110[0x18];
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
};

struct Node29b370_v1 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};
// Reached through the GOT slot at 0x7100c22f00.
extern Globalc22f00_29b370 gGlobalc22f00_29b370;
// Reached through the GOT slot at 0x7100c21db0.
extern Node29b370_v1* gGlobalc21db0_29b370;

// 0x710029b370: handle addresses computed once, for each vtable store and release call (the original's pre-indexed stores)
int call_29b370(Arg29b370_0* p0) {
    void* v0 = gGlobalc22f00_29b370.field_28;
    long* h1c8 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x1c8);
    *h1c8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_29b370) + 0x10);
    Node29b370_v1* v1 = gGlobalc21db0_29b370;
    long m3;
    if (v1 != 0) {
        void* v2 = v1->field_2af8;
        m3 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v2) + 0x10);
    } else {
        m3 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h1c8), m3);
    long* h1a8 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x1a8);
    *h1a8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_29b370) + 0x10);
    Node29b370_v1* v5 = gGlobalc21db0_29b370;
    long m7;
    if (v5 != 0) {
        void* v6 = v5->field_2af8;
        m7 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v6) + 0x10);
    } else {
        m7 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h1a8), m7);
    long* h188 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x188);
    *h188 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_29b370) + 0x10);
    Node29b370_v1* v9 = gGlobalc21db0_29b370;
    long m11;
    if (v9 != 0) {
        void* v10 = v9->field_2af8;
        m11 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v10) + 0x10);
    } else {
        m11 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h188), m11);
    long* h168 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x168);
    *h168 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_29b370) + 0x10);
    Node29b370_v1* v13 = gGlobalc21db0_29b370;
    long m15;
    if (v13 != 0) {
        void* v14 = v13->field_2af8;
        m15 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v14) + 0x10);
    } else {
        m15 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h168), m15);
    long* h148 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x148);
    *h148 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_29b370) + 0x10);
    Node29b370_v1* v17 = gGlobalc21db0_29b370;
    long m19;
    if (v17 != 0) {
        void* v18 = v17->field_2af8;
        m19 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v18) + 0x10);
    } else {
        m19 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h148), m19);
    long* h128 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x128);
    *h128 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_29b370) + 0x10);
    Node29b370_v1* v21 = gGlobalc21db0_29b370;
    long m23;
    if (v21 != 0) {
        void* v22 = v21->field_2af8;
        m23 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v22) + 0x10);
    } else {
        m23 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h128), m23);
    long* h108 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x108);
    *h108 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_29b370) + 0x10);
    Node29b370_v1* v25 = gGlobalc21db0_29b370;
    long m27;
    if (v25 != 0) {
        void* v26 = v25->field_2af8;
        m27 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v26) + 0x10);
    } else {
        m27 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h108), m27);
    long* he8 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0xe8);
    *he8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_29b370) + 0x10);
    Node29b370_v1* v29 = gGlobalc21db0_29b370;
    long m31;
    if (v29 != 0) {
        void* v30 = v29->field_2af8;
        m31 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v30) + 0x10);
    } else {
        m31 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(he8), m31);
    long* hc8 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0xc8);
    *hc8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_29b370) + 0x10);
    Node29b370_v1* v33 = gGlobalc21db0_29b370;
    long m35;
    if (v33 != 0) {
        void* v34 = v33->field_2af8;
        m35 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v34) + 0x10);
    } else {
        m35 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(hc8), m35);
    long* ha8 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0xa8);
    *ha8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_29b370) + 0x10);
    Node29b370_v1* v37 = gGlobalc21db0_29b370;
    long m39;
    if (v37 != 0) {
        void* v38 = v37->field_2af8;
        m39 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v38) + 0x10);
    } else {
        m39 = 0;
    }
    return reinterpret_cast<int (*)(long, long)>(v0)(reinterpret_cast<long>(ha8), m39);
}

void callee_2fcc8c(void*);        // 0x71002fcc8c

struct Globalc22f00_300d3c {
    unsigned char pad0[0x28];
    void* field_28;               // +28
};

struct Arg300d3c_0 {
    unsigned char pad0[0x3390];
    long field_3390;                // +3390
    unsigned char pad3398[0x28];
    long field_33c0;                // +33c0
    unsigned char pad33c8[0x28];
    long field_33f0;                // +33f0
    unsigned char pad33f8[0x28];
    long field_3420;                // +3420
    unsigned char pad3428[0x28];
    long field_3450;                // +3450
    unsigned char pad3458[0x28];
    long field_3480;                // +3480
    unsigned char pad3488[0x28];
    long field_34b0;                // +34b0
    unsigned char pad34b8[0x28];
    long field_34e0;                // +34e0
    unsigned char pad34e8[0x28];
    long field_3510;                // +3510
    unsigned char pad3518[0x28];
    long field_3540;                // +3540
    unsigned char pad3548[0x28];
    long field_3570;                // +3570
    unsigned char pad3578[0x28];
    long field_35a0;                // +35a0
    unsigned char pad35a8[0x4a0];
    long field_3a48;                // +3a48
    unsigned char pad3a50[0x4b0];
    long field_3f00;                // +3f00
    unsigned char pad3f08[0x4b0];
    long field_43b8;                // +43b8
    unsigned char pad43c0[0x4b0];
    long field_4870;                // +4870
    unsigned char pad4878[0x4b0];
    long field_4d28;                // +4d28
    unsigned char pad4d30[0x4b0];
    long field_51e0;                // +51e0
    unsigned char pad51e8[0x4b0];
    long field_5698;                // +5698
    unsigned char pad56a0[0x4b0];
    long field_5b50;                // +5b50
    unsigned char pad5b58[0x4b0];
    long field_6008;                // +6008
    unsigned char pad6010[0x4b0];
    long field_64c0;                // +64c0
    unsigned char pad64c8[0x4b0];
    long field_6978;                // +6978
    unsigned char pad6980[0x4b0];
    long field_6e30;                // +6e30
    unsigned char pad6e38[0x30];
    long field_6e68;                // +6e68
    unsigned char pad6e70[0x4a0];
    long field_7310;                // +7310
    unsigned char pad7318[0x30];
    long field_7348;                // +7348
    unsigned char pad7350[0x20];
    long field_7370;                // +7370
    unsigned char pad7378[0x20];
    long field_7398;                // +7398
};

struct Node300d3c_v2 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};
// Reached through the GOT slot at 0x7100c22f00.
extern Globalc22f00_300d3c gGlobalc22f00_300d3c;
// Reached through the GOT slot at 0x7100c21db0.
extern Node300d3c_v2* gGlobalc21db0_300d3c;

// 0x7100300d3c: handle addresses computed once, for each vtable store and release call (the original's pre-indexed stores)
int call_300d3c(Arg300d3c_0* p0) {
    callee_2fcc8c(p0);
    void* v1 = gGlobalc22f00_300d3c.field_28;
    long* h7398 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x7398);
    *h7398 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v2 = gGlobalc21db0_300d3c;
    long m4;
    if (v2 != 0) {
        void* v3 = v2->field_2af8;
        m4 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v3) + 0x10);
    } else {
        m4 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h7398), m4);
    long* h7370 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x7370);
    *h7370 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v6 = gGlobalc21db0_300d3c;
    long m8;
    if (v6 != 0) {
        void* v7 = v6->field_2af8;
        m8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v7) + 0x10);
    } else {
        m8 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h7370), m8);
    long* h7348 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x7348);
    *h7348 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v10 = gGlobalc21db0_300d3c;
    long m12;
    if (v10 != 0) {
        void* v11 = v10->field_2af8;
        m12 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v11) + 0x10);
    } else {
        m12 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h7348), m12);
    long* h7310 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x7310);
    *h7310 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v14 = gGlobalc21db0_300d3c;
    long m16;
    if (v14 != 0) {
        void* v15 = v14->field_2af8;
        m16 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v15) + 0x10);
    } else {
        m16 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h7310), m16);
    long* h6e68 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x6e68);
    *h6e68 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v18 = gGlobalc21db0_300d3c;
    long m20;
    if (v18 != 0) {
        void* v19 = v18->field_2af8;
        m20 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v19) + 0x10);
    } else {
        m20 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h6e68), m20);
    long* h6e30 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x6e30);
    *h6e30 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v22 = gGlobalc21db0_300d3c;
    long m24;
    if (v22 != 0) {
        void* v23 = v22->field_2af8;
        m24 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v23) + 0x10);
    } else {
        m24 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h6e30), m24);
    long* h6978 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x6978);
    *h6978 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v26 = gGlobalc21db0_300d3c;
    long m28;
    if (v26 != 0) {
        void* v27 = v26->field_2af8;
        m28 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v27) + 0x10);
    } else {
        m28 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h6978), m28);
    long* h64c0 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x64c0);
    *h64c0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v30 = gGlobalc21db0_300d3c;
    long m32;
    if (v30 != 0) {
        void* v31 = v30->field_2af8;
        m32 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v31) + 0x10);
    } else {
        m32 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h64c0), m32);
    long* h6008 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x6008);
    *h6008 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v34 = gGlobalc21db0_300d3c;
    long m36;
    if (v34 != 0) {
        void* v35 = v34->field_2af8;
        m36 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v35) + 0x10);
    } else {
        m36 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h6008), m36);
    long* h5b50 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x5b50);
    *h5b50 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v38 = gGlobalc21db0_300d3c;
    long m40;
    if (v38 != 0) {
        void* v39 = v38->field_2af8;
        m40 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v39) + 0x10);
    } else {
        m40 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h5b50), m40);
    long* h5698 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x5698);
    *h5698 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v42 = gGlobalc21db0_300d3c;
    long m44;
    if (v42 != 0) {
        void* v43 = v42->field_2af8;
        m44 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v43) + 0x10);
    } else {
        m44 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h5698), m44);
    long* h51e0 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x51e0);
    *h51e0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v46 = gGlobalc21db0_300d3c;
    long m48;
    if (v46 != 0) {
        void* v47 = v46->field_2af8;
        m48 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v47) + 0x10);
    } else {
        m48 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h51e0), m48);
    long* h4d28 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x4d28);
    *h4d28 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v50 = gGlobalc21db0_300d3c;
    long m52;
    if (v50 != 0) {
        void* v51 = v50->field_2af8;
        m52 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v51) + 0x10);
    } else {
        m52 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h4d28), m52);
    long* h4870 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x4870);
    *h4870 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v54 = gGlobalc21db0_300d3c;
    long m56;
    if (v54 != 0) {
        void* v55 = v54->field_2af8;
        m56 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v55) + 0x10);
    } else {
        m56 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h4870), m56);
    long* h43b8 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x43b8);
    *h43b8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v58 = gGlobalc21db0_300d3c;
    long m60;
    if (v58 != 0) {
        void* v59 = v58->field_2af8;
        m60 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v59) + 0x10);
    } else {
        m60 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h43b8), m60);
    long* h3f00 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x3f00);
    *h3f00 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v62 = gGlobalc21db0_300d3c;
    long m64;
    if (v62 != 0) {
        void* v63 = v62->field_2af8;
        m64 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v63) + 0x10);
    } else {
        m64 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h3f00), m64);
    long* h3a48 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x3a48);
    *h3a48 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v66 = gGlobalc21db0_300d3c;
    long m68;
    if (v66 != 0) {
        void* v67 = v66->field_2af8;
        m68 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v67) + 0x10);
    } else {
        m68 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h3a48), m68);
    long* h35a0 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x35a0);
    *h35a0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v70 = gGlobalc21db0_300d3c;
    long m72;
    if (v70 != 0) {
        void* v71 = v70->field_2af8;
        m72 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v71) + 0x10);
    } else {
        m72 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h35a0), m72);
    long* h3570 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x3570);
    *h3570 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v74 = gGlobalc21db0_300d3c;
    long m76;
    if (v74 != 0) {
        void* v75 = v74->field_2af8;
        m76 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v75) + 0x10);
    } else {
        m76 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h3570), m76);
    long* h3540 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x3540);
    *h3540 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v78 = gGlobalc21db0_300d3c;
    long m80;
    if (v78 != 0) {
        void* v79 = v78->field_2af8;
        m80 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v79) + 0x10);
    } else {
        m80 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h3540), m80);
    long* h3510 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x3510);
    *h3510 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v82 = gGlobalc21db0_300d3c;
    long m84;
    if (v82 != 0) {
        void* v83 = v82->field_2af8;
        m84 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v83) + 0x10);
    } else {
        m84 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h3510), m84);
    long* h34e0 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x34e0);
    *h34e0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v86 = gGlobalc21db0_300d3c;
    long m88;
    if (v86 != 0) {
        void* v87 = v86->field_2af8;
        m88 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v87) + 0x10);
    } else {
        m88 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h34e0), m88);
    long* h34b0 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x34b0);
    *h34b0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v90 = gGlobalc21db0_300d3c;
    long m92;
    if (v90 != 0) {
        void* v91 = v90->field_2af8;
        m92 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v91) + 0x10);
    } else {
        m92 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h34b0), m92);
    long* h3480 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x3480);
    *h3480 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v94 = gGlobalc21db0_300d3c;
    long m96;
    if (v94 != 0) {
        void* v95 = v94->field_2af8;
        m96 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v95) + 0x10);
    } else {
        m96 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h3480), m96);
    long* h3450 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x3450);
    *h3450 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v98 = gGlobalc21db0_300d3c;
    long m100;
    if (v98 != 0) {
        void* v99 = v98->field_2af8;
        m100 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v99) + 0x10);
    } else {
        m100 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h3450), m100);
    long* h3420 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x3420);
    *h3420 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v102 = gGlobalc21db0_300d3c;
    long m104;
    if (v102 != 0) {
        void* v103 = v102->field_2af8;
        m104 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v103) + 0x10);
    } else {
        m104 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h3420), m104);
    long* h33f0 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x33f0);
    *h33f0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v106 = gGlobalc21db0_300d3c;
    long m108;
    if (v106 != 0) {
        void* v107 = v106->field_2af8;
        m108 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v107) + 0x10);
    } else {
        m108 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h33f0), m108);
    long* h33c0 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x33c0);
    *h33c0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v110 = gGlobalc21db0_300d3c;
    long m112;
    if (v110 != 0) {
        void* v111 = v110->field_2af8;
        m112 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v111) + 0x10);
    } else {
        m112 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v1)(reinterpret_cast<long>(h33c0), m112);
    long* h3390 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x3390);
    *h3390 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_300d3c) + 0x10);
    Node300d3c_v2* v114 = gGlobalc21db0_300d3c;
    long m116;
    if (v114 != 0) {
        void* v115 = v114->field_2af8;
        m116 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v115) + 0x10);
    } else {
        m116 = 0;
    }
    return reinterpret_cast<int (*)(long, long)>(v1)(reinterpret_cast<long>(h3390), m116);
}

void callee_30fcc0(long);        // 0x710030fcc0
void callee_310454(long);        // 0x7100310454
void callee_316764(long);        // 0x7100316764
void callee_3843f0(long);        // 0x71003843f0

struct Arg356154_0 {
    unsigned char pad0[0x5b20];
    long field_5b20;                // +5b20
    unsigned char pad5b28[0x10];
    long field_5b38;                // +5b38
    unsigned char pad5b40[0x10];
    long field_5b50;                // +5b50
    unsigned char pad5b58[0x10];
    long field_5b68;                // +5b68
    unsigned char pad5b70[0x10];
    long field_5b80;                // +5b80
    unsigned char pad5b88[0x10];
    long field_5b98;                // +5b98
    unsigned char pad5ba0[0x10];
    long field_5bb0;                // +5bb0
    unsigned char pad5bb8[0x10];
    long field_5bc8;                // +5bc8
    unsigned char pad5bd0[0x10];
    long field_5be0;                // +5be0
    unsigned char pad5be8[0x10];
    long field_5bf8;                // +5bf8
    unsigned char pad5c00[0x10];
    long field_5c10;                // +5c10
    unsigned char pad5c18[0x10];
    long field_5c28;                // +5c28
    unsigned char pad5c30[0x10];
    long field_5c40;                // +5c40
    unsigned char pad5c48[0x10];
    long field_5c58;                // +5c58
    unsigned char pad5c60[0x10];
    long field_5c70;                // +5c70
    unsigned char pad5c78[0x10];
    long field_5c88;                // +5c88
    unsigned char pad5c90[0x20];
    void* field_5cb0;               // +5cb0
    unsigned char pad5cb8[0x40];
    void* field_5cf8;               // +5cf8
    unsigned char pad5d00[0x2210];
    void* field_7f10;               // +7f10
    unsigned char pad7f18[0x40];
    void* field_7f58;               // +7f58
    unsigned char pad7f60[0x2210];
    void* field_a170;               // +a170
    unsigned char pada178[0x40];
    void* field_a1b8;               // +a1b8
    unsigned char pada1c0[0x2210];
    void* field_c3d0;               // +c3d0
    unsigned char padc3d8[0x40];
    void* field_c418;               // +c418
    unsigned char padc420[0x2210];
    void* field_e630;               // +e630
    unsigned char pade638[0x40];
    void* field_e678;               // +e678
    unsigned char pade680[0x2210];
    void* field_10890;               // +10890
    unsigned char pad10898[0x40];
    void* field_108d8;               // +108d8
    unsigned char pad108e0[0x2210];
    void* field_12af0;               // +12af0
    unsigned char pad12af8[0x40];
    void* field_12b38;               // +12b38
    unsigned char pad12b40[0x2210];
    void* field_14d50;               // +14d50
    unsigned char pad14d58[0x40];
    void* field_14d98;               // +14d98
};

struct Globalc22f00_356154 {
    unsigned char pad0[0x28];
    void* field_28;               // +28
};

struct Node356154_v16 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};
// Reached through the GOT slot at 0x7100c22f00.
extern Globalc22f00_356154 gGlobalc22f00_356154;
// Reached through the GOT slot at 0x7100c21db0.
extern Node356154_v16* gGlobalc21db0_356154;

// 0x7100356154: the frame destructor calls get back their this+offset argument (argfix), handle addresses computed once
int call_356154(Arg356154_0* p0) {
    long a0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x351f0);
    callee_316764(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x35208));
    callee_316764(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x351f0));
    callee_3843f0(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x17398));
    callee_310454(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x17218));
    callee_30fcc0(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x171e8));
    callee_30fcc0(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x16fa8));
    p0->field_14d50 = nullptr;
    p0->field_14d98 = nullptr;
    callee_316764(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x14d58));
    p0->field_12af0 = nullptr;
    p0->field_12b38 = nullptr;
    callee_316764(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x12af8));
    p0->field_10890 = nullptr;
    p0->field_108d8 = nullptr;
    callee_316764(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x10898));
    p0->field_e630 = nullptr;
    p0->field_e678 = nullptr;
    callee_316764(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xe638));
    p0->field_c3d0 = nullptr;
    p0->field_c418 = nullptr;
    callee_316764(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xc3d8));
    p0->field_a170 = nullptr;
    p0->field_a1b8 = nullptr;
    callee_316764(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xa178));
    p0->field_7f10 = nullptr;
    p0->field_7f58 = nullptr;
    callee_316764(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x7f18));
    p0->field_5cb0 = nullptr;
    p0->field_5cf8 = nullptr;
    callee_316764(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5cb8));
    void* v15 = gGlobalc22f00_356154.field_28;
    long* h5c88 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x5c88);
    *h5c88 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_356154) + 0x10);
    Node356154_v16* v16 = gGlobalc21db0_356154;
    long m18;
    if (v16 != 0) {
        void* v17 = v16->field_2af8;
        m18 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v17) + 0x10);
    } else {
        m18 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v15)(reinterpret_cast<long>(h5c88), m18);
    long* h5c70 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x5c70);
    *h5c70 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_356154) + 0x10);
    Node356154_v16* v20 = gGlobalc21db0_356154;
    long m22;
    if (v20 != 0) {
        void* v21 = v20->field_2af8;
        m22 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v21) + 0x10);
    } else {
        m22 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v15)(reinterpret_cast<long>(h5c70), m22);
    long* h5c58 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x5c58);
    *h5c58 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_356154) + 0x10);
    Node356154_v16* v24 = gGlobalc21db0_356154;
    long m26;
    if (v24 != 0) {
        void* v25 = v24->field_2af8;
        m26 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v25) + 0x10);
    } else {
        m26 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v15)(reinterpret_cast<long>(h5c58), m26);
    long* h5c40 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x5c40);
    *h5c40 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_356154) + 0x10);
    Node356154_v16* v28 = gGlobalc21db0_356154;
    long m30;
    if (v28 != 0) {
        void* v29 = v28->field_2af8;
        m30 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v29) + 0x10);
    } else {
        m30 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v15)(reinterpret_cast<long>(h5c40), m30);
    long* h5c28 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x5c28);
    *h5c28 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_356154) + 0x10);
    Node356154_v16* v32 = gGlobalc21db0_356154;
    long m34;
    if (v32 != 0) {
        void* v33 = v32->field_2af8;
        m34 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v33) + 0x10);
    } else {
        m34 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v15)(reinterpret_cast<long>(h5c28), m34);
    long* h5c10 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x5c10);
    *h5c10 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_356154) + 0x10);
    Node356154_v16* v36 = gGlobalc21db0_356154;
    long m38;
    if (v36 != 0) {
        void* v37 = v36->field_2af8;
        m38 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v37) + 0x10);
    } else {
        m38 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v15)(reinterpret_cast<long>(h5c10), m38);
    long* h5bf8 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x5bf8);
    *h5bf8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_356154) + 0x10);
    Node356154_v16* v40 = gGlobalc21db0_356154;
    long m42;
    if (v40 != 0) {
        void* v41 = v40->field_2af8;
        m42 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v41) + 0x10);
    } else {
        m42 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v15)(reinterpret_cast<long>(h5bf8), m42);
    long* h5be0 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x5be0);
    *h5be0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_356154) + 0x10);
    Node356154_v16* v44 = gGlobalc21db0_356154;
    long m46;
    if (v44 != 0) {
        void* v45 = v44->field_2af8;
        m46 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v45) + 0x10);
    } else {
        m46 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v15)(reinterpret_cast<long>(h5be0), m46);
    long* h5bc8 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x5bc8);
    *h5bc8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_356154) + 0x10);
    Node356154_v16* v48 = gGlobalc21db0_356154;
    long m50;
    if (v48 != 0) {
        void* v49 = v48->field_2af8;
        m50 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v49) + 0x10);
    } else {
        m50 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v15)(reinterpret_cast<long>(h5bc8), m50);
    long* h5bb0 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x5bb0);
    *h5bb0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_356154) + 0x10);
    Node356154_v16* v52 = gGlobalc21db0_356154;
    long m54;
    if (v52 != 0) {
        void* v53 = v52->field_2af8;
        m54 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v53) + 0x10);
    } else {
        m54 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v15)(reinterpret_cast<long>(h5bb0), m54);
    long* h5b98 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x5b98);
    *h5b98 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_356154) + 0x10);
    Node356154_v16* v56 = gGlobalc21db0_356154;
    long m58;
    if (v56 != 0) {
        void* v57 = v56->field_2af8;
        m58 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v57) + 0x10);
    } else {
        m58 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v15)(reinterpret_cast<long>(h5b98), m58);
    long* h5b80 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x5b80);
    *h5b80 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_356154) + 0x10);
    Node356154_v16* v60 = gGlobalc21db0_356154;
    long m62;
    if (v60 != 0) {
        void* v61 = v60->field_2af8;
        m62 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v61) + 0x10);
    } else {
        m62 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v15)(reinterpret_cast<long>(h5b80), m62);
    long* h5b68 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x5b68);
    *h5b68 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_356154) + 0x10);
    Node356154_v16* v64 = gGlobalc21db0_356154;
    long m66;
    if (v64 != 0) {
        void* v65 = v64->field_2af8;
        m66 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v65) + 0x10);
    } else {
        m66 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v15)(reinterpret_cast<long>(h5b68), m66);
    long* h5b50 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x5b50);
    *h5b50 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_356154) + 0x10);
    Node356154_v16* v68 = gGlobalc21db0_356154;
    long m70;
    if (v68 != 0) {
        void* v69 = v68->field_2af8;
        m70 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v69) + 0x10);
    } else {
        m70 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v15)(reinterpret_cast<long>(h5b50), m70);
    long* h5b38 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x5b38);
    *h5b38 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_356154) + 0x10);
    Node356154_v16* v72 = gGlobalc21db0_356154;
    long m74;
    if (v72 != 0) {
        void* v73 = v72->field_2af8;
        m74 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v73) + 0x10);
    } else {
        m74 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v15)(reinterpret_cast<long>(h5b38), m74);
    long* h5b20 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x5b20);
    *h5b20 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_356154) + 0x10);
    Node356154_v16* v76 = gGlobalc21db0_356154;
    long m78;
    if (v76 != 0) {
        void* v77 = v76->field_2af8;
        m78 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v77) + 0x10);
    } else {
        m78 = 0;
    }
    return reinterpret_cast<int (*)(long, long)>(v15)(reinterpret_cast<long>(h5b20), m78);
}

int callee2_1e26e0(void*, long);        // 0x71001e26e0
void callee_339084(long);        // 0x7100339084
void callee_3390a0(void*);        // 0x71003390a0
void callee_37cc88(long);        // 0x710037cc88
void callee_37f550(long);        // 0x710037f550

struct Arg33b670_0 {
    long field_0;                // +0
    unsigned char pad8[0x3a8];
    long field_3b0;                // +3b0
    unsigned char pad3b8[0x148];
    unsigned char field_500;       // +500
    unsigned char pad501[0x3];
    void* field_504 __attribute__((packed));               // +504
};
// Reached through the GOT slot at 0x7100c22a00.
extern void* gGlobalc22a00_33b670;
// Reached through the GOT slot at 0x7100c2aef8.
extern unsigned char gGlobalc2aef8_33b670[];
// Reached through the GOT slot at 0x7100c2aef0.
extern unsigned char gGlobalc2aef0_33b670[];

// 0x710033b670: a field at an offset its type would not get declared packed (fixalign)
int call_33b670(Arg33b670_0* p0) {
    callee_3390a0(p0);
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2aef8_33b670) + 0x10);
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x128));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x170));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1b8));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x200));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x248));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x290));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2d8));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x320));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x368));
    callee_339084(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3b0));
    p0->field_3b0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2aef0_33b670) + 0x10);
    callee_37f550(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3b8));
    callee_5d2744(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3f0));
    callee_37cc88(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3b8));
    void* v14 = gGlobalc22a00_33b670;
    int c15 = callee2_1e26e0(v14, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3f0));
    p0->field_500 = 0;
    p0->field_504 = nullptr;
    return c15;
}

void callee2_1e2360(void*, void*, int, void*);        // 0x71001e2360

class Node377cb0_v5 {
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

    unsigned char pad8[0x28];
    int field_30;                 // +30
    long field_34 __attribute__((packed));                // +34
    unsigned char pad3c[0x1c];
    unsigned char field_58;       // +58
};

struct Node377cb0_v4 {
    unsigned char pad0[0x18];
    Node377cb0_v5* field_18;      // +18
};

struct Arg377cb0_0 {
    Node377cb0_v4* field_0;      // +0
    void* field_8;               // +8
    void* field_10;               // +10
    void* field_18;               // +18
    void* field_20;               // +20
    void* field_28;               // +28
    long field_30;                // +30
    long field_38;                // +38
    int field_40;                 // +40
    unsigned char pad44[0x4];
    long field_48;                // +48
    long field_50;                // +50
    int field_58;                 // +58
};
// Reached through the GOT slot at 0x7100c22a00.
extern void* gGlobalc22a00_377cb0;
// Reached through the GOT slot at 0x7100c22f00.
extern unsigned char gGlobalc22f00_377cb0[];
extern unsigned char gLocal7dac8c_377cb0[] __attribute__((visibility("hidden")));    // 0x71007dac8c
extern unsigned char gLocal7d7ace_377cb0[] __attribute__((visibility("hidden")));    // 0x71007d7ace
extern unsigned char gLocal7d6341_377cb0[] __attribute__((visibility("hidden")));    // 0x71007d6341
extern unsigned char gLocal7d633e_377cb0[] __attribute__((visibility("hidden")));    // 0x71007d633e
extern unsigned char gLocal7d6329_377cb0[] __attribute__((visibility("hidden")));    // 0x71007d6329
extern unsigned char gLocal7d6322_377cb0[] __attribute__((visibility("hidden")));    // 0x71007d6322

// 0x7100377cb0: a field at an offset its type would not get declared packed (fixalign)
void* call_377cb0(Arg377cb0_0* p0) {
    p0->field_0 = nullptr;
    p0->field_20 = nullptr;
    p0->field_28 = nullptr;
    new (reinterpret_cast<unsigned char*>(p0) + 0x30) LayoutHandle;
    new (reinterpret_cast<unsigned char*>(p0) + 0x48) LayoutHandle;
    void* v0 = gGlobalc22a00_377cb0;
    callee2_1e2360(v0, p0, 0x4203, gLocal7dac8c_377cb0);
    void* v2 = gGlobalc22a00_377cb0;
    callee_1e26e8(v2);
    Node377cb0_v4* v4 = p0->field_0;
    Node377cb0_v5* v5 = v4->field_18;
    v5->field_30 = -0x3cc20000;
    v5->field_34 = static_cast<unsigned long>(static_cast<unsigned int>(0x41800000));
    unsigned char v6 = v5->field_58;
    v5->field_58 = v6 | 0x10;
    Node377cb0_v4* v7 = p0->field_0;
    void* c8 = callee_1e3770(v7, gLocal7d7ace_377cb0, 0);
    p0->field_8 = c8;
    Node377cb0_v4* v9 = p0->field_0;
    void* c10 = callee_1e3770(v9, gLocal7d6341_377cb0, 0);
    p0->field_10 = c10;
    Node377cb0_v4* v11 = p0->field_0;
    void* c12 = callee_1e3770(v11, gLocal7d633e_377cb0, 0);
    Node377cb0_v4* v13 = p0->field_0;
    p0->field_18 = c12;
    Node377cb0_v5* v14 = v13->field_18;
    void* c17 = v14->slot_12(gLocal7d6329_377cb0, 1);
    Node377cb0_v4* v18 = p0->field_0;
    p0->field_20 = c17;
    Node377cb0_v5* v19 = v18->field_18;
    void* c22 = v19->slot_12(gLocal7d6322_377cb0, 1);
    p0->field_28 = c22;
    return c22;
}

struct Arg577514_0 {
    long field_0;                // +0
    int field_8;                 // +8
    unsigned char padc[0x4];
    void* field_10;               // +10
    int field_18;                 // +18
    int field_1c;                 // +1c
    int field_20;                 // +20
    int field_24;                 // +24
};
// Reached through the GOT slot at 0x7100c2d620.
extern unsigned char gGlobalc2d620_577514[];

// 0x7100577514: stores in the original's order
void call_577514(Arg577514_0* p0) {
    p0->field_8 = 0;
    p0->field_10 = nullptr;
    p0->field_20 = -1;
    p0->field_18 = 0x7fffffff;
    p0->field_1c = 0x7fffffff;
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2d620_577514) + 0x10);
    p0->field_24 = 0;
}

struct Arg6b440_0 {
    long field_0;                // +0
    void* field_8;               // +8
    void* field_10;               // +10
    int field_18;                 // +18
    long field_1c __attribute__((packed));                // +1c
    long field_24 __attribute__((packed));                // +24
    long field_2c __attribute__((packed));                // +2c
};
// Reached through the GOT slot at 0x7100c22098.
extern unsigned char gGlobalc22098_6b440[];

// 0x710006b440: stores in the original's order
void call_6b440(Arg6b440_0* p0) {
    p0->field_10 = nullptr;
    p0->field_18 = -1;
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc22098_6b440) + 0x10);
    p0->field_2c = -1;
    p0->field_8 = nullptr;
    p0->field_24 = -1;
    p0->field_1c = -1;
}

void callee_2fcb90(void*);        // 0x71002fcb90
void callee_300d3c(long);        // 0x7100300d3c
void callee_3aab84(long);        // 0x71003aab84

struct Arg2fb9f0_0 {
    long field_0;                // +0
    unsigned char pad8[0xe078];
    long field_e080;                // +e080
};

struct Globalc22f00_2fb9f0 {
    unsigned char pad0[0x28];
    void* field_28;               // +28
};

struct Node2fb9f0_v7 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};
// Reached through the GOT slot at 0x7100c22f00.
extern Globalc22f00_2fb9f0 gGlobalc22f00_2fb9f0;
// Reached through the GOT slot at 0x7100c21db0.
extern Node2fb9f0_v7* gGlobalc21db0_2fb9f0;
// Reached through the GOT slot at 0x7100c2ac38.
extern unsigned char gGlobalc2ac38_2fb9f0[];

// 0x71002fb9f0: member calls given back the this+offset argument the generator dropped (argfix), handle addresses computed once
int call_2fb9f0(Arg2fb9f0_0* p0) {
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2ac38_2fb9f0) + 0x10);
    callee_2fcb90(p0);
    callee_3aab84(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x12708));
    callee_3aab84(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x103e8));
    callee_3aab84(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xe0c8));
    callee_316764(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xe0b0));
    callee_316764(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xe098));
    auto* he080 = &p0->field_e080;
    *he080 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_2fb9f0) + 0x10);
    void* v6 = gGlobalc22f00_2fb9f0.field_28;
    Node2fb9f0_v7* v7 = gGlobalc21db0_2fb9f0;
    long m9;
    if (v7 != 0) {
        void* v8 = v7->field_2af8;
        m9 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v8) + 0x10);
    } else {
        m9 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v6)(reinterpret_cast<long>(he080), m9);
    callee_300d3c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x260));
    callee_5d27b4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x150));
    callee_5d27b4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x40));
    return callee_316aa4(p0);
}

void callee4_1e2218(void*, long, int);        // 0x71001e2218
int callee2_1f8720(long);        // 0x71001f8720
void callee_1f8724(long);        // 0x71001f8724
void callee_2925c8(void*, long, int);        // 0x71002925c8

class Node349480_v2 {
public:
    virtual void slot_0();
    virtual void slot_1();

    unsigned char pad8[0x10];
    void* field_18;               // +18
};

class Node349480_v6 {
public:
    virtual void slot_0();
    virtual void slot_1();

    unsigned char pad8[0x10];
    void* field_18;               // +18
};

struct Arg349480_0 {
    long field_0;                // +0
    unsigned char pad8[0x2254];
    unsigned char field_225c;       // +225c
    unsigned char pad225d[0x3];
    Node349480_v2* field_2260;      // +2260
    Node349480_v6* field_2268;      // +2268
    unsigned char pad2270[0xa0];
    void* field_2310;               // +2310
    void* field_2318;               // +2318
    void* field_2320;               // +2320
    unsigned char pad2328[0x10];
    void* field_2338;               // +2338
    unsigned char pad2340[0x10];
    void* field_2350;               // +2350
    unsigned char pad2358[0x10];
    long field_2368;                // +2368
    unsigned char pad2370[0x10];
    long field_2380;                // +2380
    unsigned char pad2388[0x10];
    long field_2398;                // +2398
    unsigned char pad23a0[0x34];
    int field_23d4;                 // +23d4
};

struct Node349480_v15 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};

struct Globalc22f00_349480 {
    unsigned char pad0[0x28];
    void* field_28;               // +28
};
// Reached through the GOT slot at 0x7100c22a00.
extern void* gGlobalc22a00_349480;
// Reached through the GOT slot at 0x7100c21db0.
extern Node349480_v15* gGlobalc21db0_349480;
// Reached through the GOT slot at 0x7100c22f00.
extern Globalc22f00_349480 gGlobalc22f00_349480;
// Reached through the GOT slot at 0x7100c2af18.
extern unsigned char gGlobalc2af18_349480[];

// 0x7100349480: member calls given back the this+offset argument the generator dropped (argfix), handle addresses computed once
int call_349480(Arg349480_0* p0) {
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2af18_349480) + 0x10);
    unsigned char v0 = p0->field_225c;
    if (v0 != 0) {
        callee_1f8724(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2270));
        Node349480_v2* v2 = p0->field_2260;
        void* v3 = p0->field_2338;
        void* v4 = v2->field_18;
        callee_5da1b0(v3, v4);
        Node349480_v6* v6 = p0->field_2268;
        void* v7 = p0->field_2350;
        void* v8 = v6->field_18;
        callee_5da1b0(v7, v8);
        p0->field_2320 = nullptr;
        p0->field_2318 = nullptr;
        p0->field_2310 = nullptr;
        void* v10 = gGlobalc22a00_349480;
        int v11 = p0->field_23d4;
        callee_2925c8(v10, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x8), v11);
        void* v13 = gGlobalc22a00_349480;
        Node349480_v2* v14 = p0->field_2260;
        void* m28;
        if (v14 != 0) {
            Node349480_v15* v15 = gGlobalc21db0_349480;
            void* v16 = v15->field_2af8;
            long a17 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v16) + 0x10);
            callee4_1e2218(v13, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v13) + 0x7b8), 0x4204);
            Node349480_v2* v19 = p0->field_2260;
            callee_5d4408(v19, a17);
            Node349480_v2* v21 = p0->field_2260;
            v21->slot_1();
            Node349480_v2* v25 = p0->field_2260;
            callee3_5c3774(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v13) + 0xd8), v25);
            p0->field_2260 = nullptr;
            void* v27 = gGlobalc22a00_349480;
            m28 = v27;
        } else {
            m28 = v13;
        }
        Node349480_v6* v30 = p0->field_2268;
        if (v30 != 0) {
            Node349480_v15* v31 = gGlobalc21db0_349480;
            void* v32 = v31->field_2af8;
            long a33 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v32) + 0x10);
            callee4_1e2218(m28, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(m28) + 0x7b8), 0x4204);
            Node349480_v6* v35 = p0->field_2268;
            callee_5d4408(v35, a33);
            Node349480_v6* v37 = p0->field_2268;
            v37->slot_1();
            Node349480_v6* v41 = p0->field_2268;
            callee3_5c3774(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(m28) + 0xd8), v41);
            p0->field_2268 = nullptr;
        }
        p0->field_225c = 0;
    }
    auto* h2398 = &p0->field_2398;
    *h2398 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_349480) + 0x10);
    void* v45 = gGlobalc22f00_349480.field_28;
    Node349480_v15* v46 = gGlobalc21db0_349480;
    long m48;
    if (v46 != 0) {
        void* v47 = v46->field_2af8;
        m48 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v47) + 0x10);
    } else {
        m48 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v45)(reinterpret_cast<long>(h2398), m48);
    auto* h2380 = &p0->field_2380;
    *h2380 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_349480) + 0x10);
    Node349480_v15* v50 = gGlobalc21db0_349480;
    long m52;
    if (v50 != 0) {
        void* v51 = v50->field_2af8;
        m52 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v51) + 0x10);
    } else {
        m52 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v45)(reinterpret_cast<long>(h2380), m52);
    auto* h2368 = &p0->field_2368;
    *h2368 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_349480) + 0x10);
    Node349480_v15* v54 = gGlobalc21db0_349480;
    long m56;
    if (v54 != 0) {
        void* v55 = v54->field_2af8;
        m56 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v55) + 0x10);
    } else {
        m56 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v45)(reinterpret_cast<long>(h2368), m56);
    return callee2_1f8720(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2270));
}

void callee2_30fcc0(long);        // 0x710030fcc0
void callee_33a018(long);        // 0x710033a018
void callee_33a338(long);        // 0x710033a338
void callee_33b748(long);        // 0x710033b748
int callee_3c76d8(void*);        // 0x71003c76d8

struct Arg306044_0 {
    long field_0;                // +0
    unsigned char pad8[0x88];
    long field_90;                // +90
    unsigned char pad98[0x1c78];
    long field_1d10;                // +1d10
    unsigned char pad1d18[0x288];
    long field_1fa0;                // +1fa0
    unsigned char pad1fa8[0x1c78];
    long field_3c20;                // +3c20
    unsigned char pad3c28[0x288];
    long field_3eb0;                // +3eb0
    unsigned char pad3eb8[0x1c78];
    long field_5b30;                // +5b30
    unsigned char pad5b38[0x288];
    long field_5dc0;                // +5dc0
    unsigned char pad5dc8[0x1c78];
    long field_7a40;                // +7a40
    unsigned char pad7a48[0x288];
    long field_7cd0;                // +7cd0
    unsigned char pad7cd8[0x1c78];
    long field_9950;                // +9950
    unsigned char pad9958[0x288];
    long field_9be0;                // +9be0
    unsigned char pad9be8[0x1c78];
    long field_b860;                // +b860
    unsigned char padb868[0x288];
    long field_baf0;                // +baf0
    unsigned char padbaf8[0x1c78];
    long field_d770;                // +d770
    unsigned char padd778[0x380];
    long field_daf8;                // +daf8
    unsigned char paddb00[0x130];
    long field_dc30;                // +dc30
};

struct Globalc22f00_306044 {
    unsigned char pad0[0x28];
    void* field_28;               // +28
};

struct Node306044_v4 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};
// Reached through the GOT slot at 0x7100c22f00.
extern Globalc22f00_306044 gGlobalc22f00_306044;
// Reached through the GOT slot at 0x7100c21db0.
extern Node306044_v4* gGlobalc21db0_306044;
// Reached through the GOT slot at 0x7100c2acc8.
extern unsigned char gGlobalc2acc8_306044[];
// Reached through the GOT slot at 0x7100c2acd8.
extern unsigned char gGlobalc2acd8_306044[];
// Reached through the GOT slot at 0x7100c2acd0.
extern unsigned char gGlobalc2acd0_306044[];

// 0x7100306044: the sub-object at +90 through one pointer: its vtable store (pre-indexed), its handle at +1c80 and its base destructor call; member calls given back their argument (argfix)
int call_306044(Arg306044_0* p0) {
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2acc8_306044) + 0x10);
    auto* hdc30 = &p0->field_dc30;
    *hdc30 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2acd8_306044) + 0x10);
    callee_33a338(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xe140));
    callee_33b748(reinterpret_cast<long>(hdc30));
    callee_5d27b4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xdb10));
    auto* hdaf8 = &p0->field_daf8;
    *hdaf8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_306044) + 0x10);
    void* v3 = gGlobalc22f00_306044.field_28;
    Node306044_v4* v4 = gGlobalc21db0_306044;
    long m6;
    if (v4 != 0) {
        void* v5 = v4->field_2af8;
        m6 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v5) + 0x10);
    } else {
        m6 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v3)(reinterpret_cast<long>(hdaf8), m6);
    auto* hbaf0 = &p0->field_baf0;
    *hbaf0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2acd0_306044) + 0x10);
    callee2_30fcc0(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd7a8));
    auto* hd770 = &p0->field_d770;
    *hd770 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_306044) + 0x10);
    Node306044_v4* v9 = gGlobalc21db0_306044;
    long m11;
    if (v9 != 0) {
        void* v10 = v9->field_2af8;
        m11 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v10) + 0x10);
    } else {
        m11 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v3)(reinterpret_cast<long>(hd770), m11);
    callee_5d27b4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd5b0));
    callee_33a018(reinterpret_cast<long>(hbaf0));
    auto* h9be0 = &p0->field_9be0;
    *h9be0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2acd0_306044) + 0x10);
    callee2_30fcc0(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xb898));
    auto* hb860 = &p0->field_b860;
    *hb860 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_306044) + 0x10);
    Node306044_v4* v16 = gGlobalc21db0_306044;
    long m18;
    if (v16 != 0) {
        void* v17 = v16->field_2af8;
        m18 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v17) + 0x10);
    } else {
        m18 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v3)(reinterpret_cast<long>(hb860), m18);
    callee_5d27b4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xb6a0));
    callee_33a018(reinterpret_cast<long>(h9be0));
    long a22 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x7cd0);
    auto* h7cd0 = &p0->field_7cd0;
    *h7cd0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2acd0_306044) + 0x10);
    callee2_30fcc0(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x9988));
    auto* h9950 = &p0->field_9950;
    *h9950 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_306044) + 0x10);
    Node306044_v4* v24 = gGlobalc21db0_306044;
    long m26;
    if (v24 != 0) {
        void* v25 = v24->field_2af8;
        m26 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v25) + 0x10);
    } else {
        m26 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v3)(reinterpret_cast<long>(h9950), m26);
    callee_5d27b4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x9790));
    callee_33a018(reinterpret_cast<long>(h7cd0));
    long a30 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5dc0);
    auto* h5dc0 = &p0->field_5dc0;
    *h5dc0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2acd0_306044) + 0x10);
    callee2_30fcc0(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x7a78));
    auto* h7a40 = &p0->field_7a40;
    *h7a40 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_306044) + 0x10);
    Node306044_v4* v32 = gGlobalc21db0_306044;
    long m34;
    if (v32 != 0) {
        void* v33 = v32->field_2af8;
        m34 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v33) + 0x10);
    } else {
        m34 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v3)(reinterpret_cast<long>(h7a40), m34);
    callee_5d27b4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x7880));
    callee_33a018(reinterpret_cast<long>(h5dc0));
    long a38 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3eb0);
    auto* h3eb0 = &p0->field_3eb0;
    *h3eb0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2acd0_306044) + 0x10);
    callee2_30fcc0(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5b68));
    auto* h5b30 = &p0->field_5b30;
    *h5b30 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_306044) + 0x10);
    Node306044_v4* v40 = gGlobalc21db0_306044;
    long m42;
    if (v40 != 0) {
        void* v41 = v40->field_2af8;
        m42 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v41) + 0x10);
    } else {
        m42 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v3)(reinterpret_cast<long>(h5b30), m42);
    callee_5d27b4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5970));
    callee_33a018(reinterpret_cast<long>(h3eb0));
    long a46 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1fa0);
    auto* h1fa0 = &p0->field_1fa0;
    *h1fa0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2acd0_306044) + 0x10);
    callee2_30fcc0(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3c58));
    auto* h3c20 = &p0->field_3c20;
    *h3c20 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_306044) + 0x10);
    Node306044_v4* v48 = gGlobalc21db0_306044;
    long m50;
    if (v48 != 0) {
        void* v49 = v48->field_2af8;
        m50 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v49) + 0x10);
    } else {
        m50 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v3)(reinterpret_cast<long>(h3c20), m50);
    callee_5d27b4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3a60));
    callee_33a018(reinterpret_cast<long>(h1fa0));
    auto* h90 = &p0->field_90;
    *h90 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2acd0_306044) + 0x10);
    callee2_30fcc0(reinterpret_cast<long>(h90) + static_cast<unsigned long>(static_cast<unsigned int>(0x1cb8)));
    long* h1d10 = reinterpret_cast<long*>(reinterpret_cast<long>(h90) + static_cast<unsigned long>(static_cast<unsigned int>(0x1c80)));
    *h1d10 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_306044) + 0x10);
    Node306044_v4* v55 = gGlobalc21db0_306044;
    long m57;
    if (v55 != 0) {
        void* v56 = v55->field_2af8;
        m57 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v56) + 0x10);
    } else {
        m57 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v3)(reinterpret_cast<long>(h1d10), m57);
    callee_5d27b4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1b50));
    callee_33a018(reinterpret_cast<long>(h90));
    return callee_3c76d8(p0);
}

void callee_5e3e40(void*);        // 0x71005e3e40
void* callee_5e3e84(void*);        // 0x71005e3e84
int callee_5e3ec8(void*);        // 0x71005e3ec8
int callee_5e3ed0(void*);        // 0x71005e3ed0
int callee_5e3ed8(void*);        // 0x71005e3ed8
void callee_5e3efc(void*, long);        // 0x71005e3efc
int callee_5e3f04(void*, long);        // 0x71005e3f04
void callee_5e3f0c(void*, int);        // 0x71005e3f0c
void callee_5e3f14(void*, int);        // 0x71005e3f14

struct Arg5df2e8_0 {
    long field_0;                // +0
    unsigned char pad8[0x38];
    float field_40;               // +40
    float field_44;               // +44
    int field_48;                 // +48
};
extern void* gLocala9abf0_5df2e8[] __attribute__((visibility("hidden")));    // 0x7100a9abf0
// Reached through the GOT slot at 0x7100c2dd40.
extern unsigned char gGlobalc2dd40_5df2e8[];

// 0x71005df2e8: the float parameters declared before the int one: the entry copies arguments to callee-saved registers in parameter order
int call_5df2e8(Arg5df2e8_0* p0, void* p1, void* p2, float f0, float f1, int p3) {
    callee_5e3e40(p0);
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2dd40_5df2e8) + 0x10);
    p0->field_40 = f0 + f0;
    p0->field_44 = f1 + f1;
    p0->field_48 = p3;
    callee_5e3f0c(p0, (p3 << 2) + 0x14);
    int v2 = p0->field_48;
    callee_5e3f14(p0, (v2 * 0xc) + 0x12);
    void* c4 = callee_5e3e84(p0);
    int c5 = callee_5e3ed0(p0);
    callee_5e3efc(p0, static_cast<long>(static_cast<int>(c5)) * reinterpret_cast<long>(c4));
    int c7 = callee_5e3ec8(p0);
    long m9;
    if (static_cast<unsigned int>(c7) <= 2) {
        void* v8 = gLocala9abf0_5df2e8[static_cast<long>(static_cast<int>(c7))];
        m9 = reinterpret_cast<long>(v8);
    } else {
        m9 = 1;
    }
    int c10 = callee_5e3ed8(p0);
    return callee_5e3f04(p0, static_cast<long>(static_cast<int>(c10)) * m9);
}

int callee_2d25e8(long);        // 0x71002d25e8

struct Arg2d2498_0 {
    long field_0;                // +0
    unsigned char pad8[0x20];
    int field_28;                 // +28
    unsigned char pad2c[0x4d18];
    int field_4d44;                 // +4d44
    unsigned char pad4d48[0xccc8];
    int field_11a10;                 // +11a10
    unsigned char pad11a14[0x4];
    int field_11a18;                 // +11a18
};

struct Elem2d2498_r19 {
    unsigned char pad0[0x48];
};
// Reached through the GOT slot at 0x7100c2aaa8.
extern unsigned char gGlobalc2aaa8_2d2498[];

// 0x71002d2498: the vtable store before the field at +28, as in the original
int call_2d2498(Arg2d2498_0* p0) {
    callee_3c7188(p0);
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2aaa8_2d2498) + 0x10);
    p0->field_28 = 0;
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x30));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x78));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xc0));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x108));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x150));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x198));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1e0));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x228));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x270));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2b8));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x300));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x348));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x390));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3d8));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x420));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x468));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4b0));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4f8));
    new (reinterpret_cast<unsigned char*>(p0) + 0x540) LayoutSprite[0x100];
    p0->field_4d44 = 0;
    callee_2d25e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4d50));
    callee_2d25e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x6f70));
    callee_2d25e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x9190));
    callee_2d25e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xb3b0));
    callee_2d25e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd5d0));
    int c27 = callee_2d25e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xf7f0));
    p0->field_11a10 = 0;
    p0->field_11a18 = 0;
    return c27;
}


struct Node3182bc_v1 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};

struct Globalc22f00_3182bc {
    unsigned char pad0[0x28];
    void* field_28;               // +28
};
// Reached through the GOT slot at 0x7100c22f00.
extern Globalc22f00_3182bc gGlobalc22f00_3182bc;
// Reached through the GOT slot at 0x7100c21db0.
extern Node3182bc_v1* gGlobalc21db0_3182bc;
// Reached through the GOT slot at 0x7100c2adc8.
extern unsigned char gGlobalc2adc8_3182bc[];

struct Arg3182bc_0 {
    long field_0;                // +0
};

// 0x71003182bc: written by hand in generated style (gen.py fails on its pre-indexed store): five handle pairs, both addresses of a pair computed before its first vtable store
int call_3182bc(Arg3182bc_0* p0) {
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2adc8_3182bc) + 0x10);
    void* v0 = gGlobalc22f00_3182bc.field_28;
    long* h221e0 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x221e0);
    long* h221f8 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x221f8);
    *h221f8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3182bc) + 0x10);
    Node3182bc_v1* v1 = gGlobalc21db0_3182bc;
    long m3;
    if (v1 != 0) {
        void* v2 = v1->field_2af8;
        m3 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v2) + 0x10);
    } else {
        m3 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h221f8), m3);
    *h221e0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3182bc) + 0x10);
    Node3182bc_v1* v4 = gGlobalc21db0_3182bc;
    long m6;
    if (v4 != 0) {
        void* v5 = v4->field_2af8;
        m6 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v5) + 0x10);
    } else {
        m6 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h221e0), m6);
    long* h19980 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x19980);
    long* h19998 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x19998);
    *h19998 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3182bc) + 0x10);
    Node3182bc_v1* v7 = gGlobalc21db0_3182bc;
    long m9;
    if (v7 != 0) {
        void* v8 = v7->field_2af8;
        m9 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v8) + 0x10);
    } else {
        m9 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h19998), m9);
    *h19980 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3182bc) + 0x10);
    Node3182bc_v1* v10 = gGlobalc21db0_3182bc;
    long m12;
    if (v10 != 0) {
        void* v11 = v10->field_2af8;
        m12 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v11) + 0x10);
    } else {
        m12 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h19980), m12);
    long* h11120 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x11120);
    long* h11138 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x11138);
    *h11138 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3182bc) + 0x10);
    Node3182bc_v1* v13 = gGlobalc21db0_3182bc;
    long m15;
    if (v13 != 0) {
        void* v14 = v13->field_2af8;
        m15 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v14) + 0x10);
    } else {
        m15 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h11138), m15);
    *h11120 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3182bc) + 0x10);
    Node3182bc_v1* v16 = gGlobalc21db0_3182bc;
    long m18;
    if (v16 != 0) {
        void* v17 = v16->field_2af8;
        m18 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v17) + 0x10);
    } else {
        m18 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h11120), m18);
    long* h88c0 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x88c0);
    long* h88d8 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x88d8);
    *h88d8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3182bc) + 0x10);
    Node3182bc_v1* v19 = gGlobalc21db0_3182bc;
    long m21;
    if (v19 != 0) {
        void* v20 = v19->field_2af8;
        m21 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v20) + 0x10);
    } else {
        m21 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h88d8), m21);
    *h88c0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3182bc) + 0x10);
    Node3182bc_v1* v22 = gGlobalc21db0_3182bc;
    long m24;
    if (v22 != 0) {
        void* v23 = v22->field_2af8;
        m24 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v23) + 0x10);
    } else {
        m24 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h88c0), m24);
    long* h60 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x60);
    long* h78 = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x78);
    *h78 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3182bc) + 0x10);
    Node3182bc_v1* v25 = gGlobalc21db0_3182bc;
    long m27;
    if (v25 != 0) {
        void* v26 = v25->field_2af8;
        m27 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v26) + 0x10);
    } else {
        m27 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h78), m27);
    *h60 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_3182bc) + 0x10);
    Node3182bc_v1* v28 = gGlobalc21db0_3182bc;
    long m30;
    if (v28 != 0) {
        void* v29 = v28->field_2af8;
        m30 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v29) + 0x10);
    } else {
        m30 = 0;
    }
    reinterpret_cast<void (*)(long, long)>(v0)(reinterpret_cast<long>(h60), m30);
    return callee_316aa4(p0);
}

int callee_46440(long);        // 0x7100046440

struct Arg354_0 {
    long field_0;                // +0
    int field_8;                 // +8
    int field_c;                 // +c
    int field_10;                 // +10
    unsigned char pad14[0x4];
    void* field_18;               // +18
    unsigned char pad20[0x8];
    void* field_28;               // +28
    void* field_30;               // +30
    int field_38;                 // +38
};
// Reached through the GOT slot at 0x7100c21658.
extern unsigned char gGlobalc21658_354[];
// Reached through the GOT slot at 0x7100c21668.
extern unsigned char gGlobalc21668_354[];

// 0x7100000354: stores in the original's order (ordtry)
int call_354(Arg354_0* p0, int p1) {
    p0->field_8 = p1;
    p0->field_c = -1;
    p0->field_10 = 0;
    p0->field_18 = nullptr;
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc21658_354) + 0x10);
    int c0 = callee_46440(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x20));
    p0->field_38 = 0;
    p0->field_28 = nullptr;
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc21668_354) + 0x10);
    p0->field_30 = nullptr;
    return c0;
}

int callee_5f37e8(long);        // 0x71005f37e8

struct Arg5c238c_0 {
    long field_0;                // +0
    int field_8;                 // +8
    unsigned char padc[0x4];
    void* field_10;               // +10
    void* field_18;               // +18
    void* field_20;               // +20
    long field_28;                // +28
    unsigned char pad30[0x28];
    void* field_58;               // +58
    unsigned char field_60;       // +60
    unsigned char pad61[0x7];
    void* field_68;               // +68
};
// Reached through the GOT slot at 0x7100c2db50.
extern unsigned char gGlobalc2db50_5c238c[];
// Reached through the GOT slot at 0x7100c2db58.
extern unsigned char gGlobalc2db58_5c238c[];

// 0x71005c238c: stores in the original's order (ordtry)
int call_5c238c(Arg5c238c_0* p0, void* p1, void* p2, void* p3) {
    p0->field_8 = 0;
    p0->field_10 = p1;
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2db50_5c238c) + 0x10);
    p0->field_18 = p2;
    p0->field_20 = p3;
    int c0 = callee_5f37e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x28));
    p0->field_58 = nullptr;
    p0->field_60 = 0;
    p0->field_28 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2db58_5c238c) + 0x10);
    p0->field_68 = reinterpret_cast<void*>(p0);
    return c0;
}

int callee_5c2d24(long);        // 0x71005c2d24

struct Arg4b09c_0 {
    long field_0;                // +0
    void* field_8;               // +8
    void* field_10;               // +10
    int field_18;                 // +18
    unsigned char pad1c[0x4];
    void* field_20;               // +20
    long field_28;                // +28
    unsigned char pad30[0x58];
    void* field_88;               // +88
    int field_90;                 // +90
    unsigned char pad94[0x4];
    void* field_98;               // +98
    long field_a0;                // +a0
    unsigned char pada8[0x58];
    void* field_100;               // +100
};
// Reached through the GOT slot at 0x7100c21ed0.
extern unsigned char gGlobalc21ed0_4b09c[];
// Reached through the GOT slot at 0x7100c21ed8.
extern unsigned char gGlobalc21ed8_4b09c[];

// 0x710004b09c: stores in the original's order (ordtry)
int call_4b09c(Arg4b09c_0* p0) {
    p0->field_10 = nullptr;
    p0->field_18 = 0;
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc21ed0_4b09c) + 0x10);
    p0->field_20 = nullptr;
    p0->field_8 = nullptr;
    callee_5c2d24(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x28));
    p0->field_88 = nullptr;
    p0->field_28 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc21ed8_4b09c) + 0x10);
    p0->field_90 = 0;
    p0->field_98 = nullptr;
    int c1 = callee_5c2d24(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xa0));
    p0->field_a0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc21ed8_4b09c) + 0x10);
    p0->field_100 = nullptr;
    return c1;
}

int callee_59583c(void*);        // 0x710059583c

class Node2207dc_v0 {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();

    int field_8;                 // +8
};

struct Arg2207dc_0 {
    long field_0;                // +0
    unsigned char pad8[0x38];
    void* field_40;               // +40
    Node2207dc_v0* field_48;      // +48
};

class Node2207dc_v7 {
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
    virtual void slot_12(void*);
};

struct Node2207dc_v5 {
    unsigned char pad0[0x48];
    Node2207dc_v7* field_48;      // +48
    int field_50;                 // +50
};
// Reached through the GOT slot at 0x7100c23450.
extern Node2207dc_v5* gGlobalc23450_2207dc;
// Reached through the GOT slot at 0x7100c23448.
extern unsigned char gGlobalc23448_2207dc[];

// 0x71002207dc: stores in the original's order (ordtry)
int call_2207dc(Arg2207dc_0* p0) {
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc23448_2207dc) + 0x10);
    Node2207dc_v0* v0 = p0->field_48;
    p0->field_40 = nullptr;
    if (v0 != 0) {
        int v1 = v0->field_8;
        v0->field_8 = v1 - 1;
        if ((v1 - 1) == 0) {
            v0->slot_3();
        }
        p0->field_48 = nullptr;
    }
    Node2207dc_v5* v5 = gGlobalc23450_2207dc;
    if (v5 != 0) {
        int v6 = v5->field_50;
        v5->field_50 = v6 - 1;
        if ((v6 - 1) == 0) {
            Node2207dc_v7* v7 = v5->field_48;
            if (v7 != 0) {
                v7->slot_12(v5);
            }
        }
        gGlobalc23450_2207dc = nullptr;
    }
    return callee_59583c(p0);
}

int callee_4a1ae0(void*);        // 0x71004a1ae0

class Node49d50c_v0 {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();

    int field_8;                 // +8
};

class Node49d50c_v5 {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();

    int field_8;                 // +8
};

class Node49d50c_v10 {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();

    int field_8;                 // +8
};

class Node49d50c_v15 {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();

    int field_8;                 // +8
};

struct Arg49d50c_0 {
    long field_0;                // +0
    unsigned char pad8[0x18];
    long field_20;                // +20
    unsigned char pad28[0x15a8];
    Node49d50c_v0* field_15d0;      // +15d0
    void* field_15d8;               // +15d8
    Node49d50c_v5* field_15e0;      // +15e0
    void* field_15e8;               // +15e8
    Node49d50c_v10* field_15f0;     // +15f0
    void* field_15f8;               // +15f8
    Node49d50c_v15* field_1600;     // +1600
};
// Reached through the GOT slot at 0x7100c2cc30.
extern unsigned char gGlobalc2cc30_49d50c[];

// 0x710049d50c: stores in the original's order (ordtry)
int call_49d50c(Arg49d50c_0* p0) {
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2cc30_49d50c) + 0x10);
    Node49d50c_v0* v0 = p0->field_15d0;
    p0->field_20 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2cc30_49d50c) + 0xa8);
    if (v0 != 0) {
        int v1 = v0->field_8;
        v0->field_8 = v1 - 1;
        if ((v1 - 1) == 0) {
            v0->slot_3();
        }
        p0->field_15d0 = nullptr;
    }
    Node49d50c_v5* v5 = p0->field_15e0;
    if (v5 != 0) {
        int v6 = v5->field_8;
        v5->field_8 = v6 - 1;
        if ((v6 - 1) == 0) {
            v5->slot_3();
        }
        p0->field_15e0 = nullptr;
    }
    Node49d50c_v10* v10 = p0->field_15f0;
    if (v10 != 0) {
        int v11 = v10->field_8;
        v10->field_8 = v11 - 1;
        if ((v11 - 1) == 0) {
            v10->slot_3();
        }
        p0->field_15f0 = nullptr;
    }
    Node49d50c_v15* v15 = p0->field_1600;
    if (v15 != 0) {
        int v16 = v15->field_8;
        v15->field_8 = v16 - 1;
        if ((v16 - 1) == 0) {
            v15->slot_3();
        }
        p0->field_1600 = nullptr;
    }
    p0->field_15d8 = nullptr;
    p0->field_15e8 = nullptr;
    p0->field_15f8 = nullptr;
    return callee_4a1ae0(p0);
}

int callee_38f958(void*);        // 0x710038f958
void callee_391fbc(long);        // 0x7100391fbc

struct Arg392abc_0 {
    long field_0;                // +0
};
// Reached through the GOT slot at 0x7100c2b1e8.
extern unsigned char gGlobalc2b1e8_392abc[];

// 0x7100392abc: stores in the original's order (ordtry)
int call_392abc(Arg392abc_0* p0) {
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2b1e8_392abc) + 0x10);
    long a0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2268);
    callee_391fbc(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x25f8));
    callee_391fbc(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x25c8));
    callee_391fbc(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2598));
    callee_391fbc(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2568));
    callee_391fbc(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2538));
    callee_391fbc(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2508));
    callee_391fbc(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x24d8));
    callee_391fbc(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x24a8));
    callee_391fbc(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2478));
    callee_391fbc(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2448));
    callee_391fbc(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2418));
    callee_391fbc(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x23e8));
    callee_391fbc(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x23b8));
    callee_391fbc(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2388));
    callee_391fbc(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2358));
    callee_391fbc(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2328));
    callee_391fbc(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x22f8));
    callee_391fbc(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x22c8));
    callee_391fbc(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2298));
    callee_391fbc(a0);
    return callee_38f958(p0);
}

int callee_23e1bc(void*, void*);        // 0x710023e1bc

struct Arg2424b0_0 {
    long field_0;                // +0
    void* field_8;               // +8
    int field_10;                 // +10
    volatile unsigned short field_14;      // +14
    unsigned short field_16;      // +16
    volatile unsigned short field_18;      // +18
    unsigned char pad1a[0x6];
    void* field_20;               // +20
    void* field_28;               // +28
    unsigned char pad30[0x8];
    void* field_38;               // +38
    void* field_40;               // +40
    void* field_48;               // +48
    void* field_50;               // +50
    void* field_58;               // +58
    unsigned char pad60[0x40];
    int field_a0;                 // +a0
    unsigned char field_a4;       // +a4
};

class Node2424b0_v4 {
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
    virtual int slot_12(void*);
};

struct Node2424b0_v3 {
    unsigned char pad0[0x29db8];
    Node2424b0_v4* field_29db8;      // +29db8
};
// Reached through the GOT slot at 0x7100c21708.
extern Node2424b0_v3* gGlobalc21708_2424b0;
// Reached through the GOT slot at 0x7100c21758.
extern void* gGlobalc21758_2424b0;
// Reached through the GOT slot at 0x7100c2a4f0.
extern unsigned char gGlobalc2a4f0_2424b0[];

// 0x71002424b0: two volatile fields where the original keeps those stores in source order (voltry)
int call_2424b0(Arg2424b0_0* p0) {
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2a4f0_2424b0) + 0x10);
    Node2424b0_v3* v0 = gGlobalc21708_2424b0;
    int c1 = callee_23e1bc(v0, p0);
    void* v2 = gGlobalc21758_2424b0;
    p0->field_18 = 0xffff;
    p0->field_a0 = 0;
    p0->field_a4 = 0;
    p0->field_20 = nullptr;
    p0->field_28 = nullptr;
    p0->field_50 = nullptr;
    p0->field_58 = nullptr;
    p0->field_8 = v2;
    p0->field_14 = 0;
    p0->field_16 = 0;
    p0->field_40 = nullptr;
    p0->field_48 = nullptr;
    p0->field_38 = nullptr;
    p0->field_10 = -1;
    if (p0 == 0) {
        return c1;
    }
    Node2424b0_v3* v3 = gGlobalc21708_2424b0;
    Node2424b0_v4* v4 = v3->field_29db8;
    return v4->slot_12(p0);
}

void callee3_1e26e0(void*, long);        // 0x71001e26e0
void callee_33840c(long);        // 0x710033840c
void callee_338494(void*);        // 0x7100338494
void callee_33b0c4(long);        // 0x710033b0c4

struct Arg33a1c8_0 {
    long field_0;                // +0
    unsigned char pad8[0x2a8];
    int field_2b0;                 // +2b0
    unsigned char pad2b4[0x4];
    void* field_2b8;               // +2b8
    unsigned char pad2c0[0x138];
    float field_3f8;               // +3f8
    unsigned char pad3fc[0x4];
    int field_400;                 // +400
    unsigned char pad404[0x4];
    long field_408;                // +408
    unsigned char pad410[0x2230];
    int field_2640;                 // +2640
    unsigned char pad2644[0x4];
    unsigned char field_2648;       // +2648
    unsigned char pad2649[0x3];
    int field_264c;                 // +264c
    int field_2650;                 // +2650
    int field_2654;                 // +2654
    long field_2658;                // +2658
    unsigned char pad2660[0x2230];
    int field_4890;                 // +4890
    unsigned char pad4894[0x4];
    unsigned char field_4898;       // +4898
    unsigned char pad4899[0x3];
    int field_489c;                 // +489c
    int field_48a0;                 // +48a0
    int field_48a4;                 // +48a4
    unsigned char pad48a8[0x1c];
    unsigned char field_48c4;       // +48c4
};
// Reached through the GOT slot at 0x7100c22a00.
extern void* gGlobalc22a00_33a1c8;
// Reached through the GOT slot at 0x7100c21df0.
extern unsigned int gGlobalc21df0_33a1c8;
// Reached through the GOT slot at 0x7100c2aee0.
extern unsigned char gGlobalc2aee0_33a1c8[];
// Reached through the GOT slot at 0x7100c2aee8.
extern unsigned char gGlobalc2aee8_33a1c8[];

// 0x710033a1c8: generated source (genfix); outside the generator runs because the function is in the third session's scope
float call_33a1c8(Arg33a1c8_0* p0) {
    callee_338494(p0);
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2aee0_33a1c8) + 0x10);
    callee_5d2744(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2c0));
    callee_33840c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x408));
    p0->field_408 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2aee8_33a1c8) + 0x10);
    callee_33b0c4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x440));
    p0->field_2648 = 0xff;
    p0->field_264c = 0x438c0000;
    p0->field_2650 = 0x42000000;
    p0->field_2654 = 0x42000000;
    p0->field_2640 = 0;
    callee_33840c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2658));
    p0->field_2658 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2aee8_33a1c8) + 0x10);
    callee_33b0c4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2690));
    p0->field_4898 = 0xff;
    p0->field_489c = 0x438c0000;
    p0->field_48a0 = 0x42000000;
    p0->field_48a4 = 0x42000000;
    p0->field_4890 = 0;
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x48c8));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4910));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4958));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x49a0));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x49e8));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4a30));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4a78));
    callee_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4ac0));
    p0->field_2b8 = nullptr;
    p0->field_2b0 = 0;
    p0->field_48c4 = 0;
    void* v14 = gGlobalc22a00_33a1c8;
    callee3_1e26e0(v14, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2c0));
    unsigned int v16 = gGlobalc21df0_33a1c8;
    p0->field_400 = 0;
    p0->field_3f8 = static_cast<float>(static_cast<unsigned int>(v16));
    return static_cast<float>(static_cast<unsigned int>(v16));
}

void callee3_1e2360(void*, void*, int, void*);        // 0x71001e2360

class Node377acc_v5 {
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

    unsigned char pad8[0x28];
    int field_30;                 // +30
    long field_34 __attribute__((packed, aligned(4)));                // +34
    unsigned char pad3c[0xc];
    long field_48;                // +48
    unsigned char pad50[0x8];
    unsigned char field_58;       // +58
};

struct Node377acc_v4 {
    unsigned char pad0[0x18];
    Node377acc_v5* field_18;      // +18
};

struct Arg377acc_0 {
    Node377acc_v4* field_0;      // +0
    unsigned char pad8[0x8];
    void* field_10;               // +10
    void* field_18;               // +18
    void* field_20;               // +20
    void* field_28;               // +28
    void* field_30;               // +30
    long field_38;                // +38
    long field_40;                // +40
    int field_48;                 // +48
};

struct C30377acc {
    unsigned char pad0[0x58];
    unsigned char field_58;       // +58
};

struct C36377acc {
    unsigned char pad0[0x58];
    unsigned char field_58;       // +58
};

struct C42377acc {
    unsigned char pad0[0x58];
    unsigned char field_58;       // +58
};

struct C48377acc {
    unsigned char pad0[0x58];
    unsigned char field_58;       // +58
};
// Reached through the GOT slot at 0x7100c22a00.
extern void* gGlobalc22a00_377acc;
// Reached through the GOT slot at 0x7100c22f00.
extern unsigned char gGlobalc22f00_377acc[];
extern unsigned char gLocal7da472_377acc[] __attribute__((visibility("hidden")));    // 0x71007da472
extern unsigned char gLocal73fffb_377acc[] __attribute__((visibility("hidden")));    // 0x710073fffb
extern unsigned char gLocal74056c_377acc[] __attribute__((visibility("hidden")));    // 0x710074056c
extern unsigned char gLocal7d9d39_377acc[] __attribute__((visibility("hidden")));    // 0x71007d9d39
extern unsigned char gLocal7da486_377acc[] __attribute__((visibility("hidden")));    // 0x71007da486
extern unsigned char gLocal7da491_377acc[] __attribute__((visibility("hidden")));    // 0x71007da491
extern unsigned char gLocal7da4a8_377acc[] __attribute__((visibility("hidden")));    // 0x71007da4a8
extern unsigned char gLocal7da4c0_377acc[] __attribute__((visibility("hidden")));    // 0x71007da4c0
extern unsigned char gLocal7da4d9_377acc[] __attribute__((visibility("hidden")));    // 0x71007da4d9
extern unsigned char gLocal7da4ed_377acc[] __attribute__((visibility("hidden")));    // 0x71007da4ed

// 0x7100377acc: generated source (genfix); outside the generator runs because the function is in the third session's scope
C48377acc* call_377acc(Arg377acc_0* p0) {
    p0->field_0 = nullptr;
    p0->field_28 = nullptr;
    p0->field_30 = nullptr;
    new (reinterpret_cast<unsigned char*>(p0) + 0x38) LayoutHandle;
    void* v0 = gGlobalc22a00_377acc;
    callee3_1e2360(v0, p0, 0x41ff, gLocal7da472_377acc);
    void* v2 = gGlobalc22a00_377acc;
    callee_1e26e8(v2);
    Node377acc_v4* v4 = p0->field_0;
    Node377acc_v5* v5 = v4->field_18;
    v5->field_48 = 0x3f8000003f800000;
    unsigned char v6 = v5->field_58;
    v5->field_58 = v6 | 0x10;
    Node377acc_v4* v7 = p0->field_0;
    void* c8 = callee_1e3770(v7, gLocal73fffb_377acc, 0);
    p0->field_10 = c8;
    Node377acc_v4* v9 = p0->field_0;
    void* c10 = callee_1e3770(v9, gLocal74056c_377acc, 0);
    p0->field_18 = c10;
    Node377acc_v4* v11 = p0->field_0;
    void* c12 = callee_1e3770(v11, gLocal7d9d39_377acc, 1);
    Node377acc_v4* v13 = p0->field_0;
    p0->field_20 = c12;
    Node377acc_v5* v14 = v13->field_18;
    void* c17 = v14->slot_12(gLocal7da486_377acc, 1);
    Node377acc_v4* v18 = p0->field_0;
    p0->field_28 = c17;
    Node377acc_v5* v19 = v18->field_18;
    void* c22 = v19->slot_12(gLocal7da491_377acc, 1);
    Node377acc_v4* v23 = p0->field_0;
    p0->field_30 = c22;
    Node377acc_v5* v24 = v23->field_18;
    v24->field_30 = -0x3d4a0000;
    v24->field_34 = static_cast<unsigned long>(static_cast<unsigned int>(0x43e60000));
    unsigned char v25 = v24->field_58;
    v24->field_58 = v25 | 0x10;
    Node377acc_v4* v26 = p0->field_0;
    Node377acc_v5* v27 = v26->field_18;
    C30377acc* c30 = static_cast<C30377acc*>(v27->slot_12(gLocal7da4a8_377acc, 1));
    unsigned char v31 = c30->field_58;
    c30->field_58 = v31 & 0xfe;
    Node377acc_v4* v32 = p0->field_0;
    Node377acc_v5* v33 = v32->field_18;
    C36377acc* c36 = static_cast<C36377acc*>(v33->slot_12(gLocal7da4c0_377acc, 1));
    unsigned char v37 = c36->field_58;
    c36->field_58 = v37 & 0xfe;
    Node377acc_v4* v38 = p0->field_0;
    Node377acc_v5* v39 = v38->field_18;
    C42377acc* c42 = static_cast<C42377acc*>(v39->slot_12(gLocal7da4d9_377acc, 1));
    unsigned char v43 = c42->field_58;
    c42->field_58 = v43 & 0xfe;
    Node377acc_v4* v44 = p0->field_0;
    Node377acc_v5* v45 = v44->field_18;
    C48377acc* c48 = static_cast<C48377acc*>(v45->slot_12(gLocal7da4ed_377acc, 1));
    unsigned char v49 = c48->field_58;
    c48->field_58 = v49 & 0xfe;
    return c48;
}

extern "C" void* memset(void*, int, unsigned long);

int callee_2fede0(void*);        // 0x71002fede0
void callee_39e154(long, int);        // 0x710039e154
void callee_3a4034(long);        // 0x71003a4034
void callee_3a4c6c(long);        // 0x71003a4c6c

class Node2fe9c8_v44 {
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

struct Node2fe9c8_v43 {
    unsigned char pad0[0x18];
    Node2fe9c8_v44* field_18;     // +18
};

struct Arg2fe9c8_0 {
    long field_0;                // +0
    void* field_8;               // +8
    unsigned char pad10[0x30240];
    void* field_30250;               // +30250
    Node2fe9c8_v43* field_30258;     // +30258
    void* field_30260;               // +30260
    void* field_30268;               // +30268
    void* field_30270;               // +30270
    void* field_30278;               // +30278
    void* field_30280;               // +30280
    void* field_30288;               // +30288
    void* field_30290;               // +30290
    void* field_30298;               // +30298
    void* field_302a0;               // +302a0
    void* field_302a8;               // +302a8
    void* field_302b0;               // +302b0
    void* field_302b8;               // +302b8
    void* field_302c0;               // +302c0
    void* field_302c8;               // +302c8
    void* field_302d0;               // +302d0
    unsigned char pad302d8[0x50];
    int field_30328;                 // +30328
    int field_3032c;                 // +3032c
    int field_30330;                 // +30330
    unsigned char field_30334;       // +30334
    unsigned char pad30335[0x3];
    long field_30338;                // +30338
};
// Reached through the GOT slot at 0x7100c22a00.
extern void* gGlobalc22a00_2fe9c8;
// Reached through the GOT slot at 0x7100c2ac50.
extern unsigned char gGlobalc2ac50_2fe9c8[];
extern unsigned char gLocal7d9190_2fe9c8[] __attribute__((visibility("hidden")));    // 0x71007d9190
extern unsigned char gLocal7d91a1_2fe9c8[] __attribute__((visibility("hidden")));    // 0x71007d91a1
extern unsigned char gLocal7d91a7_2fe9c8[] __attribute__((visibility("hidden")));    // 0x71007d91a7
extern unsigned char gLocal7d91b7_2fe9c8[] __attribute__((visibility("hidden")));    // 0x71007d91b7
extern unsigned char gLocal7d91c6_2fe9c8[] __attribute__((visibility("hidden")));    // 0x71007d91c6
extern unsigned char gLocal7d91d6_2fe9c8[] __attribute__((visibility("hidden")));    // 0x71007d91d6
extern unsigned char gLocal7d91e6_2fe9c8[] __attribute__((visibility("hidden")));    // 0x71007d91e6
extern unsigned char gLocal7d91f6_2fe9c8[] __attribute__((visibility("hidden")));    // 0x71007d91f6
extern unsigned char gLocal7d9206_2fe9c8[] __attribute__((visibility("hidden")));    // 0x71007d9206
extern unsigned char gLocal7d9212_2fe9c8[] __attribute__((visibility("hidden")));    // 0x71007d9212
extern unsigned char gLocal7d921e_2fe9c8[] __attribute__((visibility("hidden")));    // 0x71007d921e
extern unsigned char gLocal7d9229_2fe9c8[] __attribute__((visibility("hidden")));    // 0x71007d9229
extern unsigned char gLocal7d9233_2fe9c8[] __attribute__((visibility("hidden")));    // 0x71007d9233
extern unsigned char gLocal7d9240_2fe9c8[] __attribute__((visibility("hidden")));    // 0x71007d9240

// 0x71002fe9c8: generated source (genfix); outside the generator runs because the function is in the third session's scope
int call_2fe9c8(Arg2fe9c8_0* p0, void* p1) {
    p0->field_8 = p1;
    memset(reinterpret_cast<void*>(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x18)), 0, 0x48);
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2ac50_2fe9c8) + 0x10);
    callee_39e154(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x60), 0);
    callee_39e154(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2380), 0);
    callee_39e154(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x46a0), 0);
    callee_39e154(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x69c0), 0);
    callee_3a4034(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x8ce0));
    callee_3a4034(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xc180));
    callee_3a4034(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xf620));
    callee_3a4034(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x12ac0));
    callee_3a4034(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x15f60));
    callee_3a4034(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x19400));
    callee_3a4034(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1c8a0));
    callee_3a4034(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1fd40));
    callee_3a4034(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x231e0));
    callee_3a4c6c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x26680));
    callee_3a4c6c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x277d0));
    callee_3a4c6c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x28920));
    callee_3a4c6c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x29a70));
    callee_3a4c6c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2abc0));
    callee_3a4c6c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2bd10));
    callee_3a4c6c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2ce60));
    callee_3a4c6c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2dfb0));
    callee_3a4c6c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2f100));
    p0->field_30260 = nullptr;
    p0->field_30250 = nullptr;
    p0->field_30258 = nullptr;
    p0->field_30328 = 4;
    p0->field_3032c = 0;
    p0->field_30330 = -1;
    p0->field_30334 = 0;
    p0->field_30338 = 0x200000000;
    void* v23 = gGlobalc22a00_2fe9c8;
    callee_1e2360(v23, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x30258), 0x41f3, gLocal7d9190_2fe9c8);
    Node2fe9c8_v43* v25 = p0->field_30258;
    void* c26 = callee_1e3770(v25, gLocal7d91a1_2fe9c8, 1);
    p0->field_30268 = c26;
    Node2fe9c8_v43* v27 = p0->field_30258;
    void* c28 = callee_1e3770(v27, gLocal7d91a7_2fe9c8, 0);
    p0->field_30270 = c28;
    Node2fe9c8_v43* v29 = p0->field_30258;
    void* c30 = callee_1e3770(v29, gLocal7d91b7_2fe9c8, 0);
    p0->field_30278 = c30;
    Node2fe9c8_v43* v31 = p0->field_30258;
    void* c32 = callee_1e3770(v31, gLocal7d91c6_2fe9c8, 0);
    p0->field_30280 = c32;
    Node2fe9c8_v43* v33 = p0->field_30258;
    void* c34 = callee_1e3770(v33, gLocal7d91d6_2fe9c8, 0);
    p0->field_30288 = c34;
    p0->field_30290 = nullptr;
    Node2fe9c8_v43* v35 = p0->field_30258;
    void* c36 = callee_1e3770(v35, gLocal7d91e6_2fe9c8, 0);
    p0->field_30298 = c36;
    Node2fe9c8_v43* v37 = p0->field_30258;
    void* c38 = callee_1e3770(v37, gLocal7d91f6_2fe9c8, 0);
    p0->field_302a0 = c38;
    Node2fe9c8_v43* v39 = p0->field_30258;
    void* c40 = callee_1e3770(v39, gLocal7d9206_2fe9c8, 0);
    p0->field_302a8 = c40;
    Node2fe9c8_v43* v41 = p0->field_30258;
    void* c42 = callee_1e3770(v41, gLocal7d9212_2fe9c8, 0);
    p0->field_302b0 = c42;
    Node2fe9c8_v43* v43 = p0->field_30258;
    Node2fe9c8_v44* v44 = v43->field_18;
    void* c47 = v44->slot_12(gLocal7d921e_2fe9c8, 1);
    p0->field_302b8 = c47;
    Node2fe9c8_v43* v48 = p0->field_30258;
    Node2fe9c8_v44* v49 = v48->field_18;
    void* c52 = v49->slot_12(gLocal7d9229_2fe9c8, 1);
    p0->field_302c0 = c52;
    Node2fe9c8_v43* v53 = p0->field_30258;
    Node2fe9c8_v44* v54 = v53->field_18;
    void* c57 = v54->slot_12(gLocal7d9233_2fe9c8, 1);
    p0->field_302c8 = c57;
    Node2fe9c8_v43* v58 = p0->field_30258;
    Node2fe9c8_v44* v59 = v58->field_18;
    void* c62 = v59->slot_12(gLocal7d9240_2fe9c8, 1);
    p0->field_302d0 = c62;
    memset(reinterpret_cast<void*>(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x302d8)), 0, 0x50);
    return callee_2fede0(p0);
}

void callee_46448(long);        // 0x7100046448
void callee_71748(long);        // 0x7100071748
int callee_58ce50(long);        // 0x710058ce50

class Node37420_v86 {
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
    virtual void slot_12(void*);
};

class Node37420_v80 {
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
    virtual void slot_12(void*);
};

class Node37420_v73 {
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
    virtual void slot_12(void*);
};

class Node37420_v66 {
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
    virtual void slot_12(void*);
};

class Node37420_v59 {
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
    virtual void slot_12(void*);
};

class Node37420_v52 {
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
    virtual void slot_12(void*);
};

class Node37420_v45 {
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
    virtual void slot_12(void*);
};

class Node37420_v38 {
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
    virtual void slot_12(void*);
};

class Node37420_v31 {
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
    virtual void slot_12(void*);
};

class Node37420_v24 {
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
    virtual void slot_12(void*);
};

struct Arg37420_0 {
    unsigned char pad0[0x18];
    long field_18;                // +18
    Node37420_v86* field_20;      // +20
    void* field_28;               // +28
    unsigned char pad30[0x818];
    void* field_848;               // +848
    unsigned char pad850[0x48];
    long field_898;                // +898
    Node37420_v80* field_8a0;      // +8a0
    void* field_8a8;               // +8a8
    unsigned char pad8b0[0x818];
    void* field_10c8;               // +10c8
    unsigned char pad10d0[0x48];
    long field_1118;                // +1118
    Node37420_v73* field_1120;      // +1120
    void* field_1128;               // +1128
    unsigned char pad1130[0x818];
    void* field_1948;               // +1948
    unsigned char pad1950[0x48];
    long field_1998;                // +1998
    Node37420_v66* field_19a0;      // +19a0
    void* field_19a8;               // +19a8
    unsigned char pad19b0[0x818];
    void* field_21c8;               // +21c8
    unsigned char pad21d0[0x48];
    long field_2218;                // +2218
    Node37420_v59* field_2220;      // +2220
    void* field_2228;               // +2228
    unsigned char pad2230[0x818];
    void* field_2a48;               // +2a48
    unsigned char pad2a50[0x48];
    long field_2a98;                // +2a98
    Node37420_v52* field_2aa0;      // +2aa0
    void* field_2aa8;               // +2aa8
    unsigned char pad2ab0[0x818];
    void* field_32c8;               // +32c8
    unsigned char pad32d0[0x48];
    long field_3318;                // +3318
    Node37420_v45* field_3320;      // +3320
    void* field_3328;               // +3328
    unsigned char pad3330[0x818];
    void* field_3b48;               // +3b48
    unsigned char pad3b50[0x48];
    long field_3b98;                // +3b98
    Node37420_v38* field_3ba0;      // +3ba0
    void* field_3ba8;               // +3ba8
    unsigned char pad3bb0[0x818];
    void* field_43c8;               // +43c8
    unsigned char pad43d0[0x48];
    long field_4418;                // +4418
    Node37420_v31* field_4420;      // +4420
    void* field_4428;               // +4428
    unsigned char pad4430[0x818];
    void* field_4c48;               // +4c48
    unsigned char pad4c50[0x48];
    long field_4c98;                // +4c98
    Node37420_v24* field_4ca0;      // +4ca0
    void* field_4ca8;               // +4ca8
    unsigned char pad4cb0[0x818];
    void* field_54c8;               // +54c8
};
// Reached through the GOT slot at 0x7100c21dc8.
extern unsigned char gGlobalc21dc8_37420[];

// 0x7100037420: stores in the original's order: the first member's vtable store before its pointer is read (onceptr)
int call_37420(Arg37420_0* p0) {
    callee_46448(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x6870));
    callee_46448(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x6830));
    callee_46448(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x67f0));
    callee_46448(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x67b0));
    callee_46448(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x6770));
    callee_46448(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x6730));
    callee_46448(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x66f0));
    callee_46448(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x66b0));
    callee_46448(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x6670));
    callee_46448(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x6630));
    callee_46448(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x65f0));
    callee_46448(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x65b0));
    callee_46448(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x6570));
    callee_46448(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x6530));
    callee_46448(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x64f0));
    callee_46448(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x64b0));
    callee_46448(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x6470));
    callee_46448(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x6430));
    callee_46448(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x63f0));
    callee_46448(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x63b0));
    long r20 = 0;
    do {
        callee_71748(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x6350) + r20);
        r20 = r20 - 0x28;
    } while (r20 != -0xe60);
    long a23 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4c98);
    p0->field_4c98 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc21dc8_37420) + 0x10);
    void* v22 = p0->field_4ca8;
    if (v22 != 0) {
        Node37420_v24* v24 = p0->field_4ca0;
        v24->slot_12(v22);
        p0->field_4ca8 = nullptr;
        p0->field_54c8 = nullptr;
    }
    callee_58ce50(a23);
    void* v29 = p0->field_4428;
    long a30 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4418);
    p0->field_4418 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc21dc8_37420) + 0x10);
    if (v29 != 0) {
        Node37420_v31* v31 = p0->field_4420;
        v31->slot_12(v29);
        p0->field_4428 = nullptr;
        p0->field_4c48 = nullptr;
    }
    callee_58ce50(a30);
    void* v36 = p0->field_3ba8;
    long a37 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3b98);
    p0->field_3b98 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc21dc8_37420) + 0x10);
    if (v36 != 0) {
        Node37420_v38* v38 = p0->field_3ba0;
        v38->slot_12(v36);
        p0->field_3ba8 = nullptr;
        p0->field_43c8 = nullptr;
    }
    callee_58ce50(a37);
    void* v43 = p0->field_3328;
    long a44 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3318);
    p0->field_3318 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc21dc8_37420) + 0x10);
    if (v43 != 0) {
        Node37420_v45* v45 = p0->field_3320;
        v45->slot_12(v43);
        p0->field_3328 = nullptr;
        p0->field_3b48 = nullptr;
    }
    callee_58ce50(a44);
    void* v50 = p0->field_2aa8;
    long a51 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2a98);
    p0->field_2a98 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc21dc8_37420) + 0x10);
    if (v50 != 0) {
        Node37420_v52* v52 = p0->field_2aa0;
        v52->slot_12(v50);
        p0->field_2aa8 = nullptr;
        p0->field_32c8 = nullptr;
    }
    callee_58ce50(a51);
    void* v57 = p0->field_2228;
    long a58 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2218);
    p0->field_2218 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc21dc8_37420) + 0x10);
    if (v57 != 0) {
        Node37420_v59* v59 = p0->field_2220;
        v59->slot_12(v57);
        p0->field_2228 = nullptr;
        p0->field_2a48 = nullptr;
    }
    callee_58ce50(a58);
    void* v64 = p0->field_19a8;
    long a65 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1998);
    p0->field_1998 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc21dc8_37420) + 0x10);
    if (v64 != 0) {
        Node37420_v66* v66 = p0->field_19a0;
        v66->slot_12(v64);
        p0->field_19a8 = nullptr;
        p0->field_21c8 = nullptr;
    }
    callee_58ce50(a65);
    void* v71 = p0->field_1128;
    long a72 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1118);
    p0->field_1118 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc21dc8_37420) + 0x10);
    if (v71 != 0) {
        Node37420_v73* v73 = p0->field_1120;
        v73->slot_12(v71);
        p0->field_1128 = nullptr;
        p0->field_1948 = nullptr;
    }
    callee_58ce50(a72);
    void* v78 = p0->field_8a8;
    long a79 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x898);
    p0->field_898 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc21dc8_37420) + 0x10);
    if (v78 != 0) {
        Node37420_v80* v80 = p0->field_8a0;
        v80->slot_12(v78);
        p0->field_8a8 = nullptr;
        p0->field_10c8 = nullptr;
    }
    callee_58ce50(a79);
    auto* h18 = &p0->field_18;
    *h18 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc21dc8_37420) + 0x10);
    void* v85 = p0->field_28;
    if (v85 != 0) {
        Node37420_v86* v86 = p0->field_20;
        v86->slot_12(v85);
        p0->field_28 = nullptr;
        p0->field_848 = nullptr;
    }
    return callee_58ce50(reinterpret_cast<long>(h18));
}

void callee_218abc(long);        // 0x7100218abc

struct Arg1f5118_0 {
    long field_0;                // +0
    void* field_8;               // +8
    void* field_10;               // +10
    unsigned char pad18[0x58d0];
    void* field_58e8;               // +58e8
    void* field_58f0;               // +58f0
    void* field_58f8;               // +58f8
    void* field_5900;               // +5900
    void* field_5908;               // +5908
    int field_5910;                 // +5910
    unsigned char field_5914;       // +5914
    unsigned char pad5915[0x3];
    int field_5918;                 // +5918
    unsigned char field_591c;       // +591c
    unsigned char pad591d[0x28b];
    unsigned char field_5ba8;       // +5ba8
    unsigned char pad5ba9[0x3];
    int field_5bac;                 // +5bac
    int field_5bb0;                 // +5bb0
    int field_5bb4;                 // +5bb4
    int field_5bb8;                 // +5bb8
    unsigned char field_5bbc;       // +5bbc
};

struct Elem1f5118_r1 {
    unsigned char pad0[0x48];
};
// Reached through the GOT slot at 0x7100c231d0.
extern unsigned char gGlobalc231d0_1f5118[];

// 0x71001f5118: a class (ctor2class --prefix) whose member constructor at +18 gets back the this+18 argument the generator dropped
class Class1f5118 {
public:
    Class1f5118();
    virtual void v00();

    void* f8;
    void* f10;
};

Class1f5118::Class1f5118()
    : f8(nullptr), f10(nullptr) {
    Arg1f5118_0* p0 = reinterpret_cast<Arg1f5118_0*>(this);
    callee_218abc(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x18));
    new (reinterpret_cast<unsigned char*>(p0) + 0x28) LayoutSprite[0xc8];
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3868));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x38f0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3978));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3a00));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3a88));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3b10));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3b98));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3c20));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3ca8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3d30));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3db8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3e40));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3ec8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3f50));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3fd8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4060));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x40e8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4170));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x41f8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4280));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4308));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4390));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4418));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x44a0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4528));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x45b0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4638));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x46c0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4748));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x47d0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4858));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x48e0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4968));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x49f0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4a78));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4b00));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4b88));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4c10));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4c98));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4d20));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4da8));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4df0));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4e38));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4e80));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4ec8));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4f10));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4f58));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4fa0));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4fe8));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5030));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5078));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x50c0));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5108));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5150));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5198));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x51e0));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5228));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5270));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x52b8));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5300));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5348));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5390));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x53d8));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5420));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5468));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x54b0));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x54f8));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5540));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5588));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x55d0));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5618));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5660));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x56a8));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x56f0));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5738));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5780));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x57c8));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5810));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5858));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x58a0));
    p0->field_5910 = 0;
    p0->field_5908 = nullptr;
    p0->field_5900 = nullptr;
    p0->field_58f8 = nullptr;
    p0->field_58f0 = nullptr;
    p0->field_58e8 = nullptr;
    p0->field_5914 = 1;
    p0->field_5918 = 0;
    p0->field_591c = 1;
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5920));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5968));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x59b0));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x59f8));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5a40));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5a88));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5ad0));
    callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5b18));
    int c92 = callee2_1ef52c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5b60));
    p0->field_5ba8 = 0;
    p0->field_5bac = 0;
    p0->field_5bb0 = 0;
    p0->field_5bb4 = 0x42000000;
    p0->field_5bb8 = 0x42000000;
    p0->field_5bbc = 1;
}


void callee4_1e2360(void*, void*, int, void*);        // 0x71001e2360
void callee4_1e2360(void*, long, int, void*);        // 0x71001e2360
void callee_1e41d8(void*, long, int);        // 0x71001e41d8
int callee_1e4570(void*, float);        // 0x71001e4570
void callee_1e709c(void*, void*, void*, int, int, int);        // 0x71001e709c
int callee_1e73c0(void*, long, void*, int, int, int, float, float);        // 0x71001e73c0
void callee_1f8700(long);        // 0x71001f8700
void callee_1f8820(long, void*, void*, int);        // 0x71001f8820
void* callee_217d64(int);        // 0x7100217d64
void callee2_5da17c(void*, void*);        // 0x71005da17c

class Node35b928_v39 {
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

struct Node35b928_v38 {
    unsigned char pad0[0x18];
    Node35b928_v39* field_18;     // +18
};

struct Node35b928_v25 {
    unsigned char pad0[0x48];
    float field_48;               // +48
    unsigned char pad4c[0xc];
    unsigned char field_58;       // +58
};

struct Node35b928_v24 {
    unsigned char pad0[0x18];
    Node35b928_v25* field_18;     // +18
};

struct Node35b928_v28 {
    unsigned char pad0[0x58];
    unsigned char field_58;       // +58
};

struct Node35b928_v27 {
    unsigned char pad0[0x18];
    Node35b928_v28* field_18;     // +18
};

struct Node35b928_v114 {
    unsigned char pad0[0x18];
    void* field_18;               // +18
};

struct Node35b928_v120 {
    unsigned char pad0[0x18];
    void* field_18;               // +18
};

struct Node35b928_v89 {
    unsigned char pad0[0x5b];
    unsigned char field_5b;       // +5b
};

struct Arg35b928_0 {
    Node35b928_v38* field_0;     // +0
    Node35b928_v24* field_8;     // +8
    Node35b928_v27* field_10;     // +10
    Node35b928_v114* field_18;    // +18
    Node35b928_v120* field_20;    // +20
    void* field_28;               // +28
    void* field_30;               // +30
    void* field_38;               // +38
    void* field_40;               // +40
    unsigned char pad48[0x880];
    Node35b928_v89* field_8c8;     // +8c8
    int field_8d0;                 // +8d0
    int field_8d4;                 // +8d4
    int field_8d8;                 // +8d8
};

struct Node35b928_v32 {
    unsigned char pad0[0x20b98];
    int field_20b98;                 // +20b98
};

struct C4735b928 {
    unsigned char pad0[0x50];
    float field_50;               // +50
};

struct C6435b928 {
    unsigned char pad0[0x50];
    float field_50;               // +50
};

struct C8135b928 {
    unsigned char pad0[0x50];
    float field_50;               // +50
};

struct C8535b928 {
    long field_0;                // +0
    unsigned char pad8[0x158];
    void* field_160;               // +160
    void* field_168;               // +168
    void* field_170;               // +170
};
// Reached through the GOT slot at 0x7100c22a00.
extern void* gGlobalc22a00_35b928;
// Reached through the GOT slot at 0x7100c22a30.
extern Node35b928_v32* gGlobalc22a30_35b928;
extern unsigned char gLocal7d6180_35b928[] __attribute__((visibility("hidden")));    // 0x71007d6180
extern unsigned char gLocal7d6191_35b928[] __attribute__((visibility("hidden")));    // 0x71007d6191
extern unsigned char gLocal7d61a1_35b928[] __attribute__((visibility("hidden")));    // 0x71007d61a1
extern unsigned char gLocal7d61b5_35b928[] __attribute__((visibility("hidden")));    // 0x71007d61b5
extern unsigned char gLocal7d61c2_35b928[] __attribute__((visibility("hidden")));    // 0x71007d61c2
extern unsigned char gLocal7d61d0_35b928[] __attribute__((visibility("hidden")));    // 0x71007d61d0
extern unsigned char gLocal7d61de_35b928[] __attribute__((visibility("hidden")));    // 0x71007d61de
extern unsigned char gLocal7d61ed_35b928[] __attribute__((visibility("hidden")));    // 0x71007d61ed
extern unsigned char gLocal7d61fa_35b928[] __attribute__((visibility("hidden")));    // 0x71007d61fa
extern unsigned char gLocal7d6208_35b928[] __attribute__((visibility("hidden")));    // 0x71007d6208
extern unsigned char gLocal7d6216_35b928[] __attribute__((visibility("hidden")));    // 0x71007d6216
// Reached through the GOT slot at 0x7100c22f68.
extern unsigned char gGlobalc22f68_35b928[];
extern unsigned char gLocal740db7_35b928[] __attribute__((visibility("hidden")));    // 0x7100740db7
extern unsigned char gLocal740dc1_35b928[] __attribute__((visibility("hidden")));    // 0x7100740dc1

// 0x710035b928: the two stack locals declared in the original's order (generated source)
int call_35b928(Arg35b928_0* p0, int p1) {
    void* local_8;
    long local_0;
    p0->field_0 = nullptr;
    p0->field_10 = nullptr;
    p0->field_8 = nullptr;
    p0->field_38 = nullptr;
    p0->field_40 = nullptr;
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
    p0->field_8d0 = p1;
    p0->field_8d4 = 0;
    p0->field_8d8 = 0;
    callee_1f8700(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x8e0));
    callee_1f8700(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x980));
    void* v18 = gGlobalc22a00_35b928;
    callee4_1e2360(v18, p0, 0x4203, gLocal7d6180_35b928);
    void* v20 = gGlobalc22a00_35b928;
    callee4_1e2360(v20, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x8), 0x41e5, gLocal7d6191_35b928);
    void* v22 = gGlobalc22a00_35b928;
    callee4_1e2360(v22, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x10), 0x41e5, gLocal7d61a1_35b928);
    Node35b928_v24* v24 = p0->field_8;
    Node35b928_v25* v25 = v24->field_18;
    unsigned char v26 = v25->field_58;
    v25->field_58 = v26 & 0xfe;
    Node35b928_v27* v27 = p0->field_10;
    Node35b928_v28* v28 = v27->field_18;
    unsigned char v29 = v28->field_58;
    v28->field_58 = v29 & 0xfe;
    void* v30 = gGlobalc22a00_35b928;
    callee_1e26e8(v30);
    Node35b928_v32* v32 = gGlobalc22a30_35b928;
    local_0 = 0x41e0000041e00000;
    local_8 = nullptr;
    callee_1e709c(v32, &local_8, &local_0, 0x3c, 0x41, 0);
    v32->field_20b98 = 2;
    if (p1 != 2) {
        if (p1 != 1) {
            if (p1 == 0) {
                Node35b928_v38* v34 = p0->field_0;
                void* c35 = callee_1e3770(v34, gLocal7d61b5_35b928, 0);
                p0->field_18 = static_cast<Node35b928_v114*>(c35);
                Node35b928_v38* v36 = p0->field_0;
                void* c37 = callee_1e3770(v36, gLocal7d61c2_35b928, 0);
                Node35b928_v38* v38 = p0->field_0;
                p0->field_20 = static_cast<Node35b928_v120*>(c37);
                Node35b928_v39* v39 = v38->field_18;
                void* c42 = v39->slot_12(gLocal7d61d0_35b928, 1);
                Node35b928_v38* v43 = p0->field_0;
                p0->field_38 = c42;
                Node35b928_v39* v44 = v43->field_18;
                C4735b928* c47 = static_cast<C4735b928*>(v44->slot_12(gLocal7d61de_35b928, 1));
                p0->field_40 = reinterpret_cast<void*>(c47);
                float v48 = c47->field_50;
                void* c49 = callee_217d64(0x42);
                int c50 = callee_1e73c0(v32, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x48), c49, 0x10, 1, 0xff, v48, 0.0f);
                p0->field_8d8 = c50;
            }
        } else {
            Node35b928_v38* v51 = p0->field_0;
            void* c52 = callee_1e3770(v51, gLocal7d61ed_35b928, 0);
            p0->field_18 = static_cast<Node35b928_v114*>(c52);
            Node35b928_v38* v53 = p0->field_0;
            void* c54 = callee_1e3770(v53, gLocal7d61fa_35b928, 0);
            Node35b928_v38* v55 = p0->field_0;
            p0->field_20 = static_cast<Node35b928_v120*>(c54);
            Node35b928_v39* v56 = v55->field_18;
            void* c59 = v56->slot_12(gLocal7d6208_35b928, 1);
            Node35b928_v38* v60 = p0->field_0;
            p0->field_38 = c59;
            Node35b928_v39* v61 = v60->field_18;
            C6435b928* c64 = static_cast<C6435b928*>(v61->slot_12(gLocal7d6216_35b928, 1));
            p0->field_40 = reinterpret_cast<void*>(c64);
            float v65 = c64->field_50;
            void* c66 = callee_217d64(0x56);
            int c67 = callee_1e73c0(v32, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x48), c66, 0x10, 1, 0xff, v65, 0.0f);
            p0->field_8d8 = c67;
        }
    } else {
        Node35b928_v38* v68 = p0->field_0;
        void* c69 = callee_1e3770(v68, gLocal7d61ed_35b928, 0);
        p0->field_18 = static_cast<Node35b928_v114*>(c69);
        Node35b928_v38* v70 = p0->field_0;
        void* c71 = callee_1e3770(v70, gLocal7d61fa_35b928, 0);
        Node35b928_v38* v72 = p0->field_0;
        p0->field_20 = static_cast<Node35b928_v120*>(c71);
        Node35b928_v39* v73 = v72->field_18;
        void* c76 = v73->slot_12(gLocal7d6208_35b928, 1);
        Node35b928_v38* v77 = p0->field_0;
        p0->field_38 = c76;
        Node35b928_v39* v78 = v77->field_18;
        C8135b928* c81 = static_cast<C8135b928*>(v78->slot_12(gLocal7d6216_35b928, 1));
        p0->field_40 = reinterpret_cast<void*>(c81);
        float v82 = c81->field_50;
        void* c83 = callee_217d64(0xa9);
        int c84 = callee_1e73c0(v32, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x48), c83, 0x10, 1, 0xff, v82, 0.0f);
        p0->field_8d8 = c84;
    }
    PanelPane* c85 = new PanelPane;
    void* v87 = p0->field_40;
    p0->field_8c8 = reinterpret_cast<Node35b928_v89*>(c85);
    callee2_5da17c(v87, c85);
    Node35b928_v89* v89 = p0->field_8c8;
    unsigned char v90 = v89->field_5b;
    v89->field_5b = (v90 & 0xf3) | 8;
    Node35b928_v89* v91 = p0->field_8c8;
    int v92 = p0->field_8d8;
    callee_1e41d8(v91, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x48), v92);
    void* v94 = gGlobalc22a00_35b928;
    callee_1e26e4(v94);
    Node35b928_v24* v96 = p0->field_8;
    void* c97 = callee_1e3770(v96, gLocal740db7_35b928, 1);
    p0->field_28 = c97;
    Node35b928_v27* v98 = p0->field_10;
    void* c99 = callee_1e3770(v98, gLocal740dc1_35b928, 1);
    Node35b928_v24* v100 = p0->field_8;
    p0->field_30 = c99;
    void* v101 = p0->field_38;
    Node35b928_v25* v102 = v100->field_18;
    callee2_5da17c(v101, v102);
    Node35b928_v27* v104 = p0->field_10;
    void* v105 = p0->field_38;
    Node35b928_v28* v106 = v104->field_18;
    callee2_5da17c(v105, v106);
    Node35b928_v24* v108 = p0->field_8;
    void* v109 = p0->field_28;
    callee_1f8820(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x8e0), v108, v109, 0xa);
    Node35b928_v27* v111 = p0->field_10;
    void* v112 = p0->field_30;
    callee_1f8820(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x980), v111, v112, 0xa);
    Node35b928_v114* v114 = p0->field_18;
    void* v115 = v114->field_18;
    Node35b928_v24* v116 = p0->field_8;
    Node35b928_v25* v117 = v116->field_18;
    float v118 = v117->field_48;
    callee_1e4570(v115, v118);
    Node35b928_v120* v120 = p0->field_20;
    void* v121 = v120->field_18;
    Node35b928_v24* v122 = p0->field_8;
    Node35b928_v25* v123 = v122->field_18;
    float v124 = v123->field_48;
    int c125 = callee_1e4570(v121, v124);
    return c125;
}

int callee_5c3ac8(void*);        // 0x71005c3ac8

struct Node5252f0_v0 {
    int field_0;                 // +0
    unsigned char pad4[0x1c];
    void* field_20;               // +20
    void* field_28;               // +28
    void* field_30;               // +30
};

struct Arg5252f0_0 {
    long field_0;                // +0
    unsigned char pad8[0x8];
    Node5252f0_v0* field_10;      // +10
};
// Reached through the GOT slot at 0x7100c2ca08.
extern void* gGlobalc2ca08_5252f0;
// Reached through the GOT slot at 0x7100c2d1a8.
extern unsigned char gGlobalc2d1a8_5252f0[];

// 0x71005252f0: the element address computed as a pointer offset before the function pointer is loaded (generated source)
int call_5252f0(Arg5252f0_0* p0) {
    Node5252f0_v0* v0 = p0->field_10;
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2d1a8_5252f0) + 0x10);
    if (v0 != 0) {
        void* v1 = v0->field_30;
        v0->field_20 = nullptr;
        v0->field_28 = nullptr;
        if (v1 != 0) {
            int v2 = v0->field_0;
            if (v2 >= 1) {
                void* v3 = gGlobalc2ca08_5252f0;
                reinterpret_cast<void (*)(void*)>(v3)(v1);
                int v5 = v0->field_0;
                if (v5 >= 2) {
                    long r6 = 1;
                    long r7 = 0x40;
                    void* v8;
                    void* v9;
                    int v11;
                    do {
                        v8 = v0->field_30;
                        void* arg = static_cast<unsigned char*>(v8) + r7;
                        v9 = gGlobalc2ca08_5252f0;
                        reinterpret_cast<void (*)(void*)>(v9)(arg);
                        v11 = v0->field_0;
                        long next_r6 = r6 + 1;
                        long next_r7 = r7 + 0x40;
                        r6 = next_r6;
                        r7 = next_r7;
                    } while (r6 < static_cast<long>(static_cast<int>(v11)));
                }
            }
        }
    }
    return callee_5c3ac8(p0);
}

int callee_46194(long);        // 0x7100046194
void callee_46240(long);        // 0x7100046240

struct Argc6fe4_0 {
    volatile long field_0;                // +0
    void* field_8;               // +8
    int field_10;                 // +10
    unsigned char pad14[0xc];
    void* field_20;               // +20
    void* field_28;               // +28
    void* field_30;               // +30
    void* field_38;               // +38
    void* field_40;               // +40
    void* field_48;               // +48
    void* field_50;               // +50
    void* field_58;               // +58
    unsigned char pad60[0x20];
    int field_80;                 // +80
    unsigned char pad84[0xc];
    void* field_90;               // +90
    void* field_98;               // +98
    int field_a0;                 // +a0
    unsigned char pada4[0xc];
    void* field_b0;               // +b0
    void* field_b8;               // +b8
    unsigned short field_c0;      // +c0
};

struct Globalc216f8_c6fe4 {
    unsigned char pad0[0x30];
    void* field_30;               // +30
    void* field_38;               // +38
};

struct Globalc216a8_c6fe4 {
    void* field_0;               // +0
    void* field_8;               // +8
};
// Reached through the GOT slot at 0x7100c219e0.
extern int gGlobalc219e0_c6fe4;
// Reached through the GOT slot at 0x7100c216f8.
extern Globalc216f8_c6fe4 gGlobalc216f8_c6fe4;
// Reached through the GOT slot at 0x7100c216a8.
extern Globalc216a8_c6fe4 gGlobalc216a8_c6fe4;
// Reached through the GOT slot at 0x7100c22878.
extern unsigned char gGlobalc22878_c6fe4[];

// 0x71000c6fe4: the vtable field volatile, so its store stays in source order (voltry)
int call_c6fe4(Argc6fe4_0* p0) {
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc22878_c6fe4) + 0x10);
    p0->field_8 = nullptr;
    int v0 = gGlobalc219e0_c6fe4;
    p0->field_10 = v0;
    void* v1 = gGlobalc216f8_c6fe4.field_38;
    p0->field_28 = v1;
    void* v2 = gGlobalc216f8_c6fe4.field_30;
    p0->field_20 = v2;
    void* v3 = gGlobalc216f8_c6fe4.field_38;
    p0->field_38 = v3;
    void* v4 = gGlobalc216f8_c6fe4.field_30;
    p0->field_30 = v4;
    void* v5 = gGlobalc216f8_c6fe4.field_38;
    p0->field_48 = v5;
    void* v6 = gGlobalc216f8_c6fe4.field_30;
    p0->field_40 = v6;
    void* v7 = gGlobalc216a8_c6fe4.field_8;
    p0->field_58 = v7;
    void* v8 = gGlobalc216a8_c6fe4.field_0;
    p0->field_50 = v8;
    callee_46240(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x60));
    callee_46240(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x68));
    int c11 = callee_46194(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x70));
    p0->field_80 = 0;
    void* v12 = gGlobalc216a8_c6fe4.field_8;
    p0->field_98 = v12;
    void* v13 = gGlobalc216a8_c6fe4.field_0;
    p0->field_90 = v13;
    p0->field_a0 = 0;
    void* v14 = gGlobalc216f8_c6fe4.field_38;
    p0->field_b8 = v14;
    void* v15 = gGlobalc216f8_c6fe4.field_30;
    p0->field_b0 = v15;
    p0->field_c0 = 0;
    return c11;
}

void callee_30e84c(long);        // 0x710030e84c
void callee_38c480(void*, int, void*, void*);        // 0x710038c480
void callee_38cc6c(void*, int);        // 0x710038cc6c
void callee_38ccb0(void*, int, void*, int);        // 0x710038ccb0

class Node392d44_v14 {
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

struct Node392d44_v13 {
    unsigned char pad0[0x18];
    Node392d44_v14* field_18;     // +18
};

struct Arg392d44_0 {
    long field_0;                // +0
    Node392d44_v13* field_8;     // +8
    unsigned char pad10[0x2258];
    long field_2268;                // +2268
    void* field_2270;               // +2270
    unsigned char pad2278[0x4400];
    void* field_6678;               // +6678
    void* field_6680;               // +6680
    void* field_6688;               // +6688
    float field_6690;                 // +6690
    float field_6694;                 // +6694
    unsigned char field_6698;       // +6698
    unsigned char pad6699[0x3];
    int field_669c;                 // +669c
    int field_66a0;                 // +66a0
    unsigned char field_66a4;       // +66a4
    unsigned char pad66a5[0x3];
    int field_66a8;                 // +66a8
    int field_66ac;                 // +66ac
    unsigned char field_66b0;       // +66b0
    unsigned char pad66b1[0x7];
    int field_66b8;                 // +66b8
    unsigned char pad66bc[0x4];
    void* field_66c0;               // +66c0
    long field_66c8;                // +66c8
    long field_66d0;                // +66d0
    unsigned short field_66d8;      // +66d8
    unsigned short field_66da;      // +66da
    unsigned char pad66dc[0x4];
    unsigned char field_66e0;       // +66e0
    unsigned char pad66e1[0xf];
    void* field_66f0;               // +66f0
    unsigned char pad66f8[0xaa0];
    void* field_7198;               // +7198
    unsigned char pad71a0[0x10];
    float field_71b0;                 // +71b0
    float field_71b4;                 // +71b4
    unsigned char pad71b8[0x4];
    long field_71bc __attribute__((packed, aligned(4)));                // +71bc
    unsigned char pad71c4[0x8];
    int field_71cc;                 // +71cc
    unsigned char pad71d0[0x8];
    int field_71d8;                 // +71d8
    unsigned char pad71dc[0x14];
    void* field_71f0;               // +71f0
    void* field_71f8;               // +71f8
};

struct C21392d44 {
    unsigned char pad0[0x58];
    unsigned char field_58;       // +58
};

struct C30392d44 {
    unsigned char pad0[0x58];
    unsigned char field_58;       // +58
};

struct Elem392d44_r1 {
    unsigned char pad0[0x88];
};
// Reached through the GOT slot at 0x7100c22a00.
extern void* gGlobalc22a00_392d44;
extern unsigned char gLocal7db06f_392d44[] __attribute__((visibility("hidden")));    // 0x71007db06f
extern unsigned char gLocal7db088_392d44[] __attribute__((visibility("hidden")));    // 0x71007db088
// Reached through the GOT slot at 0x7100c2b198.
extern unsigned char gGlobalc2b198_392d44[];
// Reached through the GOT slot at 0x7100c2b1f8.
extern unsigned char gGlobalc2b1f8_392d44[];
// Reached through the GOT slot at 0x7100c22f00.
extern unsigned char gGlobalc22f00_392d44[];
extern unsigned char gLocal73fffb_392d44[] __attribute__((visibility("hidden")));    // 0x710073fffb
extern unsigned char gLocal7d6062_392d44[] __attribute__((visibility("hidden")));    // 0x71007d6062
extern unsigned char gLocal740004_392d44[] __attribute__((visibility("hidden")));    // 0x7100740004
extern unsigned char gLocal74053d_392d44[] __attribute__((visibility("hidden")));    // 0x710074053d
extern unsigned char gLocal74056c_392d44[] __attribute__((visibility("hidden")));    // 0x710074056c
extern unsigned char gLocal7db098_392d44[] __attribute__((visibility("hidden")));    // 0x71007db098
extern unsigned char gLocal740512_392d44[] __attribute__((visibility("hidden")));    // 0x7100740512
extern unsigned char gLocal7db0a3_392d44[] __attribute__((visibility("hidden")));    // 0x71007db0a3
extern unsigned char gLocal7db0af_392d44[] __attribute__((visibility("hidden")));    // 0x71007db0af
extern unsigned char gLocal7da3d0_392d44[] __attribute__((visibility("hidden")));    // 0x71007da3d0
extern unsigned char gLocal7db0b8_392d44[] __attribute__((visibility("hidden")));    // 0x71007db0b8

// 0x7100392d44: float fields for the float constants (16.0f, 28.0f), so ConstantHoisting does not derive one from another; the member store after both vtable stores
void* call_392d44(Arg392d44_0* p0) {
    callee_38c480(p0, 0x4204, gLocal7db06f_392d44, gLocal7db088_392d44);
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2b198_392d44) + 0x10);
    p0->field_2268 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2b1f8_392d44) + 0x10);
    p0->field_2270 = nullptr;
    new (reinterpret_cast<unsigned char*>(p0) + 0x2278) LayoutFrame[0x80];
    p0->field_6688 = nullptr;
    p0->field_6680 = nullptr;
    p0->field_6678 = nullptr;
    p0->field_6690 = 16.0f;
    p0->field_6694 = 16.0f;
    p0->field_6698 = 0;
    p0->field_669c = 0x41;
    p0->field_66a0 = 0x4e;
    p0->field_66a4 = 0;
    p0->field_66a8 = 0x51;
    p0->field_66ac = 0;
    p0->field_66b0 = 0;
    p0->field_66b8 = -1;
    p0->field_66c0 = nullptr;
    new (reinterpret_cast<unsigned char*>(p0) + 0x66c8) LayoutHandle;
    p0->field_66e0 = 0;
    callee_30e84c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x66e8));
    p0->field_71d8 = 0;
    p0->field_71f8 = nullptr;
    p0->field_71f0 = nullptr;
    void* v5 = gGlobalc22a00_392d44;
    callee_1e26e8(v5);
    callee_38ccb0(p0, 0, gLocal73fffb_392d44, 0);
    callee_38ccb0(p0, 1, gLocal7d6062_392d44, 0);
    callee_38ccb0(p0, 2, gLocal740004_392d44, 0);
    callee_38ccb0(p0, 3, gLocal74053d_392d44, 0);
    callee_38ccb0(p0, 4, gLocal74056c_392d44, 0);
    callee_38cc6c(p0, 0xd);
    Node392d44_v13* v13 = p0->field_8;
    Node392d44_v14* v14 = v13->field_18;
    void* c17 = v14->slot_12(gLocal7db098_392d44, 1);
    p0->field_2270 = c17;
    p0->field_6678 = reinterpret_cast<void*>(gLocal740512_392d44);
    p0->field_6690 = 28.0f;
    p0->field_6694 = 28.0f;
    p0->field_669c = 0x41;
    p0->field_66a0 = 0x4e;
    p0->field_66b0 = 1;
    Node392d44_v14* v18 = v13->field_18;
    C21392d44* c21 = static_cast<C21392d44*>(v18->slot_12(gLocal7db0a3_392d44, 1));
    p0->field_66c0 = reinterpret_cast<void*>(c21);
    unsigned char v22 = c21->field_58;
    c21->field_58 = v22 & 0xfe;
    Node392d44_v14* v23 = v13->field_18;
    void* c26 = v23->slot_12(gLocal7db0af_392d44, 1);
    p0->field_66f0 = c26;
    p0->field_7198 = reinterpret_cast<void*>(gLocal740512_392d44);
    p0->field_71b0 = 16.0f;
    p0->field_71b4 = 16.0f;
    p0->field_71cc = 1;
    p0->field_71bc = 0x430000003c;
    Node392d44_v14* v27 = v13->field_18;
    C30392d44* c30 = static_cast<C30392d44*>(v27->slot_12(gLocal7da3d0_392d44, 1));
    p0->field_71f0 = reinterpret_cast<void*>(c30);
    unsigned char v31 = c30->field_58;
    c30->field_58 = v31 & 0xfe;
    void* c32 = callee_1e3770(v13, gLocal7db0b8_392d44, 0);
    p0->field_71f8 = c32;
    return c32;
}

void callee_3005f0(long, int);        // 0x71003005f0
void callee_3166d4(long, int);        // 0x71003166d4
void callee_316a64(void*);        // 0x7100316a64
int callee2_39e154(long, int);        // 0x710039e154

struct Arg2fb5c0_0 {
    long field_0;                // +0
    unsigned char pad8[0x7618];
    void* field_7620;               // +7620
    unsigned char pad7628[0x10];
    void* field_7638;               // +7638
    void* field_7640;               // +7640
    void* field_7648;               // +7648
    void* field_7650;               // +7650
    void* field_7658;               // +7658
    void* field_7660;               // +7660
    unsigned char pad7668[0x6a10];
    int field_e078;                 // +e078
    int field_e07c;                 // +e07c
    long field_e080;                // +e080
    long field_e088;                // +e088
    unsigned short field_e090;      // +e090
    unsigned short field_e092;      // +e092
    unsigned char pade094[0x6994];
    unsigned char field_14a28;       // +14a28
};

struct Elem2fb5c0_r4 {
    unsigned char pad0[0x48];
};
// Reached through the GOT slot at 0x7100c2ac38.
extern unsigned char gGlobalc2ac38_2fb5c0[];
// Reached through the GOT slot at 0x7100c22f00.
extern unsigned char gGlobalc22f00_2fb5c0[];

class Built316a64 {
public:
    Built316a64();                                                       // 0x7100316a64
    unsigned char pad[0x40];
};

class LightResource {
public:
    LightResource();                                                     // 0x71005d2744
    unsigned char pad[0x110];
};

class Obj3005f0 {
public:
    Obj3005f0(int);                                                      // 0x71003005f0
    unsigned char pad[0x73c0];
};

class PanelBase_316a64 {
public:
    PanelBase_316a64();                                                    // 0x7100316a64
    virtual ~PanelBase_316a64();
    unsigned char pad8[0x38];
};

class Class2fb5c0 : public PanelBase_316a64 {
public:
    Class2fb5c0();
    virtual ~Class2fb5c0();

    LightResource m40;
    LightResource m150;
    Obj3005f0 m260;
    void* f7620;
    unsigned char pad7628[0x10];
    void* f7638;
    void* f7640;
    void* f7648;
    void* f7650;
    void* f7658;
    void* f7660;
    unsigned char pad7668[0x10];
    LayoutSprite a7678[256];
    LayoutFrame mbe78;
    LayoutFrame mbf00;
    LayoutFrame mbf88;
    LayoutFrame mc010;
    LayoutFrame mc098;
    LayoutFrame mc120;
    LayoutFrame mc1a8;
    LayoutFrame mc230;
    LayoutFrame mc2b8;
    LayoutFrame mc340;
    LayoutFrame mc3c8;
    LayoutFrame mc450;
    LayoutFrame mc4d8;
    LayoutFrame mc560;
    LayoutFrame mc5e8;
    LayoutFrame mc670;
    LayoutFrame mc6f8;
    LayoutFrame mc780;
    LayoutFrame mc808;
    LayoutFrame mc890;
    LayoutFrame mc918;
    LayoutFrame mc9a0;
    LayoutFrame mca28;
    LayoutFrame mcab0;
    LayoutFrame mcb38;
    LayoutFrame mcbc0;
    LayoutFrame mcc48;
    LayoutFrame mccd0;
    LayoutFrame mcd58;
    LayoutFrame mcde0;
    LayoutFrame mce68;
    LayoutFrame mcef0;
    LayoutFrame mcf78;
};

Class2fb5c0::Class2fb5c0()
    : m260(0), f7620(nullptr), f7638(nullptr), f7640(nullptr), f7648(nullptr), f7650(nullptr), f7658(nullptr), f7660(nullptr) {
    Arg2fb5c0_0* p0 = reinterpret_cast<Arg2fb5c0_0*>(this);
    callee2_1f0140(reinterpret_cast<long>(p0) + (0xd << 0xc));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd088));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd110));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd198));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd220));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd2a8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd330));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd3b8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd440));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd4c8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd550));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd5d8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd660));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd6e8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd770));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd7f8));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd880));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd908));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd990));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xda18));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xdaa0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xdb28));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xdbb0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xdc38));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xdcc0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xdd48));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xddd0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xde58));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xdee0));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xdf68));
    callee2_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xdff0));
    p0->field_e078 = 0;
    p0->field_e07c = 0;
    new (reinterpret_cast<unsigned char*>(p0) + 0xe080) LayoutHandle;
    callee_3166d4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xe098), 1);
    callee_3166d4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xe0b0), 1);
    callee2_39e154(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xe0c8), 0);
    callee2_39e154(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x103e8), 0);
    int c75 = callee2_39e154(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x12708), 0);
    p0->field_14a28 = 0;
}


void callee_366f48(long);        // 0x7100366f48
void callee_37cd30(long, float, float, float);        // 0x710037cd30

struct Arg365c90_0 {
    long field_0;                // +0
    int field_8;                 // +8
    int field_c;                 // +c
    void* field_10;               // +10
    void* field_18;               // +18
    unsigned char pad20[0x17aa0];
    void* field_17ac0;               // +17ac0
    void* field_17ac8;               // +17ac8
};
// Reached through the GOT slot at 0x7100c2b008.
extern unsigned char gGlobalc2b008_365c90[];

// 0x7100365c90: the 0xff fill as a loop, which LoopIdiomRecognize makes a memset after TailCallElim has run (so bl memset; ret, not a tail call)
void call_365c90(Arg365c90_0* p0, void* p1) {
    p0->field_8 = 4;
    p0->field_c = 2;
    p0->field_10 = nullptr;
    p0->field_18 = p1;
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2b008_365c90) + 0x10);
    callee_366f48(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x20));
    callee_366f48(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2270));
    callee_366f48(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x44c0));
    callee_366f48(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x6710));
    callee_366f48(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x8960));
    callee_366f48(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xabb0));
    callee_366f48(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xce00));
    callee_366f48(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xf050));
    callee_366f48(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x112a0));
    callee_366f48(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x134f0));
    callee_366f48(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x15740));
    callee_37f550(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x17a90));
    p0->field_17ac8 = nullptr;
    p0->field_17ac0 = nullptr;
    callee_37cc88(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x17a90));
    callee_37cd30(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x17a90), -2.8e+02f, 425.0f, 844.0f);
    // A loop: LoopIdiomRecognize makes it a memset after TailCallElim has run, so the call is not a tail call.
    for (int i = 0; i < 0x100; i++)
        reinterpret_cast<unsigned char*>(p0)[0x17990 + i] = 0xff;
}


struct Node391fbc_v1 {
    unsigned char pad0[0x18];
    void* field_18;               // +18
};

class Node391fbc_v0 {
public:
    virtual void slot_0();
    virtual void slot_1();

    unsigned char pad8[0x10];
    Node391fbc_v1* volatile field_18;      // +18
};

struct Arg391fbc_0 {
    Node391fbc_v0* field_0;      // +0
    unsigned char pad8[0x10];
    long field_18;                // +18
};

struct Node391fbc_v8 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};

struct Globalc22f00_391fbc {
    unsigned char pad0[0x28];
    void* field_28;               // +28
};
// Reached through the GOT slot at 0x7100c22a00.
extern void* gGlobalc22a00_391fbc;
// Reached through the GOT slot at 0x7100c21db0.
extern Node391fbc_v8* gGlobalc21db0_391fbc;
// Reached through the GOT slot at 0x7100c22f00.
extern Globalc22f00_391fbc gGlobalc22f00_391fbc;

// 0x7100391fbc: the object's link pointer volatile, so it is read again for the unlink call as in the original
int call_391fbc(Arg391fbc_0* p0) {
    Node391fbc_v0* v0 = p0->field_0;
    if (v0 != 0) {
        Node391fbc_v1* v1 = v0->field_18;
        void* v2 = v1->field_18;
        if (v2 != 0) {
            Node391fbc_v1* v3 = v0->field_18;
            void* v4 = v3->field_18;
            callee_5da1b0(v4, v3);
            Node391fbc_v0* v6 = p0->field_0;
            if (v6 != 0) {
                void* v7 = gGlobalc22a00_391fbc;
                Node391fbc_v8* v8 = gGlobalc21db0_391fbc;
                void* v9 = v8->field_2af8;
                callee_5d4408(v6, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v9) + 0x10));
                Node391fbc_v0* v11 = p0->field_0;
                v11->slot_1();
                Node391fbc_v0* v15 = p0->field_0;
                callee3_5c3774(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v7) + 0x68), v15);
                p0->field_0 = nullptr;
            }
        } else {
            void* v18 = gGlobalc22a00_391fbc;
            Node391fbc_v8* v19 = gGlobalc21db0_391fbc;
            void* v20 = v19->field_2af8;
            callee_5d4408(v0, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v20) + 0x10));
            Node391fbc_v0* v22 = p0->field_0;
            v22->slot_1();
            Node391fbc_v0* v26 = p0->field_0;
            callee3_5c3774(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v18) + 0x68), v26);
            p0->field_0 = nullptr;
        }
        p0->field_0 = nullptr;
    }
    p0->field_18 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(&gGlobalc22f00_391fbc) + 0x10);
    void* v30 = gGlobalc22f00_391fbc.field_28;
    Node391fbc_v8* v31 = gGlobalc21db0_391fbc;
    long m33;
    if (v31 != 0) {
        void* v32 = v31->field_2af8;
        m33 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v32) + 0x10);
    } else {
        m33 = 0;
    }
    return reinterpret_cast<int (*)(long, long)>(v30)(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x18), m33);
}

int callee2_38f958(void*);        // 0x710038f958

struct Node390210_v1 {
    unsigned char pad0[0x18];
    void* field_18;               // +18
};

class Node390210_v0 {
public:
    virtual void slot_0();
    virtual void slot_1();

    unsigned char pad8[0x10];
    Node390210_v1* volatile field_18;      // +18
};

struct Arg390210_0 {
    long field_0;                // +0
    unsigned char pad8[0x2260];
    Node390210_v0* field_2268;      // +2268
    unsigned char pad2270[0x8];
    void* field_2278;               // +2278
};

struct Node390210_v8 {
    unsigned char pad0[0x2af8];
    void* field_2af8;               // +2af8
};
// Reached through the GOT slot at 0x7100c22a00.
extern void* gGlobalc22a00_390210;
// Reached through the GOT slot at 0x7100c21db0.
extern Node390210_v8* gGlobalc21db0_390210;
// Reached through the GOT slot at 0x7100c2b1a8.
extern unsigned char gGlobalc2b1a8_390210[];

// 0x7100390210: the object's link pointer volatile, so it is read again for the unlink call as in the original
int call_390210(Arg390210_0* p0) {
    Node390210_v0* v0 = p0->field_2268;
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2b1a8_390210) + 0x10);
    if (v0 != 0) {
        Node390210_v1* v1 = v0->field_18;
        void* v2 = v1->field_18;
        if (v2 != 0) {
            void* v3 = p0->field_2278;
            Node390210_v1* v4 = v0->field_18;
            callee_5da1b0(v3, v4);
            Node390210_v0* v6 = p0->field_2268;
            if (v6 != 0) {
                void* v7 = gGlobalc22a00_390210;
                Node390210_v8* v8 = gGlobalc21db0_390210;
                void* v9 = v8->field_2af8;
                callee_5d4408(v6, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v9) + 0x10));
                Node390210_v0* v11 = p0->field_2268;
                v11->slot_1();
                Node390210_v0* v15 = p0->field_2268;
                callee3_5c3774(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v7) + 0x68), v15);
                p0->field_2268 = nullptr;
            }
        } else {
            void* v18 = gGlobalc22a00_390210;
            Node390210_v8* v19 = gGlobalc21db0_390210;
            void* v20 = v19->field_2af8;
            callee_5d4408(v0, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v20) + 0x10));
            Node390210_v0* v22 = p0->field_2268;
            v22->slot_1();
            Node390210_v0* v26 = p0->field_2268;
            callee3_5c3774(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v18) + 0x68), v26);
            p0->field_2268 = nullptr;
        }
    }
    return callee2_38f958(p0);
}


void callee2_1e22e4(void*, int);        // 0x71001e22e4
void callee5_1e2360(void*, void*, int, void*);        // 0x71001e2360
void callee5_1e2360(void*, long, int, void*);        // 0x71001e2360

class Node28b238_v24 {
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

    unsigned char pad8[0x40];
    float field_48;               // +48
};

struct Node28b238_v23 {
    unsigned char pad0[0x18];
    Node28b238_v24* field_18;     // +18
};

struct Node28b238_v9 {
    unsigned char pad0[0x58];
    unsigned char field_58;       // +58
};

struct Node28b238_v8 {
    unsigned char pad0[0x18];
    Node28b238_v9* field_18;      // +18
};

struct Node28b238_v12 {
    unsigned char pad0[0x58];
    unsigned char field_58;       // +58
};

struct Node28b238_v11 {
    unsigned char pad0[0x18];
    Node28b238_v12* field_18;     // +18
};

struct Node28b238_v15 {
    unsigned char pad0[0x58];
    unsigned char field_58;       // +58
};

struct Node28b238_v14 {
    unsigned char pad0[0x18];
    Node28b238_v15* field_18;     // +18
};

struct Node28b238_v108 {
    unsigned char pad0[0x18];
    void* field_18;               // +18
};

struct Node28b238_v120 {
    unsigned char pad0[0x18];
    void* field_18;               // +18
};

struct Node28b238_v114 {
    unsigned char pad0[0x18];
    void* field_18;               // +18
};

struct Node28b238_v126 {
    unsigned char pad0[0x18];
    void* field_18;               // +18
};

struct Node28b238_v98 {
    unsigned char pad0[0x5b];
    unsigned char field_5b;       // +5b
};

struct Node28b238_v100 {
    unsigned char pad0[0x5b];
    unsigned char field_5b;       // +5b
};

struct Arg28b238_0 {
    Node28b238_v23* field_0;     // +0
    Node28b238_v8* field_8;      // +8
    Node28b238_v11* field_10;     // +10
    Node28b238_v14* field_18;     // +18
    Node28b238_v108* field_20;    // +20
    Node28b238_v120* field_28;    // +28
    Node28b238_v114* field_30;    // +30
    Node28b238_v126* field_38;    // +38
    void* field_40;               // +40
    void* field_48;               // +48
    void* field_50;               // +50
    void* field_58;               // +58
    void* field_60;               // +60
    void* field_68;               // +68
    void* field_70;               // +70
    unsigned char pad78[0x1100];
    Node28b238_v98* field_1178;     // +1178
    Node28b238_v100* field_1180;    // +1180
    unsigned char pad1188[0x8];
    int field_1190;                 // +1190
    int field_1194;                 // +1194
};

struct Node28b238_v17 {
    unsigned char pad0[0x20b98];
    int field_20b98;                 // +20b98
};

struct C8728b238 {
    long field_0;                // +0
    unsigned char pad8[0x158];
    void* field_160;               // +160
    void* field_168;               // +168
    void* field_170;               // +170
};

struct C9028b238 {
    long field_0;                // +0
    unsigned char pad8[0x158];
    void* field_160;               // +160
    void* field_168;               // +168
    void* field_170;               // +170
};
// Reached through the GOT slot at 0x7100c22a00.
extern void* gGlobalc22a00_28b238;
// Reached through the GOT slot at 0x7100c22a30.
extern Node28b238_v17* gGlobalc22a30_28b238;
extern unsigned char gLocal7d6180_28b238[] __attribute__((visibility("hidden")));    // 0x71007d6180
extern unsigned char gLocal7d6191_28b238[] __attribute__((visibility("hidden")));    // 0x71007d6191
extern unsigned char gLocal7d61a1_28b238[] __attribute__((visibility("hidden")));    // 0x71007d61a1
extern unsigned char gLocal7d61b5_28b238[] __attribute__((visibility("hidden")));    // 0x71007d61b5
extern unsigned char gLocal7d61c2_28b238[] __attribute__((visibility("hidden")));    // 0x71007d61c2
extern unsigned char gLocal7d61d0_28b238[] __attribute__((visibility("hidden")));    // 0x71007d61d0
extern unsigned char gLocal7d61de_28b238[] __attribute__((visibility("hidden")));    // 0x71007d61de
extern unsigned char gLocal7d61ed_28b238[] __attribute__((visibility("hidden")));    // 0x71007d61ed
extern unsigned char gLocal7d61fa_28b238[] __attribute__((visibility("hidden")));    // 0x71007d61fa
extern unsigned char gLocal7d6208_28b238[] __attribute__((visibility("hidden")));    // 0x71007d6208
extern unsigned char gLocal7d6216_28b238[] __attribute__((visibility("hidden")));    // 0x71007d6216
extern unsigned char gLocal740db7_28b238[] __attribute__((visibility("hidden")));    // 0x7100740db7
extern unsigned char gLocal740dc1_28b238[] __attribute__((visibility("hidden")));    // 0x7100740dc1
// Reached through the GOT slot at 0x7100c22f68.
extern unsigned char gGlobalc22f68_28b238[];

// 0x710028b238: the two stack locals declared in the original's order (generated source)
int call_28b238(Arg28b238_0* p0) {
    void* local_8;
    long local_0;
    void* v0 = gGlobalc22a00_28b238;
    callee5_1e2360(v0, p0, 0x4203, gLocal7d6180_28b238);
    void* v2 = gGlobalc22a00_28b238;
    callee5_1e2360(v2, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x8), 0x41e5, gLocal7d6191_28b238);
    void* v4 = gGlobalc22a00_28b238;
    callee5_1e2360(v4, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x10), 0x41e5, gLocal7d6191_28b238);
    void* v6 = gGlobalc22a00_28b238;
    callee5_1e2360(v6, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x18), 0x41e5, gLocal7d61a1_28b238);
    Node28b238_v8* v8 = p0->field_8;
    Node28b238_v9* v9 = v8->field_18;
    unsigned char v10 = v9->field_58;
    v9->field_58 = v10 & 0xfe;
    Node28b238_v11* v11 = p0->field_10;
    Node28b238_v12* v12 = v11->field_18;
    unsigned char v13 = v12->field_58;
    v12->field_58 = v13 & 0xfe;
    Node28b238_v14* v14 = p0->field_18;
    Node28b238_v15* v15 = v14->field_18;
    unsigned char v16 = v15->field_58;
    v15->field_58 = v16 & 0xfe;
    Node28b238_v17* v17 = gGlobalc22a30_28b238;
    local_0 = 0x41e0000041e00000;
    local_8 = nullptr;
    callee_1e709c(v17, &local_8, &local_0, 0x3c, 0x41, 0);
    v17->field_20b98 = 2;
    Node28b238_v23* v19 = p0->field_0;
    void* c20 = callee_1e3770(v19, gLocal7d61b5_28b238, 0);
    p0->field_20 = static_cast<Node28b238_v108*>(c20);
    Node28b238_v23* v21 = p0->field_0;
    void* c22 = callee_1e3770(v21, gLocal7d61c2_28b238, 0);
    Node28b238_v23* v23 = p0->field_0;
    p0->field_30 = static_cast<Node28b238_v114*>(c22);
    Node28b238_v24* v24 = v23->field_18;
    void* c27 = v24->slot_12(gLocal7d61d0_28b238, 1);
    Node28b238_v23* v28 = p0->field_0;
    p0->field_58 = c27;
    Node28b238_v24* v29 = v28->field_18;
    void* c32 = v29->slot_12(gLocal7d61de_28b238, 1);
    p0->field_68 = c32;
    long a33 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x78);
    void* c34 = callee_217d64(0x42);
    int c35 = callee_1e73c0(v17, a33, c34, 0x10, 1, 0xff, 0.0f, 0.0f);
    p0->field_1190 = c35;
    local_0 = 0x41e0000041e00000;
    local_8 = nullptr;
    callee_1e709c(v17, &local_8, &local_0, 0x3c, 0x41, 0);
    v17->field_20b98 = 2;
    Node28b238_v23* v37 = p0->field_0;
    void* c38 = callee_1e3770(v37, gLocal7d61ed_28b238, 0);
    p0->field_28 = static_cast<Node28b238_v120*>(c38);
    Node28b238_v23* v39 = p0->field_0;
    void* c40 = callee_1e3770(v39, gLocal7d61fa_28b238, 0);
    Node28b238_v23* v41 = p0->field_0;
    p0->field_38 = static_cast<Node28b238_v126*>(c40);
    Node28b238_v24* v42 = v41->field_18;
    void* c45 = v42->slot_12(gLocal7d6208_28b238, 1);
    Node28b238_v23* v46 = p0->field_0;
    p0->field_60 = c45;
    Node28b238_v24* v47 = v46->field_18;
    void* c50 = v47->slot_12(gLocal7d6216_28b238, 1);
    p0->field_70 = c50;
    long a51 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x8f8);
    void* c52 = callee_217d64(0x56);
    int c53 = callee_1e73c0(v17, a51, c52, 0x10, 1, 0xff, 0.0f, 0.0f);
    p0->field_1194 = c53;
    Node28b238_v8* v54 = p0->field_8;
    void* c55 = callee_1e3770(v54, gLocal740db7_28b238, 1);
    p0->field_40 = c55;
    Node28b238_v11* v56 = p0->field_10;
    void* c57 = callee_1e3770(v56, gLocal740db7_28b238, 1);
    p0->field_48 = c57;
    Node28b238_v14* v58 = p0->field_18;
    void* c59 = callee_1e3770(v58, gLocal740dc1_28b238, 1);
    Node28b238_v8* v60 = p0->field_8;
    p0->field_50 = c59;
    void* v61 = p0->field_58;
    Node28b238_v9* v62 = v60->field_18;
    callee2_5da17c(v61, v62);
    Node28b238_v11* v64 = p0->field_10;
    void* v65 = p0->field_60;
    Node28b238_v12* v66 = v64->field_18;
    callee2_5da17c(v65, v66);
    Node28b238_v14* v68 = p0->field_18;
    void* v69 = p0->field_60;
    Node28b238_v15* v70 = v68->field_18;
    callee2_5da17c(v69, v70);
    Node28b238_v8* v72 = p0->field_8;
    void* v73 = p0->field_40;
    callee_1f8820(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1198), v72, v73, 0xa);
    Node28b238_v11* v75 = p0->field_10;
    void* v76 = p0->field_48;
    callee_1f8820(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1238), v75, v76, 0xa);
    Node28b238_v14* v78 = p0->field_18;
    void* v79 = p0->field_50;
    callee_1f8820(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x12d8), v78, v79, 0xa);
    void* v81 = gGlobalc22a00_28b238;
    callee2_1e22e4(v81, 0x41e5);
    void* v83 = gGlobalc22a00_28b238;
    callee2_1e22e4(v83, 0x41e5);
    void* v85 = gGlobalc22a00_28b238;
    callee2_1e22e4(v85, 0x41e5);
    PanelPane* m89 = new PanelPane;
    p0->field_1178 = reinterpret_cast<Node28b238_v98*>(m89);
    PanelPane* c90 = new PanelPane;
    void* v92 = p0->field_68;
    Node28b238_v98* v93 = p0->field_1178;
    p0->field_1180 = reinterpret_cast<Node28b238_v100*>(c90);
    callee2_5da17c(v92, v93);
    void* v95 = p0->field_70;
    Node28b238_v100* v96 = p0->field_1180;
    callee2_5da17c(v95, v96);
    Node28b238_v98* v98 = p0->field_1178;
    unsigned char v99 = v98->field_5b;
    v98->field_5b = (v99 & 0xf3) | 8;
    Node28b238_v100* v100 = p0->field_1180;
    unsigned char v101 = v100->field_5b;
    v100->field_5b = (v101 & 0xf3) | 8;
    Node28b238_v98* v102 = p0->field_1178;
    int v103 = p0->field_1190;
    callee_1e41d8(v102, a33, v103);
    Node28b238_v100* v105 = p0->field_1180;
    int v106 = p0->field_1194;
    callee_1e41d8(v105, a51, v106);
    Node28b238_v108* v108 = p0->field_20;
    void* v109 = v108->field_18;
    Node28b238_v23* v110 = p0->field_0;
    Node28b238_v24* v111 = v110->field_18;
    float v112 = v111->field_48;
    callee_1e4570(v109, v112);
    Node28b238_v114* v114 = p0->field_30;
    void* v115 = v114->field_18;
    Node28b238_v23* v116 = p0->field_0;
    Node28b238_v24* v117 = v116->field_18;
    float v118 = v117->field_48;
    callee_1e4570(v115, v118);
    Node28b238_v120* v120 = p0->field_28;
    void* v121 = v120->field_18;
    Node28b238_v23* v122 = p0->field_0;
    Node28b238_v24* v123 = v122->field_18;
    float v124 = v123->field_48;
    callee_1e4570(v121, v124);
    Node28b238_v126* v126 = p0->field_38;
    void* v127 = v126->field_18;
    Node28b238_v23* v128 = p0->field_0;
    Node28b238_v24* v129 = v128->field_18;
    float v130 = v129->field_48;
    int c131 = callee_1e4570(v127, v130);
    return c131;
}

int callee_20341c(int, int);        // 0x710020341c
int callee_204728();        // 0x7100204728
void* callee_2184d4(int);        // 0x71002184d4
void callee_30e5f8(long);        // 0x710030e5f8
void callee_30e708(long);        // 0x710030e708
int callee2_37cd30(long, float, float, float);        // 0x710037cd30
void callee_38cc40(long, void*);        // 0x710038cc40
void callee_38cff0(void*, long, int);        // 0x710038cff0
void callee_38dc8c(void*, long);        // 0x710038dc8c
int callee_3fa4a8(int);        // 0x71003fa4a8

struct Arg30eadc_0 {
    long field_0;                // +0
    unsigned char pad8[0x6e998];
    int field_6e9a0;                 // +6e9a0
};

struct Node30eadc_v56 {
    unsigned char pad0[0x10];
    void* field_10;               // +10
};

struct Elem30eadc_0 {
    unsigned char pad0[0x258];
    Node30eadc_v56* field_258;     // +258
    unsigned char pad260[0x2010];
};

struct Elem30eadc_1 {
    unsigned char pad0[0x250];
    int field_250;                 // +250
    unsigned char pad254[0x201c];
};
extern int gLocal8001b0_30eadc[] __attribute__((visibility("hidden")));    // 0x71008001b0
// Reached through the GOT slot at 0x7100c2ad38.
extern unsigned char gGlobalc2ad38_30eadc[];

// 0x710030eadc: the loop as a switch on its int index (cases 41, 46-48 skip a locked entry) with one copy of the panel setup, the message pointers typed as pointers
int call_30eadc(Arg30eadc_0* p0) {
    callee_38cff0(p0, 0, 0xb);
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2ad38_30eadc) + 0x10);
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x258));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x24c8));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4738));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x69a8));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x8c18));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xae88));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd0f8));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xf368));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x115d8));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x13848));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x15ab8));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x17d28));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x19f98));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1c208));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1e478));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x206e8));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x22958));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x24bc8));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x26e38));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x290a8));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2b318));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2d588));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2f7f8));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x31a68));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x33cd8));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x35f48));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x381b8));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3a428));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3c698));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3e908));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x40b78));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x42de8));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x45058));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x472c8));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x49538));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4b7a8));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4da18));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4fc88));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x51ef8));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x54168));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x563d8));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x58648));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5a8b8));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5cb28));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5ed98));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x61008));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x63278));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x654e8));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x67758));
    callee_30e5f8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x699c8));
    callee_30e708(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x6bc38));
    p0->field_6e9a0 = -1;
    int r52 = 0;
    int v54;
    int m91;
    int m79;
    int c55;
    int m67;
    Node30eadc_v56* v56;
    void* v57;
    int c59;
    int c60;
    int m63;
    int m64;
    int c61;
    int c62;
    Node30eadc_v56* v68;
    void* v69;
    int c71;
    int c72;
    int m75;
    int m76;
    int c73;
    int c74;
    Node30eadc_v56* v80;
    void* v81;
    int c83;
    int c84;
    void* m87;
    void* m88;
    void* c85;
    void* c86;
    for (int i = 0; i < 0x32; i++) {
        v54 = gLocal8001b0_30eadc[i];
        switch (i) {
        case 0x29:
        case 0x2e:
        case 0x2f:
        case 0x30:
            if ((callee_3fa4a8(v54) & 0xff) == 0)
                continue;
            break;
        }
        v80 = reinterpret_cast<Elem30eadc_0*>(p0)[static_cast<long>(static_cast<int>(r52))].field_258;
        v81 = v80->field_10;
        reinterpret_cast<void (*)(long, int)>(v81)(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + (static_cast<long>(static_cast<int>(r52)) * 0x2270) + 0x258), r52);
        reinterpret_cast<Elem30eadc_1*>(reinterpret_cast<unsigned char*>(p0) + static_cast<long>(static_cast<long>(static_cast<int>(r52))) * 0x2270 + 0x2270)->field_250 = v54;
        c83 = callee_204728();
        c84 = callee_20341c(c83, v54);
        if ((c84 & 0xff) != 0) {
        c85 = callee_2184d4(v54);
        m87 = c85;
        m88 = c85;
        } else {
        c86 = callee_217d64(0x8a);
        m87 = c86;
        m88 = c86;
        }
        callee_38cc40(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + (static_cast<long>(static_cast<int>(r52)) * 0x2270) + 0x258), m87);
        callee_38dc8c(p0, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + (static_cast<long>(static_cast<int>(r52)) * 0x2270) + 0x258));
        r52++;
    }
    return callee2_37cd30(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x228), -216.0f, 412.0f, 8.4e+02f);
}

int callee2_20341c(int, int);        // 0x710020341c
void callee_38cff0(void*, void*, int);        // 0x710038cff0
void callee_397378(long);        // 0x7100397378
void callee_397488(long);        // 0x7100397488

struct Arg397750_0 {
    long field_0;                // +0
    unsigned char pad8[0x6e998];
    int field_6e9a0;                 // +6e9a0
};

struct Node397750_v56 {
    unsigned char pad0[0x10];
    void* field_10;               // +10
};

struct Elem397750_0 {
    unsigned char pad0[0x258];
    Node397750_v56* field_258;     // +258
    unsigned char pad260[0x2010];
};

struct Elem397750_1 {
    unsigned char pad0[0x250];
    int field_250;                 // +250
    unsigned char pad254[0x201c];
};
extern int gLocal80347c_397750[] __attribute__((visibility("hidden")));    // 0x710080347c
// Reached through the GOT slot at 0x7100c2b230.
extern unsigned char gGlobalc2b230_397750[];

// 0x7100397750: the loop as a switch on its int index (cases 41, 46-48 skip a locked entry) with one copy of the panel setup, the message pointers typed as pointers
int call_397750(Arg397750_0* p0, void* p1) {
    callee_38cff0(p0, p1, 0xb);
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2b230_397750) + 0x10);
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x258));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x24c8));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4738));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x69a8));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x8c18));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xae88));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd0f8));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xf368));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x115d8));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x13848));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x15ab8));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x17d28));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x19f98));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1c208));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1e478));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x206e8));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x22958));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x24bc8));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x26e38));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x290a8));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2b318));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2d588));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2f7f8));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x31a68));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x33cd8));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x35f48));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x381b8));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3a428));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3c698));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3e908));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x40b78));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x42de8));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x45058));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x472c8));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x49538));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4b7a8));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4da18));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4fc88));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x51ef8));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x54168));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x563d8));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x58648));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5a8b8));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5cb28));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5ed98));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x61008));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x63278));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x654e8));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x67758));
    callee_397378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x699c8));
    callee_397488(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x6bc38));
    p0->field_6e9a0 = -1;
    int r52 = 0;
    int v54;
    int m91;
    int m79;
    int c55;
    int m67;
    Node397750_v56* v56;
    void* v57;
    int c59;
    int c60;
    int m63;
    int m64;
    int c61;
    int c62;
    Node397750_v56* v68;
    void* v69;
    int c71;
    int c72;
    int m75;
    int m76;
    int c73;
    int c74;
    Node397750_v56* v80;
    void* v81;
    int c83;
    int c84;
    void* m87;
    void* m88;
    void* c85;
    void* c86;
    for (int i = 0; i < 0x32; i++) {
        v54 = gLocal80347c_397750[i];
        switch (i) {
        case 0x29:
        case 0x2e:
        case 0x2f:
        case 0x30:
            if ((callee_3fa4a8(v54) & 0xff) == 0)
                continue;
            break;
        }
        v80 = reinterpret_cast<Elem397750_0*>(p0)[static_cast<long>(static_cast<int>(r52))].field_258;
        v81 = v80->field_10;
        reinterpret_cast<void (*)(long, int)>(v81)(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + (static_cast<long>(static_cast<int>(r52)) * 0x2270) + 0x258), r52);
        reinterpret_cast<Elem397750_1*>(reinterpret_cast<unsigned char*>(p0) + static_cast<long>(static_cast<long>(static_cast<int>(r52))) * 0x2270 + 0x2270)->field_250 = v54;
        c83 = callee_204728();
        c84 = callee2_20341c(c83, v54);
        if ((c84 & 0xff) != 0) {
        c85 = callee_2184d4(v54);
        m87 = c85;
        m88 = c85;
        } else {
        c86 = callee_217d64(0x8a);
        m87 = c86;
        m88 = c86;
        }
        callee_38cc40(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + (static_cast<long>(static_cast<int>(r52)) * 0x2270) + 0x258), m87);
        callee_38dc8c(p0, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + (static_cast<long>(static_cast<int>(r52)) * 0x2270) + 0x258));
        r52++;
    }
    return callee2_37cd30(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x228), -216.0f, 412.0f, 8.4e+02f);
}


class Node3e0624_v51 {
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
    virtual void slot_12(void*);
};

class Node3e0624_v44 {
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
    virtual void slot_12(void*);
};

class Node3e0624_v37 {
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
    virtual void slot_12(void*);
};

class Node3e0624_v30 {
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
    virtual void slot_12(void*);
};

class Node3e0624_v23 {
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
    virtual void slot_12(void*);
};

class Node3e0624_v16 {
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
    virtual void slot_12(void*);
};

class Node3e0624_v9 {
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
    virtual void slot_12(void*);
};

class Node3e0624_v2 {
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
    virtual void slot_12(void*);
};

struct Arg3e0624_0 {
    unsigned char pad0[0x1f0];
    long field_1f0;                // +1f0
    Node3e0624_v51* field_1f8;     // +1f8
    void* field_200;               // +200
    unsigned char pad208[0x818];
    void* field_a20;               // +a20
    unsigned char pada28[0x48];
    long field_a70;                // +a70
    Node3e0624_v44* field_a78;     // +a78
    void* field_a80;               // +a80
    unsigned char pada88[0x818];
    void* field_12a0;               // +12a0
    unsigned char pad12a8[0x48];
    long field_12f0;                // +12f0
    Node3e0624_v37* field_12f8;     // +12f8
    void* field_1300;               // +1300
    unsigned char pad1308[0x818];
    void* field_1b20;               // +1b20
    unsigned char pad1b28[0x48];
    long field_1b70;                // +1b70
    Node3e0624_v30* field_1b78;     // +1b78
    void* field_1b80;               // +1b80
    unsigned char pad1b88[0x818];
    void* field_23a0;               // +23a0
    unsigned char pad23a8[0x48];
    long field_23f0;                // +23f0
    Node3e0624_v23* field_23f8;     // +23f8
    void* field_2400;               // +2400
    unsigned char pad2408[0x818];
    void* field_2c20;               // +2c20
    unsigned char pad2c28[0x48];
    long field_2c70;                // +2c70
    Node3e0624_v16* field_2c78;     // +2c78
    void* field_2c80;               // +2c80
    unsigned char pad2c88[0x818];
    void* field_34a0;               // +34a0
    unsigned char pad34a8[0x48];
    long field_34f0;                // +34f0
    Node3e0624_v9* field_34f8;      // +34f8
    void* field_3500;               // +3500
    unsigned char pad3508[0x818];
    void* field_3d20;               // +3d20
    unsigned char pad3d28[0x48];
    long field_3d70;                // +3d70
    Node3e0624_v2* field_3d78;      // +3d78
    void* field_3d80;               // +3d80
    unsigned char pad3d88[0x818];
    void* field_45a0;               // +45a0
};
// Reached through the GOT slot at 0x7100c2b670.
extern unsigned char gGlobalc2b670_3e0624[];
// Reached through the GOT slot at 0x7100c2b678.
extern unsigned char gGlobalc2b678_3e0624[];

// 0x71003e0624: each member's vtable store before its pointer is read (generated source)
int call_3e0624(Arg3e0624_0* p0) {
    long a1 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3d70);
    p0->field_3d70 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2b670_3e0624) + 0x10);
    void* v0 = p0->field_3d80;
    if (v0 != 0) {
        Node3e0624_v2* v2 = p0->field_3d78;
        v2->slot_12(v0);
        p0->field_3d80 = nullptr;
        p0->field_45a0 = nullptr;
    }
    callee_58ce50(a1);
    long a8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x34f0);
    p0->field_34f0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2b670_3e0624) + 0x10);
    void* v7 = p0->field_3500;
    if (v7 != 0) {
        Node3e0624_v9* v9 = p0->field_34f8;
        v9->slot_12(v7);
        p0->field_3500 = nullptr;
        p0->field_3d20 = nullptr;
    }
    callee_58ce50(a8);
    long a15 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x2c70);
    p0->field_2c70 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2b670_3e0624) + 0x10);
    void* v14 = p0->field_2c80;
    if (v14 != 0) {
        Node3e0624_v16* v16 = p0->field_2c78;
        v16->slot_12(v14);
        p0->field_2c80 = nullptr;
        p0->field_34a0 = nullptr;
    }
    callee_58ce50(a15);
    long a22 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x23f0);
    p0->field_23f0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2b670_3e0624) + 0x10);
    void* v21 = p0->field_2400;
    if (v21 != 0) {
        Node3e0624_v23* v23 = p0->field_23f8;
        v23->slot_12(v21);
        p0->field_2400 = nullptr;
        p0->field_2c20 = nullptr;
    }
    callee_58ce50(a22);
    long a29 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1b70);
    p0->field_1b70 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2b678_3e0624) + 0x10);
    void* v28 = p0->field_1b80;
    if (v28 != 0) {
        Node3e0624_v30* v30 = p0->field_1b78;
        v30->slot_12(v28);
        p0->field_1b80 = nullptr;
        p0->field_23a0 = nullptr;
    }
    callee_58ce50(a29);
    long a36 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x12f0);
    p0->field_12f0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2b678_3e0624) + 0x10);
    void* v35 = p0->field_1300;
    if (v35 != 0) {
        Node3e0624_v37* v37 = p0->field_12f8;
        v37->slot_12(v35);
        p0->field_1300 = nullptr;
        p0->field_1b20 = nullptr;
    }
    callee_58ce50(a36);
    long a43 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xa70);
    p0->field_a70 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2b678_3e0624) + 0x10);
    void* v42 = p0->field_a80;
    if (v42 != 0) {
        Node3e0624_v44* v44 = p0->field_a78;
        v44->slot_12(v42);
        p0->field_a80 = nullptr;
        p0->field_12a0 = nullptr;
    }
    callee_58ce50(a43);
    long a50 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1f0);
    p0->field_1f0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2b678_3e0624) + 0x10);
    void* v49 = p0->field_200;
    if (v49 != 0) {
        Node3e0624_v51* v51 = p0->field_1f8;
        v51->slot_12(v49);
        p0->field_200 = nullptr;
        p0->field_a20 = nullptr;
    }
    return callee_58ce50(a50);
}

int callee2_59583c(void*);        // 0x710059583c

class Node220870_v0 {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();

    int field_8;                 // +8
};

struct Arg220870_0 {
    long field_0;                // +0
    unsigned char pad8[0x38];
    void* field_40;               // +40
    Node220870_v0* field_48;      // +48
};

class Node220870_v7 {
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
    virtual void slot_12(void*);
};

struct Node220870_v5 {
    unsigned char pad0[0x48];
    Node220870_v7* field_48;      // +48
    int field_50;                 // +50
};
// Reached through the GOT slot at 0x7100c23450.
extern Node220870_v5* gGlobalc23450_220870;
// Reached through the GOT slot at 0x7100c23448.
extern unsigned char gGlobalc23448_220870[];

// 0x7100220870: the member's vtable store before its pointer is read (generated source; its inventory size corrected in 0bba5b9)
int call_220870(Arg220870_0* p0) {
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc23448_220870) + 0x10);
    Node220870_v0* v0 = p0->field_48;
    p0->field_40 = nullptr;
    if (v0 != 0) {
        int v1 = v0->field_8;
        v0->field_8 = v1 - 1;
        if ((v1 - 1) == 0) {
            v0->slot_3();
        }
        p0->field_48 = nullptr;
    }
    Node220870_v5* v5 = gGlobalc23450_220870;
    if (v5 != 0) {
        int v6 = v5->field_50;
        v5->field_50 = v6 - 1;
        if ((v6 - 1) == 0) {
            Node220870_v7* v7 = v5->field_48;
            if (v7 != 0) {
                v7->slot_12(v5);
            }
        }
        gGlobalc23450_220870 = nullptr;
    }
    return callee2_59583c(p0);
}
