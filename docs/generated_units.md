# Generated units

These units were produced by shape and symbolic-execution generators rather than written by hand.
Every function in them matches, and functions that did not compile or did not match were left out.
Their types and names are placeholders, kept here for a later naming pass that merges them onto
real classes.

| Unit | Generator | Placeholders used |
| --- | --- | --- |
| `misc/tiny_shapes.cpp` | tiny shapes (8-16 bytes) | `ObjNNN`/`PairNNN`/`HolderNNN` structs with one or two fields; `gData_NNN` GOT objects; `callee_NNN` |
| `misc/tiny_shapes2.cpp` | tiny shapes, second set (8-32 bytes) | `gGot_NNN`/`gLocal_NNN` globals; `HolderNNN`/`RecordNNN`/`ItemNNN`/`FlagsNNN` structs; `callee_NNN` |
| `misc/forwarders.cpp` | register tracking, tail calls | `gGlobal_NNN` GOT values; `callee_NNN` with `void*`/`int` parameters |
| `misc/forwarders2.cpp` | register tracking with argument fields | `ArgNNN_k` argument structs (`field_OFF`, `part_OFF`); `gObject_NNN`, `gLocal_NNN`, `gLocalValue_NNN` |
| `misc/leaf_functions.cpp` | straight-line leaves | `ArgNNN_k`/`NodeNNN_...` structs with `field_OFF` |
| `misc/leaf_functions2.cpp` | leaves with compares and selects | as above |
| `misc/branch_functions.cpp` | leaves with forward branches | as above |
| `misc/call_functions.cpp` | functions with calls | as above, plus `callee_NNN` declarations and named locals `vN` (loads) and `cN` (call results) |
| `misc/call_functions2.cpp` | functions with calls and globals | as above, plus per-function global structs `GlobalADDR_FUNC`/`LocalADDR_FUNC` (objects `gGlobalADDR_FUNC`); callees take struct pointers as `void*` |
| `misc/call_functions3.cpp` | functions with calls, up to 256 bytes | as `misc/call_functions2.cpp`, plus `movk` constants and `ubfx` extracts |
| `misc/branch_functions2.cpp` | leaves with forward branches, 120-256 bytes | as `misc/branch_functions.cpp` |
| `misc/call_functions4.cpp` | functions with calls, 256-480 bytes | as `misc/call_functions3.cpp` |
| `misc/stack_functions.cpp` | functions with stack locals | as `misc/virtual_calls.cpp`; address-taken stack regions are ordinary locals `local_OFF` (struct type `StackOFF_FUNC` when they have several fields), no frame structs |
| `misc/general_functions.cpp` | combined generator (calls, virtual calls, stack locals, guards, jumps back to shared return blocks) | as `misc/stack_functions.cpp` and `misc/virtual_calls.cpp` |
| `misc/general_functions2.cpp` | combined generator with arrays, pair accesses and writeback | as `misc/general_functions.cpp`, plus array fields `field_OFF[1]` indexed by the access |
| `misc/general_functions3.cpp` | combined generator with floats | as `misc/general_functions2.cpp`, plus float parameters `fN` listed after the integer ones |
| `misc/general_functions4.cpp` | combined generator with type-clash casts and unified returns | as `misc/general_functions3.cpp` |
| `misc/general_functions5.cpp` | combined generator with if/else structuring | as `misc/general_functions4.cpp`, plus merged locals `mN` assigned in both branches |
| `misc/variant_functions.cpp` | combined generator with a per-function variant search | as `misc/general_functions5.cpp` |
| `misc/variant_functions2.cpp` | variant search, second run | as `misc/general_functions5.cpp` |
| `misc/variant_functions3.cpp` | variant search, third run | as `misc/general_functions5.cpp` |
| `misc/variant_functions4.cpp` | variant search, fourth run (swapped early-return ifs) | as `misc/general_functions5.cpp` |
| `misc/variant_functions5.cpp` | variant search, fifth run (element access, page objects) | as `misc/general_functions5.cpp`, plus element structs `ElemFUNC_N` sized to their stride |
| `misc/switches/switch_NNN.cpp` | generated switches, one per unit with the jump table mapped as `.rodata` | as `misc/general_functions5.cpp` |
| `misc/variant_functions6.cpp` | variant search, sixth run (tail calls anywhere) | as `misc/variant_functions5.cpp` |
| `misc/variant_functions7.cpp` | variant search, seventh run | as `misc/variant_functions5.cpp` |
| `misc/loop_functions3.cpp` | loop generator on the newest combined generator | as `misc/loop_functions2.cpp` |
| `misc/variant_functions8.cpp` | variant search, eighth run (nested if/else regions) | as `misc/variant_functions5.cpp` |
| `misc/variant_functions9.cpp` | variant search, ninth run (float constants and returns) | as `misc/variant_functions5.cpp` |
| `misc/variant_functions10.cpp`, `misc/variant_functions11.cpp` | variant search, tenth and eleventh runs | as `misc/variant_functions5.cpp` |
| `misc/variant_functions12.cpp` | variant search, twelfth run (zero-extension) | as `misc/variant_functions5.cpp` |
| `misc/variant_functions13.cpp`, `misc/variant_functions14.cpp` | variant search, thirteenth and fourteenth runs | as `misc/variant_functions5.cpp` |
| `misc/variant_functions15.cpp` | variant search, fifteenth run (inner element arrays, byte-offset indexes) | as `misc/variant_functions5.cpp`, plus byte arrays `field_OFF[1]` read through casts |
| `misc/variant_functions16.cpp` | variant search, sixteenth run (named imports) | as `misc/variant_functions5.cpp`; library calls use their real names |
| `misc/variant_functions17.cpp` | variant search, seventeenth run (byte-offset and selected bases) | as `misc/variant_functions5.cpp`, plus `BytesFUNC_N`/`PickedFUNC_N` structs |
| `misc/variant_functions18.cpp` | variant search, eighteenth run (signed narrow loads, clamped element index) | as `misc/variant_functions17.cpp` |
| `misc/variant_functions19.cpp` | variant search, nineteenth run (dead merges dropped, void tail-call functions) | as `misc/variant_functions17.cpp` |
| `misc/variant_functions20.cpp` | variant search, twentieth run (callee overloads and second names) | as `misc/variant_functions17.cpp`; `callee2_ADDR`/`callee3_ADDR` are second placeholder names for `callee_ADDR` |
| `misc/variant_functions21.cpp` | variant search, twenty-first run (compile-error fixes) | as `misc/variant_functions20.cpp` |
| `misc/variant_functions22.cpp` | variant search, twenty-second run (shifted operands, zero-extended parameters, large constant offsets) | as `misc/variant_functions20.cpp` |
| `misc/variant_functions23.cpp` | variant search, twenty-third run (function-pointer calls, extended operands) | as `misc/variant_functions20.cpp` |
| `misc/variant_functions24.cpp` | variant search, twenty-fourth run (extends, float pairs, `Float2` returns) | as `misc/variant_functions20.cpp`; `Float2` is a placeholder for a two-float struct |
| `misc/variant_functions25.cpp` | variant search, twenty-fifth run (vector fields, narrow parameters) | as `misc/variant_functions20.cpp`; `Vec4f` is a placeholder for a 16-byte vector type |
| `misc/variant_functions26.cpp` | variant search, twenty-sixth run (loops) | as `misc/variant_functions20.cpp`, plus `ElemFUNC_rN` element structs of pointer loop variables |
| `misc/variant_functions27.cpp` | variant search, twenty-seventh run (sequential loops) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions28.cpp` | variant search, twenty-eighth run (index loops) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions29.cpp` | variant search, twenty-ninth run (branches inside loops) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions30.cpp` | variant search, thirtieth run (stack objects padded to the frame) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions31.cpp` | variant search, thirty-first run (joins at post-dominators) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions32.cpp` | variant search, thirty-second run (16-bit range tests) | as `misc/variant_functions26.cpp` |
| `misc/loop_functions.cpp` | one bottom-tested loop | as `misc/general_functions.cpp`, plus loop-carried locals `rN` updated at the end of a `do`/`while` |
| `misc/loop_functions2.cpp` | loops with if/else bodies and pointer induction variables | as `misc/loop_functions.cpp`, plus element structs `ElemFUNC_rN` sized to the stride |
| `misc/virtual_calls.cpp` | functions with virtual calls | as `misc/call_functions3.cpp`, plus placeholder classes whose virtual methods `slot_K` stand for vtable slot `K` (slots not called are declared `void slot_K()`); some `callee_NNN` are known functions (for example `get_default_heap`, `DefaultHeap::release`) |

`NNN` is the function's address without the `0x7100` prefix, `OFF` a byte offset, `ADDR` a data
address and `FUNC` the address of the function using it. The same address can appear under several
placeholder names (for example one `callee_NNN` declaration per unit, or one global struct per
function); `data/units.json` maps each of them to the same address.
