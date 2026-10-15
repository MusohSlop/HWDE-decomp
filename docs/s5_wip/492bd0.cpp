// Fifth session, parked: 0x7100492bd0 (6,132 bytes), a spatial tree's build from a job queue: resets the cells,
// grows the box array, sizes the axis lists, computes the items' bounds (in up to 12 bounds jobs when there is a
// queue and the tree is parallel, else in one of two identical serial loops), rebuilds the tree bounds when the
// items left them or reached the limits, the centres' mean and deviation, the two split axes and their ranges, the
// 8 and 4 split ranges around the mean, then marks the axis bits (2 mask jobs, the fill at 0x49686c and 32 cell
// jobs; or serially, then the fill and the 32 cells at 0x490834 with two pools from one allocation).
// This draft is 6,144 B; edit distance 227 abstracted, 632 exact (tools/s5/lev.py; the first draft was 775/1,298).
// Maps: --map "_ZN9Job492bd0C2Ev=0x71005c3ad4" --map "_ZN9Job492bd0D2Ev=0x71005c3ae8"
//   --map "got:_ZTV15BoundsJob492bd0=0x7100c2cb50" --map "got:_ZTV13MaskJob492bd0=0x7100c2cb58"
//   --map "got:_ZTV13CellJob492bd0=0x7100c2cb60" --name _ZN10Tree492bd05buildEP14JobQueue492bd0
// Settled (each measured): the jobs are real classes (base constructor 0x5c3ad4 and destructor 0x5c3ae8 out of
// line, vtables external through the GOT): the 32 cell jobs' construction and destruction then unroll as in the
// original (402 -> 277); the allocation info is a temporary passed by const reference (all three share one slot)
// and the mask jobs live in their own block (510 -> 402); the bounds job gets the count and adds the start in its
// constructor (after the base constructor call); the float compares take references and read the floats as ints
// (int loads, fmov to float after); the max accumulations compare the box value first ((m ^ box) > (m ^ acc)); the
// accumulators are two Box locals (0x20 each); the serial bounds loop is written out twice (jobs && parallel, else
// parallel, else) so SimplifyCFG hoists only the shared stores; the job phase is if (jobs && parallel) ... else if
// (!parallel) marks ...; the lock is while (!__sync_bool_compare_and_swap(&lock, 0, 1)) {}; the mark loops are
// helpers taking the split count, axis and item count by value (read once per loop, as in the original); the box
// column is addressed through a pointer (v[0], v[3]); the split ranges read bmax[axis] and bmin[axis] off separate
// bases; the upper split ranges are lo + (q1 + span), lo + q2, lo + q3 with q2 and q3 including the span; the
// reduce loop copies each job's box; the mean loop reads the box array once before the loop.
// Still off: block placement and jump threading of the bounds jobs' tail (the original keeps one wait call; the
// push loop's zero-count guard is a 32-bit cbz there, and an unsigned int index fixes that here but costs 80 in
// register allocation); the accumulators' initial stores are merged into 64-bit stores in places; register
// allocation and scheduling in the mark loops, the split-range block and the mean loop.
extern "C" float sqrtf(float x);                                            // 0x71006008a0

struct AllocInfo492bd0 {
    unsigned short kind;
    unsigned short flags;
    unsigned int pad;
    void* owner;
    AllocInfo492bd0(unsigned short k) : kind(k), flags(0), owner(nullptr) {}
};

struct Allocator492bd0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void* alloc(unsigned long size, const AllocInfo492bd0& info);                   // +30
    virtual void v7();
    virtual void* alloc_aligned(unsigned long size, unsigned long align, const AllocInfo492bd0& info);   // +40
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void free(void* p);                                                        // +60
};

inline void* operator new(unsigned long, void* p) {
    return p;
}

// A job of the engine's queue: its constructor and destructor are out of line, its vtable is external (GOT).
struct Job492bd0 {
    Job492bd0();                                                                        // 0x71005c3ad4
    virtual ~Job492bd0();                                                               // 0x71005c3ae8
    virtual void run();
};

struct JobQueue492bd0 {
    virtual void v0();
    virtual void v1();
    virtual void begin(int count);                                                     // +10
    virtual void push(Job492bd0* job);                                                 // +18
    virtual void wait();                                                               // +20
};


