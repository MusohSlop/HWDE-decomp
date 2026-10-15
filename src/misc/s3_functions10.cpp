// Hand-written constructors (third session): classes with their members in the original's
// order. Names are descriptive placeholders. Status: matching/README.md.

extern "C" void* memset(void*, int, unsigned long);
extern "C" int snprintf(char* buf, unsigned long size, const char* format, ...);

struct Vec4f {
    float x, y, z, w;
};
typedef float f32x4 __attribute__((vector_size(16)));

struct GlobalTable {
    unsigned char pad[0x30];
    Vec4f v30;                     // +30
};
// Reached through the GOT slot at 0x7100c216f8.
extern GlobalTable gGlobalc216f8;

// 0x18 bytes, constructed out of line.
struct BufferSlot {
    BufferSlot();                  // 0x710003ce04
    unsigned char raw[0x18];
};

// 0x18 bytes; its five zeroed fields are merged into one 0x15-byte memset (three overlapping 8-byte stores).
struct ZeroRecord {
    ZeroRecord() : p(nullptr), q(0), r(0), s(0) {}
    void* p;
    long q;
    int r;
    char s;
};

// +37f0 of RecordBank. Its member initialisers run before its body's memset of the first array, so the record
// stores and the tail's memset come first.
struct RecordBlock {
    RecordBlock() : recs(), tail(), flag(false) { memset(data, 0, sizeof(data)); }
    unsigned char data[0xb005];    // +0
    ZeroRecord recs[9];            // +b008
    unsigned char tail[0x6d7];     // +b0e0
    unsigned char pad;
    unsigned char buf[0xdae];      // +b7b8: cleared by RecordBank's body
    bool flag;                     // +c566
};

// 0x60 bytes. The int at +30 is set first and again inside the -1 run at +28 (which becomes a 14-byte memset):
// the load of the table in between keeps the first store alive.
struct alignas(16) SlotState {
    SlotState() {
        i30 = -1;
        v0 = gGlobalc216f8.v30;
        v10 = (f32x4){0, 0, 0, 0};
        i20 = -1;
        s24 = -1;
        i28 = -1;
        i2c = -1;
        i30 = -1;
        s34 = -1;
        l38 = 0;
        i40 = -1;
        i44 = -1;
        c48 = 0;
        f4c = 0;
        c50 = 0;
        c51 = 0;
    }
    Vec4f v0;                      // +0
    f32x4 v10;                     // +10
    int i20;                       // +20
    short s24;                     // +24
    int i28;                       // +28
    int i2c;                       // +2c
    int i30;                       // +30
    short s34;                     // +34
    long l38;                      // +38
    int i40;                       // +40
    int i44;                       // +44
    char c48;                      // +48
    float f4c;                     // +4c
    char c50;                      // +50
    char c51;                      // +51
};

// 0xf0 bytes: a SlotState and its own fields. The floats keep their own base registers in the loop.
struct alignas(16) SlotEntry {
    SlotEntry() : head() {
        i60 = -1;
        i64 = -1;
        l68 = 0;
        l70 = 0;
        l78 = 0;
        i80 = -1;
        i84 = -1;
        i88 = -1;
        l90 = 0;
        i98 = -1;
        va0 = gGlobalc216f8.v30;
        ib0 = -1;
        ib4 = -1;
        fb8 = 6.2831855f;
        fbc = 0;
        ic0 = -1;
        ic4 = -1;
        ic8 = 0;
        icc = 0;
        id0 = -1;
        id4 = -1;
        id8 = -1;
        idc = 0;
        ie0 = -1;
    }
    SlotState head;                // +0
    int i60, i64;                  // +60
    long l68, l70, l78;            // +68
    int i80, i84, i88;             // +80
    long l90;                      // +90
    int i98;                       // +98
    int pad9c;
    Vec4f va0;                     // +a0
    int ib0, ib4;                  // +b0
    float fb8;                     // +b8: 2 pi
    float fbc;                     // +bc
    int ic0, ic4;                  // +c0
    int ic8, icc;                  // +c8
    int id0, id4, id8;             // +d0
    int idc;                       // +dc
    int ie0;                       // +e0
};

