// The binding gatherers (fifth session): for each shader stage marked dirty, gather the stage's 16-byte entries of
// each resource kind (the source's entries clamped to the limits, then the extra entries, then a default up to the
// limit) and upload them with 0x7100591c18; stage 9 gathers the per-entry scales. 0x71005a18e0 is the same with
// the entries of stages 3 and 4 transformed by a matrix (and those of stage 3 normalised on request).
// The declaration order of the loop index and the count (i, n) decides which of the two the register coalescer
// joins with the stage 9 copy loop's counter. Struct, field and callee names are placeholders after the address
// and offset, as in the generated units. Status: matching/README.md.
#include "misc/matrix_inverse.h"

extern "C" float sqrtf(float);

union Vec4_59f778 {
    float32x4_t v;
    float f[4];
    unsigned long l[2];
    int i[4];
    struct {
        float x, y, z, w;
    };
};

union Matrix5a18e0 {
    float m[4][4];
    XMMATRIX x;
};

struct Tex59f778 {
    Vec4_59f778 v[2];
};
struct Samp59f778 {
    Vec4_59f778 v[4];
};
struct Img59f778 {
    Vec4_59f778 v[6];
};
struct Buf59f778 {
    Vec4_59f778 v[3];
};

struct Source59f778 {
    unsigned int count[4];            // +0
    const Tex59f778* tex;             // +10
    const Samp59f778* samp;           // +18
    const Img59f778* img;             // +20
    const Buf59f778* buf;             // +28
};

struct Scales59f778 {
    unsigned char pad0[0xb0];
    const float* tex;                 // +b0
    const float* samp;                // +b8
    const float* img;                 // +c0
};

struct Device59f778 {
    unsigned char pad0[0xd0];
    Vec4_59f778 fill;                 // +d0
};

struct State59f778 {
    unsigned long enabled;            // +0
    unsigned long dirty;              // +8
};

struct Ctx59f778;

void set_591c18(State59f778* state, Ctx59f778* ctx, int stage, unsigned int count, const void* data);  // 0x7100591c18

static const Vec4_59f778 kUnitY = {{0.0f, 1.0f, 0.0f, 0.0f}};
static const Vec4_59f778 kUnitX = {{1.0f, 0.0f, 0.0f, 0.0f}};
static const Vec4_59f778 kZero = {};

struct Binder59f778 {
    unsigned char pad0[0x10];
    Ctx59f778* ctx;                   // +10
    unsigned char pad18[0x40];
    const Source59f778* source;       // +58
    const Scales59f778* scales;       // +60
    unsigned char pad68[0x10];
    State59f778* state;               // +78
    const Device59f778* device;       // +80
    unsigned char pad88[0x8];
    const long* pending;              // +90
    unsigned char pad98[0x58];
    unsigned int extra_count[4];      // +f0
    const Tex59f778* extra_tex;       // +100
    const Samp59f778* extra_samp;     // +108
    const Img59f778* extra_img;       // +110
    const Buf59f778* extra_buf;       // +118
    unsigned char pad120[0x84];
    unsigned char ends[4];            // +1a4

    void update(const unsigned int* limits);
    void update(const unsigned int* limits, const Matrix5a18e0* m, unsigned char normalize);
};

static inline unsigned int min_u(unsigned int a, unsigned int b) {
    return a > b ? b : a;
}

static inline bool stage_on(const State59f778* st, long any, int stage) {
    return (st->dirty >> stage & 1) && (any || (st->enabled >> stage & 1));
}

