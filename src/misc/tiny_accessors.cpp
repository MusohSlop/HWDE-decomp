// Tiny accessors found by tools/family_scan.py --immediates, one group per shape: flag-gated
// constants, pair copies, chained virtual calls, clamped fields, bounded 16-bit and byte reads, part
// forwards, guarded forwards, virtual result tests, icon lookups and draws, table entry calls, child
// fields, offset results, nonzero tests and member addresses. Each group differs only in its offsets,
// limits, slots and callees; types and functions are named after their address.
// Status: matching/README.md.

extern unsigned char gFlag_c2edf0 __attribute__((visibility("hidden"))); // 0x7100c2edf0

// 0x710006fc10
int flag_value_6fc10() {
    return gFlag_c2edf0 ? 0x2d : 0;
}

extern unsigned char gFlag_c2ee00 __attribute__((visibility("hidden"))); // 0x7100c2ee00

// 0x710006fc74
int flag_value_6fc74() {
    return gFlag_c2ee00 ? 0x14 : 0;
}

extern unsigned char gFlag_c2ee0c __attribute__((visibility("hidden"))); // 0x7100c2ee0c

// 0x710006fcbc
int flag_value_6fcbc() {
    return gFlag_c2ee0c ? 0xa : 0;
}

extern unsigned char gFlag_c2ee1c __attribute__((visibility("hidden"))); // 0x7100c2ee1c

// 0x710006fe04
int flag_value_6fe04() {
    return gFlag_c2ee1c ? 0xa : 0;
}

extern unsigned char gFlag_c2ee20 __attribute__((visibility("hidden"))); // 0x7100c2ee20

// 0x710006fe1c
int flag_value_6fe1c() {
    return gFlag_c2ee20 ? 0x9 : 0;
}

struct ValuePair {
    long first;
    long second;
};

struct PairHolder36724 {
    unsigned char pad[0xa0];
    ValuePair pair;           // +a0
};

// 0x7100036724
void set_pair_36724(PairHolder36724* holder, const ValuePair* value) {
    holder->pair.second = value->second;
    holder->pair.first = value->first;
}

struct PairHolder14a61c {
    ValuePair pair;           // +0
};

// 0x710014a61c
void set_pair_14a61c(PairHolder14a61c* holder, const ValuePair* value) {
    holder->pair.second = value->second;
    holder->pair.first = value->first;
}

struct PairHolder42e7ec {
    unsigned char pad[0x50];
    ValuePair pair;           // +50
};

// 0x710042e7ec
void set_pair_42e7ec(PairHolder42e7ec* holder, const ValuePair* value) {
    holder->pair.second = value->second;
    holder->pair.first = value->first;
}

struct PairHolder42e800 {
    unsigned char pad[0x60];
    ValuePair pair;           // +60
};

// 0x710042e800
void set_pair_42e800(PairHolder42e800* holder, const ValuePair* value) {
    holder->pair.second = value->second;
    holder->pair.first = value->first;
}

struct PairHolder4a1284 {
    unsigned char pad[0x1910];
    ValuePair pair;           // +1910
};

// 0x71004a1284
void set_pair_4a1284(PairHolder4a1284* holder, const ValuePair* value) {
    holder->pair.second = value->second;
    holder->pair.first = value->first;
}

struct PairHolder54bc24 {
    unsigned char pad[0x50];
    ValuePair pair;           // +50
};

// 0x710054bc24
void set_pair_54bc24(PairHolder54bc24* holder, const ValuePair* value) {
    holder->pair.second = value->second;
    holder->pair.first = value->first;
}

class ChainTarget7a178 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void call();
};
struct ChainMiddle7a178 {
    unsigned char pad[0x18];
    ChainTarget7a178* target;   // +18
};
struct ChainOwner7a178 {
    unsigned char pad[0x10];
    ChainMiddle7a178* middle;   // +10
};

// 0x710007a178
void chain_call_7a178(ChainOwner7a178* owner) {
    owner->middle->target->call();
}

class ChainTargetae5c4 {
public:
    virtual void v00();
    virtual void v08();
    virtual void call();
};
struct ChainMiddleae5c4 {
    unsigned char pad[0x18];
    ChainTargetae5c4* target;   // +18
};
struct ChainOwnerae5c4 {
    unsigned char pad[0x8];
    ChainMiddleae5c4* middle;   // +8
};

