// Small constructors and destructors written by hand (third session), third unit. Names are descriptive
// placeholders. Status: matching/README.md.

extern "C" void* memcpy(void*, const void*, unsigned long);

namespace nn {
namespace os {
struct EventType {
    unsigned char data[0x28];
};
struct ThreadType {
    unsigned char data[0x1c0];
};
void SignalEvent(EventType* event);
void WaitThread(ThreadType* thread);
void DestroyThread(ThreadType* thread);
void FinalizeEvent(EventType* event);
}  // namespace os
}  // namespace nn

// 0x71001f10f4: vtable GOT 0x7100c23130. The base's fields are stored before the vtable; the -1 pair at +34 is
// one 8-byte copy of a constant, so it stays apart from the -1 at +30.
struct Pair1f10f4 {
    int a;
    int b;
};
static const Pair1f10f4 kNone1f10f4 = {-1, -1};

class Base1f10f4 {
public:
    Base1f10f4() : flags(0xa0300002), p10(nullptr), p18(nullptr) {}
    virtual ~Base1f10f4();

    unsigned int flags;          // +08
    void* p10;                   // +10
    void* p18;                   // +18
};

class Obj1f10f4 : public Base1f10f4 {
public:
    Obj1f10f4();
    ~Obj1f10f4();

    float m[4];                  // +20
    int i30;                     // +30
    Pair1f10f4 r34;              // +34
    int i3c;                     // +3c
    int i40;                     // +40
    int i44;                     // +44
    Pair1f10f4 r48;              // +48
    Pair1f10f4 r50;              // +50
    Pair1f10f4 r58;              // +58
    int i60;                     // +60
};

Obj1f10f4::Obj1f10f4() {
    m[0] = 1.0f;
    m[1] = 0.0f;
    m[2] = 0.0f;
    m[3] = 1.0f;
    i30 = -1;
    r34 = kNone1f10f4;
    i3c = 0;
    i40 = 0;
    i44 = 0;
    r48.a = 0;
    r48.b = 0;
    r50 = r48;
    r58 = r48;
    i60 = 0;
}

// 0x71000cb4d0: vtable GOT 0x7100c22938; seven -1 ids and a zeroed block.
class Basecafd4 {
public:
    Basecafd4();                 // 0x71000cafd4
    virtual ~Basecafd4();
    unsigned char pad8[0x20];
};

class Objcb4d0 : public Basecafd4 {
public:
    Objcb4d0();
    ~Objcb4d0();

    short ids[7];                // +28
    short count;                 // +36
    void* p38;                   // +38
    void* p40;                   // +40
    void* p48;                   // +48
    void* p50;                   // +50
    int i58;                     // +58
    short s5c;                   // +5c
    short s5e;                   // +5e
    int i60;                     // +60
    int limit;                   // +64
    int i68;                     // +68
};

Objcb4d0::Objcb4d0() {
    for (int i = 0; i < 7; i++)
        ids[i] = -1;
    count = 8;
    p38 = nullptr;
    p40 = nullptr;
    p48 = nullptr;
    p50 = nullptr;
    i58 = 0;
    s5c = 0;
    limit = 100;
    i68 = 0;
}

// 0x71005f3808 (D2, in s3_functions14).
class Buffer5f3808 {
public:
    virtual ~Buffer5f3808();

    void* p8;                    // +08
    void* p10;                   // +10
    int state;                   // +18
    unsigned char pad1c[0x4];
    void* data;                  // +20
};

class Base5c4278 {
public:
    virtual ~Base5c4278();       // 0x71005c4278
    unsigned char pad8[0x20];
};

// 0x71005c2234 and 0x71005c22e8 (D2): the same destructor twice. The owner resets its buffer (vtable GOT
// 0x7100c2b738), or has it closed through the buffer's vtable, then the buffer and the base go.
#define BUFFER_OWNER(NAME)                                                                                    \
    class NAME##Buffer : public Buffer5f3808 {                                                                \
    public:                                                                                                   \
        ~NAME##Buffer() {                                                                                     \
            if (p30)                                                                                          \
                p30 = nullptr;                                                                                \
        }                                                                                                     \
        virtual void v10();                                                                                   \
        virtual void v18();                                                                                   \
        virtual void close(void* arg);                                                                        \
        void reset() {                                                                                        \
            if (owned) {                                                                                      \
                owned = false;                                                                                \
                p30 = nullptr;                                                                                \
                p8 = nullptr;                                                                                 \
                state = 0;                                                                                    \
            } else {                                                                                          \
                close(nullptr);                                                                               \
            }                                                                                                 \
        }                                                                                                     \
                                                                                                              \
        void* p28;                                                                                            \
        void* p30;                                                                                            \
        bool owned;                                                                                           \
    };                                                                                                        \
                                                                                                              \
    class NAME : public Base5c4278 {                                                                          \
    public:                                                                                                   \
        virtual void anchor();                                                                                \
        ~NAME();                                                                                              \
                                                                                                              \
        NAME##Buffer buffer;                                                                                  \
    };                                                                                                        \
                                                                                                              \
    NAME::~NAME() { buffer.reset(); }

