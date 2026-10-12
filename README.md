# Matching decompilation

Byte-for-byte matching work for update 1.0.1 `main`. The behavior-equivalent reconstruction in `src/` stays untouched and serves as the semantic reference. See `handoff/MATCHING_HANDOFF.md` for the plan and `docs/toolchain.md` for compiler hashes.

## Compile and check

```
.tools/clang-3.9.1/bin/clang++.exe -O3 -g -mcpu=cortex-a57+fp+simd+crypto+crc -mno-implicit-float -stdlib=libc++ -fPIC -fstandalone-debug --target=aarch64-linux-elf -std=c++14 -c matching/src/event/resource_queue_controls.cpp -o matching/build/resource_queue_controls.o
python -B -I matching/tools/check_obj.py matching/build/resource_queue_controls.o --map .bss=c8af40 _Z21resource_queue_activev=2589b4 _Z29resource_queue_callback_statePv=25970c _Z32resource_queue_callback_in_statePvj=2597a8 _Z29resource_queue_callback_countv=25984c
```

`check_obj.py` compares each named function with `main.memory.bin`. It applies ADRP, ADD/LDST lo12 and B/BL relocations whose targets have an original address (compared functions, plus each `--map NAME=ADDRESS`), then compares every word in full. GOT relocations and unmapped targets are masked and listed as unresolved. `matching/build/` holds objects and is not committed.

## Results

| Address | Function | Clang 3.9.1 | Clang 4.0.1 |
| --- | --- | --- | --- |
| `2589b4` | `resource_queue_active` | match | match |
| `25970c` | `resource_queue_callback_state` | match | mismatch: match tails become separate `mov`+`b` blocks (46 words, not 39) |
| `2597a8` | `resource_queue_callback_in_state` | match | mismatch: same tail layout (48 words, not 41) |
| `25984c` | `resource_queue_callback_count` | match | mismatch: `mov w12, #1` + `csel w11, w12, w11, eq` becomes `csinc w11, w11, wzr, ne` (29 words, not 30) |
| `2170fc` (= `217070`) | `DemoSequence::clear` | near miss | same as 3.9.1 |

The registry must be an internal-linkage (or hidden) global: the original uses direct ADRP/ADD, not the GOT.

`2170fc` near miss: the prologue (`str x21, [sp, #-0x30]!` / `stp x20, x19` / `stp x29, x30` / `add x29, sp, #0x20`), the epilogue, the `orr`-immediate constants and the `umaddl` loop all match. The candidate peels the first release explicitly, which reproduces the original loop. It is one instruction short (34 words, not 35). The original loads `items` into `x1`, uses `mov x0, x1` for the first release and reuses `x1` for the `count == 0` path to the free call. The candidate loads into `x0`, so the `count == 0` path reloads `items`. In the original the reload sits on a separate loop-exit block that the candidate's control flow lacks.