struct Box492bd0 {                    // 0x20
    float min[3];
    float max[3];
    unsigned char pad18[8];
};

struct OutBox492bd0 {                 // 0x20, a bounds job's result
    float min[4];
    float max[4];
};

struct Item492bd0 {
    unsigned char pad0[0x68];
    unsigned long index;              // +68
};

struct Source492bd0 {
    unsigned long count;              // +0
    unsigned char pad8[8];
    void** items;                     // +10
};

struct Axis492bd0 {                   // 0x18
    unsigned long count;              // +0
    unsigned long x8;                 // +8
    unsigned int* bits;               // +10
};

struct Cell492bd0 {                   // 0x18
    unsigned long head;
    unsigned char pad8[0x10];
};

struct Range492bd0 {
    float lo;
    float hi;
};

struct Pool492bd0 {
    unsigned long x0;
    unsigned long count;
    void* data;
};

void bounds_491028(Box492bd0* out, void* item);                                        // 0x7100491028

// Integer compare of two floats' bits (both negative: the order flips), the engine's fast float less-than.
static inline bool float_less(const float& a, const float& b) {
    int ia = *reinterpret_cast<const int*>(&a);
    int ib = *reinterpret_cast<const int*>(&b);
    int m = (ia & ib) >> 31;
    return (m ^ ia) < (m ^ ib);
}
static inline bool float_greater(const float& a, const float& b) {
    int ia = *reinterpret_cast<const int*>(&a);
    int ib = *reinterpret_cast<const int*>(&b);
    int m = (ia & ib) >> 31;
    return (m ^ ia) > (m ^ ib);
}

struct Tree492bd0 {
    Allocator492bd0* allocator;       // +0
    unsigned char pad8[8];
    Source492bd0* source;             // +10
    unsigned long count;              // +18
    unsigned long capacity;           // +20
    Box492bd0* boxes;                 // +28
    Axis492bd0 axes0[64];             // +30
    Axis492bd0 axes1[64];             // +630
    unsigned long xc30;               // +c30
    unsigned char padc38[0x10];
    unsigned long xc48;               // +c48
    unsigned char padc50[0x10];
    Cell492bd0 cells0[8];             // +c60
    Cell492bd0 cells1[32];            // +d20
    unsigned char pad1020[0x30];
    unsigned int* slots;              // +1050
    unsigned long node_count;         // +1058
    unsigned char pad1060[8];
    Item492bd0** nodes;               // +1068
    unsigned char pad1070[0x18];
    volatile unsigned long lock;      // +1088
    unsigned int* x1090;              // +1090
    unsigned long x1098;              // +1098
    int x10a0;                        // +10a0
    unsigned int slot_stride;         // +10a4
    unsigned char pad10a8[0x28];
    float bounds_min[3];              // +10d0
    float pad10dc;
    float bounds_max[3];              // +10e0
    float pad10ec;
    Range492bd0 split_range0;         // +10f0
    Range492bd0 split_range1;         // +10f8
    float box_min[3];                 // +1100
    float pad110c;
    float box_max[3];                 // +1110
    float pad111c;
    float limit_min[3];               // +1120
    float pad112c;
    float limit_max[3];               // +1130
    float pad113c;
    float step0;                      // +1140
    float step1;                      // +1144
    unsigned long axis0;              // +1148
    unsigned long axis1;              // +1150
    unsigned long parallel;           // +1158
    unsigned long axis_copy;          // +1160
    unsigned long extra;              // +1168
    unsigned long split_count0;       // +1170
    unsigned long split_count1;       // +1178
    unsigned long x1180;              // +1180
    unsigned char rebuilt;            // +1188

    unsigned char grow_491cf0(unsigned long capacity);                                // 0x7100491cf0
    void fill_49686c(Cell492bd0* cells, Box492bd0* boxes, unsigned long count, Range492bd0* r8, unsigned long a0,
                     Range492bd0* r4, unsigned long a1, unsigned long x);             // 0x710049686c
    bool build(JobQueue492bd0* jobs);
    inline void mark_boxes(Axis492bd0* axes, Range492bd0* splits, unsigned long nsplit, unsigned long axis,
                           unsigned long cnt);
    inline void mark_nodes(Axis492bd0* axes, Range492bd0* splits, unsigned long nsplit, unsigned long axis,
                           unsigned long cnt);

