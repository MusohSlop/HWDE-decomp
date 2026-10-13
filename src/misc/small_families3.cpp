// Further small code families found by tools/family_scan.py, grouped until their source files
// are linked: getter forwarders with two arguments, paired calls on a global, walks over a
// null-terminated list, and manager lookups. Within a family the bodies are identical apart
// from the globals and callees they use; functions are named after their address, callees
// after theirs. Status: matching/README.md.

// Getter forwarders with two arguments.

void* fetch_455ebc();                                               // 0x7100455ebc

void apply2_4579c8(void* object, int a, int b);                 // 0x71004579c8

void apply2_4579fc(void* object, int a, int b);                 // 0x71004579fc

void apply2_457a40(void* object, int a, int b);                 // 0x7100457a40

void apply2_457fb8(void* object, int a, int b);                 // 0x7100457fb8

void* fetch_425dd0();                                               // 0x7100425dd0

void apply2_42727c(void* object, int a, int b);                 // 0x710042727c

void apply2_427330(void* object, int a, int b);                 // 0x7100427330

void apply2_4272b8(void* object, int a, int b);                 // 0x71004272b8

void apply2_4273d0(void* object, int a, int b);                 // 0x71004273d0

// 0x7100452b58
void forward2_452b58(int a, int b) {
    apply2_4579c8(fetch_455ebc(), a, b);
}

// 0x7100452b84
void forward2_452b84(int a, int b) {
    apply2_4579fc(fetch_455ebc(), a, b);
}

// 0x7100452bb0
void forward2_452bb0(int a, int b) {
    apply2_457a40(fetch_455ebc(), a, b);
}

// 0x7100453480
void forward2_453480(int a, int b) {
    apply2_457fb8(fetch_455ebc(), a, b);
}

// 0x7100453df4
void forward2_453df4(int a, int b) {
    apply2_42727c(fetch_425dd0(), a, b);
}

// 0x7100453e20
void forward2_453e20(int a, int b) {
    apply2_427330(fetch_425dd0(), a, b);
}

// 0x7100453ea0
void forward2_453ea0(int a, int b) {
    apply2_4272b8(fetch_425dd0(), a, b);
}

// 0x7100453fd8
void forward2_453fd8(int a, int b) {
    apply2_4273d0(fetch_425dd0(), a, b);
}


// Two calls on the object held in a global.

// Reached through the GOT slot at 0x7100c22058.
extern void* gGlobal_c22058;

void step_5f5d8(void* object);                                   // 0x710005f5d8

void step_5fcb0(void* object);                                   // 0x710005fcb0

void step_5fcbc(void* object);                                   // 0x710005fcbc

void step_5f794(void* object);                                   // 0x710005f794

void step_5fd04(void* object);                                   // 0x710005fd04

void step_60448(void* object);                                   // 0x7100060448

void step_6090c(void* object);                                   // 0x710006090c

void step_6018c(void* object);                                   // 0x710006018c

void step_60990(void* object);                                   // 0x7100060990

void step_61108(void* object);                                   // 0x7100061108

void step_61188(void* object);                                   // 0x7100061188

void step_60c2c(void* object);                                   // 0x7100060c2c

// Reached through the GOT slot at 0x7100c22d58.
extern void* gGlobal_c22d58;

void step_3ece58(void* object);                                   // 0x71003ece58

void step_3ed104(void* object);                                   // 0x71003ed104

// 0x710006e774
void two_steps_6e774() {
    step_5f5d8(gGlobal_c22058);
    step_5fcb0(gGlobal_c22058);
}

// 0x710006e7a0
void two_steps_6e7a0() {
    step_5fcbc(gGlobal_c22058);
    step_5f794(gGlobal_c22058);
}

// 0x710006e7cc
void two_steps_6e7cc() {
    step_5fd04(gGlobal_c22058);
    step_60448(gGlobal_c22058);
}

// 0x710006e7f8
void two_steps_6e7f8() {
    step_6090c(gGlobal_c22058);
    step_6018c(gGlobal_c22058);
}

// 0x710006e824
void two_steps_6e824() {
    step_60990(gGlobal_c22058);
    step_61108(gGlobal_c22058);
}

// 0x710006e850
void two_steps_6e850() {
    step_61188(gGlobal_c22058);
    step_60c2c(gGlobal_c22058);
}

// 0x71003e77a4
void two_steps_3e77a4() {
    step_3ece58(gGlobal_c22d58);
    step_3ed104(gGlobal_c22d58);
}


