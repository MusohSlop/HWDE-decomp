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
| `misc/variant_functions33.cpp` | variant search, thirty-third run (virtual call results inlined) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions34.cpp` | variant search, thirty-fourth run (functions of 401 to 1,500 bytes) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions35.cpp` | variant search, thirty-fifth run (functions of 1,501 to 6,000 bytes) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions36.cpp` | variant search, thirty-sixth run (two-level arrays, pointer arrays) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions37.cpp` | variant search, thirty-seventh run (stack arguments, nested loops, split constant stores) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions38.cpp` | variant search, thirty-eighth run (64-bit constant fields) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions39.cpp` | variant search, thirty-ninth run (merged bases) | as `misc/variant_functions26.cpp`, plus `MnFUNC` structs of merged pointers |
| `misc/variant_functions40.cpp` | variant search, fortieth run (overloads within a function) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions41.cpp` | variant search, forty-first run (framed stack arguments, spills, more instructions) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions42.cpp` | variant search, forty-second run (struct inner elements) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions43.cpp` | variant search, forty-third run (conditional increments) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions44.cpp` | variant search, forty-fourth run (address arguments taken early) | as `misc/variant_functions26.cpp` |
| `misc/large_functions.cpp` | two of the largest functions (`3b8504`, `462678`) | as `misc/variant_functions26.cpp`; the name strings of `462678` are `gLocalADDR_462678` data placeholders mapped to their original addresses |
| `misc/variant_functions45.cpp` | variant search, forty-fifth run (member addresses, 1,501 to 6,000 bytes) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions46.cpp` | variant search, forty-sixth run (test of the parallel search) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions47.cpp` | variant search, forty-seventh run (the whole 8 to 1,500 byte band) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions48.cpp` | variant search, forty-eighth run (knob combinations) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions49.cpp` | variant search, forty-ninth run (byte arrays in elements, loop fixes) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions50.cpp` | variant search, fiftieth run (loops unrolled by two) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions51.cpp` | variant search, fifty-first run (unions, merged constant stores) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions52.cpp` | variant search, fifty-second run (fixed parallel runner) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions53.cpp` | `ef298` (member-array loop) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions54.cpp` | variant search, fifty-fourth run (byte offsets from loaded sizes) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions55.cpp` | variant search, fifty-fifth run (merged generator) | as `misc/variant_functions26.cpp`; vector constants are `(Vec4f){...}` literals |
| `misc/variant_functions56.cpp` | variant search, fifty-sixth run (newly generating functions) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions57.cpp` | variant search, fifty-seventh run (joins inside loops) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions58.cpp` | variant search, fifty-eighth run (untouched argument registers) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions59.cpp` | variant search, fifty-ninth run (variadic stubs) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions60.cpp`, `misc/variant_functions60_2.cpp` | variant search, sixtieth run (switch statements; a second unit for a table apart from the first) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions61.cpp` | variant search, sixty-first run (every generating, unmatched function below `0x7100380000` after the int return fix) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions62.cpp` | variant search, sixty-second run (functions changed by known callee arity, bitfield writes and constant division) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions63.cpp` | variant search, sixty-third run (functions changed by signed and 64-bit constant division and paired int loads) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions64.cpp` | variant search, sixty-fourth run (structs returned through `x8`) | as `misc/variant_functions26.cpp` |
| `misc/variant_functions65.cpp` | variant search, sixty-fifth run (`voidret` over every generating, unmatched function below `0x7100380000`) | as `misc/variant_functions26.cpp` |
| `misc/s2_functions1.cpp` | second session, first run over `0x7100380000` and up (the whole 4-byte constant pool, 16-byte vector constants from the literal pool) | as `misc/variant_functions26.cpp`; vector constants are `(Vec4f){...}` literals, mapped through `.rodata.cst16` |
| `misc/s2_functions2.cpp` | second session, second run (float stack slots, `sqrtf`, float branches, indexed floats) | as `misc/s2_functions1.cpp` |
| `misc/s2_functions3.cpp` | second session, third run (constant-store fields retyped, integer reads of two widths; only the newly generated functions) | as `misc/s2_functions1.cpp` |
| `misc/s2_functions4.cpp` | second session, vector step 1 (vector arithmetic, fused multiply-adds by lane) | as `misc/s2_functions1.cpp`; `Vec4f` is an `ext_vector_type(4)` float, fused multiply-adds are `arm_neon.h` intrinsics on `float32x4_t` casts |
| `misc/s2_functions5.cpp` | second session, vector steps 2-4 with the loop and call-register fixes of `master` (only the newly generated functions) | as `misc/s2_functions4.cpp` |
| `misc/s2_functions6.cpp` | second session, vector step 5 (lane inserts; only the newly generated functions) | as `misc/s2_functions4.cpp`; lane inserts use the unit helpers `vins` and `vundef` |
| `misc/s2_functions7.cpp` | second session, vector step 6 (vector addressing; only the newly generated functions) | as `misc/s2_functions4.cpp` |
| `misc/s2_functions8.cpp` | second session, int returns where the original never sign-extends (`noretint`; the functions whose generated code had an extra `sxtw x0`) | as `misc/s2_functions1.cpp` |
| `misc/s2_functions9.cpp` | second session, rerun of every generating but unmatched function over `0x7100380000` and up after `noretint` and `nosextarg` | as `misc/s2_functions1.cpp` |
| `misc/s2_functions10.cpp` | second session, argument counts from known callee names (`noknownarity`; only the functions whose generated code changed) | as `misc/s2_functions1.cpp` |
| `misc/s2_functions11.cpp` | second session, bitfield writes and constant division (`nobitfield`, `nodivmagic`; only the functions whose generated code changed) | as `misc/s2_functions1.cpp`; bitfield fields are unions of the whole field and `bfOFF_START` bitfields |
| `misc/s2_functions12.cpp` | second session, paired int loads and pointer-plus-constant as byte-pointer arithmetic (`nopair32`, `noptradd`; only the functions whose generated code changed) | as `misc/s2_functions1.cpp` |
| `misc/s2_functions13.cpp` | second session, void functions (`voidret`, `voidret+sink`, `voidret+callinline`, with address hoisting on) over every generating but unmatched function of `0x7100380000` and up | as `misc/s2_functions1.cpp`; hoisted member addresses are locals `aN` |
| `misc/s2_functions14.cpp` | second session, member addresses computed early (only the functions with such an address; `nohoistaddr` turns it off) | as `misc/s2_functions13.cpp` |
| `misc/loop_functions.cpp` | one bottom-tested loop | as `misc/general_functions.cpp`, plus loop-carried locals `rN` updated at the end of a `do`/`while` |
| `misc/loop_functions2.cpp` | loops with if/else bodies and pointer induction variables | as `misc/loop_functions.cpp`, plus element structs `ElemFUNC_rN` sized to the stride |
| `misc/virtual_calls.cpp` | functions with virtual calls | as `misc/call_functions3.cpp`, plus placeholder classes whose virtual methods `slot_K` stand for vtable slot `K` (slots not called are declared `void slot_K()`); some `callee_NNN` are known functions (for example `get_default_heap`, `DefaultHeap::release`) |

`NNN` is the function's address without the `0x7100` prefix, `OFF` a byte offset, `ADDR` a data
address and `FUNC` the address of the function using it. The same address can appear under several
placeholder names (for example one `callee_NNN` declaration per unit, or one global struct per
function); `data/units.json` maps each of them to the same address.
