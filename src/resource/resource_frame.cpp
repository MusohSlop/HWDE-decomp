// Matching candidates for the resource frame bodies 0x710025b394-0x710025b754.
// Semantics: docs/resource-frame.md. Status: matching/README.md.

#include "resource/resource_frame.h"

struct AllocDescriptor {
    unsigned short kind;
    unsigned short flags;
    void* extra;

    AllocDescriptor(unsigned short k) : kind(k), flags(0), extra(nullptr) {}
};

class DefaultHeap {
public:
    void* allocate(unsigned int alignment, unsigned long size, int a, int b); // 0x710045c458
    void release(void* ptr, int a, int b);                                  // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

unsigned int resource_size(unsigned int identity);                          // 0x710025a178
void* resource_read(unsigned int identity, void* dest, unsigned int offset,
                    unsigned int size, void* owner, unsigned int flags);    // 0x710025a1ac
void resource_free(void* storage);                                          // 0x710025a1ec

static inline void* frame_alloc(ResourceAllocator* allocator, unsigned int size) {
    return allocator->alloc_aligned(size, 0x10, AllocDescriptor(0x2e));
}

static inline void* heap_alloc(unsigned int size) {
    return get_default_heap()->allocate(0x10, size, 1, 0);
}

// First body of the unit (0x710025b390); its name is a placeholder.
void resource_frame_nop() {}

ResourceFrame::ResourceFrame()
    : mStorage(nullptr), mHeaderWords(0), mStride(0), mIdentity(0xffffffff), mAllocator(nullptr),
      mOwnsStorage(false), mTable(false) {}

ResourceFrame::~ResourceFrame() {
    close();
}

void ResourceFrame::close() {
    if (mOwnsStorage) {
        if (mStorage) {
            if (mAllocator)
                mAllocator->free(mStorage);
            else
                resource_free(mStorage);
            mStorage = nullptr;
        }
        mOwnsStorage = false;
    }
    mIdentity = 0xffffffff;
    mAllocator = nullptr;
}

bool ResourceFrame::is_open() const {
    return mStorage != nullptr;
}

inline void ResourceFrame::set_layout(int mode) {
    switch (mode) {
    case 0:
        mHeaderWords = 1;
        mStride = 2;
        break;
    case 1:
        mHeaderWords = 1;
        mStride = 1;
        break;
    case 2:
        mHeaderWords = 0;
        mStride = 2;
        break;
    }
}

void ResourceFrame::bind(int mode, void* storage) {
    mStorage = storage;
    set_layout(mode);
}

bool ResourceFrame::open(int mode, unsigned int identity, ResourceAllocator* allocator) {
    void* data;
    if (allocator) {
        unsigned int size = resource_size(identity);
        if (size)
            frame_alloc(allocator, size);
        data = resource_read(identity, nullptr, 0, 0, nullptr, 0);
        if (!data)
            return false;
        mAllocator = allocator;
    } else {
        data = resource_read(identity, nullptr, 0, 0, nullptr, 0);
        if (!data)
            return false;
    }
    mStorage = data;
    set_layout(mode);
    mIdentity = identity;
    mOwnsStorage = true;
    return true;
}

bool ResourceFrame::open_table(int mode, unsigned int identity, ResourceAllocator* allocator) {
    unsigned int count = 0;
    resource_read(identity, &count, 0, 4, nullptr, 0);
    if (count == 0)
        return false;
    unsigned int size = (count << 3) | 4;
    void* buffer = allocator ? allocator->alloc_aligned(size, 0x10, AllocDescriptor(0x2e)) : nullptr;
    void* data = resource_read(identity, buffer, 0, size, nullptr, 0);
    if (!data) {
        if (buffer)
            allocator->free(buffer);
        return false;
    }
    mStorage = data;
    set_layout(mode);
    mIdentity = identity;
    mAllocator = allocator;
    mOwnsStorage = true;
    mTable = true;
    return true;
}

unsigned int ResourceFrame::count() const {
    return *static_cast<const unsigned int*>(mStorage);
}

unsigned int ResourceFrame::entry_offset(unsigned int index) const {
    const unsigned int* table = static_cast<const unsigned int*>(mStorage) + mHeaderWords;
    return table[mStride * index];
}

unsigned int ResourceFrame::entry_size(unsigned int index) const {
    const unsigned int* table = static_cast<const unsigned int*>(mStorage) + mHeaderWords;
    const unsigned int* entry = table + mStride * index;
    return entry[1];
}

const void* ResourceFrame::lookup(unsigned int index) const {
    return static_cast<const char*>(mStorage) + entry_offset(index);
}

void* ResourceFrame::load(unsigned int index, void* dest, unsigned int size) {
    if (size == 0)
        size = entry_size(index);
    unsigned int offset = entry_offset(index);
    bool owned = dest == nullptr;
    void* buffer = dest;
    if (owned)
        buffer = heap_alloc(size);
    void* result = resource_read(mIdentity, buffer, offset, size, nullptr, 0);
    void* ret = result ? buffer : nullptr;
    if (!result && owned) {
        get_default_heap()->release(buffer, 1, 0);
        ret = nullptr;
    }
    return ret;
}
