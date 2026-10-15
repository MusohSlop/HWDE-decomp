// Fifth session, in progress: 0x71004ce8e0 (2,104 bytes), a shader program's binding resolve: binds the uniform and
// sampler blocks of its four stages, its geometry stage and up to five extra stages at running offsets (twice,
// through one inline helper), then looks every binding's uniform and sampler name up stage by stage and sets a bit
// in a 128-bit mask for each one that is not found. 2,112 bytes here, 23 instructions off when registers are
// abstracted. Settled: the call sequence, the helper inlined (always_inline), the lookup chains, the sampler base
// read between the uniform and the sampler offset sums. Still off: register allocation and spill slots (stage 0
// and one offset stay in registers in the original; 8 bytes of reloads here), which depend on the order and the
// lifetimes of the locals: a topotry candidate.
// irsearch --loads-free (instruction moves, loads free among themselves) reaches 0 off abstracted (same size and
// schedule) with 36 register diffs left, two swapped pairs of callee-saved registers (s0/f1 and s2/f2). The order
// (build/s5 scratch, minimized with --minimize --strict): main read before the binding count, the stages, u1, f1,
// u2, then the geometry pointer; s2's sampler count, the extra sampler base and s1's sampler count read before s2's
// uniform count; the extra uniform base before f2. Not yet a readable source order.
// Maps for tools/s5/sbs.py (name=address): _ZN9Sub4ce8e05readyEv=0x71005998cc
//   _Z20bind_uniforms_5a4848P11Stage4ce8e0Pvib=0x71005a4848 _Z20bind_samplers_5a4b00P11Stage4ce8e0Pvib=0x71005a4b00
//   _Z20bind_uniforms_5a86c8P11Stage4ce8e0Pvib=0x71005a86c8 _Z20bind_samplers_5a88c4P11Stage4ce8e0Pvib=0x71005a88c4
//   _Z19find_uniform_5a5664P11Stage4ce8e0PviS1_=0x71005a5664
//   _Z19find_sampler_5a58a8P11Stage4ce8e0PviS1_=0x71005a58a8
//   _Z19find_uniform_5a93bcP11Stage4ce8e0PviS1_=0x71005a93bc
//   _Z19find_sampler_5a9648P11Stage4ce8e0PviS1_=0x71005a9648 _Z15init_buf_58fac4Pv=0x710058fac4
// with --name _ZN13Program4ce8e07resolveEv.

struct Stage4ce8e0 {
    unsigned char pad0[0x58];
    int uniform_count;                // +58
    int sampler_count;                // +5c
};

struct Stages4ce8e0 {
    unsigned char pad0[0x68];
    Stage4ce8e0* stages[4];           // +68
    Stage4ce8e0* geometry;            // +88
};

struct Shader4ce8e0 {
    unsigned char pad0[0x6c];
    int binding_count;                // +6c
};

struct Binding4ce8e0 {
    short uniform;
    short sampler;
    unsigned char pad4[0xc];
};

struct Sub4ce8e0 {
    unsigned char ready();        // 0x71005998cc
};

void bind_uniforms_5a4848(Stage4ce8e0* stage, void* list, int base, bool flag);        // 0x71005a4848
void bind_samplers_5a4b00(Stage4ce8e0* stage, void* list, int base, bool flag);        // 0x71005a4b00
void bind_uniforms_5a86c8(Stage4ce8e0* stage, void* list, int base, bool flag);        // 0x71005a86c8
void bind_samplers_5a88c4(Stage4ce8e0* stage, void* list, int base, bool flag);        // 0x71005a88c4
int find_uniform_5a5664(Stage4ce8e0* stage, void* name, int base, void* buf);        // 0x71005a5664
int find_sampler_5a58a8(Stage4ce8e0* stage, void* name, int base, void* buf);        // 0x71005a58a8
int find_uniform_5a93bc(Stage4ce8e0* stage, void* name, int base, void* buf);        // 0x71005a93bc
int find_sampler_5a9648(Stage4ce8e0* stage, void* name, int base, void* buf);        // 0x71005a9648
void init_buf_58fac4(void* buf);        // 0x710058fac4

