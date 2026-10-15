// Functions that inline the unit-state test (fourth session's unit-state batch; the test and the unit types are in
// include/misc/s4_unit_state.h). Most look a unit up by its 16-bit id and pass its actor on to a command when the
// unit's state allows it. Functions are named after their address; names are descriptive placeholders.

#include "misc/s4_unit_state.h"

void unit_command_7f310(UnitActor* actor, int arg);                         // 0x710007f310
void unit_command_7f584(UnitActor* actor, int arg);                         // 0x710007f584
void unit_command_80bf8(UnitActor* actor, int arg);                         // 0x7100080bf8
int unit_command_82244(UnitActor* actor, int arg);                          // 0x7100082244

class UnitCommands : public UnitTable {
public:
    void command_2169c(short id, int arg);
    void command_22d58(short id, int arg);
    void command_22e80(short id, int arg);
    void command_234fc(short id, unsigned char on);
    void command_23260(int side);
};

// 0x710002169c
void UnitCommands::command_2169c(short id, int arg) {
    Unit* u = unit(id);
    IF_UNIT_STATE_ACTIVE(u->state()->id, unit_command_7f310(u->actor(), arg));
}

// 0x7100022d58
void UnitCommands::command_22d58(short id, int arg) {
    Unit* u = unit(id);
    IF_UNIT_STATE_ACTIVE(u->state()->id, {
        UnitActor* a = u->actor();
        if (a) unit_command_80bf8(a, arg);
    });
}

// 0x7100022e80
void UnitCommands::command_22e80(short id, int arg) {
    Unit* u = unit(id);
    if (!u) return;
    IF_UNIT_STATE_ACTIVE(u->state()->id, unit_command_7f584(u->actor(), arg));
}

// A unit id passed by value (in a 64-bit register).
struct UnitId {
    short value;
};

// 0x710003e29c
int unit_command_3e29c(UnitId id, int arg) {
    Unit* u = gUnitTable_c21690->units[id.value];
    IF_UNIT_STATE_ACTIVE(u->state()->id, {
        UnitActor* a = u->actor();
        if (a) return unit_command_82244(a, arg);
    });
    return 0;
}

int unit_command_85908(UnitActor* actor);                                   // 0x7100085908
int unit_command_9906c(UnitActor* actor, void* arg);                        // 0x710009906c
int unit_command_995f4(UnitActor* actor, int arg);                          // 0x71000995f4


// 0x710000b548
int unit_command_b548(short id) {
    Unit* u = find_unit(id);
    if (!u) return 0;
    IF_UNIT_STATE_ACTIVE(u->state()->id, {
        UnitActor* a = u->actor();
        if (a) return unit_command_85908(a);
    });
    return 0;
}

// 0x710000b488 (an int result: a bool's phi would let the switch become a lookup bitmap)
int unit_flag35_b488(short id) {
    Unit* u = find_unit(id);
    if (!u) return 0;
    IF_UNIT_STATE_ACTIVE(u->state()->id, {
        UnitActor* a = u->actor();
        if (!a) return 0;
        return (a->flags50 >> 35) & 1;
    });
    return 0;
}

// 0x7100040b0c
int unit_command_40b0c(short id, void* arg) {
    Unit* u = find_unit(id);
    if (!u) return 0;
    IF_UNIT_STATE_ACTIVE(u->state()->id, {
        UnitActor* a = u->actor();
        if (a) return unit_command_9906c(a, arg);
    });
    return 0;
}

// 0x7100040404
int unit_command_40404(int side, int arg) {
    Unit* u = gUnitTable_c21690->unit(side_unit_id_db3c(side));
    if (!u) return 0;
    IF_UNIT_STATE_ACTIVE(u->state()->id, {
        UnitActor* a = u->actor();
        if (a) return unit_command_995f4(a, arg);
    });
    return 0;
}
void unit_command_863c4(UnitActor* actor);                                  // 0x71000863c4
void unit_command_864b4(UnitActor* actor);                                  // 0x71000864b4
float unit_range_997e0(UnitActor* actor);                                   // 0x71000997e0

// 0x710003e60c
int unit_command_3e60c(short id, int arg) {
    Unit* u = find_unit(id);
    if (!u) return 0;
    IF_UNIT_STATE_ACTIVE(u->state()->id, {
        UnitActor* a = u->actor();
        if (a) return a->command(arg);
    });
    return 0;
}

