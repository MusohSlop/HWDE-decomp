// Object loaders found by tools/family_scan.py: each opens a memory stream on a data block,
// parses it into a resource on the current heap (the shared state's, else the object
// manager's), and if the resource has the expected type builds an object from it with the
// resource loader; otherwise it drops the resource. The members differ only in the builder
// they call. Grouped here until their source files are linked; functions are named after
// their address. Status: matching/README.md.

class MemoryStream {
public:
    MemoryStream();                                                         // 0x710053d304
    ~MemoryStream();                                                        // 0x710053d338
    void open(const void* data, void* owner, unsigned long size);           // 0x710053d360
    void close();                                                           // 0x710053d388

    unsigned char storage[0x20];
};

struct Heap;
class Resource {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void destroy();   // +18

    int refs;                 // +08
    unsigned char pad[0x24];
    int type;                 // +30
};
Resource* parse_resource(MemoryStream* stream, Heap* heap, Heap* scratch);   // 0x7100595f98

struct SharedState {
    unsigned char pad[0x10];
    Heap* heap;               // +10
};
SharedState* get_shared_state();                                            // 0x71002aae3c
struct ObjectManager {
    unsigned char pad[0x10];
    Heap* heap;               // +10
};
// Reached through the GOT slots at 0x7100c21de8, 0x7100c21db0 and 0x7100c220f8.
extern ObjectManager* gObjectManager;
struct ResourceLoader;
extern ResourceLoader* gResourceLoader;
extern int gObjectResourceType;

void* build_object_72768(ResourceLoader* loader, Resource* resource, int c, void* d, Heap* heap, int b,
                         void* e);                              // 0x7100072768

// 0x7100071838
void* load_object_71838(const void* data, unsigned int size, int b, int c, void* d) {
    MemoryStream stream;
    stream.open(data, nullptr, size);
    ResourceLoader* loader = gResourceLoader;
    Heap* heap = get_shared_state()->heap;
    if (!heap)
        heap = gObjectManager->heap;
    void* object = nullptr;
    if (Resource* resource = parse_resource(&stream, heap, heap)) {
        if (resource->type == gObjectResourceType) {
            object = build_object_72768(loader, resource, c, d, heap, b, nullptr);
        } else if (!--resource->refs) {
            resource->destroy();
        }
    }
    stream.close();
    return object;
}

void* build_object_73070(ResourceLoader* loader, Resource* resource, int c, void* d, Heap* heap, int b,
                         void* e);                              // 0x7100073070

// 0x7100071950
void* load_object_71950(const void* data, unsigned int size, int b, int c, void* d) {
    MemoryStream stream;
    stream.open(data, nullptr, size);
    ResourceLoader* loader = gResourceLoader;
    Heap* heap = get_shared_state()->heap;
    if (!heap)
        heap = gObjectManager->heap;
    void* object = nullptr;
    if (Resource* resource = parse_resource(&stream, heap, heap)) {
        if (resource->type == gObjectResourceType) {
            object = build_object_73070(loader, resource, c, d, heap, b, nullptr);
        } else if (!--resource->refs) {
            resource->destroy();
        }
    }
    stream.close();
    return object;
}

void* build_object_73770(ResourceLoader* loader, Resource* resource, int c, void* d, Heap* heap, int b,
                         void* e);                              // 0x7100073770

// 0x7100071a68
void* load_object_71a68(const void* data, unsigned int size, int b, int c, void* d) {
    MemoryStream stream;
    stream.open(data, nullptr, size);
    ResourceLoader* loader = gResourceLoader;
    Heap* heap = get_shared_state()->heap;
    if (!heap)
        heap = gObjectManager->heap;
    void* object = nullptr;
    if (Resource* resource = parse_resource(&stream, heap, heap)) {
        if (resource->type == gObjectResourceType) {
            object = build_object_73770(loader, resource, c, d, heap, b, nullptr);
        } else if (!--resource->refs) {
            resource->destroy();
        }
    }
    stream.close();
    return object;
}

void* build_object_73e50(ResourceLoader* loader, Resource* resource, int c, void* d, Heap* heap, int b,
                         void* e);                              // 0x7100073e50

