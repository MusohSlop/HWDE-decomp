// Skinned-model updates found by tools/family_scan.py --immediates: each refreshes the model's
// pose resource when its "dirty" flag is set, re-binds the bone buffer if it moved, refreshes the
// skin set and runs the model class's own update. They differ in the skin set's offset and in that
// last call; functions are named after their address, callees after theirs.
// Status: matching/README.md.

struct PoseEntry {
    int value0;
    unsigned int offset;      // +04
    long value8;
};

class BoneBinding {
public:
    void rebind();                                                          // 0x71005a9be8
    unsigned char pad[0x1018];
};

class SkinSet {
public:
    void refresh(void* model);                                              // 0x7100595dd0
};

PoseEntry* load_pose(void* resource, int a, int b, int c, int d, int e, int f, int g); // 0x710059685c

class UpdatedModel {
public:
    virtual void v000();
    virtual void v008();
    virtual void v010();
    virtual void v018();
    virtual void v020();
    virtual void v028();
    virtual void v030();
    virtual void v038();
    virtual void v040();
    virtual void v048();
    virtual void v050();
    virtual void v058();
    virtual void v060();
    virtual void v068();
    virtual void v070();
    virtual void v078();
    virtual void v080();
    virtual void v088();
    virtual void v090();
    virtual void v098();
    virtual void v0a0();
    virtual void v0a8();
    virtual void v0b0();
    virtual void v0b8();
    virtual void v0c0();
    virtual void v0c8();
    virtual void v0d0();
    virtual void v0d8();
    virtual void v0e0();
    virtual void v0e8();
    virtual void v0f0();
    virtual void v0f8();
    virtual void v100();
    virtual void v108();
    virtual void v110();
    virtual void v118();
    virtual void v120();
    virtual void v128();
    virtual void v130();
    virtual void v138();
    virtual void v140();
    virtual void v148();
    virtual void v150();
    virtual void v158();
    virtual void v160();
    virtual void v168();
    virtual void v170();
    virtual void bind_bones(BoneBinding* binding);                          // +178

    void prepare_pose();                                                    // 0x710059469c
    void bones_moved();                                                     // 0x7100072e2c

    unsigned char pad8[0x18];
    unsigned char* resource;  // +020
    unsigned char pad28[0x170];
    BoneBinding binding;      // +198
    unsigned char* bones;     // +11b0
    unsigned char pad11b8[0xa8];
    int pose_args[7];         // +1260
    unsigned char pad127c[4];
    PoseEntry* pose;          // +1280
    unsigned char pad1288[0xc];
    int pose_index;           // +1294
    unsigned short flags;     // +1298
    unsigned char pad129a[6];
};
static_assert(sizeof(UpdatedModel) == 0x12a0, "updated model size");

// The larger of two values by reference, like std::max. Going through references keeps the clamp a
// 32-bit select that is widened afterwards, as in the original.
template <typename T>
static inline const T& larger(const T& a, const T& b) {
    return a > b ? a : b;
}

// Shared by every update below (in the original each class has its own copy); always_inline keeps
// Clang from outlining it once it is used 22 times in this unit.
static inline __attribute__((always_inline)) void update_pose(UpdatedModel* model) {
    if (model->flags & 0x20)
        model->prepare_pose();
    unsigned short flags = model->flags;
    model->flags = flags | 0x800;
    if (flags & 0x10) {
        model->pose = load_pose(model->resource, model->pose_args[0], model->pose_args[1],
                                model->pose_args[2], model->pose_args[3], model->pose_args[4],
                                model->pose_args[5], model->pose_args[6]);
        if (model->resource) {
            int index = larger(model->pose_index, 0);
            unsigned char* bones = model->resource + model->pose[static_cast<unsigned int>(index)].offset + 0x30;
            if (bones != model->bones) {
                model->bones = bones;
                model->bones_moved();
                model->binding.rebind();
                model->bind_bones(&model->binding);
                model->flags |= 0x100;
            }
        }
        model->flags &= ~0x10;
    }
}

struct UpdateHost12a0 : UpdatedModel {
    SkinSet skins;            // +12a0
};

void finish_update_5932d0(UpdatedModel* model);                  // 0x71005932d0

// 0x7100072c08
void update_model_72c08(UpdateHost12a0* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_5932d0(model);
    model->flags &= ~0x800;
}

struct UpdateHost12e0 : UpdatedModel {
    unsigned char pad12a0[0x40];
    SkinSet skins;            // +12e0
};

void finish_update_592540(UpdatedModel* model);                  // 0x7100592540

// 0x7100073c30
void update_model_73c30(UpdateHost12e0* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_592540(model);
    model->flags &= ~0x800;
}

// 0x7100074300
void update_model_74300(UpdateHost12a0* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_5932d0(model);
    model->flags &= ~0x800;
}

// 0x71000749d0
void update_model_749d0(UpdateHost12a0* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_5932d0(model);
    model->flags &= ~0x800;
}

void finish_update_59105c(UpdatedModel* model);                  // 0x710059105c

