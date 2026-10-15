// Large functions written by hand (fifth session). Struct, field and callee names are placeholders after the
// address and offset, as in the generated units. Status: matching/README.md.

inline void* operator new(unsigned long, void* where) noexcept { return where; }

int callee_45c96c();        // 0x710045c96c
void* callee_45c458(int, int, long, int, int);        // 0x710045c458

static inline void* heap_alloc_38e39c(long size) {
    return callee_45c458(callee_45c96c(), 0x10, size, 1, 0);
}

struct Layers38e39c;
void callee_391ab8(Layers38e39c*, int, int);        // 0x7100391ab8
void callee_391ac0(Layers38e39c*, int);        // 0x7100391ac0
void callee_391ac4(Layers38e39c*, int);        // 0x7100391ac4
extern Layers38e39c* gGlobalc2b170_38e39c;
extern void* gGlobalc22dc0_38e39c;
void callee_2ccf38(void*, int);        // 0x71002ccf38

struct Scene38e39c;

class Mode38e39c {
public:
    virtual ~Mode38e39c();
    virtual void slot_2(void*);
    virtual void slot_3();
    virtual void slot_4();
    virtual void slot_5();
    virtual void slot_6(int);
    virtual void slot_7(int);
    virtual unsigned char finished();

    Scene38e39c* owner;           // +8
};

class Mode0_38e39c : public Mode38e39c {
public:
    unsigned char pad10[0x200];
    int field_210;                // +210
};

class Mode1_38e39c : public Mode38e39c {
};

class Mode2_38e39c : public Mode38e39c {
};

class Mode3_38e39c : public Mode38e39c {
};

class Mode4_38e39c : public Mode38e39c {
public:
    void set_210(int value) { field_210 = value; }
    void set_21c(int value) { field_21c = value; }
    unsigned char pad10[0x200];
    int field_210;                // +210
    unsigned char pad214[0x8];
    int field_21c;                // +21c
};

class Mode5_38e39c : public Mode38e39c {
};

class Mode6_38e39c : public Mode38e39c {
};

class Mode7_38e39c : public Mode38e39c {
};

class Mode9_38e39c : public Mode38e39c {
};

struct Scene38e39c {
    unsigned char pad0[0x28];
    Mode38e39c* current;          // +28
    Mode38e39c* previous;         // +30
    Mode0_38e39c* mode0;          // +38
    Mode1_38e39c* mode1;          // +40
    Mode2_38e39c* mode2;          // +48
    Mode3_38e39c* mode3;          // +50
    Mode4_38e39c* mode4;          // +58
    Mode6_38e39c* mode6;          // +60
    Mode7_38e39c* mode7;          // +68
    Mode38e39c mode8;             // +70
    unsigned char pad80[0x1b9e48];
    Mode9_38e39c* mode9;          // +1b9ec8
    Mode5_38e39c* mode5;          // +1b9ed0
    unsigned char pad1b9ed8[0x8];
    unsigned char field_1b9ee0[0x220];   // +1b9ee0
    int state;                    // +1ba100
    unsigned char pad1ba104[0x84];
    int table_1ba188[31];         // +1ba188
    int table_1ba204[31];         // +1ba204
    int field_1ba280;             // +1ba280

    void set_mode(int mode, int sub);
};

void callee_38dca4(Mode0_38e39c*, Scene38e39c*);        // 0x710038dca4
void callee_39036c(Mode1_38e39c*, Scene38e39c*);        // 0x710039036c
void callee_390854(Mode2_38e39c*);        // 0x7100390854
void callee_390928(Mode2_38e39c*, int);        // 0x7100390928
void callee_390c60(Mode3_38e39c*);        // 0x7100390c60
void callee_390dcc(Mode3_38e39c*, int);        // 0x7100390dcc
void callee_391034(Mode4_38e39c*);        // 0x7100391034
void callee_3911a0(Mode4_38e39c*, int);        // 0x71003911a0
void callee_395324(Mode5_38e39c*, Scene38e39c*);        // 0x7100395324
void callee_397750(Mode6_38e39c*, Scene38e39c*);        // 0x7100397750
void callee_392080(Mode7_38e39c*, Scene38e39c*);        // 0x7100392080
void callee_39bbec(Mode9_38e39c*, Scene38e39c*);        // 0x710039bbec
void callee_39be08(Mode9_38e39c*);        // 0x710039be08
unsigned char callee_39c6d8(Mode9_38e39c*);        // 0x710039c6d8
void callee_39cc64(Mode9_38e39c*, int);        // 0x710039cc64
int callee_3c750c(Scene38e39c*);        // 0x71003c750c
void callee_3c745c(Scene38e39c*, int, int, int);        // 0x71003c745c

