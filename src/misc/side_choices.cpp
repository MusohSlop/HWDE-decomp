// Side choices found by tools/family_scan.py --immediates: each sets an object's two side fields to
// the given side, or rolls each of them separately from the shared random source when the side is
// not 0 or 1. They differ only in the field offsets; types and functions are named after their
// address. Status: matching/README.md.

class RandomSource {
public:
    unsigned int roll();                                                    // 0x71003336c4
};
// Reached through the GOT slot at 0x7100c22c00.
extern RandomSource gRandomSource_c22c00;

struct Sided3005a0 {
    unsigned char pad[0x154];
    unsigned int side_b;      // +154
    unsigned int side_a;      // +158
};

// 0x71003005a0
void choose_side_3005a0(Sided3005a0* object, unsigned int side) {
    if (side <= 1) {
        object->side_a = side;
        object->side_b = side;
    } else {
        object->side_a = gRandomSource_c22c00.roll();
        object->side_b = gRandomSource_c22c00.roll();
    }
}

struct Sided31ce10 {
    unsigned char pad[0x48];
    unsigned int side_b;      // +48
    unsigned int side_a;      // +4c
};

// 0x710031ce10
void choose_side_31ce10(Sided31ce10* object, unsigned int side) {
    if (side <= 1) {
        object->side_a = side;
        object->side_b = side;
    } else {
        object->side_a = gRandomSource_c22c00.roll();
        object->side_b = gRandomSource_c22c00.roll();
    }
}

struct Sided3259e0 {
    unsigned char pad[0x48];
    unsigned int side_b;      // +48
    unsigned int side_a;      // +4c
};

// 0x71003259e0
void choose_side_3259e0(Sided3259e0* object, unsigned int side) {
    if (side <= 1) {
        object->side_a = side;
        object->side_b = side;
    } else {
        object->side_a = gRandomSource_c22c00.roll();
        object->side_b = gRandomSource_c22c00.roll();
    }
}

struct Sided32dfe4 {
    unsigned char pad[0x48];
    unsigned int side_b;      // +48
    unsigned int side_a;      // +4c
};

// 0x710032dfe4
void choose_side_32dfe4(Sided32dfe4* object, unsigned int side) {
    if (side <= 1) {
        object->side_a = side;
        object->side_b = side;
    } else {
        object->side_a = gRandomSource_c22c00.roll();
        object->side_b = gRandomSource_c22c00.roll();
    }
}

struct Sided333284 {
    unsigned char pad[0x48];
    unsigned int side_b;      // +48
    unsigned int side_a;      // +4c
};

// 0x7100333284
void choose_side_333284(Sided333284* object, unsigned int side) {
    if (side <= 1) {
        object->side_a = side;
        object->side_b = side;
    } else {
        object->side_a = gRandomSource_c22c00.roll();
        object->side_b = gRandomSource_c22c00.roll();
    }
}
