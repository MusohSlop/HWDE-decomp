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

struct Part379f30 { ~Part379f30(); unsigned char data[0x10]; };              // 0x7100379f30

struct HandlePair2e2dcc { unsigned char pad0[0x8]; DtorHandle hs[2]; unsigned char pad38[0xb8]; };   // 0xf0

// 0x71002e2dcc (D2): no vtable of its own; two arrays of 36 handle pairs destroyed in loops, two more handles and
// three members (written by tools/s3/dtor2class.py).
class Class2e2dcc {
public:
    ~Class2e2dcc();

    unsigned char pad0[0x90];
    HandlePair2e2dcc pairs90[36];   // +90
    HandlePair2e2dcc pairs2250[36]; // +2250
    DtorHandle h4410;               // +4410
    DtorHandle h4428;               // +4428
    unsigned char pad4440[0xc1f0 - 0x4440];
    Part5d27b4 mc1f0;               // +c1f0
    unsigned char padc200[0xc300 - 0xc200];
    Part5d27b4 mc300;               // +c300
    unsigned char padc310[0x17768 - 0xc310];
    Part379f30 m17768;              // +17768
};

Class2e2dcc::~Class2e2dcc() {}

// Objects of the layout root, released through its heap (GOT 0x7100c22a00).
struct ObjLink {
    unsigned char pad0[0x18];
    void* owner;                    // +18
};

class LayoutObj {
public:
    virtual void v0();
    virtual void destroy();         // +8
    unsigned char pad8[0x10];
    ObjLink* link;                  // +18
};

struct ObjHeap {
    unsigned char pad0[0x68];
    unsigned char list68[0x70];     // +68
    unsigned char listd8[0x6e0];    // +d8
    unsigned char lock7b8[0x8];     // +7b8
};
extern ObjHeap* gObjHeap;           // GOT 0x7100c22a00

void heap_enter(ObjHeap* heap, void* lock, int id);       // 0x71001e2218
void obj_detach(LayoutObj* obj, void* root);              // 0x71005d4408
void heap_return(void* list, LayoutObj* obj);             // 0x71005c3774
void link_drop(void* owner, ObjLink* link);               // 0x71005da1b0

inline void release_linked(LayoutObj*& p) {
    if (p) {
        ObjLink* l = p->link;
        if (l->owner)
            link_drop(l->owner, l);
        if (p) {
            ObjHeap* heap = gObjHeap;
            void* root = gHandleHeapOwner->heap + 0x10;
            heap_enter(heap, heap->lock7b8, 0x4213);
            obj_detach(p, root);
            p->destroy();
            heap_return(heap->listd8, p);
            p = nullptr;
        }
    }
}

inline void release_obj(LayoutObj*& p) {
    ObjHeap* heap = gObjHeap;
    if (p) {
        void* root = gHandleHeapOwner->heap + 0x10;
        heap_enter(heap, heap->lock7b8, 0x4213);
        obj_detach(p, root);
        p->destroy();
        heap_return(heap->listd8, p);
        p = nullptr;
    }
}

struct Elem2b349c {
    ~Elem2b349c();                  // 0x71002b349c
    unsigned char pad0[0x10];
    LayoutObj* obj;                 // +10
    unsigned char pad18[0x988 - 0x18];
};

struct Frame1f8720 {
    ~Frame1f8720();                 // 0x71001f8720
    void stop();                    // 0x71001f8724
    unsigned char data[0xa0];
};

struct Sub2b25b0 {
    void clear();                   // 0x71002b25b0
    unsigned char data[0x20];
};

// 0x71002b4df0 (D2): a body that releases the objects of its six elements and two of its own (the inline release helpers
// above), then its members: the elements, two handles, four frames and the handle at +a0 (released as a tail call).
class Class2b4df0 {
public:
    virtual ~Class2b4df0();

    unsigned char pad8[0x10];
    LayoutObj* f18;                 // +18
    LayoutObj* f20;                 // +20
    unsigned char pad28[0xa0 - 0x28];
    DtorHandle ha0;                 // +a0
    unsigned char padb8[0x33c8 - 0xb8];
    Sub2b25b0 s33c8;                // +33c8
    Frame1f8720 frames[4];          // +33e8
    unsigned char pad3668[0x3918 - 0x3668];
    DtorHandle h3918;               // +3918
    DtorHandle h3930;               // +3930
    Elem2b349c elems[6];            // +3948
};

