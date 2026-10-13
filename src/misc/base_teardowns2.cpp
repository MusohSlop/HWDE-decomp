// More destructor bodies reached through a secondary base (the shape of misc/base_teardowns.cpp),
// found by scanning for the same instruction pattern: each tears down the object's member parts and
// its primary base, given the address of the secondary base (the deleting forms then return the
// object to the default heap). Functions are named after their address. Status: matching/README.md.

class DefaultHeap {
public:
    void release(void* ptr, unsigned char a, unsigned char b);              // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

void destroy_part_b8ab0(void* part);                                        // 0x71000b8ab0
void destroy_part_bf6cc(void* part);                                        // 0x71000bf6cc
void destroy_part_c0920(void* part);                                        // 0x71000c0920
void destroy_part_cdf04(void* part);                                        // 0x71000cdf04
void destroy_part_cf58c(void* part);                                        // 0x71000cf58c
void destroy_part_cf5bc(void* part);                                        // 0x71000cf5bc
void destroy_part_cfe84(void* part);                                        // 0x71000cfe84
void destroy_part_d2534(void* part);                                        // 0x71000d2534
void destroy_part_d3410(void* part);                                        // 0x71000d3410
void destroy_part_d3428(void* part);                                        // 0x71000d3428

// 0x7100025ba8: secondary base at +260
void destroy_from_base_25ba8(unsigned char* base) {
    unsigned char* object = base - 0x260;
    destroy_part_c0920(base + 0x580);
    destroy_part_bf6cc(base + 0x10);
    destroy_part_b8ab0(object);
}

// 0x7100025bdc: secondary base at +260
void delete_from_base_25bdc(unsigned char* base) {
    unsigned char* object = base - 0x260;
    destroy_part_c0920(base + 0x580);
    destroy_part_bf6cc(base + 0x10);
    destroy_part_b8ab0(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x7100025c58: secondary base at +270
void destroy_from_base_25c58(unsigned char* base) {
    unsigned char* object = base - 0x270;
    destroy_part_c0920(base + 0x570);
    destroy_part_bf6cc(base);
    destroy_part_b8ab0(object);
}

// 0x7100025c8c: secondary base at +270
void delete_from_base_25c8c(unsigned char* base) {
    unsigned char* object = base - 0x270;
    destroy_part_c0920(base + 0x570);
    destroy_part_bf6cc(base);
    destroy_part_b8ab0(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x7100025cfc: secondary base at +7d0
void destroy_from_base_25cfc(unsigned char* base) {
    unsigned char* object = base - 0x7d0;
    destroy_part_c0920(base + 0x10);
    destroy_part_bf6cc(base - 0x560);
    destroy_part_b8ab0(object);
}

// 0x7100025d30: secondary base at +7d0
void delete_from_base_25d30(unsigned char* base) {
    unsigned char* object = base - 0x7d0;
    destroy_part_c0920(base + 0x10);
    destroy_part_bf6cc(base - 0x560);
    destroy_part_b8ab0(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x7100029404: secondary base at +e8
void destroy_from_base_29404(unsigned char* base) {
    unsigned char* object = base - 0xe8;
    destroy_part_d3428(base + 0x68);
    destroy_part_d2534(base + 0x58);
    destroy_part_cfe84(base + 0x28);
    destroy_part_cf5bc(base);
    destroy_part_cdf04(object);
}

// 0x7100029448: secondary base at +e8
void delete_from_base_29448(unsigned char* base) {
    unsigned char* object = base - 0xe8;
    destroy_part_d3428(base + 0x68);
    destroy_part_d2534(base + 0x58);
    destroy_part_cfe84(base + 0x28);
    destroy_part_cf5bc(base);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x7100029510: secondary base at +108
void destroy_from_base_29510(unsigned char* base) {
    unsigned char* object = base - 0x108;
    destroy_part_d3428(base + 0x48);
    destroy_part_d2534(base + 0x38);
    destroy_part_cfe84(base + 0x8);
    destroy_part_cf5bc(base - 0x20);
    destroy_part_cdf04(object);
}

// 0x7100029554: secondary base at +108
void delete_from_base_29554(unsigned char* base) {
    unsigned char* object = base - 0x108;
    destroy_part_d3428(base + 0x48);
    destroy_part_d2534(base + 0x38);
    destroy_part_cfe84(base + 0x8);
    destroy_part_cf5bc(base - 0x20);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x7100029614: secondary base at +110
void destroy_from_base_29614(unsigned char* base) {
    unsigned char* object = base - 0x110;
    destroy_part_d3428(base + 0x40);
    destroy_part_d2534(base + 0x30);
    destroy_part_cfe84(base);
    destroy_part_cf5bc(base - 0x28);
    destroy_part_cdf04(object);
}

// 0x7100029658: secondary base at +110
void delete_from_base_29658(unsigned char* base) {
    unsigned char* object = base - 0x110;
    destroy_part_d3428(base + 0x40);
    destroy_part_d2534(base + 0x30);
    destroy_part_cfe84(base);
    destroy_part_cf5bc(base - 0x28);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x7100029a2c: secondary base at +140
void destroy_from_base_29a2c(unsigned char* base) {
    unsigned char* object = base - 0x140;
    destroy_part_d3428(base + 0x10);
    destroy_part_d2534(base);
    destroy_part_cfe84(base - 0x30);
    destroy_part_cf5bc(base - 0x58);
    destroy_part_cdf04(object);
}

// 0x7100029a70: secondary base at +140
void delete_from_base_29a70(unsigned char* base) {
    unsigned char* object = base - 0x140;
    destroy_part_d3428(base + 0x10);
    destroy_part_d2534(base);
    destroy_part_cfe84(base - 0x30);
    destroy_part_cf5bc(base - 0x58);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x7100029ae8: secondary base at +148
void destroy_from_base_29ae8(unsigned char* base) {
    unsigned char* object = base - 0x148;
    destroy_part_d3428(base + 0x8);
    destroy_part_d2534(base - 0x8);
    destroy_part_cfe84(base - 0x38);
    destroy_part_cf5bc(base - 0x60);
    destroy_part_cdf04(object);
}

// 0x7100029b2c: secondary base at +148
void delete_from_base_29b2c(unsigned char* base) {
    unsigned char* object = base - 0x148;
    destroy_part_d3428(base + 0x8);
    destroy_part_d2534(base - 0x8);
    destroy_part_cfe84(base - 0x38);
    destroy_part_cf5bc(base - 0x60);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x710002ac84: secondary base at +e0
void destroy_from_base_2ac84(unsigned char* base) {
    unsigned char* object = base - 0xe0;
    destroy_part_d3428(base + 0x60);
    destroy_part_d2534(base + 0x50);
    destroy_part_cfe84(base + 0x20);
    destroy_part_cf58c(base + 0x8);
    destroy_part_cdf04(object);
}

// 0x710002acc8: secondary base at +e0
void delete_from_base_2acc8(unsigned char* base) {
    unsigned char* object = base - 0xe0;
    destroy_part_d3428(base + 0x60);
    destroy_part_d2534(base + 0x50);
    destroy_part_cfe84(base + 0x20);
    destroy_part_cf58c(base + 0x8);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x710002ad20: secondary base at +e8
void destroy_from_base_2ad20(unsigned char* base) {
    unsigned char* object = base - 0xe8;
    destroy_part_d3428(base + 0x58);
    destroy_part_d2534(base + 0x48);
    destroy_part_cfe84(base + 0x18);
    destroy_part_cf58c(base);
    destroy_part_cdf04(object);
}

// 0x710002ad64: secondary base at +e8
void delete_from_base_2ad64(unsigned char* base) {
    unsigned char* object = base - 0xe8;
    destroy_part_d3428(base + 0x58);
    destroy_part_d2534(base + 0x48);
    destroy_part_cfe84(base + 0x18);
    destroy_part_cf58c(base);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x710002ae24: secondary base at +f8
void destroy_from_base_2ae24(unsigned char* base) {
    unsigned char* object = base - 0xf8;
    destroy_part_d3428(base + 0x48);
    destroy_part_d2534(base + 0x38);
    destroy_part_cfe84(base + 0x8);
    destroy_part_cf58c(base - 0x10);
    destroy_part_cdf04(object);
}

// 0x710002ae68: secondary base at +f8
void delete_from_base_2ae68(unsigned char* base) {
    unsigned char* object = base - 0xf8;
    destroy_part_d3428(base + 0x48);
    destroy_part_d2534(base + 0x38);
    destroy_part_cfe84(base + 0x8);
    destroy_part_cf58c(base - 0x10);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x710002af1c: secondary base at +100
void destroy_from_base_2af1c(unsigned char* base) {
    unsigned char* object = base - 0x100;
    destroy_part_d3428(base + 0x40);
    destroy_part_d2534(base + 0x30);
    destroy_part_cfe84(base);
    destroy_part_cf58c(base - 0x18);
    destroy_part_cdf04(object);
}

// 0x710002af60: secondary base at +100
void delete_from_base_2af60(unsigned char* base) {
    unsigned char* object = base - 0x100;
    destroy_part_d3428(base + 0x40);
    destroy_part_d2534(base + 0x30);
    destroy_part_cfe84(base);
    destroy_part_cf58c(base - 0x18);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x710002b330: secondary base at +130
void destroy_from_base_2b330(unsigned char* base) {
    unsigned char* object = base - 0x130;
    destroy_part_d3428(base + 0x10);
    destroy_part_d2534(base);
    destroy_part_cfe84(base - 0x30);
    destroy_part_cf58c(base - 0x48);
    destroy_part_cdf04(object);
}

// 0x710002b374: secondary base at +130
void delete_from_base_2b374(unsigned char* base) {
    unsigned char* object = base - 0x130;
    destroy_part_d3428(base + 0x10);
    destroy_part_d2534(base);
    destroy_part_cfe84(base - 0x30);
    destroy_part_cf58c(base - 0x48);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x710002b3ec: secondary base at +138
void destroy_from_base_2b3ec(unsigned char* base) {
    unsigned char* object = base - 0x138;
    destroy_part_d3428(base + 0x8);
    destroy_part_d2534(base - 0x8);
    destroy_part_cfe84(base - 0x38);
    destroy_part_cf58c(base - 0x50);
    destroy_part_cdf04(object);
}

// 0x710002b430: secondary base at +138
void delete_from_base_2b430(unsigned char* base) {
    unsigned char* object = base - 0x138;
    destroy_part_d3428(base + 0x8);
    destroy_part_d2534(base - 0x8);
    destroy_part_cfe84(base - 0x38);
    destroy_part_cf58c(base - 0x50);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000c934c: secondary base at +e0
void destroy_from_base_c934c(unsigned char* base) {
    unsigned char* object = base - 0xe0;
    destroy_part_d3410(base + 0x60);
    destroy_part_d2534(base + 0x50);
    destroy_part_cfe84(base + 0x20);
    destroy_part_cf58c(base + 0x8);
    destroy_part_cdf04(object);
}

// 0x71000c9390: secondary base at +e8
void destroy_from_base_c9390(unsigned char* base) {
    unsigned char* object = base - 0xe8;
    destroy_part_d3410(base + 0x58);
    destroy_part_d2534(base + 0x48);
    destroy_part_cfe84(base + 0x18);
    destroy_part_cf58c(base);
    destroy_part_cdf04(object);
}

// 0x71000c93d4: secondary base at +f8
void destroy_from_base_c93d4(unsigned char* base) {
    unsigned char* object = base - 0xf8;
    destroy_part_d3410(base + 0x48);
    destroy_part_d2534(base + 0x38);
    destroy_part_cfe84(base + 0x8);
    destroy_part_cf58c(base - 0x10);
    destroy_part_cdf04(object);
}

// 0x71000c9418: secondary base at +100
void destroy_from_base_c9418(unsigned char* base) {
    unsigned char* object = base - 0x100;
    destroy_part_d3410(base + 0x40);
    destroy_part_d2534(base + 0x30);
    destroy_part_cfe84(base);
    destroy_part_cf58c(base - 0x18);
    destroy_part_cdf04(object);
}

// 0x71000c9528: secondary base at +130
void destroy_from_base_c9528(unsigned char* base) {
    unsigned char* object = base - 0x130;
    destroy_part_d3410(base + 0x10);
    destroy_part_d2534(base);
    destroy_part_cfe84(base - 0x30);
    destroy_part_cf58c(base - 0x48);
    destroy_part_cdf04(object);
}

// 0x71000c956c: secondary base at +138
void destroy_from_base_c956c(unsigned char* base) {
    unsigned char* object = base - 0x138;
    destroy_part_d3410(base + 0x8);
    destroy_part_d2534(base - 0x8);
    destroy_part_cfe84(base - 0x38);
    destroy_part_cf58c(base - 0x50);
    destroy_part_cdf04(object);
}

// 0x71000c9644: secondary base at +e0
void delete_from_base_c9644(unsigned char* base) {
    unsigned char* object = base - 0xe0;
    destroy_part_d3410(base + 0x60);
    destroy_part_d2534(base + 0x50);
    destroy_part_cfe84(base + 0x20);
    destroy_part_cf58c(base + 0x8);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000c969c: secondary base at +e8
void delete_from_base_c969c(unsigned char* base) {
    unsigned char* object = base - 0xe8;
    destroy_part_d3410(base + 0x58);
    destroy_part_d2534(base + 0x48);
    destroy_part_cfe84(base + 0x18);
    destroy_part_cf58c(base);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000c96f4: secondary base at +f8
void delete_from_base_c96f4(unsigned char* base) {
    unsigned char* object = base - 0xf8;
    destroy_part_d3410(base + 0x48);
    destroy_part_d2534(base + 0x38);
    destroy_part_cfe84(base + 0x8);
    destroy_part_cf58c(base - 0x10);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000c974c: secondary base at +100
void delete_from_base_c974c(unsigned char* base) {
    unsigned char* object = base - 0x100;
    destroy_part_d3410(base + 0x40);
    destroy_part_d2534(base + 0x30);
    destroy_part_cfe84(base);
    destroy_part_cf58c(base - 0x18);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000c98ac: secondary base at +130
void delete_from_base_c98ac(unsigned char* base) {
    unsigned char* object = base - 0x130;
    destroy_part_d3410(base + 0x10);
    destroy_part_d2534(base);
    destroy_part_cfe84(base - 0x30);
    destroy_part_cf58c(base - 0x48);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000c9904: secondary base at +138
void delete_from_base_c9904(unsigned char* base) {
    unsigned char* object = base - 0x138;
    destroy_part_d3410(base + 0x8);
    destroy_part_d2534(base - 0x8);
    destroy_part_cfe84(base - 0x38);
    destroy_part_cf58c(base - 0x50);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000c9b3c: secondary base at +e0
void destroy_from_base_c9b3c(unsigned char* base) {
    unsigned char* object = base - 0xe0;
    destroy_part_d3410(base + 0x60);
    destroy_part_d2534(base + 0x50);
    destroy_part_cfe84(base + 0x20);
    destroy_part_cf58c(base + 0x8);
    destroy_part_cdf04(object);
}

// 0x71000c9b80: secondary base at +e8
void destroy_from_base_c9b80(unsigned char* base) {
    unsigned char* object = base - 0xe8;
    destroy_part_d3410(base + 0x58);
    destroy_part_d2534(base + 0x48);
    destroy_part_cfe84(base + 0x18);
    destroy_part_cf58c(base);
    destroy_part_cdf04(object);
}

// 0x71000c9bc4: secondary base at +f8
void destroy_from_base_c9bc4(unsigned char* base) {
    unsigned char* object = base - 0xf8;
    destroy_part_d3410(base + 0x48);
    destroy_part_d2534(base + 0x38);
    destroy_part_cfe84(base + 0x8);
    destroy_part_cf58c(base - 0x10);
    destroy_part_cdf04(object);
}

// 0x71000c9c08: secondary base at +100
void destroy_from_base_c9c08(unsigned char* base) {
    unsigned char* object = base - 0x100;
    destroy_part_d3410(base + 0x40);
    destroy_part_d2534(base + 0x30);
    destroy_part_cfe84(base);
    destroy_part_cf58c(base - 0x18);
    destroy_part_cdf04(object);
}

// 0x71000c9d24: secondary base at +130
void destroy_from_base_c9d24(unsigned char* base) {
    unsigned char* object = base - 0x130;
    destroy_part_d3410(base + 0x10);
    destroy_part_d2534(base);
    destroy_part_cfe84(base - 0x30);
    destroy_part_cf58c(base - 0x48);
    destroy_part_cdf04(object);
}

// 0x71000c9d68: secondary base at +138
void destroy_from_base_c9d68(unsigned char* base) {
    unsigned char* object = base - 0x138;
    destroy_part_d3410(base + 0x8);
    destroy_part_d2534(base - 0x8);
    destroy_part_cfe84(base - 0x38);
    destroy_part_cf58c(base - 0x50);
    destroy_part_cdf04(object);
}

// 0x71000c9e4c: secondary base at +e0
void delete_from_base_c9e4c(unsigned char* base) {
    unsigned char* object = base - 0xe0;
    destroy_part_d3410(base + 0x60);
    destroy_part_d2534(base + 0x50);
    destroy_part_cfe84(base + 0x20);
    destroy_part_cf58c(base + 0x8);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000c9ea4: secondary base at +e8
void delete_from_base_c9ea4(unsigned char* base) {
    unsigned char* object = base - 0xe8;
    destroy_part_d3410(base + 0x58);
    destroy_part_d2534(base + 0x48);
    destroy_part_cfe84(base + 0x18);
    destroy_part_cf58c(base);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000c9efc: secondary base at +f8
void delete_from_base_c9efc(unsigned char* base) {
    unsigned char* object = base - 0xf8;
    destroy_part_d3410(base + 0x48);
    destroy_part_d2534(base + 0x38);
    destroy_part_cfe84(base + 0x8);
    destroy_part_cf58c(base - 0x10);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000c9f54: secondary base at +100
void delete_from_base_c9f54(unsigned char* base) {
    unsigned char* object = base - 0x100;
    destroy_part_d3410(base + 0x40);
    destroy_part_d2534(base + 0x30);
    destroy_part_cfe84(base);
    destroy_part_cf58c(base - 0x18);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000ca0c0: secondary base at +130
void delete_from_base_ca0c0(unsigned char* base) {
    unsigned char* object = base - 0x130;
    destroy_part_d3410(base + 0x10);
    destroy_part_d2534(base);
    destroy_part_cfe84(base - 0x30);
    destroy_part_cf58c(base - 0x48);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000ca118: secondary base at +138
void delete_from_base_ca118(unsigned char* base) {
    unsigned char* object = base - 0x138;
    destroy_part_d3410(base + 0x8);
    destroy_part_d2534(base - 0x8);
    destroy_part_cfe84(base - 0x38);
    destroy_part_cf58c(base - 0x50);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}
