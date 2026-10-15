// Work in progress (third session), not a unit: 0x7100038868, the same code as 0x71003e1dec, 0x7100441e94 and
// 0x71003e350c (5,920 bytes each). Compiles to 5,900 bytes; 81 instructions still differ with registers abstracted:
// the dispatch on the node mode (the original falls through into the record allocation and jumps from the
// no-record mode-0 path straight into case 0), the stores of the flag-3 back lists (the original stores the
// list pointer after every entry), the count-table loop addressing and the keep-branch start (start + count - 1
// as an add of 0xffff). Check with tools/s3/try.py docs/s3_wip/38868.cpp 38868 --name _ZN10DrawSorter4sortEPihhh
// --map _Z13setup_counterP11DrawCounter=0x7100583bfc --map _Z11finish_typeP8DrawTypeP10DrawSorter=0x7100583e68

// Bucket sort of draw nodes by a normalised key, then a pass that sends every node's items to per-layer
// front and back lists.

struct DrawItem {
    unsigned char pad0[4];
    short layer;              // +04
};

struct DrawGroup {
    unsigned char pad0[0x14];
    unsigned int front_count; // +14
    unsigned int back_count;  // +18
    unsigned char pad1c[0x14];
    DrawItem* items[1];       // +30
};

struct DrawGroupTable {
    unsigned char pad0[0x10];
    DrawGroup** groups[1];    // +10
};

struct DrawModel {
    unsigned char pad0[0x40];
    DrawGroupTable* table;    // +40
};

struct DrawCounter {
    unsigned short counts[2][8];  // +00
    unsigned short base[2][8];    // +20 (base[0][0] == 0xffff: not set up)
    unsigned short pending[2][8]; // +40
    unsigned char pad60[0x20];
    unsigned short remaining;     // +80
};

struct DrawNode;
struct DrawStats {
    unsigned char pad0[0x9e];
    unsigned short offset;    // +9e
};

struct DrawSorter;
struct DrawType {
    unsigned char pad0[0x78];
    unsigned short default_count; // +78
    unsigned char pad7a[0x16];
    unsigned char (*visible)(void* target, DrawNode* node); // +90
    unsigned char pad98[0x20];
    DrawStats* stats;         // +b8
    unsigned short start[2];  // +c0
    unsigned short size[2];   // +c4
};

struct DrawOwner {
    unsigned char pad0[8];
    unsigned char target[8];  // +08
    DrawModel* model;         // +10
    unsigned char pad18[0x20];
    DrawType* type;           // +38
};

struct DrawSlot {
    unsigned char group;
    unsigned char sub;
};

union DrawId {
    struct {
        DrawSlot slot;
        unsigned short mode;
    };
    unsigned short slot_bits;  // group | sub << 8
    unsigned int bits;         // group | sub << 8 | mode << 16
};

struct DrawNode {
    unsigned int value0;      // +00
    unsigned char b4;         // +04
    unsigned char b5;         // +05
    unsigned char b6;         // +06
    unsigned char b7;         // +07
    DrawId id;                // +08
    float key;                // +0c
    unsigned short value10;   // +10
    short layer;              // +12
    unsigned char pad14[4];
    long value18;             // +18
    DrawCounter* counter;     // +20
    unsigned char pad28[8];
    long matrix[4];           // +30
    DrawOwner* owner;         // +50
    DrawNode* next;           // +58
};

struct DrawRecord {
    long matrix[4];           // +00
    long value20;             // +20
    unsigned short value28;   // +28
    short layer;              // +2a
    short count2c;            // +2c
    short start2e;            // +2e
    short count30;            // +30
    short start32;            // +32
    unsigned char b34;        // +34
    unsigned char b35;        // +35
    unsigned char b36;        // +36
    unsigned char b37;        // +37
    unsigned int value38;     // +38
    unsigned char pad3c[4];
    DrawOwner* owner;         // +40
};

struct DrawEntry {
    DrawItem* item;
    DrawRecord* record;
};

void setup_counter(DrawCounter* counter);                                   // 0x7100583bfc
void finish_type(DrawType* type, DrawSorter* sorter);                       // 0x7100583e68

