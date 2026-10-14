// Complete-object destructors found by tools/family_scan.py --immediates: each stores its class's
// vtable pointer, destroys its eleven member parts from the last one down, then its three bases.
// They differ in the member layout and some member types; classes are named after the destructor's
// address. Status: matching/README.md.

class DestructBase0 {
public:
    virtual ~DestructBase0();                                               // 0x7100018580

    unsigned char pad8[8];
};
struct DestructBase1 {
    ~DestructBase1();                                                       // 0x71000cdf04

    unsigned char data[0xe8];
};

struct Part_cfe84_30 {
    ~Part_cfe84_30();                                  // 0x71000cfe84

    unsigned char data[0x30];
};
struct Part_d2534_10 {
    ~Part_d2534_10();                                  // 0x71000d2534

    unsigned char data[0x10];
};
struct Part_d3428_30 {
    ~Part_d3428_30();                                  // 0x71000d3428

    unsigned char data[0x30];
};
struct Part_7b8d4_550 {
    ~Part_7b8d4_550();                                // 0x710007b8d4

    unsigned char data[0x550];
};
struct Part_aadec_a0 {
    ~Part_aadec_a0();                                  // 0x71000aadec

    unsigned char data[0xa0];
};
struct Part_b7240_40 {
    ~Part_b7240_40();                                  // 0x71000b7240

    unsigned char data[0x40];
};
struct Part_c31d0_270 {
    ~Part_c31d0_270();                                // 0x71000c31d0

    unsigned char data[0x270];
};
struct Part_c4e54_170 {
    ~Part_c4e54_170();                                // 0x71000c4e54

    unsigned char data[0x170];
};
struct Part_c800c_150 {
    ~Part_c800c_150();                                // 0x71000c800c

    unsigned char data[0x150];
};
struct Part_c7dc4_40 {
    ~Part_c7dc4_40();                                  // 0x71000c7dc4

    unsigned char data[0x40];
};
struct Part_af10c_10 {
    ~Part_af10c_10();                                  // 0x71000af10c

    unsigned char data[0x10];
};
struct Part_9b8bc_160 {
    ~Part_9b8bc_160();                                // 0x710009b8bc

    unsigned char data[0x160];
};
struct Part_aab24_18 {
    ~Part_aab24_18();                                  // 0x71000aab24

    unsigned char data[0x18];
};
struct Part_b7240_48 {
    ~Part_b7240_48();                                  // 0x71000b7240

    unsigned char data[0x48];
};
struct Part_bec1c_270 {
    ~Part_bec1c_270();                                // 0x71000bec1c

    unsigned char data[0x270];
};
struct Part_c615c_a0 {
    ~Part_c615c_a0();                                  // 0x71000c615c

    unsigned char data[0xa0];
};
struct Part_ade48_10 {
    ~Part_ade48_10();                                  // 0x71000ade48

    unsigned char data[0x10];
};
struct Part_9b288_160 {
    ~Part_9b288_160();                                // 0x710009b288

    unsigned char data[0x160];
};
struct Part_ba0b4_40 {
    ~Part_ba0b4_40();                                  // 0x71000ba0b4

    unsigned char data[0x40];
};
struct Part_c47bc_70 {
    ~Part_c47bc_70();                                  // 0x71000c47bc

    unsigned char data[0x70];
};
struct Part_c7d20_100 {
    ~Part_c7d20_100();                                // 0x71000c7d20

    unsigned char data[0x100];
};
struct Part_b8ab0_260 {
    ~Part_b8ab0_260();                                // 0x71000b8ab0

    unsigned char data[0x260];
};
struct Part_be4c8_260 {
    ~Part_be4c8_260();                                // 0x71000be4c8

    unsigned char data[0x260];
};
struct DestructBase2_cf5bc_120 {
    ~DestructBase2_cf5bc_120();      // 0x71000cf5bc

    unsigned char data[0x28];
};
// Vtable through the GOT slot at 0x7100c21ca0.
class Destructed2891c : public DestructBase0, public DestructBase1, public DestructBase2_cf5bc_120 {
public:
    ~Destructed2891c();
    virtual void key_function();

    Part_cfe84_30 part_120;        // +120
    Part_d2534_10 part_150;        // +150
    Part_d3428_30 part_160;        // +160
    Part_7b8d4_550 part_190;        // +190
    Part_aadec_a0 part_6e0;        // +6e0
    Part_b7240_40 part_780;        // +780
    Part_c31d0_270 part_7c0;        // +7c0
    Part_c4e54_170 part_a30;        // +a30
    Part_c800c_150 part_ba0;        // +ba0
    Part_c7dc4_40 part_cf0;        // +cf0
    Part_af10c_10 part_d30;        // +d30
};

