// Fifth session, parked: family (d) triple, 0x71003d7708 (and 0x71003d887c, 0x71003d98f8: the same with the callees
// 0x71003d8388/0x71003d86ac and 0x71003d94fc/0x71003d9820), 1,220 bytes each; 1,204 bytes here, 58 instructions
// off abstracted. A render batch: items (16 bytes: part, material) walked forward or backward (a byte flag), runs
// of items that share a shader (the shader table indexed by (part->a + mat->b) * stride + base) bound once
// (virtual unbind/bind), drawn per pass (passes, begin(p), end_pass, end) with 0x710003bad0 and 0x710003bdf4,
// or per item when the shader's byte at +0x1298 has bit 0; null shaders and failed binds skip the run; the
// renderer state saved at the start is restored by a tail call to 0x710052ac40. Settled: the flag is an unsigned
// char, the step is written at each advance (LICM puts its own test of the flag after the empty-range check),
// stop is selected before begin with an eq test. Still off: the original reloads the item's material pointer for
// the shader lookup at the loop head (ldp of both pointers after the null test; ours reuses the tested load), the
// layout of the duplicated scan loops, and the spills of stop and step.
// Maps: setup_3bad0=0x710003bad0 submit_3bdf4=0x710003bdf4 restore_52ac40=0x710052ac40 (build/s5/fd/sb.ps1).
struct Part3d7708 {
    unsigned char pad0[0x4];
    short a;                          // +4
};
struct Mat3d7708 {
    unsigned char pad0[0x2a];
    short b;                          // +2a
};

struct Item3d7708 {
    Part3d7708* part;                 // +0
    Mat3d7708* mat;                   // +8
};

struct Ctx3d7708 {
    unsigned char pad0[0x18];
    unsigned long z[6];               // +18
    int pass;                         // +48
};

struct Shader3d7708 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual unsigned char bind();               // +58
    virtual void unbind();                      // +60
    virtual unsigned int passes();              // +68
    virtual void end();                         // +70
    virtual unsigned char begin(unsigned int p); // +78
    virtual void end_pass();                    // +80
};

struct Renderer3d7708 {
    unsigned char pad0[0x88];
    int state;                        // +88
};

void restore_52ac40(Renderer3d7708* r, int state);  // 0x710052ac40

struct Batch3d7708 {
    unsigned char pad0[0x28];
    Renderer3d7708* renderer;         // +28
    unsigned char pad30[0xc10];
    Shader3d7708* current;            // +c40
    Shader3d7708* shaders[0x100];     // +c48
    int saved;                        // +1448
    int stride;                       // +144c
    int base;                         // +1450

    Shader3d7708* shader_of(const Item3d7708* it) {
        return shaders[(it->part->a + it->mat->b) * stride + base];
    }
    void draw(unsigned int count, Item3d7708* items, Ctx3d7708* ctx, unsigned char reverse);
};

void setup_3bad0(Batch3d7708* b, Item3d7708* it, Ctx3d7708* ctx);                          // 0x710003bad0
void submit_3bdf4(Item3d7708* it, Ctx3d7708* ctx, Renderer3d7708* r, Shader3d7708* sh);    // 0x710003bdf4

#define STEP (reverse ? -1 : 1)

// 0x71003d7708
void Batch3d7708::draw(unsigned int count, Item3d7708* items, Ctx3d7708* ctx, unsigned char reverse) {
    Item3d7708* end = items + count;
    saved = renderer->state;
    Item3d7708* stop = reverse == 0 ? end : items - 1;
    Item3d7708* it = reverse == 0 ? items : end - 1;
    while (it != stop) {
        if (it->mat == nullptr) {
            it += STEP;
            continue;
        }
        Shader3d7708* sh = shader_of(it);
        Item3d7708* e = it;
        if (sh == nullptr) {
            for (; e != stop; e += STEP) {
                if (e->mat != nullptr && shader_of(e) != nullptr) {
                    break;
                }
            }
            it = e;
            continue;
        }
        for (int k = 0; k < 6; k++) {
            ctx->z[k] = 0;
        }
        ctx->pass = -1;
        if (current != sh) {
            if (current != nullptr) {
                current->unbind();
            }
            unsigned char ok = sh->bind();
            current = sh;
            if (!ok) {
                for (; e != stop; e += STEP) {
                    if (e->mat != nullptr && shader_of(e) != sh) {
                        break;
                    }
                }
                it = e;
                continue;
            }
        }
        if (reinterpret_cast<unsigned char*>(sh)[0x1298] & 1) {
            for (; e != stop; e += STEP) {
                if (e->mat == nullptr) {
                    continue;
                }
                if (shader_of(e) != sh) {
                    break;
                }
                setup_3bad0(this, e, ctx);
                unsigned int n = sh->passes();
                for (unsigned int p = 0; p < n; p++) {
                    if (!sh->begin(p)) {
                        break;
                    }
                    ctx->z[3] = 0;
                    submit_3bdf4(e, ctx, renderer, sh);
                    sh->end_pass();
                }
                sh->end();
            }
            it = e;
            continue;
        }
        unsigned int n = sh->passes();
        if (n == 0) {
            continue;
        }
        if (!sh->begin(0)) {
            for (; e != stop; e += STEP) {
                if (e->mat != nullptr && shader_of(e) != sh) {
                    break;
                }
            }
            sh->end();
            it = e;
            continue;
        }
        ctx->z[3] = 0;
        for (; e != stop; e += STEP) {
            if (e->mat == nullptr) {
                continue;
            }
            if (shader_of(e) != sh) {
                break;
            }
            setup_3bad0(this, e, ctx);
            submit_3bdf4(e, ctx, renderer, sh);
        }
        sh->end_pass();
        for (unsigned int p = 1; p < n; p++) {
            if (!sh->begin(p)) {
                break;
            }
            ctx->z[3] = 0;
            for (Item3d7708* q = it; q < e; q += STEP) {
                if (q->mat != nullptr) {
                    setup_3bad0(this, q, ctx);
                    submit_3bdf4(q, ctx, renderer, sh);
                }
            }
            sh->end_pass();
        }
        sh->end();
        it = e;
    }
    restore_52ac40(renderer, saved);
}
