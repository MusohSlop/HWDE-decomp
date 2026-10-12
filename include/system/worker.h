// Worker thread controls. Semantics: docs/worker-lifecycle.md, docs/worker-shutdown.md.
#pragma once

namespace nn {
namespace os {
struct MutexType;
struct ThreadType;
struct EventType;
void LockMutex(MutexType* mutex);
void UnlockMutex(MutexType* mutex);
void SignalEvent(EventType* event);
void WaitEvent(EventType* event);
void WaitThread(ThreadType* thread);
}  // namespace os
}  // namespace nn

// Reference-counted system object; the manager's mutex guards the count.
class RefObject {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void destroy();   // +0x18

    unsigned int ref_count;   // +08
};

class WorkerMutex : public RefObject {
public:
    alignas(8) unsigned char mutex[0x20];   // +10: nn::os::MutexType storage
};

class WorkerThread : public RefObject {
public:
    alignas(8) unsigned char handle[0x1c0]; // +10: nn::os::ThreadType storage
    unsigned char event[0x20];   // +1d0: nn::os::EventType storage
};

struct Worker {
    WorkerThread* thread;     // +00
    WorkerMutex* mutex;       // +08
    void (*callback)();       // +10
    unsigned char ready;      // +18
    unsigned char stop;       // +19
};
static_assert(sizeof(Worker) == 0x20, "worker size");
static_assert(__builtin_offsetof(WorkerThread, event) == 0x1d0, "thread event offset");

void wait_worker_ready(Worker* worker);           // 0x710045e094
unsigned char poll_worker_state(Worker* worker);  // 0x710045e0d8
void start_worker(Worker* worker);                // 0x710045e114
void shutdown_worker(Worker* worker);             // 0x710045de58
