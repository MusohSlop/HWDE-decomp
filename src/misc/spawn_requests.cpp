// Spawn requests (0x71001bfdfc-0x71001c00b4): copy a request into a message, resolving its five unit
// ids (aliases 0x79-0x7c through the current roster, family ids 0x50-0x5f by the active
// difficulty step), and hand it to the post state. Found by tools/family_scan.py. Names are
// descriptive placeholders. Status: matching/README.md.

struct RosterSlot {
    unsigned char pad[0x1c];
    int unit;                 // +1c
};

struct RosterTable {
    unsigned char pad[0xb18];
    RosterSlot* slots[4];     // +b18
};

struct StepInfo {
    unsigned char pad[4];
    int step;                 // +04
};

struct StepOwner {
    unsigned char pad[0x139948];
    StepInfo* info;           // +139948
};

// Reached through the GOT slot at 0x7100c21698.
extern RosterTable* gRecord_c21698;
// Reached through the GOT slot at 0x7100c22ca8.
extern StepOwner* gGlobal_c22ca8;

static inline int resolve_unit(int id) {
    if (id == 0x78)
        return 0x78;
    int alias = id - 0x79;
    if (static_cast<unsigned int>(alias) <= 3)
        id = gRecord_c21698->slots[alias]->unit;
    StepInfo* info = gGlobal_c22ca8->info;
    if (info && info->step && (id & ~0xf) == 0x50)
        id += info->step * 5 - 5;
    return id;
}

struct SpawnPair {
    int a;
    int b;
};

struct SpawnRequest {
    int pad0;
    int kind;                 // +04
    int units[5];             // +08
    SpawnPair pair;           // +1c
    int c;                    // +24
    int d;                    // +28
};

struct SpawnMessage {
    int kind;                 // +00
    int units[5];             // +04
    SpawnPair pair;           // +18
    int c;                    // +20
    int d;                    // +24
    unsigned char pad28[8];
};

struct Container18d5d8;
struct PostState;
PostState* member_18d5d8(Container18d5d8* container);                       // 0x710018d5d8
// Reached through the GOT slot at 0x7100c216e8.
extern Container18d5d8* gShop;
void post_spawn_1a5e80(PostState* state, SpawnMessage* message);               // 0x71001a5e80
void post_spawn_1a61b4(PostState* state, SpawnMessage* message);               // 0x71001a61b4
void post_spawn_1a63fc(PostState* state, SpawnMessage* message);               // 0x71001a63fc
void post_spawn_1a65bc(PostState* state, SpawnMessage* message);               // 0x71001a65bc

// 0x71001bfdfc
void request_spawn_1bfdfc(const SpawnRequest* request) {
    SpawnMessage message;
    message.kind = request->kind;
    for (int i = 0; i < 5; ++i) {
        message.units[i] = request->units[i];
        message.units[i] = resolve_unit(request->units[i]);
    }
    message.pair = request->pair;
    message.c = request->c;
    message.d = request->d;
    post_spawn_1a5e80(member_18d5d8(gShop), &message);
}
// 0x71001bfee4
void request_spawn_1bfee4(const SpawnRequest* request) {
    SpawnMessage message;
    message.kind = request->kind;
    for (int i = 0; i < 5; ++i) {
        message.units[i] = request->units[i];
        message.units[i] = resolve_unit(request->units[i]);
    }
    message.pair = request->pair;
    message.c = request->c;
    message.d = request->d;
    post_spawn_1a61b4(member_18d5d8(gShop), &message);
}
// 0x71001bffcc
void request_spawn_1bffcc(const SpawnRequest* request) {
    SpawnMessage message;
    message.kind = request->kind;
    for (int i = 0; i < 5; ++i) {
        message.units[i] = request->units[i];
        message.units[i] = resolve_unit(request->units[i]);
    }
    message.pair = request->pair;
    message.c = request->c;
    message.d = request->d;
    post_spawn_1a63fc(member_18d5d8(gShop), &message);
}
// 0x71001c00b4
void request_spawn_1c00b4(const SpawnRequest* request) {
    SpawnMessage message;
    message.kind = request->kind;
    for (int i = 0; i < 5; ++i) {
        message.units[i] = request->units[i];
        message.units[i] = resolve_unit(request->units[i]);
    }
    message.pair = request->pair;
    message.c = request->c;
    message.d = request->d;
    post_spawn_1a65bc(member_18d5d8(gShop), &message);
}
