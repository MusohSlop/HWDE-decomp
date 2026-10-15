// Hand-written constructors (third session), second unit: layouts whose animations are created inline
// (misc/anim_transform.h). Names are descriptive placeholders. Status: matching/README.md.

#include "misc/anim_transform.h"

extern "C" void* memset(void*, int, unsigned long);

class LayoutAnimation;
class IconTable;
class PaneBase;

class AnimPlayer {
public:
    void set_speed(float speed);                                            // 0x71001e4570
};
class LayoutAnimation {
public:
    unsigned char pad[0x18];
    AnimPlayer* player;       // +18
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
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void bind_animation(AnimTransform* anim, bool a, bool b); // +80
    void add(EffectGroup* child);                                           // 0x71005da17c
    void add(PaneBase* pane);                                               // 0x71005da17c
    EffectGroup* duplicate(void* root);                                     // 0x71005dec80

    unsigned char pad8[0x28];
    float offset30;           // +30
    float offset34;           // +34
    float offset38;           // +38
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

// A layout node: its animation list (+8), root group (+18) and resource accessor (+40).
class LightEffectNode {
public:
    virtual void v00();
    LayoutAnimation* create_animation_3770(const char* name, bool loop);   // 0x71001e3770
    void* find_animation(const char* name);                                // 0x71005d4fec

    AnimLink anims;           // +08
    EffectGroup* group;       // +18
    unsigned char pad20[0x20];
    void* accessor;           // +40
};

class EffectManager {
public:
    void create_node(LightEffectNode** out, int id, const char* layout);    // 0x71001e2360
    void flush();                                                           // 0x71001e26e4
    void sync();                                                            // 0x71001e26e8
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

static inline void* layout_root() {
    return gResourceLoader ? gResourceLoader->layout->root : nullptr;
}

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

struct TrackVec2 {
    float x, y;
};

class PaneBase {
public:
    static void* operator new(unsigned long size) noexcept;                 // 0x71005d4380
    PaneBase();                                                             // 0x71005dc664
    virtual ~PaneBase();

    unsigned char pad8[0x28];
    float offset30;           // +30
    float offset34;           // +34
    float offset38;           // +38
    unsigned char pad3c[0x1c];
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

static inline void move_y(PaneBase* pane, float dy) {
    pane->offset34 += dy;
    pane->flags58 |= 0x10;
}

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

    unsigned char pad[0x20b98];
    int align;                // +20b98
};
// Reached through the GOT slot at 0x7100c22a30.
extern TextRenderer* gTextRenderer;

void set_pane_lines(PanelPane* pane, TrackLightTarget* lines, unsigned int count); // 0x71001e41d8
const char* message_text(int id);                                           // 0x7100217d64
void attach_group(LightEffectNode* node, EffectGroup* group);               // 0x71001f8224

class ScrollList {
public:
    ScrollList();                                                           // 0x71001f8700
    void setup(LightEffectNode* node, LayoutAnimation* anim, int count);   // 0x71001f8820

