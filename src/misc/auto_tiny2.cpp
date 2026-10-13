// More tiny functions synthesized from their instructions: flag sets and clears, wide clears,
// far byte reads, equality and range tests, child forwards with a constant, chained reads, entry
// finds, bit fields, constant byte stores, far member addresses, masked stores, indexed reads and
// writes, and global addresses and values. Types and functions are named after their address.
// Status: matching/README.md.

struct FarHolder37fa8 {
    unsigned char pad0[0x84d0];
    unsigned char member[1];  // +84d0
};

// 0x7100037fa8
void* far_member_37fa8(FarHolder37fa8* object) {
    return object->member;
}

struct Cleared4d3b0 {
    long value0;
    long value1;
};

// 0x710004d3b0
void clear_all_4d3b0(Cleared4d3b0* object) {
    object->value0 = 0;
    object->value1 = 0;
}

struct Cleared4d3bc {
    long value0;
    long value1;
    long value2;
    long value3;
    long value4;
    long value5;
    long value6;
    long value7;
};

// 0x710004d3bc
void clear_all_4d3bc(Cleared4d3bc* object) {
    object->value6 = 0;
    object->value7 = 0;
    object->value4 = 0;
    object->value5 = 0;
    object->value2 = 0;
    object->value3 = 0;
    object->value0 = 0;
    object->value1 = 0;
}

struct Cleared4d3d4 {
    long value0;
    long value1;
    long value2;
    long value3;
    long value4;
    long value5;
};

// 0x710004d3d4
void clear_all_4d3d4(Cleared4d3d4* object) {
    object->value4 = 0;
    object->value5 = 0;
    object->value2 = 0;
    object->value3 = 0;
    object->value0 = 0;
    object->value1 = 0;
}

struct Cleared4d3e8 {
    long value0;
    long value1;
};

// 0x710004d3e8
void clear_all_4d3e8(Cleared4d3e8* object) {
    object->value0 = 0;
    object->value1 = 0;
}

struct Cleared4d3f4 {
    long value0;
    long value1;
    long value2;
    long value3;
};

// 0x710004d3f4
void clear_all_4d3f4(Cleared4d3f4* object) {
    object->value2 = 0;
    object->value3 = 0;
    object->value0 = 0;
    object->value1 = 0;
}

struct Cleared4d938 {
    long value0;
    long value1;
    long value2;
    long value3;
};

// 0x710004d938
void clear_all_4d938(Cleared4d938* object) {
    object->value2 = 0;
    object->value3 = 0;
    object->value0 = 0;
    object->value1 = 0;
}

struct Cleared4db84 {
    long value0;
    long value1;
    long value2;
    long value3;
};

// 0x710004db84
void clear_all_4db84(Cleared4db84* object) {
    object->value2 = 0;
    object->value3 = 0;
    object->value0 = 0;
    object->value1 = 0;
}

struct Inner4dc08 {
    unsigned char pad0[0x674];
    int value;  // +674
};
struct Outer4dc08 {
    unsigned char pad0[0x20];
    Inner4dc08* inner;  // +20
};

// 0x710004dc08
int inner_4dc08(Outer4dc08* object) {
    return object->inner->value;
}

struct Flag6abb8 {
    unsigned char pad0[0x4];
    unsigned short value;  // +4
};

// 0x710006abb8
void set_value_6abb8(Flag6abb8* object) {
    object->value = 0xffff;
}

struct Cleared6cc38 {
    long value0;
    long value1;
};

// 0x710006cc38
void clear_all_6cc38(Cleared6cc38* object) {
    object->value0 = 0;
    object->value1 = 0;
}

struct Flags7b278 {
    unsigned char pad0[0x50];
    unsigned long flags;  // +50
};

// 0x710007b278
void raise_flags_7b278(Flags7b278* object) {
    object->flags |= 0x100ul;
}

struct Flags8c5f4 {
    unsigned char pad0[0x50];
    unsigned long flags;  // +50
};

// 0x710008c5f4
void raise_flags_8c5f4(Flags8c5f4* object) {
    object->flags |= 0x1000000ul;
}

struct Packed99718 {
    unsigned char pad0[0x50];
    unsigned int bits;  // +50
};

// 0x7100099718
unsigned int bits_99718(Packed99718* object) {
    return (object->bits >> 28) & 0x1;
}

struct Flags99810 {
    unsigned char pad0[0x50];
    unsigned long flags;  // +50
};

// 0x7100099810
void raise_flags_99810(Flags99810* object) {
    object->flags |= 0x800000000ul;
}

struct Flags99820 {
    unsigned char pad0[0x50];
    unsigned long flags;  // +50
};

// 0x7100099820
void raise_flags_99820(Flags99820* object) {
    object->flags |= 0x400000000ul;
}

struct Arrayba590 {
    unsigned char pad0[0x34];
    float values[1];  // +34
};

