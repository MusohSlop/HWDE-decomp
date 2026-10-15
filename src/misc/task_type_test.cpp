// Task type test (0x71001f7c94): returns the object when it is a Task5d08f8 or derives from it.
// Names are descriptive placeholders. Status: matching/README.md.

#include "misc/type_node.h"

struct TaskObject {
    virtual const TypeNode* type();
};

// 0x71001f7c94
TaskObject* as_task_1f7c94(TaskObject* object) {
    const TypeNode* wanted = TypeOf<Task5d08f8>::get();
    if (!object)
        return nullptr;
    for (const TypeNode* type = object->type(); type; type = type->parent) {
        if (type == wanted)
            return object;
    }
    return nullptr;
}
