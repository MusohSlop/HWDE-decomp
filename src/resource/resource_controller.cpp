// Matching candidates for the resource controller unit (0x710025aa48-0x710025adf0).
// Semantics: docs/resource-metadata.md, docs/resource-read.md. Status: matching/README.md.

#include "resource/resource_file.h"
#include "resource/resource_name.h"

struct AllocDescriptor {
    unsigned short kind;
    unsigned short flags;
    void* extra;

    AllocDescriptor(unsigned short k) : kind(k), flags(0), extra(nullptr) {}
};

class ResourceAllocator {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void* alloc_aligned(unsigned long size, unsigned int alignment,
                                const AllocDescriptor& desc);   // +0x40
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void free(void* ptr);                               // +0x60
};

struct HeapAllocatorSlot {
    ResourceAllocator* get();                                    // 0x710045c2ec
};

class DefaultHeap {
public:
    unsigned int budget();                                                  // 0x710045c450
    void* allocate(unsigned int alignment, unsigned long size, int a, int b); // 0x710045c458
    void release(void* ptr, int a, int b);                                  // 0x710045c2f4

    unsigned char unknown[0x38];
    HeapAllocatorSlot allocator;  // +38
};
DefaultHeap* get_default_heap();                      // 0x710045c96c

class DirectFile {
public:
    DirectFile();                                                     // 0x710053e410
    ~DirectFile();                                                    // 0x710053e440
    unsigned char open(const char* path, int mode, int a, void* b);   // 0x710053e488
    void close();                                                     // 0x710053e510
    void read(void* dest, unsigned long position, unsigned long size); // 0x710053e554

private:
    unsigned char storage[0x10];
};

struct SharedState;
SharedState* get_shared_state();                      // 0x71002aae3c
unsigned char shared_state_exiting(SharedState* s);   // 0x71002ac7f0
unsigned char resource_queue_cancelled();             // 0x71002589c0
unsigned char resource_busy();                        // 0x7100259aec
void set_resource_waiting(unsigned char waiting);     // 0x7100259e44
void sleep_milliseconds(unsigned int ms);             // 0x7100459d18
unsigned long get_system_tick();                      // 0x71006009e0
unsigned long get_system_tick_frequency();            // 0x71006009f0

extern "C" int snprintf(char* buffer, unsigned long size, const char* format, ...);  // 0x7100600b30

struct RegionSettings;
RegionSettings* get_region_settings();                // 0x710020bd74
int region_kind(RegionSettings* settings);            // 0x710020c22c

// Name table, reached through the GOT slot at 0x7100c2a620.
extern const char* const gResourceNames[];

unsigned char resource_file_gate();                   // 0x710025a56c
void set_resource_file_gate(unsigned char gate);      // 0x710025a578

class ResourceController {
public:
    void resolve_name(char* buffer, int identity);            // 0x710025ab58
    unsigned char initialize();                               // 0x710025acdc
    void finalize();                                          // 0x710025ace8
    unsigned int size(unsigned int identity);                 // 0x710025acec
    void* read(int identity, void* dest, unsigned int offset, unsigned int size,
               DefaultHeap* heap, int flags);                 // 0x710025adf0

private:
    float mLastReadTime;          // +00: seconds at the end of the last read
    unsigned char unknown[0x12874];
    unsigned int mCachedSize;     // +12878: size of resource 0x4a1e, or all bits set
};

// Controller cell at 0x7100c8b098, reached through the GOT slot at 0x7100c2a608.
extern ResourceController* gResourceController;

