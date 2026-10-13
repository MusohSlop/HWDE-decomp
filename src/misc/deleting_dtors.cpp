// Deleting destructors found by tools/family_scan.py: each runs its base destructor and
// returns the object to the default heap through the class operator delete, which tests for
// null (the same shape as the scene tasks' 0x71002725bc). Grouped here until their source
// files are linked; classes are named after the destructor address, bases after theirs.
// Status: matching/README.md.

class DefaultHeap {
public:
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c


class DtorBase_38763c {
public:
    virtual ~DtorBase_38763c();                                    // 0x710038763c
};


// 0x71001dd8e0
class Owned_1dd8e0 : public DtorBase_38763c {
public:
    ~Owned_1dd8e0() override;

    static void operator delete(void* ptr) {
        if (ptr)
            get_default_heap()->release(ptr, 1, 0);
    }
};

Owned_1dd8e0::~Owned_1dd8e0() {}


// 0x71003adcb8
class Owned_3adcb8 : public DtorBase_38763c {
public:
    ~Owned_3adcb8() override;

    static void operator delete(void* ptr) {
        if (ptr)
            get_default_heap()->release(ptr, 1, 0);
    }
};

Owned_3adcb8::~Owned_3adcb8() {}


// 0x71003adf64
class Owned_3adf64 : public DtorBase_38763c {
public:
    ~Owned_3adf64() override;

    static void operator delete(void* ptr) {
        if (ptr)
            get_default_heap()->release(ptr, 1, 0);
    }
};

Owned_3adf64::~Owned_3adf64() {}


// 0x71003ae614
class Owned_3ae614 : public DtorBase_38763c {
public:
    ~Owned_3ae614() override;

    static void operator delete(void* ptr) {
        if (ptr)
            get_default_heap()->release(ptr, 1, 0);
    }
};

Owned_3ae614::~Owned_3ae614() {}


// 0x71003b00f0
class Owned_3b00f0 : public DtorBase_38763c {
public:
    ~Owned_3b00f0() override;

    static void operator delete(void* ptr) {
        if (ptr)
            get_default_heap()->release(ptr, 1, 0);
    }
};

Owned_3b00f0::~Owned_3b00f0() {}


// 0x71003c58e4
class Owned_3c58e4 : public DtorBase_38763c {
public:
    ~Owned_3c58e4() override;

    static void operator delete(void* ptr) {
        if (ptr)
            get_default_heap()->release(ptr, 1, 0);
    }
};

Owned_3c58e4::~Owned_3c58e4() {}
