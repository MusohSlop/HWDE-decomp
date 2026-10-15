// PARKED (7 off, polarity only): `f == 0 ? 0 : v` gives the original's schedule but csel wzr, v, eq where the original
// has csel v, wzr, ne; `f != 0 ? v : 0` lets the DAG fold the 8 and 2 terms to cset + lsl (6fc44 in tiny_shapes2.cpp
// shows the same gap). Tried: bool/char flags, casts on each term, if-accumulate, !f forms.
// Two option masks built from flag bytes in .bss (fourth session, 2-copy family 6fa00): a base byte plus a constant
// for each flag that is set. The bytes are reached directly (hidden), so each copy names its own; names are
// descriptive placeholders.

extern unsigned char gFlag_c2ed94 __attribute__((visibility("hidden")));     // 0x7100c2ed94
extern unsigned char gFlag_c2eda4 __attribute__((visibility("hidden")));     // 0x7100c2eda4
extern unsigned char gFlag_c2edb4 __attribute__((visibility("hidden")));     // 0x7100c2edb4
extern unsigned char gFlag_c2edbc __attribute__((visibility("hidden")));     // 0x7100c2edbc
extern unsigned char gFlag_c2edc8 __attribute__((visibility("hidden")));     // 0x7100c2edc8
extern unsigned char gFlag_c2edd0 __attribute__((visibility("hidden")));     // 0x7100c2edd0
extern unsigned char gFlag_c2eddc __attribute__((visibility("hidden")));     // 0x7100c2eddc
extern unsigned char gFlag_c2ede4 __attribute__((visibility("hidden")));     // 0x7100c2ede4
extern unsigned char gFlag_c2ed90 __attribute__((visibility("hidden")));     // 0x7100c2ed90
extern unsigned char gFlag_c2eda0 __attribute__((visibility("hidden")));     // 0x7100c2eda0
extern unsigned char gFlag_c2edb0 __attribute__((visibility("hidden")));     // 0x7100c2edb0
extern unsigned char gFlag_c2edb8 __attribute__((visibility("hidden")));     // 0x7100c2edb8
extern unsigned char gFlag_c2edcc __attribute__((visibility("hidden")));     // 0x7100c2edcc
extern unsigned char gFlag_c2edd4 __attribute__((visibility("hidden")));     // 0x7100c2edd4
extern unsigned char gFlag_c2edd8 __attribute__((visibility("hidden")));     // 0x7100c2edd8
extern unsigned char gFlag_c2ede0 __attribute__((visibility("hidden")));     // 0x7100c2ede0

// 0x710006fa00
int option_mask_6fa00() {
    int mask = gFlag_c2ed94;
    mask += gFlag_c2eda4 == 0 ? 0 : 0x15;
    mask += gFlag_c2edb4 == 0 ? 0 : 0x87;
    mask += gFlag_c2edbc == 0 ? 0 : 0x70;
    mask += gFlag_c2edc8 == 0 ? 0 : 0x28;
    mask += gFlag_c2edd0 == 0 ? 0 : 0x11;
    mask += gFlag_c2eddc == 0 ? 0 : 8;
    mask += gFlag_c2ede4 == 0 ? 0 : 2;
    return mask;
}

// 0x710006fb08
int option_mask_6fb08() {
    int mask = gFlag_c2ed90;
    mask += gFlag_c2eda0 == 0 ? 0 : 0x15;
    mask += gFlag_c2edb0 == 0 ? 0 : 0x87;
    mask += gFlag_c2edb8 == 0 ? 0 : 0x70;
    mask += gFlag_c2edcc == 0 ? 0 : 0x28;
    mask += gFlag_c2edd4 == 0 ? 0 : 0x11;
    mask += gFlag_c2edd8 == 0 ? 0 : 8;
    mask += gFlag_c2ede0 == 0 ? 0 : 2;
    return mask;
}
