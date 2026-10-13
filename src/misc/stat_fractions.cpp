// Stat percentages found by tools/family_scan.py --immediates: each asks the stat query for one
// stat of the given unit and returns it as a fraction of 100, or 1 when the query fails. They differ
// only in the stat; functions are named after their address. Status: matching/README.md.

int stat_query(int unit, int stat, unsigned int* value, unsigned int* limit); // 0x71000011ec

// 0x7100001198: stat 0x5
float stat_fraction_1198(int unit) {
    unsigned int value = 0;
    unsigned int limit = 0;
    if (static_cast<unsigned int>(stat_query(unit, 0x5, &value, &limit)) <= 3)
        return value / 100.0f;
    return 1.0f;
}

// 0x71000016c8: stat 0x11
float stat_fraction_16c8(int unit) {
    unsigned int value = 0;
    unsigned int limit = 0;
    if (static_cast<unsigned int>(stat_query(unit, 0x11, &value, &limit)) <= 3)
        return value / 100.0f;
    return 1.0f;
}

// 0x710000171c: stat 0x12
float stat_fraction_171c(int unit) {
    unsigned int value = 0;
    unsigned int limit = 0;
    if (static_cast<unsigned int>(stat_query(unit, 0x12, &value, &limit)) <= 3)
        return value / 100.0f;
    return 1.0f;
}

// 0x7100001770: stat 0x13
float stat_fraction_1770(int unit) {
    unsigned int value = 0;
    unsigned int limit = 0;
    if (static_cast<unsigned int>(stat_query(unit, 0x13, &value, &limit)) <= 3)
        return value / 100.0f;
    return 1.0f;
}

// 0x71000017c4: stat 0x14
float stat_fraction_17c4(int unit) {
    unsigned int value = 0;
    unsigned int limit = 0;
    if (static_cast<unsigned int>(stat_query(unit, 0x14, &value, &limit)) <= 3)
        return value / 100.0f;
    return 1.0f;
}

// 0x7100001818: stat 0x15
float stat_fraction_1818(int unit) {
    unsigned int value = 0;
    unsigned int limit = 0;
    if (static_cast<unsigned int>(stat_query(unit, 0x15, &value, &limit)) <= 3)
        return value / 100.0f;
    return 1.0f;
}
