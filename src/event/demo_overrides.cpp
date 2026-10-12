// Matching candidates for 0x71002586bc-0x7100258970: mode-dependent overrides, a
// frame-heap singleton and the resource queue worker globals with their static
// initializer. Names are descriptive placeholders. Status: matching/README.md.

#include "system/worker.h"

inline void* operator new(unsigned long, void* where) noexcept { return where; }

class DefaultHeap {
public:
    void* allocate(unsigned int alignment, unsigned long size, int a, int b); // 0x710045c458
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                      // 0x710045c96c

void initialize_worker(Worker* worker);               // 0x710045de40 (Worker constructor)
void destroy_worker(Worker* worker);                  // 0x710045de54 (Worker destructor)

struct GameState {
    unsigned char unknown[0xd20];
    unsigned int vector[3];   // +d20
    unsigned char unknown_d2c[0x20];
    int target_index;         // +d4c
    unsigned int mode;        // +d50
    unsigned char unknown_d54[8];
    float speed;              // +d5c
    unsigned int query(unsigned int id);   // 0x7100252f54
};
// Game state cell (GOT 0x7100c22d68) and stage number (GOT 0x7100c2a590).
extern GameState* gGameState;
extern unsigned int gStageNumber;

struct DemoTuning {
    unsigned char unknown00[0x10];
    unsigned int value10;     // +10
    float value14;            // +14
    float value18;            // +18
    unsigned char unknown1c[0x1c];
    unsigned int value38;     // +38
    unsigned char unknown3c[4];
    float value40;            // +40
    float value44;            // +44
};

static inline bool tuning_mode_active() {
    GameState* game = gGameState;
    if (!game)
        return false;
    unsigned int mode = game->mode;
    return mode <= 12 && ((1u << mode) & 0x1780);
}

struct PlatformFlags {
    unsigned char unknown0;
    unsigned char flags1;     // +01
    unsigned char unknown2[2];
    unsigned char flags4;     // +04
};
PlatformFlags* get_platform_flags();                  // 0x710016ef34

struct DemoPlayer {
    unsigned char unknown00[0x10];
    char name[0x30];          // +10
    unsigned long pair[2];    // +40
    unsigned char unknown50[0x128];
    void* target;             // +178
    float value180;           // +180
    float value184;           // +184
    float value188;           // +188
    unsigned char unknown18c[4];
    float speed_scale;        // +190
};
// Player cell (GOT 0x7100c2a5a8) and current event index (GOT 0x7100c2a560).
extern DemoPlayer* gDemoPlayer;
extern unsigned int gDemoEventIndex;

struct ObjectTable {
    unsigned char unknown[0x68];
    void* entries[1];         // +68
};
struct TableEntryA {
    unsigned char unknown[0xc8];
    void* value;              // +c8
};
struct TableEntryB {
    unsigned char unknown[0x88];
    void* value;              // +88
};
// Object tables (GOT 0x7100c2a518 and 0x7100c2a530).
extern ObjectTable* gObjectTableA;
extern ObjectTable* gObjectTableB;

void copy_name(char* dst, const char* src);   // 0x710003ff70

void* lookup_table_a(int id) {
    unsigned int index = id - 0x118;
    if (index <= 0x63) {
        TableEntryA* entry = static_cast<TableEntryA*>(gObjectTableA->entries[static_cast<int>(index)]);
        if (entry)
            return entry->value;
        return nullptr;
    }
    return nullptr;
}

void* lookup_table_b(int id) {
    unsigned int index = id - 0x4d9;
    if (index <= 0x12b)
        return static_cast<TableEntryB*>(gObjectTableB->entries[static_cast<int>(index)])->value;
    return nullptr;
}

static inline void* player_target() {
    if (gGameState->target_index < 0)
        return nullptr;
    if (gDemoEventIndex > 0x10c)
        return nullptr;
    return gDemoPlayer->target;
}

void* demo_player_target() {
    return player_target();
}

static inline bool large_platform() {
    return (get_platform_flags()->flags1 & 0xa) || (get_platform_flags()->flags1 & 4) ||
           (get_platform_flags()->flags4 & 2);
}

int demo_player_target_state() {
    if (!large_platform())
        return -1;
    GameState* game = gGameState;
    if (game) {
        switch (game->mode) {
        case 7:
        case 8:
        case 9:
        case 10:
        case 12:
            return player_target() ? 3 : -1;
        }
    }
    return -1;
}

// Written as a switch on the mode; the shared helper's bit test gives a branch here.
float demo_speed_scale() {
    GameState* game = gGameState;
    if (game) {
        switch (game->mode) {
        case 7:
        case 8:
        case 9:
        case 10:
        case 12:
            return game->speed * gDemoPlayer->speed_scale;
        }
    }
    return 0.0f;
}

void demo_player_pair(unsigned long* out) {
    DemoPlayer* player = gDemoPlayer;
    out[1] = player->pair[1];
    out[0] = player->pair[0];
}

void demo_player_name(char* dst) {
    copy_name(dst, gDemoPlayer->name);
}

static inline bool value_mode_active() {
    GameState* game = gGameState;
    return game && game->mode != 0xffffffff && game->mode != 0x16;
}

float demo_player_value180() {
    float value = 64.0f;
    if (value_mode_active())
        value = gDemoPlayer->value180;
    return value;
}

float demo_player_value184() {
    float value = 64.0f;
    if (value_mode_active())
        value = gDemoPlayer->value184;
    return value;
}

float demo_player_value188() {
    float value = 64.0f;
    if (value_mode_active())
        value = gDemoPlayer->value188;
    return value;
}

void demo_tuning_vector(unsigned int* out) {
    if (!tuning_mode_active())
        return;
    GameState* game = gGameState;
    out[0] = game->vector[0];
    out[1] = game->vector[1];
    out[2] = game->vector[2];
}

void apply_demo_tuning(DemoTuning* tuning) {
    if (!tuning_mode_active())
        return;
    switch (gStageNumber) {
    case 2:
        tuning->value40 = 1500.0f;
        tuning->value44 = 250000.0f;
        tuning->value10 = 0;
        tuning->value14 = 1.55f;
        tuning->value18 = 5.67f;
        return;
    case 0x20:
        tuning->value40 = 10500.0f;
        tuning->value44 = 450000.0f;
        return;
    case 0x13:
        tuning->value38 = 0;
        return;
    }
}

void demo_tuning_nop() {}

void apply_demo_limit(unsigned int* value) {
    if (!tuning_mode_active())
        return;
    unsigned int stage = gStageNumber;
    if (stage == 0xf || stage == 3)
        *value = 0;
}

unsigned int query_game_state(unsigned int id) {
    return gGameState->query(id);
}

unsigned int demo_overrides_zero() {
    return 0;
}

class FrameHeapImpl {
public:
    FrameHeapImpl();                                                               // 0x71005c2d24
    ~FrameHeapImpl();                                                              // 0x71005c2c8c
    void initialize(void* buffer, unsigned long size, int a, int b, int alignment); // 0x71005c2d40
    void finalize();                                                               // 0x71005c2e54

private:
    unsigned char storage[0x60];
};

struct FrameHeap {
    void* buffer;             // +00
    FrameHeapImpl impl;       // +08

