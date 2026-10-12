// Matching candidates for the worker bodies 0x710045de40-0x710045e154.
// Semantics: docs/worker-lifecycle.md, docs/worker-shutdown.md. Status: matching/README.md.

#include "system/worker.h"

struct ObjectManager {
    unsigned char unknown[0x80];
    unsigned char mutex[0x20];   // +80
};
// Manager cell, reached through the GOT slot at 0x7100c21de8.
extern ObjectManager* gObjectManager;

WorkerThread* create_thread(ObjectManager* manager, int (*entry)(WorkerThread*, Worker*),
                            Worker* worker, unsigned long stack_size, int setting2, int setting1,
                            const char* name);                    // 0x71005c3f88
WorkerMutex* create_mutex(ObjectManager* manager);                // 0x71005c418c
void sleep_worker_retry();                                        // 0x7100459d10

static inline nn::os::MutexType* worker_mutex(Worker* worker) {
    return reinterpret_cast<nn::os::MutexType*>(worker->mutex->mutex);
}

static inline void release_object(RefObject* object) {
    ObjectManager** manager = &gObjectManager;
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>((*manager)->mutex));
    unsigned int count = --object->ref_count;
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>((*manager)->mutex));
    if (count == 0)
        object->destroy();
}

void initialize_worker(Worker* worker) {
    worker->mutex = nullptr;
    worker->callback = nullptr;
    worker->thread = nullptr;
    worker->ready = 1;
    worker->stop = 0;
}

void destroy_worker(Worker* worker) {
    shutdown_worker(worker);
}

void shutdown_worker(Worker* worker) {
    if (worker->thread) {
        wait_worker_ready(worker);
        worker->stop = 1;
        nn::os::SignalEvent(reinterpret_cast<nn::os::EventType*>(worker->thread->event));
        nn::os::WaitThread(reinterpret_cast<nn::os::ThreadType*>(worker->thread->handle));
        if (WorkerThread* thread = worker->thread) {
            release_object(thread);
            worker->thread = nullptr;
        }
    }
    if (WorkerMutex* mutex = worker->mutex) {
        release_object(mutex);
        worker->mutex = nullptr;
    }
}

int worker_trampoline(WorkerThread* thread, Worker* worker) {
    if (!worker->stop) {
        nn::os::EventType* event = reinterpret_cast<nn::os::EventType*>(thread->event);
        do {
            worker->callback();
            nn::os::LockMutex(worker_mutex(worker));
            worker->ready = 1;
            nn::os::UnlockMutex(worker_mutex(worker));
            nn::os::WaitEvent(event);
        } while (!worker->stop);
    }
    nn::os::LockMutex(worker_mutex(worker));
    worker->ready = 1;
    nn::os::UnlockMutex(worker_mutex(worker));
    return 0;
}

void set_worker_ready(Worker* worker, unsigned char ready) {
    nn::os::LockMutex(worker_mutex(worker));
    worker->ready = ready;
    nn::os::UnlockMutex(worker_mutex(worker));
}

void create_worker(Worker* worker, void (*callback)(), const char* name, int setting1,
                   int setting2, unsigned long stack_size) {
    worker->ready = 1;
    worker->stop = 0;
    worker->callback = callback;
    ObjectManager** manager = &gObjectManager;
    worker->thread = create_thread(*manager, worker_trampoline, worker, stack_size, setting2,
                                   setting1, name);
    worker->mutex = create_mutex(*manager);
}

void wait_worker_ready(Worker* worker) {
    while (!poll_worker_state(worker))
        sleep_worker_retry();
}

unsigned char poll_worker_state(Worker* worker) {
    nn::os::LockMutex(worker_mutex(worker));
    unsigned char ready = worker->ready;
    nn::os::UnlockMutex(worker_mutex(worker));
    return ready;
}

void start_worker(Worker* worker) {
    nn::os::LockMutex(worker_mutex(worker));
    worker->ready = 0;
    nn::os::UnlockMutex(worker_mutex(worker));
    nn::os::SignalEvent(reinterpret_cast<nn::os::EventType*>(worker->thread->event));
}

nn::os::ThreadType* worker_thread_handle(Worker* worker) {
    return reinterpret_cast<nn::os::ThreadType*>(worker->thread->handle);
}
