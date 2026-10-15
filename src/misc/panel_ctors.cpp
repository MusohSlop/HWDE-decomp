// Constructors of panel classes built on the same base (0x71000b8a6c, 0x71000c3184): construct the
// base, set the vtable and clear the class's own pointers. Names are descriptive placeholders.
// Status: matching/README.md.

class PanelBase {
public:
    PanelBase();                                                            // 0x71000ba7f0
    virtual void base_slot();

    unsigned char data[0x230];
};

// Vtable through the GOT slot at 0x7100c22798.
class PanelB8a6c : public PanelBase {
public:
    PanelB8a6c();
    virtual void key_function();

    void* parts[5];           // +238
};

// 0x71000b8a6c
PanelB8a6c::PanelB8a6c() : parts() {}

// Vtable through the GOT slot at 0x7100c22828.
class PanelC3184 : public PanelBase {
public:
    PanelC3184();
    virtual void key_function();

    void* parts[7];           // +238
};

// 0x71000c3184
PanelC3184::PanelC3184() : parts() {}