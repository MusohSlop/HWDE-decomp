// Reference-counted slot teardown found by tools/family_scan.py --immediates (the shape of
// BoardOverride::reset in event/board_override.cpp, with the slots released from the last one
// down). Status: matching/README.md.

struct RefObject {
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void destroy();   // +18

    int refs;                 // +08
};

static inline void release(RefObject** slot) {
    if (RefObject* object = *slot) {
        if (!--object->refs)
            object->destroy();
        *slot = nullptr;
    }
}

struct RefSlots_5cdc28 {
    void reset();

    unsigned char pad[0x98];
    RefObject* objects[5];    // +98
};

// 0x71005cdc28
void RefSlots_5cdc28::reset() {
    release(&objects[4]);
    release(&objects[3]);
    release(&objects[2]);
    release(&objects[1]);
    release(&objects[0]);
}