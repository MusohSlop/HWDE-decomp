// Matching candidates for the demo light target bodies 0x710025d014-0x710025d19c.
// Names are descriptive placeholders. Status: matching/README.md.

#include "event/demo_track.h"

extern "C" float sqrtf(float value);

// Rotates point around origin by angle (radians) into out.
void rotate_point(TrackVec2* out, const TrackVec2* origin, const TrackVec2* point,
                  float angle);                                             // 0x71001f714c

class TrackRenderer {
public:
    void begin(int mode);                                                   // 0x71001df744
    void write(void* data, unsigned int size, int slot);                    // 0x71001df8c0
    void end();                                                             // 0x71001df838
};
// Reached through the GOT slot at 0x7100c22a40.
extern TrackRenderer* gTrackRenderer;

static const float kTwoPi = 6.28318548f;
static const float kPi = 3.14159274f;
static const float kHalfPi = 1.57079637f;
static const float kDegToRad = 0.0174532924f;

// Polynomial cosine: Taylor terms to x^6 near zero, the sine series near pi/2.
static inline float track_cos(float x) {
    if (x == 0.0f)
        return 1.0f;
    float a = x < 0.0f ? -x : x;
    while (a >= kTwoPi)
        a -= kTwoPi;
    bool low = !(a >= kPi);
    float b = low ? a : a - kPi;
    bool lower = !(b >= kHalfPi);
    float c = lower ? b : kPi - b;
    if (!(c >= 0.908318520f)) {
        float c2 = c * c;
        if (low != lower)
            return ((c2 - 30.0f) * (c2 * c2 + 360.0f) + 10080.0f) * (1.0f / 720.0f);
        return ((30.0f - c2) * (c2 * c2 + 360.0f) - 10080.0f) * (1.0f / 720.0f);
    }
    float d = kHalfPi - c;
    float d2 = d * d;
    float d4 = d2 * d2;
    return d * ((low != lower) ? (d2 - 6.0f) * 20.0f - d4 : d4 + (6.0f - d2) * 20.0f) * (1.0f / 120.0f);
}

// Polynomial sine, the counterpart of track_cos.
static inline float track_sin(float x) {
    if (x == 0.0f)
        return 0.0f;
    float a = x < 0.0f ? -x : x;
    while (a >= kTwoPi)
        a -= kTwoPi;
    bool low = !(a >= kPi);
    bool positive = (x < 0.0f) != low;
    float b = low ? a : a - kPi;
    float c = !(b >= kHalfPi) ? b : kPi - b;
    if (!(c >= 0.668318510f)) {
        float c2 = c * c;
        float c4 = c2 * c2;
        return c * (positive ? c4 + (6.0f - c2) * 20.0f : (c2 - 6.0f) * 20.0f - c4) * (1.0f / 120.0f);
    }
    float d = kHalfPi - c;
    float d2 = d * d;
    if (positive)
        return ((30.0f - d2) * (d2 * d2 + 360.0f) - 10080.0f) * (1.0f / 720.0f);
    return ((d2 - 30.0f) * (d2 * d2 + 360.0f) + 10080.0f) * (1.0f / 720.0f);
}

void TrackLightTarget::build_quad(TrackLightTable* table, const TrackLight& light, int index) {
    unsigned int size = table->items[index]->size;
    float width = (size & 0xffff) * (light.scale20 + 0.0f);
    float height = (size >> 16) * (light.scale24 + 0.0f);
    TrackVec2 center = {light.values.z, light.values.w};
    float left = width * -0.5f;
    float right = width * 0.5f;
    float bottom = height * 0.5f;
    float top = height * -0.5f;
    TrackVec2 c0 = {left, top};
    TrackVec2 c1 = {right, top};
    TrackVec2 c2 = {left, bottom};
    TrackVec2 c3 = {right, bottom};
    value18[0] = 0.0f;
    value18[1] = 0.0f;
    matrix[0] = 1.0f;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 1.0f;
    scale[1] = 1.0f;
    scale[0] = 1.0f;
    image = index >= 0 && index < table->count ? table->items[index] : nullptr;
    float angle = light.position.z;
    if (angle != 0.0f) {
        float radians = angle * kDegToRad;
        rotate_point(&c0, &center, &c0, radians);
        rotate_point(&c1, &center, &c1, radians);
        rotate_point(&c2, &center, &c2, radians);
        rotate_point(&c3, &center, &c3, radians);
        quad[0] = c0;
        quad[1] = c1;
        quad[2] = c2;
        quad[3] = c3;
    } else {
        quad[0].x = center.x - width * 0.5f;
        quad[0].y = center.y - height * 0.5f;
        quad[1].x = center.x + width * 0.5f;
        quad[1].y = center.y - height * 0.5f;
        quad[2].x = center.x - width * 0.5f;
        quad[2].y = center.y + height * 0.5f;
        quad[3].x = center.x + width * 0.5f;
        quad[3].y = center.y + height * 0.5f;
    }
}

void apply_track_light(TrackLightTarget* target, const TrackLight& light, const TrackLight& base,
                       TrackLightTable* table, int index) {
    if (!target)
        return;
    if (light.bytes2e[0] == 0 || light.color.a == 0) {
        target->flags |= 0x80;
        return;
    }
    target->flags &= ~0x80u;
    if (!table)
        return;
    TrackLight shown(light);
    if (base.position.z < -1.1920929e-05f || base.position.z > 1.1920929e-05f) {
        float dy = light.values.w * base.scale24 * 4.5f;
        float dx = light.values.z * base.scale20 * 4.8f;
        float length = sqrtf(dx * dx + dy * dy);
        float x;
        if (dx >= 0.0f)
            x = base.values.z * 4.8f + length * track_cos(base.position.z * kDegToRad);
        else
            x = base.values.z - length * track_cos(base.position.z * kDegToRad);
        float y;
        if (dy >= 0.0f)
            y = base.values.w * 4.5f - length * track_sin(base.position.z * kDegToRad);
        else
            y = base.values.w + length * track_sin(base.position.z * kDegToRad);
        shown.values.z = x;
        shown.values.w = dy + y;
    } else {
        shown.values.z = base.values.z * 4.8f + light.values.z * 4.8f * base.scale20 +
                         (table->items[index]->size & 0xffff) * light.scale20 * 0.25f * 0.5f;
        shown.values.w = base.values.w * 4.5f + light.values.w * 4.5f * base.scale24 +
                         (table->items[index]->size >> 16) * light.scale24 * 0.25f * 0.5f;
    }
    target->build_quad(table, shown, index);
    target->blend = light.flag2c;
    target->colors[0] = light.color;
    target->colors[1] = light.color;
    target->colors[2] = light.color;
    target->colors[3] = light.color;
    target->value78 = 0;
    TrackRenderer* renderer = gTrackRenderer;
    renderer->begin(0x10);
    renderer->write(target, 0x88, -1);
    renderer->end();
}
