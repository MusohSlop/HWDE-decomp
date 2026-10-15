# Fourth-session helpers

Scripts the fourth session uses for hand-matching non-constructor functions over 1,500 bytes below `0x7100380000`.
They find the checkout from their own location (`tools/s4` -> `matching`) and write scratch files under `build/s4`.
None of them changes `check.py`, `check_obj.py`, the generator or the third session's tools, and none of them
decides a match: a result only counts after the unit passes the full `tools/check.py`. The third session's tools
(`tools/s3/`, see its README) do most of the comparing; these only add what the fourth session's split needs.

Run them with the project's Python, `python -B -I tools/s4/SCRIPT ...`, from `matching/`.

- `cands.py OUT.txt [--lo HEX] [--hi HEX] [--min N] [--max N] [--skip FILE ...]` lists the session's candidates:
  unmatched functions of more than MIN bytes (default 1,500) in the address range (default `0`-`380000`), without
  the constructor-shaped ones (the vtable-store scan of `tools/s3/vtscan.py`) and without every address in the SKIP
  files (claims and scope files of the other sessions). Feed it to `tools/s3/rank.py --only` for the ranking.
- `bytep.py IN.cpp OUT.cpp ADDR [PARAM...]` rewrites the `long pN` parameters of a generated function (default
  `p0`) as `unsigned char*`, so `pN + C` is a byte-pointer offset instead of integer arithmetic. Clang's constant
  hoisting rebases large integer offsets on a shared callee-saved base; offsets of a pointer are left alone, as in
  the original's member addresses (`176ce0`).
- `perm.py TEMPLATE ADDR NAME OUTDIR [--sym SYMJSON] [--map ...] [--slot KEY=a|b ...] [--slots SLOTS.json]` is an
  unattended permutation search: every combination of the `{KEY}` options is compiled with `tools/s3/try.py`, one
  line per combination goes to `OUTDIR/log.txt`, the best source to `OUTDIR/best.cpp`, a match to
  `OUTDIR/match.cpp`. All scratch files stay in OUTDIR (outside the worktree, for example
  `worktrees\s4_perm\ADDR\`). Start it through `tools/lowprio.py` so it runs at idle priority; a hit still has to
  go into its unit and pass the full check.
- `triage.py LIST.txt [OUT.tsv]` gives shape metrics (conditional branches, loops, float instructions, calls, jump
  tables, frame size) for the functions in LIST, sorted by a rough difficulty score, to pick quick hand-writes.
- `copymap.py ADDR [SRCREG DSTREG]` lists the copied pieces (source offset, destination offset, width) of a
  straight-line copy function, to read the layout of serialisers such as `11298c`.
- `ctorlayout.py ADDR [--size TARGET=BYTES ...] [--all] [--cpp]` reads a constructor's member layout from the
  original's code, for the large vtable-less constructors that `tools/s3/vtscan.py` does not count (`e25dc`,
  `ffdf8`): it follows `this` and the constants built with mov/movk through the function, takes each call on
  `this`+offset as a member constructor, each `this`-based store as a field, and each of Clang's two array loops
  (a byte count counted down, a pointer compared with the end) as a member array (several calls per iteration:
  an array of structs), and stops at the first instruction it does not model (the body). It prints the members
  in order with the gaps between them, runs of one constructor merged into arrays (Clang fully unrolls arrays of
  up to 70 elements into separate calls, so a straight run is an array as well); `--cpp` prints them as member
  declarations with byte pads for the gaps and a struct per multi-call loop.
