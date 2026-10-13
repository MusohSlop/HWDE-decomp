// Matching candidates for the Adventure board popups (0x71002a6e88-0x71002aadac).
// Names are descriptive placeholders. Status: matching/README.md.

#include "event/demo_effects.h"
#include "event/demo_light_system.h"
#include "event/demo_track.h"

void hide_targets(TrackLightTarget* targets, unsigned int count);           // 0x71001f7530

static inline void* layout_root() {
    return gResourceLoader ? gResourceLoader->layout->root : nullptr;
}

// Layout handle; its vtable lives in the effect manager unit (GOT 0x7100c22f00).
class LayoutHandle {
public:
    virtual ~LayoutHandle() { release(layout_root()); }
    virtual void v10();
    virtual void release(void* root); // +18

    long id;                  // +08
    short a;                  // +10
    short b;                  // +12
};

class PopupNode {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void show(int visible);                                         // +20
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
    virtual void set_frame(float frame);                                    // +b0
    virtual void vb8();
    virtual void vc0();
    virtual void vc8();
    virtual void rewind();                                                  // +d0
};

struct PopupItem {
    EffectGroup* object;      // +00
    LayoutHandle handle;      // +08
};
static_assert(sizeof(PopupItem) == 0x20, "item size");

// The popup layout (0x2940 bytes), destroyed out of line (0x71002a6fd0).
class PopupTargets {
public:
    ~PopupTargets();                                                        // 0x71002a6fd0

    LightEffectNode* node;            // +00
    PopupNode* anim;                  // +08
    LightResource resource;           // +10
    PopupItem items[15];              // +120
    TrackLightTarget icons[24];       // +300
    TrackLightTarget labels[24];      // +fc0
    TrackLightTarget frames[24];      // +1c80
};
static_assert(sizeof(PopupTargets) == 0x2940, "popup targets size");

class BoardPopups {
public:
    void finalize();                                                        // 0x71002a6e88
    void reset();                                                           // 0x71002aadac

    void* value0;             // +00
    unsigned char flag8;      // +08
    unsigned char pad9[0x17];
    PopupTargets targets;     // +20
    unsigned char pad2960[0x19c0];
    LightEffectNode* overlay; // +4320
    long value4328;           // +4328
    unsigned char pad4330[0x23c];
    float frame;              // +456c
};

void BoardPopups::finalize() {
    EffectManager* manager = gEffectManager;
    if (targets.node) {
        void* root = gResourceLoader->layout->root;
        manager->unregister(manager->registry, 0x420d);
        targets.node->detach(root);
        targets.node->release();
        manager->children.remove(targets.node);
        targets.node = nullptr;
    }
    if (overlay) {
        EffectManager* manager = gEffectManager;
        void* root = gResourceLoader->layout->root;
        overlay->detach(root);
        overlay->release();
        manager->nodes.remove(overlay);
        overlay = nullptr;
    }
    targets.node = nullptr;
    for (int i = 0; i < 15; ++i)
        targets.items[i].object = nullptr;
    hide_targets(targets.frames, 24);
    hide_targets(targets.icons, 24);
    hide_targets(targets.labels, 24);
    flag8 = 0;
    value0 = nullptr;
    overlay = nullptr;
    value4328 = 0;
}

void BoardPopups::reset() {
    if (targets.anim)
        targets.anim->rewind();
    targets.anim->set_frame(frame);
    if (targets.anim)
        targets.anim->show(1);
}
