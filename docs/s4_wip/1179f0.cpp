// 0x71001179f0 (1,520 B), fourth session, parked. Build: this file alone, try.py with the symbol file
//   {"gsyms": ["got:gTextRenderer=0x7100c22a30", "got:gIcons_1179f0=0x7100c22a10", "got:gFlag_1179f0=0x7100c22bc8",
//   "got:gGlobalc216e8_1179f0=0x7100c216e8"], "imports": ["_Z16get_shared_statev=0x71002aae3c",
//   "_Z12screen_widthv=0x71003df258", "_ZN12TextRenderer8set_areaEP9TrackVec2S1_iii=0x71001e709c",
//   "_ZN12TextRenderer4drawEPvPKciiiff=0x71001e73c0", "_ZN12TextRenderer7measureEPKcP9TrackVec2S3_ff=0x71001e5e08",
//   "_ZN9Obj1179f013callee_1162ccEv=0x71001162cc"]} and --map .rodata.cst8=0x710073cd1c.
// State: 1,520 B, 8 words off, none with registers abstracted. What is right: the locals declared at the top with
// size first (the stack order), each vector set through an inline setter (both values computed before the stores),
// the flag selects written flag == 0 ? a : b (two-float constant-pool tables), sprite addresses taken before the
// icon lookups or positions that follow, the switch selects written unlocked == 0 ? a : b, and the hit rectangle
// from x, y loaded between the multiply and the size.y store (Reassociate ranks count stores, so a store between
// size.y's load and pos.y's load puts h first in y + h).
// Still different: registers in the rectangle block after the 1eff04 call: the original has size.y*0.5 in s3,
// -554 in s2 and pos.y in s3; ours s0, s3 and s2.#include "event/demo_effects.h"
#include "event/demo_light_system.h"
#include "event/layout_panes.h"

class TextRenderer {
public:
    void set_area(TrackVec2* pos, TrackVec2* size, int a, int b, int c);    // 0x71001e709c
    unsigned int draw(void* dest, const char* text, int line, int a, int alpha, float x,
                      float y);                                             // 0x71001e73c0
    unsigned int measure(const char* text, TrackVec2* size, TrackVec2* extent, float x,
                         float width);                                      // 0x71001e5e08

    unsigned char pad[0x20b98];
    int align;                // +20b98
    int valign;               // +20b9c
    unsigned char pad20ba0[0x28];
    unsigned char right_to_left; // +20bc8
    unsigned char wrap;       // +20bc9
};
// Reached through the GOT slot at 0x7100c22a30.
extern TextRenderer* gTextRenderer;

struct SharedState {
    int value0;
    int language;             // +04
};
SharedState* get_shared_state();                                            // 0x71002aae3c
int screen_width();                                                         // 0x71003df258

struct IconRecord_1179f0 {
    unsigned char pad0[8];
    unsigned short width;            // +8
    unsigned short height;           // +a
    unsigned char padc[4];
};

struct IconSet_1179f0 {
    void* texture;                   // +0
};

// Reached through the GOT slot at 0x7100c22a10.
extern IconSet_1179f0* gIcons_1179f0;
// Reached through the GOT slot at 0x7100c22bc8.
extern unsigned char gFlag_1179f0;
// Reached through the GOT slot at 0x7100c216e8.
extern void* gGlobalc216e8_1179f0;

// The flag word of a sprite: +8 bit 7 and the 4-bit field at bit 16.
struct SpriteFlags_1179f0 {
    unsigned char pad0[8];
    unsigned int : 7;
    unsigned int bit7 : 1;           // +8 bit 7
    unsigned int : 8;
    unsigned int field16 : 4;        // +8 bits 16-19
    unsigned int : 12;
};

static inline void set_1179f0(TrackVec2* v, float x, float y) {
    v->x = x;
    v->y = y;
}

static inline void set_rect_1179f0(float* rect, float x, float y, float w, float h) {
    float left = x - w;
    float top = y - h;
    float bottom = y + h;
    rect[0] = left;
    rect[1] = top;
    rect[2] = x + w;
    rect[3] = bottom;
}

