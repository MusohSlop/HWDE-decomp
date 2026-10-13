// Small code families found by tools/family_scan.py, grouped until their source files are
// linked: guarded global forwarders, id-range filters, paired global resets and buffer
// releases. Within a family the bodies are identical apart from the global or callee they
// use; functions are named after their address, callees after theirs. Status: matching/README.md.

// Guarded global forwarders: pass the argument on only when the global object exists.

// Reached through the GOT slot at 0x7100c2a530.
extern void* gObjectTableB;

void guarded_call_24c9c0(void* object, int value);             // 0x710024c9c0

// Reached through the GOT slot at 0x7100c2b700.
extern void* gGlobal_c2b700;

void guarded_call_3f8228(void* object, int value);             // 0x71003f8228

void guarded_call_3f83c0(void* object, int value);             // 0x71003f83c0

// Reached through the GOT slot at 0x7100c2b710.
extern void* gGlobal_c2b710;

void guarded_call_3fce70(void* object, int value);             // 0x71003fce70

void guarded_call_3fd790(void* object, int value);             // 0x71003fd790

void guarded_call_3fd970(void* object, int value);             // 0x71003fd970

// Reached through the GOT slot at 0x7100c2b750.
extern void* gGlobal_c2b750;

void guarded_call_40abb0(void* object, int value);             // 0x710040abb0

// Reached through the GOT slot at 0x7100c2bbd0.
extern void* gSingleton_c2bbd0;

void guarded_call_460d48(void* object, int value);             // 0x7100460d48

// 0x7100255ee8
void guarded_forward_255ee8(int value) {
    if (gObjectTableB)
        guarded_call_24c9c0(gObjectTableB, value);
}

// 0x71003fa234
void guarded_forward_3fa234(int value) {
    if (gGlobal_c2b700)
        guarded_call_3f8228(gGlobal_c2b700, value);
}

// 0x71003fa2d4
void guarded_forward_3fa2d4(int value) {
    if (gGlobal_c2b700)
        guarded_call_3f83c0(gGlobal_c2b700, value);
}

// 0x71003fe6c0
void guarded_forward_3fe6c0(int value) {
    if (gGlobal_c2b710)
        guarded_call_3fce70(gGlobal_c2b710, value);
}

// 0x71003ff340
void guarded_forward_3ff340(int value) {
    if (gGlobal_c2b710)
        guarded_call_3fd790(gGlobal_c2b710, value);
}

// 0x71003ff378
void guarded_forward_3ff378(int value) {
    if (gGlobal_c2b710)
        guarded_call_3fd970(gGlobal_c2b710, value);
}

// 0x710040b0dc
void guarded_forward_40b0dc(int value) {
    if (gGlobal_c2b750)
        guarded_call_40abb0(gGlobal_c2b750, value);
}

// 0x7100460f3c
void guarded_forward_460f3c(int value) {
    if (gSingleton_c2bbd0)
        guarded_call_460d48(gSingleton_c2bbd0, value);
}


// Id filters: ids 0x447-0x44b are looked up, any other id gives -1.

int lookup_id_2115c0(int id);                                    // 0x71002115c0

int lookup_id_2115e4(int id);                                    // 0x71002115e4

int lookup_id_211608(int id);                                    // 0x7100211608

int lookup_id_21162c(int id);                                    // 0x710021162c

int lookup_id_211650(int id);                                    // 0x7100211650

int lookup_id_211674(int id);                                    // 0x7100211674

int lookup_id_211698(int id);                                    // 0x7100211698

// 0x710000e96c
int filter_id_e96c(int id) {
    if (id == 0x447 || (id & ~3) == 0x448)
        return lookup_id_2115c0(id);
    return -1;
}

// 0x710000e98c
int filter_id_e98c(int id) {
    if (id == 0x447 || (id & ~3) == 0x448)
        return lookup_id_2115e4(id);
    return -1;
}

// 0x710000e9ac
int filter_id_e9ac(int id) {
    if (id == 0x447 || (id & ~3) == 0x448)
        return lookup_id_211608(id);
    return -1;
}

// 0x710000e9cc
int filter_id_e9cc(int id) {
    if (id == 0x447 || (id & ~3) == 0x448)
        return lookup_id_21162c(id);
    return -1;
}

// 0x710000e9ec
int filter_id_e9ec(int id) {
    if (id == 0x447 || (id & ~3) == 0x448)
        return lookup_id_211650(id);
    return -1;
}

