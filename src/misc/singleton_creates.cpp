// Singleton creation found by tools/family_scan.py --immediates (the same shape as
// create_demo_effect_pool in event/demo_effect_pool.cpp): each builds its object on the default heap
// the first time and keeps it in its global. They differ only in the object (its size and
// constructor); the types and functions are named after the creating function's address.
// Status: matching/README.md.

class DefaultHeap {
public:
    void* allocate(unsigned int alignment, unsigned long size, int a, int b); // 0x710045c458
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

inline void* operator new(unsigned long, void* storage) { return storage; }

class Singletond5698 {
public:
    Singletond5698();                                             // 0x71000d51e8

    unsigned char data[0x620];
};
extern Singletond5698* gSingletond5698;

// 0x71000d5698
void create_singleton_d5698() {
    if (!gSingletond5698) {
        void* storage = get_default_heap()->allocate(0x10, sizeof(Singletond5698), 1, 0);
        gSingletond5698 = new (storage) Singletond5698;
    }
}

class Singletondde30 {
public:
    Singletondde30();                                             // 0x71000de068

    unsigned char data[0x1340];
};
extern Singletondde30* gSingletondde30;

// 0x71000dde30
void create_singleton_dde30() {
    if (!gSingletondde30) {
        void* storage = get_default_heap()->allocate(0x10, sizeof(Singletondde30), 1, 0);
        gSingletondde30 = new (storage) Singletondde30;
    }
}

class Singletondf4cc {
public:
    Singletondf4cc();                                             // 0x71000df644

    unsigned char data[0x4458];
};
extern Singletondf4cc* gSingletondf4cc;

// 0x71000df4cc
void create_singleton_df4cc() {
    if (!gSingletondf4cc) {
        void* storage = get_default_heap()->allocate(0x10, sizeof(Singletondf4cc), 1, 0);
        gSingletondf4cc = new (storage) Singletondf4cc;
    }
}

class Singleton12c178 {
public:
    Singleton12c178();                                            // 0x710012c278

    unsigned char data[0xad0];
};
extern Singleton12c178* gSingleton12c178;

// 0x710012c178
void create_singleton_12c178() {
    if (!gSingleton12c178) {
        void* storage = get_default_heap()->allocate(0x10, sizeof(Singleton12c178), 1, 0);
        gSingleton12c178 = new (storage) Singleton12c178;
    }
}

class Singleton288e30 {
public:
    Singleton288e30();                                            // 0x7100288a40

    unsigned char data[0x8a0];
};
extern Singleton288e30* gSingleton288e30;

// 0x7100288e30
void create_singleton_288e30() {
    if (!gSingleton288e30) {
        void* storage = get_default_heap()->allocate(0x10, sizeof(Singleton288e30), 1, 0);
        gSingleton288e30 = new (storage) Singleton288e30;
    }
}

class Singleton291d18 {
public:
    Singleton291d18();                                            // 0x7100291760

    unsigned char data[0x1530];
};
extern Singleton291d18* gSingleton291d18;

// 0x7100291d18
void create_singleton_291d18() {
    if (!gSingleton291d18) {
        void* storage = get_default_heap()->allocate(0x10, sizeof(Singleton291d18), 1, 0);
        gSingleton291d18 = new (storage) Singleton291d18;
    }
}

class Singleton414004 {
public:
    Singleton414004();                                            // 0x710041368c

    unsigned char data[0x5a40];
};
extern Singleton414004* gSingleton414004;

// 0x7100414004
void create_singleton_414004() {
    if (!gSingleton414004) {
        void* storage = get_default_heap()->allocate(0x10, sizeof(Singleton414004), 1, 0);
        gSingleton414004 = new (storage) Singleton414004;
    }
}

class Singleton444958 {
public:
    Singleton444958();                                            // 0x7100444528

    unsigned char data[0x58f8];
};
extern Singleton444958* gSingleton444958;

// 0x7100444958
void create_singleton_444958() {
    if (!gSingleton444958) {
        void* storage = get_default_heap()->allocate(0x10, sizeof(Singleton444958), 1, 0);
        gSingleton444958 = new (storage) Singleton444958;
    }
}
