// Matching candidate for the demo sequence item loader at 0x71002173c4.
// Semantics: docs/demo-sequence.md.

struct AllocDescriptor {
    unsigned short kind;
    unsigned short flags;
    void* extra;

    AllocDescriptor(unsigned short k) : kind(k), flags(0), extra(nullptr) {}
};

class DemoOwner {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void* alloc(unsigned long size, const AllocDescriptor& desc); // +0x30
};

struct DemoPoint {
    float w[8];
};
static_assert(sizeof(DemoPoint) == 0x20, "point size");

struct DemoSequenceItemSource {
    float header[6];          // +00; header[0] is the point count
    unsigned int pad[2];      // +18
    DemoPoint points[1];      // +20
};

struct DemoSequenceItem {
    DemoOwner* owner;         // +00
    float header[6];          // +08
    unsigned long pad;        // +20
    DemoPoint* points;        // +28

    void load(DemoOwner* owner, const DemoSequenceItemSource* src);
};
static_assert(sizeof(DemoSequenceItem) == 0x30, "item size");

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

