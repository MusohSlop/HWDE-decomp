// Fifth session, parked: 0x71005efb3c (6,012 bytes), the stream voice's update (a state machine over
// state +dc8: 0 idle, 1 starting, 2 playing, 3 pausing, 4 paused, 5 resuming, 6 closing). It runs the faders
// (main, pause, volume, pitch and up to six channel groups, 0x28 bytes each), copies the newest command block out of
// the double buffer at +dd8 (flags read with ldarh, cleared with stlr), applies it to the current command at +f78
// (whole, or bit by bit), starts or stops the stream, creates and releases the voices, submits the decoded block as
// one wave buffer per voice, retires released buffers, and publishes a status block under the write lock.
// This draft is the original's size (6,012 B); edit distance 168 instructions abstracted, 488 exact (tools/s5/lev.py,
// sbs.py --lev: difflib's counts pair the two copies of the effects block wrongly here and read about 340).
// Settled (each measured): the changed flag is a bool (no masking on the ors); the 8-byte command fields (start
// info, pan, gain) are passed by value to small setters that store the halves (one ldr x, two str w), with the
// 2D vector a union so it is not an HFA; the range test of the start fraction is written to let NaN through
// (f < 0 || f >= 1 fails: b.mi/b.ge); the pause and resume commands work on the state cached in a local and the
// pause one is a switch (case 3 needs time 0; the cached state is the constant 3 on that path, mov w8, #3); the
// start/stop dispatch on bit 0 is a switch (the range 1-5 is tested first); vol, pitch and group fades go through
// fade_to(target, time) (the target is loaded before the fader's current value); the state dispatch tests the
// starting state's block first in source so it is the fall-through; the start position is a switch with the cases
// in the order 0, 0x4000, 0x8000 (lowered 0x8000, 0x4000, 0 as in the original); the command copy is the flags
// stored first (volatile u16, so its reads stay in memory) and one memcpy of the rest, which SROA splits into the
// original's pieces (0x3a, scalars, 0x34, 0x34, 8). Second pass: the release loop's index is an unsigned long tested
// as (int)i < (int)count (64-bit index for the addresses, 32-bit exit compare) with the inner test written
// count > i; the busy scan's index is a long over (buffers + read_index)[j * block_count]; the wave buffer address
// is dest + stride * (unsigned)i, which LSR turns into the original's 64-bit accumulator over the widened
// stride|start load (an explicit u32 accumulator splits that load in two); the context pointer is read before the
// x30/in_use stores; the pitch ratio (exp2f * gain.y) is computed before the loop (MachineSink moves it past the
// count test); the normal start also sets pitch_changed; Fader::remaining multiplies step * count; the position
// is computed into a local before the status stores.
// Still off: register allocation (0x43 sits in w27 instead of w24, applied in w24 instead of w26, pitch_changed is
// spilled at the first path instead of living in w27, so the spill area is 0x10 bytes smaller and every sp offset
// differs), the group update loop's channels load hoisted above the tbz (the original reloads it on both paths), the
// command copy's memcpy source taken from the field base (x25 + 0xdda) instead of the flags pointer (x21 + 2), the
// info base kept in x23 in the start path, the start transition's block layout, the pan/mix tail (the original tests
// output_changed in two blocks, cbz and tbz), and the advance block's schedule.
// Maps: the nn::audio and nn::os imports by their mangled names (0x7100601910-0x7100601c70), exp2f (0x7100601430),
//   and .rodata (the state-to-status lookup table) at 0x7100a9adc0.
extern "C" void* memcpy(void* dest, const void* src, unsigned long size);   // 0x7100600870
extern "C" void* memset(void* dest, int value, unsigned long size);         // 0x7100600890
extern "C" float exp2f(float x);                                            // 0x7100601430

