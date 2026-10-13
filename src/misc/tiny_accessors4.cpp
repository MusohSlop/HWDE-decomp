// Another set of tiny accessors from tools/family_scan.py --immediates: range-checked byte stores,
// row flags, clamped bytes, saturating counters, optional global bytes, node placement, byte-set
// tests, scaled virtual results and triple-buffered slots. Each group differs only in offsets,
// limits and globals; types and functions are named after their address. Status: matching/README.md.

struct Setting1a0ccc {
    unsigned char pad[0xb1];
    unsigned char value;      // +b1
};

// 0x71001a0ccc
void set_setting_1a0ccc(Setting1a0ccc* object, int value) {
    if (static_cast<unsigned int>(value) <= 0xc)
        object->value = value;
}

struct Setting1ffb18 {
    unsigned char pad[0x1f];
    unsigned char value;      // +1f
};

// 0x71001ffb18
void set_setting_1ffb18(Setting1ffb18* object, int value) {
    if (static_cast<unsigned int>(value) <= 0x23)
        object->value = value;
}

struct Setting2002a8 {
    unsigned char pad[0x20];
    unsigned char value;      // +20
};

// 0x71002002a8
void set_setting_2002a8(Setting2002a8* object, int value) {
    if (static_cast<unsigned int>(value) <= 0xfe)
        object->value = value;
}

struct Setting2034d0 {
    unsigned char pad[0x148];
    unsigned char value;      // +148
};

// 0x71002034d0
void set_setting_2034d0(Setting2034d0* object, int value) {
    if (static_cast<unsigned int>(value) <= 0x3)
        object->value = value;
}

struct Setting20362c {
    unsigned char pad[0x149];
    unsigned char value;      // +149
};

// 0x710020362c
void set_setting_20362c(Setting20362c* object, int value) {
    if (static_cast<unsigned int>(value) <= 0x3)
        object->value = value;
}

struct Setting203c68 {
    unsigned char pad[0x160];
    unsigned char value;      // +160
};

// 0x7100203c68
void set_setting_203c68(Setting203c68* object, int value) {
    if (static_cast<unsigned int>(value) <= 0x4)
        object->value = value;
}

struct Setting20bb2c {
    unsigned char pad[0x120];
    unsigned char value;      // +120
};

// 0x710020bb2c
void set_setting_20bb2c(Setting20bb2c* object, int value) {
    if (static_cast<unsigned int>(value) <= 0x1)
        object->value = value;
}

struct Setting20bb3c {
    unsigned char pad[0x121];
    unsigned char value;      // +121
};

// 0x710020bb3c
void set_setting_20bb3c(Setting20bb3c* object, int value) {
    if (static_cast<unsigned int>(value) <= 0x1)
        object->value = value;
}

struct Setting20bb4c {
    unsigned char pad[0x122];
    unsigned char value;      // +122
};

// 0x710020bb4c
void set_setting_20bb4c(Setting20bb4c* object, int value) {
    if (static_cast<unsigned int>(value) <= 0x1)
        object->value = value;
}

struct Setting20bc04 {
    unsigned char pad[0x125];
    unsigned char value;      // +125
};

// 0x710020bc04
void set_setting_20bc04(Setting20bc04* object, int value) {
    if (static_cast<unsigned int>(value) <= 0x1)
        object->value = value;
}

struct Setting20bf50 {
    unsigned char pad[0x273];
    unsigned char value;      // +273
};

// 0x710020bf50
void set_setting_20bf50(Setting20bf50* object, int value) {
    if (static_cast<unsigned int>(value) <= 0x1)
        object->value = value;
}

struct Setting20bf60 {
    unsigned char pad[0x274];
    unsigned char value;      // +274
};

// 0x710020bf60
void set_setting_20bf60(Setting20bf60* object, int value) {
    if (static_cast<unsigned int>(value) <= 0xf)
        object->value = value;
}

struct Setting20bf70 {
    unsigned char pad[0x275];
    unsigned char value;      // +275
};

// 0x710020bf70
void set_setting_20bf70(Setting20bf70* object, int value) {
    if (static_cast<unsigned int>(value) <= 0xf)
        object->value = value;
}

struct Setting20bf80 {
    unsigned char pad[0x27b];
    unsigned char value;      // +27b
};

// 0x710020bf80
void set_setting_20bf80(Setting20bf80* object, int value) {
    if (static_cast<unsigned int>(value) <= 0x1)
        object->value = value;
}

struct Setting20bf90 {
    unsigned char pad[0x27c];
    unsigned char value;      // +27c
};

// 0x710020bf90
void set_setting_20bf90(Setting20bf90* object, int value) {
    if (static_cast<unsigned int>(value) <= 0x1)
        object->value = value;
}

