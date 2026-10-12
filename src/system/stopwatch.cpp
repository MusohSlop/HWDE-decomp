// Matching candidates for 0x710045dd2c (named-id singleton) and the stopwatch
// bodies 0x710045dd84-0x710045dde8. Status: matching/README.md.

unsigned long get_system_tick();            // 0x71006009e0 (nn::os::GetSystemTick)
unsigned long get_system_tick_frequency();  // 0x71006009f0 (nn::os::GetSystemTickFrequency)

struct NamedId {
    unsigned int id;
    const char* name;

    NamedId() : id(0), name("dummy") {}
};

NamedId* get_dummy_id() {
    static NamedId sDummy;
    return &sDummy;
}

class Stopwatch {
public:
    Stopwatch();
    void reset();
    ~Stopwatch();
    void start();
    void stop();
    unsigned int elapsed_ms() const;

private:
    unsigned long mStart;
    unsigned long mEnd;
};

Stopwatch::Stopwatch() : mStart(~0ul), mEnd(~0ul) {}

void Stopwatch::reset() {
    mStart = ~0ul;
    mEnd = ~0ul;
}

Stopwatch::~Stopwatch() {}

void Stopwatch::start() {
    mStart = get_system_tick();
}

void Stopwatch::stop() {
    mEnd = get_system_tick();
}

unsigned int Stopwatch::elapsed_ms() const {
    float ticks = static_cast<float>(mEnd - mStart);
    float ticks_per_us = static_cast<float>(get_system_tick_frequency() / 1000000);
    return static_cast<unsigned int>(ticks / ticks_per_us / 1000.0f);
}