// Walks over a null-terminated list of entries at +18.

void visit_5270c(void* entry);                                   // 0x710005270c

void visit_52764(void* entry);                                   // 0x7100052764

void visit_5277c(void* entry);                                   // 0x710005277c

void visit_52788(void* entry);                                   // 0x7100052788

void visit_52794(void* entry);                                   // 0x7100052794

void visit_527a0(void* entry);                                   // 0x71000527a0

// 0x710005bd8c
struct EntryList_5bd8c {
    void visit_all();

    unsigned char pad[0x18];
    void* entries[1];         // +18: null-terminated
};

void EntryList_5bd8c::visit_all() {
    for (void** entry = entries; *entry; ++entry)
        visit_5270c(*entry);
}

// 0x710005c70c
struct EntryList_5c70c {
    void visit_all();

    unsigned char pad[0x18];
    void* entries[1];         // +18: null-terminated
};

void EntryList_5c70c::visit_all() {
    for (void** entry = entries; *entry; ++entry)
        visit_52764(*entry);
}

// 0x710005c78c
struct EntryList_5c78c {
    void visit_all();

    unsigned char pad[0x18];
    void* entries[1];         // +18: null-terminated
};

void EntryList_5c78c::visit_all() {
    for (void** entry = entries; *entry; ++entry)
        visit_5277c(*entry);
}

// 0x710005c7c0
struct EntryList_5c7c0 {
    void visit_all();

    unsigned char pad[0x18];
    void* entries[1];         // +18: null-terminated
};

void EntryList_5c7c0::visit_all() {
    for (void** entry = entries; *entry; ++entry)
        visit_52788(*entry);
}

// 0x710005c7f4
struct EntryList_5c7f4 {
    void visit_all();

    unsigned char pad[0x18];
    void* entries[1];         // +18: null-terminated
};

void EntryList_5c7f4::visit_all() {
    for (void** entry = entries; *entry; ++entry)
        visit_52794(*entry);
}

// 0x710005c828
struct EntryList_5c828 {
    void visit_all();

    unsigned char pad[0x18];
    void* entries[1];         // +18: null-terminated
};

void EntryList_5c828::visit_all() {
    for (void** entry = entries; *entry; ++entry)
        visit_527a0(*entry);
}


// Manager lookups: resolve a key through the manager's index, then query the manager.
// The manager pointer is a hidden global read directly (not through the GOT).

struct Manager;
extern Manager* gManager_c47f08 __attribute__((visibility("hidden")));

void* resolve_497cdc(void* index, void* key);                    // 0x7100497cdc

int query_1daea4(Manager* manager, void* entry, int a, int b);  // 0x71001daea4

void* resolve_497d54(void* index, void* key);                    // 0x7100497d54

void* resolve_497dcc(void* index, void* key);                    // 0x7100497dcc

void* resolve_497ebc(void* index, void* key);                    // 0x7100497ebc

void* resolve_497f64(void* index, void* key);                    // 0x7100497f64

// 0x71001db834
int manager_lookup_1db834(void* key, int a, int b) {
    Manager* manager = gManager_c47f08;
    if (!manager)
        return -1;
    return query_1daea4(manager, resolve_497cdc(reinterpret_cast<void**>(manager)[1], key), a, b);
}

// 0x71001db89c
int manager_lookup_1db89c(void* key, int a, int b) {
    Manager* manager = gManager_c47f08;
    if (!manager)
        return -1;
    return query_1daea4(manager, resolve_497d54(reinterpret_cast<void**>(manager)[1], key), a, b);
}

// 0x71001db9e8
int manager_lookup_1db9e8(void* key, int a, int b) {
    Manager* manager = gManager_c47f08;
    if (!manager)
        return -1;
    return query_1daea4(manager, resolve_497dcc(reinterpret_cast<void**>(manager)[1], key), a, b);
}

// 0x71001dba50
int manager_lookup_1dba50(void* key, int a, int b) {
    Manager* manager = gManager_c47f08;
    if (!manager)
        return -1;
    return query_1daea4(manager, resolve_497ebc(reinterpret_cast<void**>(manager)[1], key), a, b);
}

// 0x71001dbab8
int manager_lookup_1dbab8(void* key, int a, int b) {
    Manager* manager = gManager_c47f08;
    if (!manager)
        return -1;
    return query_1daea4(manager, resolve_497f64(reinterpret_cast<void**>(manager)[1], key), a, b);
}
