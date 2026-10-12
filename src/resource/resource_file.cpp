// Matching candidates for the resource file unit 0x710025a53c-0x710025aa0c.
// Semantics: docs/resource-file.md. Status: matching/README.md.

#include "resource/file_system.h"
#include "resource/resource_file.h"
#include "system/object_manager.h"
#include "system/stopwatch.h"

extern "C" char* strncpy(char* dst, const char* src, unsigned long size);   // 0x7100600a10

struct SharedState;
SharedState* get_shared_state();                      // 0x71002aae3c
unsigned char shared_state_exiting(SharedState* s);   // 0x71002ac7f0
unsigned char shared_state_stopping(SharedState* s);  // 0x71002aca94
unsigned char resource_queue_cancelled();             // 0x71002589c0
void sleep_worker_retry();                            // 0x7100459d10
void begin_file_scope();                              // 0x71003fa364
void end_file_scope();                                // 0x71003fa368

// Byte at 0x7100bd0a10.
extern unsigned char gResourceFileGate __attribute__((visibility("hidden")));

static Stopwatch sResourceTimer;   // 0x7100c8b088

void restart_resource_timer() {
    sResourceTimer.reset();
    sResourceTimer.start();
}

void resource_file_nop() {}

unsigned char resource_file_gate() {
    return gResourceFileGate;
}

void set_resource_file_gate(unsigned char gate) {
    gResourceFileGate = gate;
}


static void* const kNoHandle = reinterpret_cast<void*>(~0ul);

ResourceFile::ResourceFile() {
    __builtin_memset(mName, 0, sizeof(mName));
    mDone = 0;
    mHandle = kNoHandle;
    mDest = nullptr;
    mScoped = 0;
    mPosition = 0;
    mSize = 0;
}

inline void ResourceFile::close_handle() {
    if (shared_state_exiting(get_shared_state()))
        return;
    if (mHandle != kNoHandle) {
        ObjectManager** manager = &gObjectManager;
        if ((*manager)->file_system->close(&mHandle, 0))
            (*manager)->file_system->release(mHandle);
        mHandle = kNoHandle;
    }
    mDone = 0;
}

void ResourceFile::close() {
    if (mHandle == kNoHandle)
        return;
    close_handle();
}

unsigned char ResourceFile::open() {
    if (mHandle != kNoHandle)
        return true;
    ObjectManager** manager = &gObjectManager;
    FileSystem* fs = (*manager)->file_system;
    if (fs->open(mName, 1, 2, &mHandle, nullptr, 1)) {
        mHandle = kNoHandle;
        return false;
    }
    unsigned int status = (*manager)->file_system->status(mHandle, nullptr);
    while (status == 2) {
        sleep_worker_retry();
        status = (*manager)->file_system->status(mHandle, nullptr);
        if (shared_state_exiting(get_shared_state()) || resource_queue_cancelled()) {
            if (fs->release(mHandle) == 0)
                mHandle = kNoHandle;
            return false;
        }
    }
    unsigned long size = fs->size(mHandle);
    mSize = mSize - 1 >= size ? size : mSize;
    mDone = 0;
    return true;
}

unsigned char ResourceFile::read() {
    if (shared_state_exiting(get_shared_state()))
        return false;
    if (mHandle == kNoHandle)
        return false;
    ObjectManager** manager = &gObjectManager;
    FileSystem* fs = (*manager)->file_system;
    unsigned long position = mPosition;
    mDone = 0;
    unsigned long count;
    if (position) {
        if (fs->seek(mHandle, position, 0, &count, 0))
            return false;
        mDone = count;
    }
    if (fs->read(mHandle, mDest, mSize, &count, 1))
        return false;
    unsigned int status = (*manager)->file_system->status(mHandle, nullptr);
    while (status == 4) {
        sleep_worker_retry();
        status = (*manager)->file_system->status(mHandle, nullptr);
        if (shared_state_exiting(get_shared_state()) || resource_queue_cancelled()) {
            if ((*manager)->file_system->release(mHandle))
                return false;
            mHandle = kNoHandle;
            return false;
        }
    }
    if (count != mSize)
        return false;
    mDone += count;
    return true;
}

void ResourceFile::set_name(const char* name, unsigned char scoped, unsigned char) {
    strncpy(mName, name, 0xff);
    mName[0xff] = 0;
    mDone = 0;
    mHandle = kNoHandle;
    mDest = nullptr;
    mScoped = scoped;
    mGated = 0;
    mPosition = 0;
    mSize = 0;
}

unsigned char ResourceFile::run(void* dest, unsigned long position, unsigned long size) {
    mDest = dest;
    mPosition = position;
    mSize = size;
    if (mScoped)
        begin_file_scope();
    bool result;
    do {
        if (mGated) {
            sResourceTimer.stop();
            if (sResourceTimer.elapsed_ms()) {
                sleep_worker_retry();
                sResourceTimer.start();
            }
        }
        if (resource_queue_cancelled()) {
            result = false;
            goto done;
        }
        if (open()) {
            if (read()) {
                result = true;
                goto done;
            }
            close_handle();
        }
    } while (!shared_state_stopping(get_shared_state()));
    result = false;
done:
    if (mScoped)
        end_file_scope();
    return result;
}
