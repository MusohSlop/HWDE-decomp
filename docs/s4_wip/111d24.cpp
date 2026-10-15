// 0x7100111d24 (2,676 B), fourth session, parked. Build: this file alone, try.py with build/s4/empty.json and
// --map _Z13callee_16ef34v=0x710016ef34 --map _Z13callee_20fbd4v=0x710020fbd4 --map _Z13callee_20ff14Pv=0x710020ff14.
// State: same size, 5 instructions off (1 with registers abstracted): in the reset branch the trip count 10 and
// the -1.0f bits are materialised in the other order (the original has -1.0f first, in w9), so w9/w10 swap.
// The load branch is the reverse of 11298c (struct-assignment loops) and matches. Index loops are needed: pointer
// loops over the entries are fully unrolled. Field order c a b d e f g h is the closest of those tried.
struct Rec14_11298c {
    int v[5];
};

struct Rec18_11298c {
    int v[6];
};

class Entry1d_111d24 {
public:
    Entry1d_111d24() : a(3), b(-1), c(-1.0f), d(-1.0f), e(-1), f(false), g(-1), h(true) {}

    int a;                           // +0
    int b;                           // +4
    float c;                         // +8
    float d;                         // +c
    int e;                           // +10
    bool f;                          // +14
    int g;                           // +18
    bool h;                          // +1c
};

struct Save111d24 {
    int count;                       // +0
    Rec14_11298c recs[32];           // +4
    Rec18_11298c last;               // +284
    Entry1d_111d24 names[10];        // +29c
};

struct Obj111d24 {
    unsigned char pad0[0xedc];
    int field_edc;                   // +edc
    int field_ee0;                   // +ee0
    unsigned char padee4[0x280];
    int count;                       // +1164
    Rec14_11298c recs[32];           // +1168
    int field_13e8;                  // +13e8
    unsigned char pad13ec[0x50c];
    Entry1d_111d24 names[10];        // +18f8
    Rec18_11298c last;               // +1a38
};

struct Flags111d24 {
    unsigned char pad0[2];
    unsigned char field_2;           // +2
};

Flags111d24* callee_16ef34();                                                // 0x710016ef34
void* callee_20fbd4();                                                       // 0x710020fbd4
unsigned char* callee_20ff14(void*);                                         // 0x710020ff14

// 0x7100111d24
void call_111d24(Obj111d24* p0) {
    p0->field_edc = 0;
    p0->field_ee0 = 0;
    if (callee_16ef34()->field_2 & 1) {
        Save111d24* s = reinterpret_cast<Save111d24*>(callee_20ff14(callee_20fbd4()) + 0x40190);
        p0->count = s->count;
        for (int i = 0; i < 32; i++) {
            p0->recs[i] = s->recs[i];
        }
        p0->last = s->last;
        for (int i = 0; i < 10; i++) {
            p0->names[i] = s->names[i];
        }
    } else {
        for (int i = 0; i < 32; i++) {
            p0->recs[i].v[0] = 7;
        }
        p0->count = 0;
        for (int i = 0; i < 10; i++) {
            p0->names[i].c = -1.0f;
            p0->names[i].a = 3;
            p0->names[i].b = -1;
            p0->names[i].d = -1.0f;
            p0->names[i].e = -1;
            p0->names[i].f = false;
            p0->names[i].g = -1;
            p0->names[i].h = true;        }
        p0->last.v[0] = 2;
    }
    p0->field_13e8 = 0;
}
