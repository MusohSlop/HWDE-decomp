// Probe: ways of writing "clear the header fields, then clear a byte array", compared against
// CountedBlock::reset (0x710004c054). Each variant is compiled with the project flags and its
// assembly compared to the original by matching/scratch/memset_probe/probe.py.

extern "C" void* memset(void* dest, int value, unsigned long size);

template <class T> static inline void fill_bytes(T* first, T* last, T value) {
    for (; first != last; ++first)
        *first = value;
}

struct Bytes {
    unsigned char b[0x1f4];
};

#define FIELDS                     \
    long value0;              /* +00 */ \
    long value8;              /* +08 */ \
    long value10;             /* +10 */ \
    int value18;              /* +18 */ \
    unsigned char pad1c[4];

#define HEADER value18 = 0; value0 = 0; value8 = 0; value10 = 0;

struct LoopBefore { void reset(); FIELDS unsigned char bytes[0x1f4]; };
void LoopBefore::reset() { HEADER for (unsigned int i = 0; i < sizeof(bytes); ++i) bytes[i] = 0; }

struct LoopAfter { void reset(); FIELDS unsigned char bytes[0x1f4]; };
void LoopAfter::reset() { for (unsigned int i = 0; i < sizeof(bytes); ++i) bytes[i] = 0; HEADER }

struct MemsetBefore { void reset(); FIELDS unsigned char bytes[0x1f4]; };
void MemsetBefore::reset() { HEADER memset(bytes, 0, sizeof(bytes)); }

struct MemsetAfter { void reset(); FIELDS unsigned char bytes[0x1f4]; };
void MemsetAfter::reset() { memset(bytes, 0, sizeof(bytes)); HEADER }

struct MemsetAddrBefore { void reset(); FIELDS unsigned char bytes[0x1f4]; };
void MemsetAddrBefore::reset() { HEADER memset(&bytes[0], 0, sizeof(bytes) / sizeof(bytes[0]) * sizeof(bytes[0])); }

struct ValueInitBefore { void reset(); FIELDS Bytes bytes; };
void ValueInitBefore::reset() { HEADER bytes = Bytes(); }

struct ValueInitAfter { void reset(); FIELDS Bytes bytes; };
void ValueInitAfter::reset() { bytes = Bytes(); HEADER }

struct BraceInitBefore { void reset(); FIELDS Bytes bytes; };
void BraceInitBefore::reset() { HEADER bytes = {}; }

struct FillBefore { void reset(); FIELDS unsigned char bytes[0x1f4]; };
void FillBefore::reset() { HEADER fill_bytes(bytes, bytes + sizeof(bytes), static_cast<unsigned char>(0)); }

struct FillAfter { void reset(); FIELDS unsigned char bytes[0x1f4]; };
void FillAfter::reset() { fill_bytes(bytes, bytes + sizeof(bytes), static_cast<unsigned char>(0)); HEADER }

struct WholeValueInit { void reset(); FIELDS unsigned char bytes[0x1f4]; };
void WholeValueInit::reset() { *this = WholeValueInit(); }

// Control: HeaderTable::reset (0x71005fad40) matches with a loop and the header first.
struct Control { void reset(); long value0; int value8; unsigned char padc[4]; unsigned char bytes[0xab]; unsigned char padbb; int valuebc; };
void Control::reset() { value0 = 0; value8 = 0; valuebc = 0; for (unsigned int i = 0; i < sizeof(bytes); ++i) bytes[i] = 0; }

// SplitTable::clear (0x71003dd0e4): two regions, the second's address kept across the first clear.
template <unsigned long N> struct Block { unsigned char b[N]; };
struct SplitBlocks { void reset(); Block<0x110> head; unsigned char pad[0x70]; Block<0x300> tail; };
void SplitBlocks::reset() { head = {}; tail = {}; }

struct SplitRef { void reset(); Block<0x110> head; unsigned char pad[0x70]; Block<0x300> tail; };
void SplitRef::reset() { Block<0x300>& rest = tail; head = {}; rest = {}; }

struct SplitPtrLoop { void reset(); unsigned char head[0x110]; unsigned char pad[0x70]; unsigned char tail[0x300]; };
void SplitPtrLoop::reset() { unsigned char* rest = tail; for (unsigned int i = 0; i < 0x110; ++i) head[i] = 0; for (unsigned int i = 0; i < 0x300; ++i) rest[i] = 0; }

struct SplitMemset { void reset(); unsigned char head[0x110]; unsigned char pad[0x70]; unsigned char tail[0x300]; };
void SplitMemset::reset() { unsigned char* rest = tail; memset(head, 0, 0x110); memset(rest, 0, 0x300); }