struct Setting20bfa0 {
    unsigned char pad[0x281];
    unsigned char value;      // +281
};

// 0x710020bfa0
void set_setting_20bfa0(Setting20bfa0* object, int value) {
    if (static_cast<unsigned int>(value) <= 0x1)
        object->value = value;
}

struct Setting20bfb0 {
    unsigned char pad[0x282];
    unsigned char value;      // +282
};

// 0x710020bfb0
void set_setting_20bfb0(Setting20bfb0* object, int value) {
    if (static_cast<unsigned int>(value) <= 0x1)
        object->value = value;
}

struct Setting20c214 {
    unsigned char pad[0x27e];
    unsigned char value;      // +27e
};

// 0x710020c214
void set_setting_20c214(Setting20c214* object, int value) {
    if (static_cast<unsigned int>(value) <= 0x1)
        object->value = value;
}

struct Setting20c234 {
    unsigned char pad[0x280];
    unsigned char value;      // +280
};

// 0x710020c234
void set_setting_20c234(Setting20c234* object, int value) {
    if (static_cast<unsigned int>(value) <= 0x1)
        object->value = value;
}

struct FlagRow2079f4 {
    unsigned char flags[0xb];
};

// 0x71002079f4
void raise_flag_2079f4(FlagRow2079f4* rows, unsigned char row) {
    rows[row].flags[1] = 1;
}

struct FlagRow207a0c {
    unsigned char flags[0xb];
};

// 0x7100207a0c
void raise_flag_207a0c(FlagRow207a0c* rows, unsigned char row) {
    rows[row].flags[2] = 1;
}

struct FlagRow207a24 {
    unsigned char flags[0xb];
};

// 0x7100207a24
void raise_flag_207a24(FlagRow207a24* rows, unsigned char row) {
    rows[row].flags[3] = 1;
}

struct FlagRow207a3c {
    unsigned char flags[0xb];
};

// 0x7100207a3c
void raise_flag_207a3c(FlagRow207a3c* rows, unsigned char row) {
    rows[row].flags[4] = 1;
}

struct FlagRow207a54 {
    unsigned char flags[0xb];
};

// 0x7100207a54
void raise_flag_207a54(FlagRow207a54* rows, unsigned char row) {
    rows[row].flags[5] = 1;
}

struct FlagRow207a6c {
    unsigned char flags[0xb];
};

// 0x7100207a6c
void raise_flag_207a6c(FlagRow207a6c* rows, unsigned char row) {
    rows[row].flags[6] = 1;
}

struct FlagRow207a84 {
    unsigned char flags[0xb];
};

// 0x7100207a84
void raise_flag_207a84(FlagRow207a84* rows, unsigned char row) {
    rows[row].flags[7] = 1;
}

struct Toggle20bb8c {
    unsigned char pad[0x120];
    signed char value;        // +120
};

// 0x710020bb8c
int toggle_20bb8c(Toggle20bb8c* object) {
    int value = object->value;
    value = value < 0 ? 0 : value;
    return value > 1 ? 1 : value;
}

struct Toggle20bba8 {
    unsigned char pad[0x121];
    signed char value;        // +121
};

// 0x710020bba8
int toggle_20bba8(Toggle20bba8* object) {
    int value = object->value;
    value = value < 0 ? 0 : value;
    return value > 1 ? 1 : value;
}

struct Toggle20bbc4 {
    unsigned char pad[0x122];
    signed char value;        // +122
};

// 0x710020bbc4
int toggle_20bbc4(Toggle20bbc4* object) {
    int value = object->value;
    value = value < 0 ? 0 : value;
    return value > 1 ? 1 : value;
}

struct Toggle20bbe0 {
    unsigned char pad[0x124];
    signed char value;        // +124
};

// 0x710020bbe0
int toggle_20bbe0(Toggle20bbe0* object) {
    int value = object->value;
    value = value < 0 ? 0 : value;
    return value > 1 ? 1 : value;
}

struct Toggle20c18c {
    unsigned char pad[0x271];
    signed char value;        // +271
};

// 0x710020c18c
int toggle_20c18c(Toggle20c18c* object) {
    int value = object->value;
    value = value < 0 ? 0 : value;
    return value > 1 ? 1 : value;
}

struct Toggle20c1a8 {
    unsigned char pad[0x273];
    signed char value;        // +273
};

// 0x710020c1a8
int toggle_20c1a8(Toggle20c1a8* object) {
    int value = object->value;
    value = value < 0 ? 0 : value;
    return value > 1 ? 1 : value;
}

struct Saturating1a7ed8 {
    unsigned char pad[0x2460];
    unsigned char count;      // +2460
};

