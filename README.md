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
-O3 -g -mcpu=cortex-a57+fp+simd+crypto+crc -mno-implicit-float -stdlib=libc++ -fPIC -fstandalone-debug --target=aarch64-linux-elf -std=c++14 -fno-strict-aliasing -fno-exceptions -mllvm -regalloc=greedy
```

The last two flags are not in the BotW/SMO set. Koei Tecmo built this game, so its flags can differ.
- `-fno-strict-aliasing`: needed for `2173c4`. Without it, the loop keeps the point-array pointer in a register instead of reloading it, and the two arguments swap registers.
- `-fno-exceptions`: the destructor `217070` is identical to `clear` (`2170fc`). With exceptions enabled, it gains a `__clang_call_terminate` landing pad.
- `-mllvm -regalloc=greedy`: greedy is already the default allocator, so allocation doesn't change. Naming an allocator explicitly makes Clang 3.9 skip its Cortex-A57 FP load-balancing pass (`AArch64A57FPLoadBalancing`, added only with the default allocator). That pass renames FP registers in multiply chains, which lets the load/store pairer merge stores the original keeps separate (`25cb98`). No earlier match changes.

Clang 4.0.1 fails three of the leaf queue functions; Clang 3.8.1 fails 7 of the 14 functions (see `docs/toolchain.md`).

## Results

251 of 313 attempted functions match: 241 inventory functions (40,840 bytes) plus 10 bodies outside the baseline inventory: the worker trampoline `45df64`, the static initializers `25aa0c` and `258970`, the array destructor `258944`, the queue worker entry points `2599ac`/`2599c4`, the gate thunk `25a174`, the cache worker callbacks `25b218`/`25b25c` and the empty `TrackResources::update` (`25cd50`). The other sixty-two are near misses, all `m`.

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
| `258280` | `demo_player_target_state` | match: the mode test is a `switch` on modes 7, 8, 9, 10 and 12 (gives the `ccmp`) |
| `25834c` | `demo_speed_scale` | match: same `switch` |
| `25839c` | `demo_player_pair` | match |
| `2583bc` | `demo_player_name` | `m`: ours tail-calls `copy_name`; the original makes a normal call with a frame. `3ff70` is not a string copy (it does float math on `[x1+8]`), so the name is a placeholder |
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
| `259ea8` | `ChunkedData::extract` | `m`: `from_allocator` is set inside the allocator branch (gives the original's `cset`); the original still re-checks the scratch pointer after the loop. 111 words vs 114 |
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
| `25a650` | `ResourceFile::open` | match: the size clamp is `mSize == 0 \|\| mSize > size`, which InstCombine folds into the original's `mSize - 1 >= size` |
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
| `25adf0` | `ResourceController::read` | `m`: block layout of the cancellation/exit tail. A `keep = dest != nullptr` flag gives the original's `cset`, but the two return tests still come out in the other order |
| `25b828`–`25b860` | `TrackKey` constructors, destructor and a trivial body | match |
| `25bb9c`, `25bba0` | trivial body, `TrackLight::reset` | match |
| `25bcd0` | `TrackLight::copy` | match |
| `25bd64` | trivial body | match |
| `25bbe8`, `25bd68` | `TrackLight::decode`, `decode_full` | match |
| `25be54` | `TrackLight::copy_full` | match |
| `25bef0` | `TrackLight::equals` | match |
| `25bfdc` | `TrackLight::interpolate` | match |
| `25c240` | `TrackSlot::TrackSlot` | match |
| `25c254` | `TrackLightSet::TrackLightSet` | match |
| `25c26c` | `TrackLightSet::load` | match |
| `25c634` | `TrackLightSet::update` | match |
| `25c6c0` | `TrackLightSet::update_scaled` | `m`: the original loads `values.w` with `scale20` (one `ldp`) and pairs its store with `values.z`; 4 instructions differ |
| `25c7ac`, `25c7e0`, `25c814` | `TrackLightChannel` constructor, `clear`, `set_keys` | match |
| `25c820` | `TrackLightChannel::update` | match |
| `25c96c` | `TrackLightChannel::sample` | match |
| `25cb98` | `TrackLightChannel::update_scaled` | match |
| `25cd44`, `25cd50` | `TrackResources` constructor, empty `update` (outside the inventory) | match |
| `25cd54`, `25cde8`, `25ce7c` | `TrackResources::release`, `reset`, `clear` | match |
| `25cf10` | `TrackResources::load` | match |
| `25cf50` | `TrackResources::load_one` | match |
| `25d014` | `TrackLightTarget::build_quad` | match |
| `25dc08` | `DemoLightSystem::DemoLightSystem` | `m`: the stores to `+0x199ec`, `+0x199f4` and `+0x19a00` come out in reverse order (7 words) |
| `25df64`, `25dfb4` | `create_demo_light_system`, `destroy_demo_light_system` | match |
| `25e02c`, `25e284` | `DemoLightSystem::initialize`, `finalize` | match |
| `25e370`, `25e4d0` | `DemoLightSystem::load`, `unload` | match |
| `25e538` | `DemoLightSystem::update` | match |
| `25e78c` | `DemoLightSystem::start` | match |
| `25e8a0` | `DemoLightSystem::play` | `m`: the final clamp becomes `fmax` plus `fcsel`; the original keeps an `fcsel`/`fccmp` chain (3 instructions) |
| `25eb70` | `DemoLightSystem::finish` | match |
| `25ec3c` | `DemoLightSystem::draw` (152 bytes; the inventory merged it with `25ecd4`) | match |
| `25ecd4` | `DemoLightSystem::draw_intro` | `m`: same size; the pointer setup and flag stores at the top are scheduled differently, which shifts register allocation |
| `25f44c` | `DemoLightSystem::layout_frames` | `m`: one merged 64-bit rectangle store comes out before the `max.y` store instead of after (8 words) |
| `25f6b8` | `DemoLightSystem::layout_panel` | match |
| `25f820` | `DemoLightSystem::draw_text` | match |
| `25f944` | `DemoLightSystem::render` (696 bytes; the inventory merged it with `25fbfc`) | match |
| `25fbfc` | `DemoLightSystem::render_ending` | match |
| `25ffe8`, `260220` | `TrackLightTableSet` constructor, destructor (76 bytes; the inventory said 80) | match |
| `26026c`, `260288`, `2605d0` | `TrackLightTableSet::init`, `finalize`, `unload` | match |
| `260290` | `TrackLightTableSet::load` (140 bytes; the inventory merged it with `26031c`) | match |
| `260648` | `LightEntry::LightEntry` | `m`: `scale` is set in the initializer list, which fixes its store; the color is still zeroed as one word where the original uses two halfword stores |
| `2606b8`, `2606fc` | `LightEntry` destructor, `unload` | match |
| `260740` | `LightEntry::bind` | match: `make_texture` takes the color packed as an `unsigned int`, built in the call from the four bytes |
| `26086c` | `DemoEffectPool::DemoEffectPool` | match |
| `260a48` | `DemoEffectPool::finalize` | match |
| `260b60`, `260bac` | `create_demo_effect_pool`, `destroy_demo_effect_pool` | match |
| `260c0c` | `DemoEffectPool::initialize` | match |
| `260d54` | `DemoEffectPool::clear` | match |
| `260fe8` | `DemoEffectPool::update` | match |
| `261024` | `DemoEffectPool::update_slots` | match |
| `261290` | `DemoEffectPool::update_markers` | match |
| `261720` | `DemoEffectPool::draw_marker` | near miss |
| `261aa8` | `DemoEffectPool::render_marker` | near miss |
| `261e24` | `DemoEffectPool::setup` | near miss |
| `262e78` | `DemoEffectPool::restart` | near miss |
| `26302c` | `DemoEffectPool::draw` | match |
| `26303c` | `DemoEffectPool::draw_nodes` | match |
| `2632cc` | `PanelTargets::PanelTargets` | match |
| `2637fc` | `DemoPanelSystem::finalize` | match |
| `2639a8` | `PanelTargets::~PanelTargets` | match |
| `263b3c` | `create_demo_panel_system` | near miss |
| `263cfc` | `destroy_demo_panel_system` | match |
| `263d58` | `DemoPanelSystem::initialize` | near miss |
| `2648dc` | `DemoPanelSystem::update` | match |
| `2649cc` | `DemoPanelSystem::update_state` | near miss |
| `264c28` | `DemoPanelSystem::update_icons` | near miss |
| `26514c` | `DemoPanelSystem::update_cells` | near miss |
| `266740` | `DemoPanelSystem::draw` | match |
| `266810` | `DemoPanelSystem::draw_wall` | match |
| `2669c0` | `DemoPanelSystem::open_window` | near miss |
| `266a20` | `AdvCaption::finalize` | match |
| `266aac` | `create_adv_caption` | match |
| `266b98` | `destroy_adv_caption` | match |
| `266cd8` | `AdvCaption::initialize` | match |
| `266ec0`-`266ef8` | `AdvCaption` value accessors (5) | match |
| `266f04` | `AdvCaption::update` | match |
| `266f58`, `267308` | `AdvCaption::draw`, `draw_alternate` | match |
| `266f6c` | `AdvCaption::draw_text` | near miss |
| `26731c` | `AdvEffects::finalize` | match |
| `26759c`, `26767c` | `create_adv_effects`, `destroy_adv_effects` | match |
| `2676ec` | `AdvEffects::initialize` | near miss |
| `267c44` | `AdvEffects::update` | match |
| `267d64` | `AdvEffects::update_screens` | match |
| `267f94`, `268224` | `AdvEffects::update_records`, `update_exit` | match |
| `268340` | `AdvEffects::play_screen` | near miss |
| `268874` | `AdvEffects::show_result` | match |
| `268a80` | `AdvEffects::end_screens` | near miss |
| `268f10`, `268f74` | `AdvEffects::draw_start`, `draw_environment` | match |
| `268fc8`, `2690a8` | `AdvEffects::draw_screens`, `draw_screens_alternate` | match |
| `269188` | `AdvEffects::play_banner` | near miss |
| `269238`, `269440` | `AdvEffects::play_enter`, `play_exit` | near miss |
| `269544`, `2695a8` | `AdvEffects::stop_banner`, `EffectRecord::stop` | match |
| `2696a8` | `AdvEffects::play_clock` | near miss |
| `269720`–`26983c` | `EffectClock::stop`, `AdvEffects::clock_frame`, `clock_done`, `clock_active` | match |
| `269858`–`269c40` | `item_weapon_value`, `item_rank`, `item_is_kind`, `board_intro_pending`, `BoardQuery::active_count`, `total_count`, `unit_alive` | match |
| `269cfc`, `269dd0`, `269ea8` | `unit_kind`, `board_value`, `neighbor_cell` | match |
| `269de0`, `269fa0`, `269fd8`, `26a080` | `held_kind`, `is_officer_kind`, `is_keep_kind`, `is_gate_kind` | near miss |
| `26a014`, `26a100` | `is_fort_kind`, `open_gate` | match |
| `26a220`, `26a454` | `BoardRow::gate_state`, `update_dlc_gates` | near miss |
| `26a7e0`, `26a90c` | `dlc_unit_unlocked`, `Player::cell_open` | match |
| `26a98c` | `Player::setup` | near miss |
| `26b088`–`26b374` | `dlc_board_flag`, `Player::cell_cleared`, `cell_selectable`, `BoardQuery::cell_level`, `board_complete` | match |
| `26b3cc` | `BoardQuery::find_entry` | near miss |
| `26b798`, `26bd64` | `fill_cell_entries`, `start_board_battle` | near miss |
| `26c11c` | `stage_message` | match |
| `26c610`–`26c884` | `is_plain_cell`, `unit_override_kind`, `unit_frame`, `unit_override_frame` | near miss |
| `26c154`, `26c924` | `load_board`, `unit_has_override` | near miss |
| `26cc30`, `26cdec` | `ward_slot`, `is_shop_kind` | near miss |
| `26cd2c`, `26cd8c`, `26ce44` | `unit_is_leader`, `cell_group_flag`, `board_enabled` | match |
| `26ce4c` | `board_overflow` | match |
| `26d02c`, `26d09c` | `board_side_quest`, `board_side_quest_open` | match |
| `26d124`, `26d6dc` | `reset_side_board`, `tick_seals` | near miss |
| `26d620` | `tick_side_quest` | match |
| `26d978`, `26da1c`, `26dd70` | `tick_timer`, `seal_random_keep`, `advance_nightmare` | near miss |
| `26db3c`, `26dbb4`, `26dc74`, `26e278` | `nightmare_stage`, `reset_nightmare`, `nightmare_reached`, `check_nightmare_clear` | match |
| `26e434`, `26e9f4`, `26ea94` | `AdvModeTask::AdvModeTask`, `run_options`, `run_save` | match |
| `26e4a8`, `26e824`, `26eb54` | `AdvModeTask::run`, `BoardQuery::reset`, `run_board_menu` | near miss |
| `26031c` | `TrackLightTableSet::load_tracks` | `m`: the two overflow tests compile to `cmp #0x101; b.lo` instead of `cmp #0x100; b.ls` (4 words) |
| `25d19c` | `apply_track_light` | `m`: same size; the inlined cosine tests its sign with `cmp` instead of `eor`/`tbz`, and some polynomial blocks are scheduled differently |
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
- **Mergeable constants.** Clang emits a separate literal per function in `.rodata.cst4`; the linker merges equal values. `check_obj.py` resolves such relocations to the first equal constant in the 4 KiB after the mapped base.
- **Demo track items (`event/demo_track_items.cpp`, `25b828`–`25bd64`).** These bodies are decided by how stores merge, which depends on field types.
  - `TrackKey`'s field at `+0x10` is a `float`: a float zero doesn't merge with the integer -1 index stores beside it.
  - `TrackLight`'s values are an aggregate assigned at once.
  - Its color at `+0x28` is a union of a raw 32-bit word (cleared with one store) and four bytes. The bytes are copied through `set(TrackColor)` by value, which gives the original 32-bit load and four byte stores.
  - The record decoders store the position with one 16-byte vector store. With `-mno-implicit-float` the SLP vectorizer stays off, so the source uses an explicit 16-byte float vector type there; the original's vector type probably has SIMD storage. The record's color bytes are gathered into a local `TrackColor` and assigned through `set()`.
  - `equals` returns early after each test, with an inlined vector `operator==` for the position.
  - `interpolate` lerps each field whose bit is set in the target's change mask (`+0x30`). Three source details matter:
    - the `to` value comes first in the helper's argument order;
    - `from`'s color is read as one raw word, with the bytes extracted by shifts;
    - the byte lerp computes its product into a local first.
  - Deferred: `25b864` (824 bytes), a loader built on a serializer stream with many unknown callees.
