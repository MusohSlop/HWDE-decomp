// Fifth session, parked: 0x71003ccf84 (3,100 bytes), the npad reader. This source compiles to the original size with
// 24 instructions differing (abstract 17), all in the tail: the original shares one reset block (counter address in
// x8, then mov w0, wzr; str wzr, [x8]) between the id == -1 path, the Joy-Con right attribute test and the
// connected test, and lays the miss-count path out as the fallthrough; the keep flag is tested with eor/tbz.
// Here the reset paths stay separate (str wzr, [x8, #4]) and the miss-count path is placed after the epilogue.
// Map: _ZL11sNpad3ccf84=0x7100ca3280 _ZL14sNpadIds3ccf84=0x7100bdbfd0, got:_ZN2nn3hid6NpadId3No1E=0x7100c2b540,
// got:_ZN2nn3hid6NpadId8HandheldE=0x7100c2b548, the nn::hid imports from tools/gen/plt_names.json.
// The setters 3ce1fc and 3ce208 (same unit in the original) keep the flag from being folded.

namespace nn {
namespace util {
template <int N, typename Tag>
struct BitFlagSet {
    unsigned int storage[(N + 31) / 32];
};
template <typename Tag>
struct BitFlagSet<64, Tag> {
    unsigned long storage[1];
};
}  // namespace util
namespace hid {
struct NpadStyleTag;
struct NpadButton;
struct NpadAttribute;
typedef util::BitFlagSet<32, NpadStyleTag> NpadStyleSet;
enum NpadJoyHoldType { NpadJoyHoldType_Vertical, NpadJoyHoldType_Horizontal };
struct VibrationDeviceHandle {
    unsigned int value;
};
struct AnalogStickState {
    int x;
    int y;
};
struct NpadStateBase {
    long samplingNumber;                                  // +0
    util::BitFlagSet<64, NpadButton> buttons;             // +8
    AnalogStickState analogStickL;                        // +10
    AnalogStickState analogStickR;                        // +18
    util::BitFlagSet<32, NpadAttribute> attributes;       // +20
};
struct NpadFullKeyState : NpadStateBase {};
struct NpadJoyDualState : NpadStateBase {};
struct NpadHandheldState : NpadStateBase {};
struct NpadJoyLeftState : NpadStateBase {};
struct NpadJoyRightState : NpadStateBase {};
struct ControllerSupportArg {
    unsigned char playerCountMin;              // +0
    unsigned char playerCountMax;              // +1
    bool enableTakeOverConnection;             // +2
    bool enableLeftJustify;                    // +3
    bool enablePermitJoyDual;                  // +4
    bool enableSingleMode;                     // +5
    bool enableIdentificationColor;            // +6
    unsigned char identificationColor[16];     // +7
    bool enableExplainText;                    // +17
    char explainText[0x204];                   // +18

    void SetDefault() {
        playerCountMin = 0;
        playerCountMax = 4;
        enableTakeOverConnection = true;
        enableLeftJustify = true;
        enablePermitJoyDual = true;
        enableSingleMode = false;
        enableIdentificationColor = false;
        enableExplainText = false;
    }
};
struct ControllerSupportResultInfo {
    int playerCount;
    unsigned int selectedNpadId;
};
namespace NpadId {
extern const unsigned int No1;
extern const unsigned int Handheld;
}  // namespace NpadId
void InitializeNpad();
void SetSupportedNpadStyleSet(NpadStyleSet);
void SetNpadJoyHoldType(NpadJoyHoldType);
void SetSupportedNpadIdType(const unsigned int*, unsigned long);
NpadStyleSet GetNpadStyleSet(const unsigned int&);
struct Result {
    unsigned int value;
};
Result ShowControllerSupport(ControllerSupportResultInfo*, const ControllerSupportArg&);
int GetVibrationDeviceHandles(VibrationDeviceHandle*, int, const unsigned int&, NpadStyleSet);
void InitializeVibrationDevice(const VibrationDeviceHandle&);
void GetNpadState(NpadFullKeyState*, const unsigned int&);
void GetNpadState(NpadJoyDualState*, const unsigned int&);
void GetNpadState(NpadHandheldState*, const unsigned int&);
void GetNpadState(NpadJoyLeftState*, const unsigned int&);
void GetNpadState(NpadJoyRightState*, const unsigned int&);
}  // namespace hid
}  // namespace nn

