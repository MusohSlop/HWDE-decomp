// Getter-then-call forwarders found by tools/family_scan.py: each fetches an object from a
// getter and passes its argument to one function on it (the same shape as game_query,
// 0x7100207ad8). Grouped here until their source files are linked; functions are named after
// their address, callees after theirs. Status: matching/README.md.

void* getter_458634();                                              // 0x7100458634

int object_call_458d5c(void* object, int value);               // 0x7100458d5c

void* getter_4449ec();                                              // 0x71004449ec

int object_call_446c24(void* object, int value);               // 0x7100446c24

void* getter_4140a4();                                              // 0x71004140a4

int object_call_414d6c(void* object, int value);               // 0x7100414d6c

int object_call_415440(void* object, int value);               // 0x7100415440

int object_call_446054(void* object, int value);               // 0x7100446054

void* getter_425dd0();                                              // 0x7100425dd0

int object_call_427244(void* object, int value);               // 0x7100427244

int object_call_427404(void* object, int value);               // 0x7100427404

int object_call_447d58(void* object, int value);               // 0x7100447d58

void* getter_3d2fd4();                                              // 0x71003d2fd4

int object_call_3d6864(void* object, int value);               // 0x71003d6864

// 0x71004522fc
int query_4522fc(int value) {
    return object_call_458d5c(getter_458634(), value);
}

// 0x7100452320
int query_452320(int value) {
    return object_call_446c24(getter_4449ec(), value);
}

// 0x710045236c
int query_45236c(int value) {
    return object_call_414d6c(getter_4140a4(), value);
}

// 0x7100452390
int query_452390(int value) {
    return object_call_415440(getter_4140a4(), value);
}

// 0x71004529f8
int query_4529f8(int value) {
    return object_call_446054(getter_4449ec(), value);
}

// 0x7100453dd0
int query_453dd0(int value) {
    return object_call_427244(getter_425dd0(), value);
}

// 0x7100454004
int query_454004(int value) {
    return object_call_427404(getter_425dd0(), value);
}

// 0x7100454454
int query_454454(int value) {
    return object_call_447d58(getter_4449ec(), value);
}

// 0x71004556a4
int query_4556a4(int value) {
    return object_call_3d6864(getter_3d2fd4(), value);
}
