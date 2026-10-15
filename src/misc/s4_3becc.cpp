// A draw command's set-up and statistics (fourth session, template families 3becc and 3c108): DrawCmd::init copies the
// source's fields, looks up the node it is attached to and counts the command in its mesh's counter block, allocating
// the block from a pool when the mesh has none; Stats::add counts a command's mesh items by its kind. The original has
// four identical copies of each (DrawCmd::init: 0x710003becc, 0x71003e6020, 0x71003e63e0, 0x71004439e8; Stats::add:
// 0x710003c108, 0x71003e625c, 0x71003e661c, 0x7100443c24: functions compiled into four objects), written here as
// templates with a dummy copy number. Names are descriptive placeholders.
// The table lookups read the table into a local before indexing it (the index comes out in the second register), the
// node index is computed before the node array is read, and the id lists compare their count first. In Stats::add the
// command's offset is an int, one sign extension shared by all loops (so InstCombine does not widen the index adds),
// the row is read before the column (GVN widens the row's load over column and kind), Stats is 8-aligned (the totals'
// loads widen as well) and the second loop of kind 0 computes its end once.
void* callee_583e2c(void*, void*);
void callee_583e4c(void*, void*, void*);

struct Entry {
    unsigned char pad0[0x1c];
    int value;                // +1c
};
struct EntryTable {
    unsigned char pad0[0x10];
    Entry** entries;          // +10
};
struct MeshTable;
struct Resource {
    unsigned char pad0[0x40];
    EntryTable* table;        // +40
};

static inline Entry* entry_at(EntryTable* t, unsigned int i) { return t->entries[i]; }

struct IdList {
    unsigned char pad0[6];
    short count;              // +06
    unsigned char pad8[4];
    short ids[1];             // +0c
};
struct NodeEntry {
    IdList* list;             // +00
};
struct NodeEntryTable {
    unsigned char pad0[0x10];
    NodeEntry** entries;      // +10
};
struct NodeRes {
    unsigned char pad0[0x40];
    NodeEntryTable* table;    // +40
};
struct Mapping {
    unsigned char pad0[0xc];
    int node;                 // +0c
};
struct MapEntry {
    unsigned char pad0[8];
    Mapping* mapping;         // +08
};
struct MapEntryTable {
    unsigned char pad0[0x10];
    MapEntry** entries;       // +10
};
struct MapRes {
    unsigned char pad0[0x40];
    MapEntryTable* table;     // +40
};

struct Skeleton {
    unsigned int index;       // +00
    unsigned char pad4[4];
    NodeRes* res;             // +08
    unsigned char* nodes;     // +10: 0x40-byte nodes
};

struct MeshItem {
    unsigned char pad0[4];
    short id;                 // +04
};
struct MeshList {
    unsigned char pad0[0x14];
    unsigned int n0;          // +14
    unsigned int n1;          // +18
    unsigned char pad1c[0x14];
    MeshItem* items[1];       // +30
};
struct MeshRow {
    MeshList** lists;
};
struct MeshTable {
    unsigned char pad0[0x10];
    MeshRow rows[1];          // +10
};

struct Mesh {
    unsigned char pad0[0x90];
    void* f90;                // +90
};

struct Source {
    unsigned char pad0[8];
    unsigned int index;       // +08
    unsigned char padc[4];
    Resource* res;            // +10
    void* f18;                // +18
    Skeleton* skel;           // +20
    unsigned char pad28[0x10];
    Mesh* mesh;               // +38
    unsigned char pad40[8];
    void* f48;                // +48
    void* f50;                // +50
    unsigned char pad58[0x10];
    unsigned short flags;     // +68
    unsigned char f6a;        // +6a
    unsigned char f6b;        // +6b
    int node;                 // +6c
    void* f70;                // +70
};

struct Counts {
    unsigned short rows[8][8];  // +00
    unsigned short f80;         // +80
    unsigned char pad82[6];
};
struct Pool {
    int* next;                  // +00
    long used;                  // +08
};

struct DrawCmd {
    int value;                // +00
    unsigned char mode;       // +04
    unsigned char f5;         // +05
    unsigned char f6;         // +06
    unsigned char f7;         // +07
    unsigned char row;        // +08
    unsigned char col;        // +09
    unsigned short kind;      // +0a
    float fc;                 // +0c
    short f10;                // +10
    short base;               // +12
    unsigned char pad14[4];
    void* f18;                // +18
    Counts* counts;           // +20
    void* node;               // +28
    void* f30;                // +30
    void* f38;                // +38
    void* f40;                // +40
    void* f48;                // +48
    Source* src;              // +50
    void* f58;                // +58

