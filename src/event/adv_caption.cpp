// Matching candidates for the Adventure Mode caption bodies 0x7100266a20-0x7100266f04
// (adv_caption.bflyt). Names are descriptive placeholders. Status: matching/README.md.

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

int screen_width();                                                         // 0x71003df258
int screen_height();                                                        // 0x71003df250
unsigned int display_width();                                               // 0x71003cc930
unsigned int display_height();                                              // 0x71003cc94c

// Layout and pane names, merged with other literals by the linker.
extern const char kAdvCaptionLayout[] __attribute__((visibility("hidden")));   // 0x710074000f
extern const char kFontRight[] __attribute__((visibility("hidden")));       // 0x7100740072
extern const char kFontLeft[] __attribute__((visibility("hidden")));        // 0x7100740079
// Step of the resource queue, reached through the GOT slot at 0x7100c21df0.
extern unsigned int gResourceQueueElapsedStep;

class AdvCaption {
public:
    AdvCaption() {
        node = nullptr;
        initialized = 0;
        value0 = nullptr;
        step_bits = 0;
        value8a70 = 0;
        display_size = 0;
        screen_size = 0;
        value0c = -1;
        value10 = -1;
    }
    ~AdvCaption() { finalize(); }
    void finalize();                                                        // 0x7100266a20
    void initialize();                                                      // 0x7100266cd8
    void set_value0c(int value);                                            // 0x7100266ec0
    int get_value0c();                                                      // 0x7100266ed4
    void set_value10(int value);                                            // 0x7100266edc
    int get_value10();                                                      // 0x7100266ef0
    void clear_value10();                                                   // 0x7100266ef8
    void update();                                                          // 0x7100266f04

    void* value0;                     // +00
    unsigned char initialized;        // +08
    unsigned char pad9[3];
    int value0c;                      // +0c
    int value10;                      // +10
    unsigned char pad14[4];
    TrackLightTarget lines[128];      // +18
    TrackLightTarget shadows[128];    // +4418
    unsigned char pad8818[8];
    PanelPane* right;                 // +8820
    PanelPane* left;                  // +8828
    LightEffectNode* node;            // +8830
    unsigned char pad8838[8];
    LightResource resource;           // +8840
    LightResource overlay;            // +8950
    union {
        unsigned long screen_size;    // +8a60: cleared as one word
        struct {
            float screen_w;           // +8a60
            float screen_h;           // +8a64
        };
    };
    union {
        unsigned long display_size;   // +8a68
        struct {
            float display_w;          // +8a68
            float display_h;          // +8a6c
        };
    };
    unsigned long value8a70;          // +8a70
    union {
        int step_bits;                // +8a78
        float step;                   // +8a78
    };
    unsigned char pad8a7c[4];
};
static_assert(sizeof(AdvCaption) == 0x8a80, "caption size");

// Reached through the GOT slot at 0x7100c2a6b0.
extern AdvCaption* gAdvCaption;

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

void AdvCaption::finalize() {
    release_child(node);
    initialized = 0;
    value0 = nullptr;
    node = nullptr;
    value0c = -1;
    value10 = -1;
}

void create_adv_caption() {
    if (!gAdvCaption) {
        void* storage = get_default_heap()->allocate(0x10, sizeof(AdvCaption), 1, 0);
        gAdvCaption = new (storage) AdvCaption;
    }
}

void destroy_adv_caption() {
    if (gAdvCaption) {
        gAdvCaption->finalize();
        AdvCaption* caption = gAdvCaption;
        if (caption) {
            caption->~AdvCaption();
            get_default_heap()->release(caption, 1, 0);
        }
        gAdvCaption = nullptr;
    }
}

void AdvCaption::initialize() {
    if (initialized)
        return;
    gEffectManager->create_node(&node, 0x41e5, kAdvCaptionLayout);
    gEffectManager->sync();
    gEffectManager->attach(&resource, nullptr);
    float width = screen_width();
    float height = screen_height();
    screen_w = width;
    screen_h = height;
    gEffectManager->attach_resource(&overlay);
    float display_x = display_width();
    float display_y = display_height();
    display_w = display_x;
    display_h = display_y;
    right = new PanelPane;
    left = new PanelPane;
    node->group->find(kFontRight, 1)->add(right);
    node->group->find(kFontLeft, 1)->add(left);
    right->align = 2;
    left->align = 2;
    step = gResourceQueueElapsedStep;
    initialized = 1;
}

void AdvCaption::set_value0c(int value) {
    if (value0c != value)
        value0c = value;
}

int AdvCaption::get_value0c() {
    return value0c;
}

void AdvCaption::set_value10(int value) {
    if (value10 != value)
        value10 = value;
}

int AdvCaption::get_value10() {
    return value10;
}

void AdvCaption::clear_value10() {
    value10 = -1;
}

void AdvCaption::update() {
    if (initialized) {
        LightEffectNode* target = node;
        void* root = gEffectManager->current();
        target->update(root, 0);
    }
}
