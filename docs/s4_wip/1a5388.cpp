// 0x71001a5388 (1,648 B), fourth session, parked. Build: this file alone, try.py with a symbol file holding
// got:gGlobalc22c40_1a5388=0x7100c22c40 and memcpy=0x7100600870. Types as in misc/s4_functions01.cpp (1a4b48).
// State: same size, 1 instruction off: in the latch of the records loop the original advances the destination
// pointer first (add x21; add x22; sub x23), ours advances it after the count. The index form of the loop gets that
// order but gives the source pointer x21 and the destination x22 (6 off, 0 with registers abstracted).
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

// Reached through the GOT slot at 0x7100c22c40.
extern unsigned char* gGlobalc22c40_1a5388;
void* callee_1b02cc(void*, int);                                             // 0x71001b02cc
void* callee_218d18(void*, int, int);                                        // 0x7100218d18

// 0x71001a5388
void call_1a5388(Src1a4b48* p0, Dst1a4b48* p1) {
    for (int i = 0; i < 2; i++) {
        p0->recs[i] = p1->recs[i];
    }
    {
        RecC0_1a4b48* d = p0->recs + 2;
        RecC0_1a4b48* s = p1->recs + 2;
        for (long i = 2; i < 34; i++) {
            *d = *s;
            if (d->field_a8 != 0xff) {
                d->field_b0 = callee_1b02cc(gGlobalc22c40_1a5388 + 0xb8, d->field_a8);
            }
            d++;
            s++;
        }
    }
    for (int i = 0; i < 32; i++) {
        p0->pairs[i] = p1->pairs[i];
    }
    p0->str8a = p1->str8a;
    p0->strc3 = p1->strc3;
    p0->str27 = p1->str27;
    p0->field_1f4e = p1->field_1b84;
    p0->field_1f50 = p1->field_1b86;
    p0->field_19e0 = p1->field_1b88;
    p0->field_19dc = p1->field_1b8c;
    p0->field_19e4 = p1->field_1b80;
    p0->field_19e8 = p1->field_1b8a;
    p0->field_19ec = p1->field_1b91;
    p0->field_1f4d = p1->field_1b93;
    p0->field_19d4 = p1->field_1b8d;
    p0->field_19d8 = p1->field_1b90;
    p0->field_19d0 = p1->field_1b8e;
    for (int i = 0; i < 2; i++) {
        p0->recs[i].field_b0 = callee_218d18(&p0->objs[i], p0->recs[i].field_a8, 0);
    }
    for (int i = 0; i < 4; i++) {
        p0->rec24[i].field_0 = p1->rec24[i].field_0;
        p0->rec24[i].field_8 = p1->rec24[i].field_8;
        p0->rec24[i].field_18 = p1->rec24[i].field_18;
        p0->rec24[i].field_1e = p1->rec24[i].field_1e;
        p0->rec24[i].field_20 = p1->rec24[i].field_20;
        p0->rec24[i].field_1c = p1->rec24[i].field_1c;
        p0->rec24[i].field_1a = p1->rec24[i].field_1a;
    }
    p0->tail.field_0 = p1->tail.field_0;
    p0->tail.field_1 = p1->tail.field_1;
    p0->tail.field_2 = p1->tail.field_2;
    p0->tail.name = p1->tail.name;
    p0->tail.field_13 = p1->tail.field_13;
    p0->tail.field_14 = p1->tail.field_14;
    p0->tail.field_15 = p1->tail.field_15;
    p0->tail.field_17 = p1->tail.field_17;
    p0->tail.field_19 = p1->tail.field_18;
    p0->tail.field_1a = p1->tail.field_19;
}