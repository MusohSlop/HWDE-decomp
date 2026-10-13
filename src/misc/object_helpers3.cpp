// Mixed small families from tools/family_scan.py --immediates: command completions (directly and
// through a secondary base), event broadcasts, unconditional singleton creation, triple-buffered row
// values, list visits, paired optional calls, value searches and created-then-started singletons.
// Each group differs only in offsets, slots and callees; types and functions are named after their
// address. Status: matching/README.md.

class DefaultHeap {
public:
    void* allocate(unsigned int alignment, unsigned long size, int a, int b); // 0x710045c458
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

inline void* operator new(unsigned long, void* storage) { return storage; }

class CommandUnit {
public:
    virtual void v000();
    virtual void v008();
    virtual void v010();
    virtual void v018();
    virtual void v020();
    virtual void v028();
    virtual void v030();
    virtual void v038();
    virtual void v040();
    virtual void v048();
    virtual void v050();
    virtual void v058();
    virtual void v060();
    virtual void v068();
    virtual void v070();
    virtual void v078();
    virtual void v080();
    virtual void v088();
    virtual void v090();
    virtual void v098();
    virtual void v0a0();
    virtual void v0a8();
    virtual void v0b0();
    virtual void v0b8();
    virtual void v0c0();
    virtual void v0c8();
    virtual void v0d0();
    virtual void v0d8();
    virtual void v0e0();
    virtual void v0e8();
    virtual void v0f0();
    virtual void v0f8();
    virtual void v100();
    virtual void v108();
    virtual void v110();
    virtual void v118();
    virtual void v120();
    virtual void v128();
    virtual void v130();
    virtual void v138();
    virtual void v140();
    virtual void v148();
    virtual void v150();
    virtual void v158();
    virtual void v160();
    virtual void v168();
    virtual void v170();
    virtual void v178();
    virtual void v180();
    virtual void v188();
    virtual void v190();
    virtual void v198();
    virtual void v1a0();
    virtual void v1a8();
    virtual void v1b0();
    virtual void v1b8();
    virtual void v1c0();
    virtual void v1c8();
    virtual void v1d0();
    virtual void v1d8();
    virtual void v1e0();
    virtual void v1e8();
    virtual void v1f0();
    virtual void v1f8();
    virtual void v200();
    virtual void v208();
    virtual void v210();
    virtual void v218();
    virtual void v220();
    virtual void v228();
    virtual void v230();
    virtual void v238();
    virtual void v240();
    virtual void v248();
    virtual void v250();
    virtual void v258();
    virtual void v260();
    virtual void v268();
    virtual void v270();
    virtual void v278();
    virtual void v280();
    virtual void v288();
    virtual void v290();
    virtual void v298();
    virtual void v2a0();
    virtual void v2a8();
    virtual void v2b0();
    virtual void v2b8();
    virtual void v2c0();
    virtual void v2c8();
    virtual void v2d0();
    virtual void v2d8();
    virtual void v2e0();
    virtual void v2e8();
    virtual void v2f0();
    virtual void v2f8();
    virtual void v300();
    virtual void v308();
    virtual void v310();
    virtual void v318();
    virtual void v320();
    virtual void v328();
    virtual void v330();
    virtual void v338();
    virtual void v340();
    virtual void v348();
    virtual void v350();
    virtual void v358();
    virtual void v360();
    virtual void v368();
    virtual void v370();
    virtual void v378();
    virtual void v380();
    virtual void v388();
    virtual void v390();
    virtual void v398();
    virtual void v3a0();
    virtual void v3a8();
    virtual void v3b0();
    virtual void v3b8();
    virtual void v3c0();
    virtual void v3c8();
    virtual void v3d0();
    virtual void v3d8();
    virtual void v3e0();
    virtual int command();    // +3e8

