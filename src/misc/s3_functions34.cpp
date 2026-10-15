// Template families released to the third session by the fourth: copies with identical code (call targets and
// constants aside), each written once as a template with a copy number and explicitly instantiated per copy.
// Names are descriptive placeholders. Status: matching/README.md.

// Two bytes and a halfword (0x71000b70c8, 0x71000b70e4): the halfword and the byte pair are stored apart (as two
// halfwords they would merge into one word).
struct State_b70c8 {
    short value;                 // +00
    unsigned char low;           // +02
    unsigned char high;          // +03
};

template <int Copy>
void reset_b70c8(State_b70c8* s) {
    s->value = 0;
    s->low = 0;
    s->high = 0xff;
}

template void reset_b70c8<0>(State_b70c8*);   // 0x71000b70c8
template void reset_b70c8<1>(State_b70c8*);   // 0x71000b70e4

class Game;
Game* fetch_204728();                                                       // 0x7100204728

// Options with a flag at bit 10 of their first word.
struct Options16ef34 {
    unsigned int : 10;
    unsigned int flag : 1;
    unsigned int : 21;
};
Options16ef34* options_16ef34();                                            // 0x710016ef34
int level_16f640(Options16ef34* options);                                   // 0x710016f640
void set_2038c0(Game* game, int flag, int level, int mode);                // 0x71002038c0
void set_2036b8(Game* game, int flag, int level, int mode);                // 0x71002036b8

// One function per target and mode; the flag is read before the level is fetched.
template <int Which, int Mode>
void apply_option() {
    Game* game = fetch_204728();
    int flag = options_16ef34()->flag;
    int level = level_16f640(options_16ef34());
    if (Which == 0)
        set_2038c0(game, flag, level, Mode);
    else
        set_2036b8(game, flag, level, Mode);
}

template void apply_option<0, 1>();     // 0x710017903c
template void apply_option<0, 0>();     // 0x7100179080
template void apply_option<1, 0>();     // 0x71001814e8
template void apply_option<1, 1>();     // 0x7100181704
template void apply_option<1, 2>();     // 0x71001818dc
template void apply_option<1, 3>();     // 0x7100181990
template void apply_option<0, 2>();     // 0x7100181b7c
template void apply_option<0, 3>();     // 0x7100181c14

class Listener84344 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void refresh();      // +18
};

class Holder84344 {
public:
    virtual ~Holder84344();

    unsigned char pad8[0x48];
    unsigned long : 26;
    unsigned long mark_a : 1;    // +50 bit 26
    unsigned long mark_b : 1;    // +50 bit 27
    unsigned long : 36;
    unsigned char pad58[0x148];
};

// Two copies of one class: the holder with its listener second (at +1a0).
template <int Copy>
class Marked84344 : public Holder84344, public Listener84344 {
public:
    void clear_marks();
};

template <int Copy>
void Marked84344<Copy>::clear_marks() {
    mark_a = 0;
    mark_b = 0;
    refresh();
}

template void Marked84344<0>::clear_marks();   // 0x7100084344
template void Marked84344<1>::clear_marks();   // 0x7100086ab0

// An entry of the 128-entry table (0x5a0 bytes).
struct Entry1485cc {
    template <int Copy> void update();     // <0> 0x7100193b1c, <1> 0x7100193b84
    unsigned char data[0x5a0];
};

struct Table1485cc {
    unsigned char pad[0x99dc0];
    Entry1485cc entries[0x80];  // +99dc0
};
// Reached through the GOT slot at 0x7100c216e8.
extern Table1485cc* gTable1485cc;

// The entry for an id (out-of-range ids use the first), updated.
template <int Copy>
void update_entry(int id) {
    Table1485cc* table = gTable1485cc;
    unsigned int index = static_cast<unsigned int>(id) < 0x80 ? id : 0;
    table->entries[index].update<Copy>();
}

template void update_entry<0>(int);   // 0x71001485cc
template void update_entry<1>(int);   // 0x7100148600

// A byte writer: its cursor at +10.
template <int Copy>
struct Writer1fbe50 {
    void put(unsigned char b) { *cursor++ = b; }
    void put_u32(unsigned int value);

    unsigned char pad0[0x10];
    unsigned char* cursor;       // +10
};

// A little-endian 32-bit value, a byte at a time.
template <int Copy>
void Writer1fbe50<Copy>::put_u32(unsigned int value) {
    put(value);
    put(value >> 8);
    put(value >> 16);
    put(value >> 24);
}

template void Writer1fbe50<0>::put_u32(unsigned int);   // 0x71001fbe50
template void Writer1fbe50<1>::put_u32(unsigned int);   // 0x71001fbea0

struct Resource1cc31c {
    int flags;                   // +00: bit 31 owned
};

