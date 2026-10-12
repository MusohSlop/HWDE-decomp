// Matching candidates for the demo effect pool bodies 0x710026086c-0x7100260fe8.
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

extern unsigned int gResourceQueueElapsedStep;

// Layout names, merged with other literals by the linker.
extern const char kQuestionLayout[] __attribute__((visibility("hidden")));  // 0x71007d5ab6
extern const char kNumberLayout[] __attribute__((visibility("hidden")));    // 0x71007d5ac9
extern const char kNumberPane[] __attribute__((visibility("hidden")));      // 0x710074129f

class LayoutAnimation {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void set_active(bool active); // +20
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
    virtual void v98();
    virtual void va0();
    virtual void va8();
    virtual void set_rate(float rate); // +b0
    virtual void vb8();
    virtual void vc0();
    virtual void vc8();
    virtual void rewind(); // +d0
    unsigned short frame_count();                                           // 0x71005ce178

    unsigned char pad8[0x18];
    float frame;              // +20
    unsigned char pad24[0x18];
    float speed;              // +3c
};

class GameState {
public:
    unsigned char pad[0x1bb7c];
    unsigned int mode;        // +1bb7c
};

class Player {
public:
    unsigned char active(int id);                                           // 0x710026a90c

    int id;                   // +00
    unsigned char pad4[0x764];
    unsigned char enabled[8]; // +768
    unsigned char pad770[0x24c8];
};

class Game {
public:
    GameState* state();                                                     // 0x7100204c10

    unsigned char pad[0x2944];
    Player players[4];        // +2944
};
Game* get_game();                                                           // 0x7100204728

struct IconRect {
    unsigned short v[8];
};

class IconTable {
public:
    const IconRect* get(int id);                                            // 0x7100283d74
    void apply(LightSource* source, IconRect* rect, TrackVec2* position);   // 0x7100283db0
};
// Reached through the GOT slot at 0x7100c2a650.
extern IconTable* gIconTable;

class TrackRenderer {
public:
    void write(void* data, unsigned int size, int slot);                    // 0x71001df8c0
    void begin(int mode);                                                   // 0x71001df744
    void end();                                                             // 0x71001df838
};
// Reached through the GOT slot at 0x7100c22a40.
extern TrackRenderer* gTrackRenderer;

int unit_kind(int player, int slot);                                        // 0x7100269cfc
int unit_frame(int player, int slot);                                       // 0x710026c730
unsigned char unit_has_override(int player, int slot);                               // 0x710026c924
int unit_override_kind(int player, int slot);                               // 0x710026c654
int unit_override_frame(int player, int slot);                              // 0x710026c884
unsigned int display_width();                                               // 0x71003cc930
unsigned int display_height();                                              // 0x71003cc94c
TrackVec2 project_point(TrackVec2* position, float width, float height);    // 0x71001e412c

class UnitRoster {
public:
    void query(int player, int slot, int pass, int* kind, int* value, int* flag); // 0x710026b3cc
};

// Layout and animation names, reached through the GOT slots at 0x7100c2a658-0x7100c2a670.
extern const char* const kSlotLayouts[];
extern const char* const kSlotAnimations[];
extern const char* const kMarkerLayouts[];
extern const char* const kMarkerAnimations[];
extern const char kEnemyDetailLayout[] __attribute__((visibility("hidden"))); // 0x71007d5ad7

// Frame delta, reached through the GOT slot at 0x7100c22a28.
extern float gFrameDelta;

struct EffectSlot {
    LightEffectNode* node;    // +00
    LayoutAnimation* value8;  // +08
    LayoutAnimation* animation; // +10
    int index;                // +18
    int value;                // +1c
    int kind;                 // +20
    unsigned char pad24[4];

    void reset() {
        node = nullptr;
        value8 = 0;
        animation = nullptr;
        index = -1;
        value = 0;
        kind = 0xd;
    }
};
static_assert(sizeof(EffectSlot) == 0x28, "slot size");

struct EffectMarker {
    LightEffectNode* node;    // +00
    LayoutAnimation* value8;  // +08
    int index;                // +10
    int value;                // +14
    int kind;                 // +18
    unsigned char pad1c[4];

