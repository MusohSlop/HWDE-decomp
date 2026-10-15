// std::vector growth paths of two element types (fourth session, template family 2cba00): libc++'s
// vector<T*>::__push_back_slow_path (348 bytes) from misc/s4_libcxx.h, for 0x71002cba00 and 0x710039721c. Names other
// than the std:: ones are descriptive placeholders.

#include "misc/s4_libcxx.h"

struct Elem2cba00;
struct Elem39721c;
template void Vector<Elem2cba00*>::push_back_slow_path(Elem2cba00* const&);
template void Vector<Elem39721c*>::push_back_slow_path(Elem39721c* const&);
