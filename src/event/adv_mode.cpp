// Matching candidates for the Adventure Mode state machine 0x710026e434-0x710026ed7c.
// AdvModeTask::run (0x710026e4a8) is at the end.
// Names are descriptive placeholders. Status: matching/README.md.

#include "event/board_query.h"

inline void* operator new(unsigned long, void* where) noexcept { return where; }

class DefaultHeap {
public:
    void* allocate(unsigned int alignment, unsigned long size, int a, int b); // 0x710045c458
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

void play_demo_fade(int kind, int a, int b, void* target, float time);      // 0x71003f9b34

class GameState {
public:
    int base_level(int kind);                                               // 0x7100203550

    unsigned char pad[0x1bb7c];
    unsigned int mode;        // +1bb7c
};

struct Player {
    unsigned char pad[0x2acc];
    unsigned char value2acc;  // +2acc
    unsigned char value2acd;  // +2acd
    unsigned char pad2ace[0x16a];
};
static_assert(sizeof(Player) == 0x2c38, "player size");

class Game {
public:
    GameState* state();                                                     // 0x7100204c10

    unsigned char pad[0x2944];
    Player players[1];        // +2944
};
Game* get_game();                                                           // 0x7100204728

static inline unsigned int game_mode() {
    return get_game()->state()->mode;
}

// Scene task base classes (constructors 0x710039cc78 and 0x7100387524).
class Task {
public:
    Task();                                                                 // 0x710039cc78
    virtual ~Task();
    virtual void run();
};

class SceneTask {
public:
    SceneTask();                                                            // 0x7100387524
    virtual ~SceneTask();
};

class SharedState {
public:
    int run_task(SceneTask* task);                                          // 0x71002ad584
};
SharedState* get_shared_state();                                            // 0x71002aae3c
unsigned char shared_state_exiting(SharedState* state);                     // 0x71002ac7f0

class AdvModeTask : public Task {
public:
    AdvModeTask();                                                          // 0x710026e434
    void run();                                                             // 0x710026e4a8

    int result;               // +08
};

void BoardQuery::reset() {
    state = 4;
    valuecc = 100;
    value13 = 0;
    value14 = 0;
    valuec5 = 0;
    value10 = 0;
    value11 = 0;
    step = 0;
    previous_step = 0;
    value22 = 0;
    value20 = 0;
    value21 = 0;
    value18 = 0;
    valued0 = 0;
    timer_done = 0;
    seal_done = 0;
    turn_alert = 0;
    valueb9f5 = 0;
    quest_short = 0;
    quest_long = 0;
    sealed_high = 0;
    sealed_low = 0;
    reset_pending = -1;
    valueb9f0 = 0;
    valueb9d8 = -1;
    valueb9dc = -1;
    valueb9e0 = 0;
    valueb9e1 = 0;
    valued4 = 0;
    access = 0;
    for (int i = 0; i < 4; ++i) {
        base_levels[i] = get_game()->state()->base_level(i);
        levels34[i] = -1;
    }
    for (int i = 0; i < 0x80; ++i) {
        cell_flags[i] = 0;
        cell_values[i] = -1;
        groups[i] = 0;
        cell_marks[i] = 0;
        for (int k = 0; k < 0x1c; ++k) {
            levels[i][k] = -1;
            kinds[i][k] = 3;
            flags[i][k] = 0;
            items[i][k] = -1;
        }
    }
    active = 1;
    valueb9f6 = 0;
    valueb9f7 = 0;
    valueb9fc = -1;
    valueb9f8 = 0;
    valueb9f9 = 0;
    valueba00 = 0;
}

AdvModeTask::AdvModeTask() {}

class OptionTask : public SceneTask {
public:
    OptionTask() { closing = 0; }

    unsigned char pad8[0x2d419];
    unsigned char closing;    // +2d421
    unsigned char pad2d422[0xe];
};
static_assert(sizeof(OptionTask) == 0x2d430, "option task size");

class OptionSource {
public:
    int pending();                                                          // 0x710020c1fc
    int locked();                                                           // 0x710020c204
};
OptionSource* get_option_source();                                          // 0x710020bd74
// Reached through the GOT slot at 0x7100c2a728.
extern int gOptionState;

void run_options() {
    gOptionState = 0;
    if (get_option_source()->pending())
        return;
    gOptionState = 1;
    void* storage = get_default_heap()->allocate(0x10, sizeof(OptionTask), 1, 0);
    OptionTask* task = new (storage) OptionTask;
    get_shared_state()->run_task(task);
    delete task;
}

class SaveTask : public SceneTask {
public:
    SaveTask();                                                             // 0x71002877f4

    unsigned char pad8[0x2d428];
    BoardQuery* query;        // +2d430
    unsigned char pad2d438[8];
};
static_assert(sizeof(SaveTask) == 0x2d440, "save task size");

void run_save() {
    play_demo_fade(1, 1, 0, nullptr, 0.668f);
    void* storage = get_default_heap()->allocate(0x10, sizeof(SaveTask), 1, 0);
    SaveTask* task = new (storage) SaveTask;
    task->query = &gBoardQuery;
    int result = get_shared_state()->run_task(task);
    delete task;
    BoardQuery& query = gBoardQuery;
    query.previous_step = query.step;
    if (result == 1) {
        query.step = 2;
    } else {
        query.step = 12;
        query.state = 2;
    }
}

void set_menu_layer(int layer);                                             // 0x71003fa4c8
void set_menu_cursor(int cursor);                                           // 0x71003fa724

class BoardMenuTask : public SceneTask {
public:
    BoardMenuTask() {}

