// Parked unit-state functions (fourth session), with the unit-state header and the declarations of
// src/misc/s4_unit_state.cpp. 2174c: 5 off, the id < 0xd2 test (the original compares (id << 16 | 0xffff) with
// 0xd2fffe, ours and-masks). bf440: 2 off, the original merges the 12/13 compare into a ccmp with the returns kept as
// branches; ours does one or the other. 43e20: 11 off, the original keeps three return-1 blocks (copies per
// predecessor group); ours shares one. 8b910: 7 off, the select of the item record survives only as a select of loads
// (done below); the original keeps the platform-bit-0 return and the last flag test as branches, ours folds the last into a
// bic and places the return-1 block apart. It uses UnitTable::by_ref (inline: return units[ref->id];).

struct ItemDef {
    unsigned char pad0[0x32];
    unsigned short kind;      // +32
    unsigned char pad34[0x1c];
};
extern ItemDef* gItemDefs;   // GOT 0x7100c216a0
struct UnitPartKind {
    int kind;                 // +00
};
struct PlatformFlags64 {
    unsigned long bits;       // +00
};
PlatformFlags64* get_platform_flags();                                      // 0x710016ef34
void unit_command_98d2c(UnitActor* actor, void* a, void* b);                // 0x7100098d2c
// bf440 is int UnitState::item_blocked() (declare it in UnitState).

// 0x710002174c
void UnitCommands::command_2174c(int side, void* a, void* b) {
    short id = side_unit_id_db3c(side);
    Unit* u = find_unit(id);
    if (!u) return;
    if (static_cast<unsigned short>(id) >= 0xd2) return;
    IF_UNIT_STATE_ACTIVE(u->state()->id, {
        UnitActor* actor = u->actor();
        if (actor) unit_command_98d2c(actor, a, b);
    });
}

// 0x71000bf440
int UnitState::item_blocked() {
    unsigned int item = this->item();
    if (item > 0x44b) return 1;
    if (gItemDefs[static_cast<int>(item)].kind != 5) return 1;
    Unit* u = gUnitTable_c21690->unit_at(unit_id);
    if (!u) return 1;
    IF_UNIT_STATE_ACTIVE(u->state()->id, {
        UnitActor* a = u->actor();
        if (a) {
            UnitParts* parts = a->parts;
            if (parts && reinterpret_cast<UnitPartKind*>(parts)->kind == 0xfc) return 0;
        }
    });
    return 1;
}

// 0x7100043e20
int side_unit_blocked_43e20(int side) {
    if (static_cast<unsigned int>(side) > 1) return 0;
    if (get_platform_flags()->bits & 0x100b0000cUL) return 0;
    Unit* u = find_unit(side_unit_id_db3c(side));
    if (!u) return 1;
    IF_UNIT_STATE_ACTIVE(u->state()->id, {
        UnitActor* a = u->actor();
        if (!a) return 1;
        return !static_cast<unsigned char>(a->command(0x30));
    });
    return 1;
}


struct UnitRef {
    unsigned short id;        // +00
};
struct ItemDefSigned {
    unsigned char pad0[0x32];
    short kind;               // +32
    unsigned char pad34[0x1c];
};
// Reached through the GOT slot at 0x7100c216a0.
extern ItemDefSigned* gItemDefs;
struct PlatformBits {
    unsigned char bits;       // +00
};
PlatformBits* get_platform_flags();                                         // 0x710016ef34

inline Unit* UnitTable::by_ref(UnitRef* ref) { return units[ref->id]; }

class UnitItemCheck {
public:
    int matches_8b910(int kind);

    unsigned char pad0[0x10];
    UnitState* state;         // +10
};

// 0x710008b910 (only the switch part of the unit-state test: an actor unless the id is one of the down states)
int UnitItemCheck::matches_8b910(int kind) {
    if (!(state->kind & 3)) return 0;
    if (get_platform_flags()->bits & 4) return 0;
    UnitRef* ref = state->unit_ref();
    if (!ref) return 0;
    if (!gUnitTable_c21690->has_22640(ref)) return 0;
    Unit* u = gUnitTable_c21690->by_ref(ref);
    if (!u) return 0;
    int item = item_of_unit_a870(u->state()->unit_id);
    short k = static_cast<unsigned int>(item) < 0x44c ? gItemDefs[item].kind : ((ItemDefSigned*)0)->kind;
    if (k != kind) return 0;
    if (u->state()->flags9 & 1) return 0;
    if (!(get_platform_flags()->bits & 1)) return 1;
    short id = side_unit_id_db3c((state->bits8 & 3) != 2);
    if (static_cast<unsigned short>(id) >= 0xd2) return 1;
    Unit* v = gUnitTable_c21690->unit(id);
    if (!v) return 1;
    UnitActor* a;
    switch (v->state()->id) {
    case 6: case 7: case 9: case 10:
    case 16: case 17: case 18: case 19: case 20: case 21: case 39:
        a = 0;
        break;
    default:
        a = v->actor();
    }
    if (a->parts->part->flags_9 & 4) return 0;
    return 1;
}
// 74eb0 (UnitSetupList::capture, 636 B; declare void capture(); in UnitSetupList), 21 off: our record address is
// computed once above the null check and the unit table's GOT address is hoisted out of the loop; the original
// recomputes this + i*0x78 in each block (madd) and keeps 0xffff in a register instead.
float actor_rate_85914(UnitActor* actor);                                   // 0x7100085914
unsigned char actor_limited_99a60(UnitActor* actor);                        // 0x7100099a60
void capture_setup_99830(UnitActor* actor, UnitSetupLink* link);            // 0x7100099830

