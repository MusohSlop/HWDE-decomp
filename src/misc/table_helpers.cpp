// Helpers next to the object tables (0x71002471dc-0x7100248638): a four-column row append, a
// descriptor-tagged allocation through an owner's allocator and a mode-dependent stop. Names are
// descriptive placeholders. Status: matching/README.md.

struct FourColumns {
    unsigned char pad[0x10];
    int count;                // +10
    unsigned char pad14[4];
    int first[8];             // +18
    int second[8];            // +38
    int third[8];             // +58
    int fourth[8];            // +78
};

// 0x71002471dc
void add_row_2471dc(FourColumns* table, int row, int a, int b, int c, int d) {
    table->first[row] = a;
    table->second[row] = b;
    table->third[row] = c;
    table->fourth[row] = d;
    ++table->count;
}

struct BlockDesc {
    BlockDesc(unsigned short value) : kind(value), flags(0), extra(0) {}

    unsigned short kind;      // +00
    unsigned short flags;     // +02
    long extra;               // +08
};

struct BlockAllocator {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void* alloc(unsigned long size, const BlockDesc& desc);
};

struct BlockOwner {
    unsigned char pad[0xc0];
    BlockAllocator* allocator; // +c0
};

// 0x7100247200
void* alloc_block_247200(BlockOwner* owner, unsigned int size) {
    return owner->allocator->alloc(size, BlockDesc(0x2e));
}

struct SoundHandle;
void stop_sound_2563c0(SoundHandle* handle);                                // 0x71002563c0
void stop_stream_256418(SoundHandle* handle);                               // 0x7100256418

struct SoundSlot {
    unsigned char pad[0x38];
    SoundHandle* handle;      // +38
    unsigned char pad40[0x48];
    int mode;                 // +88
    int active;               // +8c
};

// 0x7100248638
void stop_slot_248638(SoundSlot* slot) {
    if (!slot->active)
        return;
    switch (slot->mode) {
    case 0:
    case 5:
        stop_sound_2563c0(slot->handle);
        break;
    default:
        stop_stream_256418(slot->handle);
        break;
    }
    slot->active = 0;
}