namespace nn {
namespace audio {
struct VoiceType {
    enum PlayState { PlayState_Started, PlayState_Stopped, PlayState_Paused };
    void* impl;
};
struct SubMixType {
    void* impl;
};
struct AudioRendererConfig {
    void* impl[4];
};
struct MemoryPoolType {
    void* impl;
};
struct WaveBuffer;
void SetVoicePlayState(VoiceType* voice, VoiceType::PlayState state);                     // 0x7100601bf0
void SetVoiceVolume(VoiceType* voice, float volume);                                      // 0x7100601c00
void SetVoicePitch(VoiceType* voice, float pitch);                                        // 0x7100601c40
void ReleaseVoiceSlot(AudioRendererConfig* config, VoiceType* voice);                     // 0x7100601bb0
void ReleaseSubMix(AudioRendererConfig* config, SubMixType* mix);                         // 0x7100601910
void SetSubMixVolume(SubMixType* mix, float volume);                                      // 0x7100601c30
void CopyMemoryPoolData(const MemoryPoolType* pool, void* dest, const void* src, unsigned long size);   // 0x7100601c10
bool AppendWaveBuffer(VoiceType* voice, const WaveBuffer* buffer);                        // 0x7100601c20
const WaveBuffer* GetReleasedWaveBuffer(VoiceType* voice);                                // 0x7100601c50
long GetVoicePlayedSampleCount(const VoiceType* voice);                                   // 0x7100601c70
}  // namespace audio
namespace os {
struct ReaderWriterLockType {
    unsigned char storage[0x38];
};
bool TryAcquireWriteLock(ReaderWriterLockType* lock);                                     // 0x7100601c60
void ReleaseWriteLock(ReaderWriterLockType* lock);                                        // 0x7100601950
}  // namespace os
}  // namespace nn

struct Owner5efb3c {
    unsigned char pad0[0x3c0];
    nn::audio::AudioRendererConfig config;  // +3c0
    unsigned char pad3e0[0x84];
    int frame;                              // +464
    unsigned char pad468[0x90];
    int x4f8;                               // +4f8
};

// A volume ramp (0x28 bytes).
struct Fader5efb3c {
    int count;                // +0
    unsigned int rate;        // +4
    int x8;                   // +8
    float duration;           // +c
    float x10;                // +10
    int step;                 // +14
    float x18;                // +18
    float target;             // +1c
    float value;              // +20
    unsigned char dirty;      // +24
    unsigned char pad25[3];

    bool update_5f3d28(int frame);                                              // 0x71005f3d28
    void start_5f3cc4(float from, float to, unsigned int time, int curve);      // 0x71005f3cc4

    bool fading() const { return duration > 0.0f; }
    void fade_to(float to, unsigned int time) { start_5f3cc4(value, to, time, 0); }
    void clean() {
        if (dirty) {
            dirty = 0;
        }
    }
    unsigned int remaining() const {
        float elapsed = static_cast<float>(static_cast<unsigned int>(step * count) / rate);
        return duration > elapsed ? static_cast<unsigned int>(duration - elapsed) : 0;
    }
};

struct StopParams5efb3c {
    int mode;
    unsigned int time;
    int curve;
};
struct FadeParams5efb3c {
    float target;
    unsigned int time;
};
// The engine's 2D vector: a union, so by value it travels as one 64-bit integer.
union Vec2u5efb3c {
    struct {
        float x;
        float y;
    };
    long bits;
};
static inline Vec2u5efb3c vec2(float x, float y) {
    Vec2u5efb3c r;
    r.x = x;
    r.y = y;
    return r;
}
struct GroupParams5efb3c {
    unsigned int mask;
    float volume[6];
    unsigned int time[6];
};
struct Effect5efb3c {
    unsigned char on;
    unsigned char pad1[3];
    unsigned int params[5];
};
struct EffectParams5efb3c {
    unsigned int mask;
    Effect5efb3c effects[2];
};
struct StartInfo5efb3c {
    unsigned int flags;
    unsigned int position;
};

// A command block (0xd0 bytes): the game thread fills one of two and publishes it, the voice copies it out.
struct Command5efb3c {
    volatile unsigned short flags;  // +0
    unsigned short x2;              // +2
    int x4;                         // +4
    long source;                    // +8
    void* handle;                   // +10
    StartInfo5efb3c start;          // +18
    int x20;                        // +20
    unsigned int fade_in_time;      // +24
    int fade_in_curve;              // +28
    unsigned char x2c;              // +2c
    StopParams5efb3c stop;          // +30
    unsigned int pause_time;        // +3c
    FadeParams5efb3c volume;        // +40
    FadeParams5efb3c pitch;         // +48
    Vec2u5efb3c pan;            // +50
    int x58;                        // +58
    int x5c;                        // +5c
    GroupParams5efb3c groups;       // +60
    EffectParams5efb3c effects;     // +94
    Vec2u5efb3c gain;           // +c8
};

struct WaveBuffer5efb3c {
    const void* buffer;       // +0
    unsigned long size;       // +8
    int start;                // +10
    int end;                  // +14
    bool loop;                // +18
    bool end_of_stream;       // +19
    unsigned char pad1a[6];
    const void* context;      // +20
    unsigned long context_size;  // +28
    int x30;                  // +30
    bool in_use;              // +34
    unsigned char pad35[3];
};

