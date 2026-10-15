// Complete-object destructors found by the destructor scan: each stores its vtable pointer,
// destroys its own members from the last one down (inner groups with their own bases included),
// then its second base if it has one, and tail-calls its root base's destructor. Classes are named
// after the destructor's address. Status: matching/README.md.

class Root338580_2c0 {
public:
    virtual ~Root338580_2c0();                      // 0x7100338580

    unsigned char pad8[0x2b8];
};

struct Part5d27b4_148 { ~Part5d27b4_148(); unsigned char data[0x148]; };      // 0x71005d27b4
struct Part338440_2250 { ~Part338440_2250(); unsigned char data[0x2250]; };    // 0x7100338440


// Vtable through the GOT slot at 0x7100c2aee0.
class Destructed33a338 : public Root338580_2c0, public Part5d27b4_148 {
public:
    ~Destructed33a338();
    virtual void key_function();

    Part338440_2250 parts_408[2];   // +408
};

// 0x710033a338
Destructed33a338::~Destructed33a338() {}
