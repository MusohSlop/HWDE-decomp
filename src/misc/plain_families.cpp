// Small families with identical code (tools/family_scan.py, plain): state steps whose handler runs on
// the owner itself, refresh-then-apply virtual pairs and lookups that fill one of two outputs.
// Functions are named after their address. Status: matching/README.md.

struct OwnState4da0ec {
    void (*handler)(void* self);
    long adjust;              // doubled, as in a member-function pointer
    unsigned char data[0x10];
};
// Reached through the GOT slot at 0x7100c2ceb0.
extern OwnState4da0ec gOwnStates_4da0ec[];
struct SelfMachine4da0ec {
    unsigned char pad[4];
    int state;                // +04
    OwnState4da0ec* current;  // +08
};

// 0x71004da0ec
void self_step_4da0ec(SelfMachine4da0ec* owner) {
    OwnState4da0ec& state = gOwnStates_4da0ec[owner->state];
    state.handler(reinterpret_cast<unsigned char*>(owner) + (state.adjust >> 1));
    owner->current = &gOwnStates_4da0ec[owner->state];
}

struct OwnState4da15c {
    void (*handler)(void* self);
    long adjust;              // doubled, as in a member-function pointer
    unsigned char data[0x10];
};
// Reached through the GOT slot at 0x7100c2cea0.
extern OwnState4da15c gOwnStates_4da15c[];
struct SelfMachine4da15c {
    unsigned char pad[4];
    int state;                // +04
    OwnState4da15c* current;  // +08
};

// 0x71004da15c
void self_step_4da15c(SelfMachine4da15c* owner) {
    OwnState4da15c& state = gOwnStates_4da15c[owner->state];
    state.handler(reinterpret_cast<unsigned char*>(owner) + (state.adjust >> 1));
    owner->current = &gOwnStates_4da15c[owner->state];
}

struct OwnState4da1a0 {
    void (*handler)(void* self);
    long adjust;              // doubled, as in a member-function pointer
    unsigned char data[0x10];
};
// Reached through the GOT slot at 0x7100c2cea8.
extern OwnState4da1a0 gOwnStates_4da1a0[];
struct SelfMachine4da1a0 {
    unsigned char pad[4];
    int state;                // +04
    OwnState4da1a0* current;  // +08
};

// 0x71004da1a0
void self_step_4da1a0(SelfMachine4da1a0* owner) {
    OwnState4da1a0& state = gOwnStates_4da1a0[owner->state];
    state.handler(reinterpret_cast<unsigned char*>(owner) + (state.adjust >> 1));
    owner->current = &gOwnStates_4da1a0[owner->state];
}

struct OwnState4dea74 {
    void (*handler)(void* self);
    long adjust;              // doubled, as in a member-function pointer
    unsigned char data[0x10];
};
// Reached through the GOT slot at 0x7100c2cec8.
extern OwnState4dea74 gOwnStates_4dea74[];
struct SelfMachine4dea74 {
    unsigned char pad[4];
    int state;                // +04
    OwnState4dea74* current;  // +08
};

// 0x71004dea74
void self_step_4dea74(SelfMachine4dea74* owner) {
    OwnState4dea74& state = gOwnStates_4dea74[owner->state];
    state.handler(reinterpret_cast<unsigned char*>(owner) + (state.adjust >> 1));
    owner->current = &gOwnStates_4dea74[owner->state];
}

class RefreshApply {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void refresh();   // +20
    virtual void v28();
    virtual void apply(int value); // +30
};

// 0x71003d769c
void refresh_apply_3d769c(RefreshApply* object, int value) {
    object->refresh();
    object->apply(value);
}

// 0x71003d7e9c
void refresh_apply_3d7e9c(RefreshApply* object, int value) {
    object->refresh();
    object->apply(value);
}

// 0x71003d9010
void refresh_apply_3d9010(RefreshApply* object, int value) {
    object->refresh();
    object->apply(value);
}

// 0x71003da08c
void refresh_apply_3da08c(RefreshApply* object, int value) {
    object->refresh();
    object->apply(value);
}

struct LookupService;
// Reached through the GOT slot at 0x7100c216f0.
extern LookupService* gLookupService;

void lookup_6e00c(LookupService* service, int a, int b, int* first, int* second); // 0x710006e00c

// 0x710006ec7c
int lookup_first_6ec7c(int a, int b) {
    int value = -1;
    lookup_6e00c(gLookupService, a, b, &value, nullptr);
    return value;
}

void lookup_6e070(LookupService* service, int a, int b, int* first, int* second); // 0x710006e070

// 0x710006ed14
int lookup_first_6ed14(int a, int b) {
    int value = -1;
    lookup_6e070(gLookupService, a, b, &value, nullptr);
    return value;
}

void lookup_6e0b0(LookupService* service, int a, int b, int* first, int* second); // 0x710006e0b0

// 0x710006edac
int lookup_first_6edac(int a, int b) {
    int value = -1;
    lookup_6e0b0(gLookupService, a, b, &value, nullptr);
    return value;
}


// 0x710006ecc8
int lookup_second_6ecc8(int a, int b) {
    int value = -1;
    lookup_6e00c(gLookupService, a, b, nullptr, &value);
    return value;
}


// 0x710006ed60
int lookup_second_6ed60(int a, int b) {
    int value = -1;
    lookup_6e070(gLookupService, a, b, nullptr, &value);
    return value;
}


// 0x710006edf8
int lookup_second_6edf8(int a, int b) {
    int value = -1;
    lookup_6e0b0(gLookupService, a, b, nullptr, &value);
    return value;
}