// 0x710059f778
void Binder59f778::update(const unsigned int* limits) {
    const Source59f778* src = source;
    State59f778* st = state;
    float32x4_t fill = device->fill.v;
    const Tex59f778* tex = src->tex;
    const Samp59f778* samp = src->samp;
    unsigned int c0 = min_u(src->count[0], limits[0]);
    unsigned int c1 = min_u(src->count[1], limits[1]);
    unsigned int c2 = min_u(src->count[2], limits[2]);
    unsigned int c3 = min_u(src->count[3], limits[3]);
    const Tex59f778* tex_x = extra_tex - c0;
    const Samp59f778* samp_x = extra_samp - c1;
    const Img59f778* img_x = extra_img - c2;
    const Buf59f778* buf_x = extra_buf - c3;
    unsigned int e0 = min_u(extra_count[0] + c0, limits[0]);
    unsigned int e1 = min_u(extra_count[1] + c1, limits[1]);
    unsigned int e2 = min_u(extra_count[2] + c2, limits[2]);
    unsigned int e3 = min_u(extra_count[3] + c3, limits[3]);
    const Img59f778* img = src->img;
    const Buf59f778* buf = src->buf;
    ends[0] = e0;
    ends[1] = e1;
    ends[2] = e2;
    ends[3] = e3;
    long any = *pending;
    Vec4_59f778 data[32];
    unsigned int i, n;

    if (stage_on(st, any, 3)) {
        n = 0;
        for (i = 0; i < c0; i++)
            data[n++] = tex[i].v[0];
        for (; i < e0; i++)
            data[n++] = tex_x[i].v[0];
        for (; i < limits[0]; i++)
            data[n++] = kUnitY;
        for (i = 0; i < c2; i++)
            data[n++] = img[i].v[1];
        for (; i < e2; i++)
            data[n++] = img_x[i].v[1];
        for (; i < limits[2]; i++)
            data[n++] = kUnitY;
        for (i = 0; i < c3; i++)
            data[n++] = buf[i].v[0];
        for (; i < e3; i++)
            data[n++] = buf_x[i].v[0];
        for (; i < limits[3]; i++)
            data[n++] = kUnitY;
        set_591c18(st, ctx, 3, n, data);
    }
    if (stage_on(st, any, 4)) {
        n = 0;
        for (i = 0; i < c1; i++)
            data[n++] = samp[i].v[0];
        for (; i < e1; i++)
            data[n++] = samp_x[i].v[0];
        for (; i < limits[1]; i++)
            data[n++].v = fill;
        for (i = 0; i < c2; i++)
            data[n++] = img[i].v[0];
        for (; i < e2; i++)
            data[n++] = img_x[i].v[0];
        for (; i < limits[2]; i++)
            data[n++].v = fill;
        set_591c18(st, ctx, 4, n, data);
    }
    if (stage_on(st, any, 5)) {
        n = 0;
        for (i = 0; i < c0; i++)
            data[n++] = tex[i].v[1];
        for (; i < e0; i++)
            data[n++] = tex_x[i].v[1];
        for (; i < limits[0]; i++)
            data[n++] = kZero;
        for (i = 0; i < c1; i++)
            data[n++] = samp[i].v[1];
        for (; i < e1; i++)
            data[n++] = samp_x[i].v[1];
        for (; i < limits[1]; i++)
            data[n++] = kZero;
        for (i = 0; i < c2; i++)
            data[n++] = img[i].v[2];
        for (; i < e2; i++)
            data[n++] = img_x[i].v[2];
        for (; i < limits[2]; i++)
            data[n++] = kZero;
        for (i = 0; i < c3; i++)
            data[n++] = buf[i].v[1];
        for (; i < e3; i++)
            data[n++] = buf_x[i].v[1];
        for (; i < limits[3]; i++)
            data[n++] = kZero;
        set_591c18(st, ctx, 5, n, data);
    }
    if (stage_on(st, any, 6)) {
        n = 0;
        for (i = 0; i < c1; i++)
            data[n++] = samp[i].v[2];
        for (; i < e1; i++)
            data[n++] = samp_x[i].v[2];
        for (; i < limits[1]; i++)
            data[n++] = kZero;
        for (i = 0; i < c2; i++)
            data[n++] = img[i].v[3];
        for (; i < e2; i++)
            data[n++] = img_x[i].v[3];
        for (; i < limits[2]; i++)
            data[n++] = kZero;
        for (i = 0; i < c3; i++)
            data[n++] = buf[i].v[2];
        for (; i < e3; i++)
            data[n++] = buf_x[i].v[2];
        for (; i < limits[3]; i++)
            data[n++] = kZero;
        set_591c18(st, ctx, 6, n, data);
    }
    if (stage_on(st, any, 7)) {
        n = 0;
        for (i = 0; i < c1; i++)
            data[n++] = samp[i].v[3];
        for (; i < e1; i++)
            data[n++] = samp_x[i].v[3];
        for (; i < limits[1]; i++)
            data[n++] = kUnitX;
        for (i = 0; i < c2; i++)
            data[n++] = img[i].v[4];
        for (; i < e2; i++)
            data[n++] = img_x[i].v[4];
        for (; i < limits[2]; i++)
            data[n++] = kUnitX;
        set_591c18(st, ctx, 7, n, data);
    }
    if (stage_on(st, any, 8)) {
        n = 0;
        for (i = 0; i < c2; i++)
            data[n++] = img[i].v[5];
        for (; i < e2; i++)
            data[n++] = img_x[i].v[5];
        for (; i < limits[2]; i++)
            data[n++] = kZero;
        set_591c18(st, ctx, 8, n, data);
    }
    if (stage_on(st, any, 9)) {
        const float* s0 = nullptr;
        const float* s1 = nullptr;
        const float* s2 = nullptr;
        if (const Scales59f778* sc = scales) {
            s0 = sc->tex;
            s1 = sc->samp;
            s2 = sc->img;
        }
        float* f = data[0].f;
        n = 0;
        for (i = 0; i < c0; i++)
            f[n++] = s0 ? s0[i] : 1.0f;
        for (; i < e0; i++)
            f[n++] = 1.0f;
        for (; i < limits[0]; i++)
            f[n++] = 1.0f;
        for (i = 0; i < c1; i++)
            f[n++] = s1 ? s1[i] : 1.0f;
        for (; i < e1; i++)
            f[n++] = 1.0f;
        for (; i < limits[1]; i++)
            f[n++] = 1.0f;
        for (i = 0; i < c2; i++)
            f[n++] = s2 ? s2[i] : 1.0f;
        for (; i < e2; i++)
            f[n++] = 1.0f;
        for (; i < limits[2]; i++)
            f[n++] = 1.0f;
        set_591c18(st, ctx, 9, (n + 3) / 4, data);
    }
}

