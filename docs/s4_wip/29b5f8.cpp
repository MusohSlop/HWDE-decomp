// 0x710029b5f8 AdvBoard::initialize (9,224 B), fourth session, parked. Build: this file alone with try.py (or
//   build/s4/adiff.py), --name _ZN8AdvBoard10initializeEv and the symbol file docs/s4_wip/29b5f8.json (the GOT name
//   tables, the 94 strings and the new callee names; its .rodata 0x71007f8a30 holds the two jump tables).
// State: 9,224 B (the original's size), 12 instructions off counting branch targets. What is right:
//   - create_window_animation returns a WindowAnimation* that the board stores into LayoutAnimation* members, and
//     the stops right after a create (signboards, moon_clash) are written inline: the original keeps their second
//     null check (LVI cannot see the null through the base conversion; a static inline helper is threaded on its own
//     before it is inlined). Stops of reloaded members (ending) are threaded in both, so they keep the helper.
//   - the weapon loop rereads the finish check and the rate through a plain pointer to the array: the original
//     computes this+i*8 again in each block (LSR expands each use in its own block when the address values differ).
//   - the adv_text_lv loop walks the plates with their own pointer (the latch then steps the level offset first).
//   - view_left is volatile, so of the four default stores only top and right merge (the original's 64-bit store).
// Still different: (1) the moves loop: our JumpThreading sends the "i == 8 && mode == 4" failure edge through the
//   latch straight to the loop exit (LVI knows i == 8 there); the original branches to the latch. short, long,
//   unsigned, do-while, an else-continue and a pointer for tv.moves did not change it. (2) the view defaults (11):
//   the original materializes &top, 7, the top/right constant and &bottom before the hide store and &left after the
//   cell load (x24, x22, x25, x23), ours &left first; all 120 orders of the four stores and the cell read, with and
//   without the volatile, and a packed view_left (stops every merge) were no better. (2) is scheduling only, a
//   candidate for s5's IR statement search (tools/s5/irsearch.py); (1) is a control-flow difference.

// Adventure Mode board: AdvBoard::initialize (0x710029b5f8), which loads the board's layouts (the whole map on
// the TV and the DRC, the player marker, the DLC counters and timers, network plates and the result windows),
// binds their animations and places the camera on the player's cell. Names are descriptive placeholders; the
// effect types are the demo units' (event/demo_effects.h), declared here with the animation's +d8 slot.

// Intrusive ring link (prev at +0, next at +8).
struct ListLink {
    ListLink* prev;
    ListLink* next;

    // Splices the ring that starts at node in front of this link.
    void link_before(ListLink* node) {
        ListLink* last = node->prev;
        node->prev = prev;
        last->next = this;
        prev->next = node;
        prev = last;
    }
};

class LayoutAnimation {
public:
    static void* operator new(unsigned long size) noexcept;                 // 0x71005d4380
    LayoutAnimation();                                                      // 0x71005d026c
    virtual ~LayoutAnimation();
    virtual void v10();
    virtual void v18();
    virtual void set_active(bool active); // +20
    virtual void reset(); // +28
    virtual void v30();
    virtual void v38();
    virtual void bind(void* root, void* resources, void* block); // +40
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void v60();
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void v80();
    virtual void v88();
    virtual void v90();
    virtual void v98();
    virtual void va0();
    virtual void va8();
    virtual void set_rate(float rate); // +b0
    virtual void vb8();
    virtual void set_frame(float frame); // +c0
    virtual void vc8();
    virtual void rewind(); // +d0
    virtual void finish(); // +d8

    ListLink link;            // +08
    unsigned char pad18[0x30];
};

// What create_window_animation returns; the board keeps it as a LayoutAnimation. Through that conversion the
// original's second null check after a create is not threaded (the check tests the call, the reload the base).
class WindowAnimation : public LayoutAnimation {};

// Animation bound to a node's binding ring (0x58 bytes, vtable GOT 0x7100c2a698).
class AnimBinding : public LayoutAnimation {
public:
    AnimBinding() : value48(nullptr), value50(0) {}
    ~AnimBinding();

    void* value48;            // +48
    int value50;              // +50
};

struct AnimSource {
    void* data;               // +00
    void* block;              // +08
    unsigned char pad10[0x10];

    explicit AnimSource(void* resource);                                    // 0x71005cfac8
};

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
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void bind_animation(void* binding, bool a, bool b); // +80
    void add(EffectGroup* child);                                           // 0x71005da17c
    EffectGroup* duplicate(void* root);                                     // 0x71005dec80

    unsigned char pad8[0x28];
    float offset30;           // +30
    float offset34;           // +34
    unsigned char pad38[0x10];
    float scale48;            // +48
    float scale4c;            // +4c
    unsigned char pad50[8];
    unsigned char flags58;    // +58: bit 0 visible, bit 4 moved
};

class LightEffectNode {
public:
    virtual void v00();
    LayoutAnimation* create_animation(const char* name, bool loop);         // 0x71001e3820
    WindowAnimation* create_window_animation(const char* name, bool loop);  // 0x71001e37c8
    void* find_animation(const char* name);                                 // 0x71005d4fec

    ListLink bindings;        // +08
    EffectGroup* group;       // +18
    unsigned char pad20[0x20];
    void* resources;          // +40
};

class LightResource {
private:
    unsigned char data[0x110];
};

class EffectManager {
public:
    void create_node(LightEffectNode** out, int id, const char* layout);    // 0x71001e2360
    void attach(LightResource* resource, void* owner);                      // 0x71001e26dc
    void attach_resource(LightResource* resource);                          // 0x71001e26e0
    void sync();                                                            // 0x71001e26e8
    void finish(int id);                                                    // 0x71001e22e4
};
// Reached through the GOT slot at 0x7100c22a00.
extern EffectManager* gEffectManager;

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

struct HandleState {
    long id;                  // +08
    short a;                  // +10
    short b;                  // +12
};

// Layout handle; its vtable lives in the effect manager unit (GOT 0x7100c22f00).
class LayoutHandle : public HandleState {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void release(void* root); // +18
};

