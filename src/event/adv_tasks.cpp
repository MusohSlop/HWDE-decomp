// Matching candidates for Adventure Mode task constructors and teardown (0x71002877f4,
// 0x7100288e7c, 0x71002906dc, 0x7100290778). Names are descriptive placeholders.
// Status: matching/README.md.

class DefaultHeap {
public:
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

class SceneTask {
public:
    SceneTask();                                                            // 0x7100387524
    virtual ~SceneTask();
};

class DialogTask {
public:
    DialogTask();                                                           // 0x71003892d8
    virtual ~DialogTask();
};

class SaveTask : public DialogTask {
public:
    SaveTask();                                                             // 0x71002877f4
    ~SaveTask();

    unsigned char pad8[0x2d41c];
    int value2d424;           // +2d424
    int value2d428;           // +2d428
    int value2d42c;           // +2d42c
    void* query;              // +2d430
    long value2d438;          // +2d438
};
static_assert(sizeof(SaveTask) == 0x2d440, "save task size");

SaveTask::SaveTask() {
    query = nullptr;
    value2d424 = 0;
    value2d428 = 0;
    value2d42c = 4;
    value2d438 = 0;
}

class ResultTask : public SceneTask {
public:
    ResultTask();                                                           // 0x71002906dc
    ~ResultTask();
    void prepare();                                                         // 0x7100290778

    unsigned char pad8[0x2d420];
    long value2d428;          // +2d428
    int state;                // +2d430
    int value2d434;           // +2d434
    unsigned char pad2d438[8];
};
static_assert(sizeof(ResultTask) == 0x2d440, "result task size");

ResultTask::ResultTask() {
    value2d434 = -1;
    value2d428 = 0;
    state = 0;
}

void create_menu_board();                                                   // 0x7100283dc4
void register_resource_callback(void* callback, void (*completion)(int, unsigned int),
                                unsigned int flags);                        // 0x7100258b0c
// Result resource request, reached through the GOT slot at 0x7100c2a878.
extern unsigned char gResultRequest[];

void ResultTask::prepare() {
    state = 0;
    create_menu_board();
    register_resource_callback(gResultRequest, nullptr, 0x20);
}

class LayoutGroup {
public:
    ~LayoutGroup();                                                         // 0x71005d27b4
    unsigned char pad[0x120];
};

class BoardCursor {
public:
    ~BoardCursor() { finalize(); }
    void finalize();                                                        // 0x7100288be0

    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }

    unsigned char pad[0x160];
    LayoutGroup groups[3];    // +160
};
// Reached through the GOT slot at 0x7100c2a778.
extern BoardCursor* gBoardCursor;

void destroy_board_cursor() {
    if (gBoardCursor) {
        gBoardCursor->finalize();
        delete gBoardCursor;
        gBoardCursor = nullptr;
    }
}

class LightResource {
public:
    ~LightResource();                                                       // 0x71005d27b4
    unsigned char pad[0x110];
};

struct LayoutRoot {
    unsigned char pad[0x10];
    unsigned char root[1];    // +10
};
struct ResourceLoaderView {
    unsigned char pad[0x2af8];
    LayoutRoot* layout;       // +2af8
};
// Reached through the GOT slot at 0x7100c21db0.
extern ResourceLoaderView* gResourceLoader;

static inline void* layout_root() {
    return gResourceLoader ? gResourceLoader->layout->root : nullptr;
}

// Layout handle; its vtable lives in the effect manager unit (GOT 0x7100c22f00).
class LayoutHandle {
public:
    virtual ~LayoutHandle() { release(layout_root()); }
    virtual void v10();
    virtual void release(void* root); // +18

    long id;                  // +08
    short a;                  // +10
    short b;                  // +12
};

class BoardUnits {
public:
    ~BoardUnits() { finalize(); }
    void finalize();                                                        // 0x710029194c

    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }

    unsigned char pad[0x150];
    LightResource resources[2];   // +150
    unsigned char pad370[0x1198];
    LayoutHandle handle;          // +1508
};
// Reached through the GOT slot at 0x7100c2a780.
extern BoardUnits* gBoardUnits;

void destroy_board_units() {
    if (gBoardUnits) {
        gBoardUnits->finalize();
        delete gBoardUnits;
        gBoardUnits = nullptr;
    }
}
