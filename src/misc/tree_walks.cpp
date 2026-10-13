// Scene-tree walks found by tools/family_scan.py --immediates: each visits a node's children,
// testing leaves against the context's collision set (stopping the walk on the first hit) and
// collecting the branches the visitor accepts, then descends into those. They differ only in the
// visitor type (its tests and its hit flag); functions are named after their address.
// Status: matching/README.md.

struct alignas(8) TreeSpan {
    unsigned int count;
    unsigned int first;
};
struct TreeNode {
    unsigned char pad[0x20];
    TreeSpan span;            // +20
    unsigned char pad28[8];
};
struct WalkContext {
    unsigned char pad[0x64];
    unsigned char mode;       // +64
    void* set;                // +68
};
struct TreeWalker {
    WalkContext* context;
    unsigned char stopped;    // +08
};

struct Visitor4ea47c {
    unsigned char pad[0x50];
    unsigned char hit;        // +50
};
unsigned char accepts_branch_4e36f0(Visitor4ea47c* visitor, TreeNode* node);            // 0x71004e36f0
unsigned char hits_leaf_4e961c(void* set, Visitor4ea47c** visitor, TreeNode* node, unsigned char mode); // 0x71004e961c

static inline unsigned long leaf_result_4ea47c(TreeWalker* walker, TreeNode* node, Visitor4ea47c* visitor) {
    WalkContext* context = walker->context;
    Visitor4ea47c* target = visitor;
    if (!hits_leaf_4e961c(context->set, &target, node, context->mode))
        return 0;
    visitor->hit = 1;
    return 2;
}

// 0x71004ea47c
void walk_tree_4ea47c(TreeWalker* walker, TreeNode* node, Visitor4ea47c* visitor) {
    TreeSpan span = node->span;
    TreeNode* accepted[8] = {};
    TreeNode* child = node + span.first;
    for (unsigned long i = 0; i < span.count; ++i, ++child) {
        unsigned long result;
        if (child->span.count) {
            result = accepts_branch_4e36f0(visitor, child);
        } else {
            result = leaf_result_4ea47c(walker, child, visitor);
        }
        if (result == 1) {
            accepted[i] = child;
        } else if (result == 2) {
            walker->stopped = 1;
            return;
        }
    }
    for (unsigned long i = 0; i < span.count; ++i) {
        if (accepted[i]) {
            walk_tree_4ea47c(walker, accepted[i], visitor);
            if (walker->stopped)
                return;
        }
    }
}

struct Visitor4ea6e4 {
    unsigned char pad[0x20];
    unsigned char hit;        // +20
};
unsigned char accepts_branch_511610(Visitor4ea6e4* visitor, TreeNode* node);            // 0x7100511610
unsigned char hits_leaf_4ea810(void* set, Visitor4ea6e4** visitor, TreeNode* node, unsigned char mode); // 0x71004ea810

static inline unsigned long leaf_result_4ea6e4(TreeWalker* walker, TreeNode* node, Visitor4ea6e4* visitor) {
    WalkContext* context = walker->context;
    Visitor4ea6e4* target = visitor;
    if (!hits_leaf_4ea810(context->set, &target, node, context->mode))
        return 0;
    visitor->hit = 1;
    return 2;
}

// 0x71004ea6e4
void walk_tree_4ea6e4(TreeWalker* walker, TreeNode* node, Visitor4ea6e4* visitor) {
    TreeSpan span = node->span;
    TreeNode* accepted[8] = {};
    TreeNode* child = node + span.first;
    for (unsigned long i = 0; i < span.count; ++i, ++child) {
        unsigned long result;
        if (child->span.count) {
            result = accepts_branch_511610(visitor, child);
        } else {
            result = leaf_result_4ea6e4(walker, child, visitor);
        }
        if (result == 1) {
            accepted[i] = child;
        } else if (result == 2) {
            walker->stopped = 1;
            return;
        }
    }
    for (unsigned long i = 0; i < span.count; ++i) {
        if (accepted[i]) {
            walk_tree_4ea6e4(walker, accepted[i], visitor);
            if (walker->stopped)
                return;
        }
    }
}

struct Visitor4eb798 {
    unsigned char pad[0x30];
    unsigned char hit;        // +30
};
unsigned char accepts_branch_50f744(Visitor4eb798* visitor, TreeNode* node);            // 0x710050f744
unsigned char hits_leaf_4eb8c4(void* set, Visitor4eb798** visitor, TreeNode* node, unsigned char mode); // 0x71004eb8c4

static inline unsigned long leaf_result_4eb798(TreeWalker* walker, TreeNode* node, Visitor4eb798* visitor) {
    WalkContext* context = walker->context;
    Visitor4eb798* target = visitor;
    if (!hits_leaf_4eb8c4(context->set, &target, node, context->mode))
        return 0;
    visitor->hit = 1;
    return 2;
}

// 0x71004eb798
void walk_tree_4eb798(TreeWalker* walker, TreeNode* node, Visitor4eb798* visitor) {
    TreeSpan span = node->span;
    TreeNode* accepted[8] = {};
    TreeNode* child = node + span.first;
    for (unsigned long i = 0; i < span.count; ++i, ++child) {
        unsigned long result;
        if (child->span.count) {
            result = accepts_branch_50f744(visitor, child);
        } else {
            result = leaf_result_4eb798(walker, child, visitor);
        }
        if (result == 1) {
            accepted[i] = child;
        } else if (result == 2) {
            walker->stopped = 1;
            return;
        }
    }
    for (unsigned long i = 0; i < span.count; ++i) {
        if (accepted[i]) {
            walk_tree_4eb798(walker, accepted[i], visitor);
            if (walker->stopped)
                return;
        }
    }
}

