// State-machine steps found by tools/family_scan.py --immediates: each calls the current state's
// handler on the machine part of its owner, then points the owner at the state's table entry, which
// the handler may have changed. The table keeps each handler as a function and a this-adjustment
// stored doubled (the layout of a member-function pointer on this target, without the virtual bit,
// which the original never tests). They differ only
// in the layout and the table; types and functions are named after their address.
// Status: matching/README.md.

struct Machine4d9714 {
    int value;
};
struct State4d9714 {
    void (*handler)(void* self);
    long adjust;
    unsigned char data[0x10];
};
// Reached through the GOT slot at 0x7100c2cea8.
extern State4d9714 gStates_4d9714[];
struct StateOwner4d9714 {
    unsigned char pad[0x10];
    Machine4d9714 machine;   // +10
    int state;                // +14
    State4d9714* current;  // +18
};

// 0x71004d9714
void step_4d9714(StateOwner4d9714* owner) {
    State4d9714& state = gStates_4d9714[owner->state];
    state.handler(reinterpret_cast<unsigned char*>(owner) + (state.adjust >> 1) + 0x10);
    owner->current = &gStates_4d9714[owner->state];
}

struct Machine4d9890 {
    int value;
};
struct State4d9890 {
    void (*handler)(void* self);
    long adjust;
    unsigned char data[0x10];
};
// Reached through the GOT slot at 0x7100c2ceb0.
extern State4d9890 gStates_4d9890[];
struct StateOwner4d9890 {
    unsigned char pad[0x10];
    Machine4d9890 machine;   // +10
    int state;                // +14
    State4d9890* current;  // +18
};

// 0x71004d9890
void step_4d9890(StateOwner4d9890* owner) {
    State4d9890& state = gStates_4d9890[owner->state];
    state.handler(reinterpret_cast<unsigned char*>(owner) + (state.adjust >> 1) + 0x10);
    owner->current = &gStates_4d9890[owner->state];
}

struct Machine4d9d0c {
    int value;
};
struct State4d9d0c {
    void (*handler)(void* self);
    long adjust;
    unsigned char data[0x10];
};
// Reached through the GOT slot at 0x7100c2ceb0.
extern State4d9d0c gStates_4d9d0c[];
struct StateOwner4d9d0c {
    unsigned char pad[0x10];
    Machine4d9d0c machine;   // +10
    int state;                // +14
    State4d9d0c* current;  // +18
};

// 0x71004d9d0c
void step_4d9d0c(StateOwner4d9d0c* owner) {
    State4d9d0c& state = gStates_4d9d0c[owner->state];
    state.handler(reinterpret_cast<unsigned char*>(owner) + (state.adjust >> 1) + 0x10);
    owner->current = &gStates_4d9d0c[owner->state];
}

struct Machine4da240 {
    int value;
};
struct State4da240 {
    void (*handler)(void* self);
    long adjust;
    unsigned char data[0x10];
};
// Reached through the GOT slot at 0x7100c2cea8.
extern State4da240 gStates_4da240[];
struct StateOwner4da240 {
    unsigned char pad[0x10];
    Machine4da240 machine;   // +10
    int state;                // +14
    State4da240* current;  // +18
};

// 0x71004da240
void step_4da240(StateOwner4da240* owner) {
    State4da240& state = gStates_4da240[owner->state];
    state.handler(reinterpret_cast<unsigned char*>(owner) + (state.adjust >> 1) + 0x10);
    owner->current = &gStates_4da240[owner->state];
}

struct Machine4da9e0 {
    int value;
};
struct State4da9e0 {
    void (*handler)(void* self);
    long adjust;
    unsigned char data[0x10];
};
// Reached through the GOT slot at 0x7100c2cea8.
extern State4da9e0 gStates_4da9e0[];
struct StateOwner4da9e0 {
    unsigned char pad[0x20];
    Machine4da9e0 machine;   // +20
    int state;                // +24
    State4da9e0* current;  // +28
};

// 0x71004da9e0
void step_4da9e0(StateOwner4da9e0* owner) {
    State4da9e0& state = gStates_4da9e0[owner->state];
    state.handler(reinterpret_cast<unsigned char*>(owner) + (state.adjust >> 1) + 0x20);
    owner->current = &gStates_4da9e0[owner->state];
}

struct Machine4dacb0 {
    int value;
};
struct State4dacb0 {
    void (*handler)(void* self);
    long adjust;
    unsigned char data[0x10];
};
// Reached through the GOT slot at 0x7100c2cea8.
extern State4dacb0 gStates_4dacb0[];
struct StateOwner4dacb0 {
    unsigned char pad[0x20];
    Machine4dacb0 machine;   // +20
    int state;                // +24
    State4dacb0* current;  // +28
};

// 0x71004dacb0
void step_4dacb0(StateOwner4dacb0* owner) {
    State4dacb0& state = gStates_4dacb0[owner->state];
    state.handler(reinterpret_cast<unsigned char*>(owner) + (state.adjust >> 1) + 0x20);
    owner->current = &gStates_4dacb0[owner->state];
}

struct Machine4dbdc4 {
    int value;
};
struct State4dbdc4 {
    void (*handler)(void* self);
    long adjust;
    unsigned char data[0x10];
};
// Reached through the GOT slot at 0x7100c2cea8.
extern State4dbdc4 gStates_4dbdc4[];
struct StateOwner4dbdc4 {
    unsigned char pad[0x20];
    Machine4dbdc4 machine;   // +20
    int state;                // +24
    State4dbdc4* current;  // +28
};

// 0x71004dbdc4
void step_4dbdc4(StateOwner4dbdc4* owner) {
    State4dbdc4& state = gStates_4dbdc4[owner->state];
    state.handler(reinterpret_cast<unsigned char*>(owner) + (state.adjust >> 1) + 0x20);
    owner->current = &gStates_4dbdc4[owner->state];
}

struct Machine4dd61c {
    int value;
};
struct State4dd61c {
    void (*handler)(void* self);
    long adjust;
    unsigned char data[0x10];
};
// Reached through the GOT slot at 0x7100c2cec8.
extern State4dd61c gStates_4dd61c[];
struct StateOwner4dd61c {
    unsigned char pad[0x10];
    Machine4dd61c machine;   // +10
    int state;                // +14
    State4dd61c* current;  // +18
};

// 0x71004dd61c
void step_4dd61c(StateOwner4dd61c* owner) {
    State4dd61c& state = gStates_4dd61c[owner->state];
    state.handler(reinterpret_cast<unsigned char*>(owner) + (state.adjust >> 1) + 0x10);
    owner->current = &gStates_4dd61c[owner->state];
}

struct Machine4df4d8 {
    int value;
};
struct State4df4d8 {
    void (*handler)(void* self);
    long adjust;
    unsigned char data[0x10];
};
// Reached through the GOT slot at 0x7100c2cec0.
extern State4df4d8 gStates_4df4d8[];
struct StateOwner4df4d8 {
    unsigned char pad[0x20];
    Machine4df4d8 machine;   // +20
    int state;                // +24
    State4df4d8* current;  // +28
};

// 0x71004df4d8
void step_4df4d8(StateOwner4df4d8* owner) {
    State4df4d8& state = gStates_4df4d8[owner->state];
    state.handler(reinterpret_cast<unsigned char*>(owner) + (state.adjust >> 1) + 0x20);
    owner->current = &gStates_4df4d8[owner->state];
}
