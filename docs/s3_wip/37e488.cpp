// WIP (third session): 37e488, the weapon name panel's init(int id) (2,240 bytes), 4 off with registers abstracted:
// the original gives scale s0 and inv s1 (ours the other way round) and orders skill_l's products accordingly.
// Maps: build/s3/m37e488.txt; function _ZN12WpnNamePanel4initEi.

#include "event/demo_effects.h"
class PaneBase {
public:
    static void* operator new(unsigned long size) noexcept;                 // 0x71005d4380
    PaneBase();                                                             // 0x71005dc664
    virtual ~PaneBase();

    unsigned char pad8[0x50];
    unsigned char flags58;    // +58
    unsigned char pad59[0x107];
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
class LayoutAnimation;

class NamedNode {
public:
    LayoutAnimation* create_animation_3770(const char* name, bool loop);   // 0x71001e3770
};

struct HandleState {
    long id;                     // +08
    short a;                     // +10
    short b;                     // +12

    HandleState() : id(-1), a(0), b(0) {}
};

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
void icon_rect_1f4940(int kind, IconRect* rect);                                                 // 0x71001f4940

extern const char kWpnNameLayout[] __attribute__((visibility("hidden")));       // 0x71007dadbd
extern const char kIconGradeLayout[] __attribute__((visibility("hidden")));     // 0x71007da5ce
extern const char kSeparate[] __attribute__((visibility("hidden")));            // 0x71007dadd2
extern const char kWpnNamePlate[] __attribute__((visibility("hidden")));        // 0x71007daddb
extern const char kWpnNamePlateOver[] __attribute__((visibility("hidden")));    // 0x71007dadea
extern const char kFontWpnName[] __attribute__((visibility("hidden")));        // 0x71007d8f83
extern const char kIconGradePos[] __attribute__((visibility("hidden")));       // 0x71007dadfe
extern const char kIconSkill[] __attribute__((visibility("hidden")));          // 0x71007dae0d
extern const char kNumSkillR[] __attribute__((visibility("hidden")));          // 0x71007dae18
extern const char kNumSkillL[] __attribute__((visibility("hidden")));          // 0x71007dae24
extern const char kNumSkillSlash[] __attribute__((visibility("hidden")));      // 0x71007dae30
extern const char kPlateCursor[] __attribute__((visibility("hidden")));        // 0x71007da19c
extern const char kPlateCursor00[] __attribute__((visibility("hidden")));      // 0x71007dae40
extern const char kPlateCursor01[] __attribute__((visibility("hidden")));      // 0x71007dae59
extern const char kCheck[] __attribute__((visibility("hidden")));              // 0x71007da277
extern const char kTextNewDummy[] __attribute__((visibility("hidden")));       // 0x71007da3c1
extern const char kNamePlate[] __attribute__((visibility("hidden")));          // 0x71007d84fe
extern const char kInAnim[] __attribute__((visibility("hidden")));             // 0x710073fffb
extern const char kOnOffAnim[] __attribute__((visibility("hidden")));          // 0x71007d6062
extern const char kLoopAnim[] __attribute__((visibility("hidden")));           // 0x7100740004
extern const char kSelectAnim[] __attribute__((visibility("hidden")));         // 0x710074053d
extern const char kOutAnim[] __attribute__((visibility("hidden")));            // 0x710074056c
extern const char kOverAnim[] __attribute__((visibility("hidden")));           // 0x71007dae72
extern const char kGradeAnim[] __attribute__((visibility("hidden")));          // 0x71007d7c7b

static inline EffectGroup* find_pane(LightEffectNode* node, const char* name) { return node->group->find(name, 1); }
static inline void hide(EffectGroup* pane) { pane->flags58 &= ~1; }
static inline void show(EffectGroup* pane) { pane->flags58 |= 1; }
// The flag byte is read before y is stored.
static inline void shift_y(EffectGroup* g, float dy) {
    unsigned char flags = g->flags58;
    g->offset34 += dy;
    g->flags58 = flags | 0x10;
}
static inline void set_pos(EffectGroup* g, float x, float y) {
    g->flags58 |= 0x10;
    g->offset30 = x;
    g->offset34 = y;
}
static inline LayoutAnimation* anim(LightEffectNode* node, const char* name) {
    return reinterpret_cast<NamedNode*>(node)->create_animation_3770(name, false);
}

class WpnNamePanel {
public:
    void init(int id);

