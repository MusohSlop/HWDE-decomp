// Large functions matched by hand, starting from generated source (fourth session). Struct, field and callee names
// are placeholders after the address and offset, as in the generated units. Status: matching/README.md.
// new[] here calls the imported operator new[] (the PLT stub at 0x7100600880), not the game's own at 0x71003ccc34;
// the unit's map in data/units.json points _Znam at the stub.

int callee_db3d8(void*, long, int);        // 0x71000db3d8
void callee_f7a24(void*);        // 0x71000f7a24
void callee_1e2360(void*, long, int, void*);        // 0x71001e2360
void callee_1e26dc(void*, void*, long);        // 0x71001e26dc
void* callee_1e3770(void*, void*, int);        // 0x71001e3770
void callee_1e4570(void*, float);        // 0x71001e4570
void callee_1f0140(long);        // 0x71001f0140
void callee_1f0140(void*);        // 0x71001f0140
void* callee_45c458(int, int, int, int, int);        // 0x710045c458
int callee_45c96c();        // 0x710045c96c

class Nodef6fc0_v32 {
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
    float field_4c;               // +4c
};

struct Nodef6fc0_v31 {
    unsigned char pad0[0x18];
    Nodef6fc0_v32* field_18;      // +18
};

struct Argf6fc0_0 {
    unsigned char pad0[0x110];
    Nodef6fc0_v31* field_110;      // +110
    void* field_118;               // +118
    void* field_120;               // +120
    void* field_128;               // +128
    void* field_130;               // +130
    void* field_138;               // +138
    void* field_140;               // +140
    void* field_148;               // +148
    void* field_150;               // +150
    void* field_158;               // +158
    void* field_160;               // +160
    void* field_168;               // +168
    void* field_170;               // +170
    void* field_178;               // +178
    void* field_180;               // +180
    void* field_188;               // +188
    void* field_190;               // +190
    void* field_198;               // +198
    void* field_1a0;               // +1a0
    void* field_1a8;               // +1a8
    void* field_1b0;               // +1b0
    void* field_1b8;               // +1b8
    void* field_1c0;               // +1c0
    void* field_1c8;               // +1c8
    void* field_1d0;               // +1d0
    void* field_1d8;               // +1d8
    void* field_1e0;               // +1e0
    void* field_1e8;               // +1e8
    void* field_1f0;               // +1f0
    void* field_1f8;               // +1f8
    void* field_200;               // +200
    void* field_208;               // +208
    void* field_210;               // +210
    void* field_218;               // +218
    void* field_220;               // +220
    void* field_228;               // +228
    void* field_230;               // +230
    void* field_238;               // +238
    void* field_240;               // +240
    void* field_248;               // +248
    void* field_250;               // +250
    void* field_258;               // +258
    void* field_260;               // +260
    void* field_268;               // +268
    void* field_270;               // +270
    void* field_278;               // +278
    void* field_280;               // +280
    void* field_288;               // +288
    void* field_290;               // +290
    unsigned char pad298[0x1298];
    void* field_1530;               // +1530
};

struct Nodef6fc0_v34 {
    unsigned char pad0[0x18];
    void* field_18;               // +18
};

struct Nodef6fc0_v46 {
    unsigned char pad0[0x18];
    void* field_18;               // +18
};

struct Nodef6fc0_v58 {
    unsigned char pad0[0x18];
    void* field_18;               // +18
};

struct Nodef6fc0_v70 {
    unsigned char pad0[0x18];
    void* field_18;               // +18
};

struct Bytesf6fc0_0 {
    unsigned char pad0[0x118];
    Nodef6fc0_v34* field_118;      // +118
    Nodef6fc0_v46* field_120;      // +120
    Nodef6fc0_v58* field_128;      // +128
    Nodef6fc0_v70* field_130;      // +130
};

struct Globalc22c18_f6fc0 {
    void* field_0;               // +0
    void* field_8;               // +8
};

struct C256f6fc0 {
    unsigned char pad0[0x2a8];
    float field_2a8;                // +2a8
    float field_2ac;                // +2ac
    unsigned char pad2b0[0x353c];
    int field_37ec;                 // +37ec
};

struct C268f6fc0 {
    unsigned char pad0[0x2a8];
    float field_2a8;                // +2a8
    float field_2ac;                // +2ac
    unsigned char pad2b0[0x353c];
    int field_37ec;                 // +37ec
};
// Reached through the GOT slot at 0x7100c22a00.
extern void* gGlobalc22a00_f6fc0;
// Reached through the GOT slot at 0x7100c22c18.
extern Globalc22c18_f6fc0 gGlobalc22c18_f6fc0;
// Reached through the GOT slot at 0x7100c22a10.
extern void* gGlobalc22a10_f6fc0;
extern unsigned char gLocal740556_f6fc0[] __attribute__((visibility("hidden")));    // 0x7100740556
extern unsigned char gLocal73fffb_f6fc0[] __attribute__((visibility("hidden")));    // 0x710073fffb
extern unsigned char gLocal740568_f6fc0[] __attribute__((visibility("hidden")));    // 0x7100740568
extern unsigned char gLocal74056a_f6fc0[] __attribute__((visibility("hidden")));    // 0x710074056a
extern unsigned char gLocal74056c_f6fc0[] __attribute__((visibility("hidden")));    // 0x710074056c
extern unsigned char gLocal740570_f6fc0[] __attribute__((visibility("hidden")));    // 0x7100740570
extern unsigned char gLocal740575_f6fc0[] __attribute__((visibility("hidden")));    // 0x7100740575
extern unsigned char gLocal740579_f6fc0[] __attribute__((visibility("hidden")));    // 0x7100740579
extern unsigned char gLocal74057d_f6fc0[] __attribute__((visibility("hidden")));    // 0x710074057d
extern unsigned char gLocal740583_f6fc0[] __attribute__((visibility("hidden")));    // 0x7100740583
extern unsigned char gLocal740588_f6fc0[] __attribute__((visibility("hidden")));    // 0x7100740588
extern unsigned char gLocal74058c_f6fc0[] __attribute__((visibility("hidden")));    // 0x710074058c
extern unsigned char gLocal740590_f6fc0[] __attribute__((visibility("hidden")));    // 0x7100740590
extern unsigned char gLocal740596_f6fc0[] __attribute__((visibility("hidden")));    // 0x7100740596
extern unsigned char gLocal7405ac_f6fc0[] __attribute__((visibility("hidden")));    // 0x71007405ac
extern unsigned char gLocal7405c2_f6fc0[] __attribute__((visibility("hidden")));    // 0x71007405c2
extern unsigned char gLocal7405d8_f6fc0[] __attribute__((visibility("hidden")));    // 0x71007405d8
extern unsigned char gLocal7405ee_f6fc0[] __attribute__((visibility("hidden")));    // 0x71007405ee
extern unsigned char gLocal740604_f6fc0[] __attribute__((visibility("hidden")));    // 0x7100740604
extern unsigned char gLocal74061a_f6fc0[] __attribute__((visibility("hidden")));    // 0x710074061a
extern unsigned char gLocal740630_f6fc0[] __attribute__((visibility("hidden")));    // 0x7100740630
extern unsigned char gLocal740646_f6fc0[] __attribute__((visibility("hidden")));    // 0x7100740646
extern unsigned char gLocal74065c_f6fc0[] __attribute__((visibility("hidden")));    // 0x710074065c
extern unsigned char gLocal740672_f6fc0[] __attribute__((visibility("hidden")));    // 0x7100740672
extern unsigned char gLocal740688_f6fc0[] __attribute__((visibility("hidden")));    // 0x7100740688
extern unsigned char gLocal74069e_f6fc0[] __attribute__((visibility("hidden")));    // 0x710074069e
extern unsigned char gLocal7406b4_f6fc0[] __attribute__((visibility("hidden")));    // 0x71007406b4
extern unsigned char gLocal7406ca_f6fc0[] __attribute__((visibility("hidden")));    // 0x71007406ca
extern unsigned char gLocal7406e0_f6fc0[] __attribute__((visibility("hidden")));    // 0x71007406e0
extern unsigned char gLocal7406f6_f6fc0[] __attribute__((visibility("hidden")));    // 0x71007406f6
extern unsigned char gLocal74070f_f6fc0[] __attribute__((visibility("hidden")));    // 0x710074070f
extern unsigned char gLocal740728_f6fc0[] __attribute__((visibility("hidden")));    // 0x7100740728
extern unsigned char gLocal740741_f6fc0[] __attribute__((visibility("hidden")));    // 0x7100740741
extern unsigned char gLocal74075a_f6fc0[] __attribute__((visibility("hidden")));    // 0x710074075a
extern unsigned char gLocal740773_f6fc0[] __attribute__((visibility("hidden")));    // 0x7100740773
extern unsigned char gLocal74078c_f6fc0[] __attribute__((visibility("hidden")));    // 0x710074078c
extern unsigned char gLocal7407a5_f6fc0[] __attribute__((visibility("hidden")));    // 0x71007407a5
extern unsigned char gLocal7407be_f6fc0[] __attribute__((visibility("hidden")));    // 0x71007407be
extern unsigned char gLocal7407d0_f6fc0[] __attribute__((visibility("hidden")));    // 0x71007407d0
extern unsigned char gLocal7407e0_f6fc0[] __attribute__((visibility("hidden")));    // 0x71007407e0

// 0x71000f6fc0: void; the two-float field at +2a8 of the two inlined 0x37f0-byte objects is stored as two floats (24.0f), so the merged 64-bit constant is built in place instead of hoisted
void call_f6fc0(Argf6fc0_0* p0) {
    Nodef6fc0_v31* v0 = p0->field_110;
    if (v0 == 0) {
        void* v1 = gGlobalc22a00_f6fc0;
        long a2 = reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x110);
        callee_1e26dc(v1, p0, 0);
        void* v4 = gGlobalc22a00_f6fc0;
        callee_1e2360(v4, a2, 0x4209, gLocal740556_f6fc0);
        Nodef6fc0_v31* v6 = p0->field_110;
        void* c7 = callee_1e3770(v6, gLocal73fffb_f6fc0, 1);
        p0->field_118 = c7;
        Nodef6fc0_v31* v8 = p0->field_110;
        void* c9 = callee_1e3770(v8, gLocal740568_f6fc0, 1);
        p0->field_120 = c9;
        Nodef6fc0_v31* v10 = p0->field_110;
        void* c11 = callee_1e3770(v10, gLocal74056a_f6fc0, 1);
        p0->field_128 = c11;
        Nodef6fc0_v31* v12 = p0->field_110;
        void* c13 = callee_1e3770(v12, gLocal74056c_f6fc0, 1);
        p0->field_130 = c13;
        Nodef6fc0_v31* v14 = p0->field_110;
        void* c15 = callee_1e3770(v14, gLocal740570_f6fc0, 1);
        p0->field_138 = c15;
        Nodef6fc0_v31* v16 = p0->field_110;
        void* c17 = callee_1e3770(v16, gLocal740575_f6fc0, 1);
        p0->field_140 = c17;
        Nodef6fc0_v31* v18 = p0->field_110;
        void* c19 = callee_1e3770(v18, gLocal740579_f6fc0, 1);
        p0->field_148 = c19;
        Nodef6fc0_v31* v20 = p0->field_110;
        void* c21 = callee_1e3770(v20, gLocal74057d_f6fc0, 1);
        p0->field_150 = c21;
        Nodef6fc0_v31* v22 = p0->field_110;
        void* c23 = callee_1e3770(v22, gLocal740583_f6fc0, 1);
        p0->field_158 = c23;
        Nodef6fc0_v31* v24 = p0->field_110;
        void* c25 = callee_1e3770(v24, gLocal740588_f6fc0, 1);
        p0->field_160 = c25;
        Nodef6fc0_v31* v26 = p0->field_110;
        void* c27 = callee_1e3770(v26, gLocal74058c_f6fc0, 1);
        p0->field_168 = c27;
        Nodef6fc0_v31* v28 = p0->field_110;
        void* c29 = callee_1e3770(v28, gLocal740590_f6fc0, 1);
        p0->field_170 = c29;
        long r30 = 0;
        Nodef6fc0_v31* v31;
        Nodef6fc0_v32* v32;
        float v33;
        Nodef6fc0_v34* v34;
        void* v35;
        Nodef6fc0_v31* v37;
        Nodef6fc0_v32* v38;
        float v39;
        Nodef6fc0_v34* v40;
        void* v41;
        Nodef6fc0_v31* v43;
        Nodef6fc0_v32* v44;
        float v45;
        Nodef6fc0_v46* v46;
        void* v47;
        Nodef6fc0_v31* v49;
        Nodef6fc0_v32* v50;
        float v51;
        Nodef6fc0_v46* v52;
        void* v53;
        Nodef6fc0_v31* v55;
        Nodef6fc0_v32* v56;
        float v57;
        Nodef6fc0_v58* v58;
        void* v59;
        Nodef6fc0_v31* v61;
        Nodef6fc0_v32* v62;
        float v63;
        Nodef6fc0_v58* v64;
        void* v65;
        Nodef6fc0_v31* v67;
        Nodef6fc0_v32* v68;
        float v69;
        Nodef6fc0_v70* v70;
        void* v71;
        Nodef6fc0_v31* v73;
        Nodef6fc0_v32* v74;
        float v75;
        Nodef6fc0_v70* v76;
        void* v77;
        do {
            v31 = p0->field_110;
            v32 = v31->field_18;
            v33 = v32->field_48;
            v34 = reinterpret_cast<Bytesf6fc0_0*>(reinterpret_cast<unsigned char*>(p0) + r30)->field_118;
            v35 = v34->field_18;
            callee_1e4570(v35, v33);
            v37 = p0->field_110;
            v38 = v37->field_18;
            v39 = v38->field_4c;
            v40 = reinterpret_cast<Bytesf6fc0_0*>(reinterpret_cast<unsigned char*>(p0) + r30)->field_118;
            v41 = v40->field_18;
            callee_1e4570(v41, v39);
            v43 = p0->field_110;
            v44 = v43->field_18;
            v45 = v44->field_48;
            v46 = reinterpret_cast<Bytesf6fc0_0*>(reinterpret_cast<unsigned char*>(p0) + r30)->field_120;
            v47 = v46->field_18;
            callee_1e4570(v47, v45);
            v49 = p0->field_110;
            v50 = v49->field_18;
            v51 = v50->field_4c;
            v52 = reinterpret_cast<Bytesf6fc0_0*>(reinterpret_cast<unsigned char*>(p0) + r30)->field_120;
            v53 = v52->field_18;
            callee_1e4570(v53, v51);
            v55 = p0->field_110;
            v56 = v55->field_18;
            v57 = v56->field_48;
            v58 = reinterpret_cast<Bytesf6fc0_0*>(reinterpret_cast<unsigned char*>(p0) + r30)->field_128;
            v59 = v58->field_18;
            callee_1e4570(v59, v57);
            v61 = p0->field_110;
            v62 = v61->field_18;
            v63 = v62->field_4c;
            v64 = reinterpret_cast<Bytesf6fc0_0*>(reinterpret_cast<unsigned char*>(p0) + r30)->field_128;
            v65 = v64->field_18;
            callee_1e4570(v65, v63);
            v67 = p0->field_110;
            v68 = v67->field_18;
            v69 = v68->field_48;
            v70 = reinterpret_cast<Bytesf6fc0_0*>(reinterpret_cast<unsigned char*>(p0) + r30)->field_130;
            v71 = v70->field_18;
            callee_1e4570(v71, v69);
            v73 = p0->field_110;
            v74 = v73->field_18;
            v75 = v74->field_4c;
            v76 = reinterpret_cast<Bytesf6fc0_0*>(reinterpret_cast<unsigned char*>(p0) + r30)->field_130;
            v77 = v76->field_18;
            callee_1e4570(v77, v75);
            r30 = r30 + 0x20;
        } while (r30 != 0x60);
        Nodef6fc0_v31* v79 = p0->field_110;
        Nodef6fc0_v32* v80 = v79->field_18;
        void* c83 = v80->slot_12(gLocal740596_f6fc0, 1);
        Nodef6fc0_v31* v84 = p0->field_110;
        p0->field_178 = c83;
        Nodef6fc0_v32* v85 = v84->field_18;
        void* c88 = v85->slot_12(gLocal7405ac_f6fc0, 1);
        Nodef6fc0_v31* v89 = p0->field_110;
        p0->field_198 = c88;
        Nodef6fc0_v32* v90 = v89->field_18;
        void* c93 = v90->slot_12(gLocal7405c2_f6fc0, 1);
        Nodef6fc0_v31* v94 = p0->field_110;
        p0->field_1b8 = c93;
        Nodef6fc0_v32* v95 = v94->field_18;
        void* c98 = v95->slot_12(gLocal7405d8_f6fc0, 1);
        Nodef6fc0_v31* v99 = p0->field_110;
        p0->field_1d8 = c98;
        Nodef6fc0_v32* v100 = v99->field_18;
        void* c103 = v100->slot_12(gLocal7405ee_f6fc0, 1);
        Nodef6fc0_v31* v104 = p0->field_110;
        p0->field_1f8 = c103;
        Nodef6fc0_v32* v105 = v104->field_18;
        void* c108 = v105->slot_12(gLocal740604_f6fc0, 1);
        Nodef6fc0_v31* v109 = p0->field_110;
        p0->field_218 = c108;
        Nodef6fc0_v32* v110 = v109->field_18;
        void* c113 = v110->slot_12(gLocal74061a_f6fc0, 1);
        Nodef6fc0_v31* v114 = p0->field_110;
        p0->field_238 = c113;
        Nodef6fc0_v32* v115 = v114->field_18;
        void* c118 = v115->slot_12(gLocal740630_f6fc0, 1);
        Nodef6fc0_v31* v119 = p0->field_110;
        p0->field_258 = c118;
        Nodef6fc0_v32* v120 = v119->field_18;
        void* c123 = v120->slot_12(gLocal740630_f6fc0, 1);
        Nodef6fc0_v31* v124 = p0->field_110;
        p0->field_260 = c123;
        Nodef6fc0_v32* v125 = v124->field_18;
        void* c128 = v125->slot_12(gLocal740646_f6fc0, 1);
        Nodef6fc0_v31* v129 = p0->field_110;
        p0->field_180 = c128;
        Nodef6fc0_v32* v130 = v129->field_18;
        void* c133 = v130->slot_12(gLocal74065c_f6fc0, 1);
        Nodef6fc0_v31* v134 = p0->field_110;
        p0->field_1a0 = c133;
        Nodef6fc0_v32* v135 = v134->field_18;
        void* c138 = v135->slot_12(gLocal740672_f6fc0, 1);
        Nodef6fc0_v31* v139 = p0->field_110;
        p0->field_1c0 = c138;
        Nodef6fc0_v32* v140 = v139->field_18;
        void* c143 = v140->slot_12(gLocal740688_f6fc0, 1);
        Nodef6fc0_v31* v144 = p0->field_110;
        p0->field_1e0 = c143;
        Nodef6fc0_v32* v145 = v144->field_18;
        void* c148 = v145->slot_12(gLocal74069e_f6fc0, 1);
        Nodef6fc0_v31* v149 = p0->field_110;
        p0->field_200 = c148;
        Nodef6fc0_v32* v150 = v149->field_18;
        void* c153 = v150->slot_12(gLocal7406b4_f6fc0, 1);
        Nodef6fc0_v31* v154 = p0->field_110;
        p0->field_220 = c153;
        Nodef6fc0_v32* v155 = v154->field_18;
        void* c158 = v155->slot_12(gLocal7406ca_f6fc0, 1);
        Nodef6fc0_v31* v159 = p0->field_110;
        p0->field_240 = c158;
        Nodef6fc0_v32* v160 = v159->field_18;
        void* c163 = v160->slot_12(gLocal7406e0_f6fc0, 1);
        Nodef6fc0_v31* v164 = p0->field_110;
        p0->field_268 = c163;
        Nodef6fc0_v32* v165 = v164->field_18;
        void* c168 = v165->slot_12(gLocal7406f6_f6fc0, 1);
        Nodef6fc0_v31* v169 = p0->field_110;
        p0->field_188 = c168;
        Nodef6fc0_v32* v170 = v169->field_18;
        void* c173 = v170->slot_12(gLocal74070f_f6fc0, 1);
        Nodef6fc0_v31* v174 = p0->field_110;
        p0->field_1a8 = c173;
        Nodef6fc0_v32* v175 = v174->field_18;
        void* c178 = v175->slot_12(gLocal740728_f6fc0, 1);
        Nodef6fc0_v31* v179 = p0->field_110;
        p0->field_1c8 = c178;
        Nodef6fc0_v32* v180 = v179->field_18;
        void* c183 = v180->slot_12(gLocal740741_f6fc0, 1);
        Nodef6fc0_v31* v184 = p0->field_110;
        p0->field_1e8 = c183;
        Nodef6fc0_v32* v185 = v184->field_18;
        void* c188 = v185->slot_12(gLocal74075a_f6fc0, 1);
        Nodef6fc0_v31* v189 = p0->field_110;
        p0->field_208 = c188;
        Nodef6fc0_v32* v190 = v189->field_18;
        void* c193 = v190->slot_12(gLocal740773_f6fc0, 1);
        Nodef6fc0_v31* v194 = p0->field_110;
        p0->field_228 = c193;
        Nodef6fc0_v32* v195 = v194->field_18;
        void* c198 = v195->slot_12(gLocal74078c_f6fc0, 1);
        Nodef6fc0_v31* v199 = p0->field_110;
        p0->field_248 = c198;
        Nodef6fc0_v32* v200 = v199->field_18;
        void* c203 = v200->slot_12(gLocal7407a5_f6fc0, 1);
        Nodef6fc0_v31* v204 = p0->field_110;
        p0->field_270 = c203;
        Nodef6fc0_v32* v205 = v204->field_18;
        void* c208 = v205->slot_12(gLocal740646_f6fc0, 1);
        Nodef6fc0_v31* v209 = p0->field_110;
        p0->field_190 = c208;
        Nodef6fc0_v32* v210 = v209->field_18;
        void* c213 = v210->slot_12(gLocal74065c_f6fc0, 1);
        Nodef6fc0_v31* v214 = p0->field_110;
        p0->field_1b0 = c213;
        Nodef6fc0_v32* v215 = v214->field_18;
        void* c218 = v215->slot_12(gLocal740672_f6fc0, 1);
        Nodef6fc0_v31* v219 = p0->field_110;
        p0->field_1d0 = c218;
        Nodef6fc0_v32* v220 = v219->field_18;
        void* c223 = v220->slot_12(gLocal740688_f6fc0, 1);
        Nodef6fc0_v31* v224 = p0->field_110;
        p0->field_1f0 = c223;
        Nodef6fc0_v32* v225 = v224->field_18;
        void* c228 = v225->slot_12(gLocal74069e_f6fc0, 1);
        Nodef6fc0_v31* v229 = p0->field_110;
        p0->field_210 = c228;
        Nodef6fc0_v32* v230 = v229->field_18;
        void* c233 = v230->slot_12(gLocal7406b4_f6fc0, 1);
        Nodef6fc0_v31* v234 = p0->field_110;
        p0->field_230 = c233;
        Nodef6fc0_v32* v235 = v234->field_18;
        void* c238 = v235->slot_12(gLocal7406ca_f6fc0, 1);
        Nodef6fc0_v31* v239 = p0->field_110;
        p0->field_250 = c238;
        Nodef6fc0_v32* v240 = v239->field_18;
        void* c243 = v240->slot_12(gLocal7406e0_f6fc0, 1);
        Nodef6fc0_v31* v244 = p0->field_110;
        p0->field_278 = c243;
        Nodef6fc0_v32* v245 = v244->field_18;
        void* c248 = v245->slot_12(gLocal7407be_f6fc0, 1);
        Nodef6fc0_v31* v249 = p0->field_110;
        p0->field_280 = c248;
        Nodef6fc0_v32* v250 = v249->field_18;
        void* c253 = v250->slot_12(gLocal7407d0_f6fc0, 1);
        p0->field_288 = c253;
        void* v254 = gGlobalc22c18_f6fc0.field_0;
        void* m265;
        if (v254 == 0) {
            int c255 = callee_45c96c();
            C256f6fc0* c256 = static_cast<C256f6fc0*>(callee_45c458(c255, 0x10, 0x37f0, 1, 0));
            callee_1f0140(c256);
            callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(c256) + 0x88));
            callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(c256) + 0x110));
            callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(c256) + 0x198));
            callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(c256) + 0x220));
            c256->field_2a8 = 24.0f; c256->field_2ac = 24.0f;
            long r262 = 0;
            do {
                callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(c256) + r262 + 0x2b0));
                r262 = r262 + 0x88;
            } while (r262 != static_cast<unsigned long>(static_cast<unsigned int>(0x3520)));
            c256->field_37ec = 0;
            gGlobalc22c18_f6fc0.field_0 = reinterpret_cast<void*>(c256);
            m265 = reinterpret_cast<void*>(c256);
        } else {
            m265 = v254;
        }
        void* v266 = gGlobalc22c18_f6fc0.field_8;
        void* m277;
        if (v266 == 0) {
            int c267 = callee_45c96c();
            C268f6fc0* c268 = static_cast<C268f6fc0*>(callee_45c458(c267, 0x10, 0x37f0, 1, 0));
            callee_1f0140(c268);
            callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(c268) + 0x88));
            callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(c268) + 0x110));
            callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(c268) + 0x198));
            callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(c268) + 0x220));
            c268->field_2a8 = 24.0f; c268->field_2ac = 24.0f;
            long r274 = 0;
            do {
                callee_1f0140(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(c268) + r274 + 0x2b0));
                r274 = r274 + 0x88;
            } while (r274 != static_cast<unsigned long>(static_cast<unsigned int>(0x3520)));
            c268->field_37ec = 0;
            gGlobalc22c18_f6fc0.field_8 = reinterpret_cast<void*>(c268);
            void* v276 = gGlobalc22c18_f6fc0.field_0;
            m277 = v276;
        } else {
            m277 = m265;
        }
        callee_f7a24(m277);
        void* v279 = gGlobalc22c18_f6fc0.field_8;
        callee_f7a24(v279);
        Nodef6fc0_v31* v281 = p0->field_110;
        Nodef6fc0_v32* v282 = v281->field_18;
        void* c285 = v282->slot_12(gLocal7407e0_f6fc0, 1);
        p0->field_290 = c285;
        void* v286 = gGlobalc22a10_f6fc0;
        callee_db3d8(v286, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x298), 0x44);
        void* v288 = gGlobalc22a10_f6fc0;
        callee_db3d8(v288, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x4b8), 0x44);
        void* v290 = gGlobalc22a10_f6fc0;
        callee_db3d8(v290, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x6d8), 0x44);
        void* v292 = gGlobalc22a10_f6fc0;
        callee_db3d8(v292, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x8f8), 0x44);
        void* v294 = gGlobalc22a10_f6fc0;
        callee_db3d8(v294, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xb18), 0x44);
        void* v296 = gGlobalc22a10_f6fc0;
        callee_db3d8(v296, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xd38), 0x44);
        void* v298 = gGlobalc22a10_f6fc0;
        callee_db3d8(v298, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xf58), 0x44);
        void* v300 = gGlobalc22a10_f6fc0;
        callee_db3d8(v300, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1178), 0x44);
        void* v302 = gGlobalc22a10_f6fc0;
        callee_db3d8(v302, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1200), 0x8b);
        void* v304 = gGlobalc22a10_f6fc0;
        callee_db3d8(v304, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x3a8), 0x10c);
        void* v306 = gGlobalc22a10_f6fc0;
        callee_db3d8(v306, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x5c8), 0x10c);
        void* v308 = gGlobalc22a10_f6fc0;
        callee_db3d8(v308, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x7e8), 0x10c);
        void* v310 = gGlobalc22a10_f6fc0;
        callee_db3d8(v310, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xa08), 0x10c);
        void* v312 = gGlobalc22a10_f6fc0;
        callee_db3d8(v312, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xc28), 0x10c);
        void* v314 = gGlobalc22a10_f6fc0;
        callee_db3d8(v314, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xe48), 0x10c);
        void* v316 = gGlobalc22a10_f6fc0;
        callee_db3d8(v316, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1068), 0x10c);
        void* v318 = gGlobalc22a10_f6fc0;
        callee_db3d8(v318, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1310), 0x10c);
        void* v320 = gGlobalc22a10_f6fc0;
        callee_db3d8(v320, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x430), 0x10b);
        void* v322 = gGlobalc22a10_f6fc0;
        callee_db3d8(v322, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x650), 0x10b);
        void* v324 = gGlobalc22a10_f6fc0;
        callee_db3d8(v324, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x870), 0x10b);
        void* v326 = gGlobalc22a10_f6fc0;
        callee_db3d8(v326, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xa90), 0x10b);
        void* v328 = gGlobalc22a10_f6fc0;
        callee_db3d8(v328, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xcb0), 0x10b);
        void* v330 = gGlobalc22a10_f6fc0;
        callee_db3d8(v330, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0xed0), 0x10b);
        void* v332 = gGlobalc22a10_f6fc0;
        callee_db3d8(v332, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x10f0), 0x10b);
        void* v334 = gGlobalc22a10_f6fc0;
        callee_db3d8(v334, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1398), 0x10b);
        void* v336 = gGlobalc22a10_f6fc0;
        callee_db3d8(v336, reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p0) + 0x1420), 0xa3);
        p0->field_1530 = nullptr;
    }
}

