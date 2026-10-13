// Derived-class constructors found by tools/family_scan.py: each calls its base constructor
// and stores its own vtable pointer. They are byte-identical apart from those two references
// (the same shape as AdvModeTask::AdvModeTask, 0x710026e434) and live in their classes'
// source files across the image, so they are grouped here until those files are linked.
// Classes are named after the constructor address, bases after the base constructor.
// Status: matching/README.md.

class Base_7a0c8 {
public:
    Base_7a0c8();                                                   // 0x710007a0c8
    virtual ~Base_7a0c8();
};

// 0x710007a4b8; vtable through the GOT slot at 0x7100c221e8
class Derived_7a4b8 : public Base_7a0c8 {
public:
    Derived_7a4b8();
    ~Derived_7a4b8() override;
};

Derived_7a4b8::Derived_7a4b8() {}

class Base_99ad0 {
public:
    Base_99ad0();                                                   // 0x7100099ad0
    virtual ~Base_99ad0();
};

// 0x710009b258; vtable through the GOT slot at 0x7100c22358
class Derived_9b258 : public Base_99ad0 {
public:
    Derived_9b258();
    ~Derived_9b258() override;
};

Derived_9b258::Derived_9b258() {}

// 0x710009b88c; vtable through the GOT slot at 0x7100c22360
class Derived_9b88c : public Base_99ad0 {
public:
    Derived_9b88c();
    ~Derived_9b88c() override;
};

Derived_9b88c::Derived_9b88c() {}

class Base_ade30 {
public:
    Base_ade30();                                                   // 0x71000ade30
    virtual ~Base_ade30();
};

// 0x71000aed10; vtable through the GOT slot at 0x7100c224e0
class Derived_aed10 : public Base_ade30 {
public:
    Derived_aed10();
    ~Derived_aed10() override;
};

Derived_aed10::Derived_aed10() {}

// 0x71000b6080; vtable through the GOT slot at 0x7100c22740
class Derived_b6080 : public Base_ade30 {
public:
    Derived_b6080();
    ~Derived_b6080() override;
};

Derived_b6080::Derived_b6080() {}

class Base_b8a6c {
public:
    Base_b8a6c();                                                   // 0x71000b8a6c
    virtual ~Base_b8a6c();
};

// 0x71000be498; vtable through the GOT slot at 0x7100c227d0
class Derived_be498 : public Base_b8a6c {
public:
    Derived_be498();
    ~Derived_be498() override;
};

Derived_be498::Derived_be498() {}

class Base_c3184 {
public:
    Base_c3184();                                                   // 0x71000c3184
    virtual ~Base_c3184();
};

// 0x71000bebec; vtable through the GOT slot at 0x7100c227e0
class Derived_bebec : public Base_c3184 {
public:
    Derived_bebec();
    ~Derived_bebec() override;
};

Derived_bebec::Derived_bebec() {}

class Base_39cc78 {
public:
    Base_39cc78();                                                  // 0x710039cc78
    virtual ~Base_39cc78();
};

// 0x71002fb3b0; vtable through the GOT slot at 0x7100c2ac28
class Derived_2fb3b0 : public Base_39cc78 {
public:
    Derived_2fb3b0();
    ~Derived_2fb3b0() override;
};

Derived_2fb3b0::Derived_2fb3b0() {}

// 0x710039d240; vtable through the GOT slot at 0x7100c2b298
class Derived_39d240 : public Base_39cc78 {
public:
    Derived_39d240();
    ~Derived_39d240() override;
};

Derived_39d240::Derived_39d240() {}

// 0x71003af9fc; vtable through the GOT slot at 0x7100c2b3c8
class Derived_3af9fc : public Base_39cc78 {
public:
    Derived_3af9fc();
    ~Derived_3af9fc() override;
};

Derived_3af9fc::Derived_3af9fc() {}

// 0x71003c6fa4; vtable through the GOT slot at 0x7100c2b488
class Derived_3c6fa4 : public Base_39cc78 {
public:
    Derived_3c6fa4();
    ~Derived_3c6fa4() override;
};

Derived_3c6fa4::Derived_3c6fa4() {}

class Base_41be40 {
public:
    Base_41be40();                                                  // 0x710041be40
    virtual ~Base_41be40();
};

// 0x71004194c0; vtable through the GOT slot at 0x7100c2b7f0
class Derived_4194c0 : public Base_41be40 {
public:
    Derived_4194c0();
    ~Derived_4194c0() override;
};

Derived_4194c0::Derived_4194c0() {}

// 0x7100419850; vtable through the GOT slot at 0x7100c2b7f8
class Derived_419850 : public Base_41be40 {
public:
    Derived_419850();
    ~Derived_419850() override;
};

Derived_419850::Derived_419850() {}

// 0x7100419a7c; vtable through the GOT slot at 0x7100c2b800
class Derived_419a7c : public Base_41be40 {
public:
    Derived_419a7c();
    ~Derived_419a7c() override;
};

Derived_419a7c::Derived_419a7c() {}