// 0x7100074eb0
void UnitSetupList::capture() {
    for (int i = 0; i < 0xd2; i++) {
        Unit* u = gUnitTable_c21690->unit(i);
        if (!u) {
            UnitSetup* s = &setups[i];
            memset(s, 0, 0x3e);
            s->rank = -1;
            s->raise = 0;
            s->raise_shaped = 0;
            s->value = 0;
            s->scale = 0;
            s->shape = 0xffff;
            s->extra = 0;
            s->limit = 0;
            s->link.id = -1;
            memset(s->link.rest, 0, sizeof(s->link.rest));
            continue;
        }
        setups[i].used = 1;
        UnitSetup* s = &setups[i];
        s->marked = (u->state()->bits8 >> 8) & 1;
        IF_UNIT_STATE_ACTIVE(u->state()->id, {
            UnitActor* a = u->actor();
            if (a) {
                s->rank = a->value45c;
                for (int j = 0; j < 0x3c; j++) {
                    Unit* v = gUnitTable_c21690->unit_at(a->links[j]);
                    if (v && (v->state()->flags9 & 1)) s->linked[j] = 1;
                }
                s->raise = (a->flags50 >> 35) & 1;
                s->raise_shaped = unit_command_85908(a);
                s->value = u->state()->rate308();
                s->scale = u->state()->rate300();
                s->shape = actor_rate_85914(a);
                s->extra = a->value49c;
                if (actor_limited_99a60(a)) s->limit = a->limit498;
                s->link.id = -1;
                memset(s->link.rest, 0, sizeof(s->link.rest));
                capture_setup_99830(a, &s->link);
            }
        });
    }
}
// 41b7c (680 B, jump table at 0x710073faf0, right after 41990's in the same .rodata): 26 off with direct stores per
// case (below); 16 off with a local k stored once after the switch and the zero cases storing directly (goto calc).
// The switch itself matches once the zero cases 4-10, 13, 18, ... 42 are listed in a block of their own. Left: the
// original tail-merges the kind stores (mov w8, #k; b store) and duplicates the join for case 12 (mov w0, #1).
struct UnitStateInfo {
    unsigned char pad0[4];
    short gauge;              // +04
    unsigned char pad6[2];
    unsigned char flags;      // +08: bit 3 has a gauge
};

// 0x7100041b7c
int unit_gauge_41b7c(short id, float* ratio, int* kind) {
    *ratio = 0;
    if (kind) *kind = 0;
    Unit* u = find_unit(id);
    if (!u) return 0;
    if (!(u->state()->kind & 3)) return 0;
    UnitStateInfo* info = u->state()->info;
    if (!(info->flags & 8)) return 0;
    UnitActor* a = 0;
    IF_UNIT_STATE_ACTIVE(u->state()->id, a = u->actor());
    if (!kind) return 1;
    UnitEffect* e;
    switch (info->gauge) {
    case 11: *kind = 6; break;
    case 12: *kind = 1; break;
    case 14: *kind = 2; break;
    case 15: *kind = 3; break;
    case 16:
        *kind = 0;
        *ratio = 0;
        e = find_effect_7f7a8(a, 0x1c);
        if (e) *ratio = e->value();
        return 1;
    case 17: *kind = 4; break;
    case 19: *kind = 5; break;
    case 21:
        *kind = 0;
        *ratio = 0;
        e = find_effect_7f7a8(a, 0x15);
        if (e) *ratio = e->value();
        return 1;
    case 27:
        *kind = 0;
        *ratio = 0;
        e = find_effect_7f7a8(a, 0xc);
        if (!e || e->kind() < 1) {
            e = find_effect_7f7a8(a, 0xd);
            if (!e || e->kind() < 1) return 1;
        }
        *ratio = e->value();
        return 1;
    case 33: *kind = 7; break;
    case 37:
        *kind = 0;
        *ratio = 0;
        e = find_effect_7f7a8(a, 0x18);
        if (e) *ratio = e->value();
        return 1;
    case 38: *kind = 8; break;
    case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 13: case 18: case 20: case 22: case 23:
    case 24: case 25: case 26: case 28: case 29: case 30: case 31: case 32: case 34: case 35: case 36: case 39:
    case 40: case 41: case 42:
        *kind = 0;
        break;
    default:
        *kind = 0;
        break;
    }
    *ratio = (a->limit498 - gUnitLimitMin) / (gUnitLimitMax - gUnitLimitMin);
    return 1;
}

