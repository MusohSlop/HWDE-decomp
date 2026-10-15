// Large functions written by hand (fifth session). Struct, field and callee names are placeholders after the
// address and offset, as in the generated units. Status: matching/README.md.

typedef float Vec4f __attribute__((ext_vector_type(4)));

extern "C" void* memcpy(void*, const void*, unsigned long);

struct Global455ebc {
    unsigned char pad0[0x70];
    unsigned short field_70;
};
Global455ebc* callee_455ebc();        // 0x7100455ebc

static inline float wrap_yaw_415f00(float a) {
    float r;
    if (a > 180.0f) {
        r = a + -360.0f;
    } else {
        r = a <= -180.0f ? a + 360.0f : a;
    }
    return r;
}

// The second comparison goes through double: it keeps its own compare (the original tests "pl" and "mi" of
// one fcmp separately, and combines "gt" with "pl" in an and), where a repeated float comparison is merged
// and the negation becomes a bic.
static inline float clamp_pitch_415f00(float a) {
    bool lo = a < -90.0f;
    bool hi = (a > 90.0f) & !(a < -90.0);
    return (lo | hi) ? (hi ? 90.0f : -90.0f) : a;
}

struct View30_415f00 {
    Vec4f pos;                   // +0
    Vec4f target;                // +10
    float pitch;                 // +20
    float yaw;                   // +24
    unsigned char pad28[0x8];
};

static inline View30_415f00 operator-(const View30_415f00& a, const View30_415f00& b) {
    View30_415f00 r;
    r.pos = a.pos - b.pos;
    r.target = a.target - b.target;
    r.yaw = wrap_yaw_415f00(a.yaw - b.yaw);
    r.pitch = clamp_pitch_415f00(a.pitch - b.pitch);
    return r;
}

struct View20_415f00 {
    Vec4f pos;                   // +0
    float pitch;                 // +10
    float yaw;                   // +14
    unsigned char pad18[0x8];
};

static inline View20_415f00 operator-(const View20_415f00& a, const View20_415f00& b) {
    View20_415f00 r;
    r.pos = a.pos - b.pos;
    r.yaw = wrap_yaw_415f00(a.yaw - b.yaw);
    r.pitch = clamp_pitch_415f00(a.pitch - b.pitch);
    return r;
}

struct Block40_415f00 {
    float e0;                    // +0
    float e4;                    // +4
    float e8;                    // +8
    float ec;                    // +c
    unsigned char pad10[0x10];
    Vec4f v20;                   // +20
    Vec4f v30;                   // +30
};

static inline Block40_415f00 operator-(const Block40_415f00& a, const Block40_415f00& b) {
    Block40_415f00 r;
    r.v20 = a.v20 - b.v20;
    r.v30 = a.v30 - b.v30;
    r.e8 = a.e8 - b.e8;
    r.ec = a.ec - b.ec;
    r.e0 = a.e0 - b.e0;
    r.e4 = a.e4 - b.e4;
    return r;
}

struct State415f00 {
    View30_415f00 view_0;               // +0
    View30_415f00 view_30;              // +30
    View20_415f00 view_60;              // +60
    View20_415f00 view_80;              // +80
    View20_415f00 view_a0;              // +a0
    Vec4f field_c0;              // +c0
    Vec4f field_d0;              // +d0
    Block40_415f00 block_e0;            // +e0
    Vec4f field_120;             // +120
    float field_130;             // +130
    float field_134;             // +134
    float field_138;             // +138
    float field_13c;             // +13c
    Vec4f field_140;             // +140
    Vec4f field_150;             // +150
    Vec4f field_160;             // +160
    float field_170;             // +170
    float field_174;             // +174
    float field_178;             // +178
    float field_17c;             // +17c
    float field_180;             // +180
    float field_184;             // +184
    unsigned char pad188[0x8];
    Vec4f field_190;             // +190
    float field_1a0;             // +1a0
    float field_1a4;             // +1a4
    unsigned char pad1a8[0x8];
    Vec4f field_1b0;             // +1b0
    Vec4f field_1c0;             // +1c0
    Vec4f field_1d0;             // +1d0
    Vec4f field_1e0;             // +1e0
    float field_1f0;             // +1f0
    int field_1f4;               // +1f4
    int field_1f8;               // +1f8
    float field_1fc;             // +1fc
    float field_200;             // +200
    float field_204;             // +204
    unsigned char pad208[0x8];
    Vec4f field_210;             // +210
    Vec4f field_220;             // +220
    float field_230;             // +230
    float field_234;             // +234
    float field_238;             // +238
    float field_23c;             // +23c
    float field_240;             // +240
    float field_244;             // +244
    float field_248;             // +248
    unsigned char pad24c[0xe4];
    int field_330;               // +330
    int field_334;               // +334
    int field_338;               // +338
    unsigned char pad33c[0x4];
    float field_340;             // +340
    float field_344;             // +344
    float field_348;             // +348
    float field_34c;             // +34c
    float field_350;             // +350
    float field_354;             // +354
    float field_358;             // +358
    float field_35c;             // +35c
    float field_360;             // +360
    float field_364;             // +364
    float field_368;             // +368
    float field_36c;             // +36c
    float field_370;             // +370
    float field_374;             // +374
    unsigned char pad378[0x8];
    Vec4f field_380;             // +380
    unsigned char pad390[0x20];
};

