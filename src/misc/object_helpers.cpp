// Small object helpers found by tools/family_scan.py --immediates, one group per shape: paired part
// calls, hook frees, locked virtual calls, scaled item fields, entry floats, notify-and-release,
// relation kinds, paired virtual resets and bit tests in byte sets. Each group differs only in its
// offsets, slots and callees; types and functions are named after their address.
// Status: matching/README.md.


void part_op_475d8(void* part);                                    // 0x71000475d8
void part_op_3ab40(void* part);                                    // 0x710003ab40

// 0x710004699c
void paired_parts_4699c(unsigned char* self) {
    part_op_475d8(self + 0x72930);
    part_op_3ab40(self + 0xeaf80);
}

void part_op_3b0b0(void* part);                                    // 0x710003b0b0
void part_op_475f0(void* part);                                    // 0x71000475f0

// 0x71000469d4
void paired_parts_469d4(unsigned char* self) {
    part_op_3b0b0(self + 0xeaf80);
    part_op_475f0(self + 0x72930);
}

void part_op_e062c(void* part);                                    // 0x71000e062c
void part_op_13063c(void* part);                                    // 0x710013063c

// 0x7100103830
void paired_parts_103830(unsigned char* self) {
    part_op_e062c(self + 0x5d520);
    part_op_13063c(self + 0x5d110);
}

void part_op_1306c8(void* part);                                    // 0x71001306c8
void part_op_e0634(void* part);                                    // 0x71000e0634

// 0x71001058d0
void paired_parts_1058d0(unsigned char* self) {
    part_op_1306c8(self + 0x5d110);
    part_op_e0634(self + 0x5d520);
}

struct NodeOwner1ef138;
void release_node_1ef138(NodeOwner1ef138* owner);                    // 0x71001ef138
struct NodeOwner1f21f8;
void release_node_1f21f8(NodeOwner1f21f8* owner);                    // 0x71001f21f8

// 0x710038797c
void paired_parts_38797c(unsigned char* self) {
    release_node_1ef138(reinterpret_cast<NodeOwner1ef138*>(self + 0x2d2a0));
    release_node_1f21f8(reinterpret_cast<NodeOwner1f21f8*>(self + 0x2d130));
}

struct HookedBuffer4612ec {
    unsigned char owned;      // +0
    unsigned char pad1[7];
    void* buffer;             // +8
};
// Reached through the GOT slot at 0x7100c2bc00.
extern void (*gFreeHook_c2bc00)(void* buffer);

// 0x71004612ec
void free_hooked_4612ec(HookedBuffer4612ec* owner) {
    void* buffer = owner->buffer;
    gFreeHook_c2bc00(buffer);
    owner->buffer = nullptr;
    owner->owned = 0;
}

struct HookedBuffer462600 {
    void* buffer;             // +0
    void* cursor;             // +8
    unsigned char pad10[0x100];
    unsigned char owned;      // +110
};
// Reached through the GOT slot at 0x7100c2bdf8.
extern void (*gFreeHook_c2bdf8)(void* buffer);

// 0x7100462600
void free_hooked_462600(HookedBuffer462600* owner) {
    void* buffer = owner->buffer;
    gFreeHook_c2bdf8(buffer);
    owner->cursor = nullptr;
    owner->owned = 0;
}

struct HookedBuffer466c7c {
    unsigned char owned;      // +0
    unsigned char pad1[7];
    void* buffer;             // +8
};
// Reached through the GOT slot at 0x7100c2c2a0.
extern void (*gFreeHook_c2c2a0)(void* buffer);

// 0x7100466c7c
void free_hooked_466c7c(HookedBuffer466c7c* owner) {
    void* buffer = owner->buffer;
    gFreeHook_c2c2a0(buffer);
    owner->buffer = nullptr;
    owner->owned = 0;
}

struct HookedBuffer5f9614 {
    unsigned char owned;      // +0
    unsigned char pad1[7];
    void* buffer;             // +8
};
// Reached through the GOT slot at 0x7100c2c430.
extern void (*gFreeHook_c2c430)(void* buffer);

// 0x71005f9614
void free_hooked_5f9614(HookedBuffer5f9614* owner) {
    void* buffer = owner->buffer;
    gFreeHook_c2c430(buffer);
    owner->buffer = nullptr;
    owner->owned = 0;
}

struct HookedBuffer5f9ad8 {
    unsigned char pad[8];
    void* buffer;             // +8
    unsigned char pad10[0x40];
    unsigned char owned;      // +50
};
// Reached through the GOT slot at 0x7100c2ca08.
extern void (*gFreeHook_c2ca08)(void* buffer);

// 0x71005f9ad8
void free_hooked_5f9ad8(HookedBuffer5f9ad8* owner) {
    void* buffer = owner->buffer;
    gFreeHook_c2ca08(buffer);
    owner->buffer = nullptr;
    owner->owned = 0;
}

