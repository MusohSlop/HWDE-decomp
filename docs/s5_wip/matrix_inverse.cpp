// Fifth session, notes: the 4x4 matrix inverse inlined in 23 unmatched functions (36,800 bytes; each has 24 tbl
// lookups, 5b5c1c has two copies): 96e0c a6470 1e26f8 2212c4 242070 3d0ca4 3e1538 3e6aa8 3f4b2c 41ff58 47f8ac 482bc4
// 489450 4b2e34 54e330 5a3ce0 5acba4 5ad154 5b5c1c 5b6cbc 5be884 5f4418 5f9fac (1e26f8 and 5f4418 have 12).
// It is built from DirectXMath's NEON primitives: the transpose as two rounds of vzipq_f32; swizzles as two
// vtbl2_u8 lookups on 8-byte control words (0x03020100-style, at 0x7e2090: YX, XX, ZZ, YY, WW, WZ) joined with
// vcombine_f32; XMVector4Dot (vmul, get_high + get_low, vpadd, vcombine); XMVectorReciprocal (vrecpe and two
// vrecps steps); then the result cleared where the determinant is zero (vceqq + vbicq). The cofactors use the
// swizzles YXXX, ZZYY and WWWZ of the transposed rows, fused multiply-adds (vfmaq/vfmsq) and the sign vectors
// (1, -1, 1, -1) and (-1, 1, -1, 1) at 0x73e0f0 and 0x73e100.
// Below: a scratch copy of 3e1538 (624 bytes, not in this session's range, used only as a test bed) with the
// inverse written that way. It compiles to the same size with every instruction of the inverse present and the
// arithmetic in the original's order; the difference is scheduling (the original makes the swizzles row by row
// from row 0 and keeps one register for the constant-pool adrp; ours starts with row 1), 56 instructions off when
// registers are abstracted. Mapping for tools/s5/sbs.py: --map .rodata.cst8=0x71007e2090 plus maps3e1538.txt
// (the two GOT globals). A search over 256 orders (transpose, swizzle lines by row or by kind, the cofactor
// blocks, where the signs are applied, the operand order of the final products) found no match; the best, kept
// below, is 49 off abstracted. What is left is how the constants are scheduled: the original loads each mask and
// identity row right before its use with one adrp register (x10) rematerialized each time, ours hoists them all to
// the top; so the source form of the swizzle or of the constants still differs. Once one copy matches, the same
// inline should carry to the other 22.

#include <arm_neon.h>

typedef float32x4_t XMVECTOR;
struct XMMATRIX {
    XMVECTOR r[4];
};

static const unsigned int kControl[4] = {0x03020100, 0x07060504, 0x0B0A0908, 0x0F0E0D0C};

template <unsigned E0, unsigned E1, unsigned E2, unsigned E3>
static inline XMVECTOR swizzle(XMVECTOR v) {
    uint8x8x2_t tbl;
    tbl.val[0] = vreinterpret_u8_f32(vget_low_f32(v));
    tbl.val[1] = vreinterpret_u8_f32(vget_high_f32(v));
    uint32x2_t idx = vcreate_u32(static_cast<unsigned long>(kControl[E0]) |
                                 (static_cast<unsigned long>(kControl[E1]) << 32));
    const uint8x8_t lo = vtbl2_u8(tbl, vreinterpret_u8_u32(idx));
    idx = vcreate_u32(static_cast<unsigned long>(kControl[E2]) | (static_cast<unsigned long>(kControl[E3]) << 32));
    const uint8x8_t hi = vtbl2_u8(tbl, vreinterpret_u8_u32(idx));
    return vcombine_f32(vreinterpret_f32_u8(lo), vreinterpret_f32_u8(hi));
}

