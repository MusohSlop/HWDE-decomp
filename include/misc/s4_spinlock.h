// The yielding spin lock that about ten functions inline (fourth session's spin-lock batch): lock spins on a
// compare-and-swap of 0 -> 1, yielding the thread between attempts; unlock swaps 1 -> 0 once. Both are fenced on each
// side with a full barrier written as inline asm (dmb ish, like nn::os's memory fence): with __sync_synchronize the
// first barrier is scheduled after the lock word's address and the this copy, the original issues it first. They are
// statement macros on the lock word (an lvalue). Names are descriptive placeholders.
#pragma once

void nn_yield_thread();                                                     // 0x7100600b20 (nn::os::YieldThread)

#define SPIN_FENCE() asm volatile("dmb ish" ::: "memory")

#define SPIN_LOCK(word)                                                                     \
    do {                                                                                    \
        SPIN_FENCE();                                                                       \
        while (!__sync_bool_compare_and_swap(&(word), 0, 1)) nn_yield_thread();            \
        SPIN_FENCE();                                                                       \
    } while (0)

#define SPIN_UNLOCK(word)                                                                   \
    do {                                                                                    \
        SPIN_FENCE();                                                                       \
        __sync_bool_compare_and_swap(&(word), 1, 0);                                        \
        SPIN_FENCE();                                                                       \
    } while (0)