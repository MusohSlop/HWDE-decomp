// Pairs of tiny accessors found by tools/family_scan.py --immediates (two copies of each shape, in
// different classes): counters, capped and range-checked stores and reads, flag tests, clears,
// global reads and writes, entry addresses, text lookups, chunk sets, copies, node draws, guarded
// calls and child-field reads. Each pair differs only in offsets, limits, globals and callees; types
// and functions are named after their address. Status: matching/README.md.

struct Counter794d4 {
    unsigned char pad[0x84];
    int count;                // +84
};

// 0x71000794d4
void count_up_794d4(Counter794d4* object) {
    ++object->count;
}

struct Counter14a7c8 {
    unsigned char pad[0x48];
    int count;                // +48
};

// 0x710014a7c8
void count_up_14a7c8(Counter14a7c8* object) {
    ++object->count;
}

struct Capped86668 {
    unsigned char pad[0x45c];
    int value;                // +45c
};

// 0x7100086668
void set_capped_86668(Capped86668* object, int value) {
    object->value = static_cast<unsigned int>(value) < 0x3c ? value : -1;
}

struct Capped216cc0 {
    unsigned char pad[0x28];
    int value;                // +28
};

// 0x7100216cc0
void set_capped_216cc0(Capped216cc0* object, int value) {
    object->value = static_cast<unsigned int>(value) < 0x406 ? value : -1;
}

struct Zeroed133d40 {
    unsigned char pad[0x112];
    unsigned short value;     // +112
};

// 0x7100133d40
unsigned char is_zero_133d40(Zeroed133d40* object) {
    return object->value == 0;
}

struct Zeroed244978 {
    unsigned char pad[0x18];
    unsigned short value;     // +18
};

// 0x7100244978
unsigned char is_zero_244978(Zeroed244978* object) {
    return object->value == 0;
}

struct Flags165904 {
    unsigned char flags[1];
};

// 0x7100165904
unsigned char flag_at_165904(Flags165904* object, unsigned int index) {
    return object->flags[index] != 0x0;
}

struct Flags4404c4 {
    unsigned char flags[1];
};

// 0x71004404c4
unsigned char flag_at_4404c4(Flags4404c4* object, unsigned int index) {
    return object->flags[index] != 0xff;
}

struct FarInt1ecbc0 {
    unsigned char pad[0x16740];
    int value;                // +16740
};

// 0x71001ecbc0
void clear_far_1ecbc0(FarInt1ecbc0* object) {
    object->value = 0;
}

struct FarInt1ecdec {
    unsigned char pad[0x16760];
    int value;                // +16760
};

// 0x71001ecdec
void clear_far_1ecdec(FarInt1ecdec* object) {
    object->value = 0;
}

struct ShortId200200 {
    unsigned char pad[0x12];
    unsigned short id;        // +12
};

// 0x7100200200
void set_short_id_200200(ShortId200200* object, unsigned int id) {
    if (!(id >> 16))
        object->id = id;
}

struct ShortId200218 {
    unsigned char pad[0x14];
    unsigned short id;        // +14
};

// 0x7100200218
void set_short_id_200218(ShortId200218* object, unsigned int id) {
    if (!(id >> 16))
        object->id = id;
}

struct ItemId2034f4 {
    unsigned char pad[0x14a];
    short id;                 // +14a
};

// 0x71002034f4
void set_item_id_2034f4(ItemId2034f4* object, int id) {
    if (static_cast<unsigned int>(id) <= 0x12b)
        object->id = id;
}

struct ItemId203650 {
    unsigned char pad[0x15c];
    short id;                 // +15c
};

// 0x7100203650
void set_item_id_203650(ItemId203650* object, int id) {
    if (static_cast<unsigned int>(id) <= 0x12b)
        object->id = id;
}

struct Shorts206088 {
    unsigned char pad[0x12];
    unsigned short values[0x100]; // +12
};

// 0x7100206088
unsigned short short_by_key_206088(Shorts206088* object, unsigned char key) {
    return object->values[key];
}

struct Shorts208a08 {
    unsigned char pad[0x10];
    unsigned short values[0x100]; // +10
};