    unsigned char body[0x140];
};

void prepare_cf5c4(void* part);                           // 0x71000cf5c4
void post_result_cff58(void* queue, int result);          // 0x71000cff58
void finish_d04bc(void* part);                            // 0x71000d04bc

// 0x71000292b8
void complete_command_292b8(CommandUnit* unit) {
    prepare_cf5c4(reinterpret_cast<unsigned char*>(unit) + 0xe8);
    unsigned char* queue = reinterpret_cast<unsigned char*>(unit) + 0x110;
    post_result_cff58(queue, unit->command());
    finish_d04bc(reinterpret_cast<unsigned char*>(unit) + 0x130);
}

void prepare_cf594(void* part);                           // 0x71000cf594

// 0x710002abec
void complete_command_2abec(CommandUnit* unit) {
    prepare_cf594(reinterpret_cast<unsigned char*>(unit) + 0xe8);
    unsigned char* queue = reinterpret_cast<unsigned char*>(unit) + 0x100;
    post_result_cff58(queue, unit->command());
    finish_d04bc(reinterpret_cast<unsigned char*>(unit) + 0x120);
}


// 0x71000cabe0
void complete_command_cabe0(CommandUnit* unit) {
    prepare_cf594(reinterpret_cast<unsigned char*>(unit) + 0xe8);
    unsigned char* queue = reinterpret_cast<unsigned char*>(unit) + 0x100;
    post_result_cff58(queue, unit->command());
    finish_d04bc(reinterpret_cast<unsigned char*>(unit) + 0x120);
}


// 0x71000294a0: secondary base at +e8
void complete_from_base_294a0(unsigned char* base) {
    prepare_cf5c4(base);
    CommandUnit* unit = reinterpret_cast<CommandUnit*>(base - 0xe8);
    unsigned char* queue = reinterpret_cast<unsigned char*>(unit) + 0x110;
    post_result_cff58(queue, unit->command());
    finish_d04bc(reinterpret_cast<unsigned char*>(unit) + 0x130);
}


// 0x710002adbc: secondary base at +e8
void complete_from_base_2adbc(unsigned char* base) {
    prepare_cf594(base);
    CommandUnit* unit = reinterpret_cast<CommandUnit*>(base - 0xe8);
    unsigned char* queue = reinterpret_cast<unsigned char*>(unit) + 0x100;
    post_result_cff58(queue, unit->command());
    finish_d04bc(reinterpret_cast<unsigned char*>(unit) + 0x120);
}


// 0x71000cac78: secondary base at +e8
void complete_from_base_cac78(unsigned char* base) {
    prepare_cf594(base);
    CommandUnit* unit = reinterpret_cast<CommandUnit*>(base - 0xe8);
    unsigned char* queue = reinterpret_cast<unsigned char*>(unit) + 0x100;
    post_result_cff58(queue, unit->command());
    finish_d04bc(reinterpret_cast<unsigned char*>(unit) + 0x120);
}

namespace nn {
namespace os {
struct EventType;
void SignalEvent(EventType* event);
void WaitEvent(EventType* event);
}  // namespace os
}  // namespace nn

struct Broadcaster56b120 {
    unsigned char pad[0x58];
    nn::os::EventType** events; // +58
    unsigned char pad60[0x18];
    int count;                // +78
};

// 0x710056b120
void signal_all_56b120(Broadcaster56b120* object) {
    for (long i = 0; i < object->count; ++i)
        nn::os::SignalEvent(object->events[i]);
}

struct Broadcaster56b168 {
    unsigned char pad[0x70];
    nn::os::EventType** events; // +70
    unsigned char pad78[0x0];
    int count;                // +78
};

// 0x710056b168
void wait_all_56b168(Broadcaster56b168* object) {
    for (long i = 0; i < object->count; ++i)
        nn::os::WaitEvent(object->events[i]);
}

struct Broadcaster56b1b0 {
    unsigned char pad[0x70];
    nn::os::EventType** events; // +70
    unsigned char pad78[0x0];
    int count;                // +78
};

// 0x710056b1b0
void wait_all_56b1b0(Broadcaster56b1b0* object) {
    for (long i = 0; i < object->count; ++i)
        nn::os::WaitEvent(object->events[i]);
}

class Created5dea4 {
public:
    Created5dea4();                                                // 0x710005df48

    unsigned char data[0x3148];
};
// Reached through the GOT slot at 0x7100c22058.
extern Created5dea4* gCreated_5dea4;

// 0x710005dea4
void create_5dea4() {
    void* storage = get_default_heap()->allocate(0x10, sizeof(Created5dea4), 1, 0);
    gCreated_5dea4 = new (storage) Created5dea4;
}

class Created184f80 {
public:
    Created184f80();                                               // 0x7100184e20

