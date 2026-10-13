// Adventure Mode state and per-cell entry tables (one global object, reached through the GOT
// slot at 0x7100c23250). Names are descriptive placeholders. Layout from the reset at
// 0x710026e824 and the board query unit.
#pragma once

class BoardQuery {
public:
    int active_count(int slot);                                             // 0x7100269bb8
    int total_count(int slot);                                              // 0x7100269bfc
    bool unit_alive(int player, int slot, int team);                        // 0x7100269c40
    int cell_level(unsigned int cell);                                      // 0x710026b234
    void find_entry(unsigned int cell, unsigned int slot, int kind, int* level, int* position,
                    int* state);                                            // 0x710026b3cc
    void reset();                                                           // 0x710026e824

    unsigned char active;     // +0000
    unsigned char pad1[3];
    int state;                // +0004
    int step;                 // +0008
    int previous_step;        // +000c
    unsigned char value10;    // +0010
    unsigned char value11;    // +0011
    unsigned char value12;    // +0012
    unsigned char value13;    // +0013
    unsigned char value14;    // +0014
    unsigned char pad15[3];
    long value18;             // +0018
    unsigned char value20;    // +0020
    unsigned char value21;    // +0021
    unsigned char value22;    // +0022
    unsigned char pad23;
    int base_levels[4];       // +0024
    int levels34[4];          // +0034
    unsigned char pad44;
    unsigned char cell_flags[0x80]; // +0045
    unsigned char valuec5;    // +00c5
    unsigned char padc6[6];
    int valuecc;              // +00cc
    unsigned char valued0;    // +00d0
    unsigned char timer_done; // +00d1
    unsigned char seal_done;  // +00d2
    unsigned char padd3;
    int valued4;              // +00d4
    int cell_values[0x80];    // +00d8
    unsigned char groups[0x80]; // +02d8
    unsigned char cell_marks[0x80]; // +0358
    int levels[0x80][0x1c];   // +03d8
    int kinds[0x80][0x1c];    // +3bd8
    unsigned char flags[0x80][0x1c]; // +73d8
    unsigned int items[0x80][0x1c]; // +81d8
    int valueb9d8;            // +b9d8
    int valueb9dc;            // +b9dc
    unsigned char valueb9e0;  // +b9e0
    unsigned char valueb9e1;  // +b9e1
    unsigned char padb9e2[2];
    int access;               // +b9e4
    unsigned char turn_alert; // +b9e8
    unsigned char padb9e9[3];
    int reset_pending;        // +b9ec
    unsigned char valueb9f0;  // +b9f0
    unsigned char quest_short; // +b9f1
    unsigned char quest_long; // +b9f2
    unsigned char sealed_high; // +b9f3
    unsigned char sealed_low; // +b9f4
    unsigned char valueb9f5;  // +b9f5
    unsigned char valueb9f6;  // +b9f6
    unsigned char valueb9f7;  // +b9f7
    unsigned char valueb9f8;  // +b9f8
    unsigned char valueb9f9;  // +b9f9
    unsigned char padb9fa[2];
    int valueb9fc;            // +b9fc
    union {
        long valueba00;       // +ba00: cleared as one word
        struct {
            int valueba00_low;
            unsigned char item_found; // +ba04
            unsigned char padba05[3];
        };
    };
};
static_assert(sizeof(BoardQuery) == 0xba08, "board query size");

// Reached through the GOT slot at 0x7100c23250.
extern BoardQuery gBoardQuery;
