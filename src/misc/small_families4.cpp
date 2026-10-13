// Further code families found by tools/family_scan.py, grouped until their source files are
// linked: nine-sprite constructors, swapped-argument calls that negate a result vector, and
// disposals through the owning pool. Within a family the bodies are identical apart from the
// callees they use; classes and functions are named after their address, callees after theirs.
// Status: matching/README.md.

class LayoutSprite {
public:
    LayoutSprite();                                                         // 0x71001ef52c
    virtual void v00();
    unsigned char pad[0x40];
};

class PoolAllocator {
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
    virtual void free(void* object);                                        // +60
};

struct Pool {
    PoolAllocator* allocator; // +00
};

// Nine-sprite constructors.

// 0x71000f2f08
struct SpriteRow_f2f08 {
    SpriteRow_f2f08();

    LayoutSprite sprites[9];
};

SpriteRow_f2f08::SpriteRow_f2f08() {}

// 0x710011fa70
struct SpriteRow_11fa70 {
    SpriteRow_11fa70();

    LayoutSprite sprites[9];
};

SpriteRow_11fa70::SpriteRow_11fa70() {}

// 0x7100132a90
struct SpriteRow_132a90 {
    SpriteRow_132a90();

    LayoutSprite sprites[9];
};

SpriteRow_132a90::SpriteRow_132a90() {}

// 0x71002d64a0
struct SpriteRow_2d64a0 {
    SpriteRow_2d64a0();

    LayoutSprite sprites[9];
};

SpriteRow_2d64a0::SpriteRow_2d64a0() {}


// Swapped-argument calls that negate the optional result vector.

void solve_4e730c(void* a, void* b, void* c, void* d);          // 0x71004e730c

void solve_501658(void* a, void* b, void* c, void* d);          // 0x7100501658

void solve_510ae8(void* a, void* b, void* c, void* d);          // 0x7100510ae8

void solve_510d20(void* a, void* b, void* c, void* d);          // 0x7100510d20

void solve_511210(void* a, void* b, void* c, void* d);          // 0x7100511210

// 0x71004e78d0
void solve_reversed_4e78d0(void* a, void* b, void* c, void* d, float* normal) {
    solve_4e730c(b, a, d, c);
    if (normal) {
        normal[0] = -normal[0];
        normal[1] = -normal[1];
        normal[2] = -normal[2];
    }
}

// 0x7100502714
void solve_reversed_502714(void* a, void* b, void* c, void* d, float* normal) {
    solve_501658(b, a, d, c);
    if (normal) {
        normal[0] = -normal[0];
        normal[1] = -normal[1];
        normal[2] = -normal[2];
    }
}

// 0x71005114dc
void solve_reversed_5114dc(void* a, void* b, void* c, void* d, float* normal) {
    solve_510ae8(b, a, d, c);
    if (normal) {
        normal[0] = -normal[0];
        normal[1] = -normal[1];
        normal[2] = -normal[2];
    }
}

// 0x71005115b8
void solve_reversed_5115b8(void* a, void* b, void* c, void* d, float* normal) {
    solve_510d20(b, a, d, c);
    if (normal) {
        normal[0] = -normal[0];
        normal[1] = -normal[1];
        normal[2] = -normal[2];
    }
}

// 0x7100511a34
void solve_reversed_511a34(void* a, void* b, void* c, void* d, float* normal) {
    solve_511210(b, a, d, c);
    if (normal) {
        normal[0] = -normal[0];
        normal[1] = -normal[1];
        normal[2] = -normal[2];
    }
}


// Disposals through the owning pool: detach from the pool, dispose of the object (virtual
// slot +8) and return it to the pool's allocator.

void detach_471e90(Pool* pool);                                   // 0x7100471e90

// 0x7100472ba0
class Pooled_472ba0 {
public:
    virtual void v00();
    virtual void dispose();   // +08

    void release();

    unsigned char pad[0x158];
    Pool* pool;               // +160
};

void Pooled_472ba0::release() {
    detach_471e90(pool);
    PoolAllocator* allocator = pool ? pool->allocator : nullptr;
    dispose();
    allocator->free(this);
}

// 0x710047a5d8
class Pooled_47a5d8 {
public:
    virtual void v00();
    virtual void dispose();   // +08

    void release();

    unsigned char pad[0x158];
    Pool* pool;               // +160
};

void Pooled_47a5d8::release() {
    detach_471e90(pool);
    PoolAllocator* allocator = pool ? pool->allocator : nullptr;
    dispose();
    allocator->free(this);
}

// 0x71004801c8
class Pooled_4801c8 {
public:
    virtual void v00();
    virtual void dispose();   // +08

    void release();

    unsigned char pad[0x158];
    Pool* pool;               // +160
};

void Pooled_4801c8::release() {
    detach_471e90(pool);
    PoolAllocator* allocator = pool ? pool->allocator : nullptr;
    dispose();
    allocator->free(this);
}

// 0x7100483460
class Pooled_483460 {
public:
    virtual void v00();
    virtual void dispose();   // +08

    void release();

    unsigned char pad[0x158];
    Pool* pool;               // +160
};

void Pooled_483460::release() {
    detach_471e90(pool);
    PoolAllocator* allocator = pool ? pool->allocator : nullptr;
    dispose();
    allocator->free(this);
}

// 0x710048a340
class Pooled_48a340 {
public:
    virtual void v00();
    virtual void dispose();   // +08

    void release();

    unsigned char pad[0x158];
    Pool* pool;               // +160
};

void Pooled_48a340::release() {
    detach_471e90(pool);
    PoolAllocator* allocator = pool ? pool->allocator : nullptr;
    dispose();
    allocator->free(this);
}
