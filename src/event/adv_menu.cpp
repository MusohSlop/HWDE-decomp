// Matching candidates for the Adventure Mode menu scene 0x71002734bc-0x71002748d4, plus
// BoardOverlay (0x7100280f6c).
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
    void hide();                                                            // 0x71001e1c9c
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
    virtual ~MenuView();
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
    void release(void* fade, void* target);                                 // 0x71001dfb5c
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
    void shutdown();                                                        // 0x71002731e4
    void refresh();                                                         // 0x7100273ccc
    void draw();                                                            // 0x7100273e1c

    unsigned char pad[0x2d424];
    unsigned int page;        // +2d424
    unsigned char pad2d428[8];
    MenuView* views[8];       // +2d430: [1] is the overlay
    struct SharedObject* object2d470; // +2d470
    struct SharedObject* object2d478; // +2d478
    unsigned char fade2d480[8]; // +2d480
};

void MenuScene::refresh() {
    gFader->begin(0);
    get_game();
    get_game()->state();
    get_unit_database();
    if (views[1])
        views[1]->refresh();
    if (MenuView* view = views[page])
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
    if (views[1])
        views[1]->render();
    if (MenuView* view = views[page])
        view->draw();
    renderer->end(target);
}

class DemoPanelSystem {
public:
    void draw();                                                            // 0x7100266740
    void initialize();                                                      // 0x7100263d58
    void finalize();                                                        // 0x71002637fc
    void update();                                                          // 0x71002648dc
};
class DemoEffectPool {
public:
    void draw();                                                            // 0x710026302c
    void initialize();                                                      // 0x7100260c0c
    unsigned char restart();                                                // 0x7100262e78
    void finalize();                                                        // 0x7100260a48
    void update();                                                          // 0x7100260fe8
};
class AdvCaption {
public:
    void initialize();                                                      // 0x7100266cd8
    void draw();                                                            // 0x7100266f58
    void finalize();                                                        // 0x7100266a20
    void set_value0c(int value);                                            // 0x7100266ec0
    void update();                                                          // 0x7100266f04
};
class AdvEffects {
public:
    void draw_start();                                                      // 0x7100268f10
    void draw_screens();                                                    // 0x7100268fc8
    void initialize();                                                      // 0x71002676ec
    void play_exit(unsigned char forward);                                  // 0x7100269440
    void finalize();                                                        // 0x710026731c
    void update();                                                          // 0x7100267c44

    unsigned char pad[0x494];
    int value494;             // +494
};
class AdvBoard {
public:
    void initialize();                                                      // 0x710029b5f8
    void finalize();                                                        // 0x710029a20c
    void reset_view();                                                      // 0x71002a64fc
    void update();                                                          // 0x71002a016c
};
class BoardCursor {
public:
    void initialize();                                                      // 0x7100288ef4
    void draw();                                                            // 0x710028a150
    void finalize();                                                        // 0x7100288be0
    void update();                                                          // 0x7100289714

    unsigned char pad[0x10];
    int value10;              // +10
};
class BoardUnits {
public:
    void initialize();                                                      // 0x7100291e14
    void draw();                                                            // 0x7100298670
    void finalize();                                                        // 0x710029194c
    void update();                                                          // 0x7100292694
};
class BoardPopups {
public:
    void initialize();                                                      // 0x71002a73d4
    void draw();                                                            // 0x71002aa188
    void finalize();                                                        // 0x71002a6e88
    void reset();                                                           // 0x71002aadac
    void update();                                                          // 0x71002a7a80
};
class BoardCamera {
public:
    void initialize();                                                      // 0x7100288a10
    unsigned char pressed(int button);                                      // 0x7100288a38
    void release(int button);                                               // 0x7100288a24
    void finalize();                                                        // 0x7100288a14
    void update();                                                          // 0x7100288a18
    void set_mode(int a, int b);                                            // 0x7100288a20
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
    void reset();                                                           // 0x7100290e90

    unsigned char pad[0x30];
    unsigned char active;     // +30
    unsigned char pad31[3];
    int phase;                // +34
};
// Reached through the GOT slot at 0x7100c2a6f0.
extern BoardOverride gBoardOverride;

