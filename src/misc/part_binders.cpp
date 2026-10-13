// The per-part binders behind misc/part_binding.cpp (0x710059c560-0x710059cb00, found by
// tools/family_scan.py --immediates): each resolves the part's selected items into the context's
// entry table, starting at the given entry. They differ only in which slot of each item they test
// and which resolver they call; functions are named after their address. Status: matching/README.md.

struct BindItem {
    void* resource;
    unsigned char pad[8];
};
struct BindChunk {
    BindChunk* next;
    unsigned int start;       // +08
    BindItem* items;          // +10
};
struct BindPartEntry {
    unsigned char pad[0x1e];
    short slots[6];           // +1e
    unsigned char pad2a[0x56];
};
struct BindPart {
    unsigned char pad[0x40];
    BindChunk* chunks;        // +40
    unsigned char pad48[0xc];
    unsigned int item_count;  // +54
    unsigned int counts[6];   // +58
    struct Entries {
        BindPartEntry& operator[](unsigned long i) { return items[i]; }
        BindPartEntry items[1];
    } entries;                // +70
};
struct BindEntry {
    unsigned int id;
    unsigned int packed;      // +4
    unsigned short index;     // +8
};
struct BindContext {
    void* handle;
    unsigned int capacity;    // +08
    BindEntry entries[1];     // +0c
};

unsigned int resolve_item_527cbc(void* handle, void* resource); // 0x7100527cbc

// 0x710059c560: slot 0
unsigned char bind_part_59c560(BindContext* context, BindPart* part, unsigned int start, long mask) {
    unsigned int count = part->item_count;
    BindPart::Entries& entries = part->entries;
    BindChunk* head = reinterpret_cast<BindChunk*>(&part->chunks);
    for (unsigned long i = 0; i < count; mask >>= 1, ++i) {
        if (!(mask & 1) || entries[i].slots[0] < 0)
            continue;
        BindChunk* chunk = head;
        do
            chunk = chunk->next;
        while (i < chunk->start);
        if (start >= context->capacity)
            return false;
        unsigned int id = resolve_item_527cbc(context->handle,
                                  chunk->items[static_cast<unsigned int>(i) - chunk->start].resource);
        context->entries[start].id = id;
        unsigned int packed = 0;
        unsigned int index = 0;
        if (id) {
            packed = (id & 0xf000ffff) | 0x10000;
            index = (id >> 16) & 0xfff;
        }
        context->entries[start].packed = packed;
        context->entries[start].index = index;
        ++start;
    }
    return true;
}

unsigned int resolve_item_527ba4(void* handle, void* resource); // 0x7100527ba4

// 0x710059c650: slot 1
unsigned char bind_part_59c650(BindContext* context, BindPart* part, unsigned int start, long mask) {
    unsigned int count = part->item_count;
    BindPart::Entries& entries = part->entries;
    BindChunk* head = reinterpret_cast<BindChunk*>(&part->chunks);
    for (unsigned long i = 0; i < count; mask >>= 1, ++i) {
        if (!(mask & 1) || entries[i].slots[1] < 0)
            continue;
        BindChunk* chunk = head;
        do
            chunk = chunk->next;
        while (i < chunk->start);
        if (start >= context->capacity)
            return false;
        unsigned int id = resolve_item_527ba4(context->handle,
                                  chunk->items[static_cast<unsigned int>(i) - chunk->start].resource);
        context->entries[start].id = id;
        unsigned int packed = 0;
        unsigned int index = 0;
        if (id) {
            packed = (id & 0xf000ffff) | 0x10000;
            index = (id >> 16) & 0xfff;
        }
        context->entries[start].packed = packed;
        context->entries[start].index = index;
        ++start;
    }
    return true;
}

unsigned int resolve_item_5326c8(void* handle, void* resource); // 0x71005326c8

