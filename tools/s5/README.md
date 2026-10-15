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
- `variants_cpp.py TEMPLATE ADDR SYM [--map ...] --slot KEY=a|b|... [--slot ...] [--show K]` compiles every
  combination of a template's `{KEY}` options (`\n` for a newline, `||` between options that contain `|`) and
  prints each variant's abstract and exact instruction diffs and word diffs, best last; stops at a match
  (`build/s5/var/match.cpp`). Like s3's permtry.py, but it ranks all variants instead of stopping silently.
- `ranges.py CPP|LL FUNC` prints the live ranges as the greedy allocator sees them (after the pre-RA scheduler):
  each virtual register's first definition, last use and length in instructions, the ranges allocated first
  (spanning blocks, or longer than 64 instructions for FPR128/GPR64: longest first, ties to the lower vreg) and the
  register each got. For register-allocation-only near misses: the original's registers tell which ranges must be
  longer than which.
- `irsearch.py LL FUNC ADDR [--map ...] [--groups] [--iters N] [--temp T] [--seed S] [--work DIR]` searches
  instruction orders of the function's largest block in its optimized IR (`clang -S -emit-llvm` of the scratch
  file), compiling each order with the optimizer off (`-Xclang -disable-llvm-optzns`, about 0.15 s), scored by
  abstract then exact instruction diffs. Numbered values are renamed so any order is valid IR. `--groups` moves
  whole statements only (an instruction with several users or none, with the operands only it uses, kept
  contiguous) plus swaps of a statement's two independent calls, with simulated annealing (`--temp`, restarts to the
  best after `--restart` tries): orders a source file can give. `--gmin BEST.ll` (with `--groups`) then moves each
  statement back toward the original order while neither distance grows and marks what stays moved (`*`); that
  list is what to change in the source. Without `--groups` it moves single instructions (finds schedule matches
  fast, but the orders rarely map back to source). Writes `gbest.ll`/`best.ll` and stops at a match (`match.ll`).
  Try plain mode first on schedule- or allocation-only near misses: it closed s4's `29b5f8` (11 off, one block) in
  seconds where `--groups` ran half an hour without gain, and diffing `match.ll` against the source block names
  the statements to move; `--block LABEL` picks another block (the setup block of the model builders, `21d738`).
  Use it for schedule- or register-only near misses where the pre-RA scheduler keeps the IR order (check with
  `-mllvm -print-machineinstrs`: compare the input and output of "Machine Instruction Scheduler"). Give it the
  scratch `.cpp` and it emits the IR itself with the unit flags, `-g` and `-Xclang -emit-llvm-uselists`: both the
  debug intrinsics and the use-list order change codegen in some functions (`3b4e98`: 6 off from source, 8 from IR
  without `-g`, 7 without the use-lists), so its first score must equal what sbs.py reports; when clang cannot read
  the `-g` IR back (it crashes on some, `761d8`) it falls back to IR without `-g` and says so. Loads, stores and calls
  keep their relative order, so blocks made mostly of memory operations leave it little to move; `--loads-free` lets
  loads move among themselves (stores and calls stay ordered), which is how local definitions read from memory can
  be reordered in source (`4ce8e0`). `--minimize BEST.ll` moves single instructions back toward the source order
  (`--strict`: the exact distance may not grow either); both minimizers accept only moves that reduce the number of
  inverted pairs, so they always end. Multi-line instructions (`switch`) stay whole and terminators and phis stay
  in place; orders that fail to compile are counted and reported at the end, the first kept as `irs_tmp.ll.fail`.
  Names ending in an address (`callee_X`, `kName_X`) and the functions of every unit resolve as in sbs.py (before
  this fix, each reference to such a name counted as a difference: 386 off where sbs.py says 117 on `3ba734`).

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
- A range test `sub; cmp #9; b.hs else` with the then-arm placed first, where ours has `cmp #8; b.hi`: the original's
  branch went to the then-arm at instruction selection (else was the next block) and block placement reversed it;
  write the test negated with the then-arm as the else block, `if (!(x >= 18 && x <= 26)) { ... } else { x += 5; }`.
  `3bd1d8` (twice).
- A run of "flag and (all or owned)" tests where the original loads the all flag once at the top and duplicates
  the rest on its value (each test after it threaded): the helper tests the all flag first,
  `all ? has[i] != 0 : has[i] && owned[i]`; the form `has[i] && (all || owned[i])` reloads it per test. `3bd1d8`.
- A 12-byte struct copied through a stack temporary (x,y as one 8-byte load stored to the stack and reloaded, z
  stored too or kept in a register with `mov w9, w9`): copy into a local and pass it to a const-reference setter,
  inside a macro, not an inline function (inlined, the local is promoted). Without TBAA a store between the load
  and the store keeps both halves in memory. `3beef0` (four copies), `3be490` (four).
