// Unit commands (0x71001c4b64-0x71001c70e0): resolve a command's unit id (0x78 is the local
// player's unit, 0x79-0x7c the roster aliases, 0x50-0x5f stepped by difficulty) and store the
// command's value in a field of the unit's record when the unit belongs to one of the three teams.
// Names are descriptive placeholders. Status: matching/README.md.

struct RosterSlot {
    unsigned char pad[0x1c];
    int unit;                 // +1c
};

struct RosterPlayer {
    unsigned char pad[8];
    RosterSlot* slot;         // +08
};

struct RosterTable {
    unsigned char pad[0xb08];
    RosterPlayer* players[2]; // +b08
    RosterSlot* slots[4];     // +b18

    RosterPlayer* player(int index) { return static_cast<unsigned int>(index) < 2 ? players[index] : players[0]; }
};

struct StepInfo {
    unsigned char pad[4];
    int step;                 // +04
};

struct StepOwner {
    unsigned char pad[0x139948];
    StepInfo* info;           // +139948
};

struct MemberList {
    unsigned short* data;     // +00
    int capacity;             // +08
    int count;                // +0c

    unsigned short get(int index) const { return index < count ? data[index] : 0; }
};

struct UnitRecord {
    unsigned char pad[0x20];
    float position[9];        // +20

    unsigned int team;        // +44
    unsigned char pad48[0x14];
    int leader;               // +5c
    unsigned char pad60[0x48];
    int values[3];            // +a8
    unsigned char padb4[0x64];
    unsigned int flag_bits : 25; // +118
    unsigned int stance : 2;
    unsigned int high_bits : 5;
    unsigned int : 0;
    unsigned int state_low : 16; // +11c
    unsigned int following : 1;
    unsigned int state_mid : 3;
    unsigned int side : 1;
    unsigned int state_high : 11;
    int timers[4];            // +120
    unsigned char pad130[8];
    MemberList members;       // +138
    unsigned char pad148[0x18];
};

struct OfficerRecord {
    unsigned char pad[0x18];
    unsigned char active : 1; // +18
    unsigned char pad19[7];
    unsigned char visible : 1; // +20
    unsigned char pad21[7];
    unsigned int kind;        // +28
    unsigned char pad2c[0x18];
    unsigned int type;        // +44
    unsigned char pad48[0x688];
};

struct OfficerType {
    unsigned char pad[0x30];
    unsigned char flags;      // +30
    unsigned char pad31[0xb];
};

struct UnitRoster {
    unsigned char pad[0xc20];
    UnitRecord units[0xf6];   // +c20
    OfficerRecord officers[300]; // +15e60
    unsigned char pad95a20_gap[0x95a20 - 0x15e60 - 300 * 0x6d0];
    OfficerType* types;       // +95a20

    UnitRecord* unit(unsigned int id) { return id < 0xf6 ? &units[id] : nullptr; }
    OfficerRecord* officer(unsigned int id) { return id < 300 ? &officers[id] : nullptr; }
};

// Reached through the GOT slot at 0x7100c21698.
extern RosterTable* gRecord_c21698;
// Reached through the GOT slot at 0x7100c22ca8.
extern StepOwner* gGlobal_c22ca8;
struct UnitState {
    unsigned char pad[0x94];
    int value;                // +94
    unsigned char pad98[0x88];
};

struct OfficerState {
    int order;                // +00
    int timer;                // +04
    int reset;                // +08
    unsigned char padc[0xf4];
};

struct UnitStates {
    UnitState units[0xf6];    // +00
    unsigned char pad114c0[0xe8];
    OfficerState officers[300]; // +115a8
};

// Reached through the GOT slot at 0x7100c22bd8.
extern UnitStates* gBlock_c22bd8;
// Reached through the GOT slot at 0x7100c216e8.
extern UnitRoster* gShop;

struct LocalPlayer {
    LocalPlayer() {}

    int index;
};

static inline int resolve_unit(int id) {
    if (id == 0x78) {
        static LocalPlayer local;
        int index = local.index;
        id = gRecord_c21698->player(index)->slot->unit;
    } else {
        int alias = id - 0x79;
        if (static_cast<unsigned int>(alias) <= 3)
            id = gRecord_c21698->slots[alias]->unit;
    }
    StepInfo* info = gGlobal_c22ca8->info;
    if (info && info->step && (id & ~0xf) == 0x50)
        id += info->step * 5 - 5;
    return id;
}

struct UnitCommand {
    int pad0;
    int unit;                 // +04
    int value;                // +08
    int extra[2];             // +0c
};

// 0x71001c6db0
void set_unit_value0_1c6db0(const UnitCommand* command) {
    int id = resolve_unit(command->unit);
    UnitRecord* unit = gShop->unit(id);
    if (unit->team <= 2)
        unit->values[0] = command->value;
}

// 0x71001c6ec0
void set_unit_value1_1c6ec0(const UnitCommand* command) {
    int id = resolve_unit(command->unit);
    UnitRecord* unit = gShop->unit(id);
    if (unit->team <= 2)
        unit->values[1] = command->value;
}

