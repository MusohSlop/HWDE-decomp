// Fifth session, in progress: 0x71003ba734 (7,108 bytes), the stage-select menu's build (Menu3bdbf0::build in
// misc/s5_functions02.cpp's class: five layouts, the 32 stage panes, the face, plate, battle-area, attribute and
// recommend panes with their animations, ten text panes). 7,100 bytes here, 125 instructions off abstracted.
// Settled: every helper inlined (always_inline: the anim creation of 3b4e98, bind_new_anim, add_text); each of the
// plate, area and attribute loops starts with the find_pane of the template pane, so SimplifyCFG hoists it into the
// latch and the hide after the loop reuses it (as in the original); the stage slot is remapped by a three-case
// chain (18-22 +9, 23-26 -5, 27-31 -5) and the DLC test is computed first in its branch.
// Still off: the original keeps this in x24 and the five layout addresses in x25/x27/x19/x26/x22 from the start
// (here this is spilled early), and its DLC branch keeps slot < 32 as a bool across the hide calls (a phi from
// jump threading); the rest is register allocation and spill slots.
// To build: python build/s5/g3ba/mk.py turns misc/s5_functions02.cpp's menu part plus this file into a scratch unit
// (the pane gains slots 13-16, rotate, scale, size and origin; the menu's panes become panes[32]); 3bd1d8, 3bdbf0 and
// 3beef0 still compare with 0 word diffs there.
// Maps: got:gMgr_c22a00=0x7100c22a00 got:gApp_c21db0=0x7100c21db0 got:_ZTV10Anim3ba734=0x7100c2a698
//   got:_ZTV10Text3ba734=0x7100c22f68 got:kStagePanes_bdb398=0x7100c2b450 got:kFaceParents_bdb498=0x7100c2b458
//   with --name _ZN10Menu3bdbf05buildEv.

struct Mgr3ba734 {
    void load(Layout3bdbf0** layout, int id, const char* name);        // 0x71001e2360
    void attach_resource(void* res);        // 0x71001e26e0
    void flush();        // 0x71001e26e4
    void sync();        // 0x71001e26e8
    void release(int id);        // 0x71001e22e4
};
extern Mgr3ba734* gMgr_c22a00;

struct Sys3ba734 {
    unsigned char pad0[0x10];
    unsigned char device[0x10];       // +10
};
struct App3ba734 {
    unsigned char pad0[0x2af8];
    Sys3ba734* sys;                   // +2af8
};
extern App3ba734* gApp_c21db0;

Pane3bdbf0* clone_pane_5dec80(Pane3bdbf0* pane, void* device);        // 0x71005dec80
void add_child_5da17c(Pane3bdbf0* parent, Pane3bdbf0* child);        // 0x71005da17c
AnimBase3ba734* get_anim_1e37c8(Layout3bdbf0* layout, const char* name, bool create);        // 0x71001e37c8
Pane3bdbf0* find_1f8224(Layout3bdbf0* layout, Pane3bdbf0* pane);        // 0x71001f8224

__attribute__((always_inline)) static inline Anim3ba734* create_anim(Layout3bdbf0* layout, void* device, const AnimInfo3ba734& info) {
    void* block = info.block;
    if (block == nullptr) {
        return nullptr;
    }
    Anim3ba734* anim = new Anim3ba734();
    if (anim != nullptr) {
        layout->anims.link_prev(&anim->link);
        anim->set_resource(device, layout->accessor, block);
    }
    return anim;
}

__attribute__((always_inline)) static inline void bind_new_anim(Pane3bdbf0* pane, Anim3ba734** slot, Layout3bdbf0* layout, void* device,
                                 const char* name) {
    AnimInfo3ba734 info(layout->find_anim(name));
    *slot = create_anim(layout, device, info);
    pane->bind_anim(*slot, true, true);
    if (*slot != nullptr) {
        (*slot)->set_enable(false);
    }
}

__attribute__((always_inline)) static inline void add_text(Pane3bdbf0* root, const char* name, Text3ba734** out) {
    Pane3bdbf0* parent = root->find_pane(name, true);
    *out = new Text3ba734();
    (*out)->set_visible(false);
    add_child_5da17c(parent, *out);
    if ((parent->origin & 0xc) == 4) {
        (*out)->set_translate(Float3_3bdbf0{0.0f, parent->size[1] * -0.5f, 0.0f});
    }
}

