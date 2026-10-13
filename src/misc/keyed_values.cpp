// Keyed value lookups found by tools/family_scan.py --immediates: each finds the entry whose lazy id
// resolves to the given id and returns one of its values, or -1 when no entry has it. They differ only
// in the value group; types and functions are named after their address. Status: matching/README.md.

class LazyId8 {
public:
    int resolve();                                                          // 0x71002471a8
};

struct KeyedEntry251820 {
    unsigned char pad[0x10];
    LazyId8 key;              // +10
    unsigned char pad11[0x17];
    int values[1];            // +28
    unsigned char pad2c[0x134];
};
struct KeyedTable251820 {
    unsigned char pad[0x98];
    unsigned int count;       // +98
    unsigned char pad9c[0x84];
    KeyedEntry251820* entries;   // +120
};

// 0x7100251820
int keyed_value_251820(KeyedTable251820* table, int id, int slot) {
    for (unsigned int i = 0; i < table->count; ++i) {
        if (table->entries[i].key.resolve() == id)
            return table->entries[i].values[slot];
    }
    return -1;
}

struct KeyedEntry2518c4 {
    unsigned char pad[0x10];
    LazyId8 key;              // +10
    unsigned char pad11[0x37];
    int values[1];            // +48
    unsigned char pad4c[0x114];
};
struct KeyedTable2518c4 {
    unsigned char pad[0x98];
    unsigned int count;       // +98
    unsigned char pad9c[0x84];
    KeyedEntry2518c4* entries;   // +120
};

// 0x71002518c4
int keyed_value_2518c4(KeyedTable2518c4* table, int id, int slot) {
    for (unsigned int i = 0; i < table->count; ++i) {
        if (table->entries[i].key.resolve() == id)
            return table->entries[i].values[slot];
    }
    return -1;
}

struct KeyedEntry251968 {
    unsigned char pad[0x10];
    LazyId8 key;              // +10
    unsigned char pad11[0x57];
    int values[1];            // +68
    unsigned char pad6c[0xf4];
};
struct KeyedTable251968 {
    unsigned char pad[0x98];
    unsigned int count;       // +98
    unsigned char pad9c[0x84];
    KeyedEntry251968* entries;   // +120
};

// 0x7100251968
int keyed_value_251968(KeyedTable251968* table, int id, int slot) {
    for (unsigned int i = 0; i < table->count; ++i) {
        if (table->entries[i].key.resolve() == id)
            return table->entries[i].values[slot];
    }
    return -1;
}
