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

class DefaultHeap {
public:
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

// 0x71003c5cc0 (D2) and 0x71003c5e74 (D0, deleted through the default heap): vtable GOT 0x7100c2b480; twelve slots.
class Screen3c5cc0 : public Basec719c {
public:
    virtual void anchor();
    ~Screen3c5cc0();
    static void operator delete(void* ptr) {
        if (ptr)
            get_default_heap()->release(ptr, 1, 0);
    }
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
#define NODE_PAGE(NAME, SIZE)                                                                                     \
    class NAME : public Base3aab84 {                                                                          \
    public:                                                                                                   \
        void v10();                                                                                           \
        ~NAME();                                                                                              \
                                                                                                              \
        LightEffectNode* node;                                                                                \
        unsigned char pad2328[SIZE - 0x2328];                                                                 \
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

NODE_PAGE(Page39ef38, 0x2380)
NODE_PAGE(Page3a164c, 0xabf0)

struct Player37cd6c {
    ~Player37cd6c();             // 0x710037f568
    void stop();                 // 0x710037cd6c
    unsigned char data[0x30];
};

// The screen base (vtable GOT 0x7100c2b2d0): stops its player.
class ScreenBase3ab2bc {
public:
    virtual void anchor();
    virtual ~ScreenBase3ab2bc() { player.stop(); }

    unsigned char pad8[0x78];
    Player37cd6c player;         // +80
    unsigned char padb0[0x10];
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

// 0x71003a149c (D2): vtable GOT 0x7100c2b2e0; five node pages (their destructors called) and two plain pages
// (inline).
class Screen3a149c : public ScreenBase3ab2bc {
public:
    void anchor();
    ~Screen3a149c();

    void* pc0;                   // +c0
    Page3a164c page_c8;          // +c8
    Page3a164c page_acb8;        // +acb8
    Page3a164c page_158a8;       // +158a8
    Page3a164c page_20498;       // +20498
    Page3a164c page_2b088;       // +2b088
    Base3aab84 page_35c78;       // +35c78
    Base3aab84 page_37f98;       // +37f98
};

Screen3a149c::~Screen3a149c() {}
// 0x71003ab044 (D2): vtable GOT 0x7100c2b310; four node pages and three plain pages.
class Screen3ab044 : public ScreenBase3ab2bc {
public:
    void anchor();
    ~Screen3ab044();

    Page3a164c page_c0;          // +c0
    Page3a164c page_acb0;        // +acb0
    Page3a164c page_158a0;       // +158a0
    Page3a164c page_20490;       // +20490
    Base3aab84 page_2b080;       // +2b080
    Base3aab84 page_2d3a0;       // +2d3a0
    Base3aab84 page_2f6c0;       // +2f6c0
};

Screen3ab044::~Screen3ab044() {}

// 0x71003ab454 (D2): vtable GOT 0x7100c2b320; three node pages and three plain pages.
class Screen3ab454 : public ScreenBase3ab2bc {
public:
    void anchor();
    ~Screen3ab454();

    Page3a164c page_c0;          // +c0
    Page3a164c page_acb0;        // +acb0
    Page3a164c page_158a0;       // +158a0
    Base3aab84 page_20490;       // +20490
    Base3aab84 page_227b0;       // +227b0
    Base3aab84 page_24ad0;       // +24ad0
};

Screen3ab454::~Screen3ab454() {}
// One slot: a light effect node unregistered and released through the effect manager (read before the test).
struct Slot365dc4 {
    ~Slot365dc4() {
        EffectManager* manager = gEffectManager;
        if (node) {
            void* root = gResourceLoader->layout->root;
            manager->unregister(manager->registry, 0x4203);
            node->detach(root);
            node->release();
            manager->children.remove(node);
            node = nullptr;
        }
    }

    unsigned char pad0[0x18];
    LightEffectNode* node;       // +18
    unsigned char pad20[0x2230];
};

// 0x7100365dc4 (D2): vtable GOT 0x7100c2b008; stops its player, then eleven slots go.
class Menu365dc4 {
public:
    virtual void anchor();
    virtual ~Menu365dc4();

