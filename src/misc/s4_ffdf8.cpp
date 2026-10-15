// Per-player battle display (0x5f990 bytes; two are made by 0x710011175c, one by 0x71000d7f10 with the two
// view rectangles). Names are descriptive placeholders; member types are known only by their out-of-line
// constructors.
#include "event/demo_light_system.h"

extern "C" void* memset(void* dest, int value, unsigned long size);

// 0x20 bytes with a vtable (0x7100c23148).
class InfoMarker {
public:
    InfoMarker();                                                        // 0x71001f18e8
    unsigned char pad[0x20];
};

// 0x410 bytes: a LightResource at +40 and five frames.
class InfoGauge {
public:
    InfoGauge();                                                         // 0x71001305e4
    unsigned char pad[0x410];
};

// 0x290 bytes: a LightResource at +30 and two frames.
class InfoTimer {
public:
    InfoTimer();                                                         // 0x71000e05d4
    unsigned char pad[0x290];
};

class LayoutRect {
public:
    LayoutRect();                                                        // 0x71001f1cd8
    unsigned char pad[0x28];
};

class LayoutBox {
public:
    LayoutBox();                                                         // 0x71001f1e0c
    unsigned char pad[0x10];
};

// 0x28 bytes with a vtable (0x7100c23138).
class LayoutLine {
public:
    LayoutLine();                                                        // 0x71001f1594
    unsigned char pad[0x28];
};

// Counter slot (0x18 bytes).
struct InfoSlot {
    int type;                 // +00
    int state;                // +04
    float time;               // +08
    int index;                // +0c
    float value;              // +10
    int count;                // +14

    InfoSlot() : type(3), time(0.0f), index(-1), value(0.0f), count(0) { state = 2; }
};

// A counter whose constructor leaves it uninitialised (the display clears the array in its body).
struct HudCount {
    int value;

    HudCount() {}
};

// A counted list of ids.
struct HudList {
    int count;
    int items[50];
};

// A rectangle stored as size, then corner.
struct HudRect {
    float width;
    float height;
    float x;
    float y;
};

// A source with its two frames.
struct HudSourceFrames {
    LightSource source;
    TrackLightTarget frame48;
    TrackLightTarget frame_d0;
};

// Three sources drawn together.
struct HudSourceTriple {
    LightSource a;
    LightSource b;
    LightSource c;
};

// The display's state (0xe0 bytes), a base without a constructor.
struct HudState {
    int player;                               // +00
    int first;                                // +04
    unsigned char pad08[8];
    unsigned char flag10;                     // +10
    unsigned char pad11;
    unsigned char flag12;                     // +12
    unsigned char pad13[0x11];
    int value24;                              // +24
    int value28;                              // +28
    unsigned char pad2c[0x18];
    HudRect rect44;                           // +44
    unsigned char pad54[0xc];
    int value60;                              // +60
    unsigned char pad64[0x7c];
};

class PlayerHud : public HudState {
public:
    explicit PlayerHud(int mode);
    PlayerHud(int mode, float x0, float y0, float w0, float h0, float x1, float y1, float w1, float h1);

