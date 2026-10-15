// A slot table's load (fourth session, template family 11a81c): fourteen 0x88-byte entries bound to resources 22,
// 21 down to 10, and 23 of the global resource set, each marked loaded (flag 0x80). The original has two identical
// copies (0x710011a81c, 0x710011ae90), written as one template with a dummy copy number. Names are descriptive
// placeholders.

struct ResourceSet {
    void* context;            // +0
};
// Reached through the GOT slot at 0x7100c22a10.
extern ResourceSet* gResourceSet;
void* resource_11a81c(ResourceSet* set, int id);                            // 0x71000db39c

struct SlotView {
    int bind(void* resource, void* context);                                // 0x71001f0df4
    unsigned char pad0[8];
    unsigned int flags;       // +08
    unsigned char padc[0x74];
};

struct SlotEntry {
    unsigned char pad0[8];
    SlotView view;            // +08
};

class SlotTable {
public:
    template <int Copy> void load();

    int head;                 // +00
    int count4;               // +04
    int count8;               // +08
    unsigned char padc[4];
    SlotEntry entries[14];    // +10
};

template <int Copy>
void SlotTable::load() {
    count4 = 0;
    count8 = 0;
    entries[0].view.bind(resource_11a81c(gResourceSet, 0x16), gResourceSet->context);
    entries[0].view.flags |= 0x80;
    for (int i = 0; i < 12; i++) {
        entries[i + 1].view.bind(resource_11a81c(gResourceSet, 0x15 - i), gResourceSet->context);
        entries[i + 1].view.flags |= 0x80;
    }
    entries[13].view.bind(resource_11a81c(gResourceSet, 0x17), gResourceSet->context);
    entries[13].view.flags |= 0x80;
}

template void SlotTable::load<0>();
template void SlotTable::load<1>();
