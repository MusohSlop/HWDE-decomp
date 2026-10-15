// Destructors on 3a43c4's base where that base's destructor stays out of line (third session): a node base with
// page arrays, and the screen holding four such sets. Names are descriptive placeholders. Status: matching/README.md.

#include "event/demo_effects.h"

// 3a43c4's base (vtable GOT 0x7100c2b2b0), its destructor out of line (0x71003aab84).
class Base3aab84 {
public:
    virtual ~Base3aab84();
    unsigned char pad8[0x2318];
};

struct Slot349480 {
    ~Slot349480();               // 0x7100349480
    unsigned char data[0x23e0];
};

// A base with a light effect node (vtable GOT 0x7100c2af28), its destructor inline.
class NodeBase348 {
public:
    virtual void anchor();
    virtual ~NodeBase348() {
        if (node) {
            EffectManager* manager = gEffectManager;
            node->detach(gResourceLoader->layout->root);
            node->release();
            manager->nodes.remove(node);
            node = nullptr;
        }
        ie0 = 0;
        pf0 = nullptr;
        pf8 = nullptr;
        p100 = nullptr;
    }

    unsigned char pad8[0xd8];
    int ie0;                     // +e0
    LightEffectNode* node;       // +e8
    void* pf0;                   // +f0
    void* pf8;                   // +f8
    void* p100;                  // +100
    unsigned char pad108[0x8];
};

// 0x71003485e8 (D2): vtable GOT 0x7100c2af38; eleven pages and eleven slots on the node base, as arrays (their
// begin addresses are computed once, before the unrolled loops).
class Pages3485e8 : public NodeBase348 {
public:
    void anchor();
    ~Pages3485e8();

    Base3aab84 pages[11];        // +110
    Slot349480 slots[11];        // +18370
    unsigned char pad30e10[0xb0];
};

Pages3485e8::~Pages3485e8() {}

struct Part5d27b4 { ~Part5d27b4(); unsigned char data[0x10]; };   // 0x71005d27b4

class Basec719c {
public:
    virtual ~Basec719c();        // 0x71003c719c
};

// The node base with four pages (vtable GOT 0x7100c2af30; out of line at 0x71003487c0), inline here.
class Pages3487c0 : public NodeBase348 {
public:
    void anchor();

    Base3aab84 pages[4];         // +110
};

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

// 0x710034840c (D2): vtable GOT 0x7100c2af60; a node unregistered and released, four page sets (separate members,
// each address computed at its call) and a smaller one, a layout handle. The manager is read before the node test,
// so its GOT address stays in a register for the smaller set's release.
class Screen34840c : public Basec719c {
public:
    virtual void anchor();
    ~Screen34840c();

    unsigned char pad8[0x38];
    Part5d27b4 m40;              // +40
    unsigned char pad50[0x100];
    Pages3487c0 small;           // +150
    unsigned char pad8ee0[0x18];
    Pages3485e8 set_8ef8;        // +8ef8
    Pages3485e8 set_39db8;       // +39db8
    Pages3485e8 set_6ac78;       // +6ac78
    Pages3485e8 set_9bb38;       // +9bb38
    LightEffectNode* node;       // +cc9f8
    unsigned char padcca00[0x10];
    void* pcca10;                // +cca10
    HandleBody handle;           // +cca18
};

Screen34840c::~Screen34840c() {
    EffectManager* manager = gEffectManager;
    if (node) {
        void* root = gResourceLoader->layout->root;
        manager->unregister(manager->registry, 0x4204);
        node->detach(root);
        node->release();
        manager->children.remove(node);
        node = nullptr;
    }
    pcca10 = nullptr;
}

struct ObjHeap;
// Reached through the GOT slot at 0x7100c22a00.
extern ObjHeap* gObjHeap;
void heap_note(ObjHeap* heap, void* at, int n);              // 0x71002925c8

struct Player37cd6c {
    ~Player37cd6c();             // 0x710037f568
    void stop();                 // 0x710037cd6c
    unsigned char data[0x30];
};

// A card's base (vtable GOT 0x7100c2b158): notes its block on the object heap.
class CardBase38fc44 {
public:
    virtual void anchor();
    virtual ~CardBase38fc44() { heap_note(gObjHeap, s8, n2264); }

    unsigned char s8[0x225c];    // +8
    int n2264;                   // +2264
    unsigned char pad2268[0x4460];
};

// A card (vtable GOT 0x7100c2b198) with a layout handle.
class Card38fc44 : public CardBase38fc44 {
public:
    void anchor();

    HandleBody handle;           // +66c8
    unsigned char pad66d8[0xb28];
};

// The deck's base (vtable GOT 0x7100c2b168): stops its player.
class DeckBase38fc44 {
public:
    virtual void anchor();
    virtual ~DeckBase38fc44() { player.stop(); }

    unsigned char pad8[0x220];
    Player37cd6c player;         // +228
};

// The deck (vtable GOT 0x7100c2b190): 62 cards.
class Deck38fc44 : public DeckBase38fc44 {
public:
    void anchor();

    Card38fc44 cards[62];        // +258
};

// 0x710038fc44 (D2): vtable GOT 0x7100c2b188 (constructed at 0x710038ecfc); its deck of 62 cards and two parts.
class Table38fc44 : public Basec719c {
public:
    virtual void anchor();
    ~Table38fc44();

    unsigned char pad8[0x68];
    Deck38fc44 deck;             // +70
    unsigned char pad1b9ec8[0x18];
    Part5d27b4 part_1b9ee0;      // +1b9ee0
    unsigned char pad1b9ef0[0x100];
    Part5d27b4 part_1b9ff0;      // +1b9ff0
};

Table38fc44::~Table38fc44() {}
