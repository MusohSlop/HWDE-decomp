// Fifth session, in progress: 0x71003beef0 (1,596 bytes), the line refresh of the menu whose 3bdbf0 (show_line)
// is matched in misc/s5_functions02.cpp; this draft reuses that unit's types (the colour type needs a constructor
// here, so its static colour array gets the original's guarded initialisation; 3bdbf0 must be rechecked with it).
// 1,548 bytes here, 34 instructions off when registers are abstracted. Settled: the flag bytes are read one by one
// (an align-1 byte-array type, so GVN does not widen the loads), the three lit flags as a local bool[3], the
// name table at 0xbdb860 (kLine3Names_bdb860), the four set_vtx_color calls per unlit line, show_line3 three
// times. Still off: each of the four pane translate copies goes through a 12-byte stack temporary in the original
// (x and y as one 8-byte load stored to the stack and reloaded, z kept in a register with a "mov w9, w9"), which
// accounts for the 48 missing bytes, and the DLC flags' true block is shared between the two tests there.
// Maps for tools/s5/sbs.py: the static colour array and its guard (_ZZN10Menu3bdbf013refresh_linesEvE6colors at
// 0x7100ca2ea8, guard _ZGVZ... at 0x7100ca2eb8) and .rodata=0x7100804428.

extern "C" void* memset(void*, int, unsigned long);
extern "C" void* memcpy(void*, const void*, unsigned long);

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
    Color3bdbf0(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_) : r(r_), g(g_), b(b_), a(a_) {}
};

template <int N>
struct Bytes3beef0 {
    unsigned char v[N];
    unsigned char operator[](int i) const { return v[i]; }
};

struct Float3_3beef0 {
    float x, y, z;
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
    unsigned char pad8[0x28];
    Float3_3beef0 translate;          // +30
    unsigned char pad3c[0x1c];
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
    unsigned char pad0[0x4e0];
    Bytes3beef0<6> field_4e0;         // +4e0
    unsigned char pad4e6[0xa];
    Bytes3beef0<8> field_4f0;         // +4f0
    unsigned char pad4f8[0x8];
    Bytes3beef0<6> field_500;         // +500
    unsigned char pad506[0xa];
    Bytes3beef0<8> field_510;         // +510
    unsigned char pad518[0x2f];
    unsigned char field_547;          // +547
    unsigned char pad548[0x2b8];
    Layout3bdbf0* layout;             // +800
    unsigned char pad808[0x158];
    Pane3bdbf0* panes_960[2];         // +960
    unsigned char pad970[0x10];
    Pane3bdbf0* panes_980[2];         // +980
    unsigned char pad990[0xb0];
    Pane3bdbf0* sources_a40[4];       // +a40

    Pane3bdbf0* find(const char* name) { return layout->root->find_pane(name, true); }
    void show_line(int line, unsigned char visible);
    void refresh_lines();
};


extern const char* const kLine3Names_bdb860[3] __attribute__((visibility("hidden")));

static inline void show_line3(Menu3bdbf0* m) {
    m->find(kLine300_7db832)->flags |= 1;
    m->find(kLine301_7db83c)->flags |= 1;
    m->find(kLine302_7db846)->flags |= 1;
    m->find(kLine303_7db850)->flags &= ~1;
}

static inline Float3_3beef0 get_translate(const Pane3bdbf0* p) {
    return p->translate;
}

static inline void copy_translate(Pane3bdbf0* dst, Pane3bdbf0* src) {
    dst->translate = get_translate(src);
    dst->flags |= 0x10;
}

// 0x71003beef0
void Menu3bdbf0::refresh_lines() {
    static Color3bdbf0 colors[4] = {{0xff, 0xff, 0xff, 0xff}, {0xff, 0xff, 0xff, 0x00}, {0xff, 0xff, 0xff, 0xff},
                                    {0xff, 0xff, 0xff, 0x00}};
    bool lit[3] = {};
    bool any = false;
    if (field_4e0[0] && field_500[0]) {
        any = true;
        lit[0] = true;
    }
    if (field_4e0[2] && field_500[2]) {
        any = true;
        lit[1] = true;
    }
    if (field_4e0[4] && field_500[4]) {
        any = true;
        lit[2] = true;
    }
    bool dlc0;
    if ((field_4f0[0] && field_510[0]) || (field_4f0[4] && field_510[4])) {
        dlc0 = true;
    } else {
        dlc0 = false;
    }
    bool dlc1;
    if ((field_4f0[1] && field_510[1]) || (field_4f0[5] && field_510[5])) {
        dlc1 = true;
    } else {
        dlc1 = false;
    }
    if (any) {
        show_line3(this);
        show_line3(this);
        show_line3(this);
        for (int i = 0; i < 3; i++) {
            if (!lit[i]) {
                const char* name = kLine3Names_bdb860[i];
                find(name)->set_vtx_color(0, colors[0]);
                find(name)->set_vtx_color(1, colors[1]);
                find(name)->set_vtx_color(2, colors[2]);
                find(name)->set_vtx_color(3, colors[3]);
            }
        }
    }
    if (dlc0) {
        show_line(0x14, 1);
        copy_translate(panes_960[0], sources_a40[0]);
        copy_translate(panes_960[1], sources_a40[1]);
        find(kLine300_7db832)->flags &= ~1;
        find(kLine04_7db85a)->flags &= ~1;
        find(kLine700_7db872)->flags &= ~1;
    }
    if (dlc1) {
        show_line(0x15, 1);
        copy_translate(panes_980[0], sources_a40[2]);
        copy_translate(panes_980[1], sources_a40[3]);
        find(kLine302_7db846)->flags &= ~1;
        find(kLine06_7db86a)->flags &= ~1;
        find(kLine702_7db886)->flags &= ~1;
    }
}