static inline SpriteFlags_1179f0* flags_1179f0(void* sprite) {
    return reinterpret_cast<SpriteFlags_1179f0*>(sprite);
}

const IconRecord_1179f0* callee_db39c(IconSet_1179f0*, int);                 // 0x71000db39c
void callee_1effa8(void*, const IconRecord_1179f0*, void*, TrackVec2*, TrackVec2*); // 0x71001effa8
void callee_1eff04(void*, const IconRecord_1179f0*, void*, TrackVec2*);      // 0x71001eff04
void callee_1f0df4(void*, const IconRecord_1179f0*, void*);                  // 0x71001f0df4
int callee_118978(void*, const char*, TrackVec2);                            // 0x7100118978
int callee_117fe0(void*, const char*, TrackVec2, TrackVec2);                 // 0x7100117fe0
void* callee_18d5d8(void*);                                                  // 0x710018d5d8
int callee_1a6f6c(void*, int);                                               // 0x71001a6f6c
unsigned char callee_1a811c(void*, int);                                     // 0x71001a811c

struct Obj1179f0 {
    unsigned char pad0[8];
    int state;                       // +8
    unsigned int line_count;         // +c
    int value10;                     // +10
    unsigned char pad14[4];
    int value18;                     // +18
    unsigned char pad1c[4];
    unsigned char lines[0x6c00];     // +20
    unsigned char sprite6c20[0x48];  // +6c20
    unsigned char obj6c68[0x139b0];  // +6c68
    void* ptr1a618;                  // +1a618
    unsigned char pad1a620[0x30];
    unsigned char icons[4][0x88];    // +1a650
    int value1a870;                  // +1a870
    unsigned char pad1a874[0x26d00];
    int value41574;                  // +41574
    int value41578;                  // +41578
    unsigned char pad4157c[0x16f8];
    int value42c74;                  // +42c74
    unsigned char pad42c78[8];
    unsigned char sprite42c80[0x68]; // +42c80
    unsigned char sprite42ce8[0x48]; // +42ce8
    unsigned char sprite42d30[0x30]; // +42d30
    float rect[4];                   // +42d60
    unsigned char pad42d70[0x28];
    int mode;                        // +42d98
    int value42d9c;                  // +42d9c
    unsigned char pad42da0[0x614];
    int value433b4;                  // +433b4

    void callee_1162cc();                                                    // 0x71001162cc
};
static_assert(__builtin_offsetof(Obj1179f0, ptr1a618) == 0x1a618, "1a618");
static_assert(__builtin_offsetof(Obj1179f0, value41574) == 0x41574, "41574");
static_assert(__builtin_offsetof(Obj1179f0, value42c74) == 0x42c74, "42c74");
static_assert(__builtin_offsetof(Obj1179f0, rect) == 0x42d60, "42d60");
static_assert(__builtin_offsetof(Obj1179f0, value433b4) == 0x433b4, "433b4");

