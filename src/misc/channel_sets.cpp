// Float setters (0x7100243fe0-0x710024440c): when the global stage is ready the value goes to the
// stage's channel table, otherwise to every channel of the object's own list with a fixed kind.
// Found by tools/family_scan.py --immediates. Names are descriptive placeholders; addresses are in
// the comments. Status: matching/README.md.

struct Stage23b9;

struct Channel4a2e {
    void set(int kind, float value);                                        // 0x71004a2e00

    unsigned char data[0xf0];
};

struct ChannelList {
    unsigned char pad[0x64];
    unsigned int count;       // +64
    unsigned char pad68[8];
    Channel4a2e channels[1];  // +70
};

struct ChannelOwner {
    unsigned char pad[0x28];
    ChannelList* list;        // +28
};

struct Stage23b9 {
    unsigned char pad[0x1ed80];
    unsigned char channels[1]; // +1ed80
};

// Reached through the GOT slot at 0x7100c21708.
extern Stage23b9* gGlobal_c21708;
unsigned char stage_ready_23b9a4(Stage23b9* stage);                         // 0x710023b9a4
void stage_set_2409e0(void* channels, ChannelOwner* owner, float value);       // 0x71002409e0
void stage_set_240cc0(void* channels, ChannelOwner* owner, float value);       // 0x7100240cc0
void stage_set_240d78(void* channels, ChannelOwner* owner, float value);       // 0x7100240d78
void stage_set_240e30(void* channels, ChannelOwner* owner, float value);       // 0x7100240e30

// 0x7100243fe0
void set_channels_243fe0(ChannelOwner* owner, float value) {
    if (stage_ready_23b9a4(gGlobal_c21708)) {
        stage_set_2409e0(gGlobal_c21708->channels, owner, value);
        return;
    }
    ChannelList* list = owner->list;
    if (!list)
        return;
    for (unsigned int i = 0; i < list->count; ++i)
        list->channels[i].set(5, value);
}
// 0x71002442a4
void set_channels_2442a4(ChannelOwner* owner, float value) {
    if (stage_ready_23b9a4(gGlobal_c21708)) {
        stage_set_240cc0(gGlobal_c21708->channels, owner, value);
        return;
    }
    ChannelList* list = owner->list;
    if (!list)
        return;
    for (unsigned int i = 0; i < list->count; ++i)
        list->channels[i].set(9, value);
}
// 0x7100244358
void set_channels_244358(ChannelOwner* owner, float value) {
    if (stage_ready_23b9a4(gGlobal_c21708)) {
        stage_set_240d78(gGlobal_c21708->channels, owner, value);
        return;
    }
    ChannelList* list = owner->list;
    if (!list)
        return;
    for (unsigned int i = 0; i < list->count; ++i)
        list->channels[i].set(10, value);
}
// 0x710024440c
void set_channels_24440c(ChannelOwner* owner, float value) {
    if (stage_ready_23b9a4(gGlobal_c21708)) {
        stage_set_240e30(gGlobal_c21708->channels, owner, value);
        return;
    }
    ChannelList* list = owner->list;
    if (!list)
        return;
    for (unsigned int i = 0; i < list->count; ++i)
        list->channels[i].set(11, value);
}