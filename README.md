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

112 of 125 attempted functions match: 103 inventory functions (9,012 bytes) plus 9 bodies outside the baseline inventory: the worker trampoline `45df64`, the static initializers `25aa0c` and `258970`, the array destructor `258944`, the queue worker entry points `2599ac`/`2599c4`, the gate thunk `25a174` and the cache worker callbacks `25b218`/`25b25c`. The other thirteen are near misses: twelve `m` and one `M`.

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
| `2581d4`, `258210` | `lookup_table_a`, `lookup_table_b` | match |
| `258240` | `demo_player_target` | match |
| `258280` | `demo_player_target_state` | `m`: the mode test uses separate `b.hi`/`cbz` branches instead of the original `ccmp` |
| `25834c` | `demo_speed_scale` | `m`: same mode-test difference (6 words) |
| `25839c` | `demo_player_pair` | match |
| `2583bc` | `demo_player_name` | `m`: ours tail-calls `copy_name`; the original makes a normal call with a frame |
| `2583e0`–`258458` | `demo_player_value180/184/188` | match |
| `258494` | `demo_tuning_vector` | match |
| `2586bc` | `apply_demo_tuning` | match |
| `258760`–`2587cc` | `demo_tuning_nop`, `apply_demo_limit`, `query_game_state`, `demo_overrides_zero` | match |
| `2587d4`, `258824` | `create_frame_heap`, `destroy_frame_heap` | match |
| `25886c`, `258900` | `FrameHeap::initialize`, `finalize` | match |
| `258944`, `258970` | array destructor and static initializer of the queue workers (outside the inventory) | match |
| `2589b4` | `resource_queue_active` | match |
| `2589d0` | `cancel_resource_queue` | match |
| `258a68` | `finish_resource_queue` | match |
| `258b0c` | `register_resource_callback` | `m`: the first callback load is scheduled after the two flag stores instead of before (7 words) |
| `258c64` | `process_resource_queue` | `m`: registers of the running count and registry base swapped (w9/w10), plus scheduling in the write-back loops; 328 words vs 326 |
| `25917c` | `remove_resource_callback` | match |
| `259260` | `update_resource_queue` | `m`: one word; the `flag2` test is `cbz` instead of `tbz #0` |
| `259680` | `resource_queue_has_callback` | match |
| `2599dc` | `shutdown_resource_queue` | match |
| `259aec` | `resource_busy` | `m`: the rematerialized `result = 1` is placed one instruction later (3 words) |
| `259e44` | `set_resource_waiting` | match |
| `2598c4` | `initialize_resource_queue` | match |
| `2599ac`, `2599c4` | `run_resource_queue_worker`, `run_resource_queue_high_worker` (static) | match |
| `259e84`–`259e90` | `ChunkedData::set`, `nop`, `size` | match |
| `259ea8` | `ChunkedData::extract` | `M`: same size (114 words) but register and block layout differ in 72 words |
| `25a070` | `ChunkedData::extract_allocated` | match |
| `25a0d8` | `initialize_resource_system` | match |
| `25a134` | `shutdown_resource_system` | match |
| `25a174` | `set_resource_system_gate` | match |
| `25b0c0` | `initialize_resource_cache` | match |
| `25b120` | `shutdown_resource_cache` | match |
| `25b180` | `ResourceCache::stop` | match |
| `25b218`, `25b25c` | `run_resource_cache_read`, `run_resource_cache_direct` | match |
| `25b2a0` | `ResourceCache::start` | match |
| `25970c` | `resource_queue_callback_state` | match |
| `2597a8` | `resource_queue_callback_in_state` | match |
| `25984c` | `resource_queue_callback_count` | match |
| `25b394` | `ResourceFrame::ResourceFrame` | match |
| `25b3ac` | `ResourceFrame::~ResourceFrame` | match |
| `25b40c` | `ResourceFrame::close` | match |
| `25b46c` | `ResourceFrame::is_open` | match |
| `25b47c` | `ResourceFrame::bind` | match |
| `25b390` | first body of the resource-frame unit (empty; placeholder name) | match |
| `25b4b4` | `ResourceFrame::open` | match |
| `25b5b8` | `ResourceFrame::open_table` | match |
| `25b6f8` | `ResourceFrame::count` | match |
| `25b704` | `ResourceFrame::entry_offset` | match |
| `25b71c` | `ResourceFrame::entry_size` | match |
| `25b738` | `ResourceFrame::lookup` | match |
| `25b754` | `ResourceFrame::load` | `m`: the order of one `cset`/`csel` pair (4 words) |
| `25a178` | `resource_size` | match |
| `25a1ac` | `resource_read` | match |
| `25a1ec` | `resource_free` | match |
| `25a248`–`25a258` | `ResourceName` constructor, destructor, `finish`, `set` | match |
| `25a260` | `ResourceName::exists` | match |
| `25a2a0` | `query_resource_info` | match |
| `25a344` | `ResourceName::size` | match |
| `25a388` | `initialize_resource_service` | match |
| `25a404` | `shutdown_resource_service` | match |
| `25a4a8` | `run_resource_metadata_worker` (static) | match |
| `2589c0` | `resource_queue_cancelled` | match |
| `25a53c` | `restart_resource_timer` | match |
| `25a568`–`25a578` | `resource_file_nop`, `resource_file_gate`, `set_resource_file_gate` | match |
| `25a584` | `ResourceFile::ResourceFile` | match |
| `25a5c4` | `ResourceFile::close` | match |
| `25a650` | `ResourceFile::open` | `m`: one `csel` with swapped operands and inverted condition |
| `25a764` | `ResourceFile::read` | `m`: the seek failure gets its own `return 0` (81 words vs 79) |
| `25a8a0` | `ResourceFile::set_name` | match |
| `25a8e8` | `ResourceFile::run` | match |
| `25aa0c` | static initializer of the resource-file unit (outside the inventory) | match |
| `25aa48` | `ResourceFile::read_direct` | match |
| `25aad4` | `create_resource_controller` | match |
| `25ab18` | `destroy_resource_controller` | match |
| `25ab58` | `ResourceController::resolve_name` | match |
| `25acdc`, `25ace8` | `ResourceController::initialize`, `finalize` | match |
| `25acec` | `ResourceController::size` | match |
| `25adf0` | `ResourceController::read` | `m`: block layout of the cancellation/exit tail; 179 words vs 180 |
| `45dd2c` | `get_dummy_id` (function-local static) | match |
| `45dd84`–`45dde8` | `Stopwatch` constructor, `reset`, destructor, `start`, `stop`, `elapsed_ms` | match |
| `45de40` | `initialize_worker` | match |
| `45de54` | `destroy_worker` | match |
| `45de58` | `shutdown_worker` | match |
| `45df64` | `worker_trampoline` (outside the inventory) | match |
| `45dff0` | `set_worker_ready` | match |
| `45e028` | `create_worker` | match |
| `45e094` | `wait_worker_ready` | match |
| `45e0d8` | `poll_worker_state` | match |
| `45e114` | `start_worker` | match |
| `45e154` | `worker_thread_handle` | match |

