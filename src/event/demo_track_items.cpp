// Matching candidates for the small demo-track item bodies after the resource
// frame (0x710025b828-0x710025bd64). Names are descriptive placeholders.
// Status: matching/README.md.

struct TrackKey {
    unsigned long value0;     // +00
    unsigned long value8;     // +08
    float value10;            // +10
    unsigned int index14;     // +14
    unsigned int index18;     // +18
    unsigned int value1c;     // +1c
    unsigned long id20;       // +20
    unsigned long id28;       // +28

    TrackKey();
    explicit TrackKey(unsigned long value);
    ~TrackKey();
};

TrackKey::TrackKey() {
    value0 = 0;
    value8 = 0;
    value10 = 0;
    index14 = 0xffffffff;
    index18 = 0xffffffff;
    value1c = 0;
    id20 = ~0ul;
    id28 = ~0ul;
}

TrackKey::~TrackKey() {}

TrackKey::TrackKey(unsigned long value) {
    value0 = value;
    value8 = 0;
    value10 = 0;
    index14 = 0xffffffff;
    index18 = 0xffffffff;
    id20 = ~0ul;
    id28 = ~0ul;
}

void track_key_nop() {}

struct TrackVector {
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

struct TrackLight {
    TrackVector position;     // +00
    TrackVector values;       // +10
    float scale20;            // +20
    float scale24;            // +24
    TrackColor color;         // +28
    unsigned char flag2c;     // +2c
    unsigned char level2d;    // +2d
    unsigned char bytes2e[2]; // +2e
    unsigned short value30;   // +30
    unsigned int value34;     // +34
    unsigned char flag38;     // +38

    void reset();
    void copy(const TrackLight& other);
};

void track_light_nop() {}

void TrackLight::reset() {
    position = kTrackDefaultVector;
    values = TrackVector{0, 0, 0, 0};
    scale20 = 1.0f;
    scale24 = 1.0f;
    color.raw = 0;
    flag2c = 0;
    level2d = 0x80;
    bytes2e[0] = 0;
    bytes2e[1] = 0;
    value30 = 0;
    value34 = 0;
    flag38 = 0;
}

void TrackLight::copy(const TrackLight& other) {
    values.x = other.values.x;
    values.y = other.values.y;
    values.z = other.values.z;
    values.w = other.values.w;
    scale20 = other.scale20;
    scale24 = other.scale24;
    flag2c = other.flag2c;
    level2d = other.level2d;
    bytes2e[0] = other.bytes2e[0];
    bytes2e[1] = other.bytes2e[1];
    value30 = other.value30;
    value34 = other.value34;
    position = other.position;
    color.set(other.color);
}

void track_item_nop() {}