struct PanelItem {
    EffectGroup* object;      // +00
    LayoutHandle handle;      // +08
};

struct IconRect {
    unsigned short v[8];
};

class IconTable {
public:
    const IconRect* get(int id);                                            // 0x7100283d74

    void* texture;            // +00
};
// Reached through the GOT slot at 0x7100c2a650.
extern IconTable* gIconTable;

void apply_icon(EffectGroup* pane, LayoutHandle* handle, void* texture, const IconRect* rect); // 0x71001f7fe4

class GameState {
public:
    unsigned char pad[0x1bb7c];
    unsigned int mode;        // +1bb7c
};

struct Player {
    int id;                   // +0000: current cell
    unsigned char pad4[0x296c];
    int facing;               // +2970
    unsigned char pad2974[0x2c4];
};

class Progress {
public:
    int base_level(int kind);                                               // 0x7100203550
    void set_base_level(int kind, int level);                               // 0x7100203580
    unsigned char record(int id);                                           // 0x71002032f4

    unsigned char pad[0x14c];
};

class Game {
public:
    GameState* state();                                                     // 0x7100204c10

    unsigned char pad[0x27f8];
    Progress progress;        // +27f8
    Player players[1];        // +2944
};
Game* get_game();                                                           // 0x7100204728

static inline unsigned int game_mode() {
    return get_game()->state()->mode;
}

class MaterialBook {
public:
    void* entry(int material);                                              // 0x71002015a8
};
MaterialBook* get_material_book();                                          // 0x7100200fc0
unsigned char material_known(void* flags);                                  // 0x71001ff9e8
unsigned char material_unlocked(void* entry, int kind);                     // 0x71001ff974

int stage_message();                                                        // 0x710026c11c

// Number shown with a digit animation (0xa0 bytes).
class NumberDisplay {
public:
    void init(LightEffectNode* node, LayoutAnimation* anim, int digits);    // 0x71001f8820

    unsigned char pad[0xa0];
};

// 0x710029da00 (four animations, the shape of EffectClock::stop)
struct AnimationSet_29da00 {
    void stop();

    LightEffectNode* owner;   // +00
    LayoutAnimation* anims[4]; // +08
};

struct NodeAnim {
    LightEffectNode* node;    // +00
    LayoutAnimation* anim;    // +08
};

// One view of the whole map (0x120 bytes).
struct BoardMapView {
    LightEffectNode* node;            // +00
    PanelItem arrows[4];              // +08
    EffectGroup* locks[4];            // +88
    EffectGroup* colors[6];           // +a8
    LayoutAnimation* moves[9];        // +d8
};

class AdvBoard {
public:
    void initialize();
    void update_icons();                                                    // 0x710029dc3c
    void update_counters();                                                 // 0x710029e8c0
    void update_plates();                                                   // 0x710029ecf8
    void update_view();                                                     // 0x710029f47c

    unsigned char pad0[8];
    unsigned char initialized;        // +08
    unsigned char pad9[3];
    int state;                        // +0c
    int pc_detail;                    // +10
    unsigned char pad14[0xc];
    BoardMapView tv;                  // +20
    BoardMapView drc;                 // +140
    LightEffectNode* headwind;        // +260
    LayoutAnimation* headwind_anim;   // +268
    unsigned char pad270[0x10];
    LightEffectNode* wall_u;          // +280
    LightEffectNode* wall_b;          // +288
    AnimationSet_29da00 pc;           // +290
    unsigned char flag2b8;            // +2b8
    unsigned char pad2b9[3];
    int cell2bc;                      // +2bc
    int cell2c0;                      // +2c0
    int value2c4;                     // +2c4
    int value2c8;                     // +2c8
    unsigned int direction;           // +2cc
    LightEffectNode* cursor;          // +2d0
    LayoutAnimation* cursor_loop;     // +2d8
    LightEffectNode* icons;           // +2e0
    LayoutAnimation* weapon_effects[8]; // +2e8
    EffectGroup* face_dummy;          // +328
    unsigned char pad330[0x18];
    NodeAnim arrivals[3];             // +348
    LightEffectNode* links[10];       // +378
    LayoutAnimation* link_loops[10];  // +3c8
    PanelItem levels[10];             // +418
    LightEffectNode* plates[10];      // +558
    LayoutAnimation* plate_opens[10]; // +5a8
    unsigned char pad5f8[0x70f8];
    LightResource resource76f0;       // +76f0
    LightResource resource7800;       // +7800
    unsigned char pad7910[8];
    LightEffectNode* timer;           // +7918
    LayoutAnimation* timer_in;        // +7920
    NodeAnim timer_num;               // +7928
    NodeAnim timer_red;               // +7938
    NodeAnim timer_plus;              // +7948
    EffectGroup* timer_pos;           // +7958
    EffectGroup* timer_plus_pos;      // +7960
    LightEffectNode* moon;            // +7968
    LayoutAnimation* moon_scale;      // +7970
    LayoutAnimation* moon_clash;      // +7978
    LightEffectNode* battleship;      // +7980
    LightEffectNode* squid;           // +7988
    LightEffectNode* tornado;         // +7990
    LightEffectNode* nightmare;       // +7998
    LightEffectNode* egg_counter;     // +79a0
    LightEffectNode* eggs[2];         // +79a8
    LightEffectNode* eggs_pwup[2];    // +79b8
    EffectGroup* egg_groups[8];       // +79c8
    LayoutAnimation* egg_inout;       // +7a08
    LayoutAnimation* inst_inout;      // +7a10
    LayoutAnimation* egg_anims[4];    // +7a18
    NumberDisplay egg_numbers[4];     // +7a38
    unsigned char pad7cb8[0x18];
    LightEffectNode* wind_stone;      // +7cd0
    LightEffectNode* linebeck;        // +7cd8
    LightEffectNode* zdl3_counter;    // +7ce0
    LightEffectNode* zdl3_num;        // +7ce8
    LightEffectNode* hourglass_top;   // +7cf0
    LightEffectNode* hourglass_bottom; // +7cf8
    EffectGroup* counters[6];         // +7d00
    EffectGroup* num_pos;             // +7d30
    LayoutAnimation* counter_inout;   // +7d38
    LayoutAnimation* num_anim;        // +7d40
    LayoutAnimation* hourglass_anims[2]; // +7d48
    unsigned char pad7d58[0x18];
    LightEffectNode* signboard;       // +7d70
    LightEffectNode* crack;           // +7d78
    LayoutAnimation* signboard_anims[29]; // +7d80
    unsigned char pad7e68[0x19c20];
    LightEffectNode* ending;          // +21a88
    LayoutAnimation* ending_in;       // +21a90
    LayoutAnimation* ending_loop;     // +21a98
    LayoutAnimation* ending_out;      // +21aa0
    PanelItem complete_end;           // +21aa8
    PanelItem complete_end_ef;        // +21ac8
    unsigned char pad21ae8[4];
    int value21aec;                   // +21aec
    LightEffectNode* expup_tv;        // +21af0
    LayoutAnimation* expup_tv_in;     // +21af8
    PanelItem expup_tv_text;          // +21b00
    LightEffectNode* expup_drc;       // +21b20
    LayoutAnimation* expup_drc_in;    // +21b28
    PanelItem expup_drc_text;         // +21b30
    LightEffectNode* complete;        // +21b50
    EffectGroup* complete_icons[4];   // +21b58
    LayoutAnimation* complete_in;     // +21b78
    PanelItem complete_text;          // +21b80
    PanelItem complete_text_00;       // +21ba0
    unsigned char pad21bc0[4];
    float scroll_x;                   // +21bc4
    float scroll_y;                   // +21bc8
    volatile int view_left;           // +21bcc
    int view_top;                     // +21bd0
    int view_right;                   // +21bd4
    int view_bottom;                  // +21bd8
    float rate;                       // +21bdc
    void* ptr21be0;                   // +21be0
    unsigned char pad21be8[8];
    NumberDisplay timer_numbers[3];   // +21bf0
    NumberDisplay zdl3_number;        // +21dd0
};
static_assert(__builtin_offsetof(AdvBoard, pc) == 0x290, "pc");
static_assert(__builtin_offsetof(AdvBoard, resource76f0) == 0x76f0, "resource");
static_assert(__builtin_offsetof(AdvBoard, timer) == 0x7918, "timer");
static_assert(__builtin_offsetof(AdvBoard, egg_numbers) == 0x7a38, "eggs");
static_assert(__builtin_offsetof(AdvBoard, signboard) == 0x7d70, "signboard");
static_assert(__builtin_offsetof(AdvBoard, ending) == 0x21a88, "ending");
static_assert(__builtin_offsetof(AdvBoard, rate) == 0x21bdc, "rate");
static_assert(__builtin_offsetof(AdvBoard, zdl3_number) == 0x21dd0, "zdl3");

