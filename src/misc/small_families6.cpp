// More code families found by tools/family_scan.py, grouped until their source files are
// linked: constant-table lookups, command results passed on, base-calling destructors,
// two-argument global forwarders and channel destructors with the active flag at +50. Within
// a family the bodies are identical apart from the tables, globals and callees they use;
// classes and functions are named after their address, callees after theirs.
// Status: matching/README.md.

class ResultTarget {
public:
    virtual void v000();
    virtual void v008();
    virtual void v010();
    virtual void v018();
    virtual void v020();
    virtual void v028();
    virtual void v030();
    virtual void v038();
    virtual void v040();
    virtual void v048();
    virtual void v050();
    virtual void v058();
    virtual void v060();
    virtual void v068();
    virtual void v070();
    virtual void v078();
    virtual void v080();
    virtual void v088();
    virtual void v090();
    virtual void v098();
    virtual void v0a0();
    virtual void v0a8();
    virtual void v0b0();
    virtual void v0b8();
    virtual void v0c0();
    virtual void v0c8();
    virtual void v0d0();
    virtual void v0d8();
    virtual void v0e0();
    virtual void v0e8();
    virtual void v0f0();
    virtual void v0f8();
    virtual void v100();
    virtual void v108();
    virtual void v110();
    virtual void v118();
    virtual void v120();
    virtual void v128();
    virtual void v130();
    virtual void v138();
    virtual void v140();
    virtual void v148();
    virtual void v150();
    virtual void v158();
    virtual void v160();
    virtual void v168();
    virtual void v170();
    virtual void v178();
    virtual void v180();
    virtual void v188();
    virtual void v190();
    virtual void v198();
    virtual void v1a0();
    virtual void v1a8();
    virtual void v1b0();
    virtual void v1b8();
    virtual void v1c0();
    virtual void v1c8();
    virtual void v1d0();
    virtual void v1d8();
    virtual void v1e0();
    virtual void v1e8();
    virtual void v1f0();
    virtual void v1f8();
    virtual void v200();
    virtual void v208();
    virtual void v210();
    virtual void v218();
    virtual void v220();
    virtual void v228();
    virtual void v230();
    virtual void v238();
    virtual void v240();
    virtual void v248();
    virtual void v250();
    virtual void v258();
    virtual void v260();
    virtual void v268();
    virtual void v270();
    virtual void v278();
    virtual void v280();
    virtual void v288();
    virtual void v290();
    virtual void v298();
    virtual void v2a0();
    virtual void v2a8();
    virtual void v2b0();
    virtual void v2b8();
    virtual void v2c0();
    virtual void v2c8();
    virtual void v2d0();
    virtual void v2d8();
    virtual void v2e0();
    virtual void v2e8();
    virtual void v2f0();
    virtual void v2f8();
    virtual void v300();
    virtual void v308();
    virtual void v310();
    virtual void v318();
    virtual void v320();
    virtual void v328();
    virtual void v330();
    virtual void v338();
    virtual void v340();
    virtual void v348();
    virtual void v350();
    virtual void v358();
    virtual void v360();
    virtual void v368();
    virtual void v370();
    virtual void v378();
    virtual void v380();
    virtual void v388();
    virtual void v390();
    virtual void v398();
    virtual void v3a0();
    virtual void v3a8();
    virtual void v3b0();
    virtual void v3b8();
    virtual void v3c0();
    virtual void v3c8();
    virtual void v3d0();
    virtual void v3d8();
    virtual void v3e0();
    virtual int command();    // +3e8
};

// Constant-table lookups (the tables are hidden constants addressed directly).

extern const int kTable_1937a0[] __attribute__((visibility("hidden")));

extern const int kTable_4659f0[] __attribute__((visibility("hidden")));

extern const int kTable_465a00[] __attribute__((visibility("hidden")));

extern const int kTable_465a10[] __attribute__((visibility("hidden")));

extern const int kTable_465a20[] __attribute__((visibility("hidden")));

extern const int kTable_465a30[] __attribute__((visibility("hidden")));

extern const int kTable_465a40[] __attribute__((visibility("hidden")));

extern const int kTable_465a50[] __attribute__((visibility("hidden")));

extern const int kTable_465a60[] __attribute__((visibility("hidden")));

extern const int kTable_465a70[] __attribute__((visibility("hidden")));

extern const int kTable_465a80[] __attribute__((visibility("hidden")));

extern const int kTable_465b44[] __attribute__((visibility("hidden")));

extern const int kTable_465b54[] __attribute__((visibility("hidden")));

extern const int kTable_465b98[] __attribute__((visibility("hidden")));

extern const int kTable_465ba8[] __attribute__((visibility("hidden")));

extern const int kTable_465bb8[] __attribute__((visibility("hidden")));

