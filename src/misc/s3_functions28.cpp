// Hand fixes of generated source (third session): the generator's code with the original's statement order where a
// class boundary moves a store or an address is taken early. Names are placeholders after the address and offset. Status: matching/README.md.

extern "C" void* memset(void*, int, unsigned long);

void* callee_217d64(int);        // 0x7100217d64
void callee_33bbb4(long, int, int);        // 0x710033bbb4
void callee_5d2744(long);        // 0x71005d2744

struct Arg2defc0_0 {
    long field_0;                // +0
    unsigned char pad8[0x228];
    unsigned char field_230;       // +230
    unsigned char pad231[0x7];
    void* field_238;               // +238
    unsigned short field_240;      // +240
    unsigned char field_242;       // +242
    unsigned char pad243[0x1];
    int field_244;                 // +244
    unsigned char field_248;       // +248
    unsigned char pad249[0x3];
    int field_24c;                 // +24c
    unsigned short field_250;      // +250
    unsigned char field_252;       // +252
    unsigned char pad253[0x5];
    void* field_258;               // +258
    void* field_260;               // +260
    void* field_268;               // +268
    unsigned char field_270;       // +270
    unsigned char pad271[0xf];
    long field_280;                // +280
    unsigned char pad288[0x15498];
    void* field_15720;               // +15720
    void* field_15728;               // +15728
    void* field_15730;               // +15730
    void* field_15738;               // +15738
    void* field_15740;               // +15740
    void* field_15748;               // +15748
    void* field_15750;               // +15750
    void* field_15758;               // +15758
    void* field_15760;               // +15760
    void* field_15768;               // +15768
    void* field_15770;               // +15770
    void* field_15778;               // +15778
    void* field_15780;               // +15780
    void* field_15788;               // +15788
    void* field_15790;               // +15790
    void* field_15798;               // +15798
    void* field_157a0;               // +157a0
    void* field_157a8;               // +157a8
    void* field_157b0;               // +157b0
    void* field_157b8;               // +157b8
    void* field_157c0;               // +157c0
    void* field_157c8;               // +157c8
    void* field_157d0;               // +157d0
    void* field_157d8;               // +157d8
    void* field_157e0;               // +157e0
    void* field_157e8;               // +157e8
    void* field_157f0;               // +157f0
    unsigned char pad157f8[0x10];
    void* field_15808;               // +15808
    long field_15810;                // +15810
    long field_15818;                // +15818
    unsigned short field_15820;      // +15820
    unsigned short field_15822;      // +15822
    unsigned char pad15824[0x104];
    long field_15928;                // +15928
    long field_15930;                // +15930
    unsigned short field_15938;      // +15938
    unsigned short field_1593a;      // +1593a
    unsigned char pad1593c[0x4];
    long field_15940;                // +15940
    long field_15948;                // +15948
    unsigned short field_15950;      // +15950
    unsigned short field_15952;      // +15952
    unsigned char pad15954[0x4];
    long field_15958;                // +15958
    long field_15960;                // +15960
    unsigned short field_15968;      // +15968
    unsigned short field_1596a;      // +1596a
    unsigned char pad1596c[0x4];
    long field_15970;                // +15970
    long field_15978;                // +15978
    unsigned short field_15980;      // +15980
    unsigned short field_15982;      // +15982
    unsigned char pad15984[0x4];
    long field_15988;                // +15988
    long field_15990;                // +15990
    unsigned short field_15998;      // +15998
    unsigned short field_1599a;      // +1599a
    unsigned char pad1599c[0x4];
    long field_159a0;                // +159a0
    long field_159a8;                // +159a8
    unsigned short field_159b0;      // +159b0
    unsigned short field_159b2;      // +159b2
    unsigned char pad159b4[0x4];
    long field_159b8;                // +159b8
    long field_159c0;                // +159c0
    unsigned short field_159c8;      // +159c8
    unsigned short field_159ca;      // +159ca
};
// Reached through the GOT slot at 0x7100c2abb0.
extern unsigned char gGlobalc2abb0_2defc0[];
// Reached through the GOT slot at 0x7100c2abb8.
extern unsigned char gGlobalc2abb8_2defc0[];
// Reached through the GOT slot at 0x7100c2abc0.
extern unsigned char gGlobalc2abc0_2defc0[];
// Reached through the GOT slot at 0x7100c22f00.
extern unsigned char gGlobalc22f00_2defc0[];