// 0x710003fc30
int unit_command_3fc30(int side, int arg) {
    Unit* u = find_unit(side_unit_id_db3c(side));
    if (!u) return 0;
    IF_UNIT_STATE_ACTIVE(u->state()->id, {
        UnitActor* a = u->actor();
        if (a) return a->command(arg);
    });
    return 0;
}

// 0x71000234fc
void UnitCommands::command_234fc(short id, unsigned char on) {
    Unit* u = find_unit(id);
    if (!u) return;
    IF_UNIT_STATE_ACTIVE(u->state()->id, {
        UnitActor* a = u->actor();
        if (a) {
            if (on)
                unit_command_863c4(a);
            else
                unit_command_864b4(a);
        }
    });
}

// 0x71000431f4
float side_unit_range_431f4(int side) {
    if (static_cast<unsigned int>(side) <= 1) {
        Unit* u = gUnitTable_c21690->unit(side_unit_id_db3c(side));
        if (u) {
            IF_UNIT_STATE_ACTIVE(u->state()->id, {
                UnitActor* a = u->actor();
                if (a) return unit_range_997e0(a);
            });
        }
    }
    return 800.0f;
}
// 0x7100043128
int side_unit_flag57_43128(int side) {
    if (static_cast<unsigned int>(side) <= 1) {
        Unit* u = gUnitTable_c21690->unit(side_unit_id_db3c(side));
        if (u) {
            IF_UNIT_STATE_ACTIVE(u->state()->id, {
                UnitActor* a = u->actor();
                if (!a) return 0;
                return (a->flags50 >> 57) & 1;
            });
        }
    }
    return 0;
}
struct UnitPart {
    unsigned char pad0[2];
    unsigned short flags;     // +02
    unsigned char pad4[5];
    unsigned char flags_9;    // +09
    unsigned char pada[2];
    unsigned char flags_c;    // +0c
};
struct UnitParts {
    unsigned char pad0[0x18];
    UnitPart* part;           // +18
};

int unit_command_99098(UnitActor* actor);                                   // 0x7100099098

// 0x710000eda4
int unit_part_flag_eda4(int id) {
    if (static_cast<unsigned int>(id) < 0xd2) return 0;
    Unit* u = find_unit(id);
    if (!u) return 0;
    IF_UNIT_STATE_ACTIVE(u->state()->id, {
        UnitActor* a = u->actor();
        if (!a) return 0;
        UnitParts* parts = a->parts;
        if (!parts) return 0;
        UnitPart* part = parts->part;
        if (!part) return 0;
        return part->flags & 1;
    });
    return 0;
}

// 0x7100041e24
int unit_command_41e24(short id) {
    Unit* u = find_unit(id);
    if (!u) return 0;
    if (!(u->state()->kind & 3)) return 0;
    UnitActor* a = 0;
    IF_UNIT_STATE_ACTIVE(u->state()->id, a = u->actor());
    return unit_command_99098(a);
}

class UnitLink {
public:
    Unit* linked_unit();

    unsigned char pad0[0x18];
    Unit* unit;               // +18
    unsigned char pad20[0x50];
    int mode;                 // +70
};

// 0x71000ce7e8
Unit* UnitLink::linked_unit() {
    Unit* u = unit;
    IF_UNIT_STATE_ACTIVE(u->state()->id, {
        UnitActor* a = u->actor();
        if (a) {
            switch (mode) {
            case 0x2f2: case 0x2f3: case 0x2f4: case 0x316: {
                return gUnitTable_c21690->unit_at(a->links[0]);
            }
            }
            return 0;
        }
    });
    return 0;
}
// 0x7100023260
void UnitCommands::command_23260(int side) {
    if (static_cast<unsigned int>(side) > 1) return;
    Unit* u = find_unit(side_unit_id_db3c(side));
    if (!u) return;
    UnitActor* a = 0;
    IF_UNIT_STATE_ACTIVE(u->state()->id, a = u->actor());
    UnitState* s = u->state();
    if (!a || !s) return;
    s->refresh();
    a->flags50 |= 0x200000000;
}

