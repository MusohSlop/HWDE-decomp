// Resource file object (0x130 bytes). Semantics: docs/resource-file.md.
#pragma once

class ResourceFile {
public:
    ResourceFile();                                                    // 0x710025a584
    void close();                                                      // 0x710025a5c4
    unsigned char open();                                              // 0x710025a650
    unsigned char read();                                              // 0x710025a764
    void set_name(const char* name, unsigned char scoped, unsigned char unused); // 0x710025a8a0
    unsigned char run(void* dest, unsigned long position, unsigned long size);   // 0x710025a8e8
    unsigned char read_direct(void* dest, unsigned long position, unsigned long size); // 0x710025aa48

private:
    void close_handle();

    unsigned long mPosition;     // +00
    unsigned long mSize;         // +08
    unsigned long mDone;         // +10
    void* mHandle;               // +18
    void* mDest;                 // +20
    char mName[0x100];           // +28
    unsigned char mScoped;       // +128
    unsigned char mGated;        // +129
};
static_assert(sizeof(ResourceFile) == 0x130, "resource file size");