// 0x71002defc0: the derived vtable store (GOT 0x7100c2abb8) comes right after the owner at +238, where the base
// ends; the generator put it after the base's last field.
void* call_2defc0(Arg2defc0_0* p0, void* p1) {
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2abb0_2defc0) + 0x10);
    callee_5d2744(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x10));
    callee_5d2744(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x120));
    p0->field_230 = 0;
    p0->field_238 = p1;
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2abb8_2defc0) + 0x10);
    p0->field_240 = 0;
    p0->field_242 = 0;
    p0->field_244 = 0;
    p0->field_24c = 0;
    p0->field_248 = 0;
    p0->field_270 = 0;
    callee_33bbb4(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x280), 0, 0x41ea);
    p0->field_280 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2abc0_2defc0) + 0x10);
    p0->field_15808 = nullptr;
    p0->field_15738 = nullptr;
    p0->field_15730 = nullptr;
    p0->field_15728 = nullptr;
    p0->field_15720 = nullptr;
    p0->field_15768 = nullptr;
    p0->field_15760 = nullptr;
    p0->field_15758 = nullptr;
    p0->field_157b8 = nullptr;
    p0->field_157b0 = nullptr;
    p0->field_157a8 = nullptr;
    p0->field_157a0 = nullptr;
    p0->field_157f0 = nullptr;
    p0->field_157e8 = nullptr;
    p0->field_157e0 = nullptr;
    p0->field_157d8 = nullptr;
    p0->field_15818 = -1;
    p0->field_15820 = 0;
    p0->field_15822 = 0;
    p0->field_15810 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc22f00_2defc0) + 0x10);
    p0->field_15930 = -1;
    p0->field_15938 = 0;
    p0->field_1593a = 0;
    p0->field_15928 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc22f00_2defc0) + 0x10);
    p0->field_15948 = -1;
    p0->field_15950 = 0;
    p0->field_15952 = 0;
    p0->field_15940 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc22f00_2defc0) + 0x10);
    p0->field_15960 = -1;
    p0->field_15968 = 0;
    p0->field_1596a = 0;
    p0->field_15958 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc22f00_2defc0) + 0x10);
    p0->field_15978 = -1;
    p0->field_15980 = 0;
    p0->field_15982 = 0;
    p0->field_15970 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc22f00_2defc0) + 0x10);
    p0->field_15990 = -1;
    p0->field_15998 = 0;
    p0->field_1599a = 0;
    p0->field_15988 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc22f00_2defc0) + 0x10);
    p0->field_159a8 = -1;
    p0->field_159b0 = 0;
    p0->field_159b2 = 0;
    p0->field_159a0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc22f00_2defc0) + 0x10);
    p0->field_159c0 = -1;
    p0->field_159c8 = 0;
    p0->field_159ca = 0;
    p0->field_159b8 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc22f00_2defc0) + 0x10);
    p0->field_252 = 0;
    p0->field_250 = 0;
    p0->field_15750 = nullptr;
    p0->field_15748 = nullptr;
    p0->field_15740 = nullptr;
    p0->field_15798 = nullptr;
    p0->field_15790 = nullptr;
    p0->field_15788 = nullptr;
    p0->field_15780 = nullptr;
    p0->field_15778 = nullptr;
    p0->field_15770 = nullptr;
    p0->field_157d0 = nullptr;
    p0->field_157c8 = nullptr;
    p0->field_157c0 = nullptr;
    void* c3 = callee_217d64(0xdd);
    p0->field_258 = c3;
    void* c4 = callee_217d64(0xde);
    p0->field_260 = c4;
    void* c5 = callee_217d64(0xdf);
    p0->field_268 = c5;
    return c5;
}

int callee_4a3d34(void*);        // 0x71004a3d34
void callee_4b24b4(long, int);        // 0x71004b24b4

struct Node4c8b04_v0 {
    unsigned char pad0[0x10];
    int field_10;                 // +10
    unsigned char pad14[0xc];
    int field_20;                 // +20
};

class Node4c8b04_v15 {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();

    int field_8;                 // +8
};

class Node4c8b04_v20 {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();

    int field_8;                 // +8
};

class Node4c8b04_v25 {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();

    int field_8;                 // +8
};

class Node4c8b04_v30 {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();

    int field_8;                 // +8
};

class Node4c8b04_v35 {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();

    int field_8;                 // +8
};

