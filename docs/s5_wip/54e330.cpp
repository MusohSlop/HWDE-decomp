// Fifth session, in progress: 0x710054e330 (948 bytes) on include/misc/matrix_inverse.h: a look-to matrix from three
// axes and an eye (dot products), translated by -P (row.xyz += row.w * t, so rows 0-2 get x + px * -0.0), times the
// inverse of the camera's projection, stored at +12b0; then the uniform block's dirty bit and a float uniform from the
// camera mode. 980 bytes here, 125 instructions off abstracted.
// Still off: our pre-RA scheduler hoists the projection loads, the constant-pool loads and constants to the top of
// the block and runs out of registers (d8-d14 saved); the original keeps the scalar part first. With
// -mllvm -enable-misched=false the size matches (948) and 64 are off; -misched-bottomup gives 61; irsearch (statement
// and instruction moves) does not get below 100, so the source shape differs, not just the order.
// Maps: --map .rodata.cst8=0x71007e2090 --name _ZN9Obj54e3306updateEP12Camera54e330
#include "misc/matrix_inverse.h"

struct Vec3f54e330 {
    float x, y, z;
};

struct Camera54e330 {
    Vec3f54e330 pos;                  // +0
    unsigned char pad0c[0x64];
    Vec3f54e330 axis_x;               // +70
    unsigned char pad7c[0x4];
    Vec3f54e330 axis_y;               // +80
    unsigned char pad8c[0x4];
    Vec3f54e330 axis_z;               // +90
    unsigned char pad9c[0x4];
    Vec3f54e330 eye;                  // +a0
    unsigned char padac[0x4];
    XMMATRIX proj;                    // +b0
    unsigned char padf0[0x58];
    int mode;                         // +148
};

struct Uniforms54e330 {
    unsigned long flags;              // +0
    unsigned char pad8[0xc8];
    void* matrix_slot;                // +d0
    unsigned char padd8[0xaa];
    unsigned short state;             // +182
    unsigned char pad184[0x4c];
    float value;                      // +1d0
};

struct Obj54e330 {
    unsigned char pad0[0x30];
    Uniforms54e330* uniforms;         // +30
    unsigned char pad38[0x1278];
    XMMATRIX mat;                     // +12b0

    void update(Camera54e330* cam);
};

int callee_57cd98();        // 0x710057cd98

struct Matrix44f54e330 {
    float m[4][4];
};

// 0x710054e330
void Obj54e330::update(Camera54e330* cam) {
    const Vec3f54e330& ax = cam->axis_x;
    const Vec3f54e330& ay = cam->axis_y;
    const Vec3f54e330& az = cam->axis_z;
    const Vec3f54e330& e = cam->eye;
    float d0 = -(ax.x * e.x + ax.y * e.y + ax.z * e.z);
    float d1 = -(ay.x * e.x + ay.y * e.y + ay.z * e.z);
    float d2 = -(az.x * e.x + az.y * e.y + az.z * e.z);
    float tx = -cam->pos.x;
    float ty = -cam->pos.y;
    float tz = -cam->pos.z;
    XMMATRIX view;
    view.r[0] = (float32x4_t){ax.x + 0.0f * tx, ay.x + 0.0f * ty, az.x + 0.0f * tz, 0.0f};
    view.r[1] = (float32x4_t){ax.y + 0.0f * tx, ay.y + 0.0f * ty, az.y + 0.0f * tz, 0.0f};
    view.r[2] = (float32x4_t){ax.z + 0.0f * tx, ay.z + 0.0f * ty, az.z + 0.0f * tz, 0.0f};
    view.r[3] = (float32x4_t){d0 + tx, d1 + ty, d2 + tz, 1.0f};
    XMMATRIX inv = XMMatrixInverse(cam->proj);
    mat.r[0] = XMVector4Transform(inv.r[0], view);
    mat.r[1] = XMVector4Transform(inv.r[1], view);
    mat.r[2] = XMVector4Transform(inv.r[2], view);
    mat.r[3] = XMVector4Transform(inv.r[3], view);
    Uniforms54e330* u = uniforms;
    if (u->matrix_slot != nullptr) {
        u->flags |= 1;
    }
    int mode = cam->mode;
    int kind = callee_57cd98();
    float f;
    if (mode & 2) {
        f = kind == 2 ? 0.0f : -1.0f;
    } else {
        f = kind == 2 ? 1.0f : (kind == 4 ? 0.0f : 1.0f);
    }
    u = uniforms;
    if (u->state != 1 || u->value != f) {
        u->flags |= 4;
        u->value = f;
        u->state = 1;
    }
}
