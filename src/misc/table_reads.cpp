// Small table reads found by tools/family_scan.py --immediates: range-checked byte and 16-bit
// fields (zero past the end), signed byte and 16-bit ids with an id limit (-1 past it), and byte
// fields of the record a handle names. Each group differs only in its limits and offsets; types and
// functions are named after their address. Status: matching/README.md.

struct ByteTable6ad7c {
    unsigned char pad[0x640];
    unsigned char values[1];  // +640
};

// 0x710006ad7c
unsigned char byte_at_6ad7c(ByteTable6ad7c* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x44b)
        return table->values[index];
    return 0;
}

struct ByteTable205510 {
    unsigned char pad[0x46];
    unsigned char values[1];  // +46
};

// 0x7100205510
unsigned char byte_at_205510(ByteTable205510* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x6)
        return table->values[index];
    return 0;
}

struct ByteTable20552c {
    unsigned char pad[0x4d];
    unsigned char values[1];  // +4d
};

// 0x710020552c
unsigned char byte_at_20552c(ByteTable20552c* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x6)
        return table->values[index];
    return 0;
}

struct ByteTable205568 {
    unsigned char pad[0x661];
    unsigned char values[1];  // +661
};

// 0x7100205568
unsigned char byte_at_205568(ByteTable205568* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x3)
        return table->values[index];
    return 0;
}

struct ByteTable205584 {
    unsigned char pad[0x665];
    unsigned char values[1];  // +665
};

// 0x7100205584
unsigned char byte_at_205584(ByteTable205584* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x3)
        return table->values[index];
    return 0;
}

struct ByteTable2055a0 {
    unsigned char pad[0x669];
    unsigned char values[1];  // +669
};

// 0x71002055a0
unsigned char byte_at_2055a0(ByteTable2055a0* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x3)
        return table->values[index];
    return 0;
}

struct ByteTable2055bc {
    unsigned char pad[0x66d];
    unsigned char values[1];  // +66d
};

// 0x71002055bc
unsigned char byte_at_2055bc(ByteTable2055bc* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x3)
        return table->values[index];
    return 0;
}

struct ByteTable20a0f8 {
    unsigned char pad[0xc];
    unsigned char values[1];  // +c
};

// 0x710020a0f8
unsigned char byte_at_20a0f8(ByteTable20a0f8* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x3)
        return table->values[index];
    return 0;
}

struct ByteTable210488 {
    unsigned char pad[0xb4];
    unsigned char values[1];  // +b4
};

// 0x7100210488
unsigned char byte_at_210488(ByteTable210488* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x59)
        return table->values[index];
    return 0;
}

struct ByteTable3eda44 {
    unsigned char pad[0x2a0];
    unsigned char values[1];  // +2a0
};

// 0x71003eda44
unsigned char byte_at_3eda44(ByteTable3eda44* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x1)
        return table->values[index];
    return 0;
}

struct ShortTabled8908 {
    unsigned char pad[0xf0];
    short values[1];  // +f0
};

// 0x71000d8908
int short_at_d8908(ShortTabled8908* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x77)
        return table->values[index];
    return 0;
}

struct ShortTabled8924 {
    unsigned char pad[0x1e0];
    short values[1];  // +1e0
};

// 0x71000d8924
int short_at_d8924(ShortTabled8924* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x77)
        return table->values[index];
    return 0;
}

struct ShortTabled8940 {
    unsigned char pad[0x2d0];
    short values[1];  // +2d0
};

// 0x71000d8940
int short_at_d8940(ShortTabled8940* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x77)
        return table->values[index];
    return 0;
}

struct ShortTabled895c {
    unsigned char pad[0x5a0];
    short values[1];  // +5a0
};

// 0x71000d895c
int short_at_d895c(ShortTabled895c* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x77)
        return table->values[index];
    return 0;
}

struct ShortTabled8978 {
    unsigned char pad[0x690];
    short values[1];  // +690
};

// 0x71000d8978
int short_at_d8978(ShortTabled8978* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x77)
        return table->values[index];
    return 0;
}

struct ShortTabled8994 {
    unsigned char pad[0x780];
    short values[1];  // +780
};

// 0x71000d8994
int short_at_d8994(ShortTabled8994* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x77)
        return table->values[index];
    return 0;
}

struct ShortTable20b56c {
    unsigned char pad[0xa];
    short values[1];  // +a
};

// 0x710020b56c
int short_at_20b56c(ShortTable20b56c* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x4)
        return table->values[index];
    return 0;
}

struct ShortTable20b588 {
    unsigned char pad[0x14];
    short values[1];  // +14
};

// 0x710020b588
int short_at_20b588(ShortTable20b588* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x4)
        return table->values[index];
    return 0;
}

struct ShortTable20b948 {
    unsigned char pad[0x380];
    short values[1];  // +380
};

// 0x710020b948
int short_at_20b948(ShortTable20b948* table, int index) {
    if (static_cast<unsigned int>(index) <= 0x3f)
        return table->values[index];
    return 0;
}

struct ByteId1fe640 {
    unsigned char pad[0x4];
    signed char id;  // +4
};

// 0x71001fe640: ids below 0x3
int byte_id_1fe640(ByteId1fe640* record) {
    signed char id = record->id;
    return static_cast<unsigned char>(id) < 0x3 ? id : -1;
}

struct ByteId1fe654 {
    unsigned char pad[0x5];
    signed char id;  // +5
};

// 0x71001fe654: ids below 0x19
int byte_id_1fe654(ByteId1fe654* record) {
    signed char id = record->id;
    return static_cast<unsigned char>(id) < 0x19 ? id : -1;
}

struct ByteId2034bc {
    unsigned char pad[0x148];
    signed char id;  // +148
};

