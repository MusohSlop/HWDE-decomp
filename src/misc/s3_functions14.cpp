// Small constructors and destructors written by hand (third session). Names are descriptive placeholders.
// Status: matching/README.md.

extern "C" void* memset(void*, int, unsigned long);
void free_601040(void* ptr);                                 // 0x7100601040

namespace nn {
namespace os {
struct MutexType;
struct EventType;
enum EventClearMode { EventClearMode_ManualClear, EventClearMode_AutoClear };
void LockMutex(MutexType* mutex);
void UnlockMutex(MutexType* mutex);
void InitializeEvent(EventType* event, bool signaled, EventClearMode mode);
}  // namespace os
}  // namespace nn

struct ObjectManagerView {
    unsigned char pad0[0x80];
    unsigned char mutex[0x20];   // +80
};
// Reached through the GOT slot at 0x7100c21de8.
extern ObjectManagerView* gObjectManager;

static inline nn::os::MutexType* manager_mutex() {
    return reinterpret_cast<nn::os::MutexType*>(gObjectManager->mutex);
}

// A reference-counted object (its count at +8).
struct RefObj {
    unsigned char pad0[0x8];
    int refs;                    // +08
};

// 0x71000d4c9c: fifteen ids, all -1 (one 30-byte fill).
class IdTableD4c9c {
public:
    IdTableD4c9c();
    virtual ~IdTableD4c9c();

    short ids[15];            // +08
};

IdTableD4c9c::IdTableD4c9c() {
    for (int i = 0; i < 15; i++)
        ids[i] = -1;
}

// 0x71005f8348: a block whose buffer at +68 is cleared last.
class Block5f8348 {
public:
    Block5f8348();
    virtual ~Block5f8348();

    void* p8;                 // +08
    unsigned char pad10[0x38];
    void* p48;                // +48
    void* p50;                // +50
    unsigned char pad58[0x8];
    int count60;              // +60
    int kind64;               // +64
    unsigned char buf[0x60];  // +68
};

Block5f8348::Block5f8348() : p8(nullptr), p48(nullptr), p50(nullptr), count60(0), kind64(2), buf() {}

// 0x71005f6bf8: the same shape with kind 6 and the buffer at +40.
class Block5f6bf8 {
public:
    Block5f6bf8();
    virtual ~Block5f6bf8();

    void* p8;                 // +08
    unsigned char pad10[0x10];
    void* p20;                // +20
    void* p28;                // +28
    unsigned char pad30[0x8];
    int count38;              // +38
    int kind3c;               // +3c
    unsigned char buf[0x60];  // +40
};

Block5f6bf8::Block5f6bf8() : p8(nullptr), p20(nullptr), p28(nullptr), count38(0), kind3c(6), buf() {}

// 0x71001f1594: the colour is its base's member, so its store comes before the vtable store and is not merged
// with the id; the position is two int stores, so the copy into the base position reads it back.
struct Pair1f1594 {
    int a, b;
    Pair1f1594() : a(0), b(0) {}
};

class ColorBase1f1594 {
public:
    ColorBase1f1594() : color(0xa0300303) {}
    virtual ~ColorBase1f1594();

    unsigned int color;       // +08
};

class Pane1f1594 : public ColorBase1f1594 {
public:
    Pane1f1594();
    virtual ~Pane1f1594();

    int id;                   // +0c
    Pair1f1594 pos;           // +10
    Pair1f1594 base;          // +18
    int value20;              // +20
    float scale;              // +24
};

Pane1f1594::Pane1f1594() : id(-1), base(pos), value20(0), scale(1.0f) {}

// A pointer that takes a reference when set.
struct RefPtr {
    RefObj* p;
    explicit RefPtr(RefObj* p_) : p(p_) {
        if (p)
            p->refs++;
    }
};

// 0x71005332a0: COUNT pointer slots cleared in place, after a reference to the owner.
class SlotsBase5332a0 {
public:
    SlotsBase5332a0() : value8(0) {}
    virtual ~SlotsBase5332a0();

