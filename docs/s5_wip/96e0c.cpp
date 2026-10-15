// Fifth session, in progress: 0x7100096e0c (868 bytes) on include/misc/matrix_inverse.h: a node's transform (two calls
// of its virtual getter at +38: rotation angles at +50, position at +20), an XYZ Euler rotation from three sincos
// calls (fd70: sincos(angle, &sin, &cos)) with the position as row 3, its inverse applied to the input vector, then
// call_75ad0 (target +250, node, -1, kTrackDefaultVector, &out), or call_75a9c when the node is null; then flag
// 0x10000000 at +50. Same size, 47 instructions off abstracted.
// Settled: the frame (sin and cos are 16-byte aligned arrays inside an inlined rotation helper, so their slots die
// before the output vector's, which reuses sin's slot as in the original); row 0 computed first. Still off: the order
// of the sin/cos reloads after the calls and of the products, one translation lane loaded by ldr+mov instead of ld1.
// irsearch --groups reaches 14 off (sin/cos loads early, row 0's lanes reordered, one swizzle with its halves
// flipped, the input vector loaded earlier); --gmin keeps all of those, so no readable source order yet.
// Maps: --map .rodata.cst8=0x71007e2090 --map _Z12sincos_96e0cfPfS_=0x710000fd70
//   --map _Z16call_75ad0_96e0cPvP9Node96e0ciPKvPK13__Float32x4_t=0x7100075ad0
//   --map _Z16call_75a9c_96e0cPvPK13__Float32x4_t=0x7100075a9c --map got:kTrackDefaultVector_96e0c=0x7100c216a8
//   --name _ZN10Owner96e0c6updateEP9Node96e0cPK13__Float32x4_t
#include "misc/matrix_inverse.h"

struct Xform96e0c {
    unsigned char pad0[0x20];
    float pos[3];                     // +20
    unsigned char pad2c[0x24];
    float rot[3];                     // +50
};

struct Node96e0c {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual Xform96e0c* xform();      // +38
};

void sincos_96e0c(float angle, float* s, float* c);        // 0x710000fd70
void call_75ad0_96e0c(void* target, Node96e0c* node, int index, const void* def, const XMVECTOR* v);  // 0x7100075ad0
void call_75a9c_96e0c(void* target, const XMVECTOR* v);    // 0x7100075a9c
extern const unsigned char kTrackDefaultVector_96e0c[];

static inline XMMATRIX rotation_xyz_96e0c(const float* rot) {
    float s[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    sincos_96e0c(rot[0], &s[0], &c[0]);
    sincos_96e0c(rot[1], &s[1], &c[1]);
    sincos_96e0c(rot[2], &s[2], &c[2]);
    XMMATRIX m;
    m.r[0] = (float32x4_t){c[1] * c[2], c[1] * s[2], -s[1], 0.0f};
    m.r[1] = (float32x4_t){c[2] * (s[1] * s[0]) - s[2] * c[0], s[2] * (s[1] * s[0]) + c[2] * c[0], c[1] * s[0], 0.0f};
    m.r[2] = (float32x4_t){s[2] * s[0] + c[2] * (s[1] * c[0]), s[2] * (s[1] * c[0]) - c[2] * s[0], c[1] * c[0], 0.0f};
    m.r[3] = (float32x4_t){0.0f, 0.0f, 0.0f, 1.0f};
    return m;
}
struct Owner96e0c {
    unsigned char pad0[0x50];
    unsigned long flags;              // +50
    unsigned char pad58[0x1f8];
    unsigned char target[0x10];       // +250

    void update(Node96e0c* node, const XMVECTOR* v);
};

// 0x7100096e0c
void Owner96e0c::update(Node96e0c* node, const XMVECTOR* v) {
    if (node != nullptr) {
        Xform96e0c* r = node->xform();
        Xform96e0c* p = node->xform();
        XMVECTOR t = vld1q_lane_f32(&p->pos[0], vdupq_n_f32(1.0f), 0);
        t = vld1q_lane_f32(&p->pos[1], t, 1);
        t = vld1q_lane_f32(&p->pos[2], t, 2);
        XMMATRIX m = rotation_xyz_96e0c(r->rot);
        m.r[3] = t;
        XMVECTOR out = XMVector4Transform(*v, XMMatrixInverse(m));
        call_75ad0_96e0c(target, node, -1, kTrackDefaultVector_96e0c, &out);
    } else {
        call_75a9c_96e0c(target, v);
    }
    flags |= 0x10000000;
}
