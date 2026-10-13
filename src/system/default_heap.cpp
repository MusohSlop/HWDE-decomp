// Matching candidates for the default heap (0x710045c1dc-0x710045c96c): the two static getters and\n// the block allocator.
// Names are descriptive placeholders. Status: matching/README.md.

namespace nn {
namespace os {
struct MutexType {
    unsigned char storage[0x20];
};
void LockMutex(MutexType* mutex);
void UnlockMutex(MutexType* mutex);
}  // namespace os
}  // namespace nn

static const unsigned long kSizeMask = 0x7fffffffffffffffUL;
static const unsigned long kKeepFlag = 0x8000000000000000UL;

// One heap block: a header followed by the payload.
struct HeapBlock {
    HeapBlock* prev;          // +00
    HeapBlock* next;          // +08
    void* data;               // +10: null while free
    unsigned long size;       // +18: bit 63 keeps the block on release
};

struct HeapLock {
    unsigned char pad[0x10];
    nn::os::MutexType mutex;  // +10
};

// Lock owned by the heap; its constructor is out of line.
class HeapMutex {
public:
    HeapMutex();                                                            // 0x71005c42b8
    unsigned char pad[0x68];
};

class DefaultHeap {
public:
    DefaultHeap() : locker(nullptr), value8(0) {
        value40 = 0;
        value38 = 2;
    }
    void* allocate(unsigned long alignment, unsigned long size, unsigned char lock,
                   unsigned char keep);                                    // 0x710045c458
    void release(void* ptr, unsigned char lock, unsigned char force);      // 0x710045c2f4

    HeapLock* locker;         // +00
    long value8;              // +08
    unsigned char pad10[0x10];
    HeapBlock* cursor;        // +20: first block worth searching
    HeapBlock* tail;          // +28
    unsigned long free_bytes; // +30
    int value38;              // +38
    long value40;             // +40
    HeapMutex mutex;          // +48
};
static_assert(sizeof(DefaultHeap) == 0xb0, "default heap size");

class FrameHeapImpl {
public:
    FrameHeapImpl();                                                        // 0x71005c2d24
    virtual ~FrameHeapImpl();
    unsigned char pad[0x58];
};

// Two frame heaps with their own vtables (GOT 0x7100c2bba0 and 0x7100c2bba8).
class FrontFrameHeap : public FrameHeapImpl {
public:
    ~FrontFrameHeap() override;
};
class BackFrameHeap : public FrameHeapImpl {
public:
    ~BackFrameHeap() override;
};

class SystemHeap : public DefaultHeap {
public:
    SystemHeap() : limit(1000), value174(0), value178(0) {}
    ~SystemHeap();

    FrontFrameHeap front;     // +b0
    BackFrameHeap back;       // +110
    int limit;                // +170
    int value174;             // +174
    int value178;             // +178
};
static_assert(sizeof(SystemHeap) == 0x180, "system heap size");

class HeapRegistry {
public:
    HeapRegistry() : first(nullptr), value8(nullptr), value10(nullptr), value20(nullptr) {}
    ~HeapRegistry();

    void* first;              // +00
    void* value8;             // +08
    void* value10;            // +10
    void* value18;            // +18
    void* value20;            // +20
    void* value28;            // +28
    void* value30;            // +30
};

// 0x710045c1dc
HeapRegistry* get_heap_registry() {
    static HeapRegistry sRegistry;
    return &sRegistry;
}

// 0x710045c96c
DefaultHeap* get_default_heap() {
    static SystemHeap sHeap;
    return &sHeap;
}

void* DefaultHeap::allocate(unsigned long alignment, unsigned long size, unsigned char lock,
                            unsigned char keep) {
    if (lock && locker)
        nn::os::LockMutex(&locker->mutex);
    void* result = nullptr;
    if (size) {
        unsigned long padded = alignment + size + 0x2e;
        unsigned long need = padded & ~0xfUL;
        if (free_bytes >= need) {
            HeapBlock* block = cursor;
            do {
                if (block->data || need + 0x20 >= (block->size & kSizeMask))
                    continue;
                HeapBlock* rest = reinterpret_cast<HeapBlock*>(reinterpret_cast<unsigned char*>(block) + need);
                rest->prev = block;
                HeapBlock* next = block->next;
                rest->next = next;
                rest->data = nullptr;
                rest->size = (block->size - need) & kSizeMask;
                if (next)
                    next->prev = rest;
                block->size = padded & 0x7ffffffffffffff0UL;
                block->next = rest;
                block->data = block + 1;
                cursor = rest;
                if (tail < rest)
                    tail = rest;
                free_bytes -= need;
                unsigned long data = reinterpret_cast<unsigned long>(block->data);
                unsigned long size_bits = block->size;
                unsigned long misalign = data % alignment;
                unsigned long aligned = data + (misalign ? alignment - misalign : 0);
                result = reinterpret_cast<void*>(aligned);
                block->data = result;
                block->size = keep ? size_bits | kKeepFlag : size_bits & kSizeMask;
                break;
            } while ((block = block->next));
        }
    }
    if (lock && locker)
        nn::os::UnlockMutex(&locker->mutex);
    return result;
}

void DefaultHeap::release(void* ptr, unsigned char lock, unsigned char force) {
    if (lock && locker)
        nn::os::LockMutex(&locker->mutex);
    if (ptr) {
        HeapBlock* block = tail;
        while ((block = block->prev)) {
            if (block->data != ptr)
                continue;
            if (!force && (block->size & kKeepFlag))
                break;
            block->data = nullptr;
            if (tail->prev == block)
                tail = block;
            free_bytes += block->size & kSizeMask;
            HeapBlock* merged = block;
            HeapBlock* prev = block->prev;
            if (prev && !prev->data) {
                HeapBlock* next = block->next;
                prev->next = next;
                prev->size = (prev->size + block->size) & kSizeMask;
                if (next)
                    next->prev = prev;
                else
                    tail = prev;
                merged = prev;
            }
            HeapBlock* next = merged->next;
            if (next && !next->data) {
                merged->size = (merged->size + next->size) & kSizeMask;
                next->prev = nullptr;
                next->size = 0;
                HeapBlock* after = next->next;
                merged->next = after;
                if (after)
                    after->prev = merged;
                else
                    tail = merged;
            }
            if (cursor > merged)
                cursor = merged;
            break;
        }
    }
    if (lock && locker)
        nn::os::UnlockMutex(&locker->mutex);
}
