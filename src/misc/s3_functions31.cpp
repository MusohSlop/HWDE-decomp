// Constructors converted from generated source by tools/s3/ctor2class.py (third session): one-argument calls on
// this+off as members, element loops as member arrays, layout handles from their stores, a no-argument call at +0 as
// the polymorphic base, and stores after a later member as body statements. Names are placeholders. Status:
// matching/README.md.

class LayoutFrame {
public:
    LayoutFrame();                                                       // 0x71001f0140
    unsigned char pad[0x88];
};

class MenuCursor {
public:
    MenuCursor();                                                        // 0x710037f550
    unsigned char pad[0x30];
};

class Obj31ce68 {
public:
    Obj31ce68();                                                         // 0x710031ce68
    unsigned char pad[0x2530];
};

class Base316a64_40 {
public:
    Base316a64_40();                                                     // 0x7100316a64
    virtual ~Base316a64_40();
    unsigned char pad8[0x38];
};

class Class31a1e0 : public Base316a64_40 {
public:
    Class31a1e0();
    virtual void v00();

    int f40;
    unsigned char pad44[0x4];
    int f48;
    int f4c;
    LayoutFrame a50[3808];
    unsigned char pad7e750[0x70];
    Obj31ce68 m7e7c0;
    Obj31ce68 m80cf0;
    Obj31ce68 m83220;
    Obj31ce68 m85750;
    Obj31ce68 m87c80;
    Obj31ce68 m8a1b0;
    Obj31ce68 m8c6e0;
    Obj31ce68 m8ec10;
    Obj31ce68 m91140;
    Obj31ce68 m93670;
    Obj31ce68 m95ba0;
    Obj31ce68 m980d0;
    Obj31ce68 m9a600;
    Obj31ce68 m9cb30;
    Obj31ce68 m9f060;
    Obj31ce68 ma1590;
    Obj31ce68 ma3ac0;
    Obj31ce68 ma5ff0;
    Obj31ce68 ma8520;
    Obj31ce68 maaa50;
    Obj31ce68 macf80;
    Obj31ce68 maf4b0;
    Obj31ce68 mb19e0;
    Obj31ce68 mb3f10;
    Obj31ce68 mb6440;
    Obj31ce68 mb8970;
    Obj31ce68 mbaea0;
    Obj31ce68 mbd3d0;
    Obj31ce68 mbf900;
    Obj31ce68 mc1e30;
    Obj31ce68 mc4360;
    Obj31ce68 mc6890;
    MenuCursor mc8dc0;
    void* fc8df0;
    void* fc8df8;
    unsigned char fc8e00;
};

// 0x710031a1e0
Class31a1e0::Class31a1e0()
    : f40(0), f48(2), f4c(-1), fc8df0(nullptr), fc8df8(nullptr), fc8e00(0) {}

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

class ScrollList {
public:
    ScrollList();                                                        // 0x71001f8700
    unsigned char pad[0xa0];
};

class Class37adf4 {
public:
    Class37adf4();

    long f0;
    int f8;
    unsigned char padc[0x4];
    void* f10;
    void* f18;
    void* f20;
    void* f28;
    void* f30;
    void* f38;
    void* f40;
    void* f48;
    void* f50;
    void* f58;
    void* f60;
    LayoutHandle h68;
    int f80;
    unsigned char pad84[0x4];
    void* f88;
    void* f90;
    void* f98;
    LayoutHandle ha0;
    LayoutHandle hb8;
    LayoutHandle hd0;
    LayoutHandle he8;
    ScrollList m100;
    int f1a0;
    unsigned char pad1a4[0x4];
    void* f1a8;
    void* f1b0;
    void* f1b8;
    LayoutHandle h1c0;
    LayoutHandle h1d8;
    LayoutHandle h1f0;
    LayoutHandle h208;
    ScrollList m220;
    int f2c0;
    unsigned char pad2c4[0x4];
    void* f2c8;
    void* f2d0;
    void* f2d8;
    LayoutHandle h2e0;
    LayoutHandle h2f8;
    LayoutHandle h310;
    LayoutHandle h328;
    ScrollList m340;
    int f3e0;
    unsigned char pad3e4[0x4];
    void* f3e8;
    void* f3f0;
    void* f3f8;
    LayoutHandle h400;
    LayoutHandle h418;
    LayoutHandle h430;
    LayoutHandle h448;
    ScrollList m460;
};

