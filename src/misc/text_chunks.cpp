// Text chunk accessors (0x7100218d18-0x7100219048): a chunk is a packed table with a header (row
// size, offset of the rows, one type byte per column); each accessor checks the column's type and
// reads the cell, where the cell offset is the sum of the sizes of the earlier columns. Names are
// descriptive placeholders. Status: matching/README.md.

struct ChunkHeader {
    unsigned char pad[0xa];
    unsigned short row_size;  // +0a
    unsigned int rows;        // +0c: offset of the first row
    unsigned char types[1];   // +10: one per column
};

static const int kColumnSizes[8] = {4, 4, 2, 1, 4, 2, 1, 4};

class TextChunks {
public:
    const char* text(unsigned int row, unsigned int column) const;
    int value(unsigned int row, unsigned int column) const;
    int number(unsigned int row, unsigned int column) const;
    unsigned short half(unsigned int row, unsigned int column) const;
    unsigned short count(unsigned int row, unsigned int column) const;
    unsigned char byte(unsigned int row, unsigned int column) const;
    unsigned char flag(unsigned int row, unsigned int column) const;

private:
    const unsigned char* rows() const { return reinterpret_cast<const unsigned char*>(data) + data->rows; }
    static unsigned int offset(const unsigned char* types, unsigned int column) {
        unsigned int offset = 0;
        while (column--) {
            unsigned char type = *types++;
            offset += type <= 7 ? kColumnSizes[type] : 0;
        }
        return offset;
    }
    const unsigned char* cell(const unsigned char* types, unsigned int row, unsigned int column) const {
        unsigned int at = offset(types, column);
        return rows() + data->row_size * row + at;
    }

    void* vtable_slot;        // +00 (vtable pointer of the owning class)
    const ChunkHeader* data;  // +08
};

// 0x7100218d18
const char* TextChunks::text(unsigned int row, unsigned int column) const {
    if (!data)
        return nullptr;
    const unsigned char* types = data->types;
    if (types[column] != 0)
        return nullptr;
    const unsigned char* at = cell(types, row, column);
    return reinterpret_cast<const char*>(rows() + *reinterpret_cast<const unsigned int*>(at));
}

// 0x7100218da0
int TextChunks::value(unsigned int row, unsigned int column) const {
    if (!data)
        return -1;
    const unsigned char* types = data->types;
    if (types[column] != 1)
        return -1;
    return *reinterpret_cast<const int*>(cell(types, row, column));
}

// 0x7100218e28
int TextChunks::number(unsigned int row, unsigned int column) const {
    if (!data)
        return -1;
    const unsigned char* types = data->types;
    if (types[column] != 4)
        return -1;
    return *reinterpret_cast<const int*>(cell(types, row, column));
}

// 0x7100218eb0
unsigned short TextChunks::half(unsigned int row, unsigned int column) const {
    if (!data)
        return 0xffff;
    const unsigned char* types = data->types;
    if (types[column] != 2)
        return 0xffff;
    return *reinterpret_cast<const unsigned short*>(cell(types, row, column));
}

// 0x7100218f38
unsigned short TextChunks::count(unsigned int row, unsigned int column) const {
    if (!data)
        return 0xffff;
    const unsigned char* types = data->types;
    if (types[column] != 5)
        return 0xffff;
    return *reinterpret_cast<const unsigned short*>(cell(types, row, column));
}

// 0x7100218fc0
unsigned char TextChunks::byte(unsigned int row, unsigned int column) const {
    if (!data)
        return 0xff;
    const unsigned char* types = data->types;
    if (types[column] != 3)
        return 0xff;
    return *cell(types, row, column);
}

// 0x7100219048
unsigned char TextChunks::flag(unsigned int row, unsigned int column) const {
    if (!data)
        return 0xff;
    const unsigned char* types = data->types;
    if (types[column] != 6)
        return 0xff;
    return *cell(types, row, column);
}