    void reset() {
        node = nullptr;
        value8 = 0;
        index = -1;
        value = 0;
        kind = 4;
    }
};
static_assert(sizeof(EffectMarker) == 0x20, "marker size");

struct EffectCaption {
    LightEffectNode* node;    // +00
    int value;                // +08
    unsigned char pad0c[4];
};

template <class T>
static inline void advance_nodes(T* items, const unsigned int& count) {
    for (int i = 0; static_cast<unsigned int>(i) < count; ++i)
        items[i].node->advance(gFrameDelta);
}

class DemoEffectPool {
public:
    DemoEffectPool();
    ~DemoEffectPool() { finalize(); }
    void initialize();
    void clear();
    void finalize();
    void update();
    void update_slots();
    void update_markers();
    void setup();
    bool restart();
    void draw();
    void draw_nodes();
    void draw_marker(LightEffectNode* node, int index, int value, int player); // 0x7100261720
    // Defined in the class, so it is emitted as an inline function the optimizer cannot rewrite.
    void render_marker(LightEffectNode* node, int index, int value, int player) { // 0x7100261aa8
        if (get_game()->state()->mode != 5 && get_game()->state()->mode != 6 &&
            get_game()->state()->mode != 8)
            return;
        if (static_cast<unsigned int>(value) > 0xaf)
            return;
        int kind = unit_kind(player, value);
        if (unit_has_override(player, value))
            kind = unit_override_kind(player, value);
        int frame = unit_frame(player, value);
        if (unit_has_override(player, value))
            frame = unit_override_frame(player, value);
        if (get_game()->state()->mode == 8) {
            bool kind_valid = kind != -1 && kind < 9;
            bool frame_valid = frame != -1 && frame < 9;
            bool kind_large = static_cast<unsigned int>(kind - 0x97) < 9;
            bool frame_large = static_cast<unsigned int>(frame - 0x97) < 9;
            if (!kind_valid && !frame_valid && !kind_large && !frame_large)
                return;
            if (kind_valid && !kind_large && frame > 8 && !frame_large)
                return;
            if (static_cast<unsigned int>(index - 0x2b) < 8)
                return;
            if (kind_large && frame != -1 && !frame_large)
                return;
        } else {
            bool kind_valid = kind != -1 && kind <= 0x25;
            bool frame_valid = frame != -1 && frame <= 0x25;
            if (!kind_valid && !frame_valid)
                return;
            if (kind_valid && frame > 0x25)
                return;
            if (static_cast<unsigned int>(index - 0x2b) < 8)
                return;
            if (static_cast<unsigned int>(frame - 0x16) < 4 || static_cast<unsigned int>(kind - 9) < 4 ||
                static_cast<unsigned int>(kind - 0x16) < 4 || static_cast<unsigned int>(frame - 9) < 4)
                return;
        }
        EffectGroup* group = node->group;
        float y = group->offset34;
        float x = group->offset30;
        LightSource source;
        TrackVec2 screen;
        {
            TrackVec2 position = {x, y - 24.0f};
            screen = project_point(&position, display_width(), display_height());
        }
        const IconRect* src = gIconTable->get(0xbf);
        IconRect rect = *src;
        rect.v[0] = src->v[0];
        rect.v[1] = src->v[1];
        rect.v[2] = src->v[2];
        rect.v[3] = src->v[3] + 1;
        rect.v[4] = src->v[4];
        rect.v[5] = src->v[5] - 1;
        rect.v[6] = src->v[6];
        rect.v[7] = src->v[7];
        gIconTable->apply(&source, &rect, &screen);
        source.min.x = screen.x - 48.0f;
        source.min.y = screen.y - 24.0f;
        source.max.x = screen.x + 48.0f;
        source.max.y = screen.y + 24.0f;
        gTrackRenderer->begin(0x11);
        gTrackRenderer->write(&source, 0x48, -1);
        gTrackRenderer->end();
    }

