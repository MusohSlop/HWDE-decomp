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
    unsigned long index;      // +28 (low half -1, high half 0)
    long value30;             // +30
    long value38;             // +38
    long value40;             // +40
};
static_assert(sizeof(LayoutSprite) == 0x48, "layout sprite size");

LayoutSprite::LayoutSprite()
    : flags(static_cast<int>(0xa0300000)), value10(0), value18(0), scale_x(1.0f), scale_y(1.0f),
      index(0xffffffffUL), value30(0), value38(0), value40(0) {}

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
    void clear();                                                           // 0x7100218ad0
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
class LightAllocator {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void v28();
    virtual void v30();
    virtual void v38();
    virtual void v40();
    virtual void v48();
    virtual void v50();
    virtual void v58();
    virtual void free(void* ptr);                                           // +60
};
class LightScene : public LightSceneBase {
public:
    void finalize();
    void init(LightAllocator* allocator);
    void unload();

    unsigned char pad28[0x58c0];
    long value58e8;           // +58e8
    long value58f0;           // +58f0
    long value58f8;           // +58f8
    int value5900;            // +5900
    int value5904;            // +5904
    int value5908;            // +5908
    int value590c;            // +590c
    int value5910;            // +5910
    unsigned char value5914;  // +5914
    unsigned char pad5915[3];
    int value5918;            // +5918
    unsigned char value591c;  // +591c
    unsigned char pad591d[0x28b];
    unsigned char value5ba8;  // +5ba8
    unsigned char pad5ba9[3];
    int value5bac;            // +5bac
    float value5bb0;          // +5bb0
    float value5bb4;          // +5bb4
    float value5bb8;          // +5bb8
    unsigned char value5bbc;  // +5bbc
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

// 0x71001f5670; original file: light lists, 0x71001f4e70-0x71001f5670
void LightScene::init(LightAllocator* allocator) {
    *reinterpret_cast<LightAllocator**>(pad8) = allocator;
    *reinterpret_cast<void**>(pad8 + 8) = nullptr;
    value5900 = 0;
    value58f8 = 0;
    value58f0 = 0;
    value58e8 = 0;
    value5904 = -1;
    value5908 = -1;
    value590c = 0;
    value5910 = 0;
    value5914 = 1;
    value5918 = 0;
    value591c = 1;
    value5ba8 = 1;
    value5bac = 0;
    value5bb0 = 0.0f;
    value5bb4 = 32.0f;
    value5bb8 = 32.0f;
    if (allocator)
        value5bbc = 0;
}

// 0x71001f58e4; original file: light lists, 0x71001f4e70-0x71001f5948
void LightScene::unload() {
    chunk.clear();
    if (void* buffer = *reinterpret_cast<void**>(pad8 + 8)) {
        if (value5bbc)
            get_default_heap()->release(buffer, 1, 0);
        else
            (*reinterpret_cast<LightAllocator**>(pad8))->free(buffer);
        *reinterpret_cast<void**>(pad8 + 8) = nullptr;
    }
}

// 0x71001f4ee0; original file: light lists, 0x71001f4e70-0x71001f5670
int make_light_object(int id) {
    if (static_cast<unsigned int>(id) <= 999) {
        if (id <= 0x10)
            return id + 0x2f30;
        switch (id) {
        case 0x14e:
            return 0x2f41;
        case 0x153:
            return 0x2f42;
        case 0x154:
            return 0x2f43;
        }
        if (static_cast<unsigned int>(id - 0x165) <= 4)
            return id + 0x2ddf;
        switch (id) {
        case 0x197:
            return 0x4651;
        case 0x198:
            return 0x4655;
        case 0x199:
            return 0x4653;
        case 0x19a:
            return 0x4652;
        case 0x19b:
            return 0x4654;
        }
        return 0x2f30;
    }
    return -1;
}
class LayoutRoot;
// 0x71001e26ec; original file: effect manager, 0x71001e22e4-0x71001e26ec
class EffectManager {
public:
    void* current();

    unsigned char pad[0x1290];
    unsigned char* layout;    // +1290
};

void* EffectManager::current() {
    return layout + 0x680;
}

class Fader;
// Reached through the GOT slot at 0x7100c23018.
extern Fader* gScreenFader;

// 0x71001e50b0; original file: screen fader, 0x71001e50b0-0x71001e526c
Fader* screen_fader() {
    return gScreenFader;
}

// 0x71001e526c; original file: screen fader, 0x71001e50b0-0x71001e526c
class Fader {
public:
    void fade(float seconds, int color, bool out);

    unsigned char pad[0x28];
    int mask28;               // +028
    unsigned char pad2c[0x8c];
    int maskb8;               // +0b8
    unsigned char padbc[0x13c];
    int color;                // +1f8
    unsigned int frames;      // +1fc
    unsigned int remaining;   // +200
    unsigned char active;     // +204
    unsigned char pad205[5];
    unsigned char fading_in;  // +20a
    unsigned char pad20b;
    int value20c;             // +20c
};

void Fader::fade(float seconds, int color, bool out) {
    int mask = out ? 0 : -1;
    fading_in = !out;
    unsigned int count = seconds * 60.0f;
    mask28 = mask;
    maskb8 = mask;
    value20c = 0;
    this->color = color;
    active = 1;
    frames = count;
    remaining = count;
    if (!count) {
        frames = 0;
        remaining = 1;
        if (!color)
            active = 0;
    }
}

class RenderTarget {
public:
    void end_batch();                                                       // 0x710052ed78
};
// Reached through the GOT slot at 0x7100c21db0.
extern RenderTarget* gRenderTarget;

// 0x71001e4560; original file: sprite batch, 0x71001e4500-0x71001e4560
void end_sprite_batch() {
    gRenderTarget->end_batch();
}