    int state;                        // +00
    LightEffectNode* name_node;       // +08
    LightEffectNode* grade_node;      // +10
    LightEffectNode* parts_node;      // +18
    LayoutAnimation* name_anims[6];   // +20
    LayoutAnimation* parts_anims[6];  // +50
    LayoutAnimation* grade_anim;      // +80
    EffectGroup* name_plate;          // +88
    EffectGroup* text_dummy;          // +90
    EffectGroup* plate_over;          // +98
    EffectGroup* separate;            // +a0
    EffectGroup* grade_pos;           // +a8
    EffectGroup* check;               // +b0
    EffectGroup* font_name;           // +b8
    EffectGroup* skill_l;             // +c0
    EffectGroup* skill_slash;         // +c8
    EffectGroup* skill_r;             // +d0
    unsigned char padd8[0x2ed0];
    PanelPane* texts[4];              // +2fa8
    LayoutHandle icon;                // +2fc8
    unsigned char pad2fe0[0x9];
    bool b2fe9;                       // +2fe9
    bool ready;                       // +2fea
    int id;                           // +2fec
};

// 0x710037e488
void WpnNamePanel::init(int id_) {
    state = 0;
    skill_r = nullptr;
    ready = false;
    grade_node = nullptr;
    name_node = nullptr;
    text_dummy = nullptr;
    plate_over = nullptr;
    grade_anim = nullptr;
    name_plate = nullptr;
    font_name = nullptr;
    skill_l = nullptr;
    grade_pos = nullptr;
    check = nullptr;
    id = id_;
    gEffectManager->create_node(&name_node, id_, kWpnNameLayout);
    gEffectManager->create_node(&grade_node, 0x41e5, kIconGradeLayout);
    gEffectManager->create_node(&parts_node, id, kWpnNameLayout);
    hide(find_pane(parts_node, kSeparate));
    hide(find_pane(parts_node, kWpnNamePlate));
    hide(find_pane(parts_node, kWpnNamePlateOver));
    hide(find_pane(parts_node, kFontWpnName));
    hide(find_pane(parts_node, kIconGradePos));
    hide(find_pane(parts_node, kIconSkill));
    hide(find_pane(parts_node, kNumSkillR));
    hide(find_pane(parts_node, kNumSkillL));
    hide(find_pane(parts_node, kNumSkillSlash));
    hide(find_pane(parts_node, kPlateCursor));
    hide(find_pane(parts_node, kPlateCursor00));
    hide(find_pane(parts_node, kPlateCursor01));
    hide(find_pane(parts_node, kCheck));
    show(find_pane(parts_node, kTextNewDummy));
    gEffectManager->sync();
    name_plate = find_pane(name_node, kNamePlate);
    text_dummy = find_pane(parts_node, kTextNewDummy);
    plate_over = find_pane(name_node, kWpnNamePlateOver);
    separate = find_pane(name_node, kSeparate);
    grade_pos = find_pane(name_node, kIconGradePos);
    check = find_pane(name_node, kCheck);
    font_name = find_pane(name_node, kFontWpnName);
    skill_l = find_pane(name_node, kNumSkillL);
    skill_slash = find_pane(name_node, kNumSkillSlash);
    skill_r = find_pane(name_node, kNumSkillR);
    hide(find_pane(name_node, kTextNewDummy));
    name_anims[0] = anim(name_node, kInAnim);
    name_anims[1] = anim(name_node, kOnOffAnim);
    name_anims[2] = anim(name_node, kLoopAnim);
    name_anims[3] = anim(name_node, kSelectAnim);
    name_anims[4] = anim(name_node, kOutAnim);
    name_anims[5] = anim(name_node, kOverAnim);
    parts_anims[0] = anim(parts_node, kInAnim);
    parts_anims[1] = anim(parts_node, kOnOffAnim);
    parts_anims[2] = anim(parts_node, kLoopAnim);
    parts_anims[3] = anim(parts_node, kSelectAnim);
    parts_anims[4] = anim(parts_node, kOutAnim);
    parts_anims[5] = anim(parts_node, kOverAnim);
    gEffectManager->flush();
    grade_pos->add(grade_node->group);
    grade_anim = anim(grade_node, kGradeAnim);
    IconRect rect;
    icon_rect_1f4940(0, &rect);
    apply_icon(text_dummy, &icon, gIconSource->table, &gIconRects[32]);
    if (EffectGroup* g = font_name) {
        unsigned char f = g->flags58;
        g->offset34 = g->offset34 + g->size54 * -0.5f;
        g->flags58 = f | 0x10;
    }
    float scale = name_node->group->scale48;
    float inv = 1.5f / scale;
    if (skill_l) {
        float k = scale - 1.0f;
        float dy = skill_l->size54 * 0.5f;
        float dx = k * skill_l->size50 * 0.5f;
        float y = skill_l->offset34 - dy;
        set_pos(skill_l, inv * skill_l->offset30 - dx, y);
    }
    if (skill_slash) {
        float h = skill_slash->size54;
        set_pos(skill_slash, inv * skill_slash->offset30 - h * 0.5f, skill_slash->offset34 - h * 0.5f);
    }
    if (skill_r) {
        float shift = (scale - 1.0f) * skill_l->size50;
        set_pos(skill_r, inv * skill_r->offset30 + shift * 0.5f - skill_r->size54 * 0.5f, skill_r->offset34 - skill_r->size54 * 0.5f);
    }
    texts[0] = new PanelPane;
    texts[1] = new PanelPane;
    texts[2] = new PanelPane;
    texts[3] = new PanelPane;
    texts[0]->flags58 &= ~1;
    texts[1]->flags58 &= ~1;
    texts[2]->flags58 &= ~1;
    texts[3]->flags58 &= ~1;
    font_name->add(texts[0]);
    skill_r->add(texts[1]);
    skill_l->add(texts[2]);
    skill_slash->add(texts[3]);
    b2fe9 = false;
    ready = true;
}