    UnitRoster* roster;               // +00
    unsigned char initialized;        // +08
    unsigned char pad9[3];
    int count0c;                      // +0c
    int value10;                      // +10
    unsigned char pad14[4];
    EffectSlot slots_a[28];           // +18
    unsigned int count_a;                      // +478
    unsigned char pad47c[4];
    EffectSlot slots_b[28];           // +480
    unsigned int count_b;                      // +8e0
    unsigned char pad8e4[4];
    EffectMarker markers_c[28];       // +8e8
    unsigned int count_c;                      // +c68
    unsigned char padc6c[4];
    EffectMarker markers_d[28];       // +c70
    unsigned int count_d;                      // +ff0
    unsigned char padff4[4];
    EffectCaption captions[28];       // +ff8
    unsigned int count_e;                      // +11b8
    unsigned char pad11bc[4];
    LightEffectNode* node;            // +11c0
    unsigned char pad11c8[8];
    LightResource resource;           // +11d0
    float step;                       // +12e0
    unsigned char pad12e4[0xc];
};
static_assert(sizeof(DemoEffectPool) == 0x12f0, "pool size");

// Reached through the GOT slot at 0x7100c2a648.
extern DemoEffectPool* gDemoEffectPool;

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

DemoEffectPool::DemoEffectPool() {
    step = 0;
    initialized = 0;
    roster = nullptr;
    count0c = 0;
    for (int i = 0; i < 28; ++i)
        slots_a[i].reset();
    for (int i = 0; i < 28; ++i)
        slots_b[i].reset();
    for (int i = 0; i < 28; ++i)
        markers_c[i].reset();
    for (int i = 0; i < 28; ++i)
        markers_d[i].reset();
    for (int i = 0; i < 28; ++i) {
        captions[i].node = nullptr;
        captions[i].value = 0;
    }
    count_a = 0;
    count_c = 0;
    count_b = 0;
    count_d = 0;
    count_e = 0;
    node = nullptr;
}

void DemoEffectPool::finalize() {
    clear();
    if (node) {
        EffectManager* manager = gEffectManager;
        node->detach(gResourceLoader->layout->root);
        node->release();
        manager->nodes.remove(node);
        node = nullptr;
    }
    node = nullptr;
    for (int i = 0; i < 28; ++i) {
        release_node(captions[i].node, 0x420d);
        captions[i].node = nullptr;
        captions[i].value = 0;
    }
    count0c = 0;
    roster = nullptr;
    initialized = 0;
}

void create_demo_effect_pool() {
    if (!gDemoEffectPool) {
        void* storage = get_default_heap()->allocate(0x10, sizeof(DemoEffectPool), 1, 0);
        gDemoEffectPool = new (storage) DemoEffectPool;
    }
}

void destroy_demo_effect_pool() {
    if (gDemoEffectPool) {
        gDemoEffectPool->finalize();
        DemoEffectPool* pool = gDemoEffectPool;
        if (pool) {
            pool->~DemoEffectPool();
            get_default_heap()->release(pool, 1, 0);
        }
        gDemoEffectPool = nullptr;
    }
}

void DemoEffectPool::initialize() {
    if (initialized)
        return;
    for (int i = 0; i < 28; ++i) {
        EffectCaption& caption = captions[i];
        gEffectManager->create_node(&caption.node, 0x420d, kQuestionLayout);
        caption.node->group->flags58 &= ~1;
    }
    gEffectManager->create_node(&node, 0x41e5, kNumberLayout);
    node->group->find(kNumberPane, 1)->flags58 &= ~1;
    EffectGroup* group = node->group;
    group->add(new LightEffect(0x11));
    gEffectManager->attach_resource(&resource);
    step = gResourceQueueElapsedStep;
    initialized = 1;
}

void DemoEffectPool::clear() {
    for (int i = 0; i < 28; ++i) {
        release_node(slots_a[i].node, 0x4211);
        slots_a[i].reset();
    }
    for (int i = 0; i < 28; ++i) {
        release_node(markers_c[i].node, 0x420f);
        markers_c[i].reset();
    }
    for (int i = 0; i < 28; ++i) {
        release_node(slots_b[i].node, 0x4211);
        slots_b[i].reset();
    }
    for (int i = 0; i < 28; ++i) {
        release_node(markers_d[i].node, 0x420f);
        markers_d[i].reset();
    }
    for (int i = 0; i < 28; ++i) {
        if (captions[i].node)
            captions[i].node->group->flags58 &= ~1;
    }
    count_a = 0;
    count_c = 0;
    count_b = 0;
    count_d = 0;
    count0c = 0;
}