- **Demo light set, channels and resources (`25c254`–`25cf50`).** These are four units: `event/demo_light_set.cpp` (`25c254`–`25c6c0`), `event/demo_light_channel.cpp` (`25c7ac`–`25cb98`), `event/demo_track_resources.cpp` (`25cd44`–`25cf10`) and `event/demo_track_resource_load.cpp` (`25cf50`). The shared types are in `include/event/demo_track.h`.
  - The boundaries come from calls. The set calls `TrackLight` methods, the channel functions and even the empty `~TrackLight` (`25bd64`) instead of inlining them. `TrackResources::load` sets `x0` for `load_one`, so dead-argument elimination couldn't see that `load_one` ignores `this`.
  - `TrackVector` is 16-byte aligned, which makes `TrackLight` 0x40 bytes and puts the stack copies at 16-byte offsets. `TrackLight`'s default constructor calls `reset()`, its copy constructor `copy()`, and a record constructor `decode()`.
  - `load` constructs only the first channel and the first key of each list with placement `new`. It releases its arrays through a member `release(void*)` helper. A free helper or inline code makes GVN merge the field address into a PHI. The allocation size is computed into an `unsigned int` local. Merged keys are counted with an inverted condition (`if (!same || !flag38)`).
  - The scale functions take their adjustment as a `TrackVector` by value (an HFA in `v1`–`v4`) after the time, with the alpha byte last. That gives the original argument copy order and `adjust.x * field` operand order.
  - `sample` takes the output pointer first. It finds the key with a search whose default is the count, and binds the previous key by reference before copying the current one. The ease is `t * (t * (1 - k)) + t * k`, clamped through two selects (`fmax`/`fmin`).
  - The table switch lists its cases 2, 1, 0; the original then tests 0 first.
  - The handle release copies the member into a local before decrementing the count. The loader's `MemoryStream::open` takes a 64-bit size.
