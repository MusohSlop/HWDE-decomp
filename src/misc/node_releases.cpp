// Effect-node releases found by tools/family_scan.py --immediates (the shape of release_child in
// event/adv_caption.cpp): each detaches its node from the layout root, releases it, returns it to
// the effect manager's list and forgets it. They differ only in where the node is kept; types and
// functions are named after their address. Status: matching/README.md.

#include "event/demo_effects.h"
#include "event/demo_light_system.h"
#include "event/layout_panes.h"

struct NodeOwner1ef138 {
    unsigned char pad[0x120];
    LightEffectNode* node;    // +120
};

// 0x71001ef138
void release_node_1ef138(NodeOwner1ef138* owner) {
    if (owner->node) {
        EffectManager* manager = gEffectManager;
        void* root = gResourceLoader->layout->root;
        owner->node->detach(root);
        owner->node->release();
        manager->nodes.remove(owner->node);
        owner->node = nullptr;
    }
}

struct NodeOwner1f21f8 {
    unsigned char pad[0x120];
    LightEffectNode* node;    // +120
};

// 0x71001f21f8
void release_node_1f21f8(NodeOwner1f21f8* owner) {
    if (owner->node) {
        EffectManager* manager = gEffectManager;
        void* root = gResourceLoader->layout->root;
        owner->node->detach(root);
        owner->node->release();
        manager->nodes.remove(owner->node);
        owner->node = nullptr;
    }
}

struct NodeOwner336da8 {
    LightEffectNode* node;    // +0
};

// 0x7100336da8
void release_node_336da8(NodeOwner336da8* owner) {
    if (owner->node) {
        EffectManager* manager = gEffectManager;
        void* root = gResourceLoader->layout->root;
        owner->node->detach(root);
        owner->node->release();
        manager->nodes.remove(owner->node);
        owner->node = nullptr;
    }
}

struct NodeOwner35ca18 {
    unsigned char pad[0x8];
    LightEffectNode* node;    // +8
};

// 0x710035ca18
void release_node_35ca18(NodeOwner35ca18* owner) {
    if (owner->node) {
        EffectManager* manager = gEffectManager;
        void* root = gResourceLoader->layout->root;
        owner->node->detach(root);
        owner->node->release();
        manager->nodes.remove(owner->node);
        owner->node = nullptr;
    }
}
