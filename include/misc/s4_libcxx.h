// libc++ container code written out for pointer elements (fourth session): the deque map's __split_buffer and
// std::vector's growth path, after the libc++ that the game links (exceptions off: a failed length check prints the
// length_error's message and aborts). Units that include it instantiate the templates they match. Names other than the
// std:: ones are descriptive placeholders.
#pragma once

typedef unsigned long size_t;
typedef long ptrdiff_t;

void* operator new(size_t size);                                            // 0x71003ccb94
void operator delete(void* p) noexcept;                                     // 0x71003ccc84
extern "C" void* memmove(void* dst, const void* src, size_t n);             // 0x7100600940 (import)
extern "C" void* memcpy(void* dst, const void* src, size_t n);              // 0x7100600870 (import)
extern "C" int fprintf(void* stream, const char* format, ...);              // 0x7100600a70 (import)
extern "C" void abort() __attribute__((noreturn));                          // 0x7100600a80 (import)
extern "C" void* stderr;

namespace std {
class logic_error {
public:
    explicit logic_error(const char* msg);                                  // 0x7100600a50 (import)
    virtual ~logic_error() noexcept;
    virtual const char* what() const noexcept;                              // 0x7100600a60 (import)

private:
    void* imp_;
};
class length_error : public logic_error {
public:
    __attribute__((visibility("hidden"), always_inline)) explicit length_error(const char* msg) : logic_error(msg) {}
    virtual ~length_error() noexcept;
};
}

__attribute__((noreturn, always_inline)) static inline void throw_length_error(const char* msg) {
    std::length_error e(msg);
    fprintf(stderr, "%s\n", e.what());
    abort();
}

template <class U>
static inline const U& max_of(const U& a, const U& b) { return a < b ? b : a; }

template <class T>
__attribute__((always_inline)) static inline T* allocate_n(size_t n) {
    if (n > (~0UL >> 3))
        throw_length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
    return static_cast<T*>(__builtin_operator_new(n * sizeof(T)));
}

template <class T>
struct SplitBuffer {
    T* first_;
    T* begin_;
    T* end_;
    T* end_cap_;

    SplitBuffer(size_t cap, size_t start) {
        first_ = cap != 0 ? allocate_n<T>(cap) : 0;
        begin_ = end_ = first_ + start;
        end_cap_ = first_ + cap;
    }
    ~SplitBuffer() {
        if (first_) __builtin_operator_delete(first_);
    }
    SplitBuffer() {}

    void construct_at_end(T* first, T* last) {
        for (; first != last; ++first) {
            *end_ = *first;
            ++end_;
        }
    }

    void push_back(const T& x);
    void push_back(T&& x);
    void push_front(const T& x);
    void push_front(T&& x);
};

template <class T>
static inline void swap_ptr(T*& a, T*& b) {
    T* t = a;
    a = b;
    b = t;
}

template <class T>
void SplitBuffer<T>::push_back(const T& x) {
    if (end_ == end_cap_) {
        if (begin_ > first_) {
            ptrdiff_t d = begin_ - first_;
            d = (d + 1) / 2;
            T* result = begin_ - d;
            size_t n = end_ - begin_;
            if (n > 0) memmove(result, begin_, n * sizeof(T));
            end_ = result + n;
            begin_ -= d;
        } else {
            size_t c = max_of<size_t>(2 * static_cast<size_t>(end_cap_ - first_), 1);
            SplitBuffer<T> t(c, c / 4);
            t.construct_at_end(begin_, end_);
            swap_ptr(first_, t.first_);
            swap_ptr(begin_, t.begin_);
            swap_ptr(end_, t.end_);
            swap_ptr(end_cap_, t.end_cap_);
        }
    }
    *end_ = x;
    ++end_;
}

template <class T>
void SplitBuffer<T>::push_back(T&& x) {
    if (end_ == end_cap_) {
        if (begin_ > first_) {
            ptrdiff_t d = begin_ - first_;
            d = (d + 1) / 2;
            T* result = begin_ - d;
            size_t n = end_ - begin_;
            if (n > 0) memmove(result, begin_, n * sizeof(T));
            end_ = result + n;
            begin_ -= d;
        } else {
            size_t c = max_of<size_t>(2 * static_cast<size_t>(end_cap_ - first_), 1);
            SplitBuffer<T> t(c, c / 4);
            t.construct_at_end(begin_, end_);
            swap_ptr(first_, t.first_);
            swap_ptr(begin_, t.begin_);
            swap_ptr(end_, t.end_);
            swap_ptr(end_cap_, t.end_cap_);
        }
    }
    *end_ = x;
    ++end_;
}


template <class T>
void SplitBuffer<T>::push_front(const T& x) {
    if (begin_ == first_) {
        if (end_ < end_cap_) {
            ptrdiff_t d = end_cap_ - end_;
            d = (d + 1) / 2;
            T* result = end_ + d;
            size_t n = end_ - begin_;
            if (n > 0) {
                result -= n;
                memmove(result, begin_, n * sizeof(T));
            }
            begin_ = result;
            end_ += d;
        } else {
            size_t c = max_of<size_t>(2 * static_cast<size_t>(end_cap_ - first_), 1);
            SplitBuffer<T> t(c, (c + 3) / 4);
            t.construct_at_end(begin_, end_);
            swap_ptr(first_, t.first_);
            swap_ptr(begin_, t.begin_);
            swap_ptr(end_, t.end_);
            swap_ptr(end_cap_, t.end_cap_);
        }
    }
    *(begin_ - 1) = x;
    --begin_;
}

