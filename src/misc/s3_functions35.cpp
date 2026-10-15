// Relaxed template families (third session's share of the fourth session's relaxed scan): copies with the same
// code once registers, immediates and relocation targets are abstracted, each written once as a template over
// the type, kind or callee that differs and explicitly instantiated per copy. Names are descriptive
// placeholders. Status: matching/README.md.

extern "C" void* memcpy(void* dest, const void* src, unsigned long size);
inline void* operator new(unsigned long, void* where) noexcept { return where; }

// A program object: reference counted (count at +8, destroyed through its fourth virtual function).
class Program51ca70 {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void destroy();      // +18

    void add_ref() { ++refs; }
    void release() {
        if (--refs == 0)
            destroy();
    }

    int refs;                    // +08
};

// One slot of a render object's table: two ids.
struct Slot51ca70 {
    int id;                      // +00
    int binding;                 // +04
};

// The base of the render objects (its constructor 0x71005325e4 is out of line): a reference count, its program and
// the program's slot table and four query results.
class Base_5325e4 {
public:
    Base_5325e4();
    virtual ~Base_5325e4();
    virtual void v10();
    virtual void destroy();      // +18

    void add_ref() { ++refs; }
    void release() {
        if (--refs == 0)
            destroy();
    }

    int refs;                    // +08
    Program51ca70* program;      // +10
    Slot51ca70* slots;           // +18
    unsigned int count;          // +20
    int result24;                // +24
    int result28;                // +28
    int result2c;                // +2c
    int result30;                // +30
};

class RenderPair : public Base_5325e4 {
public:
    RenderPair();                // 0x7100527bd8
    ~RenderPair() override;

    unsigned char pad34[4];
    void* first;                 // +38
    void* second;                // +40
};

class RenderCount : public Base_5325e4 {
public:
    RenderCount();               // 0x7100527b68
    ~RenderCount() override;

    int count34;                 // +34
};

class RenderIndex : public Base_5325e4 {
public:
    RenderIndex();               // 0x7100527b08
    ~RenderIndex() override;

    int index;                   // +34
};

class Derived_527a38 : public Base_5325e4 {
public:
    Derived_527a38();            // 0x7100527a38
    ~Derived_527a38() override;
};

class RenderTriple : public Base_5325e4 {
public:
    RenderTriple();              // 0x7100527a94
    ~RenderTriple() override;

    int a;                       // +34
    int b;                       // +38
    int c;                       // +3c
};

class Derived_5279dc : public Base_5325e4 {
public:
    Derived_5279dc();            // 0x71005279dc
    ~Derived_5279dc() override;
};

// An allocation's description: a kind (5 here) and two zeros.
struct AllocDesc51ca70 {
    explicit AllocDesc51ca70(short kind_) : kind(kind_), flags(0), extra(0) {}

    short kind;
    short flags;
    long extra;
};

class Allocator51ca70 {
public:
    virtual void v00(); virtual void v08(); virtual void v10(); virtual void v18();
    virtual void v20(); virtual void v28(); virtual void v30(); virtual void v38();
    virtual void* allocate(unsigned long size, unsigned long align, const AllocDesc51ca70& desc);   // +40
};

struct RenderGlobal51ca70;
// Reached through the GOT slot at 0x7100c2d088.
extern RenderGlobal51ca70 gRenderGlobal51ca70;

class Device51ca70;
Program51ca70* make_program_5239ac(int id, const void* data, unsigned long size, void* p5, int i6, void* p7, int i8,
                                   void* table, void* p9);                        // 0x71005239ac
unsigned char link_program_5241fc(Program51ca70* program, void* context, Device51ca70* device, RenderGlobal51ca70* global,
                         void* p5);                                               // 0x71005241fc
unsigned int program_ids_524578(Program51ca70* program, int* ids, int max);      // 0x7100524578
int program_bindings_52476c(Program51ca70* program, int* ids, int max);          // 0x710052476c
int program_query_524904(Program51ca70* program, void* out, int index);          // 0x7100524904
int program_query_524a08(Program51ca70* program, void* out, int index);          // 0x7100524a08
int program_query_524ac0(Program51ca70* program, void* out, int index);          // 0x7100524ac0

