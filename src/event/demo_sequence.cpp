// Matching candidate for the demo sequence clear at 0x71002170fc.
// Semantics: docs/demo-sequence.md.

struct DemoSequenceItem {
    unsigned char data[0x30];
};
static_assert(sizeof(DemoSequenceItem) == 0x30, "item size");

class DemoOwner {
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
    virtual void free(void* ptr); // +0x60
};

void release_demo_sequence_item(DemoSequenceItem* item);

struct DemoSequence {
    DemoOwner* owner;         // +00
    DemoSequenceItem* items;  // +08
    unsigned int count;       // +10

    void clear();
};

void DemoSequence::clear() {
    if (items) {
        if (count != 0) {
            release_demo_sequence_item(&items[0]);
            for (unsigned int i = 1; i < count; ++i)
                release_demo_sequence_item(&items[i]);
        }
        if (items)
            owner->free(items);
        items = nullptr;
        count = 0;
    }
}

