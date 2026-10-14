// Unit commands (0x71001c4b64-0x71001c70e0): resolve a command's unit id (0x78 is the local
// player's unit, 0x79-0x7c the roster aliases, 0x50-0x5f stepped by difficulty) and store the
// command's value in a field of the unit's record when the unit belongs to one of the three teams.
// Names are descriptive placeholders. Status: matching/README.md.

struct Gauge19d2 {
    unsigned char data[1];
};

struct RosterSlot {
    unsigned char pad[0x1c];
    int unit;                 // +1c
    unsigned char pad20[4];
    unsigned int officer_type; // +24
    unsigned char pad28[5];
    unsigned char started;    // +2d
    unsigned char active;     // +2e
    unsigned char pad2f[0x21];
    Gauge19d2 gauge;          // +50
    unsigned char pad51[0x147];
    int defeated;             // +198
    int captured;             // +19c
};

struct RosterPlayer {
    unsigned char pad[8];
    RosterSlot* slot;         // +08
};

struct RosterTable {
    unsigned char pad[0xb08];
    RosterPlayer* players[2]; // +b08
    RosterSlot* slots[4];     // +b18
    unsigned char padb38[0x10];
    unsigned int player_count; // +b48
    unsigned int slot_count;  // +b4c

    RosterPlayer* player(int index) { return static_cast<unsigned int>(index) < 2 ? players[index] : players[0]; }
    RosterSlot* slot(int index) { return static_cast<unsigned int>(index) < 4 ? slots[index] : slots[0]; }
    static int slot_index(int index) { return static_cast<unsigned int>(index) < 4 ? index : -1; }
};

struct StepInfo {
    unsigned char pad[4];
    int step;                 // +04
};

struct MessageEntry {
    unsigned char data[0x24c];
};

struct MessageQueue {
    unsigned int index;       // +00
    MessageEntry entries[1];  // +04
};

struct StepBits {
    unsigned char data[0x7a8];
};

struct StepOwner {
    unsigned char pad[0x138b90];
    StepBits bits;            // +138b90
    MessageQueue messages;    // +139338
    unsigned char pad139588[0x350];
    int fade_mode;            // +1398d8
    float fade_rate;          // +1398dc
    unsigned char pad1398e0[0x60];
    unsigned char state;      // +139940
    StepInfo* info;           // +139948
    unsigned char recording;  // +139950
};

struct MemberList {
    unsigned short* data;     // +00
    int capacity;             // +08
    int count;                // +0c

    unsigned short get(int index) const { return index < count ? data[index] : 0; }
};

struct UnitRecord {
    unsigned char pad[0x20];
    float position[8];        // +20
    float speed;              // +40

    unsigned int team;        // +44
    unsigned char pad48[4];
    int item_field;           // +4c
    unsigned char pad50[8];
    int item;                 // +58
    int leader;               // +5c
    unsigned char pad60[4];
    int rank;                 // +64
    unsigned char pad68[4];
    int category;             // +6c
    unsigned char pad70[4];
    int group_value;          // +74
    unsigned char pad78[0x30];
    int values[3];            // +a8
    unsigned char padb4[0x18];
    unsigned int limits[2];   // +cc
    unsigned char padd4[0x20];
    unsigned int damage;      // +f4
    unsigned char padf8[0x18];
    int ai_mode;              // +110
    unsigned char pad114[4];
    unsigned int flag_bits : 25; // +118
    unsigned int stance : 2;
    unsigned int high_bits : 5;
    unsigned int : 0;
    unsigned int state_kind : 3; // +11c
    unsigned int state_low : 7;
    unsigned int order : 3;
    unsigned int state_mid_low : 3;
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
    unsigned char pad2c[8];
    int max_level;            // +34
    int level;                // +38
    unsigned char pad3c[4];
    int item;                 // +40
    unsigned int type;        // +44
    unsigned int health;      // +48
    unsigned char pad4c[0x20];
    unsigned char status;     // +6c
    unsigned char pad6d[0x663];
};

struct CampRecord {
    unsigned char active;     // +00
    unsigned char pad1[0xb];
    unsigned int team;        // +0c
    unsigned char pad10[0x20];
};

struct alignas(16) SpotPosition {
    float x;                  // +00
    float y;                  // +04
    float z;                  // +08
    float w;                  // +0c
};

struct SpotRecord {
    SpotPosition position;    // +00
    unsigned char pad10[0x20];
    unsigned int points[4];   // +30
    unsigned char pad40[0x164];
    unsigned int limits[2];   // +1a4
    unsigned char pad1ac[0x164];
};

struct PointPosition {
    float x;                  // +00
    float y;                  // +04
    float z;                  // +08
    float w;                  // +0c
};

struct PointRecord {
    unsigned char pad[0x10];
    PointPosition position;   // +10
    unsigned char pad20[0x14];
    int active;               // +34
    unsigned char pad38[8];
    unsigned char enabled : 1; // +40
    unsigned char pad41[0xf];
};

struct LinkCell {
    unsigned char kind;       // +00
    unsigned char value;      // +01
    unsigned char pad2[2];
    unsigned char state;      // +04
    unsigned char pad5[3];
};

struct OfficerType {
    unsigned char pad[0x30];
    unsigned char flags;      // +30
    unsigned char pad31[0xb];
};

struct RosterTeam {
    unsigned char pad[4];
    int score;                // +04
    unsigned char pad8[0x7f];
    unsigned char : 1;        // +87
    unsigned char hold : 1;
    unsigned char : 2;
    unsigned char guard : 1;
    unsigned char rally : 1;
    unsigned char pad88[0x250];
    MemberList commanders;    // +2d8
    unsigned char pad2e8[0x38];
    MemberList guards;        // +320
    unsigned char pad330[8];
};

struct UnitRoster {
    unsigned char pad[0x278];
    RosterTeam teams[3];      // +278
    UnitRecord units[0xf6];   // +c20
    OfficerRecord officers[300]; // +15e60
    unsigned char pad95a20_gap[0x95a20 - 0x15e60 - 300 * 0x6d0];
    OfficerType* types;       // +95a20
    unsigned char pad95a28[0xc6dc0 - 0x95a28];
    LinkCell links[0x40][0x40]; // +c6dc0
    unsigned char padcedc0[0x80];
    SpotRecord spots[0x18];   // +cee40
    CampRecord camps[10];     // +d37c0
    PointRecord points[0x40]; // +d39a0

    CampRecord* camp(unsigned int id) { return id < 10 ? &camps[id] : nullptr; }
    SpotRecord* spot(unsigned int id) { return id < 0x18 ? &spots[id] : nullptr; }
    PointRecord* point(unsigned int id) { return id < 0x40 ? &points[id] : nullptr; }
    LinkCell* link(unsigned int from, unsigned int to) {
        unsigned int column = to < 0x40 ? to : 0;
        LinkCell* row = links[from < 0x40 ? from : 0];
        return &row[column];
    }

