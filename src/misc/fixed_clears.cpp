// Fixed-size clears found by scanning for one code shape: each fills its whole object with one
// byte value through memset, without a tail call. They come from loops (the loop idiom pass
// creates the memset after tail calls are marked; an explicit memset would be tail-called).
// They sit in their owners' source files across the image and are grouped here until those
// files are linked; types are named after the function address. Status: matching/README.md.

// 0x710004631c
struct ClearBlock_4631c {
    void clear();
    unsigned char bytes[0x132];
};

void ClearBlock_4631c::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x710004633c
struct ClearBlock_4633c {
    void clear();
    unsigned char bytes[0x132];
};

void ClearBlock_4633c::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x71003ccf50
struct ClearBlock_3ccf50 {
    void clear();
    unsigned char bytes[0x104];
};

void ClearBlock_3ccf50::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x71003debb4
struct ClearBlock_3debb4 {
    void clear();
    unsigned char bytes[0xd0];
};

void ClearBlock_3debb4::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x7100434338
struct ClearBlock_434338 {
    void clear();
    unsigned char bytes[0x9c];
};

void ClearBlock_434338::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x710043484c
struct ClearBlock_43484c {
    void clear();
    unsigned char bytes[0x84];
};

void ClearBlock_43484c::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x7100434874
struct ClearBlock_434874 {
    void clear();
    unsigned char bytes[0x84];
};

void ClearBlock_434874::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x71004386cc
struct ClearBlock_4386cc {
    void clear();
    unsigned char bytes[0xc84];
};

void ClearBlock_4386cc::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x71004386f4
struct ClearBlock_4386f4 {
    void clear();
    unsigned char bytes[0xc84];
};

void ClearBlock_4386f4::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x710043a94c
struct ClearBlock_43a94c {
    void clear();
    unsigned char bytes[0x480];
};

void ClearBlock_43a94c::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x7100443da8
struct ClearBlock_443da8 {
    void clear();
    unsigned char bytes[0x58];
};

void ClearBlock_443da8::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x71004611e8
struct ClearBlock_4611e8 {
    void clear();
    unsigned char bytes[0x48];
};

void ClearBlock_4611e8::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x7100461420
struct ClearBlock_461420 {
    void clear();
    unsigned char bytes[0xe8];
};

void ClearBlock_461420::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x7100462504
struct ClearBlock_462504 {
    void clear();
    unsigned char bytes[0x120];
};

void ClearBlock_462504::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x7100466ba8
struct ClearBlock_466ba8 {
    void clear();
    unsigned char bytes[0xd8];
};

void ClearBlock_466ba8::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x7100466cb4
struct ClearBlock_466cb4 {
    void clear();
    unsigned char bytes[0x48];
};

void ClearBlock_466cb4::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x7100466e2c
struct ClearBlock_466e2c {
    void clear();
    unsigned char bytes[0x48];
};

void ClearBlock_466e2c::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x7100466f30
struct ClearBlock_466f30 {
    void clear();
    unsigned char bytes[0x48];
};

void ClearBlock_466f30::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x71005f8fe8
struct ClearBlock_5f8fe8 {
    void clear();
    unsigned char bytes[0x2028];
};

void ClearBlock_5f8fe8::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x71005f972c
struct ClearBlock_5f972c {
    void clear();
    unsigned char bytes[0x628];
};

void ClearBlock_5f972c::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x71005f9a78
struct ClearBlock_5f9a78 {
    void clear();
    unsigned char bytes[0x58];
};

void ClearBlock_5f9a78::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x71005f9b18
struct ClearBlock_5f9b18 {
    void clear();
    unsigned char bytes[0x3018];
};

void ClearBlock_5f9b18::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x7100454b30
struct ClearBlock_454b30 {
    void clear();
    unsigned char bytes[0x1b000];
};

void ClearBlock_454b30::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}

// 0x7100454b80
struct ClearBlock_454b80 {
    void clear();
    unsigned char bytes[0x1b000];
};

void ClearBlock_454b80::clear() {
    for (unsigned int i = 0; i < sizeof(bytes); ++i)
        bytes[i] = 0;
}
