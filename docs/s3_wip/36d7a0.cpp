// WIP (third session): 36d7a0, the select menu constructor, as a copy of misc/s3_functions09.cpp with SelectMenu at the end.
// 37 off with registers abstracted (2,900 bytes, size matches). Found: the ids and owner are a non-polymorphic base
// (stored before the vtable pointer); the group positions are written as integer bit patterns, so constant hoisting
// derives 475.0f from 214.0f's register as in the original; the 21-byte state is cleared by a body memset after the
// counts. Left: register and spill choices (the original keeps 2 more spill slots: &title_pos, the text lines).

// Hand-written giants (third session): constructors written as classes, their members in the original's order.
// Names are descriptive placeholders. Status: matching/README.md.

extern "C" void* memset(void*, int, unsigned long);

class AnimPlayer {
public:
    void set_speed(float speed);                                            // 0x71001e4570
};
class LayoutAnimation {
public:
    unsigned char pad[0x18];
    AnimPlayer* player;       // +18
};
class PaneBase;
class PanelPane;

struct TrackVec2 {
    float x, y;
};

static inline TrackVec2 make_vec2(float x, float y) {
    TrackVec2 v;
    v.x = x;
    v.y = y;
    return v;
}

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
    void add(EffectGroup* child);                                           // 0x71005da17c
    void add(PaneBase* pane);                                               // 0x71005da17c
    EffectGroup* duplicate(void* root);                                     // 0x71005dec80

    unsigned char pad8[0x10];
    EffectGroup* parent;      // +18
    unsigned char pad20[0x10];
    float offset30;           // +30
    float offset34;           // +34
    float offset38;           // +38
    unsigned char pad3c[0xc];
    float scale48;            // +48
    unsigned char pad4c[0xc];
    union {
        unsigned char flags58; // +58: bit 0 visible, bit 4 moved
        struct {
            unsigned char visible : 1;
            unsigned char : 7;
        };
    };
    unsigned char alpha59;    // +59

    // By reference, so its loads are 4-byte aligned and GVN does not widen them into one 8-byte load.
    const TrackVec2& translate() const { return *reinterpret_cast<const TrackVec2*>(&offset30); }
};

class LightEffectNode {
public:
    virtual void v00();
    LayoutAnimation* create_animation_3770(const char* name, bool loop);   // 0x71001e3770
    PanelPane* create_text_pane();                                          // 0x71001e4148

    unsigned char pad8[0x10];
    EffectGroup* group;       // +18
};

class EffectManager {
public:
    void create_node(LightEffectNode** out, int id, const char* layout);    // 0x71001e2360
    void sync();                                                            // 0x71001e26e8
    void finish(int id);                                                    // 0x71001e22e4
};
// Reached through the GOT slot at 0x7100c22a00.
extern EffectManager* gEffectManager;

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
    unsigned char alpha59;    // +59
    unsigned char pad5a;
    unsigned char : 2;
    unsigned char align : 2;  // +5b bits 2-3
    unsigned char : 4;
    unsigned char pad5c[0x104];

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
    unsigned char pad[0x58];
    float left;               // +58
    unsigned char pad5c[4];
    float right;              // +60
    unsigned char pad64[0x24];

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

void project_point(TrackVec2* point, float width, float height);            // 0x71001e412c
void set_pane_lines(PanelPane* pane, TrackLightTarget* lines, unsigned int count); // 0x71001e41d8
const char* message_text(int id);                                           // 0x7100217d64
// Stubs that return 0 and 5 (their bodies are compiled out).
int trace_begin(int id);                                                    // 0x71001763e8
int trace_end(int token);                                                   // 0x7100176418
void attach_group(LightEffectNode* node, EffectGroup* group);               // 0x71001f8224

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
class IconTable;
struct IconSource {
    IconTable* table;
};
// Reached through the GOT slot at 0x7100c22bf0.
extern IconSource* gIconSource;
// Reached through the GOT slot at 0x7100c22c38.
extern const IconRect gIconRects[];
void apply_icon(EffectGroup* pane, LayoutHandle* handle, IconTable* table, const IconRect* rect); // 0x71001f7fe4

class ScrollList {
public:
    ScrollList();                                                           // 0x71001f8700
    void setup(LightEffectNode* node, LayoutAnimation* anim, int count);   // 0x71001f8820

