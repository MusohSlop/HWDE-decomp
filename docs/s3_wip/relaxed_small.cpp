// WIP (third session): small relaxed groups parked (pieces of build/s3/t_small2.cpp; the expression-op and limit
// types are as in misc/s3_functions35.cpp).
// 4c2bec/4c3874, 4c2b44/4c382c (64 and 72 B): the original calls the next op and returns (a frame) where ours
// tail-calls it; a 16-byte struct result did not change that.
// 5fdb84/5fee04 (72 B): 2 words; the original pairs the stores at +4c/+50 (kind, used) and leaves +48 alone. Best
// of the 120 body orders of the five later fields: count, used, kind, table, flags.

// The pointer field at the next operand's offset, passed on to the next op.
template <int Table>
Result4c2b expr_pointer_field(int** cursor, unsigned char* base) {
    unsigned int offset = *(*cursor)++;
    int op = *(*cursor)++;
    return expr_ops<Table>()[op](cursor, *reinterpret_cast<void**>(base + offset));
}

// The self-relative field at the next operand's offset (its address plus the offset it holds).
template <int Table>
Result4c2b expr_relative_field(int** cursor, unsigned char* base) {
    unsigned int offset = *(*cursor)++;
    int op = *(*cursor)++;
    unsigned char* field = base + offset;
    return expr_ops<Table>()[op](cursor, field + *reinterpret_cast<int*>(field));
}

template Result4c2b expr_pointer_field<0>(int**, unsigned char*);    // 0x71004c2bec
template Result4c2b expr_pointer_field<1>(int**, unsigned char*);    // 0x71004c3874
template Result4c2b expr_relative_field<0>(int**, unsigned char*);   // 0x71004c2b44
template Result4c2b expr_relative_field<1>(int**, unsigned char*);   // 0x71004c382c
// ---- 5fdb84/5fee04: a limit object initialised after its base (the largest float, its kind 4, a global table).
struct Base5fa9 {
    Base5fa9();                  // 0x71005fa954
    unsigned char pad0[0x3c];
};
struct Table5fdb;
// Reached through the GOT slots at 0x7100c2de78 and 0x7100c2de90.
extern Table5fdb gLimitTableA;
extern Table5fdb gLimitTableB;

template <int Copy>
struct Limit5fdb : Base5fa9 {
    Limit5fdb();

    float max;                   // +3c
    long total;                  // +40
    int count;                   // +48
    int kind;                    // +4c
    int used;                    // +50
    int pad54;
    Table5fdb* table;            // +58
    short flags;                 // +60
};

template <int Copy>
Limit5fdb<Copy>::Limit5fdb()
    : max(3.40282347e+38f), total(0), count(0), kind(4), used(0), table(Copy == 0 ? &gLimitTableA : &gLimitTableB),
      flags(0) {}

template Limit5fdb<0>::Limit5fdb();   // 0x71005fdb84
template Limit5fdb<1>::Limit5fdb();   // 0x71005fee04


// 550d94/550de0 (76 B): 9 words; ours loads the motion pointer once before the branch (hoisted), the original
// in each branch after storing the target.
// ---- 550d94/550de0: one of two targets set (immediately, or as an offset from the current value).
struct Vec3_550d {
    float x, y, z;
};
struct Motion550d {
    unsigned char pad0[0x40];
    Vec3_550d vectors[2];        // +40
    unsigned char pad58[0x80];
    unsigned int current;        // +d8
    unsigned char paddc[0x6c];
    bool dirty[2];               // +148
};
struct Target550d {
    float target;
    float offset;
};

template <int I>
struct Driver550d {
    void set(float value, unsigned char now);

    unsigned char pad0[0x1a4];
    Target550d targets[2];       // +1a4
    unsigned char pad1b4[0x1f4];
    Motion550d* motion;          // +3a8
};

template <int I>
void Driver550d<I>::set(float value, unsigned char now) {
    if (targets[I].target == value)
        return;
    targets[I].target = value;
    if (now) {
        Motion550d* m = motion;
        m->vectors[I].x = value;
        m->dirty[m->current ^ 1] = true;
    } else {
        targets[I].offset = value - motion->vectors[I].x;
    }
}

template void Driver550d<1>::set(float, unsigned char);   // 0x7100550d94
template void Driver550d<0>::set(float, unsigned char);   // 0x7100550de0


