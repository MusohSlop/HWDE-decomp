// A renderer's batch drawer, templates instantiated once per item kind (the kinds are the item materials, named
// after their first instantiation):
// - Renderer::draw_items<Kind> walks an item list forwards or backwards, groups neighbouring items that use the same
//   shader, binds the shader once per group and draws the group once per pass: <Kind3b64c> (0x710003b64c),
//   <Kind3d7f04> (0x71003d7f04), <Kind3d9078> (0x71003d9078), <Kind3da0f4> (0x71003da0f4, with draw_item inlined);
// - draw_item<Kind> hands one item to the device by its part's kind: <Kind3b64c> (0x710003bdf4), <Kind3d7f04>
//   (0x71003d86ac), <Kind3d9078> (0x71003d9820). Kind3da0f4's first hook is empty, which makes its draw_item cheap
//   enough to inline;
// - Renderer::draw_list<Kind> is draw_items with the second shader table, its null shaders skipped before the state is
//   reset: <Kind3da0f4> (0x71003dab18). The other kinds' copies (0x71003d7708, 0x71003d887c, 0x71003d98f8) come out 8
//   bytes short: one loop exit shares a block that the original keeps apart (docs/s4_wip/3d7708.txt).
// Names are descriptive placeholders.

struct Device {
    unsigned char pad0[0x88];
    int cull;                 // +88
};
void callee_52ac40(Device*, int);                                           // 0x710052ac40: sets the cull mode

class Shader {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();
    virtual void slot_4();
    virtual void slot_5();
    virtual void slot_6();
    virtual void slot_7();
    virtual void slot_8();
    virtual void slot_9();
    virtual void slot_10();
    virtual unsigned char begin();                  // +58
    virtual void finish();                          // +60
    virtual unsigned int passes();                  // +68
    virtual void end();                             // +70
    virtual unsigned char begin_pass(unsigned int); // +78
    virtual void end_pass();                        // +80

    unsigned char pad8[0x1290];
    unsigned char per_item;   // +1298: draw every item on its own (all passes per item)
};

struct PartA {
    unsigned char pad0[4];
    short id;                 // +04
    short kind;               // +06
};
struct PartB {
    unsigned char pad0[0x2a];
    short id;                 // +2a
    unsigned char pad2c[0x14];
    void* material;           // +40: the kind's material
};
struct Item {
    PartA* a;
    PartB* b;                 // null: skipped
};

struct MatPart;
struct DrawState {
    PartA* f0;
    MatPart* f8;
    PartB* f10;
    PartB* f18;               // the previous item's f10
    void* f20;
    void* f28;
    void* f30;
    void* f38;
    void* f40;
    int index;                // +48
};

void callee_58ce5c(DrawState*, Device*, Shader*);                           // 0x710058ce5c
void callee_58d6dc(DrawState*, Device*, Shader*);                           // 0x710058d6dc
void callee_58de98(DrawState*, Device*, Shader*);                           // 0x710058de98

struct MatBase {
    void* head;
};
struct MatPart {
    void* head;
    void hook_b(Shader*, PartA*);                                           // 0x71003d8788
};
struct Kind3b64c : MatBase, MatPart {
    void hook_a(Shader*, PartA*);                                           // 0x71000363ec
    void hook_b(Shader*, PartA*);                                           // 0x710003659c
};
struct Kind3d7f04 : MatBase, MatPart {
    void hook_a(Shader*, PartA*);                                           // 0x710043c2a8
};
struct Kind3d9078 : MatBase, MatPart {
    void hook_a(Shader*, PartA*);                                           // 0x710043ca58
    void hook_b(Shader*, PartA*);                                           // 0x710043ca84
};
struct Kind3da0f4 : MatBase, MatPart {
    void hook_a(Shader*, PartA*) {}
    void hook_b(Shader*, PartA*);                                           // 0x71003daa1c
};

