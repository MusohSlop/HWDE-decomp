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
    ~FrameHeapImpl();                                                       // 0x71005c2c8c
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

// 0x71005c42ec; original file: heap objects, 0x71005c2c78-0x71005c42ec
HeapMutex::~HeapMutex() {}

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
// 0x710053d454; original file: file system objects, 0x710053d304-0x710053e718
// Vtable through the GOT slot at 0x7100c2d2f8.
class FileStream : public Plain_53e718 {
public:
    FileStream();
    ~FileStream() override;

    void* handle;             // +08
    void* buffer;             // +10
    unsigned long size;       // +18
};

FileStream::FileStream() : handle(nullptr), buffer(nullptr), size(0) {}

// Base of three small classes; its constructor (0x71005325e4) is out of line.
class Base_5325e4 {
public:
    Base_5325e4();
    virtual ~Base_5325e4();
    unsigned char pad[0x2c];
};

// 0x7100527bd8; original file: render objects, 0x7100527b08-0x7100527bd8
// Vtable through the GOT slot at 0x7100c2d220.
class RenderPair : public Base_5325e4 {
public:
    RenderPair();
    ~RenderPair() override;

    unsigned char pad34[4];
    void* first;              // +38
    void* second;             // +40
};

RenderPair::RenderPair() : first(nullptr), second(nullptr) {}

// 0x7100527b68; vtable through the GOT slot at 0x7100c2d210.
class RenderCount : public Base_5325e4 {
public:
    RenderCount();
    ~RenderCount() override;

    int count;                // +34
};

RenderCount::RenderCount() : count(0) {}

// 0x7100527b08; vtable through the GOT slot at 0x7100c2d208.
class RenderIndex : public Base_5325e4 {
public:
    RenderIndex();
    ~RenderIndex() override;

    int index;                // +34
};

RenderIndex::RenderIndex() : index(0) {}
// Base whose constructor (0x710041be40) is out of line; its last four bytes are tail padding
// that a derived class reuses.
class Base_41be40 {
public:
    Base_41be40();
    virtual ~Base_41be40();
    unsigned char pad[0x44];
};

// 0x7100434a54; original file: game objects, 0x7100434a54
// Vtable through the GOT slot at 0x7100c2b9f0.
class PairedSlot : public Base_41be40 {
public:
    PairedSlot();
    ~PairedSlot() override;

    int first;                // +4c
    int second;               // +50
};

PairedSlot::PairedSlot() : first(0), second(0) {}

class FrameHeapBase {
public:
    FrameHeapBase();                                                        // 0x71005c2d24
    virtual ~FrameHeapBase();
    void finalize();                                                        // 0x71005c2e54
    unsigned char pad[0x58];
};

// 0x71000464c8; original file: frame heaps, 0x71000464c8
// Vtable through the GOT slot at 0x7100c21e58.
class OwnedFrameHeap : public FrameHeapBase {
public:
    OwnedFrameHeap();
    ~OwnedFrameHeap() override;

    void* owner;              // +60
};

OwnedFrameHeap::OwnedFrameHeap() : owner(nullptr) {}

namespace nn {
namespace os {
struct MutexType;
struct EventType;
void LockMutex(MutexType* mutex);
void UnlockMutex(MutexType* mutex);
void WaitEvent(EventType* event);
void ClearEvent(EventType* event);
void YieldThread();
}  // namespace os
}  // namespace nn

struct MutexOwner {
    unsigned char pad[0x10];
    unsigned char mutex[0x20]; // +10
};

// 0x71005c4bec; original file: heap objects, 0x71005c2c78-0x71005c4bec
struct LockedFrameHeap {
    void finalize();

    void* value0;             // +00
    FrameHeapBase heap;       // +08
    MutexOwner* owner;        // +68
};

void LockedFrameHeap::finalize() {
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(owner->mutex));
    heap.finalize();
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(owner->mutex));
}

// 0x710053c508; original file: file system objects, 0x710053c508
struct LockedCounter {
    int value();

    unsigned char pad[0x20];
    int count;                // +20
    unsigned char pad24[0x94];
    unsigned char mutex[0x20]; // +b8
};

int LockedCounter::value() {
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(mutex));
    int result = count;
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(mutex));
    return result;
}
// 0x7100424a58, 0x710041fe54; original file: game objects, 0x710041be40-0x7100424a58
// Vtables through the GOT slots at 0x7100c2b8a0 and 0x7100c2b860.
class DualSlotA : public Base_41be40 {
public:
    DualSlotA();
    ~DualSlotA() override;

    unsigned char pad4c[4];
    void* first;              // +50
    void* second;             // +58
};

