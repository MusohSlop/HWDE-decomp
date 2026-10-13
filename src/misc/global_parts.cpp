// Calls on parts of a large global found by tools/family_scan.py --immediates: each passes one part
// of the global object at 0x7100c21690 and its argument to the part's handler. They differ only in
// the part and the handler; functions are named after their address. Status: matching/README.md.

// Reached through the GOT slot at 0x7100c21690.
extern unsigned char* gGlobal_c21690;

void part_call_f08(void* part, int value);                                       // 0x7100000f08

// 0x7100001088: part at +1249c0
void global_part_1088(int value) {
    part_call_f08(gGlobal_c21690 + 0x1249c0, value);
}

void part_call_381e4(void* part, int value);                                     // 0x71000381e4

// 0x710003d888: part at +eaf80
void global_part_3d888(int value) {
    part_call_381e4(gGlobal_c21690 + 0xeaf80, value);
}

void part_call_39f88(void* part, int value);                                     // 0x7100039f88

// 0x710003d8ac: part at +eaf80
void global_part_3d8ac(int value) {
    part_call_39f88(gGlobal_c21690 + 0xeaf80, value);
}

void part_call_37fb4(void* part, int value);                                     // 0x7100037fb4

// 0x710003d8d0: part at +eaf80
void global_part_3d8d0(int value) {
    part_call_37fb4(gGlobal_c21690 + 0xeaf80, value);
}

void part_call_48ff4(void* part, int value);                                     // 0x7100048ff4

// 0x7100040cd0: part at +72930
void global_part_40cd0(int value) {
    part_call_48ff4(gGlobal_c21690 + 0x72930, value);
}