    __attribute__((always_inline)) void serial_bounds(float* A, Box492bd0* all, unsigned long nodes_n) {
        float* dmin = A;
        float* dmax = A + 3;
        for (unsigned long i = 0; i < nodes_n; i++) {
            Item492bd0* item = nodes[i];
            if (item != nullptr) {
                unsigned long k = item->index;
                Box492bd0* b = &all[k];
                bounds_491028(b, source->items[k]);
                if (float_less(b->max[0], dmax[0])) {
                    dmax[0] = b->max[0];
                }
                if (float_greater(b->min[0], dmin[0])) {
                    dmin[0] = b->min[0];
                }
                if (float_less(b->max[1], dmax[1])) {
                    dmax[1] = b->max[1];
                }
                if (float_greater(b->min[1], dmin[1])) {
                    dmin[1] = b->min[1];
                }
                if (float_less(b->max[2], dmax[2])) {
                    dmax[2] = b->max[2];
                }
                if (float_greater(b->min[2], dmin[2])) {
                    dmin[2] = b->min[2];
                }
            }
        }
    }
};

void cell_490834(Cell492bd0* cell, Cell492bd0* parent, Pool492bd0* a, Pool492bd0* b, Range492bd0* r,
                 unsigned long a0, unsigned long a1, unsigned long x);                // 0x7100490834

struct BoundsJob492bd0 : Job492bd0 {  // 0x20, vtable GOT 0x7100c2cb50
    int start;                        // +8
    int end;                          // +c
    Tree492bd0* tree;                 // +10
    OutBox492bd0* out;                // +18
    BoundsJob492bd0(int s, int n, Tree492bd0* t, OutBox492bd0* o) : start(s), end(n + s), tree(t), out(o) {}
    void run();
};

struct MaskJob492bd0 : Job492bd0 {    // 0x38
    Tree492bd0* tree;                 // +8
    Axis492bd0* axes;                 // +10
    Range492bd0* splits;              // +18
    unsigned long count;              // +20
    unsigned long axis;               // +28
    bool all;                         // +30
    MaskJob492bd0() {}                // vtable GOT 0x7100c2cb58
    void run();
};

struct CellJob492bd0 : Job492bd0 {    // 0x30
    int index;                        // +8
    Tree492bd0* tree;                 // +10
    Range492bd0* ranges;              // +18
    unsigned long a0;                 // +20
    unsigned long a1;                 // +28
    CellJob492bd0() {}                // vtable GOT 0x7100c2cb60
    void run();
};

static inline void mark_axis(Axis492bd0* axes, Range492bd0* splits, unsigned long n, const Box492bd0& b,
                             unsigned long axis, unsigned long k) {
    for (unsigned long j = 0; j < n; j++) {
        const float* v = &b.min[axis];
        if (float_greater(v[0], splits[j].lo) && float_less(v[3], splits[j].hi)) {
            axes[j].bits[k >> 5] |= 1u << (k & 31);
        }
    }
}

static inline void init6(float* p) {
    p[3] = p[4] = p[5] = 3.4028235e38f;
    p[0] = p[1] = p[2] = -3.4028235e38f;
}

__attribute__((always_inline)) inline void Tree492bd0::mark_boxes(Axis492bd0* axes, Range492bd0* splits,
                                                                 unsigned long nsplit, unsigned long axis,
                                                                 unsigned long cnt) {
    for (unsigned long k = 0; k < cnt; k++) {
        mark_axis(axes, splits, nsplit, boxes[k], axis, k);
    }
}

__attribute__((always_inline)) inline void Tree492bd0::mark_nodes(Axis492bd0* axes, Range492bd0* splits,
                                                                 unsigned long nsplit, unsigned long axis,
                                                                 unsigned long cnt) {
    for (unsigned long i = 0; i < cnt; i++) {
        Item492bd0* item = nodes[i];
        if (item != nullptr) {
            unsigned long k = item->index;
            mark_axis(axes, splits, nsplit, boxes[k], axis, k);
        }
    }
}

