// Fifth session, parked: 0x7100423e04 (2,808 bytes), a battle display mode switch. This source compiles to the
// original size with 61 instructions differing (abstract 21). Still different: the first test (the original keeps
// !force in a register and branches on it after the mode compare: a br on an and of two compares that
// CodeGenPrepare split), the order of the three stage tests in case 3, the two flag bytes at +8c/+8d that Clang
// loads as one halfword here, and where the shared tail (flag store, mode store, return 1) is placed.
// Map: got:gGlobalc21698_423e04=0x7100c21698 got:gGlobalc216e8_423e04=0x7100c216e8 .rodata=0x710080fc40.

struct Panel423e04 {
    unsigned char pad0[0x10];
    unsigned char field_10[0xe8];     // +10
    unsigned int flags;               // +f8
};

struct Slot423e04 {
    unsigned char pad0[0x10];
    void* field_10;                   // +10
};

struct Entry423e04 {
    unsigned char pad0[0x8];
    Slot423e04* field_8;              // +8
};

struct Game423e04 {
    unsigned char pad0[0xb08];
    Entry423e04* field_b08;           // +b08
    Entry423e04* field_b10;           // +b10
};

extern Game423e04* gGlobalc21698_423e04;
struct PlayerSlot423e04 {
    unsigned int flags;               // +0
    unsigned char pad4[0x30c];
};

struct Players423e04 {
    unsigned char pad0[0xcf120];
    PlayerSlot423e04 players[24];     // +cf120
};

extern Players423e04* gGlobalc216e8_423e04;

struct Battle423e04;
void callee_41c644(Battle423e04*, int, int);        // 0x710041c644
void callee_41c544(Battle423e04*, int, int, int, void*, void*, void*);        // 0x710041c544
void callee_1d2a1c(unsigned int);        // 0x71001d2a1c
void callee_423888(Battle423e04*, float);        // 0x7100423888
void callee_43eb10(Panel423e04*, int);        // 0x710043eb10
void callee_3fe1a4(int, void*, int, void*, void*, int, float, float);        // 0x71003fe1a4
unsigned int callee_200acc(void*);        // 0x7100200acc
void callee_4239e4(Battle423e04*, unsigned int);        // 0x71004239e4

static inline unsigned int target_of(Entry423e04* entry) {
    void* p = entry->field_8->field_10;
    return p != nullptr ? callee_200acc(p) : 0xffffffff;
}

static inline bool special_stage(unsigned int stage) {
    return (stage - 0x20 < 3) || (stage - 0x32 < 0x1e);
}

struct Battle423e04 {
    unsigned char pad0[0x10];
    float field_10;                   // +10
    unsigned char pad14[0x10];
    unsigned int field_24;            // +24
    int mode;                         // +28
    unsigned char pad2c[0x1c];
    unsigned char field_48;           // +48
    unsigned char pad49[0x7];
    Panel423e04* panels[4];           // +50
    unsigned char pad70[0x14];
    unsigned int stage;               // +84
    unsigned int player;              // +88
    unsigned char field_8c;           // +8c
    unsigned char field_8d;           // +8d
    unsigned char pad8e[0x2];
    unsigned int field_90;            // +90

    long side(int own) {
        unsigned int id = stage;
        if (special_stage(id)) {
            return own ? 0 : 2;
        }
        return static_cast<long>(own ? id < 0xc9 : id > 200) << 1;
    }
    Panel423e04* panel(int own, int second) {
        return panels[second ? side(own) | 1 : side(own)];
    }
    int set_mode(int mode, unsigned char force);
};