class BoardScene {
public:
    int update();                                                           // 0x7100273efc
    int frame_of(int kind);                                                 // 0x7100274080
    unsigned char start();                                                  // 0x7100274238

    unsigned char pad0[8];
    int state;                // +08
    int previous;             // +0c
    struct BoardStateView* query; // +10
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

struct BoardStateView {
    unsigned char pad[0xd4];
    int valued4;              // +d4
};

struct Player {
    unsigned char pad[0x2acc];
    unsigned char value2acc;  // +2acc
    unsigned char value2acd;  // +2acd
    unsigned char pad2ace[0x16a];
};

class GameBoard {
public:
    unsigned char pad[0x2944];
    Player players[1];        // +2944
};

static inline unsigned int menu_mode() {
    return get_game()->state()->mode;
}

static inline GameBoard* game_board() {
    return reinterpret_cast<GameBoard*>(get_game());
}

static inline int stage_fade_message() {
    int message = 1;
    switch (menu_mode()) {
    case 3:
        message = 0x31;
        break;
    case 4: {
        GameBoard* game = game_board();
        unsigned char counter = game->players[menu_mode()].value2acc;
        game = game_board();
        if (game->players[menu_mode()].value2acd == 1)
            message = 0x32;
        else if (counter < 0x19)
            message = 0x34;
        else
            message = counter < 0x31 ? 0x33 : 0x32;
        break;
    }
    case 5:
        message = 0x5c;
        break;
    case 6:
        message = 0x3a;
        break;
    case 7:
        message = 0x3b;
        break;
    case 8:
        message = 0x61;
        break;
    case 9:
        message = 0x62;
        break;
    }
    return message;
}

void register_resource_callback(void* callback, void (*completion)(int, unsigned int),
                                unsigned int flags);                        // 0x7100258b0c
void remove_resource_callback(void* callback);                              // 0x710025917c
unsigned char resource_queue_has_callback(void* callback);                  // 0x7100259680
unsigned char resource_queue_callback_in_state(void* callback, unsigned int state); // 0x71002597a8
struct SharedState;
SharedState* get_shared_state();                                            // 0x71002aae3c
void* shared_state_resources(SharedState* state);                           // 0x71002ad1dc
void dialog_open(void* resources, int a, int b);                            // 0x710038861c
void dialog_close(void* resources, int a);                                  // 0x710038862c
void play_demo_fade(int kind, int a, int b, void* target, float time);      // 0x71003f9b34

class TextCursor {
public:
    void reset(int a, int b, float time);                                   // 0x71001e526c
};
TextCursor* get_text_cursor();                                              // 0x71001e50b0
// Board resource request, reached through the GOT slot at 0x7100c2a7a8.
extern unsigned char gBoardRequest[];

unsigned char BoardScene::start() {
    if (!resource_queue_has_callback(gBoardRequest)) {
        register_resource_callback(gBoardRequest, nullptr, 0x20);
        if (void* resources = shared_state_resources(get_shared_state()))
            dialog_open(resources, 1, 1);
        return 0;
    }
    if (!resource_queue_callback_in_state(gBoardRequest, 3))
        return 0;
    remove_resource_callback(gBoardRequest);
    gBoardCursor->initialize();
    gDemoPanelSystem->initialize();
    gDemoEffectPool->initialize();
    gAdvBoard->initialize();
    gBoardUnits->initialize();
    gBoardPopups->initialize();
    gAdvCaption->initialize();
    gAdvEffects->initialize();
    gBoardCamera->initialize();
    switch (query->valued4) {
    case 0:
        gBoardCamera->set_mode(3, 6);
        break;
    case 1:
        gBoardCamera->set_mode(3, 1);
        break;
    case 2:
        gBoardCamera->set_mode(3, 2);
        break;
    case 3:
        gBoardCamera->set_mode(3, 0);
        break;
    }
    if (void* resources = shared_state_resources(get_shared_state()))
        dialog_close(resources, 1);
    if (get_text_cursor() && get_text_cursor())
        get_text_cursor()->reset(0, 1, 0.0f);
    gAdvCaption->set_value0c(0x2a);
    gBoardOverride.active = 1;
    gBoardOverride.phase = 1;
    gBoardCursor->value10 = 0;
    gBoardPopups->reset();
    gAdvBoard->reset_view();
    play_demo_fade(stage_fade_message(), 1, 0, nullptr, 0.668f);
    return 1;
}

// Layout element classes (constructors in the layout library).
struct LayoutRect {
    LayoutRect();                                                           // 0x71001f1cd8
    unsigned char pad[0x28];
};
struct LayoutBox {
    LayoutBox();                                                            // 0x71001f1e0c
    unsigned char pad[0x10];
};
struct LayoutSprite {
    LayoutSprite();                                                         // 0x71001ef52c
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void draw(void* target, Fader* fader); // +18

