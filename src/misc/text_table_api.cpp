// Text table setup and shutdown entry points (0x710021366c-0x71002139f4): create, load and destroy
// the banked text tables through their own functions. Names are descriptive placeholders. Status:
// matching/README.md.

struct TextTable211744 {
    void unload();                                                          // 0x71002117d8
};
struct TextTable211c74 {
    void unload();                                                          // 0x7100211d08
    void load();                                                            // 0x7100211edc
};
struct TextTable212a08 {
    void unload();                                                          // 0x7100212a9c
    void load();                                                            // 0x7100212c0c
};
// Reached through the GOT slots at 0x7100c23340, 0x7100c23348 and 0x7100c23350.
extern TextTable211744* gTable_c23340;
extern TextTable211c74* gTable_c23348;
extern TextTable212a08* gTable_c23350;
void create_table_2116bc();                                                 // 0x71002116bc
void create_table_211be8();                                                 // 0x7100211be8
void create_table_21297c();                                                 // 0x710021297c
void destroy_table_211744();                                                // 0x7100211744
void destroy_table_211c74();                                                // 0x7100211c74
void destroy_table_212a08();                                                // 0x7100212a08

// 0x710021366c
void ensure_system_text_21366c() {
    if (!gTable_c23340)
        create_table_2116bc();
}

// 0x7100213684
void release_system_text_213684() {
    if (gTable_c23340) {
        gTable_c23340->unload();
        destroy_table_211744();
    }
}

// 0x7100213988
void ensure_stage_text_213988() {
    if (!gTable_c23348) {
        create_table_211be8();
        create_table_21297c();
    }
}

// 0x71002139b0
void release_stage_text_2139b0() {
    if (gTable_c23348) {
        gTable_c23348->unload();
        destroy_table_211c74();
    }
    if (gTable_c23350) {
        gTable_c23350->unload();
        destroy_table_212a08();
    }
}

// 0x71002139f4
void load_stage_text_2139f4() {
    if (gTable_c23348)
        gTable_c23348->load();
    if (gTable_c23350)
        gTable_c23350->load();
}