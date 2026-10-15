// The uniform setters (fifth session): one template instantiated for six shader stages (0x71005a5b64 0x71005a60cc
// 0x71005a6634 0x71005a6b9c 0x71005a7104 0x71005a766c). Each writes a uniform's value into the stage's constant
// buffer (buffers[stage][loc >> 28] + (loc & 0xffff), one 16-byte slot per element) and marks the buffer dirty: an
// array of first + len elements (clamped to the stage's count) or a single value, by type (1 float, 2 vec2, 3 vec3,
// 4 vec4, 5 and 6 ints that may be stored inline, 7 mat4). Stages 0 and 4 keep their location and count in the
// uniform's base fields, the others in its extension; the template takes them as member pointers.
// The dirty bit is set in every case (the identical or/store tails are merged by branch folding); the inline loops
// test i != n (the others i < n), which lets LSR count them down; the single vec4 stores its high half first.
// Struct, field and callee names are placeholders after the address and offset, as in the generated units.
// Status: matching/README.md.
extern "C" void* memcpy(void*, const void*, unsigned long);

struct Uniform5a5b64 {
    unsigned int loc0;                // +0
    unsigned int loc4;                // +4
    unsigned char pad8[0x8];
    short type;                       // +10
    unsigned short inl;               // +12
    unsigned char pad14[0x2];
    unsigned short first;             // +16
    unsigned short len;               // +18
    unsigned short count0;            // +1a
    unsigned short count4;            // +1c
    unsigned char pad1e[0x6];
    unsigned int loc1;                // +24
    unsigned int loc2;                // +28
    unsigned int loc3;                // +2c
    unsigned int loc5;                // +30
    unsigned char pad34[0x10];
    unsigned short count1;            // +44
    unsigned short count2;            // +46
    unsigned short count3;            // +48
    unsigned short count5;            // +4a
    unsigned char pad4c[0x14];
    union {
        const void* ptr;              // +60
        unsigned int u[4];
        unsigned long l[2];
    };
};

struct Vec3_5a5b64 {
    unsigned long xy;
    unsigned int z;
} __attribute__((packed, aligned(4)));

struct Slot1_5a5b64 {
    unsigned int x;
    unsigned int pad[3];
};
struct Slot2_5a5b64 {
    unsigned long xy;
    unsigned long pad;
};
struct Slot3_5a5b64 {
    Vec3_5a5b64 v;
    unsigned int pad;
};

struct Ctx5a5b64 {
    unsigned char pad0[0x670];
    unsigned int dirty[6];            // +670
    unsigned char pad688[0x18];
    char* buffers[6][14];             // +6a0

    template <int S>
    char* at(unsigned int loc) {
        return buffers[S][loc >> 28] + (loc & 0xffff);
    }

    template <int S, bool Ext, unsigned int Uniform5a5b64::*Loc, unsigned short Uniform5a5b64::*Count>
    void set(const Uniform5a5b64* u);
};

