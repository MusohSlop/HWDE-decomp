// Percentage queries found by tools/family_scan.py --immediates: when the owner has a given stat,
// read the stat's first value from the stat table and return it divided by 100. Each also reads
// the second value and discards it, as the original does. They differ only in the stat id;
// functions are named after their address. Status: matching/README.md.

struct StatEntry;
struct StatTable;
unsigned char owner_has_stat(void* owner, int stat);                        // 0x710000e1f4
StatTable* load_global_2151a0();                                            // 0x71002151a0
StatEntry* stat_entry(StatTable* table, int stat);                          // 0x7100215354
unsigned int stat_value(StatEntry* entry, int which);                       // 0x7100215150

// 0x7100001a70: stat 0x5
float stat_ratio_1a70(void* owner) {
    if (!owner_has_stat(owner, 0x5))
        return 0.0f;
    unsigned int value = stat_value(stat_entry(load_global_2151a0(), 0x5), 0);
    stat_value(stat_entry(load_global_2151a0(), 0x5), 1);
    return value / 100.0f;
}

// 0x7100002bf4: stat 0x25
float stat_ratio_2bf4(void* owner) {
    if (!owner_has_stat(owner, 0x25))
        return 0.0f;
    unsigned int value = stat_value(stat_entry(load_global_2151a0(), 0x25), 0);
    stat_value(stat_entry(load_global_2151a0(), 0x25), 1);
    return value / 100.0f;
}

// 0x7100002cd0: stat 0x27
float stat_ratio_2cd0(void* owner) {
    if (!owner_has_stat(owner, 0x27))
        return 0.0f;
    unsigned int value = stat_value(stat_entry(load_global_2151a0(), 0x27), 0);
    stat_value(stat_entry(load_global_2151a0(), 0x27), 1);
    return value / 100.0f;
}

// 0x7100002d40: stat 0x28
float stat_ratio_2d40(void* owner) {
    if (!owner_has_stat(owner, 0x28))
        return 0.0f;
    unsigned int value = stat_value(stat_entry(load_global_2151a0(), 0x28), 0);
    stat_value(stat_entry(load_global_2151a0(), 0x28), 1);
    return value / 100.0f;
}

// 0x7100002db0: stat 0x2b
float stat_ratio_2db0(void* owner) {
    if (!owner_has_stat(owner, 0x2b))
        return 0.0f;
    unsigned int value = stat_value(stat_entry(load_global_2151a0(), 0x2b), 0);
    stat_value(stat_entry(load_global_2151a0(), 0x2b), 1);
    return value / 100.0f;
}

// 0x7100002e20: stat 0x2c
float stat_ratio_2e20(void* owner) {
    if (!owner_has_stat(owner, 0x2c))
        return 0.0f;
    unsigned int value = stat_value(stat_entry(load_global_2151a0(), 0x2c), 0);
    stat_value(stat_entry(load_global_2151a0(), 0x2c), 1);
    return value / 100.0f;
}

// 0x7100002e90: stat 0x2d
float stat_ratio_2e90(void* owner) {
    if (!owner_has_stat(owner, 0x2d))
        return 0.0f;
    unsigned int value = stat_value(stat_entry(load_global_2151a0(), 0x2d), 0);
    stat_value(stat_entry(load_global_2151a0(), 0x2d), 1);
    return value / 100.0f;
}

// 0x7100002f00: stat 0x2e
float stat_ratio_2f00(void* owner) {
    if (!owner_has_stat(owner, 0x2e))
        return 0.0f;
    unsigned int value = stat_value(stat_entry(load_global_2151a0(), 0x2e), 0);
    stat_value(stat_entry(load_global_2151a0(), 0x2e), 1);
    return value / 100.0f;
}

// 0x7100002f70: stat 0x2f
float stat_ratio_2f70(void* owner) {
    if (!owner_has_stat(owner, 0x2f))
        return 0.0f;
    unsigned int value = stat_value(stat_entry(load_global_2151a0(), 0x2f), 0);
    stat_value(stat_entry(load_global_2151a0(), 0x2f), 1);
    return value / 100.0f;
}