    int value8;               // +08
};

class Slots5332a0 : public SlotsBase5332a0 {
public:
    Slots5332a0(int count, RefObj* owner);
    virtual ~Slots5332a0();

    RefPtr owner;             // +10
    int count;                // +18
    void* slots[1];           // +20
};

Slots5332a0::Slots5332a0(int count_, RefObj* owner_) : owner(owner_), count(count_) {
    memset(slots, 0, count_ * sizeof(void*));
}

// 0x710034a910 (D2): 100 elements destroyed in a loop.
struct Elem34a910 {
    ~Elem34a910();            // 0x710034d974
    unsigned char data[0xb0];
};

class List34a910 {
public:
    virtual ~List34a910();

    unsigned char pad8[0x18];
    Elem34a910 elems[100];    // +20
};

List34a910::~List34a910() {}

// 0x71005f3808 (D2): frees its buffer unless its state is 0 or 2.
class Buffer5f3808 {
public:
    virtual ~Buffer5f3808();

    void* p8;                 // +08
    void* p10;                // +10
    int state;                // +18
    unsigned char pad1c[0x4];
    void* data;               // +20
};

Buffer5f3808::~Buffer5f3808() {
    if (state != 0 && state != 2)
        free_601040(data);
    state = 0;
    p8 = nullptr;
    p10 = nullptr;
}

// 0x7100595930 and 0x71005959d4 (D2): a named node kept in a global list sorted by its name's hash (linked
// through +18); the destructor unlinks it.
class Node5959d4;
// Reached through the GOT slot at 0x7100c2d798.
extern Node5959d4* gNodeList5959d4;

class Node5959d4 {
public:
    Node5959d4(const char* name);
    virtual ~Node5959d4();

    unsigned int hash;        // +08
    const char* name;         // +10
    Node5959d4* next;         // +18
};

Node5959d4::Node5959d4(const char* name_) : name(name_) {
    unsigned int h = 0;
    for (const unsigned char* p = reinterpret_cast<const unsigned char*>(name_); *p; p++)
        h = h * 27 + *p;
    hash = h;
    Node5959d4* prev = nullptr;
    Node5959d4* node = gNodeList5959d4;
    while (node && node->hash < h) {
        prev = node;
        node = node->next;
    }
    if (prev) {
        prev->next = this;
        next = node;
    } else {
        next = gNodeList5959d4;
        gNodeList5959d4 = this;
    }
}

Node5959d4::~Node5959d4() {
    Node5959d4* prev = nullptr;
    Node5959d4* node = gNodeList5959d4;
    while (node && node != this) {
        prev = node;
        node = node->next;
    }
    if (node) {
        if (!prev)
            gNodeList5959d4 = next;
        else
            prev->next = next;
    }
}

// Reached through the GOT slot at 0x7100c2da48.
extern int gCount5b38e8;

// 0x71005b38e8: cleared, then counted under the object manager's lock.
class Counted5b38e8 {
public:
    Counted5b38e8();
    virtual ~Counted5b38e8();

    void* f8;
    void* f10;
    void* f18;
    void* f20;
    void* f28;
    void* f30;
    void* f38;
    void* f40;
};

Counted5b38e8::Counted5b38e8()
    : f8(nullptr), f18(nullptr), f20(nullptr), f28(nullptr), f30(nullptr), f38(nullptr), f40(nullptr) {
    nn::os::LockMutex(manager_mutex());
    gCount5b38e8++;
    nn::os::UnlockMutex(manager_mutex());
}

// 0x71000d2784: five parts, then its reset (a virtual call).
struct Part7572c {
    Part7572c();              // 0x710007572c
    unsigned char data[0x40];
};

class Group_d2784 {
public:
    Group_d2784();
    virtual ~Group_d2784();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void reset();     // +28

    unsigned char pad8[0x8];
    Part7572c parts[5];       // +10
    int value150;             // +150
};

