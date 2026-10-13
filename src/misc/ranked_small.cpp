// Small functions picked by tools/rank_targets.py whose callees are all named. They come from
// several game and system source files; each definition names the address region of the
// original file it likely belongs to, for a later split. Names are descriptive placeholders.
// Status: matching/README.md.

// Bases whose constructors are matched in misc/small_families2.cpp.
class Plain_53e718 {
public:
    Plain_53e718();                                                         // 0x710053e718
    virtual ~Plain_53e718();
    virtual void reset();     // +10
};
class Plain_53e630 {
public:
    Plain_53e630();                                                         // 0x710053e630
    virtual ~Plain_53e630();
};
class Plain_5c2c78 {
public:
    Plain_5c2c78();                                                         // 0x71005c2c78
    virtual ~Plain_5c2c78();
};

// 0x710053e410; original file: file system objects, 0x710053d304-0x710053e718
// Vtable through the GOT slot at 0x7100c2d308.
class FileHandle : public Plain_53e718 {
public:
    FileHandle();
    ~FileHandle() override;
    bool open(const char* path, int mode, int flags, void* arg);
    void close();

    void* handle;             // +08
};

FileHandle::FileHandle() : handle(nullptr) {}

class FileSystem {
public:
    int open(const char* path, int mode, int flags, void** handle, void* arg, int extra); // 0x71005374a4
    void close(void** handle, int flags);                                   // 0x71005374ac
};
struct ObjectManager {
    unsigned char pad[0xc8];
    FileSystem* files;        // +c8
};
// Reached through the GOT slot at 0x7100c21de8.
extern ObjectManager* gObjectManager;

// 0x710053e488; original file: file system objects, 0x710053d304-0x710053e718
bool FileHandle::open(const char* path, int mode, int flags, void* arg) {
    reset();
    if (gObjectManager->files->open(path, mode | 6, flags, &handle, arg, 0)) {
        handle = nullptr;
        return false;
    }
    return true;
}

// 0x710053e510; original file: file system objects, 0x710053d304-0x710053e718
void FileHandle::close() {
    if (handle) {
        gObjectManager->files->close(&handle, 0);
        handle = nullptr;
    }
}

// 0x710053d304; original file: file system objects, 0x710053d304-0x710053e718
// Vtable through the GOT slot at 0x7100c2d2f0.
class MemoryStream : public Plain_53e630 {
public:
    MemoryStream();
    ~MemoryStream() override;

    void* data;               // +08
    void* owner;              // +10
    unsigned long size;       // +18
};

MemoryStream::MemoryStream() : data(nullptr), owner(nullptr), size(0) {}

class FrameHeapImpl {
public:
    FrameHeapImpl();                                                        // 0x71005c2d24
    unsigned char pad[0x60];
};

// 0x71005c42b8; original file: heap objects, 0x71005c2c78-0x71005c42b8
// Vtable through the GOT slot at 0x7100c2dba0.
class HeapMutex : public Plain_5c2c78 {
public:
    HeapMutex();
    ~HeapMutex() override;

    FrameHeapImpl heap;       // +08
};

HeapMutex::HeapMutex() {}

inline short zero_short() { return 0; }

// 0x710045ce00; original file: worker/system helpers, 0x710045ce00
short* shared_zero_short() {
    static short value = zero_short();
    return &value;
}

struct SharedState;
SharedState* get_shared_state();                                            // 0x71002aae3c
unsigned char shared_state_exiting(SharedState* state);                     // 0x71002ac7f0
void request_sound(void* player, int id, int a, int b);                     // 0x71003f7c94
// Reached through the GOT slot at 0x7100c2b700.
extern void* gGlobal_c2b700;

// 0x71003f9fac; original file: sound requests, 0x71003f9fac
void request_sound_unless_exiting(int id) {
    if (gGlobal_c2b700 && !shared_state_exiting(get_shared_state()))
        request_sound(gGlobal_c2b700, id, 0, 0);
}

struct BattleSetup {
    BattleSetup() : value0(0), value8(0), value10(0), value18(0), value38(0), slot(-1), count(6) {}

    long value0;              // +00
    long value8;              // +08
    long value10;             // +10
    long value18;             // +18
    unsigned char pad20[0x18];
    long value38;             // +38
    int slot;                 // +40
    int count;                // +44
    int value48;              // +48 (the tail padding after it keeps the object out of the merged block)
};
static_assert(sizeof(BattleSetup) == 0x50, "battle setup size");
// Reached through the GOT slot at 0x7100c22d28.
extern BattleSetup* gBattleSetup;

// 0x710016ef34; original file: battle setup, 0x710016ef34-0x710016f2ac
BattleSetup* get_battle_setup() {
    if (!gBattleSetup) {
        static BattleSetup setup;
        gBattleSetup = &setup;
    }
    return gBattleSetup;
}

class SceneTask {
public:
    SceneTask();                                                            // 0x7100387524
    virtual ~SceneTask();
};

// 0x71002d8e2c; original file: scene tasks, 0x71002d8e2c
// Vtable through the GOT slot at 0x7100c2ab68.
class LargeSceneTask : public SceneTask {
public:
    LargeSceneTask();
    ~LargeSceneTask() override;

    unsigned char pad[0x2d41c];
    int value2d424;           // +2d424
    int value2d428;           // +2d428
    unsigned char value2d42c; // +2d42c
    unsigned char pad2d42d[3];
    long value2d430;          // +2d430
    short value2d438;         // +2d438
    unsigned char value2d43a; // +2d43a
};

LargeSceneTask::LargeSceneTask() {
    value2d424 = -1;
    value2d428 = -1;
    value2d42c = 0;
    value2d43a = 0;
    value2d438 = 0;
    value2d430 = 0;
}
// 0x710053e1b0; original file: file system objects, 0x710053d304-0x710053e718
// Vtable through the GOT slot at 0x7100c2d300.
class FileReader : public Plain_53e630 {
public:
    FileReader();
    ~FileReader() override;

    void* handle;             // +08
};

FileReader::FileReader() : handle(nullptr) {}
unsigned char battle_flag_0();                                              // 0x7100455858
void* load_global_4140a4();                                                 // 0x71004140a4

// 0x7100453638; original file: global queries, 0x7100453590-0x7100453638 (battle_flag_0 is
// called, not inlined, so it is not in misc/helpers.cpp)
unsigned char global_4140a4_check() {
    if (!battle_flag_0() && load_global_4140a4())
        load_global_4140a4();
    return 0;
}