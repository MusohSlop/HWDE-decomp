// 0x710031e3d0 (1,992 B), fourth session, parked. Build: this file alone, try.py with --name
//   _ZN11Class31e3d010initializeEv and the symbol file worktrees/s4_perm/31e3d0/31e3d0.json (copied below).
// State: 1,984 B, 41 instructions off, 11 with registers abstracted. Everything up to +0x6a0 matches: values that
// the original stores as integers come from by-reference helper parameters (InstCombine turns a float load that is
// only stored into an i32 load before inlining), so the rect origin (50, 189) is rebased by constant hoisting and
// the panel x offsets stay apart from the merged y/z stores; the label positions are copied from a constant table
// (i64 constants, the second rebased); 31eeb8 gets an undefined first argument (it never reads x0); the screen
// check keeps x, y and h in locals.
// Still different: (1) the 20-sprite loop: the original steps a byte offset (64-bit add, 32-bit compare with 0xaa0),
// ours a pointer; (2) the second screen test: the original tests ((word | y) & 0xffff) and then w before h, ours
// (x | y) and h before w. A search over 8 loop forms and 32 compare forms (s4_perm/31e3d0) found nothing better.
// Symbols: {"gsyms": ["got:gTextRenderer=0x7100c22a30", "got:gIcons_31e3d0=0x7100c22a10",
//   "got:gGlobal_31e3d0=0x7100c22be8", "got:gHolder_31e3d0=0x7100c22bf0", "got:kColors_31e3d0=0x7100c22c68",
//   "got:kIconRects_31e3d0=0x7100c22c38", "got:gEffectManager=0x7100c22a00", "got:_ZTV11LightEffect=0x7100c22be0",
//   "kSlices8014b4_31e3d0=0x71008014b4", "kSlices8014e4_31e3d0=0x71008014e4", "kLayout_31e3d0=0x71007d8090",
//   "kOn_31e3d0=0x71007d8de1", "kOff_31e3d0=0x71007d80da"], "imports": ["_Z16get_shared_statev=0x71002aae3c",
//   "_Z20shared_state_exitingP11SharedState=0x71002ac7f0", "_Z24resource_queue_cancelledv=0x71002589c0",
//   "_Z13display_widthv=0x71003cc930", "_Z14display_heightv=0x71003cc94c",
//   "_ZN12TextRenderer11color_indexEii=0x71001e5774", "_Z15draw_icon_db3b4P14IconSet_31e3d0Pvi=0x71000db3b4",
//   "_Z15draw_icon_db3d8P14IconSet_31e3d0Pvi=0x71000db3d8", "_ZN11Class31e3d05setupEi=0x710031eb98",
//   "_ZN13EffectManager11create_nodeEPP15LightEffectNodeiPKc=0x71001e2360",
//   "_ZN11EffectGroup3addEP10EffectBase=0x71005da17c", "_ZN10EffectBasenwEm=0x71005d4380",
//   "_ZN10EffectBaseC2Ev=0x71005d9690", "memcpy=0x7100600870"]}#include "event/demo_effects.h"
#include "event/demo_light_system.h"
#include "event/layout_panes.h"

class TextRenderer {
public:
    unsigned int color_index(int kind, int a);                                // 0x71001e5774
};
// Reached through the GOT slot at 0x7100c22a30.
extern TextRenderer* gTextRenderer;

struct SharedState {
    int value0;
    int language;             // +04
};
SharedState* get_shared_state();                                            // 0x71002aae3c
unsigned char shared_state_exiting(SharedState* state);                     // 0x71002ac7f0
unsigned char resource_queue_cancelled();                                   // 0x71002589c0
unsigned int display_width();                                               // 0x71003cc930
unsigned int display_height();                                              // 0x71003cc94c

struct IconRecord_31e3d0 {
    unsigned char pad0[8];
    unsigned short width;            // +8
    unsigned short height;           // +a
    unsigned char padc[4];
};

struct IconSet_31e3d0 {
    void* texture;                   // +0
};

