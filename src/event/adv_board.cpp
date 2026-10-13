// Matching candidates for the Adventure Mode board queries 0x7100269858-0x710026b3c8.
// Player::setup (0x710026a98c), BoardQuery::find_entry (0x710026b3cc) and the catalog fill
// (0x710026b798) are at the end.
// Names are descriptive placeholders. Status: matching/README.md.

#include "resource/resource_frame.h"

extern "C" void* memset(void* dest, int value, unsigned long size);

class ItemTable {
public:
    unsigned char contains(unsigned int item);                              // 0x71001ff2c8
    int weapon_of(unsigned int item);                                       // 0x71001ff1c4
    unsigned char is_special(unsigned int item);                            // 0x71001ff2a4
    int level_of(int item);                                                 // 0x71001ff218
    unsigned char has_rare(int item);                                       // 0x71001ff280
    unsigned char has_common(int item);                                     // 0x71001ff25c
};
ItemTable* get_item_table();                                                // 0x71001ff050

struct WeaponRecord {
    short value;              // +0
    signed char kind;         // +2
};

class WeaponTable {
public:
    WeaponRecord* find(unsigned int weapon);                                // 0x7100215d34
};
WeaponTable* get_weapon_table();                                            // 0x7100215b84

class GameState {
public:
    unsigned char pad[0x1bb7c];
    unsigned int mode;        // +1bb7c
};

struct BoardRow;
unsigned char dlc_unit_unlocked(BoardRow* unit);

class CellRecord {
public:
    unsigned char cleared();                                                // 0x7100202164

    int unit;                 // +00
    int stage;                // +04
    int value8;               // +08
    unsigned char padc[8];
    int value14;              // +14
    int value18;              // +18
    unsigned char pad1c[0x1c];
    int value38;              // +38
};
static_assert(sizeof(CellRecord) == 0x3c, "cell record size");

struct PlayerMark {
    int flags;                // +0: bit 1 item held
    int value;                // +4
};

struct Player {
    bool cell_open(int cell);                                               // 0x710026a90c
    bool cell_cleared(int cell);                                            // 0x710026b0d4
    void setup(BoardRow* rows, int stage);                                  // 0x710026a98c
    int cell_state(unsigned int cell) { return cell_states[cell]; }

    int id;                   // +0000: current cell
    int cell_states[0x80];    // +0004
    PlayerMark marks[0x80];   // +0204: indexed by cell
    unsigned char pad604[0x64];
    unsigned char no_fort[0x80];  // +0668
    unsigned char pad6e8[0x80];
    unsigned char unguarded[0x80]; // +0768
    unsigned char open[0x80]; // +07e8
    unsigned char short_route[0x80]; // +0868
    int gate_levels[0x50];    // +08e8
    unsigned char pada28[0x140];
    CellRecord records[0x80]; // +0b68
    unsigned char seen[8];    // +2968: [6] is the DLC board flag
    unsigned char pad2970[0x158];
    int value2ac8;            // +2ac8
    unsigned char value2acc;  // +2acc
    unsigned char value2acd;  // +2acd
    unsigned char value2ace;  // +2ace
    unsigned char value2acf;  // +2acf
    unsigned char pad2ad0[2];
    unsigned char value2ad2;  // +2ad2
    unsigned char pad2ad3[0x65];
    unsigned char history[0x100]; // +2b38
};
static_assert(sizeof(Player) == 0x2c38, "player size");

class Progress {
public:
    unsigned char has(int content);                                         // 0x7100203180
    int base_level(int kind);                                               // 0x7100203550

    unsigned char pad[0x14c];
};

class Game {
public:
    GameState* state();                                                     // 0x7100204c10
    int unit_count(unsigned int mode, int slot, unsigned char flag);        // 0x7100203970
    void add_reward(unsigned int mode, int cell, int slot, unsigned char flag); // 0x7100203858
    void show_reward(unsigned int mode, int cell, int slot, unsigned char flag); // 0x7100203aa8

    unsigned char pad[0x27f8];
    Progress progress;        // +27f8
    Player players[1];        // +2944
};
Game* get_game();                                                           // 0x7100204728

// Two runs of bitfields (8 and 4 bytes); the compiler reads them with mixed widths, as the original does.
struct UnitInfo {
    int kind : 16;            // +0
    int frame : 16;           // +2
    int override : 16;        // +4: negative when unset
    int value6 : 16;          // +6
    int : 0;
    int value8 : 8;           // +8
    int team : 8;             // +9
    int value10 : 8;          // +a
    unsigned int defeated : 8; // +b
};
static_assert(sizeof(UnitInfo) == 0xc, "unit info size");

struct CellPosition {
    int x;
    int y;
};

// One player's board (0x1e0 bytes).
struct BoardRow {
    unsigned char gate_state(int gate, unsigned char raw);                  // 0x710026a220

    short value0;             // +00
    short value2;             // +02
    short value4;             // +04
    unsigned char pad6[2];
    signed char gates[4];     // +08
    signed char owner;        // +0c
    unsigned char blocked[4]; // +0d
    signed char guards;       // +11
    unsigned char kind;       // +12
    signed char level;        // +13
    signed char group;        // +14
    unsigned char pad15;
    unsigned short value16;   // +16
    unsigned short value18;   // +18
    unsigned short value1a;   // +1a
    unsigned short value1c;   // +1c
    unsigned short value1e;   // +1e
    unsigned char pad20[6];
    short item;               // +26
    unsigned char pad28[2];
    unsigned short value2a;   // +2a
    unsigned char pad2c[2];
    short cells[0xb0];        // +2e: unit index of each board cell
    unsigned char pad18e[2];
    CellPosition positions[2][5]; // +190
};
static_assert(sizeof(BoardRow) == 0x1e0, "board row size");

struct Unit {
    unsigned char has_flag(int flag);                                       // 0x710020d984
    void set_flag(int flag, bool on);                                       // 0x710020dc10

    unsigned char pad0[4];
    int value4;               // +04
    unsigned char pad8[0x36];
    unsigned short rank;      // +3e
};

// Reward items of a cell (8 bytes).
struct RewardPair {
    short second;             // +0
    unsigned char pad2[2];
    short first;              // +4
    unsigned char pad6[2];
};