struct Program4ce8e0 {
    unsigned char pad0[0x20];
    Sub4ce8e0 sub;                    // +20
    unsigned char pad21[0x1f];
    Shader4ce8e0* shader;             // +40
    Stages4ce8e0* main;               // +48
    Stage4ce8e0* extra[5];            // +50
    void** uniform_names;             // +78
    void** sampler_names;             // +80
    unsigned char pad88[0x1218];
    Binding4ce8e0* bindings;          // +12a0
    unsigned char pad12a8[0x14];
    unsigned char flags;              // +12bc
    unsigned char pad12bd[0x3];
    unsigned int missing_uniforms[4]; // +12c0
    unsigned int missing_samplers[4]; // +12d0
    unsigned char pad12e0[0x20];
    int extra_uniform_base;           // +1300
    int extra_sampler_base;           // +1304

    __attribute__((always_inline)) void bind_all(Stage4ce8e0* s0, Stage4ce8e0* s1, Stage4ce8e0* s2, Stage4ce8e0* s3, Stage4ce8e0* g, int u1, int u2,
                  int u3, int u4, int f1, int f2, int f3, int f4, int u, int f) {
        bind_uniforms_5a4848(s0, nullptr, 0, false);
        bind_samplers_5a4b00(s0, nullptr, 0, false);
        bind_uniforms_5a4848(s1, nullptr, u1, false);
        bind_samplers_5a4b00(s1, nullptr, f1, false);
        bind_uniforms_5a4848(s2, nullptr, u2, false);
        bind_samplers_5a4b00(s2, nullptr, f2, false);
        bind_uniforms_5a4848(s3, nullptr, u3, false);
        bind_samplers_5a4b00(s3, nullptr, f3, false);
        bind_uniforms_5a86c8(g, nullptr, u4, false);
        bind_samplers_5a88c4(g, nullptr, f4, false);
        bind_uniforms_5a4848(extra[0], nullptr, u, false);
        bind_samplers_5a4b00(extra[0], nullptr, f, false);
        u += extra[0]->uniform_count;
        f += extra[0]->sampler_count;
        if (extra[1] != nullptr) {
            bind_uniforms_5a4848(extra[1], nullptr, u, false);
            bind_samplers_5a4b00(extra[1], nullptr, f, false);
            u += extra[1]->uniform_count;
            f += extra[1]->sampler_count;
        }
        if (extra[2] != nullptr) {
            bind_uniforms_5a4848(extra[2], nullptr, u, false);
            bind_samplers_5a4b00(extra[2], nullptr, f, false);
            u += extra[2]->uniform_count;
            f += extra[2]->sampler_count;
        }
        if (extra[3] != nullptr) {
            bind_uniforms_5a4848(extra[3], nullptr, u, false);
            bind_samplers_5a4b00(extra[3], nullptr, f, false);
            u += extra[3]->uniform_count;
            f += extra[3]->sampler_count;
        }
        if (extra[4] != nullptr) {
            bind_uniforms_5a4848(extra[4], nullptr, u, false);
            bind_samplers_5a4b00(extra[4], nullptr, f, false);
        }
    }
    void resolve();
};