    UnitRecord* unit(unsigned int id) { return id < 0xf6 ? &units[id] : nullptr; }
    RosterTeam* team(unsigned int id) { return id < 3 ? &teams[id] : nullptr; }
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
struct SpawnedUnit {
    unsigned char pad[0x20];
    float position[10];       // +20
    unsigned int officer;     // +48
};
SpawnedUnit* find_spawned_1b93b8(int unit, int a, int b);                   // 0x71001b93b8
unsigned char stage_busy_1d740c(StepOwner* owner);                                   // 0x71001d740c

struct BattleMusic {
    unsigned char pad[0x3e];
    short level;              // +3e
};
BattleMusic* current_music_6b40();                                          // 0x7100006b40
unsigned char music_flag_20d9c8(BattleMusic* music, int flag);                       // 0x710020d9c8
void release_unit_1140c4(void* system, unsigned int officer, int flag);     // 0x71001140c4
void release_unit_f2824(void* system, unsigned int officer, int flag);      // 0x71000f2824

struct Container18f12c;
struct EffectQueue;
EffectQueue* member_18f12c(Container18f12c* container);                     // 0x710018f12c
void queue_effect_19a914(EffectQueue* queue, const float* position, int a, void* b, int c); // 0x710019a914

// 0x71001c2ef8
void dismiss_unit_1c2ef8(const UnitCommand* command) {
    if (stage_busy_1d740c(gGlobal_c22ca8))
        return;
    SpawnedUnit* spawned = find_spawned_1b93b8(resolve_unit(command->unit), 0, 0x44c);
    if (!spawned)
        return;
    unsigned int officer = spawned->officer;
    if (current_music_6b40()) {
        BattleMusic* music = current_music_6b40();
        if (music_flag_20d9c8(music, 0) && music->level >= 0) {
            BattleMusic* again = current_music_6b40();
            int calm = music_flag_20d9c8(again, 0) ? again->level < 3 : 1;
            if (officer <= 0xf5 && calm && gShop->units[officer].team)
                return;
        }
    }
    release_unit_1140c4(gGlobal_c22a60, officer, 1);
    release_unit_f2824(gGlobal_c22be8, officer, 1);
    queue_effect_19a914(member_18f12c(reinterpret_cast<Container18f12c*>(gShop)), spawned->position, 1, nullptr, 5);
}
unsigned char type_ready_172160(unsigned int type);                         // 0x7100172160
unsigned int gauge_max_19d25c(Gauge19d2* gauge);                            // 0x710019d25c
void set_gauge_19d31c(Gauge19d2* gauge, unsigned int value, unsigned int max); // 0x710019d31c
void clear_gauge_19d738(Gauge19d2* gauge);                                  // 0x710019d738

static inline int player_for_type(RosterTable* table, unsigned int type) {
    if (!type_ready_172160(type))
        return -1;
    for (int i = 0; i < table->player_count; ++i) {
        if (table->players[i]->slot->officer_type == type)
            return static_cast<unsigned int>(i) < 2 ? i : -1;
    }
    return -1;
}

// 0x71001c260c
void set_player_gauge_1c260c(const UnitCommand* command) {
    int id = resolve_unit(command->unit);
    UnitRoster* roster = gShop;
    UnitRecord* unit = roster->unit(id);
    if (unit->team > 2 || unit->state_kind)
        return;
    unsigned int level = static_cast<unsigned int>(command->value) > 3 ? 3 : command->value;
    unsigned int type = roster->officer(unit->members.get(unit->leader))->type;
    int player = player_for_type(gRecord_c21698, type);
    if (!type_ready_172160(type) || static_cast<unsigned int>(player) > 1)
        return;
    Gauge19d2* gauge = &gRecord_c21698->players[player]->slot->gauge;
    unsigned int max = gauge_max_19d25c(gauge);
    set_gauge_19d31c(gauge, level > max ? max : level, max);
    if (!level)
        clear_gauge_19d738(gauge);
}
void set_officer_mode_3e27c(unsigned int type, int mode, int flag);         // 0x710003e27c
void raise_unit_flags_133cf8(UnitState* state);                             // 0x7100133cf8
void refresh_unit_1d3f74(int unit);                                         // 0x71001d3f74
void reset_officer_1adac4(unsigned int officer, int a, int b, void* c);     // 0x71001adac4
void update_officer_1999d8(OfficerRecord* officer, int a, int b);           // 0x71001999d8
void sync_officer_1adf80(unsigned int officer);                             // 0x71001adf80

// 0x71001c4478
void set_unit_mode_1c4478(const UnitCommand* command) {
    int id = resolve_unit(command->unit);
    UnitRoster* roster = gShop;
    UnitRecord* unit = roster->unit(id);
    if (unit->team > 2 || (unit->state_kind & 5))
        return;
    int mode = command->value;
    unsigned short leader_id = unit->members.get(unit->leader);
    OfficerRecord* leader = roster->officer(leader_id);
    unsigned int type = leader->type;
    if (type_ready_172160(type)) {
        set_officer_mode_3e27c(type, mode, 0);
        switch (mode) {
        case 3:
        case 4:
            raise_unit_flags_133cf8(&gBlock_c22bd8->units[static_cast<unsigned int>(id)]);
            refresh_unit_1d3f74(id);
            break;
        case 7:
            unit->ai_mode = 2;
            break;
        }
        return;
    }
    switch (mode) {
    case 3:
    case 4:
        if (!(unit->state_kind & 2)) {
            refresh_unit_1d3f74(id);
            reset_officer_1adac4(leader_id, 300, 1, nullptr);
            update_officer_1999d8(leader, 0, 0);
            int level = leader->level - 1;
            level = level < 0 ? 0 : level;
            leader->level = level > leader->max_level ? leader->max_level : level;
            sync_officer_1adf80(leader_id);
        }
        raise_unit_flags_133cf8(&gBlock_c22bd8->units[static_cast<unsigned int>(id)]);
        break;
    case 5:
        unit->ai_mode = 2;
        break;
    }
}
void load_type_17097c(unsigned int type);                                   // 0x710017097c
void start_type_170530(unsigned int type);                                  // 0x7100170530

// 0x71001c4888
void set_unit_condition_1c4888(const UnitCommand* command) {
    int id = resolve_unit(command->unit);
    UnitRoster* roster = gShop;
    UnitRecord* unit = roster->unit(id);
    if (unit->team > 2 || (unit->state_kind & 5))
        return;
    unsigned short leader_id = unit->members.get(unit->leader);
    OfficerRecord* leader = roster->officer(leader_id);
    int condition = command->value;
    unsigned int type = leader->type;
    int mode;
    switch (condition) {
    case 0: {
        unsigned int health = 1000 - unit->damage * 1000 / 100;
        if (health < 1 || health > 1000)
            health = 1;
        leader->health = health > 1000 ? 1000 : health;
        if (type_ready_172160(type)) {
            load_type_17097c(type);
            start_type_170530(type);
        }
        leader->status &= ~6;
        unit->state_kind &= ~6;
        mode = 8;
        break;
    }
    case 1:
        raise_unit_flags_133cf8(&gBlock_c22bd8->units[static_cast<unsigned int>(id)]);
        mode = 10;
        break;
    default:
        raise_unit_flags_133cf8(&gBlock_c22bd8->units[static_cast<unsigned int>(id)]);
        mode = 9;
        break;
    }
    unit->ai_mode = 0;
    if (type_ready_172160(type)) {
        set_officer_mode_3e27c(type, mode, 0);
        return;
    }
    if (!command->value)
        return;
    if (!(leader->status & 2))
        reset_officer_1adac4(leader_id, 300, 1, nullptr);
    update_officer_1999d8(leader, 0, 0);
    int level = leader->level - 1;
    level = level < 0 ? 0 : level;
    leader->level = level > leader->max_level ? leader->max_level : level;
    sync_officer_1adf80(leader_id);
}
void release_unit_113c40(void* system, int unit, int flag);                 // 0x7100113c40
void release_unit_f2404(void* system, int unit, int flag);                  // 0x71000f2404
void queue_unit_effect_19a858(EffectQueue* queue, const float* position, int a, void* b, int c); // 0x710019a858

// 0x71001b91a0
void dismiss_group_1b91a0(const UnitCommand* command) {
    if (stage_busy_1d740c(gGlobal_c22ca8))
        return;
    unsigned int id = resolve_unit(command->unit);
    if (id > 0xf5)
        return;
    UnitRoster* roster = gShop;
    if (roster->units[id].team > 2)
        return;
    if (!command->value && roster->units[id].state_kind)
        return;
    const float* position = roster->units[id].position;
    if (current_music_6b40()) {
        BattleMusic* music = current_music_6b40();
        if (music_flag_20d9c8(music, 0) && music->level >= 0) {
            BattleMusic* again = current_music_6b40();
            int calm = music_flag_20d9c8(again, 0) ? again->level < 3 : 1;
            if (calm && gShop->units[id].team)
                return;
        }
    }
    release_unit_113c40(gGlobal_c22a60, id, 1);
    release_unit_f2404(gGlobal_c22be8, id, 1);
    queue_unit_effect_19a858(member_18f12c(reinterpret_cast<Container18f12c*>(gShop)), position, 1, nullptr, 5);
}
struct TeamUnitCommand {
    int pad0;
    int unit;                 // +04
    int teams[2];             // +08
    int force;                // +10
};

// 0x71001b9950
void dismiss_team_unit_1b9950(const TeamUnitCommand* command) {
    if (stage_busy_1d740c(gGlobal_c22ca8))
        return;
    unsigned int id = resolve_unit(command->unit);
    if (id > 0xf5)
        return;
    UnitRoster* roster = gShop;
    unsigned int team = roster->units[id].team;
    if (team > 2)
        return;
    unsigned char matches = 0;
    for (int i = 0; i < 2; ++i) {
        if (command->teams[i] != -1)
            matches |= static_cast<unsigned int>(command->teams[i]) == team;
    }
    if (!matches)
        return;
    if (!command->force && roster->units[id].state_kind)
        return;
    const float* position = roster->units[id].position;
    if (current_music_6b40()) {
        BattleMusic* music = current_music_6b40();
        if (music_flag_20d9c8(music, 0) && music->level >= 0) {
            BattleMusic* again = current_music_6b40();
            int calm = music_flag_20d9c8(again, 0) ? again->level < 3 : 1;
            if (calm && gShop->units[id].team)
                return;
        }
    }
    release_unit_113c40(gGlobal_c22a60, id, 1);
    release_unit_f2404(gGlobal_c22be8, id, 1);
    queue_unit_effect_19a858(member_18f12c(reinterpret_cast<Container18f12c*>(gShop)), position, 1, nullptr, 5);
}
int item_field_21139c(int item);                                            // 0x710021139c
int item_field_2113c0(int item);                                            // 0x71002113c0
int text_base_213d38(int value);                                            // 0x7100213d38
int text_id_213a8c(int text);                                               // 0x7100213a8c
const char* text_213b30(int text);                                          // 0x7100213b30
int fill_message_1b7dc4(int a, int value, int kind, int b, int* unit, int* item, int* score, int* field,
                        int* rank, int* text_id, const char** text, int none); // 0x71001b7dc4
void guarded_forward_40b0dc(int text);                                      // 0x710040b0dc
void post_message_1d7444(MessageEntry* entry, int item, int rank, int score, int field, int text_id,
                         const char* text, int value, int result);         // 0x71001d7444
void flush_effects_19a7f4(EffectQueue* queue);                              // 0x710019a7f4

// 0x71001b7b20
void post_unit_message_1b7b20(const UnitCommand* command) {
    int id = command->unit;
    id = resolve_unit(id);
    UnitRecord* unit = gShop->unit(id);
    if (unit->team > 2)
        return;
    int item = unit->item;
    int score = gShop->teams[unit->team].score;
    int field = static_cast<unsigned int>(item) <= 0x44b ? item_field_21139c(item) : -1;
    int rank = unit->rank;
    int requested = command->value;
    StepInfo* info = gGlobal_c22ca8->info;
    int step = info ? info->step * 1000 : 0;
    int value = text_base_213d38(requested) + step;
    int text_id = -1;
    const char* text = "";
    if (static_cast<unsigned int>(value) < 0x47d8 || (gGlobal_c22ca8->info && gGlobal_c22ca8->info->step)) {
        text_id = text_id_213a8c(value);
        text = text_213b30(value);
    }
    int result = fill_message_1b7dc4(1, command->value, item_field_2113c0(unit->item), 1, &id, &item, &score,
                                     &field, &rank, &text_id, &text, -1);
    int shown = text_id;
    if (static_cast<unsigned int>(shown) < 0x1d1a) {
        guarded_forward_40b0dc(shown);
        if (!stage_busy_1d740c(gGlobal_c22ca8)) {
            MessageQueue* messages = &gGlobal_c22ca8->messages;
            post_message_1d7444(&messages->entries[messages->index], item, rank, score, field, shown, text,
                                value, result);
        }
    }
    flush_effects_19a7f4(member_18f12c(reinterpret_cast<Container18f12c*>(gShop)));
}
struct MarkerPosition {
    float x;                  // +00
    float y;                  // +04
    float z;                  // +08
    float w;                  // +0c
};
void focus_camera_113df4(void* system, float x, float z);                   // 0x7100113df4
void focus_map_f25c0(void* system, float x, float z);                       // 0x71000f25c0
void queue_marker_19a914(EffectQueue* queue, const MarkerPosition* position, int a, void* b, int c); // 0x710019a914

// 0x71001c3550
void place_marker_1c3550(const UnitCommand* command) {
    if (stage_busy_1d740c(gGlobal_c22ca8))
        return;
    float x = static_cast<unsigned int>(command->unit * 1000 + 500);
    float z = static_cast<unsigned int>(command->value * 1000 + 500);
    MarkerPosition position = {x, 0.0f, z, 1.0f};
    focus_camera_113df4(gGlobal_c22a60, x, z);
    focus_map_f25c0(gGlobal_c22be8, x, z);
    queue_marker_19a914(member_18f12c(reinterpret_cast<Container18f12c*>(gShop)), &position, 2, nullptr, 5);
}

struct BattleSetup {
    union {
        struct {
            unsigned int flags;   // +00
            unsigned int options; // +04
        };
        unsigned long wide_flags;
    };
};
BattleSetup* get_battle_setup();                                            // 0x710016ef34
void open_camp_16ee2c(unsigned int camp, unsigned int kind);                // 0x710016ee2c
unsigned char stage_mode_1d7364(StepOwner* owner, int mode);               // 0x71001d7364
void raise_flag_168370(unsigned int flag, int a, int b);                    // 0x7100168370

// 0x71001c7224
void activate_camp_1c7224(const UnitCommand* command) {
    unsigned int id = command->value;
    CampRecord* camp = gShop->camp(id);
    if (!camp->active)
        return;
    unsigned int kind = command->unit;
    if (kind >= 3) {
        if (camp->team > 2)
            return;
        open_camp_16ee2c(id, kind);
        if (get_battle_setup()->flags & 0x4000) {
            if (!stage_mode_1d7364(gGlobal_c22ca8, 3))
                return;
        }
        raise_flag_168370(id + 0xec, 0, 1);
        return;
    }
    open_camp_16ee2c(id, kind);
}unsigned int resolve_spot_1b69cc(int id);                                   // 0x71001b69cc
void release_spot_1140c4(void* system, unsigned int spot, int flag);        // 0x71001140c4
void release_spot_f2824(void* system, unsigned int spot, int flag);         // 0x71000f2824
void queue_spot_19a914(EffectQueue* queue, const SpotPosition* position, int a, void* b, int c); // 0x710019a914

// 0x71001c361c
void release_spot_1c361c(const UnitCommand* command) {
    unsigned int id = resolve_spot_1b69cc(command->unit);
    bool busy = stage_busy_1d740c(gGlobal_c22ca8);
    if (id > 0x17 || busy)
        return;
    SpotPosition position = gShop->spots[id].position;
    position.w = 1.0f;
    release_spot_1140c4(gGlobal_c22a60, id, 0);
    release_spot_f2824(gGlobal_c22be8, id, 0);
    queue_spot_19a914(member_18f12c(reinterpret_cast<Container18f12c*>(gShop)), &position, 0, nullptr, 5);
}

// Same as resolve_unit, but 0x78 is always the first player's unit.
static inline int resolve_unit_first(int id) {
    if (id == 0x78) {
        id = gRecord_c21698->players[0]->slot->unit;
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

struct SpotSlot;
struct SpotSlots;
SpotSlots* spot_slots_1898b8(UnitRoster* roster);                           // 0x71001898b8
SpotSlot* spot_slot_19cfac(SpotSlots* slots, unsigned int spot);            // 0x710019cfac
void put_unit_19bde0(SpotSlot* slot, int team, int unit);                   // 0x710019bde0

// 0x71001c2840
void assign_spot_1c2840(const UnitCommand* command) {
    int id = resolve_unit_first(command->value);
    unsigned int spot = resolve_spot_1b69cc(command->unit);
    UnitRoster* roster = gShop;
    unsigned int team = roster->unit(id)->team;
    if (team <= 2)
        put_unit_19bde0(spot_slot_19cfac(spot_slots_1898b8(roster), spot), team, id);
}
struct OrderBoard;
unsigned char item_below_21121c(int item);                                         // 0x710021121c
OrderBoard* order_board_18d5d8(UnitRoster* roster);                         // 0x710018d5d8
void post_order_1a791c(OrderBoard* board, int unit, int value, int kind);   // 0x71001a791c

// 0x71001c65b0
void post_unit_order_1c65b0(const UnitCommand* command) {
    int id = resolve_unit_first(command->unit);
    UnitRecord* unit = gShop->unit(id);
    if (unit->flag_bits & 0x80)
        return;
    if (item_below_21121c(unit->item))
        post_order_1a791c(order_board_18d5d8(gShop), id, command->value, 0xd);
}
struct ItemCatalog;
// Reached through the GOT slot at 0x7100c21df8.
extern ItemCatalog* gCatalog_c21df8;
int item_level_1fb810(int item);                                            // 0x71001fb810
int item_for_level_1fb214(ItemCatalog* catalog, int level);                 // 0x71001fb214

// 0x71001c57b0
void set_item_field_1c57b0(const UnitCommand* command) {
    int id = resolve_unit_first(command->unit);
    UnitRecord* unit = gShop->unit(id);
    if (unit->team > 2)
        return;
    int value = command->value;
    if (static_cast<unsigned int>(value) > 999)
        return;
    if (value == 999) {
        int item = unit->item;
        if (item_level_1fb810(item) >= 0 && item_level_1fb810(item) <= 99) {
            int level = item_level_1fb810(item);
            item = item_for_level_1fb214(gCatalog_c21df8, level);
        }
        value = item_field_21139c(item);
    }
    unit->item_field = value;
}

static inline bool text_ready(int kind) {
    StepInfo* info = gGlobal_c22ca8->info;
    int step = info ? info->step * 1000 : 0;
    int value = text_base_213d38(kind) + step;
    return static_cast<unsigned int>(value) < 0x47d8 && static_cast<unsigned int>(text_id_213a8c(value)) < 0x1d1a;
}

// 0x71001c5c34
void set_spot_limits_1c5c34(const UnitCommand* command) {
    unsigned int id = resolve_spot_1b69cc(command->unit);
    SpotRecord* spot = gShop->spot(id);
    text_base_213d38(1);
    if (text_ready(1)) {
        unsigned int limit = command->value;
        spot->limits[0] = limit > 0x100 ? 0x100 : limit;
    }
    if (text_ready(2)) {
        unsigned int limit = command->extra[0];
        spot->limits[1] = limit > 0x100 ? 0x100 : limit;
    }
}
void move_unit_16af1c(int unit, const MarkerPosition* position, int flag, float delay); // 0x710016af1c
void move_unit_16ab4c(int unit, const MarkerPosition* position, int flag, float delay); // 0x710016ab4c
void move_unit_16b1f8(int unit, const MarkerPosition* position, int flag, float delay); // 0x710016b1f8

// 0x71001c019c
void move_unit_1c019c(const UnitCommand* command) {
    int id = resolve_unit_first(command->unit);
    MarkerPosition position;
    int cell_x = command->value, cell_z = command->extra[0];
    position.x = static_cast<unsigned int>(cell_x * 1000 + 500);
    position.y = 0.0f;
    position.z = static_cast<unsigned int>(cell_z * 1000 + 500);
    position.w = 1.0f;
    UnitRecord* unit = gShop->unit(id);
    if (unit->state_kind & 4)
        move_unit_16af1c(id, &position, 1, 0.0f);
    if (unit->state_kind & 1)
        move_unit_16ab4c(id, &position, 1, 0.0f);
    else
        move_unit_16b1f8(id, &position, 0x80, 0.0f);
}
struct PlayerView {
    unsigned char pad[0x9e0];
    int mode;                 // +9e0
};
// The GOT slot at 0x7100c22ab0 points at this array.
extern PlayerView* gViews_c22ab0[2];

struct FocusInfo {
    unsigned char pad[0x10];
    unsigned char done;       // +10
    unsigned char ready;      // +11
    unsigned char kind;       // +12
    unsigned char pad13;
    int item;                 // +14
};
FocusInfo* focus_info_18f0e0(UnitRoster* roster);                           // 0x710018f0e0
void apply_focus_191e3c(FocusInfo* focus);                                  // 0x7100191e3c

// 0x71001c7ebc
void set_focus_1c7ebc(const UnitCommand* command) {
    unsigned int id = resolve_unit_first(command->value);
    int item;
    if (id > 0xf5)
        item = -1;
    else
        item = gShop->units[id].item;
    int mode;
    switch (command->unit) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        mode = 0;
        break;
    case 6:
    case 8:
    case 9:
    case 10:
        mode = 1;
        break;
    case 7:
        mode = 2;
        break;
    default:
        mode = 3;
        break;
    }
    gViews_c22ab0[0]->mode = mode;
    if (gRecord_c21698->player_count >= 2)
        gViews_c22ab0[1]->mode = mode;
    focus_info_18f0e0(gShop)->kind = command->unit;
    focus_info_18f0e0(gShop)->item = item;
    apply_focus_191e3c(focus_info_18f0e0(gShop));
}
void queue_spot_19a858(EffectQueue* queue, const SpotPosition* position, int a, void* b, int c); // 0x710019a858

// 0x71001b9c88
void release_spot_1b9c88(const UnitCommand* command) {
    unsigned int id = resolve_spot_1b69cc(command->unit);
    if (stage_busy_1d740c(gGlobal_c22ca8))
        return;
    SpotPosition position = gShop->spot(id)->position;
    position.w = 1.0f;
    release_unit_113c40(gGlobal_c22a60, id, 0);
    release_unit_f2404(gGlobal_c22be8, id, 0);
    queue_spot_19a858(member_18f12c(reinterpret_cast<Container18f12c*>(gShop)), &position, 0, nullptr, 5);
}
void focus_camera_113a60(void* system, float x, float z);                   // 0x7100113a60
void focus_map_f2234(void* system, float x, float z);                       // 0x71000f2234
void queue_marker_19a858(EffectQueue* queue, const MarkerPosition* position, int a, void* b, int c); // 0x710019a858

// 0x71001b9ba8
void place_marker_1b9ba8(const UnitCommand* command) {
    if (stage_busy_1d740c(gGlobal_c22ca8))
        return;
    float x = static_cast<unsigned int>(command->unit * 1000 + 500);
    float z = static_cast<unsigned int>(command->value * 1000 + 500);
    MarkerPosition position = {x, 0.0f, z, 1.0f};
    focus_camera_113a60(gGlobal_c22a60, x, z);
    focus_map_f2234(gGlobal_c22be8, x, z);
    queue_marker_19a858(member_18f12c(reinterpret_cast<Container18f12c*>(gShop)), &position, 2, nullptr, 5);
}
void queue_point_19a858(EffectQueue* queue, const PointPosition* position, int a, void* b, int c); // 0x710019a858

// 0x71001b9d58
void show_point_1b9d58(const UnitCommand* command) {
    PointRecord* point = gShop->point(command->unit);
    if (stage_busy_1d740c(gGlobal_c22ca8))
        return;
    if (!point->active)
        return;
    PointPosition* position = &point->position;
    focus_camera_113a60(gGlobal_c22a60, position->x, position->z);
    focus_map_f2234(gGlobal_c22be8, position->x, position->z);
    queue_point_19a858(member_18f12c(reinterpret_cast<Container18f12c*>(gShop)), position, 2, nullptr, 5);
}

// 0x71001b981c
void dismiss_spawned_1b981c(const UnitCommand* command) {
    if (stage_busy_1d740c(gGlobal_c22ca8))
        return;
    SpawnedUnit* spawned = find_spawned_1b93b8(command->unit, command->extra[0], command->value);
    if (!spawned)
        return;
    unsigned int officer = spawned->officer;
    const float* position = spawned->position;
    if (current_music_6b40()) {
        BattleMusic* music = current_music_6b40();
        if (music_flag_20d9c8(music, 0) && music->level >= 0) {
            BattleMusic* again = current_music_6b40();
            int calm = music_flag_20d9c8(again, 0) ? again->level < 3 : 1;
            if (officer <= 0xf5 && calm && gShop->units[officer].team)
                return;
        }
    }
    release_unit_113c40(gGlobal_c22a60, officer, 1);
    release_unit_f2404(gGlobal_c22be8, officer, 1);
    queue_unit_effect_19a858(member_18f12c(reinterpret_cast<Container18f12c*>(gShop)), position, 1, nullptr, 5);
}
struct MusicPlayer;
// Reached through the GOT slot at 0x7100c22d90.
extern MusicPlayer* gMusic_c22d90;
unsigned int current_track_3f50cc(MusicPlayer* player);                     // 0x71003f50cc
void set_track_3f50d4(MusicPlayer* player, int track);                      // 0x71003f50d4
void prepare_track_3fa4a8(int track);                                       // 0x71003fa4a8
void play_bgm_3f9b34(int track, int a, int b, void* c, float fade);         // 0x71003f9b34
void record_track_1a7650(OrderBoard* board, int track);                     // 0x71001a7650

struct MusicCommand {
    int pad0;
    int track;                // +04
    int pad8;
    int start;                // +0c
    int length;               // +10
};

// 0x71001b9e14
void play_music_1b9e14(MusicCommand* command) {
    if (stage_busy_1d740c(gGlobal_c22ca8))
        return;
    if (gMusic_c22d90) {
        unsigned int current = current_track_3f50cc(gMusic_c22d90);
        if (current <= 0x31f)
            command->track = current;
    }
    if (get_battle_setup()->flags & 0x4000) {
        record_track_1a7650(order_board_18d5d8(gShop), command->track);
        return;
    }
    int track = command->track;
    switch (track) {
    case 0x3a:
    case 0x3b:
    case 0x61:
    case 0x62:
    case 0x63:
        prepare_track_3fa4a8(track);
        break;
    }
    play_bgm_3f9b34(track, 1, 0, nullptr, 0.668f);
    if (gMusic_c22d90)
        set_track_3f50d4(gMusic_c22d90, track);
    if (gGlobal_c22ca8->recording)
        record_track_1a7650(order_board_18d5d8(gShop), track);
}
void set_bit_1ccdc0(StepBits* bits, int index, unsigned char value);        // 0x71001ccdc0
unsigned char focus_open_190f24(FocusInfo* focus);                          // 0x7100190f24
unsigned char focus_busy_190f04(FocusInfo* focus);                          // 0x7100190f04
void start_focus_1d3528();                                                  // 0x71001d3528

static inline int resolve_flag(int id) {
    StepInfo* info = gGlobal_c22ca8->info;
    if (info && info->step && (id & ~0xf) == 0x10)
        id += info->step * 4 - 4;
    return id;
}

// 0x71001ba1b4
void set_flag_1ba1b4(const UnitCommand* command) {
    set_bit_1ccdc0(&gGlobal_c22ca8->bits, resolve_flag(command->unit), command->value);
    if (!(get_battle_setup()->flags & 0x400))
        return;
    if (resolve_flag(command->unit) != 2)
        return;
    if (!focus_info_18f0e0(gShop)->ready || focus_info_18f0e0(gShop)->done)
        return;
    if (focus_open_190f24(focus_info_18f0e0(gShop)) && !focus_busy_190f04(focus_info_18f0e0(gShop)))
        start_focus_1d3528();
}

struct BgmParams {
    BgmParams()
        : volume(1.0f), flags(0), offset(0), start(0), length(200), gains{1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
          fade(0.668f), balance(0.5f) {}

    float volume;             // +00
    int flags;                // +04
    int offset;               // +08
    int start;                // +0c
    int length;               // +10
    float gains[6];           // +14
    float fade;               // +2c
    float balance;            // +30
};
void play_bgm_params_3f9b34(int track, int a, int b, BgmParams* params, float fade); // 0x71003f9b34

// 0x71001c1ff0
void play_music_part_1c1ff0(MusicCommand* command) {
    if (stage_busy_1d740c(gGlobal_c22ca8))
        return;
    BgmParams params;
    if (gMusic_c22d90) {
        unsigned int current = current_track_3f50cc(gMusic_c22d90);
        if (current <= 0x31f)
            command->track = current;
    }
    params.volume = 0.0f;
    params.start = command->start;
    params.length = command->length;
    params.fade = 0.668f;
    int track = command->track;
    play_bgm_params_3f9b34(track, 1, 0, &params, 0.668f);
    if (gMusic_c22d90)
        set_track_3f50d4(gMusic_c22d90, track);
    if (gGlobal_c22ca8->recording)
        record_track_1a7650(order_board_18d5d8(gShop), track);
}
// 0x71001b6968
unsigned char link_value_1b6968(unsigned int from, unsigned int to, bool resolved) {
    LinkCell* cell = gShop->link(from, to);
    unsigned char value = cell->value;
    if (resolved && cell->state == 5)
        value = cell->kind;
    return value;
}
void activate_point_1a9b5c(unsigned int point, int value);                  // 0x71001a9b5c

// 0x71001c0c34
void activate_spot_points_1c0c34(const UnitCommand* command) {
    unsigned int id = resolve_spot_1b69cc(command->unit);
    SpotRecord* spot = gShop->spot(id);
    for (int i = 0; i < 4; ++i) {
        unsigned int point = spot->points[i];
        if (point < 0x40)
            activate_point_1a9b5c(point, command->value);
    }
}
void reset_focus_191928(FocusInfo* focus);                                  // 0x7100191928
void set_setup_flags_16f618(BattleSetup* setup, unsigned long flags);       // 0x710016f618
void set_setup_mode_16f6c0(BattleSetup* setup, int mode);                   // 0x710016f6c0

// 0x71001ba2f0
void set_battle_mode_1ba2f0(const UnitCommand* command) {
    if ((get_battle_setup()->flags & 0x400) || (get_battle_setup()->options & 2)) {
        if (command->unit == 2) {
            reset_focus_191928(focus_info_18f0e0(gShop));
            gGlobal_c22ca8->fade_mode = 1;
            gGlobal_c22ca8->fade_rate = 1.0f;
            return;
        }
    }
    set_setup_flags_16f618(get_battle_setup(), 8);
    set_setup_mode_16f6c0(get_battle_setup(), command->unit);
}
unsigned char music_mode_20d984(BattleMusic* music, int mode);              // 0x710020d984
void set_time_limit_16f6b0(BattleSetup* setup, int seconds);                // 0x710016f6b0

// 0x71001bd1c0
void set_time_limit_1bd1c0(const UnitCommand* command) {
    int minutes = command->unit;
    if (current_music_6b40()) {
        BattleMusic* music = current_music_6b40();
        if (music_mode_20d984(music, 0x15) || music->level == 6) {
            if (music_mode_20d984(current_music_6b40(), 9))
                minutes = 20;
            if (music_mode_20d984(current_music_6b40(), 10))
                minutes = 20;
        }
    }
    set_time_limit_16f6b0(get_battle_setup(), minutes ? minutes * 3600 : -1);
}
struct UnitSlot;
UnitSlot* unit_slot_19bcfc(SpotSlots* slots, unsigned int unit);            // 0x710019bcfc
void set_slot_range_19ba90(UnitSlot* slot, int near, int far);              // 0x710019ba90
void set_slot_angle_19ba98(UnitSlot* slot, int angle);                      // 0x710019ba98

struct RangeCommand {
    int pad0;
    int unit;                 // +04
    int near;                 // +08
    int far;                  // +0c
    int angle;                // +10
};

// 0x71001ba5c8
void set_unit_range_1ba5c8(const RangeCommand* command) {
    int id = resolve_unit_first(command->unit);
    UnitSlot* slot = unit_slot_19bcfc(spot_slots_1898b8(gShop), id);
    set_slot_range_19ba90(slot, command->near * 100, command->far * 100);
    set_slot_angle_19ba98(slot, command->angle * 45);
}

// 0x71001ba8ac
void stop_unit_1ba8ac(const UnitCommand* command) {
    int id = resolve_unit_first(command->unit);
    UnitRecord* unit = gShop->unit(id);
    if (unit->team > 2)
        return;
    if (!(unit->state_kind & 5) && command->value)
        return;
    if (unit->state_kind & 4)
        move_unit_16af1c(id, nullptr, 1, 0.0f);
    else
        move_unit_16ab4c(id, nullptr, 1, 0.0f);
}

// 0x71001bc9c4
void set_unit_order_1bc9c4(const UnitCommand* command) {
    int id = resolve_unit_first(command->unit);
    UnitRecord* unit = gShop->unit(id);
    if (unit->team > 2 || (unit->state_kind & 2) || (unit->flag_bits & 0x80))
        return;
    unit->order = 0;
    switch (command->value) {
    case 1:
        unit->order = 1;
        break;
    case 2:
        unit->order = 2;
        break;
    case 3:
        unit->order = 4;
        break;
    }
}
void put_count_1ccd38(StepBits* bits, unsigned int index, int value);       // 0x71001ccd38

static inline int resolve_count(int id) {
    StepInfo* info = gGlobal_c22ca8->info;
    if (info && info->step && (id & ~7) == 8)
        id += info->step * 2 - 2;
    return id;
}

// 0x71001c24f8
void store_slot_total_1c24f8(const UnitCommand* command) {
    int total = 0;
    switch (command->value) {
    case 1: {
        RosterTable* table = gRecord_c21698;
        for (unsigned int i = 0; i < table->slot_count; ++i)
            total += table->slot(RosterTable::slot_index(i))->defeated;
        break;
    }
    case 0: {
        RosterTable* table = gRecord_c21698;
        for (unsigned int i = 0; i < table->slot_count; ++i)
            total += table->slot(RosterTable::slot_index(i))->captured;
        break;
    }
    }
    put_count_1ccd38(&gGlobal_c22ca8->bits, resolve_count(command->unit), total);
}
struct AreaCommand {
    int pad0;
    int kind;                 // +04
    int from_x;               // +08
    int from_z;               // +0c
    int to_x;                 // +10
    int to_z;                 // +14
};
void show_area_114f88(void* system, int kind, float x0, float z0, float x1, float z1); // 0x7100114f88
void show_area_f2e8c(void* system, int kind, float x0, float z0, float x1, float z1);  // 0x71000f2e8c
void hide_area_113a54(void* system);                                        // 0x7100113a54
void hide_area_f2220(void* system);                                         // 0x71000f2220

// 0x71001ba090
void show_area_1ba090(const AreaCommand* command) {
    MarkerPosition from;
    int from_x = command->from_x, from_z = command->from_z;
    from.x = static_cast<unsigned int>(from_x * 1000 + 500);
    from.y = 0.0f;
    from.z = static_cast<unsigned int>(from_z * 1000 + 500);
    from.w = 1.0f;
    MarkerPosition to;
    int to_x = command->to_x, to_z = command->to_z;
    to.x = static_cast<unsigned int>(to_x * 1000 + 500);
    to.y = 0.0f;
    to.z = static_cast<unsigned int>(to_z * 1000 + 500);
    to.w = 1.0f;
    if (static_cast<unsigned int>(command->kind) <= 1) {
        queue_marker_19a914(member_18f12c(reinterpret_cast<Container18f12c*>(gShop)), &from, 8, &to, command->kind + 3);
        show_area_114f88(gGlobal_c22a60, command->kind, from.x, from.z, to.x, to.z);
        show_area_f2e8c(gGlobal_c22be8, command->kind, from.x, from.z, to.x, to.z);
    } else {
        hide_area_113a54(gGlobal_c22a60);
        hide_area_f2220(gGlobal_c22be8);
    }
}

// 0x71001bcac4
void load_leader_type_1bcac4(const UnitCommand* command) {
    int id = resolve_unit_first(command->unit);
    UnitRoster* roster = gShop;
    UnitRecord* unit = roster->unit(id);
    if (unit->team > 2 || (unit->flag_bits & 0x80))
        return;
    type_loaded_172174(roster->officer(unit->members.get(unit->leader))->type);
}

// 0x71001ba9a0
void move_unit_to_1ba9a0(const UnitCommand* command) {
    int id = resolve_unit_first(command->unit);
    MarkerPosition position;
    int cell_x = command->value, cell_z = command->extra[0];
    position.x = static_cast<unsigned int>(cell_x * 1000 + 500);
    position.y = 0.0f;
    position.z = static_cast<unsigned int>(cell_z * 1000 + 500);
    position.w = 1.0f;
    UnitRecord* unit = gShop->unit(id);
    if (unit->team > 2)
        return;
    if (!(unit->state_kind & 5) && command->extra[1])
        return;
    if (unit->state_kind & 4)
        move_unit_16af1c(id, &position, 1, 0.0f);
    else
        move_unit_16ab4c(id, &position, 1, 0.0f);
}

// 0x71001baca0
void walk_unit_to_1baca0(const UnitCommand* command) {
    int id = resolve_unit_first(command->unit);
    MarkerPosition position;
    int cell_x = command->value, cell_z = command->extra[0];
    position.x = static_cast<unsigned int>(cell_x * 1000 + 500);
    position.y = 0.0f;
    position.z = static_cast<unsigned int>(cell_z * 1000 + 500);
    position.w = 1.0f;
    UnitRecord* unit = gShop->unit(id);
    if (unit->team > 2)
        return;
    if (!(unit->state_kind & 5) && command->extra[1])
        return;
    if (unit->state_kind & 4)
        move_unit_16af1c(id, &position, 0, unit->speed);
    else
        move_unit_16ab4c(id, &position, 0, unit->speed);
}

static inline void set_list_order(UnitRoster* roster, MemberList* list, const UnitCommand* command) {
    for (int i = 0; i < list->count; ++i) {
        UnitRecord* unit = roster->unit(list->data[i]);
        unit->order = 0;
        if (command->extra[0])
            unit->order = 2;
    }
}

// 0x71001c37f4
void set_team_flag_1c37f4(const UnitCommand* command) {
    UnitRoster* roster = gShop;
    RosterTeam* team = roster->team(command->unit);
    switch (command->value) {
    case 0:
        if (command->extra[0])
            team->guard = 1;
        else
            team->guard = 0;
        break;
    case 1:
        if (command->extra[0])
            team->hold = 1;
        else
            team->hold = 0;
        break;
    case 2:
        if (command->extra[0])
            team->rally = 1;
        else
            team->rally = 0;
        set_list_order(roster, &team->commanders, command);
        set_list_order(roster, &team->guards, command);
        break;
    }
}

struct OrderCommand {
    int pad0;
    int kind;                 // +04
    int value;                // +08
    int target;               // +0c
    int mode;                 // +10
};

// 0x71001b9f28
void post_orders_1b9f28(const OrderCommand* command) {
    OrderBoard* board = order_board_18d5d8(gShop);
    int kind = command->kind;
    switch (command->mode) {
    case 0:
        for (int i = 0; i < 0x76; ++i)
            post_order_1a791c(board, i, command->value, kind);
        break;
    case 1:
        post_order_1a791c(board, resolve_unit_first(command->target), command->value, kind);
        break;
    case 2:
        for (int i = 0; i < 0x76; ++i) {
            if (gShop->units[i].item == command->target)
                post_order_1a791c(board, i, command->value, kind);
        }
        break;
    }
}
unsigned char slot_locked_1a3240(RosterTable* table, int slot);             // 0x71001a3240

struct SlotFlagsCommand {
    int pad0;
    int values[4];            // +04
};

// 0x71001c8524
void set_slot_flags_1c8524(const SlotFlagsCommand* command) {
    int values[4] = {command->values[0], command->values[1], command->values[2], command->values[3]};
    bool enabled[4] = {values[0] != 0, values[1] != 0, values[2] != 0, values[3] != 0};
    for (int i = 0; i < 4; ++i) {
        RosterTable* table = gRecord_c21698;
        unsigned long flags = get_battle_setup()->wide_flags;
        if (slot_locked_1a3240(table, i))
            continue;
        RosterSlot* slot = table->slots[i];
        slot->active = enabled[i];
        if ((flags & 0x4000) && values[i] && !slot->started)
            slot->started = enabled[i];
    }
}

// 0x71001c5a9c
void set_unit_limits_1c5a9c(const UnitCommand* command) {
    int id = resolve_unit_first(command->unit);
    UnitRecord* unit = gShop->unit(id);
    text_base_213d38(command->value);
    if (text_ready(command->value)) {
        unsigned int limit = command->value;
        unit->limits[0] = limit > 0x100 ? 0x100 : limit;
    }
    if (text_ready(command->extra[0])) {
        unsigned int limit = command->extra[0];
        unit->limits[1] = limit > 0x100 ? 0x100 : limit;
    }
}
MemberList* team_group_197ac4(RosterTeam* team, int group);                 // 0x7100197ac4
int item_field_211554(int item);                                            // 0x7100211554

struct GroupCommand {
    int pad0;
    int team;                 // +04
    int value;                // +08
    int filter;               // +0c
};

// 0x71001c3d38
void set_group_value_1c3d38(const GroupCommand* command) {
    UnitRoster* roster = gShop;
    RosterTeam* team = roster->team(command->team);
    for (int group = 0; group < 8; ++group) {
        MemberList* list = team_group_197ac4(team, group);
        unsigned int count = list->count;
        for (unsigned int i = 0; i < count; ++i) {
            unsigned short id = list->get(i);
            UnitRecord* unit = roster->unit(id);
            if (unit->team > 2 || unit->state_kind || (unit->flag_bits & 0x80))
                continue;
            UnitRecord* current = gShop->unit(id);
            switch (command->filter) {
            case 1: {
                OfficerRecord* leader = gShop->officer(current->members.get(current->leader));
                if (static_cast<unsigned int>(item_field_211554(leader->item) - 2) >= 4)
                    continue;
                break;
            }
            case 2:
                if (static_cast<unsigned int>(id - 0x84) > 0x17)
                    continue;
                break;
            }
            unit->group_value = command->value;
        }
    }
}
void open_point_1a99c8(unsigned int point, bool flag);                      // 0x71001a99c8
void close_point_1a9ac4(unsigned int point, bool flag);                     // 0x71001a9ac4

// 0x71001c08fc
void open_spot_points_1c08fc(const UnitCommand* command) {
    unsigned int id = resolve_spot_1b69cc(command->unit);
    UnitRoster* roster = gShop;
    SpotRecord* spot = roster->spot(id);
    for (int i = 0; i < 4; ++i) {
        unsigned int point = spot->points[i];
        if (point < 0x40 && roster->points[point].active && roster->points[point].enabled)
            open_point_1a99c8(point, get_battle_setup()->flags & 0x4000);
    }
}

// 0x71001c0a98
void close_spot_points_1c0a98(const UnitCommand* command) {
    unsigned int id = resolve_spot_1b69cc(command->unit);
    UnitRoster* roster = gShop;
    SpotRecord* spot = roster->spot(id);
    for (int i = 0; i < 4; ++i) {
        unsigned int point = spot->points[i];
        if (point < 0x40 && roster->points[point].active && roster->points[point].enabled)
            close_point_1a9ac4(point, get_battle_setup()->flags & 0x4000);
    }
}
void refresh_type_1704e0(unsigned int type);                                // 0x71001704e0

// 0x71001c61f0
void set_unit_damage_1c61f0(const UnitCommand* command) {
    int id = resolve_unit_first(command->unit);
    UnitRoster* roster = gShop;
    UnitRecord* unit = roster->unit(id);
    if (unit->team > 2)
        return;
    unsigned int percent = command->value;
    unsigned int damage = 100 - (percent > 100 ? 100 : percent);
    unit->damage = damage > 100 ? 100 : damage;
    OfficerRecord* leader = roster->officer(unit->members.get(unit->leader));
    unsigned int type = leader->type;
    if (type_ready_172160(type)) {
        refresh_type_1704e0(type);
        start_type_170530(type);
        return;
    }
    unsigned int health = 1000 - damage * 1000 / 100;
    if (health < 1 || health > 1000)
        health = 1;
    unsigned int current = leader->health > health ? health : leader->health;
    leader->health = current > 1000 ? 1000 : current;
}

// Same as resolve_unit_first, with the step read before the family test.
static inline int resolve_unit_family(int id) {
    if (id == 0x78) {
        id = gRecord_c21698->players[0]->slot->unit;
    } else {
        int alias = id - 0x79;
        if (static_cast<unsigned int>(alias) <= 3)
            id = gRecord_c21698->slots[alias]->unit;
    }
    StepInfo* info = gGlobal_c22ca8->info;
    int step = info ? info->step : 0;
    if (step && (id & ~0xf) == 0x50)
        id += step * 5 - 5;
    return id;
}

struct TurnCommand {
    int pad0;
    int unit;                 // +04
    unsigned int x;           // +08
    unsigned int z;           // +0c
    int heading;              // +10
};

static inline float wrap_angle(float angle) {
    if (angle > 3.14159265f)
        return angle - 6.28318531f;
    return angle <= -3.14159265f ? angle + 6.28318531f : angle;
}

// 0x71001c02e4
void turn_unit_1c02e4(const TurnCommand* command) {
    int id = resolve_unit_family(command->unit);
    float x = command->x * 100.0f;
    float z = command->z * 100.0f;
    MarkerPosition position;
    position.w = 1.0f;
    position.z = z;
    position.x = x;
    position.y = 0.0f;
    float angle = wrap_angle(static_cast<float>(static_cast<unsigned int>(command->heading * 45)) * 0.017453292f);
    UnitRecord* unit = gShop->unit(id);
    if (unit->state_kind & 4)
        move_unit_16af1c(id, &position, 1, angle);
    if (unit->state_kind & 1)
        move_unit_16ab4c(id, &position, 1, angle);
    else
        move_unit_16b1f8(id, &position, 0x80, angle);
}
float type_health_17097c(unsigned int type);                                // 0x710017097c
void set_type_health_170530(unsigned int type, float health);               // 0x7100170530

// 0x71001c5d60
void set_leader_health_1c5d60(const UnitCommand* command) {
    int id = resolve_unit_first(command->unit);
    UnitRoster* roster = gShop;
    UnitRecord* unit = roster->unit(id);
    if (unit->team > 2 || unit->state_kind)
        return;
    unsigned int percent = command->value;
    percent = percent == 0 ? 1 : (percent > 100 ? 100 : percent);
    OfficerRecord* leader = roster->officer(unit->members.get(unit->leader));
    unsigned int type = leader->type;
    if (type_ready_172160(type)) {
        float health = type_health_17097c(type);
        if (percent != 100)
            health = percent * health / 100.0f;
        set_type_health_170530(type, health);
        return;
    }
    unsigned int limit = 1000 - unit->damage * 1000 / 100;
    if (limit < 1 || limit > 1000)
        limit = 1;
    unsigned int target = percent * 1000 / 100;
    unsigned int health = target > limit ? limit : target;
    leader->health = health > 1000 ? 1000 : health;
}
struct ItemRecord {
    unsigned char pad[4];
    short field;              // +04
    unsigned char pad6[0x4a];
};

struct ItemTable {
    ItemRecord items[0x44c];

    ItemRecord* item(int id) { return static_cast<unsigned int>(id) < 0x44c ? &items[id] : nullptr; }
};
// Reached through the GOT slot at 0x7100c216a0.
extern ItemTable* gItems_c216a0;
int field_rank_1f4b1c(int field);                                           // 0x71001f4b1c
void swap_field_rank_1f4b40(int field, int rank);                           // 0x71001f4b40
void set_item_field_194778(UnitRecord* unit, int field);                    // 0x7100194778

// 0x71001c58d4
void assign_item_field_1c58d4(const UnitCommand* command) {
    int id = resolve_unit_first(command->unit);
    UnitRecord* unit = gShop->unit(id);
    if (unit->team > 2)
        return;
    unsigned int value = command->value;
    if (value > 999)
        return;
    int item = unit->item;
    if (unit->category == 1)
        return;
    if (value == 999) {
        if (item_level_1fb810(item) >= 0 && item_level_1fb810(item) <= 99) {
            int level = item_level_1fb810(item);
            value = item_field_21139c(item_for_level_1fb214(gCatalog_c21df8, level));
        } else {
            value = item_field_21139c(item);
        }
    }
    if (field_rank_1f4b1c(value) < 0)
        swap_field_rank_1f4b40(value, field_rank_1f4b1c(gItems_c216a0->item(item)->field));
    if (value <= 999 && value + 0x8000 < 0x10000)
        gItems_c216a0->item(item)->field = value;
    set_item_field_194778(unit, value);
}

struct GroupStepCommand {
    int pad0;
    int team;                 // +04
    int mode;                 // +08
    int delta;                // +0c
    int filter;               // +10
};

// 0x71001c3ec0
void step_group_value_1c3ec0(const GroupStepCommand* command) {
    UnitRoster* roster = gShop;
    RosterTeam* team = roster->team(command->team);
    for (int group = 0; group < 8; ++group) {
        MemberList* list = team_group_197ac4(team, group);
        unsigned int count = list->count;
        for (unsigned int i = 0; i < count; ++i) {
            unsigned short id = list->get(i);
            UnitRecord* unit = roster->unit(id);
            if (unit->team > 2 || unit->state_kind || (unit->flag_bits & 0x80))
                continue;
            UnitRecord* current = gShop->unit(id);
            switch (command->filter) {
            case 1: {
                OfficerRecord* leader = gShop->officer(current->members.get(current->leader));
                if (static_cast<unsigned int>(item_field_211554(leader->item) - 2) >= 4)
                    continue;
                break;
            }
            case 2:
                if (static_cast<unsigned int>(id - 0x84) > 0x17)
                    continue;
                break;
            }
            int old = unit->group_value;
            int value = old + command->delta;
            int wide = value < 0 ? 0 : value;
            wide = wide > 4 ? 4 : wide;
            int narrow = value < 1 ? 1 : value;
            narrow = narrow > 3 ? 3 : narrow;
            int next = command->mode != 1 ? wide : narrow;
            if (command->delta >= 1 ? next >= old : next <= old)
                unit->group_value = next;
        }
    }
}
