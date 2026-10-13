// More tiny accessors found by tools/family_scan.py --immediates, one group per shape: fallback
// slots, clamped fields, offset ids, capped 16-bit fields, hooked forwards, constructors that clear a
// base field before the vtable pointer, bounded 16-bit reads, entry addresses, list appends, byte
// stores, entry fields, sentinel tests and pointer tests. Each group differs only in its offsets,
// limits and globals; types and functions are named after their address. Status: matching/README.md.

struct SlotTable34c660 {
    unsigned char pad[0x194f34];
    int current;              // +194f34
    unsigned char pad194f38[0x0];
    int values[4];            // +194f38
};

// 0x710034c660
int slot_value_34c660(SlotTable34c660* table, int slot) {
    if (static_cast<unsigned int>(slot) >= 4)
        slot = table->current;
    return table->values[slot];
}

struct SlotTable34f7a4 {
    unsigned char pad[0x194f34];
    int current;              // +194f34
    unsigned char pad194f38[0x10];
    int values[4];            // +194f48
};

// 0x710034f7a4
int slot_value_34f7a4(SlotTable34f7a4* table, int slot) {
    if (static_cast<unsigned int>(slot) >= 4)
        slot = table->current;
    return table->values[slot];
}

struct SlotTable350290 {
    unsigned char pad[0x194f34];
    int current;              // +194f34
    unsigned char pad194f38[0x20];
    int values[4];            // +194f58
};

// 0x7100350290
int slot_value_350290(SlotTable350290* table, int slot) {
    if (static_cast<unsigned int>(slot) >= 4)
        slot = table->current;
    return table->values[slot];
}

struct Clamp2_19b680 {
    unsigned char pad[0x14];
    int value;                // +14
};

// 0x710019b680
int clamp_two_19b680(Clamp2_19b680* object) {
    int value = object->value;
    value = value < 0 ? 0 : value;
    return value > 2 ? 2 : value;
}

struct Clamp2_19b928 {
    unsigned char pad[0x4];
    int value;                // +4
};

// 0x710019b928
int clamp_two_19b928(Clamp2_19b928* object) {
    int value = object->value;
    value = value < 0 ? 0 : value;
    return value > 2 ? 2 : value;
}

struct Clamp2_19b9f4 {
    unsigned char pad[0x20];
    int value;                // +20
};

// 0x710019b9f4
int clamp_two_19b9f4(Clamp2_19b9f4* object) {
    int value = object->value;
    value = value < 0 ? 0 : value;
    return value > 2 ? 2 : value;
}

// 0x710023a458
int offset_id_23a458(void* self, int id) {
    if (static_cast<unsigned int>(id) > 0x3f)
        return -1;
    int value = id + 0xe26;
    if (value > 0xe51)
        return -1;
    return value;
}

// 0x710023a474
int offset_id_23a474(void* self, int id) {
    if (static_cast<unsigned int>(id) > 0x95)
        return -1;
    int value = id + 0xdc5;
    if (value > 0xe23)
        return -1;
    return value;
}

// 0x710023a4a0
int offset_id_23a4a0(void* self, int id) {
    if (static_cast<unsigned int>(id) > 0x10c)
        return -1;
    int value = id + 0xe53;
    if (value > 0xf5f)
        return -1;
    return value;
}

struct Capped1fe2dc {
    unsigned char pad[0x8];
    unsigned short value;     // +8
};

// 0x71001fe2dc
unsigned short capped_1fe2dc(Capped1fe2dc* object) {
    unsigned short value = object->value;
    return value > 0x1f4 ? 0x1f4 : value;
}

struct Capped1fe2f0 {
    unsigned char pad[0xa];
    unsigned short value;     // +a
};

// 0x71001fe2f0
unsigned short capped_1fe2f0(Capped1fe2f0* object) {
    unsigned short value = object->value;
    return value > 0x1f4 ? 0x1f4 : value;
}

struct Capped1fe304 {
    unsigned char pad[0xc];
    unsigned short value;     // +c
};

// 0x71001fe304
unsigned short capped_1fe304(Capped1fe304* object) {
    unsigned short value = object->value;
    return value > 0x1f4 ? 0x1f4 : value;
}

struct Capped1fe318 {
    unsigned char pad[0x10];
    unsigned short value;     // +10
};

// 0x71001fe318
unsigned short capped_1fe318(Capped1fe318* object) {
    unsigned short value = object->value;
    return value > 0x1f4 ? 0x1f4 : value;
}

struct HookArg461324 {
    unsigned char pad[0x8];
    void* value;              // +8
};
// Reached through the GOT slot at 0x7100c2bc08.
extern void (*gHook_c2bc08)(void* value);

// 0x7100461324
void hook_forward_461324(HookArg461324* object) {
    void* value = object->value;
    gHook_c2bc08(value);
}

