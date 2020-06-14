//
// Created on 2020 - 06 - 03
// Written by: SYX
//

#ifndef _C3TL_STRING_H_
#define _C3TL_STRING_H_

#include <cstring>
#include <stddef.h>
#include "memory.h"
#include "iterator.h"
#include "iostream.h"

namespace c3 {

    template<class CharT, class Allocator = c3::allocator<CharT> >
    class basic_string;

    typedef basic_string<char> string;
    typedef basic_string<wchar_t> wstring;
    typedef basic_string<char16_t> u16string;
    typedef basic_string<char32_t> u32string;


    template<class CharT, class Allocator>
    class basic_string {

    public:
        typedef c3::allocator<CharT> allocator_type;
        typedef c3::allocator<CharT> data_allocator;

        typedef typename allocator_type::value_type value_type;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;

        typedef value_type *iterator;
        typedef const value_type *const_iterator;
        typedef c3::reverse_iterator<iterator> reverse_iterator;
        typedef c3::reverse_iterator<const_iterator> const_reverse_iterator;

    public:
        static const size_type npos = -1;
    private:
        pointer _data;
        size_t _size;
        Allocator _alloc;
    public:
        size_type size() const { return _size; }

        size_type length() const { return _size; }

        const_pointer data() const {
            Allocator alloc = _alloc;
            pointer r = alloc.allocate(_size + 1);
            for(size_t i=0; i<_size; ++i)
                alloc.construct(r+i, _data[i]);
            r[_size] = static_cast<value_type >(0);
            return r;
        }

        const_pointer c_str() const { return data(); }

        // 构造空串
        basic_string() {
            _size = 0;
            _data = nullptr;
            this->_alloc = Allocator();
        }

        // 构造空串，使用 alloc 作为内存分配器
        explicit basic_string(const Allocator &alloc) {
            _size = 0;
            _data = nullptr;
            this->_alloc = alloc;
        }

        // 复制构造函数
        basic_string(const basic_string &other) {
            _alloc = Allocator();
            _data = _alloc.allocate(other.size());
            _size = other.size();
            for (size_t i = 0; i < _size; i++) {
                _alloc.construct(_data + i, other.data()[i]);
            }

        }

        // 复制构造函数，使用 alloc 作为内存分配器
        basic_string(const basic_string &other, const Allocator &alloc) {
            this->_alloc = alloc;
            _data = this->_alloc.allocate(other.size());
            _size = other.size();
            for (size_t i = 0; i < _size; i++)
                _alloc.construct(_data + i, other.data()[i]);
        }

        // （可选）移动构造函数
        //
        // 'basic_string( basic_string&& other );
        // （可选）移动构造函数，使用 alloc 作为内存分配器
        // basic_string( basic_string&& other, const Allocator& alloc );
        // 构造拥有 count 个字符 ch 的串，使用 alloc 作为内存分配器
        //basic_string( size_type count, value_type ch, const Allocator& alloc = Allocator() )
        // 以 other 的子串 [pos, pos+count) 构造串。若 count == npos 或未指定 count 或越过字符串的结尾，则产生的子串为 [pos, other.size())。
        basic_string(const basic_string &other, size_type pos, size_type count = npos,
                     const Allocator &alloc = Allocator()) {
            this->_alloc = alloc;
            if (count == -1 || pos + count > other.size()) {
                _data = _alloc.allocate(other.size() - pos);
                for (int i = 0; i < other.size() - pos; i++) {
                    _alloc.construct(_data + i, other.data()[pos + i]);
                }
                _size = other.size() - pos;

            } else {
                _data = _alloc.allocate(count);
                for (int i = 0; i < count; i++) {
                    _alloc.construct(_data + i, other.data()[pos + i]);
                }
                _size = count;

            }
        }

