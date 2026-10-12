// Demo track light types shared by the track item, light set and light
// channel units. Names are descriptive placeholders.
#pragma once

#include "system/worker.h"

// Track key data loaded per stage.
struct TrackKey {
    void* owner;              // +00
    unsigned long value8;     // +08
    float value10;            // +10
    unsigned int index14;     // +14
    unsigned int index18;     // +18
    unsigned int value1c;     // +1c
    unsigned long id20;       // +20
    unsigned long id28;       // +28

    TrackKey();
    explicit TrackKey(void* owner);
    ~TrackKey();
    void finalize();
    void unload();
    void load(int stage);     // 0x710025b864
};
static_assert(sizeof(TrackKey) == 0x30, "key size");

struct alignas(16) TrackVector {
    float x, y, z, w;
};
// Default vector, reached through the GOT slot at 0x7100c216a8.
extern const TrackVector kTrackDefaultVector;

struct TrackColor {
    union {
        unsigned int raw;
        struct {
            unsigned char r, g, b, a;
        };
    };

    void set(TrackColor value) {
        r = value.r;
        g = value.g;
        b = value.b;
        a = value.a;
    }
};

// Packed light record as stored in track data.
struct TrackLightRecord {
    unsigned short value0;    // +00
    unsigned short value1;    // +02
    short value2;             // +04
    short value3;             // +06
    short position[3];        // +08
    unsigned short scale20;   // +0e: hundredths
    unsigned short scale24;   // +10: hundredths
    unsigned char color[4];   // +12
    unsigned char flag2c;     // +16
    unsigned char level2d;    // +17
    unsigned char bytes2e[2]; // +18
    unsigned short value30;   // +1a
    unsigned int value34;     // +1c
};

// values.x and values.y are the first and last frame of a key.
struct TrackLight {
    TrackVector position;     // +00
    TrackVector values;       // +10
    float scale20;            // +20
    float scale24;            // +24
    TrackColor color;         // +28
    unsigned char flag2c;     // +2c
    unsigned char level2d;    // +2d: easing, 0x80 is linear
    unsigned char bytes2e[2]; // +2e
    unsigned short value30;   // +30
    unsigned int value34;     // +34
    unsigned char flag38;     // +38

    TrackLight() { reset(); }
    TrackLight(const TrackLight& other) { copy(other); }
    explicit TrackLight(const TrackLightRecord& record) { decode(record); }
    ~TrackLight();

    void reset();
    void decode(const TrackLightRecord& record);
    void copy(const TrackLight& other);
    void decode_full(const TrackLightRecord& record);
    void copy_full(const TrackLight& other);
    unsigned char equals(const TrackLight& other) const;
    void interpolate(const TrackLight& to, const TrackLight& from, float t, float alpha_t);
};
static_assert(sizeof(TrackLight) == 0x40, "light size");

struct TrackVec2 {
    float x, y;
};

// Image of a light table; size holds the width in the low and the height in
// the high 16 bits.
struct TrackLightImage {
    unsigned char pad[0x30];
    unsigned int size;        // +30
};

// Reference-counted table of images (loaded by TrackResources).
struct TrackLightTable : public RefObject {
    unsigned char pad0c[0xc];
    int count;                // +18
    unsigned int pad1c;       // +1c
    TrackLightImage* items[1]; // +20
};

// Quad lit by a channel; flag 0x80 in +08 marks it for update.
struct TrackLightTarget {
    void* vtable;             // +00
    union {
        unsigned int flags;   // +08
        struct {
            unsigned int : 7;
            unsigned int hidden : 1;
            unsigned int : 8;
            unsigned int blend : 4;
        };
    };
    TrackLightImage* image;   // +10
    float value18[2];         // +18
    float matrix[4];          // +20
    float scale[2];           // +30
    TrackColor colors[4];     // +38
    unsigned char pad48[0x10]; // +48
    TrackVec2 quad[4];        // +58
    float alpha;              // +78
    unsigned char pad7c[0xc]; // +7c

    TrackLightTarget();                                                 // 0x71001f0140
    void build_quad(TrackLightTable* table, const TrackLight& light, int index);
};
static_assert(sizeof(TrackLightTarget) == 0x88, "target size");

void apply_track_light(TrackLightTarget* target, const TrackLight& light, const TrackLight& base,
                       TrackLightTable* table, int index);

struct TrackLightNode {
    unsigned char pad[0xc0];
    unsigned char dirty;      // +c0
};

struct TrackLightChannel {
    int mode;                       // +00: table 0-2
    int value4;                     // +04
    unsigned int count;             // +08: keys
    unsigned int index;             // +0c
    TrackLightTarget* targets[4];   // +10
    TrackLightNode* nodes[4];       // +30
    int value50;                    // +50
    TrackLight* keys;               // +58
    unsigned int value60;           // +60

    TrackLightChannel();
    void clear();
    void set_keys(TrackLight* keys, unsigned int count);
    void update(const TrackLight& base, float time);
    unsigned char sample(TrackLight* out, float time);
    void update_scaled(const TrackLight& base, float time, TrackVector adjust, unsigned char alpha);
};
static_assert(sizeof(TrackLightChannel) == 0x68, "channel size");

// Default-constructed storage for a TrackLightSet (0x28 bytes).
struct TrackSlot {
    unsigned long value0;     // +00
    unsigned long value8;     // +08
    unsigned int value10;     // +10
    unsigned long value18;    // +18
    unsigned long id20;       // +20

    TrackSlot();
};
