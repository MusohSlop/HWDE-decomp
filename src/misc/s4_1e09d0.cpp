// The map of a std::deque of 0x71001e0580's element type (fourth session, template families 1e09d0 and 1e0bb0): libc++'s
// __split_buffer<T*>::push_back and push_front, each in its const& and && forms (identical code for a pointer):
// push_back 0x71001e09d0 (&&) and 0x71001e0d90 (const&), push_front 0x71001e0bb0 (&&) and 0x71001e0f70 (const&). Written
// after libc++: std::move/move_backward as memmove, the capacity through max<size_type> taking references,
// __builtin_operator_new/delete, and the allocator's length check reporting through a length_error, fprintf and abort
// (exceptions are off). Names are descriptive placeholders.

typedef unsigned long size_t;
typedef long ptrdiff_t;

void* operator new(size_t size);                                            // 0x71003ccb94
void operator delete(void* p) noexcept;                                     // 0x71003ccc84
extern "C" void* memmove(void* dst, const void* src, size_t n);             // 0x7100600940 (import)
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

__attribute__((noreturn)) static inline void throw_length_error(const char* msg) {
    std::length_error e(msg);
    fprintf(stderr, "%s\n", e.what());
    abort();
}

template <class U>
static inline const U& max_of(const U& a, const U& b) { return a < b ? b : a; }

template <class T>
static inline T* allocate_n(size_t n) {
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
struct Elem1e0580;
template void SplitBuffer<Elem1e0580*>::push_back(Elem1e0580* const&);
template void SplitBuffer<Elem1e0580*>::push_back(Elem1e0580*&&);
template void SplitBuffer<Elem1e0580*>::push_front(Elem1e0580* const&);
template void SplitBuffer<Elem1e0580*>::push_front(Elem1e0580*&&);
