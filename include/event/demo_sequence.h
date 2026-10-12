// Demo sequence types. Semantics: docs/demo-sequence.md.
#pragma once

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
    virtual void v38();
    virtual void v40();
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void free(void* ptr);                                         // +0x60
};

// Frees through the owner when the pointer is set. The null check must stay
// in this helper: written inline in the caller it changes loop optimization.
inline void demo_safe_free(DemoOwner* owner, void* ptr) {
    if (ptr)
        owner->free(ptr);
}

struct DemoPoint {
    float w[8];               // +00 time, +04 value, +10 value past the last point
};
static_assert(sizeof(DemoPoint) == 0x20, "point size");

struct DemoSequenceItemSource {
    float header[6];          // +00; header[0] is the point count
    unsigned int pad[2];      // +18
    DemoPoint points[1];      // +20
};

struct DemoSequenceItem {
    DemoOwner* owner;         // +00
    float header[6];          // +08: count, ?, value, lower, upper, ?
    unsigned long pad;        // +20
    DemoPoint* points;        // +28

    void load(DemoOwner* owner, const DemoSequenceItemSource* src);
    void release();
};
static_assert(sizeof(DemoSequenceItem) == 0x30, "item size");

struct DemoSequence {
    DemoOwner* owner;         // +00
    DemoSequenceItem* items;  // +08
    unsigned int count;       // +10

    explicit DemoSequence(DemoOwner* owner);
    ~DemoSequence();
    void initialize();
    void empty_operation();
    void clear();
    float sample(unsigned int index, float time);
};
