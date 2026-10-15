// Fifth session, in progress: 0x71003b4e98 (2,576 bytes), the mode menu's build (eight item slots, the layout
// load, an optional extra item, then seven items, each with five animations), drafted on top of
// misc/s5_functions02.cpp (its Pane type gains rotate/scale and slots 13-16; 3bd1d8, 3bdbf0, 3beef0 and 448544
// are unaffected). Same size, 6 instructions off when registers are abstracted.
// Settled: the anim creation is an inlined CreateAnimTransform (the resource block tested before the allocation,
// a nothrow class operator new, the base constructor out of line and the derived one inline with the vtable
// through the GOT, an nn::util-style LinkPrev push-back, then the virtual SetResource); the pane setters each
// reload items[count]; set_shown as if/else (the csel of orr/and); the two colours are GOT globals; the message
// manager and its data are loaded after &items[count] and before the item's id (set_texts, always_inline). The
// loop-carried y is a union { float f; int i; } whose int view is written into the translate (main's idea: an
// integer access to the whole slot makes SROA type it i32, so the phi lives in a GPR with fmov around the fadd);
// the non-extra start is 224.40001f (0x43606667); the last loop's index is an int (a pointer induction variable).
// Still off: in the extra item's block, the scale constant is materialised before the first setter in the
// original and the translate's x is stored after the flags; here the anim-name table's adrp is scheduled there and
// two registers swap. Shapes tried with identical results: the translate through the int view, its fields in
// another order, a make_pos helper, a named constant for the scale.
// Maps for tools/s5/sbs.py (name=address): got:gMgr_c22a00=0x7100c22a00 got:gApp_c21db0=0x7100c21db0
//   got:gMsg_c2b3f8=0x7100c2b3f8 got:kColorOn_c2b440=0x7100c2b440 got:kColorOff_c2b438=0x7100c2b438
//   got:_ZTV10Anim3b4e98=0x7100c2a698 kModeMenuBflyt_7db2f6=0x71007db2f6 kModeMenu_740e41=0x7100740e41
//   kMenuTxtOff_7db306=0x71007db306 kMenuTxtOn_7db313=0x71007db313 kAnimNames_bdb370=0x7100bdb370
//   kMsgOff_7e3ca8=0x71007e3ca8 kMsgOn_7e3cc8=0x71007e3cc8 _ZN14AnimInfo3b4e98C1EPv=0x71005cfac8
//   _ZN12Layout3b4e989find_animEPKc=0x71005d4fec _ZN14AnimBase3b4e98C2Ev=0x71005d026c
//   _ZN14AnimBase3b4e98nwEm=0x71005d4380 _ZN14ItemPane3b4e98C1Ev=0x71005d9690 _ZN14ItemPane3b4e98nwEm=0x71005d4380
//   _ZN9Mgr3b4e984loadEPP12Layout3b4e98iPKc=0x71001e2360 _ZN9Mgr3b4e986attachEPvS0_=0x71001e26dc
//   _ZN9Mgr3b4e9815attach_resourceEPv=0x71001e26e0 _ZN9Mgr3b4e984syncEv=0x71001e26e8
//   _ZN12MsgMgr3b4e983getEi=0x71003c58c8 _Z17clone_pane_5dec80P10Pane3bdbf0Pv=0x71005dec80
//   _Z16add_child_5da17cP10Pane3bdbf0S0_=0x71005da17c _Z16next_pane_5dec3cP10Pane3bdbf0=0x71005dec3c
//   _Z15set_text_1f7fe4P10Pane3bdbf0PvS1_PKt=0x71001f7fe4 _ZN10Item3b4e986updateEv=0x71003b58a8
//   .rodata.cst4=0x710073b000
// with --name _ZN14ModeMenu3b4e985buildEv.

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
extern const char kArwU_7d5b66[] __attribute__((visibility("hidden")));
extern const char kArwL_7d5b6c[] __attribute__((visibility("hidden")));
extern const char kArwR_7d5b72[] __attribute__((visibility("hidden")));
extern const char kArwD_7d5b78[] __attribute__((visibility("hidden")));
extern const char* const kLine3Names_bdb860[3] __attribute__((visibility("hidden")));

// A constructor, so a function-local static array of colours gets a guarded initialisation (3beef0).
struct Color3bdbf0 {
    unsigned char r, g, b, a;
    Color3bdbf0(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_) : r(r_), g(g_), b(b_), a(a_) {}
};

