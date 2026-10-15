// PARKED (2 off each): the original keeps the key test as cmp w8, #0x10000; b.lo. The IR here has the same
// icmp ult 65536, but our DAG turns it into lsr #16; cbz (15 unmatched functions show the cmp form). The key parameter
// is 64-bit (mov x20, x1).
// A keyed lookup in a resource frame (fourth session, 2-copy family 23dd14): finds the entry of the key's low half,
// walks its item list for the item whose key has the same high half and hands the argument to it (the one call that
// differs: 0x71002431cc or 0x710024393c). KeyedFrame::apply<0> (0x710023dd14) and apply<1> (0x710023e0c0). Names are
// descriptive placeholders.

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
    for (FrameItem* item = node->first; item; item = item->next_2449a8(0)) {
        if ((item->key_244838() ^ static_cast<unsigned int>(key)) < 0x10000) {
            item->apply<Copy>(arg);
            return;
        }
    }
}

// 0x710023dd14
template void KeyedFrame::apply<0>(unsigned long, int);
// 0x710023e0c0
template void KeyedFrame::apply<1>(unsigned long, int);