class UnitDatabase {
public:
    Unit* unit(int id);                                                     // 0x710020eeb8

    unsigned char pad[0xdb608];
    BoardRow rows[1];         // +db608
};
UnitDatabase* get_unit_database();                                          // 0x710020ec80

static inline RewardPair* reward_pairs(UnitDatabase* database) {
    return reinterpret_cast<RewardPair*>(reinterpret_cast<unsigned char*>(database) + 0xebd7a);
}

static inline UnitInfo* unit_infos(UnitDatabase* database) {
    return reinterpret_cast<UnitInfo*>(reinterpret_cast<unsigned char*>(database) + 0xea608);
}

// Team byte of a unit record, read as a plain byte.
static inline signed char unit_team(UnitInfo* info) {
    return reinterpret_cast<signed char*>(info)[9];
}

class BoardOverride {
public:
    int stage_kind(int player);                                             // 0x7100290fb0
    int remap_kind(int kind, void* table);                                  // 0x7100290fd4
    unsigned char has_primary(int player, int slot);                        // 0x71002910b0
    unsigned char has_secondary(int player, int slot);                      // 0x7100291058
};
// Reached through the GOT slot at 0x7100c2a6f0.
extern BoardOverride gBoardOverride;
// Gate level thresholds, reached through the GOT slot at 0x7100c2a6f8.
extern int gGateLevels[];

class Unlocks {
public:
    unsigned char has(int content);                                         // 0x7100224990
};
Unlocks* get_unlocks();                                                     // 0x71002248a0

// Neighbour offsets (up, left, right, down) and the gate pairs they share.
extern const int kNeighborOffsets[4] __attribute__((visibility("hidden")));  // 0x71007e1ff0
struct GatePair {
    int neighbor;
    int own;
};
extern const GatePair kGatePairs[4] __attribute__((visibility("hidden")));   // 0x71007e3c08

extern const int kBoardValues[] __attribute__((visibility("hidden")));     // 0x71007f6718

static inline unsigned int game_mode() {
    return get_game()->state()->mode;
}

static inline WeaponRecord* item_weapon(unsigned int item) {
    if (item <= 0x2e3 && get_item_table()->contains(item)) {
        unsigned int weapon = get_item_table()->weapon_of(item);
        if (weapon <= 0x12b)
            return get_weapon_table()->find(weapon);
    }
    return nullptr;
}

int item_weapon_value(unsigned int item) {
    if (WeaponRecord* record = item_weapon(item))
        return record->value;
    return -1;
}

int item_rank(unsigned int item) {
    WeaponRecord* record = item_weapon(item);
    if (record && record->kind == 0)
        return 1;
    record = item_weapon(item);
    if (record && record->kind == 1)
        return 2;
    record = item_weapon(item);
    if (record && record->kind == 2)
        return 3;
    record = item_weapon(item);
    if (record && record->kind == 3)
        return 4;
    record = item_weapon(item);
    if (record && record->kind == 4)
        return 5;
    return get_item_table()->is_special(item) != 0;
}

bool item_is_kind(unsigned int item, int kind) {
    WeaponRecord* record = item_weapon(item);
    if (record && record->kind == kind)
        return true;
    return false;
}

bool board_intro_pending() {
    Game* game = get_game();
    if (!game->players[game_mode()].value2ac8)
        return false;
    if (game_mode() != 0)
        return false;
    game = get_game();
    if (game->players[game_mode()].id != 0x68)
        return false;
    return game_mode() == 0;
}

class BoardQuery {
public:
    int active_count(int slot);                                             // 0x7100269bb8
    int total_count(int slot);                                              // 0x7100269bfc
    bool unit_alive(int player, int slot, int team);                        // 0x7100269c40
    int cell_level(unsigned int cell);                                      // 0x710026b234
    void find_entry(unsigned int cell, unsigned int slot, int kind, int* level, int* position,
                    int* state);                                            // 0x710026b3cc

    unsigned char pad[0x2d8];
    unsigned char groups[0x100]; // +02d8
    int levels[0x80][0x1c];   // +03d8
    int kinds[0x80][0x1c];    // +3bd8
    unsigned char flags[0x80][0x1c]; // +73d8
    unsigned int items[0x80][0x1c]; // +81d8
    unsigned char padb9d8[0xc];
    int access;               // +b9e4
};
// Reached through the GOT slot at 0x7100c23250.
extern BoardQuery gBoardQuery;

int BoardQuery::active_count(int slot) {
    Game* game = get_game();
    return game->unit_count(game_mode(), slot, 1);
}

int BoardQuery::total_count(int slot) {
    Game* game = get_game();
    return game->unit_count(game_mode(), slot, 0);
}

int unit_kind(int player, int slot);

bool BoardQuery::unit_alive(int player, int slot, int team) {
    get_game();
    game_mode();
    unit_kind(player, slot);
    unsigned int index = get_unit_database()->rows[player].cells[static_cast<unsigned int>(slot)];
    if (team < 0)
        return false;
    if (team != 0) {
        if (unit_infos(get_unit_database())[index].team != team ||
            unit_infos(get_unit_database())[index].defeated == 1)
            return false;
    }
    return true;
}

int unit_kind(int player, int slot) {
    unsigned int index = get_unit_database()->rows[player].cells[static_cast<unsigned int>(slot)];
    int kind = unit_infos(get_unit_database())[index].kind;
    if (game_mode() == 3) {
        if (kind == 0xd2)
            return gBoardOverride.stage_kind(player);
    } else if (game_mode() == 4) {
        return gBoardOverride.remap_kind(kind, &gBoardQuery);
    }
    return kind;
}

struct TrackVec2 {
    float x;
    float y;
};
class AdvBoard {
public:
    TrackVec2 start_position(int state);                                    // 0x710029f8ec
};
// Reached through the GOT slot at 0x7100c2a6c0.
extern AdvBoard* gAdvBoard;
unsigned int display_width();                                               // 0x71003cc930
unsigned int display_height();                                              // 0x71003cc94c

unsigned int random_below(int count);                                       // 0x7100459bd8
int item_category(unsigned int item);                                       // 0x7100211554

int board_value(int index) {
    return kBoardValues[index];
}