        // 以 s 的首 count 个字符构造串。s 能包含 '\0'。串的长度为 count。若 [s, s + count) 不是合法范围则行为未定义。
        basic_string(const_pointer s, size_type count, const Allocator &alloc = Allocator()) {
            if (count < 1)return;
            else {
                this->_alloc = alloc;
                _data = _alloc.allocate(count);
                for (int i = 0; i < count; i++) {
                    _alloc.construct(_data + i, s[i]);
                }
                _size = count;
            }
        }

        // 用以 '\0' 结尾的 CharT 数组初始化串。（一般用双引号括起来的字符串初始化 string 即调用该函数）
        basic_string(const_pointer s, const Allocator &alloc = Allocator()) {
            this->_alloc = alloc;
            int count = 0;
            int i = 0;
            while (s[i] != '\0') {
                count++;
                i++;
            }
            _data = _alloc.allocate(count);
            for (int i = 0; i < count; i++) {
                _alloc.construct(_data + i, s[i]);
            }
            _size = count;
        }


        // 以 count 个 ch 替换本串。返回 *this
        basic_string &assign(size_type count, value_type ch) {
            pointer tmp = this->_alloc.allocate(count);
            if (tmp == nullptr)
                return *this;
            for (size_t i = 0; i < count; i++) {
                _alloc.construct(tmp + i, ch);
            }
            _alloc.deallocate(_data, _size);
            this->_data = tmp;
            this->_size = count;
            return *this;
        }

        // 相当于 assign(1, ch)。返回 *this
        basic_string &operator=(value_type ch) {
            pointer tmp;
            tmp = _alloc.allocate(1);
            tmp[0] = ch;
            _alloc.deallocate(_data, _size);
            _data = tmp;
            _size = 1;

        }

        // 以 str 的副本替换本串。返回 *this
        basic_string &assign(const basic_string &str) {
            _alloc.deallocate(_data, _size);
            _data = _alloc.allocate(str.size());
            for (int i = 0; i < str.size(); i++) {
                _alloc.construct(_data + i, str[i]);
            }
            _size = str.size();
            return *this;
        }

        basic_string &operator=(const basic_string &str) {
            assign(str);


        }

        // 以 str 的子串 [pos, pos+count) 替换本串。若请求的子串越过其尾或 count == npos ，则产生的子串是 [pos, str.size())。返回 *this
        basic_string &assign(const basic_string &str, size_type pos, size_type count) {
            basic_string(str, pos, count);
        }

        // （可选）移动 str 到本串。返回 *this
        // basic_string& assign( basic_string&& str );
        // basic_string& operator=( basic_string&& str );
        // 以范围 [s, s+count) 中的字符的副本替换本串。此范围能含 '\0'。返回 *this
        basic_string &assign(const_pointer s, size_type count) {
            pointer tmp;
            tmp = _alloc.allocate(count);
            for (int i = 0; i < count; i++) {
                tmp[i] = s[i];
            }
            _alloc.deallocate(_data, _size);
            _data = tmp;
            _size = count;
            return *this;
        }

        // 以 s 的副本替换本串。返回 *this
        basic_string &assign(const_pointer s) {
            pointer tmp;
            tmp = _alloc.allocate(strlen(s));
            _alloc.deallocate(_data, _size);
            for (int i = 0; i < strlen(s); i++) {
                tmp[i] = s[i];
            }
            _data = tmp;
            _size = strlen(s);
            return *this;

        }

        basic_string &operator=(const_pointer s) {
            assign(s);
            return *this;
        }


        // 返回使用的内存分配器
        Allocator get_allocator() const {
            return _alloc;
        }


        // 返回到位于指定位置 pos 的字符的引用。
        reference at(size_type pos) {
            return _data[pos];
        }

        reference operator[](size_type pos) {
            return _data[pos];
        }

        const_reference at(size_type pos) const {
            return _data[pos];
        }

        const_reference operator[](size_type pos) const {
            return _data[pos];
        }


        // 返回首字符的引用
        reference front() {
            return _data[0];
        }

        const_reference front() const {
            return _data[0];
        }


