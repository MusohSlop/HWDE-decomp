// Global getters found by tools/family_scan.py: each returns the pointer held in one global
// (the same shape as screen_fader, 0x71001e50b0). They sit in their owners' source files across
// the image and are grouped here until those files are linked; globals without a known role
// are named after their GOT slot, getters after their address. Status: matching/README.md.

// Two globals whose getters return their second word.
struct GlobalPair {
    void* first;
    void* second;
};

// Reached through the GOT slot at 0x7100c22a50.
extern void* gSingleton_c22a50;

// Reached through the GOT slot at 0x7100c22cb8.
extern void* gSingleton_c22cb8;

// Reached through the GOT slot at 0x7100c22cd8.
extern void* gSingleton_c22cd8;

// Reached through the GOT slot at 0x7100c22e10.
extern void* gSingleton_c22e10;

// Reached through the GOT slot at 0x7100c22e68.
extern void* gSingleton_c22e68;

// Reached through the GOT slot at 0x7100c23218.
extern void* gSingleton_c23218;

// Reached through the GOT slot at 0x7100c23220.
extern void* gSingleton_c23220;

// Reached through the GOT slot at 0x7100c23230.
extern void* gSingleton_c23230;

// Reached through the GOT slot at 0x7100c23238.
extern void* gSingleton_c23238;

// Reached through the GOT slot at 0x7100c23240.
extern void* gSingleton_c23240;

// Reached through the GOT slot at 0x7100c23260.
extern void* gSingleton_c23260;

// Reached through the GOT slot at 0x7100c23268.
extern void* gSingleton_c23268;

// Reached through the GOT slot at 0x7100c23270.
extern void* gSingleton_c23270;

// Reached through the GOT slot at 0x7100c23288.
extern void* gGlobal_c23288;

// Reached through the GOT slot at 0x7100c23290.
extern void* gGlobal_c23290;

// Reached through the GOT slot at 0x7100c23298.
extern void* gSingleton_c23298;

// Reached through the GOT slot at 0x7100c232a0.
extern void* gSingleton_c232a0;

// Reached through the GOT slot at 0x7100c232a8.
extern void* gSingleton_c232a8;

// Reached through the GOT slot at 0x7100c232b0.
extern void* gSingleton_c232b0;

// Reached through the GOT slot at 0x7100c232b8.
extern void* gSingleton_c232b8;

// Reached through the GOT slot at 0x7100c232c0.
extern void* gSingleton_c232c0;

// Reached through the GOT slot at 0x7100c232c8.
extern void* gSingleton_c232c8;

// Reached through the GOT slot at 0x7100c232e0.
extern void* gSingleton_c232e0;

// Reached through the GOT slot at 0x7100c23308.
extern void* gGlobal_c23308;

// Reached through the GOT slot at 0x7100c23310.
extern void* gGlobal_c23310;

// Reached through the GOT slot at 0x7100c23320.
extern void* gSingleton_c23320;

// Reached through the GOT slot at 0x7100c23330.
extern void* gSingleton_c23330;

// Reached through the GOT slot at 0x7100c23338.
extern void* gSingleton_c23338;

// Reached through the GOT slot at 0x7100c23350.
extern void* gGlobal_c23350;

// Reached through the GOT slot at 0x7100c23360.
extern void* gSingleton_c23360;

// Reached through the GOT slot at 0x7100c23358.
extern void* gSingleton_c23358;

// Reached through the GOT slot at 0x7100c23370.
extern void* gSingleton_c23370;

// Reached through the GOT slot at 0x7100c23378.
extern void* gSingleton_c23378;

// Reached through the GOT slot at 0x7100c23368.
extern void* gSingleton_c23368;

// Reached through the GOT slot at 0x7100c23380.
extern void* gSingleton_c23380;

// Reached through the GOT slot at 0x7100c23390.
extern void* gSingleton_c23390;

// Reached through the GOT slot at 0x7100c2a528.
extern void* gSingleton_c2a528;