    unsigned char pad[0xa0];
};

class CharaFace {
public:
    explicit CharaFace(bool flag);                                          // 0x7100342280

    LightEffectNode* node;
    unsigned char pad8[0x48];
};

class AttributeIcon {
public:
    explicit AttributeIcon(int count);                                      // 0x71003166d4
    void reset();                                                           // 0x7100316804
    void set_group(EffectGroup* group);                                     // 0x7100316974
    void set_mode(int mode);                                                // 0x7100316a30

    unsigned char pad[0x18];
};

// Layout, pane and animation names, merged with other literals by the linker.
extern const char kChallengeRecordLayout[] __attribute__((visibility("hidden")));     // 0x71007da5b7
extern const char kIconGradeLayout[] __attribute__((visibility("hidden")));           // 0x71007da5ce
extern const char kNumAttackChgLayout[] __attribute__((visibility("hidden")));        // 0x71007da5df
extern const char kNumRupeeChgLayout[] __attribute__((visibility("hidden")));         // 0x71007da5f4
extern const char kNumRecordChallengeLayout[] __attribute__((visibility("hidden")));  // 0x71007da61d
extern const char kNumRecordChgLayout[] __attribute__((visibility("hidden")));        // 0x71007da608
extern const char kInAnim[] __attribute__((visibility("hidden")));                    // 0x710073fffb
extern const char kOutAnim[] __attribute__((visibility("hidden")));                   // 0x710074056c
extern const char kEffAnim[] __attribute__((visibility("hidden")));                   // 0x71007da638
extern const char kCharaNameTxtDummy[] __attribute__((visibility("hidden")));         // 0x71007da63c
extern const char kCharaFacePos[] __attribute__((visibility("hidden")));              // 0x71007da651
extern const char kCharaFace2pPos[] __attribute__((visibility("hidden")));            // 0x71007da660
extern const char kPadZlDummy[] __attribute__((visibility("hidden")));                // 0x71007da672
extern const char kPadZrDummy[] __attribute__((visibility("hidden")));                // 0x71007da67f
extern const char kGradeDummy[] __attribute__((visibility("hidden")));                // 0x71007d5bd7
extern const char kGradeAnim[] __attribute__((visibility("hidden")));                 // 0x71007d7c7b
extern const char kNumberAnim[] __attribute__((visibility("hidden")));                // 0x71007da450
// Seventeen pane names, icon_attribute_pos to font_2p.
extern const char* const kChallengeRecordPanes[] __attribute__((visibility("hidden"))); // 0x7100bd7210

// 0x71003447f0: the challenge record screen (challenge_record.bflyt, 0xe5f0 bytes; 349210 builds it with flag false).
class ChallengeRecordScreen {
public:
    explicit ChallengeRecordScreen(bool flag);

    LightEffectNode* layout;          // +00: challenge_record
    LightEffectNode* grade_icon;      // +08: icon_grade
    LightEffectNode* attack_numbers;  // +10: num_attack_chg
    LightEffectNode* rupee_numbers;   // +18: num_rupee_chg
    LightEffectNode* record_numbers;  // +20: num_record_challenge or num_record_chg
    PanelPane* texts[15];             // +28
    PanelPane* captions[2];           // +a0: under font_1p and font_2p
    ScrollList attack_list;           // +b0
    ScrollList rupee_list;            // +150
    ScrollList record_lists[7];       // +1f0
    LayoutAnimation* anims[9];        // +650: in, out (or in, out, eff with the flag), grade, three number
    EffectGroup* parts[6];            // +698: chara_name_txt_dummy, chara_face_pos, chara_face_2p_pos,
                                      //       pad_zl_dummy, pad_zr_dummy, grade_dummy
    EffectGroup* grades[3];           // +6c8: copies of grade_dummy
    LayoutHandle handles[6];          // +6e0: -, three grades, ZL, ZR
    TrackLightTarget lines0[32];      // +770: text lines, 32 per pane
    TrackLightTarget lines1[32];      // +1870
    TrackLightTarget lines2[32];      // +2970
    TrackLightTarget lines3[32];      // +3a70
    TrackLightTarget lines4[32];      // +4b70
    TrackLightTarget lines5[32];      // +5c70
    TrackLightTarget lines6[32];      // +6d70
    TrackLightTarget lines7[32];      // +7e70
    TrackLightTarget lines8[32];      // +8f70
    TrackLightTarget lines9[32];      // +a070
    TrackLightTarget lines10[32];     // +b170
    TrackLightTarget lines11[32];     // +c270
    TrackLightTarget lines12[32];     // +d370
    CharaFace face_1p;                // +e470
    CharaFace face_2p;                // +e4c0
    AttributeIcon attribute;          // +e510
    EffectGroup* positions[17];       // +e528: kChallengeRecordPanes
    unsigned char pade5b0[0x2f];
    unsigned char value_e5df;         // +e5df
    unsigned char flag;               // +e5e0
    unsigned char value_e5e1;         // +e5e1
    unsigned char pade5e2[2];
    int layout_id;                    // +e5e4
    unsigned char pade5e8[8];
};static_assert(sizeof(ChallengeRecordScreen) == 0xe5f0, "screen size");

