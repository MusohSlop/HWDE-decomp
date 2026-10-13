// More pairs of tiny accessors found by tools/family_scan.py --immediates (two copies of each shape,
// in different classes). Each pair differs only in offsets, limits, globals and callees; types and
// functions are named after their address. Status: matching/README.md.

#include "tiny_common.h"

struct Checked3af87c {
    unsigned char pad0[0x8];
    void* first;  // +8
    unsigned char pad10[0x8];
    void* second;  // +18
    unsigned char pad20[0x28];
    unsigned char enabled;  // +48
};

// 0x71003af87c
unsigned char check_both_3af87c(Checked3af87c* object) {
    if (object->enabled && check_object_1f7da0(object->first))
        check_object_1f7da0(object->second);
    return 0;
}

struct Checked3af97c {
    unsigned char pad0[0x8];
    void* first;  // +8
    unsigned char pad10[0x10];
    void* second;  // +20
    unsigned char pad28[0x8];
    unsigned char enabled;  // +30
};

// 0x71003af97c
unsigned char check_both_3af97c(Checked3af97c* object) {
    if (object->enabled && check_object_1f7da0(object->first))
        check_object_1f7da0(object->second);
    return 0;
}

struct Entry64_4443ec {
    unsigned char data[0x40];
};
struct EntryHeader4443ec {
    unsigned char pad0[0x6];
    unsigned short count;  // +6
};
struct EntryList4443ec {
    unsigned char pad0[0x20];
    EntryHeader4443ec* header;  // +20
    Entry64_4443ec* entries;  // +28
};

// 0x71004443ec
Entry64_4443ec* entry_at_4443ec(EntryList4443ec* list, unsigned int index) {
    if (!list->entries || !list->header || list->header->count <= index)
        return nullptr;
    return &list->entries[index];
}

struct Entry64_444468 {
    unsigned char data[0x40];
};
struct EntryHeader444468 {
    unsigned char pad0[0xa];
    unsigned short count;  // +a
};
struct EntryList444468 {
    unsigned char pad0[0x20];
    EntryHeader444468* header;  // +20
    unsigned char pad28[0x10];
    Entry64_444468* entries;  // +38
};

// 0x7100444468
Entry64_444468* entry_at_444468(EntryList444468* list, unsigned int index) {
    if (!list->entries || !list->header || list->header->count <= index)
        return nullptr;
    return &list->entries[index];
}

struct FarBits2032f4 {
    unsigned char pad0[0x1bb88];
    unsigned int bits[1];  // +1bb88
};

// 0x71002032f4
unsigned char far_bit_2032f4(FarBits2032f4* set, int id) {
    if (static_cast<unsigned int>(id) <= 0xff)
        return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
    return 0;
}

struct FarBits203388 {
    unsigned char pad0[0x1bba8];
    unsigned int bits[1];  // +1bba8
};

// 0x7100203388
unsigned char far_bit_203388(FarBits203388* set, int id) {
    if (static_cast<unsigned int>(id) <= 0x3f)
        return (set->bits[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
    return 0;
}

struct ShowMiddle38cc74 {
    unsigned char pad[0x18];
    ShowNode* node;           // +18
};
struct ShowPair38cc74 {
    unsigned char pad0[0x8];
    ShowMiddle38cc74* middle;  // +8
    unsigned char pad10[0x30];
    ShowNode* extra;  // +40
};

// 0x710038cc74
void set_shown_38cc74(ShowPair38cc74* object, unsigned char shown) {
    bool on = shown != 0;
    object->middle->node->shown = on;
    if (object->extra)
        object->extra->shown = on;
}

struct ShowMiddle39e008 {
    unsigned char pad[0x18];
    ShowNode* node;           // +18
};
struct ShowPair39e008 {
    unsigned char pad0[0x8];
    ShowMiddle39e008* middle;  // +8
    unsigned char pad10[0x28];
    ShowNode* extra;  // +38
};

// 0x710039e008
void set_shown_39e008(ShowPair39e008* object, unsigned char shown) {
    bool on = shown != 0;
    object->middle->node->shown = on;
    if (object->extra)
        object->extra->shown = on;
}

class Refreshed5dba00 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void v40();
    virtual void v48();
    virtual void refresh();

    unsigned char pad8[0xd8];
    void* value;              // +e0
};

// 0x71005dba00
void* refresh_get_5dba00(Refreshed5dba00* object, int skip) {
    object->refresh();
    return skip ? nullptr : object->value;
}

class Refreshed5dd384 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void v40();
    virtual void v48();
    virtual void refresh();

    unsigned char pad8[0x140];
    void* value;              // +148
};

// 0x71005dd384
void* refresh_get_5dd384(Refreshed5dd384* object, int skip) {
    object->refresh();
    return skip ? nullptr : object->value;
}

struct GridRow20f0c0 {
    unsigned short values[12];
};
struct Grid20f0c0 {
    unsigned char pad0[0xe];
    GridRow20f0c0 rows[4];  // +e
};

// 0x710020f0c0
unsigned short grid_value_20f0c0(Grid20f0c0* grid, short row, short column) {
    unsigned short value = 0;
    if (row <= 3 && column <= 5)
        value = grid->rows[row].values[column];
    return value;
}

struct GridRow20f0f8 {
    unsigned short values[12];
};
struct Grid20f0f8 {
    unsigned char pad0[0x1a];
    GridRow20f0f8 rows[4];  // +1a
};

// 0x710020f0f8
unsigned short grid_value_20f0f8(Grid20f0f8* grid, short row, short column) {
    unsigned short value = 0;
    if (row <= 3 && column <= 5)
        value = grid->rows[row].values[column];
    return value;
}

struct KindEntry214b48 {
    unsigned char pad0[0x4];
    signed char id;  // +4
    unsigned char pad5[0xb];
};
struct KindHolder214b48 {
    unsigned char pad0[0x10];
    short kind;  // +10
};
// Reached through the GOT slot at 0x7100c23360.
extern KindEntry214b48* gKinds_214b48;

