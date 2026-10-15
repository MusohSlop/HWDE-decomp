// Named blob writes (0x71005710a8, 0x71005711e0): hash the name, find the entry by its first or
// second hash, ask the store for the entry's info and, if the sizes agree, copy the data in and mark
// the entry dirty. Names are descriptive placeholders. Status: matching/README.md.

struct BlobInfo {
    unsigned char pad[0x20];
    unsigned int size;        // +20
    unsigned char pad24[4];
};

struct BlobQuery;
unsigned char query_info_5790c4(BlobQuery* query, int id, BlobInfo* info); // 0x71005790c4

struct BlobStore {
    unsigned char pad[0x20];
    BlobQuery* query;         // +20

    unsigned char info(int id, BlobInfo* info) { return query_info_5790c4(query, id, info); }
};

struct BlobEntry {
    unsigned int hashes[2];   // +00
    int id;                   // +08
    unsigned char pad0c[8];
    unsigned char dirty;      // +14
    unsigned char pad15[3];
    BlobEntry* next;          // +18
    unsigned char data[1];    // +20
};

struct BlobTable {
    unsigned char pad[0x30];
    BlobEntry* head;          // +30
    unsigned char pad38[0x10];
    BlobStore* store;         // +48
};

extern "C" void* memcpy(void* dest, const void* source, unsigned long size);

static inline void copy_bytes(unsigned char* dest, const unsigned char* source, unsigned int size) {
    if (size <= 3) {
        for (unsigned int i = 0; i < size; ++i)
            dest[i] = source[i];
    } else {
        memcpy(dest, source, size);
    }
}

static inline unsigned int hash_name(const unsigned char* name) {
    if (!name)
        return 0;
    unsigned int hash = name[0];
    unsigned long factor = 1;
    for (unsigned int i = 0; name[i]; ++i) {
        factor = static_cast<unsigned int>(factor) * 31UL;
        hash += name[i] * factor;
    }
    return hash;
}
// 0x71005710a8
unsigned char write_blob_5710a8(BlobTable* table, const unsigned char* name, const unsigned char* data,
                               unsigned int size) {
    unsigned int hash = hash_name(name);
    for (BlobEntry* entry = table->head; entry; entry = entry->next) {
        if (entry->hashes[0] == hash) {
            BlobInfo info;
            if (!table->store->info(entry->id, &info) || info.size != size)
                return 0;
            copy_bytes(entry->data, data, size);
            entry->dirty = 1;
            return 1;
        }
    }
    return 0;
}
// 0x71005711e0
unsigned char write_blob_5711e0(BlobTable* table, const unsigned char* name, const unsigned char* data,
                               unsigned int size) {
    unsigned int hash = hash_name(name);
    for (BlobEntry* entry = table->head; entry; entry = entry->next) {
        if (entry->hashes[1] == hash) {
            BlobInfo info;
            if (!table->store->info(entry->id, &info) || info.size != size)
                return 0;
            copy_bytes(entry->data, data, size);
            entry->dirty = 1;
            return 1;
        }
    }
    return 0;
}
