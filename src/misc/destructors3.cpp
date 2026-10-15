// Complete-object destructors found by the destructor scan (calls ending in a tail call of the
// root destructor at 0x7100018580): own members from the last one down, inner groups with their
// own bases, then the second base. Classes are named after the destructor's address. Status:
// matching/README.md.

class DefaultHeap {
public:
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

class DestructRoot16 {
public:
    virtual ~DestructRoot16();                                              // 0x7100018580
    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }

    unsigned char pad8[8];
};

class DestructRoot8 {
public:
    virtual ~DestructRoot8();                                               // 0x7100018580
    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }
};

struct Part23818_eff0 { ~Part23818_eff0(); unsigned char data[0xeff0]; };      // 0x7100023818
struct Part7b8d4_550 { ~Part7b8d4_550(); unsigned char data[0x550]; };        // 0x710007b8d4
struct Partaadec_a0 { ~Partaadec_a0(); unsigned char data[0xa0]; };          // 0x71000aadec
struct Partb7240_40 { ~Partb7240_40(); unsigned char data[0x40]; };          // 0x71000b7240
struct Partb8ab0_270 { ~Partb8ab0_270(); unsigned char data[0x270]; };        // 0x71000b8ab0
struct Partbf6cc_570 { ~Partbf6cc_570(); unsigned char data[0x570]; };        // 0x71000bf6cc
struct Partc0920_30 { ~Partc0920_30(); unsigned char data[0x30]; };          // 0x71000c0920
struct Partc4e54_170 { ~Partc4e54_170(); unsigned char data[0x170]; };        // 0x71000c4e54
struct Partc800c_150 { ~Partc800c_150(); unsigned char data[0x150]; };        // 0x71000c800c
struct Partc7dc4_40 { ~Partc7dc4_40(); unsigned char data[0x40]; };          // 0x71000c7dc4
struct Partaf10c_10 { ~Partaf10c_10(); unsigned char data[0x10]; };          // 0x71000af10c
struct Partb789c_70 { ~Partb789c_70(); unsigned char data[0x70]; };          // 0x71000b789c
struct Part9df34_570 { ~Part9df34_570(); unsigned char data[0x570]; };        // 0x710009df34
struct Partc8eb8_a0 { ~Partc8eb8_a0(); unsigned char data[0xa0]; };          // 0x71000c8eb8
struct Part76274_bd0 { ~Part76274_bd0(); unsigned char data[0xbd0]; };        // 0x7100076274
struct Partaab24_18 { ~Partaab24_18(); unsigned char data[0x18]; };          // 0x71000aab24
struct Partb7774_18 { ~Partb7774_18(); unsigned char data[0x18]; };          // 0x71000b7774
struct Partb8ab0_260 { ~Partb8ab0_260(); unsigned char data[0x260]; };        // 0x71000b8ab0
struct Partc47bc_70 { ~Partc47bc_70(); unsigned char data[0x70]; };          // 0x71000c47bc
struct Partc8a00_100 { ~Partc8a00_100(); unsigned char data[0x100]; };        // 0x71000c8a00
struct Partad7f8_10 { ~Partad7f8_10(); unsigned char data[0x10]; };          // 0x71000ad7f8
struct Partad594_48 { ~Partad594_48(); unsigned char data[0x48]; };          // 0x71000ad594
struct Partc8a00_110 { ~Partc8a00_110(); unsigned char data[0x110]; };        // 0x71000c8a00
struct Partcb18c_30 { ~Partcb18c_30(); unsigned char data[0x30]; };          // 0x71000cb18c
struct Part79a40_88 { ~Part79a40_88(); unsigned char data[0x88]; };          // 0x7100079a40
struct Partc44b0_c0 { ~Partc44b0_c0(); unsigned char data[0xc0]; };          // 0x71000c44b0
struct Partc8358_110 { ~Partc8358_110(); unsigned char data[0x110]; };        // 0x71000c8358
struct Partaed40_10 { ~Partaed40_10(); unsigned char data[0x10]; };          // 0x71000aed40
struct Partac2b4_150 { ~Partac2b4_150(); unsigned char data[0x150]; };        // 0x71000ac2b4
struct Partba0b4_40 { ~Partba0b4_40(); unsigned char data[0x40]; };          // 0x71000ba0b4
struct Partc47bc_78 { ~Partc47bc_78(); unsigned char data[0x78]; };          // 0x71000c47bc
struct Partcdf04_e0 { ~Partcdf04_e0(); unsigned char data[0xe0]; };          // 0x71000cdf04
struct Partcf58c_20 { ~Partcf58c_20(); unsigned char data[0x20]; };          // 0x71000cf58c
struct Partb7774_20 { ~Partb7774_20(); unsigned char data[0x20]; };          // 0x71000b7774
struct Partae6b0_10 { ~Partae6b0_10(); unsigned char data[0x10]; };          // 0x71000ae6b0

