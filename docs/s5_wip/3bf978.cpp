// Fifth session, in progress: 0x71003bf978 (3,060 bytes), the stage menu's status panel (the stage remap of 3bd1d8,
// seven rank animations from the rank table at 0x13c, two more from the stage record, the weapon text or rank, the
// check marks from the save data, the clear animations, the layout redraw with the mask pane's alpha kept, and the
// pending tilt), drafted on top of misc/s5_functions02.cpp. 3,056 bytes here, 174 instructions off when registers
// are abstracted. Settled: the call sequence, the fields, the check marks as if/else setters (csel of orr/and,
// unsigned-char results tested with tst #0xff), the remap. Still off: the rank-to-frame mapping's shape (the
// original keeps the -1 test as a branch into the hide block in the loop and the two record ranks, a select only
// for the weapon rank; 100 is clamped through the shared +1 block), the loop reloads each slot's pane after the
// animation calls (passing the slot by reference made it worse here, 3,136 B), and register choices from both.
// Maps for tools/s5/sbs.py (name=address): got:gWeaponTable_c2af58=0x7100c2af58 got:gMgr_c22a00=0x7100c22a00
//   got:gDelta_c22a28=0x7100c22a28 _ZN10Anim3bf9789frame_maxEv=0x71005ce178 _Z14get_db_20dfd0v=0x710020dfd0
//   _Z12touch_20d8f4P12Record3bf978=0x710020d8f4 _Z16weapon_of_1fd8a4i=0x71001fd8a4
//   _Z18weapon_text_379834PvjPt=0x7100379834 _Z15set_text_1f7fe4P10Pane3bdbf0PvS1_PKt=0x71001f7fe4
//   _ZN10Save3bf9787clearedEbii=0x71002038c0 _ZN10Save3bf9788has_itemEii=0x7100202eb0
//   _Z16get_save_204728v=0x7100204728 _ZN9Mgr3bf9788resourceEv=0x71001e26ec _ZN13Obj940_3bf9786updateEf=0x71003c0870
//   _ZN10Menu3bdbf013update_3c056cEb=0x71003c056c _ZN10Menu3bdbf012apply_3bccacEii=0x71003bccac .rodata=0x7100804404
// with --name _ZN10Menu3bdbf013update_statusEv.

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
    unsigned char pad8[0x28];
    Float3_3bdbf0 translate;          // +30
    Float3_3bdbf0 rotate;             // +3c
    unsigned char pad48[0x10];
    unsigned char flags;              // +58

    unsigned char alpha_59;           // +59
    void set_visible(bool visible) { flags = (flags & ~1) | (visible & 1); }
    void set_shown(bool shown) {
        if (shown) {
            flags |= 1;
        } else {
            flags &= ~1;
        }
    }
    void set_translate(const Float3_3bdbf0& t) {
        translate = t;
        flags |= 0x10;
    }
};

struct Layout3bdbf0 {
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
    virtual void draw(float delta);
    virtual void slot_12();
    virtual void slot_13();
    virtual void slot_14();
    virtual void slot_15();
    virtual void slot_16();
    virtual void slot_17();
    virtual void attach(void* res, int arg);
    unsigned char pad8[0x10];
    Pane3bdbf0* root;                 // +18
};

// Each colour is its own temporary, stored right before its call.
static inline void set_white(Pane3bdbf0* pane) {
    for (int i = 0; i < 4; i++) {
        pane->set_vtx_color(i, Color3bdbf0{0xff, 0xff, 0xff, 0xff});
    }
}

struct Anim3bf978 {
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();
    virtual void set_enable(bool enable);
    virtual void apply();
    virtual void slot_6();
    virtual void slot_7();
    virtual void slot_8();
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
    virtual void set_frame(float frame);
    virtual void slot_25();
    virtual void play();
    unsigned char pad8[0x18];
    float frame;                      // +20
    unsigned char pad24[0x20];
    unsigned char state;              // +44
    unsigned short frame_max();        // 0x71005ce178
};

