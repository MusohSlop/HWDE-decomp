# Second matching session

How a second Claude Code session works next to the main one on this PC without touching the same files or racing on
git. The main session keeps `master`; the second session works in its own worktree and branch, and only the main
session merges and commits to `master`.

## Worktree

- Path: `F:\Claude Decomps\project1\worktrees\s2` (ignored locally through `.git/info/exclude`, so it never shows up
  in `git status` of the main folder).
- Branch: `matching-s2`, started from `master`.
- The worktree reaches the toolchain and the game image through directory junctions that `.gitignore` already
  covers: `worktrees\s2\.tools` points to `F:\Claude Decomps\project1\.tools`, and
  `worktrees\s2\analysis\extracted\update\decompressed` points to the folder of the same name in the main tree.
  Nothing else is linked or copied; key material is never read, linked or copied.
- `tools/check.py` and the other repository tools find everything relative to the worktree, so they work there
  unchanged. Run every command from `worktrees\s2\matching` or with absolute paths inside it.
- Generator scripts for the second session are copies in `F:\Claude Decomps\project1\worktrees\s2_tools`, with
  their paths pointing at the worktree. The second session edits only those copies; the main session keeps its own
  copies in its scratchpad. See `docs/generator_handoff.md` for what each script does.

## Split of the work

| | Main session | Second session |
|---|---|---|
| Unmatched functions, generator band runs | addresses below `0x7100380000` | addresses from `0x7100380000` up |
| Generator failure classes to work on | base kind, loops (shape, nesting, carried values), anything found in the band runs | overlapping and unaligned constant stores (the rest of "field clash"), vector constants from the literal pool ("constant outside pool", "vector addressing"), float register forms ("reg s0", "float addressing") |
| Near misses (hand-written units, quality `m`) | none | all of them; fix the hand-written source and keep its names |
| New generated units | `misc/variant_functionsNN.cpp` | `misc/s2_functionsNN.cpp` |
| Shared files | `data/units.json`, `data/functions.csv`, `README.md`, `docs/generated_units.md`, `docs/progress.png` on `master` | the same files, on `matching-s2` only |

Each session restricts its band runs to its own address range (the runners take the range through the
`RV_ADDR_LO` and `RV_ADDR_HI` environment variables, as hex image offsets: the main session uses `0`-`380000`, the
second session `380000`-`800000`). A generator fix found by one session is passed on in the next report, so the
other session can port it.

## CPU

The PC has 16 logical cores. Band runs: the main session uses `RV_JOBS=8`, the second session `RV_JOBS=6`, leaving
two cores for single compiles, checks and the desktop. Only one session runs a full near-miss probe or a whole-band
rerun at a time; say so in the report before starting one.

## Merge procedure (main session only)

1. The second session commits on `matching-s2` with the usual rules (full check before every commit, zero masked
   relocations, author `Claude <claude@local.invalid>`, only files under `matching/`), and reports the commit.
2. In the main folder: `git merge --no-commit matching-s2`.
3. Conflicts in `data/units.json` are resolved with `merge_units.py` (in the main session's scratchpad tools, a
   copy is in `worktrees\s2_tools`): it starts from `master`'s version, adds every unit and symbol from the branch,
   and stops on any name defined with two different values. Conflicts in `README.md` and
   `docs/generated_units.md` keep the rows of both sides. `data/functions.csv` and `docs/progress.png` are
   regenerated, not merged: take `master`'s version, then run `tools/check.py --update` and
   `tools/progress_map.py --readme` and the README score script.
4. Full check on the merged tree. Commit the merge only when it is clean (no unresolved relocations, no lost
   matches compared with both sides).
5. The second session then runs `git merge master` in its worktree before its next commit, so the branches stay
   close.

Neither session pushes anything.