DualSlotA::DualSlotA() : first(nullptr), second(nullptr) {}

class DualSlotB : public Base_41be40 {
public:
    DualSlotB();
    ~DualSlotB() override;

    unsigned char pad4c[4];
    void* first;              // +50
    void* second;             // +58
};

DualSlotB::DualSlotB() : first(nullptr), second(nullptr) {}

// Model base (its constructor is matched elsewhere as 0x71005928c0).
class ModelCore {
public:
    ModelCore();                                                            // 0x71005928c0
    virtual ~ModelCore();
    unsigned char pad[0x1298];
};

// 0x7100553c8c; original file: model classes, 0x7100553c8c
// Vtable through the GOT slot at 0x7100c2d390.
class AttachedModel : public ModelCore {
public:
    AttachedModel();
    ~AttachedModel() override;

    void* attachment;         // +12a0
};

AttachedModel::AttachedModel() : attachment(nullptr) {}

class LightResource {
public:
    ~LightResource();                                                       // 0x71005d27b4
    unsigned char pad[0x110];
};
class PanelBase_316aa4 {
public:
    virtual ~PanelBase_316aa4();                                            // 0x7100316aa4
    unsigned char pad[0x38];
};

// 0x71003000c4; original file: panels, 0x71003000c4
// Vtable through the GOT slot at 0x7100c2ac88.
class ResourcePanel : public PanelBase_316aa4 {
public:
    ~ResourcePanel() override;

    LightResource resource;   // +40
};

ResourcePanel::~ResourcePanel() {}
// 0x710053c4d0; original file: file system objects, 0x710053c4d0-0x710053c508
struct LockedPointer {
    void* value();

    void* owner;              // +00
    void* pointer;            // +08
    unsigned char pad10[0xa8];
    unsigned char mutex[0x20]; // +b8
};

void* LockedPointer::value() {
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(mutex));
    void* result = pointer;
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(mutex));
    return result;
}

// 0x710053b490; original file: file system objects, 0x710053b490
struct LockedQueue {
    bool pending();

    unsigned char mutex[0x3c8]; // +000: the mutex starts the object
    int count;                // +3c8
};

bool LockedQueue::pending() {
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(mutex));
    bool result = count > 0;
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(mutex));
    return result;
}

// Base of two small classes; its constructor (0x71000ade30) is out of line.
class Base_ade30 {
public:
    Base_ade30();
    virtual ~Base_ade30();
    unsigned char pad[0x10];
};

// 0x71000b59e0; vtable through the GOT slot at 0x7100c226d8.
class AdePair : public Base_ade30 {
public:
    AdePair();
    ~AdePair() override;

    void* first;              // +18
    void* second;             // +20
};

AdePair::AdePair() : first(nullptr), second(nullptr) {}

// 0x71000ae67c; vtable through the GOT slot at 0x7100c224d8.
class AdeSingle : public Base_ade30 {
public:
    AdeSingle();
    ~AdeSingle() override;

    void* value;              // +18
};

AdeSingle::AdeSingle() : value(nullptr) {}

// 0x7100527a94; vtable through the GOT slot at 0x7100c2d1f8.
class RenderTriple : public Base_5325e4 {
public:
    RenderTriple();
    ~RenderTriple() override;

    int a;                    // +34
    int b;                    // +38
    int c;                    // +3c
};

RenderTriple::RenderTriple() : a(0), b(0), c(0) {}
// 0x710045d938; original file: heap objects, 0x710045d938
// Vtable through the GOT slot at 0x7100c2bbc0.
class HeapClient : public Plain_5c2c78 {
public:
    explicit HeapClient(void* owner);
    ~HeapClient() override;

    void* owner;              // +08
    void* value10;            // +10
};

HeapClient::HeapClient(void* owner) : owner(owner), value10(nullptr) {}

// 0x710042092c; original file: game objects, 0x710041be40-0x7100424a58
// Vtable through the GOT slot at 0x7100c2b868.
class QuadSlot : public Base_41be40 {
public:
    QuadSlot();
    ~QuadSlot() override;

    unsigned char pad4c[4];
    void* a;                  // +50
    void* b;                  // +58
    void* c;                  // +60
    void* d;                  // +68
};

QuadSlot::QuadSlot() : a(nullptr), b(nullptr), c(nullptr), d(nullptr) {}

class Game {
public:
    void* trophy(unsigned int id);                                          // 0x71002042bc
};
Game* get_game();                                                           // 0x7100204728

// 0x71002f81e0; original file: trophy widgets, 0x71002f81e0-0x71002f8218
struct TrophyWidget {
    void select(int id);
    void show(void* trophy);                                                // 0x71002f8218