// 0x7100040bcc (the test jumps to the action; with the action inside it, the 12/13 compare merges into a ccmp)
unsigned int unit_rank_40bcc(short id) {
    Unit* u = gUnitTable_c21690->unit(id);
    if (u) {
        IF_UNIT_STATE_ACTIVE(u->state()->id, goto active);
        return 0xd2;
    active:
        UnitActor* a = u->actor();
        if (a && static_cast<unsigned char>(a->command(0x18))) {
            Unit* v = gUnitTable_c21690->units[id];
            if (v) {
                unsigned int rank = gUnitTable_c21690->roster.rank(v);
                if (rank < 0xd2) return rank;
            }
        }
    }
    return 0xd2;
}

int item_rank_1fb810(int item);                                              // 0x71001fb810

class UnitWatcher {
public:
    void update();
    void apply_c6828(void* target);
    void base_update_c480c();                                               // 0x71000c480c

    void* vtable;
    UnitState* state;         // +08
    unsigned char pad10[8];
    unsigned int flags;       // +18
};

// 0x71000c6190
void UnitWatcher::update() {
    base_update_c480c();
    UnitState* s = state;
    IF_UNIT_STATE_ACTIVE(s->id, {
        int rank = item_rank_1fb810(s->unit->state()->item());
        if (rank == 0xb)
            flags |= 0x40;
        else if (rank == 0x15)
            flags |= 0x80;
    });
}
template <class T> static inline const T& max_ref(const T& a, const T& b) { return a < b ? b : a; }

unsigned char unit_can_7c5a8(UnitActor* actor, int what);                  // 0x710007c5a8

struct UnitTimerOwner {
    unsigned char pad0[0x20];
    short slot;               // +20
};
struct UnitTimerTarget {
    unsigned char pad0[0x18];
    Unit* unit;               // +18
};

class UnitTimer {
public:
    void update(float dt, UnitTimerTarget* target);
    void step_3c784(UnitTimerTarget* target);                               // 0x710003c784

    unsigned char pad0[8];
    UnitTimerOwner* owner;    // +08
    unsigned char pad10[4];
    int steps;                // +14
    float time;               // +18
    unsigned char pad1c[0x27];
    bool held;                // +43
};

// 0x710003c674
void UnitTimer::update(float dt, UnitTimerTarget* target) {
    if (!held) time = max_ref(0.0f, time - dt);
    int slot = owner->slot;
    if (static_cast<unsigned int>(slot) <= 12) {
        Unit* u = target->unit;
        IF_UNIT_STATE_ACTIVE(u->state()->id, {
            UnitActor* a = u->actor();
            if (a && !unit_can_7c5a8(a, slot + 12)) {
                held = false;
                time = 0;
            }
        });
    }
    step_3c784(target);
    steps++;
}

struct UnitLinkOwner {
    unsigned char pad0[0x18];
    Unit* unit;               // +18
};

// A unit's own actor, or the actor of the unit its rank points at when both can command 0x18 and that unit's state
// allows it.
class UnitProxy {
public:
    void refresh();
    float reach();
    int flag15();

    __attribute__((always_inline)) UnitActor* effective_actor() {
        UnitActor* self = owner->unit->actor();
        if (!static_cast<unsigned char>(self->command(0x18))) return self;
        UnitActor* target = 0;
        if (static_cast<unsigned char>(owner->unit->actor()->command(0x18))) {
            unsigned int rank = gUnitTable_c21690->roster.rank(owner->unit);
            if (rank <= 0x6d6) {
                Unit* u = gUnitTable_c21690->unit(rank);
                if (u) IF_UNIT_STATE_ACTIVE(u->state()->id, target = u->actor());
            }
        }
        if (!target) target = self;
        return target;
    }

    void* vtable;
    UnitLinkOwner* owner;     // +08
};

// 0x71000af770
void UnitProxy::refresh() { effective_actor()->refresh(); }

// 0x71000af8c4
float UnitProxy::reach() { return effective_actor()->reach; }

// 0x71000afa10
int UnitProxy::flag15() { return (effective_actor()->flags50 >> 15) & 1; }
unsigned char side_ready_4126c(int side);                                   // 0x710004126c
void set_controller_3ce218(bool second);                                    // 0x71003ce218
int side_order_1eb798(int side, int order, int arg);                        // 0x71001eb798
int side_order_1eb904(int side, int order);                                 // 0x71001eb904