struct Block5efb3c {
    unsigned int count;       // +0
    unsigned int size;        // +4
    unsigned int stride;      // +8
    int start;                // +c
    int end;                  // +10
    int x14;                  // +14
    unsigned int context_size;  // +18
    unsigned int pad1c;
    const void* data;         // +20
    const void* contexts[12]; // +28
};

struct Pan5efb3c {
    float x0;
    float x4;
    float mix[24];
};

struct StreamInfo5efb3c {
    long total;               // +190
    int rate;                 // +198
    int channels;             // +19c
    int loop_start;           // +1a0
    int loop_length;          // +1a4
};

struct Status5efb3c {
    unsigned int code;        // +0
    float volume;             // +4
    float fader_volume;       // +8
    float fader_pitch;        // +c
    unsigned int x10;         // +10
    float x14;                // +14
    float position;           // +18
    unsigned char pad1c[2];
    unsigned char channels;   // +1e
    unsigned char looped;     // +1f
    int rate;                 // +20
    int total;                // +24
    int loop_start;           // +28
    int loop_end;             // +2c
    long played;              // +30
    int x38;                  // +38
    float x3c;                // +3c
};

struct Stream5efb3c {
    unsigned char pad0[0x70];
    void* x70;                // +70
    unsigned char pad78[0x48];

    bool ready_5f7db4(int wait);                                                          // 0x71005f7db4
    bool open_5f7b80(void* a, void* b, void* c, long source);                             // 0x71005f7b80
    bool seek_5f7ce0(long* position);                                                     // 0x71005f7ce0
    void close_5f7c98();                                                                  // 0x71005f7c98
    void read_5f7d3c(char* dest, int size);                                               // 0x71005f7d3c
};

struct Loader5efb3c {
    unsigned char pad0[0x18];
    void set_5f813c(void* handle);                                                        // 0x71005f813c
    void reset_5f8180();                                                                  // 0x71005f8180
};

struct Mixer5efb3c {
    unsigned char pad0[0x2c];
    bool idle_5eb330();                                                                   // 0x71005eb330
    void release_5ecfcc(Owner5efb3c* owner, nn::audio::SubMixType* mix);                  // 0x71005ecfcc
    void update_5eb388();                                                                 // 0x71005eb388
};

struct Meter5efb3c {
    float level_5ec694(unsigned char channels);                                           // 0x71005ec694
};

void release_handle_5f3c40(void* handle);                                                 // 0x71005f3c40
bool create_voices_5ee2d8(nn::audio::VoiceType* voices, Owner5efb3c* owner, int a, StreamInfo5efb3c* info,
                          unsigned char b, void* c, int d, unsigned int e);               // 0x71005ee2d8
void update_voices_5ee650(nn::audio::VoiceType* voices);                                  // 0x71005ee650
void calc_pan_5e96b4(float x, float y, float z, Pan5efb3c* out);                          // 0x71005e96b4
void apply_pan_5f13f0(nn::audio::VoiceType* voices, float* mix);                          // 0x71005f13f0

static inline bool idle(int state) {
    return state == 0 || state == 1 || state == 6;
}

