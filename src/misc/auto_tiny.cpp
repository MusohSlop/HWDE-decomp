// Tiny functions synthesized from their instructions (one shape each: field getters and setters,
// clears, constant returns, member addresses, part and child forwards, virtual forwards and fixed
// clears). Types and functions are named after their address. Status: matching/README.md.

extern "C" void* memset(void* dest, int value, unsigned long size);

// 0x710000019c
int zero_19c() {
    return 0;
}

// 0x7100009adc
int constant_9adc() {
    return 1;
}

// 0x710000c2a8
int zero_c2a8() {
    return 0;
}

// 0x710000c2b0
int zero_c2b0() {
    return 0;
}

// 0x710000e048
int zero_e048() {
    return 0;
}

struct Field100ec {
    unsigned char pad[0x3c];
    float value;  // +3c
};

// 0x71000100ec
float get_100ec(Field100ec* object) {
    return object->value;
}

struct Field100f4 {
    unsigned char pad[0x40];
    float value;  // +40
};

// 0x71000100f4
float get_100f4(Field100f4* object) {
    return object->value;
}

struct Field100fc {
    unsigned char pad[0x44];
    float value;  // +44
};

// 0x71000100fc
float get_100fc(Field100fc* object) {
    return object->value;
}

struct Field363e4 {
    unsigned char pad[0x30];
    long value;  // +30
};

// 0x71000363e4
void set_363e4(Field363e4* object, long value) {
    object->value = value;
}

struct Field36738 {
    unsigned char pad[0xb0];
    int value;  // +b0
};

// 0x7100036738
void set_36738(Field36738* object, int value) {
    object->value = value;
}

struct Field36764 {
    unsigned char pad[0xe0];
    int value;  // +e0
};

// 0x7100036764
void set_36764(Field36764* object, int value) {
    object->value = value;
}

// 0x710003df9c
int constant_3df9c() {
    return 1;
}

// 0x7100042d38
int zero_42d38() {
    return 0;
}

// 0x7100043d24
int constant_43d24() {
    return 1;
}

struct Field46404 {
    int value;  // +0
};

// 0x7100046404
void clear_46404(Field46404* object) {
    object->value = 0;
}

struct Field46440 {
    long value;  // +0
};

// 0x7100046440
void clear_46440(Field46440* object) {
    object->value = 0;
}

struct Field46480 {
    long value;  // +0
};

// 0x7100046480
void clear_46480(Field46480* object) {
    object->value = 0;
}

struct Field46bfc {
    unsigned char pad[0x1f40];
    long value;  // +1f40
};

// 0x7100046bfc
void clear_46bfc(Field46bfc* object) {
    object->value = 0;
}

struct Field4a9d0 {
    unsigned char pad[0x50];
    long value;  // +50
};

// 0x710004a9d0
void clear_4a9d0(Field4a9d0* object) {
    object->value = 0;
}

struct Block4ca10 {
    unsigned char data[0x80];
};

// 0x710004ca10
void clear_block_4ca10(Block4ca10* block) {
    memset(block, 0, sizeof(Block4ca10));
}

struct Block4ca98 {
    unsigned char data[0x110];
};

// 0x710004ca98
void clear_block_4ca98(Block4ca98* block) {
    memset(block, 0, sizeof(Block4ca98));
}

struct Block4d35c {
    unsigned char data[0x190];
};

// 0x710004d35c
void clear_block_4d35c(Block4d35c* block) {
    memset(block, 0, sizeof(Block4d35c));
}

struct Field4d954 {
    unsigned char pad[0x8];
    long value;  // +8
};

// 0x710004d954
void clear_4d954(Field4d954* object) {
    object->value = 0;
}

struct Field4d95c {
    unsigned char pad[0x10];
    int value;  // +10
};

// 0x710004d95c
void clear_4d95c(Field4d95c* object) {
    object->value = 0;
}

struct Block4d9bc {
    unsigned char data[0xb0];
};

// 0x710004d9bc
void clear_block_4d9bc(Block4d9bc* block) {
    memset(block, 0, sizeof(Block4d9bc));
}

struct Field4db94 {
    int value;  // +0
};

// 0x710004db94
void clear_4db94(Field4db94* object) {
    object->value = 0;
}

void handle_51070(void* object);                                      // 0x7100051070
struct Forward4dc14 {
    unsigned char pad[0x20];
    void* child;  // +20
};

// 0x710004dc14
void forward_child_4dc14(Forward4dc14* object) {
    handle_51070(object->child);
}

void handle_50c54(void* object);                                      // 0x7100050c54
struct Forward4dc28 {
    unsigned char pad[0x20];
    void* child;  // +20
};

// 0x710004dc28
void forward_child_4dc28(Forward4dc28* object) {
    handle_50c54(object->child);
}

void handle_50cf8(void* object);                                      // 0x7100050cf8
struct Forward4dc30 {
    unsigned char pad[0x20];
    void* child;  // +20
};

// 0x710004dc30
void forward_child_4dc30(Forward4dc30* object) {
    handle_50cf8(object->child);
}

void handle_4c334(void* object);                                      // 0x710004c334
struct Forward51ea8 {
    unsigned char pad[0x20];
    unsigned char part[1];  // +20
};

// 0x7100051ea8
void forward_part_51ea8(Forward51ea8* object) {
    handle_4c334(object->part);
}

class Virtual5270c {
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
    virtual void v60();
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void v80();
    virtual void call();  // +88
};

// 0x710005270c
void vcall_5270c(Virtual5270c* object) {
    object->call();
}

class Virtual52758 {
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
    virtual void v60();
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void v80();
    virtual void v88();
    virtual void v90();
    virtual void v98();
    virtual void call();  // +a0
};

// 0x7100052758
void vcall_52758(Virtual52758* object) {
    object->call();
}

class Virtual52764 {
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
    virtual void v60();
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void v80();
    virtual void v88();
    virtual void v90();
    virtual void v98();
    virtual void va0();
    virtual void call();  // +a8
};

// 0x7100052764
void vcall_52764(Virtual52764* object) {
    object->call();
}

class Virtual52770 {
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
    virtual void v60();
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void v80();
    virtual void v88();
    virtual void v90();
    virtual void v98();
    virtual void va0();
    virtual void va8();
    virtual void call();  // +b0
};

// 0x7100052770
void vcall_52770(Virtual52770* object) {
    object->call();
}

class Virtual5277c {
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
    virtual void v60();
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void v80();
    virtual void v88();
    virtual void v90();
    virtual void v98();
    virtual void va0();
    virtual void va8();
    virtual void vb0();
    virtual void call();  // +b8
};

// 0x710005277c
void vcall_5277c(Virtual5277c* object) {
    object->call();
}

class Virtual52788 {
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
    virtual void v60();
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void v80();
    virtual void v88();
    virtual void v90();
    virtual void v98();
    virtual void va0();
    virtual void va8();
    virtual void vb0();
    virtual void vb8();
    virtual void call();  // +c0
};

// 0x7100052788
void vcall_52788(Virtual52788* object) {
    object->call();
}

class Virtual52794 {
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
    virtual void v60();
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void v80();
    virtual void v88();
    virtual void v90();
    virtual void v98();
    virtual void va0();
    virtual void va8();
    virtual void vb0();
    virtual void vb8();
    virtual void vc0();
    virtual void call();  // +c8
};

// 0x7100052794
void vcall_52794(Virtual52794* object) {
    object->call();
}

void handle_35420(void* object);                                      // 0x7100035420
struct Forward527d0 {
    unsigned char pad[0x10];
    void* child;  // +10
};

// 0x71000527d0
void forward_child_527d0(Forward527d0* object) {
    handle_35420(object->child);
}

struct Field5fcb0 {
    unsigned char pad[0x2664];
    int value;  // +2664
};

// 0x710005fcb0
void set_constant_5fcb0(Field5fcb0* object) {
    object->value = 1;
}

struct Field6abc4 {
    unsigned char pad[0x4];
    unsigned short value;  // +4
};

// 0x710006abc4
void set_6abc4(Field6abc4* object, unsigned short value) {
    object->value = value;
}

struct Field6d38c {
    long value;  // +0
};

// 0x710006d38c
void set_6d38c(Field6d38c* object, long value) {
    object->value = value;
}

void handle_75fd8(void* object);                                      // 0x7100075fd8
struct Forward6d818 {
    unsigned char pad[0x108];
    unsigned char part[1];  // +108
};

// 0x710006d818
void forward_part_6d818(Forward6d818* object) {
    handle_75fd8(object->part);
}

// 0x710006f32c
int constant_6f32c() {
    return -1;
}

// 0x710006f554
int constant_6f554() {
    return -1;
}

// 0x710006f7b4
int zero_6f7b4() {
    return 0;
}

struct Field74c0c {
    unsigned char pad[0x40];
    int value;  // +40
};

// 0x7100074c0c
int get_74c0c(Field74c0c* object) {
    return object->value;
}

struct Field7a1f4 {
    unsigned char pad[0x38];
    float value;  // +38
};

// 0x710007a1f4
float get_7a1f4(Field7a1f4* object) {
    return object->value;
}

struct Field85914 {
    unsigned char pad[0x4e0];
    float value;  // +4e0
};

// 0x7100085914
float get_85914(Field85914* object) {
    return object->value;
}

struct Field86b5c {
    unsigned char pad[0x164];
    int value;  // +164
};

// 0x7100086b5c
void clear_86b5c(Field86b5c* object) {
    object->value = 0;
}

struct Holder99724 {
    unsigned char pad[0x250];
    unsigned char member[1];  // +250
};

// 0x7100099724
void* member_99724(Holder99724* object) {
    return object->member;
}

struct Holder9972c {
    unsigned char pad[0x260];
    unsigned char member[1];  // +260
};

// 0x710009972c
void* member_9972c(Holder9972c* object) {
    return object->member;
}

// 0x7100099788
int constant_99788() {
    return 1;
}

class Virtual9ce10 {
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
    virtual void v60();
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void v80();
    virtual void v88();
    virtual void v90();
    virtual void v98();
    virtual void va0();
    virtual void va8();
    virtual void vb0();
    virtual void vb8();
    virtual void vc0();
    virtual void vc8();
    virtual void vd0();
    virtual void vd8();
    virtual void ve0();
    virtual void ve8();
    virtual void vf0();
    virtual void vf8();
    virtual void v100();
    virtual void v108();
    virtual void v110();
    virtual void call();  // +118
};

// 0x710009ce10
void vcall_9ce10(Virtual9ce10* object) {
    object->call();
}

struct Fieldaab78 {
    unsigned char pad[0x10];
    int value;  // +10
};

// 0x71000aab78
void clear_aab78(Fieldaab78* object) {
    object->value = 0;
}

struct Fieldb70dc {
    unsigned char pad[0x3];
    unsigned char value;  // +3
};

// 0x71000b70dc
void clear_b70dc(Fieldb70dc* object) {
    object->value = 0;
}

class Virtualb7298 {
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
    virtual void v60();
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void v80();
    virtual void v88();
    virtual void v90();
    virtual void v98();
    virtual void va0();
    virtual void va8();
    virtual void vb0();
    virtual void vb8();
    virtual void vc0();
    virtual void vc8();
    virtual void call();  // +d0
};

// 0x71000b7298
void vcall_b7298(Virtualb7298* object) {
    object->call();
}

struct Fieldba4d8 {
    unsigned char pad[0x18];
    long value;  // +18
};

// 0x71000ba4d8
long get_ba4d8(Fieldba4d8* object) {
    return object->value;
}

struct Fieldba588 {
    unsigned char pad[0x30];
    int value;  // +30
};

// 0x71000ba588
void clear_ba588(Fieldba588* object) {
    object->value = 0;
}

struct Fieldc65f8 {
    unsigned char pad[0x70];
    long value;  // +70
};

// 0x71000c65f8
void set_c65f8(Fieldc65f8* object, long value) {
    object->value = value;
}

struct Fieldc660c {
    unsigned char pad[0x78];
    float value;  // +78
};

// 0x71000c660c
float get_c660c(Fieldc660c* object) {
    return object->value;
}

struct Fieldcdb3c {
    long value;  // +0
};

// 0x71000cdb3c
void clear_cdb3c(Fieldcdb3c* object) {
    object->value = 0;
}

struct Fieldcdd28 {
    unsigned char pad[0x18];
    int value;  // +18
};

// 0x71000cdd28
int get_cdd28(Fieldcdd28* object) {
    return object->value;
}

struct Fieldcf594 {
    unsigned char pad[0x8];
    int value;  // +8
};

// 0x71000cf594
void set_constant_cf594(Fieldcf594* object) {
    object->value = -1;
}

struct Fieldcf9b0 {
    unsigned char pad[0x8];
    unsigned char value;  // +8
};

// 0x71000cf9b0
unsigned char get_cf9b0(Fieldcf9b0* object) {
    return object->value;
}

class Virtualcff58 {
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
    virtual void call();  // +58
};

// 0x71000cff58
void vcall_cff58(Virtualcff58* object) {
    object->call();
}

struct Fieldd046c {
    unsigned char pad[0x8];
    unsigned char value;  // +8
};

// 0x71000d046c
void clear_d046c(Fieldd046c* object) {
    object->value = 0;
}

struct Fieldd04bc {
    unsigned char pad[0x8];
    long value;  // +8
};

// 0x71000d04bc
void clear_d04bc(Fieldd04bc* object) {
    object->value = 0;
}

struct Fieldd3440 {
    unsigned char pad[0x8];
    long value;  // +8
};

// 0x71000d3440
void clear_d3440(Fieldd3440* object) {
    object->value = 0;
}

struct Fieldd345c {
    unsigned char pad[0xc];
    int value;  // +c
};

// 0x71000d345c
void clear_d345c(Fieldd345c* object) {
    object->value = 0;
}

struct Blockd86b8 {
    unsigned char data[0x870];
};

// 0x71000d86b8
void clear_block_d86b8(Blockd86b8* block) {
    memset(block, 0, sizeof(Blockd86b8));
}

// 0x71000dc550
int zero_dc550() {
    return 0;
}

struct Fielddd8a0 {
    unsigned char pad[0x90];
    int value;  // +90
};

