# Matching decompilation

Byte-for-byte matching work for update 1.0.1 `main`. The behavior-equivalent reconstruction in `src/` stays untouched and serves as the semantic reference. See `handoff/MATCHING_HANDOFF.md` for the plan and `docs/toolchain.md` for compiler hashes.

## Compiler and flags

Clang 3.9.1 (`.tools/clang-3.9.1`) with:

```
-O3 -g -mcpu=cortex-a57+fp+simd+crypto+crc -mno-implicit-float -stdlib=libc++ -fPIC -fstandalone-debug --target=aarch64-linux-elf -std=c++14 -fno-strict-aliasing
```

`-fno-strict-aliasing` is required. Without it, `2173c4` reloads the item's point pointer only once and swaps x19/x20. With it, `2173c4` matches and the earlier matches are unchanged. Koei Tecmo, not Nintendo, built this game, so its flags need not equal the BotW/SMO set.

## Compile and check

```
.tools/clang-3.9.1/bin/clang++.exe <flags above> -c matching/src/event/resource_queue_controls.cpp -o matching/build/resource_queue_controls.o
python -B -I matching/tools/check_obj.py matching/build/resource_queue_controls.o --map .bss=c8af40 _Z21resource_queue_activev=2589b4 _Z29resource_queue_callback_statePv=25970c _Z32resource_queue_callback_in_statePvj=2597a8 _Z29resource_queue_callback_countv=25984c
python -B -I matching/tools/check_obj.py matching/build/demo_sequence_item.o _ZN16DemoSequenceItem4loadEP9DemoOwnerPK22DemoSequenceItemSource=2173c4
```

`check_obj.py` compares each named function with `main.memory.bin`. It applies ADRP, ADD/LDST lo12 and B/BL relocations whose targets have an original address (compared functions, plus each `--map NAME=ADDRESS`), then compares every word in full. GOT relocations and unmapped targets are masked and listed as unresolved. `matching/build/` holds objects and is not committed.

`data/functions.csv` lists all 17,276 baseline inventory entries (`Address,Quality,Size,Name`; quality `O` match, `m` minor, `M` major, `U` undecompiled, `L` library). `tools/seed_functions.py` regenerates it from `functions.tsv` and keeps existing qualities and names.

## Results

| Address | Function | Clang 3.9.1 | Clang 4.0.1 |
| --- | --- | --- | --- |
| `2589b4` | `resource_queue_active` | match | match |
| `25970c` | `resource_queue_callback_state` | match | mismatch: match tails become separate `mov`+`b` blocks (46 words, not 39) |
| `2597a8` | `resource_queue_callback_in_state` | match | mismatch: same tail layout (48 words, not 41) |
| `25984c` | `resource_queue_callback_count` | match | mismatch: `mov w12, #1` + `csel w11, w12, w11, eq` becomes `csinc w11, w11, wzr, ne` (29 words, not 30) |
| `2173c4` | `DemoSequenceItem::load` | match (needs `-fno-strict-aliasing`) | not tried |
| `2170fc` (= `217070`) | `DemoSequence::clear` | near miss (`m`) | same as 3.9.1 |
| `217294` | `DemoSequence::sample` | near miss (`M`) | not tried |

Total: 5 functions, 720 bytes matched.

### Source-shape lessons

- The queue registry must be an internal-linkage (or hidden) global: the original uses direct ADRP/ADD, not the GOT.
- `2173c4`: the six header words are an array (`float header[6]`) copied in a loop. Named fields of different structs get struct-path TBAA, and their loads merge into 64-bit loads. Each point is copied word by word through per-iteration references (`DemoPoint& dst = points[i]`). A struct assignment becomes a 64-bit `memcpy` expansion. Indexing `points[i].w[k]` directly reloads `points` before every word.

### Near misses

`2170fc`: the prologue (`str x21, [sp, #-0x30]!` / `stp x20, x19` / `stp x29, x30` / `add x29, sp, #0x20`), the epilogue, the `orr`-immediate constants and the `umaddl` loop all match. The candidate peels the first release explicitly, which reproduces the original loop. It is one instruction short (34 words, not 35). The original loads `items` into `x1`, uses `mov x0, x1` for the first release and reuses `x1` for the `count == 0` path to the free call. The candidate loads into `x0`, so the `count == 0` path reloads `items`. In the original the reload sits on a separate loop-exit block that the candidate's control flow lacks.

`217294` (candidate: 71 words; original: 76):
- **What matches:** the index check, the 64-bit item address, the `fcvtzu` count, the scan loop, the interpolation arithmetic (`fsub`/`fdiv`/`fmax`/`fmin`) and the final `fcsel` clamp all reproduce.
- **Differences:**
  1. The original gives the `n == 0` path its own copy of the clamp and return (`ldp s0, s1, [x8, #0x10]` ... `ret`). The candidate shares one clamp tail.
  2. On the scan's not-found path, the original keeps a redundant `mov w10, w11; cbz w10`. Our compiler drops it because it knows `n != 0`.
  3. The interpolation schedules `1 - f` before the first `fmul`.
- **Tried:** moving the `n == 0` test after the loop (variant S1) matches the prefix through the loop, but then the `n == 0` test reappears on the not-found path. An early return with an inline clamp helper, a nested `j == 0` / `n == 0` test and four orders of the lerp expression all failed to close the gap.
