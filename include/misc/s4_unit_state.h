// The unit-state test (fourth session): about 55 functions inline it on a unit's state id (Unit::state()->id).
// IF_UNIT_STATE_ACTIVE(id, action) runs the action when the id is 0-24, 58 or 59, and not 6, 7, 9, 10, 12, 13, 16-21
// or 39. The shape is what matches: the pairs 58/59 and 12/13 are bitwise (&) tests, so they become (id & ~1)
// compares sharing one and; the rest is a switch that lowers to a bit test over 0..39; and the action sits in the
// switch default (written as an inline bool helper, the switch becomes a lookup bitmap instead).
// Names are descriptive placeholders.
#pragma once

#define IF_UNIT_STATE_ACTIVE(id, action)                                                    \
    do {                                                                                    \
        int st_ = (id);                                                                     \
        if (st_ >= 0 && (st_ < 25 || !((st_ != 58) & (st_ != 59)))) {                        \
            switch (st_) {                                                                  \
            case 6: case 7: case 9: case 10:                                                \
            case 16: case 17: case 18: case 19: case 20: case 21: case 39:                  \
                break;                                                                      \
            default:                                                                        \
                if ((st_ != 12) & (st_ != 13)) { action; }                                  \
            }                                                                               \
        }                                                                                   \
    } while (0)

class Unit;

// What Unit::state() returns: a polymorphic state object with the state id at +10.
class UnitState {
public:
    virtual void s000();
    virtual void s008();
    virtual void s010();
    virtual void s018();
    virtual void s020();
    virtual void s028();
    virtual void s030();
    virtual void s038();
    virtual void s040();
    virtual void s048();
    virtual void s050();
    virtual void s058();
    virtual void s060();
    virtual int type();       // +68
    virtual void s070();
    virtual void s078();
    virtual void s080();
    virtual void s088();
    virtual void s090();
    virtual void s098();
    virtual void s0a0();
    virtual void s0a8();
    virtual void s0b0();
    virtual void s0b8();
    virtual void s0c0();
    virtual void s0c8();
    virtual void s0d0();
    virtual void s0d8();
    virtual void s0e0();
    virtual void s0e8();
    virtual void s0f0();
    virtual void s0f8();
    virtual void s100();
    virtual void s108();
    virtual void s110();
    virtual void s118();
    virtual void s120();
    virtual void s128();
    virtual void s130();
    virtual void s138();
    virtual void s140();
    virtual void s148();
    virtual void s150();
    virtual void s158();
    virtual void s160();
    virtual void s168();
    virtual void s170();
    virtual void s178();
    virtual void s180();
    virtual void s188();
    virtual void s190();
    virtual void s198();
    virtual void s1a0();
    virtual void s1a8();
    virtual void s1b0();
    virtual void s1b8();
    virtual void s1c0();
    virtual void s1c8();
    virtual void s1d0();
    virtual void s1d8();
    virtual void s1e0();
    virtual void s1e8();
    virtual void s1f0();
    virtual void s1f8();
    virtual void s200();
    virtual void s208();
    virtual void s210();
    virtual void s218();
    virtual void s220();
    virtual void s228();
    virtual void s230();
    virtual void s238();
    virtual void s240();
    virtual int special();    // +248
    virtual void s250();
    virtual void s258();
    virtual void s260();
    virtual void s268();
    virtual void s270();
    virtual void s278();
    virtual void s280();
    virtual void s288();
    virtual void s290();
    virtual void s298();
    virtual void s2a0();
    virtual void s2a8();
    virtual void s2b0();
    virtual void s2b8();
    virtual void s2c0();
    virtual void s2c8();
    virtual void refresh();   // +2d0
    virtual void s2d8();
    virtual void s2e0();
    virtual void s2e8();
    virtual void s2f0();
    virtual void s2f8();
    virtual float rate300();  // +300
    virtual float rate308();  // +308
    virtual void s310();
    virtual void s318();
    virtual struct UnitRef* unit_ref();  // +320
    virtual void s328();
    virtual void set_scale(float scale);  // +330
    virtual void s338();
    virtual void s340();
    virtual void s348();
    virtual void s350();
    virtual void s358();
    virtual void s360();
    virtual void s368();
    virtual void s370();
    virtual void s378();
    virtual void s380();
    virtual void s388();
    virtual void s390();
    virtual void s398();
    virtual void s3a0();
    virtual void s3a8();
    virtual void s3b0();
    virtual void s3b8();
    virtual void s3c0();
    virtual void s3c8();
    virtual void s3d0();
    virtual void s3d8();
    virtual void s3e0();
    virtual int item();       // +3e8
    virtual void s3f0();
    virtual void s3f8();
    virtual float rate400();  // +400
    virtual void s408();
    virtual float rate410();  // +410

    int item_blocked();       // 0x71000bf440 (parked: docs/s4_wip/unit_state_parked.cpp)

    union {
        unsigned char kind;   // +08: bits 0-1 the side
        unsigned long bits8;  // +08 read whole
        struct {
            unsigned char pad8;
            unsigned char flags9; // +09
            unsigned char pada[4];
            unsigned char flags_e; // +0e
        };
    };
    int id;                   // +10
    unsigned char pad14[4];
    Unit* unit;               // +18
    unsigned char pad20[4];
    short unit_id;            // +24
    unsigned char pad26[0x32];
    struct UnitStateInfo* info;  // +58
};

