// Sequenced slot plays found by tools/family_scan.py (identical code apart from the callee): each
// takes the slot's sequence id and, when it has one, resets the render target's two channels and
// starts the sequence through the sequencer's player with the slot's resource. Functions are named
// after their address. Status: matching/README.md.

struct RenderTarget;
// Reached through the GOT slot at 0x7100c21db0.
extern RenderTarget* gRenderTarget;
void reset_channel_52a87c(RenderTarget* target, int channel);               // 0x710052a87c
void reset_layer_52a778(RenderTarget* target, int channel, int layer);      // 0x710052a778

struct Sequencer {
    unsigned char pad[0x68];
    void* player;             // +68
};
// Reached through the GOT slot at 0x7100c21880.
extern Sequencer* gSequencer;

struct PlayParams {
    unsigned char data[0x4c];
    int flags;                // +4c
};

struct SequenceSlots {
    unsigned char pad[8];
    void* resources[9];       // +08
    unsigned int ids[9];      // +50
};

void play_sequence_3b64c(void* player, unsigned int id, void* resource, PlayParams* params, int mode); // 0x710003b64c

// 0x71003d7440
void play_slot_3d7440(SequenceSlots* slots, unsigned int slot) {
    unsigned int id = slots->ids[slot];
    if (!id)
        return;
    RenderTarget* target = gRenderTarget;
    reset_channel_52a87c(target, 0);
    reset_layer_52a778(target, 0, 0);
    PlayParams params;
    params.flags = 0;
    play_sequence_3b64c(gSequencer->player, id, slots->resources[slot], &params, 0);
}

void play_sequence_3d7708(void* player, unsigned int id, void* resource, PlayParams* params, int mode); // 0x71003d7708

// 0x71003d760c
void play_slot_3d760c(SequenceSlots* slots, unsigned int slot) {
    unsigned int id = slots->ids[slot];
    if (!id)
        return;
    RenderTarget* target = gRenderTarget;
    reset_channel_52a87c(target, 0);
    reset_layer_52a778(target, 0, 0);
    PlayParams params;
    params.flags = 0;
    play_sequence_3d7708(gSequencer->player, id, slots->resources[slot], &params, 0);
}

void play_sequence_3d7f04(void* player, unsigned int id, void* resource, PlayParams* params, int mode); // 0x71003d7f04

// 0x71003d7c40
void play_slot_3d7c40(SequenceSlots* slots, unsigned int slot) {
    unsigned int id = slots->ids[slot];
    if (!id)
        return;
    RenderTarget* target = gRenderTarget;
    reset_channel_52a87c(target, 0);
    reset_layer_52a778(target, 0, 0);
    PlayParams params;
    params.flags = 0;
    play_sequence_3d7f04(gSequencer->player, id, slots->resources[slot], &params, 0);
}

void play_sequence_3d887c(void* player, unsigned int id, void* resource, PlayParams* params, int mode); // 0x71003d887c

// 0x71003d7e0c
void play_slot_3d7e0c(SequenceSlots* slots, unsigned int slot) {
    unsigned int id = slots->ids[slot];
    if (!id)
        return;
    RenderTarget* target = gRenderTarget;
    reset_channel_52a87c(target, 0);
    reset_layer_52a778(target, 0, 0);
    PlayParams params;
    params.flags = 0;
    play_sequence_3d887c(gSequencer->player, id, slots->resources[slot], &params, 0);
}

void play_sequence_3d9078(void* player, unsigned int id, void* resource, PlayParams* params, int mode); // 0x71003d9078

// 0x71003d8db4
void play_slot_3d8db4(SequenceSlots* slots, unsigned int slot) {
    unsigned int id = slots->ids[slot];
    if (!id)
        return;
    RenderTarget* target = gRenderTarget;
    reset_channel_52a87c(target, 0);
    reset_layer_52a778(target, 0, 0);
    PlayParams params;
    params.flags = 0;
    play_sequence_3d9078(gSequencer->player, id, slots->resources[slot], &params, 0);
}

void play_sequence_3d98f8(void* player, unsigned int id, void* resource, PlayParams* params, int mode); // 0x71003d98f8

// 0x71003d8f80
void play_slot_3d8f80(SequenceSlots* slots, unsigned int slot) {
    unsigned int id = slots->ids[slot];
    if (!id)
        return;
    RenderTarget* target = gRenderTarget;
    reset_channel_52a87c(target, 0);
    reset_layer_52a778(target, 0, 0);
    PlayParams params;
    params.flags = 0;
    play_sequence_3d98f8(gSequencer->player, id, slots->resources[slot], &params, 0);
}

void play_sequence_3da0f4(void* player, unsigned int id, void* resource, PlayParams* params, int mode); // 0x71003da0f4

// 0x71003d9e30
void play_slot_3d9e30(SequenceSlots* slots, unsigned int slot) {
    unsigned int id = slots->ids[slot];
    if (!id)
        return;
    RenderTarget* target = gRenderTarget;
    reset_channel_52a87c(target, 0);
    reset_layer_52a778(target, 0, 0);
    PlayParams params;
    params.flags = 0;
    play_sequence_3da0f4(gSequencer->player, id, slots->resources[slot], &params, 0);
}

void play_sequence_3dab18(void* player, unsigned int id, void* resource, PlayParams* params, int mode); // 0x71003dab18

// 0x71003d9ffc
void play_slot_3d9ffc(SequenceSlots* slots, unsigned int slot) {
    unsigned int id = slots->ids[slot];
    if (!id)
        return;
    RenderTarget* target = gRenderTarget;
    reset_channel_52a87c(target, 0);
    reset_layer_52a778(target, 0, 0);
    PlayParams params;
    params.flags = 0;
    play_sequence_3dab18(gSequencer->player, id, slots->resources[slot], &params, 0);
}