void DemoEffectPool::update() {
    if (initialized) {
        update_slots();
        update_markers();
    }
}

void DemoEffectPool::update_slots() {
    switch (count0c) {
    case 1:
        advance_nodes(slots_a, count_a);
        advance_nodes(markers_c, count_c);
        advance_nodes(slots_b, count_b);
        advance_nodes(markers_d, count_d);
        break;
    case 3: {
        if (!slots_a[0].node) {
            clear();
            return;
        }
        LayoutAnimation* animation = slots_a[0].animation;
        if (animation->frame == animation->frame_count()) {
            count0c = 2;
            return;
        }
        advance_nodes(slots_a, count_a);
        advance_nodes(markers_c, count_c);
        advance_nodes(slots_b, count_b);
        advance_nodes(markers_d, count_d);
        break;
    }
    }
}

template <class T>
static inline void move_node(DemoEffectPool* pool, T& item, int kind, float offset, Player* player) {
    float delta = item.kind == kind ? -offset : offset;
    EffectGroup* group = item.node->group;
    group->offset34 = delta + group->offset34;
    group->flags58 |= 0x10;
    LightEffectNode* target = item.node;
    void* root = gEffectManager->current();
    target->update(root, 0);
    pool->draw_marker(item.node, item.index, item.value, player->id);
    pool->render_marker(item.node, item.index, item.value, player->id);
}

void DemoEffectPool::update_markers() {
    if (count0c == 0)
        return;
    Game* game = get_game();
    Player* player = &game->players[get_game()->state()->mode];
    if (player->active(player->id)) {
        EffectCaption* caption = captions;
        for (unsigned int i = 0; i < static_cast<unsigned int>(count_e); ++caption, ++i) {
            if (captions[static_cast<unsigned int>(count_e)].node) {
                LightEffectNode* target = caption->node;
                void* root = gEffectManager->current();
                target->update(root, 0);
            }
        }
    }
    float offset = slots_a[0].animation->speed != 0.0f ? 0.5f : 0.0f;
    if (player->active(player->id)) {
        for (int i = 0; static_cast<unsigned int>(i) < static_cast<unsigned int>(count_d); ++i)
            move_node(this, markers_d[i], 1, offset, player);
    }
    if (player->active(player->id)) {
        for (int i = 0; static_cast<unsigned int>(i) < static_cast<unsigned int>(count_b); ++i)
            move_node(this, slots_b[i], 3, offset, player);
    }
    if (player->active(player->id) && count_a != 0) {
        for (int i = 0; static_cast<unsigned int>(i) < static_cast<unsigned int>(count_c); ++i)
            move_node(this, markers_c[i], 1, offset, player);
        for (int i = 1; static_cast<unsigned int>(i) < static_cast<unsigned int>(count_a); ++i)
            move_node(this, slots_a[i], 3, offset, player);
        if (slots_a[0].node)
            move_node(this, slots_a[0], 3, offset, player);
    }
    if (LightEffectNode* counter = node)
    {
        void* root = gEffectManager->current();
        counter->update(root, 0);
    }

}

