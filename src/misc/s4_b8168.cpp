// A unit task's update (fourth session, 2-copy family b8168): refreshes the body again when its state id passes the
// unit-state test shared by about 55 functions (the switch lowers to a bit test over 0..39; 12/13 and 58/59 are masked
// compares outside it), then continues (0x71000b7614 or 0x71000b7654). UnitTask::update<0> (0x71000b8168), update<1>
// (0x71000b821c). Names are descriptive placeholders.

struct UnitState {
    unsigned char pad0[0x10];
    int id;                   // +10
};

class UnitBody {
public:
    virtual void v00();
    virtual void v08();
    virtual void* refresh();  // +10
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void v40();
    virtual UnitState* state();  // +48
};

struct UnitOwner {
    unsigned char pad0[0x18];
    UnitBody* body;           // +18
};

static inline bool state_active(int st) {
    if (st < 0) return false;
    if (st >= 25 && st != 58 && st != 59) return false;
    switch (st) {
    case 6: case 7: case 9: case 10: case 12: case 13:
    case 16: case 17: case 18: case 19: case 20: case 21: case 39:
        return false;
    }
    return true;
}

class UnitTask {
public:
    template <int Copy> void update();
    void next_b7614();                                                      // 0x71000b7614
    void next_b7654();                                                      // 0x71000b7654

    template <int Copy> void next() {
        if (Copy == 0)
            next_b7614();
        else
            next_b7654();
    }

    void* vtable;
    UnitOwner* owner;         // +08
};

template <int Copy>
void UnitTask::update() {
    if (!owner->body->refresh()) return;
    UnitBody* body = owner->body;
    int st = body->state()->id;
    if (st >= 0 && (st < 25 || !((st != 58) & (st != 59)))) {
        switch (st) {
        case 6: case 7: case 9: case 10:
        case 16: case 17: case 18: case 19: case 20: case 21: case 39:
            break;
        default:
            if ((st != 12) & (st != 13)) body->refresh();
        }
    }
    next<Copy>();
}

// 0x71000b8168
template void UnitTask::update<0>();
// 0x71000b821c
template void UnitTask::update<1>();
