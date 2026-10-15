// A material's stat curves (fourth session, template family 1fc968): curve_at<C> interpolates a stat linearly between its
// values at levels 1, 99, 150, 200 and 255, each band starting from the value at the level below it (the call for level 98
// inlines, the clamp to 254 becomes a loop). Two curves of the same entry use it: curve_at<CurveA> (0x71001fc968) and
// curve_at<CurveB> (0x71001fcb28). Names are descriptive placeholders.

class MaterialEntry {
public:
    int stat_a1();                                                          // 0x71001ff92c
    int stat_a99();                                                         // 0x71001ff934
    int stat_a150();                                                        // 0x71001ff9b8
    int stat_a200();                                                        // 0x71001ff9c0
    int stat_a255();                                                        // 0x71001ff9c8
    int stat_b1();                                                          // 0x71001ff93c
    int stat_b99();                                                         // 0x71001ff944
    int stat_b150();                                                        // 0x71001ff9d0
    int stat_b200();                                                        // 0x71001ff9d8
    int stat_b255();                                                        // 0x71001ff9e0
};
class MaterialBook {
public:
    MaterialEntry* entry(int id);                                           // 0x71002015a8
};
MaterialBook* get_material_book();                                          // 0x7100200fc0

struct CurveA {
    static int at1(MaterialEntry* r) { return r->stat_a1(); }
    static int at99(MaterialEntry* r) { return r->stat_a99(); }
    static int at150(MaterialEntry* r) { return r->stat_a150(); }
    static int at200(MaterialEntry* r) { return r->stat_a200(); }
    static int at255(MaterialEntry* r) { return r->stat_a255(); }
};
struct CurveB {
    static int at1(MaterialEntry* r) { return r->stat_b1(); }
    static int at99(MaterialEntry* r) { return r->stat_b99(); }
    static int at150(MaterialEntry* r) { return r->stat_b150(); }
    static int at200(MaterialEntry* r) { return r->stat_b200(); }
    static int at255(MaterialEntry* r) { return r->stat_b255(); }
};

template <class C>
int curve_at(int id, unsigned int level) {
    MaterialEntry* r = get_material_book()->entry(id);
    if (!r) return 0;
    if (level <= 98) return C::at1(r) + (C::at99(r) - C::at1(r)) * level / 98;
    if (level <= 149) return curve_at<C>(id, 98) + (C::at150(r) - C::at99(r)) * (level - 98) / 51;
    if (level <= 199) return curve_at<C>(id, 149) + (C::at200(r) - C::at150(r)) * (level - 149) / 50;
    if (level > 254) return curve_at<C>(id, 254);
    return curve_at<C>(id, 199) + (C::at255(r) - C::at200(r)) * (level - 199) / 55;
}

template int curve_at<CurveA>(int, unsigned int);
template int curve_at<CurveB>(int, unsigned int);
