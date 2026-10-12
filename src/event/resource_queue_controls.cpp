// Matching candidates for the resource queue registry at 0x7100c8af40.
// Semantics: docs/resource-queue-controls.md.

namespace nn {
namespace os {
struct MutexType;
void LockMutex(MutexType* mutex);
void UnlockMutex(MutexType* mutex);
}  // namespace os
}  // namespace nn

class ResourceQueueReference {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void destroy();   // +0x18

    unsigned int ref_count;   // +08
    nn::os::MutexType* mutex_storage[1]; // +10: the mutex object itself
};

struct ResourceQueueManager {
    unsigned char unknown[0x80];
    nn::os::MutexType* mutex_storage[1]; // +80
};
// Elapsed step added to running entries, reached through the GOT slot at 0x7100c21df0.
extern unsigned int gResourceQueueElapsedStep;
// Byte at 0x7100c8af38 that enables the high worker.
extern unsigned char gResourceQueueHighEnabled __attribute__((visibility("hidden")));
// Manager cell, reached through the GOT slot at 0x7100c21de8.
extern ResourceQueueManager* gResourceQueueManager;

struct ResourceQueueWorker {
    unsigned char data[0x20];
};

struct SharedState;
SharedState* get_shared_state();                      // 0x71002aae3c
unsigned char shared_state_exiting(SharedState* state); // 0x71002ac7f0
void wait_worker_ready(ResourceQueueWorker* worker);  // 0x710045e094
unsigned char poll_worker_state(ResourceQueueWorker* worker); // 0x710045e0d8
void shutdown_worker(ResourceQueueWorker* worker);    // 0x710045de58
void start_worker(ResourceQueueWorker* worker);       // 0x710045e114
void* get_frame_source();                             // 0x71003ad9cc
unsigned char frame_source_skipping(void* source);    // 0x71003adbe0


struct ResourceQueueEntry {
    unsigned int state;       // +00
    void* callback;           // +08
    void (*completion)(int, unsigned int); // +10
    unsigned int argument;    // +18
    unsigned int elapsed;     // +1c
};
static_assert(sizeof(ResourceQueueEntry) == 0x20, "entry size");

struct __attribute__((packed)) ResourceQueueRegistry {
    unsigned char active;     // +00
    bool flag1;               // +01
    volatile bool flag2;      // +02
    unsigned char pad03[5];   // +03
    ResourceQueueReference* reference; // +08
    void* unknown10;          // +10
    void* worker_callback;    // +18
    void* high_worker_callback; // +20
    ResourceQueueEntry entries[8]; // +28
};
static_assert(sizeof(ResourceQueueRegistry) == 0x128, "registry size");

// Worker controls at 0x7100c8aef8; defined with the worker lifecycle code.
extern ResourceQueueWorker gResourceQueueWorkers[2] __attribute__((visibility("hidden")));
// Registry at 0x7100c8af40, defined in another unit. The declaration has
// alignment 1 (packed type), which keeps the 16-bit clears unfolded.
extern ResourceQueueRegistry gResourceQueueRegistry __attribute__((visibility("hidden")));

static nn::os::MutexType* registry_mutex() {
    return reinterpret_cast<nn::os::MutexType*>(gResourceQueueRegistry.reference->mutex_storage);
}

unsigned char resource_queue_active() {
    return gResourceQueueRegistry.active;
}

static inline unsigned int entry_priority(const ResourceQueueEntry& entry) {
    return entry.state == 3 ? 0x100 : entry.state == 2 ? 0 : entry.argument;
}

// Field-wise copy: the four bytes at +4 stay with the destination.
static inline void copy_entry(ResourceQueueEntry& dst, const ResourceQueueEntry& src) {
    dst.state = src.state;
    dst.callback = src.callback;
    dst.completion = src.completion;
    dst.argument = src.argument;
    dst.elapsed = src.elapsed;
}

// Exchange sort that keeps the threshold captured before the inner loop.
static inline void sort_entries(ResourceQueueEntry* entries, unsigned int count) {
    if (count < 2)
        return;
    for (unsigned int i = 0; i < count - 1; ++i) {
        unsigned int key = entry_priority(entries[i]);
        for (unsigned int j = i + 1; j < count; ++j) {
            if (key > entry_priority(entries[j])) {
                ResourceQueueEntry tmp;
                copy_entry(tmp, entries[i]);
                copy_entry(entries[i], entries[j]);
                copy_entry(entries[j], tmp);
            }
        }
    }
}

