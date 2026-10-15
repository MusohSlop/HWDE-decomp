// A popup panel's per-frame update (fourth session, template family 2bdbd4): PopupPanel::update counts its timer, steps its
// state (start the intro after the delay, wait for the node's animation, slide out and rewind) with each new state
// clearing the timer in one 64-bit store, then advances its effect node and updates it while the effect manager is
// active. The original has two identical copies (0x71002bdbd4, 0x71002c0348), written as one template with a dummy
// copy number; each copy's jump table is mapped by its COMDAT section. Names are descriptive placeholders.

#include "event/demo_effects.h"

// Reached through the GOT slots at 0x7100c22a28 and 0x7100c21df0.
extern float gFrameDelta;
extern unsigned int gResourceQueueElapsedStep;

unsigned char is_ready_1f7e3c(void* node);                                  // 0x71001f7e3c

struct EffectManagerFlags {
    unsigned char pad0[0x1290];
    void* active;             // +1290
};

class PopupPanel {
public:
    template <int Copy> void update();

    void set_state(int s) {
        state = s;
        timer = 0;
    }

    int state;                // +00
    int timer;                // +04
    int delay;                // +08
    unsigned char padc[4];
    LightEffectNode* node;    // +10
    LayoutAnimation* intro;   // +18
    unsigned char pad20[8];
    LayoutAnimation* outro;   // +28
};

template <int Copy>
void PopupPanel::update() {
    if (!state) return;
    int t = timer++;
    switch (state) {
    case 1:
        if (t >= delay) {
            intro->set_rate(gResourceQueueElapsedStep);
            set_state(2);
        }
        break;
    case 2:
        if (is_ready_1f7e3c(node)) set_state(5);
        break;
    case 3:
        if (is_ready_1f7e3c(node)) set_state(0);
        break;
    case 4:
        if (is_ready_1f7e3c(node)) {
            EffectGroup* g = node->group;
            g->offset34 += 60.0f;
            g->flags58 |= 0x10;
            if (outro) outro->rewind();
            set_state(5);
        }
        break;
    }
    node->advance(gFrameDelta);
    if (reinterpret_cast<EffectManagerFlags*>(gEffectManager)->active) {
        LightEffectNode* target = node;
        void* root = gEffectManager->current();
        target->update(root, 0);
    }
}

template void PopupPanel::update<0>();
template void PopupPanel::update<1>();
