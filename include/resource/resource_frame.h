// Resource frame view (40 bytes). Semantics: docs/resource-frame.md.
// The bodies are not matched yet; units.json maps them to their original addresses.
#pragma once

class ResourceFrame {
public:
    ResourceFrame();                                  // 0x710025b394
    ~ResourceFrame();                                 // 0x710025b3ac
    void close();                                     // 0x710025b40c
    void bind(int mode, void* storage);               // 0x710025b47c
    unsigned int count() const;                       // 0x710025b6f8
    const void* lookup(unsigned int index) const;     // 0x710025b738

private:
    void* mStorage;           // +00
    unsigned int mLayout[2];  // +08
    unsigned int mIdentity;   // +10
    void* mOwner;             // +18
    bool mOwnsStorage;        // +20
};
static_assert(sizeof(ResourceFrame) == 0x28, "frame size");
