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
    unsigned short frame_count();                                           // 0x71005ce178

    unsigned char pad[0x20];
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
    unsigned char pad4[0x2c34];
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

// Frame delta, reached through the GOT slot at 0x7100c22a28.
extern float gFrameDelta;

struct EffectSlot {
    LightEffectNode* node;    // +00
    unsigned long value8;     // +08
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
    unsigned long value8;     // +08
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
static inline void advance_nodes(T* items, const int& count) {
    for (int i = 0; static_cast<unsigned int>(i) < static_cast<unsigned int>(count); ++i)
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

    unsigned long value0;             // +00
    unsigned char initialized;        // +08
    unsigned char pad9[3];
    int count0c;                      // +0c
    unsigned char pad10[8];
    EffectSlot slots_a[28];           // +18
    int count_a;                      // +478
    unsigned char pad47c[4];
    EffectSlot slots_b[28];           // +480
    int count_b;                      // +8e0
    unsigned char pad8e4[4];
    EffectMarker markers_c[28];       // +8e8
    int count_c;                      // +c68
    unsigned char padc6c[4];
    EffectMarker markers_d[28];       // +c70
    int count_d;                      // +ff0
    unsigned char padff4[4];
    EffectCaption captions[28];       // +ff8
    int count_e;                      // +11b8
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
    value0 = 0;
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
    value0 = 0;
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