// Name tables, reached through the GOT slots at 0x7100c2a8a8-0x7100c2a8f0.
extern const char* kPcDetailLayouts[];
extern const char* kArrowMoveAnims[];
extern const char* kArrowWholePanes[];
extern const char* kIconLockPanes[];
extern const char* kColorAnims[];
extern const char* kHeadwindAnims[];
extern const char* kMoveAnims[];
extern const char* kWeaponIconPanes[];
extern const char* kNetworkLinkLayouts[];
extern const char* kNetPlatePanes[];
// Name tables reached PC-relative.
extern const char* kSignboardAnims[] __attribute__((visibility("hidden")));    // 0x7100bd21c0
extern const char* kWeaponEffectAnims[] __attribute__((visibility("hidden"))); // 0x7100bd22a8

// Layout, pane and animation names, merged with other literals by the linker.
extern const char kAdvWholeMapLayout[] __attribute__((visibility("hidden")));       // 0x71007d703e
extern const char kAdvWholeMapDrcLayout[] __attribute__((visibility("hidden")));    // 0x71007d7052
extern const char kAdvWallHeadwindLayout[] __attribute__((visibility("hidden")));   // 0x71007d706a
extern const char kAdvCursorDrcLayout[] __attribute__((visibility("hidden")));      // 0x71007d7085
extern const char kAdvIconLayout[] __attribute__((visibility("hidden")));           // 0x71007d709a
extern const char kAdvEndingLayout[] __attribute__((visibility("hidden")));         // 0x71007d70a9
extern const char kAdvExpupTvLayout[] __attribute__((visibility("hidden")));        // 0x71007d70ba
extern const char kAdvExpupDrcLayout[] __attribute__((visibility("hidden")));       // 0x71007d70cd
extern const char kAdvComplateLayout[] __attribute__((visibility("hidden")));       // 0x71007d70e1
extern const char kArrivalEffectLayout[] __attribute__((visibility("hidden")));     // 0x71007d6975
extern const char kAdvDlc3TimerLayout[] __attribute__((visibility("hidden")));      // 0x71007d70f4
extern const char kAdvDlc3NumTimerLayout[] __attribute__((visibility("hidden")));   // 0x71007d7109
extern const char kAdvDlc3NumTimerRedLayout[] __attribute__((visibility("hidden"))); // 0x71007d7122
extern const char kAdvDlc3NumTimerPlusLayout[] __attribute__((visibility("hidden"))); // 0x71007d713f
extern const char kAdvDlc3MoonLayout[] __attribute__((visibility("hidden")));       // 0x71007d715d
extern const char kAdvIconBattleshipLayout[] __attribute__((visibility("hidden"))); // 0x71007d7171
extern const char kAdvIconSquidLayout[] __attribute__((visibility("hidden")));      // 0x71007d718b
extern const char kAdvIconTornadoLayout[] __attribute__((visibility("hidden")));    // 0x71007d71a0
extern const char kAdvIconNightmareLayout[] __attribute__((visibility("hidden")));  // 0x71007d71b7
extern const char kAdvZdl2CounterLayout[] __attribute__((visibility("hidden")));    // 0x71007d71d0
extern const char kAdvZdl2NumEggLayout[] __attribute__((visibility("hidden")));     // 0x71007d71e7
extern const char kAdvZdl2NumEggPwupLayout[] __attribute__((visibility("hidden"))); // 0x71007d71fe
extern const char kAdvIconWindStoneLayout[] __attribute__((visibility("hidden")));  // 0x71007d721a
extern const char kAdvIconLinebeckCompanyLayout[] __attribute__((visibility("hidden"))); // 0x71007d7234
extern const char kAdvZdl3CounterLayout[] __attribute__((visibility("hidden")));    // 0x71007d7254
extern const char kAdvZdl3NumLayout[] __attribute__((visibility("hidden")));        // 0x71007d726b
extern const char kAdvZdl3HourglassTopLayout[] __attribute__((visibility("hidden"))); // 0x71007d727e
extern const char kAdvZdl3HourglassBottomLayout[] __attribute__((visibility("hidden"))); // 0x71007d729b
extern const char kAdvWallZdl3ULayout[] __attribute__((visibility("hidden")));      // 0x71007d72bb
extern const char kAdvWallZdl3BLayout[] __attribute__((visibility("hidden")));      // 0x71007d72d4
extern const char kAdvZdl4RavioSignboardLayout[] __attribute__((visibility("hidden"))); // 0x71007d72ed
extern const char kAdvIconCrackLayout[] __attribute__((visibility("hidden")));      // 0x71007d730c
extern const char kAdvWallZdl4ULayout[] __attribute__((visibility("hidden")));      // 0x71007d7321
extern const char kAdvWallZdl4BLayout[] __attribute__((visibility("hidden")));      // 0x71007d733a
extern const char kArwWholeTv[] __attribute__((visibility("hidden")));              // 0x71007d7353
extern const char kPcPane[] __attribute__((visibility("hidden")));                  // 0x71007d7360
extern const char kArwU[] __attribute__((visibility("hidden")));                    // 0x71007d5b66
extern const char kArwL[] __attribute__((visibility("hidden")));                    // 0x71007d5b6c
extern const char kArwR[] __attribute__((visibility("hidden")));                    // 0x71007d5b72
extern const char kArwD[] __attribute__((visibility("hidden")));                    // 0x71007d5b78
extern const char kNumTimerPos[] __attribute__((visibility("hidden")));             // 0x71007d7363
extern const char kNumTimerPlusPos[] __attribute__((visibility("hidden")));         // 0x71007d7371
extern const char kLoopAnim[] __attribute__((visibility("hidden")));                // 0x7100740004
extern const char kTimerBaseIn[] __attribute__((visibility("hidden")));             // 0x71007d7383
extern const char kNumTimerAnim[] __attribute__((visibility("hidden")));            // 0x71007d7391
extern const char kNumTimerRedAnim[] __attribute__((visibility("hidden")));         // 0x71007d739b
extern const char kNumTimerPlusAnim[] __attribute__((visibility("hidden")));        // 0x71007d73a9
extern const char kNumEggPos[] __attribute__((visibility("hidden")));               // 0x71007d73b8
extern const char kNumInstPos[] __attribute__((visibility("hidden")));              // 0x71007d73c4
extern const char kItemAdvDummy[] __attribute__((visibility("hidden")));            // 0x71007d6126
extern const char kEggCounterBase[] __attribute__((visibility("hidden")));          // 0x71007d73d1
extern const char kEggCounterBasePwup[] __attribute__((visibility("hidden")));      // 0x71007d73e2
extern const char kInstCounterBase[] __attribute__((visibility("hidden")));         // 0x71007d73f8
extern const char kInstCounterBasePwup[] __attribute__((visibility("hidden")));     // 0x71007d740a
extern const char kEggCounterCracked[] __attribute__((visibility("hidden")));       // 0x71007d7421
extern const char kEggCounterInout[] __attribute__((visibility("hidden")));         // 0x71007d7435
extern const char kInstCounterInout[] __attribute__((visibility("hidden")));        // 0x71007d7447
extern const char kNumEggAnim[] __attribute__((visibility("hidden")));              // 0x71007d745a
extern const char kAdvZdl2NumEggPane[] __attribute__((visibility("hidden")));       // 0x71007411b8
extern const char kAdvZdl2NumEggPwupPane[] __attribute__((visibility("hidden")));   // 0x71007411c9
extern const char kCounterLinebeckShip[] __attribute__((visibility("hidden")));     // 0x71007d7462
extern const char kCounterIronShip[] __attribute__((visibility("hidden")));         // 0x71007d7478
extern const char kCounterGoldenShip[] __attribute__((visibility("hidden")));       // 0x71007d748a
extern const char kCounterGodTrain[] __attribute__((visibility("hidden")));         // 0x71007d749e
extern const char kCounterSteelTrain[] __attribute__((visibility("hidden")));       // 0x71007d74b0
extern const char kCounterGoldenTrain[] __attribute__((visibility("hidden")));      // 0x71007d74c4
extern const char kNumPos[] __attribute__((visibility("hidden")));                  // 0x71007d74d9
extern const char kCounterInout[] __attribute__((visibility("hidden")));            // 0x71007d74e1
extern const char kNumAnim[] __attribute__((visibility("hidden")));                 // 0x71007d74ef
extern const char kAdvZdl3NumPane[] __attribute__((visibility("hidden")));          // 0x710074121e
extern const char kHourglass[] __attribute__((visibility("hidden")));               // 0x71007d74f3
extern const char kBgCloud[] __attribute__((visibility("hidden")));                 // 0x71007d74fd
extern const char kMoonScale[] __attribute__((visibility("hidden")));               // 0x71007d765c
extern const char kMoonClash[] __attribute__((visibility("hidden")));               // 0x71007d7667
extern const char kCrash[] __attribute__((visibility("hidden")));                   // 0x71007d7672
extern const char kAdvNetPlateLayout[] __attribute__((visibility("hidden")));       // 0x71007d7678
extern const char kOpenAnim[] __attribute__((visibility("hidden")));                // 0x71007d768c
extern const char kNetIconFriends[] __attribute__((visibility("hidden")));          // 0x71007d7691
extern const char kAdvTextLv[] __attribute__((visibility("hidden")));               // 0x71007d76a2
extern const char kInAnim[] __attribute__((visibility("hidden")));                  // 0x710073fffb
extern const char kOutAnim[] __attribute__((visibility("hidden")));                 // 0x710074056c
extern const char kAdvTextCompleteEnd[] __attribute__((visibility("hidden")));      // 0x71007d76ae
extern const char kAdvTextCompleteEndEf[] __attribute__((visibility("hidden")));    // 0x71007d76c4
extern const char kExpupDummy[] __attribute__((visibility("hidden")));              // 0x71007d76dd
extern const char kExpupIn[] __attribute__((visibility("hidden")));                 // 0x71007d76e9
extern const char kAdvTextComplete[] __attribute__((visibility("hidden")));         // 0x71007d76f2
extern const char kAdvTextComplete00[] __attribute__((visibility("hidden")));       // 0x71007d7704
extern const char kIconHeartContainers[] __attribute__((visibility("hidden")));     // 0x71007d6e91
extern const char kIconSkulltula[] __attribute__((visibility("hidden")));           // 0x71007d7719
extern const char kIconWpnS[] __attribute__((visibility("hidden")));                // 0x71007d7728
extern const char kIconFairy[] __attribute__((visibility("hidden")));               // 0x71007d7733
extern const char kPcFaceDummy[] __attribute__((visibility("hidden")));             // 0x71007d778e
extern const char kArrivalAnim[] __attribute__((visibility("hidden")));             // 0x71007d69a9
extern const char kAdvIconLock[] __attribute__((visibility("hidden")));             // 0x71007d779c

