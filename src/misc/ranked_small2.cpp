// Small functions picked by tools/rank_targets.py that call functions defined in
// misc/helpers.cpp or misc/ranked_small.cpp without inlining them, so they need a unit of their
// own. Each definition names the address region of the original file it likely belongs to.
// Names are descriptive placeholders. Status: matching/README.md.

struct BattleSetupFlags {
    unsigned long flags;
};
BattleSetupFlags* get_battle_setup();                                       // 0x710016ef34
unsigned char global_part28_434a24(int value);                              // 0x71004540b4

// 0x710014935c; original file: battle objects, 0x710014935c
bool battle_unit_flag(int id) {
    BattleSetupFlags* setup = get_battle_setup();
    bool result = false;
    if (id != 999 && (setup->flags & 0x2000))
        result = global_part28_434a24(id);
    return result;
}
