// Collects draw records from item pairs into a frame arena (fourth session, relaxed group 3db158): for each pair whose
// first part is of kind 1 and has a source set, a 0x38-byte record and a copy of the source's 16-byte entries are
// taken from the arena (16-byte aligned) and the record is pushed on a list. collect<0> (0x71003db158), collect<1>
// (0x71003db330) and collect<2> (0x71003db508), identical. Names are descriptive placeholders.

typedef unsigned long size_t;
extern "C" void* memcpy(void* dst, const void* src, size_t n);              // 0x7100600870 (import)
inline void* operator new(unsigned long, void* p) noexcept { return p; }

// Bump allocator {base, used, cap}. The aligned form computes the padding on the integer address (`used + base`
// after canonicalization), while take's pointer is `base + used`: the two are not CSE'd, as in the original.
struct FrameArena {
    char* base;               // +00
    size_t used;              // +08
    size_t cap;               // +10

    void* take(size_t n) {
        if (used + n > cap) return 0;
        size_t off = used;
        used += n;
        return base + off;
    }
    void* take_aligned(size_t n, size_t align = 16) {
        size_t cur = reinterpret_cast<size_t>(base) + used;
        size_t pad = ((cur + align - 1) & ~(align - 1)) - cur;
        if (pad && !take(pad)) return 0;
        return take(n);
    }
    void* clone(const void* src, size_t n) {
        void* p = take_aligned(n);
        memcpy(p, src, n);
        return p;
    }
};

// The two count records are distinct types: the phi of their `count` addresses then can't fold into one GEP, which
// leaves the `add #4` after the merge.
struct DrawCountsA {
    int pad0;
    unsigned int count;       // +04
};
struct DrawCountsB {
    int pad0;
    unsigned int count;       // +04
};
struct DrawSourceA {
    unsigned char pad0[0x190];
    DrawCountsA* counts;      // +190
    unsigned char pad198[0x30];
    void* entries;            // +1c8
};
struct DrawSourceB {
    unsigned char pad0[0x198];
    void* entries;            // +198
    DrawCountsB* counts;      // +1a0
};
struct DrawSourceSet {
    unsigned char pad0[0x30];
    DrawSourceA** low;        // +30, sources 0..9999
    DrawSourceB** high;       // +38, sources from 10000
};
struct DrawOwnerSlot {
    unsigned char pad0[0x78];
    DrawSourceSet* set;       // +78
};
struct DrawOwner {
    unsigned char pad0[0x20];
    DrawOwnerSlot* slot;      // +20
    unsigned char pad28[0x58];
    DrawSourceSet* set;       // +80
};
struct DrawPartA {
    unsigned char pad0[6];
    unsigned short kind;      // +06
    unsigned char pad8[2];
    short source;             // +0a, high bit: take the set from the owner's slot
};
struct DrawPartB {
    unsigned char pad0[0x40];
    DrawOwner* owner;         // +40
};
struct DrawPair {
    DrawPartA* a;
    DrawPartB* b;
};
// Built with placement new and a constructor: with plain stores after the allocation, SimplifyCFG drops the
// allocator's failure paths (a store through the null result is undefined).
struct DrawRecord {
    DrawRecord() : entries(0), count(0), owner(0), part(0), next(0) {}
    void* entries;            // +00
    unsigned int count;       // +08
    DrawOwner* owner;         // +10
    DrawPartA* part;          // +18
    DrawRecord* next;         // +20
    unsigned char pad28[0x10];
};

template <int Copy>
void collect(DrawPair* pairs, unsigned int count, FrameArena* arena, DrawRecord** head) {
    for (unsigned int i = 0; i < count; i++) {
        DrawPair& pair = pairs[i];
        DrawPartA* a = pair.a;
        if (a->kind != 1) continue;
        DrawOwner* owner = pair.b->owner;
        DrawSourceSet* set = a->source < 0 && owner->slot ? owner->slot->set : owner->set;
        if (!set) continue;
        DrawRecord* r = new (arena->take_aligned(sizeof(DrawRecord))) DrawRecord;
        unsigned int index = pair.a->source & 0x7fff;
        unsigned int n;
        void* src;
        if (index >= 10000) {
            DrawSourceB* s = set->high[index - 10000];
            n = s->counts->count;
            src = s->entries;
        } else {
            DrawSourceA* s = set->low[index];
            n = s->counts->count;
            src = s->entries;
        }
        void* copy = arena->clone(src, static_cast<size_t>(n) * 16);
        r->owner = owner;
        r->part = pair.a;
        r->entries = copy;
        r->count = n;
        r->next = *head;
        *head = r;
    }
}

// 0x71003db158
template void collect<0>(DrawPair*, unsigned int, FrameArena*, DrawRecord**);
// 0x71003db330
template void collect<1>(DrawPair*, unsigned int, FrameArena*, DrawRecord**);
// 0x71003db508
template void collect<2>(DrawPair*, unsigned int, FrameArena*, DrawRecord**);
