// Channel destructors written by hand (third session): reference-counted objects released and their tables freed,
// links that leave their targets. Names are descriptive placeholders. Status: matching/README.md.

struct Listener;

// The listener hub: detach at +60.
struct ListenerHub {
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
    virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
    virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11();
    virtual void detach(Listener* listener);    // +60
};
// Reached through the GOT slot at 0x7100c2d010.
extern ListenerHub* gHub_c2d010;

class ChannelBase {
public:
    virtual ~ChannelBase();      // 0x71005c3ac8

    void* p8;                    // +08
};

// A reference-counted object: the count at +08, destroy at +18.
struct Counted574024 {
    virtual void v00(); virtual void v08(); virtual void v10();
    virtual void destroy();      // +18
    int refs;                    // +08
};

// 0x7100574024 and 0x71005740a4 (D2): the same destructor twice (vtable GOT 0x7100c2d608): releases its objects.
#define OBJECT_CHANNEL(NAME)                                                                                  \
    class NAME : public ChannelBase {                                                                         \
    public:                                                                                                   \
        virtual void anchor();                                                                                \
        ~NAME();                                                                                              \
                                                                                                              \
        unsigned char pad10[0xc];                                                                             \
        unsigned int count;                                                                                   \
        Counted574024** objects;                                                                              \
    };                                                                                                        \
                                                                                                              \
    NAME::~NAME() {                                                                                           \
        for (unsigned int i = 0; i < count; i++) {                                                            \
            if (Counted574024* object = objects[i]) {                                                         \
                if (--object->refs == 0)                                                                      \
                    object->destroy();                                                                        \
                objects[i] = nullptr;                                                                         \
            }                                                                                                 \
        }                                                                                                     \
    }

OBJECT_CHANNEL(Channel574024)
OBJECT_CHANNEL(Channel5740a4)

// A link's target keeps one of two slots pointing at the link.
struct LinkTarget {
    unsigned char pad0[0x20];
    void* slots[2];              // +20
};
struct LinkOwner {
    unsigned char pad0[0x10];
    LinkTarget* target;          // +10
};

// A channel base 0x48 bytes long; its destructor is the same empty one (0x71005c3ac8).
class ChannelBase48 {
public:
    virtual ~ChannelBase48();
    virtual void v10();
    virtual void v18();
    virtual void v20();

    unsigned char pad8[0x40];
};

class LinkBase {
public:
    virtual void link_v00();
    LinkOwner* owner;            // +08
};

// 0x7100526f68 and 0x71005274a0 (D2): a channel that is also a link (at +48); the link leaves its target, the
// listener leaves the hub. Vtables GOT 0x7100c2d1d8 and 0x7100c2d1e0.
#define LINK_CHANNEL(NAME)                                                                                    \
    class NAME : public ChannelBase48, public LinkBase {                                                      \
    public:                                                                                                   \
        virtual void anchor();                                                                                \
        ~NAME();                                                                                              \
                                                                                                              \
        Listener* listener;                                                                                   \
    };                                                                                                        \
                                                                                                              \
    NAME::~NAME() {                                                                                           \
        LinkBase* link = this;                                                                                \
        LinkTarget* target = link->owner->target;                                                             \
        for (int i = 0; i < 2; i++) {                                                                         \
            if (target->slots[i] == link) {                                                                   \
                target->slots[i] = nullptr;                                                                   \
                break;                                                                                        \
            }                                                                                                 \
        }                                                                                                     \
        Listener* l = listener;                                                                               \
        gHub_c2d010->detach(l);                                                                               \
    }

LINK_CHANNEL(Channel526f68)
LINK_CHANNEL(Channel5274a0)

struct Heap497370 {
    virtual void v00(); virtual void v08(); virtual void v10(); virtual void v18(); virtual void v20();
    virtual void v28(); virtual void v30(); virtual void v38(); virtual void v40(); virtual void v48();
    virtual void v50(); virtual void v58();
    virtual void free(void* ptr);   // +60
};