int held_kind(int kind, int player) {
    Game* game = get_game();
    unsigned int mode = game_mode();
    UnitDatabase* database = get_unit_database();
    if ((kind == 0x12 || kind == 0x14 || kind == 0x15 || kind == 0x1a || kind == 0x1b || kind == 0x1c) &&
        (game->players[mode].marks[player].flags & 2)) {
        int level = get_item_table()->level_of(database->rows[player].item);
        kind = static_cast<unsigned int>(level) < 100 ? level : 0;
    }
    return kind;
}

int neighbor_cell(int cell, unsigned int direction) {
    switch (direction) {
    case 0:
        return cell > 15 ? cell - 16 : cell;
    case 1:
        return cell % 16 != 0 ? cell - 1 : cell;
    case 2:
        return cell % 16 != 15 ? cell + 1 : cell;
    case 3:
        return cell < 0x70 ? cell + 16 : cell;
    case 4: {
        int target = cell % 16 != 0 ? cell - 17 : cell - 16;
        return cell > 15 ? target : target + 16;
    }
    case 5: {
        int target = cell % 16 != 15 ? cell - 15 : cell - 16;
        return cell > 15 ? target : target + 16;
    }
    case 7: {
        int target = cell % 16 != 0 ? cell + 15 : cell + 16;
        return cell < 0x70 ? target : target - 16;
    }
    case 8: {
        int target = cell % 16 != 15 ? cell + 17 : cell + 16;
        return cell < 0x70 ? target : target - 16;
    }
    }
    return cell;
}

bool is_officer_kind(int kind) {
    switch (kind) {
    case 8:
    case 9:
    case 15:
    case 23:
    case 49:
    case 56:
    case 63:
    case 69:
        return true;
    }
    return false;
}

bool is_keep_kind(int kind) {
    switch (kind) {
    case 10:
    case 11:
    case 12:
    case 22:
    case 24:
    case 25:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 57:
    case 60:
    case 61:
        return true;
    }
    return false;
}

bool is_fort_kind(int kind) {
    switch (kind) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 13:
    case 14:
    case 16:
    case 33:
    case 34:
    case 35:
    case 47:
    case 48:
    case 58:
    case 62:
    case 64:
    case 65:
    case 66:
    case 67:
    case 68:
        return true;
    }
    return game_mode() == 8 && kind == 0x1e;
}

bool is_gate_kind(int kind) {
    if (game_mode() == 8)
        return kind >= 0x32 && kind <= 0x37;
    switch (kind) {
    case 17:
    case 30:
    case 31:
    case 32:
    case 59:
        return true;
    }
    return false;
}

int open_gate(int player) {
    Game* game = get_game();
    unsigned int mode = game_mode();
    BoardRow* row = &get_unit_database()->rows[static_cast<unsigned int>(player)];
    PlayerMark* mark = &game->players[mode].marks[player];
    for (int i = 0; i < 4; ++i) {
        if (row->gate_state(i, 0) == 7 && !(mark->flags & 0x1000))
            return i;
    }
    return -1;
}

unsigned char BoardRow::gate_state(int gate, unsigned char raw) {
    signed char state = gates[gate];
    if (raw)
        return state;
    Game* game = get_game();
    unsigned int mode = game_mode();
    bool open;
    switch (gate) {
    case 0:
        open = game->players[mode].marks[owner].flags & 0x100;
        break;
    case 1:
        open = game->players[mode].marks[owner].flags & 0x40;
        break;
    case 2:
        open = game->players[mode].marks[owner].flags & 0x20;
        break;
    case 3:
        open = game->players[mode].marks[owner].flags & 0x80;
        break;
    default:
        open = false;
        break;
    }
    if (open) {
        unsigned int level = game->players[mode].gate_levels[owner];
        if (state <= 3 && level != 0xffffffffu)
            state = gGateLevels[level] <= state ? 2 : state;
    }
    game = get_game();
    mode = game_mode();
    if (state == 7)
        state = !(game->players[mode].marks[owner].flags & 0x1000) ? 7 : 2;
    game = get_game();
    if (game->players[game_mode()].value2acd == 3) {
        if (state == 0 || state == 1)
            state = 2;
        return state;
    }
    game = get_game();
    Player& player = game->players[game_mode()];
    bool locked = game_mode() == 8 && player.value2ad2 == 9;
    if (locked & (state == 1 || state == 2))
        state = 0;
    return state;
}

static inline bool content_unlocked(int content) {
    return get_game()->progress.has(content) && get_unlocks()->has(content);
}

unsigned char dlc_unit_unlocked(BoardRow* unit) {
    if (unit->kind == 0x17 && content_unlocked(6))
        return true;
    if (unit->kind == 0x18 && content_unlocked(7))
        return true;
    if (unit->kind == 0x19 && content_unlocked(8))
        return true;
    return unit->kind == 0x1a && content_unlocked(9);
}

static inline bool is_dlc_kind(BoardRow* row) {
    return row->kind >= 0x17 && row->kind <= 0x1a;
}

bool Player::cell_open(int cell) {
    BoardRow* row = &get_unit_database()->rows[cell];
    if (is_dlc_kind(row) && !dlc_unit_unlocked(row))
        return false;
    return cell_state(cell) > 1;
}

void update_dlc_gates() {
    UnitDatabase* database = get_unit_database();
    Game* game = get_game();
    unsigned int mode = game_mode();
    Player* player = &game->players[mode];
    for (int i = 0; i < 0x80; ++i) {
        BoardRow* row = &database->rows[i];
        if (!is_dlc_kind(row))
            continue;
        if (!dlc_unit_unlocked(row)) {
            row->kind = 3;
            player->cell_states[i] = -1;
            continue;
        }
        if (database->rows[i].level <= 0) {
            row->kind = 3;
            game->players[mode].cell_states[i] = 3;
        }
        int column = i % 16;
        for (int d = 0; d < 4; ++d) {
            int neighbor = i + kNeighborOffsets[d];
            if (static_cast<unsigned int>(neighbor) > 0x7f || (column == 0 && d == 1) ||
                (column == 15 && d == 2))
                continue;
            const GatePair& pair = kGatePairs[d];
            signed char state;
            if (game->players[mode].cell_open(neighbor) ||
                (dlc_unit_unlocked(&database->rows[neighbor]) && database->rows[neighbor].level >= 1))
                state = 3;
            else
                state = 4;
            database->rows[neighbor].gates[pair.neighbor] = state;
            database->rows[i].gates[pair.own] = state;
        }
    }
}

