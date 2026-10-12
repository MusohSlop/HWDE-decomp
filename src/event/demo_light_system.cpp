// Matching candidates for the demo light system bodies 0x710025dc08-0x710025e4d0.
// Names are descriptive placeholders. Status: matching/README.md.

#include "event/demo_effects.h"
#include "event/demo_light_system.h"

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
    unsigned char captioned();                                              // 0x71003890bc
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

    unsigned char pad[0x204];
    unsigned char fading;     // +204
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

class TextRenderer {
public:
    void set_area(TrackVec2* pos, TrackVec2* size, int a, int b, int c);    // 0x71001e709c
    unsigned int draw(void* dest, const char* text, int line, int a, int alpha, float x,
                      float y);                                             // 0x71001e73c0

    unsigned int measure(const char* text, TrackVec2* size, TrackVec2* extent, float x,
                         float width);                                      // 0x71001e5e08

    unsigned char pad[0x20b7c];
    int mode20b7c;            // +20b7c
    unsigned char pad20b80[0xc];
    int mode20b8c;            // +20b8c
    unsigned char pad20b90[8];
    int mode20b98;            // +20b98
    int mode20b9c;            // +20b9c
    unsigned char pad20ba0[0x29];
    unsigned char flag20bc9;  // +20bc9
    unsigned char flag20bca;  // +20bca
};
// Reached through the GOT slot at 0x7100c22a30.
extern TextRenderer* gTextRenderer;

class TrackRenderer {
public:
    void write(void* data, unsigned int size, int slot);                    // 0x71001df8c0
    void flush(int slot);                                                   // 0x71001df128
    void begin(int mode);                                                   // 0x71001df744
    void end();                                                             // 0x71001df838
};
// Reached through the GOT slot at 0x7100c22a40.
extern TrackRenderer* gTrackRenderer;

int screen_width();                                                         // 0x71003df258
int screen_height();                                                        // 0x71003df250
const char* message_text(int id);                                           // 0x7100217d64
float lerp_float(float from, float to, float t);                            // 0x71001f6b40
int lerp_int(int from, int to, int frame, int frames);                      // 0x71001f6b50
void play_demo_sound(int id, int a, void* b, int c, float volume, float pan, float pitch); // 0x71003fbe44

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
    group->add(new LightEffect(0x10));
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

void DemoLightSystem::draw() {
    if (static_cast<unsigned int>(stage) > 0x3b)
        return;
    switch (state) {
    case 1:
        draw_intro();
        break;
    case 6:
    case 9:
    case 11:
        break;
    case 10:
        layout_panel();
        break;
    default:
        layout_frames();
        layout_panel();
        draw_text();
        break;
    }
}

void DemoLightSystem::layout_frames() {
    TrackLightTable* frames = static_cast<TrackLightTable*>(object7278);
    if (frames && state == 2) {
        sources[0].image = frames->count >= 1 ? frames->items[0] : nullptr;
        sources[0].uv0.x = 0.0f;
        sources[0].uv0.y = 0.0f;
        sources[0].uv1.x = 0.9375f;
        sources[0].uv1.y = 0.52734375f;
        sources[0].min.x = 0.0f;
        sources[0].min.y = 0.0f;
        sources[0].max.x = 1920.0f;
        sources[0].max.y = 1080.0f;
        sources[0].flags &= ~0x80u;
    } else {
        sources[0].flags |= 0x80;
    }
    TrackLightTable* logo = static_cast<TrackLightTable*>(object7280);
    if (logo && state == 2) {
        sources[1].image = logo->count >= 1 ? logo->items[0] : nullptr;
        sources[1].uv0.x = 0.0f;
        sources[1].uv0.y = 0.0f;
        sources[1].uv1.x = 0.5859375f;
        sources[1].uv1.y = 0.933852136f;
        sources[1].min.x = 780.0f;
        sources[1].max.y = 1020.0f;
        sources[1].min.y = 60.0f;
        sources[1].max.x = 1980.0f;
        sources[1].flags &= ~0x80u;
    } else {
        sources[1].flags |= 0x80;
    }
    float half_width = screen_width() * 0.5f;
    float half_height = screen_height() * 0.5f;
    TrackLightTarget& banner = table_set.banner;
    banner.hidden = 0;
    banner.blend = 0;
    banner.alpha = 1.0f;
    banner.quad[0].x = half_width - 1024.0f;
    banner.quad[0].y = half_height - 512.0f;
    banner.quad[1].x = half_width + 1024.0f;
    banner.quad[1].y = half_height - 512.0f;
    banner.quad[2].x = half_width - 1024.0f;
    banner.quad[2].y = half_height + 512.0f;
    banner.quad[3].x = half_width + 1024.0f;
    banner.quad[3].y = half_height + 512.0f;
    banner.value18[0] = 0.0f;
    banner.value18[1] = 0.0f;
    banner.matrix[0] = 1.0f;
    banner.matrix[1] = 0.0f;
    banner.matrix[2] = 0.0f;
    banner.matrix[3] = 1.0f;
    banner.scale[0] = 1.0f;
    banner.scale[1] = 1.0f;
}