void DemoEffectPool::draw_marker(LightEffectNode* node, int index, int value, int player) {
    if (get_game()->state()->mode != 4 && get_game()->state()->mode != 7 &&
        get_game()->state()->mode != 9)
        return;
    int slot = value < 0 ? -value : value;
    int kind = unit_kind(player, slot);
    int frame = unit_frame(player, slot);
    if (get_game()->state()->mode == 4) {
        if (static_cast<unsigned int>(kind - 0xc5) > 8)
            return;
    } else if (get_game()->state()->mode == 7) {
        if (kind != 0x64 && static_cast<unsigned int>(frame - 0xd) > 0xc)
            return;
    } else if (get_game()->state()->mode == 9) {
        if (frame >= 0xd && static_cast<unsigned int>(frame - 0x16) >= 0x11) {
            bool blocked = static_cast<unsigned int>(frame - 0x2d) < 0xb1 || frame > 0xe2;
            if (static_cast<unsigned int>(kind - 0xde) >= 5 && blocked)
                return;
        } else if (static_cast<unsigned int>(kind - 0xde) > 4) {
            return;
        }
    }
    float half_width;
    float lift = 37.0f;
    switch (index) {
    case 47:
    case 48:
        lift = 80.75f;
        half_width = 72.0f;
        break;
    default:
        half_width = 48.0f;
        break;
    case 43:
        lift = 80.75f;
    case 44:
        half_width = 96.0f;
        break;
    case 45:
        half_width = 144.0f;
        break;
    case 46:
    case 49:
    case 50:
        return;
    }
    EffectGroup* group = node->group;
    float y = group->offset34;
    float x = group->offset30;
    LightSource source;
    TrackVec2 screen;
    {
        TrackVec2 position = {x, y - lift};
        screen = project_point(&position, display_width(), display_height());
    }
    GameState* first = get_game()->state();
    GameState* state = get_game()->state();
    int icon = 0xbe;
    if (kind != 0x64 || state->mode != 7) {
        int base = first->mode == 4 ? 0x105 : 0xbd;
        if (get_game()->state()->mode != 9 || static_cast<unsigned int>(frame - 0x27) >= 6)
            icon = base;
    }
    const IconRect* src = gIconTable->get(icon);
    IconRect rect = *src;
    rect.v[0] = src->v[0];
    rect.v[1] = src->v[1];
    rect.v[2] = src->v[2] + 1;
    rect.v[3] = src->v[3];
    rect.v[4] = src->v[4] - 2;
    rect.v[5] = src->v[5];
    rect.v[6] = src->v[6];
    rect.v[7] = src->v[7];
    gIconTable->apply(&source, &rect, &screen);
    source.min.x = screen.x - half_width;
    source.min.y = screen.y - 11.666667f;
    source.max.x = half_width + screen.x;
    source.max.y = screen.y + 11.666667f;
    source.color.a = 0x78;
    gTrackRenderer->begin(0x11);
    gTrackRenderer->write(&source, 0x48, -1);
    gTrackRenderer->end();
}

struct UnitRecord {
    int kind;
    int value;
    int flag;

    UnitRecord() : kind(-1), value(-1), flag(0) {}

};

// Places a node on the 16-column grid encoded in `cell`.
static inline void place_node(LightEffectNode* node, unsigned int cell) {
    EffectGroup* group = node->group;
    float x = static_cast<float>(cell & 0xf) * 56.0f + -420.0f;
    float y = 304.0f - static_cast<float>(cell >> 4) * 56.0f;
    group->offset38 = 0.0f;
    group->flags58 |= 0x10;
    group->offset30 = x * 1.5f;
    group->offset34 = y * 1.5f;
}

static inline void set_scale(LightEffectNode* node, const float& scale) {
    EffectGroup* group = node->group;
    group->scale48 = scale;
    group->scale4c = scale;
    group->flags58 |= 0x10;
}

static inline void rewind_animation(LayoutAnimation*& animation) {
    if (animation)
        animation->rewind();
    if (animation)
        animation->set_active(false);
}