    void* first;
    unsigned char pad8[0x98];
};

// The experience parts: a common base that takes its group, and four kinds built with a mode.
class ExpPart {
public:
    void attach(EffectGroup* group);                                        // 0x710030ff30
};
class ExpGauge : public ExpPart {
public:
    explicit ExpGauge(int mode);                                            // 0x710030ff4c
    void reset();                                                           // 0x71003100ac
    unsigned char pad[0x30];
};
class HeartGauge : public ExpPart {
public:
    explicit HeartGauge(int mode);                                          // 0x710031012c
    void reset();                                                           // 0x710031028c
    unsigned char pad[0x30];
};
class LevelNumber : public ExpPart {
public:
    explicit LevelNumber(int mode);                                         // 0x71003102fc
    void reset();                                                           // 0x7100310520
    unsigned char pad[0x180];
};
class HeartRow : public ExpPart {
public:
    explicit HeartRow(int mode);                                            // 0x7100310b88
    void reset();                                                           // 0x7100310d14
    unsigned char pad[0x238];
};

extern const char kShopExpLayout[] __attribute__((visibility("hidden")));       // 0x71007da967
extern const char kNumAttackLayout[] __attribute__((visibility("hidden")));     // 0x71007d7e4f
extern const char kNumAttackUpLayout[] __attribute__((visibility("hidden")));   // 0x71007da9bf
extern const char kWinExpIn[] __attribute__((visibility("hidden")));            // 0x71007da9d3
extern const char kWinExpOut[] __attribute__((visibility("hidden")));           // 0x71007da9de
extern const char kHeartEffLoop[] __attribute__((visibility("hidden")));        // 0x71007da9ea
extern const char kEffectS[] __attribute__((visibility("hidden")));             // 0x71007da9f9
extern const char kEffectM[] __attribute__((visibility("hidden")));             // 0x71007daa02
extern const char kEffectL[] __attribute__((visibility("hidden")));             // 0x71007daa0b
extern const char kNumAttack[] __attribute__((visibility("hidden")));           // 0x7100740d77
extern const char kNumAttackUp[] __attribute__((visibility("hidden")));         // 0x7100740d91
extern const char kFontAttack[] __attribute__((visibility("hidden")));          // 0x71007daa14
extern const char kTextLvDummy[] __attribute__((visibility("hidden")));         // 0x71007d8d2c
extern const char kTextExpDummy[] __attribute__((visibility("hidden")));        // 0x71007d9fb5
extern const char kTextLvmax[] __attribute__((visibility("hidden")));           // 0x71007d9fc4
extern const char kExp[] __attribute__((visibility("hidden")));                 // 0x71007d9fcf
extern const char kHeartPos[] __attribute__((visibility("hidden")));            // 0x710074005e
extern const char kNumLevelPos[] __attribute__((visibility("hidden")));         // 0x71007d8d3a
extern const char kHeartPosDlc[] __attribute__((visibility("hidden")));         // 0x71007daa20
extern const char kExpGaugePos[] __attribute__((visibility("hidden")));         // 0x71007da087
extern const char kHeartContainersPos[] __attribute__((visibility("hidden")));  // 0x71007da095
extern const char kHeartEff[] __attribute__((visibility("hidden")));            // 0x71007da9b5
extern const char kHeartBk[] __attribute__((visibility("hidden")));             // 0x71007da9ac

// 0x7100363040: the shop's experience screen (shop_exp.bflyt with the attack number layouts): 60 hearts, each a copy
// of heart_pos with its own heart_eff_loop transform.
class ShopExpScreen {
public:
    ShopExpScreen();

