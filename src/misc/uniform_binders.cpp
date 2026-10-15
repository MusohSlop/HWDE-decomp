// Shader uniform binders around 0x71004b0000 (fifth session). A uniform handle packs its buffer slot in the top
// four bits and its byte offset in the low sixteen; writing one also marks the slot dirty. Struct, field and callee
// names are placeholders after the address and offset, as in the generated units. Status: matching/README.md.

namespace nn {
namespace os {
struct MutexType;
void LockMutex(MutexType* mutex);
void UnlockMutex(MutexType* mutex);
}  // namespace os
}  // namespace nn

extern "C" void* memcpy(void*, const void*, unsigned long);

// A self-relative pointer: an offset from the field's own address.
template <class T>
struct Rel4bc6b8 {
    int offset;
    T* get() { return reinterpret_cast<T*>(reinterpret_cast<char*>(this) + offset); }
    bool valid() { return offset != 0; }
};

struct Program4bc6b8;

struct Context4bc6b8 {
    unsigned char pad0[0x684];
    unsigned int dirty;               // +684
    unsigned char pad688[0x248];
    char* buffers[16];                // +8d0
};

void callee_52b938(Context4bc6b8*, Program4bc6b8*);        // 0x710052b938
void callee_52cc6c(Context4bc6b8*, int, int, void*);        // 0x710052cc6c
void callee_52ba34(Context4bc6b8*, int, int, void*);        // 0x710052ba34
void callee_5303c0(Context4bc6b8*, unsigned int, int, int);        // 0x71005303c0

// The setters are macros: the value is only evaluated once the handle is known to be set, so every rel-pointer
// field address is built in the block that loads it (the original's pre-indexed loads, with the other fields of
// the object addressed from the updated base). An inline function evaluates the value first and the shared field
// addresses get hoisted. SET_PARAM evaluates the value before the destination, SET_PARAM_AT after it.
#define SET_PARAM(ctx, h, v)                                                                                   \
    do {                                                                                                       \
        unsigned int handle_ = (h);                                                                            \
        if (handle_ != 0) {                                                                                    \
            *reinterpret_cast<unsigned int*>((ctx)->buffers[handle_ >> 28] + (handle_ & 0xffff)) = (v);       \
            (ctx)->dirty |= 1 << (handle_ >> 28);                                                              \
        }                                                                                                      \
    } while (0)
#define SET_PARAM_AT(ctx, h, v)                                                                                \
    do {                                                                                                       \
        unsigned int handle_ = (h);                                                                            \
        if (handle_ != 0) {                                                                                    \
            unsigned int* dst_ =                                                                               \
                reinterpret_cast<unsigned int*>((ctx)->buffers[handle_ >> 28] + (handle_ & 0xffff));          \
            *dst_ = (v);                                                                                       \
            (ctx)->dirty |= 1 << (handle_ >> 28);                                                              \
        }                                                                                                      \
    } while (0)
