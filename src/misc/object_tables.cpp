// Object tables (0x7100247364 to 0x710024c928): a global table with a head block, its own frame
// allocator and a slot area whose second part is cleared on reset. Three tables differ only in the
// head block size and the two slot area sizes. Names are descriptive placeholders. Status:
// matching/README.md.

extern "C" void* memset(void* dest, int value, unsigned long size);

class DefaultHeap {
public:
    void* allocate(unsigned long alignment, unsigned long size, unsigned char a, unsigned char b); // 0x710045c458
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

void* allocate_block_255dec(unsigned int size);                             // 0x7100255dec
void free_block_255e40(void* block);                                        // 0x7100255e40

struct LightAllocator {
    LightAllocator();                                                       // 0x71005c2d24
    void setup(void* memory, unsigned int size, int a, int b, int alignment); // 0x71005c2d40
    void clear();                                                           // 0x71005c2e54

    unsigned char data[0x60];
};

template <unsigned int HeadSize, unsigned long Kept, unsigned long Cleared>
struct ObjectTable {
    ObjectTable() : head(nullptr) { memset(slots, 0, sizeof(slots)); }
    static void* operator new(unsigned long size) { return get_default_heap()->allocate(0x10, size, 1, 0); }

    void init() {
        head = allocate_block_255dec(HeadSize);
        allocator.setup(head, HeadSize, 4, 4, 0x10);
    }

    void reset() {
        memset(slots + Kept, 0, Cleared);
        allocator.clear();
        if (head) {
            free_block_255e40(head);
            head = nullptr;
        }
    }

    void* head;               // +00
    LightAllocator allocator; // +08
    unsigned char slots[Kept + Cleared]; // +68
};

typedef ObjectTable<0x4000, 0x328, 0x328> ObjectTableA;
typedef ObjectTable<0x8000, 0x800, 0x1818> ObjectTableB;
typedef ObjectTable<0x4000, 0x960, 0x968> ObjectTableC;

// The second table takes its allocator reference before clearing the slots.
template <>
void ObjectTable<0x8000, 0x800, 0x1818>::reset() {
    LightAllocator& slots_allocator = allocator;
    memset(slots + 0x800, 0, 0x1818);
    slots_allocator.clear();
    if (head) {
        free_block_255e40(head);
        head = nullptr;
    }
}

template struct ObjectTable<0x4000, 0x328, 0x328>;   // init 0x710024741c, reset 0x7100247460
template struct ObjectTable<0x8000, 0x800, 0x1818>;  // init 0x7100248754, reset 0x7100248798
template struct ObjectTable<0x4000, 0x960, 0x968>;   // init 0x710024c8e4, reset 0x710024c928
// Reached through the GOT slot at 0x7100c2a518.
extern ObjectTableA* gObjects_c2a518;

// 0x7100247364
void create_objects_247364() {
    if (!gObjects_c2a518)
        gObjects_c2a518 = new ObjectTableA;
}
// Reached through the GOT slot at 0x7100c2a520.
extern ObjectTableB* gObjects_c2a520;

// 0x710024869c
void create_objects_24869c() {
    if (!gObjects_c2a520)
        gObjects_c2a520 = new ObjectTableB;
}
// Reached through the GOT slot at 0x7100c2a530.
extern ObjectTableC* gObjects_c2a530;

// 0x710024c82c
void create_objects_24c82c() {
    if (!gObjects_c2a530)
        gObjects_c2a530 = new ObjectTableC;
}
