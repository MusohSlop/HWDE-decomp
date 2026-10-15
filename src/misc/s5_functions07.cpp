// Ray and polygon tests of the collision module (fifth session): 0x7100409078's classification of a ray against
// a segment (codes 0-13, kept a near miss), and 0x7100402aec, which intersects a segment with a polygon's plane and
// casts a ray from the hit point across the polygon, counting crossings with 0x7100409078.
// The classifier must be in the same unit: FunctionAttrs marks its pointer parameters nocapture readonly but not the
// function itself (it may call sqrtf, which sets errno), so EarlyCSE keeps the reloads of the hit point and the ray
// after each call while GVN removes them later, after LoopUnswitch has seen a loop too large to unswitch on the
// collinear case's n > 2 guard (InstCombine then folds that guard to n != 2 against the outer loop's n > 1).
// A declaration with __attribute__((pure)) drops the reloads before LoopUnswitch, and the loop is unswitched.
// Struct, field and callee names are placeholders after the address and offset, as in the generated units. Status:
// matching/README.md.
#include <arm_neon.h>

extern "C" float sqrtf(float);

// The engine's 16-byte vector, as in the vector six (docs/s5_wip/4eab78.cpp).
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
static inline Vec4u operator-(Vec4u a, Vec4u b) {
    return vec4(a.v - b.v);
}
static inline bool operator==(const Vec4u& a, const Vec4u& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}
// A function of its own: optimised before it is inlined, its negation folds into the phi of the comparison chain
// (true on the early exits, une on the last lane), the flag the classifier keeps in w8.
static inline bool operator!=(const Vec4u& a, const Vec4u& b) {
    return !(a == b);
}

static inline bool near_zero(float f) {
    return f >= -1.1920929e-05f && f <= 1.1920929e-05f;
}
static inline bool in_range(float f, float lo, float hi) {
    return f >= lo && f <= hi;
}

signed char intersect_402aec(const Vec3f* p, const Vec4u* verts, int n, const Vec4u* plane, const Vec3f* lo,
                             const Vec3f* hi, float radius);
int classify_409078(const Vec4u* p, const Vec4u* dir, const Vec4u* a, const Vec4u* b);

// 0x7100402aec: the segment from p along the plane's normal against the plane (within radius / 2), then the
// polygon test of the hit point: 1 inside or on the boundary, 0 outside, -1 when the classifier fails.
// The locals' order is the source of the match: hit's lifetime starts between the normal's two reads (so the
// denominator reads it again, and Reassociate keeps d first in each product), and the normal's components are read
// in pairs so the allocator gives d.y and d.z the lower registers. The collinear case's e is written through .v,
// so its lanes are extracted where they are used (z, y first), which decides the dot product's registers.
signed char intersect_402aec(const Vec3f* p, const Vec4u* verts, int n, const Vec4u* plane, const Vec3f* lo,
                             const Vec3f* hi, float radius) {
    Vec3f a = *p;
    const Vec3f& nn = *reinterpret_cast<const Vec3f*>(plane);
    float nx = nn.x, ny = nn.y;
    float bx = a.x + nx;
    float by = a.y + ny;
    float nz = nn.z;
    float dx = bx - a.x;
    float dy = by - a.y;
    float bz = a.z + nz;
    float dz = bz - a.z;
    Vec4u hit;
    float denom = dx * plane->x + dy * plane->y + dz * plane->z;
    if (near_zero(denom)) {
        return 0;
    }
    float t = -(a.x * plane->x + a.y * plane->y + a.z * plane->z + plane->w) / denom;
    hit.x = p->x + dx * t;
    hit.y = p->y + dy * t;
    hit.z = p->z + dz * t;
    hit.w = 1.0f;
    float tol = radius * 0.5f + 1.1920929e-05f;
    if (__builtin_fabsf(t) > tol + 1.1920929e-05f) {
        return 0;
    }
    if ((hit.x < lo->x || hit.x > hi->x) && (hit.y < lo->y || hit.y > hi->y) && (hit.z < lo->z || hit.z > hi->z)) {
        return 0;
    }
    if (verts[0] == hit) {
        return 1;
    }
    Vec4u dir = verts[0] - hit;
    float inv = 1.0f / sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    dir.x = dir.x * inv;
    dir.y = inv * dir.y;
    dir.z = inv * dir.z;
    int crossings = 0;
    for (int i = 1; i < n; i++) {
        switch (classify_409078(&hit, &dir, &verts[i], &verts[(i + 1) % n])) {
        case 0:
            return -1;
        case 3:
        case 4:
        case 5:
        case 6:
        case 10:
        case 11:
        case 12:
            return 1;
        case 9:  // through the next vertex: find the first vertex off the ray and compare sides
            for (int k = 2; k < n; k++) {
                Vec4u e;
                e.v = verts[(k + i) % n].v - hit.v;
                float cx = dir.y * e.z - dir.z * e.y;
                float cy = dir.z * e.x - dir.x * e.z;
                float cz = dir.x * e.y - dir.y * e.x;
                if (!near_zero(cx) || !near_zero(cy) || !near_zero(cz)) {
                    Vec4u e0 = verts[i] - hit;
                    float c0x = dir.y * e0.z - dir.z * e0.y;
                    float c0y = dir.z * e0.x - dir.x * e0.z;
                    float c0z = dir.x * e0.y - dir.y * e0.x;
                    if (!(cx * c0x + cy * c0y + cz * c0z >= 0.0f)) {
                        crossings++;
                    }
                    i += k - 1;
                    break;
                }
                if (!(e.x * dir.x + dir.y * e.y + dir.z * e.z > 0.0f)) {
                    return 1;
                }
            }
            break;
        case 13:
            crossings++;
            break;
        }
    }
    return crossings % 2 == 1;
}

