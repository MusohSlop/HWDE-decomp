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


// 550d94/550de0 (76 B): 9 words; ours loads the motion pointer once before the branch (hoisted), the original
// in each branch after storing the target.
// ---- 550d94/550de0: one of two targets set (immediately, or as an offset from the current value).
struct Vec3_550d {
    float x, y, z;
};
struct Motion550d {
    unsigned char pad0[0x40];
    Vec3_550d vectors[2];        // +40
    unsigned char pad58[0x80];
    unsigned int current;        // +d8
    unsigned char paddc[0x6c];
    bool dirty[2];               // +148
};
struct Target550d {
    float target;
    float offset;
};

template <int I>
struct Driver550d {
    void set(float value, unsigned char now);

    unsigned char pad0[0x1a4];
    Target550d targets[2];       // +1a4
    unsigned char pad1b4[0x1f4];
    Motion550d* motion;          // +3a8
};

template <int I>
void Driver550d<I>::set(float value, unsigned char now) {
    if (targets[I].target == value)
        return;
    targets[I].target = value;
    if (now) {
        Motion550d* m = motion;
        m->vectors[I].x = value;
        m->dirty[m->current ^ 1] = true;
    } else {
        targets[I].offset = value - motion->vectors[I].x;
    }
}

template void Driver550d<1>::set(float, unsigned char);   // 0x7100550d94
template void Driver550d<0>::set(float, unsigned char);   // 0x7100550de0


// 5064ec/506fb0 (88 B): the row is built as two 64-bit stores as in the original (a 16-byte union returned by
// value), 17 words off in the order of the products; irsearch queued.
// ---- 5064ec/506fb0: the second row of a rotation matrix from a quaternion.
union Row5064 {
    struct {
        float x, y, z, w;
    };
    unsigned int bits[4];
};
struct Quat5064 {
    float x, y, z, w;
};
struct Matrix5064 {
    Row5064 rows[3];
};

inline Row5064 row_y(const Quat5064& q) {
    float x2 = q.x + q.x;
    float y2 = q.y + q.y;
    float z2 = q.z + q.z;
    Row5064 r;
    r.x = x2 * q.y - z2 * q.w;
    r.y = 1.0f - q.z * z2 - q.x * x2;
    r.z = y2 * q.z + x2 * q.w;
    r.w = 0.0f;
    return r;
}

template <int Copy>
void set_row_y(Matrix5064* m, const Quat5064* q) {
    m->rows[1] = row_y(*q);
}

template void set_row_y<0>(Matrix5064*, const Quat5064*);   // 0x71005064ec
template void set_row_y<1>(Matrix5064*, const Quat5064*);   // 0x7100506fb0

