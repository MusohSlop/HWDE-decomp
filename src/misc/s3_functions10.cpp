// Hand-written constructors (third session): classes with their members in the original's
// order. Names are descriptive placeholders. Status: matching/README.md.

extern "C" void* memset(void*, int, unsigned long);

struct Vec4f {
    float x, y, z, w;
};
typedef float f32x4 __attribute__((vector_size(16)));

struct GlobalTable {
    unsigned char pad[0x30];
    Vec4f v30;                     // +30
};
// Reached through the GOT slot at 0x7100c216f8.
extern GlobalTable gGlobalc216f8;

// 0x18 bytes, constructed out of line.
struct BufferSlot {
    BufferSlot();                  // 0x710003ce04
    unsigned char raw[0x18];
};

// 0x18 bytes; its five zeroed fields are merged into one 0x15-byte memset (three overlapping 8-byte stores).
struct ZeroRecord {
    ZeroRecord() : p(nullptr), q(0), r(0), s(0) {}
    void* p;
    long q;
    int r;
    char s;
};

// +37f0 of RecordBank. Its member initialisers run before its body's memset of the first array, so the record
// stores and the tail's memset come first.
struct RecordBlock {
    RecordBlock() : recs(), tail(), flag(false) { memset(data, 0, sizeof(data)); }
    unsigned char data[0xb005];    // +0
    ZeroRecord recs[9];            // +b008
    unsigned char tail[0x6d7];     // +b0e0
    unsigned char pad;
    unsigned char buf[0xdae];      // +b7b8: cleared by RecordBank's body
    bool flag;                     // +c566
};

// 0x60 bytes. The int at +30 is set first and again inside the -1 run at +28 (which becomes a 14-byte memset):
// the load of the table in between keeps the first store alive.
struct alignas(16) SlotState {
    SlotState() {
        i30 = -1;
        v0 = gGlobalc216f8.v30;
        v10 = (f32x4){0, 0, 0, 0};
        i20 = -1;
        s24 = -1;
        i28 = -1;
        i2c = -1;
        i30 = -1;
        s34 = -1;
        l38 = 0;
        i40 = -1;
        i44 = -1;
        c48 = 0;
        f4c = 0;
        c50 = 0;
        c51 = 0;
    }
    Vec4f v0;                      // +0
    f32x4 v10;                     // +10
    int i20;                       // +20
    short s24;                     // +24
    int i28;                       // +28
    int i2c;                       // +2c
    int i30;                       // +30
    short s34;                     // +34
    long l38;                      // +38
    int i40;                       // +40
    int i44;                       // +44
    char c48;                      // +48
    float f4c;                     // +4c
    char c50;                      // +50
    char c51;                      // +51
};

// 0xf0 bytes: a SlotState and its own fields. The floats keep their own base registers in the loop.
struct alignas(16) SlotEntry {
    SlotEntry() : head() {
        i60 = -1;
        i64 = -1;
        l68 = 0;
        l70 = 0;
        l78 = 0;
        i80 = -1;
        i84 = -1;
        i88 = -1;
        l90 = 0;
        i98 = -1;
        va0 = gGlobalc216f8.v30;
        ib0 = -1;
        ib4 = -1;
        fb8 = 6.2831855f;
        fbc = 0;
        ic0 = -1;
        ic4 = -1;
        ic8 = 0;
        icc = 0;
        id0 = -1;
        id4 = -1;
        id8 = -1;
        idc = 0;
        ie0 = -1;
    }
    SlotState head;                // +0
    int i60, i64;                  // +60
    long l68, l70, l78;            // +68
    int i80, i84, i88;             // +80
    long l90;                      // +90
    int i98;                       // +98
    int pad9c;
    Vec4f va0;                     // +a0
    int ib0, ib4;                  // +b0
    float fb8;                     // +b8: 2 pi
    float fbc;                     // +bc
    int ic0, ic4;                  // +c0
    int ic8, icc;                  // +c8
    int id0, id4, id8;             // +d0
    int idc;                       // +dc
    int ie0;                       // +e0
};

class RecordBank {
public:
    RecordBank();

    BufferSlot slots[11];          // +0
    int sizes[11];                 // +108
    int pad134;
    unsigned char buf138[0x36b8];  // +138
    RecordBlock block;             // +37f0
    SlotState states[71];          // +fd60
    int stateCount;                // +11800
    SlotEntry entriesA[100];       // +11810
    int entryCountA;               // +175d0
    SlotEntry entriesB[210];       // +175e0
    long l23ac0;                   // +23ac0
    int i23ac8;                    // +23ac8
    unsigned char pad23acc[0x84];
    short s23b50;                  // +23b50
};

// 0x71000193e8
RecordBank::RecordBank()
    : block(), states(), stateCount(0), entriesA(), entryCountA(0), entriesB(), l23ac0(0), i23ac8(0) {
    memset(buf138, 0, sizeof(buf138));
    memset(block.buf, 0, sizeof(block.buf));
    sizes[0] = 0x10b50;
    sizes[1] = 0xdb0;
    sizes[2] = 0xd00;
    sizes[3] = 0x1710;
    sizes[4] = 0xd60;
    sizes[5] = 0x510;
    sizes[6] = 0x9f0;
    sizes[7] = 0x1190;
    sizes[8] = 0x540;
    sizes[9] = 0x6a0;
    sizes[10] = 0x1200;
    s23b50 = 0;
}

