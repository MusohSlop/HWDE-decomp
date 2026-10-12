// Matching candidates for the demo panel system bodies 0x71002632cc-0x7100263cfc.
// Names are descriptive placeholders. Status: matching/README.md.

#include "event/demo_effects.h"
#include "event/demo_light_system.h"

inline void* operator new(unsigned long, void* where) noexcept { return where; }

class DefaultHeap {
public:
    void* allocate(unsigned int alignment, unsigned long size, int a, int b); // 0x710045c458
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

void hide_targets(TrackLightTarget* targets, unsigned int count);           // 0x71001f7530

static inline void* layout_root() {
    return gResourceLoader ? gResourceLoader->layout->root : nullptr;
}

struct HandleState {
    long id;                  // +08
    short a;                  // +10
    short b;                  // +12

    HandleState() : id(-1), a(0), b(0) {}
};

// Layout handle; its vtable lives in the effect manager unit (GOT 0x7100c22f00).
// The state base is constructed before the vtable pointer is stored.
class LayoutHandle : public HandleState {
public:
    // Inline virtual destructor (vtable slots 0 and 1).
    virtual ~LayoutHandle() { release(layout_root()); }
    virtual void v10();
    virtual void release(void* root); // +18
};static_assert(sizeof(LayoutHandle) == 0x18, "handle size");

struct PanelItem {
    EffectGroup* object;      // +00
    LayoutHandle handle;      // +08
};
static_assert(sizeof(PanelItem) == 0x20, "item size");

class PanelTargets {
public:
    PanelTargets();                                                         // 0x71002632cc
    ~PanelTargets();                                                        // 0x71002639a8

    LightEffectNode* node;            // +00
    unsigned char pad8[8];
    LightResource resource;           // +10
    PanelItem items[4];               // +120
    TrackLightTarget icons[24];       // +1a0
    TrackLightTarget cells[544];      // +e60
    TrackLightTarget marks[544];      // +12f60
    TrackLightTarget labels[24];      // +25060
    TrackLightTarget frames[24];      // +25d20
    EffectGroup* attribute_pos;       // +269e0
    PanelItem extras[4];              // +269e8
};
static_assert(sizeof(PanelTargets) == 0x26a68, "targets size");

PanelTargets::PanelTargets() {}

// Animation binding attached to a node's binding ring (0x58 bytes).
class AnimBindingBase {
public:
    static void* operator new(unsigned long size) noexcept;                 // 0x71005d4380
    AnimBindingBase();                                                      // 0x71005d026c
    virtual ~AnimBindingBase();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void bind(void* root, void* resources, void* block);  // +40

    ListLink link;            // +08
    unsigned char pad18[0x30];
};

class AnimBinding : public AnimBindingBase {
public:
    AnimBinding() : value48(nullptr), value50(0) {}
    ~AnimBinding();

    void* value48;            // +48
    int value50;              // +50
};
static_assert(sizeof(AnimBinding) == 0x58, "binding size");

struct AnimSource {
    void* data;               // +00
    void* block;              // +08
    unsigned char pad10[0x10];

    explicit AnimSource(void* resource);                                    // 0x71005cfac8
};

class PaneBase {
public:
    static void* operator new(unsigned long size) noexcept;                 // 0x71005d4380
    PaneBase();                                                             // 0x71005dc664
    virtual ~PaneBase();

    unsigned char pad8[0x53];
    unsigned char : 2;
    unsigned char align : 2;  // +5b bits 2-3
    unsigned char : 4;
    unsigned char pad5c[0x104];
};

// Text pane (0x180 bytes); vtable reached through the GOT slot at 0x7100c22f68.
class PanelPane : public PaneBase {
public:
    PanelPane() : value160(nullptr), value168(nullptr), value170(nullptr) {}
    ~PanelPane();

