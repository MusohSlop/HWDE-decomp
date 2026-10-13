// Matching candidates for the Adventure Mode board queries 0x7100269858-0x710026a908.
// Names are descriptive placeholders. Status: matching/README.md.

class ItemTable {
public:
    unsigned char contains(unsigned int item);                              // 0x71001ff2c8
    int weapon_of(unsigned int item);                                       // 0x71001ff1c4
    unsigned char is_special(unsigned int item);                            // 0x71001ff2a4
    int level_of(int item);                                                 // 0x71001ff218
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

struct PlayerMark {
    int flags;                // +0: bit 1 item held
    int value;                // +4
};

struct Player {
    bool cell_open(int cell);                                               // 0x710026a90c
    int cell_state(unsigned int cell) { return cell_states[cell]; }

    int id;                   // +0000
    int cell_states[0x80];    // +0004
    PlayerMark marks[0xdc];   // +0204: indexed by board owner
    unsigned char pad8e4[4];
    int gate_levels[0x50];    // +08e8
    unsigned char pad[0x20a0];
    int value2ac8;            // +2ac8
    unsigned char pad2acc;
    unsigned char value2acd;  // +2acd
    unsigned char pad2ace[4];
    unsigned char value2ad2;  // +2ad2
    unsigned char pad2ad3[0x165];
};
static_assert(sizeof(Player) == 0x2c38, "player size");

class Progress {
public:
    unsigned char has(int content);                                         // 0x7100203180

    unsigned char pad[0x14c];
};

class Game {
public:
    GameState* state();                                                     // 0x7100204c10
    int unit_count(unsigned int mode, int slot, unsigned char flag);        // 0x7100203970

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

// One player's board (0x1e0 bytes).
struct BoardRow {
    unsigned char gate_state(int gate, unsigned char raw);                  // 0x710026a220

    unsigned char pad0[8];
    signed char gates[4];     // +08
    signed char owner;        // +0c
    unsigned char padd[5];
    unsigned char kind;       // +12
    signed char level;        // +13
    unsigned char pad14[0x12];
    short item;               // +26
    unsigned char pad28[6];
    short cells[0xd9];        // +2e: unit index of each board cell
};
static_assert(sizeof(BoardRow) == 0x1e0, "board row size");

class UnitDatabase {
public:
    unsigned char pad[0xdb608];
    BoardRow rows[1];         // +db608
};
UnitDatabase* get_unit_database();                                          // 0x710020ec80

static inline UnitInfo* unit_infos(UnitDatabase* database) {
    return reinterpret_cast<UnitInfo*>(reinterpret_cast<unsigned char*>(database) + 0xea608);
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
