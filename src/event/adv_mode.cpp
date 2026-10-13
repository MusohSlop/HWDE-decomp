// Matching candidates for the Adventure Mode state machine 0x710026e434-0x710026ed7c.
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
    unsigned char cleared(int player);                                      // 0x7100203278
    void set_cleared(int player, unsigned char on);                         // 0x71002032ac
    unsigned char record_shown(int record);                                 // 0x71002032f4
    void set_record_shown(int record, unsigned char on);                    // 0x7100203330

    unsigned char pad[0x1bb7c];
    unsigned int mode;        // +1bb7c
};

struct Player {
    int id;                   // +0000
    unsigned char pad4[0x664];
    unsigned char no_fort[0x80]; // +0668
    unsigned char pad6e8[0x23e4];
    unsigned char value2acc;  // +2acc
    unsigned char value2acd;  // +2acd
    unsigned char pad2ace[0x16a];
};
static_assert(sizeof(Player) == 0x2c38, "player size");

class Game {
public:
    GameState* state();                                                     // 0x7100204c10
    unsigned short stock(int item);                                         // 0x7100203b10
    void add_stock(int item, int count);                                    // 0x7100203b2c
    void mark_stock(int item, unsigned char on);                            // 0x7100203b88
    unsigned char has_progress(int kind);                                   // 0x7100204174
    unsigned char clear_count();                                            // 0x710020422c

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

    unsigned char pad0[4];
    int language;             // +004
    unsigned char pad8[0x208];
    int screen;               // +210
};
SharedState* get_shared_state();                                            // 0x71002aae3c
unsigned char shared_state_exiting(SharedState* state);                     // 0x71002ac7f0

class AdvModeTask : public Task {
public:
    AdvModeTask();                                                          // 0x710026e434
    void run();                                                             // 0x710026e4a8

    int result;               // +08
};

class OptionSource {
public:
    int pending();                                                          // 0x710020c1fc
    int locked();                                                           // 0x710020c204
};
OptionSource* get_option_source();                                          // 0x710020bd74
// Reached through the GOT slot at 0x7100c2a728.
extern int gOptionState;
void run_options();
void run_save();
void run_board_menu();
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