struct HookArg462638 {
    void* value;              // +0
};
// Reached through the GOT slot at 0x7100c2be00.
extern void (*gHook_c2be00)(void* value);

// 0x7100462638
void hook_forward_462638(HookArg462638* object) {
    void* value = object->value;
    gHook_c2be00(value);
}

struct HookArg5f90ec {
    unsigned char pad[0x8];
    void* value;              // +8
};
// Reached through the GOT slot at 0x7100c2bf68.
extern void (*gHook_c2bf68)(void* value);

// 0x71005f90ec
void hook_forward_5f90ec(HookArg5f90ec* object) {
    void* value = object->value;
    gHook_c2bf68(value);
}

struct HookArg5f9100 {
    unsigned char pad[0x8];
    void* value;              // +8
};
// Reached through the GOT slot at 0x7100c2bf70.
extern void (*gHook_c2bf70)(void* value);

// 0x71005f9100
void hook_forward_5f9100(HookArg5f9100* object) {
    void* value = object->value;
    gHook_c2bf70(value);
}

// The count sits in a non-virtual base, so it is cleared before the vtable pointer is stored.
struct CountBase6d65c {
    CountBase6d65c() : count(0) {}

    int count;                // +8
};
// Vtable through the GOT slot at 0x7100c220e8.
class Counted6d65c : public CountBase6d65c {
public:
    Counted6d65c();
    virtual ~Counted6d65c();
};

// 0x710006d65c
Counted6d65c::Counted6d65c() {}

// The count sits in a non-virtual base, so it is cleared before the vtable pointer is stored.
struct CountBase337bac {
    CountBase337bac() : count(0) {}

    int count;                // +8
};
// Vtable through the GOT slot at 0x7100c2ae80.
class Counted337bac : public CountBase337bac {
public:
    Counted337bac();
    virtual ~Counted337bac();
};

// 0x7100337bac
Counted337bac::Counted337bac() {}

// The count sits in a non-virtual base, so it is cleared before the vtable pointer is stored.
struct CountBase57cda8 {
    CountBase57cda8() : count(0) {}

    unsigned char pad[0x150];
    int count;                // +158
};
// Vtable through the GOT slot at 0x7100c2b760.
class Counted57cda8 : public CountBase57cda8 {
public:
    Counted57cda8();
    virtual ~Counted57cda8();
};

// 0x710057cda8
Counted57cda8::Counted57cda8() {}

struct ShortList20b3a0 {
    short values[0x80];
};

// 0x710020b3a0
int short_entry_20b3a0(ShortList20b3a0* list, int index) {
    if (static_cast<unsigned int>(index) <= 0x7f)
        return list->values[index];
    return -1;
}

struct ShortList20b860 {
    short values[0x40];
};

// 0x710020b860
int short_entry_20b860(ShortList20b860* list, int index) {
    if (static_cast<unsigned int>(index) <= 0x3f)
        return list->values[index];
    return -1;
}

struct ShortList210470 {
    short values[0x5a];
};

// 0x7100210470
int short_entry_210470(ShortList210470* list, int index) {
    if (static_cast<unsigned int>(index) <= 0x59)
        return list->values[index];
    return -1;
}

struct BigEntry20e204 {
    unsigned char data[0x270];
};
class BigTable20e204 {
public:
    BigEntry20e204* find(int index) {
        return static_cast<unsigned int>(index) < 0x12c ? &entries[index] : nullptr;
    }

    unsigned char pad[8];
    BigEntry20e204 entries[0x12c];   // +08
};

// 0x710020e204
BigEntry20e204* entry_20e204(BigTable20e204* table, int index) {
    return table->find(index);
}

struct BigEntry20eea0 {
    unsigned char data[0x270];
};
class BigTable20eea0 {
public:
    BigEntry20eea0* find(int index) {
        return static_cast<unsigned int>(index) < 0x5a0 ? &entries[index] : nullptr;
    }

    unsigned char pad[8];
    BigEntry20eea0 entries[0x5a0];   // +08
};

// 0x710020eea0
BigEntry20eea0* entry_20eea0(BigTable20eea0* table, int index) {
    return table->find(index);
}

struct BigEntry20eeb8 {
    unsigned char data[0x270];
};
class BigTable20eeb8 {
public:
    BigEntry20eeb8* find(int index) {
        return static_cast<unsigned int>(index) < 0x5a0 ? &entries[index] : nullptr;
    }

    unsigned char pad[8];
    BigEntry20eeb8 entries[0x5a0];   // +08
};

// 0x710020eeb8
BigEntry20eeb8* entry_20eeb8(BigTable20eeb8* table, int index) {
    return table->find(index);
}

struct ListNode53c784 {
    unsigned char pad[0x80];
    ListNode53c784* owner;    // +80
    ListNode53c784* next;     // +88
};

// 0x710053c784
void append_node_53c784(ListNode53c784* list, ListNode53c784* node) {
    ListNode53c784* last;
    do {
        last = list;
        node->owner = last;
        list = last->next;
    } while (list);
    last->next = node;
}

