// Parked unit-state functions (fourth session), with the unit-state header and the declarations of
// src/misc/s4_unit_state.cpp. 2174c: 5 off, the id < 0xd2 test (the original compares (id << 16 | 0xffff) with
// 0xd2fffe, ours and-masks). bf440: 2 off, the original merges the 12/13 compare into a ccmp with the returns kept as
// branches; ours does one or the other. 43e20: 11 off, the original keeps three return-1 blocks (copies per
// predecessor group); ours shares one.

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

