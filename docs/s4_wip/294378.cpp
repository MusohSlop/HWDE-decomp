// 0x7100294378 AdvUnit::decide (12,092 B), fourth session, parked. Build: this file alone with try.py or
//   build/s4/adiff.py, --name _ZN7AdvUnit6decideEv and docs/s4_wip/294378.json (its .rodata 0x71007f8554 holds the
//   main 70-entry jump table and the nested switch's 10-entry one right after it). can_move (0x7100298094) and
//   can_warp (0x7100298390) from this file are matched in src/misc/s4_298094.cpp.
// State: 12,368 B, 1,080 instructions off with registers abstracted (branch targets counted). can_move is only
//   declared here: defined in the same file, LLVM stops passing this to it (it never reads it) while the original
//   passes this at every call, so can_move was in another unit. Cases 9/f/45, c/16/31, 20/3a/44, 25/30/3c,
//   26/3e/42, 1, 2, 3 and 4 now start within 0x20 bytes of the original's; from case 5 on ours drifts (case 18's
//   code lands at the end, +2ff4 against the original's +128c; 276 B more in all). What is right:
//   - the cell is an int (c - 1 with nsw lets the inlined neighbour tests fold for constant offsets; unsigned,
//     nothing folds and the function is 4.6 KB larger); the neighbour test is can_move's own helper (adjacent,
//     returning unsigned char), which already gives the original's code for step(c - 0x10, c - 0x20) in case 8;
//   - the "may go" test comes in two forms: pick(dir) (if (!ready()) return 4; return blocked() ? 4 : dir;),
//     whose select lets BranchFolding share the tails (the original's shared blocks at 297180, 29713c, 297244 and
//     296e8c), and go(dir) (if (ready() && !blocked()) return dir; return 4;), which keeps its own branches;
//     the choice per call site below comes from a greedy search (build/s4/pickgreedy.py) and is only a start;
//   - case 2: GameState* now = get_game()->state(); if (c == 0x25 && now->mode == 2 && map == 0x6c) gives the
//     original's separate c test, then the mode load and a cmp/ccmp pair, and a branch to a distant pick(3);
//   - case c/16/31 does its own left test and then continues in case 2's chain (goto right): the original keeps
//     both left tests and shares the rest in case 2's code. With two full chains (1,169) our tail merging keeps
//     case c's copy and sends case 2 into it; with case 2 falling through into case c's chain (1,079, 12,292 B)
//     there is one left test only. Moving whole cases around in the source changes nothing (same code).
// Still different: the order of the first neighbour test of a chain: the original tests the column first
//   ((c & 0xf) != 0) and then c and c - 1 against 0xb0 as separate branches; ours computes the two range tests as
//   an or, branches on the column, then on the or. Writing the left/right steps out (column first) did not help.
//   The calls to blocked are often in shared tails in ours where the original has them inline, and the reverse
//   (build/s4/callseq.py lists them). The original materializes case 2's 0x1bb7c offset before the c test (ours
//   after it). ready (0x7100297f34) is 2 off: the panel is loaded in the entry block (MachineSink then moves the
//   load and its address down but leaves the constants, as in the original); what remains is the index's zero
//   extension, which InstCombine places after the second get_unit_database call. blocked (0x7100298178, the same
//   load) is 46 off in its tail. The open() check converts the panel to a 64-bit index before its second call
//   (one instruction at each of about 30 sites); the first neighbour test of case 9 tests the column first.

// Adventure Mode: a board unit's movement choice (0x7100294378). By the unit's kind it tests the cells around it
// (the eight-neighbour test of can_move, the unit tables' passability and the panels' blocking byte) and returns
// the direction to move (0 down, 1 up, 2 right, 3 left, as the callers read it), 4 to stay or 5 when it cannot
// move. Names are descriptive placeholders.

class GameState {
public:
    unsigned char pad[0x1bb7c];
    unsigned int mode;        // +1bb7c
};