    LightEffectNode* layout;          // +00: shop_exp
    LightEffectNode* attack;          // +08: num_attack
    LightEffectNode* attack_up;       // +10: num_attack_up
    LayoutAnimation* anims[3];        // +18: win_exp_in, win_exp_out, heart_eff_loop
    LayoutAnimation* attack_anim;     // +30
    LayoutAnimation* attack_up_anim;  // +38
    LayoutAnimation* effects[3];      // +40: effect_s, effect_m, effect_l
    AnimTransformBasic* hearts[60];   // +58
    EffectGroup* num_attack_pos;      // +238
    EffectGroup* num_attack_up_pos;   // +240
    EffectGroup* font_attack;         // +248
    EffectGroup* text_lv;             // +250
    EffectGroup* text_exp;            // +258
    EffectGroup* text_lvmax;          // +260
    EffectGroup* exp;                 // +268
    EffectGroup* heart_pos;           // +270
    EffectGroup* num_level_pos;       // +278
    EffectGroup* heart_panes[60];     // +280
    TrackLightTarget lines[32];       // +460
    PanelPane* caption;               // +1560
    int line_count;                   // +1568
    ScrollList attack_list;           // +1570
    ScrollList attack_up_list;        // +1610
    LayoutHandle lv_handle;           // +16b0
    LayoutHandle exp_handle;          // +16c8
    LayoutHandle lvmax_handle;        // +16e0
    ExpGauge gauge;                   // +16f8
    HeartGauge heart_gauge;           // +1728
    LevelNumber level;                // +1758
    HeartRow heart_row;               // +18d8
    bool ready;                       // +1b10
    void* value1b18;                  // +1b18
};

ShopExpScreen::ShopExpScreen()
    : layout(nullptr), attack(nullptr), attack_up(nullptr), num_attack_pos(nullptr), num_attack_up_pos(nullptr), font_attack(nullptr), text_lv(nullptr), text_exp(nullptr), text_lvmax(nullptr), exp(nullptr), heart_pos(nullptr), num_level_pos(nullptr),
      line_count(0), gauge(0), heart_gauge(1),
      level(1), heart_row(1), value1b18(nullptr) {
    gEffectManager->create_node(&layout, 0x4203, kShopExpLayout);
    gEffectManager->create_node(&attack, 0x41e5, kNumAttackLayout);
    gEffectManager->create_node(&attack_up, 0x41e5, kNumAttackUpLayout);
    attack->group->visible = false;
    attack_up->group->visible = false;
    gEffectManager->sync();
    anims[0] = layout->create_animation_3770(kWinExpIn, false);
    anims[1] = layout->create_animation_3770(kWinExpOut, false);
    anims[2] = layout->create_animation_3770(kHeartEffLoop, true);
    effects[0] = layout->create_animation_3770(kEffectS, false);
    effects[1] = layout->create_animation_3770(kEffectM, false);
    effects[2] = layout->create_animation_3770(kEffectL, false);
    anims[0]->player->set_speed(layout->group->scale48);
    anims[1]->player->set_speed(layout->group->scale48);
    anims[2]->player->set_speed(layout->group->scale48);
    effects[0]->player->set_speed(layout->group->scale48);
    effects[1]->player->set_speed(layout->group->scale48);
    effects[2]->player->set_speed(layout->group->scale48);
    gEffectManager->flush();
    attack_anim = attack->create_animation_3770(kNumAttack, false);
    attack_up_anim = attack_up->create_animation_3770(kNumAttackUp, false);
    num_attack_pos = layout->group->find(kNumAttack, 1);
    num_attack_up_pos = layout->group->find(kNumAttackUp, 1);
    font_attack = layout->group->find(kFontAttack, 1);
    text_lv = layout->group->find(kTextLvDummy, 1);
    text_exp = layout->group->find(kTextExpDummy, 1);
    text_lvmax = layout->group->find(kTextLvmax, 1);
    exp = layout->group->find(kExp, 1);
    heart_pos = layout->group->find(kHeartPos, 1);
    num_level_pos = layout->group->find(kNumLevelPos, 1);
    layout->group->find(kHeartPosDlc, 1)->visible = false;
    {
        TextRenderer* renderer = gTextRenderer;
        TrackVec2 pos = {};
        TrackVec2 size;
        size.x = 28.0f;
        size.y = 28.0f;
        renderer->set_area(&pos, &size, 0x41, 0x4e, 0);
        renderer->align = 2;
        line_count = renderer->draw(lines, message_text(0x78), 0x20, 1, 0xff, 0.0f, 0.0f);
    }
    caption = new PanelPane;
    font_attack->add(caption);
    caption->align = 2;
    set_pane_lines(caption, lines, line_count);
    move_y(caption, -2.0f);
    num_attack_pos->add(attack->group);
    num_attack_up_pos->add(attack_up->group);
    apply_icon(text_lv, &lv_handle, gIconSource->table, &gIconRects[0x13]);
    apply_icon(text_exp, &exp_handle, gIconSource->table, &gIconRects[0x21]);
    apply_icon(text_lvmax, &lvmax_handle, gIconSource->table, &gIconRects[0x14]);
    gauge.reset();
    heart_gauge.reset();
    level.reset();
    heart_row.reset();
    ready = true;
    gauge.attach(layout->group->find(kExpGaugePos, 1));
    heart_gauge.attach(layout->group->find(kHeartContainersPos, 1));
    level.attach(num_level_pos);
    for (int i = 0; i < 60; i++) {
        heart_panes[i] = heart_pos->duplicate(gResourceLoader->layout->root);
        LightEffectNode* node = layout;
        hearts[i] = create_anim_transform(node, layout_root(), node->find_animation(kHeartEffLoop));
        heart_panes[i]->find(kHeartEff, 1)->bind_animation(hearts[i], true, true);
    }
    for (int i = 0; i < 60; i++)
        heart_pos->add(heart_panes[i]);
    heart_pos->find(kHeartBk, 1)->visible = false;
    heart_pos->find(kHeartEff, 1)->visible = false;
    gEffectManager->sync();
    attach_group(layout, heart_pos);
    heart_row.attach(heart_pos);
    heart_pos->flags58 |= 1;
    attack_list.setup(attack, attack_anim, 5);
    attack_up_list.setup(attack_up, attack_up_anim, 5);
}

extern const char kShopAttackLayout[] __attribute__((visibility("hidden")));    // 0x71007daa41
extern const char kNumDefenseLayout[] __attribute__((visibility("hidden")));    // 0x71007d8009
extern const char kNumSpeedLayout[] __attribute__((visibility("hidden")));      // 0x71007d6191
extern const char kNumRangeLayout[] __attribute__((visibility("hidden")));      // 0x71007d61a1
extern const char kWinAttackIn[] __attribute__((visibility("hidden")));         // 0x71007d9f7d
extern const char kWinAttackOut[] __attribute__((visibility("hidden")));        // 0x71007d9f8b
extern const char kAttackLoopA[] __attribute__((visibility("hidden")));         // 0x71007daa55
extern const char kAttackLoopB[] __attribute__((visibility("hidden")));         // 0x71007daa62
extern const char kNumDefense[] __attribute__((visibility("hidden")));          // 0x7100740d82
extern const char kNumSpeed[] __attribute__((visibility("hidden")));            // 0x7100740db7
extern const char kNumRange[] __attribute__((visibility("hidden")));            // 0x7100740dc1
extern const char kTextTitle[] __attribute__((visibility("hidden")));           // 0x71007da00f
extern const char kTextCaption[] __attribute__((visibility("hidden")));         // 0x71007da028
extern const char kTextNote[] __attribute__((visibility("hidden")));            // 0x71007da038
extern const char kTextLeft[] __attribute__((visibility("hidden")));            // 0x71007daa70
extern const char kTextRight[] __attribute__((visibility("hidden")));           // 0x71007daa7d
extern const char kNumPosA[] __attribute__((visibility("hidden")));             // 0x71007daa8c
extern const char kNumPosB[] __attribute__((visibility("hidden")));             // 0x71007d61d0
extern const char kTextBottom[] __attribute__((visibility("hidden")));          // 0x71007d7e75

static inline void move_y(EffectGroup* group, float dy) {
    group->offset34 += dy;
    group->flags58 |= 0x10;
}

static inline void show_if(PanelPane* pane, int count) {
    pane->visible = count != 0;
}

static inline void place_x(EffectGroup* group, float x) {
    group->offset30 = x;
    TrackVec2 yz = {};
    *reinterpret_cast<TrackVec2*>(&group->offset34) = yz;
    group->flags58 |= 0x10;
}

// 0x7100364878: the shop's attack screen (four number layouts with scroll lists, three text panes drawn from
// messages, two plain ones and a layout handle).
class ShopAttackScreen {
public:
    ShopAttackScreen();