    Slot365dc4 slots[11];        // +8
    unsigned char pad17978[0x118];
    Player37cd6c player;         // +17a90
};

Menu365dc4::~Menu365dc4() { player.stop(); }

static inline void release_node(LightEffectNode*& node) {
    if (node) {
        EffectManager* manager = gEffectManager;
        void* root = gResourceLoader->layout->root;
        node->detach(root);
        node->release();
        manager->nodes.remove(node);
        node = nullptr;
    }
}

// One slot: a light effect node, released again when the slot goes.
struct Slot34dd88 {
    ~Slot34dd88() { release_node(node); }

    LightEffectNode* node;       // +00
    unsigned char pad8[0x2250];
};

// 0x710034dd88 (D2): 36 slots, their nodes released first; then the player is stopped.
class Board34dd88 {
public:
    ~Board34dd88();

    Slot34dd88 slots[36];        // +0
    Player37cd6c player;         // +4d460
};

Board34dd88::~Board34dd88() {
    for (long i = 0; i < 36; i++)
        release_node(slots[i].node);
    player.stop();
}

// The layout handle (vtable GOT 0x7100c22f00): its destructor releases it through the context.
struct LayoutContext;
inline LayoutContext* layout_context() {
    return gResourceLoader ? reinterpret_cast<LayoutContext*>(gResourceLoader->layout->root) : nullptr;
}

class HandleBody {
public:
    virtual void anchor();
    virtual ~HandleBody() { release(layout_context()); }
    virtual void release(LayoutContext* context);

    long id;                     // +08
};

// One slot of the menu: a light effect node released through the effect manager, and a layout handle.
struct Elem367498 {
    ~Elem367498() {
        EffectManager* manager = gEffectManager;
        if (node) {
            void* root = gResourceLoader->layout->root;
            manager->unregister(manager->registry, 0x4203);
            node->detach(root);
            node->release();
            manager->children.remove(node);
            node = nullptr;
        }
    }

    unsigned char pad0[0x10];
    LightEffectNode* node;       // +10
    unsigned char pad18[0x2690];
    HandleBody handle;           // +26a8
};

struct Part367498 {
    ~Part367498();               // 0x710036b06c
    unsigned char data[0x10];
};

// 0x7100367498 (D2): vtable GOT 0x7100c2b010; 13 slots, a player and a part.
class Menu367498 {
public:
    virtual void anchor();
    virtual ~Menu367498();

    void* p8;                    // +08
    Elem367498 elems[13];        // +10
    unsigned char pad1f768[0x190];
    Player37cd6c player;         // +1f8f8
    Part367498 part;             // +1f928
};

Menu367498::~Menu367498() { player.stop(); }

// 0x71003aace4 (D2): vtable GOT 0x7100c2b2d8; six plain pages.
class Screen3aace4 : public ScreenBase3ab2bc {
public:
    void anchor();
    ~Screen3aace4();

    Base3aab84 page_c0;          // +c0
    Base3aab84 page_23e0;        // +23e0
    Base3aab84 page_4700;        // +4700
    Base3aab84 page_6a20;        // +6a20
    Base3aab84 page_8d40;        // +8d40
    Base3aab84 page_b060;        // +b060
};

Screen3aace4::~Screen3aace4() {}
// 0x71003a4f90 (D2): a node holder with a layout handle; the node is released as on a node page.
struct NodeHolder3a4f90 {
    ~NodeHolder3a4f90();

