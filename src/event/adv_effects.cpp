// Matching candidates for the Adventure Mode stage effect bodies 0x710026731c-0x710026767c
// (adv_btl_start, adv_change_tv/drc, adv_env_eff, adv_dlc3_clock). Names are descriptive
// placeholders. Status: matching/README.md.

#include "event/demo_effects.h"
#include "event/demo_light_system.h"

extern "C" void* memset(void* dest, int value, unsigned long size);

inline void* operator new(unsigned long, void* where) noexcept { return where; }

class DefaultHeap {
public:
    void* allocate(unsigned int alignment, unsigned long size, int a, int b); // 0x710045c458
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

// A layout with its animations (0x38 bytes); cleared from the back.
struct EffectRecord {
    LightEffectNode* node;    // +00
    LayoutAnimation* anims[5]; // +08: in_0, in_1, in_2, in_3, out
    int state;                // +30
    unsigned char pad34[4];

    void stop();                                                            // 0x71002695a8

    void reset() {
        state = 0;
        anims[4] = nullptr;
        anims[3] = nullptr;
        anims[2] = nullptr;
        anims[1] = nullptr;
        anims[0] = nullptr;
        node = nullptr;
    }
};
static_assert(sizeof(EffectRecord) == 0x38, "record size");

// Resource of one effect layer, padded to 0x120 bytes.
struct EffectLayer {
    LightResource resource;   // +00
    float width;              // +110
    float height;             // +114
    unsigned char pad118[8];
};

// Battle-start banner layout and its animation.
struct EffectBanner {
    LightEffectNode* node;    // +00
    LayoutAnimation* anim;    // +08
};

struct EffectScreen {
    LightEffectNode* node;    // +00
    LayoutAnimation* anims[25]; // +08
};
static_assert(sizeof(EffectScreen) == 0xd0, "screen size");

struct EffectClock {
    LightEffectNode* node;    // +00
    void* value8;             // +08
    LayoutAnimation* anims[4]; // +10: song of time in, out, re-in, re-out
    unsigned char pad30[0x20];
};
static_assert(sizeof(EffectClock) == 0x50, "clock size");

class AdvEffects {
public:
    AdvEffects() {
        start.reset();
        environment.reset();
        value0 = nullptr;
        step = 0.0f;
        value8 = 0;
        flagc = 0;
        playing2e8 = 0;
        flag2e9 = 0;
        value4ec = 0;
        flag270 = 0;
        banner.anim = nullptr;
        banner.node = nullptr;
        memset(screens, 0, sizeof(screens));
        flag490 = 0;
        value494 = 0;
        memset(&clock, 0, sizeof(clock));
        flag4e8 = 0;
    }
    ~AdvEffects() { finalize(); }
    void finalize();                                                        // 0x710026731c
    void initialize();                                                      // 0x71002676ec
    void update();                                                          // 0x7100267c44
    void update_screens();                                                  // 0x7100267d64
    void update_records();                                                  // 0x7100267f94
    void update_exit();                                                     // 0x7100268224
    void play_screen(int kind, int a, int b);                               // 0x7100268340
    void show_result(int result);                                           // 0x7100268874
    unsigned char end_screens();                                            // 0x7100268a80
    void draw_start();                                                      // 0x7100268f10
    void draw_environment();                                                // 0x7100268f74
    void draw_screens();                                                    // 0x7100268fc8
    void draw_screens_alternate();                                          // 0x71002690a8
    void play_banner();                                                     // 0x7100269188
    void play_enter(unsigned char forward, int state);                               // 0x7100269238
    void play_exit(unsigned char forward);                                           // 0x7100269440
    void stop_banner();                                                     // 0x7100269544
    void fade_nightmare();
    void reset_screens();