// 0x71001937a0
int table_value_1937a0(unsigned int index) {
    return kTable_1937a0[index];
}

// 0x71004659f0
int table_value_4659f0(unsigned int index) {
    return kTable_4659f0[index];
}

// 0x7100465a00
int table_value_465a00(unsigned int index) {
    return kTable_465a00[index];
}

// 0x7100465a10
int table_value_465a10(unsigned int index) {
    return kTable_465a10[index];
}

// 0x7100465a20
int table_value_465a20(unsigned int index) {
    return kTable_465a20[index];
}

// 0x7100465a30
int table_value_465a30(unsigned int index) {
    return kTable_465a30[index];
}

// 0x7100465a40
int table_value_465a40(unsigned int index) {
    return kTable_465a40[index];
}

// 0x7100465a50
int table_value_465a50(unsigned int index) {
    return kTable_465a50[index];
}

// 0x7100465a60
int table_value_465a60(unsigned int index) {
    return kTable_465a60[index];
}

// 0x7100465a70
int table_value_465a70(unsigned int index) {
    return kTable_465a70[index];
}

// 0x7100465a80
int table_value_465a80(unsigned int index) {
    return kTable_465a80[index];
}

// 0x7100465b44
int table_value_465b44(unsigned int index) {
    return kTable_465b44[index];
}

// 0x7100465b54
int table_value_465b54(unsigned int index) {
    return kTable_465b54[index];
}

// 0x7100465b98
int table_value_465b98(unsigned int index) {
    return kTable_465b98[index];
}

// 0x7100465ba8
int table_value_465ba8(unsigned int index) {
    return kTable_465ba8[index];
}

// 0x7100465bb8
int table_value_465bb8(unsigned int index) {
    return kTable_465bb8[index];
}


// Command results passed on.

int pass_result_e91c(int result);                              // 0x710000e91c

int pass_result_c42c(int result);                              // 0x710000c42c

int pass_result_e96c(int result);                              // 0x710000e96c

int pass_result_e98c(int result);                              // 0x710000e98c

int pass_result_e9ac(int result);                              // 0x710000e9ac

int pass_result_e9cc(int result);                              // 0x710000e9cc

int pass_result_e9ec(int result);                              // 0x710000e9ec

int pass_result_ea0c(int result);                              // 0x710000ea0c

int pass_result_ea2c(int result);                              // 0x710000ea2c

// 0x71000cf1dc
int command_result_cf1dc(ResultTarget* target) {
    return pass_result_e91c(target->command());
}

// 0x71000cf208
int command_result_cf208(ResultTarget* target) {
    return pass_result_c42c(target->command());
}

// 0x71000cf234
int command_result_cf234(ResultTarget* target) {
    return pass_result_e96c(target->command());
}

// 0x71000cf260
int command_result_cf260(ResultTarget* target) {
    return pass_result_e98c(target->command());
}

// 0x71000cf28c
int command_result_cf28c(ResultTarget* target) {
    return pass_result_e9ac(target->command());
}

// 0x71000cf2b8
int command_result_cf2b8(ResultTarget* target) {
    return pass_result_e9cc(target->command());
}

// 0x71000cf2e4
int command_result_cf2e4(ResultTarget* target) {
    return pass_result_e9ec(target->command());
}

// 0x71000cf310
int command_result_cf310(ResultTarget* target) {
    return pass_result_ea0c(target->command());
}

// 0x71000cf33c
int command_result_cf33c(ResultTarget* target) {
    return pass_result_ea2c(target->command());
}


// Destructors over an out-of-line base destructor whose body compiles to nothing. With a
// literally empty body Clang skips the vtable store; the original keeps it, so its body did
// something that inlined away (on_finish stands in for that).
inline void on_finish() {}

class FinishBase_5c3a58 {
public:
    virtual ~FinishBase_5c3a58();                                  // 0x71005c3a58
};


class FinishBase_7b8d4 {
public:
    virtual ~FinishBase_7b8d4();                                  // 0x710007b8d4
};


class FinishBase_ad594 {
public:
    virtual ~FinishBase_ad594();                                  // 0x71000ad594
};


class FinishBase_aab24 {
public:
    virtual ~FinishBase_aab24();                                  // 0x71000aab24
};


class FinishBase_b7774 {
public:
    virtual ~FinishBase_b7774();                                  // 0x71000b7774
};



class FinishBase_3cfc74 {
public:
    virtual ~FinishBase_3cfc74();                                  // 0x71003cfc74
};


class FinishBase_53e644 {
public:
    virtual ~FinishBase_53e644();                                  // 0x710053e644
};


class FinishBase_53e72c {
public:
    virtual ~FinishBase_53e72c();                                  // 0x710053e72c
};