        // 返回末字符的引用
        reference back() {
            return _data[_size - 1];
        }

        const_reference back() const {
            return _data[_size - 1];
        }

        // 返回可变或常迭代器，取决于 *this 的常性。
        iterator begin() {
            return _data;
        }

        const_iterator begin() const {
            return _data;
        }


        // 返回指向字符串末字符的后一个字符的迭代器。此字符表现为占位符，试图访问它导致未定义行为。
        iterator end() {
            return _data + _size;
        }

        const_iterator end() const {
            return _data + _size;
        }


        // 返回指向逆转字符串首字符的逆向迭代器。它对应非逆向字符串的末字符。
        reverse_iterator rbegin() {
            return c3::reverse_iterator<iterator>(_data + _size);
        }


        const_reverse_iterator rbegin() const {
            return c3::reverse_iterator<iterator>(_data + _size);
        }


        // 返回指向逆转字符串末字符后一个字符的逆向迭代器。它对应非逆向字符串的首字符的前一个字符。
        reverse_iterator rend() {
            return c3::reverse_iterator<iterator>(_data);
        }

        const_reverse_iterator rend() const {
            return c3::reverse_iterator<iterator>(_data);
        }


        // 若串为空则返回 true ，否则返回 false 。
        bool empty() const {
            if (_size == 0)return true;
            else return false;
        }


        // 返回由于操作系统或库实现限制所能保有的最大串长度（一般为npos）
        size_type max_size() const {
            return npos;
        }


        // 返回当前已为串分配的保留空间的字符数。（不要与size和length混淆）
        size_type capacity() const {
            return _size;
        }


        // 重新分配串的保留空间。若 new_cap 大于当前 capacity()，则分配新存储，并令 capacity() 大于或等于 new_cap。若 new_cap 小于或等于当前 capacity()，则无效果。
        void reserve(size_type new_cap = 0);


        // 请求移除未使用的保留空间。（非强制）
        void shrink_to_fit() {

        }


        // 清空串。
        void clear() {
            _size = 0;
        }


        // 在位置 index 插入 count 个字符 ch 的副本。返回* this
        basic_string &insert(size_type index, size_type count, value_type ch) {
            pointer tmp1;
            tmp1 = _data;
            size_t length;
            length = _size;
            _alloc.deallocate(_data, _size);
            _data = _alloc.allocate(length + count);
            _size = length + count;
            for (int i = 0; i < index; i++) {
                _data[i] = tmp1[i];
            }
            for (int i = 0; i < count; i++) {
                _data[i + index] = ch;
            }
            for (int i = 0; i < length - index; i++) {
                _data[i + index + count] = tmp1[i + index];
            }
            return *this;

        }

        // 在位置 index 插入 s 所指向的以 '\0' 结尾的字符串。返回* this
        basic_string &insert(size_type index, const_pointer s) {

        }

        // 在位置 index 插入范围 [s, s+count) 中的字符。范围能含有 '\0'。返回* this
        basic_string &insert(size_type index, const_pointer s, size_type count);

        // 在位置 index 插入 str。返回* this
        basic_string &insert(size_type index, const basic_string &str);

        // 在位置 index 插入 str.substr(index_str, count)。返回* this
        basic_string &insert(size_type index, const basic_string &str, size_type index_str, size_type count);

        // 在迭代器 pos 所指向的字符前插入字符 ch。返回插入后的迭代器。
        iterator insert(iterator pos, value_type ch);

        // 在 pos 所指向的元素（若存在）前插入 count 个字符。
        void insert(iterator pos, size_type count, value_type ch);


        // 移除始于 index 的 min(count, size() - index) 个字符。返回 *this
        basic_string &erase(size_type index = 0, size_type count = npos);

        // 移除位于 position 的字符。返回移除后的迭代器
        iterator erase(iterator position);

        // 移除范围 [first, last) 中的字符。返回移除后的 last 迭代器
        iterator erase(iterator first, iterator last);


