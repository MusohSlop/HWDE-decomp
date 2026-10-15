// Type nodes: each class's node points at its base class's node, built on first use through a
// guarded function-local static. Used by misc/type_chains.cpp and the type tests.
#pragma once

struct TypeNode {
    TypeNode(const TypeNode* parent);

    const TypeNode* parent;   // +00
};

inline TypeNode::TypeNode(const TypeNode* parent) : parent(parent) {}

template <class T>
struct TypeOf {
    static const TypeNode* get();
};

template <class T>
const TypeNode* TypeOf<T>::get() {
    static TypeNode node(TypeOf<typename T::Base>::get());
    return &node;
}

// True when type is T or derives from it.
template <class T>
inline bool is_type(const TypeNode* type) {
    const TypeNode* wanted = TypeOf<T>::get();
    for (; type; type = type->parent) {
        if (type == wanted)
            return true;
    }
    return false;
}

struct ActorRoot {};
struct ActorMid { typedef ActorRoot Base; };
struct ActorSide { typedef ActorRoot Base; };
struct ActorScaleStop { typedef ActorRoot Base; };
struct Actor1e47a4 { typedef ActorMid Base; };
struct Actor1e4874 { typedef ActorSide Base; };
struct Actor1e4a1c { typedef ActorMid Base; };
struct TaskRoot {};
struct TaskMid { typedef TaskRoot Base; };
struct Task5d08f8 { typedef TaskMid Base; };
struct SystemRoot {};
struct SystemMid { typedef SystemRoot Base; };
struct System5fcd4c { typedef SystemMid Base; };

template <>
inline const TypeNode* TypeOf<ActorRoot>::get() {
    static TypeNode node(nullptr);
    return &node;
}

template <>
inline const TypeNode* TypeOf<TaskRoot>::get() {
    static TypeNode node(nullptr);
    return &node;
}

template <>
inline const TypeNode* TypeOf<SystemRoot>::get() {
    static TypeNode node(nullptr);
    return &node;
}