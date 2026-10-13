// Small helpers picked by tools/rank_targets.py whose callees are all named: battle-setup flag
// wrappers and fixed-size clears. They come from several game source files; each definition
// names the address region of the original file it likely belongs to, for a later split.
// Names are descriptive placeholders. Status: matching/README.md.

extern "C" void* memset(void* dest, int value, unsigned long size);

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
    unsigned char pad[0x2ad4];
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