bool dlc_board_flag() {
    Game* game = get_game();
    return game->players[game_mode()].seen[6] != 0;
}

bool Player::cell_cleared(int cell) {
    BoardRow* row = &get_unit_database()->rows[cell];
    if (is_dlc_kind(row) && !dlc_unit_unlocked(row))
        return false;
    return cell_state(cell) == 3;
}

unsigned char cell_selectable(int cell) {
    switch (get_unit_database()->rows[static_cast<unsigned int>(cell)].value0) {
    case 0x15c:
    case 0x283:
    case 0x3e6:
    case 0x50d:
        return false;
    }
    if (game_mode() == 4 && get_unit_database()->rows[cell].value1e == 6 && !dlc_board_flag())
        return false;
    return true;
}

int BoardQuery::cell_level(unsigned int cell) {
    int level = get_game()->progress.base_level(0);
    int value = get_unit_database()->rows[cell].value4;
    Game* game = get_game();
    Player& player = game->players[game_mode()];
    if (player.gate_levels[player.id] == 3)
        value = -1;
    bool own;
    if (game_mode() == 8) {
        game = get_game();
        own = game->players[game_mode()].value2acd != 5 && static_cast<unsigned int>(value) <= 0x63;
    } else {
        own = static_cast<unsigned int>(value) <= 0x63;
    }
    if (own) {
        game = get_game();
        if (!game->players[game_mode()].records[cell].cleared())
            level = value;
    }
    return static_cast<unsigned int>(level) < 100 ? level : 0;
}

bool board_complete() {
    Game* game = get_game();
    Player& player = game->players[game_mode()];
    return player.gate_levels[player.id] == 3;
}

static inline void find_start(int& id, BoardRow* rows) {
    for (int i = 0; i < 0x80; ++i) {
        if (rows[i].kind == 1 || rows[i].kind == 7) {
            id = i;
            break;
        }
    }
}

void Player::setup(BoardRow* rows, int stage) {
    if (id != -1 && !cell_open(id)) {
        find_start(id, rows);
    }
    if (stage == 4 && dlc_board_flag()) {
        if (!cell_cleared(0x22))
            cell_states[0x22] = 2;
    }
    if (id != -1) {
        if (game_mode() >= 3 && !cell_selectable(id)) {
            find_start(id, rows);
        }
        return;
    }
    for (int i = 0; i < 0x80; ++i) {
        BoardRow* row = &rows[i];
        if (row->kind == 7 || row->kind == 1) {
            id = i;
            unsigned long slot = static_cast<short>(rows[i].value1e);
            if (slot <= 7)
                seen[slot] = 1;
        }
        open[i] = 1;
        if (rows[i].blocked[0] || rows[i].blocked[1] || rows[i].blocked[2] || rows[i].blocked[3])
            open[i] = 0;
        unguarded[i] = rows[i].guards <= 0;
        bool fort = false;
        for (int j = 0; j < 0xb0 && !fort; ++j)
            fort = is_fort_kind(unit_team(&unit_infos(get_unit_database())[row->cells[j]]));
        no_fort[i] = !fort;
        switch (row->kind) {
        case 3:
        case 6:
        case 11:
        case 13:
        case 18:
            cell_states[i] = 3;
            break;
        }
        unsigned int mode = game_mode();
        if (rows[i].value16 >= 0x12c) {
            get_game()->add_reward(mode, i, 2, 1);
            get_game()->show_reward(mode, i, 2, 1);
        }
        if (rows[i].value18 >= 0x12c) {
            get_game()->add_reward(mode, i, 3, 1);
            get_game()->show_reward(mode, i, 3, 1);
        }
        RewardPair* pair = &reward_pairs(get_unit_database())[rows[i].value2];
        int first = pair->first;
        int second = pair->second;
        if (rows[i].value1c >= 100 && !get_item_table()->has_rare(second) &&
            !get_item_table()->has_rare(first)) {
            get_game()->add_reward(mode, i, 1, 1);
            get_game()->show_reward(mode, i, 1, 1);
        }
        if (rows[i].value1a >= 100 && !get_item_table()->has_common(second) &&
            !get_item_table()->has_common(first)) {
            get_game()->add_reward(mode, i, 0, 1);
            get_game()->show_reward(mode, i, 0, 1);
        }
        if (rows[i].value2a <= 0xef)
            short_route[i] = 1;
        unsigned char kind = row->kind;
        if (kind == 0xf || kind == 0x10)
            marks[i].flags |= 1;
        else
            marks[i].flags &= ~1;
        Unit* unit = get_unit_database()->unit(rows[i].value0);
        if (unit->rank == 3)
            marks[i].flags |= 0x200;
        if (unit->rank == 4)
            marks[i].flags |= 0x400;
        if (unit->rank == 5)
            marks[i].flags |= 0x800;
        if (kind == 0x1b)
            marks[i].flags |= 0x2000;
        else
            marks[i].flags &= ~0x2000;
        if (kind == 0x1c)
            marks[i].flags |= 0x4000;
        else
            marks[i].flags &= ~0x4000;
        if (kind == 0x1d)
            marks[i].flags |= 0x8000;
        else
            marks[i].flags &= ~0x8000;
        if (static_cast<short>(rows[i].value1e) == -1)
            cell_states[i] = 3;
    }
    cell_states[id] = 3;
    switch (stage) {
    case 4:
        value2acc = 3;
        value2acf = 0;
        break;
    case 5:
        value2acc = 0xff;
        break;
    case 8:
        cell_states[0x73] = 2;
        break;
    case 9:
        value2acc = 0xff;
        value2acd = 0xff;
        value2ace = 0xff;
        value2acf = 0xff;
        break;
    }
    memset(history, 0, sizeof(history));
}

static inline bool tracks_items() {
    return game_mode() == 3 || game_mode() == 4 || game_mode() >= 6;
}

static inline int cell_position(CellPosition& position) {
    return position.x + position.y * 16;
}

