// Game-object accessors after the item table (0x7100201da0-0x71002043f0). Names are descriptive
// placeholders; addresses are in the comments. Status: matching/README.md.

struct Row201da0 {
    unsigned char pad[8];
    short value;              // +08
    unsigned char pad0a[0x3e];
};

// 0x7100201da0
unsigned char row_in_band_201da0(Row201da0* rows, int row) {
    if (static_cast<unsigned int>(row) <= 0x20) {
        short value = rows[row].value;
        return value > 0xc7 ? value < 0xe9 : 0;
    }
    return 0;
}

// 0x7100201e4c
int band_index_201e4c(int value) {
    unsigned int index = value - 0xc8;
    return index < 0x21 ? static_cast<int>(index) : -1;
}

struct Key2020d4 {
    long id;                  // +00
    unsigned char flag;       // +08
};

// 0x71002020d4
void clear_key_2020d4(Key2020d4* key) {
    key->id = 0;
    key->flag = 0;
}

// 0x71002020e0
unsigned char same_key_2020e0(const Key2020d4* a, const Key2020d4* b) {
    if (a->id != b->id)
        return 0;
    if (a->flag != b->flag)
        return 0;
    return a->flag == 0;
}

struct Short202128 {
    unsigned short value;
};

// 0x7100202128
void set_value_202128(Short202128* object, int a, int b, int c, unsigned short value) {
    object->value = value;
}

struct Pending2026b8 {
    unsigned char pad[0x26a8];
    long target;              // +26a8
    int index;                // +26b0
};

// 0x71002026b8
void reset_pending_2026b8(Pending2026b8* object) {
    object->index = -1;
    object->target = -1;
}

struct Time2026e4 {
    unsigned int value;
};

// 0x71002026e4
void set_time_2026e4(Time2026e4* object, unsigned int value) {
    if (value <= 0x36ee7f)
        object->value = value;
}

struct Ptrs2028b4 {
    void* items[0x20];
};

// 0x71002028b4
void* item_2028b4(Ptrs2028b4* object, unsigned int index) {
    if (index <= 0x1f)
        return object->items[index];
    return nullptr;
}

struct Flags202e74 {
    unsigned char pad[0x130];
    unsigned char flags[8];   // +130
};

// 0x7100202e74
unsigned char flag_202e74(Flags202e74* object, int index) {
    if (static_cast<unsigned int>(index) < 8)
        return 1;
    if (index == -1)
        return object->flags[0];
    return 0;
}

// 0x7100202e9c
void set_flag_202e9c(Flags202e74* object, unsigned int index, unsigned char value) {
    if (index <= 7)
        object->flags[index] = value;
}

struct Ids203504 {
    unsigned char pad[0x14c];
    short first[4];           // +14c
    short second[4];          // +154
};

// 0x7100203504
int first_id_203504(Ids203504* object, int slot) {
    if (static_cast<unsigned int>(slot) <= 3) {
        short id = object->first[slot];
        return static_cast<unsigned short>(id) < 0x64 ? id : -1;
    }
    return -1;
}

// 0x71002035ac
int second_id_2035ac(Ids203504* object, int slot) {
    if (static_cast<unsigned int>(slot) <= 3) {
        short id = object->second[slot];
        return static_cast<unsigned short>(id) < 0x64 ? id : -1;
    }
    return -1;
}

struct FarIds203580 {
    unsigned char pad[0x1bb80];
    short ids[4];             // +1bb80
};

// 0x7100203580
void set_far_id_203580(FarIds203580* object, int slot, int id) {
    if (static_cast<unsigned int>(slot) > 3)
        return;
    if (static_cast<unsigned int>(id) >= 0x64 && id != -1)
        return;
    object->ids[slot] = id;
}

struct Counts203b10 {
    unsigned char pad[0x185a];
    unsigned short counts[0x80]; // +185a
};

// 0x7100203b10
unsigned short count_203b10(Counts203b10* object, int index) {
    if (static_cast<unsigned int>(index) <= 0x7f)
        return object->counts[index];
    return 0;
}

// 0x7100203b2c
void set_count_203b2c(Counts203b10* object, int index, unsigned short count) {
    if (static_cast<unsigned int>(index) <= 0x7f)
        object->counts[index] = count > 0x3e7 ? 0x3e7 : count;
}

struct Stage203c80 {
    unsigned char pad[0x161];
    signed char stage;        // +161
};

// 0x7100203c80
void set_stage_203c80(Stage203c80* object, int stage) {
    if (static_cast<unsigned int>(stage + 1) <= 5)
        object->stage = stage;
}

struct Save203de4 {
    unsigned char pad[0x32dd0];
    unsigned char mirror[1];  // +32dd0
};

// 0x7100203de4
void* save_block_203de4(Save203de4* save, unsigned char mirrored) {
    if (mirrored)
        return save->mirror;
    return save;
}

struct Bytes2041 {
    unsigned char pad[0x1a18];
    unsigned char difficulty; // +1a18
    unsigned char pad1a19[0xc9b];
    unsigned char flags[0x100]; // +26b4
};

// 0x7100204150
void set_difficulty_204150(Bytes2041* object, unsigned char difficulty) {
    object->difficulty = difficulty > 0xe ? 0 : difficulty;
}

// 0x71002042a8
void set_byte_flag_2042a8(Bytes2041* object, unsigned char index, unsigned char value) {
    object->flags[index] = value;
}

struct Stock2043 {
    unsigned char pad[0x237c];
    unsigned char stock[0xf0]; // +237c
};

// 0x71002043a8
unsigned char stock_2043a8(Stock2043* object, int index) {
    return object->stock[index > 0xef ? 0 : index];
}

// 0x71002043c4
void use_stock_2043c4(Stock2043* object, int index, unsigned char amount) {
    unsigned char& stock = object->stock[index > 0xef ? 0 : index];
    unsigned char have = stock;
    stock = have - (have < amount ? have : amount);
}

// 0x71002043f0
int stocked_kinds_2043f0(Stock2043* object) {
    int count = 0;
    for (int i = 0; i < 0xf0; ++i) {
        if (object->stock[i])
            ++count;
    }
    return count;
}