// 0x710021d518
void update_model_21d518(UpdateHost12e0* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_59105c(model);
    model->flags &= ~0x800;
}

struct UpdateHost12f0 : UpdatedModel {
    unsigned char pad12a0[0x50];
    SkinSet skins;            // +12f0
};

void finish_update_222398(UpdatedModel* model);                  // 0x7100222398

// 0x710021dbd8
void update_model_21dbd8(UpdateHost12f0* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_222398(model);
    model->flags &= ~0x800;
}

// 0x710021e298
void update_model_21e298(UpdateHost12e0* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_59105c(model);
    model->flags &= ~0x800;
}

struct UpdateHost12b0 : UpdatedModel {
    unsigned char pad12a0[0x10];
    SkinSet skins;            // +12b0
};

void finish_update_5541e8(UpdatedModel* model);                  // 0x71005541e8

// 0x710021e978
void update_model_21e978(UpdateHost12b0* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_5541e8(model);
    model->flags &= ~0x800;
}

struct UpdateHost1f20 : UpdatedModel {
    unsigned char pad12a0[0xc80];
    SkinSet skins;            // +1f20
};

void finish_update_2212c4(UpdatedModel* model);                  // 0x71002212c4

// 0x710021f0f8
void update_model_21f0f8(UpdateHost1f20* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_2212c4(model);
    model->flags &= ~0x800;
}

struct UpdateHost1330 : UpdatedModel {
    unsigned char pad12a0[0x90];
    SkinSet skins;            // +1330
};

void finish_update_54aaa0(UpdatedModel* model);                  // 0x710054aaa0

// 0x710021f7d8
void update_model_21f7d8(UpdateHost1330* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_54aaa0(model);
    model->flags &= ~0x800;
}

// 0x710021fe98
void update_model_21fe98(UpdateHost12e0* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_59105c(model);
    model->flags &= ~0x800;
}

// 0x7100220558
void update_model_220558(UpdateHost12e0* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_59105c(model);
    model->flags &= ~0x800;
}

struct UpdateHost12d0 : UpdatedModel {
    unsigned char pad12a0[0x30];
    SkinSet skins;            // +12d0
};

void finish_update_22794c(UpdatedModel* model);                  // 0x710022794c

// 0x710023f47c
void update_model_23f47c(UpdateHost12d0* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_22794c(model);
    model->flags &= ~0x800;
}

void finish_update_591a08(UpdatedModel* model);                  // 0x7100591a08

// 0x71003e5df8
void update_model_3e5df8(UpdateHost12b0* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_591a08(model);
    model->flags &= ~0x800;
}

struct UpdateHost1320 : UpdatedModel {
    unsigned char pad12a0[0x80];
    SkinSet skins;            // +1320
};

// 0x71004105a8
void update_model_4105a8(UpdateHost1320* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_5932d0(model);
    model->flags &= ~0x800;
}

struct UpdateHost1470 : UpdatedModel {
    unsigned char pad12a0[0x1d0];
    SkinSet skins;            // +1470
};

// 0x7100410c88
void update_model_410c88(UpdateHost1470* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_5932d0(model);
    model->flags &= ~0x800;
}

struct UpdateHost12c0 : UpdatedModel {
    unsigned char pad12a0[0x20];
    SkinSet skins;            // +12c0
};

// 0x7100411368
void update_model_411368(UpdateHost12c0* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_5932d0(model);
    model->flags &= ~0x800;
}

struct UpdateHost13d0 : UpdatedModel {
    unsigned char pad12a0[0x130];
    SkinSet skins;            // +13d0
};

void finish_update_44c94c(UpdatedModel* model);                  // 0x710044c94c

// 0x710044df28
void update_model_44df28(UpdateHost13d0* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_44c94c(model);
    model->flags &= ~0x800;
}

void finish_update_591ec8(UpdatedModel* model);                  // 0x7100591ec8

// 0x710044e62c
void update_model_44e62c(UpdateHost12a0* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_591ec8(model);
    model->flags &= ~0x800;
}

struct UpdateHost14c0 : UpdatedModel {
    unsigned char pad12a0[0x220];
    SkinSet skins;            // +14c0
};

void finish_update_5c7d4c(UpdatedModel* model);                  // 0x71005c7d4c

// 0x710044ed28
void update_model_44ed28(UpdateHost14c0* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_5c7d4c(model);
    model->flags &= ~0x800;
}

// 0x7100450bb0
void update_model_450bb0(UpdateHost12a0* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_5932d0(model);
    model->flags &= ~0x800;
}

struct UpdateHost1430 : UpdatedModel {
    unsigned char pad12a0[0x190];
    SkinSet skins;            // +1430
};

void finish_update_557dfc(UpdatedModel* model);                  // 0x7100557dfc

// 0x7100451298
void update_model_451298(UpdateHost1430* model) {
    update_pose(model);
    model->skins.refresh(model);
    finish_update_557dfc(model);
    model->flags &= ~0x800;
}