class RegionEntry {
public:
    int mode_20bbfc();                                                      // 0x710020bbfc
};
class RegionSettings {
public:
    RegionEntry* entry_20c154(int side);                                    // 0x710020c154
};
RegionSettings* get_region_settings();                                      // 0x710020bd74

class SideOrders {
public:
    int issue_cdbb4(int side);

    unsigned char pad0[4];
    unsigned int flags;       // +04
};

// 0x71000cdbb4
int SideOrders::issue_cdbb4(int side) {
    if (static_cast<unsigned int>(side) > 1) return 0x23;
    if (!side_ready_4126c(side)) return 0x23;
    set_controller_3ce218(side == 1);
    unsigned int f = flags;
    if (!f) return 0x23;
    if (f & 0x84009) {
        int mode = get_region_settings()->entry_20c154(side)->mode_20bbfc();
        switch (mode) {
        case 0:
            return side_order_1eb798(side, 0, 0);
        case 1:
            return side_order_1eb904(side, 0x2000);
        }
        return 0x23;
    }
    if (f & 0x800) {
        Unit* u = gUnitTable_c21690->unit(side_unit_id_db3c(side));
        if (!u) return 0x23;
        IF_UNIT_STATE_ACTIVE(u->state()->id, {
            UnitActor* a = u->actor();
            if (!a) return 0x23;
            if (!static_cast<unsigned char>(a->check_200(0))) return side_order_1eb798(side, 2, 0);
        });
        return 0x23;
    }
    if (!(f & 0x2000)) return 0x23;
    return side_order_1eb798(side, 6, 0);
}

struct Vec4f {
    float x, y, z, w;
};
// Reached through the GOT slot at 0x7100c216a8.
extern Vec4f kTrackDefaultVector;

int item_of_unit_a870(int unit_id);                                         // 0x710000a870
int item_field_211530(int item);                                            // 0x7100211530
void set_track_46c68(void* target, int id, int kind, Vec4f* value);         // 0x7100046c68

// 0x71000c6828
void UnitWatcher::apply_c6828(void* target) {
    int item = item_of_unit_a870(state->unit_id);
    if (static_cast<unsigned int>(item) > 0x44b) return;
    if (item_field_211530(item) != 0xb) return;
    Unit* u = state->unit;
    if (!u) return;
    IF_UNIT_STATE_ACTIVE(u->state()->id, {
        UnitActor* a = u->actor();
        if (!a) return;
        if (unit_can_7c5a8(a, 0xc)) {
            Vec4f v = kTrackDefaultVector;
            v.x = 0.01f;
            v.y = 0.01f;
            v.z = 0.01f;
            set_track_46c68(target, 0x96, 6, &v);
            set_track_46c68(target, 0x9c, 6, &v);
        }
        if (a->parts->part->flags_c & 2) {
            Vec4f v = kTrackDefaultVector;
            set_track_46c68(target, 0xb, 7, &v);
            set_track_46c68(target, 0xc, 7, &v);
        }
    });
}
struct SideOwnerId {
    unsigned char pad0[0x24];
    int unit_id;              // +24
};
struct SideSlotId {
    unsigned int kind;        // +00
    SideOwnerId* owner;       // +08
};
struct SideTableId {
    unsigned char pad0[0xb08];
    SideSlotId* sides[2];     // +b08
};
// Reached through the GOT slot at 0x7100c21698.
extern SideTableId* gSideTable;
short fallback_unit_id_170c58();                                            // 0x7100170c58

// The body of side_unit_id_db3c, for the callers that inline it.
static inline __attribute__((always_inline)) short side_unit_id(int side) {
    SideTableId* t = gSideTable;
    if (t) {
        SideSlotId* s = *(static_cast<unsigned int>(side) < 2 ? &t->sides[side] : &t->sides[0]);
        if (s && s->kind <= 1 && s->owner) return s->owner->unit_id;
    }
    return fallback_unit_id_170c58();
}

