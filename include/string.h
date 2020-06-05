#ifndef _C3TL_STRING_H_
#define _C3TL_STRING_H_

#include <stddef.h>
#include "memory.h"
#include "iterator.h"

namespace c3
{


template < class CharT, class Allocator = c3::allocator<CharT> >
class basic_string {

public:
    typedef c3::allocator<CharT>                     allocator_type;
    typedef c3::allocator<CharT>                     data_allocator;

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
    static const size_type npos = -1;		

public:

    // 构造空串
    basic_string();
    // 构造空串，使用 alloc 作为内存分配器
    explicit basic_string( const Allocator& alloc );
    // 复制构造函数
    basic_string( const basic_string& other );
    // 复制构造函数，使用 alloc 作为内存分配器
    basic_string( const basic_string& other, const Allocator& alloc );
    // （可选）移动构造函数
    // basic_string( basic_string&& other );
    // （可选）移动构造函数，使用 alloc 作为内存分配器
    // basic_string( basic_string&& other, const Allocator& alloc );
    // 构造拥有 count 个字符 ch 的串，使用 alloc 作为内存分配器
    basic_string( size_type count, value_type ch, const Allocator& alloc = Allocator() );
    // 以 other 的子串 [pos, pos+count) 构造串。若 count == npos 或未指定 count 或越过字符串的结尾，则产生的子串为 [pos, other.size())。
    basic_string( const basic_string& other, size_type pos, size_type count = c3::basic_string::npos, const Allocator& alloc = Allocator() );
    // 以 s 的首 count 个字符构造串。s 能包含 '\0'。串的长度为 count。若 [s, s + count) 不是合法范围则行为未定义。
    basic_string( const_pointer s, size_type count, const Allocator& alloc = Allocator() );
    // 用以 '\0' 结尾的 CharT 数组初始化串。（一般用双引号括起来的字符串初始化 string 即调用该函数）
    basic_string( const_pointer s, const Allocator& alloc = Allocator() );


    // 以 count 个 ch 替换本串。返回 *this
    basic_string& assign( size_type count, value_type ch );
    // 相当于 assign(1, ch)。返回 *this
    basic_string& operator=( value_type ch );
    // 以 str 的副本替换本串。返回 *this
    basic_string& assign( const basic_string& str );
    basic_string& operator=( const basic_string& str );
    // 以 str 的子串 [pos, pos+count) 替换本串。若请求的子串越过其尾或 count == npos ，则产生的子串是 [pos, str.size())。返回 *this
    basic_string& assign( const basic_string& str, size_type pos, size_type count );
    // （可选）移动 str 到本串。返回 *this
    // basic_string& assign( basic_string&& str );
    // basic_string& operator=( basic_string&& str );
    // 以范围 [s, s+count) 中的字符的副本替换本串。此范围能含 '\0'。返回 *this
    basic_string& assign( const_pointer s, size_type count );
    // 以 s 的副本替换本串。返回 *this
    basic_string& assign( const_pointer s );
    basic_string& operator=( const_pointer s );


    // 返回使用的内存分配器
    Allocator get_allocator() const;


    // 返回到位于指定位置 pos 的字符的引用。
    reference at( size_type pos );
    reference operator[]( size_type pos );
    const_reference at( size_type pos ) const;
    const_reference operator[]( size_type pos ) const;


    // 返回首字符的引用
    reference front();
    const_reference front() const;


    // 返回末字符的引用
    reference back();
    const_reference back() const;


    // 返回字符串的不可修改的原生字符数组。
    const_pointer data() const;
    const_pointer c_str() const;


    // 返回可变或常迭代器，取决于 *this 的常性。
    iterator begin();
    const_iterator begin() const;


    // 返回指向字符串末字符的后一个字符的迭代器。此字符表现为占位符，试图访问它导致未定义行为。 
    iterator end();
    const_iterator end() const;


    // 返回指向逆转字符串首字符的逆向迭代器。它对应非逆向字符串的末字符。 
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;


    // 返回指向逆转字符串末字符后一个字符的逆向迭代器。它对应非逆向字符串的首字符的前一个字符。 
    reverse_iterator rend();
    const_reverse_iterator rend() const;


    // 若串为空则返回 true ，否则返回 false 。
    bool empty() const;


    // 返回串的长度，即串中的字符数
    size_type size() const;
    size_type length() const;


    // 返回由于操作系统或库实现限制所能保有的最大串长度（一般为npos）
    size_type max_size() const;


    // 返回当前已为串分配的保留空间的字符数。（不要与size和length混淆）
    size_type capacity() const;


    // 重新分配串的保留空间。若 new_cap 大于当前 capacity()，则分配新存储，并令 capacity() 大于或等于 new_cap。若 new_cap 小于或等于当前 capacity()，则无效果。 
    void reserve( size_type new_cap = 0 );


    // 请求移除未使用的保留空间。（非强制） 
    void shrink_to_fit();


    // 清空串。
    void clear();


