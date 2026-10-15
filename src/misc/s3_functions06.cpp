// Large functions from generated source, fixed by hand (third session). Struct, field and callee names are
// placeholders after the address and offset, as in the generated units. Status: matching/README.md.

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
    LayoutFrame();                                                         // 0x71001f0140
    unsigned char pad[0x88];
};

class Obj1f10f4 {
public:
    Obj1f10f4();                                                           // 0x71001f10f4
    unsigned char pad[0x68];
};

class Obj2d6c5c {
public:
    Obj2d6c5c();                                                           // 0x71002d6c5c
    unsigned char pad[0x1c8];
};

class Obj2f2370 {
public:
    Obj2f2370();                                                           // 0x71002f2370
    unsigned char pad[0x1aeb0];
};

class Obj316f8c {
public:
    Obj316f8c();                                                           // 0x7100316f8c
    unsigned char pad[0x15650];
};

class Obj350f50 {
public:
    Obj350f50();                                                           // 0x7100350f50
    unsigned char pad[0x968];
};

// 0x7100351428: the sub-object at +5b310 clears +5b350 (16 bytes) and then +5b318 (7 bytes) with memset in its constructor body, which Clang lowers to the two reversed store groups
class Class351428 {
public:
    Class351428(void* p1);
    virtual void v00();