// Reached through the GOT slot at 0x7100c2ab80.
extern void* gGlobal_c2ab80;

// Reached through the GOT slot at 0x7100c2ae58.
extern void* gGlobal_c2ae58;

// Reached through the GOT slot at 0x7100c2b380.
extern void* gGlobal_c2b380;

// Reached through the GOT slot at 0x7100c2b5e8.
extern void* gGlobal_c2b5e8;

// Reached through the GOT slot at 0x7100c2b758.
extern void* gSingleton_c2b758;

// Reached through the GOT slot at 0x7100c2b7d8.
extern void* gGlobal_c2b7d8;

// Reached through the GOT slot at 0x7100c2b8d0.
extern void* gGlobal_c2b8d0;

// Reached through the GOT slot at 0x7100c2ba60.
extern void* gGlobal_c2ba60;

// Reached through the GOT slot at 0x7100c2ba80.
extern void* gGlobal_c2ba80;

// Reached through the GOT slot at 0x7100c2ba88.
extern void* gGlobal_c2ba88;

// Reached through the GOT slot at 0x7100c2ba90.
extern void* gSingleton_c2ba90;

// Reached through the GOT slot at 0x7100c2bb30.
extern void* gGlobal_c2bb30;

// Reached through the GOT slot at 0x7100c2bb40.
extern void* gGlobal_c2bb40;

// Reached through the GOT slot at 0x7100c2bb48.
extern void* gGlobal_c2bb48;

// Reached through the GOT slot at 0x7100c2bb60.
extern void* gGlobal_c2bb60;

// Reached through the GOT slot at 0x7100c2bb70.
extern GlobalPair gGlobal_c2bb70;

// Reached through the GOT slot at 0x7100c2bb78.
extern GlobalPair gGlobal_c2bb78;

// Reached through the GOT slot at 0x7100c2bbb8.
extern void* gSingleton_c2bbb8;

// Reached through the GOT slot at 0x7100c2cb70.
extern void* gGlobal_c2cb70;

// Reached through the GOT slot at 0x7100c21db0.
extern void* gResourceLoader;

// 0x71000d86c4
void* load_global_d86c4() {
    return gSingleton_c22a50;
}

// 0x71001469a8
void* load_global_1469a8() {
    return gSingleton_c22cb8;
}

// 0x71001649fc
void* load_global_1649fc() {
    return gSingleton_c22cd8;
}

// 0x7100187590
void* load_global_187590() {
    return gSingleton_c22e10;
}

// 0x71001a9c80
void* load_global_1a9c80() {
    return gSingleton_c22e68;
}

// 0x71001fe7c8
void* load_global_1fe7c8() {
    return gSingleton_c23218;
}

// 0x71001feb28
void* load_global_1feb28() {
    return gSingleton_c23220;
}

// 0x7100200fc0
void* load_global_200fc0() {
    return gSingleton_c23230;
}

// 0x7100201604
void* load_global_201604() {
    return gSingleton_c23238;
}

// 0x71002017c0
void* load_global_2017c0() {
    return gSingleton_c23240;
}

// 0x7100204ca8
void* load_global_204ca8() {
    return gSingleton_c23260;
}

// 0x710020710c
void* load_global_20710c() {
    return gSingleton_c23268;
}

// 0x71002074c0
void* load_global_2074c0() {
    return gSingleton_c23270;
}

// 0x7100208a70
void* load_global_208a70() {
    return gGlobal_c23288;
}

// 0x7100208e28
void* load_global_208e28() {
    return gGlobal_c23290;
}

// 0x7100209a34
void* load_global_209a34() {
    return gSingleton_c23298;
}

// 0x7100209cb4
void* load_global_209cb4() {
    return gSingleton_c232a0;
}

// 0x710020a31c
void* load_global_20a31c() {
    return gSingleton_c232a8;
}

// 0x710020acb0
void* load_global_20acb0() {
    return gSingleton_c232b0;
}