// A device: its allocator and context, and a table at +3010.
class Device51ca70 {
public:
    template <class T>
    T* create(const void* data, unsigned long size, int id, unsigned long extra, void* p5, int i6, void* p7, int i8);
    template <class T, int Id>
    T* create_default(const void* data, unsigned long size);
    unsigned char check_binding(int id, int binding);                                      // 0x71005298f8

    unsigned char pad0[0x29d0];
    Allocator51ca70* allocator;  // +29d0
    void* context;               // +29d8
    unsigned char pad29e0[0x630];
    unsigned char table[0x10];   // +3010
};

// A render object of type T for a program built from DATA: allocated with EXTRA bytes after the object, then the
// slot table and a copy of the data; null when the program does not link or a binding is refused.
template <class T>
T* Device51ca70::create(const void* data, unsigned long size, int id, unsigned long extra, void* p5, int i6, void* p7,
                        int i8) {
    Program51ca70* program = make_program_5239ac(id, data, size, p5, i6, p7, i8, table, nullptr);
    T* object = nullptr;
    if (program) {
        if (link_program_5241fc(program, context, this, &gRenderGlobal51ca70, nullptr)) {
            int ids[14];
            unsigned int count = program_ids_524578(program, ids, 14);
            unsigned long table_size = count * sizeof(Slot51ca70);
            unsigned long offset = (sizeof(T) + extra + 15) & ~15ul;
            unsigned long total = offset + size + table_size;
            object = static_cast<T*>(allocator->allocate(total, 16, AllocDesc51ca70(5)));
            if (object) {
                unsigned char* table_start = reinterpret_cast<unsigned char*>(object) + offset;
                Slot51ca70* slots = reinterpret_cast<Slot51ca70*>(table_start);
                void* copy = table_start + table_size;
                new (object) T();
                memcpy(copy, data, size);
                object->program = program;
                program->add_ref();
                object->slots = slots;
                object->count = count;
                int bindings[14];
                object->result24 = program_bindings_52476c(program, bindings, 14);
                object->result28 = program_query_524904(program, nullptr, 0);
                object->result30 = program_query_524a08(program, nullptr, 0);
                object->result2c = program_query_524ac0(program, nullptr, 0);
                for (unsigned int i = 0; i < count; ++i) {
                    object->slots[i].binding = bindings[i];
                    object->slots[i].id = ids[i];
                }
                object->add_ref();
                for (unsigned int i = 0; i < object->count; ++i) {
                    if (!check_binding(id, object->slots[i].binding)) {
                        object->release();
                        object = nullptr;
                        break;
                    }
                }
            }
        }
        program->release();
    }
    return object;
}

template RenderPair* Device51ca70::create<RenderPair>(const void*, unsigned long, int, unsigned long, void*, int, void*, int);          // 0x710051ca70
template RenderCount* Device51ca70::create<RenderCount>(const void*, unsigned long, int, unsigned long, void*, int, void*, int);        // 0x710051ccd4
template RenderIndex* Device51ca70::create<RenderIndex>(const void*, unsigned long, int, unsigned long, void*, int, void*, int);        // 0x710051cf84
template Derived_527a38* Device51ca70::create<Derived_527a38>(const void*, unsigned long, int, unsigned long, void*, int, void*, int);  // 0x710051d21c
template RenderTriple* Device51ca70::create<RenderTriple>(const void*, unsigned long, int, unsigned long, void*, int, void*, int);      // 0x710051d5b4
template Derived_5279dc* Device51ca70::create<Derived_5279dc>(const void*, unsigned long, int, unsigned long, void*, int, void*, int);  // 0x710051d84c