// 0x7100208a08
unsigned short short_by_key_208a08(Shorts208a08* object, unsigned char key) {
    return object->values[key];
}

struct Flagged2dbba4 {
    unsigned char pad[0xd];
    unsigned char enabled;    // +d
};
void flagged_action_3ab83c(Flagged2dbba4* object);                    // 0x71003ab83c

// 0x71002dbba4
void run_if_flagged_2dbba4(Flagged2dbba4* object) {
    if (object->enabled)
        flagged_action_3ab83c(object);
}

struct Flagged3110e8 {
    unsigned char pad[0x22c];
    unsigned char enabled;    // +22c
};
void flagged_action_3110f8(Flagged3110e8* object);                    // 0x71003110f8

// 0x71003110e8
void run_if_flagged_3110e8(Flagged3110e8* object) {
    if (object->enabled)
        flagged_action_3110f8(object);
}

struct FarByte2d5ed4 {
    unsigned char pad[0x7505c];
    unsigned char value;      // +7505c
};

// 0x71002d5ed4
unsigned char far_byte_2d5ed4(FarByte2d5ed4* object) {
    return object->value;
}

struct FarByte38c46c {
    unsigned char pad[0x2e5eaa];
    unsigned char value;      // +2e5eaa
};

// 0x710038c46c
unsigned char far_byte_38c46c(FarByte38c46c* object) {
    return object->value;
}

struct Cleared40e2d0 {
    long a;
    long b;
    long c;
    long d;
    unsigned char pad20[4];
    int e;                    // +24
};

// 0x710040e2d0
void clear_40e2d0(Cleared40e2d0* object) {
    object->e = 0;
    object->c = 0;
    object->d = 0;
    object->a = 0;
    object->b = 0;
}

struct Cleared4718e0 {
    long a;
    long b;
    long c;
    long d;
    int e;                    // +20
};

// 0x71004718e0
void clear_4718e0(Cleared4718e0* object) {
    object->e = 0;
    object->c = 0;
    object->d = 0;
    object->a = 0;
    object->b = 0;
}

struct GlobalRecorddbec {
    unsigned char pad[0xb48];
    int value;                // +b48
};
// Reached through the GOT slot at 0x7100c21698.
extern GlobalRecorddbec* gRecord_c21698;

// 0x710000dbec
int global_field_dbec() {
    return gRecord_c21698->value;
}

struct GlobalRecord389164 {
    unsigned char pad[0x8];
    int value;                // +8
};
// Reached through the GOT slot at 0x7100c22ef8.
extern GlobalRecord389164* gRecord_c22ef8;

// 0x7100389164
int global_field_389164() {
    return gRecord_c22ef8->value;
}

struct Snapshot8162c {
    unsigned char pad[0x448];
    int value;                // +448
};
// Reached through the GOT slot at 0x7100c22250.
extern int gValue_c22250;

// 0x710008162c
void snapshot_8162c(Snapshot8162c* object) {
    object->value = gValue_c22250;
}

struct Snapshot86b48 {
    unsigned char pad[0x164];
    int value;                // +164
};
// Reached through the GOT slot at 0x7100c22280.
extern int gValue_c22280;

// 0x7100086b48
void snapshot_86b48(Snapshot86b48* object) {
    object->value = gValue_c22280;
}

struct Bound133680 {
    unsigned char pad[0x80];
    void* target;             // +80
    unsigned int flags;       // +88
};

// 0x7100133680
void bind_133680(Bound133680* object, void* target) {
    object->target = target;
    object->flags |= 2;
}

struct Bound13f85c {
    unsigned char pad[0x88];
    void* target;             // +88
    unsigned char pad90[0x44];
    unsigned int flags;       // +d4
};

// 0x710013f85c
void bind_13f85c(Bound13f85c* object, void* target) {
    object->target = target;
    object->flags |= 2;
}

struct Cell19cfc0 {
    unsigned char data[0xc];
};
struct Cells19cfc0 {
    unsigned char pad[0x37cc];
    Cell19cfc0 cells[1];   // +37cc
};

// 0x710019cfc0
Cell19cfc0* cell_19cfc0(Cells19cfc0* object, unsigned int index) {
    return &object->cells[index];
}

