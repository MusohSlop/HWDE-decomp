// PARKED 6deac (212 B), 2 off: needs the Registry of src/misc/s4_4b76c.cpp (with its virtual release slots). Our
// arms share one hoisted e->target load (ldr x1 before the mode test); the original loads it in each arm after the
// vtable slot. Tried: if/else both ways, ?:, a switch, locals per arm, a Registry* for the calls.
struct RegistryHostBase {
    virtual void h00();
    unsigned char pad8[0x138];
};

// The registry is a base at +140, so its release calls stay virtual.
struct RegistryHost6deac : RegistryHostBase, Registry {
    void remove(int id);
};

// 0x710006deac
void RegistryHost6deac::remove(int id) {
    RegistryEntry* e = entry(id);
    if (!e) return;
    if (e->mode >= 0)
        release(e->target);
    else
        release_id(e->target, e->id);
    e->target = 0;
    e->id = -1;
    e->id2 = -1;
    e->mode = 0;
    used--;
}
