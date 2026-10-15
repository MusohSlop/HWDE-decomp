// 0x7100347928 (1,724 B), fourth session, parked. Build: this file alone, try.py with --name
// _ZN11Class3479286updateEiP10Info347928i and a symbol file with the GOT slots c22a30, c2af58, c21df8, c22bf0,
// c22c38, the strings at 7da68c/7da69b/7da6a6 and the placeholders 1763e8, 176418, 379690, 1f7fe4.
// State: 1,712 B, 43 off with registers abstracted. Still different: the original places the shown branch of the
// lock test between the hidden branch and the shared store (ours moves it to the end: our hidden path is hotter),
// one more callee-saved register in ours (x26), so the rect and the text-area vectors sit elsewhere in the frame.
#include "event/demo_effects.h"
#include "event/demo_light_system.h"
#include "event/layout_panes.h"

class TextRenderer {
public:
    void set_area(TrackVec2* pos, TrackVec2* size, int a, int b, int c);    // 0x71001e709c
    unsigned int draw(void* dest, const char* text, int line, int a, int alpha, float x,
                      float y);                                             // 0x71001e73c0

    unsigned char pad[0x20b8c];
    int spacing;              // +20b8c
    unsigned char pad20b90[8];
    int align;                // +20b98
    unsigned char pad20b9c[0x2d];
    unsigned char wrap;       // +20bc9
    unsigned char shrink;     // +20bca
};
// Reached through the GOT slot at 0x7100c22a30.
extern TextRenderer* gTextRenderer;

void set_pane_lines(PanelPane* pane, TrackLightTarget* lines, unsigned int count); // 0x71001e41d8

struct Flags_347928 {
    unsigned char pad0[0x58];
    unsigned char visible : 1;   // +58 bit 0
    unsigned char : 7;
};

static inline void show_347928(void* group, bool visible) {
    reinterpret_cast<Flags_347928*>(group)->visible = visible;
}

struct IconRect_347928 {
    unsigned char pad[0x10];
};

struct Info347928 {
    int field_0;                     // +0
    int field_4;                     // +4
    int field_8;                     // +8
    int field_c;                     // +c
    int field_10;                    // +10
    int field_14;                    // +14
    int field_18;                    // +18
    int field_1c;                    // +1c
    int field_20;                    // +20
    int field_24;                    // +24
    int field_28;                    // +28
    int field_2c;                    // +2c
    int field_30;                    // +30
    int field_34;                    // +34
    int field_38;                    // +38
    int field_3c;                    // +3c
};

struct Holder_347928 {
    void* table;                     // +0
};

// Reached through the GOT slot at 0x7100c2af58.
extern void* gGlobalc2af58_347928;
// Reached through the GOT slot at 0x7100c21df8.
extern void* gGlobalc21df8_347928;
// Reached through the GOT slot at 0x7100c22bf0.
extern Holder_347928* gGlobalc22bf0_347928;
// Reached through the GOT slot at 0x7100c22c38.
extern IconRect_347928 gGlobalc22c38_347928[];

extern const char kWinRecordWpn_347928[] __attribute__((visibility("hidden")));    // 0x71007da68c
extern const char kWinEmblem_347928[] __attribute__((visibility("hidden")));       // 0x71007da69b
extern const char kIconAttack_347928[] __attribute__((visibility("hidden")));      // 0x71007da6a6

int callee_1fb23c(void*, int);                                               // 0x71001fb23c
void* callee_379690(void*, int, IconRect_347928*);                           // 0x7100379690
void callee_1f7fe4(void*, void*, void*, IconRect_347928*);                   // 0x71001f7fe4
void callee_1f7f44(void*, int);                                              // 0x71001f7f44
void* callee_1763e8(int);                                                    // 0x71001763e8
void callee_176418(void*);                                                   // 0x7100176418
void* callee_214000();                                                       // 0x7100214000
void* callee_214200(void*, int);                                             // 0x7100214200
int callee_213f00(void*);                                                    // 0x7100213f00
void* callee_214890();                                                       // 0x7100214890
void* callee_214aa8(void*, int);                                             // 0x7100214aa8
int callee_214564(void*);                                                    // 0x7100214564
void callee_316a30(void*, int);                                              // 0x7100316a30
const char* callee_217efc(int, int);                                         // 0x7100217efc
void* callee_2017c0();                                                       // 0x71002017c0
unsigned char callee_201f00(void*, int);                                     // 0x7100201f00
unsigned char callee_201ee0(void*, int);                                     // 0x7100201ee0
unsigned char callee_201f20(void*, int);                                     // 0x7100201f20

class Class347928 {
public:
    void update(int mode, Info347928* info, int which);                     // 0x7100347928

