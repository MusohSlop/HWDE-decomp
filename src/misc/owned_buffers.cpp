// Owned-buffer releases found by tools/family_scan.py --immediates (the shape of SlotBuffer::release
// in misc/ranked_small.cpp): each frees its buffer through the default heap's slot allocator when it
// owns one, then forgets it. They differ only in the flag and buffer offsets; types and functions are
// named after their address. Status: matching/README.md.

class SlotAllocator {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void v40();
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void free(void* ptr);                                           // +60
};
class HeapAllocatorSlot {
public:
    SlotAllocator* get();                                                   // 0x710045c2ec
};
struct HeapWithSlot {
    unsigned char pad[0x38];
    HeapAllocatorSlot slot;   // +38
};
HeapWithSlot* get_default_heap_slots();                                     // 0x710045c96c

struct OwnedBuffer132b10 {
    unsigned char pad[0xe8];
    void* buffer;             // +e8
    unsigned char padf0[0x8];
    unsigned char owned;      // +f8
};

// 0x7100132b10
void release_buffer_132b10(OwnedBuffer132b10* owner) {
    if (owner->owned && owner->buffer) {
        get_default_heap_slots()->slot.get()->free(owner->buffer);
        owner->buffer = nullptr;
    }
}

struct OwnedBuffer13eaac {
    unsigned char pad[0xb8];
    void* buffer;             // +b8
    unsigned char padc0[0x8];
    unsigned char owned;      // +c8
};

// 0x710013eaac
void release_buffer_13eaac(OwnedBuffer13eaac* owner) {
    if (owner->owned && owner->buffer) {
        get_default_heap_slots()->slot.get()->free(owner->buffer);
        owner->buffer = nullptr;
    }
}

struct OwnedBuffer193754 {
    unsigned char pad[0x78];
    void* buffer;             // +78
    unsigned char pad80[0x8];
    unsigned char owned;      // +88
};

// 0x7100193754
void release_buffer_193754(OwnedBuffer193754* owner) {
    if (owner->owned && owner->buffer) {
        get_default_heap_slots()->slot.get()->free(owner->buffer);
        owner->buffer = nullptr;
    }
}

struct OwnedBuffer1940ac {
    unsigned char pad[0x138];
    void* buffer;             // +138
    unsigned char pad140[0x8];
    unsigned char owned;      // +148
};

// 0x71001940ac
void release_buffer_1940ac(OwnedBuffer1940ac* owner) {
    if (owner->owned && owner->buffer) {
        get_default_heap_slots()->slot.get()->free(owner->buffer);
        owner->buffer = nullptr;
    }
}

struct OwnedBuffer19682c {
    unsigned char pad[0x10];
    void* buffer;             // +10
    unsigned char pad18[0x8];
    unsigned char owned;      // +20
};

// 0x710019682c
void release_buffer_19682c(OwnedBuffer19682c* owner) {
    if (owner->owned && owner->buffer) {
        get_default_heap_slots()->slot.get()->free(owner->buffer);
        owner->buffer = nullptr;
    }
}

struct OwnedBuffer19d9dc {
    unsigned char pad[0x158];
    void* buffer;             // +158
    unsigned char pad160[0x8];
    unsigned char owned;      // +168
};

// 0x710019d9dc
void release_buffer_19d9dc(OwnedBuffer19d9dc* owner) {
    if (owner->owned && owner->buffer) {
        get_default_heap_slots()->slot.get()->free(owner->buffer);
        owner->buffer = nullptr;
    }
}
