// Game-data accessors near the item table (0x71001fe6b0-0x7100200e94), in the shape of
// ItemTable::weapon_of in misc/accessors.cpp. Names are descriptive placeholders; addresses are in
// the comments. Status: matching/README.md.

struct ItemEntryLevels {
    int state;                // +00
    short level;              // +04
    signed char rank;         // +06
    unsigned char pad7;
};
struct ItemLevels {
    ItemEntryLevels entries[0x2e4];
};

// 0x71001ff170
int item_level_1ff170(ItemLevels* table, int item) {
    int level = table->entries[item].level;
    return static_cast<unsigned int>(level) < 0x64 && static_cast<unsigned int>(item) < 0x2e4 ? level : -1;
}

// 0x71001ff18c
int item_level_1ff18c(ItemLevels* table, int item) {
    int level = table->entries[item].level;
    return static_cast<unsigned int>(level) < 0x64 && static_cast<unsigned int>(item) < 0x2e4 ? level : -1;
}

// 0x71001ff1a8
int item_level_1ff1a8(ItemLevels* table, int item) {
    int level = table->entries[item].level;
    return static_cast<unsigned int>(level) < 0x64 && static_cast<unsigned int>(item) < 0x2e4 ? level : -1;
}

// 0x71001ff1e0
int item_level_1ff1e0(ItemLevels* table, int item) {
    int level = table->entries[item].level;
    return static_cast<unsigned int>(level) < 0x64 && static_cast<unsigned int>(item) < 0x2e4 ? level : -1;
}

// 0x71001ff218
int item_level_1ff218(ItemLevels* table, int item) {
    int level = table->entries[item].level;
    return static_cast<unsigned int>(level) < 0x64 && static_cast<unsigned int>(item) < 0x2e4 ? level : -1;
}

// 0x71001ff1fc
int item_rank_1ff1fc(ItemLevels* table, int item) {
    int rank = table->entries[item].rank;
    return static_cast<unsigned int>(rank) < 0x24 && static_cast<unsigned int>(item) < 0x2e4 ? rank : -1;
}

// 0x71001ff234
int item_short_1ff234(ItemLevels* table, int item) {
    if (static_cast<unsigned int>(item) <= 0x2e3) {
        short level = table->entries[item].level;
        return static_cast<unsigned short>(level) < 0x80 ? level : -1;
    }
    return -1;
}

struct PairIds1fe6b0 {
    unsigned char pad[0xe];
    short ids[2];             // +0e
};

// 0x71001fe6b0
int pair_id_1fe6b0(PairIds1fe6b0* object, unsigned int index) {
    if (index <= 1)
        return object->ids[index];
    return -1;
}

struct Triple1fe7 {
    short values[3];
};
struct Grid1fe724 {
    unsigned char pad[0x52];
    Triple1fe7 rows[0x1f];    // +52
};
struct Grid1fe75c {
    unsigned char pad[0x10c];
    unsigned short rows[0x1f][3]; // +10c
};

// 0x71001fe724
int grid_id_1fe724(Grid1fe724* grid, int row, unsigned int column) {
    int result = -1;
    if (static_cast<unsigned int>(row) <= 0x1e && column <= 2) {
        short id = grid->rows[row].values[column];
        result = static_cast<unsigned short>(id) < 0x80 ? id : -1;
    }
    return result;
}

// 0x71001fe75c
unsigned short grid_value_1fe75c(Grid1fe75c* grid, int row, unsigned int column) {
    unsigned short result = 0;
    if (static_cast<unsigned int>(row) <= 0x1e && column <= 2)
        result = grid->rows[row][column];
    return result;
}

struct Counted1feaf0 {
    unsigned char pad[4];
    int values[4];            // +04
    unsigned int count;       // +14
};

// 0x71001feaf0
int counted_value_1feaf0(Counted1feaf0* object, unsigned int index) {
    if (index <= 3) {
        if (object->count >= index)
            return object->values[index];
        return -1;
    }
    return -1;
}

struct Bytes1ff90c {
    unsigned char pad[0x42];
    signed char values[0x64]; // +42
};

// 0x71001ff90c
int byte_1ff90c(Bytes1ff90c* object, int index) {
    int result = 0;
    if (index >= 0 && static_cast<unsigned int>(index) <= 0x63)
        result = object->values[index];
    return result;
}

struct Flags1ff9e8 {
    unsigned char pad[0x10];
    unsigned short flags;     // +10
};

// 0x71001ff9e8
unsigned char flag_low_1ff9e8(Flags1ff9e8* object) {
    return *reinterpret_cast<unsigned char*>(&object->flags) & 1;
}

// 0x71001ff9f4
unsigned int flag_mixed_1ff9f4(Flags1ff9e8* object) {
    unsigned short flags = object->flags;
    return flags & 1 ? 1 : (flags >> 2) & 1;
}

// 0x71001ffa0c
unsigned int flag_bit2_1ffa0c(Flags1ff9e8* object) {
    return (object->flags >> 2) & 1;
}