// The pane is read again after each call (a reference to the member), and the count is signed.
static inline void show_text(PanelPane*& pane, TrackLightTarget* lines, int id) {
    TextRenderer* renderer = gTextRenderer;
    TrackVec2 pos = {};
    TrackVec2 size;
    size.x = 26.0f;
    size.y = 26.0f;
    renderer->set_area(&pos, &size, 0x41, 0x4e, 0);
    renderer->align = 2;
    int count = renderer->draw(lines, message_text(id), 0x20, 1, 0xff, 0.0f, 0.0f);
    set_pane_lines(pane, lines, count);
    pane->set_visible(count > 0);
}

// The flag byte is read before x is stored: the original merges only y and z into one 8-byte store.
static inline void place(EffectGroup* group, float y) {
    group->offset34 = y;
    group->offset38 = 0.0f;
    unsigned char flags = group->flags58;
    group->offset30 = 0.0f;
    group->flags58 = flags | 0x10;
}

ChallengeRecordScreen::ChallengeRecordScreen(bool flag_)
    : layout(nullptr), grade_icon(nullptr), attack_numbers(nullptr), rupee_numbers(nullptr), record_numbers(nullptr),
      parts(), face_1p(flag_), face_2p(flag_), attribute(1) {
    value_e5df = 0;
    flag = flag_;
    value_e5e1 = 0;
    layout_id = flag_ ? 0x4213 : 0x4204;
    gEffectManager->create_node(&layout, layout_id, kChallengeRecordLayout);
    gEffectManager->create_node(&grade_icon, 0x41e5, kIconGradeLayout);
    gEffectManager->create_node(&attack_numbers, layout_id, kNumAttackChgLayout);
    gEffectManager->create_node(&rupee_numbers, layout_id, kNumRupeeChgLayout);
    // Two calls, whose common tail branch folding merges: the original branches on the flag for the name.
    if (flag)
        gEffectManager->create_node(&record_numbers, layout_id, kNumRecordChallengeLayout);
    else
        gEffectManager->create_node(&record_numbers, layout_id, kNumRecordChgLayout);
    // Handle addresses taken here are kept (and spilled) until the icons are applied, as in the original.
    LayoutHandle* grade_handles = &handles[1];
    LayoutHandle* zr_handle = &handles[5];
    attack_numbers->group->flags58 &= ~1;
    rupee_numbers->group->flags58 &= ~1;
    record_numbers->group->flags58 &= ~1;
    LayoutHandle* zl_handle = &handles[4];
    if (flag) {
        anims[2] = layout->create_animation_3770(kInAnim, false);
        anims[3] = layout->create_animation_3770(kOutAnim, false);
        anims[4] = layout->create_animation_3770(kEffAnim, false);
    } else {
        anims[0] = layout->create_animation_3770(kInAnim, false);
        anims[1] = layout->create_animation_3770(kOutAnim, false);
    }
    parts[0] = layout->group->find(kCharaNameTxtDummy, 1);
    parts[1] = layout->group->find(kCharaFacePos, 1);
    parts[2] = layout->group->find(kCharaFace2pPos, 1);
    parts[3] = layout->group->find(kPadZlDummy, 1);
    parts[4] = layout->group->find(kPadZrDummy, 1);
    parts[5] = layout->group->find(kGradeDummy, 1);
    for (int i = 0; i < 17; i++)
        positions[i] = layout->group->find(kChallengeRecordPanes[i], 1);
    attribute.reset();
    attribute.set_group(positions[0]);
    attribute.set_mode(2);
    parts[1]->add(face_1p.node->group);
    parts[2]->add(face_2p.node->group);
    positions[2]->add(grade_icon->group);
    positions[3]->add(attack_numbers->group);
    positions[4]->add(rupee_numbers->group);
    positions[5]->add(record_numbers->group);
    anims[5] = grade_icon->create_animation_3770(kGradeAnim, false);
    anims[6] = attack_numbers->create_animation_3770(kNumberAnim, false);
    anims[7] = rupee_numbers->create_animation_3770(kNumberAnim, false);
    anims[8] = record_numbers->create_animation_3770(kNumberAnim, false);
    gEffectManager->finish(layout_id);
    gEffectManager->finish(0x41e5);
    trace_end(trace_begin(0));
    parts[3]->flags58 |= 1;
    parts[4]->flags58 |= 1;
    apply_icon(parts[3], zl_handle, gIconSource->table, &gIconRects[0x37]);
    apply_icon(parts[4], zr_handle, gIconSource->table, &gIconRects[0x3b]);
    parts[5]->flags58 &= ~1;
    for (int i = 0; i < 3; i++) {
        grades[i] = parts[5]->duplicate(gResourceLoader->layout->root);
        grades[i]->flags58 |= 1;
        parts[5]->parent->add(grades[i]);
        attach_group(layout, grades[i]);
        place(grades[i]->parent, i * -40.0f);
        apply_icon(grades[i], grade_handles + i, gIconSource->table, &gIconRects[0x1c + i]);
    }
    attack_list.setup(attack_numbers, anims[6], 12);
    rupee_list.setup(rupee_numbers, anims[7], 12);
    for (int i = 0; i < 7; i++)
        record_lists[i].setup(record_numbers, anims[8], 12);
    for (int i = 0; i < 15; i++)
        texts[i] = layout->create_text_pane();
    captions[0] = new PanelPane;
    captions[1] = new PanelPane;
    captions[0]->align = 2;
    captions[1]->align = 2;
    positions[15]->add(captions[0]);
    positions[16]->add(captions[1]);
    show_text(texts[7], lines2, 0xd3);
    show_text(texts[8], lines3, 0xcc);
    show_text(texts[9], lines4, 0xcd);
    show_text(texts[10], lines5, 0xce);
    show_text(texts[11], lines6, 0xd0);
    show_text(texts[12], lines7, 0xd1);
    show_text(texts[13], lines8, 0xd2);
    show_text(texts[14], lines9, 0xcf);
    // The captions are written out: through an inline helper the second one's anchor load moves above the renderer
    // load, and the registers after it change.
    {
        EffectGroup* anchor = positions[15];
        const TrackVec2& translate = anchor->translate();
        TrackVec2 pos = make_vec2(translate.x, translate.y);
        TextRenderer* renderer = gTextRenderer;
        project_point(&pos, 1920.0f, 1080.0f);
        TrackVec2 size;
        pos.x = 0.0f;
        pos.y = 0.0f;
        size.x = 16.800001f;
        size.y = 16.800001f;
        renderer->set_area(&pos, &size, 0x52, 0x4e, 0);
        renderer->value20bc9 = 1;
        renderer->value20bca = 1;
        renderer->value20b9c = 1;
        renderer->value20b8c = 0x53;
        renderer->align = 2;
        int count = renderer->draw(lines10, message_text(0x2c), 0x20, 1, 0xff, 0.0f, 0.0f);
        set_pane_lines(captions[0], lines10, count);
        captions[0]->set_visible(count > 0);
    }
    {
        TextRenderer* renderer = gTextRenderer;
        EffectGroup* anchor = positions[16];
        const TrackVec2& translate = anchor->translate();
        TrackVec2 pos = make_vec2(translate.x, translate.y);
        project_point(&pos, 1920.0f, 1080.0f);
        TrackVec2 size;
        pos.x = 0.0f;
        pos.y = 0.0f;
        size.x = 16.800001f;
        size.y = 16.800001f;
        renderer->set_area(&pos, &size, 0x5b, 0x4e, 0);
        renderer->value20bc9 = 1;
        renderer->value20bca = 1;
        renderer->value20b9c = 1;
        renderer->value20b8c = 0x41;
        renderer->align = 2;
        int count = renderer->draw(lines11, message_text(0x2d), 0x20, 1, 0xff, 0.0f, 0.0f);
        set_pane_lines(captions[1], lines11, count);
        captions[1]->set_visible(count > 0);
    }
    for (int i = 0; i < 15; i++)
        texts[i]->alpha59 = 0;
}
extern const char kSelectLayout[] __attribute__((visibility("hidden")));       // 0x71007dab98
extern const char kSelectFrameLayout[] __attribute__((visibility("hidden")));  // 0x71007dabab
extern const char kSelectPosA[] __attribute__((visibility("hidden")));         // 0x71007dabc0
extern const char kSelectPosB[] __attribute__((visibility("hidden")));         // 0x71007dabce
extern const char kSelectAnimA[] __attribute__((visibility("hidden")));        // 0x71007dabdc
extern const char kSelectAnimB[] __attribute__((visibility("hidden")));        // 0x71007dabed
extern const char kSelectAnimC[] __attribute__((visibility("hidden")));        // 0x71007dabff
extern const char kSelectAnimD[] __attribute__((visibility("hidden")));        // 0x71007dac10
extern const char kFrameAnimA[] __attribute__((visibility("hidden")));         // 0x71007dac22
extern const char kFrameAnimB[] __attribute__((visibility("hidden")));         // 0x71007dac2b
extern const char kFrameAnimC[] __attribute__((visibility("hidden")));         // 0x71007dac35
extern const char kFrameAnimD[] __attribute__((visibility("hidden")));         // 0x71007409da
extern const char kFrameAnimE[] __attribute__((visibility("hidden")));         // 0x71007dac3c
extern const char kEffectS[] __attribute__((visibility("hidden")));            // 0x71007da9f9
extern const char kEffectM[] __attribute__((visibility("hidden")));            // 0x71007daa02
extern const char kEffectL[] __attribute__((visibility("hidden")));            // 0x71007daa0b
extern const char kSelectTitle[] __attribute__((visibility("hidden")));        // 0x71007dac44
extern const char kSelectText[] __attribute__((visibility("hidden")));         // 0x71007dac51

