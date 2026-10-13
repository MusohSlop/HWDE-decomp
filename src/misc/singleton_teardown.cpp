// Singleton teardown functions found by tools/rank_targets.py: each frees a heap-allocated
// singleton held in a global pointer and clears the pointer. They are byte-identical apart
// from the global, and each sits in its owner's source file (the address gives the region),
// so they are grouped here until those files are linked. Globals without a known role are
// named after their GOT slot. Status: matching/README.md.

class DefaultHeap {
public:
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

static inline void destroy_singleton(void*& slot) {
    if (void* object = slot) {
        get_default_heap()->release(object, 1, 0);
        slot = nullptr;
    }
}

// Reached through the GOT slot at 0x7100c22a50.
extern void* gSingleton_c22a50;

// 0x71000d8730; original file: the owner's source file around 0x71000d8730
void destroy_singleton_c22a50() {
    destroy_singleton(gSingleton_c22a50);
}

// Reached through the GOT slot at 0x7100c22ad0.
extern void* gSingleton_c22ad0;

// 0x71000dd8a8; original file: the owner's source file around 0x71000dd8a8
void destroy_singleton_c22ad0() {
    destroy_singleton(gSingleton_c22ad0);
}

// Reached through the GOT slot at 0x7100c22ad8.
extern void* gSingleton_c22ad8;

// 0x71000df518; original file: the owner's source file around 0x71000df518
void destroy_singleton_c22ad8() {
    destroy_singleton(gSingleton_c22ad8);
}

// Reached through the GOT slot at 0x7100c22ab8.
extern void* gSingleton_c22ab8;

// 0x710011fbdc; original file: the owner's source file around 0x710011fbdc
void destroy_singleton_c22ab8() {
    destroy_singleton(gSingleton_c22ab8);
}

// Reached through the GOT slot at 0x7100c22ac0.
extern void* gSingleton_c22ac0;

// 0x710013255c; original file: the owner's source file around 0x710013255c
void destroy_singleton_c22ac0() {
    destroy_singleton(gSingleton_c22ac0);
}

// Reached through the GOT slot at 0x7100c22cb8.
extern void* gSingleton_c22cb8;

// 0x71001469fc; original file: the owner's source file around 0x71001469fc
void destroy_singleton_c22cb8() {
    destroy_singleton(gSingleton_c22cb8);
}

// Reached through the GOT slot at 0x7100c22cd8.
extern void* gSingleton_c22cd8;

// 0x7100164a50; original file: the owner's source file around 0x7100164a50
void destroy_singleton_c22cd8() {
    destroy_singleton(gSingleton_c22cd8);
}

// Reached through the GOT slot at 0x7100c22e10.
extern void* gSingleton_c22e10;

// 0x71001875e8; original file: the owner's source file around 0x71001875e8
void destroy_singleton_c22e10() {
    destroy_singleton(gSingleton_c22e10);
}

// Reached through the GOT slot at 0x7100c22e68.
extern void* gSingleton_c22e68;

// 0x71001a9cdc; original file: the owner's source file around 0x71001a9cdc
void destroy_singleton_c22e68() {
    destroy_singleton(gSingleton_c22e68);
}

// Reached through the GOT slot at 0x7100c22d30.
extern void* gSingleton_c22d30;

// 0x71001cbc1c; original file: the owner's source file around 0x71001cbc1c
void destroy_singleton_c22d30() {
    destroy_singleton(gSingleton_c22d30);
}

// Reached through the GOT slot at 0x7100c23018.
extern void* gScreenFader;

// 0x71001e522c; original file: the owner's source file around 0x71001e522c
void destroy_screen_fader() {
    destroy_singleton(gScreenFader);
}

// Reached through the GOT slot at 0x7100c23218.
extern void* gSingleton_c23218;

// 0x71001fea0c; original file: the owner's source file around 0x71001fea0c
void destroy_singleton_c23218() {
    destroy_singleton(gSingleton_c23218);
}

// Reached through the GOT slot at 0x7100c23220.
extern void* gSingleton_c23220;

// 0x71001fee84; original file: the owner's source file around 0x71001fee84
void destroy_singleton_c23220() {
    destroy_singleton(gSingleton_c23220);
}

// Reached through the GOT slot at 0x7100c23228.
extern void* gItemTable;

// 0x71001ff0bc; original file: the owner's source file around 0x71001ff0bc
void destroy_item_table() {
    destroy_singleton(gItemTable);
}

// Reached through the GOT slot at 0x7100c23230.
extern void* gSingleton_c23230;

// 0x7100201374; original file: the owner's source file around 0x7100201374
void destroy_singleton_c23230() {
    destroy_singleton(gSingleton_c23230);
}

// Reached through the GOT slot at 0x7100c23238.
extern void* gSingleton_c23238;

// 0x7100201694; original file: the owner's source file around 0x7100201694
void destroy_singleton_c23238() {
    destroy_singleton(gSingleton_c23238);
}

// Reached through the GOT slot at 0x7100c23240.
extern void* gSingleton_c23240;

// 0x710020203c; original file: the owner's source file around 0x710020203c
void destroy_singleton_c23240() {
    destroy_singleton(gSingleton_c23240);
}

// Reached through the GOT slot at 0x7100c23260.
extern void* gSingleton_c23260;

// 0x7100204d14; original file: the owner's source file around 0x7100204d14
void destroy_singleton_c23260() {
    destroy_singleton(gSingleton_c23260);
}

// Reached through the GOT slot at 0x7100c23268.
extern void* gSingleton_c23268;

// 0x7100207288; original file: the owner's source file around 0x7100207288
void destroy_singleton_c23268() {
    destroy_singleton(gSingleton_c23268);
}

// Reached through the GOT slot at 0x7100c23270.
extern void* gSingleton_c23270;

// 0x7100207608; original file: the owner's source file around 0x7100207608
void destroy_singleton_c23270() {
    destroy_singleton(gSingleton_c23270);
}

// Reached through the GOT slot at 0x7100c23298.
extern void* gSingleton_c23298;

// 0x7100209abc; original file: the owner's source file around 0x7100209abc
void destroy_singleton_c23298() {
    destroy_singleton(gSingleton_c23298);
}

// Reached through the GOT slot at 0x7100c232a0.
extern void* gSingleton_c232a0;

// 0x7100209d6c; original file: the owner's source file around 0x7100209d6c
void destroy_singleton_c232a0() {
    destroy_singleton(gSingleton_c232a0);
}

// Reached through the GOT slot at 0x7100c232a8.
extern void* gSingleton_c232a8;

// 0x710020a42c; original file: the owner's source file around 0x710020a42c
void destroy_singleton_c232a8() {
    destroy_singleton(gSingleton_c232a8);
}

// Reached through the GOT slot at 0x7100c232b0.
extern void* gSingleton_c232b0;

// 0x710020ad1c; original file: the owner's source file around 0x710020ad1c
void destroy_singleton_c232b0() {
    destroy_singleton(gSingleton_c232b0);
}

// Reached through the GOT slot at 0x7100c232b8.
extern void* gSingleton_c232b8;

// 0x710020b304; original file: the owner's source file around 0x710020b304
void destroy_singleton_c232b8() {
    destroy_singleton(gSingleton_c232b8);
}

// Reached through the GOT slot at 0x7100c232c0.
extern void* gSingleton_c232c0;

// 0x710020b448; original file: the owner's source file around 0x710020b448
void destroy_singleton_c232c0() {
    destroy_singleton(gSingleton_c232c0);
}

// Reached through the GOT slot at 0x7100c232c8.
extern void* gSingleton_c232c8;

// 0x710020b6ac; original file: the owner's source file around 0x710020b6ac
void destroy_singleton_c232c8() {
    destroy_singleton(gSingleton_c232c8);
}

// Reached through the GOT slot at 0x7100c232d0.
extern void* gProfileStats;

// 0x710020b9dc; original file: the owner's source file around 0x710020b9dc
void destroy_profile_stats() {
    destroy_singleton(gProfileStats);
}

// Reached through the GOT slot at 0x7100c232e0.
extern void* gSingleton_c232e0;

// 0x710020c6ec; original file: the owner's source file around 0x710020c6ec
void destroy_singleton_c232e0() {
    destroy_singleton(gSingleton_c232e0);
}

// Reached through the GOT slot at 0x7100c23318.
extern void* gSingleton_c23318;

// 0x710020f8cc; original file: the owner's source file around 0x710020f8cc
void destroy_singleton_c23318() {
    destroy_singleton(gSingleton_c23318);
}

// Reached through the GOT slot at 0x7100c23320.
extern void* gSingleton_c23320;

// 0x710020fd80; original file: the owner's source file around 0x710020fd80
void destroy_singleton_c23320() {
    destroy_singleton(gSingleton_c23320);
}

// Reached through the GOT slot at 0x7100c23330.
extern void* gSingleton_c23330;

// 0x71002103a8; original file: the owner's source file around 0x71002103a8
void destroy_singleton_c23330() {
    destroy_singleton(gSingleton_c23330);
}

// Reached through the GOT slot at 0x7100c23338.
extern void* gSingleton_c23338;

// 0x71002107ec; original file: the owner's source file around 0x71002107ec
void destroy_singleton_c23338() {
    destroy_singleton(gSingleton_c23338);
}

// Reached through the GOT slot at 0x7100c216a0.
extern void* gItemDefs;

// 0x71002110d8; original file: the owner's source file around 0x71002110d8
void destroy_item_defs() {
    destroy_singleton(gItemDefs);
}

// Reached through the GOT slot at 0x7100c23360.
extern void* gSingleton_c23360;

// 0x7100214174; original file: the owner's source file around 0x7100214174
void destroy_singleton_c23360() {
    destroy_singleton(gSingleton_c23360);
}

// Reached through the GOT slot at 0x7100c23358.
extern void* gSingleton_c23358;

// 0x7100214a1c; original file: the owner's source file around 0x7100214a1c
void destroy_singleton_c23358() {
    destroy_singleton(gSingleton_c23358);
}

// Reached through the GOT slot at 0x7100c23370.
extern void* gSingleton_c23370;

// 0x7100214c38; original file: the owner's source file around 0x7100214c38
void destroy_singleton_c23370() {
    destroy_singleton(gSingleton_c23370);
}

// Reached through the GOT slot at 0x7100c23378.
extern void* gSingleton_c23378;

// 0x7100214e00; original file: the owner's source file around 0x7100214e00
void destroy_singleton_c23378() {
    destroy_singleton(gSingleton_c23378);
}

// Reached through the GOT slot at 0x7100c23368.
extern void* gSingleton_c23368;

// 0x71002152c8; original file: the owner's source file around 0x71002152c8
void destroy_singleton_c23368() {
    destroy_singleton(gSingleton_c23368);
}

// Reached through the GOT slot at 0x7100c23380.
extern void* gSingleton_c23380;

// 0x7100215880; original file: the owner's source file around 0x7100215880
void destroy_singleton_c23380() {
    destroy_singleton(gSingleton_c23380);
}

// Reached through the GOT slot at 0x7100c23390.
extern void* gSingleton_c23390;

// 0x7100216ecc; original file: the owner's source file around 0x7100216ecc
void destroy_singleton_c23390() {
    destroy_singleton(gSingleton_c23390);
}

// Reached through the GOT slot at 0x7100c2a528.
extern void* gSingleton_c2a528;

// 0x7100248c60; original file: the owner's source file around 0x7100248c60
void destroy_singleton_c2a528() {
    destroy_singleton(gSingleton_c2a528);
}

// Reached through the GOT slot at 0x7100c2b758.
extern void* gSingleton_c2b758;

// 0x710040d5e8; original file: the owner's source file around 0x710040d5e8
void destroy_singleton_c2b758() {
    destroy_singleton(gSingleton_c2b758);
}

// Reached through the GOT slot at 0x7100c2ba90.
extern void* gSingleton_c2ba90;

// 0x710044bbe0; original file: the owner's source file around 0x710044bbe0
void destroy_singleton_c2ba90() {
    destroy_singleton(gSingleton_c2ba90);
}

// Reached through the GOT slot at 0x7100c2bbb8.
extern void* gSingleton_c2bbb8;

// 0x710045d7c4; original file: the owner's source file around 0x710045d7c4
void destroy_singleton_c2bbb8() {
    destroy_singleton(gSingleton_c2bbb8);
}

// Reached through the GOT slot at 0x7100c2bbd0.
extern void* gSingleton_c2bbd0;

// 0x7100460e90; original file: the owner's source file around 0x7100460e90
void destroy_singleton_c2bbd0() {
    destroy_singleton(gSingleton_c2bbd0);
}