// 0x71000ae5c4
void chain_call_ae5c4(ChainOwnerae5c4* owner) {
    owner->middle->target->call();
}

class ChainTargetae5d8 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void call();
};
struct ChainMiddleae5d8 {
    unsigned char pad[0x18];
    ChainTargetae5d8* target;   // +18
};
struct ChainOwnerae5d8 {
    unsigned char pad[0x8];
    ChainMiddleae5d8* middle;   // +8
};

// 0x71000ae5d8
void chain_call_ae5d8(ChainOwnerae5d8* owner) {
    owner->middle->target->call();
}

class ChainTargetae5ec {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void call();
};
struct ChainMiddleae5ec {
    unsigned char pad[0x18];
    ChainTargetae5ec* target;   // +18
};
struct ChainOwnerae5ec {
    unsigned char pad[0x8];
    ChainMiddleae5ec* middle;   // +8
};

// 0x71000ae5ec
void chain_call_ae5ec(ChainOwnerae5ec* owner) {
    owner->middle->target->call();
}

class ChainTargetba16c {
public:
    virtual void v00();
    virtual void v08();
    virtual void call();
};
struct ChainMiddleba16c {
    unsigned char pad[0x18];
    ChainTargetba16c* target;   // +18
};
struct ChainOwnerba16c {
    unsigned char pad[0x18];
    ChainMiddleba16c* middle;   // +18
};

// 0x71000ba16c
void chain_call_ba16c(ChainOwnerba16c* owner) {
    owner->middle->target->call();
}

class ChainTargetc4948 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void call();
};
struct ChainMiddlec4948 {
    unsigned char pad[0x18];
    ChainTargetc4948* target;   // +18
};
struct ChainOwnerc4948 {
    unsigned char pad[0x8];
    ChainMiddlec4948* middle;   // +8
};

// 0x71000c4948
void chain_call_c4948(ChainOwnerc4948* owner) {
    owner->middle->target->call();
}

struct Clamped19b648 {
    unsigned char pad[0x10];
    int value;                // +10
};

// 0x710019b648: 0 to 0x17
int clamped_19b648(Clamped19b648* object) {
    int value = object->value;
    value = value < 0 ? 0 : value;
    return value > 0x17 ? 0x17 : value;
}

struct Clamped19b69c {
    unsigned char pad[0x1c];
    int value;                // +1c
};

// 0x710019b69c: 0 to 0x3e7
int clamped_19b69c(Clamped19b69c* object) {
    int value = object->value;
    value = value < 0 ? 0 : value;
    return value > 0x3e7 ? 0x3e7 : value;
}

struct Clamped19b8d0 {
    unsigned char pad[0x4];
    int value;                // +4
};

// 0x710019b8d0: 0 to 0x4f
int clamped_19b8d0(Clamped19b8d0* object) {
    int value = object->value;
    value = value < 0 ? 0 : value;
    return value > 0x4f ? 0x4f : value;
}

struct Clamped19bb74 {
    int value;                // +0
};

// 0x710019bb74: 0 to 0x44b
int clamped_19bb74(Clamped19bb74* object) {
    int value = object->value;
    value = value < 0 ? 0 : value;
    return value > 0x44b ? 0x44b : value;
}

struct Shorts1ff6e8 {
    unsigned char pad[0x4];
    short values[1];          // +4
};

// 0x71001ff6e8
int short_or_none_1ff6e8(Shorts1ff6e8* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x2)
        return table->values[index];
    return -1;
}

struct Shorts20b5a4 {
    unsigned char pad[0x1e];
    short values[1];          // +1e
};

// 0x710020b5a4
int short_or_none_20b5a4(Shorts20b5a4* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x4)
        return table->values[index];
    return -1;
}

struct Shorts20b878 {
    unsigned char pad[0x80];
    short values[1];          // +80
};

// 0x710020b878
int short_or_none_20b878(Shorts20b878* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x3f)
        return table->values[index];
    return -1;
}

struct Shorts214534 {
    unsigned char pad[0x18];
    short values[1];          // +18
};

// 0x7100214534
int short_or_none_214534(Shorts214534* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x4)
        return table->values[index];
    return -1;
}

void part_handler_4a910(void* part);                              // 0x710004a910

// 0x71000475f0
void forward_part_475f0(unsigned char* self) {
    part_handler_4a910(self + 0x10770);
}

void part_handler_5c3774(void* part);                              // 0x71005c3774