class RecordBank {
public:
    RecordBank();

    BufferSlot slots[11];          // +0
    int sizes[11];                 // +108
    int pad134;
    unsigned char buf138[0x36b8];  // +138
    RecordBlock block;             // +37f0
    SlotState states[71];          // +fd60
    int stateCount;                // +11800
    SlotEntry entriesA[100];       // +11810
    int entryCountA;               // +175d0
    SlotEntry entriesB[210];       // +175e0
    long l23ac0;                   // +23ac0
    int i23ac8;                    // +23ac8
    unsigned char pad23acc[0x84];
    short s23b50;                  // +23b50
};

// 0x71000193e8
RecordBank::RecordBank()
    : block(), states(), stateCount(0), entriesA(), entryCountA(0), entriesB(), l23ac0(0), i23ac8(0) {
    memset(buf138, 0, sizeof(buf138));
    memset(block.buf, 0, sizeof(block.buf));
    sizes[0] = 0x10b50;
    sizes[1] = 0xdb0;
    sizes[2] = 0xd00;
    sizes[3] = 0x1710;
    sizes[4] = 0xd60;
    sizes[5] = 0x510;
    sizes[6] = 0x9f0;
    sizes[7] = 0x1190;
    sizes[8] = 0x540;
    sizes[9] = 0x6a0;
    sizes[10] = 0x1200;
    s23b50 = 0;
}

class LayoutAnimation;
class IconTable;

class PaneBase;

struct GroupTranslate {
    int x;
    float y;
    int z;
};

class EffectGroup {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void v40();
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual EffectGroup* find(const char* name, int depth); // +60
    // By reference, so its loads are 4-byte aligned and GVN does not widen them into one 8-byte load.
    const GroupTranslate& translate() const { return *reinterpret_cast<const GroupTranslate*>(&x30); }
    void add(EffectGroup* child);                                           // 0x71005da17c
    void remove(EffectGroup* child);                                        // 0x71005da1b0
    void add(PaneBase* pane);                                               // 0x71005da17c
    EffectGroup* duplicate(void* root);                                     // 0x71005dec80
    void set_name(const char* name);                                        // 0x71005d9abc

    unsigned char pad8[0x10];
    EffectGroup* parent;      // +18
    unsigned char pad20[0x10];
    int x30;                  // +30
    float y34;                // +34
    int z38;                  // +38
    unsigned char pad3c[0xc];
    float scale48;            // +48
    float scale4c;            // +4c
    float size50;             // +50
    float size54;             // +54
    union {
        unsigned char flags58; // +58: bit 0 visible, bit 4 moved
        struct {
            unsigned char visible : 1;
            unsigned char : 7;
        };
    };
};

class LightEffectNode {
public:
    virtual void v00();
    LayoutAnimation* create_animation_3770(const char* name, bool loop);   // 0x71001e3770

    unsigned char pad8[0x10];
    EffectGroup* group;       // +18
};

class LightResource {
public:
    LightResource();                                                        // 0x71005d2744
    unsigned char pad[0x110];
};

class EffectManager {
public:
    void create_node(LightEffectNode** out, int id, const char* layout);    // 0x71001e2360
    void finish(int id);                                                    // 0x71001e22e4
    void attach(LightResource* resource, void* owner);                      // 0x71001e26dc
    void attach_resource(LightResource* resource);                          // 0x71001e26e0
    void flush();                                                           // 0x71001e26e4
    void sync();                                                            // 0x71001e26e8
};
// Reached through the GOT slot at 0x7100c22a00.
extern EffectManager* gEffectManager;

struct HandleState {
    long id;                  // +08
    short a;                  // +10
    short b;                  // +12

    HandleState() : id(-1), a(0), b(0) {}
};

// Layout handle; its vtable lives in the effect manager unit (GOT 0x7100c22f00).
class LayoutHandle : public HandleState {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
};

struct IconRect {
    unsigned short v[8];
};
struct IconSource {
    IconTable* table;
};
// Reached through the GOT slot at 0x7100c22bf0.
extern IconSource* gIconSource;
// Reached through the GOT slot at 0x7100c22c38.
extern const IconRect gIconRects[];
void apply_icon(EffectGroup* pane, LayoutHandle* handle, IconTable* table, const IconRect* rect); // 0x71001f7fe4

