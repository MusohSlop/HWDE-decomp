// 0x710021d738 (948 B): a model builder. The family (parked at 14 abstract diffs, all register allocation): 21d738,
// 21ddf8, 21f9f8, 2200b8, 450710 (only the object size and the vtables differ), 73070, 73e50, 74520, 4100e8, 4107c8,
// 410ea8, 73770, 23efbc, 21d074, 3e5954, 21e4b8, 21f318, 450dd4, 44e84c, 44e15c, 44da50, 44ffb8, 21eb98, and the main
// session's 72768 (misc/model_builders.cpp, now the third session's).
// Written like 72768 with TrackedModel (0x710058fe30) as the base and 0x12f0 as the object size, plus the fifth
// session's arrangement: the node pointer (p + base) right after the name table and the weight pointer (p + end) as
// its own statement just before the shape table, so base keeps a callee-saved register and materials, textures and
// samplers are spilled as in the original (18 to 14).
// Left: (1) the original keeps the loader (x0) and user (x6) arguments in x20/x21 across query and spills both with
// one stp at the top of the success block; ours spills loader, user and extras at their definitions (greedy's region
// split takes only the compact region around setup). (2) bones and end swap w23/w24. (3) the reloads around setup
// follow from (1).
// Tried without effect: 32 statement-order/type variants (before s5's arrangement); after it, the query outputs'
// order, an early return, a named AllocParams (47 off), late locals for loader/user, a ternary for size, the list and
// count locals declared before the query or in the plain branch, the skin local at the top, the copy loop through a
// pointer (73 off). irsearch: --groups --loads-free and plain mode on the size block (18 to 16 before the
// arrangement); s5's plain runs over every block of 5+ instructions moved nothing.
// Symbols for try.py: --map got:_ZTV19SkinnedModel_21d738=0x7100c233e0 --map got:_ZTV17PlainModel_21d738=0x7100c233e8
//
// The diff (ours -, original +; branch-only lines dropped):
//    --- replace ours[10:11] orig[10:11]
//       28 - str x0, [sp, #0x70]
//       28 + mov x20, x0
//    --- insert ours[13:13] orig[13:14]
//       34 + str x3, [sp, #0x70]
//    --- replace ours[14:15] orig[15:16]
//       38 - stp x3, x6, [sp, #0x60]
//       3c + mov x21, x6
//    --- replace ours[19:20] orig[20:21]
//    --- insert ours[22:22] orig[23:24]
//       5c + stp x21, x20, [sp, #0x60]
//    --- replace ours[25:26] orig[27:28]
//    --- replace ours[32:33] orig[34:35]
//       80 - lsl w24, w9, #3
//       88 + lsl w23, w9, #3
//    --- replace ours[39:40] orig[41:42]
//       9c - add w9, w24, w25
//       a4 + add w9, w23, w25
//    --- replace ours[55:58] orig[57:60]
//       dc - add w23, w9, w27
//       e0 - add w9, w10, w23
//       e4 - csel w9, w23, w9, eq
//       e4 + add w24, w9, w27
//       e8 + add w9, w10, w24
//       ec + csel w9, w24, w9, eq
//    --- replace ours[59:60] orig[61:63]
//       ec - ldr x8, [x13, #0x38]
//       f4 + csel w8, w24, w9, eq
//       f8 + ldr x9, [x13, #0x38]
//    --- replace ours[61:62] orig[64:66]
//       f4 - csel w1, w23, w9, eq
//      100 + strh w10, [sp, #0x78]
//      104 + mov w1, w8
//    --- delete ours[64:65] orig[68:68]
//      100 - strh w10, [sp, #0x78]
//    --- replace ours[67:68] orig[70:71]
//      10c - blr x8
//      118 + blr x9
//    --- replace ours[69:70] orig[72:73]
//    --- replace ours[74:75] orig[77:78]
//    --- replace ours[91:92] orig[94:95]
//    --- replace ours[102:103] orig[105:106]
//    --- replace ours[107:108] orig[110:111]
//    --- replace ours[115:116] orig[118:119]
//    --- replace ours[135:138] orig[138:140]
//      21c - ldp x7, x15, [sp, #0x60]
//      220 - ldr x1, [sp, #0x70]
//      224 - ldp w12, w14, [sp, #0x58]
//      228 + ldr x7, [sp, #0x70]
//      22c + ldp w12, w13, [sp, #0x58]
//    --- replace ours[140:143] orig[142:145]
//      234 - ldr x2, [sp, #0x48]
//      23c + ldr x1, [sp, #0x48]
//    --- replace ours[148:151] orig[150:152]
//      250 - ldr x17, [sp, #0x60]
//      254 - ldr x1, [sp, #0x70]
//      258 + ldr x17, [sp, #0x70]
//    --- replace ours[152:156] orig[153:155]
//      260 - ldr x1, [sp, #0x70]
//      268 - ldr x17, [sp, #0x60]
//      26c - ldr x1, [sp, #0x70]
//      268 + ldr x17, [sp, #0x70]
//    --- replace ours[168:169] orig[167:168]
//    --- replace ours[170:171] orig[169:170]
//    --- replace ours[175:177] orig[174:175]
//      2bc - ldr x15, [sp, #0x68]
//      2c0 - ldp w12, w14, [sp, #0x58]
//      2b8 + ldp w12, w13, [sp, #0x58]
//    --- replace ours[178:179] orig[176:177]
//      2c8 - mov x5, x2
//      2c0 + mov x5, x1
//    --- replace ours[180:181] orig[178:179]
//      2d0 - add x9, x8, w24, uxtw
//      2c8 + add x9, x8, w23, uxtw
//    --- delete ours[182:183] orig[180:180]
//      2d8 - stp x8, x9, [sp]
//    --- insert ours[185:185] orig[182:186]
//      2d8 + add x13, x12, w13, uxtw
//      2dc + add x14, x20, w24, uxtw
//      2e0 + stp x13, x14, [sp, #0x28]
//      2e4 + ldp x14, x1, [sp, #0x60]
//    --- delete ours[186:187] orig[187:187]
//      2e8 - add x13, x20, w23, uxtw
//    --- delete ours[189:190] orig[189:189]
//      2f4 - add x14, x12, w14, uxtw
//    --- replace ours[191:194] orig[190:194]
//      2fc - stp x13, x15, [sp, #0x30]
//      300 - stp x10, x11, [sp, #0x10]
//      304 - stp x12, x14, [sp, #0x20]
//      2f8 + stp x11, x12, [sp, #0x18]
//      2fc + str x14, [sp, #0x38]
//      300 + stp x9, x10, [sp, #8]
//      304 + str x8, [sp]
//    --- replace ours[214:215] orig[214:215]
//    --- replace ours[218:219] orig[218:219]
//    --- replace ours[231:232] orig[231:232]
//    --- replace ours[236:237] orig[236:237]