### Source-shape lessons

- **Translation units and globals.**
  - `DemoSequenceItem` (`2173c4`, `2174d0`) is a separate unit after the sequence unit. If it is in the same file, `release` gets inlined into `clear`.
  - The queue registry (`c8af40`), the worker controls (`c8aef8`) and the high-worker enable byte (`c8af38`) are external hidden globals. As file-static globals in one unit, LLVM's GlobalMerge combines them and addresses one relative to another.
  - The registry declaration has alignment 1 (a packed type). LLVM folds the low 12 bits of an address into a halfword access only when the global's alignment is at least 2. With alignment 1, the 16-bit clear of `active`/`flag1` becomes `adrp; add; strh [x8]`, as in the original. Clang raises every definition to at least 4-byte alignment, so this works only through an `extern` declaration.
  - The manager cell (`c21de8`) and the elapsed step (`c21df0`) are default-visibility externs reached through the GOT. `check_obj.py` resolves GOT relocations through `got:NAME` entries in `units.json`.
- **Inline helpers change optimization order.**
  - `clear` matches only when the final free goes through an inline `demo_safe_free(owner, ptr)` helper. Writing the null check directly in `clear` changes the loop: the original peels the first `release` and reloads `items` at the top of each later iteration.
  - `finish_resource_queue` is inlined twice into `update_resource_queue` (the early path and the readiness test). `cancel_resource_queue` is inlined into `shutdown_resource_queue`.
- **`2173c4`.**
  - The six header words are an array copied in a loop. Named fields of different structs get struct-path TBAA, and their loads merge into 64-bit loads.
  - Each point is copied word by word through per-iteration references (`DemoPoint& dst = points[i]`). A struct assignment turns into 64-bit copies.
- **`217294`.**
  - The `n == 0` case returns early with its own written-out clamp. A shared clamp tail, or a helper, produces one merged tail.
  - The scan stores its result in a separate variable initialized to `n`. A plain `for (j...) break;` lets the compiler drop the original's redundant `j == 0` test on the not-found path.
  - The lerp uses a temporary `g = 1 - f` to get the original scheduling.