struct Voice5efb3c {
    Owner5efb3c* owner;                       // +0
    nn::audio::MemoryPoolType pool;           // +8
    nn::os::ReaderWriterLockType lock;        // +10
    unsigned char x48[0x48];                  // +48
    unsigned char x90[0x28];                  // +90
    Loader5efb3c loader;                      // +b8
    Stream5efb3c stream;                      // +d0
    StreamInfo5efb3c info;                    // +190
    unsigned char pad1a8[0x284];
    volatile int x42c;                        // +42c
    unsigned char x430[2];
    unsigned char x432;                       // +432
    unsigned char pad433[5];
    Block5efb3c block;                        // +438
    unsigned char pad4c0[0xe0];
    nn::audio::VoiceType voices[12];          // +5a0
    nn::audio::SubMixType submix;             // +600
    Mixer5efb3c mixer;                        // +608
    Meter5efb3c meter;                        // +634
    unsigned char pad635[0x323];
    Effect5efb3c effect0;                     // +958
    unsigned char effect0_state[0x60];        // +970
    Effect5efb3c effect1;                     // +9d0
    unsigned char effect1_state[0x60];        // +9e8
    unsigned char pada48[0x20];
    int queued[48];                           // +a68
    int xb28;                                 // +b28
    unsigned int voice_count;                 // +b2c
    int channels;                             // +b30
    unsigned int padb34;
    unsigned char xb38[0x20];                 // +b38
    Fader5efb3c main;                         // +b58
    Fader5efb3c pause;                        // +b80
    Fader5efb3c volume;                       // +ba8
    Fader5efb3c pitch;                        // +bd0
    Fader5efb3c groups[6];                    // +bf8
    Vec2u5efb3c pan;                      // +ce8
    Vec2u5efb3c gain;                     // +cf0
    int block_size;                           // +cf8
    unsigned int padcfc;
    char* read_base;                          // +d00
    char* buffer_base;                        // +d08
    int block_count;                          // +d10
    unsigned int padd14;
    WaveBuffer5efb3c* buffers;                // +d18
    int read_index;                           // +d20
    int pending;                              // +d24
    int queued_blocks;                        // +d28
    unsigned int play_flags;                  // +d2c
    int start_mode;                           // +d30
    unsigned int start_position;              // +d34
    int xd38;                                 // +d38
    unsigned int padd3c;
    Status5efb3c status;                      // +d40
    Status5efb3c shared_status;               // +d80
    volatile unsigned int shared_code;        // +dc0
    volatile int xdc4;                        // +dc4
    int state;                                // +dc8
    unsigned char xdcc;                       // +dcc
    unsigned char xdcd;
    unsigned char xdce;                       // +dce
    unsigned char xdcf;
    volatile unsigned int command_index;      // +dd0
    unsigned int paddd4;
    Command5efb3c commands[2];                // +dd8
    Command5efb3c current;                    // +f78

    void stop_5f12b8();                                                                   // 0x71005f12b8
    void update(float volume, bool changed);

    void set_pan(Vec2u5efb3c p) {
        pan.x = p.x;
        pan.y = p.y;
    }
    void set_gain(Vec2u5efb3c g) {
        gain.x = g.x;
        gain.y = g.y;
    }
    void set_start(StartInfo5efb3c info) {
        play_flags = info.flags;
        start_mode = info.flags & 0xc000;
        start_position = info.position;
    }

    void pause_voices() {
        for (unsigned int i = 0; i < voice_count; i++) {
            nn::audio::SetVoicePlayState(&voices[i], nn::audio::VoiceType::PlayState_Paused);
        }
    }
    void start_voices() {
        for (unsigned int i = 0; i < voice_count; i++) {
            nn::audio::SetVoicePlayState(&voices[i], nn::audio::VoiceType::PlayState_Started);
        }
    }
    void mark_dirty() {
        main.dirty = 1;
        volume.dirty = 1;
        pitch.dirty = 1;
        for (unsigned int k = 0; k < voice_count / channels; k++) {
            groups[k].dirty = 1;
        }
    }
    void set_group_volume(unsigned int k) {
        if (channels > 0 && k < voice_count / channels) {
            float v = groups[k].value;
            nn::audio::VoiceType* p = &voices[static_cast<int>(channels * k)];
            for (int j = 0; j < channels; j++) {
                nn::audio::SetVoiceVolume(p + j, v);
            }
        }
    }
    void apply_effects() {
        unsigned int mask = current.effects.mask;
        if (mask & 1) {
            effect0 = current.effects.effects[0];
            if (!current.effects.effects[0].on) {
                memset(effect0_state, 0, sizeof(effect0_state));
            }
        }
        if (mask & 2) {
            effect1 = current.effects.effects[1];
            if (!current.effects.effects[1].on) {
                memset(effect1_state, 0, sizeof(effect1_state));
            }
        }
        current.effects.mask = 0;
    }
};

