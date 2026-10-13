// Global forwarders with an argument, found by tools/family_scan.py: each passes its argument
// to one function on the object held in a global (the same shape as query_game_state,
// 0x71002587b4). Grouped here until their source files are linked; functions are named after
// their address, callees after theirs. Status: matching/README.md.

// Reached through the GOT slot at 0x7100c21690.
extern void* gGlobal_c21690;

void global_call_2113c(void* object, int value);              // 0x710002113c

void global_call_2118c(void* object, int value);              // 0x710002118c

void global_call_21554(void* object, int value);              // 0x7100021554

void global_call_21600(void* object, int value);              // 0x7100021600

void global_call_218a4(void* object, int value);              // 0x71000218a4

void global_call_21b28(void* object, int value);              // 0x7100021b28

void global_call_22d08(void* object, int value);              // 0x7100022d08

void global_call_2183c(void* object, int value);              // 0x710002183c

// Reached through the GOT slot at 0x7100c22058.
extern void* gGlobal_c22058;

void global_call_63dc8(void* object, int value);              // 0x7100063dc8

void global_call_64aa0(void* object, int value);              // 0x7100064aa0

void global_call_64b48(void* object, int value);              // 0x7100064b48

void global_call_64c08(void* object, int value);              // 0x7100064c08

void global_call_64cb4(void* object, int value);              // 0x7100064cb4

void global_call_65778(void* object, int value);              // 0x7100065778

void global_call_65060(void* object, int value);              // 0x7100065060

void global_call_6522c(void* object, int value);              // 0x710006522c

void global_call_6a9f0(void* object, int value);              // 0x710006a9f0

void global_call_6aa48(void* object, int value);              // 0x710006aa48

void global_call_66b70(void* object, int value);              // 0x7100066b70

// Reached through the GOT slot at 0x7100c21df8.
extern void* gStageLights;

void global_call_1fb214(void* object, int value);              // 0x71001fb214

// Reached through the GOT slot at 0x7100c21708.
extern void* gGlobal_c21708;

void global_call_23bc00(void* object, int value);              // 0x710023bc00

void global_call_23bd34(void* object, int value);              // 0x710023bd34

void global_call_23bd98(void* object, int value);              // 0x710023bd98

void global_call_23be18(void* object, int value);              // 0x710023be18

void global_call_23be7c(void* object, int value);              // 0x710023be7c

void global_call_23bf1c(void* object, int value);              // 0x710023bf1c

void global_call_23c5c8(void* object, int value);              // 0x710023c5c8

void global_call_23cc74(void* object, int value);              // 0x710023cc74

void global_call_23d9f4(void* object, int value);              // 0x710023d9f4

// Reached through the GOT slot at 0x7100c2a5a8.
extern void* gDemoPlayer;

void global_call_25179c(void* object, int value);              // 0x710025179c

// Reached through the GOT slot at 0x7100c22d68.
extern void* gGameState;

void global_call_254964(void* object, int value);              // 0x7100254964

// Reached through the GOT slot at 0x7100c22d58.
extern void* gGlobal_c22d58;

void global_call_3ed870(void* object, int value);              // 0x71003ed870

// Reached through the GOT slot at 0x7100c2b700.
extern void* gGlobal_c2b700;

void global_call_3f850c(void* object, int value);              // 0x71003f850c

// Reached through the GOT slot at 0x7100c21880.
extern void* gSequencer;

void global_call_3df600(void* object, int value);              // 0x71003df600

// 0x710003f15c
void forward_3f15c(int value) {
    global_call_2113c(gGlobal_c21690, value);
}

// 0x710003f174
void forward_3f174(int value) {
    global_call_2118c(gGlobal_c21690, value);
}

// 0x710003f1c0
void forward_3f1c0(int value) {
    global_call_21554(gGlobal_c21690, value);
}

// 0x710003f1d8
void forward_3f1d8(int value) {
    global_call_21600(gGlobal_c21690, value);
}

// 0x710003f2e8
void forward_3f2e8(int value) {
    global_call_218a4(gGlobal_c21690, value);
}

// 0x710003f620
void forward_3f620(int value) {
    global_call_21b28(gGlobal_c21690, value);
}

// 0x710003fa1c
void forward_3fa1c(int value) {
    global_call_22d08(gGlobal_c21690, value);
}

// 0x7100043f34
void forward_43f34(int value) {
    global_call_2183c(gGlobal_c21690, value);
}

// 0x710006e40c
void forward_6e40c(int value) {
    global_call_63dc8(gGlobal_c22058, value);
}

// 0x710006e714
void forward_6e714(int value) {
    global_call_64aa0(gGlobal_c22058, value);
}

// 0x710006e72c
void forward_6e72c(int value) {
    global_call_64b48(gGlobal_c22058, value);
}

// 0x710006e744
void forward_6e744(int value) {
    global_call_64c08(gGlobal_c22058, value);
}

// 0x710006e75c
void forward_6e75c(int value) {
    global_call_64cb4(gGlobal_c22058, value);
}

// 0x710006e99c
void forward_6e99c(int value) {
    global_call_65778(gGlobal_c22058, value);
}

// 0x710006e9c4
void forward_6e9c4(int value) {
    global_call_65060(gGlobal_c22058, value);
}

// 0x710006e9dc
void forward_6e9dc(int value) {
    global_call_6522c(gGlobal_c22058, value);
}

// 0x710006ea74
void forward_6ea74(int value) {
    global_call_6a9f0(gGlobal_c22058, value);
}

// 0x710006ea8c
void forward_6ea8c(int value) {
    global_call_6aa48(gGlobal_c22058, value);
}

// 0x710006f764
void forward_6f764(int value) {
    global_call_66b70(gGlobal_c22058, value);
}

// 0x710017dff0
void forward_17dff0(int value) {
    global_call_1fb214(gStageLights, value);
}

// 0x7100241af8
void forward_241af8(int value) {
    global_call_23bc00(gGlobal_c21708, value);
}

// 0x7100241b90
void forward_241b90(int value) {
    global_call_23bd34(gGlobal_c21708, value);
}

// 0x7100241ba8
void forward_241ba8(int value) {
    global_call_23bd98(gGlobal_c21708, value);
}

// 0x7100241bc0
void forward_241bc0(int value) {
    global_call_23be18(gGlobal_c21708, value);
}

// 0x7100241bd8
void forward_241bd8(int value) {
    global_call_23be7c(gGlobal_c21708, value);
}

// 0x7100241bf0
void forward_241bf0(int value) {
    global_call_23bf1c(gGlobal_c21708, value);
}

// 0x7100241c50
void forward_241c50(int value) {
    global_call_23c5c8(gGlobal_c21708, value);
}

// 0x7100241c78
void forward_241c78(int value) {
    global_call_23cc74(gGlobal_c21708, value);
}

// 0x7100241fa0
void forward_241fa0(int value) {
    global_call_23d9f4(gGlobal_c21708, value);
}

// 0x7100256660
void forward_256660(int value) {
    global_call_25179c(gDemoPlayer, value);
}

// 0x71002581ac
void forward_2581ac(int value) {
    global_call_254964(gGameState, value);
}

// 0x71003e8148
void forward_3e8148(int value) {
    global_call_3ed870(gGlobal_c22d58, value);
}

// 0x71003fa724
void forward_3fa724(int value) {
    global_call_3f850c(gGlobal_c2b700, value);
}

// 0x7100455944
void forward_455944(int value) {
    global_call_3df600(gSequencer, value);
}
