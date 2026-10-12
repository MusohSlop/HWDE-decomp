// Matching candidates for the demo panel system bodies 0x71002632cc-0x7100263cfc.
// Names are descriptive placeholders. Status: matching/README.md.

#include "event/demo_effects.h"
#include "event/demo_light_system.h"
#include "event/layout_panes.h"

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

// Animation bound to a node's binding ring (0x58 bytes, vtable GOT 0x7100c2a698).
class AnimBinding : public LayoutAnimation {
public:
    AnimBinding() : value48(nullptr), value50(0) {}
    ~AnimBinding();

    void* value48;            // +48
    int value50;              // +50
};
static_assert(sizeof(AnimBinding) == 0x58, "binding size");

// Attribute icon: a duplicated pane and its bound animation.
struct AttributeSlot {
    EffectGroup* pane;        // +00
    LayoutAnimation* anim;    // +08
};
struct AnimSource {
    void* data;               // +00
    void* block;              // +08
    unsigned char pad10[0x10];

    explicit AnimSource(void* resource);                                    // 0x71005cfac8
};


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
    void draw();                                                            // 0x7100266740
    void draw_wall();                                                       // 0x7100266810
    void open_window();                                                     // 0x71002669c0

    void* value0;                     // +00
    unsigned char flag8;              // +08
    unsigned char flag9;              // +09
    unsigned char flag_a;             // +0a
    unsigned char padb;
    int size[2];                      // +0c
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
    AttributeSlot attributes[2];      // +26b20
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

    int id;                   // +00
    unsigned char pad4[0x8e4];
    int ranks[0xa0];          // +8e8: by unit

    PlayerEntry entries[128]; // +b68
    unsigned char unlocked[0x164]; // +2968: by attribute
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
    unsigned char pad2[2];
    unsigned short character; // +04
    unsigned short grade;     // +06
    unsigned char pad8[0x16];
    short attribute;          // +1e
    unsigned char pad20[4];
    unsigned short weapon;    // +24
    unsigned char pad26[0x1ba];
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
unsigned char unit_info_hidden();                                           // 0x710026b374

struct IconRect {
    unsigned short v[8];
};

class IconTable {
public:
    const IconRect* get(int id);                                            // 0x7100283d74
};
// Reached through the GOT slot at 0x7100c2a650.
extern IconTable* gIconTable;

extern const char kWallLeft[] __attribute__((visibility("hidden")));            // 0x71007d5cb5
extern const char kWallRight[] __attribute__((visibility("hidden")));           // 0x71007d5cbc
extern const char kWallUp[] __attribute__((visibility("hidden")));              // 0x71007d5cc3
extern const char kWallDown[] __attribute__((visibility("hidden")));            // 0x71007d5cca
int wall_direction(int player);                                             // 0x710026a100
void play_sound(int id, void* source);                                      // 0x71003fef50

extern const char kQuestionMark[] __attribute__((visibility("hidden")));         // 0x71007d5c98
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
    size[0] = 0;
    size[1] = 0;
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
    attributes[1].anim = nullptr;
    attributes[1].pane = nullptr;
    attributes[0].anim = nullptr;
    attributes[0].pane = nullptr;
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

    attributes[0].pane = node26b40->group->find(kAttributeIcon, 1)->duplicate(gResourceLoader->layout->root);
    targets.attribute_pos->add(attributes[0].pane);
    attributes[0].anim = bind_animation(node26b40, root, kAttributeAnim);
    attributes[0].pane->bind_animation(attributes[0].anim, true, true);
    attributes[1].pane = node26b40->group->find(kAttributeIcon, 1)->duplicate(gResourceLoader->layout->root);
    targets.attribute_pos->add(attributes[1].pane);
    attributes[1].anim = bind_animation(node26b40, root, kAttributeAnim);
    attributes[1].pane->bind_animation(attributes[1].anim, true, true);
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
        size[0] = -1;
        size[1] = -1;
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
            size[0] = get_unit_database()->unit(unit)->width();
            size[1] = get_unit_database()->unit(unit)->height();
            target->set_flag(0x11, false);
        } else {
            size[0] = target->width();
            size[1] = get_unit_database()->unit(unit)->height();
        }
    }
    int last = value1c;
    value14 = get_unit_database()->unit(last)->value0c;
}