    LightEffectNode* layout;          // +00
    LightEffectNode* attack;          // +08
    LightEffectNode* defense;         // +10
    LightEffectNode* speed;           // +18
    LightEffectNode* range;           // +20
    LayoutAnimation* anims[4];        // +28
    LayoutAnimation* effects[3];      // +48
    LayoutAnimation* number_anims[4]; // +60
    EffectGroup* title;               // +80
    EffectGroup* caption_pos;         // +88
    EffectGroup* note;                // +90
    EffectGroup* left;                // +98
    EffectGroup* right;               // +a0
    EffectGroup* num_pos_a;           // +a8
    EffectGroup* num_pos_b;           // +b0
    EffectGroup* bottom;              // +b8
    TrackLightTarget lines[64];       // +c0
    TrackLightTarget lines_b[64];     // +22c0
    TrackLightTarget more_lines[128]; // +44c0
    TrackLightTarget left_lines[32];  // +88c0
    TrackLightTarget right_lines[32]; // +99c0
    PanelPane* panes[5];              // +aac0
    int title_lines;                  // +aae8
    int caption_lines;                // +aaec
    int note_lines;                   // +aaf0
    int left_count;                   // +aaf4
    int right_count;                  // +aaf8
    ScrollList attack_list;           // +ab00
    ScrollList defense_list;          // +aba0
    ScrollList speed_list;            // +ac40
    ScrollList range_list;            // +ace0
    LayoutHandle handle;              // +ad80
};

ShopAttackScreen::ShopAttackScreen()
    : layout(nullptr), attack(nullptr), defense(nullptr), speed(nullptr), range(nullptr), note(nullptr), left(nullptr),
      right(nullptr), num_pos_a(nullptr), num_pos_b(nullptr), bottom(nullptr), title_lines(0), caption_lines(0),
      note_lines(0), left_count(0), right_count(0) {
    gEffectManager->create_node(&layout, 0x4203, kShopAttackLayout);
    gEffectManager->create_node(&attack, 0x41e5, kNumAttackLayout);
    gEffectManager->create_node(&defense, 0x41e5, kNumDefenseLayout);
    gEffectManager->create_node(&speed, 0x41e5, kNumSpeedLayout);
    gEffectManager->create_node(&range, 0x41e5, kNumRangeLayout);
    attack->group->visible = false;
    defense->group->visible = false;
    speed->group->visible = false;
    range->group->visible = false;
    place_x(layout->group, 153.0f);
    gEffectManager->sync();
    anims[0] = layout->create_animation_3770(kWinAttackIn, true);
    anims[1] = layout->create_animation_3770(kWinAttackOut, true);
    anims[2] = layout->create_animation_3770(kAttackLoopA, true);
    anims[3] = layout->create_animation_3770(kAttackLoopB, true);
    effects[0] = layout->create_animation_3770(kEffectS, false);
    effects[1] = layout->create_animation_3770(kEffectM, false);
    effects[2] = layout->create_animation_3770(kEffectL, false);
    gEffectManager->flush();
    number_anims[0] = attack->create_animation_3770(kNumAttack, false);
    number_anims[1] = defense->create_animation_3770(kNumDefense, false);
    number_anims[2] = speed->create_animation_3770(kNumSpeed, false);
    number_anims[3] = range->create_animation_3770(kNumRange, false);
    title = layout->group->find(kTextTitle, 1);
    caption_pos = layout->group->find(kTextCaption, 1);
    note = layout->group->find(kTextNote, 1);
    left = layout->group->find(kTextLeft, 1);
    right = layout->group->find(kTextRight, 1);
    num_pos_a = layout->group->find(kNumPosA, 1);
    num_pos_b = layout->group->find(kNumPosB, 1);
    bottom = layout->group->find(kTextBottom, 1);
    num_pos_a->add(attack->group);
    num_pos_a->add(defense->group);
    num_pos_b->add(speed->group);
    num_pos_b->add(range->group);
    gEffectManager->sync();
    attach_group(layout, caption_pos);
    TextRenderer* renderer = gTextRenderer;
    {
        TrackVec2 pos = {};
        TrackVec2 size;
        size.x = 28.0f;
        size.y = 28.0f;
        renderer->set_area(&pos, &size, 0x3c, 0x41, 0);
        renderer->align = 2;
        title_lines = renderer->draw(lines, message_text(0xa8), 0x40, 1, 0xff, 0.0f, 0.0f);
    }
    panes[0] = new PanelPane;
    title->add(panes[0]);
    move_y(panes[0], -2.0f);
    panes[0]->align = 2;
    set_pane_lines(panes[0], lines, title_lines);
    show_if(panes[0], title_lines);
    {
        TrackVec2 pos = {};
        TrackVec2 size;
        size.x = 28.0f;
        size.y = 28.0f;
        renderer->set_area(&pos, &size, 0x3c, 0x41, 0);
        renderer->align = 2;
        left_count = renderer->draw(left_lines, message_text(0x55), 0x20, 1, 0xff, 0.0f, 0.0f);
    }
    panes[3] = new PanelPane;
    left->add(panes[3]);
    move_y(panes[3], -2.0f);
    panes[3]->align = 2;
    set_pane_lines(panes[3], left_lines, left_count);
    show_if(panes[3], left_count);
    {
        TrackVec2 pos = {};
        TrackVec2 size;
        size.x = 28.0f;
        size.y = 28.0f;
        renderer->set_area(&pos, &size, 0x41, 0x4e, 0);
        renderer->align = 2;
        right_count = renderer->draw(right_lines, message_text(0x56), 0x20, 1, 0xff, 0.0f, 0.0f);
    }
    panes[4] = new PanelPane;
    right->add(panes[4]);
    panes[4]->align = 2;
    set_pane_lines(panes[4], right_lines, right_count);
    show_if(panes[4], right_count);
    panes[2] = new PanelPane;
    note->add(panes[2]);
    panes[2]->align = 2;
    panes[1] = new PanelPane;
    caption_pos->add(panes[1]);
    move_y(caption_pos, -2.0f);
    panes[1]->align = 2;
    attack_list.setup(attack, number_anims[0], 5);
    defense_list.setup(defense, number_anims[1], 5);
    speed_list.setup(speed, number_anims[2], 10);
    range_list.setup(range, number_anims[3], 10);
}
static inline void move_x(EffectGroup* pane, float dx) {
    pane->offset30 += dx;
    pane->flags58 |= 0x10;
}

void* load_global_334a04();                                 // 0x7100334a04
struct PageOverride;
// Reached through the GOT slot at 0x7100c22da8.
extern PageOverride* gPageOverride;

// Ids of the active page while no override is set (two branches: the getter and the global have different types).
inline bool page_ids() { return !load_global_334a04() && !gPageOverride; }

class RandomSource {
public:
    void roll();                                                            // 0x71003336c4
};
// Reached through the GOT slot at 0x7100c22c00.
extern RandomSource gRandomSource;
int controller_style_3ce218();                                              // 0x71003ce218

struct OptionOwner;

// A cursor sub-object of the options screens (0x30 bytes).
class MenuCursor {
public:
    MenuCursor();                                                           // 0x710037f550
    void init();                                                            // 0x710037cc88
    void set(float x, float y, float width);                                // 0x710037cd30

