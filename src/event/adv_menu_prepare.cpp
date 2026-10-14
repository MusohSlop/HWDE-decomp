// Adventure Mode menu board loading (0x7100283e88), split out of event/adv_menu_board.cpp: its unit layout ids
// come from a switch that Clang turns into a lookup table at 0x71007f7a20, which lies apart from the jump tables
// of the other menu board helpers, so the function needs its own .rodata. Names are descriptive placeholders.
// Status: matching/README.md.

struct ResourceHandle {
    void* resource;
};

struct MenuBoard {
    ResourceHandle board;     // +00
    ResourceHandle units;     // +08
    unsigned char value10;    // +10
    unsigned char loaded;     // +11
    unsigned char pad12[6];
};
// Reached through the GOT slot at 0x7100c2a650.
extern MenuBoard* gMenuBoard;

struct SharedState {
    unsigned char pad0[4];
    int language;             // +04
};
SharedState* get_shared_state();                                            // 0x71002aae3c
unsigned char shared_state_exiting(SharedState* state);                     // 0x71002ac7f0
void* load_layout(int id);                                                  // 0x71001f7868

void prepare_menu_board(int mode, unsigned char flag) {
    if (shared_state_exiting(get_shared_state()))
        return;
    MenuBoard* board = gMenuBoard;
    if (!board)
        return;
    board->value10 = flag;
    SharedState* shared = get_shared_state();
    if (!board->board.resource) {
        int language = shared->language;
        void* layout = load_layout(language == 6 ? 0x2d55 : language + 0x2d54);
        board->board.resource = layout;
        if (mode == -1 || !layout)
            return;
    } else if (mode == -1) {
        return;
    }
    MenuBoard* current = gMenuBoard;
    // modes 2-8 pick a unit layout from a table; mode 9 and the rest are handled by the default
    int index;
    switch (mode) {
    case 2: index = 1; break;
    case 3: index = 2; break;
    case 4: index = 3; break;
    case 5: index = 4; break;
    case 6: index = 0; break;
    case 7: index = 1; break;
    case 8: index = 2; break;
    default: index = mode == 9 ? 3 : 0; break;
    }
    if (!current->units.resource) {
        void* layout = load_layout(static_cast<unsigned int>(mode) < 6 ? (index | 0x2d60) : index + 0x4629);
        current->units.resource = layout;
        if (!layout)
            return;
    }
    current->loaded = 1;
}