unsigned char ResourceFile::read_direct(void* dest, unsigned long position, unsigned long size) {
    mDest = dest;
    mPosition = position;
    mSize = size;
    DirectFile file;
    unsigned char result;
    if (file.open(mName, 0x1006, 2, nullptr)) {
        file.read(mDest, mPosition, size);
        file.close();
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

void create_resource_controller() {
    ResourceController** cell = &gResourceController;
    if (!*cell)
        *cell = static_cast<ResourceController*>(get_default_heap()->allocate(0x10, 4, 1, 0));
}

void destroy_resource_controller() {
    ResourceController** cell = &gResourceController;
    if (ResourceController* controller = *cell)
        get_default_heap()->release(controller, 1, 0);
    *cell = nullptr;
}

static inline unsigned int query_size(const char* path) {
    ResourceName name;
    name.set(path);
    return name.exists() ? name.size() : 0;
}

static inline unsigned int query_size_cached(const char* path, unsigned int* cache) {
    ResourceName name;
    name.set(path);
    unsigned int result = name.exists() ? name.size() : 0;
    *cache = result;
    name.finish();
    return result;
}

// Identities 0x834-0x944 are remapped when the region kind is 1. The cases were
// generated from the original jump table at 0x71007f4c48.
void ResourceController::resolve_name(char* buffer, int identity) {
    RegionSettings* settings = get_region_settings();
    if (settings && region_kind(settings) == 1) {
        switch (identity) {
        case 0x834:
            identity = 0x712;
            break;
        case 0x838:
            identity = 0x5ad;
            break;
        case 0x839:
            identity = 0x5af;
            break;
        case 0x83a:
            identity = 0x5b0;
            break;
        case 0x83b:
            identity = 0x5bd;
            break;
        case 0x83c:
            identity = 0x5b3;
            break;
        case 0x83d:
            identity = 0x5be;
            break;
        case 0x83f:
            identity = 0x5c0;
            break;
        case 0x840:
            identity = 0x5c1;
            break;
        case 0x841:
            identity = 0x5c2;
            break;
        case 0x842:
            identity = 0x5c3;
            break;
        case 0x843:
            identity = 0x5c4;
            break;
        case 0x84b:
            identity = 0x5ac;
            break;
        case 0x84c:
            identity = 0x5b9;
            break;
        case 0x84d:
            identity = 0x5ba;
            break;
        case 0x84e:
            identity = 0x5b2;
            break;
        case 0x84f:
            identity = 0x5b5;
            break;
        case 0x851:
            identity = 0x5c9;
            break;
        case 0x852:
            identity = 0x5c5;
            break;
        case 0x858:
            identity = 0x5a9;
            break;
        case 0x859:
            identity = 0x5aa;
            break;
        case 0x85a:
            identity = 0x5a6;
            break;
        case 0x85b:
            identity = 0x5b1;
            break;
        case 0x85c:
            identity = 0x5b4;
            break;
        case 0x85d:
            identity = 0x5b6;
            break;
        case 0x85e:
            identity = 0x5b7;
            break;
        case 0x860:
            identity = 0x5bb;
            break;
        case 0x861:
            identity = 0x5bc;
            break;
        case 0x944:
            identity = 0x5ae;
            break;
        case 0x85f:
            identity = 0x5b8;
            break;
        }
    }
    const char* name = gResourceNames[identity];
    if (*name)
        snprintf(buffer, 0x100, "%s/%s/%s", "rom:", "data", name);
    else
        buffer[0] = 0;
}

unsigned char ResourceController::initialize() {
    mLastReadTime = 0;
    return 1;
}

void ResourceController::finalize() {}

unsigned int ResourceController::size(unsigned int identity) {
    unsigned char gate = resource_file_gate();
    set_resource_file_gate(0);
    char path[0x100];
    unsigned int result;
    if (identity == 0x4a1e) {
        result = mCachedSize;
        if (result == 0xffffffff)
            result = query_size_cached(path, &mCachedSize);
    } else {
        resolve_name(path, identity);
        result = query_size(path);
    }
    set_resource_file_gate(gate);
    return result;
}

// Near miss: register assignment of the offset, size and length values differs (see README).
void* ResourceController::read(int identity, void* dest, unsigned int offset, unsigned int size,
                               DefaultHeap* heap, int flags) {
    if (identity > 0x4a1d)
        return nullptr;
    char path[0x100];
    resolve_name(path, identity);
    if (!path[0])
        return nullptr;
    if (resource_busy()) {
        set_resource_waiting(1);
        while (resource_busy())
            sleep_milliseconds(10);
        set_resource_waiting(0);
    }
    if (resource_queue_cancelled())
        return nullptr;
    if (shared_state_exiting(get_shared_state()))
        return nullptr;
    unsigned int file_size = this->size(identity);
    if (!file_size)
        return nullptr;
    bool from_allocator = false;
    unsigned int start = file_size > offset ? offset : 0;
    unsigned int remaining = file_size - start;
    unsigned int length = size == 0 ? remaining : (remaining > size ? size : remaining);
    void* buffer = dest;
    if (!dest) {
        if (heap)
            flags = 0;
        else
            heap = get_default_heap();
        if (heap->budget() < length) {
            buffer = get_default_heap()->allocator.get()->alloc_aligned(length, 0x10, AllocDescriptor(0x2e));
            from_allocator = true;
        } else {
            buffer = heap->allocate(0x10, length, 1, flags);
            from_allocator = false;
        }
        if (!buffer)
            return nullptr;
    }
    ResourceFile file;
    file.set_name(path, 1, 1);
    unsigned long done = 0;
    while (length) {
        unsigned int chunk = length > 0xa00000 ? 0xa00000 : length;
        if (!file.run(static_cast<char*>(buffer) + done, start + static_cast<unsigned int>(done), chunk)) {
            if (!dest) {
                DefaultHeap* release_heap = get_default_heap();
                if (from_allocator)
                    release_heap->allocator.get()->free(buffer);
                else
                    release_heap->release(buffer, 1, 0);
            }
            file.close();
            return nullptr;
        }
        length -= chunk;
        done += 0xa00000;
    }
    file.close();
    mLastReadTime = static_cast<float>(get_system_tick()) / static_cast<float>(get_system_tick_frequency());
    if (resource_queue_cancelled()) {
        if (dest)
            return nullptr;
    } else {
        bool keep = dest != nullptr;
        unsigned char exiting = shared_state_exiting(get_shared_state());
        void* ret = exiting ? nullptr : buffer;
        if (!exiting || keep)
            return ret;
    }
    DefaultHeap* release_heap = get_default_heap();
    if (from_allocator)
        release_heap->allocator.get()->free(buffer);
    else
        release_heap->release(buffer, 1, 0);
    return nullptr;
}
