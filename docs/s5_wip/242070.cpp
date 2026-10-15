// Fifth session, in progress: 0x7100242070 (876 bytes) on include/misc/matrix_inverse.h: an object's matrix (at base +
// this->offset) multiplied by the world matrix (this+188), a ray from it (origin the product's row 3, direction
// (0,0,1,0) through its rotation) tested by 241058; on a hit 241088 builds a new matrix (row 3 the ray origin), and the
// result times inverse(world) is stored back. 860 bytes here, 93 instructions off abstracted.
// Settled: the finite test on the translation is (bits & 0x7f800000) < 0x7f800000 (gives ubfx; cmp #0xfe; b.hi) on
// floats read through a 16-aligned type (so GVN widens x and y into one 8-byte load, as the original does); the
// direction's products are splat-first fmla (the shared XMVector4Transform is now splat-first); t is declared before
// the ray (frame order). Still off: our pre-RA scheduler sinks the product M*W below the inverse's swizzles (MIR
// position 32 -> 111), the original keeps it before the zips, which raises the pressure into d8-d12 (0x140 frame); no
// statement order tried (product/ray/inverse in four orders, irsearch --groups 1,500 tries: 93 -> 88) keeps it there.
// Maps: --map .rodata.cst8=0x71007e2090 --name _ZN9Obj2420706updateEPc
#include "misc/matrix_inverse.h"

union Mat242070 {
    XMMATRIX v;
    float m[4][4];
};

static inline bool is_finite_242070(float f) {
    union {
        float f;
        unsigned int i;
    } u;
    u.f = f;
    return (u.i & 0x7f800000) < 0x7f800000;
}

static inline XMMATRIX XMMatrixMultiply(XMMATRIX a, XMMATRIX b) {
    XMMATRIX r;
    r.r[0] = XMVector4Transform(a.r[0], b);
    r.r[1] = XMVector4Transform(a.r[1], b);
    r.r[2] = XMVector4Transform(a.r[2], b);
    r.r[3] = XMVector4Transform(a.r[3], b);
    return r;
}

struct Ray242070 {
    XMVECTOR origin;
    XMVECTOR dir;
};

bool callee_241058(Ray242070* ray, float* t, XMVECTOR* hit);           // 0x7100241058
void callee_241088(XMMATRIX* out, const XMVECTOR* hit, const XMVECTOR* dir);  // 0x7100241088

struct Obj242070 {
    unsigned char pad0[0x3c];
    int offset;                       // +3c
    unsigned char pad40[0x148];
    XMMATRIX* world;                  // +188

    void update(char* base);
};

// 0x7100242070
void Obj242070::update(char* base) {
    XMMATRIX* m = reinterpret_cast<XMMATRIX*>(base + offset);
    const Mat242070* f = reinterpret_cast<const Mat242070*>(m);
    if (!is_finite_242070(f->m[3][0]) || !is_finite_242070(f->m[3][1]) || !is_finite_242070(f->m[3][2])) {
        return;
    }
    XMMATRIX w = *world;
    XMMATRIX p = XMMatrixMultiply(*m, w);
    XMMATRIX inv = XMMatrixInverse(w);
    float t;
    Ray242070 ray;
    ray.origin = p.r[3];
    XMMATRIX rot = p;
    rot.r[3] = (float32x4_t){0.0f, 0.0f, 0.0f, 1.0f};
    ray.dir = XMVector4Transform((float32x4_t){0.0f, 0.0f, 1.0f, 0.0f}, rot);
    XMVECTOR hit;
    XMMATRIX n;
    if (callee_241058(&ray, &t, &hit)) {
        callee_241088(&n, &hit, &ray.dir);
        n.r[3] = ray.origin;
    } else {
        n = p;
    }
    *m = XMMatrixMultiply(n, inv);
}