    unsigned char data[0x7920];
};
// Reached through the GOT slot at 0x7100c22d60.
extern Created184f80* gCreated_184f80;

// 0x7100184f80
void create_184f80() {
    void* storage = get_default_heap()->allocate(0x10, sizeof(Created184f80), 1, 0);
    gCreated_184f80 = new (storage) Created184f80;
}

class Created3ec804 {
public:
    Created3ec804();                                               // 0x71003ec8a4

    unsigned char data[0x4a0];
};
// Reached through the GOT slot at 0x7100c22d58.
extern Created3ec804* gCreated_3ec804;

// 0x71003ec804
void create_3ec804() {
    void* storage = get_default_heap()->allocate(0x10, sizeof(Created3ec804), 1, 0);
    gCreated_3ec804 = new (storage) Created3ec804;
}

struct BufRow3d7154 {
    float value;
    unsigned char pad4[0x3ac];
};
struct Buffered3d7154 {
    unsigned char pad[0x710e0];
    unsigned int frame;       // +710e0
    unsigned char pad710e4[0xefc];
    BufRow3d7154 rows[1];   // +71fe0, 0x760 bytes per buffer
};

// 0x71003d7154
float buffered_value_3d7154(Buffered3d7154* object, int row) {
    unsigned int buffer = object->frame % 3;
    return reinterpret_cast<BufRow3d7154*>(reinterpret_cast<unsigned char*>(object->rows) + buffer * 0x760)[row].value;
}

struct BufRow3d7198 {
    float value;
    unsigned char pad4[0x3ac];
};
struct Buffered3d7198 {
    unsigned char pad[0x710e0];
    unsigned int frame;       // +710e0
    unsigned char pad710e4[0xf00];
    BufRow3d7198 rows[1];   // +71fe4, 0x760 bytes per buffer
};

// 0x71003d7198
float buffered_value_3d7198(Buffered3d7198* object, int row) {
    unsigned int buffer = object->frame % 3;
    return reinterpret_cast<BufRow3d7198*>(reinterpret_cast<unsigned char*>(object->rows) + buffer * 0x760)[row].value;
}

struct BufRow3d71dc {
    float value;
    unsigned char pad4[0x3ac];
};
struct Buffered3d71dc {
    unsigned char pad[0x710e0];
    unsigned int frame;       // +710e0
    unsigned char pad710e4[0xe28];
    BufRow3d71dc rows[1];   // +71f0c, 0x760 bytes per buffer
};

// 0x71003d71dc
float buffered_value_3d71dc(Buffered3d71dc* object, int row) {
    unsigned int buffer = object->frame % 3;
    return reinterpret_cast<BufRow3d71dc*>(reinterpret_cast<unsigned char*>(object->rows) + buffer * 0x760)[row].value;
}

class Visited595d94 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void visit(void* arg); // +30

    Visited595d94* next;     // +08
};

// 0x7100595d94
void visit_all_595d94(Visited595d94* node, void* arg) {
    do {
        node->visit(arg);
        node = node->next;
    } while (node);
}

class Visited595dd0 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void visit(void* arg); // +38

    Visited595dd0* next;     // +08
};

// 0x7100595dd0
void visit_all_595dd0(Visited595dd0* node, void* arg) {
    do {
        node->visit(arg);
        node = node->next;
    } while (node);
}

class Visited595e0c {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void visit(void* arg); // +40

    Visited595e0c* next;     // +08
};

// 0x7100595e0c
void visit_all_595e0c(Visited595e0c* node, void* arg) {
    do {
        node->visit(arg);
        node = node->next;
    } while (node);
}

void part_first_5cb348(void* part);                       // 0x71005cb348
void part_second_5cdb80(void* part);                      // 0x71005cdb80
struct PairedParts5cbe28 {
    unsigned char pad[0x430];
    void* first;              // +430
    void* second;             // +438
};

// 0x71005cbe28
void run_parts_5cbe28(PairedParts5cbe28* object) {
    if (object->first)
        part_first_5cb348(object->first);
    if (object->second)
        part_second_5cdb80(object->second);
}

void part_first_5cb420(void* part);                       // 0x71005cb420
void part_second_5cdbfc(void* part);                      // 0x71005cdbfc
struct PairedParts5cbe64 {
    unsigned char pad[0x430];
    void* first;              // +430
    void* second;             // +438
};