// 0x71000dd8a0
void clear_dd8a0(Fielddd8a0* object) {
    object->value = 0;
}

void handle_5d27b4(void* object);                                     // 0x71005d27b4
struct Forwarde062c {
    unsigned char pad[0x30];
    unsigned char part[1];  // +30
};

// 0x71000e062c
void forward_part_e062c(Forwarde062c* object) {
    handle_5d27b4(object->part);
}

struct Holderfed9c {
    unsigned char pad[0xdc];
    unsigned char member[1];  // +dc
};

// 0x71000fed9c
void* member_fed9c(Holderfed9c* object) {
    return object->member;
}

struct Fieldff8f0 {
    unsigned char pad[0x18];
    long value;  // +18
};

// 0x71000ff8f0
long get_ff8f0(Fieldff8f0* object) {
    return object->value;
}

struct Fieldff8f8 {
    unsigned char pad[0x20];
    long value;  // +20
};

// 0x71000ff8f8
long get_ff8f8(Fieldff8f8* object) {
    return object->value;
}

struct Holderffb5c {
    unsigned char pad[0xd8];
    unsigned char member[1];  // +d8
};

// 0x71000ffb5c
void* member_ffb5c(Holderffb5c* object) {
    return object->member;
}

struct Holderffbac {
    unsigned char pad[0x776];
    unsigned char member[1];  // +776
};

// 0x71000ffbac
void* member_ffbac(Holderffbac* object) {
    return object->member;
}

struct Field113a54 {
    unsigned char pad[0x1a38];
    int value;  // +1a38
};

// 0x7100113a54
void set_constant_113a54(Field113a54* object) {
    object->value = 2;
}

struct Field1179e8 {
    unsigned char pad[0x8];
    int value;  // +8
};

// 0x71001179e8
int get_1179e8(Field1179e8* object) {
    return object->value;
}

struct Field12f560 {
    unsigned char pad[0xc];
    int value;  // +c
};

// 0x710012f560
int get_12f560(Field12f560* object) {
    return object->value;
}

struct Field135df0 {
    unsigned char pad[0x100];
    unsigned char value;  // +100
};

// 0x7100135df0
void set_135df0(Field135df0* object, unsigned char value) {
    object->value = value;
}

struct Field135df8 {
    unsigned char pad[0x101];
    unsigned char value;  // +101
};

// 0x7100135df8
void set_135df8(Field135df8* object, unsigned char value) {
    object->value = value;
}

// 0x710013cec0
int zero_13cec0() {
    return 0;
}

// 0x710013d0a0
int constant_13d0a0() {
    return 246;
}

struct Block14974c {
    unsigned char data[0x2000];
};

// 0x710014974c
void clear_block_14974c(Block14974c* block) {
    memset(block, 0, sizeof(Block14974c));
}

struct Field14a5c0 {
    unsigned char pad[0x30];
    unsigned char value;  // +30
};

// 0x710014a5c0
unsigned char get_14a5c0(Field14a5c0* object) {
    return object->value;
}

struct Field14a5c8 {
    unsigned char pad[0x10];
    int value;  // +10
};

// 0x710014a5c8
int get_14a5c8(Field14a5c8* object) {
    return object->value;
}

struct Field14a5d0 {
    unsigned char pad[0x10];
    int value;  // +10
};

// 0x710014a5d0
void set_14a5d0(Field14a5d0* object, int value) {
    object->value = value;
}

struct Field14a5d8 {
    unsigned char pad[0x14];
    int value;  // +14
};

// 0x710014a5d8
int get_14a5d8(Field14a5d8* object) {
    return object->value;
}

struct Field14a5e0 {
    unsigned char pad[0x14];
    int value;  // +14
};

// 0x710014a5e0
void set_14a5e0(Field14a5e0* object, int value) {
    object->value = value;
}

struct Field14a5e8 {
    unsigned char pad[0x18];
    int value;  // +18
};

// 0x710014a5e8
int get_14a5e8(Field14a5e8* object) {
    return object->value;
}

struct Field14a5f0 {
    unsigned char pad[0x18];
    int value;  // +18
};

// 0x710014a5f0
void set_14a5f0(Field14a5f0* object, int value) {
    object->value = value;
}

struct Field14a5f8 {
    unsigned char pad[0x1c];
    int value;  // +1c
};

// 0x710014a5f8
int get_14a5f8(Field14a5f8* object) {
    return object->value;
}

struct Field14a600 {
    unsigned char pad[0x1c];
    int value;  // +1c
};

// 0x710014a600
void set_14a600(Field14a600* object, int value) {
    object->value = value;
}

struct Field14a608 {
    unsigned char pad[0x31];
    unsigned char value;  // +31
};

// 0x710014a608
unsigned char get_14a608(Field14a608* object) {
    return object->value;
}

struct Field14a610 {
    unsigned char pad[0x31];
    unsigned char value;  // +31
};

// 0x710014a610
void set_14a610(Field14a610* object, unsigned char value) {
    object->value = value;
}

struct Field14a630 {
    unsigned char pad[0x32];
    unsigned char value;  // +32
};

// 0x710014a630
unsigned char get_14a630(Field14a630* object) {
    return object->value;
}

struct Field14a638 {
    unsigned char pad[0x32];
    unsigned char value;  // +32
};

// 0x710014a638
void set_14a638(Field14a638* object, unsigned char value) {
    object->value = value;
}

struct Field14a640 {
    unsigned char pad[0x34];
    float value;  // +34
};

// 0x710014a640
float get_14a640(Field14a640* object) {
    return object->value;
}

struct Field14a690 {
    unsigned char pad[0x20];
    int value;  // +20
};

// 0x710014a690
int get_14a690(Field14a690* object) {
    return object->value;
}

struct Field14a698 {
    unsigned char pad[0x20];
    int value;  // +20
};

// 0x710014a698
void set_14a698(Field14a698* object, int value) {
    object->value = value;
}

struct Field14a6a0 {
    unsigned char pad[0x24];
    int value;  // +24
};

// 0x710014a6a0
int get_14a6a0(Field14a6a0* object) {
    return object->value;
}

struct Field14a6a8 {
    unsigned char pad[0x24];
    int value;  // +24
};

// 0x710014a6a8
void set_14a6a8(Field14a6a8* object, int value) {
    object->value = value;
}

struct Field14a6b0 {
    unsigned char pad[0x28];
    int value;  // +28
};

// 0x710014a6b0
int get_14a6b0(Field14a6b0* object) {
    return object->value;
}

struct Field14a6b8 {
    unsigned char pad[0x28];
    int value;  // +28
};

// 0x710014a6b8
void set_14a6b8(Field14a6b8* object, int value) {
    object->value = value;
}

struct Field14a6c0 {
    unsigned char pad[0x38];
    unsigned char value;  // +38
};

// 0x710014a6c0
unsigned char get_14a6c0(Field14a6c0* object) {
    return object->value;
}

struct Field14a6c8 {
    unsigned char pad[0x2c];
    int value;  // +2c
};

// 0x710014a6c8
int get_14a6c8(Field14a6c8* object) {
    return object->value;
}

struct Field14a6d0 {
    unsigned char pad[0x2c];
    int value;  // +2c
};

// 0x710014a6d0
void set_14a6d0(Field14a6d0* object, int value) {
    object->value = value;
}

struct Field14a6d8 {
    unsigned char pad[0x3c];
    int value;  // +3c
};

// 0x710014a6d8
int get_14a6d8(Field14a6d8* object) {
    return object->value;
}

struct Field14a6e0 {
    unsigned char pad[0x3c];
    int value;  // +3c
};

// 0x710014a6e0
void set_14a6e0(Field14a6e0* object, int value) {
    object->value = value;
}

struct Field14a7a0 {
    unsigned char pad[0x40];
    int value;  // +40
};

// 0x710014a7a0
int get_14a7a0(Field14a7a0* object) {
    return object->value;
}

struct Field14a7a8 {
    unsigned char pad[0x40];
    int value;  // +40
};

// 0x710014a7a8
void set_14a7a8(Field14a7a8* object, int value) {
    object->value = value;
}

struct Field14a7b0 {
    unsigned char pad[0x44];
    int value;  // +44
};

// 0x710014a7b0
int get_14a7b0(Field14a7b0* object) {
    return object->value;
}

struct Field14a7b8 {
    unsigned char pad[0x44];
    int value;  // +44
};

// 0x710014a7b8
void set_14a7b8(Field14a7b8* object, int value) {
    object->value = value;
}

struct Field14a7c0 {
    unsigned char pad[0x48];
    int value;  // +48
};

// 0x710014a7c0
int get_14a7c0(Field14a7c0* object) {
    return object->value;
}

struct Field154468 {
    unsigned char pad[0x8];
    int value;  // +8
};

// 0x7100154468
void clear_154468(Field154468* object) {
    object->value = 0;
}

struct Field154474 {
    unsigned char pad[0x8];
    int value;  // +8
};

// 0x7100154474
void clear_154474(Field154474* object) {
    object->value = 0;
}

struct Field15447c {
    unsigned char pad[0x8];
    int value;  // +8
};

// 0x710015447c
void clear_15447c(Field15447c* object) {
    object->value = 0;
}

// 0x7100157dbc
int zero_157dbc() {
    return 0;
}

struct Field157dc4 {
    long value;  // +0
};

// 0x7100157dc4
long get_157dc4(Field157dc4* object) {
    return object->value;
}

struct Field157dcc {
    unsigned char pad[0x10];
    long value;  // +10
};

// 0x7100157dcc
long get_157dcc(Field157dcc* object) {
    return object->value;
}

// 0x710015bd20
int zero_15bd20() {
    return 0;
}

// 0x710015c090
int zero_15c090() {
    return 0;
}

// 0x710015c108
int zero_15c108() {
    return 0;
}

// 0x710015c110
int constant_15c110() {
    return 1;
}

struct Field16f2bc {
    unsigned char pad[0x34];
    int value;  // +34
};

// 0x710016f2bc
void set_16f2bc(Field16f2bc* object, int value) {
    object->value = value;
}

struct Field16f638 {
    unsigned char pad[0x20];
    int value;  // +20
};

// 0x710016f638
int get_16f638(Field16f638* object) {
    return object->value;
}

struct Field16f640 {
    unsigned char pad[0x24];
    int value;  // +24
};

// 0x710016f640
int get_16f640(Field16f640* object) {
    return object->value;
}

struct Field16f648 {
    unsigned char pad[0x30];
    int value;  // +30
};

// 0x710016f648
int get_16f648(Field16f648* object) {
    return object->value;
}

struct Field16f650 {
    unsigned char pad[0x28];
    int value;  // +28
};

// 0x710016f650
int get_16f650(Field16f650* object) {
    return object->value;
}

struct Field16f658 {
    unsigned char pad[0x34];
    int value;  // +34
};

// 0x710016f658
int get_16f658(Field16f658* object) {
    return object->value;
}

struct Field16f660 {
    unsigned char pad[0x38];
    int value;  // +38
};

// 0x710016f660
int get_16f660(Field16f660* object) {
    return object->value;
}

struct Field16f6a8 {
    unsigned char pad[0x40];
    int value;  // +40
};

// 0x710016f6a8
int get_16f6a8(Field16f6a8* object) {
    return object->value;
}

struct Field16f6b0 {
    unsigned char pad[0x40];
    int value;  // +40
};

// 0x710016f6b0
void set_16f6b0(Field16f6b0* object, int value) {
    object->value = value;
}

struct Field16f6b8 {
    unsigned char pad[0x44];
    int value;  // +44
};

// 0x710016f6b8
int get_16f6b8(Field16f6b8* object) {
    return object->value;
}

// 0x7100172158
int constant_172158() {
    return 210;
}

// 0x710017c68c
int zero_17c68c() {
    return 0;
}

// 0x7100181cac
int constant_181cac() {
    return 1;
}

struct Field184d10 {
    unsigned char pad[0x10];
    unsigned short value;  // +10
};

// 0x7100184d10
void set_184d10(Field184d10* object, unsigned short value) {
    object->value = value;
}

struct Field184dd0 {
    unsigned char pad[0x14];
    unsigned short value;  // +14
};

// 0x7100184dd0
void set_184dd0(Field184dd0* object, unsigned short value) {
    object->value = value;
}

struct Field187ca0 {
    unsigned char pad[0x14];
    int value;  // +14
};

// 0x7100187ca0
int get_187ca0(Field187ca0* object) {
    return object->value;
}

struct Field187d70 {
    unsigned char pad[0x4dc];
    int value;  // +4dc
};

// 0x7100187d70
int get_187d70(Field187d70* object) {
    return object->value;
}

struct Field1923b8 {
    unsigned char pad[0xa4];
    int value;  // +a4
};

// 0x71001923b8
void set_constant_1923b8(Field1923b8* object) {
    object->value = -1;
}

struct Field193438 {
    unsigned char value;  // +0
};

// 0x7100193438
unsigned char get_193438(Field193438* object) {
    return object->value;
}

struct Field193440 {
    unsigned char value;  // +0
};

// 0x7100193440
void set_193440(Field193440* object, unsigned char value) {
    object->value = value;
}

struct Field193448 {
    unsigned char pad[0x1];
    signed char value;  // +1
};

// 0x7100193448
int get_193448(Field193448* object) {
    return object->value;
}

struct Field193470 {
    unsigned char pad[0x2];
    unsigned char value;  // +2
};

// 0x7100193470
unsigned char get_193470(Field193470* object) {
    return object->value;
}

struct Field193478 {
    unsigned char pad[0x2];
    unsigned char value;  // +2
};

// 0x7100193478
void set_193478(Field193478* object, unsigned char value) {
    object->value = value;
}

struct Field193480 {
    unsigned char pad[0x3];
    unsigned char value;  // +3
};

// 0x7100193480
unsigned char get_193480(Field193480* object) {
    return object->value;
}

struct Field193488 {
    unsigned char pad[0x3];
    unsigned char value;  // +3
};

// 0x7100193488
void set_193488(Field193488* object, unsigned char value) {
    object->value = value;
}

struct Field193614 {
    unsigned char pad[0x8];
    unsigned char value;  // +8
};

