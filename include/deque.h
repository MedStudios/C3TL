//
// Created on 2020 - 6 - 11
// Written by TSH
//

#ifndef _C3TL_DEQUE_H_
#define _C3TL_DEQUE_H_

#include <cstring>
#include "memory.h"
#include "iterator.h"
#include "utility.h"

namespace c3
{

template< class T, class Allocator = c3::allocator<T> >
class deque {

public:
    typedef c3::allocator<T>                         allocator_type;
    typedef c3::allocator<T>                         data_allocator;

    typedef typename allocator_type::value_type      value_type;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;

    typedef pointer*                                 map_pointer;

public:
    static const size_type seg_size = 16;     // 默认的单位内存段大小（ seg_size * sizeof(T) ）

public:
    struct iterator {
        pointer     cur;     // 指向当前遍历的元素
        pointer     first;   // 指向所处内存段的首位
        pointer     last;    // 指向所处内存段的末位后一位
        map_pointer node;    // 指向 _map 数组中存储的指向所处内存段的指针

        // 指针访问符
        reference operator*() const {
            return *(this->cur);
        }

        iterator& operator++ () {
            if(this->cur + 1 == this->last) {
                ++node;
                this->first = this->node[0];
                this->last = this->node[0] + deque<T, Allocator>::seg_size;
                this->cur = this->first;
            } else {
                ++cur;
            }
            return *this;
        }
        iterator operator++ (int) {
            iterator ip = *this;
            ++(*this);
            return ip;
        }
        iterator& operator-- () {
            if(this->cur == this->first) {
                --node;
                this->first = this->node[0];
                this->last = this->node[0] + deque<T, Allocator>::seg_size;
                this->cur = this->last - 1;
            } else {
                --cur;
            }
            return *this;
        }
        iterator& operator-- (int) {
            iterator ip = *this;
            --(*this);
            return ip;
        }
        iterator operator+ (const int & n) const {
            if (n==0)
                return *this;

            iterator ip = *this;
            // 要偏移多少个内存段
            int node_offset;
            // 在内存段里要偏移多少个位置
            int it_offset;

            const int ss = static_cast<const int>(deque<T, Allocator>::seg_size);
            if ( n > 0 ) {
                int t = n + (ip.cur - ip.first);
                node_offset = t / ss;
                it_offset = t % ss;
            } else {
                int t = n - (ip.last - ip.cur);
                node_offset = (t + 1) / ss;
                it_offset = (ss + t % ss) % ss;
                if (it_offset == -1) it_offset = ss - 1;
            }
            ip.node += node_offset;
            ip.first = ip.node[0];
            ip.last = ip.node[0] + seg_size;
            ip.cur = ip.node[0] + it_offset;
            return ip;
        }
        iterator operator- (const int & n) const {
            return (*this) + (-n);
        }
        deque<T, Allocator>::difference_type operator- (const iterator & rhs) const {
            difference_type node_diff = (this->node - rhs.node) * deque<T, Allocator>::seg_size;
            difference_type this_offset =  this->cur - this->first;
            difference_type rhs_offset = rhs.cur - rhs.first;
            return node_diff + this_offset - rhs_offset;
        }
        iterator& operator+= (const int& n) {
            (*this) = (*this) + n;
            return (*this);
        }
        iterator& operator-= (const int& n) {
            (*this) = (*this) - n;
            return (*this);
        }
        iterator& operator[] (const unsigned int& n) const {
            return *(*this + n);
        }
        bool operator< (const iterator& rhs) const {
            return ((*this) - rhs) < 0;
        }
        bool operator<= (const iterator& rhs) const {
            return ((*this) - rhs) <= 0;
        }
        bool operator> (const iterator& rhs) const {
            return ((*this) - rhs) > 0;
        }
        bool operator>= (const iterator& rhs) const {
            return ((*this) - rhs) > 0;
        }
        bool operator== (const iterator& rhs) const {
            return ((*this) - rhs) == 0;
        }
        bool operator!= (const iterator& rhs) const {
            return ((*this) - rhs) != 0;
        }
    };