// 0x71002034bc: ids below 0x4
int byte_id_2034bc(ByteId2034bc* record) {
    signed char id = record->id;
    return static_cast<unsigned char>(id) < 0x4 ? id : -1;
}

struct ByteId203618 {
    unsigned char pad[0x149];
    signed char id;  // +149
};

// 0x7100203618: ids below 0x4
int byte_id_203618(ByteId203618* record) {
    signed char id = record->id;
    return static_cast<unsigned char>(id) < 0x4 ? id : -1;
}

struct ByteId20d8f4 {
    unsigned char pad[0x10];
    signed char id;  // +10
};

// 0x710020d8f4: ids below 0x64
int byte_id_20d8f4(ByteId20d8f4* record) {
    signed char id = record->id;
    return static_cast<unsigned char>(id) < 0x64 ? id : -1;
}

struct ByteId20d908 {
    unsigned char pad[0x11];
    signed char id;  // +11
};

// 0x710020d908: ids below 0x20
int byte_id_20d908(ByteId20d908* record) {
    signed char id = record->id;
    return static_cast<unsigned char>(id) < 0x20 ? id : -1;
}

struct ByteId213f00 {
    unsigned char pad[0x4];
    signed char id;  // +4
};

// 0x7100213f00: ids below 0x40
int byte_id_213f00(ByteId213f00* record) {
    signed char id = record->id;
    return static_cast<unsigned char>(id) < 0x40 ? id : -1;
}

struct ByteId213f8c {
    unsigned char pad[0x4];
    signed char id;  // +4
};

// 0x7100213f8c: ids below 0x6
int byte_id_213f8c(ByteId213f8c* record) {
    signed char id = record->id;
    return static_cast<unsigned char>(id) < 0x6 ? id : -1;
}

struct ByteId213fa0 {
    unsigned char pad[0x5];
    signed char id;  // +5
};

// 0x7100213fa0: ids below 0x5
int byte_id_213fa0(ByteId213fa0* record) {
    signed char id = record->id;
    return static_cast<unsigned char>(id) < 0x5 ? id : -1;
}

struct ByteId214550 {
    unsigned char pad[0x5];
    signed char id;  // +5
};

// 0x7100214550: ids below 0x64
int byte_id_214550(ByteId214550* record) {
    signed char id = record->id;
    return static_cast<unsigned char>(id) < 0x64 ? id : -1;
}

struct ByteId214564 {
    unsigned char pad[0x6];
    signed char id;  // +6
};

// 0x7100214564: ids below 0x5
int byte_id_214564(ByteId214564* record) {
    signed char id = record->id;
    return static_cast<unsigned char>(id) < 0x5 ? id : -1;
}

struct IdRow201e20 {
    unsigned char pad[0x8];
    short id;                 // +8
    unsigned char pada[0x3e];
};

// 0x7100201e20: rows up to 0x20, ids below 0x12c
int row_id_201e20(IdRow201e20* rows, int row) {
    if (static_cast<unsigned int>(row) <= 0x20) {
        short id = rows[row].id;
        return static_cast<unsigned short>(id) < 0x12c ? id : -1;
    }
    return -1;
}

struct IdRow201e5c {
    unsigned char pad[0xa];
    short id;                 // +a
    unsigned char padc[0x3c];
};

// 0x7100201e5c: rows up to 0x20, ids below 0x4
int row_id_201e5c(IdRow201e5c* rows, int row) {
    if (static_cast<unsigned int>(row) <= 0x20) {
        short id = rows[row].id;
        return static_cast<unsigned short>(id) < 0x4 ? id : -1;
    }
    return -1;
}

struct IdRow201e88 {
    unsigned char pad[0xc];
    short id;                 // +c
    unsigned char pade[0x3a];
};

// 0x7100201e88: rows up to 0x20, ids below 0x5
int row_id_201e88(IdRow201e88* rows, int row) {
    if (static_cast<unsigned int>(row) <= 0x20) {
        short id = rows[row].id;
        return static_cast<unsigned short>(id) < 0x5 ? id : -1;
    }
    return -1;
}

struct IdRow201eb4 {
    unsigned char pad[0x10];
    short id;                 // +10
    unsigned char pad12[0x36];
};

// 0x7100201eb4: rows up to 0x20, ids below 0x2e4
int row_id_201eb4(IdRow201eb4* rows, int row) {
    if (static_cast<unsigned int>(row) <= 0x20) {
        short id = rows[row].id;
        return static_cast<unsigned short>(id) < 0x2e4 ? id : -1;
    }
    return -1;
}

struct HandleRecord {
    unsigned char bytes[0xc0];
};
// Reached through the GOT slot at 0x7100c23268.
extern HandleRecord* gSingleton_c23268;
struct RecordHandle {
    int index;
};

// 0x7100206648: byte 1
unsigned char handle_byte_206648(RecordHandle* handle) {
    HandleRecord* records = gSingleton_c23268;
    return records[handle->index].bytes[1];
}

// 0x710020666c: byte 2
unsigned char handle_byte_20666c(RecordHandle* handle) {
    HandleRecord* records = gSingleton_c23268;
    return records[handle->index].bytes[2];
}

// 0x7100206690: byte 5
unsigned char handle_byte_206690(RecordHandle* handle) {
    HandleRecord* records = gSingleton_c23268;
    return records[handle->index].bytes[5];
}

// 0x71002066b4: byte 3
unsigned char handle_byte_2066b4(RecordHandle* handle) {
    HandleRecord* records = gSingleton_c23268;
    return records[handle->index].bytes[3];
}

// 0x71002066d8: byte 4
unsigned char handle_byte_2066d8(RecordHandle* handle) {
    HandleRecord* records = gSingleton_c23268;
    return records[handle->index].bytes[4];
}
