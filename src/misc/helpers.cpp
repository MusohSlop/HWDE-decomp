// Small helpers picked by tools/rank_targets.py whose callees are all named: battle-setup flag
// wrappers and fixed-size clears. They come from several game source files; each definition
// names the address region of the original file it likely belongs to, for a later split.
// Names are descriptive placeholders. Status: matching/README.md.

extern "C" void* memset(void* dest, int value, unsigned long size);

// A byte block cleared by value-initialization (`block = {}`). Where the original clears an
// array after storing other fields, this keeps the stores in front of the memset; a loop or an
// explicit memset lets them move behind it (matching/scratch/memset_probe).
template <unsigned long N> struct ByteBlock {
    unsigned char bytes[N];
};

class BattleSetup {
public:
    void clear_flags(int flags);                                            // 0x710016f29c
    void set_flags(int flags);                                              // 0x710016f2ac

    unsigned int flags;       // +00
};
BattleSetup* get_battle_setup();                                            // 0x710016ef34

// 0x7100255f54; original file: battle setup wrappers, 0x7100255f54-0x7100256680
void enable_battle_flag_25() {
    get_battle_setup()->set_flags(0x2000000);
}

// 0x7100255f6c; original file: battle setup wrappers, 0x7100255f54-0x7100256680
void disable_battle_flag_25() {
    get_battle_setup()->clear_flags(0x2000000);
}

// 0x71002560e0; original file: battle setup wrappers, 0x7100255f54-0x7100256680
unsigned char battle_flag_3() {
    return get_battle_setup()->flags >> 3 & 1;
}

// 0x7100256140; original file: battle setup wrappers, 0x7100255f54-0x7100256680
unsigned char battle_flag_20() {
    return get_battle_setup()->flags >> 20 & 1;
}

// 0x7100256680; original file: battle setup wrappers, 0x7100255f54-0x7100256680
void enable_battle_flag_20() {
    get_battle_setup()->set_flags(0x100000);
}

// 0x71001f8700; original file: light records, 0x71001f8700
struct LightRecordSet {
    void clear();

    int count;                // +00
    unsigned long records[0x13]; // +08
};

void LightRecordSet::clear() {
    count = 0;
    for (unsigned int i = 0; i < 0x13; ++i)
        records[i] = 0;
}

// 0x7100208ad4; original file: game data tables, 0x7100208ad4
struct GameDataBlock {
    void clear();
    unsigned char data[0x3480];
};

void GameDataBlock::clear() {
    for (unsigned int i = 0; i < sizeof(data); ++i)
        data[i] = 0;
}

// 0x7100209aa0; original file: game data tables, 0x7100209aa0
struct ProfileName {
    void clear();
    unsigned char data[0x6e];
};

void ProfileName::clear() {
    for (unsigned int i = 0; i < sizeof(data); ++i)
        data[i] = 0;
}

// 0x710020b280; original file: profile statistics, 0x710020b280
struct StatSlots {
    void reset();
    unsigned char slots[0x100];
};

void StatSlots::reset() {
    for (unsigned int i = 0; i < sizeof(slots); ++i)
        slots[i] = 0xff;
}

// 0x710020efa8; original file: unit database, 0x710020ec80-0x710020efa8
struct UnitSlots {
    void reset();
    unsigned char slots[0x960];
};

void UnitSlots::reset() {
    for (unsigned int i = 0; i < sizeof(slots); ++i)
        slots[i] = 0xff;
}

// Path buffer next to the resource cache (0x7100c8b0a8), addressed directly.
extern unsigned char gResourcePath[0x202] __attribute__((visibility("hidden")));

// 0x710025b36c; original file: resource cache, 0x710025b0c0-0x710025b36c
void clear_resource_path() {
    for (unsigned int i = 0; i < sizeof(gResourcePath); ++i)
        gResourcePath[i] = 0;
}

unsigned long get_system_tick();                                            // 0x71006009e0 (nn::os::GetSystemTick)

class ProfileStats {
public:
    int value(int id);                                                      // 0x710020ba78
};
class Profile {
public:
    ProfileStats* stats();                                                  // 0x710020b970
    int skill_value(int index);
    int item_value(unsigned int index);
};

// An item record's statistic; the record starts with its owner's profile.
struct ItemStatRef {
    int stat_value();

    unsigned char pad[0xc];
    short stat;               // +0c
};

// 0x71001fe68c; original file: item table, 0x71001ff050-0x71001ff2c8 (just before it)
int ItemStatRef::stat_value() {
    return reinterpret_cast<Profile*>(this)->stats()->value(stat);
}

struct WeaponStatRef {
    int stat_value();

    unsigned char pad[0xc];
    short stat;               // +0c
};

// 0x7100215124; original file: weapon table, 0x7100215124-0x7100215d34
int WeaponStatRef::stat_value() {
    return reinterpret_cast<Profile*>(this)->stats()->value(stat);
}

class Game {
public:
    int query(int id);                                                      // 0x71002046fc
};
Game* get_game();                                                           // 0x7100204728

// 0x7100207ad8; original file: game queries, 0x7100207ad8
int game_query(int id) {
    return get_game()->query(id);
}

// 0x71002020ac; original file: game object, 0x71002020ac-0x7100204c10
struct TickTimer {
    void start();

    unsigned long started;    // +00
    unsigned char done;       // +08
};

void TickTimer::start() {
    started = get_system_tick();
    done = 0;
}

// 0x71002addbc; original file: shared state, 0x71002ad584-0x71002addbc
struct TaskClock {
    long elapsed();

    unsigned char pad[0x268];
    unsigned long started;    // +268
};

long TaskClock::elapsed() {
    return get_system_tick() - started;
}

class OptionSource;
// Reached through the GOT slot at 0x7100c232d8.
extern OptionSource* gOptionSource;
void operator delete(void* ptr) noexcept;                                    // 0x71003ccc84

// 0x710020bf20; original file: region/option settings, 0x710020bd74-0x710020c22c (before it)
void destroy_option_source() {
    if (gOptionSource) {
        operator delete(gOptionSource);
        gOptionSource = nullptr;
    }
}

class TrackRenderer {
public:
    void flush(int layer);                                                  // 0x71001df128
};
// Reached through the GOT slot at 0x7100c22a40.
extern TrackRenderer* gTrackRenderer;

// 0x7100287be4; original file: board cursor/camera, 0x7100287be4
void flush_track_renderer() {
    gTrackRenderer->flush(-1);
    gTrackRenderer->flush(-1);
}

class ObjectManager;
class WorkerMutex;
// Reached through the GOT slot at 0x7100c21de8.
extern ObjectManager* gObjectManager;
WorkerMutex* create_mutex(ObjectManager* manager);                          // 0x71005c418c
// The system mutex (0x7100cf03f0), addressed directly.
extern WorkerMutex* gSystemMutex __attribute__((visibility("hidden")));

