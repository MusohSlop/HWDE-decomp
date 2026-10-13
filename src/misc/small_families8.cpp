// More code families found by tools/family_scan.py, grouped until their source files are
// linked: four-byte stream reads, light-holder teardowns and reference resets. Within a family
// the bodies are identical apart from the globals and callees they use; classes and functions
// are named after their address. Status: matching/README.md.

class DefaultHeap {
public:
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c
void release_light(void** slot);                                            // 0x71001f7960

struct RefCounted {
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void destroy();   // +18

    int refs;                 // +08
};

static inline void drop(RefCounted** slot) {
    if (RefCounted* object = *slot) {
        if (!--object->refs)
            object->destroy();
        *slot = nullptr;
    }
}

// Four-byte reads from a byte stream, one byte at a time.

// 0x71001fbcdc
struct ByteStream_1fbcdc {
    void read4(unsigned char* out);

    unsigned char pad[0x10];
    unsigned char* cursor;    // +10
};

void ByteStream_1fbcdc::read4(unsigned char* out) {
    out[0] = *cursor++;
    out[1] = *cursor++;
    out[2] = *cursor++;
    out[3] = *cursor++;
}

// 0x71001fbd30
struct ByteStream_1fbd30 {
    void read4(unsigned char* out);

    unsigned char pad[0x10];
    unsigned char* cursor;    // +10
};

void ByteStream_1fbd30::read4(unsigned char* out) {
    out[0] = *cursor++;
    out[1] = *cursor++;
    out[2] = *cursor++;
    out[3] = *cursor++;
}

// 0x71001fbd84
struct ByteStream_1fbd84 {
    void read4(unsigned char* out);

    unsigned char pad[0x10];
    unsigned char* cursor;    // +10
};

void ByteStream_1fbd84::read4(unsigned char* out) {
    out[0] = *cursor++;
    out[1] = *cursor++;
    out[2] = *cursor++;
    out[3] = *cursor++;
}


// Light-holder teardowns: release the held light, then the holder.

// 0x7100379a00
struct LightHolder_379a00 {
    void* light;              // +00
};
// Reached through the GOT slot at 0x7100c2af58.
extern LightHolder_379a00* gGlobal_c2af58;

void destroy_light_holder_379a00() {
    if (LightHolder_379a00* holder = gGlobal_c2af58) {
        if (holder->light) {
            release_light(&holder->light);
            holder->light = nullptr;
        }
        get_default_heap()->release(holder, 1, 0);
        gGlobal_c2af58 = nullptr;
    }
}

// 0x710037abdc
struct LightHolder_37abdc {
    void* light;              // +00
};
// Reached through the GOT slot at 0x7100c2a9c8.
extern LightHolder_37abdc* gGlobal_c2a9c8;

void destroy_light_holder_37abdc() {
    if (LightHolder_37abdc* holder = gGlobal_c2a9c8) {
        if (holder->light) {
            release_light(&holder->light);
            holder->light = nullptr;
        }
        get_default_heap()->release(holder, 1, 0);
        gGlobal_c2a9c8 = nullptr;
    }
}

// 0x710037ad18
struct LightHolder_37ad18 {
    void* light;              // +00
};
// Reached through the GOT slot at 0x7100c2ada0.
extern LightHolder_37ad18* gGlobal_c2ada0;

void destroy_light_holder_37ad18() {
    if (LightHolder_37ad18* holder = gGlobal_c2ada0) {
        if (holder->light) {
            release_light(&holder->light);
            holder->light = nullptr;
        }
        get_default_heap()->release(holder, 1, 0);
        gGlobal_c2ada0 = nullptr;
    }
}


// Reference resets: drop the held reference, reset the id to -1 and clear the next field.

// 0x710043b300
struct RefSlot_43b300 {
    void reset();

    RefCounted* object;       // +00
    int id;                   // +08
    int extra;                // +0c
};

void RefSlot_43b300::reset() {
    drop(&object);
    id = -1;
    extra = 0;
}

// 0x710043b34c
struct RefSlot_43b34c {
    void reset();

    RefCounted* object;       // +00
    int id;                   // +08
    int extra;                // +0c
};

void RefSlot_43b34c::reset() {
    drop(&object);
    id = -1;
    extra = 0;
}

// 0x710043b398
struct RefSlot_43b398 {
    void reset();

    RefCounted* object;       // +00
    int id;                   // +08
    int extra;                // +0c
};

void RefSlot_43b398::reset() {
    drop(&object);
    id = -1;
    extra = 0;
}


// Reference resets that clear a count.

// 0x710040d638
struct CountedRef_40d638 {
    void reset();

    RefCounted* object;       // +00
    int count;                // +08
};

void CountedRef_40d638::reset() {
    drop(&object);
    count = 0;
}

// 0x710040d680
struct CountedRef_40d680 {
    void reset();

    RefCounted* object;       // +00
    int count;                // +08
};

void CountedRef_40d680::reset() {
    drop(&object);
    count = 0;
}

// 0x710040d6c8
struct CountedRef_40d6c8 {
    void reset();

    RefCounted* object;       // +00
    int count;                // +08
};

void CountedRef_40d6c8::reset() {
    drop(&object);
    count = 0;
}
