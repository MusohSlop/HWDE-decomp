# Yielding spin lock: recognizer recipe (fourth session)

Main's `nospinlock` knob covers the plain lock, `while (!__sync_bool_compare_and_swap(&lock, 0, v)) {}` (exact on
49b448). A second form yields the thread between attempts and is fenced on both sides. It is matched in
`src/misc/s4_spinlock.cpp`; the macros are in `include/misc/s4_spinlock.h`.

## Recognizing it

```
dmb   ish                       ; fence before the lock
mov   x19, x0                   ; (setup, after the fence)
add   x20, x19, #<lock>
mov   w8, #1
ldaxr w9, [x20]                 ; first attempt
cbnz  w9, <slow>
stlxr w9, w8, [x20]
cbnz  w9, <first attempt>
b     <locked>
<slow>: mov w21, #1; clrex; b <yield>
<retry>: clrex
<yield>: bl #0x600b20           ; nn::os::YieldThread
ldaxr w8, [x20]
cbnz  w8, <retry>
stlxr w8, w21, [x20]
cbnz  w8, <yield + 4>
<locked>: dmb ish               ; fence after the lock
...                             ; the guarded body
dmb   ish                       ; fence before the unlock
ldaxr w8, [x20]                 ; unlock: one compare-and-swap 1 -> 0
cmp   w8, #1
b.ne  <clrex>
stlxr w8, wzr, [x20]
cbnz  w8, <unlock ldaxr>
...   clrex
dmb   ish                       ; fence after the unlock
```

Grep key: a function with `ldaxr`, `bl #0x600b20` and `dmb ish` (`build/s4/grepdis.py "bl #0x600b20$" "ldaxr " "dmb
ish"`): 8 functions (49c9dc, 49ca74, 49c7a4, 49c880, 49cb24, 49c364, 468f7c, 469334). Two more (4d0294, 4d0c18) yield
without the fences.

## Source

```
#define SPIN_FENCE() asm volatile("dmb ish" ::: "memory")
#define SPIN_LOCK(word)   do { SPIN_FENCE(); while (!__sync_bool_compare_and_swap(&(word), 0, 1)) nn_yield_thread(); SPIN_FENCE(); } while (0)
#define SPIN_UNLOCK(word) do { SPIN_FENCE(); __sync_bool_compare_and_swap(&(word), 1, 0); SPIN_FENCE(); } while (0)
```

- The fences must be inline asm (`dmb ish` with a memory clobber, like nn::os's memory fence). With
  `__sync_synchronize()` or `__atomic_thread_fence(__ATOMIC_SEQ_CST)` the IR fence is the same, but our scheduler
  issues the first `dmb` after the `this` copy, the lock address and the constant 1; the original issues it first.
  (Only the first fence's position shows; the asm form fixes it, and it matches with all four as asm.)
- `nn_yield_thread()` is the import at 0x7100600b20 (`_Z15nn_yield_threadv` in units.json).
- The lock word is an `int`; the unlock is a single compare-and-swap of 1 -> 0, its result ignored.

## Matched

49c9dc, 49ca74, 49c7a4, 49c880 (one class: a lock at +0x60 guarding a four-slot float ring at +0x30 and a flag word at
+0x68). Parked: 49cb24, 2 off (docs/s4_wip/49cb24.cpp: the original reloads a field inside a branch). Open: 49c364
(the class's factory), 468f7c, 469334, 4d0294, 4d0c18.