// 0x71003ba734
void Menu3bdbf0::build() {
    if (ready) {
        return;
    }
    memset(panes, 0, sizeof(Pane3bdbf0*) * 32);
    memset(&rcm_pos, 0, 0x80);
    layout = nullptr;
    plates = nullptr;
    areas = nullptr;
    attributes = nullptr;
    recommend = nullptr;
    field_11670 = -1;
    for (int i = 0; i < 11; i++) {
        faces[i].pane = nullptr;
    }
    for (int i = 0; i < 32; i++) {
        plates_11678[i].pane = nullptr;
    }
    for (int i = 0; i < 32; i++) {
        attrs[i].pane = nullptr;
    }
    rcm = nullptr;
    gMgr_c22a00->load(&layout, 0x4200, kSnaSeleParts_7db544);
    gMgr_c22a00->load(&plates, 0x4200, kSnaPlateParts_7db559);
    gMgr_c22a00->load(&areas, 0x4200, kSnaBtlarea_7db56f);
    gMgr_c22a00->load(&attributes, 0x41e5, kIconAttribute_7d5c0b);
    gMgr_c22a00->load(&recommend, 0x41e5, kIconRecommend_7da6d1);
    Sys3ba734* sys = gApp_c21db0->sys;
    gMgr_c22a00->sync();
    gMgr_c22a00->attach_resource(res_830);
    Pane3bdbf0** stage_panes = panes;
    for (int i = 0; i < 32; i++) {
        stage_panes[i] = layout->root->find_pane(kStagePanes_bdb398[i], true);
    }
    void* device = sys->device;
    sources_a40[0] = find(kIconPos04Dlc_7db581);
    sources_a40[1] = find(kIconPos05Dlc_7db591);
    sources_a40[2] = find(kIconPos08Dlc_7db5a1);
    sources_a40[3] = find(kIconPos09Dlc_7db5b1);
    rcm_pos = find(kIconRcmPos_7db5c1);
    for (int i = 0; i < 26; i++) {
        anims[i] = get_anim_1e37c8(layout, kSelAnims_bdb558[i], true);
    }
    for (int i = 0; i < 26; i++) {
        if (anims[i] != nullptr) {
            anims[i]->play();
        }
        if (anims[i] != nullptr) {
            anims[i]->set_enable(false);
        }
    }
    faces[0].pane = find(kFaceParents_bdb498[0]);
    faces[0].anim = static_cast<Anim3ba734*>(anims[11]);
    for (int i = 1; i < 7; i++) {
        faces[i].pane = clone_pane_5dec80(faces[0].pane, gApp_c21db0->sys->device);
        add_child_5da17c(find(kFaceParents_bdb498[i]), faces[i].pane);
        bind_new_anim(faces[i].pane, &faces[i].anim, layout, device, kFace_7d9d39);
        faces[i].pane->set_translate(Float3_3bdbf0{0.0f, 0.0f, 0.0f});
    }
    for (int i = 0; i < 4; i++) {
        faces[7 + i].pane = find(kFacePanes_bdb628[i]);
        bind_new_anim(faces[7 + i].pane, &faces[7 + i].anim, layout, device, kFace_7d9d39);
    }
    AnimBase3ba734* a = get_anim_1e37c8(layout, kDifficulty_7db6b0, true);
    difficulty = a;
    if (a != nullptr) {
        a->set_frame(0.0f);
    }
    a = get_anim_1e37c8(layout, kSkulltula_7db6bb, true);
    skulltula = a;
    if (a != nullptr) {
        a->set_frame(0.0f);
    }
    cursor = find(kCursorEasy_7db6c5);
    cursor->flags |= 1;
    windows[0] = find(kWindowEasy_7db6d1);
    windows[1] = find(kWindowNormal_7db6dd);
    windows[2] = find(kWindowHard_7db6eb);
    windows[3] = find(kWindowVeryhard_7db6f7);

    for (int i = 0; i < 32; i++) {
        plates_11678[i].pane = clone_pane_5dec80(plates->root->find_pane(kSnaPlateParts_740e57, true), gApp_c21db0->sys->device);
        Plate3ba734& plate = plates_11678[i];
        add_child_5da17c(stage_panes[i], plate.pane);
        int slot = i;
        if (i >= 18 && i <= 22) {
            slot += 9;
        } else if (i >= 23 && i <= 26) {
            slot -= 5;
        } else if (i >= 27 && i <= 31) {
            slot -= 5;
        }
        const char* const* names;
        if (slot >= 27) {
            bool dlc = slot < 32;
            plate.pane->find_pane(kSnaPlateOff_7db74d, true)->flags &= ~1;
            plate.pane->find_pane(kSnaPlateOn01_7db75b, true)->flags &= ~1;
            names = dlc ? kPlateAnimsDlc_bdb698 : kPlateAnims_bdb648;
        } else {
            plate.pane->find_pane(kSnaPlateOffDlc_7db76b, true)->flags &= ~1;
            plate.pane->find_pane(kSnaPlateOnDlc_7db77d, true)->flags &= ~1;
            names = kPlateAnims_bdb648;
        }
        for (int j = 0; j < 10; j++) {
            bind_new_anim(plate.pane, &plate.anims[j], plates, device, names[j]);
        }
    }
    plates->root->find_pane(kSnaPlateParts_740e57, true)->flags &= ~1;

    float scale = areas->root->scale[0] / layout->root->scale[0];
    for (int i = 0; i < 32; i++) {
        areas_12478[i].pane = clone_pane_5dec80(areas->root->find_pane(kSnaBtlarea_740e4b, true), gApp_c21db0->sys->device);
        Area3ba734& area = areas_12478[i];
        add_child_5da17c(stage_panes[i], area.pane);
        find_1f8224(layout, area.pane)->set_scale(scale, scale);
        for (int j = 0; j < 3; j++) {
            bind_new_anim(area.pane, &area.anims[j], areas, device, kAreaAnims_bdb6e8[j]);
        }
        area.attr_pos = area.pane->find_pane(kBtlAttributePos_7da7ad, true);
        if (area.pane == nullptr) {
            continue;
        }
        add_text(area.pane, kFontBtlAreaName_7da807, &area.texts[0]);
        if (area.pane == nullptr) {
            continue;
        }
        add_text(area.pane, kFontEffAttribute_7da81a, &area.texts[1]);
        if (area.pane == nullptr) {
            continue;
        }
        add_text(area.pane, kFontRes_7d5c8f, &area.texts[2]);
    }
    areas->root->find_pane(kSnaBtlarea_740e4b, true)->flags &= ~1;
    gMgr_c22a00->flush();

    for (int i = 0; i < 32; i++) {
        attrs[i].pane = clone_pane_5dec80(attributes->root->find_pane(kIconAttribute_740d16, true), gApp_c21db0->sys->device);
        PaneAnim3ba734& attr = attrs[i];
        add_child_5da17c(areas_12478[i].attr_pos, attr.pane);
        float w = areas_12478[i].attr_pos->size[0];
        float h = areas_12478[i].attr_pos->size[1];
        attr.pane->set_size(w * layout->root->scale[0], h * layout->root->scale[1]);
        bind_new_anim(attr.pane, &attr.anim, attributes, device, kAttribute_7d5c33);
    }
    attributes->root->find_pane(kIconAttribute_740d16, true)->flags &= ~1;
    gMgr_c22a00->sync();

    rcm = clone_pane_5dec80(recommend->root->find_pane(kRecommend_7db794, true), gApp_c21db0->sys->device);
    add_child_5da17c(rcm_pos, rcm);
    for (int j = 0; j < 3; j++) {
        bind_new_anim(rcm, &rcm_anims[j], recommend, device, kRcmAnims_bdb700[j]);
    }
    recommend->root->find_pane(kRecommend_7db794, true)->flags &= ~1;

    if (layout->root != nullptr) {
        add_text(layout->root, kFontHen_7db79e, &texts[0]);
    }
    if (layout->root != nullptr) {
        add_text(layout->root, kText7a7_7db7a7, &texts[1]);
    }
    if (layout->root != nullptr) {
        add_text(layout->root, kText7b5_7db7b5, &texts[2]);
    }
    if (layout->root != nullptr) {
        add_text(layout->root, kText7c3_7db7c3, &texts[3]);
    }
    if (layout->root != nullptr) {
        add_text(layout->root, kText7d2_7db7d2, &texts[4]);
    }
    if (layout->root != nullptr) {
        add_text(layout->root, kText7e1_7db7e1, &texts[5]);
    }
    if (layout->root != nullptr) {
        add_text(layout->root, kText7ed_7db7ed, &texts[6]);
    }
    if (layout->root != nullptr) {
        add_text(layout->root, kText7f7_7db7f7, &texts[7]);
    }
    if (layout->root != nullptr) {
        add_text(layout->root, kText803_7db803, &texts[8]);
    }
    if (layout->root != nullptr) {
        add_text(layout->root, kText80d_7db80d, &texts[9]);
    }
    Pane3bdbf0* anyone = find(kIconAnyone00_7db81b);
    Float3_3bdbf0 t = anyone->translate;
    t.y += 5.0f;
    anyone->set_translate(t);
    sub_b6be0.init(0x41e5);
    for (int i = 0; i < 320; i++) {
        gMgr_c22a00->release(0x4200);
    }
    ready = 1;
}