struct ListNode53c79c {
    unsigned char pad[0x90];
    ListNode53c79c* owner;    // +90
    ListNode53c79c* next;     // +98
};

// 0x710053c79c
void append_node_53c79c(ListNode53c79c* list, ListNode53c79c* node) {
    ListNode53c79c* last;
    do {
        last = list;
        node->owner = last;
        list = last->next;
    } while (list);
    last->next = node;
}

struct ListNode53c7b4 {
    unsigned char pad[0xa8];
    ListNode53c7b4* owner;    // +a8
    ListNode53c7b4* next;     // +b0
};

// 0x710053c7b4
void append_node_53c7b4(ListNode53c7b4* list, ListNode53c7b4* node) {
    ListNode53c7b4* last;
    do {
        last = list;
        node->owner = last;
        list = last->next;
    } while (list);
    last->next = node;
}

struct ByteFieldf21c8 {
    unsigned char pad[0x4055a];
    unsigned char value;      // +4055a
};

// 0x71000f21c8
void set_byte_f21c8(ByteFieldf21c8* object, unsigned char value) {
    object->value = value;
}

struct ByteField1edcf0 {
    unsigned char pad[0x1681c];
    unsigned char value;      // +1681c
};

// 0x71001edcf0
void set_byte_1edcf0(ByteField1edcf0* object, unsigned char value) {
    object->value = value;
}

struct ByteField386188 {
    unsigned char pad[0x17b15];
    unsigned char value;      // +17b15
};

// 0x7100386188
void set_byte_386188(ByteField386188* object, unsigned char value) {
    object->value = value;
}

struct ByteField38c3d8 {
    unsigned char pad[0x2e5ea8];
    unsigned char value;      // +2e5ea8
};

// 0x710038c3d8
void set_byte_38c3d8(ByteField38c3d8* object, unsigned char value) {
    object->value = value;
}

struct FieldEntry13e678 {
    unsigned char pad[0x20];
    int value;                // +20
    unsigned char pad24[0x4];
};

// 0x710013e678
int entry_field_13e678(FieldEntry13e678* entries, unsigned int index) {
    return entries[index].value;
}

struct FieldEntry45d610 {
    unsigned char pad[0x18];
    int value;                // +18
    unsigned char pad1c[0xfc];
};

// 0x710045d610
int entry_field_45d610(FieldEntry45d610* entries, unsigned int index) {
    return entries[index].value;
}

struct FieldEntry45d620 {
    unsigned char pad[0x1c];
    int value;                // +1c
    unsigned char pad20[0xf8];
};

// 0x710045d620
int entry_field_45d620(FieldEntry45d620* entries, unsigned int index) {
    return entries[index].value;
}

struct FieldEntry45d630 {
    unsigned char pad[0x20];
    int value;                // +20
    unsigned char pad24[0xf4];
};

// 0x710045d630
int entry_field_45d630(FieldEntry45d630* entries, unsigned int index) {
    return entries[index].value;
}

struct Sentinel19b608 {
    int value;                // +0
};

// 0x710019b608
unsigned char is_set_19b608(Sentinel19b608* object) {
    return object->value != -1;
}

struct Sentinel19b8c0 {
    int value;                // +0
};

// 0x710019b8c0
unsigned char is_set_19b8c0(Sentinel19b8c0* object) {
    return object->value != -1;
}

struct Sentinel19b8ec {
    unsigned char pad[0x4];
    int value;                // +4
};

// 0x710019b8ec
unsigned char is_set_19b8ec(Sentinel19b8ec* object) {
    return object->value != -1;
}

struct Sentinel19bb38 {
    unsigned char pad[0x34];
    int value;                // +34
};

// 0x710019bb38
unsigned char is_set_19bb38(Sentinel19bb38* object) {
    return object->value != -1;
}

struct PtrHolder244860 {
    unsigned char pad[0x28];
    void* pointer;            // +28
};

// 0x7100244860
unsigned char has_pointer_244860(PtrHolder244860* object) {
    return object->pointer != nullptr;
}

struct PtrHolder3c7b40 {
    unsigned char pad[0xa0];
    void* pointer;            // +a0
};

// 0x71003c7b40
unsigned char has_pointer_3c7b40(PtrHolder3c7b40* object) {
    return object->pointer != nullptr;
}

struct PtrHolder3c8488 {
    unsigned char pad[0x28];
    void* pointer;            // +28
};

// 0x71003c8488
unsigned char has_pointer_3c8488(PtrHolder3c8488* object) {
    return object->pointer != nullptr;
}

struct PtrHolder434800 {
    unsigned char pad[0x88];
    void* pointer;            // +88
};

// 0x7100434800
unsigned char has_pointer_434800(PtrHolder434800* object) {
    return object->pointer != nullptr;
}
