// More small code families found by tools/family_scan.py, grouped until their source files
// are linked: vtable-only constructors, getter-to-call chains, null-guarded global calls and
// two object disposals. Within a family the bodies are identical apart from the vtable,
// global or callee they use; classes and functions are named after their address, callees
// after theirs. Status: matching/README.md.

// Constructors that only store the vtable pointer.

// 0x710001856c; vtable through the GOT slot at 0x7100c21a58
class Plain_1856c {
public:
    Plain_1856c();
    virtual ~Plain_1856c();
};

Plain_1856c::Plain_1856c() {}

// 0x710004ddd8; vtable through the GOT slot at 0x7100c21f00
class Plain_4ddd8 {
public:
    Plain_4ddd8();
    virtual ~Plain_4ddd8();
};

Plain_4ddd8::Plain_4ddd8() {}

// 0x710006d674; vtable through the GOT slot at 0x7100c220e8
class Plain_6d674 {
public:
    Plain_6d674();
    virtual ~Plain_6d674();
};

Plain_6d674::Plain_6d674() {}

// 0x7100075bf8; vtable through the GOT slot at 0x7100c221a8
class Plain_75bf8 {
public:
    Plain_75bf8();
    virtual ~Plain_75bf8();
};

Plain_75bf8::Plain_75bf8() {}

// 0x710007a104; vtable through the GOT slot at 0x7100c221c8
class Plain_7a104 {
public:
    Plain_7a104();
    virtual ~Plain_7a104();
};

Plain_7a104::Plain_7a104() {}

// 0x71000aab24; vtable through the GOT slot at 0x7100c224a0
class Plain_aab24 {
public:
    Plain_aab24();
    virtual ~Plain_aab24();
};

Plain_aab24::Plain_aab24() {}

// 0x71000ade48; vtable through the GOT slot at 0x7100c224d0
class Plain_ade48 {
public:
    Plain_ade48();
    virtual ~Plain_ade48();
};

Plain_ade48::Plain_ade48() {}

// 0x71000bf6cc; vtable through the GOT slot at 0x7100c227f8
class Plain_bf6cc {
public:
    Plain_bf6cc();
    virtual ~Plain_bf6cc();
};

Plain_bf6cc::Plain_bf6cc() {}

// 0x71000bfad0; vtable through the GOT slot at 0x7100c22808
class Plain_bfad0 {
public:
    Plain_bfad0();
    virtual ~Plain_bfad0();
};

Plain_bfad0::Plain_bfad0() {}

// 0x71000c2f08; vtable through the GOT slot at 0x7100c22820
class Plain_c2f08 {
public:
    Plain_c2f08();
    virtual ~Plain_c2f08();
};

Plain_c2f08::Plain_c2f08() {}

// 0x71000c47bc; vtable through the GOT slot at 0x7100c22838
class Plain_c47bc {
public:
    Plain_c47bc();
    virtual ~Plain_c47bc();
};

Plain_c47bc::Plain_c47bc() {}

// 0x71000c919c; vtable through the GOT slot at 0x7100c228f0
class Plain_c919c {
public:
    Plain_c919c();
    virtual ~Plain_c919c();
};

Plain_c919c::Plain_c919c() {}

// 0x71000cb000; vtable through the GOT slot at 0x7100c22920
class Plain_cb000 {
public:
    Plain_cb000();
    virtual ~Plain_cb000();
};

Plain_cb000::Plain_cb000() {}

// 0x7100339084; vtable through the GOT slot at 0x7100c2aec0
class Plain_339084 {
public:
    Plain_339084();
    virtual ~Plain_339084();
};

Plain_339084::Plain_339084() {}

// 0x710043b234; vtable through the GOT slot at 0x7100c2ba38
class Plain_43b234 {
public:
    Plain_43b234();
    virtual ~Plain_43b234();
};

Plain_43b234::Plain_43b234() {}

// 0x71004e1620; vtable through the GOT slot at 0x7100c2cee8
class Plain_4e1620 {
public:
    Plain_4e1620();
    virtual ~Plain_4e1620();
};

