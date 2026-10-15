// Mid-sized game-object helpers (0x7100200318-0x71002054cc): stream loops over fixed tables, table
// copies, capped values, board offsets and grid lookups. Names are descriptive placeholders;
// addresses are in the comments. Status: matching/README.md.

extern "C" void* memcpy(void* dest, const void* source, unsigned long size);

struct Stream1fbf44;
void transfer_1fbf44(Stream1fbf44* stream, void* data, int size);          // 0x71001fbf44

struct Record2014 {
    unsigned char current[0x30]; // +00
    unsigned char saved[0x30];   // +30
    unsigned char pad60[0x28];
};
struct Records2014 {
    unsigned char pad[0x41c8];
    Record2014 records[0x28]; // +41c8
};

// 0x71002014a4
unsigned char transfer_records_2014a4(Records2014* object, Stream1fbf44* stream) {
    for (int i = 0; i < 0x28; ++i)
        transfer_1fbf44(stream, object->records[i].saved, 0x30);
    return 1;
}

// 0x71002014f4
void save_records_2014f4(Records2014* object) {
    for (int i = 0; i < 0x28; ++i)
        memcpy(object->records[i].saved, object->records[i].current, 0x30);
}

// 0x7100201544
void restore_records_201544(Records2014* object) {
    for (int i = 0; i < 0x28; ++i)
        memcpy(object->records[i].current, object->records[i].saved, 0x30);
}

struct Limits20b184;
Limits20b184* load_global_20acb0();                                         // 0x710020acb0
unsigned int limit_20b184(Limits20b184* limits, int kind);                  // 0x710020b184

struct Capped200318 {
    unsigned char pad[0x18];
    unsigned int value;       // +18
};

// 0x7100200318
void set_capped_200318(Capped200318* object, unsigned int value) {
    unsigned int limit = limit_20b184(load_global_20acb0(), 0xfe);
    object->value = limit >= value ? value : limit;
}

struct Board2041 {
    unsigned char pad[0x1a19];
    signed char row;          // +1a19
    signed char column;       // +1a1a
    unsigned char pad1a1b[0xcd9];
    unsigned char shifted;    // +26f4
};

// 0x7100204174
unsigned char shift_board_204174(Board2041* board, unsigned char amount) {
    signed char* column = &board->column;
    int new_column = *column + amount;
    if (static_cast<unsigned int>(new_column) <= 0xe) {
        signed char* row = &board->row;
        int old_row = *row;
        if (static_cast<unsigned int>(old_row + amount) <= 0xf) {
            *column = new_column;
            *row = static_cast<unsigned char>(old_row) + amount;
            return 1;
        }
        return 0;
    }
    return 0;
}

// 0x71002041d0
void shift_board_once_2041d0(Board2041* board) {
    unsigned char* shifted = &board->shifted;
    if (*shifted)
        return;
    signed char* column = &board->column;
    int new_column = *column + 2;
    if (static_cast<unsigned int>(new_column) <= 0xe) {
        signed char* row = &board->row;
        int old_row = *row;
        if (static_cast<unsigned int>(old_row + 2) <= 0xf) {
            *column = new_column;
            *row = static_cast<unsigned char>(old_row) + 2;
        }
    }
    *shifted = 1;
}

struct Grid205420 {
    unsigned char base[7][4];   // +00
    unsigned char pad1c[0x38];
    unsigned char alt[7][4];    // +54
};

// 0x7100205420
unsigned char grid_205420(Grid205420* grid, int column, int row, unsigned char any, unsigned char alt) {
    bool allowed = (row | any) != 0;
    if (static_cast<unsigned int>(column) <= 3 && static_cast<unsigned int>(row) <= 6 && allowed) {
        if (alt)
            return grid->alt[row][column];
        return grid->base[row][column];
    }
    return 0;
}

struct Grid205474 {
    unsigned char pad[0x1c];
    unsigned char base[7][3];   // +1c
    unsigned char pad31[0x3f];
    unsigned char alt[7][3];    // +70
};

// 0x7100205474
unsigned char grid_205474(Grid205474* grid, int column, int row, unsigned char any, unsigned char alt) {
    bool allowed = (row | any) != 0;
    if (static_cast<unsigned int>(column) <= 2 && static_cast<unsigned int>(row) <= 6 && allowed) {
        if (alt)
            return grid->alt[row][column];
        return grid->base[row][column];
    }
    return 0;
}

struct Grid2054cc {
    unsigned char pad[0x31];
    unsigned char cells[7][3];  // +31
};

// 0x71002054cc
unsigned char grid_2054cc(Grid2054cc* grid, int column, int row, unsigned char any) {
    bool allowed = (row | any) != 0;
    if (static_cast<unsigned int>(column) <= 2 && static_cast<unsigned int>(row) <= 6 && allowed)
        return grid->cells[row][column];
    return 0;
}
