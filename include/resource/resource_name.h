// Resource path holder used by the metadata service (0x710025a248-0x710025a344).
#pragma once

struct ResourceName {
    const char* path;

    ResourceName();                 // 0x710025a248
    ~ResourceName();                // 0x710025a250
    void finish();                  // 0x710025a254
    void set(const char* value);    // 0x710025a258
    unsigned char exists() const;   // 0x710025a260
    unsigned long size() const;     // 0x710025a344
};