- **Demo light target (`event/demo_light_target.cpp`, `25d014`–`25d19c`).** `apply_track_light` positions a light's quad. It is a free function with a null check on the target. With an angle it inlines a polynomial cosine and sine (range reduction by 2π and π, then Taylor terms to x⁶ or x⁵), written once in each branch. `build_quad` builds the corners and rotates them with `rotate_point` (`1f714c`).
  - `build_quad`: the field at `+0x18` is two floats, so the two zero stores merge into one 64-bit store while the 1.0/0.0 matrix stores stay 32-bit. `scale[1]` is written before `scale[0]`, which keeps that pair from merging. The corner halves go into four locals.
  - `apply_track_light`: the range-reduction selects use inverted compares (`!(a >= kPi)`), which gives `fcsel lt`. `dy` is computed before `dx`. The no-angle path reads the image size inline.
- **Demo light system (`event/demo_light_system.cpp`, `25dc08`–`25eb70`).** This is the 0x19b40-byte singleton behind the GOT slot `c22d98`; the light channels reach their tables through it (`+0x72a8`). Its layout is in `include/event/demo_light_system.h`. Member types are known only from their out-of-line constructors, destructors and methods. The implicit destructor, inlined in `destroy_demo_light_system`, gives the member order.
  - `TrackKey` (`+0x5c28`) moved into `demo_track.h`. Its empty bodies are `TrackKey::finalize` (`25b860`) and `TrackKey::unload` (`25bb9c`), and `25b864` is `TrackKey::load(int)`. The pointer constructor is placed with `new`.
  - The scene at `+0x68` has an implicit constructor around an out-of-line base constructor and a vtable from elsewhere, so it is value-initialized (`scene()`): memset, base constructor, vtable store.
  - The default heap's allocator is a base at `+0xb0`, reached through a reference. As a member, clang devirtualizes the calls; through a pointer, it adds a null check.
  - `+0x199ec` is a 4-byte flag group plus an index, value-initialized as one struct, so the zero store is 64-bit. The tail fields are assigned in the constructor body in the order 9b20, 9b24, 9b30, 9b28, 9b38, 9b27, 9b25, 9b26. Only `9b25`/`9b26` merge.
  - `update` dispatches through a 12-entry jump table (`7f508c`, mapped as `.rodata`). States 3–5, 7 and 8 share the tail that sets state 9.
  - Two strings are linker-merged literals (`""` at `740512`, `"font_caption.bflyt"` at `741e21`), declared as hidden externs.