// The plain form: ID fixed, no extra space and no other parameters (0x710051d1e8, 0x710051d818).
template <class T, int Id>
T* Device51ca70::create_default(const void* data, unsigned long size) {
    return create<T>(data, size, Id, 0, nullptr, 0, nullptr, 0);
}

template Derived_527a38* Device51ca70::create_default<Derived_527a38, 2>(const void*, unsigned long);   // 0x710051d1e8
template Derived_5279dc* Device51ca70::create_default<Derived_5279dc, 5>(const void*, unsigned long);   // 0x710051d818

// Small relaxed groups.

extern "C" float tanf(float value);
extern "C" float expf(float value);
extern "C" float logf(float value);

// 57abc8 x7: a uniform value of N bytes written to the fragment stage's bank.
struct FragmentStage57a {
    unsigned char pad0[0x670];
    unsigned int dirty;          // +670
    unsigned char pad674[0x2c];
    unsigned char* banks[16];    // +6a0
};

class UniformBase57a {
public:
    void prepare();              // 0x710057cc80

    unsigned char pad0[0x58];
    unsigned int handle;         // +58: bank in the top four bits, offset in the low 16
    unsigned int pad5c;
};

template <int N, int Copy>
class Uniform57a : public UniformBase57a {
public:
    void upload(FragmentStage57a* stage);

    unsigned char value[N];      // +60
};

template <int N, int Copy>
void Uniform57a<N, Copy>::upload(FragmentStage57a* stage) {
    prepare();
    const unsigned char* source = value;
    unsigned int bank = handle >> 28;
    memcpy(stage->banks[bank] + (handle & 0xffff), source, N);
    stage->dirty |= 1 << bank;
}

template void Uniform57a<0x40, 0>::upload(FragmentStage57a*);   // 0x710057abc8
template void Uniform57a<0x80, 0>::upload(FragmentStage57a*);   // 0x710057acb4
template void Uniform57a<0x30, 0>::upload(FragmentStage57a*);   // 0x710057ada0
template void Uniform57a<0x40, 1>::upload(FragmentStage57a*);   // 0x710057ae8c
template void Uniform57a<0x50, 0>::upload(FragmentStage57a*);   // 0x710057af78
template void Uniform57a<0x60, 0>::upload(FragmentStage57a*);   // 0x710057b064
template void Uniform57a<0x70, 0>::upload(FragmentStage57a*);   // 0x710057b150

// 4c0bb0 x3: an expression op: the next operand evaluated through the handler table, its tangent returned.
typedef float (*Handler4c0b)(int** cursor);
// Reached through the GOT slot at 0x7100c2cd08.
extern Handler4c0b gExprHandlers4c0b[];

template <float (*Function)(float)>
float expr_apply(int** cursor) {
    int* op = *cursor;
    *cursor = op + 1;
    return Function(gExprHandlers4c0b[*op](cursor));
}

template float expr_apply<tanf>(int**);   // 0x71004c0bb0
template float expr_apply<expf>(int**);   // 0x71004c0be0
template float expr_apply<logf>(int**);   // 0x71004c0c10

// 554bb0/5d285c: a value copied into its holder.
struct Value554a { unsigned char data[0x68]; };
struct Value554b { unsigned char data[0x40]; };

template <class T, int Offset>
struct Holder554 {
    void set(const T& value) { this->value = value; }
    void assign(const T& value);

    unsigned char pad0[Offset];
    T value;
};

template <class T, int Offset>
void Holder554<T, Offset>::assign(const T& value) {
    this->value = value;
}

template void Holder554<Value554a, 0x18>::assign(const Value554a&);   // 0x7100554bb0
template void Holder554<Value554b, 0x10>::assign(const Value554b&);   // 0x71005d285c

// 5fd004/5fd028: a callback given the object's part at +48 and its owner's entry.
struct Owner5fd0 {
    unsigned char pad0[0x88];
    void* entry;                 // +88
};

template <int Copy>
struct Visitor5fd0 {
    void visit(void (*callback)(void* part, void* entry, void* context), void* context);

