// Page and screen constructors written by hand (third session): nodes created by page ids, animations and panes
// looked up through the effect manager's API. Names are descriptive placeholders. Status: matching/README.md.

#include "event/demo_effects.h"

void* load_global_334a04();                                 // 0x7100334a04
struct PageOverride;
// Reached through the GOT slot at 0x7100c22da8.
extern PageOverride* gPageOverride;

inline bool page_ids() { return !load_global_334a04() && !gPageOverride; }

extern const char gLayout39ec78[] __attribute__((visibility("hidden")));     // 0x71007db10c
extern const char gTitle39ec78[] __attribute__((visibility("hidden")));      // 0x71007d6079
extern const char gAnimIn39ec78[] __attribute__((visibility("hidden")));     // 0x710073fffb
extern const char gAnimLoop39ec78[] __attribute__((visibility("hidden")));   // 0x710074056c
extern const char gAnimSel39ec78[] __attribute__((visibility("hidden")));    // 0x71007db16e
extern const char gPaneA39ec78[] __attribute__((visibility("hidden")));      // 0x71007db11f
extern const char gPaneB39ec78[] __attribute__((visibility("hidden")));      // 0x71007db128
extern const char gPaneC39ec78[] __attribute__((visibility("hidden")));      // 0x71007db138
extern const char gPaneD39ec78[] __attribute__((visibility("hidden")));      // 0x71007db178
extern const char gAnimOut39ec78[] __attribute__((visibility("hidden")));    // 0x71007d6062
extern const char gAnimWait39ec78[] __attribute__((visibility("hidden")));   // 0x710074053d
extern const char gAnimOn39ec78[] __attribute__((visibility("hidden")));     // 0x71007d5b89
extern const char gAnimOff39ec78[] __attribute__((visibility("hidden")));    // 0x71007d5b94
extern const char gPaneE39ec78[] __attribute__((visibility("hidden")));      // 0x71007db187

class AnimPlayer {
public:
    void set_speed(float speed);                                            // 0x71001e4570
};

struct AnimHandle {
    unsigned char pad0[0x18];
    AnimPlayer* player;          // +18
};

class PanelNode : public LightEffectNode {
public:
    AnimHandle* create_animation_3770(const char* name, bool loop);         // 0x71001e3770
};

// 3a43c4's base (vtable GOT 0x7100c2b2b0), constructed out of line.
class Base3aab84 {
public:
    Base3aab84(int id, int alt_id, const char* layout, const char* title, int mode);   // 0x710039d3fc
    virtual ~Base3aab84();

    PanelNode* node;             // +08
    AnimHandle* anim10;          // +10
    AnimHandle* anim18;          // +18
    void* p20;                   // +20
    AnimHandle* anim28;          // +28
    AnimHandle* anim30;          // +30
    unsigned char pad38[0x22c0];
    int count22f8;               // +22f8
    int id22fc;                  // +22fc
    int id2300;                  // +2300
    unsigned char pad2304[0x18];
    unsigned char active;        // +231c
};

// 0x710039ec78: a node page (vtable GOT 0x7100c2b2c8; destroyed at 0x710039ef38).
class Page39ec78 : public Base3aab84 {
public:
    Page39ec78();
    void v10();
    ~Page39ec78();

    LightEffectNode* page_node;  // +2320
    AnimHandle* anim2328;        // +2328
    AnimHandle* anim2330;        // +2330
    AnimHandle* anim2338;        // +2338
    AnimHandle* anim2340;        // +2340
    AnimHandle* anim2348;        // +2348
    unsigned char pad2350[0x10];
    EffectGroup* group2360;      // +2360
    EffectGroup* group2368;      // +2368
    bool flag2370;               // +2370
    int i2374;                   // +2374
    int i2378;                   // +2378
    int i237c;                   // +237c
};

Page39ec78::Page39ec78()
    : Base3aab84(0x4202, 0x41f3, gLayout39ec78, gTitle39ec78, 0), page_node(nullptr), i2374(0), i2378(15), i237c(0) {
    PanelNode* n = node;
    if (page_ids()) {
        gEffectManager->create_node(&page_node, 0x4202, gLayout39ec78);
        gEffectManager->sync();
    } else {
        gEffectManager->create_node(&page_node, 0x41f3, gLayout39ec78);
        gEffectManager->flush();
    }
    anim2328 = n->create_animation_3770(gAnimIn39ec78, false);
    anim2330 = n->create_animation_3770(gAnimLoop39ec78, false);
    anim2338 = n->create_animation_3770(gAnimSel39ec78, false);
    anim2338->player->set_speed(n->group->scale48);
    n->group->find(gPaneA39ec78, 1)->flags58 &= ~1;
    n->group->find(gPaneB39ec78, 1)->flags58 &= ~1;
    n->group->find(gPaneC39ec78, 1)->flags58 &= ~1;
    n->group->find(gPaneD39ec78, 1)->flags58 &= ~1;
    gEffectManager->flush();
    anim10 = node->create_animation_3770(gAnimIn39ec78, false);
    anim18 = node->create_animation_3770(gAnimOut39ec78, false);
    anim28 = node->create_animation_3770(gAnimWait39ec78, false);
    anim30 = node->create_animation_3770(gAnimLoop39ec78, false);
    anim2340 = n->create_animation_3770(gAnimOn39ec78, true);
    anim2348 = n->create_animation_3770(gAnimOff39ec78, true);
    group2368 = n->group->find(gPaneE39ec78, 1);
    group2360 = n->group->find(gPaneD39ec78, 1);
    count22f8 = 15;
    flag2370 = false;
}
