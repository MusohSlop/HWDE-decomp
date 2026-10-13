// Static object built on first use, found by tools/family_scan.py (one of 13 identical-shape
// functions; see misc/static_families.cpp). Each lives in its own unit, as in the original:
// with several in one unit, LLVM's global merge pass would put their statics into one block.
// Names are placeholders after the function address. Status: matching/README.md.

// Reached through the GOT slot at 0x7100c2d8f0.
extern unsigned char gGlobal_c2d8f0[];

class StaticBase_595930 {
public:
    explicit StaticBase_595930(void* source);                  // 0x7100595930
    virtual ~StaticBase_595930();
    unsigned char pad[8];
};

// 0x71005afb1c
class Static_5afb1c : public StaticBase_595930 {
public:
    explicit Static_5afb1c(void* source) : StaticBase_595930(source) {}
    ~Static_5afb1c() override;
};

void build_static_5afb1c() {
    static Static_5afb1c instance(gGlobal_c2d8f0);
}
