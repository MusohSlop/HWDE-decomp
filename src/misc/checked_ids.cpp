// Range-checked ids found by tools/family_scan.py --immediates: each returns a 16-bit id field of
// its record, or -1 when the id is past the table's end. They differ only in the field and the
// limit; types and functions are named after their address. Status: matching/README.md.

struct IdRecord1fe2b4 {
    unsigned char pad[0x2];
    short id;                 // +2
};

// 0x71001fe2b4: ids below 0x44c
int checked_id_1fe2b4(IdRecord1fe2b4* record) {
    short id = record->id;
    return static_cast<unsigned short>(id) < 0x44c ? id : -1;
}

struct IdRecord1fe2c8 {
    unsigned char pad[0x4];
    short id;                 // +4
};

// 0x71001fe2c8: ids below 0x96
int checked_id_1fe2c8(IdRecord1fe2c8* record) {
    short id = record->id;
    return static_cast<unsigned short>(id) < 0x96 ? id : -1;
}

struct IdRecord1fe678 {
    unsigned char pad[0xa];
    short id;                 // +a
};

// 0x71001fe678: ids below 0x4b
int checked_id_1fe678(IdRecord1fe678* record) {
    short id = record->id;
    return static_cast<unsigned short>(id) < 0x4b ? id : -1;
}

struct IdRecord1ff960 {
    unsigned char pad[0x26];
    short id;                 // +26
};

// 0x71001ff960: ids below 0x40
int checked_id_1ff960(IdRecord1ff960* record) {
    short id = record->id;
    return static_cast<unsigned short>(id) < 0x40 ? id : -1;
}

struct IdRecord2003e8 {
    unsigned char pad[0x1c];
    short id;                 // +1c
};

// 0x71002003e8: ids below 0x406
int checked_id_2003e8(IdRecord2003e8* record) {
    short id = record->id;
    return static_cast<unsigned short>(id) < 0x406 ? id : -1;
}

struct IdRecord20175c {
    unsigned char pad[0x4];
    short id;                 // +4
};

// 0x710020175c: ids below 0x12c
int checked_id_20175c(IdRecord20175c* record) {
    short id = record->id;
    return static_cast<unsigned short>(id) < 0x12c ? id : -1;
}

struct IdRecord201770 {
    unsigned char pad[0x6];
    short id;                 // +6
};

// 0x7100201770: ids below 0x4
int checked_id_201770(IdRecord201770* record) {
    short id = record->id;
    return static_cast<unsigned short>(id) < 0x4 ? id : -1;
}

struct IdRecord201784 {
    unsigned char pad[0x8];
    short id;                 // +8
};

// 0x7100201784: ids below 0x5
int checked_id_201784(IdRecord201784* record) {
    short id = record->id;
    return static_cast<unsigned short>(id) < 0x5 ? id : -1;
}

struct IdRecord201798 {
    unsigned char pad[0xa];
    short id;                 // +a
};

// 0x7100201798: ids below 0x21
int checked_id_201798(IdRecord201798* record) {
    short id = record->id;
    return static_cast<unsigned short>(id) < 0x21 ? id : -1;
}

struct IdRecord2017ac {
    unsigned char pad[0xc];
    short id;                 // +c
};

// 0x71002017ac: ids below 0x2e4
int checked_id_2017ac(IdRecord2017ac* record) {
    short id = record->id;
    return static_cast<unsigned short>(id) < 0x2e4 ? id : -1;
}

struct IdRecord202114 {
    short id;                 // +0
};

// 0x7100202114: ids below 0x64
int checked_id_202114(IdRecord202114* record) {
    short id = record->id;
    return static_cast<unsigned short>(id) < 0x64 ? id : -1;
}

struct IdRecord2034e0 {
    unsigned char pad[0x14a];
    short id;                 // +14a
};

// 0x71002034e0: ids below 0x12c
int checked_id_2034e0(IdRecord2034e0* record) {
    short id = record->id;
    return static_cast<unsigned short>(id) < 0x12c ? id : -1;
}

struct IdRecord20363c {
    unsigned char pad[0x15c];
    short id;                 // +15c
};

// 0x710020363c: ids below 0x12c
int checked_id_20363c(IdRecord20363c* record) {
    short id = record->id;
    return static_cast<unsigned short>(id) < 0x12c ? id : -1;
}

struct IdRecord209ffc {
    unsigned char pad[0x4];
    short id;                 // +4
};

// 0x7100209ffc: ids below 0x46
int checked_id_209ffc(IdRecord209ffc* record) {
    short id = record->id;
    return static_cast<unsigned short>(id) < 0x46 ? id : -1;
}

struct IdRecord20a0b8 {
    unsigned char pad[0x12];
    short id;                 // +12
};

// 0x710020a0b8: ids below 0x406
int checked_id_20a0b8(IdRecord20a0b8* record) {
    short id = record->id;
    return static_cast<unsigned short>(id) < 0x406 ? id : -1;
}

struct IdRecord20a0dc {
    unsigned char pad[0x8];
    short id;                 // +8
};

// 0x710020a0dc: ids below 0x46
int checked_id_20a0dc(IdRecord20a0dc* record) {
    short id = record->id;
    return static_cast<unsigned short>(id) < 0x46 ? id : -1;
}

struct IdRecord20a134 {
    unsigned char pad[0x14];
    short id;                 // +14
};

// 0x710020a134: ids below 0x80
int checked_id_20a134(IdRecord20a134* record) {
    short id = record->id;
    return static_cast<unsigned short>(id) < 0x80 ? id : -1;
}

struct IdRecord20eed8 {
    unsigned char pad[0x4];
    short id;                 // +4
};

// 0x710020eed8: ids below 0x12c
int checked_id_20eed8(IdRecord20eed8* record) {
    short id = record->id;
    return static_cast<unsigned short>(id) < 0x12c ? id : -1;
}

struct IdRecord20eeec {
    unsigned char pad[0x6];
    short id;                 // +6
};

// 0x710020eeec: ids below 0x46
int checked_id_20eeec(IdRecord20eeec* record) {
    short id = record->id;
    return static_cast<unsigned short>(id) < 0x46 ? id : -1;
}