extern const char kLoadingLayout[] __attribute__((visibility("hidden")));     // 0x7100741e55
extern const char kLoadingAnim[] __attribute__((visibility("hidden")));       // 0x7100741e63
extern const char kTriforceAnim[] __attribute__((visibility("hidden")));      // 0x7100741e70
extern const char kLoadingDummy[] __attribute__((visibility("hidden")));      // 0x7100741e7e
extern const char kTriforce[] __attribute__((visibility("hidden")));          // 0x7100741e8c
extern const char kLoadingDummy00[] __attribute__((visibility("hidden")));    // 0x7100741e95

// 0x71001eeed4: the loading screen (loading.bflyt).
class LoadingScreen {
public:
    LoadingScreen();

    long value0;               // +0
    unsigned char value8;
    unsigned char value9;      // +9
    unsigned char pada[6];
    LightResource resource;    // +10
    LightEffectNode* node;     // +120
    LayoutAnimation* anim;     // +128
    LayoutHandle handle0;      // +130
    LayoutHandle handle1;      // +148
    EffectGroup* group160;     // +160: triforce_anim
    EffectGroup* group168;     // +168: loading_dummy
};

LoadingScreen::LoadingScreen() : value0(0), value9(0), node(nullptr) {
    gEffectManager->attach(&resource, nullptr);
    gEffectManager->create_node(&node, 0x41e7, kLoadingLayout);
    gEffectManager->flush();
    anim = node->create_animation_3770(kLoadingAnim, true);
    group160 = node->group->find(kTriforceAnim, 1);
    group168 = node->group->find(kLoadingDummy, 1);
    node->group->find(kTriforce, 1)->visible = false;
    apply_icon(group168, &handle0, gIconSource->table, &gIconRects[0xe]);
    apply_icon(node->group->find(kLoadingDummy00, 1), &handle1, gIconSource->table, &gIconRects[0xe]);
}

extern const char kSavingLayout[] __attribute__((visibility("hidden")));      // 0x7100741ea6
extern const char kSavingLoop[] __attribute__((visibility("hidden")));        // 0x7100741eb3
extern const char kSavingDummy[] __attribute__((visibility("hidden")));       // 0x7100741ebf
extern const char kSavingDummy00[] __attribute__((visibility("hidden")));     // 0x7100741ecc

// 0x71001f1f88: the saving screen (saving.bflyt).
class SavingScreen {
public:
    SavingScreen();

    int value0;                // +0
    int value4;
    int value8;
    int valuec;                // +c
    LightResource resource;    // +10
    LightEffectNode* node;     // +120
    LayoutAnimation* anim;     // +128
    LayoutHandle handle0;      // +130
    LayoutHandle handle1;      // +148
    EffectGroup* group160;     // +160: triforce_anim
    bool flag168;              // +168
};

SavingScreen::SavingScreen() : value0(0), valuec(0), node(nullptr), flag168(false) {
    gEffectManager->attach_resource(&resource);
    gEffectManager->create_node(&node, 0x41ed, kSavingLayout);
    gEffectManager->flush();
    anim = node->create_animation_3770(kSavingLoop, true);
    gEffectManager->finish(0x41ed);
    group160 = node->group->find(kTriforceAnim, 1);
    node->group->find(kTriforce, 1)->visible = false;
    apply_icon(node->group->find(kSavingDummy, 1), &handle0, gIconSource->table, &gIconRects[0x11]);
    apply_icon(node->group->find(kSavingDummy00, 1), &handle1, gIconSource->table, &gIconRects[0x11]);
}

