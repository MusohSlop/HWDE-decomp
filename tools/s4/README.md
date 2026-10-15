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
