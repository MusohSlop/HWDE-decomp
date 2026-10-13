// Destructor bodies reached through a secondary base whose members include a polymorphic group
// (found by scanning for the misc/base_teardowns.cpp pattern with a vtable store in the middle):
// each tears down the leading parts, then the group (its destructor stores the group's vtable
// pointer and destroys its four members), then the remaining parts and the primary base. The
// deleting forms then return the object to the default heap. Functions are named after their
// address. Status: matching/README.md.

class DefaultHeap {
public:
    void release(void* ptr, unsigned char a, unsigned char b);              // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

struct GroupSlot {
    ~GroupSlot();                                                           // 0x7100031374

    unsigned char data[0x10];
};
struct GroupTail {
    ~GroupTail();                                                           // 0x710004640c

    unsigned char data[8];
};
// Vtable through the GOT slot at 0x7100c21d60.
class TeardownGroup {
public:
    virtual ~TeardownGroup() {}
    virtual void key_function();

    GroupSlot first;          // +08
    GroupSlot second;         // +18
    GroupSlot third;          // +28
    GroupTail tail;           // +38
};

void destroy_part_cdf04(void* part);                                        // 0x71000cdf04
void destroy_part_cf58c(void* part);                                        // 0x71000cf58c
void destroy_part_cfe84(void* part);                                        // 0x71000cfe84
void destroy_part_d2534(void* part);                                        // 0x71000d2534
void destroy_part_d3410(void* part);                                        // 0x71000d3410
void destroy_part_d3428(void* part);                                        // 0x71000d3428

// 0x710002748c: secondary base at +e0
void destroy_with_group_2748c(unsigned char* base) {
    unsigned char* object = base - 0xe0;
    destroy_part_d3428(base + 0xa8);
    destroy_part_d2534(base + 0x90);
    reinterpret_cast<TeardownGroup*>(base + 0x30)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base + 0x20);
    destroy_part_cf58c(base + 0x8);
    destroy_part_cdf04(object);
}

// 0x7100027500: secondary base at +e0
void delete_with_group_27500(unsigned char* base) {
    unsigned char* object = base - 0xe0;
    destroy_part_d3428(base + 0xa8);
    destroy_part_d2534(base + 0x90);
    reinterpret_cast<TeardownGroup*>(base + 0x30)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base + 0x20);
    destroy_part_cf58c(base + 0x8);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x7100027588: secondary base at +e8
void destroy_with_group_27588(unsigned char* base) {
    unsigned char* object = base - 0xe8;
    destroy_part_d3428(base + 0xa0);
    destroy_part_d2534(base + 0x88);
    reinterpret_cast<TeardownGroup*>(base + 0x28)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base + 0x18);
    destroy_part_cf58c(base);
    destroy_part_cdf04(object);
}

// 0x71000275fc: secondary base at +e8
void delete_with_group_275fc(unsigned char* base) {
    unsigned char* object = base - 0xe8;
    destroy_part_d3428(base + 0xa0);
    destroy_part_d2534(base + 0x88);
    reinterpret_cast<TeardownGroup*>(base + 0x28)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base + 0x18);
    destroy_part_cf58c(base);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000276fc: secondary base at +f8
void destroy_with_group_276fc(unsigned char* base) {
    unsigned char* object = base - 0xf8;
    destroy_part_d3428(base + 0x90);
    destroy_part_d2534(base + 0x78);
    reinterpret_cast<TeardownGroup*>(base + 0x18)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base + 0x8);
    destroy_part_cf58c(base - 0x10);
    destroy_part_cdf04(object);
}

// 0x7100027770: secondary base at +f8
void delete_with_group_27770(unsigned char* base) {
    unsigned char* object = base - 0xf8;
    destroy_part_d3428(base + 0x90);
    destroy_part_d2534(base + 0x78);
    reinterpret_cast<TeardownGroup*>(base + 0x18)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base + 0x8);
    destroy_part_cf58c(base - 0x10);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000278c0: secondary base at +100
void destroy_with_group_278c0(unsigned char* base) {
    unsigned char* object = base - 0x100;
    destroy_part_d3428(base + 0x88);
    destroy_part_d2534(base + 0x70);
    reinterpret_cast<TeardownGroup*>(base + 0x10)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base);
    destroy_part_cf58c(base - 0x18);
    destroy_part_cdf04(object);
}

// 0x7100027934: secondary base at +100
void delete_with_group_27934(unsigned char* base) {
    unsigned char* object = base - 0x100;
    destroy_part_d3428(base + 0x88);
    destroy_part_d2534(base + 0x70);
    reinterpret_cast<TeardownGroup*>(base + 0x10)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base);
    destroy_part_cf58c(base - 0x18);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x7100027c90: secondary base at +150
void destroy_with_group_27c90(unsigned char* base) {
    unsigned char* object = base - 0x150;
    destroy_part_d3428(base + 0x38);
    destroy_part_d2534(base + 0x20);
    reinterpret_cast<TeardownGroup*>(base - 0x40)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base - 0x50);
    destroy_part_cf58c(base - 0x68);
    destroy_part_cdf04(object);
}

