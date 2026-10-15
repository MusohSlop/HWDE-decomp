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