Plain_4e1620::Plain_4e1620() {}

// 0x710053e630; vtable through the GOT slot at 0x7100c2d310
class Plain_53e630 {
public:
    Plain_53e630();
    virtual ~Plain_53e630();
};

Plain_53e630::Plain_53e630() {}

// 0x710053e718; vtable through the GOT slot at 0x7100c2d318
class Plain_53e718 {
public:
    Plain_53e718();
    virtual ~Plain_53e718();
};

Plain_53e718::Plain_53e718() {}

// 0x71005c2c78; vtable through the GOT slot at 0x7100c2db60
class Plain_5c2c78 {
public:
    Plain_5c2c78();
    virtual ~Plain_5c2c78();
};

Plain_5c2c78::Plain_5c2c78() {}

// 0x71005c3ad4; vtable through the GOT slot at 0x7100c2db70
class Plain_5c3ad4 {
public:
    Plain_5c3ad4();
    virtual ~Plain_5c3ad4();
};

Plain_5c3ad4::Plain_5c3ad4() {}

// 0x71005d43f0; vtable through the GOT slot at 0x7100c2dca8
class Plain_5d43f0 {
public:
    Plain_5d43f0();
    virtual ~Plain_5d43f0();
};

Plain_5d43f0::Plain_5d43f0() {}

// 0x71005dc26c; vtable through the GOT slot at 0x7100c2dd08
class Plain_5dc26c {
public:
    Plain_5dc26c();
    virtual ~Plain_5dc26c();
};

Plain_5dc26c::Plain_5dc26c() {}

// 0x7100600244; vtable through the GOT slot at 0x7100c2dee0
class Plain_600244 {
public:
    Plain_600244();
    virtual ~Plain_600244();
};

Plain_600244::Plain_600244() {}

// 0x7100600510; vtable through the GOT slot at 0x7100c2def8
class Plain_600510 {
public:
    Plain_600510();
    virtual ~Plain_600510();
};

Plain_600510::Plain_600510() {}


// Getter-to-call chains: pass the getter's result to one function.

void* fetch_20fbd4();                                               // 0x710020fbd4

void apply_20ff60(void* object);                                  // 0x710020ff60

void* fetch_3d2fd4();                                               // 0x71003d2fd4

void apply_3d6fd0(void* object);                                  // 0x71003d6fd0

void* fetch_452124();                                               // 0x7100452124

void apply_40cf4(void* object);                                  // 0x7100040cf4

void apply_3d6548(void* object);                                  // 0x71003d6548

void apply_3d711c(void* object);                                  // 0x71003d711c

void apply_3d63e4(void* object);                                  // 0x71003d63e4

void apply_3d64a4(void* object);                                  // 0x71003d64a4

void* fetch_16ef34();                                               // 0x710016ef34

void apply_16f71c(void* object);                                  // 0x710016f71c

void apply_3d6134(void* object);                                  // 0x71003d6134

void* fetch_204728();                                               // 0x7100204728

void apply_204710(void* object);                                  // 0x7100204710

void* fetch_3f3ac();                                               // 0x710003f3ac

void apply_3f3bc(void* object);                                  // 0x710003f3bc

void* fetch_3abbe0();                                               // 0x71003abbe0

void apply_3acc24(void* object);                                  // 0x71003acc24

void* fetch_2da374();                                               // 0x71002da374

void apply_2da438(void* object);                                  // 0x71002da438

void apply_3ad910(void* object);                                  // 0x71003ad910

void* fetch_45ce00();                                               // 0x710045ce00

void apply_45ce4c(void* object);                                  // 0x710045ce4c

void* fetch_43cf64();                                               // 0x710043cf64

void apply_43d714(void* object);                                  // 0x710043d714

void apply_43d81c(void* object);                                  // 0x710043d81c

void apply_43d2f8(void* object);                                  // 0x710043d2f8

void* fetch_425dd0();                                               // 0x7100425dd0

void apply_426c48(void* object);                                  // 0x7100426c48

void* fetch_4140a4();                                               // 0x71004140a4

