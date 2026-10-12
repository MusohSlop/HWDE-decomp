// Matching candidates for the demo light entry bodies 0x7100260648-0x7100260740.
// Names are descriptive placeholders. Status: matching/README.md.

#include "event/demo_light_system.h"

class TextureLoader {
public:
    RefObject* make_texture(LightAllocator* allocator, unsigned int color, void* source,
                            TrackVec2 offset);                              // 0x71004e27bc
};
// Reached through the GOT slot at 0x7100c21db0.
extern TextureLoader* gResourceLoader;

// Allocator of the last bound entry, reached through the GOT slot at 0x7100c2a640.
extern LightAllocator* gLightEntryAllocator;

// Default sprite colors (0x7f50f0).
static const LightMatrix kEntryColors = {{
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
}};

static inline void release_texture(RefObject*& ref) {
    RefObject* object = ref;
    if (object) {
        if (--object->ref_count == 0)
            object->destroy();
        ref = nullptr;
    }
}

LightEntry::LightEntry()
    : texture(nullptr), value8(0), value10(0), modes(), position(kTrackDefaultVector),
      target(kTrackDefaultVector), offset(), value58(0), scale{1.0f, 1.0f}, color(), count6c(3), count70(3),
      flags74(0), matrix(), visible(1) {
}

LightEntry::~LightEntry() {
    release_texture(texture);
}

void LightEntry::unload() {
    release_texture(texture);
}

void LightEntry::bind(LightAllocator* allocator) {
    gLightEntryAllocator = allocator;
    position = kTrackDefaultVector;
    target = kTrackDefaultVector;
    color = Color4u8(0xff, 0xff, 0xff, 0xff);
    visible = 1;
    offset.x = 0.0f;
    offset.y = 0.0f;
    count6c = 3;
    count70 = 3;
    flags74 = 0x222;
    matrix = kEntryColors;
    modes[0] = 0;
    modes[1] = 0;
    modes[2] = 1;
    modes[3] = 1;
    modes[4] = 3;
    modes[5] = 3;
    release_texture(texture);
    texture = gResourceLoader->make_texture(allocator, color.a << 24 | color.b << 16 | color.g << 8 | color.r,
                                            nullptr, offset);
}
