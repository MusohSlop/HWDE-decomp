// Destructor bodies reached through a secondary base found by tools/family_scan.py --immediates:
// each tears down the object's four member parts and its primary base, given the address of the
// secondary base (the deleting forms then return the object to the default heap). They differ only
// in the secondary base's offset, the member offsets and two of the part destructors; functions are
// named after their address. Status: matching/README.md.

class DefaultHeap {
public:
    void release(void* ptr, unsigned char a, unsigned char b);              // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

void destroy_part_d3428(void* part);                // 0x71000d3428
void destroy_part_d2534(void* part);                // 0x71000d2534
void destroy_part_cfe84(void* part);                // 0x71000cfe84
void destroy_part_cf5bc(void* part);                // 0x71000cf5bc
void destroy_part_cdf04(void* part);                // 0x71000cdf04
void destroy_part_cf58c(void* part);                // 0x71000cf58c
void destroy_part_d3410(void* part);                // 0x71000d3410

// 0x71000296d8: secondary base at +120
void destroy_from_base_296d8(unsigned char* base) {
    unsigned char* object = base - 0x120;
    destroy_part_d3428(base + 0x30);
    destroy_part_d2534(base + 0x20);
    destroy_part_cfe84(base - 0x10);
    destroy_part_cf5bc(base - 0x38);
    destroy_part_cdf04(object);
}

// 0x710002971c: secondary base at +120
void delete_from_base_2971c(unsigned char* base) {
    unsigned char* object = base - 0x120;
    destroy_part_d3428(base + 0x30);
    destroy_part_d2534(base + 0x20);
    destroy_part_cfe84(base - 0x10);
    destroy_part_cf5bc(base - 0x38);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x710002981c: secondary base at +128
void destroy_from_base_2981c(unsigned char* base) {
    unsigned char* object = base - 0x128;
    destroy_part_d3428(base + 0x28);
    destroy_part_d2534(base + 0x18);
    destroy_part_cfe84(base - 0x18);
    destroy_part_cf5bc(base - 0x40);
    destroy_part_cdf04(object);
}

// 0x7100029860: secondary base at +128
void delete_from_base_29860(unsigned char* base) {
    unsigned char* object = base - 0x128;
    destroy_part_d3428(base + 0x28);
    destroy_part_d2534(base + 0x18);
    destroy_part_cfe84(base - 0x18);
    destroy_part_cf5bc(base - 0x40);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x710002990c: secondary base at +130
void destroy_from_base_2990c(unsigned char* base) {
    unsigned char* object = base - 0x130;
    destroy_part_d3428(base + 0x20);
    destroy_part_d2534(base + 0x10);
    destroy_part_cfe84(base - 0x20);
    destroy_part_cf5bc(base - 0x48);
    destroy_part_cdf04(object);
}

// 0x7100029950: secondary base at +130
void delete_from_base_29950(unsigned char* base) {
    unsigned char* object = base - 0x130;
    destroy_part_d3428(base + 0x20);
    destroy_part_d2534(base + 0x10);
    destroy_part_cfe84(base - 0x20);
    destroy_part_cf5bc(base - 0x48);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x710002afe0: secondary base at +110
void destroy_from_base_2afe0(unsigned char* base) {
    unsigned char* object = base - 0x110;
    destroy_part_d3428(base + 0x30);
    destroy_part_d2534(base + 0x20);
    destroy_part_cfe84(base - 0x10);
    destroy_part_cf58c(base - 0x28);
    destroy_part_cdf04(object);
}

// 0x710002b024: secondary base at +110
void delete_from_base_2b024(unsigned char* base) {
    unsigned char* object = base - 0x110;
    destroy_part_d3428(base + 0x30);
    destroy_part_d2534(base + 0x20);
    destroy_part_cfe84(base - 0x10);
    destroy_part_cf58c(base - 0x28);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x710002b120: secondary base at +118
void destroy_from_base_2b120(unsigned char* base) {
    unsigned char* object = base - 0x118;
    destroy_part_d3428(base + 0x28);
    destroy_part_d2534(base + 0x18);
    destroy_part_cfe84(base - 0x18);
    destroy_part_cf58c(base - 0x30);
    destroy_part_cdf04(object);
}

// 0x710002b164: secondary base at +118
void delete_from_base_2b164(unsigned char* base) {
    unsigned char* object = base - 0x118;
    destroy_part_d3428(base + 0x28);
    destroy_part_d2534(base + 0x18);
    destroy_part_cfe84(base - 0x18);
    destroy_part_cf58c(base - 0x30);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x710002b210: secondary base at +120
void destroy_from_base_2b210(unsigned char* base) {
    unsigned char* object = base - 0x120;
    destroy_part_d3428(base + 0x20);
    destroy_part_d2534(base + 0x10);
    destroy_part_cfe84(base - 0x20);
    destroy_part_cf58c(base - 0x38);
    destroy_part_cdf04(object);
}

// 0x710002b254: secondary base at +120
void delete_from_base_2b254(unsigned char* base) {
    unsigned char* object = base - 0x120;
    destroy_part_d3428(base + 0x20);
    destroy_part_d2534(base + 0x10);
    destroy_part_cfe84(base - 0x20);
    destroy_part_cf58c(base - 0x38);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000c945c: secondary base at +110
void destroy_from_base_c945c(unsigned char* base) {
    unsigned char* object = base - 0x110;
    destroy_part_d3410(base + 0x30);
    destroy_part_d2534(base + 0x20);
    destroy_part_cfe84(base - 0x10);
    destroy_part_cf58c(base - 0x28);
    destroy_part_cdf04(object);
}

// 0x71000c94a0: secondary base at +118
void destroy_from_base_c94a0(unsigned char* base) {
    unsigned char* object = base - 0x118;
    destroy_part_d3410(base + 0x28);
    destroy_part_d2534(base + 0x18);
    destroy_part_cfe84(base - 0x18);
    destroy_part_cf58c(base - 0x30);
    destroy_part_cdf04(object);
}

// 0x71000c94e4: secondary base at +120
void destroy_from_base_c94e4(unsigned char* base) {
    unsigned char* object = base - 0x120;
    destroy_part_d3410(base + 0x20);
    destroy_part_d2534(base + 0x10);
    destroy_part_cfe84(base - 0x20);
    destroy_part_cf58c(base - 0x38);
    destroy_part_cdf04(object);
}

// 0x71000c97a4: secondary base at +110
void delete_from_base_c97a4(unsigned char* base) {
    unsigned char* object = base - 0x110;
    destroy_part_d3410(base + 0x30);
    destroy_part_d2534(base + 0x20);
    destroy_part_cfe84(base - 0x10);
    destroy_part_cf58c(base - 0x28);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000c97fc: secondary base at +118
void delete_from_base_c97fc(unsigned char* base) {
    unsigned char* object = base - 0x118;
    destroy_part_d3410(base + 0x28);
    destroy_part_d2534(base + 0x18);
    destroy_part_cfe84(base - 0x18);
    destroy_part_cf58c(base - 0x30);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000c9854: secondary base at +120
void delete_from_base_c9854(unsigned char* base) {
    unsigned char* object = base - 0x120;
    destroy_part_d3410(base + 0x20);
    destroy_part_d2534(base + 0x10);
    destroy_part_cfe84(base - 0x20);
    destroy_part_cf58c(base - 0x38);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000c9c4c: secondary base at +110
void destroy_from_base_c9c4c(unsigned char* base) {
    unsigned char* object = base - 0x110;
    destroy_part_d3410(base + 0x30);
    destroy_part_d2534(base + 0x20);
    destroy_part_cfe84(base - 0x10);
    destroy_part_cf58c(base - 0x28);
    destroy_part_cdf04(object);
}

// 0x71000c9ce0: secondary base at +120
void destroy_from_base_c9ce0(unsigned char* base) {
    unsigned char* object = base - 0x120;
    destroy_part_d3410(base + 0x20);
    destroy_part_d2534(base + 0x10);
    destroy_part_cfe84(base - 0x20);
    destroy_part_cf58c(base - 0x38);
    destroy_part_cdf04(object);
}

// 0x71000c9fac: secondary base at +110
void delete_from_base_c9fac(unsigned char* base) {
    unsigned char* object = base - 0x110;
    destroy_part_d3410(base + 0x30);
    destroy_part_d2534(base + 0x20);
    destroy_part_cfe84(base - 0x10);
    destroy_part_cf58c(base - 0x28);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000ca068: secondary base at +120
void delete_from_base_ca068(unsigned char* base) {
    unsigned char* object = base - 0x120;
    destroy_part_d3410(base + 0x20);
    destroy_part_d2534(base + 0x10);
    destroy_part_cfe84(base - 0x20);
    destroy_part_cf58c(base - 0x38);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}
