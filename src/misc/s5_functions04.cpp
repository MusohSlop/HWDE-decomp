// The trophy checker's update (fifth session): for every trophy marked pending and not yet earned and reported,
// test its condition (a play statistic, a count over stages, maps, units or items, or one of the per-trophy
// checks next to it at 0x710045e160-0x710045efc0) and unlock it; trophy 12 is checked twice, as in the original.
// Every loop is its own inline function, as in the original: written in the caller, the get_game() call that
// starts the loop body and the one that starts the unlock are hoisted out of the loop. Struct, field and callee
// names are placeholders after the address and offset, as in the generated units. Status: matching/README.md.

struct Stats45f07c {
    unsigned long stat_2028b4(unsigned int id);                       // 0x71002028b4
};

struct Board45f07c {
    unsigned char cleared_26b0d4(int cell);                           // 0x710026b0d4
};

struct Map45f07c {
    Board45f07c board;                // +0
    unsigned char pad1[0x8e7];
    int states[128];                  // +8e8
    unsigned char pad_ae8[0x2150];
};

struct Game45f07c {
    unsigned char pad0[0x27f8];
    Stats45f07c stats;                // +27f8
    unsigned char pad27f9[0x14b];
    Board45f07c board;                // +2944
    unsigned char pad2945[0x8e7];
    int ranks[128];                   // +322c
    unsigned char pad342c[0x4d88];
    Map45f07c maps[8];                // +81b4

    unsigned char earned_203dfc(int id);                              // 0x7100203dfc
    unsigned char reported_203d0c(int id);                            // 0x7100203d0c
    void set_earned_203e30(int id, unsigned char on);                 // 0x7100203e30
    unsigned char stage_cleared_202eb0(int stage, int rank);          // 0x7100202eb0
    unsigned short count_203b10(int id);                              // 0x7100203b10
    unsigned char flag_204674(int id);                                // 0x7100204674
    unsigned char has_202b1c(int id);                                 // 0x7100202b1c
    unsigned char has_202ba0(int id);                                 // 0x7100202ba0
    unsigned char unlocked_204518(int id);                            // 0x7100204518
    unsigned char has_flag_2026fc(int id);                            // 0x71002026fc
    unsigned char has_202cec(int id);                                 // 0x7100202cec
};

Game45f07c* get_game();                                               // 0x7100204728

struct Unit45f07c {
    short map;                        // +0
    unsigned char pad2[0x1de];
};
struct UnitDb45f07c {
    unsigned char pad0[0xdb626];
    Unit45f07c units[128];            // +db626
};
UnitDb45f07c* get_unit_database_20ec80();                             // 0x710020ec80

struct Entry45f07c {
    unsigned int kind_209bd8();                                       // 0x7100209bd8
};
struct Table45f07c {
    Entry45f07c* entry_209c48(int index);                             // 0x7100209c48
};
Table45f07c* load_global_209cb4();                                    // 0x7100209cb4

struct Level45f07c {
    unsigned int clamped_200294();                                    // 0x7100200294
};
struct Found45f07c {
    unsigned char pad0[0x28];
    Level45f07c level;                // +28
};
struct FoundTable45f07c {
    Found45f07c* found_2015a8(int index);                             // 0x71002015a8
};
FoundTable45f07c* load_global_200fc0();                               // 0x7100200fc0

struct Progress45f07c {
    unsigned char done;
    float target;
    float current;
};
Progress45f07c progress_45e160(int id);                               // 0x710045e160

unsigned char call_45e718();                                          // 0x710045e718
unsigned char call_45e9e8();                                          // 0x710045e9e8
unsigned char call_45ea64();                                          // 0x710045ea64
unsigned char call_45e930();                                          // 0x710045e930
unsigned char call_45eae4();                                          // 0x710045eae4
unsigned char call_45eba0();                                          // 0x710045eba0
unsigned char call_45ec50();                                          // 0x710045ec50
unsigned char call_45ed00();                                          // 0x710045ed00
unsigned char call_45edb0();                                          // 0x710045edb0
unsigned char call_45ee60();                                          // 0x710045ee60
unsigned char call_45ef10();                                          // 0x710045ef10
unsigned char call_45efc0();                                          // 0x710045efc0