    // 在位置 index 插入 count 个字符 ch 的副本。返回* this
    basic_string& insert( size_type index, size_type count, value_type ch );
    // 在位置 index 插入 s 所指向的以 '\0' 结尾的字符串。返回* this
    basic_string& insert( size_type index, const_pointer s );
    // 在位置 index 插入范围 [s, s+count) 中的字符。范围能含有 '\0'。返回* this
    basic_string& insert( size_type index, const_pointer s, size_type count );
    // 在位置 index 插入 str。返回* this
    basic_string& insert( size_type index, const basic_string& str );
    // 在位置 index 插入 str.substr(index_str, count)。返回* this
    basic_string& insert( size_type index, const basic_string& str, size_type index_str, size_type count );
    // 在迭代器 pos 所指向的字符前插入字符 ch。返回插入后的迭代器。
    iterator insert( iterator pos, value_type ch );
    // 在 pos 所指向的元素（若存在）前插入 count 个字符。
    void insert( iterator pos, size_type count, value_type ch );


    // 移除始于 index 的 min(count, size() - index) 个字符。返回 *this
    basic_string& erase( size_type index = 0, size_type count = npos );
    // 移除位于 position 的字符。返回移除后的迭代器
    iterator erase( iterator position );
    // 移除范围 [first, last) 中的字符。返回移除后的 last 迭代器
    iterator erase( iterator first, iterator last );


    // 附加给定字符 ch 到字符串尾。 
    void push_back( value_type ch );


    // 从字符串移除末字符。 
    void pop_back();


    /*
    统一返回 *this
    */
    // 后附 count 个 ch 的副本
    basic_string& append( size_type count, value_type ch );
    // 相当于 append(1, ch)。返回 *this
    basic_string& operator+=( value_type ch );
    // 后附 str
    basic_string& append( const basic_string& str );
    basic_string& operator+=( const basic_string& str );
    // 后附 str 的子串 [pos, pos+count) 。若请求的子串越过结尾或 count == npos，则后附的子串为 [pos, size()) 。
    basic_string& append( const basic_string& str, size_type pos, size_type count );
    // 后附范围 [s, s + count) 中的字符。此范围能含有 '\0'。
    basic_string& append( const_pointer s, size_type count );
    // 后附 s 所指向的以 '\0' 结尾的字符串。
    basic_string& append( const_pointer s );
    basic_string& operator+=( const_pointer s );


    /*
    若 *this 在字典序中先出现于参数所指定的字符序列，则返回正值。
    若两个序列比较等价则返回零。
    若 *this 在字典序中后出现于参数所指定的字符序列，则返回负值。 
    */
    // 比较此串与 str。
    int compare( const basic_string& str ) const;
    // 比较此串的 [pos1, pos1+count1) 子串与 str 。若 count1 > size() - pos1 则子串为 [pos1, size()) 。
    int compare( size_type pos1, size_type count1, const basic_string& str ) const;
    // 比较此串的 [pos1, pos1+count1) 子串与 str 的子串 [pos2, pos2+count2) 。若 count1 > size() - pos1 则第一子串为 [pos1, size()) 。类似地若 count2 > str.size() - pos2 则第二子串为 [pos2, str.size()) 。
    int compare( size_type pos1, size_type count1, const basic_string& str, size_type pos2, size_type count2 ) const;
    // 比较此串与 s
    int compare( const_pointer s ) const;
    // 见第2条重载
    int compare( size_type pos1, size_type count1, const_pointer s ) const;
    // 见第3条重载
    int compare( size_type pos1, size_type count1, const_pointer s, size_type count2 ) const;


    /*
    统一返回 *this
    */
    // 以 str 替换本串 [pos, pos + count) 部分。
    basic_string& replace( size_type pos, size_type count, const basic_string& str );
    // 以 str 替换本串 [first, last) 部分。
    basic_string& replace( const_iterator first, const_iterator last, const basic_string& str );
    // 以 str 的子串 [pos2, pos2 + count2) 替换本串 [pos, pos + count) 部分，除非 count2==npos 或它可能越过 str.size() ，则使用 [pos2, str.size()) 。
    basic_string& replace( size_type pos, size_type count, const basic_string& str, size_type pos2, size_type count2 = npos );
    // 以范围 [cstr, cstr + count2) 中的字符替换本串 [pos, pos + count) 部分。
    basic_string& replace( size_type pos, size_type count, const_pointer cstr, size_type count2 );
    // 以范围 [cstr, cstr + count2) 中的字符替换本串 [first, last) 部分。
    basic_string& replace( const_iterator first, const_iterator last, const_pointer cstr, size_type count2 );
    // 以范围 cstr 中的字符替换本串 [pos, pos + count) 部分。
    basic_string& replace( size_type pos, size_type count, const_pointer cstr );
    // 以范围 cstr 中的字符替换本串 [first, last) 部分。
    basic_string& replace( const_iterator first, const_iterator last, const_pointer cstr );
    // 以 count2 个字符 ch 替换本串 [pos, pos + count) 部分。
    basic_string& replace( size_type pos, size_type count, size_type count2, value_type ch );
    // 以 count2 个字符 ch 替换本串 [first, last) 部分。
    basic_string& replace( const_iterator first, const_iterator last, size_type count2, value_type ch );