// 0x710000ea0c
int filter_id_ea0c(int id) {
    if (id == 0x447 || (id & ~3) == 0x448)
        return lookup_id_211674(id);
    return -1;
}

// 0x710000ea2c
int filter_id_ea2c(int id) {
    if (id == 0x447 || (id & ~3) == 0x448)
        return lookup_id_211698(id);
    return -1;
}


// Paired resets: reset both halves of a global pair when they exist.
struct GlobalHalves {
    void* first;
    void* second;
};

// Reached through the GOT slot at 0x7100c22af8.
extern GlobalHalves gGlobal_c22af8;

void reset_half_f4d30(void* half);                              // 0x71000f4d30

// Reached through the GOT slot at 0x7100c22aa0.
extern GlobalHalves gGlobal_c22aa0;

void reset_half_fd6b4(void* half);                              // 0x71000fd6b4

// Reached through the GOT slot at 0x7100c22270.
extern GlobalHalves gGlobal_c22270;

void reset_half_11b708(void* half);                              // 0x710011b708

// Reached through the GOT slot at 0x7100c22af0.
extern GlobalHalves gGlobal_c22af0;

void reset_half_120170(void* half);                              // 0x7100120170

// Reached through the GOT slot at 0x7100c22a78.
extern GlobalHalves gGlobal_c22a78;

void reset_half_12348c(void* half);                              // 0x710012348c

// 0x71000f4cf0
void reset_halves_f4cf0() {
    if (gGlobal_c22af8.first)
        reset_half_f4d30(gGlobal_c22af8.first);
    if (gGlobal_c22af8.second)
        reset_half_f4d30(gGlobal_c22af8.second);
}

// 0x71000fd674
void reset_halves_fd674() {
    if (gGlobal_c22aa0.first)
        reset_half_fd6b4(gGlobal_c22aa0.first);
    if (gGlobal_c22aa0.second)
        reset_half_fd6b4(gGlobal_c22aa0.second);
}

// 0x710011b6c8
void reset_halves_11b6c8() {
    if (gGlobal_c22270.first)
        reset_half_11b708(gGlobal_c22270.first);
    if (gGlobal_c22270.second)
        reset_half_11b708(gGlobal_c22270.second);
}

// 0x7100120130
void reset_halves_120130() {
    if (gGlobal_c22af0.first)
        reset_half_120170(gGlobal_c22af0.first);
    if (gGlobal_c22af0.second)
        reset_half_120170(gGlobal_c22af0.second);
}

// 0x710012344c
void reset_halves_12344c() {
    if (gGlobal_c22a78.first)
        reset_half_12348c(gGlobal_c22a78.first);
    if (gGlobal_c22a78.second)
        reset_half_12348c(gGlobal_c22a78.second);
}


// Buffer releases: hand the buffer back to its allocator (virtual slot +60) and clear it.
class BufferAllocator {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void v40();
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void free(void* buffer);                                        // +60
};

// 0x71002476f4
struct BufferSlot_2476f4 {
    void release();

    void* owner;              // +00
    void* buffer;             // +08
    void* value10;            // +10
    BufferAllocator* allocator; // +18
};

void BufferSlot_2476f4::release() {
    if (buffer)
        allocator->free(buffer);
    buffer = nullptr;
}

// 0x7100247d58
struct BufferSlot_247d58 {
    void release();

    void* owner;              // +00
    void* buffer;             // +08
    void* value10;            // +10
    BufferAllocator* allocator; // +18
};

void BufferSlot_247d58::release() {
    if (buffer)
        allocator->free(buffer);
    buffer = nullptr;
}

// 0x710024cc24
struct BufferSlot_24cc24 {
    void release();

    void* owner;              // +00
    void* buffer;             // +08
    void* value10;            // +10
    BufferAllocator* allocator; // +18
};

void BufferSlot_24cc24::release() {
    if (buffer)
        allocator->free(buffer);
    buffer = nullptr;
}

// 0x710024d3a0
struct BufferSlot_24d3a0 {
    void release();

    void* owner;              // +00
    void* buffer;             // +08
    void* value10;            // +10
    BufferAllocator* allocator; // +18
};

void BufferSlot_24d3a0::release() {
    if (buffer)
        allocator->free(buffer);
    buffer = nullptr;
}

// 0x710024d6a4
struct BufferSlot_24d6a4 {
    void release();

    void* owner;              // +00
    void* buffer;             // +08
    void* value10;            // +10
    BufferAllocator* allocator; // +18
};

void BufferSlot_24d6a4::release() {
    if (buffer)
        allocator->free(buffer);
    buffer = nullptr;
}
