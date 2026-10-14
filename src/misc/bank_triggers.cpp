// Sound or effect triggers (0x710021c5d4-0x710021cf88): an id at or above 0x4000 goes to the global
// player first; a low byte inside the object's bank goes to the bank, through its short or long
// path depending on the slot's flag; other ids below 0x4000 go to the global player. Found by
// tools/family_scan.py --immediates. Names are descriptive placeholders. Status: matching/README.md.

struct BankSlot {
    unsigned char pad[4];
    unsigned short flag;      // +04
    unsigned char pad6[0x7a];
};

struct Bank {
    unsigned char pad[0x54];
    unsigned int count;       // +54
    unsigned char pad58[0x28];
    BankSlot slots[1];        // +80
};

struct TriggerOwner;
unsigned char play_594144(TriggerOwner* owner, unsigned int id, int kind, int mode, void* arg,
                          void* context);                                   // 0x7100594144
void bank_play_5a7d6c(Bank* bank, unsigned int slot, int kind, int mode, void* arg,
                      void* context);                                       // 0x71005a7d6c
void bank_play_short_5a81c4(Bank* bank, unsigned int slot, int kind, void* arg,
                            void* context);                                 // 0x71005a81c4

struct TriggerOwner {
    unsigned char pad[0x10];
    void* context;            // +10
    unsigned char pad18[0x18];
    Bank* bank;               // +30
};
struct Trigger21c5d4 : TriggerOwner {
    unsigned char pad38[0x12a4];
    unsigned int id;          // +12dc
};

// 0x710021c5d4
unsigned char trigger_21c5d4(Trigger21c5d4* owner, void* arg) {
    unsigned int id = owner->id;
    if (id >= 0x4000 && play_594144(owner, id, 4, 1, arg, nullptr))
        return 1;
    Bank* bank = owner->bank;
    if (bank) {
        unsigned int slot = id & 0xff;
        if (slot < bank->count) {
            void* context = owner->context;
            if (bank->slots[slot].flag) {
                bank_play_5a7d6c(bank, slot, 4, 1, arg, context);
                return 1;
            }
            bank_play_short_5a81c4(bank, slot, 4, arg, context);
            return 1;
        }
    }
    if ((id >> 14) == 0)
        return play_594144(owner, id, 4, 1, arg, nullptr);
    return 0;
}
struct Trigger21c6c0 : TriggerOwner {
    unsigned char pad38[0x12a4];
    unsigned int id;          // +12dc
};

// 0x710021c6c0
unsigned char trigger_21c6c0(Trigger21c6c0* owner, void* arg) {
    unsigned int id = owner->id;
    if (id >= 0x4000 && play_594144(owner, id, 4, 1, arg, nullptr))
        return 1;
    Bank* bank = owner->bank;
    if (bank) {
        unsigned int slot = id & 0xff;
        if (slot < bank->count) {
            void* context = owner->context;
            if (bank->slots[slot].flag) {
                bank_play_5a7d6c(bank, slot, 4, 1, arg, context);
                return 1;
            }
            bank_play_short_5a81c4(bank, slot, 4, arg, context);
            return 1;
        }
    }
    if ((id >> 14) == 0)
        return play_594144(owner, id, 4, 1, arg, nullptr);
    return 0;
}
struct Trigger21cf88 : TriggerOwner {
    unsigned char pad38[0x129c];
    unsigned int id;          // +12d4
};

// 0x710021cf88
unsigned char trigger_21cf88(Trigger21cf88* owner, void* arg) {
    unsigned int id = owner->id;
    if (id >= 0x4000 && play_594144(owner, id, 4, 1, arg, nullptr))
        return 1;
    Bank* bank = owner->bank;
    if (bank) {
        unsigned int slot = id & 0xff;
        if (slot < bank->count) {
            void* context = owner->context;
            if (bank->slots[slot].flag) {
                bank_play_5a7d6c(bank, slot, 4, 1, arg, context);
                return 1;
            }
            bank_play_short_5a81c4(bank, slot, 4, arg, context);
            return 1;
        }
    }
    if ((id >> 14) == 0)
        return play_594144(owner, id, 4, 1, arg, nullptr);
    return 0;
}
