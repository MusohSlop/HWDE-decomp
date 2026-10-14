// More single functions from tools/rank_targets.py (small leaves that matched code calls). Names are
// descriptive placeholders; addresses are in the comments. Status: matching/README.md.

void begin_52ada0(void* object, int mode);                                  // 0x710052ada0

// 0x710052ad98
void begin_default_52ad98(void* object) {
    begin_52ada0(object, 0);
}

void open_4f9aa0(void* a, void* b, void* c, void* extra);                   // 0x71004f9aa0

// 0x71004f9a98
void open_plain_4f9a98(void* a, void* b, void* c) {
    open_4f9aa0(a, b, c, nullptr);
}

struct Cursor5c3a1c {
    unsigned char pad[0x50];
    long current;             // +50
    long start;               // +58
};

// 0x71005c3a1c
void rewind_5c3a1c(Cursor5c3a1c* cursor) {
    cursor->current = cursor->start;
}

struct Triple53d388 {
    unsigned char pad[8];
    long first;               // +08
    long second;              // +10
    long third;               // +18
};

// 0x710053d388
void clear_53d388(Triple53d388* object) {
    object->second = 0;
    object->third = 0;
    object->first = 0;
}

struct Slot466e20 {
    unsigned char used;       // +00
    unsigned char pad1[7];
    long first;               // +08
    long second;              // +10
};

// 0x7100466e20
void clear_slot_466e20(Slot466e20* slot) {
    slot->used = 0;
    slot->first = 0;
    slot->second = 0;
}

// 0x7100466f24
void clear_slot_466f24(Slot466e20* slot) {
    slot->used = 0;
    slot->first = 0;
    slot->second = 0;
}

// 0x7100467004
void clear_slot_467004(Slot466e20* slot) {
    slot->used = 0;
    slot->first = 0;
    slot->second = 0;
}

struct Holder5155a4 {
    unsigned char pad[0x10];
    long value;               // +10
};

// 0x71005155a4
int store_5155a4(Holder5155a4* holder, const long* value) {
    holder->value = *value;
    return 1;
}

struct Counter471e90 {
    unsigned char pad[0x10];
    int count;                // +10
};

// 0x7100471e90
void release_471e90(Counter471e90* counter) {
    --counter->count;
}

struct Count1a8e1c {
    unsigned char pad[0xc];
    unsigned int count;       // +0c
};

// 0x71001a8e1c
unsigned char has_many_1a8e1c(Count1a8e1c* object) {
    return object->count > 1;
}

struct Flags16f29c {
    unsigned long flags;
};

// 0x710016f29c
void clear_flags_16f29c(Flags16f29c* object, unsigned long bits) {
    object->flags &= ~bits;
}

struct Range_cf5c4 {
    unsigned char pad[8];
    long first;               // +08
    long second;              // +10
    long third;               // +18
};

// 0x71000cf5c4
void invalidate_cf5c4(Range_cf5c4* range) {
    range->second = -1;
    range->third = -1;
    range->first = -1;
}

// Vtable through the GOT slot at 0x7100c233b0.
class Link218c18 {
public:
    Link218c18();
    virtual ~Link218c18();

    void* target;             // +08
};

// 0x7100218c18
Link218c18::Link218c18() : target(nullptr) {}

struct Once527a0 {
    unsigned char pad[0x20];
    unsigned int flags;       // +20
};

// 0x71000527a0
void mark_527a0(Once527a0* object) {
    if (!(object->flags & 1))
        object->flags |= 1;
}

void configure_4a764(void* part, int mode, int limit);                      // 0x710004a764

// 0x71000475d8
void configure_475d8(unsigned char* object) {
    configure_4a764(object + 0x10770, 3, 0x2bc);
}

// Reached through the GOT slots at 0x7100c2dc90 and 0x7100c2dca0.
extern void (*gNotify_c2dc90)(void* object, int kind, void* context);
extern void* gNotifyContext_c2dca0;

// 0x71005d4380
void notify_5d4380(void* object) {
    gNotify_c2dc90(object, 4, gNotifyContext_c2dca0);
}

class DataChunk {
public:
    unsigned char set(const void* data);                                    // 0x7100218c34

    void* vtable_slot;        // +00
    const unsigned int* data; // +08
};

// 0x7100218c34
unsigned char DataChunk::set(const void* source) {
    if (!source)
        return 0;
    data = static_cast<const unsigned int*>(source);
    unsigned int magic = *data;
    return (magic & 0xffff0000) == 0x130000 && (magic & 0xffff) == 0x4c58;
}

// The fields sit in a non-virtual base, so they are cleared before the vtable pointer is stored.
struct QueueBase5325e4 {
    QueueBase5325e4() {
        count = 0;
        head = nullptr;
        size = 0;
        first = nullptr;
        second = nullptr;
    }

    int count;                // +08
    unsigned char padc[4];
    void* head;               // +10
    unsigned char pad18[8];
    void* first;              // +20
    void* second;             // +28
    int size;                 // +30
};
// Vtable through the GOT slot at 0x7100c2d288.
class Queue5325e4 : public QueueBase5325e4 {
public:
    Queue5325e4();
    virtual ~Queue5325e4();
};

// 0x71005325e4
Queue5325e4::Queue5325e4() {}

struct OwnerBase5c2d24 {
    OwnerBase5c2d24() : owner(nullptr) {}

    unsigned char pad8[0x18];
    void* owner;              // +20
};
// Vtable through the GOT slot at 0x7100c2db68.
class Owned5c2d24 : public OwnerBase5c2d24 {
public:
    Owned5c2d24();
    virtual ~Owned5c2d24();
};

// 0x71005c2d24
Owned5c2d24::Owned5c2d24() {}

struct PairBase_ade30 {
    PairBase_ade30() : value(nullptr), count(0) {}

    void* value;              // +08
    int count;                // +10
};
// Vtable through the GOT slot at 0x7100c224d0.
class Pair_ade30 : public PairBase_ade30 {
public:
    Pair_ade30();
    virtual ~Pair_ade30();
};

// 0x71000ade30
Pair_ade30::Pair_ade30() {}
