# Generator handoff

State of the generated-unit work at commit time, for a session picking it up.

## Where the tools are

The generator and its drivers are in `tools/gen/`. Every script finds the checkout from its own location
(`tools/gen` -> `matching` -> project root), so the same files run unchanged in another worktree against that
worktree's `data/units.json` and `build/`. They need the project's `.tools/` (compiler and capstone) and the
decompressed game image under `analysis/extracted/update/decompressed/` next to `matching/`.

- `gen.py OUT.cpp UNIT LO HI` is the generator: symbolic execution of every unmatched function of LO to HI bytes,
  written out as C++ into OUT. Environment switches: `ONLY`, `EXCLUDE`, `VARIANT`, `VARIANT_MAP`, `DRYRUN` (no
  symbol writes), `FAILDUMP` (one line per skipped function with its reason), `TRACE` (re-raise internal errors),
  `NEARMISS` (also take near misses), `SYMOUT` (write the symbols to register to a file instead of `units.json`).
- `run_bands.py gen.py UNIT LO HI [KNOBFILE]` runs the generator over a size band in chunks of about 25 functions,
  generating and compiling them in parallel with a timeout per compile, tries each knob set in turn (`knobs.txt`
  lists the current sets), and writes every exact match into UNIT under its winning knobs. A chunk keeps the matches
  that are clean on their own even when another function in it has an unresolved relocation; a chunk that times out
  or fails to compile is split until only the offending function is lost, and the log counts those losses.
  `RV_JOBS` sets the number of parallel jobs, `RV_TIMEOUT` the timeout, and `RV_ADDR_LO` and `RV_ADDR_HI` (hex
  image offsets) restrict the address range; `RV_ONLY` names a file of hex image offsets to restrict the run to
  (for a rerun of only the functions a generator change newly covers). Timed-out chunks are logged to
  `build/rvpar_slow.txt`.
- `mm_probe.py gen.py LO HI` classifies the first differing instruction pair of every mismatch. With `--classes` (and `--addr LO-HI`, `--only FILE`, `--knobs K`, `--jobs N`, `--tsv FILE`) it runs `mm_tally.py` instead: scratch units under `build/mmtally` (`data/units.json` is not touched), compiled in parallel, every function sorted into match / size / regalloc / schedule / other, with the size and other classes split by word difference and first differing pair.
- `probe_one.py gen.py ADDR` generates one function into a scratch unit, prints its diff and source, and removes the
  scratch unit again.
- `nm_probe.py gen.py FILE` does the same for the logged near misses under each knob set, so a generated match can
  guide a fix of the hand-written version.