// 0x7100071b80
void* load_object_71b80(const void* data, unsigned int size, int b, int c, void* d) {
    MemoryStream stream;
    stream.open(data, nullptr, size);
    ResourceLoader* loader = gResourceLoader;
    Heap* heap = get_shared_state()->heap;
    if (!heap)
        heap = gObjectManager->heap;
    void* object = nullptr;
    if (Resource* resource = parse_resource(&stream, heap, heap)) {
        if (resource->type == gObjectResourceType) {
            object = build_object_73e50(loader, resource, c, d, heap, b, nullptr);
        } else if (!--resource->refs) {
            resource->destroy();
        }
    }
    stream.close();
    return object;
}

void* build_object_74520(ResourceLoader* loader, Resource* resource, int c, void* d, Heap* heap, int b,
                         void* e);                              // 0x7100074520

// 0x7100071c98
void* load_object_71c98(const void* data, unsigned int size, int b, int c, void* d) {
    MemoryStream stream;
    stream.open(data, nullptr, size);
    ResourceLoader* loader = gResourceLoader;
    Heap* heap = get_shared_state()->heap;
    if (!heap)
        heap = gObjectManager->heap;
    void* object = nullptr;
    if (Resource* resource = parse_resource(&stream, heap, heap)) {
        if (resource->type == gObjectResourceType) {
            object = build_object_74520(loader, resource, c, d, heap, b, nullptr);
        } else if (!--resource->refs) {
            resource->destroy();
        }
    }
    stream.close();
    return object;
}

void* build_object_21d074(ResourceLoader* loader, Resource* resource, int c, void* d, Heap* heap, int b,
                          void* e);                              // 0x710021d074

// 0x710021a224
void* load_object_21a224(const void* data, unsigned int size, int b, int c, void* d) {
    MemoryStream stream;
    stream.open(data, nullptr, size);
    ResourceLoader* loader = gResourceLoader;
    Heap* heap = get_shared_state()->heap;
    if (!heap)
        heap = gObjectManager->heap;
    void* object = nullptr;
    if (Resource* resource = parse_resource(&stream, heap, heap)) {
        if (resource->type == gObjectResourceType) {
            object = build_object_21d074(loader, resource, c, d, heap, b, nullptr);
        } else if (!--resource->refs) {
            resource->destroy();
        }
    }
    stream.close();
    return object;
}

void* build_object_21d738(ResourceLoader* loader, Resource* resource, int c, void* d, Heap* heap, int b,
                          void* e);                              // 0x710021d738

// 0x710021a33c
void* load_object_21a33c(const void* data, unsigned int size, int b, int c, void* d) {
    MemoryStream stream;
    stream.open(data, nullptr, size);
    ResourceLoader* loader = gResourceLoader;
    Heap* heap = get_shared_state()->heap;
    if (!heap)
        heap = gObjectManager->heap;
    void* object = nullptr;
    if (Resource* resource = parse_resource(&stream, heap, heap)) {
        if (resource->type == gObjectResourceType) {
            object = build_object_21d738(loader, resource, c, d, heap, b, nullptr);
        } else if (!--resource->refs) {
            resource->destroy();
        }
    }
    stream.close();
    return object;
}

void* build_object_21ddf8(ResourceLoader* loader, Resource* resource, int c, void* d, Heap* heap, int b,
                          void* e);                              // 0x710021ddf8

// 0x710021a454
void* load_object_21a454(const void* data, unsigned int size, int b, int c, void* d) {
    MemoryStream stream;
    stream.open(data, nullptr, size);
    ResourceLoader* loader = gResourceLoader;
    Heap* heap = get_shared_state()->heap;
    if (!heap)
        heap = gObjectManager->heap;
    void* object = nullptr;
    if (Resource* resource = parse_resource(&stream, heap, heap)) {
        if (resource->type == gObjectResourceType) {
            object = build_object_21ddf8(loader, resource, c, d, heap, b, nullptr);
        } else if (!--resource->refs) {
            resource->destroy();
        }
    }
    stream.close();
    return object;
}

void* build_object_21e4b8(ResourceLoader* loader, Resource* resource, int c, void* d, Heap* heap, int b,
                          void* e);                              // 0x710021e4b8

// 0x710021a56c
void* load_object_21a56c(const void* data, unsigned int size, int b, int c, void* d) {
    MemoryStream stream;
    stream.open(data, nullptr, size);
    ResourceLoader* loader = gResourceLoader;
    Heap* heap = get_shared_state()->heap;
    if (!heap)
        heap = gObjectManager->heap;
    void* object = nullptr;
    if (Resource* resource = parse_resource(&stream, heap, heap)) {
        if (resource->type == gObjectResourceType) {
            object = build_object_21e4b8(loader, resource, c, d, heap, b, nullptr);
        } else if (!--resource->refs) {
            resource->destroy();
        }
    }
    stream.close();
    return object;
}