    void* value0;                     // +00
    int value8;                       // +08
    unsigned char flagc;              // +0c
    unsigned char padd[0x13];
    EffectLayer layers[2];            // +20
    EffectBanner banner;              // +260
    unsigned char flag270;            // +270
    unsigned char pad271[7];
    EffectRecord start;               // +278
    EffectRecord environment;         // +2b0
    unsigned char playing2e8;         // +2e8
    unsigned char flag2e9;            // +2e9
    unsigned char pad2ea[6];
    EffectScreen screens[2];          // +2f0
    unsigned char flag490;            // +490
    unsigned char pad491[3];
    int value494;                     // +494
    EffectClock clock;                // +498
    unsigned char flag4e8;            // +4e8
    unsigned char pad4e9[3];
    float value4ec;                   // +4ec
    float step;                       // +4f0
    unsigned char pad4f4[0xc];
};
static_assert(sizeof(AdvEffects) == 0x500, "effects size");

class GameState {
public:
    unsigned char pad[0x1bb7c];
    unsigned int mode;        // +1bb7c
};

class Game {
public:
    GameState* state();                                                     // 0x7100204c10
};
Game* get_game();                                                           // 0x7100204728

int screen_width();                                                         // 0x71003df258
int screen_height();                                                        // 0x71003df250
unsigned int display_width();                                               // 0x71003cc930
unsigned int display_height();                                              // 0x71003cc94c

// Layout and animation names, merged with other literals by the linker.
extern const char kBattleStartLayout[] __attribute__((visibility("hidden")));   // 0x71007d5d25
extern const char kChangeTvLayout[] __attribute__((visibility("hidden")));      // 0x71007d5d39
extern const char kChangeDrcLayout[] __attribute__((visibility("hidden")));     // 0x71007d5d4d
extern const char kEnvEffectLayout[] __attribute__((visibility("hidden")));     // 0x71007d5d62
extern const char kClockLayout[] __attribute__((visibility("hidden")));         // 0x71007d5d74
extern const char kBattleStartAnim[] __attribute__((visibility("hidden")));     // 0x71007d5d89
extern const char kIn0Anim[] __attribute__((visibility("hidden")));             // 0x71007d5d93
extern const char kIn1Anim[] __attribute__((visibility("hidden")));             // 0x71007d5d98
extern const char kIn2Anim[] __attribute__((visibility("hidden")));             // 0x71007d5d9d
extern const char kIn3Anim[] __attribute__((visibility("hidden")));             // 0x7100740583
extern const char kOutAnim[] __attribute__((visibility("hidden")));             // 0x710074056c
extern const char kSongInAnim[] __attribute__((visibility("hidden")));          // 0x71007d5f01
extern const char kSongOutAnim[] __attribute__((visibility("hidden")));         // 0x71007d5f11
extern const char kSongReInAnim[] __attribute__((visibility("hidden")));        // 0x71007d5f22
extern const char kSongReOutAnim[] __attribute__((visibility("hidden")));       // 0x71007d5f35
// Animation names of the environment screens (0x7100bd0ea0).
extern const char* const kScreenAnims[25] __attribute__((visibility("hidden")));
// Board positions (pointer reached through the GOT slot at 0x7100c2a6c0).
class AdvBoard {
public:
    TrackVec2 start_position(int state);                                    // 0x710029f8ec
    TrackVec2 environment_position(int state);                              // 0x710029fd90
};
extern AdvBoard* gAdvBoard;
// Border panes of the change screens, reached through the GOT slot at 0x7100c2a6c8.
extern const char* const kBorderLines[];
float lerp_float(float from, float to, float t);                            // 0x71001f6b40
// Frame delta, reached through the GOT slot at 0x7100c22a28.
extern float gFrameDelta;

// Environment panes (area_shadow_long ... nightmare), a hidden table at 0x7100bd0f68.
extern const char* const kEnvPanes[9] __attribute__((visibility("hidden")));
unsigned int random_below(int count);
float random_float(float range);                                            // 0x7100459c14
int unit_kind(int player, int slot);                                        // 0x7100269cfc
int unit_frame(int player, int slot);                                       // 0x710026c730
unsigned char unit_has_override(int player, int slot);                      // 0x710026c924
int unit_override_kind(int player, int slot);                               // 0x710026c654
// Cell size and origin of the two screens' board grids, reached through the GOT slots
// at 0x7100c2a6d0-0x7100c2a6e8.
extern TrackVec2 gScreenCellSize;
extern TrackVec2 gScreenCellOrigin;
extern TrackVec2 gScreenCellSize2;
extern TrackVec2 gScreenCellOrigin2;
extern const char kAreaShadowLong[] __attribute__((visibility("hidden")));      // 0x71007d5f53
extern const char kAreaShadowShort[] __attribute__((visibility("hidden")));     // 0x71007d5f64
extern const char kSparkLong[] __attribute__((visibility("hidden")));           // 0x71007d5e73
extern const char kSparkShort[] __attribute__((visibility("hidden")));          // 0x71007d5e7e
extern const char kSnowLong[] __attribute__((visibility("hidden")));            // 0x71007d5e8a
extern const char kSnowShort[] __attribute__((visibility("hidden")));           // 0x71007d5e94
extern const char kMajoraPower[] __attribute__((visibility("hidden")));         // 0x71007d5f76
extern const char kWind[] __attribute__((visibility("hidden")));                // 0x71007d5ed2
extern const char kNightmare[] __attribute__((visibility("hidden")));           // 0x71007d5f49                                                // 0x7100459bd8

struct UnitRecord {
    unsigned char pad[0x12];
    unsigned char kind;       // +12
    unsigned char pad13[0x1cd];
};
class UnitDatabase {
public:
    unsigned char pad[0xdb608];
    UnitRecord records[1];    // +db608
};
UnitDatabase* get_unit_database();                                          // 0x710020ec80

struct PlayerMark {
    int flags;                // +0
    int value;                // +4
};

class Player {
public:
    int id;                   // +00
    unsigned char pad4[0x200];
    PlayerMark marks[8];      // +204: by player
    unsigned char pad244[0x29f4];
};
static_assert(sizeof(Player) == 0x2c38, "player size");

class Game2 {
public:
    unsigned char pad[0x2944];
    Player players[1];        // +2944, 0x2c38 each
};

// Step of the resource queue, reached through the GOT slot at 0x7100c21df0.
extern unsigned int gResourceQueueElapsedStep;

// Reached through the GOT slot at 0x7100c2a6b8.
extern AdvEffects* gAdvEffects;

// Variant that reads the manager inside the check.
static inline void release_last(LightEffectNode*& node, int id) {
    if (node) {
        EffectManager* manager = gEffectManager;
        void* root = gResourceLoader->layout->root;
        manager->unregister(manager->registry, id);
        node->detach(root);
        node->release();
        manager->children.remove(node);
        node = nullptr;
    }
}

static inline void release_node(LightEffectNode*& node, int id) {
    EffectManager* manager = gEffectManager;
    if (node) {
        void* root = gResourceLoader->layout->root;
        manager->unregister(manager->registry, id);
        node->detach(root);
        node->release();
        manager->children.remove(node);
        node = nullptr;
    }
}

void AdvEffects::finalize() {
    release_node(banner.node, 0x420d);
    release_node(start.node, 0x420d);
    release_node(environment.node, 0x420d);
    release_node(screens[0].node, 0x420d);
    release_node(screens[1].node, 0x420d);
    release_last(clock.node, 0x420d);
    memset(&banner, 0, sizeof(banner));
    value0 = nullptr;
    value8 = 0;
    flagc = 0;
    memset(&clock, 0, sizeof(clock));
}

void create_adv_effects() {
    if (!gAdvEffects) {
        void* storage = get_default_heap()->allocate(0x10, sizeof(AdvEffects), 1, 0);
        gAdvEffects = new (storage) AdvEffects;
    }
}

void destroy_adv_effects() {
    if (gAdvEffects) {
        gAdvEffects->finalize();
        AdvEffects* effects = gAdvEffects;
        if (effects) {
            effects->~AdvEffects();
            get_default_heap()->release(effects, 1, 0);
        }
        gAdvEffects = nullptr;
    }
}

static inline void load_animation(LayoutAnimation*& slot, LightEffectNode* node, const char* name) {
    LayoutAnimation* animation = node->create_window_animation(name, true);
    slot = animation;
    if (animation)
        animation->set_active(false);
}

static inline void stop_animation(LayoutAnimation*& animation) {
    if (animation)
        animation->rewind();
    if (animation)
        animation->set_active(false);
}

void AdvEffects::initialize() {
    if (flagc)
        return;
    gEffectManager->create_node(&banner.node, 0x420d, kBattleStartLayout);
    gEffectManager->create_node(&start.node, 0x420d, kChangeTvLayout);
    gEffectManager->create_node(&environment.node, 0x420d, kChangeDrcLayout);
    gEffectManager->create_node(&screens[0].node, 0x420d, kEnvEffectLayout);
    gEffectManager->create_node(&screens[1].node, 0x420d, kEnvEffectLayout);
    if (get_game()->state()->mode == 4)
        gEffectManager->create_node(&clock.node, 0x420d, kClockLayout);
    gEffectManager->sync();
    load_animation(banner.anim, banner.node, kBattleStartAnim);
    load_animation(start.anims[0], start.node, kIn0Anim);
    load_animation(start.anims[1], start.node, kIn1Anim);
    load_animation(start.anims[2], start.node, kIn2Anim);
    load_animation(start.anims[3], start.node, kIn3Anim);
    load_animation(start.anims[4], start.node, kOutAnim);
    load_animation(environment.anims[0], environment.node, kIn0Anim);
    load_animation(environment.anims[1], environment.node, kIn1Anim);
    load_animation(environment.anims[2], environment.node, kIn2Anim);
    load_animation(environment.anims[3], environment.node, kIn3Anim);
    load_animation(environment.anims[4], environment.node, kOutAnim);
    for (int i = 0; i < 25; ++i)
        load_animation(screens[0].anims[i], screens[0].node, kScreenAnims[i]);
    for (int i = 0; i < 25; ++i) {
        load_animation(screens[1].anims[i], screens[1].node, kScreenAnims[i]);
        gEffectManager->finish(0x420d);
    }
    if (get_game()->state()->mode == 4) {
        load_animation(clock.anims[0], clock.node, kSongInAnim);
        load_animation(clock.anims[1], clock.node, kSongOutAnim);
        load_animation(clock.anims[2], clock.node, kSongReInAnim);
        load_animation(clock.anims[3], clock.node, kSongReOutAnim);
    }
    gEffectManager->attach(&layers[0].resource, nullptr);
    float width = screen_width();
    float height = screen_height();
    layers[0].width = width;
    layers[0].height = height;
    gEffectManager->attach_resource(&layers[1].resource);
    float display_x = display_width();
    float display_y = display_height();
    layers[1].width = display_x;
    layers[1].height = display_y;
    stop_animation(banner.anim);
    start.stop();
    environment.stop();
    flag270 = 0;
    playing2e8 = 0;
    flag2e9 = 0;
    value8 = 0;
    for (int i = 0; i < 25; ++i) {
        LayoutAnimation*& animation = screens[1].anims[i];
        if (animation)
            animation->rewind();
        animation->reset();
        if (animation)
            animation->set_active(false);
    }
    flag490 = 0;
    value494 = 0;
    step = gResourceQueueElapsedStep;
    value8 = 0;
    flagc = 1;
}

static inline bool animation_done(LayoutAnimation* animation) {
    return animation->frame == animation->frame_count();
}

static inline void advance_node(LightEffectNode* node) {
    node->advance(gFrameDelta);
}

void AdvEffects::update() {
    if (!flagc)
        return;
    update_screens();
    if (clock.node) {
        clock.node->advance(gFrameDelta);
        LightEffectNode* target = clock.node;
        void* root = gEffectManager->current();
        target->update(root, 0);
    }
    if (!value8)
        return;
    if (banner.node && flag270) {
        if (animation_done(banner.anim)) {
            value8 = 0;
            flag270 = 0;
        }
        banner.node->advance(gFrameDelta);
        LightEffectNode* target = banner.node;
        void* root = gEffectManager->current();
        target->update(root, 0);
    }
    update_records();
    update_exit();
}

void AdvEffects::update_screens() {
    if (!flag490 || !screens[0].node || !screens[1].node)
        return;
    for (int i = 0; static_cast<unsigned int>(i) <= 24; ++i) {
        int kind = value494;
        bool ending = false;
        if (kind == 5) {
            if (i == 0xd)
                ending = true;
            else if (i == 8 && animation_done(screens[1].anims[i]))
                gAdvEffects->play_screen(5, 0, 0);
        } else if (kind == 8) {
            if (i == 0x14)
                ending = true;
            else if (i == 0x12 && animation_done(screens[1].anims[i]))
                gAdvEffects->play_screen(8, 0, 0);
        } else if (i == 0x16 && kind == 0xa) {
            if (animation_done(screens[1].anims[0x16]))
                gAdvEffects->play_screen(0xa, 0, 0);
        }
        if (ending && animation_done(screens[1].anims[i]))
            show_result(-1);
        LayoutAnimation* animation = screens[1].anims[i];
        if (animation->speed != 0.0f && (animation->state44 & 2)) {
            end_screens();
            break;
        }
    }
    screens[0].node->advance(gFrameDelta);
    LightEffectNode* first = screens[0].node;
    void* root = gEffectManager->current();
    first->update(root, 0);
    screens[1].node->advance(gFrameDelta);
    LightEffectNode* second = screens[1].node;
    root = gEffectManager->current();
    second->update(root, 0);
}

static inline float animation_progress(LayoutAnimation* animation, float frame) {
    return frame / animation->frame_count();
}

void AdvEffects::update_records() {
    if (!start.node || !environment.node || !playing2e8)
        return;
    LayoutAnimation* first = start.anims[0];
    if (first->speed == 0.0f) {
        if (first->frame == 0.0f) {
            value8 = 0;
            playing2e8 = 0;
        } else if (animation_done(first)) {
            value8 = 3;
        }
    }
    for (int i = 0; i < 4; ++i) {
        TrackVec2 target = gAdvBoard->start_position(start.state);
        float frame = __builtin_fmaxf(start.anims[i]->frame, 0.0f);
        float x = lerp_float(target.x, 0.0f, frame / start.anims[i]->frame_count());
        float y = lerp_float(target.y, 0.0f, frame / start.anims[i]->frame_count());
        EffectGroup* line = start.node->group->find(kBorderLines[i], 1);
        line->offset30 = x;
        line->offset34 = y;
        line->flags58 |= 0x10;
    }
    for (int i = 0; i < 4; ++i) {
        TrackVec2 target = gAdvBoard->environment_position(environment.state);
        float frame = __builtin_fmaxf(environment.anims[i]->frame, 0.0f);
        float x = lerp_float(target.x, 0.0f, frame / environment.anims[i]->frame_count());
        float y = lerp_float(target.y, 0.0f, frame / environment.anims[i]->frame_count());
        EffectGroup* line = environment.node->group->find(kBorderLines[i], 1);
        line->offset30 = x;
        line->offset34 = y;
        line->flags58 |= 0x10;
    }
    start.node->advance(gFrameDelta);
    LightEffectNode* first_node = start.node;
    void* root = gEffectManager->current();
    first_node->update(root, 0);
    environment.node->advance(gFrameDelta);
    LightEffectNode* second_node = environment.node;
    root = gEffectManager->current();
    second_node->update(root, 0);
}

void AdvEffects::update_exit() {
    if (!start.node || !environment.node || !flag2e9)
        return;
    LayoutAnimation* out = start.anims[4];
    if (out->speed == 0.0f) {
        if (out->frame == 0.0f) {
            value8 = 3;
        } else if (animation_done(out)) {
            flag2e9 = 0;
            value8 = 0;
        }
    }
    start.node->advance(gFrameDelta);
    LightEffectNode* first_node = start.node;
    void* root = gEffectManager->current();
    first_node->update(root, 0);
    environment.node->advance(gFrameDelta);
    LightEffectNode* second_node = environment.node;
    root = gEffectManager->current();
    second_node->update(root, 0);
}

static inline void play_animation(LayoutAnimation*& animation, float rate) {
    animation->set_rate(rate);
    if (animation)
        animation->set_active(true);
}

static inline void show_env_pane(LightEffectNode* node, int shown) {
    for (int i = 0; i < 9; ++i) {
        EffectGroup* pane = node->group->find(kEnvPanes[i], 1);
        if (i == shown)
            pane->flags58 |= 1;
        else
            pane->flags58 &= ~1;
    }
}

inline void AdvEffects::reset_screens() {
    for (int i = 0; i < 25; ++i) {
        LayoutAnimation*& animation = screens[1].anims[i];
        if (animation)
            animation->rewind();
        animation->reset();
        if (animation)
            animation->set_active(false);
    }
}

void AdvEffects::play_screen(int kind, int variant, int option) {
    UnitDatabase* database = get_unit_database();
    Game* game = get_game();
    unsigned int mode = get_game()->state()->mode;
    Game* current = get_game();
    GameState* state = get_game()->state();
    int result;
    bool ready;
    if (variant != 0) {
        Game2* players = reinterpret_cast<Game2*>(current);
        unsigned char unit_kind = database->records[players->players[state->mode].id].kind;
        if (static_cast<unsigned int>(unit_kind - 0xf) > 1) {
            ready = false;
            result = -1;
        } else {
            Game2* owner = reinterpret_cast<Game2*>(get_game());
            int id = owner->players[get_game()->state()->mode].id;
            ready = !(reinterpret_cast<Game2*>(game)->players[mode].marks[id].flags & 1);
            result = ready ? -1 : 0;
        }
    } else {
        result = 0;
        ready = true;
    }
    bool keep = kind == 10 && option != 0;
    bool busy = variant == 1 || !ready;
    if (!keep && !busy) {
        reset_screens();
        flag490 = 0;
        value494 = 0;
    }
    if (static_cast<unsigned int>(kind) > 10)
        return;
    value494 = kind;
    unsigned int pick = random_below(2);
    unsigned int index;
    switch (kind) {
    case 0:
        return;
    case 1:
        index = pick;
        goto play_pick;
    case 2:
        index = pick + 2;
        goto play_pick;
    case 3:
        index = pick + 4;
        goto play_pick;
    case 4:
        index = pick + 6;
    play_pick:
        play_animation(screens[1].anims[index], step);
        show_result(-1);
        break;
    case 5:
        if (!busy)
            play_animation(screens[1].anims[variant + 9], (variant == -1 ? 1.4f : 1.0f) * step);
        if (variant != 0)
            play_animation(screens[1].anims[variant + 12], step);
        show_result(result);
        break;
    case 6:
        play_animation(screens[1].anims[pick + 14], step);
        show_result(pick + 2);
        break;
    case 7:
        play_animation(screens[1].anims[pick + 16], step);
        show_result(pick + 4);
        break;
    case 8:
        if (ready)
            play_animation(screens[1].anims[option + 19], step);
        show_env_pane(screens[1].node, 6);
        break;
    case 9:
        play_animation(screens[1].anims[21], step);
        show_env_pane(screens[1].node, 7);
        break;
    default:
        if (option == 0) {
            play_animation(screens[1].anims[23], step);
            show_env_pane(screens[1].node, 8);
        } else {
            flag4e8 = 1;
            value4ec = 60.0f;
        }
        break;
    }
    if (end_screens()) {
        flag490 = 1;
        return;
    }
    value494 = 0;
    reset_screens();
    flag490 = 0;
    value494 = 0;
}

void AdvEffects::show_result(int result) {
    if (result != -1) {
        for (unsigned int i = 0; i < 9; ++i) {
            EffectGroup* pane = screens[1].node->group->find(kEnvPanes[i], 1);
            if (static_cast<unsigned int>(result) == i)
                pane->flags58 |= 1;
            else
                pane->flags58 &= ~1;
        }
        return;
    }
    screens[1].node->group->find(kAreaShadowLong, 1)->flags58 &= ~1;
    screens[1].node->group->find(kAreaShadowShort, 1)->flags58 &= ~1;
    screens[1].node->group->find(kSparkLong, 1)->flags58 &= ~1;
    screens[1].node->group->find(kSparkShort, 1)->flags58 &= ~1;
    screens[1].node->group->find(kSnowLong, 1)->flags58 &= ~1;
    screens[1].node->group->find(kSnowShort, 1)->flags58 &= ~1;
    screens[1].node->group->find(kMajoraPower, 1)->flags58 &= ~1;
    screens[1].node->group->find(kWind, 1)->flags58 &= ~1;
    screens[1].node->group->find(kNightmare, 1)->flags58 &= ~1;
}

void AdvEffects::draw_start() {
    if (!flagc)
        return;
    if (value8 && start.node)
        start.node->draw(0);
    if (banner.node)
        banner.node->draw(0);
    if (clock.node)
        clock.node->draw(0);
}

void AdvEffects::draw_environment() {
    if (!flagc)
        return;
    if (value8 && environment.node)
        environment.node->draw(0);
    if (banner.node)
        banner.node->draw(0);
}

inline void AdvEffects::fade_nightmare() {
    if (!flagc || !flag490 || !screens[1].node)
        return;
    if (value494 == 10 && flag4e8) {
        float value = value4ec;
        if (value > 0.0f) {
            value -= step;
            value4ec = value;
            if (value <= 0.0f) {
                value = 0.0f;
                value4ec = 0.0f;
            }
        }
        int alpha = value / 60.0f * 255.0f;
        screens[1].node->group->find(kNightmare, 1)->alpha59 = alpha;
        if (value4ec == 0.0f) {
            flag4e8 = 0;
            show_result(-1);
        }
    }
    screens[1].node->draw(0);
}

void AdvEffects::draw_screens() {
    fade_nightmare();
}

void AdvEffects::draw_screens_alternate() {
    fade_nightmare();
}

void AdvEffects::play_banner() {
    if (flag270 || !flagc)
        return;
    stop_animation(banner.anim);
    start.stop();
    environment.stop();
    flag270 = 1;
    playing2e8 = 0;
    flag2e9 = 0;
    value8 = 3;
    if (banner.anim)
        banner.anim->set_active(true);
    banner.anim->set_rate(step);
}

void AdvEffects::play_enter(unsigned char forward, int state) {
    if (playing2e8 || !flagc)
        return;
    stop_animation(banner.anim);
    start.stop();
    environment.stop();
    float rate = step + step;
    flag270 = 0;
    flag2e9 = 0;
    rate = forward ? rate : -rate;
    playing2e8 = 1;
    value8 = 1;
    start.state = state;
    if (forward) {
        float frame = 0.0f;
        for (int i = 0; i < 4; ++i) {
            EffectGroup* line = start.node->group->find(kBorderLines[i], 1);
            float z = line->offset38;
            TrackVec2 position = gAdvBoard->start_position(state);
            line->offset30 = position.x;
            line->offset34 = position.y;
            line->offset38 = z;
            line->flags58 |= 0x10;
            start.anims[i]->set_active(true);
            start.anims[i]->set_rate(rate);
            start.anims[i]->frame = frame;
            frame -= 5.0f;
        }
    } else {
        for (int i = 0; i < 4; ++i) {
            EffectGroup* line = start.node->group->find(kBorderLines[i], 1);
            float z = line->offset38;
            TrackVec2 position = gAdvBoard->start_position(state);
            line->offset30 = position.x;
            line->offset34 = position.y;
            line->offset38 = z;
            line->flags58 |= 0x10;
            if (start.anims[i])
                start.anims[i]->set_active(true);
            start.anims[i]->set_rate(rate);
        }
    }
}

void AdvEffects::play_exit(unsigned char forward) {
    if (flag2e9 || !flagc)
        return;
    stop_animation(banner.anim);
    start.stop();
    environment.stop();
    float rate = step + step;
    flag270 = 0;
    playing2e8 = 0;
    rate = forward ? rate : -rate;
    flag2e9 = 1;
    value8 = 2;
    if (start.anims[4])
        start.anims[4]->set_active(true);
    start.anims[4]->set_rate(rate);
    if (environment.anims[4])
        environment.anims[4]->set_active(true);
    environment.anims[4]->set_rate(rate);
}

void EffectRecord::stop() {
    for (int i = 0; i < 5; ++i)
        stop_animation(anims[i]);
}

void AdvEffects::stop_banner() {
    stop_animation(banner.anim);
    start.stop();
    environment.stop();
    flag270 = 0;
    playing2e8 = 0;
    flag2e9 = 0;
    value8 = 0;
}

static inline unsigned int game_mode() {
    return get_game()->state()->mode;
}

static inline bool is_screen_cell(int kind) {
    if (game_mode() == 8)
        return (kind >= 0x3d && kind <= 0x3e) || (kind >= 0x42 && kind <= 0x4a);
    return (kind >= 0xa0 && kind <= 0xa8) || kind == 0x3f || (kind >= 0x43 && kind <= 0x4b);
}

unsigned char AdvEffects::end_screens() {
    unsigned int kind = value494;
    if (kind > 10)
        return 0;
    float z0 = screens[0].node->group->offset38;
    float z1 = screens[1].node->group->offset38;
    float x0, y0, x1, y1;
    switch (kind) {
    case 5:
    case 6:
    case 7:
    case 8:
    case 10:
        x0 = 0.0f;
        y0 = 0.0f;
        x1 = 0.0f;
        y1 = 0.0f;
        break;
    case 1:
    case 2:
    case 4:
    case 9: {
        float x = random_float(200.0f) + -100.0f;
        float y = random_float(200.0f) + -100.0f;
        x0 = x;
        y0 = y;
        x1 = x;
        y1 = y;
        break;
    }
    case 3: {
        Game2* game = reinterpret_cast<Game2*>(get_game());
        int player = game->players[game_mode()].id;
        int cells[0xb0] = {-1};
        unsigned int count = 0;
        for (int i = 0; i < 0xb0; ++i) {
            int unit = unit_kind(player, i);
            int frame = unit_frame(player, i);
            if (unit_has_override(player, i))
                unit = unit_override_kind(player, i);
            if (game_mode() == 4 &&
                ((frame >= 0xd2 && frame <= 0xdd) || (frame >= 0xc5 && frame <= 0xd1) ||
                 (frame >= 0xa4 && frame <= 0xb0) || (frame >= 0xb8 && frame <= 0xc4)))
                continue;
            if (game_mode() == 5 || game_mode() == 6) {
                if (!is_screen_cell(unit))
                    continue;
                if (frame != -1 && !is_screen_cell(frame))
                    continue;
                if (unit == 0x50 || unit == 0x51)
                    continue;
            } else if (game_mode() == 8) {
                if (!((is_screen_cell(unit) && frame == -1) || is_screen_cell(frame)))
                    continue;
                if (unit == 0x38)
                    continue;
            } else if (unit != 0 && unit != 2) {
                continue;
            }
            cells[count++] = i;
        }
        if (!count)
            return 0;
        int cell = cells[random_below(count)];
        float column = cell % 16;
        float row = cell / 16;
        x0 = gScreenCellSize.x * column + gScreenCellOrigin.x;
        y0 = row * gScreenCellSize.y + gScreenCellOrigin.y + -28.0f;
        x1 = column * gScreenCellSize2.x + gScreenCellOrigin2.x;
        y1 = row * gScreenCellSize2.y + gScreenCellOrigin2.y + -28.0f;
        break;
    }
    default:
        return 0;
    }
    EffectGroup* first = screens[0].node->group;
    first->offset30 = x0;
    first->offset34 = y0;
    first->offset38 = z0;
    first->flags58 |= 0x10;
    EffectGroup* second = screens[1].node->group;
    second->offset30 = x1;
    second->offset34 = y1;
    second->offset38 = z1;
    second->flags58 |= 0x10;
    return 1;
}