Class2b4df0::~Class2b4df0() {
    for (int i = 0; i < 6; i++)
        release_linked(elems[i].obj);
    s33c8.clear();
    release_obj(f18);
    release_obj(f20);
}

inline void release_list68(LayoutObj*& p) {
    ObjHeap* heap = gObjHeap;
    if (p) {
        void* root = gHandleHeapOwner->heap + 0x10;
        obj_detach(p, root);
        p->destroy();
        heap_return(heap->list68, p);
        p = nullptr;
    }
}

inline void release_id(LayoutObj*& p, int id) {
    ObjHeap* heap = gObjHeap;
    if (p) {
        void* root = gHandleHeapOwner->heap + 0x10;
        heap_enter(heap, heap->lock7b8, id);
        obj_detach(p, root);
        p->destroy();
        heap_return(heap->listd8, p);
        p = nullptr;
    }
}

struct Sub37f568 {
    ~Sub37f568();                   // 0x710037f568
    void stop();                    // 0x710037cd6c
    unsigned char data[0x40];
};

struct Elem2bd8cc { ~Elem2bd8cc(); unsigned char data[0xe0]; };              // 0x71002bd8cc
struct Elem2bfda4 { ~Elem2bfda4(); unsigned char data[0x188]; };             // 0x71002bfda4

// 0x71002beea8 (D2): its two frames stopped and two objects unlinked in the body, a member stopped, three objects
// released, then the members: the frames (two members, so each address is kept for both calls), the member, an
// array of 32 elements and two handles.
class Class2beea8 {
public:
    virtual ~Class2beea8();

    unsigned char pad8[0x10];
    LayoutObj* f18;                 // +18
    LayoutObj* f20;                 // +20
    LayoutObj* f28;                 // +28
    unsigned char pad30[0xf8 - 0x30];
    void* ownerf8;                  // +f8
    void* owner100;                 // +100
    unsigned char pad108[0x3d28 - 0x108];
    DtorHandle h3d28;               // +3d28
    DtorHandle h3d40;               // +3d40
    Elem2bd8cc elems[32];           // +3d58
    Sub37f568 s5958;                // +5958
    Frame1f8720 fa;                 // +5998
    Frame1f8720 fb;                 // +5a38
};

Class2beea8::~Class2beea8() {
    fa.stop();
    fb.stop();
    if (f20)
        link_drop(ownerf8, f20->link);
    if (f28)
        link_drop(owner100, f28->link);
    s5958.stop();
    release_id(f18, 0x4217);
    release_list68(f20);
    release_list68(f28);
}

// 0x71002c18c0 (D2): the same with other offsets, 32 larger elements and three handles.
class Class2c18c0 {
public:
    virtual ~Class2c18c0();

    unsigned char pad8[0x10];
    LayoutObj* f18;                 // +18
    LayoutObj* f20;                 // +20
    LayoutObj* f28;                 // +28
    unsigned char pad30[0x100 - 0x30];
    void* owner100;                 // +100
    void* owner108;                 // +108
    unsigned char pad110[0x3d30 - 0x110];
    DtorHandle h3d30;               // +3d30
    DtorHandle h3d48;               // +3d48
    DtorHandle h3d60;               // +3d60
    Elem2bfda4 elems[32];           // +3d78
    Sub37f568 s6e78;                // +6e78
    Frame1f8720 fa;                 // +6eb8
    Frame1f8720 fb;                 // +6f58
};

Class2c18c0::~Class2c18c0() {
    fa.stop();
    fb.stop();
    if (f20)
        link_drop(owner100, f20->link);
    if (f28)
        link_drop(owner108, f28->link);
    s6e78.stop();
    release_id(f18, 0x4217);
    release_list68(f20);
    release_list68(f28);
}