// One map's progress record (8 bytes).
struct MapProgress {
    unsigned char pad0[5];
    unsigned char flags;      // +5: bit 5 cleared
    unsigned char pad6[2];
};

struct Player {
    unsigned char cell_cleared(int map);                                    // 0x710026b0d4

    int map;                  // +0000
    unsigned char pad4[0x1fc];
    MapProgress progress[0x80]; // +0200
    unsigned char pad600[0x68];
    unsigned char forts[0x100]; // +0668
    unsigned char keeps[0x80]; // +0768
    unsigned char officers[0x300]; // +07e8
    unsigned char visited[0x80]; // +0ae8
    unsigned char padb68[0x2acc - 0xb68];
    unsigned char gate_count; // +2acc
    unsigned char gate_level; // +2acd
    unsigned char gate_bits;  // +2ace
    unsigned char pad2acf[0x2c38 - 0x2acf];
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
    unsigned char pad0[6];
    char flag6;               // +06
    unsigned char pad7[5];
    unsigned char warp;       // +0c: 0xff when the map has no link
    unsigned char padd[0xb];
    short dir;                // +18
    unsigned char pad1a[0xc];
    short cells[0xb0];        // +26: the panel on each cell
    unsigned char pad186[0x1e0 - 0x186];
};

// A panel's record (12 bytes).
struct PanelInfo {
    unsigned int type : 8;    // +0
    int kind : 8;             // +1
    unsigned int blocking : 8; // +2
    unsigned int flag3 : 8;   // +3
    unsigned char pad4[8];
};

class UnitDatabase {
public:
    const PanelInfo& panel(unsigned int id) const { return panels[id]; }

    unsigned char pad[0xdb610];
    MapUnits maps[0x80];      // +db610
    PanelInfo panels[1];      // +ea610
};
static_assert(__builtin_offsetof(UnitDatabase, panels) == 0xea610, "panels");
UnitDatabase* get_unit_database();                                          // 0x710020ec80
unsigned char unit_is_leader(int map, int cell);                            // 0x710026cd2c
int unit_frame(int map, int cell);                                          // 0x710026c730
int unit_kind(int map, int cell);                                           // 0x7100269cfc
unsigned char is_fort_kind(int kind);                                       // 0x710026a014
unsigned char is_officer_kind(int kind);                                    // 0x7100269fa0
unsigned char is_keep_kind(int kind);                                       // 0x7100269fd8
unsigned char is_gate_kind(int kind);                                       // 0x710026a080

// The board state that owns the units.
class AdvBoardState {
public:
    unsigned char pad[0xd8];
    int links[0x80];          // +d8: the map each map's warp leads to
    unsigned char pad2d8[0xb9dc - 0x2d8];
    int target;               // +b9dc
    unsigned char padb9e0[4];
    int lane;                 // +b9e4
};

class AdvUnit {
public:
    int decide();                                                           // 0x7100294378
    unsigned char ready();                                                  // 0x7100297f34
    unsigned char can_move(unsigned int from, unsigned int to);             // 0x7100298094
    unsigned char blocked();                                                // 0x7100298178
    unsigned char can_warp(int map);                                        // 0x7100298390

    // The direction if the unit may go now, otherwise stay.
    int pick(int dir) {
        if (!ready())
            return 4;
        return blocked() ? 4 : dir;
    }

    // The same test written as one condition (the direction and the stay take separate returns).
    int go(int dir) {
        if (ready() && !blocked())
            return dir;
        return 4;
    }

    AdvBoardState* board;     // +00
    unsigned char pad8[0x14];
    int kind;                 // +1c
    unsigned char pad20[0x28];
    unsigned int cell;        // +48
};

