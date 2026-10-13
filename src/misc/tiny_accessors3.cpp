// A third set of tiny accessors found by tools/family_scan.py --immediates: byte flags, entry
// addresses, hooked forwards with arguments, table bytes, flag bytes, global member calls, float
// accumulators, flag sets, wide fields, byte lookups, part forwards and copied child fields. Each
// group differs only in its offsets, strides and globals; types and functions are named after their
// address. Status: matching/README.md.

struct FlagBytes7c5a8 {
    unsigned char pad[0x40c];
    unsigned char flags[1];   // +40c
};

// 0x710007c5a8
unsigned char flag_set_7c5a8(FlagBytes7c5a8* object, int index) {
    return object->flags[index] != 0;
}

struct FlagBytes8105c {
    unsigned char pad[0x40c];
    unsigned char flags[1];   // +40c
};

// 0x710008105c
unsigned char flag_set_8105c(FlagBytes8105c* object, int index) {
    return object->flags[index] != 0;
}

struct FlagBytes9d2b4 {
    unsigned char pad[0x158];
    unsigned char flags[1];   // +158
};

// 0x710009d2b4
unsigned char flag_set_9d2b4(FlagBytes9d2b4* object, int index) {
    return object->flags[index] != 0;
}

struct Slot13e2a0 {
    unsigned char data[0x50];
};
struct Slots13e2a0 {
    unsigned char pad[0x2b20];
    Slot13e2a0 slots[1];   // +2b20
};

// 0x710013e2a0
Slot13e2a0* slot_13e2a0(Slots13e2a0* object, unsigned int index) {
    return &object->slots[index];
}

struct Slot19cfac {
    unsigned char data[0x6c];
};
struct Slots19cfac {
    unsigned char pad[0x2dac];
    Slot19cfac slots[1];   // +2dac
};

// 0x710019cfac
Slot19cfac* slot_19cfac(Slots19cfac* object, unsigned int index) {
    return &object->slots[index];
}

struct Slot3de8cc {
    unsigned char data[0xd0];
};
struct Slots3de8cc {
    unsigned char pad[0x7620];
    Slot3de8cc slots[1];   // +7620
};

// 0x71003de8cc
Slot3de8cc* slot_3de8cc(Slots3de8cc* object, unsigned int index) {
    return &object->slots[index];
}

struct Slot13e290 {
    unsigned char data[0x50];
};
struct Slots13e290 {
    unsigned char pad[0x640];
    Slot13e290 slots[1];   // +640
};

// 0x710013e290
Slot13e290* slot_13e290(Slots13e290* object, unsigned int index) {
    return &object->slots[index];
}

struct Slot19bcfc {
    unsigned char data[0x58];
};
struct Slots19bcfc {
    unsigned char pad[0x6c];
    Slot19bcfc slots[1];   // +6c
};

// 0x710019bcfc
Slot19bcfc* slot_19bcfc(Slots19bcfc* object, unsigned int index) {
    return &object->slots[index];
}

struct Slot5d3688 {
    unsigned char data[0x28];
};
struct Slots5d3688 {
    unsigned char pad[0x678];
    Slot5d3688 slots[1];   // +678
};

// 0x71005d3688
Slot5d3688* slot_5d3688(Slots5d3688* object, unsigned int index) {
    return &object->slots[index];
}

struct HookTarget4615a8 {
    unsigned char pad[0xb8];
    void* value;              // +b8
};
// Reached through the GOT slot at 0x7100c2bc58.
extern void (*gHook_c2bc58)(void* value, void* a, void* b);

// 0x71004615a8
void hook_call_4615a8(HookTarget4615a8* object, void* a, void* b) {
    void* value = object->value;
    gHook_c2bc58(value, a, b);
}

struct HookTarget462650 {
    void* value;              // +0
};
// Reached through the GOT slot at 0x7100c2be08.
extern void (*gHook_c2be08)(void* value, void* a, void* b);