struct Record3bf978 {
    unsigned char pad0[0x1c];
    short rank_1c;                    // +1c
    short rank_1e;                    // +1e
    short rank_20;                    // +20
    short weapon_22;                  // +22
};

struct Db3bf978 {
    virtual void slot_0();
    virtual void slot_1();
    virtual Record3bf978* get(int stage);
};
Db3bf978* get_db_20dfd0();        // 0x710020dfd0
void touch_20d8f4(Record3bf978* record);        // 0x710020d8f4
unsigned int weapon_of_1fd8a4(int id);        // 0x71001fd8a4
void* weapon_text_379834(void* table, unsigned int id, unsigned short* buf);        // 0x7100379834
void set_text_1f7fe4(Pane3bdbf0* pane, void* buf, void* data, const unsigned short* text);        // 0x71001f7fe4
extern void* gWeaponTable_c2af58;

struct Save3bf978 {
    unsigned char cleared(bool hard, int stage, int index);        // 0x71002038c0
    unsigned char has_item(int stage, int index);        // 0x7100202eb0
};
Save3bf978* get_save_204728();        // 0x7100204728

struct Mgr3bf978 {
    unsigned char pad0[0x1290];
    void* field_1290;                 // +1290
    void* resource();        // 0x71001e26ec
};
extern Mgr3bf978* gMgr_c22a00;
extern float gDelta_c22a28;

struct Obj940_3bf978 {
    void update(float t);        // 0x71003c0870
};



struct RankSlot3bf978 {
    Pane3bdbf0* pane;
    Anim3bf978* anim;
};

// A rank to its animation frame (-1: none).
static inline int rank_frame(int v) {
    if (v == 0x15) {
        return 0x12;
    }
    if (v == 0x18) {
        return 0x13;
    }
    if (v == 0x19) {
        return 0x14;
    }
    if (v == 100) {
        return 0x65;
    }
    int f = static_cast<unsigned>(v) < 0x1f ? v : 0;
    if (v >= 0xc) {
        return f + 1;
    }
    if (v == -1) {
        return -1;
    }
    return f;
}

static inline bool show_frame(Pane3bdbf0* pane, Anim3bf978*& anim, int f) {
    if (f < 0 || anim->frame_max() < f) {
        if (anim != nullptr) {
            anim->set_enable(false);
        }
        pane->flags &= ~1;
        return false;
    }
    if (anim != nullptr) {
        anim->set_frame(static_cast<float>(f));
        if (anim != nullptr) {
            anim->set_enable(true);
        }
    }
    pane->flags |= 1;
    return true;
}

struct Menu3bdbf0 {
    unsigned char pad0[0x3c];
    int slot_kind[32];                // +3c
    unsigned char padbc[0x80];
    int ranks[32][7];                 // +13c
    unsigned char pad4bc[0x20];
    Bytes3bdbf0<32> has;              // +4dc
    Bytes3bdbf0<32> owned;            // +4fc
    unsigned char pad51c[0x20];
    int stage;                        // +53c
    unsigned char pad540[7];
    unsigned char all_open;           // +547
    unsigned char has_extra;          // +548
    unsigned char pad549[0x2b7];
    Layout3bdbf0* layout;             // +800
    unsigned char pad808[0x138];
    Obj940_3bf978 obj_940;            // +940
    unsigned char pad941[0x1f];
    Pane3bdbf0* panes_960[2];         // +960
    unsigned char pad970[0x10];
    Pane3bdbf0* panes_980[2];         // +980
    unsigned char pad990[0xb0];
    Pane3bdbf0* sources_a40[4];       // +a40
    RankSlot3bf978 rank_slots[7];     // +a60
    RankSlot3bf978 rank_ad0;          // +ad0
    RankSlot3bf978 rank_ae0;          // +ae0
    Pane3bdbf0* pane_af0;             // +af0
    unsigned char padaf8[0x8];
    RankSlot3bf978 rank_b00;          // +b00
    unsigned char padb10[0x8];
    Pane3bdbf0* tilt_panes[8];        // +b18
    unsigned char padb58[0x18];
    Anim3bf978* anims_b70[12];        // +b70
    unsigned char padbd0[0x48];
    Pane3bdbf0* pane_c18;             // +c18
    unsigned char padc20[0x98];
    unsigned char text_cb8[0x18];     // +cb8
    unsigned char padcd0[0xb5f58];
    int kinds[32];                    // +b6c28
    unsigned char padb6ca8[0x4];
    unsigned char draw_b6cac;         // +b6cac
    unsigned char padb6cad[0x7];
    int pending_b6cb4;                // +b6cb4
    int pending_b6cb8;                // +b6cb8
    unsigned char padb6cbc[0x1c];
    float time_b6cd8;                 // +b6cd8

