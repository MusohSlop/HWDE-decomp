// Worker barriers found by tools/family_scan.py --immediates: each counts one more arrival under the
// pool's lock and, when every worker has arrived, signals each worker's event. They differ only in
// which arrival counter they use; types and functions are named after their address.
// Status: matching/README.md.

namespace nn {
namespace os {
struct MutexType;
struct EventType;
void SignalEvent(EventType* event);
void LockMutex(MutexType* mutex);
void UnlockMutex(MutexType* mutex);
}  // namespace os
}  // namespace nn

struct PoolThread {
    unsigned char pad[0x1d0];
    unsigned char wake_event[1]; // +1d0
};
struct PoolWorker {
    unsigned char pad[8];
    PoolThread* thread;       // +08
    unsigned char pad10[0x30];
};
struct PoolLock {
    unsigned char pad[0x10];
    unsigned char mutex[1];   // +10
};

struct WorkerPool55610c {
    unsigned char pad[0x170];
    PoolWorker* workers;      // +170
    unsigned int worker_count; // +178
    unsigned char pad17c[4];
    PoolLock* lock;           // +180
    volatile unsigned int arrived; // +188
};

// 0x710055610c
void arrive_55610c(WorkerPool55610c* pool) {
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(pool->lock->mutex));
    ++pool->arrived;
    if (pool->arrived == pool->worker_count) {
        for (unsigned int i = 0; i < pool->worker_count; ++i)
            nn::os::SignalEvent(reinterpret_cast<nn::os::EventType*>(pool->workers[i].thread->wake_event));
    }
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(pool->lock->mutex));
}

struct WorkerPool556188 {
    unsigned char pad[0x170];
    PoolWorker* workers;      // +170
    unsigned int worker_count; // +178
    unsigned char pad17c[4];
    PoolLock* lock;           // +180
    unsigned char pad188[0x4];
    volatile unsigned int arrived; // +18c
};

// 0x7100556188
void arrive_556188(WorkerPool556188* pool) {
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(pool->lock->mutex));
    ++pool->arrived;
    if (pool->arrived == pool->worker_count) {
        for (unsigned int i = 0; i < pool->worker_count; ++i)
            nn::os::SignalEvent(reinterpret_cast<nn::os::EventType*>(pool->workers[i].thread->wake_event));
    }
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(pool->lock->mutex));
}

struct WorkerPool556204 {
    unsigned char pad[0x170];
    PoolWorker* workers;      // +170
    unsigned int worker_count; // +178
    unsigned char pad17c[4];
    PoolLock* lock;           // +180
    unsigned char pad188[0x8];
    volatile unsigned int arrived; // +190
};

// 0x7100556204
void arrive_556204(WorkerPool556204* pool) {
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(pool->lock->mutex));
    ++pool->arrived;
    if (pool->arrived == pool->worker_count) {
        for (unsigned int i = 0; i < pool->worker_count; ++i)
            nn::os::SignalEvent(reinterpret_cast<nn::os::EventType*>(pool->workers[i].thread->wake_event));
    }
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(pool->lock->mutex));
}
