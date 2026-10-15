// A keyed lookup in a resource frame (fourth session, 2-copy family 23dd14): finds the entry of the key's low half,
// walks its item list for the item whose key has the same high half and hands the argument to it (the one call that
// differs: 0x71002431cc or 0x710024393c). KeyedFrame::apply<0> (0x710023dd14) and apply<1> (0x710023e0c0). Names are
// descriptive placeholders.
// The high-half test is the walk's exit condition (`while (item && (k ^ key) >= 0x10000)`), which keeps the original's
// `cmp w8, #0x10000; b.lo`; written as an `if` inside the loop body the same compare becomes `lsr #16; cbz` (found by an
// unattended variant search; `found`/`break` forms of the walk match too).

#include "resource/resource_frame.h"

class FrameItem {
public:
    unsigned int key_244838();                                              // 0x7100244838
    FrameItem* next_2449a8(int flags);                                      // 0x71002449a8
    void apply_2431cc(int arg);                                             // 0x71002431cc
    void apply_24393c(int arg);                                             // 0x710024393c

    template <int Copy> void apply(int arg) {
        if (Copy == 0)
            apply_2431cc(arg);
        else
            apply_24393c(arg);
    }
};

struct FrameNode {
    unsigned char pad0[0x28];
    FrameItem* first;         // +28
};

class KeyedFrame {
public:
    template <int Copy> void apply(unsigned long key, int arg);

    unsigned char pad0[0x10b8];
    ResourceFrame frame;      // +10b8
};

template <int Copy>
void KeyedFrame::apply(unsigned long key, int arg) {
    unsigned int index = key & 0xffff;
    if (frame.count() <= index) return;
    const FrameNode* node = static_cast<const FrameNode*>(frame.lookup(index));
    if (!node) return;
    FrameItem* item = node->first;
    while (item && (item->key_244838() ^ static_cast<unsigned int>(key)) >= 0x10000) item = item->next_2449a8(0);
    if (item) item->apply<Copy>(arg);
}

// 0x710023dd14
template void KeyedFrame::apply<0>(unsigned long, int);
// 0x710023e0c0
template void KeyedFrame::apply<1>(unsigned long, int);

extern KeyedFrame* gKeyedFrame;                                             // through the GOT slot 0x7100c21708

// The same walk on the global frame, returning the item (0x7100241dcc).
FrameItem* find_frame_item(unsigned long key) {
    unsigned int index = key & 0xffff;
    ResourceFrame& frame = gKeyedFrame->frame;
    if (frame.count() <= index) return 0;
    const FrameNode* node = static_cast<const FrameNode*>(frame.lookup(index));
    if (!node) return 0;
    FrameItem* item = node->first;
    while (item && (item->key_244838() ^ static_cast<unsigned int>(key)) >= 0x10000) item = item->next_2449a8(0);
    return item;
}
