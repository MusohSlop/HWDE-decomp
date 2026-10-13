// Per-slot table passes found by tools/family_scan.py --immediates: each runs its slot handler over
// every slot of a fixed table, passing the slot's index and the caller's argument. They differ only
// in the slot size, the slot count and the handler; types and functions are named after their
// address. Status: matching/README.md.

struct TableSlot1fea4c {
    unsigned char data[0x1c8];
};
void handle_slot_1fe32c(TableSlot1fea4c* slot, int index, void* arg);                 // 0x71001fe32c

// 0x71001fea4c
void for_each_slot_1fea4c(TableSlot1fea4c* slots, void* arg) {
    for (int i = 0; i < 0x4b; ++i)
        handle_slot_1fe32c(&slots[i], i, arg);
}

struct TableSlot207068 {
    unsigned char data[0xc0];
};
void handle_slot_2066fc(TableSlot207068* slot, int index, void* arg);                 // 0x71002066fc

// 0x7100207068
void for_each_slot_207068(TableSlot207068* slots, void* arg) {
    for (int i = 0; i < 0xc8; ++i)
        handle_slot_2066fc(&slots[i], i, arg);
}

struct TableSlot2141b4 {
    unsigned char data[0x10];
};
void handle_slot_213d4c(TableSlot2141b4* slot, int index, void* arg);                 // 0x7100213d4c

// 0x71002141b4
void for_each_slot_2141b4(TableSlot2141b4* slots, void* arg) {
    for (int i = 0; i < 0xfa; ++i)
        handle_slot_213d4c(&slots[i], i, arg);
}

struct TableSlot214a5c {
    unsigned char data[0x28];
};
void handle_slot_214214(TableSlot214a5c* slot, int index, void* arg);                 // 0x7100214214

// 0x7100214a5c
void for_each_slot_214a5c(TableSlot214a5c* slots, void* arg) {
    for (int i = 0; i < 0x40; ++i)
        handle_slot_214214(&slots[i], i, arg);
}

struct TableSlot215308 {
    unsigned char data[0x14];
};
void handle_slot_214f78(TableSlot215308* slot, int index, void* arg);                 // 0x7100214f78

// 0x7100215308
void for_each_slot_215308(TableSlot215308* slots, void* arg) {
    for (int i = 0; i < 0x40; ++i)
        handle_slot_214f78(&slots[i], i, arg);
}
