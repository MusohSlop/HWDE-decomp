// Large functions written by hand (fifth session), second unit. Struct, field and callee names are placeholders
// after the address and offset, as in the generated units; string literals are named after the text and their
// address (the linker merged two of them with other modules' strings). Status: matching/README.md.

extern "C" void* memset(void*, int, unsigned long);

extern const char kLine300_7db832[] __attribute__((visibility("hidden")));
extern const char kLine301_7db83c[] __attribute__((visibility("hidden")));
extern const char kLine302_7db846[] __attribute__((visibility("hidden")));
extern const char kLine303_7db850[] __attribute__((visibility("hidden")));
extern const char kLine00_7db82a[] __attribute__((visibility("hidden")));
extern const char kLine01_7d7ef3[] __attribute__((visibility("hidden")));
extern const char kLine02_7da0be[] __attribute__((visibility("hidden")));
extern const char kLine04_7db85a[] __attribute__((visibility("hidden")));
extern const char kLine05_7db862[] __attribute__((visibility("hidden")));
extern const char kLine06_7db86a[] __attribute__((visibility("hidden")));
extern const char kLine700_7db872[] __attribute__((visibility("hidden")));
extern const char kLine701_7db87c[] __attribute__((visibility("hidden")));
extern const char kLine702_7db886[] __attribute__((visibility("hidden")));
extern const char kLine703_7db890[] __attribute__((visibility("hidden")));
extern const char kLine08_7db89a[] __attribute__((visibility("hidden")));
extern const char kLine09_7db8a2[] __attribute__((visibility("hidden")));
extern const char kLine10_7db8aa[] __attribute__((visibility("hidden")));
extern const char kLine11_7db8b2[] __attribute__((visibility("hidden")));
extern const char kLine12_7db8ba[] __attribute__((visibility("hidden")));
extern const char kLine13_7db8c2[] __attribute__((visibility("hidden")));
extern const char kLine14_7db8ca[] __attribute__((visibility("hidden")));
extern const char kLineDlc00_7db922[] __attribute__((visibility("hidden")));
extern const char kLineDlc01_7db92e[] __attribute__((visibility("hidden")));
extern const char kLine300Dlc_7db8d2[] __attribute__((visibility("hidden")));
extern const char kLine04Dlc_7db8e0[] __attribute__((visibility("hidden")));
extern const char kLine700Dlc_7db8ec[] __attribute__((visibility("hidden")));
extern const char kLine302Dlc_7db8fa[] __attribute__((visibility("hidden")));
extern const char kLine06Dlc_7db908[] __attribute__((visibility("hidden")));
extern const char kLine702Dlc_7db914[] __attribute__((visibility("hidden")));
extern const char kLineDlc04_7db952[] __attribute__((visibility("hidden")));
extern const char kLineZds00_7db95e[] __attribute__((visibility("hidden")));
extern const char kLineZds01_7db96a[] __attribute__((visibility("hidden")));
extern const char kLineZds02_7db976[] __attribute__((visibility("hidden")));
extern const char kLineZds03_7db982[] __attribute__((visibility("hidden")));
extern const char kLineZds04_7db98e[] __attribute__((visibility("hidden")));
extern const char kLineZds05_7db99a[] __attribute__((visibility("hidden")));
extern const char kLineZds06_7db9a6[] __attribute__((visibility("hidden")));
extern const char kLineZds07_7db9b2[] __attribute__((visibility("hidden")));
extern const char kLineZds08_7db9be[] __attribute__((visibility("hidden")));
extern const char kLineDlc02_7db93a[] __attribute__((visibility("hidden")));
extern const char kLineDlc03_7db946[] __attribute__((visibility("hidden")));

struct Color3bdbf0 {
    unsigned char r, g, b, a;
};

struct Pane3bdbf0 {
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();
    virtual void slot_4();
    virtual void set_vtx_color(int index, const Color3bdbf0& color);
    virtual void slot_6();
    virtual void slot_7();
    virtual void slot_8();
    virtual void slot_9();
    virtual void slot_10();
    virtual void slot_11();
    virtual Pane3bdbf0* find_pane(const char* name, bool recursive);
    unsigned char pad8[0x50];
    unsigned char flags;              // +58

    void set_visible(bool visible) { flags = (flags & ~1) | (visible & 1); }
};

struct Layout3bdbf0 {
    unsigned char pad0[0x18];
    Pane3bdbf0* root;                 // +18
};

