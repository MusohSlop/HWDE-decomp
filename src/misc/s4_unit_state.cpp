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
short side_unit_id_db3c(int side);                                          // 0x710000db3c

static inline Unit* find_unit(short id) { return gUnitTable_c21690->unit(id); }

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
                return gUnitTable_c21690->unit_at(a->link);
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