- A virtual lookup whose vtable load comes before the load of its name argument (`ldr x8, [x0]` before
  `ldr x21, [table, i, lsl #3]`): call the virtual function directly with the table read in its arguments, not
  through an inline helper taking the name. `3beef0`, `3be490`.
- A flag set in one block reached from both tests of an `||` (one `mov w25, #1`): `bool f = false; if (a || b)
  f = true;` -- an if/else assigning true and false, or the expression itself, duplicates the true block. `3beef0`.
- Byte flags at constant indexes merged into `ldrh` where the original reads them one by one, and indexed ones
  addressed as `this + i` with the field offset in the load: make the array member an align-1 wrapper with
  `operator[]`. `3be490`, `3beef0`.
- A long straight-line NEON block (the matrix inverse) where the shape matches but registers and the post-RA
  interleaving do not: the pre-RA scheduler leaves such a block in IR order, so the source order sets each live
  range's length, the greedy allocator gives the ranges longer than 64 instructions their registers longest first
  (a tie goes to the lower vreg, the value defined first), and the post-RA scheduler then interleaves around the
  registers that came out. Read off the original's registers which ranges must outrank which (`ranges.py`), and
  move statements to lengthen or shorten them by single instructions; `irsearch.py --groups` finds such orders. For
  the inverse: the d row's swizzles in the order d2, d1, d3 (the YX control's range otherwise ties c2's and wins on
  vreg number) and each cofactor row multiplied by its sign in the same statement (c1-c3 one instruction longer).
  `5a3ce0`, `3e1538` (first try on the shared `include/misc/matrix_inverse.h`), `5f9fac`.
- Vectors built by lane inserts inside a loop with no copy of the zero vector per iteration (`mov vN.16b, vZ.16b`
  only before the loop): the vectors are carried, zeroed once before the loop and their lanes rewritten each time
  (`m.r[0] = vsetq_lane_f32(p0.x, m.r[0], 0)`), so lane 3 keeps its zero without a copy. `5f9fac`.
- A float finite test as `ubfx wN, wM, #23, #8; cmp wN, #0xfe; b.hi`: `(bits & 0x7f800000) < 0x7f800000`; the
  shift-and-mask forms (`((bits >> 23) & 0xff) != 0xff`, a bitfield) are folded to `and; cmp #0x7f800000`. Two such
  tests on adjacent floats sharing one `ldr x` read them through a 16-byte aligned type (GVN widens an 8-aligned
  load). `242070` (parked).
- Fused multiply-adds with a constant splat as the first multiplicand (`fmla v, vSplat, vRow`): the transform is
  written `vfmaq_f32(r, vdupq_lane_f32(lo, 1), m.r[1])`; with a variable vector both forms give the by-element
  `fmla`, so the shared `XMVector4Transform` is written splat-first. `242070` (parked).
- A loop whose body starts with the same call as the code after it (`bl get_game` at the top of the body and of
  the unlock), with the original keeping the call in the body and the exit test at the bottom: write the loop as
  its own inline function returning the result. Written in the caller, SimplifyCFG hoists the common call above
  the loop test before LoopRotate runs, and the rotated loop then calls it in the preheader and the latch (and a
  `bool ok` + `break` form also carries the flag in a register). Several `continue`s in such a loop become a
  state switch (`orr #4; and #7; cmp #4`); one combined `if (... && ...) return false;` keeps the branches.
  `45f07c` (eight loops).
- Two values that leave a loop equal (a copy loop's index and the output count, both counting from 0) and the
  original's register coalescing joins the loop counter with one of them (`mov w24, w8` after the loop): the order
  of their declarations decides which (`unsigned int i, n;` against `n, i`, through the order of the phis);
  register-only differences across a whole function can come from that one join. `59f778`.
- `cmp a, b; csel wD, wB, wA, hi` is `a > b ? b : a` (`b < a ? b : a` gives `cmp b, a; csel ..., lo`). `59f778`.
- A 16-byte zero stored as `stp xzr, xzr` into an array of a union holding a `float32x4_t`: copy a `static const`
  zero of the union (lowered as a memset); value-initialisation stores a NEON zero (`movi; str q`). `59f778`.
- A transform written into an output entry with all three results computed before the first store (`stp s, s;
  str s` after the arithmetic): compute into locals, then store; storing each component as it is computed makes
  the input reloaded after every store (the output may alias it), and returning the union by value sends it
  through integer registers (`fmov; bfi; stp x`). `5a18e0`.
