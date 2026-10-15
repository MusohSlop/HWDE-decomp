// Fifth session, parked: 0x71004abdcc (2,256 bytes), a uniform binder of the 4bc6b8 family (misc/uniform_binders.cpp
// has its setter macros and notes). This draft compiles to 2,252 bytes, 110 instructions off when registers are
// abstracted. Solved here: the handle table offset, the light directions kept in memory as floats (scalar loads and
// stores, then one q reload; four q constants from .rodata.cst16), the clamp as "x <= lo ? lo : x" (the other forms
// become fmaxnm), the stack order (colours, reflected colours, directions), count * size. Still off: the scheduling
// of the light loop (the original converts the red channel right after clamping it and stores it with a
// register-offset str, then pairs green and blue; the 3x3 transform's products come in another order), the camera
// rows loaded before the loop in another order, the two half-size floats stored with two str (not stp), and d8/d9
// swapped for width and height.

typedef float Vec4f __attribute__((ext_vector_type(4)));

extern "C" void* memcpy(void*, const void*, unsigned long);

template <class T>
struct Rel4abdcc {
    int offset;
    T* get() { return reinterpret_cast<T*>(reinterpret_cast<char*>(this) + offset); }
};

struct Program4abdcc;

struct Context4abdcc {
    unsigned char pad0[0x684];
    unsigned int dirty;               // +684
    unsigned char pad688[0x248];
    char* buffers[16];                // +8d0
};

void callee_52b938(Context4abdcc*, Program4abdcc*);        // 0x710052b938
void callee_52cc6c(Context4abdcc*, int, int, void*);        // 0x710052cc6c
void callee_5303c0(Context4abdcc*, unsigned int, int, int);        // 0x71005303c0

#define SET_PARAM(ctx, h, v)                                                                                   \
    do {                                                                                                       \
        unsigned int handle_ = (h);                                                                            \
        if (handle_ != 0) {                                                                                    \
            *reinterpret_cast<unsigned int*>((ctx)->buffers[handle_ >> 28] + (handle_ & 0xffff)) = (v);       \
            (ctx)->dirty |= 1 << (handle_ >> 28);                                                              \
        }                                                                                                      \
    } while (0)
#define SET_PARAM_MAT(ctx, h, v)                                                                               \
    do {                                                                                                       \
        unsigned int handle_ = (h);                                                                            \
        if (handle_ != 0) {                                                                                    \
            const void* src_ = (v);                                                                            \
            memcpy((ctx)->buffers[handle_ >> 28] + (handle_ & 0xffff), src_, 0x40);                            \
            (ctx)->dirty |= 1 << (handle_ >> 28);                                                              \
        }                                                                                                      \
    } while (0)

extern Vec4f gOne_c21ee8;

static inline float clamp4abdcc(float x, float lo, float hi) {
    float r = x <= lo ? lo : x;
    if (hi <= x) {
        r = hi;
    }
    return r;
}

struct Color4abdcc {
    unsigned int r, g, b;
};

struct Color4_4abdcc {
    Color4abdcc rgb;
    unsigned int a;
};

struct Matrix4abdcc {
    float m[16];
};

struct Layout4abdcc {
    unsigned int count;               // +0
    unsigned char pad4[0x26];
    unsigned short kind;              // +2a
};

struct Camera4abdcc {
    unsigned char pad0[0x80];
    float m[4][4];                    // +80
    unsigned char padc0[0xb0];
    float field_170;                  // +170
    unsigned char pad174[0x10];
    float field_184;                  // +184
    unsigned char pad188[0x28];
    float proj[16];                   // +1b0
};

struct Handles4abdcc {
    unsigned int field_0;             // +1188
    unsigned int field_4;             // +118c
    unsigned int field_8;             // +1190
    unsigned int field_c;             // +1194
    unsigned int field_10;            // +1198
    unsigned int field_14;            // +119c
    unsigned int field_18;            // +11a0
    unsigned int field_1c;            // +11a4
    unsigned int field_20;            // +11a8
    unsigned int field_24;            // +11ac
};

struct Shader4abdcc {
    unsigned char pad0[0x10];
    Context4abdcc* ctx;               // +10
    unsigned char pad18[0x2c0];
    Program4abdcc* programs[0x1d6];   // +2d8
    Handles4abdcc h[4];               // +1188
};

struct Pass4abdcc {
    unsigned char pad0[0x4];
    int index;                        // +4
    unsigned int flags;               // +8
    unsigned int size;                // +c
    unsigned char pad10[0x4];
    Rel4abdcc<Layout4abdcc> layout;   // +14
    unsigned char pad18[0x1a0];
    Shader4abdcc* shader;             // +1b8
    void* field_1c0;                  // +1c0
    void* field_1c8;                  // +1c8