        // 附加给定字符 ch 到字符串尾。
        void push_back(value_type ch) {
            pointer tmp1;
            size_t length;
            length = _size;
            tmp1 = _data;
            _alloc.deallocate(_data, _size);
            _alloc.allocate(length + 1);
            _size = length + 1;
            for (int i = 0; i < length; i++) {
                _data[i] = tmp1[i];
            }
            _data[length] = ch;
        }


        // 从字符串移除末字符。
        void pop_back() {
            _size = _size - 1;
        }


        /*
        统一返回 *this
        */
        // 后附 count 个 ch 的副本
        basic_string &append(size_type count, value_type ch) {
            for (int i = 0; i < count; i++) {
                push_back(ch);
            }
            return *this;
        }

        // 相当于 append(1, ch)。返回 *this
        basic_string &operator+=(value_type ch) {
            push_back(ch);
            return *this;
        }

        // 后附 str
        basic_string &append(const basic_string &str) {
            pointer tmp1;
            tmp1 = _alloc.allocate(_size);
            memcpy(tmp1, _data, _size);
            _alloc.deallocate(_data, _size);
            _data = _alloc.allocate(_size + str.size());
            for (int i = 0; i < _size; i++) {
                _data[i] = tmp1[i];
            }
            for (int i = 0; i < str.size(); i++) {
                _data[_size + i] = str.data()[i];
            }
            _size = _size + str.size();
            return *this;

        }

        basic_string &operator+=(const basic_string &str) {
            append(str);
            return *this;
        }

        // 后附 str 的子串 [pos, pos+count) 。若请求的子串越过结尾或 count == npos，则后附的子串为 [pos, size()) 。
        basic_string &append(const basic_string &str, size_type pos, size_type count);

        // 后附范围 [s, s + count) 中的字符。此范围能含有 '\0'。
        basic_string &append(const_pointer s, size_type count);

        // 后附 s 所指向的以 '\0' 结尾的字符串。
        basic_string &append(const_pointer s) {
            pointer tmp1;
            tmp1 = _alloc.allocate(_size);
            memcpy(tmp1, _data, _size);
            _alloc.deallocate(_data, _size);
            _data = _alloc.allocate(_size + strlen(s));
            for (int i = 0; i < _size; i++) {
                _data[i] = tmp1[i];
            }
            for (int i = 0; i < strlen(s); i++) {
                _data[i + _size] = s[i];
            }
            _size = _size + strlen(s);
            return *this;
        }

        basic_string &operator+=(const_pointer s) {
            append(s);
            return *this;
        }


        /*
        若 *this 在字典序中先出现于参数所指定的字符序列，则返回正值。
        若两个序列比较等价则返回零。
        若 *this 在字典序中后出现于参数所指定的字符序列，则返回负值。
        */
        // 比较此串与 str。
        int compare(const basic_string &str) const;

        // 比较此串的 [pos1, pos1+count1) 子串与 str 。若 count1 > size() - pos1 则子串为 [pos1, size()) 。
        int compare(size_type pos1, size_type count1, const basic_string &str) const;

        // 比较此串的 [pos1, pos1+count1) 子串与 str 的子串 [pos2, pos2+count2) 。若 count1 > size() - pos1 则第一子串为 [pos1, size()) 。类似地若 count2 > str.size() - pos2 则第二子串为 [pos2, str.size()) 。
        int compare(size_type pos1, size_type count1, const basic_string &str, size_type pos2, size_type count2) const;

        // 比较此串与 s
        int compare(const_pointer s) const;

        // 见第2条重载
        int compare(size_type pos1, size_type count1, const_pointer s) const;

        // 见第3条重载
        int compare(size_type pos1, size_type count1, const_pointer s, size_type count2) const;


        /*
        统一返回 *this
        */
        // 以 str 替换本串 [pos, pos + count) 部分。
        basic_string &replace(size_type pos, size_type count, const basic_string &str);

        // 以 str 替换本串 [first, last) 部分。
        basic_string &replace(const_iterator first, const_iterator last, const basic_string &str);

