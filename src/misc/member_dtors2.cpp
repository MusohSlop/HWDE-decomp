// Destructors of plain classes that only destroy their members (last member first, arrays from
// their last element), found by a destructor-shape scan. Structs are named after the destructor's
// address. Status: matching/README.md.

struct Member25b3ac_28 { ~Member25b3ac_28(); unsigned char data[0x28]; };  // 0x710025b3ac
struct Member218c2c_10 { ~Member218c2c_10(); unsigned char data[0x10]; };  // 0x7100218c2c
struct Member5fbbb0_418 { ~Member5fbbb0_418(); unsigned char data[0x418]; }; // 0x71005fbbb0
struct Member462520_120 { ~Member462520_120(); unsigned char data[0x120]; }; // 0x7100462520
struct Member461204_58 { ~Member461204_58(); unsigned char data[0x58]; };  // 0x7100461204
struct Member461204_68 { ~Member461204_68(); unsigned char data[0x68]; };  // 0x7100461204
struct Member466140_28 { ~Member466140_28(); unsigned char data[0x28]; };  // 0x7100466140

struct Members217608 {
    ~Members217608();

    unsigned char pad[0x10];
    Member25b3ac_28 part_10;        // +10
    Member218c2c_10 parts_38[8];    // +38
};

// 0x7100217608
Members217608::~Members217608() {}

struct Members5d383c {
    ~Members5d383c();

    unsigned char pad[0x80];
    Member5fbbb0_418 part_80;        // +80
    Member462520_120 part_498;        // +498
    Member461204_58 part_5b8;        // +5b8
    Member461204_68 part_610;        // +610
    Member466140_28 parts_678[6];    // +678
};

// 0x71005d383c
Members5d383c::~Members5d383c() {}