    unsigned char data[0x30];
};

// Base of the options screens (0xc0 bytes; vtable GOT 0x7100c2b2d0).
class OptionScreenBase {
public:
    explicit OptionScreenBase(OptionOwner* owner_) : owner(owner_), value78(0) {
        memset(state, 0, sizeof(state));
        flagb8 = 0;
        valueb0 = 0;
        cursor.init();
        cursor.set(150.0f, 126.0f, 223.0f);
    }
    virtual ~OptionScreenBase();

    OptionOwner* owner;               // +08
    unsigned char pad10[8];
    unsigned char state[0x60];        // +18
    long value78;                     // +78
    MenuCursor cursor;                // +80
    long valueb0;                     // +b0
    unsigned char flagb8;             // +b8
};

// An option line (0x2320 bytes): its base builds the menu_parts layout out of line, then the five animations.
class OptionPanelBase {
public:
    OptionPanelBase(int id, int id2, const char* layout, const char* name, int mode); // 0x710039d3fc
    virtual ~OptionPanelBase();

    LightEffectNode* node;            // +08
    LayoutAnimation* anims[5];        // +10: in, on_off, loop_0, select_0, out
    unsigned char pad38[0x22c0];
    int value22f8;                    // +22f8
    unsigned char pad22fc[0x24];
};

extern const char kMenuPartsLayout[] __attribute__((visibility("hidden")));   // 0x71007d6051
extern const char kFontMenu[] __attribute__((visibility("hidden")));          // 0x71007d6079
extern const char kInAnim[] __attribute__((visibility("hidden")));            // 0x710073fffb
extern const char kOnOffAnim[] __attribute__((visibility("hidden")));         // 0x71007d6062
extern const char kLoop0Anim[] __attribute__((visibility("hidden")));         // 0x71007d6069
extern const char kSelect0Anim[] __attribute__((visibility("hidden")));       // 0x71007d6070
extern const char kOutAnim[] __attribute__((visibility("hidden")));           // 0x710074056c

class OptionPanel : public OptionPanelBase {
public:
    OptionPanel() : OptionPanelBase(0x41ea, 0x41ea, kMenuPartsLayout, kFontMenu, 0) {
        anims[0] = node->create_animation_3770(kInAnim, false);
        anims[1] = node->create_animation_3770(kOnOffAnim, false);
        anims[2] = node->create_animation_3770(kLoop0Anim, false);
        anims[3] = node->create_animation_3770(kSelect0Anim, false);
        anims[4] = node->create_animation_3770(kOutAnim, false);
        value22f8 = 0x10;
    }
    virtual void v10();       // declared, not defined: the vtable stays external (GOT 0x7100c2b2b8)
};

class OptionPage {
public:
    OptionPage();                                                           // 0x71003a4034
    unsigned char data[0x34a0];
};
class OptionKeyRow {
public:
    OptionKeyRow();                                                         // 0x71003a4c6c
    unsigned char data[0x1150];
};
class OptionButtonRow {
public:
    OptionButtonRow();                                                      // 0x71003a554c
    unsigned char data[0x1160];
};

extern const char kOptBgCntLayout[] __attribute__((visibility("hidden")));    // 0x71007d9190
extern const char kBgIn[] __attribute__((visibility("hidden")));              // 0x71007d91a1
extern const char kLineInGamepad[] __attribute__((visibility("hidden")));     // 0x71007d91a7
extern const char kLineProconIn[] __attribute__((visibility("hidden")));      // 0x71007d91b7
extern const char kLineGpL00In[] __attribute__((visibility("hidden")));       // 0x71007d91c6
extern const char kLineGpR00In[] __attribute__((visibility("hidden")));       // 0x71007d91d6
extern const char kLineGpL01In[] __attribute__((visibility("hidden")));       // 0x71007d91e6
extern const char kLineGpR01In[] __attribute__((visibility("hidden")));       // 0x71007d91f6
extern const char kWindowLIn[] __attribute__((visibility("hidden")));         // 0x71007d9206
extern const char kWindowSIn[] __attribute__((visibility("hidden")));         // 0x71007d9212
extern const char kArwIn[] __attribute__((visibility("hidden")));             // 0x71007dac35
extern const char kArwLLoop[] __attribute__((visibility("hidden")));          // 0x71007d5b89
extern const char kArwRLoop[] __attribute__((visibility("hidden")));          // 0x71007d5b94
extern const char kBgGamepad[] __attribute__((visibility("hidden")));         // 0x71007d921e
extern const char kBgProcon[] __attribute__((visibility("hidden")));          // 0x71007d9229
extern const char kBgGamepadL[] __attribute__((visibility("hidden")));        // 0x71007d9233
extern const char kBgGamepadR[] __attribute__((visibility("hidden")));        // 0x71007d9240
extern const char kArw[] __attribute__((visibility("hidden")));               // 0x71007d830f
extern const char kLineOnGamepad[] __attribute__((visibility("hidden")));     // 0x71007db2e6

// 0x71003a60cc: the options screen (opt_bg_cnt.bflyt, 0x56960 bytes), ending in a tail call of its build (0x71003a6e7c).
class OptionScreen : public OptionScreenBase {
public:
    explicit OptionScreen(OptionOwner* owner);
    virtual ~OptionScreen();
    void build();                                                           // 0x71003a6e7c