// c69a0 (UnitWatcher::pose_c69a0, 740 B; declare void pose_c69a0(void* target); in UnitWatcher), 2 off: the
// quaternion's fmul operands come out in other registers (cz, cx, sy); a 64-form search over operand orders runs in
// worktrees\s4_perm\c69a0.
void sin_cos_fd70(float angle, float* s, float* c);                         // 0x710000fd70

// A rotation from three half angles (x, y, z order).
static inline void quat_from_half_angles(Vec4f* q, float hx, float hy, float hz) {
    float sx, cx, sy, cy, sz, cz;
    sin_cos_fd70(hx, &sx, &cx);
    sin_cos_fd70(hy, &sy, &cy);
    sin_cos_fd70(hz, &sz, &cz);
    q->x = sx * cy * cz - cx * sy * sz;
    q->y = cx * sy * cz + sx * cy * sz;
    q->z = cy * cx * sz - sx * sy * cz;
    q->w = cy * cx * cz + sx * sy * sz;
}

static inline void set_pose(void* target, int id, float sx, float sy, float sz, float hx, float hy, float hz, float px,
                            float py, float pz) {
    Vec4f s;
    s.x = sx;
    s.y = sy;
    s.z = sz;
    s.w = 0.0f;
    Vec4f q;
    Vec4f p;
    p.x = px;
    p.y = py;
    p.z = pz;
    p.w = 0.0f;
    quat_from_half_angles(&q, hx, hy, hz);
    set_track_46c68(target, id, 4, &s);
    set_track_46c68(target, id, 7, &q);
    set_track_46c68(target, id, 1, &p);
}
// 0x71000c69a0
void UnitWatcher::pose_c69a0(void* target) {
    UnitState* s = state;
    Unit* u = s->unit;
    UnitActor* a = 0;
    IF_UNIT_STATE_ACTIVE(u->state()->id, a = u->actor());
    if (item_rank_1fb810(s->unit->state()->item()) != 0x15) return;
    if (!unit_can_7c5a8(a, 0xc)) return;
    set_pose(target, 0x1f4, 1.0f, 0.8f, 0.7f, -0.785398185f, 0.0872664601f, 0.0f, 0.0f, -3.0f, 4.0f);
    set_pose(target, 0x1f5, 1.5f, 1.0f, 1.0f, -0.0884881988f, 0.0f, 0.0f, 0.0f, 21.86f, -8.12f);
}
// 17860 (UnitAim::update, 816 B), about 50 off: a first draft. The original keeps this in x20, has a 0xb0 frame with
// the second area at sp+0xc apart from the matrix at sp+0x10, and reads the place's y/z pair first in the second copy.
extern "C" float sqrtf(float value);                                        // 0x71006008a0 (import)

struct Vec3f {
    float x, y, z;
};
struct UnitPlace {
    unsigned char pad0[0x20];
    Vec3f pos;                // +20
};
struct UnitMatrix {
    float rows[12];
    Vec3f pos;                // +30
    float w;
};
unsigned int unit_count_453984();                                           // 0x7100453984
unsigned char unit_area_4549dc(int id, int* area);                          // 0x71004549dc
void unit_matrix_453bb8(UnitMatrix* out, int id);                           // 0x7100453bb8
unsigned char keep_target_ce28(int area, int ref_area, bool closer);       // 0x710000ce28

static inline float distance(const Vec3f& a, const Vec3f& b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float dz = a.z - b.z;
    return sqrtf(dx * dx + dy * dy + dz * dz);
}

class UnitAim {
public:
    void update();

    // The target's position: the unit's own if the id is out of range.
    Vec3f target_pos(int id) {
        Vec3f p = self->place()->pos;
        if (id >= 0 && static_cast<unsigned int>(id) < unit_count_453984()) {
            UnitMatrix m;
            unit_matrix_453bb8(&m, id);
            p = m.pos;
        }
        return p;
    }

    // The target to keep: the current one unless the new one is preferred.
    __attribute__((always_inline)) int pick(int current, int target, float dist, int ref_area) {
        int area;
        Vec3f p = target_pos(current);
        if (current >= 0 && static_cast<unsigned int>(current) < unit_count_453984() &&
            unit_area_4549dc(current, &area)) {
            float d = distance(p, self->place()->pos);
            if (!keep_target_ce28(area, ref_area, dist < d)) return current;
        }
        return target;
    }
    Unit* owner;              // +00
    Unit* self;               // +08
    int target;               // +10
};

// 0x7100017860
void UnitAim::update() {
    int t = target;
    int ref_area;
    if (t >= 0 && static_cast<unsigned int>(t) < unit_count_453984()) {
        if (!unit_area_4549dc(t, &ref_area)) return;
    }
    Vec3f p = target_pos(t);
    float dist = distance(p, self->place()->pos);
    UnitActor* a = owner->actor();
    int current = a->target_c0;
    if (current == t) return;
    t = pick(current, t, dist, ref_area);
    a->target_c0 = t;
    a->flags50 |= 0x1000;
    UnitActor* b = 0;
    IF_UNIT_STATE_ACTIVE(self->state()->id, b = self->actor());
    b->target_4f8 = pick(b->target_4f8, t, dist, ref_area);
}