struct Group266f0_f630 : Partb8ab0_270 {
    Partbf6cc_570 member_270;         // +270
    Partc0920_30 member_7e0;          // +7e0
};

struct Group266f0_ffb0 : Partc800c_150 {
    Partc7dc4_40 member_150;          // +150
};

struct Group26384_f660 : Partb8ab0_270 {
    Partbf6cc_570 member_270;         // +270
    Partc0920_30 member_7e0;          // +7e0
};

struct Group26384_ffe0 : Partc800c_150 {
    Partc7dc4_40 member_150;          // +150
};

struct Group236c4_f660 : Partb8ab0_270 {
    Partbf6cc_570 member_270;         // +270
    Partc0920_30 member_7e0;          // +7e0
};

struct Group236c4_ffe0 : Partc800c_150 {
    Partc7dc4_40 member_150;          // +150
};

struct Group265a4_f680 : Partb8ab0_270 {
    Partbf6cc_570 member_270;         // +270
    Partc0920_30 member_7e0;          // +7e0
};

struct Group265a4_10000 : Partc800c_150 {
    Partc7dc4_40 member_150;          // +150
};

struct SecondBase2bd5c : Partcdf04_e0 {
    Partcf58c_20 member_e0;          // +e0
};

struct Group2bd5c_1d0 : Partb8ab0_270 {
    Partbf6cc_570 member_270;         // +270
    Partc0920_30 member_7e0;          // +7e0
};

struct Group2bd5c_b50 : Partc800c_150 {
    Partc7dc4_40 member_150;          // +150
};

// Vtable through the GOT slot at 0x7100c21c78.
class Destructed266f0 : public DestructRoot16, public Part23818_eff0 {
public:
    ~Destructed266f0();
    virtual void key_function();

    Part7b8d4_550 part_f000;        // +f000
    Partaadec_a0 part_f550;         // +f550
    Partb7240_40 part_f5f0;         // +f5f0
    Group266f0_f630 group_f630;     // +f630
    Partc4e54_170 part_fe40;        // +fe40
    Group266f0_ffb0 group_ffb0;     // +ffb0
    Partaf10c_10 part_10140;        // +10140
};

// 0x71000266f0
Destructed266f0::~Destructed266f0() {}

// Vtable through the GOT slot at 0x7100c21c60.
class Destructed26384 : public DestructRoot16, public Part23818_eff0 {
public:
    ~Destructed26384();
    virtual void key_function();

    Part7b8d4_550 part_f000;        // +f000
    Partaadec_a0 part_f550;         // +f550
    Partb789c_70 part_f5f0;         // +f5f0
    Group26384_f660 group_f660;     // +f660
    Partc4e54_170 part_fe70;        // +fe70
    Group26384_ffe0 group_ffe0;     // +ffe0
    Partaf10c_10 part_10170;        // +10170
};

// 0x7100026384
Destructed26384::~Destructed26384() {}

// Vtable through the GOT slot at 0x7100c21c28.
class Destructed236c4 : public DestructRoot16, public Part23818_eff0 {
public:
    ~Destructed236c4();
    virtual void key_function();

    Part7b8d4_550 part_f000;        // +f000
    Partaadec_a0 part_f550;         // +f550
    Partb789c_70 part_f5f0;         // +f5f0
    Group236c4_f660 group_f660;     // +f660
    Partc4e54_170 part_fe70;        // +fe70
    Group236c4_ffe0 group_ffe0;     // +ffe0
    Partaf10c_10 part_10170;        // +10170
};

// 0x71000236c4
Destructed236c4::~Destructed236c4() {}

// Vtable through the GOT slot at 0x7100c21c70.
class Destructed265a4 : public DestructRoot16, public Part23818_eff0 {
public:
    ~Destructed265a4();
    virtual void key_function();

    Part9df34_570 part_f000;        // +f000
    Partaadec_a0 part_f570;         // +f570
    Partb789c_70 part_f610;         // +f610
    Group265a4_f680 group_f680;     // +f680
    Partc4e54_170 part_fe90;        // +fe90
    Group265a4_10000 group_10000;   // +10000
    Partaf10c_10 part_10190;        // +10190
};

// 0x71000265a4
Destructed265a4::~Destructed265a4() {}

// Vtable through the GOT slot at 0x7100c21bd0.
class Destructed2ffe0 : public DestructRoot16, public Partc8eb8_a0 {
public:
    ~Destructed2ffe0();
    virtual void key_function();

    Part76274_bd0 part_b0;          // +b0
    Partaab24_18 part_c80;          // +c80
    Partb7774_18 part_c98;          // +c98
    Partb8ab0_260 part_cb0;         // +cb0
    Partc47bc_70 part_f10;          // +f10
    Partc8a00_100 part_f80;         // +f80
    Partad7f8_10 part_1080;         // +1080
};

