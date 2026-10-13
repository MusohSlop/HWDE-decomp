// Singleton teardowns with a finalizer and an out-of-line destructor, found by
// tools/family_scan.py (the same shape as destroy_adv_board, 0x710029b5a4). Grouped here until
// their source files are linked; classes and functions are named after the function address.
// Status: matching/README.md.

class DefaultHeap {
public:
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c


// 0x71000dde7c
class Owner_dde7c {
public:
    ~Owner_dde7c();                                                  // 0x71000de138
    void finalize();                                                // 0x71000dded0

    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }
};
// Reached through the GOT slot at 0x7100c22aa8.
extern Owner_dde7c* gGlobal_c22aa8;

void destroy_owner_dde7c() {
    if (gGlobal_c22aa8) {
        gGlobal_c22aa8->finalize();
        delete gGlobal_c22aa8;
        gGlobal_c22aa8 = nullptr;
    }
}


// 0x71001e052c
class Owner_1e052c {
public:
    ~Owner_1e052c();                                                  // 0x71001dfb60
    void finalize();                                                // 0x71001ded64

    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }
};
// Reached through the GOT slot at 0x7100c22a40.
extern Owner_1e052c* gTrackRenderer;

void destroy_owner_1e052c() {
    if (gTrackRenderer) {
        gTrackRenderer->finalize();
        delete gTrackRenderer;
        gTrackRenderer = nullptr;
    }
}


// 0x71001e4490
class Owner_1e4490 {
public:
    ~Owner_1e4490();                                                  // 0x71001e14a4
    void finalize();                                                // 0x71001e19e8

    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }
};
// Reached through the GOT slot at 0x7100c22a00.
extern Owner_1e4490* gEffectManager;

void destroy_owner_1e4490() {
    if (gEffectManager) {
        gEffectManager->finalize();
        delete gEffectManager;
        gEffectManager = nullptr;
    }
}


// 0x71003c5770
class Owner_3c5770 {
public:
    ~Owner_3c5770();                                                  // 0x71003c57c4
    void finalize();                                                // 0x71003c57c4

    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }
};
// Reached through the GOT slot at 0x7100c2b3f8.
extern Owner_3c5770* gGlobal_c2b3f8;

void destroy_owner_3c5770() {
    if (gGlobal_c2b3f8) {
        gGlobal_c2b3f8->finalize();
        delete gGlobal_c2b3f8;
        gGlobal_c2b3f8 = nullptr;
    }
}
