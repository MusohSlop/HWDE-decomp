// Matching candidates for the title banner (0x71001e1b48-0x71001e22d8).
// Names are descriptive placeholders. Status: matching/README.md.

struct AllocParams {
    explicit AllocParams(short alignment) : alignment(alignment), flags(0), tag(0) {}

    short alignment;          // +0
    short flags;              // +2
    long tag;                 // +8
};

// The default heap's front frame heap (at +b0).
class FrameAllocator {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void* allocate(long size, const AllocParams& params);           // +30
    virtual void v38();
    virtual void v40();
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void free(void* ptr);                                           // +60
};

class DefaultHeap {
public:
    FrameAllocator* frame_allocator() { return &front; }

    unsigned char pad[0xb0];
    FrameAllocator front;     // +b0
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

class FrameHeapImpl {
public:
    void initialize(void* buffer, unsigned long size, int a, int b, int alignment); // 0x71005c2d40
    void finalize();                                                               // 0x71005c2e54
    unsigned char pad[0x60];
};

class TitleBanner {
public:
    void hide();                                                            // 0x71001e1c9c
    void set_layer(int layer);                                              // 0x71001e1e2c
    void release_layer();                                                   // 0x71001e1ec4

    unsigned char pad[0xd0];
    long layer_size;          // +d0
    FrameHeapImpl frames;     // +d8
    void* buffer;             // +138
    unsigned char pad140[0x678];
    int layer;                // +7b8
};

void TitleBanner::hide() {
    if (buffer) {
        release_layer();
        frames.finalize();
        get_default_heap()->frame_allocator()->free(buffer);
        buffer = nullptr;
        layer = -1;
    }
}

void TitleBanner::set_layer(int layer) {
    this->layer = layer;
    long size;
    switch (layer) {
    case -1:
        size = 0;
        break;
    case 0:
        size = 0x1e00000;
        break;
    case 1:
        size = 0x800000;
        break;
    case 2:
    case 3:
        size = 0x1980000;
        break;
    case 4:
        size = 0x1480000;
        break;
    case 5:
        size = 0x100000;
        break;
    case 7:
        size = 0x1400000;
        break;
    default:
        size = 0;
        break;
    }
    layer_size = size;
    void* memory = get_default_heap()->frame_allocator()->allocate(layer_size, AllocParams(0x2e));
    buffer = memory;
    frames.initialize(memory, layer_size, 4, 4, 0x10);
}