float callee_2578(int, int);        // 0x7100002578
float callee_25fc(int, float);        // 0x71000025fc
float callee_2684(int, int);        // 0x7100002684
int callee_2740(int, int);        // 0x7100002740
int callee_27c4(int, int);        // 0x71000027c4
int callee_2848(int, int);        // 0x7100002848
int callee_28cc(int, int);        // 0x71000028cc
int callee_295c(int, int);        // 0x710000295c
short callee_db3c(int);        // 0x710000db3c
int callee_ebe8(int);        // 0x710000ebe8
int callee_211dc(void*, unsigned short, int, int, int, int);        // 0x71000211dc

struct Node1f00_v1 {
    unsigned char pad0[0xc4];
    int field_c4;                 // +c4
};

struct Elem1f00_0 {
    Node1f00_v1* field_0;        // +0
};

class Arg1f00_1 {
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
    virtual void* slot_9();
};

class C71f00 {
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
    virtual void slot_12();
    virtual void slot_13();
    virtual void slot_14();
    virtual void slot_15();
    virtual void slot_16();
    virtual void slot_17();
    virtual void slot_18();
    virtual void slot_19();
    virtual void slot_20();
    virtual void slot_21();
    virtual void slot_22();
    virtual void slot_23();
    virtual void slot_24();
    virtual void slot_25();
    virtual void slot_26();
    virtual void slot_27();
    virtual void slot_28();
    virtual void slot_29();
    virtual void slot_30();
    virtual void slot_31();
    virtual void slot_32();
    virtual void slot_33();
    virtual void slot_34();
    virtual void slot_35();
    virtual void slot_36();
    virtual void slot_37();
    virtual void slot_38();
    virtual void slot_39();
    virtual void slot_40();
    virtual void slot_41();
    virtual void slot_42();
    virtual void slot_43();
    virtual void slot_44();
    virtual void slot_45();
    virtual void slot_46();
    virtual void slot_47();
    virtual void slot_48();
    virtual void slot_49();
    virtual void slot_50();
    virtual void slot_51();
    virtual void slot_52();
    virtual void slot_53();
    virtual void slot_54();
    virtual void slot_55();
    virtual void slot_56();
    virtual void slot_57();
    virtual void slot_58();
    virtual void slot_59();
    virtual void slot_60();
    virtual void slot_61();
    virtual void slot_62();
    virtual void slot_63();
    virtual void slot_64();
    virtual void slot_65();
    virtual void slot_66();
    virtual void slot_67();
    virtual void slot_68();
    virtual void slot_69();
    virtual void slot_70();
    virtual void slot_71();
    virtual void slot_72();
    virtual void slot_73();
    virtual void slot_74();
    virtual void slot_75();
    virtual void slot_76();
    virtual void slot_77();
    virtual void slot_78();
    virtual void slot_79();
    virtual void slot_80();
    virtual void slot_81();
    virtual void slot_82();
    virtual void slot_83();
    virtual void slot_84();
    virtual void slot_85();
    virtual void slot_86();
    virtual void slot_87();
    virtual void slot_88();
    virtual void slot_89();
    virtual void slot_90();
    virtual void slot_91();
    virtual void slot_92();
    virtual void slot_93();
    virtual void slot_94();
    virtual void slot_95();
    virtual void slot_96();
    virtual void slot_97();
    virtual void slot_98();
    virtual void slot_99();
    virtual void slot_100();
    virtual void slot_101();
    virtual void slot_102();
    virtual void slot_103();
    virtual void slot_104();
    virtual void slot_105();
    virtual void slot_106();
    virtual void slot_107();
    virtual void slot_108();
    virtual void slot_109();
    virtual void slot_110();
    virtual void slot_111();
    virtual void slot_112();
    virtual void slot_113();
    virtual void slot_114();
    virtual void slot_115();
    virtual void slot_116();
    virtual void slot_117();
    virtual void slot_118();
    virtual void slot_119();
    virtual void slot_120();
    virtual void slot_121();
    virtual void slot_122();
    virtual void slot_123();
    virtual void slot_124();
    virtual void slot_125();
    virtual void slot_126();
    virtual void slot_127();
    virtual void slot_128();
    virtual void slot_129();
    virtual void slot_130();
    virtual void slot_131();
    virtual void slot_132(float);
};

struct Elem1f00_1 {
    void* field_0;               // +0
};

class M141f00 {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();
    virtual void slot_4();
    virtual void slot_5();
    virtual void slot_6();
    virtual void slot_7();
    virtual void* slot_8();
};

class C171f00 {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();
    virtual void slot_4();
    virtual void slot_5(int, int, int, int);
};

class C251f00 {
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
    virtual void slot_12();
    virtual void slot_13();
    virtual void slot_14();
    virtual void slot_15();
    virtual void slot_16();
    virtual void slot_17();
    virtual void slot_18();
    virtual void slot_19();
    virtual void slot_20();
    virtual void slot_21();
    virtual void slot_22();
    virtual void slot_23();
    virtual void slot_24();
    virtual void slot_25();
    virtual void slot_26();
    virtual void slot_27();
    virtual void slot_28();
    virtual void slot_29();
    virtual void slot_30();
    virtual void slot_31();
    virtual void slot_32();
    virtual void slot_33();
    virtual void slot_34();
    virtual void slot_35();
    virtual void slot_36();
    virtual void slot_37();
    virtual void slot_38();
    virtual void slot_39();
    virtual void slot_40();
    virtual void slot_41();
    virtual void slot_42(float, int);
};

struct Elem1f00_2 {
    void* field_0;               // +0
};

class M321f00 {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();
    virtual void slot_4();
    virtual void slot_5();
    virtual void slot_6();
    virtual void slot_7();
    virtual void* slot_8();
};

class C351f00 {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();
    virtual void slot_4();
    virtual void slot_5(int, int, int, int);
};

struct Elem1f00_3 {
    void* field_0;               // +0
};

struct M421f00 {
    unsigned char pad0[0x10];
    int field_10;                 // +10
    unsigned char pad14[0x8];
    int field_1c;                 // +1c
    unsigned char pad20[0x8];
    int field_28;                 // +28
    unsigned char pad2c[0x8];
    int field_34;                 // +34
    unsigned char pad38[0x8];
    int field_40;                 // +40
    unsigned char pad44[0x8];
    int field_4c;                 // +4c
    unsigned char pad50[0x8];
    int field_58;                 // +58
    unsigned char pad5c[0x8];
    int field_64;                 // +64
    unsigned char pad68[0x8];
    int field_70;                 // +70
    unsigned char pad74[0x8];
    int field_7c;                 // +7c
    unsigned char pad80[0x8];
    int field_88;                 // +88
    unsigned char pad8c[0x8];
    int field_94;                 // +94
    unsigned char pad98[0x8];
    int field_a0;                 // +a0
};

struct C591f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C661f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C731f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C801f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C871f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C941f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C1011f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C1081f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C1151f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C1221f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C1291f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C1361f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C1431f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct Node1f00_v150 {
    unsigned char pad0[0x10];
    int field_10;                 // +10
    unsigned char pad14[0x8];
    int field_1c;                 // +1c
    unsigned char pad20[0x8];
    int field_28;                 // +28
    unsigned char pad2c[0x8];
    int field_34;                 // +34
    unsigned char pad38[0x8];
    int field_40;                 // +40
    unsigned char pad44[0x8];
    int field_4c;                 // +4c
    unsigned char pad50[0x8];
    int field_58;                 // +58
    unsigned char pad5c[0x8];
    int field_64;                 // +64
    unsigned char pad68[0x8];
    int field_70;                 // +70
    unsigned char pad74[0x8];
    int field_7c;                 // +7c
    unsigned char pad80[0x8];
    int field_88;                 // +88
    unsigned char pad8c[0x8];
    int field_94;                 // +94
    unsigned char pad98[0x8];
    int field_a0;                 // +a0
};

struct Elem1f00_4 {
    Node1f00_v150* field_0;      // +0
};

struct C1671f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C1741f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C1811f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C1881f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C1951f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C2021f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C2091f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C2161f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C2231f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C2301f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C2371f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C2441f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C2511f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct Node1f00_v258 {
    unsigned char pad0[0x10];
    int field_10;                 // +10
    unsigned char pad14[0x8];
    int field_1c;                 // +1c
    unsigned char pad20[0x8];
    int field_28;                 // +28
    unsigned char pad2c[0x8];
    int field_34;                 // +34
    unsigned char pad38[0x8];
    int field_40;                 // +40
    unsigned char pad44[0x8];
    int field_4c;                 // +4c
    unsigned char pad50[0x8];
    int field_58;                 // +58
    unsigned char pad5c[0x8];
    int field_64;                 // +64
    unsigned char pad68[0x8];
    int field_70;                 // +70
    unsigned char pad74[0x8];
    int field_7c;                 // +7c
    unsigned char pad80[0x8];
    int field_88;                 // +88
    unsigned char pad8c[0x8];
    int field_94;                 // +94
    unsigned char pad98[0x8];
    int field_a0;                 // +a0
};

struct Elem1f00_5 {
    Node1f00_v258* field_0;      // +0
};

struct C2751f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C2821f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C2891f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C2961f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C3031f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C3101f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C3171f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C3241f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C3311f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C3381f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C3451f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C3521f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C3591f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct Node1f00_v366 {
    unsigned char pad0[0x10];
    int field_10;                 // +10
    unsigned char pad14[0x8];
    int field_1c;                 // +1c
    unsigned char pad20[0x8];
    int field_28;                 // +28
    unsigned char pad2c[0x8];
    int field_34;                 // +34
    unsigned char pad38[0x8];
    int field_40;                 // +40
    unsigned char pad44[0x8];
    int field_4c;                 // +4c
    unsigned char pad50[0x8];
    int field_58;                 // +58
    unsigned char pad5c[0x8];
    int field_64;                 // +64
    unsigned char pad68[0x8];
    int field_70;                 // +70
    unsigned char pad74[0x8];
    int field_7c;                 // +7c
    unsigned char pad80[0x8];
    int field_88;                 // +88
    unsigned char pad8c[0x8];
    int field_94;                 // +94
    unsigned char pad98[0x8];
    int field_a0;                 // +a0
};

struct Elem1f00_6 {
    Node1f00_v366* field_0;      // +0
};