// 0x7100459b2c; original file: worker/system helpers, 0x7100459xxx
void create_system_mutex() {
    gSystemMutex = create_mutex(gObjectManager);
}

class LayoutAnimation {
public:
    unsigned short frame_count();                                           // 0x71005ce178

    unsigned char pad[0x20];
    float frame;              // +20
};

// 0x71002a6398; original file: board popups, 0x71002a6398-0x71002aadac
struct PopupAnimView {
    bool finished();

    unsigned char pad[0x7978];
    LayoutAnimation* anim;    // +7978
};

bool PopupAnimView::finished() {
    LayoutAnimation* animation = anim;
    float frame = animation->frame;
    return frame == animation->frame_count();
}

class StatusBlock {
public:
    void initialize();                                                      // 0x7100205824
};

// 0x71002880fc; original file: board cursor/camera, 0x71002880fc
struct StatusPanel {
    void reset();

    int value0;               // +00
    StatusBlock block;        // +04
    unsigned char pad[0x9b];
};

void StatusPanel::reset() {
    StatusBlock* status = &block;
    memset(this, 0, 0xa0);
    status->initialize();
}
// 0x710020c6b0; original file: region/option settings, 0x710020bd74-0x710020c22c (after it)
struct OptionTables {
    void reset();

    unsigned char values[0x1a90];  // +0000
    unsigned char slots[0x190];    // +1a90
};

void OptionTables::reset() {
    for (unsigned int i = 0; i < sizeof(values); ++i)
        values[i] = 0;
    for (unsigned int i = 0; i < sizeof(slots); ++i)
        slots[i] = 0xff;
}

// 0x71002102ec; original file: unit database tables, 0x71002102ec
struct UnitTable {
    void reset();

    unsigned char slots[0xb4];     // +00
    unsigned char values[0x5a];    // +b4
};

void UnitTable::reset() {
    for (unsigned int i = 0; i < sizeof(values); ++i)
        values[i] = 0;
    for (unsigned int i = 0; i < sizeof(slots); ++i)
        slots[i] = 0xff;
}

extern "C" void* memcpy(void* dest, const void* src, unsigned long size);

// 0x7100210d94; original file: unit database tables, 0x7100210d94
struct UnitRecord {
    void assign(const UnitRecord* other);

    int id;                   // +00: kept on assignment
    unsigned char data[0x4c];
};

void UnitRecord::assign(const UnitRecord* other) {
    int keep = id;
    if (other && other != this)
        memcpy(this, other, sizeof(*this));
    id = keep;
}

// 0x71001fbc04; original file: data stream, 0x71001fbbb0-0x71001fbe00
struct StreamBuffer {
    bool open(int writing, unsigned int size, unsigned char* buffer);

    unsigned char pad[8];
    unsigned char* begin;     // +08
    unsigned char* cursor;    // +10
    unsigned int size;        // +18
    int writing;              // +1c
};

bool StreamBuffer::open(int writing, unsigned int size, unsigned char* buffer) {
    begin = buffer;
    cursor = buffer;
    this->size = size;
    this->writing = writing;
    if (!writing)
        memset(buffer, 0, size);
    return begin != nullptr;
}

struct SharedState {
    unsigned char pad[4];
    int stage;                // +04
};
SharedState* get_shared_state();                                            // 0x71002aae3c
void* load_layout(int id);                                                  // 0x71001f7868
// Reached through the GOT slot at 0x7100c22ed8.
extern void* gStageLayout;

// 0x71001dd920; original file: stage layout, 0x71001dd920
void load_stage_layout() {
    int stage = get_shared_state()->stage;
    gStageLayout = load_layout(stage == 6 ? 0x1f40 : stage + 0x1f3f);
}

struct TextDatabase {
    unsigned char pad[4];
    int language;             // +04
};
// Reached through the GOT slot at 0x7100c233a0.
extern TextDatabase gTextDatabase;

// 0x7100217c7c; original file: text database, 0x7100217c7c-0x7100217d64
bool text_language_changed() {
    int language = gTextDatabase.language;
    int stage = get_shared_state()->stage;
    return language != (stage == 6 ? 1 : stage);
}

void notify_light_aborted(int id);                                          // 0x71003fe2d4
// Reached through the GOT slot at 0x7100c2a538.
extern int gPendingLights[20];

// 0x7100251c8c; original file: pending lights, 0x7100251c8c
void abort_pending_lights() {
    for (int i = 0; i < 20; ++i) {
        if (gPendingLights[i] != -1)
            notify_light_aborted(gPendingLights[i]);
    }
}

// Reached through the GOT slot at 0x7100c22e90.
extern unsigned int gFrameCounter;

// 0x71001d3244; original file: frame counter, 0x71001d3244
void advance_frame_counter() {
    if (!(get_battle_setup()->flags & 0x4000)) {
        unsigned int next = gFrameCounter + 1;
        gFrameCounter = next > 0x5ff ? 0 : next;
    }
}
// 0x7100455858; original file: battle setup wrappers, 0x7100455858
unsigned char battle_flag_0() {
    return get_battle_setup()->flags & 1;
}

unsigned char game_has_flag(Game* game, int flag);                          // 0x71002026fc

// 0x710000dbd4; original file: game queries, 0x710000dbd4
unsigned char game_flag_17() {
    return game_has_flag(get_game(), 0x11);
}

struct Global425dd0 {
    unsigned char pad[0x10];
    void* part10;             // +10
    unsigned char pad18[8];
    void* part20;             // +20
    void* part28;             // +28
    unsigned char pad30[0x2aa4];
    int value2ad4;            // +2ad4
};
Global425dd0* load_global_425dd0();                                         // 0x7100425dd0

// 0x71004544f0; original file: global queries, 0x71004544f0
int global_425dd0_value() {
    return load_global_425dd0()->value2ad4;
}

struct Global4449ec {
    unsigned char pad[0x80];
    int value80;              // +80
};
Global4449ec* load_global_4449ec();                                         // 0x71004449ec

// 0x7100453984; original file: global queries, 0x7100453984
int global_4449ec_value() {
    return load_global_4449ec()->value80;
}

void* load_global_20fbd4();                                                 // 0x710020fbd4
void* resolve_20ff60(void* object);                                         // 0x710020ff60
void finish_752d8(void* object);                                            // 0x71000752d8

// 0x710003d04c; original file: global chains, 0x710003d04c
void global_chain_3d04c() {
    finish_752d8(resolve_20ff60(load_global_20fbd4()));
}

// 0x710058fac4; original file: tables, 0x710058fac4
struct ByteTable {
    void clear();
    unsigned char bytes[0x100];
};

void ByteTable::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}
// 0x710046abc4; original file: record copies, 0x710046abc4
struct RecordCopy {
    bool load(const void* source);

    unsigned char pad[0x30];
    unsigned char data[0x1c0]; // +30
};

