# Matching decompilation

Byte-for-byte matching work for update 1.0.1 `main`. The behavior-equivalent reconstruction in `src/` stays untouched and serves as the semantic reference. See `handoff/MATCHING_HANDOFF.md` for the plan and `docs/toolchain.md` for compiler hashes.

## Layout

| Path | Contents |
| --- | --- |
| `data/units.json` | Compiler, flags, original addresses of external symbols, and per unit the functions and file-static variables with their original addresses |
| `data/functions.csv` | All 17,276 baseline inventory entries: `Address,Quality,Size,Name`, quality `O` match, `m` minor, `M` major, `U` undecompiled, `L` library |
| `include/`, `src/` | Matching C++ by subsystem |
| `tools/check.py` | Compiles units and compares them; `--update` writes results to `functions.csv`; `--diff` prints instruction diffs |
| `tools/check_obj.py` | Compares one object file; also usable directly for experiments |
| `tools/seed_functions.py` | Regenerates `functions.csv` from `functions.tsv`, keeping recorded results |
| `build/` | Objects (not committed) |

```
python -B -I matching/tools/check.py --diff            # every unit
python -B -I matching/tools/check.py event/demo_sequence.cpp
python -B -I matching/tools/check.py --update          # record results
```

A function matches only when its compiled size equals the inventory size and every word is equal after relocations are resolved. The checker applies ADRP, ADD/LDST lo12 and B/BL relocations against the original addresses of: functions of every unit; the symbols in `units.json`; and file-static variables (found through their section-relative relocations). GOT relocations and unknown targets are masked and listed as unresolved.

## Compiler and flags

Clang 3.9.1 with:

```
-O3 -g -mcpu=cortex-a57+fp+simd+crypto+crc -mno-implicit-float -stdlib=libc++ -fPIC -fstandalone-debug --target=aarch64-linux-elf -std=c++14 -fno-strict-aliasing -fno-exceptions
```

The last two flags are not in the BotW/SMO set. Koei Tecmo built this game, so its flags can differ.
- `-fno-strict-aliasing`: needed for `2173c4`. Without it, the loop keeps the point-array pointer in a register instead of reloading it, and the two arguments swap registers.
- `-fno-exceptions`: the destructor `217070` is identical to `clear` (`2170fc`). With exceptions enabled, it gains a `__clang_call_terminate` landing pad.

Clang 4.0.1 fails three of the leaf queue functions; Clang 3.8.1 fails 7 of the 14 functions (see `docs/toolchain.md`).

## Results

14 of 17 attempted functions match: 1,732 bytes.

| Address | Function | Status |
| --- | --- | --- |
| `217054` | `DemoSequence::initialize` | match |
| `217060` | `DemoSequence::empty_operation` | match |
| `217064` | `DemoSequence::DemoSequence(DemoOwner*)` | match |
| `217070` | `DemoSequence::~DemoSequence` | match |
| `2170fc` | `DemoSequence::clear` | match |
| `217188` | `DemoSequence::load(void*)` | match |
| `217294` | `DemoSequence::sample` | `m`: registers of `n` and the scan index swapped (w10/w11); 65 of 76 words equal |
| `2173c4` | `DemoSequenceItem::load` | match |
| `2174d0` | `DemoSequenceItem::release` | match |
| `2589b4` | `resource_queue_active` | match |
| `2589d0` | `cancel_resource_queue` | match |
| `258b0c` | `register_resource_callback` | `m`: the first callback load is scheduled after the two flag stores instead of before (3 words) |
| `25917c` | `remove_resource_callback` | match |
| `258a68` | `finish_resource_queue` | `m`: final 16-bit clear and register-address handling (see below) |
| `25970c` | `resource_queue_callback_state` | match |
| `2597a8` | `resource_queue_callback_in_state` | match |
| `25984c` | `resource_queue_callback_count` | match |

### Source-shape lessons

- **Translation units.**
  - `DemoSequenceItem` (`2173c4`, `2174d0`) is a separate unit after the sequence unit. If it is in the same file, `release` gets inlined into `clear`.
  - The resource queue worker controls (`c8aef8`) are defined outside the queue unit. As two file-static globals, LLVM's GlobalMerge combines them with the registry and addresses one relative to the other.
- **Inline helpers change optimization order.**
  - `clear` matches only when the final free goes through an inline `demo_safe_free(owner, ptr)` helper. Writing the null check directly in `clear` changes the loop: the original peels the first `release` and reloads `items` at the top of each later iteration.
- **`2173c4`.**
  - The six header words are an array copied in a loop. Named fields of different structs get struct-path TBAA, and their loads merge into 64-bit loads.
  - Each point is copied word by word through per-iteration references (`DemoPoint& dst = points[i]`). A struct assignment turns into 64-bit copies.
- **`217294`.**
  - The `n == 0` case returns early with its own written-out clamp. A shared clamp tail, or a helper, produces one merged tail.
  - The scan stores its result in a separate variable initialized to `n`. A plain `for (j...) break;` lets the compiler drop the original's redundant `j == 0` test on the not-found path.
  - The lerp uses a temporary `g = 1 - f` to get the original scheduling.
- **`217188`.** The allocation descriptor comes from an inline `demo_alloc` helper. Inlined stack slots go first, so the 40-byte resource frame lands below the descriptor, as in the original. The size is computed into a local first (`unsigned int size = sizeof(DemoSequenceItem) * count;`), which gives the original instruction order.
- **`25917c`.** It is written as find-then-act: first find the index, then test the state. A combined loop produces per-entry pre-indexed loads.
- **Queue booleans.** They are `unsigned char` (tested with `and #0xff; cbnz`), not `bool`. The getter returns the byte. The two cancel flags (`+1`, `+2`) are `volatile`, which keeps their stores separate; other threads poll them. The entry reset is written state, callback, completion, argument, elapsed. The compiler then emits the original store order and pairing.

### Near misses

`258b0c`: the original loads `entries[0].callback` before the two `strb wzr` flag clears; ours loads it after them because the flags are `volatile`. Making only `flag2` volatile, or using a packed registry without `volatile`, didn't fix it. The packed version also lets the DAG merge the flag stores.

`217294`: everything but register allocation matches. The original keeps `n` in w11 and the scan index in x10; we get the reverse. Changing the index type, the variable order, the loop form or the `found`/`goto`/`continue` shape didn't change it.

`258a68`: the original clears `active` and `flag1` with `adrp x8; add x8, #0xf40; strh wzr, [x8]` and keeps nothing in x20. Our compiler either folds the low 12 bits into a 16-bit store, or emits two `strb` stores when it can't merge them.
- **Alignment evidence:** with a `packed` (alignment 1) registry, the base is materialized and the only remaining difference is two `strb` vs one `strh`. That suggests the original merged two zero-byte stores after instruction selection.
- **Tried:** an unaligned `u16` store, `memset`, reversed order, byte pointers and partial `volatile`; none matched. The committed source keeps the plain struct with both flags `volatile`.