// A byte array read through an align-1 type, so adjacent flag loads are not merged into one wider load.
template <int N>
struct Bytes3bdbf0 {
    unsigned char v[N];
    unsigned char operator[](int i) const { return v[i]; }
};

struct Float3_3bdbf0 {
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
    virtual void slot_13();
    virtual void slot_14();
    virtual void slot_15();
    virtual void bind_anim(struct Anim3b4e98* anim, bool a, bool b);
    unsigned char pad8[0x28];
    Float3_3bdbf0 translate;          // +30
    Float3_3bdbf0 rotate;             // +3c
    float scale[2];                   // +48
    unsigned char pad50[0x8];
    unsigned char flags;              // +58

    void set_visible(bool visible) { flags = (flags & ~1) | (visible & 1); }
    void set_translate(const Float3_3bdbf0& t) {
        translate = t;
        flags |= 0x10;
    }
    void set_rotate(const Float3_3bdbf0& r) {
        rotate = r;
        flags |= 0x10;
    }
    void set_scale(float x, float y) {
        scale[0] = x;
        scale[1] = y;
        flags |= 0x10;
    }
    void set_shown(bool shown) {
        if (shown) {
            flags |= 1;
        } else {
            flags &= ~1;
        }
    }
};

union YBits3b4e98 {
    float f;
    int i;
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
    unsigned char pad0[0x3c];
    int slot_kind[32];                // +3c
    unsigned char padbc[0x420];
    Bytes3bdbf0<32> has;              // +4dc
    Bytes3bdbf0<32> owned;            // +4fc
    unsigned char pad51c[0x20];
    int stage;                        // +53c
    unsigned char pad540[7];
    unsigned char all_open;           // +547
    unsigned char pad548[0x2b8];
    Layout3bdbf0* layout;             // +800
    unsigned char pad808[0x158];
    Pane3bdbf0* panes_960[2];         // +960
    unsigned char pad970[0x10];
    Pane3bdbf0* panes_980[2];         // +980
    unsigned char pad990[0xb0];
    Pane3bdbf0* sources_a40[4];       // +a40
    unsigned char pada60[0xb61c8];
    int kinds[32];                    // +b6c28

    Pane3bdbf0* find(const char* name) { return layout->root->find_pane(name, true); }
    // The two forms of the same test: the first tests the stage's flag first, the second the all-open flag (so
    // in a run of them the all-open load is shared and every test after it is threaded on its value).
    bool is_open(int i) { return has[i] && (all_open || owned[i]); }
    bool can_go(int i) { return all_open ? has[i] != 0 : has[i] && owned[i]; }
    void update_arrows();
    void show_line(int line, unsigned char visible);
    void refresh_lines();
};

// A stage id to its slot: ids from 0x20 (DLC stages 200 to 232 and 100) are shifted down, then two ranges swap.
static inline int stage_slot(int id) {
    if (id >= 0x20) {
        if (static_cast<unsigned>(id - 200) <= 0x20 || id == 100) {
            id -= 0x44;
        } else {
            id = 0;
        }
        // Written negated: the +5 arm is the else block, so the compare stays "< 9" and is reversed only by block
        // placement (cmp #9; b.hs), not "> 8".
        if (!(id >= 18 && id <= 26)) {
            if (id >= 27 && id <= 31) {
                id -= 9;
            }
        } else {
            id += 5;
        }
    }
    return id;
}

// The same remapping, for the kind table: a stage index below 0x20 is remapped too.
static inline int kind_slot(unsigned id) {
    int s = id;
    if (id >= 0x20) {
        if (static_cast<unsigned>(id - 200) <= 0x20 || id == 100) {
            s = id - 0x44;
        } else {
            s = 0;
        }
    }
    if (!(s >= 18 && s <= 26)) {
        if (s >= 27 && s <= 31) {
            s -= 9;
        }
    } else {
        s += 5;
    }
    return s;
}

