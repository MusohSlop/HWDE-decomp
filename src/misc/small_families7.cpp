// More code families found by tools/family_scan.py, grouped until their source files are
// linked: frame-heap holder teardowns, calls on the shared state's resources, constructors
// that clear one field, and list walks. Within a family the bodies are identical apart from
// the globals and callees they use; classes and functions are named after their address,
// callees after theirs. Status: matching/README.md.

class DefaultHeap {
public:
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

class FrameHeapImpl {
public:
    ~FrameHeapImpl();                                                       // 0x71005c2c8c
    unsigned char pad[0x60];
};

struct SharedState;
struct SharedResources;
SharedState* get_shared_state();                                            // 0x71002aae3c
SharedResources* shared_state_resources(SharedState* state);                // 0x71002ad1dc

// Frame-heap holder teardowns (the shape of 0x7100258824).

// 0x71002473d4
struct FrameHolder_2473d4 {
    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }

    void* buffer;             // +00
    FrameHeapImpl heap;       // +08
};
// Reached through the GOT slot at 0x7100c2a518.
extern FrameHolder_2473d4* gObjectTableA;

void destroy_frame_holder_2473d4() {
    if (gObjectTableA) {
        delete gObjectTableA;
        gObjectTableA = nullptr;
    }
}

// 0x710024870c
struct FrameHolder_24870c {
    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }

    void* buffer;             // +00
    FrameHeapImpl heap;       // +08
};
// Reached through the GOT slot at 0x7100c2a520.
extern FrameHolder_24870c* gGlobal_c2a520;

void destroy_frame_holder_24870c() {
    if (gGlobal_c2a520) {
        delete gGlobal_c2a520;
        gGlobal_c2a520 = nullptr;
    }
}

// 0x710024c89c
struct FrameHolder_24c89c {
    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }

    void* buffer;             // +00
    FrameHeapImpl heap;       // +08
};
// Reached through the GOT slot at 0x7100c2a530.
extern FrameHolder_24c89c* gObjectTableB;

void destroy_frame_holder_24c89c() {
    if (gObjectTableB) {
        delete gObjectTableB;
        gObjectTableB = nullptr;
    }
}


// Calls on the shared state's resources, when there are any.

void resources_call_389218(SharedResources* resources);          // 0x7100389218

void resources_call_387fd8(SharedResources* resources);          // 0x7100387fd8

void resources_call_388ecc(SharedResources* resources);          // 0x7100388ecc

void resources_call_388fcc(SharedResources* resources);          // 0x7100388fcc

void resources_call_389138(SharedResources* resources);          // 0x7100389138

// 0x710000e6b0
void with_resources_e6b0() {
    if (SharedResources* resources = shared_state_resources(get_shared_state()))
        resources_call_389218(resources);
}

// 0x71003c72b0
void with_resources_3c72b0() {
    if (SharedResources* resources = shared_state_resources(get_shared_state()))
        resources_call_387fd8(resources);
}

// 0x71003c7388
void with_resources_3c7388() {
    if (SharedResources* resources = shared_state_resources(get_shared_state()))
        resources_call_388ecc(resources);
}

// 0x71003c73e4
void with_resources_3c73e4() {
    if (SharedResources* resources = shared_state_resources(get_shared_state()))
        resources_call_388fcc(resources);
}

// 0x71003c74e8
void with_resources_3c74e8() {
    if (SharedResources* resources = shared_state_resources(get_shared_state()))
        resources_call_389138(resources);
}

// 0x7100455a18
void with_resources_455a18() {
    if (SharedResources* resources = shared_state_resources(get_shared_state()))
        resources_call_389218(resources);
}


// The same with an argument.

void resources_call_388028(SharedResources* resources, int value);// 0x7100388028

void resources_call_388eec(SharedResources* resources, int value);// 0x7100388eec

void resources_call_389128(SharedResources* resources, int value);// 0x7100389128

void resources_call_3891d0(SharedResources* resources, int value);// 0x71003891d0

