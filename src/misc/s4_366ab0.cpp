// A page menu's draw (fourth session, 2-copy family 366ab0): draws up to 11 pages, the selected one last.
// PageMenu::draw<0> (0x7100366ab0) and draw<1> (0x7100366b64).

#include "event/demo_effects.h"

class PageScroller {
public:
    void update_37d96c();                                                   // 0x710037d96c
};

struct PageSlot {
    unsigned char pad0[0x20];
    LightEffectNode* node;    // +20
    unsigned char pad28[0x2228];
};

class PageMenu {
public:
    template <int Copy> void draw();

    PageSlot pages[11];       // +00000
    unsigned char pad17970[0x120];
    PageScroller scroller;    // +17a90
    unsigned char pad17a91[0x2f];
    int selected;             // +17ac0
    int count;                // +17ac4
};

template <int Copy>
void PageMenu::draw() {
    scroller.update_37d96c();
    int n = count < 11 ? count : 11;
    for (int i = 0; i < n; i++) {
        if (i != selected) pages[i].node->draw(0);
    }
    pages[selected].node->draw(0);
}

// 0x7100366ab0
template void PageMenu::draw<0>();
// 0x7100366b64
template void PageMenu::draw<1>();
