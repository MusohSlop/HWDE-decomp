float gauge_value_e69c(int id);                                             // 0x710000e69c
float gauge_add_e6a4(int id, float delta);                                  // 0x710000e6a4
void gauge_set_e6a8(int id, float value);                                   // 0x710000e6a8

struct GaugeUser {
    template <int Copy> bool spend(float amount, unsigned char refill);

    unsigned char pad0[9];
    unsigned char locked : 1;  // +09 bit 0
    unsigned char pada[0x1a];
    short gauge;              // +24
};

template <int Copy>
bool GaugeUser::spend(float amount, unsigned char refill) {
    float before = gauge_value_e69c(gauge);
    bool keep = before <= 0.0f || locked;
    int empty = gauge_add_e6a4(gauge, -amount) <= 0.0f;
    bool stop = !refill | !empty;
    if (!keep && !stop) {
        gauge_set_e6a8(gauge, 1.0f);
        empty = 0;
    }
    return empty && before > 0.0f;
}

// 0x71000272a4
template bool GaugeUser::spend<0>(float, unsigned char);
// 0x7100029174
template bool GaugeUser::spend<1>(float, unsigned char);
// 0x710002aaac
template bool GaugeUser::spend<2>(float, unsigned char);
// 0x71000caaa0
template bool GaugeUser::spend<3>(float, unsigned char);