    template <int Copy>
    void init(void* owner, Pool* pool, Source* s, unsigned char row_, short fa_, void* f58_, short f10_,
              unsigned short f12_, void* f18_, float fc_);
};

static inline MapEntry* map_entry(Resource* r, unsigned int i) { return reinterpret_cast<MapRes*>(r)->table->entries[i]; }

static inline int node_index(Source* t, NodeEntry* e) {
    int n = t->node;
    if (n >= 0) {
        IdList* l = e->list;
        return l->count > n ? l->ids[n] : -1;
    }
    int m = map_entry(t->res, t->index)->mapping->node;
    if (m >= 0) return m;
    unsigned int k = m & 0x7fffffff;
    IdList* l = e->list;
    return l->count > (int)k ? l->ids[k] : -1;
}
template <int Copy>
void DrawCmd::init(void* owner, Pool* pool, Source* s, unsigned char row_, short fa_, void* f58_, short f10_,
               unsigned short f12_, void* f18_, float fc_) {
    row = row_;
    col = s->index;
    kind = fa_;
    src = s;
    f18 = f18_;
    f10 = f10_;
    base = f12_;
    f30 = s->f18;
    f38 = s->skel ? s->skel->nodes : 0;
    f40 = s->f48;
    f48 = s->f50;
    unsigned short fl = s->flags;
    mode = (fl & 0xff) == 1 ? ((fl & 0xff00) == 0x100 ? 6 : 3) : 3;
    f5 = s->flags;
    f6 = s->f6a;
    f7 = s->f6b;
    EntryTable* et = s->res->table;
    value = et->entries[s->index]->value;
    Mesh* mesh = s->mesh;
    if (mesh && mesh->f90) {
        Counts* c = static_cast<Counts*>(callee_583e2c(mesh, owner));
        counts = c;
        Source* t = src;
        void* nd = t->f70;
        if (!nd) {
            Skeleton* sk = t->skel;
            if (sk) {
                NodeEntryTable* nt = sk->res->table;
                NodeEntry* e = nt->entries[sk->index];
                long idx = node_index(t, e);
                nd = sk->nodes + (idx << 6);
            }
        }
        node = nd;
        if (!c) {
            int* r = pool->next;
            pool->used += 0x22;
            int id = *r;
            pool->next = r + 0x22;
            *pool->next = id + 0x22;
            counts = reinterpret_cast<Counts*>(r);
            __builtin_memset(r, 0, 0x88);
            callee_583e4c(mesh, owner, counts);
            counts->rows[2][0] = 0xffff;
            c = counts;
        }
        c->rows[row][col]++;
        counts->f80++;
    } else {
        counts = 0;
        node = 0;
    }
    f58 = f58_;
    fc = fc_;
}

struct Stats {
    void* head;
    unsigned char pad8[0x14];
    int calls;                // +1c
    int counts0[0x100];       // +20
    int counts1[0x100];       // +420
    int total0;               // +820
    int total1;               // +824

    template <int Copy> void add(DrawCmd* c);
};

template <int Copy>
void Stats::add(DrawCmd* c) {
    calls++;
    Resource* res = c->src->res;
    MeshRow* r = &reinterpret_cast<MeshTable*>(res->table)->rows[c->row];
    MeshList* m = r->lists[c->col];
    int b = c->base;
    switch (c->kind) {
    case 0: {
        unsigned int n0 = m->n0;
        for (unsigned int i = 0; i < n0; i++) counts0[m->items[i]->id + b]++;
        total0 += m->n0;
        unsigned int end = n0 + m->n1;
        for (unsigned int i = m->n0; i < end; i++) counts1[m->items[i]->id + b]++;
        total1 += m->n1;
        break;
    }
    case 1: {
        unsigned int n = m->n0 + m->n1;
        for (unsigned int i = 0; i < n; i++) counts1[m->items[i]->id + b]++;
        total1 += n;
        break;
    }
    case 2: {
        unsigned int n = m->n0 + m->n1;
        for (unsigned int i = 0; i < n; i++) counts0[m->items[i]->id + b]++;
        total0 += n;
        break;
    }
    }
}
template void DrawCmd::init<0>(void*, Pool*, Source*, unsigned char, short, void*, short, unsigned short, void*, float);
template void DrawCmd::init<1>(void*, Pool*, Source*, unsigned char, short, void*, short, unsigned short, void*, float);
template void DrawCmd::init<2>(void*, Pool*, Source*, unsigned char, short, void*, short, unsigned short, void*, float);
template void DrawCmd::init<3>(void*, Pool*, Source*, unsigned char, short, void*, short, unsigned short, void*, float);
template void Stats::add<0>(DrawCmd*);
template void Stats::add<1>(DrawCmd*);
template void Stats::add<2>(DrawCmd*);
template void Stats::add<3>(DrawCmd*);