// 0x71003bd1d8: places the four arrow panes and shows those that lead to an open stage from the current one.
void Menu3bdbf0::update_arrows() {
    find(kArwL_7d5b6c)->set_visible(false);
    find(kArwR_7d5b72)->set_visible(false);
    find(kArwU_7d5b66)->set_visible(false);
    find(kArwD_7d5b78)->set_visible(false);
    float z = find(kArwU_7d5b66)->translate.z;
    find(kArwU_7d5b66)->set_translate(Float3_3bdbf0{-200.0f, 230.0f, z});
    z = find(kArwD_7d5b78)->translate.z;
    find(kArwD_7d5b78)->set_translate(Float3_3bdbf0{-200.0f, -250.0f, z});

    int slot = stage_slot(stage);
    int cur = static_cast<unsigned>(slot) < 0x20 ? slot_kind[slot] : -1;
    if (is_open(20) || is_open(24)) {
        if (cur == 4 || cur == 5) {
            kinds[4] = 7;
            kinds[5] = 7;
        }
    } else {
        kinds[4] = 2;
        kinds[5] = 2;
    }
    if (is_open(21) || is_open(25)) {
        if (cur == 8 || cur == 9) {
            kinds[8] = 8;
            kinds[9] = 8;
        }
    } else {
        kinds[8] = 2;
        kinds[9] = 2;
    }

    switch (kinds[kind_slot(cur)]) {
    case 1:
        if (can_go(4) || can_go(6) || can_go(25) || can_go(8)) {
            find(kArwR_7d5b72)->set_visible(true);
        }
        break;
    case 2:
        if (can_go(3)) {
            find(kArwL_7d5b6c)->set_visible(true);
        }
        if (can_go(10)) {
            find(kArwR_7d5b72)->set_visible(true);
        }
        if (can_go(20) || can_go(24)) {
            find(kArwU_7d5b66)->set_visible(true);
        }
        if (can_go(21) || can_go(25)) {
            find(kArwD_7d5b78)->set_visible(true);
        }
        break;
    case 3:
        if (can_go(10)) {
            find(kArwL_7d5b6c)->set_visible(true);
        }
        if (can_go(13)) {
            find(kArwR_7d5b72)->set_visible(true);
        }
        break;
    case 4:
        if (can_go(13)) {
            find(kArwL_7d5b6c)->set_visible(true);
        }
        if (can_go(16)) {
            find(kArwR_7d5b72)->set_visible(true);
        }
        break;
    case 5:
        if (can_go(16)) {
            find(kArwL_7d5b6c)->set_visible(true);
        }
        if (can_go(23)) {
            find(kArwR_7d5b72)->set_visible(true);
        }
        break;
    case 6:
        find(kArwL_7d5b6c)->set_visible(true);
        break;
    case 7:
        if (can_go(24)) {
            find(kArwU_7d5b66)->set_visible(true);
        }
        if (can_go(6) || can_go(8) || can_go(21) || can_go(25)) {
            find(kArwD_7d5b78)->set_visible(true);
        }
        if (can_go(3)) {
            find(kArwL_7d5b6c)->set_visible(true);
        }
        if (can_go(10)) {
            find(kArwR_7d5b72)->set_visible(true);
        }
        break;
    case 8:
        find(kArwU_7d5b66)->set_visible(true);
        if (can_go(3)) {
            find(kArwL_7d5b6c)->set_visible(true);
        }
        if (can_go(10)) {
            find(kArwR_7d5b72)->set_visible(true);
        }
        break;
    case 9:
        find(kArwD_7d5b78)->set_visible(true);
        break;
    }
}

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
        bool shown = all_open ? (visible & 1) : (has[20] ? owned[20] != 0 : false);
        find(kLineDlc02_7db93a)->set_visible(shown);
        break;
    }
    case 0x15: {
        find(kLine302Dlc_7db8fa)->set_visible(visible & 1);
        find(kLine06Dlc_7db908)->set_visible(visible & 1);
        find(kLine702Dlc_7db914)->set_visible(visible & 1);
        bool shown = all_open ? (visible & 1) : (has[21] ? owned[21] != 0 : false);
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

static inline void show_line3(Menu3bdbf0* m) {
    m->find(kLine300_7db832)->flags |= 1;
    m->find(kLine301_7db83c)->flags |= 1;
    m->find(kLine302_7db846)->flags |= 1;
    m->find(kLine303_7db850)->flags &= ~1;
}

// A translate copied through a local into the const-reference setter: the local stays a stack temporary (no TBAA,
// so a store between its load and its store may alias the source), with z kept in a register when nothing is
// stored in between. As an inline function the local is promoted; as a macro it stays in this function's frame.
#define COPY_TRANSLATE(dst, src)                \
    do {                                        \
        Float3_3bdbf0 t_ = (src)->translate;    \
        (dst)->set_translate(t_);               \
    } while (0)

// 0x71003beef0: refreshes the lines of the third stage group and of the two DLC groups. The DLC flags start false
// and are set in one block shared by both tests; the first lookup of each unlit line is a direct virtual call
// with the name table read in its arguments (after the vtable load).
void Menu3bdbf0::refresh_lines() {
    static Color3bdbf0 colors[4] = {{0xff, 0xff, 0xff, 0xff}, {0xff, 0xff, 0xff, 0x00}, {0xff, 0xff, 0xff, 0xff},
                                    {0xff, 0xff, 0xff, 0x00}};
    bool lit[3] = {};
    bool any = false;
    if (has[4] && owned[4]) {
        any = true;
        lit[0] = true;
    }
    if (has[6] && owned[6]) {
        any = true;
        lit[1] = true;
    }
    if (has[8] && owned[8]) {
        any = true;
        lit[2] = true;
    }
    bool dlc0 = false;
    if ((has[20] && owned[20]) || (has[24] && owned[24])) {
        dlc0 = true;
    }
    bool dlc1 = false;
    if ((has[21] && owned[21]) || (has[25] && owned[25])) {
        dlc1 = true;
    }
    if (any) {
        show_line3(this);
        show_line3(this);
        show_line3(this);
        for (int i = 0; i < 3; i++) {
            if (!lit[i]) {
                layout->root->find_pane(kLine3Names_bdb860[i], true)->set_vtx_color(0, colors[0]);
                const char* name = kLine3Names_bdb860[i];
                find(name)->set_vtx_color(1, colors[1]);
                find(name)->set_vtx_color(2, colors[2]);
                find(name)->set_vtx_color(3, colors[3]);
            }
        }
    }
    if (dlc0) {
        show_line(0x14, 1);
        COPY_TRANSLATE(panes_960[0], sources_a40[0]);
        COPY_TRANSLATE(panes_960[1], sources_a40[1]);
        find(kLine300_7db832)->flags &= ~1;
        find(kLine04_7db85a)->flags &= ~1;
        find(kLine700_7db872)->flags &= ~1;
    }
    if (dlc1) {
        show_line(0x15, 1);
        COPY_TRANSLATE(panes_980[0], sources_a40[2]);
        COPY_TRANSLATE(panes_980[1], sources_a40[3]);
        find(kLine302_7db846)->flags &= ~1;
        find(kLine06_7db86a)->flags &= ~1;
        find(kLine702_7db886)->flags &= ~1;
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

extern const char kModeMenuBflyt_7db2f6[] __attribute__((visibility("hidden")));
extern const char kModeMenu_740e41[] __attribute__((visibility("hidden")));
extern const char kMenuTxtOff_7db306[] __attribute__((visibility("hidden")));
extern const char kMenuTxtOn_7db313[] __attribute__((visibility("hidden")));
extern const char* const kAnimNames_bdb370[5] __attribute__((visibility("hidden")));
extern const int kMsgOff_7e3ca8[] __attribute__((visibility("hidden")));
extern const int kMsgOn_7e3cc8[] __attribute__((visibility("hidden")));
extern const Color3bdbf0 kColorOn_c2b440;
extern const Color3bdbf0 kColorOff_c2b438;

// nn::util-style intrusive list node: prev, then next.
struct ListNode3b4e98 {
    ListNode3b4e98* prev;
    ListNode3b4e98* next;
    void link_prev(ListNode3b4e98* node) {
        ListNode3b4e98* last = node->prev;
        node->prev = prev;
        last->next = this;
        prev->next = node;
        prev = last;
    }
};

struct AnimInfo3b4e98 {
    void* f0;
    void* block;                      // +8
    void* f10;
    void* f18;
    AnimInfo3b4e98(void* res);        // 0x71005cfac8
};

struct Layout3b4e98 {
    void* f0;
    ListNode3b4e98 anims;             // +8
    Pane3bdbf0* root;                 // +18
    unsigned char pad20[0x20];
    void* accessor;                   // +40
    void* find_anim(const char* name);        // 0x71005d4fec
};

struct AnimBase3b4e98 {
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();
    virtual void set_enable(bool enable);
    virtual void slot_5();
    virtual void slot_6();
    virtual void slot_7();
    virtual void set_resource(void* device, void* accessor, void* block);
    virtual void slot_9();
    virtual void slot_10();
    virtual void slot_11();
    virtual void slot_12();
    virtual void slot_13();
    virtual void slot_14();
    virtual void slot_15();
    virtual void slot_16();
    virtual void slot_17();
    virtual void slot_18();
    virtual void slot_19();
    virtual void slot_20();
    virtual void slot_21();
    virtual void slot_22();
    virtual void slot_23();
    virtual void slot_24();
    virtual void slot_25();
    virtual void play();
    virtual void rewind();
    ListNode3b4e98 link;              // +8
    unsigned char pad18[0x30];
    AnimBase3b4e98();                 // 0x71005d026c
    static void* operator new(unsigned long size) throw();     // 0x71005d4380
};

struct Anim3b4e98 : AnimBase3b4e98 {
    void* field_48;                   // +48
    int field_50;                     // +50
    Anim3b4e98() : field_48(nullptr), field_50(0) {}
    virtual void key();
};

struct ItemPane3b4e98 : Pane3bdbf0 {
    unsigned char pad59[0x87];
    ItemPane3b4e98();                 // 0x71005d9690
    static void* operator new(unsigned long size) throw();     // 0x71005d4380
};

struct Mgr3b4e98 {
    void load(Layout3b4e98** layout, int id, const char* name);        // 0x71001e2360
    void attach(void* res, void* arg);        // 0x71001e26dc
    void attach_resource(void* res);        // 0x71001e26e0
    void sync();        // 0x71001e26e8
};
extern Mgr3b4e98* gMgr_c22a00;

struct Sys3b4e98 {
    unsigned char pad0[0x10];
    unsigned char device[0x10];       // +10
};
struct App3b4e98 {
    unsigned char pad0[0x2af8];
    Sys3b4e98* sys;                   // +2af8
};
extern App3b4e98* gApp_c21db0;

struct MsgMgr3b4e98 {
    unsigned char pad0[0x10];
    void* data;                       // +10
    const unsigned short* get(int id);        // 0x71003c58c8
};
extern MsgMgr3b4e98* gMsg_c2b3f8;

Pane3bdbf0* clone_pane_5dec80(Pane3bdbf0* pane, void* device);        // 0x71005dec80
void add_child_5da17c(Pane3bdbf0* parent, Pane3bdbf0* child);        // 0x71005da17c
Pane3bdbf0* next_pane_5dec3c(Pane3bdbf0* pane);        // 0x71005dec3c
void set_text_1f7fe4(Pane3bdbf0* pane, void* buf, void* data, const unsigned short* text);        // 0x71001f7fe4

static inline Anim3b4e98* create_anim(Layout3b4e98* layout, void* device, const AnimInfo3b4e98& info) {
    void* block = info.block;
    if (block == nullptr) {
        return nullptr;
    }
    Anim3b4e98* anim = new Anim3b4e98();
    if (anim != nullptr) {
        layout->anims.link_prev(&anim->link);
        anim->set_resource(device, layout->accessor, block);
    }
    return anim;
}

struct Item3b4e98 {
    Pane3bdbf0* pane;                 // +0
    Anim3b4e98* anims[5];             // +8
    unsigned char text_on[0x18];      // +30
    unsigned char text_off[0x18];     // +48
    int id;                           // +60
    void update();        // 0x71003b58a8
};

struct ModeMenu3b4e98 {
    unsigned char pad0[0x38];
    unsigned char lit[7];             // +38
    unsigned char has_extra;          // +3f
    unsigned char pad40[0x20];
    Layout3b4e98* layout;             // +60
    unsigned char pad68[0x8];
    unsigned char res_70[0x110];      // +70
    unsigned char res_180[0x110];     // +180
    Item3b4e98 items[8];              // +290
    unsigned char pad5d0[0x48];
    unsigned int count;               // +618
    unsigned char pad61c[0x10];
    unsigned char ready;              // +62c

    __attribute__((always_inline)) void set_texts(int index) {
        Item3b4e98& current = items[count];
        MsgMgr3b4e98* mgr = gMsg_c2b3f8;
        void* data = mgr->data;
        int id = current.id;
        const unsigned short* text = mgr->get(kMsgOff_7e3ca8[id]);
        Item3b4e98& item = items[index];
        set_text_1f7fe4(item.pane->find_pane(kMenuTxtOff_7db306, true), item.text_off, data, text);
        item.pane->find_pane(kMenuTxtOff_7db306, true)->set_shown(true);
        mgr = gMsg_c2b3f8;
        data = mgr->data;
        text = mgr->get(kMsgOn_7e3cc8[id]);
        set_text_1f7fe4(item.pane->find_pane(kMenuTxtOn_7db313, true), item.text_on, data, text);
        items[index].pane->find_pane(kMenuTxtOn_7db313, true)->set_shown(true);
    }
    void build();
};

// 0x71003b4e98
void ModeMenu3b4e98::build() {
    if (ready) {
        return;
    }
    layout = nullptr;
    for (int k = 0; k < 8; k++) {
        items[k].pane = nullptr;
        for (int j = 0; j < 5; j++) {
            items[k].anims[j] = nullptr;
        }
        items[k].id = 8;
    }
    count = 0;
    gMgr_c22a00->load(&layout, 0x41fe, kModeMenuBflyt_7db2f6);
    gMgr_c22a00->attach(res_70, nullptr);
    gMgr_c22a00->attach_resource(res_180);
    gMgr_c22a00->sync();
    void* device = gApp_c21db0->sys->device;
    layout->root->find_pane(kModeMenu_740e41, true)->set_shown(false);
    YBits3b4e98 y;
    if (has_extra == 1) {
        items[count].pane = new ItemPane3b4e98();
        Pane3bdbf0* copy = clone_pane_5dec80(layout->root->find_pane(kModeMenu_740e41, true), gApp_c21db0->sys->device);
        copy->set_shown(true);
        add_child_5da17c(items[count].pane, copy);
        add_child_5da17c(layout->root, items[count].pane);
        items[count].pane->set_shown(false);
        items[count].pane->set_scale(1.0f, 1.0f);
        items[count].pane->set_rotate(Float3_3bdbf0{0.0f, 0.0f, 0.0f});
        items[count].pane->set_translate(Float3_3bdbf0{-417.0f, 262.548f, 0.0f});
        for (int j = 0; j < 5; j++) {
            Layout3b4e98* l = layout;
            AnimInfo3b4e98 info(l->find_anim(kAnimNames_bdb370[j]));
            items[count].anims[j] = create_anim(l, device, info);
            items[count].pane->bind_anim(items[count].anims[j], true, true);
            if (items[count].anims[j] != nullptr) {
                items[count].anims[j]->set_enable(false);
            }
        }
        items[count].id = 7;
        set_texts(count);
        count++;
        y.f = 187.548f;
    } else {
        y.f = 224.40001f;
    }
    for (int i = 0; i < 7; i++) {
        items[count].pane = new ItemPane3b4e98();
        Pane3bdbf0* copy = clone_pane_5dec80(layout->root->find_pane(kModeMenu_740e41, true), gApp_c21db0->sys->device);
        copy->set_shown(true);
        add_child_5da17c(items[count].pane, copy);
        add_child_5da17c(layout->root, items[count].pane);
        items[count].pane->set_shown(count < 8);
        items[count].pane->set_scale(1.0f, 1.0f);
        items[count].pane->set_rotate(Float3_3bdbf0{0.0f, 0.0f, 0.0f});
        { Float3_3bdbf0 t; t.x = -417.0f; *reinterpret_cast<int*>(&t.y) = y.i; t.z = 0.0f; items[count].pane->set_translate(t); }
        if (copy != nullptr) {
            const Color3bdbf0& color = lit[i] ? kColorOn_c2b440 : kColorOff_c2b438;
            do {
                copy->set_vtx_color(0, color);
                copy->set_vtx_color(1, color);
                copy->set_vtx_color(2, color);
                copy->set_vtx_color(3, color);
                copy = next_pane_5dec3c(copy);
            } while (copy != nullptr);
        }
        for (int j = 0; j < 5; j++) {
            Layout3b4e98* l = layout;
            AnimInfo3b4e98 info(l->find_anim(kAnimNames_bdb370[j]));
            items[count].anims[j] = create_anim(l, device, info);
            items[count].pane->bind_anim(items[count].anims[j], true, true);
            if (items[count].anims[j] != nullptr) {
                items[count].anims[j]->set_enable(false);
            }
        }
        items[count].id = i;
        set_texts(count);
        count++;
        y.f -= 75.0f;
    }
    for (int k = 0; k < count; k++) {
        items[k].update();
        if (items[k].anims[4] != nullptr) {
            items[k].anims[4]->rewind();
        }
        if (items[k].anims[0] != nullptr) {
            items[k].anims[0]->play();
        }
        if (items[k].anims[0] != nullptr) {
            items[k].anims[0]->set_enable(true);
        }
    }
    ready = 1;
}
