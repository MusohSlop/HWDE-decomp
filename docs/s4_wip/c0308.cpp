// 0x71000c0308 (1,536 B), fourth session, parked. Build: this file alone, try.py with
//   --map _Z11callee_8b30P9Vec4c0308S0_S0_=0x7100008b30 and build/s3rank/rc0308_d.json from rank.py.
// State: 1,492 B, 40 instructions off with registers abstracted. What is right: bone lookups (the LOD list
// through an accessor so the base loads before the index), quaternion from matrix (be28c), axis switch with
// case 2 tested first, rotate into a temporary then copy (so the axis w is copied as an int), normalise in
// memory (the loads after sqrtf give x*inv, inv*y, inv*z through Reassociate ranks), quaternion product,
// slerp at t = 0.5 with the asin/sin polynomials, a >= pi/2 select.
// Still different: (1) the four address phis of the axis come out z,y,x,w (original x,y,z,w: the w add
// first and x coalesced with the GOT base); (2) the translation copy: the original keeps four address phis
// (+30..+3c of either matrix) and loads after the join, ours folds them into one pointer phi; (3) operand
// order of the slerp products (original: qA.x*s and q.x*s but s*qA.y.. s*q.w, i.e. only the x loads rank
// below the phi s) and of the quaternion-to-matrix products; (4) qA.w*r.w in the dot product.
extern "C" float sqrtf(float);

struct Vec4c0308 {
    float x, y, z, w;
};

struct Mtx44c0308 {
    Vec4c0308 r[3];
    int t[4];
};

struct BoneMapc0308 {
    unsigned char pad0[6];
    short count;                   // +6
    unsigned char pad8[4];
    short index[1];                // +c
};

struct Lodc0308 {
    BoneMapc0308* map;             // +0
};

struct LodListc0308 {
    unsigned char pad0[0x10];
    Lodc0308** lods;               // +10

    Lodc0308* at(unsigned int i) {
        return lods[i];
    }
};

struct SkelResc0308 {
    unsigned char pad0[0x40];
    LodListc0308* lodList;         // +40
};

struct Skelc0308 {
    unsigned char pad0[8];
    unsigned int lod;              // +8
    unsigned char padc[4];
    SkelResc0308* res;             // +10
    Mtx44c0308* mtx;               // +18

    Mtx44c0308* boneMtx(int bone) {
        BoneMapc0308* m = res->lodList->at(lod)->map;
        int i = m->count > bone ? m->index[bone] : -1;
        return &mtx[i];
    }
};

class Checkerc0308 {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();
    virtual void slot_4();
    virtual void slot_5();
    virtual void slot_6();
    virtual void slot_7();
    virtual void slot_8();
    virtual void slot_9();
    virtual void slot_10();
    virtual void slot_11();
    virtual void slot_12();
    virtual void slot_13();
    virtual void slot_14();
    virtual void slot_15();
    virtual void slot_16();
    virtual void slot_17();
    virtual void slot_18();
    virtual void slot_19();
    virtual void slot_20();
    virtual void slot_21();
    virtual void slot_22();
    virtual void slot_23();
    virtual void slot_24();
    virtual void slot_25();
    virtual void slot_26();
    virtual void slot_27();
    virtual void slot_28();
    virtual void slot_29();
    virtual void slot_30();
    virtual void slot_31();
    virtual void slot_32();
    virtual void slot_33();
    virtual void slot_34();
    virtual void slot_35();
    virtual void slot_36();
    virtual void slot_37();
    virtual void slot_38();
    virtual void slot_39();
    virtual void slot_40();
    virtual void slot_41();
    virtual void slot_42();
    virtual void slot_43();
    virtual void slot_44();
    virtual void slot_45();
    virtual void slot_46();
    virtual void slot_47();
    virtual void slot_48();
    virtual void slot_49();
    virtual void slot_50();
    virtual void slot_51();
    virtual void slot_52();
    virtual void slot_53();
    virtual void slot_54();
    virtual void slot_55();
    virtual void slot_56();
    virtual void slot_57();
    virtual void slot_58();
    virtual void slot_59();
    virtual void slot_60();
    virtual void slot_61();
    virtual void slot_62();
    virtual void slot_63();
    virtual void slot_64();
    virtual void slot_65();
    virtual void slot_66();
    virtual void slot_67();
    virtual void slot_68();
    virtual void slot_69();
    virtual void slot_70();
    virtual void slot_71();
    virtual void slot_72();
    virtual void slot_73();
    virtual void slot_74();
    virtual void slot_75();
    virtual void slot_76();
    virtual void slot_77();
    virtual void slot_78();
    virtual void slot_79();
    virtual void slot_80();
    virtual void slot_81();
    virtual void slot_82();
    virtual void slot_83();
    virtual void slot_84();
    virtual void slot_85();
    virtual void slot_86();
    virtual void slot_87();
    virtual void slot_88();
    virtual void slot_89();
    virtual unsigned char slot_90(int);
};

struct Ownerc0308 {
    unsigned char pad0[8];
    Checkerc0308* checker;         // +8
};

// Reached through the GOT slot at 0x7100c216f8.
extern Vec4c0308 gGlobalc216f8_c0308[3];