void* build_object_21eb98(ResourceLoader* loader, Resource* resource, int c, void* d, Heap* heap, int b,
                          void* e);                              // 0x710021eb98

// 0x710021a684
void* load_object_21a684(const void* data, unsigned int size, int b, int c, void* d) {
    MemoryStream stream;
    stream.open(data, nullptr, size);
    ResourceLoader* loader = gResourceLoader;
    Heap* heap = get_shared_state()->heap;
    if (!heap)
        heap = gObjectManager->heap;
    void* object = nullptr;
    if (Resource* resource = parse_resource(&stream, heap, heap)) {
        if (resource->type == gObjectResourceType) {
            object = build_object_21eb98(loader, resource, c, d, heap, b, nullptr);
        } else if (!--resource->refs) {
            resource->destroy();
        }
    }
    stream.close();
    return object;
}

void* build_object_21f318(ResourceLoader* loader, Resource* resource, int c, void* d, Heap* heap, int b,
                          void* e);                              // 0x710021f318

// 0x710021a79c
void* load_object_21a79c(const void* data, unsigned int size, int b, int c, void* d) {
    MemoryStream stream;
    stream.open(data, nullptr, size);
    ResourceLoader* loader = gResourceLoader;
    Heap* heap = get_shared_state()->heap;
    if (!heap)
        heap = gObjectManager->heap;
    void* object = nullptr;
    if (Resource* resource = parse_resource(&stream, heap, heap)) {
        if (resource->type == gObjectResourceType) {
            object = build_object_21f318(loader, resource, c, d, heap, b, nullptr);
        } else if (!--resource->refs) {
            resource->destroy();
        }
    }
    stream.close();
    return object;
}

void* build_object_21f9f8(ResourceLoader* loader, Resource* resource, int c, void* d, Heap* heap, int b,
                          void* e);                              // 0x710021f9f8

// 0x710021a8b4
void* load_object_21a8b4(const void* data, unsigned int size, int b, int c, void* d) {
    MemoryStream stream;
    stream.open(data, nullptr, size);
    ResourceLoader* loader = gResourceLoader;
    Heap* heap = get_shared_state()->heap;
    if (!heap)
        heap = gObjectManager->heap;
    void* object = nullptr;
    if (Resource* resource = parse_resource(&stream, heap, heap)) {
        if (resource->type == gObjectResourceType) {
            object = build_object_21f9f8(loader, resource, c, d, heap, b, nullptr);
        } else if (!--resource->refs) {
            resource->destroy();
        }
    }
    stream.close();
    return object;
}

void* build_object_2200b8(ResourceLoader* loader, Resource* resource, int c, void* d, Heap* heap, int b,
                          void* e);                              // 0x71002200b8

// 0x710021a9cc
void* load_object_21a9cc(const void* data, unsigned int size, int b, int c, void* d) {
    MemoryStream stream;
    stream.open(data, nullptr, size);
    ResourceLoader* loader = gResourceLoader;
    Heap* heap = get_shared_state()->heap;
    if (!heap)
        heap = gObjectManager->heap;
    void* object = nullptr;
    if (Resource* resource = parse_resource(&stream, heap, heap)) {
        if (resource->type == gObjectResourceType) {
            object = build_object_2200b8(loader, resource, c, d, heap, b, nullptr);
        } else if (!--resource->refs) {
            resource->destroy();
        }
    }
    stream.close();
    return object;
}

void* build_object_44da50(ResourceLoader* loader, Resource* resource, int c, void* d, Heap* heap, int b,
                          void* e);                              // 0x710044da50

// 0x710044cfc8
void* load_object_44cfc8(const void* data, unsigned int size, int b, int c, void* d) {
    MemoryStream stream;
    stream.open(data, nullptr, size);
    ResourceLoader* loader = gResourceLoader;
    Heap* heap = get_shared_state()->heap;
    if (!heap)
        heap = gObjectManager->heap;
    void* object = nullptr;
    if (Resource* resource = parse_resource(&stream, heap, heap)) {
        if (resource->type == gObjectResourceType) {
            object = build_object_44da50(loader, resource, c, d, heap, b, nullptr);
        } else if (!--resource->refs) {
            resource->destroy();
        }
    }
    stream.close();
    return object;
}