// 0x7100193614
void set_193614(Field193614* object, unsigned char value) {
    object->value = value;
}

struct Field19361c {
    unsigned char pad[0x9];
    unsigned char value;  // +9
};

// 0x710019361c
void set_19361c(Field19361c* object, unsigned char value) {
    object->value = value;
}

struct Field194778 {
    unsigned char pad[0x50];
    int value;  // +50
};

// 0x7100194778
void set_194778(Field194778* object, int value) {
    object->value = value;
}

struct Field1947ac {
    unsigned char pad[0x158];
    unsigned char value;  // +158
};

// 0x71001947ac
void set_1947ac(Field1947ac* object, unsigned char value) {
    object->value = value;
}

struct Field1947b4 {
    unsigned char pad[0x159];
    unsigned char value;  // +159
};

// 0x71001947b4
void set_1947b4(Field1947b4* object, unsigned char value) {
    object->value = value;
}

struct Field1949a8 {
    unsigned char pad[0x108];
    int value;  // +108
};

// 0x71001949a8
void set_1949a8(Field1949a8* object, int value) {
    object->value = value;
}

struct Field1949b0 {
    unsigned char pad[0x10c];
    unsigned char value;  // +10c
};

// 0x71001949b0
void set_1949b0(Field1949b0* object, unsigned char value) {
    object->value = value;
}

struct Field195918 {
    unsigned char pad[0x2e4];
    float value;  // +2e4
};

// 0x7100195918
void set_195918(Field195918* object, float value) {
    object->value = value;
}

struct Field19646c {
    unsigned char pad[0x5];
    unsigned char value;  // +5
};

// 0x710019646c
void set_19646c(Field19646c* object, unsigned char value) {
    object->value = value;
}

struct Field1968d0 {
    unsigned char value;  // +0
};

// 0x71001968d0
unsigned char get_1968d0(Field1968d0* object) {
    return object->value;
}

struct Field1968d8 {
    unsigned char value;  // +0
};

// 0x71001968d8
void set_1968d8(Field1968d8* object, unsigned char value) {
    object->value = value;
}

struct Holder196928 {
    unsigned char pad[0x10];
    unsigned char member[1];  // +10
};

// 0x7100196928
void* member_196928(Holder196928* object) {
    return object->member;
}

struct Field196930 {
    unsigned char pad[0x8];
    int value;  // +8
};

// 0x7100196930
void set_196930(Field196930* object, int value) {
    object->value = value;
}

struct Field196938 {
    unsigned char pad[0x8];
    int value;  // +8
};

// 0x7100196938
int get_196938(Field196938* object) {
    return object->value;
}

struct Field196940 {
    unsigned char pad[0x4];
    int value;  // +4
};

// 0x7100196940
void set_196940(Field196940* object, int value) {
    object->value = value;
}

struct Field197a98 {
    unsigned char pad[0x82];
    unsigned short value;  // +82
};

// 0x7100197a98
void set_197a98(Field197a98* object, unsigned short value) {
    object->value = value;
}

struct Field198c80 {
    unsigned char pad[0x34];
    int value;  // +34
};

// 0x7100198c80
void set_198c80(Field198c80* object, int value) {
    object->value = value;
}

struct Field19b520 {
    unsigned char value;  // +0
};

// 0x710019b520
unsigned char get_19b520(Field19b520* object) {
    return object->value;
}

struct Field19b528 {
    unsigned char pad[0x1];
    unsigned char value;  // +1
};

// 0x710019b528
unsigned char get_19b528(Field19b528* object) {
    return object->value;
}

struct Field19b530 {
    unsigned char pad[0x1];
    unsigned char value;  // +1
};

// 0x710019b530
void set_19b530(Field19b530* object, unsigned char value) {
    object->value = value;
}

struct Field19b6b8 {
    unsigned char pad[0x20];
    int value;  // +20
};

// 0x710019b6b8
int get_19b6b8(Field19b6b8* object) {
    return object->value;
}

struct Field19ba54 {
    unsigned char pad[0x4c];
    int value;  // +4c
};

// 0x710019ba54
int get_19ba54(Field19ba54* object) {
    return object->value;
}

struct Field19ba78 {
    int value;  // +0
};

// 0x710019ba78
void set_19ba78(Field19ba78* object, int value) {
    object->value = value;
}

struct Field19ba80 {
    unsigned char pad[0x8];
    int value;  // +8
};

// 0x710019ba80
void set_19ba80(Field19ba80* object, int value) {
    object->value = value;
}

struct Field19ba88 {
    unsigned char pad[0xc];
    int value;  // +c
};

// 0x710019ba88
void set_19ba88(Field19ba88* object, int value) {
    object->value = value;
}

struct Field19bd0c {
    int value;  // +0
};

// 0x710019bd0c
void set_19bd0c(Field19bd0c* object, int value) {
    object->value = value;
}

struct Field19bd28 {
    unsigned char pad[0x4];
    int value;  // +4
};

// 0x710019bd28
int get_19bd28(Field19bd28* object) {
    return object->value;
}

struct Field19bd30 {
    unsigned char pad[0x8];
    int value;  // +8
};

// 0x710019bd30
int get_19bd30(Field19bd30* object) {
    return object->value;
}

// 0x710019be04
int constant_19be04() {
    return 3;
}

struct Field19d254 {
    unsigned char pad[0xc];
    unsigned char value;  // +c
};

// 0x710019d254
unsigned char get_19d254(Field19d254* object) {
    return object->value;
}

struct Field19d25c {
    unsigned char pad[0xd];
    unsigned char value;  // +d
};

// 0x710019d25c
unsigned char get_19d25c(Field19d25c* object) {
    return object->value;
}

struct Field19d74c {
    unsigned char pad[0xe];
    unsigned char value;  // +e
};

// 0x710019d74c
void set_19d74c(Field19d74c* object, unsigned char value) {
    object->value = value;
}

struct Field1a38ec {
    int value;  // +0
};

// 0x71001a38ec
int get_1a38ec(Field1a38ec* object) {
    return object->value;
}

struct Field1a3900 {
    unsigned char pad[0x4];
    int value;  // +4
};

// 0x71001a3900
int get_1a3900(Field1a3900* object) {
    return object->value;
}

struct Field1a3908 {
    unsigned char pad[0x9];
    unsigned char value;  // +9
};

// 0x71001a3908
unsigned char get_1a3908(Field1a3908* object) {
    return object->value;
}

struct Field1a3910 {
    unsigned char pad[0xc];
    int value;  // +c
};

// 0x71001a3910
int get_1a3910(Field1a3910* object) {
    return object->value;
}

struct Field1a3918 {
    unsigned char pad[0x10];
    int value;  // +10
};

// 0x71001a3918
int get_1a3918(Field1a3918* object) {
    return object->value;
}

struct Field1a7650 {
    unsigned char pad[0x19d0];
    int value;  // +19d0
};

// 0x71001a7650
void set_1a7650(Field1a7650* object, int value) {
    object->value = value;
}

struct Field1a7658 {
    unsigned char pad[0x19dc];
    int value;  // +19dc
};

// 0x71001a7658
void set_1a7658(Field1a7658* object, int value) {
    object->value = value;
}

struct Field1a7660 {
    unsigned char pad[0x19e0];
    int value;  // +19e0
};

// 0x71001a7660
void set_1a7660(Field1a7660* object, int value) {
    object->value = value;
}

struct Field1a7668 {
    unsigned char pad[0x19e4];
    int value;  // +19e4
};

// 0x71001a7668
int get_1a7668(Field1a7668* object) {
    return object->value;
}

struct Field1a76a0 {
    unsigned char pad[0x19e8];
    int value;  // +19e8
};

// 0x71001a76a0
void set_1a76a0(Field1a76a0* object, int value) {
    object->value = value;
}

struct Field1a76a8 {
    unsigned char pad[0x19e8];
    int value;  // +19e8
};

// 0x71001a76a8
int get_1a76a8(Field1a76a8* object) {
    return object->value;
}

// 0x71001a76d0
int zero_1a76d0() {
    return 0;
}

struct Field1a7e9c {
    unsigned char pad[0x19f0];
    long value;  // +19f0
};

// 0x71001a7e9c
long get_1a7e9c(Field1a7e9c* object) {
    return object->value;
}

struct Field1a8498 {
    unsigned char pad[0x4];
    int value;  // +4
};

// 0x71001a8498
void set_1a8498(Field1a8498* object, int value) {
    object->value = value;
}

struct Field1a8cfc {
    int value;  // +0
};

// 0x71001a8cfc
int get_1a8cfc(Field1a8cfc* object) {
    return object->value;
}

struct Field1a8d04 {
    int value;  // +0
};

// 0x71001a8d04
void set_1a8d04(Field1a8d04* object, int value) {
    object->value = value;
}

struct Field1a8d0c {
    unsigned char pad[0x8];
    int value;  // +8
};

// 0x71001a8d0c
int get_1a8d0c(Field1a8d0c* object) {
    return object->value;
}

struct Field1a8d14 {
    unsigned char pad[0x8];
    int value;  // +8
};

// 0x71001a8d14
void set_1a8d14(Field1a8d14* object, int value) {
    object->value = value;
}

struct Field1a8d1c {
    unsigned char pad[0xc];
    int value;  // +c
};

// 0x71001a8d1c
int get_1a8d1c(Field1a8d1c* object) {
    return object->value;
}

struct Field1a8d24 {
    unsigned char pad[0xc];
    int value;  // +c
};

// 0x71001a8d24
void set_1a8d24(Field1a8d24* object, int value) {
    object->value = value;
}

struct Field1a8d2c {
    unsigned char pad[0x10];
    int value;  // +10
};

// 0x71001a8d2c
int get_1a8d2c(Field1a8d2c* object) {
    return object->value;
}

struct Field1a8d34 {
    unsigned char pad[0x10];
    int value;  // +10
};

// 0x71001a8d34
void set_1a8d34(Field1a8d34* object, int value) {
    object->value = value;
}

struct Field1a8d7c {
    unsigned char pad[0x24];
    int value;  // +24
};

// 0x71001a8d7c
int get_1a8d7c(Field1a8d7c* object) {
    return object->value;
}

struct Field1a8d84 {
    unsigned char pad[0x24];
    int value;  // +24
};

// 0x71001a8d84
void set_1a8d84(Field1a8d84* object, int value) {
    object->value = value;
}

struct Field1a8d8c {
    unsigned char pad[0x28];
    int value;  // +28
};

// 0x71001a8d8c
int get_1a8d8c(Field1a8d8c* object) {
    return object->value;
}

struct Field1a8d94 {
    unsigned char pad[0x28];
    int value;  // +28
};

// 0x71001a8d94
void set_1a8d94(Field1a8d94* object, int value) {
    object->value = value;
}

struct Field1a8d9c {
    unsigned char pad[0x2c];
    int value;  // +2c
};

// 0x71001a8d9c
int get_1a8d9c(Field1a8d9c* object) {
    return object->value;
}

struct Field1a8da4 {
    unsigned char pad[0x2c];
    int value;  // +2c
};

// 0x71001a8da4
int get_1a8da4(Field1a8da4* object) {
    return object->value;
}

struct Field1a8dac {
    unsigned char pad[0x2c];
    int value;  // +2c
};

// 0x71001a8dac
void set_1a8dac(Field1a8dac* object, int value) {
    object->value = value;
}

struct Field1a8db4 {
    unsigned char pad[0x2c];
    int value;  // +2c
};

// 0x71001a8db4
void set_1a8db4(Field1a8db4* object, int value) {
    object->value = value;
}

struct Field1a8dbc {
    unsigned char pad[0x30];
    int value;  // +30
};

// 0x71001a8dbc
int get_1a8dbc(Field1a8dbc* object) {
    return object->value;
}

struct Field1a8dc4 {
    unsigned char pad[0x30];
    int value;  // +30
};

// 0x71001a8dc4
void set_1a8dc4(Field1a8dc4* object, int value) {
    object->value = value;
}

struct Field1a8dcc {
    unsigned char pad[0x34];
    int value;  // +34
};

// 0x71001a8dcc
int get_1a8dcc(Field1a8dcc* object) {
    return object->value;
}

struct Field1a8dd4 {
    unsigned char pad[0x34];
    int value;  // +34
};

// 0x71001a8dd4
void set_1a8dd4(Field1a8dd4* object, int value) {
    object->value = value;
}

struct Field1a8ddc {
    unsigned char pad[0x38];
    int value;  // +38
};

// 0x71001a8ddc
int get_1a8ddc(Field1a8ddc* object) {
    return object->value;
}

struct Field1a8de4 {
    unsigned char pad[0x38];
    int value;  // +38
};

// 0x71001a8de4
void set_1a8de4(Field1a8de4* object, int value) {
    object->value = value;
}

struct Field1a8dec {
    unsigned char pad[0x3c];
    int value;  // +3c
};

// 0x71001a8dec
int get_1a8dec(Field1a8dec* object) {
    return object->value;
}

struct Field1a8df4 {
    unsigned char pad[0x3c];
    int value;  // +3c
};

// 0x71001a8df4
void set_1a8df4(Field1a8df4* object, int value) {
    object->value = value;
}

struct Field1a8dfc {
    unsigned char pad[0x40];
    int value;  // +40
};

// 0x71001a8dfc
int get_1a8dfc(Field1a8dfc* object) {
    return object->value;
}

struct Field1a8e04 {
    unsigned char pad[0xc3];
    unsigned char value;  // +c3
};

// 0x71001a8e04
void set_1a8e04(Field1a8e04* object, unsigned char value) {
    object->value = value;
}

struct Field1a8e0c {
    unsigned char pad[0xc4];
    unsigned char value;  // +c4
};

// 0x71001a8e0c
unsigned char get_1a8e0c(Field1a8e0c* object) {
    return object->value;
}

struct Field1a8e14 {
    unsigned char pad[0xc4];
    unsigned char value;  // +c4
};

// 0x71001a8e14
void set_1a8e14(Field1a8e14* object, unsigned char value) {
    object->value = value;
}

struct Field1b0024 {
    unsigned char pad[0xc];
    int value;  // +c
};