Group_d2784::Group_d2784() : value150(0) {
    reset();
}

// 0x71005c49fc: a frame heap holding a reference to its owner (counted under the object manager's lock).
class Plain_5c2c78 {
public:
    Plain_5c2c78();              // 0x71005c2c78
    virtual ~Plain_5c2c78();
};

class FrameHeapImpl {
public:
    FrameHeapImpl();             // 0x71005c2d24
    unsigned char data[0x60];
};

class OwnedHeap5c49fc : public Plain_5c2c78 {
public:
    explicit OwnedHeap5c49fc(RefObj* owner);
    virtual ~OwnedHeap5c49fc();

    FrameHeapImpl heap;          // +08
    RefObj* owner;               // +68
};

OwnedHeap5c49fc::OwnedHeap5c49fc(RefObj* owner_) : owner(owner_) {
    nn::os::LockMutex(manager_mutex());
    owner_->refs++;
    nn::os::UnlockMutex(manager_mutex());
}

// 0x71005f7984: a worker with a request block (vtable at +90) and two events.
class RequestBlock5f7984 {
public:
    RequestBlock5f7984() : p8(nullptr), p30(nullptr), p38(nullptr), count48(0), kind4c(2), buf() {}
    virtual ~RequestBlock5f7984();

    void* p8;                 // +08
    unsigned char pad10[0x20];
    void* p30;                // +30
    void* p38;                // +38
    unsigned char pad40[0x8];
    int count48;              // +48
    int kind4c;               // +4c
    unsigned char buf[0x60];  // +50
};

class Worker5f7984 {
public:
    Worker5f7984();

    unsigned char pad0[0x70];
    void* p70;                // +70
    void* p78;                // +78
    void* p80;                // +80
    unsigned char pad88[0x8];
    RequestBlock5f7984 block; // +90
    unsigned char pad140[0x1c0];
    unsigned char ready[0x28];   // +300
    unsigned char done[0x28];    // +328
    unsigned char pad350[0xc];
    long value35c __attribute__((packed, aligned(4)));   // +35c
};

Worker5f7984::Worker5f7984() : p70(nullptr), p78(nullptr), p80(nullptr) {
    nn::os::InitializeEvent(reinterpret_cast<nn::os::EventType*>(ready), false, nn::os::EventClearMode_AutoClear);
    nn::os::InitializeEvent(reinterpret_cast<nn::os::EventType*>(done), false, nn::os::EventClearMode_ManualClear);
    value35c = 0;
}

// 0x71002d4f14 (D2): the middle base of 2cff80 (s3_functions05's Mid2cff80), its destructor out of line here.
struct ObjHeap;
// Reached through the GOT slot at 0x7100c22a00.
extern ObjHeap* gObjHeap;
void heap_note(ObjHeap* heap, void* at, int n);              // 0x71002925c8

struct Part5d27b4 { ~Part5d27b4(); unsigned char data[0x10]; };   // 0x71005d27b4

class Basec719c {
public:
    virtual ~Basec719c();           // 0x71003c719c
};

class Mid2d4f14 : public Basec719c {
public:
    ~Mid2d4f14();
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

Mid2d4f14::~Mid2d4f14() {
    if (open49f8) {
        heap_note(gObjHeap, s140, n49e0);
        closed();
        open49f8 = 0;
    }
}

// 0x7100533118: a table of COUNT 0x48-byte items cleared in place; the items' address is taken before the count is
// stored (it decides the registers).
struct Item533118 {
    void* first;
    unsigned char data[0x40];
};

class Table533118 {
public:
    explicit Table533118(int count);
    virtual ~Table533118();

    int value8;               // +08
    void* p10;                // +10
    int count;                // +18
    Item533118 items[1];      // +20
};

Table533118::Table533118(int count_) : value8(0), p10(nullptr) {
    Item533118* p = items;
    count = count_;
    memset(p, 0, count_ * sizeof(Item533118));
}