class UnitEffect {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual int kind();       // +20
    virtual void e28();
    virtual void e30();
    virtual void e38();
    virtual void e40();
    virtual void e48();
    virtual void e50();
    virtual void e58();
    virtual void e60();
    virtual void e68();
    virtual void e70();
    virtual void e78();
    virtual void e80();
    virtual void e88();
    virtual void e90();
    virtual void e98();
    virtual void ea0();
    virtual void ea8();
    virtual void eb0();
    virtual void eb8();
    virtual float value();    // +c0
};
UnitEffect* find_effect_7f7a8(UnitActor* actor, int id);                    // 0x710007f7a8
int battle_mode_1720c4();                                                   // 0x71001720c4
struct BattleMusic;
BattleMusic* current_music_6b40();                                          // 0x7100006b40
unsigned char music_flag_20d9c8(BattleMusic* music, int flag);              // 0x710020d9c8

// 0x710000ec18
int side_unit_busy_ec18(int side) {
    if (battle_mode_1720c4() == 0x1e) return 1;
    if (static_cast<unsigned int>(side) > 1) return 0;
    Unit* u = gUnitTable_c21690->unit(side_unit_id(side));
    if (!u) return 0;
    IF_UNIT_STATE_ACTIVE(u->state()->id, {
        UnitActor* a = u->actor();
        if (!a) return 0;
        UnitEffect* e = find_effect_7f7a8(a, 0x32);
        if (e && e->kind() == 0x1c) return 1;
        e = find_effect_7f7a8(a, 5);
        if (e && e->kind() == 6) return 1;
        BattleMusic* m = current_music_6b40();
        if (m && music_flag_20d9c8(m, 0xc)) return 1;
        return 0;
    });
    return 0;
}

void copy_state_cb0a8(UnitState* to, UnitState* from);                     // 0x71000cb0a8
unsigned char rule_on_3c520(int rule);                                      // 0x710003c520
unsigned char actor_flag_9d2b4(UnitActor* actor, int flag);                 // 0x710009d2b4
unsigned char actor_flag_81070(UnitActor* actor, int flag);                 // 0x7100081070

class UnitPair {
public:
    void sync();

    void* vtable;
    Unit* first;              // +08
    Unit* second;             // +10
    unsigned char pad18[0x1c];
    int mode;                 // +34
};

// 0x710005acb0
void UnitPair::sync() {
    copy_state_cb0a8(first->state(), second->state());
    first->body()->link(second->body());
    unsigned char on;
    if (rule_on_3c520(0x10)) {
        on = actor_flag_9d2b4(first->actor(), 0x19);
    } else {
        on = 0;
        Unit* u = first;
        IF_UNIT_STATE_ACTIVE(u->state()->id, {
            UnitActor* a = u->actor();
            if (a) {
                int m = mode;
                unsigned char can = unit_can_7c5a8(a, 0x19);
                on = can;
                if (m == 7) {
                    if (!can)
                        on = 1;
                    else
                        on = !actor_flag_81070(a, 0);
                }
            }
        });
    }
    UnitState* s = second->state();
    unsigned long bits = s->bits8;
    if (on)
        bits |= 1UL << 47;
    else
        bits &= ~(1UL << 47);
    s->bits8 = bits;
}

// 0x7100041990
int side_rank_41990(int side, unsigned int kind) {
    if (static_cast<unsigned int>(side) > 1) return -1;
    if (kind > 4) return -1;
    switch (kind) {
    case 1:
        if (side_unit_can(side, 0x21)) return 2;
        return side_unit_can(side, 0x22) == 0 ? 0 : 2;
    case 4:
        return !side_ready_4126c(side);
    case 0:
    case 2:
    case 3:
        return 0;
    }
    return -1;
}
class UnitView {
public:
    virtual void w00();
    virtual void w08();
    virtual void w10();
    virtual void w18();
    virtual void w20();
    virtual void show_item(int item, int value, int a, int b);  // +28
};

unsigned char item_allowed_ba08(int item, short id, unsigned char quiet);    // 0x710000ba08
int side_value_ebe8(int side);                                              // 0x710000ebe8
void give_item_33df0(Unit* unit, UnitActor* actor, int item);               // 0x7100033df0
void item_used_bc1c(int item);                                              // 0x710000bc1c
void special_item_171de0(int item);                                         // 0x7100171de0

class ItemRow {
public:
    int value_209ffc();                                                     // 0x7100209ffc
    int count_20a0cc();                                                     // 0x710020a0cc
};
class ItemRows {
public:
    ItemRow* row_20a4e8(int item);                                          // 0x710020a4e8
};
ItemRows* get_item_rows_20a31c();                                           // 0x710020a31c

