// Matching candidates for the resource queue registry at 0x7100c8af40.
// Semantics: docs/resource-queue-controls.md.

struct ResourceQueueEntry {
    unsigned int state;       // +00
    void* callback;           // +08
    void (*completion)(int, unsigned int); // +10
    unsigned int argument;    // +18
    unsigned int elapsed;     // +1c
};
static_assert(sizeof(ResourceQueueEntry) == 0x20, "entry size");

struct ResourceQueueRegistry {
    bool active;              // +00
    bool flag1;               // +01
    bool flag2;               // +02
    void* reference;          // +08
    void* mutex;              // +10
    void* worker_callback;    // +18
    void* high_worker_callback; // +20
    ResourceQueueEntry entries[8]; // +28
};
static_assert(sizeof(ResourceQueueRegistry) == 0x128, "registry size");

static ResourceQueueRegistry sRegistry;

bool resource_queue_active() {
    return sRegistry.active;
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
