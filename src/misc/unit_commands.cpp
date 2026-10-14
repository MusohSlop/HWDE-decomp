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
    unsigned char pad28[0x28];
    Gauge19d2 gauge;          // +50
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

    RosterPlayer* player(int index) { return static_cast<unsigned int>(index) < 2 ? players[index] : players[0]; }
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

struct StepOwner {
    unsigned char pad[0x139338];
    MessageQueue messages;    // +139338
    unsigned char pad13958c[0x3bc];
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
    unsigned char pad48[0x10];
    int item;                 // +58
    int leader;               // +5c
    unsigned char pad60[4];
    int rank;                 // +64
    unsigned char pad68[0x40];
    int values[3];            // +a8
    unsigned char padb4[0x40];
    unsigned int damage;      // +f4
    unsigned char padf8[0x18];
    int ai_mode;              // +110
    unsigned char pad114[4];
    unsigned int flag_bits : 25; // +118
    unsigned int stance : 2;
    unsigned int high_bits : 5;
    unsigned int : 0;
    unsigned int state_kind : 3; // +11c
    unsigned int state_low : 13;
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
    unsigned char pad3c[8];
    unsigned int type;        // +44
    unsigned int health;      // +48
    unsigned char pad4c[0x20];
    unsigned char status;     // +6c
    unsigned char pad6d[0x663];
};

struct OfficerType {
    unsigned char pad[0x30];
    unsigned char flags;      // +30
    unsigned char pad31[0xb];
};

struct RosterTeam {
    unsigned char pad[4];
    int score;                // +04
    unsigned char pad8[0x330];
};

struct UnitRoster {
    unsigned char pad[0x278];
    RosterTeam teams[3];      // +278
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