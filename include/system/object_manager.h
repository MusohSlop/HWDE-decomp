// System object manager, reached through the GOT slot at 0x7100c21de8.
#pragma once

class FileSystem;

struct ObjectManager {
    unsigned char unknown[0x80];
    unsigned char mutex[0x20];   // +80: nn::os::MutexType storage
    unsigned char unknown_a0[0x28];
    FileSystem* file_system;     // +c8
};
static_assert(__builtin_offsetof(ObjectManager, file_system) == 0xc8, "file system offset");

extern ObjectManager* gObjectManager;
