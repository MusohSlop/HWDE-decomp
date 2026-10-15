// An actor's placement (fourth session, template family 137730): Placer::place<Rule> takes the actor's place entry and,
// when the rule accepts it, places the actor at the entry, at the grid cell found for it, or where it stands; a rejected
// entry resets the actor and places it with a fallback height. Two rules: place<PlaceRuleA> (0x7100137730) and
// place<PlaceRuleB> (0x710013789c). The cell's area goes through its own local, so the actor's own area is passed on
// without a store. Names are descriptive placeholders.

struct Vec4 {
    float x, y, z, w;
};

struct PlaceEntry {
    Vec4 pos;                 // +000
    unsigned char pad10[0xf7];
    unsigned char area;       // +107
    unsigned char pad108[0x18];
};

struct PlaceGrid {
    unsigned char find(Vec4* out, PlaceEntry* entry, int area);             // 0x7100153cf4
    void cell(int* area, int* index, Vec4* pos);                            // 0x710014a8f0
};

struct PlaceTable {
    PlaceEntry entries[0x284];  // +0
    unsigned char pad2d480[0x1e0];
    PlaceGrid grid;           // +2d660
};
// Reached through the GOT slot at 0x7100c22bd8.
extern PlaceTable* gPlaceTable;

unsigned char area_has_grid(int area);                                      // 0x7100148fd8

struct Actor {
    Vec4 pos;                 // +00
    unsigned char pad10[0x40];
    float height;             // +50
    unsigned char pad54[0x18];
    unsigned int place;       // +6c
    unsigned char pad70[0x19];
    unsigned char flags;      // +89: bit 3 placed
    unsigned char pad8a[0x7d];
    unsigned char area;       // +107
};
struct PlaceRuleA {
    static unsigned char valid(Actor* a, PlaceEntry* e);                    // 0x7100135698
};
struct PlaceRuleB {
    static unsigned char valid(Actor* a, PlaceEntry* e);                    // 0x7100135748
};
void set_actor_state(Actor* a, int state);                                  // 0x71001349c0
void place_actor(Actor* a, Vec4* pos, int area, float height);              // 0x7100133158

class Placer {
public:
    template <class Rule> void place();
    float fallback_height();                                                // 0x7100136cf0

    Actor* actor;
};

template <class Rule>
void Placer::place() {
    Actor* a = actor;
    if (a->flags & 8) {
        set_actor_state(a, 0);
        return;
    }
    PlaceTable* t = gPlaceTable;
    PlaceEntry* e = &t->entries[a->place];
    if (!Rule::valid(a, e)) {
        set_actor_state(actor, 0);
        float h = fallback_height();
        place_actor(actor, &actor->pos, actor->area, h);
        return;
    }
    Vec4 pos;
    pos.w = 1.0f;
    int area;
    if (!area_has_grid(e->area)) {
        pos = e->pos;
        area = e->area;
    } else {
        PlaceGrid* g = &gPlaceTable->grid;
        if (!g->find(&pos, e, e->area)) {
            pos = actor->pos;
            area = actor->area;
        } else {
            int cell_area, index;
            g->cell(&cell_area, &index, &pos);
            area = cell_area;
        }
    }
    place_actor(actor, &pos, area, actor->height);
}

template void Placer::place<PlaceRuleA>();
template void Placer::place<PlaceRuleB>();