    InfoMarker me0;
    LightSource m100[7];
    LightSource a2f8[150];
    LightSource m2d28[2];
    InfoMarker m2db8;
    unsigned char pad2dd8[0xc];
    HudRect view_a;                           // +2de4
    HudRect view_b;                           // +2df4
    unsigned char pad2e04[4];
    LayoutRect m2e08;
    LayoutBox m2e30;
    LightSource m2e40[2];
    TrackLightTarget m2ed0[2];
    LightSource m2fe0[2];
    TrackLightTarget m3070[2];
    HudSourceFrames a3180[150];
    TrackLightTarget mfb10[3];
    LightSource mfca8;
    unsigned char padfcf0[0x18];
    TrackLightTarget mfd08[10];
    LightSource a10258[300];
    LightSource a156b8[118];
    LightSource a177e8[118];
    LightSource a19918[118];
    LightSource a1ba48[118];
    LightSource a1db78[118];
    LightSource a1fca8[300];
    LightSource m25108[4];
    HudSourceTriple a25228[300];
    unsigned char pad34f48[0x3b0];
    LightSource a352f8[300];
    unsigned char pad3a758[0x60];
    LightSource m3a7b8[7];
    int value3a9b0;                           // +3a9b0
    InfoSlot slots[7];                        // +3a9b4
    unsigned char pad3aa5c[4];
    LightSource m3aa60[14];
    unsigned char pad3ae50[0x8];
    LightSource m3ae58[32];
    unsigned char pad3b758[0x8];
    LightSource m3b760[2];
    unsigned char pad3b7f0[0x10];
    LightSource m3b800[4];
    unsigned char pad3b920[0x28];
    LightSource m3b948[64];
    unsigned char pad3cb48[0x8];
    LightSource a3cb50[100];
    unsigned char pad3e770[0x7c];
    HudCount counts[48];                      // +3e7ec
    unsigned char pad3e8ac[4];
    LightSource m3e8b0[48];
    unsigned char pad3f630[0x8];
    LightSource a3f638[100];
    LightSource m41258[12];
    LightSource a415b8[384];
    LightSource m481b8[18];
    unsigned char pad486c8[0x18];
    LayoutLine m486e0[18];
    HudList list;                             // +489b0
    unsigned char pad48a7c[4];
    LightSource a48a80[100];
    LightSource m4a6a0[40];
    TrackLightTarget a4b1e0[100];
    unsigned char pad4e700[0xe0];
    LightSource m4e7e0[20];
    unsigned char pad4ed80[0x8];
    TrackLightTarget a4ed88[134];
    TrackLightTarget a534b8[134];
    unsigned char pad57be8[0x438];
    TrackLightTarget a58020[150];
    unsigned char pad5cfd0[0x10];
    LightSource m5cfe0[4];
    unsigned char pad5d100[0x10];
    InfoGauge m5d110;
    InfoTimer m5d520;
    LightSource m5d7b0[50];
    unsigned char pad5e5c0[0x20];
    TrackLightTarget m5e5e0;
    LightSource m5e668[8];
    unsigned char pad5e8a8[0x1070];
    LightSource m5f918;
    unsigned char pad5f960[0x20];
    void* ptr5f980;                           // +5f980
    unsigned char pad5f988[8];
};
static_assert(sizeof(PlayerHud) == 0x5f990, "hud size");

// 0x71000ffdf8
PlayerHud::PlayerHud(int mode) {
    switch (mode) {
    case 0:
        player = 0;
        first = 1;
        value28 = 0;
        break;
    case 1:
        player = 1;
        first = 0;
        value28 = 1;
        break;
    default:
        player = 0;
        first = 1;
        break;
    }
    value24 = 0;
    value60 = 0;
    rect44 = HudRect();
    flag10 = 0;
    flag12 = 0;
    list.count = 0;
    memset(counts, 0, sizeof(counts));
    ptr5f980 = nullptr;
    memset(list.items, 0, sizeof(list.items));
}

// 0x7100101ae4: near miss, 13 instructions off, 1 with registers abstracted: y0 and h0 swap callee-saved registers and
// the four half sizes are multiplied in another order.
PlayerHud::PlayerHud(int mode, float x0, float y0, float w0, float h0, float x1, float y1, float w1, float h1) {
    player = mode;
    first = mode == 0;
    value28 = 0;
    flag10 = 1;
    value24 = 0;
    value60 = 0;
    rect44 = HudRect();
    flag12 = 0;
    view_a.width = w0;
    view_a.height = h0;
    view_b.width = w1;
    view_b.height = h1;
    view_a.x = x0 - w0 * 0.5f;
    view_a.y = y0 - h0 * 0.5f;
    view_b.x = x1 - w1 * 0.5f;
    view_b.y = y1 - h1 * 0.5f;
    list.count = 0;
    memset(counts, 0, sizeof(counts));
    ptr5f980 = nullptr;
    memset(list.items, 0, sizeof(list.items));
}