// Binds the named animation of node to a new binding linked into the node's ring.
static inline AnimBinding* bind_animation(LightEffectNode* node, void* root, const char* name) {
    AnimSource source(node->find_animation(name));
    void* block = source.block;
    if (!block)
        return nullptr;
    AnimBinding* binding = new AnimBinding;
    if (binding) {
        node->bindings.link_before(&binding->link);
        binding->bind(root, node->resources, block);
    }
    return binding;
}

static inline void hide(EffectGroup* group) {
    group->flags58 &= ~1;
}

static inline void reset_scale(EffectGroup* group) {
    group->scale48 = 1.0f;
    group->scale4c = 1.0f;
    group->flags58 |= 0x10;
}

static inline void show_icon(PanelItem& item, int icon) {
    const IconRect* rect = gIconTable->get(icon);
    void* texture = gIconTable->texture;
    apply_icon(item.object, &item.handle, texture, rect);
    item.object->flags58 |= 1;
}

// Starts an animation, reading the pointer again after the activation call.
static inline void start_animation(LayoutAnimation*& anim, const float& rate) {
    LayoutAnimation* current = anim;
    if (current) {
        current->set_active(true);
        current = anim;
    }
    current->set_rate(rate);
}

static inline void stop_animation(LayoutAnimation*& anim) {
    if (anim)
        anim->rewind();
    if (anim)
        anim->set_active(false);
}

