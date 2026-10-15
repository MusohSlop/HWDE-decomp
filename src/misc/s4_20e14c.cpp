// The shutdown of two global record tables (fourth session, template family 20e14c): every record is cleared and its
// id reset to -1, then the table is deleted. destroy_bgm_player (0x710020e14c, in the unit/BGM data file) and
// destroy_unit_database (0x710020ede8, in the unit database file) share one inline template; the loop works on a local
// copy of the global and the delete reads the global again. Names are descriptive placeholders.

struct TableRecord {
    int id;                   // +000
    unsigned char data[0x26c];
};

class RecordTable {
public:
    virtual ~RecordTable();
    virtual TableRecord* record(unsigned int i);   // +10
    virtual unsigned int count();                   // +18
};

class BgmPlayer : public RecordTable {};
class UnitDatabase : public RecordTable {};

// Reached through the GOT slots at 0x7100c232f0 and 0x7100c232e8.
extern BgmPlayer* gBgmPlayer;
extern UnitDatabase* gUnitDatabase;

template <class T>
static inline void destroy_table(T*& table) {
    T* t = table;
    if (!t) return;
    for (unsigned int i = 0; i < t->count(); i++) {
        TableRecord* r = t->record(i);
        __builtin_memset(r->data, 0, sizeof(r->data));
        r->id = -1;
    }
    delete table;
    table = nullptr;
}

// 0x710020e14c
void destroy_bgm_player() {
    destroy_table(gBgmPlayer);
}

// 0x710020ede8
void destroy_unit_database() {
    destroy_table(gUnitDatabase);
}
