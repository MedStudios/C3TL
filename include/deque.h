//
// Created on 2020 - 6 - 11
// Written by TSH
//

#ifndef _C3TL_DEQUE_H_
#define _C3TL_DEQUE_H_

#include <cstring>
#include "memory.h"

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
                this->first = this->node;
                this->last = this->node + deque<T, Allocator>::seg_size;
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
                this->first = this->node;
                this->last = this->node + deque<T, Allocator>::seg_size;
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
        iterator operator+ (const int & n) {
            if (n==0)
                return *this;

            iterator ip = *this;
            // 要偏移多少个内存段
            int node_offset;
            // 在内存段里要偏移多少个位置
            int it_offset;

            if ( n > 0 ) {
                int t = (n + (ip.cur - ip.first));
                node_offset = t / deque<T, Allocator>::seg_size;
                it_offset = t % deque<T, Allocator>::seg_size;
            } else {
                int t = (n - (ip.last - ip.cur));
                int node_offset =  t / deque<T, Allocator>::seg_size;
                int it_offset = deque<T, Allocator>::seg_size + ( t % deque<T, Allocator>::seg_size );
            }
            ip.node += node_offset;
            ip.first = ip.node;
            ip.last = ip.node + seg_size;
            ip.cur = ip.node + it_offset;
            return ip;
        }
        iterator operator- (const int & n) {
            return (*this) + (-n);
        }
        deque<T, Allocator>::difference_type operator- (const iterator & rhs)  {
            return ((this->node - rhs.node) * deque<T, Allocator>::seg_size) - (this->cur - this->first) + (rhs.cur - rhs.first);
        }
        iterator& operator+= (const int& n) {
            (*this) = (*this) + n;
            return (*this);
        }
        iterator& operator-= (const int& n) {
            (*this) = (*this) - n;
            return (*this);
        }
        iterator& operator[] (const unsigned int& n) {
            return *(*this + n);
        }
        bool operator< (const iterator& rhs) {
            return ((*this) - rhs) < 0;
        }
        bool operator<= (const iterator& rhs) {
            return ((*this) - rhs) <= 0;
        }
        bool operator> (const iterator& rhs) {
            return ((*this) - rhs) > 0;
        }
        bool operator>= (const iterator& rhs) {
            return ((*this) - rhs) > 0;
        }
        bool operator== (const iterator& rhs) {
            return ((*this) - rhs) == 0;
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
    void _expand_back(size_type count) {
        size_type new_map_size = this->_map_size + count;
        map_pointer tmp = new pointer[new_map_size];
        memcpy(tmp, this->_map, sizeof(pointer) * this->_map_size);
        delete[] this->_map;
        this->_map = tmp;
        for(size_type i = this->_map_size; i < new_map_size; ++i) {
            _map[i] = this->_alloc.allocate(seg_size);
        }
        this->_map_size = new_map_size;
    }
    // 向前扩展map
    void _expand_front(size_type count) {
        size_type new_map_size = this->_map_size + count;
        map_pointer tmp = new pointer[new_map_size];
        memcpy(tmp + count, this->_map, sizeof(pointer) * this->_map_size);
        delete[] this->_map;
        this->_map = tmp;
        for(size_type i = 0; i < count; ++i) {
            _map[i] = this->_alloc.allocate(seg_size);
        }
        this->_map_size = new_map_size;
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
    void resize( size_type count );// 若当前大小大于 count ，则减小容器为其首 count 个元素。若当前大小小于 count， 则后附额外的 value 的副本。
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
    for(size_type i = 0; i < other._map_size; ++i) {
        for(size_type j = 0; j < seg_size; ++j) {
            this->_alloc.destroy(_map[i] + j);
        }
        this->_alloc.deallocate(_map + i);
    }
    delete[] this->_map;
    this->_map = new pointer[other._map_size];
    for(size_type i = 0; i < other._map_size; ++i) {
        this->_map[i] = this->_alloc.allocate(seg_size);
        for(size_type j = 0; j < seg_size; ++j) {
            this->_alloc.construct(this->_map[i] + j, other._map[i][j]);
        }
    }
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
deque<T, Allocator>::deque( size_type count, const_reference value, const Allocator& alloc):
    _alloc(alloc)
{
    size_type map_size = count / seg_size + 1
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
    this->_first.first = _map[0];
    this->_first.last = _map[0]+ seg_size;
    this->_first.cur = this->_first.first;
    this->_first.node = _map + 0;
    this->_last = iterator();
    this->_last.first = _map[map_size - 1];
    this->_last.last = _map[map_size - 1] + seg_size;
    this->_last.cur = this->_last.first + count % seg_size;
    this->_last.node = _map + map_size - 1;

}

// （可选）deque( deque&& other );
// （可选）deque( deque&& other, const Allocator& alloc );


// 销毁 deque 。调用每个元素的析构函数，然后解分配所用的存储。注意，若元素是指针，则不销毁所指向的对象。
template< class T, class Allocator >
deque<T, Allocator>::~deque() {
    for(size_type i = 0; i < other._map_size; ++i) {
        for(size_type j = 0; j < seg_size; ++j) {
            this->_alloc.destroy(_map[i] + j);
        }
        this->_alloc.deallocate(_map + i);
    }
    delete[] this->_map;
}








}

#endif // _C3TL_DEQUE_H_