// 0x7100419f40; vtable through the GOT slot at 0x7100c2b808
class Derived_419f40 : public Base_41be40 {
public:
    Derived_419f40();
    ~Derived_419f40() override;
};

Derived_419f40::Derived_419f40() {}

// 0x7100427f34; vtable through the GOT slot at 0x7100c2b960
class Derived_427f34 : public Base_41be40 {
public:
    Derived_427f34();
    ~Derived_427f34() override;
};

Derived_427f34::Derived_427f34() {}

// 0x7100428bdc; vtable through the GOT slot at 0x7100c2b968
class Derived_428bdc : public Base_41be40 {
public:
    Derived_428bdc();
    ~Derived_428bdc() override;
};

Derived_428bdc::Derived_428bdc() {}

// 0x7100428ed8; vtable through the GOT slot at 0x7100c2b970
class Derived_428ed8 : public Base_41be40 {
public:
    Derived_428ed8();
    ~Derived_428ed8() override;
};

Derived_428ed8::Derived_428ed8() {}

// 0x7100429120; vtable through the GOT slot at 0x7100c2b978
class Derived_429120 : public Base_41be40 {
public:
    Derived_429120();
    ~Derived_429120() override;
};

Derived_429120::Derived_429120() {}

// 0x710042964c; vtable through the GOT slot at 0x7100c2b980
class Derived_42964c : public Base_41be40 {
public:
    Derived_42964c();
    ~Derived_42964c() override;
};

Derived_42964c::Derived_42964c() {}

// 0x710043516c; vtable through the GOT slot at 0x7100c2b9f8
class Derived_43516c : public Base_41be40 {
public:
    Derived_43516c();
    ~Derived_43516c() override;
};

Derived_43516c::Derived_43516c() {}

// 0x710043581c; vtable through the GOT slot at 0x7100c2ba00
class Derived_43581c : public Base_41be40 {
public:
    Derived_43581c();
    ~Derived_43581c() override;
};

Derived_43581c::Derived_43581c() {}

// 0x7100435ca8; vtable through the GOT slot at 0x7100c2ba08
class Derived_435ca8 : public Base_41be40 {
public:
    Derived_435ca8();
    ~Derived_435ca8() override;
};

Derived_435ca8::Derived_435ca8() {}

// 0x71004367fc; vtable through the GOT slot at 0x7100c2ba10
class Derived_4367fc : public Base_41be40 {
public:
    Derived_4367fc();
    ~Derived_4367fc() override;
};

Derived_4367fc::Derived_4367fc() {}

// 0x7100437ed4; vtable through the GOT slot at 0x7100c2ba20
class Derived_437ed4 : public Base_41be40 {
public:
    Derived_437ed4();
    ~Derived_437ed4() override;
};

Derived_437ed4::Derived_437ed4() {}

class Base_57cda8 {
public:
    Base_57cda8();                                                  // 0x710057cda8
    virtual ~Base_57cda8();
};

// 0x71004d28f0; vtable through the GOT slot at 0x7100c2ce58
class Derived_4d28f0 : public Base_57cda8 {
public:
    Derived_4d28f0();
    ~Derived_4d28f0() override;
};

Derived_4d28f0::Derived_4d28f0() {}

class Base_5325e4 {
public:
    Base_5325e4();                                                  // 0x71005325e4
    virtual ~Base_5325e4();
};

// 0x71005279dc; vtable through the GOT slot at 0x7100c2d1e8
class Derived_5279dc : public Base_5325e4 {
public:
    Derived_5279dc();
    ~Derived_5279dc() override;
};

Derived_5279dc::Derived_5279dc() {}

// 0x7100527a38; vtable through the GOT slot at 0x7100c2d1f0
class Derived_527a38 : public Base_5325e4 {
public:
    Derived_527a38();
    ~Derived_527a38() override;
};

Derived_527a38::Derived_527a38() {}

class Base_553450 {
public:
    Base_553450();                                                  // 0x7100553450
    virtual ~Base_553450();
};

// 0x7100557dc4; vtable through the GOT slot at 0x7100c2d3c0
class Derived_557dc4 : public Base_553450 {
public:
    Derived_557dc4();
    ~Derived_557dc4() override;
};

Derived_557dc4::Derived_557dc4() {}

class Base_5d9e04 {
public:
    Base_5d9e04();                                                  // 0x71005d9e04
    virtual ~Base_5d9e04();
};

// 0x71005e3b10; vtable through the GOT slot at 0x7100c2dd98
class Derived_5e3b10 : public Base_5d9e04 {
public:
    Derived_5e3b10();
    ~Derived_5e3b10() override;
};

Derived_5e3b10::Derived_5e3b10() {}

class Base_5fce1c {
public:
    Base_5fce1c();                                                  // 0x71005fce1c
    virtual ~Base_5fce1c();
};

// 0x71005fcaa4; vtable through the GOT slot at 0x7100c2de28
class Derived_5fcaa4 : public Base_5fce1c {
public:
    Derived_5fcaa4();
    ~Derived_5fcaa4() override;
};

Derived_5fcaa4::Derived_5fcaa4() {}
