// Fifth session, working: 0x7100492bd0 (6,132 bytes), a spatial tree's build from a job queue. First draft: 5,732 B,
// edit distance 775 abstracted, 1,298 exact (tools/s5/lev.py). Name: _ZN10Tree492bd05buildEP14JobQueue492bd0.
// Callees by address: the job's vtable slots come from the GOT (0xc2cb50/58/60), job ctor 0x5c3ad4 and dtor
// 0x5c3ae8, grow 0x491cf0, bounds 0x491028, fill 0x49686c, cell 0x490834; constants 1.15, 0.67, 0.32, 0.25, 3, 0.5.
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
    virtual void* alloc(unsigned long size, AllocInfo492bd0* info);                   // +30
    virtual void v7();
    virtual void* alloc_aligned(unsigned long size, unsigned long align, AllocInfo492bd0* info);   // +40
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void free(void* p);                                                        // +60
};

struct Job492bd0 {
    void* vtable;
    void init_5c3ad4();                                                                // 0x71005c3ad4
    void fini_5c3ae8();                                                                // 0x71005c3ae8
};

struct JobQueue492bd0 {
    virtual void v0();
    virtual void v1();
    virtual void begin(int count);                                                     // +10
    virtual void push(Job492bd0* job);                                                 // +18
    virtual void wait();                                                               // +20
};

extern void* const kBoundsJobVtable_492bd0[] __attribute__((visibility("hidden")));    // GOT 0x7100c2cb50
extern void* const kMaskJobVtable_492bd0[] __attribute__((visibility("hidden")));      // GOT 0x7100c2cb58
extern void* const kCellJobVtable_492bd0[] __attribute__((visibility("hidden")));      // GOT 0x7100c2cb60