struct Stick3ccf84 {
    int x;
    int y;
};

struct Pad3ccf84 {
    int kind;                 // +0
    unsigned int buttons;     // +4
    unsigned char pad8[0xc];
    Stick3ccf84 right;        // +14
    Stick3ccf84 left;         // +1c
};

static struct {
    bool keep;
    unsigned char initialized;
    int missCount[2];
    int vibrationCount[2];
    nn::hid::VibrationDeviceHandle vibration[2][2];
} sNpad3ccf84;
static struct {
    unsigned int ids[2];
    unsigned int supported[3];
} sNpadIds3ccf84 = {{0, 0xffffffff}, {0, 1, 0x20}};

// 0x71003ce1fc
void clear_keep_npad_3ce1fc() {
    sNpad3ccf84.keep = false;
}

// 0x71003ce208
void set_keep_npad_3ce208() {
    sNpad3ccf84.keep = true;
}

static inline unsigned short stick_axis_3ccf84(int value) {
    short v = value * 0x80 / 0x7fff + 0x7f;
    if (v < 0) {
        v = 0;
    }
    if (v > 0xff) {
        v = 0xff;
    }
    return v;
}

static inline void read_full_3ccf84(Pad3ccf84* pad, const nn::hid::NpadStateBase& state) {
    unsigned int b = state.buttons.storage[0];
    unsigned int out = 0;
    if (b & 0x10) out |= 0x2;
    if (b & 0x800) out |= 0x1;
    if (b & 0x20) out |= 0x4;
    if (b & 0x400) out |= 0x8;
    if (b & 0x2000) out |= 0x10;
    if (b & 0x4000) out |= 0x20;
    if (b & 0x8000) out |= 0x40;
    if (b & 0x1000) out |= 0x80;
    if (b & 0x100) out |= 0x100;
    if (b & 0x200) out |= 0x200;
    if (b & 0x40) out |= 0x400;
    if (b & 0x80) out |= 0x800;
    if (b & 0x4) out |= 0x1000;
    if (b & 0x1) out |= 0x2000;
    if (b & 0x2) out |= 0x4000;
    if (b & 0x8) out |= 0x8000;
    pad->buttons = out;
    pad->right.x = stick_axis_3ccf84(state.analogStickR.x);
    pad->right.y = stick_axis_3ccf84(-state.analogStickR.y);
    pad->left.x = stick_axis_3ccf84(state.analogStickL.x);
    pad->left.y = stick_axis_3ccf84(-state.analogStickL.y);
    pad->kind = 7;
}

