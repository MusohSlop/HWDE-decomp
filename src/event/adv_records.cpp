// Matching candidates for the Adventure Mode record serializers 0x710028386c-0x7100283b50.
// Names are descriptive placeholders. Status: matching/README.md.

class DataStream {
public:
    void read(unsigned short* value);                                       // 0x71001fbc84
    void write(unsigned short value);                                       // 0x71001fbe00
    void read(unsigned char* value);                                        // 0x71001fbc54
    void write(unsigned char value);                                        // 0x71001fbdd8

    template <typename T>
    void transfer16(T& value) {
        if (reading)
            read(reinterpret_cast<unsigned short*>(&value));
        else
            write(static_cast<unsigned short>(value));
    }

    template <typename T>
    void transfer8(T& value) {
        if (reading)
            read(reinterpret_cast<unsigned char*>(&value));
        else
            write(static_cast<unsigned char>(value));
    }

    unsigned char pad[0x1c];
    int reading;              // +1c
};

struct CellPosition {
    int x;
    int y;
};

extern "C" void* memset(void* dest, int value, unsigned long size);

// Raw view of one board row for serialization.
struct BoardRow {
    short head[4];            // +00
    unsigned char gates[4];   // +08
    signed char owner;        // +0c
    unsigned char flags[8];   // +0d
    unsigned char pad15;
    short stats[6];           // +16
    short extra[6];           // +22
    short cells[0xb0];        // +2e
    unsigned char pad18e[2];
    CellPosition positions[2][5]; // +190
};
static_assert(sizeof(BoardRow) == 0x1e0, "board row size");

struct UnitInfo {
    short values[4];          // +0
    unsigned char bytes[4];   // +8
};

void BoardRow_serialize(BoardRow* row, DataStream* stream, int index) {
    for (int i = 0; i < 4; ++i)
        stream->transfer16(row->head[i]);
    for (int i = 0; i < 4; ++i)
        stream->transfer8(row->gates[i]);
    for (int i = 0; i < 8; ++i)
        stream->transfer8(row->flags[i]);
    for (int i = 0; i < 6; ++i)
        stream->transfer16(row->stats[i]);
    memset(row->cells, 0, sizeof(row->cells));
    memset(row->positions, 0, sizeof(row->positions));
    for (int i = 0; i < 6; ++i)
        stream->transfer16(row->extra[i]);
    row->owner = index;
}

void BoardRow_serialize_extra(BoardRow* row, DataStream* stream) {
    signed char x;
    signed char y;
    for (int i = 0; i < 5; ++i) {
        stream->transfer8(x);
        stream->transfer8(y);
        row->positions[0][i].x = x;
        row->positions[0][i].y = y;
    }
    for (int i = 0; i < 5; ++i) {
        stream->transfer8(x);
        stream->transfer8(y);
        row->positions[1][i].x = x;
        row->positions[1][i].y = y;
    }
}

void UnitInfo_serialize(UnitInfo* info, DataStream* stream) {
    stream->transfer16(info->values[0]);
    stream->transfer16(info->values[1]);
    stream->transfer16(info->values[2]);
    stream->transfer16(info->values[3]);
    stream->transfer8(info->bytes[0]);
    stream->transfer8(info->bytes[1]);
    stream->transfer8(info->bytes[2]);
    stream->transfer8(info->bytes[3]);
}

void RewardPair_serialize(void* pair, DataStream* stream) {
    short* values = static_cast<short*>(pair);
    stream->transfer16(values[0]);
    stream->transfer16(values[1]);
    stream->transfer16(values[2]);
    stream->transfer16(values[3]);
}
