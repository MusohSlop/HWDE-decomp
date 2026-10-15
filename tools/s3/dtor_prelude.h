// Prelude of dtor2class.py's output: the layout handle as destructors inline it (the vtable store, then release()
// through the vtable with the heap of the owner at GOT 0x7100c21db0; its vtable is at GOT 0x7100c22f00).
struct HandleHeapOwner {
    unsigned char pad0[0x2af8];
    unsigned char* heap;            // +2af8
};
extern HandleHeapOwner* gHandleHeapOwner;

inline void* handle_root_heap() { return gHandleHeapOwner ? gHandleHeapOwner->heap + 0x10 : nullptr; }

struct DtorHandleState {
    long id;
    short a;
    short b;
};

class DtorHandle : public DtorHandleState {
public:
    virtual ~DtorHandle() { release(handle_root_heap()); }
    virtual void v10();
    virtual void release(void* root);
};
