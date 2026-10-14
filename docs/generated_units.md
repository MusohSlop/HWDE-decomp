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
| `misc/virtual_calls.cpp` | functions with virtual calls | as `misc/call_functions3.cpp`, plus placeholder classes whose virtual methods `slot_K` stand for vtable slot `K` (slots not called are declared `void slot_K()`); some `callee_NNN` are known functions (for example `get_default_heap`, `DefaultHeap::release`) |

`NNN` is the function's address without the `0x7100` prefix, `OFF` a byte offset, `ADDR` a data
address and `FUNC` the address of the function using it. The same address can appear under several
placeholder names (for example one `callee_NNN` declaration per unit, or one global struct per
function); `data/units.json` maps each of them to the same address.
