// Matching candidates for the Adventure board override object (0x7100290e90-0x7100291104).
// Names are descriptive placeholders. Status: matching/README.md.

class GameState {
public:
    unsigned char pad[0x1bb7c];
    unsigned int mode;        // +1bb7c
};

class Game {
public:
    GameState* state();                                                     // 0x7100204c10
};
Game* get_game();                                                           // 0x7100204728

unsigned char dlc_board_flag();                                                 // 0x710026b088
unsigned char cell_group_flag(int cell);                                    // 0x710026cd8c
int unit_frame(int player, int slot);                                       // 0x710026c730

struct RefObject {
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void destroy();   // +18

    int refs;                 // +08
};

static inline void release(RefObject** slot) {
    if (RefObject* object = *slot) {
        if (!--object->refs)
            object->destroy();
        *slot = nullptr;
    }
}

struct FrameHeader {
    unsigned short width;     // +0
    unsigned short height;    // +2
    unsigned short span;      // +4
    unsigned short pad6;
    unsigned short count;     // +8
};

struct FrameEntry {
    short kind;               // +0
    unsigned short start;     // +2
    unsigned short row;       // +4
    unsigned short length;    // +6
};

class BoardOverride {
public:
    void reset();                                                           // 0x7100290e90
    RefObject* resource();                                                  // 0x7100290f74
    FrameHeader* frames();                                                  // 0x7100290f94
    FrameEntry* frame(unsigned int index);                                  // 0x7100290f9c
    int stage_kind(int player);                                             // 0x7100290fb0
    int remap_kind(int kind, void* table);                                  // 0x7100290fd4
    unsigned char has_secondary(int player, int slot);                      // 0x7100291058
    unsigned char has_primary(int player, int slot);                        // 0x71002910b0

    unsigned char pad[8];
    RefObject* objects[5];    // +08
    unsigned char active;     // +30
    unsigned char pad31[3];
    int phase;                // +34
    FrameHeader header;       // +38
    FrameEntry entries[10];   // +42
};

// Replacement kinds for the eight DLC kinds 0x93-0x9a once every route is cleared.
static const int kClearedKinds[8] = {0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0x99, 0xef};

void BoardOverride::reset() {
    release(&objects[0]);
    release(&objects[1]);
    release(&objects[2]);
    release(&objects[3]);
    release(&objects[4]);
}

RefObject* BoardOverride::resource() {
    return objects[0];
}

FrameHeader* BoardOverride::frames() {
    return &header;
}

FrameEntry* BoardOverride::frame(unsigned int index) {
    return index < 10 ? &entries[index] : entries;
}

int BoardOverride::stage_kind(int player) {
    return cell_group_flag(player) ? 0xd2 : 0xd3;
}

int BoardOverride::remap_kind(int kind, void*) {
    unsigned int index = kind - 0x93;
    if (index <= 7 && dlc_board_flag()) {
        Game* game = get_game();
        unsigned char* slot = reinterpret_cast<unsigned char*>(game) +
                              static_cast<unsigned long>(get_game()->state()->mode) * 0x2c38;
        if ((slot[0x5412] & 0xf) == 0xf)
            kind = kClearedKinds[static_cast<int>(index)];
    }
    return kind;
}

unsigned char BoardOverride::has_secondary(int player, int slot) {
    if (get_game()->state()->mode != 8)
        return 0;
    return unit_frame(player, slot) == 0xda;
}

unsigned char BoardOverride::has_primary(int player, int slot) {
    if (get_game()->state()->mode != 8)
        return 0;
    return unit_frame(player, slot) == 0xd9;
}
