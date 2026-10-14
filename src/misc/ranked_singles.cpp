// Single functions from tools/rank_targets.py (small leaves that matched code calls). Names are
// descriptive placeholders; addresses are in the comments. Status: matching/README.md.

struct SlotTable426ab4 {
    unsigned char pad[0x40];
    void* items[0x400];       // +40
};

// 0x7100426ab4
void* slot_item_426ab4(SlotTable426ab4* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x3ff)
        return table->items[index];
    return nullptr;
}

struct FlagWord387784 {
    unsigned char pad[0xc];
    unsigned int flags;       // +0c
};

// 0x7100387784
void set_flags_387784(FlagWord387784* object, unsigned int bits, unsigned char on) {
    unsigned int flags = object->flags;
    unsigned int cleared = flags & ~bits;
    unsigned int raised = flags | bits;
    object->flags = on == 0 ? cleared : raised;
}

struct PairIds215150 {
    unsigned char pad[0xe];
    short ids[2];             // +0e
};

// 0x7100215150
int pair_id_215150(PairIds215150* object, unsigned int index) {
    if (index <= 1)
        return object->ids[index];
    return -1;
}

// Vtable through the GOT slot at 0x7100c2b290.
class Handle39cc78 {
public:
    Handle39cc78();
    virtual ~Handle39cc78();

    int id;                   // +08
};

// 0x710039cc78
Handle39cc78::Handle39cc78() : id(-1) {}

struct Options_c2b710;
// Reached through the GOT slot at 0x7100c2b710.
extern Options_c2b710* gOptions_c2b710;
void apply_option_3fbec4(Options_c2b710* options, int value, int flags);   // 0x71003fbec4

// 0x71003fe230
void apply_option_3fe230(int value) {
    if (gOptions_c2b710)
        apply_option_3fbec4(gOptions_c2b710, value, 0);
}

struct OptionBlock_c2b710 {
    unsigned char pad[0xf14];
    int selection;            // +f14
};
// Reached through the GOT slot at 0x7100c2b710.
extern OptionBlock_c2b710* gOptionBlock_c2b710;
void notify_option_3fa0e0(int id);                                          // 0x71003fa0e0

// 0x71003ff140
void reset_selection_3ff140() {
    if (gOptionBlock_c2b710) {
        gOptionBlock_c2b710->selection = -1;
        notify_option_3fa0e0(0xc8);
    }
}

struct Span53d360 {
    unsigned char pad[8];
    unsigned char* end;       // +08
    long tag;                 // +10
    long position;            // +18
};

// 0x710053d360
unsigned char open_span_53d360(Span53d360* span, unsigned char* data, long size, long tag) {
    if (!data)
        return 0;
    span->end = data + size;
    span->tag = tag;
    span->position = 0;
    return 1;
}

struct Choice20ff60 {
    int alternate;            // +00
    unsigned char pad4[0x6fb50];
    unsigned char primary[0x7cb90]; // +6fb54
    unsigned char secondary[1];     // +ec6e4
};

// 0x710020ff60
void* choice_20ff60(Choice20ff60* object) {
    return object->alternate == 0 ? object->primary : object->secondary;
}

struct Record446054 {
    unsigned char data[0x1a0];
};
struct Records446054 {
    unsigned char pad[0x18];
    Record446054* records;    // +18
    unsigned char pad20[0x60];
    int count;                // +80
};

// 0x7100446054
Record446054* record_446054(Records446054* table, int index) {
    Record446054* record = nullptr;
    if (index >= 0 && table->records && index < table->count)
        record = &table->records[index];
    return record;
}

struct UnitTable_c21690 {
    unsigned char pad[0x138];
    void* units[0x6d7];       // +138
};
// Reached through the GOT slot at 0x7100c21690.
extern UnitTable_c21690* gUnitTable_c21690;
void release_unit_3141c(void* unit, int mode);                              // 0x710003141c

// 0x710003f308
void release_unit_3f308(short id) {
    release_unit_3141c(static_cast<unsigned short>(id) <= 0x6d6 ? gUnitTable_c21690->units[id] : nullptr, 1);
}

// 0x710003f344
void release_unit_3f344(short id) {
    release_unit_3141c(static_cast<unsigned short>(id) <= 0x6d6 ? gUnitTable_c21690->units[id] : nullptr, 1);
}

struct Row2042bc {
    unsigned char data[0xa0];
};
struct Rows2042bc {
    unsigned char pad[0x1a1c];
    Row2042bc rows[0xf];      // +1a1c
};

// 0x71002042bc
Row2042bc* row_2042bc(Rows2042bc* object, unsigned char index) {
    return &object->rows[index > 0xe ? 0 : index];
}

struct Mode3df5e4 {
    unsigned char pad[0x3340];
    int mode;                 // +3340
};
void apply_mode_3df768(Mode3df5e4* object);                                 // 0x71003df768

// 0x71003df5e4
void set_mode_3df5e4(Mode3df5e4* object, unsigned char enabled, unsigned char strong) {
    object->mode = enabled ? (strong ? 2 : 1) : 0;
    apply_mode_3df768(object);
}

struct FarField1ec94c;
int far_field_1ec94c(FarField1ec94c* object);                               // 0x71001ec94c
struct Block3890bc {
    unsigned char pad[0xb8];
    unsigned char field[0x16820 - 0xb8]; // +b8
};
struct Blocks3890bc {
    Block3890bc blocks[1];
};

// 0x71003890bc
unsigned char block_active_3890bc(Blocks3890bc* object) {
    unsigned int index = *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(object) + 0x2d0f8);
    return far_field_1ec94c(reinterpret_cast<FarField1ec94c*>(object->blocks[index].field)) != 0;
}

struct StagePair {
    int first;
    int second;
};
extern const StagePair kStagePairs_7e2060[] __attribute__((visibility("hidden"))); // 0x71007e2060
extern unsigned int gStageIndex_ca31b8 __attribute__((visibility("hidden")));      // 0x7100ca31b8

// 0x71003cc930
int stage_first_3cc930() {
    return kStagePairs_7e2060[gStageIndex_ca31b8].first;
}

// 0x71003cc94c
int stage_second_3cc94c() {
    return kStagePairs_7e2060[gStageIndex_ca31b8].second;
}
