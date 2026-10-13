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

// Skinned and plain models; vtables through the GOT slots at 0x7100c22108 and 0x7100c22110.
class SkinnedModel_72768 : public Model {
public:
    SkinnedModel_72768() { flags &= ~0x800; }
    void v00() override;

    SkinSet skins;            // +12a0
};
class PlainModel_72768 : public Model {
public:
    void v00() override;
};

void* create_model_72768(ResourceLoader* loader, ModelResource* resource, int extra_count,
                         void** extras, Heap* heap, unsigned char validate, void* user);

// 0x7100072768
void* create_model_72768(ResourceLoader* loader, ModelResource* resource, int extra_count,
                         void** extras, Heap* heap, unsigned char validate, void* user) {
    unsigned int nodes, skins;
    if (resource->query(&nodes, &skins)) {
        unsigned int base = nodes + 0x12a0;
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
        void* objects[4];
        Model* model = static_cast<Model*>(heap->allocate(size, AllocParams(6)));
        if (model) {
            void* skin = nullptr;
            unsigned int count = extra_count;
            void** list = extras;
            if (nodes) {
                SkinnedModel_72768* skinned = new (model) SkinnedModel_72768;
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
                new (model) PlainModel_72768;
            }
            unsigned char* p = reinterpret_cast<unsigned char*>(model);
            unsigned char* bone_table = p + body;
            unsigned char* name_table = bone_table + bones;
            unsigned char* material_table = name_table + bone_names;
            unsigned char* texture_table = material_table + materials;
            unsigned char* sampler_table = texture_table + textures;
            unsigned char* shape_table = sampler_table + samplers;
            if (!model->setup(loader, heap, resource, p + base, skin, count, list, bone_table,
                              name_table, material_table, texture_table, sampler_table,
                              shape_table, p + end, user)) {
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
