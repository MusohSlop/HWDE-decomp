// Officer reinforcement messages (0x71001d36c8, 0x71001d381c): post a message for an officer slot,
// and a second one with the officer's record unless the officer is already in the list, then count
// the post. Found by tools/family_scan.py --immediates. Names are descriptive placeholders. Status:
// matching/README.md.

struct BattleSetup {
    unsigned long flags;
};
BattleSetup* get_battle_setup();                                            // 0x710016ef34

struct OfficerRecord {
    unsigned char data[0x310];
};

struct Container18d5d8 {
    unsigned char pad[0xcee40];
    OfficerRecord officers[0x18]; // +cee40

    OfficerRecord* officer(unsigned int slot) { return slot < 0x18 ? &officers[slot] : nullptr; }
};

struct PostState {
    unsigned char pad[0x2455];
    unsigned char posts;      // +2455
};
PostState* member_18d5d8(Container18d5d8* container);                       // 0x710018d5d8
unsigned char has_entry_1a78d4(PostState* state, unsigned int slot, int list); // 0x71001a78d4
void post_message_1cea08(int a, int message, int kind, int duration, int b, int c, int d, int e,
                         int f, int g, OfficerRecord* record, int h, unsigned int slot, long i,
                         long j);                                           // 0x71001cea08

// Reached through the GOT slot at 0x7100c216e8.
extern Container18d5d8* gShop;
// Reached through the GOT slot at 0x7100c22e90.
extern unsigned int gFrameCounter;
// 0x71001d36c8
void post_officer_1d36c8(unsigned int slot) {
    unsigned long flags = get_battle_setup()->flags;
    if (slot > 0x17 || (flags & 0x4000) || member_18d5d8(gShop)->posts)
        return;
    unsigned int next = gFrameCounter + 1;
    Container18d5d8* container = gShop;
    gFrameCounter = next > 0x5ff ? 0 : next;
    post_message_1cea08(0, 0xc35a, 0x62, 0x1770, 6, 0, 3, 6, 0, 3, nullptr, 2, slot, 0, 0);
    if (!has_entry_1a78d4(member_18d5d8(gShop), slot, 0xd))
        post_message_1cea08(0, 0xc350, 0x62, 0xbb8, 6, 0, 3, 6, 0, 3, container->officer(slot), 2, slot, 0, 0);
    ++member_18d5d8(gShop)->posts;
}
// 0x71001d381c
void post_officer_1d381c(unsigned int slot) {
    unsigned long flags = get_battle_setup()->flags;
    if (slot > 0x17 || (flags & 0x4000) || member_18d5d8(gShop)->posts)
        return;
    unsigned int next = gFrameCounter + 1;
    Container18d5d8* container = gShop;
    gFrameCounter = next > 0x5ff ? 0 : next;
    post_message_1cea08(0, 0xc35a, 0x5c, 0x1770, 6, 0, 3, 6, 0, 3, nullptr, 2, slot, 0, 0);
    if (!has_entry_1a78d4(member_18d5d8(gShop), slot, 0xd))
        post_message_1cea08(0, 0xc350, 0x5c, 0xbb8, 6, 0, 3, 6, 0, 3, container->officer(slot), 2, slot, 0, 0);
    ++member_18d5d8(gShop)->posts;
}
