// Matching candidates for the demo sequence item bodies 0x71002173c4 and 0x71002174d0.
// Semantics: docs/demo-sequence.md. Status: matching/README.md.

#include "event/demo_sequence.h"

void DemoSequenceItem::load(DemoOwner* owner_, const DemoSequenceItemSource* src) {
    owner = owner_;
    for (int i = 0; i < 6; ++i)
        header[i] = src->header[i];
    unsigned int n = static_cast<unsigned int>(header[0]);
    if (n == 0) {
        points = nullptr;
        return;
    }
    points = static_cast<DemoPoint*>(owner_->alloc(n << 5, AllocDescriptor(0x2e)));
    for (unsigned int i = 0; i < n; ++i) {
        DemoPoint& dst = points[i];
        const DemoPoint& from = src->points[i];
        for (int k = 0; k < 8; ++k)
            dst.w[k] = from.w[k];
    }
}

void DemoSequenceItem::release() {
    demo_safe_free(owner, points);
    points = nullptr;
}
