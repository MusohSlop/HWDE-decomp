// Destructors found by tools/family_scan.py: each stores its vtable, stops its member at
// +10 if that member is active (passing the shared context from the GOT slot at
// 0x7100c2d020), destroys the member and tail-calls the base destructor (0x71005c3ac8).
// They are byte-identical apart from those references and come from several source
// files, so they are grouped here until those files are linked. Classes are named after
// the destructor address, member types after their destructor. Status: matching/README.md.

class ChannelBase {
public:
    virtual ~ChannelBase();                                                  // 0x71005c3ac8
    unsigned char pad8[8];
};

class ChannelContext;
// Reached through the GOT slot at 0x7100c2d020.
extern ChannelContext* gChannelContext;

struct Channel_46143c {
    void stop(ChannelContext* context);                              // 0x7100461538
    ~Channel_46143c();                                                  // 0x710046143c

    unsigned char active;
};

// 0x710051f788; vtable through the GOT slot at 0x7100c2d048
class ChannelUser_51f788 : public ChannelBase {
public:
    ~ChannelUser_51f788() override;

    Channel_46143c member;    // +10
};

ChannelUser_51f788::~ChannelUser_51f788() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x710051f7e0; vtable through the GOT slot at 0x7100c2d048
class ChannelUser_51f7e0 : public ChannelBase {
public:
    ~ChannelUser_51f7e0() override;

    Channel_46143c member;    // +10
};

ChannelUser_51f7e0::~ChannelUser_51f7e0() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x710051f838; vtable through the GOT slot at 0x7100c2d048
class ChannelUser_51f838 : public ChannelBase {
public:
    ~ChannelUser_51f838() override;

    Channel_46143c member;    // +10
};

ChannelUser_51f838::~ChannelUser_51f838() {
    if (member.active)
        member.stop(gChannelContext);
}

struct Channel_466e48 {
    void stop(ChannelContext* context);                              // 0x7100466f24
    ~Channel_466e48();                                                  // 0x7100466e48

    unsigned char active;
};

// 0x710051f890; vtable through the GOT slot at 0x7100c2d018
class ChannelUser_51f890 : public ChannelBase {
public:
    ~ChannelUser_51f890() override;

    Channel_466e48 member;    // +10
};

ChannelUser_51f890::~ChannelUser_51f890() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x710051f8e8; vtable through the GOT slot at 0x7100c2d018
class ChannelUser_51f8e8 : public ChannelBase {
public:
    ~ChannelUser_51f8e8() override;

    Channel_466e48 member;    // +10
};

ChannelUser_51f8e8::~ChannelUser_51f8e8() {
    if (member.active)
        member.stop(gChannelContext);
}

struct Channel_466f4c {
    void stop(ChannelContext* context);                              // 0x7100467004
    ~Channel_466f4c();                                                  // 0x7100466f4c

    unsigned char active;
};

// 0x710051f940; vtable through the GOT slot at 0x7100c2d028
class ChannelUser_51f940 : public ChannelBase {
public:
    ~ChannelUser_51f940() override;

    Channel_466f4c member;    // +10
};

ChannelUser_51f940::~ChannelUser_51f940() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x710051f998; vtable through the GOT slot at 0x7100c2d028
class ChannelUser_51f998 : public ChannelBase {
public:
    ~ChannelUser_51f998() override;

    Channel_466f4c member;    // +10
};

ChannelUser_51f998::~ChannelUser_51f998() {
    if (member.active)
        member.stop(gChannelContext);
}

struct Channel_4622b0 {
    void stop(ChannelContext* context);                              // 0x71004623d4
    ~Channel_4622b0();                                                  // 0x71004622b0

    unsigned char active;
};

// 0x7100526750; vtable through the GOT slot at 0x7100c2d0f0
class ChannelUser_526750 : public ChannelBase {
public:
    ~ChannelUser_526750() override;

    Channel_4622b0 member;    // +10
};

ChannelUser_526750::~ChannelUser_526750() {
    if (member.active)
        member.stop(gChannelContext);
}

struct Channel_466bc4 {
    void stop(ChannelContext* context);                              // 0x7100466c7c
    ~Channel_466bc4();                                                  // 0x7100466bc4

    unsigned char active;
};

// 0x71005267a8; vtable through the GOT slot at 0x7100c2d140
class ChannelUser_5267a8 : public ChannelBase {
public:
    ~ChannelUser_5267a8() override;

    Channel_466bc4 member;    // +10
};

ChannelUser_5267a8::~ChannelUser_5267a8() {
    if (member.active)
        member.stop(gChannelContext);
}

struct Channel_461204 {
    void stop(ChannelContext* context);                              // 0x71004612ec
    ~Channel_461204();                                                  // 0x7100461204

    unsigned char active;
};

// 0x7100526800; vtable through the GOT slot at 0x7100c2d110
class ChannelUser_526800 : public ChannelBase {
public:
    ~ChannelUser_526800() override;

    Channel_461204 member;    // +10
};

ChannelUser_526800::~ChannelUser_526800() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x7100526858; vtable through the GOT slot at 0x7100c2d110
class ChannelUser_526858 : public ChannelBase {
public:
    ~ChannelUser_526858() override;

