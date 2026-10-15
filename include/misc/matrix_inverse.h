// The NEON 4x4 matrix inverse inlined in about twenty functions, and the DirectXMath-style vector helpers it is
// built from: XMVECTOR is a float32x4_t, the transpose is two rounds of vzipq_f32, a swizzle is two vtbl lookups on
// 8-byte control words (constant-pool entries at 0x7e2090: YX, XX, ZZ, YY, WW, WZ) joined with vcombine_f32, the
// determinant is a 4-wide dot product and its reciprocal two Newton steps from vrecpe.
//
// The order of the statements in XMMatrixInverse is the source of the match, not a detail: the pre-RA scheduler
// leaves this block in IR order, so the order decides the live-range lengths, the greedy allocator assigns the long
// ranges longest first (ties to the lower vreg), and the post-RA scheduler interleaves the lookups according to the
// registers that come out. The d row's swizzles are made in the order d2, d1, d3 (it ties the YX control's range
// with c2's otherwise), and every cofactor row takes its sign in its own statement.
#pragma once

#include <arm_neon.h>

typedef float32x4_t XMVECTOR;
struct XMMATRIX {
    XMVECTOR r[4];
};

static const unsigned int kXMSwizzleControl[4] = {0x03020100, 0x07060504, 0x0B0A0908, 0x0F0E0D0C};

template <unsigned E0, unsigned E1, unsigned E2, unsigned E3>
static inline XMVECTOR XMVectorSwizzle(XMVECTOR v) {
    uint8x8x2_t tbl;
    tbl.val[0] = vreinterpret_u8_f32(vget_low_f32(v));
    tbl.val[1] = vreinterpret_u8_f32(vget_high_f32(v));
    uint32x2_t idx = vcreate_u32(static_cast<unsigned long>(kXMSwizzleControl[E0]) |
                                 (static_cast<unsigned long>(kXMSwizzleControl[E1]) << 32));
    const uint8x8_t lo = vtbl2_u8(tbl, vreinterpret_u8_u32(idx));
    idx = vcreate_u32(static_cast<unsigned long>(kXMSwizzleControl[E2]) |
                      (static_cast<unsigned long>(kXMSwizzleControl[E3]) << 32));
    const uint8x8_t hi = vtbl2_u8(tbl, vreinterpret_u8_u32(idx));
    return vcombine_f32(vreinterpret_f32_u8(lo), vreinterpret_f32_u8(hi));
}

static inline XMMATRIX XMMatrixIdentity() {
    XMMATRIX m;
    m.r[0] = (float32x4_t){1.0f, 0.0f, 0.0f, 0.0f};
    m.r[1] = (float32x4_t){0.0f, 1.0f, 0.0f, 0.0f};
    m.r[2] = (float32x4_t){0.0f, 0.0f, 1.0f, 0.0f};
    m.r[3] = (float32x4_t){0.0f, 0.0f, 0.0f, 1.0f};
    return m;
}

static inline XMMATRIX XMMatrixTranspose(XMMATRIX m) {
    float32x4x2_t p0 = vzipq_f32(m.r[0], m.r[2]);
    float32x4x2_t p1 = vzipq_f32(m.r[1], m.r[3]);
    float32x4x2_t t0 = vzipq_f32(p0.val[0], p1.val[0]);
    float32x4x2_t t1 = vzipq_f32(p0.val[1], p1.val[1]);
    XMMATRIX r;
    r.r[0] = t0.val[0];
    r.r[1] = t0.val[1];
    r.r[2] = t1.val[0];
    r.r[3] = t1.val[1];
    return r;
}

static inline XMVECTOR XMVector4Dot(XMVECTOR a, XMVECTOR b) {
    float32x4_t t = vmulq_f32(a, b);
    float32x2_t v1 = vget_low_f32(t);
    float32x2_t v2 = vget_high_f32(t);
    v1 = vadd_f32(v2, v1);
    v1 = vpadd_f32(v1, v1);
    return vcombine_f32(v1, v1);
}

static inline XMVECTOR XMVectorReciprocal(XMVECTOR v) {
    float32x4_t r = vrecpeq_f32(v);
    float32x4_t s = vrecpsq_f32(r, v);
    r = vmulq_f32(r, s);
    s = vrecpsq_f32(r, v);
    return vmulq_f32(r, s);
}