    typedef const iterator                           const_iterator;
    typedef c3::reverse_iterator<iterator>           reverse_iterator;
    typedef c3::reverse_iterator<const_iterator>     const_reverse_iterator;

protected:
    Allocator _alloc;
    map_pointer _map;		// 不同内存段的映射指针数组
    size_type _map_size;	// _map 数组的 长度
//  size_type _my_off;	    // 首元素离首内存段之首的偏移量
    size_type _size;        // 这个 deque 有多少个元素
    iterator _first;
    iterator _last;

    // 向后扩展map
    void _expand_back(const size_type& map_count) {
        // _first 迭代器在 _map 中的第几个内存块里
        size_type offset_first = this->_first.node - this->_map;
        // _last 迭代器在 _map 中的第几个内存块里
        size_type offset_last = this->_last.node - this->_map;
        size_type new_map_size = this->_map_size + map_count;
        auto tmp = new pointer[new_map_size];
        memcpy(tmp, this->_map, sizeof(pointer) * this->_map_size);
        delete[] this->_map;
        this->_map = tmp;
        for(size_type i = this->_map_size; i < new_map_size; ++i) {
            _map[i] = this->_alloc.allocate(seg_size);
        }
        this->_map_size = new_map_size;
        this->_first.node = this->_map + offset_first;
        this->_last.node = this->_map + offset_last;
    }
    // 向前扩展map
    void _expand_front(const size_type& map_count) {
        // _first 迭代器在 _map 中的第几个内存块里
        size_type offset_first = this->_first.node - this->_map;
        // _last 迭代器在 _map 中的第几个内存块里
        size_type offset_last = this->_last.node - this->_map;
        size_type new_map_size = this->_map_size + map_count;
        auto tmp = new pointer[new_map_size];
        memcpy(tmp + map_count, this->_map, sizeof(pointer) * this->_map_size);
        delete[] this->_map;
        this->_map = tmp;

        for(size_type i = 0; i < map_count; ++i) {
            this->_map[i] = this->_alloc.allocate(seg_size);
        }
        this->_map_size = new_map_size;
        this->_first.node = this->_map + map_count + offset_first;
        this->_last.node = this->_map + map_count + offset_last;
    }


public:

    // 构造空的 deque
    deque();
    // 构造空的 deque，使用 alloc 作为内存分配器
    explicit deque( const Allocator& alloc );
    // 复制构造函数
    deque( const deque& other );
    // 复制构造函数，使用 alloc 作为内存分配器
    deque( const deque& other, const Allocator& alloc );
    // 构造拥有个 count 默认 T 实例的容器。不进行复制。使用 alloc 作为内存分配器
    explicit deque( size_type count, const Allocator& alloc = Allocator() );
    // 构造拥有 count 个 value 的元素的容器。使用 alloc 作为内存分配器
    deque( size_type count, const_reference value, const Allocator& alloc = Allocator());
    // （可选）deque( deque&& other );
    // （可选）deque( deque&& other, const Allocator& alloc );


    // 销毁 deque 。调用每个元素的析构函数，然后解分配所用的存储。注意，若元素是指针，则不销毁所指向的对象。
    ~deque();


    // 复制赋值运算符。以 other 的副本替换内容。
    deque& operator=( const deque& other );
    // 移动赋值运算符。
    // （可选）deque& operator=( deque&& other );


    // 以 count 个 value 替换 deque 的内容。
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


    // 请求移除未使用的保留空间。（非强制）
    void shrink_to_fit();


    // 清空容器。
    void clear();


    // 在 pos 前插入 value 。
    iterator insert( const_iterator pos, const_reference value );
    // （可选）iterator insert( const_iterator pos, T&& value );

    // 在 pos 前插入 count 个 value 。
    iterator insert( const_iterator pos, size_type count, const_reference value );


    // 移除位于 pos 的元素。
    iterator erase( const_iterator pos );
    // 移除范围 [first; last) 中的元素。
    iterator erase( const_iterator first, const_iterator last );


    // 后附给定元素 value 到容器尾。
    void push_back( const_reference value );
    // （可选）void push_back( T&& value );


    // 移除容器的最末元素。在空容器上调用 pop_back 是未定义的。
    void pop_back();


    // 前附给定元素 value 到容器尾。
    void push_front( const_reference value );
    // （可选）void push_front( T&& value );


    // 移除容器的首元素。在空容器上调用 pop_back 是未定义的。
    void pop_front();



