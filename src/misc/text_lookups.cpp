// Message-text lookups found by tools/family_scan.py --immediates: each maps an id range onto
// the text database's third table (+88) by adding a fixed offset, and gives the empty string for
// ids out of range or before the database is loaded (the same shape as message_text in
// misc/accessors.cpp). They differ only in the offset; functions are named after their address.
// Status: matching/README.md.

class TextTable {
public:
    const char* find(int id, int a);                                        // 0x7100218d18
    unsigned char pad[0x20];
};

struct TextDatabase {
    unsigned char loaded;     // +00
    unsigned char pad1[0x87];
    TextTable extra;          // +88
};
// Reached through the GOT slot at 0x7100c233a0.
extern TextDatabase gTextDatabase;
extern const char kEmptyText[] __attribute__((visibility("hidden")));     // 0x7100740512

// 0x7100218040: ids from -0x1194
const char* extra_text_218040(int id) {
    unsigned int index = id + 0x1194;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x710021807c: ids from -0x125c
const char* extra_text_21807c(int id) {
    unsigned int index = id + 0x125c;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x71002180b8: ids from -0x1338
const char* extra_text_2180b8(int id) {
    unsigned int index = id + 0x1338;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x71002180f4: ids from -0x13b8
const char* extra_text_2180f4(int id) {
    unsigned int index = id + 0x13b8;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x71002181bc: ids from -0x1479
const char* extra_text_2181bc(int id) {
    unsigned int index = id + 0x1479;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x7100218454: ids from -0x2009
const char* extra_text_218454(int id) {
    unsigned int index = id + 0x2009;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x71002184d4: ids from -0x2fe6
const char* extra_text_2184d4(int id) {
    unsigned int index = id + 0x2fe6;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x7100218510: ids from -0x26fc
const char* extra_text_218510(int id) {
    unsigned int index = id + 0x26fc;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x710021854c: ids from -0x2da2
const char* extra_text_21854c(int id) {
    unsigned int index = id + 0x2da2;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x7100218588: ids from -0x2dfc
const char* extra_text_218588(int id) {
    unsigned int index = id + 0x2dfc;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x71002185c4: ids from -0x2c76
const char* extra_text_2185c4(int id) {
    unsigned int index = id + 0x2c76;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x7100218600: ids from -0x279a
const char* extra_text_218600(int id) {
    unsigned int index = id + 0x279a;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x710021863c: ids from -0x27da
const char* extra_text_21863c(int id) {
    unsigned int index = id + 0x27da;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x7100218678: ids from -0x277c
const char* extra_text_218678(int id) {
    unsigned int index = id + 0x277c;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x71002186b4: ids from -0x250d
const char* extra_text_2186b4(int id) {
    unsigned int index = id + 0x250d;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x7100218724: ids from -0x2790
const char* extra_text_218724(int id) {
    unsigned int index = id + 0x2790;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x7100218760: ids from -0x2795
const char* extra_text_218760(int id) {
    unsigned int index = id + 0x2795;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x710021879c: ids from -0x24b9
const char* extra_text_21879c(int id) {
    unsigned int index = id + 0x24b9;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x71002187d8: ids from -0x24cf
const char* extra_text_2187d8(int id) {
    unsigned int index = id + 0x24cf;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x7100218850: ids from -0x3176
const char* extra_text_218850(int id) {
    unsigned int index = id + 0x3176;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x710021888c: ids from -0x323e
const char* extra_text_21888c(int id) {
    unsigned int index = id + 0x323e;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x71002188c8: ids from -0x3252
const char* extra_text_2188c8(int id) {
    unsigned int index = id + 0x3252;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x7100218904: ids from -0x3342
const char* extra_text_218904(int id) {
    unsigned int index = id + 0x3342;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x7100218940: ids from -0x3441
const char* extra_text_218940(int id) {
    unsigned int index = id + 0x3441;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x710021897c: ids from -0x34a5
const char* extra_text_21897c(int id) {
    unsigned int index = id + 0x34a5;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x71002189b8: ids from -0x3509
const char* extra_text_2189b8(int id) {
    unsigned int index = id + 0x3509;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}

// 0x71002189f4: ids from -0x350e
const char* extra_text_2189f4(int id) {
    unsigned int index = id + 0x350e;
    if (index <= 0x363e && gTextDatabase.loaded)
        return gTextDatabase.extra.find(index, 0);
    return kEmptyText;
}