- **`217188`.** The allocation descriptor comes from an inline `demo_alloc` helper. Inlined stack slots go first, so the 40-byte resource frame lands below the descriptor, as in the original. The size is computed into a local first (`unsigned int size = sizeof(DemoSequenceItem) * count;`), which gives the original instruction order.
- **`25917c`.** It is written as find-then-act: first find the index, then test the state. A combined loop produces per-entry pre-indexed loads. The scheduler's three find-and-mark passes use the same shape through `complete_resource_callback`.
- **`259680`.** It ORs all eight comparisons (`found |= ...`) instead of returning early.
- **`259260`.** The "high worker may start" condition is an `unsigned char` computed eagerly with a bitwise OR (`(id == nullptr) | (done != 0)`), reset to 1 after a completion. It is tested third in the condition: after the `0x1f` argument test and the callback test.
- **Resource frame (`resource/resource_frame.cpp`).**
  - Close and the destructor are the same body: the destructor calls `close()`, which is inlined.
  - The layout switch is an inline `set_layout` helper shared by `bind`, `open` and `open_table`. Its two 32-bit stores merge into one 64-bit constant store.
  - `entry_size` indexes through an entry pointer (`entry[1]`), which gives `ldr w0, [x8, #4]`.
  - `load` keeps "the caller gave no buffer" in a boolean computed at the top (`bool owned = dest == nullptr;`), and the result in a separate `ret` variable. That keeps the original's `cset`/`tbnz` instead of an `orr` of the two pointers.
- **Resource file (`resource/resource_file.cpp`, `25a53c`–`25aa0c`).**
  - The unit ends with its static initializer at `25aa0c`: it constructs the file-gate stopwatch (`c8b088`) and registers its destructor with `__cxa_atexit`, taking the destructor's address and `__dso_handle` from the GOT. Clang emits a unit's static initializer after its functions, which marks the unit boundary.
  - `open()` and `read()` return `unsigned char`. `close()` wraps an inline `close_handle()` that `run()` also uses; the inlined copy lacks `close()`'s leading handle check.
- **Resource controller (`resource/resource_controller.cpp`).**
  - `resolve_name` ignores `this`, so dead-argument elimination leaves `x0` unset at its call in `size`. That only happens because both are defined in the same unit.
  - The switch cases are generated from the original jump table (`7f4c48`). Its targets in address order are the cases in increasing identity order.
  - `size` builds its `ResourceName` objects in two inline helpers. Inlined stack slots go first, so the name lands above the 256-byte path buffer, as in the original.
  - `read` constructs its `ResourceFile` after the allocation, below the 256-byte path buffer. `ResourceFile::set_name` takes a third, unused byte argument, which `read` passes as 1. `read_direct` is a `ResourceFile` method defined in the controller unit, using a 16-byte stack file object (`53e410`-`53e554`).
- **Resource access and metadata service (`resource/resource_access.cpp`).**
  - The controller cell (`c8b098`, GOT `c2a608`) and the manager cell (GOT `c21de8`) are default-visibility externs. The service cell (`c8b068`) and request block (`c8b070`) are external hidden globals.
  - `resource_free` compares the storage address with the region threshold as integers. A pointer comparison swaps the `cmp` operands.
  - `45de40` is the `Worker` constructor and `45de54` the `Worker` destructor: the service's constructor calls the former before clearing its mutex pointer, and its destructor calls the latter.
  - The query ignores the result of a second `shared_state_exiting(get_shared_state())` call. The worker callback is a static function, referenced with ADRP/ADD.
- **Stopwatch and singleton (`system/stopwatch.cpp`).** The function-local static's guard and object are merged into one block, with the guard first (`cf05f0`, object at `cf05f8`). `elapsed_ms` converts ticks with `frequency / 1000000` and a `1000.0f` literal (`73bbd4`). String and float literals are mapped by section name in `units.json`.
- **Workers (`system/worker.cpp`).**
  - Thread and mutex objects share a ref-counted base: a vtable, a 32-bit count at `+8`, and destroy at slot `+0x18`. Their payloads start at `+0x10`, so they need `alignas(8)` after the 32-bit count.
  - The release sequence is an inline `release_object` helper; shutdown uses it twice. It captures the manager cell's GOT slot once, exactly like the queue shutdown.
  - `wait_worker_ready` is `while (!poll_worker_state(w)) sleep_worker_retry();` with the poll inlined. Shutdown inlines the wait again.
  - The trampoline is a default-visibility function, so `create_worker` loads its address from the GOT (`c2bbc8`). `destroy_worker` is a separate one-instruction function that tail-calls `shutdown_worker`.
