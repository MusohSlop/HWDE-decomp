// Part-binding sequences found by tools/family_scan.py --immediates: each binds a model's five
// parts to the context in order, each starting after the previous parts' counts, the last with the
// argument's mask. They differ only in which count (the per-part count slot) they use; functions are
// named after their address. Status: matching/README.md.

struct BindPart {
    unsigned char pad[0x58];
    unsigned int counts[8];   // +58
};
struct BindContext;
struct BindMask {
    unsigned char pad[0x70];
    long mask;                // +70
};
struct BindArgs {
    unsigned char pad[0x20];
    BindMask* mask;           // +20
};

struct PartSet {
    unsigned char pad[0x68];
    BindPart* parts[4];       // +68
    BindPart* last;           // +88
};

unsigned char bind_part_59c560(BindContext* context, BindPart* part, unsigned int start, long mask); // 0x710059c560

// 0x7100598fa0: count slot 0
bool bind_parts_598fa0(PartSet* set, BindContext* context, BindArgs* args) {
    BindPart* first = set->parts[0];
    BindPart* second = set->parts[1];
    BindPart* third = set->parts[2];
    BindPart* fourth = set->parts[3];
    BindPart* last = set->last;
    unsigned int count0 = first->counts[0];
    unsigned int count1 = second->counts[0];
    unsigned int count2 = third->counts[0];
    unsigned int count3 = fourth->counts[0];
    if (!bind_part_59c560(context, first, 0, -1))
        return false;
    if (!bind_part_59c560(context, second, count0, -1))
        return false;
    unsigned int start = count1 + count0;
    if (!bind_part_59c560(context, third, start, -1))
        return false;
    start += count2;
    if (!bind_part_59c560(context, fourth, start, -1))
        return false;
    return bind_part_59c560(context, last, start + count3, args->mask ? args->mask->mask : 0);
}

unsigned char bind_part_59c650(BindContext* context, BindPart* part, unsigned int start, long mask); // 0x710059c650

// 0x71005990ac: count slot 1
bool bind_parts_5990ac(PartSet* set, BindContext* context, BindArgs* args) {
    BindPart* first = set->parts[0];
    BindPart* second = set->parts[1];
    BindPart* third = set->parts[2];
    BindPart* fourth = set->parts[3];
    BindPart* last = set->last;
    unsigned int count0 = first->counts[1];
    unsigned int count1 = second->counts[1];
    unsigned int count2 = third->counts[1];
    unsigned int count3 = fourth->counts[1];
    if (!bind_part_59c650(context, first, 0, -1))
        return false;
    if (!bind_part_59c650(context, second, count0, -1))
        return false;
    unsigned int start = count1 + count0;
    if (!bind_part_59c650(context, third, start, -1))
        return false;
    start += count2;
    if (!bind_part_59c650(context, fourth, start, -1))
        return false;
    return bind_part_59c650(context, last, start + count3, args->mask ? args->mask->mask : 0);
}

unsigned char bind_part_59c740(BindContext* context, BindPart* part, unsigned int start, long mask); // 0x710059c740

// 0x71005991b8: count slot 2
bool bind_parts_5991b8(PartSet* set, BindContext* context, BindArgs* args) {
    BindPart* first = set->parts[0];
    BindPart* second = set->parts[1];
    BindPart* third = set->parts[2];
    BindPart* fourth = set->parts[3];
    BindPart* last = set->last;
    unsigned int count0 = first->counts[2];
    unsigned int count1 = second->counts[2];
    unsigned int count2 = third->counts[2];
    unsigned int count3 = fourth->counts[2];
    if (!bind_part_59c740(context, first, 0, -1))
        return false;
    if (!bind_part_59c740(context, second, count0, -1))
        return false;
    unsigned int start = count1 + count0;
    if (!bind_part_59c740(context, third, start, -1))
        return false;
    start += count2;
    if (!bind_part_59c740(context, fourth, start, -1))
        return false;
    return bind_part_59c740(context, last, start + count3, args->mask ? args->mask->mask : 0);
}

unsigned char bind_part_59c830(BindContext* context, BindPart* part, unsigned int start, long mask); // 0x710059c830

// 0x71005992c4: count slot 3
bool bind_parts_5992c4(PartSet* set, BindContext* context, BindArgs* args) {
    BindPart* first = set->parts[0];
    BindPart* second = set->parts[1];
    BindPart* third = set->parts[2];
    BindPart* fourth = set->parts[3];
    BindPart* last = set->last;
    unsigned int count0 = first->counts[3];
    unsigned int count1 = second->counts[3];
    unsigned int count2 = third->counts[3];
    unsigned int count3 = fourth->counts[3];
    if (!bind_part_59c830(context, first, 0, -1))
        return false;
    if (!bind_part_59c830(context, second, count0, -1))
        return false;
    unsigned int start = count1 + count0;
    if (!bind_part_59c830(context, third, start, -1))
        return false;
    start += count2;
    if (!bind_part_59c830(context, fourth, start, -1))
        return false;
    return bind_part_59c830(context, last, start + count3, args->mask ? args->mask->mask : 0);
}

unsigned char bind_part_59c920(BindContext* context, BindPart* part, unsigned int start, long mask); // 0x710059c920

// 0x71005993d0: count slot 4
bool bind_parts_5993d0(PartSet* set, BindContext* context, BindArgs* args) {
    BindPart* first = set->parts[0];
    BindPart* second = set->parts[1];
    BindPart* third = set->parts[2];
    BindPart* fourth = set->parts[3];
    BindPart* last = set->last;
    unsigned int count0 = first->counts[4];
    unsigned int count1 = second->counts[4];
    unsigned int count2 = third->counts[4];
    unsigned int count3 = fourth->counts[4];
    if (!bind_part_59c920(context, first, 0, -1))
        return false;
    if (!bind_part_59c920(context, second, count0, -1))
        return false;
    unsigned int start = count1 + count0;
    if (!bind_part_59c920(context, third, start, -1))
        return false;
    start += count2;
    if (!bind_part_59c920(context, fourth, start, -1))
        return false;
    return bind_part_59c920(context, last, start + count3, args->mask ? args->mask->mask : 0);
}

unsigned char bind_part_59ca10(BindContext* context, BindPart* part, unsigned int start, long mask); // 0x710059ca10

// 0x71005994dc: count slot 5
bool bind_parts_5994dc(PartSet* set, BindContext* context, BindArgs* args) {
    BindPart* first = set->parts[0];
    BindPart* second = set->parts[1];
    BindPart* third = set->parts[2];
    BindPart* fourth = set->parts[3];
    BindPart* last = set->last;
    unsigned int count0 = first->counts[5];
    unsigned int count1 = second->counts[5];
    unsigned int count2 = third->counts[5];
    unsigned int count3 = fourth->counts[5];
    if (!bind_part_59ca10(context, first, 0, -1))
        return false;
    if (!bind_part_59ca10(context, second, count0, -1))
        return false;
    unsigned int start = count1 + count0;
    if (!bind_part_59ca10(context, third, start, -1))
        return false;
    start += count2;
    if (!bind_part_59ca10(context, fourth, start, -1))
        return false;
    return bind_part_59ca10(context, last, start + count3, args->mask ? args->mask->mask : 0);
}
