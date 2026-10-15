// libc++'s vector<T*>::__push_back_slow_path with the game's heap allocator (fourth session, 0x71001e4f1c): the
// allocator asks the heap (0x71004599b4) for its limit, allocates through it with an allocation tag and frees through
// it, so the old elements move one at a time. Names are descriptive placeholders.

#include "misc/s4_libcxx.h"

struct HeapTag {
    HeapTag(short t) : tag(t), flags(0), extra(0) {}

    short tag;                // +00
    short flags;              // +02
    long extra;               // +08
};

class GameHeap {
public:
    virtual void v00();
    virtual void v08();
    virtual unsigned long max_bytes();  // +10
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void* alloc(unsigned long size, unsigned int alignment, const HeapTag& tag);  // +40
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void free(void* p);  // +60
};
GameHeap* game_heap_4599b4();                                               // 0x71004599b4

template <class T, short Tag>
struct HeapAllocator {
    static T* allocate(size_t n) {
        return static_cast<T*>(game_heap_4599b4()->alloc(n * sizeof(T), alignof(T), HeapTag(Tag)));
    }
    static void deallocate(T* p, size_t) { game_heap_4599b4()->free(p); }
    static size_t max_size() { return game_heap_4599b4()->max_bytes() / sizeof(T); }
};

struct DrawEntry;
// 0x71001e4f1c
template void VectorA<DrawEntry*, HeapAllocator<DrawEntry*, 0x2e> >::push_back_slow_path(DrawEntry* const&);