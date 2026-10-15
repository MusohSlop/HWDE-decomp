// A trophy view's open (fourth session, 2-copy family 317754): closing plays the layout's close animation; opening
// picks a random side, finds its unit's material id and shows that trophy (the tail call is the one difference:
// 0x7100317844 or 0x7100318a3c). TrophyView::open<0> (0x7100317754) and open<1> (0x710031894c).

class RandomSource {
public:
    int roll();                                                             // 0x71003336c4
};
// Reached through the GOT slot at 0x7100c22c00.
extern RandomSource gRandomSource;

struct SideOwner {
    unsigned char pad0[0x10];
    void* unit;               // +10
};
struct SideSlot {
    unsigned char pad0[8];
    SideOwner* owner;         // +08
};
struct SideTable {
    unsigned char pad0[0xb08];
    SideSlot* sides[2];       // +b08
};
// Reached through the GOT slot at 0x7100c21698.
extern SideTable* gSideTable;

int unit_material_200acc(void* unit);                                       // 0x7100200acc

class MaterialId {
public:
    unsigned int id();                                                      // 0x71002005f4
};
struct MaterialEntry {
    unsigned char pad0[0x28];
    MaterialId ident;         // +28
};
class MaterialBook {
public:
    MaterialEntry* entry(int id);                                           // 0x71002015a8
};
MaterialBook* get_material_book();                                          // 0x7100200fc0

struct TrophyRecord;
class Game {
public:
    TrophyRecord* trophy(unsigned int id);                                  // 0x71002042bc
};
Game* get_game();                                                           // 0x7100204728

void stop_voice_3feccc();                                                   // 0x71003feccc
void play_layout_1f7a0c(void* layout, int a, int b, float rate);            // 0x71001f7a0c

class TrophyView {
public:
    template <int Copy> void open(unsigned char on);
    void set_mode_316b2c(int mode);                                         // 0x7100316b2c
    void show_317844(TrophyRecord* record);                                 // 0x7100317844
    void show_318a3c(TrophyRecord* record);                                 // 0x7100318a3c

    template <int Copy> void show(TrophyRecord* record) {
        if (Copy == 0)
            show_317844(record);
        else
            show_318a3c(record);
    }

    unsigned char pad0[0x48];
    unsigned char layout[8];  // +48
};

template <int Copy>
void TrophyView::open(unsigned char on) {
    if (!on) {
        stop_voice_3feccc();
        play_layout_1f7a0c(layout, 3, 2, 1.0f);
        set_mode_316b2c(2);
        return;
    }
    int side = gRandomSource.roll();
    SideTable* table = gSideTable;
    if (side < 0) side = 0;
    SideSlot* slot = *(static_cast<unsigned int>(side) < 2 ? &table->sides[side] : &table->sides[0]);
    unsigned int id = 0xff;
    if (slot) {
        void* unit = slot->owner->unit;
        int material = unit ? unit_material_200acc(unit) : -1;
        MaterialEntry* e = get_material_book()->entry(material);
        if (e) id = e->ident.id();
    }
    TrophyRecord* record = get_game()->trophy(id);
    if (record) show<Copy>(record);
}

// 0x7100317754
template void TrophyView::open<0>(unsigned char);
// 0x710031894c
template void TrophyView::open<1>(unsigned char);
