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

void hide_targets(TrackLightTarget* targets, unsigned int count);           // 0x71001f7530
int screen_width();                                                         // 0x71003df258
int screen_height();                                                        // 0x71003df250
unsigned int display_width();                                               // 0x71003cc930
unsigned int display_height();                                              // 0x71003cc94c

class TextRenderer {
public:
    void set_area(TrackVec2* pos, TrackVec2* size, int a, int b, int c);    // 0x71001e709c
    unsigned int draw(void* dest, const char* text, int line, int a, int alpha, float x,
                      float y);                                             // 0x71001e73c0
    unsigned int measure(const char* text, TrackVec2* size, TrackVec2* extent, float x,
                         float width);                                      // 0x71001e5e08

    unsigned char pad[0x20b98];
    unsigned long align;      // +20b98: horizontal and vertical alignment
    unsigned char pad20ba0[0x28];
    unsigned char right_to_left; // +20bc8
    unsigned char pad20bc9[0x23f];
    int justify;              // +20e08
};
// Reached through the GOT slot at 0x7100c22a30.
extern TextRenderer* gTextRenderer;

struct SharedState {
    int value0;
    int language;             // +04
};
SharedState* get_shared_state();                                            // 0x71002aae3c

const char* unit_name(int unit);                                            // 0x7100217d2c
const char* item_name(int item);                                            // 0x7100217d9c
void set_pane_lines(PanelPane* pane, TrackLightTarget* lines, unsigned int count); // 0x71001e41d8

struct TrackVec3 {
    float x, y, z;
};

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
    void draw();                                                            // 0x7100266f58
    void draw_text(int mode);                                               // 0x7100266f6c
    void draw_alternate();                                                  // 0x7100267308

    void* value0;                     // +00
    unsigned char initialized;        // +08
    unsigned char pad9[3];
    int value0c;                      // +0c
    int value10;                      // +10
    unsigned char pad14[4];
    TrackLightTarget lines[128];      // +18
    TrackLightTarget shadows[128];    // +4418
    unsigned int line_count;          // +8818
    unsigned int shadow_count;        // +881c
    PanelPane* right;                 // +8820
    PanelPane* left;                  // +8828
    LightEffectNode* node;            // +8830
    unsigned char pad8838[8];
    LightResource resources[2];       // +8840: layout, overlay
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
    gEffectManager->attach(&resources[0], nullptr);
    float width = screen_width();
    float height = screen_height();
    screen_w = width;
    screen_h = height;
    gEffectManager->attach_resource(&resources[1]);
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

void AdvCaption::draw() {
    if (initialized)
        draw_text(0);
}

void AdvCaption::draw_text(int mode) {
    if (!node)
        return;
    EffectGroup* group = node->group;
    TrackVec2 scale = *reinterpret_cast<TrackVec2*>(&group->scale48);
    TrackVec3 position = *reinterpret_cast<TrackVec3*>(&group->offset30);
    if (mode == 0 || mode == 1) {
    hide_targets(lines, 0x80);
    hide_targets(shadows, 0x80);
    line_count = 0;
    shadow_count = 0;
    TextRenderer* renderer = gTextRenderer;
    int language = get_shared_state()->language;
    int compact = language == 6 ? 1 : language;
    TrackVec2 pos;
    TrackVec2 size;
    TrackVec2 extent;
    if (static_cast<unsigned int>(value0c) <= 0xc7) {
        EffectGroup* font = group->find(kFontRight, 1);
        float scale_x = group->scale48;
        float scale_y = group->scale4c;
        float height = font->size54 * scale_y;
        float width = font->size50 * scale_x;
        pos.x = 0.0f;
        pos.y = 0.0f;
        size.x = height;
        size.y = height;
        if (!compact)
            pos.y = 7.0f;
        const char* text = unit_name(value0c);
        renderer->set_area(&pos, &size, 0x3c, 0x4b, 0);
        renderer->measure(text, &size, &extent, 0.0f, screen_width());
        extent.x = width + extent.x;
        renderer->align = 0x200000002ul;
        renderer->justify = 2;
        line_count = renderer->draw(lines, text, 0x80, 1, 0xff, 0.0f, 0.0f);
        for (int i = 0; static_cast<unsigned int>(i) < line_count; ++i)
            lines[i].hidden = 0;
    }
    if (static_cast<unsigned int>(value10) <= 0x363e) {
        EffectGroup* font = group->find(kFontLeft, 1);
        float height = font->size54 * group->scale4c;
        pos.x = 0.0f;
        pos.y = 0.0f;
        size.x = height;
        size.y = height;
        if (!compact)
            pos.y = 7.0f;
        float x = 1722.0f - extent.x;
        const char* text = item_name(value10);
        renderer->set_area(&pos, &size, 0x3c, 0x4b, 0);
        renderer->align = 2;
        if (compact)
            renderer->right_to_left = 1;
        unsigned int count = renderer->draw(shadows, text, 0x80, 1, 0xff, x, 0.0f);
        shadow_count = count;
        for (unsigned long i = 0; i < shadow_count; ++i)
            shadows[i].hidden = 0;
    }
    node->draw(0);
    set_pane_lines(right, lines, line_count);
    set_pane_lines(left, shadows, shadow_count);
    *reinterpret_cast<TrackVec3*>(&group->offset30) = position;
    *reinterpret_cast<TrackVec2*>(&group->scale48) = scale;
    group->flags58 |= 0x10;
    }
}

void AdvCaption::draw_alternate() {
    if (initialized)
        draw_text(1);
}