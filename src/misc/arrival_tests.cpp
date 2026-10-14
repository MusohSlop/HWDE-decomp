// Arrival tests (0x7100024364 and four more, identical code): note whether the object's position is
// already within a tiny epsilon of its target, apply the new value, then report whether it has just
// arrived. Found by tools/family_scan.py. Names are descriptive placeholders. Status:
// matching/README.md.

void apply_value_e6a4(int id, float value);                               // 0x710000e6a4

struct Mover {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67();
    virtual void slot68();
    virtual void slot69();
    virtual void slot70();
    virtual void slot71();
    virtual void slot72();
    virtual void slot73();
    virtual void slot74();
    virtual void slot75();
    virtual void slot76();
    virtual void slot77();
    virtual void slot78();
    virtual void slot79();
    virtual void slot80();
    virtual void slot81();
    virtual void slot82();
    virtual void slot83();
    virtual void slot84();
    virtual void slot85();
    virtual void slot86();
    virtual void slot87();
    virtual void slot88();
    virtual void slot89();
    virtual void slot90();
    virtual void slot91();
    virtual void slot92();
    virtual void slot93();
    virtual void slot94();
    virtual void slot95();
    virtual void slot96();
    virtual void slot97();
    virtual void slot98();
    virtual void slot99();
    virtual void slot100();
    virtual void slot101();
    virtual void slot102();
    virtual void slot103();
    virtual void slot104();
    virtual void slot105();
    virtual void slot106();
    virtual void slot107();
    virtual void slot108();
    virtual void slot109();
    virtual void slot110();
    virtual void slot111();
    virtual void slot112();
    virtual void slot113();
    virtual void slot114();
    virtual void slot115();
    virtual void slot116();
    virtual void slot117();
    virtual void slot118();
    virtual void slot119();
    virtual void slot120();
    virtual void slot121();
    virtual void slot122();
    virtual void slot123();
    virtual void slot124();
    virtual void slot125();
    virtual void slot126();
    virtual void slot127();
    virtual float position();
    virtual void slot129();
    virtual float target();

    unsigned char pad8[0x1c];
    short id;                 // +24
};

static inline bool near_target(Mover* mover, float target) {
    float position = mover->position();
    return target >= position + -1.1920928955078125e-05f && target <= position + 1.1920928955078125e-05f;
}
// 0x7100024364
bool arrived_24364(Mover* mover, float value) {
    float target = mover->target();
    float position = mover->position();
    bool was_near = false;
    if (position + -1.1920928955078125e-05f <= target && position + 1.1920928955078125e-05f >= target)
        was_near = true;
    apply_value_e6a4(mover->id, value);
    return !was_near && near_target(mover, target);
}
// 0x71000271e8
bool arrived_271e8(Mover* mover, float value) {
    float target = mover->target();
    float position = mover->position();
    bool was_near = false;
    if (position + -1.1920928955078125e-05f <= target && position + 1.1920928955078125e-05f >= target)
        was_near = true;
    apply_value_e6a4(mover->id, value);
    return !was_near && near_target(mover, target);
}
// 0x71000290b8
bool arrived_290b8(Mover* mover, float value) {
    float target = mover->target();
    float position = mover->position();
    bool was_near = false;
    if (position + -1.1920928955078125e-05f <= target && position + 1.1920928955078125e-05f >= target)
        was_near = true;
    apply_value_e6a4(mover->id, value);
    return !was_near && near_target(mover, target);
}
// 0x710002a9f0
bool arrived_2a9f0(Mover* mover, float value) {
    float target = mover->target();
    float position = mover->position();
    bool was_near = false;
    if (position + -1.1920928955078125e-05f <= target && position + 1.1920928955078125e-05f >= target)
        was_near = true;
    apply_value_e6a4(mover->id, value);
    return !was_near && near_target(mover, target);
}
// 0x71000ca9e4
bool arrived_ca9e4(Mover* mover, float value) {
    float target = mover->target();
    float position = mover->position();
    bool was_near = false;
    if (position + -1.1920928955078125e-05f <= target && position + 1.1920928955078125e-05f >= target)
        was_near = true;
    apply_value_e6a4(mover->id, value);
    return !was_near && near_target(mover, target);
}