// 0x71001c6fd0
void set_unit_value2_1c6fd0(const UnitCommand* command) {
    int id = resolve_unit(command->unit);
    UnitRecord* unit = gShop->unit(id);
    if (unit->team <= 2)
        unit->values[2] = command->value;
}

// 0x71001c4b64
void set_unit_state_1c4b64(const UnitCommand* command) {
    int id = resolve_unit(command->unit);
    gBlock_c22bd8->units[static_cast<unsigned int>(id)].value = command->value;
}

// 0x71001c70e0
void clear_unit_timers_1c70e0(const UnitCommand* command) {
    int which = command->value;
    int id = resolve_unit(command->unit);
    UnitRecord* unit = gShop->unit(id);
    if (unit->team > 2)
        return;
    switch (static_cast<unsigned char>(which)) {
    case 0:
        unit->timers[0] = 0;
        unit->timers[2] = 0;
        break;
    case 1:
        unit->timers[1] = 0;
        unit->timers[3] = 0;
        break;
    case 2:
        unit->timers[0] = 0;
        break;
    case 3:
        unit->timers[1] = 0;
        break;
    case 4:
        unit->timers[2] = 0;
        break;
    case 5:
        unit->timers[3] = 0;
        break;
    }
}
// 0x71001c66b4
void set_unit_stance_1c66b4(const UnitCommand* command) {
    int id = resolve_unit(command->unit);
    int mode = command->value;
    UnitRecord* unit = gShop->unit(id);
    switch (mode) {
    case 0:
        unit->stance = 0;
        break;
    case 1:
        unit->stance = 2;
        break;
    case 2:
        unit->stance = 1;
        break;
    }
}

static inline void set_alias(RosterTable* table, int slot, int id) {
    if (id != 0x78 && static_cast<unsigned int>(id) <= 0xf6)
        table->slots[slot]->unit = id;
}

// 0x71001c83d4
void set_aliases_1c83d4(const UnitCommand* command) {
    int first = resolve_unit(command->unit);
    int second = command->value;
    int third = command->extra[0];
    int fourth = command->extra[1];
    RosterTable* table = gRecord_c21698;
    set_alias(table, 0, first);
    set_alias(table, 1, second);
    set_alias(table, 2, third);
    set_alias(table, 3, fourth);
}
void notify_unit_114540(void* system, int unit, int flag);                  // 0x7100114540
void notify_unit_f2b34(void* system, int unit, int flag);                   // 0x71000f2b34
// Reached through the GOT slot at 0x7100c22a60.
extern void* gGlobal_c22a60;
// Reached through the GOT slot at 0x7100c22be8.
extern void* gGlobal_c22be8;

// 0x71001c36f0
void notify_unit_1c36f0(const UnitCommand* command) {
    int id = resolve_unit(command->unit);
    notify_unit_114540(gGlobal_c22a60, id, 1);
    notify_unit_f2b34(gGlobal_c22be8, id, 1);
}

// 0x71001c46f4
void order_members_1c46f4(const UnitCommand* command) {
    int id = resolve_unit(command->unit);
    UnitRecord* unit = gShop->unit(id);
    unsigned int count = unit->members.count;
    if (!count)
        return;
    int order = command->value;
    for (unsigned int i = 0; i < count; ++i) {
        unsigned short member = unit->members.get(i);
        if (gShop->officer(member)->kind <= 0xf5) {
            OfficerState& state = gBlock_c22bd8->officers[member];
            state.order = order;
            state.timer = 5;
            state.reset = 5;
        }
    }
}
void play_effect_180850(int unit, int effect, const float* position, int a, int b, float scale); // 0x7100180850

// 0x71001c1ec4
void play_unit_effect_1c1ec4(const UnitCommand* command) {
    // Here the first field is the effect and the second the unit.
    int id = resolve_unit(command->value);
    UnitRecord* unit = gShop->unit(id);
    if (unit->team <= 2)
        play_effect_180850(command->unit, -1, unit->position, 0, 1, 1.0f);
}
float leader_rate_1947f0(UnitRecord* unit);                                 // 0x71001947f0
void set_rate_1949a8(UnitRecord* unit, unsigned int rate);                  // 0x71001949a8
void set_side_flag_1949b0(UnitRecord* unit, bool flag);                     // 0x71001949b0
bool type_loaded_172174(int type);                                          // 0x7100172174

// 0x71001c4c5c
void set_unit_follow_1c4c5c(const UnitCommand* command) {
    int id = resolve_unit(command->unit);
    unsigned char enable = command->value;
    UnitRecord* unit = gShop->unit(id);
    if (!enable) {
        unit->following = 0;
        return;
    }
    set_rate_1949a8(unit, leader_rate_1947f0(unit) * 1000.0f);
    UnitRoster* roster = gShop;
    OfficerRecord* leader = roster->officer(unit->members.get(unit->leader));
    bool flag;
    if (!leader->active || !leader->visible) {
        flag = unit->side;
    } else {
        unsigned int type = leader->type;
        type_loaded_172174(type);
        flag = (roster->types[type].flags >> 5) & 1;
    }
    set_side_flag_1949b0(unit, flag);
    unit->following = 1;
}