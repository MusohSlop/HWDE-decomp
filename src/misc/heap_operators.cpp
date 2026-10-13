// The global allocation entry points (0x71003cca08-0x71003cccb8), found by tools/family_scan.py:
// malloc and the operator new forms all allocate from the default heap's back frame heap (+110)
// with 0x2e as the alignment code. Status: matching/README.md.

namespace std {
struct nothrow_t {};
}  // namespace std

struct AllocParams {
    explicit AllocParams(short alignment) : alignment(alignment), flags(0), tag(0) {}

    short alignment;          // +0
    short flags;              // +2
    long tag;                 // +8
};

class FrameAllocator {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void* allocate(unsigned long size, const AllocParams& params);  // +30
    virtual void v38();
    virtual void v40();
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void free(void* ptr);                                           // +60
};

class DefaultHeap {
public:
    FrameAllocator* back_allocator() { return &back; }

    unsigned char pad[0x110];
    FrameAllocator back;      // +110
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

static inline void* heap_allocate(unsigned long size) {
    return get_default_heap()->back_allocator()->allocate(size, AllocParams(0x2e));
}

// 0x71003cca08
extern "C" void* malloc(unsigned long size) {
    return heap_allocate(size);
}

// 0x71003ccb94
void* operator new(unsigned long size) {
    return heap_allocate(size);
}

// 0x71003ccbe4
void* operator new(unsigned long size, const std::nothrow_t&) noexcept {
    return heap_allocate(size);
}

// 0x71003ccc34
void* operator new[](unsigned long size) {
    return heap_allocate(size);
}

// 0x71003ccc84
void operator delete(void* ptr) noexcept {
    get_default_heap()->back_allocator()->free(ptr);
}

// 0x71003cccb8
void operator delete[](void* ptr) noexcept {
    get_default_heap()->back_allocator()->free(ptr);
}