struct TrophyBits45f07c {
    unsigned int words[2];

    bool test(int id) const { return (words[id / 32] & (1u << (id % 32))) != 0; }
    void set(int id) { words[id / 32] |= 1u << (id % 32); }
};

struct TrophyChecker45f07c {
    TrophyBits45f07c done;            // +0
    unsigned int pad8;
    TrophyBits45f07c pending;         // +c

    void update();
    void unlock(int id) {
        get_game()->set_earned_203e30(id, 1);
        done.set(id);
    }
};

static inline bool earned(int id) {
    return get_game()->earned_203dfc(id) && get_game()->reported_203d0c(id);
}

static inline unsigned long stat(unsigned int id) {
    return get_game()->stats.stat_2028b4(id);
}

static inline bool stage_cleared(int stage, int rank) {
    return stage >= 32 || get_game()->stage_cleared_202eb0(stage, rank);
}

static inline bool stages_cleared(int rank) {
    for (unsigned int i = 0; i < 300; i++) {
        if (!stage_cleared(i, rank))
            return false;
    }
    return true;
}

static inline bool any_count_999() {
    for (int i = 0; i < 128; i++) {
        if (get_game()->count_203b10(i) == 999)
            return true;
    }
    return false;
}

static inline unsigned int count_flags_204674() {
    unsigned int n = 0;
    for (int i = 0; i < 39; i++) {
        if (get_game()->flag_204674(i) == 1)
            n++;
    }
    return n;
}

static inline bool all_202b1c() {
    for (int i = 0; i < 75; i++) {
        if (!get_game()->has_202b1c(i))
            return false;
    }
    return true;
}

static inline bool all_202ba0() {
    for (int i = 0; i < 35; i++) {
        if (!get_game()->has_202ba0(i))
            return false;
    }
    return true;
}

static inline bool all_unlocked_204518() {
    for (int i = 0; i < 255; i++) {
        unsigned int kind = load_global_209cb4()->entry_209c48(i)->kind_209bd8();
        if (!(i >= 120 && i <= 126) && kind <= 4 && !get_game()->unlocked_204518(i))
            return false;
    }
    return true;
}

static inline bool all_ranks() {
    for (long i = 0; i < 128; i++) {
        if (get_game()->ranks[i] != 3)
            return false;
    }
    return true;
}

static inline bool all_states(int map) {
    for (long i = 0; i < 128; i++) {
        if (get_game()->maps[map].states[i] != 3)
            return false;
    }
    return true;
}

static inline bool no_lost_units(int map) {
    for (long i = 0; i < 128; i++) {
        if (get_game()->maps[map].states[i] == -1 && get_unit_database_20ec80()->units[i].map != -1)
            return false;
    }
    return true;
}

static inline bool all_earned() {
    for (int i = 0; i < 61; i++) {
        if (!get_game()->earned_203dfc(i))
            return false;
    }
    return true;
}

static inline bool cells_cleared() {
    for (int i = 0; i < 128; i++) {
        if (!get_game()->board.cleared_26b0d4(i))
            return false;
    }
    return true;
}

static inline bool board_cleared(int map) {
    for (int i = 0; i < 128; i++) {
        if (!get_game()->maps[map].board.cleared_26b0d4(i))
            return false;
    }
    return true;
}

static inline bool map_done(int map) {
    for (long i = 0; i < 128; i++) {
        if (get_game()->maps[map].states[i] != 3 && get_unit_database_20ec80()->units[i].map != -1)
            return false;
    }
    return true;
}

static inline bool level_reached(unsigned int level) {
    for (int i = 0; i < 40; i++) {
        if (load_global_200fc0()->found_2015a8(i)->level.clamped_200294() >= level)
            return true;
    }
    return false;
}