// 0x71000ba590
float at_ba590(Arrayba590* object, int index) {
    return object->values[index];
}

struct Flagcf638 {
    unsigned char pad0[0x8];
    unsigned char value;  // +8
};

// 0x71000cf638
void set_value_cf638(Flagcf638* object) {
    object->value = 0x1;
}

struct Flag12c26c {
    unsigned char pad0[0xac0];
    unsigned char value;  // +ac0
};

// 0x710012c26c
void set_value_12c26c(Flag12c26c* object) {
    object->value = 0x1;
}

struct Flags1336a8 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x71001336a8
void clear_flags_1336a8(Flags1336a8* object) {
    object->flags &= ~0x4u;
}

struct Flags133810 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133810
void clear_flags_133810(Flags133810* object) {
    object->flags &= ~0x40u;
}

struct Flags1338c0 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x71001338c0
void clear_flags_1338c0(Flags1338c0* object) {
    object->flags &= ~0x80u;
}

struct Flags133970 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133970
void clear_flags_133970(Flags133970* object) {
    object->flags &= ~0x400u;
}

struct Flags133a20 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133a20
void clear_flags_133a20(Flags133a20* object) {
    object->flags &= ~0x100u;
}

struct Flags133ad0 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133ad0
void clear_flags_133ad0(Flags133ad0* object) {
    object->flags &= ~0x800u;
}

struct Flags133ae0 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133ae0
void raise_flags_133ae0(Flags133ae0* object) {
    object->flags |= 0x200u;
}

struct Flags133af0 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133af0
void clear_flags_133af0(Flags133af0* object) {
    object->flags &= ~0x200u;
}

struct Flags133ba0 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133ba0
void clear_flags_133ba0(Flags133ba0* object) {
    object->flags &= ~0x100000u;
}

struct Flags133bb0 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133bb0
void raise_flags_133bb0(Flags133bb0* object) {
    object->flags |= 0x200000u;
}

struct Flags133bc0 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133bc0
void clear_flags_133bc0(Flags133bc0* object) {
    object->flags &= ~0x200000u;
}

struct Flags133bd0 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133bd0
void raise_flags_133bd0(Flags133bd0* object) {
    object->flags |= 0x400000u;
}

struct Flags133be0 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133be0
void clear_flags_133be0(Flags133be0* object) {
    object->flags &= ~0x400000u;
}

struct Flags133bf0 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133bf0
void raise_flags_133bf0(Flags133bf0* object) {
    object->flags |= 0x800000u;
}

struct Flags133c00 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133c00
void clear_flags_133c00(Flags133c00* object) {
    object->flags &= ~0x800000u;
}

struct Flags133c10 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133c10
void raise_flags_133c10(Flags133c10* object) {
    object->flags |= 0x10000u;
}

struct Flags133c20 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133c20
void clear_flags_133c20(Flags133c20* object) {
    object->flags &= ~0x10000u;
}

struct Flags133c30 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133c30
void raise_flags_133c30(Flags133c30* object) {
    object->flags |= 0x4000u;
}

struct Flags133c40 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133c40
void clear_flags_133c40(Flags133c40* object) {
    object->flags &= ~0x4000u;
}

struct Flags133c50 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133c50
void raise_flags_133c50(Flags133c50* object) {
    object->flags |= 0x8000u;
}

struct Flags133c60 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133c60
void clear_flags_133c60(Flags133c60* object) {
    object->flags &= ~0x8000u;
}

struct Flags133c70 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133c70
void raise_flags_133c70(Flags133c70* object) {
    object->flags |= 0x20000u;
}

struct Flags133c80 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133c80
void clear_flags_133c80(Flags133c80* object) {
    object->flags &= ~0x20000u;
}

struct Flags133c90 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133c90
void raise_flags_133c90(Flags133c90* object) {
    object->flags |= 0x40000u;
}

struct Flags133ca0 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133ca0
void raise_flags_133ca0(Flags133ca0* object) {
    object->flags |= 0x80000u;
}

struct Flags133cb0 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133cb0
void clear_flags_133cb0(Flags133cb0* object) {
    object->flags &= ~0x80000u;
}

struct Packed133cc0 {
    unsigned char pad0[0x88];
    unsigned int bits;  // +88
};

// 0x7100133cc0
unsigned int bits_133cc0(Packed133cc0* object) {
    return (object->bits >> 19) & 0x1;
}

