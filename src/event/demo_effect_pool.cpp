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

struct EffectSlot {
    LightEffectNode* node;    // +00
    unsigned long value8;     // +08
    unsigned long value10;    // +10
    int index;                // +18
    int value1c;              // +1c
    int kind;                 // +20
    unsigned char pad24[4];

    void reset() {
        node = nullptr;
        value8 = 0;
        value10 = 0;
        index = -1;
        value1c = 0;
        kind = 0xd;
    }
};
static_assert(sizeof(EffectSlot) == 0x28, "slot size");

struct EffectMarker {
    LightEffectNode* node;    // +00
    unsigned long value8;     // +08
    int index;                // +10
    int value14;              // +14
    int kind;                 // +18
    unsigned char pad1c[4];

    void reset() {
        node = nullptr;
        value8 = 0;
        index = -1;
        value14 = 0;
        kind = 4;
    }
};
static_assert(sizeof(EffectMarker) == 0x20, "marker size");

struct EffectCaption {
    LightEffectNode* node;    // +00
    int value;                // +08
    unsigned char pad0c[4];
};

class DemoEffectPool {
public:
    DemoEffectPool();
    ~DemoEffectPool() { finalize(); }
    void initialize();
    void clear();
    void finalize();
    void update();
    void update_slots();                                                    // 0x7100261024
    void update_markers();                                                  // 0x7100261290

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
