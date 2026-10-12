// Matching candidates for the demo light set bodies 0x710025c254-0x710025c6c0.
// Names are descriptive placeholders. Status: matching/README.md.

#include "event/demo_sequence.h"
#include "event/demo_track.h"
#include "resource/resource_frame.h"

inline void* operator new(unsigned long, void* where) noexcept { return where; }

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

TrackLightSet::TrackLightSet(DemoOwner* owner_, int value24_)
    : owner(owner_), channels(nullptr), count(0), keys(nullptr), value20(-1), value24(value24_) {}

unsigned int TrackLightSet::load(void* resource) {
    for (unsigned int i = 0; i < count + 1; ++i) {
        if (keys && keys[i]) {
            owner->free(keys[i]);
            keys[i] = nullptr;
        }
    }
    release(keys);
    release(channels);
    keys = nullptr;
    channels = nullptr;
    count = 0;
    value20 = -1;

    ResourceFrame frame;
    frame.bind(0, resource);
    const short* header = static_cast<const short*>(frame.lookup(0));
    unsigned int n = header[0];
    int value = header[3];
    int first_count = header[1];
    count = n;
    value20 = value;
    unsigned int size = (n + 1) * sizeof(TrackLightChannel);
    channels = static_cast<TrackLightChannel*>(demo_alloc(owner, size));
    keys = static_cast<TrackLight**>(demo_alloc(owner, (count + 1) * sizeof(TrackLight*)));
    TrackLightChannel* first = new (channels) TrackLightChannel;
    channels = first;
    first->clear();
    first->index = -1;
    first->value50 = value24;
    first->mode = -1;
    first->value4 = -1;
    first->count = first_count;
    for (unsigned int i = 0; i < count; ++i) {
        TrackLightChannel* channel = &channels[i + 1];
        channel->clear();
        channel->index = i;
        channel->value50 = value24;
        const short* entry = &header[4 + i * 4];
        channel->mode = entry[0];
        channel->value4 = entry[1];
        channel->count = entry[2];
    }

    const TrackLightRecord* records = static_cast<const TrackLightRecord*>(frame.lookup(1));
    unsigned int base = 0;
    for (unsigned int i = 0; i < count + 1; ++i) {
        unsigned int& key_count = channels[i].count;
        unsigned int total = key_count;
        if (total != 0) {
            keys[i] = static_cast<TrackLight*>(demo_alloc(owner, total * sizeof(TrackLight)));
            keys[i] = new (keys[i]) TrackLight;
            const TrackLightRecord* source = &records[base];
            TrackLight* current = keys[i];
            current->decode_full(source[0]);
            unsigned int removed = 0;
            unsigned int out = 1;
            for (unsigned long k = 1; k < total; ++k) {
                TrackLight light(source[k]);
                unsigned char same = current->equals(light);
                if (!same || !current->flag38) {
                    current = &keys[i][out++];
                    current->decode_full(source[k]);
                    if (same)
                        current->flag38 = 1;
                } else {
                    current->values.y = light.values.y;
                    ++removed;
                    key_count = total - removed;
                }
            }
        } else {
            keys[i] = nullptr;
        }
        base += total;
        channels[i].set_keys(keys[i], key_count);
    }
    frame.close();
    return n;
}

void TrackLightSet::update(float time) {
    TrackLight light;
    channels[0].sample(&light, time);
    for (unsigned int i = 0; i < count; ++i)
        channels[i + 1].update(light, time);
}

// adjust: scale20 and scale24 factors, then values.z and values.w offsets.
// Near miss: the original pairs the values.w load and store differently (see README).
void TrackLightSet::update_scaled(float time, TrackVector adjust, unsigned char alpha) {
    TrackLight light;
    channels[0].sample(&light, time);
    light.scale20 = adjust.x * light.scale20;
    light.values.w = adjust.w + light.values.w;
    light.scale24 = adjust.y * light.scale24;
    light.values.z = adjust.z + light.values.z;
    for (unsigned int i = 0; i < count; ++i)
        channels[i + 1].update_scaled(light, time, adjust, alpha);
}