static inline XMMATRIX transpose(const XMMATRIX& m) {
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

static inline XMVECTOR dot4(XMVECTOR a, XMVECTOR b) {
    float32x4_t t = vmulq_f32(a, b);
    float32x2_t v1 = vget_low_f32(t);
    float32x2_t v2 = vget_high_f32(t);
    v1 = vadd_f32(v2, v1);
    v1 = vpadd_f32(v1, v1);
    return vcombine_f32(v1, v1);
}

static inline XMVECTOR reciprocal(XMVECTOR v) {
    float32x4_t r = vrecpeq_f32(v);
    float32x4_t s = vrecpsq_f32(r, v);
    r = vmulq_f32(r, s);
    s = vrecpsq_f32(r, v);
    return vmulq_f32(r, s);
}

static inline XMMATRIX inverse(const XMMATRIX& m) {
    const float32x4_t sign1 = {1.0f, -1.0f, 1.0f, -1.0f};
    const float32x4_t sign2 = {-1.0f, 1.0f, -1.0f, 1.0f};
    XMMATRIX t = transpose(m);
    XMVECTOR d1 = swizzle<1, 0, 0, 0>(t.r[3]);
    XMVECTOR c1 = swizzle<1, 0, 0, 0>(t.r[2]);
    XMVECTOR b1 = swizzle<1, 0, 0, 0>(t.r[1]);
    XMVECTOR a1 = swizzle<1, 0, 0, 0>(t.r[0]);
    XMVECTOR d2 = swizzle<2, 2, 1, 1>(t.r[3]);
    XMVECTOR c2 = swizzle<2, 2, 1, 1>(t.r[2]);
    XMVECTOR b2 = swizzle<2, 2, 1, 1>(t.r[1]);
    XMVECTOR a2 = swizzle<2, 2, 1, 1>(t.r[0]);
    XMVECTOR d3 = swizzle<3, 3, 3, 2>(t.r[3]);
    XMVECTOR c3 = swizzle<3, 3, 3, 2>(t.r[2]);
    XMVECTOR b3 = swizzle<3, 3, 3, 2>(t.r[1]);
    XMVECTOR a3 = swizzle<3, 3, 3, 2>(t.r[0]);
    XMVECTOR t1 = vsubq_f32(vmulq_f32(c2, d3), vmulq_f32(c3, d2));
    XMVECTOR t2 = vsubq_f32(vmulq_f32(c1, d3), vmulq_f32(c3, d1));
    XMVECTOR t3 = vsubq_f32(vmulq_f32(c1, d2), vmulq_f32(c2, d1));
    XMVECTOR r0 = vfmaq_f32(vfmsq_f32(vmulq_f32(b1, t1), b2, t2), t3, b3);
    XMVECTOR r1 = vfmaq_f32(vfmsq_f32(vmulq_f32(a1, t1), a2, t2), t3, a3);
    r0 = vmulq_f32(r0, sign1);
    r1 = vmulq_f32(r1, sign2);
    XMVECTOR u1 = vsubq_f32(vmulq_f32(a2, b3), vmulq_f32(a3, b2));
    XMVECTOR u2 = vsubq_f32(vmulq_f32(a1, b3), vmulq_f32(a3, b1));
    XMVECTOR u3 = vsubq_f32(vmulq_f32(a1, b2), vmulq_f32(a2, b1));
    XMVECTOR r2 = vfmaq_f32(vfmsq_f32(vmulq_f32(u1, d1), d2, u2), u3, d3);
    XMVECTOR r3 = vfmaq_f32(vfmsq_f32(vmulq_f32(c1, u1), c2, u2), u3, c3);
    r2 = vmulq_f32(r2, sign1);
    r3 = vmulq_f32(r3, sign2);
    XMVECTOR det = dot4(t.r[0], r0);
    XMVECTOR rcp = reciprocal(det);
    uint32x4_t zero = vceqq_f32(det, vdupq_n_f32(0.0f));
    XMMATRIX out;
    out.r[0] = vreinterpretq_f32_u32(vbicq_u32(vreinterpretq_u32_f32(vmulq_f32(rcp, r0)), zero));
    out.r[1] = vreinterpretq_f32_u32(vbicq_u32(vreinterpretq_u32_f32(vmulq_f32(rcp, r1)), zero));
    out.r[2] = vreinterpretq_f32_u32(vbicq_u32(vreinterpretq_u32_f32(vmulq_f32(r2, rcp)), zero));
    out.r[3] = vreinterpretq_f32_u32(vbicq_u32(vreinterpretq_u32_f32(vmulq_f32(r3, rcp)), zero));
    return out;
}

struct Camera3e1538 {
    unsigned char pad0[0x350];
    unsigned char field_350[0x80];    // +350
    XMMATRIX view;                    // +3d0
    unsigned char pad410[0x190];
};

struct Cameras3e1538 {
    unsigned char pad0[0x0];
    Camera3e1538 cameras[8];
};

extern Cameras3e1538* gGlobalc21880_3e1538;

struct Table3e1538 {
    unsigned char pad0[0x430];
    void* field_430[8];               // +430
};
extern Table3e1538 gGlobalc21dd0_3e1538;

struct View3e1538;
void callee_3e17a8(View3e1538*, int, void*);        // 0x71003e17a8
void* callee_402c4(int);        // 0x71000402c4

struct View3e1538 {
    unsigned char pad0[0x28];
    unsigned char field_28;           // +28
    unsigned char pad29[0xf];
    int field_38;                     // +38
    unsigned char pad3c[0xb4];
    XMMATRIX inverse_views[8];        // +f0

    void update(int index);
};

static const XMMATRIX kIdentity = {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f},
                                    {0.0f, 0.0f, 0.0f, 1.0f}}};

// 0x71003e1538
void View3e1538::update(int index) {
    field_38 = 0;
    inverse_views[index].r[0] = (float32x4_t){1.0f, 0.0f, 0.0f, 0.0f};
    inverse_views[index].r[1] = (float32x4_t){0.0f, 1.0f, 0.0f, 0.0f};
    inverse_views[index].r[2] = (float32x4_t){0.0f, 0.0f, 1.0f, 0.0f};
    inverse_views[index].r[3] = (float32x4_t){0.0f, 0.0f, 0.0f, 1.0f};
    inverse_views[index] = inverse(gGlobalc21880_3e1538->cameras[index].view);
    if (field_28) {
        callee_3e17a8(this, index, gGlobalc21880_3e1538->cameras[index].field_350);
    }
    gGlobalc21dd0_3e1538.field_430[index] = callee_402c4(index);
}