// 0x7100027d04: secondary base at +150
void delete_with_group_27d04(unsigned char* base) {
    unsigned char* object = base - 0x150;
    destroy_part_d3428(base + 0x38);
    destroy_part_d2534(base + 0x20);
    reinterpret_cast<TeardownGroup*>(base - 0x40)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base - 0x50);
    destroy_part_cf58c(base - 0x68);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x7100027df0: secondary base at +160
void destroy_with_group_27df0(unsigned char* base) {
    unsigned char* object = base - 0x160;
    destroy_part_d3428(base + 0x28);
    destroy_part_d2534(base + 0x10);
    reinterpret_cast<TeardownGroup*>(base - 0x50)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base - 0x60);
    destroy_part_cf58c(base - 0x78);
    destroy_part_cdf04(object);
}

// 0x7100027e64: secondary base at +160
void delete_with_group_27e64(unsigned char* base) {
    unsigned char* object = base - 0x160;
    destroy_part_d3428(base + 0x28);
    destroy_part_d2534(base + 0x10);
    reinterpret_cast<TeardownGroup*>(base - 0x50)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base - 0x60);
    destroy_part_cf58c(base - 0x78);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x7100027fa4: secondary base at +170
void destroy_with_group_27fa4(unsigned char* base) {
    unsigned char* object = base - 0x170;
    destroy_part_d3428(base + 0x18);
    destroy_part_d2534(base);
    reinterpret_cast<TeardownGroup*>(base - 0x60)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base - 0x70);
    destroy_part_cf58c(base - 0x88);
    destroy_part_cdf04(object);
}

// 0x7100028018: secondary base at +170
void delete_with_group_28018(unsigned char* base) {
    unsigned char* object = base - 0x170;
    destroy_part_d3428(base + 0x18);
    destroy_part_d2534(base);
    reinterpret_cast<TeardownGroup*>(base - 0x60)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base - 0x70);
    destroy_part_cf58c(base - 0x88);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000280c8: secondary base at +180
void destroy_with_group_280c8(unsigned char* base) {
    unsigned char* object = base - 0x180;
    destroy_part_d3428(base + 0x8);
    destroy_part_d2534(base - 0x10);
    reinterpret_cast<TeardownGroup*>(base - 0x70)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base - 0x80);
    destroy_part_cf58c(base - 0x98);
    destroy_part_cdf04(object);
}

// 0x710002813c: secondary base at +180
void delete_with_group_2813c(unsigned char* base) {
    unsigned char* object = base - 0x180;
    destroy_part_d3428(base + 0x8);
    destroy_part_d2534(base - 0x10);
    reinterpret_cast<TeardownGroup*>(base - 0x70)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base - 0x80);
    destroy_part_cf58c(base - 0x98);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000cbb48: secondary base at +e0
void destroy_with_group_cbb48(unsigned char* base) {
    unsigned char* object = base - 0xe0;
    destroy_part_d3410(base + 0xa0);
    destroy_part_d2534(base + 0x90);
    reinterpret_cast<TeardownGroup*>(base + 0x30)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base + 0x20);
    destroy_part_cf58c(base + 0x8);
    destroy_part_cdf04(object);
}

// 0x71000cbbbc: secondary base at +e8
void destroy_with_group_cbbbc(unsigned char* base) {
    unsigned char* object = base - 0xe8;
    destroy_part_d3410(base + 0x98);
    destroy_part_d2534(base + 0x88);
    reinterpret_cast<TeardownGroup*>(base + 0x28)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base + 0x18);
    destroy_part_cf58c(base);
    destroy_part_cdf04(object);
}

// 0x71000cbc30: secondary base at +f8
void destroy_with_group_cbc30(unsigned char* base) {
    unsigned char* object = base - 0xf8;
    destroy_part_d3410(base + 0x88);
    destroy_part_d2534(base + 0x78);
    reinterpret_cast<TeardownGroup*>(base + 0x18)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base + 0x8);
    destroy_part_cf58c(base - 0x10);
    destroy_part_cdf04(object);
}

// 0x71000cbca4: secondary base at +100
void destroy_with_group_cbca4(unsigned char* base) {
    unsigned char* object = base - 0x100;
    destroy_part_d3410(base + 0x80);
    destroy_part_d2534(base + 0x70);
    reinterpret_cast<TeardownGroup*>(base + 0x10)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base);
    destroy_part_cf58c(base - 0x18);
    destroy_part_cdf04(object);
}

// 0x71000cbd98: secondary base at +150
void destroy_with_group_cbd98(unsigned char* base) {
    unsigned char* object = base - 0x150;
    destroy_part_d3410(base + 0x30);
    destroy_part_d2534(base + 0x20);
    reinterpret_cast<TeardownGroup*>(base - 0x40)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base - 0x50);
    destroy_part_cf58c(base - 0x68);
    destroy_part_cdf04(object);
}

