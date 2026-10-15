// Fifth session, parked: 0x7100400e40 (6,304 bytes), a model instance's setup from its resource: attaches to the
// owner, reads the entry index and two parameters from the resource header, clears the state block when the entry
// exists, resets the mark and pair arrays, copies four ranges, the points' positions and creates the shared slots
// (releasing the ones made so far and returning false when one fails), then sets up three node lists (0xd0, 0xb0
// and 0xc0 bytes per node) by source type: a bounding box over points, a TRS transform to a matrix (Euler angles
// through sincos, or a quaternion; identity when the rotation is near zero), or a fitted shape (0x407eec,
// 0x4086c8); last the id groups and their mask bits.
// This draft is 5,496 B against 6,304; edit distance 723 abstracted, 1,115 exact (tools/s5/lev.py). Maps: .rodata
// (the two jump tables, 0x80f48c and 0x80f49c, in this order) = 0x710080f48c.
// Settled: the helpers are always_inline (as plain inline the TRS helper stays a call, 3 sincos instead of 18);
// owner->x18 is passed directly; the entry test is count > idx on a 0x30-byte entry array (smaddl); the mark and
// pair loops and the point copy go through a reference (one load of the array base); the table offset is a select
// (h ? (off ? h + off : 0) : 0 as an if plus a select helper); each node's src/flags pair is stored once before the
// null test (the original keeps flags = 0 before flags = 0x40000000 on that path); the id groups are an inline
// called three times with the mask in a local stored after each id and the rest filled by a loop (LoopIdiom makes
// the original's memset with (k ^ 3) * 4 + 4) indexing ids[g * 4 + k].
// Still off: the original keeps two copies of each inlined matrix block per list (case 2 and case 4 of the first
// and third switch, types 2 and 0 of the second): 18 sincos calls against our 9. The copies are identical except
// the order of two products and of the four stores at the end (a different post-RA schedule, swapped between the
// first and third lists), so branch folding cannot merge them; ours schedules both alike and they are merged.
extern "C" void* memcpy(void* dest, const void* src, unsigned long size);   // 0x7100600870
extern "C" void* memset(void* dest, int value, unsigned long size);         // 0x7100600890

void sincos_fd70(float angle, float* s, float* c);                          // 0x710000fd70
void transform_22286c(float* out, const float* m);                          // 0x710022286c
unsigned char fit_407eec(float* m, const void* points, int count, bool flag);        // 0x7100407eec
void bounds_4086c8(float r, float* a, float* b, const void* points, int count, const float* m);   // 0x71004086c8
void attach_5e7578(void* owner, void* target);                              // 0x71005e7578

struct Shared400e40 {
    void** vtable;
    int refs;                         // +8
};
Shared400e40* create_5c1730(void* owner, void* arg);                        // 0x71005c1730

struct Vec2i400e40 {
    int x;
    int y;
};
struct Vec3i400e40 {
    int x;
    int y;
    int z;
};

// A node source in the resource: a TRS transform (rotation as Euler angles or a quaternion), a point list, or a
// fitted shape, by type.
struct Source400e40 {
    unsigned char pad0[4];
    unsigned int flags;               // +4
    short type8;                      // +8 (second and third lists)
    unsigned char pada[2];
    short typec;                      // +c (first list)
    unsigned char pade[0x22];
    union {
        struct {
            float tx;                 // +30
            float ty;                 // +34
            float tz;                 // +38
        };
        struct {
            int count;                // +30
            float radius;             // +34
        };
    };
    unsigned char pad3c[4];
    float rot[4];                     // +40 (or the first of the points, 16 bytes each)
    unsigned char pad50[0x10];
    int keys;                         // +60
};

struct Table400e40 {
    unsigned char pad0[8];
    struct {
        Vec3i400e40 v;
        int pad;
    } entries[1];                     // +8
};

struct Header400e40 {
    unsigned char pad0[0x24];
    int entry_count;                  // +24
    unsigned int entry_offset;        // +28
    int index;                        // +2c
    float x30;                        // +30
    int x34;                          // +34
    int vec_count;                    // +38
    unsigned int vec_offset;          // +3c
    unsigned char pad40[8];
    int count1;                       // +48
    unsigned int table1;              // +4c
    unsigned char pad50[8];
    int count2;                       // +58
    unsigned int table2;              // +5c
    unsigned char pad60[8];
    unsigned int flags_offset;        // +68
    unsigned int x6c;                 // +6c
    int count3;                       // +70
    unsigned int table3;              // +74