    Channel_461204 member;    // +10
};

ChannelUser_526858::~ChannelUser_526858() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x7100526a8c; vtable through the GOT slot at 0x7100c2d0f0
class ChannelUser_526a8c : public ChannelBase {
public:
    ~ChannelUser_526a8c() override;

    Channel_4622b0 member;    // +10
};

ChannelUser_526a8c::~ChannelUser_526a8c() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x7100526ae4; vtable through the GOT slot at 0x7100c2d0f0
class ChannelUser_526ae4 : public ChannelBase {
public:
    ~ChannelUser_526ae4() override;

    Channel_4622b0 member;    // +10
};

ChannelUser_526ae4::~ChannelUser_526ae4() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x7100526b3c; vtable through the GOT slot at 0x7100c2d140
class ChannelUser_526b3c : public ChannelBase {
public:
    ~ChannelUser_526b3c() override;

    Channel_466bc4 member;    // +10
};

ChannelUser_526b3c::~ChannelUser_526b3c() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x7100526b94; vtable through the GOT slot at 0x7100c2d140
class ChannelUser_526b94 : public ChannelBase {
public:
    ~ChannelUser_526b94() override;

    Channel_466bc4 member;    // +10
};

ChannelUser_526b94::~ChannelUser_526b94() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x7100526bec; vtable through the GOT slot at 0x7100c2d110
class ChannelUser_526bec : public ChannelBase {
public:
    ~ChannelUser_526bec() override;

    Channel_461204 member;    // +10
};

ChannelUser_526bec::~ChannelUser_526bec() {
    if (member.active)
        member.stop(gChannelContext);
}

struct Channel_5f8f68 {
    void stop(ChannelContext* context);                              // 0x71005f8f78
    ~Channel_5f8f68();                                                  // 0x71005f8f68

    unsigned char active;
};

// 0x7100526c44; vtable through the GOT slot at 0x7100c2d158
class ChannelUser_526c44 : public ChannelBase {
public:
    ~ChannelUser_526c44() override;

    Channel_5f8f68 member;    // +10
};

ChannelUser_526c44::~ChannelUser_526c44() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x7100526c9c; vtable through the GOT slot at 0x7100c2d158
class ChannelUser_526c9c : public ChannelBase {
public:
    ~ChannelUser_526c9c() override;

    Channel_5f8f68 member;    // +10
};

ChannelUser_526c9c::~ChannelUser_526c9c() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x7100526cf4; vtable through the GOT slot at 0x7100c2d158
class ChannelUser_526cf4 : public ChannelBase {
public:
    ~ChannelUser_526cf4() override;

    Channel_5f8f68 member;    // +10
};

ChannelUser_526cf4::~ChannelUser_526cf4() {
    if (member.active)
        member.stop(gChannelContext);
}

struct Channel_466cd0 {
    void stop(ChannelContext* context);                              // 0x7100466e20
    ~Channel_466cd0();                                                  // 0x7100466cd0

    unsigned char active;
};

// 0x7100526d4c; vtable through the GOT slot at 0x7100c2d188
class ChannelUser_526d4c : public ChannelBase {
public:
    ~ChannelUser_526d4c() override;

    Channel_466cd0 member;    // +10
};

ChannelUser_526d4c::~ChannelUser_526d4c() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x7100526da4; vtable through the GOT slot at 0x7100c2d188
class ChannelUser_526da4 : public ChannelBase {
public:
    ~ChannelUser_526da4() override;

    Channel_466cd0 member;    // +10
};

ChannelUser_526da4::~ChannelUser_526da4() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x7100526dfc; vtable through the GOT slot at 0x7100c2d188
class ChannelUser_526dfc : public ChannelBase {
public:
    ~ChannelUser_526dfc() override;

    Channel_466cd0 member;    // +10
};

ChannelUser_526dfc::~ChannelUser_526dfc() {
    if (member.active)
        member.stop(gChannelContext);
}

struct Channel_5f9428 {
    void stop(ChannelContext* context);                              // 0x71005f9614
    ~Channel_5f9428();                                                  // 0x71005f9428

    unsigned char active;
};

// 0x7100530434; vtable through the GOT slot at 0x7100c2d238
class ChannelUser_530434 : public ChannelBase {
public:
    ~ChannelUser_530434() override;

    Channel_5f9428 member;    // +10
};

ChannelUser_530434::~ChannelUser_530434() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x710053048c; vtable through the GOT slot at 0x7100c2d238
class ChannelUser_53048c : public ChannelBase {
public:
    ~ChannelUser_53048c() override;

    Channel_5f9428 member;    // +10
};

ChannelUser_53048c::~ChannelUser_53048c() {
    if (member.active)
        member.stop(gChannelContext);
}

// 0x71005304e4; vtable through the GOT slot at 0x7100c2d238
class ChannelUser_5304e4 : public ChannelBase {
public:
    ~ChannelUser_5304e4() override;

    Channel_5f9428 member;    // +10
};

ChannelUser_5304e4::~ChannelUser_5304e4() {
    if (member.active)
        member.stop(gChannelContext);
}
