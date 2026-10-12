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
    void decode(const TrackLightRecord& record);
    void copy(const TrackLight& other);
    void decode_full(const TrackLightRecord& record);
    void copy_full(const TrackLight& other);
    bool equals(const TrackLight& other) const;
    void interpolate(const TrackLight& to, const TrackLight& from, float t, float alpha_t);
};

static inline void decode_light(TrackLight* light, const TrackLightRecord& record) {
    light->values.x = record.value0;
    light->values.y = record.value1;
    light->values.z = record.value2;
    light->values.w = record.value3;
    light->scale20 = record.scale20 / 100.0f;
    light->scale24 = record.scale24 / 100.0f;
    light->flag2c = record.flag2c;
    light->level2d = record.level2d;
    light->bytes2e[0] = record.bytes2e[0];
    light->bytes2e[1] = record.bytes2e[1];
    light->value30 = record.value30;
    light->value34 = record.value34;
    typedef float Float4 __attribute__((vector_size(16)));
    *reinterpret_cast<Float4*>(&light->position) =
        Float4{static_cast<float>(record.position[0]), static_cast<float>(record.position[1]),
               static_cast<float>(record.position[2]), 0};
    TrackColor color;
    color.r = record.color[0];
    color.g = record.color[1];
    color.b = record.color[2];
    color.a = record.color[3];
    light->color.set(color);
}

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

void TrackLight::decode(const TrackLightRecord& record) {
    decode_light(this, record);
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

void TrackLight::decode_full(const TrackLightRecord& record) {
    decode_light(this, record);
    flag38 = 0;
}

void TrackLight::copy_full(const TrackLight& other) {
    copy(other);
    flag38 = other.flag38;
}

static inline bool vector_equal(const TrackVector& a, const TrackVector& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

bool TrackLight::equals(const TrackLight& other) const {
    if (other.values.z != values.z)
        return false;
    if (other.values.w != values.w)
        return false;
    if (!vector_equal(other.position, position))
        return false;
    if (other.scale20 != scale20)
        return false;
    if (other.scale24 != scale24)
        return false;
    if (other.color.a != color.a)
        return false;
    return other.bytes2e[0] == bytes2e[0];
}

static inline float lerp_value(float to, float from, float t) {
    return from + (to - from) * t;
}

static inline unsigned char lerp_byte(unsigned char to, unsigned char from, float t) {
    int diff = to - from;
    float delta = diff * t;
    return static_cast<int>(from + delta);
}

// Interpolates the fields whose bit is set in to.value30 (the change mask).
void TrackLight::interpolate(const TrackLight& to, const TrackLight& from, float t, float alpha_t) {
    values.z = (to.value30 & 0x1) ? lerp_value(to.values.z, from.values.z, t) : values.z;
    values.w = (to.value30 & 0x2) ? lerp_value(to.values.w, from.values.w, t) : values.w;
    position.x = (to.value30 & 0x4) ? lerp_value(to.position.x, from.position.x, t) : position.x;
    position.y = (to.value30 & 0x8) ? lerp_value(to.position.y, from.position.y, t) : position.y;
    position.z = (to.value30 & 0x10) ? lerp_value(to.position.z, from.position.z, t) : position.z;
    position.w = 0;
    scale20 = (to.value30 & 0x20) ? lerp_value(to.scale20, from.scale20, t) : scale20;
    scale24 = (to.value30 & 0x40) ? lerp_value(to.scale24, from.scale24, t) : scale24;
    TrackColor to_color = to.color;
    unsigned int from_raw = from.color.raw;
    color.r = (to.value30 & 0x80) ? lerp_byte(to_color.r, from_raw & 0xff, t) : color.r;
    color.g = (to.value30 & 0x100) ? lerp_byte(to_color.g, (from_raw >> 8) & 0xff, t) : color.g;
    color.b = (to.value30 & 0x200) ? lerp_byte(to_color.b, (from_raw >> 16) & 0xff, t) : color.b;
    color.a = (to.value30 & 0x400) ? lerp_byte(to_color.a, from_raw >> 24, alpha_t) : color.a;
    bytes2e[0] = ((to.value30 & 0x2000) == 0 ? this : &to)->bytes2e[0];
    bytes2e[1] = ((to.value30 & 0x4000) == 0 ? this : &to)->bytes2e[1];
}

struct TrackSlot {
    unsigned long value0;     // +00
    unsigned long value8;     // +08
    unsigned int value10;     // +10
    unsigned long value18;    // +18
    unsigned long id20;       // +20

    TrackSlot();
};

TrackSlot::TrackSlot() {
    value0 = 0;
    value8 = 0;
    value10 = 0;
    value18 = 0;
    id20 = ~0ul;
}
