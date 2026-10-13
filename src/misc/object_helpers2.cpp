// More accessors from tools/family_scan.py --immediates: dispose-and-free (the shape of
// dispose_40001c in misc/small_families2.cpp), resolved item calls, byte-set bit updates, grid cells
// with a default, offset tables filled from a hook, special-item checks and ring-buffer pops. Each
// group differs only in offsets, slots, limits and globals; types and functions are named after their
// address. Status: matching/README.md.

class FreeingList {
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
    virtual void free(void* object);
};

class Disposable49bfac {
public:
    virtual void v00();
    virtual void dispose();

    unsigned char pad8[0x10];
    FreeingList* allocator;   // +18
};

// 0x710049bfac
void dispose_49bfac(Disposable49bfac* object) {
    FreeingList* allocator = object->allocator;
    if (object)
        object->dispose();
    allocator->free(object);
}

class Disposable4a1d88 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void dispose();

    unsigned char pad8[0x30];
    FreeingList* allocator;   // +38
};

// 0x71004a1d88
void dispose_4a1d88(Disposable4a1d88* object) {
    FreeingList* allocator = object->allocator;
    if (object)
        object->dispose();
    allocator->free(object);
}

class Disposable4c9c58 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void dispose();

    unsigned char pad8[0x0];
    FreeingList* allocator;   // +8
};

// 0x71004c9c58
void dispose_4c9c58(Disposable4c9c58* object) {
    FreeingList* allocator = object->allocator;
    if (object)
        object->dispose();
    allocator->free(object);
}

class Disposable594584 {
public:
    virtual void v00();
    virtual void dispose();

    unsigned char pad8[0x10];
    FreeingList* allocator;   // +18
};

// 0x7100594584
void dispose_594584(Disposable594584* object) {
    FreeingList* allocator = object->allocator;
    if (object)
        object->dispose();
    allocator->free(object);
}

class Disposable5bc8a8 {
public:
    virtual void v00();
    virtual void dispose();

    unsigned char pad8[0x138];
    FreeingList* allocator;   // +140
};

// 0x71005bc8a8
void dispose_5bc8a8(Disposable5bc8a8* object) {
    FreeingList* allocator = object->allocator;
    if (object)
        object->dispose();
    allocator->free(object);
}

class Applied2113c {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void apply(float value);
};
class Resolvable2113c {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual Applied2113c* resolve();
};
struct ItemSet2113c {
    unsigned char pad[0x138];
    Resolvable2113c* items[0x6d7]; // +138
};

// 0x710002113c
void apply_item_2113c(ItemSet2113c* set, short id, float value) {
    Resolvable2113c* item = static_cast<unsigned short>(id) <= 0x6d6 ? set->items[id] : nullptr;
    item->resolve()->apply(value);
}

class Applied2118c {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void apply(float value);
};
class Resolvable2118c {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual Applied2118c* resolve();
};
struct ItemSet2118c {
    unsigned char pad[0x138];
    Resolvable2118c* items[0x6d7]; // +138
};

// 0x710002118c
void apply_item_2118c(ItemSet2118c* set, short id, float value) {
    Resolvable2118c* item = static_cast<unsigned short>(id) <= 0x6d6 ? set->items[id] : nullptr;
    item->resolve()->apply(value);
}

class Applied22d08 {
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
    virtual void apply(float value);
};
class Resolvable22d08 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual Applied22d08* resolve();
};
struct ItemSet22d08 {
    unsigned char pad[0x138];
    Resolvable22d08* items[0x6d7]; // +138
};

// 0x7100022d08
void apply_item_22d08(ItemSet22d08* set, short id, float value) {
    Resolvable22d08* item = static_cast<unsigned short>(id) <= 0x6d6 ? set->items[id] : nullptr;
    item->resolve()->apply(value);
}

class Applied230c8 {
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
    virtual void apply(float value);
};
class Resolvable230c8 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual Applied230c8* resolve();
};
struct ItemSet230c8 {
    unsigned char pad[0x138];
    Resolvable230c8* items[0x6d7]; // +138
};

// 0x71000230c8
void apply_item_230c8(ItemSet230c8* set, short id, float value) {
    Resolvable230c8* item = static_cast<unsigned short>(id) <= 0x6d6 ? set->items[id] : nullptr;
    item->resolve()->apply(value);
}

struct ByteFlags1a7f88 {
    unsigned char pad[0x2463];
    unsigned char bits[1];    // +2463
};

