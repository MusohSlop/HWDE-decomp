// More code families found by tools/family_scan.py, grouped until their source files are
// linked: singleton deletes and creations on the default heap, command checks, and calls made
// under the object manager's lock. Within a family the bodies are identical apart from the
// globals and callees they use; classes and functions are named after their address, callees
// after theirs. Status: matching/README.md.

class DefaultHeap {
public:
    void* allocate(unsigned long alignment, unsigned long size, unsigned char lock,
                   unsigned char keep);                                     // 0x710045c458
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

namespace nn {
namespace os {
struct MutexType;
void LockMutex(MutexType* mutex);
void UnlockMutex(MutexType* mutex);
}  // namespace os
}  // namespace nn

struct ObjectManager {
    unsigned char pad[0xa0];
    unsigned char mutex[0x20];   // +a0
};
// Reached through the GOT slot at 0x7100c21de8.
extern ObjectManager* gObjectManager;

class CheckTarget {
public:
    virtual void v000();
    virtual void v008();
    virtual void v010();
    virtual void v018();
    virtual void v020();
    virtual void v028();
    virtual void v030();
    virtual void v038();
    virtual void v040();
    virtual void v048();
    virtual void v050();
    virtual void v058();
    virtual void v060();
    virtual void v068();
    virtual void v070();
    virtual void v078();
    virtual void v080();
    virtual void v088();
    virtual void v090();
    virtual void v098();
    virtual void v0a0();
    virtual void v0a8();
    virtual void v0b0();
    virtual void v0b8();
    virtual void v0c0();
    virtual void v0c8();
    virtual void v0d0();
    virtual void v0d8();
    virtual void v0e0();
    virtual void v0e8();
    virtual void v0f0();
    virtual void v0f8();
    virtual void v100();
    virtual void v108();
    virtual void v110();
    virtual void v118();
    virtual void v120();
    virtual void v128();
    virtual void v130();
    virtual void v138();
    virtual void v140();
    virtual void v148();
    virtual void v150();
    virtual void v158();
    virtual void v160();
    virtual void v168();
    virtual void v170();
    virtual void v178();
    virtual void v180();
    virtual void v188();
    virtual void v190();
    virtual void v198();
    virtual void v1a0();
    virtual void v1a8();
    virtual void v1b0();
    virtual void v1b8();
    virtual void v1c0();
    virtual void v1c8();
    virtual void v1d0();
    virtual void v1d8();
    virtual void v1e0();
    virtual void v1e8();
    virtual void v1f0();
    virtual void v1f8();
    virtual void v200();
    virtual void v208();
    virtual void v210();
    virtual void v218();
    virtual void v220();
    virtual void v228();
    virtual void v230();
    virtual void v238();
    virtual void v240();
    virtual void v248();
    virtual void v250();
    virtual void v258();
    virtual void v260();
    virtual void v268();
    virtual void v270();
    virtual void v278();
    virtual void v280();
    virtual void v288();
    virtual void v290();
    virtual void v298();
    virtual void v2a0();
    virtual void v2a8();
    virtual void v2b0();
    virtual void v2b8();
    virtual void v2c0();
    virtual void v2c8();
    virtual void v2d0();
    virtual void v2d8();
    virtual void v2e0();
    virtual void v2e8();
    virtual void v2f0();
    virtual void v2f8();
    virtual void v300();
    virtual void v308();
    virtual void v310();
    virtual void v318();
    virtual void v320();
    virtual void v328();
    virtual void v330();
    virtual void v338();
    virtual void v340();
    virtual void v348();
    virtual void v350();
    virtual void v358();
    virtual void v360();
    virtual void v368();
    virtual void v370();
    virtual void v378();
    virtual void v380();
    virtual void v388();
    virtual void v390();
    virtual void v398();
    virtual void v3a0();
    virtual void v3a8();
    virtual void v3b0();
    virtual void v3b8();
    virtual void v3c0();
    virtual void v3c8();
    virtual void v3d0();
    virtual void v3d8();
    virtual void v3e0();
    virtual int command();    // +3e8
};
class CheckPart {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void v40();
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void v60();
    virtual void v68();
    virtual void v70();
    virtual int pending();    // +78
};

// Singleton deletes: run the destructor and return the object to the default heap.

// 0x7100189448
class Deletable_189448 {
public:
    ~Deletable_189448();                                              // 0x7100188838

    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }
};
// Reached through the GOT slot at 0x7100c216e8.
extern Deletable_189448* gShop;

void delete_singleton_189448() {
    if (gShop) {
        delete gShop;
        gShop = nullptr;
    }
}

// 0x71003d2f8c
class Deletable_3d2f8c {
public:
    ~Deletable_3d2f8c();                                              // 0x71003d23a8

    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }
};
// Reached through the GOT slot at 0x7100c2b5e8.
extern Deletable_3d2f8c* gGlobal_c2b5e8;

void delete_singleton_3d2f8c() {
    if (gGlobal_c2b5e8) {
        delete gGlobal_c2b5e8;
        gGlobal_c2b5e8 = nullptr;
    }
}

// 0x71004449a4
class Deletable_4449a4 {
public:
    ~Deletable_4449a4();                                              // 0x71004446b8

    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }
};
// Reached through the GOT slot at 0x7100c2ba80.
extern Deletable_4449a4* gGlobal_c2ba80;

void delete_singleton_4449a4() {
    if (gGlobal_c2ba80) {
        delete gGlobal_c2ba80;
        gGlobal_c2ba80 = nullptr;
    }
}