struct Flags133ccc {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133ccc
void raise_flags_133ccc(Flags133ccc* object) {
    object->flags |= 0x1000000u;
}

struct Flags133cdc {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133cdc
void clear_flags_133cdc(Flags133cdc* object) {
    object->flags &= ~0x1000000u;
}

struct Flags133cf8 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133cf8
void raise_flags_133cf8(Flags133cf8* object) {
    object->flags |= 0x2000000u;
}

struct Packed133d08 {
    unsigned char pad0[0x88];
    unsigned int bits;  // +88
};

// 0x7100133d08
unsigned int bits_133d08(Packed133d08* object) {
    return (object->bits >> 25) & 0x1;
}

struct Flags133d14 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133d14
void raise_flags_133d14(Flags133d14* object) {
    object->flags |= 0x4000000u;
}

struct Flags133d24 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133d24
void clear_flags_133d24(Flags133d24* object) {
    object->flags &= ~0x4000000u;
}

struct Packed133d34 {
    unsigned char pad0[0x88];
    unsigned int bits;  // +88
};

// 0x7100133d34
unsigned int bits_133d34(Packed133d34* object) {
    return (object->bits >> 26) & 0x1;
}

struct Flags133d80 {
    unsigned char pad0[0x88];
    unsigned int flags;  // +88
};

// 0x7100133d80
void clear_flags_133d80(Flags133d80* object) {
    object->flags &= ~0x8000000u;
}

struct FarHolder14a8e4 {
    unsigned char pad0[0x4a88];
    unsigned char member[1];  // +4a88
};

// 0x710014a8e4
void* far_member_14a8e4(FarHolder14a8e4* object) {
    return object->member;
}

struct FarHolder152464 {
    unsigned char pad0[0x2200];
    unsigned char member[1];  // +2200
};

// 0x7100152464
void* far_member_152464(FarHolder152464* object) {
    return object->member;
}

struct Packed15aa44 {
    unsigned char pad0[0x150];
    unsigned int bits;  // +150
};

// 0x710015aa44
unsigned int bits_15aa44(Packed15aa44* object) {
    return (object->bits >> 1) & 0x1;
}

extern int gValue_c337b8 __attribute__((visibility("hidden"))); // 0x7100c337b8

// 0x7100170c58
int global_value_170c58() {
    return gValue_c337b8;
}

struct Masked193608 {
    unsigned char pad0[0x4];
    unsigned int value;  // +4
};

// 0x7100193608
void set_masked_193608(Masked193608* object, unsigned int value) {
    object->value = value & 0xff;
}

struct Flag19b108 {
    unsigned short value;  // +0
};

// 0x710019b108
void set_value_19b108(Flag19b108* object) {
    object->value = 0x1880;
}

struct Ranged19ba10 {
    unsigned char pad0[0x24];
    unsigned int value;  // +24
};

// 0x710019ba10
int ranged_19ba10(Ranged19ba10* object) {
    unsigned int value = object->value;
    return value < 0xc9 ? static_cast<int>(value) : -1;
}

struct Masked19baf4 {
    unsigned char pad0[0x1c];
    unsigned int value;  // +1c
};

// 0x710019baf4
void set_masked_19baf4(Masked19baf4* object, unsigned int value) {
    object->value = value & 0xff;
}

struct Array19bde0 {
    unsigned char pad0[0x50];
    int values[1];  // +50
};

// 0x710019bde0
void put_19bde0(Array19bde0* object, int index, int value) {
    object->values[index] = value;
}

struct FarHolder19cfe8 {
    unsigned char pad0[0x39ac];
    unsigned char member[1];  // +39ac
};

// 0x710019cfe8
void* far_member_19cfe8(FarHolder19cfe8* object) {
    return object->member;
}

struct Array19cff4 {
    unsigned char pad0[0x3e7c];
    int values[1];  // +3e7c
};

// 0x710019cff4
int at_19cff4(Array19cff4* object, unsigned int index) {
    return object->values[index];
}

struct Array1a38f4 {
    unsigned char pad0[0x324];
    unsigned char values[1];  // +324
};

// 0x71001a38f4
unsigned char at_1a38f4(Array1a38f4* object, unsigned int index) {
    return object->values[index];
}

struct Array1a3990 {
    unsigned char pad0[0x1f8];
    int values[1];  // +1f8
};

// 0x71001a3990
int at_1a3990(Array1a3990* object, unsigned int index) {
    return object->values[index];
}

struct Array1a399c {
    unsigned char pad0[0x1f8];
    int values[1];  // +1f8
};

// 0x71001a399c
void put_1a399c(Array1a399c* object, unsigned int index, int value) {
    object->values[index] = value;
}

struct Tested1a76c0 {
    unsigned char pad0[0x19ec];
    int value;  // +19ec
};

// 0x71001a76c0
unsigned char test_1a76c0(Tested1a76c0* object) {
    return object->value == 1;
}

struct Tested1a76d8 {
    unsigned char pad0[0x19ec];
    int value;  // +19ec
};

// 0x71001a76d8
unsigned char test_1a76d8(Tested1a76d8* object) {
    return object->value == 1;
}

struct Tested1a76e8 {
    unsigned char pad0[0x19ec];
    int value;  // +19ec
};

// 0x71001a76e8
unsigned char test_1a76e8(Tested1a76e8* object) {
    return object->value == 1;
}

struct Far1a7720 {
    unsigned char pad0[0x1f4c];
    unsigned char value;  // +1f4c
};

// 0x71001a7720
unsigned char far_1a7720(Far1a7720* object) {
    return object->value;
}

struct Far1a7738 {
    unsigned char pad0[0x1f4d];
    unsigned char value;  // +1f4d
};

// 0x71001a7738
unsigned char far_1a7738(Far1a7738* object) {
    return object->value;
}

struct Far1a7ecc {
    unsigned char pad0[0x2460];
    unsigned char value;  // +2460
};

// 0x71001a7ecc
unsigned char far_1a7ecc(Far1a7ecc* object) {
    return object->value;
}

struct Far1a7ef8 {
    unsigned char pad0[0x2461];
    unsigned char value;  // +2461
};

// 0x71001a7ef8
unsigned char far_1a7ef8(Far1a7ef8* object) {
    return object->value;
}

struct Far1a7f24 {
    unsigned char pad0[0x2462];
    unsigned char value;  // +2462
};

// 0x71001a7f24
unsigned char far_1a7f24(Far1a7f24* object) {
    return object->value;
}

struct Far1a7fd8 {
    unsigned char pad0[0x2473];
    unsigned char value;  // +2473
};

// 0x71001a7fd8
unsigned char far_1a7fd8(Far1a7fd8* object) {
    return object->value;
}

struct Far1a8054 {
    unsigned char pad0[0x2478];
    unsigned char value;  // +2478
};

// 0x71001a8054
unsigned char far_1a8054(Far1a8054* object) {
    return object->value;
}

struct Array1a8d3c {
    unsigned char pad0[0x14];
    int values[1];  // +14
};

// 0x71001a8d3c
int at_1a8d3c(Array1a8d3c* object, int index) {
    return object->values[index];
}

struct Array1a8d48 {
    unsigned char pad0[0x14];
    int values[1];  // +14
};

// 0x71001a8d48
void put_1a8d48(Array1a8d48* object, int index, int value) {
    object->values[index] = value;
}

struct Masked1b0330 {
    unsigned char pad0[0x4];
    unsigned int value;  // +4
};

// 0x71001b0330
void set_masked_1b0330(Masked1b0330* object, unsigned int value) {
    object->value = value & 0xff;
}

struct Masked1ba2d0 {
    unsigned char pad0[0x4];
    unsigned int value;  // +4
};

// 0x71001ba2d0
void set_masked_1ba2d0(Masked1ba2d0* object, unsigned int value) {
    object->value = value & 0xff;
}

struct Array1ccd2c {
    unsigned char pad0[0x140];
    int values[1];  // +140
};

// 0x71001ccd2c
int at_1ccd2c(Array1ccd2c* object, unsigned int index) {
    return object->values[index];
}

struct Array1ccd38 {
    unsigned char pad0[0x140];
    int values[1];  // +140
};

// 0x71001ccd38
void put_1ccd38(Array1ccd38* object, unsigned int index, int value) {
    object->values[index] = value;
}

struct Array1ccf20 {
    unsigned char pad0[0x67c];
    int values[1];  // +67c
};

// 0x71001ccf20
int at_1ccf20(Array1ccf20* object, unsigned int index) {
    return object->values[index];
}

struct Array1ccf2c {
    unsigned char pad0[0x67c];
    int values[1];  // +67c
};

// 0x71001ccf2c
void put_1ccf2c(Array1ccf2c* object, unsigned int index, int value) {
    object->values[index] = value;
}

struct Tested1e52c8 {
    unsigned char pad0[0x1fc];
    int value;  // +1fc
};

// 0x71001e52c8
unsigned char test_1e52c8(Tested1e52c8* object) {
    return object->value == 0;
}

struct Entry1feadc {
    unsigned char data[0x1c8];
};
class Entries1feadc {
public:
    Entry1feadc* find(int index) {
        return static_cast<unsigned int>(index) < 0x4b ? &entries[index] : nullptr;
    }