// 0x71003ccf84: reads controller INDEX into PAD (buttons remapped, sticks scaled to 0..255), initialising the
// npad library and the vibration devices on first use; a controller that stays disconnected for 300 calls is
// dropped when removal is allowed.
int call_3ccf84(unsigned int index, Pad3ccf84* pad, unsigned char horizontal) {
    if (!(sNpad3ccf84.initialized & 1)) {
        nn::hid::InitializeNpad();
        nn::hid::NpadStyleSet styles = {{0x1f}};
        nn::hid::SetSupportedNpadStyleSet(styles);
        nn::hid::SetNpadJoyHoldType(nn::hid::NpadJoyHoldType_Horizontal);
        nn::hid::SetSupportedNpadIdType(sNpadIds3ccf84.supported, 3);
        if (nn::hid::GetNpadStyleSet(nn::hid::NpadId::No1).storage[0] == 0) {
            sNpadIds3ccf84.ids[0] = 0x20;
        }
        if (nn::hid::GetNpadStyleSet(nn::hid::NpadId::Handheld).storage[0] == 0) {
            nn::hid::ControllerSupportArg arg;
            arg.SetDefault();
            arg.enableSingleMode = true;
            arg.enableTakeOverConnection = false;
            nn::hid::ControllerSupportResultInfo info;
            if (nn::hid::ShowControllerSupport(&info, arg).value == 0) {
                sNpadIds3ccf84.ids[0] = 0;
                sNpadIds3ccf84.ids[1] = 0xffffffff;
            }
            sNpadIds3ccf84.ids[0] = info.selectedNpadId;
        }
        for (int i = 0; i < 2; i++) {
            if (sNpadIds3ccf84.ids[i] != 0xffffffff) {
                nn::hid::NpadStyleSet style = nn::hid::GetNpadStyleSet(sNpadIds3ccf84.ids[i]);
                if (style.storage[0] != 0) {
                    sNpad3ccf84.vibrationCount[i] =
                        nn::hid::GetVibrationDeviceHandles(sNpad3ccf84.vibration[i], 2, sNpadIds3ccf84.ids[i], style);
                }
                for (int j = 0; j < sNpad3ccf84.vibrationCount[i]; j++) {
                    nn::hid::InitializeVibrationDevice(sNpad3ccf84.vibration[i][j]);
                }
            }
        }
        sNpad3ccf84.initialized = true;
    }
    pad->buttons = 0;
    Stick3ccf84 neutral = {0x7f, 0x7f};
    pad->right = neutral;
    pad->left = neutral;
    if (index == 0) {
        sNpadIds3ccf84.ids[0] = nn::hid::GetNpadStyleSet(nn::hid::NpadId::No1).storage[0] == 0 ? 0x20 : 0;
    }
    unsigned int id = sNpadIds3ccf84.ids[index];
    if (id != 0xffffffff) {
        nn::hid::NpadStyleSet style = nn::hid::GetNpadStyleSet(id);
        int connected = 0;
        if (style.storage[0] & 1) {
            nn::hid::NpadFullKeyState state;
            nn::hid::GetNpadState(&state, id);
            read_full_3ccf84(pad, state);
            connected = state.attributes.storage[0] & 1;
        }
        if (style.storage[0] & 4) {
            nn::hid::NpadJoyDualState state;
            nn::hid::GetNpadState(&state, id);
            read_full_3ccf84(pad, state);
            if ((state.attributes.storage[0] & 5) == 5) {
                connected = (state.attributes.storage[0] & 0x10) ? 1 : connected;
            }
        }
        if (style.storage[0] & 2) {
            nn::hid::NpadHandheldState state;
            nn::hid::GetNpadState(&state, id);
            read_full_3ccf84(pad, state);
            connected = (state.attributes.storage[0] & 1) ? 1 : connected;
        }
        if (style.storage[0] & 8) {
            nn::hid::NpadJoyLeftState state;
            nn::hid::GetNpadState(&state, id);
            if (horizontal) {
                unsigned int b = state.buttons.storage[0];
                unsigned int out = 0;
                if (b & 0x10) out |= 0x2;
                if (b & 0x800) out |= 0x8;
                if (b & 0x40) out |= 0x100;
                if (b & 0x1000000) out |= 0x400;
                if (b & 0x2000000) out |= 0x800;
                if (b & 0x4000) out |= 0x1000;
                if (b & 0x8000) out |= 0x2000;
                if (b & 0x1000) out |= 0x4000;
                if (b & 0x2000) out |= 0x8000;
                pad->buttons = out;
                pad->right.x = 0x7f;
                pad->right.y = 0x7f;
                pad->left.x = stick_axis_3ccf84(-state.analogStickL.y);
                pad->left.y = stick_axis_3ccf84(-state.analogStickL.x);
                pad->kind = 7;
            } else {
                pad->left.x = stick_axis_3ccf84(-state.analogStickL.y);
                pad->left.y = stick_axis_3ccf84(-state.analogStickL.x);
                pad->right.x = 0x7f;
                pad->right.y = 0x7f;
                unsigned long b64 = state.buttons.storage[0];
                unsigned int b = b64;
                unsigned int out;
                if (b64 & 0x2000000) {
                    out = 0;
                    if (b & 0x10) out |= 0x4;
                    if (b & 0x800) out |= 0x1;
                    if (b & 0x1000000) out |= 0x800;
                    if (b & 0x4000) out |= 0x200;
                    if (b & 0x8000) out |= 0x20;
                    if (b & 0x1000) out |= 0x40;
                    if (b & 0x2000) out |= 0x80;
                } else {
                    out = 0;
                    if (b & 0x10) out |= 0x400;
                    if (b & 0x800) out |= 0x8;
                    if (b & 0x1000000) out |= 0x100;
                    if (b & 0x4000) out |= 0x1000;
                    if (b & 0x8000) out |= 0x2000;
                    if (b & 0x1000) out |= 0x4000;
                    if (b & 0x2000) out |= 0x8000;
                }
                pad->kind = 7;
                pad->buttons = out;
            }
            connected = (state.attributes.storage[0] & 1) ? 1 : connected;
        }
        if (style.storage[0] & 0x10) {
            nn::hid::NpadJoyRightState state;
            nn::hid::GetNpadState(&state, id);
            if (horizontal) {
                unsigned int b = state.buttons.storage[0];
                unsigned int out = 0;
                if (b & 0x20) out |= 0x2;
                if (b & 0x400) out |= 0x8;
                if (b & 0x80) out |= 0x100;
                if (b & 0x4000000) out |= 0x400;
                if (b & 0x8000000) out |= 0x800;
                if (b & 0x8) out |= 0x1000;
                if (b & 0x4) out |= 0x2000;
                if (b & 0x1) out |= 0x4000;
                if (b & 0x2) out |= 0x8000;
                pad->buttons = out;
                pad->right.x = 0x7f;
                pad->right.y = 0x7f;
                pad->left.x = stick_axis_3ccf84(state.analogStickR.y);
                pad->left.y = stick_axis_3ccf84(state.analogStickR.x);
                pad->kind = 7;
            } else {
                pad->left.x = stick_axis_3ccf84(state.analogStickR.y);
                pad->left.y = stick_axis_3ccf84(state.analogStickR.x);
                pad->right.x = 0x7f;
                pad->right.y = 0x7f;
                unsigned long b64 = state.buttons.storage[0];
                unsigned int b = b64;
                unsigned int out;
                if (b64 & 0x8000000) {
                    out = 0;
                    if (b & 0x20) out |= 0x4;
                    if (b & 0x400) out |= 0x1;
                    if (b & 0x4000000) out |= 0x800;
                    if (b & 0x8) out |= 0x200;
                    if (b & 0x4) out |= 0x20;
                    if (b & 0x1) out |= 0x40;
                    if (b & 0x2) out |= 0x80;
                } else {
                    out = 0;
                    if (b & 0x20) out |= 0x400;
                    if (b & 0x400) out |= 0x8;
                    if (b & 0x4000000) out |= 0x100;
                    if (b & 0x8) out |= 0x1000;
                    if (b & 0x4) out |= 0x2000;
                    if (b & 0x1) out |= 0x4000;
                    if (b & 0x2) out |= 0x8000;
                }
                pad->kind = 7;
                pad->buttons = out;
            }
            if (state.attributes.storage[0] & 1) {
                goto reset;
            }
        }
        {
            int& misses = sNpad3ccf84.missCount[index];
            if (connected) {
                misses = 0;
                return 0;
            }
            if (misses++ < 300) {
                return 0;
            }
            if (sNpad3ccf84.keep) {
                return 0;
            }
            sNpadIds3ccf84.ids[index] = 0xffffffff;
            return -1;
        }
    }
reset:
    sNpad3ccf84.missCount[index] = 0;
    return 0;
}