bool RecordCopy::load(const void* source) {
    memcpy(data, source, sizeof(data));
    return true;
}

// 0x7100434364; original file: tables, 0x7100434364
struct CountedTable {
    void clear();

    unsigned char bytes[0x90]; // +00
    unsigned char pad90[8];
    int count;                // +98
};

void CountedTable::clear() {
    count = 0;
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x710024884c; original file: tables, 0x710024884c
struct TailTable {
    void clear();

    unsigned char pad[0x68];
    unsigned char bytes[0x2018]; // +68
};

void TailTable::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

struct BattleSetupBytes {
    unsigned char value0[2];
    unsigned char flags2;     // +02
};
struct BattleSetupHalves {
    unsigned short value0;
    unsigned short flags2;    // +02
};

// 0x710000ea88; original file: battle setup wrappers, 0x710000ea88-0x710000eaa8
bool battle_mode_flags() {
    return reinterpret_cast<BattleSetupBytes*>(get_battle_setup())->flags2 & 0x30;
}

// 0x710000eaa8; original file: battle setup wrappers, 0x710000ea88-0x710000eaa8
unsigned char battle_flag_16() {
    return reinterpret_cast<BattleSetupHalves*>(get_battle_setup())->flags2 & 1;
}

struct Global4140a4 {
    unsigned char pad[0x2194];
    unsigned int flags;       // +2194
};
Global4140a4* load_global_4140a4();                                         // 0x71004140a4

// 0x7100453590; original file: global queries, 0x7100453590
unsigned char global_4140a4_flag_10() {
    return load_global_4140a4()->flags >> 10 & 1;
}

void* load_global_455ebc();                                                 // 0x7100455ebc
void apply_4573b8(void* object, void* value);                               // 0x71004573b8

// 0x7100452b34; original file: global queries, 0x7100452b34
void forward_452b34(void* value) {
    apply_4573b8(load_global_455ebc(), value);
}

struct StageBgm {
    unsigned char pad[0xf14];
    int base_id;              // +f14
};
// Reached through the GOT slot at 0x7100c2b710.
extern StageBgm* gStageBgm;
void play_bgm(int id, float fade, int a, int b, void* c);                   // 0x71003f9b34

// 0x71003ff164; original file: stage music, 0x71003ff164
void play_stage_bgm(int muted) {
    if (!gStageBgm || muted || gStageBgm->base_id == -1)
        return;
    int stage = get_shared_state()->stage;
    int id;
    if (stage == 0 || get_shared_state()->stage == 9 || get_shared_state()->stage == 11)
        id = gStageBgm->base_id + 0x190;
    else if (get_shared_state()->stage == 10)
        id = gStageBgm->base_id + 0x190;
    else
        id = gStageBgm->base_id + 0x1c2;
    play_bgm(id, 32.0f, 1, 0, nullptr);
}
// 0x710040bbb8; original file: tables, 0x710040bbb8
struct HugeTable {
    void clear();

    unsigned char pad[0x30000];
    unsigned char bytes[0x20004]; // +30000
};

void HugeTable::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x71001cba88; original file: tables, 0x71001cba88
struct InnerTable {
    void clear();

    unsigned char pad[0x2198];
    unsigned char bytes[0xc8]; // +2198
};

void InnerTable::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x71001a844c, 0x71001a8474; original file: light presets, 0x71001a844c-0x71001a8d3c
struct PresetTable {
    void reset();

    int count;                // +00
    int selected;             // +04
    unsigned char bytes[0x400]; // +08
};

void PresetTable::reset() {
    count = 0;
    selected = -1;
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

struct PresetTableCopy {
    void reset();

    int count;                // +00
    int selected;             // +04
    unsigned char bytes[0x400]; // +08
};

void PresetTableCopy::reset() {
    count = 0;
    selected = -1;
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

class LightPreset {
public:
    int value(int index);                                                   // 0x71001a8d3c
};
LightPreset* current_light_preset();                                        // 0x71001a8c38

// 0x71003336d4; original file: light preset queries, 0x71003336d4
int preset_value(void* owner, int index) {
    return current_light_preset()->value(index);
}

void* load_layout(int id);                                                  // 0x71001f7868
// Reached through the GOT slots at 0x7100c2abf0 and 0x7100c2ab50.
extern void* gLayout_44c5;
extern void* gLayout_4691;

// 0x71002ede70; original file: scene layouts, 0x71002ede70
void load_layout_44c5() {
    gLayout_44c5 = load_layout(0x44c5);
}

// 0x71002d7190; original file: scene layouts, 0x71002d7190
void load_layout_4691() {
    gLayout_4691 = load_layout(0x4691);
}

void apply_457960(void* object, int value);                                 // 0x7100457960

// 0x7100135cc4; original file: global queries, 0x7100135cc4
struct SignedByteHolder {
    void forward();

    unsigned char pad[0x10c];
    signed char value;        // +10c
};

void SignedByteHolder::forward() {
    int v = value;
    apply_457960(load_global_455ebc(), v);
}
// 0x71005f8c80, 0x71005f766c; original file: record copies, 0x71005f766c-0x71005f8c80
struct RecordAt48 {
    bool copy_to(void* out);

    unsigned char pad[0x48];
    unsigned char data[0x80]; // +48
};

bool RecordAt48::copy_to(void* out) {
    memcpy(out, data, sizeof(data));
    return true;
}

struct RecordAt20 {
    bool copy_to(void* out);

    unsigned char pad[0x20];
    unsigned char data[0x80]; // +20
};

bool RecordAt20::copy_to(void* out) {
    memcpy(out, data, sizeof(data));
    return true;
}

void part_call_434a24(void* part, int value);                               // 0x7100434a24
void part_call_41fe04(void* part, int value);                               // 0x710041fe04
void part_call_41fe38(void* part, int value);                               // 0x710041fe38
void part_call_41fe1c(void* part, int value);                               // 0x710041fe1c

// 0x71004540b4; original file: global queries, 0x71004540b4-0x7100453d48
void global_part28_434a24(int value) {
    part_call_434a24(load_global_425dd0()->part28, value);
}

// 0x7100453d48
void global_part20_41fe04(int value) {
    part_call_41fe04(load_global_425dd0()->part20, value);
}

// 0x7100453ce0
void global_part20_41fe38(int value) {
    part_call_41fe38(load_global_425dd0()->part20, value);
}

// 0x7100453cb8
void global_part20_41fe1c(int value) {
    part_call_41fe1c(load_global_425dd0()->part20, value);
}

struct Global455ebc {
    unsigned char pad[0x76];
    unsigned short value76;   // +76
};

// 0x7100452ad0; original file: global queries, 0x7100452ad0
bool global_455ebc_active() {
    return load_global_455ebc() &&
           reinterpret_cast<Global455ebc*>(load_global_455ebc())->value76 != 0;
}

struct SharedResources;
SharedResources* shared_state_resources(SharedState* state);                // 0x71002ad1dc
int resources_value_389164(SharedResources* resources);                     // 0x7100389164

// 0x71003c750c; original file: shared-state resource queries, 0x71003c72b0-0x71003c750c
int resources_value() {
    if (SharedResources* resources = shared_state_resources(get_shared_state()))
        return resources_value_389164(resources);
    return -1;
}

class LightEffectNode {
public:
    void draw(int layer);                                                   // 0x71001e34a0
};

// 0x71003b5ac8; original file: scene drawing, 0x71003b5ac8
void draw_node_and_flush(LightEffectNode* node) {
    node->draw(0);
    gTrackRenderer->flush(-1);
}

struct ScreenFaderView {
    unsigned char busy();                                                   // 0x71001e52c8

    unsigned char pad[0x1f8];
    int color;                // +1f8
};
ScreenFaderView* screen_fader();                                            // 0x71001e50b0

// 0x71003885d4; original file: scene fades, 0x71003885d4
bool screen_fader_white() {
    return screen_fader() && screen_fader()->color == 1;
}

class MaterialBook {
public:
    void entry(int id);                                                     // 0x71002015a8
};
MaterialBook* load_global_200fc0();                                         // 0x7100200fc0

// 0x71001a8d54; original file: light presets, 0x71001a844c-0x71001a8d3c (after it)
struct PresetMaterials {
    void apply(int index);

    unsigned char pad[0x14];
    int materials[1];         // +14
};

void PresetMaterials::apply(int index) {
    int id = materials[index];
    load_global_200fc0()->entry(id);
}

struct Global187590 {
    unsigned char pad[0xa4];
    unsigned char flags[1];   // +a4
};
Global187590* load_global_187590();                                         // 0x7100187590

// 0x71000d8180; original file: global queries, 0x71000d8180
unsigned char global_187590_flag(void* owner, unsigned int index) {
    return load_global_187590()->flags[index];
}

// 0x710000eb14; original file: battle setup wrappers, 0x710000ea88-0x710000eb14
bool battle_mode_bits() {
    return *reinterpret_cast<unsigned long*>(get_battle_setup()) & 0x100900000UL;
}
// 0x71005eb5e8; original file: tables, 0x71005eb5e8
struct ScaledTable {
    void reset();

    unsigned char active;     // +00
    unsigned char pad1[3];
    float scale;              // +04
    unsigned char bytes[0x70]; // +08
};

void ScaledTable::reset() {
    active = 0;
    scale = 1.0f;
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

void global_call_427444(Global425dd0* global, void* a, void* b);            // 0x7100427444

// 0x71004544c4; original file: global queries, 0x71004540b4-0x7100453d48
void global_pair_427444(void* a, void* b) {
    global_call_427444(load_global_425dd0(), a, b);
}


void global_call_416abc(Global4140a4* global, void* a, int b);              // 0x7100416abc

// 0x71004535ac; original file: global queries, 0x7100453590-0x7100453638
void global_pair_416abc(void* a, int b) {
    global_call_416abc(load_global_4140a4(), a, b);
}

void* load_global_458634();                                                 // 0x7100458634
void global_call_45938c(void* global, float a, float b);                    // 0x710045938c

// 0x710040e2a4; original file: global queries, 0x710040e2a4
void global_floats_45938c(float a, float b) {
    global_call_45938c(load_global_458634(), a, b);
}

// 0x7100252074; original file: tables, 0x7100252074
struct SlotTable {
    void reset();

    long value0;              // +00
    long value8;              // +08
    long value10;             // +10
    unsigned char slots[0xc9c]; // +18
};

void SlotTable::reset() {
    value0 = 0;
    value8 = 0;
    value10 = 0;
    for (unsigned int i = 0; i < sizeof(slots); ++i)
        slots[i] = 0xff;
}

// 0x7100048918; original file: tables, 0x7100048918
struct VastTable {
    void clear();

    unsigned char pad[0x10940];
    unsigned char bytes[0x57808]; // +10940
};

void VastTable::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x71005fad40; original file: tables, 0x71005fad40
struct HeaderTable {
    void reset();

    long value0;              // +00
    int value8;               // +08
    unsigned char padc[4];
    unsigned char bytes[0xab]; // +10
    unsigned char padbb;
    int valuebc;              // +bc
};

void HeaderTable::reset() {
    value0 = 0;
    value8 = 0;
    valuebc = 0;
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

void* load_global_3d2fd4();                                                 // 0x71003d2fd4
void global_call_3d68a8(void* global, int id, int flags);                   // 0x71003d68a8

// 0x710045595c; original file: global queries, 0x710045595c
void global_flagged_3d68a8(int id, unsigned char flag) {
    bool set = flag != 0;
    global_call_3d68a8(load_global_3d2fd4(), id, set << 1);
}
void part_call2_41fda8(void* part, int a, int b);                            // 0x710041fda8

// 0x7100453da0; original file: global queries, 0x71004540b4-0x7100453d48 (nearby)
void global_part20_41fda8(int a, int b) {
    part_call2_41fda8(load_global_425dd0()->part20, a, b);
}

struct Global4140a4Records {
    unsigned char pad[0x4a30];
    unsigned char records[1][0x7d0]; // +4a30
};

// 0x7100453608; original file: global queries, 0x7100453590-0x7100453638
void* global_4140a4_record(int index) {
    return reinterpret_cast<Global4140a4Records*>(load_global_4140a4())->records[index];
}

class DemoLightSystem {
public:
    void render();                                                          // 0x710025f944
};
// Reached through the GOT slot at 0x7100c22d98.
extern DemoLightSystem* gDemoLightSystem;

// 0x71003b0188; original file: scene drawing, 0x71003b0188
void render_lights_and_flush() {
    gDemoLightSystem->render();
    gTrackRenderer->flush(-1);
}

class LayoutSpriteObject {
public:
    LayoutSpriteObject();                                                   // 0x71001ef52c
    virtual void v00();
    unsigned char pad[0x40];
};

// 0x71002cdb5c; original file: layout widgets, 0x71002cdb5c
struct SpriteWidget {
    SpriteWidget();

    int value0;               // +00
    LayoutSpriteObject sprite; // +08
    int value50;              // +50
    long value58;             // +58
    long value60;             // +60
};

SpriteWidget::SpriteWidget() : value0(0), value50(0), value58(0), value60(0) {}

void call_1d738c(void* object, int a, int b);                               // 0x71001d738c
// Reached through the GOT slot at 0x7100c22ca8.
extern void* gGlobal_c22ca8;

// 0x7100256698; original file: battle setup wrappers, 0x7100255f54-0x7100256698
void disable_battle_flag_20() {
    get_battle_setup()->clear_flags(0x100000);
    call_1d738c(gGlobal_c22ca8, 9, 0);
}

void call_1d2ae8(int a, int b, int c);                                      // 0x71001d2ae8

// 0x71001d2e60; original file: frame counter, 0x71001d2e60-0x71001d3244
void start_default_effect() {
    if (!(get_battle_setup()->flags & 0x4000))
        call_1d2ae8(0x79, 0xbb8, 0x258);
}

class DataChunk {
public:
    DataChunk();                                                            // 0x7100218c18
    unsigned char pad[0x10];
};

// 0x71001af410; original file: data chunks, 0x71001af410
struct ChunkPair {
    ChunkPair();

    DataChunk first;          // +00
    long value10;             // +10
    DataChunk second;         // +18
    long value28;             // +28
};

ChunkPair::ChunkPair() {
    value10 = 0;
    value28 = 0;
}

// 0x710004c054; original file: tables, 0x710004c054
struct CountedBlock {
    void reset();

    long value0;              // +00
    long value8;              // +08
    long value10;             // +10
    int value18;              // +18
    unsigned char pad1c[4];
    ByteBlock<0x1f4> bytes;   // +20
};

void CountedBlock::reset() {
    value18 = 0;
    value0 = 0;
    value8 = 0;
    value10 = 0;
    bytes = {};
}

unsigned int index_3d6fd0(void* global);                                    // 0x71003d6fd0

// 0x710003a020; original file: global queries, 0x710003a020
struct CountTable {
    void clear_current();

    unsigned char pad[0x84c0];
    int counts[1];            // +84c0
};

void CountTable::clear_current() {
    counts[index_3d6fd0(load_global_3d2fd4())] = 0;
}
// 0x71003885ac; original file: scene fades, 0x71003885ac-0x71003885d4
unsigned char screen_fader_busy() {
    if (screen_fader())
        return screen_fader()->busy();
    return 1;
}

// 0x710000eaec; original file: battle setup wrappers, 0x710000ea88-0x710000eb14
bool battle_mode_bits_copy() {
    return *reinterpret_cast<unsigned long*>(get_battle_setup()) & 0x100900000UL;
}

// 0x710000eac4; original file: battle setup wrappers, 0x710000ea88-0x710000eb14
bool battle_mode_clear() {
    return (*reinterpret_cast<unsigned long*>(get_battle_setup()) & 0x10000000cUL) == 0;
}

void part_call2_41fd80(void* part, int a, int b);                            // 0x710041fd80

// 0x7100453d70; original file: global queries, 0x71004540b4-0x7100453d48 (nearby)
void global_part20_41fd80(int a, int b) {
    part_call2_41fd80(load_global_425dd0()->part20, a, b);
}

// 0x71004535d8; original file: global queries, 0x7100453590-0x7100453638
int global_4140a4_record_value(int index) {
    return *reinterpret_cast<int*>(reinterpret_cast<Global4140a4Records*>(load_global_4140a4())->records[index] + 0x794);
}
void global_call_4272f0(Global425dd0* global, int id, float value);          // 0x71004272f0

// 0x7100453ecc; original file: global queries, 0x7100453da0-0x7100453ecc
void global_float_4272f0(int id, float value) {
    global_call_4272f0(load_global_425dd0(), id, value);
}

class CaptionLayer {
public:
    void show(int a, int b);                                                // 0x71001de2ec

    unsigned char pad[0x10];
    int value10;              // +10
};
// Reached through the GOT slot at 0x7100c22ef8.
extern CaptionLayer* gCaptionLayer;

// 0x71003890f4; original file: scene captions, 0x71003890f4
void show_caption_layer(void* owner, int a, int b, int value) {
    gCaptionLayer->show(a, b);
    gCaptionLayer->value10 = value;
}

void release_light(void** slot);                                            // 0x71001f7960

// 0x71002d71b4; original file: scene layouts, 0x71002d7190-0x71002d71b4
void release_layout_4691() {
    if (gLayout_4691) {
        release_light(&gLayout_4691);
        gLayout_4691 = nullptr;
    }
}

short forward_value_3f388();                                                // 0x710003f388

// 0x710024c7f8; original file: lazy ids, 0x710024c7f8
struct LazyId {
    int resolve();

    unsigned char pad[0x78];
    int id;                   // +78
};

int LazyId::resolve() {
    if (id == -1)
        id = forward_value_3f388();
    return id;
}
// 0x71005ec504; original file: tables, 0x71005ec504
struct TrailerTable {
    void reset();

    ByteBlock<0x300> bytes;   // +000
    long value300;            // +300
    long value308;            // +308
    long value310;            // +310
    long value318;            // +318
    unsigned char active;     // +320
};

void TrailerTable::reset() {
    value300 = 0;
    active = 1;
    value318 = 0;
    value310 = 0;
    value308 = 0;
    bytes = {};
}

struct Block40 {
    unsigned char bytes[0x40];
};

// 0x71003dfb34; original file: block copies, 0x71003dfb34
Block40* copy_block40(void* owner, Block40* out, const Block40* in) {
    memcpy(out, in, sizeof(Block40));
    return out;
}

struct PanelPane;
struct TrackLightTarget;
void set_pane_lines(PanelPane* pane, TrackLightTarget* targets, unsigned int count); // 0x71001e41d8

// 0x71003a5144; original file: panel drawing, 0x71003a5144
struct LinePanel {
    void draw();

    LightEffectNode* node;    // +00
    unsigned char pad8[0x18];
    PanelPane* pane;          // +20
    unsigned char pad28[0x18];
    unsigned char lines[1];   // +40
};

void LinePanel::draw() {
    set_pane_lines(pane, reinterpret_cast<TrackLightTarget*>(lines), 0x20);
    node->draw(0);
}

short forward_value_3f378();                                                // 0x710003f378

// 0x71002471a8; original file: lazy ids, 0x71002471a8
struct LazyId8 {
    int resolve();

    void* owner;              // +00
    int id;                   // +08
};

int LazyId8::resolve() {
    if (id == -1)
        id = forward_value_3f378();
    return id;
}
int random_below(int limit);                                                // 0x7100459bd8

// 0x710020ca04; original file: random tables, 0x710020ca04
struct RandomRows {
    int pick(int row);

    int rows[1][5];
};

int RandomRows::pick(int row) {
    return rows[row][random_below(5)];
}

void reset_light_pair_base(void* pair);                                     // 0x71001e5518

// 0x71001eb3e4; original file: light pairs, 0x71001eb3e4
struct LightPair {
    void release();

    void* first;              // +00
    void* second;             // +08
    void* value10;            // +10
};

void LightPair::release() {
    release_light(&first);
    release_light(&second);
    second = nullptr;
    value10 = nullptr;
    first = nullptr;
    reset_light_pair_base(this);
}

// 0x71000d0930; original file: tables, 0x71000d0930
struct SubInit {
    void init();                                                            // 0x7100031378
    unsigned char pad[0x10];
};

struct BigCleared {
    void reset();

    unsigned char pad[0x30];
    SubInit sub;              // +30
    ByteBlock<0xecb0> bytes;  // +40
};

void BigCleared::reset() {
    bytes = {};
    sub.init();
}

// A hidden flag byte (0x7100c2ee14), read directly.
extern bool gBattleTimerFlag __attribute__((visibility("hidden")));

struct BattleSetupMode {
    unsigned char value0[4];
    unsigned char mode4;      // +04
};

// 0x710006fdb8; original file: battle timers, 0x710006fdb8
int battle_timer_seconds() {
    unsigned char mode = reinterpret_cast<BattleSetupMode*>(get_battle_setup())->mode4;
    bool open = !(mode & 4);
    return gBattleTimerFlag && open ? 0x14 : 0;
}

// 0x71005340ec; original file: entry lists, 0x71005340ec
struct EntryCopy {
    unsigned int copy_to(void* out);

    unsigned char pad[0x30];
    unsigned int count;       // +30
    unsigned char entries[1]; // +34
};

unsigned int EntryCopy::copy_to(void* out) {
    memcpy(out, entries, static_cast<unsigned long>(count) * 8);
    return count;
}
void* load_global_44bc20();                                                 // 0x710044bc20
void global_call_44c360(void* global, void* value);                         // 0x710044c360

// 0x71004543dc; original file: global queries, 0x71004543dc
void guarded_forward_44c360(void* value) {
    if (load_global_44bc20())
        global_call_44c360(load_global_44bc20(), value);
}

struct UnitInfoRecord {
    unsigned char pad[0x1eb];
    signed char level;        // +1eb
};
struct UnitEntry {
    unsigned char pad[0x110];
    UnitInfoRecord* info;     // +110
};
UnitEntry* find_unit_446054(Global4449ec* global, int id);                  // 0x7100446054

// 0x7100452a24; original file: global queries, 0x7100452a24
bool unit_has_level(int id) {
    return find_unit_446054(load_global_4449ec(), id)->info->level > 0;
}

// 0x7100434384; original file: tables, 0x7100434364-0x7100434384
struct OwnedTable {
    void init(void* owner);

    void* owner;              // +00
    unsigned char bytes[0x88]; // +08
    unsigned char pad90[8];
    int count;                // +98
};

void OwnedTable::init(void* owner) {
    count = 0;
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
    this->owner = owner;
}

// 0x71003e7114; original file: record copies, 0x71003e7114
struct LargeRecord {
    void copy_to(LargeRecord* out);

    unsigned char pad[0x10];
    unsigned char data[0x150]; // +10
    int value160;             // +160
};

void LargeRecord::copy_to(LargeRecord* out) {
    memcpy(out->data, data, sizeof(data));
    out->value160 = value160;
}

// 0x71003dd0e4; original file: tables, 0x71003dd0e4
struct SplitTable {
    void clear();

    ByteBlock<0x110> head;    // +000
    unsigned char pad110[0x70];
    ByteBlock<0x300> tail;    // +180
};

void SplitTable::clear() {
    head = {};
    tail = {};
}

struct SubRelease {
    void release();                                                         // 0x71003af6ec
};

// 0x71003aa540; original file: scene objects, 0x71003aa540
struct LightOwner {
    void release();

    unsigned char pad[0x298];
    void* light;              // +298
    SubRelease sub;           // +2a0
};

void LightOwner::release() {
    if (light) {
        release_light(&light);
        light = nullptr;
    }
    sub.release();
}

// 0x71003a4754; original file: panel drawing, 0x71003a4754
struct WidePanel {
    void draw();

    unsigned char pad[0x2320];
    LightEffectNode* node;    // +2320
    unsigned char pad2328[0x38];
    PanelPane* pane;          // +2360
    unsigned char pad2368[0x18];
    unsigned char lines[1];   // +2380
};

void WidePanel::draw() {
    set_pane_lines(pane, reinterpret_cast<TrackLightTarget*>(lines), 0x20);
    node->draw(0);
}
// 0x7100214c00; original file: weapon table, 0x7100214c00
struct WeaponSlots {
    void reset();

    unsigned char head[6];    // +00
    short slots[5];           // +06
    unsigned char rest[0x78]; // +10
};

void WeaponSlots::reset() {
    unsigned char* bytes = head;
    for (unsigned int i = 0; i < 0x88; ++i)
        bytes[i] = 0;
    slots[4] = -1;
    slots[0] = -1;
    slots[1] = -1;
    slots[2] = -1;
    slots[3] = -1;
}

struct Singleton232a8 {
    unsigned char pad[0x2d0];
    unsigned char normal[0xf18]; // +2d0
    unsigned char special[1];    // +11e8
};
// Reached through the GOT slot at 0x7100c232a8.
extern Singleton232a8* gSingleton_c232a8;

// 0x710020ac40; original file: game data tables, 0x710020ac40
void* current_unit_table() {
    BattleSetupMode* setup = reinterpret_cast<BattleSetupMode*>(get_battle_setup());
    Singleton232a8* tables = gSingleton_c232a8;
    return !(setup->mode4 & 4) ? tables->normal : tables->special;
}

// 0x7100209d34; original file: game data tables, 0x7100209d34
struct MixedTable {
    void reset();

    unsigned char values[0x4fb]; // +000
    unsigned char pad4fb;
    unsigned char slots[0x3fc];  // +4fc
};

void MixedTable::reset() {
    for (unsigned int i = 0; i < sizeof(values); ++i)
        values[i] = 0;
    for (unsigned int i = 0; i < sizeof(slots); ++i)
        slots[i] = 0xff;
}

// Reached through the GOT slot at 0x7100c23180.
extern void* gStageLayout2;

// 0x71001f31e4; original file: stage layout, 0x71001f31e4
void load_stage_layout2() {
    int stage = get_shared_state()->stage;
    gStageLayout2 = load_layout(stage == 6 ? 0x2d : stage + 0x2c);
}

class DataChunkSet {
public:
    void set(const void* data);                                             // 0x7100218c34
    unsigned char pad[0x10];
};

// 0x71001a5e18; original file: light presets, 0x71001a5e18
struct ChunkPairAt {
    void assign(const void* first, const void* second);

    unsigned char pad[0x19b0];
    DataChunkSet a;           // +19b0
    DataChunkSet b;           // +19c0
};

void ChunkPairAt::assign(const void* first, const void* second) {
    a.set(first);
    b.set(second);
}

// 0x7100193bec; original file: light records, 0x7100193bec
struct MirroredTables {
    void save();

    unsigned char pad[0x94];
    unsigned char current[2][0x100]; // +94
    unsigned char saved[2][0x100];   // +294
};

void MirroredTables::save() {
    memcpy(saved[0], current[0], 0x100);
    memcpy(saved[1], current[1], 0x100);
}

// 0x710006cce4; original file: entry lists, 0x710006cce4
struct EntryArray {
    void clear();

    int value0;               // +00
    unsigned int count;       // +04
    void* entries;            // +08
};

void EntryArray::clear() {
    if (count)
        memset(entries, 0, static_cast<unsigned long>(count) * 8);
    count = 0;
}
// 0x71001f31ac, 0x71001f3174; original file: stage layout, 0x71001f3174-0x71001f31e4
void load_stage_layout3() {
    int stage = get_shared_state()->stage;
    gStageLayout2 = load_layout(stage == 6 ? 0x39 : stage + 0x38);
}

void load_stage_layout4() {
    int stage = get_shared_state()->stage;
    gStageLayout2 = load_layout(stage == 6 ? 0x2d : stage + 0x2c);
}

unsigned char global_call_456e40(void* global, void* value);                // 0x7100456e40

// 0x7100452af8; original file: global queries, 0x7100452af8
unsigned char guarded_query_456e40(void* value) {
    if (load_global_455ebc())
        return global_call_456e40(load_global_455ebc(), value);
    return 1;
}
struct Defaults48 {
    unsigned char bytes[0x30];
};
// Default values (0x710080c220), addressed directly.
extern const Defaults48 kDefaults48 __attribute__((visibility("hidden")));

// 0x71003dcae8; original file: tables, 0x71003dcae8
struct DefaultPair {
    void reset();

    Defaults48 first;         // +00
    Defaults48 second;        // +30
};

void DefaultPair::reset() {
    memcpy(&first, &kDefaults48, sizeof(Defaults48));
    memcpy(&second, &kDefaults48, sizeof(Defaults48));
}

void resources_call_3882e8(SharedResources* resources, float value, int flag); // 0x71003882e8

// 0x71003c7200; original file: shared-state resource queries, 0x71003c7200
void resources_set_value(float value) {
    if (SharedResources* resources = shared_state_resources(get_shared_state()))
        resources_call_3882e8(resources, value, 1);
}

struct HeldLight {
    void* light;              // +00
};
// Reached through the GOT slots at 0x7100c2ada0 and 0x7100c2af58.
extern HeldLight* gGlobal_c2ada0;
extern HeldLight* gGlobal_c2af58;

// 0x710037adb8; original file: held lights, 0x710037adb8
void release_held_light_c2ada0() {
    if (HeldLight* held = gGlobal_c2ada0) {
        if (held->light) {
            release_light(&held->light);
            held->light = nullptr;
        }
    }
}

// 0x7100379ab4; original file: held lights, 0x7100379ab4
void release_held_light_c2af58() {
    if (HeldLight* held = gGlobal_c2af58) {
        if (held->light) {
            release_light(&held->light);
            held->light = nullptr;
        }
    }
}
unsigned char resource_queue_cancelled();                                   // 0x71002589c0
unsigned char shared_state_exiting(SharedState* state);                     // 0x71002ac7f0

// 0x7100300140; original file: scene tasks, 0x7100300140
struct PendingRequest {
    void clear_unless_stopping();

    void* owner;              // +00
    void* request;            // +08
};

void PendingRequest::clear_unless_stopping() {
    if (!resource_queue_cancelled() && !shared_state_exiting(get_shared_state()))
        request = nullptr;
}

unsigned char resource_queue_has_callback(void* request);                   // 0x7100259680
// Resource requests by type (0x7100bd3668), addressed directly.
extern void* const kTypeRequests[] __attribute__((visibility("hidden")));

// 0x71002d8d98; original file: scene tasks, 0x71002d8d98
struct RequestWaiter {
    bool ready();

    unsigned char type;       // +000
    unsigned char pad[0x1c1];
    unsigned char busy;       // +1c2
};

bool RequestWaiter::ready() {
    if (busy)
        return false;
    return !resource_queue_has_callback(kTypeRequests[type]);
}

// 0x710011f1a4; original file: battle timers, 0x710011f1a4
struct TimerStart {
    void start(int value);

    unsigned char pad[0x48];
    unsigned char active;     // +48
    unsigned char pad49[3];
    int seconds;              // +4c
    int value;                // +50
};

void TimerStart::start(int value) {
    if (!(get_battle_setup()->flags & 2)) {
        active = 1;
        seconds = 0x10;
        this->value = value;
    }
}

// 0x710004a660; original file: tables, 0x710004a660
struct MixedRecord {
    void reset();

    unsigned char head[0x2c]; // +00 (cleared with the first 0x41 bytes)
    int limit;                // +2c
    unsigned char pad30[0x18];
    long value48;             // +48
    long value50;             // +50
    long value58;             // +58
    long value60;             // +60
    long value68;             // +68
    long value70;             // +70
};

void MixedRecord::reset() {
    unsigned char* bytes = head;
    for (unsigned int i = 0; i < 0x41; ++i)
        bytes[i] = 0;
    value68 = 0;
    value70 = 0;
    value58 = 0;
    value60 = 0;
    limit = 0x28;
    value48 = 0;
    value50 = 0;
}
void* load_global_40d628();                                                 // 0x710040d628
void global_call_40d754(void* global, void* a, int b);                      // 0x710040d754

// 0x7100454314; original file: global queries, 0x7100454314
void guarded_forward_40d754(void* a, int b) {
    if (load_global_40d628())
        global_call_40d754(load_global_40d628(), a, b);
}

void part_call3_4348a4(void* part, int a, void* b, void* c);                // 0x71004348a4
void part_call3_41fdd8(void* part, void* a, void* b, int c);                // 0x710041fdd8
void part_call3_41d100(void* part, int a, int b, int c);                    // 0x710041d100

// 0x7100454028; original file: global queries, 0x71004540b4-0x7100453d48 (nearby)
void global_part28_4348a4(int a, void* b, void* c) {
    part_call3_4348a4(load_global_425dd0()->part28, a, b, c);
}

// 0x7100453d08
void global_part20_41fdd8(void* a, void* b, int c) {
    part_call3_41fdd8(load_global_425dd0()->part20, a, b, c);
}

// 0x71004528fc
void global_part10_41d100(int a, int b, int c) {
    part_call3_41d100(load_global_425dd0()->part10, a, b, c);
}
// Reached through the GOT slot at 0x7100c2a9c8.
extern HeldLight* gGlobal_c2a9c8;

// 0x710037ac7c; original file: held lights, 0x710037ac7c
void release_held_light_c2a9c8() {
    if (HeldLight* held = gGlobal_c2a9c8) {
        if (held->light) {
            release_light(&held->light);
            held->light = nullptr;
        }
    }
}

// 0x71003de474; original file: tables, 0x71003de474
struct TimedTable {
    void reset();

    union {
        ByteBlock<0xc0> all;  // the whole object, cleared first
        struct {
            unsigned char bytes[0xa8]; // +00
            int valuea8;              // +a8
            unsigned char padac[8];
            int id;                   // +b4
            float duration;           // +b8
            int valuebc;              // +bc
        };
    };
};

void TimedTable::reset() {
    all = {};
    id = -1;
    duration = 5000.0f;
    valuea8 = 0;
    valuebc = 0;
}
// 0x71002015c4; original file: game data tables, 0x71002015c4
struct FlagTable {
    void reset();

    unsigned char slots[0x1680]; // +0000
    unsigned char values[0xf0];  // +1680
};

void FlagTable::reset() {
    for (unsigned int i = 0; i < sizeof(values); ++i)
        values[i] = 0;
    for (unsigned int i = 0; i < sizeof(slots); ++i)
        slots[i] = 0xff;
}
// 0x71001f33c8; original file: stage layout, 0x71001f33c8
void reload_stage_light(void** slot) {
    release_light(slot);
    int stage = get_shared_state()->stage;
    *slot = load_layout(stage == 6 ? 0xb : stage + 0xa);
}

// 0x71001ef284; original file: layout elements, 0x71001ef284
struct DelayedNode {
    void show();

    int count;                // +00
    unsigned char pad4[4];
    unsigned char shown;      // +08
    unsigned char enabled;    // +09
    unsigned char padA[0x116];
    LightEffectNode* node;    // +120
};

void DelayedNode::show() {
    if (count && enabled) {
        node->draw(0);
        shown = 1;
    }
}

class DefaultHeapRelease {
public:
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeapRelease* get_default_heap_release();                             // 0x710045c96c

// 0x710006cca4; original file: buffers, 0x710006cca4
struct OwnedBuffer {
    void reset();

    void* value0;             // +00
    void* buffer;             // +08
};

void OwnedBuffer::reset() {
    if (void* data = buffer) {
        get_default_heap_release()->release(data, 1, 0);
        buffer = nullptr;
    }
    value0 = nullptr;
}

// 0x710003cea8; original file: buffers, 0x710003cea8
struct SizedBuffer {
    void reset();

    void* buffer;             // +00
    long size;                // +08
    long used;                // +10
};

void SizedBuffer::reset() {
    if (void* data = buffer) {
        get_default_heap_release()->release(data, 1, 0);
        buffer = nullptr;
    }
    size = 0;
    used = 0;
}

unsigned char forward_flag_6eb7c();                                         // 0x710006eb7c
// Reached through the GOT slot at 0x7100c2ec00.
extern int gGlobalMode_c2ec00;

// 0x710003e22c; original file: global queries, 0x710003e22c
bool global_mode_basic() {
    if (forward_flag_6eb7c())
        return gGlobalMode_c2ec00 == 0 || gGlobalMode_c2ec00 == 1;
    return false;
}
void global_call_44bf70(void* global, void* a, void* b, int c, float d);    // 0x710044bf70

// 0x7100454398, 0x7100454354; original file: global queries, 0x7100454354-0x7100454398
void guarded_play_44bf70(void* value) {
    if (load_global_44bc20())
        global_call_44bf70(load_global_44bc20(), value, nullptr, 1, 1.0f);
}

void guarded_play_44bf70_copy(void* value) {
    if (load_global_44bc20())
        global_call_44bf70(load_global_44bc20(), value, nullptr, 1, 1.0f);
}
void notify_light_restarted(int id);                                        // 0x71003fe230

// 0x7100251ccc; original file: pending lights, 0x7100251c8c-0x7100251ccc
void restart_pending_lights() {
    for (int i = 0; i < 20; ++i) {
        if (gPendingLights[i] != -1)
            notify_light_restarted(gPendingLights[i]);
    }
}
ProfileStats* profile_stats();                                              // 0x710020b970 (no argument)

struct ProfileShorts {
    unsigned char pad[0x180];
    short skills[0x40];       // +180
    unsigned char pad200[0x3fa];
    short items[0xff];        // +5fa
};

// 0x710020b8b0; original file: profile statistics, 0x710020b8b0
int Profile::skill_value(int index) {
    if (static_cast<unsigned int>(index) <= 0x3f)
        return profile_stats()->value(reinterpret_cast<ProfileShorts*>(this)->skills[index]);
    return -1;
}

// 0x710020b1cc; original file: profile statistics, 0x710020b1cc
int Profile::item_value(unsigned int index) {
    if (index <= 0xfe)
        return profile_stats()->value(reinterpret_cast<ProfileShorts*>(this)->items[index]);
    return -1;
}

int unit_level_20b210(void* table, int kind);                                // 0x710020b210
void* load_global_20acb0();                                                 // 0x710020acb0

// 0x7100210dd0; original file: unit database tables, 0x7100210dd0
struct UnitLevelEntry {
    int level();

    unsigned char pad[0x36];
    signed char kind;         // +36
    unsigned char pad37[3];
    short fixed_level;        // +3a
    unsigned char pad3c[2];
    unsigned char flags;      // +3e
};

int UnitLevelEntry::level() {
    if (flags & 4)
        return 0;
    int value = fixed_level;
    if (value >= 0)
        return value;
    return unit_level_20b210(load_global_20acb0(), kind);
}

// 0x71001cc94c; original file: buffers, 0x71001cc94c
struct OptionalBuffer {
    void release();

    unsigned char pad[0x790];
    void* buffer;             // +790
    unsigned char pad798[0xc];
    unsigned char owned;      // +7a4
};

void OptionalBuffer::release() {
    if (owned) {
        if (void* data = buffer) {
            get_default_heap_release()->release(data, 1, 0);
            buffer = nullptr;
        }
    }
}

struct Plain8 {
    Plain8() {}
    long value;
};

// 0x71001c8690; original file: battle objects, 0x71001c8690
Plain8* shared_plain8() {
    static Plain8 instance;
    return &instance;
}
class DefaultHeapAlloc {
public:
    void* allocate(unsigned long alignment, unsigned long size, unsigned char lock,
                   unsigned char keep);                                     // 0x710045c458
};
DefaultHeapAlloc* get_default_heap_alloc();                                 // 0x710045c96c
// Reached through the GOT slots at 0x7100c22cd8 and 0x7100c22cb8.
extern void* gSingleton_c22cd8;
extern void* gSingleton_c22cb8;

// 0x7100164a0c; original file: battle objects, 0x7100164a0c
void create_singleton_c22cd8() {
    if (!gSingleton_c22cd8)
        gSingleton_c22cd8 = get_default_heap_alloc()->allocate(0x10, 0x18c, 1, 0);
}

// 0x71001469b8; original file: battle objects, 0x71001469b8
void create_singleton_c22cb8() {
    if (!gSingleton_c22cb8)
        gSingleton_c22cb8 = get_default_heap_alloc()->allocate(0x10, 0x30, 1, 0);
}