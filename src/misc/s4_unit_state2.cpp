// More functions that inline the unit-state test (fourth session's unit-state batch, continued from
// src/misc/s4_unit_state.cpp): those with a jump table of their own (one .rodata map per unit) and those that the
// first unit calls (kept apart so they don't inline there). Functions are named after their address.

#include "misc/s4_unit_state.h"

int actor_flag_8105c(UnitActor* actor, int flag);                           // 0x710008105c
int actor_slot_8bf6c(UnitActor* actor, int slot);                           // 0x710008bf6c
int actor_slot_8be6c(UnitActor* actor, int slot);                           // 0x710008be6c
unsigned char actor_on_835a8(UnitActor* actor);                             // 0x71000835a8
unsigned int actor_mode_990e0(UnitActor* actor);                            // 0x71000990e0
int item_class_c42c(int item);                                              // 0x710000c42c

// 0x7100041f0c
int unit_slot_on_41f0c(short id, unsigned int slot) {
    Unit* u = find_unit(id);
    if (!u) return 0;
    if (!(u->state()->kind & 3)) return 0;
    int type = u->state()->type();
    UnitActor* a = 0;
    IF_UNIT_STATE_ACTIVE(u->state()->id, a = u->actor());
    switch (slot) {
    case 0: case 1: case 2: case 3: case 4:
        if (type != 0xc) return 0;
        return actor_flag_8105c(a, slot + 0xc);
    case 5: case 6: case 7: case 8:
        if (type != 3) return 0;
        return actor_slot_8bf6c(a, slot - 5);
    case 9: case 10: case 11:
        if (type != 7) return 0;
        return actor_slot_8be6c(a, slot - 8);
    case 12:
        if (type != 0x12) return 0;
        return u->state()->special();
    case 13: case 14: case 15: case 16: case 17:
        if (!actor_on_835a8(a)) return 0;
        return slot - 0xd == actor_mode_990e0(a);
    case 18: case 19: case 20: case 21:
        if (type != 6) return 0;
        return actor_flag_8105c(a, slot - 6);
    case 22: case 23: case 24: case 25: case 26:
        if (!(u->state()->flags_e & 1)) return 0;
        if (item_class_c42c(u->state()->item()) != 0x18) return 0;
        return actor_slot_8be6c(a, slot - 0x15);
    case 27: case 28:
        if (type != 0x1b) return 0;
        return actor_flag_8105c(a, slot - 0xf);
    }
    return 0;
}
unsigned char side_busy_3e7a10(int side);                                   // 0x71003e7a10

// 0x710004126c
unsigned char side_ready_4126c(int side) {
    return static_cast<unsigned int>(side) <= 1 && !side_unit_can(side, 0x22) && !side_unit_can(side, 0xf) &&
           !side_unit_can(side, 0x2e) && !side_busy_3e7a10(side);
}