    OptionPanel sound;                // +c0
    OptionPanel voice;                // +23e0
    OptionPanel vibration;            // +4700
    OptionPanel camera_x;             // +6a20
    OptionPanel camera_y;             // +8d40
    OptionPanel camera_speed;         // +b060
    OptionPanel message;              // +d380
    OptionPanel minimap;              // +f6a0
    OptionPanel more_panels[9];       // +119c0
    int value255e0;                   // +255e0
    unsigned char pad255e4;
    unsigned char flag255e5;          // +255e5
    unsigned char pad255e6;
    unsigned char flag255e7;          // +255e7
    unsigned char flag255e8;          // +255e8
    unsigned char pad255e9;
    unsigned char flag255ea;          // +255ea
    unsigned char pad255eb[5];
    OptionPage pages[9];              // +255f0
    OptionKeyRow key_rows[9];         // +42f90
    void* value4cb60;                 // +4cb60
    unsigned char pad4cb68[0x48];
    LightEffectNode* layout;          // +4cbb0
    LayoutAnimation* bg_in;           // +4cbb8
    void* value4cbc0;                 // +4cbc0
    void* value4cbc8;                 // +4cbc8
    LayoutAnimation* line_anims[4];   // +4cbd0: line_in_gamepad, line_procon_in, line_gp_l_00_in, line_gp_r_00_in
    void* value4cbf0;                 // +4cbf0
    LayoutAnimation* more_anims[7];   // +4cbf8: line_gp_l_01_in to arw_r_loop
    void* value4cc30;                 // +4cc30
    void* value4cc38;                 // +4cc38
    void* value4cc40;                 // +4cc40
    EffectGroup* backgrounds[5];      // +4cc48: bg_gamepad, bg_procon, bg_gamepad_l, bg_gamepad_r, -
    unsigned char block4cc70[0x48];   // +4cc70
    EffectGroup* arw;                 // +4ccb8
    void* value4ccc0;                 // +4ccc0
    void* value4ccc8;                 // +4ccc8
    int style;                        // +4ccd0
    long value4ccd4 __attribute__((packed)); // +4ccd4
    int value4ccdc;                   // +4ccdc
    OptionButtonRow button_rows[9];   // +4cce0
    int value56940;                   // +56940
    int pad56944;
    int value56948;                   // +56948
    int pad5694c[3];
    OptionOwner* owner56958;          // +56958
};

OptionScreen::OptionScreen(OptionOwner* owner_)
    : OptionScreenBase(owner_), value255e0(0), flag255e5(0), flag255e7(0), flag255e8(0), flag255ea(0),
      value4cb60(nullptr), layout(nullptr), bg_in(nullptr), value4cbc0(nullptr), value4cbc8(nullptr),
      value4cc30(nullptr), value4cc38(nullptr), value4cc40(nullptr), value4ccc0(nullptr), value4ccc8(nullptr),
      value4ccd4(0), value4ccdc(0), value56940(0), value56948(0), owner56958(owner_) {
    memset(backgrounds, 0, sizeof(backgrounds));
    if (page_ids()) {
        gEffectManager->create_node(&layout, 0x4202, kOptBgCntLayout);
        gEffectManager->sync();
    } else {
        gEffectManager->create_node(&layout, 0x41f3, kOptBgCntLayout);
        gEffectManager->flush();
    }
    bg_in = layout->create_animation_3770(kBgIn, true);
    line_anims[0] = layout->create_animation_3770(kLineInGamepad, false);
    line_anims[1] = layout->create_animation_3770(kLineProconIn, false);
    line_anims[2] = layout->create_animation_3770(kLineGpL00In, false);
    line_anims[3] = layout->create_animation_3770(kLineGpR00In, false);
    value4cbf0 = nullptr;
    more_anims[0] = layout->create_animation_3770(kLineGpL01In, false);
    more_anims[1] = layout->create_animation_3770(kLineGpR01In, false);
    more_anims[2] = layout->create_animation_3770(kWindowLIn, false);
    more_anims[3] = layout->create_animation_3770(kWindowSIn, false);
    more_anims[4] = layout->create_animation_3770(kArwIn, false);
    more_anims[5] = layout->create_animation_3770(kArwLLoop, false);
    more_anims[6] = layout->create_animation_3770(kArwRLoop, false);
    backgrounds[0] = layout->group->find(kBgGamepad, 1);
    backgrounds[1] = layout->group->find(kBgProcon, 1);
    backgrounds[2] = layout->group->find(kBgGamepadL, 1);
    backgrounds[3] = layout->group->find(kBgGamepadR, 1);
    backgrounds[4] = nullptr;
    arw = layout->group->find(kArw, 1);
    memset(block4cc70, 0, sizeof(block4cc70));
    layout->group->find(kLineOnGamepad, 1)->flags58 |= 1;
    if (!page_ids())
        gRandomSource.roll();
    style = controller_style_3ce218();
    if (style == 5)
        move_x(arw, 30.0f);
    build();
}