// An entry of the select menu (0x1150 bytes), set up with its index and position.
class SelectEntry {
public:
    SelectEntry();                                                          // 0x7100370350
    void setup(int index, bool first, float x, float y);                   // 0x710036e2f4

    unsigned char data[0x1150];
};

class SelectPart {
public:
    SelectPart();                                                           // 0x7100383fbc

    unsigned char data[0x1de58];
};

// The group goes left by half the drawn text's width.
static inline void center_on(EffectGroup* group, const TrackLightTarget& line) {
    float left = line.left;
    float width = line.right - left;
    group->offset34 = 0.0f;
    group->offset38 = 0.0f;
    unsigned char flags = group->flags58;
    group->offset30 = (left + width) * -0.5f;
    group->flags58 = flags | 0x10;
}

// The menu's ids and owner: a base, stored before the menu's vtable pointer.
struct MenuState {
    explicit MenuState(void* owner_) : i8(1), ic(2), p10(nullptr), owner(owner_) {}

    int i8;                           // +08
    int ic;                           // +0c
    void* p10;                        // +10
    void* owner;                      // +18
};

// 0x710036d7a0: the select menu (vtable GOT 0x7100c2b060): three entries, two parts, the layout and its frame, a
// title and a text drawn and centred.
class SelectMenu : public MenuState {
public:
    explicit SelectMenu(void* owner);
    virtual void anchor();