struct C3831f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C3901f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C3971f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C4041f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C4111f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C4181f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C4251f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C4321f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C4391f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C4461f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C4531f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C4601f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C4671f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct Node1f00_v474 {
    unsigned char pad0[0x10];
    int field_10;                 // +10
    unsigned char pad14[0x8];
    int field_1c;                 // +1c
    unsigned char pad20[0x8];
    int field_28;                 // +28
    unsigned char pad2c[0x8];
    int field_34;                 // +34
    unsigned char pad38[0x8];
    int field_40;                 // +40
    unsigned char pad44[0x8];
    int field_4c;                 // +4c
    unsigned char pad50[0x8];
    int field_58;                 // +58
    unsigned char pad5c[0x8];
    int field_64;                 // +64
    unsigned char pad68[0x8];
    int field_70;                 // +70
    unsigned char pad74[0x8];
    int field_7c;                 // +7c
    unsigned char pad80[0x8];
    int field_88;                 // +88
    unsigned char pad8c[0x8];
    int field_94;                 // +94
    unsigned char pad98[0x8];
    int field_a0;                 // +a0
};

struct Elem1f00_7 {
    Node1f00_v474* field_0;      // +0
};

struct C4911f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C4971f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C5031f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C5091f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C5151f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C5211f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C5271f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C5331f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C5391f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C5451f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C5511f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C5571f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};

struct C5631f00 {
    unsigned char pad0[0x24];
    unsigned short field_24;      // +24
};
// Reached through the GOT slot at 0x7100c21698.
extern void* gGlobalc21698_1f00;
// Reached through the GOT slot at 0x7100c21690.
extern void* gGlobalc21690_1f00;

// 0x7100001f00: the float from 2578 is 25fc's second argument and the float from 25fc and 2684 goes on to the virtual calls; db3c returns a short id, checked as unsigned and used as a signed index
int call_1f00(int p0, Arg1f00_1* p1) {
    void* v0 = gGlobalc21698_1f00;
    Node1f00_v1* v1 = (static_cast<unsigned int>(p0) < 2 ? &reinterpret_cast<Elem1f00_0*>(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v0) + 0xb08))[static_cast<long>(static_cast<int>(p0))] : &reinterpret_cast<Elem1f00_0*>(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v0) + 0xb08))[0])->field_0;
    int v2 = v1->field_c4;
    float c3 = callee_2578(p0, v2);
    float c4 = callee_25fc(p0, c3);
    if (c4 > 0.0f) {
        C71f00* c7 = static_cast<C71f00*>(p1->slot_9());
        c7->slot_132(c4);
        void* v11 = gGlobalc21690_1f00;
        short c12 = callee_db3c(p0);
        M141f00* m14;
        if (static_cast<unsigned short>(c12) <= 0x6d6) {
            void* v13 = reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(v11) + 0x138)[c12];
            m14 = static_cast<M141f00*>(v13);
        } else {
            m14 = nullptr;
        }
        C171f00* c17 = static_cast<C171f00*>(m14->slot_8());
        c17->slot_5(1, 0, 1, 1);
    }
    float c21 = callee_2684(p0, v2);
    if (c21 > 0.0f) {
        int c22 = callee_ebe8(p0);
        C251f00* c25 = static_cast<C251f00*>(p1->slot_9());
        c25->slot_42(c21, 1);
        void* v29 = gGlobalc21690_1f00;
        short c30 = callee_db3c(p0);
        M321f00* m32;
        if (static_cast<unsigned short>(c30) <= 0x6d6) {
            void* v31 = reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(v29) + 0x138)[c30];
            m32 = static_cast<M321f00*>(v31);
        } else {
            m32 = nullptr;
        }
        C351f00* c35 = static_cast<C351f00*>(m32->slot_8());
        c35->slot_5(6, c22, 1, 1);
    }
    int c39 = callee_2740(p0, v2);
    if ((c39 & 0xff) != 0) {
        void* v40 = gGlobalc21698_1f00;
        M421f00* m42;
        if (v40 != 0) {
            void* v41 = (static_cast<unsigned int>(p0) < 2 ? &reinterpret_cast<Elem1f00_3*>(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v40) + 0xb08))[static_cast<long>(static_cast<int>(p0))] : &reinterpret_cast<Elem1f00_3*>(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v40) + 0xb08))[0])->field_0;
            m42 = static_cast<M421f00*>(v41);
        } else {
            m42 = static_cast<M421f00*>(v40);
        }
        int v43 = m42->field_10;
        if (v43 != 0) {
            int v44 = m42->field_1c;
            if (v44 != 0) {
                int v45 = m42->field_28;
                if (v45 != 0) {
                    int v46 = m42->field_34;
                    int m125;
                    if (v46 != 0) {
                        int v47 = m42->field_40;
                        int m118;
                        if (v47 != 0) {
                            int v48 = m42->field_4c;
                            int m111;
                            if (v48 != 0) {
                                int v49 = m42->field_58;
                                int m104;
                                if (v49 != 0) {
                                    int v50 = m42->field_64;
                                    int m97;
                                    if (v50 != 0) {
                                        int v51 = m42->field_70;
                                        int m90;
                                        if (v51 != 0) {
                                            int v52 = m42->field_7c;
                                            int m83;
                                            if (v52 != 0) {
                                                int v53 = m42->field_88;
                                                int m76;
                                                if (v53 != 0) {
                                                    int v54 = m42->field_94;
                                                    int m69;
                                                    if (v54 != 0) {
                                                        int v55 = m42->field_a0;
                                                        int m62;
                                                        if (v55 == 0) {
                                                            void* v56 = gGlobalc21690_1f00;
                                                            C591f00* c59 = static_cast<C591f00*>(p1->slot_9());
                                                            unsigned short v60 = c59->field_24;
                                                            int c61 = callee_211dc(v56, v60, 0x1a, 1, 0, 0);
                                                            m62 = c61;
                                                        } else {
                                                            m62 = c39;
                                                        }
                                                        m69 = m62;
                                                    } else {
                                                        void* v63 = gGlobalc21690_1f00;
                                                        C661f00* c66 = static_cast<C661f00*>(p1->slot_9());
                                                        unsigned short v67 = c66->field_24;
                                                        int c68 = callee_211dc(v63, v67, 0x1a, 1, 0, 0);
                                                        m69 = c68;
                                                    }
                                                    m76 = m69;
                                                } else {
                                                    void* v70 = gGlobalc21690_1f00;
                                                    C731f00* c73 = static_cast<C731f00*>(p1->slot_9());
                                                    unsigned short v74 = c73->field_24;
                                                    int c75 = callee_211dc(v70, v74, 0x1a, 1, 0, 0);
                                                    m76 = c75;
                                                }
                                                m83 = m76;
                                            } else {
                                                void* v77 = gGlobalc21690_1f00;
                                                C801f00* c80 = static_cast<C801f00*>(p1->slot_9());
                                                unsigned short v81 = c80->field_24;
                                                int c82 = callee_211dc(v77, v81, 0x1a, 1, 0, 0);
                                                m83 = c82;
                                            }
                                            m90 = m83;
                                        } else {
                                            void* v84 = gGlobalc21690_1f00;
                                            C871f00* c87 = static_cast<C871f00*>(p1->slot_9());
                                            unsigned short v88 = c87->field_24;
                                            int c89 = callee_211dc(v84, v88, 0x1a, 1, 0, 0);
                                            m90 = c89;
                                        }
                                        m97 = m90;
                                    } else {
                                        void* v91 = gGlobalc21690_1f00;
                                        C941f00* c94 = static_cast<C941f00*>(p1->slot_9());
                                        unsigned short v95 = c94->field_24;
                                        int c96 = callee_211dc(v91, v95, 0x1a, 1, 0, 0);
                                        m97 = c96;
                                    }
                                    m104 = m97;
                                } else {
                                    void* v98 = gGlobalc21690_1f00;
                                    C1011f00* c101 = static_cast<C1011f00*>(p1->slot_9());
                                    unsigned short v102 = c101->field_24;
                                    int c103 = callee_211dc(v98, v102, 0x1a, 1, 0, 0);
                                    m104 = c103;
                                }
                                m111 = m104;
                            } else {
                                void* v105 = gGlobalc21690_1f00;
                                C1081f00* c108 = static_cast<C1081f00*>(p1->slot_9());
                                unsigned short v109 = c108->field_24;
                                int c110 = callee_211dc(v105, v109, 0x1a, 1, 0, 0);
                                m111 = c110;
                            }
                            m118 = m111;
                        } else {
                            void* v112 = gGlobalc21690_1f00;
                            C1151f00* c115 = static_cast<C1151f00*>(p1->slot_9());
                            unsigned short v116 = c115->field_24;
                            int c117 = callee_211dc(v112, v116, 0x1a, 1, 0, 0);
                            m118 = c117;
                        }
                        m125 = m118;
                    } else {
                        void* v119 = gGlobalc21690_1f00;
                        C1221f00* c122 = static_cast<C1221f00*>(p1->slot_9());
                        unsigned short v123 = c122->field_24;
                        int c124 = callee_211dc(v119, v123, 0x1a, 1, 0, 0);
                        m125 = c124;
                    }
                } else {
                    void* v126 = gGlobalc21690_1f00;
                    C1291f00* c129 = static_cast<C1291f00*>(p1->slot_9());
                    unsigned short v130 = c129->field_24;
                    callee_211dc(v126, v130, 0x1a, 1, 0, 0);
                }
            } else {
                void* v133 = gGlobalc21690_1f00;
                C1361f00* c136 = static_cast<C1361f00*>(p1->slot_9());
                unsigned short v137 = c136->field_24;
                callee_211dc(v133, v137, 0x1a, 1, 0, 0);
            }
        } else {
            void* v140 = gGlobalc21690_1f00;
            C1431f00* c143 = static_cast<C1431f00*>(p1->slot_9());
            unsigned short v144 = c143->field_24;
            callee_211dc(v140, v144, 0x1a, 1, 0, 0);
        }
    }
    int c148 = callee_27c4(p0, v2);
    if ((c148 & 0xff) != 0) {
        void* v149 = gGlobalc21698_1f00;
        Node1f00_v150* v150 = (static_cast<unsigned int>(p0) < 2 ? &reinterpret_cast<Elem1f00_4*>(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v149) + 0xb08))[static_cast<long>(static_cast<int>(p0))] : &reinterpret_cast<Elem1f00_4*>(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v149) + 0xb08))[0])->field_0;
        int v151 = v150->field_10;
        if (v151 != 1) {
            int v152 = v150->field_1c;
            if (v152 != 1) {
                int v153 = v150->field_28;
                if (v153 != 1) {
                    int v154 = v150->field_34;
                    int m233;
                    if (v154 != 1) {
                        int v155 = v150->field_40;
                        int m226;
                        if (v155 != 1) {
                            int v156 = v150->field_4c;
                            int m219;
                            if (v156 != 1) {
                                int v157 = v150->field_58;
                                int m212;
                                if (v157 != 1) {
                                    int v158 = v150->field_64;
                                    int m205;
                                    if (v158 != 1) {
                                        int v159 = v150->field_70;
                                        int m198;
                                        if (v159 != 1) {
                                            int v160 = v150->field_7c;
                                            int m191;
                                            if (v160 != 1) {
                                                int v161 = v150->field_88;
                                                int m184;
                                                if (v161 != 1) {
                                                    int v162 = v150->field_94;
                                                    int m177;
                                                    if (v162 != 1) {
                                                        int v163 = v150->field_a0;
                                                        int m170;
                                                        if (v163 == 1) {
                                                            void* v164 = gGlobalc21690_1f00;
                                                            C1671f00* c167 = static_cast<C1671f00*>(p1->slot_9());
                                                            unsigned short v168 = c167->field_24;
                                                            int c169 = callee_211dc(v164, v168, 0x1b, 1, 0, 0);
                                                            m170 = c169;
                                                        } else {
                                                            m170 = c148;
                                                        }
                                                        m177 = m170;
                                                    } else {
                                                        void* v171 = gGlobalc21690_1f00;
                                                        C1741f00* c174 = static_cast<C1741f00*>(p1->slot_9());
                                                        unsigned short v175 = c174->field_24;
                                                        int c176 = callee_211dc(v171, v175, 0x1b, 1, 0, 0);
                                                        m177 = c176;
                                                    }
                                                    m184 = m177;
                                                } else {
                                                    void* v178 = gGlobalc21690_1f00;
                                                    C1811f00* c181 = static_cast<C1811f00*>(p1->slot_9());
                                                    unsigned short v182 = c181->field_24;
                                                    int c183 = callee_211dc(v178, v182, 0x1b, 1, 0, 0);
                                                    m184 = c183;
                                                }
                                                m191 = m184;
                                            } else {
                                                void* v185 = gGlobalc21690_1f00;
                                                C1881f00* c188 = static_cast<C1881f00*>(p1->slot_9());
                                                unsigned short v189 = c188->field_24;
                                                int c190 = callee_211dc(v185, v189, 0x1b, 1, 0, 0);
                                                m191 = c190;
                                            }
                                            m198 = m191;
                                        } else {
                                            void* v192 = gGlobalc21690_1f00;
                                            C1951f00* c195 = static_cast<C1951f00*>(p1->slot_9());
                                            unsigned short v196 = c195->field_24;
                                            int c197 = callee_211dc(v192, v196, 0x1b, 1, 0, 0);
                                            m198 = c197;
                                        }
                                        m205 = m198;
                                    } else {
                                        void* v199 = gGlobalc21690_1f00;
                                        C2021f00* c202 = static_cast<C2021f00*>(p1->slot_9());
                                        unsigned short v203 = c202->field_24;
                                        int c204 = callee_211dc(v199, v203, 0x1b, 1, 0, 0);
                                        m205 = c204;
                                    }
                                    m212 = m205;
                                } else {
                                    void* v206 = gGlobalc21690_1f00;
                                    C2091f00* c209 = static_cast<C2091f00*>(p1->slot_9());
                                    unsigned short v210 = c209->field_24;
                                    int c211 = callee_211dc(v206, v210, 0x1b, 1, 0, 0);
                                    m212 = c211;
                                }
                                m219 = m212;
                            } else {
                                void* v213 = gGlobalc21690_1f00;
                                C2161f00* c216 = static_cast<C2161f00*>(p1->slot_9());
                                unsigned short v217 = c216->field_24;
                                int c218 = callee_211dc(v213, v217, 0x1b, 1, 0, 0);
                                m219 = c218;
                            }
                            m226 = m219;
                        } else {
                            void* v220 = gGlobalc21690_1f00;
                            C2231f00* c223 = static_cast<C2231f00*>(p1->slot_9());
                            unsigned short v224 = c223->field_24;
                            int c225 = callee_211dc(v220, v224, 0x1b, 1, 0, 0);
                            m226 = c225;
                        }
                        m233 = m226;
                    } else {
                        void* v227 = gGlobalc21690_1f00;
                        C2301f00* c230 = static_cast<C2301f00*>(p1->slot_9());
                        unsigned short v231 = c230->field_24;
                        int c232 = callee_211dc(v227, v231, 0x1b, 1, 0, 0);
                        m233 = c232;
                    }
                } else {
                    void* v234 = gGlobalc21690_1f00;
                    C2371f00* c237 = static_cast<C2371f00*>(p1->slot_9());
                    unsigned short v238 = c237->field_24;
                    callee_211dc(v234, v238, 0x1b, 1, 0, 0);
                }
            } else {
                void* v241 = gGlobalc21690_1f00;
                C2441f00* c244 = static_cast<C2441f00*>(p1->slot_9());
                unsigned short v245 = c244->field_24;
                callee_211dc(v241, v245, 0x1b, 1, 0, 0);
            }
        } else {
            void* v248 = gGlobalc21690_1f00;
            C2511f00* c251 = static_cast<C2511f00*>(p1->slot_9());
            unsigned short v252 = c251->field_24;
            callee_211dc(v248, v252, 0x1b, 1, 0, 0);
        }
    }
    int c256 = callee_2848(p0, v2);
    if ((c256 & 0xff) != 0) {
        void* v257 = gGlobalc21698_1f00;
        Node1f00_v258* v258 = (static_cast<unsigned int>(p0) < 2 ? &reinterpret_cast<Elem1f00_5*>(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v257) + 0xb08))[static_cast<long>(static_cast<int>(p0))] : &reinterpret_cast<Elem1f00_5*>(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v257) + 0xb08))[0])->field_0;
        int v259 = v258->field_10;
        if (v259 != 2) {
            int v260 = v258->field_1c;
            if (v260 != 2) {
                int v261 = v258->field_28;
                if (v261 != 2) {
                    int v262 = v258->field_34;
                    int m341;
                    if (v262 != 2) {
                        int v263 = v258->field_40;
                        int m334;
                        if (v263 != 2) {
                            int v264 = v258->field_4c;
                            int m327;
                            if (v264 != 2) {
                                int v265 = v258->field_58;
                                int m320;
                                if (v265 != 2) {
                                    int v266 = v258->field_64;
                                    int m313;
                                    if (v266 != 2) {
                                        int v267 = v258->field_70;
                                        int m306;
                                        if (v267 != 2) {
                                            int v268 = v258->field_7c;
                                            int m299;
                                            if (v268 != 2) {
                                                int v269 = v258->field_88;
                                                int m292;
                                                if (v269 != 2) {
                                                    int v270 = v258->field_94;
                                                    int m285;
                                                    if (v270 != 2) {
                                                        int v271 = v258->field_a0;
                                                        int m278;
                                                        if (v271 == 2) {
                                                            void* v272 = gGlobalc21690_1f00;
                                                            C2751f00* c275 = static_cast<C2751f00*>(p1->slot_9());
                                                            unsigned short v276 = c275->field_24;
                                                            int c277 = callee_211dc(v272, v276, 0x1c, 1, 0, 0);
                                                            m278 = c277;
                                                        } else {
                                                            m278 = c256;
                                                        }
                                                        m285 = m278;
                                                    } else {
                                                        void* v279 = gGlobalc21690_1f00;
                                                        C2821f00* c282 = static_cast<C2821f00*>(p1->slot_9());
                                                        unsigned short v283 = c282->field_24;
                                                        int c284 = callee_211dc(v279, v283, 0x1c, 1, 0, 0);
                                                        m285 = c284;
                                                    }
                                                    m292 = m285;
                                                } else {
                                                    void* v286 = gGlobalc21690_1f00;
                                                    C2891f00* c289 = static_cast<C2891f00*>(p1->slot_9());
                                                    unsigned short v290 = c289->field_24;
                                                    int c291 = callee_211dc(v286, v290, 0x1c, 1, 0, 0);
                                                    m292 = c291;
                                                }
                                                m299 = m292;
                                            } else {
                                                void* v293 = gGlobalc21690_1f00;
                                                C2961f00* c296 = static_cast<C2961f00*>(p1->slot_9());
                                                unsigned short v297 = c296->field_24;
                                                int c298 = callee_211dc(v293, v297, 0x1c, 1, 0, 0);
                                                m299 = c298;
                                            }
                                            m306 = m299;
                                        } else {
                                            void* v300 = gGlobalc21690_1f00;
                                            C3031f00* c303 = static_cast<C3031f00*>(p1->slot_9());
                                            unsigned short v304 = c303->field_24;
                                            int c305 = callee_211dc(v300, v304, 0x1c, 1, 0, 0);
                                            m306 = c305;
                                        }
                                        m313 = m306;
                                    } else {
                                        void* v307 = gGlobalc21690_1f00;
                                        C3101f00* c310 = static_cast<C3101f00*>(p1->slot_9());
                                        unsigned short v311 = c310->field_24;
                                        int c312 = callee_211dc(v307, v311, 0x1c, 1, 0, 0);
                                        m313 = c312;
                                    }
                                    m320 = m313;
                                } else {
                                    void* v314 = gGlobalc21690_1f00;
                                    C3171f00* c317 = static_cast<C3171f00*>(p1->slot_9());
                                    unsigned short v318 = c317->field_24;
                                    int c319 = callee_211dc(v314, v318, 0x1c, 1, 0, 0);
                                    m320 = c319;
                                }
                                m327 = m320;
                            } else {
                                void* v321 = gGlobalc21690_1f00;
                                C3241f00* c324 = static_cast<C3241f00*>(p1->slot_9());
                                unsigned short v325 = c324->field_24;
                                int c326 = callee_211dc(v321, v325, 0x1c, 1, 0, 0);
                                m327 = c326;
                            }
                            m334 = m327;
                        } else {
                            void* v328 = gGlobalc21690_1f00;
                            C3311f00* c331 = static_cast<C3311f00*>(p1->slot_9());
                            unsigned short v332 = c331->field_24;
                            int c333 = callee_211dc(v328, v332, 0x1c, 1, 0, 0);
                            m334 = c333;
                        }
                        m341 = m334;
                    } else {
                        void* v335 = gGlobalc21690_1f00;
                        C3381f00* c338 = static_cast<C3381f00*>(p1->slot_9());
                        unsigned short v339 = c338->field_24;
                        int c340 = callee_211dc(v335, v339, 0x1c, 1, 0, 0);
                        m341 = c340;
                    }
                } else {
                    void* v342 = gGlobalc21690_1f00;
                    C3451f00* c345 = static_cast<C3451f00*>(p1->slot_9());
                    unsigned short v346 = c345->field_24;
                    callee_211dc(v342, v346, 0x1c, 1, 0, 0);
                }
            } else {
                void* v349 = gGlobalc21690_1f00;
                C3521f00* c352 = static_cast<C3521f00*>(p1->slot_9());
                unsigned short v353 = c352->field_24;
                callee_211dc(v349, v353, 0x1c, 1, 0, 0);
            }
        } else {
            void* v356 = gGlobalc21690_1f00;
            C3591f00* c359 = static_cast<C3591f00*>(p1->slot_9());
            unsigned short v360 = c359->field_24;
            callee_211dc(v356, v360, 0x1c, 1, 0, 0);
        }
    }
    int c364 = callee_28cc(p0, v2);
    if ((c364 & 0xff) != 0) {
        void* v365 = gGlobalc21698_1f00;
        Node1f00_v366* v366 = (static_cast<unsigned int>(p0) < 2 ? &reinterpret_cast<Elem1f00_6*>(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v365) + 0xb08))[static_cast<long>(static_cast<int>(p0))] : &reinterpret_cast<Elem1f00_6*>(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v365) + 0xb08))[0])->field_0;
        int v367 = v366->field_10;
        if (v367 != 3) {
            int v368 = v366->field_1c;
            if (v368 != 3) {
                int v369 = v366->field_28;
                if (v369 != 3) {
                    int v370 = v366->field_34;
                    int m449;
                    if (v370 != 3) {
                        int v371 = v366->field_40;
                        int m442;
                        if (v371 != 3) {
                            int v372 = v366->field_4c;
                            int m435;
                            if (v372 != 3) {
                                int v373 = v366->field_58;
                                int m428;
                                if (v373 != 3) {
                                    int v374 = v366->field_64;
                                    int m421;
                                    if (v374 != 3) {
                                        int v375 = v366->field_70;
                                        int m414;
                                        if (v375 != 3) {
                                            int v376 = v366->field_7c;
                                            int m407;
                                            if (v376 != 3) {
                                                int v377 = v366->field_88;
                                                int m400;
                                                if (v377 != 3) {
                                                    int v378 = v366->field_94;
                                                    int m393;
                                                    if (v378 != 3) {
                                                        int v379 = v366->field_a0;
                                                        int m386;
                                                        if (v379 == 3) {
                                                            void* v380 = gGlobalc21690_1f00;
                                                            C3831f00* c383 = static_cast<C3831f00*>(p1->slot_9());
                                                            unsigned short v384 = c383->field_24;
                                                            int c385 = callee_211dc(v380, v384, 0x1d, 1, 0, 0);
                                                            m386 = c385;
                                                        } else {
                                                            m386 = c364;
                                                        }
                                                        m393 = m386;
                                                    } else {
                                                        void* v387 = gGlobalc21690_1f00;
                                                        C3901f00* c390 = static_cast<C3901f00*>(p1->slot_9());
                                                        unsigned short v391 = c390->field_24;
                                                        int c392 = callee_211dc(v387, v391, 0x1d, 1, 0, 0);
                                                        m393 = c392;
                                                    }
                                                    m400 = m393;
                                                } else {
                                                    void* v394 = gGlobalc21690_1f00;
                                                    C3971f00* c397 = static_cast<C3971f00*>(p1->slot_9());
                                                    unsigned short v398 = c397->field_24;
                                                    int c399 = callee_211dc(v394, v398, 0x1d, 1, 0, 0);
                                                    m400 = c399;
                                                }
                                                m407 = m400;
                                            } else {
                                                void* v401 = gGlobalc21690_1f00;
                                                C4041f00* c404 = static_cast<C4041f00*>(p1->slot_9());
                                                unsigned short v405 = c404->field_24;
                                                int c406 = callee_211dc(v401, v405, 0x1d, 1, 0, 0);
                                                m407 = c406;
                                            }
                                            m414 = m407;
                                        } else {
                                            void* v408 = gGlobalc21690_1f00;
                                            C4111f00* c411 = static_cast<C4111f00*>(p1->slot_9());
                                            unsigned short v412 = c411->field_24;
                                            int c413 = callee_211dc(v408, v412, 0x1d, 1, 0, 0);
                                            m414 = c413;
                                        }
                                        m421 = m414;
                                    } else {
                                        void* v415 = gGlobalc21690_1f00;
                                        C4181f00* c418 = static_cast<C4181f00*>(p1->slot_9());
                                        unsigned short v419 = c418->field_24;
                                        int c420 = callee_211dc(v415, v419, 0x1d, 1, 0, 0);
                                        m421 = c420;
                                    }
                                    m428 = m421;
                                } else {
                                    void* v422 = gGlobalc21690_1f00;
                                    C4251f00* c425 = static_cast<C4251f00*>(p1->slot_9());
                                    unsigned short v426 = c425->field_24;
                                    int c427 = callee_211dc(v422, v426, 0x1d, 1, 0, 0);
                                    m428 = c427;
                                }
                                m435 = m428;
                            } else {
                                void* v429 = gGlobalc21690_1f00;
                                C4321f00* c432 = static_cast<C4321f00*>(p1->slot_9());
                                unsigned short v433 = c432->field_24;
                                int c434 = callee_211dc(v429, v433, 0x1d, 1, 0, 0);
                                m435 = c434;
                            }
                            m442 = m435;
                        } else {
                            void* v436 = gGlobalc21690_1f00;
                            C4391f00* c439 = static_cast<C4391f00*>(p1->slot_9());
                            unsigned short v440 = c439->field_24;
                            int c441 = callee_211dc(v436, v440, 0x1d, 1, 0, 0);
                            m442 = c441;
                        }
                        m449 = m442;
                    } else {
                        void* v443 = gGlobalc21690_1f00;
                        C4461f00* c446 = static_cast<C4461f00*>(p1->slot_9());
                        unsigned short v447 = c446->field_24;
                        int c448 = callee_211dc(v443, v447, 0x1d, 1, 0, 0);
                        m449 = c448;
                    }
                } else {
                    void* v450 = gGlobalc21690_1f00;
                    C4531f00* c453 = static_cast<C4531f00*>(p1->slot_9());
                    unsigned short v454 = c453->field_24;
                    callee_211dc(v450, v454, 0x1d, 1, 0, 0);
                }
            } else {
                void* v457 = gGlobalc21690_1f00;
                C4601f00* c460 = static_cast<C4601f00*>(p1->slot_9());
                unsigned short v461 = c460->field_24;
                callee_211dc(v457, v461, 0x1d, 1, 0, 0);
            }
        } else {
            void* v464 = gGlobalc21690_1f00;
            C4671f00* c467 = static_cast<C4671f00*>(p1->slot_9());
            unsigned short v468 = c467->field_24;
            callee_211dc(v464, v468, 0x1d, 1, 0, 0);
        }
    }
    int c472 = callee_295c(p0, v2);
    if ((c472 & 0xff) != 0) {
        void* v473 = gGlobalc21698_1f00;
        Node1f00_v474* v474 = (static_cast<unsigned int>(p0) < 2 ? &reinterpret_cast<Elem1f00_7*>(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v473) + 0xb08))[static_cast<long>(static_cast<int>(p0))] : &reinterpret_cast<Elem1f00_7*>(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v473) + 0xb08))[0])->field_0;
        int v475 = v474->field_10;
        if (v475 != 6) {
            int v476 = v474->field_1c;
            if (v476 != 6) {
                int v477 = v474->field_28;
                if (v477 != 6) {
                    int v478 = v474->field_34;
                    if (v478 != 6) {
                        int v479 = v474->field_40;
                        if (v479 != 6) {
                            int v480 = v474->field_4c;
                            if (v480 != 6) {
                                int v481 = v474->field_58;
                                if (v481 != 6) {
                                    int v482 = v474->field_64;
                                    if (v482 != 6) {
                                        int v483 = v474->field_70;
                                        if (v483 != 6) {
                                            int v484 = v474->field_7c;
                                            if (v484 != 6) {
                                                int v485 = v474->field_88;
                                                if (v485 != 6) {
                                                    int v486 = v474->field_94;
                                                    if (v486 != 6) {
                                                        int v487 = v474->field_a0;
                                                        if (v487 == 6) {
                                                            void* v488 = gGlobalc21690_1f00;
                                                            C4911f00* c491 = static_cast<C4911f00*>(p1->slot_9());
                                                            unsigned short v492 = c491->field_24;
                                                            return callee_211dc(v488, v492, 0x28, 1, 0, 0);
                                                        }
                                                    } else {
                                                        void* v494 = gGlobalc21690_1f00;
                                                        C4971f00* c497 = static_cast<C4971f00*>(p1->slot_9());
                                                        unsigned short v498 = c497->field_24;
                                                        return callee_211dc(v494, v498, 0x28, 1, 0, 0);
                                                    }
                                                } else {
                                                    void* v500 = gGlobalc21690_1f00;
                                                    C5031f00* c503 = static_cast<C5031f00*>(p1->slot_9());
                                                    unsigned short v504 = c503->field_24;
                                                    return callee_211dc(v500, v504, 0x28, 1, 0, 0);
                                                }
                                            } else {
                                                void* v506 = gGlobalc21690_1f00;
                                                C5091f00* c509 = static_cast<C5091f00*>(p1->slot_9());
                                                unsigned short v510 = c509->field_24;
                                                return callee_211dc(v506, v510, 0x28, 1, 0, 0);
                                            }
                                        } else {
                                            void* v512 = gGlobalc21690_1f00;
                                            C5151f00* c515 = static_cast<C5151f00*>(p1->slot_9());
                                            unsigned short v516 = c515->field_24;
                                            return callee_211dc(v512, v516, 0x28, 1, 0, 0);
                                        }
                                    } else {
                                        void* v518 = gGlobalc21690_1f00;
                                        C5211f00* c521 = static_cast<C5211f00*>(p1->slot_9());
                                        unsigned short v522 = c521->field_24;
                                        return callee_211dc(v518, v522, 0x28, 1, 0, 0);
                                    }
                                } else {
                                    void* v524 = gGlobalc21690_1f00;
                                    C5271f00* c527 = static_cast<C5271f00*>(p1->slot_9());
                                    unsigned short v528 = c527->field_24;
                                    return callee_211dc(v524, v528, 0x28, 1, 0, 0);
                                }
                            } else {
                                void* v530 = gGlobalc21690_1f00;
                                C5331f00* c533 = static_cast<C5331f00*>(p1->slot_9());
                                unsigned short v534 = c533->field_24;
                                return callee_211dc(v530, v534, 0x28, 1, 0, 0);
                            }
                        } else {
                            void* v536 = gGlobalc21690_1f00;
                            C5391f00* c539 = static_cast<C5391f00*>(p1->slot_9());
                            unsigned short v540 = c539->field_24;
                            return callee_211dc(v536, v540, 0x28, 1, 0, 0);
                        }
                    } else {
                        void* v542 = gGlobalc21690_1f00;
                        C5451f00* c545 = static_cast<C5451f00*>(p1->slot_9());
                        unsigned short v546 = c545->field_24;
                        return callee_211dc(v542, v546, 0x28, 1, 0, 0);
                    }
                } else {
                    void* v548 = gGlobalc21690_1f00;
                    C5511f00* c551 = static_cast<C5511f00*>(p1->slot_9());
                    unsigned short v552 = c551->field_24;
                    return callee_211dc(v548, v552, 0x28, 1, 0, 0);
                }
            } else {
                void* v554 = gGlobalc21690_1f00;
                C5571f00* c557 = static_cast<C5571f00*>(p1->slot_9());
                unsigned short v558 = c557->field_24;
                return callee_211dc(v554, v558, 0x28, 1, 0, 0);
            }
        } else {
            void* v560 = gGlobalc21690_1f00;
            C5631f00* c563 = static_cast<C5631f00*>(p1->slot_9());
            unsigned short v564 = c563->field_24;
            return callee_211dc(v560, v564, 0x28, 1, 0, 0);
        }
    }
    return c472;
}

