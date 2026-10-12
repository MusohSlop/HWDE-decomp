// Tick stopwatch (0x710045dd84-0x710045dde8).
#pragma once

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