    int flags;                // +08: bit 7 dirty
    unsigned char padc[0x3c];
};
static_assert(sizeof(LayoutSprite) == 0x48, "layout sprite size");
struct LayoutFrame {
    LayoutFrame();                                                          // 0x71001f0140
    unsigned char pad0[8];
    int flags;                // +08: bit 7 dirty
    unsigned char padc[0x7c];
};
static_assert(sizeof(LayoutFrame) == 0x88, "layout frame size");

// Header of the board view (fields +08 to +28), initialised before the vtable pointer.
struct BoardViewBase {
    BoardViewBase(int value, void* owner)
        : value8(value), valuec(value), owner(owner), value18(0), value20(0) {}

    int value8;               // +000008
    int valuec;               // +00000c
    void* owner;              // +000010
    long value18;             // +000018
    long value20;             // +000020
};

// Board view (0x1a8068 bytes): one sprite per board unit slot.
class BoardView : public BoardViewBase {
public:
    BoardView(int value, void* owner);                                      // 0x7100274530
    virtual ~BoardView();
    virtual void init(int value, void* owner);                              // 0x7100274624

    LayoutRect rect;          // +000028
    LayoutBox box;            // +000050
    int value60;              // +000060
    int value64;              // +000064
    int value68;              // +000068
    unsigned char value6c;    // +00006c
    unsigned char pad6d[3];
    int value70;              // +000070
    unsigned short value74;   // +000074
    unsigned char pad76[2];
    LayoutSprite cursor;      // +000078
    LayoutFrame frame_c0;     // +0000c0
    LayoutFrame frame_148;    // +000148
    LayoutSprite grid[0x80][0xb0]; // +0001d0
    LayoutSprite extra[9][0xb0];   // +18c1d0
    LayoutFrame frame_1a7f50; // +1a7f50
    LayoutFrame frame_1a7fd8; // +1a7fd8
    int value1a8060;          // +1a8060
    unsigned char value1a8064; // +1a8064
    unsigned char pad1a8065[3];
};
static_assert(sizeof(BoardView) == 0x1a8068, "board view size");

BoardView::BoardView(int value, void* owner) : BoardViewBase(value, owner) {
    init(value, owner);
}

void BoardView::init(int value, void* owner) {
    value8 = value;
    valuec = value;
    value18 = 0;
    value20 = 0;
    cursor.flags |= 0x80;
    this->owner = owner;
    frame_c0.flags |= 0x80;
    frame_148.flags |= 0x80;
    for (int row = 0; row < 0x80; ++row) {
        for (int i = 0; i < 0xb0; ++i)
            grid[row][i].flags |= 0x80;
    }
    for (int set = 0; set < 9; ++set) {
        for (int i = 0; i < 0xb0; ++i)
            extra[set][i].flags |= 0x80;
    }
    value60 = 1;
    if (menu_mode() == 1)
        value60 = 0;
    value70 = -1;
    value64 = 1;
    value68 = 0;
    value6c = 0;
    value74 = 0;
    value1a8060 = 0;
    value1a8064 = 0;
}

struct SharedObject {
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void destroy();   // +18