void process_resource_queue() {
    ResourceQueueEntry running[8];
    ResourceQueueEntry waiting[8];
    ResourceQueueEntry finished[8];
    unsigned int running_count = 0;
    unsigned int waiting_count = 0;
    unsigned int finished_count = 0;
    unsigned int empty_count = 0;
    for (int i = 0; i < 8; ++i) {
        const ResourceQueueEntry& entry = gResourceQueueRegistry.entries[i];
        if (entry.state == 2) {
            copy_entry(running[running_count], entry);
            ++running_count;
        } else if (entry.state == 1) {
            copy_entry(waiting[waiting_count], entry);
            ++waiting_count;
        } else if (entry.state == 3) {
            copy_entry(finished[finished_count], entry);
            ++finished_count;
        } else {
            ++empty_count;
        }
    }
    unsigned int index = 0;
    sort_entries(running, running_count);
    for (unsigned int i = 0; i < running_count; ++i)
        copy_entry(gResourceQueueRegistry.entries[index++], running[i]);
    sort_entries(waiting, waiting_count);
    for (unsigned int i = 0; i < waiting_count; ++i)
        copy_entry(gResourceQueueRegistry.entries[index++], waiting[i]);
    for (unsigned int i = 0; i < empty_count; ++i) {
        ResourceQueueEntry& entry = gResourceQueueRegistry.entries[index++];
        entry.state = 0;
        entry.callback = nullptr;
        entry.completion = nullptr;
        entry.argument = 0x100;
        entry.elapsed = 0;
    }
    sort_entries(finished, finished_count);
    for (unsigned int i = 0; i < finished_count; ++i)
        copy_entry(gResourceQueueRegistry.entries[index++], finished[i]);
}

void cancel_resource_queue() {
    nn::os::LockMutex(registry_mutex());
    if (gResourceQueueRegistry.active == 1) {
        gResourceQueueRegistry.flag1 = true;
        gResourceQueueRegistry.flag2 = true;
    }
    gResourceQueueRegistry.worker_callback = nullptr;
    gResourceQueueRegistry.high_worker_callback = nullptr;
    for (int i = 0; i < 8; ++i) {
        ResourceQueueEntry& entry = gResourceQueueRegistry.entries[i];
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

void register_resource_callback(void* callback, void (*completion)(int, unsigned int),
                                unsigned int argument) {
    nn::os::LockMutex(registry_mutex());
    gResourceQueueRegistry.flag1 = false;
    gResourceQueueRegistry.flag2 = false;
    for (int i = 0; i < 8; ++i) {
        ResourceQueueEntry& entry = gResourceQueueRegistry.entries[i];
        if (entry.callback == callback)
            break;
        if (entry.state == 0) {
            entry.state = 1;
            entry.callback = callback;
            entry.completion = completion;
            entry.argument = argument;
            entry.elapsed = 0;
            break;
        }
    }
    process_resource_queue();
    nn::os::UnlockMutex(registry_mutex());
}

void remove_resource_callback(void* callback) {
    nn::os::LockMutex(registry_mutex());
    int i;
    for (i = 0; i < 8; ++i) {
        if (gResourceQueueRegistry.entries[i].callback == callback)
            break;
    }
    if (i != 8) {
        ResourceQueueEntry& entry = gResourceQueueRegistry.entries[i];
        if (entry.state != 2) {
            entry.state = 0;
            entry.callback = nullptr;
            entry.completion = nullptr;
            entry.argument = 0x100;
            entry.elapsed = 0;
        }
    }
    process_resource_queue();
    nn::os::UnlockMutex(registry_mutex());
}

void shutdown_resource_queue() {
    cancel_resource_queue();
    if (!shared_state_exiting(get_shared_state())) {
        shutdown_worker(&gResourceQueueWorkers[0]);
        shutdown_worker(&gResourceQueueWorkers[1]);
    }
    ResourceQueueReference* reference = gResourceQueueRegistry.reference;
    if (!reference)
        return;
    ResourceQueueManager** manager = &gResourceQueueManager;
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>((*manager)->mutex_storage));
    unsigned int count = --reference->ref_count;
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>((*manager)->mutex_storage));
    if (count == 0)
        reference->destroy();
    gResourceQueueRegistry.reference = nullptr;
}