- **Inventory corrections.** Three rows were wrong because Ghidra merged a function with the one it tail-calls, or misjudged an end. `25ec3c` (2,064 bytes) is now `25ec3c` (152) plus `25ecd4` (1,912). `25f944` (1,636) is now `25f944` (696) plus `25fbfc` (940). `260290` (832) is now `260290` (140) plus `26031c` (692). `260220` is 76 bytes, not 80 (80 would overlap `26026c`). `functions.csv` has 17,279 rows now.
- **Light table set (`event/demo_light_table_set.cpp`, `25ffe8`–`2605d0`).** It holds the light system's `TrackResources` at `+8`; the three handles are the channels' tables, so `TrackLightTable` derives from `RefObject`. The empty `25cd50` is `~TrackResources`. `25c240` (`TrackSlot`) default-constructs each `TrackLightSet`'s storage before placement. The `LightAllocator` is a `DemoOwner`.
  - `ResourceFrame::open` returns `unsigned char`, which gives the caller's `and #0xff`. The frame unit still matches.
  - `load_tracks` holds each channel count in a local, loads `channels` before the counter store, and reads both overflow counters through one 64-bit view (a union), as the original does.
- **Light system rendering.** `render` dispatches with a switch (cases 1, 10, 11); an if-chain lets SimplifyCFG hoist the shared `begin()` call. Its last two layers go through an inline `draw_layer` helper. `render_ending` keeps a function-local static table of 33 per-stage offsets (guard `c8b2c0`, data `c8b2c8`) built through a constructor, which is why it needs a guard. The stage offset is copied into a local before `begin()`, and the timer test is `<=`-first.
- **Light entries (`event/demo_light_entry.cpp`, `260648`–`260740`).** These are textured sprites, 0xd0 bytes each, holding a reference-counted texture. They are a separate unit because the table-set loops call their constructor and destructor. `bind` copies a 64-byte table of four RGBA colors (`7f50f0`, mapped as `.rodata`) and stores the allocator in a global (GOT `c2a640`).
- **Demo effect pool (`event/demo_effect_pool.cpp`, `26086c`–`26303c`).** A 0x12f0-byte singleton (GOT `c2a648`) holding four arrays of 28 effect slots (two 0x28-byte kinds, two 0x20-byte kinds), 28 caption nodes, a counter node and a `LightResource`.
  - The effect-manager types moved to `include/event/demo_effects.h`. `LightEffect` takes its mode (0x10 in the light system, 0x11 here).
  - Releasing a node unregisters its id (0x4211 slots, 0x420f markers, 0x420d captions) before detaching it. The root pointer is read first.
  - The constructor assigns everything in its body, after the `LightResource` member is constructed. Slots are reset by inline `reset()` helpers. The destructor calls `finalize()`, so `destroy_demo_effect_pool` finalizes twice, as in the original.
  - `initialize` binds each caption by reference in its loop and stores `step` before `initialized`.
  - `update_slots` is a switch on the pool state. Its four advance loops go through one small template helper; with separate helper functions it shrinks enough to be inlined into `update`, which breaks `update`.
  - `update_markers` copies each node into a local, then fetches the effect root, then makes the virtual call. That gives the original order: node load, `current()` call, vtable load. The caption loop walks a pointer (incremented before the index) and tests `captions[count_e]` (an out-of-range index, as in the original).
  - `draw_marker` has to be defined in this unit: the original calls it without setting `x0` (dead-argument elimination). `render_marker` is called with `x0` set even though it never reads it, and it is also called from `298c3c`. So it is an inline member (linkonce, which the optimizer leaves alone), emitted where `update_markers` first references it. `DemoEffectPool::draw` (`26302c`) calls both the same way, so it belongs to this unit too.
  - `unit_has_override` (`26c924`) returns `unsigned char` (`and #0xff; cbz`).
  - The element counters are `unsigned int`: `setup` indexes the arrays with a zero-extended count (`uxtw`). The `advance_nodes` helper takes `const unsigned int&` so `update_slots` still matches.
  - `setup` (`261e24`) runs two passes. Each asks the roster (`26b3cc`) for five {kind, value, flag} records and exchange-sorts them by value, then fills slots, markers and captions. Values above 1000 or equal to -1 clear the kind. Kinds 0x28–0x2a map to slot layouts 0xd–0xf. The cell value gives the grid position: x = (col·56 − 420)·1.5, y = (304 − row·56)·1.5. The two passes differ only in their arrays and in the animation and kind indices (`2 + pass`, `6 + pass`, `pass`).
  - In the sort, the swap saves `records[j]`'s fields, copies `records[i]` over `records[j]` as a whole struct (an 8+4-byte copy), then stores the saved fields into `records[i]`. That gives the original's mix of 64-bit and field-wise moves. A marker uses one of two `create_node` calls (the special enemy layout for marker 0x1e in modes 7 and up), which the optimizer merges. The 0.6525 scale has to be written as `0.652500033f`, which gives the original's 0x3f270a3e.
  - The `26302c` inventory row was two functions: `draw` (16 bytes) checks `initialized` and tail-calls `draw_nodes` (`26303c`, 656 bytes). `draw_nodes` mirrors `update_markers`, with `draw(0)` in place of `update`. Its helper takes the node, index and value by reference, which gives the original's loop pointer.