    Entry1feadc entries[0x4b];
};

// 0x71001feadc
Entry1feadc* find_1feadc(Entries1feadc* table, int index) {
    return table->find(index);
}

struct Entry201594 {
    unsigned char data[0xa8];
};
class Entries201594 {
public:
    Entry201594* find(int index) {
        return static_cast<unsigned int>(index) < 0x64 ? &entries[index] : nullptr;
    }

    Entry201594 entries[0x64];
};

// 0x7100201594
Entry201594* find_201594(Entries201594* table, int index) {
    return table->find(index);
}

struct Far203c94 {
    unsigned char pad0[0x1992];
    signed char value;  // +1992
};

// 0x7100203c94
int far_203c94(Far203c94* object) {
    return object->value;
}

struct Far203cf4 {
    unsigned char pad0[0x1993];
    unsigned char value;  // +1993
};

// 0x7100203cf4
unsigned char far_203cf4(Far203cf4* object) {
    return object->value;
}

struct Far204168 {
    unsigned char pad0[0x1a18];
    unsigned char value;  // +1a18
};

// 0x7100204168
unsigned char far_204168(Far204168* object) {
    return object->value;
}

struct Far20422c {
    unsigned char pad0[0x1a19];
    unsigned char value;  // +1a19
};

// 0x710020422c
unsigned char far_20422c(Far20422c* object) {
    return object->value;
}

struct Far2045fc {
    unsigned char pad0[0x26d0];
    unsigned char value;  // +26d0
};

// 0x71002045fc
unsigned char far_2045fc(Far2045fc* object) {
    return object->value;
}

struct Far204614 {
    unsigned char pad0[0x26d1];
    unsigned char value;  // +26d1
};

// 0x7100204614
unsigned char far_204614(Far204614* object) {
    return object->value;
}

struct FarHolder20471c {
    unsigned char pad0[0x26c8];
    unsigned char member[1];  // +26c8
};

// 0x710020471c
void* far_member_20471c(FarHolder20471c* object) {
    return object->member;
}

struct Tested2061ac {
    unsigned char pad0[0x15];
    unsigned char value;  // +15
};

// 0x71002061ac
unsigned char test_2061ac(Tested2061ac* object) {
    return object->value == 99;
}

struct Array2061bc {
    unsigned char pad0[0x16];
    unsigned char values[1];  // +16
};

// 0x71002061bc
unsigned char at_2061bc(Array2061bc* object, int index) {
    return object->values[index];
}

struct Array2061c8 {
    unsigned char pad0[0x16];
    unsigned char values[1];  // +16
};

// 0x71002061c8
void put_2061c8(Array2061c8* object, int index, unsigned char value) {
    object->values[index] = value;
}

struct Flag2079c4 {
    unsigned char pad0[0xa5];
    unsigned char value;  // +a5
};

// 0x71002079c4
void set_value_2079c4(Flag2079c4* object) {
    object->value = 0x1;
}

struct Flag2079d0 {
    unsigned char pad0[0xa6];
    unsigned char value;  // +a6
};

// 0x71002079d0
void set_value_2079d0(Flag2079d0* object) {
    object->value = 0x1;
}

struct Ranged209fec {
    unsigned int value;  // +0
};

// 0x7100209fec
int ranged_209fec(Ranged209fec* object) {
    unsigned int value = object->value;
    return value < 0xc9 ? static_cast<int>(value) : -1;
}

struct Entry20c154 {
    unsigned char data[0x138];
};
class Entries20c154 {
public:
    Entry20c154* find(int index) {
        return static_cast<unsigned int>(index) < 0x2 ? &entries[index] : nullptr;
    }

