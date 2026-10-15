// Banked table lookups (0x71002131f8-0x710021357c): each reads one column of an entry from a banked
// table, where bank 1 continues past id 1000 in extension chunks of 1000 entries. They differ only in
// the column and the value type; functions are named after their address. Status: matching/README.md.

struct ChunkTable {
    unsigned char data[0x10];
};
short chunk_short_218eb0(ChunkTable* chunk, unsigned int id, int column);         // 0x7100218eb0
signed char chunk_byte_218fc0(ChunkTable* chunk, unsigned int id, int column);    // 0x7100218fc0

struct BankedTable {
    unsigned char pad[0x10];
    ChunkTable banks[2];      // +10
    unsigned char loaded[2];  // +30
    unsigned char pad32[0x2e];
    ChunkTable extra[1];      // +60
};

// 0x71002131f8: column 3
int banked_short_2131f8(BankedTable* table, int bank, unsigned int id) {
    short value;
    if (bank == 1) {
        if (id >= 1000 && table->loaded[1]) {
            value = chunk_short_218eb0(&table->extra[id / 1000 - 1], id % 1000, 3);
            return value;
        }
    } else if (bank > 1) {
        value = -1;
        return value;
    }
    unsigned int index = bank;
    if (table->loaded[index])
        value = chunk_short_218eb0(&table->banks[index], id, 3);
    else
        value = -1;
    return value;
}

// 0x7100213284: column 6
int banked_byte_213284(BankedTable* table, int bank, unsigned int id) {
    signed char value;
    if (bank == 1) {
        if (id >= 1000 && table->loaded[1]) {
            value = chunk_byte_218fc0(&table->extra[id / 1000 - 1], id % 1000, 6);
            return value;
        }
    } else if (bank > 1) {
        value = -1;
        return value;
    }
    unsigned int index = bank;
    if (table->loaded[index])
        value = chunk_byte_218fc0(&table->banks[index], id, 6);
    else
        value = -1;
    return value;
}

// 0x7100213310: column 7
int banked_byte_213310(BankedTable* table, int bank, unsigned int id) {
    signed char value;
    if (bank == 1) {
        if (id >= 1000 && table->loaded[1]) {
            value = chunk_byte_218fc0(&table->extra[id / 1000 - 1], id % 1000, 7);
            return value;
        }
    } else if (bank > 1) {
        value = -1;
        return value;
    }
    unsigned int index = bank;
    if (table->loaded[index])
        value = chunk_byte_218fc0(&table->banks[index], id, 7);
    else
        value = -1;
    return value;
}

// 0x710021339c: column 4
signed char banked_byte_21339c(BankedTable* table, int bank, unsigned int id) {
    if (bank == 1) {
        if (id >= 1000 && table->loaded[1])
            return chunk_byte_218fc0(&table->extra[id / 1000 - 1], id % 1000, 4);
    } else if (bank > 1) {
        return -1;
    }
    unsigned int index = bank;
    if (!table->loaded[index])
        return -1;
    return chunk_byte_218fc0(&table->banks[index], id, 4);
}

// 0x7100213414: column 5
signed char banked_byte_213414(BankedTable* table, int bank, unsigned int id) {
    if (bank == 1) {
        if (id >= 1000 && table->loaded[1])
            return chunk_byte_218fc0(&table->extra[id / 1000 - 1], id % 1000, 5);
    } else if (bank > 1) {
        return -1;
    }
    unsigned int index = bank;
    if (!table->loaded[index])
        return -1;
    return chunk_byte_218fc0(&table->banks[index], id, 5);
}

// 0x710021348c: column 1
short banked_short_21348c(BankedTable* table, int bank, unsigned int id) {
    if (bank == 1) {
        if (id >= 1000 && table->loaded[1])
            return chunk_short_218eb0(&table->extra[id / 1000 - 1], id % 1000, 1);
    } else if (bank > 1) {
        return -1;
    }
    unsigned int index = bank;
    if (!table->loaded[index])
        return -1;
    return chunk_short_218eb0(&table->banks[index], id, 1);
}

// 0x7100213504: column 2
short banked_short_213504(BankedTable* table, int bank, unsigned int id) {
    if (bank == 1) {
        if (id >= 1000 && table->loaded[1])
            return chunk_short_218eb0(&table->extra[id / 1000 - 1], id % 1000, 2);
    } else if (bank > 1) {
        return -1;
    }
    unsigned int index = bank;
    if (!table->loaded[index])
        return -1;
    return chunk_short_218eb0(&table->banks[index], id, 2);
}

int chunk_value_218da0(ChunkTable* chunk, unsigned int id, int column);         // 0x7100218da0
const char* chunk_text_218d18(ChunkTable* chunk, unsigned int id, int variant);  // 0x7100218d18
extern const char kEmptyText[] __attribute__((visibility("hidden")));           // 0x7100740512

// 0x710021357c: column 0
int banked_value_21357c(BankedTable* table, int bank, unsigned int id) {
    if (bank == 1) {
        if (id >= 1000 && table->loaded[1])
            return chunk_value_218da0(&table->extra[id / 1000 - 1], id % 1000, 0);
    } else if (bank > 1) {
        return -1;
    }
    unsigned int index = bank;
    if (!table->loaded[index])
        return -1;
    return chunk_value_218da0(&table->banks[index], id, 0);
}

// 0x71002135f0: text variant 8
const char* banked_text_2135f0(BankedTable* table, int bank, unsigned int id) {
    if (bank == 1) {
        if (id >= 1000 && table->loaded[1])
            return chunk_text_218d18(&table->extra[id / 1000 - 1], id % 1000, 8);
    } else if (bank > 1) {
        return kEmptyText;
    }
    unsigned int index = bank;
    if (!table->loaded[index])
        return kEmptyText;
    return chunk_text_218d18(&table->banks[index], id, 8);
}
