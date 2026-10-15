// Fifth session, notes: the 4x4 matrix inverse inlined in 23 unmatched functions (36,800 bytes; each has 24 tbl
// lookups, 5b5c1c has two copies): 96e0c a6470 1e26f8 2212c4 242070 3d0ca4 3e1538 3e6aa8 3f4b2c 41ff58 47f8ac 482bc4
// 489450 4b2e34 54e330 5a3ce0 5acba4 5ad154 5b5c1c 5b6cbc 5be884 5f4418 5f9fac (1e26f8 and 5f4418 have 12).
//
// It is built from DirectXMath's NEON primitives: the transpose as two rounds of vzipq_f32; swizzles as two
// vtbl2_u8 lookups on 8-byte control words (0x03020100-style, at 0x7e2090: YX, XX, ZZ, YY, WW, WZ) joined with
// vcombine_f32; XMVector4Dot (vmul, get_high + get_low, vpadd, vcombine); XMVectorReciprocal (vrecpe and two
// vrecps steps); then the result cleared where the determinant is zero (vceqq + vbicq). The cofactors use the
// swizzles YXXX, ZZYY and WWWZ of the transposed rows, fused multiply-adds (vfmaq/vfmsq) and the sign vectors
// (1, -1, 1, -1) and (-1, 1, -1, 1) at 0x73e0f0 and 0x73e100.
//
// What is settled (each step measured): the matrix and the transpose take XMMATRIX by value (FXMMATRIX), so the
// four rows load in order before the zips; the swizzles are computed row by row (a1 a2 a3, b1 ... d3); the cofactor
// order is t1 t2 t3, r0 r1 (each times its sign in the same statement), u1 u2 u3, r2 r3 (signs applied after);
// vfmaq_f32's multiplicands are written (b3, t3), (a3, t3), (d3, u3), (c3, u3) (the instruction then comes out as
// the original's fmla v, t3, b3); the four products by the reciprocal are made before the four vbicq; the
// determinant is (high + low) then vpadd. The swizzle's internal form does not matter (vtbl2_u8 / vtbl2_s8 /
// vqtbl1_u8, combined as u8 or f32), nor do constant-pool masks versus extern const globals at their addresses.
//
// Best results: 5a3ce0 (712 bytes, below) is the same size with 5 instructions off when registers are abstracted
// (44 words): one pocket where the original schedules the d row's XX lookup right after the c row's YY lookup and
// the a3 * b2 product later; no statement order (216 orders of the cofactor blocks, 40 interleavings of the c and d
// swizzles with either half first) closes it. 3d0ca4 (1,556 bytes, second draft below) is the same size and 35 off:
// its frame differs (the original keeps the matrix, the uv vector and one shared slot for the viewport, view info,
// exposure and length temporaries apart; LLVM 3.9's stack colouring starts a slot at its first use, and every form
// tried here lets the matrix share the temporaries' slot, which also changes how the inverse's registers are
// chosen). 3e1538 (624 bytes) has an identity matrix stored to the same place first; without it the inverse there
// schedules like the original. Maps: tools/s5/sbs.py --map .rodata.cst8=0x71007e2090 (and tanf=0x7100600970 and the
// two GOT globals for 3d0ca4, see the draft).

// ===== 0x71005a3ce0 draft (5 off abstracted) =====

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