// 0x7100462650
void hook_call_462650(HookTarget462650* object, void* a, void* b) {
    void* value = object->value;
    gHook_c2be08(value, a, b);
}

struct HookTarget462664 {
    void* value;              // +0
};
// Reached through the GOT slot at 0x7100c2be10.
extern void (*gHook_c2be10)(void* value, void* a, void* b);

// 0x7100462664
void hook_call_462664(HookTarget462664* object, void* a, void* b) {
    void* value = object->value;
    gHook_c2be10(value, a, b);
}

struct ByteQuad {
    unsigned char bytes[4];
};
extern const ByteQuad kByteQuads_a98234[] __attribute__((visibility("hidden"))); // 0x7100a98234

// 0x7100574df4
unsigned char quad_byte_574df4(unsigned int index) {
    return kByteQuads_a98234[index].bytes[1];
}

// 0x7100574e08
unsigned char quad_byte_574e08(unsigned int index) {
    return kByteQuads_a98234[index].bytes[2];
}

// 0x7100574e1c
unsigned char quad_byte_574e1c(unsigned int index) {
    return kByteQuads_a98234[index].bytes[3];
}

struct FlagByte835a8 {
    unsigned char pad[0x428];
    unsigned char flag;       // +428
};

// 0x71000835a8
unsigned char flag_on_835a8(FlagByte835a8* object) {
    return object->flag != 0;
}

struct FlagByte99388 {
    unsigned char pad[0x429];
    unsigned char flag;       // +429
};

// 0x7100099388
unsigned char flag_on_99388(FlagByte99388* object) {
    return object->flag != 0;
}

struct FlagByte244790 {
    unsigned char pad[0xa4];
    unsigned char flag;       // +a4
};

// 0x7100244790
unsigned char flag_on_244790(FlagByte244790* object) {
    return object->flag != 0;
}

struct SizedBuffer {
    void reset();                                                           // 0x710003cea8

    void* buffer;
    long size;
};
struct BufferHolder_c22480 {
    unsigned char pad[8];
    SizedBuffer buffer;       // +08
};
// Reached through the GOT slot at 0x7100c22480.
extern BufferHolder_c22480 gBufferHolder_c22480;

// 0x71000aa5dc
void reset_global_buffer_aa5dc() {
    gBufferHolder_c22480.buffer.reset();
}

namespace nn {
namespace os {
struct MutexType;
void LockMutex(MutexType* mutex);
void UnlockMutex(MutexType* mutex);
}  // namespace os
}  // namespace nn

struct SystemMutex {
    unsigned char pad[0x10];
    unsigned char mutex[1];   // +10
};
extern SystemMutex* gSystemMutex __attribute__((visibility("hidden")));

// 0x7100459b54
void lock_system_mutex() {
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(gSystemMutex->mutex));
}

// 0x7100459b64
void unlock_system_mutex() {
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(gSystemMutex->mutex));
}

struct Accumd3430 {
    unsigned char pad[0x8];
    float total;              // +8
};

// 0x71000d3430
void accumulate_d3430(Accumd3430* object, float amount) {
    object->total += amount;
}

struct Accum40e8f4 {
    unsigned char pad[0x20];
    float total;              // +20
};

// 0x710040e8f4
void accumulate_40e8f4(Accum40e8f4* object, float amount) {
    object->total += amount;
}

struct Accum40f874 {
    unsigned char pad[0xe0];
    float total;              // +e0
};

// 0x710040f874
void accumulate_40f874(Accum40f874* object, float amount) {
    object->total += amount;
}

struct WideFlags16f2ac {
    unsigned long flags;      // +0
};

// 0x710016f2ac
void set_flags_16f2ac(WideFlags16f2ac* object, unsigned long bits) {
    object->flags |= bits;
}

struct WideFlags16f618 {
    unsigned char pad[0x8];
    unsigned long flags;      // +8
};