void* build_object_44e15c(ResourceLoader* loader, Resource* resource, int c, void* d, Heap* heap, int b,
                          void* e);                              // 0x710044e15c

// 0x710044d0e0
void* load_object_44d0e0(const void* data, unsigned int size, int b, int c, void* d) {
    MemoryStream stream;
    stream.open(data, nullptr, size);
    ResourceLoader* loader = gResourceLoader;
    Heap* heap = get_shared_state()->heap;
    if (!heap)
        heap = gObjectManager->heap;
    void* object = nullptr;
    if (Resource* resource = parse_resource(&stream, heap, heap)) {
        if (resource->type == gObjectResourceType) {
            object = build_object_44e15c(loader, resource, c, d, heap, b, nullptr);
        } else if (!--resource->refs) {
            resource->destroy();
        }
    }
    stream.close();
    return object;
}

void* build_object_44e84c(ResourceLoader* loader, Resource* resource, int c, void* d, Heap* heap, int b,
                          void* e);                              // 0x710044e84c

// 0x710044d1f8
void* load_object_44d1f8(const void* data, unsigned int size, int b, int c, void* d) {
    MemoryStream stream;
    stream.open(data, nullptr, size);
    ResourceLoader* loader = gResourceLoader;
    Heap* heap = get_shared_state()->heap;
    if (!heap)
        heap = gObjectManager->heap;
    void* object = nullptr;
    if (Resource* resource = parse_resource(&stream, heap, heap)) {
        if (resource->type == gObjectResourceType) {
            object = build_object_44e84c(loader, resource, c, d, heap, b, nullptr);
        } else if (!--resource->refs) {
            resource->destroy();
        }
    }
    stream.close();
    return object;
}

void* build_object_44ffb8(ResourceLoader* loader, Resource* resource, int c, void* d, Heap* heap, int b,
                          void* e);                              // 0x710044ffb8

// 0x710044d310
void* load_object_44d310(const void* data, unsigned int size, int b, int c, void* d) {
    MemoryStream stream;
    stream.open(data, nullptr, size);
    ResourceLoader* loader = gResourceLoader;
    Heap* heap = get_shared_state()->heap;
    if (!heap)
        heap = gObjectManager->heap;
    void* object = nullptr;
    if (Resource* resource = parse_resource(&stream, heap, heap)) {
        if (resource->type == gObjectResourceType) {
            object = build_object_44ffb8(loader, resource, c, d, heap, b, nullptr);
        } else if (!--resource->refs) {
            resource->destroy();
        }
    }
    stream.close();
    return object;
}

void* build_object_450710(ResourceLoader* loader, Resource* resource, int c, void* d, Heap* heap, int b,
                          void* e);                              // 0x7100450710

// 0x710044d428
void* load_object_44d428(const void* data, unsigned int size, int b, int c, void* d) {
    MemoryStream stream;
    stream.open(data, nullptr, size);
    ResourceLoader* loader = gResourceLoader;
    Heap* heap = get_shared_state()->heap;
    if (!heap)
        heap = gObjectManager->heap;
    void* object = nullptr;
    if (Resource* resource = parse_resource(&stream, heap, heap)) {
        if (resource->type == gObjectResourceType) {
            object = build_object_450710(loader, resource, c, d, heap, b, nullptr);
        } else if (!--resource->refs) {
            resource->destroy();
        }
    }
    stream.close();
    return object;
}

void* build_object_450dd4(ResourceLoader* loader, Resource* resource, int c, void* d, Heap* heap, int b,
                          void* e);                              // 0x7100450dd4

// 0x710044d540
void* load_object_44d540(const void* data, unsigned int size, int b, int c, void* d) {
    MemoryStream stream;
    stream.open(data, nullptr, size);
    ResourceLoader* loader = gResourceLoader;
    Heap* heap = get_shared_state()->heap;
    if (!heap)
        heap = gObjectManager->heap;
    void* object = nullptr;
    if (Resource* resource = parse_resource(&stream, heap, heap)) {
        if (resource->type == gObjectResourceType) {
            object = build_object_450dd4(loader, resource, c, d, heap, b, nullptr);
        } else if (!--resource->refs) {
            resource->destroy();
        }
    }
    stream.close();
    return object;
}
