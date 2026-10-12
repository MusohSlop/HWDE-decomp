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
    void* object;             // +00
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
    void* object269e0;                // +269e0
    PanelItem extras[4];              // +269e8
};
static_assert(sizeof(PanelTargets) == 0x26a68, "targets size");

PanelTargets::PanelTargets() {}

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

    void* value0;                     // +00
    unsigned char flag8;              // +08
    unsigned char flag9;              // +09
    unsigned char pada[2];
    int value0c;                      // +0c
    int value10;                      // +10
    int value14;                      // +14
    unsigned char flag18;             // +18
    unsigned char pad19[3];
    int value1c;                      // +1c
    unsigned char flag20;             // +20
    unsigned char pad21[0xf];
    PanelTargets targets;             // +30
    unsigned char pad26a98[0x70];
    PanelLink link26b08;              // +26b08
    void* value26b20;                 // +26b20
    void* value26b28;                 // +26b28
    void* value26b30;                 // +26b30
    void* value26b38;                 // +26b38
    LightEffectNode* node26b40;       // +26b40
    LightEffectNode* node26b48;       // +26b48
    void* value26b50;                 // +26b50
    unsigned char pad26b58[0x10];
    union {
        PanelLink link26b68;          // +26b68
        struct {
            LightEffectNode* node26b68;
            void* value26b70;
            int value26b78;
        };
    };
};
static_assert(sizeof(DemoPanelSystem) == 0x26b80, "system size");

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
    targets.object269e0 = nullptr;
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
    link26b68.reset();
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
    release_node(node26b68, 0x420d);
    flag8 = 0;
    value0 = nullptr;
    node26b68 = nullptr;
    value26b70 = nullptr;
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
