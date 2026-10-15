# Third-session helpers

Scripts the third session uses to fix generated source by hand, mostly for large constructors. They find the
checkout from their own location (`tools/s3` -> `matching`), read `data/units.json` and `data/functions.csv`, and
write scratch files under `build/s3` (rank.py under `build/s3rank`). None of them changes `check.py`,
`check_obj.py` or the generator, and none of them decides a match: a result only counts after the unit passes
the full `tools/check.py`.

Run them with the project's Python, `python -B -I tools/s3/SCRIPT ...`, from `matching/`.

## Comparing one function

- `try.py CPP ADDR [SYMJSON] [--name SYM] [--map NAME=ADDR ...] [--all] [--ctx N] [--work DIR]` compiles one
  scratch file and diffs one function against the original: instruction diff count (difflib, registers included)
  and the differing runs. Symbols come from `units.json`, from SYMJSON (gen.py's `SYMOUT` format) and from
  `--map`; undefined names that end in `_<hex address>` (as the generator's placeholders do) map to that address.
  A mangled free function's name is cut at its length prefix first, so a parameter code after the address (`callee_33840cl`) is not read as part of it (rank.py does the same).
  Reports unresolved relocations; it prints `MATCH` only for identical bytes. The object file goes to DIR
  (default `build/s3`), never next to the source.
- `permtry.py TEMPLATE ADDR SYM [--sym SYMJSON] [--map ...] [--sep SEP] [--work DIR] --slot KEY=a|b|...` fills
  `{KEY}` placeholders of a template with every combination of options (`\n` for newlines) and runs try.py on
  each; stops at a match (written to `DIR/perm_match.cpp`, exit code 0; 1 without a match).
- `voltry.py CPP ADDR SYMJSON [--max K] [--work DIR]` (or `--list FILE` with lines `ADDR CPP SYMJSON [SYM]`) marks struct fields of a generated source `volatile`, every
  subset of up to K fields (default 2), and stops at a match (`DIR/vol_match.cpp`). AArch64's scheduler moves a
  store past the function's other memory accesses only when it can prove them disjoint, never a volatile one, so
  this finds stores the original keeps in source order (`5f80bc`, `5f37e8`).
- `blocks.py`, `ours.py` and `regiondiff.py` are for long functions: `blocks.py` lists the differing runs with their lengths,
  `ours.py` writes our relocated disassembly in the original's address layout, and `regiondiff.py OURS.s ORIG.s START [END] [--abs]`
  prints a side-by-side diff of one region (`--abs` hides register numbers).
- `floattry.py CPP ADDR SYMJSON [--max K] [--work DIR]` (or `--list FILE`) retypes `int` fields the function
  stores zero to as `float`, up to K at a time: Clang merges adjacent int stores into one wider store but not
  stores of different types, so a field that is a float in the original keeps its own `str wzr` (`3322ac`); a
  match goes to `DIR/float_match.cpp`.
- `ordtry.py CPP ADDR SYMJSON [--limit N] [--work DIR]` (or `--list FILE`) tries orders of a generated function's
  straight-line statements (the whole body, or those before its first branch or loop) without a spec: calls keep their order, the statements between two calls are
  permuted (a use after the statement that sets the local), up to N orders; a match goes to `DIR/ord_match.cpp`.
  Run it on the `fixalign.py` output for functions with misaligned 8-byte stores (`c5df8`, `1f18e8`).
- `topotry.py SPEC.json [--work DIR]` tries every order of a set of statements (with dependencies and chains that
  keep a relative order) in a template's `{REGION}`; for load and store order problems. The spec format is in the
  script's docstring; a match goes to `DIR/topo_match.cpp` (exit code 0).
- `irsbatch.py LIST [--iters N] [--loads-free] [--plain] --work DIR` runs the fifth session's `tools/s5/irsearch.py --groups` (used as is; `--loads-free` is passed on, `--plain` runs its plain mode instead of `--groups`)
  over the lines `ADDR CPP [SYMS] [FUNC] [NAME=ADDR ...]` of LIST, one after another; each source goes to irsearch
  as a .cpp, so its IR is emitted with -g and use-list orders like the unit compile. A match is copied to
  `DIR/irs_match_ADDR.ll`. Some functions' -g IR does not compile back (clang 3.9.1 crashes, `761d8`); irsearch
  then stops at its first score.

## Unattended searches

`bgsearch.py` runs one of the searches above (permtry, topotry, voltry, ordtry, floattry, or `irsbatch.py`) detached through `tools/lowprio.py` (idle
priority, one job, as `docs/second_session.md` asks of unattended searches), so it only uses spare CPU, with its
own work folder under `build/s3_perm/NAME/` (ignored by git; nothing tracked is touched). At most two run at a
time.

```
python -B -I tools/s3/bgsearch.py start 351428-vol voltry.py build/s3/h351428.cpp 351428 build/s3/h351428.json --max 3
python -B -I tools/s3/bgsearch.py list          # NAME, pid, running or exit code, match file, last log line
python -B -I tools/s3/bgsearch.py stop 351428-vol
```

`start` appends `--work build/s3_perm/NAME/work` to the search's arguments, writes its output to
`build/s3_perm/NAME/log.txt`, its PID to `build/s3_perm/NAME/pid` and `build/s3_perm/pids.txt`, and its exit code
to `build/s3_perm/NAME/exit.txt` when it ends (0: it found a match, in `NAME/work/perm_match.cpp`,
`topo_match.cpp`, `vol_match.cpp`, `ord_match.cpp`, or `*_match_ADDR.cpp` for a `--list` run; `irs_match_ADDR.ll`
from irsbatch.py, an IR order still to be written as source). A hit is only a candidate: put the source into its unit (addgen.py or by
hand), register its symbols, and run `tools/check.py UNIT`, then the full `tools/check.py`, before committing it.
Anything else unattended (a rank.py or batchconv.py batch) goes through `tools/lowprio.py --jobs 1 -- ...` as
well.

## Ranking and the generator's source

- `rank.py OUT.tsv LO HI [--jobs N] [--knobs K] [--only FILE] [--limit N]` generates every unmatched function of
  LO to HI bytes into its own scratch unit (so a jump table maps), compiles it with a timeout and writes one row
  per function: class (as mm_tally), instruction diffs with and without registers, size difference, first
  differing pair, or the generator's failure reason. Use at most two jobs here.
- `vtscan.py OUT.tsv` lists unmatched functions that store a vtable (GOT load, `+0x10`) into `this`.
- `diffsig.py BATCH.tsv [MAXN]` prints, for each function of a batchconv.py table at most MAXN instructions off, the
  differing instructions of its best variant with registers abstracted, one line per function, to group near
  misses by cause.
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
  A no-argument call on `this` before the class's own vtable store becomes its polymorphic base (constructed
  with C2; the members start where the next one does), the element-pointer loop with a byte count is a member
  array too, and a store, memset or layout handle field (id, counters) set after a member at a higher offset
  was constructed becomes a body statement in the original's order (initialisers run in declaration order).
  Prints the constructor's symbol and the `--map` arguments for the placeholder classes (`ObjNNN`, or the class
  of a constructor already named in `units.json`). A field at an offset its type would not get is declared
  `__attribute__((packed))` (and fixalign.py's packed fields are read). A run of equal no-argument members
  becomes an array when the
  original's vtable store post-increments (`str x8, [xN], #K`) to the run's second member: Clang folds into that
  store the newest `this`+K address with K under 256, which for single members is the last one under 256 and for
  an array the second element (`--no-post-arrays` keeps single members).
- `dtor2class.py ADDR OUT.cpp [--name CLASS]` writes a destructor made of member destructor calls, layout handles
  and a base destructor as a class, from the original's code alone (no generator): it emulates the function from
  its entry (loops run their iterations), records the vtable store, each handle (the handle vtable store, then
  the release call through it) and each member destructor call with its `this` offset, and lays them out by offset
  (handles destroyed in a loop become an array of slots of the loop's stride). The handle class it uses is in
  `dtor_prelude.h` (`--no-prelude` leaves it out and names the part types after the function, for a unit that
  has the prelude). A call on `this` before anything is destroyed becomes a method called in the body, a release
  through `br` ends it, and a run of member destructor calls whose last address is kept in a register is an array.
  Prints `name` and `maps` like ctor2class; exits 1 when the function does other things (`31a47c`, `3ba38c`,
  `2e2dcc`, `299de0`).
- `genfix.py IN.cpp OUT.cpp [loops] [panes] [handles]` rewrites generated source in place of a class: element
  loops as placement `new T[N]`, the 0x180-byte pane allocation (operator new `0x71005d4380`, `PaneBase`
  constructor, vtable GOT `0x7100c22f68`, three null fields) as `new PanelPane` from `event/layout_panes.h`, and
  layout-handle store groups as placement `new LayoutHandle` (through `handlify.py`).
- `onceptr.py IN.cpp OUT.cpp` computes a stored field's address once when the same `p0 + X` is passed on soon
  after (`auto* hX = &p0->field_X; *hX = V; ... f(hX)`): one IR value, so Clang folds the store into a pre-indexed
  `str xA, [xB, #X]!` and passes `xB` on, as the original does where an inlined handle destructor stores its vtable
  and then releases itself (`37af54`, `34d974`, `2a6fd0` and seven more). Same contract as genfix.py; prints
  `onceptr N` (the number of rewrites).
- `argfix.py IN.cpp OUT.cpp ADDR [CALLEE...]` gives back the `this`+offset argument the generator dropped from calls
  it wrote as `callee_X();` (destructors' member calls, often through a thunk the generator thinks takes no
  arguments): the original's call sites are read in order, following `mov`/`movk`/`add` into `x0` from `this`.
  Without CALLEE it fixes every callee declared without parameters (`356154`, with onceptr).
- `fixalign.py IN.cpp OUT.cpp` marks generated struct fields that sit at an offset their type would not get (a `long`
  at `+...4`, which C++ pads to the next multiple of 8) as `__attribute__((packed))`, so they stay where the
  generator meant.
- `batchconv.py RANK.tsv OUT.tsv [--jobs N] [--knob K]` runs the generated version (after fixalign) through
  genfix, onceptr, argfix + onceptr, ctor2class and ctor2class `--prefix` (the class forms followed by genfix) for
  every generated function in a rank.py table, and copies matches to `build/s3/conv/match_ADDR.cpp` with their
  symbol file.

### Command-line contract of the converters

The generator's `ctorclass` knob calls these three, so their interface stays fixed (changes are announced in the
third session's reports). Paths may be absolute or relative to the caller's directory; the scripts find
`units.json` and the original image from their own location. No prompts.

- `ctor2class.py GEN.cpp ADDR OUT.cpp [--name CLASS] [--prefix] [--handle-got GOT] [--no-post-arrays]`: reads
  gen.py's output for the function `call_ADDR` (ADDR in hex), writes OUT.cpp and exits 0, printing
  `name SYMBOL` (the constructor's mangled name) and `maps --map NAME=ADDR ...` (symbols for the classes it
  declared). Exits 1 without writing OUT.cpp when the function is missing or has statements it cannot convert
  (listed after `UNHANDLED:`).
- `genfix.py IN.cpp OUT.cpp [loops] [panes] [handles]` (all three when none is named): writes OUT.cpp (may be
  IN.cpp) and exits 0, also when nothing changed; nonzero for an unknown fix name, unreadable input or a failed
  handlify step.
- `handlify.py IN.cpp OUT.cpp [GOT]` (GOT of the handle vtable, default `c22f00`): writes OUT.cpp and exits 0;
  nonzero on failure.

## Adding a function to a unit

- `addgen.py SRC.cpp ADDR SYMJSON UNIT [NOTE]` appends a generated-style (or converted) function to a unit:
  identical declarations, extern globals, includes and type definitions already in the unit are dropped, a
  callee declaration that clashes with one in the unit (another return type or parameter list) moves, with all of
  the new code's overloads of that callee, to one new prefix `calleeK_NNN` that clashes with none of them (as gen.py
  does inside a unit), the function's symbols and the function itself are registered in `units.json`, and the unit is built
  and checked (with `tools/gen/autosym.py` for the callee names). NOTE becomes the comment over the function.
- `dropunit.py UNIT` removes a unit's entry from `units.json` (its symbols stay).

## Template families in the third session's scope

- `famscan.py OUT.txt [--skip FILE ...] [--keep HEX ...]` groups every unmatched function by the abstracted opcode
  sequence of `tools/s4/families.py` (shape code copied from there) but keeps what that scan leaves out: families
  with a copy in `docs/s3_scope.txt`, a constructor-shaped copy or a copy over 1,500 bytes. Families with a copy in a
  SKIP file (another session's claims or family list) or at a `--keep` address (held elsewhere) are dropped. Each
  line marks copies in the scope (`*`) and constructor-shaped ones (`+`).

## One address, start to end

```
python -B -I tools/s3/rank.py build/s3/one.tsv 8 1000000 --only build/s3/one.txt    # one.txt: the hex offset
python -B -I tools/s3/ctor2class.py build/s3rank/r28ee38_d.cpp 28ee38 build/s3/c28ee38.cpp
python -B -I tools/s3/try.py build/s3/c28ee38.cpp 28ee38 build/s3rank/r28ee38_d.json --name _ZN11Class28ee38C2Ev
python -B -I tools/s3/addgen.py build/s3/c28ee38.cpp 28ee38 build/s3rank/r28ee38_d.json misc/s3_functions03.cpp
python -B -I tools/check.py --update
```