// 0x710020b29c
void* load_global_20b29c() {
    return gSingleton_c232b8;
}

// 0x710020b3d8
void* load_global_20b3d8() {
    return gSingleton_c232c0;
}

// 0x710020b60c
void* load_global_20b60c() {
    return gSingleton_c232c8;
}

// 0x710020c630
void* load_global_20c630() {
    return gSingleton_c232e0;
}

// 0x710020ef00
void* load_global_20ef00() {
    return gGlobal_c23308;
}

// 0x710020f130
void* load_global_20f130() {
    return gGlobal_c23310;
}

// 0x710020fbd4
void* load_global_20fbd4() {
    return gSingleton_c23320;
}

// 0x7100210328
void* load_global_210328() {
    return gSingleton_c23330;
}

// 0x710021069c
void* load_global_21069c() {
    return gSingleton_c23338;
}

// 0x71002123f0
void* load_global_2123f0() {
    return gGlobal_c23350;
}

// 0x7100214000
void* load_global_214000() {
    return gSingleton_c23360;
}

// 0x7100214890
void* load_global_214890() {
    return gSingleton_c23358;
}

// 0x7100214b80
void* load_global_214b80() {
    return gSingleton_c23370;
}

// 0x7100214d88
void* load_global_214d88() {
    return gSingleton_c23378;
}

// 0x71002151a0
void* load_global_2151a0() {
    return gSingleton_c23368;
}

// 0x7100215468
void* load_global_215468() {
    return gSingleton_c23380;
}

// 0x7100216d48
void* load_global_216d48() {
    return gSingleton_c23390;
}

// 0x7100248b6c
void* load_global_248b6c() {
    return gSingleton_c2a528;
}

// 0x71002da374
void* load_global_2da374() {
    return gGlobal_c2ab80;
}

// 0x7100334a04
void* load_global_334a04() {
    return gGlobal_c2ae58;
}

// 0x71003abbe0
void* load_global_3abbe0() {
    return gGlobal_c2b380;
}

// 0x71003d2fd4
void* load_global_3d2fd4() {
    return gGlobal_c2b5e8;
}

// 0x710040d628
void* load_global_40d628() {
    return gSingleton_c2b758;
}

// 0x71004140a4
void* load_global_4140a4() {
    return gGlobal_c2b7d8;
}

// 0x7100425dd0
void* load_global_425dd0() {
    return gGlobal_c2b8d0;
}

// 0x710043cf64
void* load_global_43cf64() {
    return gGlobal_c2ba60;
}

// 0x71004449ec
void* load_global_4449ec() {
    return gGlobal_c2ba80;
}

// 0x7100448534
void* load_global_448534() {
    return gGlobal_c2ba88;
}

// 0x710044bc20
void* load_global_44bc20() {
    return gSingleton_c2ba90;
}

// 0x710045164c
void* load_global_45164c() {
    return gGlobal_c2bb30;
}

// 0x7100455ebc
void* load_global_455ebc() {
    return gGlobal_c2bb40;
}

// 0x7100458634
void* load_global_458634() {
    return gGlobal_c2bb48;
}

// 0x71004599b4
void* load_global_4599b4() {
    return gGlobal_c2bb60;
}

// 0x71004599c4
void* load_global_4599c4() {
    return gGlobal_c2bb70.second;
}

// 0x71004599d4
void* load_global_4599d4() {
    return gGlobal_c2bb78.second;
}

// 0x710045ceb4
void* load_global_45ceb4() {
    return gSingleton_c2bbb8;
}

// 0x710049732c
void* load_global_49732c() {
    return gGlobal_c2cb70;
}

// 0x7100531e0c
void* load_global_531e0c() {
    return gResourceLoader;
}

// 0x71005326b8
void* load_global_5326b8() {
    return gResourceLoader;
}

// 0x71005337b0
void* load_global_5337b0() {
    return gResourceLoader;
}

// 0x71005340dc
void* load_global_5340dc() {
    return gResourceLoader;
}
