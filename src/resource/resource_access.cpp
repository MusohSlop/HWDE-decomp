// Matching candidates for the resource access helpers 0x710025a178-0x710025a258.
// Semantics: docs/resource-open.md, docs/resource-full-open.md. Status: matching/README.md.

#include "resource/resource_frame.h"
#include "system/worker.h"

extern "C" void* memset(void* dst, int value, unsigned long size);   // 0x7100600890
void* operator new(unsigned long size);                               // 0x71003ccb94
void operator delete(void* ptr) noexcept;                              // 0x71003ccc84
void nn_yield_thread();                                                // 0x7100600b20 (nn::os::YieldThread)
void sleep_worker_retry();                                             // 0x7100459d10

void initialize_worker(Worker* worker);                                // 0x710045de40
void destroy_worker(Worker* worker);                                   // 0x710045de54
void create_worker(Worker* worker, void (*callback)(), const char* name, int setting1,
                   int setting2, unsigned long stack_size);            // 0x710045e028

class FileSystem {
public:
    unsigned int open(const char* path, int a, int b, void** handle, void* c, int d); // 0x71005374a4
    unsigned long size(void* handle);                                                 // 0x71005374d0
    void close(void** handle, int a);                                                 // 0x71005374ac
};

struct ObjectManager {
    unsigned char unknown[0x80];
    unsigned char mutex[0x20];   // +80
    unsigned char unknown_a0[0x28];
    FileSystem* file_system;     // +c8
};
// Manager cell, reached through the GOT slot at 0x7100c21de8.
extern ObjectManager* gObjectManager;
WorkerMutex* create_mutex(ObjectManager* manager);                     // 0x71005c418c

struct ResourceInfo {
    unsigned long unknown00;     // +00
    unsigned long size;          // +08
    unsigned char unknown10[0x418];
};
static_assert(sizeof(ResourceInfo) == 0x428, "info size");

struct ResourceName {
    const char* path;
};

struct ResourceRequest {
    unsigned int result;         // +00
    ResourceInfo* info;          // +08
    const char* path;            // +10
};

struct ResourceService {
    Worker worker;               // +00
    WorkerMutex* mutex;          // +20

    ResourceService() {
        initialize_worker(&worker);   // the Worker constructor
        mutex = nullptr;
    }
    ~ResourceService() { destroy_worker(&worker); }
};

// Service cell at 0x7100c8b068 and request block at 0x7100c8b070.
extern ResourceService* gResourceService __attribute__((visibility("hidden")));
extern ResourceRequest gResourceRequest __attribute__((visibility("hidden")));

struct SharedState;
SharedState* get_shared_state();                                 // 0x71002aae3c
void* shared_state_resources(SharedState* state);                // 0x71002ad1dc
unsigned char shared_state_exiting(SharedState* state);          // 0x71002ac7f0

class ResourceController {
public:
    unsigned int size(unsigned int identity);                    // 0x710025acec
    void* read(unsigned int identity, void* dest, unsigned int offset, unsigned int size,
               void* owner, unsigned int flags);                 // 0x710025adf0
};
// Controller cell at 0x7100c8b098, reached through the GOT slot at 0x7100c2a608.
extern ResourceController* gResourceController;

struct MemoryRegion {
    void* begin;              // +00
    void* unknown08;          // +08
    unsigned long end;        // +10: storage above this belongs to the default heap
};
MemoryRegion* get_memory_region();                               // 0x710045c1dc

struct HeapAllocatorSlot {
    ResourceAllocator* get();                                    // 0x710045c2ec
};

class DefaultHeap {
public:
    void* allocate(unsigned int alignment, unsigned int size, int a, int b); // 0x710045c458
    void release(void* ptr, int a, int b);                                  // 0x710045c2f4

    unsigned char unknown[0x38];
    HeapAllocatorSlot allocator;  // +38
};
DefaultHeap* get_default_heap();                                 // 0x710045c96c

unsigned int resource_size(unsigned int identity) {
    shared_state_resources(get_shared_state());
    return gResourceController->size(identity);
}

void* resource_read(unsigned int identity, void* dest, unsigned int offset, unsigned int size,
                    void* owner, unsigned int flags) {
    return gResourceController->read(identity, dest, offset, size, owner, flags);
}

void resource_free(void* storage) {
    unsigned long end = get_memory_region()->end;
    DefaultHeap* heap = get_default_heap();
    if (reinterpret_cast<unsigned long>(storage) > end)
        heap->release(storage, 1, 0);
    else
        heap->allocator.get()->free(storage);
}

static inline void release_object(RefObject* object) {
    ObjectManager** manager = &gObjectManager;
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>((*manager)->mutex));
    unsigned int count = --object->ref_count;
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>((*manager)->mutex));
    if (count == 0)
        object->destroy();
}

unsigned int query_resource_info(ResourceService* service, const char* path, ResourceInfo* info);

bool resource_info_exists(const ResourceName* name) {
    ResourceInfo info;
    return query_resource_info(gResourceService, name->path, &info) == 0;
}

unsigned int query_resource_info(ResourceService* service, const char* path, ResourceInfo* info) {
    if (shared_state_exiting(get_shared_state()))
        return 0;
    if (service->mutex)
        nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(service->mutex->mutex));
    gResourceRequest.info = info;
    gResourceRequest.path = path;
    start_worker(&service->worker);
    while (!poll_worker_state(&service->worker)) {
        nn_yield_thread();
        sleep_worker_retry();
    }
    shared_state_exiting(get_shared_state());
    if (service->mutex)
        nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(service->mutex->mutex));
    return gResourceRequest.result;
}

unsigned long resource_info_size(const ResourceName* name) {
    ResourceInfo info;
    if (query_resource_info(gResourceService, name->path, &info) != 0)
        return 0;
    return info.size;
}

static void run_resource_metadata_worker();

void initialize_resource_service() {
    if (gResourceService)
        return;
    ResourceService* service = new ResourceService;
    gResourceService = service;
    service->mutex = create_mutex(gObjectManager);
    create_worker(&service->worker, run_resource_metadata_worker, "FileInfoGetter", 2, 2, 0x10000);
}

void shutdown_resource_service() {
    ResourceService* service = gResourceService;
    if (!service)
        return;
    if (WorkerMutex* mutex = service->mutex) {
        release_object(mutex);
        service->mutex = nullptr;
        shutdown_worker(&service->worker);
    }
    delete gResourceService;
    gResourceService = nullptr;
}

static void run_resource_metadata_worker() {
    ResourceRequest* request = &gResourceRequest;
    memset(request->info, 0, sizeof(ResourceInfo));
    FileSystem* fs = gObjectManager->file_system;
    void* handle;
    request->result = fs->open(request->path, 1, 2, &handle, nullptr, 0);
    if (request->result == 0) {
        request->info->size = fs->size(handle);
        fs->close(&handle, 0);
    }
}

// Trivial bodies that follow; names are placeholders.
struct ResourceHandle {
    void* ptr;

    ResourceHandle();
    ~ResourceHandle();
    void empty_operation();
    void set(void* value);
};

ResourceHandle::ResourceHandle() : ptr(nullptr) {}
ResourceHandle::~ResourceHandle() {}
void ResourceHandle::empty_operation() {}
void ResourceHandle::set(void* value) {
    ptr = value;
}
