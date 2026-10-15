// Constructors and destructors on 3a43c4's base where that base's destructor stays out of line (third session): a
// node base with page arrays, and the screen holding four such sets. Names are descriptive placeholders. Status:
// matching/README.md.

#include "event/demo_effects.h"

// 3a43c4's base (vtable GOT 0x7100c2b2b0), its destructor out of line (0x71003aab84).
class Base3aab84 {
public:
    virtual ~Base3aab84();
    unsigned char pad8[0x2318];
};

struct TrackVec2 {
    float x, y;
};

static inline TrackVec2 make_vec2(float x, float y) {
    TrackVec2 v;
    v.x = x;
    v.y = y;
    return v;
}

// A page on that base, constructed out of line; its destructor is the base's.
class Page39e154 : public Base3aab84 {
public:
    explicit Page39e154(int mode = 0);                                      // 0x710039e154
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void v40();
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void v60();
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void v80();
    virtual void v88();
    virtual void v90();
    virtual void place(int slot, int mode);                                // +98
    void set_title(const char* text);                                       // 0x710039dfc4
    void set_text(const char* text);                                        // 0x710039dff0
};

const char* message_text(int id);                                          // 0x7100217d64
const char* item_name(int item);                                           // 0x7100217d9c
struct Unlocks {
    unsigned char flag_a();                                                 // 0x71002249a0
    unsigned char flag_b();                                                 // 0x71002249a8
};
Unlocks* get_unlocks();                                                     // 0x71002248a0
struct BitSet202df8;
BitSet202df8* fetch_204728();                                               // 0x7100204728
unsigned char has_bit_202df8(BitSet202df8* set, int id);                   // 0x7100202df8
struct IdRow201e20;
int row_id_201e20(IdRow201e20* rows, int row);                             // 0x7100201e20

struct Slot349480 {
    Slot349480();                // 0x7100341048
    ~Slot349480();               // 0x7100349480
    unsigned char data[0x23e0];
};

class Screen34840c;
class PanelNode;

// The node and what was looked up on it: value-initialized as one member, so its memset comes before the one
// MemCpyOpt makes of the four zero fields at +c8.
struct NodeLink {
    int ie0;                     // +00
    int ie4;                     // +04
    PanelNode* node;             // +08
    void* pf0;                   // +10
    EffectGroup* pf8;            // +18
    EffectGroup* p100;           // +20
};

class PanelNode : public LightEffectNode {
public:
    void* create_animation_3770(const char* name, bool loop);               // 0x71001e3770
};

extern const char gLayout348[] __attribute__((visibility("hidden")));        // 0x71007d878a
extern const char gAnim348[] __attribute__((visibility("hidden")));          // 0x71007d8905
extern const char gPaneA348[] __attribute__((visibility("hidden")));         // 0x71007d8916
extern const char gPaneB348[] __attribute__((visibility("hidden")));         // 0x7100740dcf

// A base with a light effect node (vtable GOT 0x7100c2af28), its constructor and destructor inline.
class NodeBase348 {
public:
    NodeBase348(Screen34840c* owner, int index)
        : owner(owner), ic8(0), count(0), pd0(nullptr), flag(false), link(), index(index), i10c(-1) {
        for (int i = 0; i < 22; i++)
            list[i] = nullptr;
        gEffectManager->create_node(reinterpret_cast<LightEffectNode**>(&link.node), 0x41e5, gLayout348);
        gEffectManager->flush();
        link.pf0 = link.node->create_animation_3770(gAnim348, true);
        link.pf8 = link.node->group->find(gPaneA348, 1);
        link.p100 = link.node->group->find(gPaneB348, 1);
    }
    virtual void anchor();
    virtual ~NodeBase348() {
        if (link.node) {
            EffectManager* manager = gEffectManager;
            link.node->detach(gResourceLoader->layout->root);
            link.node->release();
            manager->nodes.remove(link.node);
            link.node = nullptr;
        }
        link.ie0 = 0;
        link.pf0 = nullptr;
        link.pf8 = nullptr;
        link.p100 = nullptr;
    }

