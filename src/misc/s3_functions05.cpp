// Destructors written by hand (third session). Classes are named after the destructor's address, as in
// functions.csv. The empty destructor at 0x710004640c and the base destructor at 0x71000ade48 are each shared by
// many classes (identical code folding), so the member types here only give the sizes. Status: matching/README.md.

class DefaultHeap {
public:
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

class SlotBase_ade48 {
public:
    virtual ~SlotBase_ade48();                                              // 0x71000ade48
    unsigned char data8[0x84];
};

struct SlotHead_4640c {
    ~SlotHead_4640c();                                                      // 0x710004640c
    unsigned char data[0x6c];
};

struct Slot_4640c {
    ~Slot_4640c();                                                          // 0x710004640c
    unsigned char data[0x70];
};

// A count and the first slot. The slot sits two steps from the bank (+f8, then +4), so it is the address the
// vtable store's post-increment reaches (+fc); the head (+8c) and the later slots, one step from the bank, are
// addressed where they are destroyed.
struct SlotCount_4640c {
    int count;
    Slot_4640c first;
};

// 0x71000b63f4 (D2) and 0x71000b6478 (D0)
class SlotBankB63f4 : public SlotBase_ade48 {
public:
    ~SlotBankB63f4();
    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }

    SlotHead_4640c head;      // +8c
    SlotCount_4640c counted;  // +f8
    Slot_4640c s16c, s1dc, s24c, s2bc, s32c, s39c, s40c, s47c;
};

SlotBankB63f4::~SlotBankB63f4() {}

// 0x71000af10c (D2)
class SlotBankAf10c : public SlotBase_ade48 {
public:
    ~SlotBankAf10c();
    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }

    SlotHead_4640c head;      // +8c
    SlotCount_4640c counted;  // +f8
    Slot_4640c s16c, s1dc, s24c, s2bc, s32c, s39c, s40c, s47c, s4ec, s55c, s5cc, s63c, s6ac, s71c, s78c, s7fc,
        s86c, s8dc;
};

SlotBankAf10c::~SlotBankAf10c() {}

struct Part5f9428 { ~Part5f9428(); unsigned char data[0x10]; };              // 0x71005f9428
struct Part461204 { ~Part461204(); unsigned char data[0x48]; };              // 0x7100461204
struct Part462520 { ~Part462520(); unsigned char data[0x120]; };             // 0x7100462520
struct Part4665a8 { ~Part4665a8(); unsigned char data[0x20]; };              // 0x71004665a8

// 0x71005fbbb0 (D2). The six parts at +90 are one array: its base stays in a register for the last (tail)
// call, and the vtable store post-increments to its fourth element (+f0).
class Class5fbbb0 {
public:
    virtual ~Class5fbbb0();

    unsigned char data8[0x88];
    Part4665a8 parts[6];        // +90
    Part462520 p150;            // +150
    Part461204 p270, p2b8, p300, p348;
    Part5f9428 p390;
};

Class5fbbb0::~Class5fbbb0() {}
