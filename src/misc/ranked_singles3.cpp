// A third set of single functions from tools/rank_targets.py. Names are descriptive placeholders;
// addresses are in the comments. Status: matching/README.md.

extern unsigned int gRandomSeed __attribute__((visibility("hidden")));     // 0x7100cf03f8

// 0x7100459bd8: linear congruential generator, result below the limit
int random_below(int limit) {
    unsigned int bound = limit;
    if (bound < 2)
        return 0;
    gRandomSeed = gRandomSeed * 0x41c64e6d + 0x3039;
    return (gRandomSeed >> 16) % bound;
}

struct Settings3fa4c8 {
    unsigned char pad[0x19c8];
    int locked;               // +19c8
    unsigned char pad19cc[0x34];
    int busy;                 // +1a00
    unsigned char pad1a04[0x110];
    unsigned int mode;        // +1b14
};
// Reached through the GOT slot at 0x7100c2b700.
extern Settings3fa4c8* gSettings3fa4c8;

// 0x71003fa4c8
void set_mode_3fa4c8(unsigned int mode) {
    Settings3fa4c8* settings = gSettings3fa4c8;
    if (!settings)
        return;
    if (settings->locked) {
        if (mode <= 3 && !settings->busy)
            settings->mode = mode;
    } else if (mode <= 3) {
        settings->mode = mode;
    }
}

struct Pair6e0 {
    short first;
    short second;
};
struct Placement6e0 {
    unsigned char pad[0xa90];
    Pair6e0 pairs[0x512];     // +a90
};

// 0x710006e070
int placement_6e070(Placement6e0* table, int row, void* unused, int* first, int* second) {
    int id = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(table) + row * 0x94 + 0x1eda);
    if (static_cast<unsigned int>(id) <= 0x511) {
        if (first)
            *first = table->pairs[id].first;
        if (second)
            *second = table->pairs[id].second;
    }
    return id;
}

// 0x710006e0b0
int placement_6e0b0(Placement6e0* table, int slot, void* unused, int* first, int* second) {
    int id = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(table) + 0x48198 + slot * 2);
    if (static_cast<unsigned int>(id) <= 0x511) {
        if (first)
            *first = table->pairs[id].first;
        if (second)
            *second = table->pairs[id].second;
    }
    return id;
}

class Probe1928c {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void refresh();   // +20
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual Probe1928c* target(); // +40
    virtual unsigned char* state(); // +48
};

// 0x710001928c
void refresh_target_1928c(Probe1928c* object) {
    if (!(object->state()[9] & 0x40))
        object->target()->refresh();
}

struct Owner461538 {
    unsigned char used;       // +00
    unsigned char pad1[7];
    void** context;           // +08
    unsigned char pad10[0xa8];
    void* buffer;             // +b8
    void* mapped;             // +c0
};
// Reached through the GOT slots at 0x7100c2bc40 and 0x7100c2bc48.
extern void (*gUnmap_c2bc40)(void* context, void* mapped);
extern void (*gFree_c2bc48)(void* buffer);

// 0x7100461538
void release_461538(Owner461538* owner) {
    if (void* mapped = owner->mapped) {
        void* context = *owner->context;
        gUnmap_c2bc40(context, mapped);
        owner->mapped = nullptr;
    }
    void* buffer = owner->buffer;
    gFree_c2bc48(buffer);
    owner->used = 0;
}

struct Owner4623d4 {
    unsigned char used;       // +00
    unsigned char kind;       // +01
    unsigned char pad2[0xe];
    void* handle;             // +10
};
// Reached through the GOT slots at 0x7100c2bdb0 and 0x7100c2bdb8.
extern void (*gCloseA_c2bdb0)(void* handle);
extern void (*gCloseB_c2bdb8)(void* handle);

// 0x71004623d4
void close_4623d4(Owner4623d4* owner) {
    switch (owner->kind) {
    case 1: {
        void* handle = owner->handle;
        gCloseA_c2bdb0(handle);
        break;
    }
    case 2: {
        void* handle = owner->handle;
        gCloseB_c2bdb8(handle);
        break;
    }
    }
    owner->handle = nullptr;
    owner->used = 0;
}

struct Section5f8f78 {
    unsigned char used;       // +00
    unsigned char locked;     // +01
    unsigned char extra;      // +02
    unsigned char pad3[5];
    unsigned char part8[0x20];  // +08
    unsigned char part28[0x28]; // +28
    unsigned char part50[0x30]; // +50
    unsigned char part80[0x1c]; // +80
    unsigned char part9c[4];    // +9c
};
void reset_part_46611c(void* part, void* context);                         // 0x710046611c
void reset_part_46637c(void* part, void* context);                         // 0x710046637c
void reset_part_46653c(void* part, void* context);                         // 0x710046653c
void reset_part_4668d8(void* part, void* context);                         // 0x71004668d8
void reset_part_4668f4(void* part, void* context);                         // 0x71004668f4

// 0x71005f8f78
void reset_section_5f8f78(Section5f8f78* section, void* context) {
    if (!section->locked) {
        reset_part_46611c(section->part50, context);
        reset_part_46637c(section->part28, context);
        reset_part_46653c(section->part80, context);
        reset_part_4668d8(section->part8, context);
        if (section->extra & 1)
            reset_part_4668f4(section->part9c, context);
    }
    section->used = 0;
}