// 0x71001d7338
void forward_part_1d7338(unsigned char* self) {
    part_handler_5c3774(self + 0x139870);
}

void part_handler_379f84(void* part);                              // 0x7100379f84

// 0x71002f98ec
void forward_part_2f98ec(unsigned char* self) {
    part_handler_379f84(self + 0x41e18);
}

void part_handler_1f2378(void* part);                              // 0x71001f2378

// 0x71003885fc
void forward_part_3885fc(unsigned char* self) {
    part_handler_1f2378(self + 0x2d130);
}

void part_handler_1f23f8(void* part);                              // 0x71001f23f8

// 0x710038860c
void forward_part_38860c(unsigned char* self) {
    part_handler_1f23f8(self + 0x2d130);
}

void part_handler_1ef2cc(void* part);                              // 0x71001ef2cc

// 0x710038861c
void forward_part_38861c(unsigned char* self) {
    part_handler_1ef2cc(self + 0x2d2a0);
}

void part_handler_1ef39c(void* part);                              // 0x71001ef39c

// 0x710038862c
void forward_part_38862c(unsigned char* self) {
    part_handler_1ef39c(self + 0x2d2a0);
}

void child_handler_f35b0(void* child);                              // 0x71000f35b0
struct ChildHolderf487c {
    unsigned char pad[0x8];
    void* child;              // +8
};

// 0x71000f487c
void forward_child_f487c(ChildHolderf487c* holder) {
    if (holder->child)
        child_handler_f35b0(holder->child);
}

void child_handler_2ae1c8(void* child);                              // 0x71002ae1c8
struct ChildHolder316b48 {
    unsigned char pad[0x38];
    void* child;              // +38
};

// 0x7100316b48
void forward_child_316b48(ChildHolder316b48* holder) {
    if (holder->child)
        child_handler_2ae1c8(holder->child);
}

void child_handler_40e568(void* child);                              // 0x710040e568
struct ChildHolder414d4c {
    unsigned char pad[0x8];
    void* child;              // +8
};

// 0x7100414d4c
void forward_child_414d4c(ChildHolder414d4c* holder) {
    if (holder->child)
        child_handler_40e568(holder->child);
}

void child_handler_41d41c(void* child);                              // 0x710041d41c
struct ChildHolder426b28 {
    unsigned char pad[0x30];
    void* child;              // +30
};

// 0x7100426b28
void forward_child_426b28(ChildHolder426b28* holder) {
    if (holder->child)
        child_handler_41d41c(holder->child);
}

void child_handler_4340c8(void* child);                              // 0x71004340c8
struct ChildHolder4345d8 {
    unsigned char pad[0x88];
    void* child;              // +88
};

// 0x71004345d8
void forward_child_4345d8(ChildHolder4345d8* holder) {
    if (holder->child)
        child_handler_4340c8(holder->child);
}

void child_handler_470da8(void* child);                              // 0x7100470da8
struct ChildHolder43ca48 {
    unsigned char pad[0x80];
    void* child;              // +80
};

// 0x710043ca48
void forward_child_43ca48(ChildHolder43ca48* holder) {
    if (holder->child)
        child_handler_470da8(holder->child);
}

void child_handler_43ba7c(void* child);                              // 0x710043ba7c
struct ChildHolder43d534 {
    unsigned char pad[0x48];
    void* child;              // +48
};

// 0x710043d534
void forward_child_43d534(ChildHolder43d534* holder) {
    if (holder->child)
        child_handler_43ba7c(holder->child);
}

class Resolved18f8c {
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
    virtual void call();
};
class Resolver18f8c {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual Resolved18f8c* resolve();
};

// 0x7100018f8c
void resolve_call_18f8c(Resolver18f8c* source) {
    source->resolve()->call();
}

class Resolved193c4 {
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
    virtual void call();
};
class Resolver193c4 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual Resolved193c4* resolve();
};

// 0x71000193c4
void resolve_call_193c4(Resolver193c4* source) {
    source->resolve()->call();
}

class Resolvedd4c38 {
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
    virtual void call();
};
class Resolverd4c38 {
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
    virtual Resolvedd4c38* resolve();
};

// 0x71000d4c38
void resolve_call_d4c38(Resolverd4c38* source) {
    source->resolve()->call();
}

