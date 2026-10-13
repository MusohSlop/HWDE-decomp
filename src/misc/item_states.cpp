// Item state tests found by tools/family_scan.py --immediates (the shape of ItemTable::is_special in
// misc/accessors.cpp): each tests whether an item's state is one value, after a range check. They
// differ only in the state; functions are named after their address. Status: matching/README.md.

struct ItemStateEntry {
    int state;
    int value;
};
struct ItemStates {
    ItemStateEntry entries[0x2e4];
};

// 0x71001ff25c: state 0
unsigned char item_in_state_1ff25c(ItemStates* table, int item) {
    if (static_cast<unsigned int>(item) <= 0x2e3)
        return table->entries[item].state == 0;
    return 0;
}

// 0x71001ff280: state 1
unsigned char item_in_state_1ff280(ItemStates* table, int item) {
    if (static_cast<unsigned int>(item) <= 0x2e3)
        return table->entries[item].state == 1;
    return 0;
}

// 0x71001ff2ec: state 4
unsigned char item_in_state_1ff2ec(ItemStates* table, int item) {
    if (static_cast<unsigned int>(item) <= 0x2e3)
        return table->entries[item].state == 4;
    return 0;
}

// 0x71001ff310: state 5
unsigned char item_in_state_1ff310(ItemStates* table, int item) {
    if (static_cast<unsigned int>(item) <= 0x2e3)
        return table->entries[item].state == 5;
    return 0;
}

// 0x71001ff334: state 6
unsigned char item_in_state_1ff334(ItemStates* table, int item) {
    if (static_cast<unsigned int>(item) <= 0x2e3)
        return table->entries[item].state == 6;
    return 0;
}