struct DrawSorter {
    unsigned char pad0[0x10];
    DrawNode** buckets;       // +010
    unsigned int bucket_count; // +018
    int state;                // +01c
    unsigned int counts[2][256];    // +020: front, back
    unsigned int front_total; // +820
    unsigned int back_total;  // +824
    unsigned char pad828[8];
    DrawEntry* entries;       // +830
    DrawRecord* records;      // +838
    unsigned int record_count; // +840
    unsigned char pad844[0x1c];
    long value860;            // +860
    DrawNode* head;           // +868
    float max;                // +870
    float min;                // +874
    unsigned int count;       // +878

    // Puts one node into its bucket (unordered), returns through node the next one.
    void place(DrawNode*& node, float scale) {
        DrawNode* next = node->next;
        float key = scale * (node->key - min);
        unsigned int slot = static_cast<int>(key * static_cast<float>(bucket_count - 1));
        node->key = key;
        node->next = buckets[slot];
        buckets[slot] = node;
        node = next;
    }
    // Inserts one node into its bucket, keeping the bucket ordered by key.
    void insert(DrawNode*& node, float scale) {
        float key = scale * (node->key - min);
        unsigned int slot = static_cast<int>(key * static_cast<float>(bucket_count - 1));
        DrawNode* next = node->next;
        node->key = key;
        DrawNode* at = buckets[slot];
        if (at == nullptr) {
            buckets[slot] = node;
            node->next = nullptr;
        } else {
            DrawNode* prev;
            do {
                prev = at;
                at = prev->next;
            } while (at != nullptr && at->key < key);
            if (prev->key >= key) {
                node->next = prev;
                if (prev == buckets[slot]) {
                    buckets[slot] = node;
                }
            } else {
                node->next = at;
                prev->next = node;
            }
        }
        node = next;
    }
    void sort(int* lengths, unsigned char reverse_back, unsigned char ordered, unsigned char keep);};

#define PLACE4(f) f(node, scale); f(node, scale); f(node, scale); f(node, scale);
#define PLACE16(f) PLACE4(f) PLACE4(f) PLACE4(f) PLACE4(f)

