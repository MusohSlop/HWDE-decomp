// Resource frame view (40 bytes). Semantics: docs/resource-frame.md.
#pragma once

struct AllocDescriptor;

// Allocator interface used by resource frames; the same vtable layout as
// DemoOwner (event/demo_sequence.h).
class ResourceAllocator {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void* alloc_aligned(unsigned int size, unsigned int alignment,
                                const AllocDescriptor& desc);   // +0x40
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void free(void* ptr);                               // +0x60
};

class ResourceFrame {
public:
    ResourceFrame();                                                  // 0x710025b394
    ~ResourceFrame();                                                 // 0x710025b3ac
    void close();                                                     // 0x710025b40c
    bool is_open() const;                                             // 0x710025b46c
    void bind(int mode, void* storage);                               // 0x710025b47c
    bool open(int mode, unsigned int identity, ResourceAllocator* allocator);       // 0x710025b4b4
    bool open_table(int mode, unsigned int identity, ResourceAllocator* allocator); // 0x710025b5b8
    unsigned int count() const;                                       // 0x710025b6f8
    unsigned int entry_offset(unsigned int index) const;              // 0x710025b704
    unsigned int entry_size(unsigned int index) const;                // 0x710025b71c
    const void* lookup(unsigned int index) const;                     // 0x710025b738
    void* load(unsigned int index, void* dest, unsigned int size);    // 0x710025b754

private:
    void set_layout(int mode);

    void* mStorage;               // +00
    unsigned int mHeaderWords;    // +08
    unsigned int mStride;         // +0c
    unsigned int mIdentity;       // +10
    ResourceAllocator* mAllocator; // +18
    bool mOwnsStorage;            // +20
    bool mTable;                  // +21
};
static_assert(sizeof(ResourceFrame) == 0x28, "frame size");