// 0x71005cbe64
void run_parts_5cbe64(PairedParts5cbe64* object) {
    if (object->first)
        part_first_5cb420(object->first);
    if (object->second)
        part_second_5cdbfc(object->second);
}

void part_first_5ce10c(void* part);                       // 0x71005ce10c
void part_second_5ce10c(void* part);                      // 0x71005ce10c
struct PairedParts5d2804 {
    unsigned char pad[0xc8];
    void* first;              // +c8
    void* second;             // +d0
};

// 0x71005d2804
void run_parts_5d2804(PairedParts5d2804* object) {
    if (object->first)
        part_first_5ce10c(object->first);
    if (object->second)
        part_second_5ce10c(object->second);
}

struct Searchable1599c0 {
    unsigned char pad0[0x40];
    int* values;  // +40
    unsigned char pad48[0x4];
    int count;  // +4c
    unsigned char pad50[0x8];
    void* ready;  // +58
};

// 0x71001599c0
unsigned char contains_1599c0(Searchable1599c0* object, int value) {
    if (!object->ready)
        return 0;
    int found = -1;
    for (int i = 0; i < object->count; ++i) {
        if (object->values[i] == value) {
            found = i;
            break;
        }
    }
    return found >= 0;
}

struct Searchable159a1c {
    unsigned char pad0[0x20];
    int* values;  // +20
    unsigned char pad28[0x4];
    int count;  // +2c
    unsigned char pad30[0x8];
    void* ready;  // +38
};

// 0x7100159a1c
unsigned char contains_159a1c(Searchable159a1c* object, int value) {
    if (!object->ready)
        return 0;
    int found = -1;
    for (int i = 0; i < object->count; ++i) {
        if (object->values[i] == value) {
            found = i;
            break;
        }
    }
    return found >= 0;
}

struct Searchable159a78 {
    int* values;  // +0
    unsigned char pad8[0x4];
    int count;  // +c
    unsigned char pad10[0x8];
    void* ready;  // +18
};

// 0x7100159a78
unsigned char contains_159a78(Searchable159a78* object, int value) {
    if (!object->ready)
        return 0;
    int found = -1;
    for (int i = 0; i < object->count; ++i) {
        if (object->values[i] == value) {
            found = i;
            break;
        }
    }
    return found >= 0;
}

class Started1de9f8 {
public:
    Started1de9f8();                                               // 0x71001ddfe8
    void start();                                                       // 0x71001ddd00

    unsigned char data[0x23f0];
};
// Reached through the GOT slot at 0x7100c22ef8.
extern Started1de9f8* gStarted_1de9f8;

// 0x71001de9f8
void ensure_started_1de9f8() {
    if (gStarted_1de9f8)
        return;
    void* storage = get_default_heap()->allocate(0x10, sizeof(Started1de9f8), 1, 0);
    gStarted_1de9f8 = new (storage) Started1de9f8;
    gStarted_1de9f8->start();
}

class Started1e4434 {
public:
    Started1e4434();                                               // 0x71001e1390
    void start();                                                       // 0x71001e1548

    unsigned char data[0x1340];
};
// Reached through the GOT slot at 0x7100c22a00.
extern Started1e4434* gStarted_1e4434;

// 0x71001e4434
void ensure_started_1e4434() {
    if (gStarted_1e4434)
        return;
    void* storage = get_default_heap()->allocate(0x10, sizeof(Started1e4434), 1, 0);
    gStarted_1e4434 = new (storage) Started1e4434;
    gStarted_1e4434->start();
}

class Started3fe0ac {
public:
    Started3fe0ac();                                               // 0x71003fa73c
    void start();                                                       // 0x71003faa10

    unsigned char data[0x1c10];
};
// Reached through the GOT slot at 0x7100c2b710.
extern Started3fe0ac* gStarted_3fe0ac;

// 0x71003fe0ac
void ensure_started_3fe0ac() {
    if (gStarted_3fe0ac)
        return;
    void* storage = get_default_heap()->allocate(0x10, sizeof(Started3fe0ac), 1, 0);
    gStarted_3fe0ac = new (storage) Started3fe0ac;
    gStarted_3fe0ac->start();
}
