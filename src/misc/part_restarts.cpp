// Four-part animation restarts (0x71003bdae4-0x71003c5608): each part is reset (or rewound), played
// and given the same rate. Only the first part is null-checked. Found by tools/family_scan.py
// --immediates. Names are descriptive placeholders. Status: matching/README.md.

struct AnimPart {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void play(int mode);
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
    virtual void set_rate(float rate);
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void reset();
    virtual void rewind();
};
struct Restart3bdae4 {
    unsigned char pad[0x270];
    AnimPart* parts[4];       // +270
};

// 0x71003bdae4
void restart_parts_3bdae4(Restart3bdae4* object, float rate) {
    if (object->parts[0])
        object->parts[0]->reset();
    if (object->parts[0])
        object->parts[0]->play(1);
    object->parts[0]->set_rate(rate);
    object->parts[1]->reset();
    object->parts[1]->play(1);
    object->parts[1]->set_rate(rate);
    object->parts[2]->reset();
    object->parts[2]->play(1);
    object->parts[2]->set_rate(rate);
    object->parts[3]->reset();
    object->parts[3]->play(1);
    object->parts[3]->set_rate(rate);
}
struct Restart3c0870 {
    unsigned char pad[0x250];
    AnimPart* parts[4];       // +250
};

// 0x71003c0870
void restart_parts_3c0870(Restart3c0870* object, float rate) {
    if (object->parts[0])
        object->parts[0]->reset();
    if (object->parts[0])
        object->parts[0]->play(1);
    object->parts[0]->set_rate(rate);
    object->parts[1]->reset();
    object->parts[1]->play(1);
    object->parts[1]->set_rate(rate);
    object->parts[2]->reset();
    object->parts[2]->play(1);
    object->parts[2]->set_rate(rate);
    object->parts[3]->reset();
    object->parts[3]->play(1);
    object->parts[3]->set_rate(rate);
}
struct Restart3c324c {
    unsigned char pad[0x230];
    AnimPart* parts[4];       // +230
};

// 0x71003c324c
void restart_parts_3c324c(Restart3c324c* object, float rate) {
    if (object->parts[0])
        object->parts[0]->reset();
    if (object->parts[0])
        object->parts[0]->play(1);
    object->parts[0]->set_rate(rate);
    object->parts[1]->reset();
    object->parts[1]->play(1);
    object->parts[1]->set_rate(rate);
    object->parts[2]->reset();
    object->parts[2]->play(1);
    object->parts[2]->set_rate(rate);
    object->parts[3]->reset();
    object->parts[3]->play(1);
    object->parts[3]->set_rate(rate);
}
struct Restart3c5608 {
    unsigned char pad[0x230];
    AnimPart* parts[4];       // +230
};

// 0x71003c5608
void restart_parts_3c5608(Restart3c5608* object, float rate) {
    if (object->parts[0])
        object->parts[0]->rewind();
    if (object->parts[0])
        object->parts[0]->play(1);
    object->parts[0]->set_rate(rate);
    object->parts[1]->rewind();
    object->parts[1]->play(1);
    object->parts[1]->set_rate(rate);
    object->parts[2]->rewind();
    object->parts[2]->play(1);
    object->parts[2]->set_rate(rate);
    object->parts[3]->rewind();
    object->parts[3]->play(1);
    object->parts[3]->set_rate(rate);
}
