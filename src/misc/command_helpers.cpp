// Small helpers called by the script command dispatcher (0x71001c86d4): word and byte table
// stores, clamped setters and flag tests. Names are descriptive placeholders. Status:
// matching/README.md.

struct Words1ccc18 {
    int data[1];
};

// 0x71001ccc18
void put_word_1ccc18(Words1ccc18* words, unsigned int index, int value) {
    words->data[index] = value;
}

struct Flags19b538 {
    unsigned char bits;       // +00: top bit set when taken
};

// 0x710019b538
unsigned char top_clear_19b538(Flags19b538* flags) {
    return (flags->bits >> 7) ^ 1;
}

struct Mode1a76b0 {
    unsigned char pad[0x19ec];
    int mode;                 // +19ec
};

// 0x71001a76b0
void set_mode_1a76b0(Mode1a76b0* object, int mode) {
    object->mode = mode < 3 ? mode : 0;
}

struct Stage133d68 {
    unsigned char pad[0x112];
    unsigned short stage;     // +112
};

// 0x7100133d68
void raise_stage_133d68(Stage133d68* object) {
    if (object->stage <= 1)
        object->stage = 2;
}

struct Row1cbfdc {
    unsigned char value;      // +00
    unsigned char pad1[0x2a];
};

struct Rows1cbfdc {
    Row1cbfdc rows[1];
};

// 0x71001cbfdc
int row_value_1cbfdc(Rows1cbfdc* table, unsigned int row) {
    unsigned char value = table->rows[row].value;
    return value == 0xff ? -1 : value;
}

struct Count19bb00 {
    unsigned char pad[0x10];
    int count;                // +10
};

// 0x710019bb00
void set_count_19bb00(Count19bb00* object, int count) {
    count = count < 0 ? 0 : count;
    object->count = count > 8 ? 8 : count;
}

struct Level19bb1c {
    unsigned char pad[0x4c];
    int level;                // +4c
};

// 0x710019bb1c
void set_level_19bb1c(Level19bb1c* object, int level) {
    level = level < 0 ? 0 : level;
    object->level = level > 4 ? 4 : level;
}

// Reached through the GOT slot at 0x7100c21df0.
extern int gResourceQueueElapsedStep;

struct Timers1ccc20 {
    unsigned char pad[0x40];
    int timers[1];            // +40
};

// 0x71001ccc20
void set_timer_1ccc20(Timers1ccc20* object, unsigned int index, int steps) {
    object->timers[index] = gResourceQueueElapsedStep * steps;
}

struct Counters1ccd44 {
    unsigned char pad[0x140];
    int counters[1];          // +140
};

// 0x71001ccd44
void add_counter_1ccd44(Counters1ccd44* object, unsigned int index, int delta) {
    int value = object->counters[index] + delta;
    object->counters[index] = value < 0 ? 0 : value;
}

struct Requests252488;
void post_request_252488(Requests252488* requests, int owner, int request); // 0x7100252488

struct Manager258150 {
    unsigned char pad[0x68];
    unsigned char requests[0xcec]; // +68
    int owner;                // +d54
};
// Reached through the GOT slot at 0x7100c22d68.
extern Manager258150* gManager_c22d68;

// 0x7100258150
void post_request_258150(int request) {
    Manager258150* manager = gManager_c22d68;
    post_request_252488(reinterpret_cast<Requests252488*>(manager->requests), manager->owner, request);
}

struct Levels19b580 {
    unsigned char pad[2];
    unsigned char levels[3];  // +02
};

// 0x710019b580
void set_level_19b580(Levels19b580* object, unsigned int index, int level) {
    if (index > 2)
        return;
    level = level < 0 ? 0 : level;
    object->levels[index] = level < 3 ? level : 3;
}

void register_resource_callback(void* callback, void (*completion)(int, unsigned int),
                                unsigned int flags);                        // 0x7100258b0c
// Reached through the GOT slot at 0x7100c22c30.
extern unsigned char gCallback_c22c30[];

struct Track0ffbb4 {
    unsigned int current;     // +00
    unsigned int pending;     // +04
};

// 0x71000ffbb4
void request_track_ffbb4(Track0ffbb4* track, unsigned int id) {
    if (id > 0x103 || track->current == id)
        return;
    track->pending = id;
    register_resource_callback(gCallback_c22c30, nullptr, 0x20);
}

struct Purse1a10e4 {
    unsigned char pad[0x60];
    unsigned int total;       // +60
};

struct Wallet1a10e4 {
    unsigned char pad[8];
    Purse1a10e4* purse;       // +08
    unsigned char pad10[0xa4];
    unsigned int earned;      // +b4
};

// 0x71001a10e4
void add_money_1a10e4(Wallet1a10e4* wallet, unsigned int amount) {
    unsigned int total = wallet->purse->total + amount;
    wallet->purse->total = total > 9999999 ? 9999999 : total;
    unsigned int earned = wallet->earned + amount;
    wallet->earned = earned > 9999999 ? 9999999 : earned;
}

