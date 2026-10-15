// Fifth session, parked: family (a), 0x71004f09dc 0x71004f17f8 0x71004f2620 0x71004f3448 (1,532 bytes each), one
// template instantiated four times; each copy is 21 instructions off abstracted (1,536 bytes here, 74 instruction
// diffs). Notes: docs/s5_wip/4f09dc.txt. Maps for tools/s5/sbs.py (4f09dc; the siblings use their own shape name
// and callee 0x71004f481c, 0x71004f475c, 0x71004f48dc):
//   --name _ZN11Owner4f09dcI11Shape4f09dcE4findEP12Result4f09dc
//   --map "_Z14contact_4e7928P13Contact4f09dcPK11Entry4f09dcPK5Vec4u=0x71004e7928"
//   --map "_ZN11Shape4f09dc7contactEP13Contact4f09dcPKS_PK5Vec4uPK9Dir4f09dcS1_=0x71004f42c0"
#include "misc/matrix_inverse.h"

extern "C" float sqrtf(float);

union Vec4u {
    float32x4_t v;
    float f[4];
    long l[2];
    int i[4];
    struct {
        float x, y, z, w;
    };
};

struct Vec3f {
    float x, y, z;
};

// The vector five's helper: the 12-byte copy splits into three int loads here (any field order with z before y).
static inline Vec4u to_vec4(const Vec3f& v) {
    Vec4u r;
    *reinterpret_cast<Vec3f*>(&r) = v;
    r.i[3] = 0;
    return r;
}

// The hit direction: its default constructor zeroes w (the 64 stores of the hit array's set-up and the store at
// the top of each iteration); the constructor makes the hit non-POD, so its assignment copies 0x28 bytes.
union Dir4f09dc {
    float32x4_t v;
    float f[4];
    long l[2];
    int i[4];
    struct {
        float x, y, z, w;
    };
    Dir4f09dc() { w = 0.0f; }
};

struct Contact4f09dc {
    unsigned long kind : 8;
    unsigned long sub : 14;
    unsigned long rest : 42;
};

static inline void trim(Contact4f09dc& c) {
    if (c.kind == 2) {
        c.rest = 0;
    }
}

struct ContactPair4f09dc {
    Contact4f09dc a;
    Contact4f09dc b;
    // The duplicate scan compiles to an address comparison in the original (no loads): identity, not value.
    bool operator==(const ContactPair4f09dc& o) const { return this == &o; }
};

struct Entry4f09dc {
    unsigned char pad0[0x30];
    Vec3f n;                          // +30
    unsigned char pad3c[0x4];
    Vec4u a;                          // +40
    Vec4u b;                          // +50
    unsigned char pad60[0x30];
};

void contact_4e7928(Contact4f09dc* out, const Entry4f09dc* e, const Vec4u* p);  // 0x71004e7928

struct Hit4f09dc {
    Dir4f09dc dir;                    // +0
    ContactPair4f09dc ids;            // +10
    Entry4f09dc* entry;               // +20
};

static inline float len2(const Entry4f09dc* e) {
    Vec4u d;
    d.v = e->a.v - e->b.v;
    return d.x * d.x + d.y * d.y + d.z * d.z;
}

struct HitList4f09dc {
    Hit4f09dc items[64];
    unsigned long count;

    // A member function: inlined, its key alloca moves to the top of the caller's entry block, which puts the key
    // (and the direction, merged into its slot) above the hit array as in the original frame.
    void sort() {
        unsigned long n = count;
        for (unsigned long i = 1; i < n; i++) {
            Hit4f09dc key = items[i];
            int j = i;
            while (j > 0) {
                if (!(len2(key.entry) < len2(items[j - 1].entry))) break;
                items[j] = items[j - 1];
                j--;
            }
            items[j] = key;
        }
    }
};

union Matrix4f09dc {
    float m[4][4];
    XMMATRIX x;
};

struct Result4f09dc {
    Vec4u p0;                         // +0
    Vec4u p1;                         // +10
    Vec4u n;                          // +20
    Contact4f09dc a;                  // +30
    Contact4f09dc b;                  // +38
    unsigned char pad40[0xc0];
    int found;                        // +100
};

struct Shape4f09dc {
    unsigned char pad0[0x20];
    static void contact(Contact4f09dc* out, const Shape4f09dc* s, const Vec4u* a, const Dir4f09dc* dir,
                        Contact4f09dc* other);  // 0x71004f42c0
};

template <class S>
struct Owner4f09dc {
    S shape;
    Entry4f09dc entries[64];
    unsigned long count;
    unsigned long pad;
    Matrix4f09dc* mtx;

    bool find(Result4f09dc* out);
};