struct Holder_31e3d0 {
    void* table;                     // +0
};

// Three slices (left, top, right, bottom) of a frame texture.
struct Slices_31e3d0 {
    unsigned char data[0x30];
};

struct Rect16_31e3d0 {
    unsigned int x : 16;
    unsigned int y : 16;
};

struct Screen_31e3d0 {
    unsigned char pad0[4];
    Rect16_31e3d0 pos;               // +4
    Rect16_31e3d0 size;              // +8
};

struct Global_31e3d0 {
    unsigned char pad0[0x90];
    unsigned char sound90[0x408c0];  // +90
    Screen_31e3d0* screen;           // +40950
};

// Reached through the GOT slot at 0x7100c22be8.
extern Global_31e3d0* gGlobal_31e3d0;
// Reached through the GOT slot at 0x7100c22a10.
extern IconSet_31e3d0* gIcons_31e3d0;
// Reached through the GOT slot at 0x7100c22bf0.
extern Holder_31e3d0* gHolder_31e3d0;
// Reached through the GOT slot at 0x7100c22c68.
extern const int kColors_31e3d0[];
// Reached through the GOT slot at 0x7100c22c38.
extern const IconRecord_31e3d0 kIconRects_31e3d0[];

extern const Slices_31e3d0 kSlices8014b4_31e3d0 __attribute__((visibility("hidden"))); // 0x71008014b4
extern const Slices_31e3d0 kSlices8014e4_31e3d0 __attribute__((visibility("hidden"))); // 0x71008014e4
extern const char kLayout_31e3d0[] __attribute__((visibility("hidden")));            // 0x71007d8090
extern const char kOn_31e3d0[] __attribute__((visibility("hidden")));                // 0x71007d8de1
extern const char kOff_31e3d0[] __attribute__((visibility("hidden")));               // 0x71007d80da

void callee_edc50(void*, int);                                               // 0x71000edc50
void draw_icon_db3b4(IconSet_31e3d0*, void*, int);                           // 0x71000db3b4
void draw_icon_db3d8(IconSet_31e3d0*, void*, int);                           // 0x71000db3d8
const IconRecord_31e3d0* callee_db39c(IconSet_31e3d0*, int);                 // 0x71000db39c
void callee_31eeb8(void* unused, void* target, const IconRecord_31e3d0* icon, void* texture,
                   Slices_31e3d0* slices, bool a, bool b, float x, float y, float z); // 0x710031eeb8
void callee_32b4a8(void*);                                                   // 0x710032b4a8
void callee_1f3424(Holder_31e3d0*, void*, int, TrackVec2*);                  // 0x71001f3424
void callee_1f0df4(void*, const IconRecord_31e3d0*, void*);                  // 0x71001f0df4
void* callee_1e3770(void*, void*, int);                                      // 0x71001e3770

// 31eeb8 never reads its first argument, so its callers leave x0 as it is.
static inline void* unused_31e3d0() {
    void* p;
    return p;
}

struct Panel31f0dc {
    LightEffectNode* node;           // +0
    unsigned char pad8[0x1558];
};
struct Panel31f27c {
    LightEffectNode* node;           // +0
    unsigned char pad8[0x11a8];
};
void callee_31f0dc(Panel31f0dc*);                                            // 0x710031f0dc
void callee_31f27c(Panel31f27c*);                                            // 0x710031f27c

struct SpriteFlags_31e3d0 {
    unsigned char pad0[8];
    unsigned int : 7;
    unsigned int bit7 : 1;           // +8 bit 7
    unsigned int : 24;
};

static inline SpriteFlags_31e3d0* flags_31e3d0(void* sprite) {
    return reinterpret_cast<SpriteFlags_31e3d0*>(sprite);
}

struct PaneBits_31e3d0 {
    unsigned int : 8;
    unsigned int field8 : 8;         // bits 8-15
    unsigned int : 4;
    unsigned int field20 : 3;        // bits 20-22
    unsigned int : 9;
};