    unsigned char pad0[0x48];
    unsigned char part[0x8];     // +48
    Owner5fd0* owner;            // +50
};

template <int Copy>
void Visitor5fd0<Copy>::visit(void (*callback)(void* part, void* entry, void* context), void* context) {
    callback(part, owner->entry, context);
}

template void Visitor5fd0<0>::visit(void (*)(void*, void*, void*), void*);   // 0x71005fd004
template void Visitor5fd0<1>::visit(void (*)(void*, void*, void*), void*);   // 0x71005fd028

// 53217c/53413c: the size of a block of N entries (at least one) after its header.
template <int Header>
unsigned long block_size(unsigned int count) {
    return Header + (count ? count : 1) * 8ul;
}

template unsigned long block_size<0x30>(unsigned int);   // 0x710053217c
template unsigned long block_size<0x34>(unsigned int);   // 0x710053413c

// 571464/5715b4: a call with a local for its result.
long resolve_571484(void* a, void* b, void* c, void* d, void* e, long* result);   // 0x7100571484
long resolve_5715d4(void* a, void* b, void* c, void* d, void* e, long* result);   // 0x71005715d4

template <int Copy>
long resolve_ignoring(void* a, void* b, void* c, void* d, void* e) {
    long result;
    if (Copy == 0)
        return resolve_571484(a, b, c, d, e, &result);
    return resolve_5715d4(a, b, c, d, e, &result);
}

template long resolve_ignoring<0>(void*, void*, void*, void*, void*);   // 0x7100571464
template long resolve_ignoring<1>(void*, void*, void*, void*, void*);   // 0x71005715b4

// 53ebe8/53f1e4: a call with a local for its result.
struct Result53eb { long a, b; };
long query_53ec08(void* a, void* b, Result53eb* result);                      // 0x710053ec08
long query_53f204(void* a, void* b, Result53eb* result);                      // 0x710053f204

template <int Copy>
long query_ignoring(void* a, void* b) {
    Result53eb result;
    if (Copy == 0)
        return query_53ec08(a, b, &result);
    return query_53f204(a, b, &result);
}

template long query_ignoring<0>(void*, void*);   // 0x710053ebe8
template long query_ignoring<1>(void*, void*);   // 0x710053f1e4

namespace nn {
namespace util {
class RelocationTable {
public:
    void Relocate();
};
class BinaryFileHeader {
public:
    bool IsRelocated() const;
    RelocationTable* GetRelocationTable();
};
}  // namespace util
}  // namespace nn

// 5f8d04/5f8d38: a resource file relocated in place (once) and returned.
template <int Copy>
nn::util::BinaryFileHeader* relocated(nn::util::BinaryFileHeader* header) {
    if (!header->IsRelocated())
        header->GetRelocationTable()->Relocate();
    return header;
}

template nn::util::BinaryFileHeader* relocated<0>(nn::util::BinaryFileHeader*);   // 0x71005f8d04
template nn::util::BinaryFileHeader* relocated<1>(nn::util::BinaryFileHeader*);   // 0x71005f8d38

// 50de34/50efb8: a lookup that reports whether nothing was found.
struct Key50de {
    void* a;
    void* b;
};
struct Out50de {
    long a, b;
};
unsigned char find_50deac(Key50de* key, Out50de* first, Out50de* second, void* extra);   // 0x710050deac
unsigned char find_50f030(Key50de* key, Out50de* first, Out50de* second, void* extra);   // 0x710050f030

template <int Copy>
bool missing(void* a, void* b) {
    Out50de first;
    Out50de second;
    Key50de key = {a, b};
    if (Copy == 0)
        return !find_50deac(&key, &first, &second, nullptr);
    return !find_50f030(&key, &first, &second, nullptr);
}

template bool missing<0>(void*, void*);   // 0x710050de34
template bool missing<1>(void*, void*);   // 0x710050efb8