// Each colour is its own temporary, stored right before its call.
static inline void set_white(Pane3bdbf0* pane) {
    for (int i = 0; i < 4; i++) {
        pane->set_vtx_color(i, Color3bdbf0{0xff, 0xff, 0xff, 0xff});
    }
}

struct Menu3bdbf0 {
    unsigned char pad0[0x4f0];
    unsigned char field_4f0[2];       // +4f0
    unsigned char pad4f2[0x1e];
    unsigned char field_510[2];       // +510
    unsigned char pad512[0x35];
    unsigned char field_547;          // +547
    unsigned char pad548[0x2b8];
    Layout3bdbf0* layout;             // +800

    Pane3bdbf0* find(const char* name) { return layout->root->find_pane(name, true); }
    void show_line(int line, unsigned char visible);
};

// 0x71003bdbf0: shows or hides the line panes of LINE (1 to 31) of a layout. VISIBLE is a byte whose bit 0 is
// used (the original masks it where it computes the DLC lines' flag, so the shared tail uses orr there and bfxil
// elsewhere); that flag is computed before its pane is looked up.
void Menu3bdbf0::show_line(int line, unsigned char visible) {
    switch (line) {
    case 0x1:
        find(kLine00_7db82a)->set_visible(visible & 1);
        break;
    case 0x2:
        find(kLine01_7d7ef3)->set_visible(visible & 1);
        break;
    case 0x3:
        find(kLine02_7da0be)->set_visible(visible & 1);
        break;
    case 0x4:
    case 0x6:
    case 0x8:
        find(kLine300_7db832)->set_visible(visible & 1);
        find(kLine301_7db83c)->set_visible(visible & 1);
        find(kLine302_7db846)->set_visible(visible & 1);
        find(kLine303_7db850)->set_visible(false);
        break;
    case 0x5:
        find(kLine04_7db85a)->set_visible(visible & 1);
        break;
    case 0x7:
        find(kLine05_7db862)->set_visible(visible & 1);
        break;
    case 0x9:
        find(kLine06_7db86a)->set_visible(visible & 1);
        break;
    case 0xa:
        set_white(find(kLine700_7db872));
        find(kLine700_7db872)->set_visible(visible & 1);
        set_white(find(kLine701_7db87c));
        find(kLine701_7db87c)->set_visible(visible & 1);
        set_white(find(kLine702_7db886));
        find(kLine702_7db886)->set_visible(visible & 1);
        find(kLine703_7db890)->set_visible(false);
        break;
    case 0xb:
        find(kLine08_7db89a)->set_visible(visible & 1);
        break;
    case 0xc:
        find(kLine09_7db8a2)->set_visible(visible & 1);
        break;
    case 0xd:
        find(kLine10_7db8aa)->set_visible(visible & 1);
        break;
    case 0xe:
        find(kLine11_7db8b2)->set_visible(visible & 1);
        break;
    case 0xf:
        find(kLine12_7db8ba)->set_visible(visible & 1);
        break;
    case 0x10:
        find(kLine13_7db8c2)->set_visible(visible & 1);
        break;
    case 0x11:
        find(kLine14_7db8ca)->set_visible(visible & 1);
        break;
    case 0x12:
        find(kLineDlc00_7db922)->set_visible(visible & 1);
        break;
    case 0x13:
        find(kLineDlc01_7db92e)->set_visible(visible & 1);
        break;
    case 0x14: {
        find(kLine300Dlc_7db8d2)->set_visible(visible & 1);
        find(kLine04Dlc_7db8e0)->set_visible(visible & 1);
        find(kLine700Dlc_7db8ec)->set_visible(visible & 1);
        bool shown = field_547 ? (visible & 1) : (field_4f0[0] ? field_510[0] != 0 : false);
        find(kLineDlc02_7db93a)->set_visible(shown);
        break;
    }
    case 0x15: {
        find(kLine302Dlc_7db8fa)->set_visible(visible & 1);
        find(kLine06Dlc_7db908)->set_visible(visible & 1);
        find(kLine702Dlc_7db914)->set_visible(visible & 1);
        bool shown = field_547 ? (visible & 1) : (field_4f0[1] ? field_510[1] != 0 : false);
        find(kLineDlc03_7db946)->set_visible(shown);
        break;
    }
    case 0x16:
        find(kLineDlc04_7db952)->set_visible(visible & 1);
        break;
    case 0x17:
        find(kLineZds00_7db95e)->set_visible(visible & 1);
        break;
    case 0x18:
        find(kLineZds01_7db96a)->set_visible(visible & 1);
        set_white(find(kLine700Dlc_7db8ec));
        break;
    case 0x19:
        find(kLineZds02_7db976)->set_visible(visible & 1);
        set_white(find(kLine702Dlc_7db914));
        break;
    case 0x1a:
        find(kLineZds03_7db982)->set_visible(visible & 1);
        break;
    case 0x1b:
        find(kLineZds04_7db98e)->set_visible(visible & 1);
        break;
    case 0x1c:
        find(kLineZds05_7db99a)->set_visible(visible & 1);
        break;
    case 0x1d:
        find(kLineZds06_7db9a6)->set_visible(visible & 1);
        break;
    case 0x1e:
        find(kLineZds07_7db9b2)->set_visible(visible & 1);
        break;
    case 0x1f:
        find(kLineZds08_7db9be)->set_visible(visible & 1);
        break;
    }
}