BUFFER_OWNER(Owner5c2234)
BUFFER_OWNER(Owner5c22e8)

// 0x71005f79fc (D2): a worker's teardown: if running, signal, join and destroy its thread; then its two events
// and its job slot (vtable GOT 0x7100c2de00) go.
class Job5f79fc {
public:
    virtual ~Job5f79fc();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void release();      // +28
};

class JobSlot5f79fc {
public:
    virtual void anchor();
    ~JobSlot5f79fc() {
        if (job) {
            job->release();
            job = nullptr;
        }
        p10 = nullptr;
    }

    Job5f79fc* job;              // +08
    void* p10;                   // +10
};

struct Event5f79fc {
    ~Event5f79fc() { nn::os::FinalizeEvent(&event); }
    nn::os::EventType event;
};

class Worker5f79fc {
public:
    ~Worker5f79fc();

    unsigned char pad0[0x90];
    JobSlot5f79fc slot;          // +90
    unsigned char pada8[0x98];
    nn::os::ThreadType thread;   // +140
    Event5f79fc wake;            // +300
    Event5f79fc done;            // +328
    unsigned char pad350[0x10];
    bool running;                // +360
    bool busy;                   // +361
};

Worker5f79fc::~Worker5f79fc() {
    if (running) {
        running = false;
        nn::os::SignalEvent(&wake.event);
        nn::os::WaitThread(&thread);
        nn::os::DestroyThread(&thread);
        busy = false;
    }
}

// 0x71005e3f48: a vertex/index buffer description: the index size from the index count, the vertex stride from
// the attribute bits (12-byte position, 12-byte normal, 8-byte texture coordinate).
class Mesh5e3f48 {
public:
    Mesh5e3f48(unsigned int attrs, int type, int segments);
    virtual ~Mesh5e3f48();

    void* p8;                    // +08
    void* p10;                   // +10
    unsigned int attrs;          // +18
    int index_type;              // +1c
    int type;                    // +20
    int vertex_count;            // +24
    int index_count;             // +28
    unsigned long vertex_bytes;  // +30
    unsigned long index_bytes;   // +38
    int segments;                // +40
};

Mesh5e3f48::Mesh5e3f48(unsigned int attrs_, int type_, int segments_)
    : p8(nullptr), p10(nullptr), attrs(attrs_), index_type(2), type(type_), index_count(0), vertex_bytes(0),
      index_bytes(0), segments(segments_) {
    vertex_count = segments_ + 1;
    int n;
    if (type_ == 2)
        n = vertex_count;
    else if (type_ == 3)
        n = segments_ * 3;
    else
        n = 0;
    if (n <= 0xff)
        index_type = 0;
    else if (n < 0x10000)
        index_type = 1;
    else
        index_type = 2;
    unsigned long stride = 0;
    if (attrs_ & 1)
        stride += 12;
    if (attrs_ & 2)
        stride += 12;
    if (attrs_ & 4)
        stride += 8;
    vertex_bytes = stride * (segments_ + 1);
    index_count = n;
    index_bytes = n * sizeof(unsigned int);
}

class DefaultHeap {
public:
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

// 0x71002d4d84 and 0x71002d4e4c (D2; their deleting forms 0x71002d61d4 and 0x71002d601c, deleted through the default
// heap): two screens on 2cff80's middle base, each holding a layout handle. 0x71002d60f8 is the second screen's
// deleting destructor once more (vtable GOT 0x7100c2aa88 too), from a class of its own.
struct ObjHeap;
// Reached through the GOT slot at 0x7100c22a00.
extern ObjHeap* gObjHeap;
void heap_note(ObjHeap* heap, void* at, int n);              // 0x71002925c8

struct Part5d27b4 { ~Part5d27b4(); unsigned char data[0x10]; };   // 0x71005d27b4

class Basec719c {
public:
    virtual ~Basec719c();        // 0x71003c719c
};

// The middle base (vtable GOT 0x7100c2aa68; its deleting destructor is in s3_functions15), inline here.
class Mid2d5f90 : public Basec719c {
public:
    ~Mid2d5f90() {
        if (open49f8) {
            heap_note(gObjHeap, s140, n49e0);
            closed();
            open49f8 = 0;
        }
    }
    virtual void v10(); virtual void v18(); virtual void v20(); virtual void v28(); virtual void v30();
    virtual void v38(); virtual void v40(); virtual void v48(); virtual void v50(); virtual void v58();
    virtual void v60(); virtual void v68(); virtual void v70(); virtual void v78(); virtual void v80();
    virtual void closed();

