// Fifth session, parked: 0x71003b0428 (1,800 bytes), the start of a stage sequence (reads the stage's settings,
// fills the state's id list, then either restores a save or sets up a new one, and runs the loading request).
// This draft compiles to 1,764 bytes, 37 instructions off when registers are abstracted. Still off: the second
// mode == 7 test is jump-threaded through the mode == 3 arm here (the original tests it after both arms merge, and
// tests mode == 7 again later instead of keeping a flag); the last loop's exit compares against count - 1 built as
// the sum of the seven id flags in the original (an LFTR-style exit), ours compares against the select chain; the
// restart byte is spilled to the stack in the original. Callees whose first parameter is unsigned need an explicit
// --map in tools/s5/sbs.py (its address regex stops at 'j'):
// --name _ZN10Task3b04285startEv --map got:gGlobalc22dc0_3b0428=0x7100c22dc0 --map got:gGlobalc21db0_3b0428=0x7100c21db0 --map memcpy=0x7100600870 --map _Z13callee_1fc0a8jbbb=0x71001fc0a8 --map _Z13callee_20f9dcjib=0x710020f9dc --map _Z13callee_20faa8ji=0x710020faa8 --map _Z13callee_20fb0cji=0x710020fb0c --map _Z13callee_20fb70ji=0x710020fb70 --map _Z13callee_3c9668jiiii=0x71003c9668

extern "C" void* memcpy(void*, const void*, unsigned long);

struct Mgr3b0428;
struct Info3b0428;
struct Stage3b0428 {
    virtual void slot_0();
    virtual void slot_1();
    virtual Info3b0428* info(unsigned int stage);
};
struct Save3b0428;
struct Party3b0428 {
    unsigned char pad0[0x318];
    int field_318;                    // +318
};
extern Party3b0428* gGlobalc22dc0_3b0428;
extern void* gGlobalc21db0_3b0428;

struct Object3b0428 {
    virtual void slot_0();
    virtual void destroy();
};

