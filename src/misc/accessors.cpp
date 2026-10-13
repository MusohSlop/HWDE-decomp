// Small accessors and global getters picked by tools/rank_targets.py. They come from several
// game source files; they are grouped here because each is self-contained. Each definition
// names the address region of the original file it likely belongs to, for a later split.
// Names are descriptive placeholders. Status: matching/README.md.

namespace nn {
struct TimeSpan {
    long nanoseconds;
};
namespace os {
void SleepThread(TimeSpan time);
}
}  // namespace nn

// 0x7100459d10
// 0x7100459d10; original file: worker/system helpers, 0x7100459xxx
void sleep_worker_retry() {
    nn::TimeSpan wait = {10000};
    nn::os::SleepThread(wait);
}

class HeapAllocatorSlot {
public:
    void* get();                                                            // 0x710045c2ec

    unsigned char pad[0x10];
    unsigned char allocator[8]; // +10
};

// 0x710045c2ec; original file: default heap, 0x710045c1dc-0x710045c96c
void* HeapAllocatorSlot::get() {
    return allocator;
}

struct DlcCatalog;
class DlcStore {
public:
    DlcCatalog* catalog();                                                  // 0x7100291740
    void close();                                                           // 0x710029174c

    unsigned char pad[0x1010];
    unsigned char catalog1010[0x480]; // +1010
    void* session;            // +1490
};
// Reached through the GOT slot at 0x7100c2a880.
extern DlcStore gDlcStore;

// 0x7100291734; original file: DLC store, 0x7100291734-0x710029174c
DlcStore* get_dlc_store() {
    return &gDlcStore;
}

// 0x7100291740; original file: DLC store, 0x7100291734-0x710029174c
DlcCatalog* DlcStore::catalog() {
    return reinterpret_cast<DlcCatalog*>(catalog1010);
}

// 0x710029174c; original file: DLC store, 0x7100291734-0x710029174c
void DlcStore::close() {
    session = nullptr;
}

class Unlocks {
public:
    unsigned char has(int content);                                         // 0x7100224990
};

// 0x7100224990; original file: unlocks, 0x71002248a0-0x7100224990
unsigned char Unlocks::has(int) {
    return 1;
}

class BgmTrack {
public:
    unsigned short length();                                                // 0x710020d954

    unsigned char pad[0x3c];
    unsigned short frames;    // +3c
};

// 0x710020d954; original file: unit/BGM data, 0x710020d9xx
unsigned short BgmTrack::length() {
    return frames;
}

struct RegionSettings {
    unsigned char pad[0x27b];
    signed char pending;      // +27b
    signed char locked;       // +27c
    unsigned char pad27d[3];
    signed char kind;         // +280
};

// 0x710020c22c; original file: region/option settings, 0x710020bd74-0x710020c22c
int region_kind(RegionSettings* settings) {
    return settings->kind;
}

class OptionSource {
public:
    int pending();                                                          // 0x710020c1fc
    int locked();                                                           // 0x710020c204
};

// 0x710020c1fc; original file: region/option settings, 0x710020bd74-0x710020c22c
int OptionSource::pending() {
    return reinterpret_cast<RegionSettings*>(this)->pending;
}

// 0x710020c204; original file: region/option settings, 0x710020bd74-0x710020c22c
int OptionSource::locked() {
    return reinterpret_cast<RegionSettings*>(this)->locked;
}

class WeaponTable;
class UnitDatabase;
class BgmPlayer;
class ProfileStats;
// Reached through the GOT slots at 0x7100c23388, 0x7100c232e8, 0x7100c232f0, 0x7100c232d8 and
// 0x7100c232d0.
extern WeaponTable* gWeaponTable;
extern UnitDatabase* gUnitDatabase;
extern BgmPlayer* gBgmPlayer;
extern OptionSource* gOptionSource;
extern ProfileStats* gProfileStats;

// 0x7100215b84; original file: weapon table, 0x7100215b84-0x7100215d34
WeaponTable* get_weapon_table() {
    return gWeaponTable;
}

// 0x710020ec80; original file: unit database, 0x710020ec80-0x710020eeb8
UnitDatabase* get_unit_database() {
    return gUnitDatabase;
}

// 0x710020dfd0; original file: unit/BGM data, 0x710020dfd0
BgmPlayer* bgm_player() {
    return gBgmPlayer;
}

// 0x710020bd74; original file: region/option settings, 0x710020bd74-0x710020c22c
OptionSource* get_option_source() {
    return gOptionSource;
}

class Profile {
public:
    ProfileStats* stats();                                                  // 0x710020b970
};

