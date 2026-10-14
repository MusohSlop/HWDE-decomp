# Generator handoff

State of the generated-unit work at commit time, for a session picking it up.

## Where the tools are

The generator and its drivers are local scratch scripts, not part of this repository. They live in the
session scratchpad under `%TEMP%\claude\F--Claude-Decomps-project1\a4886e8e-540c-4eed-9f51-3566a18d420d\scratchpad\tools`.

- `gen_allNN.py` is the generator, one file per step (`gen_all47.py` is the latest). Each `patch_allNN.py`
  derives `gen_allNN.py` from the previous one and documents the change in its first lines.
- `rv_par.py GEN UNIT LO HI [KNOBFILE]` runs the generator over unmatched functions of LO to HI bytes. It splits
  the candidates into units of about 25 functions, compiles them in parallel with a timeout per compile, tries
  each knob set in turn, and writes every exact match into UNIT under its winning knobs. Mismatches are not kept.
  Chunks that time out are logged to `rvpar_slow.txt` next to the tools directory. `run_variants8.py` is the older
  single-unit version.
- `mm_probe.py GEN LO HI` classifies the first differing instruction pair of every mismatch.
- `probe_one.py GEN ADDR` generates one function into a scratch unit, prints its diff and source, and removes the
  scratch unit again.
- `nm_probe.py GEN FILE` does the same for the logged near misses (`NEARMISS=1`) under several knob sets, so a
  generated match can guide a fix of the hand-written version.
- Environment switches of the generator: `ONLY`, `EXCLUDE`, `VARIANT`, `VARIANT_MAP`, `DRYRUN` (no symbol
  writes), `FAILDUMP` (one line per skipped function with its reason), `TRACE` (re-raise internal errors),
  `NEARMISS`.

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
`bytecast`, `ptrloop`, `forkjoin`, `stackpad`, `narrowparam`, `norange`, `longconst`, `argfirst` and
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