Mgr3b0428* callee_204728();        // 0x7100204728
unsigned int callee_20363c(Mgr3b0428*);        // 0x710020363c
unsigned int callee_2034e0(Mgr3b0428*);        // 0x71002034e0
Stage3b0428* callee_20dfd0();        // 0x710020dfd0
int callee_20d8f4(Info3b0428*);        // 0x710020d8f4
int callee_20d908(Info3b0428*);        // 0x710020d908
unsigned char callee_20d91c(Info3b0428*);        // 0x710020d91c
int callee_203618(Mgr3b0428*);        // 0x7100203618
int callee_2034bc(Mgr3b0428*);        // 0x71002034bc
int callee_20faa8(unsigned int, int);        // 0x710020faa8
int callee_2035ac(Mgr3b0428*, int);        // 0x71002035ac
int callee_203504(Mgr3b0428*, int);        // 0x7100203504
unsigned int callee_20f9dc(unsigned int, int, bool);        // 0x710020f9dc
Save3b0428* callee_1a8c38();        // 0x71001a8c38
int* callee_20fbd4();        // 0x710020fbd4
void callee_210250(int*);        // 0x7100210250
int* callee_20fed8(int*);        // 0x710020fed8
void callee_1a8df4(Save3b0428*, int);        // 0x71001a8df4
void callee_1a8e14(Save3b0428*, int);        // 0x71001a8e14
void callee_2cc1e0(Party3b0428*, bool);        // 0x71002cc1e0
void callee_2cda2c(Party3b0428*);        // 0x71002cda2c
int callee_1a8d7c(Save3b0428*);        // 0x71001a8d7c
unsigned int callee_20fb0c(unsigned int, int);        // 0x710020fb0c
void callee_20fb70(unsigned int, int);        // 0x710020fb70
void callee_3c9668(unsigned int, int, int, int, int);        // 0x71003c9668
void* callee_2aae3c();        // 0x71002aae3c
unsigned char callee_2ac7f0(void*);        // 0x71002ac7f0
void callee_1a8ba4(Save3b0428*);        // 0x71001a8ba4
unsigned char callee_202eb0(Mgr3b0428*, int, int);        // 0x7100202eb0
void callee_1a8d04(Save3b0428*, int);        // 0x71001a8d04
void callee_1a8d14(Save3b0428*, int);        // 0x71001a8d14
unsigned char callee_2035f8(Mgr3b0428*);        // 0x71002035f8
void callee_1a8d24(Save3b0428*, unsigned char);        // 0x71001a8d24
unsigned char callee_203608(Mgr3b0428*);        // 0x7100203608
void callee_1a8d34(Save3b0428*, unsigned char);        // 0x71001a8d34
void callee_1a8d48(Save3b0428*, int, int);        // 0x71001a8d48
void callee_1a8d84(Save3b0428*, int);        // 0x71001a8d84
void callee_1a8d94(Save3b0428*, int);        // 0x71001a8d94
void callee_1a8dac(Save3b0428*, unsigned int);        // 0x71001a8dac
void callee_1a8dc4(Save3b0428*, int);        // 0x71001a8dc4
void callee_1a8dd4(Save3b0428*, int);        // 0x71001a8dd4
int callee_459bd8(int);        // 0x7100459bd8
void callee_1a8de4(Save3b0428*, int);        // 0x71001a8de4
void callee_1fc0a8(unsigned int, bool, bool, bool);        // 0x71001fc0a8
int callee_202800(Mgr3b0428*);        // 0x7100202800
void* callee_3abbe0();        // 0x71003abbe0
void callee_3ad160(void*);        // 0x71003ad160
void callee_3abd40();        // 0x71003abd40
void* callee_45c96c();        // 0x710045c96c
Object3b0428* callee_45c458(void*, int, int, bool, bool);        // 0x710045c458
void callee_1721b0(Object3b0428*);        // 0x71001721b0
struct Request3b0428 {
    unsigned char restart;            // +0
    unsigned char pad1[3];
    unsigned char done;               // +4
};
void callee_175b08(Object3b0428*, Request3b0428*);        // 0x7100175b08
int callee_2ad584(void*, Object3b0428*);        // 0x71002ad584
void callee_175d54(Object3b0428*);        // 0x7100175d54
void callee_2ad464(void*, int, bool);        // 0x71002ad464
void callee_52ad98(void*);        // 0x710052ad98
void callee_3ade70(int, int, int);        // 0x71003ade70

static inline void read_alt(int* p) {
    p[0] = callee_2035ac(callee_204728(), 0);
    p[1] = callee_2035ac(callee_204728(), 1);
    p[2] = callee_2035ac(callee_204728(), 2);
    p[3] = callee_2035ac(callee_204728(), 3);
}

static inline void read_normal(int* p) {
    p[0] = callee_203504(callee_204728(), 0);
    p[1] = callee_203504(callee_204728(), 1);
    p[2] = callee_203504(callee_204728(), 2);
    p[3] = callee_203504(callee_204728(), 3);
}

struct State3b0428 {
    int mode;                         // +0
    int next;                         // +4
    unsigned char restart;            // +8
    unsigned char pad9[0xb];
    unsigned int stage;               // +14
    unsigned char pad18[0xc];
    unsigned int ids[8];              // +24
};

struct Task3b0428 {
    State3b0428* state;

    void start();
};