struct Box492bd0 {                    // 0x20
    float min[3];
    float max[3];
    unsigned char pad18[8];
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
static inline bool float_less(float a, float b) {
    int ia = *reinterpret_cast<int*>(&a);
    int ib = *reinterpret_cast<int*>(&b);
    int m = (ia & ib) >> 31;
    return (m ^ ia) < (m ^ ib);
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
};

void cell_490834(Cell492bd0* cell, Cell492bd0* parent, Pool492bd0* a, Pool492bd0* b, Range492bd0* r,
                 unsigned long a0, unsigned long a1, unsigned long x);                // 0x7100490834

struct BoundsJob492bd0 : Job492bd0 {  // 0x20
    int start;                        // +8
    int end;                          // +c
    Tree492bd0* tree;                 // +10
    Box492bd0* out;                   // +18
};

struct MaskJob492bd0 : Job492bd0 {    // 0x38
    Tree492bd0* tree;                 // +8
    Axis492bd0* axes;                 // +10
    Range492bd0* splits;              // +18
    unsigned long count;              // +20
    unsigned long axis;               // +28
    bool all;                         // +30
};

struct CellJob492bd0 : Job492bd0 {    // 0x30
    int index;                        // +8
    Tree492bd0* tree;                 // +10
    Range492bd0* ranges;              // +18
    unsigned long a0;                 // +20
    unsigned long a1;                 // +28
};

static inline void mark_axis(Axis492bd0* axes, Range492bd0* splits, unsigned long n, const Box492bd0& b,
                             unsigned long axis, unsigned long k) {
    for (unsigned long j = 0; j < n; j++) {
        if (float_less(splits[j].lo, b.min[axis]) && float_less(b.min[axis + 3], splits[j].hi)) {
            axes[j].bits[k >> 5] |= 1u << (k & 31);
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
    float bmin[3];
    float bmax[3];
    float dmin[3];
    float dmax[3];
    bmin[0] = bmin[1] = bmin[2] = -3.4028235e38f;
    bmax[0] = bmax[1] = bmax[2] = 3.4028235e38f;
    dmin[0] = dmin[1] = dmin[2] = -3.4028235e38f;
    dmax[0] = dmax[1] = dmax[2] = 3.4028235e38f;
    if (jobs != nullptr && parallel != 0) {
        unsigned long parts = nodes_n < 12 ? nodes_n : 12;
        AllocInfo492bd0 info(0x11);
        BoundsJob492bd0* list =
            static_cast<BoundsJob492bd0*>(allocator->alloc_aligned((parts & 0xffffffff) << 5, 0x10, &info));
        if (list == nullptr) {
            return false;
        }
        AllocInfo492bd0 info2(0x11);
        Box492bd0* out = static_cast<Box492bd0*>(allocator->alloc_aligned((parts & 0xffffffff) << 5, 0x10, &info2));
        if (out == nullptr) {
            allocator->free(list);
            return false;
        }
        jobs->begin(static_cast<int>(parts));
        unsigned long per = (nodes_n + 11) / 12;
        unsigned long left = nodes_n;
        int start = 0;
        for (unsigned long i = 0; i < (parts & 0xffffffff); i++) {
            unsigned long take = left <= (per & 0xffffffff) ? left : per;
            list[i].init_5c3ad4();
            list[i].start = start;
            list[i].end = static_cast<int>(take) + start;
            list[i].tree = this;
            list[i].out = &out[i];
            list[i].vtable = const_cast<void**>(kBoundsJobVtable_492bd0) + 2;
            jobs->push(&list[i]);
            left -= take & 0xffffffff;
            start += static_cast<int>(take);
        }
        jobs->wait();
        for (unsigned long i = 0; i < (parts & 0xffffffff); i++) {
            Box492bd0& b = out[i];
            if (float_less(b.max[0], dmax[0])) {
                dmax[0] = b.max[0];
            }
            if (float_less(dmin[0], b.min[0])) {
                dmin[0] = b.min[0];
            }
            if (float_less(b.max[1], dmax[1])) {
                dmax[1] = b.max[1];
            }
            if (float_less(dmin[1], b.min[1])) {
                dmin[1] = b.min[1];
            }
            if (float_less(b.max[2], dmax[2])) {
                dmax[2] = b.max[2];
            }
            if (float_less(dmin[2], b.min[2])) {
                dmin[2] = b.min[2];
            }
        }
        allocator->free(out);
        allocator->free(list);
    } else {
        for (unsigned long i = 0; i < nodes_n; i++) {
            Item492bd0* item = nodes[i];
            if (item != nullptr) {
                unsigned long k = item->index;
                Box492bd0* b = &all[k];
                bounds_491028(b, source->items[k]);
                if (float_less(b->max[0], dmax[0])) {
                    dmax[0] = b->max[0];
                }
                if (float_less(dmin[0], b->min[0])) {
                    dmin[0] = b->min[0];
                }
                if (float_less(b->max[1], dmax[1])) {
                    dmax[1] = b->max[1];
                }
                if (float_less(dmin[1], b->min[1])) {
                    dmin[1] = b->min[1];
                }
                if (float_less(b->max[2], dmax[2])) {
                    dmax[2] = b->max[2];
                }
                if (float_less(dmin[2], b->min[2])) {
                    dmin[2] = b->min[2];
                }
            }
        }
    }
    if (bounds_min[0] < dmin[0] || bounds_min[1] < dmin[1] || bounds_min[2] < dmin[2] ||
        dmax[0] < bounds_max[0] || dmax[1] < bounds_max[1] || dmax[2] < bounds_max[2] ||
        bounds_min[0] <= limit_min[0] || bounds_min[1] <= limit_min[1] || bounds_min[2] <= limit_min[2] ||
        limit_max[0] <= bounds_max[0] || limit_max[1] <= bounds_max[1] || limit_max[2] <= bounds_max[2]) {
        Box492bd0* b = boxes;
        for (unsigned long i = n; i != 0; i--) {
            if (float_less(b->max[0], bmax[0])) {
                bmax[0] = b->max[0];
            }
            if (float_less(bmin[0], b->min[0])) {
                bmin[0] = b->min[0];
            }
            if (float_less(b->max[1], bmax[1])) {
                bmax[1] = b->max[1];
            }
            if (float_less(bmin[1], b->min[1])) {
                bmin[1] = b->min[1];
            }
            if (float_less(b->max[2], bmax[2])) {
                bmax[2] = b->max[2];
            }
            if (float_less(bmin[2], b->min[2])) {
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
        for (unsigned long i = 0; i < nodes_n; i++) {
            Item492bd0* item = nodes[i];
            if (item != nullptr) {
                Box492bd0* b = &boxes[item->index];
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
    float* bminp = bmin;
    split_range0.lo = bminp[a0 * 2 + 3];
    split_range0.hi = bminp[a0 * 2];
    split_range1.lo = bminp[a1 + 3];
    split_range1.hi = bminp[a1];
    bounds_min[0] = bmin[0];
    bounds_min[1] = bmin[1];
    bounds_min[2] = bmin[2];
    bounds_max[0] = bmax[0];
    pad10dc = 0.0f;
    bounds_max[1] = bmax[1];
    pad10ec = 0.0f;
    bounds_max[2] = bmax[2];
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
        if (float_less(m, hi) && float_less(lo = dmin[c0 * 2 + 3], m)) {
            float d = dev[c0 * 2];
            float span = m - lo;
            float w = d * 1.15f;
            float p1, p2, p3;
            if (float_less(w, span)) {
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
            if (float_less(w, up)) {
                q1 = d * 0.32f;
                q2 = d * 0.67f;
                q3 = w;
            } else {
                q1 = up * 0.25f;
                q2 = q1 + q1;
                q3 = q1 * 3.0f;
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
            r8[4].hi = lo + q1 + span;
            r8[5].lo = lo + q1 + span;
            r8[5].hi = lo + span + q2;
            r8[6].lo = lo + span + q2;
            r8[6].hi = lo + span + q3;
            r8[7].lo = lo + span + q3;
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
        if (float_less(m, hi) && float_less(lo = dmin[c1 + 3], m)) {
            float span = m - lo;
            float w = dev[c1] * 0.67f;
            float up = hi - m;
            float p1 = float_less(w, span) ? span - w : span * 0.5f;
            float q1 = float_less(w, up) ? w : up * 0.5f;
            r4[0].lo = lo + 0.0f;
            r4[0].hi = lo + p1;
            r4[1].lo = lo + p1;
            r4[1].hi = lo + span;
            r4[2].lo = lo + span;
            r4[2].hi = lo + q1 + span;
            r4[3].lo = lo + q1 + span;
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
    if (jobs != nullptr) {
        if (parallel != 0) {
            MaskJob492bd0 mj[2];
            mj[0].init_5c3ad4();
            mj[0].vtable = const_cast<void**>(kMaskJobVtable_492bd0) + 2;
            mj[1].init_5c3ad4();
            mj[1].vtable = const_cast<void**>(kMaskJobVtable_492bd0) + 2;
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
            mj[1].fini_5c3ae8();
            mj[0].fini_5c3ae8();
            fill_49686c(cells0, bx, n, r8, ax0, r4, c1, x1180);
            CellJob492bd0 cj[32];
            for (int k = 0; k < 32; k++) {
                cj[k].init_5c3ad4();
                cj[k].vtable = const_cast<void**>(kCellJobVtable_492bd0) + 2;
            }
            unsigned int* s = slots;
            while (__atomic_exchange_n(&lock, 1, __ATOMIC_ACQUIRE) != 0) {
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
            for (int k = 31; k >= 0; k--) {
                cj[k].fini_5c3ae8();
            }
        }
        return true;
    }
    if (parallel != 0) {
        return true;
    }
    if (*flag) {
        if (count != 0) {
            for (unsigned long k = 0; k < count; k++) {
                mark_axis(axes0, splits0, split_count0, boxes[k], axis0, k);
            }
            for (unsigned long k = 0; k < count; k++) {
                mark_axis(axes1, splits1, split_count1, boxes[k], axis1, k);
            }
        }
    } else {
        if (node_count != 0) {
            for (unsigned long i = 0; i < node_count; i++) {
                Item492bd0* item = nodes[i];
                if (item != nullptr) {
                    unsigned long k = item->index;
                    mark_axis(axes0, splits0, split_count0, boxes[k], axis0, k);
                }
            }
            for (unsigned long i = 0; i < node_count; i++) {
                Item492bd0* item = nodes[i];
                if (item != nullptr) {
                    unsigned long k = item->index;
                    mark_axis(axes1, splits1, split_count1, boxes[k], axis1, k);
                }
            }
        }
    }
    fill_49686c(cells0, bx, n, r8, ax0, r4, c1, x1180);
    AllocInfo492bd0 info(0x11);
    Allocator492bd0* al = allocator;
    char* mem = static_cast<char*>(allocator->alloc(n * 0x50, &info));
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
    return true;
}
