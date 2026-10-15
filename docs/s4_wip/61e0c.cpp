// WIP: Mgr::update (0x7100061e0c, 0x7100061fc4, 0x710006217c; 440 bytes, three identical copies).
// State (fourth session): 4 off with registers abstracted. For each active element it counts the non-null entries of
// a list (up to 0x76), tests whether any entry's id is below 0x6d7 and sets bit 0 of the element info's flags.
// Settled: unsigned element count (cbz guard), a 64-bit unsigned scan index (b.lo), the "any low" flag a byte with ||
// in a helper returning bool (the loop then unrolls by 2 with the original's `and #0xff` test).
// Still off: the original materializes ok = !low as a phi (1 on the empty-list path, eor on the loop exit) and selects
// the cleared flags on it; ours selects on low (InstCombine folds the negation into the select), and the empty-list
// block is placed early. Writing ok = !low directly pushes the negation into the loop's phi (39 off).
struct Info {
    int mode;                 // +0
    unsigned int flags;       // +4: bit 0 set when an entry is below the threshold
};
struct Entry {
    unsigned char pad0[4];
    unsigned short id;        // +4
};

class Elem {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual unsigned char active();     // +18
    virtual void slot_4();
    virtual void slot_5();
    virtual void slot_6();
    virtual void slot_7();
    virtual void slot_8();
    virtual void slot_9();
    virtual void slot_10();
    virtual void slot_11();
    virtual void slot_12();
    virtual void slot_13();
    virtual void slot_14();
    virtual void slot_15();
    virtual void slot_16();
    virtual void slot_17();
    virtual void slot_18();
    virtual void slot_19();
    virtual void slot_20();
    virtual void slot_21();
    virtual void slot_22();
    virtual void slot_23();
    virtual void slot_24();
    virtual void slot_25();
    virtual Entry** entries();          // +d0
    virtual Info* info();               // +d8

    unsigned char pad8[0x3d8];
};

static inline bool any_low(Entry** list, unsigned int n) {
    unsigned char low = 0;
    for (unsigned int k = 0; k < n; k++)
        low = low || list[k]->id < 0x6d7;
    return low;
}
class Mgr;
void callee_6b428(Info*, int);
void callee_63f7c(Mgr*, Elem*);
void callee_6cd1c(void*, Elem*);

class Mgr {
public:
    void update(Elem* elems, unsigned int count);

    unsigned char pad0[0x3100];
    unsigned char sub[1];     // +3100
};

void Mgr::update(Elem* elems, unsigned int count) {
    for (unsigned int i = 0; i < count; i++) {
        Elem* e = &elems[i];
        if (!e->active()) continue;
        Info* info = e->info();
        Entry** list = e->entries();
        int mode = (info->flags & 2) ? 6 : 0;
        unsigned long j;
        for (j = 0; j < 0x76; j++)
            if (!list[j]) break;
        int n = j;
        bool ok = !any_low(list, n);
        callee_6b428(info, 0);
        unsigned int fl = info->flags;
        if (ok) fl &= ~1u;
        else fl |= 1;
        info->mode = mode;
        info->flags = fl;
        callee_63f7c(this, e);
        callee_6cd1c(sub, e);
    }
}