// 0x71001b0024
int get_1b0024(Field1b0024* object) {
    return object->value;
}

struct Field1b002c {
    unsigned char pad[0x10];
    int value;  // +10
};

// 0x71001b002c
int get_1b002c(Field1b002c* object) {
    return object->value;
}

struct Holder1b0034 {
    unsigned char pad[0x18];
    unsigned char member[1];  // +18
};

// 0x71001b0034
void* member_1b0034(Holder1b0034* object) {
    return object->member;
}

struct Field1b0328 {
    int value;  // +0
};

// 0x71001b0328
void set_1b0328(Field1b0328* object, int value) {
    object->value = value;
}

struct Field1b24a8 {
    int value;  // +0
};

// 0x71001b24a8
void set_constant_1b24a8(Field1b24a8* object) {
    object->value = 80;
}

struct Field1b2874 {
    int value;  // +0
};

// 0x71001b2874
void set_constant_1b2874(Field1b2874* object) {
    object->value = 120;
}

struct Field1b5778 {
    int value;  // +0
};

// 0x71001b5778
void set_constant_1b5778(Field1b5778* object) {
    object->value = 360;
}

struct Field1b5794 {
    int value;  // +0
};

// 0x71001b5794
void set_constant_1b5794(Field1b5794* object) {
    object->value = 10000;
}

struct Field1b7964 {
    int value;  // +0
};

// 0x71001b7964
int get_1b7964(Field1b7964* object) {
    return object->value;
}

struct Field1b796c {
    int value;  // +0
};

// 0x71001b796c
void set_1b796c(Field1b796c* object, int value) {
    object->value = value;
}

struct Field1b86c0 {
    int value;  // +0
};

// 0x71001b86c0
void set_constant_1b86c0(Field1b86c0* object) {
    object->value = 1010;
}

struct Field1b9188 {
    int value;  // +0
};

// 0x71001b9188
void set_constant_1b9188(Field1b9188* object) {
    object->value = 60;
}

struct Field1b9b94 {
    int value;  // +0
};

// 0x71001b9b94
void set_constant_1b9b94(Field1b9b94* object) {
    object->value = 70;
}

struct Field1b9c74 {
    int value;  // +0
};

// 0x71001b9c74
void set_constant_1b9c74(Field1b9c74* object) {
    object->value = 80;
}

struct Field1b9c80 {
    unsigned char pad[0x4];
    int value;  // +4
};

// 0x71001b9c80
void set_1b9c80(Field1b9c80* object, int value) {
    object->value = value;
}

struct Field1ba2c4 {
    int value;  // +0
};

// 0x71001ba2c4
void set_constant_1ba2c4(Field1ba2c4* object) {
    object->value = 300;
}

struct Field1ba2dc {
    int value;  // +0
};

// 0x71001ba2dc
void set_constant_1ba2dc(Field1ba2dc* object) {
    object->value = 310;
}

struct Field1ba2e8 {
    unsigned char pad[0x4];
    int value;  // +4
};

// 0x71001ba2e8
void set_1ba2e8(Field1ba2e8* object, int value) {
    object->value = value;
}

struct Field1bdb88 {
    int value;  // +0
};

// 0x71001bdb88
void set_constant_1bdb88(Field1bdb88* object) {
    object->value = 1300;
}

struct Field1bde40 {
    int value;  // +0
};

// 0x71001bde40
void set_constant_1bde40(Field1bde40* object) {
    object->value = 50000;
}

struct Field1be738 {
    int value;  // +0
};

// 0x71001be738
void set_constant_1be738(Field1be738* object) {
    object->value = 50010;
}

struct Field1beb94 {
    int value;  // +0
};

// 0x71001beb94
void set_constant_1beb94(Field1beb94* object) {
    object->value = 50020;
}

struct Field1bf038 {
    int value;  // +0
};

// 0x71001bf038
void set_constant_1bf038(Field1bf038* object) {
    object->value = 50030;
}

struct Field1bf51c {
    int value;  // +0
};

// 0x71001bf51c
void set_constant_1bf51c(Field1bf51c* object) {
    object->value = 50040;
}

struct Field1bf9c4 {
    int value;  // +0
};

// 0x71001bf9c4
void set_constant_1bf9c4(Field1bf9c4* object) {
    object->value = 50070;
}

struct Field1c0cd8 {
    int value;  // +0
};

// 0x71001c0cd8
void set_constant_1c0cd8(Field1c0cd8* object) {
    object->value = 10;
}

struct Field1cc8a8 {
    long value;  // +0
};

// 0x71001cc8a8
long get_1cc8a8(Field1cc8a8* object) {
    return object->value;
}

struct Holder1ccf38 {
    unsigned char pad[0x790];
    unsigned char member[1];  // +790
};

// 0x71001ccf38
void* member_1ccf38(Holder1ccf38* object) {
    return object->member;
}

struct Field1dbd24 {
    unsigned char pad[0x52];
    unsigned short value;  // +52
};

// 0x71001dbd24
unsigned short get_1dbd24(Field1dbd24* object) {
    return object->value;
}

struct Field1e30d8 {
    unsigned char pad[0x1290];
    long value;  // +1290
};

// 0x71001e30d8
void clear_1e30d8(Field1e30d8* object) {
    object->value = 0;
}

struct Field1ef2c4 {
    int value;  // +0
};

// 0x71001ef2c4
int get_1ef2c4(Field1ef2c4* object) {
    return object->value;
}

struct Field1f2370 {
    int value;  // +0
};

// 0x71001f2370
int get_1f2370(Field1f2370* object) {
    return object->value;
}

struct Forward1f3110 {
    unsigned char pad[0x350];
    unsigned char part[1];  // +350
};

// 0x71001f3110
void forward_part_1f3110(Forward1f3110* object) {
    handle_5d27b4(object->part);
}

struct Field1f3348 {
    unsigned char pad[0x328];
    unsigned char value;  // +328
};

// 0x71001f3348
unsigned char get_1f3348(Field1f3348* object) {
    return object->value;
}

// 0x71001f7fd4
int zero_1f7fd4() {
    return 0;
}

struct Field1fe668 {
    unsigned char pad[0x6];
    unsigned short value;  // +6
};

// 0x71001fe668
unsigned short get_1fe668(Field1fe668* object) {
    return object->value;
}

struct Field1fe670 {
    unsigned char pad[0x8];
    unsigned short value;  // +8
};

// 0x71001fe670
unsigned short get_1fe670(Field1fe670* object) {
    return object->value;
}

struct Field1feb20 {
    unsigned char pad[0x14];
    int value;  // +14
};

// 0x71001feb20
int get_1feb20(Field1feb20* object) {
    return object->value;
}

struct Block1ff044 {
    unsigned char data[0x173c];
};

// 0x71001ff044
void clear_block_1ff044(Block1ff044* block) {
    memset(block, 0, sizeof(Block1ff044));
}

struct Field1ff820 {
    unsigned char pad[0x3a];
    short value;  // +3a
};

// 0x71001ff820
int get_1ff820(Field1ff820* object) {
    return object->value;
}

struct Field1ff828 {
    unsigned char pad[0x3c];
    short value;  // +3c
};

// 0x71001ff828
int get_1ff828(Field1ff828* object) {
    return object->value;
}

struct Field1ff92c {
    unsigned char pad[0x10];
    unsigned short value;  // +10
};

// 0x71001ff92c
unsigned short get_1ff92c(Field1ff92c* object) {
    return object->value;
}

struct Field1ff934 {
    unsigned char pad[0x12];
    unsigned short value;  // +12
};

// 0x71001ff934
unsigned short get_1ff934(Field1ff934* object) {
    return object->value;
}

struct Field1ff93c {
    unsigned char pad[0x1a];
    unsigned short value;  // +1a
};

// 0x71001ff93c
unsigned short get_1ff93c(Field1ff93c* object) {
    return object->value;
}

struct Field1ff944 {
    unsigned char pad[0x1c];
    unsigned short value;  // +1c
};

// 0x71001ff944
unsigned short get_1ff944(Field1ff944* object) {
    return object->value;
}

struct Field1ff9b8 {
    unsigned char pad[0x14];
    unsigned short value;  // +14
};

// 0x71001ff9b8
unsigned short get_1ff9b8(Field1ff9b8* object) {
    return object->value;
}

struct Field1ff9c0 {
    unsigned char pad[0x16];
    unsigned short value;  // +16
};

// 0x71001ff9c0
unsigned short get_1ff9c0(Field1ff9c0* object) {
    return object->value;
}

struct Field1ff9c8 {
    unsigned char pad[0x18];
    unsigned short value;  // +18
};

// 0x71001ff9c8
unsigned short get_1ff9c8(Field1ff9c8* object) {
    return object->value;
}

struct Field1ff9d0 {
    unsigned char pad[0x1e];
    unsigned short value;  // +1e
};

// 0x71001ff9d0
unsigned short get_1ff9d0(Field1ff9d0* object) {
    return object->value;
}

struct Field1ff9d8 {
    unsigned char pad[0x20];
    unsigned short value;  // +20
};

// 0x71001ff9d8
unsigned short get_1ff9d8(Field1ff9d8* object) {
    return object->value;
}

struct Field1ff9e0 {
    unsigned char pad[0x22];
    unsigned short value;  // +22
};

// 0x71001ff9e0
unsigned short get_1ff9e0(Field1ff9e0* object) {
    return object->value;
}

struct Field1ffb28 {
    unsigned char pad[0x1f];
    signed char value;  // +1f
};

// 0x71001ffb28
int get_1ffb28(Field1ffb28* object) {
    return object->value;
}

struct Field2001f8 {
    unsigned char pad[0x12];
    unsigned short value;  // +12
};

// 0x71002001f8
unsigned short get_2001f8(Field2001f8* object) {
    return object->value;
}

struct Field200210 {
    unsigned char pad[0x14];
    unsigned short value;  // +14
};

// 0x7100200210
unsigned short get_200210(Field200210* object) {
    return object->value;
}

struct Field200310 {
    unsigned char pad[0x18];
    int value;  // +18
};

// 0x7100200310
int get_200310(Field200310* object) {
    return object->value;
}

struct Field2005d4 {
    unsigned char pad[0x21];
    unsigned char value;  // +21
};

// 0x71002005d4
unsigned char get_2005d4(Field2005d4* object) {
    return object->value;
}

struct Field2005dc {
    unsigned char pad[0x21];
    unsigned char value;  // +21
};

// 0x71002005dc
void set_2005dc(Field2005dc* object, unsigned char value) {
    object->value = value;
}

struct Field2005e4 {
    unsigned char pad[0x22];
    unsigned char value;  // +22
};

// 0x71002005e4
unsigned char get_2005e4(Field2005e4* object) {
    return object->value;
}

struct Field2005ec {
    unsigned char pad[0x22];
    unsigned char value;  // +22
};

// 0x71002005ec
void set_2005ec(Field2005ec* object, unsigned char value) {
    object->value = value;
}

struct Field2005f4 {
    unsigned char pad[0x23];
    unsigned char value;  // +23
};

// 0x71002005f4
unsigned char get_2005f4(Field2005f4* object) {
    return object->value;
}

struct Field2005fc {
    unsigned char pad[0x23];
    unsigned char value;  // +23
};

// 0x71002005fc
void set_2005fc(Field2005fc* object, unsigned char value) {
    object->value = value;
}

struct Field200acc {
    int value;  // +0
};

// 0x7100200acc
int get_200acc(Field200acc* object) {
    return object->value;
}

// 0x71002013b4
int constant_2013b4() {
    return 1920;
}

struct Field2035f8 {
    unsigned char pad[0x15e];
    unsigned char value;  // +15e
};

// 0x71002035f8
unsigned char get_2035f8(Field2035f8* object) {
    return object->value;
}

struct Field203600 {
    unsigned char pad[0x15e];
    unsigned char value;  // +15e
};

// 0x7100203600
void set_203600(Field203600* object, unsigned char value) {
    object->value = value;
}

struct Field203608 {
    unsigned char pad[0x15f];
    unsigned char value;  // +15f
};

// 0x7100203608
unsigned char get_203608(Field203608* object) {
    return object->value;
}

struct Field203610 {
    unsigned char pad[0x15f];
    unsigned char value;  // +15f
};

// 0x7100203610
void set_203610(Field203610* object, unsigned char value) {
    object->value = value;
}

struct Field203c60 {
    unsigned char pad[0x160];
    unsigned char value;  // +160
};

// 0x7100203c60
unsigned char get_203c60(Field203c60* object) {
    return object->value;
}

struct Field203c78 {
    unsigned char pad[0x161];
    signed char value;  // +161
};

// 0x7100203c78
int get_203c78(Field203c78* object) {
    return object->value;
}

struct Block204c9c {
    unsigned char data[0x6ec];
};

// 0x7100204c9c
void clear_block_204c9c(Block204c9c* block) {
    memset(block, 0, sizeof(Block204c9c));
}

struct Field206098 {
    int value;  // +0
};

// 0x7100206098
int get_206098(Field206098* object) {
    return object->value;
}

struct Field206180 {
    unsigned char pad[0x15];
    unsigned char value;  // +15
};

// 0x7100206180
unsigned char get_206180(Field206180* object) {
    return object->value;
}

struct Field206188 {
    unsigned char pad[0x15];
    unsigned char value;  // +15
};

// 0x7100206188
void set_206188(Field206188* object, unsigned char value) {
    object->value = value;
}

struct Field2061fc {
    unsigned char pad[0x1b];
    unsigned char value;  // +1b
};

// 0x71002061fc
unsigned char get_2061fc(Field2061fc* object) {
    return object->value;
}

struct Field206204 {
    unsigned char pad[0x1b];
    unsigned char value;  // +1b
};

// 0x7100206204
void set_206204(Field206204* object, unsigned char value) {
    object->value = value;
}

struct Field20620c {
    unsigned char pad[0x1c];
    unsigned char value;  // +1c
};

// 0x710020620c
unsigned char get_20620c(Field20620c* object) {
    return object->value;
}

struct Field206214 {
    unsigned char pad[0x1d];
    unsigned char value;  // +1d
};

// 0x7100206214
unsigned char get_206214(Field206214* object) {
    return object->value;
}

