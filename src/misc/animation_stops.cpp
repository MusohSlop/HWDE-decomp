// Animation-set stops found by tools/family_scan.py: each rewinds and deactivates five
// animations (the same shape as EffectRecord::stop, 0x71002695a8). Grouped here until their
// source files are linked; classes are named after the function address.
// Status: matching/README.md.

#include "event/demo_effects.h"

static inline void stop_animation(LayoutAnimation*& animation) {
    if (animation)
        animation->rewind();
    if (animation)
        animation->set_active(false);
}


// 0x7100289614
struct AnimationSet_289614 {
    void stop();

    void* owner;              // +00
    LayoutAnimation* anims[5]; // +08
};

void AnimationSet_289614::stop() {
    for (int i = 0; i < 5; ++i)
        stop_animation(anims[i]);
}


// 0x71002923c8
struct AnimationSet_2923c8 {
    void stop();

    void* owner;              // +00
    LayoutAnimation* anims[5]; // +08
};

void AnimationSet_2923c8::stop() {
    for (int i = 0; i < 5; ++i)
        stop_animation(anims[i]);
}


// 0x71003b58a8
struct AnimationSet_3b58a8 {
    void stop();

    void* owner;              // +00
    LayoutAnimation* anims[5]; // +08
};

void AnimationSet_3b58a8::stop() {
    for (int i = 0; i < 5; ++i)
        stop_animation(anims[i]);
}