class Tested279d0 {
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

// 0x71000279d0
unsigned char test_state_279d0(Tested279d0* object) {
    return object->state() == 0;
}

class Tested3eead0 {
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
    virtual int state();
};

// 0x71003eead0
unsigned char test_state_3eead0(Tested3eead0* object) {
    return object->state() == 3;
}

class Tested5f3bf4 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual int state();
};

// 0x71005f3bf4
unsigned char test_state_5f3bf4(Tested5f3bf4* object) {
    return object->state() == 2;
}

struct IconRecord {
    unsigned char data[0x10];
};

extern const IconRecord kIconTable_ba38a0[] __attribute__((visibility("hidden"))); // 0x7100ba38a0
struct IconSetdb39c {
    const IconRecord* icon(int id) {
        return static_cast<unsigned int>(id) > 0x188 ? nullptr : &kIconTable_ba38a0[id];
    }

    void* texture;
};

// 0x71000db39c
const IconRecord* icon_db39c(IconSetdb39c* icons, int id) {
    return icons->icon(id);
}

extern const IconRecord kIconTable_802b08[] __attribute__((visibility("hidden"))); // 0x7100802b08
struct IconSet37ab7c {
    const IconRecord* icon(int id) {
        return static_cast<unsigned int>(id) > 0x6e ? nullptr : &kIconTable_802b08[id];
    }

    void* texture;
};

// 0x710037ab7c
const IconRecord* icon_37ab7c(IconSet37ab7c* icons, int id) {
    return icons->icon(id);
}

extern const IconRecord kIconTable_8031f8[] __attribute__((visibility("hidden"))); // 0x71008031f8
struct IconSet37acb8 {
    const IconRecord* icon(int id) {
        return static_cast<unsigned int>(id) > 0x4 ? nullptr : &kIconTable_8031f8[id];
    }

    void* texture;
};

// 0x710037acb8
const IconRecord* icon_37acb8(IconSet37acb8* icons, int id) {
    return icons->icon(id);
}

extern const IconRecord kIconTable_804728[] __attribute__((visibility("hidden"))); // 0x7100804728
struct IconSet3c58c8 {
    const IconRecord* icon(int id) {
        return static_cast<unsigned int>(id) > 0xf ? nullptr : &kIconTable_804728[id];
    }

    void* texture;
};

// 0x71003c58c8
const IconRecord* icon_3c58c8(IconSet3c58c8* icons, int id) {
    return icons->icon(id);
}

void draw_icon_1efe5c(void* target, const IconRecord* icon, void* texture); // 0x71001efe5c

// 0x71000db3b4
void draw_icon_db3b4(IconSetdb39c* icons, void* target, int id) {
    draw_icon_1efe5c(target, icons->icon(id), icons->texture);
}

void draw_icon_1f0df4(void* target, const IconRecord* icon, void* texture); // 0x71001f0df4

// 0x71000db3d8
void draw_icon_db3d8(IconSetdb39c* icons, void* target, int id) {
    draw_icon_1f0df4(target, icons->icon(id), icons->texture);
}

void draw_icon_1eff04(void* target, const IconRecord* icon, void* texture); // 0x71001eff04

// 0x71000db3fc
void draw_icon_db3fc(IconSetdb39c* icons, void* target, int id) {
    draw_icon_1eff04(target, icons->icon(id), icons->texture);
}

// Reached through the GOT slot at 0x7100c22d58.
extern void** gGlobal_c22d58;

class TableEntry3e7a84 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void call(void* a, void* b);
};

// 0x71003e7a84
void entry_call_3e7a84(int index, void* a, void* b) {
    if (TableEntry3e7a84* entry = static_cast<TableEntry3e7a84*>(gGlobal_c22d58[index]))
        entry->call(a, b);
}

class TableEntry3e7acc {
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
    virtual void call(void* a, void* b);
};

// 0x71003e7acc
void entry_call_3e7acc(int index, void* a, void* b) {
    if (TableEntry3e7acc* entry = static_cast<TableEntry3e7acc*>(gGlobal_c22d58[index]))
        entry->call(a, b);
}

class TableEntry3e7af0 {
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
    virtual void call(void* a, void* b);
};

// 0x71003e7af0
void entry_call_3e7af0(int index, void* a, void* b) {
    if (TableEntry3e7af0* entry = static_cast<TableEntry3e7af0*>(gGlobal_c22d58[index]))
        entry->call(a, b);
}

