// Matching candidates for the resource system unit (0x7100259ea8-0x710025a174).
// Status: matching/README.md.

#include "system/object_manager.h"

extern "C" void* memcpy(void* dst, const void* src, unsigned long size);   // 0x7100600870

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

class DefaultHeap {
public:
    void* allocate(unsigned int alignment, unsigned long size, int a, int b); // 0x710045c458
    void release(void* ptr, int a, int b);                                  // 0x710045c2f4
};
DefaultHeap* get_default_heap();                      // 0x710045c96c

// Chunked data: a header, a table of chunk sizes and 128-byte aligned chunks.
struct ChunkedHeader {
    unsigned int chunk_size;      // +00
    unsigned int count;           // +04
    unsigned int total_size;      // +08
    unsigned int sizes[1];        // +0c
};

struct ChunkedData {
    ChunkedHeader* header;

    void set(ChunkedHeader* value);                       // 0x7100259e84
    void nop();                                           // 0x7100259e8c
    unsigned int size() const;                            // 0x7100259e90
    void extract(void* dest);                             // 0x7100259ea8
    void* extract_allocated(DefaultHeap* heap);           // 0x710025a070
};

struct ManagerAllocator {
    unsigned char unknown[0x10];
    ResourceAllocator* allocator;  // +10
};

void ChunkedData::set(ChunkedHeader* value) {
    header = value;
}

void ChunkedData::nop() {}

unsigned int ChunkedData::size() const {
    return header ? header->total_size : 0;
}

// Major difference: register and block layout differ (see README).
void ChunkedData::extract(void* dest) {
    ChunkedHeader* h = header;
    unsigned int count = h->count;
    unsigned int total = h->total_size;
    unsigned int chunk = h->chunk_size;
    unsigned int remainder = total % chunk;
    unsigned int last = remainder == 0 ? chunk : remainder;
    ResourceAllocator* allocator = reinterpret_cast<ManagerAllocator*>(gObjectManager)->allocator;
    unsigned int scratch_size = chunk * 12 / 10 + 0x2800;
    if (scratch_size < chunk * 2)
        scratch_size = chunk * 2;
    void* scratch = nullptr;
    bool from_allocator = false;
    if (allocator) {
        scratch = allocator->alloc_aligned(scratch_size, 0x80, AllocDescriptor(0x2e));
        from_allocator = scratch != nullptr;
    }
    if (!scratch)
        scratch = get_default_heap()->allocate(0x10, scratch_size, 1, 0);
    if (!scratch)
        return;
    if (count) {
        const unsigned int* sizes = h->sizes;
        unsigned int offset = (h->count * 4 + 0x8b) & ~0x7fu;
        unsigned int out = 0;
        for (unsigned int i = 0; i < count; ++i) {
            unsigned int size = sizes[i];
            unsigned int expected = i == count - 1 ? last : chunk;
            if (size >= expected)
                memcpy(static_cast<char*>(dest) + out, reinterpret_cast<char*>(header) + offset, expected);
            unsigned int pad = size & 0x7f ? 0x80 - (size & 0x7f) : 0;
            offset = size + offset + pad;
            out += chunk;
        }
    }
    if (scratch) {
        if (from_allocator)
            allocator->free(scratch);
        else
            get_default_heap()->release(scratch, 1, 0);
    }
}

void* ChunkedData::extract_allocated(DefaultHeap* heap) {
    if (!heap)
        heap = get_default_heap();
    void* buffer = heap->allocate(0x10, size(), 1, 0);
    extract(buffer);
    return buffer;
}

class ResourceController {
public:
    unsigned char initialize();   // 0x710025acdc
    void finalize();              // 0x710025ace8
};
extern ResourceController* gResourceController;   // GOT 0x7100c2a608

class ResourceCache {
public:
    void start();                 // 0x710025b2a0
    void stop();                  // 0x710025b180
};
extern ResourceCache* gResourceCache;             // GOT 0x7100c2a610

void initialize_resource_service();               // 0x710025a388
void shutdown_resource_service();                 // 0x710025a404
void restart_resource_timer();                    // 0x710025a53c
void resource_file_nop();                         // 0x710025a568
void set_resource_file_gate(unsigned char gate);  // 0x710025a578
void create_resource_controller();                // 0x710025aad4
void destroy_resource_controller();               // 0x710025ab18
void initialize_resource_cache();                 // 0x710025b0c0
void shutdown_resource_cache();                   // 0x710025b120
void initialize_resource_queue();                 // 0x71002598c4
void shutdown_resource_queue();                   // 0x71002599dc

unsigned char initialize_resource_system() {
    initialize_resource_service();
    restart_resource_timer();
    create_resource_controller();
    if (!gResourceController->initialize())
        return 0;
    initialize_resource_cache();
    gResourceCache->start();
    initialize_resource_queue();
    return 1;
}

void shutdown_resource_system() {
    shutdown_resource_queue();
    gResourceCache->stop();
    shutdown_resource_cache();
    gResourceController->finalize();
    destroy_resource_controller();
    resource_file_nop();
    shutdown_resource_service();
}

void set_resource_system_gate(unsigned char gate) {
    set_resource_file_gate(gate);
}
