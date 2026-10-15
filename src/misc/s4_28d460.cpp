// An icon panel's per-frame update (fourth session, 2-copy family 28d460): shows or hides the icon, then advances and
// updates both effect nodes, each node read before the effect manager's current() call. IconPanel::update<0>
// (0x710028d460) and update<1> (0x710037781c). Names are descriptive placeholders.

#include "event/demo_effects.h"

// Reached through the GOT slot at 0x7100c22a28.
extern float gFrameDelta;

struct IconRect28d460 {
    float x, y, w, h;
};
unsigned char icon_ready_1f4918(int id);                                     // 0x71001f4918
void* icon_table_1f4940(int id, IconRect28d460* rect);                      // 0x71001f4940
void apply_icon_1f7fe4(EffectGroup* group, void* handle, void* table, IconRect28d460* rect); // 0x71001f7fe4

static inline void step(LightEffectNode*& node) {
    node->advance(gFrameDelta);
    LightEffectNode* target = node;
    void* root = gEffectManager->current();
    target->update(root, 0);
}

class IconPanel {
public:
    template <int Copy> void update();

    LightEffectNode* back;    // +00
    LightEffectNode* front;   // +08
    unsigned char pad10[0x38];
    EffectGroup* icon;        // +48
    unsigned char pad50[0x1000];
    unsigned char handle[0x18];  // +1050
};

template <int Copy>
void IconPanel::update() {
    if (icon_ready_1f4918(0)) {
        IconRect28d460 rect;
        void* table = icon_table_1f4940(0, &rect);
        apply_icon_1f7fe4(icon, handle, table, &rect);
        icon->flags58 |= 1;
    } else {
        icon->flags58 &= ~1;
    }
    step(back);
    step(front);
}

// 0x710028d460
template void IconPanel::update<0>();
// 0x710037781c
template void IconPanel::update<1>();
