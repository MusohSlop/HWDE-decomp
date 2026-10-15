// PARKED 14a50c x3 (88 B each), 6 off: with the stores in this order (the original's output order) everything but the
// last group lines up; our DAG merges mode/layer and flags/target into two 64-bit constant stores (mov x8,
// #0x300000003; movk; stp x8, x9), the original keeps four 32-bit stores (stp w). All 120 orders of those five stores
// give the same 6.

// A light setting's reset (fourth session, 3-copy family 14a50c): LightSetting::reset<0> (0x710014a50c), reset<1>
// (0x710014a564) and reset<2> (0x710014a6e8), identical. Names are descriptive placeholders.

struct LightSetting {
    template <int Copy> void reset();

    void* source;             // +00
    float offset;             // +08
    float scale;              // +0c
    int red;                  // +10
    int green;                // +14
    int blue;                 // +18
    int alpha;                // +1c
    int mode;                 // +20
    int layer;                // +24
    int flags;                // +28
    int target;               // +2c
    unsigned char kind;       // +30
    unsigned char size;       // +31
    unsigned char level;      // +32
    unsigned char pad33;
    int extra;                // +34
    bool active;              // +38
    unsigned char pad39[3];
    int count;                // +3c
};

template <int Copy>
void LightSetting::reset() {
    red = 0xf6;
    green = 9;
    blue = 0x1b;
    alpha = 0xf6;
    size = 0x18;
    offset = 0.0f;
    scale = 1.0f;
    kind = 3;
    source = 0;
    extra = 0;
    active = false;
    level = 0x80;
    mode = 7;
    layer = 3;
    flags = 0;
    target = -1;
    count = 0;
}

// 0x710014a50c
template void LightSetting::reset<0>();
// 0x710014a564
template void LightSetting::reset<1>();
// 0x710014a6e8
template void LightSetting::reset<2>();