static inline void release_ref(Counted574024*& ptr) {
    if (Counted574024* p = ptr) {
        if (--p->refs == 0)
            p->destroy();
        ptr = nullptr;
    }
}

// 0x7100497370 (D2): vtable GOT 0x7100c2cb78; its objects, their table (freed on its heap) and two more objects.
class Channel497370 : public ChannelBase {
public:
    virtual void anchor();
    ~Channel497370();

    Heap497370* heap;            // +10
    void* p18;                   // +18
    Counted574024** objects;     // +20
    unsigned long count;         // +28
    Counted574024* p30;          // +30
    Counted574024* p38;          // +38
};

Channel497370::~Channel497370() {
    for (unsigned long i = 0; i < count; i++) {
        if (Counted574024* object = objects[i]) {
            if (--object->refs == 0)
                object->destroy();
            objects[i] = nullptr;
        }
    }
    if (objects && heap) {
        heap->free(objects);
        objects = nullptr;
    }
    release_ref(p30);
    release_ref(p38);
}

namespace nn {
namespace os {
struct MutexType;
void LockMutex(MutexType* mutex);
void UnlockMutex(MutexType* mutex);
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

struct Entry5743b4 {
    Counted574024* object;
    void* p8;
};

// 0x71005743b4 (D2): vtable GOT 0x7100c2d610; an object released under the object manager's lock, then the objects
// of its entries.
class Channel5743b4 : public ChannelBase {
public:
    virtual void anchor();
    ~Channel5743b4();

    void* p10;                   // +10
    Counted574024* owner;        // +18
    int count;                   // +20
    Entry5743b4* entries;        // +28
};

Channel5743b4::~Channel5743b4() {
    if (Counted574024* p = owner) {
        nn::os::LockMutex(manager_mutex());
        int refs = --p->refs;
        nn::os::UnlockMutex(manager_mutex());
        if (refs == 0)
            p->destroy();
        owner = nullptr;
    }
    if (entries) {
        unsigned int n = count + 3;
        for (unsigned int i = 0; i < n; i++) {
            if (Counted574024* object = entries[i].object) {
                if (--object->refs == 0)
                    object->destroy();
                entries[i].object = nullptr;
            }
        }
    }
}
// 0x710056fdb0 (D2): vtable GOT 0x7100c2d550; its objects, then three more (the first under the object manager's lock).
class Channel56fdb0 : public ChannelBase {
public:
    virtual void anchor();
    ~Channel56fdb0();

    void* p10;                   // +10
    Counted574024* owner;        // +18
    Counted574024* p20;          // +20
    unsigned int count;          // +28
    Counted574024** objects;     // +30
    Counted574024* p38;          // +38
};

Channel56fdb0::~Channel56fdb0() {
    for (unsigned int i = 0; i < count; i++) {
        if (Counted574024* object = objects[i]) {
            if (--object->refs == 0)
                object->destroy();
            objects[i] = nullptr;
        }
    }
    release_ref(p38);
    if (Counted574024* p = owner) {
        nn::os::LockMutex(manager_mutex());
        int refs = --p->refs;
        nn::os::UnlockMutex(manager_mutex());
        if (refs == 0)
            p->destroy();
        owner = nullptr;
    }
    release_ref(p20);
}

class DefaultHeap {
public:
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

struct Cell40a68c {
    ~Cell40a68c();               // 0x710025b3ac
    unsigned char data[0x28];
};

// 0x710040a68c (D0, deleted through the default heap): vtable GOT 0x7100c2b740; 135 cells.
class Grid40a68c {
public:
    virtual void anchor();
    virtual ~Grid40a68c();
    static void operator delete(void* ptr) {
        if (ptr)
            get_default_heap()->release(ptr, 1, 0);
    }

    Cell40a68c cells[135];       // +8
};

Grid40a68c::~Grid40a68c() {}