extern const char kGetPieceLayout[] __attribute__((visibility("hidden")));    // 0x71007d7f58
extern const char kPiecePartsLayout[] __attribute__((visibility("hidden")));  // 0x71007d7fd0
extern const char kGetAnim[] __attribute__((visibility("hidden")));           // 0x71007d7fe2
extern const char kVIn[] __attribute__((visibility("hidden")));               // 0x71007db059
extern const char kVOut[] __attribute__((visibility("hidden")));              // 0x71007db05e
extern const char kTitlePlate[] __attribute__((visibility("hidden")));        // 0x7100740bbf
extern const char kPieceLine[] __attribute__((visibility("hidden")));         // 0x71007db064
extern const char kGetPiece[] __attribute__((visibility("hidden")));          // 0x7100740f46
extern const char kPieceFormat[] __attribute__((visibility("hidden")));       // 0x71007d7fbd
extern const char kWallpaperPiece[] __attribute__((visibility("hidden")));    // 0x71007d7fe6

// A menu screen built from one layout (base of the piece screen; constructor 0x710038c480).
class MenuScreen {
public:
    MenuScreen(int id, const char* layout, void* owner);                    // 0x710038c480
    virtual ~MenuScreen();
    void add_anim(int slot, const char* name, int flags);                   // 0x710038ccb0
    void place(float x, float y);                                           // 0x710038cc48

    LightEffectNode* node;    // +8
    unsigned char pad10[0x2258];
};

// One piece of the wallpaper (0x30 bytes; destructor 0x7100391fbc).
struct PieceSlot {
    PieceSlot() : node(nullptr), anim(nullptr) {
        gEffectManager->create_node(&node, 0x41fa, kPiecePartsLayout);
        anim = node->create_animation_3770(kGetAnim, true);
    }
    ~PieceSlot();

    LightEffectNode* node;    // +0
    LayoutAnimation* anim;    // +8
    EffectGroup* piece;       // +10: wallpaper_piece
    LayoutHandle handle;      // +18
};

// 0x7100391bd8: the get piece screen (get_piece.bflyt); its destructor is 0x7100392abc.
class GetPieceScreen : public MenuScreen {
public:
    GetPieceScreen();
    ~GetPieceScreen();

    PieceSlot pieces[20];     // +2268
    EffectGroup* line;        // +2628: piece_line
    int value2630;            // +2630
};

GetPieceScreen::GetPieceScreen() : MenuScreen(0x41fa, kGetPieceLayout, nullptr), line(nullptr), value2630(0) {
    gEffectManager->sync();
    add_anim(0, kVIn, 0);
    add_anim(4, kVOut, 0);
    place(375.0f, -44.0f);
    LightEffectNode* layout = node;
    gEffectManager->sync();
    layout->group->find(kTitlePlate, 1)->visible = false;
    line = layout->group->find(kPieceLine, 1);
    EffectGroup* title = layout->group->find(kGetPiece, 1);
    int x = title->translate().x;
    float y = title->translate().y + 21.0f;
    int z = title->translate().z;
    title = layout->group->find(kGetPiece, 1);
    title->x30 = x;
    title->y34 = y;
    title->z38 = z;
    title->flags58 |= 0x10;
    for (int i = 0; i < 20; i++) {
        char name[16] = {};
        snprintf(name, sizeof(name), kPieceFormat, i);
        EffectGroup* slot = layout->group->find(name, 1);
        pieces[i].piece = pieces[i].node->group->find(kWallpaperPiece, 1);
        EffectGroup* group = pieces[i].node->group;
        if (group->parent)
            group->parent->remove(group);
        slot->add(pieces[i].node->group);
    }
}

struct TrackVec2 {
    float x, y;
};

class PaneBase {
public:
    static void* operator new(unsigned long size) noexcept;                 // 0x71005d4380
    PaneBase();                                                             // 0x71005dc664
    virtual ~PaneBase();

    unsigned char pad8[0x50];
    union {
        unsigned char flags58; // +58
        struct {
            unsigned char visible : 1;
            unsigned char : 7;
        };
    };
    unsigned char pad59[0x107];

    void set_visible(bool on) { visible = on; }
};

// Text pane (0x180 bytes); vtable reached through the GOT slot at 0x7100c22f68.
class PanelPane : public PaneBase {
public:
    PanelPane() : value160(nullptr), value168(nullptr), value170(nullptr) {}
    ~PanelPane();

    void* value160;           // +160
    void* value168;           // +168
    void* value170;           // +170
    unsigned char pad178[8];
};