    void* value160;           // +160
    void* value168;           // +168
    void* value170;           // +170
    unsigned char pad178[8];
};
static_assert(sizeof(PanelPane) == 0x180, "pane size");

// Layout, pane and animation names, merged with other literals by the linker.
extern const char kInfoWindowLayout[] __attribute__((visibility("hidden")));    // 0x71007d5bf5
extern const char kAttributeLayout[] __attribute__((visibility("hidden")));     // 0x71007d5c0b
extern const char kAttributePos[] __attribute__((visibility("hidden")));        // 0x71007d5c20
extern const char kMissionText[] __attribute__((visibility("hidden")));         // 0x71007d5c6f
extern const char kNumberPos[] __attribute__((visibility("hidden")));           // 0x71007d5ca9
extern const char kAttributeIcon[] __attribute__((visibility("hidden")));       // 0x7100740d16
extern const char kAttributeAnim[] __attribute__((visibility("hidden")));       // 0x71007d5c33
extern const char kWallLayout[] __attribute__((visibility("hidden")));          // 0x71007d5c3d
extern const char kLoopAnim[] __attribute__((visibility("hidden")));            // 0x7100740004
extern const char kMissionFont[] __attribute__((visibility("hidden")));         // 0x71007d5c51
extern const char kLimitedText[] __attribute__((visibility("hidden")));         // 0x71007d5c5e
extern const char kAttributeFont[] __attribute__((visibility("hidden")));       // 0x71007d5c80
extern const char kResFont[] __attribute__((visibility("hidden")));             // 0x71007d5c8f
extern const char kNumberLayout[] __attribute__((visibility("hidden")));        // 0x71007d5ac9
extern const char kNumberPane[] __attribute__((visibility("hidden")));          // 0x710074129f
// Name tables, reached through the GOT slots at 0x7100c2a680-0x7100c2a6a8.
extern const char* const kArrowPanes[];
extern const char* const kLockPanes[];
extern const char* const kDummyPanes[];
extern const char* const kWindowAnims[];
extern const char* const kArrowLoops[];
// Step of the resource queue, reached through the GOT slot at 0x7100c21df0.
extern unsigned int gResourceQueueElapsedStep;
// Wall layout record (+26b68): node, loop animation and playback step.
struct WallLink {
    LightEffectNode* node;    // +00
    LayoutAnimation* loop;    // +08
    float step;               // +10

    void reset() {
        step = 0.0f;
        loop = nullptr;
        node = nullptr;
    }
};

struct PanelLink {
    void* first;              // +00
    void* second;             // +08
    int count;                // +10

    void reset() {
        count = 0;
        second = nullptr;
        first = nullptr;
    }
};

class DemoPanelSystem {
public:
    DemoPanelSystem();
    ~DemoPanelSystem() { finalize(); }
    void finalize();                                                        // 0x71002637fc
    void initialize();                                                      // 0x7100263d58
    void update();                                                          // 0x71002648dc
    void update_state();                                                    // 0x71002649cc
    void update_icons();                                                    // 0x7100264c28
    void update_cells();                                                    // 0x710026514c
    void update_marks();                                                    // 0x71002653dc

    void* value0;                     // +00
    unsigned char flag8;              // +08
    unsigned char flag9;              // +09
    unsigned char flag_a;             // +0a
    unsigned char padb;
    int value0c;                      // +0c
    int value10;                      // +10
    int value14;                      // +14
    unsigned char flag18;             // +18
    unsigned char pad19[3];
    int value1c;                      // +1c
    unsigned char flag20;             // +20
    unsigned char pad21[0xf];
    PanelTargets targets;             // +30
    EffectGroup* locks[4];            // +26a98
    LayoutAnimation* arrow_loops[4];  // +26ab8
    LayoutAnimation* window_anim;     // +26ad8
    PanelPane* panes[5];              // +26ae0
    PanelLink link26b08;              // +26b08
    EffectGroup* value26b20;          // +26b20
    AnimBinding* value26b28;          // +26b28
    EffectGroup* value26b30;          // +26b30
    AnimBinding* value26b38;          // +26b38
    LightEffectNode* node26b40;       // +26b40
    LightEffectNode* node26b48;       // +26b48
    LayoutAnimation* value26b50;      // +26b50
    AnimBinding* value26b58;          // +26b58
    EffectGroup* number_pane;         // +26b60
    LightEffectNode* wall_node;       // +26b68
    LayoutAnimation* wall_loop;       // +26b70
    float step;                       // +26b78
    unsigned char pad26b7c[4];
};
static_assert(sizeof(DemoPanelSystem) == 0x26b80, "system size");

class GameState {
public:
    unsigned char pad[0x1bb7c];
    unsigned int mode;        // +1bb7c
};

struct PlayerEntry {
    int value0;               // +00
    unsigned char pad4[0x14];
    int unit;                 // +18
    unsigned char pad1c[0x20];

