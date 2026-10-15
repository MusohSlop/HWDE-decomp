// PARKED fa9c (724 B, jump table at 0x710073dc88: a unit of its own), about 41 abstract off: the switch and the shared
// result test match in shape; the original orders the case blocks 0, 4, 11, 14, 1, 2, 3, 5-10, 12, 13, 15 and tail-merges
// the actor_flag_8105c calls (mov w1, #n; b call). Needs Game::has_flag_2026fc = 0x71002026fc in units.json symbols.

// More functions that inline the unit-state test (fourth session's unit-state batch, continued from
// src/misc/s4_unit_state.cpp; one unit per jump table). Functions are named after their address.

#include "misc/s4_unit_state.h"

int actor_flag_8105c(UnitActor* actor, int flag);                           // 0x710008105c

class Game {
public:
    unsigned char has_flag_2026fc(int flag);                                // 0x71002026fc
};
Game* get_game();                                                           // 0x7100204728

struct ItemDefFlags {
    unsigned char pad0[0x3d];
    unsigned char flags;      // +3d: bit 7
    unsigned char pad3e[0x12];
};
// Reached through the GOT slot at 0x7100c216a0.
extern ItemDefFlags* gItemDefs;

struct Rule {
    unsigned char pad0[0x100];
    short kind;               // +100
    short value;              // +102
    unsigned char pad104[0xc];
};
struct RuleSet {
    Rule* rules;              // +00
};

// 0x710000fa9c
int rule_value_fa9c(short id, RuleSet* set, unsigned int index, int add, int fallback) {
    Unit* u = find_unit(id);
    if (!u) return fallback;
    IF_UNIT_STATE_ACTIVE(u->state()->id, {
        UnitActor* a = u->actor();
        if (!a) return fallback;
        Rule* rules = set->rules;
        unsigned char r;
        switch (rules[index].kind) {
        case 0:
            if (u->state()->type() != 0x14) return fallback;
            r = get_game()->has_flag_2026fc(0x11);
            break;
        case 4: r = actor_flag_8105c(a, 0xe); break;
        case 11: r = actor_flag_8105c(a, 0x15); break;
        case 14:
            if (u->state()->kind & 3) return fallback;
            goto ok;
        case 1: r = u->state()->special(); break;
        case 2: r = actor_flag_8105c(a, 0xc); break;
        case 3: r = actor_flag_8105c(a, 0xd); break;
        case 5: r = actor_flag_8105c(a, 0xf); break;
        case 6: r = actor_flag_8105c(a, 0x10); break;
        case 7: r = actor_flag_8105c(a, 0x11); break;
        case 8: r = actor_flag_8105c(a, 0x12); break;
        case 9: r = actor_flag_8105c(a, 0x13); break;
        case 10: r = actor_flag_8105c(a, 0x14); break;
        case 12: {
            if (u->state()->type() != 0x14) return fallback;
            float f = u->state()->rate400();
            float g = u->state()->rate410();
            if (!(g + -1.1920929e-05f <= f && g + 1.1920929e-05f >= f)) return fallback;
            r = get_game()->has_flag_2026fc(0x11);
            break;
        }
        case 13:
            if (!(u->state()->kind & 3)) return fallback;
            goto ok;
        case 15: {
            int item = u->state()->item();
            unsigned char flags = static_cast<unsigned int>(item) < 0x44c ? gItemDefs[item].flags : ((ItemDefFlags*)0)->flags;
            if (!(flags & 0x80)) return fallback;
            goto ok;
        }
        default:
            return fallback;
        }
        if (!r) return fallback;
    ok:        short v = rules[index].value;
        if (v < 0) return fallback;
        return v + add;
    });
    return fallback;
}