struct AllocInfo448544 {
    unsigned short tag;
    unsigned short flags;
    void* name;
    explicit AllocInfo448544(unsigned short t) : tag(t), flags(0), name(nullptr) {}
};

struct Heap448544 {
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();
    virtual void slot_4();
    virtual void slot_5();
    virtual void slot_6();
    virtual void slot_7();
    virtual void slot_8();
    virtual void* alloc(unsigned long size, int align, const AllocInfo448544& info);
};

// The allocation info is a temporary built in the call, so its stores come right before the call.
static inline void* heap_alloc(Heap448544* heap, unsigned long size) {
    return heap->alloc(size, 0x10, AllocInfo448544(0x2e));
}

struct Vec4_448544 {
    float x, y, z, w;
};

struct Light448544 {
    float v[8];
};

struct Texture448544 {
    unsigned char pad0[0x50];
    unsigned int lo : 10;
    unsigned int format : 6;
    unsigned int hi : 16;
};

struct Group448544 {
    unsigned char pad0[0xb8];
    void* first;                      // +b8
    void* field_c0;                   // +c0
    // Setters: the group is loaded before the value it is given.
    void set_first(void* p) { first = p; }
    void set_c0(void* p) { field_c0 = p; }
    unsigned char padc8[0x38];
};

struct Item448544 {
    unsigned char pad0[0x1a0];
};

struct Effect448544 {
    virtual void slot_0();
    virtual void slot_1();
    virtual void attach(Group448544* group);
    unsigned char pad8[0x18];
    int field_20;                     // +20
    unsigned char pad24[0xc];
    int field_30;                     // +30
    int field_34;                     // +34
    int field_38;                     // +38
    unsigned char pad3c[0x2c];
    int field_68;                     // +68
};

struct Pool448544 {
    long field_0;
    long field_8;
    unsigned long field_10;
    int field_18;
    unsigned char pad1c[0x7c];
    unsigned char field_98;           // +98
};

struct Slot448544 {
    unsigned char pad0[0xb0];
};

struct Global_c216f8 {
    unsigned char pad0[0x10];
    unsigned char field_10[1];        // +10
};
extern Global_c216f8 gGlobalc216f8_448544;
extern void* gGlobalc21db0_448544;