class FinishBase_5c3ac8 {
public:
    virtual ~FinishBase_5c3ac8();                                  // 0x71005c3ac8
};


class FinishBase_5d968c {
public:
    virtual ~FinishBase_5d968c();                                  // 0x71005d968c
};



// 0x7100036b8c; vtable through the GOT slot at 0x7100c21db8
class Finished_36b8c : public FinishBase_5c3a58 {
public:
    ~Finished_36b8c() override;
};

Finished_36b8c::~Finished_36b8c() {
    on_finish();
}

// 0x710009df34; vtable through the GOT slot at 0x7100c22390
class Finished_9df34 : public FinishBase_7b8d4 {
public:
    ~Finished_9df34() override;
};

Finished_9df34::~Finished_9df34() {
    on_finish();
}

// 0x71000aadec; vtable through the GOT slot at 0x7100c224a8
class Finished_aadec : public FinishBase_ad594 {
public:
    ~Finished_aadec() override;
};

Finished_aadec::~Finished_aadec() {
    on_finish();
}

// 0x71000ad594; vtable through the GOT slot at 0x7100c224c0
class Finished_ad594 : public FinishBase_aab24 {
public:
    ~Finished_ad594() override;
};

Finished_ad594::~Finished_ad594() {
    on_finish();
}

// 0x71000b7240; vtable through the GOT slot at 0x7100c22750
class Finished_b7240 : public FinishBase_b7774 {
public:
    ~Finished_b7240() override;
};

Finished_b7240::~Finished_b7240() {
    on_finish();
}

// 0x71000ba0b4; vtable through the GOT slot at 0x7100c227a0
class Finished_ba0b4 : public FinishBase_5c3a58 {
public:
    ~Finished_ba0b4() override;
};

Finished_ba0b4::~Finished_ba0b4() {
    on_finish();
}

// 0x71003cfc60; vtable through the GOT slot at 0x7100c2b5c0
class Finished_3cfc60 : public FinishBase_3cfc74 {
public:
    ~Finished_3cfc60() override;
};

Finished_3cfc60::~Finished_3cfc60() {
    on_finish();
}

// 0x710053e1e0; vtable through the GOT slot at 0x7100c2d300
class Finished_53e1e0 : public FinishBase_53e644 {
public:
    ~Finished_53e1e0() override;
};

Finished_53e1e0::~Finished_53e1e0() {
    on_finish();
}

// 0x710053e440; vtable through the GOT slot at 0x7100c2d308
class Finished_53e440 : public FinishBase_53e72c {
public:
    ~Finished_53e440() override;
};

Finished_53e440::~Finished_53e440() {
    on_finish();
}

// 0x71005ca990; vtable through the GOT slot at 0x7100c2dbf8
class Finished_5ca990 : public FinishBase_5c3ac8 {
public:
    ~Finished_5ca990() override;
};

Finished_5ca990::~Finished_5ca990() {
    on_finish();
}

// 0x71005db8cc; vtable through the GOT slot at 0x7100c2dcf8
class Finished_5db8cc : public FinishBase_5d968c {
public:
    ~Finished_5db8cc() override;
};

Finished_5db8cc::~Finished_5db8cc() {
    on_finish();
}

// 0x71005dd278; vtable through the GOT slot at 0x7100c2dd10
class Finished_5dd278 : public FinishBase_5d968c {
public:
    ~Finished_5dd278() override;
};

Finished_5dd278::~Finished_5dd278() {
    on_finish();
}


// Two-argument global forwarders.

// Reached through the GOT slot at 0x7100c21690.
extern void* gGlobal_c21690;

void global_call2_22d58(void* object, int a, int b);            // 0x7100022d58

void global_call2_21a24(void* object, int a, int b);            // 0x7100021a24

// Reached through the GOT slot at 0x7100c22058.
extern void* gGlobal_c22058;

void global_call2_63270(void* object, int a, int b);            // 0x7100063270

void global_call2_65648(void* object, int a, int b);            // 0x7100065648

void global_call2_652d4(void* object, int a, int b);            // 0x71000652d4

// Reached through the GOT slot at 0x7100c2a520.
extern void* gGlobal_c2a520;

void global_call2_248adc(void* object, int a, int b);            // 0x7100248adc

void global_call2_248b24(void* object, int a, int b);            // 0x7100248b24

// 0x710003e27c
void forward_pair_3e27c(int a, int b) {
    global_call2_22d58(gGlobal_c21690, a, b);
}

// 0x710003f2c8
void forward_pair_3f2c8(int a, int b) {
    global_call2_21a24(gGlobal_c21690, a, b);
}

// 0x710006e3ec
void forward_pair_6e3ec(int a, int b) {
    global_call2_63270(gGlobal_c22058, a, b);
}