template <int S, bool Ext, unsigned int Uniform5a5b64::*Loc, unsigned short Uniform5a5b64::*Count>
void Ctx5a5b64::set(const Uniform5a5b64* u) {
    unsigned int loc = u->*Loc;
    unsigned short count = u->*Count;
    if (count != 0) {
        unsigned int n = u->first + u->len;
        if (n > count) {
            n = count;
        }
        const void* data = u->ptr;
        switch (u->type) {
        case 1: {
            const unsigned int* src = static_cast<const unsigned int*>(data);
            Slot1_5a5b64* d = reinterpret_cast<Slot1_5a5b64*>(at<S>(loc));
            for (unsigned int i = 0; i < n; i++) {
                d->x = *src;
                src++;
                d++;
            }
            dirty[S] |= 1u << (loc >> 28);
            break;
        }
        case 2: {
            const unsigned long* src = static_cast<const unsigned long*>(data);
            Slot2_5a5b64* d = reinterpret_cast<Slot2_5a5b64*>(at<S>(loc));
            for (unsigned int i = 0; i < n; i++) {
                d->xy = *src;
                src++;
                d++;
            }
            dirty[S] |= 1u << (loc >> 28);
            break;
        }
        case 3: {
            const Vec3_5a5b64* src = static_cast<const Vec3_5a5b64*>(data);
            Slot3_5a5b64* d = reinterpret_cast<Slot3_5a5b64*>(at<S>(loc));
            for (unsigned int i = 0; i < n; i++) {
                d->v = *src;
                src++;
                d++;
            }
            dirty[S] |= 1u << (loc >> 28);
            break;
        }
        case 4:
            memcpy(at<S>(loc), data, n * 16ul);
            dirty[S] |= 1u << (loc >> 28);
            break;
        case 5: {
            if (u->inl == 1) {
                const unsigned int* src = u->u;
                Slot1_5a5b64* d = reinterpret_cast<Slot1_5a5b64*>(at<S>(loc));
                for (unsigned int i = 0; i != n; i++) {
                    d->x = *src;
                    src++;
                    d++;
                }
            } else {
                const unsigned int* src = static_cast<const unsigned int*>(data);
                Slot1_5a5b64* d = reinterpret_cast<Slot1_5a5b64*>(at<S>(loc));
                for (unsigned int i = 0; i < n; i++) {
                    d->x = *src;
                    src++;
                    d++;
                }
            }
            dirty[S] |= 1u << (loc >> 28);
            break;
        }
        case 6: {
            if (u->inl == 1) {
                const unsigned int* src = u->u;
                Slot1_5a5b64* d = reinterpret_cast<Slot1_5a5b64*>(at<S>(loc));
                for (unsigned int i = 0; i != n; i++) {
                    d->x = *src;
                    src++;
                    d++;
                }
            } else {
                const unsigned int* src = static_cast<const unsigned int*>(data);
                Slot1_5a5b64* d = reinterpret_cast<Slot1_5a5b64*>(at<S>(loc));
                for (unsigned int i = 0; i < n; i++) {
                    d->x = *src;
                    src++;
                    d++;
                }
            }
            dirty[S] |= 1u << (loc >> 28);
            break;
        }
        case 7:
            memcpy(at<S>(loc), data, n * 64ul);
            dirty[S] |= 1u << (loc >> 28);
            break;
        default:
            return;
        }
    } else {
        switch (u->type) {
        case 1:
        case 5:
        case 6:
            if (Ext) {
                unsigned int* d = reinterpret_cast<unsigned int*>(at<S>(loc));
                *d = u->u[0];
            } else {
                *reinterpret_cast<unsigned int*>(at<S>(loc)) = u->u[0];
            }
            dirty[S] |= 1u << (loc >> 28);
            break;
        case 2: {
            unsigned long* d = reinterpret_cast<unsigned long*>(at<S>(loc));
            *d = u->l[0];
            dirty[S] |= 1u << (loc >> 28);
            break;
        }
        case 3:
            *reinterpret_cast<Vec3_5a5b64*>(at<S>(loc)) = *reinterpret_cast<const Vec3_5a5b64*>(u->u);
            dirty[S] |= 1u << (loc >> 28);
            break;
        case 4: {
            unsigned long* d = reinterpret_cast<unsigned long*>(at<S>(loc));
            d[1] = u->l[1];
            d[0] = u->l[0];
            dirty[S] |= 1u << (loc >> 28);
            break;
        }
        case 7: {
            const void* src = u->ptr;
            memcpy(at<S>(loc), src, 0x40);
            dirty[S] |= 1u << (loc >> 28);
            break;
        }
        default:
            return;
        }
    }
}

template void Ctx5a5b64::set<0, false, &Uniform5a5b64::loc0, &Uniform5a5b64::count0>(const Uniform5a5b64*);  // 0x71005a5b64
template void Ctx5a5b64::set<4, false, &Uniform5a5b64::loc4, &Uniform5a5b64::count4>(const Uniform5a5b64*);  // 0x71005a60cc
template void Ctx5a5b64::set<1, true, &Uniform5a5b64::loc1, &Uniform5a5b64::count1>(const Uniform5a5b64*);  // 0x71005a6634
template void Ctx5a5b64::set<2, true, &Uniform5a5b64::loc2, &Uniform5a5b64::count2>(const Uniform5a5b64*);  // 0x71005a6b9c
template void Ctx5a5b64::set<3, true, &Uniform5a5b64::loc3, &Uniform5a5b64::count3>(const Uniform5a5b64*);  // 0x71005a7104
template void Ctx5a5b64::set<5, true, &Uniform5a5b64::loc5, &Uniform5a5b64::count5>(const Uniform5a5b64*);  // 0x71005a766c
