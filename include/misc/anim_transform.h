// The animation-transform creation that layout code inlines (an nn::ui2d-style CreateAnimTransformBasic), shared by
// the hand-matching sessions. Names are descriptive placeholders.
//
// The block, as the original compiles it: the resource's animation block is tested before anything is allocated; the
// object comes from a nothrow class operator new; the base constructor is out of line and the derived one inline (its
// vtable through the GOT slot at 0x7100c2a698, two fields cleared); the new object is pushed onto the layout's
// animation list (an nn::util-style LinkPrev); then the virtual SetResource (+40) is called with the layout's
// resource accessor, which is loaded after the link.
//
// Use: create_anim_transform(layout, root, layout->find_animation(name)), where LAYOUT has an AnimLink `anims`
// (+8 in the layout node) and a `void* accessor` (+40), and ROOT is the device or root pointer passed through to
// SetResource. Arguments are evaluated left to right, so a root computed in the call comes before the lookup.
// main's src/event/demo_panel_system.cpp has the same shape as its static bind_animation (AnimSource, AnimBinding).
//
// Symbols (data/units.json): _ZN10AnimSourceC1EPv 0x71005cfac8, _ZN13AnimTransformC2Ev 0x71005d026c,
// _ZN13AnimTransformnwEm 0x71005d4380, got:_ZTV18AnimTransformBasic 0x7100c2a698.
#pragma once

// Intrusive list link: prev at +0, next at +8.
struct AnimLink {
    AnimLink* prev;
    AnimLink* next;

    // Splices the ring that starts at NODE in front of this link (the back of the list whose head this is).
    void link_prev(AnimLink* node) {
        AnimLink* last = node->prev;
        node->prev = prev;
        last->next = this;
        prev->next = node;
        prev = last;
    }
};

// The resource of one animation, looked up by name (0x20 bytes; its block at +8).
struct AnimSource {
    void* data;               // +00
    void* block;              // +08
    unsigned char pad10[0x10];

    explicit AnimSource(void* resource);                                    // 0x71005cfac8
};

// Base animation transform (0x48 bytes).
class AnimTransform {
public:
    static void* operator new(unsigned long size) noexcept;                 // 0x71005d4380
    AnimTransform();                                                        // 0x71005d026c
    virtual ~AnimTransform();
    virtual void v10();
    virtual void v18();
    virtual void set_enable(bool enable); // +20
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void set_resource(void* root, void* accessor, void* block); // +40

    AnimLink link;            // +08
    unsigned char pad18[0x30];
};

// The transform the layouts create (0x58 bytes; vtable through the GOT slot at 0x7100c2a698).
class AnimTransformBasic : public AnimTransform {
public:
    AnimTransformBasic() : bindings(nullptr), binding_count(0) {}
    virtual void v48();       // declared, not defined: the vtable stays in the module that defines it

    void* bindings;           // +48
    int binding_count;        // +50
};

template <class Layout>
inline AnimTransformBasic* create_anim_transform(Layout* layout, void* root, void* resource) {
    AnimSource source(resource);
    void* block = source.block;
    if (block == nullptr)
        return nullptr;
    AnimTransformBasic* anim = new AnimTransformBasic;
    if (anim != nullptr) {
        layout->anims.link_prev(&anim->link);
        anim->set_resource(root, layout->accessor, block);
    }
    return anim;
}
