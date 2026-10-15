// 0x710003e934 (1,620 B), fourth session, parked. Build: this file alone, try.py with build/s3rank/r3e934_d.json
// from rank.py and --map for the callees whose names do not end in five or six hex digits (3334, 31934, 172174,
// 1a8584, 5b898, 5b904, 5c85c). State: 1,640 B, 79 instructions off with registers abstracted.
// What is right: case 2 written first (Clang then tests 0x1c, 0x18, 2 as the original does), the unit lookup
// computing the address before choosing null (the select survives, so the null csel stays), the signed-char range
// test as v >= -0x80 && v < 0x80, the 0x18 case written already jump-threaded, the leader id held as int.
// Still different: our 0x1c and default cases share their field_10/field_c stores (tail merge), the original keeps
// them apart; the order of the 0xf4820 object, the unit table and field_a around the 3334 call.
void* callee_214000();                                                       // 0x7100214000
void* callee_214200(void*, int);                                             // 0x7100214200
int callee_213f00(void*);                                                    // 0x7100213f00
int callee_1fb214(void*, int);                                               // 0x71001fb214
void* callee_3334(void*, int, int, int);                                     // 0x7100003334
unsigned char callee_172174(unsigned int);                                   // 0x7100172174
void callee_31934(unsigned int, int);                                        // 0x7100031934
void callee_1a8584(void*, unsigned int);                                     // 0x71001a8584
void callee_5b898(void*, int, unsigned int);                                 // 0x710005b898
void callee_5b904(void*, unsigned int);                                      // 0x710005b904
unsigned char callee_5c85c(void*, void*);                                    // 0x710005c85c

struct Unit3e934 {
    unsigned char pad0[0xa];
    short field_a;                 // +a
    short field_c;                 // +c
    unsigned char pade[2];
    short field_10;                // +10
    unsigned char pad12[0x25];
    signed char field_37;          // +37
    unsigned char pad38[0x18];
};

struct Slot3e934 {
    int field_0;                   // +0
    int field_4;                   // +4
    int field_8;                   // +8
    unsigned char padc[0x30];
};

struct Game3e934 {
    unsigned char pad0[0x16558];
    int field_16558;               // +16558
    unsigned char pad1655c[0x7f4c4];
    Slot3e934* slots;              // +95a20

    Slot3e934* slot(unsigned int i) {
        if (callee_172174(i) & 0xff) {
            return nullptr;
        }
        return &slots[i];
    }
};

struct Ret3334_3e934 {
    unsigned char pad0[0x4c];
    short field_4c;                // +4c
};

struct Msg3e934 {
    unsigned char pad0[0x34];
    int field_34;                  // +34
    unsigned char pad38[8];
};

// Reached through the GOT slot at 0x7100c21df8.
extern void* gGlobalc21df8_3e934;
// Reached through the GOT slot at 0x7100c216a0.
extern Unit3e934* gGlobalc216a0_3e934;
// Reached through the GOT slot at 0x7100c216f0.
extern unsigned char* gGlobalc216f0_3e934;
// Reached through the GOT slot at 0x7100c216e8.
extern Game3e934* gGlobalc216e8_3e934;
// Reached through the GOT slot at 0x7100c21e00.
extern unsigned int gGlobalc21e00_3e934;
// Reached through the GOT slot at 0x7100c21e08.
extern unsigned int gGlobalc21e08_3e934;
// Reached through the GOT slot at 0x7100c21690.
extern unsigned char* gGlobalc21690_3e934;

static inline Unit3e934* unit_3e934(int id) {
    Unit3e934* p = &gGlobalc216a0_3e934[id];
    return static_cast<unsigned int>(id) < 0x44c ? p : nullptr;
}

static inline Unit3e934* unitS_3e934(short id) {
    Unit3e934* p = &gGlobalc216a0_3e934[id];
    return static_cast<unsigned short>(id) < 0x44c ? p : nullptr;
}

static inline bool valid37_3e934(int v) {
    return static_cast<unsigned int>(v) < 0x24 && v >= -0x80 && v < 0x80;
}

static inline bool valid10_3e934(int v) {
    return static_cast<unsigned int>(v) < 0x27f || v == -1;
}

static inline bool validKind_3e934(int v) {
    return static_cast<short>(v) == v && (static_cast<unsigned int>(v) < 0x40 || v == -1);
}

