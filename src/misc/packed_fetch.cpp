// Packed-entry fetches found by tools/family_scan.py --immediates: each copies one entry of a
// packed archive's table (offset and size pairs in the header) into the caller's buffer, reading it
// from the archive's file first when the archive streams. They differ only in which table offset
// they use; functions are named after their address. Status: matching/README.md.

class FileSystem {
public:
    int seek(void* handle, unsigned long position, int origin, unsigned long* result, int flags); // 0x71005374c4
    int read(void* handle, void* buffer, unsigned long size, unsigned long* result, int flags);   // 0x71005374b4
};
struct ObjectManager {
    unsigned char pad[0xc8];
    FileSystem* file_system;  // +c8
};
extern ObjectManager* gObjectManager;

void* copy_entry(void* dest, const void* source, unsigned long size); // 0x7100517e9c

struct PackedEntry {
    unsigned int offset;
    unsigned int size;
};

struct PackedArchive {
    unsigned char pad[0x18];
    void* file;               // +18
    unsigned char* data;      // +20
    unsigned char pad28[8];
    unsigned char header[0x98]; // +30
    unsigned int tables[0x15];  // +c8
    unsigned int base_unused;
};

// 0x71005968d0: table at +c8
void* fetch_entry_5968d0(PackedArchive* archive, void* dest, unsigned int index) {
    if (!archive->data)
        return nullptr;
    const PackedEntry* entry =
        reinterpret_cast<const PackedEntry*>(&archive->header[archive->tables[0]]) + index;
    const unsigned int* fields = &entry->offset;
    unsigned int offset = *fields;
    unsigned int size = fields[1];
    if (!archive->file)
        return copy_entry(dest, archive->data + offset, size);
    FileSystem* fs = gObjectManager->file_system;
    if (fs->seek(archive->file, archive->tables[6] + offset, 0, nullptr, 0))
        return nullptr;
    unsigned long count;
    if (fs->read(archive->file, archive->data, size, &count, 0) == 0 && count == size)
        return copy_entry(dest, archive->data, size);
    return nullptr;
}

// 0x71005969bc: table at +cc
void* fetch_entry_5969bc(PackedArchive* archive, void* dest, unsigned int index) {
    if (!archive->data)
        return nullptr;
    const PackedEntry* entry =
        reinterpret_cast<const PackedEntry*>(&archive->header[archive->tables[1]]) + index;
    const unsigned int* fields = &entry->offset;
    unsigned int offset = *fields;
    unsigned int size = fields[1];
    if (!archive->file)
        return copy_entry(dest, archive->data + offset, size);
    FileSystem* fs = gObjectManager->file_system;
    if (fs->seek(archive->file, archive->tables[6] + offset, 0, nullptr, 0))
        return nullptr;
    unsigned long count;
    if (fs->read(archive->file, archive->data, size, &count, 0) == 0 && count == size)
        return copy_entry(dest, archive->data, size);
    return nullptr;
}

// 0x7100596aa8: table at +100
void* fetch_entry_596aa8(PackedArchive* archive, void* dest, unsigned int index) {
    if (!archive->data)
        return nullptr;
    const PackedEntry* entry =
        reinterpret_cast<const PackedEntry*>(&archive->header[archive->tables[14]]) + index;
    const unsigned int* fields = &entry->offset;
    unsigned int offset = *fields;
    unsigned int size = fields[1];
    if (!archive->file)
        return copy_entry(dest, archive->data + offset, size);
    FileSystem* fs = gObjectManager->file_system;
    if (fs->seek(archive->file, archive->tables[6] + offset, 0, nullptr, 0))
        return nullptr;
    unsigned long count;
    if (fs->read(archive->file, archive->data, size, &count, 0) == 0 && count == size)
        return copy_entry(dest, archive->data, size);
    return nullptr;
}

// 0x7100596b94: table at +104
void* fetch_entry_596b94(PackedArchive* archive, void* dest, unsigned int index) {
    if (!archive->data)
        return nullptr;
    const PackedEntry* entry =
        reinterpret_cast<const PackedEntry*>(&archive->header[archive->tables[15]]) + index;
    const unsigned int* fields = &entry->offset;
    unsigned int offset = *fields;
    unsigned int size = fields[1];
    if (!archive->file)
        return copy_entry(dest, archive->data + offset, size);
    FileSystem* fs = gObjectManager->file_system;
    if (fs->seek(archive->file, archive->tables[6] + offset, 0, nullptr, 0))
        return nullptr;
    unsigned long count;
    if (fs->read(archive->file, archive->data, size, &count, 0) == 0 && count == size)
        return copy_entry(dest, archive->data, size);
    return nullptr;
}

// 0x7100596c80: table at +108
void* fetch_entry_596c80(PackedArchive* archive, void* dest, unsigned int index) {
    if (!archive->data)
        return nullptr;
    const PackedEntry* entry =
        reinterpret_cast<const PackedEntry*>(&archive->header[archive->tables[16]]) + index;
    const unsigned int* fields = &entry->offset;
    unsigned int offset = *fields;
    unsigned int size = fields[1];
    if (!archive->file)
        return copy_entry(dest, archive->data + offset, size);
    FileSystem* fs = gObjectManager->file_system;
    if (fs->seek(archive->file, archive->tables[6] + offset, 0, nullptr, 0))
        return nullptr;
    unsigned long count;
    if (fs->read(archive->file, archive->data, size, &count, 0) == 0 && count == size)
        return copy_entry(dest, archive->data, size);
    return nullptr;
}

// 0x7100596d6c: table at +114
void* fetch_entry_596d6c(PackedArchive* archive, void* dest, unsigned int index) {
    if (!archive->data)
        return nullptr;
    const PackedEntry* entry =
        reinterpret_cast<const PackedEntry*>(&archive->header[archive->tables[19]]) + index;
    const unsigned int* fields = &entry->offset;
    unsigned int offset = *fields;
    unsigned int size = fields[1];
    if (!archive->file)
        return copy_entry(dest, archive->data + offset, size);
    FileSystem* fs = gObjectManager->file_system;
    if (fs->seek(archive->file, archive->tables[6] + offset, 0, nullptr, 0))
        return nullptr;
    unsigned long count;
    if (fs->read(archive->file, archive->data, size, &count, 0) == 0 && count == size)
        return copy_entry(dest, archive->data, size);
    return nullptr;
}
