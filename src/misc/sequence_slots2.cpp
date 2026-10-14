// More sequenced slot plays (the shape of misc/sequence_slots.cpp, identical code apart from the
// callee): one group also sets the second channel's volume before starting, the other starts the
// sequence on layer 1 with the looping flag. Functions are named after their address.
// Status: matching/README.md.

struct RenderTarget;
// Reached through the GOT slot at 0x7100c21db0.
extern RenderTarget* gRenderTarget;
void reset_channel_52a87c(RenderTarget* target, int channel);               // 0x710052a87c
void reset_layer_52a778(RenderTarget* target, int channel, int layer);      // 0x710052a778
void set_volume_52a984(RenderTarget* target, int channel, int volume);      // 0x710052a984

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

struct VoiceSlots {
    unsigned char pad[8];
    void* resources[9];       // +08
    unsigned int ids[9];      // +50
};
struct LoopSlots {
    unsigned char pad[0x20];
    void* resources[7];       // +20
    unsigned char pad58[4];
    unsigned int ids[9];      // +5c
};

void play_sequence_3b64c(void* player, unsigned int id, void* resource, PlayParams* params, int mode); // 0x710003b64c

// 0x71003d74d0
void play_voice_slot_3d74d0(VoiceSlots* slots, unsigned int slot) {
    unsigned int id = slots->ids[slot];
    if (!id)
        return;
    RenderTarget* target = gRenderTarget;
    reset_channel_52a87c(target, 1);
    set_volume_52a984(target, 4, 100);
    reset_layer_52a778(target, 0, 0);
    PlayParams params;
    params.flags = 0;
    play_sequence_3b64c(gSequencer->player, id, slots->resources[slot], &params, 0);
}

void play_sequence_3d7f04(void* player, unsigned int id, void* resource, PlayParams* params, int mode); // 0x71003d7f04

// 0x71003d7cd0
void play_voice_slot_3d7cd0(VoiceSlots* slots, unsigned int slot) {
    unsigned int id = slots->ids[slot];
    if (!id)
        return;
    RenderTarget* target = gRenderTarget;
    reset_channel_52a87c(target, 1);
    set_volume_52a984(target, 4, 100);
    reset_layer_52a778(target, 0, 0);
    PlayParams params;
    params.flags = 0;
    play_sequence_3d7f04(gSequencer->player, id, slots->resources[slot], &params, 0);
}

void play_sequence_3d9078(void* player, unsigned int id, void* resource, PlayParams* params, int mode); // 0x71003d9078

// 0x71003d8e44
void play_voice_slot_3d8e44(VoiceSlots* slots, unsigned int slot) {
    unsigned int id = slots->ids[slot];
    if (!id)
        return;
    RenderTarget* target = gRenderTarget;
    reset_channel_52a87c(target, 1);
    set_volume_52a984(target, 4, 100);
    reset_layer_52a778(target, 0, 0);
    PlayParams params;
    params.flags = 0;
    play_sequence_3d9078(gSequencer->player, id, slots->resources[slot], &params, 0);
}

void play_sequence_3da0f4(void* player, unsigned int id, void* resource, PlayParams* params, int mode); // 0x71003da0f4

// 0x71003d9ec0
void play_voice_slot_3d9ec0(VoiceSlots* slots, unsigned int slot) {
    unsigned int id = slots->ids[slot];
    if (!id)
        return;
    RenderTarget* target = gRenderTarget;
    reset_channel_52a87c(target, 1);
    set_volume_52a984(target, 4, 100);
    reset_layer_52a778(target, 0, 0);
    PlayParams params;
    params.flags = 0;
    play_sequence_3da0f4(gSequencer->player, id, slots->resources[slot], &params, 0);
}


// 0x71003d7570
void play_loop_slot_3d7570(LoopSlots* slots, unsigned int slot) {
    unsigned int id = slots->ids[slot];
    if (!id)
        return;
    RenderTarget* target = gRenderTarget;
    reset_channel_52a87c(target, 1);
    reset_layer_52a778(target, 0, 1);
    PlayParams params;
    params.flags = 1;
    play_sequence_3b64c(gSequencer->player, id, slots->resources[slot], &params, 0);
}


// 0x71003d7d70
void play_loop_slot_3d7d70(LoopSlots* slots, unsigned int slot) {
    unsigned int id = slots->ids[slot];
    if (!id)
        return;
    RenderTarget* target = gRenderTarget;
    reset_channel_52a87c(target, 1);
    reset_layer_52a778(target, 0, 1);
    PlayParams params;
    params.flags = 1;
    play_sequence_3d7f04(gSequencer->player, id, slots->resources[slot], &params, 0);
}


// 0x71003d8ee4
void play_loop_slot_3d8ee4(LoopSlots* slots, unsigned int slot) {
    unsigned int id = slots->ids[slot];
    if (!id)
        return;
    RenderTarget* target = gRenderTarget;
    reset_channel_52a87c(target, 1);
    reset_layer_52a778(target, 0, 1);
    PlayParams params;
    params.flags = 1;
    play_sequence_3d9078(gSequencer->player, id, slots->resources[slot], &params, 0);
}


// 0x71003d9f60
void play_loop_slot_3d9f60(LoopSlots* slots, unsigned int slot) {
    unsigned int id = slots->ids[slot];
    if (!id)
        return;
    RenderTarget* target = gRenderTarget;
    reset_channel_52a87c(target, 1);
    reset_layer_52a778(target, 0, 1);
    PlayParams params;
    params.flags = 1;
    play_sequence_3da0f4(gSequencer->player, id, slots->resources[slot], &params, 0);
}