    const char* base() const { return reinterpret_cast<const char*>(this); }
    struct Entry {
        unsigned char data[0x30];
    };
    const Entry* entry(int i) const { return &reinterpret_cast<const Entry*>(base() + entry_offset)[i]; }
    const Vec2i400e40* vec(int k) const {
        return k < vec_count ? &reinterpret_cast<const Vec2i400e40*>(base() + vec_offset)[k] : nullptr;
    }
    const Table400e40* table6c() const {
        return x6c != 0 ? reinterpret_cast<const Table400e40*>(base() + x6c) : nullptr;
    }
    const Source400e40* source(const unsigned int* table, long i) const {
        return reinterpret_cast<const Source400e40*>(base() + table[i]);
    }
};

struct Resource400e40 {
    unsigned char pad0[0x18];
    Header400e40* header;             // +18
};

struct Owner400e40 {
    unsigned char pad0[0x18];
    void* x18;                        // +18
};

struct Node1_400e40 {                 // 0xd0
    const Source400e40* src;          // +0
    unsigned int flags;               // +8
    unsigned char padc[0x2c];
    float x38;                        // +38
    float x3c;                        // +3c
    float x40;                        // +40
    float x44;                        // +44
    float x48;                        // +48
    float x4c;                        // +4c
    float m[16];                      // +50
    float out[16];                    // +90
};
struct Node2_400e40 {                 // 0xb0
    const Source400e40* src;          // +0
    unsigned int flags;               // +8
    unsigned char padc[0x24];
    float m[16];                      // +30
    float out[16];                    // +70
};
struct Node3_400e40 {                 // 0xc0
    const Source400e40* src;          // +0
    unsigned int flags;               // +8
    unsigned char padc[0x34];
    float m[16];                      // +40
    float out[16];                    // +80
};

struct Slot400e40 {                   // 0x68
    Shared400e40* object;
    unsigned char pad8[0x60];
};
struct Point400e40 {                  // 0x48
    unsigned char pad0[0x18];
    Vec3i400e40 pos;                  // +18
    unsigned char pad24[0x24];
};
struct Pair400e40 {                   // 0x10
    long a;
    int b;
    int pad;
};
struct Range400e40 {                  // 0x18
    Vec2i400e40 v;
    unsigned char pad8[0x10];
};
struct State400e40 {                  // 0x2c
    int words[11];
};

static const float kEps = 1.1920929e-05f;

static inline __attribute__((always_inline)) void euler_matrix(float* m, const Source400e40* s, float* sn, float* cs) {
    sincos_fd70(s->rot[0], &sn[0], &cs[0]);
    sincos_fd70(s->rot[1], &sn[1], &cs[1]);
    sincos_fd70(s->rot[2], &sn[2], &cs[2]);
    m[0] = cs[1] * cs[2];
    m[1] = cs[1] * sn[2];
    m[2] = -sn[1];
    m[3] = 0.0f;
    m[4] = cs[2] * sn[1] * sn[0] - sn[2] * cs[0];
    m[5] = sn[2] * sn[1] * sn[0] + cs[2] * cs[0];
    m[6] = cs[1] * sn[0];
    m[7] = 0.0f;
    m[8] = sn[2] * sn[0] + cs[2] * sn[1] * cs[0];
    m[9] = sn[2] * sn[1] * cs[0] - cs[2] * sn[0];
    m[10] = cs[1] * cs[0];
    m[11] = 0.0f;
    m[12] = s->tx;
    m[13] = s->ty;
    m[14] = s->tz;
    m[15] = 1.0f;
}

static inline __attribute__((always_inline)) void quat_matrix(float* m, const Source400e40* s) {
    float x = s->rot[0];
    float y = s->rot[1];
    float z = s->rot[2];
    float w = s->rot[3];
    float x2 = x + x;
    float y2 = y + y;
    float z2 = z + z;
    float zz = z * z2;
    float xx = x * x2;
    m[0] = (1.0f - y * y2) - zz;
    m[1] = x2 * y + z2 * w;
    m[2] = x * z2 - y2 * w;
    m[3] = 0.0f;
    m[4] = x2 * y - z2 * w;
    m[5] = (1.0f - zz) - xx;
    m[6] = y2 * z + x2 * w;
    m[7] = 0.0f;
    m[8] = x * z2 + y2 * w;
    m[9] = y2 * z - x2 * w;
    m[10] = (1.0f - xx) - y * y2;
    m[11] = 0.0f;
    m[12] = s->tx;
    m[13] = s->ty;
    m[14] = s->tz;
    m[15] = 1.0f;
}