    LightEffectNode* node;           // +0
    unsigned char pad8[0x28];
    PanelPane* text_pane;            // +30
    EffectGroup* group38;            // +38
    unsigned char pad40[0x638];
    void* anim678;                   // +678
    unsigned char pad680[0x18];
    EffectGroup* icon698;            // +698
    unsigned char pad6a0[0x10];
    EffectGroup* group6b0;           // +6b0
    EffectGroup* group6b8;           // +6b8
    unsigned char pad6c0[8];
    EffectGroup* icons[3];           // +6c8
    unsigned char handle6e0[0x18];   // +6e0
    unsigned char handles[3][0x18];  // +6f8
    unsigned char pad740[0x30];
    TrackLightTarget lines[16];      // +770
    unsigned char padff0[0xd498];
    void* anime488;                  // +e488
    unsigned char pade490[0x30];
    LightEffectNode* nodee4c0;       // +e4c0
    unsigned char pade4c8[0x10];
    void* anime4d8;                  // +e4d8
    unsigned char pade4e0[0x30];
    unsigned char togglee510[0x20];  // +e510
    EffectGroup* groupe530;          // +e530
    EffectGroup* groupe538;          // +e538
    unsigned char pade540[0x60];
    EffectGroup* groupe5a0;          // +e5a0
    EffectGroup* groupe5a8;          // +e5a8
    int unit;                        // +e5b0
    unsigned char badge;             // +e5b4
    unsigned char pade5b5[3];
    int valuee5b8;                   // +e5b8
    int valuee5bc;                   // +e5bc
    int valuee5c0;                   // +e5c0
    int valuee5c4;                   // +e5c4
    int valuee5c8;                   // +e5c8
    int valuee5cc;                   // +e5cc
    int valuee5d0;                   // +e5d0
    int valuee5d4;                   // +e5d4
    int valuee5d8;                   // +e5d8
    unsigned char flags[3];          // +e5dc
    unsigned char pade5df;
    bool lock;                       // +e5e0
};
static_assert(__builtin_offsetof(Class347928, lines) == 0x770, "lines");
static_assert(__builtin_offsetof(Class347928, anime488) == 0xe488, "e488");
static_assert(__builtin_offsetof(Class347928, lock) == 0xe5e0, "lock");

static inline void set_icon_347928(Class347928* self, int k, const int* value_ptr) {
    if (self->flags[k]) {
        int value = *value_ptr;
        if (static_cast<unsigned int>(value - 1) < 3) {
            callee_1f7fe4(self->icons[k], self->handles[k], gGlobalc22bf0_347928->table, &gGlobalc22c38_347928[0x1f - value]);
            show_347928(self->icons[k], true);
            return;
        }
    }
    show_347928(self->icons[k], false);
}

// 0x7100347928
void Class347928::update(int mode, Info347928* info, int which) {
    unsigned int stage = mode - 0x13;
    IconRect_347928 rect;
    void* table = callee_379690(gGlobalc2af58_347928, callee_1fb23c(gGlobalc21df8_347928, mode), &rect);
    callee_1f7fe4(icon698, handle6e0, table, &rect);
    int frame = (mode == 100 || static_cast<unsigned int>(mode) < 0x1f) ? mode : 0;
    callee_1f7f44(anime488, frame + (mode > 0xb ? 1 : 0));
    callee_176418(callee_1763e8(0));
    if (stage >= 2 && !lock) {
        show_347928(group6b0, true);
        show_347928(group6b8, true);
    } else {
        show_347928(group6b0, false);
        show_347928(group6b8, false);
    }
    unit = info->field_20;
    badge = info->field_24;
    show_347928(node->group->find(kWinRecordWpn_347928, 1), true);
    show_347928(node->group->find(kWinEmblem_347928, 1), false);
    show_347928(node->group->find(kIconAttack_347928, 1), true);
    int u;
    if (stage >= 2 && (u = unit) != -1) {
        int kind = callee_213f00(callee_214200(callee_214000(), u));
        callee_316a30(togglee510, callee_214564(callee_214aa8(callee_214890(), kind)));
        int id = unit;
        TextRenderer* renderer = gTextRenderer;
        TrackVec2 pos;
        pos.x = 0.0f;
        pos.y = 0.0f;
        TrackVec2 size;
        size.x = 26.0f;
        size.y = 26.0f;
        renderer->set_area(&pos, &size, 0x52, 0x4e, 0);
        renderer->wrap = 1;
        renderer->shrink = 1;
        renderer->spacing = 0x53;
        renderer->align = 2;
        unsigned int count = renderer->draw(lines, callee_217efc(id, 9), 0x40, 1, 0xff, 308.0f, 0.0f);
        set_pane_lines(text_pane, lines, count);
        show_347928(text_pane, static_cast<int>(count) > 0);
        show_347928(groupe530, true);
        if (badge != 0) {
            callee_1f7f44(anim678, badge - 1);
            show_347928(groupe538, true);
        } else {
            show_347928(groupe538, false);
        }
        valuee5b8 = info->field_3c;
    } else {
        show_347928(groupe530, false);
        show_347928(text_pane, false);
        show_347928(groupe538, false);
        show_347928(group38, false);
        callee_316a30(togglee510, -1);
        valuee5b8 = 0;
        if (stage < 2) {
            show_347928(node->group->find(kWinRecordWpn_347928, 1), false);
            show_347928(node->group->find(kWinEmblem_347928, 1), true);
            show_347928(node->group->find(kIconAttack_347928, 1), false);
        }
    }
    valuee5bc = info->field_28;
    valuee5c0 = info->field_4;
    valuee5c4 = info->field_8;
    valuee5c8 = info->field_c;
    valuee5cc = info->field_14;
    flags[0] = callee_201f00(callee_2017c0(), which);
    flags[1] = callee_201ee0(callee_2017c0(), which);
    flags[2] = callee_201f20(callee_2017c0(), which);
    valuee5d0 = info->field_18;
    valuee5d4 = info->field_1c;
    valuee5d8 = info->field_10;
    set_icon_347928(this, 0, &info->field_2c);
    set_icon_347928(this, 1, &info->field_30);
    set_icon_347928(this, 2, &info->field_34);
    int rank = info->field_38;
    if (static_cast<unsigned int>(rank) < 0x1f && valuee5bc != 0) {
        callee_1f7f44(anime4d8, rank + (rank > 0xb ? 1 : 0));
        show_347928(nodee4c0->group, true);
        show_347928(groupe5a0, true);
        show_347928(groupe5a8, true);
    } else {
        show_347928(nodee4c0->group, false);
        show_347928(groupe5a0, false);
        show_347928(groupe5a8, false);
    }
}
