// Large functions matched by hand, starting from generated source (third session).
// Names are descriptive placeholders after the address. Status: matching/README.md.

class LayoutSprite {
public:
    LayoutSprite();                                                         // 0x71001ef52c
    unsigned char pad[0x48];
};
static_assert(sizeof(LayoutSprite) == 0x48, "layout sprite size");

class LayoutFrame {
public:
    LayoutFrame();                                                          // 0x71001f0140
    unsigned char pad[0x88];
};
static_assert(sizeof(LayoutFrame) == 0x88, "layout frame size");

struct HandleState {
    long id;                  // +08
    short a;                  // +10
    short b;                  // +12

    HandleState() : id(-1), a(0), b(0) {}
};

// Layout handle; its vtable lives in the effect manager unit (GOT 0x7100c22f00).
// The state base is constructed before the vtable pointer is stored.
class LayoutHandle : public HandleState {
public:
    virtual ~LayoutHandle();
    virtual void v10();
    virtual void release(void* root); // +18
};
static_assert(sizeof(LayoutHandle) == 0x18, "handle size");

#define LAYOUT_SPRITES8(n) LayoutSprite n##0, n##1, n##2, n##3, n##4, n##5, n##6, n##7;
#define LAYOUT_FRAMES10(n) LayoutFrame n##0, n##1, n##2, n##3, n##4, n##5, n##6, n##7, n##8, n##9;

// 0x710030be50: five sprites, an array of 544 and 128 single sprites. Clang constructs the array in a loop and
// fully unrolls the five-element head, so only single members give the 128 separate calls at the end.
class LayoutSpriteTable {
public:
    LayoutSpriteTable();

    LayoutSprite head[5];       // +0000
    LayoutSprite cells[544];    // +0168
    LAYOUT_SPRITES8(tail0) LAYOUT_SPRITES8(tail1) LAYOUT_SPRITES8(tail2) LAYOUT_SPRITES8(tail3)
    LAYOUT_SPRITES8(tail4) LAYOUT_SPRITES8(tail5) LAYOUT_SPRITES8(tail6) LAYOUT_SPRITES8(tail7)
    LAYOUT_SPRITES8(tail8) LAYOUT_SPRITES8(tail9) LAYOUT_SPRITES8(taila) LAYOUT_SPRITES8(tailb)
    LAYOUT_SPRITES8(tailc) LAYOUT_SPRITES8(taild) LAYOUT_SPRITES8(taile) LAYOUT_SPRITES8(tailf)
};
static_assert(sizeof(LayoutSpriteTable) == 0xbe68, "layout sprite table size");

LayoutSpriteTable::LayoutSpriteTable() {}

// 0x71003b9ccc: a layout handle and 150 single frames (an array would be constructed in a loop).
class LayoutFrameSet {
public:
    LayoutFrameSet();

    unsigned char pad0[0x40];
    LayoutHandle handle;        // +0040
    LAYOUT_FRAMES10(frame0) LAYOUT_FRAMES10(frame1) LAYOUT_FRAMES10(frame2) LAYOUT_FRAMES10(frame3)
    LAYOUT_FRAMES10(frame4) LAYOUT_FRAMES10(frame5) LAYOUT_FRAMES10(frame6) LAYOUT_FRAMES10(frame7)
    LAYOUT_FRAMES10(frame8) LAYOUT_FRAMES10(frame9) LAYOUT_FRAMES10(framea) LAYOUT_FRAMES10(frameb)
    LAYOUT_FRAMES10(framec) LAYOUT_FRAMES10(framed) LAYOUT_FRAMES10(framee)
};
static_assert(sizeof(LayoutFrameSet) == 0x5008, "layout frame set size");

LayoutFrameSet::LayoutFrameSet() {}

#define LAYOUT_FRAMES8(n) LayoutFrame n##0, n##1, n##2, n##3, n##4, n##5, n##6, n##7;

// 0x7100325e64: two layout handles, an array of 256 frames, then 64 single frames, 64 single sprites and 64 single
// frames, and a zeroed tail.
class LayoutFramePanel {
public:
    LayoutFramePanel();