bool resource_queue_has_callback(void* callback) {
    bool found = false;
    for (int i = 0; i < 8; ++i)
        found |= gResourceQueueRegistry.entries[i].callback == callback;
    return found;
}

bool finish_resource_queue(unsigned char wait, unsigned char unused, unsigned char skip_exit_check) {
    if (gResourceQueueRegistry.active != 1)
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
    gResourceQueueRegistry.active = 0;
    gResourceQueueRegistry.flag1 = false;
    return true;
}

// Marks the first entry with this callback as finished, then postprocesses.
static void complete_resource_callback(void* callback) {
    int i;
    for (i = 0; i < 8; ++i) {
        if (gResourceQueueRegistry.entries[i].callback == callback)
            break;
    }
    if (i != 8)
        gResourceQueueRegistry.entries[i].state = 3;
    process_resource_queue();
}

void update_resource_queue() {
    if (frame_source_skipping(get_frame_source())) {
        finish_resource_queue(0, 0, 0);
        return;
    }
    nn::os::LockMutex(registry_mutex());
    if (!finish_resource_queue(0, 0, 0) || gResourceQueueRegistry.flag2) {
        unsigned char done = poll_worker_state(&gResourceQueueWorkers[1]);
        void* id = gResourceQueueRegistry.high_worker_callback;
        unsigned char idle = (id == nullptr) | (done != 0);
        if (done && id) {
            complete_resource_callback(id);
            idle = 1;
            gResourceQueueRegistry.high_worker_callback = nullptr;
        }
        ResourceQueueEntry& entry = gResourceQueueRegistry.entries[1];
        if (entry.argument == 0x1f && entry.callback && idle && entry.state == 1 && gResourceQueueHighEnabled) {
            gResourceQueueRegistry.active = 1;
            gResourceQueueRegistry.flag1 = false;
            gResourceQueueRegistry.flag2 = false;
            gResourceQueueRegistry.high_worker_callback = entry.callback;
            start_worker(&gResourceQueueWorkers[1]);
            entry.state = 2;
            entry.elapsed = 0;
        }
    } else {
        if (void* id = gResourceQueueRegistry.worker_callback) {
            complete_resource_callback(id);
            gResourceQueueRegistry.worker_callback = nullptr;
        }
        if (void* id = gResourceQueueRegistry.high_worker_callback) {
            complete_resource_callback(id);
            gResourceQueueRegistry.high_worker_callback = nullptr;
        }
        ResourceQueueEntry& entry = gResourceQueueRegistry.entries[0];
        if (entry.callback && entry.state == 1) {
            if (!(gResourceQueueRegistry.active & 1)) {
                gResourceQueueRegistry.active = 1;
                gResourceQueueRegistry.flag1 = false;
                gResourceQueueRegistry.flag2 = false;
                gResourceQueueRegistry.worker_callback = entry.callback;
                start_worker(&gResourceQueueWorkers[0]);
            }
            entry.state = 2;
            entry.elapsed = 0;
        }
    }
    if (!shared_state_exiting(get_shared_state())) {
        for (int i = 0; i < 8; ++i) {
            ResourceQueueEntry& entry = gResourceQueueRegistry.entries[i];
            if (entry.callback && entry.completion) {
                unsigned int state = entry.state;
                if (state - 1 < 2)
                    entry.elapsed += gResourceQueueElapsedStep;
                entry.completion(state, entry.elapsed);
            }
        }
    }
    nn::os::UnlockMutex(registry_mutex());
}

unsigned int resource_queue_callback_state(void* callback) {
    for (int i = 0; i < 8; ++i) {
        if (gResourceQueueRegistry.entries[i].callback == callback)
            return gResourceQueueRegistry.entries[i].state;
    }
    return 0;
}

bool resource_queue_callback_in_state(void* callback, unsigned int state) {
    for (int i = 0; i < 8; ++i) {
        if (gResourceQueueRegistry.entries[i].callback == callback)
            return gResourceQueueRegistry.entries[i].state == state;
    }
    return false;
}

int resource_queue_callback_count() {
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        if (gResourceQueueRegistry.entries[i].callback)
            ++count;
    }
    return count;
}