// 0x71005efb3c
void Voice5efb3c::update(float volume_scale, bool changed) {
    bool pitch_changed;
    if (!idle(state)) {
        int frame = owner->frame;
        if (main.fading()) {
            changed |= main.update_5f3d28(frame);
            if (!main.fading() && main.target == 0.0f) {
                stop_5f12b8();
            }
        }
        if (pause.fading()) {
            changed |= pause.update_5f3d28(frame);
            if (!pause.fading()) {
                int s;
                if (pause.target == 0.0f) {
                    pause_voices();
                    mark_dirty();
                    s = 4;
                } else {
                    s = 2;
                }
                state = s;
            }
        }
        changed |= volume.update_5f3d28(frame);
        pitch_changed = pitch.update_5f3d28(frame);
        for (unsigned int k = 0; k < voice_count / channels; k++) {
            if (groups[k].update_5f3d28(frame)) {
                set_group_volume(k);
            }
        }
    } else {
        pitch_changed = false;
    }

    bool applied;
    unsigned int index = __atomic_load_n(&command_index, __ATOMIC_ACQUIRE);
    Command5efb3c& source = commands[index];
    unsigned short flags = __atomic_load_n(&source.flags, __ATOMIC_ACQUIRE);
    if (flags == 0) {
        applied = false;
    } else {
        Command5efb3c local;
        local.flags = flags;
        memcpy(reinterpret_cast<char*>(&local) + 2, reinterpret_cast<char*>(&source) + 2, sizeof(local) - 2);
        __atomic_store_n(&source.flags, 0, __ATOMIC_RELEASE);
        __atomic_store_n(&source.groups.mask, 0, __ATOMIC_RELEASE);
        __atomic_store_n(&source.effects.mask, 0, __ATOMIC_RELEASE);
        source.handle = nullptr;
        if (local.flags & 1) {
            if (current.handle != nullptr) {
                release_handle_5f3c40(current.handle);
            }
            current.handle = nullptr;
            current = local;
            applied = true;
        } else {
            if (local.flags & 2) {
                current.flags |= 2;
                current.stop = local.stop;
                current.flags &= ~1;
                if (current.handle != nullptr) {
                    release_handle_5f3c40(current.handle);
                }
                current.handle = nullptr;
            }
            if (local.flags & 4) {
                current.flags |= 4;
                current.flags &= ~8;
                current.pause_time = local.pause_time;
            }
            if (local.flags & 8) {
                current.flags |= 8;
                current.flags &= ~4;
                current.pause_time = local.pause_time;
            }
            if (local.flags & 0x10) {
                current.flags |= 0x10;
                current.volume = local.volume;
            }
            if (local.flags & 0x20) {
                current.flags |= 0x20;
                current.pitch = local.pitch;
            }
            if (local.flags & 0x40) {
                current.flags |= 0x40;
                current.pan = local.pan;
            }
            if (local.flags & 0x80) {
                current.flags |= 0x80;
                current.x58 = local.x58;
            }
            if (local.flags & 0x100) {
                current.flags |= 0x100;
                current.x5c = local.x5c;
            }
            if (local.flags & 0x200) {
                current.flags |= 0x200;
                current.groups = local.groups;
            }
            if (local.flags & 0x400) {
                current.flags |= 0x400;
                current.effects = local.effects;
            }
            if (local.flags & 0x800) {
                current.flags |= 0x800;
                current.gain = local.gain;
            }
            applied = false;
        }
    }

    unsigned int code;
    if (current.flags & 1) {
        switch (state) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            stop_5f12b8();
            break;
        case 0:
            current.flags &= ~1;
            loader.set_5f813c(current.handle);
            if (stream.open_5f7b80(x48, x90, &loader, current.source)) {
                __atomic_store_n(&x42c, current.x20, __ATOMIC_RELEASE);
                state = 1;
                read_index = 0;
                pending = -1;
                queued_blocks = 0;
                xdcc = 0;
                xdce = current.x2c;
                main.start_5f3cc4(0.0f, 1.0f, current.fade_in_time, current.fade_in_curve);
                set_start(current.start);
            } else {
                loader.reset_5f8180();
            }
            if (current.handle != nullptr) {
                release_handle_5f3c40(current.handle);
            }
            current.handle = nullptr;
            break;
        }
        pitch_changed = false;
        changed = false;
        code = 3;
    } else {
        code = 0;
    }

    if (current.flags & 2) {
        current.flags &= ~2;
        if (state != 0 && state != 6) {
            unsigned int time = current.stop.time;
            if (time == 0) {
                stop_5f12b8();
                pitch_changed = false;
                changed = false;
            } else {
                bool fade = true;
                if (main.fading() && main.target == 0.0f) {
                    unsigned int rest = main.remaining();
                    switch (current.stop.mode & 3) {
                    case 1:
                        fade = rest <= time;
                        break;
                    case 2:
                        fade = rest >= time;
                        break;
                    case 3:
                        fade = false;
                        break;
                    }
                }
                if (fade) {
                    main.start_5f3cc4(main.value, 0.0f, time, current.stop.curve);
                    if (state != 1 && state != 4) {
                        main.clean();
                    }
                }
            }
        }
    }

    bool pan_changed;
    bool output_changed;
    if (!(current.flags & 1)) {
        int s = state;
        if (s == 1) {
            pan_changed = false;
            output_changed = false;
            goto starting;
        }
        if (voice_count != 0) {
            if (current.flags & 4) {
                unsigned int time = current.pause_time;
                switch (s) {
                case 3:
                    if (time != 0) {
                        break;
                    }
                case 2:
                case 5:
                    pause.start_5f3cc4(pause.value, 0.0f, time, 0);
                    if (time == 0) {
                        pause_voices();
                        mark_dirty();
                        s = 4;
                    } else {
                        pause.clean();
                        s = 3;
                    }
                    state = s;
                    break;
                }
            }
            if (current.flags & 8) {
                unsigned int time = current.pause_time;
                if (s == 3 || s == 4 || (s == 5 && time == 0)) {
                    start_voices();
                    main.clean();
                    volume.clean();
                    pitch.clean();
                    pause.start_5f3cc4(pause.value, 1.0f, time, 0);
                    if (time != 0) {
                        pause.clean();
                        s = 5;
                    } else {
                        s = 2;
                    }
                    pitch_changed = true;
                    changed = true;
                    state = s;
                }
            }
            if (current.flags & 0x10) {
                volume.fade_to(current.volume.target, current.volume.time);
                if (state != 4) {
                    volume.clean();
                }
                changed = true;
            }
            if (current.flags & 0x20) {
                pitch.fade_to(current.pitch.target, current.pitch.time);
                if (state != 4) {
                    pitch.clean();
                }
                pitch_changed = true;
            }
            bool pan_set = false;
            if (current.flags & 0x40) {
                set_pan(current.pan);
                pan_set = true;
            }
            bool xb28_set = false;
            if (current.flags & 0x80) {
                xb28 = current.x58;
                xb28_set = true;
            }
            if (current.flags & 0x100) {
                __atomic_store_n(&x42c, current.x5c, __ATOMIC_RELEASE);
            }
            if (current.flags & 0x200) {
                for (unsigned int k = 0; k < voice_count / channels; k++) {
                    if (current.groups.mask & (1 << k)) {
                        groups[k].fade_to(current.groups.volume[k], current.groups.time[k]);
                        if (state != 4) {
                            groups[k].clean();
                        }
                        set_group_volume(k);
                    }
                }
            }
            if (current.flags & 0x400) {
                apply_effects();
            }
            output_changed = xb28_set;
            pan_changed = pan_set;
            if (current.flags & 0x800) {
                set_gain(current.gain);
                pitch_changed = true;
                changed = true;
            }
        } else {
            pan_changed = false;
            output_changed = false;
        }
        current.flags &= 0xf203;
    } else {
        output_changed = false;
        pan_changed = false;
    }

    if (state == 1) {
    starting:
        if (stream.ready_5f7db4(0)) {
            if (stream.x70 == nullptr) {
                goto failed_close;
            }
            if (voice_count == 0) {
                read_index = 0;
                pending = -1;
                queued_blocks = 0;
                long position;
                int mode = start_mode;
                unsigned int at = start_position;
                status.played = 0;
                xd38 = 0;
                switch (mode) {
                case 0:
                    position = at;
                    break;
                case 0x4000:
                    position = static_cast<long>(info.rate) * at / 1000;
                    break;
                case 0x8000: {
                    float f = *reinterpret_cast<float*>(&at);
                    if (f < 0.0f || f >= 1.0f) {
                        goto failed;
                    }
                    position = static_cast<long>(f * static_cast<float>(info.total));
                    break;
                }
                default:
                    goto failed;
                }
                if (position >= info.total) {
                    goto failed;
                }
                if (position != 0) {
                    if (!stream.seek_5f7ce0(&position)) {
                        goto failed;
                    }
                    xd38 = static_cast<int>(position);
                }
                if (!create_voices_5ee2d8(voices, owner, 0, &info, xdce, xb38, owner->x4f8, (play_flags >> 1) & 1)) {
                    goto failed;
                }
                status.x38 = xd38;
                if (current.flags & 0x10) {
                    volume.fade_to(current.volume.target, current.volume.time);
                }
                if (current.flags & 0x20) {
                    pitch.fade_to(current.pitch.target, current.pitch.time);
                }
                if (current.flags & 0x40) {
                    set_pan(current.pan);
                } else {
                    set_pan(vec2(0.0f, -1.0f));
                }
                if (current.flags & 0x80) {
                    xb28 = current.x58;
                }
                if (current.flags & 0x100) {
                    __atomic_store_n(&x42c, current.x5c, __ATOMIC_RELEASE);
                }
                if (current.flags & 0x200) {
                    for (unsigned int k = 0; k < voice_count / channels; k++) {
                        if (current.groups.mask & (1 << k)) {
                            groups[k].fade_to(current.groups.volume[k], current.groups.time[k]);
                            set_group_volume(k);
                        }
                    }
                }
                if (current.flags & 0x400) {
                    apply_effects();
                }
                if (current.flags & 0x800) {
                    set_gain(current.gain);
                } else {
                    set_gain(vec2(1.0f, 1.0f));
                }
                status.channels = static_cast<unsigned char>(info.channels);
                status.rate = info.rate;
                status.total = static_cast<int>(info.total);
                int loop_start;
                int loop_end;
                if (info.loop_length == 0) {
                    status.looped = 0;
                    loop_start = 0;
                    loop_end = 0;
                } else {
                    status.looped = 0xff;
                    loop_start = info.loop_start;
                    loop_end = info.loop_start + info.loop_length - 1;
                }
                status.loop_start = loop_start;
                status.loop_end = loop_end;
                current.flags &= 0xf20f;
            }
            if (state == 1 && (xdcc || queued_blocks >= block_count)) {
                int s;
                if (!(current.flags & 4)) {
                    main.clean();
                    volume.clean();
                    pitch.clean();
                    pause.target = 1.0f;
                    pause.x18 = 1.0f;
                    pause.value = 1.0f;
                    pause.duration = 0.0f;
                    pause.x10 = 0.0f;
                    pause.dirty = 1;
                    for (unsigned int k = 0; k < voice_count / channels; k++) {
                        groups[k].clean();
                        set_group_volume(k);
                    }
                    start_voices();
                    pitch_changed = true;
                    s = 2;
                    changed = true;
                } else {
                    current.flags &= ~4;
                    pause_voices();
                    s = 4;
                    pause.x18 = 0.0f;
                    pause.target = 0.0f;
                    pause.value = 0.0f;
                    pause.duration = 0.0f;
                    pause.x10 = 0.0f;
                    pause.dirty = 1;
                }
                state = s;
                for (unsigned int k = 0; k < voice_count / channels; k++) {
                    set_group_volume(k);
                }
                output_changed = true;
                pan_changed = true;
            }
        }
    } else if (state == 6) {
        if (mixer.idle_5eb330()) {
            if (voice_count != 0) {
                Owner5efb3c* o = owner;
                mixer.release_5ecfcc(o, &submix);
                nn::audio::AudioRendererConfig* config = &o->config;
                for (unsigned long i = 0; i < voice_count; i++) {
                    nn::audio::ReleaseVoiceSlot(config, &voices[i]);
                }
                nn::audio::ReleaseSubMix(config, &submix);
                voice_count = 0;
            }
            if (stream.ready_5f7db4(0)) {
                loader.reset_5f8180();
                state = 0;
                goto submit;
            }
        }
    }
    goto active;