- `batch_fix.py`, `fixnames.py`, `autosym.py`, `rm_unit_names.py` and `clean_matches.py` are the runner's helpers
  (rename placeholder symbols, add callee symbols, remove a unit's names, list the clean matches of a built unit).
- `merge_units.py OURS THEIRS OUT` merges two versions of `data/units.json` (see `docs/second_session.md`).
- `dis.py ADDR...` disassembles functions of the image by address.

## What the generator covers

Symbolic execution over one function at a time, written out as ordinary C++ with placeholder names
(`docs/generated_units.md` lists the units and placeholder schemes). It handles:

- calls, virtual calls, calls through loaded or parameter function pointers, tail calls and imports;
- stack objects, register spills, and incoming stack arguments;
- if/else structures joined at post-dominators;
- `do`/`while` loops written as index loops over element arrays, including sequential and nested loops;
- one- and two-level element access, byte-offset and selected bases, and pointers chosen by a branch;
- floats, two-float returns, 16-byte vector copies, range tests on narrow ids, and the common AArch64
  arithmetic and bit-field instructions;
- float constants from the whole 4-byte literal pool (`0x710073b000`-`0x710073ca00`) and 16-byte vector
  constants from the 16-byte pool (from `0x710073dff0`), written as `(Vec4f){...}` literals; generated units map
  `.rodata.cst4` and `.rodata.cst16` to the two pool starts, and `check_obj.py` searches 0x2000 bytes from a
  mapped pool start for a merged constant;
- float and vector stack slots: fields of an address-taken stack object, or spill slots whose value comes back on
  reload;
- `sqrtf` with errno kept (`fsqrt`, `fcmp sD, sD`, `b.vc` over a `bl sqrtf`, or `b.vs` to a tail call), written
  as one `sqrtf` call;
- branches on float compares with `mi`/`pl`, and register-indexed and pre-indexed float loads and stores;
- with the `copy64` knob, an `ldr x` whose value is only stored again is an 8-byte copy, written as
  `__builtin_memcpy` on byte addresses so the fields on both sides keep their own types;
- fields typed only by 8-byte constant stores (`str xzr`, `stp xzr, xzr` on stack objects) take the type of a
  later narrower access, and the constant store is split over the fields it covers;
- integer reads of different widths at one offset (Clang narrows a load whose value is only truncated) are one
  field of the wider type, read back with each load's own type (knob `nowiden` turns this off);
- 128-bit float vector arithmetic (knob `novec` turns it off): `Vec4f` is `float __attribute__((ext_vector_type(4)))`
  (earlier units keep their `vector_size(16)` typedef, which compiles the same), vector `+ - *`, multiply by a lane,
  `fmla`/`fmls` as `vfmaq_laneq_f32`/`vfmsq_laneq_f32`/`vfmaq_f32`/`vfmsq_f32` from `arm_neon.h`, `dup`, zero `movi`,
  negation, lane reads `v[i]`, and stores of vector values;
- vectors passed and returned in two x registers (knob `novecu`): the engine's vector type is a 16-byte aggregate
  that the AAPCS passes in two general registers, written as `union VecU { Vec4f v; long l[2]; }`, a parameter
  `VecU pN` (registers N and N+1) read as `pN.v`, and `vecu(v)` for a vector returned or passed on;
- `fmov vD.4s, #imm` as a vector of one constant, `(Vec4f)(c)` (knob `novecsplat`);
- the `sqrtf` slow path may spill and reload float registers around its call (knob `nosqrtspill`);
- vector lane inserts `mov vD.s[i], vS.s[j]` (knob `novecins`), written with the unit helpers `vins(v, s, i)` and
  `vundef()` (a vector built lane by lane starts undefined, with lane 0 the scalar already in `sD`);
- vector addressing (knob `novecaddr`): `[xB, xI, lsl #4]` is a Vec4f array element, `[xB, xI]` a Vec4f through a
  byte offset, `[xB, #off]!` and `[xB], #off` step the base; every vector value can be stored;
- an int return where the original never sign-extends into x0 (knob `noretint`): a return merged from a 32-bit int
  and a 64-bit value (often a pointer known to be null on that path) is int, and so are the merged values on the way,
  instead of long (which added `sxtw x0, w0`); a pointer converted to a narrower integer goes through long;
- compile fixes: stack objects at negative frame offsets are named `local_mNN`, a pointer compared as a 32-bit
  unsigned value goes through `unsigned long`, and a struct pointer passed to a differently typed import parameter
  is reinterpret_cast;
- a short or signed char passed to a call is an int argument (knob `nosextarg`): the calling convention leaves a
  narrow argument's upper bits unspecified, so a short parameter would be loaded with `ldrh` where the original's
  `ldrsh` shows an int parameter;
- argument counts from known callee names (knob `noknownarity`): a callee named with a real mangled name in the
  symbol table or a hand-written unit never gets more integer or float arguments than its parameter list (plus
  `this` for a member) allows; a function that fails with a reduced call is generated again without it; the name of
  a trivial callee (one that never reads an argument register, such as an empty body) does not limit the count, as
  its parameter list is a guess (knob `trivialarity` uses it, and a function that fails without it is generated
  again with it);
- bitfield writes (knob `nobitfield`): a store of `(load of the same field & mask) | x` that rewrites one run of bits
  is a bitfield assignment `p->bfOFF_START = x;`, with the field declared as a union of the whole field and an
  anonymous struct of bitfields (Clang then computes the value before the load, as the original does);
- unsigned division and modulo by a constant (knob `nodivmagic`): a multiply of a 32-bit unsigned value by a magic
  number shifted right by 32 or more, checked to be exact, is `x / d`, and `x - d * (x / d)` (msub, or shifted adds)
  is `x % d`; `msub` is supported as `c - a*b`;
- signed division and modulo by a constant (knob `nosdivmagic`): `smull` by a magic number with Clang's sign fix
  (`asr` of the product plus its sign bit, or `asr` of high half plus x plus `lsr #31`), checked against truncating
  division, is `x / d`, and `x - d * (x / d)` is `x % d`;
- 64-bit unsigned division and modulo by a constant (knob `noudiv64`): `umulh` by a magic number and a shift (after a
  shift of x for an even divisor), checked on extreme and random values, is `x / d`, and `x - d * (x / d)` is
  `x % d`;
- two int fields read by one 64-bit load (knob `nopair32`): an `ldr xN` whose value is only used as `wN` and as its
  high word (`lsr`/`asr #32`, `ubfx #32, #32`) is two int field loads; a function where the split fails is
  generated again without it;
- a pointer plus a constant is byte-pointer arithmetic (knob `noptradd`),
  `reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p) + C)`: written as integer arithmetic, Clang's constant
  hoisting kept a large C in a callee-saved register across calls, one more saved register than the original (a
  different frame and store pairing);
- a member address computed early is a local declared there (knob `nohoistaddr`): an `add xD, xN, #C` (or a
  register holding a constant) into x19-x28 whose value is only copied into argument registers after at least one
  call is `long aN = ...;` at the add (Clang emits the address where the source computes it, so the original declared
  it early, typically the first element of an array it constructs or destroys); written at the call, the original's
  extra saved register was missing; a function that fails with it is generated again without it;
- indexed element addresses are one byte-pointer expression with the variable part first and the constant last
  (knob `noelemaddr`): an element access on a pointer plus whole elements is
  `reinterpret_cast<Elem*>(reinterpret_cast<unsigned char*>(p) + static_cast<long>(i) * S + C)->field`, and a
  pointer plus an index plus a constant is `reinterpret_cast<long>(reinterpret_cast<unsigned char*>(p) + i*S + C)`;
  with the constant first, LLVM reassociated and hoisted `p + C` out of a loop into a callee-saved register;
- float results of indirect calls (knob `novcallf`): when the instructions after a virtual call or a call through a
  function pointer read s0 before writing it, s0 is the call's result (as for direct calls), and a float call result
  still in x0 no longer hides a changed s0 at the return (`bl f; fneg s0, s0; ret` returned the call result);
- float argument counts without consumed temporaries (knob `nofargscan`): when a float register below the count (one
  more than the highest float register written since the previous call) is undefined, the count is taken again from
  the straight-line code before the call, counting only registers not read after their last write;
- two-float struct results of calls (knob `nof2call`): when the code after a call (straight-line, following
  unconditional jumps) reads s1 before writing it, the callee returns `Float2` and s0 and s1 are its `.x` and `.y`
  (`bl f; stp s0, s1, [sp, #0x18]`; these failed with undefined s1);
- values merged in float registers are floats (knob `nofmerge`): a call result only copied in a float register
  (`bl f; mov v8.16b, v0.16b`) stayed untyped and failed a merge with a float ("merge types: int|float"); the call
  results in a used float merge, and in every float merge connected to it, are floats, unless one of them also
  reaches a merge outside the float registers (a call result is in x0 and s0) or its callee returns an int at
  another call; a float merge with a side typed as an int or a pointer (the stale s0 of an int call) is dropped;
- fields at offsets their type is not aligned to (knob `nopackfield`): a scalar field whose offset is not a multiple
  of its size (a long at +45594) is declared `__attribute__((packed, aligned(N)))` with N the alignment of its
  offset, so the compiler does not pad it to its natural alignment and move every later field;
- int fields converted to float in a vector register (knob `noicvt`): `ldr s0, [..]; ucvtf s0, s0` (scvtf for int),
  `ldr h0, [..]; ucvtf s0, s0` (an unsigned short, as `ldr h` zero-extends; `ldr b` for unsigned char) and
  `ldr h0, [..]; sshll v0.4s, v0.4h, #0; scvtf s0, s0` (short, ushll for unsigned short) are int loads of the
  field's type and `static_cast<float>` of them (these failed as "ucvtf", "scvtf" and "reg h0");
- byte-offset accesses into typed fields (knob `nobytearr`): an unscaled register-indexed access of a value wider
  than a byte made the field at its base a byte array, and a direct access of another type at that offset failed
  with "field clash"; the typed field now wins and the byte-offset access goes through
  `reinterpret_cast<unsigned char*>(&p->field)[i]` (real byte arrays keep their type);
- float values through general registers (knob `nofbits`): `fmov sD, wN` of a constant is that float constant and of
  an int field load retypes the field as a float; `fmov wD, sN` holds the float's bits, with `eor 0x80000000` a
  negation, `and 0x7fffffff` an absolute value, a 32-bit store a float store and `fmov` back the float (floats in
  parameter registers, as two-float structs passed in x registers, are not modelled yet);
- conditional float compares (knob `nofccmp`): `fccmp sA, sB, #nzcv, cond` is a link of the compare chain as `ccmp`
  is for ints, and a chain may end in a float condition (`mi`, `pl`, ...);
- stack vector slots used as lanes and halves (knob `novecunion`): a 16-byte stack slot used as a Vec4f and also as
  float or int lanes or as 8-byte halves (`ldp x0, x1` to pass the vector in two x registers) is a `VecU` union
  (`Vec4f v; long l[2]; float f[4]; int i[4];`), and each access goes through the view of its type; struct and class
  members likewise (a Vec4f member whose lanes are also read or written as floats);
- float rounding (knob `nofround`): `fcvtms`/`fcvtmu`, `fcvtps`/`fcvtpu`, `fcvtas`/`fcvtau` are the int conversion of
  `__builtin_floorf`/`ceilf`/`roundf`, `frintm`/`frintp`/`frinta`/`frintz` those calls and `__builtin_truncf`, and
  `fnmul` is `-(a * b)`;
- sqrtf slow paths (knob `nosqrtpair`): register pairs saved around the `bl sqrtf` are skipped like single spills and
  keep their values, and an `fcmp sD, sD` with independent instructions before its `b.vc` is moved down to it;
- vectors from two x registers (knob `novcomb`): a call result's x0/x1 is a `VecU` return read as `.v`, other pairs
  `vcombine_f32(vcreate_f32(lo), vcreate_f32(hi))`, and a lone vector half `vecu(v).l[h]`;
- post-indexed float loads and stores (knob `nofpost`), and single-lane vector loads and stores (knob `nold1`):
  `ld1 {vN.s}[k]` inserts a float field into a lane, `st1 {vN.s}[k]` stores one, `ld1 {vN.d}[0]` loads a low half;
- a vector and a scalar merged in one float register (knob `vlanemerge`, used when a function fails with
  "merge types: float|Vec4f"): the vector side is lane 0; the bits of a float used as an int (`fmov w, s` read
  elsewhere) are an unsigned int through `__builtin_memcpy` in a lambda;
- an array field also accessed as a scalar at its start (knob `noarrscalar`): the scalar keeps the field and the
  indexed accesses go through `reinterpret_cast<T*>(&p->field)[i]` with T the element type;
- struct copies (knob `nostructcopy`): a run of load/store pieces whose loaded values are only stored, between two
  (non-stack) bases at one delta and covering 12 or more contiguous bytes in straight-line code, is one struct
  assignment of `struct alignas(A) BlkR_A_FUNC { unsigned char b[R]; }`, or a loop over the records when the pieces
  repeat a record pattern (Clang expands both into the same pieces); the pieces no longer type fields. The pieces'
  bases may be computed (`add xD, xR, #imm`, `mov`, and register offsets set by `mov`/`movk`; knob `nocopybase`);
  pieces that make equal runs at a constant stride with gaps between them are a loop copying one member per record
  (`d.names[i].name = s.names[i].name`, a 29-byte member at a 0x20 stride; knob `nocopystride`); and when the run
  only repeats a record pattern after a leading or before a trailing field, that field stays a field (a count
  before its array; knob `nocopycut`, which prefers the cut whose records start with their largest piece); a
  copy's bases are told apart by register versions (knob `nocopyver`), so a copy from a pointer loaded in the same
  block (a vector copied before its w is set) is found too, and emitted where both bases still hold those values;
- single-piece copies (knob `copy1`, used when a function fails with a field clash or an overlap; `nocopy1` turns the
  retry off): an 8- or 16-byte value loaded and only stored at a constant delta is a block copy, so a constructor's
  16-byte member copy or a two-float member read as 8 bytes does not type the fields;
- copies to and from stack locals (knob `nostackcopy`): a copy whose stack side lies in one addressed stack object is
  a block copy into (or out of) that local, whose struct is made as large as the copied range and aligned as the
  pieces show, its fields typed only by the other accesses (a vector copied into a local, its w set, the local
  passed on);
- a memset the original calls with `bl` right before the epilogue (knob `novalinit`): an explicit `memset()` is
  marked tail and would compile to `b memset`, so the call came from MemCpyOpt (a struct assigned from a
  value-initialised temporary) or LoopIdiom (a fill loop); with constant value and size it is written as
  `*reinterpret_cast<ZeroN_FUNC*>(p) = ZeroN_FUNC{};` for zero, a byte fill loop otherwise.

Knobs for source-order alternatives include `sink`, `callinline`, `revstores`, `globalfirst`, `swapif`,
`bytecast`, `ptrloop`, `forkjoin`, `stackpad`, `narrowparam`, `norange`, `longconst`, `argfirst`,
`inlmask_N`, `memberaddr`, `sortstores`, `vptrlast`, `copy64`, `loadfirst` (in a run of loads right before a
call, the loads whose values the call does not use come first: Clang's schedulers reorder independent loads, and
the order decides whether the two values share a callee-saved register) and `vptrfirst` (a vtable pointer store
moves up past the loads just before it that read the same object at or after its offset: an inlined member
destructor stores the member's vtable pointer first, and the scheduler hoists the field loads above it). Functions whose generated source would exceed 2 MB
are skipped (forking at every branch can grow a function's source exponentially).

## Queued next

1. Rerun `nm_probe.py` with the latest generator over the near misses and fix any that match in their
   hand-written units, keeping the hand-written names.
2. Keep sampling the largest mismatch groups (`mm_probe.py`) for shared causes. The remaining big groups are
   mostly register allocation and scheduling inside large functions.

## Source rules found by hand

Shapes the hand-matching sessions confirmed, for the generator and for hand work. Each held in the functions named.

- Global operators are called through their PLT stubs. `operator new[]` (`_Znam`) is defined at `0x71003ccc34`
  (`heap_operators.cpp` binds the name there to match the definition), but nothing calls that address directly: all
  three callers go through the stub at `0x7100600880`, because a call to a global operator can be preempted. One name
  stands for two addresses, so `units.json` keeps the definition and a unit that calls the operator maps the name to
  its stub for itself: `tools/add_symbols.py --map UNIT _Znam=0x7100600880` (da854).
- Memory-stream loaders: the stream is a local object called through a pointer (`MemStream memory; MemStream* stream =
  &memory;`, since calls on the object itself are devirtualised), one `read(&rec->field, nullptr, sizeof field)` per
  field in field order, the target id read into an `int` initialised to 0, and the record type built from the read
  list (`add x1, x21, #off` with `mov w3, #size`) (d89b0, d98e0, da854).
- A preheader value used only after a loop is sunk into the exit block by IndVarSimplify, which skips the instruction
  before each one it moves; a derived local right after it (`int table32 = table;`) makes the truncation the sunk value
  (da854).
- Byte pointers keep big member offsets as GEP offsets, which constant hoisting leaves alone (176ce0).
- A `memcpy` whose source address is computed first sets `x1` before `x0`: the source was in a local first (19c9a4).
- Some records are copied member by member, not by struct assignment (19c9a4).
- A range-for over a member array unrolls fully where an index loop unrolls by four (20e224); an unsigned counter used
  as an `int` index kept an unroll factor of two (1f9a98).
- Placement constructors return `this` (`mov x0, x19` at the end): the generator returns its first argument when `x0`
  is set back to it after the last call (425de0's pieces, `noretthis`).
- A byte fill that compiles to `bl memset` and then a loop counting only pointer and length is an explicit
  unlimited-buffer fast path with locals (`if (cap == 0) { char* p = ptr; int len = n0; for (...) { *p++ = c; len++; }
  ptr = p; n0 = len; } else { for (...) put(c); }`) (45b158).
- A three-case switch compares in source case order (3e934). A bounded table getter keeps its null `csel` only when the
  address is computed before the null choice (`T* p = &tbl[i]; return i < N ? p : nullptr;`).

## Rules carried over

Full check (`tools/check.py --update`) before every commit, zero masked relocations, local commits only, and only
files under `matching/` in a commit.
