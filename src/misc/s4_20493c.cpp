// A game state's reset (fourth session, 2-copy family 20493c): clears 0x27f8 bytes, sets the defaults, resets the 15
// trophy records and tail-calls the options' init. The byte at +1992 is entry 0x1831 of the array at +161 (written as a
// field it schedules its constant the other way). GameState::init<0> (0x710020493c) and init<1> (0x7100204aac).

typedef unsigned long size_t;
extern "C" void* memset(void* dst, int c, size_t n);                        // 0x7100600890 (import)

class StatusBlock {
public:
    void initialize();                                                      // 0x7100205824
};
class TrophyTimes {
public:
    void reset_287e40();                                                    // 0x7100287e40
};
struct TrophyRecord {
    unsigned char data[0xa0];
};
StatusBlock* trophy_stats(TrophyRecord* record);                            // 0x71002885d4
TrophyTimes* trophy_times_28873c(TrophyRecord* record);                     // 0x710028873c

class GameOptions {
public:
    void init_2021e8();                                                     // 0x71002021e8
};

class GameState {
public:
    template <int Copy> void init();

    unsigned char pad0[0x148];
    unsigned char flag148;    // +148
    unsigned char flag149;    // +149
    unsigned short count14a;  // +14a
    int range14c[2];          // +14c
    int range154[2];          // +154
    unsigned char pad15c[2];
    unsigned char flag15e;    // +15e
    unsigned char flag15f;    // +15f
    unsigned char pad160;
    unsigned char slots161[0x18b8];  // +161: the first 0xaa1 cleared to 0xff, entry 0x1831 too
    unsigned char levels1a19[2];  // +1a19
    unsigned char pad1a1b;
    TrophyRecord trophies[15];  // +1a1c
    unsigned char pad237c[0xf0];
    unsigned char slots246c[0xf0];  // +246c
    unsigned char pad255c[0x4c];
    unsigned char slots25a8[0xff];  // +25a8
    unsigned char pad26a7;
    long id26a8;              // +26a8
    int index26b0;            // +26b0
    unsigned char pad26b4[0x40];
    unsigned char flag26f4;   // +26f4
    unsigned char pad26f5[0x103];
    GameOptions options;      // +27f8
};

template <int Copy>
void GameState::init() {
    memset(this, 0, 0x27f8);
    flag148 = 1;
    count14a = 0;
    memset(range14c, 0xff, sizeof(range14c));
    memset(range154, 0xff, sizeof(range154));
    flag15e = 1;
    flag15f = 1;
    flag149 = 1;
    slots161[0x1831] = 0xff;
    memset(slots161, 0xff, 0xaa1);
    memset(levels1a19, 5, sizeof(levels1a19));
    for (int i = 0; i < 15; i++) {
        trophy_stats(&trophies[i])->initialize();
        trophy_times_28873c(&trophies[i])->reset_287e40();
    }
    memset(slots246c, 0xff, sizeof(slots246c));
    memset(slots25a8, 0xff, sizeof(slots25a8));
    index26b0 = -1;
    id26a8 = -1;
    flag26f4 = 1;
    options.init_2021e8();
}

// 0x710020493c
template void GameState::init<0>();
// 0x7100204aac
template void GameState::init<1>();