struct ByteRow201ee0 {
    unsigned char pad[0x14];
    unsigned char value;      // +14
    unsigned char pad15[0x33];
};

// 0x7100201ee0
unsigned char row_byte_201ee0(ByteRow201ee0* rows, int row) {
    if (static_cast<unsigned int>(row) <= 0x20)
        return rows[row].value;
    return 0;
}

struct ByteRow201f00 {
    unsigned char pad[0x20];
    unsigned char value;      // +20
    unsigned char pad21[0x27];
};

// 0x7100201f00
unsigned char row_byte_201f00(ByteRow201f00* rows, int row) {
    if (static_cast<unsigned int>(row) <= 0x20)
        return rows[row].value;
    return 0;
}

struct ByteRow201f20 {
    unsigned char pad[0x2c];
    unsigned char value;      // +2c
    unsigned char pad2d[0x1b];
};

// 0x7100201f20
unsigned char row_byte_201f20(ByteRow201f20* rows, int row) {
    if (static_cast<unsigned int>(row) <= 0x20)
        return rows[row].value;
    return 0;
}

struct CheckedBytes205548 {
    unsigned char pad[0x85];
    unsigned char values[0x12c]; // +85
};

// 0x7100205548
unsigned char checked_byte_205548(CheckedBytes205548* table, int index) {
    unsigned char value = 0;
    if (index >= 0 && static_cast<unsigned int>(index) <= 0x12b)
        value = table->values[index];
    return value;
}

struct CheckedBytes2055d8 {
    unsigned char pad[0x1b1];
    unsigned char values[0x12c]; // +1b1
};

// 0x71002055d8
unsigned char checked_byte_2055d8(CheckedBytes2055d8* table, int index) {
    unsigned char value = 0;
    if (index >= 0 && static_cast<unsigned int>(index) <= 0x12b)
        value = table->values[index];
    return value;
}

struct CheckedBytes205624 {
    unsigned char pad[0x409];
    unsigned char values[0x12c]; // +409
};

// 0x7100205624
unsigned char checked_byte_205624(CheckedBytes205624* table, int index) {
    unsigned char value = 0;
    if (index >= 0 && static_cast<unsigned int>(index) <= 0x12b)
        value = table->values[index];
    return value;
}

struct PairTarget40e8ac {
    unsigned char pad[0x60];
    ValuePair pair;           // +60
};
struct PairForward40e8ac {
    PairTarget40e8ac* target;
};

// 0x710040e8ac
void forward_pair_40e8ac(PairForward40e8ac* owner, const ValuePair* value) {
    PairTarget40e8ac* target = owner->target;
    target->pair.second = value->second;
    target->pair.first = value->first;
}

struct PairTarget40e8c4 {
    unsigned char pad[0x30];
    ValuePair pair;           // +30
};
struct PairForward40e8c4 {
    PairTarget40e8c4* target;
};

// 0x710040e8c4
void forward_pair_40e8c4(PairForward40e8c4* owner, const ValuePair* value) {
    PairTarget40e8c4* target = owner->target;
    target->pair.second = value->second;
    target->pair.first = value->first;
}

struct PairTarget40e8dc {
    unsigned char pad[0x40];
    ValuePair pair;           // +40
};
struct PairForward40e8dc {
    PairTarget40e8dc* target;
};

// 0x710040e8dc
void forward_pair_40e8dc(PairForward40e8dc* owner, const ValuePair* value) {
    PairTarget40e8dc* target = owner->target;
    target->pair.second = value->second;
    target->pair.first = value->first;
}

struct PairTarget40ea94 {
    unsigned char pad[0x200];
    ValuePair pair;           // +200
};
struct PairForward40ea94 {
    PairTarget40ea94* target;
};

// 0x710040ea94
void forward_pair_40ea94(PairForward40ea94* owner, const ValuePair* value) {
    PairTarget40ea94* target = owner->target;
    target->pair.second = value->second;
    target->pair.first = value->first;
}

struct ChildRecord4443d4 {
    unsigned char pad[0xa];
    unsigned short value;     // +a
};
struct ChildOwner4443d4 {
    unsigned char pad[0x20];
    ChildRecord4443d4* child;    // +20
};

// 0x71004443d4
unsigned short child_field_4443d4(ChildOwner4443d4* owner) {
    return owner->child ? owner->child->value : 0;
}