void DemoLightSystem::layout_panel() {
    SharedResources* resources = shared_state_resources(get_shared_state());
    if ((resources && resources->captioned()) || flags99ec.d) {
        TrackLightTable* table = static_cast<TrackLightTable*>(table_set.resources.primary);
        float width = screen_width();
        float height = screen_height();
        TrackLightTarget& panel = table_set.panel;
        panel.hidden = 0;
        panel.blend = 0;
        panel.quad[0].x = 0.0f;
        panel.quad[0].y = 0.0f;
        panel.quad[1].x = width;
        panel.quad[1].y = 0.0f;
        panel.quad[2].x = 0.0f;
        panel.quad[2].y = height;
        panel.quad[3].x = width;
        panel.quad[3].y = height;
        panel.value18[0] = 0.0f;
        panel.value18[1] = 0.0f;
        panel.matrix[0] = 1.0f;
        panel.matrix[1] = 0.0f;
        panel.matrix[2] = 0.0f;
        panel.matrix[3] = 1.0f;
        panel.scale[0] = 1.0f;
        panel.scale[1] = 1.0f;
        panel.colors[0].r = 0;
        panel.colors[0].g = 0;
        panel.colors[0].b = 0;
        panel.colors[0].a = 0x1e;
        panel.colors[1] = panel.colors[0];
        panel.colors[2] = panel.colors[0];
        panel.colors[3] = panel.colors[0];
        panel.image = table->count >= 3 ? table->items[2] : nullptr;
    } else {
        table_set.panel.flags |= 0x80;
    }
}

void DemoLightSystem::draw_text() {
    LightSource* text = table_set.captions;
    if (!flags99ec.d) {
        hide_sources(text, 5);
        return;
    }
    show_sources(text, 5);
    TrackVec2 size = {32.0f, 32.0f};
    TrackVec2 pos = {screen_width() * 0.5f, 16.0f};
    const char* message = message_text(0x17c);
    TextRenderer* renderer = gTextRenderer;
    renderer->set_area(&pos, &size, 7, 0x20, 0);
    renderer->mode20b9c = 1;
    renderer->draw(text, message, 5, 1, 0xff, 0.0f, 0.0f);
    renderer->mode20b7c = 0;
    gTrackRenderer->write(text, 0x168, -1);
}

static inline void draw_layer(void* data, unsigned int size) {
    gEffectManager->begin();
    gTrackRenderer->write(data, size, -1);
    gTrackRenderer->flush(-1);
    gEffectManager->end();
}