class ResourceManager1cc31c {
public:
    void release(Resource1cc31c* res);     // 0x71001d7338
};
// Reached through the GOT slot at 0x7100c22ca8.
extern ResourceManager1cc31c* gResourceManager1cc31c;

// A resource reference: released when owned, then reset.
template <int Copy>
struct ResourceRef1cc31c {
    void reset();

    Resource1cc31c* res;         // +00
    int kind;                    // +08
    int value;                   // +0c
    int index;                   // +10
    int slot;                    // +14
    void* extra;                 // +18
};

template <int Copy>
void ResourceRef1cc31c<Copy>::reset() {
    if (res && res->flags < 0)
        gResourceManager1cc31c->release(res);
    kind = 2;
    value = 0;
    res = nullptr;
    index = 0;
    extra = nullptr;
    slot = -1;
}

template void ResourceRef1cc31c<0>::reset();   // 0x71001cc31c
template void ResourceRef1cc31c<1>::reset();   // 0x71001cc370

struct HeapBase379f30 {
    virtual ~HeapBase379f30();
    unsigned char pad8[0xa8];
};
struct Allocator379f30 {
    virtual void v00(); virtual void v08(); virtual void v10(); virtual void v18(); virtual void v20(); virtual void v28();
    virtual void v30(); virtual void v38(); virtual void v40(); virtual void v48(); virtual void v50(); virtual void v58();
    virtual void free(void* p);  // +60
};
// The default heap: its allocator interface second (at +b0).
struct DefaultHeap : HeapBase379f30, Allocator379f30 {
    void release(void* ptr, int a, int b);                                  // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

// A buffer with a 15-byte header: its data freed through the default heap, then the header cleared and marked.
template <int Copy>
struct Buffer379f30 {
    void release();