inline void release_in(LayoutObj*& p, int id) {
    if (p) {
        ObjHeap* heap = gObjHeap;
        void* root = gHandleHeapOwner->heap + 0x10;
        heap_enter(heap, heap->lock7b8, id);
        obj_detach(p, root);
        p->destroy();
        heap_return(heap->listd8, p);
        p = nullptr;
    }
}

struct Elem2b81b4 {
    ~Elem2b81b4();                  // 0x71002b81b4
    unsigned char pad0[0x10];
    LayoutObj* obj;                 // +10
    unsigned char pad18[0x988 - 0x18];
};

struct Sub2b6e94 {
    void clear();                   // 0x71002b6e94
    unsigned char data[0x20];
};

// 0x71002b9f9c (D2): the shape of 2b4df0 with eleven elements, three released objects (the heap read inside each
// check) and four handles.
class Class2b9f9c {
public:
    virtual ~Class2b9f9c();

    unsigned char pad8[0x10];
    LayoutObj* f18;                 // +18
    LayoutObj* f20;                 // +20
    LayoutObj* f28;                 // +28
    unsigned char pad30[0x33e0 - 0x30];
    Sub2b6e94 s33e0;                // +33e0
    Frame1f8720 frames[4];          // +3400
    unsigned char pad3680[0x3c00 - 0x3680];
    DtorHandle h3c00;               // +3c00
    DtorHandle h3c18;               // +3c18
    DtorHandle h3c30;               // +3c30
    DtorHandle h3c48;               // +3c48
    unsigned char pad3c60[0x8];
    Elem2b81b4 elems[11];           // +3c68
};

Class2b9f9c::~Class2b9f9c() {
    for (int i = 0; i < 11; i++)
        release_linked(elems[i].obj);
    s33e0.clear();
    release_in(f18, 0x4213);
    release_in(f20, 0x4213);
    release_in(f28, 0x421c);
}

inline void release_linked68(LayoutObj*& p) {
    if (p) {
        ObjLink* l = p->link;
        if (l->owner)
            link_drop(l->owner, l);
        if (p) {
            ObjHeap* heap = gObjHeap;
            void* root = gHandleHeapOwner->heap + 0x10;
            obj_detach(p, root);
            p->destroy();
            heap_return(heap->list68, p);
            p = nullptr;
        }
        p = nullptr;
    }
}

struct Elem2c6a58 {
    LayoutObj* obj;                 // +0
    unsigned char pad8[0x10];
    DtorHandle h;                   // +18
};

// 0x71002c6a58 (D2): releases the objects of its 20 elements and two of its own, then destroys the elements
// (each one's handle, in a loop).
class Class2c6a58 {
public:
    virtual ~Class2c6a58();

    unsigned char pad8[0x10];
    LayoutObj* f18;                 // +18
    LayoutObj* f20;                 // +20
    unsigned char pad28[0x70 - 0x28];
    Elem2c6a58 elems[20];           // +70
};

Class2c6a58::~Class2c6a58() {
    for (int i = 0; i < 20; i++)
        release_linked68(elems[i].obj);
    release_id(f18, 0x421a);
    release_id(f20, 0x421a);
}

class TableObj {
public:
    virtual ~TableObj();
    virtual void v10();
    virtual void attach(void* root);    // +18
};

void table_free(TableObj* obj);         // 0x71005d43a0

// 0x71002bd8cc (D2): the elements of 2beea8's array, a table of 17 objects and a handle.
struct TableElem2bd8cc {
    ~TableElem2bd8cc();

    unsigned char pad0[0x10];
    LayoutObj* obj;                 // +10
    unsigned char pad18[0x20];
    TableObj* table[17];            // +38
    DtorHandle h;                   // +c0
    unsigned char padd8[0x8];
};

TableElem2bd8cc::~TableElem2bd8cc() {
    void* root = handle_root_heap();
    for (int i = 0; i < 17; i++) {
        if (table[i]) {
            table[i]->attach(root);
            link_drop(obj->link, reinterpret_cast<ObjLink*>(table[i]));
            TableObj* t = table[i];
            if (t) {
                t->~TableObj();
                table_free(t);
            }
            table[i] = nullptr;
        }
    }
    release_in(obj, 0x4217);
}

