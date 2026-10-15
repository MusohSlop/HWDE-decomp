// Fifth session, parked: family (d) pair, 0x7100503bd0 (and its sibling 0x7100504188: the other shape's transform
// 0x71005076b8, support vtable GOT 0x7100c2cf50 and contact callee 0x71004f475c), 1,460 bytes each; 1,468 bytes
// here, 25 instructions off abstracted. A capsule-mesh contact: the capsule copied (0x28 bytes, non-POD) and
// moved into the body's frame by the inverse matrix, two support objects (one built through a base and a derived
// class: base vtable, identity matrix, the mesh centre from 0x71004ffd2c, then the derived vtable), a GJK solve
// (0x71004fcea4 init, 0x71004fdd70 solve, returns false -> 0), the closest points transformed back (the family (a)
// tail), the shape callee for the first contact id, and the second id encoded from the simplex (vertex, edge or
// face rotated to its smallest index; a degenerate face, 0x71005078c4, falls back to its longest edge).
// Settled: the matrix temporary in its own scope (it shares the solver's slot), unsigned long return (mov x0, xzr),
// the three simplex indices as separate members (two of them are read as one 64-bit load), the result points in a
// local that escapes with the contact point (pt, a, b at sp+0x50/0x60/0x70) and copied from the solver as one
// 32-byte pair, the w stores b then a, the edge lengths written inline. Still off: the support objects' stores
// (the original pairs the first one's vptr and pointer), the solver's second point is copied in the original
// with its own address but ours reuses the constructor's (x21 + 0x10, an extra callee-saved register), the
// contact point copy after the sqrt split reads through a register, the 3x3 normal transform (same leftover as
// family a; irsearch on the tail block finds 22 with orders that do not map to source), and the vertex id.
// Maps (tools/s5/sbs.py, build/s5/fd/s.ps1 has them all):
//   valid_5078c4=0x71005078c4 center_4ffd2c=0x71004ffd2c inverse_22286c=0x710022286c transform_506df8=0x7100506df8
//   Shape503bd0::contact=0x71004f481c Gjk503bd0::init=0x71004fcea4 Gjk503bd0::solve=0x71004fdd70
//   got:_ZTV20CapsuleSupport503bd0=0x7100c2cf48 got:_ZTV21MeshSupportBase503bd0=0x7100c2cf70
//   got:_ZTV17MeshSupport503bd0=0x7100c2cf78
#include "misc/matrix_inverse.h"

extern "C" float sqrtf(float);

union Vec4u {
    float32x4_t v;
    float f[4];
    long l[2];
    int i[4];
    struct {
        float x, y, z, w;
    };
};

// A vector whose default constructor zeroes w.
union Dir503bd0 {
    float32x4_t v;
    float f[4];
    long l[2];
    int i[4];
    struct {
        float x, y, z, w;
    };
    Dir503bd0() { w = 0.0f; }
};

union ContactId503bd0 {
    unsigned long raw;
    struct {
        unsigned long kind : 8;
        unsigned long v : 14;
        unsigned long rest : 42;
    } vertex;
    struct {
        unsigned long kind : 8;
        unsigned long a : 14;
        unsigned long b : 15;
        unsigned long rest : 27;
    } edge;
    struct {
        unsigned long kind : 8;
        unsigned long a : 16;
        unsigned long b : 16;
        unsigned long c : 16;
        unsigned long top : 8;
    } face;
};

struct Result503bd0 {
    Vec4u p0;                         // +0
    Vec4u p1;                         // +10
    Vec4u n;                          // +20
    ContactId503bd0 a;                // +30
    ContactId503bd0 b;                // +38
    unsigned char pad40[0xc0];
    int found;                        // +100
};

struct Capsule503bd0 {
    Dir503bd0 p;                      // +0
    Dir503bd0 q;                      // +10
    float radius;                     // +20
    float length;                     // +24
};

struct Mesh503bd0 {
    unsigned char pad0[0x3c];
    unsigned short verts;             // +3c (offset of the vertex array, from +20)
};

struct Body503bd0 {
    XMMATRIX world;                   // +0
    unsigned char pad40[0x28];
    Mesh503bd0* mesh;                 // +68
};

void inverse_22286c(XMMATRIX* out, const Body503bd0* body);                         // 0x710022286c
void transform_506df8(Capsule503bd0* c, const XMMATRIX* m);                          // 0x7100506df8
void center_4ffd2c(Mesh503bd0* mesh, Dir503bd0* out);                                 // 0x71004ffd2c
unsigned char valid_5078c4(const Vec4u* a, const Vec4u* b, const Vec4u* c);    // 0x71005078c4

struct Support503bd0 {
    virtual void support();
};

struct CapsuleSupport503bd0 : Support503bd0 {
    Capsule503bd0* shape;
    CapsuleSupport503bd0(Capsule503bd0* c) : shape(c) {}
    void support();
};

struct MeshSupportBase503bd0 : Support503bd0 {
    XMMATRIX m;                       // +10
    Dir503bd0 center;                 // +50
    Dir503bd0 extent;                 // +60
    float scale;                      // +70
    Mesh503bd0* mesh;                 // +78
    MeshSupportBase503bd0(Mesh503bd0* mh) : m(XMMatrixIdentity()), scale(1.0f), mesh(mh) {
        center_4ffd2c(mh, &center);
    }
    void support();
};