// 0x71004585ec
class Deletable_4585ec {
public:
    ~Deletable_4585ec();                                              // 0x71004583b8

    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }
};
// Reached through the GOT slot at 0x7100c2bb48.
extern Deletable_4585ec* gGlobal_c2bb48;

void delete_singleton_4585ec() {
    if (gGlobal_c2bb48) {
        delete gGlobal_c2bb48;
        gGlobal_c2bb48 = nullptr;
    }
}


// Singleton creations: an eight-byte record cleared on creation.
struct NullRecord {
    void* value;
};

// Reached through the GOT slot at 0x7100c2af58.
extern NullRecord* gGlobal_c2af58;

// Reached through the GOT slot at 0x7100c2a9c8.
extern NullRecord* gGlobal_c2a9c8;

// Reached through the GOT slot at 0x7100c2ada0.
extern NullRecord* gGlobal_c2ada0;

// Reached through the GOT slot at 0x7100c2bb30.
extern NullRecord* gGlobal_c2bb30;

// 0x71003799b8
void create_record_3799b8() {
    if (!gGlobal_c2af58) {
        NullRecord* record = static_cast<NullRecord*>(get_default_heap()->allocate(0x10, 8, 1, 0));
        record->value = nullptr;
        gGlobal_c2af58 = record;
    }
}

// 0x710037ab94
void create_record_37ab94() {
    if (!gGlobal_c2a9c8) {
        NullRecord* record = static_cast<NullRecord*>(get_default_heap()->allocate(0x10, 8, 1, 0));
        record->value = nullptr;
        gGlobal_c2a9c8 = record;
    }
}

// 0x710037acd0
void create_record_37acd0() {
    if (!gGlobal_c2ada0) {
        NullRecord* record = static_cast<NullRecord*>(get_default_heap()->allocate(0x10, 8, 1, 0));
        record->value = nullptr;
        gGlobal_c2ada0 = record;
    }
}

// 0x7100451548
void create_record_451548() {
    if (!gGlobal_c2bb30) {
        NullRecord* record = static_cast<NullRecord*>(get_default_heap()->allocate(0x10, 8, 1, 0));
        record->value = nullptr;
        gGlobal_c2bb30 = record;
    }
}


// Command checks: run the command, then report whether the part at +100 has nothing pending.

// 0x7100026d4c
struct CheckHost_26d4c : CheckTarget {
    bool idle();

    unsigned char pad[0xf8];
    CheckPart* part_storage[1]; // +100: the part object starts here
};

bool CheckHost_26d4c::idle() {
    CheckPart* part = reinterpret_cast<CheckPart*>(part_storage);
    command();
    return part->pending() == 0;
}

// 0x710002a6d0
struct CheckHost_2a6d0 : CheckTarget {
    bool idle();

    unsigned char pad[0xf8];
    CheckPart* part_storage[1]; // +100: the part object starts here
};

bool CheckHost_2a6d0::idle() {
    CheckPart* part = reinterpret_cast<CheckPart*>(part_storage);
    command();
    return part->pending() == 0;
}

// 0x71000ca6d8
struct CheckHost_ca6d8 : CheckTarget {
    bool idle();

    unsigned char pad[0xf8];
    CheckPart* part_storage[1]; // +100: the part object starts here
};

bool CheckHost_ca6d8::idle() {
    CheckPart* part = reinterpret_cast<CheckPart*>(part_storage);
    command();
    return part->pending() == 0;
}

// 0x71000ccb50
struct CheckHost_ccb50 : CheckTarget {
    bool idle();

    unsigned char pad[0xf8];
    CheckPart* part_storage[1]; // +100: the part object starts here
};

bool CheckHost_ccb50::idle() {
    CheckPart* part = reinterpret_cast<CheckPart*>(part_storage);
    command();
    return part->pending() == 0;
}


// Calls made under the object manager's lock.

void* locked_call_5c2f18(void* list);                              // 0x71005c2f18

void* locked_call_5c2f5c(void* list);                              // 0x71005c2f5c

void* locked_call_5c2fd0(void* list);                              // 0x71005c2fd0

void* locked_call_5c3a14(void* list);                              // 0x71005c3a14

// 0x71005c441c
struct Locked_5c441c {
    void* fetch();

    void* owner;              // +00
    unsigned char list[8];    // +08
};

void* Locked_5c441c::fetch() {
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(gObjectManager->mutex));
    void* result = locked_call_5c2f18(list);
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(gObjectManager->mutex));
    return result;
}

// 0x71005c4468
struct Locked_5c4468 {
    void* fetch();

    void* owner;              // +00
    unsigned char list[8];    // +08
};

void* Locked_5c4468::fetch() {
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(gObjectManager->mutex));
    void* result = locked_call_5c2f5c(list);
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(gObjectManager->mutex));
    return result;
}

// 0x71005c4510
struct Locked_5c4510 {
    void* fetch();

    void* owner;              // +00
    unsigned char list[8];    // +08
};

void* Locked_5c4510::fetch() {
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(gObjectManager->mutex));
    void* result = locked_call_5c2fd0(list);
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(gObjectManager->mutex));
    return result;
}

// 0x71005c48a8
struct Locked_5c48a8 {
    void* fetch();

    void* owner;              // +00
    unsigned char list[8];    // +08
};

void* Locked_5c48a8::fetch() {
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(gObjectManager->mutex));
    void* result = locked_call_5c3a14(list);
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(gObjectManager->mutex));
    return result;
}