// 4c2bec/4c3874, 4c2b44/4c382c, 4d5fa4/4d6058: expression ops reading a field of the record at BASE.
// An op's result: two words.
struct Result4c2b {
    void* a;
    void* b;
};
typedef Result4c2b (*Op4c2b)(int** cursor, void* value);
typedef Result4c2b (*Entry4d5f)(int** cursor, void* context, unsigned char* field);
// Reached through the GOT slots at 0x7100c2cd68 and 0x7100c2cd20.
extern Op4c2b gExprOpsA[];
extern Op4c2b gExprOpsB[];

template <int Table>
Op4c2b* expr_ops() {
    return Table == 0 ? gExprOpsA : gExprOpsB;
}

// An expression: its code, first op and the record field it starts from.
struct Expr4d5f {
    unsigned char pad0[0x8];
    int field_offset;            // +08
    unsigned char padc[0x10];
    int op;                      // +1c
    int code[1];                 // +20
};

template <int Table>
Result4c2b expr_evaluate(Expr4d5f* expr, unsigned char* base, void* context) {
    unsigned char* field = base + expr->field_offset;
    int* cursor = expr->code;
    return reinterpret_cast<Entry4d5f*>(expr_ops<Table>())[expr->op](&cursor, context, field);
}

template Result4c2b expr_evaluate<0>(Expr4d5f*, unsigned char*, void*);   // 0x71004d5fa4
template Result4c2b expr_evaluate<1>(Expr4d5f*, unsigned char*, void*);   // 0x71004d6058

// 5c8dc4/5c8e0c: COUNT elements read in full, compared against EXPECTED bytes.
class Reader5c8d {
public:
    virtual void v00(); virtual void v08(); virtual void v10(); virtual void v18();
    virtual unsigned long read(void* buffer, void* offset, unsigned long size);   // +20
};

template <int Size>
bool read_exactly(Reader5c8d* reader, void* buffer, unsigned long expected, unsigned int count) {
    unsigned long size = static_cast<unsigned long>(count) * Size;
    unsigned long got = reader->read(buffer, nullptr, size) == size ? size : 0;
    return got == expected;
}

template bool read_exactly<0x30>(Reader5c8d*, void*, unsigned long, unsigned int);   // 0x71005c8dc4
template bool read_exactly<0x18>(Reader5c8d*, void*, unsigned long, unsigned int);   // 0x71005c8e0c

// 5fdbd0/5fee50: a value scaled from a source's count, plus an offset.
class Source5fdb {
public:
    virtual void v00(); virtual void v08(); virtual void v10(); virtual void v18(); virtual void v20();
    virtual void v28(); virtual void v30(); virtual void v38(); virtual void v40(); virtual void v48();
    virtual void v50();
    virtual int count();         // +58
};

template <int Copy>
struct Scaled5fdb {
    float value();

    unsigned char pad0[0x10];
    float scale;                 // +10
    unsigned char pad14[0x14];
    Source5fdb* source;          // +28
    unsigned char pad30[0x14];
    float offset;                // +44
};

template <int Copy>
float Scaled5fdb<Copy>::value() {
    float n = source ? static_cast<float>(source->count()) : 0.0f;
    return n * scale + offset;
}

template float Scaled5fdb<0>::value();   // 0x71005fdbd0
template float Scaled5fdb<1>::value();   // 0x71005fee50

// 5d29fc/5de8b4: an entry of a circular list found by its name (up to 128 characters).
struct Named5d29 {
    Named5d29* prev;             // +00
    Named5d29* next;             // +08
    char name[0x80];             // +10
    void* value;                 // +90
};

template <int Copy>
struct NamedList5d29 : Named5d29 {
    void* find(const char* key);
};

inline bool same_name(const char* a, const char* b) {
    for (long i = 0; i < 0x80; ++i) {
        if (a[i] != b[i])
            return false;
        if (!a[i])
            return true;
    }
    return true;
}

template <int Copy>
void* NamedList5d29<Copy>::find(const char* key) {
    for (Named5d29* node = next; node != this; node = node->next) {
        if (same_name(key, node->name))
            return node->value;
    }
    return nullptr;
}

