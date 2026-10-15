// WIP (third session): small relaxed groups parked (pieces of build/s3/t_small2.cpp; the expression-op and limit
// types are as in misc/s3_functions35.cpp).
// 4c2bec/4c3874, 4c2b44/4c382c (64 and 72 B): the original calls the next op and returns (a frame) where ours
// tail-calls it; a 16-byte struct result did not change that.
// 5fdb84/5fee04 (72 B): 2 words; the original pairs the stores at +4c/+50 (kind, used) and leaves +48 alone. Best
// of the 120 body orders of the five later fields: count, used, kind, table, flags.

// The pointer field at the next operand's offset, passed on to the next op.
template <int Table>
Result4c2b expr_pointer_field(int** cursor, unsigned char* base) {
    unsigned int offset = *(*cursor)++;
    int op = *(*cursor)++;
    return expr_ops<Table>()[op](cursor, *reinterpret_cast<void**>(base + offset));
}

// The self-relative field at the next operand's offset (its address plus the offset it holds).
template <int Table>
Result4c2b expr_relative_field(int** cursor, unsigned char* base) {
    unsigned int offset = *(*cursor)++;
    int op = *(*cursor)++;
    unsigned char* field = base + offset;
    return expr_ops<Table>()[op](cursor, field + *reinterpret_cast<int*>(field));
}

template Result4c2b expr_pointer_field<0>(int**, unsigned char*);    // 0x71004c2bec
template Result4c2b expr_pointer_field<1>(int**, unsigned char*);    // 0x71004c3874
template Result4c2b expr_relative_field<0>(int**, unsigned char*);   // 0x71004c2b44
template Result4c2b expr_relative_field<1>(int**, unsigned char*);   // 0x71004c382c
// ---- 5fdb84/5fee04: a limit object initialised after its base (the largest float, its kind 4, a global table).
struct Base5fa9 {
    Base5fa9();                  // 0x71005fa954
    unsigned char pad0[0x3c];
};
struct Table5fdb;
// Reached through the GOT slots at 0x7100c2de78 and 0x7100c2de90.
extern Table5fdb gLimitTableA;
extern Table5fdb gLimitTableB;

template <int Copy>
struct Limit5fdb : Base5fa9 {
    Limit5fdb();

    float max;                   // +3c
    long total;                  // +40
    int count;                   // +48
    int kind;                    // +4c
    int used;                    // +50
    int pad54;
    Table5fdb* table;            // +58
    short flags;                 // +60
};

template <int Copy>
Limit5fdb<Copy>::Limit5fdb()
    : max(3.40282347e+38f), total(0), count(0), kind(4), used(0), table(Copy == 0 ? &gLimitTableA : &gLimitTableB),
      flags(0) {}

template Limit5fdb<0>::Limit5fdb();   // 0x71005fdb84
template Limit5fdb<1>::Limit5fdb();   // 0x71005fee04

