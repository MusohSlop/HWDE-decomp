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

// The layout handle as destructors inline it: the vtable store, then release() through the vtable with the heap
// of the owner at GOT 0x7100c21db0 (its vtable is in another unit, GOT 0x7100c22f00).
struct HandleHeapOwner {
    unsigned char pad0[0x2af8];
    unsigned char* heap;            // +2af8
};
extern HandleHeapOwner* gHandleHeapOwner;

inline void* handle_root_heap() { return gHandleHeapOwner ? gHandleHeapOwner->heap + 0x10 : nullptr; }

struct DtorHandleState {
    long id;
    short a;
    short b;
};

class DtorHandle : public DtorHandleState {
public:
    virtual ~DtorHandle() { release(handle_root_heap()); }
    virtual void v10();
    virtual void release(void* root);
};

class Base316aa4 {
public:
    virtual ~Base316aa4();          // 0x7100316aa4
};

struct Part37f568 { ~Part37f568(); unsigned char data[0x10]; };              // 0x710037f568

struct HandleRun31a47c {
    unsigned char pad0[0x24b8];
    DtorHandle hs[5];               // +24b8
};

// 0x710031a47c (D2): 32 runs of five handles destroyed in a loop, between a member and the base destructor.
class Class31a47c : public Base316aa4 {
public:
    ~Class31a47c();

    unsigned char pad8[0x7e7b8 - 8];
    HandleRun31a47c runs[32];       // +7e7b8
    unsigned char padc8db8[0x8];
    Part37f568 part;                // +c8dc0
};

Class31a47c::~Class31a47c() {}

struct Part5d27b4 { ~Part5d27b4(); unsigned char data[0x10]; };              // 0x71005d27b4
struct Part35ca18 { ~Part35ca18(); unsigned char data[0x10]; };              // 0x710035ca18
struct Part379b04 { ~Part379b04(); unsigned char data[0x10]; };              // 0x7100379b04

struct Slot70_3ba38c { unsigned char pad0[0x58]; DtorHandle h; };            // 0x70
struct Slot5008_3ba38c { DtorHandle h; unsigned char pad18[0x5008 - 0x18]; };

class Basec719c {
public:
    virtual ~Basec719c();           // 0x71003c719c
};

// 0x71003ba38c (D2): single handles and members, and two arrays of handle slots destroyed in loops.
class Class3ba38c : public Basec719c {
public:
    ~Class3ba38c();

    unsigned char pad8[0x560 - 8];
    Part5d27b4 m560;
    unsigned char pad570[0x6a0 - 0x570];
    DtorHandle h6a0;
    unsigned char pad6b8[0x700 - 0x6b8];
    DtorHandle h700;
    unsigned char pad718[0x760 - 0x718];
    DtorHandle h760;
    unsigned char pad778[0x830 - 0x778];
    Part5d27b4 m830;
    unsigned char pad840[0xc70 - 0x840];
    DtorHandle hc70, hc88, hca0, hcb8;
    unsigned char padcd0[0x11678 - 0xcd0];
    Slot70_3ba38c slots70[32];      // +11678
    unsigned char pad12478[0x124b8 - 0x12478];
    Slot5008_3ba38c slots5008[32];  // +124b8
    unsigned char padb25b8[0xb2798 - 0xb25b8];
    Part35ca18 mb2798;
    unsigned char padb27a8[0xb6be0 - 0xb27a8];
    Part379b04 mb6be0;
    unsigned char padb6bf0[0xb6cc0 - 0xb6bf0];
    DtorHandle hb6cc0;
};

Class3ba38c::~Class3ba38c() {}