// Large screen destructors written by hand (third session): handles stopped, node groups taken off their parents,
// light effect nodes released, slots cleared. Names are descriptive placeholders. Status: matching/README.md.

#include "event/demo_effects.h"

struct Part5d27b4 { ~Part5d27b4(); unsigned char data[0x10]; };   // 0x71005d27b4

class Base316aa4 {
public:
    virtual ~Base316aa4();       // 0x7100316aa4
    unsigned char pad8[0x38];
};

// A sound or effect handle stopped when the screen closes; its destructor stops it too.
struct Cue1f8724 {
    ~Cue1f8724();                // 0x71001f8720
    void stop();                 // 0x71001f8724
    unsigned char data[0xa0];
};

struct Part33c82c {
    ~Part33c82c();               // 0x710033c82c
    unsigned char data[0x154b8];
};

// A group's parent sits at +18 of the group.
struct GroupLink {
    unsigned char pad0[0x18];
    struct ParentGroup* parent;  // +18
};
struct ParentGroup {
    void remove(EffectGroup* group);                                        // 0x71005da1b0
};

static inline void detach_group(LightEffectNode* node) {
    if (node) {
        GroupLink* link = reinterpret_cast<GroupLink*>(node->group);
        if (link->parent)
            link->parent->remove(node->group);
    }
}

static inline void release_plain(LightEffectNode*& node) {
    if (node) {
        EffectManager* manager = gEffectManager;
        node->detach(gResourceLoader->layout->root);
        node->release();
        manager->nodes.remove(node);
        node = nullptr;
    }
}

// A slot of the screen: cleared when it goes.
struct Slot304788 {
    ~Slot304788() { clear(); }
    void clear();                // 0x7100301e78

    LightEffectNode* node;       // +00
    unsigned char pad8[0x6228];
};

// The last slot: its node's group leaves its parent and the node is released when it goes.
struct LastSlot304788 {
    ~LastSlot304788() {
        detach_group(node);
        release_plain(node);
    }

    LightEffectNode* node;       // +00
    unsigned char pad8[0x90];
};

// 0x7100304788 (D2): vtable GOT 0x7100c2acb0; cues and voices stopped in pairs, icons and frames taken off the
// three groups and released, the slots' groups off their parents and the slots cleared, the tabs released.
class Screen304788 : public Base316aa4 {
public:
    void anchor();
    ~Screen304788();

    Part5d27b4 m40;              // +40
    unsigned char pad50[0x100];
    LightEffectNode* tabs[3];    // +150
    LightEffectNode* icons[3];   // +168
    LightEffectNode* frames[3];  // +180
    unsigned char pad198[0xa8];
    ParentGroup* groups[3];      // +240
    unsigned char pad258[0x6b20];
    Slot304788 slots[3];         // +6d78
    LastSlot304788 last;         // +19408
    Part33c82c part194a0;        // +194a0
    Cue1f8724 cues[3];           // +2e958
    Cue1f8724 voices[3];         // +2eb38
};

Screen304788::~Screen304788() {
    for (int i = 0; i < 3; i++) {
        cues[i].stop();
        voices[i].stop();
    }
    for (int i = 0; i < 3; i++)
        groups[i]->remove(icons[i]->group);
    for (int i = 0; i < 3; i++)
        groups[i]->remove(frames[i]->group);
    for (int i = 0; i < 3; i++) {
        release_plain(icons[i]);
        release_plain(frames[i]);
    }
    for (int i = 0; i < 3; i++) {
        detach_group(slots[i].node);
        slots[i].clear();
    }
    detach_group(last.node);
    for (int i = 0; i < 3; i++)
        release_plain(tabs[i]);
}
