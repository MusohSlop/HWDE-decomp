// Matching candidates for the demo sequence bodies 0x7100217054-0x7100217294.
// Semantics: docs/demo-sequence.md. Status: matching/README.md.

#include "event/demo_sequence.h"
#include "resource/resource_frame.h"

void DemoSequence::initialize() {
    count = 0;
    owner = nullptr;
    items = nullptr;
}

void DemoSequence::empty_operation() {}

DemoSequence::DemoSequence(DemoOwner* owner_) : owner(owner_), items(nullptr), count(0) {}

DemoSequence::~DemoSequence() {
    clear();
}

void DemoSequence::clear() {
    if (items) {
        for (unsigned int i = 0; i < count; ++i)
            items[i].release();
        demo_safe_free(owner, items);
        items = nullptr;
        count = 0;
    }
}

void DemoSequence::load(void* resource) {
    ResourceFrame frame;
    frame.bind(0, resource);
    count = frame.count();
    if (count != 0) {
        unsigned int size = sizeof(DemoSequenceItem) * count;
        items = static_cast<DemoSequenceItem*>(demo_alloc(owner, size));
        for (unsigned int i = 0; i < count; ++i) {
            DemoSequenceItem& item = items[i];
            const void* source = frame.lookup(i);
            item.load(owner, static_cast<const DemoSequenceItemSource*>(source));
        }
    }
    frame.close();
}

// Near miss: only the registers of n and the scan index are swapped (see README).
float DemoSequence::sample(unsigned int index, float time) {
    if (count <= index)
        return 0.0f;
    DemoSequenceItem* item = &items[index];
    unsigned int n = static_cast<unsigned int>(item->header[0]);
    if (n == 0) {
        float v = item->header[2];
        if (item->header[3] > v)
            v = item->header[3];
        if (v > item->header[4])
            v = item->header[4];
        return v;
    }
    float value;
    unsigned int j = n;
    for (unsigned int k = 0; k < n; ++k) {
        if (item->points[k].w[0] > time) {
            j = k;
            break;
        }
    }
    if (j == 0) {
        value = item->points[0].w[1];
    } else if (j == n) {
        value = item->points[j - 1].w[4];
    } else {
        const DemoPoint& prev = item->points[j - 1];
        const DemoPoint& cur = item->points[j];
        float f = (time - prev.w[0]) / (cur.w[0] - prev.w[0]);
        if (f < 0.0f)
            f = 0.0f;
        if (f > 1.0f)
            f = 1.0f;
        float g = 1.0f - f;
        value = cur.w[1] * f + prev.w[1] * g;
    }
    if (item->header[3] > value)
        value = item->header[3];
    if (value > item->header[4])
        value = item->header[4];
    return value;
}
