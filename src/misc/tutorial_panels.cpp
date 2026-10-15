// Tutorial panel switches (0x710032ef7c, 0x71003989b0): open or close a tutorial panel's two
// animated parts and record the panel state; opening loads the tutorial layout on first use and
// closing it releases the layout node. Found by tools/family_scan.py --immediates. Names are
// descriptive placeholders. Status: matching/README.md.

#include "event/demo_effects.h"

struct PanelPart {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void play(int mode);
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void reset();
    virtual void rewind();
};
struct TutorialPanel32ef7c;
void init_panel_32e9a0(TutorialPanel32ef7c* panel);                                     // 0x710032e9a0
void update_panel_32f19c(void* track);                                  // 0x710032f19c

struct TutorialPanel32ef7c {
    int state;                // +00
    unsigned char pad4[0x10];
    int pending;              // +14
    unsigned char pad18[0x10];
    LightEffectNode* node;    // +28
    unsigned char pad30[0x220];
    unsigned char track[8];   // +250
    PanelPart* first;         // +258
    unsigned char pad260[0x28];
    PanelPart* second;        // +288
    unsigned char pad290[0x26634];
    bool loaded;              // +268c4
};

// 0x710032ef7c
void switch_panel_32ef7c(TutorialPanel32ef7c* panel, unsigned char open, unsigned char animate) {
    if (open) {
        if (panel->state)
            return;
        if (!panel->loaded) {
            panel->node = nullptr;
            gEffectManager->create_node(&panel->node, 0x41e9, "tutorial.bflyt");
            gEffectManager->flush();
            init_panel_32e9a0(panel);
            panel->loaded = true;
        }
        update_panel_32f19c(panel->track);
        bool animated = animate;
        update_panel_32f19c(panel->track);
        if (animated) {
            if (panel->first)
                panel->first->rewind();
            if (panel->first)
                panel->first->play(1);
            panel->state = 3;
            panel->pending = 0;
            return;
        } else {
            if (panel->second)
                panel->second->rewind();
            if (panel->first)
                panel->first->reset();
            if (panel->first)
                panel->first->play(1);
            panel->state = 1;
            panel->pending = 0;
            return;
        }
    } else {
        update_panel_32f19c(panel->track);
        bool animated = animate;
        update_panel_32f19c(panel->track);
        if (animated) {
            if (panel->second)
                panel->second->rewind();
            if (panel->second)
                panel->second->play(1);
            panel->state = 0;
            if (panel->loaded) {
                if (panel->node) {
                    EffectManager* manager = gEffectManager;
                    panel->node->detach(gResourceLoader->layout->root);
                    panel->node->release();
                    manager->nodes.remove(panel->node);
                    panel->node = nullptr;
                }
                panel->loaded = false;
            }
        } else {
            if (panel->first)
                panel->first->reset();
            if (panel->second)
                panel->second->reset();
            if (panel->second)
                panel->second->play(1);
            panel->state = 2;
            panel->pending = 0;
            return;
        }
    }
    panel->pending = 0;
}
struct TutorialPanel3989b0;
void init_panel_39863c(TutorialPanel3989b0* panel);                                     // 0x710039863c
void update_panel_398bd0(void* track);                                  // 0x7100398bd0

struct TutorialPanel3989b0 {
    int state;                // +00
    unsigned char pad4[0x10];
    int pending;              // +14
    unsigned char pad18[0x10];
    LightEffectNode* node;    // +28
    unsigned char pad30[0x220];
    unsigned char track[8];   // +250
    PanelPart* first;         // +258
    unsigned char pad260[0x28];
    PanelPart* second;        // +288
    unsigned char pad290[0x1454c];
    bool loaded;              // +147dc
};

// 0x71003989b0
void switch_panel_3989b0(TutorialPanel3989b0* panel, unsigned char open, unsigned char animate) {
    if (open) {
        if (panel->state)
            return;
        if (!panel->loaded) {
            panel->node = nullptr;
            gEffectManager->create_node(&panel->node, 0x41e9, "tutorial.bflyt");
            gEffectManager->flush();
            init_panel_39863c(panel);
            panel->loaded = true;
        }
        update_panel_398bd0(panel->track);
        bool animated = animate;
        update_panel_398bd0(panel->track);
        if (animated) {
            if (panel->first)
                panel->first->rewind();
            if (panel->first)
                panel->first->play(1);
            panel->state = 3;
            panel->pending = 0;
            return;
        } else {
            if (panel->second)
                panel->second->rewind();
            if (panel->first)
                panel->first->reset();
            if (panel->first)
                panel->first->play(1);
            panel->state = 1;
            panel->pending = 0;
            return;
        }
    } else {
        update_panel_398bd0(panel->track);
        bool animated = animate;
        update_panel_398bd0(panel->track);
        if (animated) {
            if (panel->second)
                panel->second->rewind();
            if (panel->second)
                panel->second->play(1);
            panel->state = 0;
            if (panel->loaded) {
                if (panel->node) {
                    EffectManager* manager = gEffectManager;
                    panel->node->detach(gResourceLoader->layout->root);
                    panel->node->release();
                    manager->nodes.remove(panel->node);
                    panel->node = nullptr;
                }
                panel->loaded = false;
            }
        } else {
            if (panel->first)
                panel->first->reset();
            if (panel->second)
                panel->second->reset();
            if (panel->second)
                panel->second->play(1);
            panel->state = 2;
            panel->pending = 0;
            return;
        }
    }
    panel->pending = 0;
}