// 0x71001179f0
void call_1179f0(Obj1179f0* self, int p1, int mode, int p3, const char* text, int p5) {
    TrackVec2 size;
    TrackVec2 pos;
    TrackVec2 extent;
    TrackVec2 pos2;
    TrackVec2 size2;
    TextRenderer* renderer = gTextRenderer;
    self->value42d9c = p3;
    get_shared_state();
    self->value42c74 = 0;
    void* sprite = self->sprite42ce8;
    const IconRecord_1179f0* iconA = callee_db39c(gIcons_1179f0, 0xcd);
    const IconRecord_1179f0* iconB = callee_db39c(gIcons_1179f0, 0xca);
    set_1179f0(&pos, 404.0f, gFlag_1179f0 == 0 ? 795.0f : 491.0f);
    set_1179f0(&size, 1108.0f, iconA->height);
    callee_1effa8(sprite, iconA, gIcons_1179f0->texture, &pos, &size);
    flags_1179f0(self->sprite42ce8)->bit7 = 0;
    void* spriteB = self->sprite42d30;
    set_1179f0(&pos, 958.0f, gFlag_1179f0 == 0 ? 845.0f : 545.0f);
    set_1179f0(&size, iconB->width, iconB->height);
    callee_1eff04(spriteB, iconB, gIcons_1179f0->texture, &pos);
    size.x = 554.0f;
    float h = size.y * 0.5f * 1.2f;
    float x = pos.x;
    float y = pos.y;
    size.y = h;
    set_rect_1179f0(self->rect, x, y, size.x, size.y);
    flags_1179f0(self->sprite42d30)->bit7 = 0;
    flags_1179f0(self->sprite42d30)->field16 = 1;
    if (self->ptr1a618 != nullptr) {
        self->value1a870 = 1;
        callee_1f0df4(self->icons[0], callee_db39c(gIcons_1179f0, 0xcd), gIcons_1179f0->texture);
        callee_1f0df4(self->icons[1], callee_db39c(gIcons_1179f0, 0xca), gIcons_1179f0->texture);
        callee_1f0df4(self->icons[2], callee_db39c(gIcons_1179f0, 0xd0), gIcons_1179f0->texture);
        callee_1f0df4(self->icons[3], callee_db39c(gIcons_1179f0, 0xca), gIcons_1179f0->texture);
    }
    set_1179f0(&size, 32.0f, 32.0f);
    renderer->right_to_left = 1;
    renderer->measure(text, &size, &extent, 0.0f, screen_width());
    set_1179f0(&pos, 959.0f, gFlag_1179f0 == 0 ? 828.0f : 524.0f);
    renderer->set_area(&pos, &size, 0x3c, 0x4b, p5 != 0);
    renderer->right_to_left = 1;
    renderer->align = 2;
    renderer->valign = 1;
    self->line_count = renderer->draw(self->lines, text, 0x180, 0, 0xff, 1024.0f, 0.0f);
    void* sprite2 = self->sprite6c20;
    const IconRecord_1179f0* icon = callee_db39c(gIcons_1179f0, 0x19);
    set_1179f0(&pos, 1545.0f, gFlag_1179f0 == 0 ? 515.0f : 493.0f);
    set_1179f0(&size, 328.0f, icon->height);
    callee_1effa8(sprite2, icon, gIcons_1179f0->texture, &pos, &size);
    flags_1179f0(self->sprite6c20)->bit7 = 0;
    void* obj = self->obj6c68;
    set_1179f0(&pos, 1599.0f, gFlag_1179f0 == 0 ? 535.0f : 513.0f);
    set_1179f0(&size, 24.0f, 24.0f);
    if (get_shared_state()->language == 9) {
        self->value10 = callee_118978(obj, text, pos);
    } else {
        self->value10 = callee_117fe0(obj, text, pos, size);
    }
    self->value433b4 = -1;
    self->value41574 = 0;
    self->value41578 = 0;
    self->callee_1162cc();
    set_1179f0(&pos2, 679.0f, gFlag_1179f0 == 0 ? 468.0f : 365.0f);
    void* sprite3 = self->sprite42c80;
    void* table = callee_18d5d8(gGlobalc216e8_1179f0);
    unsigned char unlocked = callee_1a811c(table, callee_1a6f6c(table, p1));
    int id;
    switch (mode) {
    case 1:
        id = unlocked == 0 ? 0x1b : 0x35;
        break;
    case 2:
        id = unlocked == 0 ? 0x1c : 0x37;
        break;
    case 3:
        id = unlocked == 0 ? 0x1a : 0x36;
        break;
    default:
        id = 0;
        break;
    }
    const IconRecord_1179f0* icon2 = callee_db39c(gIcons_1179f0, id);
    const IconRecord_1179f0* info = callee_db39c(gIcons_1179f0, id);
    set_1179f0(&size2, info->width, info->height);
    callee_1effa8(sprite3, icon2, gIcons_1179f0->texture, &pos2, &size2);
    self->value18 = 0;
    self->mode = mode;
    self->state = 1;
}
