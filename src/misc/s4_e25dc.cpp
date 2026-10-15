// Battle information display (0x408c0 bytes; member +90 of the 0x71000ef31c object): the time, damage and map
// overlays of information_time.bflyt and information_map.bflyt. Names are descriptive placeholders; member types
// are known only by their out-of-line constructors.
#include "event/demo_effects.h"
#include "event/demo_light_system.h"

void callee_1e4570(void*, float);        // 0x71001e4570

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

// 0x13b8 bytes: an 0xf2f08 object, 57 sources, a frame and two more sources.
class InfoMapPanel {
public:
    InfoMapPanel();                                                      // 0x71000e4ee0
    unsigned char pad[0x13b8];
};

// 0x618 bytes: 21 sources.
class InfoIconSet {
public:
    InfoIconSet();                                                       // 0x71000e510c
    unsigned char pad[0x618];
};

// 0x900 bytes: 32 sources.
class InfoIconTable {
public:
    InfoIconTable();                                                     // 0x71000e51c8
    unsigned char pad[0x900];
};

// Three sources drawn together.
struct InfoSourceTriple {
    LightSource a;
    LightSource b;
    LightSource c;
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

class InformationDisplay {
public:
    InformationDisplay();

    unsigned char pad0[0x128];
    InfoMarker marker128;                    // +128
    LightSource sources148[6];               // +148
    LightSource sources2f8[150];             // +2f8
    LightSource sources2d28[2];              // +2d28
    InfoMarker marker2db8;                   // +2db8
    TrackLightTarget targets2dd8[8];         // +2dd8
    unsigned char pad3218[0x18];
    LightSource sources3230[300];             // +3230
    LightSource sources8690[118];             // +8690
    LightSource sourcesa7c0[118];             // +a7c0
    LightSource sourcesc8f0[118];             // +c8f0
    LightSource sourcesea20[118];             // +ea20
    LightSource sources10b50[118];            // +10b50
    LightSource sources12c80[4];              // +12c80
    InfoSourceTriple triples[300];            // +12da0
    unsigned char pad22ac0[0x20];
    LightSource sources22ae0[300];            // +22ae0
    unsigned char pad27f40[0x60];
    LightSource sources27fa0[7];              // +27fa0
    unsigned char pad28198[4];
    InfoSlot slots[7];                        // +2819c
    unsigned char pad28244[4];
    LightSource sources28248[7];              // +28248
    unsigned char pad28440[8];
    LightSource sources28448[32];             // +28448
    unsigned char pad28d48[8];
    LightSource sources28d50[32];             // +28d50
    unsigned char pad29650[8];
    LightSource sources29658[50];             // +29658
    unsigned char pad2a468[0x140];
    LightSource sources2a5a8[24];             // +2a5a8
    unsigned char pad2ac68[8];
    LightSource sources2ac70[50];             // +2ac70
    TrackLightTarget targets2ba80[150];       // +2ba80
    unsigned char pad30a30[0x10];
    LightSource sources30a40[4];              // +30a40
    InfoGauge gauge30b60;                     // +30b60
    InfoTimer timer30f70;                     // +30f70
    LightSource sources31200[50];             // +31200
    unsigned char pad32010[8];
    LightSource sources32018[70];             // +32018
    TrackLightTarget targets333c8[50];        // +333c8
    unsigned char pad34e58[0xe0];
    LightSource sources34f38[10];             // +34f38
    unsigned char pad35208[8];
    TrackLightTarget targets35210[67];        // +35210
    unsigned char pad375a8[0x438];
    LightSource sources379e0[64];             // +379e0
    InfoGauge gauge38be0;                     // +38be0
    LightSource sources38ff0[4];              // +38ff0
    TrackLightTarget targets39110[150];       // +39110
    unsigned char pad3e0c0[8];
    InfoMapPanel map_panel;                   // +3e0c8
    InfoIconSet icon_set;                     // +3f480
    InfoIconTable icon_table;                 // +3fa98
    unsigned char pad40398[0x10];
    LightSource sources403a8[4];              // +403a8
    unsigned char pad404c8[8];
    LightEffectNode* time_node;               // +404d0: information_time.bflyt
    LightEffectNode* map_node;                // +404d8: information_map.bflyt
    LightResource resource;                   // +404e0
    LayoutAnimation* time_in;                 // +405f0
    LayoutAnimation* time_out;                // +405f8
    LayoutAnimation* damage_in;               // +40600
    LayoutAnimation* damage_out;              // +40608
    LayoutAnimation* map_in;                  // +40610
    LayoutAnimation* map_out;                 // +40618
    unsigned char pad40620[0x10];
    LightSource sources40630[9];              // +40630
    unsigned char pad408b8[8];
};
static_assert(sizeof(InformationDisplay) == 0x408c0, "display size");

// The animation's target (+18).
static inline void* anim_target(LayoutAnimation* anim) {
    return *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(anim) + 0x18);
}

// 0x71000e25dc
InformationDisplay::InformationDisplay() {
    map_node = nullptr;
    time_node = nullptr;
    time_in = nullptr;
    map_out = nullptr;
    map_in = nullptr;
    damage_out = nullptr;
    damage_in = nullptr;
    time_out = nullptr;
    gEffectManager->create_node(&time_node, 0x41ef, "information_time.bflyt");
    gEffectManager->create_node(&map_node, 0x41ef, "information_map.bflyt");
    gEffectManager->flush();

    LayoutAnimation* anim = time_node->create_animation("time_in", true);
    time_in = anim;
    float scale = time_node->group->scale48;
    callee_1e4570(anim_target(anim), scale);
    if (time_in)
        time_in->set_active(false);

    anim = time_node->create_animation("time_out", true);
    time_out = anim;
    scale = time_node->group->scale48;
    callee_1e4570(anim_target(anim), scale);
    if (time_out)
        time_out->set_active(false);

    anim = time_node->create_animation("damage_in", true);
    damage_in = anim;
    scale = time_node->group->scale48;
    callee_1e4570(anim_target(anim), scale);
    if (damage_in)
        damage_in->set_active(false);

    anim = time_node->create_animation("damage_out", true);
    damage_out = anim;
    scale = time_node->group->scale48;
    callee_1e4570(anim_target(anim), scale);
    if (damage_out)
        damage_out->set_active(false);

    map_in = map_node->create_animation("map_in", true);
    if (map_in)
        map_in->set_active(false);
    map_out = map_node->create_animation("map_out", true);
    if (map_out)
        map_out->set_active(false);

    map_node->group->add(new LightEffect(0x10));
}