    FrameHeap() : buffer(nullptr) {}
    void initialize();
    void finalize();
};
static_assert(sizeof(FrameHeap) == 0x68, "frame heap size");


// Frame heap cell, reached through the GOT slot at 0x7100c2a5f0.
extern FrameHeap* gFrameHeap;

void create_frame_heap() {
    FrameHeap** cell = &gFrameHeap;
    if (!*cell) {
        void* storage = get_default_heap()->allocate(0x10, sizeof(FrameHeap), 1, 0);
        *cell = new (storage) FrameHeap;
    }
}

void destroy_frame_heap() {
    FrameHeap** cell = &gFrameHeap;
    if (FrameHeap* heap = *cell) {
        heap->~FrameHeap();
        get_default_heap()->release(heap, 1, 0);
        *cell = nullptr;
    }
}

void FrameHeap::initialize() {
    unsigned long size = 0x14000;
    DefaultHeap* heap;
    if ((get_platform_flags()->flags1 & 0xa) || (get_platform_flags()->flags1 & 4) ||
        (get_platform_flags()->flags4 & 2)) {
        heap = get_default_heap();
        size += 0x200000;
    } else {
        heap = get_default_heap();
    }
    buffer = heap->allocate(0x10, size, 1, 0);
    impl.initialize(buffer, size, 4, 4, 0x10);
}

void FrameHeap::finalize() {
    impl.finalize();
    if (void* b = buffer) {
        get_default_heap()->release(b, 1, 0);
        buffer = nullptr;
    }
}

// The resource queue worker controls (0x7100c8aef8), defined here; the queue
// unit refers to them as an external hidden global.
// QueueWorker only gives the array the Worker constructor (0x710045de40) and destructor
// (0x710045de54), which drive the static initializer and the array destructor.
struct QueueWorker : Worker {
    QueueWorker();
    ~QueueWorker();
};
QueueWorker gResourceQueueWorkers[2] __attribute__((visibility("hidden")));