// 0x71001a111c
void spend_money_1a111c(Wallet1a10e4* wallet, unsigned int amount) {
    unsigned int total = wallet->purse->total;
    unsigned int left = total - amount;
    wallet->purse->total = left > total ? 0 : left;
    unsigned int earned = wallet->earned;
    unsigned int rest = earned - amount;
    wallet->earned = rest > earned ? 0 : rest;
}

struct Unit254974 {
    unsigned char pad[0x58];
    int item;                 // +58
    unsigned char pad5c[0x104];
};

struct Roster254974 {
    unsigned char pad[0xc20];
    Unit254974 units[0xf6];   // +c20

    Unit254974* unit(unsigned int id) { return id < 0xf6 ? &units[id] : nullptr; }
};
// Reached through the GOT slot at 0x7100c216e8.
extern Roster254974* gShop;

struct Pick254974 {
    int item;                 // +00
    unsigned int unit;        // +04
};

struct Picks254974 {
    unsigned char pad[0xe58];
    Pick254974 picks[1];      // +e58
};

// 0x7100254974
void pick_unit_254974(Picks254974* picks, unsigned int unit, int slot) {
    picks->picks[slot].item = gShop->unit(unit)->item;
    picks->picks[slot].unit = unit;
}

struct Focus172110;
Focus172110* focus_info_18f0e0(Roster254974* roster);                       // 0x710018f0e0
void set_focus_193184(Focus172110* focus, int a, int b);                    // 0x7100193184

// 0x7100172110
void set_focus_172110(int a, int b) {
    set_focus_193184(focus_info_18f0e0(gShop), a, b);
}

struct Stage1d738c {
    unsigned char pad[0x139940];
    unsigned int flags;       // +139940
};

// 0x71001d738c
void set_stage_flag_1d738c(Stage1d738c* stage, unsigned int flag, unsigned char on) {
    unsigned int mask = flag < 10 ? 1 << flag : 0;
    if (on)
        stage->flags |= mask;
    else
        stage->flags &= ~mask;
}

struct Settings3fa36c {
    unsigned char pad[0x1a4c];
    float defaults[7];        // +1a4c
    float targets[7];         // +1a68
    float rates[7];           // +1a84
    int counts[7];            // +1aa0
    int steps[7];             // +1abc
};
// Reached through the GOT slot at 0x7100c2b700.
extern Settings3fa36c* gSettings_c2b700;

// 0x71003fa36c
void start_fade_3fa36c(unsigned int index, float target, float rate, int count) {
    Settings3fa36c* settings = gSettings_c2b700;
    if (!settings)
        return;
    if (!(target >= 0.0f))
        target = settings->defaults[index];
    settings->targets[index] = target;
    settings->rates[index] = rate;
    settings->counts[index] = count == 0 ? 1 : count;
    settings->steps[index] = 0;
}

// 0x7100195920
bool inside_field_195920(const float* position) {
    if (position[0] < 0.0f || position[0] >= 64000.0f)
        return false;
    if (position[2] < 0.0f || position[2] >= 64000.0f)
        return false;
    return !(position[1] < 0.0f);
}

struct Entries1a6f6c {
    unsigned char pad[0x228];
    struct {
        unsigned char kind;   // +00
        unsigned char pad1[0xbf];
    } entries[32];            // +228
};

// 0x71001a6f6c
unsigned int find_kind_1a6f6c(Entries1a6f6c* table, int kind) {
    for (unsigned int i = 0; i < 32; ++i) {
        if (table->entries[i].kind == kind)
            return i;
    }
    return 32;
}

struct Bits1a7bd8 {
    unsigned char pad[0x1dd8];
    unsigned char bits[1];    // +1dd8
};

// 0x71001a7bd8
void set_bit_1a7bd8(Bits1a7bd8* object, int index, unsigned char on) {
    unsigned int byte = index / 8;
    unsigned char mask = 1 << (index & 7);
    if (on)
        object->bits[byte] |= mask;
    else
        object->bits[byte] &= ~mask;
}

struct Unit16a6ac {
    unsigned char pad[0x11c];
    unsigned int kind : 3;    // +11c
    unsigned int marked : 1;
    unsigned int rest : 28;
    unsigned char pad120[0x40];
};

struct Roster16a6ac {
    unsigned char pad[0xc20];
    Unit16a6ac units[0xf6];   // +c20

    Unit16a6ac* unit(unsigned int id) { return id < 0xf6 ? &units[id] : nullptr; }
};

struct UnitState16a6ac {
    unsigned char pad[0x90];
    int mark;                 // +90
    unsigned char pad94[0x8c];
};

