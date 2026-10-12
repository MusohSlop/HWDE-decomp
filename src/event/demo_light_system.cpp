// Matching candidates for the demo light system bodies 0x710025dc08-0x710025e4d0.
// Names are descriptive placeholders. Status: matching/README.md.

#include "event/demo_light_system.h"
#include "event/demo_sequence.h"

inline void* operator new(unsigned long, void* where) noexcept { return where; }

class HeapCore {
public:
    virtual void v00();

private:
    unsigned char data[0xa8];
};

// The allocator interface is a base at +0xb0.
class DefaultHeap : public HeapCore, public DemoOwner {
public:
    void* allocate(unsigned int alignment, unsigned long size, int a, int b); // 0x710045c458
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

unsigned char resource_queue_cancelled();                                   // 0x71002589c0

class EffectBase {
public:
    static void* operator new(unsigned long size) noexcept;                 // 0x71005d4380
    EffectBase();                                                           // 0x71005d9690
    virtual ~EffectBase();

private:
    unsigned char data[0xd4];
};

class LightEffect : public EffectBase {
public:
    LightEffect() : mode(0x10) {}
    virtual void v10();

    int mode;                 // +dc
};

class EffectGroup {
public:
    void add(EffectBase* effect);                                           // 0x71005da17c
};

class LightEffectNode {
public:
    virtual void v00();
    virtual void release();
    virtual void v10();
    virtual void v18();
    virtual void v20();
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
    virtual void update(void* context, int mode); // +90
    void detach(void* root);                                                // 0x71005d4408

    unsigned char pad8[0x10];
    EffectGroup* group;       // +18
};

class EffectList {
public:
    void remove(LightEffectNode* node);                                     // 0x71005c3774
};

class EffectManager {
public:
    void create_node(LightEffectNode** out, int id, const char* layout);    // 0x71001e2360
    void attach(LightResource* resource, void* owner);                      // 0x71001e26dc
    void* current();                                                        // 0x71001e26ec

    unsigned char pad[0x68];
    EffectList nodes;         // +68
};
// Reached through the GOT slot at 0x7100c22a00.
extern EffectManager* gEffectManager;

class CaptionLayer {
public:
    void refresh(int mode);                                                 // 0x71001de418
    void show(int frames, int mode);                                        // 0x71001de2ec

