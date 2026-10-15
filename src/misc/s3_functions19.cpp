// Mid-size destructors written by hand (third session): light effect nodes released through the effect
// manager, pages on 3a43c4's base, the handle registry and heap-owned buffers. Names are descriptive
// placeholders. Status: matching/README.md.

#include "event/demo_effects.h"

namespace nn {
namespace os {
struct MutexType {
    unsigned char data[0x20];
};
void LockMutex(MutexType* mutex);
void UnlockMutex(MutexType* mutex);
}  // namespace os
}  // namespace nn

// An allocator: free at +60.
class Heap56e698 {
public:
    virtual void v00(); virtual void v08(); virtual void v10(); virtual void v18(); virtual void v20();
    virtual void v28(); virtual void v30(); virtual void v38(); virtual void v40(); virtual void v48();
    virtual void v50(); virtual void v58();
    virtual void free(void* ptr);    // +60
};
// Reached through the GOT slot at 0x7100c2d3e8.
extern Heap56e698* gHeap56e698;

// A buffer on the global heap.
struct Buffer56e698 {
    ~Buffer56e698() {
        if (data) {
            gHeap56e698->free(data);
            data = nullptr;
            end = nullptr;
            begin = nullptr;
        }
    }

    void* begin;                 // +00
    void* end;                   // +08
    void* data;                  // +10
};

struct Pair56e698 {
    Buffer56e698 first;          // +00
    Buffer56e698 second;         // +18
};

// The base (vtable GOT 0x7100c2d458), its destructor inline here.
class Base56e698 {
public:
    virtual void anchor();
    virtual ~Base56e698() {
        if (pa0)
            allocator->free(pa0);
    }

    unsigned char pad8[0x90];
    Heap56e698* allocator;       // +98
    void* pa0;                   // +a0
};

// 0x710056e698 (D2): vtable GOT 0x7100c2d540; a pair of buffers and a block freed through its own allocator,
// two buffers on the global heap.
class Obj56e698 : public Base56e698 {
public:
    void anchor();
    ~Obj56e698();

    unsigned char pada8[0x30];
    Pair56e698* pair;            // +d8
    Buffer56e698 bufe0;          // +e0
    Buffer56e698 buff8;          // +f8
    void* p110;                  // +110
};

Obj56e698::~Obj56e698() {
    if (pair) {
        pair->~Pair56e698();
        allocator->free(pair);
    }
    if (p110)
        allocator->free(p110);
}

// A pair cleared when its owner goes.
struct Pair3c5cc0 {
    ~Pair3c5cc0() {
        a = nullptr;
        b = nullptr;
    }
    void* a;
    void* b;
};

// One slot of the screen: a light effect node released through the effect manager's node list.
struct Elem3c5cc0 {
    ~Elem3c5cc0() {
        if (node) {
            EffectManager* manager = gEffectManager;
            void* root = gResourceLoader->layout->root;
            node->detach(root);
            node->release();
            manager->nodes.remove(node);
            node = nullptr;
        }
        node = nullptr;
    }

    LightEffectNode* node;       // +00
    unsigned char pad8[0x28];
    Pair3c5cc0 pair;             // +30
    unsigned char pad40[0x1110];
};

class Basec719c {
public:
    virtual ~Basec719c();        // 0x71003c719c
};

// 0x71003c5cc0 (D2): vtable GOT 0x7100c2b480; twelve slots.
class Screen3c5cc0 : public Basec719c {
public:
    virtual void anchor();
    ~Screen3c5cc0();
    void close();                // 0x71003c5d8c

    unsigned char pad8[0x20];
    bool open;                   // +28
    unsigned char pad29[0xf];
    Elem3c5cc0 elems[12];        // +38
};

Screen3c5cc0::~Screen3c5cc0() {
    if (open)
        close();
}

// The handle registry: an id leaves it under the registry's lock.
struct Listener;

struct ListenerHub {
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
    virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
    virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11();
    virtual void detach(Listener* listener);    // +60
};
// Reached through the GOT slot at 0x7100c2d010.
extern ListenerHub* gHub_c2d010;

struct IdHandler {
    virtual void slot0();
    virtual void remove(long id);               // +08
};

struct IdNode {
    long id;                     // +00
    unsigned char pad8[8];
    IdNode* next;                // +10
};

struct IdList {
    unsigned char pad[0x20];
    IdNode* head;                // +20
};
void remove_node_520ac0(IdList* list, IdNode* node);                       // 0x7100520ac0

struct Registry {
    nn::os::MutexType mutex;     // +00
    unsigned char pad20[0x120];
    IdList ids;                  // +140
    unsigned char pad168[0x30];
    IdHandler* handler;          // +198
};

static inline void unregister_id(Registry* registry, long id) {
    nn::os::LockMutex(&registry->mutex);
    if (registry->handler) {
        registry->handler->remove(id);
    } else {
        for (IdNode* node = registry->ids.head; node; node = node->next) {
            if (node->id == id) {
                remove_node_520ac0(&registry->ids, node);
                break;
            }
        }
    }
    nn::os::UnlockMutex(&registry->mutex);
}