void apply_415b08(void* object);                                  // 0x7100415b08

void apply_4273c8(void* object);                                  // 0x71004273c8

// 0x710000ea74
void chain_ea74() {
    apply_20ff60(fetch_20fbd4());
}

// 0x7100036710
void chain_36710() {
    apply_3d6fd0(fetch_3d2fd4());
}

// 0x71001727f0
void chain_1727f0() {
    apply_40cf4(fetch_452124());
}

// 0x71001769e8
void chain_1769e8() {
    apply_3d6548(fetch_3d2fd4());
}

// 0x7100176c28
void chain_176c28() {
    apply_3d711c(fetch_3d2fd4());
}

// 0x7100176c4c
void chain_176c4c() {
    apply_3d63e4(fetch_3d2fd4());
}

// 0x7100176c60
void chain_176c60() {
    apply_3d64a4(fetch_3d2fd4());
}

// 0x710018f0f0
void chain_18f0f0() {
    apply_16f71c(fetch_16ef34());
}

// 0x71001dfad4
void chain_1dfad4() {
    apply_3d6134(fetch_3d2fd4());
}

// 0x7100207ac4
void chain_207ac4() {
    apply_204710(fetch_204728());
}

// 0x7100256640
void chain_256640() {
    apply_3f3bc(fetch_3f3ac());
}

// 0x710034f300
void chain_34f300() {
    apply_3acc24(fetch_3abbe0());
}

// 0x7100354254
void chain_354254() {
    apply_2da438(fetch_2da374());
}

// 0x71003544c4
void chain_3544c4() {
    apply_3ad910(fetch_3abbe0());
}

// 0x71003ae760
void chain_3ae760() {
    apply_45ce4c(fetch_45ce00());
}

// 0x71003ae784
void chain_3ae784() {
    apply_45ce4c(fetch_45ce00());
}

// 0x71003b41e4
void chain_3b41e4() {
    apply_3acc24(fetch_3abbe0());
}

// 0x7100451fd4
void chain_451fd4() {
    apply_43d714(fetch_43cf64());
}

// 0x7100452024
void chain_452024() {
    apply_43d81c(fetch_43cf64());
}

// 0x7100452124
void chain_452124() {
    apply_43d2f8(fetch_43cf64());
}

// 0x71004521d4
void chain_4521d4() {
    apply_426c48(fetch_425dd0());
}

// 0x71004521e8
void chain_4521e8() {
    apply_415b08(fetch_4140a4());
}

// 0x7100453fc4
void chain_453fc4() {
    apply_4273c8(fetch_425dd0());
}


// Null-guarded global calls.

// Reached through the GOT slot at 0x7100c22a08.
extern void* gGlobal_c22a08;

void guarded_apply_d5778(void* object);                          // 0x71000d5778

// Reached through the GOT slot at 0x7100c22a60.
extern void* gGlobal_c22a60;

void guarded_apply_111954(void* object);                          // 0x7100111954

// Reached through the GOT slot at 0x7100c231b0.
extern void* gGlobal_c231b0;

void guarded_apply_1f4024(void* object);                          // 0x71001f4024

void guarded_apply_1f3c24(void* object);                          // 0x71001f3c24

void guarded_apply_1f4264(void* object);                          // 0x71001f4264

void guarded_apply_1f3f48(void* object);                          // 0x71001f3f48

void guarded_apply_1f41b4(void* object);                          // 0x71001f41b4

// Reached through the GOT slot at 0x7100c23240.
extern void* gSingleton_c23240;

void guarded_apply_2017d0(void* object);                          // 0x71002017d0

// Reached through the GOT slot at 0x7100c23318.
extern void* gSingleton_c23318;

void guarded_apply_20f4b8(void* object);                          // 0x710020f4b8

// Reached through the GOT slot at 0x7100c23340.
extern void* gGlobal_c23340;

void guarded_apply_211948(void* object);                          // 0x7100211948

// Reached through the GOT slot at 0x7100c2b700.
extern void* gGlobal_c2b700;

void guarded_apply_3f7090(void* object);                          // 0x71003f7090

