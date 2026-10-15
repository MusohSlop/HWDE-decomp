// A scene's start routine (fourth session, 2-copy family 5f794): clears bit 1 of three lookup-service flags, resets,
// prepares (the one call that differs: 0x710005fae8 or 0x7100060d60), enters every ready entry and applies the 0x44b
// lookup range. Scene5f794::start<0> (0x710005f794) and start<1> (0x7100060c2c). Names are descriptive placeholders.

struct LookupService {
    unsigned char pad0[0x14];
    unsigned int flags14;     // +14
    unsigned char pad18[0x104];
    unsigned int flags11c;    // +11c
    unsigned char pad120[0x34];
    unsigned int flags154;    // +154
};
// Reached through the GOT slot at 0x7100c216f0.
extern LookupService* gLookupService;

int lookup_first_6ec7c(int a, int b);                                       // 0x710006ec7c
int lookup_second_6ecc8(int a, int b);                                      // 0x710006ecc8
int lookup_6e070(LookupService* service, int a, int b, int* first, int* second); // 0x710006e070

struct PlatformFlags {
    unsigned char pad0[4];
    unsigned char bits;       // +4: bit 2 skips the lookup
};
PlatformFlags* get_platform_flags();                                        // 0x710016ef34

struct SceneEntry {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual unsigned char ready();
    unsigned char pad8[0x30];
};

class Scene5f794 {
public:
    template <int Copy> void start();
    void reset_5f8c8();                                                     // 0x710005f8c8
    void prepare_5fae8();                                                   // 0x710005fae8
    void prepare_60d60();                                                   // 0x7100060d60
    void enter_678d4(SceneEntry* e);                                        // 0x71000678d4
    void set_range_6a4f4(int first, int second);                            // 0x710006a4f4

    template <int Copy> void prepare() {
        if (Copy == 0)
            prepare_5fae8();
        else
            prepare_60d60();
    }

    SceneEntry* entries;      // +00
    unsigned char pad8[0x48];
    unsigned int count;       // +50
    unsigned char pad54[0x2610];
    int timer;                // +2664
    int phase;                // +2668
};

template <int Copy>
void Scene5f794::start() {
    LookupService* s = gLookupService;
    s->flags14 &= ~2u;
    s->flags11c &= ~2u;
    s->flags154 &= ~2u;
    timer = 0;
    reset_5f8c8();
    phase = 5;
    prepare<Copy>();
    for (unsigned int i = 0; i < count; i++) {
        SceneEntry* e = &entries[i];
        if (e->ready()) enter_678d4(e);
    }
    if (get_platform_flags()->bits & 4) return;
    int first = lookup_first_6ec7c(0x44b, 0);
    int second = lookup_second_6ecc8(0x44b, 0);
    set_range_6a4f4(first, second);
    if (static_cast<unsigned int>(lookup_6e070(gLookupService, 0x44b, 0, &first, &second)) <= 0x511)
        set_range_6a4f4(first, second);
}

// 0x710005f794
template void Scene5f794::start<0>();
// 0x7100060c2c
template void Scene5f794::start<1>();