void DemoEffectPool::setup() {
    if (value10 != 0 || count0c != 0)
        return;
    count_a = 0;
    count_c = 0;
    count_b = 0;
    count_d = 0;
    count_e = 0;
    Game* game = get_game();
    Player* player = &game->players[get_game()->state()->mode];
    int id = player->id;
    if (!player->active(id))
        return;
    if (!player->enabled[player->id])
        return;

    UnitRecord first[5];
    for (int i = 0; i < 5; ++i)
        roster->query(id, i, 0, &first[i].kind, &first[i].value, &first[i].flag);
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 5; ++j) {
            if (first[i].value > first[j].value) {
                int kind = first[j].kind;
                int value = first[j].value;
                int flag = first[j].flag;
                first[j] = first[i];
                first[i].kind = kind;
                first[i].value = value;
                first[i].flag = flag;
            }
        }
    }
    gEffectManager->sync();
    for (int i = 0; i < 5; ++i) {
        int flag = first[i].flag;
        int value = first[i].value;
        unsigned int kind = first[i].kind;
        if (value == -1 || value > 1000)
            kind = -1;
        if (static_cast<unsigned int>(kind) <= 0x2a) {
            if (kind == 0x28)
                kind = 0xd;
            if (kind == 0x29)
                kind = 0xe;
            if (kind == 0x2a)
                kind = 0xf;
            slots_a[count_a].index = kind;
            slots_a[count_a].value = value;
            gEffectManager->create_node(&slots_a[count_a].node, 0x4211, kSlotLayouts[kind]);
            gEffectManager->sync();
            place_node(slots_a[count_a].node, slots_a[count_a].value);
            set_scale(slots_a[count_a].node, 1.3125f);
            slots_a[count_a].value8 = slots_a[count_a].node->create_animation(kSlotAnimations[2], true);
            slots_a[count_a].animation = slots_a[count_a].node->create_animation(kSlotAnimations[6], true);
            slots_a[count_a].kind = 2;
            gEffectManager->finish(0x4211);
            EffectSlot& slot = slots_a[count_a];
            rewind_animation(slot.value8);
            rewind_animation(slot.animation);
            slots_a[count_a].value8->set_rate(0.5f);
            if (slots_a[count_a].value8)
                slots_a[count_a].value8->set_active(true);
            ++count_a;
        }
        unsigned int marker = kind - 0x28;
        if (marker <= 0x3b && static_cast<unsigned int>(kind - 0x42) >= 3) {
            markers_c[count_c].index = kind;
            markers_c[count_c].value = value;
            unsigned int mode = get_game()->state()->mode;
            if (marker == 0x1e && mode >= 7)
                gEffectManager->create_node(&markers_c[count_c].node, 0x420f, kEnemyDetailLayout);
            else
                gEffectManager->create_node(&markers_c[count_c].node, 0x420f, kMarkerLayouts[marker]);
            gEffectManager->sync();
            place_node(markers_c[count_c].node, markers_c[count_c].value);
            if (kind == 0x41)
                set_scale(markers_c[count_c].node, 0.652500033f);
            else
                set_scale(markers_c[count_c].node, 1.3125f);
            markers_c[count_c].value8 = markers_c[count_c].node->create_animation(kMarkerAnimations[0], true);
            markers_c[count_c].kind = 0;
            gEffectManager->finish(0x420f);
            rewind_animation(markers_c[count_c].value8);
            markers_c[count_c].value8->set_rate(0.5f);
            if (markers_c[count_c].value8)
                markers_c[count_c].value8->set_active(true);
            ++count_c;
        }
        if (flag == 1 && captions[count_e].node) {
            place_node(captions[count_e].node, value);
            captions[count_e].node->group->flags58 |= 1;
            ++count_e;
        }
    }

    UnitRecord second[5];
    for (int i = 0; i < 5; ++i)
        roster->query(id, i, 1, &second[i].kind, &second[i].value, &second[i].flag);
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 5; ++j) {
            if (second[i].value > second[j].value) {
                int kind = second[j].kind;
                int value = second[j].value;
                int flag = second[j].flag;
                second[j] = second[i];
                second[i].kind = kind;
                second[i].value = value;
                second[i].flag = flag;
            }
        }
    }    for (int i = 0; i < 5; ++i) {
        int flag = second[i].flag;
        int value = second[i].value;
        unsigned int kind = second[i].kind;
        if (value == -1 || value > 1000)
            kind = -1;
        if (static_cast<unsigned int>(kind) <= 0x2a) {
            if (kind == 0x28)
                kind = 0xd;
            if (kind == 0x29)
                kind = 0xe;
            if (kind == 0x2a)
                kind = 0xf;
            slots_b[count_b].index = kind;
            slots_b[count_b].value = value;
            gEffectManager->create_node(&slots_b[count_b].node, 0x4211, kSlotLayouts[kind]);
            gEffectManager->sync();
            place_node(slots_b[count_b].node, slots_b[count_b].value);
            set_scale(slots_b[count_b].node, 1.3125f);
            slots_b[count_b].value8 = slots_b[count_b].node->create_animation(kSlotAnimations[3], true);
            slots_b[count_b].animation = slots_b[count_b].node->create_animation(kSlotAnimations[7], true);
            slots_b[count_b].kind = 3;
            gEffectManager->finish(0x4211);
            EffectSlot& slot = slots_b[count_b];
            rewind_animation(slot.value8);
            rewind_animation(slot.animation);
            slots_b[count_b].value8->set_rate(0.5f);
            if (slots_b[count_b].value8)
                slots_b[count_b].value8->set_active(true);
            ++count_b;
        }
        unsigned int marker = kind - 0x28;
        if (marker <= 0x3b && static_cast<unsigned int>(kind - 0x42) >= 3) {
            markers_d[count_d].index = kind;
            markers_d[count_d].value = value;
            unsigned int mode = get_game()->state()->mode;
            if (marker == 0x1e && mode >= 7)
                gEffectManager->create_node(&markers_d[count_d].node, 0x420f, kEnemyDetailLayout);
            else
                gEffectManager->create_node(&markers_d[count_d].node, 0x420f, kMarkerLayouts[marker]);
            gEffectManager->sync();
            place_node(markers_d[count_d].node, markers_d[count_d].value);
            if (kind == 0x41)
                set_scale(markers_d[count_d].node, 0.652500033f);
            else
                set_scale(markers_d[count_d].node, 1.3125f);
            markers_d[count_d].value8 = markers_d[count_d].node->create_animation(kMarkerAnimations[1], true);
            markers_d[count_d].kind = 1;
            gEffectManager->finish(0x420f);
            rewind_animation(markers_d[count_d].value8);
            markers_d[count_d].value8->set_rate(0.5f);
            if (markers_d[count_d].value8)
                markers_d[count_d].value8->set_active(true);
            ++count_d;
        }
        if (flag == 1 && captions[count_e].node) {
            place_node(captions[count_e].node, value);
            captions[count_e].node->group->flags58 |= 1;
            ++count_e;
        }
    }
    count0c = 1;
}