struct Visitor4ec85c {
    unsigned char pad[0x30];
    unsigned char hit;        // +30
};
unsigned char accepts_branch_50ec98(Visitor4ec85c* visitor, TreeNode* node);            // 0x710050ec98
unsigned char hits_leaf_4ec988(void* set, Visitor4ec85c** visitor, TreeNode* node, unsigned char mode); // 0x71004ec988

static inline unsigned long leaf_result_4ec85c(TreeWalker* walker, TreeNode* node, Visitor4ec85c* visitor) {
    WalkContext* context = walker->context;
    Visitor4ec85c* target = visitor;
    if (!hits_leaf_4ec988(context->set, &target, node, context->mode))
        return 0;
    visitor->hit = 1;
    return 2;
}

// 0x71004ec85c
void walk_tree_4ec85c(TreeWalker* walker, TreeNode* node, Visitor4ec85c* visitor) {
    TreeSpan span = node->span;
    TreeNode* accepted[8] = {};
    TreeNode* child = node + span.first;
    for (unsigned long i = 0; i < span.count; ++i, ++child) {
        unsigned long result;
        if (child->span.count) {
            result = accepts_branch_50ec98(visitor, child);
        } else {
            result = leaf_result_4ec85c(walker, child, visitor);
        }
        if (result == 1) {
            accepted[i] = child;
        } else if (result == 2) {
            walker->stopped = 1;
            return;
        }
    }
    for (unsigned long i = 0; i < span.count; ++i) {
        if (accepted[i]) {
            walk_tree_4ec85c(walker, accepted[i], visitor);
            if (walker->stopped)
                return;
        }
    }
}

struct Visitor4ed920 {
    unsigned char pad[0x40];
    unsigned char hit;        // +40
};
unsigned char accepts_branch_513ec8(Visitor4ed920* visitor, TreeNode* node);            // 0x7100513ec8
unsigned char hits_leaf_4eda4c(void* set, Visitor4ed920** visitor, TreeNode* node, unsigned char mode); // 0x71004eda4c

static inline unsigned long leaf_result_4ed920(TreeWalker* walker, TreeNode* node, Visitor4ed920* visitor) {
    WalkContext* context = walker->context;
    Visitor4ed920* target = visitor;
    if (!hits_leaf_4eda4c(context->set, &target, node, context->mode))
        return 0;
    visitor->hit = 1;
    return 2;
}

// 0x71004ed920
void walk_tree_4ed920(TreeWalker* walker, TreeNode* node, Visitor4ed920* visitor) {
    TreeSpan span = node->span;
    TreeNode* accepted[8] = {};
    TreeNode* child = node + span.first;
    for (unsigned long i = 0; i < span.count; ++i, ++child) {
        unsigned long result;
        if (child->span.count) {
            result = accepts_branch_513ec8(visitor, child);
        } else {
            result = leaf_result_4ed920(walker, child, visitor);
        }
        if (result == 1) {
            accepted[i] = child;
        } else if (result == 2) {
            walker->stopped = 1;
            return;
        }
    }
    for (unsigned long i = 0; i < span.count; ++i) {
        if (accepted[i]) {
            walk_tree_4ed920(walker, accepted[i], visitor);
            if (walker->stopped)
                return;
        }
    }
}

struct Visitor4ee9d4 {
    unsigned char pad[0x70];
    unsigned char hit;        // +70
};
unsigned char accepts_branch_5025b4(Visitor4ee9d4* visitor, TreeNode* node);            // 0x71005025b4
unsigned char hits_leaf_4eeb00(void* set, Visitor4ee9d4** visitor, TreeNode* node, unsigned char mode); // 0x71004eeb00

static inline unsigned long leaf_result_4ee9d4(TreeWalker* walker, TreeNode* node, Visitor4ee9d4* visitor) {
    WalkContext* context = walker->context;
    Visitor4ee9d4* target = visitor;
    if (!hits_leaf_4eeb00(context->set, &target, node, context->mode))
        return 0;
    visitor->hit = 1;
    return 2;
}

// 0x71004ee9d4
void walk_tree_4ee9d4(TreeWalker* walker, TreeNode* node, Visitor4ee9d4* visitor) {
    TreeSpan span = node->span;
    TreeNode* accepted[8] = {};
    TreeNode* child = node + span.first;
    for (unsigned long i = 0; i < span.count; ++i, ++child) {
        unsigned long result;
        if (child->span.count) {
            result = accepts_branch_5025b4(visitor, child);
        } else {
            result = leaf_result_4ee9d4(walker, child, visitor);
        }
        if (result == 1) {
            accepted[i] = child;
        } else if (result == 2) {
            walker->stopped = 1;
            return;
        }
    }
    for (unsigned long i = 0; i < span.count; ++i) {
        if (accepted[i]) {
            walk_tree_4ee9d4(walker, accepted[i], visitor);
            if (walker->stopped)
                return;
        }
    }
}