// 0x710037adf4
Class37adf4::Class37adf4()
    : f0(-1), f8(-1), f10(nullptr), f18(nullptr), f20(nullptr), f58(nullptr), f60(nullptr), f80(-1), f88(nullptr), f90(nullptr), f98(nullptr), f1a0(-1), f1a8(nullptr), f1b0(nullptr), f1b8(nullptr), f2c0(-1), f2c8(nullptr), f2d0(nullptr), f2d8(nullptr), f3e0(-1), f3e8(nullptr), f3f0(nullptr), f3f8(nullptr) {
    f48 = nullptr;
    f50 = nullptr;
    h68.id = -1;
    f38 = nullptr;
    f40 = nullptr;
    f28 = nullptr;
    f30 = nullptr;
}

// Layout handle; its vtable lives in the effect manager unit (GOT 0x7100c22f00).

class Obj37a514 {
public:
    Obj37a514();                                                         // 0x710037a514
    unsigned char pad[0x18];
};

class Class2dbe5c {
public:
    Class2dbe5c();
    virtual void v00();

    void* f8;
    void* f10;
    unsigned char z18[0x140];
    void* f158;
    LayoutHandle h160;
    LayoutHandle h178;
    LayoutHandle h190;
    LayoutHandle h1a8;
    LayoutHandle h1c0;
    LayoutHandle h1d8;
    LayoutHandle h1f0;
    LayoutHandle h208;
    LayoutHandle h220;
    LayoutHandle h238;
    void* f250;
    void* f258;
    int f260;
    unsigned char pad264[0x4];
    Obj37a514 m268;
    unsigned short f280;
};

// 0x71002dbe5c
Class2dbe5c::Class2dbe5c()
    : f8(nullptr), f10(nullptr), f158(nullptr), f280(0xff) {
    __builtin_memset(z18, 0, sizeof(z18));
    f260 = 0;
    f258 = nullptr;
    f250 = nullptr;
}

int callee_3e82b0(void*);        // 0x71003e82b0

struct Arg3edc2c_0 {
    long field_0;                // +0
    unsigned char pad8[0xc8];
    void* field_d0;               // +d0
    void* field_d8;               // +d8
    void* field_e0;               // +e0
    void* field_e8;               // +e8
    int field_f0;                 // +f0
    int field_f4;                 // +f4
    int field_f8;                 // +f8
    int field_fc;                 // +fc
    int field_100;                 // +100
    int field_104;                 // +104
    int field_108;                 // +108
    unsigned short field_10c;      // +10c
    unsigned char field_10e;       // +10e
};

struct Globalc216f8_3edc2c {
    unsigned char pad0[0x30];
    void* field_30;               // +30
    void* field_38;               // +38
};

struct alignas(8) Blk10_8_3edc2c {
    unsigned char b[16];
};
// Reached through the GOT slot at 0x7100c216f8.
extern Globalc216f8_3edc2c gGlobalc216f8_3edc2c;
// Reached through the GOT slot at 0x7100c2b6d0.
extern unsigned char gGlobalc2b6d0_3edc2c[];


class Base3e82b0_8 {
public:
    Base3e82b0_8();                                                      // 0x71003e82b0
    virtual ~Base3e82b0_8();
    unsigned char pad8[0x0];
};

class Class3edc2c : public Base3e82b0_8 {
public:
    Class3edc2c();
    virtual void v00();

};

// 0x71003edc2c: +f4 keeps its integer store, +fc and +100 are float stores (as integer stores, 64.0f would be derived
// from 40.0f's register and the +f8/+fc pair merged).
Class3edc2c::Class3edc2c() {
    Arg3edc2c_0* p0 = reinterpret_cast<Arg3edc2c_0*>(this);
    *reinterpret_cast<Blk10_8_3edc2c*>((reinterpret_cast<unsigned char*>(p0) + 0xc0)) = *reinterpret_cast<const Blk10_8_3edc2c*>((reinterpret_cast<unsigned char*>(&gGlobalc216f8_3edc2c) + 0x30));
    void* v1 = gGlobalc216f8_3edc2c.field_38;
    p0->field_d8 = v1;
    void* v2 = gGlobalc216f8_3edc2c.field_30;
    p0->field_f0 = 0;
    p0->field_f4 = 0x42200000;
    p0->field_f8 = 0;
    *reinterpret_cast<float*>(&p0->field_fc) = 64.0f;
    p0->field_e0 = nullptr;
    p0->field_e8 = nullptr;
    *reinterpret_cast<float*>(&p0->field_100) = 95000.0f;
    p0->field_104 = -1;
    p0->field_108 = 0;
    p0->field_d0 = v2;
    p0->field_10c = 0;
    p0->field_10e = 1;
}
