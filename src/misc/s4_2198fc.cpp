// Two shader set-ups on one base (fourth session, template family 2198fc): after the base init they look up three uniform
// locations by name (-1 without a material): DarkenShader::setup (0x71002198fc: vDarkenScale, vDarkenOffset, cRim) and
// RogiaShader::setup (0x71002229cc: fRogiaThreshold, fRogiaAdditionalTexThreshold, cRim). Names are descriptive
// placeholders.

class ShaderProgram {
public:
    int uniform(const char* name);                                          // 0x71005a3fac
};
struct ShaderMaterial {
    unsigned char pad0[0x40];
    ShaderProgram* program;   // +40
};

extern const char kDarkenScale_2198fc[] __attribute__((visibility("hidden")));    // 0x710073ff56 "vDarkenScale"
extern const char kDarkenOffset_2198fc[] __attribute__((visibility("hidden")));   // 0x710073ff63 "vDarkenOffset"
extern const char kRim_2198fc[] __attribute__((visibility("hidden")));            // 0x710073ff71 "cRim"
extern const char kRogiaThreshold_2229cc[] __attribute__((visibility("hidden")));       // 0x710073fefc
extern const char kRogiaTexThreshold_2229cc[] __attribute__((visibility("hidden")));    // 0x710073ff0c

class ShaderSetup {
public:
    unsigned char init();                                                   // 0x710058ff40

    int location(const char* name) { return material ? material->program->uniform(name) : -1; }

    unsigned char pad0[0x30];
    ShaderMaterial* material; // +30
    unsigned char pad38[0x1298];
};

class DarkenShader : public ShaderSetup {
public:
    bool setup();

    int pad12d0;
    int scale;                // +12d4
    int offset;               // +12d8
    int rim;                  // +12dc
};

class RogiaShader : public ShaderSetup {
public:
    bool setup();

    int pad12d0;
    int threshold;            // +12d4
    int tex_threshold;        // +12d8
    int rim;                  // +12dc
};

// 0x71002198fc
bool DarkenShader::setup() {
    if (!init()) return false;
    scale = location(kDarkenScale_2198fc);
    offset = location(kDarkenOffset_2198fc);
    rim = location(kRim_2198fc);
    return true;
}

// 0x71002229cc
bool RogiaShader::setup() {
    if (!init()) return false;
    threshold = location(kRogiaThreshold_2229cc);
    tex_threshold = location(kRogiaTexThreshold_2229cc);
    rim = location(kRim_2198fc);
    return true;
}
