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
    unsigned char flags58;    // +58
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
