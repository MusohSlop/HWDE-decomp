// Composite screen destructors written by hand (third session): screens made of other screens, holders of effect
// nodes and layout handles. Names are descriptive placeholders. Status: matching/README.md.

#include "event/demo_effects.h"

void release_held_light_c2ada0();                                           // 0x710037adb8
void destroy_light_holder_37ad18();                                         // 0x710037ad18
void heap_note(EffectManager* manager, void* at, int id);                   // 0x71002925c8

class Base316aa4 {
public:
    virtual ~Base316aa4();                                                  // 0x7100316aa4
    unsigned char pad8[0x38];
};

struct Part5d27b4 { ~Part5d27b4(); unsigned char data[0x110]; };          // 0x71005d27b4
struct Part33c82c { ~Part33c82c(); unsigned char data[0x154b8]; };        // 0x710033c82c
struct Part2fb9f0 { ~Part2fb9f0(); unsigned char data[0x14a30]; };        // 0x71002fb9f0
struct Part304788 { ~Part304788(); unsigned char data[0x2ed20]; };        // 0x7100304788
struct Part333318 { ~Part333318(); unsigned char data[0x46b40]; };        // 0x7100333318
struct Part327344 { ~Part327344(); unsigned char data[0x1bf60]; };        // 0x7100327344
struct Part3192f0 { ~Part3192f0(); unsigned char data[0x70570]; };        // 0x71003192f0
struct Part310454 { ~Part310454(); unsigned char data[0x180]; };          // 0x7100310454
struct Part3843f0 { ~Part3843f0(); unsigned char data[0x10]; };           // 0x71003843f0

// A sound or effect handle; its destructor stops it.
struct Cue1f8724 {
    ~Cue1f8724();                                                           // 0x71001f8720
    unsigned char data[0xa0];
};

// A group's parent sits at +18 of the group.
struct GroupLink {
    unsigned char pad0[0x18];
    struct ParentGroup* parent;  // +18
};
struct ParentGroup {
    void remove(EffectGroup* group);                                        // 0x71005da1b0
};

// The layout handle as destructors inline it: the vtable store, then release() through the vtable with the
// layout root (vtable GOT 0x7100c22f00).
inline void* layout_root() { return gResourceLoader ? gResourceLoader->layout->root : nullptr; }

struct DtorHandleState {
    long id;
    short a;
    short b;
};

class DtorHandle : public DtorHandleState {
public:
    virtual ~DtorHandle() { release(layout_root()); }
    virtual void v10();
    virtual void release(void* root);
};

// A holder of an effect node (vtable GOT 0x7100c2ad48): when it goes, the effect manager is flushed for the ids
// 0x41e4 to 0x41fa and synced otherwise, the node's group leaves its parent and the heap notes the slot.
class NodeHolder {
public:
    virtual ~NodeHolder() {
        if (static_cast<unsigned int>(id - 0x41e4) <= 0x16)
            gEffectManager->flush();
        else
            gEffectManager->sync();
        if (node) {
            GroupLink* link = reinterpret_cast<GroupLink*>(node->group);
            if (link->parent)
                link->parent->remove(node->group);
        }
        heap_note(gEffectManager, &node, id);
    }
    virtual void v10();

    LightEffectNode* node;       // +08
    int id;                      // +10
    unsigned char pad14[0x1c];
};

// A holder with a cue (vtable GOT 0x7100c2ad68).
class CueHolder : public NodeHolder {
public:
    virtual void v18();

    unsigned char pad30[0x8];
    Cue1f8724 cue;               // +38
};

// 0x7100313038 (D2): vtable GOT 0x7100c2ad78; the held light released, then its members in reverse: seven layout
// handles (separate members; as an array the first release load moves ahead of its vtable store), two light
// resources, the holders and the screens it is made of (one of them 304788's).
class Screen313038 : public Base316aa4 {
public:
    virtual void anchor();
    ~Screen313038();

    Part33c82c part40;           // +40
    unsigned char pad154f8[0x28];
    Part2fb9f0 part15520;        // +15520
    Part304788 part29f50;        // +29f50
    Part333318 part58c70;        // +58c70
    Part327344 part9f7b0;        // +9f7b0
    Part3192f0 partbb710;        // +bb710
    NodeHolder holder12bc80;     // +12bc80
    NodeHolder holder12bcb0;     // +12bcb0
    Part310454 part12bce0;       // +12bce0
    CueHolder holder12be60;      // +12be60
    NodeHolder holder12bf38;     // +12bf38
    unsigned char pad12bf68[0x210];
    Part3843f0 part12c178;       // +12c178
    unsigned char pad12c188[0x1de48];
    Part5d27b4 light149fd0;      // +149fd0
    Part5d27b4 light14a0e0;      // +14a0e0
    unsigned char pad14a1f0[0xb0];
    DtorHandle handle14a2a0;     // +14a2a0
    DtorHandle handle14a2b8;     // +14a2b8
    DtorHandle handle14a2d0;     // +14a2d0
    DtorHandle handle14a2e8;     // +14a2e8
    DtorHandle handle14a300;     // +14a300
    DtorHandle handle14a318;     // +14a318
    DtorHandle handle14a330;     // +14a330
};

Screen313038::~Screen313038() {
    release_held_light_c2ada0();
    destroy_light_holder_37ad18();
}
