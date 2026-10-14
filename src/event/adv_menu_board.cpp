// Matching candidates for the Adventure Mode menu board helpers 0x7100282d74-0x710028404c.

#include "event/board_query.h"
// Names are descriptive placeholders. Status: matching/README.md.

class DefaultHeap {
public:
    void* allocate(unsigned int alignment, unsigned long size, int a, int b); // 0x710045c458
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

class GameState {
public:
    unsigned char pad[0x1bb7c];
    unsigned int mode;        // +1bb7c
};

struct Player {
    int id;                   // +0000
    unsigned char pad4[0x6e4];
    unsigned char visited[0x80]; // +06e8
    unsigned char pad768[0x100];
    unsigned char short_route[0x80]; // +0868
    unsigned char pad8e8[0x2080];
    unsigned char seen[8];    // +2968
    unsigned char pad2970[0x2c8];
};
static_assert(sizeof(Player) == 0x2c38, "player size");

class Game {
public:
    GameState* state();                                                     // 0x7100204c10
    unsigned char clear_count();                                            // 0x710020422c
    void* trophy(unsigned int index);                                       // 0x71002042bc
    unsigned char has_item(int item);                                       // 0x7100203fac
    unsigned char unlocked(int id);                                         // 0x7100204518
    unsigned char class_unlocked(int slot);                                 // 0x7100202e74

    unsigned char pad[0x2944];
    Player players[1];        // +2944
};
Game* get_game();                                                           // 0x7100204728

struct BoardRow {
    short value0;             // +00
    short value2;             // +02
    unsigned char pad4[0x1a];
    short value1e;            // +1e
    unsigned char pad20[8];
    short value28;            // +28
    short value2a;            // +2a
    short value2c;            // +2c
    unsigned char pad2e[0x1b2];
};

class UnitDatabase {
public:
    unsigned char pad[0xdb608];
    BoardRow rows[1];         // +db608
};
UnitDatabase* get_unit_database();                                          // 0x710020ec80

class LevelTable {
public:
    int level_of(int item);                                                 // 0x71001ff218
};
LevelTable* get_level_table();                                              // 0x71001ff050

unsigned char cell_exists(int cell, int a, int* skipped) {
    UnitDatabase* database = get_unit_database();
    Game* game = get_game();
    unsigned int mode = get_game()->state()->mode;
    long seen = database->rows[cell].value1e;
    unsigned int pair = database->rows[cell].value2;
    UnitDatabase* units = get_unit_database();
    if (game->players[mode].id == cell)
        return 0;
    if (game->players[mode].visited[cell]) {
        if (skipped)
            ++*skipped;
        return 0;
    }
    int level = get_level_table()->level_of(
        reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(units) + 0xebd7c)[pair * 4]);
    if (static_cast<unsigned int>(level) > 0x63)
        return 0;
    return game->players[mode].seen[seen] != 0;
}

struct IconEntry {
    unsigned char data[0x10];
};
extern const IconEntry kMenuIcons[] __attribute__((visibility("hidden")));  // 0x71007f69bc

void draw_icon(void* target, const IconEntry* icon, void* texture);         // 0x71001eff04

class MenuIcons {
public:
    const IconEntry* icon(int id);                                          // 0x7100283d74
    void draw(void* target, int id);                                        // 0x7100283d8c
    void draw_entry(void* target, const IconEntry* icon);                   // 0x7100283db0

    void* texture;            // +00
};

const IconEntry* MenuIcons::icon(int id) {
    return static_cast<unsigned int>(id) > 0x105 ? nullptr : &kMenuIcons[id];
}

void MenuIcons::draw(void* target, int id) {
    draw_icon(target, icon(id), texture);
}

void MenuIcons::draw_entry(void* target, const IconEntry* icon) {
    draw_icon(target, icon, texture);
}

struct ResourceHandle {
    void* resource;
    void release();                                                         // 0x71001f7960
};

struct MenuBoard {
    ResourceHandle board;     // +00
    ResourceHandle units;     // +08
    unsigned char value10;    // +10
    unsigned char loaded;     // +11
    unsigned char pad12[6];
};
// Reached through the GOT slot at 0x7100c2a650.
extern MenuBoard* gMenuBoard;

void create_menu_board() {
    if (!gMenuBoard) {
        MenuBoard* board = static_cast<MenuBoard*>(get_default_heap()->allocate(0x10, sizeof(MenuBoard), 1, 0));
        board->value10 = 0;
        board->loaded = 0;
        board->board.resource = nullptr;
        board->units.resource = nullptr;
        gMenuBoard = board;
    }
}

static inline void clear_board(MenuBoard* board) {
    if (board->board.resource) {
        board->board.release();
        board->board.resource = nullptr;
    }
    if (board->units.resource) {
        board->units.release();
        board->units.resource = nullptr;
    }
    board->loaded = 0;
}

void release_menu_units() {
    if (MenuBoard* board = gMenuBoard) {
        clear_board(board);
        get_default_heap()->release(board, 1, 0);
        gMenuBoard = nullptr;
    }
}

void release_menu_board() {
    if (MenuBoard* board = gMenuBoard)
        clear_board(board);
}

class DialogTask {
public:
    DialogTask();                                                           // 0x71003892d8
    virtual ~DialogTask();
};