// 0x7100214b48
int kind_id_214b48(KindHolder214b48* object) {
    long kind = object->kind;
    if (static_cast<unsigned long>(kind) <= 0xf9) {
        signed char id = gKinds_214b48[kind].id;
        return static_cast<unsigned char>(id) < 0x40 ? id : -1;
    }
    return -1;
}

struct KindEntry215dbc {
    unsigned char pad0[0x5];
    signed char id;  // +5
    unsigned char pad6[0xa];
};
struct KindHolder215dbc {
    unsigned char pad0[0x10];
    short kind;  // +10
};
// Reached through the GOT slot at 0x7100c23360.
extern KindEntry215dbc* gKinds_215dbc;

// 0x7100215dbc
int kind_id_215dbc(KindHolder215dbc* object) {
    long kind = object->kind;
    if (static_cast<unsigned long>(kind) <= 0xf9) {
        signed char id = gKinds_215dbc[kind].id;
        return static_cast<unsigned char>(id) < 0x5 ? id : -1;
    }
    return -1;
}

// 0x7100248100
struct BufferSlot_248100 {
    void release();

    unsigned char pad[0x30];
    void* buffer;             // +30
    unsigned char pad38[0x40];
    BufferAllocator* allocator; // +78
};

void BufferSlot_248100::release() {
    if (buffer)
        allocator->free(buffer);
    buffer = nullptr;
}

// 0x710024b910
struct BufferSlot_24b910 {
    void release();

    unsigned char pad[0x48];
    void* buffer;             // +48
    unsigned char pad50[0x30];
    BufferAllocator* allocator; // +80
};

void BufferSlot_24b910::release() {
    if (buffer)
        allocator->free(buffer);
    buffer = nullptr;
}

// 0x7100217cbc
const char* database_text_217cbc(int id) {
    if (static_cast<unsigned int>(id) <= 0x63 && gTextDatabase.loaded)
        return gTextDatabase.table_at_48.find(id, 0);
    return kEmptyText;
}

// 0x7100217d2c
const char* database_text_217d2c(int id) {
    if (static_cast<unsigned int>(id) <= 0xc7 && gTextDatabase.loaded)
        return gTextDatabase.table_at_68.find(id, 0);
    return kEmptyText;
}

class Owned2da33c {
public:
    virtual void v00();
    virtual void destroy();
};
// Reached through the GOT slot at 0x7100c2ab80.
extern Owned2da33c* gOwned_c2ab80;

// 0x71002da33c
void destroy_owned_2da33c() {
    if (gOwned_c2ab80) {
        gOwned_c2ab80->destroy();
        gOwned_c2ab80 = nullptr;
    }
}

class Owned336334 {
public:
    virtual void destroy();
};
// Reached through the GOT slot at 0x7100c2ae58.
extern Owned336334* gOwned_c2ae58;

// 0x7100336334
void destroy_owned_336334() {
    if (gOwned_c2ae58) {
        gOwned_c2ae58->destroy();
        gOwned_c2ae58 = nullptr;
    }
}

void prepare_38db1c(void* object);                              // 0x710038db1c
void apply_scaled_38cb58(void* part, float scale, int value); // 0x710038cb58

// 0x7100392408
void setup_part_392408(unsigned char* object, int value) {
    prepare_38db1c(object);
    apply_scaled_38cb58(object + 0x1c1a0, 1.0f, value);
}

void prepare_38db1c(void* object);                              // 0x710038db1c
void apply_scaled_38cb58(void* part, float scale, int value); // 0x710038cb58

// 0x7100395f78
void setup_part_395f78(unsigned char* object, int value) {
    prepare_38db1c(object);
    apply_scaled_38cb58(object + 0x96cf8, 1.0f, value);
}

struct LookupEntry454508 {
    unsigned char pad0[0x20];
    int value;  // +20
};

// 0x7100454508
int lookup_value_454508(int id) {
    LookupEntry454508* entry = static_cast<LookupEntry454508*>(find_entry_426ab4(load_global_425dd0(), id));
    return entry ? entry->value : -1;
}

struct LookupEntry454904 {
    unsigned char pad0[0x30];
    int value;  // +30
};

// 0x7100454904
int lookup_value_454904(int id) {
    LookupEntry454904* entry = static_cast<LookupEntry454904*>(find_entry_426ab4(load_global_425dd0(), id));
    return entry ? entry->value : -1;
}

// 0x71004613b0
long query_value_4613b0(QueryHandle* handle) {
    void* target = handle->target;
    int value;
    gQuery_c22f20(target, 0x13, &value);
    return value;
}

// 0x71004613e8
long query_value_4613e8(QueryHandle* handle) {
    void* target = handle->target;
    int value;
    gQuery_c22f20(target, 0x14, &value);
    return value;
}

struct TwoBits20f450 {
    unsigned char pad0[0xe10];
    unsigned char packed[1];  // +e10
};

// 0x710020f450
int two_bit_20f450(TwoBits20f450* object, int index) {
    unsigned int byte = index / 4;
    return ((object->packed[byte] >> ((index % 4) * 2)) & 3) + 1;
}

struct TwoBits20f484 {
    unsigned char pad0[0xe5b];
    unsigned char packed[1];  // +e5b
};

// 0x710020f484
int two_bit_20f484(TwoBits20f484* object, int index) {
    unsigned int byte = index / 4;
    return ((object->packed[byte] >> ((index % 4) * 2)) & 3) + 1;
}

struct ToggleMiddle316a30 {
    unsigned char pad[0x18];
    ShowNode* node;           // +18
};
struct Toggle316a30 {
    ToggleMiddle316a30* middle;  // +0
    void* target;  // +8
};

// 0x7100316a30
void toggle_shown_316a30(Toggle316a30* object, unsigned int level) {
    if (!object->middle)
        return;
    ShowNode* node = object->middle->node;
    if (level <= 4) {
        node->shown = 1;
        refresh_shown_1f7f44(object->target);
    } else {
        node->shown = 0;
    }
}