static inline XMMATRIX transpose(XMMATRIX m) {
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

static inline XMMATRIX inverse(XMMATRIX m) {
    const float32x4_t sign1 = {1.0f, -1.0f, 1.0f, -1.0f};
    const float32x4_t sign2 = {-1.0f, 1.0f, -1.0f, 1.0f};
    XMMATRIX t = transpose(m);
    XMVECTOR a1 = swizzle<1, 0, 0, 0>(t.r[0]);
    XMVECTOR a2 = swizzle<2, 2, 1, 1>(t.r[0]);
    XMVECTOR a3 = swizzle<3, 3, 3, 2>(t.r[0]);
    XMVECTOR b1 = swizzle<1, 0, 0, 0>(t.r[1]);
    XMVECTOR b2 = swizzle<2, 2, 1, 1>(t.r[1]);
    XMVECTOR b3 = swizzle<3, 3, 3, 2>(t.r[1]);
    XMVECTOR c1 = swizzle<1, 0, 0, 0>(t.r[2]);
    XMVECTOR c2 = swizzle<2, 2, 1, 1>(t.r[2]);
    XMVECTOR c3 = swizzle<3, 3, 3, 2>(t.r[2]);
    XMVECTOR d1 = swizzle<1, 0, 0, 0>(t.r[3]);
    XMVECTOR d2 = swizzle<2, 2, 1, 1>(t.r[3]);
    XMVECTOR d3 = swizzle<3, 3, 3, 2>(t.r[3]);
    XMVECTOR t1 = vsubq_f32(vmulq_f32(c2, d3), vmulq_f32(c3, d2));
    XMVECTOR t2 = vsubq_f32(vmulq_f32(c1, d3), vmulq_f32(c3, d1));
    XMVECTOR t3 = vsubq_f32(vmulq_f32(c1, d2), vmulq_f32(c2, d1));
    XMVECTOR r0 = vmulq_f32(vfmaq_f32(vfmsq_f32(vmulq_f32(b1, t1), b2, t2), b3, t3), sign1);
    XMVECTOR r1 = vmulq_f32(vfmaq_f32(vfmsq_f32(vmulq_f32(a1, t1), a2, t2), a3, t3), sign2);
    XMVECTOR u1 = vsubq_f32(vmulq_f32(a2, b3), vmulq_f32(a3, b2));
    XMVECTOR u2 = vsubq_f32(vmulq_f32(a1, b3), vmulq_f32(a3, b1));
    XMVECTOR u3 = vsubq_f32(vmulq_f32(a1, b2), vmulq_f32(a2, b1));
    XMVECTOR r2 = vfmaq_f32(vfmsq_f32(vmulq_f32(u1, d1), d2, u2), d3, u3);
    XMVECTOR r3 = vfmaq_f32(vfmsq_f32(vmulq_f32(c1, u1), c2, u2), c3, u3);
    r2 = vmulq_f32(r2, sign1);
    r3 = vmulq_f32(r3, sign2);
    XMVECTOR det = dot4(t.r[0], r0);
    XMVECTOR rcp = reciprocal(det);
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


struct Source5a3ce0 {
    unsigned char pad0[0x1880];
    float m[4][4];                    // +1880
    XMMATRIX view;                    // +18c0
};

struct Target5a3ce0 {
    unsigned long flags;              // +0
    unsigned char pad8[0xd7a];
    unsigned short state;             // +d82
    unsigned char padd84[0x4c];
    float v[4];                       // +dd0
};

struct Light5a3ce0 {
    unsigned char pad0[0x88];
    Target5a3ce0* target;             // +88
    unsigned char pad90[0x30];
    Source5a3ce0* source;             // +c0
    unsigned char padc8[0x18];
    float near_clip;                  // +e0
    float far_clip;                   // +e4

    void update();
};

static inline XMVECTOR transform(XMVECTOR v, XMMATRIX m) {
    float32x2_t lo = vget_low_f32(v);
    float32x2_t hi = vget_high_f32(v);
    XMVECTOR r = vmulq_lane_f32(m.r[0], lo, 0);
    r = vfmaq_lane_f32(r, m.r[1], lo, 1);
    r = vfmaq_lane_f32(r, m.r[2], hi, 0);
    return vfmaq_lane_f32(r, m.r[3], hi, 1);
}

// 0x71005a3ce0
void Light5a3ce0::update() {
    float a = near_clip;
    float b = far_clip;
    Source5a3ce0* src = source;
    XMVECTOR v;
    if (a < b) {
        float32x4_t p = {src->m[0][3], src->m[1][3], src->m[2][3], src->m[3][3] - b};
        v = vmulq_n_f32(p, -1.0f / (b - a));
    } else {
        v = (float32x4_t){0.0f, 0.0f, 0.0f, 1.0f};
    }
    XMVECTOR r = transform(v, transpose(inverse(src->view)));
    Target5a3ce0* t = target;
    if (t->state != 1 || t->v[0] != vgetq_lane_f32(r, 0) || t->v[1] != vgetq_lane_f32(r, 1) ||
        t->v[2] != vgetq_lane_f32(r, 2) || t->v[3] != vgetq_lane_f32(r, 3)) {
        t->flags |= 0x4000000;
        vst1q_f32(t->v, r);
        t->state = 1;
    }
}


// ===== 0x71003d0ca4 draft (35 off abstracted) =====
#if 0
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

static inline XMMATRIX transpose(XMMATRIX m) {
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

static inline XMMATRIX inverse(XMMATRIX m) {
    const float32x4_t sign1 = {1.0f, -1.0f, 1.0f, -1.0f};
    const float32x4_t sign2 = {-1.0f, 1.0f, -1.0f, 1.0f};
    XMMATRIX t = transpose(m);
    XMVECTOR a1 = swizzle<1, 0, 0, 0>(t.r[0]);
    XMVECTOR a2 = swizzle<2, 2, 1, 1>(t.r[0]);
    XMVECTOR a3 = swizzle<3, 3, 3, 2>(t.r[0]);
    XMVECTOR b1 = swizzle<1, 0, 0, 0>(t.r[1]);
    XMVECTOR b2 = swizzle<2, 2, 1, 1>(t.r[1]);
    XMVECTOR b3 = swizzle<3, 3, 3, 2>(t.r[1]);
    XMVECTOR c1 = swizzle<1, 0, 0, 0>(t.r[2]);
    XMVECTOR c2 = swizzle<2, 2, 1, 1>(t.r[2]);
    XMVECTOR c3 = swizzle<3, 3, 3, 2>(t.r[2]);
    XMVECTOR d1 = swizzle<1, 0, 0, 0>(t.r[3]);
    XMVECTOR d2 = swizzle<2, 2, 1, 1>(t.r[3]);
    XMVECTOR d3 = swizzle<3, 3, 3, 2>(t.r[3]);
    XMVECTOR t1 = vsubq_f32(vmulq_f32(c2, d3), vmulq_f32(c3, d2));
    XMVECTOR t2 = vsubq_f32(vmulq_f32(c1, d3), vmulq_f32(c3, d1));
    XMVECTOR t3 = vsubq_f32(vmulq_f32(c1, d2), vmulq_f32(c2, d1));
    XMVECTOR r0 = vmulq_f32(vfmaq_f32(vfmsq_f32(vmulq_f32(b1, t1), b2, t2), b3, t3), sign1);
    XMVECTOR r1 = vmulq_f32(vfmaq_f32(vfmsq_f32(vmulq_f32(a1, t1), a2, t2), a3, t3), sign2);
    XMVECTOR u1 = vsubq_f32(vmulq_f32(a2, b3), vmulq_f32(a3, b2));
    XMVECTOR u2 = vsubq_f32(vmulq_f32(a1, b3), vmulq_f32(a3, b1));
    XMVECTOR u3 = vsubq_f32(vmulq_f32(a1, b2), vmulq_f32(a2, b1));
    XMVECTOR r2 = vfmaq_f32(vfmsq_f32(vmulq_f32(u1, d1), d2, u2), d3, u3);
    XMVECTOR r3 = vfmaq_f32(vfmsq_f32(vmulq_f32(c1, u1), c2, u2), c3, u3);
    r2 = vmulq_f32(r2, sign1);
    r3 = vmulq_f32(r3, sign2);
    XMVECTOR det = dot4(t.r[0], r0);
    XMVECTOR rcp = reciprocal(det);
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

extern const char kINPUTSCENE_7dbd82[] __attribute__((visibility("hidden")));
extern const char kVUVOffset_7dbd8e[] __attribute__((visibility("hidden")));
extern const char kVViewInfo_7dbd98[] __attribute__((visibility("hidden")));
extern const char kMatV2W1_7dbe58[] __attribute__((visibility("hidden")));
extern const char kMatV2W2_7dbe61[] __attribute__((visibility("hidden")));
extern const char kMatV2W3_7dbe6a[] __attribute__((visibility("hidden")));
extern const char kMatV2W4_7dbe73[] __attribute__((visibility("hidden")));
extern const char kFExposure_7dbe0e[] __attribute__((visibility("hidden")));
extern const char kTexZ_7dbda2[] __attribute__((visibility("hidden")));
extern const char kTexBlurWeight_7dbda7[] __attribute__((visibility("hidden")));
extern const char kFEyeToAtLength_7dbdb5[] __attribute__((visibility("hidden")));
extern const char kFAperture_7dbdc4[] __attribute__((visibility("hidden")));
extern const char kFFov_7dbdce[] __attribute__((visibility("hidden")));
extern const char kFNear_7dbdd3[] __attribute__((visibility("hidden")));
extern const char kFFar_7dbdd9[] __attribute__((visibility("hidden")));

extern "C" float tanf(float);
extern "C" float sqrtf(float);

struct Shader3d0ca4;
struct Texture3d0ca4;
int callee_570f28(Shader3d0ca4*, const char*);        // 0x7100570f28
void callee_571318(Shader3d0ca4*, int, void*);        // 0x7100571318
void callee_5710a8(Shader3d0ca4*, const char*, const void*, int);        // 0x71005710a8
int callee_570eac(Shader3d0ca4*, const char*);        // 0x7100570eac
void callee_570fa4(Shader3d0ca4*, int, const void*, int);        // 0x7100570fa4

struct Camera3d0ca4 {
    unsigned char pad0[0x10];
    float target[3];                  // +10
    unsigned char pad1c[0x4];
    float eye[3];                     // +20
    unsigned char pad2c[0x54];
    XMMATRIX view;                    // +80
    unsigned char padc0[0x80];
    float near_clip;                  // +140
    float far_clip;                   // +144
    float fov;                        // +148
    float aspect;                     // +14c
    unsigned char pad150[0xc];
    float aperture;                   // +15c
};
void* callee_3d2fd4();        // 0x71003d2fd4
Camera3d0ca4* callee_3d6864(void*, int);        // 0x71003d6864

struct View3d0ca4 {
    unsigned char pad0[0x28];
    float width;                      // +28 (of the view at +5a0)
    float height;                     // +2c
    unsigned char pad30[0x570];
};
struct Views3d0ca4 {
    unsigned char pad0[0x5a0];
    View3d0ca4 views[4][2];           // +5a0
};
extern Views3d0ca4* gGlobalc21880_3d0ca4;
unsigned char callee_3df658(Views3d0ca4*);        // 0x71003df658

struct Viewport3d0ca4 {
    int x, y, w, h;
    int extra;
};
Viewport3d0ca4 callee_5159a0(void*);        // 0x71005159a0
extern void* gGlobalc21db0_3d0ca4;

struct TextureList3d0ca4 {
    unsigned char pad0[0x18];
    int count;                        // +18
    unsigned char pad1c[0x4];
    void* first;                      // +20
};

struct Source3d0ca4 {
    unsigned char pad0[0x10];
    unsigned char texture[1];         // +10
};

struct Pass3d0ca4 {
    unsigned char pad0[0x48];
    Shader3d0ca4* shaders[4][3];      // +48
    unsigned char padA8[0x10];
    TextureList3d0ca4* blur;          // +b8
    unsigned char padc0[0xc0];
    int exposure[4];                  // +180
    unsigned char pad190[0x40];
    float aperture_override[4];       // +1d0
    int selected[4];                  // +1e0

    void setup(unsigned int view, int eye, int stage, Source3d0ca4* scene, Source3d0ca4* depth);
};

// 0x71003d0ca4
void Pass3d0ca4::setup(unsigned int view, int eye, int stage, Source3d0ca4* scene, Source3d0ca4* depth) {
    Shader3d0ca4* shader = shaders[eye][stage];
    callee_571318(shader, callee_570f28(shader, kINPUTSCENE_7dbd82), scene->texture);
    if (stage == 2) {
        return;
    }
    Camera3d0ca4* camera = callee_3d6864(callee_3d2fd4(), eye);
    bool half = callee_3df658(gGlobalc21880_3d0ca4);
    {
        Viewport3d0ca4 vp = callee_5159a0(gGlobalc21db0_3d0ca4);
        float uv[4];
        View3d0ca4& v = gGlobalc21880_3d0ca4->views[view][eye];
        uv[0] = static_cast<float>(vp.w) / v.width;
        uv[1] = static_cast<float>(vp.h) / v.height;
        uv[2] = static_cast<float>(vp.x) / v.width;
        uv[3] = static_cast<float>(vp.y) / v.height;
        if (half) {
            if (eye == 1) {
                uv[1] *= 0.5f;
            }
            uv[3] *= 0.5f;
        }
        callee_5710a8(shader, kVUVOffset_7dbd8e, uv, 0x10);
    }
    {
        float t = tanf(camera->fov * 0.5f);
        float info[4];
        info[0] = (t + t) * camera->aspect;
        info[1] = t * -2.0f;
        info[2] = camera->far_clip / (camera->near_clip - camera->far_clip);
        info[3] = (camera->near_clip * camera->far_clip) / (camera->far_clip - camera->near_clip);
        callee_5710a8(shader, kVViewInfo_7dbd98, info, 0x10);
    }
    XMMATRIX m = inverse(camera->view);
    callee_5710a8(shaders[0][selected[0]], kMatV2W1_7dbe58, &m.r[0], 0x10);
    callee_5710a8(shaders[0][selected[0]], kMatV2W2_7dbe61, &m.r[1], 0x10);
    callee_5710a8(shaders[0][selected[0]], kMatV2W3_7dbe6a, &m.r[2], 0x10);
    callee_5710a8(shaders[0][selected[0]], kMatV2W4_7dbe73, &m.r[3], 0x10);
    {
        int exp = exposure[eye];
        Shader3d0ca4* target;
        if (static_cast<unsigned int>(stage) < 3) {
            target = shaders[eye][stage];
        } else {
            target = shaders[eye][selected[eye]];
        }
        callee_5710a8(target, kFExposure_7dbe0e, &exp, 4);
    }
    if (stage == 0) {
        callee_571318(shader, callee_570eac(shader, kTexZ_7dbda2), depth->texture);
        int index = callee_570eac(shader, kTexBlurWeight_7dbda7);
        if (blur != nullptr) {
            callee_571318(shader, index, blur->count >= 1 ? blur->first : nullptr);
        }
    } else if (stage == 1) {
        callee_571318(shader, callee_570eac(shader, kTexZ_7dbda2), depth->texture);
        int index = callee_570eac(shader, kFEyeToAtLength_7dbdb5);
        float dx = camera->eye[0] - camera->target[0];
        float dy = camera->eye[1] - camera->target[1];
        float dz = camera->eye[2] - camera->target[2];
        float length = sqrtf(dx * dx + dy * dy + dz * dz);
        if (aperture_override[eye] > 0.0f) {
            length = aperture_override[eye];
            aperture_override[eye] = -1.0f;
        }
        callee_570fa4(shader, index, &length, 4);
        callee_570fa4(shader, callee_570eac(shader, kFAperture_7dbdc4), &camera->aperture, 4);
        callee_570fa4(shader, callee_570eac(shader, kFFov_7dbdce), &camera->fov, 4);
        callee_570fa4(shader, callee_570eac(shader, kFNear_7dbdd3), &camera->near_clip, 4);
        callee_570fa4(shader, callee_570eac(shader, kFFar_7dbdd9), &camera->far_clip, 4);
    }
}

#endif
