// Adventure Mode board units: the neighbour test with the unit tables (AdvUnit::can_move, 0x7100298094) and the
// map-link check (AdvUnit::can_warp, 0x7100298390). Their caller, the unit's movement choice at 0x7100294378, is
// in docs/s4_wip/294378.cpp. Names are descriptive placeholders.

class GameState {
public:
    unsigned char pad[0x1bb7c];
    unsigned int mode;        // +1bb7c
};

struct Player {
    unsigned char cell_cleared(int map);                                    // 0x710026b0d4

    int map;                  // +0000
    unsigned char pad4[0x2c34];
};
static_assert(sizeof(Player) == 0x2c38, "Player");

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

// A map's unit table (0x1e0 bytes).
struct MapUnits {
    unsigned char pad0[0xc];
    unsigned char warp;       // +0c: 0xff when the map has no link
    unsigned char padd[0x1d3];
};

class UnitDatabase {
public:
    unsigned char pad[0xdb610];
    MapUnits maps[0x80];      // +db610
};
UnitDatabase* get_unit_database();                                          // 0x710020ec80
unsigned char unit_is_leader(int map, int cell);                            // 0x710026cd2c

// The board state that owns the units.
class AdvBoardState {
public:
    unsigned char pad[0xd8];
    int links[0x80];          // +d8: the map each map's warp leads to
};

class AdvUnit {
public:
    unsigned char can_move(unsigned int from, unsigned int to);             // 0x7100298094
    unsigned char can_warp(int map);                                        // 0x7100298390

    AdvBoardState* board;     // +00
};

// The eight-neighbour test (16 cells to a row, 0xb0 cells). It returns unsigned char: as a bool the inlined
// result is tested differently.
static inline unsigned char adjacent(unsigned int from, unsigned int to) {
    if (from < 0xb0 && to < 0xb0) {
        int col = static_cast<int>(from) % 16;
        int f = from;
        int t = to;
        int up = f - 0x10;
        int up_lo = col != 0 ? f - 0x11 : up;
        int up_hi = col != 15 ? f - 0xf : up;
        int lo = f - (col != 0);
        int hi = col != 15 ? f + 1 : f;
        int down_lo = col != 0 ? f + 0xf : f + 0x10;
        int down_hi = col != 15 ? f + 0x11 : f + 0x10;
        if ((up_lo <= t && t <= up_hi) || (lo <= t && t <= hi) || (down_lo <= t && t <= down_hi))
            return true;
    }
    return false;
}

// 0x7100298094
unsigned char AdvUnit::can_move(unsigned int from, unsigned int to) {
    if (adjacent(from, to)) {
        Game* game = get_game();
        return unit_is_leader(game->players[game_mode()].map, to);
    }
    return false;
}

// 0x7100298390
unsigned char AdvUnit::can_warp(int map) {
    Game* game = get_game();
    Player& player = game->players[game_mode()];
    // Read unconditionally and replaced by the argument (a csel; testing the argument first sinks the load).
    int target = player.map;
    if (map != -1)
        target = map;
    if (get_unit_database()->maps[target].warp == 0xff)
        return false;
    int link = board->links[target];
    if (link == -1 || link == target)
        return false;
    return player.cell_cleared(target) || player.cell_cleared(link);
}
