// Fifth session, notes: the NEON 4x4 matrix inverse is matched and shared as include/misc/matrix_inverse.h (5a3ce0
// and 3e1538 in misc/s5_functions03.cpp). Copies left: 96e0c a6470 2212c4 242070 3d0ca4 3e6aa8 3f4b2c 41ff58 47f8ac
// 482bc4 489450 4b2e34 54e330 5acba4 5ad154 5b5c1c 5b6cbc 5be884 5f9fac (1e26f8 and 5f4418 are a look-at, not the
// inverse). The generator fails on all of them (zip/tbl/d registers), so each is written by hand around the inline.
//
// 3d0ca4 (1,556 bytes, below, on the shared inline): same size, 31 instructions off abstracted, all from the frame:
// the original's frame is 0xe0 bytes (ours 0xc0) and keeps the viewport return slot, the uv vector, the matrix and one
// shared slot for the view info, exposure and length temporaries apart; LLVM 3.9's stack colouring starts a slot at
// its first use, and every form tried lets the matrix share the temporaries' slot. Maps for tools/s5/sbs.py:
//   --map .rodata.cst8=0x71007e2090 --map tanf=0x7100600970 --map got:gGlobalc21880_3d0ca4=0x7100c21880
//   --map got:gGlobalc21db0_3d0ca4=0x7100c21db0 --name _ZN10Pass3d0ca45setupEjiiP12Source3d0ca4S1_

#include "misc/matrix_inverse.h"
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
    XMMATRIX m = XMMatrixInverse(camera->view);
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