- **Demo panel system (`event/demo_panel_system.cpp`, `2632cc`–`2649cc`).** The Adventure Mode info window (`adv_info_window.bflyt`, attribute icons, arrow and lock panes). A second 0x26b80-byte singleton (GOT `c2a678`) built like the effect pool. Its member at `+0x30` (`PanelTargets`, out-of-line constructor and destructor) holds a node, a `LightResource`, two groups of four {pointer, `LayoutHandle`} items and five `TrackLightTarget` arrays (24, 544, 544, 24, 24). `hide_targets` (`1f7530`) sets the hidden bit on a run of targets.
  - `LayoutHandle` derives from a plain state base ({id = -1, two shorts}), so its vtable pointer is stored after the fields. Its destructor is an inline virtual (vtable slots 0 and 1) that calls virtual slot 3, `release(root)`. Because the class has an inline virtual function, Clang can't emit the vtable `available_externally`, and the call goes through a load from the external vtable (GOT `c22f00`), as in the original.
  - `initialize` (`263d58`) creates the window, attribute, number and (in modes 5 and 6) wall layouts. It looks up the arrow, lock and dummy panes by name tables, binds the attribute and number animations, and adds five 0x180-byte text panes. An animation binding (0x58 bytes, vtable GOT `c2a698`) is spliced into the node's binding ring with an inline `ListLink::link_before`. Its source (`5cfac8`) is a 0x20-byte local whose block pointer is copied into a local before the calls. `LayoutAnimation` moved to `include/event/demo_effects.h`, and `LightEffectNode` gained its binding ring (`+08`) and resources (`+40`).
  - The wall record at `+0x26b68` is plain members, so `initialize` addresses each field separately. The constructor clears it through a cast to a three-field record with an inline `reset()`, which keeps `create`'s store order.
  - `update` (`2648dc`) advances and updates the window node, then calls three per-group updates (`264c28`, `26514c`, `2653dc`). `update_state` (`2649cc`) finds the player's entry among 128 and reads the unit's size and value from the unit database (`20ec80`/`20eeb8`).
  - `update_icons` (`264c28`) hides the four item panes. If the player has the unit's attribute unlocked, it derives character, weapon and grade icons from the unit record (`+04`, `+24`, `+06`) and places them on the two front panes, using a centred, larger layout when only one icon shows. It then sets the rank icon (`0xc0`-`0xc2`) and the question mark. Icons go through `gIconTable` and `apply_icon` (`1f7fe4`).
  - `update_cells` (`26514c`) drives the two attribute icons. They are {pane, animation} pairs at `+0x26b20`, and an `AnimBinding` is a `LayoutAnimation` (`frame_count`, `set_frame` at `+c0`). Each pair's frame is `size[i]` (`+0x0c`); an icon shows only while that frame is within the animation and the attribute is unlocked.
  - `draw` (`266740`) places the number pane with `value14 > 9 ? 245.0f : 273.0f`. A select of two float constants compiles to a load from a two-entry constant-pool pair indexed by the condition, which is what the original shows (no table in the source). `draw_wall` shows one of `wall_u`/`wall_l`/`wall_r`/`wall_d` by `wall_direction` (`26a100`, a jump table at `7f5150`). `open_window` restarts the window animation and plays sound 0x17ec.
  - The pane classes moved to `include/event/layout_panes.h`.
  - `finalize` releases two nodes with id 0x420d (unregister, then the children list) and two plain nodes (the nodes list, no unregister). `+0x26b08` and `+0x26b68` are {pointer, pointer, int} records, reset by an inline helper.