struct UnitStates16a6ac {
    UnitState16a6ac units[0xf6];
};
// Reached through the GOT slot at 0x7100c22bd8.
extern UnitStates16a6ac* gBlock_c22bd8;

// 0x710016a6ac
void mark_unit_16a6ac(unsigned int id, int mark) {
    Unit16a6ac* unit = reinterpret_cast<Roster16a6ac*>(gShop)->unit(id);
    UnitStates16a6ac* states = gBlock_c22bd8;
    if (!unit->marked)
        unit->marked = 1;
    states->units[id].mark = mark;
}

struct Seen1a48f4 {
    unsigned char pad[0x1ebc];
    unsigned char seen[0x3c]; // +1ebc
    unsigned char hidden[1];  // +1ef8
};

static inline unsigned int unit_bit(unsigned int unit) {
    unit = unit == 0x76 ? 0 : unit;
    return unit > 0x76 ? 1 : unit;
}

// 0x71001a48f4
void set_shown_1a48f4(Seen1a48f4* object, unsigned int unit, unsigned char shown) {
    unsigned int bit = unit_bit(unit);
    unsigned int byte = bit >> 3;
    unsigned char mask = 1 << (bit & 7);
    if (shown)
        object->hidden[byte] &= ~mask;
    else
        object->hidden[byte] |= mask;
}

// 0x71001a7b50
void set_seen_1a7b50(Seen1a48f4* object, unsigned int unit, unsigned char seen) {
    unsigned int bit = unit_bit(unit);
    unsigned int byte = bit >> 3;
    unsigned char mask = 1 << (bit & 7);
    if (seen)
        object->seen[byte] |= mask;
    else
        object->seen[byte] &= ~mask;
}

struct Slots427368;
Slots427368* load_global_425dd0();                                          // 0x7100425dd0
void forward_427368(Slots427368* slots, int id, void* a, void* b, void* c, void* d); // 0x7100427368

// 0x7100453e4c
void forward_453e4c(int id, void* unused, void* a, void* b, void* c, void* d) {
    forward_427368(load_global_425dd0(), id, a, b, c, d);
}

struct Setup40d18;
Setup40d18* get_battle_setup();                                             // 0x710016ef34
void set_setup_flags_16f618(Setup40d18* setup, unsigned long flags);        // 0x710016f618
struct Board40d18;
Board40d18* order_board_18d5d8(Roster254974* roster);                       // 0x710018d5d8
void open_board_1a8048(Board40d18* board, int flag);                        // 0x71001a8048

struct Once40d18 {
    int done;                 // +00
    int extra;                // +04
};
// Reached through the GOT slot at 0x7100c2ec00.
extern Once40d18 gOnce_c2ec00;

// 0x7100040d18
void open_board_once_40d18() {
    if (gOnce_c2ec00.done)
        return;
    set_setup_flags_16f618(get_battle_setup(), 0x100000000);
    gOnce_c2ec00.done = 1;
    gOnce_c2ec00.extra = 0;
    open_board_1a8048(order_board_18d5d8(gShop), 1);
}

extern "C" float fmaxf(float a, float b);
float ground_height_4534ac(const float* position);                          // 0x71004534ac

// 0x7100148d3c
float ground_148d3c(const float* position) {
    float height = 0.0f;
    if (inside_field_195920(position))
        height = fmaxf(ground_height_4534ac(position), 0.0f);
    return height;
}

struct Queue146f38;
void reset_queue_146f38(Queue146f38* queue);                                // 0x7100146f38

struct Log165874 {
    unsigned char lines[0x100]; // +000
    int resets;               // +100
    short head;               // +104
    short limit;              // +106
};

// 0x7100165874
void reset_log_165874(Log165874* log) {
    log->head = 0;
    __builtin_memset(log->lines, 0, sizeof(log->lines));
    log->limit = 0x80;
    reset_queue_146f38(reinterpret_cast<Queue146f38*>(reinterpret_cast<unsigned char*>(gBlock_c22bd8) + 0x37230));
    ++log->resets;
}

struct StageInfo1ccdf0 {
    unsigned char pad[0xc];
    unsigned char flags;      // +0c
};
struct Stage1ccdf0;
// Reached through the GOT slot at 0x7100c22ca8.
extern Stage1ccdf0* gGlobal_c22ca8;
StageInfo1ccdf0* stage_info_1d6ad0(Stage1ccdf0* stage);                     // 0x71001d6ad0

struct Unlocks1ccdf0 {
    unsigned char pad[0x1fc];
    unsigned int bits[1];     // +1fc
};

// 0x71001ccdf0
bool unlocked_1ccdf0(Unlocks1ccdf0* unlocks, unsigned int id) {
    StageInfo1ccdf0* info = stage_info_1d6ad0(gGlobal_c22ca8);
    if (info && (info->flags & 2))
        return true;
    return (unlocks->bits[id >> 5] & (1u << (id & 31))) != 0;
}