struct Cell19cfd4 {
    unsigned char data[0xc];
};
struct Cells19cfd4 {
    unsigned char pad[0x3844];
    Cell19cfd4 cells[1];   // +3844
};

// 0x710019cfd4
Cell19cfd4* cell_19cfd4(Cells19cfd4* object, unsigned int index) {
    return &object->cells[index];
}

class TextTable {
public:
    const char* find(int id, int variant);                                  // 0x7100218d18
};

struct Texts1a7ea4 {
    unsigned char pad[0x19b0];
    TextTable table;          // +19b0
};

// 0x71001a7ea4
const char* text_1a7ea4(Texts1a7ea4* object, int id, unsigned int variant) {
    int next = variant < 8 ? variant + 1 : 0;
    return object->table.find(id, next);
}

struct Texts1a7eb8 {
    unsigned char pad[0x19c0];
    TextTable table;          // +19c0
};

// 0x71001a7eb8
const char* text_1a7eb8(Texts1a7eb8* object, int id, unsigned int variant) {
    int next = variant < 8 ? variant + 1 : 0;
    return object->table.find(id, next);
}

struct DataChunk {
    void set(const void* data);                                             // 0x7100218c34

    unsigned char body[0x10];
};

struct Chunks1af4a8 {
    unsigned char pad[0x10];
    DataChunk* chunks;        // +10
};

// 0x71001af4a8
void set_chunk_1af4a8(Chunks1af4a8* object, const void* data, int index) {
    if (data)
        object->chunks[index].set(data);
}

struct Chunks1af4bc {
    unsigned char pad[0x28];
    DataChunk* chunks;        // +28
};

// 0x71001af4bc
void set_chunk_1af4bc(Chunks1af4bc* object, const void* data, int index) {
    if (data)
        object->chunks[index].set(data);
}

struct Plain1d7b14 {
    unsigned char data[0x530];
};

// 0x71001d7b14
void copy_to_1d7b14(const Plain1d7b14* source, Plain1d7b14* dest) {
    *dest = *source;
}

struct Plain533558 {
    unsigned char data[0x48];
};

// 0x7100533558
void copy_to_533558(const Plain533558* source, Plain533558* dest) {
    *dest = *source;
}

class DrawNode {
public:
    void draw(int mode);                                                    // 0x71001e34a0
};

struct NodeHolder1ee650 {
    unsigned char pad[0x2410];
    DrawNode* node;           // +2410
};

// 0x71001ee650
void draw_node_1ee650(NodeHolder1ee650* object) {
    if (object->node)
        object->node->draw(0);
}

struct NodeHolder37bd18 {
    unsigned char pad[0x10];
    DrawNode* node;           // +10
};

// 0x710037bd18
void draw_node_37bd18(NodeHolder37bd18* object) {
    if (object->node)
        object->node->draw(0);
}

// 0x71001f4e94
int offset_index_1f4e94(int index) {
    return static_cast<unsigned int>(index) < 0x7 ? index + 0x1f72 : -1;
}

// 0x71001f5104
int offset_index_1f5104(int index) {
    return static_cast<unsigned int>(index) < 0x2e ? index + 0x2ba6 : -1;
}

struct Row1fef54 {
    unsigned char data[0x18];
};
class RowTable1fef54 {
public:
    Row1fef54* find(int index) {
        return static_cast<unsigned int>(index) < 0x19 ? &rows[index] : nullptr;
    }

    Row1fef54 rows[0x19];
};

// 0x71001fef54
Row1fef54* row_1fef54(RowTable1fef54* table, int index) {
    return table->find(index);
}

struct Row20a4e8 {
    unsigned char data[0x18];
};
class RowTable20a4e8 {
public:
    Row20a4e8* find(int index) {
        return static_cast<unsigned int>(index) < 0xc9 ? &rows[index] : nullptr;
    }

    Row20a4e8 rows[0xc9];
};

// 0x710020a4e8
Row20a4e8* row_20a4e8(RowTable20a4e8* table, int index) {
    return table->find(index);
}

struct Capped16_1ff94c {
    unsigned char pad[0x24];
    unsigned short value;     // +24
};

