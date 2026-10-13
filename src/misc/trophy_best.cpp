// "Is this the best slot" queries found by tools/family_scan.py --immediates: each takes a
// trophy record from the game, finds the slot (0-19) with the highest rating and tests whether
// it is a given slot. They differ only in that slot; functions are named after their address.
// Status: matching/README.md.

struct TrophyStats;
struct TrophyRecord;
class Game {
public:
    TrophyRecord* trophy(unsigned int id);                                  // 0x71002042bc
};
Game* get_game();                                                           // 0x7100204728
TrophyStats* trophy_stats(TrophyRecord* record);                            // 0x71002885d4
unsigned char trophy_rating(TrophyStats* stats, int slot);                  // 0x710020639c

static inline unsigned char best_slot(unsigned int id) {
    TrophyRecord* record = get_game()->trophy(id);
    int best = 0;
    for (int slot = 1; slot < 20; ++slot) {
        unsigned char rating = trophy_rating(trophy_stats(record), slot);
        if (rating > trophy_rating(trophy_stats(record), best))
            best = slot;
    }
    return best;
}

// 0x7100207d3c: slot 1
bool best_slot_is_207d3c(unsigned int id) {
    return best_slot(id) == 1;
}

// 0x7100207dbc: slot 2
bool best_slot_is_207dbc(unsigned int id) {
    return best_slot(id) == 2;
}

// 0x7100207e3c: slot 3
bool best_slot_is_207e3c(unsigned int id) {
    return best_slot(id) == 3;
}

// 0x7100207ebc: slot 4
bool best_slot_is_207ebc(unsigned int id) {
    return best_slot(id) == 4;
}

// 0x7100207f3c: slot 5
bool best_slot_is_207f3c(unsigned int id) {
    return best_slot(id) == 5;
}

// 0x7100207fbc: slot 6
bool best_slot_is_207fbc(unsigned int id) {
    return best_slot(id) == 6;
}

// 0x710020803c: slot 7
bool best_slot_is_20803c(unsigned int id) {
    return best_slot(id) == 7;
}

// 0x71002080bc: slot 8
bool best_slot_is_2080bc(unsigned int id) {
    return best_slot(id) == 8;
}

// 0x710020813c: slot 9
bool best_slot_is_20813c(unsigned int id) {
    return best_slot(id) == 9;
}

// 0x71002081bc: slot 10
bool best_slot_is_2081bc(unsigned int id) {
    return best_slot(id) == 10;
}

// 0x710020823c: slot 11
bool best_slot_is_20823c(unsigned int id) {
    return best_slot(id) == 11;
}

// 0x71002082bc: slot 12
bool best_slot_is_2082bc(unsigned int id) {
    return best_slot(id) == 12;
}

// 0x710020833c: slot 13
bool best_slot_is_20833c(unsigned int id) {
    return best_slot(id) == 13;
}

// 0x71002083bc: slot 14
bool best_slot_is_2083bc(unsigned int id) {
    return best_slot(id) == 14;
}

// 0x710020843c: slot 15
bool best_slot_is_20843c(unsigned int id) {
    return best_slot(id) == 15;
}

// 0x71002084bc: slot 16
bool best_slot_is_2084bc(unsigned int id) {
    return best_slot(id) == 16;
}

// 0x710020853c: slot 17
bool best_slot_is_20853c(unsigned int id) {
    return best_slot(id) == 17;
}

// 0x71002085bc: slot 18
bool best_slot_is_2085bc(unsigned int id) {
    return best_slot(id) == 18;
}

// 0x710020863c: slot 19
bool best_slot_is_20863c(unsigned int id) {
    return best_slot(id) == 19;
}
