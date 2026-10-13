// Large singleton creation found by tools/family_scan.py --immediates (the same shape as
// create_demo_light_system in event/demo_light_system.cpp): each builds its object on the default heap
// the first time and keeps it in its global. They differ only in the object (its size and
// constructor); the types and functions are named after the creating function's address.
// Status: matching/README.md.

class DefaultHeap {
public:
    void* allocate(unsigned int alignment, unsigned long size, int a, int b); // 0x710045c458
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

inline void* operator new(unsigned long, void* storage) { return storage; }

class Singleton115460 {
public:
    Singleton115460();                                            // 0x7100118e44

    unsigned char data[0x43490];
};
extern Singleton115460* gSingleton115460;

// 0x7100115460
void create_singleton_115460() {
    if (!gSingleton115460) {
        void* storage = get_default_heap()->allocate(0x10, sizeof(Singleton115460), 1, 0);
        gSingleton115460 = new (storage) Singleton115460;
    }
}

class Singleton1893f8 {
public:
    Singleton1893f8();                                            // 0x7100187d78

    unsigned char data[0xe0b50];
};
extern Singleton1893f8* gSingleton1893f8;

// 0x71001893f8
void create_singleton_1893f8() {
    if (!gSingleton1893f8) {
        void* storage = get_default_heap()->allocate(0x10, sizeof(Singleton1893f8), 1, 0);
        gSingleton1893f8 = new (storage) Singleton1893f8;
    }
}

class Singleton29b554 {
public:
    Singleton29b554();                                            // 0x7100299570

    unsigned char data[0x21e80];
};
extern Singleton29b554* gSingleton29b554;

// 0x710029b554
void create_singleton_29b554() {
    if (!gSingleton29b554) {
        void* storage = get_default_heap()->allocate(0x10, sizeof(Singleton29b554), 1, 0);
        gSingleton29b554 = new (storage) Singleton29b554;
    }
}
