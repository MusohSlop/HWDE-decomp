// Platform file service (manager +0xc8). Handles are opaque; all bits set means none.
#pragma once

class FileSystem {
public:
    unsigned int open(const char* path, int a, int b, void** handle, void* c, int d);   // 0x71005374a4
    unsigned int close(void** handle, int a);                                         // 0x71005374ac
    unsigned int release(void* handle);                                               // 0x71005374b0
    unsigned int read(void* handle, void* dest, unsigned long size, unsigned long* out,
                      int a);                                                         // 0x71005374b4
    unsigned int seek(void* handle, unsigned long position, int a, unsigned long* out,
                      int b);                                                         // 0x71005374c4
    unsigned int status(void* handle, void* a);                                       // 0x71005374cc
    unsigned long size(void* handle);                                                 // 0x71005374d0
};