struct ToggleMiddle3814d4 {
    unsigned char pad[0x18];
    ShowNode* node;           // +18
};
struct Toggle3814d4 {
    unsigned char pad0[0x10];
    ToggleMiddle3814d4* middle;  // +10
    unsigned char pad18[0x18];
    void* target;  // +30
};

// 0x71003814d4
void toggle_shown_3814d4(Toggle3814d4* object, unsigned int level) {
    if (!object->middle)
        return;
    ShowNode* node = object->middle->node;
    if (level <= 4) {
        node->shown = 1;
        refresh_shown_1f7f44(object->target);
    } else {
        node->shown = 0;
    }
}

class Compared6bee4 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void v40();
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void v60();
    virtual void v68();
    virtual int state();
};

// 0x710006bee4
unsigned char state_is_6bee4(Compared6bee4* object, int state) {
    return object->state() == state;
}

class Compared6bf44 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void v40();
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void v60();
    virtual void v68();
    virtual void v70();
    virtual int state();
};

// 0x710006bf44
unsigned char state_is_6bf44(Compared6bf44* object, int state) {
    return object->state() == state;
}

struct BitWord1a7670 {
    unsigned char pad0[0x19e4];
    unsigned int bits;  // +19e4
};

// 0x71001a7670
void set_bit_1a7670(BitWord1a7670* object, int bit, unsigned char on) {
    unsigned int mask = 1 << bit;
    if (on)
        object->bits |= mask;
    else
        object->bits &= ~mask;
}

struct BitWord1ccdc0 {
    unsigned char pad0[0x1f8];
    unsigned int bits;  // +1f8
};

// 0x71001ccdc0
void set_bit_1ccdc0(BitWord1ccdc0* object, int bit, unsigned char on) {
    unsigned int mask = 1 << bit;
    if (on)
        object->bits |= mask;
    else
        object->bits &= ~mask;
}

class Registered1dd0e0 {
public:
    virtual void v00();
    virtual void notify(void* arg);
};
struct Registry1dd0e0 {
    unsigned char pad0[0x8];
    Registered1dd0e0* entries[0x400];  // +8
};
extern Registry1dd0e0* gRegistry_1dd0e0 __attribute__((visibility("hidden"))); // 0x7100c47f10

// 0x71001dd0e0
void notify_entry_1dd0e0(int index, void* arg) {
    if (static_cast<unsigned int>(index) > 0x3ff || !gRegistry_1dd0e0)
        return;
    if (Registered1dd0e0* entry = gRegistry_1dd0e0->entries[index])
        entry->notify(arg);
}

class Registered1dd110 {
public:
    virtual void v00();
    virtual void v08();
    virtual void notify(void* arg);
};
struct Registry1dd110 {
    unsigned char pad0[0x8];
    Registered1dd110* entries[0x400];  // +8
};
extern Registry1dd110* gRegistry_1dd110 __attribute__((visibility("hidden"))); // 0x7100c47f10

// 0x71001dd110
void notify_entry_1dd110(int index, void* arg) {
    if (static_cast<unsigned int>(index) > 0x3ff || !gRegistry_1dd110)
        return;
    if (Registered1dd110* entry = gRegistry_1dd110->entries[index])
        entry->notify(arg);
}

struct Offset257160 {
    unsigned char pad0[0x58];
    int value;  // +58
};
struct OffsetTable257160 {
    unsigned char pad0[0x68];
    Offset257160* entries[0x12c];  // +68
};
// Reached through the GOT slot at 0x7100c2a530.
extern OffsetTable257160* gOffsets_257160;

// 0x7100257160
int offset_entry_257160(int id) {
    unsigned int index = id - 0x4d9;
    if (index <= 0x12b)
        return gOffsets_257160->entries[static_cast<int>(index)]->value;
    return -1;
}

struct Offset257190 {
    unsigned char pad0[0x5c];
    int value;  // +5c
};
struct OffsetTable257190 {
    unsigned char pad0[0x68];
    Offset257190* entries[0x12c];  // +68
};
// Reached through the GOT slot at 0x7100c2a530.
extern OffsetTable257190* gOffsets_257190;

// 0x7100257190
int offset_entry_257190(int id) {
    unsigned int index = id - 0x4d9;
    if (index <= 0x12b)
        return gOffsets_257190->entries[static_cast<int>(index)]->value;
    return -1;
}

struct ByteSet8c614 {
    unsigned char pad0[0x46c];
    unsigned char bits[1];  // +46c
};

// 0x710008c614
void mark_8c614(ByteSet8c614* set, unsigned int id) {
    if (id <= 0x6)
        set->bits[id >> 3] |= 1 << (id & 7);
}

struct ByteSetb00d0 {
    unsigned char pad0[0x998];
    unsigned char bits[1];  // +998
};

// 0x71000b00d0
void mark_b00d0(ByteSetb00d0* set, unsigned int id) {
    if (id <= 0x7)
        set->bits[id >> 3] |= 1 << (id & 7);
}

struct Saveddd268 {
    int active;  // +0
    unsigned char pad4[0x16c];
    unsigned char data[1];  // +170
};

// 0x71000dd268
void save_if_set_dd268(Saveddd268* object) {
    if (object->active)
        save_block_1df8c0(gSaveTarget_c22a40, object->data, 0x330, -1);
}

struct Savede0640 {
    int active;  // +0
    unsigned char pad4[0x14c];
    unsigned char data[1];  // +150
};

// 0x71000e0640
void save_if_set_e0640(Savede0640* object) {
    if (object->active)
        save_block_1df8c0(gSaveTarget_c22a40, object->data, 0x110, -1);
}

struct WideRow203660 {
    short values[0x12c];
};
struct WideGrid203660 {
    unsigned char pad0[0x162];
    WideRow203660 rows[4];  // +162
};

// 0x7100203660
short* grid_cell_203660(WideGrid203660* grid, int row, int column) {
    short* cell = nullptr;
    if (static_cast<unsigned int>(row) <= 3 && static_cast<unsigned int>(column) <= 0x12b)
        cell = &grid->rows[row].values[column];
    return cell;
}

