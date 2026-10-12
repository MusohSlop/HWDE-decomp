// Matching candidates for the demo light table set bodies 0x710025ffe8-0x71002605d0.
// Names are descriptive placeholders. Status: matching/README.md.

#include "event/demo_light_system.h"
#include "resource/resource_frame.h"

inline void* operator new(unsigned long, void* where) noexcept { return where; }

struct SharedState {
    int value0;
    int mode;                 // +4
};
SharedState* get_shared_state();                                            // 0x71002aae3c

class ResourceLoaderCore {
public:
    void flush();                                                           // 0x710052ad98
};
// Reached through the GOT slot at 0x7100c21db0.
extern ResourceLoaderCore* gResourceLoader;

TrackLightTableSet::TrackLightTableSet()
    : allocator(nullptr), counts(), count126a0(0), buffer(nullptr) {}

TrackLightTableSet::~TrackLightTableSet() {}

void TrackLightTableSet::init(LightAllocator* allocator_) {
    allocator = allocator_;
    count126a0 = 0;
    resources.release();
}

void TrackLightTableSet::finalize() {
    resources.reset();
}

void TrackLightTableSet::unload() {
    gResourceLoader->flush();
    for (int i = 0; i < 192; ++i)
        entries[i].unload();
    if (buffer)
        allocator->free(buffer);
    resources.clear();
}

void TrackLightTableSet::load(int stage, float* times) {
    resources.load(stage);
    int base = get_shared_state()->mode == 0 || get_shared_state()->mode == 9 ||
                       get_shared_state()->mode == 11 || get_shared_state()->mode == 10
                   ? 0x3d87
                   : 0x3e10;
    load_tracks(base + stage, times);
}

static inline bool counts_full(LightCounts counts) {
    return counts.targets > 0x100 || counts.entries >= 0xc1;
}

int TrackLightTableSet::load_tracks(unsigned int id, float* times) {
    ResourceFrame frame;
    int result = 0;
    if (frame.open(0, id, nullptr)) {
        count126a0 = frame.count() - 1;
        const short* header = static_cast<const short*>(frame.lookup(0));
        times[1] = header[0];
        times[2] = header[1];
        times[3] = header[2];
        result = static_cast<unsigned short>(header[3]);
        buffer = demo_alloc(allocator, count126a0 * sizeof(TrackLightSet));
        buffer = new (buffer) TrackSlot;
        void* records = const_cast<void*>(frame.lookup(1));
        TrackLightSet* first = count126a0 != 0 ? static_cast<TrackLightSet*>(buffer) : nullptr;
        new (first) TrackLightSet(allocator, 0);
        first->load(records);
        for (unsigned int i = 1; i < count126a0; ++i) {
            void* source = const_cast<void*>(frame.lookup(i + 1));
            TrackLightSet* set = count126a0 > i ? &static_cast<TrackLightSet*>(buffer)[i] : nullptr;
            new (set) TrackLightSet(allocator, i);
            set->load(source);
            unsigned int count = set->count;
            for (unsigned int c = 1; c <= count; ++c) {
                unsigned int next = counts.targets + 1;
                if (next > 0x100) {
                    counts.targets = 0x101;
                } else {
                    TrackLightChannel* channels = set->channels;
                    TrackLightTarget* target = &targets[counts.targets];
                    counts.targets = next;
                    channels[c].targets[0] = target;
                }
            }
            count = set->count;
            for (unsigned int c = 1; c <= count; ++c) {
                unsigned int next = counts.entries + 1;
                if (next > 0xc0) {
                    counts.entries = 0xc1;
                } else {
                    TrackLightChannel* channels = set->channels;
                    counts.entries = next;
                    LightEntry* entry = &entries[next - 1];
                    entry->bind(allocator);
                    channels[c].nodes[0] = reinterpret_cast<TrackLightNode*>(entry);
                }
            }
            unsigned long both = counts.raw;
            if (static_cast<unsigned int>(both) > 0x100 || static_cast<unsigned int>(both >> 32) >= 0xc1)
                break;
        }
        frame.close();
    }
    return result;
}