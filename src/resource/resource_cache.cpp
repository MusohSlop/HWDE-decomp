// Matching candidates for the resource cache unit (0x710025b0c0-0x710025b390).
// Status: matching/README.md.

#include "resource/resource_file.h"
#include "system/object_manager.h"
#include "system/worker.h"

extern "C" void* memset(void* dst, int value, unsigned long size);   // 0x7100600890

struct SharedState;
SharedState* get_shared_state();                      // 0x71002aae3c
unsigned char shared_state_exiting(SharedState* s);   // 0x71002ac7f0

class DefaultHeap {
public:
    void* allocate(unsigned int alignment, unsigned long size, int a, int b); // 0x710045c458
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                      // 0x710045c96c

void initialize_worker(Worker* worker);               // 0x710045de40 (Worker constructor)
void destroy_worker(Worker* worker);                  // 0x710045de54 (Worker destructor)
void create_worker(Worker* worker, void (*callback)(), const char* name, int setting1,
                   int setting2, unsigned long stack_size);  // 0x710045e028
WorkerMutex* create_mutex(ObjectManager* manager);    // 0x71005c418c

struct ResourceCacheRequest {
    ResourceFile* file;       // +00
    void* dest;               // +08
    unsigned long size;       // +10
    unsigned long position;   // +18
    unsigned char failed;     // +20
};

class ResourceCache {
public:
    void start();             // 0x710025b2a0
    void stop();              // 0x710025b180

    unsigned char unknown[0x800];
    Worker reader0;           // +800
    Worker reader1;           // +820
    Worker writer;            // +840
    ResourceCacheRequest read;    // +860
    ResourceCacheRequest direct;  // +888
    WorkerMutex* mutex;       // +8b0
};
static_assert(sizeof(ResourceCache) == 0x8b8, "cache size");

// Cache cell, reached through the GOT slot at 0x7100c2a610.
extern ResourceCache* gResourceCache;

static inline void release_object(RefObject* object) {
    ObjectManager** manager = &gObjectManager;
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>((*manager)->mutex));
    unsigned int count = --object->ref_count;
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>((*manager)->mutex));
    if (count == 0)
        object->destroy();
}

void initialize_resource_cache() {
    ResourceCache** cell = &gResourceCache;
    if (*cell)
        return;
    ResourceCache* cache = static_cast<ResourceCache*>(get_default_heap()->allocate(0x10, sizeof(ResourceCache), 1, 0));
    initialize_worker(&cache->reader0);
    initialize_worker(&cache->reader1);
    initialize_worker(&cache->writer);
    *cell = cache;
}

void shutdown_resource_cache() {
    ResourceCache** cell = &gResourceCache;
    if (ResourceCache* cache = *cell) {
        cache->stop();
        destroy_worker(&cache->writer);
        destroy_worker(&cache->reader1);
        destroy_worker(&cache->reader0);
        get_default_heap()->release(cache, 1, 0);
    }
    *cell = nullptr;
}

void ResourceCache::stop() {
    if (!shared_state_exiting(get_shared_state())) {
        shutdown_worker(&writer);
        shutdown_worker(&reader0);
        shutdown_worker(&reader1);
    }
    if (WorkerMutex* m = mutex) {
        release_object(m);
        mutex = nullptr;
    }
}

void run_resource_cache_read() {
    ResourceCache* cache = gResourceCache;
    cache->read.failed = !cache->read.file->run(cache->read.dest, cache->read.position, cache->read.size);
}

void run_resource_cache_direct() {
    ResourceCache* cache = gResourceCache;
    cache->direct.failed =
        !cache->direct.file->read_direct(cache->direct.dest, cache->direct.position, cache->direct.size);
}

void ResourceCache::start() {
    create_worker(&reader0, run_resource_cache_read, "FileReader", 2, 2, 0x4000);
    create_worker(&reader1, run_resource_cache_read, "FileReader", 2, 2, 0x4000);
    create_worker(&writer, run_resource_cache_direct, "FileWriter", 0, 2, 0x4000);
    read.failed = 0;
    read.position = 0;
    read.size = 0;
    read.dest = nullptr;
    read.file = nullptr;
    direct.failed = 0;
    direct.position = 0;
    direct.size = 0;
    direct.dest = nullptr;
    direct.file = nullptr;
    mutex = create_mutex(gObjectManager);
}