// 0x710002ffe0
Destructed2ffe0::~Destructed2ffe0() {}

// Vtable through the GOT slot at 0x7100c21bb0.
class Destructed2f628 : public DestructRoot16, public Partc8eb8_a0 {
public:
    ~Destructed2f628();
    virtual void key_function();

    Part76274_bd0 part_b0;          // +b0
    Partad594_48 part_c80;          // +c80
    Partb7774_18 part_cc8;          // +cc8
    Partb8ab0_260 part_ce0;         // +ce0
    Partc47bc_70 part_f40;          // +f40
    Partc8a00_110 part_fb0;         // +fb0
    Partad7f8_10 part_10c0;         // +10c0
};

// 0x710002f628
Destructed2f628::~Destructed2f628() {}

// Vtable through the GOT slot at 0x7100c21bf0.
class Destructed30690 : public DestructRoot8, public Partcb18c_30 {
public:
    ~Destructed30690();
    virtual void key_function();

    Part79a40_88 part_38;           // +38
    Partaab24_18 part_c0;           // +c0
    Partb7774_18 part_d8;           // +d8
    Partb8ab0_260 part_f0;          // +f0
    Partc44b0_c0 part_350;          // +350
    Partc8358_110 part_410;         // +410
    Partaed40_10 part_520;          // +520
};

// 0x7100030690
Destructed30690::~Destructed30690() {}

// Vtable through the GOT slot at 0x7100c21be8.
class Destructed30554 : public DestructRoot8, public Partcb18c_30 {
public:
    ~Destructed30554();
    virtual void key_function();

    Part79a40_88 part_38;           // +38
    Partaab24_18 part_c0;           // +c0
    Partb7774_18 part_d8;           // +d8
    Partb8ab0_260 part_f0;          // +f0
    Partc47bc_70 part_350;          // +350
    Partc8358_110 part_3c0;         // +3c0
    Partaed40_10 part_4d0;          // +4d0
};

// 0x7100030554
Destructed30554::~Destructed30554() {}

// Vtable through the GOT slot at 0x7100c21be0.
class Destructed30418 : public DestructRoot16, public Partc8eb8_a0 {
public:
    ~Destructed30418();
    virtual void key_function();

    Part76274_bd0 part_b0;          // +b0
    Partac2b4_150 part_c80;         // +c80
    Partb7774_18 part_dd0;          // +dd0
    Partba0b4_40 part_de8;          // +de8
    Partc47bc_78 part_e28;          // +e28
    Partc8a00_100 part_ea0;         // +ea0
    Partad7f8_10 part_fa0;          // +fa0
};

// 0x7100030418
Destructed30418::~Destructed30418() {}

// Vtable through the GOT slot at 0x7100c21bc0.
class Destructed2fd40 : public DestructRoot16, public Partc8eb8_a0 {
public:
    ~Destructed2fd40();
    virtual void key_function();

    Part76274_bd0 part_b0;          // +b0
    Partaab24_18 part_c80;          // +c80
    Partb7774_18 part_c98;          // +c98
    Partba0b4_40 part_cb0;          // +cb0
    Partc47bc_70 part_cf0;          // +cf0
    Partc8a00_100 part_d60;         // +d60
    Partad7f8_10 part_e60;          // +e60
};

// 0x710002fd40
Destructed2fd40::~Destructed2fd40() {}

// Vtable through the GOT slot at 0x7100c21b98.
class Destructed2f0e8 : public DestructRoot16, public Partc8eb8_a0 {
public:
    ~Destructed2f0e8();
    virtual void key_function();

    Part76274_bd0 part_b0;          // +b0
    Partad594_48 part_c80;          // +c80
    Partb7774_18 part_cc8;          // +cc8
    Partba0b4_40 part_ce0;          // +ce0
    Partc47bc_70 part_d20;          // +d20
    Partc8a00_110 part_d90;         // +d90
    Partad7f8_10 part_ea0;          // +ea0
};

// 0x710002f0e8
Destructed2f0e8::~Destructed2f0e8() {}

// Vtable through the GOT slot at 0x7100c21d08.
class Destructed2bd5c : public DestructRoot16, public SecondBase2bd5c {
public:
    ~Destructed2bd5c();
    virtual void key_function();

    Part79a40_88 part_110;          // +110
    Partaab24_18 part_198;          // +198
    Partb7774_20 part_1b0;          // +1b0
    Group2bd5c_1d0 group_1d0;       // +1d0
    Partc4e54_170 part_9e0;         // +9e0
    Group2bd5c_b50 group_b50;       // +b50
    Partae6b0_10 part_ce0;          // +ce0
};

// 0x710002bd5c
Destructed2bd5c::~Destructed2bd5c() {}