    LightEffectNode* node;       // +00
    unsigned char pad8[0x20];
    HandleBody handle;           // +28
    unsigned char pad38[0x1118];
};

NodeHolder3a4f90::~NodeHolder3a4f90() {
    if (page_ids()) {
        EffectManager* manager = gEffectManager;
        if (node) {
            void* root = gResourceLoader->layout->root;
            manager->unregister(manager->registry, 0x4202);
            node->detach(root);
            node->release();
            manager->children.remove(node);
            node = nullptr;
        }
    } else {
        EffectManager* manager = gEffectManager;
        if (node) {
            node->detach(gResourceLoader->layout->root);
            node->release();
            manager->nodes.remove(node);
            node = nullptr;
        }
    }
}
void table_free(void* obj);                                                  // 0x71005d43a0

class Pane2bfda4 {
public:
    virtual ~Pane2bfda4();
    virtual void v10();
    virtual void unbind(LayoutContext* context);    // +18
};

class PaneGroup {
public:
    void remove(Pane2bfda4* pane);                                          // 0x71005da1b0
};

// 0x71002bfda4 (D2): seventeen pairs of panes taken off the node's group and freed, the node unregistered and
// released, two layout handles.
struct Board2bfda4 {
    ~Board2bfda4();

    void release_pane(Pane2bfda4*& pane, LayoutContext* context) {
        if (pane) {
            pane->unbind(context);
            reinterpret_cast<PaneGroup*>(node->group)->remove(pane);
            if (Pane2bfda4* p = pane) {
                p->~Pane2bfda4();
                table_free(p);
            }
        }
    }

    unsigned char pad0[0x10];
    LightEffectNode* node;       // +10
    unsigned char pad18[0x20];
    Pane2bfda4* front[17];       // +38
    void* pc0;                   // +c0
    Pane2bfda4* back[17];        // +c8
    HandleBody handle150;        // +150
    void* p160;                  // +160
    HandleBody handle168;        // +168
};

Board2bfda4::~Board2bfda4() {
    LayoutContext* context = layout_context();
    for (int i = 0; i < 17; i++) {
        if (front[i] && back[i]) {
            release_pane(front[i], context);
            release_pane(back[i], context);
            front[i] = nullptr;
            back[i] = nullptr;
        }
    }
    if (node) {
        EffectManager* manager = gEffectManager;
        void* root = gResourceLoader->layout->root;
        manager->unregister(manager->registry, 0x4217);
        node->detach(root);
        node->release();
        manager->children.remove(node);
        node = nullptr;
    }
}

// 3a43c4's class and the 3a57fc items, their destructors out of line.
struct Class3a43c4 {
    ~Class3a43c4();              // 0x71003a43c4
    unsigned char data[0x34a0];
};
struct Item3a57fc {
    ~Item3a57fc();               // 0x71003a57fc
    unsigned char data[0x1160];
};

// 0x71003a7668 (D2): vtable GOT 0x7100c2b330; a node released as on a node page, then nine items, nine node holders
// (0x71003a4f90), nine 3a43c4 pages, nine plain pages in an array and eight more.
class Screen3a7668 : public ScreenBase3ab2bc {
public:
    void anchor();
    ~Screen3a7668();

    Base3aab84 page_c0;          // +c0
    Base3aab84 page_23e0;        // +23e0
    Base3aab84 page_4700;        // +4700
    Base3aab84 page_6a20;        // +6a20
    Base3aab84 page_8d40;        // +8d40
    Base3aab84 page_b060;        // +b060
    Base3aab84 page_d380;        // +d380
    Base3aab84 page_f6a0;        // +f6a0
    Base3aab84 pages[9];         // +119c0
    unsigned char pad255e0[0x10];
    Class3a43c4 lists[9];        // +255f0
    NodeHolder3a4f90 holders[9]; // +42f90
    unsigned char pad4cb60[0x50];
    LightEffectNode* node;       // +4cbb0
    unsigned char pad4cbb8[0x128];
    Item3a57fc items[9];         // +4cce0
};

Screen3a7668::~Screen3a7668() {
    if (page_ids()) {
        EffectManager* manager = gEffectManager;
        if (node) {
            void* root = gResourceLoader->layout->root;
            manager->unregister(manager->registry, 0x4202);
            node->detach(root);
            node->release();
            manager->children.remove(node);
            node = nullptr;
        }
    } else {
        EffectManager* manager = gEffectManager;
        if (node) {
            node->detach(gResourceLoader->layout->root);
            node->release();
            manager->nodes.remove(node);
            node = nullptr;
        }
    }
}