// 0x71001a7f88
void set_byte_flag_1a7f88(ByteFlags1a7f88* set, unsigned int id, unsigned char on) {
    if (id > 0x7f)
        return;
    if (on)
        set->bits[id >> 3] |= 1 << (id & 7);
    else
        set->bits[id >> 3] &= ~(1 << (id & 7));
}

struct ByteFlags2027b0 {
    unsigned char pad[0x1990];
    unsigned char bits[1];    // +1990
};

// 0x71002027b0
void set_byte_flag_2027b0(ByteFlags2027b0* set, unsigned int id, unsigned char on) {
    if (id > 0xc)
        return;
    if (on)
        set->bits[id >> 3] |= 1 << (id & 7);
    else
        set->bits[id >> 3] &= ~(1 << (id & 7));
}

struct ByteFlags203b88 {
    unsigned char pad[0x195a];
    unsigned char bits[1];    // +195a
};

// 0x7100203b88
void set_byte_flag_203b88(ByteFlags203b88* set, unsigned int id, unsigned char on) {
    if (id > 0x7f)
        return;
    if (on)
        set->bits[id >> 3] |= 1 << (id & 7);
    else
        set->bits[id >> 3] &= ~(1 << (id & 7));
}

struct ByteFlags203c10 {
    unsigned char pad[0x196a];
    unsigned char bits[1];    // +196a
};

// 0x7100203c10
void set_byte_flag_203c10(ByteFlags203c10* set, unsigned int id, unsigned char on) {
    if (id > 0x12b)
        return;
    if (on)
        set->bits[id >> 3] |= 1 << (id & 7);
    else
        set->bits[id >> 3] &= ~(1 << (id & 7));
}

struct GridCell {
    unsigned char bytes[0x20];
};
extern const GridCell kDefaultCell __attribute__((visibility("hidden"))); // 0x7100be2098
struct CellGrid {
    unsigned char pad[0x40];
    GridCell* cells;          // +40
    unsigned char pad48[8];
    unsigned int width;       // +50
    unsigned int height;      // +54
};

// 0x710045664c
unsigned char cell_byte_45664c(CellGrid* grid, unsigned int x, unsigned int y) {
    const GridCell& cell = x < grid->width && y < grid->height ? grid->cells[x + y * grid->width] : kDefaultCell;
    return cell.bytes[0x2];
}

// 0x7100456af4
unsigned char cell_byte_456af4(CellGrid* grid, unsigned int x, unsigned int y) {
    const GridCell& cell = x < grid->width && y < grid->height ? grid->cells[x + y * grid->width] : kDefaultCell;
    return cell.bytes[0xd];
}

// 0x7100456b40
unsigned char cell_byte_456b40(CellGrid* grid, unsigned int x, unsigned int y) {
    const GridCell& cell = x < grid->width && y < grid->height ? grid->cells[x + y * grid->width] : kDefaultCell;
    return cell.bytes[0xf];
}

// 0x7100457fb8
unsigned char cell_byte_457fb8(CellGrid* grid, unsigned int x, unsigned int y) {
    const GridCell& cell = x < grid->width && y < grid->height ? grid->cells[x + y * grid->width] : kDefaultCell;
    return cell.bytes[0x13];
}

struct HookSource527070 {
    unsigned char pad[0xb8];
    void* handle;             // +b8
};
struct HookTable527070 {
    unsigned char pad[0x58];
    long* offsets;            // +58
    unsigned char pad60[0x18];
    HookSource527070* source;   // +78
    unsigned char pad80[0x8];
    long base;                // +88
};
// Reached through the GOT slot at 0x7100c2c730.
extern long (*gOffsetHook_c2c730)(void* handle);

// 0x7100527070
void fill_offset_527070(HookTable527070* table, int index) {
    void* handle = table->source->handle;
    long offset = gOffsetHook_c2c730(handle);
    table->offsets[index] = table->base + offset;
}

struct HookSource5271c8 {
    unsigned char pad[0xb8];
    void* handle;             // +b8
};
struct HookTable5271c8 {
    unsigned char pad[0x10];
    long* offsets;            // +10
    unsigned char pad18[0x18];
    HookSource5271c8* source;   // +30
    unsigned char pad38[0x8];
    long base;                // +40
};
// Reached through the GOT slot at 0x7100c2c730.
extern long (*gOffsetHook_c2c730)(void* handle);

// 0x71005271c8
void fill_offset_5271c8(HookTable5271c8* table, int index) {
    void* handle = table->source->handle;
    long offset = gOffsetHook_c2c730(handle);
    table->offsets[index] = table->base + offset;
}