    Pane3bdbf0* find(const char* name) { return layout->root->find_pane(name, true); }
    // The two forms of the same test: the first tests the stage's flag first, the second the all-open flag (so
    // in a run of them the all-open load is shared and every test after it is threaded on its value).
    bool is_open(int i) { return has[i] && (all_open || owned[i]); }
    bool can_go(int i) { return all_open ? has[i] != 0 : has[i] && owned[i]; }
    void update_3c056c(bool flag);        // 0x71003c056c
    void apply_3bccac(int a, int b);        // 0x71003bccac
    void update_status();
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

extern const char kIconAnyone00_7db81b[] __attribute__((visibility("hidden")));
extern const char kWeaponPos01_7db9ca[] __attribute__((visibility("hidden")));
extern const char kMmFacePos03_7db6a1[] __attribute__((visibility("hidden")));
extern const char kIconAnyone01_7db9d8[] __attribute__((visibility("hidden")));
extern const char kIconDif01_7db9e7[] __attribute__((visibility("hidden")));
extern const char kCheck00_7db9f3[] __attribute__((visibility("hidden")));
extern const char kCheck01_7db9fc[] __attribute__((visibility("hidden")));
extern const char kCheck02_7dba05[] __attribute__((visibility("hidden")));
extern const char kCheck03_7dba0e[] __attribute__((visibility("hidden")));
extern const char kCheck04_7dba17[] __attribute__((visibility("hidden")));
extern const char kCheck05_7dba20[] __attribute__((visibility("hidden")));
extern const char kCheck06_7dba29[] __attribute__((visibility("hidden")));
extern const char kCheck07_7dba32[] __attribute__((visibility("hidden")));
extern const char kBgScenarioMaskL_7dba3b[] __attribute__((visibility("hidden")));

// 0x71003bf978
void Menu3bdbf0::update_status() {
    int slot = stage_slot(stage);
    int cur = static_cast<unsigned>(slot) < 0x20 ? slot_kind[slot] : -1;
    touch_20d8f4(get_db_20dfd0()->get(cur));
    for (int k = 0; k < 7; k++) {
        int s = stage_slot(stage);
        int rank = static_cast<unsigned>(s) < 0x20 ? ranks[s][k] : -1;
        show_frame(rank_slots[k].pane, rank_slots[k].anim, rank_frame(rank));
    }
    update_3c056c(true);
    if (show_frame(rank_ad0.pane, rank_ad0.anim, rank_frame(get_db_20dfd0()->get(cur)->rank_1e))) {
        rank_ad0.anim->apply();
    }
    if (show_frame(rank_ae0.pane, rank_ae0.anim, rank_frame(get_db_20dfd0()->get(cur)->rank_1c))) {
        rank_ae0.anim->apply();
    }
    pane_af0->flags &= ~1;
    rank_b00.pane->flags &= ~1;
    find(kIconAnyone00_7db81b)->flags |= 1;
    find(kWeaponPos01_7db9ca)->flags &= ~1;
    find(kMmFacePos03_7db6a1)->flags &= ~1;
    find(kIconAnyone01_7db9d8)->flags &= ~1;
    unsigned int weapon = weapon_of_1fd8a4(get_db_20dfd0()->get(cur)->weapon_22);
    short rank = get_db_20dfd0()->get(cur)->rank_20;
    int f = rank_frame(rank);
    if (weapon < 0x27f) {
        unsigned short buf[8];
        void* data = weapon_text_379834(gWeaponTable_c2af58, weapon, buf);
        set_text_1f7fe4(find(kWeaponPos01_7db9ca), text_cb8, data, buf);
        find(kWeaponPos01_7db9ca)->flags |= 1;
    } else if (static_cast<unsigned short>(rank) >= 100) {
        find(kIconAnyone01_7db9d8)->flags |= 1;
    } else {
        show_frame(rank_b00.pane, rank_b00.anim, f);
    }
    find(kIconDif01_7db9e7)->flags |= 1;
    find(kCheck00_7db9f3)->set_shown(get_save_204728()->cleared(false, cur, 1));
    find(kCheck01_7db9fc)->set_shown(get_save_204728()->cleared(false, cur, 0));
    find(kCheck02_7dba05)->set_shown(get_save_204728()->cleared(false, cur, 2));
    find(kCheck03_7dba0e)->set_shown(get_save_204728()->cleared(false, cur, 3));
    find(kCheck04_7dba17)->set_shown(get_save_204728()->has_item(cur, 0));
    find(kCheck05_7dba20)->set_shown(get_save_204728()->has_item(cur, 1));
    find(kCheck06_7dba29)->set_shown(get_save_204728()->has_item(cur, 2));
    if (has_extra) {
        if (!(pane_c18->flags & 1)) {
            pane_c18->flags |= 1;
        }
        bool got = get_save_204728()->has_item(cur, 3);
        if (got) {
            find(kCheck07_7dba32)->flags |= 1;
        } else {
            find(kCheck07_7dba32)->flags &= ~1;
        }
    } else {
        find(kCheck07_7dba32)->flags &= ~1;
    }
    Anim3bf978* first = anims_b70[0];
    if ((first->state & 1) && first->frame == static_cast<float>(first->frame_max())) {
        for (int k = 0; k < 12; k++) {
            if (anims_b70[k] != nullptr) {
                anims_b70[k]->play();
                if (anims_b70[k] != nullptr) {
                    anims_b70[k]->set_enable(false);
                }
            }
        }
        obj_940.update(time_b6cd8);
    }
    if (layout != nullptr && draw_b6cac) {
        bool restore = false;
        Pane3bdbf0* mask = nullptr;
        unsigned char alpha = 0;
        if (!tilt_panes[1]->pad8[0x24 - 8]) {
            mask = find(kBgScenarioMaskL_7dba3b);
            restore = true;
            if (mask != nullptr) {
                alpha = mask->alpha_59;
            }
        }
        layout->draw(gDelta_c22a28);
        if (restore && mask != nullptr) {
            mask->alpha_59 = alpha;
        }
        if (gMgr_c22a00->field_1290 != nullptr) {
            layout->attach(gMgr_c22a00->resource(), 0);
        }
    }
    if (pending_b6cb4 != -1 && tilt_panes[0]->rotate.x == 0.0f && tilt_panes[1]->rotate.x == 0.0f &&
        tilt_panes[2]->rotate.x == 0.0f && tilt_panes[3]->rotate.x == 0.0f && tilt_panes[4]->rotate.x == 0.0f &&
        tilt_panes[5]->rotate.x == 0.0f && tilt_panes[6]->rotate.x == 0.0f && tilt_panes[7]->rotate.x == 0.0f) {
        apply_3bccac(pending_b6cb4, pending_b6cb8);
        pending_b6cb4 = -1;
        pending_b6cb8 = -1;
    }
}