struct Field20621c {
    unsigned char pad[0x1e];
    unsigned char value;  // +1e
};

// 0x710020621c
unsigned char get_20621c(Field20621c* object) {
    return object->value;
}

struct Field206264 {
    unsigned char pad[0x66];
    unsigned char value;  // +66
};

// 0x7100206264
unsigned char get_206264(Field206264* object) {
    return object->value;
}

struct Field2062d4 {
    unsigned char pad[0x39];
    signed char value;  // +39
};

// 0x71002062d4
int get_2062d4(Field2062d4* object) {
    return object->value;
}

struct Field2062dc {
    unsigned char pad[0x3a];
    signed char value;  // +3a
};

// 0x71002062dc
int get_2062dc(Field2062dc* object) {
    return object->value;
}

struct Field2062e4 {
    unsigned char pad[0x3b];
    signed char value;  // +3b
};

// 0x71002062e4
int get_2062e4(Field2062e4* object) {
    return object->value;
}

struct Field2062ec {
    unsigned char pad[0x3c];
    signed char value;  // +3c
};

// 0x71002062ec
int get_2062ec(Field2062ec* object) {
    return object->value;
}

struct Field2062f4 {
    unsigned char pad[0x39];
    unsigned char value;  // +39
};

// 0x71002062f4
void set_2062f4(Field2062f4* object, unsigned char value) {
    object->value = value;
}

struct Field2062fc {
    unsigned char pad[0x3a];
    unsigned char value;  // +3a
};

// 0x71002062fc
void set_2062fc(Field2062fc* object, unsigned char value) {
    object->value = value;
}

struct Field206304 {
    unsigned char pad[0x3b];
    unsigned char value;  // +3b
};

// 0x7100206304
void set_206304(Field206304* object, unsigned char value) {
    object->value = value;
}

struct Field20630c {
    unsigned char pad[0x3c];
    unsigned char value;  // +3c
};

// 0x710020630c
void set_20630c(Field20630c* object, unsigned char value) {
    object->value = value;
}

struct Field206538 {
    unsigned char pad[0x3d];
    signed char value;  // +3d
};

// 0x7100206538
int get_206538(Field206538* object) {
    return object->value;
}

struct Field206540 {
    unsigned char pad[0x3e];
    signed char value;  // +3e
};

// 0x7100206540
int get_206540(Field206540* object) {
    return object->value;
}

struct Field2065f0 {
    unsigned char pad[0x64];
    unsigned short value;  // +64
};

// 0x71002065f0
unsigned short get_2065f0(Field2065f0* object) {
    return object->value;
}

struct Field2089b8 {
    unsigned char pad[0x1];
    signed char value;  // +1
};

// 0x71002089b8
int get_2089b8(Field2089b8* object) {
    return object->value;
}

struct Field2089c0 {
    unsigned char pad[0x2];
    unsigned char value;  // +2
};

// 0x71002089c0
unsigned char get_2089c0(Field2089c0* object) {
    return object->value;
}

struct Field2089c8 {
    unsigned char pad[0x4];
    unsigned char value;  // +4
};

// 0x71002089c8
unsigned char get_2089c8(Field2089c8* object) {
    return object->value;
}

struct Field2089d0 {
    unsigned char pad[0x3];
    unsigned char value;  // +3
};

// 0x71002089d0
unsigned char get_2089d0(Field2089d0* object) {
    return object->value;
}

struct Field2089d8 {
    unsigned char pad[0x5];
    unsigned char value;  // +5
};

// 0x71002089d8
unsigned char get_2089d8(Field2089d8* object) {
    return object->value;
}

struct Field2089e0 {
    unsigned char pad[0x6];
    unsigned short value;  // +6
};

// 0x71002089e0
unsigned short get_2089e0(Field2089e0* object) {
    return object->value;
}

struct Field2089e8 {
    unsigned char pad[0x8];
    unsigned short value;  // +8
};

// 0x71002089e8
unsigned short get_2089e8(Field2089e8* object) {
    return object->value;
}

struct Field2089f0 {
    unsigned char pad[0xa];
    unsigned short value;  // +a
};

// 0x71002089f0
unsigned short get_2089f0(Field2089f0* object) {
    return object->value;
}

struct Field2089f8 {
    unsigned char pad[0xc];
    unsigned short value;  // +c
};

// 0x71002089f8
unsigned short get_2089f8(Field2089f8* object) {
    return object->value;
}

struct Field208a00 {
    unsigned char pad[0xe];
    unsigned short value;  // +e
};

// 0x7100208a00
unsigned short get_208a00(Field208a00* object) {
    return object->value;
}

struct Field208d88 {
    unsigned char pad[0x20];
    int value;  // +20
};

// 0x7100208d88
int get_208d88(Field208d88* object) {
    return object->value;
}

struct Field209bd8 {
    unsigned char pad[0x2];
    unsigned char value;  // +2
};

// 0x7100209bd8
unsigned char get_209bd8(Field209bd8* object) {
    return object->value;
}

struct Field209be0 {
    unsigned char pad[0x3];
    signed char value;  // +3
};

// 0x7100209be0
int get_209be0(Field209be0* object) {
    return object->value;
}

struct Field209be8 {
    unsigned char pad[0x4];
    unsigned char value;  // +4
};

// 0x7100209be8
unsigned char get_209be8(Field209be8* object) {
    return object->value;
}

struct Field20a0cc {
    unsigned char pad[0x6];
    short value;  // +6
};

// 0x710020a0cc
int get_20a0cc(Field20a0cc* object) {
    return object->value;
}

struct Field20a0d4 {
    unsigned char pad[0x6];
    unsigned short value;  // +6
};

// 0x710020a0d4
void set_20a0d4(Field20a0d4* object, unsigned short value) {
    object->value = value;
}

struct Field20a0f0 {
    unsigned char pad[0xa];
    short value;  // +a
};

// 0x710020a0f0
int get_20a0f0(Field20a0f0* object) {
    return object->value;
}

struct Block20aca4 {
    unsigned char data[0xcf0];
};

// 0x710020aca4
void clear_block_20aca4(Block20aca4* block) {
    memset(block, 0, sizeof(Block20aca4));
}

struct Block20b964 {
    unsigned char data[0xb40];
};

// 0x710020b964
void clear_block_20b964(Block20b964* block) {
    memset(block, 0, sizeof(Block20b964));
}

struct Field20bbfc {
    unsigned char pad[0x125];
    signed char value;  // +125
};

// 0x710020bbfc
int get_20bbfc(Field20bbfc* object) {
    return object->value;
}

// 0x710020c14c
int constant_20c14c() {
    return 660;
}

struct Field20c20c {
    unsigned char pad[0x27e];
    signed char value;  // +27e
};

// 0x710020c20c
int get_20c20c(Field20c20c* object) {
    return object->value;
}

// 0x710020c224
int constant_20c224() {
    return 1;
}

struct Field20c244 {
    unsigned char pad[0x281];
    signed char value;  // +281
};

// 0x710020c244
int get_20c244(Field20c244* object) {
    return object->value;
}

struct Field20c24c {
    unsigned char pad[0x282];
    signed char value;  // +282
};

// 0x710020c24c
int get_20c24c(Field20c24c* object) {
    return object->value;
}

struct Field20c254 {
    unsigned char pad[0x283];
    unsigned char value;  // +283
};

// 0x710020c254
unsigned char get_20c254(Field20c254* object) {
    return object->value;
}

struct Field20c270 {
    unsigned char pad[0x284];
    unsigned char value;  // +284
};

// 0x710020c270
unsigned char get_20c270(Field20c270* object) {
    return object->value;
}

struct Field20c278 {
    unsigned char pad[0x284];
    unsigned char value;  // +284
};

// 0x710020c278
void set_20c278(Field20c278* object, unsigned char value) {
    object->value = value;
}

struct Field20c55c {
    int value;  // +0
};

// 0x710020c55c
int get_20c55c(Field20c55c* object) {
    return object->value;
}

struct Field20c564 {
    unsigned char pad[0x8];
    int value;  // +8
};

// 0x710020c564
int get_20c564(Field20c564* object) {
    return object->value;
}

struct Field20c578 {
    unsigned char pad[0x2c];
    int value;  // +2c
};

// 0x710020c578
int get_20c578(Field20c578* object) {
    return object->value;
}

struct Field20c58c {
    unsigned char pad[0x18];
    int value;  // +18
};

// 0x710020c58c
int get_20c58c(Field20c58c* object) {
    return object->value;
}

struct Field20c594 {
    unsigned char pad[0x1c];
    int value;  // +1c
};

// 0x710020c594
int get_20c594(Field20c594* object) {
    return object->value;
}

struct Field20c59c {
    unsigned char pad[0x20];
    int value;  // +20
};

// 0x710020c59c
int get_20c59c(Field20c59c* object) {
    return object->value;
}

struct Field20c5a4 {
    unsigned char pad[0x24];
    unsigned char value;  // +24
};

// 0x710020c5a4
unsigned char get_20c5a4(Field20c5a4* object) {
    return object->value;
}

struct Field20c5ac {
    unsigned char pad[0x28];
    int value;  // +28
};

// 0x710020c5ac
int get_20c5ac(Field20c5ac* object) {
    return object->value;
}

struct Block20c774 {
    unsigned char data[0xc4];
};

// 0x710020c774
void clear_block_20c774(Block20c774* block) {
    memset(block, 0, sizeof(Block20c774));
}

struct Field20ca44 {
    unsigned char pad[0xa8];
    int value;  // +a8
};

// 0x710020ca44
int get_20ca44(Field20ca44* object) {
    return object->value;
}

struct Field20d91c {
    unsigned char pad[0x15];
    unsigned char value;  // +15
};

// 0x710020d91c
unsigned char get_20d91c(Field20d91c* object) {
    return object->value;
}

struct Field20d924 {
    unsigned char pad[0x26];
    short value;  // +26
};

// 0x710020d924
int get_20d924(Field20d924* object) {
    return object->value;
}

// 0x710020e21c
int constant_20e21c() {
    return 300;
}

// 0x710020eed0
int constant_20eed0() {
    return 1440;
}

struct Field20f0ac {
    unsigned char pad[0x4];
    unsigned short value;  // +4
};

// 0x710020f0ac
unsigned short get_20f0ac(Field20f0ac* object) {
    return object->value;
}

struct Field210634 {
    unsigned char pad[0x4];
    int value;  // +4
};

// 0x7100210634
int get_210634(Field210634* object) {
    return object->value;
}

struct Field21063c {
    unsigned char pad[0x8];
    int value;  // +8
};

// 0x710021063c
int get_21063c(Field21063c* object) {
    return object->value;
}

struct Field210644 {
    unsigned char pad[0xc];
    int value;  // +c
};

// 0x7100210644
int get_210644(Field210644* object) {
    return object->value;
}

struct Field21064c {
    unsigned char pad[0x10];
    int value;  // +10
};

// 0x710021064c
int get_21064c(Field21064c* object) {
    return object->value;
}

struct Field210654 {
    unsigned char pad[0x14];
    int value;  // +14
};

// 0x7100210654
int get_210654(Field210654* object) {
    return object->value;
}

struct Field21065c {
    unsigned char pad[0x18];
    int value;  // +18
};

// 0x710021065c
int get_21065c(Field21065c* object) {
    return object->value;
}

// 0x7100211284
int zero_211284() {
    return 0;
}

// 0x710021128c
int zero_21128c() {
    return 0;
}

// 0x7100211358
int zero_211358() {
    return 0;
}

// 0x7100211504
int constant_211504() {
    return -1;
}

struct Field213f28 {
    unsigned char pad[0xc];
    unsigned char value;  // +c
};

// 0x7100213f28
unsigned char get_213f28(Field213f28* object) {
    return object->value;
}

struct Field213fb4 {
    unsigned char pad[0x6];
    unsigned short value;  // +6
};

// 0x7100213fb4
unsigned short get_213fb4(Field213fb4* object) {
    return object->value;
}

struct Field213fbc {
    unsigned char pad[0x8];
    short value;  // +8
};

// 0x7100213fbc
int get_213fbc(Field213fbc* object) {
    return object->value;
}

struct Field213fc4 {
    unsigned char pad[0xa];
    signed char value;  // +a
};

// 0x7100213fc4
int get_213fc4(Field213fc4* object) {
    return object->value;
}

struct Field214578 {
    unsigned char pad[0x7];
    signed char value;  // +7
};

// 0x7100214578
int get_214578(Field214578* object) {
    return object->value;
}

struct Field214580 {
    unsigned char pad[0x8];
    short value;  // +8
};

// 0x7100214580
int get_214580(Field214580* object) {
    return object->value;
}

struct Field214730 {
    unsigned char pad[0x6];
    short value;  // +6
};

// 0x7100214730
int get_214730(Field214730* object) {
    return object->value;
}

struct Block214df4 {
    unsigned char data[0x5a];
};

// 0x7100214df4
void clear_block_214df4(Block214df4* block) {
    memset(block, 0, sizeof(Block214df4));
}

struct Field215148 {
    unsigned char pad[0x12];
    unsigned char value;  // +12
};

// 0x7100215148
unsigned char get_215148(Field215148* object) {
    return object->value;
}

struct Field215430 {
    unsigned char pad[0x4];
    unsigned short value;  // +4
};

// 0x7100215430
unsigned short get_215430(Field215430* object) {
    return object->value;
}

struct Field215438 {
    unsigned char pad[0x6];
    short value;  // +6
};

// 0x7100215438
int get_215438(Field215438* object) {
    return object->value;
}

struct Field215460 {
    unsigned char pad[0x108];
    int value;  // +108
};

// 0x7100215460
int get_215460(Field215460* object) {
    return object->value;
}

struct Field215da4 {
    unsigned char pad[0x10];
    short value;  // +10
};

// 0x7100215da4
int get_215da4(Field215da4* object) {
    return object->value;
}

struct Field2161e0 {
    unsigned char pad[0x12];
    unsigned short value;  // +12
};

// 0x71002161e0
void set_2161e0(Field2161e0* object, unsigned short value) {
    object->value = value;
}