- **Adventure caption (`event/adv_caption.cpp`, `266a20`–`266f04`).** A 0x8a80-byte singleton (GOT `c2a6b0`) for `adv_caption.bflyt`: two arrays of 128 `TrackLightTarget`s, two text panes (`font_r`, `font_l`), a node and two `LightResource`s. `initialize` calls both size functions before storing their results. The symbol names in `units.json` are global, so the layout name is `kAdvCaptionLayout`: reusing `kCaptionLayout` silently remapped the light system's literal and broke its `initialize`.
- **Adventure caption drawing.** The `266f58` inventory row was three functions: `draw` and `draw_alternate` (20 bytes each) call `draw_text(0)` / `draw_text(1)` (`266f6c`). `draw_text` saves the caption group's position and scale, lays out the unit name and item name through the text renderer into the two target arrays, unhides the targets it produced, hands them to the two font panes (`1e41d8`), and restores the group. The mode test is `mode == 0 || mode == 1` (InstCombine turns it into `(mode \| 1) == 1`). `destroy_adv_caption` matches once the two `LightResource`s are an array: the array destructor loop keeps the base address live, as in the original.
- **Adventure stage effects (`event/adv_effects.cpp`, `26731c`–`2695a8`).** A 0x500-byte singleton (GOT `c2a6b8`) for `adv_btl_start`, `adv_change_tv`/`drc`, `adv_env_eff` and `adv_dlc3_clock`. It holds a banner (node and animation), two change records (node, `in_0`–`in_3`/`out`, state), two environment screens (node and 25 animations named by a hidden table at `bd0ea0`), and the mode-4 clock (four song-of-time animations). Its two resource layers are an array of {`LightResource`, width, height} records 0x120 bytes apart, which is what makes `destroy` match.
  - The constructor's two odd-sized `memset`s (0x1a1 and 0x55 bytes) come from clearing the screen array and the clock record next to the zeroed neighbouring fields: the compiler merges them. `finalize` clears the banner pair with `memset(&banner, 0, sizeof(banner))`. Plain stores were moved after the final `memset`, which stopped the tail call. The first five nodes are released with the manager read before the check; the clock uses the variant that reads it inside.
  - `LayoutAnimation::frame` is `volatile`: the original reloads it for every test (`update_records`, `update_exit`), which a plain `float` does not reproduce.
  - `draw_screens` and `draw_screens_alternate` are byte-identical bodies (the nightmare pane fade, alpha byte at `EffectGroup+59`); both come from one inline. The flags of `play_enter`/`play_exit` are `unsigned char` (tested with `tst #0xff`).
  - `update_screens` tests kind 5 before kind 8, uses an `int` index (the original compares it in 32 bits and indexes `anims[i]` dynamically) and an unsigned loop test.
- **Adventure board queries (`event/adv_board.cpp`, `269858`–`26a90c`).** Item and weapon lookups, the per-player unit table (`UnitDatabase+db608`: one 0x1e0-byte `BoardRow` per cell, with gate states at `+8`, owner `+c`, kind `+12`, level `+13`; unit records of 12 bytes at `+ea608`), the per-player cell states (`Player+4`), the 16-wide neighbour step, and the DLC unlock checks.
  - `UnitInfo::kind` is an `int :16` bitfield. As a `short`, InstCombine narrows `kind == 0xd2` to a 16-bit compare (`and #0xffff`); the bitfield keeps the original's 32-bit compare.
  - The diagonal neighbours are written as the full diagonal first (`cell - 17`/`cell - 16`) with the row edge fixed afterwards; chaining the two single steps gives a different select.
  - `BoardQuery` is a real object: per-cell tables of 28 entries (levels `+3d8`, kinds `+3bd8`, flag bytes `+73d8`, items `+81d8`). The last 0x50 bytes of each `BoardRow` are a `[2][5]` table of {x, y} cell positions. `cell_level` matches once the mode-8 test reads the player byte before the range test.
  - The 12-byte unit record is two runs of bitfields: four 16-bit fields (kind, frame, override, value6), then `int : 0`, then four bytes. With one run `unit_alive` stops matching; with no bitfields `unit_kind` does.
  - The GOT slot `c23250` holds the global `BoardQuery` (`gBoardQuery`), which `unit_kind` passes to the remap call. `fill_cell_entries` fills a cell's 28 entries from the shop catalog (`gShop`, lists 2-0x75, three entries each) and the item table (`gItemDefs`, 0x50-byte records). `start_board_battle` sets up the battle parameters and runs four fills.
  - `board_overflow` counts the board columns and rows that fall outside the display. The row offset is written as a subtraction (`origin.y - y * 44`): `x - 0.0f` folds away for the first row, `x + 0.0f` does not. The column loop tests `!= 0x400`.
  - `tick_side_quest` decrements a byte counter to zero with the subtraction done in 32 bits (`sub #1` then a byte compare); an 8-bit subtraction gives `add #0xff`.
  - `check_nightmare_clear` matches with its two found flags as `unsigned char` (tested with `and #0xff`) declared second-first, which gives the original register order. `nightmare_reached` needs the open test as one condition rather than `continue`s.
  - `ward_slot` (`26cc30`) is the helper `unit_has_override` inlines twice; using it there brought that function from 119 to 106 differing words.
  - `dlc_unit_unlocked` returns `unsigned char`: its callers test `and #0xff`, which a `bool` result does not produce. `unit_alive` matches with the team and defeated tests in one `||`.
- **Adventure Mode state machine (`event/adv_mode.cpp`, `26e434`–`26ed7c`).** `AdvModeTask` (vtable through GOT `c2a700`) loads all ten boards, sets up each player, then loops: a title task, the options task, and a dispatch on `BoardQuery::step` to the save, board menu, event, battle, result, shop and ending tasks. Each sub-task is a `SceneTask` allocated on the default heap and run through `SharedState::run_task` (`2ad584`), then deleted through its virtual destructor. The global `BoardQuery` (`c23250`) holds the state (`+4`), step (`+8`) and previous step (`+c`); its full 0xba08-byte layout, read from `BoardQuery::reset`, is now in `include/event/board_query.h` and shared with `adv_board.cpp`.
  - `run_save` matches with the failure branch written `step = 12; state = 2;`: in the other order the two `step` stores are sunk into one, while the original keeps `state`/`step` as one 64-bit store.
