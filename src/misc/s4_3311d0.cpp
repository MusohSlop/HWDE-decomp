// A scene's per-frame update (fourth session, template family 3311d0): two scene classes share one inline template that
// ticks the scene (its single or normal mode), advances its effect node by the frame delta, counts its frame counter up
// to 1000 and draws its view: Scene3311d0::update (0x71003311d0) and Scene39a9f4::update (0x710039a9f4). Names are
// descriptive placeholders.

#include "event/demo_effects.h"

// Reached through the GOT slot at 0x7100c22a28.
extern float gFrameDelta;

struct SceneView {
    void set_view(int a, int b, int c);                                     // 0x710037dd20
    void draw(void* scene);                                                 // 0x710037f5f8
};

struct SceneBase {
    int active;               // +00
    int mode;                 // +04
    unsigned char pad8[4];
    int counter;              // +0c
    int view_c;               // +10
    int view_a;               // +14
    int view_b;               // +18
    unsigned char pad1c[4];
    LightEffectNode* node;    // +20
    unsigned char pad28[8];
    unsigned char scene[0x183d8];  // +30
    SceneView view;           // +18408
    unsigned char pad18409[0x33];
    unsigned char enabled;    // +1843c
};

template <class T>
static inline void update_scene(T* s) {
    if (!s->enabled) return;
    if (!s->active) return;
    if (s->mode == 1) s->tick_single();
    else s->tick();
    if (s->node) {
        s->node->advance(gFrameDelta);
        LightEffectNode* target = s->node;
        void* root = gEffectManager->current();
        target->update(root, 0);
    }
    if (s->counter != -1 && s->counter <= 999) s->counter++;
    s->view.set_view(s->view_a, s->view_b, s->view_c);
    s->view.draw(s->scene);
}

struct Scene3311d0 : SceneBase {
    void update();
    void tick_single();                                                     // 0x71003312b8
    void tick();                                                            // 0x71003315b8
};

// 0x71003311d0
void Scene3311d0::update() {
    update_scene(this);
}

struct Scene39a9f4 : SceneBase {
    void update();
    void tick_single();                                                     // 0x710039aadc
    void tick();                                                            // 0x710039ae10
};

// 0x710039a9f4
void Scene39a9f4::update() {
    update_scene(this);
}
