// Effect manager types shared by the demo light units. Names are descriptive
// placeholders.
#pragma once

class LightResource;

class EffectBase {
public:
    static void* operator new(unsigned long size) noexcept;                 // 0x71005d4380
    EffectBase();                                                           // 0x71005d9690
    virtual ~EffectBase();

private:
    unsigned char data[0xd4];
};

class LightEffect : public EffectBase {
public:
    explicit LightEffect(int mode_) : mode(mode_) {}
    virtual void v10();

    int mode;                 // +dc
};

class EffectGroup {
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
    virtual EffectGroup* find(const char* name, int depth); // +60
    void add(EffectBase* effect);                                           // 0x71005da17c

    unsigned char pad8[0x28];
    float offset30;           // +30
    float offset34;           // +34
    unsigned char pad38[0x20];
    unsigned char flags58;    // +58: bit 0 visible, bit 4 moved
};

class LightEffectNode {
public:
    virtual void v00();
    virtual void release();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void v40();
    virtual void v48();
    virtual void v50();
    virtual void advance(float delta); // +58
    virtual void v60();
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void v80();
    virtual void v88();
    virtual void update(void* context, int mode); // +90
    void detach(void* root);                                                // 0x71005d4408
    void draw(int mode);                                                    // 0x71001e34a0

    unsigned char pad8[0x10];
    EffectGroup* group;       // +18
};

class EffectList {
public:
    void remove(LightEffectNode* node);                                     // 0x71005c3774
};

class EffectManager {
public:
    void create_node(LightEffectNode** out, int id, const char* layout);    // 0x71001e2360
    void attach(LightResource* resource, void* owner);                      // 0x71001e26dc
    void* current();                                                        // 0x71001e26ec
    void begin();                                                           // 0x71001e22e0
    void end();                                                             // 0x71001e22d8
    void attach_resource(LightResource* resource);                          // 0x71001e26e0
    void unregister(void* registry, int id);                                // 0x71001e2218

    unsigned char pad[0x68];
    EffectList nodes;         // +68
    unsigned char pad69[0x6f];
    EffectList children;      // +d8
    unsigned char padd9[0x6df];
    unsigned char registry[1]; // +7b8
};
// Reached through the GOT slot at 0x7100c22a00.
extern EffectManager* gEffectManager;

struct LayoutRoot {
    unsigned char pad[0x10];
    unsigned char root[1];    // +10
};
struct ResourceLoaderView {
    unsigned char pad[0x2af8];
    LayoutRoot* layout;       // +2af8
};
// Reached through the GOT slot at 0x7100c21db0.
extern ResourceLoaderView* gResourceLoader;
