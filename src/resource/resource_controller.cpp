// Matching candidates for the resource controller unit (0x710025aa48-0x710025adf0).
// Semantics: docs/resource-metadata.md, docs/resource-read.md. Status: matching/README.md.

#include "resource/resource_name.h"

extern "C" int snprintf(char* buffer, unsigned long size, const char* format, ...);  // 0x7100600b30

struct RegionSettings;
RegionSettings* get_region_settings();                // 0x710020bd74
int region_kind(RegionSettings* settings);            // 0x710020c22c

// Name table, reached through the GOT slot at 0x7100c2a620.
extern const char* const gResourceNames[];

unsigned char resource_file_gate();                   // 0x710025a56c
void set_resource_file_gate(unsigned char gate);      // 0x710025a578

class ResourceController {
public:
    void resolve_name(char* buffer, int identity);            // 0x710025ab58
    unsigned int size(unsigned int identity);                 // 0x710025acec

private:
    unsigned char unknown[0x12878];
    unsigned int mCachedSize;     // +12878: size of resource 0x4a1e, or all bits set
};

static inline unsigned int query_size(const char* path) {
    ResourceName name;
    name.set(path);
    return name.exists() ? name.size() : 0;
}

static inline unsigned int query_size_cached(const char* path, unsigned int* cache) {
    ResourceName name;
    name.set(path);
    unsigned int result = name.exists() ? name.size() : 0;
    *cache = result;
    name.finish();
    return result;
}

// Identities 0x834-0x944 are remapped when the region kind is 1. The cases were
// generated from the original jump table at 0x71007f4c48.
void ResourceController::resolve_name(char* buffer, int identity) {
    RegionSettings* settings = get_region_settings();
    if (settings && region_kind(settings) == 1) {
        switch (identity) {
        case 0x834:
            identity = 0x712;
            break;
        case 0x838:
            identity = 0x5ad;
            break;
        case 0x839:
            identity = 0x5af;
            break;
        case 0x83a:
            identity = 0x5b0;
            break;
        case 0x83b:
            identity = 0x5bd;
            break;
        case 0x83c:
            identity = 0x5b3;
            break;
        case 0x83d:
            identity = 0x5be;
            break;
        case 0x83f:
            identity = 0x5c0;
            break;
        case 0x840:
            identity = 0x5c1;
            break;
        case 0x841:
            identity = 0x5c2;
            break;
        case 0x842:
            identity = 0x5c3;
            break;
        case 0x843:
            identity = 0x5c4;
            break;
        case 0x84b:
            identity = 0x5ac;
            break;
        case 0x84c:
            identity = 0x5b9;
            break;
        case 0x84d:
            identity = 0x5ba;
            break;
        case 0x84e:
            identity = 0x5b2;
            break;
        case 0x84f:
            identity = 0x5b5;
            break;
        case 0x851:
            identity = 0x5c9;
            break;
        case 0x852:
            identity = 0x5c5;
            break;
        case 0x858:
            identity = 0x5a9;
            break;
        case 0x859:
            identity = 0x5aa;
            break;
        case 0x85a:
            identity = 0x5a6;
            break;
        case 0x85b:
            identity = 0x5b1;
            break;
        case 0x85c:
            identity = 0x5b4;
            break;
        case 0x85d:
            identity = 0x5b6;
            break;
        case 0x85e:
            identity = 0x5b7;
            break;
        case 0x860:
            identity = 0x5bb;
            break;
        case 0x861:
            identity = 0x5bc;
            break;
        case 0x944:
            identity = 0x5ae;
            break;
        case 0x85f:
            identity = 0x5b8;
            break;
        }
    }
    const char* name = gResourceNames[identity];
    if (*name)
        snprintf(buffer, 0x100, "%s/%s/%s", "rom:", "data", name);
    else
        buffer[0] = 0;
}

unsigned int ResourceController::size(unsigned int identity) {
    unsigned char gate = resource_file_gate();
    set_resource_file_gate(0);
    char path[0x100];
    unsigned int result;
    if (identity == 0x4a1e) {
        result = mCachedSize;
        if (result == 0xffffffff)
            result = query_size_cached(path, &mCachedSize);
    } else {
        resolve_name(path, identity);
        result = query_size(path);
    }
    set_resource_file_gate(gate);
    return result;
}
