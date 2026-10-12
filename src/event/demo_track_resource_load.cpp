// Matching candidate for the demo track resource loader body 0x710025cf50.
// Names are descriptive placeholders. Status: matching/README.md.

#include "event/demo_track_resources.h"

unsigned int resource_size(unsigned int identity);                          // 0x710025a178
void* resource_read(unsigned int identity, void* dest, unsigned int offset,
                    unsigned int size, void* owner, unsigned int flags);    // 0x710025a1ac
void resource_free(void* storage);                                          // 0x710025a1ec

// Stream over a resource held in memory.
class MemoryStream {
public:
    MemoryStream();                                                     // 0x710053d304
    ~MemoryStream();                                                    // 0x710053d338
    void open(const void* data, void* owner, unsigned long size);       // 0x710053d360
    void close();                                                       // 0x710053d388

private:
    unsigned char storage[0x20];
};

class ResourceLoader {
public:
    RefObject* load(MemoryStream* stream);                              // 0x710051ad9c
};
// Reached through the GOT slot at 0x7100c21db0.
extern ResourceLoader* gResourceLoader;

RefObject* TrackResources::load_one(unsigned int id) {
    void* data = resource_read(id, nullptr, 0, 0, nullptr, 0);
    if (!data)
        return nullptr;
    unsigned int size = resource_size(id);
    if (size == 0) {
        resource_free(data);
        return nullptr;
    }
    RefObject* result;
    {
        MemoryStream stream;
        stream.open(data, nullptr, size);
        result = gResourceLoader->load(&stream);
        stream.close();
    }
    resource_free(data);
    return result;
}