struct MeshSupport503bd0 : MeshSupportBase503bd0 {
    MeshSupport503bd0(Mesh503bd0* mh) : MeshSupportBase503bd0(mh) {}
    void support();
};

struct Gjk503bd0 {
    Dir503bd0 v[18];                  // +0
    unsigned char pad120[0x10];
    bool done;                        // +130
    unsigned char pad131[0x1b];
    int i0;                           // +14c
    int i1;                           // +150
    int i2;                           // +154

    Gjk503bd0() : done(false) {}
    void init(Support503bd0* a, Support503bd0* b);                                 // 0x71004fcea4
    unsigned char solve(Vec4u* normal);                                            // 0x71004fdd70
};

struct Pair503bd0 {
    Vec4u a;
    Vec4u b;
};

struct Seg503bd0 {
    Vec4u pt;
    Pair503bd0 pr;
};

struct Shape503bd0 {
    static void contact(ContactId503bd0* out, const Capsule503bd0* s, const Vec4u* p, const Vec4u* n,
                        ContactId503bd0* other);  // 0x71004f481c
};

static inline float dist(const Vec4u& a, const Vec4u& b) {
    return sqrtf((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) + (b.z - a.z) * (b.z - a.z));
}

// 0x7100503bd0
unsigned long contact_503bd0(Result503bd0* out, const Capsule503bd0* s, const Body503bd0* body) {
    Capsule503bd0 c;
    {
        XMMATRIX inv;
        inverse_22286c(&inv, body);
        c = *s;
        transform_506df8(&c, &inv);
    }
    CapsuleSupport503bd0 sa(&c);
    MeshSupport503bd0 sb(body->mesh);
    Gjk503bd0 g;
    g.init(&sa, &sb);
    if (!g.solve(&out->n)) {
        return 0;
    }
    Seg503bd0 seg;
    seg.pr = *reinterpret_cast<const Pair503bd0*>(&g);
    seg.pr.b.w = 1.0f;
    seg.pr.a.w = 1.0f;
    seg.pr.a.v = XMVector4Transform(seg.pr.a.v, body->world);
    seg.pr.b.v = XMVector4Transform(seg.pr.b.v, body->world);
    out->p0 = seg.pr.a;
    out->p1 = seg.pr.b;
    const float(*m)[4] = reinterpret_cast<const float(*)[4]>(&body->world);
    float rx = m[0][0] * out->n.x + m[1][0] * out->n.y + m[2][0] * out->n.z;
    float ry = out->n.x * m[0][1] + out->n.y * m[1][1] + out->n.z * m[2][1];
    float rz = out->n.x * m[0][2] + out->n.y * m[1][2] + out->n.z * m[2][2];
    out->n.x = rx;
    out->n.y = ry;
    out->n.z = rz;
    float inv2 = 1.0f / sqrtf(out->n.x * out->n.x + out->n.y * out->n.y + out->n.z * out->n.z);
    float x = out->n.x * inv2;
    float y = inv2 * out->n.y;
    float z = inv2 * out->n.z;
    out->n.x = x;
    out->n.y = y;
    out->n.z = z;
    seg.pt = seg.pr.a;
    seg.pt.i[3] = 0;
    Shape503bd0::contact(&out->a, s, &seg.pt, &out->n, nullptr);
    int i0 = g.i0, i1 = g.i1, i2 = g.i2;
    if (i0 == i1) {
        if (i0 == i2) {
            out->b.vertex.kind = 2;
            out->b.vertex.v = i0;
        } else {
            out->b.edge.kind = 1;
            out->b.edge.a = i0;
            out->b.edge.b = i2;
        }
    } else if (i0 == i2 || i1 == i2) {
        out->b.edge.kind = 1;
        out->b.edge.a = i0;
        out->b.edge.b = i1;
    } else {
        out->b.face.kind = 5;
        if (i1 < i0 && i1 < i2) {
            out->b.face.c = i0;
            out->b.face.a = i1;
            out->b.face.b = i2;
        } else if (i2 < i0 && i2 < i1) {
            out->b.face.b = i0;
            out->b.face.c = i1;
            out->b.face.a = i2;
        } else {
            out->b.face.a = i0;
            out->b.face.b = i1;
            out->b.face.c = i2;
        }
        Mesh503bd0* mesh = body->mesh;
        const Vec4u* verts = reinterpret_cast<const Vec4u*>(reinterpret_cast<const char*>(mesh) + mesh->verts + 0x20);
        unsigned long idx[3] = {out->b.face.a, out->b.face.b, out->b.face.c};
        Vec4u tri[3];
        for (int k = 0; k < 3; k++) {
            tri[k] = verts[idx[k]];
            tri[k].i[3] = 0;
        }
        if (!valid_5078c4(&tri[0], &tri[1], &tri[2])) {
            out->b.raw = 0;
            float best = -3.4028235e38f;
            float d01 = dist(tri[0], tri[1]);
            if (d01 > best) {
                best = d01;
            }
            float d02 = dist(tri[0], tri[2]);
            int ea = 0, eb = 1;
            if (d02 > best) {
                best = d02;
                eb = 2;
            }
            float d12 = dist(tri[1], tri[2]);
            if (d12 > best) {
                ea = 1;
                eb = 2;
            }
            out->b.edge.kind = 1;
            out->b.edge.a = idx[ea];
            out->b.edge.b = idx[eb];
        }
    }
    if (out->a.vertex.kind == 2) {
        out->a.vertex.rest = 0;
    }
    out->found = 1;
    return 1;
}