// Quad of a text line (0x88 bytes).
struct TrackLightTarget {
    unsigned char pad[0x88];

    TrackLightTarget();                                                     // 0x71001f0140
};

class TextRenderer {
public:
    void set_area(TrackVec2* pos, TrackVec2* size, int a, int b, int c);    // 0x71001e709c
    int draw(void* dest, const char* text, int line, int a, int alpha, float x,
             float y);                                                      // 0x71001e73c0

    unsigned char pad[0x20b8c];
    int value20b8c;           // +20b8c
    unsigned char pad20b90[8];
    int align;                // +20b98
    int value20b9c;           // +20b9c
    unsigned char pad20ba0[0x29];
    unsigned char value20bc9; // +20bc9
    unsigned char value20bca; // +20bca
};
// Reached through the GOT slot at 0x7100c22a30.
extern TextRenderer* gTextRenderer;

void set_pane_lines(PanelPane* pane, TrackLightTarget* lines, unsigned int count); // 0x71001e41d8
const char* message_text(int id);                                           // 0x7100217d64

struct LayoutRoot {
    unsigned char pad[0x10];
    unsigned char root[1];    // +10
};
struct ResourceLoaderView {
    unsigned char pad[0x2af8];
    LayoutRoot* layout;       // +2af8
};
// Reached through the GOT slot at 0x7100c21db0.
extern ResourceLoaderView* gResourceLoader;

class AnimPlayer {
public:
    void set_speed(float speed);                                            // 0x71001e4570
};
class LayoutAnimation {
public:
    unsigned char pad[0x18];
    AnimPlayer* player;       // +18
};

struct ByteBits;
unsigned char byte_bit_203bd8(ByteBits* bits, unsigned int index);                  // 0x7100203bd8
int piece_level_1f4e18(int count);                                          // 0x71001f4e18
int notify_1f47a8(int id, int value);                                       // 0x71001f47a8

// The collection the screen shows: pieces owned (+bd0) and pieces seen (+bd8).
struct PieceOwner {
    unsigned char pad[0xbd0];
    ByteBits* owned;          // +bd0
    ByteBits* seen;           // +bd8
    bool locked;              // +be0
};

extern const char kGetPieceEffLayout[] __attribute__((visibility("hidden")));  // 0x71007d7f68
extern const char kFrame[] __attribute__((visibility("hidden")));             // 0x71007d7f7c
extern const char kWallpaper[] __attribute__((visibility("hidden")));         // 0x71007d7f82
extern const char kCloneWallpaper[] __attribute__((visibility("hidden")));    // 0x71007d7f8c
extern const char kInAnim[] __attribute__((visibility("hidden")));            // 0x710073fffb
extern const char kOutAnim[] __attribute__((visibility("hidden")));           // 0x710074056c
extern const char kCompleteAnim[] __attribute__((visibility("hidden")));      // 0x71007d7f9c
extern const char kEffInAnim[] __attribute__((visibility("hidden")));         // 0x71007d7fa5
extern const char kEffLoopAnim[] __attribute__((visibility("hidden")));       // 0x71007d7fac
extern const char kEffOutAnim[] __attribute__((visibility("hidden")));        // 0x71007d7fb5
extern const char kFontTitle[] __attribute__((visibility("hidden")));         // 0x71007d7dca

// One piece of the new-piece screen (0x30 bytes): its node plays "get" at the speed of the node's scale.
struct NewPieceSlot {
    NewPieceSlot() : node(nullptr), anim(nullptr) {
        gEffectManager->create_node(&node, 0x41fa, kPiecePartsLayout);
        anim = node->create_animation_3770(kGetAnim, true);
        anim->player->set_speed(node->group->scale48);
    }

    LightEffectNode* node;    // +0
    LayoutAnimation* anim;    // +8
    EffectGroup* piece;       // +10: wallpaper_piece
    LayoutHandle handle;      // +18
};

static inline void reparent(EffectGroup* slot, LightEffectNode* const& node) {
    EffectGroup* group = node->group;
    if (group->parent)
        group->parent->remove(group);
    slot->add(node->group);
}