class UnitActor {
public:
    virtual void a00();
    virtual void a08();
    virtual void a10();
    virtual void a18();
    virtual void a20();
    virtual void a28();
    virtual void a30();
    virtual void a38();
    virtual void a40();
    virtual void a48();
    virtual void a50();
    virtual void a58();
    virtual void a60();
    virtual void a68();
    virtual void a70();
    virtual void a78();
    virtual void a80();
    virtual void a88();
    virtual void a90();
    virtual void a98();
    virtual void aa0();
    virtual void aa8();
    virtual void ab0();
    virtual void ab8();
    virtual void ac0();
    virtual void ac8();
    virtual void ad0();
    virtual void ad8();
    virtual void ae0();
    virtual void ae8();
    virtual void af0();
    virtual void af8();
    virtual void a100();
    virtual void a108();
    virtual void a110();
    virtual void refresh();   // +118
    virtual void a120();
    virtual void a128();
    virtual void a130();
    virtual void a138();
    virtual void a140();
    virtual void a148();
    virtual void a150();
    virtual void a158();
    virtual void a160();
    virtual void a168();
    virtual void a170();
    virtual void a178();
    virtual int command(int arg);  // +180
    virtual void a188();
    virtual void a190();
    virtual void a198();
    virtual void a1a0();
    virtual void a1a8();
    virtual void a1b0();
    virtual void a1b8();
    virtual void a1c0();
    virtual void a1c8();
    virtual void a1d0();
    virtual void a1d8();
    virtual void a1e0();
    virtual void a1e8();
    virtual void a1f0();
    virtual void a1f8();
    virtual int check_200(int arg);  // +200

    unsigned char pad8[0x2c];
    float reach;              // +34
    unsigned char pad38[0x18];
    unsigned long flags50;    // +50: flag bits, read as (flags50 >> n) & 1 into an int
    struct UnitParts* parts;  // +58
    unsigned char pad60[0x60];
    int target_c0;            // +c0
    unsigned char padc4[0x1c];
    short links[0x3c];        // +e0
    unsigned char pad158[0x304];
    int value45c;             // +45c
    unsigned char pad460[0x38];
    float limit498;           // +498
    int value49c;             // +49c
    unsigned char pad4a0[0x44];
    unsigned short shape4e4;  // +4e4
    unsigned char pad4e6[0x12];
    int target_4f8;           // +4f8
};

class UnitBody;

class Unit {
public:
    virtual void v00();
    virtual void v08();
    virtual UnitActor* actor();  // +10
    virtual void v18();
    virtual void v20();
    virtual UnitBody* body();    // +28
    virtual void v30();
    virtual struct UnitPlace* place();  // +38
    virtual class UnitView* view();  // +40
    virtual UnitState* state();  // +48
};

// What Unit::body() returns.
class UnitBody {
public:
    virtual void b000();
    virtual void b008();
    virtual void b010();
    virtual void b018();
    virtual void b020();
    virtual void b028();
    virtual void b030();
    virtual void b038();
    virtual void b040();
    virtual void b048();
    virtual void b050();
    virtual void b058();
    virtual void b060();
    virtual void b068();
    virtual void b070();
    virtual void b078();
    virtual void b080();
    virtual void b088();
    virtual void b090();
    virtual void b098();
    virtual void b0a0();
    virtual void b0a8();
    virtual void b0b0();
    virtual void b0b8();
    virtual void b0c0();
    virtual void b0c8();
    virtual void b0d0();
    virtual void b0d8();
    virtual void b0e0();
    virtual void b0e8();
    virtual void b0f0();
    virtual void b0f8();
    virtual void b100();
    virtual void b108();
    virtual void b110();
    virtual void b118();
    virtual void b120();
    virtual void b128();
    virtual void b130();
    virtual void b138();
    virtual void b140();
    virtual void b148();
    virtual void b150();
    virtual void b158();
    virtual void b160();
    virtual void b168();
    virtual void b170();
    virtual void b178();
    virtual void link(UnitBody* other);  // +180
};

// The unit table: units by 16-bit id at +138, 0x6d7 of them.
struct UnitTable {
    unsigned char pad0[0x138];
    Unit* units[0x6d7];       // +138

    Unit* unit(short id) { return static_cast<unsigned short>(id) <= 0x6d6 ? units[id] : 0; }
    int give_211dc(short id, int item, unsigned char show, unsigned char notify, unsigned char quiet);
    unsigned char has_22640(struct UnitRef* ref);                            // 0x7100022640
    Unit* by_ref(struct UnitRef* ref);
    Unit* unit_at(long id) { return static_cast<unsigned long>(id) <= 0x6d6 ? units[id] : 0; }

    unsigned char pad37f0[0xf3b00 - 0x37f0];
    struct UnitRoster {
        unsigned int rank(Unit* unit);                                      // 0x710005d4d0
    } roster;                 // +f3b00
};
// Reached through the GOT slot at 0x7100c21690.
extern UnitTable* gUnitTable_c21690;

static inline Unit* find_unit(short id) { return gUnitTable_c21690->unit(id); }

short side_unit_id_db3c(int side);                                          // 0x710000db3c

// Whether a unit (by id), or the unit of a side, can take an actor command.
static inline int unit_can(short id, int cmd) {
    Unit* u = find_unit(id);
    if (!u) return 0;
    IF_UNIT_STATE_ACTIVE(u->state()->id, {
        UnitActor* a = u->actor();
        if (!a) return 0;
        return static_cast<unsigned char>(a->command(cmd));
    });
    return 0;
}
static inline int side_unit_can(int side, int cmd) { return unit_can(side_unit_id_db3c(side), cmd); }

// unit_can with the action outside the test (goto): the original's shape in 3e350.
static inline int unit_can_jump(short id, int cmd) {
    Unit* u = find_unit(id);
    if (!u) return 0;
    IF_UNIT_STATE_ACTIVE(u->state()->id, goto active);
    return 0;
active:
    UnitActor* a = u->actor();
    if (!a) return 0;
    return static_cast<unsigned char>(a->command(cmd));
}