void callee_be28c(Vec4c0308*, Mtx44c0308*);                                  // 0x71000be28c
void callee_8b30(Vec4c0308*, Vec4c0308*, Vec4c0308*);                         // 0x7100008b30

static inline void rotNorm_c0308(Vec4c0308& d, const Vec4c0308& v, const Mtx44c0308& m) {
    Vec4c0308 r = v;
    r.x = v.x * m.r[0].x + v.y * m.r[1].x + v.z * m.r[2].x;
    r.y = v.x * m.r[0].y + v.y * m.r[1].y + v.z * m.r[2].y;
    r.z = v.x * m.r[0].z + v.y * m.r[1].z + v.z * m.r[2].z;
    d = r;
    float inv = 1.0f / sqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
    d.x *= inv;
    d.y *= inv;
    d.z *= inv;
}

static inline Vec4c0308 axis_c0308(int axis) {
    switch (axis) {
    case 2:
        return gGlobalc216f8_c0308[2];
    case 1:
        return gGlobalc216f8_c0308[1];
    default:
        return gGlobalc216f8_c0308[0];
    }
}

// 0x71000c0308
void call_c0308(Ownerc0308* p0, Skelc0308* p1, int boneA, int boneB, int boneOut, int axis, unsigned char apply) {
    Vec4c0308 qA;
    Vec4c0308 qB;
    Vec4c0308 dirA;
    Vec4c0308 dirB;
    Vec4c0308 q;
    Mtx44c0308* mA = p1->boneMtx(boneA);
    callee_be28c(&qA, mA);
    Mtx44c0308* mB = p1->boneMtx(boneB);
    callee_be28c(&qB, mB);
    Vec4c0308 v = axis_c0308(axis);
    rotNorm_c0308(dirA, v, *mA);
    rotNorm_c0308(dirB, v, *mB);
    callee_8b30(&q, &dirB, &dirA);
    {
        float qw = q.w, bw = qB.w, bx = qB.x, qx = q.x, qy = q.y, bz = qB.z, qz = q.z, by = qB.y;
        float x = (qw * bx + bw * qx) + (qy * bz - qz * by);
        float y = (bw * qy + qw * by) + (bx * qz - qx * bz);
        float z = (qw * bz + bw * qz) + (qx * by - bx * qy);
        float w = qw * bw - (bz * qz + (bx * qx + qy * by));
        q.x = x;
        q.y = y;
        q.z = z;
        q.w = w;
    }
    {
        float d = qA.x * q.x + qA.y * q.y + qA.z * q.z + qA.w * q.w;
        float s = 0.5f;
        if (d > -0.9f && d < 0.9f) {
            float d2 = d * d;
            float a = 1.5707964f - d * (d2 * (d2 * (d2 * (d2 * 0.041791946f + 0.044642858f) + 0.075f) + 0.16666667f) + 1.0f);
            if (a >= 1.5707964f) {
                a = 3.1415927f - a;
            }
            float a2 = a * a;
            float h2 = a2 * 0.25f;
            s = (1.0f / (a2 * (a2 - 20.0f) + 120.0f)) * ((h2 * (h2 - 20.0f) + 120.0f) * 0.5f);
        }
        if (d < 0.0f) {
            q.x = qA.x * s - q.x * s;
            q.y = qA.y * s - q.y * s;
            q.z = qA.z * s - q.z * s;
            q.w = qA.w * s - q.w * s;
        } else {
            q.x = qA.x * s + q.x * s;
            q.y = qA.y * s + q.y * s;
            q.z = qA.z * s + q.z * s;
            q.w = qA.w * s + q.w * s;
        }
    }
    Mtx44c0308 m;
    {
        float x = q.x, y = q.y, z = q.z, w = q.w;
        float x2 = x + x;
        float y2 = y + y;
        float z2 = z + z;
        float xx = x * x2;
        float yy = y * y2;
        float zz = z * z2;
        float xy = x2 * y;
        float yz = y2 * z;
        float xz = x * z2;
        float wx = x2 * w;
        float wy = y2 * w;
        float wz = z2 * w;
        m.r[0].x = 1.0f - yy - zz;
        m.r[0].y = xy + wz;
        m.r[0].z = xz - wy;
        m.r[0].w = 0.0f;
        m.r[1].x = xy - wz;
        m.r[1].y = 1.0f - zz - xx;
        m.r[1].z = yz + wx;
        m.r[1].w = 0.0f;
        m.r[2].x = xz + wy;
        m.r[2].y = yz - wx;
        m.r[2].z = 1.0f - xx - yy;
        m.r[2].w = 0.0f;
    }
    int t[4];
    if (apply) {
        if (!p0->checker->slot_90(boneOut)) {
            return;
        }
        Mtx44c0308* o = p1->boneMtx(boneOut);
        t[0] = o->t[0];
        t[1] = o->t[1];
        t[2] = o->t[2];
        t[3] = o->t[3];
    } else {
        t[0] = mA->t[0];
        t[1] = mA->t[1];
        t[2] = mA->t[2];
        t[3] = mA->t[3];
    }
    m.t[0] = t[0];
    m.t[1] = t[1];
    m.t[2] = t[2];
    m.t[3] = t[3];
    if (!p0->checker->slot_90(boneOut)) {
        return;
    }
    *p1->boneMtx(boneOut) = m;
}
