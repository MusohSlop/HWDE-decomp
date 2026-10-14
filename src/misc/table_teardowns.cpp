// Banked table teardowns (0x7100211744, 0x7100211c74, 0x7100212a08): unload a global banked text
// table, delete it on the default heap and clear the global. Three tables with their own unload
// functions. Names are descriptive placeholders. Status: matching/README.md.

class DefaultHeap {
public:
    void* allocate(unsigned long alignment, unsigned long size, unsigned char a, unsigned char b); // 0x710045c458
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

static inline void free_default(void* ptr) {
    get_default_heap()->release(ptr, 1, 0);
}

struct TextChunks {
    TextChunks();                                                           // 0x7100218c18
    ~TextChunks();                                                          // 0x7100218c2c
    void release(unsigned char keep);                                       // 0x7100218c68

    unsigned char data[0x10];
};
struct TextTable211744 {
    TextTable211744() {
        loaded[0] = 0;
        loaded[1] = 0;
        storage[0] = nullptr;
        storage[1] = nullptr;
    }
    void unload();                                                          // 0x71002117d8
    static void* operator new(unsigned long size) { return get_default_heap()->allocate(0x10, size, 1, 0); }
    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }

    void* storage[2];         // +00
    TextChunks banks[2];      // +10
    unsigned char loaded[2];  // +30
    unsigned char pad32[6];
    void* extra_storage[5];   // +38
    TextChunks extra[5];      // +60
};
// Reached through the GOT slot at 0x7100c23340.
extern TextTable211744* gTable_c23340;

// 0x7100211744
void destroy_table_211744() {
    if (gTable_c23340) {
        gTable_c23340->unload();
        delete gTable_c23340;
        gTable_c23340 = nullptr;
    }
}
struct TextTable211c74 {
    TextTable211c74() {
        loaded[0] = 0;
        loaded[1] = 0;
        storage[0] = nullptr;
        storage[1] = nullptr;
        count = 0;
    }
    void unload();                                                          // 0x7100211d08
    static void* operator new(unsigned long size) { return get_default_heap()->allocate(0x10, size, 1, 0); }
    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }

    void* storage[2];         // +00
    TextChunks banks[2];      // +10
    unsigned char loaded[2];  // +30
    unsigned char pad32[2];
    int count;                // +34
    void* extra_storage[5];   // +38
    TextChunks extra[5];      // +60
};
// Reached through the GOT slot at 0x7100c23348.
extern TextTable211c74* gTable_c23348;

// 0x7100211c74
void destroy_table_211c74() {
    if (gTable_c23348) {
        gTable_c23348->unload();
        delete gTable_c23348;
        gTable_c23348 = nullptr;
    }
}
struct TextTable212a08 {
    TextTable212a08() {
        loaded[0] = 0;
        loaded[1] = 0;
        storage[0] = nullptr;
        storage[1] = nullptr;
        count = 0;
    }
    void unload();                                                          // 0x7100212a9c
    static void* operator new(unsigned long size) { return get_default_heap()->allocate(0x10, size, 1, 0); }
    static void operator delete(void* ptr) { get_default_heap()->release(ptr, 1, 0); }

    void* storage[2];         // +00
    TextChunks banks[2];      // +10
    unsigned char loaded[2];  // +30
    unsigned char pad32[2];
    int count;                // +34
    void* extra_storage[5];   // +38
    TextChunks extra[5];      // +60
};
// Reached through the GOT slot at 0x7100c23350.
extern TextTable212a08* gTable_c23350;

// 0x7100212a08
void destroy_table_212a08() {
    if (gTable_c23350) {
        gTable_c23350->unload();
        delete gTable_c23350;
        gTable_c23350 = nullptr;
    }
}

// 0x71002117d8
void TextTable211744::unload() {
    for (int i = 0; i < 2; ++i) {
        if (storage[i]) {
            if (loaded[i]) {
                banks[i].release(0);
                loaded[i] = 0;
            }
            free_default(storage[i]);
            storage[i] = nullptr;
        }
    }
    for (int i = 0; i < 5; ++i) {
        extra[i].release(0);
        if (extra_storage[i]) {
            free_default(extra_storage[i]);
            extra_storage[i] = nullptr;
        }
    }
}
// 0x7100211d08
void TextTable211c74::unload() {
    for (int i = 0; i < 2; ++i) {
        if (storage[i]) {
            if (loaded[i]) {
                banks[i].release(0);
                loaded[i] = 0;
            }
            free_default(storage[i]);
            storage[i] = nullptr;
        }
    }
    for (int i = 0; i < 5; ++i) {
        extra[i].release(0);
        if (extra_storage[i]) {
            free_default(extra_storage[i]);
            extra_storage[i] = nullptr;
        }
    }
    TextTable211744* first = gTable_c23340;
    if (first->storage[1] && first->loaded[1]) {
        first->banks[1].release(0);
        first->loaded[1] = 0;
    }
    for (int i = 0; i < 5; ++i)
        first->extra[i].release(0);
}
// 0x7100212a9c
void TextTable212a08::unload() {
    for (int i = 0; i < 2; ++i) {
        if (storage[i]) {
            if (loaded[i]) {
                banks[i].release(0);
                loaded[i] = 0;
            }
            free_default(storage[i]);
            storage[i] = nullptr;
        }
    }
    for (int i = 0; i < 5; ++i) {
        extra[i].release(0);
        if (extra_storage[i]) {
            free_default(extra_storage[i]);
            extra_storage[i] = nullptr;
        }
    }
}
// 0x71002116bc
void create_table_2116bc() {
    if (!gTable_c23340)
        gTable_c23340 = new TextTable211744;
}
// 0x7100211be8
void create_table_211be8() {
    if (!gTable_c23348)
        gTable_c23348 = new TextTable211c74;
}
// 0x710021297c
void create_table_21297c() {
    if (!gTable_c23350)
        gTable_c23350 = new TextTable212a08;
}