        // 以 str 的子串 [pos2, pos2 + count2) 替换本串 [pos, pos + count) 部分，除非 count2==npos 或它可能越过 str.size() ，则使用 [pos2, str.size()) 。
        basic_string &
        replace(size_type pos, size_type count, const basic_string &str, size_type pos2, size_type count2 = npos);

        // 以范围 [cstr, cstr + count2) 中的字符替换本串 [pos, pos + count) 部分。
        basic_string &replace(size_type pos, size_type count, const_pointer cstr, size_type count2);

        // 以范围 [cstr, cstr + count2) 中的字符替换本串 [first, last) 部分。
        basic_string &replace(const_iterator first, const_iterator last, const_pointer cstr, size_type count2);

        // 以范围 cstr 中的字符替换本串 [pos, pos + count) 部分。
        basic_string &replace(size_type pos, size_type count, const_pointer cstr);

        // 以范围 cstr 中的字符替换本串 [first, last) 部分。
        basic_string &replace(const_iterator first, const_iterator last, const_pointer cstr);

        // 以 count2 个字符 ch 替换本串 [pos, pos + count) 部分。
        basic_string &replace(size_type pos, size_type count, size_type count2, value_type ch);

        // 以 count2 个字符 ch 替换本串 [first, last) 部分。
        basic_string &replace(const_iterator first, const_iterator last, size_type count2, value_type ch);


        // 返回子串 [pos, pos+count) 。若请求的子串越过结尾或 count == npos，则返回的子串为 [pos, size()) 。
        basic_string substr(size_type pos = 0, size_type count = npos) const;


        // 复制子串 [pos, pos+count) 到 dest 所指向的字符串。若请求的子串越过结尾或 count == npos，则复制的子串为 [pos, size()) 。产生的字符串不是以 '\0' 终止的。
        size_type copy(pointer dest, size_type count, size_type pos = 0) const;


        // 重设串大小以含 count 个字符。若当前大小小于 count ，则后附额外的字符。若当前大小大于 count，则缩减 string 到为其首 count 个元素。 前者初始化新字符为 CharT()，后者初始化新字符为 ch 。
        void resize(size_type count);

        void resize(size_type count, value_type ch);


        // 交换 string 与 other 的内容。
        void swap(basic_string &other);


        /*
        返回找到的子串的首字符位置，或若找不到这种子串则为 npos 。
        */
        // 寻找首个等于 str 的子串。搜索始于 pos 向后。
        size_type find(const basic_string &str, size_type pos = 0) const;

        // 寻找首个等于范围 [s, s+count) 的子串，此范围能含 '\0'。搜索始于 pos 向后。
        size_type find(const_pointer s, size_type pos, size_type count) const;

        // 寻找首个等于 s 的子串。搜索始于 pos 向后。
        size_type find(const_pointer s, size_type pos = 0) const;

        // 寻找首个字符 ch。搜索始于 pos 向后。
        size_type find(value_type ch, size_type pos = 0) const;

        /*
        返回找到的子串的首字符位置，或若找不到这种子串则为 npos 。
        */
        // 寻找最后一个等于 str 的子串。搜索始于 pos 向前。
        size_type rfind(const basic_string &str, size_type pos = npos) const;

        // 寻找最后一个等于范围 [s, s+count) 的子串，此范围能含 '\0'。搜索始于 pos 向前。
        size_type rfind(const_pointer s, size_type pos, size_type count) const;

        // 寻找最后一个等于范围 [s, s+count) 的子串，此范围能含 '\0'。搜索始于 pos 向前。
        size_type rfind(const_pointer s, size_type pos = npos) const;

        // 寻找最后一个字符 ch。搜索始于 pos 向前。
        size_type rfind(value_type ch, size_type pos = npos) const;

        /*
        返回找到的字符的位置，或若找不到这种字符则为 npos 。
        */
        // 寻找等于 str 中字符之一的首个字符。搜索始于 pos 向后。
        size_type find_first_of(const basic_string &str, size_type pos = 0) const;