static inline void set_rect_31e3d0(LightSource* source, const TrackVec2& pos, float width, float height) {
    source->min.x = pos.x;
    source->min.y = pos.y;
    float right = pos.x + width;
    float bottom = pos.y + height;
    source->max.x = right;
    source->max.y = bottom;
}

static inline void move_31e3d0(EffectGroup* group, const float& x, float y) {
    group->offset30 = x;
    group->offset34 = y;
    group->offset38 = 0.0f;
    group->flags58 |= 0x10;
}

static inline void frame_31e3d0(void* target, int id, const Slices_31e3d0& table, float x, float y, float z) {
    const IconRecord_31e3d0* icon = callee_db39c(gIcons_31e3d0, id);
    Slices_31e3d0 slices = table;
    callee_31eeb8(unused_31e3d0(), target, icon, gIcons_31e3d0->texture, &slices, true, false, x, y, z);
}

static const TrackVec2 kLabelPos_31e3d0[] = {{117.0f, 169.0f}, {267.0f, 169.0f}};

static inline void label_31e3d0(void* target, int color, const TrackVec2& at) {
    TrackVec2 pos = at;
    callee_1f3424(gHolder_31e3d0, target, color, &pos);
}

class Class31e3d0 {
public:
    void initialize();                                                       // 0x710031e3d0
    void setup(int index);                                                   // 0x710031eb98

    unsigned char pad0[8];
    long value8;                     // +8
    unsigned char pad10[0x34];
    unsigned char flag44;            // +44
    unsigned char pad45[0x9b];
    unsigned char initialized;       // +e0
    unsigned char pade1[3];
    int mode;                        // +e4
    unsigned char pade8[0x15ae0];
    LightSource source15bc8;         // +15bc8
    unsigned char pad15c10[0x90];
    unsigned char frame15ca0[0xd8];  // +15ca0
    unsigned char label15d78[0x48];  // +15d78
    unsigned char label15dc0[0x1148];// +15dc0
    unsigned char frames[3][0xd8];   // +16f08
    unsigned char pad17190[0xd318];
    LightSource source244a8;         // +244a8
    unsigned char sprite244f0[0x88]; // +244f0
    unsigned char sprites[20][0x88]; // +24578
    long value25018;                 // +25018
    int value25020;                  // +25020
    unsigned char pad25024[4];
    LightEffectNode* node25028;      // +25028
    void* part25030;                 // +25030
    void* part25038;                 // +25038
    unsigned char pad25040[0x10];
    unsigned char object25050[0x3a140]; // +25050
    Panel31f0dc panels[4];           // +5f190
    Panel31f27c rows[6];             // +64710
};
static_assert(__builtin_offsetof(Class31e3d0, source15bc8) == 0x15bc8, "15bc8");
static_assert(__builtin_offsetof(Class31e3d0, frames) == 0x16f08, "16f08");
static_assert(__builtin_offsetof(Class31e3d0, source244a8) == 0x244a8, "244a8");
static_assert(__builtin_offsetof(Class31e3d0, sprites) == 0x24578, "24578");
static_assert(__builtin_offsetof(Class31e3d0, node25028) == 0x25028, "25028");
static_assert(__builtin_offsetof(Class31e3d0, panels) == 0x5f190, "5f190");
static_assert(__builtin_offsetof(Class31e3d0, rows) == 0x64710, "64710");