static inline __attribute__((always_inline)) void identity_matrix(float* m, const Source400e40* s) {
    m[0] = 1.0f;
    m[1] = 0.0f;
    m[2] = 0.0f;
    m[3] = 0.0f;
    m[4] = 0.0f;
    m[5] = 1.0f;
    m[6] = 0.0f;
    m[7] = 0.0f;
    m[8] = 0.0f;
    m[9] = 0.0f;
    m[10] = 1.0f;
    m[11] = 0.0f;
    m[12] = s->tx;
    m[13] = s->ty;
    m[14] = s->tz;
    m[15] = 1.0f;
}

static inline __attribute__((always_inline)) bool near_zero(float f) {
    return -kEps <= f && f <= kEps;
}

// Builds the node matrix from a TRS source; returns false for the identity (the caller marks it).
static inline __attribute__((always_inline)) bool trs_matrix(float* m, const Source400e40* s, bool quat, float* sn, float* cs) {
    if (!quat) {
        if (near_zero(s->rot[0]) && near_zero(s->rot[1]) && near_zero(s->rot[2])) {
            return false;
        }
        euler_matrix(m, s, sn, cs);
    } else {
        if (near_zero(s->rot[0]) && near_zero(s->rot[1]) && near_zero(s->rot[2]) && 0.9999881f <= s->rot[3] &&
            s->rot[3] <= 1.0000119f) {
            return false;
        }
        quat_matrix(m, s);
    }
    return true;
}

struct Model400e40 {
    unsigned char pad0[0x18];
    Owner400e40* owner;               // +18
    unsigned char pad20[8];
    Resource400e40* resource;         // +28
    int x30;                          // +30
    unsigned char pad34[0xc];
    unsigned char x40[0x70];          // +40
    State400e40 saved;                // +b0
    State400e40 state;                // +dc
    float x108;                       // +108
    float x10c;                       // +10c
    int x110;                         // +110
    int index;                        // +114
    float x118;                       // +118
    int x11c;                         // +11c
    int x120;                         // +120
    unsigned char pad124[4];
    Range400e40 ranges[4];            // +128
    unsigned char pad188[0];
    Point400e40* points;              // +188
    int point_count;                  // +190
    unsigned char pad194[4];
    Slot400e40* slots;                // +198
    int slot_count;                   // +1a0
    int x1a4;                         // +1a4
    long x1a8;                        // +1a8
    float x1b0;                       // +1b0
    float x1b4;                       // +1b4
    int x1b8;                         // +1b8
    unsigned char pad1bc[4];
    unsigned char (*marks)[2];        // +1c0
    int mark_count;                   // +1c8
    unsigned char pad1cc[4];
    Pair400e40* pairs;                // +1d0
    int pair_count;                   // +1d8
    unsigned char pad1dc[4];
    Node1_400e40* nodes1;             // +1e0
    int node1_count;                  // +1e8
    unsigned char pad1ec[4];
    Node2_400e40* nodes2;             // +1f0
    int node2_count;                  // +1f8
    unsigned char pad1fc[4];
    Node3_400e40* nodes3;             // +200
    int node3_count;                  // +208
    unsigned char pad20c[0x14];
    unsigned int mask;                // +220
    int ids[12];                      // +224

    bool setup();
    void copy_ids(int g, const unsigned int* src, unsigned int& m) {
        int k = 0;
        for (; k < 4; k++) {
            int id = static_cast<int>(src[k]);
            if (id < 0) {
                break;
            }
            ids[g * 4 + k] = id;
            m |= (0x10u << k) | (0x100u << (g * 4 + k));
            mask = m;
        }
        for (; k < 4; k++) {
            ids[g * 4 + k] = -1;
        }
    }
};