// 0x710059c740: slot 2
unsigned char bind_part_59c740(BindContext* context, BindPart* part, unsigned int start, long mask) {
    unsigned int count = part->item_count;
    BindPart::Entries& entries = part->entries;
    BindChunk* head = reinterpret_cast<BindChunk*>(&part->chunks);
    for (unsigned long i = 0; i < count; mask >>= 1, ++i) {
        if (!(mask & 1) || entries[i].slots[2] < 0)
            continue;
        BindChunk* chunk = head;
        do
            chunk = chunk->next;
        while (i < chunk->start);
        if (start >= context->capacity)
            return false;
        unsigned int id = resolve_item_5326c8(context->handle,
                                  chunk->items[static_cast<unsigned int>(i) - chunk->start].resource);
        context->entries[start].id = id;
        unsigned int packed = 0;
        unsigned int index = 0;
        if (id) {
            packed = (id & 0xf000ffff) | 0x10000;
            index = (id >> 16) & 0xfff;
        }
        context->entries[start].packed = packed;
        context->entries[start].index = index;
        ++start;
    }
    return true;
}

unsigned int resolve_item_5326c8(void* handle, void* resource); // 0x71005326c8

// 0x710059c830: slot 3
unsigned char bind_part_59c830(BindContext* context, BindPart* part, unsigned int start, long mask) {
    unsigned int count = part->item_count;
    BindPart::Entries& entries = part->entries;
    BindChunk* head = reinterpret_cast<BindChunk*>(&part->chunks);
    for (unsigned long i = 0; i < count; mask >>= 1, ++i) {
        if (!(mask & 1) || entries[i].slots[3] < 0)
            continue;
        BindChunk* chunk = head;
        do
            chunk = chunk->next;
        while (i < chunk->start);
        if (start >= context->capacity)
            return false;
        unsigned int id = resolve_item_5326c8(context->handle,
                                  chunk->items[static_cast<unsigned int>(i) - chunk->start].resource);
        context->entries[start].id = id;
        unsigned int packed = 0;
        unsigned int index = 0;
        if (id) {
            packed = (id & 0xf000ffff) | 0x10000;
            index = (id >> 16) & 0xfff;
        }
        context->entries[start].packed = packed;
        context->entries[start].index = index;
        ++start;
    }
    return true;
}

unsigned int resolve_item_527ad4(void* handle, void* resource); // 0x7100527ad4

// 0x710059c920: slot 4
unsigned char bind_part_59c920(BindContext* context, BindPart* part, unsigned int start, long mask) {
    unsigned int count = part->item_count;
    BindPart::Entries& entries = part->entries;
    BindChunk* head = reinterpret_cast<BindChunk*>(&part->chunks);
    for (unsigned long i = 0; i < count; mask >>= 1, ++i) {
        if (!(mask & 1) || entries[i].slots[4] < 0)
            continue;
        BindChunk* chunk = head;
        do
            chunk = chunk->next;
        while (i < chunk->start);
        if (start >= context->capacity)
            return false;
        unsigned int id = resolve_item_527ad4(context->handle,
                                  chunk->items[static_cast<unsigned int>(i) - chunk->start].resource);
        context->entries[start].id = id;
        unsigned int packed = 0;
        unsigned int index = 0;
        if (id) {
            packed = (id & 0xf000ffff) | 0x10000;
            index = (id >> 16) & 0xfff;
        }
        context->entries[start].packed = packed;
        context->entries[start].index = index;
        ++start;
    }
    return true;
}

unsigned int resolve_item_5326c8(void* handle, void* resource); // 0x71005326c8

// 0x710059ca10: slot 5
unsigned char bind_part_59ca10(BindContext* context, BindPart* part, unsigned int start, long mask) {
    unsigned int count = part->item_count;
    BindPart::Entries& entries = part->entries;
    BindChunk* head = reinterpret_cast<BindChunk*>(&part->chunks);
    for (unsigned long i = 0; i < count; mask >>= 1, ++i) {
        if (!(mask & 1) || entries[i].slots[5] < 0)
            continue;
        BindChunk* chunk = head;
        do
            chunk = chunk->next;
        while (i < chunk->start);
        if (start >= context->capacity)
            return false;
        unsigned int id = resolve_item_5326c8(context->handle,
                                  chunk->items[static_cast<unsigned int>(i) - chunk->start].resource);
        context->entries[start].id = id;
        unsigned int packed = 0;
        unsigned int index = 0;
        if (id) {
            packed = (id & 0xf000ffff) | 0x10000;
            index = (id >> 16) & 0xfff;
        }
        context->entries[start].packed = packed;
        context->entries[start].index = index;
        ++start;
    }
    return true;
}