// 0x71001ff94c
unsigned short capped16_1ff94c(Capped16_1ff94c* object) {
    unsigned short value = object->value;
    return value > 0x5dc0 ? 0x5dc0 : value;
}

struct Capped16_200228 {
    unsigned char pad[0x16];
    unsigned short value;     // +16
};

// 0x7100200228
unsigned short capped16_200228(Capped16_200228* object) {
    unsigned short value = object->value;
    return value > 0x5dc0 ? 0x5dc0 : value;
}

struct Slot207a9c {
    unsigned char pad[0x8];
    unsigned char value;      // +8
    unsigned char pad9[0x2];
};

// 0x7100207a9c
void set_slot_byte_207a9c(Slot207a9c* slots, unsigned char index, unsigned char value) {
    slots[index].value = value;
}

struct Slot207ab0 {
    unsigned char pad[0x9];
    unsigned char value;      // +9
    unsigned char pada[0x1];
};

// 0x7100207ab0
void set_slot_byte_207ab0(Slot207ab0* slots, unsigned char index, unsigned char value) {
    slots[index].value = value;
}

struct Guarded218ad8 {
    unsigned char pad[0x8];
    void* target;             // +8
};
unsigned char guarded_query_2192b4(Guarded218ad8* object);                // 0x71002192b4

// 0x7100218ad8
unsigned char query_if_set_218ad8(Guarded218ad8* object) {
    if (object->target)
        return guarded_query_2192b4(object);
    return 0;
}

struct Guarded227938 {
    unsigned char pad[0x12b0];
    void* target;             // +12b0
};
unsigned char guarded_query_593018(Guarded227938* object);                // 0x7100593018

// 0x7100227938
unsigned char query_if_set_227938(Guarded227938* object) {
    if (object->target)
        return guarded_query_593018(object);
    return 0;
}

struct GameBytes255f2c {
    unsigned char pad[0xdb9];
    unsigned char value;      // +db9
};
// Reached through the GOT slot at 0x7100c22d68.
extern GameBytes255f2c* gGameState_255f2c;

// 0x7100255f2c
unsigned char game_byte_255f2c() {
    return gGameState_255f2c->value;
}

struct GameBytes25812c {
    unsigned char pad[0xd8a];
    unsigned char value;      // +d8a
};
// Reached through the GOT slot at 0x7100c22d68.
extern GameBytes25812c* gGameState_25812c;

// 0x710025812c
unsigned char game_byte_25812c() {
    return gGameState_25812c->value;
}

struct Child4408b8 {
    unsigned char pad[0x5];
    unsigned char flag;       // +5
};
struct Parent4408b8 {
    unsigned char pad[0x118];
    Child4408b8* child;   // +118
};

// 0x71004408b8
unsigned char child_flag_4408b8(Parent4408b8* object) {
    return object->child->flag != 0;
}

struct Child5ce194 {
    unsigned char pad[0xa];
    unsigned char flag;       // +a
};
struct Parent5ce194 {
    unsigned char pad[0x18];
    Child5ce194* child;   // +18
};

// 0x71005ce194
unsigned char child_flag_5ce194(Parent5ce194* object) {
    return object->child->flag != 0;
}

struct BitWord197b2c {
    unsigned char pad[0x10];
    unsigned int bits;        // +10
};

// 0x7100197b2c
unsigned char has_bit_197b2c(BitWord197b2c* object, int bit) {
    return (object->bits & (1 << bit)) != 0;
}

struct BitWord1ccda8 {
    unsigned char pad[0x1f8];
    unsigned int bits;        // +1f8
};

// 0x71001ccda8
unsigned char has_bit_1ccda8(BitWord1ccda8* object, int bit) {
    return (object->bits & (1 << bit)) != 0;
}

struct Rec1a7048 {
    unsigned char pad[0xb8];
    unsigned char value;      // +238
    unsigned char pad239[0x7];
};
struct Recs1a7048 {
    unsigned char pad[0x180];
    Rec1a7048 records[0x20];
};

// 0x71001a7048
void set_rec_byte_1a7048(Recs1a7048* table, unsigned int index, unsigned char value) {
    if (index <= 0x1f)
        table->records[index].value = value;
}