struct ChildRecord5cfbcc {
    unsigned char pad[0xa];
    unsigned short value;     // +a
};
struct ChildOwner5cfbcc {
    unsigned char pad[0x10];
    ChildRecord5cfbcc* child;    // +10
};

// 0x71005cfbcc
unsigned short child_field_5cfbcc(ChildOwner5cfbcc* owner) {
    return owner->child ? owner->child->value : 0;
}

struct ChildRecord5cfc1c {
    unsigned char pad[0xc];
    unsigned short value;     // +c
};
struct ChildOwner5cfc1c {
    unsigned char pad[0x18];
    ChildRecord5cfc1c* child;    // +18
};

// 0x71005cfc1c
unsigned short child_field_5cfc1c(ChildOwner5cfc1c* owner) {
    return owner->child ? owner->child->value : 0;
}

struct ChildRecord5dad44 {
    unsigned char pad[0x8];
    unsigned short value;     // +8
};
struct ChildOwner5dad44 {
    unsigned char pad[0xa8];
    ChildRecord5dad44* child;    // +a8
};

// 0x71005dad44
unsigned short child_field_5dad44(ChildOwner5dad44* owner) {
    return owner->child ? owner->child->value : 0;
}

int base_value_537880();                                        // 0x7100537880

// 0x7100537394
int offset_value_537394() {
    return base_value_537880() + 0x100;
}

int base_value_5e4614();                                        // 0x71005e4614

// 0x71005e434c
int offset_value_5e434c() {
    return base_value_5e4614() + 0xc0;
}

int base_value_5e5200();                                        // 0x71005e5200

// 0x71005e4f04
int offset_value_5e4f04() {
    return base_value_5e5200() + 0x1b0;
}

int base_value_5e79cc();                                        // 0x71005e79cc

// 0x71005e748c
int offset_value_5e748c() {
    return base_value_5e79cc() + 0xff0;
}

struct Countedf8800 {
    unsigned char pad[0x1530];
    int value;                // +1530
};

// 0x71000f8800
unsigned char has_value_f8800(Countedf8800* object) {
    return object->value != 0;
}

struct Counted19b9b8 {
    unsigned char pad[0x14];
    int value;                // +14
};

// 0x710019b9b8
unsigned char has_value_19b9b8(Counted19b9b8* object) {
    return object->value != 0;
}

struct Counted19b9e4 {
    unsigned char pad[0x1c];
    int value;                // +1c
};

// 0x710019b9e4
unsigned char has_value_19b9e4(Counted19b9e4* object) {
    return object->value != 0;
}

struct Counted19ba5c {
    unsigned char pad[0x50];
    int value;                // +50
};

// 0x710019ba5c
unsigned char has_value_19ba5c(Counted19ba5c* object) {
    return object->value != 0;
}

struct Counted2fe688 {
    int value;                // +0
};

// 0x71002fe688
unsigned char has_value_2fe688(Counted2fe688* object) {
    return object->value != 0;
}

struct Counted555c38 {
    unsigned char pad[0x3d0];
    int value;                // +3d0
};

// 0x7100555c38
unsigned char has_value_555c38(Counted555c38* object) {
    return object->value != 0;
}

struct Container1898b8 {
    unsigned char pad[0x95a28];
    unsigned char member[1];  // +95a28
};

// 0x71001898b8
void* member_1898b8(Container1898b8* container) {
    return container->member;
}

struct Container18d5d8 {
    unsigned char pad[0xd4e68];
    unsigned char member[1];  // +d4e68
};

// 0x710018d5d8
void* member_18d5d8(Container18d5d8* container) {
    return container->member;
}

struct Container18f0e0 {
    unsigned char pad[0xd72f0];
    unsigned char member[1];  // +d72f0
};

// 0x710018f0e0
void* member_18f0e0(Container18f0e0* container) {
    return container->member;
}

struct Container18f11c {
    unsigned char pad[0xd73c0];
    unsigned char member[1];  // +d73c0
};

// 0x710018f11c
void* member_18f11c(Container18f11c* container) {
    return container->member;
}

struct Container18f12c {
    unsigned char pad[0xd77c8];
    unsigned char member[1];  // +d77c8
};

// 0x710018f12c
void* member_18f12c(Container18f12c* container) {
    return container->member;
}

struct Container18f13c {
    unsigned char pad[0x998d8];
    unsigned char member[1];  // +998d8
};

// 0x710018f13c
void* member_18f13c(Container18f13c* container) {
    return container->member;
}