// The material is converted to its second base in a local before the previous item is read (the conversion's
// register comes first), and the state's item pair is stored before the part pair.
template <class Kind>
void draw_item(Item* item, DrawState* st, Device* dev, Shader* shader) {
    PartA* part = item->a;
    PartB* b = item->b;
    Kind* m = static_cast<Kind*>(b->material);
    MatPart* mp = m;
    PartB* prev = st->f10;
    st->f10 = b;
    st->f18 = prev;
    st->f0 = part;
    st->f8 = mp;
    PartA* a = item->a;
    switch (a->kind) {
    case 0:
    case 2:
        m->hook_a(shader, a);
        callee_58ce5c(st, dev, shader);
        break;
    case 1:
        m->hook_b(shader, a);
        callee_58d6dc(st, dev, shader);
        break;
    case 4:
        callee_58de98(st, dev, shader);
        break;
    }
}

class Renderer {
public:
    template <class Kind> void draw_items(unsigned int count, Item* items, DrawState* st, unsigned char reverse);
    // The same with the second shader table, null shaders skipped before the state is reset.
    template <class Kind> void draw_list(unsigned int count, Item* items, DrawState* st, unsigned char reverse);
    // Per-item render state: 0x710003bad0, 0x71003d8388, 0x71003d94fc, 0x71003da6f8 (docs/s4_wip/3bad0.cpp).
    template <class Kind> void setup(Item* item, DrawState* st);

    Shader* shader_for(Item* it) {
        int w = stride;
        return table[base + w * (it->b->id + it->a->id)];
    }
    Shader* list_shader_for(Item* it) {
        int w = stride;
        return list_table[base + w * (it->b->id + it->a->id)];
    }
    bool select(Shader* s) {
        if (current == s) return true;
        if (current) current->finish();
        bool ok = s->begin();
        current = s;
        return ok;
    }

    unsigned char pad0[0x28];
    Device* dev;              // +28
    unsigned char pad30[0x400];
    Shader* table[258];       // +430
    Shader* current;          // +c40
    Shader* list_table[256];  // +c48
    int saved_cull;           // +1448
    int stride;               // +144c
    int base;                 // +1450
};

// The loop keeps the group start in two variables (`it` and `first`): GVN then cannot prove the null test's load
// and the shader lookup's load the same, and the original reloads the item's fields after the test.
template <class Kind>
void Renderer::draw_items(unsigned int count, Item* items, DrawState* st, unsigned char reverse) {
    saved_cull = dev->cull;
    Item* end = reverse == 0 ? items + count : items - 1;
    Item* it = reverse == 0 ? items : items + count - 1;
    Item* first = it;
    while (end != it) {
        long step = reverse == 0 ? 1 : -1;
        if (!it->b) { it += step; first = it; continue; }
        Shader* s = shader_for(first);
        st->f18 = 0;
        st->f20 = 0;
        st->f28 = 0;
        st->f30 = 0;
        st->f38 = 0;
        st->f40 = 0;
        st->index = -1;
        Item* next;
        if (!s || !select(s)) {
            for (next = first; end != next; next += step)
                if (next->b && s != shader_for(next)) break;
            it = first = next;
            continue;
        }
        if (s->per_item & 1) {
            for (next = first; end != next; next += step) {
                if (!next->b) continue;
                if (s != shader_for(next)) break;
                setup<Kind>(next, st);
                unsigned int n = s->passes();
                for (unsigned int i = 0; i < n; i++) {
                    if (!s->begin_pass(i)) break;
                    st->f30 = 0;
                    draw_item<Kind>(next, st, dev, s);
                    s->end_pass();
                }
                s->end();
            }
            it = first = next;
            continue;
        }
        unsigned int n = s->passes();
        if (n == 0) continue;
        if (!s->begin_pass(0)) {
            for (next = first; end != next; next += step)
                if (next->b && s != shader_for(next)) break;
        } else {
            st->f30 = 0;
            for (next = first; end != next; next += step) {
                if (!next->b) continue;
                if (s != shader_for(next)) break;
                setup<Kind>(next, st);
                draw_item<Kind>(next, st, dev, s);
            }
            s->end_pass();
            for (unsigned int i = 1; i < n; i++) {
                if (!s->begin_pass(i)) break;
                st->f30 = 0;
                for (Item* p = first; next > p; p += step)
                    if (p->b) {
                        setup<Kind>(p, st);
                        draw_item<Kind>(p, st, dev, s);
                    }
                s->end_pass();
            }
        }
        s->end();
        it = first = next;
    }
    callee_52ac40(dev, saved_cull);
}