// 5064ec/506fb0 (88 B): the row is built as two 64-bit stores as in the original (a 16-byte union returned by
// value), 17 words off in the order of the products; irsearch queued.
// ---- 5064ec/506fb0: the second row of a rotation matrix from a quaternion.
union Row5064 {
    struct {
        float x, y, z, w;
    };
    unsigned int bits[4];
};
struct Quat5064 {
    float x, y, z, w;
};
struct Matrix5064 {
    Row5064 rows[3];
};

inline Row5064 row_y(const Quat5064& q) {
    float x2 = q.x + q.x;
    float y2 = q.y + q.y;
    float z2 = q.z + q.z;
    Row5064 r;
    r.x = x2 * q.y - z2 * q.w;
    r.y = 1.0f - q.z * z2 - q.x * x2;
    r.z = y2 * q.z + x2 * q.w;
    r.w = 0.0f;
    return r;
}

template <int Copy>
void set_row_y(Matrix5064* m, const Quat5064* q) {
    m->rows[1] = row_y(*q);
}

template void set_row_y<0>(Matrix5064*, const Quat5064*);   // 0x71005064ec
template void set_row_y<1>(Matrix5064*, const Quat5064*);   // 0x7100506fb0


// 59f5e8/59f670 (136 B): 6 words, the or of the counters' flags is scheduled after the total load in the
// original; irsearch queued.
// ---- 59f5e8/59f670: a channel's value and data set, its target and counters updated.
struct Base59f5 {
    int pad0;
    int base[2];                 // +04
};
struct TargetBlock59f5 {
    unsigned char pad0[0x2];
    unsigned short active;       // +02 (+a82)
    unsigned char pad4[0x4c];
    int value;                   // +50 (+ad0)
    unsigned char pad54[0x2c];
};
struct Target59f5 {
    unsigned long flags;         // +00
    unsigned char pad8[0xa78];
    TargetBlock59f5 blocks[2];   // +a80
};
struct CounterBlock59f5 {
    unsigned char pad0[0x6];
    unsigned short pending;      // +06 (+106)
    unsigned short total;        // +08 (+108)
    unsigned char pada[0x46];
    void* active;                // +50 (+150)
    unsigned char pad58[0x28];
};
struct Counters59f5 {
    unsigned long flags;         // +00
    unsigned char pad8[0xf8];
    CounterBlock59f5 blocks[2];  // +100
};

template <int K>
struct Channel59f5 {
    void set(int value, void* data);

    unsigned char pad0[0x58];
    Base59f5* base;              // +58
    unsigned char pad60[0x28];
    Target59f5* target;          // +88
    Counters59f5* counters;      // +90
    unsigned char pad98[0x38];
    int mode;                    // +d0
    unsigned char padd4[0x20];
    int values[2];               // +f4
    unsigned char padfc[0xc];
    void* data[2];               // +108
};

template <int K>
void Channel59f5<K>::set(int value, void* data_) {
    Base59f5* b = base;
    values[K] = value;
    data[K] = data_;
    int n = b->base[K] + value + (mode == K + 2 ? -1 : 0);
    Target59f5* t = target;
    if (t->blocks[K].value != n || t->blocks[K].active != 1) {
        t->flags |= 0x100000ul << K;
        t->blocks[K].value = n;
        t->blocks[K].active = 1;
    }
    Counters59f5* c = counters;
    if (c->blocks[K].active) {
        c->flags |= 2ul << K;
        unsigned short pending = c->blocks[K].pending;
        c->blocks[K].pending = 0;
        c->blocks[K].total += pending;
    }
}

template void Channel59f5<0>::set(int, void*);   // 0x710059f5e8
template void Channel59f5<1>::set(int, void*);   // 0x710059f670

// 4d3524/4d35c4 (160 B): 6 abstract, NEON lane multiply-adds (arm_neon.h) in the original's register use but a
// different schedule. 524a08/524ac0 (184 B): 7 abstract at best (two explicit loops), the header loads and the item
// pointer placement. 509728/509ba4 (188 B): 7 abstract, the original keeps the hit's address in x22 across the
// call.
#include <arm_neon.h>
// ---- 4d3524/4d35c4: a node's matrix multiplied by another, passed on with a scaled weight.
struct Matrix4d35 {
    float32x4_t rows[4];
};
struct Node4d35 {
    unsigned char pad0[0x10];
    Matrix4d35 matrix;           // +10
};
struct Owner4d35;
void apply_4d51d4(Owner4d35* owner, Node4d35* node, int kind, Matrix4d35* matrix, float weight);   // 0x71004d51d4