extern "C" void* memcpy(void*, const void*, unsigned long);
extern "C" void* memset(void*, int, unsigned long);

void callee_f1278(void*, long);        // 0x71000f1278
void callee_11298c(void*, long);        // 0x710011298c
int callee_115d9c(void*, long);        // 0x7100115d9c
void callee_130e2c(void*, long);        // 0x7100130e2c
int callee_16ef34();        // 0x710016ef34
void callee_16f508(int, long);        // 0x710016f508
int callee_170c58();        // 0x7100170c58
int callee_172174(int);        // 0x7100172174
int callee_1898b8(void*);        // 0x71001898b8
int callee_18d5d8(void*);        // 0x710018d5d8
int callee_18f0e0(void*);        // 0x710018f0e0
int callee_18f104(void*, int);        // 0x710018f104
void* callee_18f12c(void*);        // 0x710018f12c
void callee_18f254(int, long);        // 0x710018f254
void callee_193930(long, long);        // 0x7100193930
void callee_1940f8(long, long);        // 0x71001940f8
void callee_195d38(long, long);        // 0x7100195d38
void callee_196378(long, long);        // 0x7100196378
void callee_196888(int, long);        // 0x7100196888
void callee_19711c(long, long);        // 0x710019711c
void callee_198e8c(long, long);        // 0x7100198e8c
void callee_199630(long, long);        // 0x7100199630
void callee_19b4e8(long, long);        // 0x710019b4e8
void callee_19be70(int, long);        // 0x710019be70
void callee_1a1f20(void*, long, long);        // 0x71001a1f20
void callee_1a4b48(int, long);        // 0x71001a4b48
void callee_1a85f4(long, long);        // 0x71001a85f4
void callee_1d68ac(void*);        // 0x71001d68ac

struct Node176ce0_v1 {
    unsigned char pad0[0x95a20];
    void* field_95a20;               // +95a20
};

struct Globalc22ab0_176ce0 {
    void* field_0;               // +0
    void* field_8;               // +8
};

struct Elem176ce0_r6 {
    unsigned char pad0[0x5a0];
};

struct Elem176ce0_r43 {
    unsigned char pad0[0x50];
};

struct Elem176ce0_r89 {
    unsigned char pad0[0x160];
};

struct Elem176ce0_r93 {
    unsigned char pad0[0x6d0];
};
// Reached through the GOT slot at 0x7100c216e8.
extern Node176ce0_v1* gGlobalc216e8_176ce0;
// Reached through the GOT slot at 0x7100c22ca8.
extern void* gGlobalc22ca8_176ce0;
// Reached through the GOT slot at 0x7100c21698.
extern void* gGlobalc21698_176ce0;
// Reached through the GOT slot at 0x7100c22a60.
extern void* gGlobalc22a60_176ce0;
// Reached through the GOT slot at 0x7100c22be8.
extern void* gGlobalc22be8_176ce0;
// Reached through the GOT slot at 0x7100c22ab0.
extern Globalc22ab0_176ce0 gGlobalc22ab0_176ce0;
// Reached through the GOT slot at 0x7100c22a70.
extern void* gGlobalc22a70_176ce0;