    int f8;
    int fc;
    void* f10;
    void* f18;
    void* f20;
    void* f28;
    void* f30;
    void* f38;
    unsigned char pad40[0x40];
    void* f80;
    LayoutFrame m88;
    LayoutFrame m110;
    LayoutFrame m198;
    LayoutFrame m220;
    LayoutFrame m2a8;
    LayoutFrame m330;
    LayoutFrame m3b8;
    LayoutFrame m440;
    LayoutFrame m4c8;
    LayoutFrame m550;
    LayoutFrame m5d8;
    LayoutFrame m660;
    LayoutFrame m6e8;
    LayoutFrame m770;
    LayoutFrame m7f8;
    LayoutFrame m880;
    LayoutFrame m908;
    LayoutFrame m990;
    LayoutFrame ma18;
    LayoutFrame maa0;
    LayoutFrame mb28;
    LayoutFrame mbb0;
    LayoutFrame mc38;
    LayoutFrame mcc0;
    LayoutFrame md48;
    LayoutFrame mdd0;
    LayoutFrame me58;
    LayoutFrame mee0;
    LayoutFrame mf68;
    LayoutFrame mff0;
    LayoutFrame m1078;
    LayoutFrame m1100;
    LayoutFrame m1188;
    LayoutFrame m1210;
    LayoutFrame m1298;
    LayoutFrame m1320;
    LayoutFrame m13a8;
    LayoutFrame m1430;
    LayoutFrame m14b8;
    LayoutFrame m1540;
    LayoutFrame m15c8;
    LayoutFrame m1650;
    LayoutFrame m16d8;
    LayoutFrame m1760;
    LayoutFrame m17e8;
    LayoutFrame m1870;
    LayoutFrame m18f8;
    LayoutFrame m1980;
    LayoutFrame m1a08;
    LayoutFrame m1a90;
    LayoutFrame m1b18;
    LayoutFrame m1ba0;
    LayoutFrame m1c28;
    LayoutFrame m1cb0;
    LayoutFrame m1d38;
    LayoutFrame m1dc0;
    LayoutFrame m1e48;
    LayoutFrame m1ed0;
    LayoutFrame m1f58;
    LayoutFrame m1fe0;
    LayoutFrame m2068;
    LayoutFrame m20f0;
    LayoutFrame m2178;
    LayoutFrame m2200;
    LayoutFrame a2288[320];
    LayoutFrame acc88[256];
    LayoutFrame m15488;
    LayoutFrame m15510;
    LayoutFrame m15598;
    LayoutFrame m15620;
    LayoutFrame m156a8;
    LayoutFrame m15730;
    LayoutFrame m157b8;
    LayoutFrame m15840;
    LayoutFrame m158c8;
    LayoutFrame m15950;
    LayoutFrame m159d8;
    LayoutFrame m15a60;
    LayoutFrame m15ae8;
    LayoutFrame m15b70;
    LayoutFrame m15bf8;
    LayoutFrame m15c80;
    LayoutFrame m15d08;
    LayoutFrame m15d90;
    LayoutFrame m15e18;
    LayoutFrame m15ea0;
    LayoutFrame m15f28;
    LayoutFrame m15fb0;
    LayoutFrame m16038;
    LayoutFrame m160c0;
    LayoutFrame m16148;
    LayoutFrame m161d0;
    LayoutFrame m16258;
    LayoutFrame m162e0;
    LayoutFrame m16368;
    LayoutFrame m163f0;
    LayoutFrame m16478;
    LayoutFrame m16500;
    LayoutFrame m16588;
    LayoutFrame m16610;
    LayoutFrame m16698;
    LayoutFrame m16720;
    LayoutFrame m167a8;
    LayoutFrame m16830;
    LayoutFrame m168b8;
    LayoutFrame m16940;
    LayoutFrame m169c8;
    LayoutFrame m16a50;
    LayoutFrame m16ad8;
    LayoutFrame m16b60;
    LayoutFrame m16be8;
    LayoutFrame m16c70;
    LayoutFrame m16cf8;
    LayoutFrame m16d80;
    LayoutFrame m16e08;
    LayoutFrame m16e90;
    LayoutFrame m16f18;
    LayoutFrame m16fa0;
    LayoutFrame m17028;
    LayoutFrame m170b0;
    LayoutFrame m17138;
    LayoutFrame m171c0;
    LayoutFrame m17248;
    LayoutFrame m172d0;
    LayoutFrame m17358;
    LayoutFrame m173e0;
    LayoutFrame m17468;
    LayoutFrame m174f0;
    LayoutFrame m17578;
    LayoutFrame m17600;
    LayoutFrame m17688;
    LayoutFrame m17710;
    LayoutFrame m17798;
    LayoutFrame m17820;
    LayoutFrame m178a8;
    LayoutFrame m17930;
    LayoutFrame m179b8;
    LayoutFrame m17a40;
    LayoutFrame m17ac8;
    LayoutFrame m17b50;
    LayoutFrame m17bd8;
    LayoutFrame m17c60;
    LayoutFrame m17ce8;
    LayoutFrame m17d70;
    LayoutFrame m17df8;
    LayoutFrame m17e80;
    LayoutFrame m17f08;
    LayoutFrame m17f90;
    LayoutFrame m18018;
    LayoutFrame m180a0;
    LayoutFrame m18128;
    LayoutFrame m181b0;
    LayoutFrame m18238;
    LayoutFrame m182c0;
    LayoutFrame m18348;
    LayoutFrame m183d0;
    LayoutFrame m18458;
    LayoutFrame m184e0;
    LayoutFrame m18568;
    LayoutFrame m185f0;
    LayoutFrame m18678;
    LayoutFrame m18700;
    LayoutFrame m18788;
    LayoutFrame m18810;
    LayoutFrame m18898;
    LayoutFrame m18920;
    LayoutFrame m189a8;
    LayoutFrame m18a30;
    LayoutFrame m18ab8;
    LayoutFrame m18b40;
    LayoutFrame m18bc8;
    LayoutFrame m18c50;
    LayoutFrame m18cd8;
    LayoutFrame m18d60;
    LayoutFrame m18de8;
    LayoutFrame m18e70;
    LayoutFrame m18ef8;
    LayoutFrame m18f80;
    LayoutFrame m19008;
    LayoutFrame m19090;
    LayoutFrame m19118;
    LayoutFrame m191a0;
    LayoutFrame m19228;
    LayoutFrame m192b0;
    LayoutFrame m19338;
    LayoutFrame m193c0;
    LayoutFrame m19448;
    LayoutFrame m194d0;
    LayoutFrame m19558;
    LayoutFrame m195e0;
    LayoutFrame m19668;
    LayoutFrame m196f0;
    LayoutFrame m19778;
    LayoutFrame m19800;
    LayoutFrame a19888[128];
    LayoutFrame a1dc88[128];
    LayoutFrame m22088;
    LayoutFrame m22110;
    LayoutFrame m22198;
    LayoutFrame m22220;
    LayoutFrame m222a8;
    LayoutFrame m22330;
    LayoutFrame m223b8;
    LayoutFrame m22440;
    LayoutFrame m224c8;
    LayoutFrame m22550;
    LayoutFrame m225d8;
    LayoutFrame m22660;
    LayoutFrame m226e8;
    LayoutFrame m22770;
    LayoutFrame m227f8;
    LayoutFrame m22880;
    LayoutFrame m22908;
    LayoutFrame m22990;
    LayoutFrame m22a18;
    LayoutFrame m22aa0;
    LayoutFrame m22b28;
    LayoutFrame m22bb0;
    LayoutFrame m22c38;
    LayoutFrame m22cc0;
    LayoutFrame m22d48;
    LayoutFrame m22dd0;
    LayoutFrame m22e58;
    LayoutFrame m22ee0;
    LayoutFrame m22f68;
    LayoutFrame m22ff0;
    LayoutFrame m23078;
    LayoutFrame m23100;
    LayoutFrame m23188;
    LayoutFrame m23210;
    LayoutFrame m23298;
    LayoutFrame m23320;
    LayoutFrame m233a8;
    LayoutFrame m23430;
    LayoutFrame m234b8;
    LayoutFrame m23540;
    LayoutFrame m235c8;
    LayoutFrame m23650;
    LayoutFrame m236d8;
    LayoutFrame m23760;
    LayoutFrame m237e8;
    LayoutFrame m23870;
    LayoutFrame m238f8;
    LayoutFrame m23980;
    LayoutFrame m23a08;
    LayoutFrame m23a90;
    LayoutFrame m23b18;
    LayoutFrame m23ba0;
    LayoutFrame m23c28;
    LayoutFrame m23cb0;
    LayoutFrame m23d38;
    LayoutFrame m23dc0;
    LayoutFrame m23e48;
    LayoutFrame m23ed0;
    LayoutFrame m23f58;
    LayoutFrame m23fe0;
    LayoutFrame m24068;
    LayoutFrame m240f0;
    LayoutFrame m24178;
    LayoutFrame m24200;
    Obj350f50 m24288;
    Obj350f50 m24bf0;
    Obj350f50 m25558;
    Obj350f50 m25ec0;
    Obj350f50 m26828;
    Obj350f50 m27190;
    Obj350f50 m27af8;
    Obj350f50 m28460;
    Obj350f50 m28dc8;
    Obj350f50 m29730;
    Obj350f50 m2a098;
    Obj1f10f4 m2aa00;
    Obj1f10f4 m2aa68;
    Obj1f10f4 m2aad0;
    Obj1f10f4 m2ab38;
    Obj1f10f4 m2aba0;
    unsigned char pad2ac08[0x28];
    LayoutHandle h2ac30;
    Obj2d6c5c m2ac48;
    Obj2f2370 m2ae10;
    Obj316f8c m45cc0;
    struct Sub {
        int f5b310;
        unsigned char f5b314;
        unsigned char f5b315;
        unsigned char f5b316;
        int f5b318;
        unsigned short f5b31c;
        unsigned char f5b31e;
        int f5b320;
        int f5b324;
        unsigned char pad5b328[0x8];
        void* f5b330;
        unsigned char pad5b338[0x18];
        void* f5b350;
        void* f5b358;
        Sub() : f5b310(6), f5b314(0), f5b315(0), f5b316(0), f5b320(0), f5b324(0), f5b330(nullptr) {
            __builtin_memset(&f5b350, 0, 16); __builtin_memset(&f5b318, 0, 7);
        }
    } sub5b310;
    LayoutHandle h5b360;
    unsigned short f5b378;
    unsigned char pad5b37a[0x6];
    void* f5b380;
    void* f5b388;
    int f5b390;
    unsigned char pad5b394[0x4];
    LayoutHandle h5b398;
    LayoutHandle h5b3b0;
    LayoutHandle h5b3c8;
    int f5b3e0;
    unsigned char pad5b3e4[0x4];
    void* f5b3e8;
    unsigned char pad5b3f0[0x18];
    int f5b408;
    unsigned char pad5b40c[0x4];
    void* f5b410;
    unsigned char pad5b418[0x18];
    int f5b430;
    unsigned char pad5b434[0x4];
    void* f5b438;
    unsigned char pad5b440[0x18];
    int f5b458;
    unsigned char pad5b45c[0x4];
    void* f5b460;
    unsigned char pad5b468[0x18];
    int f5b480;
    unsigned char pad5b484[0x4];
    void* f5b488;
    unsigned char pad5b490[0x18];
    int f5b4a8;
    unsigned char pad5b4ac[0x4];
    void* f5b4b0;
    unsigned char pad5b4b8[0x18];
    int f5b4d0;
    unsigned char pad5b4d4[0x4];
    void* f5b4d8;
    unsigned char pad5b4e0[0x18];
    int f5b4f8;
    unsigned char pad5b4fc[0x4];
    void* f5b500;
    unsigned char pad5b508[0x18];
    int f5b520;
    unsigned char pad5b524[0x4];
    void* f5b528;
    unsigned char pad5b530[0x18];
    int f5b548;
    unsigned char pad5b54c[0x4];
    void* f5b550;
    unsigned char pad5b558[0x18];
    int f5b570;
    unsigned char pad5b574[0x4];
    void* f5b578;
    unsigned char pad5b580[0x18];
    long f5b598;
    long f5b5a0;
    long f5b5a8;
    long f5b5b0;
    long f5b5b8;
    long f5b5c0;
    long f5b5c8;
    int f5b5d0;
};

Class351428::Class351428(void* p1)
    : f8(4), fc(2), f10(p1), f18(nullptr), f20(nullptr), f28(nullptr), f30(nullptr), f38(nullptr), f80(nullptr), f5b378(0), f5b380(nullptr), f5b388(nullptr), f5b390(0), f5b3e0(0), f5b3e8(nullptr), f5b408(0), f5b410(nullptr), f5b430(0), f5b438(nullptr), f5b458(0), f5b460(nullptr), f5b480(0), f5b488(nullptr), f5b4a8(0), f5b4b0(nullptr), f5b4d0(0), f5b4d8(nullptr), f5b4f8(0), f5b500(nullptr), f5b520(0), f5b528(nullptr), f5b548(0), f5b550(nullptr), f5b570(0), f5b578(nullptr), f5b598(-1), f5b5a0(-1), f5b5a8(-1), f5b5b0(-1), f5b5b8(-1), f5b5c0(-1), f5b5c8(-1), f5b5d0(-1) {}
