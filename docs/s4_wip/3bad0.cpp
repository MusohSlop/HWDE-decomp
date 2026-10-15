// WIP: Renderer::setup<Kind> (0x710003bad0, 0x71003d8388, 0x71003d94fc, 0x71003da6f8; 804 bytes, identical bodies).
// State: same size, 5 instructions off, 2 with registers abstracted (fourth session, 2026-10-15):
// - flag block: eor operand order. The IR needs xor(!flag, want); ours is xor(want, !flag), because JumpThreading's
//   first run threads the ?: phi, which puts the flag_on load before the flag load in one block, and Reassociate then
//   orders the xor by rank (lower first). Swapping the xor's operands in the IR fixes this instruction
//   (worktrees\s4_perm\3bad0x\swap.ll). Forms tried without success: macro setter, bitwise &, explicit two-path setter,
//   flag_on read through a reference, want computed in the setter.
// - slot 1 of the uniforms (c * mul1): the fourth product gets s0 where the original has s1 (the original hoists the g
//   store above it). irsearch with loads free moves c.g's load before c.r's in that block; no source form found yet
//   (store orders, component orders, a loop over mul[2], multiplying inside the setter).
// Everything else matches: the colour compared through a float* view of &state->color.r (memcpy'd through the same
// pointer, so the base register stays live), the white path's four 1.0f stores through a local StateBlock*, GVN's
// widened loads of mul0/mul1 (StateBlock is 8-aligned), `!flag == on`, the cull flags read as int, the blend mode read
// before the new blend is stored.
struct Device {
    unsigned char pad0[0x88];
    int cull;                 // +88
};
void callee_52ac40(Device*, int);

struct Color {
    float r, g, b, a;
    bool operator!=(const Color& o) const { return !(r == o.r && g == o.g && b == o.b && a == o.a); }
};

static const Color kWhite = { 1.0f, 1.0f, 1.0f, 1.0f };

struct UniformSlot {
    short pad0;
    short changed;            // +02
    unsigned char pad4[0x4c];
    Color value;              // +50
    unsigned char pad60[0x20];
};
struct Uniforms {
    unsigned long dirty;      // +00
    unsigned char pad8[0x78];
    UniformSlot slots[2];     // +80
    void set(int i, const Color& v) {
        dirty |= 1UL << i;
        slots[i].value = v;
        slots[i].changed = 1;
    }
};

struct StateBlock {
    void* head;
    unsigned char pad8[0x1af8];
    Color color;              // +1b00
    Color mul0;               // +1b10
    Color mul1;               // +1b20
};

struct Target {
    unsigned long dirty;      // +000
    unsigned char pad8[0xbfa];
    unsigned short mode_set;  // +c02
    unsigned char padc04[0x4c];
    int mode;                 // +c50
};

struct Holder {
    unsigned char pad0[0x40];
    unsigned char sub[1];     // +40
};
void callee_59dc20(void*, void*);
void callee_5a39c4(void*);

struct GfxContext {
    unsigned char pad0[0x58];
    Holder* holder;           // +58
    unsigned char pad60[0x10];
    Uniforms* uniforms;       // +70
    unsigned char pad78[0x10];
    Target* target;           // +88
    unsigned char pad90[0x30];
    StateBlock* state;        // +c0
    unsigned char padc8[0xc];
    int blend;                // +d4
    int blend_mode;           // +d8
    unsigned char paddc[0x44];
    unsigned char flag;       // +120

    __attribute__((always_inline)) void set_color(const Color& c) {
        float* cur = &state->color.r;
        if (!(cur[0] == c.r && cur[1] == c.g && cur[2] == c.b) || cur[3] != c.a) {
            __builtin_memcpy(cur, &c, sizeof(Color));
            Color m0 = { c.r * state->mul0.r, c.g * state->mul0.g, c.b * state->mul0.b, c.a * state->mul0.a };
            uniforms->set(0, m0);
            Color m1 = { c.r * state->mul1.r, c.g * state->mul1.g, c.b * state->mul1.b, c.a * state->mul1.a };
            uniforms->set(1, m1);
        }
    }
    __attribute__((always_inline)) void set_white() {
        float* cur = &state->color.r;
        if (!(cur[0] == 1.0f && cur[1] == 1.0f && cur[2] == 1.0f && cur[3] == 1.0f)) {
            StateBlock* s = state; s->color.r = 1.0f; s->color.g = 1.0f; s->color.b = 1.0f; s->color.a = 1.0f;
            Color c = { 1.0f, 1.0f, 1.0f, 1.0f };
            Color m0 = { c.r * state->mul0.r, c.g * state->mul0.g, c.b * state->mul0.b, c.a * state->mul0.a };
            uniforms->set(0, m0);
            Color m1 = { c.r * state->mul1.r, c.g * state->mul1.g, c.b * state->mul1.b, c.a * state->mul1.a };
            uniforms->set(1, m1);
        }
    }
    void set_flag(bool on) {
        if (!flag == on) {
            flag = on;
            callee_59dc20(this, holder->sub);
        }
    }
    void set_blend(int v) {
        if (blend != (v & 0xf)) {
            int m = blend_mode;
            blend = v & 0xf;
            Target* t = target;
            if (t->mode != m || t->mode_set != 1) {
                t->dirty |= 0x800000;
                t->mode = m;
                t->mode_set = 1;
            }
            callee_5a39c4(this);
        }
    }
};

struct PartA {
    unsigned char pad0[8];
    unsigned char cull;       // +08
};
struct Material {
    unsigned char pad0[0x28];
    void* texture;            // +28
};
struct PartB {
    unsigned char pad0[0x20];
    Color* color;             // +20
    unsigned short flags;     // +28
    unsigned char pad2a[0x16];
    Material* material;       // +40
};
struct Item {
    PartA* a;
    PartB* b;
};

struct DrawState {
    unsigned char pad0[0x4c];
    int pass;                 // +4c
};

class Renderer;
void callee_58ee68(Renderer*, void*);

class Renderer {
public:
    void setup(Item* item, DrawState* st);

    unsigned char pad0[0x28];
    Device* dev;              // +28
    unsigned char pad30[0x1418];
    int saved_cull;           // +1448
    unsigned char pad144c[0x164];
    void* default_texture;    // +15b0
    unsigned char pad15b8[0x58];
    int flag_on;              // +1610
    unsigned char pad1614[0x7c];
    void* fixed_texture;      // +1690
    bool keep_color;          // +1698
    bool keep_flags;          // +1699
    unsigned char pad169a[0xe];
    GfxContext* gfx;          // +16a8
};


void Renderer::setup(Item* item, DrawState* st) {
    if (!fixed_texture) {
        void* tex = item->b->material->texture;
        if (!tex) tex = default_texture;
        callee_58ee68(this, tex);
    }
    if (!keep_color) {
        Color* c = item->b->color;
        if (c) gfx->set_color(*c);
        else gfx->set_white();
    }
    if (!keep_flags) {
        int fl = item->b->flags;
        gfx->set_flag((fl & 0x10) ? false : flag_on != 0);
        gfx->set_blend(fl);
    }
    int fl = item->b->flags;
    int mode;
    if (st->pass == 0 && (fl & 0x20)) mode = 1;
    else if (st->pass == 1 && (fl & 0x40)) mode = 1;
    else {
        mode = item->a->cull;
        if (!mode) mode = saved_cull;
    }
    callee_52ac40(dev, mode);
}