struct Field2161e8 {
    unsigned char pad[0x14];
    unsigned short value;  // +14
};

// 0x71002161e8
unsigned short get_2161e8(Field2161e8* object) {
    return object->value;
}

// 0x7100216f0c
int constant_216f0c() {
    return 41200;
}

struct Field217508 {
    unsigned char value;  // +0
};

// 0x7100217508
void clear_217508(Field217508* object) {
    object->value = 0;
}

// 0x7100224998
int zero_224998() {
    return 0;
}

// 0x71002249a0
int constant_2249a0() {
    return 1;
}

// 0x71002249a8
int constant_2249a8() {
    return 1;
}

struct Field239d98 {
    long value;  // +0
};

// 0x7100239d98
void clear_239d98(Field239d98* object) {
    object->value = 0;
}

struct Field239e30 {
    long value;  // +0
};

// 0x7100239e30
void clear_239e30(Field239e30* object) {
    object->value = 0;
}

// 0x710023bb88
int constant_23bb88() {
    return 1;
}

// 0x710023be08
int constant_23be08() {
    return 1;
}

// 0x710023be10
int constant_23be10() {
    return 1;
}

// 0x710023da3c
int zero_23da3c() {
    return 0;
}

// 0x710023e2c0
int zero_23e2c0() {
    return 0;
}

// 0x710023e2c8
int zero_23e2c8() {
    return 0;
}

// 0x710023e2d0
int zero_23e2d0() {
    return 0;
}

// 0x710023fa18
int constant_23fa18() {
    return 1;
}

struct Field24151c {
    unsigned char pad[0x10];
    long value;  // +10
};

// 0x710024151c
void clear_24151c(Field24151c* object) {
    object->value = 0;
}

struct Field2416ec {
    unsigned char pad[0x18];
    int value;  // +18
};

// 0x71002416ec
void set_2416ec(Field2416ec* object, int value) {
    object->value = value;
}

struct Field2447c0 {
    unsigned char pad[0x38];
    long value;  // +38
};

// 0x71002447c0
long get_2447c0(Field2447c0* object) {
    return object->value;
}

struct Field2447c8 {
    unsigned char pad[0x38];
    long value;  // +38
};

// 0x71002447c8
void set_2447c8(Field2447c8* object, long value) {
    object->value = value;
}

struct Field244828 {
    unsigned char pad[0x8];
    long value;  // +8
};

// 0x7100244828
long get_244828(Field244828* object) {
    return object->value;
}

struct Field244830 {
    unsigned char pad[0x8];
    long value;  // +8
};

// 0x7100244830
void set_244830(Field244830* object, long value) {
    object->value = value;
}

struct Field244838 {
    unsigned char pad[0x10];
    int value;  // +10
};

// 0x7100244838
int get_244838(Field244838* object) {
    return object->value;
}

struct Holder244840 {
    unsigned char pad[0x10];
    unsigned char member[1];  // +10
};

// 0x7100244840
void* member_244840(Holder244840* object) {
    return object->member;
}

struct Field244848 {
    unsigned char pad[0x10];
    int value;  // +10
};

// 0x7100244848
void set_constant_244848(Field244848* object) {
    object->value = -1;
}

// 0x7100244998
int zero_244998() {
    return 0;
}

struct Field2449a0 {
    unsigned char pad[0x20];
    long value;  // +20
};

// 0x71002449a0
long get_2449a0(Field2449a0* object) {
    return object->value;
}

// 0x71002464c8
int constant_2464c8() {
    return 1;
}

// 0x71002466fc
int constant_2466fc() {
    return 1;
}

// 0x7100246704
int constant_246704() {
    return 1;
}

struct Field24d384 {
    int value;  // +0
};

// 0x710024d384
void clear_24d384(Field24d384* object) {
    object->value = 0;
}

struct Field254964 {
    unsigned char pad[0xdb4];
    int value;  // +db4
};

// 0x7100254964
void set_254964(Field254964* object, int value) {
    object->value = value;
}

struct Field25496c {
    unsigned char pad[0xdb4];
    int value;  // +db4
};

// 0x710025496c
int get_25496c(Field25496c* object) {
    return object->value;
}

struct Field254efc {
    unsigned char pad[0xd50];
    int value;  // +d50
};

// 0x7100254efc
void set_constant_254efc(Field254efc* object) {
    object->value = 12;
}

struct Field2885cc {
    unsigned char pad[0x1];
    unsigned char value;  // +1
};

// 0x71002885cc
unsigned char get_2885cc(Field2885cc* object) {
    return object->value;
}

struct Holder2885d4 {
    unsigned char pad[0x4];
    unsigned char member[1];  // +4
};

// 0x71002885d4
void* member_2885d4(Holder2885d4* object) {
    return object->member;
}

struct Field2886b8 {
    unsigned char pad[0x1];
    unsigned char value;  // +1
};

// 0x71002886b8
void set_2886b8(Field2886b8* object, unsigned char value) {
    object->value = value;
}

struct Holder288734 {
    unsigned char pad[0x4];
    unsigned char member[1];  // +4
};

// 0x7100288734
void* member_288734(Holder288734* object) {
    return object->member;
}

struct Holder28873c {
    unsigned char pad[0x88];
    unsigned char member[1];  // +88
};

// 0x710028873c
void* member_28873c(Holder28873c* object) {
    return object->member;
}

struct Holder288744 {
    unsigned char pad[0x88];
    unsigned char member[1];  // +88
};

// 0x7100288744
void* member_288744(Holder288744* object) {
    return object->member;
}

void handle_206264(void* object);                                     // 0x7100206264
struct Forward288930 {
    unsigned char pad[0x4];
    unsigned char part[1];  // +4
};

// 0x7100288930
void forward_part_288930(Forward288930* object) {
    handle_206264(object->part);
}

struct Field288990 {
    unsigned char value;  // +0
};

// 0x7100288990
unsigned char get_288990(Field288990* object) {
    return object->value;
}

// 0x7100288a38
int zero_288a38() {
    return 0;
}

struct Field290d5c {
    unsigned char pad[0x28];
    long value;  // +28
};

// 0x7100290d5c
long get_290d5c(Field290d5c* object) {
    return object->value;
}

struct Field290f7c {
    unsigned char pad[0x10];
    long value;  // +10
};

// 0x7100290f7c
long get_290f7c(Field290f7c* object) {
    return object->value;
}

struct Field290f84 {
    unsigned char pad[0x18];
    long value;  // +18
};

// 0x7100290f84
long get_290f84(Field290f84* object) {
    return object->value;
}

struct Field290f8c {
    unsigned char pad[0x20];
    long value;  // +20
};

// 0x7100290f8c
long get_290f8c(Field290f8c* object) {
    return object->value;
}

void handle_38a798(void* object);                                     // 0x710038a798
struct Forward2adf14 {
    unsigned char pad[0x10];
    unsigned char part[1];  // +10
};

// 0x71002adf14
void forward_part_2adf14(Forward2adf14* object) {
    handle_38a798(object->part);
}

// 0x71002ae1cc
int constant_2ae1cc() {
    return 1;
}

// 0x71002ae1d4
int zero_2ae1d4() {
    return 0;
}

struct Field2dae38 {
    unsigned char pad[0x8];
    unsigned char value;  // +8
};

// 0x71002dae38
unsigned char get_2dae38(Field2dae38* object) {
    return object->value;
}

struct Field2dbbb4 {
    unsigned char pad[0xa];
    unsigned char value;  // +a
};

// 0x71002dbbb4
void set_2dbbb4(Field2dbbb4* object, unsigned char value) {
    object->value = value;
}

struct Field2dbc3c {
    unsigned char pad[0x104];
    int value;  // +104
};

// 0x71002dbc3c
void set_2dbc3c(Field2dbc3c* object, int value) {
    object->value = value;
}

class Virtual2de6f0 {
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
    virtual void v60();
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void v80();
    virtual void v88();
    virtual void v90();
    virtual void v98();
    virtual void va0();
    virtual void va8();
    virtual void vb0();
    virtual void vb8();
    virtual void call();  // +c0
};

// 0x71002de6f0
void vcall_2de6f0(Virtual2de6f0* object) {
    object->call();
}

struct Field2f6494 {
    unsigned char pad[0x10];
    long value;  // +10
};

// 0x71002f6494
long get_2f6494(Field2f6494* object) {
    return object->value;
}

void handle_1f7f44(void* object);                                     // 0x71001f7f44
struct Forward3102f4 {
    unsigned char pad[0x28];
    void* child;  // +28
};

// 0x71003102f4
void forward_child_3102f4(Forward3102f4* object) {
    handle_1f7f44(object->child);
}

struct Field316ae8 {
    unsigned char pad[0x30];
    int value;  // +30
};

// 0x7100316ae8
void set_316ae8(Field316ae8* object, int value) {
    object->value = value;
}

struct Field316af0 {
    unsigned char pad[0x2c];
    unsigned char value;  // +2c
};

// 0x7100316af0
void set_316af0(Field316af0* object, unsigned char value) {
    object->value = value;
}

struct Field316af8 {
    unsigned char pad[0x2c];
    unsigned char value;  // +2c
};

// 0x7100316af8
unsigned char get_316af8(Field316af8* object) {
    return object->value;
}

struct Field316b24 {
    unsigned char pad[0x28];
    int value;  // +28
};

// 0x7100316b24
int get_316b24(Field316b24* object) {
    return object->value;
}

struct Field316b2c {
    unsigned char pad[0x28];
    int value;  // +28
};

// 0x7100316b2c
void set_316b2c(Field316b2c* object, int value) {
    object->value = value;
}

struct Field316e78 {
    unsigned char pad[0x2d3];
    unsigned char value;  // +2d3
};

// 0x7100316e78
void set_316e78(Field316e78* object, unsigned char value) {
    object->value = value;
}

struct Field316e80 {
    unsigned char pad[0x350];
    long value;  // +350
};

// 0x7100316e80
void set_316e80(Field316e80* object, long value) {
    object->value = value;
}

void handle_386d84(void* object);                                     // 0x7100386d84
struct Forward333460 {
    unsigned char pad[0x150];
    unsigned char part[1];  // +150
};

// 0x7100333460
void forward_part_333460(Forward333460* object) {
    handle_386d84(object->part);
}

struct Field3336ac {
    unsigned char value;  // +0
};

// 0x71003336ac
unsigned char get_3336ac(Field3336ac* object) {
    return object->value;
}

struct Field3336b4 {
    unsigned char value;  // +0
};

// 0x71003336b4
void set_3336b4(Field3336b4* object, unsigned char value) {
    object->value = value;
}

struct Field3336bc {
    unsigned char pad[0x1];
    unsigned char value;  // +1
};

// 0x71003336bc
unsigned char get_3336bc(Field3336bc* object) {
    return object->value;
}

struct Field3336c4 {
    unsigned char pad[0x4];
    int value;  // +4
};

// 0x71003336c4
int get_3336c4(Field3336c4* object) {
    return object->value;
}

struct Field3336cc {
    unsigned char pad[0x4];
    int value;  // +4
};

// 0x71003336cc
void set_3336cc(Field3336cc* object, int value) {
    object->value = value;
}

struct Field3336f8 {
    unsigned char pad[0x74];
    int value;  // +74
};

// 0x71003336f8
void set_3336f8(Field3336f8* object, int value) {
    object->value = value;
}

struct Field333700 {
    unsigned char pad[0x74];
    int value;  // +74
};

// 0x7100333700
int get_333700(Field333700* object) {
    return object->value;
}

struct Field337ef4 {
    unsigned char pad[0x1c];
    int value;  // +1c
};

// 0x7100337ef4
void set_337ef4(Field337ef4* object, int value) {
    object->value = value;
}

class Virtual338b98 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void call();  // +20
};

// 0x7100338b98
void vcall_338b98(Virtual338b98* object) {
    object->call();
}

struct Field339f0c {
    unsigned char pad[0x60];
    float value;  // +60
};

// 0x7100339f0c
float get_339f0c(Field339f0c* object) {
    return object->value;
}

struct Field339f14 {
    unsigned char pad[0x60];
    float value;  // +60
};

// 0x7100339f14
void set_339f14(Field339f14* object, float value) {
    object->value = value;
}

void handle_37dc14(void* object);                                     // 0x710037dc14
struct Forward33b8d0 {
    unsigned char pad[0x3b8];
    unsigned char part[1];  // +3b8
};

// 0x710033b8d0
void forward_part_33b8d0(Forward33b8d0* object) {
    handle_37dc14(object->part);
}

struct Field33b8e8 {
    unsigned char pad[0x124];
    float value;  // +124
};

// 0x710033b8e8
void set_33b8e8(Field33b8e8* object, float value) {
    object->value = value;
}

// 0x710033d790
int constant_33d790() {
    return -1;
}

struct Field33d930 {
    unsigned char pad[0x28cc];
    int value;  // +28cc
};

// 0x710033d930
int get_33d930(Field33d930* object) {
    return object->value;
}

struct Field33f5e0 {
    unsigned char pad[0x295c];
    int value;  // +295c
};

// 0x710033f5e0
void set_33f5e0(Field33f5e0* object, int value) {
    object->value = value;
}

class Virtual388154 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void call();  // +18
};

// 0x7100388154
void vcall_388154(Virtual388154* object) {
    object->call();
}

struct Field38cc40 {
    unsigned char pad[0x2250];
    long value;  // +2250
};

// 0x710038cc40
void set_38cc40(Field38cc40* object, long value) {
    object->value = value;
}

struct Field38cc6c {
    unsigned char pad[0x2260];
    int value;  // +2260
};

// 0x710038cc6c
void set_38cc6c(Field38cc6c* object, int value) {
    object->value = value;
}

// 0x7100391ac8
int zero_391ac8() {
    return 0;
}

struct Field39dfc4 {
    unsigned char pad[0x22e8];
    long value;  // +22e8
};

// 0x710039dfc4
void set_39dfc4(Field39dfc4* object, long value) {
    object->value = value;
}

struct Field39dff0 {
    unsigned char pad[0x22f0];
    long value;  // +22f0
};

// 0x710039dff0
void set_39dff0(Field39dff0* object, long value) {
    object->value = value;
}

