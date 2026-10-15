// A record list's set-up (fourth session, template family 3305ec): RecordList::init clears the list, attaches its
// resource to the effect manager, stores the elapsed time and appends the (a, b) pair of each of the 255 record-book
// entries whose values are not negative and whose kind is 1, or 0 with the record shown in the game's progress. The
// original has two identical copies (0x71003305ec, 0x710039a010), written as one template with a dummy copy number.
// Names are descriptive placeholders.

#include "event/demo_effects.h"

// Reached through the GOT slot at 0x7100c21df0.
extern unsigned int gResourceQueueElapsedStep;

class RecordEntry {
public:
    int value_a();                                                          // 0x7100210624
    int value_b();                                                          // 0x7100210634
    int kind();                                                             // 0x710021063c
};
class RecordBook {
public:
    RecordEntry* entry(int i);                                              // 0x71002108dc
};
RecordBook* get_record_book();                                              // 0x710021069c

class GameState {
public:
    unsigned char record_shown(int id);                                     // 0x71002032f4
};
struct Game {
    unsigned char pad0[0x27f8];
    GameState progress;       // +27f8
};
Game* get_game();                                                           // 0x7100204728

struct RecordPair {
    int a;
    int b;
};

class RecordList {
public:
    template <int Copy> void init();

    void add(int a, int b) {
        pairs[count].a = a;
        pairs[count].b = b;
        count++;
    }

    void* head;               // +00
    int f8;                   // +08
    unsigned char padc[4];
    int count;                // +10
    int f14;                  // +14
    int f18;                  // +18
    unsigned char pad1c[0x14];
    unsigned char resource[0x17be0];  // +30
    RecordPair pairs[0xff];   // +17c10
    unsigned char pad18408[0x30];
    float elapsed;            // +18438
};

template <int Copy>
void RecordList::init() {
    f8 = 0;
    count = 0;
    f14 = 0;
    f18 = 0xb;
    head = 0;
    gEffectManager->attach_resource(reinterpret_cast<LightResource*>(resource));
    elapsed = gResourceQueueElapsedStep;
    for (int i = 0; i < 0xff; i++) {
        RecordEntry* e = get_record_book()->entry(i);
        if (!e) continue;
        int a = e->value_a();
        int b = e->value_b();
        int kind = e->kind();
        if (a < 0 || b < 0) continue;
        switch (kind) {
        case 0:
            if (get_game()->progress.record_shown(a)) add(a, b);
            break;
        case 1:
            add(a, b);
            break;
        }
    }
}

template void RecordList::init<0>();
template void RecordList::init<1>();