struct WideRow20368c {
    short values[0x28];
};
struct WideGrid20368c {
    unsigned char pad0[0xac2];
    WideRow20368c rows[4];  // +ac2
};

// 0x710020368c
short* grid_cell_20368c(WideGrid20368c* grid, int row, int column) {
    short* cell = nullptr;
    if (static_cast<unsigned int>(row) <= 3 && static_cast<unsigned int>(column) <= 0x27)
        cell = &grid->rows[row].values[column];
    return cell;
}

// 0x71002111f0
unsigned char item_below_2111f0(int item) {
    return gItemDefs->find(item)->unsigned_values[0x19] < 0x28;
}

// 0x710021121c
unsigned char item_below_21121c(int item) {
    return gItemDefs->find(item)->unsigned_values[0x19] < 0x64;
}

struct Handle24717c {
    unsigned char pad0[0x8];
    int handle;  // +8
};
void release_handle_3f308(int handle);                        // 0x710003f308

// 0x710024717c
void release_handle_24717c(Handle24717c* object) {
    release_handle_3f308(object->handle);
    object->handle = -1;
}

struct Handle24c7cc {
    unsigned char pad0[0x78];
    int handle;  // +78
};
void release_handle_3f344(int handle);                        // 0x710003f344

// 0x710024c7cc
void release_handle_24c7cc(Handle24c7cc* object) {
    release_handle_3f344(object->handle);
    object->handle = -1;
}

struct ListenerOwner3ff508 {
    unsigned char pad0[0x10];
    Listener* listener;  // +10
};
// Reached through the GOT slot at 0x7100c2b4b0.
extern ListenerOwner3ff508* gListener_c2b4b0;

// 0x71003ff508
void hand_off_3ff508(void* object) {
    if (object)
        gListener_c2b4b0->listener->released(object);
}

struct ListenerOwner497344 {
    unsigned char pad0[0x40];
    Listener* listener;  // +40
};
// Reached through the GOT slot at 0x7100c2cb70.
extern ListenerOwner497344* gListener_c2cb70;

// 0x7100497344
void hand_off_497344(void* object) {
    if (object)
        gListener_c2cb70->listener->released(object);
}

struct SlotPlayerea4c {
    unsigned char pad0[0xe0];
    int value;  // +e0
};
struct SlotOwnerea4c {
    unsigned char pad0[0xb08];
    SlotPlayerea4c* players[2];  // +b08
};
// Reached through the GOT slot at 0x7100c21698.
extern SlotOwnerea4c* gSlots_ea4c;

// 0x710000ea4c
int slot_player_ea4c(int slot) {
    SlotPlayerea4c** players = gSlots_ea4c->players;
    SlotPlayerea4c** player = static_cast<unsigned int>(slot) < 2 ? players + slot : players;
    return (*player)->value;
}

struct SlotPlayereb3c {
    unsigned char pad0[0xd4];
    int value;  // +d4
};
struct SlotOwnereb3c {
    unsigned char pad0[0xb08];
    SlotPlayereb3c* players[2];  // +b08
};
// Reached through the GOT slot at 0x7100c21698.
extern SlotOwnereb3c* gSlots_eb3c;

// 0x710000eb3c
int slot_player_eb3c(int slot) {
    SlotPlayereb3c** players = gSlots_eb3c->players;
    SlotPlayereb3c** player = static_cast<unsigned int>(slot) < 2 ? players + slot : players;
    return (*player)->value;
}

// 0x71000cf394
float item_float_cf394(void* a, void* b, int item) {
    return gItemDefs->find(item)->unsigned_words[5];
}

// 0x71000cf3bc
float item_float_cf3bc(void* a, void* b, int item) {
    return gItemDefs->find(item)->unsigned_words[6];
}

struct Phase3d6fd0 {
    unsigned char pad0[0x710dc];
    unsigned int frame;  // +710dc
};

// 0x71003d6fd0
unsigned int frame_phase_3d6fd0(Phase3d6fd0* object) {
    return object->frame % 3;
}

struct Phase3d6ff8 {
    unsigned char pad0[0x710e0];
    unsigned int frame;  // +710e0
};

// 0x71003d6ff8
unsigned int frame_phase_3d6ff8(Phase3d6ff8* object) {
    return object->frame % 3;
}

struct TwoPairs36740 {
    unsigned char pad0[0xc0];
    ValuePair first;  // +c0
    ValuePair second;  // +d0
};

// 0x7100036740
void set_two_pairs_36740(TwoPairs36740* object, const ValuePair* first, const ValuePair* second) {
    object->first.second = first->second;
    object->first.first = first->first;
    object->second.second = second->second;
    object->second.first = second->first;
}

struct TwoPairs247340 {
    unsigned char pad0[0xa0];
    ValuePair first;  // +a0
    ValuePair second;  // +b0
};

// 0x7100247340
void set_two_pairs_247340(TwoPairs247340* object, const ValuePair* first, const ValuePair* second) {
    object->first.second = first->second;
    object->first.first = first->first;
    object->second.second = second->second;
    object->second.first = second->first;
}

struct ResolvedId527d8 {
    unsigned char pad0[0x24];
    short id;  // +24
};
class IdSource527d8 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void v40();
    virtual ResolvedId527d8* resolve();
};
struct IdHolder527d8 {
    unsigned char pad0[0x8];
    IdSource527d8* source;  // +8
};

// 0x71000527d8
int resolved_id_527d8(IdHolder527d8* object) {
    return object->source->resolve()->id;
}

struct ResolvedId527fc {
    unsigned char pad0[0x24];
    short id;  // +24
};
class IdSource527fc {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void v40();
    virtual ResolvedId527fc* resolve();
};
struct IdHolder527fc {
    unsigned char pad0[0x10];
    IdSource527fc* source;  // +10
};