// 0x71004ce8e0
void Program4ce8e0::resolve() {
    for (int k = 0; k < 4; k++) {
        missing_uniforms[k] = 0;
    }
    for (int k = 0; k < 4; k++) {
        missing_samplers[k] = 0;
    }
    if (!(flags >> 4 & 1) || !sub.ready()) {
        return;
    }
    int count = shader->binding_count;
    Stage4ce8e0* g = main->geometry;
    Stage4ce8e0* s0 = main->stages[0];
    Stage4ce8e0* s1 = main->stages[1];
    Stage4ce8e0* s2 = main->stages[2];
    Stage4ce8e0* s3 = main->stages[3];
    int u1 = s0->uniform_count;
    int f1 = s0->sampler_count;
    int u2 = u1 + s1->uniform_count;
    int u3 = u2 + s2->uniform_count;
    int u4 = u3 + s3->uniform_count;
    int fb = extra_sampler_base;
    int f2 = f1 + s1->sampler_count;
    int f3 = f2 + s2->sampler_count;
    int f4 = f3 + s3->sampler_count;
    int ub = extra_uniform_base;
    bind_all(s0, s1, s2, s3, g, u1, u2, u3, u4, f1, f2, f3, f4, ub, fb);
    unsigned char ubuf[256];
    init_buf_58fac4(ubuf);
    for (unsigned i = 0; i < static_cast<unsigned>(count); i++) {
        long idx = bindings[i].uniform;
        if (idx >= 0) {
            void* name = uniform_names[idx];
            if (find_uniform_5a5664(s0, name, 0, ubuf) >= 0 || find_uniform_5a5664(s1, name, u1, ubuf) >= 0 ||
                find_uniform_5a5664(s2, name, u2, ubuf) >= 0 || find_uniform_5a5664(s3, name, u3, ubuf) >= 0 ||
                find_uniform_5a93bc(g, name, u4, ubuf) >= 0 || find_uniform_5a5664(extra[0], name, ub, ubuf) >= 0) {
                continue;
            }
            int u = extra[0]->uniform_count + ub;
            if (extra[1] != nullptr) {
                if (find_uniform_5a5664(extra[1], name, u, ubuf) >= 0) {
                    continue;
                }
                u += extra[1]->uniform_count;
            }
            if (extra[2] != nullptr) {
                if (find_uniform_5a5664(extra[2], name, u, ubuf) >= 0) {
                    continue;
                }
                u += extra[2]->uniform_count;
            }
            if (extra[3] != nullptr) {
                if (find_uniform_5a5664(extra[3], name, u, ubuf) >= 0) {
                    continue;
                }
                u += extra[3]->uniform_count;
            }
            if (extra[4] != nullptr && find_uniform_5a5664(extra[4], name, u, ubuf) >= 0) {
                continue;
            }
        }
        missing_uniforms[i >> 5] |= 1u << (i & 0x1f);
    }
    unsigned char sbuf[256];
    init_buf_58fac4(sbuf);
    for (unsigned i = 0; i < static_cast<unsigned>(count); i++) {
        long idx = bindings[i].sampler;
        if (idx >= 0) {
            void* name = sampler_names[idx];
            if (find_sampler_5a58a8(s0, name, 0, sbuf) >= 0 || find_sampler_5a58a8(s1, name, f1, sbuf) >= 0 ||
                find_sampler_5a58a8(s2, name, f2, sbuf) >= 0 || find_sampler_5a58a8(s3, name, f3, sbuf) >= 0 ||
                find_sampler_5a9648(g, name, f4, sbuf) >= 0 ||
                find_sampler_5a58a8(extra[0], name, fb, sbuf) >= 0) {
                continue;
            }
            int f = extra[0]->sampler_count + fb;
            if (extra[1] != nullptr) {
                if (find_sampler_5a58a8(extra[1], name, f, sbuf) >= 0) {
                    continue;
                }
                f += extra[1]->sampler_count;
            }
            if (extra[2] != nullptr) {
                if (find_sampler_5a58a8(extra[2], name, f, sbuf) >= 0) {
                    continue;
                }
                f += extra[2]->sampler_count;
            }
            if (extra[3] != nullptr) {
                if (find_sampler_5a58a8(extra[3], name, f, sbuf) >= 0) {
                    continue;
                }
                f += extra[3]->sampler_count;
            }
            if (extra[4] != nullptr && find_sampler_5a58a8(extra[4], name, f, sbuf) >= 0) {
                continue;
            }
        }
        missing_samplers[i >> 5] |= 1u << (i & 0x1f);
    }
    bind_all(s0, s1, s2, s3, g, u1, u2, u3, u4, f1, f2, f3, f4, ub, fb);
}
