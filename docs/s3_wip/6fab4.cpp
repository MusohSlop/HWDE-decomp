// WIP (third session): 6fab4/6fbbc (84 B each, s4's second list), 2 words off: the or of the first two flags and
// the add of the third take their operands the other way round (orr w8, w9, w8 / add w8, w8, w9 in the original).
// Tried: all 24 term orders (abcd best), locals in each load order, parenthesisations, if statements, an
// accumulator, an unsigned char result, multiplies. Maps: gOption_c2ed98..c2edec at their addresses (direct).

extern bool gOption_c2ed98 __attribute__((visibility("hidden")));   // 0x7100c2ed98
extern bool gOption_c2ed9c __attribute__((visibility("hidden")));   // 0x7100c2ed9c
extern bool gOption_c2eda8 __attribute__((visibility("hidden")));   // 0x7100c2eda8
extern bool gOption_c2edac __attribute__((visibility("hidden")));   // 0x7100c2edac
extern bool gOption_c2edc0 __attribute__((visibility("hidden")));   // 0x7100c2edc0
extern bool gOption_c2edc4 __attribute__((visibility("hidden")));   // 0x7100c2edc4
extern bool gOption_c2ede8 __attribute__((visibility("hidden")));   // 0x7100c2ede8
extern bool gOption_c2edec __attribute__((visibility("hidden")));   // 0x7100c2edec

template <int Copy>
int option_mask() {
    if (Copy == 0)
        return (gOption_c2ed9c ? 0xe : 0) + gOption_c2edac + (gOption_c2edc4 ? 0x78 : 0) + (gOption_c2edec ? 0xd : 0);
    return (gOption_c2ed98 ? 0xe : 0) + gOption_c2eda8 + (gOption_c2edc0 ? 0x78 : 0) + (gOption_c2ede8 ? 0xd : 0);
}

template int option_mask<0>();   // 0x710006fab4
template int option_mask<1>();   // 0x710006fbbc
