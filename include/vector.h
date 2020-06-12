//
// Created on 2020 - 06 - 05
// Written by: TSH
//

#ifndef _C3TL_VECTOR_H_
#define _C3TL_VECTOR_H_

#include <cstring>
#include "memory.h"
#include "iterator.h"
#include <initializer_list>
#include "utility.h"
#include "algorithm.h"

namespace c3
{

template< class T, class Allocator = c3::allocator<T> >
class vector {
public:
  typedef c3::allocator<T>                      allocator_type;
  typedef c3::allocator<T>                      data_allocator;

  typedef typename allocator_type::value_type      value_type;
  typedef typename allocator_type::pointer         pointer;
  typedef typename allocator_type::const_pointer   const_pointer;
  typedef typename allocator_type::reference       reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::size_type       size_type;
  typedef typename allocator_type::difference_type difference_type;

  typedef value_type*                              iterator;
  typedef const value_type*                        const_iterator;
  typedef c3::reverse_iterator<iterator>           reverse_iterator;
  typedef c3::reverse_iterator<const_iterator>     const_reverse_iterator;    

public:
    // 构造空的 vector
    vector();
    // 构造空的 vector，使用 alloc 作为内存分配器
    explicit vector( const Allocator& alloc );
    // 复制构造函数
    vector( const vector& other );
    // 复制构造函数，使用 alloc 作为内存分配器
    vector( const vector& other, const Allocator& alloc );
    // 构造拥有个 count 默认 T 实例的容器。不进行复制。使用 alloc 作为内存分配器
    explicit vector( size_type count, const Allocator& alloc = Allocator() );
    // 构造拥有 count 个 value 的元素的容器。使用 alloc 作为内存分配器
    vector( size_type count, const_reference value, const Allocator& alloc = Allocator());

    // 移动构造函数
    vector( vector&& other );
    // 移动构造函数，使用 alloc 作为内存分配器
    vector( vector&& other, const Allocator& alloc );

    // 初始化列表构造函数
    vector( std::initializer_list<T> init, const Allocator& alloc = Allocator() );

    // 销毁 vector 。调用每个元素的析构函数，然后解分配所用的存储。注意，若元素是指针，则不销毁所指向的对象。 
    ~vector();

    // 复制赋值运算符。以 other 的副本替换内容。
    vector& operator=( const vector& other );
    // 移动赋值运算符。
    vector& operator=( vector&& other );
    // 用初始化列表赋值
    vector& operator=( std::initializer_list<T> ilist );

    // 以 count 个 value 替换 vector 的内容。
    void assign( size_type count, const_reference value );

    // 返回与容器关联的分配器。 
    Allocator get_allocator() const;

    // 返回位于指定位置 pos 的元素的引用，有边界检查。 
    reference at( size_type pos );
    reference operator[]( size_type pos );
    const_reference at( size_type pos ) const;
    const_reference operator[]( size_type pos ) const;

    // 返回容器首元素的引用。在空容器上对 front 的调用是未定义的。 
    reference front();
    const_reference front() const;

    // 返回容器末元素的引用。在空容器上对 back 的调用是未定义的。 
    reference back();
    const_reference back() const;

    // 返回指向作为元素存储工作的底层数组的指针。指针满足范围 [data(); data() + size()) 始终是合法范围，即使容器为空（该情况下 data() 不可解引用）。
    pointer data() noexcept;
    const_pointer data() const noexcept;

    // 返回可变或常迭代器，取决于 *this 的常性。
    iterator begin();
    const_iterator begin() const;

    // 返回指向容器末元素的后一个元素的迭代器。试图访问它导致未定义行为。 
    iterator end();
    const_iterator end() const;

    // 返回指向逆转容器首元素的逆向迭代器。它对应非逆向的末元素。 
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;

    // 返回指向逆转容器首字符后一个元素的逆向迭代器。它对应非逆向首元素的前一个元素。 
    reverse_iterator rend();
    const_reverse_iterator rend() const;


    // 若容器为空则返回 true ，否则返回 false 。
    bool empty() const;

    // 返回容器的长度。
    size_type size() const;

    // 返回由于操作系统或库实现限制所能保有的最大容器长度
    size_type max_size() const;

    // 返回当前已为容器分配的保留空间的元素数。（不要与size和length混淆）
    size_type capacity() const;

