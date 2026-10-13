// Effect manager types shared by the demo light units. Names are descriptive
// placeholders.
#pragma once

class LightResource;
class LayoutAnimation;
class PaneBase;

// Intrusive ring link (prev at +0, next at +8).
struct ListLink {
    ListLink* prev;
    ListLink* next;

    // Splices the ring that starts at node in front of this link.
    void link_before(ListLink* node) {
        ListLink* last = node->prev;
        node->prev = prev;
        last->next = this;
        prev->next = node;
        prev = last;
    }
};

// Layout animation (frame state at +20, playback speed at +3c).
class LayoutAnimation {
public:
    static void* operator new(unsigned long size) noexcept;                 // 0x71005d4380
    LayoutAnimation();                                                      // 0x71005d026c
    virtual ~LayoutAnimation();
    virtual void v10();
    virtual void v18();
    virtual void set_active(bool active); // +20
    virtual void reset(); // +28
    virtual void v30();
    virtual void v38();
    virtual void bind(void* root, void* resources, void* block); // +40
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void v60();
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void v80();
    virtual void v88();
    virtual void v90();
    virtual void v98();
    virtual void va0();
    virtual void va8();
    virtual void set_rate(float rate); // +b0
    virtual void vb8();
    virtual void set_frame(float frame); // +c0
    virtual void vc8();
    virtual void rewind(); // +d0
    unsigned short frame_count();                                           // 0x71005ce178

    ListLink link;            // +08: binding ring of the owning node
    unsigned char pad18[8];
    volatile float frame;     // +20: volatile, so each check reloads it as in the original
    unsigned char pad24[0x18];
    float speed;              // +3c
    unsigned char pad40[4];
    unsigned char state44;    // +44: bit 1 finished
    unsigned char pad45[3];
};

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
    virtual void v68();
    virtual void v70();
    virtual void v78();
    virtual void bind_animation(void* binding, bool a, bool b); // +80
    void add(EffectBase* effect);                                           // 0x71005da17c
    void add(EffectGroup* child);                                           // 0x71005da17c
    void add(PaneBase* pane);                                               // 0x71005da17c
    EffectGroup* duplicate(void* root);                                     // 0x71005dec80

    unsigned char pad8[0x28];
    float offset30;           // +30
    float offset34;           // +34
    float offset38;           // +38
    unsigned char pad3c[0xc];
    float scale48;            // +48
    float scale4c;            // +4c
    float size50;             // +50
    float size54;             // +54
    unsigned char flags58;    // +58: bit 0 visible, bit 4 moved
    unsigned char alpha59;    // +59
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
    LayoutAnimation* create_animation(const char* name, bool loop);    // 0x71001e3820
    LayoutAnimation* create_window_animation(const char* name, bool loop); // 0x71001e37c8
    void* find_animation(const char* name);                                // 0x71005d4fec

    ListLink bindings;        // +08
    EffectGroup* group;       // +18
    unsigned char pad20[0x20];
    void* resources;          // +40
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
    void flush();                                                           // 0x71001e26e4
    void sync();                                                            // 0x71001e26e8
    void finish(int id);                                                    // 0x71001e22e4

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