#define SET_PARAM_F(ctx, h, v)                                                                                 \
    do {                                                                                                       \
        unsigned int handle_ = (h);                                                                            \
        if (handle_ != 0) {                                                                                    \
            *reinterpret_cast<float*>((ctx)->buffers[handle_ >> 28] + (handle_ & 0xffff)) = (v);              \
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

struct Random4bc6b8 {
    unsigned char pad0[0x10];
    nn::os::MutexType* mutex() { return reinterpret_cast<nn::os::MutexType*>(pad0 + 0x10); }
};
extern Random4bc6b8* gRandom_c2cd10;
extern unsigned int gSeed_c2cd18;

static inline unsigned int random16_4bc6b8() {
    nn::os::LockMutex(gRandom_c2cd10->mutex());
    gSeed_c2cd18 = gSeed_c2cd18 * 0x10dcd + 1;
    unsigned int value = gSeed_c2cd18 >> 16;
    nn::os::UnlockMutex(gRandom_c2cd10->mutex());
    return value;
}

// 16-byte aligned: the local copy's first piece then gets its own 16-byte aligned stack slot (the original's
// frame), instead of the 8-byte gap next to the saved d8.
struct alignas(16) Layout4bc6b8 {
    unsigned int count;               // +0
    unsigned short kind;              // +4
    unsigned short pad6;              // +6
    unsigned long words[3];           // +8
};

struct Matrices4bc6b8 {
    unsigned char pad0[0xc];
    unsigned int field_c;             // +c
    float field_10[16];               // +10
    float field_50[16];               // +50
    float field_90[16];               // +90
};

struct Type4bc6b8 {
    int field_0;
    int type;                         // +4
};

struct Target4bc6b8 {
    unsigned char pad0[0x80];
    Rel4bc6b8<Type4bc6b8> desc;       // +80
};

struct Handles6_4bc6b8 {
    unsigned int field_0;             // +3c0
    unsigned int field_4;             // +3c4
    unsigned int field_8;             // +3c8
};

struct Handles7_4bc6b8 {
    unsigned int field_0;
    unsigned int field_4;
    unsigned int field_8;
    unsigned int field_c;
    unsigned int field_10;
    unsigned int field_14;
    unsigned int field_18;
};

struct Handles7b_4bc6b8 {
    unsigned int field_0;
    unsigned int field_4;
    unsigned int field_8;
    unsigned int field_c;
};

struct Handles8_4bc6b8 {
    unsigned int field_0;
    unsigned int field_4;
    unsigned int field_8;
    unsigned int pad_c[2];
    unsigned int field_14;
    unsigned int field_18;
    unsigned int field_1c;
    unsigned int field_20;
};

struct Handles8b_4bc6b8 {
    unsigned int field_0;
    unsigned int field_4;
};

struct Shader4bc6b8 {
    unsigned char pad0[0x20];
    Program4bc6b8* program6;          // +20
    Program4bc6b8* program7[28];      // +28
    Program4bc6b8* program8[28];      // +108
    unsigned char pad1e8[0x1d8];
    Handles6_4bc6b8 h6;               // +3c0
    Handles7_4bc6b8 h7[40];           // +3cc
    Handles7b_4bc6b8 h7b[14];         // +82c
    Handles8_4bc6b8 h8[56];           // +90c
    Handles8b_4bc6b8 h8b[8];          // +10ec
};

struct Pass4bc6b8 {
    unsigned char pad0[0x4];
    int index;                        // +4
    unsigned int flags;               // +8
    unsigned int size;                // +c
    unsigned char pad10[0x4];
    Rel4bc6b8<Layout4bc6b8> layout;   // +14
    Rel4bc6b8<char> base;             // +18
    unsigned char pad1c[0x70];
    int limit;                        // +8c
    unsigned char pad90[0xc0];
    int start;                        // +150
    int end;                          // +154
    unsigned char pad158[0x60];
    Shader4bc6b8* shader;             // +1b8
    void* texture;                    // +1c0
    unsigned char pad1c8[0x18];
    Rel4bc6b8<Target4bc6b8> target;   // +1e0
    Rel4bc6b8<char> depth;            // +1e4
    unsigned char pad1e8[0x8];
    unsigned int time;                // +1f0
    unsigned int phase;               // +1f4
    Rel4bc6b8<Matrices4bc6b8> matrices; // +1f8
    unsigned char pad1fc[0x4];
    Rel4bc6b8<Pass4bc6b8> other;      // +200
    unsigned char pad204[0x14];
    unsigned int extra;               // +218

    int offset_of(void* p) { return static_cast<int>(reinterpret_cast<char*>(p) - base.get()); }
    int bind(Context4bc6b8* ctx, int pass, float value);
};

// 0x71004bc6b8: binds the program of PASS (6, 7 or 8) and sets its uniforms; returns 0 when nothing was bound.
// The handle tables are indexed as "shader->table + index" so the shader is loaded before the index (Clang 3.9
// emits an array subscript's index first).
int Pass4bc6b8::bind(Context4bc6b8* ctx, int pass, float value) {
    if (shader == nullptr) {
        return 1;
    }
    if (!(other.get()->flags & 0x200)) {
        return 0;
    }
    int result;
    if (pass == 6) {
        if (flags & 0x800) {
            callee_52b938(ctx, shader->program6);
            SET_PARAM(ctx, shader->h6.field_0, size);
            SET_PARAM(ctx, shader->h6.field_4, layout.get()->count * size + 0x10);
            unsigned int handle = shader->h6.field_8;
            if (handle != 0) {
                Layout4bc6b8 copy = *layout.get();
                copy.pad6 = 0;
                *reinterpret_cast<Layout4bc6b8*>(ctx->buffers[handle >> 28] + (handle & 0xffff)) = copy;
                ctx->dirty |= 1 << (handle >> 28);
            }
            unsigned int blocks = (size + 0x3f) >> 6;
            callee_52cc6c(ctx, 5, 0, texture);
            result = 1;
            callee_5303c0(ctx, blocks, 1, 1);
            callee_52cc6c(ctx, 5, 0, nullptr);
            flags &= ~0x800;
        } else {
            result = 0;
        }
    } else if (pass == 7) {
        if (!target.valid() || !depth.valid() || target.get()->desc.get()->type == 0xb || time == 0) {
            result = 0;
        } else {
            callee_52b938(ctx, *(shader->program7 + index));
            SET_PARAM(ctx, (shader->h7 + index)->field_0, size);
            SET_PARAM_AT(ctx, (shader->h7 + index)->field_4, time);
            SET_PARAM_AT(ctx, (shader->h7 + index)->field_8, phase);
            SET_PARAM(ctx, (shader->h7 + index)->field_c, offset_of(target.get()));
            SET_PARAM(ctx, (shader->h7 + index)->field_10, offset_of(depth.get()));
            SET_PARAM(ctx, (shader->h7 + index)->field_14, offset_of(this));
            SET_PARAM(ctx, (shader->h7 + index)->field_18, random16_4bc6b8());
            SET_PARAM(ctx, (shader->h7b + index)->field_0, other.get()->size);
            SET_PARAM(ctx, (shader->h7b + index)->field_4, offset_of(other.get()));
            SET_PARAM(ctx, (shader->h7b + index)->field_8, layout.get()->count * size + 0x10);
            SET_PARAM_AT(ctx, (shader->h7b + index)->field_c, extra);
            unsigned int blocks = (time + 0x3f) >> 6;
            callee_52cc6c(ctx, 5, 0, texture);
            result = 1;
            callee_52ba34(ctx, 5, 1, other.get()->texture);
            callee_5303c0(ctx, blocks, 1, 1);
            callee_52cc6c(ctx, 5, 0, nullptr);
            callee_52ba34(ctx, 5, 1, nullptr);
            unsigned int total = phase + time;
            unsigned int count = other.get()->size;
            time = 0;
            phase = total % count;
        }
    } else if (pass == 8) {
        callee_52b938(ctx, *(shader->program8 + index));
        SET_PARAM_AT(ctx, (shader->h8 + index)->field_0, size);
        SET_PARAM_F(ctx, (shader->h8 + index)->field_4, value);
        SET_PARAM(ctx, (shader->h8 + index)->field_8, offset_of(this));
        if (limit >= (start < limit ? end : 0)) {
            SET_PARAM_MAT(ctx, (shader->h8 + index)->field_14, matrices.get()->field_10);
            SET_PARAM_MAT(ctx, (shader->h8 + index)->field_18, matrices.get()->field_50);
            SET_PARAM_MAT(ctx, (shader->h8 + index)->field_1c, matrices.get()->field_90);
            SET_PARAM(ctx, (shader->h8 + index)->field_20, matrices.get()->field_c);
        }
        SET_PARAM(ctx, (shader->h8b + index)->field_0, other.get()->size);
        SET_PARAM(ctx, (shader->h8b + index)->field_4, offset_of(other.get()));
        unsigned int blocks = (size + 0x3f) >> 6;
        callee_52cc6c(ctx, 5, 0, texture);
        result = 1;
        callee_52ba34(ctx, 5, 1, other.get()->texture);
        callee_5303c0(ctx, blocks, 1, 1);
        callee_52cc6c(ctx, 5, 0, nullptr);
        callee_52ba34(ctx, 5, 1, nullptr);
    } else {
        result = 0;
    }
    callee_52b938(ctx, nullptr);
    return result;
}
