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
