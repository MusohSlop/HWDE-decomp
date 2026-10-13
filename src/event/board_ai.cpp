// Matching candidate for the Adventure board's computer-player target choice (0x71002709e0).
// Names are descriptive placeholders. Status: matching/README.md.

static inline float fabsf_(float value) { return __builtin_fabsf(value); }

// Cell position; its user-provided copy makes a row copy move the table element by element.
struct CellPos {
    CellPos(const CellPos& other) {
        int ox = other.x;
        int oy = other.y;
        x = ox;
        y = oy;
    }

    int x;
    int y;
};

class BoardRow {
public:
    unsigned char gate_state(int side, unsigned char raw);                   // 0x710026a220

    unsigned char value0[2];
    short reward;             // +02
    unsigned char pad04[0xe];
    unsigned char kind;       // +12
    unsigned char pad13[0x17b];
    CellPos positions[10];    // +190
};
static_assert(sizeof(BoardRow) == 0x1e0, "row size");

struct RewardPair {
    short value0;
    short item;               // +02
    unsigned char pad[4];
};

struct UnitDatabase {
    unsigned char pad[0xdb608];
    BoardRow rows[0x80];      // +db608
    unsigned char padea608[0x1772];
    RewardPair rewards[1];    // +ebd7a
};

// One player's slot in the game object (0x2c38 apart; its later fields run past the stride).
struct GameSlot {
    unsigned char pad[0x2944];
    int home;                 // +2944
    int cells[0x180];         // +2948
    unsigned char held[0xe4]; // +2f48
    unsigned char targets[0x2288]; // +302c
    int pattern;              // +52b4
};

class GameState {
public:
    unsigned char pad[0x1bb7c];
    unsigned int mode;        // +1bb7c
};

class Game {
public:
    GameState* state();                                                     // 0x7100204c10

    unsigned char pad[0x1e374];
    unsigned int active_mode; // +1e374
};

class ItemTable {
public:
    int level_of(int item);                                                 // 0x71001ff218
};

struct BattleParams {
    unsigned char pad[0x6c];
    int tag;                  // +6c
};

struct Player;

Game* get_game();                                                           // 0x7100204728
UnitDatabase* get_unit_database();                                          // 0x710020ec80
ItemTable* get_item_table();                                                // 0x71001ff050
BattleParams* get_battle_params();                                          // 0x71001a8c38
unsigned int held_kind(int level, int cell);                                // 0x7100269de0
unsigned char dlc_unit_unlocked(BoardRow* row);                             // 0x710026a7e0
unsigned char cell_available(int cell, Player* player, int* count, unsigned char a,
                             unsigned char b, int c);                       // 0x7100271894
int random_below(int limit);                                                // 0x7100459bd8

struct Distances {
    float value[3];
};
// FLT_MAX three times (0x71007f6740).
extern const Distances kFarDistances __attribute__((visibility("hidden")));

static inline GameSlot* slot_of(Game* game, unsigned long mode) {
    return reinterpret_cast<GameSlot*>(reinterpret_cast<unsigned char*>(game) + mode * 0x2c38);
}

static inline bool cell_unlocked(int cell) {
    UnitDatabase* db = get_unit_database();
    return static_cast<unsigned int>(db->rows[cell].kind - 0x17) > 3 ||
           dlc_unit_unlocked(&db->rows[cell]);
}

static inline bool row_blocked(BoardRow& row, int side) {
    return row.gate_state(side, 0) == 4 || row.gate_state(side, 0) == 6;
}

unsigned char choose_board_target(Player* player, unsigned char a, unsigned char b, int c);