// 0x7100409078: where the ray from p along dir meets the segment a-b: 0 misses, 1 crosses (or the ray points
// away), 2-13 the degenerate cases (endpoints on the ray, p on an endpoint, collinear segment). Near miss: the
// same size, 7 instructions off abstracted; the collinear cross product's indexed multiplies, the tbz of the
// apart flag and the spill slots' order are left.
int classify_409078(const Vec4u* p, const Vec4u* dir, const Vec4u* a, const Vec4u* b) {
    Vec4u ea;
    ea.v = a->v - p->v;
    float cax = dir->y * ea.z - dir->z * ea.y;
    float cay = dir->z * ea.x - dir->x * ea.z;
    float caz = dir->x * ea.y - dir->y * ea.x;
    if (!near_zero(cax) || !near_zero(cay) || !near_zero(caz)) {
        Vec4u eb;
        eb.v = b->v - p->v;
        float cbx = dir->y * eb.z - dir->z * eb.y;
        float cby = dir->z * eb.x - dir->x * eb.z;
        float cbz = dir->x * eb.y - dir->y * eb.x;
        if (!near_zero(cbx) || !near_zero(cby) || !near_zero(cbz)) {
            float ia = 1.0f / sqrtf(cax * cax + cay * cay + caz * caz);
            float nax = cax * ia;
            float nay = cay * ia;
            float naz = caz * ia;
            float ib = 1.0f / sqrtf(cbx * cbx + cby * cby + cbz * cbz);
            float nbx = cbx * ib;
            float nby = cby * ib;
            float nbz = cbz * ib;
            float d = nax * nbx + nay * nby + naz * nbz;
            if (in_range(d, 1.0f - 1.1920929e-05f, 1.0f + 1.1920929e-05f)) {
                return 1;
            }
            if (!in_range(d, -1.0f - 1.1920929e-05f, -1.0f + 1.1920929e-05f)) {
                return 0;
            }
            float cx = ea.y * eb.z - ea.z * eb.y;
            float cy = ea.z * eb.x - ea.x * eb.z;
            float cz = ea.x * eb.y - ea.y * eb.x;
            if (near_zero(cx) && near_zero(cy) && near_zero(cz)) {
                return 6;
            }
            float s = (ea.x * dir->x + ea.y * dir->y + ea.z * dir->z) + (eb.x * dir->x + eb.y * dir->y + eb.z * dir->z);
            return s < 0.0f ? 1 : 13;
        }
        if (*p == *b) {
            return 12;
        }
        return eb.x * dir->x + eb.y * dir->y + eb.z * dir->z < 0.0f ? 1 : 9;
    }
    Vec4u eb;
    eb.v = b->v - p->v;
    float cbx = dir->y * eb.z - dir->z * eb.y;
    float cby = dir->z * eb.x - dir->x * eb.z;
    float cbz = dir->x * eb.y - dir->y * eb.x;
    if (!near_zero(cbx) || !near_zero(cby) || !near_zero(cbz)) {
        if (*p == *a) {
            return 11;
        }
        return ea.x * dir->x + ea.y * dir->y + ea.z * dir->z < 0.0f ? 1 : 8;
    }
    bool apart = *a != *b;
    bool at_a = *p == *a;
    if (apart) {
        if (at_a) {
            return 4;
        }
        if (*p == *b) {
            return 5;
        }
        int r = ea.x * dir->x + ea.y * dir->y + ea.z * dir->z < 0.0f ? 1 : 2;
        if (!(ea.x * eb.x + ea.y * eb.y + ea.z * eb.z >= 0.0f)) {
            return 3;
        }
        return r;
    }
    if (at_a) {
        return 10;
    }
    return ea.x * dir->x + ea.y * dir->y + ea.z * dir->z < 0.0f ? 1 : 7;
}