// Reached through the GOT slot at 0x7100c2b710.
extern void* gGlobal_c2b710;

void guarded_apply_3fab38(void* object);                          // 0x71003fab38

void guarded_apply_3fbfac(void* object);                          // 0x71003fbfac

void guarded_apply_3faf9c(void* object);                          // 0x71003faf9c

void guarded_apply_3fd898(void* object);                          // 0x71003fd898

// Reached through the GOT slot at 0x7100c2b750.
extern void* gGlobal_c2b750;

void guarded_apply_40a92c(void* object);                          // 0x710040a92c

// Reached through the GOT slot at 0x7100c2bbd0.
extern void* gSingleton_c2bbd0;

void guarded_apply_45f07c(void* object);                          // 0x710045f07c

// 0x71000d5760
void guarded_global_d5760() {
    if (gGlobal_c22a08)
        guarded_apply_d5778(gGlobal_c22a08);
}

// 0x710011193c
void guarded_global_11193c() {
    if (gGlobal_c22a60)
        guarded_apply_111954(gGlobal_c22a60);
}

// 0x7100114fa8
void guarded_global_114fa8() {
    if (gGlobal_c22a60)
        guarded_apply_111954(gGlobal_c22a60);
}

// 0x71001f46bc
void guarded_global_1f46bc() {
    if (gGlobal_c231b0)
        guarded_apply_1f4024(gGlobal_c231b0);
}

// 0x71001f46d4
void guarded_global_1f46d4() {
    if (gGlobal_c231b0)
        guarded_apply_1f3c24(gGlobal_c231b0);
}

// 0x71001f46ec
void guarded_global_1f46ec() {
    if (gGlobal_c231b0)
        guarded_apply_1f4264(gGlobal_c231b0);
}

// 0x71001f4768
void guarded_global_1f4768() {
    if (gGlobal_c231b0)
        guarded_apply_1f3f48(gGlobal_c231b0);
}

// 0x71001f4b64
void guarded_global_1f4b64() {
    if (gGlobal_c231b0)
        guarded_apply_1f41b4(gGlobal_c231b0);
}

// 0x710020207c
void guarded_global_20207c() {
    if (gSingleton_c23240)
        guarded_apply_2017d0(gSingleton_c23240);
}

// 0x710020f90c
void guarded_global_20f90c() {
    if (gSingleton_c23318)
        guarded_apply_20f4b8(gSingleton_c23318);
}

// 0x71002136ac
void guarded_global_2136ac() {
    if (gGlobal_c23340)
        guarded_apply_211948(gGlobal_c23340);
}

// 0x71003f9e64
void guarded_global_3f9e64() {
    if (gGlobal_c2b700)
        guarded_apply_3f7090(gGlobal_c2b700);
}

// 0x71003fe108
void guarded_global_3fe108() {
    if (gGlobal_c2b710)
        guarded_apply_3fab38(gGlobal_c2b710);
}

// 0x71003fe254
void guarded_global_3fe254() {
    if (gGlobal_c2b710)
        guarded_apply_3fbfac(gGlobal_c2b710);
}

// 0x71003ff2c0
void guarded_global_3ff2c0() {
    if (gGlobal_c2b710)
        guarded_apply_3faf9c(gGlobal_c2b710);
}

// 0x71003ff360
void guarded_global_3ff360() {
    if (gGlobal_c2b710)
        guarded_apply_3fd898(gGlobal_c2b710);
}

// 0x710040b0c4
void guarded_global_40b0c4() {
    if (gGlobal_c2b750)
        guarded_apply_40a92c(gGlobal_c2b750);
}

// 0x7100460ed0
void guarded_global_460ed0() {
    if (gSingleton_c2bbd0)
        guarded_apply_45f07c(gSingleton_c2bbd0);
}


// Disposals through an allocator: the object is disposed of (virtual slot +8) and handed to its
// allocator's free (slot +60). The first family reads the allocator from the object, the second
// from its owner.
class Disposable {
public:
    virtual void v00();
    virtual void dispose();   // +08

