// Complete-object destructors (0x710002b94c, 0x71000310c4, 0x710003120c, 0x7100026844, 0x710002b80c): own members from the last one down
// (one an inner group with a base and two members), then the second base: a class with a base and
// members, one of them a polymorphic group destroyed in place (its vtable store comes first).
// Classes are named after the destructor's address. Status: matching/README.md.

class DestructRoot {
public:
    virtual ~DestructRoot();                                                // 0x7100018580

    unsigned char pad8[8];
};

struct PartPlain31374 { ~PartPlain31374(); unsigned char data[0x10]; };     // 0x7100031374
struct PartPlain4640c { ~PartPlain4640c(); unsigned char data[0x28]; };     // 0x710004640c

// Vtable through the GOT slot at 0x7100c21d60.
struct HandleGroup {
    virtual ~HandleGroup() {}
    virtual void key_function();

    PartPlain31374 first;     // +08
    PartPlain31374 second;    // +18
    PartPlain31374 third;     // +28
    PartPlain4640c fourth;    // +38
};

struct PartBasecdf04 { ~PartBasecdf04(); unsigned char data[0xe8]; };       // 0x71000cdf04
struct PartPlaincf58c { ~PartPlaincf58c(); unsigned char data[0x18]; };     // 0x71000cf58c
struct PartPlaincfe84 { ~PartPlaincfe84(); unsigned char data[0x10]; };     // 0x71000cfe84
struct PartPlaind2534 { ~PartPlaind2534(); unsigned char data[0x18]; };     // 0x71000d2534
struct PartPlaind3428 { ~PartPlaind3428(); unsigned char data[0x28]; };     // 0x71000d3428

struct ChildBase : PartBasecdf04 {
    PartPlaincf58c links;     // +e8
    PartPlaincfe84 lock;      // +100
    HandleGroup handles;      // +110
    PartPlaind2534 events;    // +170
    PartPlaind3428 timers;    // +188
};

struct PartPlainb8ab0 { ~PartPlainb8ab0(); unsigned char data[0x270]; };    // 0x71000b8ab0
struct PartPlainbf6cc { ~PartPlainbf6cc(); unsigned char data[0x570]; };    // 0x71000bf6cc
struct PartPlainc0920 { ~PartPlainc0920(); unsigned char data[0x30]; };     // 0x71000c0920

struct ViewGroup : PartPlainb8ab0 {
    PartPlainbf6cc body;      // +270
    PartPlainc0920 footer;    // +7e0
};

struct PartPlainaab24 { ~PartPlainaab24(); unsigned char data[0x18]; };     // 0x71000aab24
struct PartPlainb7774 { ~PartPlainb7774(); unsigned char data[0x18]; };     // 0x71000b7774
struct PartPlainc4e54 { ~PartPlainc4e54(); unsigned char data[0x170]; };    // 0x71000c4e54
struct PartPlainade48 { ~PartPlainade48(); unsigned char data[0x10]; };     // 0x71000ade48
struct PartPlain9c488 { ~PartPlain9c488(); unsigned char data[0x1c0]; };     // 0x71009c488
struct PartPlainc70c0 { ~PartPlainc70c0(); unsigned char data[0xd0]; };     // 0x7100c70c0

// Vtable through the GOT slot at 0x7100c21d00.
class Destructed2b94c : public DestructRoot, public ChildBase {
public:
    ~Destructed2b94c();
    virtual void key_function();

    PartPlain9c488 records;      // +1c0
    PartPlainaab24 flags;      // +380
    PartPlainb7774 queue;      // +398
    ViewGroup view;            // +3b0
    PartPlainc4e54 status;     // +bc0
    PartPlainc70c0 extra;        // +d30
    PartPlainade48 tail;       // +e00
};

// 0x71002b94c
Destructed2b94c::~Destructed2b94c() {}
struct PartPlain9bf4c { ~PartPlain9bf4c(); unsigned char data[0x1c0]; };     // 0x71009bf4c
struct PartPlainc8358 { ~PartPlainc8358(); unsigned char data[0x110]; };     // 0x7100c8358

// Vtable through the GOT slot at 0x7100c21d30.
class Destructed310c4 : public DestructRoot, public ChildBase {
public:
    ~Destructed310c4();
    virtual void key_function();