// 0x710031e3d0
void Class31e3d0::initialize() {
    callee_edc50(gGlobal_31e3d0->sound90, 3);
    setup(0);
    setup(1);
    setup(2);
    setup(3);
    if (resource_queue_cancelled()) {
        return;
    }
    if (shared_state_exiting(get_shared_state())) {
        return;
    }
    if (initialized) {
        return;
    }
    value8 = 0;
    flag44 = 0;
    draw_icon_db3b4(gIcons_31e3d0, &source15bc8, 0x2f);
    const IconRecord_31e3d0* icon = callee_db39c(gIcons_31e3d0, 0x2f);
    TrackVec2 origin;
    origin.x = 50.0f;
    origin.y = 189.0f;
    set_rect_31e3d0(&source15bc8, origin, icon->width, icon->height);
    source15bc8.flags &= ~0x80;
    frame_31e3d0(frame15ca0, 0x33, kSlices8014b4_31e3d0, 108.0f, 161.0f, 112.0f);
    callee_32b4a8(object25050);
    callee_31f0dc(&panels[0]);
    move_31e3d0(panels[0].node->group, -510.0f, 323.0f);
    callee_31f0dc(&panels[1]);
    move_31e3d0(panels[1].node->group, -510.0f, 215.0f);
    callee_31f0dc(&panels[2]);
    move_31e3d0(panels[2].node->group, -510.0f, 107.0f);
    callee_31f0dc(&panels[3]);
    move_31e3d0(panels[3].node->group, -510.0f, -1.0f);
    callee_31f27c(&rows[0]);
    move_31e3d0(rows[0].node->group, 0.0f, 237.0f);
    callee_31f27c(&rows[1]);
    move_31e3d0(rows[1].node->group, 0.0f, 169.0f);
    callee_31f27c(&rows[2]);
    move_31e3d0(rows[2].node->group, 0.0f, 101.0f);
    callee_31f27c(&rows[3]);
    move_31e3d0(rows[3].node->group, 0.0f, 33.0f);
    callee_31f27c(&rows[4]);
    move_31e3d0(rows[4].node->group, 0.0f, -35.0f);
    callee_31f27c(&rows[5]);
    move_31e3d0(rows[5].node->group, 0.0f, -103.0f);
    gEffectManager->create_node(&node25028, 0x41e5, kLayout_31e3d0);
    part25030 = callee_1e3770(node25028, const_cast<char*>(kOn_31e3d0), 1);
    part25038 = callee_1e3770(node25028, const_cast<char*>(kOff_31e3d0), 1);
    node25028->group->add(new LightEffect(0x11));
    label_31e3d0(label15d78, kColors_31e3d0[gTextRenderer->color_index(0xb, 1)], kLabelPos_31e3d0[0]);
    label_31e3d0(label15dc0, kColors_31e3d0[gTextRenderer->color_index(0xc, 1)], kLabelPos_31e3d0[1]);
    frame_31e3d0(frames[0], 0xc1, kSlices8014e4_31e3d0, -2.0f, -2.0f, 80.0f);
    frame_31e3d0(frames[1], 0xc1, kSlices8014e4_31e3d0, 104.0f, -2.0f, 80.0f);
    frame_31e3d0(frames[2], 0xc1, kSlices8014e4_31e3d0, 210.0f, -2.0f, 80.0f);
    callee_1f0df4(sprite244f0, &kIconRects_31e3d0[24], gHolder_31e3d0->table);
    float width = display_width();
    float height = display_height();
    source244a8.min.x = 0.0f;
    source244a8.min.y = 0.0f;
    source244a8.max.x = width;
    source244a8.max.y = height;
    source244a8.flags = (source244a8.flags & ~0xff00u) | 0x300;
    source244a8.flags &= ~0x700000u;
    source244a8.color.raw = 0;
    source244a8.color.a = 180;
    value25020 = 0;
    value25018 = 0;
    for (auto& sprite : sprites) {
        draw_icon_db3d8(gIcons_31e3d0, sprite, 0x157);
        flags_31e3d0(sprite)->bit7 = 1;
    }
    Global_31e3d0* global = gGlobal_31e3d0;
    if (global != nullptr) {
        Screen_31e3d0* screen = global->screen;
        unsigned int x = screen->pos.x;
        unsigned int y = screen->pos.y;
        unsigned int h = screen->size.y;
        if (x == 20 && y == 20 && screen->size.x == 44 && h == 44) {
            mode = 0;
        } else if (x == 0 && y == 0 && screen->size.x == 64 && h == 64) {
            mode = 1;
        } else {
            mode = 2;
        }
    }
    initialized = 1;
}
