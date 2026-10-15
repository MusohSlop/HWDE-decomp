// A renderer's batch drawer, a template instantiated once per item kind: Renderer::draw_items<Kind3b64c>
// (0x710003b64c), <Kind3d7f04> (0x71003d7f04) and <Kind3d9078> (0x71003d9078). It walks an item list forwards or
// backwards, groups neighbouring items that use the same shader, binds the shader once per group and draws the group
// once per pass. Names are descriptive placeholders; the kinds are named after their first instantiation.

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
};
struct PartB {
    unsigned char pad0[0x2a];
    short id;                 // +2a
};
struct Item {
    PartA* a;
    PartB* b;                 // null: skipped
};

struct DrawState {
    void* f0;
    void* f8;
    void* f10;
    void* f18;
    void* f20;
    void* f28;
    void* f30;
    void* f38;
    void* f40;
    int index;                // +48
};

struct Kind3b64c;
struct Kind3d7f04;
struct Kind3d9078;

// Draws one item with the bound shader: 0x710003bdf4, 0x71003d86ac, 0x71003d9820.
template <class Kind> void draw_item(Item* item, DrawState* st, Device* dev, Shader* shader);

class Renderer {
public:
    template <class Kind> void draw_items(unsigned int count, Item* items, DrawState* st, unsigned char reverse);
    // Per-item render state: 0x710003bad0, 0x71003d8388, 0x71003d94fc.
    template <class Kind> void setup(Item* item, DrawState* st);

    Shader* shader_for(Item* it) {
        int w = stride;
        return table[base + w * (it->b->id + it->a->id)];
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
    unsigned char padc48[0x800];
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

template void Renderer::draw_items<Kind3b64c>(unsigned int, Item*, DrawState*, unsigned char);
template void Renderer::draw_items<Kind3d7f04>(unsigned int, Item*, DrawState*, unsigned char);
template void Renderer::draw_items<Kind3d9078>(unsigned int, Item*, DrawState*, unsigned char);
