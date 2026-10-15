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
- Generator scripts: the second session started with copies in `F:\Claude Decomps\project1\worktrees\s2_tools`.
  The generator and its drivers are now also committed in `matching/tools/gen/` and find their checkout from their
  own location, so in the worktree they work on the worktree's tree unchanged. Each session edits generator code
  only on its own branch; a fix one session wants to share is merged like any other change. See
  `docs/generator_handoff.md` for what each script does.

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

The PC has 16 logical cores. Band runs: the main session uses `RV_JOBS=6`, the second session `RV_JOBS=6` and the
third session `RV_JOBS=2`, leaving two cores for single compiles, checks and the desktop. Only one session runs a full near-miss probe or a whole-band
rerun at a time; say so in the report before starting one.

## Merge procedure (main session only)

1. The second session commits on `matching-s2` with the usual rules (full check before every commit, zero masked
   relocations, author `Claude <claude@local.invalid>`, only files under `matching/`), and reports the commit.
2. In the main folder: `git merge --no-commit matching-s2`.
3. Conflicts in `data/units.json` are resolved with `tools/gen/merge_units.py OURS THEIRS OUT BASE`, where BASE
   is the file at `git merge-base master matching-s2`: it starts from `master`'s version, adds every unit and symbol
   from the branch, drops entries the branch deleted and `master` left unchanged (so a function the branch moved to
   another unit, for example to give a lookup table its own `.rodata` map, ends up only in the new unit), and stops
   on any name defined with two different values or any function listed in two units. Conflicts in `README.md` and
   `docs/generated_units.md` keep the rows of both sides. `data/functions.csv` and `docs/progress.png` are
   regenerated, not merged: take `master`'s version, then run `tools/check.py --update` and
   `tools/progress_map.py --readme` and the README score script.
4. Full check on the merged tree. Commit the merge only when it is clean (no unresolved relocations, no lost
   matches compared with both sides).
5. The second session then runs `git merge master` in its worktree before its next commit, so the branches stay
   close.

## Third session (hand matching)

A third session works the same way from `F:\Claude Decomps\project1\worktrees\s3` on branch `matching-s3`, set up
with the same recipe (junctions to `.tools` and the decompressed image, nothing else linked or copied).

- It hand-matches every unmatched function over 1,500 bytes in both address ranges, the giants over 6,000 bytes
  included (those at the highest effort). Functions on the second session's near-miss list stay with the second
  session.
- Order: functions that generate but mismatch first, closest first; then the ones that do not generate; then the
  giants.
- It never edits `matching/tools/gen/*`, `tools/check.py` or `tools/check_obj.py`; the generator stays with the main
  and second sessions.
- New units: `misc/s3_functionsNN.cpp`. CPU: `RV_JOBS=2`.
- It keeps `matching/docs/s3_claims.txt` in its worktree, listing the addresses it is working on and has matched.
  Generator runs of the other two sessions skip those: `tools/gen/run_bands.py` drops every address in the file
  named by `RV_SKIP` (hex image offsets or full `0x71...` addresses, any separators), so both other sessions run
  with `RV_SKIP=F:\Claude Decomps\project1\worktrees\s3\matching\docs\s3_claims.txt`.
- It reports its commits to the coordinator, and the main session merges `matching-s3` with the procedure above.
  A function matched on both sides keeps `master`'s copy: before the units merge, its entry is dropped from the
  branch's `units.json` and its definition from the branch's unit.

Neither session pushes anything.