// The eight-neighbour test can_move makes before it asks the unit tables (16 cells to a row, 0xb0 cells).
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
// The cell's panel does not block.
static inline bool open(unsigned int cell) {
    Game* game = get_game();
    int map = game->players[game_mode()].map;
    unsigned long panel = static_cast<unsigned int>(get_unit_database()->maps[map].cells[cell]);
    return get_unit_database()->panels[panel].blocking == 0;
}

static inline bool step(unsigned int from, unsigned int to) {
    return adjacent(from, to) && open(to);
}

// 0x7100294378
int AdvUnit::decide() {
    Game* game = get_game();
    unsigned int mode = game_mode();
    int map = game->players[mode].map;
    int c = cell;
    if (game_mode() == 8) {
        int lane = board->lane;
        if (lane != 0) {
            unsigned char left = can_move(c, c - 1);
            if (lane == 1) {
                if (left)
                    return 3;
            } else if (left && can_move(c - 1, c - 2)) {
                return 3;
            }
            return 2;
        }
    }
    switch (kind) {
    case 9:
    case 0xf:
    case 0x45:
        if ((c & 0xf) != 0) {
            if (adjacent(c, c - 1) && adjacent(c - 1, c - 2) && can_move(c - 2, c - 3))
                return go(3);
        }
        if (c % 16 != 15) {
            if (adjacent(c, c + 1) && adjacent(c + 1, c + 2) && can_move(c + 2, c + 3))
                return go(2);
        }
        if (adjacent(c, c - 0x10) && adjacent(c - 0x10, c - 0x20) && can_move(c - 0x20, c - 0x30))
            return go(1);
        if (adjacent(c, c + 0x10) && adjacent(c + 0x10, c + 0x20) && can_move(c + 0x20, c + 0x30))
            return go(0);
        return kind == 0x45 ? 4 : 5;
    case 0xc:
    case 0x16:
    case 0x31:
        if (can_move(c, c - 1) && can_move(c - 1, c - 2))
            return pick(3);
        goto right;  // the original's layout: this group's own left test, then case 2's chain
    case 0x20:
    case 0x3a:
    case 0x44:
        if ((can_move(c, c - 1) && can_move(c - 1, c - 2) && can_move(c - 2, c - 3)) || open(c))
            return pick(3);
        if ((can_move(c, c + 1) && can_move(c + 1, c + 2) && can_move(c + 2, c + 3)) || open(c))
            return pick(2);
        if ((can_move(c, c - 0x10) && can_move(c - 0x10, c - 0x20) && can_move(c - 0x20, c - 0x30)) || open(c))
            return pick(1);
        if ((can_move(c, c + 0x10) && can_move(c + 0x10, c + 0x20) && can_move(c + 0x20, c + 0x30)) || open(c))
            return pick(0);
        return kind == 0x44 ? 4 : 5;
    case 0x25:
    case 0x30:
    case 0x3c:
        if (can_move(c, c - 1))
            return pick(3);
        if (can_move(c, c + 1))
            return pick(2);
        return kind == 0x3c ? 4 : 5;
    case 0x26:
    case 0x3e:
    case 0x42:
        if (can_move(c, c - 1))
            return pick(3);
        if (can_move(c, c + 1))
            return pick(2);
        return (kind == 0x3e || kind == 0x42) ? 4 : 5;
    case 1:
        if (game_mode() == 2 && ((map == 0x18 && c == 0x3b) || (map == 0x19 && c == 0x34)))
            return pick(0);
        if (game_mode() < 3) {
            if (can_move(c, c - 1))
                return pick(3);
            if (can_move(c, c + 1))
                return pick(2);
            if (can_move(c, c - 0x10))
                return pick(1);
            if (can_move(c, c + 0x10))
                return pick(0);
            return 5;
        }
        if (can_move(c, c - 1) && can_move(c - 1, c - 2))
            return pick(3);
        if (can_move(c, c + 1) && can_move(c + 1, c + 2))
            return pick(2);
        if (can_move(c, c - 0x10) && can_move(c - 0x10, c - 0x20))
            return go(1);
        if (can_move(c, c + 0x10) && can_move(c + 0x10, c + 0x20))
            return pick(0);
        return game_mode() == 9 ? 4 : 5;
    case 2: {
        GameState* now = get_game()->state();
        if (c == 0x25 && now->mode == 2 && map == 0x6c)
            return pick(3);
    }
        if (can_move(c, c - 1) && can_move(c - 1, c - 2))
            return pick(3);
    right:
        if (can_move(c, c + 1) && can_move(c + 1, c + 2))
            return pick(2);
        if (can_move(c, c - 0x10) && can_move(c - 0x10, c - 0x20))
            return pick(1);
        if (can_move(c, c + 0x10) && can_move(c + 0x10, c + 0x20))
            return pick(0);
        return 5;
    case 3:
        if (!can_move(c, c))
            return 5;
        return go(3);
    case 4: {
        short dir = get_unit_database()->maps[map].dir;
        if (ready() && !blocked() && static_cast<unsigned short>(dir) < 4)
            return dir;
        if (can_move(c, c - 0x10) && can_move(c, c + 0x10))
            return pick(1);
        if (!can_move(c, c - 1))
            return 4;
        if (can_move(c, c + 1))
            return go(3);
        return 4;
    }
    case 5:
        if ((!ready() || blocked()) && !open(c))
            return 5;
        if (adjacent(c, c - 1) && can_move(c - 1, c - 2))
            return pick(3);
        if (adjacent(c, c + 1) && can_move(c + 1, c + 2))
            return pick(2);
        return 5;
    case 6:
        if (can_move(c, c - 0x10))
            return pick(1);
        if (can_move(c, c + 0x10))
            return pick(0);
        return 5;
    case 7:
        if (can_move(c, c - 1) && can_move(c - 1, c - 2) && can_move(c - 2, c - 3))
            return pick(3);
        if (can_move(c, c + 1) && can_move(c + 1, c + 2) && can_move(c + 2, c + 3))
            return pick(2);
        if (can_move(c, c - 0x10) && can_move(c - 0x10, c - 0x20) && can_move(c - 0x20, c - 0x30))
            return pick(1);
        if (can_move(c, c + 0x10) && can_move(c + 0x10, c + 0x20) && can_move(c + 0x20, c + 0x30))
            return pick(0);
        return 5;
    case 8:
        if (!can_move(c, c))
            return 5;
        if (step(c, c - 0x10) && step(c - 0x10, c - 0x20))
            return pick(0);
        if (step(c, c + 0x10) && step(c + 0x10, c + 0x20))
            return go(1);
        if (step(c, c - 1) && step(c - 1, c - 2))
            return pick(2);
        if (step(c, c + 1) && step(c + 1, c + 2))
            return pick(3);
        return 5;
    case 0xa:
        if (!ready() || blocked())
            return can_move(c, c) ? 4 : 5;
        return adjacent(c, c - 0x10) ? 1 : 5;
    case 0xb:
        if (!ready() || blocked())
            return can_move(c, c) ? 4 : 5;
        if (can_move(c, c - 1) && can_move(c - 1, c - 2))
            return 3;
        if (can_move(c, c + 1) && can_move(c + 1, c + 2))
            return 2;
        if (can_move(c, c - 0x10) && can_move(c - 0x10, c - 0x20))
            return 1;
        if (can_move(c, c + 0x10) && can_move(c + 0x10, c + 0x20))
            return 0;
        return 5;
    case 0xd:
        if (can_move(c, c - 1))
            return go(3);
        if (can_move(c, c + 1))
            return pick(2);
        return 5;
    case 0xe:
        if ((!ready() || blocked()) && !open(c))
            return 5;
        if (adjacent(c, c - 1) && can_move(c - 1, c - 2))
            return pick(3);
        if (adjacent(c, c + 1) && can_move(c + 1, c + 2))
            return pick(2);
        return 5;
    case 0x10:
        return go(1);
    case 0x11:
        if (unit_frame(map, c) != 0xd2)
            return 4;
        return pick(1);
    case 0x17:
        return go(static_cast<int>(c) % 16 > 8 ? 3 : 2);
    case 0x18:
        return pick(1);
    case 0x19:
        return pick(static_cast<int>(c) % 16 < 9 ? 3 : 2);
    case 0x1c: {
        int target = board->target;
        if (target != -1 && (game->players[mode].gate_bits & (1 << target)) == 0)
            return 0;
        return 5;
    }
    case 0x1e:
        if (game_mode() == 8) {
            int frame = unit_frame(map, c);
            if (static_cast<unsigned int>(frame - 0xd5) < 2) {
                if (adjacent(c, c - 1) && adjacent(c - 1, c - 2) && adjacent(c - 2, c - 3) && open(c - 3))
                    return pick(3);
                if (adjacent(c, c + 1) && adjacent(c + 1, c + 2) && adjacent(c + 2, c + 3) && open(c + 3))
                    return pick(2);
                if (adjacent(c, c - 1) && adjacent(c - 1, c - 2) && can_move(c - 2, c - 3) && !open(c - 3))
                    return pick(3);
                if (adjacent(c, c + 1) && adjacent(c + 1, c + 2) && can_move(c + 2, c + 3) && !open(c + 3))
                    return pick(2);
                return 5;
            }
            if (adjacent(c, c - 1) && adjacent(c - 1, c - 2) && can_move(c - 2, c - 3) && !open(c - 3))
                return pick(3);
            if (adjacent(c, c + 1) && adjacent(c + 1, c + 2) && can_move(c + 2, c + 3) && !open(c + 3))
                return pick(2);
            if (adjacent(c, c - 1) && adjacent(c - 1, c - 2) && adjacent(c - 2, c - 3) && open(c - 3))
                return pick(3);
            if (adjacent(c, c + 1) && adjacent(c + 1, c + 2) && adjacent(c + 2, c + 3) && open(c + 3))
                return pick(2);
            return 5;
        }
        if (can_move(c, c - 1) || open(c))
            return pick(3);
        if (can_move(c, c + 1) || open(c))
            return pick(2);
        return 5;
    case 0x1f:
        if (can_move(c, c - 1) || open(c))
            return go(3);
        if (can_move(c, c + 1) || open(c))
            return pick(2);
        return 5;
    case 0x21:
        if (can_move(c, c - 1) || open(c))
            return go(3);
        if (can_move(c, c + 1) || open(c))
            return pick(2);
        return 5;
    case 0x22:
        return pick(static_cast<int>(c) % 16 > 8 ? 3 : 2);
    case 0x23:
        if (can_move(c, c - 1))
            return pick(3);
        if (can_move(c, c + 1))
            return pick(2);
        return 5;
    case 0x24:
        if (can_move(c, c - 1) || open(c))
            return pick(3);
        if (can_move(c, c + 1) || open(c))
            return pick(2);
        return 5;
    default:
        if (static_cast<unsigned int>(kind - 0x27) < 8) {
            Player& player = game->players[mode];
            if (player.gate_count != 0 && player.gate_level < 8 && (player.progress[map].flags >> 5 & 1) == 0)
                return 4;
            return 0;
        }
        if (kind == 0x2f) {
            if (can_move(c, c + 0x10) && can_move(c + 0x10, c + 0x20))
                return pick(1);
            if (can_move(c, c - 1))
                return pick(2);
            if (can_move(c, c + 1))
                return pick(3);
            if (can_move(c, c - 0x10))
                return pick(0);
            return 5;
        }
        if (static_cast<unsigned int>(kind - 0x32) < 6)
            return 0;
        switch (kind) {
        case 0x38:
            if (!ready() || blocked())
                return 4;
            return get_unit_database()->maps[map].flag6 == 0 ? 3 : 2;
        case 0x39:
            if (can_move(c, c + 0x10) && can_move(c + 0x10, c + 0x20))
                return pick(0);
            if (can_move(c, c - 1) && can_move(c - 1, c - 2))
                return pick(3);
            if (can_move(c, c + 1) && can_move(c + 1, c + 2))
                return go(2);
            if (!can_move(c, c - 0x10) || !can_move(c - 0x10, c - 0x20))
                return 5;
            return pick(1);
        default:
            return 5;
        case 0x3b:
            if (!can_warp(-1))
                return 4;
            if (adjacent(c, c - 1) && can_move(c - 1, c - 2))
                return pick(3);
            if (adjacent(c, c + 1) && can_move(c + 1, c + 2))
                return pick(2);
            return pick(5);
        case 0x3d:
        case 0x3f:
        case 0x41:
            if ((can_move(c, c - 1) && can_move(c - 1, c - 2) && can_move(c - 2, c - 3)) || open(c))
                return go(3);
            if ((can_move(c, c + 1) && can_move(c + 1, c + 2) && can_move(c + 2, c + 3)) || open(c))
                return pick(2);
            if (!can_move(c, c - 0x10))
                return 4;
            if (can_move(c - 0x10, c - 0x20) && can_move(c - 0x20, c - 0x30) && pick(1) == 1 && kind == 0x41)
                return 1;
            return 4;
        case 0x40:
            if (adjacent(c, c - 1) && can_move(c - 1, c - 2))
                return pick(3);
            if (adjacent(c, c + 1) && can_move(c + 1, c + 2))
                return pick(2);
            return 4;
        }
        return 4;
    case 0x43:
        if (can_move(c - 3, c - 4) || open(c))
            return pick(3);
        if (can_move(c + 3, c + 4) || open(c))
            return pick(2);
        return 4;
    case 0:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x1a:
    case 0x1b:
    case 0x1d:
        return 0;
    }
}