    unsigned char pad[8];
    unsigned char selected;   // +08
};

void TrophyWidget::select(int id) {
    selected = id;
    show(get_game()->trophy(id));
}
class Base_7a0c8 {
public:
    Base_7a0c8();                                                           // 0x710007a0c8
    virtual ~Base_7a0c8();
    unsigned char pad[0x50];
};

// 0x71000aa5ec; vtable through the GOT slot at 0x7100c22488.
class Base7a0c8Child : public Base_7a0c8 {
public:
    Base7a0c8Child();
    ~Base7a0c8Child() override;

    void* value58;            // +58
    int value60;              // +60
};

Base7a0c8Child::Base7a0c8Child() : value58(nullptr), value60(0) {}
class Base_5d9e04 {
public:
    Base_5d9e04();                                                          // 0x71005d9e04
    virtual ~Base_5d9e04();
    unsigned char pad[0xd8];
};

struct RingLink {
    RingLink() : prev(this), next(this) {}

    RingLink* prev;
    RingLink* next;
};

// 0x71005db058; original file: layout nodes, 0x71005db058
// Vtable through the GOT slot at 0x7100c2dcf0.
class RingNode : public Base_5d9e04 {
public:
    RingNode();
    ~RingNode() override;

    RingLink ring;            // +e0
    void* valuef0;            // +f0
};

RingNode::RingNode() : valuef0(nullptr) {}

// 0x71005cddf0; original file: layout objects, 0x71005cddf0
struct LockedHolder {
    bool has_value();

    unsigned char pad[0x30];
    void* value;              // +30
    unsigned char pad38[0x10];
    unsigned char mutex[0x20]; // +48
};

bool LockedHolder::has_value() {
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(mutex));
    void* current = value;
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(mutex));
    return current != nullptr;
}

// 0x7100556280; original file: render queues, 0x7100556280
struct LockedCount {
    void bump();

    unsigned char pad[0x180];
    MutexOwner* owner;        // +180
    unsigned char pad188[0xc];
    int count;                // +194
};

void LockedCount::bump() {
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(owner->mutex));
    ++count;
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(owner->mutex));
}

// 0x7100422418; vtable through the GOT slot at 0x7100c2b888.
class SixSlot : public Base_41be40 {
public:
    SixSlot();
    ~SixSlot() override;

    unsigned char pad4c[4];
    void* slots[6];           // +50
};

SixSlot::SixSlot() : slots() {}

// 0x710041b020; vtable through the GOT slot at 0x7100c2b820.
class FiveSlot : public Base_41be40 {
public:
    FiveSlot();
    ~FiveSlot() override;

    unsigned char pad4c[4];
    void* slots[5];           // +50
};

FiveSlot::FiveSlot() : slots() {}
struct LockOwner {
    unsigned char pad[0x10];
    unsigned char mutex[0x20]; // +10
};

// 0x71003cc2d4, 0x71003cc224; original file: shared tasks, 0x71003cc224-0x71003cc2d4
struct LockedTaskState {
    int state();
    unsigned char done();

    LockOwner* owner;         // +00
    unsigned char pad8[0x54];
    int value5c;              // +5c
    unsigned char value60;    // +60
};

int LockedTaskState::state() {
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(owner->mutex));
    int result = value5c;
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(owner->mutex));
    return result;
}

unsigned char LockedTaskState::done() {
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(owner->mutex));
    unsigned char result = value60;
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(owner->mutex));
    return result;
}

class DrawNode {
public:
    void draw(int layer);                                                   // 0x71001e34a0
};

// 0x710038ca78; original file: scene widgets, 0x710038ca78
class NodeWidget {
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
    virtual void apply(void* value);  // +50

    void redraw(void* value);

    DrawNode* node;           // +08
};

void NodeWidget::redraw(void* value) {
    node->draw(0);
    apply(value);
}

struct EffectResource;
class EffectManagerView {
public:
    void attach(EffectResource* resource, void* owner);                    // 0x71001e26dc
};
// Reached through the GOT slot at 0x7100c22a00.
extern EffectManagerView* gEffectManager;

struct SceneSub {
    void create(int id);                                                    // 0x7100386e64
};

// 0x710033340c; original file: scene panels, 0x710033340c
struct ResourceScene {
    void attach();

    unsigned char pad[0x40];
    unsigned char resource[0x110]; // +40
    SceneSub sub;             // +150
};

void ResourceScene::attach() {
    gEffectManager->attach(reinterpret_cast<EffectResource*>(resource), nullptr);
    sub.create(0x41eb);
}
class EffectNodeList {
public:
    void remove(void* node);                                                // 0x71005c3774
    unsigned char pad[0x60];
};

