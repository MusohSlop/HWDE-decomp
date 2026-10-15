// Constructors that construct a base, set the class's vtable and clear its own fields, found by a
// constructor-shape scan. Classes are named after the constructor's address. Status:
// matching/README.md.

class Base7b5b0_550 {
public:
    Base7b5b0_550();                        // 0x710007b5b0
    virtual void base_slot();

    unsigned char data[0x548];
};

class Base9c438_1b8 {
public:
    Base9c438_1b8();                        // 0x710009c438
    virtual void base_slot();

    unsigned char data[0x1b0];
};

class Baseb71f4_40 {
public:
    Baseb71f4_40();                          // 0x71000b71f4
    virtual void base_slot();

    unsigned char data[0x38];
};

class Base3c7188_28 {
public:
    Base3c7188_28();                        // 0x71003c7188
    virtual void base_slot();

    unsigned char data[0x20];
};

class Base1f69c8_20 {
public:
    Base1f69c8_20();                        // 0x71001f69c8
    virtual void base_slot();

    unsigned char data[0x18];
};

class Base5a9f14_1350 {
public:
    Base5a9f14_1350();                    // 0x71005a9f14
    virtual void base_slot();

    unsigned char data[0x1348];
};

class Base5ce1bc_3c {
public:
    Base5ce1bc_3c();                        // 0x71005ce1bc
    virtual void base_slot();

    unsigned char data[0x34];
};

// Vtable through the GOT slot at 0x7100c22350.
class Built9b0a8 : public Base7b5b0_550 {
public:
    Built9b0a8();
    virtual void key_function();

    unsigned char field_550;       // +550
};

// 0x710009b0a8
Built9b0a8::Built9b0a8() : field_550() {}

// Vtable through the GOT slot at 0x7100c22368.
class Built9bf18 : public Base9c438_1b8 {
public:
    Built9bf18();
    virtual void key_function();

    unsigned char field_1b8;       // +1b8
};

// 0x710009bf18
Built9bf18::Built9bf18() : field_1b8() {}

// Vtable through the GOT slot at 0x7100c22790.
class Builtb8894 : public Baseb71f4_40 {
public:
    Builtb8894();
    virtual void key_function();

    void* field_40;               // +40
};

// 0x71000b8894
Builtb8894::Builtb8894() : field_40() {}

// Vtable through the GOT slot at 0x7100c2ada8.
class Built316a64 : public Base3c7188_28 {
public:
    Built316a64();
    virtual void key_function();

    int field_28;                 // +28
    unsigned char field_2c;       // +2c
    unsigned char pad2d[0x3];
    int field_30;                 // +30
    unsigned char pad34[0x4];
    void* field_38;               // +38
};

// 0x7100316a64
Built316a64::Built316a64() : field_28(), field_2c(), field_30(), field_38() {}

// Vtable through the GOT slot at 0x7100c2aea8.
class Built33840c : public Base1f69c8_20 {
public:
    Built33840c();
    virtual void key_function();

    void* field_20;               // +20
    void* field_28;               // +28
};

// 0x710033840c
Built33840c::Built33840c() : field_20(), field_28() {}

// Vtable through the GOT slot at 0x7100c2d768.
class Built591ff0 : public Base5a9f14_1350 {
public:
    Built591ff0();
    virtual void key_function();

    void* field_1350;               // +1350
    void* field_1358;               // +1358
    void* field_1360;               // +1360
    void* field_1368;               // +1368
};

// 0x7100591ff0
Built591ff0::Built591ff0() : field_1350(), field_1358(), field_1360(), field_1368() {}

// Vtable through the GOT slot at 0x7100c2dc20.
class Built5d026c : public Base5ce1bc_3c {
public:
    Built5d026c();
    virtual void key_function();

    int field_3c;                 // +3c
    void* field_40;               // +40
};

// 0x71005d026c
Built5d026c::Built5d026c() : field_3c(), field_40() {}