namespace nn {
namespace os {
struct MutexType;
void LockMutex(MutexType* mutex);
void UnlockMutex(MutexType* mutex);
}  // namespace os
}  // namespace nn

struct GuardLock {
    unsigned char pad[0x10];
    unsigned char mutex[1];   // +10
};
class GuardedService {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual long query_a();                                                 // +18
    virtual void v20();
    virtual long query_b();                                                 // +28
    virtual void v30();
    virtual void v38();
    virtual void v40();
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void v60();
    virtual void v68();
    virtual long query_c();                                                 // +70
};
struct GuardedHolder {
    GuardedService* service() { return &inner; }

    unsigned char pad[8];
    GuardedService inner;     // +08
    unsigned char pad10[0x58];
    GuardLock* lock;          // +68
};

// 0x71002ab140
long guarded_query_2ab140(GuardedHolder* holder) {
    if (holder->lock)
        nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(holder->lock->mutex));
    long result = holder->service()->query_a();
    if (holder->lock)
        nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(holder->lock->mutex));
    return result;
}

// 0x71002ab1f4
long guarded_query_2ab1f4(GuardedHolder* holder) {
    if (holder->lock)
        nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(holder->lock->mutex));
    long result = holder->service()->query_b();
    if (holder->lock)
        nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(holder->lock->mutex));
    return result;
}

// 0x71002ab9d0
long guarded_query_2ab9d0(GuardedHolder* holder) {
    if (holder->lock)
        nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(holder->lock->mutex));
    long result = holder->service()->query_c();
    if (holder->lock)
        nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(holder->lock->mutex));
    return result;
}

class ItemSource {
public:
    virtual void v000();
    virtual void v008();
    virtual void v010();
    virtual void v018();
    virtual void v020();
    virtual void v028();
    virtual void v030();
    virtual void v038();
    virtual void v040();
    virtual void v048();
    virtual void v050();
    virtual void v058();
    virtual void v060();
    virtual void v068();
    virtual void v070();
    virtual void v078();
    virtual void v080();
    virtual void v088();
    virtual void v090();
    virtual void v098();
    virtual void v0a0();
    virtual void v0a8();
    virtual void v0b0();
    virtual void v0b8();
    virtual void v0c0();
    virtual void v0c8();
    virtual void v0d0();
    virtual void v0d8();
    virtual void v0e0();
    virtual void v0e8();
    virtual void v0f0();
    virtual void v0f8();
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
    virtual int item();       // +3e8
};
union ScaledItemDef {
    unsigned short values[0x28];
};
class ScaledItemTable {
public:
    ScaledItemDef* find(int item) {
        return static_cast<unsigned int>(item) < 0x44c ? &defs[item] : nullptr;
    }

    ScaledItemDef defs[0x44c];
};
// Reached through the GOT slot at 0x7100c216a0.
extern ScaledItemTable* gItemDefs;
// Reached through the GOT slot at 0x7100c22918.
extern float gItemScale;

// 0x71000ceee4: field +22
float scaled_item_ceee4(ItemSource* source) {
    int item = source->item();
    return gItemDefs->find(item)->values[0x11] * gItemScale;
}

// 0x71000cef54: field +24
float scaled_item_cef54(ItemSource* source) {
    int item = source->item();
    return gItemDefs->find(item)->values[0x12] * gItemScale;
}

// 0x71000cefa4: field +26
float scaled_item_cefa4(ItemSource* source) {
    int item = source->item();
    return gItemDefs->find(item)->values[0x13] * gItemScale;
}

struct ValueEntry {
    unsigned char pad[0x24];
    float values[3];          // +24
    unsigned char pad30[0xc];
};
struct ValueEntryOwner {
    unsigned char pad[0x95a20];
    ValueEntry* entries;      // +95a20
};
// Reached through the GOT slot at 0x7100c216e8.
extern ValueEntryOwner* gShop;
extern unsigned int gValueEntryCount __attribute__((visibility("hidden"))); // 0x7100c337b8

static inline ValueEntry* value_entry(unsigned int index) {
    return index < gValueEntryCount ? &gShop->entries[index] : nullptr;
}

// 0x71001704e0
float entry_value_1704e0(unsigned int index) {
    ValueEntry* entry = value_entry(index);
    return entry ? entry->values[0] : 0.0f;
}

// 0x71001708f0
float entry_value_1708f0(unsigned int index) {
    ValueEntry* entry = value_entry(index);
    return entry ? entry->values[1] : 0.0f;
}

// 0x710017097c
float entry_value_17097c(unsigned int index) {
    ValueEntry* entry = value_entry(index);
    return entry ? entry->values[2] : 0.0f;
}

struct Notified4e276c;
class Listener4e276c {
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
    virtual void released(Notified4e276c* object);                                     // +60
};
struct Notified4e276c {
    virtual void v00();
    virtual void notify();    // +08

    unsigned char pad8[0x10];
    Listener4e276c* listener;  // +18
};

