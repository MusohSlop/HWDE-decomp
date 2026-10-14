// Team list removals (0x7100167cac-0x710016814c): look up a unit's team in the global roster and
// remove the unit's id from one of the team's short lists, shifting the later entries down. Found
// by tools/family_scan.py --immediates. Names are descriptive placeholders. Status:
// matching/README.md.

struct ShortList {
    unsigned short* data;     // +00
    int capacity;             // +08
    int count;                // +0c
    unsigned char pad10[8];

    int find(unsigned short value) const {
        for (int i = 0; i < count; ++i) {
            if (data[i] == value)
                return i;
        }
        return -1;
    }
    unsigned short get(int index) const {
        return index < count ? data[index] : 0;
    }
    void set(int index, unsigned short value) {
        if (index < capacity) {
            data[index] = value;
            count = count > index ? count : index + 1;
        }
    }
    void remove(int index) {
        if (index != -1 && index < count) {
            for (; index < count - 1; ++index)
                set(index, get(index + 1));
            --count;
        }
    }
};

struct RosterUnit {
    unsigned char pad[0x44];
    unsigned int team;        // +44
    unsigned char pad48[0x118];
};

struct RosterTeam {
    unsigned char pad[0x2a8];
    ShortList lists[6];       // +2a8

};

struct Roster {
    unsigned char pad[0x278];
    RosterTeam teams[3];      // +278
    RosterUnit units[0xf6];   // +c20

    RosterUnit* unit(unsigned int id) { return id < 0xf6 ? &units[id] : nullptr; }
    RosterTeam* team(unsigned int index) { return index < 3 ? &teams[index] : nullptr; }
};

// Reached through the GOT slot at 0x7100c216e8.
extern Roster* gShop;
// 0x7100167cac
void remove_from_team_167cac(unsigned int id) {
    ShortList& list = gShop->team(gShop->unit(id)->team)->lists[2];
    list.remove(list.find(static_cast<unsigned char>(id)));
}
// 0x7100167da4
void remove_from_team_167da4(unsigned int id) {
    ShortList& list = gShop->team(gShop->unit(id)->team)->lists[3];
    list.remove(list.find(static_cast<unsigned char>(id)));
}
// 0x7100168054
void remove_from_team_168054(unsigned int id) {
    ShortList& list = gShop->team(gShop->unit(id)->team)->lists[5];
    list.remove(list.find(static_cast<unsigned char>(id)));
}
// 0x710016814c
void remove_from_team_16814c(unsigned int id) {
    ShortList& list = gShop->team(gShop->unit(id)->team)->lists[0];
    list.remove(list.find(static_cast<unsigned char>(id)));
}
