// Hand fixes of generated source (third session): the generator's code with the original's statement order where a
// class boundary moves a store. Names are placeholders after the address and offset. Status: matching/README.md.

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
