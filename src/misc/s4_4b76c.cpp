// A registry lookup by id (fourth session, 2-copy family 4b76c): walks the used entries, skipping free ones (negative
// id), and returns the found entry's target object. The loop keeps clang's cleanup-destination switch (continue 4,
// return 1, fall-through 0) as a three-valued phi, from the entry pointer declared in the loop body. Registry::find<0>
// (0x710004b76c) and find<1> (0x7100075fd8); find_target<0> (0x710004df50) and find_target<1> (0x7100051eb0) return the
// entry's target itself. Names are descriptive placeholders.

struct RegistryObject;
struct RegistryTarget {
    RegistryObject* object;   // +00
};
struct RegistryEntry {
    RegistryTarget* target;   // +00
    int id;                   // +08
    int id2;                  // +0c
    int mode;                 // +10
};

class Registry {
public:
    template <int Copy> RegistryObject* find(int id);
    template <int Copy> RegistryTarget* find_target(int id);

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

    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void release_id(RegistryTarget* target, int id);  // +18
    virtual void release(RegistryTarget* target);  // +20

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

template <int Copy>
RegistryTarget* Registry::find_target(int id) {
    RegistryEntry* e = entry(id);
    if (!e) return 0;
    return e->target;
}

// 0x710004b76c
template RegistryObject* Registry::find<0>(int);
// 0x7100075fd8
template RegistryObject* Registry::find<1>(int);
// 0x710004df50 (2-copy family 4df50)
template RegistryTarget* Registry::find_target<0>(int);
// 0x7100051eb0
template RegistryTarget* Registry::find_target<1>(int);

// The same lookup on registries inside bigger objects, behind a limit on the field after the registry.
struct RegistryHost50c54 {
    RegistryTarget* find(int id);

    unsigned char pad0[0x620];
    Registry registry;        // +620
    unsigned int level;       // +638
};
struct RegistryHost50fb0 {
    RegistryTarget* find(int id);

    unsigned char pad0[0x640];
    Registry registry;        // +640
    unsigned int level;       // +658
};

// 0x7100050c54
RegistryTarget* RegistryHost50c54::find(int id) {
    if (level > 0x53) return 0;
    RegistryEntry* e = registry.entry(id);
    if (!e) return 0;
    return e->target;
}

// 0x7100050fb0
RegistryTarget* RegistryHost50fb0::find(int id) {
    if (level > 0x1b) return 0;
    RegistryEntry* e = registry.entry(id);
    if (!e) return 0;
    return e->target;
}
