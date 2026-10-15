// Small destructors and constructors written by hand (third session), second unit. Names are descriptive
// placeholders. Status: matching/README.md.

extern "C" void* memset(void*, int, unsigned long);

namespace nn {
namespace os {
struct MutexType;
void LockMutex(MutexType* mutex);
void UnlockMutex(MutexType* mutex);
}  // namespace os
}  // namespace nn

struct ObjectManagerView {
    unsigned char pad0[0x80];
    unsigned char mutex[0x20];   // +80
};
// Reached through the GOT slot at 0x7100c21de8.
extern ObjectManagerView* gObjectManager;

static inline nn::os::MutexType* manager_mutex() {
    return reinterpret_cast<nn::os::MutexType*>(gObjectManager->mutex);
}

struct RefObj {
    unsigned char pad0[0x8];
    int refs;                    // +08
};

// The handle registry's lock, held for the scope of a release (0x48 bytes on the stack).
class RegistryLock {
public:
    RegistryLock();              // 0x7100466cb4
    ~RegistryLock();             // 0x7100466cd0
    unsigned char data[0x48];
};

struct HandleRegistry {
    int find(long* id);          // 0x71004624c8
};
struct HandleSlots {
    void release(int index);     // 0x71005e3e28
};
struct HandleManager {
    unsigned char pad0[0x998];
    HandleRegistry registry;     // +998
    unsigned char pad999[0xd7];
    HandleSlots slots;           // +a70
};
// Reached through the GOT slot at 0x7100c22a00.
extern HandleManager* gHandleManager;

// 0x71001e463c (D2) and 0x71001e46b8 (D0): the layout handle's own destructor. A virtual declared before the
// destructor keeps the vtable in its own module (GOT 0x7100c22f00).
class HandleBody {
public:
    virtual void anchor();
    virtual ~HandleBody();

    long id;                     // +08
};

HandleBody::~HandleBody() {
    if (id != -1) {
        {
            HandleManager* manager = gHandleManager;
            RegistryLock lock;
            int index = manager->registry.find(&id);
            manager->slots.release(index);
        }
        id = -1;
    }
}

// 0x71005c1d14: a buffer that holds a reference to its owner (taken under the object manager's lock).
class Buffer5c1d14 {
public:
    Buffer5c1d14(RefObj* owner, void* source);
    virtual ~Buffer5c1d14();

    int value8;                  // +08
    RefObj* owner;               // +10
    void* source;                // +18
    void* p20;                   // +20
    unsigned char data[0x4000];  // +28
};

Buffer5c1d14::Buffer5c1d14(RefObj* owner_, void* source_) : value8(0), owner(owner_), source(source_), p20(nullptr) {
    if (owner_) {
        nn::os::LockMutex(manager_mutex());
        owner_->refs++;
        nn::os::UnlockMutex(manager_mutex());
    }
    memset(data, 0, sizeof(data));
}

// 0x71003b2260 (D0): 3000 elements and the scene task base, deleted through the default heap.
class DefaultHeap {
public:
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

class SceneTask {
public:
    virtual ~SceneTask();        // 0x710038763c
    unsigned char pad8[0x2d448];
};

struct Elem3b2260 {
    ~Elem3b2260();               // 0x7100337b34
    unsigned char data[0x30];
};

class Scene3b2260 : public SceneTask {
public:
    ~Scene3b2260();
    static void operator delete(void* ptr) {
        if (ptr)
            get_default_heap()->release(ptr, 1, 0);
    }

    Elem3b2260 elems[3000];      // +2d450
};

Scene3b2260::~Scene3b2260() {}

struct ObjHeap;
// Reached through the GOT slot at 0x7100c22a00.
extern ObjHeap* gObjHeap;
void heap_note(ObjHeap* heap, void* at, int n);              // 0x71002925c8

struct Part5d27b4 { ~Part5d27b4(); unsigned char data[0x10]; };   // 0x71005d27b4

class Basec719c {
public:
    virtual ~Basec719c();           // 0x71003c719c
};

// 0x71002d5f90 (D0) and its twin 0x71002cdc50: the deleting destructor of 2cff80's middle base (vtable GOT
// 0x7100c2aa68), deleted through the default heap. The same code twice in the original.
#define MID_BASE(NAME)                                                                                       \
    class NAME : public Basec719c {                                                                           \
    public:                                                                                                   \
        ~NAME();                                                                                              \
        static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }                    \
        virtual void v10(); virtual void v18(); virtual void v20(); virtual void v28(); virtual void v30();   \
        virtual void v38(); virtual void v40(); virtual void v48(); virtual void v50(); virtual void v58();   \
        virtual void v60(); virtual void v68(); virtual void v70(); virtual void v78(); virtual void v80();   \
        virtual void closed();                                                                                \
                                                                                                              \
        unsigned char pad8[0x28];                                                                             \
        Part5d27b4 m30;                                                                                       \
        unsigned char pad40[0x100];                                                                           \
        unsigned char s140[0x48a0];                                                                           \
        int n49e0;                                                                                            \
        unsigned char pad49e4[0x14];                                                                          \
        unsigned char open49f8;                                                                               \
        unsigned char pad49f9[0x7];                                                                           \
    };                                                                                                        \
                                                                                                              \
    NAME::~NAME() {                                                                                           \
        if (open49f8) {                                                                                       \
            heap_note(gObjHeap, s140, n49e0);                                                                 \
            closed();                                                                                         \
            open49f8 = 0;                                                                                     \
        }                                                                                                     \
    }

