// Two calls through the same code remap (fourth session, template family c554): codes 43 and 108 become 0x20, 90 becomes
// 0x1c and 104 to 123 become a block of other codes; others pass unchanged. remapped_c554 (0x710000c554) and
// remapped_c624 (0x710000c624) hand the result to two different functions; their jump tables follow each other in
// .rodata. Names are descriptive placeholders.

int callee_241b90(int code);                                                // 0x7100241b90
int callee_241ba8(int code);                                                // 0x7100241ba8

static inline int remap_code(int code) {
    switch (code) {
    case 43:
    case 108: return 0x20;
    case 90: return 0x1c;
    case 104: return 0x1b;
    case 105: return 0x1d;
    case 106: return 0x1e;
    case 107: return 0x1f;
    case 109: return 0x3e;
    case 110: return 0x3f;
    case 111: return 0x40;
    case 112: return 0x41;
    case 113: return 0x42;
    case 114: return 0x43;
    case 115: return 0x44;
    case 116: return 0x45;
    case 117: return 0x46;
    case 118: return 0x47;
    case 119: return 0x48;
    case 120: return 0x49;
    case 121: return 0x4a;
    case 122: return 0x4b;
    case 123: return 0x3b;
    default: return code;
    }
}

// 0x710000c554
int remapped_c554(int code) {
    return callee_241b90(remap_code(code));
}

// 0x710000c624
int remapped_c624(int code) {
    return callee_241ba8(remap_code(code));
}