// 0x71002c63ac: the new piece screen (get_piece.bflyt and its effect layout); its destructor is 0x71002c6a58.
class Class2c6a58 {
public:
    explicit Class2c6a58(PieceOwner* owner);
    virtual ~Class2c6a58();

    PieceOwner* owner;               // +8
    int state;                       // +10
    LightEffectNode* layout;         // +18
    LightEffectNode* effect;         // +20
    int value28;                     // +28
    int value2c;                     // +2c
    int piece;                       // +30: first piece owned and not seen, or -1
    int level;                       // +34
    int value38;                     // +38
    LayoutAnimation* anims[6];       // +40: in, out, complete, eff_in, eff_loop, eff_out
    NewPieceSlot pieces[20];         // +70
    EffectGroup* title;              // +430: font_title
    TrackLightTarget lines[32];      // +438
    int line_count;                  // +1538
};

static inline int first_new_piece(PieceOwner* owner) {
    for (int i = 0; i < 300; i++) {
        if (byte_bit_203bd8(owner->owned, i) != byte_bit_203bd8(owner->seen, i) && byte_bit_203bd8(owner->owned, i))
            return i;
    }
    return -1;
}

Class2c6a58::Class2c6a58(PieceOwner* owner_)
    : owner(owner_), layout(nullptr), effect(nullptr), value28(11), value2c(0), piece(-1), level(0), value38(0),
      title(nullptr), line_count(0) {
    if (owner->locked)
        return;
    piece = first_new_piece(owner);
    if (piece < 0) {
        state = 2;
        return;
    }
    gEffectManager->create_node(&layout, 0x421a, kGetPieceLayout);
    gEffectManager->create_node(&effect, 0x421a, kGetPieceEffLayout);
    gEffectManager->sync();
    EffectGroup* frame = layout->group->find(kFrame, 1);
    EffectGroup* clone = layout->group->find(kWallpaper, 1)->duplicate(gResourceLoader->layout->root);
    if (frame && clone) {
        clone->set_name(kCloneWallpaper);
        frame->add(clone);
    }
    anims[0] = layout->create_animation_3770(kInAnim, false);
    anims[1] = layout->create_animation_3770(kOutAnim, false);
    anims[2] = layout->create_animation_3770(kCompleteAnim, false);
    anims[3] = effect->create_animation_3770(kEffInAnim, false);
    anims[4] = effect->create_animation_3770(kEffLoopAnim, false);
    anims[5] = effect->create_animation_3770(kEffOutAnim, false);
    anims[0]->player->set_speed(layout->group->scale48);
    anims[1]->player->set_speed(layout->group->scale48);
    anims[2]->player->set_speed(layout->group->scale48);
    anims[3]->player->set_speed(effect->group->scale48);
    anims[4]->player->set_speed(effect->group->scale48);
    anims[5]->player->set_speed(effect->group->scale48);
    for (int i = 0; i < 20; i++) {
        char name[16] = {};
        snprintf(name, sizeof(name), kPieceFormat, i);
        EffectGroup* slot = layout->group->find(name, 1);
        pieces[i].piece = pieces[i].node->group->find(kWallpaperPiece, 1);
        reparent(slot, pieces[i].node);
    }
    title = layout->group->find(kFontTitle, 1);
    TextRenderer* renderer = gTextRenderer;
    float size = title->size54 * layout->group->scale48;
    TrackVec2 pos = {};
    TrackVec2 area;
    area.x = size;
    area.y = size;
    renderer->set_area(&pos, &area, 0x52, 0x4e, 0);
    renderer->value20bc9 = 1;
    renderer->value20bca = 1;
    renderer->value20b8c = 0x53;
    renderer->value20b9c = 1;
    renderer->align = 2;
    line_count = renderer->draw(lines, message_text(0x4a), 0x20, 1, 0xff, 0.0f, 0.0f);
    PanelPane* pane = new PanelPane;
    set_pane_lines(pane, lines, line_count);
    pane->set_visible(line_count != 0);
    title->add(pane);
    level = piece / 20;
    notify_1f47a8(0x15, piece_level_1f4e18(level));
    value38 = 0;
    value28 = 0;
    state = 0;
}