    Entry20c154 entries[0x2];
};

// 0x710020c154
Entry20c154* find_20c154(Entries20c154* table, int index) {
    return table->find(index);
}

struct Array20c56c {
    unsigned char pad0[0x30];
    unsigned char values[1];  // +30
};

// 0x710020c56c
unsigned char at_20c56c(Array20c56c* object, int index) {
    return object->values[index];
}

struct Array20c580 {
    unsigned char pad0[0xc];
    unsigned short values[1];  // +c
};

// 0x710020c580
unsigned short at_20c580(Array20c580* object, int index) {
    return object->values[index];
}

struct Array20c9f8 {
    unsigned char pad0[0xac];
    int values[1];  // +ac
};

// 0x710020c9f8
int at_20c9f8(Array20c9f8* object, unsigned int index) {
    return object->values[index];
}

struct Array20ca38 {
    unsigned char pad0[0x8c];
    int values[1];  // +8c
};

// 0x710020ca38
int at_20ca38(Array20ca38* object, int index) {
    return object->values[index];
}

struct Ranged210624 {
    unsigned int value;  // +0
};

// 0x7100210624
int ranged_210624(Ranged210624* object) {
    unsigned int value = object->value;
    return value < 0x100 ? static_cast<int>(value) : -1;
}

struct Entry2108dc {
    unsigned char data[0x64];
};
class Entries2108dc {
public:
    Entry2108dc* find(unsigned int index) {
        return static_cast<unsigned int>(index) < 0x100 ? &entries[index] : nullptr;
    }

    Entry2108dc entries[0x100];
};

// 0x71002108dc
Entry2108dc* find_2108dc(Entries2108dc* table, unsigned int index) {
    return table->find(index);
}

struct Ranged213ef0 {
    unsigned int value;  // +0
};

// 0x7100213ef0
int ranged_213ef0(Ranged213ef0* object) {
    unsigned int value = object->value;
    return value < 0x27f ? static_cast<int>(value) : -1;
}

struct Ranged214524 {
    unsigned int value;  // +0
};

// 0x7100214524
int ranged_214524(Ranged214524* object) {
    unsigned int value = object->value;
    return value < 0x40 ? static_cast<int>(value) : -1;
}

struct Entry214aa8 {
    unsigned char data[0x28];
};
class Entries214aa8 {
public:
    Entry214aa8* find(int index) {
        return static_cast<unsigned int>(index) < 0x40 ? &entries[index] : nullptr;
    }