        // 寻找等于 [s, s+count) 中字符之一的首个字符,此范围能含 '\0'。搜索始于 pos 向后。
        size_type find_first_of(const_pointer s, size_type pos, size_type count) const;

        // 寻找等于 s 中字符之一的首个字符。搜索始于 pos 向后。
        size_type find_first_of(const_pointer s, size_type pos = 0) const;

        // 寻找等于 ch 的首个字符。搜索始于 pos 向后。
        size_type find_first_of(value_type ch, size_type pos = 0) const;


        /*
        与上同，除了找到的是第一个不属于字符串中任意字符或特定字符。
        */
        size_type find_first_not_of(const basic_string &str, size_type pos = 0) const;

        size_type find_first_not_of(const_pointer s, size_type pos, size_type count) const;

        size_type find_first_not_of(const_pointer s, size_type pos = 0) const;

        size_type find_first_not_of(value_type ch, size_type pos = 0) const;



        /*
        返回找到的字符的位置，或若找不到这种字符则为 npos 。
        */
        // 寻找等于 str 中字符之一的最后字符。搜索始于 pos 向前。
        size_type find_last_of(const basic_string &str, size_type pos = npos) const;

        // 寻找等于 [s, s+count) 中字符之一的最后字符,此范围能含 '\0'。搜索始于 pos 向前。
        size_type find_last_of(const_pointer s, size_type pos, size_type count) const;

        // 寻找等于 s 中字符之一的最后字符。搜索始于 pos 向前。
        size_type find_last_of(const_pointer s, size_type pos = npos) const;

        // 寻找等于 ch 的最后字符。搜索始于 pos 向前。
        size_type find_last_of(value_type ch, size_type pos = npos) const;

        /*
        与上同，除了找到的是最后一个不属于字符串中任意字符或特定字符。
        */
        size_type find_last_not_of(const basic_string &str, size_type pos = npos) const;

        size_type find_last_not_of(const_pointer s, size_type pos, size_type count) const;

        size_type find_last_not_of(const_pointer s, size_type pos = npos) const;

        size_type find_last_not_of(value_type ch, size_type pos = npos) const;

        template< class _CharT, class _Alloc >
        friend c3::basic_string<_CharT,_Alloc> operator+( const c3::basic_string<_CharT,_Alloc>& lhs, const c3::basic_string<_CharT,_Alloc>& rhs )
        {
            basic_string s(lhs);
            s.append(rhs);
            return s;
        }

        template<class _CharT, class _Alloc>
        friend c3::basic_string<_CharT, _Alloc>
        operator+(const c3::basic_string<_CharT, _Alloc> &lhs, const _CharT *rhs)
        {
            basic_string s(lhs);
            s.append(rhs);
            return s;
        }

        template<class _CharT, class _Alloc>
        friend c3::basic_string<_CharT, _Alloc> operator+(const c3::basic_string<_CharT, _Alloc> &lhs, _CharT rhs) ;
        //template< class _CharT, class _Alloc >
        //friend c3::basic_string<_CharT,_Alloc> operator+( const _CharT* lhs, const c3::basic_string<_CharT,_Alloc>& rhs );
        //template< class _CharT, class _Alloc >
        //friend c3::basic_string<_CharT,_Alloc> operator+( _CharT lhs, const c3::basic_string<_CharT,_Alloc>& rhs );

