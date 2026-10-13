// Matching candidate for the title banner's effect-kind check (0x71001e2218). Kept apart from
// event/title_banner.cpp so that its jump table gets its own .rodata anchor.
// Names are descriptive placeholders. Status: matching/README.md.

struct EffectKey {
    int kind;
};

class EffectManager {
public:
    bool owns(EffectKey* key, int id);                                      // 0x71001e2218
};

bool EffectManager::owns(EffectKey* key, int id) {
    switch (key->kind) {
    case 0:
        return static_cast<unsigned int>(id - 0x41fe) < 7 || id == 0x4624;
    case 1:
        return static_cast<unsigned int>(id - 0x4205) < 8;
    case 2:
        return static_cast<unsigned int>(id - 0x420d) < 5 || static_cast<unsigned int>(id - 0x4625) < 3;
    case 3:
        return id == 0x4212;
    case 4:
        return static_cast<unsigned int>(id - 0x4213) < 10;
    case 5:
        return id == 0x41fd;
    case 6:
        return false;
    case 7:
        return id == 0;
    }
    return false;
}