// 0x7100492bd0
bool Tree492bd0::build(JobQueue492bd0* jobs) {
    for (int k = 0; k < 32; k++) {
        cells1[k].head = 0;
    }
    unsigned long n = source->count;
    if (capacity < n && !grow_491cf0(extra + n)) {
        return false;
    }
    count = n;
    for (unsigned long i = 0; i < split_count0; i++) {
        axes0[i].count = n;
    }
    for (unsigned long i = 0; i < split_count1; i++) {
        axes1[i].count = n;
    }
    xc30 = n;
    xc48 = n;
    if (n == 0) {
        return true;
    }
    Box492bd0* all = boxes;
    unsigned char* flag = &rebuilt;
    *flag = 0;
    unsigned long nodes_n = node_count;
    Box492bd0 B;
    Box492bd0 A;
    float* bmin = B.min;
    float* bmax = B.min + 3;
    float* dmin = A.min;
    float* dmax = A.min + 3;
    if (jobs != nullptr && parallel != 0) {
        init6(A.min);
        init6(B.min);
        unsigned long parts = nodes_n < 12 ? nodes_n : 12;
        BoundsJob492bd0* list = static_cast<BoundsJob492bd0*>(
            allocator->alloc_aligned((parts & 0xffffffff) << 5, 0x10, AllocInfo492bd0(0x11)));
        if (list == nullptr) {
            return false;
        }
        OutBox492bd0* out = static_cast<OutBox492bd0*>(
            allocator->alloc_aligned((parts & 0xffffffff) << 5, 0x10, AllocInfo492bd0(0x11)));
        if (out == nullptr) {
            allocator->free(list);
            return false;
        }
        jobs->begin(static_cast<int>(parts));
        unsigned long per = (nodes_n + 11) / 12;
        unsigned long left = nodes_n;
        int start = 0;
        for (unsigned long i = 0; i < (parts & 0xffffffff); i++) {
            unsigned long take = left > (per & 0xffffffff) ? per : left;
            BoundsJob492bd0* job = new (&list[i]) BoundsJob492bd0(start, static_cast<int>(take), this, &out[i]);
            jobs->push(job);
            left -= take & 0xffffffff;
            start += static_cast<int>(take);
        }
        jobs->wait();
        for (unsigned long i = 0; i < (parts & 0xffffffff); i++) {
            OutBox492bd0 b = out[i];
            if (float_less(b.max[0], dmax[0])) {
                dmax[0] = b.max[0];
            }
            if (float_greater(b.min[0], dmin[0])) {
                dmin[0] = b.min[0];
            }
            if (float_less(b.max[1], dmax[1])) {
                dmax[1] = b.max[1];
            }
            if (float_greater(b.min[1], dmin[1])) {
                dmin[1] = b.min[1];
            }
            if (float_less(b.max[2], dmax[2])) {
                dmax[2] = b.max[2];
            }
            if (float_greater(b.min[2], dmin[2])) {
                dmin[2] = b.min[2];
            }
        }
        allocator->free(out);
        allocator->free(list);
    } else if (parallel != 0) {
        init6(B.min);
        init6(A.min);
        for (unsigned long i = 0; i < nodes_n; i++) {
            Item492bd0* item = nodes[i];
            if (item != nullptr) {
                unsigned long k = item->index;
                Box492bd0* b = &all[k];
                bounds_491028(b, source->items[k]);
                if (float_less(b->max[0], dmax[0])) {
                    dmax[0] = b->max[0];
                }
                if (float_greater(b->min[0], dmin[0])) {
                    dmin[0] = b->min[0];
                }
                if (float_less(b->max[1], dmax[1])) {
                    dmax[1] = b->max[1];
                }
                if (float_greater(b->min[1], dmin[1])) {
                    dmin[1] = b->min[1];
                }
                if (float_less(b->max[2], dmax[2])) {
                    dmax[2] = b->max[2];
                }
                if (float_greater(b->min[2], dmin[2])) {
                    dmin[2] = b->min[2];
                }
            }
        }
    } else {
        init6(B.min);
        init6(A.min);
        for (unsigned long i = 0; i < nodes_n; i++) {
            Item492bd0* item = nodes[i];
            if (item != nullptr) {
                unsigned long k = item->index;
                Box492bd0* b = &all[k];
                bounds_491028(b, source->items[k]);
                if (float_less(b->max[0], dmax[0])) {
                    dmax[0] = b->max[0];
                }
                if (float_greater(b->min[0], dmin[0])) {
                    dmin[0] = b->min[0];
                }
                if (float_less(b->max[1], dmax[1])) {
                    dmax[1] = b->max[1];
                }
                if (float_greater(b->min[1], dmin[1])) {
                    dmin[1] = b->min[1];
                }
                if (float_less(b->max[2], dmax[2])) {
                    dmax[2] = b->max[2];
                }
                if (float_greater(b->min[2], dmin[2])) {
                    dmin[2] = b->min[2];
                }
            }
        }
    }
    if (bounds_min[0] < dmin[0] || bounds_min[1] < dmin[1] || bounds_min[2] < dmin[2] ||
        bounds_max[0] > dmax[0] || bounds_max[1] > dmax[1] || bounds_max[2] > dmax[2] ||
        bounds_min[0] <= limit_min[0] || bounds_min[1] <= limit_min[1] || bounds_min[2] <= limit_min[2] ||
        bounds_max[0] >= limit_max[0] || bounds_max[1] >= limit_max[1] || bounds_max[2] >= limit_max[2]) {
        Box492bd0* b = boxes;
        for (unsigned long i = n; i != 0; i--) {
            if (float_less(b->max[0], bmax[0])) {
                bmax[0] = b->max[0];
            }
            if (float_greater(b->min[0], bmin[0])) {
                bmin[0] = b->min[0];
            }
            if (float_less(b->max[1], bmax[1])) {
                bmax[1] = b->max[1];
            }
            if (float_greater(b->min[1], bmin[1])) {
                bmin[1] = b->min[1];
            }
            if (float_less(b->max[2], bmax[2])) {
                bmax[2] = b->max[2];
            }
            if (float_greater(b->min[2], bmin[2])) {
                bmin[2] = b->min[2];
            }
            b++;
        }
        *flag = 1;
    } else {
        bmin[0] = bounds_min[0];
        bmin[1] = bounds_min[1];
        bmin[2] = bounds_min[2];
        bmax[0] = bounds_max[0];
        bmax[1] = bounds_max[1];
        bmax[2] = bounds_max[2];
    }
    float mean[3] = {0.0f, 0.0f, 0.0f};
    float dev[3] = {0.0f, 0.0f, 0.0f};
    if (nodes_n != 0) {
        float sx = 0.0f, sy = 0.0f, sz = 0.0f, qx = 0.0f, qy = 0.0f, qz = 0.0f;
        unsigned long used = 0;
        Box492bd0* bb = boxes;
        for (unsigned long i = 0; i < nodes_n; i++) {
            Item492bd0* item = nodes[i];
            if (item != nullptr) {
                Box492bd0* b = &bb[item->index];
                float cx = (b->min[0] + b->max[0]) * 0.5f;
                sx += cx;
                mean[0] = sx;
                qx += cx * cx;
                float cy = (b->min[1] + b->max[1]) * 0.5f;
                sy += cy;
                mean[1] = sy;
                qy += cy * cy;
                float cz = (b->min[2] + b->max[2]) * 0.5f;
                sz += cz;
                qz += cz * cz;
                used++;
                mean[2] = sz;
            }
        }
        if (used != 0) {
            float f = static_cast<float>(used);
            mean[0] = sx / f;
            float v = qx / f - mean[0] * mean[0];
            dev[0] = v > 0.0f ? sqrtf(v) : 0.0f;
            mean[1] = sy / f;
            v = qy / f - mean[1] * mean[1];
            dev[1] = v > 0.0f ? sqrtf(v) : 0.0f;
            mean[2] = sz / f;
            v = qz / f - mean[2] * mean[2];
            dev[2] = v > 0.0f ? sqrtf(v) : 0.0f;
        }
    }
    unsigned long a0 = float_less(bmin[0] - bmax[0], bmin[2] - bmax[2]) ? 1 : 0;
    unsigned long a1 = float_less(bmin[0] - bmax[0], bmin[2] - bmax[2]) ? 0 : 2;
    axis0 = a0 << 1;
    axis1 = a1;
    split_range0.lo = bmax[a0 * 2];
    split_range0.hi = bmin[a0 * 2];
    split_range1.lo = bmax[a1];
    split_range1.hi = bmin[a1];
    bounds_min[0] = bmin[0];
    bounds_min[1] = bmin[1];
    bounds_min[2] = bmin[2];
    bounds_max[0] = bmax[0];
    bounds_max[1] = bmax[1];
    bounds_max[2] = bmax[2];
    pad10dc = 0.0f;
    pad10ec = 0.0f;
    axis_copy = a0 << 1;
    float s0 = (split_range0.hi - split_range0.lo) / static_cast<float>(split_count0);
    float s1 = (split_range1.hi - split_range1.lo) / static_cast<float>(split_count1);
    step0 = s0;
    step1 = s1;
    Range492bd0 splits0[64];
    Range492bd0 splits1[64];
    for (unsigned long i = 0; i < split_count0; i++) {
        float lo = s0 * static_cast<float>(i) + split_range0.lo;
        splits0[i].lo = lo;
        splits0[i].hi = s0 + lo;
    }
    for (unsigned long i = 0; i < split_count1; i++) {
        float lo = s1 * static_cast<float>(i) + split_range1.lo;
        splits1[i].lo = lo;
        splits1[i].hi = s1 + lo;
    }
    unsigned long c0 = float_less(dmin[0] - dmax[0], dmin[2] - dmax[2]) ? 1 : 0;
    unsigned long c1 = float_less(dmin[0] - dmax[0], dmin[2] - dmax[2]) ? 0 : 2;
    box_min[0] = dmin[0];
    box_min[1] = dmin[1];
    box_min[2] = dmin[2];
    pad110c = 0.0f;
    box_max[0] = dmax[0];
    box_max[1] = dmax[1];
    box_max[2] = dmax[2];
    pad111c = 0.0f;
    unsigned long ax0 = c0 << 1;
    Range492bd0 r8[8];
    Range492bd0 r4[4];
    {
        float hi = dmin[c0 * 2];
        float m = mean[c0 * 2];
        float lo;
        if (float_greater(hi, m) && float_less(lo = dmin[c0 * 2 + 3], m)) {
            float d = dev[c0 * 2];
            float span = m - lo;
            float w = d * 1.15f;
            float p1, p2, p3;
            if (float_greater(span, w)) {
                p1 = span - w;
                p2 = span + d * -0.67f;
                p3 = span + d * -0.32f;
            } else {
                p1 = span * 0.25f;
                p2 = p1 + p1;
                p3 = p1 * 3.0f;
            }
            float up = hi - m;
            float q1, q2, q3;
            if (float_greater(up, w)) {
                q1 = d * 0.32f;
                q2 = span + d * 0.67f;
                q3 = span + w;
            } else {
                q1 = up * 0.25f;
                q2 = (q1 + q1) + span;
                q3 = q1 * 3.0f + span;
            }
            r8[0].lo = lo + 0.0f;
            r8[0].hi = lo + p1;
            r8[1].lo = lo + p1;
            r8[1].hi = lo + p2;
            r8[2].lo = lo + p2;
            r8[2].hi = lo + p3;
            r8[3].lo = lo + p3;
            r8[3].hi = lo + span;
            r8[4].lo = lo + span;
            r8[4].hi = lo + (q1 + span);
            r8[5].lo = lo + (q1 + span);
            r8[5].hi = lo + q2;
            r8[6].lo = lo + q2;
            r8[6].hi = lo + q3;
            r8[7].lo = lo + q3;
            r8[7].hi = lo + (hi - lo);
        } else {
            for (int i = 0; i < 8; i++) {
                r8[i].lo = 3.4028235e38f;
                r8[i].hi = -3.4028235e38f;
            }
        }
    }
    {
        float hi = dmin[c1];
        float m = mean[c1];
        float lo;
        if (float_greater(hi, m) && float_less(lo = dmin[c1 + 3], m)) {
            float span = m - lo;
            float w = dev[c1] * 0.67f;
            float up = hi - m;
            float p1 = float_greater(span, w) ? span - w : span * 0.5f;
            float q1 = float_greater(up, w) ? w : up * 0.5f;
            r4[0].lo = lo + 0.0f;
            r4[0].hi = lo + p1;
            r4[1].lo = lo + p1;
            r4[1].hi = lo + span;
            r4[2].lo = lo + span;
            r4[2].hi = lo + (q1 + span);
            r4[3].lo = lo + (q1 + span);
            r4[3].hi = lo + (hi - lo);
        } else {
            for (int i = 0; i < 4; i++) {
                r4[i].lo = 3.4028235e38f;
                r4[i].hi = -3.4028235e38f;
            }
        }
    }
    Box492bd0* bx = boxes;
    for (int k = 0; k < 8; k++) {
        cells0[k].head = 0;
    }
    if (jobs != nullptr && parallel != 0) {
        {
            {
            MaskJob492bd0 mj[2];
            jobs->begin(2);
            bool all_items = *flag == 0;
            mj[0].tree = this;
            mj[0].axes = axes0;
            mj[0].splits = splits0;
            mj[0].count = split_count0;
            mj[0].axis = axis0;
            mj[0].all = all_items;
            mj[1].tree = this;
            mj[1].axes = axes1;
            mj[1].splits = splits1;
            mj[1].count = split_count1;
            mj[1].axis = axis1;
            mj[1].all = all_items;
            jobs->push(&mj[0]);
            jobs->push(&mj[1]);
            jobs->wait();
            }
            fill_49686c(cells0, bx, n, r8, ax0, r4, c1, x1180);
            CellJob492bd0 cj[32];
            unsigned int* s = slots;
            while (!__sync_bool_compare_and_swap(&lock, 0, 1)) {
            }
            unsigned int stride = slot_stride;
            x1090 = s;
            x1098 = 3;
            x10a0 = 3;
            s[0] = 1;
            s = reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(s) + stride);
            s[0] = 2;
            *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(s) + stride) = 3;
            lock = 0;
            jobs->begin(32);
            for (int k = 0; k < 32; k++) {
                cj[k].index = k;
                cj[k].tree = this;
                cj[k].ranges = r4;
                cj[k].a0 = ax0;
                cj[k].a1 = c1;
                jobs->push(&cj[k]);
            }
            jobs->wait();
        }
    } else if (parallel == 0) {
    if (*flag) {
        mark_boxes(axes0, splits0, split_count0, axis0, count);
        mark_boxes(axes1, splits1, split_count1, axis1, count);
    } else {
        mark_nodes(axes0, splits0, split_count0, axis0, node_count);
        mark_nodes(axes1, splits1, split_count1, axis1, node_count);
    }
    fill_49686c(cells0, bx, n, r8, ax0, r4, c1, x1180);
    char* mem = static_cast<char*>(allocator->alloc(n * 0x50, AllocInfo492bd0(0x11)));
    Allocator492bd0* al = allocator;
    Pool492bd0 pa = {0, 0, nullptr};
    Pool492bd0 pb = {0, 0, nullptr};
    if (mem != nullptr) {
        pa.count = n;
        pa.data = mem;
        char* second = mem + n * 0x28;
        if (second != nullptr) {
            pb.data = second;
            pb.count = n;
        } else {
            pb.data = nullptr;
            pb.x0 = 0;
            pb.count = 0;
        }
    }
    for (int k = 0; k < 32; k++) {
        pa.x0 = 0;
        pb.x0 = 0;
        cell_490834(&cells1[k], &cells0[k / 4], &pa, &pb, &r4[k % 4], ax0, c1, x1180);
    }
    if (pb.data != nullptr) {
        pb.count = 0;
        pb.data = nullptr;
        pb.x0 = 0;
    }
    if (pa.data != nullptr) {
        pa.count = 0;
        pa.data = nullptr;
        pa.x0 = 0;
    }
    if (mem != nullptr && al != nullptr) {
        al->free(mem);
    }
    }
    return true;
}