void BoardQuery::find_entry(unsigned int cell, unsigned int slot, int kind, int* level, int* position,
                            int* state) {
    *state = 0;
    if (kind != 0) {
        int id = get_unit_database()->rows[cell].value0;
        if (get_unit_database()->unit(id)->has_flag(13)) {
            *position = cell_position(get_unit_database()->rows[cell].positions[0][slot]);
            if (slot <= 2) {
                *level = -1;
                *state = 1;
            }
            return;
        }
        id = get_unit_database()->rows[cell].value0;
        Unit* unit = get_unit_database()->unit(id);
        if (slot >= 3 && unit->value4 == 0x6f)
            return;
    } else if (slot == 0) {
        *level = cell_level(cell);
        *position = cell_position(get_unit_database()->rows[cell].positions[1][0]);
        return;
    }
    unsigned int count = 0;
    for (int k = 0; k < 0x1c; ++k) {
        if (kinds[cell][k] != kind)
            continue;
        int value = levels[cell][k];
        bool same = value == cell_level(cell);
        int id = get_unit_database()->rows[cell].value0;
        bool hidden = get_unit_database()->unit(id)->value4 == 0x70 ? false : same;
        if (tracks_items() && flags[cell][k])
            hidden = false;
        if (tracks_items() && items[cell][k] <= 0x44b) {
            int category = item_category(items[cell][k]);
            if (k >= 1 && (category == 3 || category == 4)) {
                bool repeat = false;
                for (int m = 0; m < k; ++m) {
                    if (value == levels[cell][m] && kinds[cell][m] == kinds[cell][k]) {
                        repeat = true;
                        break;
                    }
                }
                if (repeat)
                    continue;
            }
        }
        if (count == slot && !hidden) {
            *level = value;
            *position = cell_position(get_unit_database()->rows[cell].positions[kind == 0][slot]);
            if (flags[cell][k])
                *state = 2;
            return;
        }
        count += !hidden || k == 0;
    }
}

int stage_message() {
    unsigned int mode = game_mode();
    return static_cast<int>(mode) > 6 ? mode + 0x461e : 0x4210;
}

bool is_plain_cell(BoardRow* row) {
    switch (row->kind) {
    case 8:
    case 12:
    case 14:
    case 20:
    case 21:
        return false;
    }
    signed char kind = row->kind;
    return kind >= 0 && kind < 0x20;
}

int unit_override_kind(int player, int slot) {
    unsigned int index = get_unit_database()->rows[player].cells[static_cast<unsigned int>(slot)];
    int kind = unit_infos(get_unit_database())[index].kind;
    if (unit_infos(get_unit_database())[index].override < 0)
        return kind;
    kind = unit_infos(get_unit_database())[index].override;
    if (game_mode() == 4)
        return gBoardOverride.remap_kind(kind, &gBoardQuery);
    return kind;
}

int unit_frame(int player, int slot) {
    unsigned int index = get_unit_database()->rows[player].cells[static_cast<unsigned int>(slot)];
    int frame = unit_infos(get_unit_database())[index].frame;
    Game* game = get_game();
    unsigned int mode = game_mode();
    if (game_mode() == 3) {
        if (frame == 0xd2)
            frame = gBoardOverride.stage_kind(player);
    } else if (game_mode() == 4) {
        frame = gBoardOverride.remap_kind(frame, &gBoardQuery);
    }
    if (player == 0x17 && game_mode() == 7 && game->players[mode].unguarded[player]) {
        if (static_cast<unsigned short>(index) == 0x87)
            return 0x8f;
        if (static_cast<unsigned short>(index) == 0x8c)
            return 0x90;
    }
    return frame;
}

int unit_override_frame(int player, int slot) {
    unsigned int index = get_unit_database()->rows[player].cells[static_cast<unsigned int>(slot)];
    int value = unit_infos(get_unit_database())[index].value6;
    if (game_mode() == 4)
        return gBoardOverride.remap_kind(value, &gBoardQuery);
    return value;
}

class ShopEntry {
public:
    unsigned char valid();                                                  // 0x710019b8c0
    int item();                                                             // 0x710019bb74
};

class ShopList {
public:
    unsigned char valid();                                                  // 0x710019b8ec
    ShopEntry* entry(int index);                                            // 0x710019ba6c
    int kind();                                                             // 0x710019b928
    unsigned char limited();                                                // 0x710019b9e4
};

class Catalog {
public:
    ShopList* list(int index);                                              // 0x710019bcfc
};

class ShopManager {
public:
    Catalog* catalog();                                                     // 0x71001898b8
    void select_unit(int unit);                                             // 0x710018ca68
};
// Reached through the GOT slot at 0x7100c216e8.
extern ShopManager* gShop;

struct ItemDef {
    unsigned char pad0[0x32];
    unsigned short price;     // +32
    unsigned char pad34[2];
    signed char rarity;       // +36
    unsigned char pad37[6];
    unsigned char flags;      // +3d: bit 4 tradable
    unsigned char pad3e[0x12];
};
static_assert(sizeof(ItemDef) == 0x50, "item def size");
// Reached through the GOT slot at 0x7100c216a0.
extern ItemDef* gItemDefs;

int item_group(int item);                                                   // 0x71001fb810

static inline ItemDef* item_def(int item) {
    return static_cast<unsigned int>(item) <= 0x44b ? &gItemDefs[item] : nullptr;
}

static inline bool is_rare_item(int item) {
    ItemDef* def = item_def(item);
    if (!def || !(def->flags & 0x10) || def->price > 0x63)
        return false;
    switch (def->rarity) {
    case 4:
    case 6:
        return true;
    }
    return false;
}

