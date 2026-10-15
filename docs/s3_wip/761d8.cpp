// 0x71000761d8 (156 B), parked 1 off: the original stores +bc4 (the -1/1.0f pair) before +bcc; here, with the stores in
// this order (the closest found), +bcc comes first. With the natural order (+bc0, +bc4, +bcc) the stores are in order but
// the memset's address is computed before them. Separate id/scale fields, a 12-byte constant, the fields in the init
// list and memset helpers do not help; irsearch cannot read this function's IR back with -g (clang crashes), and
// without -g it finds no better order. Symbols: got:_ZTV8Obj761d8 0x7100c221b0, _ZN9Base7a0c8C2Ev 0x710007a0c8,
// _ZN9Part31364C1Ev 0x7100031364, _ZN9Part4631cC1Ev 0x710004631c.

extern "C" void* memset(void*, int, unsigned long);

// 0x71000761d8: vtable GOT 0x7100c221b0.
class Base7a0c8 {
public:
    Base7a0c8();                 // 0x710007a0c8
    virtual ~Base7a0c8();
    unsigned char pad8[0x50];
};

struct Part31364 {
    Part31364();                 // 0x7100031364
    unsigned char data[0x10];
};

struct Part4631c {
    Part4631c();                 // 0x710004631c
    unsigned char data[0x134];
};

struct Scale761d8 {
    int id;
    float scale;
};
static const Scale761d8 kScale761d8 = {-1, 1.0f};

class Obj761d8 : public Base7a0c8 {
public:
    Obj761d8();
    ~Obj761d8();

    void* p58;                   // +58
    void* p60;                   // +60
    void* p68;                   // +68
    void* p70;                   // +70
    void* p78;                   // +78
    void* p80;                   // +80
    int i88;                     // +88
    int i8c;                     // +8c
    void* p90;                   // +90
    void* p98;                   // +98
    void* pa0;                   // +a0
    void* pa8;                   // +a8
    Part31364 partb0;            // +b0
    int ic0;                     // +c0
    Part4631c partc4;            // +c4
    void* p1f8;                  // +1f8
    void* p200;                  // +200
    void* p208;                  // +208
    void* p210;                  // +210
    int i218;                    // +218
    Part4631c part21c;           // +21c
    unsigned char table[0x870];  // +350
    int ibc0;                    // +bc0
    Scale761d8 scale;            // +bc4
    int ibcc;                    // +bcc
};

Obj761d8::Obj761d8()
    : p58(nullptr), p60(nullptr), p68(nullptr), p70(nullptr), p78(nullptr), p80(nullptr), i88(0), i8c(-1),
      p90(nullptr), pa0(nullptr), pa8(nullptr), ic0(-1), p1f8(nullptr), p200(nullptr), p208(nullptr),
      p210(nullptr), i218(0) {
    ibcc = -1;
    ibc0 = 0;
    scale = kScale761d8;
    memset(table, 0, sizeof(table));
}