struct Scene448544;
void callee_448124(Scene448544*);        // 0x7100448124
void* callee_45c96c();        // 0x710045c96c
void* callee_45c458(void*, int, int, bool, bool);        // 0x710045c458
void callee_5c2d40(Heap448544*, void*, int, int, int, int);        // 0x71005c2d40
void callee_459b54();        // 0x7100459b54
void callee_459b64();        // 0x7100459b64
Texture448544* callee_517b50(void*, int, int, int, int, int, int);        // 0x7100517b50
void* callee_58f108(unsigned int*, Heap448544*);        // 0x710058f108
void callee_58f37c(void*, Vec4_448544*);        // 0x710058f37c
void callee_58f2c0(void*, int, Light448544*);        // 0x710058f2c0
void callee_57d274(void*, void*, void*, void*, float, float, float, float, float, float);        // 0x710057d274
void callee_57ce00(void*, int, bool);        // 0x710057ce00
void* callee_4444f8();        // 0x71004444f8
void* callee_444504();        // 0x7100444504
void* callee_444510();        // 0x7100444510
void* callee_44451c();        // 0x710044451c
void callee_449f50(Group448544*);        // 0x7100449f50
void callee_43e1bc(Item448544*);        // 0x710043e1bc
void callee_449fec(Group448544*, int, void*, void*);        // 0x7100449fec
void callee_43e560(Item448544*, int, Group448544*, void*, void*, int, Heap448544*);        // 0x710043e560
void callee_44a6f4(Group448544*);        // 0x710044a6f4
void callee_433d54(Effect448544*);        // 0x7100433d54
void callee_4340c8(Effect448544*, Group448544*);        // 0x71004340c8
void callee_433dfc(Effect448544*, Heap448544*);        // 0x7100433dfc
void callee_43b234(void*);        // 0x710043b234
void callee_43b408(void*);        // 0x710043b408
void callee_43b288(void*, int, int, int, int, int, int, Heap448544*);        // 0x710043b288
void callee_43b66c(void*, int);        // 0x710043b66c
void callee_43c110(Slot448544*);        // 0x710043c110
void callee_43c1b4(Slot448544*);        // 0x710043c1b4
void callee_43c764(Slot448544*);        // 0x710043c764
void callee_43c7f4(Slot448544*);        // 0x710043c7f4
void callee_44113c(void*);        // 0x710044113c
void callee_441234(void*, float, Heap448544*, int, int, int);        // 0x7100441234
void callee_441a44(void*);        // 0x7100441a44
void callee_441b38(void*, float, Heap448544*, int, int, int);        // 0x7100441b38
void* callee_45164c();        // 0x710045164c
void callee_451548();        // 0x7100451548
void callee_45165c(void*);        // 0x710045165c

struct Scene448544 {
    unsigned char pad0[0x28];
    Heap448544 heap;                  // +28
    unsigned char pad30[0x58];
    void* buffer;                     // +88
    unsigned long buffer_pos;         // +90
    unsigned long buffer_size;        // +98
    unsigned char camera[0x170];      // +a0
    unsigned char field_210[0x10];    // +210
    unsigned char field_220[0x10];    // +220
    void* field_230;                  // +230
    Texture448544* texture;           // +238
    void* field_240;                  // +240
    Group448544* groups;              // +248
    Item448544* items;                // +250
    Effect448544* effect;             // +258
    Pool448544* pool;                 // +260
    Slot448544* slots_a;              // +268
    Slot448544* slots_b;              // +270
    int field_278;                    // +278
    int field_27c;                    // +27c
    void* field_280;                  // +280
    void* field_288;                  // +288
    unsigned char pad290[0xc];
    unsigned char field_29c;          // +29c

    void init();
};