// 0x71000527fc
int resolved_id_527fc(IdHolder527fc* object) {
    return object->source->resolve()->id;
}

struct Stepper7a1fc {
    unsigned char pad0[0x40];
    unsigned int count;  // +40
};

// 0x710007a1fc
void step_7a1fc(Stepper7a1fc* object) {
    if (object->count < gStepLimit_c221d0)
        ++object->count;
}

struct Stepper99c14 {
    unsigned char pad0[0xc0];
    unsigned int count;  // +c0
};

// 0x7100099c14
void step_99c14(Stepper99c14* object) {
    if (object->count < gStepLimit_c221d0)
        ++object->count;
}

struct Ids20352c {
    unsigned char pad0[0x14c];
    short ids[4];  // +14c
};

// 0x710020352c
void set_id_20352c(Ids20352c* object, int slot, int id) {
    if (static_cast<unsigned int>(slot) > 3)
        return;
    if (static_cast<unsigned int>(id) >= 0x64 && id != -1)
        return;
    object->ids[slot] = id;
}

struct Ids2035d4 {
    unsigned char pad0[0x154];
    short ids[4];  // +154
};

// 0x71002035d4
void set_id_2035d4(Ids2035d4* object, int slot, int id) {
    if (static_cast<unsigned int>(slot) > 3)
        return;
    if (static_cast<unsigned int>(id) >= 0x64 && id != -1)
        return;
    object->ids[slot] = id;
}

struct DrawGate3af760 {
    DrawNode* node;  // +0
    unsigned char pad8[0x20];
    ShowNode* gate;  // +28
    unsigned char pad30[0x18];
    unsigned char enabled;  // +48
};

// 0x71003af760
void draw_if_shown_3af760(DrawGate3af760* object) {
    if (object->enabled && object->gate->shown)
        object->node->draw(0);
}

struct DrawGate3af904 {
    DrawNode* node;  // +0
    unsigned char pad8[0x20];
    ShowNode* gate;  // +28
    unsigned char enabled;  // +30
};

// 0x71003af904
void draw_if_shown_3af904(DrawGate3af904* object) {
    if (object->enabled && object->gate->shown)
        object->node->draw(0);
}

void first_step_4d2f04(void* object);                              // 0x71004d2f04
void second_step_4e1604(void* part);                              // 0x71004e1604

// 0x71004cf118
void two_step_4cf118(unsigned char* object) {
    first_step_4d2f04(object);
    second_step_4e1604(object + 0x170);
}

void first_step_537568(void* object);                              // 0x7100537568
void second_step_600a90(void* part);                              // 0x7100600a90

// 0x7100537544
void two_step_537544(unsigned char* object) {
    first_step_537568(object);
    second_step_600a90(object + 0x70);
}

extern const int kValues_73de60[] __attribute__((visibility("hidden"))); // 0x710073de60

// 0x710000a130
int table_value_a130(int index) {
    if (static_cast<unsigned int>(index) <= 0x33)
        return kValues_73de60[index];
    return -1;
}

extern const int kValues_73dfd0[] __attribute__((visibility("hidden"))); // 0x710073dfd0

// 0x710000fa7c
int table_value_fa7c(int index) {
    if (static_cast<unsigned int>(index) <= 0x6)
        return kValues_73dfd0[index];
    return -1;
}

class Acked2dcdb0 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void v40();
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void v60();
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void v80();
    virtual void v88();
    virtual void v90();
    virtual void v98();
    virtual void va0();
    virtual void handle();
};

// 0x71002dcdb0
int ack_2dcdb0(Acked2dcdb0* object) {
    object->handle();
    return 1;
}

class Acked2de6c0 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void v40();
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void v60();
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void v80();
    virtual void v88();
    virtual void v90();
    virtual void v98();
    virtual void va0();
    virtual void handle();
};

// 0x71002de6c0
int ack_2de6c0(Acked2de6c0* object) {
    object->handle();
    return 1;
}

// Reached through the GOT slot at 0x7100c216f0.
extern unsigned char* gBlock_c216f0;
void block_handler_30f8(void* part, int value);                // 0x71000030f8

// 0x710006f30c
void block_call_6f30c(int value) {
    block_handler_30f8(gBlock_c216f0 + 0x1ed8, value);
}

// Reached through the GOT slot at 0x7100c21708.
extern unsigned char* gBlock_c21708;
void block_handler_245dc4(void* part, int value);                // 0x7100245dc4

// 0x7100241f0c
void block_call_241f0c(int value) {
    block_handler_245dc4(gBlock_c21708 + 0x85b0, value);
}

struct Rec1a7078 {
    unsigned char pad0[0xb9];
    unsigned char value;  // +b9
    unsigned char padba[0x6];
};
struct Recs1a7078 {
    unsigned char pad0[0x180];
    Rec1a7078 records[0x20];  // +180
};

// 0x71001a7078
unsigned char rec_byte_1a7078(Recs1a7078* table, unsigned int index) {
    if (index > 0x1f)
        return 0;
    return table->records[index].value;
}

struct Rec1a723c {
    unsigned char pad0[0xa9];
    unsigned char value;  // +a9
    unsigned char padaa[0x16];
};
struct Recs1a723c {
    unsigned char pad0[0x180];
    Rec1a723c records[0x20];  // +180
};

// 0x71001a723c
unsigned char rec_byte_1a723c(Recs1a723c* table, unsigned int index) {
    if (index > 0x1f)
        return 0;
    return table->records[index].value;
}

// Reached through the GOT slot at 0x7100c23050.
extern float gFloats_c23050[];

// 0x71001eb67c
float float_entry_1eb67c(int index) {
    if (static_cast<unsigned int>(index) > 0x5f)
        return 0.0f;
    return gFloats_c23050[index];
}

// Reached through the GOT slot at 0x7100c23068.
extern float gFloats_c23068[];

// 0x71001eb69c
float float_entry_1eb69c(int index) {
    if (static_cast<unsigned int>(index) > 0xdf)
        return 0.0f;
    return gFloats_c23068[index];
}

