// Matching candidates for the resource queue registry at 0x7100c8af40.
// Semantics: docs/resource-queue-controls.md.

namespace nn {
namespace os {
struct MutexType;
void LockMutex(MutexType* mutex);
void UnlockMutex(MutexType* mutex);
}  // namespace os
}  // namespace nn

struct ResourceQueueReference {
    unsigned char unknown[0x10];
    nn::os::MutexType* mutex_storage[1]; // +10: the mutex object itself
};

struct ResourceQueueWorker {
    unsigned char data[0x20];
};

struct SharedState;
SharedState* get_shared_state();                      // 0x71002aae3c
unsigned char shared_state_exiting(SharedState* state); // 0x71002ac7f0
void wait_worker_ready(ResourceQueueWorker* worker);  // 0x710045e094
unsigned char poll_worker_state(ResourceQueueWorker* worker); // 0x710045e0d8

struct ResourceQueueEntry {
    unsigned int state;       // +00
    void* callback;           // +08
    void (*completion)(int, unsigned int); // +10
    unsigned int argument;    // +18
    unsigned int elapsed;     // +1c
};
static_assert(sizeof(ResourceQueueEntry) == 0x20, "entry size");

struct ResourceQueueRegistry {
    unsigned char active;     // +00
    volatile bool flag1;      // +01
    volatile bool flag2;      // +02
    ResourceQueueReference* reference; // +08
    void* unknown10;          // +10
    void* worker_callback;    // +18
    void* high_worker_callback; // +20
    ResourceQueueEntry entries[8]; // +28
};
static_assert(sizeof(ResourceQueueRegistry) == 0x128, "registry size");

// Worker controls at 0x7100c8aef8; defined with the worker lifecycle code.
extern ResourceQueueWorker gResourceQueueWorkers[2] __attribute__((visibility("hidden")));
static ResourceQueueRegistry sRegistry;

static nn::os::MutexType* registry_mutex() {
    return reinterpret_cast<nn::os::MutexType*>(sRegistry.reference->mutex_storage);
}

unsigned char resource_queue_active() {
    return sRegistry.active;
}

void cancel_resource_queue() {
    nn::os::LockMutex(registry_mutex());
    if (sRegistry.active == 1) {
        sRegistry.flag1 = true;
        sRegistry.flag2 = true;
    }
    sRegistry.worker_callback = nullptr;
    sRegistry.high_worker_callback = nullptr;
    for (int i = 0; i < 8; ++i) {
        ResourceQueueEntry& entry = sRegistry.entries[i];
        if (entry.callback && entry.completion)
            entry.completion(4, entry.elapsed);
        entry.state = 0;
        entry.callback = nullptr;
        entry.completion = nullptr;
        entry.argument = 0x100;
        entry.elapsed = 0;
    }
    nn::os::UnlockMutex(registry_mutex());
}

bool finish_resource_queue(unsigned char wait, unsigned char unused, unsigned char skip_exit_check) {
    if (sRegistry.active != 1)
        return true;
    if (!skip_exit_check && shared_state_exiting(get_shared_state()))
        return true;
    if (wait) {
        wait_worker_ready(&gResourceQueueWorkers[0]);
        wait_worker_ready(&gResourceQueueWorkers[1]);
    } else {
        if (!poll_worker_state(&gResourceQueueWorkers[0]))
            return false;
        if (!poll_worker_state(&gResourceQueueWorkers[1]))
            return false;
    }
    sRegistry.active = 0;
    sRegistry.flag1 = false;
    return true;
}

unsigned int resource_queue_callback_state(void* callback) {
    for (int i = 0; i < 8; ++i) {
        if (sRegistry.entries[i].callback == callback)
            return sRegistry.entries[i].state;
    }
    return 0;
}

bool resource_queue_callback_in_state(void* callback, unsigned int state) {
    for (int i = 0; i < 8; ++i) {
        if (sRegistry.entries[i].callback == callback)
            return sRegistry.entries[i].state == state;
    }
    return false;
}

int resource_queue_callback_count() {
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        if (sRegistry.entries[i].callback)
            ++count;
    }
    return count;
}

// Keep the static registry referenced from outside so it is not folded away.
ResourceQueueRegistry* resource_queue_registry() { return &sRegistry; }




