// Layout panes shared by the Adventure Mode window units. Names are descriptive placeholders.
#pragma once

class PaneBase {
public:
    static void* operator new(unsigned long size) noexcept;                 // 0x71005d4380
    PaneBase();                                                             // 0x71005dc664
    virtual ~PaneBase();

    unsigned char pad8[0x53];
    unsigned char : 2;
    unsigned char align : 2;  // +5b bits 2-3
    unsigned char : 4;
    unsigned char pad5c[0x104];
};

// Text pane (0x180 bytes); vtable reached through the GOT slot at 0x7100c22f68.
class PanelPane : public PaneBase {
public:
    PanelPane() : value160(nullptr), value168(nullptr), value170(nullptr) {}
    ~PanelPane();

    void* value160;           // +160
    void* value168;           // +168
    void* value170;           // +170
    unsigned char pad178[8];
};
static_assert(sizeof(PanelPane) == 0x180, "pane size");