// 0x71003c72d4
void with_resources_3c72d4(void* owner, int value) {
    if (SharedResources* resources = shared_state_resources(get_shared_state()))
        resources_call_388028(resources, value);
}

// 0x71003c73ac
void with_resources_3c73ac(void* owner, int value) {
    if (SharedResources* resources = shared_state_resources(get_shared_state()))
        resources_call_388eec(resources, value);
}

// 0x71003c74b0
void with_resources_3c74b0(void* owner, int value) {
    if (SharedResources* resources = shared_state_resources(get_shared_state()))
        resources_call_389128(resources, value);
}

// 0x71003c7588
void with_resources_3c7588(void* owner, int value) {
    if (SharedResources* resources = shared_state_resources(get_shared_state()))
        resources_call_3891d0(resources, value);
}


// Constructors that clear one field after the base constructor.

class ClearBase_41be40 {
public:
    ClearBase_41be40();                                            // 0x710041be40
    virtual ~ClearBase_41be40();
    unsigned char pad[0x48];
};





// 0x710041a4d8; vtable through the GOT slot at 0x7100c2b810
class Cleared_41a4d8 : public ClearBase_41be40 {
public:
    Cleared_41a4d8();
    ~Cleared_41a4d8() override;

    void* value50;            // +50
};

Cleared_41a4d8::Cleared_41a4d8() : value50(nullptr) {}

// 0x7100421768; vtable through the GOT slot at 0x7100c2b880
class Cleared_421768 : public ClearBase_41be40 {
public:
    Cleared_421768();
    ~Cleared_421768() override;

    void* value50;            // +50
};

Cleared_421768::Cleared_421768() : value50(nullptr) {}

// 0x71004251c8; vtable through the GOT slot at 0x7100c2b8b8
class Cleared_4251c8 : public ClearBase_41be40 {
public:
    Cleared_4251c8();
    ~Cleared_4251c8() override;

    void* value50;            // +50
};

Cleared_4251c8::Cleared_4251c8() : value50(nullptr) {}

// 0x710043706c; vtable through the GOT slot at 0x7100c2ba18
class Cleared_43706c : public ClearBase_41be40 {
public:
    Cleared_43706c();
    ~Cleared_43706c() override;

    void* value50;            // +50
};

Cleared_43706c::Cleared_43706c() : value50(nullptr) {}


// Walks over a null-terminated list of entries at +37f0.

void visit_18f8c(void* entry);                                   // 0x7100018f8c

void visit_190b8(void* entry);                                   // 0x71000190b8

void visit_1928c(void* entry);                                   // 0x710001928c

void visit_192e0(void* entry);                                   // 0x71000192e0

// 0x710001fa80
struct BigList_1fa80 {
    void visit_all();

    unsigned char pad[0x37f0];
    void* entries[1];         // +37f0: null-terminated
};

void BigList_1fa80::visit_all() {
    for (void** entry = entries; *entry; ++entry)
        visit_18f8c(*entry);
}

// 0x710001fb30
struct BigList_1fb30 {
    void visit_all();

    unsigned char pad[0x37f0];
    void* entries[1];         // +37f0: null-terminated
};

void BigList_1fb30::visit_all() {
    for (void** entry = entries; *entry; ++entry)
        visit_190b8(*entry);
}

// 0x710001fbe0
struct BigList_1fbe0 {
    void visit_all();

    unsigned char pad[0x37f0];
    void* entries[1];         // +37f0: null-terminated
};

void BigList_1fbe0::visit_all() {
    for (void** entry = entries; *entry; ++entry)
        visit_1928c(*entry);
}

// 0x710001fc18
struct BigList_1fc18 {
    void visit_all();

    unsigned char pad[0x37f0];
    void* entries[1];         // +37f0: null-terminated
};

void BigList_1fc18::visit_all() {
    for (void** entry = entries; *entry; ++entry)
        visit_192e0(*entry);
}