struct Rec1a7060 {
    unsigned char pad[0xb9];
    unsigned char value;      // +239
    unsigned char pad23a[0x6];
};
struct Recs1a7060 {
    unsigned char pad[0x180];
    Rec1a7060 records[0x20];
};

// 0x71001a7060
void set_rec_byte_1a7060(Recs1a7060* table, unsigned int index, unsigned char value) {
    if (index <= 0x1f)
        table->records[index].value = value;
}

struct Capped32_2026cc {
    unsigned int value;       // +0
};

// 0x71002026cc
unsigned int capped32_2026cc(Capped32_2026cc* object) {
    unsigned int value = object->value;
    return value > 0x36ee7f ? 0x36ee7f : value;
}

struct Capped32_202800 {
    unsigned char pad[0x14];
    unsigned int value;       // +14
};

// 0x7100202800
unsigned int capped32_202800(Capped32_202800* object) {
    unsigned int value = object->value;
    return value > 0x98967f ? 0x98967f : value;
}

struct Info3383f4 {
    unsigned char pad[0x10];
    int value;                // +10
};
struct InfoHolder3383f4 {
    unsigned char pad[0x28];
    Info3383f4* info;   // +28
};

// 0x71003383f4
int info_value_3383f4(InfoHolder3383f4* object) {
    return object->info ? object->info->value : 0;
}

struct Info49ba4c {
    unsigned char pad[0x10];
    int value;                // +10
};
struct InfoHolder49ba4c {
    unsigned char pad[0x18];
    Info49ba4c* info;   // +18
};

// 0x710049ba4c
int info_value_49ba4c(InfoHolder49ba4c* object) {
    return object->info ? object->info->value : 0;
}

struct PairSource3e95e8 {
    unsigned char pad[0x20];
    long first;               // +20
    long second;              // +28
};
struct PairCopy3e95e8 {
    unsigned char pad[8];
    PairSource3e95e8* source;   // +08
    unsigned char pad10[0x10];
    long first;               // +20
    long second;              // +28
};

// 0x71003e95e8
void copy_pair_3e95e8(PairCopy3e95e8* object) {
    PairSource3e95e8* source = object->source;
    object->second = source->second;
    object->first = source->first;
}

struct PairSource3e9600 {
    unsigned char pad[0x10];
    long first;               // +10
    long second;              // +18
};
struct PairCopy3e9600 {
    unsigned char pad[8];
    PairSource3e9600* source;   // +08
    unsigned char pad10[0x20];
    long first;               // +30
    long second;              // +38
};

// 0x71003e9600
void copy_pair_3e9600(PairCopy3e9600* object) {
    PairSource3e9600* source = object->source;
    object->second = source->second;
    object->first = source->first;
}

struct Settings3fa568 {
    unsigned char pad[0x1b24];
    int value;                // +1b24
};
// Reached through the GOT slot at 0x7100c2b700.
extern Settings3fa568* gSettings_c2b700;

// 0x71003fa568
void set_setting_3fa568(int value) {
    if (gSettings_c2b700)
        gSettings_c2b700->value = value;
}

struct Settings3ff128 {
    unsigned char pad[0xf14];
    int value;                // +f14
};
// Reached through the GOT slot at 0x7100c2b710.
extern Settings3ff128* gSettings_c2b710;

// 0x71003ff128
void set_setting_3ff128(int value) {
    if (gSettings_c2b710)
        gSettings_c2b710->value = value;
}

struct Linked5c2f5c {
    unsigned char pad[0x20];
    void* link;               // +20
    unsigned char pad28[0x30];
    void* value;              // +58
};

// 0x71005c2f5c
void* linked_value_5c2f5c(Linked5c2f5c* object) {
    return object->link ? object->value : nullptr;
}

struct Linked5c2fd0 {
    unsigned char pad[0x10];
    void* value;              // +10
    unsigned char pad18[0x8];
    void* link;               // +20
};

// 0x71005c2fd0
void* linked_value_5c2fd0(Linked5c2fd0* object) {
    return object->link ? object->value : nullptr;
}
