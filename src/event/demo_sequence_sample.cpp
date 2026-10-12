// Matching candidate for the demo sequence sampler at 0x7100217294.
// Semantics: docs/demo-sequence.md. Near miss; see matching/README.md.

struct DemoPoint {
    float time;               // +00
    float value;              // +04
    float w2, w3;             // +08
    float last_value;         // +10
    float w5, w6, w7;         // +14
};
static_assert(sizeof(DemoPoint) == 0x20, "point size");

struct DemoSequenceItem {
    void* owner;              // +00
    float header[6];          // +08: count, ?, value, lower, upper, ?
    unsigned long pad;        // +20
    DemoPoint* points;        // +28
};
static_assert(sizeof(DemoSequenceItem) == 0x30, "item size");

struct DemoSequence {
    void* owner;              // +00
    DemoSequenceItem* items;  // +08
    unsigned int count;       // +10

    float sample(unsigned int index, float time);
};

float DemoSequence::sample(unsigned int index, float time) {
    if (count <= index)
        return 0.0f;
    DemoSequenceItem* item = &items[index];
    unsigned int n = static_cast<unsigned int>(item->header[0]);
    float value;
    if (n == 0) {
        value = item->header[2];
    } else {
        unsigned int j;
        for (j = 0; j < n; ++j) {
            if (item->points[j].time > time)
                break;
        }
        if (j == 0) {
            value = item->points[0].value;
        } else if (j == n) {
            value = item->points[j - 1].last_value;
        } else {
            const DemoPoint& prev = item->points[j - 1];
            const DemoPoint& cur = item->points[j];
            float f = (time - prev.time) / (cur.time - prev.time);
            if (f < 0.0f)
                f = 0.0f;
            if (f > 1.0f)
                f = 1.0f;
            value = cur.value * f + prev.value * (1.0f - f);
        }
    }
    if (item->header[3] > value)
        value = item->header[3];
    if (value > item->header[4])
        value = item->header[4];
    return value;
}
