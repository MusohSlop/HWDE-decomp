// Joint links (0x7100055d74, 0x7100059494, 0x7100059b24, 0x7100059fb8, identical code): connect the
// bodies of a joint's two ends, then attach the first end's node to the second end's node. Also a few
// other joint helpers and record constructors from the same area. Found by
// tools/family_scan.py. Names are descriptive placeholders. Status: matching/README.md.

struct JointBody;
void connect_bodies_cb0a8(JointBody* a, JointBody* b);                      // 0x71000cb0a8

struct BodyShape {
    virtual void slot0();
    virtual void slot1();
    virtual void refresh();
};

struct JointBody {
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
    virtual unsigned char is_static();

    unsigned char pad8[0x1c];
    unsigned short kind;      // +24
    unsigned char pad26[0xa];
    BodyShape* shape;         // +30
    unsigned char pad38[0x33];
    bool linked;              // +6b
};

struct JointNode {
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
    virtual void attach(JointNode* other);
};

struct JointEnd {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual JointNode* node();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual JointBody* body();
};

struct Joint {
    unsigned char pad[8];
    JointEnd* first;          // +08
    JointEnd* second;         // +10
};
// 0x7100055d74
void link_joint_55d74(Joint* joint) {
    connect_bodies_cb0a8(joint->first->body(), joint->second->body());
    joint->first->node()->attach(joint->second->node());
}
// 0x7100059494
void link_joint_59494(Joint* joint) {
    connect_bodies_cb0a8(joint->first->body(), joint->second->body());
    joint->first->node()->attach(joint->second->node());
}
// 0x7100059b24
void link_joint_59b24(Joint* joint) {
    connect_bodies_cb0a8(joint->first->body(), joint->second->body());
    joint->first->node()->attach(joint->second->node());
}
// 0x7100059fb8
void link_joint_59fb8(Joint* joint) {
    connect_bodies_cb0a8(joint->first->body(), joint->second->body());
    joint->first->node()->attach(joint->second->node());
}

// 0x7100055e0c
unsigned char first_end_movable_55e0c(Joint* joint) {
    if (joint->first->body()->is_static())
        return 0;
    return 1;
}

// 0x7100059398
void refresh_first_shape_59398(Joint* joint) {
    joint->first->body()->shape->refresh();
}

struct KindMap {
    unsigned char pad[0xefa8];
    unsigned short kinds[1];  // +efa8
};
// Reached through the GOT slot at 0x7100c21690.
extern KindMap* gGlobal_c21690;

struct KindJoint : Joint {
    unsigned char pad18[0xc];
    unsigned int kinds;       // +24: low half the body kind, high half its mapped kind
};

// 0x7100059e84
void capture_kind_59e84(KindJoint* joint) {
    KindMap* map = gGlobal_c21690;
    unsigned short kind = joint->second->body()->kind;
    unsigned short mapped = map->kinds[static_cast<short>(kind)];
    joint->kinds = kind | mapped << 16;
    joint->second->body()->linked = true;
}

// Vtable through the GOT slot at 0x7100c21ff8.
class JointRecord {
public:
    JointRecord();
    virtual void key_function();

    void* owner;              // +08
    void* link;               // +10
    long id;                  // +18
    int first;                // +20
    int second;               // +24
    void* data;               // +28
    void* extra;              // +30
};

// 0x7100055e50
JointRecord::JointRecord() : owner(nullptr), link(nullptr), id(-1), first(0), second(-1), data(nullptr), extra(nullptr) {}

// Vtable through the GOT slot at 0x7100c22000.
class JointSlot {
public:
    JointSlot();
    virtual void key_function();

    void* owner;              // +08
    void* link;               // +10
    int a;                    // +18
    int b;                    // +1c
    int c;                    // +20
    int d;                    // +24
    void* data;               // +28
    void* extra;              // +30
};

// 0x7100055e78
JointSlot::JointSlot() : owner(nullptr), link(nullptr), a(-1), b(-1), c(0), d(-1), data(nullptr), extra(nullptr) {}

// Vtable through the GOT slot at 0x7100c22030.
class JointMark {
public:
    JointMark();
    virtual void key_function();

    void* owner;              // +08
    void* link;               // +10
    int a;                    // +18
    int b;                    // +1c
    int c;                    // +20
};

// 0x71000593c4
JointMark::JointMark() : owner(nullptr), link(nullptr), a(-1), b(-1), c(0) {}