// Demo light system singleton (0x19b40 bytes). Names are descriptive
// placeholders; member types are known only by their out-of-line functions.
#pragma once

#include "event/demo_sequence.h"
#include "event/demo_track.h"
#include "event/demo_track_resources.h"

// Light channels of one track (0x28 bytes).
struct TrackLightSet {
    DemoOwner* owner;               // +00
    TrackLightChannel* channels;    // +08: count + 1
    unsigned int count;             // +10
    TrackLight** keys;              // +18: count + 1
    int value20;                    // +20
    int value24;                    // +24

    TrackLightSet(DemoOwner* owner, int value24);
    unsigned int load(void* resource);
    void update(float time);
    void release(void* p) {
        if (p)
            owner->free(p);
    }
    void update_scaled(float time, TrackVector adjust, unsigned char alpha);
};
static_assert(sizeof(TrackLightSet) == 0x28, "set size");

// Block allocator over the system's 192 KiB heap block.
class LightAllocator : public DemoOwner {
public:
    LightAllocator();                                                   // 0x71005c2d24
    ~LightAllocator();                                                  // 0x71005c2c8c
    void init(void* block, unsigned int size, int a, int b, int c);     // 0x71005c2d40
    void finalize();                                                    // 0x71005c2e54

private:
    unsigned char data[0x58];
};
static_assert(sizeof(LightAllocator) == 0x60, "allocator size");

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
    void draw(int layer, int slot);                                     // 0x71001f5fc4
    void draw_overlay(int slot);                                        // 0x71001f6344

    unsigned char pad5910[4];
    unsigned char flag5914;   // +5914
    unsigned char pad5915[7];
    unsigned char flag591c;   // +591c
    unsigned char pad591d[0x28b];
    unsigned char flag5ba8;   // +5ba8
    unsigned char pad5ba9[0x17];
};
static_assert(sizeof(LightScene) == 0x5bc0, "scene size");

// Textured rectangle; flag 0x80 in +08 hides it.
class LightSource {
public:
    LightSource();                                                      // 0x71001ef52c

    unsigned char pad0[8];
    unsigned int flags;       // +08
    unsigned char pad0c[4];
    TrackLightImage* image;   // +10
    TrackVec2 uv0;            // +18
    TrackVec2 uv1;            // +20
    TrackColor color;         // +28
    unsigned char pad2c[4];
    TrackVec2 min;            // +30
    TrackVec2 max;            // +38
    unsigned char pad40[8];
};
static_assert(sizeof(LightSource) == 0x48, "source size");

void show_sources(LightSource* sources, int count);                     // 0x71001f73e4
void hide_sources(LightSource* sources, int count);                     // 0x71001f7430

// Color as four bytes.
struct Color4u8 {
    unsigned char r, g, b, a;

    Color4u8() : r(0), g(0), b(0), a(0) {}
    Color4u8(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_)
        : r(r_), g(g_), b(b_), a(a_) {}
};

// Four RGBA colors.
struct LightMatrix {
    float m[16];
};

// Textured sprite bound to a texture made by the resource loader (0xd0 bytes).
class LightEntry {
public:
    LightEntry();
    ~LightEntry();
    void unload();
    void bind(LightAllocator* allocator);

    RefObject* texture;               // +00
    unsigned long value8;             // +08
    unsigned long value10;            // +10
    unsigned short modes[6];          // +18
    unsigned char pad24[0xc];
    TrackVector position;             // +30
    TrackVector target;               // +40
    TrackVec2 offset;                 // +50
    unsigned long value58;            // +58
    TrackVec2 scale;                  // +60
    Color4u8 color;                   // +68
    int count6c;                      // +6c
    int count70;                      // +70
    int flags74;                      // +74
    unsigned char pad78[8];
    LightMatrix matrix;               // +80: colors
    unsigned char visible;            // +c0
    unsigned char padc1[0xf];
};
static_assert(sizeof(LightEntry) == 0xd0, "entry size");

struct LightCounts {
    union {
        struct {
            unsigned int targets; // +0
            unsigned int entries; // +4
        };
        unsigned long raw;
    };
};

struct LightSlot {
    int index = -1;           // +0
    int a = 0;                // +4
    int b = 0;                // +8
    int c = 0;                // +c
};

// Light tables and the overlay quads drawn over the demo.
class TrackLightTableSet {
public:
    TrackLightTableSet();
    ~TrackLightTableSet();
    void init(LightAllocator* allocator);
    void finalize();
    void load(int stage, float* times);
    int load_tracks(unsigned int id, float* times);
    void unload();

    LightAllocator* allocator;        // +00
    TrackResources resources;         // +08: primary, secondary, extra tables
    TrackLightTarget banner;          // +20
    TrackLightTarget panel;           // +a8
    LightSource captions[5];          // +130
    LightCounts counts;               // +298
    TrackLightTarget targets[256];    // +2a0
    LightEntry entries[192];          // +8aa0
    int count126a0;                   // +126a0
    unsigned char pad126a4[4];
    void* buffer;                     // +126a8
    LightSlot slots[8];               // +126b0
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
    void draw();
    void draw_intro();
    void layout_frames();
    void layout_panel();
    void draw_text();
    void render();
    void render_ending();
    void start();
    void play();
    void finish();
};
static_assert(sizeof(DemoLightSystem) == 0x19b40, "system size");

// Reached through the GOT slot at 0x7100c22d98.
extern DemoLightSystem* gDemoLightSystem;
