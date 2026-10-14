// Locked per-core requests (0x71002ab480-0x71002ab6c8): under the owner's optional mutex, forward a
// request to the inner service with the current core's entry from the primary table, else from the
// secondary table, else the caller's fallback. When the owner is active the entry is looked up once
// beforehand as well, with the result unused. Found by tools/family_scan.py --immediates. Names
// are descriptive placeholders. Status: matching/README.md.

namespace nn {
namespace os {
struct MutexType {
    unsigned char storage[0x20];
};
void LockMutex(MutexType* mutex);
void UnlockMutex(MutexType* mutex);
}  // namespace os
}  // namespace nn

unsigned int core_index_3cc9c0();                                           // 0x71003cc9c0

struct CoreEntry {
    unsigned short count;     // +00
    unsigned char pad2[0xe];
};

struct CoreService {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void* request_a(void* a, void* b, const CoreEntry* entry);
    virtual void* request_b(void* a, void* b, const CoreEntry* entry);
    virtual void* request_c(void* a, void* b, const CoreEntry* entry);
};

struct CoreLock {
    unsigned char pad[0x10];
    nn::os::MutexType mutex;  // +10
};

struct CoreOwner {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void* active();
};

struct CoreClient : CoreOwner, CoreService {
    unsigned char pad10[0x58];
    CoreLock* lock;           // +68
    CoreEntry* primary;       // +70
    CoreEntry* secondary;     // +78

    const CoreEntry* entry(const CoreEntry* fallback) {
        unsigned short count = primary[core_index_3cc9c0()].count;
        unsigned int index = core_index_3cc9c0();
        if (count)
            return &primary[index];
        if (secondary[index].count)
            return &secondary[core_index_3cc9c0()];
        return fallback;
    }
};
// 0x71002ab480
void* locked_request_2ab480(CoreClient* client, void* a, void* b, const CoreEntry* fallback) {
    if (client->lock)
        nn::os::LockMutex(&client->lock->mutex);
    if (client->active())
        client->entry(fallback);
    void* result = static_cast<CoreService*>(client)->request_a(a, b, client->entry(fallback));
    if (client->lock)
        nn::os::UnlockMutex(&client->lock->mutex);
    return result;
}
// 0x71002ab5a4
void* locked_request_2ab5a4(CoreClient* client, void* a, void* b, const CoreEntry* fallback) {
    if (client->lock)
        nn::os::LockMutex(&client->lock->mutex);
    if (client->active())
        client->entry(fallback);
    void* result = static_cast<CoreService*>(client)->request_b(a, b, client->entry(fallback));
    if (client->lock)
        nn::os::UnlockMutex(&client->lock->mutex);
    return result;
}
// 0x71002ab6c8
void* locked_request_2ab6c8(CoreClient* client, void* a, void* b, const CoreEntry* fallback) {
    if (client->lock)
        nn::os::LockMutex(&client->lock->mutex);
    if (client->active())
        client->entry(fallback);
    void* result = static_cast<CoreService*>(client)->request_c(a, b, client->entry(fallback));
    if (client->lock)
        nn::os::UnlockMutex(&client->lock->mutex);
    return result;
}