AdvModeTask::AdvModeTask() {}

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
            if (step > 10) {
                set_fade_frames(200);
                phase = 3;
                continue;
            }
            if (step <= 5) {
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
                }
            } else if ((step & ~1) == 6) {
                run_board_shop();
            } else if (static_cast<unsigned int>(step - 8) <= 2) {
                run_board_ending();
            } else {
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

class OptionTask : public SceneTask {
public:
    OptionTask() { closing = 0; }

    unsigned char pad8[0x2d419];
    unsigned char closing;    // +2d421
    unsigned char pad2d422[0xe];
};
static_assert(sizeof(OptionTask) == 0x2d430, "option task size");


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

static inline int stage_fade_message() {
    int message = 1;
    switch (game_mode()) {
    case 3:
        message = 0x31;
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
    return message;
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
    play_demo_fade(stage_fade_message(), 1, 0, nullptr, 0.668f);
    void* work = get_default_heap()->allocate(0x20, 0x300000, 1, 0);
    void* storage = get_default_heap()->allocate(0x10, sizeof(BoardMenuTask), 1, 0);
    BoardMenuTask* task = new (storage) BoardMenuTask;
    gMenuQuery = &gBoardQuery;
    int result = get_shared_state()->run_task(task);
    delete task;
    get_default_heap()->release(work, 1, 0);
    BoardQuery& query = gBoardQuery;
    switch (result) {
    case 2:
        query.previous_step = query.step;
        query.step = 1;
        break;
    case 1:
        if (query.value11) {
            query.previous_step = query.step;
            query.step = 4;
        } else {
            query.previous_step = query.step;
            query.step = query.value12 ? 5 : 3;
        }
        break;
    default:
        query.state = 2;
        break;
    }
}

class EventTask : public SceneTask {
public:
    EventTask();                                                            // 0x7100283fd0

    unsigned char pad8[0x2d428];
    BoardQuery* query;        // +2d430
    unsigned char pad2d438[0x18];
};
static_assert(sizeof(EventTask) == 0x2d450, "event task size");

void run_board_event() {
    set_menu_layer(0);
    BoardQuery& query = gBoardQuery;
    if (query.previous_step != 4)
        play_demo_fade(stage_fade_message(), 1, 0, nullptr, 0.668f);
    void* storage = get_default_heap()->allocate(0x10, sizeof(EventTask), 1, 0);
    EventTask* task = new (storage) EventTask;
    task->query = &query;
    int result = get_shared_state()->run_task(task);
    delete task;
    switch (result) {
    case 2:
        query.previous_step = query.step;
        query.step = query.value11 && query.value13 ? 4 : 2;
        break;
    case 1:
        query.previous_step = query.step;
        query.step = 7;
        break;
    default:
        query.state = 2;
        break;
    }
}

class BattleTask : public SceneTask {
public:
    BattleTask();                                                           // 0x71002d8e2c
    void prepare();                                                         // 0x71002d8eec
    void finish();                                                          // 0x71002d901c

    unsigned char pad8[0x2d438];
};
static_assert(sizeof(BattleTask) == 0x2d440, "battle task size");

void run_board_battle() {
    set_menu_layer(0);
    play_demo_fade(0x5e, 1, 0, nullptr, 0.668f);
    void* storage = get_default_heap()->allocate(0x10, sizeof(BattleTask), 1, 0);
    BattleTask* task = new (storage) BattleTask;
    task->prepare();
    int result = get_shared_state()->run_task(task);
    task->finish();
    delete task;
    set_fade_frames(0);
    close_overlays(4, 0, 0);
    BoardQuery& query = gBoardQuery;
    query.value11 = 0;
    if (static_cast<unsigned int>(result - 1) <= 1) {
        if (query.value13) {
            query.value13 = 0;
            query.previous_step = query.step;
            query.step = 3;
        } else {
            query.previous_step = query.step;
            query.step = 2;
        }
    } else {
        query.state = 2;
    }
}

class ResultTask : public SceneTask {
public:
    ResultTask();                                                           // 0x71002906dc
    void prepare();                                                         // 0x7100290778
    void finish();                                                          // 0x71002907e4

    unsigned char pad8[0x2d438];
};
static_assert(sizeof(ResultTask) == 0x2d440, "result task size");

void run_board_result() {
    set_menu_layer(0);
    play_demo_fade(stage_fade_message(), 1, 0, nullptr, 0.668f);
    void* storage = get_default_heap()->allocate(0x10, sizeof(ResultTask), 1, 0);
    ResultTask* task = new (storage) ResultTask;
    task->prepare();
    int result = get_shared_state()->run_task(task);
    task->finish();
    delete task;
    close_overlays(4, 0, 0);
    BoardQuery& query = gBoardQuery;
    query.value12 = 0;
    if (static_cast<unsigned int>(result - 1) <= 1) {
        query.previous_step = query.step;
        query.step = 2;
    } else {
        query.state = 2;
    }
}

struct BoardRow {
    unsigned char pad[0x12];
    unsigned char kind;       // +12
    unsigned char pad13[0x1cd];
};
unsigned char dlc_unit_unlocked(BoardRow* unit);                            // 0x710026a7e0

static inline BoardRow* board_row(int cell) {
    return &reinterpret_cast<BoardRow*>(get_unit_database()->rows)[cell];
}

static inline int final_player() {
    return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(get_game()) + 0x1e374);
}

static inline bool on_final_cell() {
    if (get_shared_state()->screen != 4)
        return false;
    int player = final_player();
    if (player == 1)
        return false;
    int cell = get_game()->players[player].id;
    unsigned char kind = board_row(cell)->kind;
    return kind == 0x10 || kind == 2;
}

class BattleParams {
public:
    unsigned char pad[0x6c];
    int result;               // +6c
    unsigned char pad70[0x28];
    int reward;               // +98
    int bonus;                // +9c
};
BattleParams* get_battle_params();                                          // 0x71001a8c38

class ItemTable {
public:
    unsigned char is_special(unsigned int item);                            // 0x71001ff2a4
    int material_of(int item);                                              // 0x71001ff1a8
};
ItemTable* get_item_table();                                                // 0x71001ff050

class MaterialBook {
public:
    void* entry(int material);                                              // 0x71002015a8
};
MaterialBook* get_material_book();                                          // 0x7100200fc0
unsigned char material_known(void* flags);                                  // 0x71001ff9e8

class Inventory {
public:
    int slot(int material, int a);                                          // 0x71001fe724
    int count(int material, int a);                                         // 0x71001fe75c
};
class InventorySet {
public:
    Inventory* get(int kind);                                               // 0x71001feadc
};
InventorySet* get_inventories();                                            // 0x71001fe7c8

class EndingTask : public SceneTask {
public:
    EndingTask(int mode);                                                   // 0x71002cb32c
    void prepare();                                                         // 0x71002cb48c
    void finish();                                                          // 0x71002cb490

    unsigned char pad8[0x2d428];
};
static_assert(sizeof(EndingTask) == 0x2d430, "ending task size");
void task_release(SceneTask* task, int flags, int a);                       // 0x7100387784

void board_finish_turn(BoardQuery* query);                                  // 0x7100271aac
const char* message_text(int id);                                           // 0x7100217d64
void format_text(char* dest, const char* format, ...);                      // 0x710045a77c
void show_notice(char* text);                                               // 0x71003afd3c
void set_notice_mode(int mode, int a);                                      // 0x710039ccd4
extern "C" char* strcat(char* dest, const char* src);
extern const char kNumberFormat[] __attribute__((visibility("hidden")));    // 0x7100740bae

class RecordBook {
public:
    void* record(int index);                                                // 0x7100210870
};
RecordBook* get_record_book();                                              // 0x710021069c
int record_mode(void* record);                                              // 0x7100210654
int record_cell(void* record);                                              // 0x710021065c
int record_text(void* record);                                              // 0x7100210634

class Achievements {
public:
    void refresh();                                                         // 0x71002079d0
};
Achievements* get_achievements();                                           // 0x7100207648

void run_board_ending() {
    get_unit_database();
    Game* game = get_game();
    unsigned int mode = game_mode();
    Player* player = &game->players[mode];
    bool final = false;
    if (on_final_cell()) {
        show_system_message(0x31, 1, 0, 1, 0);
        final = true;
    }
    int reward = -1;
    if (get_battle_params()->result == 3 && player->no_fort[player->id])
        reward = get_battle_params()->reward;
    if (get_battle_params()->bonus >= 0 && get_battle_params()->bonus <= 0x2e3 && player->no_fort[player->id])
        reward = get_battle_params()->bonus;
    if (get_item_table()->is_special(reward)) {
        unsigned int material = get_item_table()->material_of(reward);
        if (material <= 0x63 &&
            !material_known(static_cast<unsigned char*>(get_material_book()->entry(material)) + 0x28)) {
            int slot = get_inventories()->get(0x21)->slot(material, 0);
            int count = get_inventories()->get(0x21)->count(material, 0);
            if (count > get_game()->stock(slot)) {
                Game* current = get_game();
                current->add_stock(slot, count - get_game()->stock(slot));
                get_game()->mark_stock(slot, 1);
            }
        }
    }
    void* storage = get_default_heap()->allocate(0x10, sizeof(EndingTask), 1, 0);
    EndingTask* task = new (storage) EndingTask(0);
    task->prepare();
    int result = get_shared_state()->run_task(task);
    task->finish();
    task_release(task, 0x80, 0);
    delete task;
    int cell = player->id;
    BoardRow* row = board_row(cell);
    if (row->kind >= 0x17 && row->kind <= 0x1a)
        dlc_unit_unlocked(row);
    BoardQuery* query = &gBoardQuery;
    board_finish_turn(query);
    char text[0x200];
    char number[0x40];
    if (on_final_cell()) {
        int winner = final_player();
        if (!get_game()->state()->cleared(winner) && get_game()->has_progress(1)) {
            if (get_shared_state()->language) {
                format_text(number, kNumberFormat, get_game()->clear_count());
            } else {
                unsigned char clears = get_game()->clear_count();
                if (clears >= 10) {
                    int ones = clears % 10 + 0xab;
                    format_text(number, message_text(clears / 10 + 0xab));
                    strcat(number, message_text(ones));
                } else {
                    format_text(number, message_text(clears + 0xab));
                }
            }
            format_text(text, message_text(0x255), number);
            show_notice(text);
        }
    }
    set_notice_mode(1, 0);
    for (int i = 0; i < 0x100; ++i) {
        if (!get_record_book()->record(i))
            continue;
        if (get_game()->state()->record_shown(i))
            continue;
        if (game_mode() != record_mode(get_record_book()->record(i)))
            continue;
        if (player->id != record_cell(get_record_book()->record(i)))
            continue;
        int id = record_text(get_record_book()->record(i)) + 0x2c6;
        const char* format = message_text(0x1e1);
        format_text(text, format, message_text(id));
        show_notice(text);
        get_game()->state()->set_record_shown(i, 1);
    }
    if (on_final_cell()) {
        int winner = final_player();
        if (!get_game()->state()->cleared(winner)) {
            get_game()->state()->set_cleared(winner, 1);
            get_achievements()->refresh();
        }
    }
    close_overlays(3, 0, 0);
    if (final) {
        query->previous_step = query->step;
        query->step = 12;
        query->state = 1;
    } else {
        query->previous_step = query->step;
        if (result == 1) {
            query->step = 2;
        } else {
            query->step = 12;
            query->state = 2;
        }
    }
}
