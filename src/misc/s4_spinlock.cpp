// Functions that inline the yielding spin lock of include/misc/s4_spinlock.h (fourth session's spin-lock batch).
// Functions are named after their address; names are descriptive placeholders.

#include "misc/s4_spinlock.h"

struct LockedEntry {
    void update_4a32fc();                                                   // 0x71004a32fc
    void flush_4a3358();                                                    // 0x71004a3358
    unsigned char data[0xf0];
};

// A spin lock at +60 guarding a four-slot sum ring (+30) with its counters and a flag word at +68.
class LockedFlags {
public:
    bool ready();
    void clear_ready();
    void commit();
    int push(float value);
    void flush();

    unsigned char pad0[0x30];
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
