// Demo light system singleton (0x19b40 bytes). Names are descriptive
// placeholders; member types are known only by their out-of-line functions.
#pragma once

#include "event/demo_track.h"

// Block allocator over the system's 192 KiB heap block.
class LightAllocator {
public:
    LightAllocator();                                                   // 0x71005c2d24
    ~LightAllocator();                                                  // 0x71005c2c8c
    void init(void* block, unsigned int size, int a, int b, int c);     // 0x71005c2d40
    void finalize();                                                    // 0x71005c2e54

private:
    unsigned char data[0x60];
};

class LightSceneBase {
public:
    LightSceneBase();                                                   // 0x71001f5118
    virtual void v00();

private:
    unsigned char data[0x58fc];

public:
    int current_index;        // +5904

private:
    unsigned char data5908[8];
};

class LightScene : public LightSceneBase {
public:
    ~LightScene();                                                      // 0x71001f560c
    virtual void v08();
    void init(LightAllocator* allocator);                               // 0x71001f5670
    void finalize();                                                    // 0x71001f56fc
    void load(int mode, int stage);                                     // 0x71001f5738
    void unload();                                                      // 0x71001f58e4
    void* environment();                                                // 0x71001f6820
    void advance(float time, float speed);                              // 0x71001f594c
    void stop();                                                        // 0x71001f5fa4

    unsigned char pad5910[4];
    unsigned char flag5914;   // +5914
    unsigned char pad5915[7];
    unsigned char flag591c;   // +591c
    unsigned char pad591d[0x28b];
    unsigned char flag5ba8;   // +5ba8
    unsigned char pad5ba9[0x17];
};
static_assert(sizeof(LightScene) == 0x5bc0, "scene size");

// Light record with a dirty flag (0x80) in its flags word.
class LightSource {
public:
    LightSource();                                                      // 0x71001ef52c

    unsigned char pad0[8];
    unsigned int flags;       // +08
    unsigned char pad0c[0x3c];
};
static_assert(sizeof(LightSource) == 0x48, "source size");

// The channels' light tables live at +8.
class TrackLightTableSet {
public:
    TrackLightTableSet();                                               // 0x710025ffe8
    ~TrackLightTableSet();                                              // 0x7100260220
    void init(LightAllocator* allocator);                               // 0x710026026c
    void finalize();                                                    // 0x7100260288
    void load(int stage, void* state);                                  // 0x7100260290
    void unload();                                                      // 0x71002605d0

    unsigned char pad0[8];
    TrackLightTable* tables[3]; // +08
    unsigned char pad20[0x12710];
};
static_assert(sizeof(TrackLightTableSet) == 0x12730, "table set size");

class LightResource {
public:
    LightResource();                                                    // 0x71005d2744
    ~LightResource();                                                   // 0x71005d27b4

private:
    unsigned char data[0x110];
};

class LightEffectNode;

struct LightFlags {
    unsigned char a;          // +0
    unsigned char b;          // +1
    unsigned char c;          // +2
    unsigned char d;          // +3
    int index;                // +4
};

struct DemoLightSystem {
    void* block;                     // +00
    LightAllocator allocator;        // +08
    LightScene scene;                // +68
    TrackKey key;                    // +5c28
    int stage;                       // +5c58
    unsigned char initialized;       // +5c5c
    unsigned char loaded;            // +5c5d
    unsigned char pad5c5e[2];
    LightSource sources[3];          // +5c60
    TrackLightTarget targets[40];    // +5d38
    void* object7278;                // +7278
    void* object7280;                // +7280
    const char* name;                // +7288
    float timer7290;                 // +7290
    float timer7294;                 // +7294
    unsigned char pad7298[8];
    TrackLightTableSet table_set;    // +72a0
    float time;                      // +199d0
    float start_time;                // +199d4
    float time99d8;                  // +199d8
    float end_time;                  // +199dc
    int state;                       // +199e0
    int value99e4;                   // +199e4
    int index99e8;                   // +199e8
    LightFlags flags99ec;            // +199ec
    float speed;                     // +199f4

    int value99f8;                   // +199f8
    unsigned char pad99fc[4];
    LightEffectNode* effect;         // +19a00
    unsigned char pad9a08[8];
    LightResource resource;          // +19a10
    int value9b20;                   // +19b20
    unsigned char flag9b24;          // +19b24
    unsigned char flag9b25;          // +19b25
    unsigned char flag9b26;          // +19b26
    unsigned char flag9b27;          // +19b27
    unsigned long last_tick;         // +19b28
    unsigned long tick;              // +19b30
    float last_delta;                // +19b38

    DemoLightSystem();
    void initialize();
    void finalize();
    void load(int stage);
    void unload();
    void update();
    void start();
    void play();
    void finish();
};
static_assert(sizeof(DemoLightSystem) == 0x19b40, "system size");

// Reached through the GOT slot at 0x7100c22d98.
extern DemoLightSystem* gDemoLightSystem;
