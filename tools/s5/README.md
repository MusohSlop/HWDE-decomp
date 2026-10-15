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