template <class S>
bool Owner4f09dc<S>::find(Result4f09dc* out) {
    if (count == 0) {
        return false;
    }
    HitList4f09dc hits;
    hits.count = 0;
    for (unsigned long i = 0; i < count; i++) {
        Entry4f09dc& e = entries[i];
        Dir4f09dc dir;
        Vec4u n = to_vec4(e.n);
        // In the caller (a helper's by-value or promoted reference parameters swap the compares' operands) and
        // with a.x read first (the last load gets the pre-indexed base, &e.b in the original).
        float ax = e.a.x;
        if (e.b.x - 0.0011920929f <= ax && ax <= e.b.x + 0.0011920929f &&
            e.b.y - 0.0011920929f <= e.a.y && e.a.y <= e.b.y + 0.0011920929f &&
            e.b.z - 0.0011920929f <= e.a.z && e.a.z <= e.b.z + 0.0011920929f) {
            dir.x = n.x;
            dir.y = n.y;
            dir.z = n.z;
            dir.w = 0.0f;
        } else {
            Vec4u d;
            d.v = e.a.v - e.b.v;
            float inv = 1.0f / sqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
            float w = d.w;
            dir.x = d.x * inv;
            dir.y = inv * d.y;
            dir.z = inv * d.z;
            dir.w = w;
        }
        if (n.x * dir.x + n.y * dir.y + n.z * dir.z > 0.0f) {
            continue;
        }
        ContactPair4f09dc ids;
        contact_4e7928(&ids.b, &e, &e.b);
        S::contact(&ids.a, &shape, &e.a, &dir, &ids.b);
        trim(ids.a);
        trim(ids.b);
        bool dup = false;
        for (unsigned long k = 0; k < hits.count; k++) {
            if (hits.items[k].ids == ids) {
                dup = true;
                break;
            }
        }
        if (dup) {
            continue;
        }
        Hit4f09dc& h = hits.items[hits.count];
        h.dir = dir;
        h.ids = ids;
        h.entry = &e;
        hits.count++;
    }
    hits.sort();
    if (hits.count == 0) {
        out->found = 0;
        return true;
    }
    Hit4f09dc& h = hits.items[hits.count - 1];
    Vec4u p0;
    *reinterpret_cast<Vec3f*>(&p0) = *reinterpret_cast<const Vec3f*>(&h.entry->a);
    p0.w = 1.0f;
    out->p0 = p0;
    Vec4u p1;
    *reinterpret_cast<Vec3f*>(&p1) = *reinterpret_cast<const Vec3f*>(&h.entry->b);
    p1.w = 1.0f;
    out->p1 = p1;
    out->p0.v = XMVector4Transform(out->p0.v, mtx->x);
    out->p1.v = XMVector4Transform(out->p1.v, mtx->x);
    const Matrix4f09dc* m = mtx;
    float rx = m->m[0][0] * h.dir.x + m->m[1][0] * h.dir.y + m->m[2][0] * h.dir.z;
    float ry = h.dir.x * m->m[0][1] + h.dir.y * m->m[1][1] + h.dir.z * m->m[2][1];
    float rz = h.dir.x * m->m[0][2] + h.dir.y * m->m[1][2] + h.dir.z * m->m[2][2];
    out->n.x = rx;
    out->n.y = ry;
    out->n.z = rz;
    out->n.w = h.dir.w;
    float inv = 1.0f / sqrtf(out->n.x * out->n.x + out->n.y * out->n.y + out->n.z * out->n.z);
    float x = out->n.x * inv;
    float y = inv * out->n.y;
    out->n.x = x;
    out->n.y = y;
    out->n.z = inv * out->n.z;
    out->b = h.ids.b;
    out->a = h.ids.a;
    out->found = 1;
    return true;
}

struct Shape4f17f8 {
    unsigned char pad0[0x30];
    static void contact(Contact4f09dc* out, const Shape4f17f8* s, const Vec4u* a, const Dir4f09dc* dir,
                        Contact4f09dc* other);  // 0x71004f481c
};
struct Shape4f2620 {
    unsigned char pad0[0x30];
    static void contact(Contact4f09dc* out, const Shape4f2620* s, const Vec4u* a, const Dir4f09dc* dir,
                        Contact4f09dc* other);  // 0x71004f475c
};
struct Shape4f3448 {
    unsigned char pad0[0x40];
    static void contact(Contact4f09dc* out, const Shape4f3448* s, const Vec4u* a, const Dir4f09dc* dir,
                        Contact4f09dc* other);  // 0x71004f48dc
};

template struct Owner4f09dc<Shape4f09dc>;  // 0x71004f09dc
template struct Owner4f09dc<Shape4f17f8>;  // 0x71004f17f8
template struct Owner4f09dc<Shape4f2620>;  // 0x71004f2620
template struct Owner4f09dc<Shape4f3448>;  // 0x71004f3448