// 0x710002891c
Destructed2891c::~Destructed2891c() {}

// Vtable through the GOT slot at 0x7100c21cc8.
class Destructed29d2c : public DestructBase0, public DestructBase1, public DestructBase2_cf5bc_120 {
public:
    ~Destructed29d2c();
    virtual void key_function();

    Part_cfe84_30 part_120;        // +120
    Part_d2534_10 part_150;        // +150
    Part_d3428_30 part_160;        // +160
    Part_9b8bc_160 part_190;        // +190
    Part_aab24_18 part_2f0;        // +2f0
    Part_b7240_48 part_308;        // +308
    Part_bec1c_270 part_350;        // +350
    Part_c615c_a0 part_5c0;        // +5c0
    Part_c800c_150 part_660;        // +660
    Part_c7dc4_40 part_7b0;        // +7b0
    Part_ade48_10 part_7f0;        // +7f0
};

// 0x7100029d2c
Destructed29d2c::~Destructed29d2c() {}

// Vtable through the GOT slot at 0x7100c21cd0.
class Destructed29e48 : public DestructBase0, public DestructBase1, public DestructBase2_cf5bc_120 {
public:
    ~Destructed29e48();
    virtual void key_function();

    Part_cfe84_30 part_120;        // +120
    Part_d2534_10 part_150;        // +150
    Part_d3428_30 part_160;        // +160
    Part_9b288_160 part_190;        // +190
    Part_aadec_a0 part_2f0;        // +2f0
    Part_b7240_40 part_390;        // +390
    Part_ba0b4_40 part_3d0;        // +3d0
    Part_c47bc_70 part_410;        // +410
    Part_c7d20_100 part_480;        // +480
    Part_c7dc4_40 part_580;        // +580
    Part_ade48_10 part_5c0;        // +5c0
};

// 0x7100029e48
Destructed29e48::~Destructed29e48() {}

struct DestructBase2_cf58c_110 {
    ~DestructBase2_cf58c_110();      // 0x71000cf58c

    unsigned char data[0x18];
};
// Vtable through the GOT slot at 0x7100c21ce0.
class Destructed2a26c : public DestructBase0, public DestructBase1, public DestructBase2_cf58c_110 {
public:
    ~Destructed2a26c();
    virtual void key_function();

    Part_cfe84_30 part_110;        // +110
    Part_d2534_10 part_140;        // +140
    Part_d3428_30 part_150;        // +150
    Part_7b8d4_550 part_180;        // +180
    Part_aadec_a0 part_6d0;        // +6d0
    Part_b7240_40 part_770;        // +770
    Part_b8ab0_260 part_7b0;        // +7b0
    Part_c4e54_170 part_a10;        // +a10
    Part_c800c_150 part_b80;        // +b80
    Part_c7dc4_40 part_cd0;        // +cd0
    Part_af10c_10 part_d10;        // +d10
};

// 0x710002a26c
Destructed2a26c::~Destructed2a26c() {}

// Vtable through the GOT slot at 0x7100c21cf0.
class Destructed2b5d4 : public DestructBase0, public DestructBase1, public DestructBase2_cf58c_110 {
public:
    ~Destructed2b5d4();
    virtual void key_function();

    Part_cfe84_30 part_110;        // +110
    Part_d2534_10 part_140;        // +140
    Part_d3428_30 part_150;        // +150
    Part_9b8bc_160 part_180;        // +180
    Part_aab24_18 part_2e0;        // +2e0
    Part_b7240_48 part_2f8;        // +2f8
    Part_be4c8_260 part_340;        // +340
    Part_c615c_a0 part_5a0;        // +5a0
    Part_c800c_150 part_640;        // +640
    Part_c7dc4_40 part_790;        // +790
    Part_ade48_10 part_7d0;        // +7d0
};

// 0x710002b5d4
Destructed2b5d4::~Destructed2b5d4() {}

// Vtable through the GOT slot at 0x7100c21cf8.
class Destructed2b6f0 : public DestructBase0, public DestructBase1, public DestructBase2_cf58c_110 {
public:
    ~Destructed2b6f0();
    virtual void key_function();

    Part_cfe84_30 part_110;        // +110
    Part_d2534_10 part_140;        // +140
    Part_d3428_30 part_150;        // +150
    Part_9b288_160 part_180;        // +180
    Part_aadec_a0 part_2e0;        // +2e0
    Part_b7240_40 part_380;        // +380
    Part_ba0b4_40 part_3c0;        // +3c0
    Part_c47bc_70 part_400;        // +400
    Part_c7d20_100 part_470;        // +470
    Part_c7dc4_40 part_570;        // +570
    Part_ade48_10 part_5b0;        // +5b0
};

// 0x710002b6f0
Destructed2b6f0::~Destructed2b6f0() {}