static inline void move_x(EffectGroup* group, float x) {
    group->offset30 = x;
    group->flags58 |= 0x10;
}

void DemoPanelSystem::update_cells() {
    if (!attributes[0].pane && !attributes[0].anim)
        return;
    UnitDatabase* database = get_unit_database();
    Game* game = get_game();
    unsigned int mode = get_game()->state()->mode;
    short* attribute = &database->records[game->players[mode].id].attribute;
    if (node26b40) {
        for (int i = 0; i < 2; ++i) {
            AttributeSlot& slot = attributes[i];
            if (game->players[mode].unlocked[*attribute]) {
                int frame = size[i];
                if (frame >= 0 && frame <= slot.anim->frame_count()) {
                    if (slot.anim)
                        slot.anim->set_frame(size[i]);
                    if (slot.anim)
                        slot.anim->set_active(true);
                    slot.pane->flags58 |= 1;
                    continue;
                }
            }
            if (slot.anim)
                slot.anim->set_active(false);
            slot.pane->flags58 &= ~1;
        }
        node26b40->advance(gFrameDelta);
        LightEffectNode* target = node26b40;
        void* root = gEffectManager->current();
        target->update(root, 0);
    } else {
        if (!game->players[mode].unlocked[*attribute])
            attributes[0].pane->flags58 &= ~1;
        if (!game->players[mode].unlocked[*attribute])
            attributes[1].pane->flags58 &= ~1;
    }
    if (size[1] != -1) {
        move_x(attributes[0].pane, -48.0f);
        move_x(attributes[1].pane, 12.0f);
    } else {
        move_x(attributes[0].pane, 0.0f);
    }
}

void apply_icon(EffectGroup* pane, LayoutHandle* handle, IconTable* table, const IconRect* rect); // 0x71001f7fe4

static inline void show_icon(PanelItem& item, int icon) {
    const IconRect* rect = gIconTable->get(icon);
    apply_icon(item.object, &item.handle, gIconTable, rect);
    item.object->flags58 |= 1;
}

static inline void set_icon(PanelItem& item, int icon) {
    if (static_cast<unsigned int>(icon) >= 0x106)
        item.object->flags58 &= ~1;
    else
        show_icon(item, icon);
}

// Icon of a character or weapon id (0-30); ids 19 and 20 share slots with their neighbours.
static inline int unit_icon(unsigned short id) {
    if (id <= 0x1e) {
        short value = id;
        int slot = value < 0x13 ? value : value - 2;
        if (static_cast<unsigned int>(slot) > 0xb)
            ++slot;
        return slot + 0x64;
    }
    return -1;
}

static inline int grade_icon(unsigned short grade) {
    unsigned short slot = grade - (static_cast<short>(grade) > 0x13);
    if (static_cast<short>(slot) > 0x1d)
        slot += 0xfffe;
    int icon = static_cast<short>(slot) + 0x82;
    return slot < 0x40 ? icon : -1;
}

static inline void place_icon(EffectGroup* pane, float x) {
    pane->offset30 = x;
    pane->offset34 = -2.0f;
    pane->offset38 = 0.0f;
    pane->flags58 |= 0x10;
}

static inline void scale_icon(EffectGroup* pane, float scale) {
    pane->scale48 = scale;
    pane->scale4c = scale;
    pane->flags58 |= 0x10;
}

