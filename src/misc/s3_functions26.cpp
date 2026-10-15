// Menu bases written by hand (third session), kept out of the units that inline them. Names are descriptive
// placeholders. Status: matching/README.md.

extern "C" void* memset(void*, int, unsigned long);

class Base38c480;

// A cursor sub-object of the menus (0x30 bytes).
class MenuCursor {
public:
    MenuCursor();                                                           // 0x710037f550
    void init();                                                            // 0x710037cc88

    unsigned char data[0x30];
};

// The deck's base (vtable GOT 0x7100c2b168): its owner, the listed panels, a line count and a cursor.
class DeckBase38cff0 {
public:
    DeckBase38cff0(void* owner, int lines);
    virtual ~DeckBase38cff0();
    void add(Base38c480* panel);                                            // 0x710038dc8c

    void* owner;                 // +08
    void* list[64];              // +10
    int i210;                    // +210
    int count;                   // +214
    int lines;                   // +218
    int i21c;                    // +21c
    int i220;                    // +220
    bool b224;                   // +224
    unsigned char pad225[3];
    MenuCursor cursor;           // +228
};

// 0x710038cff0
DeckBase38cff0::DeckBase38cff0(void* owner_, int lines_)
    : owner(owner_), i210(0), count(0), lines(lines_), i21c(0), i220(0), b224(false) {
    memset(list, 0, sizeof(list));
    cursor.init();
}
