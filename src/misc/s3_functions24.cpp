// Page and screen constructors written by hand (third session): nodes created by page ids, animations and panes
// looked up through the effect manager's API. Names are descriptive placeholders. Status: matching/README.md.

#include "event/demo_effects.h"
#include "event/layout_panes.h"

void* load_global_334a04();                                 // 0x7100334a04
struct PageOverride;
// Reached through the GOT slot at 0x7100c22da8.
extern PageOverride* gPageOverride;

inline bool page_ids() { return !load_global_334a04() && !gPageOverride; }

extern const char gLayout39ec78[] __attribute__((visibility("hidden")));     // 0x71007db10c
extern const char gTitle39ec78[] __attribute__((visibility("hidden")));      // 0x71007d6079
extern const char gAnimIn39ec78[] __attribute__((visibility("hidden")));     // 0x710073fffb
extern const char gAnimLoop39ec78[] __attribute__((visibility("hidden")));   // 0x710074056c
extern const char gAnimSel39ec78[] __attribute__((visibility("hidden")));    // 0x71007db16e
extern const char gPaneA39ec78[] __attribute__((visibility("hidden")));      // 0x71007db11f
extern const char gPaneB39ec78[] __attribute__((visibility("hidden")));      // 0x71007db128
extern const char gPaneC39ec78[] __attribute__((visibility("hidden")));      // 0x71007db138
extern const char gPaneD39ec78[] __attribute__((visibility("hidden")));      // 0x71007db178
extern const char gAnimOut39ec78[] __attribute__((visibility("hidden")));    // 0x71007d6062
extern const char gAnimWait39ec78[] __attribute__((visibility("hidden")));   // 0x710074053d
extern const char gAnimOn39ec78[] __attribute__((visibility("hidden")));     // 0x71007d5b89
extern const char gAnimOff39ec78[] __attribute__((visibility("hidden")));    // 0x71007d5b94
extern const char gPaneE39ec78[] __attribute__((visibility("hidden")));      // 0x71007db187
extern const char gLayout3940c4[] __attribute__((visibility("hidden")));     // 0x71007db0d6
extern const char gAnimA3940c4[] __attribute__((visibility("hidden")));      // 0x71007d5b6c
extern const char gAnimB3940c4[] __attribute__((visibility("hidden")));      // 0x71007d5b72
extern const char gPaneA3940c4[] __attribute__((visibility("hidden")));      // 0x71007db0ea
extern const char gPaneB3940c4[] __attribute__((visibility("hidden")));      // 0x71007d830f
extern const char gPaneC3940c4[] __attribute__((visibility("hidden")));      // 0x71007db0af
extern const char gLayout3a4034[] __attribute__((visibility("hidden")));     // 0x71007db195
extern const char gAnimA3a4034[] __attribute__((visibility("hidden")));      // 0x7100740004
extern const char gAnimB3a4034[] __attribute__((visibility("hidden")));      // 0x71007db1a6
extern const char gPaneA3a4034[] __attribute__((visibility("hidden")));      // 0x71007db1b1
extern const char gPaneB3a4034[] __attribute__((visibility("hidden")));      // 0x71007db1ba

struct LayoutContext;
inline LayoutContext* layout_context() {
    return gResourceLoader ? reinterpret_cast<LayoutContext*>(gResourceLoader->layout->root) : nullptr;
}

// A layout handle's id and two counters: a base of the handle, so they are stored before its vtable pointer and the
// two zero halfwords stay apart.
struct HandleData {
    HandleData() : id(-1), a(0), b(0) {}

    long id;                     // +08
    unsigned short a;            // +10
    unsigned short b;            // +12
};

// A layout handle (vtable GOT 0x7100c22f00).
class HandleBody : public HandleData {
public:
    virtual void anchor();
    virtual ~HandleBody() { release(layout_context()); }
    virtual void release(LayoutContext* context);
};

struct LayoutFrame {
    LayoutFrame();                                                          // 0x71001f0140
    unsigned char pad0[8];
    int flags;                   // +08: bit 7 dirty
    unsigned char padc[0x7c];
};

class AnimPlayer {
public:
    void set_speed(float speed);                                            // 0x71001e4570
};

