// Matching candidates for the Adventure Mode board queries 0x7100269858-0x710026b3c8.
// Player::setup (0x710026a98c) and BoardQuery::find_entry (0x710026b3cc) are at the end.
// Names are descriptive placeholders. Status: matching/README.md.

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

    unsigned char pad[0x3c];
};

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

struct UnitInfo {
    int kind : 16;            // +0: a bitfield, so the compare stays 32-bit
    int value2 : 16;          // +2
    unsigned char pad4[4];
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
    unsigned char pad14[2];
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
};
// Reached through the GOT slots at 0x7100c2a6f0 and 0x7100c23250.
extern BoardOverride gBoardOverride;
extern unsigned char gBoardRemapTable[];
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

    unsigned char pad[0x3d8];
    int levels[0x80][0x1c];   // +03d8
    int kinds[0x80][0x1c];    // +3bd8
    unsigned char flags[0x80][0x1c]; // +73d8
    unsigned int items[0x80][0x1c]; // +81d8
};

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
        return gBoardOverride.remap_kind(kind, gBoardRemapTable);
    }
    return kind;
}

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
