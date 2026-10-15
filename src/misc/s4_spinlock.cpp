// Functions that inline the yielding spin lock of include/misc/s4_spinlock.h (fourth session's spin-lock batch).
// Functions are named after their address; names are descriptive placeholders.

#include "misc/s4_spinlock.h"

inline void* operator new(unsigned long, void* p) noexcept { return p; }

struct LockedEntry {
    LockedEntry();                                                          // 0x71004a295c
    void* setup_4a35e8(char* data, struct GameHeap* heap, void* user);     // 0x71004a35e8
    void update_4a32fc();                                                   // 0x71004a32fc
    void flush_4a3358();                                                    // 0x71004a3358
    unsigned char data[0xf0];
};

// A spin lock at +60 guarding a four-slot sum ring (+30) with its counters and a flag word at +68.
struct GameHeap;
struct HeapTag {
    HeapTag(short t) : tag(t), flags(0), extra(0) {}

    short tag;                // +00
    short flags;              // +02
    long extra;               // +08
};
struct GameHeap {
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void* alloc(unsigned long size, const HeapTag& tag);  // +38
};
struct ObjectManager {
    unsigned char pad0[0x10];
    GameHeap* heap;           // +10
};
// Reached through the GOT slot at 0x7100c21de8.
extern ObjectManager* gObjectManager;

struct LockedSourceInfo {
    unsigned char pad0[0x14];
    unsigned int offsets[1];  // +14
};
class LockedSource {
public:
    char* data_49ba44();                                                    // 0x710049ba44
    unsigned int count_49ba4c();                                            // 0x710049ba4c
};

// Its vtable is reached through the GOT slot at 0x7100c2cbb0.
class LockedFlags {
public:
    LockedFlags(GameHeap* h, unsigned int n) : refcount(0), heap(h), lock(0), entry_count(n), flags(0) {
        for (unsigned int i = 1; i < entry_count; i++) new (&entries[i]) LockedEntry();
    }
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void destroy();   // +18

    static LockedFlags* create(LockedSource* source, GameHeap* heap, void* user);
    void finish_49c290(char* data);                                         // 0x710049c290
    bool ready();
    void clear_ready();
    void commit();
    int push(float value);
    void flush();

    int refcount;             // +08
    void* a10 = 0;            // +10
    void* a18 = 0;            // +18
    GameHeap* heap;           // +20
    void* a28 = 0;            // +28
    float ring[4];            // +30
    unsigned int count;       // +40
    unsigned int start;       // +44
    unsigned int extra;       // +48
    unsigned int out_count;   // +4c
    float out[4];             // +50
    int lock;                 // +60
    unsigned int entry_count; // +64
    union {
        unsigned int flags;   // +68: bit 16 ready
        struct {
            unsigned short flags_lo;
            unsigned short flags_hi;  // +6a
        };
    };
    unsigned char pad6c[4];
    LockedEntry entries[1];   // +70
};

// 0x710049c9dc
bool LockedFlags::ready() {
    SPIN_LOCK(lock);
    bool r = flags_hi & 1;
    SPIN_UNLOCK(lock);
    return r;
}

// 0x710049ca74
void LockedFlags::clear_ready() {
    SPIN_LOCK(lock);
    flags &= ~0x10000u;
    SPIN_UNLOCK(lock);
}
// 0x710049c7a4
void LockedFlags::commit() {
    SPIN_LOCK(lock);
    extra += count;
    count = 0;
    flags |= 0x10000;
    SPIN_UNLOCK(lock);
    for (unsigned int i = 0; i < entry_count; i++) entries[i].update_4a32fc();
}

// 0x710049c880
int LockedFlags::push(float value) {
    SPIN_LOCK(lock);
    unsigned int index = extra + count;
    unsigned int slot = index & 3;
    if (index < start + 4) {
        ring[slot] = value;
        count++;
    } else {
        unsigned int first = start & 3;
        unsigned int second = (start + 1) & 3;
        if (second == (extra & 3)) {
            unsigned int next = (extra + 1) & 3;
            ring[next] = ring[second] + ring[next];
            ring[second] = ring[first];
            ring[slot] = value;
            start++;
            extra++;
        } else {
            ring[second] = ring[first] + ring[second];
            ring[slot] = value;
            start++;
            count++;
        }
    }
    SPIN_UNLOCK(lock);
    return count;
}