template <class T>
void SplitBuffer<T>::push_front(T&& x) {
    if (begin_ == first_) {
        if (end_ < end_cap_) {
            ptrdiff_t d = end_cap_ - end_;
            d = (d + 1) / 2;
            T* result = end_ + d;
            size_t n = end_ - begin_;
            if (n > 0) {
                result -= n;
                memmove(result, begin_, n * sizeof(T));
            }
            begin_ = result;
            end_ += d;
        } else {
            size_t c = max_of<size_t>(2 * static_cast<size_t>(end_cap_ - first_), 1);
            SplitBuffer<T> t(c, (c + 3) / 4);
            t.construct_at_end(begin_, end_);
            swap_ptr(first_, t.first_);
            swap_ptr(begin_, t.begin_);
            swap_ptr(end_, t.end_);
            swap_ptr(end_cap_, t.end_cap_);
        }
    }
    *(begin_ - 1) = x;
    --begin_;
}

namespace std {
inline namespace __1 {
template <bool B>
class __vector_base_common {
protected:
    void __throw_length_error() const;                                      // 0x7100600aa0 (import)
};
}
}

// std::vector<T*>'s data and its growth path (__push_back_slow_path), after libc++.
template <class T>
struct Vector : protected std::__vector_base_common<true> {
    T* begin_;
    T* end_;
    T* end_cap_;

    size_t size() const { return static_cast<size_t>(end_ - begin_); }
    size_t capacity() const { return static_cast<size_t>(end_cap_ - begin_); }
    size_t max_size() const { return ~0UL >> 3; }

    size_t recommend(size_t new_size) const {
        const size_t ms = max_size();
        if (new_size > ms) this->__throw_length_error();
        const size_t cap = capacity();
        if (cap >= ms / 2) return ms;
        return max_of<size_t>(2 * cap, new_size);
    }

    void swap_out(SplitBuffer<T>& v) {
        ptrdiff_t n = end_ - begin_;
        v.begin_ -= n;
        if (n > 0) memcpy(v.begin_, begin_, n * sizeof(T));
        swap_ptr(begin_, v.begin_);
        swap_ptr(end_, v.end_);
        swap_ptr(end_cap_, v.end_cap_);
        v.first_ = v.begin_;
    }

    void push_back_slow_path(const T& x);
    void push_back_slow_path(T&& x);
};

template <class T>
void Vector<T>::push_back_slow_path(const T& x) {
    SplitBuffer<T> v(recommend(size() + 1), size());
    *v.end_ = x;
    v.end_++;
    swap_out(v);
}

template <class T>
void Vector<T>::push_back_slow_path(T&& x) {
    SplitBuffer<T> v(recommend(size() + 1), size());
    *v.end_ = x;
    v.end_++;
    swap_out(v);
}

// The same with an allocator A (static allocate(n), deallocate(p, n), max_size()), as libc++ builds it for an
// allocator other than std::allocator: the old elements move one at a time (__construct_backward), not with memcpy.
template <class T, class A>
struct SplitBufferA {
    T* first_;
    T* begin_;
    T* end_;
    T* end_cap_;

    SplitBufferA(size_t cap, size_t start) {
        first_ = cap != 0 ? A::allocate(cap) : 0;
        begin_ = end_ = first_ + start;
        end_cap_ = first_ + cap;
    }
    ~SplitBufferA() {
        if (first_) A::deallocate(first_, static_cast<size_t>(end_cap_ - first_));
    }
};

template <class T, class A>
struct VectorA : protected std::__vector_base_common<true> {
    T* begin_;
    T* end_;
    T* end_cap_;

    size_t size() const { return static_cast<size_t>(end_ - begin_); }
    size_t capacity() const { return static_cast<size_t>(end_cap_ - begin_); }
    size_t max_size() const {
        const size_t a = A::max_size();
        const size_t b = ~0UL >> 1;
        return b < a ? b : a;
    }

    size_t recommend(size_t new_size) const {
        const size_t ms = max_size();
        if (new_size > ms) this->__throw_length_error();
        const size_t cap = capacity();
        if (cap >= ms / 2) return ms;
        return max_of<size_t>(2 * cap, new_size);
    }

    void swap_out(SplitBufferA<T, A>& v) {
        T* b = begin_;
        T* e = end_;
        while (e != b) {
            *(v.begin_ - 1) = *--e;
            --v.begin_;
        }
        swap_ptr(begin_, v.begin_);
        swap_ptr(end_, v.end_);
        swap_ptr(end_cap_, v.end_cap_);
        v.first_ = v.begin_;
    }

    void push_back_slow_path(const T& x);
};

template <class T, class A>
void VectorA<T, A>::push_back_slow_path(const T& x) {
    SplitBufferA<T, A> v(recommend(size() + 1), size());
    *v.end_ = x;
    v.end_++;
    swap_out(v);
}
