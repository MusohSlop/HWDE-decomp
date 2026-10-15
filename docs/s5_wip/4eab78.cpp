// Fifth session, parked: 0x71004eab78 (1,524 bytes), the first of the vector six (4eab78 4ebc2c 4eccf0 4eddb4
// 4eee68 4e9984: one template over the shape at +20, 0x20/0x30/0x30/0x40/0x70/0x50 bytes, with its support and
// closest callees; 4eee68's closest takes an extra null argument). It sums the entries' edge vectors and their
// normals weighted by edge length, normalises both unless near zero (|c| < 0.0011920929 per component), picks the
// normal sum or both (dot < 0.3), projects every entry on that direction (min of a, max of b, the best entry's b
// becomes pos), then sets result from the shape's support and closest points (dot < 0.3) or by the projection,
// and writes the frame-based direction to out, normalised. This draft is 7 instructions off abstracted, 34 exact
// by edit distance (tools/s5/lev.py; 1,520 B), the same for all six copies (4eee68: 5 abstracted).
// Settled (each measured): the engine vector is a union (by value it travels as two 64-bit integers); the sums
// zeroed as two longs and kept in memory (the alternate pick takes their address); the sums, the near tests and
// the pick of v in their own block scope; the alternate copied as a vector (v.v = alt.v); operator+ takes its left
// side by reference and its right side by value; the output's frame transform computed into locals and stored after.
// Second pass: the sums' near-zero flags come from an int helper with early returns (nz3: the last compare is the
// returned value, zext'd in its own block, so SimplifyCFG cannot speculate it into an and; the flag is an int, so
// it is tested with cbnz); the out test is x, then z with +E first, then y; the frame transform is written with the
// negated components added (InstCombine folds the y and z negations into fsubs and keeps the frame element
// first); sum_a's update is (e.b - e.a) + sum_a.
// Third pass (13/75 -> 7/34): support and closest take their vector by const reference and get temporaries, so
// each slot's lifetime ends with its call and both reuse sum_b's slot (q at sp+0x50; this also puts the dir build's
// bfi in place); the projection loop computes both dot products before the min update (the min fcsel then sits
// between the b products as in the original, and v lands in v5).
// Still off: the pick's fadd takes sum_a first (ldp q0, q1 against the original's ldp q1, q0): the then block must
// not start with sum_b's load (after SROA it is the same load i128 as the else block's copy, SimplifyCFG hoists it
// and the pick becomes a select, a bsl), but when sum_a is loaded first Reassociate puts the earlier load on the
// left; the zero of best is materialised once above the count test (the original has it in the preheader and on
// the empty path); d = p - pos and t's products have v0 and v1 swapped and the x product first; the out branch's
// post-indexed store of the difference comes before the lane moves; the out normalisation's y square in s2
// instead of s3. Tried without effect: the index and best as long, count copied to a local, count > i, the out
// difference through a local, the dot product through a helper.
// Maps: --map "_ZNK12Sphere4eab787supportERK5Vec4uPv=0x7100506264" --map "_ZNK12Sphere4eab787closestERK5Vec4u=0x7100506284"
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
static inline Vec4u operator+(const Vec4u& a, Vec4u b) {
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

    Vec4u support(const Vec4u& dir, void* extra) const;        // 0x7100506264
    Vec4u closest(const Vec4u& point) const;                   // 0x7100506284
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
static inline int nz3(const Vec4u& v) {
    if (!(v.x > -0.0011920929f && v.x < 0.0011920929f)) return 0;
    if (!(v.y > -0.0011920929f && v.y < 0.0011920929f)) return 0;
    if (!(v.z > -0.0011920929f)) return 0;
    return v.z < 0.0011920929f;
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
    Vec4u v;
    float dot;
    {
    Vec4u sum_b;
    sum_b.l[0] = 0;
    sum_b.l[1] = 0;
    Vec4u sum_a;
    sum_a.l[0] = 0;
    sum_a.l[1] = 0;
    for (unsigned long i = 0; i < count; i++) {
        FitEntry& e = entries[i];
        sum_b = sum_b + to_vec4(e.n) * length3(e.b - e.a);
        sum_a = (e.b - e.a) + sum_a;
    }
    int zero_b = nz3(sum_b);
    int zero_a = nz3(sum_a);
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
    dot = sum_b.x * sum_a.x + sum_b.y * sum_a.y + sum_b.z * sum_a.z;
    if (!(dot < 0.3f)) {
        v = sum_b + sum_a;
    } else {
        v = sum_b;
    }
    if (near_zero3(v)) {
        const Vec4u& alt = zero_b ? sum_a : sum_b;
        v.v = alt.v;
        if (near_zero3(v)) {
            return false;
        }
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
        float db = v.x * e.b.x + v.y * e.b.y + v.z * e.b.z;
        if (da < lo) {
            lo = da;
        }
        if (db > hi) {
            hi = db;
            best = i;
        }
    }
    pos = entries[best].b;
    if (dot < 0.3f) {
        Vec4u p = shape.support(vec4(-v.x, -v.y, -v.z, 0.0f), nullptr);
        Vec4u d = p - pos;
        float t = v.x * d.x + v.y * d.y + v.z * d.z;
        result = shape.closest(pos + v * t);
    } else {
        result = v * (lo - hi) + pos;
    }
    if (out != nullptr) {
        if (near_zero(v.x) && v.z < 0.0011920929f && v.z > -0.0011920929f && near_zero(v.y)) {
            *out = to_vec4(frame->t) - pos;
        } else {
            Frame4eab78* f = frame;
            float ox = f->x.x * -v.x + f->y.x * -v.y + f->z.x * -v.z;
            float oy = f->x.y * -v.x + f->y.y * -v.y + f->z.y * -v.z;
            float oz = f->x.z * -v.x + f->y.z * -v.y + f->z.z * -v.z;
            out->x = ox;
            out->y = oy;
            out->z = oz;
            out->w = 0.0f;
        }
        float inv2 = 1.0f / length3(*out);
        out->x = out->x * inv2;
        out->y = inv2 * out->y;
        out->z = inv2 * out->z;
    }
    return true;
}
