// Demo track resource handles. Names are descriptive placeholders.
#pragma once

#include "system/worker.h"

struct TrackResources {
    RefObject* primary;       // +00
    RefObject* secondary;     // +08
    RefObject* extra;         // +10

    TrackResources();
    ~TrackResources();
    void release();
    void reset();
    void clear();
    void load(unsigned int id);
    RefObject* load_one(unsigned int id);
};