// 0x71004e276c
void notify_release_4e276c(Notified4e276c* object) {
    if (object)
        object->notify();
    if (object->listener)
        object->listener->released(object);
}

struct Notified56fed8;
class Listener56fed8 {
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
    virtual void released(Notified56fed8* object);                                     // +60
};
struct Notified56fed8 {
    virtual void v00();
    virtual void notify();    // +08

    unsigned char pad8[0x8];
    Listener56fed8* listener;  // +10
};

// 0x710056fed8
void notify_release_56fed8(Notified56fed8* object) {
    if (object)
        object->notify();
    if (object->listener)
        object->listener->released(object);
}

struct Notified570564;
class Listener570564 {
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
    virtual void released(Notified570564* object);                                     // +60
};
struct Notified570564 {
    virtual void v00();
    virtual void notify();    // +08

    unsigned char pad8[0x8];
    Listener570564* listener;  // +10
};

// 0x7100570564
void notify_release_570564(Notified570564* object) {
    if (object)
        object->notify();
    if (object->listener)
        object->listener->released(object);
}

class RelationSource {
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
    virtual unsigned char related(int other);                               // +88

    unsigned char pad8[2];
    unsigned short id;        // +0a
};

// 0x71002dbd78
int relation_kind_2dbd78(RelationSource* source, unsigned char other) {
    unsigned short id = source->id;
    int kind = source->related(other) ? 0x41 : 0x4a;
    return id == other ? 0x54 : kind;
}

// 0x71002dbdc4
int relation_kind_2dbdc4(RelationSource* source, unsigned char other) {
    unsigned short id = source->id;
    int kind = source->related(other) ? 0x4e : 0x4b;
    return id == other ? 0x50 : kind;
}

// 0x71002dbe10
int relation_kind_2dbe10(RelationSource* source, unsigned char other) {
    unsigned short id = source->id;
    int kind = source->related(other) ? 0x51 : 0x4a;
    return id == other ? 0x55 : kind;
}

class Resettable3aa844 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void reset();     // +18
};
struct ResetPair3aa844 {
    unsigned char pad[0x28];
    Resettable3aa844* part_28;  // +28
    Resettable3aa844* part_30;  // +30
};

// 0x71003aa844
void reset_pair_3aa844(ResetPair3aa844* pair) {
    if (pair->part_30)
        pair->part_30->reset();
    if (pair->part_28)
        pair->part_28->reset();
}

class Resettable3aa890 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void reset();     // +20
};
struct ResetPair3aa890 {
    unsigned char pad[0x28];
    Resettable3aa890* part_28;  // +28
    Resettable3aa890* part_30;  // +30
};

// 0x71003aa890
void reset_pair_3aa890(ResetPair3aa890* pair) {
    if (pair->part_30)
        pair->part_30->reset();
    if (pair->part_28)
        pair->part_28->reset();
}

class Resettable5cc4cc {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void reset();     // +30
};
struct ResetPair5cc4cc {
    unsigned char pad[0x8];
    Resettable5cc4cc* part_8;  // +8
    Resettable5cc4cc* part_10;  // +10
};

// 0x71005cc4cc
void reset_pair_5cc4cc(ResetPair5cc4cc* pair) {
    if (pair->part_8)
        pair->part_8->reset();
    if (pair->part_10)
        pair->part_10->reset();
}

struct ByteBits1a7f50 {
    unsigned char pad[0x2463];
    unsigned char bits[1];    // +2463
};

// 0x71001a7f50: ids up to 0x7f
unsigned char byte_bit_1a7f50(ByteBits1a7f50* set, unsigned int id) {
    if (id <= 0x7f)
        return (set->bits[id >> 3] & (1 << (id & 7))) != 0;
    return 0;
}

struct ByteBits202778 {
    unsigned char pad[0x1990];
    unsigned char bits[1];    // +1990
};

// 0x7100202778: ids up to 0xc
unsigned char byte_bit_202778(ByteBits202778* set, unsigned int id) {
    if (id <= 0xc)
        return (set->bits[id >> 3] & (1 << (id & 7))) != 0;
    return 0;
}

struct ByteBits203b50 {
    unsigned char pad[0x195a];
    unsigned char bits[1];    // +195a
};

// 0x7100203b50: ids up to 0x7f
unsigned char byte_bit_203b50(ByteBits203b50* set, unsigned int id) {
    if (id <= 0x7f)
        return (set->bits[id >> 3] & (1 << (id & 7))) != 0;
    return 0;
}

struct ByteBits203bd8 {
    unsigned char pad[0x196a];
    unsigned char bits[1];    // +196a
};

// 0x7100203bd8: ids up to 0x12b
unsigned char byte_bit_203bd8(ByteBits203bd8* set, unsigned int id) {
    if (id <= 0x12b)
        return (set->bits[id >> 3] & (1 << (id & 7))) != 0;
    return 0;
}
