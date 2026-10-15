// Stacked layouts (0x710059ade8-0x710059bb80): each layout places five fixed parts and up to five
// optional parts one after another, each at the running sum of the earlier parts' sizes. When
// neither the key nor the dirty state changed, a keyed layout keeps its placement and an unkeyed
// one re-places only the optional parts. The six layouts are separate classes with their own part
// types. Found by tools/family_scan.py --immediates. Names are descriptive placeholders. Status:
// matching/README.md.

struct LayoutKey {
    unsigned long id;         // +00
};

struct LayoutOwner59ade8 {
    unsigned char pad[0x48];
    unsigned long current;    // +48
};
void notify_owner_52c97c(LayoutOwner59ade8* owner, unsigned long id);     // 0x710052c97c

struct LayoutPart59ade8 {
    unsigned char pad[0x58];
    int size;                 // +58
};
void place_part_5a4848(LayoutPart59ade8* part, LayoutKey* key, int offset, bool dirty); // 0x71005a4848
void place_last_5a86c8(LayoutPart59ade8* part, LayoutKey* key, int offset, bool dirty); // 0x71005a86c8

struct Layout59ade8 {
    unsigned char pad[0x10];
    LayoutOwner59ade8* owner; // +10
    unsigned char pad18[0x10];
    LayoutKey* key;           // +28
    unsigned char pad30[0x38];
    LayoutPart59ade8* fixed[5];    // +68
    unsigned char pad90[8];
    LayoutPart59ade8* optional[5]; // +98
    unsigned char padc0[0x63];
    bool dirty;               // +123
};

// 0x710059ade8
void update_layout_59ade8(Layout59ade8* layout, LayoutKey* key) {
    LayoutKey* old = layout->key;
    unsigned long current = old ? old->id : 0;
    bool dirty = layout->dirty ? true : layout->owner->current != current;
    LayoutPart59ade8* part0 = layout->fixed[0];
    LayoutPart59ade8* part1 = layout->fixed[1];
    LayoutPart59ade8* part2 = layout->fixed[2];
    LayoutPart59ade8* part3 = layout->fixed[3];
    LayoutPart59ade8* part4 = layout->fixed[4];
    layout->dirty = false;
    bool unchanged = old == key ? !dirty : false;
    if (unchanged) {
        if (!key) {
            int offset = part0->size + part1->size + part2->size + part3->size + part4->size;
            for (int i = 0; i < 5; ++i) {
                if (layout->optional[i]) {
                    place_part_5a4848(layout->optional[i], nullptr, offset, false);
                    offset += layout->optional[i]->size;
                }
            }
        }
    } else {
        int offset1 = part0->size;
        int offset2 = offset1 + part1->size;
        int offset3 = offset2 + part2->size;
        int offset4 = offset3 + part3->size;
        int offset = offset4 + part4->size;
        place_part_5a4848(part0, key, 0, dirty);
        place_part_5a4848(part1, key, offset1, dirty);
        place_part_5a4848(part2, key, offset2, dirty);
        place_part_5a4848(part3, key, offset3, dirty);
        place_last_5a86c8(part4, key, offset4, dirty);
        for (int i = 0; i < 5; ++i) {
            if (layout->optional[i]) {
                place_part_5a4848(layout->optional[i], key, offset, dirty);
                offset += layout->optional[i]->size;
            }
        }
    }
    unsigned long id = key ? key->id : 0;
    layout->key = key;
    notify_owner_52c97c(layout->owner, id);
}
