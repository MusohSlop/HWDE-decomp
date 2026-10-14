// Phase list passes (0x710001fa08-0x710001fcbc): pick one of the owner's four null-terminated item
// lists by phase and run one step on every item in it. Found by tools/family_scan.py. Names are
// descriptive placeholders. Status: matching/README.md.

struct PhaseItem;

struct PhaseLists {
    unsigned char pad[0x6eb0];
    PhaseItem* setup[0x173];   // +6eb0
    PhaseItem* update[0x3e];   // +7a48
    PhaseItem* render[0x47];   // +7c38
    PhaseItem* cleanup[1];     // +7e70
};
void begin_item_18a70(PhaseItem* item);                                         // 0x7100018a70

// 0x710001fa08
void begin_phase_1fa08(PhaseLists* lists, unsigned int phase) {
    PhaseItem** list;
    switch (phase) {
    case 0:
        list = lists->setup;
        break;
    case 1:
        list = lists->update;
        break;
    case 2:
        list = lists->render;
        break;
    case 3:
        list = lists->cleanup;
        break;
    default:
        list = nullptr;
        break;
    }
    for (; *list; ++list)
        begin_item_18a70(*list);
}
void step_item_18fb0(PhaseItem* item);                                         // 0x7100018fb0

// 0x710001fab8
void step_phase_1fab8(PhaseLists* lists, unsigned int phase) {
    PhaseItem** list;
    switch (phase) {
    case 0:
        list = lists->setup;
        break;
    case 1:
        list = lists->update;
        break;
    case 2:
        list = lists->render;
        break;
    case 3:
        list = lists->cleanup;
        break;
    default:
        list = nullptr;
        break;
    }
    for (; *list; ++list)
        step_item_18fb0(*list);
}
void finish_item_18ef0(PhaseItem* item);                                         // 0x7100018ef0

// 0x710001fb68
void finish_phase_1fb68(PhaseLists* lists, unsigned int phase) {
    PhaseItem** list;
    switch (phase) {
    case 0:
        list = lists->setup;
        break;
    case 1:
        list = lists->update;
        break;
    case 2:
        list = lists->render;
        break;
    case 3:
        list = lists->cleanup;
        break;
    default:
        list = nullptr;
        break;
    }
    for (; *list; ++list)
        finish_item_18ef0(*list);
}
void reset_item_19368(PhaseItem* item);                                         // 0x7100019368

// 0x710001fcbc
void reset_phase_1fcbc(PhaseLists* lists, unsigned int phase) {
    PhaseItem** list;
    switch (phase) {
    case 0:
        list = lists->setup;
        break;
    case 1:
        list = lists->update;
        break;
    case 2:
        list = lists->render;
        break;
    case 3:
        list = lists->cleanup;
        break;
    default:
        list = nullptr;
        break;
    }
    for (; *list; ++list)
        reset_item_19368(*list);
}

extern "C" void* memset(void* dest, int value, unsigned long size);

struct PendingItem;
void release_item_ddb4(PendingItem* item);                                  // 0x710000ddb4

struct PendingLists {
    unsigned char pad[0xdc48];
    PendingItem* pending[0x173]; // +dc48
    unsigned char pade7e0[0x1576];
    bool clearing;               // +fd56
};

// 0x710001fc50
void clear_pending_1fc50(PendingLists* lists) {
    lists->clearing = true;
    for (PendingItem** item = lists->pending; *item; ++item)
        release_item_ddb4(*item);
    memset(lists->pending, 0, sizeof(lists->pending));
    lists->clearing = false;
}

struct FrameCounters {
    unsigned char pad[0x23ac4];
    int shown;                   // +23ac4
    int current;                 // +23ac8
};

// 0x710001fd34
void sync_counter_1fd34(FrameCounters* counters) {
    counters->shown = counters->current;
}