    unsigned char pad8[0x2d498];
};
static_assert(sizeof(BoardMenuTask) == 0x2d4a0, "board menu task size");
// Reached through the GOT slot at 0x7100c2a740.
extern BoardQuery* gMenuQuery;

void run_board_menu() {
    set_menu_layer(0);
    set_menu_cursor(0);
    int message;
    switch (game_mode()) {
    case 3:
        message = 0x31;
        break;
    default:
        message = 1;
        break;
    case 4: {
        Game* game = get_game();
        unsigned char counter = game->players[game_mode()].value2acc;
        game = get_game();
        if (game->players[game_mode()].value2acd == 1)
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
    play_demo_fade(message, 1, 0, nullptr, 0.668f);
    void* work = get_default_heap()->allocate(0x20, 0x300000, 1, 0);
    void* storage = get_default_heap()->allocate(0x10, sizeof(BoardMenuTask), 1, 0);
    BoardMenuTask* task = new (storage) BoardMenuTask;
    gMenuQuery = &gBoardQuery;
    int result = get_shared_state()->run_task(task);
    delete task;
    get_default_heap()->release(work, 1, 0);
    BoardQuery& query = gBoardQuery;
    if (result == 2) {
        query.previous_step = query.step;
        query.step = 1;
    } else if (result == 1) {
        if (query.value11) {
            query.previous_step = query.step;
            query.step = 4;
        } else {
            query.previous_step = query.step;
            query.step = query.value12 ? 5 : 3;
        }
    } else {
        query.state = 2;
    }
}

void set_fade_frames(int frames);                                           // 0x71003f9fac
void show_system_message(int id, int a, int b, int c, int d);               // 0x71003c9668
void close_overlays(int layer, int a, int b);                               // 0x71003ade70
void load_board(unsigned int stage);                                        // 0x710026c154
void run_board_event();                                                     // 0x710026ed80
void run_board_battle();                                                    // 0x710026ef60
void run_board_result();                                                    // 0x710026f05c
void run_board_shop();                                                      // 0x710026f214
void run_board_ending();                                                    // 0x710026fdf8

struct BoardRow;
class UnitDatabase {
public:
    unsigned char pad[0xdb608];
    unsigned char rows[1];    // +db608
};
UnitDatabase* get_unit_database();                                          // 0x710020ec80

class SaveSlots {
public:
    void select();                                                          // 0x7100217508
};
unsigned char* get_save_header();                                           // 0x7100217518

class StageLights {
public:
    void reset(int a, int b);                                               // 0x71001fb808
};
// Reached through the GOT slot at 0x7100c21df8.
extern StageLights* gStageLights;
// Reached through the GOT slots at 0x7100c2a708, 0x7100c2a710 and 0x7100c2a720.
extern int gTitleLock;
extern int gTitleCursor;
extern unsigned char gEndingSeen;

class TitleTask : public SceneTask {
public:
    TitleTask() { closing = 0; }

    unsigned char pad8[0x2d419];
    unsigned char closing;    // +2d421
    unsigned char pad2d422[0xe];
};

void player_setup(void* player, void* rows, int stage);                    // 0x710026a98c
unsigned char game_has_flag(Game* game, int flag);                          // 0x71002026fc
void game_set_flag(Game* game, int flag, unsigned char on);                 // 0x7100202730

void AdvModeTask::run() {
    set_fade_frames(200);
    play_demo_fade(1, 1, 0, nullptr, 0.668f);
    gTitleLock = 0;
    if (!get_option_source()->locked())
        gTitleLock = 2;
    gTitleCursor = 0;
    result = 4;
    BoardQuery* query = &gBoardQuery;
    query->reset();
    if (static_cast<unsigned int>(query->base_levels[0]) >= 100)
        query->base_levels[0] = 0;
    reinterpret_cast<SaveSlots*>(get_save_header() + 4)->select();
    for (int stage = 0; stage < 10; ++stage) {
        get_game()->state()->mode = stage;
        load_board(game_mode());
        Game* game = get_game();
        player_setup(&game->players[game_mode()], get_unit_database()->rows, stage);
    }
    get_game()->state()->mode = 0;
    load_board(game_mode());
    if (!game_has_flag(get_game(), 0x16)) {
        show_system_message(10, 1, 0, 1, 0);
        game_set_flag(get_game(), 0x16, 1);
    }
    int phase = 0;
    for (;;) {
        switch (phase & 3) {
        case 0: {
            void* storage = get_default_heap()->allocate(0x10, sizeof(TitleTask), 1, 0);
            phase = 1;
            TitleTask* task = new (storage) TitleTask;
            get_shared_state()->run_task(task);
            delete task;
            phase = 1;
            continue;
        }
        case 1:
            run_options();
            phase = 2;
            continue;
        case 2: {
            phase = 3;
            if (query->state != 4)
                continue;
            int step = query->step;
            if (query->valueb9f8) {
                query->step = 3;
                query->previous_step = step;
                run_board_event();
                phase = 2;
                continue;
            }
            switch (step) {
            case 0:
                query->step = 1;
                query->previous_step = 0;
                break;
            case 1:
                run_save();
                break;
            case 2:
                run_board_menu();
                break;
            case 3:
                run_board_event();
                break;
            case 4:
                run_board_battle();
                break;
            case 5:
                run_board_result();
                break;
            case 6:
            case 7:
                run_board_shop();
                break;
            case 8:
            case 9:
            case 10:
                run_board_ending();
                break;
            default:
                set_fade_frames(200);
                phase = 3;
                continue;
            }
            phase = 2;
            continue;
        }
        }
        break;
    }
    gStageLights->reset(0, 0);
    close_overlays(3, 0, 0);
    if (query->state == 1 && query->step == 12)
        gEndingSeen = 0;
    result = shared_state_exiting(get_shared_state()) ? -1 : query->state;
}