struct Arg4c8b04_0 {
    long field_0;                // +0
    void* field_8;               // +8
    unsigned char pad10[0x70];
    Node4c8b04_v0* field_80;      // +80
    Node4c8b04_v15* field_88;     // +88
    Node4c8b04_v20* field_90;     // +90
    Node4c8b04_v25* field_98;     // +98
    Node4c8b04_v30* field_a0;     // +a0
    Node4c8b04_v35* field_a8;     // +a8
};

struct Addr4c8b04_0 {
    int field_0;                 // +0
};

struct Addr4c8b04_1 {
    unsigned char pad0[0x4];
    int field_4;                 // +4
    unsigned char pad8[0x158];
    void* field_160;               // +160
};

struct Elem4c8b04_0 {
    unsigned char pad0[0x100];
    void* field_100;               // +100
    void* field_108;               // +108
    unsigned char pad110[0xf0];
};

struct Node4c8b04_v10 {
    unsigned char field_0[1];    // +0
};

struct Addr4c8b04_2 {
    Node4c8b04_v10* field_0;     // +0
};
// Reached through the GOT slot at 0x7100c2cdb0.
extern unsigned char gGlobalc2cdb0_4c8b04[];
// Reached through the GOT slot at 0x7100c2cce8.
extern unsigned char gGlobalc2cce8_4c8b04[];

// 0x71004c8b04 (D2): the table's relative offset is read through its own address and added to it as a char pointer,
// as the original does; the generator added two integers (the operands came out swapped).
int call_4c8b04(Arg4c8b04_0* p0) {
    Node4c8b04_v0* v0 = p0->field_80;
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc2cdb0_4c8b04) + 0x10);
    if (v0 != 0) {
        int v1 = v0->field_10;
        if (v1 != 0) {
            void* v2 = p0->field_8;
            unsigned int r3 = 0;
            int v4;
            int v5;
            int v7;
            void* v8;
            void* v9;
            void* m12;
            Node4c8b04_v10* v10;
            void* v11;
            int v14;
            do {
                v4 = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(v0) + 0x20);
                v5 = reinterpret_cast<Addr4c8b04_0*>(static_cast<long>(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v0) + 0x20 + static_cast<int>(v4)) + (static_cast<unsigned long>(static_cast<unsigned int>(r3)) << 2)))->field_0;
                callee_4b24b4((reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v0) + 0x20 + static_cast<int>(v4)) + (static_cast<unsigned long>(static_cast<unsigned int>(r3)) << 2)) + static_cast<long>(static_cast<int>(v5)), 1);
                v7 = reinterpret_cast<Addr4c8b04_1*>(static_cast<long>((reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v0) + 0x20 + static_cast<int>(v4)) + (static_cast<unsigned long>(static_cast<unsigned int>(r3)) << 2)) + static_cast<long>(static_cast<int>(v5))))->field_4;
                v8 = reinterpret_cast<Elem4c8b04_0*>(gGlobalc2cce8_4c8b04)[static_cast<long>(static_cast<int>(v7))].field_100;
                v9 = reinterpret_cast<Elem4c8b04_0*>(gGlobalc2cce8_4c8b04)[static_cast<long>(static_cast<int>(v7))].field_108;
                if ((reinterpret_cast<long>(v9) & 1) != 0) {
                    v10 = reinterpret_cast<Addr4c8b04_2*>(static_cast<long>(((reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v0) + 0x20 + static_cast<int>(v4)) + (static_cast<unsigned long>(static_cast<unsigned int>(r3)) << 2)) + static_cast<long>(static_cast<int>(v5))) + (reinterpret_cast<long>(v9) >> 1)))->field_0;
                    v11 = *reinterpret_cast<void**>(&v10->field_0[reinterpret_cast<long>(v8)]);
                    m12 = v11;
                } else {
                    m12 = v8;
                }
                reinterpret_cast<void (*)(long, void*)>(m12)(((reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v0) + 0x20 + static_cast<int>(v4)) + (static_cast<unsigned long>(static_cast<unsigned int>(r3)) << 2)) + static_cast<long>(static_cast<int>(v5))) + (reinterpret_cast<long>(v9) >> 1), v2);
                reinterpret_cast<Addr4c8b04_1*>(static_cast<long>((reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v0) + 0x20 + static_cast<int>(v4)) + (static_cast<unsigned long>(static_cast<unsigned int>(r3)) << 2)) + static_cast<long>(static_cast<int>(v5))))->field_160 = nullptr;
                v14 = v0->field_10;
                r3 = r3 + 1;
            } while (static_cast<unsigned int>(r3) < static_cast<unsigned int>(v14));
        }
    }
    Node4c8b04_v15* v15 = p0->field_88;
    if (v15 != 0) {
        int v16 = v15->field_8;
        v15->field_8 = v16 - 1;
        if ((v16 - 1) == 0) {
            v15->slot_3();
        }
        p0->field_88 = nullptr;
    }
    Node4c8b04_v20* v20 = p0->field_90;
    if (v20 != 0) {
        int v21 = v20->field_8;
        v20->field_8 = v21 - 1;
        if ((v21 - 1) == 0) {
            v20->slot_3();
        }
        p0->field_90 = nullptr;
    }
    Node4c8b04_v25* v25 = p0->field_98;
    if (v25 != 0) {
        int v26 = v25->field_8;
        v25->field_8 = v26 - 1;
        if ((v26 - 1) == 0) {
            v25->slot_3();
        }
        p0->field_98 = nullptr;
    }
    Node4c8b04_v30* v30 = p0->field_a0;
    if (v30 != 0) {
        int v31 = v30->field_8;
        v30->field_8 = v31 - 1;
        if ((v31 - 1) == 0) {
            v30->slot_3();
        }
        p0->field_a0 = nullptr;
    }
    Node4c8b04_v35* v35 = p0->field_a8;
    if (v35 != 0) {
        int v36 = v35->field_8;
        v35->field_8 = v36 - 1;
        if ((v36 - 1) == 0) {
            v35->slot_3();
        }
        p0->field_a8 = nullptr;
    }
    return callee_4a3d34(p0);
}