struct TextIds1fe788 {
    unsigned char pad0[0x14];
    short ids[0x1f];  // +14
};

// 0x71001fe788
void show_text_1fe788(TextIds1fe788* object, int slot) {
    long index = static_cast<unsigned int>(slot) < 0x1f ? slot : 0;
    show_message_217d9c(object->ids[index] + 0x2517);
}

struct TextIds1fe7a8 {
    unsigned char pad0[0x14];
    short ids[0x1f];  // +14
};

// 0x71001fe7a8
void show_text_1fe7a8(TextIds1fe7a8* object, int slot) {
    long index = static_cast<unsigned int>(slot) < 0x1f ? slot : 0;
    show_message_217d9c(object->ids[index] + 0x2608);
}

struct CheckedId20a114 {
    unsigned char pad0[0x12];
    short id;  // +12
};

// 0x710020a114
void store_id_20a114(CheckedId20a114* object, int id) {
    if (static_cast<unsigned int>(id) >= 0x406 && id != -1)
        return;
    object->id = static_cast<unsigned int>(id) < 0x406 ? id : -1;
}

struct CheckedId20a148 {
    unsigned char pad0[0x14];
    short id;  // +14
};

// 0x710020a148
void store_id_20a148(CheckedId20a148* object, int id) {
    if (static_cast<unsigned int>(id) >= 0x80 && id != -1)
        return;
    object->id = static_cast<unsigned int>(id) < 0x80 ? id : -1;
}

struct Unchecked2fd648 {
    unsigned char pad0[0x260];
    void* target;  // +260
};

// 0x71002fd648
unsigned char not_ready_2fd648(Unchecked2fd648* object) {
    return !is_ready_1f7e3c(object->target);
}

struct Unchecked3054ac {
    unsigned char pad0[0x150];
    void* target;  // +150
};

// 0x71003054ac
unsigned char not_ready_3054ac(Unchecked3054ac* object) {
    return !is_ready_1f7e3c(object->target);
}

struct OptGlobal3fa344 {
    unsigned char pad0[0x19c8];
    int value;  // +19c8
};
// Reached through the GOT slot at 0x7100c2b700.
extern OptGlobal3fa344* gOpt_3fa344;

// 0x71003fa344
int opt_field_3fa344() {
    if (gOpt_3fa344)
        return gOpt_3fa344->value;
    return -1;
}

struct OptGlobal3fa580 {
    unsigned char pad0[0x1b24];
    int value;  // +1b24
};
// Reached through the GOT slot at 0x7100c2b700.
extern OptGlobal3fa580* gOpt_3fa580;

// 0x71003fa580
int opt_field_3fa580() {
    if (gOpt_3fa580)
        return gOpt_3fa580->value;
    return -1;
}

struct Based5d7d90 {
    unsigned char pad0[0x30];
    unsigned int offset;  // +30
};

// 0x71005d7d90
void* based_5d7d90(Based5d7d90* object, BaseContext* context) {
    unsigned char* base = context->info->base;
    if (!base)
        return nullptr;
    return base + object->offset;
}

struct Based5d9068 {
    unsigned char pad0[0x34];
    unsigned int offset;  // +34
};

// 0x71005d9068
void* based_5d9068(Based5d9068* object, BaseContext* context) {
    unsigned char* base = context->info->base;
    if (!base)
        return nullptr;
    return base + object->offset;
}

// Reached through the GOT slot at 0x7100c21690.
extern unsigned char* gBlock_c21690;
void part_handler_3a020(void* part);                              // 0x710003a020

// 0x710003d86c
void block_part_3d86c() {
    part_handler_3a020(gBlock_c21690 + 0xeaf80);
}

// Reached through the GOT slot at 0x7100c22bd8.
extern unsigned char* gBlock_c22bd8;
void part_handler_154484(void* part);                              // 0x7100154484

// 0x710018ed54
void block_part_18ed54() {
    part_handler_154484(gBlock_c22bd8 + 0x38188);
}

struct CountedShort50cf8 {
    unsigned char pad0[0x632];
    unsigned short value;  // +632
    unsigned char pad634[0x4];
    unsigned int count;  // +638
};

// 0x7100050cf8
unsigned short counted_short_50cf8(CountedShort50cf8* object) {
    if (object->count > 0x53)
        return 0;
    return object->value;
}

struct CountedShort51054 {
    unsigned char pad0[0x652];
    unsigned short value;  // +652
    unsigned char pad654[0x4];
    unsigned int count;  // +658
};

// 0x7100051054
unsigned short counted_short_51054(CountedShort51054* object) {
    if (object->count > 0x1b)
        return 0;
    return object->value;
}

struct HiddenOwner1dc018 {
    unsigned char pad0[0x10];
    void* child;  // +10
};
extern HiddenOwner1dc018* gHidden_c47f08 __attribute__((visibility("hidden"))); // 0x7100c47f08

// 0x71001dc018
void* hidden_child_1dc018() {
    if (gHidden_c47f08)
        return gHidden_c47f08->child;
    return nullptr;
}

struct HiddenOwner21cda8 {
    unsigned char pad0[0x438];
    void* child;  // +438
};
extern HiddenOwner21cda8* gHidden_c75d00 __attribute__((visibility("hidden"))); // 0x7100c75d00

// 0x710021cda8
void* hidden_child_21cda8() {
    if (gHidden_c75d00)
        return gHidden_c75d00->child;
    return nullptr;
}

struct Found1fbb78 {
    unsigned char data[0x28];
};
class FoundTable1fbb78 {
public:
    Found1fbb78* find(int index) {
        return static_cast<unsigned int>(index) < 0x406 ? &entries[index] : nullptr;
    }

    unsigned char pad[0x2f78];
    Found1fbb78 entries[0x406];
};

// 0x71001fbb78
Found1fbb78* found_1fbb78(FoundTable1fbb78* table, int index) {
    return table->find(index);
}