static inline void play(LayoutAnimation*& anim, const float& rate) {
    anim->set_rate(rate);
    if (anim)
        anim->set_active(true);
}

// The icon and moon nodes are created through a byte offset from the board: the original's address for these two
// calls is not shared with the nodes' later loads, which fold the offset (sharing it keeps the address in a register
// and changes the frame).
static inline LightEffectNode** node_at(AdvBoard* board, unsigned long offset) {
    return reinterpret_cast<LightEffectNode**>(reinterpret_cast<unsigned char*>(board) + offset);
}

// 0x710029b5f8
void AdvBoard::initialize() {
    rate = 0.8f;
    if (initialized)
        return;
    gEffectManager->create_node(&tv.node, 0x420d, kAdvWholeMapLayout);
    gEffectManager->create_node(&drc.node, 0x420d, kAdvWholeMapDrcLayout);
    gEffectManager->create_node(&headwind, 0x420d, kAdvWallHeadwindLayout);
    gEffectManager->sync();
    pc_detail = 0;
    int level = get_game()->progress.base_level(0);
    if (static_cast<unsigned int>(level) <= 30) {
        void* entry = get_material_book()->entry(level);
        if (material_known(static_cast<unsigned char*>(entry) + 0x28) && material_unlocked(entry, 1))
            pc_detail = level;
        else
            get_game()->progress.set_base_level(0, pc_detail);
    }
    gEffectManager->create_node(&pc.owner, 0x4211, kPcDetailLayouts[pc_detail]);
    gEffectManager->create_node(&cursor, 0x420d, kAdvCursorDrcLayout);
    gEffectManager->create_node(node_at(this, 0x2e0), 0x420d, kAdvIconLayout);
    gEffectManager->create_node(&ending, 0x420d, kAdvEndingLayout);
    gEffectManager->create_node(&expup_tv, 0x420d, kAdvExpupTvLayout);
    gEffectManager->create_node(&expup_drc, 0x420d, kAdvExpupDrcLayout);
    gEffectManager->create_node(&complete, 0x420d, kAdvComplateLayout);
    gEffectManager->create_node(&arrivals[0].node, stage_message(), kArrivalEffectLayout);
    gEffectManager->create_node(&arrivals[1].node, stage_message(), kArrivalEffectLayout);
    gEffectManager->create_node(&arrivals[2].node, stage_message(), kArrivalEffectLayout);
    gEffectManager->create_node(&timer, 0x420d, kAdvDlc3TimerLayout);
    gEffectManager->create_node(&timer_num.node, 0x420d, kAdvDlc3NumTimerLayout);
    gEffectManager->create_node(&timer_red.node, 0x420d, kAdvDlc3NumTimerRedLayout);
    gEffectManager->create_node(&timer_plus.node, 0x420d, kAdvDlc3NumTimerPlusLayout);
    gEffectManager->create_node(node_at(this, 0x7968), 0x420d, kAdvDlc3MoonLayout);
    if (game_mode() == 5 || game_mode() == 6) {
        gEffectManager->create_node(&battleship, 0x420d, kAdvIconBattleshipLayout);
        gEffectManager->create_node(&squid, 0x420d, kAdvIconSquidLayout);
        gEffectManager->create_node(&tornado, 0x420d, kAdvIconTornadoLayout);
    } else if (game_mode() == 7) {
        gEffectManager->create_node(&nightmare, 0x4625, kAdvIconNightmareLayout);
        gEffectManager->create_node(&egg_counter, 0x4625, kAdvZdl2CounterLayout);
        gEffectManager->create_node(&eggs[0], 0x4625, kAdvZdl2NumEggLayout);
        gEffectManager->create_node(&eggs[1], 0x4625, kAdvZdl2NumEggLayout);
        gEffectManager->create_node(&eggs_pwup[0], 0x4625, kAdvZdl2NumEggPwupLayout);
        gEffectManager->create_node(&eggs_pwup[1], 0x4625, kAdvZdl2NumEggPwupLayout);
    } else if (game_mode() == 8) {
        gEffectManager->create_node(&wind_stone, 0x4626, kAdvIconWindStoneLayout);
        gEffectManager->create_node(&linebeck, 0x4626, kAdvIconLinebeckCompanyLayout);
        gEffectManager->create_node(&zdl3_counter, 0x4626, kAdvZdl3CounterLayout);
        gEffectManager->create_node(&zdl3_num, 0x4626, kAdvZdl3NumLayout);
        gEffectManager->create_node(&hourglass_top, 0x4626, kAdvZdl3HourglassTopLayout);
        gEffectManager->create_node(&hourglass_bottom, 0x4626, kAdvZdl3HourglassBottomLayout);
        gEffectManager->create_node(&wall_u, 0x4626, kAdvWallZdl3ULayout);
        gEffectManager->create_node(&wall_b, 0x4626, kAdvWallZdl3BLayout);
    } else if (game_mode() == 9) {
        gEffectManager->create_node(&signboard, 0x4627, kAdvZdl4RavioSignboardLayout);
        gEffectManager->create_node(&crack, 0x4627, kAdvIconCrackLayout);
        gEffectManager->create_node(&wall_u, 0x4627, kAdvWallZdl4ULayout);
        gEffectManager->create_node(&wall_b, 0x4627, kAdvWallZdl4BLayout);
    }
    gEffectManager->sync();
    reset_scale(pc.owner->group);
    EffectGroup* whole = tv.node->group->find(kArwWholeTv, 1);
    EffectGroup* copy = whole->duplicate(gResourceLoader->layout->root);
    pc.owner->group->find(kPcPane, 1)->add(copy);
    for (int i = 0; i < 4; ++i) {
        AnimBinding* binding = bind_animation(tv.node, layout_root(), kArrowMoveAnims[i]);
        switch (i) {
        case 0:
            pc.owner->group->find(kArwU, 1)->bind_animation(binding, true, true);
            break;
        case 1:
            pc.owner->group->find(kArwL, 1)->bind_animation(binding, true, true);
            break;
        case 2:
            pc.owner->group->find(kArwR, 1)->bind_animation(binding, true, true);
            break;
        case 3:
            pc.owner->group->find(kArwD, 1)->bind_animation(binding, true, true);
            break;
        }
        if (binding)
            binding->set_active(true);
        binding->set_rate(rate);
    }
    for (int i = 0; i < 4; ++i) {
        drc.arrows[i].object = drc.node->group->find(kArrowWholePanes[i], 1);
        drc.locks[i] = drc.node->group->find(kIconLockPanes[i], 1);
        tv.arrows[i].object = pc.owner->group->find(kArrowWholePanes[i], 1);
        tv.locks[i] = pc.owner->group->find(kIconLockPanes[i], 1);
    }
    for (int i = 0; i < 6; ++i) {
        tv.colors[i] = tv.node->group->find(kColorAnims[i], 1);
        drc.colors[i] = drc.node->group->find(kColorAnims[i], 1);
    }
    for (int i = 0; i < 9; ++i) {
        tv.moves[i] = tv.node->create_animation(kArrowMoveAnims[i], true);
        drc.moves[i] = drc.node->create_animation(kArrowMoveAnims[i], true);
        GameState* state = get_game()->state();
        if (i == 7 && state->mode == 3) {
            start_animation(tv.moves[i], rate);
            start_animation(drc.moves[i], rate);
        }
        state = get_game()->state();
        if (i == 8 && state->mode == 4) {
            start_animation(tv.moves[i], rate);
            start_animation(drc.moves[i], rate);
        }
    }
    headwind_anim = headwind->create_animation(kHeadwindAnims[0], true);
    if (game_mode() == 5 || game_mode() == 6)
        start_animation(headwind_anim, rate);
    for (int i = 0; i < 4; ++i) {
        pc.anims[i] = pc.owner->create_animation(kMoveAnims[i], true);
        gEffectManager->finish(0x4211);
    }
    pc.stop();
    if (timer) {
        timer_pos = timer->group->find(kNumTimerPos, 1);
        timer_plus_pos = timer->group->find(kNumTimerPlusPos, 1);
    }
    cursor_loop = cursor->create_animation(kLoopAnim, true);
    timer_in = timer->create_animation(kTimerBaseIn, true);
    timer_in->set_rate(rate);
    timer_num.anim = timer_num.node->create_animation(kNumTimerAnim, false);
    timer_red.anim = timer_red.node->create_animation(kNumTimerRedAnim, false);
    timer_plus.anim = timer_plus.node->create_animation(kNumTimerPlusAnim, false);
    hide(timer_num.node->group);
    hide(timer_red.node->group);
    hide(timer_plus.node->group);
    timer_pos->add(timer_num.node->group);
    timer_pos->add(timer_red.node->group);
    timer_plus_pos->add(timer_plus.node->group);
    timer_numbers[0].init(timer_num.node, timer_num.anim, 4);
    timer_numbers[1].init(timer_red.node, timer_red.anim, 4);
    timer_numbers[2].init(timer_plus.node, timer_plus.anim, 4);
    if (game_mode() == 7) {
        egg_groups[0] = egg_counter->group->find(kNumEggPos, 1);
        egg_groups[1] = egg_counter->group->find(kNumInstPos, 1);
        egg_groups[2] = egg_counter->group->find(kItemAdvDummy, 1);
        egg_groups[3] = egg_counter->group->find(kEggCounterBase, 1);
        egg_groups[4] = egg_counter->group->find(kEggCounterBasePwup, 1);
        egg_groups[5] = egg_counter->group->find(kInstCounterBase, 1);
        egg_groups[6] = egg_counter->group->find(kInstCounterBasePwup, 1);
        egg_groups[7] = egg_counter->group->find(kEggCounterCracked, 1);
        egg_inout = egg_counter->create_window_animation(kEggCounterInout, true);
        start_animation(egg_inout, rate);
        inst_inout = egg_counter->create_window_animation(kInstCounterInout, true);
        if (inst_inout)
            inst_inout->set_active(false);
        egg_anims[0] = eggs[0]->create_animation(kNumEggAnim, true);
        egg_anims[1] = eggs[1]->create_animation(kNumEggAnim, true);
        hide(eggs[0]->group);
        hide(eggs[1]->group);
        egg_anims[2] = eggs_pwup[0]->create_animation(kNumEggAnim, true);
        egg_anims[3] = eggs_pwup[1]->create_animation(kNumEggAnim, true);
        hide(eggs_pwup[0]->group);
        hide(eggs_pwup[1]->group);
        egg_groups[0]->add(eggs[0]->group);
        egg_groups[1]->add(eggs[1]->group);
        egg_groups[0]->add(eggs_pwup[0]->group);
        egg_groups[1]->add(eggs_pwup[1]->group);
        reset_scale(eggs[0]->group->find(kAdvZdl2NumEggPane, 1));
        reset_scale(eggs[1]->group->find(kAdvZdl2NumEggPane, 1));
        reset_scale(eggs_pwup[0]->group->find(kAdvZdl2NumEggPwupPane, 1));
        reset_scale(eggs_pwup[1]->group->find(kAdvZdl2NumEggPwupPane, 1));
        egg_numbers[0].init(eggs[0], egg_anims[0], 1);
        egg_numbers[1].init(eggs_pwup[0], egg_anims[2], 1);
        egg_numbers[2].init(eggs[1], egg_anims[1], 2);
        egg_numbers[3].init(eggs_pwup[1], egg_anims[3], 2);
    } else if (game_mode() == 8) {
        counters[0] = zdl3_counter->group->find(kCounterLinebeckShip, 1);
        hide(counters[0]);
        counters[1] = zdl3_counter->group->find(kCounterIronShip, 1);
        hide(counters[1]);
        counters[2] = zdl3_counter->group->find(kCounterGoldenShip, 1);
        hide(counters[2]);
        counters[3] = zdl3_counter->group->find(kCounterGodTrain, 1);
        hide(counters[3]);
        counters[4] = zdl3_counter->group->find(kCounterSteelTrain, 1);
        hide(counters[4]);
        counters[5] = zdl3_counter->group->find(kCounterGoldenTrain, 1);
        hide(counters[5]);
        num_pos = zdl3_counter->group->find(kNumPos, 1);
        counter_inout = zdl3_counter->create_animation(kCounterInout, true);
        if (counter_inout)
            counter_inout->set_active(false);
        num_anim = zdl3_num->create_animation(kNumAnim, true);
        hide(zdl3_num->group);
        reset_scale(zdl3_num->group->find(kAdvZdl3NumPane, 1));
        num_pos->add(zdl3_num->group);
        zdl3_number.init(zdl3_num, num_anim, 2);
        hourglass_anims[0] = hourglass_top->create_animation(kHourglass, true);
        hourglass_anims[1] = hourglass_bottom->create_animation(kHourglass, true);
        reset_scale(hourglass_top->group->find(kBgCloud, 1));
        reset_scale(hourglass_top->group->find(kHourglass, 1));
    } else if (game_mode() == 9) {
        for (int i = 0; i < 29; ++i) {
            signboard_anims[i] = signboard->create_window_animation(kSignboardAnims[i], true);
            if (signboard_anims[i])
                signboard_anims[i]->rewind();
            if (signboard_anims[i])
                signboard_anims[i]->set_active(false);
        }
        ptr21be0 = nullptr;
    }
    moon_scale = moon->create_window_animation(kMoonScale, true);
    moon_clash = moon->create_window_animation(kMoonClash, true);
    if (moon_clash)
        moon_clash->rewind();
    if (moon_clash)
        moon_clash->set_active(false);
    hide(moon->group->find(kCrash, 1));
    if (icons) {
        for (int i = 0; i < 20; ++i)
            hide(icons->group->find(kWeaponIconPanes[i], 1));
    }
    for (int i = 0; i < 10; ++i) {
        gEffectManager->create_node(&links[i], 0x420e, kNetworkLinkLayouts[i]);
        link_loops[i] = links[i]->create_animation(kLoopAnim, true);
    }
    for (int i = 0; i < 10; ++i) {
        gEffectManager->create_node(&plates[i], 0x420d, kAdvNetPlateLayout);
        plate_opens[i] = plates[i]->create_window_animation(kOpenAnim, true);
        int j = 0;
        do {
            hide(plates[i]->group->find(kNetPlatePanes[j], 1));
        } while (++j < 10);
        hide(plates[i]->group->find(kNetIconFriends, 1));
    }
    // The plates are walked with their own pointer (the original's latch steps the level offset first).
    LightEffectNode** plate = plates;
    for (int i = 0; i < 10; ++i, ++plate) {
        levels[i].object = (*plate)->group->find(kAdvTextLv, 1);
        show_icon(levels[i], 199);
    }
    ending_in = ending->create_window_animation(kInAnim, true);
    ending_loop = ending->create_window_animation(kLoopAnim, true);
    ending_out = ending->create_window_animation(kOutAnim, true);
    stop_animation(ending_in);
    stop_animation(ending_loop);
    stop_animation(ending_out);
    complete_end.object = ending->group->find(kAdvTextCompleteEnd, 1);
    show_icon(complete_end, 0xc4);
    complete_end_ef.object = ending->group->find(kAdvTextCompleteEndEf, 1);
    show_icon(complete_end_ef, 0xc4);
    value21aec = 0;
    expup_tv_text.object = expup_tv->group->find(kExpupDummy, 1);
    expup_drc_text.object = expup_drc->group->find(kExpupDummy, 1);
    show_icon(expup_tv_text, 0xc6);
    show_icon(expup_drc_text, 0xc6);
    expup_tv_in = expup_tv->create_window_animation(kExpupIn, true);
    if (expup_tv_in)
        expup_tv_in->set_active(false);
    expup_drc_in = expup_drc->create_window_animation(kExpupIn, true);
    if (expup_drc_in)
        expup_drc_in->set_active(false);
    complete_text.object = complete->group->find(kAdvTextComplete, 1);
    complete_text_00.object = complete->group->find(kAdvTextComplete00, 1);
    show_icon(complete_text, 0xc3);
    show_icon(complete_text_00, 0xc3);
    complete_icons[0] = complete->group->find(kIconHeartContainers, 1);
    complete_icons[1] = complete->group->find(kIconSkulltula, 1);
    complete_icons[2] = complete->group->find(kIconWpnS, 1);
    complete_icons[3] = complete->group->find(kIconFairy, 1);
    complete_in = complete->create_window_animation(kInAnim, true);
    if (complete_in)
        complete_in->set_active(false);
    EffectGroup* window = complete->group;
    window->offset30 = -39.0f;
    window->offset34 = 267.0f;
    window->flags58 |= 0x10;
    // The finish check and the rate reread the effects through a plain pointer to the array: the original computes
    // their address again in each block (a different address expression from the store's keeps them apart).
    LayoutAnimation** effects = reinterpret_cast<LayoutAnimation**>(reinterpret_cast<unsigned char*>(this) + 0x2e8);
    int i = 0;
    do {
        weapon_effects[i] = icons->create_window_animation(kWeaponEffectAnims[i], true);
        if (i < 4) {
            if (weapon_effects[i])
                weapon_effects[i]->set_active(true);
        } else {
            if (weapon_effects[i])
                weapon_effects[i]->set_active(false);
            if (effects[i])
                effects[i]->finish();
        }
        effects[i]->set_rate(rate);
    } while (++i < 8);
    face_dummy = icons->group->find(kPcFaceDummy, 1);
    reset_scale(arrivals[0].node->group);
    arrivals[0].anim = arrivals[0].node->create_animation(kArrivalAnim, true);
    if (arrivals[0].anim)
        arrivals[0].anim->set_active(false);
    reset_scale(arrivals[1].node->group);
    arrivals[1].anim = arrivals[1].node->create_animation(kArrivalAnim, true);
    if (arrivals[1].anim)
        arrivals[1].anim->set_active(false);
    arrivals[2].anim = arrivals[2].node->create_animation(kArrivalAnim, true);
    if (arrivals[2].anim)
        arrivals[2].anim->set_active(false);
    gEffectManager->attach(&resource76f0, nullptr);
    gEffectManager->attach_resource(&resource7800);
    initialized = 1;
    state = 3;
    Game* game = get_game();
    Player& player = game->players[game_mode()];
    flag2b8 = 0;
    value2c4 = -1;
    value2c8 = 8;
    cell2bc = player.id;
    cell2c0 = player.id;
    direction = 1;
    switch (player.facing) {
    case 0:
        direction = 0;
        break;
    case 1:
        direction = 2;
        break;
    case 2:
        direction = 3;
        break;
    case 3:
        direction = 1;
        break;
    }
    pc.stop();
    pc.anims[direction]->set_rate(1.0f);
    if (pc.anims[direction])
        pc.anims[direction]->set_active(true);
    if (cursor_loop) {
        cursor_loop->set_rate(rate);
        if (cursor_loop)
            cursor_loop->set_active(true);
    }
    for (int i = 0; i < 10; ++i) {
        if (link_loops[i]) {
            link_loops[i]->set_rate(rate);
            if (link_loops[i])
                link_loops[i]->set_active(true);
        }
    }
    for (int i = 0; i < 4; ++i) {
        play(tv.moves[i], rate);
        if (drc.moves[i])
            play(drc.moves[i], rate);
    }
    if (tv.moves[4]) {
        tv.moves[4]->set_rate(rate);
        if (tv.moves[4])
            tv.moves[4]->set_active(false);
    }
    if (drc.moves[4]) {
        drc.moves[4]->set_rate(rate);
        if (drc.moves[4])
            drc.moves[4]->set_active(false);
    }
    hide(icons->group->find(kAdvIconLock, 1));
    int cell = player.id;
    view_left = 5;
    view_top = 5;
    view_right = 9;
    view_bottom = 7;
    int column = cell % 16;
    int row = cell / 16;
    if ((cell & ~0xf) != 0x60 || static_cast<unsigned int>(column - 6) >= 3) {
        if (column <= 4) {
            view_left = column;
            float right = column + 4;
            view_right = right;
            scroll_x = (5 - column) * 64;
        } else if (column > 9) {
            view_right = column;
            float left = column - 4;
            view_left = left;
            scroll_x = (9 - column) * 64;
        }
        if (cell < 0x50) {
            view_top = row;
            float bottom = row + 2;
            view_bottom = bottom;
            scroll_y = (5 - row) * -44;
        } else if (cell >= 0x80) {
            view_bottom = row;
            float top = row - 2;
            view_top = top;
            scroll_y = (7 - row) * -44;
        }
    }
    if (game_mode() == 8) {
        if (!get_game()->progress.record(0xa9)) {
            scroll_x = -64.0f;
            scroll_y = -88.0f;
            view_left = 6;
            view_top = 3;
            view_right = 10;
            view_bottom = 5;
        }
    } else if (game_mode() == 9) {
        if (!get_game()->progress.record(0xb1)) {
            scroll_x = 128.0f;
            scroll_y = 0.0f;
            view_left = 3;
            view_top = 5;
            view_right = 7;
            view_bottom = 7;
        }
    }
    update_icons();
    update_counters();
    update_plates();
    update_view();
}
