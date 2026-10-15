# Unit-state test: recognizer recipe (fourth session)

About 55 functions below 0x380000 inline one test on a unit's state id; 33 match so far (`src/misc/s4_unit_state*.cpp`,
`src/misc/s4_b8168.cpp`). The test, the unit types and the helpers are in `include/misc/s4_unit_state.h`. This page
lists what a generator rule needs to know to write these functions.

## Recognizing it

The id is the int at `+0x10` of the object that `Unit` vtable slot `+0x48` returns (`state()`). The test is:

```
ldr   w9, [x0, #0x10]
tbnz  w9, #31, <fail>            ; id < 0
and   w8, w9, #0xfffffffe        ; id & ~1, shared by the 58/59 and 12/13 tests
cmp   w9, #0x19
b.lt  <bittest>                  ; id < 25
cmp   w8, #0x3a
b.ne  <fail>                     ; not 58/59
<bittest>:
mov   w10, w9
cmp   w9, #0x27
lsl   x9, <1>, x10
and   x9, x9, <0x80003f06c0>     ; 6, 7, 9, 10, 16-21, 39
ccmp  x9, #0, #4, ls
ccmp  w8, #0xc, #4, eq           ; 12/13 (sometimes a separate cmp/b.ne, see below)
b.eq  <fail>
```

The mask is built with `mov x, #0x8000000000; movk x, #0x3f, lsl #16; movk x, #0x6c0`. That triple is the grep key
(`build/s4/grepdis.py "movk x\d+, #0x3f, lsl #16" "movk x\d+, #0x6c0$"`).

## Source

```
IF_UNIT_STATE_ACTIVE(u->state()->id, action);
```

expands to

```
int st_ = id;
if (st_ >= 0 && (st_ < 25 || !((st_ != 58) & (st_ != 59)))) {
    switch (st_) {
    case 6: case 7: case 9: case 10:
    case 16: case 17: case 18: case 19: case 20: case 21: case 39:
        break;
    default:
        if ((st_ != 12) & (st_ != 13)) { action; }
    }
}
```

- The two pairs are bitwise `&` of `!=` tests. That gives the shared `and w8, w9, #0xfffffffe`. With `||` or `==` the
  58/59 pair becomes `(id | 1) == 59` instead.
- The action has to sit in the switch default. If it is a separate inline `bool` helper, SimplifyCFG turns the switch
  into a lookup bitmap (`mov x, #0x200000002; movk ...; lsr; tbz`).
- The usual actions: `a = u->actor()` (vtable `+0x10`), then something on the actor, often a call through the actor's
  vtable `+0x180` with a command number.

## Shapes that need care

1. **Results are `int`, not `bool`.** When the function returns a value (or keeps a flag) through a phi, a `bool`
   (i1) phi lets SimplifyCFG build the switch as a lookup bitmap: 34 entries x 1 bit fit in a register. With `int`
   (or `unsigned char`), 34 x 32 bits don't fit, the table density is 32% (< 40%), and the switch stays a bit test.
   Examples: b488, 43128, bf440 return `int` (a 0/1 from `(flags >> n) & 1` on a 64-bit field); 5acb0's flag is an
   `unsigned char`.
2. **`goto` out of the test when the 12/13 compare stays a separate branch.** Some originals keep `b.ne; cmp w8, #0xc;
   b.ne` instead of the ccmp. Writing the action outside the macro reproduces it:
   `IF_UNIT_STATE_ACTIVE(id, goto active); return X; active: ...` (40bcc). The opposite case (ccmp merged in the
   original, ours separate) is not solved (bf440).
3. **The side -> unit id lookup (0x710000db3c).** Most functions call it. ec18 inlines it: there an always_inline copy
   of its body is used (`side_unit_id` in `s4_unit_state.cpp`); the extern declaration stays for the others, so
   clang doesn't inline it everywhere.
4. **One jump table per unit.** A function with its own switch jump table needs its own unit (`.rodata` is mapped
   once per unit): 41f0c is in `s4_unit_state2.cpp`, fa9c needs a third. Consecutive tables can share a unit when the
   functions are in address order (41990's table at 0x710073fadc is directly followed by 41b7c's at 0x710073faf0).
5. **Callers and callees in one unit.** A unit-state function called by another one (4126c from cdbb4 and 41990,
   3c784 from 3c674) goes in another unit, or clang inlines it.

## Helpers that recur

- `find_unit(id)`: `gUnitTable->unit(id)`, `(unsigned short)id <= 0x6d6 ? units[id] : 0`; units at `+0x138`.
- `UnitTable::unit_at(long id)`: the same check on the sign-extended value (`ldrsh x8; cmp x8, #0x6d6`) for ids read
  from a field (ce7e8, 74eb0).
- `unit_can(id, cmd)` / `side_unit_can(side, cmd)`: unit's actor exists and `actor->command(cmd)` (vtable `+0x180`)
  is nonzero (as `unsigned char`). Chains of these: 41990, 4126c, 3e350.
- Selects that keep `csel x, x, xzr; ldr [x, #off]` (an item record by bound) only survive as a select of loads:
  `i < 0x44c ? defs[i].f : ((T*)0)->f` (8b910, fa9c).
- `x == 0 ? 0 : 2` gives `csel wzr, w8, eq`; `x ? 2 : 0` folds to `cset; lsl` (41990).
- Read the loop-invariant globals into locals before a loop; under -fno-strict-aliasing LICM won't hoist them past
  the stores (75434).

- The side -> unit id lookup returns `int` (the id field is an int); callers truncate it to `short`. A signed range
  test on that short (`id >= 0 && id < 0xd2`, or `< 0x6d7`) is what gives the odd `mov w8, #0xffff; bfi w8, w0, #16,
  #16; cmp w8, <(C << 16) - 1>` form (2174c, 1ac4c); an unsigned test on it gives `and w8, w0, #0xffff; cmp`.
- `unit_can_jump` (the action reached by goto) keeps a null unit's later lookups from being threaded away (3e350,
  found by an unattended variant search).
- Units by handle (1ac4c): index in the low half, generation in the high half (`UnitTable::by_handle`,
  generations at +0xefa8).

## Status

Matched: 34 (see `docs/s4_claims.txt`, "matched"). Parked with notes in `docs/s4_wip/unit_state_parked.cpp` and
`docs/s4_wip/fa9c.cpp`: 2174c, bf440, 43e20, 8b910, 74eb0, 41b7c, c69a0, 17860, 1ac4c, fa9c. Not started: 3c784, 32fc4, 43770, 2209c, 34e88,
42668, 17e84, ac28, 31edc, 8efc0 (spawn and effect routines of 900-3500 bytes). Most of them are 2-16 instructions
off on block placement, tail merging or the ccmp choice; the shape of the test itself matches in all of them.
