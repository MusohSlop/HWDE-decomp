// A registry lookup by id (fourth session, 2-copy family 4b76c): walks the used entries, skipping free ones (negative
// id), and returns the found entry's target object. The loop keeps clang's cleanup-destination switch (continue 4,
// return 1, fall-through 0) as a three-valued phi, from the entry pointer declared in the loop body. Registry::find<0>
// (0x710004b76c) and find<1> (0x7100075fd8). Names are descriptive placeholders.

struct RegistryObject;
struct RegistryTarget {
    RegistryObject* object;   // +00
};
struct RegistryEntry {
    RegistryTarget* target;   // +00
    int id;                   // +08
};

class Registry {
public:
    template <int Copy> RegistryObject* find(int id);

    RegistryEntry* entry(int id) {
        unsigned int seen = 0;
        for (unsigned long i = 0; i < capacity; i++) {
            if (seen >= used) return 0;
            RegistryEntry* e = entries[i];
            if (e->id < 0) continue;
            seen++;
            if (e->id == id) return e;
        }
        return 0;
    }

    void* vtable;
    RegistryEntry** entries;  // +08
    unsigned short capacity;  // +10
    unsigned short used;      // +12
};

template <int Copy>
RegistryObject* Registry::find(int id) {
    RegistryEntry* e = entry(id);
    if (!e) return 0;
    RegistryTarget* t = e->target;
    if (!t) return 0;
    return t->object;
}

// 0x710004b76c
template RegistryObject* Registry::find<0>(int);
// 0x7100075fd8
template RegistryObject* Registry::find<1>(int);