// Model builders found by tools/family_scan.py (called by misc/object_loaders.cpp): each
// sizes a model from its resource's tables, allocates it on the given heap, constructs it
// as the skinned or the plain variant, gathers the skin's extra objects, lays out the
// tables after the object and runs the model's setup. Status: matching/README.md.

inline void* operator new(unsigned long, void* where) noexcept { return where; }

struct AllocParams {
    explicit AllocParams(short alignment) : alignment(alignment), flags(0), tag(0) {}

    short alignment;          // +0
    short flags;              // +2
    long tag;                 // +8
};

class Heap {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void* allocate(unsigned int size, const AllocParams& params);   // +38
};

class ResourceLoader;

class ModelResource {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void destroy();   // +18

    unsigned char query(unsigned int* nodes, unsigned int* skins);          // 0x71005927d4

    int refs;                 // +08
    unsigned char pad0c[0x84];
    unsigned int weights;     // +90
    unsigned int weight_count; // +94
    unsigned int bones;       // +98
    unsigned int bone_names;  // +9c
    unsigned char pada0[0x54];
    unsigned int materials;   // +f4
    unsigned int textures;    // +f8
    unsigned int samplers;    // +fc
    unsigned char pad100[0x10];
    unsigned int shapes;      // +110
};

class SkinSet {
public:
    unsigned char init(ModelResource* resource, int flags, void* owner);    // 0x7100595a90
    void* root(void* owner);                                                // 0x7100595c4c
    unsigned int collect(void** objects, Heap* heap);                       // 0x7100595c90
};