    // 若当前大小大于 count ，则减小容器为其首 count 个元素。若当前大小小于 count， 则后附额外的默认插入的元素。
    void resize( size_type count );
    // 若当前大小大于 count ，则减小容器为其首 count 个元素。若当前大小小于 count， 则后附额外的 value 的副本。
    void resize( size_type count, const_reference value );



    // 将内容与 other 的交换。不在单个元素上调用任何移动、复制或交换操作。
    void swap( deque& other );

};


template< class T, class Allocator >
deque<T, Allocator>::deque() {
    new(this) deque(Allocator());
}

template< class T, class Allocator >
deque<T, Allocator>::deque( const Allocator& alloc ):
    _alloc(alloc),
    _map(new pointer[1]),
    _map_size(1),
    _size(0)
{
    _map[0] = this->_alloc.allocate(seg_size);
    this->_first = iterator();
    this->_first.first = _map[0];
    this->_first.last = _map[0] + seg_size;
    this->_first.cur = this->_first.first;
    this->_first.node = _map + 0;
    this->_last = this->_first;
}

template< class T, class Allocator >
deque<T, Allocator>::deque( const deque& other ) {
    new(this) deque(other, Allocator());
}

template< class T, class Allocator >
deque<T, Allocator>::deque( const deque& other, const Allocator& alloc ):
    _alloc(alloc)
{
    this->_map = new pointer[other._map_size];
    for(size_type i = 0; i < other._map_size; ++i) {
        this->_map[i] = this->_alloc.allocate(seg_size);
        for(size_type j = 0; j < seg_size; ++j) {
            this->_alloc.construct(this->_map[i] + j, other._map[i][j]);
        }
    }
    this->_size = other._size;
    this->_map_size = other._map_size;
    this->_first.first = this->_map[0];
    this->_first.last = this->_map[0] + seg_size;
    this->_first.cur = this->_map[0] + (other._first.cur - other._first.first);
    this->_first.node = this->_map;
    this->_last.first = this->_map[other._map_size - 1];
    this->_last.last = this->_map[other._map_size - 1] + seg_size;
    this->_last.cur = this->_map[0] + (other._last.cur - other._last.first);
    this->_last.node = this->_map + other._map_size - 1;
}

template< class T, class Allocator >
deque<T, Allocator>::deque( size_type count, const Allocator& alloc ) {
    new(this) deque(count, T(), alloc);
}

template< class T, class Allocator >
deque<T, Allocator>::deque( size_type count, const_reference value, const Allocator& alloc ):
    _alloc(alloc)
{
    size_type map_size = count / seg_size + 1;
    this->_map = new pointer[map_size];
    for(size_type i = 0; i < map_size - 1; ++i) {
        this->_alloc.allocate(this->_map[i], seg_size);
        for(size_type j = 0; j < seg_size; ++j) {
            this->_alloc.construct(this->_map[i] + j, value);
        }
    }
    this->_alloc.allocate(this->_map[map_size - 1], seg_size);
    for(size_type j = 0; j < count % seg_size; ++j) {
        this->_alloc.construct(this->_map[map_size - 1] + j, value);
    }
    this->_map_size = map_size;

    this->_first = iterator();
    this->_first.first = this->_map[0];
    this->_first.last = this->_map[0]+ seg_size;
    this->_first.cur = this->_first.first;
    this->_first.node = this->_map + 0;
    this->_last = iterator();
    this->_last.first = this->_map[map_size - 1];
    this->_last.last = this->_map[map_size - 1] + seg_size;
    this->_last.cur = this->_last.first + count % seg_size;
    this->_last.node = this->_map + map_size - 1;

}

template< class T, class Allocator >
deque<T, Allocator>::~deque() {
    for(size_type i = 0; i < this->_map_size - 1; ++i) {
        for(size_type j = 0; j < seg_size; ++j) {
            this->_alloc.destroy(this->_map[i] + j);
        }
        this->_alloc.deallocate(this->_map[i], seg_size);
    }
    size_type last_node_cnt = this->_last.cur - this->_last.first;
    for(size_type j = 0; j < last_node_cnt; ++j) {
        this->_alloc.destroy(this->_map[this->_map_size - 1] + j);
    }
    delete[] this->_map;
}

template< class T, class Allocator >
deque<T, Allocator>& deque<T, Allocator>::operator=( const deque& other ) {
    this->~deque();
    new(this) deque(other);
}

template< class T, class Allocator >
void deque<T, Allocator>::assign( size_type count, const_reference value ) {
    this->~deque();
    new(this) deque(count, value);
}

template< class T, class Allocator >
Allocator deque<T, Allocator>::get_allocator() const {
    return this->_alloc;
}

template< class T, class Allocator >
typename deque<T, Allocator>::reference deque<T, Allocator>::at( size_type pos ){
    size_type first_node_offset = this->_first.cur - this->_first.first;
    size_type first_map_offset = this->_first.node - this->_map;
    return this->_map[first_map_offset + ((pos + first_node_offset) / seg_size)][(pos + first_node_offset) % seg_size];
}

template< class T, class Allocator >
typename deque<T, Allocator>::reference deque<T, Allocator>::operator[]( size_type pos ) {
    return at(pos);
}

template< class T, class Allocator >
typename deque<T, Allocator>::const_reference deque<T, Allocator>::at( size_type pos ) const {
    size_type map_offset = this->_first.cur - this->_first.first;
    return this->_map[(pos + map_offset) / seg_size][(pos + map_offset) % seg_size];
}

template< class T, class Allocator >
typename deque<T, Allocator>::const_reference deque<T, Allocator>::operator[]( size_type pos ) const {
    return at(pos);
}

template< class T, class Allocator >
typename deque<T, Allocator>::reference deque<T, Allocator>::front() {
    return *(this->_first);
}
template< class T, class Allocator >
typename deque<T, Allocator>::const_reference deque<T, Allocator>::front() const {
    return *(this->_first);
}

template< class T, class Allocator >
typename deque<T, Allocator>::reference deque<T, Allocator>::back() {
    return *(this->_last - 1);
}

template< class T, class Allocator >
typename deque<T, Allocator>::const_reference deque<T, Allocator>::back() const {
    return *(this->_last - 1);
}

template< class T, class Allocator >
typename deque<T, Allocator>::iterator deque<T, Allocator>::begin() {
    return this->_first;
}

template< class T, class Allocator >
typename deque<T, Allocator>::const_iterator deque<T, Allocator>::begin() const {
    return this->_first;
}

template< class T, class Allocator >
typename deque<T, Allocator>::iterator deque<T, Allocator>::end() {
    return this->_last;
}

template< class T, class Allocator >
typename deque<T, Allocator>::const_iterator deque<T, Allocator>::end() const {
    return this->_last;
}

template< class T, class Allocator >
typename deque<T, Allocator>::reverse_iterator deque<T, Allocator>::rbegin() {
    return c3::reverse_iterator<iterator>(this->_first);
}

template< class T, class Allocator >
typename deque<T, Allocator>::const_reverse_iterator deque<T, Allocator>::rbegin() const {
    return c3::reverse_iterator<iterator>(this->_first);
}

template< class T, class Allocator >
typename deque<T, Allocator>::reverse_iterator deque<T, Allocator>::rend() {
    return c3::reverse_iterator<iterator>(this->_last);
}

template< class T, class Allocator >
typename deque<T, Allocator>::const_reverse_iterator deque<T, Allocator>::rend() const {
    return c3::reverse_iterator<iterator>(this->_last);
}

template< class T, class Allocator >
bool deque<T, Allocator>::empty() const {
    return this->_size == 0;
}

template< class T, class Allocator >
typename deque<T, Allocator>::size_type deque<T, Allocator>::size() const {
    return this->_size;
}

template< class T, class Allocator >
typename deque<T, Allocator>::size_type deque<T, Allocator>::max_size() const {
    return UINT32_MAX;
}

template< class T, class Allocator >
void deque<T, Allocator>::shrink_to_fit() {

}


template< class T, class Allocator >
void deque<T, Allocator>::clear() {
    this->~deque();
    new(this) deque(this->_alloc);
}

template< class T, class Allocator >
typename deque<T, Allocator>::iterator deque<T, Allocator>::insert( const_iterator pos, const_reference value ) {
    return insert(pos, 1, value);
}

template< class T, class Allocator >
typename deque<T, Allocator>::iterator deque<T, Allocator>::insert( const_iterator pos, size_type count, const_reference value ) {
    if(count == 0)
        return pos;

    iterator result;
    if(this->_last - pos <= pos - this->_first) {
        if(count > this->_last.last - this->_last.cur) {
            size_t expand_count = ((count - (this->_last.last - this->_last.cur)) / seg_size) + 1;
            _expand_back(expand_count);
        }
        iterator new_last = this->_last + count;
        const_iterator insert_part_last = pos + count;
        for(iterator it = new_last - 1; it != insert_part_last - 1; --it) {
            *(it) = *(it - count);
        }
        for(iterator it = insert_part_last - 1; it != pos - 1; --it) {
            this->_alloc.construct(it.cur, value);
        }
        this->_last = new_last;
        result = pos;
    } else {
        if(count > this->_first.cur - this->_last.first) {
            size_t expand_count = ((count - (this->_first.cur - this->_last.first)) / seg_size) + 1;
            _expand_front(expand_count);
        }
        iterator new_first = this->_first - count;
        const_iterator insert_part_first = pos - count;
        for(iterator it = new_first; it != insert_part_first; ++it) {
            *(it) = *(it + count);
        }
        for(iterator it = insert_part_first; it != pos; ++it) {
            this->_alloc.construct(it.cur, value);
        }
        this->_first = new_first;
        result = pos - count;
    }
    this->_size += count;
    return result;
}

template< class T, class Allocator >
typename deque<T, Allocator>::iterator deque<T, Allocator>::erase( const_iterator pos ) {
    return erase(pos, pos + 1);
}

template< class T, class Allocator >
typename deque<T, Allocator>::iterator deque<T, Allocator>::erase( const_iterator first, const_iterator last ) {
    for(iterator it = first; it != last; ++it) {
        this->_alloc.destroy(it.cur);
    }
    size_type count = last - first;
    iterator result;

    if(this->_last - last <= first - this->_first ) {
        this->_last -= count;
        for(iterator it = first; it != this->_last; ++it) {
            *(it) = *(it + count);
        }
        result = first;
    } else {
        this->_first += count;
        for(iterator it = last - 1; it != this->_first - 1; --it) {
            *(it) = *(it - count);
        }
        result = last;
    }
    this->_size -= count;
    return result;
}

template< class T, class Allocator >
void deque<T, Allocator>::push_back( const_reference value ) {
    if(this->_last.cur + 1 == this->_last.last) {
        _expand_back(1);
    }
    this->_alloc.construct((this->_last++).cur, value);
    ++this->_size;
}

template< class T, class Allocator >
void deque<T, Allocator>::pop_back() {
    this->_alloc.destroy((--this->_last).cur);
    --this->_size;
}

template< class T, class Allocator >
void deque<T, Allocator>::push_front( const_reference value ) {
    if(this->_first.cur == this->_first.first) {
        _expand_front(1);
    }
    this->_alloc.construct((--this->_first).cur, value);
    ++this->_size;
}

template< class T, class Allocator >
void deque<T, Allocator>::pop_front() {
    this->_alloc.destroy((this->_first++).cur);
    --this->_size;
}

template< class T, class Allocator >
void deque<T, Allocator>::resize( size_type count ) {
    resize(count, T());
}
template< class T, class Allocator >
void deque<T, Allocator>::resize( size_type count, const_reference value ) {
    if(count == this->_size)
        return;

    if(count < this->_size) {
        size_type map_squeeze = (count + (this->_last.last - this->_last.cur)) / seg_size;
        for(size_type i = 0; i < count; ++i) {
            this->_alloc.destroy((--this->_last).cur);
        }
        for(size_type i = 0; i < map_squeeze; ++i) {
            this->_alloc.deallocate(this->_map[--this->_map_size], seg_size);
        }
    } else {
        _expand_back(count - (this->_last.last - this->_last.cur));
        for(size_type i = 0; i < count; ++i) {
            this->_alloc.construct((this->_last++).cur, value);
        }
    }
}

template< class T, class Allocator >
void deque<T, Allocator>::swap( deque& other ) {
    c3::swap(*this, other);
}






}

#endif // _C3TL_DEQUE_H_