void DemoLightSystem::render() {
    if (static_cast<unsigned int>(stage) > 0x3b)
        return;
    switch (state) {
    case 1:
        gEffectManager->begin();
        gTrackRenderer->flush(-1);
        gEffectManager->end();
        return;
    case 10:
        render_ending();
        return;
    case 11:
        return;
    }
    gEffectManager->begin();
    gTrackRenderer->write(&sources[0], 0x48, -1);
    gTrackRenderer->write(&sources[1], 0x48, -1);
    gTrackRenderer->flush(-1);
    gEffectManager->end();
    unsigned int count = table_set.count126a0;
    for (unsigned int i = 1; i < count; ++i) {
        TrackLightSet* set =
            table_set.count126a0 > i ? &static_cast<TrackLightSet*>(table_set.buffer)[i] : nullptr;
        set->update(time);
    }
    if (time < 4.0f) {
        gTrackRenderer->begin(0xf);
        gTrackRenderer->write(targets, value99f8 * 0x88, -1);
        gTrackRenderer->end();
    }
    if (effect)
        effect->draw(0);
    scene.draw(0, -1);
    scene.draw_overlay(-1);
    draw_layer(&table_set.panel, 0x88);
    draw_layer(table_set.captions, 0x168);
}

struct StageOffset {
    float x, y;

    StageOffset(float x_, float y_) : x(x_), y(y_) {}
};

void DemoLightSystem::render_ending() {
    static const StageOffset kOffsets[] = {
        StageOffset(-3.0f, 3.0f),     StageOffset(60.0f, 36.0f),    StageOffset(-18.0f, 99.0f),
        StageOffset(148.5f, 106.5f),  StageOffset(148.5f, 106.5f),  StageOffset(97.5f, 79.5f),
        StageOffset(154.5f, 3.0f),    StageOffset(-85.5f, -30.0f),  StageOffset(-148.5f, 1.5f),
        StageOffset(-84.0f, 108.0f),  StageOffset(-175.5f, 123.0f), StageOffset(-136.5f, 61.5f),
        StageOffset(45.0f, 108.0f),   StageOffset(148.5f, 106.5f),  StageOffset(133.5f, -48.0f),
        StageOffset(148.5f, 106.5f),  StageOffset(-3.0f, 3.0f),     StageOffset(133.5f, -48.0f),
        StageOffset(-3.0f, 3.0f),     StageOffset(60.0f, 36.0f),    StageOffset(-3.0f, 3.0f),
        StageOffset(-148.5f, 1.5f),   StageOffset(-84.0f, 108.0f),  StageOffset(148.5f, 106.5f),
        StageOffset(-18.0f, 99.0f),   StageOffset(154.5f, 3.0f),    StageOffset(-175.5f, 123.0f),
        StageOffset(-148.5f, 1.5f),   StageOffset(-3.0f, 3.0f),     StageOffset(-184.5f, -46.5f),
        StageOffset(133.5f, -48.0f),  StageOffset(45.0f, 108.0f),   StageOffset(-219.0f, 6.0f),
    };
    float timer = timer7294;
    float scale;
    if (timer <= 12.0f) {
        if (timer == 12.0f) {
            play_demo_sound(0x3f, 0, nullptr, 0x3c, 1.0f, 0.0f, 0.0f);
            timer = timer7294;
        }
        scale = lerp_float(0.0f, 2.0f, timer / 36.0f);
        scale = scale < 0.0f ? 0.0f : scale;
        scale = scale > 2.0f ? 2.0f : scale;
    } else if (timer <= 36.0f) {
        float elapsed = timer - 12.0f;
        scale = lerp_float(0.0f, 2.0f, timer / 36.0f);
        scale = scale < 0.0f ? 0.0f : scale;
        scale = scale > 2.0f ? 2.0f : scale;
        lerp_int(0xff, 0, static_cast<int>(elapsed), 0x18);
        if (!(screen_fader() && screen_fader()->fading) && screen_fader() && screen_fader())
            screen_fader()->fade(0.4f, 1, 1);
    } else {
        scale = 0.0f;
    }
    StageOffset offset = kOffsets[stage];
    gEffectManager->begin();
    unsigned int count = table_set.count126a0;
    if (count >= 2) {
        TrackVector adjust;
        adjust.x = scale + 1.0f;
        adjust.y = scale + 1.0f;
        adjust.z = -(scale * offset.x);
        adjust.w = scale * offset.y;
        for (unsigned int i = 1; i < count; ++i) {
            TrackLightSet* set =
                table_set.count126a0 > i ? &static_cast<TrackLightSet*>(table_set.buffer)[i] : nullptr;
            set->update_scaled(time, adjust, 0xff);
        }
    }
    gTrackRenderer->flush(-1);
    gEffectManager->end();
    if (effect)
        effect->draw(0);
    TrackLightTarget* panel = &table_set.panel;
    gEffectManager->begin();
    gTrackRenderer->write(panel, 0x88, -1);
    gTrackRenderer->flush(-1);
    gEffectManager->end();
}