class EventTask : public DialogTask {
public:
    EventTask();                                                            // 0x7100283fd0
    ~EventTask();

    unsigned char pad8[0x2d41c];
    long value2d424;          // +2d424
    int value2d42c;           // +2d42c
    void* query;              // +2d430
    long value2d438;          // +2d438
    long value2d440;          // +2d440
    int value2d448;           // +2d448
    unsigned char pad2d44c[4];
} __attribute__((packed, aligned(8)));
static_assert(sizeof(EventTask) == 0x2d450, "event task size");

EventTask::EventTask() {
    query = nullptr;
    value2d424 = 0;
    value2d42c = 6;
    value2d440 = 0;
    value2d438 = 0;
    value2d448 = -1;
}

unsigned char game_has_flag(Game* game, int flag);                          // 0x71002026fc

static inline Player& final_player(Game* game) {
    unsigned int index = *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(game) + 0x1e374);
    return game->players[index];
}

class StageLights {
public:
    int item_of(int slot);                                                  // 0x71001fb214
};
// Reached through the GOT slot at 0x7100c21df8.
extern StageLights* gStageLights;
int item_category(unsigned int item);                                       // 0x7100211554

unsigned char slot_available(unsigned int slot) {
    if (slot > 0x63)
        return 1;
    unsigned int kind = item_category(gStageLights->item_of(slot));
    unsigned char result = kind - 3 <= 2 ? get_game()->has_item(slot) != 0 : 1;
    switch (slot) {
    case 17:
    case 18:
    case 23:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
        return 1;
    }
    return result;
}

class TrophyRecord;
unsigned char trophy_ready(TrophyRecord* record);                           // 0x7100288990
void* trophy_target(TrophyRecord* record);                                  // 0x7100288734
int target_item(void* target);                                              // 0x7100206098

unsigned char cell_trophy_open(int cell) {
    Game* game = get_game();
    int fallback = final_player(game).id;
    if (cell == -1)
        cell = fallback;
    int item = get_unit_database()->rows[cell].value28;
    if (static_cast<unsigned int>(item) > 0xc7)
        return 0;
    signed char count = get_game()->clear_count();
    for (unsigned int i = 0; i < static_cast<unsigned int>(count); ++i) {
        TrophyRecord* record = static_cast<TrophyRecord*>(get_game()->trophy(i));
        if (record && trophy_ready(record) && target_item(trophy_target(record)) == item)
            return 0;
    }
    return 1;
}

unsigned char cell_short_route(int cell) {
    Game* game = get_game();
    Player& player = final_player(game);
    int fallback = player.id;
    if (cell == -1)
        cell = fallback;
    UnitDatabase* database = get_unit_database();
    if (!game_has_flag(get_game(), 0x2d))
        return 0;
    if (static_cast<unsigned short>(database->rows[cell].value2a) > 0xef)
        return 0;
    return player.short_route[cell] != 0;
}

unsigned char cell_reward_locked(int cell) {
    Game* game = get_game();
    int fallback = final_player(game).id;
    if (cell == -1)
        cell = fallback;
    int reward = get_unit_database()->rows[cell].value2c;
    if (static_cast<unsigned int>(reward) > 0xfe)
        return 0;
    if (!game_has_flag(get_game(), 0x2d))
        return 0;
    return !get_game()->unlocked(reward);
}

void note_cell_item(int item) {
    Game* game = get_game();
    int cell = game->players[get_game()->state()->mode].id;
    if (cell != -1 && get_unit_database()->rows[cell].value2a == item)
        gBoardQuery.item_found = 1;
}

struct UnitSlot {
    int unit;
    int slot;
};
// Unit kind to unlock slot for modes 6-9 (0x71007f68b4).
static const UnitSlot kUnitSlots[19] __attribute__((used, section(".rodata.unit_slots"))) = {
    {0x72, 0}, {0x73, 0}, {0x74, 0}, {0x75, 0}, {0x80, 0}, {0x81, 0}, {0x7e, 1},
    {0x7f, 1}, {0x77, 2}, {0x78, 2}, {0xa9, 2}, {0xaa, 2}, {0x79, 3}, {0x7a, 3},
    {0x7d, 3}, {0xa8, 3}, {0x7b, 4}, {0x7c, 4}, {0x76, 6},
};

static inline unsigned int board_mode() {
    return get_game()->state()->mode;
}

bool unit_class_unlocked(int unit) {
    int slot;
    if (board_mode() == 3 || board_mode() == 4) {
        slot = 0;
        switch (unit) {
        case 0x79:
        case 0x7a:
        case 0x7d:
        case 0xa8:
            slot = 3;
            break;
        case 0x77:
        case 0x78:
            slot = 2;
            break;
        case 0x7b:
        case 0x7c:
            slot = 4;
            break;
        case 0x74:
        case 0x7e:
            slot = 1;
            break;
        case 0x76:
            slot = 6;
            break;
        }
    } else if (board_mode() == 6 || board_mode() == 7 || board_mode() == 8 || board_mode() == 9) {
        slot = 0;
        for (int i = 0; i < 19; ++i) {
            if (kUnitSlots[i].unit == unit) {
                slot = kUnitSlots[i].slot;
                break;
            }
        }
    } else {
        slot = 5;
    }
    return get_game()->class_unlocked(slot) != 0;
}
