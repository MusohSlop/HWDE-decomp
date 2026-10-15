// Fifth session, in progress: 0x71004eab78 (1,524 bytes), the first of the vector five (4eab78 4ebc2c 4eccf0 4eddb4
// 4eee68: one template, the shape member at +20 is 0x20/0x30/0x30/0x40/0x70 bytes and the two shape calls differ; the
// 64 entries of 0x60 bytes follow it, then the count and the frame pointer). It sums the entries' edge vectors and
// their normals weighted by edge length, normalises both unless near zero (|c| < 0.0011920929 per component),
// picks the normal sum or both (dot < 0.3), projects every entry on that direction (min of a, max of b, the best
// entry's b becomes pos), then sets result from the shape's support and closest points (dot < 0.3) or by the
// projection, and writes the frame-based direction to out, normalised.
// Settled (each measured): the engine vector is a union (not an HFA, so by value it travels as two 64-bit integers:
// the original's integer round trips come from by-value helpers: to_vec4 of a Vec3 (12-byte copy, int zero w),
// operator+/-/*, vec4(x, y, z, w) for the negated direction, giving the eor); the sums zeroed field by field as
// two longs (GVN cannot forward two 8-byte stores to the vector reload, which the original keeps); the edge length
// evaluated after the normal (sum_b + to_vec4(e.n) * length3(e.b - e.a)), so the normal's 8+4-byte loads come before
// the sqrt call as in the original (loop body identical). This draft is 97 instructions off abstracted at 1,588 bytes;
// with v merged by a conditional expression and the sums zeroed by zero4() it is the same size (1,524) at 108 off. Still off: the near-zero tests (the original keeps every compare a branch except the last, ours
// folds pairs into and), v's representation after the merge (the original keeps it in one vector register), and
// the frame (0xd0 with d8-d13 and x19-x24 in the original).
// On the near-zero tests: a helper's && is folded into an and inside the helper itself, before inlining (the
// -print-after-all dumps show the ands right after the inliner), because reference parameters are dereferenceable
// and their loads are safe to speculate. Through a pointer parameter (const Vec4u*) the x pair stays two branches
// as in the original, but the y and z pairs still fold after inlining; the original keeps all but the last compare
// as branches and zeroes the result register twice (before the chain and after the x pair). Per-component helpers
// by value, pointer or reference and nested ifs all compile alike (104 off).
// Maps: --map "_ZNK12Sphere4eab787supportEPK5Vec4uPv=0x7100506264" --map "_ZNK12Sphere4eab787closestEPK5Vec4u=0x7100506284"
//   --map sqrtf=0x71006008a0 --name _ZN9Fit4eab786updateEP5Vec4u
#include <arm_neon.h>

extern "C" float sqrtf(float);

// The engine's 16-byte vector: a union, so it is not an HFA; passed and returned by value it travels as two
// 64-bit integers (x0/x1), which is where the original's integer round trips come from.
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

static inline Vec4u vec4(float32x4_t v) {
    Vec4u r;
    r.v = v;
    return r;
}
static inline Vec4u operator+(Vec4u a, Vec4u b) {
    return vec4(a.v + b.v);
}
static inline Vec4u operator-(Vec4u a, Vec4u b) {
    return vec4(a.v - b.v);
}
static inline Vec4u operator*(Vec4u a, float s) {
    return vec4(vmulq_n_f32(a.v, s));
}
static inline Vec4u to_vec4(const Vec3f& v) {
    Vec4u r;
    *reinterpret_cast<Vec3f*>(&r) = v;
    r.i[3] = 0;
    return r;
}
static inline Vec4u vec4(float x, float y, float z, float w) {
    Vec4u r;
    r.x = x;
    r.y = y;
    r.z = z;
    r.w = w;
    return r;
}
static inline Vec4u zero4() {
    Vec4u r;
    r.l[0] = 0;
    r.l[1] = 0;
    return r;
}

struct FitEntry {
    unsigned char pad0[0x30];
    Vec3f n;                          // +30
    unsigned char pad3c[0x4];
    Vec4u a;                          // +40
    Vec4u b;                          // +50
};

struct Frame4eab78 {
    Vec4u x;                          // +0
    Vec4u y;                          // +10
    Vec4u z;                          // +20
    Vec3f t;                          // +30
};

struct Sphere4eab78 {
    Vec4u center;                     // +0
    float radius;                     // +10
    unsigned char pad14[0xc];

    Vec4u support(const Vec4u* dir, void* extra) const;        // 0x7100506264
    Vec4u closest(const Vec4u* point) const;                   // 0x7100506284
};

