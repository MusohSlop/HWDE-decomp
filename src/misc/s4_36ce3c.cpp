// A fading window's per-frame update (fourth session, template family 36ce3c): FadeWindow::update advances and updates
// its effect node and steps its state when the node's animation is done (open, close, the next page). The original has
// two identical copies (0x710036ce3c, 0x710036f0dc), written as one template with a dummy copy number; each copy's jump
// table is mapped by its COMDAT section. Names are descriptive placeholders.

#include "event/demo_effects.h"

// Reached through the GOT slot at 0x7100c22a28.
extern float gFrameDelta;

unsigned char is_ready_1f7e3c(void* node);                                  // 0x71001f7e3c
void play_1f7a0c(void* anim, int group, int index, float rate);             // 0x71001f7a0c

class FadeWindow {
public:
    template <int Copy> void update();

    LightEffectNode* node;    // +0000
    unsigned char anim[0x1138];  // +0008
    int state;                // +1140
    unsigned char pad1144[4];
    unsigned char has_next;   // +1148
};

template <int Copy>
void FadeWindow::update() {
    node->advance(gFrameDelta);
    LightEffectNode* target = node;
    void* root = gEffectManager->current();
    target->update(root, 0);
    switch (state) {
    case 1:
        if (is_ready_1f7e3c(node)) {
            if (has_next) {
                play_1f7a0c(anim, 5, 2, 1.0f);
                state = 5;
            } else {
                state = 3;
            }
        }
        break;
    case 2:
    case 6:
        if (is_ready_1f7e3c(node)) state = 0;
        break;
    case 5:
        if (is_ready_1f7e3c(node)) {
            play_1f7a0c(anim, 5, 3, 1.0f);
            state = 3;
        }
        break;
    }
}

template void FadeWindow::update<0>();
template void FadeWindow::update<1>();