struct Found2015a8 {
    unsigned char data[0x88];
};
class FoundTable2015a8 {
public:
    Found2015a8* find(int index) {
        return static_cast<unsigned int>(index) < 0x28 ? &entries[index] : nullptr;
    }

    unsigned char pad[0x41a0];
    Found2015a8 entries[0x28];
};

// 0x71002015a8
Found2015a8* found_2015a8(FoundTable2015a8* table, int index) {
    return table->find(index);
}

struct Fallback204428 {
    unsigned char pad0[0x246c];
    unsigned char values[1];  // +246c
};

// 0x7100204428
unsigned char byte_or_first_204428(Fallback204428* object, int index) {
    return index > 0xef ? object->values[0] : object->values[index];
}

struct Fallback2045d4 {
    unsigned char pad0[0x25a8];
    unsigned char values[1];  // +25a8
};

// 0x71002045d4
unsigned char byte_or_first_2045d4(Fallback2045d4* object, int index) {
    return index > 0xfe ? object->values[0] : object->values[index];
}

struct Scales20b22c {
    unsigned char pad0[0x814];
    float values[1];  // +814
};

// 0x710020b22c
float scale_20b22c(Scales20b22c* object, int index) {
    if (static_cast<unsigned int>(index) <= 0x12b)
        return object->values[index];
    return 1.0f;
}

struct Scales20b264 {
    unsigned char pad0[0xce0];
    float values[1];  // +ce0
};

// 0x710020b264
float scale_20b264(Scales20b264* object, int index) {
    if (static_cast<unsigned int>(index) <= 0x3)
        return object->values[index];
    return 1.0f;
}

struct Level20c1c4 {
    unsigned char pad0[0x274];
    signed char value;  // +274
};

// 0x710020c1c4
int level_20c1c4(Level20c1c4* object) {
    int value = object->value;
    value = value < 0 ? 0 : value;
    return value > 0xf ? 0xf : value;
}

struct Level20c1e0 {
    unsigned char pad0[0x275];
    signed char value;  // +275
};

// 0x710020c1e0
int level_20c1e0(Level20c1e0* object) {
    int value = object->value;
    value = value < 0 ? 0 : value;
    return value > 0xf ? 0xf : value;
}

struct Words210664 {
    unsigned char pad0[0x1c];
    int values[9];  // +1c
};

// 0x7100210664
int word_or_none_210664(Words210664* object, unsigned int index) {
    if (index <= 8)
        return object->values[index];
    return -1;
}

struct Words210680 {
    unsigned char pad0[0x40];
    int values[9];  // +40
};

// 0x7100210680
int word_or_none_210680(Words210680* object, unsigned int index) {
    if (index <= 8)
        return object->values[index];
    return -1;
}

struct GItem257acc {
    unsigned char pad0[0x6c];
    int value;  // +6c
};
struct GItems257acc {
    unsigned char pad0[0x1070];
    GItem257acc* items[1];  // +1070
};
// Reached through the GOT slot at 0x7100c2a520.
extern GItems257acc* gItems_257acc;

// 0x7100257acc
int global_item_257acc(unsigned int index) {
    return gItems_257acc->items[index]->value;
}

struct GItem257ae8 {
    unsigned char pad0[0x70];
    int value;  // +70
};
struct GItems257ae8 {
    unsigned char pad0[0x1070];
    GItem257ae8* items[1];  // +1070
};
// Reached through the GOT slot at 0x7100c2a520.
extern GItems257ae8* gItems_257ae8;

// 0x7100257ae8
int global_item_257ae8(unsigned int index) {
    return gItems_257ae8->items[index]->value;
}

struct CheckedItems3af860 {
    unsigned char pad0[0x8];
    void* items[4];  // +8
    unsigned char pad28[0x20];
    unsigned char enabled;  // +48
};

// 0x71003af860
unsigned char item_ready_3af860(CheckedItems3af860* object, int index) {
    if (object->enabled)
        return check_object_1f7da0(object->items[index]);
    return 1;
}

struct CheckedItems3af9e0 {
    unsigned char pad0[0x8];
    void* items[4];  // +8
    unsigned char pad28[0x8];
    unsigned char enabled;  // +30
};

// 0x71003af9e0
unsigned char item_ready_3af9e0(CheckedItems3af9e0* object, int index) {
    if (object->enabled)
        return check_object_1f7da0(object->items[index]);
    return 1;
}

struct Kid434768 {
    unsigned char pad0[0x68];
    int value;  // +68
};
struct Kids434768 {
    unsigned char pad0[0x8];
    Kid434768* kids[1];  // +8
};

// 0x7100434768
int kid_value_434768(Kids434768* object, unsigned int index) {
    Kid434768* kid = object->kids[index];
    return kid ? kid->value : -1;
}

struct Kid434784 {
    unsigned char pad0[0x6c];
    int value;  // +6c
};
struct Kids434784 {
    unsigned char pad0[0x8];
    Kid434784* kids[1];  // +8
};

// 0x7100434784
int kid_value_434784(Kids434784* object, unsigned int index) {
    Kid434784* kid = object->kids[index];
    return kid ? kid->value : -1;
}

struct Masked45d664 {
    unsigned char pad0[0x1c];
    unsigned int flags;  // +1c
    unsigned char pad20[0xf8];
};
struct MaskedTable45d664 {
    Masked45d664 entries[2];  // +0
    unsigned char pad230[0x14];
    unsigned int mask;  // +244
};

// 0x710045d664
unsigned char entry_masked_45d664(MaskedTable45d664* table, unsigned int index) {
    return (table->entries[index].flags & table->mask) != 0;
}

struct Masked45d680 {
    unsigned char pad0[0x1c];
    unsigned int flags;  // +1c
    unsigned char pad20[0xf8];
};
struct MaskedTable45d680 {
    Masked45d680 entries[2];  // +0
    unsigned char pad230[0x18];
    unsigned int mask;  // +248
};

// 0x710045d680
unsigned char entry_masked_45d680(MaskedTable45d680* table, unsigned int index) {
    return (table->entries[index].flags & table->mask) != 0;
}

