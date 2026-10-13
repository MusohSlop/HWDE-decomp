// Skinned-model overrides found by tools/family_scan.py: each runs the model base's version
// and then the skin set's (at +12a0 or +12e0, depending on the model class). They belong to
// the model classes built by misc/model_builders.cpp and are grouped here until those files
// are linked; functions are named after their address. Status: matching/README.md.

class SkinSet {
public:
    void apply(int mode, void* a, void* b, void* model);                    // 0x7100595e48
    void refresh(void* model);                                              // 0x7100595dd0
};

class ModelCore {
public:
    void apply(int mode, void* a, void* b);                                 // 0x710059456c
    unsigned char prepare();                                                // 0x7100592f04
};

// The base of the second group of +12e0 models.
class ModelCoreAlt {
public:
    void apply(int mode, void* a, void* b);                                 // 0x7100591150
};

struct SkinHost12a0 {
    unsigned char pad[0x1298];
    unsigned short flags;     // +1298
    unsigned char pad129a[6];
    SkinSet skins;            // +12a0
};
struct SkinHost12e0 {
    unsigned char pad[0x1298];
    unsigned short flags;     // +1298
    unsigned char pad129a[0x46];
    SkinSet skins;            // +12e0
};


// 0x7100072d18
void apply_skinned_72d18(SkinHost12a0* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCore*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

// 0x7100074410
void apply_skinned_74410(SkinHost12a0* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCore*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

// 0x7100074ae0
void apply_skinned_74ae0(SkinHost12a0* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCore*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

// 0x710044e73c
void apply_skinned_44e73c(SkinHost12a0* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCore*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

// 0x7100450cc0
void apply_skinned_450cc0(SkinHost12a0* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCore*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}


// 0x7100072dd4
unsigned char prepare_skinned_72dd4(SkinHost12a0* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

// 0x71000744cc
unsigned char prepare_skinned_744cc(SkinHost12a0* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

// 0x7100074b9c
unsigned char prepare_skinned_74b9c(SkinHost12a0* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

// 0x710044e7f8
unsigned char prepare_skinned_44e7f8(SkinHost12a0* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

// 0x7100450d7c
unsigned char prepare_skinned_450d7c(SkinHost12a0* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}



// 0x7100073d40
void apply_skinned_73d40(SkinHost12e0* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCore*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

// 0x710021d628
void apply_skinned_21d628(SkinHost12e0* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCoreAlt*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

// 0x710021e3a8
void apply_skinned_21e3a8(SkinHost12e0* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCoreAlt*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

// 0x710021ffa8
void apply_skinned_21ffa8(SkinHost12e0* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCoreAlt*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

// 0x7100220668
void apply_skinned_220668(SkinHost12e0* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCoreAlt*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}


// 0x7100073dfc
unsigned char prepare_skinned_73dfc(SkinHost12e0* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

// 0x710021d6e4
unsigned char prepare_skinned_21d6e4(SkinHost12e0* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

// 0x710021e464
unsigned char prepare_skinned_21e464(SkinHost12e0* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

// 0x7100220064
unsigned char prepare_skinned_220064(SkinHost12e0* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

// 0x7100220724
unsigned char prepare_skinned_220724(SkinHost12e0* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

// More skinned-model overrides found by a shape scan: the same body as above with the skin set at
// other offsets (and three with other bases).
class ModelCore222070 {
public:
    void apply(int mode, void* a, void* b);                                 // 0x7100222070
};
class ModelCore54b044 {
public:
    void apply(int mode, void* a, void* b);                                 // 0x710054b044
};

struct SkinHost12b0 {
    unsigned char pad[0x12b0];
    SkinSet skins;            // +12b0
};

// 0x7100073644
void apply_skinned_73644(SkinHost12b0* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCore*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

struct SkinHost12f0 {
    unsigned char pad[0x12f0];
    SkinSet skins;            // +12f0
};

// 0x710021dce8
void apply_skinned_21dce8(SkinHost12f0* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCoreAlt*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

// 0x710021ea88
void apply_skinned_21ea88(SkinHost12b0* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCore*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

struct SkinHost1f20 {
    unsigned char pad[0x1f20];
    SkinSet skins;            // +1f20
};

// 0x710021f208
void apply_skinned_21f208(SkinHost1f20* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCore222070*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

struct SkinHost1330 {
    unsigned char pad[0x1330];
    SkinSet skins;            // +1330
};

// 0x710021f8e8
void apply_skinned_21f8e8(SkinHost1330* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCore54b044*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

struct SkinHost12d0 {
    unsigned char pad[0x12d0];
    SkinSet skins;            // +12d0
};

// 0x710023f58c
void apply_skinned_23f58c(SkinHost12d0* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCore*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

// 0x71003e5f08
void apply_skinned_3e5f08(SkinHost12b0* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCore*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

struct SkinHost1320 {
    unsigned char pad[0x1320];
    SkinSet skins;            // +1320
};

// 0x71004106b8
void apply_skinned_4106b8(SkinHost1320* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCore*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

struct SkinHost1470 {
    unsigned char pad[0x1470];
    SkinSet skins;            // +1470
};

// 0x7100410d98
void apply_skinned_410d98(SkinHost1470* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCore*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

struct SkinHost12c0 {
    unsigned char pad[0x12c0];
    SkinSet skins;            // +12c0
};

// 0x7100411478
void apply_skinned_411478(SkinHost12c0* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCore*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

struct SkinHost13d0 {
    unsigned char pad[0x13d0];
    SkinSet skins;            // +13d0
};

// 0x710044e038
void apply_skinned_44e038(SkinHost13d0* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCore*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

struct SkinHost14c0 {
    unsigned char pad[0x14c0];
    SkinSet skins;            // +14c0
};

// 0x710044ee38
void apply_skinned_44ee38(SkinHost14c0* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCore*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

struct SkinHost1380 {
    unsigned char pad[0x1380];
    SkinSet skins;            // +1380
};

// 0x71004505c0
void apply_skinned_4505c0(SkinHost1380* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCore*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

struct SkinHost1430 {
    unsigned char pad[0x1430];
    SkinSet skins;            // +1430
};

// 0x71004513a8
void apply_skinned_4513a8(SkinHost1430* model, int mode, void* a, void* b) {
    reinterpret_cast<ModelCore*>(model)->apply(mode, a, b);
    model->skins.apply(mode, a, b, model);
}

// The matching prepare overrides at the other skin-set offsets (shape scan).

struct PrepHost12b0 {
    unsigned char pad[0x1298];
    unsigned short flags;     // +1298
    unsigned char pad129a[0x16];
    SkinSet skins;            // +12b0
};

// 0x710007371c
unsigned char prepare_skinned_7371c(PrepHost12b0* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

struct PrepHost12f0 {
    unsigned char pad[0x1298];
    unsigned short flags;     // +1298
    unsigned char pad129a[0x56];
    SkinSet skins;            // +12f0
};

// 0x710021dda4
unsigned char prepare_skinned_21dda4(PrepHost12f0* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

// 0x710021eb44
unsigned char prepare_skinned_21eb44(PrepHost12b0* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

struct PrepHost1f20 {
    unsigned char pad[0x1298];
    unsigned short flags;     // +1298
    unsigned char pad129a[0xc86];
    SkinSet skins;            // +1f20
};

// 0x710021f2c4
unsigned char prepare_skinned_21f2c4(PrepHost1f20* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

struct PrepHost1330 {
    unsigned char pad[0x1298];
    unsigned short flags;     // +1298
    unsigned char pad129a[0x96];
    SkinSet skins;            // +1330
};

// 0x710021f9a4
unsigned char prepare_skinned_21f9a4(PrepHost1330* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

struct PrepHost12d0 {
    unsigned char pad[0x1298];
    unsigned short flags;     // +1298
    unsigned char pad129a[0x36];
    SkinSet skins;            // +12d0
};

// 0x710023f648
unsigned char prepare_skinned_23f648(PrepHost12d0* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

// 0x71003e5fcc
unsigned char prepare_skinned_3e5fcc(PrepHost12b0* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

struct PrepHost1320 {
    unsigned char pad[0x1298];
    unsigned short flags;     // +1298
    unsigned char pad129a[0x86];
    SkinSet skins;            // +1320
};

// 0x7100410774
unsigned char prepare_skinned_410774(PrepHost1320* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

struct PrepHost1470 {
    unsigned char pad[0x1298];
    unsigned short flags;     // +1298
    unsigned char pad129a[0x1d6];
    SkinSet skins;            // +1470
};

// 0x7100410e54
unsigned char prepare_skinned_410e54(PrepHost1470* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

struct PrepHost12c0 {
    unsigned char pad[0x1298];
    unsigned short flags;     // +1298
    unsigned char pad129a[0x26];
    SkinSet skins;            // +12c0
};

// 0x7100411534
unsigned char prepare_skinned_411534(PrepHost12c0* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

struct PrepHost13d0 {
    unsigned char pad[0x1298];
    unsigned short flags;     // +1298
    unsigned char pad129a[0x136];
    SkinSet skins;            // +13d0
};

// 0x710044e108
unsigned char prepare_skinned_44e108(PrepHost13d0* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

struct PrepHost14c0 {
    unsigned char pad[0x1298];
    unsigned short flags;     // +1298
    unsigned char pad129a[0x226];
    SkinSet skins;            // +14c0
};

// 0x710044eef4
unsigned char prepare_skinned_44eef4(PrepHost14c0* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

struct PrepHost1380 {
    unsigned char pad[0x1298];
    unsigned short flags;     // +1298
    unsigned char pad129a[0xe6];
    SkinSet skins;            // +1380
};

// 0x710045067c
unsigned char prepare_skinned_45067c(PrepHost1380* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}

struct PrepHost1430 {
    unsigned char pad[0x1298];
    unsigned short flags;     // +1298
    unsigned char pad129a[0x196];
    SkinSet skins;            // +1430
};

// 0x7100451464
unsigned char prepare_skinned_451464(PrepHost1430* model) {
    unsigned char ready = reinterpret_cast<ModelCore*>(model)->prepare();
    if (ready && (model->flags & 0x804) == 0x804)
        model->skins.refresh(model);
    return ready;
}