inline void release68_in(LayoutObj*& p) {
    if (p) {
        ObjHeap* heap = gObjHeap;
        void* root = gHandleHeapOwner->heap + 0x10;
        obj_detach(p, root);
        p->destroy();
        heap_return(heap->list68, p);
        p = nullptr;
    }
}

void heap_note(ObjHeap* heap, void* at, int n);              // 0x71002925c8

class Mid2cff80 : public Basec719c {
public:
    virtual ~Mid2cff80() {
        if (open49f8) {
            heap_note(gObjHeap, s140, n49e0);
            closed();
            open49f8 = 0;
        }
    }
    virtual void v10(); virtual void v18(); virtual void v20(); virtual void v28(); virtual void v30();
    virtual void v38(); virtual void v40(); virtual void v48(); virtual void v50(); virtual void v58();
    virtual void v60(); virtual void v68(); virtual void v70(); virtual void v78(); virtual void v80();
    virtual void closed();          // +88

    unsigned char pad8[0x28];
    Part5d27b4 m30;                 // +30
    unsigned char pad40[0x100];
    unsigned char s140[0x48a0];     // +140
    int n49e0;                      // +49e0
    unsigned char pad49e4[0x14];
    unsigned char open49f8;         // +49f8
    unsigned char pad49f9[0x7];
};

// 0x71002cff80 (D2): a gate that releases one object, a member and a handle, then the inlined destructor of its base
// (its own vtable store and body) and the next base's destructor as a tail call.
class Class2cff80 : public Mid2cff80 {
public:
    ~Class2cff80();

    unsigned char pad4a00[0x9c40 - 0x4a00];
    DtorHandle h9c40;               // +9c40
    unsigned char pad9c58[0x18];
    Part5d27b4 m9c70;               // +9c70
    unsigned char pad9c80[0x100];
    LayoutObj* p9d80;               // +9d80
    unsigned char pad9d88[0xafa0 - 0x9d88];
    struct Gate { unsigned char closed; void shut(LayoutObj*& p) { if (!closed) { release68_in(p); closed = 0; } } } gate;   // +afa0
};

Class2cff80::~Class2cff80() {
    gate.shut(p9d80);
}

// Panels of the container: Mid2cff80 with one handle at its end.
class PanelA2d4a60 : public Mid2cff80 {
public:
    virtual void key();
    unsigned char pad4a00[0x18];
    DtorHandle h;                   // +4a18
};

class PanelB2d4a60 : public Mid2cff80 {
public:
    virtual void key();
    unsigned char pad4a00[0x1220];
    DtorHandle h;                   // +5c20
    unsigned char pad5c38[0x8];
};

template <unsigned long N> class Plain2d4a60 : public Basec719c {
public:
    unsigned char pad8[N - 8];
};

struct Part3c5cc0 { ~Part3c5cc0(); unsigned char data[0x10]; };              // 0x71003c5cc0

// 0x71002d4a60 (D2): a container without a vtable of its own; its members' destructors are inlined where they are
// inline (the panels and the first Mid2cff80) and called otherwise.
class Container2d4a60 {
public:
    ~Container2d4a60();

    Mid2cff80 m0;                   // +0
    unsigned char pad4a00[0x200];
    PanelA2d4a60 a4c00;             // +4c00
    PanelA2d4a60 a9630;             // +9630
    unsigned char pade060[0x10];
    PanelB2d4a60 be070;             // +e070
    Class2cff80 c13cb0;             // +13cb0
    unsigned char pad1ec70_[0x1ec70 - 0x13cb0 - sizeof(Class2cff80)];
    Plain2d4a60<0x4bc0> p1ec70;     // +1ec70
    Plain2d4a60<0x4bc0> p23830;     // +23830
    Plain2d4a60<0x9728> p283f0;     // +283f0
    Plain2d4a60<0x11a20> p31b18;    // +31b18
    Plain2d4a60<0x12418> p43538;    // +43538
    Plain2d4a60<0x12648> p55950;    // +55950
    Part3c5cc0 p67f98;              // +67f98
};

Container2d4a60::~Container2d4a60() {}