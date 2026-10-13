// Command handlers found by tools/family_scan.py: each calls virtual slot +3e8 on its argument
// and returns a constant, or forwards the slot's result with two of the argument's fields.
// The bodies are identical apart from the forwarding target, and they sit in several source
// files, so they are grouped here until those files are linked; functions are named after
// their address, callees after theirs. Status: matching/README.md.

class CommandTarget {
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

    unsigned char pad08[0x1c];
    short kind;               // +24
    unsigned char pad26[0xba];
    unsigned char queue[0x18]; // +e0
    unsigned char queue_f8[8]; // +f8
    unsigned char queue_100[8]; // +100
};

// 0x7100026b0c
int command_ret0_26b0c(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x7100026b58
int command_ret0_26b58(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x7100026c10
int command_ret0_26c10(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x7100026c30
int command_ret0_26c30(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x7100026d2c
int command_ret0_26d2c(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x7100028b58
int command_ret0_28b58(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x7100028b84
int command_ret0_28b84(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x7100028c54
int command_ret0_28c54(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x7100028c74
int command_ret0_28c74(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x7100028d70
int command_ret0_28d70(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x710002a4a4
int command_ret0_2a4a4(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x710002a4d0
int command_ret0_2a4d0(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x710002a594
int command_ret0_2a594(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x710002a5b4
int command_ret0_2a5b4(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x710002a6b0
int command_ret0_2a6b0(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x71000ca4ac
int command_ret0_ca4ac(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x71000ca4d8
int command_ret0_ca4d8(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x71000ca59c
int command_ret0_ca59c(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x71000ca5bc
int command_ret0_ca5bc(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x71000ca6b8
int command_ret0_ca6b8(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x71000cc910
int command_ret0_cc910(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x71000cc95c
int command_ret0_cc95c(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x71000cca14
int command_ret0_cca14(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x71000cca34
int command_ret0_cca34(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x71000ccb30
int command_ret0_ccb30(CommandTarget* target) {
    target->command();
    return 0;
}

// 0x7100026b78
int command_ret1_26b78(CommandTarget* target) {
    target->command();
    return 1;
}

// 0x7100026b98
int command_ret1_26b98(CommandTarget* target) {
    target->command();
    return 1;
}

// 0x7100026bf0
int command_ret1_26bf0(CommandTarget* target) {
    target->command();
    return 1;
}

// 0x7100026c50
int command_ret1_26c50(CommandTarget* target) {
    target->command();
    return 1;
}

// 0x7100028bfc
int command_ret1_28bfc(CommandTarget* target) {
    target->command();
    return 1;
}

// 0x7100028c34
int command_ret1_28c34(CommandTarget* target) {
    target->command();
    return 1;
}

// 0x7100028c94
int command_ret1_28c94(CommandTarget* target) {
    target->command();
    return 1;
}

// 0x710002a53c
int command_ret1_2a53c(CommandTarget* target) {
    target->command();
    return 1;
}

// 0x710002a574
int command_ret1_2a574(CommandTarget* target) {
    target->command();
    return 1;
}

// 0x710002a5d4
int command_ret1_2a5d4(CommandTarget* target) {
    target->command();
    return 1;
}

// 0x71000ca544
int command_ret1_ca544(CommandTarget* target) {
    target->command();
    return 1;
}

// 0x71000ca57c
int command_ret1_ca57c(CommandTarget* target) {
    target->command();
    return 1;
}

// 0x71000ca5dc
int command_ret1_ca5dc(CommandTarget* target) {
    target->command();
    return 1;
}

// 0x71000cc97c
int command_ret1_cc97c(CommandTarget* target) {
    target->command();
    return 1;
}

// 0x71000cc99c
int command_ret1_cc99c(CommandTarget* target) {
    target->command();
    return 1;
}

// 0x71000cc9f4
int command_ret1_cc9f4(CommandTarget* target) {
    target->command();
    return 1;
}

// 0x71000cca54
int command_ret1_cca54(CommandTarget* target) {
    target->command();
    return 1;
}


void post_command_cf3e4(void* queue, int kind, int result);    // 0x71000cf3e4

void post_command_cf3fc(void* queue, int kind, int result);    // 0x71000cf3fc

void post_command_cf414(void* queue, int kind, int result);    // 0x71000cf414

void post_command_cf394(void* queue, int kind, int result);    // 0x71000cf394

void post_command_cf3bc(void* queue, int kind, int result);    // 0x71000cf3bc

// 0x7100023944
void command_post_23944(CommandTarget* target) {
    unsigned char* queue = target->queue;
    int kind = target->kind;
    post_command_cf3e4(queue, kind, target->command());
}

// 0x710002397c
void command_post_2397c(CommandTarget* target) {
    unsigned char* queue = target->queue;
    int kind = target->kind;
    post_command_cf3fc(queue, kind, target->command());
}

// 0x71000239b4
void command_post_239b4(CommandTarget* target) {
    unsigned char* queue = target->queue;
    int kind = target->kind;
    post_command_cf414(queue, kind, target->command());
}

// 0x7100026a9c
void command_post_26a9c(CommandTarget* target) {
    unsigned char* queue = target->queue;
    int kind = target->kind;
    post_command_cf394(queue, kind, target->command());
}

// 0x7100026ad4
void command_post_26ad4(CommandTarget* target) {
    unsigned char* queue = target->queue;
    int kind = target->kind;
    post_command_cf3bc(queue, kind, target->command());
}

// 0x7100028ae8
void command_post_28ae8(CommandTarget* target) {
    unsigned char* queue = target->queue;
    int kind = target->kind;
    post_command_cf394(queue, kind, target->command());
}

// 0x7100028b20
void command_post_28b20(CommandTarget* target) {
    unsigned char* queue = target->queue;
    int kind = target->kind;
    post_command_cf3bc(queue, kind, target->command());
}

// 0x710002a434
void command_post_2a434(CommandTarget* target) {
    unsigned char* queue = target->queue;
    int kind = target->kind;
    post_command_cf394(queue, kind, target->command());
}

// 0x710002a46c
void command_post_2a46c(CommandTarget* target) {
    unsigned char* queue = target->queue;
    int kind = target->kind;
    post_command_cf3bc(queue, kind, target->command());
}

// 0x71000ca43c
void command_post_ca43c(CommandTarget* target) {
    unsigned char* queue = target->queue;
    int kind = target->kind;
    post_command_cf394(queue, kind, target->command());
}

// 0x71000ca474
void command_post_ca474(CommandTarget* target) {
    unsigned char* queue = target->queue;
    int kind = target->kind;
    post_command_cf3bc(queue, kind, target->command());
}

// 0x71000cc8a0
void command_post_cc8a0(CommandTarget* target) {
    unsigned char* queue = target->queue;
    int kind = target->kind;
    post_command_cf394(queue, kind, target->command());
}

// 0x71000cc8d8
void command_post_cc8d8(CommandTarget* target) {
    unsigned char* queue = target->queue;
    int kind = target->kind;
    post_command_cf3bc(queue, kind, target->command());
}


void post_command_cf8a4(void* queue, int kind, int result);    // 0x71000cf8a4

void post_command_cf8f0(void* queue, int kind, int result);    // 0x71000cf8f0

void post_command_cf644(void* queue, int kind, int result);    // 0x71000cf644

void post_command_cf800(void* queue, int kind, int result);    // 0x71000cf800

void post_command_cf970(void* queue, int kind, int result);    // 0x71000cf970

void post_command_cf9b0(void* queue, int kind, int result);    // 0x71000cf9b0

void post_command_cf930(void* queue, int kind, int result);    // 0x71000cf930

// 0x7100023a80
void command_post_23a80(CommandTarget* target) {
    unsigned char* queue = target->queue_f8;
    int kind = target->kind;
    post_command_cf8a4(queue, kind, target->command());
}

// 0x7100023ab8
void command_post_23ab8(CommandTarget* target) {
    unsigned char* queue = target->queue_f8;
    int kind = target->kind;
    post_command_cf8f0(queue, kind, target->command());
}

// 0x7100023b3c
void command_post_23b3c(CommandTarget* target) {
    unsigned char* queue = target->queue_f8;
    int kind = target->kind;
    post_command_cf644(queue, kind, target->command());
}

// 0x7100023b74
void command_post_23b74(CommandTarget* target) {
    unsigned char* queue = target->queue_f8;
    int kind = target->kind;
    post_command_cf800(queue, kind, target->command());
}

// 0x7100023bac
void command_post_23bac(CommandTarget* target) {
    unsigned char* queue = target->queue_f8;
    int kind = target->kind;
    post_command_cf970(queue, kind, target->command());
}

// 0x7100023be4
void command_post_23be4(CommandTarget* target) {
    unsigned char* queue = target->queue_f8;
    int kind = target->kind;
    post_command_cf9b0(queue, kind, target->command());
}

// 0x7100023c1c
void command_post_23c1c(CommandTarget* target) {
    unsigned char* queue = target->queue_f8;
    int kind = target->kind;
    post_command_cf930(queue, kind, target->command());
}


void post_command_cff20(void* queue, int kind, int result);    // 0x71000cff20

// 0x7100026c90
void command_post_26c90(CommandTarget* target) {
    unsigned char* queue = target->queue_100;
    int kind = target->kind;
    post_command_cff20(queue, kind, target->command());
}

// 0x710002a614
void command_post_2a614(CommandTarget* target) {
    unsigned char* queue = target->queue_100;
    int kind = target->kind;
    post_command_cff20(queue, kind, target->command());
}

// 0x71000ca61c
void command_post_ca61c(CommandTarget* target) {
    unsigned char* queue = target->queue_100;
    int kind = target->kind;
    post_command_cff20(queue, kind, target->command());
}

// 0x71000cca94
void command_post_cca94(CommandTarget* target) {
    unsigned char* queue = target->queue_100;
    int kind = target->kind;
    post_command_cff20(queue, kind, target->command());
}