struct Linked4c6cf4 {
    unsigned char data[0xb0];
};
struct Linker4c6cf4 {
    unsigned char pad0[0x4];
    int index;  // +4
    Linked4c6cf4* record;  // +8
};
// Reached through the GOT slot at 0x7100c2cd88.
extern Linked4c6cf4 gLinked_c2cd88[];

// 0x71004c6cf4
void link_4c6cf4(Linker4c6cf4* object) {
    object->record = &gLinked_c2cd88[object->index];
}

struct Linked4e2600 {
    unsigned char data[0x50];
};
struct Linker4e2600 {
    unsigned char pad0[0x4];
    int index;  // +4
    Linked4e2600* record;  // +8
};
// Reached through the GOT slot at 0x7100c2cf08.
extern Linked4e2600 gLinked_c2cf08[];

// 0x71004e2600
void link_4e2600(Linker4e2600* object) {
    object->record = &gLinked_c2cf08[object->index];
}

struct ReadyPair57d3ac {
    unsigned char pad0[0x10];
    ValuePair pair;  // +10
    unsigned char pad20[0x140];
    unsigned char ready;  // +160
};

// 0x710057d3ac
void set_ready_pair_57d3ac(ReadyPair57d3ac* object, const ValuePair* value) {
    object->pair.second = value->second;
    object->pair.first = value->first;
    object->ready = 1;
}

struct ReadyPair57d3c8 {
    unsigned char pad0[0x20];
    ValuePair pair;  // +20
    unsigned char pad30[0x130];
    unsigned char ready;  // +160
};

// 0x710057d3c8
void set_ready_pair_57d3c8(ReadyPair57d3c8* object, const ValuePair* value) {
    object->pair.second = value->second;
    object->pair.first = value->first;
    object->ready = 1;
}

struct Block5cfbe4 {
    unsigned char pad0[0x10];
    unsigned int offset;  // +10
};
struct BlockOwner5cfbe4 {
    unsigned char pad0[0x10];
    Block5cfbe4* block;  // +10
};

// 0x71005cfbe4
void* block_data_5cfbe4(BlockOwner5cfbe4* owner) {
    Block5cfbe4* block = owner->block;
    if (!block)
        return nullptr;
    return reinterpret_cast<unsigned char*>(block) + block->offset;
}

struct Block5cfc34 {
    unsigned char pad0[0x8];
    unsigned int offset;  // +8
};
struct BlockOwner5cfc34 {
    unsigned char pad0[0x18];
    Block5cfc34* block;  // +18
};

// 0x71005cfc34
void* block_data_5cfc34(BlockOwner5cfc34* owner) {
    Block5cfc34* block = owner->block;
    if (!block)
        return nullptr;
    return reinterpret_cast<unsigned char*>(block) + block->offset;
}

class Forwardedca2d8 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual int result();
};
int pass_result_6f32c(int result);                              // 0x710006f32c

// 0x71000ca2d8
int forward_result_ca2d8(Forwardedca2d8* object) {
    return pass_result_6f32c(object->result());
}

class Forwardedcedc4 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void v40();
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void v60();
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void v80();
    virtual void v88();
    virtual void v90();
    virtual void v98();
    virtual void va0();
    virtual void va8();
    virtual void vb0();
    virtual void vb8();
    virtual void vc0();
    virtual void vc8();
    virtual void vd0();
    virtual void vd8();
    virtual void ve0();
    virtual void ve8();
    virtual void vf0();
    virtual void vf8();
    virtual void v100();
    virtual void v108();
    virtual void v110();
    virtual void v118();
    virtual void v120();
    virtual void v128();
    virtual void v130();
    virtual void v138();
    virtual void v140();
    virtual void v148();
    virtual void v150();
    virtual void v158();
    virtual void v160();
    virtual void v168();
    virtual void v170();
    virtual void v178();
    virtual void v180();
    virtual void v188();
    virtual void v190();
    virtual void v198();
    virtual void v1a0();
    virtual void v1a8();
    virtual void v1b0();
    virtual void v1b8();
    virtual void v1c0();
    virtual void v1c8();
    virtual void v1d0();
    virtual void v1d8();
    virtual void v1e0();
    virtual void v1e8();
    virtual void v1f0();
    virtual void v1f8();
    virtual void v200();
    virtual void v208();
    virtual void v210();
    virtual void v218();
    virtual void v220();
    virtual void v228();
    virtual void v230();
    virtual void v238();
    virtual void v240();
    virtual void v248();
    virtual void v250();
    virtual void v258();
    virtual void v260();
    virtual void v268();
    virtual void v270();
    virtual void v278();
    virtual void v280();
    virtual void v288();
    virtual void v290();
    virtual void v298();
    virtual void v2a0();
    virtual void v2a8();
    virtual void v2b0();
    virtual void v2b8();
    virtual void v2c0();
    virtual void v2c8();
    virtual void v2d0();
    virtual void v2d8();
    virtual void v2e0();
    virtual void v2e8();
    virtual void v2f0();
    virtual void v2f8();
    virtual void v300();
    virtual void v308();
    virtual void v310();
    virtual void v318();
    virtual void v320();
    virtual void v328();
    virtual void v330();
    virtual void v338();
    virtual void v340();
    virtual void v348();
    virtual void v350();
    virtual void v358();
    virtual void v360();
    virtual void v368();
    virtual void v370();
    virtual void v378();
    virtual void v380();
    virtual void v388();
    virtual void v390();
    virtual void v398();
    virtual void v3a0();
    virtual void v3a8();
    virtual void v3b0();
    virtual void v3b8();
    virtual void v3c0();
    virtual void v3c8();
    virtual void v3d0();
    virtual void v3d8();
    virtual void v3e0();
    virtual void v3e8();
    virtual int result();
};
int pass_result_e4f4(int result);                              // 0x710000e4f4

// 0x71000cedc4
int forward_result_cedc4(Forwardedcedc4* object) {
    return pass_result_e4f4(object->result());
}