struct AnimHandle {
    unsigned char pad0[0x18];
    AnimPlayer* player;          // +18
};

class PanelNode : public LightEffectNode {
public:
    AnimHandle* create_animation_3770(const char* name, bool loop);         // 0x71001e3770
};

// 3a43c4's base (vtable GOT 0x7100c2b2b0), constructed out of line.
class Base3aab84 {
public:
    Base3aab84(int id, int alt_id, const char* layout, const char* title, int mode);   // 0x710039d3fc
    virtual ~Base3aab84();

    PanelNode* node;             // +08
    AnimHandle* anim10;          // +10
    AnimHandle* anim18;          // +18
    void* p20;                   // +20
    AnimHandle* anim28;          // +28
    AnimHandle* anim30;          // +30
    unsigned char pad38[0x22c0];
    int count22f8;               // +22f8
    int id22fc;                  // +22fc
    int id2300;                  // +2300
    unsigned char pad2304[0x18];
    unsigned char active;        // +231c
};

// 0x710039ec78: a node page (vtable GOT 0x7100c2b2c8; destroyed at 0x710039ef38).
class Page39ec78 : public Base3aab84 {
public:
    Page39ec78();
    void v10();
    ~Page39ec78();

    LightEffectNode* page_node;  // +2320
    AnimHandle* anim2328;        // +2328
    AnimHandle* anim2330;        // +2330
    AnimHandle* anim2338;        // +2338
    AnimHandle* anim2340;        // +2340
    AnimHandle* anim2348;        // +2348
    unsigned char pad2350[0x10];
    EffectGroup* group2360;      // +2360
    EffectGroup* group2368;      // +2368
    bool flag2370;               // +2370
    int i2374;                   // +2374
    int i2378;                   // +2378
    int i237c;                   // +237c
};

Page39ec78::Page39ec78()
    : Base3aab84(0x4202, 0x41f3, gLayout39ec78, gTitle39ec78, 0), page_node(nullptr), i2374(0), i2378(15), i237c(0) {
    PanelNode* n = node;
    if (page_ids()) {
        gEffectManager->create_node(&page_node, 0x4202, gLayout39ec78);
        gEffectManager->sync();
    } else {
        gEffectManager->create_node(&page_node, 0x41f3, gLayout39ec78);
        gEffectManager->flush();
    }
    anim2328 = n->create_animation_3770(gAnimIn39ec78, false);
    anim2330 = n->create_animation_3770(gAnimLoop39ec78, false);
    anim2338 = n->create_animation_3770(gAnimSel39ec78, false);
    anim2338->player->set_speed(n->group->scale48);
    n->group->find(gPaneA39ec78, 1)->flags58 &= ~1;
    n->group->find(gPaneB39ec78, 1)->flags58 &= ~1;
    n->group->find(gPaneC39ec78, 1)->flags58 &= ~1;
    n->group->find(gPaneD39ec78, 1)->flags58 &= ~1;
    gEffectManager->flush();
    anim10 = node->create_animation_3770(gAnimIn39ec78, false);
    anim18 = node->create_animation_3770(gAnimOut39ec78, false);
    anim28 = node->create_animation_3770(gAnimWait39ec78, false);
    anim30 = node->create_animation_3770(gAnimLoop39ec78, false);
    anim2340 = n->create_animation_3770(gAnimOn39ec78, true);
    anim2348 = n->create_animation_3770(gAnimOff39ec78, true);
    group2368 = n->group->find(gPaneE39ec78, 1);
    group2360 = n->group->find(gPaneD39ec78, 1);
    count22f8 = 15;
    flag2370 = false;
}

// 0x71003a4034: a node page (vtable GOT 0x7100c2b328) with five animations, two panes, a text pane added to the
// first, a layout handle and 32 layout frames. The flag at +3488 is cleared before the pointer next to it.
class Page3a4034 : public Base3aab84 {
public:
    Page3a4034();
    ~Page3a4034();