- **Duplicate names.** `check.py` now stops when `units.json` repeats a key or gives one name two addresses. `tools/add_symbols.py` adds names and refuses to remap an existing one.
- **Queue booleans.** They are `unsigned char` (tested with `and #0xff; cbnz`), not `bool`. Only `flag2` (`+2`) is `volatile`. That keeps cancel's two flag stores separate while letting `active` and `flag1` merge into the 16-bit clear. The entry reset is written state, callback, completion, argument, elapsed; the compiler then emits the original store order and pairing.

### Deferred

`2653dc` (4,964 bytes) is the panel system's large draw routine. It calls about twenty functions that aren't identified yet (`217d64`, `1e709c`, `1e73c0`, `1e41d8`, `2183c8`, ...) and needs its own round.

`45e160` (1,464 bytes) is a 61-case statistics switch with a jump table at `811194`. It calls at least six game functions whose signatures are unknown (`204728`, `203dfc`, `2028b4`, `200fc0`, `2015a8`, `200294`), so it needs its own effort. The four small virtuals at `45dcd0`–`45dd28` need their class and vtable identified first.

### Near misses

`266f6c`: two words. The two `fmul`s have their operands in the other order: the original puts the font size first while loading the group scale first, and every load order and operand order we tried keeps them together.

`2676ec`: the structure matches. Ours keeps `&start` in a callee-saved register (one more saved pair), and drops the null check before `rewind` in the screen-reset loop (the same pattern as `262e78` and `2669c0`).

`268340`, `269188`, `269238`, `269440`: the null-check pattern below (`play_screen` also schedules its pane loop differently).

`268a80`: the structure matches (kind masks `0x5e0`/`0x216`, the 176-cell board scan, the grid tables). The range tests come out in a different order and the early `return 0` is duplicated; the orderings tried so far made no difference.

`2696a8`: the null-check pattern below.

`269de0`, `269fa0`, `269fd8`, `26a080`: switch lowering. The original keeps small case sets as a `1 << x & mask` test that branches to `return 1`/`return 0` (and splits `held_kind` into three clusters); ours turns them into a bitmap lookup (`lsr mask, x; and #1`) or one cluster. `switch`, `||` chains, a loop over a table and an explicit mask all gave the same result, so this may be another compiler difference.

`26a98c`: `Player::setup` (1,788 bytes). The logic matches, including the inlined `cell_open`, `cell_cleared`, `cell_selectable` and `is_fort_kind` (its 68-entry jump table appears again at `7f52e8`). The fort-scan loop keeps a running flag in the original, and the frame is 0x20 bytes larger; four loop shapes all left about 320 words different.

`26b3cc`: `BoardQuery::find_entry`. The logic matches; the original places the non-flag `kind != 0` path after the loop and indexes the 28-entry tables through a sign-extended 64-bit counter.

`26c654`, `26c730`, `26c884`: the original reads `override` and `value6` with `and #0xffff0000; asr #16` (a redundant mask) and a load narrowed to `+4`; no bitfield layout tried reproduces that, so it may be another compiler difference. `26c610` is the switch-lowering case again.

`26c154`: `load_board` reads the board rows, cells, unit records, reward pairs and two short lists from two resource frames through a read/write stream. The logic matches; the resource id is a `csel` in ours and a branch in the original, and `ResourceFrame::is_open` is tested as a byte. `26c924`: `unit_has_override` (three jump tables, `is_fort_kind` inlined again); the logic matches, register use differs. Both capped at two attempts.

`26e824`: nine words, three byte stores scheduled earlier. `26eb54`: the case-3 constant is hoisted into the dispatch block in ours (block layout only). `26e4a8`: the logic matches; the step dispatch range checks and loop layout differ (108 of 213 words after two attempts).

`26d978`, `26da1c`: three and four words of scheduling (a store before or after the byte test, the order of two zeroing moves). `26dd70`: `advance_nightmare` (1,288 bytes, the mode-8 turn update with two 4-bit timers at `Player+2ad3`); the logic matches, one attempt.

`26cc30`, `26d124`, `26d6dc`: the logic matches; register use and scheduling differ (capped at two attempts). `26d124` inlines `neighbor_cell` both for the four neighbours and for a reverse direction search. `26cdec` is the accepted switch-lowering pattern.

`26b798`, `26bd64`: the structure matches; the rarity test in `26b798` is another switch-lowering case, and both differ in register allocation and stack layout (capped at two attempts).

`26a220`: only block placement differs. The original falls through to the `raw` return; ours branches to it.

`26a454`: the structure matches (DLC cells are closed or opened, then the gates shared with each neighbour are set to 3 or 4). Our build strength-reduces the cell pointer and keeps different values on the stack.

**Compiler probe (October 13, 2026).** `scratch/compiler_probe/probe.py` compiles one or two representatives of each suspected compiler-difference pattern (null check: `269188`, `2696a8`; switch lowering: `269fa0`, `26c610`; bitfield read: `26c884`) and three exact controls (`269544`, `269cfc`, `269c40`) with each locally available release. Clang 3.9.1 without `-regalloc=greedy` and with `-O2` gives byte-identical results to the project flags (greedy is already the default). `-regalloc=basic` is not registered in this build. `-regalloc=pbqp` breaks all three controls. Clang 3.8.1 breaks all three controls and still drops the null check; Clang 4.0.1 breaks two controls. No variant fixes any of the three patterns, so the project flags stay as they are. Clang 3.9.0 was not tried: it would need a new download.