    Screen34840c* owner;         // +08
    unsigned char pad10[0x8];
    Base3aab84* list[22];        // +18
    int ic8;                     // +c8
    int count;                   // +cc
    void* pd0;                   // +d0
    bool flag;                   // +d8
    unsigned char pad_d9[7];
    NodeLink link;               // +e0
    int index;                   // +108
    int i10c;                    // +10c
};

// 0x71003485e8 (D2): vtable GOT 0x7100c2af38; eleven pages and eleven slots on the node base, as arrays (their
// begin addresses are computed once, before the unrolled loops).
class Pages3485e8 : public NodeBase348 {
public:
    Pages3485e8(Screen34840c* owner, int index);                            // 0x7100342c60
    void anchor();
    ~Pages3485e8();
    void prepare();                                                         // 0x710034305c

    bool is_main() const { return mode == 1 || mode == 2; }

    Page39e154 pages[11];        // +110
    Slot349480 slots[11];        // +18370
    int ids[11];                 // +30e10
    int i30e3c;                  // +30e3c
    int mode;                    // +30e40
    bool b30e44;                 // +30e44
    bool b30e45;                 // +30e45
    bool b30e46;                 // +30e46
    bool shown[11];              // +30e47
    bool cells[11][9];           // +30e52
    bool hidden[11];             // +30eb5
};

// 0x7100342c60: the node base (its node created with id 0x41e5), eleven pages and slots, the tables per page set
// from the mode (reloaded after each byte store), the node's group moved and the first pane resized.
Pages3485e8::Pages3485e8(Screen34840c* owner, int index)
    : NodeBase348(owner, index), i30e3c(0), mode(index), b30e44(false) {
    for (int i = 0; i < 11; i++) {
        ids[i] = -1;
        hidden[i] = !is_main();
        shown[i] = is_main();
        for (int j = 0; j < 9; j++)
            cells[i][j] = is_main();
    }
    b30e45 = false;
    b30e46 = false;
    EffectGroup* group = link.node->group;
    group->offset30 = 22.0f;
    *reinterpret_cast<TrackVec2*>(&group->offset34) = make_vec2(303.0f, 0.0f);
    group->flags58 |= 0x10;
    EffectGroup* pane = link.pf8;
    pane->size50 = 621.0f;
    pane->flags58 |= 0x10;
}

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
    explicit Pages3487c0(Screen34840c* owner);
    void anchor();

    void add(int page, int slot, int title) {
        Page39e154* p = &pages[page];
        p->place(slot, 1);
        p->set_title(message_text(title));
        p->set_text(item_name(0x13a));
        list[count++] = p;
        ids[slot] = page;
    }

    Page39e154 pages[4];         // +110
    int ids[4];                  // +8d90
    int i8da0;                   // +8da0
    bool b8da4;                  // +8da4
};

struct IdRow201e5c;
IdRow201e5c* load_global_2017c0();                                         // 0x71002017c0

// 0x7100342498: the node base and four pages; the first page always listed, the second if unlocked, the third if
// unlocked and the fourth after it if its row's bit is set.
Pages3487c0::Pages3487c0(Screen34840c* owner) : NodeBase348(owner, 0), i8da0(4), b8da4(false) {
    int n = 0;
    add(0, n++, 0xc6);
    if (get_unlocks()->flag_a())
        add(1, n++, 0xc7);
    if (get_unlocks()->flag_b()) {
        add(2, n++, 0xc8);
        int id = row_id_201e20(reinterpret_cast<IdRow201e20*>(load_global_2017c0()), 0x17);
        if (has_bit_202df8(fetch_204728(), id))
            add(3, n++, 0xca);
    }
}

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

int row_id_201e5c(IdRow201e5c* rows, int row);                             // 0x7100201e5c

struct Gauge202130 {
    void refresh();                                                         // 0x7100202130
    unsigned char data[0x40];
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