struct Field39dff8 {
    unsigned char pad[0x22f0];
    long value;  // +22f0
};

// 0x710039dff8
long get_39dff8(Field39dff8* object) {
    return object->value;
}

struct Field39e000 {
    unsigned char pad[0x22f8];
    int value;  // +22f8
};

// 0x710039e000
int get_39e000(Field39e000* object) {
    return object->value;
}

struct Field3ad704 {
    unsigned char pad[0x8];
    unsigned char value;  // +8
};

// 0x71003ad704
unsigned char get_3ad704(Field3ad704* object) {
    return object->value;
}

struct Field3ad99c {
    unsigned char pad[0x9];
    unsigned char value;  // +9
};

// 0x71003ad99c
void set_3ad99c(Field3ad99c* object, unsigned char value) {
    object->value = value;
}

struct Field3ada2c {
    unsigned char pad[0x4];
    int value;  // +4
};

// 0x71003ada2c
int get_3ada2c(Field3ada2c* object) {
    return object->value;
}

// 0x71003af1ec
int constant_3af1ec() {
    return 1;
}

struct Field3b031c {
    long value;  // +0
};

// 0x71003b031c
void clear_3b031c(Field3b031c* object) {
    object->value = 0;
}

struct Field3b21d4 {
    unsigned char pad[0x20];
    int value;  // +20
};

// 0x71003b21d4
int get_3b21d4(Field3b21d4* object) {
    return object->value;
}

struct Field3b21f8 {
    unsigned char pad[0x24];
    int value;  // +24
};

// 0x71003b21f8
void set_3b21f8(Field3b21f8* object, int value) {
    object->value = value;
}

// 0x71003c5ad8
int zero_3c5ad8() {
    return 0;
}

struct Field3c7f18 {
    unsigned char pad[0xa8];
    int value;  // +a8
};

// 0x71003c7f18
void set_3c7f18(Field3c7f18* object, int value) {
    object->value = value;
}

struct Field3c812c {
    unsigned char pad[0xad];
    unsigned char value;  // +ad
};

// 0x71003c812c
unsigned char get_3c812c(Field3c812c* object) {
    return object->value;
}

struct Field3c8160 {
    unsigned char pad[0x90];
    long value;  // +90
};

// 0x71003c8160
long get_3c8160(Field3c8160* object) {
    return object->value;
}

// 0x71003cbe20
int zero_3cbe20() {
    return 0;
}

// 0x71003cbe28
int constant_3cbe28() {
    return 1;
}

struct Field3cbe50 {
    int value;  // +0
};

// 0x71003cbe50
int get_3cbe50(Field3cbe50* object) {
    return object->value;
}

// 0x71003cbe64
int zero_3cbe64() {
    return 0;
}

// 0x71003cbe94
int zero_3cbe94() {
    return 0;
}

// 0x71003cbea4
int zero_3cbea4() {
    return 0;
}

// 0x71003cedfc
int zero_3cedfc() {
    return 0;
}

// 0x71003cee34
int zero_3cee34() {
    return 0;
}

// 0x71003cee3c
int zero_3cee3c() {
    return 0;
}

// 0x71003cee44
int zero_3cee44() {
    return 0;
}

// 0x71003d12b8
int constant_3d12b8() {
    return 1;
}

void handle_3d075c(void* object);                                     // 0x71003d075c
struct Forward3d1e48 {
    unsigned char pad[0x10];
    unsigned char part[1];  // +10
};

// 0x71003d1e48
void forward_part_3d1e48(Forward3d1e48* object) {
    handle_3d075c(object->part);
}

void handle_3ddba0(void* object);                                     // 0x71003ddba0
struct Forward3dc624 {
    unsigned char pad[0x890];
    unsigned char part[1];  // +890
};

// 0x71003dc624
void forward_part_3dc624(Forward3dc624* object) {
    handle_3ddba0(object->part);
}

struct Field3decec {
    long value;  // +0
};

// 0x71003decec
void clear_3decec(Field3decec* object) {
    object->value = 0;
}

struct Field3ded78 {
    int value;  // +0
};

// 0x71003ded78
int get_3ded78(Field3ded78* object) {
    return object->value;
}

struct Field3ded80 {
    unsigned char pad[0x4];
    int value;  // +4
};

// 0x71003ded80
int get_3ded80(Field3ded80* object) {
    return object->value;
}

struct Field3deda4 {
    long value;  // +0
};

// 0x71003deda4
void clear_3deda4(Field3deda4* object) {
    object->value = 0;
}

// 0x71003df250
int constant_3df250() {
    return 1080;
}

// 0x71003df258
int constant_3df258() {
    return 1920;
}

struct Field3dfb14 {
    unsigned char pad[0x3344];
    int value;  // +3344
};

// 0x71003dfb14
void set_3dfb14(Field3dfb14* object, int value) {
    object->value = value;
}

struct Field3dfb1c {
    unsigned char pad[0x3344];
    int value;  // +3344
};

// 0x71003dfb1c
int get_3dfb1c(Field3dfb1c* object) {
    return object->value;
}

struct Field3dff50 {
    unsigned char pad[0xf4];
    unsigned char value;  // +f4
};

// 0x71003dff50
void clear_3dff50(Field3dff50* object) {
    object->value = 0;
}

// 0x71003e00a0
int constant_3e00a0() {
    return 1;
}

struct Field3f50cc {
    unsigned char pad[0xc];
    int value;  // +c
};

// 0x71003f50cc
int get_3f50cc(Field3f50cc* object) {
    return object->value;
}

struct Field3f50e8 {
    unsigned char pad[0x10];
    int value;  // +10
};

// 0x71003f50e8
int get_3f50e8(Field3f50e8* object) {
    return object->value;
}

// 0x71003fa33c
int zero_3fa33c() {
    return 0;
}

// 0x71003fa6f8
int zero_3fa6f8() {
    return 0;
}

// 0x71003fe604
int zero_3fe604() {
    return 0;
}

// 0x710040b378
int zero_40b378() {
    return 0;
}

void handle_550adc(void* object);                                     // 0x7100550adc
struct Forward40e8a4 {
    void* child;  // +0
};

// 0x710040e8a4
void forward_child_40e8a4(Forward40e8a4* object) {
    handle_550adc(object->child);
}

void handle_550ce4(void* object);                                     // 0x7100550ce4
struct Forward40ea68 {
    void* child;  // +0
};

// 0x710040ea68
void forward_child_40ea68(Forward40ea68* object) {
    handle_550ce4(object->child);
}

struct Block41fd50 {
    unsigned char data[0x200];
};

// 0x710041fd50
void clear_block_41fd50(Block41fd50* block) {
    memset(block, 0, sizeof(Block41fd50));
}

struct Block41fd5c {
    unsigned char data[0x200];
};

// 0x710041fd5c
void clear_block_41fd5c(Block41fd5c* block) {
    memset(block, 0, sizeof(Block41fd5c));
}

struct Block41fd68 {
    unsigned char data[0x200];
};

// 0x710041fd68
void clear_block_41fd68(Block41fd68* block) {
    memset(block, 0, sizeof(Block41fd68));
}

struct Block41fd74 {
    unsigned char data[0x200];
};

// 0x710041fd74
void clear_block_41fd74(Block41fd74* block) {
    memset(block, 0, sizeof(Block41fd74));
}

void handle_41d428(void* object);                                     // 0x710041d428
struct Forward426b20 {
    unsigned char pad[0x30];
    void* child;  // +30
};

// 0x7100426b20
void forward_child_426b20(Forward426b20* object) {
    handle_41d428(object->child);
}

void handle_41d304(void* object);                                     // 0x710041d304
struct Forward426c48 {
    unsigned char pad[0x10];
    void* child;  // +10
};

// 0x7100426c48
void forward_child_426c48(Forward426c48* object) {
    handle_41d304(object->child);
}

struct Field4273c8 {
    unsigned char pad[0x2ae0];
    int value;  // +2ae0
};

// 0x71004273c8
int get_4273c8(Field4273c8* object) {
    return object->value;
}

struct Field4345e8 {
    unsigned char pad[0x90];
    long value;  // +90
};

// 0x71004345e8
void set_4345e8(Field4345e8* object, long value) {
    object->value = value;
}

struct Block434868 {
    unsigned char data[0x84];
};

// 0x7100434868
void clear_block_434868(Block434868* block) {
    memset(block, 0, sizeof(Block434868));
}

// 0x7100438628
int zero_438628() {
    return 0;
}

struct Block4386e8 {
    unsigned char data[0xc84];
};

// 0x71004386e8
void clear_block_4386e8(Block4386e8* block) {
    memset(block, 0, sizeof(Block4386e8));
}

struct Block438710 {
    unsigned char data[0xc84];
};

// 0x7100438710
void clear_block_438710(Block438710* block) {
    memset(block, 0, sizeof(Block438710));
}

// 0x710043b22c
int zero_43b22c() {
    return 0;
}

// 0x710043b294
int constant_43b294() {
    return 1;
}

// 0x710043b29c
int constant_43b29c() {
    return 1;
}

// 0x710043b2a8
void* null_43b2a8() {
    return nullptr;
}

// 0x710043b2b0
void* null_43b2b0() {
    return nullptr;
}

struct Field43b78c {
    unsigned char pad[0x1c];
    unsigned char value;  // +1c
};

// 0x710043b78c
void clear_43b78c(Field43b78c* object) {
    object->value = 0;
}

void handle_4498ec(void* object);                                     // 0x71004498ec
struct Forward43dcf8 {
    unsigned char pad[0x58];
    void* child;  // +58
};

// 0x710043dcf8
void forward_child_43dcf8(Forward43dcf8* object) {
    handle_4498ec(object->child);
}

void handle_25b3ac(void* object);                                     // 0x710025b3ac
struct Forward4498e4 {
    unsigned char pad[0x18];
    unsigned char part[1];  // +18
};

// 0x71004498e4
void forward_part_4498e4(Forward4498e4* object) {
    handle_25b3ac(object->part);
}

// 0x7100452a1c
int zero_452a1c() {
    return 0;
}

// 0x7100455874
int zero_455874() {
    return 0;
}

// 0x710045587c
int constant_45587c() {
    return -1;
}

// 0x7100455884
int constant_455884() {
    return -1;
}

// 0x710045663c
int constant_45663c() {
    return 1;
}

// 0x7100456644
int constant_456644() {
    return 1;
}

void handle_40d308(void* object);                                     // 0x710040d308
struct Forward4578f8 {
    unsigned char pad[0x10];
    void* child;  // +10
};

// 0x71004578f8
void forward_child_4578f8(Forward4578f8* object) {
    handle_40d308(object->child);
}

void handle_44b990(void* object);                                     // 0x710044b990
struct Forward4579b8 {
    unsigned char pad[0x18];
    void* child;  // +18
};

// 0x71004579b8
void forward_child_4579b8(Forward4579b8* object) {
    handle_44b990(object->child);
}

void handle_44bb44(void* object);                                     // 0x710044bb44
struct Forward4579c0 {
    unsigned char pad[0x18];
    void* child;  // +18
};

// 0x71004579c0
void forward_child_4579c0(Forward4579c0* object) {
    handle_44bb44(object->child);
}

void handle_454c58(void* object);                                     // 0x7100454c58
struct Forward457a84 {
    unsigned char pad[0x20];
    void* child;  // +20
};

// 0x7100457a84
void forward_child_457a84(Forward457a84* object) {
    handle_454c58(object->child);
}

struct Field459660 {
    unsigned char pad[0x8];
    long value;  // +8
};

// 0x7100459660
long get_459660(Field459660* object) {
    return object->value;
}

struct Field4599e4 {
    long value;  // +0
};

// 0x71004599e4
void clear_4599e4(Field4599e4* object) {
    object->value = 0;
}

struct Field45c450 {
    unsigned char pad[0x30];
    int value;  // +30
};

// 0x710045c450
int get_45c450(Field45c450* object) {
    return object->value;
}

struct Field45ce4c {
    unsigned char value;  // +0
};

// 0x710045ce4c
unsigned char get_45ce4c(Field45ce4c* object) {
    return object->value;
}

struct Field45d5a8 {
    unsigned char pad[0x244];
    int value;  // +244
};

// 0x710045d5a8
int get_45d5a8(Field45d5a8* object) {
    return object->value;
}

struct Field45d5b0 {
    unsigned char pad[0x248];
    int value;  // +248
};

// 0x710045d5b0
int get_45d5b0(Field45d5b0* object) {
    return object->value;
}

struct Field45d5b8 {
    unsigned char pad[0x24c];
    unsigned char value;  // +24c
};

// 0x710045d5b8
void set_45d5b8(Field45d5b8* object, unsigned char value) {
    object->value = value;
}

struct Field45d5c0 {
    unsigned char pad[0x24d];
    unsigned char value;  // +24d
};

// 0x710045d5c0
void set_45d5c0(Field45d5c0* object, unsigned char value) {
    object->value = value;
}

struct Field45d5c8 {
    unsigned char pad[0x24e];
    unsigned char value;  // +24e
};

// 0x710045d5c8
unsigned char get_45d5c8(Field45d5c8* object) {
    return object->value;
}

struct Field45d5d0 {
    unsigned char pad[0x24e];
    unsigned char value;  // +24e
};

// 0x710045d5d0
void set_45d5d0(Field45d5d0* object, unsigned char value) {
    object->value = value;
}

struct Field45d5e4 {
    unsigned char pad[0x251];
    unsigned char value;  // +251
};

// 0x710045d5e4
void set_45d5e4(Field45d5e4* object, unsigned char value) {
    object->value = value;
}

struct Field4610cc {
    long value;  // +0
};

// 0x71004610cc
void clear_4610cc(Field4610cc* object) {
    object->value = 0;
}

struct Field4615bc {
    unsigned char pad[0xd0];
    long value;  // +d0
};

// 0x71004615bc
void set_4615bc(Field4615bc* object, long value) {
    object->value = value;
}

struct Field4615c4 {
    unsigned char pad[0xd8];
    long value;  // +d8
};

// 0x71004615c4
void set_4615c4(Field4615c4* object, long value) {
    object->value = value;
}