**Null checks before virtual calls.** In `play_enter` the original drops the null check where the next use of the animation is a plain field store (`frame`), but keeps it wherever the next use is a virtual call. Our build drops both. One explanation that fits: the original compiler's SimplifyCFG check for "null makes this path undefined" does not look through the bitcast clang emits for the vtable load, while 3.9.1 does. This is a hypothesis; no source shape tried so far keeps the check.

`2669c0`: as in `262e78`, the original keeps the null check on the window animation before the unconditional `set_rate`, and we drop it. A reference helper made no difference.

`266b98`: one instruction short. Registers around the two inlined `finalize` copies and the `LightResource` destructors differ.

`26514c`: the original keeps the two-pass loop rolled; ours is fully unrolled. Disabling unrolling with a pragma (tried, not kept) leaves only register-allocation differences, so the loop shape is the main gap. What keeps the original's loop rolled is not known yet.

`264c28`: the icon arithmetic and layout logic are in place. Still different: the scale is selected as integer bits in the original (`csel w`) but as a float here (`fcsel s`), the grade icon's range branch has the other polarity, and the rank tests compile to a different compare chain.

`263d58`: the structure, frame and calls match. Still different is register allocation: the original materializes the 0.66 scale constant early (in w28) and keeps `&panes[0]` in a callee-saved register.

`2649cc`: everything but four instructions matches. The original recomputes the player address for the last `stage.step == 4` byte load; ours reuses it.

`263b3c`: the inlined outer constructor's stores differ only in order. The store at `+0x26b78` comes later, and the constant for one `+0x26a78` store is set up earlier. The order doesn't follow the source order: reversing the source, permuting the groups and splitting the records were all tried.

`261e24`: the passes, slot, marker and caption blocks match in structure. Still different: the frame is 16 bytes larger (one extra spill), the unrolled sort addresses `records[j]` through the pointers kept for the roster calls instead of through `sp`, and two instruction-schedule spots (the marker position pair and the caption position). We tried pointer forms of the query and sort loops, struct copies, `operator=` and field-wise swaps.

`262e78`: everything but four instructions matches. The original keeps the two null checks on `animation` before the unconditional `set_rate(2.0f)`. We drop them, because the null path then dereferences null and the optimizer removes it. A reference local, a play helper and a per-slot helper made no difference.

`261720`: the size matches (226 words). Still different: the mode-9 range test (the original builds `cset`/`orr`/`tbnz` without hoisting `kind - 0xde`), the jump-table cases (the original loads 37.0 before the range check and keeps one block per case; ours hoists the constants), and the icon selection (the original keeps `0x1bb7c` in a callee-saved register and `0xbe` in w20). We tried the block order, `|` vs `||`, nested ifs, initializers, declaration order and five forms of the icon selection.

`261aa8`: 139 of 223 words match exactly. The non-mode-8 tests stay branchy in the original, while ours turns the second test into `cset`/`and`. The mode-8 tests merge into a different boolean network. The draw tail matches.

`26031c`: everything but the two overflow tests matches. Every way of writing `next > 0x100` (also `0x100 < next`, `>= 0x101`, `int`, no temporary, inverted arms) comes out as `ult 0x101`.

`25e8a0`: everything but the final `time` clamp matches. The original keeps the `t < 0` compare alive for a second use, so the select is not turned into `fmax`. Ternaries, `if` chains, `std::max`-style helpers and an extra variable all compile to the single-use form.

`25dc08`: three independent stores before the `LightResource` constructor call come out in reverse order. Brace and value initialization, moving fields into the body, and a 12-byte flag struct were tried.

`25d19c`: the size matches (491 words). The original computes the cosine's sign as `eor` of two re-emitted compares and tests it with `tbz`/`tst #1`. Our DAG folds the same `xor i1` into a `cmp`. Typing the flag as `int`/`unsigned char`, keeping it in a local, or writing it differently in each branch made no difference. The sine's second select and the polynomial blocks also differ in register choice and order.

`25c6c0`: the original loads `values.w` together with `scale20`, adds early and pairs the `values.w` store with `values.z` at the end. All 24 orders of the four statements were tried, plus 180 orderings that split out the loads. The closest (`values.w` computed into a temporary first) differs in 4 instructions: its store pairs with `scale20` instead.

`25b4b4`, `25b5b8`, `25b754`: these differ only in argument-register setup order or one register copy. For `load`, about 15 variants of the tail and the allocation call were tried. For `open`, a direct call, a condition-declared size, a helper that checks for zero, and keeping the allocation result were tried. An inline allocation helper fixed the similar problem in `217188`, but here it improves `load` and makes `open_table` worse.

`258b0c`: the original loads `entries[0].callback` before the two `strb wzr` flag clears; ours loads it after the volatile `flag2` store. Non-volatile flags fix the order but let the DAG merge the flag stores in `cancel` and `register`.

`259260`: the original tests `flag2` with `tbz w8, #0`; ours uses `cbz w8`. An `unsigned char` flag tested with `& 1` produces `tbz`/`tbnz`, but it flips the block layout (59 words differ). Neither branch order fixes that.

`217294`: everything but register allocation matches. The original keeps `n` in w11 and the scan index in x10; we get the reverse. Changing the index type, the variable order, the loop form or the `found`/`goto`/`continue` shape didn't change it.

`258c64`: the grouping, the three exchange sorts and the write-back match in structure.
- **Copy blocks:** writing the counter increment after the copy keeps the three copy blocks from being tail-merged.
- **Priority helper:** written as a ternary, it gives the original block layout.
- **Still different:** the registry base and the running count use swapped registers. The waiting and empty write-back loops are scheduled differently, giving 328 words vs 326.