#ifndef _C3TL_MEMORY_H_
#define _C3TL_MEMORY_H_

#include <stddef.h>

namespace c3
{

template <class T>
class allocator {
public:
    typedef T           value_type;
    typedef T*          pointer;
    typedef const T*    const_pointer;
    typedef T&          reference;
    typedef const T&    const_reference;
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;


    pointer allocate(size_type n);
    void deallocate(pointer p, size_type n);
    pointer address(reference x) { return (pointer)&x; }
    const_pointer const_address(const_reference x) { return (const_pointer)&x; }
    void construct(pointer p, const_reference value);
    void destroy(pointer p);
};

template <class T>
inline T* allocator<T>::allocate(size_t n) {
    T* tmp = (T*)(::operator new(n * sizeof(T)));
    if (tmp == 0) {
        return nullptr;
    }
    return tmp;
}

template <class T>
inline void allocator<T>::deallocate(T* p, size_t n) {
    delete[] p;
}

template <class T>
inline void allocator<T>::construct(T* p, const T& val) {
    new(p) T(val);
}

template <class T>
inline void allocator<T>::destroy(T* p) {
    p -> ~T();
}


} // namespace c3

#endif // _C3TL_MEMORY_H_