class SideItemPanel {
public:
    void show_f4890(int unit_id, int value, int count);                     // 0x71000f4890
};
// Reached through the GOT slot at 0x7100c21d48.
extern SideItemPanel* gSideItemPanels[2];

// 0x71000211dc
int UnitTable::give_211dc(short id, int item, unsigned char show, unsigned char notify, unsigned char quiet) {
    if (!item_allowed_ba08(item, id, quiet)) return 0;
    Unit* u = unit(id);
    UnitState* s = u->state();
    int side = (s->bits8 & 1) ? 0 : static_cast<int>(s->bits8 & 2) - 1;
    int value = side_value_ebe8(side);
    UnitActor* a = 0;
    IF_UNIT_STATE_ACTIVE(u->state()->id, a = u->actor());
    give_item_33df0(u, a, item);
    if (show && !quiet) u->view()->show_item(item, value, 1, 1);
    if (notify && !quiet && static_cast<unsigned int>(side) <= 1) {
        if (gSideItemPanels[side]) {
            ItemRow* row = get_item_rows_20a31c()->row_20a4e8(item);
            gSideItemPanels[side]->show_f4890(s->unit_id, row->value_209ffc(), row->count_20a0cc());
        }
    }
    item_used_bc1c(item);
    if (static_cast<unsigned int>(item - 0x32) <= 0x1d) special_item_171de0(item);
    return 1;
}
struct ShopEntry {
    unsigned char pad0[0x30];
    unsigned char flags;      // +30
    unsigned char pad31[0xb];
};
struct Shop {
    unsigned char pad0[0x95a20];
    ShopEntry* entries;       // +95a20
};
// Reached through the GOT slot at 0x7100c216e8.
extern Shop* gShop;
// Reached through the GOT slots at 0x7100c21a10 and 0x7100c21a18.
extern float gUnitLimitMin;
extern float gUnitLimitMax;

unsigned char type_loaded_172174(int id);                                  // 0x7100172174
void raise_actor_99810(UnitActor* actor, float value);                      // 0x7100099810
void raise_actor_99820(UnitActor* actor, float value);                      // 0x7100099820
void set_unit_value_1715e0(int id, float value);                            // 0x71001715e0

struct UnitSetupLink {
    int id;                   // +00
    unsigned char rest[0x18];
};
void apply_setup_999d4(UnitActor* actor, UnitSetupLink* link);              // 0x71000999d4

struct UnitSetup {
    unsigned char used;       // +00
    unsigned char marked;     // +01
    unsigned char linked[0x3c];  // +02
    unsigned char pad3e[2];
    int rank;                 // +40
    unsigned char raise;      // +44
    unsigned char raise_shaped;  // +45
    unsigned char pad46[2];
    float value;              // +48
    float scale;              // +4c
    unsigned short shape;     // +50
    unsigned char pad52[2];
    int extra;                // +54
    float limit;              // +58
    UnitSetupLink link;       // +5c
};

class UnitSetupList {
public:
    void apply();

    unsigned char pad0[0x90];
    UnitSetup setups[0xd2];   // +90
};

// 0x7100075434
void UnitSetupList::apply() {
    float lo = gUnitLimitMin;
    float hi = gUnitLimitMax;
    for (int i = 0; i < 0xd2; i++) {
        UnitSetup* s = &setups[i];
        if (!s->used) continue;
        Unit* u = gUnitTable_c21690->unit(i);
        if (s->marked) {
            Shop* shop = gShop;
            type_loaded_172174(i);
            if (shop->entries[i].flags & 1) u->state()->bits8 |= 0x100;
        }
        UnitActor* a = 0;
        IF_UNIT_STATE_ACTIVE(u->state()->id, {
            a = u->actor();
            if (a) {
                if (s->raise) {
                    raise_actor_99810(a, s->value);
                } else if (s->raise_shaped) {
                    raise_actor_99820(a, s->value);
                    a->shape4e4 = s->shape;
                }
                a->value49c = s->extra;
                a->limit498 = lo > s->limit ? lo : s->limit;
                if (a->limit498 > hi) a->limit498 = hi;
            }
        });
        set_unit_value_1715e0(i, s->value);
        u->state()->set_scale(s->scale);
        apply_setup_999d4(a, &s->link);
    }
}
