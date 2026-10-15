// Fifth session, in progress: 0x71005b6cbc (784 bytes) on include/misc/matrix_inverse.h: an input matrix (16 scalar
// loads) times a texture bias (x' = 0.5x + 0.5w, y' = 0.5w - 0.5y, z' = z + 0w, w' = w: a scale and a translate,
// row.xyz += row.w * t), the transposed inverse applies to a vector from the referenced object (w = its +a8 minus
// this+aa0), and a second vector of three differences. Same size, 37 instructions off abstracted, all in the scalar
// part's order (the pre-RA scheduler keeps the IR order here, so it is the source order). InstCombine gives
// 0.5w - 0.5y from any form; the original computes y*0.5 early with the x products. irsearch --groups got to 24 off
// (the orders it finds are not yet readable as source).
// Maps: --map .rodata.cst8=0x71007e2090 --name _ZN9Obj5b6cbc4calcEP13__Float32x4_tPK15Matrix44f5b6cbc
#include "misc/matrix_inverse.h"

struct Matrix44f5b6cbc {
    float m[4][4];
};

struct Ref5b6cbc {
    unsigned char pad0[0x78];
    float f78;                        // +78
    unsigned char pad7c[0xc];
    float f88;                        // +88
    unsigned char pad8c[0xc];
    float f98;                        // +98
    unsigned char pad9c[0xc];
    float fa8;                        // +a8
};

struct Obj5b6cbc {
    unsigned char pad0[0xaa0];
    float base;                       // +aa0
    float f_aa4;                      // +aa4
    float f_aa8;                      // +aa8
    float f_aac;                      // +aac
    unsigned char padab0[0x10];
    Ref5b6cbc* ref;                   // +ac0

    void calc(XMVECTOR* out, const Matrix44f5b6cbc* m);
};

// 0x71005b6cbc
void Obj5b6cbc::calc(XMVECTOR* out, const Matrix44f5b6cbc* in) {
    XMMATRIX b;
    for (int i = 0; i < 4; i++) {
        float x = in->m[i][0];
        float y = in->m[i][1];
        float z = in->m[i][2];
        float w = in->m[i][3];
        b.r[i] = (float32x4_t){x * 0.5f + w * 0.5f, w * 0.5f - y * 0.5f, z + w * 0.0f, w};
    }
    XMMATRIX t = XMMatrixTranspose(XMMatrixInverse(b));
    Ref5b6cbc* r = ref;
    XMVECTOR v = {r->f78, r->f88, r->f98, r->fa8 - base};
    out[0] = XMVector4Transform(v, t);
    out[1] = (float32x4_t){f_aa4 - base, f_aa8 - base, f_aac - base, 0.0f};
}
