// Destructor bodies reached through a secondary base whose first part sits at the base itself (the
// shape of misc/base_teardowns.cpp), found by scanning for the same instruction pattern: each tears
// down the object's member parts and its primary base, given the address of the secondary base (the
// deleting forms then return the object to the default heap). Functions are named after their
// address. Status: matching/README.md.

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

// 0x7100025db0: secondary base at +7e0
void destroy_from_base_25db0(unsigned char* base) {
    unsigned char* object = base - 0x7e0;
    destroy_part_c0920(base);
    destroy_part_bf6cc(base - 0x570);
    destroy_part_b8ab0(object);
}

// 0x7100025de0: secondary base at +7e0
void delete_from_base_25de0(unsigned char* base) {
    unsigned char* object = base - 0x7e0;
    destroy_part_c0920(base);
    destroy_part_bf6cc(base - 0x570);
    destroy_part_b8ab0(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x7100029bd8: secondary base at +150
void destroy_from_base_29bd8(unsigned char* base) {
    unsigned char* object = base - 0x150;
    destroy_part_d3428(base);
    destroy_part_d2534(base - 0x10);
    destroy_part_cfe84(base - 0x40);
    destroy_part_cf5bc(base - 0x68);
    destroy_part_cdf04(object);
}

// 0x7100029c18: secondary base at +150
void delete_from_base_29c18(unsigned char* base) {
    unsigned char* object = base - 0x150;
    destroy_part_d3428(base);
    destroy_part_d2534(base - 0x10);
    destroy_part_cfe84(base - 0x40);
    destroy_part_cf5bc(base - 0x68);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x710002b4dc: secondary base at +140
void destroy_from_base_2b4dc(unsigned char* base) {
    unsigned char* object = base - 0x140;
    destroy_part_d3428(base);
    destroy_part_d2534(base - 0x10);
    destroy_part_cfe84(base - 0x40);
    destroy_part_cf58c(base - 0x58);
    destroy_part_cdf04(object);
}

// 0x710002b51c: secondary base at +140
void delete_from_base_2b51c(unsigned char* base) {
    unsigned char* object = base - 0x140;
    destroy_part_d3428(base);
    destroy_part_d2534(base - 0x10);
    destroy_part_cfe84(base - 0x40);
    destroy_part_cf58c(base - 0x58);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}

// 0x71000c95b0: secondary base at +140
void destroy_from_base_c95b0(unsigned char* base) {
    unsigned char* object = base - 0x140;
    destroy_part_d3410(base);
    destroy_part_d2534(base - 0x10);
    destroy_part_cfe84(base - 0x40);
    destroy_part_cf58c(base - 0x58);
    destroy_part_cdf04(object);
}

// 0x71000c995c: secondary base at +140
void delete_from_base_c995c(unsigned char* base) {
    unsigned char* object = base - 0x140;
    destroy_part_d3410(base);
    destroy_part_d2534(base - 0x10);
    destroy_part_cfe84(base - 0x40);
    destroy_part_cf58c(base - 0x58);
    destroy_part_cdf04(object);
    get_default_heap()->release(object, 1, 0);
}