    void bind(Camera4abdcc* camera);
};

// 0x71004abdcc
void Pass4abdcc::bind(Camera4abdcc* camera) {
    if (shader == nullptr) {
        return;
    }
    Context4abdcc* ctx = shader->ctx;
    float width = camera->field_170;
    float height = camera->field_184;
    callee_52b938(ctx, *(shader->programs + index));
    SET_PARAM(ctx, (shader->h + index)->field_0, size);
    SET_PARAM(ctx, (shader->h + index)->field_4, layout.get()->count * size);
    SET_PARAM_MAT(ctx, (shader->h + index)->field_8, camera->proj);
    unsigned int handle = (shader->h + index)->field_c;
    if (handle != 0) {
        float half[2] = {width * 0.5f, height * 0.5f};
        memcpy(ctx->buffers[handle >> 28] + (handle & 0xffff), half, 8);
        ctx->dirty |= 1 << (handle >> 28);
    }
    handle = (shader->h + index)->field_10;
    if (handle != 0) {
        float (*m)[4] = camera->m;
        Matrix4abdcc inv;
        inv.m[0] = m[0][0];
        inv.m[1] = m[1][0];
        inv.m[2] = m[2][0];
        inv.m[3] = 0.0f;
        inv.m[4] = m[0][1];
        inv.m[5] = m[1][1];
        inv.m[6] = m[2][1];
        inv.m[7] = 0.0f;
        inv.m[8] = m[0][2];
        inv.m[9] = m[1][2];
        inv.m[10] = m[2][2];
        inv.m[11] = 0.0f;
        inv.m[12] = -(m[0][0] * m[3][0] + m[0][1] * m[3][1] + m[0][2] * m[3][2]);
        inv.m[13] = -(m[1][0] * m[3][0] + m[1][1] * m[3][1] + m[1][2] * m[3][2]);
        inv.m[14] = -(m[2][0] * m[3][0] + m[2][1] * m[3][1] + m[2][2] * m[3][2]);
        inv.m[15] = 1.0f;
        *reinterpret_cast<Matrix4abdcc*>(ctx->buffers[handle >> 28] + (handle & 0xffff)) = inv;
        ctx->dirty |= 1 << (handle >> 28);
    }
    if (static_cast<unsigned int>(index) <= 1) {
        unsigned int bit;
        switch (layout.get()->kind) {
        case 0x11:
        case 0x12:
        case 0x14:
        case 0x15:
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x27: {
            Handles4abdcc* entry = shader->h + index;
            unsigned int h1 = entry->field_1c;
            if (h1 == 0) {
                goto done;
            }
            unsigned int h2 = entry->field_20;
            if (h2 == 0) {
                goto done;
            }
            Color4abdcc colors[4];
            Color4abdcc reflected[4];
            Vec4f dirs[4];
            dirs[0] = (Vec4f){-0.70710677f, 0.70710677f, 0.6f, 0.0f};
            dirs[1] = (Vec4f){-0.70710677f, -0.70710677f, 0.6f, 0.0f};
            dirs[2] = (Vec4f){0.70710677f, 0.70710677f, 0.6f, 0.0f};
            dirs[3] = (Vec4f){0.70710677f, -0.70710677f, 0.6f, 0.0f};
            float (*m)[4] = camera->m;
            Vec4f axis = {m[0][2], m[1][2], m[2][2], 0.0f};
            for (int i = 0; i < 4; i++) {
                float* p = reinterpret_cast<float*>(&dirs[i]);
                float x = p[0];
                float y = p[1];
                float z = p[2];
                float nx = m[0][0] * x + m[0][1] * y + m[0][2] * z;
                float ny = m[1][0] * x + m[1][1] * y + m[1][2] * z;
                float nz = m[2][0] * x + m[2][1] * y + m[2][2] * z;
                p[0] = nx;
                p[1] = ny;
                p[2] = nz;
                float k = (m[0][2] * nx + m[1][2] * ny + nz * m[2][2]) * -2.0f;
                Vec4f d = dirs[i];
                Vec4f c = (d + gOne_c21ee8) * 127.5f;
                p[0] = clamp4abdcc(c.x, 0.0f, 255.0f);
                p[1] = clamp4abdcc(c.y, 0.0f, 255.0f);
                p[2] = clamp4abdcc(c.z, 0.0f, 255.0f);
                p[3] = clamp4abdcc(c.w, 0.0f, 255.0f);
                colors[i].r = static_cast<unsigned int>(p[0]);
                colors[i].g = static_cast<unsigned int>(p[1]);
                colors[i].b = static_cast<unsigned int>(p[2]);
                Vec4f r = (d + axis * k + gOne_c21ee8) * 127.5f;
                reflected[i].r = static_cast<unsigned int>(clamp4abdcc(r.x, 0.0f, 255.0f));
                reflected[i].g = static_cast<unsigned int>(clamp4abdcc(r.y, 0.0f, 255.0f));
                reflected[i].b = static_cast<unsigned int>(clamp4abdcc(r.z, 0.0f, 255.0f));
            }
            Color4_4abdcc* dst = reinterpret_cast<Color4_4abdcc*>(ctx->buffers[h1 >> 28] + (h1 & 0xffff));
            for (int i = 0; i < 4; i++) {
                dst[i].rgb = colors[i];
            }
            ctx->dirty |= 1 << (h1 >> 28);
            dst = reinterpret_cast<Color4_4abdcc*>(ctx->buffers[h2 >> 28] + (h2 & 0xffff));
            for (int i = 0; i < 4; i++) {
                dst[i].rgb = reflected[i];
            }
            bit = 1 << (h2 >> 28);
            break;
        }
        case 0x17:
        case 0x18:
        case 0x19: {
            unsigned int h = (shader->h + index)->field_24;
            if (h == 0) {
                goto done;
            }
            float (*m)[4] = camera->m;
            Vec4f a = {m[0][0], m[1][0], m[2][0], 0.0f};
            Vec4f b = {m[0][1], m[1][1], m[2][1], 0.0f};
            Vec4f ca = (a + gOne_c21ee8) * 127.5f;
            Vec4f cb = (gOne_c21ee8 - b) * 127.5f;
            unsigned int* dst = reinterpret_cast<unsigned int*>(ctx->buffers[h >> 28] + (h & 0xffff));
            dst[0] = static_cast<unsigned int>(clamp4abdcc(ca.x, 0.0f, 255.0f));
            dst[1] = static_cast<unsigned int>(clamp4abdcc(ca.y, 0.0f, 255.0f));
            dst[2] = static_cast<unsigned int>(clamp4abdcc(ca.z, 0.0f, 255.0f));
            dst[4] = static_cast<unsigned int>(clamp4abdcc(cb.x, 0.0f, 255.0f));
            dst[5] = static_cast<unsigned int>(clamp4abdcc(cb.y, 0.0f, 255.0f));
            dst[6] = static_cast<unsigned int>(clamp4abdcc(cb.z, 0.0f, 255.0f));
            bit = 1 << (h >> 28);
            break;
        }
        case 0x2a:
        case 0x2b:
        case 0x2c:
        case 0x2d:
        case 0x2e:
        case 0x2f: {
            unsigned int h = (shader->h + index)->field_18;
            if (h != 0) {
                float (*m)[4] = camera->m;
                Vec4f a = {m[0][0], m[1][0], m[2][0], 0.0f};
                Vec4f ca = (a + gOne_c21ee8) * 127.5f;
                unsigned int* dst = reinterpret_cast<unsigned int*>(ctx->buffers[h >> 28] + (h & 0xffff));
                dst[0] = static_cast<unsigned int>(clamp4abdcc(ca.x, 0.0f, 255.0f));
                dst[1] = static_cast<unsigned int>(clamp4abdcc(ca.y, 0.0f, 255.0f));
                dst[2] = static_cast<unsigned int>(clamp4abdcc(ca.z, 0.0f, 255.0f));
                ctx->dirty |= 1 << (h >> 28);
            }
        }
        case 2:
        case 5: {
            unsigned int h = (shader->h + index)->field_14;
            if (h == 0) {
                goto done;
            }
            float (*m)[4] = camera->m;
            Vec4f a = {m[0][2], m[1][2], m[2][2], 0.0f};
            Vec4f ca = (a + gOne_c21ee8) * 127.5f;
            unsigned int* dst = reinterpret_cast<unsigned int*>(ctx->buffers[h >> 28] + (h & 0xffff));
            dst[0] = static_cast<unsigned int>(clamp4abdcc(ca.x, 0.0f, 255.0f));
            dst[1] = static_cast<unsigned int>(clamp4abdcc(ca.y, 0.0f, 255.0f));
            dst[2] = static_cast<unsigned int>(clamp4abdcc(ca.z, 0.0f, 255.0f));
            bit = 1 << (h >> 28);
            break;
        }
        default:
            goto done;
        }
        ctx->dirty |= bit;
    }
done:
    unsigned int blocks = (size + 0x1f) >> 5;
    callee_52cc6c(ctx, 5, 0, field_1c8);
    callee_52cc6c(ctx, 5, 1, field_1c0);
    callee_5303c0(ctx, blocks, 1, 1);
    callee_52cc6c(ctx, 5, 0, nullptr);
    callee_52cc6c(ctx, 5, 1, nullptr);
    callee_52b938(ctx, nullptr);
}