    SelectEntry entry0;               // +20
    SelectEntry entry1;               // +1170
    SelectEntry entry2;               // +22c0
    SelectPart part0;                 // +3410
    SelectPart part1;                 // +21268
    LightEffectNode* layout;          // +3f0c0
    LightEffectNode* frame;           // +3f0c8
    LayoutAnimation* anim_c;          // +3f0d0
    LayoutAnimation* anim_d;          // +3f0d8
    LayoutAnimation* anim_a;          // +3f0e0
    LayoutAnimation* anim_b;          // +3f0e8
    LayoutAnimation* frame_anims[5];  // +3f0f0
    LayoutAnimation* effects[3];      // +3f118
    EffectGroup* title_pos;           // +3f130
    EffectGroup* text_pos;            // +3f138
    TrackLightTarget title_lines[32]; // +3f140
    TrackLightTarget text_lines[32];  // +40240
    PanelPane* title;                 // +41340
    PanelPane* text;                  // +41348
    unsigned char state[21];          // +41350
    int title_count;                  // +41368
    int text_count;                   // +4136c
};

SelectMenu::SelectMenu(void* owner_)
    : MenuState(owner_), layout(nullptr), frame(nullptr), title_pos(nullptr), text_pos(nullptr),
      title_count(0), text_count(0) {
    memset(state, 0, sizeof(state));
    entry0.setup(0, true, -606.0f, 353.0f);
    entry1.setup(1, false, -606.0f, 281.0f);
    entry2.setup(2, false, -606.0f, 169.0f);
    gEffectManager->create_node(&layout, 0x4203, kSelectLayout);
    gEffectManager->create_node(&frame, 0x4203, kSelectFrameLayout);
    gEffectManager->sync();
    {
        EffectGroup* pos = layout->group->find(kSelectPosA, 1);
        int* bits = reinterpret_cast<int*>(&pos->offset30);
        bits[0] = static_cast<int>(0xc1900000);
        bits[1] = 0x43560000;
        bits[2] = 0;
        pos->flags58 |= 0x10;
    }
    {
        EffectGroup* pos = layout->group->find(kSelectPosB, 1);
        int* bits = reinterpret_cast<int*>(&pos->offset30);
        bits[0] = 0x43ed8000;
        bits[1] = 0x43560000;
        bits[2] = 0;
        pos->flags58 |= 0x10;
    }
    anim_a = layout->create_animation_3770(kSelectAnimA, false);
    anim_b = layout->create_animation_3770(kSelectAnimB, false);
    anim_c = layout->create_animation_3770(kSelectAnimC, false);
    anim_d = layout->create_animation_3770(kSelectAnimD, false);
    frame_anims[0] = frame->create_animation_3770(kFrameAnimA, false);
    frame_anims[1] = frame->create_animation_3770(kFrameAnimB, false);
    frame_anims[2] = frame->create_animation_3770(kFrameAnimC, false);
    frame_anims[3] = frame->create_animation_3770(kFrameAnimD, false);
    frame_anims[4] = frame->create_animation_3770(kFrameAnimE, false);
    effects[0] = layout->create_animation_3770(kEffectS, false);
    effects[1] = layout->create_animation_3770(kEffectM, false);
    effects[2] = layout->create_animation_3770(kEffectL, false);
    anim_a->player->set_speed(layout->group->scale48);
    anim_b->player->set_speed(layout->group->scale48);
    anim_c->player->set_speed(layout->group->scale48);
    anim_d->player->set_speed(layout->group->scale48);
    title_pos = layout->group->find(kSelectTitle, 1);
    text_pos = layout->group->find(kSelectText, 1);
    TextRenderer* renderer = gTextRenderer;
    {
        TrackVec2 pos = {};
        TrackVec2 size;
        size.x = 28.0f;
        size.y = 28.0f;
        renderer->set_area(&pos, &size, 0x52, 0x4e, 0);
        renderer->value20bc9 = 1;
        renderer->value20bca = 1;
        renderer->value20b8c = 0x51;
        renderer->align = 2;
        int count = renderer->draw(title_lines, message_text(0xa6), 0x20, 1, 0xff, 0.0f, 0.0f);
        title_count = count;
        attach_group(layout, title_pos);
        center_on(title_pos->parent, title_lines[count - 1]);
    }
    title = new PanelPane;
    title_pos->add(title);
    title->align = 2;
    set_pane_lines(title, title_lines, title_count);
    {
        TrackVec2 pos = {};
        TrackVec2 size;
        size.x = 28.0f;
        size.y = 28.0f;
        renderer->set_area(&pos, &size, 0x52, 0x4e, 0);
        renderer->value20bc9 = 1;
        renderer->value20bca = 1;
        renderer->value20b8c = 0x51;
        renderer->align = 2;
        int count = renderer->draw(text_lines, message_text(0xa7), 0x20, 1, 0xff, 0.0f, 0.0f);
        text_count = count;
        attach_group(layout, text_pos);
        center_on(text_pos->parent, text_lines[count - 1]);
    }
    text = new PanelPane;
    text_pos->add(text);
    text->align = 2;
    set_pane_lines(text, text_lines, text_count);
}