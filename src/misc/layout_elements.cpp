// Layout element constructors and small light/scene helpers picked by tools/rank_targets.py.
// They come from a few game source files; each definition names the address region of the
// original file it likely belongs to, for a later split.
// Names are descriptive placeholders. Status: matching/README.md.

// 0x71001ef52c; original file: layout elements, 0x71001ef52c-0x71001f1e0c
class LayoutSprite {
public:
    LayoutSprite();
    virtual void v00();

    int flags;                // +08
    long value10;             // +10
    long value18;             // +18
    float scale_x;            // +20
    float scale_y;            // +24
    int index;                // +28
    int value2c;              // +2c
    long value30;             // +30
    long value38;             // +38
    long value40;             // +40
};
static_assert(sizeof(LayoutSprite) == 0x48, "layout sprite size");

LayoutSprite::LayoutSprite()
    : flags(static_cast<int>(0xa0300000)), value10(0), value18(0), scale_x(1.0f), scale_y(1.0f),
      index(-1), value2c(0), value30(0), value38(0), value40(0) {}

// 0x71001f1cd8; original file: layout elements, 0x71001ef52c-0x71001f1e0c
class LayoutRect {
public:
    LayoutRect();
    virtual void v00();

    int flags;                // +08
    unsigned char padc[4];
    long value10;             // +10
    int value18;              // +18
    int value1c;              // +1c
    unsigned char value20;    // +20
    unsigned char pad21[7];
};
static_assert(sizeof(LayoutRect) == 0x28, "layout rect size");

LayoutRect::LayoutRect()
    : flags(static_cast<int>(0xa0300007)), value10(0), value18(0xf), value1c(0), value20(0) {}

// 0x71001f1e0c; original file: layout elements, 0x71001ef52c-0x71001f1e0c
class LayoutBox {
public:
    LayoutBox();
    virtual void v00();

    int flags;                // +08
    int valuec;               // +0c
};
static_assert(sizeof(LayoutBox) == 0x10, "layout box size");

LayoutBox::LayoutBox() : flags(static_cast<int>(0xa0300008)), valuec(1) {}

// 0x71001f4e70; original file: light lists, 0x71001f4e70-0x71001f5670
int make_light_list(unsigned int count) {
    if (count > 0x63)
        return -1;
    int id = count + 0x2936;
    return id > 0x294c ? -1 : id;
}

class ChunkHolder {
public:
    ~ChunkHolder();                                                         // 0x7100218ac0
    unsigned char pad[0x10];
};

// 0x71001f560c; original file: light lists, 0x71001f4e70-0x71001f5670
// Base of LightScene (whose own vtable is at GOT 0x7100c2a638).
class LightSceneBase {
public:
    virtual ~LightSceneBase();

    unsigned char pad8[0x10];
    ChunkHolder chunk;        // +18
};

LightSceneBase::~LightSceneBase() {}

// 0x71001f6b40; original file: light interpolation, 0x71001f6b40-0x71001f6b60
float lerp_float(float from, float to, float t) {
    return (to - from) * t + from;
}

// 0x71001f6b50; original file: light interpolation, 0x71001f6b40-0x71001f6b60
int lerp_int(int from, int to, int numerator, int denominator) {
    return (to - from) * numerator / denominator + from;
}

// 0x71001fb23c; original file: stage lights, 0x71001fb214-0x71001fb808
class StageLights {
public:
    int lookup(int value);

    unsigned char pad[0xe8];
    short ids[0x64];          // +e8
};

int StageLights::lookup(int value) {
    if (static_cast<unsigned int>(value) <= 0x63) {
        int id = ids[value];
        return static_cast<unsigned short>(id) < 1000 ? id : -1;
    }
    return -1;
}

class DefaultHeap {
public:
    void release(void* ptr, int a, int b);                                   // 0x710045c2f4
};
DefaultHeap* get_default_heap();                                            // 0x710045c96c

// 0x71001f56fc; original file: light lists, 0x71001f4e70-0x71001f5670
class LightScene : public LightSceneBase {
public:
    void finalize();
};

void LightScene::finalize() {
    if (void* buffer = *reinterpret_cast<void**>(pad8 + 8)) {
        get_default_heap()->release(buffer, 1, 0);
        *reinterpret_cast<void**>(pad8 + 8) = nullptr;
    }
}

struct RefObject {
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void destroy();   // +18

    int refs;                 // +08
};

// 0x71001f7960; original file: light objects, 0x71001f73e4-0x71001f7960
void release_light(void** slot) {
    if (RefObject* object = static_cast<RefObject*>(*slot)) {
        if (!--object->refs)
            object->destroy();
        *slot = nullptr;
    }
}

// 0x71001f73e4; original file: light objects, 0x71001f73e4-0x71001f7960
void show_sources(LayoutSprite* sources, unsigned int count) {
    for (; count; --count, ++sources)
        sources->flags &= ~0x80;
}