// 0x710006e87c
void forward_pair_6e87c(int a, int b) {
    global_call2_65648(gGlobal_c22058, a, b);
}

// 0x710006e9f4
void forward_pair_6e9f4(int a, int b) {
    global_call2_652d4(gGlobal_c22058, a, b);
}

// 0x7100257a48
void forward_pair_257a48(int a, int b) {
    global_call2_248adc(gGlobal_c2a520, a, b);
}

// 0x7100257aac
void forward_pair_257aac(int a, int b) {
    global_call2_248b24(gGlobal_c2a520, a, b);
}


// Two-argument forwarders to a member deep inside a global object (+11b3b0).
struct DeepObject {
    unsigned char pad[0x11b3b0];
    unsigned char member[8];  // +11b3b0
};

// Reached through the GOT slot at 0x7100c21690.
extern DeepObject* gGlobal_c21690_deep;

void member_call2_16234(void* member, int a, int b);            // 0x7100016234

void member_call2_16af4(void* member, int a, int b);            // 0x7100016af4

void member_call2_16b88(void* member, int a, int b);            // 0x7100016b88

void member_call2_16c48(void* member, int a, int b);            // 0x7100016c48

void member_call2_16e74(void* member, int a, int b);            // 0x7100016e74

// 0x7100040a2c
void forward_member_40a2c(int a, int b) {
    member_call2_16234(gGlobal_c21690_deep->member, a, b);
}

// 0x7100040a58
void forward_member_40a58(int a, int b) {
    member_call2_16af4(gGlobal_c21690_deep->member, a, b);
}

// 0x7100040a84
void forward_member_40a84(int a, int b) {
    member_call2_16b88(gGlobal_c21690_deep->member, a, b);
}

// 0x7100040ab0
void forward_member_40ab0(int a, int b) {
    member_call2_16c48(gGlobal_c21690_deep->member, a, b);
}

// 0x7100040adc
void forward_member_40adc(int a, int b) {
    member_call2_16e74(gGlobal_c21690_deep->member, a, b);
}


// Channel destructors whose member keeps its active flag at +50 (or +190).
class ChannelBase {
public:
    virtual ~ChannelBase();                                                  // 0x71005c3ac8
    unsigned char pad8[8];
};
class ChannelContext;
// Reached through the GOT slot at 0x7100c2d020.
extern ChannelContext* gChannelContext;

struct Channel50_5f9a94 {
    void stop(ChannelContext* context);                              // 0x71005f9ad8
    ~Channel50_5f9a94();                                        // 0x71005f9a94

    unsigned char pad[0x50];
    unsigned char active;     // +50
};




// This member keeps its active flag at +190.
struct Channel190_5f9748 {
    void stop(ChannelContext* context);                              // 0x71005f9968
    ~Channel190_5f9748();                                        // 0x71005f9748

    unsigned char pad[0x190];
    unsigned char active;     // +190
};




// 0x710051f640; vtable through the GOT slot at 0x7100c2d038
class ChannelUser50_51f640 : public ChannelBase {
public:
    ~ChannelUser50_51f640() override;

    Channel50_5f9a94 member;    // +10
};

ChannelUser50_51f640::~ChannelUser50_51f640() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x710051f6d8; vtable through the GOT slot at 0x7100c2d038
class ChannelUser50_51f6d8 : public ChannelBase {
public:
    ~ChannelUser50_51f6d8() override;

    Channel50_5f9a94 member;    // +10
};

ChannelUser50_51f6d8::~ChannelUser50_51f6d8() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x710051f730; vtable through the GOT slot at 0x7100c2d038
class ChannelUser50_51f730 : public ChannelBase {
public:
    ~ChannelUser50_51f730() override;

    Channel50_5f9a94 member;    // +10
};

ChannelUser50_51f730::~ChannelUser50_51f730() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x71005266f8; vtable through the GOT slot at 0x7100c2d130
class ChannelUser50_5266f8 : public ChannelBase {
public:
    ~ChannelUser50_5266f8() override;

    Channel190_5f9748 member;    // +10
};

ChannelUser50_5266f8::~ChannelUser50_5266f8() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x71005269dc; vtable through the GOT slot at 0x7100c2d130
class ChannelUser50_5269dc : public ChannelBase {
public:
    ~ChannelUser50_5269dc() override;

    Channel190_5f9748 member;    // +10
};

ChannelUser50_5269dc::~ChannelUser50_5269dc() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x7100526a34; vtable through the GOT slot at 0x7100c2d130
class ChannelUser50_526a34 : public ChannelBase {
public:
    ~ChannelUser50_526a34() override;

    Channel190_5f9748 member;    // +10
};

ChannelUser50_526a34::~ChannelUser50_526a34() {
    if (member.active)
        member.stop(gChannelContext);
}
