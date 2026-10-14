// Scale accumulation (0x71005d9d20): multiply the node scales up the parent chain, stopping at the
// first ActorScaleStop. Names are descriptive placeholders. Status: matching/README.md.

#include "misc/type_node.h"

struct Scale2 {
    float x;
    float y;
};

struct ScaleNode {
    virtual void slot0();
    virtual void slot1();
    virtual const TypeNode* type();

    unsigned char pad8[0x10];
    ScaleNode* parent;        // +18
    unsigned char pad20[0x28];
    float scale_x;            // +48
    float scale_y;            // +4c
};

// 0x71005d9d20
void collect_scale_5d9d20(void* owner, Scale2* scale, ScaleNode* node) {
    scale->x = 1.0f;
    scale->y = 1.0f;
    for (; node; node = node->parent) {
        const TypeNode* stop = TypeOf<ActorScaleStop>::get();
        for (const TypeNode* type = node->type(); type; type = type->parent) {
            if (type == stop)
                return;
        }
        scale->x = scale->x * node->scale_x;
        scale->y = scale->y * node->scale_y;
    }
}