struct Bits1ffae4 {
    unsigned char pad[0xa];
    unsigned short bits[3];   // +0a
};

// 0x71001ffae4
unsigned char has_bit_1ffae4(Bits1ffae4* object, unsigned int id) {
    if (id <= 0x23)
        return (object->bits[id >> 4] & (1 << (id & 0xf))) != 0;
    return 0;
}

struct ByteBits1ffb30 {
    unsigned char pad[0x1e];
    unsigned char bits[1];    // +1e
};

// 0x71001ffb30
void set_bit_1ffb30(ByteBits1ffb30* set, unsigned int id, unsigned char on) {
    if (id > 5)
        return;
    if (on)
        set->bits[id >> 3] |= 1 << (id & 7);
    else
        set->bits[id >> 3] &= ~(1 << (id & 7));
}

struct Halves200a7c {
    unsigned char pad[0x28];
    unsigned char first[0x30];  // +28
    unsigned char second[0x30]; // +58
};

// 0x7100200a7c
void* half_200a7c(Halves200a7c* object, unsigned char second) {
    return !second ? object->first : object->second;
}

struct Kind2005bc {
    unsigned char pad[2];
    unsigned short flags;     // +02
};

// 0x71002005bc
unsigned int kind_2005bc(Kind2005bc* object) {
    unsigned short flags = object->flags;
    return flags & 2 ? 3 : (flags & 1) + 1;
}

struct Board200e38 {
    int cells[0x28][0x24];
};

// 0x7100200e38
unsigned char cell_empty_200e38(Board200e38* board, int row, int column) {
    unsigned char result = 0;
    if (static_cast<unsigned int>(row) <= 0x27 && static_cast<unsigned int>(column) <= 0x23)
        result = board->cells[row][column] == 0;
    return result;
}

// 0x7100200e68
unsigned char cell_known_200e68(Board200e38* board, int row, int column) {
    unsigned char result = 0;
    if (static_cast<unsigned int>(row) <= 0x27 && static_cast<unsigned int>(column) <= 0x23)
        result = board->cells[row][column] != -1;
    return result;
}

struct Item1ff974 {
    unsigned int id;          // +00
    unsigned char pad4[0x3a];
    unsigned short flags;     // +3e
};
struct Slot1ff974 {
    unsigned int kind;        // +00
    unsigned char pad4[4];
    Item1ff974* item;         // +08
};

// 0x71001ff974
unsigned char slot_flag_1ff974(Slot1ff974* slot) {
    if (slot->kind <= 0x27) {
        Item1ff974* item = slot->item;
        if (item) {
            if (item->id <= 0x63)
                return item->flags & 1;
            return 0;
        }
        return 0;
    }
    return 0;
}

struct Bits1ffb78 {
    unsigned short bits[5];
};

// 0x71001ffb78
unsigned char has_bit_1ffb78(Bits1ffb78* object, unsigned int id) {
    if (id <= 0x4a)
        return (object->bits[id >> 4] & (1 << (id & 0xf))) != 0;
    return 0;
}

struct Capped20023c {
    unsigned char pad[0x16];
    unsigned short value;     // +16
};

// 0x710020023c
void set_capped_20023c(Capped20023c* object, unsigned int value) {
    if (value <= 0x5dc0)
        object->value = value;
}

struct Byte200294 {
    unsigned char pad[0x20];
    unsigned char value;      // +20
};

// 0x7100200294
unsigned int clamped_byte_200294(Byte200294* object) {
    unsigned int value = object->value;
    return value == 0xff ? 0xfe : value;
}

struct Ids2003a4 {
    unsigned char pad[0x1c];
    short ids[1];             // +1c
};

// 0x71002003a4
int first_id_2003a4(Ids2003a4* object, int slot) {
    if (slot)
        return -1;
    short id = object->ids[0];
    return static_cast<unsigned short>(id) < 0x406 ? id : -1;
}

// 0x71002003c4
void set_first_id_2003c4(Ids2003a4* object, unsigned int slot, int id) {
    if (slot < 1u && (static_cast<unsigned int>(id) < 0x406 || id == -1))
        object->ids[slot] = id;
}

struct Entries216f88;
struct Entry216f88;
struct Field215da4;
void* load_global_216d48();                                                 // 0x7100216d48
Entry216f88* find_216f88(Entries216f88* table, int index);                  // 0x7100216f88
int get_215da4(Field215da4* object);                                        // 0x7100215da4

// 0x71002003fc
int first_value_2003fc(Ids2003a4* object, int slot) {
    if (slot)
        return -1;
    int id = object->ids[0];
    if (static_cast<unsigned int>(id) <= 0x405) {
        Entry216f88* entry = find_216f88(static_cast<Entries216f88*>(load_global_216d48()), id);
        return get_215da4(reinterpret_cast<Field215da4*>(entry));
    }
    return -1;
}