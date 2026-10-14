// Type chain getters (0x71001e47a4, 0x71001e4874, 0x71001e4a1c, 0x71005d08f8, 0x71005fcd4c): each
// returns a function-local type node whose parent is the node of its base type, built on first
// use through guarded statics. The getters are template instances, so the nodes and guards are
// shared symbols reached through the GOT. Found by tools/family_scan.py. Names are descriptive
// placeholders. Status: matching/README.md.

#include "misc/type_node.h"

template struct TypeOf<Actor1e47a4>;  // get: 0x71001e47a4
template struct TypeOf<Actor1e4874>;  // get: 0x71001e4874
template struct TypeOf<Actor1e4a1c>;  // get: 0x71001e4a1c
template struct TypeOf<Task5d08f8>;   // get: 0x71005d08f8
template struct TypeOf<System5fcd4c>; // get: 0x71005fcd4c
