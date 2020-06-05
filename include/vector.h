#ifndef _C3TL_VECTOR_H_
#define _C3TL_VECTOR_H_

#include "memory.h"

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
    // （可选）vector( vector&& other );
    // （可选）vector( vector&& other, const Allocator& alloc );

    // 销毁 vector 。调用每个元素的析构函数，然后解分配所用的存储。注意，若元素是指针，则不销毁所指向的对象。 
    ~vector();

    // 复制赋值运算符。以 other 的副本替换内容。
    vector& operator=( const vector& other );
    // 移动赋值运算符。
    // （可选）vector& operator=( vector&& other );

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
    // （可选）void push_back( reference& value );

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
    friend bool operator!=( const c3::vector<_T,_Alloc>& lhs, const c3::vector<_T,_Alloc>& rhs );

    // 按字典序比较 lhs 与 rhs 的内容。
    friend bool operator<( const c3::vector<_T,_Alloc>& lhs, const c3::vector<_T,_Alloc>& rhs );
    friend bool operator<=( const c3::vector<_T,_Alloc>& lhs, const c3::vector<_T,_Alloc>& rhs );
    friend bool operator>( const c3::vector<_T,_Alloc>& lhs, const c3::vector<_T,_Alloc>& rhs );
    friend bool operator>=( const c3::vector<_T,_Alloc>& lhs, const c3::vector<_T,_Alloc>& rhs );
};



// 函数实现


    
} // namespace c3

#endif // _C3TL_VECTOR_H_