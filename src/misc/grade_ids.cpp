// Grade-table ids found by tools/family_scan.py --immediates: each reads one id from a row of the
// table singleton (32 regular rows, row 100 is the extra row after them), checking the column and the
// id's range. They differ only in the column group, its size and the id limit; functions are named
// after their address. Status: matching/README.md.

struct GradeRow {
    short head[3];
    short group_a[3];         // +06
    short pad0c[7];
    short group_b[4];         // +1a
    short group_c[4];         // +22
    short group_d[7];         // +2a
};
static_assert(sizeof(GradeRow) == 0x38, "grade row size");
struct GradeTable {
    GradeRow rows[0x20];
    GradeRow extra;           // +700: row 100
};
// Reached through the GOT slot at 0x7100c23318.
extern GradeTable* gSingleton_c23318;

static inline int checked_grade(short id, int limit) {
    return static_cast<unsigned short>(id) < limit ? id : -1;
}

// 0x710020f978: group_a, ids below 0x12c
int grade_id_20f978(unsigned int row, unsigned int column) {
    GradeTable* table = gSingleton_c23318;
    if (!table)
        return -1;
    if (row <= 0x1f && column <= 2)
        return checked_grade(table->rows[row].group_a[column], 0x12c);
    if (row == 100)
        return checked_grade(table->extra.group_a[column], 0x12c);
    return -1;
}

// 0x710020faa8: group_b, ids below 0x3c
int grade_id_20faa8(unsigned int row, unsigned int column) {
    GradeTable* table = gSingleton_c23318;
    if (!table)
        return -1;
    if (row <= 0x1f && column <= 3)
        return checked_grade(table->rows[row].group_b[column], 0x3c);
    if (row == 100)
        return checked_grade(table->extra.group_b[column], 0x3c);
    return -1;
}

// 0x710020fb0c: group_c, ids below 0x47
int grade_id_20fb0c(unsigned int row, unsigned int column) {
    GradeTable* table = gSingleton_c23318;
    if (!table)
        return -1;
    if (row <= 0x1f && column <= 3)
        return checked_grade(table->rows[row].group_c[column], 0x47);
    if (row == 100)
        return checked_grade(table->extra.group_c[column], 0x47);
    return -1;
}

// 0x710020fb70: group_d, ids below 0x46
int grade_id_20fb70(unsigned int row, unsigned int column) {
    GradeTable* table = gSingleton_c23318;
    if (!table)
        return -1;
    if (row <= 0x1f && column <= 7)
        return checked_grade(table->rows[row].group_d[column], 0x46);
    if (row == 100)
        return checked_grade(table->extra.group_d[column], 0x46);
    return -1;
}