    unsigned char valid();                                                  // 0x7100202164
};
static_assert(sizeof(PlayerEntry) == 0x3c, "entry size");

struct PlayerStage {
    union {
        unsigned short raw;
        struct {
            unsigned char kind;   // +0
            unsigned char step;   // +1
        };
    };
};

class Player {
public:
    unsigned char active(int id);                                           // 0x710026a90c

    unsigned int id;          // +00
    unsigned char pad4[0xb64];
    PlayerEntry entries[128]; // +b68
    unsigned char pad2968[0x164];
    PlayerStage stage;        // +2acc
    unsigned char pad2ace[0x16a];
};
static_assert(sizeof(Player) == 0x2c38, "player size");

class Game {
public:
    GameState* state();                                                     // 0x7100204c10

    unsigned char pad[0x2944];
    Player players[4];        // +2944
};
Game* get_game();                                                           // 0x7100204728

struct UnitRecord {
    short unit;               // +00
    unsigned char pad2[0x1de];
};

class Unit {
public:
    short width();                                                          // 0x710020da0c
    short height();                                                         // 0x710020dae0
    void set_flag(int flag, bool on);                                       // 0x710020dc10

    unsigned char pad[0xc];
    int value0c;              // +0c
};

class UnitDatabase {
public:
    Unit* unit(int id);                                                     // 0x710020eeb8

