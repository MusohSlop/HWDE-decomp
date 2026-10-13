// Item-definition fields found by tools/family_scan.py --immediates: each returns one 16-bit field
// of an item's definition (the 0x50-byte records behind gItemDefs), reading from address zero for an
// out-of-range item like the original. They differ only in the field (and its type); functions are named after
// their address. Status: matching/README.md.

union ItemDefFields {
    short values[0x28];
    unsigned short unsigned_values[0x28];
    int words[0x14];
    signed char bytes[0x50];
};
static_assert(sizeof(ItemDefFields) == 0x50, "item def size");
class ItemDefTable {
public:
    ItemDefFields* find(int item) {
        return static_cast<unsigned int>(item) < 0x44c ? &defs[item] : nullptr;
    }

    ItemDefFields defs[0x44c];
};
// Reached through the GOT slot at 0x7100c216a0.
extern ItemDefTable* gItemDefs;

// 0x710021139c: field +4
int item_field_21139c(int item) {
    return gItemDefs->find(item)->values[2];
}

// 0x71002113c0: field +6
int item_field_2113c0(int item) {
    return gItemDefs->find(item)->values[3];
}

// 0x71002113e4: field +8
int item_field_2113e4(int item) {
    return gItemDefs->find(item)->values[4];
}

// 0x7100211408: field +a
int item_field_211408(int item) {
    return gItemDefs->find(item)->values[5];
}

// 0x710021142c: field +c
int item_field_21142c(int item) {
    return gItemDefs->find(item)->values[6];
}

// 0x7100211450: field +10
int item_field_211450(int item) {
    return gItemDefs->find(item)->values[8];
}

// 0x7100211530: field +32
int item_field_211530(int item) {
    return gItemDefs->find(item)->values[25];
}

// 0x710021159c: field +12
int item_field_21159c(int item) {
    return gItemDefs->find(item)->values[9];
}

// 0x71002115c0: field +42
int item_field_2115c0(int item) {
    return gItemDefs->find(item)->values[33];
}

// 0x71002115e4: field +44
int item_field_2115e4(int item) {
    return gItemDefs->find(item)->values[34];
}

// 0x7100211608: field +46
int item_field_211608(int item) {
    return gItemDefs->find(item)->values[35];
}

// 0x710021162c: field +48
int item_field_21162c(int item) {
    return gItemDefs->find(item)->values[36];
}

// 0x7100211650: field +4a
int item_field_211650(int item) {
    return gItemDefs->find(item)->values[37];
}

// 0x7100211674: field +4c
int item_field_211674(int item) {
    return gItemDefs->find(item)->values[38];
}

// 0x7100211698: field +4e
int item_field_211698(int item) {
    return gItemDefs->find(item)->values[39];
}

// 0x7100211474: field +1c
int item_field_211474(int item) {
    return gItemDefs->find(item)->words[0x7];
}

// 0x7100211498: field +28
unsigned short item_field_211498(int item) {
    return gItemDefs->find(item)->unsigned_values[0x14];
}

// 0x71002114bc: field +2a
unsigned short item_field_2114bc(int item) {
    return gItemDefs->find(item)->unsigned_values[0x15];
}

// 0x71002114e0: field +2c
unsigned short item_field_2114e0(int item) {
    return gItemDefs->find(item)->unsigned_values[0x16];
}

// 0x710021150c: field +30
unsigned short item_field_21150c(int item) {
    return gItemDefs->find(item)->unsigned_values[0x18];
}

// 0x7100211554: field +36
int item_field_211554(int item) {
    return gItemDefs->find(item)->bytes[0x36];
}

// 0x7100211578: field +37
int item_field_211578(int item) {
    return gItemDefs->find(item)->bytes[0x37];
}