// 0x71001a7ed8
void bump_1a7ed8(Saturating1a7ed8* object) {
    if (object->count != 0xff)
        ++object->count;
}

struct Saturating1a7f04 {
    unsigned char pad[0x2461];
    unsigned char count;      // +2461
};

// 0x71001a7f04
void bump_1a7f04(Saturating1a7f04* object) {
    if (object->count != 0xff)
        ++object->count;
}

struct Saturating1a7f30 {
    unsigned char pad[0x2462];
    unsigned char count;      // +2462
};

// 0x71001a7f30
void bump_1a7f30(Saturating1a7f30* object) {
    if (object->count != 0xff)
        ++object->count;
}

struct Saturating1a7fe4 {
    unsigned char pad[0x2473];
    unsigned char count;      // +2473
};

// 0x71001a7fe4
void bump_1a7fe4(Saturating1a7fe4* object) {
    if (object->count != 0xff)
        ++object->count;
}

struct Saturating1a8060 {
    unsigned char pad[0x2478];
    unsigned char count;      // +2478
};

// 0x71001a8060
void bump_1a8060(Saturating1a8060* object) {
    if (object->count != 0xff)
        ++object->count;
}

struct OptByte3364b0 {
    unsigned char pad[0x28];
    unsigned char value;      // +28
};
// Reached through the GOT slot at 0x7100c2ae58.
extern OptByte3364b0* gOptional_3364b0;

// 0x71003364b0
unsigned char optional_byte_3364b0() {
    if (gOptional_3364b0)
        return gOptional_3364b0->value;
    return 0;
}

struct OptByte3ced74 {
    unsigned char pad[0x1a];
    unsigned char value;      // +1a
};
// Reached through the GOT slot at 0x7100c2b550.
extern OptByte3ced74* gOptional_3ced74;

// 0x71003ced74
unsigned char optional_byte_3ced74() {
    if (gOptional_3ced74)
        return gOptional_3ced74->value;
    return 0;
}

struct OptByte3cedbc {
    unsigned char pad[0x1b];
    unsigned char value;      // +1b
};
// Reached through the GOT slot at 0x7100c2b550.
extern OptByte3cedbc* gOptional_3cedbc;

// 0x71003cedbc
unsigned char optional_byte_3cedbc() {
    if (gOptional_3cedbc)
        return gOptional_3cedbc->value;
    return 0;
}

struct OptByte3ceddc {
    unsigned char pad[0x1c];
    unsigned char value;      // +1c
};
// Reached through the GOT slot at 0x7100c2b550.
extern OptByte3ceddc* gOptional_3ceddc;

// 0x71003ceddc
unsigned char optional_byte_3ceddc() {
    if (gOptional_3ceddc)
        return gOptional_3ceddc->value;
    return 0;
}

struct OptByte3cee04 {
    unsigned char pad[0x1e];
    unsigned char value;      // +1e
};
// Reached through the GOT slot at 0x7100c2b550.
extern OptByte3cee04* gOptional_3cee04;

// 0x71003cee04
unsigned char optional_byte_3cee04() {
    if (gOptional_3cee04)
        return gOptional_3cee04->value;
    return 0;
}

struct PlacedNode {
    unsigned char pad[0x30];
    float x;                  // +30
    float y;                  // +34
    float z;                  // +38
    unsigned char pad3c[0x1c];
    unsigned char flags;      // +58
};
struct PlacedMiddle {
    unsigned char pad[0x18];
    PlacedNode* node;         // +18
};

struct Placer38cc48 {
    unsigned char pad[0x8];
    PlacedMiddle* middle;     // +8
};

// 0x710038cc48
void place_38cc48(Placer38cc48* object, float x, float y) {
    PlacedNode* node = object->middle->node;
    node->x = x;
    node->y = y;
    node->z = 0.0f;
    node->flags |= 0x10;
}

struct Placer39dfcc {
    unsigned char pad[0x8];
    PlacedMiddle* middle;     // +8
};

// 0x710039dfcc
void place_39dfcc(Placer39dfcc* object, float x, float y) {
    PlacedNode* node = object->middle->node;
    node->x = x;
    node->y = y;
    node->z = 0.0f;
    node->flags |= 0x10;
}

struct Placer3a4950 {
    unsigned char pad[0x2320];
    PlacedMiddle* middle;     // +2320
};

// 0x71003a4950
void place_3a4950(Placer3a4950* object, float x, float y) {
    PlacedNode* node = object->middle->node;
    node->x = x;
    node->y = y;
    node->z = 0.0f;
    node->flags |= 0x10;
}

struct Placer3a5464 {
    PlacedMiddle* middle;     // +0
};

