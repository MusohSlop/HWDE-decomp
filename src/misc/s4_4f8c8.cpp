// Counts the entries of the frames nested in a resource frame (fourth session, 2-copy family 4f8c8):
// FrameCounter::nested_count<0> (0x710004f8c8) and nested_count<1> (0x710004f994).

#include "resource/resource_frame.h"

class FrameCounter {
public:
    template <int Copy> unsigned int nested_count(void* storage, int enabled);
};

template <int Copy>
unsigned int FrameCounter::nested_count(void* storage, int enabled) {
    if (!enabled) return 0;
    ResourceFrame frame;
    frame.bind(0, storage);
    unsigned int n = frame.count();
    unsigned int total = 0;
    for (unsigned int i = 0; i < n; i++) {
        if (frame.entry_size(i)) {
            ResourceFrame sub;
            sub.bind(0, const_cast<void*>(frame.lookup(i)));
            total += sub.count();
        }
    }
    return total;
}

// 0x710004f8c8
template unsigned int FrameCounter::nested_count<0>(void*, int);
// 0x710004f994
template unsigned int FrameCounter::nested_count<1>(void*, int);