void callee_46404(long);        // 0x7100046404
void callee_46440(long);        // 0x7100046440
void callee_46480(long);        // 0x7100046480
void callee_7572c(long);        // 0x710007572c
void callee_7b288(long);        // 0x710007b288
void callee_7b584(long);        // 0x710007b584
void callee_99ad0(void*);        // 0x7100099ad0
int callee_170c58();        // 0x7100170c58

struct Arg7b5b0_0 {
    long field_0;                // +0
    unsigned char pad8[0x208];
    long field_210;                // +210
    long field_218;                // +218
    long field_220;                // +220
    long field_228;                // +228
    long field_230;                // +230
    long field_238;                // +238
    long field_240;                // +240
    long field_248;                // +248
    unsigned char pad250[0x40];
    void* field_290;               // +290
    unsigned short field_298;      // +298
    unsigned char field_29a;       // +29a
    unsigned char pad29b[0x1];
    int field_29c;                 // +29c
    long field_2a0;                // +2a0
    long field_2a8;                // +2a8
    int field_2b0;                 // +2b0
    int field_2b4;                 // +2b4
    int field_2b8;                 // +2b8
    long field_2bc __attribute__((packed, aligned(4)));                // +2bc
    int field_2c4;                 // +2c4
    void* field_2c8;               // +2c8
    void* field_2d0;               // +2d0
    int field_2d8;                 // +2d8
    int field_2dc;                 // +2dc
    int field_2e0;                 // +2e0
    int field_2e4;                 // +2e4
    long field_2e8;                // +2e8
    void* field_2f0;               // +2f0
    void* field_2f8;               // +2f8
    void* field_300;               // +300
    long field_308;                // +308
    long field_310;                // +310
    int field_318;                 // +318
    void* field_31c __attribute__((packed, aligned(4)));               // +31c
    unsigned short field_324;      // +324
    unsigned char field_326;       // +326
    unsigned char pad327[0x1];
    unsigned short field_328;      // +328
    unsigned char field_32a;       // +32a
    unsigned char pad32b[0x1];
    int field_32c;                 // +32c
    long field_330;                // +330
    long field_338;                // +338
    int field_340;                 // +340
    int field_344;                 // +344
    int field_348;                 // +348
    long field_34c __attribute__((packed, aligned(4)));                // +34c
    int field_354;                 // +354
    void* field_358;               // +358
    void* field_360;               // +360
    int field_368;                 // +368
    int field_36c;                 // +36c
    int field_370;                 // +370
    int field_374;                 // +374
    long field_378;                // +378
    void* field_380;               // +380
    void* field_388;               // +388
    void* field_390;               // +390
    long field_398;                // +398
    long field_3a0;                // +3a0
    int field_3a8;                 // +3a8
    void* field_3ac __attribute__((packed, aligned(4)));               // +3ac
    unsigned short field_3b4;      // +3b4
    unsigned char field_3b6;       // +3b6
    unsigned char pad3b7[0x1];
    long field_3b8;                // +3b8
    unsigned char pad3c0[0x4];
    int field_3c4;                 // +3c4
    void* field_3c8;               // +3c8
    int field_3d0;                 // +3d0
    int field_3d4;                 // +3d4
    int field_3d8;                 // +3d8
    long field_3dc __attribute__((packed, aligned(4)));                // +3dc
    int field_3e4;                 // +3e4
    void* field_3e8;               // +3e8
    void* field_3f0;               // +3f0
    void* field_3f8;               // +3f8
    void* field_400;               // +400
    int field_408;                 // +408
    unsigned char pad40c[0x40];
    int field_44c;                 // +44c
    int field_450;                 // +450
    unsigned char field_454;       // +454
    unsigned char field_455;       // +455
    unsigned short field_456;      // +456
    int field_458;                 // +458
    int field_45c;                 // +45c
    void* field_460;               // +460
    int field_468;                 // +468
    unsigned short field_46c;      // +46c
    unsigned char field_46e;       // +46e
    unsigned char pad46f[0x1];
    void* field_470;               // +470
    void* field_478;               // +478
    void* field_480;               // +480
    void* field_488;               // +488
    void* field_490;               // +490
    void* field_498;               // +498
    void* field_4a0;               // +4a0
    unsigned char pad4a8[0x10];
    void* field_4b8;               // +4b8
    long field_4c0;                // +4c0
    void* field_4c8;               // +4c8
    void* field_4d0;               // +4d0
    int field_4d8;                 // +4d8
    int field_4dc;                 // +4dc
    int field_4e0;                 // +4e0
    unsigned short field_4e4;      // +4e4
    unsigned char pad4e6[0x2];
    int field_4e8;                 // +4e8
    int field_4ec;                 // +4ec
    long field_4f0;                // +4f0
    int field_4f8;                 // +4f8
    unsigned char pad4fc[0xc];
    void* field_508;               // +508
    void* field_510;               // +510
    void* field_518;               // +518
    long field_520;                // +520
    int field_528;                 // +528
    long field_52c __attribute__((packed, aligned(4)));                // +52c
    long field_534 __attribute__((packed, aligned(4)));                // +534
    int field_53c;                 // +53c
    unsigned char pad540[0x8];
    int field_548;                 // +548
    int field_54c;                 // +54c
};
// Reached through the GOT slot at 0x7100c219e0.
extern int gGlobalc219e0_7b5b0;
// Reached through the GOT slot at 0x7100c22208.
extern unsigned char gGlobalc22208_7b5b0[];