- **`resource_busy` (`259aec`).** It repeats the scheduler's high-worker block with the same source order: the eager `idle`, its reset to 1 after a completion, and the `0x1f`/callback/`idle` condition order. The source now shares one inline helper (`run_high_worker`) between the two; that produces the same code and leaves both near misses as they were.
- **Allocation sizes are 64-bit.** `DefaultHeap::allocate` and `ResourceAllocator::alloc_aligned` take `unsigned long` sizes; the original sets up those arguments with 64-bit moves. Fixing that closed `ResourceFrame::open` and `open_table` and the register rotation in `ResourceController::read`.
- **Units in `259ea8`–`25b390`.** `resource/resource_system.cpp` (`259e84`–`25a174`: chunked data plus system init/shutdown), `resource/resource_cache.cpp` (`25b0c0`–`25b2a0`, with three workers named `FileReader`/`FileWriter` and callbacks referenced through the GOT). `25b390` opens the resource-frame unit. The placeholder bodies at `259e84`–`259e90` are `ChunkedData` methods (their size getter is inlined into `25a070`), and `25acdc`/`25ace8` are `ResourceController::initialize`/`finalize`.
- **Static initializer `25b36c` (not attempted).** It clears 0x202 bytes at `c8b0a8` with a non-tail `memset` call. A global whose constructor does that gets removed by clang's global-constructor evaluator, which treats a zero `memset` of a zero-initialized global as a no-op. The original kept it, so it may come from a different form.
- **Queue initializer.** The entry reset uses the same order as `cancel` (state, callback, completion, argument, elapsed). The worker entry points are static functions that tail-call the active callback. The registry's reference is created with `create_mutex`.
- **Demo overrides unit (`event/demo_overrides.cpp`, `2581d4`–`258970`).** It ends with the static initializer `258970`, which constructs the two queue workers at `c8aef8` and registers their array destructor `258944` with `__cxa_atexit`. So the workers are defined here, which is why the queue unit refers to them as an external hidden global. `45de40`/`45de54` are the `Worker` constructor and destructor.
  - `apply_demo_tuning` lists its cases in the order 2, 0x20, 0x13.
  - `FrameHeap::initialize` calls `get_default_heap()` on each side of the size condition. The base size is `0x14000`.
  - The two table lookups put the in-range path first (`if (index <= max) {...} return nullptr;`).
  - Deferred: `2584e0` (476 bytes), a 214-case switch that writes two floats through shared tail blocks.
- **Mergeable constants.** Clang emits a separate literal per function in `.rodata.cst4`; the linker merges equal values. `check_obj.py` now resolves such relocations to the first equal constant at or after the mapped base.
- **Queue booleans.** They are `unsigned char` (tested with `and #0xff; cbnz`), not `bool`. Only `flag2` (`+2`) is `volatile`. That keeps cancel's two flag stores separate while letting `active` and `flag1` merge into the 16-bit clear. The entry reset is written state, callback, completion, argument, elapsed; the compiler then emits the original store order and pairing.

### Deferred

`45e160` (1,464 bytes) is a 61-case statistics switch with a jump table at `811194`. It calls at least six game functions whose signatures are unknown (`204728`, `203dfc`, `2028b4`, `200fc0`, `2015a8`, `200294`), so it needs its own effort. The four small virtuals at `45dcd0`–`45dd28` need their class and vtable identified first.

### Near misses

`25b4b4`, `25b5b8`, `25b754`: these differ only in argument-register setup order or one register copy. For `load`, about 15 variants of the tail and the allocation call were tried. For `open`, a direct call, a condition-declared size, a helper that checks for zero, and keeping the allocation result were tried. An inline allocation helper fixed the similar problem in `217188`, but here it improves `load` and makes `open_table` worse.

`258b0c`: the original loads `entries[0].callback` before the two `strb wzr` flag clears; ours loads it after the volatile `flag2` store. Non-volatile flags fix the order but let the DAG merge the flag stores in `cancel` and `register`.

`259260`: the original tests `flag2` with `tbz w8, #0`; ours uses `cbz w8`. An `unsigned char` flag tested with `& 1` produces `tbz`/`tbnz`, but it flips the block layout (59 words differ). Neither branch order fixes that.

`217294`: everything but register allocation matches. The original keeps `n` in w11 and the scan index in x10; we get the reverse. Changing the index type, the variable order, the loop form or the `found`/`goto`/`continue` shape didn't change it.

`258c64`: the grouping, the three exchange sorts and the write-back match in structure.
- **Copy blocks:** writing the counter increment after the copy keeps the three copy blocks from being tail-merged.
- **Priority helper:** written as a ternary, it gives the original block layout.
- **Still different:** the registry base and the running count use swapped registers. The waiting and empty write-back loops are scheduled differently, giving 328 words vs 326.