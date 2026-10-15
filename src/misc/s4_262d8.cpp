// A gauge's fill step (fourth session, 2-copy family 262d8): once the value plus the step reaches the limit, the fill
// rate is clamped to [0, max] and the overflow is kept. Gauge::fill<0> (0x71000262d8) and fill<1> (0x710002fc94).
// Names are descriptive placeholders.

extern "C" float fmaxf(float a, float b);

// Reached through the GOT slots at 0x7100c21d80 and 0x7100c21d88.
extern float gGaugeRate;
extern float gGaugeRateMax;

struct GaugeLevel {
    float pad0;
    float value;              // +04
};

class Gauge {
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
    virtual GaugeLevel* level();  // +50
    virtual void v58();
    virtual void v60();
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void v80();
    virtual void v88();
    virtual void v90();
    virtual void v98();
    virtual void va0();
    virtual void va8();
    virtual void vb0();
    virtual void vb8();
    virtual void vc0();
    virtual void vc8();
    virtual void vd0();
    virtual void vd8();
    virtual void ve0();
    virtual void ve8();
    virtual void vf0();
    virtual void vf8();
    virtual void v100();
    virtual void v108();
    virtual void v110();
    virtual void v118();
    virtual void v120();
    virtual void v128();
    virtual void v130();
    virtual void v138();
    virtual void v140();
    virtual void v148();
    virtual float limit();    // +150

    template <int Copy> void fill(float step);

    unsigned char pad8[4];
    float rate;               // +0c
    unsigned char pad10[0xc4];
    float overflow;           // +d4
    unsigned char padd8[0x28];
    bool keep_overflow;       // +100
};

template <int Copy>
void Gauge::fill(float step) {
    float next = level()->value + step;
    if (next >= limit()) {
        if (rate > 0.0f) {
            float r = fmaxf(gGaugeRate, 0.0f);
            rate = r > gGaugeRateMax ? gGaugeRateMax : r;
        }
        float lim = limit();
        if (keep_overflow) overflow = lim - step;
    }
}

// 0x71000262d8
template void Gauge::fill<0>(float);
// 0x710002fc94
template void Gauge::fill<1>(float);