    unsigned char pad[0xdb608];
    UnitRecord records[1];    // +db608
};
UnitDatabase* get_unit_database();                                          // 0x710020ec80
// Frame delta, reached through the GOT slot at 0x7100c22a28.
extern float gFrameDelta;

// Reached through the GOT slot at 0x7100c2a678.
extern DemoPanelSystem* gDemoPanelSystem;

static inline void release_node(LightEffectNode*& node, int id) {
    if (node) {
        EffectManager* manager = gEffectManager;
        void* root = gResourceLoader->layout->root;
        manager->unregister(manager->registry, id);
        node->detach(root);
        node->release();
        manager->children.remove(node);
        node = nullptr;
    }
}

static inline void release_child(LightEffectNode*& node) {
    if (node) {
        EffectManager* manager = gEffectManager;
        void* root = gResourceLoader->layout->root;
        node->detach(root);
        node->release();
        manager->nodes.remove(node);
        node = nullptr;
    }
}

inline DemoPanelSystem::DemoPanelSystem() {
    targets.node = nullptr;
    for (int i = 0; i < 4; ++i)
        targets.items[i].object = nullptr;
    for (int i = 0; i < 4; ++i)
        targets.extras[i].object = nullptr;
    targets.attribute_pos = nullptr;
    hide_targets(targets.icons, 24);
    hide_targets(targets.cells, 544);
    hide_targets(targets.marks, 544);
    hide_targets(targets.labels, 24);
    hide_targets(targets.frames, 24);
    link26b08.reset();
    flag8 = 0;
    flag9 = 0;
    value0c = 0;
    value10 = 0;
    value14 = -1;
    value1c = -1;
    flag18 = 0;
    flag20 = 0;
    value0 = nullptr;
    // The three fields are cleared as one record.
    reinterpret_cast<WallLink*>(&wall_node)->reset();
    value26b50 = nullptr;
    node26b48 = nullptr;
    node26b40 = nullptr;
    value26b38 = nullptr;
    value26b30 = nullptr;
    value26b28 = nullptr;
    value26b20 = nullptr;
}

void DemoPanelSystem::finalize() {
    gEffectManager->flush();
    release_node(targets.node, 0x420d);
    release_child(node26b40);
    release_child(node26b48);
    release_node(wall_node, 0x420d);
    flag8 = 0;
    value0 = nullptr;
    wall_node = nullptr;
    wall_loop = nullptr;
}

PanelTargets::~PanelTargets() {}

void create_demo_panel_system() {
    if (!gDemoPanelSystem) {
        void* storage = get_default_heap()->allocate(0x10, sizeof(DemoPanelSystem), 1, 0);
        gDemoPanelSystem = new (storage) DemoPanelSystem;
    }
}

void destroy_demo_panel_system() {
    if (gDemoPanelSystem) {
        gDemoPanelSystem->finalize();
        DemoPanelSystem* system = gDemoPanelSystem;
        if (system) {
            system->~DemoPanelSystem();
            get_default_heap()->release(system, 1, 0);
        }
        gDemoPanelSystem = nullptr;
    }
}

// Binds the named animation of node to a new binding linked into the node's ring.
static inline AnimBinding* bind_animation(LightEffectNode* node, void* root, const char* name) {
    AnimSource source(node->find_animation(name));
    void* block = source.block;
    if (!block)
        return nullptr;
    AnimBinding* binding = new AnimBinding;
    if (binding) {
        node->bindings.link_before(&binding->link);
        binding->bind(root, node->resources, block);
    }
    return binding;
}

static inline void show_group(EffectGroup* group) {
    group->flags58 &= ~1;
}

static inline void move_group(EffectGroup* group, float y) {
    group->offset34 = y;
    group->flags58 |= 0x10;
}

void DemoPanelSystem::initialize() {
    if (flag8)
        return;
    gEffectManager->create_node(&targets.node, 0x420d, kInfoWindowLayout);
    gEffectManager->create_node(&node26b40, 0x41e5, kAttributeLayout);
    gEffectManager->sync();
    for (int i = 0; i < 4; ++i) {
        targets.extras[i].object = targets.node->group->find(kArrowPanes[i], 1);
        locks[i] = targets.node->group->find(kLockPanes[i], 1);
    }
    targets.attribute_pos = targets.node->group->find(kAttributePos, 1);
    for (int i = 0; i < 4; ++i)
        targets.items[i].object = targets.node->group->find(kDummyPanes[i], 1);
    flag_a = 0;
    if (get_game()->state()->mode >= 2) {
        flag_a = 1;
        move_group(targets.node->group->find(kMissionText, 1), -42.0f);
        move_group(targets.items[3].object, -46.0f);
        move_group(targets.node->group->find(kNumberPos, 1), -43.0f);
    }
    gEffectManager->flush();
    void* root = gResourceLoader->layout->root;

    value26b20 = node26b40->group->find(kAttributeIcon, 1)->duplicate(gResourceLoader->layout->root);
    targets.attribute_pos->add(value26b20);
    value26b28 = bind_animation(node26b40, root, kAttributeAnim);
    value26b20->bind_animation(value26b28, true, true);
    value26b30 = node26b40->group->find(kAttributeIcon, 1)->duplicate(gResourceLoader->layout->root);
    targets.attribute_pos->add(value26b30);
    value26b38 = bind_animation(node26b40, root, kAttributeAnim);
    value26b30->bind_animation(value26b38, true, true);
    show_group(node26b40->group->find(kAttributeIcon, 1));
    gEffectManager->finish(0x41e5);
    EffectGroup* pos = targets.attribute_pos;
    pos->scale48 = 0.66f;
    pos->scale4c = 0.66f;
    pos->flags58 |= 0x10;

    gEffectManager->create_node(&node26b48, 0x41e5, kNumberLayout);
    gEffectManager->sync();
    value26b50 = node26b48->create_animation(kNumberPane, true);
    show_group(node26b48->group);
    number_pane = node26b48->group->find(kNumberPane, 1)->duplicate(gResourceLoader->layout->root);
    node26b48->group->add(number_pane);
    show_group(number_pane);
    value26b58 = bind_animation(node26b48, layout_root(), kNumberPane);
    number_pane->bind_animation(value26b58, true, true);
    gEffectManager->attach_resource(&targets.resource);

    step = gResourceQueueElapsedStep;
    window_anim = targets.node->create_window_animation(kWindowAnims[0], true);
    for (int i = 0; i < 4; ++i) {
        LayoutAnimation* loop = targets.node->create_animation(kArrowLoops[i], true);
        arrow_loops[i] = loop;
        loop->set_rate(step);
    }
    if (get_game()->state()->mode == 5 || get_game()->state()->mode == 6)
        gEffectManager->create_node(&wall_node, 0x420d, kWallLayout);
    if (wall_node) {
        gEffectManager->sync();
        wall_loop = wall_node->create_animation(kLoopAnim, true);
        wall_loop->set_rate(step);
        if (wall_loop)
            wall_loop->set_active(true);
    }
    gEffectManager->sync();
    for (int i = 0; i < 5; ++i)
        panes[i] = new PanelPane;
    targets.node->group->find(kMissionFont, 1)->add(panes[0]);
    targets.node->group->find(kLimitedText, 1)->add(panes[1]);
    targets.node->group->find(kMissionText, 1)->add(panes[2]);
    targets.node->group->find(kAttributeFont, 1)->add(panes[3]);
    targets.node->group->find(kResFont, 1)->add(panes[4]);
    panes[1]->align = 2;
    flag8 = 1;
}
void DemoPanelSystem::update() {
    if (!flag8)
        return;
    update_state();
    if (targets.node) {
        targets.node->advance(gFrameDelta);
        LightEffectNode* target = targets.node;
        void* root = gEffectManager->current();
        target->update(root, 0);
        update_icons();
        update_cells();
        update_marks();
    }
    if (wall_node) {
        wall_node->advance(gFrameDelta);
        LightEffectNode* target = wall_node;
        void* root = gEffectManager->current();
        target->update(root, 0);
    }
}

void DemoPanelSystem::update_state() {
    get_unit_database();
    Game* game = get_game();
    unsigned int mode = get_game()->state()->mode;
    Player* player = &game->players[mode];
    unsigned int id = player->id;
    flag18 = 0;
    int unit = get_unit_database()->records[id].unit;
    value1c = unit;
    for (unsigned int i = 0; i < 128; ++i) {
        unsigned char valid = player->entries[i].valid();
        if (i == id && valid) {
            flag18 = 1;
            value1c = player->entries[i].value0;
            unit = game->players[mode].entries[id].unit;
            break;
        }
    }
    flag9 = player->active(id);
    if (!flag9) {
        value0c = -1;
        value10 = -1;
    } else {
        unsigned char special = false;
        if (get_game()->state()->mode == 8) {
            if (game->players[mode].stage.kind != 0 && game->players[mode].stage.step <= 5)
                special = game->players[mode].stage.step == 4;

        }
        unsigned char open = false;
        if (get_game()->state()->mode == 9)
            open = game->players[mode].stage.kind != 0xff;
        special = open | special;
        Unit* target = get_unit_database()->unit(unit);
        if (special) {
            target->set_flag(0x11, true);
            value0c = get_unit_database()->unit(unit)->width();
            value10 = get_unit_database()->unit(unit)->height();
            target->set_flag(0x11, false);
        } else {
            value0c = target->width();
            value10 = get_unit_database()->unit(unit)->height();
        }
    }
    int last = value1c;
    value14 = get_unit_database()->unit(last)->value0c;
}