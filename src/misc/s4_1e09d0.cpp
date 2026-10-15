// The map of a std::deque of 0x71001e0580's element type (fourth session, template families 1e09d0 and 1e0bb0): libc++'s
// __split_buffer<T*>::push_back and push_front, each in its const& and && forms (identical code for a pointer):
// push_back 0x71001e09d0 (&&) and 0x71001e0d90 (const&), push_front 0x71001e0bb0 (&&) and 0x71001e0f70 (const&). Written
// after libc++: std::move/move_backward as memmove, the capacity through max<size_type> taking references,
// __builtin_operator_new/delete, and the allocator's length check reporting through a length_error, fprintf and abort
// (exceptions are off). Names are descriptive placeholders.

#include "misc/s4_libcxx.h"

struct Elem1e0580;
template void SplitBuffer<Elem1e0580*>::push_back(Elem1e0580* const&);
template void SplitBuffer<Elem1e0580*>::push_back(Elem1e0580*&&);
template void SplitBuffer<Elem1e0580*>::push_front(Elem1e0580* const&);
template void SplitBuffer<Elem1e0580*>::push_front(Elem1e0580*&&);
