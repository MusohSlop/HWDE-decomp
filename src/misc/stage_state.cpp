// Stage state queries. Names are descriptive placeholders. Status: matching/README.md.

struct StageState {
    unsigned char pad[0x139940];
    unsigned char state;      // +139940
};
unsigned char game_byte_25812c();                                           // 0x710025812c

// 0x71001d740c
unsigned char stage_busy_1d740c(StageState* owner) {
    if (owner->state & 0x20)
        return 1;
    return game_byte_25812c() != 0;
}