void DrawSorter::sort(int* lengths, unsigned char reverse_back, unsigned char ordered, unsigned char keep) {
    if (state < 0) {
        return;
    }
    DrawNode* node = head;
    if (node != nullptr) {
        float range = max - min;
        float scale = 1.0f / ((range >= -1.1920929e-05f && range <= 1.1920929e-05f) ? max : range);
        unsigned int blocks = count >> 4;
        if (!ordered) {
            for (int i = blocks; i > 0; i--) {
                PLACE16(place)
            }
            for (int i = count & 15; i > 0; i--) {
                place(node, scale);
            }
        } else {
            for (unsigned int i = 0; i < blocks; i++) {
                PLACE16(insert)
            }
            unsigned int rest = count & 15;
            for (unsigned int i = 0; i < rest; i++) {
                insert(node, scale);
            }
        }
    }
    if (lengths != nullptr) {
        for (unsigned int i = 0; i < bucket_count; i++) {
            int length = 0;
            for (DrawNode* at = buckets[i]; at != nullptr; at = at->next) {
                length++;
            }
            lengths[i] = length;
        }
    }
    DrawEntry* front[256];
    DrawEntry* back[256];
    DrawEntry* at_front = entries;
    front[0] = at_front;
    DrawEntry* at_back = entries + front_total + back_total - 1;
    back[255] = at_back;
    for (int i = 0; i < 255; i++) {
        at_front += counts[0][i];
        front[i + 1] = at_front;
        at_back -= counts[1][255 - i];
        back[254 - i] = at_back;
    }
    DrawNode** bucket = buckets;
    for (unsigned int i = 0; i < bucket_count; i++, bucket++) {
        DrawNode* node = *bucket;
        if (node == nullptr) {
            continue;
        }
        do {
            DrawOwner* owner = node->owner;
            DrawCounter* counter = node->counter;
            unsigned short count2c;
            unsigned short start;
            unsigned short count30;
            unsigned short start32;
            unsigned short shift;
            unsigned char visible;
            if (counter == nullptr) {
                if (owner->type == nullptr) {
                    count2c = 0;
                    start = 0;
                    count30 = 0;
                    start32 = 0;
                    shift = 0;
                } else {
                    count2c = owner->type->default_count;
                    start = 0;
                    start32 = 0;
                    shift = 0;
                    count30 = count2c;
                }
                visible = 1;
            } else {
                if (counter->base[0][0] == 0xffff) {
                    setup_counter(counter);
                }
                DrawStats* stats = owner->type->stats;
                if (stats != nullptr && owner->type->size[node->id.slot.group] == 0) {
                    owner->type->start[node->id.slot.group] = stats->offset;
                    unsigned short slot = node->id.slot_bits;
                    owner->type->size[static_cast<unsigned char>(slot)] = node->counter->counts[static_cast<unsigned char>(slot)][slot >> 8];
                    stats->offset += owner->type->size[node->id.slot.group];
                }
                node->counter->counts[node->id.slot.group][node->id.slot.sub]--;
                unsigned short remaining = --node->counter->remaining;
                visible = owner->type->visible(owner->target, node);
                unsigned short pending = node->counter->pending[node->id.slot.group][node->id.slot.sub];
                count2c = pending + 1;
                node->counter->pending[node->id.slot.group][node->id.slot.sub] = count2c;
                if (!visible) {
                    start = 0;
                    count30 = 0;
                    shift = 0;
                } else {
                    start = node->counter->base[node->id.slot.group][node->id.slot.sub];
                    node->counter->base[node->id.slot.group][node->id.slot.sub] = start + count2c;
                    node->counter->pending[node->id.slot.group][node->id.slot.sub] = 0;
                    shift = 0;
                    if (owner->type->stats != nullptr) {
                        owner->type->size[node->id.slot.group] = 0;
                        shift = owner->type->start[node->id.slot.group] - start;
                        owner->type->start[node->id.slot.group] = 0;
                    }
                    node->value18 = 0;
                    count30 = count2c;
                }
                start32 = start;
                if (keep) {
                    start32 = start + pending;
                    node->value18 = 0;
                    if (!visible) {
                        count2c = 0;
                    }
                    count30 = 1;
                }
                if (remaining == 0) {
                    finish_type(owner->type, this);
                }
            }
            unsigned int id = node->id.bits;
            DrawGroup* group = owner->model->table->groups[id & 0xff][(id >> 8) & 0xff];
            unsigned int mode = id >> 16;
            DrawRecord* record = nullptr;
            DrawRecord* shown = nullptr;
            if (visible || (keep && (mode == 1 || (mode == 0 && group->back_count != 0)))) {
                record = records + record_count;
                record_count++;
                record->matrix[0] = node->matrix[0];
                record->matrix[1] = node->matrix[1];
                record->matrix[2] = node->matrix[2];
                record->matrix[3] = node->matrix[3];
                record->value20 = node->value18;
                record->value28 = node->value10;
                record->layer = node->layer;
                record->start2e = shift + start;
                record->owner = owner;
                record->count2c = count2c;
                record->count30 = count30;
                record->start32 = start32 + shift;
                record->b34 = node->b4;
                record->b35 = node->b5;
                record->b36 = node->b6;
                record->value38 = node->value0;
                record->b37 = node->b7;
                mode = node->id.mode;
                shown = visible ? record : nullptr;
            }
            int layer = node->layer;
            switch (mode) {
            case 0: {
                int front_count = group->front_count;
                for (int k = 0; k < front_count; k++) {
                    DrawItem* item = group->items[k];
                    DrawEntry*& slot = front[item->layer + layer];
                    slot->item = item;
                    slot->record = shown;
                    slot++;
                }
                unsigned int first = group->front_count;
                unsigned int total = first + group->back_count;
                for (int k = total; k > static_cast<int>(first); k--) {
                    DrawItem* item = group->items[k - 1];
                    DrawEntry*& slot = back[reverse_back ? 0xffu : static_cast<unsigned int>(item->layer + layer)];
                    slot->item = item;
                    slot->record = record;
                    slot--;
                }
                break;
            }
            case 1: {
                int total = group->front_count + group->back_count;
                for (int k = total - 1; k >= 0; k--) {
                    DrawItem* item = group->items[k];
                    DrawEntry*& slot = back[reverse_back ? 0xffu : static_cast<unsigned int>(item->layer + layer)];
                    slot->item = item;
                    slot->record = record;
                    slot--;
                }
                break;
            }
            case 2: {
                unsigned int total = group->front_count + group->back_count;
                for (unsigned int k = 0; k < total; k++) {
                    DrawItem* item = group->items[k];
                    DrawEntry*& slot = front[item->layer + layer];
                    slot->item = item;
                    slot->record = shown;
                    slot++;
                }
                break;
            }
            }
            node = node->next;
        } while (node != nullptr);
        *bucket = nullptr;
    }
    state = -1;
    value860 = 0;
}