static inline void setUnit_3e934(int id, int kind, int b, int h) {
    if (valid37_3e934(b)) {
        unit_3e934(id)->field_37 = static_cast<signed char>(b);
    }
    if (valid10_3e934(h)) {
        unit_3e934(id)->field_10 = static_cast<short>(h);
    }
    if (validKind_3e934(kind)) {
        unit_3e934(id)->field_c = static_cast<short>(kind);
    }
}

// 0x710003e934
void call_3e934(int p0, int p1, int p2) {
    int kind = callee_213f00(callee_214200(callee_214000(), p2));
    switch (kind) {
    case 2: {
        int id = callee_1fb214(gGlobalc21df8_3e934, p0);
        short a = unit_3e934(id)->field_a;
        int s = static_cast<Ret3334_3e934*>(callee_3334(gGlobalc216f0_3e934 + 0xf4820, a, id, p2))->field_4c;
        if (valid37_3e934(p1)) {
            unitS_3e934(s)->field_37 = static_cast<signed char>(p1);
        }
        unsigned int cur = gGlobalc21e00_3e934;
        gGlobalc216e8_3e934->slot(cur)->field_4 = s;
        callee_31934(cur, 0);
        break;
    }
    case 0x18: {
        int id = callee_1fb214(gGlobalc21df8_3e934, p0);
        short a = unit_3e934(id)->field_a;
        int s = static_cast<Ret3334_3e934*>(callee_3334(gGlobalc216f0_3e934 + 0xf4820, a, id, p2))->field_4c;
        unsigned int cur;
        if (valid37_3e934(p1)) {
            unitS_3e934(s)->field_37 = static_cast<signed char>(p1);
            cur = gGlobalc21e00_3e934;
            gGlobalc216e8_3e934->slot(cur)->field_4 = s;
            callee_31934(cur, 0);
            unit_3e934(id)->field_37 = static_cast<signed char>(p1);
        } else {
            cur = gGlobalc21e00_3e934;
            gGlobalc216e8_3e934->slot(cur)->field_4 = s;
            callee_31934(cur, 0);
        }
        if (valid10_3e934(p2)) {
            unit_3e934(id)->field_10 = static_cast<short>(p2);
        }
        unit_3e934(id)->field_c = 0x18;
        unsigned int other = gGlobalc21e08_3e934;
        Slot3e934* o = gGlobalc216e8_3e934->slot(other);
        callee_1a8584(o, other);
        o->field_4 = id;
        o->field_8 = 0x10000;
        gGlobalc216e8_3e934->field_16558 = 1;
        callee_31934(other, 1);
        Msg3e934 msg;
        callee_5b898(&msg, 0xd, cur);
        callee_5b904(&msg, other);
        msg.field_34 = 0x2f;
        callee_5c85c(gGlobalc21690_3e934 + 0xf3b00, &msg);
        break;
    }
    case 0x1c: {
        int id = callee_1fb214(gGlobalc21df8_3e934, p0);
        short a = unit_3e934(id)->field_a;
        int s = static_cast<Ret3334_3e934*>(callee_3334(gGlobalc216f0_3e934 + 0xf4820, a, id, p2))->field_4c;
        setUnit_3e934(id, 0x1c, p1, p2);
        unsigned int cur = gGlobalc21e00_3e934;
        gGlobalc216e8_3e934->slot(cur)->field_4 = id;
        callee_31934(cur, 0);
        if (valid37_3e934(p1)) {
            unitS_3e934(s)->field_37 = static_cast<signed char>(p1);
        }
        unsigned int other = gGlobalc21e08_3e934;
        Slot3e934* o = gGlobalc216e8_3e934->slot(other);
        callee_1a8584(o, other);
        o->field_4 = s;
        o->field_8 = 0x10000;
        gGlobalc216e8_3e934->field_16558 = 1;
        callee_31934(other, 1);
        Msg3e934 msg;
        callee_5b898(&msg, 0xd, cur);
        callee_5b904(&msg, other);
        callee_5c85c(gGlobalc21690_3e934 + 0xf3b00, &msg);
        break;
    }
    default: {
        int id = callee_1fb214(gGlobalc21df8_3e934, p0);
        setUnit_3e934(id, kind, p1, p2);
        unsigned int cur = gGlobalc21e00_3e934;
        gGlobalc216e8_3e934->slot(cur)->field_4 = id;
        callee_31934(cur, 0);
        break;
    }
    }
}