class ChannelBase {
public:
    virtual ~ChannelBase();      // 0x71005c3ac8

    void* p8;                    // +08
};

// Reached through the GOT slot at 0x7100c2c010: a free hook.
extern void (*gFreeHook_c2c010)(void* ptr);

// 0x71005244a0 (D2): vtable GOT 0x7100c2d168.
class Channel5244a0 : public ChannelBase {
public:
    virtual void anchor();
    ~Channel5244a0();

    long id;                     // +10
    Registry* registry;          // +18
    Listener* listener;          // +20
    unsigned char pad28[0x10];
    void* buffer;                // +38
};

Channel5244a0::~Channel5244a0() {
    if (buffer)
        gFreeHook_c2c010(buffer);
    if (id != -1)
        unregister_id(registry, id);
    if (listener)
        gHub_c2d010->detach(listener);
}

// Pages on 3a43c4's base.
struct ObjHeap;
// Reached through the GOT slot at 0x7100c22a00.
extern ObjHeap* gObjHeap;
void heap_note(ObjHeap* heap, void* at, int n);              // 0x71002925c8

void* load_global_334a04();                                 // 0x7100334a04
struct PageOverride;
// Reached through the GOT slot at 0x7100c22da8.
extern PageOverride* gPageOverride;

inline bool page_ids() { return !load_global_334a04() && !gPageOverride; }

// 3a43c4's base (vtable GOT 0x7100c2b2b0; its destructor is out of line in s3_functions15, inline here).
class Base3aab84 {
public:
    virtual ~Base3aab84() {
        if (active) {
            if (page_ids())
                heap_note(gObjHeap, s8, id22fc);
            else
                heap_note(gObjHeap, s8, id2300);
            closed();
            active = 0;
        }
    }
    virtual void v10(); virtual void v18(); virtual void v20(); virtual void v28(); virtual void v30();
    virtual void v38(); virtual void v40(); virtual void v48();
    virtual void closed();       // +50

    unsigned char s8[0x22f4];    // +8
    int id22fc;                  // +22fc
    int id2300;                  // +2300
    unsigned char pad2304[0x18];
    unsigned char active;        // +231c
};

// 0x710039ef38 and 0x71003a164c (D2): a page with a light effect node (vtables GOT 0x7100c2b2c8 and
// 0x7100c2b2c0); with page ids the node is unregistered and leaves the manager's children, otherwise its nodes.
// Each path reads the manager first, so the node test is not hoisted out of them.
#define NODE_PAGE(NAME)                                                                                       \
    class NAME : public Base3aab84 {                                                                          \
    public:                                                                                                   \
        void v10();                                                                                           \
        ~NAME();                                                                                              \
                                                                                                              \
        LightEffectNode* node;                                                                                \
        unsigned char pad2328[0x58];                                                                          \
    };                                                                                                        \
                                                                                                              \
    NAME::~NAME() {                                                                                           \
        if (page_ids()) {                                                                                     \
            EffectManager* manager = gEffectManager;                                                          \
            if (node) {                                                                                       \
                void* root = gResourceLoader->layout->root;                                                   \
                manager->unregister(manager->registry, 0x4202);                                               \
                node->detach(root);                                                                           \
                node->release();                                                                              \
                manager->children.remove(node);                                                               \
                node = nullptr;                                                                               \
            }                                                                                                 \
        } else {                                                                                              \
            EffectManager* manager = gEffectManager;                                                          \
            if (node) {                                                                                       \
                node->detach(gResourceLoader->layout->root);                                                  \
                node->release();                                                                              \
                manager->nodes.remove(node);                                                                  \
                node = nullptr;                                                                               \
            }                                                                                                 \
        }                                                                                                     \
    }

NODE_PAGE(Page39ef38)
NODE_PAGE(Page3a164c)

struct Player37cd6c {
    ~Player37cd6c();             // 0x710037f568
    void stop();                 // 0x710037cd6c
    unsigned char data[0x40];
};

// The screen base (vtable GOT 0x7100c2b2d0): stops its player.
class ScreenBase3ab2bc {
public:
    virtual void anchor();
    virtual ~ScreenBase3ab2bc() { player.stop(); }

    unsigned char pad8[0x78];
    Player37cd6c player;         // +80
};

// 0x71003ab2bc (D2): vtable GOT 0x7100c2b318; two node pages (their destructors called) and two plain pages
// (inline).
class Screen3ab2bc : public ScreenBase3ab2bc {
public:
    void anchor();
    ~Screen3ab2bc();

    Page39ef38 page_c0;          // +c0
    Page39ef38 page_2440;        // +2440
    Base3aab84 page_47c0;        // +47c0
    Base3aab84 page_6ae0;        // +6ae0
};

Screen3ab2bc::~Screen3ab2bc() {}
