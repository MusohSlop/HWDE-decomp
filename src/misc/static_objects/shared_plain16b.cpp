// A function-local static with an empty constructor (0x710019d1a4), in its own unit for the same
// reason as shared_plain16.cpp. Names are placeholders. Status: matching/README.md.

struct Plain16b {
    Plain16b() {}
    long a;
    long b;
};

// 0x710019d1a4; original file: battle objects, 0x710019d1a4
Plain16b* shared_plain16b() {
    static Plain16b instance;
    return &instance;
}