void fill_cell_entries(unsigned int cell, unsigned int* count, int min_level, int max_level,
                       unsigned char unique) {
    if (*count > 0x1b)
        return;
    for (int index = 2; index < 0x76; ++index) {
        ShopList* list = gShop->catalog()->list(index);
        if (!list->valid())
            continue;
        for (int i = 0; i < 3; ++i) {
            ShopEntry* entry = list->entry(i);
            if (!entry->valid())
                continue;
            int item = entry->item();
            int level = item_category(item);
            bool rare = is_rare_item(item);
            if (level < min_level || level > max_level)
                continue;
            if (*count >= 2) {
                bool known = false;
                for (unsigned int k = 1; k < *count; ++k) {
                    if (gBoardQuery.levels[cell][k] != item_group(item))
                        continue;
                    if (game_mode() < 3) {
                        known = true;
                    } else {
                        known = !rare && !gBoardQuery.flags[static_cast<int>(cell)][static_cast<int>(k)];
                        Unit* unit = get_unit_database()->unit(get_unit_database()->rows[static_cast<int>(cell)].value0);
                        if (!rare && gBoardQuery.kinds[static_cast<int>(cell)][static_cast<int>(k)] == 3 &&
                            unit->value4 == 0x70)
                            known = false;
                    }
                }
                if (known && (unique || list->limited())) {
                    if (*count > 0x1b)
                        break;
                    continue;
                }
                if (*count > 0x1b)
                    break;
            }
            gBoardQuery.levels[cell][*count] = item_group(item);
            gBoardQuery.kinds[cell][*count] = list->kind();
            Unit* unit = get_unit_database()->unit(get_unit_database()->rows[static_cast<int>(cell)].value0);
            switch (unit->value4) {
            case 12:
            case 20:
            case 22:
            case 0x70:
            case 0x73:
            case 0x74:
            case 0x75:
                if (list->kind() == 2)
                    gBoardQuery.kinds[cell][*count] = 1;
                break;
            }
            bool limited = list->limited();
            if (index >= 5 && limited) {
                UnitDatabase* database = get_unit_database();
                if (level != 5 || database->rows[static_cast<int>(cell)].level <= 0) {
                    if (!unit->has_flag(0xf)) {
                        bool shared = unit->has_flag(0x10);
                        if (!((level == 3 || level == 4) && shared))
                            gBoardQuery.kinds[cell][*count] = 3;
                    }
                }
            }
            if (item_group(item) == 0x42)
                gBoardQuery.kinds[cell][*count] = 3;
            if (is_rare_item(item))
                gBoardQuery.flags[static_cast<int>(cell)][*count] = 1;
            gBoardQuery.items[static_cast<int>(cell)][*count] = item;
            ++*count;
            if (*count > 0x1b)
                break;
        }
    }
}

class OverlayLayer {
public:
    void close();                                                           // 0x71003abd40
};

class Overlay {
public:
    OverlayLayer* current_layer();                                          // 0x71003ad160
};
Overlay* get_overlay();                                                     // 0x71003abbe0

void begin_board_load();                                                    // 0x710016fac0
void end_board_load();                                                      // 0x710016fae0

class BattleSetup {
public:
    void reset();                                                           // 0x710016ef18
    void set_flags(int flags);                                              // 0x710016f2ac
    void set_unit(int unit);                                                // 0x710016f2c4
};
BattleSetup* get_battle_setup();                                            // 0x710016ef34

class BattleParams {
public:
    void reset();                                                           // 0x71001a8ba4
    void set_mode(int mode);                                                // 0x71001a8d24
    void set_side(int side);                                                // 0x71001a8d34
    void set_level(int slot, int level);                                    // 0x71001a8d48
    void set_stage(int stage);                                              // 0x71001a8e2c

    unsigned char pad[0x98];
    int value98;              // +98
    unsigned char pad9c[8];
    int valuea4;              // +a4
    int valuea8;              // +a8
    int valueac;              // +ac
};
BattleParams* get_battle_params();                                          // 0x71001a8c38

void start_board_battle() {
    unsigned int count;
    if (get_overlay())
        get_overlay()->current_layer()->close();
    begin_board_load();
    Game* game = get_game();
    int cell = game->players[game_mode()].id;
    int unit = get_unit_database()->rows[cell].value0;
    get_battle_setup()->reset();
    get_battle_setup()->set_flags(0x400);
    get_battle_setup()->set_unit(unit);
    BattleParams* params = get_battle_params();
    params->reset();
    params->set_mode(1);
    params->set_side(1);
    params->set_level(0, get_game()->progress.base_level(0));
    int level = get_unit_database()->rows[cell].value4;
    game = get_game();
    Player& player = game->players[game_mode()];
    if (player.gate_levels[player.id] == 3)
        level = -1;
    if (game_mode() == 8) {
        game = get_game();
        Player& current = game->players[game_mode()];
        if (static_cast<unsigned int>(level) <= 0x63 && current.value2acd != 5)
            params->set_level(0, level);
    } else if (static_cast<unsigned int>(level) <= 0x63) {
        params->set_level(0, level);
    }
    game = get_game();
    CellRecord record = game->players[game_mode()].records[cell];
    if (record.cleared()) {
        params->set_stage(record.stage);
        params->valuea4 = record.value14;
        params->value98 = record.value8;
        params->valuea8 = record.value18;
        params->valueac = record.value38;
        unit = record.unit;
        get_battle_setup()->set_unit(unit);
        params->set_level(0, get_game()->progress.base_level(0));
    }
    get_unit_database()->unit(unit)->set_flag(1, game_mode() == 3);
    get_unit_database()->unit(unit)->set_flag(4, game_mode() == 4);
    bool late = game_mode() > 6;
    get_unit_database()->unit(unit)->set_flag(0x10, late);
    gShop->select_unit(unit);
    gBoardQuery.levels[static_cast<unsigned int>(cell)][0] = 0;
    gBoardQuery.kinds[static_cast<unsigned int>(cell)][0] = 0;
    count = 1;
    fill_cell_entries(cell, &count, 5, 5, 0);
    fill_cell_entries(cell, &count, 3, 4, 1);
    fill_cell_entries(cell, &count, 2, 2, 1);
    unsigned int previous = count;
    if (previous - 1 <= 0x1a) {
        do {
            fill_cell_entries(cell, &count, 2, 2, 0);
            if (count > 0x1b || previous == count)
                break;
            previous = count;
        } while (true);
    }
    get_battle_setup()->reset();
    end_board_load();
}