// 0x7100400e40
bool Model400e40::setup() {
    attach_5e7578(owner->x18, x40);
    Resource400e40* res = resource;
    int idx = res->header != nullptr ? res->header->index : -1;
    index = idx;
    float f = res->header != nullptr ? res->header->x30 : 0.0f;
    x118 = f;
    x11c = res->header != nullptr ? res->header->x34 : 1000;
    Header400e40* h = res->header;
    if (h != nullptr && idx >= 0 && h->entry_count > idx && h->entry(idx) != nullptr) {
        memset(&state, 0, sizeof(state));
    }
    saved = state;
    x10c = f;
    x108 = f;
    x120 = -1;
    x110 = 0;
    for (long i = 0; i < mark_count; i++) {
        unsigned char* m = marks[i];
        m[0] = 0xff;
        m[1] = 0xff;
    }
    for (long i = 0; i < pair_count; i++) {
        Pair400e40& p = pairs[i];
        p.a = 0;
        p.b = -1;
    }
    Resource400e40* r = resource;
    for (int k = 0; k < 4; k++) {
        Header400e40* hh = r->header;
        if (hh == nullptr) {
            break;
        }
        if (const Vec2i400e40* v = hh->vec(k)) {
            ranges[k].v.x = v->x;
            ranges[k].v.y = v->y;
        }
    }
    if (point_count > 0) {
        Header400e40* hh = r->header;
        const Table400e40* t = nullptr;
        if (hh != nullptr) {
            t = hh->table6c();
        }
        for (long i = 0; i < point_count; i++) {
            Point400e40& p = points[i];
            p.pos.x = t->entries[i].v.x;
            p.pos.y = t->entries[i].v.y;
            p.pos.z = t->entries[i].v.z;
        }
    }
    for (long i = 0; i < slot_count; i++) {
        Shared400e40** p = &slots[i].object;
        *p = create_5c1730(owner, nullptr);
        if (*p == nullptr) {
            for (int j = 0; j < static_cast<int>(i); j++) {
                Shared400e40*& o = slots[j].object;
                if (o != nullptr) {
                    if (--o->refs == 0) {
                        reinterpret_cast<void (*)(Shared400e40*)>(o->vtable[3])(o);
                    }
                    o = nullptr;
                }
            }
            return false;
        }
    }
    alignas(16) float sn[4];
    alignas(16) float cs[4];
    for (long i = 0; i < node1_count; i++) {
        Node1_400e40& n = nodes1[i];
        Header400e40* hh = resource->header;
        const Source400e40* s = hh != nullptr && i < hh->count1
                                    ? hh->source(reinterpret_cast<const unsigned int*>(hh->base() + hh->table1), i)
                                    : nullptr;
        n.src = s;
        n.flags = 0;
        if (s == nullptr) {
            n.flags = 0x40000000;
            continue;
        }
        float v = (s->flags & 1) ? 0.0f : 1.0f;
        unsigned int fl = ~s->flags & 1;
        n.x38 = v;
        n.x3c = v;
        n.x40 = 0.0f;
        n.flags = fl;
        n.x44 = 1.0f;
        n.x48 = 1.0f;
        n.x4c = 0.0f;
        switch (s->typec) {
        case 1:
            if (s->count < 2) {
                n.flags = fl | 0x40000000;
            }
            {
                const float(*pts)[4] = reinterpret_cast<const float(*)[4]>(s->rot);
                float* lo = &n.m[0];
                float* hi = &n.m[4];
                memcpy(lo, pts[0], 16);
                memcpy(hi, pts[0], 16);
                for (long k = 1; k < s->count; k++) {
                    for (int c = 0; c < 3; c++) {
                        float p = pts[k][c];
                        if (p < lo[c]) {
                            lo[c] = p;
                        } else if (hi[c] < p) {
                            hi[c] = p;
                        }
                    }
                }
            }
            break;
        case 2:
            if (!trs_matrix(n.m, s, (s->flags >> 5) & 1, sn, cs)) {
                n.flags = fl | 0x1000000;
                identity_matrix(n.m, s);
            }
            transform_22286c(n.out, n.m);
            break;
        case 3:
            if (!fit_407eec(n.m, s->rot, s->count, true)) {
                n.flags |= 0x40000000;
            } else {
                bounds_4086c8(s->radius, &n.m[4], &n.m[8], s->rot, s->count, n.m);
            }
            break;
        case 4:
            if (s->keys > 2) {
                if (!trs_matrix(n.m, s, (s->flags >> 5) & 1, sn, cs)) {
                    n.flags = fl | 0x1000000;
                    identity_matrix(n.m, s);
                }
                transform_22286c(n.out, n.m);
            } else {
                n.flags = fl | 0x40000000;
            }
            break;
        }
    }
    for (long i = 0; i < node2_count; i++) {
        Node2_400e40& n = nodes2[i];
        Header400e40* hh = resource->header;
        const Source400e40* s = hh != nullptr && i < hh->count2
                                    ? hh->source(reinterpret_cast<const unsigned int*>(hh->base() + hh->table2), i)
                                    : nullptr;
        n.src = s;
        n.flags = 0;
        if (s == nullptr) {
            n.flags = 0x40000000;
            continue;
        }
        unsigned int fl = ~s->flags & 1;
        n.flags = fl;
        short type = s->type8;
        if (type == 2) {
            if (s->keys < 3) {
                n.flags = fl | 0x40000000;
                continue;
            }
            if (!trs_matrix(n.m, s, (s->flags >> 3) & 1, sn, cs)) {
                n.flags = fl | 0x1000000;
                identity_matrix(n.m, s);
            }
            transform_22286c(n.out, n.m);
        } else if (type == 1) {
            if (!fit_407eec(n.m, s->rot, s->count, true)) {
                n.flags |= 0x40000000;
            } else {
                bounds_4086c8(s->radius, &n.m[4], &n.m[8], s->rot, s->count, n.m);
            }
        } else if (type == 0) {
            if (!trs_matrix(n.m, s, (s->flags >> 3) & 1, sn, cs)) {
                n.flags = fl | 0x1000000;
                identity_matrix(n.m, s);
            }
            transform_22286c(n.out, n.m);
        }
    }
    for (long i = 0; i < node3_count; i++) {
        Node3_400e40& n = nodes3[i];
        Header400e40* hh = resource->header;
        const Source400e40* s = hh != nullptr && i < hh->count3
                                    ? hh->source(reinterpret_cast<const unsigned int*>(hh->base() + hh->table3), i)
                                    : nullptr;
        n.src = s;
        n.flags = 0;
        if (s == nullptr) {
            n.flags = 0x40000000;
            continue;
        }
        unsigned int fl = ~s->flags & 1;
        n.flags = fl;
        switch (static_cast<unsigned short>(s->type8)) {
        case 1:
            if (s->count < 2) {
                n.flags = fl | 0x40000000;
            }
            {
                const float(*pts)[4] = reinterpret_cast<const float(*)[4]>(s->rot);
                float* lo = &n.m[0];
                float* hi = &n.m[4];
                memcpy(lo, pts[0], 16);
                memcpy(hi, pts[0], 16);
                for (long k = 1; k < s->count; k++) {
                    for (int c = 0; c < 3; c++) {
                        float p = pts[k][c];
                        if (p < lo[c]) {
                            lo[c] = p;
                        } else if (hi[c] < p) {
                            hi[c] = p;
                        }
                    }
                }
            }
            break;
        case 2:
            if (!trs_matrix(n.m, s, (s->flags >> 1) & 1, sn, cs)) {
                n.flags = fl | 0x1000000;
                identity_matrix(n.m, s);
            }
            transform_22286c(n.out, n.m);
            break;
        case 3:
            if (!fit_407eec(n.m, s->rot, s->count, true)) {
                n.flags |= 0x40000000;
            } else {
                bounds_4086c8(s->radius, &n.m[4], &n.m[8], s->rot, s->count, n.m);
            }
            break;
        case 4:
            if (s->keys > 2) {
                if (!trs_matrix(n.m, s, (s->flags >> 1) & 1, sn, cs)) {
                    n.flags = fl | 0x1000000;
                    identity_matrix(n.m, s);
                }
                transform_22286c(n.out, n.m);
            } else {
                n.flags |= 0x40000000;
            }
            break;
        }
    }
    Header400e40* hh = resource->header;
    if (hh != nullptr && hh->flags_offset != 0) {
        const unsigned int* fl = reinterpret_cast<const unsigned int*>(hh->base() + hh->flags_offset);
        if (fl != nullptr) {
            mask = 0;
            unsigned int m = fl[0] & 1;
            mask = m;
            if (fl[0] & 2) {
                m |= 2;
                mask = m;
            }
            if (fl[0] & 4) {
                m |= 4;
                mask = m;
            }
            copy_ids(0, &fl[1], m);
            copy_ids(1, &fl[5], m);
            copy_ids(2, &fl[9], m);
        }
    }
    x1a8 = 0;
    x1a4 = 0;
    x1b4 = 1.0f;
    x1b0 = 1.0f;
    x1b8 = 0;
    x30 = 0;
    return true;
}