    Entry214aa8 entries[0x40];
};

// 0x7100214aa8
Entry214aa8* find_214aa8(Entries214aa8* table, int index) {
    return table->find(index);
}

struct Ranged215114 {
    unsigned int value;  // +0
};

// 0x7100215114
int ranged_215114(Ranged215114* object) {
    unsigned int value = object->value;
    return value < 0x40 ? static_cast<int>(value) : -1;
}

struct Entry215354 {
    unsigned char data[0x14];
};
class Entries215354 {
public:
    Entry215354* find(int index) {
        return static_cast<unsigned int>(index) < 0x40 ? &entries[index] : nullptr;
    }

    Entry215354 entries[0x40];
};

// 0x7100215354
Entry215354* find_215354(Entries215354* table, int index) {
    return table->find(index);
}

struct Entry215978 {
    unsigned char data[0x10c];
};
class Entries215978 {
public:
    Entry215978* find(int index) {
        return static_cast<unsigned int>(index) < 0xa ? &entries[index] : nullptr;
    }

    Entry215978 entries[0xa];
};

// 0x7100215978
Entry215978* find_215978(Entries215978* table, int index) {
    return table->find(index);
}

struct Ranged216cd0 {
    unsigned char pad0[0x28];
    unsigned int value;  // +28
};

// 0x7100216cd0
int ranged_216cd0(Ranged216cd0* object) {
    unsigned int value = object->value;
    return value < 0x406 ? static_cast<int>(value) : -1;
}

struct Entry216f88 {
    unsigned char data[0x54];
};
class Entries216f88 {
public:
    Entry216f88* find(int index) {
        return static_cast<unsigned int>(index) < 0x406 ? &entries[index] : nullptr;
    }