int ward_slot(int player, int slot, unsigned char want, unsigned char exit) {
    Game* game = get_game();
    unsigned int mode = game_mode();
    if (player == 0x49) {
        int bit;
        if (exit) {
            switch (slot) {
            case 0x18:
                bit = 0;
                break;
            case 0x45:
                bit = 1;
                break;
            case 0x4b:
                bit = 2;
                break;
            case 0x78:
                bit = 3;
                break;
            default:
                return -1;
            }
        } else {
            switch (slot) {
            case 0x38:
                bit = 0;
                break;
            case 0x47:
                bit = 1;
                break;
            case 0x49:
                bit = 2;
                break;
            case 0x58:
                bit = 3;
                break;
            default:
                return -1;
            }
        }
        if (((game->players[mode].value2ace & (1 << bit)) != 0) != want)
            return -1;
        return bit;
    }
    return -1;
}
unsigned char unit_has_override(int player, int slot) {
    Game* game = get_game();
    unsigned int mode = game_mode();
    unsigned int index = get_unit_database()->rows[player].cells[static_cast<unsigned int>(slot)];
    int team = unit_infos(get_unit_database())[index].team;
    if (is_fort_kind(team))
        return game->players[mode].no_fort[player];
    switch (team) {
    case 8:
    case 9:
    case 0xf:
    case 0x17:
    case 0x31:
    case 0x38:
    case 0x3f:
    case 0x45:
        return game->players[mode].open[player];
    case 0xa:
    case 0xb:
    case 0xc:
    case 0x16:
    case 0x18:
    case 0x19:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x39:
    case 0x3c:
    case 0x3d:
        return game->players[mode].unguarded[player];
    case 0x1c: {
        int first = ward_slot(player, slot, 1, 0);
        int second = ward_slot(player, slot, 1, 1);
        return (first & second) != -1;
    }
    case 0x1e:
        return !(game->players[mode].marks[player].flags & 0x400);
    case 0x1f:
        return !(game->players[mode].marks[player].flags & 0x200);
    case 0x20:
        return !(game->players[mode].marks[player].flags & 0x800);
    }
    if (gBoardOverride.has_primary(player, slot))
        return !(game->players[mode].marks[player].flags & 0x4000);
    if (gBoardOverride.has_secondary(player, slot))
        return !(game->players[mode].marks[player].flags & 0x8000);
    return 0;
}

class DataChunk {
public:
    DataChunk();                                                            // 0x7100218c18
    ~DataChunk();                                                           // 0x7100218c2c
    void set(const void* data);                                             // 0x7100218c34
    int size();                                                             // 0x71002192c0
    void* data(int offset, int flags);                                      // 0x7100218cac
    void release(int flags);                                                // 0x7100218c68

    unsigned char pad[0x10];
};

class DataStream {
public:
    DataStream();                                                           // 0x71001fbbb0
    ~DataStream();                                                          // 0x71001fbbd0
    void open(int mode, int size, void* data);                              // 0x71001fbc04
    void close();                                                           // 0x71001fbbf0
    void read(unsigned short* value);                                       // 0x71001fbc84
    void write(unsigned short value);                                       // 0x71001fbe00

    void transfer(short& value) {
        if (reading)
            read(reinterpret_cast<unsigned short*>(&value));
        else
            write(value);
    }

    unsigned char pad[0x1c];
    int reading;              // +1c
};

static inline unsigned int board_file(unsigned int stage, unsigned int small, unsigned int large) {
    if (stage <= 5)
        return stage + small;
    return stage + large;
}

static inline void open_chunk(DataChunk& chunk, DataStream& stream, const void* data) {
    chunk.set(data);
    int size = chunk.size();
    stream.open(1, size, chunk.data(0, 0));
}

static inline void close_chunk(DataChunk& chunk, DataStream& stream) {
    stream.close();
    chunk.release(0);
}

void BoardRow_serialize(BoardRow* row, DataStream* stream, int index);     // 0x710028342c
void BoardRow_serialize_extra(BoardRow* row, DataStream* stream);          // 0x710028386c
void UnitInfo_serialize(UnitInfo* info, DataStream* stream);               // 0x7100283964
void RewardPair_serialize(void* pair, DataStream* stream);                 // 0x7100283aa4

void load_board(unsigned int stage) {
    ResourceFrame frame;
    DataChunk chunk;
    DataStream stream;
    frame.open(0, board_file(stage, 0x47, 0x4616), nullptr);
    if (frame.is_open()) {
        open_chunk(chunk, stream, frame.lookup(0));
        BoardRow* rows = get_unit_database()->rows;
        for (int i = 0; i < 0x80; ++i)
            BoardRow_serialize(&rows[i], &stream, i);
        close_chunk(chunk, stream);
        ResourceFrame cells;
        cells.open(0, board_file(stage, 0x4d, 0x461a), nullptr);
        for (int i = 0; i < 0x80; ++i) {
            open_chunk(chunk, stream, cells.lookup(i));
            BoardRow* row = &get_unit_database()->rows[i];
            for (int j = 0; j < 0xb0; ++j)
                stream.transfer(row->cells[j]);
            close_chunk(chunk, stream);
        }
        for (int i = 0; i < 0x80; ++i) {
            open_chunk(chunk, stream, cells.lookup(i + 0x80));
            BoardRow_serialize_extra(&get_unit_database()->rows[i], &stream);
            close_chunk(chunk, stream);
        }
        open_chunk(chunk, stream, frame.lookup(1));
        UnitInfo* infos = unit_infos(get_unit_database());
        for (int i = 0; i < 500; ++i)
            UnitInfo_serialize(&infos[i], &stream);
        close_chunk(chunk, stream);
        open_chunk(chunk, stream, frame.lookup(2));
        unsigned char* pairs = reinterpret_cast<unsigned char*>(get_unit_database()) + 0xebd78;
        for (int i = 0; i < 0x80; ++i)
            RewardPair_serialize(pairs + i * 8, &stream);
        close_chunk(chunk, stream);
        open_chunk(chunk, stream, frame.lookup(3));
        short* second = reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(get_unit_database()) + 0xec240);
        for (int i = 0; i < 100; ++i) {
            stream.transfer(second[i - 100]);
            stream.transfer(second[i]);
        }
        close_chunk(chunk, stream);
        for (int i = 0; i < 0x80; ++i) {
            UnitDatabase* database = get_unit_database();
            Game* game = get_game();
            if (!database->rows[i].guards)
                game->players[stage].unguarded[i] = 1;
        }
    }
}

