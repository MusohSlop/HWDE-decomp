// Slot pool resets (0x71000fc5bc, 0x71000fd1ec, 0x71002dee48): reset all 32 slots of a pool and
// clear its count. Found by tools/family_scan.py. Names are descriptive placeholders. Status:
// matching/README.md.

struct PoolSlot {
    void reset();                                                           // 0x71001f0140

    unsigned char data[0x88];
};

struct SlotPool {
    PoolSlot slots[32];       // +00
    int count;                // +1100
};
// 0x71000fc5bc
void reset_pool_fc5bc(SlotPool* pool) {
    for (int i = 0; i < 32; ++i)
        pool->slots[i].reset();
    pool->count = 0;
}
// 0x71000fd1ec
void reset_pool_fd1ec(SlotPool* pool) {
    for (int i = 0; i < 32; ++i)
        pool->slots[i].reset();
    pool->count = 0;
}
// 0x71002dee48
void reset_pool_2dee48(SlotPool* pool) {
    for (int i = 0; i < 32; ++i)
        pool->slots[i].reset();
    pool->count = 0;
}
