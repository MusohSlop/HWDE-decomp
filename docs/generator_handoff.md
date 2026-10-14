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
- `mm_probe.py gen.py LO HI` classifies the first differing instruction pair of every mismatch.
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
  `ldrsh` shows an int parameter.

Knobs for source-order alternatives include `sink`, `callinline`, `revstores`, `globalfirst`, `swapif`,
`bytecast`, `ptrloop`, `forkjoin`, `stackpad`, `narrowparam`, `norange`, `longconst`, `argfirst`,
`inlmask_N`, `memberaddr`, `sortstores`, `vptrlast` and `copy64`. Functions whose generated source would exceed 2 MB
are skipped (forking at every branch can grow a function's source exponentially).

## Queued next

1. Rerun `nm_probe.py` with the latest generator over the near misses and fix any that match in their
   hand-written units, keeping the hand-written names.
2. Keep sampling the largest mismatch groups (`mm_probe.py`) for shared causes. The remaining big groups are
   mostly register allocation and scheduling inside large functions.

## Rules carried over

Full check (`tools/check.py --update`) before every commit, zero masked relocations, local commits only, and only
files under `matching/` in a commit.
