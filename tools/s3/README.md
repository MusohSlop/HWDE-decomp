# Third-session helpers

Scripts the third session uses to fix generated source by hand, mostly for large constructors. They find the
checkout from their own location (`tools/s3` -> `matching`), read `data/units.json` and `data/functions.csv`, and
write scratch files under `build/s3` (rank.py under `build/s3rank`). None of them changes `check.py`,
`check_obj.py` or the generator, and none of them decides a match: a result only counts after the unit passes
the full `tools/check.py`.

Run them with the project's Python, `python -B -I tools/s3/SCRIPT ...`, from `matching/`.

## Comparing one function

- `try.py CPP ADDR [SYMJSON] [--name SYM] [--map NAME=ADDR ...] [--all] [--ctx N]` compiles one scratch file and
  diffs one function against the original: instruction diff count (difflib, registers included) and the
  differing runs. Symbols come from `units.json`, from SYMJSON (gen.py's `SYMOUT` format) and from `--map`;
  undefined names that end in `_<hex address>` (as the generator's placeholders do) map to that address.
  Reports unresolved relocations; it prints `MATCH` only for identical bytes.
- `permtry.py TEMPLATE ADDR SYM [--sym SYMJSON] [--map ...] --slot KEY=a|b|...` fills `{KEY}` placeholders of a
  template with every combination of options (`\n` for newlines) and runs try.py on each; stops at a match
  (written to `build/s3/perm_match.cpp`).
- `blocks.py`, `ours.py` and `regiondiff.py` are for long functions: `blocks.py` lists the differing runs with their lengths,
  `ours.py` writes our relocated disassembly in the original's address layout, and `regiondiff.py OURS.s ORIG.s START [END] [--abs]`
  prints a side-by-side diff of one region (`--abs` hides register numbers).
- `topotry.py SPEC.json` tries every order of a set of statements (with dependencies and chains that keep a
  relative order) in a template's `{REGION}`; for load and store order problems. The spec format is in the
  script's docstring.

## Ranking and the generator's source

- `rank.py OUT.tsv LO HI [--jobs N] [--knobs K] [--only FILE] [--limit N]` generates every unmatched function of
  LO to HI bytes into its own scratch unit (so a jump table maps), compiles it with a timeout and writes one row
  per function: class (as mm_tally), instruction diffs with and without registers, size difference, first
  differing pair, or the generator's failure reason. Use at most two jobs here.
- `vtscan.py OUT.tsv` lists unmatched functions that store a vtable (GOT load, `+0x10`) into `this`.
- `callers.py ADDR...` lists the `b`/`bl` sites that reach each address. `shapefind.py ADDR [QUALITY]` lists
  functions of the same size and instruction shape (registers and immediates abstracted).

## Rewriting generated source

- `ctor2class.py GEN.cpp ADDR OUT.cpp [--name CLASS] [--prefix]` turns gen.py's output for a constructor into a
  class: one-argument calls on `this+off` become member objects (with `int` constructor arguments when the call
  passes constants), the generator's element loops become member arrays (so Clang emits its own construction
  loop, which counts down the byte size), `memset` regions become value-initialised byte arrays, stores become
  fields initialised in declaration order, a vtable store at +0 becomes the class's own vtable and the
  vtable/-1/0 store groups of the layout handle (GOT `0x7100c22f00`) become `LayoutHandle` members (the
  `HandleState` base, then the vtable). With `--prefix` only the leading member initialisation becomes members
  and the rest of the function stays as the constructor body, run on the generated view of the object (`p0`).
  Prints the constructor's symbol and the `--map` arguments for the placeholder classes (`ObjNNN`, or the class
  of a constructor already named in `units.json`).
- `genfix.py IN.cpp OUT.cpp [loops] [panes] [handles]` rewrites generated source in place of a class: element
  loops as placement `new T[N]`, the 0x180-byte pane allocation (operator new `0x71005d4380`, `PaneBase`
  constructor, vtable GOT `0x7100c22f68`, three null fields) as `new PanelPane` from `event/layout_panes.h`, and
  layout-handle store groups as placement `new LayoutHandle` (through `handlify.py`).
- `fixalign.py IN.cpp OUT.cpp` marks generated struct fields that sit at an offset their type would not get (a `long`
  at `+...4`, which C++ pads to the next multiple of 8) as `__attribute__((packed))`, so they stay where the
  generator meant.
- `batchconv.py RANK.tsv OUT.tsv [--jobs N] [--knob K]` runs the generated version through genfix, ctor2class and
  ctor2class `--prefix` (each followed by genfix) for every generated function in a rank.py table, and copies
  matches to `build/s3/conv/match_ADDR.cpp` with their symbol file.

## Adding a function to a unit

- `addgen.py SRC.cpp ADDR SYMJSON UNIT [NOTE]` appends a generated-style (or converted) function to a unit:
  identical declarations, extern globals, includes and type definitions already in the unit are dropped, a
  callee declaration that clashes with one of another return type is renamed `callee2_NNN` (as gen.py does inside
  a unit), the function's symbols and the function itself are registered in `units.json`, and the unit is built
  and checked (with `tools/gen/autosym.py` for the callee names). NOTE becomes the comment over the function.
- `dropunit.py UNIT` removes a unit's entry from `units.json` (its symbols stay).

## One address, start to end

```
python -B -I tools/s3/rank.py build/s3/one.tsv 8 1000000 --only build/s3/one.txt    # one.txt: the hex offset
python -B -I tools/s3/ctor2class.py build/s3rank/r28ee38_d.cpp 28ee38 build/s3/c28ee38.cpp
python -B -I tools/s3/try.py build/s3/c28ee38.cpp 28ee38 build/s3rank/r28ee38_d.json --name _ZN11Class28ee38C2Ev
python -B -I tools/s3/addgen.py build/s3/c28ee38.cpp 28ee38 build/s3rank/r28ee38_d.json misc/s3_functions03.cpp
python -B -I tools/check.py --update
```
