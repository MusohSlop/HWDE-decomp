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
  image offsets) restrict the address range. Timed-out chunks are logged to `build/rvpar_slow.txt`.
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
  arithmetic and bit-field instructions.

Knobs for source-order alternatives include `sink`, `callinline`, `revstores`, `globalfirst`, `swapif`,
`bytecast`, `ptrloop`, `forkjoin`, `stackpad`, `narrowparam`, `norange`, `longconst`, `argfirst`,
`inlmask_N`, `memberaddr`, `sortstores` and `vptrlast`. Functions whose generated source would exceed 2 MB
are skipped (forking at every branch can grow a function's source exponentially).

## Queued next

1. Rerun `nm_probe.py` with the latest generator over the near misses and fix any that match in their
   hand-written units, keeping the hand-written names.
2. Keep sampling the largest mismatch groups (`mm_probe.py`) for shared causes. The remaining big groups are
   mostly register allocation and scheduling inside large functions.

## Rules carried over

Full check (`tools/check.py --update`) before every commit, zero masked relocations, local commits only, and only
files under `matching/` in a commit.