// 0x7100176ce0: void; the output buffer is a byte pointer, so its member addresses are GEP offsets that constant hoisting leaves alone, and the copy loops step their two pointers with a 64-bit count
void call_176ce0(unsigned char* p0) {
    memset(reinterpret_cast<void*>(p0), 0, 0x40b40);
    Node176ce0_v1* v1 = gGlobalc216e8_176ce0;
    int c2 = callee_16ef34();
    callee_16f508(c2, reinterpret_cast<long>(p0));
    void* v4 = gGlobalc22ca8_176ce0;
    callee_1d68ac(v4);
    {
        unsigned char* a = reinterpret_cast<unsigned char*>(v1) + 0x99dc0;
        unsigned char* b = p0 + 0x1f4a8;
        for (long i = 0; i < 0x80; i++) {
            callee_193930(reinterpret_cast<long>(a), reinterpret_cast<long>(b));
            a += 0x5a0;
            b += 0x16;
        }
    }
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcee40), reinterpret_cast<long>(p0 + 0x1ffa8));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcf150), reinterpret_cast<long>(p0 + 0x1ffe0));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcf460), reinterpret_cast<long>(p0 + 0x20018));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcf770), reinterpret_cast<long>(p0 + 0x20050));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcfa80), reinterpret_cast<long>(p0 + 0x20088));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcfd90), reinterpret_cast<long>(p0 + 0x200c0));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd00a0), reinterpret_cast<long>(p0 + 0x200f8));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd03b0), reinterpret_cast<long>(p0 + 0x20130));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd06c0), reinterpret_cast<long>(p0 + 0x20168));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd09d0), reinterpret_cast<long>(p0 + 0x201a0));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd0ce0), reinterpret_cast<long>(p0 + 0x201d8));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd0ff0), reinterpret_cast<long>(p0 + 0x20210));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd1300), reinterpret_cast<long>(p0 + 0x20248));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd1610), reinterpret_cast<long>(p0 + 0x20280));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd1920), reinterpret_cast<long>(p0 + 0x202b8));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd1c30), reinterpret_cast<long>(p0 + 0x202f0));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd1f40), reinterpret_cast<long>(p0 + 0x20328));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd2250), reinterpret_cast<long>(p0 + 0x20360));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd2560), reinterpret_cast<long>(p0 + 0x20398));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd2870), reinterpret_cast<long>(p0 + 0x203d0));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd2b80), reinterpret_cast<long>(p0 + 0x20408));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd2e90), reinterpret_cast<long>(p0 + 0x20440));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd31a0), reinterpret_cast<long>(p0 + 0x20478));
    callee_195d38(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd34b0), reinterpret_cast<long>(p0 + 0x204b0));
    callee_196378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd37c0), reinterpret_cast<long>(p0 + 0x204e8));
    callee_196378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd37f0), reinterpret_cast<long>(p0 + 0x204e9));
    callee_196378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd3820), reinterpret_cast<long>(p0 + 0x204ea));
    callee_196378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd3850), reinterpret_cast<long>(p0 + 0x204eb));
    callee_196378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd3880), reinterpret_cast<long>(p0 + 0x204ec));
    callee_196378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd38b0), reinterpret_cast<long>(p0 + 0x204ed));
    callee_196378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd38e0), reinterpret_cast<long>(p0 + 0x204ee));
    callee_196378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd3910), reinterpret_cast<long>(p0 + 0x204ef));
    callee_196378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd3940), reinterpret_cast<long>(p0 + 0x204f0));
    callee_196378(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xd3970), reinterpret_cast<long>(p0 + 0x204f1));
    {
        unsigned char* a = reinterpret_cast<unsigned char*>(v1) + 0xd39a0;
        unsigned char* b = p0 + 0x204f2;
        for (long i = 0; i < 0x40; i++) {
            callee_198e8c(reinterpret_cast<long>(a), reinterpret_cast<long>(b));
            a += 0x50;
            b += 0x2;
        }
    }
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcedc0), reinterpret_cast<long>(p0 + 0x20572));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcedc5), reinterpret_cast<long>(p0 + 0x20575));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcedca), reinterpret_cast<long>(p0 + 0x20578));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcedcf), reinterpret_cast<long>(p0 + 0x2057b));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcedd4), reinterpret_cast<long>(p0 + 0x2057e));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcedd9), reinterpret_cast<long>(p0 + 0x20581));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcedde), reinterpret_cast<long>(p0 + 0x20584));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcede3), reinterpret_cast<long>(p0 + 0x20587));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcede8), reinterpret_cast<long>(p0 + 0x2058a));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xceded), reinterpret_cast<long>(p0 + 0x2058d));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcedf2), reinterpret_cast<long>(p0 + 0x20590));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcedf7), reinterpret_cast<long>(p0 + 0x20593));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcedfc), reinterpret_cast<long>(p0 + 0x20596));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcee01), reinterpret_cast<long>(p0 + 0x20599));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcee06), reinterpret_cast<long>(p0 + 0x2059c));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcee0b), reinterpret_cast<long>(p0 + 0x2059f));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcee10), reinterpret_cast<long>(p0 + 0x205a2));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcee15), reinterpret_cast<long>(p0 + 0x205a5));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcee1a), reinterpret_cast<long>(p0 + 0x205a8));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcee1f), reinterpret_cast<long>(p0 + 0x205ab));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcee24), reinterpret_cast<long>(p0 + 0x205ae));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcee29), reinterpret_cast<long>(p0 + 0x205b1));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcee2e), reinterpret_cast<long>(p0 + 0x205b4));
    callee_19b4e8(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0xcee33), reinterpret_cast<long>(p0 + 0x205b7));
    int c70 = callee_18f104(v1, 0);
    callee_196888(c70, reinterpret_cast<long>(p0 + 0x205ba));
    int c72 = callee_18f104(v1, 1);
    callee_196888(c72, reinterpret_cast<long>(p0 + 0x205be));
    int c74 = callee_18f104(v1, 2);
    callee_196888(c74, reinterpret_cast<long>(p0 + 0x205c2));
    int c76 = callee_18f104(v1, 3);
    callee_196888(c76, reinterpret_cast<long>(p0 + 0x205c6));
    int c78 = callee_18f104(v1, 4);
    callee_196888(c78, reinterpret_cast<long>(p0 + 0x205ca));
    int c80 = callee_18d5d8(v1);
    callee_1a4b48(c80, reinterpret_cast<long>(p0 + 0x205d0));
    int c82 = callee_18f0e0(v1);
    callee_18f254(c82, reinterpret_cast<long>(p0 + 0x40130));
    void* c84 = callee_18f12c(v1);
    memcpy(p0 + 0x394a0, c84, 0x6c84);
    callee_19711c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0x278), reinterpret_cast<long>(p0 + 0x22388));
    callee_19711c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0x5b0), reinterpret_cast<long>(p0 + 0x22492));
    callee_19711c(reinterpret_cast<long>(reinterpret_cast<unsigned char*>(v1) + 0x8e8), reinterpret_cast<long>(p0 + 0x2259c));
    {
        unsigned char* a = reinterpret_cast<unsigned char*>(v1) + 0xc20;
        unsigned char* b = p0 + 0x226a8;
        for (long i = 0; i < 0xf6; i++) {
            callee_1940f8(reinterpret_cast<long>(a), reinterpret_cast<long>(b));
            a += 0x160;
            b += 0x7c;
        }
    }
    {
        unsigned char* a = reinterpret_cast<unsigned char*>(v1) + 0x15e60;
        unsigned char* b = p0 + 0x29dd0;
        for (long i = 0; i < 0x12c; i++) {
            callee_199630(reinterpret_cast<long>(a), reinterpret_cast<long>(b));
            a += 0x6d0;
            b += 0xb0;
        }
    }
    int n = callee_170c58();
    if (n != 0) {
        void** src = &v1->field_95a20;
        unsigned char* b = p0 + 0x36c10;
        long off = 0;
        int i = 0;
        do {
            long a = (callee_172174(i) & 0xff) != 0 ? 0 : reinterpret_cast<long>(reinterpret_cast<unsigned char*>(*src) + off);
            callee_1a85f4(a, reinterpret_cast<long>(b));
            b += 0x28;
            i++;
            off += 0x3c;
        } while (n != i);
    }
    void* v106 = gGlobalc21698_176ce0;
    callee_1a1f20(v106, reinterpret_cast<long>(p0 + 0x38ce0), reinterpret_cast<long>(p0 + 0x38e60));
    void* v108 = gGlobalc22a60_176ce0;
    callee_11298c(v108, reinterpret_cast<long>(p0 + 0x40190));
    void* v110 = gGlobalc22be8_176ce0;
    callee_f1278(v110, reinterpret_cast<long>(p0 + 0x4056c));
    int c112 = callee_1898b8(v1);
    callee_19be70(c112, reinterpret_cast<long>(p0 + 0x40948));
    void* v114 = gGlobalc22ab0_176ce0.field_0;
    callee_130e2c(v114, reinterpret_cast<long>(p0 + 0x40b28));
    void* v116 = gGlobalc22ab0_176ce0.field_8;
    callee_130e2c(v116, reinterpret_cast<long>(p0 + 0x40b30));
    void* v118 = gGlobalc22a70_176ce0;
    callee_115d9c(v118, reinterpret_cast<long>(p0 + 0x40b38));
}

struct Rec14_11298c {
    int v[5];
};

struct Rec18_11298c {
    int v[6];
};

struct Name1d_11298c {
    char s[0x1d];
};

struct Named20_11298c {
    Name1d_11298c name;
    unsigned char pad1d[3];
};

struct Src11298c {
    unsigned char pad0[0x1164];
    int count;                       // +1164
    Rec14_11298c recs[32];           // +1168
    unsigned char pad13e8[0x510];
    Named20_11298c names[10];        // +18f8
    Rec18_11298c last;               // +1a38
};

struct Dst11298c {
    int count;                       // +0
    Rec14_11298c recs[32];           // +4
    Rec18_11298c last;               // +284
    Named20_11298c names[10];        // +29c
};

// 0x710011298c: a save copier: an int, then struct-assignment loops (20-byte records, a 24-byte block, 29-byte names at a 0x20 stride) that Clang unrolls into inline copies
void call_11298c(Src11298c* p0, Dst11298c* p1) {
    p1->count = p0->count;
    for (int i = 0; i < 32; i++) {
        p1->recs[i] = p0->recs[i];
    }
    p1->last = p0->last;
    for (int i = 0; i < 10; i++) {
        p1->names[i].name = p0->names[i].name;
    }
}



struct Srcf1278 {
    unsigned char pad0[0x44f60];
    int count;                       // +44f60
    Rec14_11298c recs[32];           // +44f64
    Named20_11298c names[10];        // +451e4
    Rec18_11298c last;               // +45324
};

// 0x71000f1278: the same save copier as 11298c for another source object, whose names follow the records directly
void call_f1278(Srcf1278* p0, Dst11298c* p1) {
    p1->count = p0->count;
    for (int i = 0; i < 32; i++) {
        p1->recs[i] = p0->recs[i];
    }
    p1->last = p0->last;
    for (int i = 0; i < 10; i++) {
        p1->names[i].name = p0->names[i].name;
    }
}

struct RecC0_1a4b48 {
    unsigned char pad0[0xa8];
    unsigned char field_a8;          // +a8
    unsigned char pada9[7];
    void* field_b0;                  // +b0
    unsigned char padb8[8];
};

struct Obj10_1a4b48 {
    unsigned char b[0x10];
};

struct Pair_1a4b48 {
    int v[4];
};

struct Str8a_1a4b48 {
    char s[0x8a];
};

struct StrC3_1a4b48 {
    char s[0xc3];
};

struct Str27_1a4b48 {
    char s[0x27];
};

struct Str10_1a4b48 {
    char s[0x10];
};

struct Rec24_1a4b48 {
    int field_0;                     // +0
    unsigned char pad4[4];
    int field_8;                     // +8
    unsigned char padc[0xc];
    unsigned short field_18;         // +18
    unsigned short field_1a;         // +1a
    unsigned char field_1c;          // +1c
    unsigned char pad1d;
    unsigned short field_1e;         // +1e
    unsigned short field_20;         // +20
    unsigned char pad22[2];
};

struct __attribute__((packed)) TailSrc_1a4b48 {
    unsigned char field_0;           // +0
    unsigned char field_1;           // +1
    unsigned char field_2;           // +2
    Str10_1a4b48 name;               // +3
    unsigned char field_13;          // +13
    unsigned char field_14;          // +14
    unsigned short field_15;         // +15
    unsigned char field_17;          // +17
    unsigned char field_18;          // +18
    unsigned char field_19;          // +19
    unsigned char field_1a;          // +1a
};

struct __attribute__((packed)) TailDst_1a4b48 {
    unsigned char field_0;           // +0
    unsigned char field_1;           // +1
    unsigned char field_2;           // +2
    Str10_1a4b48 name;               // +3
    unsigned char field_13;          // +13
    unsigned char field_14;          // +14
    unsigned short field_15;         // +15
    unsigned char field_17;          // +17
    unsigned char field_18;          // +18
    unsigned char field_19;          // +19
};

struct Src1a4b48 {
    RecC0_1a4b48 recs[34];           // +0
    Obj10_1a4b48 objs[2];            // +1980
    unsigned char pad19a0[0x30];
    int field_19d0;                  // +19d0
    int field_19d4;                  // +19d4
    int field_19d8;                  // +19d8
    int field_19dc;                  // +19dc
    int field_19e0;                  // +19e0
    int field_19e4;                  // +19e4
    int field_19e8;                  // +19e8
    int field_19ec;                  // +19ec
    unsigned char pad19f0[0x3e8];
    Str8a_1a4b48 str8a;              // +1dd8
    StrC3_1a4b48 strc3;              // +1e62
    Str27_1a4b48 str27;              // +1f25
    unsigned char field_1f4c;        // +1f4c
    unsigned char field_1f4d;        // +1f4d
    unsigned short field_1f4e;       // +1f4e
    unsigned short field_1f50;       // +1f50
    unsigned char pad1f52[2];
    Pair_1a4b48 pairs[32];           // +1f54
    Rec24_1a4b48 rec24[4];           // +2154
    unsigned char pad21e4[0x27c];
    TailSrc_1a4b48 tail;             // +2460
};

struct Dst1a4b48 {
    RecC0_1a4b48 recs[34];           // +0
    Pair_1a4b48 pairs[32];           // +1980
    int field_1b80;                  // +1b80
    unsigned short field_1b84;       // +1b84
    unsigned short field_1b86;       // +1b86
    short field_1b88;                // +1b88
    short field_1b8a;                // +1b8a
    unsigned char field_1b8c;        // +1b8c
    unsigned char field_1b8d;        // +1b8d
    unsigned short field_1b8e;       // +1b8e
    unsigned char field_1b90;        // +1b90
    unsigned char field_1b91;        // +1b91
    unsigned char field_1b92;        // +1b92
    unsigned char field_1b93;        // +1b93
    Str8a_1a4b48 str8a;              // +1b94
    StrC3_1a4b48 strc3;              // +1c1e
    Str27_1a4b48 str27;              // +1ce1
    Rec24_1a4b48 rec24[4];           // +1d08
    TailDst_1a4b48 tail;             // +1d98
};

// Reached through the GOT slot at 0x7100c22d90.
extern void* gGlobalc22d90_1a4b48;
int callee_3f50e8(void*);                                                    // 0x71003f50e8

// 0x71001a4b48: a save copier: struct-assignment loops (0xc0-byte records through memcpy, 16-byte pairs inline), three odd-sized strings, fields narrowed in source order, one id looked up when it is 800, a packed tail
void call_1a4b48(Src1a4b48* p0, Dst1a4b48* p1) {
    for (int i = 0; i < 34; i++) {
        p1->recs[i] = p0->recs[i];
    }
    for (int i = 0; i < 32; i++) {
        p1->pairs[i] = p0->pairs[i];
    }
    p1->str8a = p0->str8a;
    p1->strc3 = p0->strc3;
    p1->str27 = p0->str27;
    p1->field_1b84 = p0->field_1f4e;
    p1->field_1b86 = p0->field_1f50;
    p1->field_1b88 = p0->field_19e0;
    p1->field_1b8c = p0->field_19dc;
    p1->field_1b80 = p0->field_19e4;
    p1->field_1b8a = p0->field_19e8;
    p1->field_1b91 = p0->field_19ec;
    p1->field_1b92 = p0->field_1f4c;
    p1->field_1b93 = p0->field_1f4d;
    p1->field_1b8d = p0->field_19d4;
    p1->field_1b90 = p0->field_19d8;
    int v = p0->field_19d0;
    if (v == 0x320) {
        v = callee_3f50e8(gGlobalc22d90_1a4b48);
    }
    p1->field_1b8e = v;
    for (int i = 0; i < 4; i++) {
        p1->rec24[i].field_0 = p0->rec24[i].field_0;
        p1->rec24[i].field_8 = p0->rec24[i].field_8;
        p1->rec24[i].field_18 = p0->rec24[i].field_18;
        p1->rec24[i].field_1e = p0->rec24[i].field_1e;
        p1->rec24[i].field_20 = p0->rec24[i].field_20;
        p1->rec24[i].field_1c = p0->rec24[i].field_1c;
        p1->rec24[i].field_1a = p0->rec24[i].field_1a;
    }
    p1->tail.field_0 = p0->tail.field_0;
    p1->tail.field_1 = p0->tail.field_1;
    p1->tail.field_2 = p0->tail.field_2;
    p1->tail.name = p0->tail.name;
    p1->tail.field_13 = p0->tail.field_13;
    p1->tail.field_14 = p0->tail.field_14;
    p1->tail.field_15 = p0->tail.field_15;
    p1->tail.field_17 = p0->tail.field_17;
    p1->tail.field_18 = p0->tail.field_19;
    p1->tail.field_19 = p0->tail.field_1a;
}


struct Elem1e0_20e224 {
    unsigned char b[0x1e0];
};

struct Table_20e224 {
    Elem1e0_20e224 entries[128];
};

// 0x710020e224: clears a 0x50-byte block in each of 128 table entries; the range-based for over the member array has a body cheap enough that Clang unrolls all 128 iterations, the last memset becoming a tail call
void call_20e224(Table_20e224* p0) {
    for (Elem1e0_20e224& e : p0->entries) {
        memset(e.b + 0x190, 0, 0x50);
    }
}

class Arc25b394 {
public:
    Arc25b394();                                                             // 0x710025b394
    ~Arc25b394();                                                            // 0x710025b3ac
    void open(int, int, void*);                                              // 0x710025b4b4
    unsigned char isOpen();                                                           // 0x710025b46c
    void* entry(int);                                                        // 0x710025b738
    void close();                                                            // 0x710025b40c

    unsigned char pad[0x28];
};

class Tmp218c18 {
public:
    Tmp218c18();                                                             // 0x7100218c18
    ~Tmp218c18();                                                            // 0x7100218c2c
    void set(void*);                                                         // 0x7100218c34
    int size();                                                              // 0x71002192c0
    void* data(int, int);                                                    // 0x7100218cac
    void release(int);                                                       // 0x7100218c68

    unsigned char pad[0x10];
};

class Obj1fbbb0 {
public:
    Obj1fbbb0();                                                             // 0x71001fbbb0
    ~Obj1fbbb0();                                                            // 0x71001fbbd0
    void init(int, int, void*);                                              // 0x71001fbc04
    void reset();                                                            // 0x71001fbbf0

    unsigned char pad[0x20];
};

struct Unit1f9a98 {
    unsigned char pad0[4];
    unsigned short field_4;          // +4
    unsigned char pad6[0x2c];
    short field_32;                  // +32
    unsigned char pad34[0x1c];
};

struct Mgr1f9a98 {
    unsigned char pad0[4];
    int field_4;                     // +4
    long field_8;                    // +8
    int field_10;                    // +10
    long field_14 __attribute__((packed));    // +14
};

struct This1f9a98 {
    unsigned char pad0[0x20];
    short field_20[100];             // +20
    short field_e8[100];             // +e8
};

// Reached through the GOT slot at 0x7100c21df8.
extern Mgr1f9a98* gGlobalc21df8_1f9a98;
// Reached through the GOT slot at 0x7100c216a0.
extern Unit1f9a98* gGlobalc216a0_1f9a98;

void* callee_20bd74();                                                       // 0x710020bd74
void callee_20bfc0(void*);                                                   // 0x710020bfc0
void callee_20c168(void*);                                                   // 0x710020c168
void* callee_204728();                                                       // 0x7100204728
void callee_204aac(void*);                                                   // 0x7100204aac
void callee_204c5c(void*);                                                   // 0x7100204c5c
void* callee_216d48();                                                       // 0x7100216d48
void callee_216f14(void*);                                                   // 0x7100216f14
void callee_216f9c(void*);                                                   // 0x7100216f9c
void callee_2014f4(void*);                                                   // 0x71002014f4
void callee_20a4fc(void*);                                                   // 0x710020a4fc
void* callee_1feb28();                                                       // 0x71001feb28
void callee_1feec4(void*);                                                   // 0x71001feec4
void callee_1fb14c();                                                        // 0x71001fb14c
void callee_20f3ec(void*, void*);                                            // 0x710020f3ec
void* callee_d86c4();        // 0x71000d86c4
void* callee_1fe7c8();        // 0x71001fe7c8
void* callee_1ff050();        // 0x71001ff050
void* callee_200fc0();        // 0x7100200fc0
void* callee_201604();        // 0x7100201604
void* callee_204ca8();        // 0x7100204ca8
void* callee_20710c();        // 0x710020710c
void* callee_2074c0();        // 0x71002074c0
void* callee_208a70();        // 0x7100208a70
void* callee_209a34();        // 0x7100209a34
void* callee_209cb4();        // 0x7100209cb4
void* callee_20a31c();        // 0x710020a31c
void* callee_20acb0();        // 0x710020acb0
void* callee_20b29c();        // 0x710020b29c
void* callee_20b3d8();        // 0x710020b3d8
void* callee_20b60c();        // 0x710020b60c
void* callee_20b970();        // 0x710020b970
void* callee_20c630();        // 0x710020c630
void* callee_20c72c();        // 0x710020c72c
void* callee_20dfd0();        // 0x710020dfd0
void* callee_20ec80();        // 0x710020ec80
void* callee_20ef00();        // 0x710020ef00
void* callee_20f130();        // 0x710020f130
void* callee_210328();        // 0x7100210328
void* callee_21069c();        // 0x710021069c
void* callee_214000();        // 0x7100214000
void* callee_214890();        // 0x7100214890
void* callee_214b80();        // 0x7100214b80
void* callee_214d88();        // 0x7100214d88
void* callee_2151a0();        // 0x71002151a0
void* callee_215468();        // 0x7100215468
void* callee_215b84();        // 0x7100215b84
void callee_d8770(void*, Obj1fbbb0*);        // 0x71000d8770
void callee_1fea4c(void*, Obj1fbbb0*);        // 0x71001fea4c
void callee_1fea98(void*, Obj1fbbb0*);        // 0x71001fea98
void callee_1ff0fc(void*, Obj1fbbb0*);        // 0x71001ff0fc
void callee_2013bc(void*, Obj1fbbb0*);        // 0x71002013bc
void callee_201424(void*, Obj1fbbb0*);        // 0x7100201424
void callee_2016d4(void*, Obj1fbbb0*);        // 0x71002016d4
void callee_204d54(void*, Obj1fbbb0*);        // 0x7100204d54
void callee_204f60(void*, Obj1fbbb0*);        // 0x7100204f60
void callee_2050ac(void*, Obj1fbbb0*);        // 0x71002050ac
void callee_20519c(void*, Obj1fbbb0*);        // 0x710020519c
void callee_205268(void*, Obj1fbbb0*);        // 0x7100205268
void callee_2053c4(void*, Obj1fbbb0*);        // 0x71002053c4
void callee_207068(void*, Obj1fbbb0*);        // 0x7100207068
void callee_2070b4(void*, Obj1fbbb0*);        // 0x71002070b4
void callee_20747c(void*, Obj1fbbb0*);        // 0x710020747c
void callee_208a18(void*, Obj1fbbb0*);        // 0x7100208a18
void callee_2099a0(void*, Obj1fbbb0*);        // 0x71002099a0
void callee_209bf0(void*, Obj1fbbb0*);        // 0x7100209bf0
void callee_20a46c(void*, Obj1fbbb0*);        // 0x710020a46c
void callee_20ad5c(void*, Obj1fbbb0*);        // 0x710020ad5c
void callee_20ae40(void*, Obj1fbbb0*);        // 0x710020ae40
void callee_20af5c(void*, Obj1fbbb0*);        // 0x710020af5c
void callee_20afb8(void*, Obj1fbbb0*);        // 0x710020afb8
void callee_20b0d4(void*, Obj1fbbb0*);        // 0x710020b0d4
void callee_20b344(void*, Obj1fbbb0*);        // 0x710020b344
void callee_20b488(void*, Obj1fbbb0*);        // 0x710020b488
void callee_20b6ec(void*, Obj1fbbb0*);        // 0x710020b6ec
void callee_20ba1c(void*, Obj1fbbb0*);        // 0x710020ba1c
void callee_20c5b4(void*, Obj1fbbb0*);        // 0x710020c5b4
void callee_20c780(void*, Obj1fbbb0*);        // 0x710020c780
void callee_20dd84(void*, Obj1fbbb0*);        // 0x710020dd84
void callee_20de00(void*, Obj1fbbb0*);        // 0x710020de00
void callee_20de7c(void*, Obj1fbbb0*);        // 0x710020de7c
void callee_20def8(void*, Obj1fbbb0*);        // 0x710020def8
void callee_20f014(void*, Obj1fbbb0*);        // 0x710020f014
void callee_20f2cc(void*, Obj1fbbb0*);        // 0x710020f2cc
void callee_2103e8(void*, Obj1fbbb0*);        // 0x71002103e8
void callee_21082c(void*, Obj1fbbb0*);        // 0x710021082c
void callee_211118(void*, Obj1fbbb0*);        // 0x7100211118
void callee_2141b4(void*, Obj1fbbb0*);        // 0x71002141b4
void callee_214a5c(void*, Obj1fbbb0*);        // 0x7100214a5c
void callee_214c78(void*, Obj1fbbb0*);        // 0x7100214c78
void callee_214e40(void*, Obj1fbbb0*);        // 0x7100214e40
void callee_215308(void*, Obj1fbbb0*);        // 0x7100215308
void callee_2158c0(void*, Obj1fbbb0*);        // 0x71002158c0
void callee_215cf0(void*, Obj1fbbb0*);        // 0x7100215cf0