// 0x7100423e04: switches the battle display to MODE (0 to 6), showing and hiding the four panels of both sides;
// returns 0 when the switch is refused.
int Battle423e04::set_mode(int new_mode, unsigned char force) {
    int old = mode;
    if (old == new_mode && !force) {
        return 1;
    }
    unsigned char flag;
    switch (new_mode) {
    case 0:
        if (!force && old == 5) {
            return 0;
        }
        callee_41c644(this, 0, 1);
        panel(1, 0)->flags |= 4;
        panel(1, 1)->flags |= 4;
        callee_43eb10(panel(1, 0), 0);
        callee_43eb10(panel(1, 1), 0);
        panel(0, 0)->flags |= 4;
        panel(0, 1)->flags |= 4;
        callee_43eb10(panel(0, 0), 0);
        callee_43eb10(panel(0, 1), 0);
        flag = 0;
        break;
    case 1:
        if (!force && old != 2) {
            if (old == 6 || old == 0) {
                callee_41c544(this, 0, 0, 1, nullptr, nullptr, nullptr);
            } else {
                callee_423888(this, 0.0f);
                return 0;
            }
            callee_1d2a1c(field_24);
            field_10 = 2.0f;
        } else {
            callee_41c644(this, 0, 0);
            panel(1, 0)->flags &= ~4;
            panel(1, 1)->flags &= ~4;
            callee_43eb10(panel(1, 0), 1);
            callee_43eb10(panel(1, 1), 1);
            panel(0, 0)->flags |= 4;
            panel(0, 1)->flags |= 4;
            callee_43eb10(panel(0, 0), 0);
            callee_43eb10(panel(0, 1), 0);
        }
        callee_423888(this, 0.0f);
        flag = 0;
        break;
    case 2:
        if (!force && old != 1) {
            return 0;
        }
        callee_41c544(this, 0, 0, 0, nullptr, nullptr, nullptr);
        flag = 0;
        break;
    case 3:
        if (!force && old != 1 && old != 2) {
            return 0;
        }
        if (stage < 0xc9 && stage - 0x32 >= 0x1e && stage - 0x20 >= 3) {
            callee_3fe1a4(0x2e8, panels[side(1)]->field_10, 0, nullptr, nullptr, 0x3c, 1.0f, 0.0f);
            field_10 = 0.5f;
        } else {
            unsigned int target = field_90;
            if (target == 0xffffffff) {
                target = field_8c ? target_of(gGlobalc21698_423e04->field_b08) : 0xffffffff;
                if (field_8d) {
                    target = target_of(gGlobalc21698_423e04->field_b10);
                }
            }
            if (target != 0xffffffff) {
                callee_4239e4(this, target);
            }
            callee_43eb10(panel(1, 0), 1);
            callee_43eb10(panel(1, 1), 1);
            panel(0, 0)->flags |= 4;
            panel(0, 1)->flags |= 4;
            callee_43eb10(panel(0, 0), 0);
            callee_43eb10(panel(0, 1), 0);
        }
        if (player < 0x18) {
            gGlobalc216e8_423e04->players[player].flags |= 0x20;
        }
        flag = 1;
        break;
    case 5: {
        callee_41c644(this, 0, 0);
        callee_423888(this, 1.0f);
        unsigned int id = stage;
        bool shown = id != 0xffffffff;
        Panel423e04* p = panel(1, 0);
        if (shown) {
            p->flags &= ~4;
        } else {
            p->flags |= 4;
        }
        p = panel(1, 1);
        if (shown) {
            p->flags &= ~4;
        } else {
            p->flags |= 4;
        }
        callee_43eb10(panel(1, 0), shown);
        callee_43eb10(panel(1, 1), shown);
        panel(0, 0)->flags |= 4;
        panel(0, 1)->flags |= 4;
        callee_43eb10(panel(0, 0), 0);
        callee_43eb10(panel(0, 1), 0);
        flag = 0;
        if (shown) {
            field_10 = 1.0f;
        }
        break;
    }
    case 6:
        callee_41c644(this, 0, 0);
    case 4:
        panel(1, 0)->flags |= 4;
        panel(1, 1)->flags |= 4;
        callee_43eb10(panel(1, 0), 0);
        callee_43eb10(panel(1, 1), 0);
        panel(0, 0)->flags |= 4;
        panel(0, 1)->flags |= 4;
        callee_43eb10(panel(0, 0), 0);
        callee_43eb10(panel(0, 1), 0);
        flag = 0;
        break;
    default:
        return 0;
    }
    field_48 = flag;
    mode = new_mode;
    return 1;
}
