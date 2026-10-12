// Matching candidates for the demo track resource handle bodies
// 0x710025cd44-0x710025cf10. Names are descriptive placeholders.
// Status: matching/README.md.

#include "event/demo_track_resources.h"

static inline void release_ref(RefObject*& ref) {
    RefObject* object = ref;
    if (object) {
        if (--object->ref_count == 0)
            object->destroy();
        ref = nullptr;
    }
}

TrackResources::TrackResources() : primary(nullptr), secondary(nullptr), extra(nullptr) {}

void TrackResources::update() {}

void TrackResources::release() {
    release_ref(extra);
    release_ref(secondary);
    release_ref(primary);
}

void TrackResources::reset() {
    release_ref(extra);
    release_ref(secondary);
    release_ref(primary);
}

void TrackResources::clear() {
    release_ref(extra);
    release_ref(secondary);
    release_ref(primary);
}

void TrackResources::load(unsigned int id) {
    primary = load_one(0x3c70);
    secondary = load_one(id + 0x3c75);
    extra = nullptr;
}