    int f0;                      // +00
    short f4;                    // +04
    unsigned char f6;            // +06
    unsigned char f7;            // +07
    int f8;                      // +08
    short fc;                    // +0c
    union {
        unsigned short state;    // +0e
        struct {
            unsigned char loaded;   // +0e
            unsigned char empty;    // +0f
        };
    };
    void* data;                  // +10
};

template <int Copy>
void Buffer379f30<Copy>::release() {
    if (loaded) {
        if (data) {
            get_default_heap()->free(data);
            data = nullptr;
        }
        f7 = 0;
        f8 = 0;
        fc = 0;
        loaded = 0;
        f0 = 0;
        f4 = 0;
        f6 = 0;
        f7 = 0;
        state = 0x100;
    }
}

template void Buffer379f30<0>::release();   // 0x7100379f30
template void Buffer379f30<1>::release();   // 0x7100379f84

void destroy_23a4bc(void* object);                                          // 0x710023a4bc
void destroy_2d4a60(void* object);                                          // 0x71002d4a60

// Reached through the GOT slots at 0x7100c21708 and 0x7100c22c08.
extern void* gInstance241954;
extern void* gInstance2d5f2c;

// A singleton's teardown: destroyed and returned to the default heap, then cleared.
template <int Copy>
void destroy_instance() {
    void*& instance = Copy == 0 ? gInstance241954 : gInstance2d5f2c;
    void* object = instance;
    if (object) {
        if (Copy == 0)
            destroy_23a4bc(object);
        else
            destroy_2d4a60(object);
        get_default_heap()->release(object, 1, 0);
    }
    instance = nullptr;
}

template void destroy_instance<0>();   // 0x7100241954
template void destroy_instance<1>();   // 0x71002d5f2c

extern "C" void* memset(void* dest, int value, unsigned long size);

// A record: two pointers, an id (-1 when free), and four links (-1 when unset).
struct Record215d48 {
    void* first;                 // +00
    void* second;                // +08
    short id;                    // +10
    short f12;                   // +12
    short f14;                   // +14
    short links[4];              // +16
    short f1e;                   // +1e
    void* third;                 // +20
};

template <int Copy>
void clear_record(Record215d48* record) {
    memset(record, 0, sizeof(*record));
    record->id = -1;
    for (int i = 0; i < 4; ++i)
        record->links[i] = -1;
}

template void clear_record<0>(Record215d48*);   // 0x7100215d48
template void clear_record<1>(Record215d48*);   // 0x7100215d68

// A variadic hook whose body was compiled out: it still spills every argument register.
template <int Copy>
int unused_hook(...) {
    return 0;
}

template int unused_hook<0>(...);   // 0x71001763e8
template int unused_hook<1>(...);   // 0x71003fec40

extern "C" float sqrtf(float value);

struct Point148570 {
    float x;                     // +00
    float y;                     // +04
    float z;                     // +08
};

// The ground-plane (x/z) distance between two points; the copies subtract in opposite orders.
template <int Copy>
float ground_distance(const Point148570* a, const Point148570* b) {
    const Point148570* from = Copy == 0 ? a : b;
    const Point148570* to = Copy == 0 ? b : a;
    float dx = to->x - from->x;
    float dz = to->z - from->z;
    return sqrtf(dx * dx + dz * dz);
}

template float ground_distance<0>(const Point148570*, const Point148570*);   // 0x7100148570
template float ground_distance<1>(const Point148570*, const Point148570*);   // 0x7100177814

class TextTable {
public:
    const char* find(int id, int a);                                        // 0x7100218d18
};

struct TextDatabase217d9c {
    unsigned char loaded;        // +00
    unsigned char pad1[0x87];
    TextTable names;             // +88
};
// Reached through the GOT slot at 0x7100c233a0.
extern TextDatabase217d9c gTextDatabase;
extern const char kEmptyText[] __attribute__((visibility("hidden")));       // 0x7100740512

// A name from the text database's table at +88 (empty when out of range or not loaded).
template <int Copy>
const char* name_text(int id) {
    if (static_cast<unsigned int>(id) <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.names.find(id, 0);
    return kEmptyText;
}

template const char* name_text<0>(int);   // 0x7100217d9c
template const char* name_text<1>(int);   // 0x7100218814

class CommandUnit2aec0 {
public:
    virtual void v000(); virtual void v008(); virtual void v010(); virtual void v018(); virtual void v020();
    virtual void v028(); virtual void v030(); virtual void v038(); virtual void v040(); virtual void v048();
    virtual void v050(); virtual void v058(); virtual void v060(); virtual void v068(); virtual void v070();
    virtual void v078(); virtual void v080(); virtual void v088(); virtual void v090(); virtual void v098();
    virtual void v0a0(); virtual void v0a8(); virtual void v0b0(); virtual void v0b8(); virtual void v0c0();
    virtual void v0c8(); virtual void v0d0(); virtual void v0d8(); virtual void v0e0(); virtual void v0e8();
    virtual void v0f0(); virtual void v0f8(); virtual void v100(); virtual void v108(); virtual void v110();
    virtual void v118(); virtual void v120(); virtual void v128(); virtual void v130(); virtual void v138();
    virtual void v140(); virtual void v148(); virtual void v150(); virtual void v158(); virtual void v160();
    virtual void v168(); virtual void v170(); virtual void v178(); virtual void v180(); virtual void v188();
    virtual void v190(); virtual void v198(); virtual void v1a0(); virtual void v1a8(); virtual void v1b0();
    virtual void v1b8(); virtual void v1c0(); virtual void v1c8(); virtual void v1d0(); virtual void v1d8();
    virtual void v1e0(); virtual void v1e8(); virtual void v1f0(); virtual void v1f8(); virtual void v200();
    virtual void v208(); virtual void v210(); virtual void v218(); virtual void v220(); virtual void v228();
    virtual void v230(); virtual void v238(); virtual void v240(); virtual void v248(); virtual void v250();
    virtual void v258(); virtual void v260(); virtual void v268(); virtual void v270(); virtual void v278();
    virtual void v280(); virtual void v288(); virtual void v290(); virtual void v298(); virtual void v2a0();
    virtual void v2a8(); virtual void v2b0(); virtual void v2b8(); virtual void v2c0(); virtual void v2c8();
    virtual void v2d0(); virtual void v2d8(); virtual void v2e0(); virtual void v2e8(); virtual void v2f0();
    virtual void v2f8(); virtual void v300(); virtual void v308(); virtual void v310(); virtual void v318();
    virtual void v320(); virtual void v328(); virtual void v330(); virtual void v338(); virtual void v340();
    virtual void v348(); virtual void v350(); virtual void v358(); virtual void v360(); virtual void v368();
    virtual void v370(); virtual void v378(); virtual void v380(); virtual void v388(); virtual void v390();
    virtual void v398(); virtual void v3a0(); virtual void v3a8(); virtual void v3b0(); virtual void v3b8();
    virtual void v3c0(); virtual void v3c8(); virtual void v3d0(); virtual void v3d8(); virtual void v3e0();
    virtual int command();       // +3e8
};

void prepare_cf594(void* part);                           // 0x71000cf594
void post_result_cff58(void* queue, int result);          // 0x71000cff58
void finish_d04bc(void* part);                            // 0x71000d04bc

// Completion through the unit's secondary base at +f8.
template <int Copy>
void complete_from_base_f8(unsigned char* base) {
    prepare_cf594(base - 0x10);
    CommandUnit2aec0* unit = reinterpret_cast<CommandUnit2aec0*>(base - 0xf8);
    unsigned char* queue = reinterpret_cast<unsigned char*>(unit) + 0x100;
    post_result_cff58(queue, unit->command());
    finish_d04bc(reinterpret_cast<unsigned char*>(unit) + 0x120);
}

template void complete_from_base_f8<0>(unsigned char*);   // 0x710002aec0
template void complete_from_base_f8<1>(unsigned char*);   // 0x71000cace0
