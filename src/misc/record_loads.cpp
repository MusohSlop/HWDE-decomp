// Record table loads (0x7100249494, 0x71002495e8): read a resource's first entry as 22-byte records
// into a table allocated from the owner's allocator; the second field of each record is stored as
// a running end (start + length). Found by tools/family_scan.py --immediates. Names are descriptive
// placeholders. Status: matching/README.md.

#include "resource/resource_frame.h"

struct RecordDesc {
    RecordDesc(unsigned short value) : kind(value), flags(0), extra(0) {}

    unsigned short kind;      // +00
    unsigned short flags;     // +02
    long extra;               // +08
};

struct RecordAllocator {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void* alloc(unsigned int size, const RecordDesc& desc);

    void* alloc_records(unsigned int size) {
        return alloc(size, RecordDesc(0x2e));
    }
};

struct Record22 {
    unsigned short start;     // +00
    unsigned short end;       // +02
    unsigned short values[9]; // +04
};

struct RecordTable {
    unsigned int first;       // +00
    unsigned int count;       // +04
    Record22* records;        // +08
    unsigned char pad10[8];
};

struct RecordOwner {
    unsigned char pad[0x120];
    RecordAllocator* allocator; // +120
    unsigned char pad128[0x18];
    RecordTable tables[2];      // +140
};
// 0x7100249494
void load_records_249494(RecordOwner* owner, void* storage) {
    ResourceFrame frame;
    frame.bind(0, storage);
    unsigned int size = frame.entry_size(0);
    unsigned int count = size / sizeof(Record22);
    RecordTable& table = owner->tables[0];
    table.first = 0;
    table.count = count;
    const Record22* source = static_cast<const Record22*>(frame.lookup(0));
    table.records = static_cast<Record22*>(owner->allocator->alloc_records(count * sizeof(Record22)));
    for (unsigned int j = 0; j < count; ++j) {
        Record22& record = table.records[j];
        record.start = source[j].start;
        record.end = source[j].start + source[j].end;
        record.values[0] = source[j].values[0];
        record.values[1] = source[j].values[1];
        record.values[2] = source[j].values[2];
        record.values[3] = source[j].values[3];
        record.values[4] = source[j].values[4];
        record.values[5] = source[j].values[5];
        record.values[6] = source[j].values[6];
        record.values[7] = source[j].values[7];
        record.values[8] = source[j].values[8];
    }
    frame.close();
}
// 0x71002495e8
void load_records_2495e8(RecordOwner* owner, void* storage) {
    ResourceFrame frame;
    frame.bind(0, storage);
    unsigned int size = frame.entry_size(0);
    unsigned int count = size / sizeof(Record22);
    RecordTable& table = owner->tables[1];
    table.first = 0;
    table.count = count;
    const Record22* source = static_cast<const Record22*>(frame.lookup(0));
    table.records = static_cast<Record22*>(owner->allocator->alloc_records(count * sizeof(Record22)));
    for (unsigned int j = 0; j < count; ++j) {
        Record22& record = table.records[j];
        record.start = source[j].start;
        record.end = source[j].start + source[j].end;
        record.values[0] = source[j].values[0];
        record.values[1] = source[j].values[1];
        record.values[2] = source[j].values[2];
        record.values[3] = source[j].values[3];
        record.values[4] = source[j].values[4];
        record.values[5] = source[j].values[5];
        record.values[6] = source[j].values[6];
        record.values[7] = source[j].values[7];
        record.values[8] = source[j].values[8];
    }
    frame.close();
}