void DemoPanelSystem::update_icons() {
    UnitDatabase* database = get_unit_database();
    Game* game = get_game();
    unsigned int mode = get_game()->state()->mode;
    int id = game->players[mode].id;
    for (int i = 0; i < 4; ++i)
        targets.items[i].object->flags58 &= ~1;
    node26b48->group->flags58 &= ~1;
    if (game->players[mode].unlocked[database->records[id].attribute] && !flag18) {
        unsigned short character = get_unit_database()->records[static_cast<unsigned int>(id)].character;
        unsigned short weapon = get_unit_database()->records[static_cast<unsigned int>(id)].weapon;
        unsigned short grade = get_unit_database()->records[static_cast<unsigned int>(id)].grade;
        if (unit_info_hidden()) {
            character = 0xffff;
            weapon = 0xffff;
            grade = 0xffff;
        }
        int first;
        if (get_game()->state()->mode == 8 && game->players[mode].stage.step == 5) {
            first = -1;
            weapon = 0xffff;
            grade = 0xffff;
        } else {
            first = unit_icon(character);
        }
        float scale = 0.8f;
        int second = unit_icon(weapon);
        int third = grade_icon(grade);
        bool paired = false;
        bool placed = false;
        if (first != -1) {
            set_icon(targets.items[0], first);
            if (second != -1) {
                set_icon(targets.items[1], second);
                placed = true;
            }
        } else {
            paired = second != -1;
        }
        float left = 44.0f;
        float right = 96.0f;
        if (!placed) {
            bool single = third == -1;
            if (!single) {
                if (static_cast<unsigned int>(third) <= 0x105)
                    show_icon(targets.items[1], third);
                else
                    targets.items[1].object->flags58 &= ~1;
            }
            if (!paired) {
                if (single)
                    scale = 1.0f;
                left = single ? 58.0f : 44.0f;
                right = single ? 110.0f : 96.0f;
            }
        }
        place_icon(targets.items[0].object, left);
        scale_icon(targets.items[0].object, scale);
        place_icon(targets.items[1].object, right);
        scale_icon(targets.items[1].object, scale);
    }
    if (!flag18) {
        int rank = game->players[mode].ranks[id];
        if (rank == 1)
            show_icon(targets.items[2], 0xc2);
        else if (rank == 2)
            show_icon(targets.items[2], 0xc1);
        else if (rank == 3)
            show_icon(targets.items[2], 0xc0);
    }
    if (flag9 && value14 >= 1)
        show_icon(targets.items[3], 0xc7);
    EffectGroup* question = targets.node->group->find(kQuestionMark, 1);
    if (!flag9)
        question->flags58 |= 1;
    else
        question->flags58 &= ~1;
}

void DemoPanelSystem::draw() {
    if (!flag8)
        return;
    if (wall_node)
        draw_wall();
    EffectGroup* number = targets.items[3].object;
    number->offset30 = value14 > 9 ? 245.0f : 273.0f;
    number->flags58 |= 0x10;
    EffectGroup* pos = targets.node->group->find(kNumberPos, 1);
    pos->offset30 = 335.0f;
    pos->flags58 |= 0x10;
    if (targets.node)
        targets.node->draw(0);
    if (node26b48)
        node26b48->draw(0);
}

void DemoPanelSystem::draw_wall() {
    Game* game = get_game();
    int direction = wall_direction(game->players[get_game()->state()->mode].id);
    show_group(wall_node->group->find(kWallLeft, 1));
    show_group(wall_node->group->find(kWallRight, 1));
    show_group(wall_node->group->find(kWallUp, 1));
    show_group(wall_node->group->find(kWallDown, 1));
    switch (direction) {
    case 0:
        wall_node->group->find(kWallUp, 1)->flags58 |= 1;
        break;
    case 1:
        wall_node->group->find(kWallLeft, 1)->flags58 |= 1;
        break;
    case 2:
        wall_node->group->find(kWallRight, 1)->flags58 |= 1;
        break;
    case 3:
        wall_node->group->find(kWallDown, 1)->flags58 |= 1;
        break;
    }
    wall_node->draw(0);
}

static inline void restart_animation(LayoutAnimation*& animation, const float& rate) {
    if (animation)
        animation->rewind();
    animation->set_rate(rate);
}

void DemoPanelSystem::open_window() {
    restart_animation(window_anim, step);
    play_sound(0x17ec, nullptr);
}