// 0x710020b970; original file: profile statistics, 0x710020b970-0x710020ba78
ProfileStats* Profile::stats() {
    return gProfileStats;
}

struct WeaponRecord {
    unsigned char data[0x14];
};

class WeaponTable {
public:
    WeaponRecord* find(int weapon);                                         // 0x7100215d34

    WeaponRecord records[0x12c];
};

// 0x7100215d34; original file: weapon table, 0x7100215b84-0x7100215d34
WeaponRecord* WeaponTable::find(int weapon) {
    return static_cast<unsigned int>(weapon) < 0x12c ? &records[weapon] : nullptr;
}

class ProfileStats {
public:
    int value(int id);                                                      // 0x710020ba78

    int values[0x2d0];
};

// 0x710020ba78; original file: profile statistics, 0x710020b970-0x710020ba78
int ProfileStats::value(int id) {
    if (static_cast<unsigned int>(id) <= 0x2cf) {
        int value = values[id];
        return value >= 0 ? value : -1;
    }
    return -1;
}

class TextTable {
public:
    const char* find(int id, int a);                                        // 0x7100218d18
    unsigned char pad[0x20];
};

struct TextDatabase {
    unsigned char loaded;     // +00
    unsigned char pad1[0x57];
    TextTable system;         // +58
    TextTable messages;       // +78
};
// Reached through the GOT slot at 0x7100c233a0.
extern TextDatabase gTextDatabase;
extern const char kEmptyText[] __attribute__((visibility("hidden")));       // 0x7100740512

// 0x7100217cf4; original file: text database, 0x7100217cf4-0x7100217d64
const char* system_text(int id) {
    if (static_cast<unsigned int>(id) <= 0x4f && gTextDatabase.loaded)
        return gTextDatabase.system.find(id, 0);
    return kEmptyText;
}

// 0x7100217d64; original file: text database, 0x7100217cf4-0x7100217d64
const char* message_text(int id) {
    if (static_cast<unsigned int>(id) <= 0x83d && gTextDatabase.loaded)
        return gTextDatabase.messages.find(id, 0);
    return kEmptyText;
}

class GameState {
public:
    int base_level(int kind);                                               // 0x7100203550

    unsigned char pad[0x1bb7c];
    unsigned int mode;        // +1bb7c
    short levels[4];          // +1bb80
};

class Game {
public:
    GameState* state();                                                     // 0x7100204c10
    void set_dlc_seen(unsigned char seen);                                  // 0x7100203d00
    unsigned char unlocked(int id);                                         // 0x7100204518

    unsigned char pad0[4];
    unsigned int flags[4];    // +0004
    unsigned char pad14[0x197f];
    unsigned char dlc_seen;   // +1993
    unsigned char pad1994[0xbd4];
    unsigned int unlocks[0xa4]; // +2568
    unsigned char state27f8[8]; // +27f8
};
// Reached through the GOT slot at 0x7100c23258.
extern Game* gGame;

// 0x7100204728; original file: game object, 0x71002026fc-0x7100204c10
Game* get_game() {
    return gGame;
}

// 0x7100204c10; original file: game object, 0x71002026fc-0x7100204c10
GameState* Game::state() {
    return reinterpret_cast<GameState*>(state27f8);
}

// 0x7100203d00; original file: game object, 0x71002026fc-0x7100204c10
void Game::set_dlc_seen(unsigned char seen) {
    dlc_seen = seen;
}

struct ItemEntry {
    int state;                // +0: 2 special, 3 owned
    short weapon;             // +4
    unsigned char pad6[2];
};

class ItemTable {
public:
    unsigned char contains(int item);                                       // 0x71001ff2c8
    int weapon_of(int item);                                                // 0x71001ff1c4
    unsigned char is_special(int item);                                     // 0x71001ff2a4

    ItemEntry entries[0x2e4];
};
// Reached through the GOT slot at 0x7100c23228.
extern ItemTable* gItemTable;

// 0x71001ff050; original file: item table, 0x71001ff050-0x71001ff2c8
ItemTable* get_item_table() {
    return gItemTable;
}

// 0x71001ff1c4; original file: item table, 0x71001ff050-0x71001ff2c8
int ItemTable::weapon_of(int item) {
    int weapon = entries[item].weapon;
    return static_cast<unsigned int>(weapon) < 0x12c && static_cast<unsigned int>(item) < 0x2e4 ? weapon : -1;
}

// 0x71001ff2a4; original file: item table, 0x71001ff050-0x71001ff2c8
unsigned char ItemTable::is_special(int item) {
    if (static_cast<unsigned int>(item) <= 0x2e3)
        return entries[item].state == 2;
    return 0;
}