// 0x71002709e0
unsigned char choose_board_target(Player* player, unsigned char a, unsigned char b, int c) {
    UnitDatabase* db = get_unit_database();
    Game* game = get_game();
    unsigned int mode = get_game()->state()->mode;
    GameSlot* slot = slot_of(game, mode);
    BoardRow home_row = db->rows[slot->home];
    BattleParams* params = get_battle_params();
    unsigned int home = slot->home;
    unsigned int home_x = home & 0xf;
    unsigned int home_y = home >> 4;
    float home_yf = home_y;
    float home_xf = home_x;
    int best_cell[3] = {-1, -1, -1};
    Distances best_dist = kFarDistances;
    float best_open_dist = 3.40282347e+38f;
    float best_any_dist = 3.40282347e+38f;
    int best_open = -1;
    int best_any = -1;
    int* pattern = &slot->pattern;
    int count = 0;
    for (int x = 0; x < 16; ++x) {
        float dx = x - home_xf;
        int offset_x = x - home_x;
        bool left_side = static_cast<unsigned int>(x) <= home_x;
        bool right_side = static_cast<unsigned int>(x) >= home_x;
        for (int y = 0; y < 8; ++y) {
            int cell = x + y * 16;
            if (!cell_available(cell, player, &count, a, b, c))
                continue;
            short reward = db->rows[cell].reward;
            bool wanted = b != 0;
            UnitDatabase* units = get_unit_database();
            ItemTable* items = get_item_table();
            unsigned int held = held_kind(
                items->level_of(units->rewards[static_cast<unsigned int>(reward)].item), cell);
            Game* current = get_game();
            bool skip = wanted & (slot_of(current, current->active_mode)->held[held] == 0);
            if (!skip) {
                if (static_cast<unsigned int>(x) < home_x && row_blocked(home_row, 1))
                    continue;
                if (static_cast<unsigned int>(x) > home_x && row_blocked(home_row, 2))
                    continue;
                if (static_cast<unsigned int>(y) < home_y &&
                    (row_blocked(home_row, 3) || row_blocked(home_row, 0)))
                    continue;
            }
            float dist = fabsf_(y - home_yf) + fabsf_(dx);
            int here = x + y * 16;
            if (cell_unlocked(cell) && slot->cells[cell] >= 2) {
                bool full = cell_unlocked(cell) && slot->cells[cell] == 3;
                if ((a || !full) && dist < best_open_dist) {
                    best_open_dist = dist;
                    best_open = cell;
                }
            } else if (dist < best_any_dist) {
                best_any_dist = dist;
                best_any = cell;
            }
            int down = cell < 0x70 ? here + 16 : cell;
            int up = cell > 0xf ? cell - 16 : cell;
            int right = cell % 16 != 15 ? cell + 1 : cell;
            int left = cell - ((cell & 0xf) != 0);
            bool found = false;
            for (int side = 0; side < 4; ++side) {
                int next = cell;
                switch (side) {
                case 0:
                    next = up;
                    break;
                case 1:
                    next = left;
                    break;
                case 2:
                    next = right;
                    break;
                case 3:
                    next = down;
                    break;
                }
                if (cell_unlocked(next) && slot->cells[next] == 3)
                    goto chosen;
                {
                    int next_down = next < 0x70 ? next + 16 : next;
                    int next_up = next > 0xf ? next - 16 : next;
                    int next_right = next % 16 != 15 ? next + 1 : next;
                    int next_left = next - ((next & 0xf) != 0);
                    if ((cell_unlocked(next_up) && slot->cells[next_up] == 3) ||
                        (cell_unlocked(next_left) && slot->cells[next_left] == 3) ||
                        (cell_unlocked(next_right) && slot->cells[next_right] == 3) ||
                        (cell_unlocked(next_down) && slot->cells[next_down] == 3))
                        found = true;
                }
            }
            if (!found)
                continue;
        chosen:
            {
                int offset = x;
                bool toward = false;
                switch (*pattern) {
                case 0:
                    toward = static_cast<unsigned int>(y) <= home_y;
                    offset = offset_x;
                    break;
                case 1:
                    toward = left_side;
                    offset = y - home_y;
                    break;
                case 2:
                    toward = right_side;
                    offset = y - home_y;
                    break;
                case 3:
                    toward = static_cast<unsigned int>(y) >= home_y;
                    offset = offset_x;
                    break;
                }
                if (skip || toward) {
                    int index = offset + 1;
                    if (static_cast<unsigned int>(index) <= 2 &&
                        (skip || dist < best_dist.value[index])) {
                        best_cell[index] = cell;
                        best_dist.value[index] = dist;
                        if (skip)
                            break;
                    }
                }
            }
        }
    }
    int chance;
    switch (params->tag) {
    case 0:
        chance = 20;
        break;
    case 1:
        chance = 40;
        break;
    case 2:
        chance = 70;
        break;
    case 3:
        chance = 100;
        break;
    default:
        chance = 0;
        break;
    }
    int first = best_cell[0];
    int second = best_cell[1];
    int third = best_cell[2];
    int pick;
    float pick_dist;
    if (first == -1) {
        pick_dist = 3.40282347e+38f;
        pick = -1;
    } else {
        pick_dist = best_dist.value[0];
        if (pick_dist < 3.40282347e+38f &&
            !(cell_unlocked(first) && slot->cells[first] > 1)) {
            pick = first;
        } else {
            pick = -1;
            pick_dist = 3.40282347e+38f;
        }
    }
    if (second != -1 && best_dist.value[1] < pick_dist &&
        !(cell_unlocked(second) && slot->cells[second] > 1)) {
        pick_dist = best_dist.value[1];
        pick = second;
    }
    if (third != -1 && best_dist.value[2] < pick_dist &&
        !(cell_unlocked(third) && slot->cells[third] >= 2)) {
        pick = third;
    } else if (pick == -1) {
        int fallback;
        if (first != -1 && best_dist.value[0] < pick_dist) {
            pick_dist = best_dist.value[0];
            fallback = first;
        } else {
            fallback = -1;
        }
        if (second != -1 && best_dist.value[1] < pick_dist) {
            pick_dist = best_dist.value[1];
            fallback = second;
        }
        if (third != -1 && best_dist.value[2] < pick_dist)
            fallback = third;
        pick = fallback;
        if (pick == -1) {
            int roll = random_below(100);
            int target;
            if (best_open != -1 && roll <= chance)
                target = best_open;
            else if (best_any != -1)
                target = best_any;
            else
                return 0;
            slot_of(game, mode)->targets[target] = 1;
            return 1;
        }
    }
    BoardRow* row = &db->rows[pick];
    int left = pick - ((pick & 0xf) != 0);
    int up = pick > 0xf ? pick - 16 : pick;
    int right = pick % 16 != 15 ? pick + 1 : pick;
    int other = -1;
    if (!(cell_unlocked(up) && slot->cells[up] > 1) && row->gate_state(0, 0) != 4 &&
        row->gate_state(0, 0) != 6)
        other = cell_available(up, player, nullptr, a, b, c) ? up : -1;
    if (!(cell_unlocked(left) && slot->cells[left] > 1) && row->gate_state(1, 0) != 4 &&
        row->gate_state(1, 0) != 6 && cell_available(left, player, nullptr, a, b, c))
        other = left;
    if (!(cell_unlocked(right) && slot->cells[right] > 1) && row->gate_state(2, 0) != 4 &&
        row->gate_state(2, 0) != 6 && cell_available(right, player, nullptr, a, b, c))
        other = right;
    if (other != -1 && random_below(2))
        slot_of(game, mode)->targets[other] = 1;
    else
        slot_of(game, mode)->targets[pick] = 1;
    return 1;
}