static inline bool near_zero(float f) {
    return f > -0.0011920929f && f < 0.0011920929f;
}

static inline bool near_zero3v(Vec4u v) {
    return near_zero(v.x) && near_zero(v.y) && near_zero(v.z);
}
static inline float length3v(Vec4u v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}
static inline Vec4u normalized3(Vec4u v) {
    float inv = 1.0f / length3v(v);
    v.x = v.x * inv;
    v.y = inv * v.y;
    v.z = inv * v.z;
    return v;
}
static inline bool near_zero3(const Vec4u& v) {
    return near_zero(v.x) && near_zero(v.y) && near_zero(v.z);
}

static inline float length3(const Vec4u& v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

struct Fit4eab78 {
    Vec4u result;                     // +0
    Vec4u pos;                        // +10
    Sphere4eab78 shape;               // +20
    FitEntry entries[64];             // +40
    unsigned long count;              // +1840
    unsigned long pad1848;
    Frame4eab78* frame;               // +1850

    bool update(Vec4u* out);
};

// 0x71004eab78
bool Fit4eab78::update(Vec4u* out) {
    if (count == 0) {
        return false;
    }
    Vec4u sum_b;
    sum_b.l[0] = 0;
    sum_b.l[1] = 0;
    Vec4u sum_a;
    sum_a.l[0] = 0;
    sum_a.l[1] = 0;
    for (unsigned long i = 0; i < count; i++) {
        FitEntry& e = entries[i];
        sum_b = sum_b + to_vec4(e.n) * length3(e.b - e.a);
        sum_a = sum_a + (e.b - e.a);
    }
    bool zero_b = near_zero3(sum_b);
    bool zero_a = near_zero3(sum_a);
    if (!zero_b) {
        float inv = 1.0f / length3(sum_b);
        sum_b.x = sum_b.x * inv;
        sum_b.y = inv * sum_b.y;
        sum_b.z = inv * sum_b.z;
    }
    if (!zero_a) {
        float inv = 1.0f / length3(sum_a);
        sum_a.x = sum_a.x * inv;
        sum_a.y = inv * sum_a.y;
        sum_a.z = inv * sum_a.z;
    }
    float dot = sum_b.x * sum_a.x + sum_b.y * sum_a.y + sum_b.z * sum_a.z;
    Vec4u v;
    if (dot < 0.3f) {
        v = sum_b;
    } else {
        v = sum_b + sum_a;
    }
    if (near_zero3v(v)) {
        const Vec4u& alt = zero_b ? sum_a : sum_b;
        v = alt;
        if (near_zero3v(v)) {
            return false;
        }
    }
    float inv = 1.0f / length3v(v);
    v.x = v.x * inv;
    v.y = inv * v.y;
    v.z = inv * v.z;
    float hi = -3.4028235e38f;
    float lo = 3.4028235e38f;
    unsigned long best = 0;
    for (unsigned long i = 0; i < count; i++) {
        FitEntry& e = entries[i];
        float da = v.x * e.a.x + v.y * e.a.y + v.z * e.a.z;
        if (da < lo) {
            lo = da;
        }
        float db = v.x * e.b.x + v.y * e.b.y + v.z * e.b.z;
        if (db > hi) {
            hi = db;
            best = i;
        }
    }
    pos = entries[best].b;
    if (dot < 0.3f) {
        Vec4u dir = vec4(-v.x, -v.y, -v.z, 0.0f);
        Vec4u p = shape.support(&dir, nullptr);
        Vec4u d = p - pos;
        float t = v.x * d.x + v.y * d.y + v.z * d.z;
        Vec4u q = pos + v * t;
        result = shape.closest(&q);
    } else {
        result = v * (lo - hi) + pos;
    }
    if (out != nullptr) {
        if (near_zero(v.x) && near_zero(v.z) && near_zero(v.y)) {
            *out = to_vec4(frame->t) - pos;
        } else {
            Frame4eab78* f = frame;
            out->x = -v.x * f->x.x - v.y * f->y.x - v.z * f->z.x;
            out->y = -v.x * f->x.y - v.y * f->y.y - v.z * f->z.y;
            out->z = -v.x * f->x.z - v.y * f->y.z - v.z * f->z.z;
            out->w = 0.0f;
        }
        float inv2 = 1.0f / length3(*out);
        out->x = out->x * inv2;
        out->y = inv2 * out->y;
        out->z = inv2 * out->z;
    }
    return true;
}