// 0x7100297f34
unsigned char AdvUnit::ready() {
    Game* game = get_game();
    int map = game->players[game_mode()].map;
    unsigned int c = cell;
    int k = kind;
    unit_kind(map, c);
    unsigned int p = get_unit_database()->maps[map].cells[c];
    if (k < 0)
        return false;
    if (static_cast<unsigned int>(board->lane - 1) < 2)
        return true;
    if (k == 0)
        return true;
    if (k == 0x1c)
        return true;
    if (k == get_unit_database()->panel(p).kind && get_unit_database()->panel(p).flag3 != 1)
        return true;
    return false;
}// 0x7100298178
unsigned char AdvUnit::blocked() {
    Game* game = get_game();
    unsigned int mode = game_mode();
    unsigned int c = cell;
    int map = game->players[mode].map;
    int k = kind;
    unit_kind(map, c);
    unsigned int p = get_unit_database()->maps[map].cells[c];
    if (k < 0)
        return false;
    Player& player = game->players[mode];
    if (k == 0)
        return player.visited[map] != 0;
    if (k != get_unit_database()->panel(p).kind)
        return false;
    if (get_unit_database()->panel(p).flag3 == 1)
        return false;
    if (is_fort_kind(k) && !player.forts[map])
        return false;
    if (is_officer_kind(k) && !player.officers[map])
        return false;
    if (is_keep_kind(k) && !player.keeps[map])
        return false;
    if (is_gate_kind(k) && (k == 0x11 || k == 0x3b))
        return false;
    switch (k) {
    case 0x1e:
        return !(player.progress[map].flags & 4);
    case 0x1f:
        return !(player.progress[map].flags & 2);
    case 0x20:
        return !(player.progress[map].flags & 8);
    }
    return true;
}// 0x7100298390
unsigned char AdvUnit::can_warp(int map) {
    Game* game = get_game();
    Player& player = game->players[game_mode()];
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