// More command posts found by tools/family_scan.py --immediates (the shape of command_post_23944 in
// misc/command_handlers.cpp): each posts the target's kind and its command's result to one of the
// target's queues. They differ only in the queue and the post function; functions are named after
// their address. Status: matching/README.md.

class CommandSource {
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
    unsigned char pad26[0xe2];
    unsigned char queue_108[8]; // +108
    unsigned char queue_110[0x40]; // +110
    unsigned char queue_150[8]; // +150
};

void post_command_cff20(void* queue, int kind, int result);    // 0x71000cff20
void post_command_d0178(void* queue, int kind, int result);    // 0x71000d0178
void post_command_d0474(void* queue, int kind, int result);    // 0x71000d0474

// 0x7100023cc4
void command_post_23cc4(CommandSource* target) {
    unsigned char* queue = target->queue_108;
    int kind = target->kind;
    post_command_cff20(queue, kind, target->command());
}

// 0x7100023de4
void command_post_23de4(CommandSource* target) {
    unsigned char* queue = target->queue_108;
    int kind = target->kind;
    post_command_d0178(queue, kind, target->command());
}

// 0x7100026fac
void command_post_26fac(CommandSource* target) {
    unsigned char* queue = target->queue_150;
    int kind = target->kind;
    post_command_d0474(queue, kind, target->command());
}

// 0x7100028cd4
void command_post_28cd4(CommandSource* target) {
    unsigned char* queue = target->queue_110;
    int kind = target->kind;
    post_command_cff20(queue, kind, target->command());
}

// 0x71000ccdb0
void command_post_ccdb0(CommandSource* target) {
    unsigned char* queue = target->queue_150;
    int kind = target->kind;
    post_command_d0474(queue, kind, target->command());
}
