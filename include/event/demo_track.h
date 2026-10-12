// Demo track light types shared by the track item, light set and light
// channel units. Names are descriptive placeholders.
#pragma once

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

// Object lit by a channel; flag 0x80 in +08 marks it for update.
struct TrackLightTarget {
    void* vtable;             // +00
    unsigned int flags;       // +08

    void apply(const TrackLight& light, const TrackLight& base, void* table, int value); // 0x710025d19c
};

struct TrackLightNode {
    unsigned char pad[0xc0];
    unsigned char dirty;      // +c0
};

// Light tables selected by a channel's mode, reached through the GOT slot at
// 0x7100c22d98.
struct TrackLightTables {
    unsigned char pad[0x72a8];
    void* tables[3];          // +72a8
};
extern TrackLightTables* gTrackLightTables;

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