    // 重新分配容器的保留空间。若 new_cap 大于当前 capacity()，则分配新存储，并令 capacity() 大于或等于 new_cap。若 new_cap 小于或等于当前 capacity()，则无效果。 
    void reserve( size_type new_cap = 0 );

    // 请求移除未使用的保留空间。（非强制） 
    void shrink_to_fit();

    // 清空容器。
    void clear();

    // 在 pos 前插入 value 。
    iterator insert( const_iterator pos, const_reference value );
    // （可选）iterator insert( const_iterator pos, reference& value );
    // 在 pos 前插入 count 个 value 。
    iterator insert( const_iterator pos, size_type count, const_reference value );

    // 移除位于 pos 的元素。
    iterator erase( const_iterator pos );
    // 移除范围 [first; last) 中的元素。
    iterator erase( const_iterator first, const_iterator last );

    // 后附给定元素 value 到容器尾。 
    void push_back( const_reference value );
    // 使用移动语义。 
    void push_back( reference& value );

    // 移除容器的最末元素。在空容器上调用 pop_back 是未定义的。 
    void pop_back();

    // 若当前大小大于 count ，则减小容器为其首 count 个元素。若当前大小小于 count， 则后附额外的默认插入的元素。
    void resize( size_type count );// 若当前大小大于 count ，则减小容器为其首 count 个元素。若当前大小小于 count， 则后附额外的 value 的副本。
    void resize( size_type count, const_reference value );

    // 将内容与 other 的交换。不在单个元素上调用任何移动、复制或交换操作。 
    void swap( vector& other );

    // 检查 lhs 与 rhs 的内容是否相等，即它们是否拥有相同数量的元素且 lhs 中每个元素与 rhs 的同位置元素比较相等。
    template< class _T, class _Alloc >
    friend bool operator==( const c3::vector<_T,_Alloc>& lhs, const c3::vector<_T,_Alloc>& rhs );
    template< class _T, class _Alloc >
    friend bool operator!=( const c3::vector<_T,_Alloc>& lhs, const c3::vector<_T,_Alloc>& rhs );

    // 按字典序比较 lhs 与 rhs 的内容。
    template< class _T, class _Alloc >
    friend bool operator<( const c3::vector<_T,_Alloc>& lhs, const c3::vector<_T,_Alloc>& rhs );
    template< class _T, class _Alloc >
    friend bool operator<=( const c3::vector<_T,_Alloc>& lhs, const c3::vector<_T,_Alloc>& rhs );
    template< class _T, class _Alloc >
    friend bool operator>( const c3::vector<_T,_Alloc>& lhs, const c3::vector<_T,_Alloc>& rhs );
    template< class _T, class _Alloc >
    friend bool operator>=( const c3::vector<_T,_Alloc>& lhs, const c3::vector<_T,_Alloc>& rhs );

protected:
    Allocator _alloc;
    pointer _data;
    size_type _size;
    size_type _capacity;

