// PARKED 49cb24 (LockedFlags::flush, 384 B; declare void flush(); and LockedEntry::flush_4a3358 = 0x71004a3358, and
// give LockedFlags unsigned int out_count at +4c and float out[4] at +50), 2 off: the original reloads start inside
// the branch (ldp w11, w9 with count), ours reuses the first load.

// 0x710049cb24
void LockedFlags::flush() {
    SPIN_LOCK(lock);
    unsigned int s = start;
    unsigned int e = extra;
    if (e < s) {
        unsigned int c = count;
        s = start;
        count = 0;
        e = c + e;
        extra = e;
        flags |= 0x10000;
        if (e < s) {
            s = e;
            start = e;
        }
    }
    unsigned int n = e - s;
    out_count = n;
    for (unsigned int i = 0; i < n; i++) out[i] = ring[(s + i) & 3];
    start = e & 3;
    extra = e & 3;
    SPIN_UNLOCK(lock);
    for (unsigned int i = 0; i < entry_count; i++) entries[i].flush_4a3358();
}