bool DemoEffectPool::restart() {
    if (static_cast<unsigned int>(value10 - 5) > 1)
        return false;
    if (count0c != 1)
        return false;
    for (int i = 0; static_cast<unsigned int>(i) < count_a; ++i) {
        rewind_animation(slots_a[i].value8);
        rewind_animation(slots_a[i].animation);
        slots_a[i].animation->set_rate(2.0f);
        if (slots_a[i].animation)
            slots_a[i].animation->set_active(true);
    }
    for (int i = 0; static_cast<unsigned int>(i) < count_b; ++i) {
        rewind_animation(slots_b[i].value8);
        rewind_animation(slots_b[i].animation);
        slots_b[i].animation->set_rate(2.0f);
        if (slots_b[i].animation)
            slots_b[i].animation->set_active(true);
    }
    count0c = 3;
    return true;
}

// The fields are passed by reference, so each call reloads them.
static inline void draw_node(DemoEffectPool* pool, LightEffectNode* const& node, const int& index,
                             const int& value, Player* player) {
    node->draw(0);
    pool->draw_marker(node, index, value, player->id);
    pool->render_marker(node, index, value, player->id);
}

void DemoEffectPool::draw() {
    if (initialized)
        draw_nodes();
}

void DemoEffectPool::draw_nodes() {
    if (count0c == 0)
        return;
    Game* game = get_game();
    Player* player = &game->players[get_game()->state()->mode];
    if (player->active(player->id)) {
        EffectCaption* caption = captions;
        for (unsigned int i = 0; i < count_e; ++caption, ++i) {
            if (captions[count_e].node)
                caption->node->draw(0);
        }
    }
    if (player->active(player->id)) {
        for (int i = 0; static_cast<unsigned int>(i) < count_d; ++i)
            draw_node(this, markers_d[i].node, markers_d[i].index, markers_d[i].value, player);
    }
    if (player->active(player->id)) {
        for (int i = 0; static_cast<unsigned int>(i) < count_b; ++i)
            draw_node(this, slots_b[i].node, slots_b[i].index, slots_b[i].value, player);
    }
    if (player->active(player->id) && count_a != 0) {
        for (int i = 0; static_cast<unsigned int>(i) < count_c; ++i)
            draw_node(this, markers_c[i].node, markers_c[i].index, markers_c[i].value, player);
        for (int i = 1; static_cast<unsigned int>(i) < count_a; ++i)
            draw_node(this, slots_a[i].node, slots_a[i].index, slots_a[i].value, player);
        if (slots_a[0].node)
            draw_node(this, slots_a[0].node, slots_a[0].index, slots_a[0].value, player);
    }
    if (node)
        node->draw(0);
}