failed:
    current.flags &= 0xf20f;
failed_close:
    stream.close_5f7c98();
    state = 6;
    goto submit;

active:
    if (!idle(state)) {
        if (changed & 1) {
            nn::audio::SetSubMixVolume(&submix, gain.x * (main.value * pause.value * volume.value * volume_scale));
        }
        if (pitch_changed) {
            float ratio = exp2f(pitch.value) * gain.y;
            for (unsigned int i = 0; i < voice_count; i++) {
                nn::audio::SetVoicePitch(&voices[i], ratio);
            }
        }
        if (pan_changed && info.channels == 1 && !(play_flags & 2)) {
            Pan5efb3c p;
            calc_pan_5e96b4(pan.x, pan.y, 0.0f, &p);
            apply_pan_5f13f0(voices, p.mix);
            update_voices_5ee650(voices);
        } else if (output_changed) {
            update_voices_5ee650(voices);
        }
    }

submit:
    if (pending >= 0 && stream.ready_5f7db4(0)) {
        Block5efb3c b = block;
        if (b.count == 0) {
            xdcc = 1;
        } else {
            char* dest = buffer_base + static_cast<unsigned int>(pending * block_size);
            nn::audio::CopyMemoryPoolData(&pool, dest, b.data, b.stride * b.count);
            for (unsigned long i = 0; i < static_cast<unsigned int>(b.count); i++) {
                WaveBuffer5efb3c* wb = &buffers[static_cast<unsigned int>(block_count * i)] + pending;
                wb->buffer = dest + b.stride * static_cast<unsigned int>(i);
                wb->size = b.size;
                wb->start = b.start;
                wb->end = b.end;
                wb->loop = false;
                wb->end_of_stream = false;
                wb->context = b.contexts[i];
                wb->x30 = b.x14;
                wb->in_use = true;
                wb->context_size = wb->context != nullptr ? b.context_size : 0;
                if (voice_count > i &&
                    nn::audio::AppendWaveBuffer(&voices[i], reinterpret_cast<nn::audio::WaveBuffer*>(wb))) {
                    queued[i]++;
                }
            }
            queued_blocks++;
        }
        pending = -1;
    }

    if (voice_count != 0) {
        while (queued_blocks > 0) {
            for (unsigned long i = 0; static_cast<int>(i) < static_cast<int>(voice_count); i++) {
                while (voice_count > i) {
                    WaveBuffer5efb3c* wb = const_cast<WaveBuffer5efb3c*>(reinterpret_cast<const WaveBuffer5efb3c*>(
                        nn::audio::GetReleasedWaveBuffer(&voices[i])));
                    if (wb == nullptr) {
                        break;
                    }
                    queued[i]--;
                    wb->in_use = false;
                }
            }
            bool busy = false;
            for (long j = 0; j < info.channels; j++) {
                if ((buffers + read_index)[j * block_count].in_use) {
                    busy = true;
                    break;
                }
            }
            if (busy) {
                break;
            }
            WaveBuffer5efb3c* wb = &buffers[read_index];
            int next = read_index + 1 == block_count ? 0 : read_index + 1;
            status.played += static_cast<long>(wb->end) - static_cast<long>(wb->start);
            xd38 = wb->x30;
            queued_blocks--;
            read_index = next;
        }
        if (state == 6) {
            goto status_update;
        }
        if (pending < 0 && !xdcc && queued_blocks < block_count) {
            int idx = (read_index + queued_blocks) % block_count;
            stream.read_5f7d3c(read_base + static_cast<unsigned int>(block_size * idx), block_size);
            pending = idx;
        }
    }
    if (state != 0 && state != 6 && xdcc && queued_blocks == 0 && (voice_count == 0 || queued[0] <= 0)) {
        stop_5f12b8();
    }

