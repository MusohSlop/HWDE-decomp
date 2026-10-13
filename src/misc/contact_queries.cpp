// Contact queries found by tools/family_scan.py: each runs one shape-pair test on the two
// bodies' shapes (+70), records the contact count and whether there was any, and on request
// resets the contacts it produced. The members differ only in the pair test they call; the
// 128-byte variant clears the "swapped" flag first and stores the found flag before the count,
// the 132-byte variant sets it and stores the count first. Grouped here until their source
// files are linked; functions are named after their address. Status: matching/README.md.

struct Shape {
    unsigned char pad[0x70];
};
struct Body {
    unsigned char pad[0x70];
    Shape shape;              // +70
};

struct Contact {
    void reset();                                                           // 0x71004f4284
    unsigned char pad[0x40];
};

struct ContactSet {
    Contact contacts[4];      // +000
    int count;                // +100
    unsigned char pad104[0xc];
    unsigned char swapped;    // +110
    unsigned char found;      // +111
};

long contact_test_4e3768(ContactSet* set, Shape* a, Shape* b);                                 // 0x71004e3768

// 0x7100499380
long query_contacts_499380(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_4e3768(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_511a8c(ContactSet* set, Shape* a, Shape* b);                                 // 0x7100511a8c

// 0x7100499400
long query_contacts_499400(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_511a8c(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_50f96c(ContactSet* set, Shape* a, Shape* b);                                 // 0x710050f96c

// 0x7100499480
long query_contacts_499480(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_50f96c(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_50fe68(ContactSet* set, Shape* a, Shape* b);                                 // 0x710050fe68

// 0x7100499500
long query_contacts_499500(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_50fe68(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_513ef8(ContactSet* set, Shape* a, Shape* b);                                 // 0x7100513ef8

// 0x7100499580
long query_contacts_499580(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_513ef8(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_50303c(ContactSet* set, Shape* a, Shape* b);                                 // 0x710050303c

// 0x7100499600
long query_contacts_499600(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_50303c(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_511bd8(ContactSet* set, Shape* a, Shape* b);                                 // 0x7100511bd8

// 0x7100499788
long query_contacts_499788(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_511bd8(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_511d24(ContactSet* set, Shape* a, Shape* b);                                 // 0x7100511d24

// 0x7100499808
long query_contacts_499808(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_511d24(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_511e88(ContactSet* set, Shape* a, Shape* b);                                 // 0x7100511e88

// 0x7100499888
long query_contacts_499888(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_511e88(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_514044(ContactSet* set, Shape* a, Shape* b);                                 // 0x7100514044

// 0x7100499908
long query_contacts_499908(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_514044(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_503608(ContactSet* set, Shape* a, Shape* b);                                 // 0x7100503608

// 0x7100499988
long query_contacts_499988(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_503608(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_50fab8(ContactSet* set, Shape* a, Shape* b);                                 // 0x710050fab8

// 0x7100499b10
long query_contacts_499b10(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_50fab8(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_50fc88(ContactSet* set, Shape* a, Shape* b);                                 // 0x710050fc88

// 0x7100499b90
long query_contacts_499b90(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_50fc88(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_514190(ContactSet* set, Shape* a, Shape* b);                                 // 0x7100514190

// 0x7100499c10
long query_contacts_499c10(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_514190(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_503bcc(ContactSet* set, Shape* a, Shape* b);                                 // 0x7100503bcc

// 0x7100499c90
long query_contacts_499c90(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_503bcc(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_50ffdc(ContactSet* set, Shape* a, Shape* b);                                 // 0x710050ffdc

// 0x7100499e18
long query_contacts_499e18(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_50ffdc(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_5142dc(ContactSet* set, Shape* a, Shape* b);                                 // 0x71005142dc

// 0x7100499e98
long query_contacts_499e98(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_5142dc(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_504184(ContactSet* set, Shape* a, Shape* b);                                 // 0x7100504184

// 0x7100499f18
long query_contacts_499f18(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_504184(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_514428(ContactSet* set, Shape* a, Shape* b);                                 // 0x7100514428

// 0x710049a0a0
long query_contacts_49a0a0(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_514428(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_50473c(ContactSet* set, Shape* a, Shape* b);                                 // 0x710050473c

// 0x710049a120
long query_contacts_49a120(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_50473c(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_504d6c(ContactSet* set, Shape* a, Shape* b);                                 // 0x7100504d6c

// 0x710049a2a8
long query_contacts_49a2a8(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 0;
    long count = contact_test_504d6c(set, &a->shape, &b->shape);
    set->found = count != 0;
    set->count = count;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_4e7cf0(ContactSet* set, Shape* a, Shape* b);                                 // 0x71004e7cf0

// 0x7100499680
long query_contacts_499680(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 1;
    long count = contact_test_4e7cf0(set, &a->shape, &b->shape);
    set->count = count;
    set->found = count != 0;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_4f97d8(ContactSet* set, Shape* a, Shape* b);                                 // 0x71004f97d8

// 0x7100499704
long query_contacts_499704(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 1;
    long count = contact_test_4f97d8(set, &a->shape, &b->shape);
    set->count = count;
    set->found = count != 0;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_4e7e5c(ContactSet* set, Shape* a, Shape* b);                                 // 0x71004e7e5c

// 0x7100499a08
long query_contacts_499a08(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 1;
    long count = contact_test_4e7e5c(set, &a->shape, &b->shape);
    set->count = count;
    set->found = count != 0;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_4f9a98(ContactSet* set, Shape* a, Shape* b);                                 // 0x71004f9a98

// 0x7100499a8c
long query_contacts_499a8c(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 1;
    long count = contact_test_4f9a98(set, &a->shape, &b->shape);
    set->count = count;
    set->found = count != 0;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_4e7fac(ContactSet* set, Shape* a, Shape* b);                                 // 0x71004e7fac

// 0x7100499d10
long query_contacts_499d10(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 1;
    long count = contact_test_4e7fac(set, &a->shape, &b->shape);
    set->count = count;
    set->found = count != 0;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_4f9d68(ContactSet* set, Shape* a, Shape* b);                                 // 0x71004f9d68

// 0x7100499d94
long query_contacts_499d94(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 1;
    long count = contact_test_4f9d68(set, &a->shape, &b->shape);
    set->count = count;
    set->found = count != 0;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_4e8108(ContactSet* set, Shape* a, Shape* b);                                 // 0x71004e8108

// 0x7100499f98
long query_contacts_499f98(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 1;
    long count = contact_test_4e8108(set, &a->shape, &b->shape);
    set->count = count;
    set->found = count != 0;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_4f9c14(ContactSet* set, Shape* a, Shape* b);                                 // 0x71004f9c14

// 0x710049a01c
long query_contacts_49a01c(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 1;
    long count = contact_test_4f9c14(set, &a->shape, &b->shape);
    set->count = count;
    set->found = count != 0;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_4e8264(ContactSet* set, Shape* a, Shape* b);                                 // 0x71004e8264

// 0x710049a1a0
long query_contacts_49a1a0(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 1;
    long count = contact_test_4e8264(set, &a->shape, &b->shape);
    set->count = count;
    set->found = count != 0;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_4fa028(ContactSet* set, Shape* a, Shape* b);                                 // 0x71004fa028

// 0x710049a224
long query_contacts_49a224(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 1;
    long count = contact_test_4fa028(set, &a->shape, &b->shape);
    set->count = count;
    set->found = count != 0;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_4e83b4(ContactSet* set, Shape* a, Shape* b);                                 // 0x71004e83b4

// 0x710049a328
long query_contacts_49a328(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 1;
    long count = contact_test_4e83b4(set, &a->shape, &b->shape);
    set->count = count;
    set->found = count != 0;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_4fa2ec(ContactSet* set, Shape* a, Shape* b);                                 // 0x71004fa2ec

// 0x710049a3ac
long query_contacts_49a3ac(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 1;
    long count = contact_test_4fa2ec(set, &a->shape, &b->shape);
    set->count = count;
    set->found = count != 0;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}

long contact_test_4fa55c(ContactSet* set, Shape* a, Shape* b);                                 // 0x71004fa55c

// 0x710049a430
long query_contacts_49a430(ContactSet* set, Body* a, Body* b, unsigned char reset) {
    set->swapped = 1;
    long count = contact_test_4fa55c(set, &a->shape, &b->shape);
    set->count = count;
    set->found = count != 0;
    if (reset && static_cast<int>(count) >= 1) {
        for (long i = 0; i < set->count; ++i)
            set->contacts[i].reset();
    }
    return count;
}
