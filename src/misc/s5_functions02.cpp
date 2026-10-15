// Large functions written by hand (fifth session), second unit. Struct, field and callee names are placeholders
// after the address and offset, as in the generated units; string literals are named after the text and their
// address (the linker merged two of them with other modules' strings). Status: matching/README.md.

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
