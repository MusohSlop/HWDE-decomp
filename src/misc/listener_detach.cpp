// Listener detach (0x7100522a18-0x710052374c): each object notifies itself and the global hub, then,
// if it is registered, removes its id from the registry under the registry's mutex: through the
// registry's handler when one is set, otherwise from the registry's own list. Found by
// tools/family_scan.py --immediates. Names are descriptive placeholders. Status: matching/README.md.

namespace nn {
namespace os {
struct MutexType {
    unsigned char storage[0x20];
};
void LockMutex(MutexType* mutex);
void UnlockMutex(MutexType* mutex);
}  // namespace os
}  // namespace nn

struct Listener;

struct ListenerHub {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void detach(Listener* listener);
};

// Reached through the GOT slot at 0x7100c2d010.
extern ListenerHub* gHub_c2d010;

struct IdHandler {
    virtual void slot0();
    virtual void remove(long id);
};

struct IdNode {
    long id;                  // +00
    unsigned char pad8[8];
    IdNode* next;             // +10
};

struct IdList {
    unsigned char pad[0x20];
    IdNode* head;             // +20
};
void remove_node_520ac0(IdList* list, IdNode* node);                       // 0x7100520ac0

struct Registry {
    nn::os::MutexType mutex;  // +00
    unsigned char pad20[0x120];
    IdList ids;               // +140
    unsigned char pad168[0x30];
    IdHandler* handler;       // +198
};

struct Listener {
    virtual void notify();
};
struct Listener522a18 : Listener {
    unsigned char pad8[0x630];
    long id;                  // +638
    unsigned char pad640[0x8];
    Registry* registry;       // +648
};

// 0x7100522a18
void detach_522a18(Listener522a18* listener) {
    listener->notify();
    gHub_c2d010->detach(listener);
    long id = listener->id;
    if (id == -1)
        return;
    Registry* registry = listener->registry;
    nn::os::LockMutex(&registry->mutex);
    if (registry->handler) {
        registry->handler->remove(id);
    } else {
        for (IdNode* node = registry->ids.head; node; node = node->next) {
            if (node->id == id) {
                remove_node_520ac0(&registry->ids, node);
                break;
            }
        }
    }
    nn::os::UnlockMutex(&registry->mutex);
}
struct Listener522ac8 : Listener {
    unsigned char pad8[0x48];
    long id;                  // +50
    unsigned char pad58[0x8];
    Registry* registry;       // +60
};

// 0x7100522ac8
void detach_522ac8(Listener522ac8* listener) {
    listener->notify();
    gHub_c2d010->detach(listener);
    long id = listener->id;
    if (id == -1)
        return;
    Registry* registry = listener->registry;
    nn::os::LockMutex(&registry->mutex);
    if (registry->handler) {
        registry->handler->remove(id);
    } else {
        for (IdNode* node = registry->ids.head; node; node = node->next) {
            if (node->id == id) {
                remove_node_520ac0(&registry->ids, node);
                break;
            }
        }
    }
    nn::os::UnlockMutex(&registry->mutex);
}
struct Listener52374c : Listener {
    unsigned char pad8[0x58];
    long id;                  // +60
    unsigned char pad68[0x0];
    Registry* registry;       // +68
};

// 0x710052374c
void detach_52374c(Listener52374c* listener) {
    listener->notify();
    gHub_c2d010->detach(listener);
    long id = listener->id;
    if (id == -1)
        return;
    Registry* registry = listener->registry;
    nn::os::LockMutex(&registry->mutex);
    if (registry->handler) {
        registry->handler->remove(id);
    } else {
        for (IdNode* node = registry->ids.head; node; node = node->next) {
            if (node->id == id) {
                remove_node_520ac0(&registry->ids, node);
                break;
            }
        }
    }
    nn::os::UnlockMutex(&registry->mutex);
}
