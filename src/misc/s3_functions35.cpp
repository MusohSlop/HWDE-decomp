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