struct HookSource5275a8 {
    unsigned char pad[0xb8];
    void* handle;             // +b8
};
struct HookTable5275a8 {
    unsigned char pad[0x58];
    long* offsets;            // +58
    unsigned char pad60[0x18];
    HookSource5275a8* source;   // +78
    unsigned char pad80[0x0];
    long base;                // +80
};
// Reached through the GOT slot at 0x7100c2c748.
extern long (*gOffsetHook_c2c748)(void* handle);

// 0x71005275a8
void fill_offset_5275a8(HookTable5275a8* table, int index) {
    void* handle = table->source->handle;
    long offset = gOffsetHook_c2c748(handle);
    table->offsets[index] = table->base + offset;
}

struct HookSource527700 {
    unsigned char pad[0xb8];
    void* handle;             // +b8
};
struct HookTable527700 {
    unsigned char pad[0x10];
    long* offsets;            // +10
    unsigned char pad18[0x18];
    HookSource527700* source;   // +30
    unsigned char pad38[0x0];
    long base;                // +38
};
// Reached through the GOT slot at 0x7100c2c748.
extern long (*gOffsetHook_c2c748)(void* handle);

// 0x7100527700
void fill_offset_527700(HookTable527700* table, int index) {
    void* handle = table->source->handle;
    long offset = gOffsetHook_c2c748(handle);
    table->offsets[index] = table->base + offset;
}

struct SpecialEntry {
    int state;
    short id;
    short pad6;
};
struct SpecialItems {
    SpecialEntry entries[0x2e4];
};
struct ShortList20b3a0;
ShortList20b3a0* load_global_20b29c();                                     // 0x710020b29c
int short_entry_20b3a0(ShortList20b3a0* list, int index);                  // 0x710020b3a0

// 0x71001ff358
unsigned char special_in_state_1ff358(SpecialItems* items, int item) {
    if (static_cast<unsigned int>(item) <= 0x2e3 && items->entries[item].state == 6) {
        ShortList20b3a0* list = load_global_20b29c();
        short id = items->entries[item].id;
        return short_entry_20b3a0(list, static_cast<unsigned short>(id) < 0x80 ? id : -1) == 0;
    }
    return 0;
}

// 0x71001ff3bc
unsigned char special_in_state_1ff3bc(SpecialItems* items, int item) {
    if (static_cast<unsigned int>(item) <= 0x2e3 && items->entries[item].state == 6) {
        ShortList20b3a0* list = load_global_20b29c();
        short id = items->entries[item].id;
        return short_entry_20b3a0(list, static_cast<unsigned short>(id) < 0x80 ? id : -1) == 2;
    }
    return 0;
}

// 0x71001ff420
unsigned char special_in_state_1ff420(SpecialItems* items, int item) {
    if (static_cast<unsigned int>(item) <= 0x2e3 && items->entries[item].state == 6) {
        ShortList20b3a0* list = load_global_20b29c();
        short id = items->entries[item].id;
        return short_entry_20b3a0(list, static_cast<unsigned short>(id) < 0x80 ? id : -1) == 1;
    }
    return 0;
}

struct Ring21ee8 {
    unsigned char pad[0xe7f8];
    unsigned short* values;   // +e7f8
    int capacity;             // +e800
    int count;                // +e804
    int head;                 // +e808
};

// 0x7100021ee8
unsigned short ring_pop_21ee8(Ring21ee8* ring) {
    if (!ring->count)
        return 0xffff;
    int head = ring->head;
    unsigned short value = ring->values[head];
    ring->head = (head + 1) % ring->capacity;
    --ring->count;
    return value;
}

struct Ring21f48 {
    unsigned char pad[0xe828];
    unsigned short* values;   // +e828
    int capacity;             // +e830
    int count;                // +e834
    int head;                 // +e838
};

// 0x7100021f48
unsigned short ring_pop_21f48(Ring21f48* ring) {
    if (!ring->count)
        return 0xffff;
    int head = ring->head;
    unsigned short value = ring->values[head];
    ring->head = (head + 1) % ring->capacity;
    --ring->count;
    return value;
}

struct Ring21fa8 {
    unsigned char pad[0xe888];
    unsigned short* values;   // +e888
    int capacity;             // +e890
    int count;                // +e894
    int head;                 // +e898
};

// 0x7100021fa8
unsigned short ring_pop_21fa8(Ring21fa8* ring) {
    if (!ring->count)
        return 0xffff;
    int head = ring->head;
    unsigned short value = ring->values[head];
    ring->head = (head + 1) % ring->capacity;
    --ring->count;
    return value;
}