// 0x710045f07c
void TrophyChecker45f07c::update() {
    if (pending.test(0) && !earned(0)) {
        get_game()->earned_203dfc(0);
        unsigned long a = stat(2);
        unsigned long b = stat(3);
        if ((a < b ? b : a) >= 1000)
            unlock(0);
    }
    if (pending.test(1) && !earned(1)) {
        get_game()->earned_203dfc(1);
        if (stat(0xc) >= 100)
            unlock(1);
    }
    if (pending.test(2) && !earned(2)) {
        get_game()->earned_203dfc(2);
        if (stat(0xd) >= 500)
            unlock(2);
    }
    if (pending.test(3) && !earned(3)) {
        get_game()->earned_203dfc(3);
        if (stat(0x10) >= 50)
            unlock(3);
    }
    if (pending.test(4) && !earned(4)) {
        get_game()->earned_203dfc(4);
        if (stat(0) >= 100000)
            unlock(4);
    }
    if (pending.test(5) && !earned(5)) {
        get_game()->earned_203dfc(5);
        if (stat(6) >= 1000000)
            unlock(5);
    }
    if (pending.test(6) && !earned(6)) {
        get_game()->earned_203dfc(6);
        if (stat(9) >= 1000)
            unlock(6);
    }
    if (pending.test(7) && !earned(7)) {
        get_game()->earned_203dfc(7);
        if (stat(0xa) >= 100)
            unlock(7);
    }
    if (pending.test(8) && !earned(8)) {
        get_game()->earned_203dfc(8);
        if (stat(7) >= 1000)
            unlock(8);
    }
    if (pending.test(9) && !earned(9)) {
        get_game()->earned_203dfc(9);
        if (stat(8) >= 50)
            unlock(9);
    }
    if (pending.test(10) && !earned(10)) {
        get_game()->earned_203dfc(10);
        if (static_cast<float>(static_cast<unsigned int>(stat(0xe)) / 10000) / 1000.0f >= 42.195f)
            unlock(10);
    }
    if (pending.test(11) && !earned(11)) {
        get_game()->earned_203dfc(11);
        if (stat(0x11) >= 100)
            unlock(11);
    }
    if (pending.test(12) && !earned(12)) {
        if (stages_cleared(-1))
            unlock(12);
    }
    if (pending.test(12) && !earned(12)) {
        if (stages_cleared(-1))
            unlock(12);
    }
    if (pending.test(13) && !earned(13)) {
        if (stages_cleared(3))
            unlock(13);
    }
    if (pending.test(14) && !earned(14)) {
        if (call_45e718())
            unlock(14);
    }
    if (pending.test(15) && !earned(15)) {
        if (call_45e9e8())
            unlock(15);
    }
    if (pending.test(16) && !earned(16)) {
        Progress45f07c p = progress_45e160(16);
        if (p.target != 0.0f && p.current >= p.target)
            unlock(16);
    }
    if (pending.test(17) && !earned(17)) {
        get_game()->earned_203dfc(17);
        if (stat(0xb) >= 100)
            unlock(17);
    }
    if (pending.test(18) && !earned(18)) {
        if (any_count_999())
            unlock(18);
    }
    if (pending.test(19) && !earned(19)) {
        if (static_cast<unsigned int>(stat(0xf)) >= 100)
            unlock(19);
    }
    if (pending.test(20) && !earned(20)) {
        get_game()->earned_203dfc(20);
        if (count_flags_204674() >= 39)
            unlock(20);
    }
    if (pending.test(21) && !earned(21)) {
        if (all_202b1c())
            unlock(21);
    }
    if (pending.test(22) && !earned(22)) {
        if (all_202ba0())
            unlock(22);
    }
    if (pending.test(23) && !earned(23)) {
        if (all_unlocked_204518())
            unlock(23);
    }
    if (pending.test(24) && !earned(24)) {
        if (get_game()->has_flag_2026fc(0x10))
            unlock(24);
    }
    if (pending.test(25) && !earned(25)) {
        if (get_game()->has_202cec(0x35))
            unlock(25);
    }
    if (pending.test(26) && !earned(26)) {
        if (get_game()->has_flag_2026fc(0xf))
            unlock(26);
    }
    if (pending.test(27) && !earned(27)) {
        if (call_45ea64())
            unlock(27);
    }
    if (pending.test(28) && !earned(28)) {
        get_game()->earned_203dfc(28);
        if (stat(0x13) != 0)
            unlock(28);
    }
    if (pending.test(29) && !earned(29)) {
        get_game()->earned_203dfc(29);
        if (stat(0x13) >= 3)
            unlock(29);
    }
    if (pending.test(30) && !earned(30)) {
        if (get_game()->has_flag_2026fc(0x2e))
            unlock(30);
    }
    if (pending.test(31) && !earned(31)) {
        if (cells_cleared())
            unlock(31);
    }
    if (pending.test(32) && !earned(32)) {
        if (all_ranks())
            unlock(32);
    }
    if (pending.test(33) && !earned(33)) {
        if (call_45e930())
            unlock(33);
    }
    if (pending.test(34) && !earned(34)) {
        if (board_cleared(3))
            unlock(34);
    }
    if (pending.test(35) && !earned(35)) {
        if (map_done(3))
            unlock(35);
    }
    if (pending.test(36) && !earned(36)) {
        if (call_45eae4())
            unlock(36);
    }
    if (pending.test(37) && !earned(37)) {
        if (board_cleared(0))
            unlock(37);
    }
    if (pending.test(38) && !earned(38)) {
        if (all_states(0))
            unlock(38);
    }
    if (pending.test(39) && !earned(39)) {
        if (call_45eba0())
            unlock(39);
    }
    if (pending.test(40) && !earned(40)) {
        if (board_cleared(1))
            unlock(40);
    }
    if (pending.test(41) && !earned(41)) {
        if (map_done(1))
            unlock(41);
    }
    if (pending.test(42) && !earned(42)) {
        if (call_45ec50())
            unlock(42);
    }
    if (pending.test(43) && !earned(43)) {
        if (no_lost_units(2))
            unlock(43);
    }
    if (pending.test(44) && !earned(44)) {
        if (map_done(2))
            unlock(44);
    }
    if (pending.test(45) && !earned(45)) {
        if (call_45ed00())
            unlock(45);
    }
    if (pending.test(46) && !earned(46)) {
        if (board_cleared(4))
            unlock(46);
    }
    if (pending.test(47) && !earned(47)) {
        if (map_done(4))
            unlock(47);
    }
    if (pending.test(48) && !earned(48)) {
        if (call_45edb0())
            unlock(48);
    }
    if (pending.test(49) && !earned(49)) {
        if (board_cleared(5))
            unlock(49);
    }
    if (pending.test(50) && !earned(50)) {
        if (map_done(5))
            unlock(50);
    }
    if (pending.test(51) && !earned(51)) {
        if (call_45ee60())
            unlock(51);
    }
    if (pending.test(52) && !earned(52)) {
        if (level_reached(149))
            unlock(52);
    }
    if (pending.test(53) && !earned(53)) {
        if (board_cleared(6))
            unlock(53);
    }
    if (pending.test(54) && !earned(54)) {
        if (map_done(6))
            unlock(54);
    }
    if (pending.test(55) && !earned(55)) {
        if (call_45ef10())
            unlock(55);
    }
    if (pending.test(56) && !earned(56)) {
        if (level_reached(199))
            unlock(56);
    }
    if (pending.test(57) && !earned(57)) {
        if (board_cleared(7))
            unlock(57);
    }
    if (pending.test(58) && !earned(58)) {
        if (map_done(7))
            unlock(58);
    }
    if (pending.test(59) && !earned(59)) {
        if (call_45efc0())
            unlock(59);
    }
    if (pending.test(60) && !earned(60)) {
        if (level_reached(254))
            unlock(60);
    }
    if (pending.test(61) && !earned(61)) {
        if (all_earned())
            unlock(61);
    }
    pending.words[0] = 0;
    pending.words[1] = 0;
}