    // 返回子串 [pos, pos+count) 。若请求的子串越过结尾或 count == npos，则返回的子串为 [pos, size()) 。 
    basic_string substr( size_type pos = 0, size_type count = npos ) const;


    // 复制子串 [pos, pos+count) 到 dest 所指向的字符串。若请求的子串越过结尾或 count == npos，则复制的子串为 [pos, size()) 。产生的字符串不是以 '\0' 终止的。 
    size_type copy( pointer dest, size_type count, size_type pos = 0 ) const;


    // 重设串大小以含 count 个字符。若当前大小小于 count ，则后附额外的字符。若当前大小大于 count，则缩减 string 到为其首 count 个元素。 前者初始化新字符为 CharT()，后者初始化新字符为 ch 。 
    void resize( size_type count );
    void resize( size_type count, value_type ch );


    // 交换 string 与 other 的内容。
    void swap( basic_string& other );


    /*
    返回找到的子串的首字符位置，或若找不到这种子串则为 npos 。 
    */
    // 寻找首个等于 str 的子串。搜索始于 pos 向后。
    size_type find( const basic_string& str, size_type pos = 0 ) const;
    // 寻找首个等于范围 [s, s+count) 的子串，此范围能含 '\0'。搜索始于 pos 向后。
    size_type find( const_pointer s, size_type pos, size_type count ) const;
    // 寻找首个等于 s 的子串。搜索始于 pos 向后。
    size_type find( const_pointer s, size_type pos = 0 ) const;
    // 寻找首个字符 ch。搜索始于 pos 向后。
    size_type find( value_type ch, size_type pos = 0 ) const;

    /*
    返回找到的子串的首字符位置，或若找不到这种子串则为 npos 。 
    */
    // 寻找最后一个等于 str 的子串。搜索始于 pos 向前。
    size_type rfind( const basic_string& str, size_type pos = npos ) const;
    // 寻找最后一个等于范围 [s, s+count) 的子串，此范围能含 '\0'。搜索始于 pos 向前。
    size_type rfind( const_pointer s, size_type pos, size_type count ) const;
    // 寻找最后一个等于范围 [s, s+count) 的子串，此范围能含 '\0'。搜索始于 pos 向前。
    size_type rfind( const_pointer s, size_type pos = npos ) const;
    // 寻找最后一个字符 ch。搜索始于 pos 向前。
    size_type rfind( value_type ch, size_type pos = npos ) const;

    /*
    返回找到的字符的位置，或若找不到这种字符则为 npos 。 
    */
    // 寻找等于 str 中字符之一的首个字符。搜索始于 pos 向后。
    size_type find_first_of( const basic_string& str, size_type pos = 0 ) const;
    // 寻找等于 [s, s+count) 中字符之一的首个字符,此范围能含 '\0'。搜索始于 pos 向后。
    size_type find_first_of( const_pointer s, size_type pos, size_type count ) const;
    // 寻找等于 s 中字符之一的首个字符。搜索始于 pos 向后。
    size_type find_first_of( const_pointer s, size_type pos = 0 ) const;
    // 寻找等于 ch 的首个字符。搜索始于 pos 向后。
    size_type find_first_of( value_type ch, size_type pos = 0 ) const;


    /*
    与上同，除了找到的是第一个不属于字符串中任意字符或特定字符。
    */
    size_type find_first_not_of( const basic_string& str, size_type pos = 0 ) const;
    size_type find_first_not_of( const_pointer s, size_type pos, size_type count ) const;
    size_type find_first_not_of( const_pointer s, size_type pos = 0 ) const;
    size_type find_first_not_of( value_type ch, size_type pos = 0 ) const;



    /*
    返回找到的字符的位置，或若找不到这种字符则为 npos 。 
    */
    // 寻找等于 str 中字符之一的最后字符。搜索始于 pos 向前。
    size_type find_last_of( const basic_string& str, size_type pos = npos ) const;
    // 寻找等于 [s, s+count) 中字符之一的最后字符,此范围能含 '\0'。搜索始于 pos 向前。
    size_type find_last_of( const_pointer s, size_type pos, size_type count ) const;
    // 寻找等于 s 中字符之一的最后字符。搜索始于 pos 向前。
    size_type find_last_of( const_pointer s, size_type pos = npos ) const;
    // 寻找等于 ch 的最后字符。搜索始于 pos 向前。
    size_type find_last_of( value_type ch, size_type pos = npos ) const;


    /*
    与上同，除了找到的是最后一个不属于字符串中任意字符或特定字符。
    */
    size_type find_last_not_of( const basic_string& str, size_type pos = npos ) const;
    size_type find_last_not_of( const_pointer s, size_type pos, size_type count ) const;
    size_type find_last_not_of( const_pointer s, size_type pos = npos ) const;
    size_type find_last_not_of( value_type ch, size_type pos = npos ) const;

};






// 函数实现








typedef basic_string<char>     c3::string;
typedef basic_string<wchar_t>  c3::wstring;
typedef basic_string<char16_t> c3::u16string;
typedef basic_string<char32_t> c3::u32string;

} // namespace c3



#endif // _C3TL_STRING_H_