    unsigned char pad8[0x28];
    Part5d27b4 m30;
    unsigned char pad40[0x100];
    unsigned char s140[0x48a0];
    int n49e0;
    unsigned char pad49e4[0x14];
    unsigned char open49f8;
    unsigned char pad49f9[0x7];
};

struct LayoutContext;
struct LayoutRoot {
    unsigned char pad0[0x10];
    unsigned char context[0x10]; // +10
};
struct ResourceLoader {
    unsigned char pad0[0x2af8];
    LayoutRoot* layout;          // +2af8
};
// Reached through the GOT slot at 0x7100c21db0.
extern ResourceLoader* gResourceLoader;

inline LayoutContext* layout_context() {
    return gResourceLoader ? reinterpret_cast<LayoutContext*>(gResourceLoader->layout->context) : nullptr;
}

// The layout handle (vtable GOT 0x7100c22f00): its destructor releases it through the context. In its own
// module (0x71001e463c, s3_functions15) the release is inlined; here it stays a call through the vtable.
class HandleBody {
public:
    virtual void anchor();
    virtual ~HandleBody() { release(layout_context()); }
    virtual void release(LayoutContext* context);

    long id;                     // +08
};

class Screen2d4d84 : public Mid2d5f90 {
public:
    void v10();
    ~Screen2d4d84();
    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }

    unsigned char pad4a00[0x1220];
    HandleBody handle;           // +5c20
};

Screen2d4d84::~Screen2d4d84() {}

class Screen2d4e4c : public Mid2d5f90 {
public:
    void v10();
    ~Screen2d4e4c();
    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }

    unsigned char pad4a00[0x18];
    HandleBody handle;           // +4a18
};

Screen2d4e4c::~Screen2d4e4c() {}

class Screen2d60f8 : public Mid2d5f90 {
public:
    void v10();
    ~Screen2d60f8();
    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }

    unsigned char pad4a00[0x18];
    HandleBody handle;           // +4a18
};

Screen2d60f8::~Screen2d60f8() {}

// 0x7100534010: a table that keeps a copy of its entries and the distinct keys among them (at most 16).
struct Entry534010 {
    unsigned char key;
    unsigned char pad1[3];
    unsigned int value;
};

class Table534010 {
public:
    Table534010(const Entry534010* entries, unsigned int count, int value);
    virtual ~Table534010();

    int i8;                      // +08
    void* p10;                   // +10
    int value;                   // +18
    unsigned int key_count;      // +1c
    unsigned char keys[0x10];    // +20
    unsigned int count;          // +30
    Entry534010 entries[1];      // +34
};

Table534010::Table534010(const Entry534010* entries_, unsigned int count_, int value_)
    : i8(0), p10(nullptr), value(value_), count(count_) {
    memcpy(entries, entries_, count_ * sizeof(Entry534010));
    key_count = 0;
    for (unsigned int i = 0; i < count_; i++) {
        unsigned char key = entries_[i].key;
        unsigned int j;
        for (j = 0; j < key_count; j++) {
            if (keys[j] == key)
                break;
        }
        if (j >= key_count)
            keys[key_count++] = key;
    }
}

// 0x71005d4040: two intrusive lists; the second gets one node for each item of the resource the factory makes.
struct ListLink {
    ListLink* next;
    ListLink* prev;
};

struct Item5d4040;
struct ItemDesc5d4040 {
    unsigned char data[0x18];
};
struct Resource5d4040 {
    unsigned char pad0[0x8];
    unsigned char body[0x22];    // +08
    unsigned short item_count;   // +2a
    ItemDesc5d4040 items[1];     // +2c
};

class Factory5d4040 {
public:
    virtual void v00(); virtual void v08(); virtual void v10(); virtual void v18(); virtual void v20();
    virtual void v28(); virtual void v30(); virtual void v38(); virtual void v40(); virtual void v48();
    virtual void v50(); virtual void v58();
    virtual Item5d4040* create(const ItemDesc5d4040* desc, bool shared);   // +60
};

struct ItemNode5d4040 {
    static void* operator new(unsigned long size) noexcept;                 // 0x71005d4380
    ItemNode5d4040(Item5d4040* item_) {
        link.next = link.prev = &link;
        item = item_;
    }

    ListLink link;
    Item5d4040* item;            // +10
};

class Group5d4040 {
public:
    Group5d4040(Resource5d4040* resource, Factory5d4040* factory);
    virtual ~Group5d4040();

    ListLink list8;              // +08
    ListLink items;              // +18
    void* body;                  // +28
    bool flag30;                 // +30
};

Group5d4040::Group5d4040(Resource5d4040* resource, Factory5d4040* factory) {
    list8.next = list8.prev = &list8;
    items.next = items.prev = &items;
    body = resource->body;
    flag30 = false;
    for (long i = 0; i < resource->item_count; i++) {
        Item5d4040* item = factory->create(&resource->items[i], true);
        if (!item)
            continue;
        ItemNode5d4040* node = new ItemNode5d4040(item);
        if (!node)
            continue;
        node->link.next = items.next;
        node->link.prev = &items;
        items.next->prev = &node->link;
        items.next = &node->link;
    }
}