void callee_3d4acc(State415f00*, State415f00*);        // 0x71003d4acc

// 0x7100415f00: a copy of *self with every field set to the difference of a and b (angles wrapped to
// [-180, 180] and pitches clamped to [-90, 90]), then passed to 3d4acc.
void call_415f00(State415f00* self, const State415f00* a, const State415f00* b) {
    State415f00 d;
    memcpy(&d, self, sizeof(d));
    d.view_0 = a->view_0 - b->view_0;
    d.view_30 = a->view_30 - b->view_30;
    d.view_60 = a->view_60 - b->view_60;
    d.view_a0 = a->view_a0 - b->view_a0;
    d.view_80 = a->view_80 - b->view_80;
    d.field_c0 = a->field_c0 - b->field_c0;
    d.field_d0 = a->field_d0 - b->field_d0;
    d.block_e0 = a->block_e0 - b->block_e0;
    d.field_130 = a->field_130 - b->field_130;
    d.field_134 = a->field_134 - b->field_134;
    d.field_120 = a->field_120 - b->field_120;
    d.field_138 = a->field_138 - b->field_138;
    d.field_13c = a->field_13c - b->field_13c;
    d.field_170 = a->field_170 - b->field_170;
    d.field_140 = a->field_140 - b->field_140;
    d.field_150 = a->field_150 - b->field_150;
    d.field_160 = a->field_160 - b->field_160;
    d.field_174 = a->field_174 - b->field_174;
    d.field_178 = a->field_178 - b->field_178;
    d.field_17c = a->field_17c - b->field_17c;
    d.field_180 = a->field_180 - b->field_180;
    d.field_184 = a->field_184 - b->field_184;
    d.field_190 = a->field_190 - b->field_190;
    d.field_1a0 = a->field_1a0 - b->field_1a0;
    d.field_1a4 = a->field_1a4 - b->field_1a4;
    if (callee_455ebc()->field_70 != 0) {
        d.field_1f0 = a->field_1f0 - b->field_1f0;
        {
        int x = a->field_1f4;
        int y = b->field_1f4;
        d.field_1f4 = x >= 0 ? x : y;
    }
        {
        int x = a->field_1f8;
        int y = b->field_1f8;
        d.field_1f8 = x >= 0 ? x : y;
    }
        d.field_1fc = a->field_1fc - b->field_1fc;
        d.field_200 = a->field_200 - b->field_200;
        d.field_1b0 = a->field_1b0 - b->field_1b0;
        d.field_1c0 = a->field_1c0 - b->field_1c0;
        d.field_1d0 = a->field_1d0 - b->field_1d0;
        d.field_1e0 = a->field_1e0 - b->field_1e0;
        d.field_204 = a->field_204 - b->field_204;
    }
    d.field_210 = a->field_210 - b->field_210;
    d.field_220 = a->field_220 - b->field_220;
    d.field_230 = a->field_230 - b->field_230;
    d.field_234 = a->field_234 - b->field_234;
    d.field_238 = a->field_238 - b->field_238;
    d.field_23c = a->field_23c - b->field_23c;
    d.field_240 = a->field_240 - b->field_240;
    d.field_244 = a->field_244 - b->field_244;
    d.field_248 = a->field_248 - b->field_248;
    {
        int x = a->field_330;
        int y = b->field_330;
        d.field_330 = x >= 0 ? x : y;
    }
    {
        int x = a->field_334;
        int y = b->field_334;
        d.field_334 = x >= 0 ? x : y;
    }
    d.field_338 = a->field_338;
    d.field_370 = b->field_370 - a->field_370;
    d.field_374 = b->field_374 - a->field_374;
    d.field_380 = b->field_380 - a->field_380;
    d.field_340 = a->field_340 - b->field_340;
    d.field_344 = a->field_344 - b->field_344;
    d.field_348 = a->field_348 - b->field_348;
    d.field_34c = a->field_34c - b->field_34c;
    d.field_350 = a->field_350 - b->field_350;
    d.field_354 = a->field_354 - b->field_354;
    d.field_358 = a->field_358 - b->field_358;
    d.field_35c = a->field_35c - b->field_35c;
    d.field_360 = a->field_360 - b->field_360;
    d.field_364 = a->field_364 - b->field_364;
    d.field_368 = a->field_368 - b->field_368;
    d.field_36c = a->field_36c - b->field_36c;
    callee_3d4acc(self, &d);
}

typedef void* (*Factory425de0)(void*);
extern Factory425de0 gFactories_bdf230[] __attribute__((visibility("hidden")));    // 0x7100bdf230

// 0x7100425de0: creates object kind ID with ARG through the factory table (0x53 kinds), or returns null.
void* create_425de0(int id, void* arg) {
    if (static_cast<unsigned int>(id) < 0x53) {
        return gFactories_bdf230[id](arg);
    }
    return nullptr;
}