        // 按照字典顺序比较字符串中的值
        //template< class _CharT, class _Alloc >
        //friend bool operator==( const c3::basic_string<_CharT,_Alloc>& lhs, const c3::basic_string<_CharT,_Alloc>& rhs );
        //template< class _CharT, class _Alloc >
        //friend bool operator==( const c3::basic_string<_CharT,_Alloc>& lhs, const _CharT* rhs );
        //template< class _CharT, class _Alloc >
        //friend bool operator!=( const c3::basic_string<_CharT,_Alloc>& lhs, const c3::basic_string<_CharT,_Alloc>& rhs );
        //template< class _CharT, class _Alloc >
        //friend bool operator!=( const c3::basic_string<_CharT,_Alloc>& lhs, const _CharT* rhs );
        //template< class _CharT, class _Alloc >
        //friend bool operator<( const c3::basic_string<_CharT,_Alloc>& lhs, const c3::basic_string<_CharT,_Alloc>& rhs );
        //template< class _CharT, class _Alloc >
        //friend bool operator<( const c3::basic_string<_CharT,_Alloc>& lhs, const _CharT* rhs );
        //template< class _CharT, class _Alloc >
        //friend bool operator<=( const c3::basic_string<_CharT,_Alloc>& lhs, const c3::basic_string<_CharT,_Alloc>& rhs );
        //template< class _CharT, class _Alloc >
        //friend bool operator<=( const c3::basic_string<_CharT,_Alloc>& lhs, const _CharT* rhs );
        //template< class _CharT, class _Alloc >
        //friend bool operator>( const c3::basic_string<_CharT,_Alloc>& lhs, const c3::basic_string<_CharT,_Alloc>& rhs );
        //template< class _CharT, class _Alloc >
        //friend bool operator>( const c3::basic_string<_CharT,_Alloc>& lhs, const _CharT* rhs );
        //template< class _CharT, class _Alloc >
        //friend bool operator>=( const c3::basic_string<_CharT,_Alloc>& lhs, const c3::basic_string<_CharT,_Alloc>& rhs );
        //template< class _CharT, class _Alloc >
        //friend bool operator>=( const c3::basic_string<_CharT,_Alloc>& lhs, const _CharT* rhs );

        template<class _CharT, class _Alloc>
        friend c3::basic_ostream<_CharT> &
        operator<<(c3::basic_ostream<_CharT> &os, const c3::basic_string<_CharT, _Alloc> &str) {
            os << str.c_str();
            return os;
        }

        //template <class _CharT, class _Alloc>
        //friend c3::basic_istream<_CharT>& operator>>(c3::basic_istream<_CharT>& is, c3::basic_string<_CharT, _Alloc>& str);

        //template< class _CharT, class _Alloc >
        //friend c3::basic_istream<_CharT>& getline( c3::basic_istream<_CharT>& input, c3::basic_string<_CharT, _Alloc>& str, _CharT delim );

        // 转译字符串 str 中的有符号整数值。
        // 舍弃所有空白符（以调用 isspace() 鉴别），直到找到首个非空白符，然后取尽可能多的字符组成底 n （其中 n=base ）的整数表示，并将它们转换成一个整数值。合法的整数值由下列部分组成：
        //  (可选)正或负号
        //  (可选)指示八进制底的前缀（ 0 ）（仅当底为 8 或 ​0​ 时应用）
        //  (可选)指示十六进制底的前缀（ 0x 或 0X ）（仅当底为 16 或 ​0​ 时应用）
        //  一个数字序列
        // 底的合法集是 {0,2,3,...,36} 。合法数字集对于底 2 整数是 {0,1}，对于底3整数是 {0,1,2} ，以此类推。对于大于 10 的底，合法数字包含字母字符，从对于底 11 整数的 Aa 到对于底36整数的 Zz 。忽略字符大小写。
        // 若 base 为 ​0​ ，则自动检测数值进制：若前缀为 0 ，则底为八进制，若前缀为 0x 或 0X ，则底为十六进制，否则底为十进制。
        // 若 pos 不是空指针，则对于转换函数为内部的指针 ptr 将接受 str.c_str() 中首个未转换字符的地址，然后计算该字符的下标并存储之于 *pos ，给出转换处理的字符数。
        //friend int stoi( const c3::string& str, size_t* pos = 0, int base = 10 );
        //friend int stoi( const c3::wstring& str, size_t* pos = 0, int base = 10 );
        //friend long stol( const c3::string& str, size_t* pos = 0, int base = 10 );
        //friend long stol( const c3::wstring& str, size_t* pos = 0, int base = 10 );
        //friend long long stoll( const c3::string& str, size_t* pos = 0, int base = 10 );
        //friend long long stoll( const c3::wstring& str, size_t* pos = 0, int base = 10 );