// 0x71000cbe0c: secondary base at +160
void destroy_with_group_cbe0c(unsigned char* base) {
    unsigned char* object = base - 0x160;
    destroy_part_d3410(base + 0x20);
    destroy_part_d2534(base + 0x10);
    reinterpret_cast<TeardownGroup*>(base - 0x50)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base - 0x60);
    destroy_part_cf58c(base - 0x78);
    destroy_part_cdf04(object);
}

// 0x71000cbe80: secondary base at +170
void destroy_with_group_cbe80(unsigned char* base) {
    unsigned char* object = base - 0x170;
    destroy_part_d3410(base + 0x10);
    destroy_part_d2534(base);
    reinterpret_cast<TeardownGroup*>(base - 0x60)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base - 0x70);
    destroy_part_cf58c(base - 0x88);
    destroy_part_cdf04(object);
}

// 0x71000cbef4: secondary base at +178
void destroy_with_group_cbef4(unsigned char* base) {
    unsigned char* object = base - 0x178;
    destroy_part_d3410(base + 0x8);
    destroy_part_d2534(base - 0x8);
    reinterpret_cast<TeardownGroup*>(base - 0x68)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base - 0x78);
    destroy_part_cf58c(base - 0x90);
    destroy_part_cdf04(object);
}

// 0x71000cbf68: secondary base at +180
void destroy_with_group_cbf68(unsigned char* base) {
    unsigned char* object = base - 0x180;
    destroy_part_d3410(base);
    destroy_part_d2534(base - 0x10);
    reinterpret_cast<TeardownGroup*>(base - 0x70)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base - 0x80);
    destroy_part_cf58c(base - 0x98);
    destroy_part_cdf04(object);
}

// 0x71000cc05c: secondary base at +e0
void delete_with_group_cc05c(unsigned char* base) {
    unsigned char* object = base - 0xe0;
    destroy_part_d3410(base + 0xa0);
    destroy_part_d2534(base + 0x90);
    reinterpret_cast<TeardownGroup*>(base + 0x30)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base + 0x20);
    destroy_part_cf58c(base + 0x8);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000cc0e4: secondary base at +e8
void delete_with_group_cc0e4(unsigned char* base) {
    unsigned char* object = base - 0xe8;
    destroy_part_d3410(base + 0x98);
    destroy_part_d2534(base + 0x88);
    reinterpret_cast<TeardownGroup*>(base + 0x28)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base + 0x18);
    destroy_part_cf58c(base);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000cc16c: secondary base at +f8
void delete_with_group_cc16c(unsigned char* base) {
    unsigned char* object = base - 0xf8;
    destroy_part_d3410(base + 0x88);
    destroy_part_d2534(base + 0x78);
    reinterpret_cast<TeardownGroup*>(base + 0x18)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base + 0x8);
    destroy_part_cf58c(base - 0x10);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000cc1f4: secondary base at +100
void delete_with_group_cc1f4(unsigned char* base) {
    unsigned char* object = base - 0x100;
    destroy_part_d3410(base + 0x80);
    destroy_part_d2534(base + 0x70);
    reinterpret_cast<TeardownGroup*>(base + 0x10)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base);
    destroy_part_cf58c(base - 0x18);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000cc310: secondary base at +150
void delete_with_group_cc310(unsigned char* base) {
    unsigned char* object = base - 0x150;
    destroy_part_d3410(base + 0x30);
    destroy_part_d2534(base + 0x20);
    reinterpret_cast<TeardownGroup*>(base - 0x40)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base - 0x50);
    destroy_part_cf58c(base - 0x68);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000cc398: secondary base at +160
void delete_with_group_cc398(unsigned char* base) {
    unsigned char* object = base - 0x160;
    destroy_part_d3410(base + 0x20);
    destroy_part_d2534(base + 0x10);
    reinterpret_cast<TeardownGroup*>(base - 0x50)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base - 0x60);
    destroy_part_cf58c(base - 0x78);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000cc420: secondary base at +170
void delete_with_group_cc420(unsigned char* base) {
    unsigned char* object = base - 0x170;
    destroy_part_d3410(base + 0x10);
    destroy_part_d2534(base);
    reinterpret_cast<TeardownGroup*>(base - 0x60)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base - 0x70);
    destroy_part_cf58c(base - 0x88);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000cc4a8: secondary base at +178
void delete_with_group_cc4a8(unsigned char* base) {
    unsigned char* object = base - 0x178;
    destroy_part_d3410(base + 0x8);
    destroy_part_d2534(base - 0x8);
    reinterpret_cast<TeardownGroup*>(base - 0x68)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base - 0x78);
    destroy_part_cf58c(base - 0x90);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000cc530: secondary base at +180
void delete_with_group_cc530(unsigned char* base) {
    unsigned char* object = base - 0x180;
    destroy_part_d3410(base);
    destroy_part_d2534(base - 0x10);
    reinterpret_cast<TeardownGroup*>(base - 0x70)->TeardownGroup::~TeardownGroup();
    destroy_part_cfe84(base - 0x80);
    destroy_part_cf58c(base - 0x98);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}