// 0x710016f618
void set_flags_16f618(WideFlags16f618* object, unsigned long bits) {
    object->flags |= bits;
}

struct WideFlags16f628 {
    unsigned char pad[0x10];
    unsigned long flags;      // +10
};

// 0x710016f628
void set_flags_16f628(WideFlags16f628* object, unsigned long bits) {
    object->flags |= bits;
}

struct FarField1ec94c {
    unsigned char pad[0x166d8];
    int value;                // +166d8
};

// 0x71001ec94c
int far_field_1ec94c(FarField1ec94c* object) {
    return object->value;
}

struct FarField1ecbb0 {
    unsigned char pad[0x16740];
    int value;                // +16740
};

// 0x71001ecbb0
int far_field_1ecbb0(FarField1ecbb0* object) {
    return object->value;
}

struct FarField1ecddc {
    unsigned char pad[0x16760];
    int value;                // +16760
};

// 0x71001ecddc
int far_field_1ecddc(FarField1ecddc* object) {
    return object->value;
}

struct ByteMap20639c {
    unsigned char pad[0x20];
    unsigned char values[0x100]; // +20
};

// 0x710020639c
unsigned char byte_map_20639c(ByteMap20639c* map, unsigned char key) {
    return map->values[key];
}

struct ByteMap20643c {
    unsigned char pad[0x34];
    unsigned char values[0x100]; // +34
};

// 0x710020643c
unsigned char byte_map_20643c(ByteMap20643c* map, unsigned char key) {
    return map->values[key];
}

struct ByteMap20644c {
    unsigned char pad[0x50];
    unsigned char values[0x100]; // +50
};

// 0x710020644c
unsigned char byte_map_20644c(ByteMap20644c* map, unsigned char key) {
    return map->values[key];
}

void bind_handle_256724(void* handle, void* part);                     // 0x7100256724

struct HandleOwner24803c {
    unsigned char pad[0x4];
    unsigned char part[4];    // +4
    void* handle;             // +8
};

// 0x710024803c
void bind_part_24803c(HandleOwner24803c* owner) {
    bind_handle_256724(owner->handle, owner->part);
}

struct HandleOwner24c058 {
    unsigned char pad[0x44];
    unsigned char part[4];    // +44
    void* handle;             // +48
};

// 0x710024c058
void bind_part_24c058(HandleOwner24c058* owner) {
    bind_handle_256724(owner->handle, owner->part);
}

struct HandleOwner24e1e8 {
    unsigned char pad[0x124];
    unsigned char part[4];    // +124
    void* handle;             // +128
};

// 0x710024e1e8
void bind_part_24e1e8(HandleOwner24e1e8* owner) {
    bind_handle_256724(owner->handle, owner->part);
}

struct Source3e9634 {
    unsigned char pad[0x290];
    int value;                // +290
};
struct Copier3e9634 {
    unsigned char pad[8];
    Source3e9634* source;   // +08
    unsigned char pad10[0x34];
    int value;                // +44
};

// 0x71003e9634
void copy_field_3e9634(Copier3e9634* object) {
    object->value = object->source->value;
}

struct Source3e9644 {
    unsigned char pad[0x150];
    int value;                // +150
};
struct Copier3e9644 {
    unsigned char pad[8];
    Source3e9644* source;   // +08
    unsigned char pad10[0x38];
    int value;                // +48
};

// 0x71003e9644
void copy_field_3e9644(Copier3e9644* object) {
    object->value = object->source->value;
}

struct Source3e9654 {
    unsigned char pad[0x28c];
    int value;                // +28c
};
struct Copier3e9654 {
    unsigned char pad[8];
    Source3e9654* source;   // +08
    unsigned char pad10[0x3c];
    int value;                // +4c
};

// 0x71003e9654
void copy_field_3e9654(Copier3e9654* object) {
    object->value = object->source->value;
}
