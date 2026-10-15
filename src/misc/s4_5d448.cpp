// The unit roster's lookups (fourth session, 2-copy family 5d448): walk the null-terminated member list for the member
// whose key matches the unit's id and whose kind is 2, and return its value; the two copies swap which member call is
// the key and which the value (0x71000527d8 and 0x71000527fc). UnitRosterList::lookup<0> (0x710005d448) and
// lookup<1> (0x710005d4d0, the UnitTable::UnitRoster::rank of include/misc/s4_unit_state.h). Names are descriptive
// placeholders.

#include "misc/s4_unit_state.h"

class RosterMember {
public:
    int value_527d8();                                                      // 0x71000527d8
    int value_527fc();                                                      // 0x71000527fc

    template <int Copy> int key() { return Copy == 0 ? value_527d8() : value_527fc(); }
    template <int Copy> int value() { return Copy == 0 ? value_527fc() : value_527d8(); }

    unsigned char pad0[0x18];
    int kind;                 // +18
};

class UnitRosterList {
public:
    template <int Copy> int lookup(Unit* unit);

    unsigned char pad0[0x1d80];
    RosterMember* members[1]; // +1d80, null-terminated
};

template <int Copy>
int UnitRosterList::lookup(Unit* unit) {
    for (RosterMember** p = members; *p; ++p) {
        if ((*p)->key<Copy>() == unit->state()->unit_id && (*p)->kind == 2) return (*p)->value<Copy>();
    }
    return -1;
}

// 0x710005d448
template int UnitRosterList::lookup<0>(Unit*);
// 0x710005d4d0
template int UnitRosterList::lookup<1>(Unit*);