class Model {
public:
    Model();                                                                // 0x71005928c0
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void destroy();   // +18

    unsigned char setup(ResourceLoader* loader, Heap* heap, ModelResource* resource, void* nodes,
                        void* skin, unsigned int count, void** objects, void* bones,
                        void* bone_names, void* materials, void* textures, void* samplers,
                        void* shapes, void* weights, void* user);           // 0x710059780c
    unsigned char validate();                                               // 0x7100597e90

    int refs;                 // +08
    unsigned char pad0c[0xc];
    Heap* heap;               // +18
    unsigned char pad20[0x1278];
    unsigned short flags;     // +1298
    unsigned char pad129a[6];
};

template <class T> static inline void drop(T* object) {
    if (!--object->refs)
        object->destroy();
}

class TrackedModel : public Model {
public:
    TrackedModel();                                                         // 0x710058fe30
    unsigned char pad12a0[0x50];
};

class SkinnedModel_21d738 : public TrackedModel {
public:
    SkinnedModel_21d738() { flags &= ~0x800; }
    void v00() override;

    SkinSet skins;            // +12f0
};
class PlainModel_21d738 : public TrackedModel {
public:
    void v00() override;
};

void* create_model_21d738(ResourceLoader* loader, ModelResource* resource, int extra_count,
                         void** extras, Heap* heap, unsigned char validate, void* user);

// 0x7100072768
void* create_model_21d738(ResourceLoader* loader, ModelResource* resource, int extra_count,
                         void** extras, Heap* heap, unsigned char validate, void* user) {
    unsigned int nodes, skins;
    if (resource->query(&nodes, &skins)) {
        unsigned int base = nodes + 0x12f0;
        unsigned int body = base;
        if (skins)
            body = base + (skins << 7 | 0x70);
        unsigned int bones = resource->bones * 8;
        unsigned int bone_names = resource->bone_names * 8;
        unsigned int materials = resource->materials * 8;
        unsigned int textures = resource->textures * 8;
        unsigned int samplers = resource->samplers * 8;
        unsigned int tables = (bones + bone_names + materials + textures + samplers +
                               resource->shapes * 8 + 15) & ~15u;
        unsigned int end = tables + body;
        unsigned int size = end;
        if (resource->weights && resource->weight_count)
            size = end + ((resource->weight_count * 2 + 15) & ~15u);
        Model* model = static_cast<Model*>(heap->allocate(size, AllocParams(6)));
        if (model) {
            // Declared after the allocation so it can share the parameters' stack slot.
            void* objects[4];
            void* skin = nullptr;
            unsigned int count = extra_count;
            void** list = extras;
            if (nodes) {
                SkinnedModel_21d738* skinned = new (model) SkinnedModel_21d738;
                unsigned int found;
                if (!skinned->skins.init(resource, 0, nullptr) ||
                    (skin = skinned->skins.root(nullptr),
                     found = skinned->skins.collect(objects, heap),
                     count = found + extra_count, count > 4)) {
                    model->heap = heap;
                    drop(model);
                    drop(resource);
                    return nullptr;
                }
                for (unsigned int i = 0; i < static_cast<unsigned int>(extra_count); ++i)
                    objects[found + i] = extras[i];
                list = objects;
            } else {
                new (model) PlainModel_21d738;
            }
            unsigned char* p = reinterpret_cast<unsigned char*>(model);
            unsigned char* bone_table = p + body;
            unsigned char* name_table = bone_table + bones;
            unsigned char* node_table = p + base;
            unsigned char* material_table = name_table + bone_names;
            unsigned char* texture_table = material_table + materials;
            unsigned char* sampler_table = texture_table + textures;
            unsigned char* weight_table = p + end;
            unsigned char* shape_table = sampler_table + samplers;
            if (!model->setup(loader, heap, resource, node_table, skin, count, list, bone_table,
                              name_table, material_table, texture_table, sampler_table,
                              shape_table, weight_table, user)) {
                drop(model);
                model = nullptr;
            } else if (validate && !model->validate()) {
                drop(resource);
                drop(model);
                return nullptr;
            }
            drop(resource);
            return model;
        }
    }
    drop(resource);
    return nullptr;
}