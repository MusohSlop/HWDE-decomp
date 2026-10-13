// CellRecord::cleared (0x7100202164); original file: game object, around 0x71002020xx.
// It calls the option-source accessors in misc/accessors.cpp, so it lives in its own unit.
// Names are descriptive placeholders. Status: matching/README.md.

#include "event/board_query.h"

class OptionSource {
public:
    int pending();                                                          // 0x710020c1fc
    int locked();                                                           // 0x710020c204
};
OptionSource* get_option_source();                                          // 0x710020bd74

class CellRecord {
public:
    unsigned char cleared();

    int unit;                 // +00
    unsigned char pad4[9];
    unsigned char kind;       // +0d
};

unsigned char CellRecord::cleared() {
    if (!get_option_source()->pending() && !kind && !gBoardQuery.valueba00_low)
        return unit != -1;
    if (get_option_source()->locked())
        return 0;
    if (kind == 1 && !gBoardQuery.valueba00_low)
        return unit != -1;
    return 0;
}