// 0x71005c4fdc; original file: heap objects, 0x71005c2c78-0x71005c4fdc
struct LockedNodeList {
    void remove(void* node);

    void* value0;             // +00
    EffectNodeList list;      // +08
    MutexOwner* owner;        // +68
};

void LockedNodeList::remove(void* node) {
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(owner->mutex));
    list.remove(node);
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(owner->mutex));
}

struct ManagerLock {
    unsigned char pad[0xa0];
    unsigned char mutex[0x20]; // +a0
};
// Reached through the GOT slot at 0x7100c21de8.
extern ManagerLock* gObjectManagerLock;

// 0x71005c43dc; original file: heap objects, 0x71005c2c78-0x71005c43dc
struct ManagedFrameHeap {
    void finalize();

    void* value0;             // +00
    FrameHeapBase heap;       // +08
};

void ManagedFrameHeap::finalize() {
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(gObjectManagerLock->mutex));
    heap.finalize();
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(gObjectManagerLock->mutex));
}

class FlaggedModelCore {
public:
    FlaggedModelCore();                                                     // 0x71005928c0
    virtual ~FlaggedModelCore();
    unsigned char pad[0x1290];
    unsigned short flags;     // +1298
    unsigned char pad129a[6];
};

// 0x7100591690; vtable through the GOT slot at 0x7100c2d758.
class FlaggedModel : public FlaggedModelCore {
public:
    FlaggedModel();
    ~FlaggedModel() override;

    void* value12a0;          // +12a0
};

FlaggedModel::FlaggedModel() : value12a0(nullptr) {
    flags |= 2;
}

// 0x710058fe30; vtable through the GOT slot at 0x7100c2d750.
class TrackedModel : public FlaggedModelCore {
public:
    TrackedModel();
    ~TrackedModel() override;

    unsigned char pad12a0[0x18];
    void* value12b8;          // +12b8
    void* value12c0;          // +12c0
    void* value12c8;          // +12c8
    int value12d0;            // +12d0
};

TrackedModel::TrackedModel() : value12b8(nullptr), value12c0(nullptr), value12c8(nullptr), value12d0(0) {}
struct Record150 {
    unsigned char bytes[0x150];
};

// 0x710057cdc0; original file: records, 0x710057cdc0
// Vtable through the GOT slot at 0x7100c2b760.
// The record sits in a non-virtual base, so it is copied before the vtable pointer is stored.
struct RecordBase {
    explicit RecordBase(const Record150& record) : record(record) {}

    unsigned char pad[8];     // +08
    Record150 record;         // +10
};

class RecordObject : public RecordBase {
public:
    explicit RecordObject(const Record150& record);
    virtual ~RecordObject();

    unsigned char valid;      // +160
    unsigned char dirty;      // +161
};

RecordObject::RecordObject(const Record150& record) : RecordBase(record), valid(1), dirty(1) {}

// 0x710053d978; original file: file system objects, 0x710053d978
struct LockedHandle {
    bool is_open();

    void* handle;             // +00
    unsigned char pad8[0x20];
    unsigned char mutex[0x20]; // +28
};

bool LockedHandle::is_open() {
    nn::os::LockMutex(reinterpret_cast<nn::os::MutexType*>(mutex));
    bool result = handle != nullptr;
    nn::os::UnlockMutex(reinterpret_cast<nn::os::MutexType*>(mutex));
    return result;
}

// 0x710053c1e4; original file: file system objects, 0x710053c1e4
struct EventWaiter {
    void wait();

    unsigned char pad[0xf8];
    unsigned char event[0x28]; // +f8
    unsigned char manual;     // +120
};

void EventWaiter::wait() {
    nn::os::WaitEvent(reinterpret_cast<nn::os::EventType*>(event));
    if (!manual)
        nn::os::ClearEvent(reinterpret_cast<nn::os::EventType*>(event));
}

struct WorkSlot {
    unsigned char pad[0x18];
    volatile int state;       // +18
    unsigned char pad1c[0x284];
};
static_assert(sizeof(WorkSlot) == 0x2a0, "work slot size");

// 0x71004d1920; original file: work queues, 0x71004d1920
struct WorkQueue {
    void wait_idle();

    unsigned char pad[0x44];
    unsigned int current;     // +44
    unsigned char pad48[8];
    WorkSlot* slots;          // +50
};

void WorkQueue::wait_idle() {
    WorkSlot* base = slots;
    WorkSlot* slot = &base[current];
    while (slot->state == 1)
        nn::os::YieldThread();
}