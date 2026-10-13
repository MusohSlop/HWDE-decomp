// Paired singleton creation found by tools/family_scan.py --immediates: each allocates the two
// halves of a global pair on the default heap and constructs them with index 0 and 1 (an
// out-of-line constructor). They differ in the global, the object size and the constructor;
// functions are named after their address, constructors after theirs. Status: matching/README.md.

class DefaultHeap {
public:
    void* allocate(unsigned long alignment, unsigned long size, unsigned char lock,
                   unsigned char keep);                                     // 0x710045c458
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

struct SingletonPair {
    void* first;
    void* second;
};

// Reached through the GOT slot at 0x7100c22a90.
extern SingletonPair gGlobal_c22a90;

void construct_dd7bc(void* object, int index);                        // 0x71000dd7bc

// 0x71000dd420
void create_pair_dd420() {
    if (!gGlobal_c22a90.first) {
        void* object = get_default_heap()->allocate(0x10, 0x3d0, 1, 0);
        construct_dd7bc(object, 0);
        gGlobal_c22a90.first = object;
    }
    if (!gGlobal_c22a90.second) {
        void* object = get_default_heap()->allocate(0x10, 0x3d0, 1, 0);
        construct_dd7bc(object, 1);
        gGlobal_c22a90.second = object;
    }
}

// Reached through the GOT slot at 0x7100c22ae8.
extern SingletonPair gGlobal_c22ae8;

void construct_e19c4(void* object, int index);                        // 0x71000e19c4

// 0x71000e06dc
void create_pair_e06dc() {
    if (!gGlobal_c22ae8.first) {
        void* object = get_default_heap()->allocate(0x10, 0x2e48, 1, 0);
        construct_e19c4(object, 0);
        gGlobal_c22ae8.first = object;
    }
    if (!gGlobal_c22ae8.second) {
        void* object = get_default_heap()->allocate(0x10, 0x2e48, 1, 0);
        construct_e19c4(object, 1);
        gGlobal_c22ae8.second = object;
    }
}

// Reached through the GOT slot at 0x7100c21d48.
extern SingletonPair gGlobal_c21d48;

void construct_f465c(void* object, int index);                        // 0x71000f465c

// 0x71000f42d8
void create_pair_f42d8() {
    if (!gGlobal_c21d48.first) {
        void* object = get_default_heap()->allocate(0x10, 0x48, 1, 0);
        construct_f465c(object, 0);
        gGlobal_c21d48.first = object;
    }
    if (!gGlobal_c21d48.second) {
        void* object = get_default_heap()->allocate(0x10, 0x48, 1, 0);
        construct_f465c(object, 1);
        gGlobal_c21d48.second = object;
    }
}

// Reached through the GOT slot at 0x7100c22308.
extern SingletonPair gGlobal_c22308;

void construct_fbd24(void* object, int index);                        // 0x71000fbd24

// 0x71000f8ec8
void create_pair_f8ec8() {
    if (!gGlobal_c22308.first) {
        void* object = get_default_heap()->allocate(0x10, 0xdfd8, 1, 0);
        construct_fbd24(object, 0);
        gGlobal_c22308.first = object;
    }
    if (!gGlobal_c22308.second) {
        void* object = get_default_heap()->allocate(0x10, 0xdfd8, 1, 0);
        construct_fbd24(object, 1);
        gGlobal_c22308.second = object;
    }
}

// Reached through the GOT slot at 0x7100c22aa0.
extern SingletonPair gGlobal_c22aa0;

void construct_fd8e8(void* object, int index);                        // 0x71000fd8e8

// 0x71000fd30c
void create_pair_fd30c() {
    if (!gGlobal_c22aa0.first) {
        void* object = get_default_heap()->allocate(0x10, 0x880, 1, 0);
        construct_fd8e8(object, 0);
        gGlobal_c22aa0.first = object;
    }
    if (!gGlobal_c22aa0.second) {
        void* object = get_default_heap()->allocate(0x10, 0x880, 1, 0);
        construct_fd8e8(object, 1);
        gGlobal_c22aa0.second = object;
    }
}

// Reached through the GOT slot at 0x7100c22270.
extern SingletonPair gGlobal_c22270;

void construct_11ead8(void* object, int index);                       // 0x710011ead8

// 0x710011b4bc
void create_pair_11b4bc() {
    if (!gGlobal_c22270.first) {
        void* object = get_default_heap()->allocate(0x10, 0x8410, 1, 0);
        construct_11ead8(object, 0);
        gGlobal_c22270.first = object;
    }
    if (!gGlobal_c22270.second) {
        void* object = get_default_heap()->allocate(0x10, 0x8410, 1, 0);
        construct_11ead8(object, 1);
        gGlobal_c22270.second = object;
    }
}

// Reached through the GOT slot at 0x7100c22ac8.
extern SingletonPair gGlobal_c22ac8;

void construct_11f34c(void* object, int index);                       // 0x710011f34c

// 0x710011f1e0
void create_pair_11f1e0() {
    if (!gGlobal_c22ac8.first) {
        void* object = get_default_heap()->allocate(0x10, 0xa6c8, 1, 0);
        construct_11f34c(object, 0);
        gGlobal_c22ac8.first = object;
    }
    if (!gGlobal_c22ac8.second) {
        void* object = get_default_heap()->allocate(0x10, 0xa6c8, 1, 0);
        construct_11f34c(object, 1);
        gGlobal_c22ac8.second = object;
    }
}

// Reached through the GOT slot at 0x7100c22af0.
extern SingletonPair gGlobal_c22af0;

void construct_122bac(void* object, int index);                       // 0x7100122bac

// 0x710011ffb4
void create_pair_11ffb4() {
    if (!gGlobal_c22af0.first) {
        void* object = get_default_heap()->allocate(0x10, 0x1c80, 1, 0);
        construct_122bac(object, 0);
        gGlobal_c22af0.first = object;
    }
    if (!gGlobal_c22af0.second) {
        void* object = get_default_heap()->allocate(0x10, 0x1c80, 1, 0);
        construct_122bac(object, 1);
        gGlobal_c22af0.second = object;
    }
}

// Reached through the GOT slot at 0x7100c22a78.
extern SingletonPair gGlobal_c22a78;

void construct_127ad4(void* object, int index);                       // 0x7100127ad4

// 0x71001231ac
void create_pair_1231ac() {
    if (!gGlobal_c22a78.first) {
        void* object = get_default_heap()->allocate(0x10, 0x72c0, 1, 0);
        construct_127ad4(object, 0);
        gGlobal_c22a78.first = object;
    }
    if (!gGlobal_c22a78.second) {
        void* object = get_default_heap()->allocate(0x10, 0x72c0, 1, 0);
        construct_127ad4(object, 1);
        gGlobal_c22a78.second = object;
    }
}

// Reached through the GOT slot at 0x7100c22a88.
extern SingletonPair gGlobal_c22a88;

void construct_12cb28(void* object, int index);                       // 0x710012cb28

// 0x710012c39c
void create_pair_12c39c() {
    if (!gGlobal_c22a88.first) {
        void* object = get_default_heap()->allocate(0x10, 0x11b8, 1, 0);
        construct_12cb28(object, 0);
        gGlobal_c22a88.first = object;
    }
    if (!gGlobal_c22a88.second) {
        void* object = get_default_heap()->allocate(0x10, 0x11b8, 1, 0);
        construct_12cb28(object, 1);
        gGlobal_c22a88.second = object;
    }
}

// Reached through the GOT slot at 0x7100c22ae0.
extern SingletonPair gGlobal_c22ae0;

void construct_12d5e4(void* object, int index);                       // 0x710012d5e4

// 0x710012cc90
void create_pair_12cc90() {
    if (!gGlobal_c22ae0.first) {
        void* object = get_default_heap()->allocate(0x10, 0x4a8, 1, 0);
        construct_12d5e4(object, 0);
        gGlobal_c22ae0.first = object;
    }
    if (!gGlobal_c22ae0.second) {
        void* object = get_default_heap()->allocate(0x10, 0x4a8, 1, 0);
        construct_12d5e4(object, 1);
        gGlobal_c22ae0.second = object;
    }
}

// Reached through the GOT slot at 0x7100c22a68.
extern SingletonPair gGlobal_c22a68;

void construct_1301d8(void* object, int index);                       // 0x71001301d8

// 0x710012d68c
void create_pair_12d68c() {
    if (!gGlobal_c22a68.first) {
        void* object = get_default_heap()->allocate(0x10, 0x8d60, 1, 0);
        construct_1301d8(object, 0);
        gGlobal_c22a68.first = object;
    }
    if (!gGlobal_c22a68.second) {
        void* object = get_default_heap()->allocate(0x10, 0x8d60, 1, 0);
        construct_1301d8(object, 1);
        gGlobal_c22a68.second = object;
    }
}

// Reached through the GOT slot at 0x7100c22ab0.
extern SingletonPair gGlobal_c22ab0;

void construct_130ce4(void* object, int index);                       // 0x7100130ce4

// 0x7100130adc
void create_pair_130adc() {
    if (!gGlobal_c22ab0.first) {
        void* object = get_default_heap()->allocate(0x10, 0x9e8, 1, 0);
        construct_130ce4(object, 0);
        gGlobal_c22ab0.first = object;
    }
    if (!gGlobal_c22ab0.second) {
        void* object = get_default_heap()->allocate(0x10, 0x9e8, 1, 0);
        construct_130ce4(object, 1);
        gGlobal_c22ab0.second = object;
    }
}
