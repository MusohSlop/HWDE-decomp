// Matching candidates for the demo light channel bodies
// 0x710025c7ac-0x710025cb98. Names are descriptive placeholders.
// Status: matching/README.md.

#include "event/demo_light_system.h"

TrackLightChannel::TrackLightChannel()
    : mode(-1), value4(0), count(0), index(0), targets(), nodes(), value50(0), keys(nullptr),
      value60(0) {}

void TrackLightChannel::clear() {
    mode = -1;
    value4 = -1;
    count = 0;
    index = 0;
    for (int i = 0; i < 4; ++i)
        targets[i] = nullptr;
    for (int i = 0; i < 4; ++i)
        nodes[i] = nullptr;
    value50 = 0;
    keys = nullptr;
    value60 = 0;
}

void TrackLightChannel::set_keys(TrackLight* keys_, unsigned int count_) {
    keys = keys_;
    count = count_;
}

static inline void mark_targets(TrackLightChannel* channel) {
    for (int i = 0; i < 4; ++i) {
        if (channel->targets[i])
            channel->targets[i]->flags |= 0x80;
    }
    for (int i = 0; i < 4; ++i) {
        if (channel->nodes[i])
            channel->nodes[i]->dirty = 1;
    }
}

static inline void apply_light(TrackLightChannel* channel, const TrackLight& light,
                               const TrackLight& base) {
    TrackLightTableSet* tables = &gDemoLightSystem->table_set;
    TrackLightTable* table;
    switch (channel->mode) {
    case 2:
        table = tables->tables[2];
        break;
    case 1:
        table = tables->tables[1];
        break;
    case 0:
        table = tables->tables[0];
        break;
    default:
        return;
    }
    apply_track_light(channel->targets[0], light, base, table, channel->value4);
}

void TrackLightChannel::update(const TrackLight& base, float time) {
    TrackLight light(base);
    if (!sample(&light, time)) {
        light.copy_full(base);
        light.values.z = 0;
        light.values.w = 0;
    }
    mark_targets(this);
    apply_light(this, light, base);
}

static inline float ease(float t, unsigned char level) {
    if (t < 1.0f && level != 0x80) {
        float bias = (level - 0x80) / 128.0f;
        float k = bias > 0 ? 0.5f : 1.5f;
        t = t * (t * (1.0f - k)) + t * k;
    }
    t = t < 0.0f ? 0.0f : t;
    return t > 1.0f ? 1.0f : t;
}

unsigned char TrackLightChannel::sample(TrackLight* out, float time) {
    if (count == 0)
        return 0;
    TrackLight* table = keys;
    int index;
    if (table[0].values.x >= time) {
        index = 0;
    } else {
        index = count;
        for (unsigned int i = 0; i < count; ++i) {
            const TrackLight& key = table[i];
            if ((key.values.x - 1.0f < time && key.values.y >= time) ||
                (key.values.x >= time && key.values.y < time + 1.0f)) {
                index = i;
                break;
            }
        }
    }
    if (index < 0)
        return 0;
    unsigned int prev = index != 0 ? index - 1 : 0;
    const TrackLight& from = table[prev];
    TrackLight key(table[static_cast<unsigned int>(index)]);
    unsigned char result;
    unsigned int frame = static_cast<int>(time);
    if (key.values.x > frame) {
        result = 0;
    } else {
        float t;
        float alpha_t;
        if (key.values.y == key.values.x) {
            t = 1.0f;
            alpha_t = 1.0f;
        } else {
            t = 1.0f - (key.values.y - time) / (key.values.y - key.values.x);
            alpha_t = t;
            t = ease(t, key.level2d);
        }
        if (key.values.y - key.values.x > 60.0f)
            alpha_t = (time - key.values.x) / 60.0f;
        alpha_t = ease(alpha_t, key.level2d);
        out->interpolate(key, from, t, alpha_t);
        out->values.x = key.values.x;
        out->values.y = key.values.y;
        result = 1;
    }
    return result;
}

void TrackLightChannel::update_scaled(const TrackLight& base, float time, TrackVector adjust,
                                      unsigned char alpha) {
    TrackLight light(base);
    if (sample(&light, time)) {
        light.color.a = static_cast<int>(alpha / 255.0f * light.color.a);
        light.scale20 = adjust.x * light.scale20;
        light.scale24 = adjust.y * light.scale24;
    } else {
        light.copy_full(base);
        light.values.z = 0;
        light.values.w = 0;
    }
    mark_targets(this);
    apply_light(this, light, base);
}
