// PARKED 49c364 (LockedFlags::create, 592 B), 18 off: uses the polymorphic LockedFlags of src/misc/s4_spinlock.cpp
// (its constructor, LockedEntry's at 0x71004a295c, the heap and source types). Left: ours spills the user argument
// and orders the setup loop's loads differently (register allocation).

// 0x710049c364
LockedFlags* LockedFlags::create(LockedSource* source, GameHeap* heap, void* user) {
    if (!heap) heap = gObjectManager->heap;
    if (!source) return 0;
    void* mem = heap->alloc(sizeof(LockedFlags) + (source->count_49ba4c() - 1) * sizeof(LockedEntry), HeapTag(9));
    if (!mem) return 0;
    LockedFlags* obj = new (mem) LockedFlags(heap, source->count_49ba4c());
    char* data = source->data_49ba44();
    LockedSourceInfo* info = reinterpret_cast<LockedSourceInfo*>(source->data_49ba44());
    GameHeap* h = obj->heap;
    for (unsigned int i = 0; i < source->count_49ba4c(); i++) {
        if (!obj->entries[i].setup_4a35e8(data + info->offsets[i], h, user)) {
            obj->destroy();
            return 0;
        }
    }
    obj->flags &= ~0x10u;
    __sync_fetch_and_add(&obj->refcount, 1);
    SPIN_LOCK(obj->lock);
    obj->flags &= ~0x10000u;
    for (int i = 0; i < 4; i++) obj->ring[i] = 0;
    obj->count = 0;
    obj->start = 0;
    obj->extra = 0;
    obj->out_count = 0;
    for (int i = 0; i < 4; i++) obj->out[i] = 0;
    SPIN_UNLOCK(obj->lock);
    obj->finish_49c290(source->data_49ba44());
    return obj;
}