    int refs;                 // +08
};

static inline void release_shared(SharedObject*& slot) {
    if (SharedObject* object = slot) {
        if (!--object->refs)
            object->destroy();
        slot = nullptr;
    }
}

unsigned char resource_queue_active();                                      // 0x71002589b4
bool finish_resource_queue(unsigned char wait, unsigned char unused, unsigned char skip_exit_check); // 0x7100258a68
void stop_menu_sounds();                                                    // 0x71003feea4
void destroy_adv_effects();                                                 // 0x710026767c
void destroy_adv_caption();                                                 // 0x7100266b98
void destroy_board_popups();                                                // 0x71002a7354
void destroy_board_units();                                                 // 0x7100291d64
void destroy_adv_board();                                                   // 0x710029b5a4
void destroy_demo_panel_system();                                           // 0x7100263cfc
void destroy_demo_effect_pool();                                            // 0x7100260bac
void destroy_board_cursor();                                                // 0x7100288e7c
void destroy_board_camera();                                                // 0x7100288a0c
void release_menu_board();                                                  // 0x7100283f78
void release_menu_units();                                                  // 0x7100283e10
void task_release(void* task, int flags, int a);                            // 0x7100387784

void MenuScene::shutdown() {
    if (resource_queue_active())
        finish_resource_queue(1, 0, 1);
    stop_menu_sounds();
    for (int i = 0; i < 8; ++i) {
        if (views[i]) {
            delete views[i];
            views[i] = nullptr;
        }
    }
    gAdvEffects->finalize();
    destroy_adv_effects();
    gAdvCaption->finalize();
    destroy_adv_caption();
    gBoardPopups->finalize();
    destroy_board_popups();
    gBoardUnits->finalize();
    destroy_board_units();
    gAdvBoard->finalize();
    destroy_adv_board();
    gDemoPanelSystem->finalize();
    destroy_demo_panel_system();
    gDemoEffectPool->finalize();
    destroy_demo_effect_pool();
    gBoardCursor->finalize();
    destroy_board_cursor();
    gBoardCamera->finalize();
    destroy_board_camera();
    gBoardOverride.reset();
    gTitleBanner->hide();
    release_menu_board();
    release_menu_units();
    gMenuFrame.close();
    task_release(this, 0x40, 0);
    gFader->release(fade2d480, nullptr);
    release_shared(object2d470);
    release_shared(object2d478);
}

// Header of the board overlay (fields +08 to +2c), initialised before the vtable pointer.
struct BoardOverlayBase {
    BoardOverlayBase(int value, void* owner)
        : value8(value), valuec(value), owner(owner), value18(0), value20(0), value28(0) {}

    int value8;               // +08
    int valuec;               // +0c
    void* owner;              // +10
    long value18;             // +18
    long value20;             // +20
    int value28;              // +28
    unsigned char pad2c[4];
};

// Board overlay (0x37b30 bytes): two 9x176 sprite layers.
class BoardOverlay : public BoardOverlayBase {
public:
    BoardOverlay(int value, void* owner);                                   // 0x7100280f6c
    void draw();                                                            // 0x710028228c
    void update();                                                          // 0x7100282484
    unsigned char confirm_ready();                                          // 0x71002826b0
    virtual ~BoardOverlay();

    LayoutSprite lower[9][0xb0]; // +00030
    LayoutSprite upper[9][0xb0]; // +1bdb0
};
static_assert(sizeof(BoardOverlay) == 0x37b30, "board overlay size");

BoardOverlay::BoardOverlay(int value, void* owner) : BoardOverlayBase(value, owner) {
    for (int set = 0; set < 9; ++set) {
        for (int i = 0; i < 0xb0; ++i) {
            lower[set][i].flags |= 0x80;
            upper[set][i].flags |= 0x80;
        }
    }
}

class CellRecord {
public:
    unsigned char cleared();                                                // 0x7100202164

    int unit;                 // +00
    unsigned char pad4[0x38];
};

struct MarkedPlayer {
    int id;                   // +0000
    unsigned char pad4[0x200];
    int marks[0x80][2];       // +0204
    unsigned char pad604[0x564];
    CellRecord records[0x80]; // +0b68
    unsigned char pad2968[0x2d0];
};
static_assert(sizeof(MarkedPlayer) == 0x2c38, "marked player size");

unsigned char begin_sprite_batch();                                         // 0x71001e4500
void end_sprite_batch();                                                    // 0x71001e4560

// Board layer view: two 9x176 sprite layers after a 0xe8-byte header.
class BoardLayerView {
public:
    void draw();                                                            // 0x7100280200