// 0x7100448544: sets up the scene's heap, buffers and renderer objects. KIND is 8-byte aligned in the original's
// frame (it sits below the saved d8, not in the 4-byte gap after it).
void Scene448544::init() {
    callee_448124(this);
    void* mem = callee_45c458(callee_45c96c(), 0x10, 0x20000, true, false);
    field_230 = mem;
    callee_5c2d40(&heap, mem, 0x20000, 4, 4, 0x10);
    {
        void* p = heap_alloc(&heap, 0x1400);
        buffer = p;
        buffer_pos = 0;
        buffer_size = p != nullptr ? 0x1400 : 0;
    }
    callee_459b54();
    Texture448544* tex = callee_517b50(gGlobalc21db0_448544, 0x200, 0x200, 1, 9, 0, 1);
    texture = tex;
    if (tex != nullptr) {
        tex->format = 5;
    }
    callee_459b64();
    alignas(8) unsigned int kind = 0x8001;
    Vec4_448544 color = {0.5f, 0.5f, 0.5f, 1.0f};
    Light448544 light = {{0.5f, -0.7f, -0.5f, 0.0f, 5.0f, 5.0f, 5.0f, 1.0f}};
    field_240 = callee_58f108(&kind, &heap);
    callee_58f37c(field_240, &color);
    callee_58f2c0(field_240, 1, &light);
    callee_57d274(camera, field_220, field_210, gGlobalc216f8_448544.field_10, 0.0f, 0.69813168f, 64.0f, 95000.0f, 1.0f,
                  1.0f);
    callee_57ce00(camera, 1, true);
    void* a = callee_4444f8();
    void* b = callee_444504();
    void* c = callee_444510();
    void* d = callee_44451c();
    {
        Group448544* p = static_cast<Group448544*>(heap_alloc(&heap, 0x200));
        Group448544* g = nullptr;
        if (p != nullptr) {
            callee_449f50(p);
            callee_449f50(p + 1);
            g = p;
        }
        groups = g;
    }
    {
        Item448544* p = static_cast<Item448544*>(heap_alloc(&heap, 0x9c0));
        Item448544* it = nullptr;
        if (p != nullptr) {
            for (int i = 0; i < 6; i++) {
                callee_43e1bc(p + i);
            }
            it = p;
        }
        items = it;
    }
    callee_449fec(groups, 0, d, a);
    callee_43e560(items, 0, groups, b, c, -1, &heap);
    groups->set_first(items);
    callee_44a6f4(groups);
    callee_449fec(groups + 1, 1, d, a);
    for (int i = 1; i < 6; i++) {
        callee_43e560(items + i, 0, groups + 1, b, c, -1, &heap);
    }
    groups[1].set_first(items + 1);
    callee_44a6f4(groups + 1);
    {
        Effect448544* p = static_cast<Effect448544*>(heap_alloc(&heap, 0x80));
        Effect448544* e = nullptr;
        if (p != nullptr) {
            callee_433d54(p);
            e = p;
        }
        effect = e;
    }
    effect->field_20 = 0x55;
    effect->field_30 = -1;
    effect->field_34 = -1;
    effect->field_38 = 0;
    groups->set_c0(effect);
    effect->attach(groups);
    callee_4340c8(effect, groups + 1);
    effect->field_68 = 0;
    callee_433dfc(effect, &heap);
    Pool448544* pool_p;
    {
        Pool448544* p = static_cast<Pool448544*>(heap_alloc(&heap, 0x9a0));
        pool_p = nullptr;
        if (p != nullptr) {
            p->field_0 = 0;
            p->field_8 = -1;
            p->field_10 = 0x10000ffffffffUL;
            p->field_18 = 0;
            callee_43b234(reinterpret_cast<unsigned char*>(p) + 0x20);
            memset(reinterpret_cast<unsigned char*>(p) + 0xa0, 0, 0x880);
            for (int i = 0; i < 4; i++) {
                callee_43b408(reinterpret_cast<unsigned char*>(p) + 0x920 + i * 0x20);
            }
            pool_p = p;
        }
    }
    pool = pool_p;
    *reinterpret_cast<int*>(&pool_p->field_10) = 0;
    callee_43b288(reinterpret_cast<unsigned char*>(pool_p) + 0x20, 0, 0x170000, 0x70000, 0x10000, 0x20, 4, &heap);
    pool_p->field_98 = 1;
    for (int i = 0; i < 4; i++) {
        callee_43b66c(reinterpret_cast<unsigned char*>(pool_p) + 0x920 + i * 0x20, 0x80);
    }
    {
        Slot448544* p = static_cast<Slot448544*>(heap_alloc(&heap, 0x2c0));
        Slot448544* s = nullptr;
        if (p != nullptr) {
            for (int i = 0; i < 4; i++) {
                callee_43c110(p + i);
            }
            s = p;
        }
        slots_a = s;
    }
    for (int i = 0; i < 4; i++) {
        callee_43c1b4(slots_a + i);
    }
    field_278 = 0;
    {
        Slot448544* p = static_cast<Slot448544*>(heap_alloc(&heap, 0x2c0));
        Slot448544* s = nullptr;
        if (p != nullptr) {
            for (int i = 0; i < 4; i++) {
                callee_43c764(p + i);
            }
            s = p;
        }
        slots_b = s;
    }
    for (int i = 0; i < 4; i++) {
        callee_43c7f4(slots_b + i);
    }
    field_27c = 0;
    {
        void* p = heap_alloc(&heap, 0x8c0);
        void* o = nullptr;
        if (p != nullptr) {
            callee_44113c(p);
            o = p;
        }
        field_280 = o;
        callee_441234(o, 95000.0f, &heap, 4, 0x20, 4);
    }
    {
        void* p = heap_alloc(&heap, 0x8c0);
        void* o = nullptr;
        if (p != nullptr) {
            callee_441a44(p);
            o = p;
        }
        field_288 = o;
        callee_441b38(o, 95000.0f, &heap, 4, 0x20, 4);
    }
    if (callee_45164c() == nullptr) {
        callee_451548();
        callee_45165c(callee_45164c());
        field_29c = 1;
    }
}
