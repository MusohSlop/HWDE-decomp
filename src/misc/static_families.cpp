// Static-object families found by tools/family_scan.py, grouped until their source files are
// linked: paired singleton teardowns, function-local statics in inline helpers (reached
// through the GOT because the helpers are linkonce), static objects built on first use, and
// manager lookups. Within a family the bodies are identical apart from the globals and
// callees they use; classes and functions are named after their address, callees after
// theirs. Status: matching/README.md.

class DefaultHeap {
public:
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

static inline void destroy_singleton(void*& slot) {
    if (void* object = slot) {
        get_default_heap()->release(object, 1, 0);
        slot = nullptr;
    }
}

struct SingletonPair {
    void* first;
    void* second;
};

inline void* null_value() { return nullptr; }

// Paired singleton teardowns.

// Reached through the GOT slot at 0x7100c22a90.
extern SingletonPair gGlobal_c22a90;

// Reached through the GOT slot at 0x7100c22a80.
extern SingletonPair gGlobal_c22a80;

// Reached through the GOT slot at 0x7100c22ae8.
extern SingletonPair gGlobal_c22ae8;

// Reached through the GOT slot at 0x7100c22308.
extern SingletonPair gGlobal_c22308;

// Reached through the GOT slot at 0x7100c22a88.
extern SingletonPair gGlobal_c22a88;

// Reached through the GOT slot at 0x7100c22ae0.
extern SingletonPair gGlobal_c22ae0;

// Reached through the GOT slot at 0x7100c22ab0.
extern SingletonPair gGlobal_c22ab0;

// 0x71000dd4a0
void destroy_pair_dd4a0() {
    destroy_singleton(gGlobal_c22a90.first);
    destroy_singleton(gGlobal_c22a90.second);
}

// 0x71000de698
void destroy_pair_de698() {
    destroy_singleton(gGlobal_c22a80.first);
    destroy_singleton(gGlobal_c22a80.second);
}

// 0x71000e075c
void destroy_pair_e075c() {
    destroy_singleton(gGlobal_c22ae8.first);
    destroy_singleton(gGlobal_c22ae8.second);
}

// 0x71000f8f48
void destroy_pair_f8f48() {
    destroy_singleton(gGlobal_c22308.first);
    destroy_singleton(gGlobal_c22308.second);
}

// 0x710012c41c
void destroy_pair_12c41c() {
    destroy_singleton(gGlobal_c22a88.first);
    destroy_singleton(gGlobal_c22a88.second);
}

// 0x710012cd10
void destroy_pair_12cd10() {
    destroy_singleton(gGlobal_c22ae0.first);
    destroy_singleton(gGlobal_c22ae0.second);
}

// 0x7100130b5c
void destroy_pair_130b5c() {
    destroy_singleton(gGlobal_c22ab0.first);
    destroy_singleton(gGlobal_c22ab0.second);
}


// Function-local statics in inline helpers, initialized to null on first use.








// 0x71001e4aec
inline void** holder_1e4aec() {
    static void* value = null_value();
    return &value;
}

void** static_slot_1e4aec() {
    return holder_1e4aec();
}

// 0x71005d28fc
inline void** holder_5d28fc() {
    static void* value = null_value();
    return &value;
}

void** static_slot_5d28fc() {
    return holder_5d28fc();
}

// 0x71005dafc8
inline void** holder_5dafc8() {
    static void* value = null_value();
    return &value;
}

void** static_slot_5dafc8() {
    return holder_5dafc8();
}

// 0x71005dc33c
inline void** holder_5dc33c() {
    static void* value = null_value();
    return &value;
}

void** static_slot_5dc33c() {
    return holder_5dc33c();
}

// 0x71006001a4
inline void** holder_6001a4() {
    static void* value = null_value();
    return &value;
}

void** static_slot_6001a4() {
    return holder_6001a4();
}

// 0x71006001f4
inline void** holder_6001f4() {
    static void* value = null_value();
    return &value;
}

void** static_slot_6001f4() {
    return holder_6001f4();
}

// 0x71006004c0
inline void** holder_6004c0() {
    static void* value = null_value();
    return &value;
}

void** static_slot_6004c0() {
    return holder_6004c0();
}


// Nested function-local statics: a static pointer to another inline helper's static.












// 0x71001dd4fc
inline void** inner_1dd4fc() {
    static void* value = null_value();
    return &value;
}

inline void*** outer_1dd4fc() {
    static void** value = inner_1dd4fc();
    return &value;
}

void*** static_chain_1dd4fc() {
    return outer_1dd4fc();
}

// 0x71001e45ac
inline void** inner_1e45ac() {
    static void* value = null_value();
    return &value;
}

inline void*** outer_1e45ac() {
    static void** value = inner_1e45ac();
    return &value;
}

void*** static_chain_1e45ac() {
    return outer_1e45ac();
}

// 0x71001e4968
inline void** inner_1e4968() {
    static void* value = null_value();
    return &value;
}

inline void*** outer_1e4968() {
    static void** value = inner_1e4968();
    return &value;
}

void*** static_chain_1e4968() {
    return outer_1e4968();
}

// 0x71005d004c
inline void** inner_5d004c() {
    static void* value = null_value();
    return &value;
}

inline void*** outer_5d004c() {
    static void** value = inner_5d004c();
    return &value;
}

void*** static_chain_5d004c() {
    return outer_5d004c();
}

// 0x71005d2158
inline void** inner_5d2158() {
    static void* value = null_value();
    return &value;
}

inline void*** outer_5d2158() {
    static void** value = inner_5d2158();
    return &value;
}

void*** static_chain_5d2158() {
    return outer_5d2158();
}

// 0x71005db19c
inline void** inner_5db19c() {
    static void* value = null_value();
    return &value;
}

inline void*** outer_5db19c() {
    static void** value = inner_5db19c();
    return &value;
}

void*** static_chain_5db19c() {
    return outer_5db19c();
}

// 0x71005dc1b0
inline void** inner_5dc1b0() {
    static void* value = null_value();
    return &value;
}

inline void*** outer_5dc1b0() {
    static void** value = inner_5dc1b0();
    return &value;
}

void*** static_chain_5dc1b0() {
    return outer_5dc1b0();
}

// 0x71005de570
inline void** inner_5de570() {
    static void* value = null_value();
    return &value;
}

inline void*** outer_5de570() {
    static void** value = inner_5de570();
    return &value;
}

void*** static_chain_5de570() {
    return outer_5de570();
}

// 0x71005e3298
inline void** inner_5e3298() {
    static void* value = null_value();
    return &value;
}

inline void*** outer_5e3298() {
    static void** value = inner_5e3298();
    return &value;
}

void*** static_chain_5e3298() {
    return outer_5e3298();
}

// 0x71005e3b6c
inline void** inner_5e3b6c() {
    static void* value = null_value();
    return &value;
}

inline void*** outer_5e3b6c() {
    static void** value = inner_5e3b6c();
    return &value;
}

void*** static_chain_5e3b6c() {
    return outer_5e3b6c();
}

// 0x71005fd9fc
inline void** inner_5fd9fc() {
    static void* value = null_value();
    return &value;
}

inline void*** outer_5fd9fc() {
    static void** value = inner_5fd9fc();
    return &value;
}

void*** static_chain_5fd9fc() {
    return outer_5fd9fc();
}