    iterator _first;
    iterator _last;
    iterator _end;
};




template< class T, class Allocator >
vector<T, Allocator>::vector() {
    new(this) vector(Allocator());
}

template< class T, class Allocator >
vector<T, Allocator>::vector( const Allocator& alloc ):
    _alloc(alloc),
    _size(0),
    _capacity(16)    // 默认的容量是 2^4
{
    this->_data = this->_alloc.allocate(this->_capacity);
    this->_first = this->_last = this->_data;
    this->_end = this->_data + this->_capacity;
}

template< class T, class Allocator >
vector<T, Allocator>::vector( const vector<T, Allocator>& other ) {
    new(this) vector(other, other.get_allocator());
}

template< class T, class Allocator >
vector<T, Allocator>::vector( const vector<T, Allocator>& other, const Allocator& alloc ):
    _alloc(alloc),
    _size(other.size()),
    _capacity(other.capacity())
{
    this->_data = this->_alloc.allocate(this->_capacity);
    for(unsigned int i = 0; i < this->_size; ++i) {
        this->_alloc.construct(this->_data + i, other.data()[i]);
    }
    this->_first = this->_data;
    this->_last = this->_data + this->_size;
    this->_end = this->_data + this->_capacity;
}

template< class T, class Allocator >
vector<T, Allocator>::vector( size_type count, const Allocator& alloc ):
    _alloc(alloc),
    _size(count),
    _capacity(count)
{
    this->_data = this->_alloc.allocate(this->_capacity);
    for(unsigned int i = 0; i < this->_size; ++i) {
        this->_alloc.construct(this->_data + i, T());
    }
    this->_first = this->_data;
    this->_last = this->_data + this->_size;
    this->_end = this->_data + this->_capacity;
}

template< class T, class Allocator >
vector<T, Allocator>::vector( size_type count, const_reference value, const Allocator& alloc ):
    _alloc(alloc),
    _size(count),
    _capacity(count)
{
    this->_data = this->_alloc.allocate(this->_capacity);
    for(unsigned int i = 0; i < this->_size; ++i) {
        this->_alloc.construct(this->_data + i, value);
    }
    this->_first = this->_data;
    this->_last = this->_data + this->_size;
    this->_end = this->_data + this->_capacity;
}

template< class T, class Allocator >
vector<T, Allocator>::vector( vector<T, Allocator>&& other ) {
    new(this) vector(other, c3::move(other.get_allocator()));
}

template< class T, class Allocator >
vector<T, Allocator>::vector( vector<T, Allocator>&& other, const Allocator& alloc ):
    _alloc(alloc),
    _data(other._data),
    _size(other._size),
    _capacity(other._capacity)
{
    other._data = other._alloc.allocate(0);
    other._capacity = other._size = 0;
    other._first = other._last = other._end = other._data;
    this->_first = this->_data;
    this->_last = this->_data + this->_size;
    this->_end = this->_data + this->_capacity;
}

template< class T, class Allocator >
vector<T, Allocator>::vector( std::initializer_list<T> init, const Allocator& alloc ):
    _alloc(alloc)
{
    this->_data = this->_alloc.allocate(init.size());
    this->_capacity = init.size();
    for(size_t i = 0; i < init.size(); ++i) {
        this->_alloc.construct(this->_data + i, *(init.begin() + i));
    }
    this->_size = init.size();
    this->_first = this->_data;
    this->_last = this->_data + this->_size;
    this->_end = this->_data + this->_capacity;
}

template< class T, class Allocator >
vector<T, Allocator>::~vector() {
    for(unsigned int i = 0; i < this->_size; ++i) {
        this->_alloc.destroy(this->_data + i);
    }
    this->_alloc.deallocate(this->_data, this->_capacity);
}



template< class T, class Allocator >
vector<T, Allocator>& vector<T, Allocator>::operator=( const vector<T, Allocator>& other ) {
    for(unsigned int i = 0; i < this->_size; ++i) {
        this->_alloc.destroy(this->_data + i);
    }
    this->_alloc.deallocate(this->_data, this->_capacity);
    this->_alloc = other.get_allocator();
    this->_capacity = other.capacity();
    this->_data = this->alloc.allocate(this->_capacity);
    for(size_t i = 0; i < other.size(); ++i) {
        this->_alloc.construct(this->_data + i, other.data()[i]);
    }
    this->_size = other.size();
    this->_first = this->_data;
    this->_last = this->_data + this->_size;
    this->_end = this->_data + this->_capacity;
    return *this;
}

template< class T, class Allocator >
vector<T, Allocator>& vector<T, Allocator>::operator=( vector<T, Allocator>&& other ) {
    for(unsigned int i = 0; i < this->_size; ++i) {
        this->_alloc.destroy(this->_data + i);
    }
    this->_alloc.deallocate(this->_data, this->_capacity);
    this->_alloc = c3::move(other.get_allocator());
    this->_data = other._data;
    other._data = other._alloc.allocate(0);
    other._capacity = other._size = 0;
    this->_capacity = other.capacity();
    this->_size = other.size();
    other._first = other._last = other._end = other._data;
    this->_first = this->_data;
    this->_last = this->_data + this->_size;
    this->_end = this->_data + this->_capacity;
    
    return *this;
}

template< class T, class Allocator >
vector<T, Allocator>& vector<T, Allocator>::operator=( std::initializer_list<T> ilist ) {
    for(unsigned int i = 0; i < this->_size; ++i) {
        this->_alloc.destroy(this->_data + i);
    }
    this->_alloc.deallocate(this->_data, this->_capacity);
    this->_capacity = ilist.size();
    this->_data = this->alloc.allocate(this->_capacity);
    for(size_t i = 0; i < ilist.size(); ++i) {
        this->_alloc.construct(this->_data + i, ilist.data()[i]);
    }
    this->_size = ilist.size();
    this->_first = this->_data;
    this->_last = this->_data + this->_size;
    this->_end = this->_data + this->_capacity;
    return *this;
}


template< class T, class Allocator >
void vector<T, Allocator>::assign( size_type count, const_reference value ) {
    for(unsigned int i = 0; i < this->_size; ++i) {
        this->_alloc.destroy(this->_data + i);
    }
    this->_size = 0;
    size_type new_cap = this->capacity;
    while(new_cap < count) {
        new_cap *= 2;
    }
    this->reserve(new_cap);

    for(unsigned int i = 0; i < this->_size; ++i) {
        this->_alloc.construct(this->_data + i, value);
    }
    this->_size = count();
}

template< class T, class Allocator >
Allocator vector<T, Allocator>::get_allocator() const {
    return this->_alloc;
}

template< class T, class Allocator >
typename vector<T, Allocator>::reference vector<T, Allocator>::at( size_type pos ) {
    if(pos >= this->_size)
        return *(this->_last - 1);
    return *(this->_first + pos);
}

template< class T, class Allocator >
typename vector<T, Allocator>::reference vector<T, Allocator>::operator[]( size_type pos ) {
    return at(pos);
}

template< class T, class Allocator >
typename vector<T, Allocator>::const_reference vector<T, Allocator>::at( size_type pos ) const {
    if(pos >= this->_size)
        return *(this->_last - 1);
    return *(this->_first + pos);
}

template< class T, class Allocator >
typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[]( size_type pos ) const {
    return at(pos);
}

template< class T, class Allocator >
typename vector<T, Allocator>::reference vector<T, Allocator>::front() {
    return *(this->_first);
}

template< class T, class Allocator >
typename vector<T, Allocator>::const_reference vector<T, Allocator>::front() const {
    return *(this->_first);
}

template< class T, class Allocator >
typename vector<T, Allocator>::reference vector<T, Allocator>::back() {
    return *(this->_last - 1);
}

template< class T, class Allocator >
typename vector<T, Allocator>::const_reference vector<T, Allocator>::back() const {
    return *(this->_last - 1);
}

template< class T, class Allocator >
typename vector<T, Allocator>::pointer vector<T, Allocator>::data() noexcept {
    return this->_data;
}

template< class T, class Allocator >
typename vector<T, Allocator>::const_pointer vector<T, Allocator>::data() const noexcept {
    return this->_data;
}

template< class T, class Allocator >
typename vector<T, Allocator>::iterator vector<T, Allocator>::begin() {
    return this->_first;
}

template< class T, class Allocator >
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::begin() const {
    return this->_first;
}

template< class T, class Allocator >
typename vector<T, Allocator>::iterator vector<T, Allocator>::end() {
    return this->_last;
}

template< class T, class Allocator >
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::end() const {
    return this->_last;
}

template< class T, class Allocator >
typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rbegin() {
    return c3::reverse_iterator<iterator>(this->_last);
}

template< class T, class Allocator >
typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rbegin() const {
    return c3::reverse_iterator<iterator>(this->_last);
}


template< class T, class Allocator >
typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rend() {
    return c3::reverse_iterator<iterator>(this->_first);
}

template< class T, class Allocator >
typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rend() const {
    return c3::reverse_iterator<iterator>(this->_first);
}

template< class T, class Allocator >
bool vector<T, Allocator>::empty() const {
    return this->_size == 0;
}

template< class T, class Allocator >
typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const {
    return this->_size;
}

template< class T, class Allocator >
typename vector<T, Allocator>::size_type vector<T, Allocator>::max_size() const {
    return UINT32_MAX;
}

template< class T, class Allocator >
typename vector<T, Allocator>::size_type vector<T, Allocator>::capacity() const {
    return this->_capacity;
}

template< class T, class Allocator >
void vector<T, Allocator>::reserve(size_type new_cap) {
    if (new_cap <= this->_capacity)
        return;

    pointer tmp = this->_alloc.allocate(new_cap);
    memcpy(tmp, this->_data, sizeof(T) * this->_capacity);
    this->_alloc.deallocate(this->_data, this->_capacity);
    this->_data = tmp;
    this->_capacity = new_cap;
    this->_first = this->_data;
    this->_last = this->_data + this->_size;
    this->_end = this->_data + this->_capacity;
}

template< class T, class Allocator >
void vector<T, Allocator>::shrink_to_fit() {
    pointer tmp = this->_alloc.allocate(this->_size);
    memcmp(tmp, this->_data, sizeof(T) * this->_size);
    for(unsigned int i = 0; i < this->_size; ++i) {
        this->_alloc.destroy(this->_data + i);
    }
    this->_alloc.deallocate(this->_data, this->_capacity);
    this->_data = tmp;
    this->_capacity = this->_size;
    this->_first = this->_data;
    this->_last = this->_data + this->_size;
    this->_end = this->_data + this->_capacity;
}

template< class T, class Allocator >
void vector<T, Allocator>::clear() {
    for(unsigned int i = 0; i < this->_size; ++i) {
        this->_alloc.destroy(this->_data + i);
    }
    this->_size = 0;
    this->_first = this->_last = this->_data;
    this->_end = this->_data + this->_capacity;
}

template< class T, class Allocator >
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert( const_iterator pos, const_reference value ) {
    return insert(pos, 1, value);
}

template< class T, class Allocator >
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert( const_iterator pos, size_type count, const_reference value ) {
    if (pos < this->_first || pos > this->_last)
        return const_cast<iterator>(pos);

    size_type new_cap = this->capacity;
    while(new_cap < this->_size + count) {
        new_cap *= 2;
    }
    this->reserve(new_cap);

    iterator insert_head = const_cast<iterator>(pos);
    for(iterator it = insert_head; it != this->_last; ++it) {
        *(it + count) = *(it);
    }
    for(unsigned int i = 0; i < count; ++i) {
        this->_alloc.construct(insert_head + i, value);
    }
    this->_size += count;
    return insert_head;
}

template< class T, class Allocator >
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase( const_iterator pos ) {
    return erase(pos, pos + 1);
}

template< class T, class Allocator >
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase( const_iterator first, const_iterator last ) {
    if(first > last)
        return const_cast<iterator>(first);

    iterator erase_first, erase_last;
    if (first < this->_first)
        erase_first = this->_first;
    else if (first > this->_last)
        erase_first = this->_last;
    else
        erase_first = const_cast<iterator>(first);

    if (last < this->_first)
        erase_last = this->_first;
    else if (last > this->_last)
        erase_last = this->_last;
    else
        erase_last = const_cast<iterator>(last);

    if(first == last)
        return const_cast<iterator>(first);

    size_type count = erase_last - erase_first;
    for(iterator it = erase_first; it < erase_last; ++it) {
        this->_alloc.destroy(it);
        *(it) = *(it + count);
    }
    this->_size -= count;
    return erase_first;
}

template< class T, class Allocator >
void vector<T, Allocator>::push_back( const_reference value ) {
    ++ this->_size;
    if(this->_capacity < this->_size) {
        reserve(2 * this->_capacity);
    }

    this->_alloc.construct(this->_last, value);
    ++ this->_last;
}

template< class T, class Allocator >
void vector<T, Allocator>::push_back( reference& value ) {
    if(this->_capacity <= this->_size) {
        reserve(2 * this->_capacity);
    }

    this->_alloc.construct(this->_last, c3::move(value));
    // _size 的变化必须要紧跟在 construct 后，不然当一些成员函数引用 _size 的时候，得到的不是实际正确的 _size
    // 如果把 ++_size; 放在此函数第一句，那么 reserve 函数执行时，其中引用的 _size 比实际的 _size
    // (此时还没有调用 construct) 大 1，给 _last 赋值是，它的指向会出错，而后面的 construct 又以 _last 为参数，
    // 显然会出错。
    ++ this->_size;
    ++ this->_last;
}

template< class T, class Allocator >
void vector<T, Allocator>::pop_back() {
    this->_alloc.destroy(this->_last);
    -- this->_size;
    -- this->_last;
}

template< class T, class Allocator >
void vector<T, Allocator>::resize( size_type count ) {
    resize(count, T());
}

template< class T, class Allocator >
void vector<T, Allocator>::resize( size_type count, const_reference value ) {
    if (count < this->_size) {
        for(unsigned int i = count; i < this->_size; ++i) {
            this->_alloc.destroy(this->_data + i);
        }
        this->_size = count;
    } else if (count > this->_size) {
        size_type new_cap = this->capacity;
        while(new_cap < count) {
            new_cap *= 2;
        }
        this->reserve(new_cap);
        for(unsigned int i = this->_size; i < count; ++i) {
            this->_alloc.construct(this->_data + i, value);
        }
    }
}

template< class T, class Allocator >
void vector<T, Allocator>::swap( vector& other ) {
    c3::swap(*this, other);
}
    
    

} // namespace c3

#endif // _C3TL_VECTOR_H_