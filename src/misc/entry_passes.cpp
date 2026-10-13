// Per-entry passes over a record list found by tools/family_scan.py --immediates: each walks the
// list through its virtual count and accessor and runs one handler on a part of every entry, passing
// the index and the caller's argument. They differ only in the part and the handler; types and
// functions are named after their address. Status: matching/README.md.

struct ListEntry;

class RecordList {
public:
    virtual void v00();
    virtual void v08();
    virtual ListEntry* entry(unsigned int index);                          // +10
    virtual unsigned int count();                                          // +18
};

struct EntryPart20dd84;
void handle_entry_part_20ca64(EntryPart20dd84* part, unsigned int index, void* arg); // 0x710020ca64

// 0x710020dd84: part at +4c
void for_each_entry_20dd84(RecordList* list, void* arg) {
    for (unsigned int i = 0; i < list->count(); ++i)
        handle_entry_part_20ca64(reinterpret_cast<EntryPart20dd84*>(reinterpret_cast<unsigned char*>(list->entry(i)) + 0x4c), i, arg);
}

struct EntryPart20de00;
void handle_entry_part_20cb40(EntryPart20de00* part, unsigned int index, void* arg); // 0x710020cb40

// 0x710020de00: part at +64
void for_each_entry_20de00(RecordList* list, void* arg) {
    for (unsigned int i = 0; i < list->count(); ++i)
        handle_entry_part_20cb40(reinterpret_cast<EntryPart20de00*>(reinterpret_cast<unsigned char*>(list->entry(i)) + 0x64), i, arg);
}

struct EntryPart20de7c;
void handle_entry_part_20cff8(EntryPart20de7c* part, unsigned int index, void* arg); // 0x710020cff8

// 0x710020de7c: part at +1fc
void for_each_entry_20de7c(RecordList* list, void* arg) {
    for (unsigned int i = 0; i < list->count(); ++i)
        handle_entry_part_20cff8(reinterpret_cast<EntryPart20de7c*>(reinterpret_cast<unsigned char*>(list->entry(i)) + 0x1fc), i, arg);
}
