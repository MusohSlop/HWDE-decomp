// Declarations shared by the generated accessor files (misc/tiny_pairs2.cpp). Names are descriptive
// placeholders; addresses are in the comments. Status: matching/README.md.
#pragma once

struct ValuePair {
    long first;
    long second;
};

// A node's visibility bit, kept in the low bit of the byte at +58.
struct ShowNode {
    unsigned char pad[0x58];
    unsigned char shown : 1;  // +58 bit 0
    unsigned char rest : 7;
};

class BufferAllocator {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void v40();
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void free(void* buffer);                                        // +60
};

class Listener {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void v40();
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void released(void* object);                                    // +60
};

class OwnedObject {
public:
    virtual void v00();
    virtual void destroy();                                                 // +08
};

class Notifiable {
public:
    virtual void v00();
    virtual void notify();                                                  // +08
};

class DrawNode {
public:
    void draw(int mode);                                                    // 0x71001e34a0
};

class TextTable {
public:
    const char* find(int id, int variant);                                  // 0x7100218d18

    unsigned char body[0x10];
};
struct TextDatabase {
    unsigned char loaded;     // +00
    unsigned char pad1[0x47];
    TextTable table_at_48;    // +48
    TextTable table_at_58;    // +58: system texts
    TextTable table_at_68;    // +68
    TextTable table_at_78;    // +78: messages
};
// Reached through the GOT slot at 0x7100c233a0.
extern TextDatabase gTextDatabase;
extern const char kEmptyText[] __attribute__((visibility("hidden")));       // 0x7100740512

union ItemDefFields {
    short values[0x28];
    unsigned short unsigned_values[0x28];
    unsigned int unsigned_words[0x14];
};
class ItemDefTable {
public:
    ItemDefFields* find(int item) {
        return static_cast<unsigned int>(item) < 0x44c ? &defs[item] : nullptr;
    }

    ItemDefFields defs[0x44c];
};
// Reached through the GOT slot at 0x7100c216a0.
extern ItemDefTable* gItemDefs;

struct QueryHandle {
    void* target;
};
// Reached through the GOT slot at 0x7100c22f20.
extern void (*gQuery_c22f20)(void* target, int key, int* value);

struct BaseInfo {
    unsigned char pad[0x38];
    unsigned char* base;      // +38
};
struct BaseContext {
    unsigned char pad[0xc8];
    BaseInfo* info;           // +c8
};

// Reached through the GOT slot at 0x7100c22a40.
extern void* gSaveTarget_c22a40;
// Reached through the GOT slot at 0x7100c221d0.
extern unsigned int gStepLimit_c221d0;

unsigned char check_object_1f7da0(void* object);                            // 0x71001f7da0
void refresh_shown_1f7f44(void* object);                                    // 0x71001f7f44
unsigned char is_ready_1f7e3c(void* object);                                // 0x71001f7e3c
void* load_global_425dd0();                                                 // 0x7100425dd0
void* find_entry_426ab4(void* table, int id);                               // 0x7100426ab4
void save_block_1df8c0(void* target, void* data, int size, int flags);      // 0x71001df8c0
void show_message_217d9c(int id);                                           // 0x7100217d9c