status_update:
    unsigned int value = x432;
    if (value != 0) {
        value = __atomic_load_n(&x42c, __ATOMIC_ACQUIRE);
    }
    int s = state;
    if (code == 0) {
        switch (s) {
        case 1:
            code = 3;
            break;
        case 2:
            code = 1;
            break;
        case 3:
            code = 0x1001;
            break;
        case 4:
            code = 9;
            break;
        case 5:
            code = 0x2001;
            break;
        case 6:
            code = 1;
            break;
        default:
            code = 0;
            break;
        }
        if (s >= 1 && s <= 6) {
            if (main.fading()) {
                if (main.target == 0.0f) {
                    code |= 0x200;
                } else {
                    code |= 0x100;
                }
            }
            if (volume.fading()) {
                code |= 0x400;
            }
            if (pitch.fading()) {
                code |= 0x800;
            }
            if (value != 0) {
                code |= 4;
            }
        }
    }
    status.code = code;
    status.volume = volume_scale;
    status.fader_volume = volume.value;
    status.fader_pitch = pitch.value;
    status.x10 = value;
    long samples;
    if (idle(s)) {
        samples = 0;
        status.x14 = 0.0f;
        status.position = 0.0f;
        status.x3c = 0.0f;
    } else {
        samples = voice_count != 0 ? nn::audio::GetVoicePlayedSampleCount(&voices[0]) : 0;
        float position = static_cast<float>(static_cast<unsigned int>(static_cast<int>(samples) -
                                                                       static_cast<int>(status.played) + xd38)) /
                         static_cast<float>(static_cast<unsigned int>(status.total));
        status.x14 = 1.0f;
        status.position = position;
        if (play_flags & 4) {
            status.x3c = meter.level_5ec694(status.channels);
        }
    }
    if (nn::os::TryAcquireWriteLock(&lock)) {
        shared_status = status;
        shared_status.played = samples;
        nn::os::ReleaseWriteLock(&lock);
    }
    __atomic_store_n(&shared_code, code, __ATOMIC_RELEASE);
    if (applied) {
        __atomic_store_n(&xdc4, 0, __ATOMIC_RELEASE);
    }
    if (!idle(state)) {
        mixer.update_5eb388();
    }
}