MID_BASE(Mid2d5f90)
MID_BASE(Mid2cdc50)

// 0x71003aab84 (D2): 3a43c4's base, its destructor out of line here.
void* load_global_334a04();                                 // 0x7100334a04
struct PageOverride;
// Reached through the GOT slot at 0x7100c22da8.
extern PageOverride* gPageOverride;

inline bool page_ids() { return !load_global_334a04() && !gPageOverride; }

class Base3aab84 {
public:
    virtual ~Base3aab84();
    virtual void v10(); virtual void v18(); virtual void v20(); virtual void v28(); virtual void v30();
    virtual void v38(); virtual void v40(); virtual void v48();
    virtual void closed();          // +50

    unsigned char s8[0x22f4];       // +8
    int id22fc;                     // +22fc
    int id2300;                     // +2300
    unsigned char pad2304[0x18];
    unsigned char active;           // +231c
};

Base3aab84::~Base3aab84() {
    if (active) {
        if (page_ids())
            heap_note(gObjHeap, s8, id22fc);
        else
            heap_note(gObjHeap, s8, id2300);
        closed();
        active = 0;
    }
}

// 0x71001e3b24 (D2): the text pane's destructor: its line quads, unless they are borrowed, then its base.
void table_free(void* obj);         // 0x71005d43a0

class PaneBase {
public:
    virtual ~PaneBase();            // 0x71005dd278
    unsigned char pad8[0x158];
};

struct LineQuad {
    virtual ~LineQuad();
    unsigned char pad8[0x80];
};

class PanelPane : public PaneBase {
public:
    ~PanelPane();

    LineQuad* lines;                // +160
    int line_count;                 // +168
    unsigned char pad16c[0xc];
    bool borrowed;                  // +178
};

PanelPane::~PanelPane() {
    if (!borrowed && line_count != 0) {
        for (int i = 0; i < line_count; i++)
            lines[i].~LineQuad();
        table_free(lines);
    }
}

// One entry of the format table (12 bytes).
struct FormatInfo {
    int f0;
    int bits;                    // +4
    unsigned short block;        // +8
    unsigned short pada;
};
// Reached through the GOT slot at 0x7100c2d080.
extern FormatInfo gFormatTable[];

struct ImageDesc {
    unsigned char pad0[0x8];
    unsigned long size;          // +08
    unsigned int format;         // +10
    int type;                    // +14
};

// 0x7100531a58: an image view over a description, its block counts from the format table.
class ImageView531a58 {
public:
    ImageView531a58(RefObj* owner, const ImageDesc* desc);
    virtual ~ImageView531a58();

    int value8;                  // +08
    RefObj* owner;               // +10
    void* p18;                   // +18
    int pitch;                   // +20
    short bits;                  // +24
    short block;                 // +26
    int blocks;                  // +28
    int value2c;                 // +2c
    bool single;                 // +30
    int value34;                 // +34
    void* p38;                   // +38
    void* p40;                   // +40
};

ImageView531a58::ImageView531a58(RefObj* owner_, const ImageDesc* desc) : value8(0), owner(owner_) {
    owner_->refs++;
    p18 = nullptr;
    bits = gFormatTable[desc->format].bits;
    unsigned short size_block = gFormatTable[desc->format].block;
    block = size_block;
    single = desc->type == 1;
    pitch = single ? 0 : 0x10;
    blocks = desc->size / size_block;
    value2c = 1;
    value34 = 4;
    p38 = nullptr;
    p40 = nullptr;
}
