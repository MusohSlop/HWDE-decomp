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
