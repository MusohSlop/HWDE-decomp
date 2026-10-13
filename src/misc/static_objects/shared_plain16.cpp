// A function-local static with an empty constructor (0x710020c72c), in its own unit so that
// LLVM's global merge pass does not combine its guard with other statics (see
// misc/static_families.cpp). Names are placeholders. Status: matching/README.md.

struct Plain16 {
    Plain16() {}
    long a;
    long b;
};

// 0x710020c72c; original file: region/option settings, 0x710020c72c
Plain16* shared_plain16() {
    static Plain16 instance;
    return &instance;
}