    PanelNode* page_node;        // +2320
    AnimHandle* anim2328;        // +2328
    AnimHandle* anim2330;        // +2330
    AnimHandle* anim2338;        // +2338
    AnimHandle* anim2340;        // +2340
    AnimHandle* anim2348;        // +2348
    EffectGroup* group2350;      // +2350
    EffectGroup* group2358;      // +2358
    PanelPane* pane;             // +2360
    HandleBody handle;           // +2368
    LayoutFrame frames[32];      // +2380
    void* p3480;                 // +3480
    bool b3488;                  // +3488
    int i348c;                   // +348c
    int i3490;                   // +3490
    void* p3498;                 // +3498
};

Page3a4034::Page3a4034()
    : Base3aab84(0x4202, 0x41f3, gLayout39ec78, gTitle39ec78, 0), page_node(nullptr) {
    b3488 = false;
    p3480 = nullptr;
    i348c = 0x13;
    i3490 = -1;
    p3498 = nullptr;
    if (page_ids()) {
        gEffectManager->create_node(reinterpret_cast<LightEffectNode**>(&page_node), 0x4202, gLayout3a4034);
        gEffectManager->sync();
    } else {
        gEffectManager->create_node(reinterpret_cast<LightEffectNode**>(&page_node), 0x41f3, gLayout3a4034);
        gEffectManager->flush();
    }
    anim2328 = page_node->create_animation_3770(gAnimIn39ec78, false);
    anim2330 = page_node->create_animation_3770(gAnimOut39ec78, false);
    anim2338 = page_node->create_animation_3770(gAnimA3a4034, false);
    anim2340 = page_node->create_animation_3770(gAnimWait39ec78, false);
    anim2348 = page_node->create_animation_3770(gAnimB3a4034, false);
    group2350 = page_node->group->find(gPaneA3a4034, 1);
    group2358 = page_node->group->find(gPaneB3a4034, 1);
    count22f8 = 0x12;
    pane = new PanelPane;
    group2350->add(pane);
}
// 3940c4's base, constructed out of line.
class Base38c480 {
public:
    Base38c480(int id, const char* layout, void* owner);                    // 0x710038c480
    virtual ~Base38c480();
    virtual void select(int index);                                         // +10
    void set_animation(int slot, const char* name, int mode);               // 0x710038ccb0

    PanelNode* node;             // +08
    AnimHandle* anims[5];        // +10
    unsigned char pad38[0x2218];
    const char* title;           // +2250
    const char* sub;             // +2258
    int value2260;               // +2260
    unsigned char pad2264[4];
};

// 0x71003940c4: a page (vtable GOT 0x7100c2b200) with four animations at its group's speed, two more set on the
// base, three panes and a layout handle.
class Page3940c4 : public Base38c480 {
public:
    Page3940c4();
    ~Page3940c4();

    AnimHandle* anim2268;        // +2268
    AnimHandle* anim2270;        // +2270
    AnimHandle* anim2278;        // +2278
    AnimHandle* anim2280;        // +2280
    int i2288;                   // +2288
    EffectGroup* group2290;      // +2290
    EffectGroup* group2298;      // +2298
    EffectGroup* group22a0;      // +22a0
    HandleBody handle;           // +22a8
    LayoutFrame frame22c0;       // +22c0
    LayoutFrame frame2348;       // +2348
    LayoutFrame frame23d0;       // +23d0
};

Page3940c4::Page3940c4()
    : Base38c480(0x41f6, gLayout3940c4, nullptr), i2288(0), group2290(nullptr), group2298(nullptr), group22a0(nullptr) {
    gEffectManager->sync();
    anim2268 = node->create_animation_3770(gAnimA3940c4, false);
    if (anim2268)
        anim2268->player->set_speed(node->group->scale48);
    anim2270 = node->create_animation_3770(gAnimB3940c4, false);
    if (anim2270)
        anim2270->player->set_speed(node->group->scale48);
    anim2278 = node->create_animation_3770(gAnimOn39ec78, false);
    if (anim2278)
        anim2278->player->set_speed(node->group->scale48);
    anim2280 = node->create_animation_3770(gAnimOff39ec78, false);
    if (anim2280)
        anim2280->player->set_speed(node->group->scale48);
    set_animation(0, gAnimIn39ec78, 0);
    set_animation(4, gAnimLoop39ec78, 0);
    group2290 = node->group->find(gPaneA3940c4, 1);
    group2298 = node->group->find(gPaneB3940c4, 1);
    EffectGroup* group = node->group->find(gPaneC3940c4, 1);
    group22a0 = group;
    group->offset30 = group->offset30 - 4.0f;
    group->flags58 |= 0x10;
}
extern "C" void* memset(void*, int, unsigned long);