inline float32x4_t transform(float32x4_t v, const Matrix4d35& m) {
    float32x4_t r = vmulq_laneq_f32(m.rows[0], v, 0);
    r = vfmaq_laneq_f32(r, m.rows[1], v, 1);
    r = vfmaq_laneq_f32(r, m.rows[2], v, 2);
    r = vfmaq_laneq_f32(r, m.rows[3], v, 3);
    return r;
}

template <int Kind>
void apply_product(Owner4d35* owner, Node4d35* node, const Matrix4d35* other) {
    const Matrix4d35& a = node->matrix;
    float32x4_t r0 = transform(a.rows[0], *other);
    float32x4_t r1 = transform(a.rows[1], *other);
    float32x4_t r2 = transform(a.rows[2], *other);
    float32x4_t r3 = transform(a.rows[3], *other);
    Matrix4d35 product = {{r0, r1, r2, r3}};
    apply_4d51d4(owner, node, Kind, &product, ldexpf(reinterpret_cast<const float*>(other)[7], 0x70));
}

template void apply_product<4>(Owner4d35*, Node4d35*, const Matrix4d35*);   // 0x71004d3524
template void apply_product<1>(Owner4d35*, Node4d35*, const Matrix4d35*);   // 0x71004d35c4

// ---- 524a08/524ac0: the ids of the items of one kind (optionally listed); one more than the largest, or 0.
struct Header524a {
    int pad0;
    unsigned int base;           // +04
    unsigned char pad8[0x2c];
    unsigned int count;          // +34
    unsigned int offset;         // +38
};
struct Item524a {
    unsigned char pad0[0x48];
    int ids[6];                  // +48
    int kind;                    // +60
    unsigned char pad64[0x40];
};

template <int Kind>
struct Table524a {
    int collect(int* out, unsigned int listing);

    unsigned char pad0[0x20];
    unsigned char* data;         // +20
    unsigned char pad28[0x8];
    int column;                  // +30
    unsigned char pad34[0xcc];
    Header524a* header;          // +100
};

template <int Kind>
int Table524a<Kind>::collect(int* out, unsigned int listing) {
    Header524a* h = header;
    unsigned int base = h->base;
    unsigned int count = h->count;
    unsigned int offset = h->offset;
    int largest = -1;
    unsigned int n = 0;
    for (unsigned int i = 0; i < count; ++i) {
        Item524a* item = reinterpret_cast<Item524a*>(data + (static_cast<unsigned long>(offset) + base)) + i;
        if (item->kind == Kind) {
            int id = item->ids[column];
            if (id >= 0) {
                if (out && listing)
                    out[n++] = id;
                if (id >= largest)
                    largest = id;
            }
        }
    }
    return largest < 0 ? 0 : largest + 1;
}

template int Table524a<1>::collect(int*, unsigned int);   // 0x7100524a08
template int Table524a<2>::collect(int*, unsigned int);   // 0x7100524ac0

// ---- 509728/509ba4: a ray's hit point (w 1) and the hit's normal.
struct alignas(16) Vec4_5097 {
    float x, y, z, w;
};
struct Ray5097 {
    Vec4_5097 origin;            // +00
    Vec4_5097 direction;         // +10
};
struct Hit5097 {
    float t;                     // +00
    unsigned char pad4[0xc];
    Vec4_5097 normal;            // +10
};
unsigned char raycast_5094ec(Hit5097* hit, void* scene, const Ray5097* ray);   // 0x71005094ec
unsigned char raycast_5097e4(Hit5097* hit, void* scene, const Ray5097* ray);   // 0x71005097e4

template <int Copy>
bool hit_point(Vec4_5097* point, Vec4_5097* normal, void* scene, const Ray5097* ray) {
    Hit5097 hit;
    Hit5097* h = &hit;
    h->normal.w = 0.0f;
    if (!(Copy == 0 ? raycast_5094ec(h, scene, ray) : raycast_5097e4(h, scene, ray)))
        return false;
    float t = h->t;
    point->x = ray->origin.x + t * ray->direction.x;
    point->y = ray->origin.y + t * ray->direction.y;
    point->z = ray->origin.z + t * ray->direction.z;
    point->w = 1.0f;
    *normal = h->normal;
    return true;
}

template bool hit_point<0>(Vec4_5097*, Vec4_5097*, void*, const Ray5097*);   // 0x7100509728
template bool hit_point<1>(Vec4_5097*, Vec4_5097*, void*, const Ray5097*);   // 0x7100509ba4
