// Destructors on 3a43c4's base where that base's destructor stays out of line (third session): a node base with
// page arrays, and the screen holding four such sets (and the screen's constructor). Names are descriptive
// placeholders. Status: matching/README.md.

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

class Screen34840c;

// 0x71003485e8 (D2): vtable GOT 0x7100c2af38; eleven pages and eleven slots on the node base, as arrays (their
// begin addresses are computed once, before the unrolled loops).
class Pages3485e8 : public NodeBase348 {
public:
    Pages3485e8(Screen34840c* owner, int index);                            // 0x7100342c60
    void anchor();
    ~Pages3485e8();
    void prepare();                                                         // 0x710034305c

    Base3aab84 pages[11];        // +110
    Slot349480 slots[11];        // +18370
    unsigned char pad30e10[0xb0];
};

Pages3485e8::~Pages3485e8() {}

struct Part5d27b4 {
    Part5d27b4();                // 0x71005d2744
    ~Part5d27b4();               // 0x71005d27b4
    unsigned char data[0x10];
};

class Basec719c {
public:
    Basec719c();                 // 0x71003c7188
    virtual ~Basec719c();        // 0x71003c719c
};

// The node base with four pages (vtable GOT 0x7100c2af30; out of line at 0x71003487c0), inline here.
class Pages3487c0 : public NodeBase348 {
public:
    explicit Pages3487c0(Screen34840c* owner);                              // 0x7100342498
    void anchor();

    Base3aab84 pages[4];         // +110
};

// The layout handle (vtable GOT 0x7100c22f00): its destructor releases it through the context.
struct LayoutContext;
inline LayoutContext* layout_context() {
    return gResourceLoader ? reinterpret_cast<LayoutContext*>(gResourceLoader->layout->root) : nullptr;
}

// Its id and two counters are a base, stored before the vtable pointer.
struct HandleState {
    HandleState() : id(-1), a(0), b(0) {}

    long id;                     // +08
    short a;                     // +10
    short b;                     // +12
};

class HandleBody : public HandleState {
public:
    virtual void anchor();
    virtual ~HandleBody() { release(layout_context()); }
    virtual void release(LayoutContext* context);
};

struct IconRect {
    unsigned short v[8];
};
class IconTable;
struct IconSource {
    IconTable* table;
};
// Reached through the GOT slot at 0x7100c22bf0.
extern IconSource* gIconSource;
// Reached through the GOT slot at 0x7100c22c38.
extern const IconRect gIconRects[];
void apply_icon(EffectGroup* pane, HandleBody* handle, IconTable* table, const IconRect* rect); // 0x71001f7fe4

struct IdRow201e5c;
IdRow201e5c* load_global_2017c0();                                         // 0x71002017c0
int row_id_201e5c(IdRow201e5c* rows, int row);                             // 0x7100201e5c

struct Gauge202130 {
    void refresh();                                                         // 0x7100202130
    unsigned char data[0x40];
};

class PanelNode : public LightEffectNode {
public:
    void* create_animation_3770(const char* name, bool loop);               // 0x71001e3770
};

extern const char gLayout347fe4[] __attribute__((visibility("hidden")));     // 0x71007da6b2
extern const char gAnimIn347fe4[] __attribute__((visibility("hidden")));     // 0x710073fffb
extern const char gAnimLoop347fe4[] __attribute__((visibility("hidden")));   // 0x710074056c
extern const char gPane347fe4[] __attribute__((visibility("hidden")));       // 0x71007da6c3

// 0x710034840c (D2): vtable GOT 0x7100c2af60; a node unregistered and released, four page sets (separate members,
// each address computed at its call) and a smaller one, a layout handle. The manager is read before the node test,
// so its GOT address stays in a register for the smaller set's release.
class Screen34840c : public Basec719c {
public:
    Screen34840c();
    virtual void anchor();
    ~Screen34840c();

    unsigned char pad8[0x20];
    void* p28;                   // +28
    void* p30;                   // +30
    void* p38;                   // +38
    Part5d27b4 m40;              // +40
    unsigned char pad50[0x100];
    Pages3487c0 small;           // +150
    unsigned char pad8ee0[0x18];
    Pages3485e8 set_8ef8;        // +8ef8
    Pages3485e8 set_39db8;       // +39db8
    Pages3485e8 set_6ac78;       // +6ac78
    Pages3485e8 set_9bb38;       // +9bb38
    PanelNode* node;             // +cc9f8
    void* anim_cca00;            // +cca00
    void* anim_cca08;            // +cca08
    EffectGroup* pcca10;         // +cca10
    HandleBody handle;           // +cca18
    int icca30;                  // +cca30
    Gauge202130 gauge;           // +cca34
    int icca74;                  // +cca74
    unsigned int counts[4];      // +cca78
    int rows[4][11];             // +cca88
    // Values per mode, read by the mode selector; volatile, so their six stores stay apart as in the original.
    volatile int iccb38;         // +ccb38
    volatile int iccb3c;         // +ccb3c
    volatile int iccb40;         // +ccb40
    volatile int iccb44;         // +ccb44
    volatile int iccb48;         // +ccb48
    volatile int iccb4c;         // +ccb4c
    bool bccb50;                 // +ccb50
    bool bccb51;                 // +ccb51
    bool bccb52;                 // +ccb52
    bool bccb53;                 // +ccb53
};

// 0x7100347fe4: the node and its animations, a pane with an icon on the layout handle, the four tables of ids per
// mode reset and filled from the id rows, the four sets prepared. The four flags at +ccb50 are cleared in one store.
Screen34840c::Screen34840c()
    : p28(nullptr), p30(nullptr), p38(nullptr), small(this), set_8ef8(this, 1), set_39db8(this, 2), set_6ac78(this, 3),
      set_9bb38(this, 4), node(nullptr), pcca10(nullptr), icca30(6), icca74(0), bccb50(false), bccb51(false),
      bccb52(false), bccb53(false) {
    for (int k = 0; k < 4; k++) {
        counts[k] = 0;
        for (int j = 0; j < 11; j++)
            rows[k][j] = -1;
    }
    gEffectManager->create_node(reinterpret_cast<LightEffectNode**>(&node), 0x4204, gLayout347fe4);
    anim_cca00 = node->create_animation_3770(gAnimIn347fe4, false);
    anim_cca08 = node->create_animation_3770(gAnimLoop347fe4, false);
    pcca10 = node->group->find(gPane347fe4, 1);
    apply_icon(pcca10, &handle, gIconSource->table, &gIconRects[0x1c]);
    iccb38 = -1;
    iccb3c = 0;
    iccb40 = 0;
    iccb44 = 0x13;
    iccb48 = 0x14;
    iccb4c = -1;
    for (int i = 0; i < 0x21; i++) {
        int k = row_id_201e5c(load_global_2017c0(), i);
        if (static_cast<unsigned int>(k) < 4) {
            rows[k][counts[k]] = i;
            counts[k]++;
        }
    }
    set_8ef8.prepare();
    set_39db8.prepare();
    set_6ac78.prepare();
    set_9bb38.prepare();
    gauge.refresh();
}

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
    unsigned char pad66e0[0xb20];
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
