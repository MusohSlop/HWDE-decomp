# Fifth-session helpers

Scripts the fifth session uses to hand-match large functions (non-constructors over 1,500 bytes at `0x380000` and
above). They find the checkout from their own location (`tools/s5` -> `matching`) and write scratch files next to
their input. None of them changes `check.py`, `check_obj.py` or the generator, and none of them decides a match: a
result only counts after the unit passes the full `tools/check.py`. s3's tools (`tools/s3/`) are used as they are.

Run them with the project's Python, `python -B -I tools/s5/SCRIPT ...`, from `matching/`.

- `sbs.py CPP ADDR [SYMJSON] [--name SYM] [--map NAME=ADDR ...] [--all] [--ctx N] [--abs]` compiles one scratch
  file and prints a side-by-side diff (ours | original) of one function, with the instruction diff counts and
  `MATCH` for identical bytes. Symbols resolve as in `tools/s3/try.py`; functions registered in any unit resolve
  too. `--abs` compares with registers abstracted.
- `cc.py CPP [NAME...]` compiles a scratch file and prints the disassembly of its functions (unrelocated): for
  trying source forms of a small idiom side by side in one file.
- `flt.py ADDR...` prints literal-pool words as floats.

## Source patterns found by hand

Each with the functions it fixed; three or more make it a generator note.

- A clamp that tests `gt` and `pl` of the same compare separately (`cset w8, gt; cset w10, pl; cset w9, mi;
  tst/and; fcsel; orr; fcsel`): `bool lo = x < -90.0f; bool hi = (x > 90.0f) & !(x < -90.0); x = (lo | hi) ?
  (hi ? 90.0f : -90.0f) : x;` -- the negated test goes through double, so it stays its own compare (a repeated float
  compare is merged and its negation becomes `bic`). `415f00` (five times).
- A result tested with `and w8, w0, #0xff; cbz w8` (not `tbz w0, #0`) comes from a function returning
  `unsigned char`, not `bool`. `38e39c`.
- `obj->field = value` loads `value` first; the original loading the object pointer first is an inline setter,
  `obj->set(value)` (the object expression of a member call is evaluated before its arguments). `38e39c`.
- `csel ..., lo` after `cmp wN, #K` is an unsigned range test, `static_cast<unsigned>(x) < K`. `38e39c`.
- Generated source that repeats a shared tail in every branch (the generator forks at branches): write the
  `switch` with one tail after it; LLVM's tail merging then gives the original's shared sequences, including
  the cases that jump into the middle of another case's tail. `38e39c`.
- Struct subtraction where the loads of a block come before a branch and the stores after it: an inline
  `operator-` that returns the sub-struct by value, assigned to the field. `415f00`.
- Two loads that the original makes unconditionally and selects with `csel` (`x >= 0 ? x : y` where `y` is a
  field of another object): load both into locals first; with pointer parameters Clang cannot speculate the
  second load and branches instead. `415f00`.
- Globals laid out as one block and reached through one base register: file statics that GlobalMerge merged
  (sorted by size, then by first use); a struct of them keeps the declared order. Statics never stored in the unit
  are folded to their initialiser, so the functions that write them must be in the unit too. `3ccf84`, `45a850`.
- Stores through a `char*` that do not force reloads of a buffer's length and size: the buffer fields are file
  statics whose address is never taken (GlobalsAA). `__attribute__((used))` takes the address and brings the
  reloads back. `45a850`.
- A `switch` lowered as `cmp #b; b.eq; cmp #a; b.eq; cbnz` (the zero case last, falling through): the case block
  that follows the switch in source order is the one the lowering moves last; write the cases in that order
  (`default` first here). `45a850`.
- A `csel` whose operand is a division by two that Clang turned into a branch: the select condition needs a second
  use (CodeGenPrepare only turns selects into branches when their compare has one use), for example a `bool`
  flag tested again later. `45a850`.
- Padding loops counting down from `n + 1` to `> 1`: `for (int i = n; i > 0; i--)`; counting up unrolls by two.
  `45a850`.
- Operands of an `add` of two phis in the wrong order: Reassociate orders by rank, which follows the order of the
  phis in the block, which follows the declaration order of the variables; try the declaration orders. `45a850`.
- A `bool` in a struct tested with `tbnz #0` (not `cbnz`): an `unsigned char` tested with `& 1`. `3ccf84`.
- A ShowControllerSupport-style argument block whose halfword store comes before the word store: the default
  setter, then the overrides in the order the original's merged stores show. `3ccf84`.
- A one-byte fill that is `bl memset` followed by a loop that only counts the pointer and length up: an explicit
  fast path for the unlimited buffer with the pointer and length in locals (`if (cap == 0) { char* p = ptr; int
  len = n0; for (...) { *p++ = c; len++; } ptr = p; n0 = len; } else { for (...) put(c); }`). Without it the loop
  is unswitched but LoopIdiom runs before the pointer is promoted; a helper taking the pointer by value gives the
  memset but no counting loop. `45b158` (six loops); `45baf8` has the same shape (three).
- `mov xA, xB; ldrsw xC, [xA, #off]!` reading a self-relative pointer, with the object's other fields then
  addressed from `xA` (`ldur [xA, #-8]`, `add xA, xA, #0x1a4; ldr [xA]`): the DAG's pre-indexed load, which only
  forms when `this + off` is built in the same block as both its load and the add that uses it. Evaluate the
  value inside the block that tests it (a macro setter, not an inline function whose argument is evaluated first
  and whose field addresses GVN then hoists). `4bc6b8` (nine times); see the `packed_fetch` note in the README.
- `ptr->array[i]` loads `i` before `ptr` (Clang 3.9 emits a subscript's index first); `(ptr->array + i)` or an
  accessor taking `i` loads `ptr` first. `4bc6b8` (24 times).
- Two adjacent `int` fields tested one after the other with separate loads (not one `ldr x` and `lsr #32`): GVN
  widened the first load because the field is 8-byte aligned; test through a method of a 4-byte struct
  (`rel.valid()`), whose load is `align 4`. `4bc6b8`.
- A struct copied through the stack whose first piece sits in its own 16-byte aligned slot rather than in the gap
  next to a saved `d8`: the struct type is 16-byte aligned. `4bc6b8`.
- `memcpy(dst, src, n)` with `src` computed before `dst`: evaluate `src` into a local first. `4bc6b8`.
- A flag parameter inserted with `bfxil wN, wP, #0, #1` in one place and masked with `and wP, wP, #1` before a
  branch merge in another (the merge then uses `orr`): the parameter is a byte (`unsigned char`) passed on as
  `p & 1`, not a `bool`. `3bdbf0`.
- A temporary stored right before each call that takes it by reference (after the callee's vtable slot is
  loaded): build it in the call (`f(i, Color{...})`), not as a local declared before the call. `3bdbf0`,
  `448544` (the heap allocation info, `heap->alloc(size, 0x10, AllocInfo(0x2e))`, eleven times).
- A small struct built field by field on the stack (`strh`, `strh wzr`, `str xzr`) where ours copies it from a
  constant (`ldp`/`stp` from .rodata): give it a constructor instead of an aggregate initializer. `448544`.
- A 4-byte local at an 8-aligned slot right above the saved `d8` where ours puts it 4 bytes higher: declare it
  `alignas(8)`. `448544`.
- String literals scattered across the string section (some merged with other modules' strings): declare each as
  `extern const char kName_ADDR[] __attribute__((visibility("hidden")))` and map it, instead of one
  `.rodata.str1.1` anchor. `3bdbf0` (41 strings).