    void* value08;            // +08
    class FreeList* allocator; // +10
};
class FreeList {
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
    virtual void free(void* object);                                        // +60
};

// 0x710040001c
void dispose_40001c(Disposable* object) {
    FreeList* allocator = object->allocator;
    if (object)
        object->dispose();
    allocator->free(object);
}

// 0x7100469640
void dispose_469640(Disposable* object) {
    FreeList* allocator = object->allocator;
    if (object)
        object->dispose();
    allocator->free(object);
}

// 0x7100534bc0
void dispose_534bc0(Disposable* object) {
    FreeList* allocator = object->allocator;
    if (object)
        object->dispose();
    allocator->free(object);
}

// 0x71005830a8
void dispose_5830a8(Disposable* object) {
    FreeList* allocator = object->allocator;
    if (object)
        object->dispose();
    allocator->free(object);
}

// 0x71005c8900
void dispose_5c8900(Disposable* object) {
    FreeList* allocator = object->allocator;
    if (object)
        object->dispose();
    allocator->free(object);
}

// 0x71005c94c0
void dispose_5c94c0(Disposable* object) {
    FreeList* allocator = object->allocator;
    if (object)
        object->dispose();
    allocator->free(object);
}

// 0x71005ca9a4
void dispose_5ca9a4(Disposable* object) {
    FreeList* allocator = object->allocator;
    if (object)
        object->dispose();
    allocator->free(object);
}


class Releasable {
public:
    virtual void release();   // +00
};

// 0x710051b3f0
struct Owner_51b3f0 {
    void dispose(Releasable* object);

    unsigned char pad[0x29d0];
    FreeList* allocator;      // +29d0
};

void Owner_51b3f0::dispose(Releasable* object) {
    object->release();
    allocator->free(object);
}

// 0x710051c2c8
struct Owner_51c2c8 {
    void dispose(Releasable* object);

    unsigned char pad[0x29d0];
    FreeList* allocator;      // +29d0
};

void Owner_51c2c8::dispose(Releasable* object) {
    object->release();
    allocator->free(object);
}

// 0x710051c82c
struct Owner_51c82c {
    void dispose(Releasable* object);

    unsigned char pad[0x29d0];
    FreeList* allocator;      // +29d0
};

void Owner_51c82c::dispose(Releasable* object) {
    object->release();
    allocator->free(object);
}

// 0x710051ca30
struct Owner_51ca30 {
    void dispose(Releasable* object);

    unsigned char pad[0x29d0];
    FreeList* allocator;      // +29d0
};

void Owner_51ca30::dispose(Releasable* object) {
    object->release();
    allocator->free(object);
}

// 0x710051dc84
struct Owner_51dc84 {
    void dispose(Releasable* object);

    unsigned char pad[0x29d0];
    FreeList* allocator;      // +29d0
};

void Owner_51dc84::dispose(Releasable* object) {
    object->release();
    allocator->free(object);
}

// 0x710051dcc4
struct Owner_51dcc4 {
    void dispose(Releasable* object);

    unsigned char pad[0x29d0];
    FreeList* allocator;      // +29d0
};

void Owner_51dcc4::dispose(Releasable* object) {
    object->release();
    allocator->free(object);
}

// 0x710051dd04
struct Owner_51dd04 {
    void dispose(Releasable* object);

    unsigned char pad[0x29d0];
    FreeList* allocator;      // +29d0
};

void Owner_51dd04::dispose(Releasable* object) {
    object->release();
    allocator->free(object);
}

// 0x710051dd44
struct Owner_51dd44 {
    void dispose(Releasable* object);

    unsigned char pad[0x29d0];
    FreeList* allocator;      // +29d0
};

void Owner_51dd44::dispose(Releasable* object) {
    object->release();
    allocator->free(object);
}

// 0x710051e7bc
struct Owner_51e7bc {
    void dispose(Releasable* object);

    unsigned char pad[0x29d0];
    FreeList* allocator;      // +29d0
};

void Owner_51e7bc::dispose(Releasable* object) {
    object->release();
    allocator->free(object);
}