class LayoutAnimation;
class IconTable;

class EffectGroup {
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
    virtual EffectGroup* find(const char* name, int depth); // +60

    unsigned char pad8[0x50];
    union {
        unsigned char flags58; // +58: bit 0 visible
        struct {
            unsigned char visible : 1;
            unsigned char : 7;
        };
    };
};

class LightEffectNode {
public:
    virtual void v00();
    LayoutAnimation* create_animation_3770(const char* name, bool loop);   // 0x71001e3770

    unsigned char pad8[0x10];
    EffectGroup* group;       // +18
};

class LightResource {
public:
    LightResource();                                                        // 0x71005d2744
    unsigned char pad[0x110];
};

class EffectManager {
public:
    void create_node(LightEffectNode** out, int id, const char* layout);    // 0x71001e2360
    void finish(int id);                                                    // 0x71001e22e4
    void attach(LightResource* resource, void* owner);                      // 0x71001e26dc
    void attach_resource(LightResource* resource);                          // 0x71001e26e0
    void flush();                                                           // 0x71001e26e4
};
// Reached through the GOT slot at 0x7100c22a00.
extern EffectManager* gEffectManager;

struct HandleState {
    long id;                  // +08
    short a;                  // +10
    short b;                  // +12

    HandleState() : id(-1), a(0), b(0) {}
};

// Layout handle; its vtable lives in the effect manager unit (GOT 0x7100c22f00).
class LayoutHandle : public HandleState {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
};

struct IconRect {
    unsigned short v[8];
};
struct IconSource {
    IconTable* table;
};
// Reached through the GOT slot at 0x7100c22bf0.
extern IconSource* gIconSource;
// Reached through the GOT slot at 0x7100c22c38.
extern const IconRect gIconRects[];
void apply_icon(EffectGroup* pane, LayoutHandle* handle, IconTable* table, const IconRect* rect); // 0x71001f7fe4

extern const char kLoadingLayout[] __attribute__((visibility("hidden")));     // 0x7100741e55
extern const char kLoadingAnim[] __attribute__((visibility("hidden")));       // 0x7100741e63
extern const char kTriforceAnim[] __attribute__((visibility("hidden")));      // 0x7100741e70
extern const char kLoadingDummy[] __attribute__((visibility("hidden")));      // 0x7100741e7e
extern const char kTriforce[] __attribute__((visibility("hidden")));          // 0x7100741e8c
extern const char kLoadingDummy00[] __attribute__((visibility("hidden")));    // 0x7100741e95

// 0x71001eeed4: the loading screen (loading.bflyt).
class LoadingScreen {
public:
    LoadingScreen();

    long value0;               // +0
    unsigned char value8;
    unsigned char value9;      // +9
    unsigned char pada[6];
    LightResource resource;    // +10
    LightEffectNode* node;     // +120
    LayoutAnimation* anim;     // +128
    LayoutHandle handle0;      // +130
    LayoutHandle handle1;      // +148
    EffectGroup* group160;     // +160: triforce_anim
    EffectGroup* group168;     // +168: loading_dummy
};

LoadingScreen::LoadingScreen() : value0(0), value9(0), node(nullptr) {
    gEffectManager->attach(&resource, nullptr);
    gEffectManager->create_node(&node, 0x41e7, kLoadingLayout);
    gEffectManager->flush();
    anim = node->create_animation_3770(kLoadingAnim, true);
    group160 = node->group->find(kTriforceAnim, 1);
    group168 = node->group->find(kLoadingDummy, 1);
    node->group->find(kTriforce, 1)->visible = false;
    apply_icon(group168, &handle0, gIconSource->table, &gIconRects[0xe]);
    apply_icon(node->group->find(kLoadingDummy00, 1), &handle1, gIconSource->table, &gIconRects[0xe]);
}

extern const char kSavingLayout[] __attribute__((visibility("hidden")));      // 0x7100741ea6
extern const char kSavingLoop[] __attribute__((visibility("hidden")));        // 0x7100741eb3
extern const char kSavingDummy[] __attribute__((visibility("hidden")));       // 0x7100741ebf
extern const char kSavingDummy00[] __attribute__((visibility("hidden")));     // 0x7100741ecc

// 0x71001f1f88: the saving screen (saving.bflyt).
class SavingScreen {
public:
    SavingScreen();

    int value0;                // +0
    int value4;
    int value8;
    int valuec;                // +c
    LightResource resource;    // +10
    LightEffectNode* node;     // +120
    LayoutAnimation* anim;     // +128
    LayoutHandle handle0;      // +130
    LayoutHandle handle1;      // +148
    EffectGroup* group160;     // +160: triforce_anim
    bool flag168;              // +168
};

SavingScreen::SavingScreen() : value0(0), valuec(0), node(nullptr), flag168(false) {
    gEffectManager->attach_resource(&resource);
    gEffectManager->create_node(&node, 0x41ed, kSavingLayout);
    gEffectManager->flush();
    anim = node->create_animation_3770(kSavingLoop, true);
    gEffectManager->finish(0x41ed);
    group160 = node->group->find(kTriforceAnim, 1);
    node->group->find(kTriforce, 1)->visible = false;
    apply_icon(node->group->find(kSavingDummy, 1), &handle0, gIconSource->table, &gIconRects[0x11]);
    apply_icon(node->group->find(kSavingDummy00, 1), &handle1, gIconSource->table, &gIconRects[0x11]);
}