// v times m (row vector on the left): x * r0 + y * r1 + z * r2 + w * r3.
static inline XMVECTOR XMVector4Transform(XMVECTOR v, XMMATRIX m) {
    float32x2_t lo = vget_low_f32(v);
    float32x2_t hi = vget_high_f32(v);
    XMVECTOR r = vmulq_lane_f32(m.r[0], lo, 0);
    r = vfmaq_lane_f32(r, m.r[1], lo, 1);
    r = vfmaq_lane_f32(r, m.r[2], hi, 0);
    return vfmaq_lane_f32(r, m.r[3], hi, 1);
}

// The inverse by cofactors of the transposed rows (YXXX, ZZYY, WWWZ swizzles: the 3x3 minors), all zero when the
// determinant is zero.
static inline XMMATRIX XMMatrixInverse(XMMATRIX m) {
    const float32x4_t sign1 = {1.0f, -1.0f, 1.0f, -1.0f};
    const float32x4_t sign2 = {-1.0f, 1.0f, -1.0f, 1.0f};
    XMMATRIX t = XMMatrixTranspose(m);
    XMVECTOR a1 = XMVectorSwizzle<1, 0, 0, 0>(t.r[0]);
    XMVECTOR a2 = XMVectorSwizzle<2, 2, 1, 1>(t.r[0]);
    XMVECTOR a3 = XMVectorSwizzle<3, 3, 3, 2>(t.r[0]);
    XMVECTOR b1 = XMVectorSwizzle<1, 0, 0, 0>(t.r[1]);
    XMVECTOR b2 = XMVectorSwizzle<2, 2, 1, 1>(t.r[1]);
    XMVECTOR b3 = XMVectorSwizzle<3, 3, 3, 2>(t.r[1]);
    XMVECTOR c1 = XMVectorSwizzle<1, 0, 0, 0>(t.r[2]);
    XMVECTOR c2 = XMVectorSwizzle<2, 2, 1, 1>(t.r[2]);
    XMVECTOR c3 = XMVectorSwizzle<3, 3, 3, 2>(t.r[2]);
    XMVECTOR d2 = XMVectorSwizzle<2, 2, 1, 1>(t.r[3]);
    XMVECTOR d1 = XMVectorSwizzle<1, 0, 0, 0>(t.r[3]);
    XMVECTOR d3 = XMVectorSwizzle<3, 3, 3, 2>(t.r[3]);
    XMVECTOR t1 = vsubq_f32(vmulq_f32(c2, d3), vmulq_f32(c3, d2));
    XMVECTOR t2 = vsubq_f32(vmulq_f32(c1, d3), vmulq_f32(c3, d1));
    XMVECTOR t3 = vsubq_f32(vmulq_f32(c1, d2), vmulq_f32(c2, d1));
    XMVECTOR r0 = vmulq_f32(vfmaq_f32(vfmsq_f32(vmulq_f32(b1, t1), b2, t2), b3, t3), sign1);
    XMVECTOR r1 = vmulq_f32(vfmaq_f32(vfmsq_f32(vmulq_f32(a1, t1), a2, t2), a3, t3), sign2);
    XMVECTOR u1 = vsubq_f32(vmulq_f32(a2, b3), vmulq_f32(a3, b2));
    XMVECTOR u2 = vsubq_f32(vmulq_f32(a1, b3), vmulq_f32(a3, b1));
    XMVECTOR u3 = vsubq_f32(vmulq_f32(a1, b2), vmulq_f32(a2, b1));
    XMVECTOR r2 = vmulq_f32(vfmaq_f32(vfmsq_f32(vmulq_f32(u1, d1), d2, u2), d3, u3), sign1);
    XMVECTOR r3 = vmulq_f32(vfmaq_f32(vfmsq_f32(vmulq_f32(c1, u1), c2, u2), c3, u3), sign2);
    XMVECTOR det = XMVector4Dot(t.r[0], r0);
    XMVECTOR rcp = XMVectorReciprocal(det);
    uint32x4_t zero = vceqq_f32(det, vdupq_n_f32(0.0f));
    XMVECTOR s0 = vmulq_f32(rcp, r0);
    XMVECTOR s1 = vmulq_f32(rcp, r1);
    XMVECTOR s2 = vmulq_f32(r2, rcp);
    XMVECTOR s3 = vmulq_f32(r3, rcp);
    XMMATRIX out;
    out.r[0] = vreinterpretq_f32_u32(vbicq_u32(vreinterpretq_u32_f32(s0), zero));
    out.r[1] = vreinterpretq_f32_u32(vbicq_u32(vreinterpretq_u32_f32(s1), zero));
    out.r[2] = vreinterpretq_f32_u32(vbicq_u32(vreinterpretq_u32_f32(s2), zero));
    out.r[3] = vreinterpretq_f32_u32(vbicq_u32(vreinterpretq_u32_f32(s3), zero));
    return out;
}