// 0x71004624f4
int constant_4624f4() {
    return 4096;
}

// 0x71004624fc
int constant_4624fc() {
    return 4096;
}

struct Field46611c {
    unsigned char pad[0x2c];
    unsigned char value;  // +2c
};

// 0x710046611c
void clear_46611c(Field46611c* object) {
    object->value = 0;
}

struct Field466150 {
    long value;  // +0
};

// 0x7100466150
long get_466150(Field466150* object) {
    return object->value;
}

struct Field46637c {
    unsigned char pad[0x24];
    unsigned char value;  // +24
};

// 0x710046637c
void clear_46637c(Field46637c* object) {
    object->value = 0;
}

struct Field46653c {
    unsigned char pad[0x18];
    unsigned char value;  // +18
};

// 0x710046653c
void clear_46653c(Field46653c* object) {
    object->value = 0;
}

struct Field4665b8 {
    unsigned char pad[0x10];
    long value;  // +10
};

// 0x71004665b8
long get_4665b8(Field4665b8* object) {
    return object->value;
}

struct Field4668d8 {
    unsigned char value;  // +0
};

// 0x71004668d8
void clear_4668d8(Field4668d8* object) {
    object->value = 0;
}

struct Field4668f4 {
    unsigned char value;  // +0
};

// 0x71004668f4
void clear_4668f4(Field4668f4* object) {
    object->value = 0;
}

// 0x7100467010
int zero_467010() {
    return 0;
}

// 0x71004670dc
int constant_4670dc() {
    return 1;
}

// 0x71004673c4
int constant_4673c4() {
    return 256;
}

struct Holder490034 {
    unsigned char pad[0x30];
    unsigned char member[1];  // +30
};

// 0x7100490034
void* member_490034(Holder490034* object) {
    return object->member;
}

struct Field49733c {
    unsigned char pad[0x40];
    long value;  // +40
};

// 0x710049733c
long get_49733c(Field49733c* object) {
    return object->value;
}

struct Field497ab8 {
    unsigned char pad[0x58];
    unsigned char value;  // +58
};

// 0x7100497ab8
unsigned char get_497ab8(Field497ab8* object) {
    return object->value;
}

// 0x710049ad80
int constant_49ad80() {
    return 1;
}

struct Field49ba44 {
    unsigned char pad[0x18];
    long value;  // +18
};

// 0x710049ba44
long get_49ba44(Field49ba44* object) {
    return object->value;
}

struct Field49cb10 {
    unsigned char pad[0x4c];
    int value;  // +4c
};

// 0x710049cb10
int get_49cb10(Field49cb10* object) {
    return object->value;
}

struct Field49cca4 {
    unsigned char pad[0x4c];
    int value;  // +4c
};

// 0x710049cca4
void clear_49cca4(Field49cca4* object) {
    object->value = 0;
}

void handle_4e2600(void* object);                                     // 0x71004e2600
struct Forward4e0a78 {
    unsigned char pad[0x10];
    unsigned char part[1];  // +10
};

// 0x71004e0a78
void forward_part_4e0a78(Forward4e0a78* object) {
    handle_4e2600(object->part);
}

// 0x71004fa55c
void* null_4fa55c() {
    return nullptr;
}

// 0x7100515584
void* null_515584() {
    return nullptr;
}

void handle_5256e0(void* object);                                     // 0x71005256e0
struct Forward51f374 {
    unsigned char pad[0x31d8];
    void* child;  // +31d8
};

// 0x710051f374
void forward_child_51f374(Forward51f374* object) {
    handle_5256e0(object->child);
}

struct Field520dc4 {
    unsigned char pad[0x30];
    long value;  // +30
};

// 0x7100520dc4
long get_520dc4(Field520dc4* object) {
    return object->value;
}

void handle_524b78(void* object);                                     // 0x7100524b78
struct Forward5327b0 {
    unsigned char pad[0x10];
    void* child;  // +10
};

// 0x71005327b0
void forward_child_5327b0(Forward5327b0* object) {
    handle_524b78(object->child);
}

struct Field5349dc {
    unsigned char pad[0x2c];
    int value;  // +2c
};

// 0x71005349dc
void set_5349dc(Field5349dc* object, int value) {
    object->value = value;
}

struct Field53d568 {
    unsigned char pad[0x18];
    long value;  // +18
};

// 0x710053d568
long get_53d568(Field53d568* object) {
    return object->value;
}

void handle_600a90(void* object);                                     // 0x7100600a90
struct Forward53d5c0 {
    unsigned char pad[0x920];
    unsigned char part[1];  // +920
};

// 0x710053d5c0
void forward_part_53d5c0(Forward53d5c0* object) {
    handle_600a90(object->part);
}

struct Field541adc {
    unsigned char pad[0x130];
    int value;  // +130
};

// 0x7100541adc
void set_541adc(Field541adc* object, int value) {
    object->value = value;
}

struct Field550e2c {
    unsigned char pad[0x290];
    float value;  // +290
};

// 0x7100550e2c
void set_550e2c(Field550e2c* object, float value) {
    object->value = value;
}

struct Field553448 {
    unsigned char pad[0x18];
    long value;  // +18
};

// 0x7100553448
void set_553448(Field553448* object, long value) {
    object->value = value;
}

struct Field557e3c {
    unsigned char pad[0x70];
    float value;  // +70
};

// 0x7100557e3c
float get_557e3c(Field557e3c* object) {
    return object->value;
}

struct Field557e44 {
    unsigned char pad[0x74];
    float value;  // +74
};

// 0x7100557e44
float get_557e44(Field557e44* object) {
    return object->value;
}

struct Holder557e4c {
    unsigned char pad[0x88];
    unsigned char member[1];  // +88
};

// 0x7100557e4c
void* member_557e4c(Holder557e4c* object) {
    return object->member;
}

struct Field558740 {
    unsigned char pad[0x20];
    long value;  // +20
};

// 0x7100558740
long get_558740(Field558740* object) {
    return object->value;
}

// 0x7100560484
int constant_560484() {
    return 288;
}

// 0x7100561408
int constant_561408() {
    return 128;
}

// 0x71005646d0
int constant_5646d0() {
    return 304;
}

// 0x7100564850
int constant_564850() {
    return 160;
}

// 0x7100564858
int constant_564858() {
    return 240;
}

// 0x7100564860
int constant_564860() {
    return 288;
}

// 0x7100564868
int constant_564868() {
    return 288;
}

// 0x7100564870
int constant_564870() {
    return 336;
}

// 0x71005649f8
int constant_5649f8() {
    return 256;
}

// 0x71005665d0
int constant_5665d0() {
    return 120;
}

void handle_56ace8(void* object);                                     // 0x710056ace8
struct Forward56bd6c {
    unsigned char pad[0xa8];
    unsigned char part[1];  // +a8
};

// 0x710056bd6c
void forward_part_56bd6c(Forward56bd6c* object) {
    handle_56ace8(object->part);
}

struct Field5932c4 {
    unsigned char pad[0x1294];
    int value;  // +1294
};

// 0x71005932c4
void set_constant_5932c4(Field5932c4* object) {
    object->value = -1;
}

// 0x710059457c
int constant_59457c() {
    return 1;
}

// 0x71005947d4
int constant_5947d4() {
    return 1;
}

// 0x71005aaea8
int constant_5aaea8() {
    return 2;
}

struct Field5c2e54 {
    unsigned char pad[0x20];
    long value;  // +20
};

// 0x71005c2e54
void clear_5c2e54(Field5c2e54* object) {
    object->value = 0;
}

struct Field5c3a14 {
    unsigned char pad[0x50];
    long value;  // +50
};

// 0x71005c3a14
long get_5c3a14(Field5c3a14* object) {
    return object->value;
}

// 0x71005c8944
int constant_5c8944() {
    return 1;
}

struct Field5c894c {
    unsigned char pad[0x28];
    int value;  // +28
};

// 0x71005c894c
int get_5c894c(Field5c894c* object) {
    return object->value;
}

// 0x71005ca118
int constant_5ca118() {
    return 1;
}

void handle_601340(void* object);                                     // 0x7100601340
struct Forward5cbd5c {
    unsigned char pad[0x4b0];
    unsigned char part[1];  // +4b0
};

// 0x71005cbd5c
void forward_part_5cbd5c(Forward5cbd5c* object) {
    handle_601340(object->part);
}

struct Forward5cbd64 {
    unsigned char pad[0x680];
    unsigned char part[1];  // +680
};

// 0x71005cbd64
void forward_part_5cbd64(Forward5cbd64* object) {
    handle_601340(object->part);
}

void handle_5d2354(void* object);                                     // 0x71005d2354
struct Forward5dbb70 {
    unsigned char pad[0xf8];
    unsigned char part[1];  // +f8
};

// 0x71005dbb70
void forward_part_5dbb70(Forward5dbb70* object) {
    handle_5d2354(object->part);
}

void handle_5d2398(void* object);                                     // 0x71005d2398
struct Forward5dbb78 {
    unsigned char pad[0xf8];
    unsigned char part[1];  // +f8
};

// 0x71005dbb78
void forward_part_5dbb78(Forward5dbb78* object) {
    handle_5d2398(object->part);
}

struct Field5e3e74 {
    unsigned char pad[0x8];
    long value;  // +8
};

// 0x71005e3e74
long get_5e3e74(Field5e3e74* object) {
    return object->value;
}

struct Field5e3e7c {
    unsigned char pad[0x10];
    long value;  // +10
};

// 0x71005e3e7c
long get_5e3e7c(Field5e3e7c* object) {
    return object->value;
}

struct Field5e3eb0 {
    unsigned char pad[0x30];
    long value;  // +30
};

// 0x71005e3eb0
long get_5e3eb0(Field5e3eb0* object) {
    return object->value;
}

struct Field5e3eb8 {
    unsigned char pad[0x38];
    long value;  // +38
};

// 0x71005e3eb8
long get_5e3eb8(Field5e3eb8* object) {
    return object->value;
}

struct Field5e3ec0 {
    unsigned char pad[0x18];
    int value;  // +18
};

// 0x71005e3ec0
int get_5e3ec0(Field5e3ec0* object) {
    return object->value;
}

struct Field5e3ec8 {
    unsigned char pad[0x1c];
    int value;  // +1c
};

// 0x71005e3ec8
int get_5e3ec8(Field5e3ec8* object) {
    return object->value;
}

struct Field5e3ed0 {
    unsigned char pad[0x24];
    int value;  // +24
};

// 0x71005e3ed0
int get_5e3ed0(Field5e3ed0* object) {
    return object->value;
}

struct Field5e3ed8 {
    unsigned char pad[0x28];
    int value;  // +28
};

// 0x71005e3ed8
int get_5e3ed8(Field5e3ed8* object) {
    return object->value;
}

struct Field5e3eec {
    unsigned char pad[0x10];
    long value;  // +10
};

// 0x71005e3eec
void set_5e3eec(Field5e3eec* object, long value) {
    object->value = value;
}

struct Field5e3ef4 {
    unsigned char pad[0x8];
    long value;  // +8
};

// 0x71005e3ef4
void set_5e3ef4(Field5e3ef4* object, long value) {
    object->value = value;
}

struct Field5e3efc {
    unsigned char pad[0x30];
    long value;  // +30
};

// 0x71005e3efc
void set_5e3efc(Field5e3efc* object, long value) {
    object->value = value;
}

struct Field5e3f04 {
    unsigned char pad[0x38];
    long value;  // +38
};

// 0x71005e3f04
void set_5e3f04(Field5e3f04* object, long value) {
    object->value = value;
}

struct Field5e3f0c {
    unsigned char pad[0x24];
    int value;  // +24
};

// 0x71005e3f0c
void set_5e3f0c(Field5e3f0c* object, int value) {
    object->value = value;
}

// 0x71005e73e0
int zero_5e73e0() {
    return 0;
}

// 0x71005edfd0
int zero_5edfd0() {
    return 0;
}

void handle_5f4b94(void* object);                                     // 0x71005f4b94
struct Forward5f154c {
    unsigned char pad[0x8];
    unsigned char part[1];  // +8
};

// 0x71005f154c
void forward_part_5f154c(Forward5f154c* object) {
    handle_5f4b94(object->part);
}

// 0x71005f1984
int zero_5f1984() {
    return 0;
}

// 0x71005f2640
int zero_5f2640() {
    return 0;
}

void handle_5f4f60(void* object);                                     // 0x71005f4f60
struct Forward5f2ca0 {
    unsigned char pad[0x8];
    unsigned char part[1];  // +8
};

// 0x71005f2ca0
void forward_part_5f2ca0(Forward5f2ca0* object) {
    handle_5f4f60(object->part);
}

void handle_5efb10(void* object);                                     // 0x71005efb10
struct Forward5f3758 {
    unsigned char pad[0x118];
    unsigned char part[1];  // +118
};

// 0x71005f3758
void forward_part_5f3758(Forward5f3758* object) {
    handle_5efb10(object->part);
}

struct Field5f8cd0 {
    long value;  // +0
};

// 0x71005f8cd0
void clear_5f8cd0(Field5f8cd0* object) {
    object->value = 0;
}

struct Field5f9a70 {
    unsigned char pad[0x194];
    int value;  // +194
};

// 0x71005f9a70
int get_5f9a70(Field5f9a70* object) {
    return object->value;
}

// 0x71005fa91c
void* null_5fa91c() {
    return nullptr;
}

// 0x71005fa928
int constant_5fa928() {
    return 1;
}

// 0x71005fa930
int constant_5fa930() {
    return 1;
}

// 0x71005fa938
int constant_5fa938() {
    return 1;
}

// 0x71005fa940
int constant_5fa940() {
    return 1;
}

// 0x71005fa948
int constant_5fa948() {
    return 1;
}

struct Field5faec4 {
    unsigned char pad[0xb0];
    long value;  // +b0
};

// 0x71005faec4
void set_5faec4(Field5faec4* object, long value) {
    object->value = value;
}

struct Field5fb930 {
    unsigned char pad[0xbc];
    float value;  // +bc
};

// 0x71005fb930
void set_5fb930(Field5fb930* object, float value) {
    object->value = value;
}