// 0x71001f9a98: a loader: three archives, a staging buffer and a load object as locals with destructors, fifty entries loaded and handed on (the archive indexes the block keeps in callee-saved registers come out by themselves), then a search of the unit table whose unsigned counter indexes as int, which keeps it unrolled by 2
void call_1f9a98(This1f9a98* p0) {
    if (gGlobalc21df8_1f9a98 == nullptr) {
        return;
    }
    Arc25b394 a0;
    Arc25b394 a1;
    Arc25b394 a2;
    Tmp218c18 tmp;
    Obj1fbbb0 obj;
    callee_20bfc0(callee_20bd74());
    callee_204aac(callee_204728());
    callee_216f14(callee_216d48());
    a0.open(0, 0, nullptr);
    if (!a0.isOpen()) {
        return;
    }
    a1.open(0, 1, nullptr);
    if (!a1.isOpen()) {
        return;
    }
    a2.open(0, 2, nullptr);
    if (!a2.isOpen()) {
        return;
    }
    tmp.set(a1.entry(0));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_211118(gGlobalc216a0_1f9a98, &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(0));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_2013bc(callee_200fc0(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(1));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_201424(callee_200fc0(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(2));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_2016d4(callee_201604(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(9));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20ad5c(callee_20acb0(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(10));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20ae40(callee_20acb0(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(11));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20af5c(callee_20acb0(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(12));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20afb8(callee_20acb0(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(13));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20b0d4(callee_20acb0(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(14));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_1fea4c(callee_1fe7c8(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(15));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_1fea98(callee_1fe7c8(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(3));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_2141b4(callee_214000(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(4));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_214a5c(callee_214890(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(5));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_214c78(callee_214b80(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(6));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_214e40(callee_214d88(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(7));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_215308(callee_2151a0(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(8));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_2158c0(callee_215468(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a1.entry(1));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20def8(callee_20dfd0(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a1.entry(2));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20def8(callee_20ec80(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a1.entry(3));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20dd84(callee_20ec80(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a1.entry(4));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20de00(callee_20ec80(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a1.entry(5));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20f014(callee_20ef00(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(16));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20a46c(callee_20a31c(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(17));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20c780(callee_20c72c(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(18));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20ba1c(callee_20b970(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(19));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20b488(callee_20b3d8(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(20));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20b6ec(callee_20b60c(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(21));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_2103e8(callee_210328(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(22));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_215cf0(callee_215b84(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(23));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20b344(callee_20b29c(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(24));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_204d54(callee_204ca8(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(25));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_204f60(callee_204ca8(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(26));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_2050ac(callee_204ca8(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(27));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20519c(callee_204ca8(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(28));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_205268(callee_204ca8(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(29));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_2053c4(callee_204ca8(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a2.entry(0));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_207068(callee_20710c(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a2.entry(1));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_2070b4(callee_20710c(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a2.entry(2));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_208a18(callee_208a70(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a2.entry(3));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_209bf0(callee_209cb4(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a2.entry(4));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20c5b4(callee_20c630(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a2.entry(5));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_2099a0(callee_209a34(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a2.entry(6));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20747c(callee_2074c0(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a0.entry(30));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_1ff0fc(callee_1ff050(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a1.entry(6));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20de7c(callee_20dfd0(), &obj);
    callee_20de7c(callee_20ec80(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a1.entry(7));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_21082c(callee_21069c(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a1.entry(8));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20dd84(callee_20dfd0(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a1.entry(9));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20de00(callee_20dfd0(), &obj);
    obj.reset();
    tmp.release(0);
    tmp.set(a1.entry(10));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_20f2cc(callee_20f130(), &obj);
    obj.reset();
    tmp.release(0);
    callee_20f3ec(callee_20f130(), a1.entry(11));
    tmp.set(a1.entry(12));
    obj.init(1, tmp.size(), tmp.data(0, 0));
    callee_d8770(callee_d86c4(), &obj);
    obj.reset();
    tmp.release(0);
    a0.close();
    a1.close();
    a2.close();
    callee_1feec4(callee_1feb28());
    Unit1f9a98* units = gGlobalc216a0_1f9a98;
    for (unsigned int i = 0; i < 100; i++) {
        p0->field_20[i] = -1;
        p0->field_e8[i] = -1;
        for (unsigned int j = 0; j < 0x44c; j++) {
            if (static_cast<unsigned int>(units[static_cast<int>(j)].field_32) == i) {
                p0->field_20[i] = j;
                p0->field_e8[i] = units[static_cast<int>(j)].field_4;
                break;
            }
        }
    }
    callee_1fb14c();
    Mgr1f9a98* m = gGlobalc21df8_1f9a98;
    m->field_4 = 0x15102600;
    m->field_8 = 0;
    m->field_10 = 0x15102600;
    m->field_14 = 0;
    callee_20c168(callee_20bd74());
    callee_204c5c(callee_204728());
    callee_2014f4(callee_200fc0());
    callee_216f9c(callee_216d48());
    callee_20a4fc(callee_20a31c());
}



struct R24_19c9a4 {
    unsigned char b[0x24];
};

struct R58_19c9a4 {
    unsigned char b[0x58];
};

struct R68_19c9a4 {
    unsigned char b[0x68];
};

struct P10_19c9a4 {
    int v[4];
};

struct R6c_19c9a4 {
    unsigned char b[0x6c];
};

struct V2_19c9a4 {
    float x, y;
};

struct V3_19c9a4 {
    float x, y, z;
};

struct R18_19c9a4 {
    V2_19c9a4 a;                     // +0
    int b;                           // +8
    V3_19c9a4 c;                     // +c
};

struct B4d0_19c9a4 {
    unsigned char b[0x4d0];
};

struct Obj19c9a4 {
    R24_19c9a4 r24[3];               // +0
    R58_19c9a4 objs[120];            // +6c
    P10_19c9a4 pairs[64];            // +29ac
    R6c_19c9a4 recs[24];             // +2dac
    R18_19c9a4 a18[5];               // +37cc
    R18_19c9a4 b18[15];              // +3844
    B4d0_19c9a4 block;               // +39ac
};

void callee_19b6c4(R58_19c9a4*, R68_19c9a4*);                                // 0x710019b6c4

// 0x710019c9a4: a copier with eight sources: memcpy records written with the source address taken first (as the original sets x1 before x0), a per-element call loop, 16-byte pairs, and {pair, int, triple} records copied member by member, the fifteen-record run as a range-based for so that Clang unrolls it fully
void call_19c9a4(Obj19c9a4* p0, R24_19c9a4* p1, R68_19c9a4* p2, P10_19c9a4* p3, R6c_19c9a4* p4, R18_19c9a4* p5, void* p6, B4d0_19c9a4* p7) {
    for (int i = 0; i < 3; i++) {
        const void* s = &p1[i];
        void* d = &p0->r24[i];
        memcpy(d, s, sizeof(R24_19c9a4));
    }
    for (int i = 0; i < 120; i++) {
        callee_19b6c4(&p0->objs[i], &p2[i]);
    }
    for (int i = 0; i < 64; i++) {
        const P10_19c9a4& s = p3[i];
        p0->pairs[i] = s;
    }
    for (int i = 0; i < 24; i++) {
        const void* s = &p4[i];
        void* d = &p0->recs[i];
        memcpy(d, s, sizeof(R6c_19c9a4));
    }
    for (int i = 0; i < 5; i++) {
        const R18_19c9a4& s = p5[i];
        p0->a18[i].a = s.a;
        p0->a18[i].b = s.b;
        p0->a18[i].c = s.c;
    }
    Tmp218c18 tmp;
    tmp.set(p6);
    R18_19c9a4* d = static_cast<R18_19c9a4*>(tmp.data(0, 0));
    const R18_19c9a4* s = d;
    for (R18_19c9a4& r : p0->b18) {
        r.a = s->a;
        r.b = s->b;
        r.c = s->c;
        s++;
    }
    p0->block = *p7;
}

#include "event/demo_effects.h"
#include "event/demo_light_system.h"
#include "event/layout_panes.h"

class TextRenderer {
public:
    void set_area(TrackVec2* pos, TrackVec2* size, int a, int b, int c);    // 0x71001e709c
    unsigned int draw(void* dest, const char* text, int line, int a, int alpha, float x,
                      float y);                                             // 0x71001e73c0

    unsigned char pad[0x20b98];
    int align;                // +20b98
    unsigned char pad20b9c[0x2d];
    unsigned char wrap;       // +20bc9
};
// Reached through the GOT slot at 0x7100c22a30.
extern TextRenderer* gTextRenderer;

struct SharedState {
    int value0;
    int language;             // +04
};
SharedState* get_shared_state();                                            // 0x71002aae3c
const char* message_text(int id);                                           // 0x7100217d64
void set_pane_lines(PanelPane* pane, TrackLightTarget* lines, unsigned int count); // 0x71001e41d8
void callee_1f7430(void*, int);                                             // 0x71001f7430

// The flag bytes of a pane: +58 bit 0 visible, +5b the mode, alignment and wrap fields.
struct PaneFlags_28b710 {
    unsigned char pad0[0x58];
    unsigned char visible : 1;   // +58 bit 0
    unsigned char : 7;
    unsigned char pad59[2];
    unsigned char mode : 2;      // +5b bits 0-1
    unsigned char align : 2;     // +5b bits 2-3
    unsigned char wrap : 2;      // +5b bits 4-5
    unsigned char : 2;
};

static inline PaneFlags_28b710* flags_28b710(PanelPane* pane) {
    return reinterpret_cast<PaneFlags_28b710*>(pane);
}

extern const char kLayout_28b710[] __attribute__((visibility("hidden")));          // 0x71007d6225
extern const char kGroup48_28b710[] __attribute__((visibility("hidden")));         // 0x71007d6126
extern const char kGroup50_28b710[] __attribute__((visibility("hidden")));         // 0x71007d5ca9
extern const char kGroup58_28b710[] __attribute__((visibility("hidden")));         // 0x71007d623a
extern const char kPart18_28b710[] __attribute__((visibility("hidden")));          // 0x710073fffb
extern const char kPart20_28b710[] __attribute__((visibility("hidden")));          // 0x7100740004
extern const char kPart28_28b710[] __attribute__((visibility("hidden")));          // 0x710074056c
extern const char kPane0_28b710[] __attribute__((visibility("hidden")));           // 0x71007d6247
extern const char kPane1_28b710[] __attribute__((visibility("hidden")));           // 0x71007d6253
extern const char kPane2_28b710[] __attribute__((visibility("hidden")));           // 0x71007d6262
extern const char kPane3_28b710[] __attribute__((visibility("hidden")));           // 0x71007d626f
extern const char kPane4_28b710[] __attribute__((visibility("hidden")));           // 0x71007d627f
extern const char kGroupD078_28b710[] __attribute__((visibility("hidden")));       // 0x71007d628e
extern const char kLayout2_28b710[] __attribute__((visibility("hidden")));         // 0x71007d629e
extern const char kAnim_28b710[] __attribute__((visibility("hidden")));            // 0x71007d62ab
extern const char kGroupDup_28b710[] __attribute__((visibility("hidden")));        // 0x71007d62b1

class Class28b710 {
public:
    void initialize();                                                       // 0x710028b710: a window set-up written with the effect, pane and text-renderer types of the demo units: the text-area vectors are filled field by field (an aggregate initialiser stores them as one 64-bit constant that is hoisted too early) and the five panes are separate statements, so each slot's address stays in a register
    void finish_setup();                                                     // 0x710028f4dc

    LightEffectNode* node;           // +0
    unsigned char pad8[8];
    LightEffectNode* node2;          // +10
    void* part18;                    // +18
    void* part20;                    // +20
    void* part28;                    // +28
    unsigned char pad30[8];
    LayoutAnimation* anim;           // +38
    unsigned char pad40[8];
    EffectGroup* group48;            // +48
    EffectGroup* group50;            // +50
    EffectGroup* group58;            // +58
    unsigned char sources[0x458];    // +60
    EffectGroup* copy;               // +4b8
    TrackLightTarget lines0[32];     // +4c0
    TrackLightTarget lines1[32];     // +15c0
    TrackLightTarget lines2[32];     // +26c0
    unsigned char pad37c0[0x9878];
    unsigned int count0;             // +d038
    unsigned int count1;             // +d03c
    unsigned int count2;             // +d040
    unsigned char padd044[0xc];
    PanelPane* panes[5];             // +d050
    EffectGroup* groupd078;          // +d078
};

// 0x710028b710
void Class28b710::initialize() {
    gEffectManager->create_node(&node, 0x4203, kLayout_28b710);
    group48 = node->group->find(kGroup48_28b710, 1);
    group50 = node->group->find(kGroup50_28b710, 1);
    group58 = node->group->find(kGroup58_28b710, 1);
    group58->alpha59 = 0;
    part18 = callee_1e3770(node, const_cast<char*>(kPart18_28b710), 0);
    part20 = callee_1e3770(node, const_cast<char*>(kPart20_28b710), 0);
    part28 = callee_1e3770(node, const_cast<char*>(kPart28_28b710), 0);
    callee_1f7430(sources, 0xc);
    node->group->add(new LightEffect(0x10));
    TextRenderer* renderer = gTextRenderer;
    {
        TrackVec2 pos;
        pos.x = 0.0f;
        pos.y = 0.0f;
        TrackVec2 size;
        size.x = 32.0f;
        size.y = 32.0f;
        renderer->set_area(&pos, &size, 0x53, 0x4e, 0);
    }
    renderer->wrap = 1;
    renderer->align = 2;
    count0 = renderer->draw(lines0, message_text(0x132), 0x20, 1, 0xff, 0.0f, 0.0f);
    {
        TrackVec2 pos;
        pos.x = 0.0f;
        pos.y = 0.0f;
        TrackVec2 size;
        size.x = 32.0f;
        size.y = 32.0f;
        renderer->set_area(&pos, &size, 0x53, 0x4e, 0);
    }
    renderer->wrap = 1;
    renderer->align = 2;
    count1 = renderer->draw(lines1, message_text(0x133), 0x20, 1, 0xff, 0.0f, 0.0f);
    {
        TrackVec2 pos;
        pos.x = -64.0f;
        pos.y = 0.0f;
        TrackVec2 size;
        size.x = 32.0f;
        size.y = 32.0f;
        renderer->set_area(&pos, &size, 0x5d, 0x4e, 0);
    }
    renderer->wrap = 1;
    renderer->align = 2;
    count2 = renderer->draw(lines2, message_text(0x137), 0x20, 1, 0xff, 0.0f, 0.0f);
    panes[0] = new PanelPane;
    panes[1] = new PanelPane;
    panes[2] = new PanelPane;
    panes[3] = new PanelPane;
    panes[4] = new PanelPane;
    node->group->find(kPane0_28b710, 1)->add(panes[0]);
    node->group->find(kPane1_28b710, 1)->add(panes[1]);
    node->group->find(kPane2_28b710, 1)->add(panes[2]);
    node->group->find(kPane3_28b710, 1)->add(panes[3]);
    node->group->find(kPane4_28b710, 1)->add(panes[4]);
    flags_28b710(panes[0])->mode = 1;
    flags_28b710(panes[1])->mode = 1;
    flags_28b710(panes[2])->mode = 1;
    flags_28b710(panes[2])->align = 2;
    if (get_shared_state()->language != 0) {
        flags_28b710(panes[2])->wrap = 1;
    }
    flags_28b710(panes[3])->align = 2;
    flags_28b710(panes[4])->align = 2;
    set_pane_lines(panes[0], lines0, count0);
    set_pane_lines(panes[1], lines1, count1);
    set_pane_lines(panes[2], lines2, count2);
    flags_28b710(panes[2])->visible = 0;
    groupd078 = node->group->find(kGroupD078_28b710, 1);
    finish_setup();
    gEffectManager->create_node(&node2, 0x4203, kLayout2_28b710);
    anim = node2->create_animation(kAnim_28b710, true);
    gEffectManager->finish(0x4203);
    copy = node2->group->find(kGroupDup_28b710, 1)->duplicate(gResourceLoader->layout->root);
    group58->add(copy);
    node2->group->find(kGroupDup_28b710, 1)->flags58 &= ~1;
}

class MemStream {
public:
    MemStream();                                                             // 0x710053d304
    virtual ~MemStream();
    virtual void v10();
    virtual void v18();
    virtual int read(void* dst, void* unused, int size);                     // +20
    unsigned char open(void* data, long offset, int size);                   // 0x710053d360
    void close();                                                            // 0x710053d388

    unsigned char pad8[0x18];
};

struct Header_d89b0 {
    unsigned char b[0x10];
};

struct Rec_d89b0 {
    unsigned char head[8];           // +0
    unsigned char field_8;            // +8
    unsigned char field_9;            // +9
    unsigned short field_a;           // +a
    unsigned short field_c;           // +c
    unsigned short field_e;           // +e
    unsigned char field_10;           // +10
    unsigned char field_11;           // +11
    unsigned short field_12;          // +12
    unsigned char field_14;           // +14
    unsigned char field_15;           // +15
    unsigned short field_16;          // +16
    unsigned char field_18;           // +18
    unsigned char field_19;           // +19
    unsigned char field_1a;           // +1a
    unsigned char field_1b;           // +1b
    unsigned char field_1c;           // +1c
    unsigned char field_1d;           // +1d
    unsigned short field_1e;          // +1e
    unsigned short field_20;          // +20
    unsigned char field_22;           // +22
    unsigned char field_23;           // +23
    unsigned short field_24;          // +24
    unsigned short field_26;          // +26
    unsigned short field_28;          // +28
    unsigned char field_2a;           // +2a
    unsigned char field_2b;           // +2b
    unsigned char field_2c;           // +2c
    unsigned char field_2d;           // +2d
    unsigned char field_2e;           // +2e
    unsigned char field_2f;           // +2f
    unsigned short field_30;          // +30
    unsigned char field_32;           // +32
    unsigned char field_33;           // +33
    unsigned short field_34;          // +34
    unsigned short field_36;          // +36
    unsigned short field_38;          // +38
    unsigned short field_3a;          // +3a
    unsigned short field_3c;          // +3c
    unsigned char field_3e;           // +3e
    unsigned char field_3f;           // +3f
    unsigned short field_40;          // +40
    unsigned short field_42;          // +42
    unsigned short field_44;          // +44
    unsigned char field_46;           // +46
    unsigned char field_47;           // +47
    unsigned short field_48;          // +48
    unsigned short field_4a;          // +4a
    unsigned short field_4c;          // +4c
    unsigned short field_4e;          // +4e
    unsigned short field_50;          // +50
    unsigned char field_52;           // +52
    unsigned char field_53;           // +53
    unsigned char field_54;           // +54
    unsigned char field_55;           // +55
    unsigned short field_56;          // +56
    unsigned short field_58;          // +58
    unsigned short field_5a;          // +5a
    unsigned short field_5c;          // +5c
    unsigned char field_5e;           // +5e
    unsigned char field_5f;           // +5f
    int field_60;                     // +60
    unsigned short field_64;          // +64
    unsigned short field_66;          // +66
    unsigned char field_68;           // +68
    unsigned char field_69;           // +69
    unsigned char field_6a;           // +6a
    unsigned char field_6b;           // +6b
    unsigned char field_6c;           // +6c
    unsigned char field_6d;           // +6d
    unsigned short field_6e;          // +6e
    unsigned short field_70;          // +70
    unsigned short field_72;          // +72
    unsigned char field_74;           // +74
    unsigned char field_75;           // +75
    unsigned char field_76;           // +76
    unsigned char field_77;           // +77
    unsigned char field_78;           // +78
    unsigned char field_79;           // +79
    unsigned char field_7a;           // +7a
    unsigned char field_7b;           // +7b
    unsigned short field_7c;          // +7c
    unsigned short field_7e;          // +7e
    char field_80[0x40];              // +80
    unsigned char field_c0;           // +c0
    unsigned char field_c1;           // +c1
    unsigned char field_c2;           // +c2
    unsigned char field_c3;           // +c3
    unsigned char field_c4;           // +c4
    unsigned char field_c5;           // +c5
    unsigned short field_c6;          // +c6
    unsigned char field_c8;           // +c8
    unsigned char field_c9;           // +c9
    unsigned char field_ca;           // +ca
    unsigned char field_cb;           // +cb
    unsigned short field_cc;          // +cc
    unsigned short field_ce;          // +ce
    unsigned char field_d0;           // +d0
    unsigned char field_d1;           // +d1
    unsigned short field_d2;          // +d2
    unsigned char field_d4;           // +d4
    unsigned char field_d5;           // +d5
    unsigned char field_d6;           // +d6
    unsigned char field_d7;           // +d7
    unsigned short field_d8;          // +d8
    unsigned char field_da;           // +da
    unsigned char field_db;           // +db
    unsigned short field_dc;          // +dc
    unsigned char field_de;           // +de
    unsigned char field_df;           // +df
    unsigned char field_e0;           // +e0
    unsigned char field_e1;           // +e1
    unsigned char field_e2;           // +e2
    unsigned char field_e3;           // +e3
    unsigned short field_e4;          // +e4
    unsigned short field_e6;          // +e6
    unsigned short field_e8;          // +e8
    unsigned short field_ea;          // +ea
    unsigned short field_ec;          // +ec
    unsigned short field_ee;          // +ee
    void* target;                    // +f0
    unsigned char field_f8;           // +f8
    unsigned char field_f9;           // +f9
    unsigned short field_fa;          // +fa
    unsigned char field_fc;           // +fc
    unsigned char field_fd;           // +fd
    unsigned short field_fe;          // +fe
    unsigned short field_100;         // +100
    unsigned short field_102;         // +102
    unsigned char pad104[0xc];
};
static_assert(sizeof(Rec_d89b0) == 0x110, "record size");
static_assert(__builtin_offsetof(Rec_d89b0, target) == 0xf0, "target");

struct Pool_d89b0 {
    unsigned char pad0[8];
    Rec_d89b0* free;                 // +8
};

struct List_d89b0 {
    Rec_d89b0** items;               // +0
    unsigned short capacity;         // +8
    unsigned short count;            // +a
};

struct Ctx_d89b0 {
    void* data;                      // +0
    int size;                        // +8
    int count;                       // +c
    unsigned int limit;              // +10
    unsigned char pad14[4];
    Pool_d89b0* pool;                // +18
    List_d89b0* list;                // +20
    void* table;                     // +28
};

void callee_4ca98(Rec_d89b0*);                                               // 0x710004ca98
void* callee_4df50(void*, int);                                              // 0x710004df50

// 0x71000d89b0: a record loader: a memory stream whose virtual read is called through a pointer (on the local object itself Clang calls it directly), one read per field in field order, the target id read into a local and resolved afterwards
bool call_d89b0(Ctx_d89b0* p0) {
    MemStream memory;
    MemStream* stream = &memory;
    if (!stream->open(p0->data, 0, p0->size)) {
        return false;
    }
    Pool_d89b0* pool = p0->pool;
    int count = p0->count;
    unsigned int limit = p0->limit;
    void* table = p0->table;
    Header_d89b0 header;
    stream->read(&header, nullptr, sizeof(header));
    while (count != 0) {
        Rec_d89b0* rec = pool->free;
        if (rec != nullptr) {
            pool->free = *reinterpret_cast<Rec_d89b0**>(rec);
        }
        callee_4ca98(rec);
        stream->read(rec->head, nullptr, sizeof(rec->head));
        stream->read(&rec->field_8, nullptr, sizeof(rec->field_8));
        stream->read(&rec->field_9, nullptr, sizeof(rec->field_9));
        stream->read(&rec->field_a, nullptr, sizeof(rec->field_a));
        stream->read(&rec->field_c, nullptr, sizeof(rec->field_c));
        stream->read(&rec->field_e, nullptr, sizeof(rec->field_e));
        stream->read(&rec->field_10, nullptr, sizeof(rec->field_10));
        stream->read(&rec->field_11, nullptr, sizeof(rec->field_11));
        stream->read(&rec->field_12, nullptr, sizeof(rec->field_12));
        stream->read(&rec->field_14, nullptr, sizeof(rec->field_14));
        stream->read(&rec->field_15, nullptr, sizeof(rec->field_15));
        stream->read(&rec->field_16, nullptr, sizeof(rec->field_16));
        stream->read(&rec->field_18, nullptr, sizeof(rec->field_18));
        stream->read(&rec->field_19, nullptr, sizeof(rec->field_19));
        stream->read(&rec->field_1a, nullptr, sizeof(rec->field_1a));
        stream->read(&rec->field_1b, nullptr, sizeof(rec->field_1b));
        stream->read(&rec->field_1c, nullptr, sizeof(rec->field_1c));
        stream->read(&rec->field_1d, nullptr, sizeof(rec->field_1d));
        stream->read(&rec->field_1e, nullptr, sizeof(rec->field_1e));
        stream->read(&rec->field_20, nullptr, sizeof(rec->field_20));
        stream->read(&rec->field_22, nullptr, sizeof(rec->field_22));
        stream->read(&rec->field_23, nullptr, sizeof(rec->field_23));
        stream->read(&rec->field_24, nullptr, sizeof(rec->field_24));
        stream->read(&rec->field_26, nullptr, sizeof(rec->field_26));
        stream->read(&rec->field_28, nullptr, sizeof(rec->field_28));
        stream->read(&rec->field_2a, nullptr, sizeof(rec->field_2a));
        stream->read(&rec->field_2b, nullptr, sizeof(rec->field_2b));
        stream->read(&rec->field_2c, nullptr, sizeof(rec->field_2c));
        stream->read(&rec->field_2d, nullptr, sizeof(rec->field_2d));
        stream->read(&rec->field_2e, nullptr, sizeof(rec->field_2e));
        stream->read(&rec->field_2f, nullptr, sizeof(rec->field_2f));
        stream->read(&rec->field_30, nullptr, sizeof(rec->field_30));
        stream->read(&rec->field_32, nullptr, sizeof(rec->field_32));
        stream->read(&rec->field_33, nullptr, sizeof(rec->field_33));
        stream->read(&rec->field_34, nullptr, sizeof(rec->field_34));
        stream->read(&rec->field_36, nullptr, sizeof(rec->field_36));
        stream->read(&rec->field_38, nullptr, sizeof(rec->field_38));
        stream->read(&rec->field_3a, nullptr, sizeof(rec->field_3a));
        stream->read(&rec->field_3c, nullptr, sizeof(rec->field_3c));
        stream->read(&rec->field_3e, nullptr, sizeof(rec->field_3e));
        stream->read(&rec->field_3f, nullptr, sizeof(rec->field_3f));
        stream->read(&rec->field_40, nullptr, sizeof(rec->field_40));
        stream->read(&rec->field_42, nullptr, sizeof(rec->field_42));
        stream->read(&rec->field_44, nullptr, sizeof(rec->field_44));
        stream->read(&rec->field_46, nullptr, sizeof(rec->field_46));
        stream->read(&rec->field_47, nullptr, sizeof(rec->field_47));
        stream->read(&rec->field_48, nullptr, sizeof(rec->field_48));
        stream->read(&rec->field_4a, nullptr, sizeof(rec->field_4a));
        stream->read(&rec->field_4c, nullptr, sizeof(rec->field_4c));
        stream->read(&rec->field_4e, nullptr, sizeof(rec->field_4e));
        stream->read(&rec->field_50, nullptr, sizeof(rec->field_50));
        stream->read(&rec->field_52, nullptr, sizeof(rec->field_52));
        stream->read(&rec->field_53, nullptr, sizeof(rec->field_53));
        stream->read(&rec->field_54, nullptr, sizeof(rec->field_54));
        stream->read(&rec->field_55, nullptr, sizeof(rec->field_55));
        stream->read(&rec->field_56, nullptr, sizeof(rec->field_56));
        stream->read(&rec->field_58, nullptr, sizeof(rec->field_58));
        stream->read(&rec->field_5a, nullptr, sizeof(rec->field_5a));
        stream->read(&rec->field_5c, nullptr, sizeof(rec->field_5c));
        stream->read(&rec->field_5e, nullptr, sizeof(rec->field_5e));
        stream->read(&rec->field_5f, nullptr, sizeof(rec->field_5f));
        stream->read(&rec->field_60, nullptr, sizeof(rec->field_60));
        stream->read(&rec->field_64, nullptr, sizeof(rec->field_64));
        stream->read(&rec->field_66, nullptr, sizeof(rec->field_66));
        stream->read(&rec->field_68, nullptr, sizeof(rec->field_68));
        stream->read(&rec->field_69, nullptr, sizeof(rec->field_69));
        stream->read(&rec->field_6a, nullptr, sizeof(rec->field_6a));
        stream->read(&rec->field_6b, nullptr, sizeof(rec->field_6b));
        stream->read(&rec->field_6c, nullptr, sizeof(rec->field_6c));
        stream->read(&rec->field_6d, nullptr, sizeof(rec->field_6d));
        stream->read(&rec->field_6e, nullptr, sizeof(rec->field_6e));
        stream->read(&rec->field_70, nullptr, sizeof(rec->field_70));
        stream->read(&rec->field_72, nullptr, sizeof(rec->field_72));
        stream->read(&rec->field_74, nullptr, sizeof(rec->field_74));
        stream->read(&rec->field_75, nullptr, sizeof(rec->field_75));
        stream->read(&rec->field_76, nullptr, sizeof(rec->field_76));
        stream->read(&rec->field_77, nullptr, sizeof(rec->field_77));
        stream->read(&rec->field_78, nullptr, sizeof(rec->field_78));
        stream->read(&rec->field_79, nullptr, sizeof(rec->field_79));
        stream->read(&rec->field_7a, nullptr, sizeof(rec->field_7a));
        stream->read(&rec->field_7b, nullptr, sizeof(rec->field_7b));
        stream->read(&rec->field_7c, nullptr, sizeof(rec->field_7c));
        stream->read(&rec->field_7e, nullptr, sizeof(rec->field_7e));
        stream->read(&rec->field_80, nullptr, sizeof(rec->field_80));
        stream->read(&rec->field_c0, nullptr, sizeof(rec->field_c0));
        stream->read(&rec->field_c1, nullptr, sizeof(rec->field_c1));
        stream->read(&rec->field_c2, nullptr, sizeof(rec->field_c2));
        stream->read(&rec->field_c3, nullptr, sizeof(rec->field_c3));
        stream->read(&rec->field_c4, nullptr, sizeof(rec->field_c4));
        stream->read(&rec->field_c5, nullptr, sizeof(rec->field_c5));
        stream->read(&rec->field_c6, nullptr, sizeof(rec->field_c6));
        stream->read(&rec->field_c8, nullptr, sizeof(rec->field_c8));
        stream->read(&rec->field_c9, nullptr, sizeof(rec->field_c9));
        stream->read(&rec->field_ca, nullptr, sizeof(rec->field_ca));
        stream->read(&rec->field_cb, nullptr, sizeof(rec->field_cb));
        stream->read(&rec->field_cc, nullptr, sizeof(rec->field_cc));
        stream->read(&rec->field_ce, nullptr, sizeof(rec->field_ce));
        stream->read(&rec->field_d0, nullptr, sizeof(rec->field_d0));
        stream->read(&rec->field_d1, nullptr, sizeof(rec->field_d1));
        stream->read(&rec->field_d2, nullptr, sizeof(rec->field_d2));
        stream->read(&rec->field_d4, nullptr, sizeof(rec->field_d4));
        stream->read(&rec->field_d5, nullptr, sizeof(rec->field_d5));
        stream->read(&rec->field_d6, nullptr, sizeof(rec->field_d6));
        stream->read(&rec->field_d7, nullptr, sizeof(rec->field_d7));
        stream->read(&rec->field_d8, nullptr, sizeof(rec->field_d8));
        stream->read(&rec->field_da, nullptr, sizeof(rec->field_da));
        stream->read(&rec->field_db, nullptr, sizeof(rec->field_db));
        stream->read(&rec->field_dc, nullptr, sizeof(rec->field_dc));
        stream->read(&rec->field_de, nullptr, sizeof(rec->field_de));
        stream->read(&rec->field_df, nullptr, sizeof(rec->field_df));
        stream->read(&rec->field_e0, nullptr, sizeof(rec->field_e0));
        stream->read(&rec->field_e1, nullptr, sizeof(rec->field_e1));
        stream->read(&rec->field_e2, nullptr, sizeof(rec->field_e2));
        stream->read(&rec->field_e3, nullptr, sizeof(rec->field_e3));
        stream->read(&rec->field_e4, nullptr, sizeof(rec->field_e4));
        stream->read(&rec->field_e6, nullptr, sizeof(rec->field_e6));
        stream->read(&rec->field_e8, nullptr, sizeof(rec->field_e8));
        stream->read(&rec->field_ea, nullptr, sizeof(rec->field_ea));
        stream->read(&rec->field_ec, nullptr, sizeof(rec->field_ec));
        stream->read(&rec->field_ee, nullptr, sizeof(rec->field_ee));
        int id = 0;
        stream->read(&id, nullptr, sizeof(id));
        stream->read(&rec->field_f8, nullptr, sizeof(rec->field_f8));
        stream->read(&rec->field_f9, nullptr, sizeof(rec->field_f9));
        stream->read(&rec->field_fa, nullptr, sizeof(rec->field_fa));
        stream->read(&rec->field_fc, nullptr, sizeof(rec->field_fc));
        stream->read(&rec->field_fd, nullptr, sizeof(rec->field_fd));
        stream->read(&rec->field_fe, nullptr, sizeof(rec->field_fe));
        stream->read(&rec->field_100, nullptr, sizeof(rec->field_100));
        stream->read(&rec->field_102, nullptr, sizeof(rec->field_102));
        List_d89b0* list = p0->list;
        list->items[list->count++] = rec;
        if (id != -1 && (rec->head[6] & 0x20)) {
            if (static_cast<unsigned int>(id) < limit) {
                rec->target = callee_4df50(table, id);
            }
        } else {
            rec->target = nullptr;
        }
        count--;
    }
    stream->close();
    return true;
}

struct Arena_d98e0 {
    unsigned char* base;             // +0
    unsigned long used;              // +8
    unsigned long capacity;          // +10

    void* alloc(unsigned long size) {
        unsigned long offset = used;
        unsigned long end = offset + size;
        if (end > capacity) {
            return nullptr;
        }
        used = end;
        return base + offset;
    }
};

struct Ctx_d98e0 {
    void* data;                      // +0
    int size;                        // +8
    unsigned char padc[4];
    Pool_d89b0* pool;                // +10
    Arena_d98e0* arena;              // +18
    List_d89b0* list;                // +20
};

// 0x71000d98e0: the same record loader with the record count taken from the header and the item list carved from an arena; the byte count is a local computed before the arena is loaded
unsigned int call_d98e0(Ctx_d98e0* p0) {
    MemStream memory;
    MemStream* stream = &memory;
    if (!stream->open(p0->data, 0, p0->size)) {
        return 0;
    }
    Header_d89b0 header;
    stream->read(&header, nullptr, sizeof(header));
    unsigned int n = *reinterpret_cast<unsigned int*>(header.b);
    unsigned long bytes = n * sizeof(void*);
    Arena_d98e0* arena = p0->arena;
    if (arena->capacity - arena->used < bytes) {
        return 0;
    }
    Pool_d89b0* pool = p0->pool;
    List_d89b0* list = p0->list;
    Rec_d89b0** items = static_cast<Rec_d89b0**>(arena->alloc(bytes));
    list->items = items;
    list->capacity = n;
    for (unsigned int i = 0; i < list->capacity; i++) {
        list->items[i] = nullptr;
    }
    for (unsigned int count = n; count != 0; count--) {
        Rec_d89b0* rec = pool->free;
        if (rec != nullptr) {
            pool->free = *reinterpret_cast<Rec_d89b0**>(rec);
        }
        callee_4ca98(rec);
        stream->read(rec->head, nullptr, sizeof(rec->head));
        stream->read(&rec->field_8, nullptr, sizeof(rec->field_8));
        stream->read(&rec->field_9, nullptr, sizeof(rec->field_9));
        stream->read(&rec->field_a, nullptr, sizeof(rec->field_a));
        stream->read(&rec->field_c, nullptr, sizeof(rec->field_c));
        stream->read(&rec->field_e, nullptr, sizeof(rec->field_e));
        stream->read(&rec->field_10, nullptr, sizeof(rec->field_10));
        stream->read(&rec->field_11, nullptr, sizeof(rec->field_11));
        stream->read(&rec->field_12, nullptr, sizeof(rec->field_12));
        stream->read(&rec->field_14, nullptr, sizeof(rec->field_14));
        stream->read(&rec->field_15, nullptr, sizeof(rec->field_15));
        stream->read(&rec->field_16, nullptr, sizeof(rec->field_16));
        stream->read(&rec->field_18, nullptr, sizeof(rec->field_18));
        stream->read(&rec->field_19, nullptr, sizeof(rec->field_19));
        stream->read(&rec->field_1a, nullptr, sizeof(rec->field_1a));
        stream->read(&rec->field_1b, nullptr, sizeof(rec->field_1b));
        stream->read(&rec->field_1c, nullptr, sizeof(rec->field_1c));
        stream->read(&rec->field_1d, nullptr, sizeof(rec->field_1d));
        stream->read(&rec->field_1e, nullptr, sizeof(rec->field_1e));
        stream->read(&rec->field_20, nullptr, sizeof(rec->field_20));
        stream->read(&rec->field_22, nullptr, sizeof(rec->field_22));
        stream->read(&rec->field_23, nullptr, sizeof(rec->field_23));
        stream->read(&rec->field_24, nullptr, sizeof(rec->field_24));
        stream->read(&rec->field_26, nullptr, sizeof(rec->field_26));
        stream->read(&rec->field_28, nullptr, sizeof(rec->field_28));
        stream->read(&rec->field_2a, nullptr, sizeof(rec->field_2a));
        stream->read(&rec->field_2b, nullptr, sizeof(rec->field_2b));
        stream->read(&rec->field_2c, nullptr, sizeof(rec->field_2c));
        stream->read(&rec->field_2d, nullptr, sizeof(rec->field_2d));
        stream->read(&rec->field_2e, nullptr, sizeof(rec->field_2e));
        stream->read(&rec->field_2f, nullptr, sizeof(rec->field_2f));
        stream->read(&rec->field_30, nullptr, sizeof(rec->field_30));
        stream->read(&rec->field_32, nullptr, sizeof(rec->field_32));
        stream->read(&rec->field_33, nullptr, sizeof(rec->field_33));
        stream->read(&rec->field_34, nullptr, sizeof(rec->field_34));
        stream->read(&rec->field_36, nullptr, sizeof(rec->field_36));
        stream->read(&rec->field_38, nullptr, sizeof(rec->field_38));
        stream->read(&rec->field_3a, nullptr, sizeof(rec->field_3a));
        stream->read(&rec->field_3c, nullptr, sizeof(rec->field_3c));
        stream->read(&rec->field_3e, nullptr, sizeof(rec->field_3e));
        stream->read(&rec->field_3f, nullptr, sizeof(rec->field_3f));
        stream->read(&rec->field_40, nullptr, sizeof(rec->field_40));
        stream->read(&rec->field_42, nullptr, sizeof(rec->field_42));
        stream->read(&rec->field_44, nullptr, sizeof(rec->field_44));
        stream->read(&rec->field_46, nullptr, sizeof(rec->field_46));
        stream->read(&rec->field_47, nullptr, sizeof(rec->field_47));
        stream->read(&rec->field_48, nullptr, sizeof(rec->field_48));
        stream->read(&rec->field_4a, nullptr, sizeof(rec->field_4a));
        stream->read(&rec->field_4c, nullptr, sizeof(rec->field_4c));
        stream->read(&rec->field_4e, nullptr, sizeof(rec->field_4e));
        stream->read(&rec->field_50, nullptr, sizeof(rec->field_50));
        stream->read(&rec->field_52, nullptr, sizeof(rec->field_52));
        stream->read(&rec->field_53, nullptr, sizeof(rec->field_53));
        stream->read(&rec->field_54, nullptr, sizeof(rec->field_54));
        stream->read(&rec->field_55, nullptr, sizeof(rec->field_55));
        stream->read(&rec->field_56, nullptr, sizeof(rec->field_56));
        stream->read(&rec->field_58, nullptr, sizeof(rec->field_58));
        stream->read(&rec->field_5a, nullptr, sizeof(rec->field_5a));
        stream->read(&rec->field_5c, nullptr, sizeof(rec->field_5c));
        stream->read(&rec->field_5e, nullptr, sizeof(rec->field_5e));
        stream->read(&rec->field_5f, nullptr, sizeof(rec->field_5f));
        stream->read(&rec->field_60, nullptr, sizeof(rec->field_60));
        stream->read(&rec->field_64, nullptr, sizeof(rec->field_64));
        stream->read(&rec->field_66, nullptr, sizeof(rec->field_66));
        stream->read(&rec->field_68, nullptr, sizeof(rec->field_68));
        stream->read(&rec->field_69, nullptr, sizeof(rec->field_69));
        stream->read(&rec->field_6a, nullptr, sizeof(rec->field_6a));
        stream->read(&rec->field_6b, nullptr, sizeof(rec->field_6b));
        stream->read(&rec->field_6c, nullptr, sizeof(rec->field_6c));
        stream->read(&rec->field_6d, nullptr, sizeof(rec->field_6d));
        stream->read(&rec->field_6e, nullptr, sizeof(rec->field_6e));
        stream->read(&rec->field_70, nullptr, sizeof(rec->field_70));
        stream->read(&rec->field_72, nullptr, sizeof(rec->field_72));
        stream->read(&rec->field_74, nullptr, sizeof(rec->field_74));
        stream->read(&rec->field_75, nullptr, sizeof(rec->field_75));
        stream->read(&rec->field_76, nullptr, sizeof(rec->field_76));
        stream->read(&rec->field_77, nullptr, sizeof(rec->field_77));
        stream->read(&rec->field_78, nullptr, sizeof(rec->field_78));
        stream->read(&rec->field_79, nullptr, sizeof(rec->field_79));
        stream->read(&rec->field_7a, nullptr, sizeof(rec->field_7a));
        stream->read(&rec->field_7b, nullptr, sizeof(rec->field_7b));
        stream->read(&rec->field_7c, nullptr, sizeof(rec->field_7c));
        stream->read(&rec->field_7e, nullptr, sizeof(rec->field_7e));
        stream->read(&rec->field_80, nullptr, sizeof(rec->field_80));
        stream->read(&rec->field_c0, nullptr, sizeof(rec->field_c0));
        stream->read(&rec->field_c1, nullptr, sizeof(rec->field_c1));
        stream->read(&rec->field_c2, nullptr, sizeof(rec->field_c2));
        stream->read(&rec->field_c3, nullptr, sizeof(rec->field_c3));
        stream->read(&rec->field_c4, nullptr, sizeof(rec->field_c4));
        stream->read(&rec->field_c5, nullptr, sizeof(rec->field_c5));
        stream->read(&rec->field_c6, nullptr, sizeof(rec->field_c6));
        stream->read(&rec->field_c8, nullptr, sizeof(rec->field_c8));
        stream->read(&rec->field_c9, nullptr, sizeof(rec->field_c9));
        stream->read(&rec->field_ca, nullptr, sizeof(rec->field_ca));
        stream->read(&rec->field_cb, nullptr, sizeof(rec->field_cb));
        stream->read(&rec->field_cc, nullptr, sizeof(rec->field_cc));
        stream->read(&rec->field_ce, nullptr, sizeof(rec->field_ce));
        stream->read(&rec->field_d0, nullptr, sizeof(rec->field_d0));
        stream->read(&rec->field_d1, nullptr, sizeof(rec->field_d1));
        stream->read(&rec->field_d2, nullptr, sizeof(rec->field_d2));
        stream->read(&rec->field_d4, nullptr, sizeof(rec->field_d4));
        stream->read(&rec->field_d5, nullptr, sizeof(rec->field_d5));
        stream->read(&rec->field_d6, nullptr, sizeof(rec->field_d6));
        stream->read(&rec->field_d7, nullptr, sizeof(rec->field_d7));
        stream->read(&rec->field_d8, nullptr, sizeof(rec->field_d8));
        stream->read(&rec->field_da, nullptr, sizeof(rec->field_da));
        stream->read(&rec->field_db, nullptr, sizeof(rec->field_db));
        stream->read(&rec->field_dc, nullptr, sizeof(rec->field_dc));
        stream->read(&rec->field_de, nullptr, sizeof(rec->field_de));
        stream->read(&rec->field_df, nullptr, sizeof(rec->field_df));
        stream->read(&rec->field_e0, nullptr, sizeof(rec->field_e0));
        stream->read(&rec->field_e1, nullptr, sizeof(rec->field_e1));
        stream->read(&rec->field_e2, nullptr, sizeof(rec->field_e2));
        stream->read(&rec->field_e3, nullptr, sizeof(rec->field_e3));
        stream->read(&rec->field_e4, nullptr, sizeof(rec->field_e4));
        stream->read(&rec->field_e6, nullptr, sizeof(rec->field_e6));
        stream->read(&rec->field_e8, nullptr, sizeof(rec->field_e8));
        stream->read(&rec->field_ea, nullptr, sizeof(rec->field_ea));
        stream->read(&rec->field_ec, nullptr, sizeof(rec->field_ec));
        stream->read(&rec->field_ee, nullptr, sizeof(rec->field_ee));
        int id = 0;
        stream->read(&id, nullptr, sizeof(id));
        stream->read(&rec->field_f8, nullptr, sizeof(rec->field_f8));
        stream->read(&rec->field_f9, nullptr, sizeof(rec->field_f9));
        stream->read(&rec->field_fa, nullptr, sizeof(rec->field_fa));
        stream->read(&rec->field_fc, nullptr, sizeof(rec->field_fc));
        stream->read(&rec->field_fd, nullptr, sizeof(rec->field_fd));
        stream->read(&rec->field_fe, nullptr, sizeof(rec->field_fe));
        stream->read(&rec->field_100, nullptr, sizeof(rec->field_100));
        stream->read(&rec->field_102, nullptr, sizeof(rec->field_102));
        List_d89b0* items_list = p0->list;
        items_list->items[items_list->count++] = rec;
        rec->target = nullptr;
    }
    stream->close();
    return n;
}

class OutStream {
public:
    OutStream();                                                             // 0x710053d454
    virtual ~OutStream();                                                    // 0x710053d488
    virtual void v10();
    virtual int write(void* src, void* unused, int size);                    // +18
    unsigned char open(void* data, long offset, int size);                   // 0x710053d4b0
    void close();                                                            // 0x710053d4d8
    unsigned long tell();                                                    // 0x710053d568

    unsigned char pad8[0x18];
};

struct Ctx_da854 {
    void* src;                       // +0
    void* dst;                       // +8
    int src_size;                    // +10
    int dst_size;                    // +14
};

// 0x71000da854: copies a 32-bit archive into a 64-bit one, widening every offset; the truncated table size is declared right after the 64-bit one so that IndVarSimplify leaves the 64-bit shift above the header loop
void call_da854(Ctx_da854* p0) {
    MemStream input;
    OutStream output;
    MemStream* in = &input;
    OutStream* out = &output;
    if (in->open(p0->src, 0, p0->src_size)) {
        if (out->open(p0->dst, 0, p0->dst_size)) {
            unsigned int counts[6] = {};
            int zero = 0;
            unsigned int total = 0;
            for (int i = 0; i < 6; i++) {
                in->read(&counts[i], nullptr, sizeof(counts[i]));
                out->write(&counts[i], nullptr, sizeof(counts[i]));
                total += counts[i];
            }
            unsigned long table = total * sizeof(unsigned int);
            int table32 = table;
            for (int i = 0; i < 6; i++) {
                int offset = 0;
                in->read(&offset, nullptr, sizeof(offset));
                offset += 0x18;
                out->write(&offset, nullptr, sizeof(offset));
                out->write(&zero, nullptr, sizeof(zero));
            }
            unsigned int* offsets = new unsigned int[total + 1];
            for (unsigned int i = 0; i < total; i++) {
                int offset = 0;
                in->read(&offset, nullptr, sizeof(offset));
                offsets[i] = offset + table32 + 0x18 + i * 0x10;
                out->write(&offsets[i], nullptr, sizeof(offsets[i]));
                out->write(&zero, nullptr, sizeof(zero));
            }
            offsets[total] = p0->src_size + table32 + total * 0x10 + 0x18;
            unsigned int index = 0;
            for (int k = 0; k < 6; k++) {
                for (unsigned int j = 0; j < counts[k]; j++) {
                    index++;
                    int adjust = table + 0x18 + index * 0x10;
                    int a;
                    in->read(&a, nullptr, sizeof(a));
                    out->write(&a, nullptr, sizeof(a));
                    int b;
                    in->read(&b, nullptr, sizeof(b));
                    out->write(&b, nullptr, sizeof(b));
                    int c;
                    in->read(&c, nullptr, sizeof(c));
                    out->write(&c, nullptr, sizeof(c));
                    int d;
                    in->read(&d, nullptr, sizeof(d));
                    out->write(&d, nullptr, sizeof(d));
                    int e;
                    in->read(&e, nullptr, sizeof(e));
                    out->write(&e, nullptr, sizeof(e));
                    int f;
                    in->read(&f, nullptr, sizeof(f));
                    out->write(&f, nullptr, sizeof(f));
                    int g;
                    in->read(&g, nullptr, sizeof(g));
                    g += adjust;
                    out->write(&g, nullptr, sizeof(g));
                    out->write(&zero, nullptr, sizeof(zero));
                    int h;
                    in->read(&h, nullptr, sizeof(h));
                    h += adjust;
                    out->write(&h, nullptr, sizeof(h));
                    out->write(&zero, nullptr, sizeof(zero));
                    int i;
                    in->read(&i, nullptr, sizeof(i));
                    out->write(&i, nullptr, sizeof(i));
                    int ptr;
                    in->read(&ptr, nullptr, sizeof(ptr));
                    int l;
                    in->read(&l, nullptr, sizeof(l));
                    out->write(&l, nullptr, sizeof(l));
                    ptr += adjust;
                    out->write(&ptr, nullptr, sizeof(ptr));
                    out->write(&zero, nullptr, sizeof(zero));
                    int m;
                    in->read(&m, nullptr, sizeof(m));
                    m += adjust;
                    out->write(&m, nullptr, sizeof(m));
                    out->write(&zero, nullptr, sizeof(zero));
                    int word = 0;
                    while (out->tell() < offsets[index]) {
                        in->read(&word, nullptr, sizeof(word));
                        out->write(&word, nullptr, sizeof(word));
                    }
                }
            }
            delete[] offsets;
            out->close();
        }
        in->close();
    }
}

class DefaultHeap {
public:
    void* allocate(unsigned int alignment, unsigned long size, int a, int b); // 0x710045c458
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c
int callee_170c58();                                                        // 0x7100170c58

// Arrays are carved from the default heap; the heap takes the size as 32 bits.
struct HeapTag_1451bc {};
inline void* operator new[](unsigned long size, HeapTag_1451bc) {
    return get_default_heap()->allocate(0x10, static_cast<unsigned int>(size), 1, 0);
}

// The same, cleared after allocation.
struct ZeroHeapTag_1451bc {};
inline void* operator new[](unsigned long size, ZeroHeapTag_1451bc) {
    void* p = get_default_heap()->allocate(0x10, static_cast<unsigned int>(size), 1, 0);
    memset(p, 0, size);
    return p;
}

class Elem132aec {
public:
    Elem132aec();                                                           // 0x7100132aec
    unsigned char data[0x120];
};
class Elem13ea74 {
public:
    Elem13ea74();                                                           // 0x710013ea74
    unsigned char data[0x100];
};
class Elem13bce4 {
public:
    Elem13bce4();                                                           // 0x710013bce4
    unsigned char data[0x638];
};
class Part13e2b4 {
public:
    Part13e2b4();                                                           // 0x710013e2b4
    unsigned char data[0x58];
};
class Part14a7dc {
public:
    Part14a7dc();                                                           // 0x710014a7dc
    unsigned char data[0x4bd0];
};
class Part13dd18 {
public:
    Part13dd18();                                                           // 0x710013dd18
    unsigned char data[0x5000];
};
class Part146f30 {
public:
    Part146f30();                                                           // 0x7100146f30
    unsigned char data[0xf30];
};
class Part157d68 {
public:
    Part157d68();                                                           // 0x7100157d68
    unsigned char data[0x28];
};
class Part154468 {
public:
    Part154468();                                                           // 0x7100154468
    unsigned char data[0x10];
};
class Part135e00 {
public:
    Part135e00();                                                           // 0x7100135e00
    unsigned char data[0x18];
};
class Part140b9c {
public:
    Part140b9c();                                                           // 0x7100140b9c
    unsigned char data[8];
};
class Part15e580 {
public:
    Part15e580();                                                           // 0x710015e580
    unsigned char data[8];
};
class Sub15aa9c {
public:
    Sub15aa9c();                                                            // 0x710015aa9c
    unsigned char data[0x180];
};
// Its implicit constructor is not trivial, so new[] constructs each element.
struct Elem15aa9c {
    Sub15aa9c sub;
};

struct Slot32_1451bc {
    unsigned int next;               // +0
    unsigned char pad4[0x1c];
};

struct Pair8_1451bc {
    int a;
    int b;
};

struct List0_1451bc {
    void* ptr;                       // +0
    int count;                       // +8
    int used;                        // +c
    int free;                        // +10
    unsigned char flag;              // +14
    unsigned char pad15[0x13];

    List0_1451bc() : ptr(nullptr), count(0), used(0), free(0), flag(0) {}
};

struct Pool_1451bc {
    void* ptr;                       // +0
    unsigned int count;              // +8
    unsigned int used;               // +c
    unsigned int free;               // +10
    unsigned int stride;             // +14
    void* storage;                   // +18

    Pool_1451bc() : ptr(nullptr), count(0), used(0), free(0), stride(0) {}
};

static inline void init_slots_1451bc(Pool_1451bc* pool, unsigned int count) {
    Slot32_1451bc* slots = new (HeapTag_1451bc{}) Slot32_1451bc[count];
    pool->storage = slots;
    pool->stride = sizeof(Slot32_1451bc);
    pool->ptr = slots;
    pool->count = count;
    pool->used = 0;
    pool->free = count;
    Slot32_1451bc* slot = slots;
    for (unsigned int i = 0; i < count; i++) {
        slot->next = i + 1;
        slot++;
    }
}

static inline void init_pair_1451bc(Pool_1451bc* pool, unsigned int count) {
    unsigned int half = count * sizeof(int);
    int* storage = reinterpret_cast<int*>(new (HeapTag_1451bc{}) Pair8_1451bc[count]);
    pool->storage = storage;
    pool->stride = half;
    pool->ptr = storage;
    pool->count = 2;
    pool->used = 0;
    pool->free = 2;
    storage[0] = 1;
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(storage) + half) = 2;
}

class Obj1451bc {
public:
    Obj1451bc();                                                            // 0x71001451bc

    Elem132aec items[0xf6];          // +0
    Elem13ea74 entries[0x12c];       // +114c0
    Elem15aa9c* elems;               // +240c0
    Elem13bce4 groups[24];           // +240c8
    Part13e2b4 part2d608;            // +2d608
    Part14a7dc part2d660;            // +2d660
    Part13dd18 part32230;            // +32230
    Part146f30 part37230;            // +37230
    Part157d68 part38160;            // +38160
    Part154468 part38188;            // +38188
    Part135e00 part38198;            // +38198
    Part140b9c part381b0;            // +381b0
    Part15e580 part381b8;            // +381b8
    int* values;                     // +381c0
    List0_1451bc list381c8;          // +381c8
    Pool_1451bc slots;               // +381f0
    Pool_1451bc pair38210;           // +38210
    Pool_1451bc pair38230;           // +38230
    Pool_1451bc pair38250;           // +38250
};
static_assert(__builtin_offsetof(Obj1451bc, entries) == 0x114c0, "114c0");
static_assert(__builtin_offsetof(Obj1451bc, groups) == 0x240c8, "240c8");
static_assert(__builtin_offsetof(Obj1451bc, part2d608) == 0x2d608, "2d608");
static_assert(__builtin_offsetof(Obj1451bc, part2d660) == 0x2d660, "2d660");
static_assert(__builtin_offsetof(Obj1451bc, part32230) == 0x32230, "32230");
static_assert(__builtin_offsetof(Obj1451bc, part37230) == 0x37230, "37230");
static_assert(__builtin_offsetof(Obj1451bc, part38160) == 0x38160, "38160");
static_assert(__builtin_offsetof(Obj1451bc, part381b8) == 0x381b8, "381b8");
static_assert(__builtin_offsetof(Obj1451bc, values) == 0x381c0, "381c0");
static_assert(__builtin_offsetof(Obj1451bc, slots) == 0x381f0, "381f0");
static_assert(__builtin_offsetof(Obj1451bc, pair38250) == 0x38250, "38250");

// 0x71001451bc: a constructor: member arrays built by their element constructors, five lists zeroed by their own
// constructors, then storage from the default heap; the heap takes the byte count as 32 bits, the last two arrays
// come from a clearing allocator (one memset over the full size before the element constructors), and the pair
// lists are arrays of 8-byte pairs so the byte count stays one shift of the halved count
Obj1451bc::Obj1451bc() {
    init_slots_1451bc(&slots, callee_170c58() + 10);
    init_pair_1451bc(&pair38210, static_cast<unsigned int>(callee_170c58()) >> 1);
    init_pair_1451bc(&pair38230, static_cast<unsigned int>(callee_170c58()) >> 1);
    init_pair_1451bc(&pair38250, callee_170c58());
    unsigned int count = callee_170c58();
    elems = new (ZeroHeapTag_1451bc{}) Elem15aa9c[count];
    values = new (ZeroHeapTag_1451bc{}) int[count];
}