bool unit_is_leader(int player, int slot) {
    unsigned int index = get_unit_database()->rows[player].cells[static_cast<unsigned int>(slot)];
    return unit_infos(get_unit_database())[index].value8 == 1;
}

unsigned char cell_group_flag(int cell) {
    signed char group = get_unit_database()->rows[cell].group;
    if (group == -1)
        return 0;
    return gBoardQuery.groups[group / 2];
}

bool is_shop_kind(int kind) {
    switch (kind) {
    case 0:
    case 18:
    case 19:
    case 20:
    case 21:
    case 26:
    case 27:
    case 29:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
        return true;
    }
    return gBoardQuery.access == 1 || gBoardQuery.access == 2;
}

bool board_enabled() {
    return true;
}

bool board_side_quest() {
    Game* game = get_game();
    unsigned int mode = game_mode();
    if (game_mode() == 4)
        return game->players[mode].value2acd != 1;
    return false;
}

bool board_side_quest_open() {
    Game* game = get_game();
    unsigned int mode = game_mode();
    if (game_mode() == 4 && game->players[mode].value2acd != 1)
        return game->players[mode].value2acc < 7;
    return false;
}

TrackVec2 board_overflow() {
    TrackVec2 origin = gAdvBoard->start_position(0);
    unsigned int columns = 0;
    for (unsigned int x = 0; x != 0x400; x += 0x40)
        columns += origin.x + x + 32.0f < static_cast<float>(-(display_width() / 2));
    unsigned int rows = 0;
    for (int y = 0; y < 8; ++y)
        rows += origin.y - static_cast<float>(y * 44) + -22.0f >
                static_cast<float>(display_height() / 2 - 0x57);
    TrackVec2 result;
    result.x = columns;
    result.y = rows;
    return result;
}

static inline unsigned char count_down(unsigned char value) {
    unsigned int next = value - 1;
    return static_cast<unsigned char>(next) > value ? 0 : next;
}

void tick_side_quest() {
    Game* game = get_game();
    unsigned int mode = game_mode();
    if (game_mode() == 4 && game->players[mode].value2acd != 1) {
        unsigned char& delay = game->players[mode].value2acf;
        if (delay)
            delay = count_down(delay);
        else
            game->players[mode].value2acc = count_down(game->players[mode].value2acc);
    }
}

static inline bool seal_open(Unit* unit, PlayerMark& mark) {
    if (unit->rank == 5)
        return !(mark.flags & 0x800);
    if (unit->rank == 4)
        return !(mark.flags & 0x400);
    if (unit->rank == 3)
        return !(mark.flags & 0x200);
    return false;
}

void tick_seals() {
    UnitDatabase* database = get_unit_database();
    Game* game = get_game();
    unsigned int mode = game_mode();
    if (game_mode() != 5)
        return;
    unsigned char& timer = game->players[mode].value2acc;
    if (timer == 0xff) {
        for (long i = 0; i < 0x80; ++i) {
            int id = database->rows[i].value0;
            Unit* unit = get_unit_database()->unit(id);
            if (seal_open(unit, game->players[mode].marks[i])) {
                timer = 0;
                return;
            }
        }
        return;
    }
    unsigned int next = timer + 1;
    if (next >= 13) {
        timer = 12;
    } else {
        timer = next;
        if (static_cast<unsigned char>(next) < 12)
            return;
    }
    int cells[0x80];
    unsigned int count = 0;
    for (int i = 0; i < 0x80; ++i) {
        int id = database->rows[i].value0;
        Unit* unit = get_unit_database()->unit(id);
        if (seal_open(unit, game->players[mode].marks[i]))
            cells[count++] = i;
    }
    if (!count) {
        timer = 0xff;
        return;
    }
    int cell = cells[random_below(count)];
    int id = database->rows[cell].value0;
    Unit* unit = get_unit_database()->unit(id);
    if (unit->rank == 3)
        game->players[mode].marks[cell].flags |= 0x200;
    if (unit->rank == 4)
        game->players[mode].marks[cell].flags |= 0x400;
    if (unit->rank == 5)
        game->players[mode].marks[cell].flags |= 0x800;
    timer = count <= 1 ? 0xff : 0;
}

static inline int neighbor_direction(int cell, int neighbor) {
    for (unsigned int direction = 0; direction < 9; ++direction) {
        if (neighbor_cell(cell, direction) == neighbor)
            return direction;
    }
    return 9;
}

void reset_side_board() {
    Game* game = get_game();
    unsigned int mode = game_mode();
    if (game_mode() != 4)
        return;
    UnitDatabase* database = get_unit_database();
    Player& player = game->players[mode];
    for (long i = 0; i < 0x80; ++i) {
        BoardRow* row = &database->rows[static_cast<int>(i)];
        bool keep;
        if (row->kind == 0x16) {
            keep = player.cell_cleared(i);
        } else {
            keep = false;
            for (int d = 0; d < 4; ++d) {
                int neighbor = neighbor_cell(i, d);
                if (neighbor == i)
                    continue;
                unsigned char state = row->gate_state(neighbor_direction(i, neighbor), 0);
                if (database->rows[neighbor].kind != 0x16 || !player.cell_cleared(neighbor))
                    continue;
                if (state != 4 && state != 6) {
                    keep = true;
                    break;
                }
            }
        }
        if (!keep)
            player.cell_states[i] = 0;
        if (row->kind == 7 || row->kind == 1)
            player.cell_states[i] = 2;
        if (static_cast<short>(database->rows[i].value1e) == -1)
            player.cell_states[i] = 3;
        PlayerMark& mark = player.marks[i];
        if (mark.flags & 2) {
            unsigned int pair = database->rows[i].value2;
            UnitDatabase* units = get_unit_database();
            short item = reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(units) + 0xebd7c)[pair * 4];
            int level = get_item_table()->level_of(item);
            switch (level) {
            case 20:
            case 21:
            case 26:
            case 27:
                mark.flags &= ~2;
                break;
            }
        }
        if (mark.flags & 0x18)
            mark.flags &= ~0x18;
    }
    if (dlc_board_flag())
        player.cell_states[0x22] = 2;
    if (player.value2acd == 1)
        player.value2acd = 0;
    player.value2acc = 0x48;
    player.value2acf = 0;
}
