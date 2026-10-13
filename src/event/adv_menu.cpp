// Matching candidates for the Adventure Mode menu scene 0x71002734bc-0x7100274234.
// Names are descriptive placeholders. Status: matching/README.md.

#include "resource/resource_frame.h"

extern "C" void* memset(void* dest, int value, unsigned long size);

class GameState {
public:
    unsigned char pad[0x1bb7c];
    unsigned int mode;        // +1bb7c
};

class Game {
public:
    GameState* state();                                                     // 0x7100204c10
};
Game* get_game();                                                           // 0x7100204728
void* get_unit_database();                                                  // 0x710020ec80

class BattleParams {
public:
    void clear();                                                           // 0x71001a8e1c
};
BattleParams* get_battle_params();                                          // 0x71001a8c38

void prepare_menu_board(unsigned int mode, int flags);                      // 0x7100283e88

class TitleBanner {
public:
    void set_layer(int layer);                                              // 0x71001e1e2c
    void show_default();                                                    // 0x71001e1fd8
    void show_text(int id);                                                 // 0x71001e216c
};
// Reached through the GOT slot at 0x7100c22a00.
extern TitleBanner* gTitleBanner;
// Reached through the GOT slot at 0x7100c2a798.
extern ResourceFrame gMenuFrame;

void load_menu_scene() {
    gMenuFrame.open(0, 0x1ce8, nullptr);
    get_battle_params()->clear();
    unsigned int mode = get_game()->state()->mode;
    prepare_menu_board(mode, 0);
    gTitleBanner->set_layer(2);
    if (static_cast<int>(mode) >= 7)
        gTitleBanner->show_text(mode + 0x461e);
    else
        gTitleBanner->show_default();
}

class MenuView {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void open();      // +20
    virtual void v28();
    virtual void v30();
    virtual void draw();      // +38
    virtual void v40();
    virtual void v48();
    virtual void render();    // +50
    virtual void refresh();   // +58
};

class Fader {
public:
    void begin(int layer);                                                  // 0x71001df744
    void end();                                                             // 0x71001df838
};
// Reached through the GOT slot at 0x7100c22a40.
extern Fader* gFader;

struct DrawParams {
    int value0;
    int value4;
    int value8;
    int valuec;
    int value10;
};

class Renderer {
public:
    void begin(void* target, DrawParams* params);                           // 0x71003dfec8
    void end(void* target);                                                 // 0x71003dff50
};
// Reached through the GOT slots at 0x7100c22db8 and 0x7100c21db0.
extern Renderer* gRenderer;
extern void* gRenderTarget;

class MenuScene {
public:
    void refresh();                                                         // 0x7100273ccc
    void draw();                                                            // 0x7100273e1c

    unsigned char pad[0x2d424];
    unsigned int page;        // +2d424
    unsigned char pad2d428[8];
    MenuView* pages[1];       // +2d430
    MenuView* overlay;        // +2d438
};

void MenuScene::refresh() {
    gFader->begin(0);
    get_game();
    get_game()->state();
    get_unit_database();
    if (overlay)
        overlay->refresh();
    if (MenuView* view = pages[page])
        view->open();
    gFader->end();
    gFader->begin(10);
    gFader->end();
}

void MenuScene::draw() {
    Renderer* renderer = gRenderer;
    void* target = gRenderTarget;
    DrawParams params;
    memset(&params, 0, 0x10);
    params.value4 = 2;
    params.valuec = 2;
    params.value10 = 0;
    renderer->begin(target, &params);
    if (overlay)
        overlay->render();
    if (MenuView* view = pages[page])
        view->draw();
    renderer->end(target);
}

class DemoPanelSystem {
public:
    void update();                                                          // 0x71002648dc
};
class DemoEffectPool {
public:
    void update();                                                          // 0x7100260fe8
};
class AdvCaption {
public:
    void update();                                                          // 0x7100266f04
};
class AdvEffects {
public:
    void update();                                                          // 0x7100267c44
};
class AdvBoard {
public:
    void update();                                                          // 0x71002a016c
};
class BoardCursor {
public:
    void update();                                                          // 0x7100289714
};
class BoardUnits {
public:
    void update();                                                          // 0x7100292694
};
class BoardPopups {
public:
    void update();                                                          // 0x71002a7a80
};
class BoardCamera {
public:
    void update();                                                          // 0x7100288a18
};
// Reached through GOT slots in 0x7100c2a648-0x7100c2a790.
extern DemoPanelSystem* gDemoPanelSystem;
extern DemoEffectPool* gDemoEffectPool;
extern AdvCaption* gAdvCaption;
extern AdvEffects* gAdvEffects;
extern AdvBoard* gAdvBoard;
extern BoardCursor* gBoardCursor;
extern BoardUnits* gBoardUnits;
extern BoardPopups* gBoardPopups;
extern BoardCamera* gBoardCamera;

struct FrameHeader {
    unsigned short width;     // +0
    unsigned short height;    // +2
    unsigned short span;      // +4
    unsigned short pad6;
    unsigned short count;     // +8
};

struct FrameEntry {
    short kind;               // +0
    unsigned short start;     // +2
    unsigned short row;       // +4
    unsigned short length;    // +6
};

class BoardOverride {
public:
    FrameHeader* frames();                                                  // 0x7100290f94
    FrameEntry* frame(unsigned short index);                                // 0x7100290f9c
};
// Reached through the GOT slot at 0x7100c2a6f0.
extern BoardOverride gBoardOverride;

class BoardScene {
public:
    int update();                                                           // 0x7100273efc
    int frame_of(int kind);                                                 // 0x7100274080

    unsigned char pad0[8];
    int state;                // +08
    int previous;             // +0c
    unsigned char pad10[8];
    int tick;                 // +18
    unsigned int clock;       // +1c
    int slow_tick;            // +20
    unsigned int slow_clock;  // +24
};

int BoardScene::update() {
    tick = (tick + 1) % 20;
    if (!tick)
        clock = static_cast<int>(clock + 1) % 20000;
    slow_tick = (slow_tick + 1) % 10;
    if (!slow_tick)
        slow_clock = static_cast<int>(slow_clock + 1) % 20000;
    gBoardCursor->update();
    gDemoPanelSystem->update();
    gDemoEffectPool->update();
    gAdvBoard->update();
    gBoardUnits->update();
    gBoardPopups->update();
    gAdvCaption->update();
    gAdvEffects->update();
    gBoardCamera->update();
    int old = previous;
    previous = state;
    return old;
}

int BoardScene::frame_of(int kind) {
    FrameHeader* header = gBoardOverride.frames();
    if (!header->count)
        return kind;
    int result = kind;
    for (unsigned short i = 0; i < header->count; ++i) {
        FrameEntry* entry = gBoardOverride.frame(i);
        if (entry->kind != kind)
            continue;
        unsigned int period = entry->length / header->width + 1;
        unsigned int time = clock;
        if (get_game()->state()->mode == 8 && kind == 0xda)
            time = slow_clock;
        unsigned int phase = time % period;
        if (!phase)
            return result;
        result = entry->row / header->height * (header->span / header->width) +
                 (header->width * (phase - 1) + entry->start) / header->width;
    }
    return result;
}