template void* NamedList5d29<0>::find(const char*);   // 0x71005d29fc
template void* NamedList5d29<1>::find(const char*);   // 0x71005de8b4

// 595cf4/595d44: every link of a chain accepts ARG.
template <int Slot>
class Link595c {
public:
    virtual void v00(); virtual void v08(); virtual void v10(); virtual void v18();
    virtual unsigned char accept_a(void* arg);   // +20
    virtual unsigned char accept_b(void* arg);   // +28

    bool all_accept(void* arg);

    Link595c* next;              // +08
};

template <int Slot>
bool Link595c<Slot>::all_accept(void* arg) {
    Link595c* link = this;
    do {
        if (!(Slot == 0 ? link->accept_a(arg) : link->accept_b(arg)))
            return false;
        link = link->next;
    } while (link);
    return true;
}

template bool Link595c<0>::all_accept(void*);   // 0x7100595cf4
template bool Link595c<1>::all_accept(void*);   // 0x7100595d44

// 5d0804/5d087c: a lazily created instance (a function-local static per copy).
struct Instance5d08;
Instance5d08* create_instance_5d08f8();                                     // 0x71005d08f8

template <int Copy>
Instance5d08** instance_slot() {
    static Instance5d08* instance = create_instance_5d08f8();
    return &instance;
}

template Instance5d08** instance_slot<0>();   // 0x71005d0804
template Instance5d08** instance_slot<1>();   // 0x71005d087c

// 5d2b18/5d2b74: every active entry of a circular list visited.
template <int Copy>
struct VisitorRef5d2b {
    void visit(void (*callback)(void* part, void* entry, void* context), void* context);   // 0x71005fd004 + copy
};
template <int Copy>
struct Entry5d2b {
    Entry5d2b* prev;             // +00
    Entry5d2b* next;             // +08
    unsigned char pad10[0x80];
    VisitorRef5d2b<Copy>* visitor;   // +90
    bool active;                 // +98
};

template <int Copy>
struct EntryList5d2b : Entry5d2b<Copy> {
    void visit_all(void (*callback)(void*, void*, void*), void* context);
};

template <int Copy>
void EntryList5d2b<Copy>::visit_all(void (*callback)(void*, void*, void*), void* context) {
    for (Entry5d2b<Copy>* entry = this->next; entry != this; entry = entry->next) {
        if (entry->active)
            entry->visitor->visit(callback, context);
    }
}

template void EntryList5d2b<0>::visit_all(void (*)(void*, void*, void*), void*);   // 0x71005d2b18
template void EntryList5d2b<1>::visit_all(void (*)(void*, void*, void*), void*);   // 0x71005d2b74

// 5ef678/5ef6dc: a value up to 30000 set on the inactive slot, with its state bits switched.
struct Slot5ef6 {
    unsigned short flags;        // +00
    unsigned char pad2[0x3a];
    unsigned int value;          // +3c
    unsigned char pad40[0x90];
};

template <unsigned short Clear, unsigned short Set>
struct Buffered5ef6 {
    bool set(unsigned int value);

    unsigned char pad0[0xdd0];
    unsigned int current;        // +dd0
    unsigned int paddd4;
    Slot5ef6 slots[2];           // +dd8
};

template <unsigned short Clear, unsigned short Set>
bool Buffered5ef6<Clear, Set>::set(unsigned int value) {
    if (value > 30000)
        return false;
    unsigned int index = __atomic_load_n(&current, __ATOMIC_ACQUIRE) ^ 1;
    __atomic_fetch_and(&slots[index].flags, static_cast<unsigned short>(~Clear), __ATOMIC_SEQ_CST);
    __atomic_fetch_or(&slots[index].flags, Set, __ATOMIC_SEQ_CST);
    slots[index].value = value;
    return true;
}

template bool Buffered5ef6<8, 4>::set(unsigned int);   // 0x71005ef678
template bool Buffered5ef6<4, 8>::set(unsigned int);   // 0x71005ef6dc
