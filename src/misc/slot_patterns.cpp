// Slot configuration script command: picks one of five on/off patterns for the three slots of a
// configuration, then sets its count and timer. Names are descriptive placeholders. Status:
// matching/README.md.

struct SlotConfig;
struct SlotOwner;
// Reached through the GOT slot at 0x7100c216e8.
extern SlotOwner* gShop;
SlotConfig* slot_config_18f104(SlotOwner* owner, int id);                   // 0x710018f104
void set_slot_1968f8(SlotConfig* config, int slot, int on);                 // 0x71001968f8
void set_count_196930(SlotConfig* config, int count);                       // 0x7100196930
void set_timer_196940(SlotConfig* config, int timer);                       // 0x7100196940

struct SlotCommand {
    int pad0;
    int config;               // +04
    int pattern;              // +08
    int count;                // +0c
    int timer;                // +10
};

// 0x71001bce10
void set_slot_pattern_1bce10(const SlotCommand* command) {
    SlotConfig* config = slot_config_18f104(gShop, command->config);
    int count = command->count;
    switch (command->pattern) {
    case 0:
        set_slot_1968f8(config, 0, 0);
        set_slot_1968f8(config, 1, 0);
        set_slot_1968f8(config, 2, 0);
        count = 3;
        break;
    case 1:
        set_slot_1968f8(config, 0, 1);
        set_slot_1968f8(config, 1, 0);
        set_slot_1968f8(config, 2, 0);
        break;
    case 2:
        set_slot_1968f8(config, 0, 0);
        set_slot_1968f8(config, 1, 1);
        set_slot_1968f8(config, 2, 0);
        break;
    case 3:
        set_slot_1968f8(config, 0, 0);
        set_slot_1968f8(config, 1, 0);
        set_slot_1968f8(config, 2, 1);
        break;
    case 4:
        set_slot_1968f8(config, 0, 1);
        set_slot_1968f8(config, 1, 1);
        set_slot_1968f8(config, 2, 1);
        break;
    }
    set_count_196930(config, count);
    set_timer_196940(config, command->timer);
}