static inline float logo_limit() {
    return screen_width() - 1380.0f + 600.0f;
}

void DemoLightSystem::draw_intro() {
    if (state != 1)
        return;
    TrackLightTarget* banner = &table_set.banner;
    banner->flags |= 0x80;
    sources[2].flags |= 0x80;
    sources[0].flags |= 0x80;
    sources[1].flags |= 0x80;
    for (int i = 0; i < 40; ++i)
        targets[i].flags |= 0x80;
    LightSource* layers[3] = {&sources[0], &sources[1], &sources[2]};
    unsigned int banner_alpha;
    unsigned int frame_alpha;
    bool show_name;
    float logo_x;
    float name_x;
    if (timer7290 <= 102.0f) {
        int frame_index = static_cast<int>(timer7290);
        unsigned int a = lerp_int(0, 0xff, frame_index, 0x1e);
        banner_alpha = a > 0xff ? 0xff : a;
        unsigned int b = lerp_int(0, 0xff, frame_index, 0x3c);
        name_x = 120.0f;
        show_name = false;
        frame_alpha = b > 0xff ? 0xff : b;
        logo_x = 0.0f;
    } else if (timer7290 <= 138.0f) {
        float elapsed = timer7290 - 102.0f;
        logo_x = lerp_float(logo_limit(), 0.0f, elapsed / 6.0f);
        logo_x = logo_x < 0.0f ? 0.0f : logo_x;
        if (logo_x > logo_limit())
            logo_x = logo_limit();
        TextRenderer* renderer = gTextRenderer;
        const char* text = name;
        TrackVec2 size = {54.0f, 54.0f};
        TrackVec2 extent;
        unsigned int width = renderer->measure(text, &size, &extent, 0.0f, screen_width());
        double start = width * -54.0 - 80.0;
        double x = lerp_float(start, 0.0f, elapsed / 6.0f);
        x = x < start ? start : x;
        x = x > 0.0 ? 0.0 : x;
        name_x = static_cast<float>(x) + 120.0f;
        frame_alpha = 0xff;
        show_name = true;
        banner_alpha = 0xff;
    } else {
        name_x = 120.0f;
        show_name = false;
        frame_alpha = 0xff;
        logo_x = 0.0f;
        banner_alpha = 0xff;
    }
    if (timer7290 == 102.0f)
        play_demo_sound(0x3e, 0, nullptr, 0x3c, 1.0f, 0.0f, 0.0f);
    float half_width = screen_width() * 0.5f;
    float half_height = screen_height() * 0.5f;
    banner->hidden = 0;
    banner->blend = 0;
    banner->alpha = 1.0f;
    banner->quad[0].x = half_width - 1024.0f;
    banner->quad[0].y = half_height - 512.0f;
    banner->quad[1].x = half_width + 1024.0f;
    banner->quad[1].y = half_height - 512.0f;
    banner->quad[2].x = half_width - 1024.0f;
    banner->quad[2].y = half_height + 512.0f;
    banner->quad[3].x = half_width + 1024.0f;
    banner->quad[3].y = half_height + 512.0f;
    banner->value18[0] = 0.0f;
    banner->value18[1] = 0.0f;
    banner->matrix[0] = 1.0f;
    banner->matrix[1] = 0.0f;
    banner->matrix[2] = 0.0f;
    banner->matrix[3] = 1.0f;
    banner->scale[0] = 1.0f;
    banner->scale[1] = 1.0f;
    banner->colors[0].a = banner_alpha;
    banner->colors[1].a = banner_alpha;
    banner->colors[2].a = banner_alpha;
    banner->colors[3].a = banner_alpha;
    TrackLightTable* table = static_cast<TrackLightTable*>(table_set.resources.primary);
    if (table) {
        unsigned int size = table->items[3]->size;
        float image_width = (size & 0xffff) >> 1;
        float image_height = size >> 17;
        float center_x = image_width * 0.25f + screen_width() * 0.5f;
        float center_y = image_height * 0.25f + screen_height() * 0.5f;
        sources[2].image = table->count >= 4 ? table->items[3] : nullptr;
        sources[2].uv0.x = 0.0f;
        sources[2].uv0.y = 0.0f;
        sources[2].uv1.x = 1.0f;
        sources[2].uv1.y = 1.0f;
        sources[2].flags &= ~0x80u;
        sources[2].min.x = center_x - image_width;
        sources[2].min.y = center_y - image_height;
        sources[2].max.x = image_width + center_x;
        sources[2].max.y = image_height + center_y;
        sources[2].color.a = banner_alpha;
    }
    TrackLightTable* frames = static_cast<TrackLightTable*>(object7278);
    if (frames) {
        sources[0].image = frames->count >= 1 ? frames->items[0] : nullptr;
        sources[0].uv0.x = 0.0f;
        sources[0].uv0.y = 0.0f;
        sources[0].uv1.x = 0.9375f;
        sources[0].uv1.y = 0.52734375f;
        sources[0].min.x = 0.0f;
        sources[0].min.y = 0.0f;
        sources[0].max.x = 1920.0f;
        sources[0].max.y = 1080.0f;
        sources[0].color.a = frame_alpha;
        sources[0].flags &= ~0x80u;
    }
    TrackLightTable* logos = static_cast<TrackLightTable*>(object7280);
    if (show_name && logos) {
        float x = logo_x + 1380.0f;
        sources[1].image = logos->count >= 1 ? logos->items[0] : nullptr;
        sources[1].uv0.x = 0.0f;
        sources[1].uv0.y = 0.0f;
        sources[1].uv1.x = 0.5859375f;
        sources[1].uv1.y = 0.933852136f;
        sources[1].min.x = x - 600.0f;
        sources[1].min.y = 60.0f;
        sources[1].max.x = x + 600.0f;
        sources[1].max.y = 1020.0f;
        sources[1].flags &= ~0x80u;
    }
    value99f8 = 0;
    if (show_name) {
        TextRenderer* renderer = gTextRenderer;
        TrackVec2 pos;
        TrackVec2 size;
        pos.x = name_x;
        size.x = 54.0f;
        size.y = 54.0f;
        pos.y = 81.0f;
        renderer->set_area(&pos, &size, 0x58, 0x4f, 0);
        renderer->flag20bc9 = 1;
        renderer->flag20bca = 1;
        renderer->mode20b8c = 0x59;
        renderer->mode20b98 = 2;
        value99f8 = renderer->draw(targets, name, 0x28, 1, 0xff, 0.0f, 0.0f);
        renderer->mode20b7c = 0;
        for (unsigned int i = 0; i < static_cast<unsigned int>(value99f8); ++i)
            targets[i].flags &= ~0x80u;
    }
    gTrackRenderer->write(banner, 0x88, -1);
    for (int i = 0; i < 3; ++i)
        gTrackRenderer->write(layers[i], 0x48, -1);
    gTrackRenderer->write(targets, value99f8 * 0x88, -1);
}