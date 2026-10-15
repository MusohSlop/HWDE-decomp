// Command pool appends (fourth session, 4-copy family 4adcc): each constructs one command object (just a vtable
// pointer) at the pool's write offset and counts it. CommandPool::emplace<T> for four command types: 0x710004adcc,
// 0x710004ae94, 0x710004aec0 and 0x710004aeec, and with constructor arguments 0x710004adf8, 0x710004af78 and
// 0x710004aff4. Names are descriptive placeholders.

inline void* operator new(unsigned long, void* p) noexcept { return p; }

// Their vtables are reached through the GOT slots at 0x7100c21e60, 0x7100c21e80, 0x7100c21e88, 0x7100c21e90,
// 0x7100c21e68, 0x7100c21ea8 and 0x7100c21eb8.
struct PoolCommand4adcc {
    virtual void run();
};
struct PoolCommand4ae94 {
    virtual void run();
};
struct PoolCommand4aec0 {
    virtual void run();
};
struct PoolCommand4aeec {
    virtual void run();
};

struct PoolCommand4adf8 {
    PoolCommand4adf8(void* a, void* b) : first(a), second(b) {}
    virtual void run();
    void* first;              // +08
    void* second;             // +10
};
struct PoolCommand4af78 {
    PoolCommand4af78(int a, void* b, float c) : id(a), target(b), value(c) {}
    virtual void run();
    int id;                   // +08
    void* target;             // +10
    float value;              // +18
};
struct PoolCommand4aff4 {
    PoolCommand4aff4(int a, void* b, float c, float d) : id(a), target(b), from(c), to(d) {}
    virtual void run();
    int id;                   // +08
    void* target;             // +10
    float from;               // +18
    float to;                 // +1c
};

struct CommandPool {
    template <class T> void emplace();
    template <class T, class... A> void emplace(A... args);

    unsigned char pad0[0x24];
    int count;                // +24
    unsigned char pad28[0x38];
    char* buffer;             // +60
    long used;                // +68
};

template <class T>
void CommandPool::emplace() {
    count++;
    char* p = buffer + used;
    used += sizeof(T);
    new (p) T();
}

template <class T, class... A>
void CommandPool::emplace(A... args) {
    count++;
    char* p = buffer + used;
    used += sizeof(T);
    new (p) T(args...);
}

template void CommandPool::emplace<PoolCommand4adcc>();
template void CommandPool::emplace<PoolCommand4ae94>();
template void CommandPool::emplace<PoolCommand4aec0>();
template void CommandPool::emplace<PoolCommand4aeec>();
template void CommandPool::emplace<PoolCommand4adf8>(void*, void*);
template void CommandPool::emplace<PoolCommand4af78>(int, void*, float);
template void CommandPool::emplace<PoolCommand4aff4>(int, void*, float, float);
