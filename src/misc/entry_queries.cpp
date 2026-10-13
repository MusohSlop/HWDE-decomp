// Presence queries found by tools/family_scan.py --immediates: each asks the source object embedded
// in its owner (at +110 or +120) for one of three entries (virtual slots +20, +40, +68) and reports
// whether it has one. They differ only in the member offset and the slot; functions are named after
// their address. Status: matching/README.md.

class EntrySource {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void* first_entry();              // +20
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void* second_entry();             // +40
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void v60();
    virtual void* third_entry();              // +68
};

template <unsigned long Offset>
struct SourceOwner {
    EntrySource* source() { return &embedded; }

    unsigned char pad[Offset];
    EntrySource embedded;     // +Offset
};

// 0x7100023e9c
unsigned char has_entry_23e9c(SourceOwner<0x120>* owner) {
    return owner->source()->first_entry() != nullptr;
}

// 0x7100023f10
unsigned char has_entry_23f10(SourceOwner<0x120>* owner) {
    return owner->source()->second_entry() != nullptr;
}

// 0x7100023f84
unsigned char has_entry_23f84(SourceOwner<0x120>* owner) {
    return owner->source()->third_entry() != nullptr;
}

// 0x7100026e10
unsigned char has_entry_26e10(SourceOwner<0x110>* owner) {
    return owner->source()->first_entry() != nullptr;
}

// 0x7100026e84
unsigned char has_entry_26e84(SourceOwner<0x110>* owner) {
    return owner->source()->second_entry() != nullptr;
}

// 0x7100026ef8
unsigned char has_entry_26ef8(SourceOwner<0x110>* owner) {
    return owner->source()->third_entry() != nullptr;
}

// 0x7100028e50
unsigned char has_entry_28e50(SourceOwner<0x120>* owner) {
    return owner->source()->first_entry() != nullptr;
}

// 0x7100028e8c
unsigned char has_entry_28e8c(SourceOwner<0x120>* owner) {
    return owner->source()->second_entry() != nullptr;
}

// 0x7100028ec8
unsigned char has_entry_28ec8(SourceOwner<0x120>* owner) {
    return owner->source()->third_entry() != nullptr;
}

// 0x710002a790
unsigned char has_entry_2a790(SourceOwner<0x110>* owner) {
    return owner->source()->first_entry() != nullptr;
}

// 0x710002a7cc
unsigned char has_entry_2a7cc(SourceOwner<0x110>* owner) {
    return owner->source()->second_entry() != nullptr;
}

// 0x710002a808
unsigned char has_entry_2a808(SourceOwner<0x110>* owner) {
    return owner->source()->third_entry() != nullptr;
}

// 0x71000ca798
unsigned char has_entry_ca798(SourceOwner<0x110>* owner) {
    return owner->source()->first_entry() != nullptr;
}

// 0x71000ca7d4
unsigned char has_entry_ca7d4(SourceOwner<0x110>* owner) {
    return owner->source()->second_entry() != nullptr;
}

// 0x71000ca810
unsigned char has_entry_ca810(SourceOwner<0x110>* owner) {
    return owner->source()->third_entry() != nullptr;
}

// 0x71000ccc14
unsigned char has_entry_ccc14(SourceOwner<0x110>* owner) {
    return owner->source()->first_entry() != nullptr;
}

// 0x71000ccc88
unsigned char has_entry_ccc88(SourceOwner<0x110>* owner) {
    return owner->source()->second_entry() != nullptr;
}

// 0x71000cccfc
unsigned char has_entry_cccfc(SourceOwner<0x110>* owner) {
    return owner->source()->third_entry() != nullptr;
}