        // 转译字符串 str 中的无符号整数值。
        //friend unsigned long stoul( const c3::string& str, size_t* pos = 0, int base = 10 );
        //friend unsigned long stoul( const c3::wstring& str, size_t* pos = 0, int base = 10 );
        //friend unsigned long long stoull( const c3::string& str, size_t* pos = 0, int base = 10 );
        //friend unsigned long long stoull( const c3::wstring& str, size_t* pos = 0, int base = 10 );

        // 转译字符串 str 中的浮点值。
        // 函数会舍弃任何空白符（由 c3::isspace() 确定），直至找到首个非空白符。然后它会取用尽可能多的字符，以构成合法的浮点数表示，并将它们转换成浮点值。合法的浮点值可以为下列之一：
        //     十进制浮点数表达式。它由下列部分组成：
        //         (可选) 正或负号
        //         非空的十进制数字序列，可选地包含一个小数点字符（由当前的 C 本地环境确定）（定义有效数字）
        //         (可选) e 或 E ，并跟随可选的正或负号，以及非空十进制数字序列（以 10 为底定义指数）
        //     二进制浮点数表达式。它由下列部分组成：
        //         (可选) 正或负号
        //         0x 或 0X
        //         非空的十六进制数字序列，选地包含一个小数点字符（由当前的 C 本地环境确定）（定义有效数字）
        //         (可选) p 或 P ，并跟随可选的正或负号，以及非空十进制数字序列（以 2 为底定义指数）
        //     无穷大表达式。它由下列部分组成：
        //         (可选) 正或负号
        //         INF 或 INFINITY ，忽略大小写
        //     非数（NaN）表达式。它由下列部分组成：
        //         (可选) 正或负号
        //         NAN 或 NAN(char_sequence) ，忽略 NAN 部分的大小写。 char_sequence 只能由数字、拉丁字母和下划线构成。结果是一个安静的 NaN 浮点值。
        // 若 pos 不是空指针，则对于转换函数为内部的指针 ptr 将接受 str.c_str() 中首个未转换字符的地址，然后计算该字符的下标并存储之于 *pos ，给出转换处理的字符数。
        /*friend float stof( const c3::string& str, size_t* pos = 0 );
        friend float stof( const c3::wstring& str, size_t* pos = 0 );
        friend double stod( const c3::string& str, size_t* pos = 0 );
        friend double stod( const c3::wstring& str, size_t* pos = 0 );
        friend long double stold( const c3::string& str, size_t* pos = 0 );
        friend long double stold( const c3::wstring& str, size_t* pos = 0 );

        // 将数转换成 char 字符串
        friend c3::string to_string( int value );
        friend c3::string to_string( long value );
        friend c3::string to_string( long long value );
        friend c3::string to_string( unsigned value );
        friend c3::string to_string( unsigned long value );
        friend c3::string to_string( unsigned long long value );
        friend c3::string to_string( float value );
        friend c3::string to_string( double value );
        friend c3::string to_string( long double value );

        // 将数转换成 wchar_t 字符串
        friend c3::wstring to_wstring( int value );
        friend c3::wstring to_wstring( long value );
        friend c3::wstring to_wstring( long long value );
        friend c3::wstring to_wstring( unsigned value );
        friend c3::wstring to_wstring( unsigned long value );
        friend c3::wstring to_wstring( unsigned long long value );
        friend c3::wstring to_wstring( float value );
        friend c3::wstring to_wstring( double value );
        friend c3::wstring to_wstring( long double value );*/
    };







// 函数实现










    // namespace c3



#endif // _C3TL_STRING_H_
}