    Entry216f88 entries[0x406];
};

// 0x7100216f88
Entry216f88* find_216f88(Entries216f88* table, int index) {
    return table->find(index);
}

struct Inner2192b4 {
    unsigned char pad0[0x8];
    unsigned short value;  // +8
};
struct Outer2192b4 {
    unsigned char pad0[0x8];
    Inner2192b4* inner;  // +8
};

// 0x71002192b4
unsigned short inner_2192b4(Outer2192b4* object) {
    return object->inner->value;
}

struct Flag244958 {
    unsigned char pad0[0x18];
    unsigned short value;  // +18
};

// 0x7100244958
void set_value_244958(Flag244958* object) {
    object->value = 0x3;
}

struct Array2549a8 {
    unsigned char pad0[0xe58];
    long values[1];  // +e58
};

// 0x71002549a8
long at_2549a8(Array2549a8* object, int index) {
    return object->values[index];
}

struct Tested2985b4 {
    unsigned char pad0[0x10];
    int value;  // +10
};

// 0x71002985b4
unsigned char test_2985b4(Tested2985b4* object) {
    return object->value == 0;
}

struct Flag2dbc30 {
    unsigned char pad0[0xf];
    unsigned char value;  // +f
};

// 0x71002dbc30
void set_value_2dbc30(Flag2dbc30* object) {
    object->value = 0x1;
}

extern int gValue_bd3b38 __attribute__((visibility("hidden"))); // 0x7100bd3b38

// 0x71002dee3c
int global_value_2dee3c() {
    return gValue_bd3b38;
}

struct Flag3ad9a4 {
    unsigned char pad0[0x1a];
    unsigned char value;  // +1a
};

// 0x71003ad9a4
void set_value_3ad9a4(Flag3ad9a4* object) {
    object->value = 0x1;
}

struct Ranged3b21c4 {
    unsigned char pad0[0x10];
    unsigned int value;  // +10
};

// 0x71003b21c4
int ranged_3b21c4(Ranged3b21c4* object) {
    unsigned int value = object->value;
    return value < 0x10 ? static_cast<int>(value) : -1;
}

struct Ranged3b21e8 {
    unsigned char pad0[0x24];
    unsigned int value;  // +24
};

// 0x71003b21e8
int ranged_3b21e8(Ranged3b21e8* object) {
    unsigned int value = object->value;
    return value < 0x4 ? static_cast<int>(value) : -1;
}

extern int gValue_ca31b8 __attribute__((visibility("hidden"))); // 0x7100ca31b8

// 0x71003cc924
int global_value_3cc924() {
    return gValue_ca31b8;
}

extern int gValue_bdbfc8 __attribute__((visibility("hidden"))); // 0x7100bdbfc8

// 0x71003cc9ec
int global_value_3cc9ec() {
    return gValue_bdbfc8;
}

struct Cleared3dca9c {
    long value0;
    long value1;
    long value2;
    long value3;
};

// 0x71003dca9c
void clear_all_3dca9c(Cleared3dca9c* object) {
    object->value2 = 0;
    object->value3 = 0;
    object->value0 = 0;
    object->value1 = 0;
}

struct Cleared3dcabc {
    long value0;
    long value1;
    long value2;
    long value3;
};

// 0x71003dcabc
void clear_all_3dcabc(Cleared3dcabc* object) {
    object->value2 = 0;
    object->value3 = 0;
    object->value0 = 0;
    object->value1 = 0;
}

struct Tested3df658 {
    unsigned char pad0[0x3340];
    int value;  // +3340
};

// 0x71003df658
unsigned char test_3df658(Tested3df658* object) {
    return object->value == 1;
}

struct Tested3df668 {
    unsigned char pad0[0x3340];
    int value;  // +3340
};

// 0x71003df668
unsigned char test_3df668(Tested3df668* object) {
    return object->value == 2;
}

struct Tested3dfb24 {
    unsigned char pad0[0x3344];
    int value;  // +3344
};

// 0x71003dfb24
unsigned char test_3dfb24(Tested3dfb24* object) {
    return object->value == 0;
}

struct Array3e0300 {
    unsigned char pad0[0x408];
    long values[1];  // +408
};

// 0x71003e0300
long at_3e0300(Array3e0300* object, unsigned int index) {
    return object->values[index];
}

struct Flags3eed38 {
    unsigned char pad0[0x58];
    unsigned int flags;  // +58
};

// 0x71003eed38
void raise_flags_3eed38(Flags3eed38* object) {
    object->flags |= 0x1u;
}

struct Cleared40d878 {
    long value0;
    long value1;
    long value2;
    long value3;
};

// 0x710040d878
void clear_all_40d878(Cleared40d878* object) {
    object->value2 = 0;
    object->value3 = 0;
    object->value0 = 0;
    object->value1 = 0;
}

struct Tested41bf48 {
    unsigned char pad0[0x20];
    int value;  // +20
};

// 0x710041bf48
unsigned char test_41bf48(Tested41bf48* object) {
    return object->value == 83;
}

struct Cleared41cfdc {
    long value0;
    long value1;
    long value2;
    long value3;
    long value4;
    long value5;
};

// 0x710041cfdc
void clear_all_41cfdc(Cleared41cfdc* object) {
    object->value4 = 0;
    object->value5 = 0;
    object->value2 = 0;
    object->value3 = 0;
    object->value0 = 0;
    object->value1 = 0;
}

struct Cleared41d3f4 {
    long value0;
    long value1;
    long value2;
    long value3;
};

// 0x710041d3f4
void clear_all_41d3f4(Cleared41d3f4* object) {
    object->value2 = 0;
    object->value3 = 0;
    object->value0 = 0;
    object->value1 = 0;
}

struct Cleared41d400 {
    long value0;
    long value1;
    long value2;
    long value3;
};

// 0x710041d400
void clear_all_41d400(Cleared41d400* object) {
    object->value2 = 0;
    object->value3 = 0;
    object->value0 = 0;
    object->value1 = 0;
}

struct Cleared41d41c {
    long value0;
    long value1;
    long value2;
    long value3;
};

// 0x710041d41c
void clear_all_41d41c(Cleared41d41c* object) {
    object->value2 = 0;
    object->value3 = 0;
    object->value0 = 0;
    object->value1 = 0;
}

struct Cleared44b4f0 {
    long value0;
    long value1;
    long value2;
    long value3;
};

// 0x710044b4f0
void clear_all_44b4f0(Cleared44b4f0* object) {
    object->value2 = 0;
    object->value3 = 0;
    object->value0 = 0;
    object->value1 = 0;
}

struct Cleared459514 {
    long value0;
    long value1;
    long value2;
    long value3;
};

// 0x7100459514
void clear_all_459514(Cleared459514* object) {
    object->value2 = 0;
    object->value3 = 0;
    object->value0 = 0;
    object->value1 = 0;
}

struct Inner459ae8 {
    unsigned char pad0[0x10];
    int value;  // +10
};
struct Outer459ae8 {
    unsigned char pad0[0x8];
    Inner459ae8* inner;  // +8
};

// 0x7100459ae8
int inner_459ae8(Outer459ae8* object) {
    return object->inner->value;
}

extern int gValue_cf03f8 __attribute__((visibility("hidden"))); // 0x7100cf03f8

// 0x7100459bcc
int global_value_459bcc() {
    return gValue_cf03f8;
}

struct Cleared45d840 {
    long value0;
    long value1;
    long value2;
    long value3;
};

// 0x710045d840
void clear_all_45d840(Cleared45d840* object) {
    object->value2 = 0;
    object->value3 = 0;
    object->value0 = 0;
    object->value1 = 0;
}

struct Cleared46229c {
    long value0;
    long value1;
    long value2;
    long value3;
    long value4;
    long value5;
    long value6;
    long value7;
};

// 0x710046229c
void clear_all_46229c(Cleared46229c* object) {
    object->value6 = 0;
    object->value7 = 0;
    object->value4 = 0;
    object->value5 = 0;
    object->value2 = 0;
    object->value3 = 0;
    object->value0 = 0;
    object->value1 = 0;
}

struct Flag462430 {
    unsigned char value;  // +0
};

// 0x7100462430
void set_value_462430(Flag462430* object) {
    object->value = 0x2;
}

struct Flag46243c {
    unsigned char value;  // +0
};

// 0x710046243c
void set_value_46243c(Flag46243c* object) {
    object->value = 0x1;
}

struct Cleared465f3c {
    long value0;
    long value1;
    long value2;
    long value3;
    long value4;
    long value5;
};

// 0x7100465f3c
void clear_all_465f3c(Cleared465f3c* object) {
    object->value4 = 0;
    object->value5 = 0;
    object->value2 = 0;
    object->value3 = 0;
    object->value0 = 0;
    object->value1 = 0;
}

struct Cleared46659c {
    long value0;
    long value1;
    long value2;
    long value3;
};

// 0x710046659c
void clear_all_46659c(Cleared46659c* object) {
    object->value2 = 0;
    object->value3 = 0;
    object->value0 = 0;
    object->value1 = 0;
}

struct Array49cb18 {
    unsigned char pad0[0x50];
    float values[1];  // +50
};

// 0x710049cb18
float at_49cb18(Array49cb18* object, unsigned int index) {
    return object->values[index];
}

struct Array4a29c4 {
    unsigned char pad0[0x88];
    long values[1];  // +88
};

// 0x71004a29c4
void put_4a29c4(Array4a29c4* object, unsigned int index, long value) {
    object->values[index] = value;
}

struct Array4a397c {
    unsigned char pad0[0x88];
    long values[1];  // +88
};

// 0x71004a397c
long at_4a397c(Array4a397c* object, unsigned int index) {
    return object->values[index];
}

struct Flags4f48dc {
    unsigned long flags;  // +0
};

// 0x71004f48dc
void clear_flags_4f48dc(Flags4f48dc* object) {
    object->flags &= ~0x3ffffful;
}

struct Inner5246dc {
    unsigned char pad0[0x3c];
    int value;  // +3c
};
struct Outer5246dc {
    unsigned char pad0[0x100];
    Inner5246dc* inner;  // +100
};

// 0x71005246dc
int inner_5246dc(Outer5246dc* object) {
    return object->inner->value;
}

struct Inner5256e0 {
    unsigned char pad0[0x48];
    int value;  // +48
};
struct Outer5256e0 {
    unsigned char pad0[0x10];
    Inner5256e0* inner;  // +10
};

// 0x71005256e0
int inner_5256e0(Outer5256e0* object) {
    return object->inner->value;
}

struct Inner559a10 {
    unsigned char pad0[0x652];
    unsigned char value;  // +652
};
struct Outer559a10 {
    unsigned char pad0[0xd8];
    Inner559a10* inner;  // +d8
};

// 0x7100559a10
unsigned char inner_559a10(Outer559a10* object) {
    return object->inner->value;
}

struct Inner559a1c {
    unsigned char pad0[0x2c];
    int value;  // +2c
};
struct Outer559a1c {
    unsigned char pad0[0xd0];
    Inner559a1c* inner;  // +d0
};

// 0x7100559a1c
int inner_559a1c(Outer559a1c* object) {
    return object->inner->value;
}

struct Array58e984 {
    unsigned char pad0[0x30];
    int values[1];  // +30
};

// 0x710058e984
void put_58e984(Array58e984* object, int index, int value) {
    object->values[index] = value;
}

struct Inner5ce178 {
    unsigned char pad0[0x8];
    unsigned short value;  // +8
};
struct Outer5ce178 {
    unsigned char pad0[0x18];
    Inner5ce178* inner;  // +18
};

// 0x71005ce178
unsigned short inner_5ce178(Outer5ce178* object) {
    return object->inner->value;
}

struct Masked5ce188 {
    unsigned char pad0[0x24];
    unsigned char value;  // +24
};

// 0x71005ce188
void set_masked_5ce188(Masked5ce188* object, unsigned int value) {
    object->value = value & 0x1;
}

struct Cleared5d21fc {
    long value0;
    long value1;
};

// 0x71005d21fc
void clear_all_5d21fc(Cleared5d21fc* object) {
    object->value0 = 0;
    object->value1 = 0;
}

struct Flag5f8cf8 {
    unsigned short value;  // +0
};

// 0x71005f8cf8
void set_value_5f8cf8(Flag5f8cf8* object) {
    object->value = 0x7;
}