    unsigned char pad[0x10];
    int value10;              // +10
    unsigned char pad14[4];
    unsigned char flag18;     // +18
    unsigned char pad19[7];
    unsigned char hidden;     // +20
};
// Reached through the GOT slot at 0x7100c22ef8.
extern CaptionLayer* gCaptionLayer;

struct LayoutRoot {
    unsigned char pad[0x10];
    unsigned char root[1];    // +10
};
struct ResourceLoaderView {
    unsigned char pad[0x2af8];
    LayoutRoot* layout;       // +2af8
};
// Reached through the GOT slot at 0x7100c21db0.
extern ResourceLoaderView* gResourceLoader;

class LightPreset {
public:
    unsigned int count();                                                   // 0x71001a8d7c
    int value(int index);                                                   // 0x71001a8d3c
    int mode();                                                             // 0x71001a8d1c
    int track();                                                            // 0x71001a8d9c
};
LightPreset* current_light_preset();                                        // 0x71001a8c38

class StageLights {
public:
    void* lookup(int value);                                                // 0x71001fb23c
};
// Reached through the GOT slot at 0x7100c21df8.
extern StageLights* gStageLights;

void* make_light_list(unsigned int count);                                  // 0x71001f4e70
void* make_light_object(void* source);                                      // 0x71001f4ee0
void* retain_light(void* object);                                           // 0x71001f7868
void release_light(void** slot);                                            // 0x71001f7960
void notify_lights_loaded(int stage);                                       // 0x71003ff128
void notify_lights_unloaded();                                              // 0x71003ff140

extern unsigned int gResourceQueueElapsedStep;
// Frames per second, reached through the GOT slot at 0x7100c22d50.
extern float gFrameRate;

unsigned long get_system_tick();            // 0x71006009e0 (nn::os::GetSystemTick)
unsigned long get_system_tick_frequency();  // 0x71006009f0 (nn::os::GetSystemTickFrequency)

class SharedState;
SharedState* get_shared_state();                                            // 0x71002aae3c

class SharedResources {
public:
    unsigned char busy();                                                   // 0x710038863c
    void request(int id, int a, int b);                                     // 0x7100389178
    void release_caption(int mode);                                         // 0x71003891d0
};
SharedResources* shared_state_resources(SharedState* state);               // 0x71002ad1dc

struct GameFlags {
    unsigned char bytes[4];
};
GameFlags* game_flags();                                                    // 0x710016ef34

class InputDevice {
public:
    unsigned int buttons(int port);                                         // 0x710045d620
};
InputDevice* input_device();                                                // 0x710045ceb4

class Fader {
public:
    void fade(float duration, int mode, int flags);                         // 0x71001e526c
};
Fader* screen_fader();                                                      // 0x71001e50b0

class BgmPlayer {
public:
    virtual void v00();
    virtual void v08();
    virtual void play(int track);                                           // +10
};
BgmPlayer* bgm_player();                                                    // 0x710020dfd0
int bgm_length();                                                           // 0x710020d954

class Sequencer {
public:
    void advance(int a, int b);                                             // 0x71003df5e4
};
// Reached through the GOT slot at 0x7100c21880.
extern Sequencer* gSequencer;

void play_demo_fade(int a, int b, int c, void* d, float duration);          // 0x71003f9b34
void finish_demo_fade(int mode);                                            // 0x71003fa088
void notify_light_index(int index, int* out);                               // 0x71003ff164
void notify_light_skipped();                                                // 0x71003fe254
void notify_light_aborted(int index);                                       // 0x71003fe2d4
unsigned char demo_skipping();                                              // 0x71003cbe20

// String literals, merged with others by the linker.
extern const char kEmptyString[] __attribute__((visibility("hidden")));    // 0x7100740512
extern const char kCaptionLayout[] __attribute__((visibility("hidden")));  // 0x7100741e21

DemoLightSystem::DemoLightSystem()
    : block(nullptr), scene(), stage(-1), initialized(0), loaded(0), object7278(nullptr),
      object7280(nullptr), name(nullptr), timer7290(0), timer7294(0), time(0), start_time(0),
      time99d8(0), end_time(0), state(-1), value99e4(0), index99e8(-1), flags99ec(), speed(0), effect(nullptr) {
    value9b20 = 0;
    flag9b24 = 0;
    tick = 0;
    last_tick = 0;
    last_delta = -1.0f;
    flag9b27 = 0;
    flag9b25 = 0;
    flag9b26 = 0;
}

void create_demo_light_system() {
    if (!gDemoLightSystem) {
        void* storage = get_default_heap()->allocate(0x10, sizeof(DemoLightSystem), 1, 0);
        gDemoLightSystem = new (storage) DemoLightSystem;
    }
}

void destroy_demo_light_system() {
    DemoLightSystem* system = gDemoLightSystem;
    if (system) {
        system->~DemoLightSystem();
        get_default_heap()->release(system, 1, 0);
        gDemoLightSystem = nullptr;
    }
}

void DemoLightSystem::initialize() {
    if (initialized)
        return;
    state = 0;
    value99e4 = 0;
    time99d8 = 0;
    end_time = 0;
    time = 0;
    start_time = 0;
    index99e8 = -1;
    flags99ec.a = 0;
    flags99ec.b = 0;
    flags99ec.c = 0;
    flags99ec.index = -1;
    speed = 0;
    flag9b24 = 0;
    timer7290 = 0;
    timer7294 = 0;
    name = kEmptyString;
    value99f8 = 0;
    tick = 0;
    last_tick = 0;
    last_delta = -1.0f;
    block = get_default_heap()->allocate(0x10, 0x30000, 1, 0);
    allocator.init(block, 0x30000, 4, 4, 0x10);
    table_set.init(&allocator);
    scene.init(&allocator);
    scene.flag5914 = 0;
    scene.flag591c = 0;
    scene.flag5ba8 = 0;
    new (&key) TrackKey(&allocator);
    EffectManager* manager = gEffectManager;
    manager->create_node(&effect, 0x41e5, kCaptionLayout);
    gEffectManager->attach(&resource, nullptr);
    EffectGroup* group = effect->group;
    group->add(new LightEffect);
    initialized = 1;
    sources[0].flags |= 0x80;
    sources[1].flags |= 0x80;
    sources[2].flags |= 0x80;
    object7280 = nullptr;
    object7278 = nullptr;
}

void DemoLightSystem::finalize() {
    key.finalize();
    scene.finalize();
    table_set.finalize();
    allocator.finalize();
    void* storage = block;
    if (storage) {
        get_default_heap()->release(storage, 1, 0);
        block = nullptr;
    }
    CaptionLayer* caption = gCaptionLayer;
    if (caption) {
        caption->hidden = 1;
        caption->refresh(1);
    }
    if (effect) {
        EffectManager* manager = gEffectManager;
        effect->detach(gResourceLoader->layout->root);
        effect->release();
        manager->nodes.remove(effect);
        effect = nullptr;
    }
    initialized = 0;
}

void DemoLightSystem::load(int stage_) {
    if (loaded)
        return;
    stage = stage_;
    if (static_cast<unsigned int>(stage_) > 0x3b)
        return;
    void* scratch = static_cast<DemoOwner&>(*get_default_heap()).alloc(0xa00000, AllocDescriptor(0x2e));
    scene.load(1, stage_);
    LightPreset* preset = current_light_preset();
    unsigned int count = preset->count();
    object7278 = retain_light(make_light_list(count < 100 ? count : 0));
    name = static_cast<const char*>(scene.environment());
    int value = preset->value(0);
    object7280 = retain_light(make_light_object(gStageLights->lookup(value)));
    table_set.load(stage_, &time);
    key.load(stage_);
    notify_lights_loaded(stage_);
    loaded = 1;
    static_cast<DemoOwner&>(*get_default_heap()).free(scratch);
    if (resource_queue_cancelled())
        stage = -1;
}

void DemoLightSystem::unload() {
    release_light(&object7278);
    object7278 = nullptr;
    release_light(&object7280);
    object7280 = nullptr;
    notify_lights_unloaded();
    key.unload();
    scene.unload();
    table_set.unload();
    loaded = 0;
}

void DemoLightSystem::update() {
    speed = gResourceQueueElapsedStep * 2.0f;
    if (static_cast<unsigned int>(stage) > 0x3b)
        return;
    LightEffectNode* node = effect;
    if (node) {
        void* context = gEffectManager->current();
        node->update(context, 0);
    }
    switch (state) {
    case 0:
        start();
        break;
    case 1:
        if (timer7290 >= 138.0f) {
            state = 2;
            timer7290 = 0;
            last_tick = get_system_tick();
            tick = get_system_tick();
        }
        timer7290 += 1.0f;
        break;
    case 2:
        play();
        break;
    case 3:
    case 4:
    case 5:
    case 7:
    case 8:
        state = 9;
        break;
    case 6:
        shared_state_resources(get_shared_state());
        current_light_preset();
        state = 9;
        break;
    case 9:
        if (SharedResources* resources = shared_state_resources(get_shared_state())) {
            resources->release_caption(0);
            gCaptionLayer->refresh(0);
            gCaptionLayer->value10 = -1;
            gCaptionLayer->flag18 = 0;
        }
        state = !(time >= end_time) ? 11 : 10;
        break;
    case 10:
        if (timer7294 >= 36.0f) {
            state = 11;
            timer7294 = 0;
        }
        timer7294 += 1.0f;
        break;
    case 11:
        finish();
        break;
    }
    if (flags99ec.c || flags99ec.b)
        return;
    int index = scene.current_index;
    if (index99e8 == index)
        return;
    if (index >= 0 && state == 2)
        notify_light_index(index, &flags99ec.index);
    index99e8 = index;
}

void DemoLightSystem::start() {
    shared_state_resources(get_shared_state());
    if (!(game_flags()->bytes[3] & 4)) {
        play_demo_fade(2, 1, 0, nullptr, 0.668f);
        state = 1;
        return;
    }
    int track = current_light_preset()->track();
    bgm_player()->play(track);
    int frames = bgm_length() + 100;
    gCaptionLayer->show(frames, 0);
    gCaptionLayer->value10 = -1;
    notify_lights_loaded(stage);
    time = start_time;
    flags99ec.b = 0;
    state = 3;
    if (screen_fader() && screen_fader())
        screen_fader()->fade(0.25f, 0, 1);
}

void DemoLightSystem::play() {
    SharedResources* resources = shared_state_resources(get_shared_state());
    unsigned int buttons = input_device()->buttons(0);
    scene.advance(time, speed);
    unsigned char& aborting = flags99ec.d;
    if ((buttons & 8) && !aborting) {
        if (resources) {
            if (!resources->busy()) {
                notify_light_skipped();
                scene.stop();
                state = 9;
                return;
            }
        } else {
            notify_light_skipped();
            flags99ec.c = 1;
            aborting = 0;
            if (screen_fader() && screen_fader())
                screen_fader()->fade(0.0f, 1, 1);
            scene.stop();
            time = end_time;
        }
    }
    if (resources && !aborting && !resources->busy())
        resources->request(0x49, 0, 0);
    if (time >= end_time) {
        time = end_time;
        scene.stop();
        state = 9;
        if (aborting) {
            aborting = 0;
            notify_light_aborted(flags99ec.index);
            finish_demo_fade(0);
        }
        return;
    }
    tick = get_system_tick();
    float delta = static_cast<double>(tick - last_tick) / static_cast<double>(get_system_tick_frequency());
    if (delta > 1.0f) {
        last_tick = tick;
        return;
    }
    float frames;
    if (delta > 0.0f) {
        if (last_delta < 0.0f)
            frames = delta / (1.0f / gFrameRate);
        else
            frames = (delta + last_delta) * 0.5f / (1.0f / gFrameRate);
    } else {
        frames = 0.0f;
    }
    if (aborting)
        return;
    float t = time + frames * speed;
    t = t < 0.0f ? 0.0f : t;
    time = t > end_time ? end_time : t;
    if (delta > 0.0f) {
        last_tick = tick;
        last_delta = delta;
    }
}

void DemoLightSystem::finish() {
    if (flags99ec.a) {
        flags99ec.b = 1;
        notify_lights_unloaded();
        LightPreset* preset = current_light_preset();
        if (preset && !demo_skipping() && (game_flags()->bytes[1] & 8) && start_time >= 0.0f &&
            preset->mode() == 2)
            gSequencer->advance(1, 1);
    }
    if (screen_fader() && screen_fader())
        screen_fader()->fade(0.0f, 0, 1);
}