const char* message_text(int id);                                           // 0x7100217d64
const char* item_name(int item);                                            // 0x7100217d9c
const char* text_217dd8(int id);                                            // 0x7100217dd8

extern const char kMenuPartsLayout[] __attribute__((visibility("hidden")));   // 0x71007d6051
extern const char kLoop0Anim[] __attribute__((visibility("hidden")));         // 0x71007d6069
extern const char kSelect0Anim[] __attribute__((visibility("hidden")));       // 0x71007d6070

// A cursor sub-object of the menus (0x30 bytes).
class MenuCursor {
public:
    MenuCursor();                                                           // 0x710037f550
    void init();                                                            // 0x710037cc88

    unsigned char data[0x30];
};

// The deck's base (vtable GOT 0x7100c2b168), inline here: its owner, the listed panels and a cursor.
class DeckBase38dca4 {
public:
    explicit DeckBase38dca4(void* owner_) : owner(owner_), i210(0), count(0), i218(6), i21c(0), i220(0), b224(false) {
        memset(list, 0, sizeof(list));
        cursor.init();
    }
    virtual ~DeckBase38dca4();

    template <class T> void add(T* panel) { list[count++] = panel; }

    void* owner;                 // +08
    void* list[64];              // +10
    int i210;                    // +210
    int count;                   // +214
    int i218;                    // +218
    int i21c;                    // +21c
    int i220;                    // +220
    bool b224;                   // +224
    unsigned char pad225[3];
    MenuCursor cursor;           // +228
};

// A panel of the deck menus (vtable GOT 0x7100c2b180): the menu parts layout and its five animations.
class DeckPanel : public Base38c480 {
public:
    DeckPanel() : Base38c480(0x41ea, kMenuPartsLayout, const_cast<char*>(gTitle39ec78)) {
        gEffectManager->sync();
        anims[0] = node->create_animation_3770(gAnimIn39ec78, false);
        anims[1] = node->create_animation_3770(gAnimOut39ec78, false);
        anims[2] = node->create_animation_3770(kLoop0Anim, false);
        anims[3] = node->create_animation_3770(kSelect0Anim, false);
        anims[4] = node->create_animation_3770(gAnimLoop39ec78, false);
        value2260 = 0x10;
    }
    virtual void v18();       // declared, not defined: the vtable stays external (GOT 0x7100c2b180)
};

// 0x710038dca4: a deck menu of six panels (vtable GOT 0x7100c2b178), listed with the last one second.
class DeckMenu38dca4 : public DeckBase38dca4 {
public:
    explicit DeckMenu38dca4(void* owner);
    virtual ~DeckMenu38dca4();

    DeckPanel panel_a;           // +258
    DeckPanel panel_b;           // +24c0
    DeckPanel panel_c;           // +4728
    DeckPanel panel_d;           // +6990
    DeckPanel panel_e;           // +8bf8
    DeckPanel panel_f;           // +ae60
    bool flagd0c8;               // +d0c8
};

DeckMenu38dca4::DeckMenu38dca4(void* owner_) : DeckBase38dca4(owner_), flagd0c8(false) {
    panel_a.select(0);
    panel_a.title = message_text(0x66);
    panel_a.sub = text_217dd8(0x15);
    add(&panel_a);
    panel_f.select(1);
    panel_f.title = message_text(0x138);
    panel_f.sub = item_name(0x18e);
    add(&panel_f);
    panel_b.select(2);
    panel_b.title = message_text(0x67);
    panel_b.sub = text_217dd8(0x16);
    add(&panel_b);
    panel_c.select(3);
    panel_c.title = message_text(0x68);
    panel_c.sub = text_217dd8(0x17);
    add(&panel_c);
    panel_d.select(4);
    panel_d.title = message_text(0x8b);
    panel_d.sub = text_217dd8(0x18);
    add(&panel_d);
    panel_e.select(5);
    panel_e.title = message_text(0x11);
    panel_e.sub = item_name(0x158);
    add(&panel_e);
}