    void* owner;                // +0000
    unsigned char pad8[0x90];
    LayoutHandle handle98;      // +0098
    LayoutHandle handleb0;      // +00b0
    LayoutFrame frames[256];    // +00c8
    LAYOUT_FRAMES8(upper0) LAYOUT_FRAMES8(upper1) LAYOUT_FRAMES8(upper2) LAYOUT_FRAMES8(upper3)
    LAYOUT_FRAMES8(upper4) LAYOUT_FRAMES8(upper5) LAYOUT_FRAMES8(upper6) LAYOUT_FRAMES8(upper7)
    LAYOUT_SPRITES8(mark0) LAYOUT_SPRITES8(mark1) LAYOUT_SPRITES8(mark2) LAYOUT_SPRITES8(mark3)
    LAYOUT_SPRITES8(mark4) LAYOUT_SPRITES8(mark5) LAYOUT_SPRITES8(mark6) LAYOUT_SPRITES8(mark7)
    LAYOUT_FRAMES8(lower0) LAYOUT_FRAMES8(lower1) LAYOUT_FRAMES8(lower2) LAYOUT_FRAMES8(lower3)
    LAYOUT_FRAMES8(lower4) LAYOUT_FRAMES8(lower5) LAYOUT_FRAMES8(lower6) LAYOUT_FRAMES8(lower7)
    unsigned char paddec8[0x18];
    int valuedee0;              // +dee0
    unsigned short valuedee4;   // +dee4
    void* valuedee8;            // +dee8
    int valuedef0;              // +def0
    unsigned char valuedef4;    // +def4
    unsigned char valuedef5;    // +def5
    unsigned short valuedef6;   // +def6
    int valuedef8;              // +def8
    unsigned char valuedefc;    // +defc
};
static_assert(sizeof(LayoutFramePanel) == 0xdf00, "layout frame panel size");

LayoutFramePanel::LayoutFramePanel()
    : owner(nullptr), valuedee0(0), valuedee4(0), valuedee8(nullptr), valuedef0(0), valuedef4(0), valuedef5(0),
      valuedef6(0), valuedef8(0), valuedefc(0) {}

// 0x710028ee38: 12 single sprites, 128 single frames, an array of 255 frames and a layout handle.
class LayoutFrameBoard {
public:
    LayoutFrameBoard();

    void* value0;               // +0000
    void* value8;               // +0008
    void* value10;              // +0010
    unsigned char pad18[0x28];
    void* value40;              // +0040
    unsigned char pad48[0x18];
    LAYOUT_SPRITES8(icon0)      // +0060
    LayoutSprite icon10, icon11, icon12, icon13;
    int value3c0;               // +03c0
    unsigned char pad3c4[0xfc];
    LAYOUT_FRAMES8(row0) LAYOUT_FRAMES8(row1) LAYOUT_FRAMES8(row2) LAYOUT_FRAMES8(row3)    // +04c0
    LAYOUT_FRAMES8(row4) LAYOUT_FRAMES8(row5) LAYOUT_FRAMES8(row6) LAYOUT_FRAMES8(row7)
    LAYOUT_FRAMES8(row8) LAYOUT_FRAMES8(row9) LAYOUT_FRAMES8(rowa) LAYOUT_FRAMES8(rowb)
    LAYOUT_FRAMES8(rowc) LAYOUT_FRAMES8(rowd) LAYOUT_FRAMES8(rowe) LAYOUT_FRAMES8(rowf)
    LayoutFrame cells[255];     // +48c0
    unsigned char padd038[0x4];
    int valued03c;              // +d03c
    int valued040;              // +d040
    int valued044;              // +d044
    int valued048;              // +d048
    unsigned char padd04c[0x34];
    LayoutHandle handle;        // +d080
    void* valued098;            // +d098
};
static_assert(sizeof(LayoutFrameBoard) == 0xd0a0, "layout frame board size");

LayoutFrameBoard::LayoutFrameBoard()
    : value0(nullptr), value8(nullptr), value10(nullptr), value40(nullptr), value3c0(0), valued03c(0), valued040(0),
      valued044(0), valued048(0), valued098(nullptr) {}