    unsigned char pad[0xe8];
    LayoutSprite lower[9][0xb0]; // +000e8
    LayoutSprite upper[9][0xb0]; // +1be68
};

void BoardLayerView::draw() {
    void* target = gRenderTarget;
    unsigned int mode = menu_mode();
    GameBoard* game = game_board();
    bool front = false;
    if (mode == 4) {
        MarkedPlayer* players = reinterpret_cast<MarkedPlayer*>(game->players);
        MarkedPlayer& player = players[menu_mode()];
        front = (player.marks[player.id][0] & 0x18) != 0;
    } else if (reinterpret_cast<Game*>(game)->state()->mode == 5 || menu_mode() == 6 || menu_mode() == 8) {
        front = gAdvEffects->value494 == 9;
    }
    if (begin_sprite_batch()) {
        for (int set = 0; set < 9; ++set) {
            for (int i = 0; i < 0xb0; ++i) {
                lower[set][i].draw(target, gFader);
                upper[set][i].draw(target, gFader);
            }
        }
        end_sprite_batch();
    }
    if (front) {
        gBoardUnits->draw();
        gAdvEffects->draw_screens();
    } else {
        gAdvEffects->draw_screens();
        gBoardUnits->draw();
    }
    gBoardCursor->draw();
    gAdvCaption->draw();
    gAdvEffects->draw_start();
}

void BoardOverlay::draw() {
    void* target = gRenderTarget;
    bool front = false;
    if (menu_mode() == 5 || menu_mode() == 6 || menu_mode() == 8)
        front = gAdvEffects->value494 == 9;
    if (begin_sprite_batch()) {
        for (int set = 0; set < 9; ++set) {
            for (int i = 0; i < 0xb0; ++i) {
                lower[set][i].draw(target, gFader);
                upper[set][i].draw(target, gFader);
            }
        }
        end_sprite_batch();
    }
    if (front) {
        gDemoEffectPool->draw();
        gAdvEffects->draw_screens();
    } else {
        gAdvEffects->draw_screens();
        gDemoEffectPool->draw();
    }
    gDemoPanelSystem->draw();
    gBoardPopups->draw();
    gBoardCursor->draw();
    gAdvCaption->draw();
    gAdvEffects->draw_start();
}

class Pad {
public:
    unsigned int buttons(int port);                                         // 0x710045d620
};
Pad* get_pad();                                                             // 0x710045ceb4
void play_se(int id, int a, void* target, int volume, float scale, float x, float y); // 0x71003fbe44
unsigned char resource_queue_active();                                      // 0x71002589b4

struct OverlayOwner {
    unsigned char pad[0x18];
    int unit;                 // +18
};

static inline short board_unit(void* database, int cell) {
    return *reinterpret_cast<short*>(static_cast<unsigned char*>(database) + 0xdb608 + cell * 0x1e0);
}

void BoardOverlay::update() {
    GameBoard* game = game_board();
    unsigned int mode = menu_mode();
    void* database = get_unit_database();
    if (value28 != 5)
        return;
    MarkedPlayer& player = reinterpret_cast<MarkedPlayer*>(game->players)[mode];
    long cell = player.id;
    int sealed = menu_mode() == 7 ? (player.marks[cell][0] >> 13) & 1 : 0;
    if ((get_pad()->buttons(0) & 0x2000) || gBoardCamera->pressed(0)) {
        gBoardCamera->release(0);
        if (!confirm_ready())
            return;
        if (static_cast<unsigned char>(resource_queue_active() | sealed))
            return;
        if (!gDemoEffectPool->restart())
            return;
        play_se(0x2f, 0, nullptr, 0x3c, 1.0f, 0.0f, 0.0f);
        value28 = 7;
        CellRecord record = player.records[cell];
        OverlayOwner* target = static_cast<OverlayOwner*>(owner);
        target->unit = record.cleared() ? record.unit : board_unit(database, player.id);
        return;
    }
    if ((get_pad()->buttons(0) & 0x4000) || gBoardCamera->pressed(1)) {
        play_se(5, 0, nullptr, 0x3c, 1.0f, 0.0f, 0.0f);
        gBoardCamera->release(1);
        gAdvEffects->play_exit(0);
        value28 = 2;
    }
}