// 0x71001ff2c8; original file: item table, 0x71001ff050-0x71001ff2c8
unsigned char ItemTable::contains(int item) {
    if (static_cast<unsigned int>(item) <= 0x2e3)
        return entries[item].state == 3;
    return 0;
}

class DataStream {
public:
    void read(unsigned char* value);                                        // 0x71001fbc54
    void read(unsigned short* value);                                       // 0x71001fbc84
    void write(unsigned char value);                                        // 0x71001fbdd8
    void write(unsigned short value);                                       // 0x71001fbe00

    unsigned char pad[0x10];
    unsigned char* cursor;    // +10
};

// 0x71001fbc54; original file: data stream, 0x71001fbbb0-0x71001fbe00
void DataStream::read(unsigned char* value) {
    *value = *cursor++;
}

// 0x71001fbc84; original file: data stream, 0x71001fbbb0-0x71001fbe00
void DataStream::read(unsigned short* value) {
    reinterpret_cast<unsigned char*>(value)[0] = *cursor++;
    reinterpret_cast<unsigned char*>(value)[1] = *cursor++;
}

// 0x71001fbdd8; original file: data stream, 0x71001fbbb0-0x71001fbe00
void DataStream::write(unsigned char value) {
    *cursor++ = value;
}

// 0x71001fbe00; original file: data stream, 0x71001fbbb0-0x71001fbe00
void DataStream::write(unsigned short value) {
    *cursor++ = value;
    *cursor++ = value >> 8;
}

// 0x7100203550; original file: game object, 0x71002026fc-0x7100204c10
int GameState::base_level(int kind) {
    if (static_cast<unsigned int>(kind) <= 3) {
        int level = levels[kind];
        return static_cast<unsigned short>(level) < 100 ? level : -1;
    }
    return -1;
}

// 0x7100204518; original file: game object, 0x71002026fc-0x7100204c10
unsigned char Game::unlocked(int id) {
    return (unlocks[id / 32] & static_cast<unsigned int>(1ul << (id % 32))) != 0;
}

// 0x71002026fc; original file: game object, 0x71002026fc-0x7100204c10
unsigned char game_has_flag(Game* game, int flag) {
    if (static_cast<unsigned int>(flag) <= 0x7f)
        return (game->flags[flag / 32] & static_cast<unsigned int>(1ul << (flag % 32))) != 0;
    return 0;
}

class Progress {
public:
    unsigned char has(int content);                                         // 0x7100203180

    unsigned char pad[0x140];
    unsigned int contents[1]; // +140
};

// 0x7100203180; original file: game object, 0x71002026fc-0x7100204c10
unsigned char Progress::has(int content) {
    if (static_cast<unsigned int>(content) <= 9)
        return (contents[content / 32] & static_cast<unsigned int>(1ul << (content % 32))) != 0;
    return 0;
}

struct TrackVec2 {
    float x;
    float y;
};

class AdvBoard {
public:
    TrackVec2 start_position(int cell);                                     // 0x710029f8ec
    TrackVec2 environment_position(unsigned int cell);                      // 0x710029fd90
};

// 0x710029f8ec; original file: Adventure board, 0x710029xxxx
TrackVec2 AdvBoard::start_position(int cell) {
    float x = static_cast<float>(cell % 16) * 96.0f;
    float y = static_cast<float>(cell / 16) * -66.0f;
    TrackVec2 position;
    position.x = x + -768.0f;
    position.y = y + 186.0f;
    return position;
}

// 0x710029fd90; original file: Adventure board, 0x710029xxxx
TrackVec2 AdvBoard::environment_position(unsigned int cell) {
    float x = static_cast<float>(cell % 3) * 160.0f;
    float y = static_cast<float>(cell / 3) * -110.0f;
    TrackVec2 position;
    position.x = x + -325.0f;
    position.y = y + 75.0f;
    return position;
}

struct SharedState {
    unsigned char exiting;    // +000
    unsigned char pad1[0x21f];
    void* resources;          // +220
};

// 0x71002ac7f0; original file: shared state, 0x71002aae3c-0x71002ad584
unsigned char shared_state_exiting(SharedState* state) {
    return state->exiting;
}

// 0x71002aca94; original file: shared state, 0x71002aae3c-0x71002ad584
bool shared_state_stopping(SharedState* state) {
    return state->exiting != 0;
}

// 0x71002ad1dc; original file: shared state, 0x71002aae3c-0x71002ad584
void* shared_state_resources(SharedState* state) {
    return state->resources;
}