static inline void transform3(Vec4_59f778* r, const Matrix5a18e0* m, const Vec4_59f778& v) {
    float x = m->m[0][0] * v.x + m->m[1][0] * v.y + m->m[2][0] * v.z;
    float y = v.x * m->m[0][1] + v.y * m->m[1][1] + v.z * m->m[2][1];
    float z = v.x * m->m[0][2] + v.y * m->m[1][2] + v.z * m->m[2][2];
    r->x = x;
    r->y = y;
    r->z = z;
    r->i[3] = v.i[3];
}

static inline void transform4(Vec4_59f778* r, const Matrix5a18e0* m, const Vec4_59f778& v) {
    r->v = XMVector4Transform(v.v, m->x);
}

// 0x71005a18e0
void Binder59f778::update(const unsigned int* limits, const Matrix5a18e0* m, unsigned char normalize) {
    const Source59f778* src = source;
    State59f778* st = state;
    float32x4_t fill = device->fill.v;
    const Tex59f778* tex = src->tex;
    const Samp59f778* samp = src->samp;
    const Img59f778* img = src->img;
    const Buf59f778* buf = src->buf;
    unsigned int c0 = min_u(src->count[0], limits[0]);
    unsigned int c1 = min_u(src->count[1], limits[1]);
    unsigned int c2 = min_u(src->count[2], limits[2]);
    unsigned int c3 = min_u(src->count[3], limits[3]);
    const Tex59f778* tex_x = extra_tex - c0;
    const Samp59f778* samp_x = extra_samp - c1;
    const Img59f778* img_x = extra_img - c2;
    const Buf59f778* buf_x = extra_buf - c3;
    unsigned int e0 = min_u(extra_count[0] + c0, limits[0]);
    unsigned int e1 = min_u(extra_count[1] + c1, limits[1]);
    unsigned int e2 = min_u(extra_count[2] + c2, limits[2]);
    unsigned int e3 = min_u(extra_count[3] + c3, limits[3]);
    long any = *pending;
    Vec4_59f778 data[32];
    unsigned int i, n;

    if (stage_on(st, any, 3)) {
        n = 0;
        for (i = 0; i < c0; i++)
            transform3(&data[n++], m, tex[i].v[0]);
        for (; i < e0; i++)
            transform3(&data[n++], m, tex_x[i].v[0]);
        for (; i < limits[0]; i++)
            data[n++] = kUnitY;
        for (i = 0; i < c2; i++)
            transform3(&data[n++], m, img[i].v[1]);
        for (; i < e2; i++)
            transform3(&data[n++], m, img_x[i].v[1]);
        for (; i < limits[2]; i++)
            data[n++] = kUnitY;
        for (i = 0; i < c3; i++)
            transform3(&data[n++], m, buf[i].v[0]);
        for (; i < e3; i++)
            transform3(&data[n++], m, buf_x[i].v[0]);
        for (; i < limits[3]; i++)
            data[n++] = kUnitY;
        if (normalize) {
            for (unsigned int k = 0; k < n; k++) {
                Vec4_59f778& e = data[k];
                float inv = 1.0f / sqrtf(e.x * e.x + e.y * e.y + e.z * e.z);
                e.x = e.x * inv;
                e.y = inv * e.y;
                e.z = inv * e.z;
            }
        }
        set_591c18(st, ctx, 3, n, data);
    }
    if (stage_on(st, any, 4)) {
        n = 0;
        for (i = 0; i < c1; i++)
            transform4(&data[n++], m, samp[i].v[0]);
        for (; i < e1; i++)
            transform4(&data[n++], m, samp_x[i].v[0]);
        for (; i < limits[1]; i++)
            data[n++].v = fill;
        for (i = 0; i < c2; i++)
            transform4(&data[n++], m, img[i].v[0]);
        for (; i < e2; i++)
            transform4(&data[n++], m, img_x[i].v[0]);
        for (; i < limits[2]; i++)
            data[n++].v = fill;
        set_591c18(st, ctx, 4, n, data);
    }
    if (stage_on(st, any, 5)) {
        n = 0;
        for (i = 0; i < c0; i++)
            data[n++] = tex[i].v[1];
        for (; i < e0; i++)
            data[n++] = tex_x[i].v[1];
        for (; i < limits[0]; i++)
            data[n++] = kZero;
        for (i = 0; i < c1; i++)
            data[n++] = samp[i].v[1];
        for (; i < e1; i++)
            data[n++] = samp_x[i].v[1];
        for (; i < limits[1]; i++)
            data[n++] = kZero;
        for (i = 0; i < c2; i++)
            data[n++] = img[i].v[2];
        for (; i < e2; i++)
            data[n++] = img_x[i].v[2];
        for (; i < limits[2]; i++)
            data[n++] = kZero;
        for (i = 0; i < c3; i++)
            data[n++] = buf[i].v[1];
        for (; i < e3; i++)
            data[n++] = buf_x[i].v[1];
        for (; i < limits[3]; i++)
            data[n++] = kZero;
        set_591c18(st, ctx, 5, n, data);
    }
    if (stage_on(st, any, 6)) {
        n = 0;
        for (i = 0; i < c1; i++)
            data[n++] = samp[i].v[2];
        for (; i < e1; i++)
            data[n++] = samp_x[i].v[2];
        for (; i < limits[1]; i++)
            data[n++] = kZero;
        for (i = 0; i < c2; i++)
            data[n++] = img[i].v[3];
        for (; i < e2; i++)
            data[n++] = img_x[i].v[3];
        for (; i < limits[2]; i++)
            data[n++] = kZero;
        for (i = 0; i < c3; i++)
            data[n++] = buf[i].v[2];
        for (; i < e3; i++)
            data[n++] = buf_x[i].v[2];
        for (; i < limits[3]; i++)
            data[n++] = kZero;
        set_591c18(st, ctx, 6, n, data);
    }
    if (stage_on(st, any, 7)) {
        n = 0;
        for (i = 0; i < c1; i++)
            data[n++] = samp[i].v[3];
        for (; i < e1; i++)
            data[n++] = samp_x[i].v[3];
        for (; i < limits[1]; i++)
            data[n++] = kUnitX;
        for (i = 0; i < c2; i++)
            data[n++] = img[i].v[4];
        for (; i < e2; i++)
            data[n++] = img_x[i].v[4];
        for (; i < limits[2]; i++)
            data[n++] = kUnitX;
        set_591c18(st, ctx, 7, n, data);
    }
    if (stage_on(st, any, 8)) {
        n = 0;
        for (i = 0; i < c2; i++)
            data[n++] = img[i].v[5];
        for (; i < e2; i++)
            data[n++] = img_x[i].v[5];
        for (; i < limits[2]; i++)
            data[n++] = kZero;
        set_591c18(st, ctx, 8, n, data);
    }
    if (stage_on(st, any, 9)) {
        const float* s0 = nullptr;
        const float* s1 = nullptr;
        const float* s2 = nullptr;
        if (const Scales59f778* sc = scales) {
            s0 = sc->tex;
            s1 = sc->samp;
            s2 = sc->img;
        }
        float* f = data[0].f;
        n = 0;
        for (i = 0; i < c0; i++)
            f[n++] = s0 ? s0[i] : 1.0f;
        for (; i < e0; i++)
            f[n++] = 1.0f;
        for (; i < limits[0]; i++)
            f[n++] = 1.0f;
        for (i = 0; i < c1; i++)
            f[n++] = s1 ? s1[i] : 1.0f;
        for (; i < e1; i++)
            f[n++] = 1.0f;
        for (; i < limits[1]; i++)
            f[n++] = 1.0f;
        for (i = 0; i < c2; i++)
            f[n++] = s2 ? s2[i] : 1.0f;
        for (; i < e2; i++)
            f[n++] = 1.0f;
        for (; i < limits[2]; i++)
            f[n++] = 1.0f;
        set_591c18(st, ctx, 9, (n + 3) / 4, data);
    }
}