// 0x710038e39c: switch to a mode, deleting the mode objects that finished (keeping the ones the new mode
// shares), creating the new mode's object on first use, setting the layers and the music.
void Scene38e39c::set_mode(int mode, int sub) {
    if (previous != nullptr) {
        previous = nullptr;
    }
    previous = current;
    if (current != nullptr) {
        current->slot_7(0);
    }
    if (mode0 != nullptr && mode0->finished()) {
        delete mode0;
        mode0 = nullptr;
    }
    if (mode1 != nullptr && mode1->finished() && (mode < 1 || mode > 4)) {
        delete mode1;
        mode1 = nullptr;
    }
    if (mode2 != nullptr && mode2->finished() && mode != 2 && mode != 3) {
        delete mode2;
        mode2 = nullptr;
    }
    if (mode3 != nullptr && mode3->finished()) {
        delete mode3;
        mode3 = nullptr;
    }
    if (mode4 != nullptr && mode4->finished() && (mode < 1 || mode > 4)) {
        delete mode4;
        mode4 = nullptr;
    }
    if (mode6 != nullptr && mode6->finished()) {
        delete mode6;
        mode6 = nullptr;
    }
    if (mode7 != nullptr && mode7->finished()) {
        delete mode7;
        mode7 = nullptr;
    }
    if (mode9 != nullptr && !callee_39c6d8(mode9)) {
        delete mode9;
        mode9 = nullptr;
    }
    if (mode5 != nullptr && mode5->finished()) {
        delete mode5;
        mode5 = nullptr;
    }
    int bgm;
    switch (mode) {
    case 0:
        if (mode0 == nullptr) {
            Mode0_38e39c* m = static_cast<Mode0_38e39c*>(heap_alloc_38e39c(0xd0d0));
            callee_38dca4(m, this);
            mode0 = m;
        }
        if (state == 1) {
            mode0->field_210 = 0;
        } else if (state >= 5 && state <= 9) {
            mode0->field_210 = state - 4;
        }
        current = mode0;
        state = 0;
        callee_391ac0(gGlobalc2b170_38e39c, 0);
        callee_391ac4(gGlobalc2b170_38e39c, 1);
        callee_391ac4(gGlobalc2b170_38e39c, 2);
        callee_391ac4(gGlobalc2b170_38e39c, 3);
        bgm = 0x16;
        break;
    case 1:
        if (mode1 == nullptr) {
            Mode1_38e39c* m = static_cast<Mode1_38e39c*>(heap_alloc_38e39c(0x3d0));
            callee_39036c(m, this);
            mode1 = m;
        }
        current = mode1;
        state = 1;
        callee_391ac0(gGlobalc2b170_38e39c, 0);
        callee_391ac0(gGlobalc2b170_38e39c, 1);
        callee_391ac0(gGlobalc2b170_38e39c, 2);
        callee_391ac0(gGlobalc2b170_38e39c, 3);
        callee_391ab8(gGlobalc2b170_38e39c, 1, 2);
        callee_391ab8(gGlobalc2b170_38e39c, 2, 4);
        callee_391ab8(gGlobalc2b170_38e39c, 3, 3);
        bgm = 0x17;
        break;
    case 2:
        if (mode2 == nullptr) {
            Mode2_38e39c* m = static_cast<Mode2_38e39c*>(heap_alloc_38e39c(0x11680));
            callee_390854(m);
            mode2 = m;
            m->owner = this;
            callee_390928(mode2, static_cast<unsigned int>(sub) < 0x1f ? sub : 0);
        }
        current = mode2;
        field_1ba280 = sub;
        state = 2;
        callee_391ac0(gGlobalc2b170_38e39c, 0);
        callee_391ac0(gGlobalc2b170_38e39c, 1);
        callee_391ac0(gGlobalc2b170_38e39c, 2);
        callee_391ac4(gGlobalc2b170_38e39c, 3);
        callee_391ab8(gGlobalc2b170_38e39c, 1, 4);
        callee_391ab8(gGlobalc2b170_38e39c, 2, 3);
        bgm = 0x17;
        break;
    case 3:
        if (mode3 == nullptr) {
            Mode3_38e39c* m = static_cast<Mode3_38e39c*>(heap_alloc_38e39c(0xae78));
            callee_390c60(m);
            mode3 = m;
            m->owner = this;
            callee_390dcc(mode3, sub);
        }
        current = mode3;
        state = 3;
        callee_391ac0(gGlobalc2b170_38e39c, 0);
        callee_391ac0(gGlobalc2b170_38e39c, 1);
        callee_391ac0(gGlobalc2b170_38e39c, 2);
        callee_391ac4(gGlobalc2b170_38e39c, 3);
        callee_391ab8(gGlobalc2b170_38e39c, 1, 4);
        callee_391ab8(gGlobalc2b170_38e39c, 2, 3);
        bgm = 0x17;
        break;
    case 4: {
        if (mode4 != nullptr) {
            delete mode4;
            mode4 = nullptr;
        }
        Mode4_38e39c* m = static_cast<Mode4_38e39c*>(heap_alloc_38e39c(0x4d990));
        callee_391034(m);
        mode4 = m;
        m->owner = this;
        callee_3911a0(mode4, static_cast<unsigned int>(sub) < 0x1f ? sub : 0);
        mode4->set_210(table_1ba188[sub]);
        mode4->set_21c(table_1ba204[sub]);
        current = mode4;
        state = 4;
        callee_391ac0(gGlobalc2b170_38e39c, 0);
        callee_391ac0(gGlobalc2b170_38e39c, 1);
        callee_391ac0(gGlobalc2b170_38e39c, 2);
        callee_391ac4(gGlobalc2b170_38e39c, 3);
        callee_391ab8(gGlobalc2b170_38e39c, 1, 4);
        callee_391ab8(gGlobalc2b170_38e39c, 2, 3);
        bgm = 0x17;
        break;
    }
    case 5:
        if (mode5 == nullptr) {
            Mode5_38e39c* m = static_cast<Mode5_38e39c*>(heap_alloc_38e39c(0x99298));
            callee_395324(m, this);
            mode5 = m;
        }
        current = mode5;
        state = 5;
        callee_391ac0(gGlobalc2b170_38e39c, 0);
        callee_391ac4(gGlobalc2b170_38e39c, 1);
        callee_391ac4(gGlobalc2b170_38e39c, 2);
        callee_391ac4(gGlobalc2b170_38e39c, 3);
        bgm = 0x31;
        break;
    case 6:
        if (mode6 == nullptr) {
            Mode6_38e39c* m = static_cast<Mode6_38e39c*>(heap_alloc_38e39c(0x6e9a8));
            callee_397750(m, this);
            mode6 = m;
        }
        current = mode6;
        state = 6;
        callee_391ac0(gGlobalc2b170_38e39c, 0);
        callee_391ac4(gGlobalc2b170_38e39c, 1);
        callee_391ac4(gGlobalc2b170_38e39c, 2);
        callee_391ac4(gGlobalc2b170_38e39c, 3);
        bgm = 0x18;
        break;
    case 7:
        if (mode7 == nullptr) {
            Mode7_38e39c* m = static_cast<Mode7_38e39c*>(heap_alloc_38e39c(0x1e9a0));
            callee_392080(m, this);
            mode7 = m;
        }
        current = mode7;
        state = 7;
        callee_391ac0(gGlobalc2b170_38e39c, 0);
        callee_391ac4(gGlobalc2b170_38e39c, 1);
        callee_391ac4(gGlobalc2b170_38e39c, 2);
        callee_391ac4(gGlobalc2b170_38e39c, 3);
        bgm = 0x19;
        break;
    case 8:
        current = &mode8;
        state = 8;
        callee_391ac0(gGlobalc2b170_38e39c, 0);
        callee_391ac4(gGlobalc2b170_38e39c, 1);
        callee_391ac4(gGlobalc2b170_38e39c, 2);
        callee_391ac4(gGlobalc2b170_38e39c, 3);
        bgm = 0x1a;
        break;
    case 9:
        if (mode9 == nullptr) {
            Mode9_38e39c* m = static_cast<Mode9_38e39c*>(heap_alloc_38e39c(0x2ceb0));
            callee_39bbec(m, this);
            mode9 = m;
            callee_39be08(m);
            callee_39cc64(mode9, 0);
        }
        current = mode9;
        state = 9;
        callee_391ac0(gGlobalc2b170_38e39c, 0);
        callee_391ac4(gGlobalc2b170_38e39c, 1);
        callee_391ac4(gGlobalc2b170_38e39c, 2);
        callee_391ac4(gGlobalc2b170_38e39c, 3);
        bgm = 8;
        break;
    case 10:
        callee_2ccf38(gGlobalc22dc0_38e39c, 0);
        callee_391ac4(gGlobalc2b170_38e39c, 0);
        callee_391ac4(gGlobalc2b170_38e39c, 1);
        callee_391ac4(gGlobalc2b170_38e39c, 2);
        callee_391ac4(gGlobalc2b170_38e39c, 3);
        current = nullptr;
        state = 10;
        goto done;
    default:
        goto done;
    }
    if (bgm != callee_3c750c(this)) {
        callee_3c745c(this, bgm, 0, -1);
    }
done:
    if (current != nullptr) {
        current->slot_6(0);
        current->slot_2(field_1b9ee0);
    }
    if (previous == current) {
        previous = nullptr;
    }
}
