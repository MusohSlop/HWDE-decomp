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
- `vspec.py SPEC.py [--show K] [--keep] [--lev]` is `variants_cpp.py` driven by a Python spec file (BASE, ADDR, SYM,
  MAPS and SLOTS as `(old_text, [options])` pairs), so options can hold any text, `||` included; prints each
  combination's abstract, exact and word diffs and size, best last, and stops at a match (`WORK/match.cpp`).
  Placeholder names resolve as in sbs.py. `--lev` ranks by edit distance (below).
- `lev.py CPP ADDR SYM [--map ...] [--sbs [--regs]]` prints the edit distances (abstract and exact) between a scratch
  function and the original; `sbs.py --lev` prints them too and aligns the side-by-side by edit distance. difflib's
  longest-block matching (the counts of sbs.py and the variant tools) can pair a block with its duplicate elsewhere
  in the function and then count a whole region as changed (`5efb3c`: two copies of an inlined command block; one
  correct change moved difflib's count from 121 to 348 while the edit distance went down). Use the edit distance on
  functions with repeated inline code.
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
  through integer registers (`fmov; bfi; stp x`). `5a18e0`, `4f09dc` (parked).
- A switch whose cases end in `mov w8, #1; lsl w8, w8, wN; b tail` (the source register differing between groups of
  cases) before one shared `ldr; orr; str`: the source sets the bit in every case; branch folding merges the
  identical or/store tails. One statement after the switch computes the shift once in the shared block instead.
  `5a5b64` and its five siblings (misc/s5_functions06.cpp).
- Copy loops unrolled by 4 with pointer increments and a 32-bit counter (`add w9, w9, #4; cbnz`, remainder loop with
  post-increments): `for (unsigned i = 0; i < n; i++) { d->f = *src; src++; d++; }`. The index form `d[i] = src[i]`
  widens the counter to 64 bits and unrolls by 2; `d++->f = *src++` leaves register copies in the loop; `d++`
  before `src++` swaps the two adds. `5a5b64` (x6, five loops each).
- A loop that counts down from a trip count rebuilt from the clamp (`mvn; mvn; csinv; sub w9, w15(-2), w9 ... sub
  w9, w9, #1; cbnz`) with its first element stored from an earlier wider load (GVN load PRE): the loop tests
  `i != n`; with `i < n` LSR keeps an index register for the address and an up-counting compare. `5a5b64` (x6).
- A store `*(T*)ptr() = value` whose original loads the destination before the value: put the destination in a
  local first (the right side of an assignment is evaluated first). The same for a call argument read before
  the destination (`const void* s = u->ptr; memcpy(dst(), s, n)`). One of the two orders can differ between
  otherwise identical template copies (`5a6634` against `5a5b64`): a bool template parameter selects it.
  `5a5b64` (x6).
- Jump tables of template instantiations go to `.rodata.<mangled name>` (one comdat section each): map each
  section to the original table in the unit's map (`tools/add_symbols.py --map`). `5a5b64` (x6).
- A struct member with a user-provided default constructor makes the struct non-POD, so its assignment copies
  only the data size (a 0x28-byte memcpy for a 0x30-byte, 16-aligned element). `4f09dc` (parked, x4).
- A local whose original slot sits above the caller's arrays: inside an inlined (member) function its alloca moves
  to the top of the caller's entry block, ahead of the caller's own locals. `4f09dc` (parked, x4).
- A union vector that the original keeps in one vector register (lanes read with `mov s1, v5.s[1]`, built from two
  64-bit halves at a merge) but ours splits into 32-bit pieces in integer registers: SROA only vector-promotes an
  alloca when one load or store covers it whole as a vector; copy into it as `v.v = other.v`, not `v = other`
  (a memcpy). `4eab78` (97 -> 78; parked, x6 with its template copies).
- A frame whose temporaries reuse the slots of earlier locals (dir and q at the sums' slot): give the earlier
  locals a block scope so their lifetimes end (stack colouring merges only disjoint lifetimes). `4eab78` (x6),
  `503bd0` (the inverse matrix's temporary, x2).
- A union operator whose left operand is loaded as a vector and whose result goes through x0/x1: the left side by
  reference and the right side by value (`operator+(const Vec4u& a, Vec4u b)`, the shape of a member operator).
  `4eab78` (x6).
- Compares whose operands come out swapped from a helper (`fcmp c, a` where the original has `fcmp a, c`): a static
  helper's reference parameters are turned into values by ArgumentPromotion, and InstCombine puts the argument
  (less complex) on the right; write the test in the caller (or in a non-static inline function). The last load
  of a block in IR order takes the pre-indexed base (`ldr s0, [x22, #0x70]!`). `4f09dc` (parked, x4).
- A chain of range tests (`x > -E && x < E && ... && z < E`) where the original keeps every compare a branch except
  the last, which is a `cset` tested later with `cbnz`: a helper returning `int` with early returns (`if (!(...))
  return 0; ... return z < E;`). The last compare's zext then sits in its own block with the compare, so SimplifyCFG
  cannot speculate it into an `and` (a `bool` helper, a `&&` chain or per-pair helpers all fold the last pair into
  `cset; cset; and`). `4eab78` (15 -> 10, parked).
- A frame transform whose products keep the frame element first (`fmul s2, s2, s16`) after one `fneg` of the first
  term: the negated components added (`f->x.x * -v.x + f->y.x * -v.y + f->z.x * -v.z`); InstCombine folds the
  later negations into `fsub`s and keeps the frame element on the left (written as `-v.x * f.x - v.y * f.y ...`,
  Reassociate's rank order puts `v` first). `4eab78`.
- An 8-byte field loaded once (`ldr x8`) and stored as two words (`str w8; lsr x8, x8, #0x20; str w8`): a small
  setter taking the value by value, with a type that is not an HFA (the engine's 2D vector is a union; a
  `{u32, u32}` struct), storing the halves; a struct assignment gives one `str x`, field reads give two `ldr w`.
  `5efb3c` (three setters).
- A command block copied into a local in pieces (`memcpy` of 0x3a bytes from +2, scalar loads spilled, two 0x34-byte
  `memcpy`s, one 8-byte load) after the flags were stored (`sturh` before the first `memcpy`): store the
  (volatile) flags first, then `memcpy` the rest of the struct in one call; SROA splits the copy at the boundaries
  of the later uses of the local (whole-struct assignment to the current block, the per-field partial updates).
  The volatile flags stay in memory, which gives the `ldurh` before every bit test. `5efb3c`.
- A float range check that fails with `b.mi` and `b.ge` (NaN passes): `if (f < 0.0f || f >= 1.0f) fail;`
  (`!(f >= 0) || !(f < 1)` gives `b.lt`/`b.pl`). `5efb3c`.
- A loop with a 64-bit index for its addresses (`add x8, x19, x22, lsl #3`) but a 32-bit signed exit compare
  (`cmp w22, w8; b.lt`): an `unsigned long` index tested as `(int)i < (int)count`. With `int i` IndVars widens the
  compare too (`cmp x22, w8, sxtw`); with `unsigned int i` it does not widen the index at all. A test of the zero-
  extended count against the index with the count first (`mov w9, w8; cmp x9, x22; b.ls`) is written `count > i`
  (InstCombine would put a cast second, but this compare is widened after it). `5efb3c`.
- A loop that adds a whole 64-bit load (`ldr x21, [sp, #0x48]`: a u32 stride and the next field) to an offset kept
  in a 64-bit register, used as `w25, uxtw`: the offset is not a variable in source but `stride * (unsigned)i`,
  which LSR turns into that accumulator; an explicit `unsigned` accumulator makes the DAG split the widened load into
  two `ldr w`, and an `unsigned long` one keeps an `and #0xffffffff`. `5efb3c`.
- An invariant product computed after a loop's count test (`cbz w8; ldr s1, [cf4]; fmul s9, s0, s1`) although it is
  only used inside: compute it before the loop in source; MachineSink moves it past the test. Written inside the
  loop body, the load stays in the loop (the call may change it). `5efb3c`.
- Two call arguments built in stack slots that the original puts at the same offset (the direction for one call
  and the point for the next, both at sp+0x50): pass them as temporaries to `const T&` parameters
  (`shape.support(vec4(-v.x, -v.y, -v.z, 0.0f), nullptr)`); a temporary's lifetime ends with its full expression,
  so stack colouring can give both one slot. A named local, even in a block scope, kept the second one elsewhere.
  `4eab78` (one template, six copies: a hand note, not yet three sightings for gen; 9/36 -> 7/34 by edit
  distance, also fixed a `bfi`'s place). The same for an allocation-info struct passed to three allocator calls
  (`AllocInfo(0x11)` temporaries all at sp+0x70): `492bd0`.
- A min/max scan whose `fcsel` for the first value sits between the products of the second (`fcmp s2, s1; ldp; fmul;
  fmul; fcsel s1, ...`): compute both values before either update (`da = ...; db = ...; if (da < lo) ...; if (db >
  hi) ...`). `4eab78` (one template, six copies: a hand note; 13/75 -> 9/36 with the block-scoped slot above).
- A diamond `if (c) v = a + b; else v = a;` where the original adds a first (`ldp q1, q0; fadd v0, v0, v1`) without
  hoisting: after SROA every whole load of the non-promoted `a` is the same `load i128`, so a then-block that starts
  with it is hoisted by SimplifyCFG (and the diamond becomes a select, `bsl`); a then-block that loads b first
  stays a diamond, but Reassociate then orders the `fadd` by load rank (b first). Not solved; `4eab78`.
- Local job arrays whose elements get `bl <ctor>; str <vtable from the GOT + 0x10>` 32 times in a row and
  `bl <dtor>` in reverse at the end: write the jobs as real classes (base constructor and virtual destructor
  declared out of line, a key function so the vtable is external) and declare `Job jobs[32];`. The array
  constructor and destructor loops unroll fully; an explicit init loop does not, and an empty derived destructor
  stores no vtable pointer before the base destructor call. Map the base constructor and destructor (C2/D2) and
  `got:_ZTV...` to the GOT slots. `492bd0` (402 -> 277 by edit distance).
- An integer float compare (`m = (a & b) >> 31; (m ^ a) < (m ^ b)`) whose operands are loaded with `ldr w` and
  moved to float registers afterwards (`fmov s17, w12`): the helper takes `const float&` and reads the memory as
  `int`; a by-value helper loads floats and moves them to integer registers instead. `492bd0`.
