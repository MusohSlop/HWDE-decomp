// A unit task's update (fourth session, 2-copy family b8168): when the unit's actor is there, asks for it again if the
// unit-state test passes (include/misc/s4_unit_state.h), then continues (0x71000b7614 or 0x71000b7654).
// UnitTask::update<0> (0x71000b8168), update<1> (0x71000b821c). Names are descriptive placeholders.

#include "misc/s4_unit_state.h"

struct UnitOwner {
    unsigned char pad0[0x18];
    Unit* unit;               // +18
};

class UnitTask {
public:
    template <int Copy> void update();
    void next_b7614();                                                      // 0x71000b7614
    void next_b7654();                                                      // 0x71000b7654

    template <int Copy> void next() {
        if (Copy == 0)
            next_b7614();
        else
            next_b7654();
    }

    void* vtable;
    UnitOwner* owner;         // +08
};

template <int Copy>
void UnitTask::update() {
    if (!owner->unit->actor()) return;
    Unit* unit = owner->unit;
    IF_UNIT_STATE_ACTIVE(unit->state()->id, unit->actor());
    next<Copy>();
}

// 0x71000b8168
template void UnitTask::update<0>();
// 0x71000b821c
template void UnitTask::update<1>();
