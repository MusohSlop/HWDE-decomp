// Event-pool inserts found by tools/family_scan.py --immediates: each takes the first free slot
// (state above 0x16) of a 256-slot pool, fills it with its own event kind, the data and the time,
// and appends it to the pool's list. They differ only in the event kind; functions are named after
// their address. Status: matching/README.md.

struct PoolNode {
    unsigned int state;       // +00
    unsigned char pad4[4];
    void* data;               // +08
    PoolNode* next;           // +10
    unsigned char pad18[8];
    float time;               // +20
    unsigned char pad24[0x7c];
};

struct PoolSlot {
    unsigned char pad[0x10];
    PoolNode node;            // +10
};
static_assert(sizeof(PoolSlot) == 0xb0, "pool slot size");

struct EventPool {
    PoolSlot slots[0x100];    // +0000
    unsigned char padb000[0x10];
    PoolNode* head;           // +b010
    PoolNode* tail;           // +b018
    unsigned char busy;       // +b020
};

static inline bool pool_add(EventPool* pool, unsigned int kind, void* data, float time) {
    if (pool->busy)
        return false;
    for (unsigned long i = 0; i < 0x100; ++i) {
        PoolNode* node = &pool->slots[i].node;
        if (node->state > 0x16) {
            node->state = kind;
            node->data = data;
            node->time = time;
            if (pool->head)
                pool->tail->next = node;
            else
                pool->head = node;
            node->next = nullptr;
            pool->tail = node;
            return true;
        }
    }
    return false;
}

// 0x71002407b8: kind 0xb
bool pool_add_2407b8(EventPool* pool, void* data, float time) {
    return pool_add(pool, 0xb, data, time);
}

// 0x7100240928: kind 0xd
bool pool_add_240928(EventPool* pool, void* data, float time) {
    return pool_add(pool, 0xd, data, time);
}

// 0x7100240c08: kind 0x11
bool pool_add_240c08(EventPool* pool, void* data, float time) {
    return pool_add(pool, 0x11, data, time);
}

// 0x7100240cc0: kind 0x12
bool pool_add_240cc0(EventPool* pool, void* data, float time) {
    return pool_add(pool, 0x12, data, time);
}

// 0x7100240d78: kind 0x13
bool pool_add_240d78(EventPool* pool, void* data, float time) {
    return pool_add(pool, 0x13, data, time);
}

// 0x7100240e30: kind 0x14
bool pool_add_240e30(EventPool* pool, void* data, float time) {
    return pool_add(pool, 0x14, data, time);
}

// 0x7100240ee8: kind 0x15
bool pool_add_240ee8(EventPool* pool, void* data, float time) {
    return pool_add(pool, 0x15, data, time);
}

// 0x7100240fa0: kind 0x16
bool pool_add_240fa0(EventPool* pool, void* data, float time) {
    return pool_add(pool, 0x16, data, time);
}