// 0x71003b0428
void Task3b0428::start() {
    int mode = state->mode;
    unsigned char restart = state->restart;
    Mgr3b0428* mgr = callee_204728();
    int kind = (mode == 3) << 1;
    unsigned int stage = mode == 3 ? callee_20363c(mgr) : callee_2034e0(mgr);
    if (mode == 7) {
        stage = state->stage;
        kind = 2;
    }
    int field_a = callee_20d8f4(callee_20dfd0()->info(stage));
    int field_b = callee_20d908(callee_20dfd0()->info(stage));
    unsigned char field_c = callee_20d91c(callee_20dfd0()->info(stage));
    mgr = callee_204728();
    int level;
    int bonus;
    int p[4];
    if (mode == 3) {
        level = callee_203618(mgr);
        bonus = callee_20faa8(stage, 0);
        read_alt(p);
    } else {
        level = callee_2034bc(mgr);
        bonus = callee_20faa8(stage, 0);
        if (mode == 7) {
            read_alt(p);
        } else {
            read_normal(p);
        }
    }
    for (int i = 0; i < 8; i++) {
        state->ids[i] = 0xffffffff;
    }
    if (mode == 7) {
        level = 1;
    }
    unsigned int n = 0;
    for (int i = 0; i < 7; i++) {
        unsigned int id = callee_20f9dc(stage, i, false);
        if (id < 100) {
            state->ids[n++] = id;
        }
    }
    if (restart) {
        Save3b0428* save = callee_1a8c38();
        callee_210250(callee_20fbd4());
        memcpy(save, callee_20fed8(callee_20fbd4()), 200);
        callee_1a8df4(save, -1);
        callee_1a8e14(save, 0);
        callee_2cc1e0(gGlobalc22dc0_3b0428, true);
        callee_2cda2c(gGlobalc22dc0_3b0428);
        if (callee_1a8d7c(save) >= 0 && callee_1a8d7c(save) < 0x17) {
            gGlobalc22dc0_3b0428->field_318 = callee_1a8d7c(save);
        }
    } else {
        if (mode != 3) {
            unsigned int count = callee_20fb0c(stage, 3);
            callee_20fb70(stage, 3);
            if (count <= 0x46) {
                callee_3c9668(count, 1, 1, 1, 0);
                if (callee_2ac7f0(callee_2aae3c())) {
                    state->next = 9;
                    return;
                }
            }
        }
        Save3b0428* save = callee_1a8c38();
        callee_1a8ba4(save);
        if (!callee_202eb0(callee_204728(), 0, -1)) {
            callee_1a8e14(save, 0);
            bonus = -1;
        }
        callee_1a8d04(save, kind);
        callee_1a8d14(save, field_c ? field_c * 60 : -1);
        callee_1a8d24(save, callee_2035f8(callee_204728()));
        callee_1a8d34(save, callee_203608(callee_204728()));
        callee_1a8d48(save, 0, p[0]);
        callee_1a8d48(save, 1, p[1]);
        callee_1a8d48(save, 2, p[2]);
        callee_1a8d48(save, 3, p[3]);
        callee_1a8d84(save, field_a);
        callee_1a8d94(save, 0);
        callee_1a8dac(save, stage);
        callee_1a8dc4(save, field_b);
        callee_1a8dd4(save, level);
        callee_1a8de4(save, callee_459bd8(10000));
        callee_1a8df4(save, bonus);
        if ((mode | 4) == 7) {
            callee_1a8df4(save, -1);
        }
        State3b0428* st = state;
        unsigned int count = 0;
        for (int i = 0; i < 7; i++) {
            if (st->ids[i] < 100) {
                count++;
            }
        }
        if (count != 0) {
            callee_1fc0a8(st->ids[0], true, true, false);
            st = state;
            for (unsigned int i = 1; i < count; i++) {
                callee_1fc0a8(st->ids[i], true, true, false);
                st = state;
            }
        }
        st->ids[7] = callee_202800(callee_204728());
    }
    if (callee_3abbe0() != nullptr) {
        callee_3ad160(callee_3abbe0());
        callee_3abd40();
    }
    Request3b0428 request;
    request.done = 0;
    *reinterpret_cast<int*>(&request) = 0;
    request.restart = restart;
    Object3b0428* obj = callee_45c458(callee_45c96c(), 0x10, 0xb3b10, true, false);
    callee_1721b0(obj);
    callee_175b08(obj, &request);
    int result = callee_2ad584(callee_2aae3c(), obj);
    callee_175d54(obj);
    if (obj != nullptr) {
        obj->destroy();
    }
    callee_2ad464(callee_2aae3c(), 2, false);
    callee_52ad98(gGlobalc21db0_3b0428);
    switch (result) {
    case 2:
    case 3:
        state->next = 0;
        callee_3ade70(4, 0, 0);
        return;
    case 1:
        if (request.done) {
            state->next = 7;
            state->restart = 0;
            return;
        }
        state->next = 0;
        callee_3ade70(4, 0, 0);
        return;
    }
    state->next = 9;
}