    PartPlain9bf4c records;      // +1c0
    PartPlainaab24 flags;      // +380
    PartPlainb7774 queue;      // +398
    ViewGroup view;            // +3b0
    PartPlainc4e54 status;     // +bc0
    PartPlainc8358 extra;        // +d30
    PartPlainade48 tail;       // +e40
};

// 0x7100310c4
Destructed310c4::~Destructed310c4() {}

struct Part9b0dc_560 { ~Part9b0dc_560(); unsigned char data[0x560]; };        // 0x710009b0dc
struct Part7b8d4_550 { ~Part7b8d4_550(); unsigned char data[0x550]; };        // 0x710007b8d4
struct Partaadec_a0 { ~Partaadec_a0(); unsigned char data[0xa0]; };          // 0x71000aadec
struct Partb7240_40 { ~Partb7240_40(); unsigned char data[0x40]; };          // 0x71000b7240
struct Partb8ab0_278 { ~Partb8ab0_278(); unsigned char data[0x278]; };        // 0x71000b8ab0
struct Partc0920_28 { ~Partc0920_28(); unsigned char data[0x28]; };          // 0x71000c0920
struct Partc800c_150 { ~Partc800c_150(); unsigned char data[0x150]; };        // 0x71000c800c
struct Partc7dc4_40 { ~Partc7dc4_40(); unsigned char data[0x40]; };          // 0x71000c7dc4
struct Partaf10c_10 { ~Partaf10c_10(); unsigned char data[0x10]; };          // 0x71000af10c
struct Partb8ab0_260 { ~Partb8ab0_260(); unsigned char data[0x260]; };        // 0x71000b8ab0

struct Group3120c_750 : PartPlainb8ab0 {
    PartPlainbf6cc member_270;        // +270
    PartPlainc0920 member_7e0;        // +7e0
};

struct Group26844_7f0 : Partb8ab0_278 {
    Partc0920_28 member_278;          // +278
};

struct Group26844_c00 : Partc800c_150 {
    Partc7dc4_40 member_150;          // +150
};

struct Group2b80c_bc0 : Partc800c_150 {
    Partc7dc4_40 member_150;          // +150
};

// Vtable through the GOT slot at 0x7100c21d38.
class Destructed3120c : public DestructRoot, public ChildBase {
public:
    ~Destructed3120c();
    virtual void key_function();

    Part9b0dc_560 part_1c0;         // +1c0
    PartPlainaab24 part_720;        // +720
    PartPlainb7774 part_738;        // +738
    Group3120c_750 group_750;       // +750
    PartPlainc4e54 part_f60;        // +f60
    PartPlainc8358 part_10d0;       // +10d0
    PartPlainade48 part_11e0;       // +11e0
};

// 0x710003120c
Destructed3120c::~Destructed3120c() {}

// Vtable through the GOT slot at 0x7100c21c80.
class Destructed26844 : public DestructRoot, public ChildBase {
public:
    ~Destructed26844();
    virtual void key_function();

    Part7b8d4_550 part_1c0;         // +1c0
    Partaadec_a0 part_710;          // +710
    Partb7240_40 part_7b0;          // +7b0
    Group26844_7f0 group_7f0;       // +7f0
    PartPlainc4e54 part_a90;        // +a90
    Group26844_c00 group_c00;       // +c00
    Partaf10c_10 part_d90;          // +d90
};

// 0x7100026844
Destructed26844::~Destructed26844() {}

// Vtable through the GOT slot at 0x7100c21ab0.
class Destructed2b80c : public DestructRoot, public ChildBase {
public:
    ~Destructed2b80c();
    virtual void key_function();

    Part7b8d4_550 part_1c0;         // +1c0
    Partaadec_a0 part_710;          // +710
    Partb7240_40 part_7b0;          // +7b0
    Partb8ab0_260 part_7f0;         // +7f0
    PartPlainc4e54 part_a50;        // +a50
    Group2b80c_bc0 group_bc0;       // +bc0
    Partaf10c_10 part_d50;          // +d50
};

// 0x710002b80c
Destructed2b80c::~Destructed2b80c() {}
