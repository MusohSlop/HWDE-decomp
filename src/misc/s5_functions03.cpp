// Functions with the inlined NEON 4x4 matrix inverse (fifth session), on the shared include/misc/matrix_inverse.h.
// Struct, field and callee names are placeholders after the address and offset, as in the generated units.
// Status: matching/README.md.

#include "misc/matrix_inverse.h"

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
    XMVECTOR r = XMVector4Transform(v, XMMatrixTranspose(XMMatrixInverse(src->view)));
    Target5a3ce0* t = target;
    if (t->state != 1 || t->v[0] != vgetq_lane_f32(r, 0) || t->v[1] != vgetq_lane_f32(r, 1) ||
        t->v[2] != vgetq_lane_f32(r, 2) || t->v[3] != vgetq_lane_f32(r, 3)) {
        t->flags |= 0x4000000;
        vst1q_f32(t->v, r);
        t->state = 1;
    }
}

struct View3e1538 {
    unsigned char pad0[0x350];
    unsigned char data_350[0x80];     // +350
    XMMATRIX view;                    // +3d0
    unsigned char pad410[0x190];
};
extern View3e1538* gGlobalc21880_3e1538;

struct Table3e1538 {
    unsigned char pad0[0x430];
    void* entries[8];                 // +430
};
extern Table3e1538 gGlobalc21dd0_3e1538;
void* callee_402c4(int);          // 0x71000402c4

struct Obj3e1538 {
    unsigned char pad0[0x28];
    bool flag_28;                     // +28
    unsigned char pad29[0xf];
    int field_38;                     // +38
    unsigned char pad3c[0xb4];
    XMMATRIX mats[4];                 // +f0

    void callee_3e17a8(int, void*);   // 0x71003e17a8
    void update(int idx);
};

// 0x71003e1538: the identity stored first stays (the view may alias the slot without TBAA).
void Obj3e1538::update(int idx) {
    View3e1538* views = gGlobalc21880_3e1538;
    field_38 = 0;
    mats[idx] = XMMatrixIdentity();
    mats[idx] = XMMatrixInverse(views[idx].view);
    if (flag_28) {
        callee_3e17a8(idx, views[idx].data_350);
    }
    gGlobalc21dd0_3e1538.entries[idx] = callee_402c4(idx);
}