// 0x71003a5464
void place_3a5464(Placer3a5464* object, float x, float y) {
    PlacedNode* node = object->middle->node;
    node->x = x;
    node->y = y;
    node->z = 0.0f;
    node->flags |= 0x10;
}

struct Bits213fcc {
    unsigned char pad[0xb];
    unsigned char bits[1];    // +b
};

// 0x7100213fcc
unsigned char bit_on_213fcc(Bits213fcc* set, unsigned int id) {
    if (id <= 0x7)
        return (set->bits[id >> 3] & (1 << (id & 7))) != 0;
    return 0;
}

struct Bits21516c {
    unsigned char pad[0x4];
    unsigned char bits[1];    // +4
};

// 0x710021516c
unsigned char bit_on_21516c(Bits21516c* set, unsigned int id) {
    if (id <= 0x7)
        return (set->bits[id >> 3] & (1 << (id & 7))) != 0;
    return 0;
}

struct Bits216134 {
    unsigned char pad[0x1e];
    unsigned char bits[1];    // +1e
};

// 0x7100216134
unsigned char bit_on_216134(Bits216134* set, unsigned int id) {
    if (id <= 0x4)
        return (set->bits[id >> 3] & (1 << (id & 7))) != 0;
    return 0;
}

class Counter5fa9e4 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual int count();      // +20
};
struct ScaledCount5fa9e4 {
    unsigned char pad[0xc];
    float scale;              // +c
    unsigned char pad10[0x18];
    Counter5fa9e4* counter;  // +28
};

// 0x71005fa9e4
float scaled_count_5fa9e4(ScaledCount5fa9e4* object) {
    return object->counter->count() * object->scale;
}

class Counter5faa1c {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual int count();      // +28
};
struct ScaledCount5faa1c {
    unsigned char pad[0x10];
    float scale;              // +10
    unsigned char pad14[0x14];
    Counter5faa1c* counter;  // +28
};

// 0x71005faa1c
float scaled_count_5faa1c(ScaledCount5faa1c* object) {
    return object->counter->count() * object->scale;
}

class Counter5faa54 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual int count();      // +30
};
struct ScaledCount5faa54 {
    unsigned char pad[0x10];
    float scale;              // +10
    unsigned char pad14[0x14];
    Counter5faa54* counter;  // +28
};

// 0x71005faa54
float scaled_count_5faa54(ScaledCount5faa54* object) {
    return object->counter->count() * object->scale;
}

struct Triple3d6b88 {
    void* slots[3];
};
struct Triples3d6b88 {
    unsigned char pad[0x710dc];
    unsigned int frame;       // +710dc
    unsigned char pad710e0[0x100];
    Triple3d6b88 rows[1];   // +711e0
};

// 0x71003d6b88
void* current_slot_3d6b88(Triples3d6b88* object, int row) {
    return object->rows[row].slots[object->frame % 3];
}

struct Triple3d6bc8 {
    void* slots[3];
};
struct Triples3d6bc8 {
    unsigned char pad[0x710e0];
    unsigned int frame;       // +710e0
    unsigned char pad710e4[0xfc];
    Triple3d6bc8 rows[1];   // +711e0
};

// 0x71003d6bc8
void* current_slot_3d6bc8(Triples3d6bc8* object, int row) {
    return object->rows[row].slots[object->frame % 3];
}

struct Triple3d6f10 {
    void* slots[3];
};
struct Triples3d6f10 {
    unsigned char pad[0x710dc];
    unsigned int frame;       // +710dc
    unsigned char pad710e0[0xb58];
    Triple3d6f10 rows[1];   // +71c38
};

// 0x71003d6f10
void* current_slot_3d6f10(Triples3d6f10* object, int row) {
    return object->rows[row].slots[object->frame % 3];
}

struct Triple3d6f50 {
    void* slots[3];
};
struct Triples3d6f50 {
    unsigned char pad[0x710dc];
    unsigned int frame;       // +710dc
    unsigned char pad710e0[0xb28];
    Triple3d6f50 rows[1];   // +71c08
};

// 0x71003d6f50
void* current_slot_3d6f50(Triples3d6f50* object, int row) {
    return object->rows[row].slots[object->frame % 3];
}

struct Triple3d6f90 {
    void* slots[3];
};
struct Triples3d6f90 {
    unsigned char pad[0x710e0];
    unsigned int frame;       // +710e0
    unsigned char pad710e4[0xb24];
    Triple3d6f90 rows[1];   // +71c08
};

// 0x71003d6f90
void* current_slot_3d6f90(Triples3d6f90* object, int row) {
    return object->rows[row].slots[object->frame % 3];
}