template <class Kind>
void Renderer::draw_list(unsigned int count, Item* items, DrawState* st, unsigned char reverse) {
    saved_cull = dev->cull;
    Item* end = reverse == 0 ? items + count : items - 1;
    Item* it = reverse == 0 ? items : items + count - 1;
    Item* first = it;
    while (end != it) {
        long step = reverse == 0 ? 1 : -1;
        if (!it->b) { it += step; first = it; continue; }
        Shader* s = list_shader_for(first);
        Item* next;
        if (!s) {
            for (next = first; end != next; next += step)
                if (next->b && list_shader_for(next)) break;
            it = first = next;
            continue;
        }
        st->f18 = 0;
        st->f20 = 0;
        st->f28 = 0;
        st->f30 = 0;
        st->f38 = 0;
        st->f40 = 0;
        st->index = -1;
        if (!select(s)) {
            for (next = first; end != next; next += step)
                if (next->b && s != list_shader_for(next)) break;
            it = first = next;
            continue;
        }
        if (s->per_item & 1) {
            for (next = first; end != next; next += step) {
                if (!next->b) continue;
                if (s != list_shader_for(next)) break;
                setup<Kind>(next, st);
                unsigned int n = s->passes();
                for (unsigned int i = 0; i < n; i++) {
                    if (!s->begin_pass(i)) break;
                    st->f30 = 0;
                    draw_item<Kind>(next, st, dev, s);
                    s->end_pass();
                }
                s->end();
            }
            it = first = next;
            continue;
        }
        unsigned int n = s->passes();
        if (n == 0) continue;
        if (!s->begin_pass(0)) {
            for (next = first; end != next; next += step)
                if (next->b && s != list_shader_for(next)) break;
        } else {
            st->f30 = 0;
            for (next = first; end != next; next += step) {
                if (!next->b) continue;
                if (s != list_shader_for(next)) break;
                setup<Kind>(next, st);
                draw_item<Kind>(next, st, dev, s);
            }
            s->end_pass();
            for (unsigned int i = 1; i < n; i++) {
                if (!s->begin_pass(i)) break;
                st->f30 = 0;
                for (Item* p = first; next > p; p += step)
                    if (p->b) {
                        setup<Kind>(p, st);
                        draw_item<Kind>(p, st, dev, s);
                    }
                s->end_pass();
            }
        }
        s->end();
        it = first = next;
    }
    callee_52ac40(dev, saved_cull);
}
template void draw_item<Kind3b64c>(Item*, DrawState*, Device*, Shader*);
template void draw_item<Kind3d7f04>(Item*, DrawState*, Device*, Shader*);
template void draw_item<Kind3d9078>(Item*, DrawState*, Device*, Shader*);
template void Renderer::draw_items<Kind3b64c>(unsigned int, Item*, DrawState*, unsigned char);
template void Renderer::draw_items<Kind3d7f04>(unsigned int, Item*, DrawState*, unsigned char);
template void Renderer::draw_items<Kind3d9078>(unsigned int, Item*, DrawState*, unsigned char);
template void Renderer::draw_items<Kind3da0f4>(unsigned int, Item*, DrawState*, unsigned char);
template void Renderer::draw_list<Kind3da0f4>(unsigned int, Item*, DrawState*, unsigned char);
