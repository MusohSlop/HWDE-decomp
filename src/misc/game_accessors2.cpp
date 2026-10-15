// More game-object and unit-record accessors (0x71002045f0-0x71002062c0). Names are descriptive
// placeholders; addresses are in the comments. Status: matching/README.md.

extern "C" void* memcpy(void* dest, const void* source, unsigned long size);

struct Picks2045 {
    unsigned char pad[0x26a8];
    int picks[3];             // +26a8
    unsigned char flags[0x14]; // +26b4
    unsigned char pad26c8[8];
    unsigned char choice_a;   // +26d0
    unsigned char choice_b;   // +26d1
};

// 0x71002045f0
void set_choice_a_2045f0(Picks2045* object, unsigned char value) {
    object->choice_a = value;
}

// 0x7100204608
void set_choice_b_204608(Picks2045* object, unsigned char value) {
    object->choice_b = value;
}

// 0x71002046a8
void add_pick_2046a8(Picks2045* object, int pick) {
    int* slot;
    if (object->picks[0] == -1)
        slot = &object->picks[0];
    else if (object->picks[1] == -1)
        slot = &object->picks[1];
    else if (object->picks[2] == -1)
        slot = &object->picks[2];
    else
        return;
    *slot = pick;
}

// 0x71002046e4
int pick_2046e4(Picks2045* object, int index) {
    return object->picks[static_cast<unsigned int>(index) > 2 ? 0 : index];
}

// 0x71002046fc
unsigned char flag_2046fc(Picks2045* object, unsigned char index) {
    return object->flags[index];
}

// 0x7100204aa0
int save_block_size_204aa0() {
    return 0x32dd0;
}

struct SaveBlock204c {
    unsigned char live[0x32dd0];
    unsigned char backup[0x27f8]; // +32dd0
};

// 0x7100204c5c
void backup_save_204c5c(SaveBlock204c* save) {
    if (save)
        memcpy(save->backup, save, 0x27f8);
}

// 0x7100204c80
void restore_save_204c80(SaveBlock204c* save) {
    if (save)
        memcpy(save, save->backup, 0x27f8);
}

struct Words2057b0 {
    unsigned char pad[0x6ac];
    int values[0x10];         // +6ac
};

// 0x71002057b0
int value_2057b0(Words2057b0* object, unsigned int index) {
    if (index <= 0xf)
        return object->values[index];
    return 0;
}

struct Row206034 {
    unsigned char data[0xc0];
};

// 0x7100206034
Row206034* row_206034(Row206034* rows, int index) {
    return &rows[index];
}

struct Unit2060 {
    unsigned char pad[0x15];
    unsigned char level;      // +15
    unsigned char pad16[0x1e];
    unsigned char slots[5];   // +34
    unsigned char pad39[0x2d];
    unsigned char grade;      // +66
};

// 0x7100206040
unsigned char has_slot_206040(Unit2060* unit, unsigned char kind) {
    if (unit->slots[0] == kind || unit->slots[1] == kind || unit->slots[2] == kind || unit->slots[3] == kind)
        return 1;
    return unit->slots[4] == kind;
}

// 0x71002060c0
void set_slot_2060c0(Unit2060* unit, unsigned char kind, int index) {
    unit->slots[index] = kind;
}

// 0x7100206190
void add_level_206190(Unit2060* unit, int amount) {
    int level = unit->level + amount;
    unit->level = level < 0x63 ? level : 0x63;
}

// 0x710020626c
void update_grade_20626c(Unit2060* unit) {
    unsigned char level = unit->level;
    unit->grade = level > 0x45 ? 4 : level > 0x27 ? 3 : level > 9 ? 2 : 1;
}

// 0x710020629c
int grade_for_level_20629c(Unit2060* unit, unsigned char level) {
    if (level > 0x45)
        return 4;
    if (level > 0x27)
        return 3;
    return level > 9 ? 2 : 1;
}