// 0x710007b5b0: two addresses taken early, as irsearch's minimised order has them: +2bc before the 0xff stores (so
// MemCpyOpt's memset of them goes after it) and +3c0's before the global is read.
int call_7b5b0(Arg7b5b0_0* p0) {
    callee_99ad0(p0);
    p0->field_0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(gGlobalc22208_7b5b0) + 0x10);
    callee_46404(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x158));
    callee_46404(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x15c));
    callee_46404(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x160));
    callee_46404(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x164));
    callee_46404(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x168));
    callee_46404(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x16c));
    callee_46404(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x170));
    callee_46404(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x174));
    callee_46404(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x178));
    callee_46404(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x17c));
    callee_7b288(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x180));
    callee_7b288(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1a0));
    callee_7b288(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1c0));
    callee_7b288(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1e0));
    long a15 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x250);
    memset(reinterpret_cast<void*>(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x200)), 0, 0x50);
    callee_7572c(a15);
    p0->field_29c = 0;
    p0->field_29a = 0;
    p0->field_298 = 0;
    p0->field_290 = nullptr;
    p0->field_2b0 = -1;
    p0->field_2a8 = -1;
    p0->field_2a0 = -1;
    long* a2bc = reinterpret_cast<long*>(reinterpret_cast<unsigned char*>(p0) + 0x2bc);
    p0->field_2b4 = 0;
    p0->field_2b8 = 0;
    *a2bc = -1;
    p0->field_2c4 = -1;
    p0->field_2d8 = 0;
    p0->field_2d0 = nullptr;
    p0->field_2c8 = nullptr;
    p0->field_2dc = -1;
    long a3c0 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3c0);
    int v18 = gGlobalc219e0_7b5b0;
    p0->field_2e0 = v18;
    p0->field_2e4 = 0;
    p0->field_2e8 = -1;
    p0->field_300 = nullptr;
    p0->field_2f8 = nullptr;
    p0->field_2f0 = nullptr;
    p0->field_318 = -1;
    p0->field_310 = -1;
    p0->field_308 = -1;
    p0->field_326 = 0;
    p0->field_324 = 0;
    p0->field_31c = nullptr;
    p0->field_328 = 0;
    p0->field_32a = 0;
    p0->field_32c = 0;
    p0->field_340 = -1;
    p0->field_338 = -1;
    p0->field_330 = -1;
    p0->field_344 = 0;
    p0->field_348 = 0;
    p0->field_34c = -1;
    p0->field_370 = v18;
    p0->field_354 = -1;
    p0->field_368 = 0;
    p0->field_360 = nullptr;
    p0->field_358 = nullptr;
    p0->field_36c = -1;
    p0->field_374 = 0;
    p0->field_378 = -1;
    p0->field_390 = nullptr;
    p0->field_388 = nullptr;
    p0->field_380 = nullptr;
    p0->field_3a8 = -1;
    p0->field_3a0 = -1;
    p0->field_398 = -1;
    p0->field_3b6 = 0;
    p0->field_3b4 = 0;
    p0->field_3ac = nullptr;
    p0->field_3b8 = -1;
    callee_46404(a3c0);
    p0->field_3c4 = 0;
    p0->field_3c8 = nullptr;
    p0->field_3d0 = -1;
    p0->field_3d4 = 0;
    p0->field_3d8 = 0;
    p0->field_3dc = -1;
    p0->field_3e4 = -1;
    p0->field_400 = nullptr;
    p0->field_3f8 = nullptr;
    p0->field_3f0 = nullptr;
    p0->field_3e8 = nullptr;
    p0->field_408 = -1;
    callee_7b584(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x40c));
    callee_46440(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x440));
    callee_46404(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x448));
    p0->field_44c = -1;
    p0->field_450 = 0;
    p0->field_454 = 1;
    p0->field_455 = 0;
    p0->field_456 = 0;
    p0->field_458 = -1;
    p0->field_45c = -1;
    p0->field_460 = nullptr;
    p0->field_468 = -1;
    p0->field_46c = 0;
    p0->field_46e = 0;
    p0->field_4a0 = nullptr;
    p0->field_498 = nullptr;
    p0->field_490 = nullptr;
    p0->field_488 = nullptr;
    p0->field_480 = nullptr;
    p0->field_478 = nullptr;
    p0->field_470 = nullptr;
    callee_46480(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4a8));
    callee_46480(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4b0));
    p0->field_4c0 = -0x100000000;
    p0->field_4b8 = nullptr;
    p0->field_4d8 = 0;
    p0->field_4d0 = nullptr;
    p0->field_4c8 = nullptr;
    p0->field_4dc = -1;
    p0->field_4e0 = 0;
    p0->field_4e4 = 0xffff;
    p0->field_4e8 = -1;
    p0->field_4ec = 0;
    p0->field_4f0 = static_cast<unsigned long>(static_cast<unsigned int>(-1));
    p0->field_4f8 = 0;
    p0->field_518 = nullptr;
    p0->field_510 = nullptr;
    p0->field_508 = nullptr;
    p0->field_520 = -1;
    p0->field_528 = -1;
    callee_46480(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x540));
    p0->field_548 = 0;
    int c26 = callee_170c58();
    p0->field_248 = -1;
    p0->field_54c = c26;
    p0->field_240 = -1;
    p0->field_238 = -1;
    p0->field_230 = -1;
    p0->field_228 = -1;
    p0->field_220 = -1;
    p0->field_218 = -1;
    p0->field_210 = -1;
    p0->field_400 = reinterpret_cast<void*>(-1);
    p0->field_3f8 = reinterpret_cast<void*>(-1);
    p0->field_3f0 = reinterpret_cast<void*>(-1);
    p0->field_490 = nullptr;
    p0->field_488 = nullptr;
    p0->field_480 = nullptr;
    p0->field_478 = nullptr;
    p0->field_470 = nullptr;
    p0->field_53c = -1;
    p0->field_534 = -1;
    p0->field_52c = -1;
    return c26;
}
