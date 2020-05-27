# C3TL Todo-list

### 原则 

- 代码复用原则，灵活使用已经写好的基础函数，例如
  >写 `void pop_back() { erase(end() - 1, 1); }` 
  >
  >而不是再实现一遍 `erase(end() - 1, 1)`
  >
  >写 `bool operator==( const T& lhs, const T& rhs ) { return lhs.compare(rhs); }`
  > 
  >而不是再具体实现 `lhs.compare(rhs)`
  > `

### 说明
- API 列表中，紧挨着的没有注释隔开的两行或多行函数，是功能等价的，可以只实现一遍然后复用

### 操作
- 已经实现的且待测试的 API 函数，请在函数前加上 `[testing needed]`
- 已测试的功能正常的 API 函数，请注释起来
- 有问题的或实现遇到困难的 API 函数，请在请在函数前加上 `[!!!!!]`

### `c3::allocator` @ `<memory>`

模板定义：
```cpp
template < class T >
struct allocator;
```
API：
```cpp
allocator();
allocator( const allocator& other );
~allocator();

// 为 n 个 T 类型对象的数组分配内存，返回首指针.
T* allocate( size_t n );

// 解分配 p 所引用的 T 类型对象的数组，p 须是通过先前调用 allocate 获得的指针，n 须为调用时的参数。
void deallocate( T* p, size_t n );

// 在 p 所指的未初始化内存中构造 T 类型对象。
void construct( T* p, cosnt T& val );

// 析构在已分配 p 中的对象
void destroy( T* p );
```

## `c3::cin` @ `<iostream>`
重定向到 `std::cin`

## `c3::cout` @ `<iostream>`
重定向到 `std::cout`

## `c3::reverse_iterator` @ `<iterator>`
重定向到 `std::reverse_iterator`

## `c3::basic_string` @ `<string>`

模板定义：
```cpp
template <
    class CharT,    // 字符串的字符类型
    class Allocator = c3::allocator<CharT>     // 所使用的分配器类型
> class basic_string;
```

### `c3::basic_string::iterator`
```cpp
iterator( CharT* p = nullptr );
CharT operator*() const;
CharT* operator->() const;
iterator& operator++();
iterator operator++(int);
bool operator==(const iterator &arg) const;
bool operator!=(const iterator &arg) const;
```
### `c3::basic_string::const_iterator`
```cpp
const_iterator( CharT* p = nullptr );
const CharT operator*() const;
const CharT* operator->() const;
const_iterator& operator++();
const_iterator operator++(int);
bool operator==(const const_iterator &arg) const;
bool operator!=(const const_iterator &arg) const;
```

API：
```cpp
typedef c3::string     c3::basic_string<char>
typedef c3::wstring    c3::basic_string<wchar_t>
typedef c3::u16string  c3::basic_string<char16_t>
typedef c3::u32string  c3::basic_string<char32_t>
typedef reverse_iterator c3::reverse_iterator<iterator>
typedef const_reverse_iterator c3::reverse_iterator<const_iterator>


// 表示 size_t 类型的最大值。准确含义依赖于语境。
static const size_t npos = -1;		


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
basic_string( size_t count, CharT ch, const Allocator& alloc = Allocator() );
// 以 other 的子串 [pos, pos+count) 构造串。若 count == npos 或未指定 count 或越过字符串的结尾，则产生的子串为 [pos, other.size())。
basic_string( const basic_string& other, size_t pos, size_t count = c3::basic_string::npos, const Allocator& alloc = Allocator() );
// 以 s 的首 count 个字符构造串。s 能包含 '\0'。串的长度为 count。若 [s, s + count) 不是合法范围则行为未定义。
basic_string( const CharT* s, size_t count, const Allocator& alloc = Allocator() );
// 用以 '\0' 结尾的 CharT 数组初始化串。（一般用双引号括起来的字符串初始化 string 即调用该函数）
basic_string( const CharT* s, const Allocator& alloc = Allocator() );


// 以 count 个 ch 替换本串。返回 *this
basic_string& assign( size_t count, CharT ch );
// 相当于 assign(1, ch)。返回 *this
basic_string& operator=( CharT ch );
// 以 str 的副本替换本串。返回 *this
basic_string& assign( const basic_string& str );
basic_string& operator=( const basic_string& str );
// 以 str 的子串 [pos, pos+count) 替换本串。若请求的子串越过其尾或 count == npos ，则产生的子串是 [pos, str.size())。返回 *this
basic_string& assign( const basic_string& str, size_t pos, size_t count );
// （可选）移动 str 到本串。返回 *this
// basic_string& assign( basic_string&& str );
// basic_string& operator=( basic_string&& str );
// 以范围 [s, s+count) 中的字符的副本替换本串。此范围能含 '\0'。返回 *this
basic_string& assign( const CharT* s, size_t count );
// 以 s 的副本替换本串。返回 *this
basic_string& assign( const CharT* s );
basic_string& operator=( const CharT* s );


// 返回使用的内存分配器
Allocator get_allocator() const;


// 返回到位于指定位置 pos 的字符的引用。
ChatT& at( size_t pos );
ChatT& operator[]( size_t pos );
const ChatT& at( size_t pos ) const;
const ChatT& operator[]( size_t pos ) const;


// 返回首字符的引用
CharT& front();
const CharT& front() const;


// 返回末字符的引用
CharT& back();
const CharT& back() const;


// 返回字符串的不可修改的原生字符数组。
const CharT* data() const;
const CharT* c_str() const;


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
size_t size() const;
size_t length() const;


// 返回由于操作系统或库实现限制所能保有的最大串长度（一般为npos）
size_t max_size() const;


// 返回当前已为串分配的保留空间的字符数。（不要与size和length混淆）
size_t capacity() const;


// 重新分配串的保留空间。若 new_cap 大于当前 capacity()，则分配新存储，并令 capacity() 大于或等于 new_cap。若 new_cap 小于或等于当前 capacity()，则无效果。 
void reserve( size_t new_cap = 0 );


// 请求移除未使用的保留空间。（非强制） 
void shrink_to_fit();


// 清空串。
void clear();


// 在位置 index 插入 count 个字符 ch 的副本。返回* this
basic_string& insert( size_t index, size_t count, CharT ch );
// 在位置 index 插入 s 所指向的以 '\0' 结尾的字符串。返回* this
basic_string& insert( size_t index, const CharT* s );
// 在位置 index 插入范围 [s, s+count) 中的字符。范围能含有 '\0'。返回* this
basic_string& insert( size_t index, const CharT* s, size_t count );
// 在位置 index 插入 str。返回* this
basic_string& insert( size_t index, const basic_string& str );
// 在位置 index 插入 str.substr(index_str, count)。返回* this
basic_string& insert( size_t index, const basic_string& str, size_t index_str, size_t count );
// 在迭代器 pos 所指向的字符前插入字符 ch。返回插入后的迭代器。
iterator insert( iterator pos, CharT ch );
// 在 pos 所指向的元素（若存在）前插入 count 个字符。
void insert( iterator pos, size_t count, CharT ch );


// 移除始于 index 的 min(count, size() - index) 个字符。返回 *this
basic_string& erase( size_t index = 0, size_t count = npos );
// 移除位于 position 的字符。返回移除后的迭代器
iterator erase( iterator position );
// 移除范围 [first, last) 中的字符。返回移除后的 last 迭代器
iterator erase( iterator first, iterator last );


// 附加给定字符 ch 到字符串尾。 
void push_back( CharT ch );


// 从字符串移除末字符。 
void pop_back();


/*
统一返回 *this
*/
// 后附 count 个 ch 的副本
basic_string& append( size_t count, CharT ch );
// 相当于 append(1, ch)。返回 *this
basic_string& operator+=( CharT ch );
// 后附 str
basic_string& append( const basic_string& str );
basic_string& operator+=( const basic_string& str );
// 后附 str 的子串 [pos, pos+count) 。若请求的子串越过结尾或 count == npos，则后附的子串为 [pos, size()) 。
basic_string& append( const basic_string& str, size_t pos, size_t count );
// 后附范围 [s, s + count) 中的字符。此范围能含有 '\0'。
basic_string& append( const CharT* s, size_t count );
// 后附 s 所指向的以 '\0' 结尾的字符串。
basic_string& append( const CharT* s );
basic_string& operator+=( const CharT* s );


/*
若 *this 在字典序中先出现于参数所指定的字符序列，则返回正值。
若两个序列比较等价则返回零。
若 *this 在字典序中后出现于参数所指定的字符序列，则返回负值。 
*/
// 比较此串与 str。
int compare( const basic_string& str ) const;
// 比较此串的 [pos1, pos1+count1) 子串与 str 。若 count1 > size() - pos1 则子串为 [pos1, size()) 。
int compare( size_t pos1, size_t count1, const basic_string& str ) const;
// 比较此串的 [pos1, pos1+count1) 子串与 str 的子串 [pos2, pos2+count2) 。若 count1 > size() - pos1 则第一子串为 [pos1, size()) 。类似地若 count2 > str.size() - pos2 则第二子串为 [pos2, str.size()) 。
int compare( size_t pos1, size_t count1, const basic_string& str, size_t pos2, size_t count2 ) const;
// 比较此串与 s
int compare( const CharT* s ) const;
// 见第2条重载
int compare( size_t pos1, size_t count1, const CharT* s ) const;
// 见第3条重载
int compare( size_t pos1, size_t count1, const CharT* s, size_t count2 ) const;


/*
统一返回 *this
*/
// 以 str 替换本串 [pos, pos + count) 部分。
basic_string& replace( size_t pos, size_t count, const basic_string& str );
// 以 str 替换本串 [first, last) 部分。
basic_string& replace( const_iterator first, const_iterator last, const basic_string& str );
// 以 str 的子串 [pos2, pos2 + count2) 替换本串 [pos, pos + count) 部分，除非 count2==npos 或它可能越过 str.size() ，则使用 [pos2, str.size()) 。
basic_string& replace( size_t pos, size_t count, const basic_string& str, size_t pos2, size_t count2 = npos );
// 以范围 [cstr, cstr + count2) 中的字符替换本串 [pos, pos + count) 部分。
basic_string& replace( size_t pos, size_t count, const CharT* cstr, size_t count2 );
// 以范围 [cstr, cstr + count2) 中的字符替换本串 [first, last) 部分。
basic_string& replace( const_iterator first, const_iterator last, const CharT* cstr, size_t count2 );
// 以范围 cstr 中的字符替换本串 [pos, pos + count) 部分。
basic_string& replace( size_t pos, size_t count, const CharT* cstr );
// 以范围 cstr 中的字符替换本串 [first, last) 部分。
basic_string& replace( const_iterator first, const_iterator last, const CharT* cstr );
// 以 count2 个字符 ch 替换本串 [pos, pos + count) 部分。
basic_string& replace( size_t pos, size_t count, size_t count2, CharT ch );
// 以 count2 个字符 ch 替换本串 [first, last) 部分。
basic_string& replace( const_iterator first, const_iterator last, size_t count2, CharT ch );


// 返回子串 [pos, pos+count) 。若请求的子串越过结尾或 count == npos，则返回的子串为 [pos, size()) 。 
basic_string substr( size_t pos = 0, size_t count = npos ) const;


// 复制子串 [pos, pos+count) 到 dest 所指向的字符串。若请求的子串越过结尾或 count == npos，则复制的子串为 [pos, size()) 。产生的字符串不是以 '\0' 终止的。 
size_t copy( CharT* dest, size_t count, size_t pos = 0 ) const;


// 重设串大小以含 count 个字符。若当前大小小于 count ，则后附额外的字符。若当前大小大于 count，则缩减 string 到为其首 count 个元素。 前者初始化新字符为 CharT()，后者初始化新字符为 ch 。 
void resize( size_t count );
void resize( size_t count, CharT ch );


// 交换 string 与 other 的内容。
void swap( basic_string& other );


/*
返回找到的子串的首字符位置，或若找不到这种子串则为 npos 。 
*/
// 寻找首个等于 str 的子串。搜索始于 pos 向后。
size_t find( const basic_string& str, size_t pos = 0 ) const;
// 寻找首个等于范围 [s, s+count) 的子串，此范围能含 '\0'。搜索始于 pos 向后。
size_t find( const CharT* s, size_t pos, size_t count ) const;
// 寻找首个等于 s 的子串。搜索始于 pos 向后。
size_t find( const CharT* s, size_t pos = 0 ) const;
// 寻找首个字符 ch。搜索始于 pos 向后。
size_t find( CharT ch, size_t pos = 0 ) const;

/*
返回找到的子串的首字符位置，或若找不到这种子串则为 npos 。 
*/
// 寻找最后一个等于 str 的子串。搜索始于 pos 向前。
size_t rfind( const basic_string& str, size_t pos = npos ) const;
// 寻找最后一个等于范围 [s, s+count) 的子串，此范围能含 '\0'。搜索始于 pos 向前。
size_t rfind( const CharT* s, size_t pos, size_t count ) const;
// 寻找最后一个等于范围 [s, s+count) 的子串，此范围能含 '\0'。搜索始于 pos 向前。
size_t rfind( const CharT* s, size_t pos = npos ) const;
// 寻找最后一个字符 ch。搜索始于 pos 向前。
size_t rfind( CharT ch, size_t pos = npos ) const;

/*
返回找到的字符的位置，或若找不到这种字符则为 npos 。 
*/
// 寻找等于 str 中字符之一的首个字符。搜索始于 pos 向后。
size_t find_first_of( const basic_string& str, size_t pos = 0 ) const;
// 寻找等于 [s, s+count) 中字符之一的首个字符,此范围能含 '\0'。搜索始于 pos 向后。
size_t find_first_of( const CharT* s, size_t pos, size_t count ) const;
// 寻找等于 s 中字符之一的首个字符。搜索始于 pos 向后。
size_t find_first_of( const CharT* s, size_t pos = 0 ) const;
// 寻找等于 ch 的首个字符。搜索始于 pos 向后。
size_t find_first_of( CharT ch, size_t pos = 0 ) const;


/*
与上同，除了找到的是第一个不属于字符串中任意字符或特定字符。
*/
size_t find_first_not_of( const basic_string& str, size_t pos = 0 ) const;
size_t find_first_not_of( const CharT* s, size_t pos, size_t count ) const;
size_t find_first_not_of( const CharT* s, size_t pos = 0 ) const;
size_t find_first_not_of( CharT ch, size_t pos = 0 ) const;



/*
返回找到的字符的位置，或若找不到这种字符则为 npos 。 
*/
// 寻找等于 str 中字符之一的最后字符。搜索始于 pos 向前。
size_t find_last_of( const basic_string& str, size_t pos = npos ) const;
// 寻找等于 [s, s+count) 中字符之一的最后字符,此范围能含 '\0'。搜索始于 pos 向前。
size_t find_last_of( const CharT* s, size_t pos, size_t count ) const;
// 寻找等于 s 中字符之一的最后字符。搜索始于 pos 向前。
size_t find_last_of( const CharT* s, size_t pos = npos ) const;
// 寻找等于 ch 的最后字符。搜索始于 pos 向前。
size_t find_last_of( CharT ch, size_t pos = npos ) const;


/*
与上同，除了找到的是最后一个不属于字符串中任意字符或特定字符。
*/
size_t find_last_not_of( const basic_string& str, size_t pos = npos ) const;
size_t find_last_not_of( const CharT* s, size_t pos, size_t count ) const;
size_t find_last_not_of( const CharT* s, size_t pos = npos ) const;
size_t find_last_not_of( CharT ch, size_t pos = npos ) const;
```

友元函数：
```cpp
template< class CharT, class Alloc >
c3::basic_string<CharT,Alloc> operator+( const c3::basic_string<CharT,Alloc>& lhs, const c3::basic_string<CharT,Alloc>& rhs );

template< class CharT, class Alloc >
c3::basic_string<CharT,Alloc> operator+( const c3::basic_string<CharT,Alloc>& lhs, const CharT* rhs );

template<class CharT, class Alloc>
c3::basic_string<CharT,Alloc> operator+( const c3::basic_string<CharT,Alloc>& lhs, CharT rhs );

template< class CharT, class Alloc >
c3::basic_string<CharT,Alloc> operator+( const CharT* lhs, const c3::basic_string<CharT,Alloc>& rhs );

template< class CharT, class Alloc >
c3::basic_string<CharT,Alloc> operator+( CharT lhs, const c3::basic_string<CharT,Alloc>& rhs );

/**
//（可选)
template< class CharT, class Alloc >
td::basic_string<CharT,Alloc> operator+( c3::basic_string<CharT,Alloc>&& lhs, c3::basic_string<CharT,Alloc>&& rhs );

template< class CharT, class Alloc >
c3::basic_string<CharT,Alloc> operator+( c3::basic_string<CharT,Alloc>&& lhs, const c3::basic_string<CharT,Alloc>& rhs );

template< class CharT, class Alloc >
c3::basic_string<CharT,Alloc> operator+( c3::basic_string<CharT,Alloc>&& lhs, const CharT* rhs );

template< class CharT, class Alloc >
c3::basic_string<CharT,Alloc> operator+( c3::basic_string<CharT,Alloc>&& lhs, CharT rhs );

template< class CharT, class Alloc >
c3::basic_string<CharT,Alloc> operator+( const c3::basic_string<CharT,Alloc>& lhs, c3::basic_string<CharT,Alloc>&& rhs );

template< class CharT, class Alloc >
c3::basic_string<CharT,Alloc> operator+( const CharT* lhs, c3::basic_string<CharT,Alloc>&& rhs );

template< class CharT, class Alloc >
c3::basic_string<CharT,Alloc> operator+( CharT lhs, c3::basic_string<CharT,Alloc>&& rhs );
*/



// 按照字典顺序比较字符串中的值 
template< class CharT, class Alloc >
bool operator==( const c3::basic_string<CharT,Alloc>& lhs, const c3::basic_string<CharT,Alloc>& rhs );

template< class CharT, class Alloc >
bool operator==( const c3::basic_string<CharT,Alloc>& lhs, const CharT* rhs );

template< class CharT, class Alloc >
bool operator!=( const c3::basic_string<CharT,Alloc>& lhs, const c3::basic_string<CharT,Alloc>& rhs );

template< class CharT, class Alloc >
bool operator!=( const c3::basic_string<CharT,Alloc>& lhs, const CharT* rhs );

template< class CharT, class Alloc >
bool operator<( const c3::basic_string<CharT,Alloc>& lhs, const c3::basic_string<CharT,Alloc>& rhs );

template< class CharT, class Alloc >
bool operator<( const c3::basic_string<CharT,Alloc>& lhs,
                const CharT* rhs );

template< class CharT, class Alloc >
bool operator<=( const c3::basic_string<CharT,Alloc>& lhs, const c3::basic_string<CharT,Alloc>& rhs );

template< class CharT, class Alloc >
bool operator<=( const c3::basic_string<CharT,Alloc>& lhs, const CharT* rhs );

template< class CharT, class Alloc >
bool operator>( const c3::basic_string<CharT,Alloc>& lhs, const c3::basic_string<CharT,Alloc>& rhs );

template< class CharT, class Alloc >
bool operator>( const c3::basic_string<CharT,Alloc>& lhs, const CharT* rhs );

template< class CharT, class Alloc >
bool operator>=( const c3::basic_string<CharT,Alloc>& lhs, const c3::basic_string<CharT,Alloc>& rhs );

template< class CharT, class Alloc >
bool operator>=( const c3::basic_string<CharT,Alloc>& lhs, const CharT* rhs );




template <class CharT, class Allocator>
c3::basic_ostream<CharT>& operator<<(c3::basic_ostream<CharT>& os, const c3::basic_string<CharT, Allocator>& str);

template <class CharT, class Traits, class Allocator>
c3::basic_istream<CharT>& operator>>(c3::basic_istream<CharT>& is,  c3::basic_string<CharT, Allocator>& str);





template< class CharT, class Allocator >
c3::basic_istream<CharT>& getline( c3::basic_istream<CharT>& input, c3::basic_string<CharT,Allocator>& str, CharT delim );



// 转译字符串 str 中的有符号整数值。
// 舍弃所有空白符（以调用 isspace() 鉴别），直到找到首个非空白符，然后取尽可能多的字符组成底 n （其中 n=base ）的整数表示，并将它们转换成一个整数值。合法的整数值由下列部分组成： 
//  (可选)正或负号
//  (可选)指示八进制底的前缀（ 0 ）（仅当底为 8 或 ​0​ 时应用）
//  (可选)指示十六进制底的前缀（ 0x 或 0X ）（仅当底为 16 或 ​0​ 时应用） 
//  一个数字序列 
// 底的合法集是 {0,2,3,...,36} 。合法数字集对于底 2 整数是 {0,1}，对于底3整数是 {0,1,2} ，以此类推。对于大于 10 的底，合法数字包含字母字符，从对于底 11 整数的 Aa 到对于底36整数的 Zz 。忽略字符大小写。 
// 若 base 为 ​0​ ，则自动检测数值进制：若前缀为 0 ，则底为八进制，若前缀为 0x 或 0X ，则底为十六进制，否则底为十进制。
// 若 pos 不是空指针，则对于转换函数为内部的指针 ptr 将接受 str.c_str() 中首个未转换字符的地址，然后计算该字符的下标并存储之于 *pos ，给出转换处理的字符数。 
int stoi( const c3::string& str, size_t* pos = 0, int base = 10 );
int stoi( const c3::wstring& str, size_t* pos = 0, int base = 10 );
long stol( const c3::string& str, size_t* pos = 0, int base = 10 );
long stol( const c3::wstring& str, size_t* pos = 0, int base = 10 );
long long stoll( const c3::string& str, size_t* pos = 0, int base = 10 );
long long stoll( const c3::wstring& str, size_t* pos = 0, int base = 10 );


// 转译字符串 str 中的无符号整数值。
unsigned long stoul( const c3::string& str, c3::size_t* pos = 0, int base = 10 );
unsigned long stoul( const c3::wstring& str, c3::size_t* pos = 0, int base = 10 );
unsigned long long stoull( const c3::string& str, c3::size_t* pos = 0, int base = 10 );
unsigned long long stoull( const c3::wstring& str, c3::size_t* pos = 0, int base = 10 );


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
float stof( const c3::string& str, size_t* pos = 0 );
float stof( const c3::wstring& str, size_t* pos = 0 );
double stod( const c3::string& str, size_t* pos = 0 );
double stod( const c3::wstring& str, size_t* pos = 0 );
long double stold( const c3::string& str, size_t* pos = 0 );
long double stold( const c3::wstring& str, size_t* pos = 0 );



// 将数转换成 char 字符串
c3::string to_string( int value );
c3::string to_string( long value );
c3::string to_string( long long value );
c3::string to_string( unsigned value );
c3::string to_string( unsigned long value );
c3::string to_string( unsigned long long value );
c3::string to_string( float value );
c3::string to_string( double value );
c3::string to_string( long double value );


// 将数转换成 wchar_t 字符串
c3::wstring to_wstring( int value );
c3::wstring to_wstring( long value );
c3::wstring to_wstring( long long value );
c3::wstring to_wstring( unsigned value );
c3::wstring to_wstring( unsigned long value );
c3::wstring to_wstring( unsigned long long value );
c3::wstring to_wstring( float value );
c3::wstring to_wstring( double value );
c3::wstring to_wstring( long double value );
```

## `c3::vector` @ `<vector>`

模板定义：
```cpp
template<
    class T,
    class Allocator = c3::allocator<T>
> class vector;
```

API：
```cpp
// 构造空的 vector
vector();
// 构造空的 vector，使用 alloc 作为内存分配器
explicit vector( const Allocator& alloc );
// 复制构造函数
vector( const vector& other );
// 复制构造函数，使用 alloc 作为内存分配器
vector( const vector& other, const Allocator& alloc );
// 构造拥有个 count 默认 T 实例的容器。不进行复制。使用 alloc 作为内存分配器
explicit vector( size_t count, const Allocator& alloc = Allocator() );
// 构造拥有 count 个 value 的元素的容器。使用 alloc 作为内存分配器
vector( size_t count, const T& value, const Allocator& alloc = Allocator());
// （可选）vector( vector&& other );
// （可选）vector( vector&& other, const Allocator& alloc );


// 销毁 vector 。调用每个元素的析构函数，然后解分配所用的存储。注意，若元素是指针，则不销毁所指向的对象。 
~vector();


// 复制赋值运算符。以 other 的副本替换内容。
vector& operator=( const vector& other );
// 移动赋值运算符。
// （可选）vector& operator=( vector&& other );


// 以 count 个 value 替换 vector 的内容。
void assign( size_t count, const T& value );


// 返回与容器关联的分配器。 
Allocator get_allocator() const;


// 返回位于指定位置 pos 的元素的引用，有边界检查。 
T& at( size_t pos );
T& operator[]( size_t pos );
const T& at( size_t pos ) const;
const T& operator[]( size_t pos ) const;



// 返回容器首元素的引用。在空容器上对 front 的调用是未定义的。 
T& front();
const T& front() const;


// 返回容器末元素的引用。在空容器上对 back 的调用是未定义的。 
T& back();
const T& back() const;

// 返回指向作为元素存储工作的底层数组的指针。指针满足范围 [data(); data() + size()) 始终是合法范围，即使容器为空（该情况下 data() 不可解引用）。
T* data() noexcept;
const T* data() const noexcept;


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
size_t size() const;


// 返回由于操作系统或库实现限制所能保有的最大容器长度
size_t max_size() const;


// 返回当前已为容器分配的保留空间的元素数。（不要与size和length混淆）
size_t capacity() const;


// 重新分配容器的保留空间。若 new_cap 大于当前 capacity()，则分配新存储，并令 capacity() 大于或等于 new_cap。若 new_cap 小于或等于当前 capacity()，则无效果。 
void reserve( size_t new_cap = 0 );


// 请求移除未使用的保留空间。（非强制） 
void shrink_to_fit();


// 清空容器。
void clear();


// 在 pos 前插入 value 。
iterator insert( const_iterator pos, const T& value );
// （可选）iterator insert( const_iterator pos, T&& value );
// 在 pos 前插入 count 个 value 。
iterator insert( const_iterator pos, size_t count, const T& value );

// 移除位于 pos 的元素。
iterator erase( const_iterator pos );
// 移除范围 [first; last) 中的元素。
iterator erase( const_iterator first, const_iterator last );


// 后附给定元素 value 到容器尾。 
void push_back( const T& value );
// （可选）void push_back( T&& value );


// 移除容器的最末元素。在空容器上调用 pop_back 是未定义的。 
void pop_back();


// 若当前大小大于 count ，则减小容器为其首 count 个元素。若当前大小小于 count， 则后附额外的默认插入的元素。
void resize( size_t count );// 若当前大小大于 count ，则减小容器为其首 count 个元素。若当前大小小于 count， 则后附额外的 value 的副本。
void resize( size_t count, const T& value );



// 将内容与 other 的交换。不在单个元素上调用任何移动、复制或交换操作。 
void swap( vector& other );
```

友元函数：
```cpp
// 检查 lhs 与 rhs 的内容是否相等，即它们是否拥有相同数量的元素且 lhs 中每个元素与 rhs 的同位置元素比较相等。
template< class T, class Alloc >
bool operator==( const c3::vector<T,Alloc>& lhs, const c3::vector<T,Alloc>& rhs );
template< class T, class Alloc >
bool operator!=( const c3::vector<T,Alloc>& lhs, const c3::vector<T,Alloc>& rhs );

// 按字典序比较 lhs 与 rhs 的内容。
template< class T, class Alloc >
bool operator<( const c3::vector<T,Alloc>& lhs, const c3::vector<T,Alloc>& rhs );
template< class T, class Alloc >
bool operator<=( const c3::vector<T,Alloc>& lhs, const c3::vector<T,Alloc>& rhs );
template< class T, class Alloc >
bool operator>( const c3::vector<T,Alloc>& lhs, const c3::vector<T,Alloc>& rhs );
template< class T, class Alloc >
bool operator>=( const c3::vector<T,Alloc>& lhs, const c3::vector<T,Alloc>& rhs );
```



## `c3::deque` @ `<deque>`

> 注：`deque` 是双向队列，两端都支持插入和弹出操作，这说明 `deque` 同时支持 FIFO 的队列操作和 LIFO 的栈操作，STL 中将其封装成为单独的 `stack` 类模板和 `queue` 类模板。

模板定义：
```cpp
template<
    class T,
    class Allocator = c3::allocator<T>
> class deque;
```

API：
```cpp
// 构造空的 deque
deque();
// 构造空的 deque，使用 alloc 作为内存分配器
explicit deque( const Allocator& alloc );
// 复制构造函数
deque( const deque& other );
// 复制构造函数，使用 alloc 作为内存分配器
deque( const deque& other, const Allocator& alloc );
// 构造拥有个 count 默认 T 实例的容器。不进行复制。使用 alloc 作为内存分配器
explicit deque( size_t count, const Allocator& alloc = Allocator() );
// 构造拥有 count 个 value 的元素的容器。使用 alloc 作为内存分配器
deque( size_t count, const T& value, const Allocator& alloc = Allocator());
// （可选）deque( deque&& other );
// （可选）deque( deque&& other, const Allocator& alloc );


// 销毁 deque 。调用每个元素的析构函数，然后解分配所用的存储。注意，若元素是指针，则不销毁所指向的对象。 
~deque();


// 复制赋值运算符。以 other 的副本替换内容。
deque& operator=( const deque& other );
// 移动赋值运算符。
// （可选）deque& operator=( deque&& other );


// 以 count 个 value 替换 deque 的内容。
void assign( size_t count, const T& value );


// 返回与容器关联的分配器。 
Allocator get_allocator() const;


// 返回位于指定位置 pos 的元素的引用，有边界检查。 
T& at( size_t pos );
T& operator[]( size_t pos );
const T& at( size_t pos ) const;
const T& operator[]( size_t pos ) const;



// 返回容器首元素的引用。在空容器上对 front 的调用是未定义的。 
T& front();
const T& front() const;


// 返回容器末元素的引用。在空容器上对 back 的调用是未定义的。 
T& back();
const T& back() const;


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
size_t size() const;


// 返回由于操作系统或库实现限制所能保有的最大容器长度
size_t max_size() const;


// 请求移除未使用的保留空间。（非强制） 
void shrink_to_fit();


// 清空容器。
void clear();


// 在 pos 前插入 value 。
iterator insert( const_iterator pos, const T& value );
// （可选）iterator insert( const_iterator pos, T&& value );
// 在 pos 前插入 count 个 value 。
iterator insert( const_iterator pos, size_t count, const T& value );


// 移除位于 pos 的元素。
iterator erase( const_iterator pos );
// 移除范围 [first; last) 中的元素。
iterator erase( const_iterator first, const_iterator last );


// 后附给定元素 value 到容器尾。 
void push_back( const T& value );
// （可选）void push_back( T&& value );


// 移除容器的最末元素。在空容器上调用 pop_back 是未定义的。 
void pop_back();


// 前附给定元素 value 到容器尾。 
void push_front( const T& value );
// （可选）void push_front( T&& value );


// 移除容器的首元素。在空容器上调用 pop_back 是未定义的。 
void pop_front();



// 若当前大小大于 count ，则减小容器为其首 count 个元素。若当前大小小于 count， 则后附额外的默认插入的元素。
void resize( size_t count );// 若当前大小大于 count ，则减小容器为其首 count 个元素。若当前大小小于 count， 则后附额外的 value 的副本。
void resize( size_t count, const T& value );



// 将内容与 other 的交换。不在单个元素上调用任何移动、复制或交换操作。 
void swap( deque& other );
```

友元函数：
```cpp
// 检查 lhs 与 rhs 的内容是否相等，即它们是否拥有相同数量的元素且 lhs 中每个元素与 rhs 的同位置元素比较相等。
template< class T, class Alloc >
bool operator==( const c3::deque<T,Alloc>& lhs, const c3::deque<T,Alloc>& rhs );
template< class T, class Alloc >
bool operator!=( const c3::deque<T,Alloc>& lhs, const c3::deque<T,Alloc>& rhs );

// 按字典序比较 lhs 与 rhs 的内容。
template< class T, class Alloc >
bool operator<( const c3::deque<T,Alloc>& lhs, const c3::deque<T,Alloc>& rhs );
template< class T, class Alloc >
bool operator<=( const c3::deque<T,Alloc>& lhs, const c3::deque<T,Alloc>& rhs );
template< class T, class Alloc >
bool operator>( const c3::deque<T,Alloc>& lhs, const c3::deque<T,Alloc>& rhs );
template< class T, class Alloc >
bool operator>=( const c3::deque<T,Alloc>& lhs, const c3::deque<T,Alloc>& rhs );
```



## `c3::stack` @ `<stack>`

模板定义：
```cpp
template<
    class T,
    class Container = std::deque<T>
> class stack;
```
> 注：`stack` 类模板是 `Container` 类的封装，其中 `Container` 通常且默认是 `deque` ——即， `stack` 是 `deque` 作为一个**栈**单独实现的一个类模板。 `stack` 的 API 可以完全基于 `deque`，不过 `deque` 作为栈不允许的操作不会在 `stack` 中得到定义。 

成员对象：
```cpp
protected:
    Container c;    // 底层容器，默认为一个 deque
```

API:

```cpp
// 默认构造函数。值初始化容器。
stack() : stack(Container()) { }
//  以 cont 的内容复制构造底层容器 c 。
explicit stack( const Container& cont );
// （可选）explicit stack( Container&& cont );
// 复制构造函数
stack( const stack& other );
// 移动构造函数
// （可选）stack( stack&& other );


// 销毁 stack 。调用每个元素的析构函数，然后解分配所用的存储。注意，若元素是指针，则不销毁所指向的对象。 
~stack();
	

// 复制赋值运算符。返回 *this
stack& operator=( const stack& other );
// 移动赋值运算符。返回 *this
// （可选）stack& operator=( stack&& other );

// 返回 stack 中顶元素的引用。它是最近推入的元素。此元素将在调用 pop() 时被移除。等效于调用 c.back() 。 
T& top();
const T& top() const;
		

// 即调用 c.empty() 。
bool empty() const;


// 即调用 c.size() 。
size_t size() const;


// 即调用 c.push_back(value) ：后附给定元素 value 到栈尾。 
void push( const T& value );
// （可选）void push_back( T&& value );


// 即调用 c.pop_back(value) 移除容器的最末元素。
void pop();


// 将内容与 other 的交换。
void swap( stack& other );
```


友元函数：
```cpp
// 检查 lhs 与 rhs 的内容是否相等，即它们是否拥有相同数量的元素且 lhs 中每个元素与 rhs 的同位置元素比较相等。
template< class T, class Alloc >
bool operator==( const c3::stack<T,Alloc>& lhs, const c3::stack<T,Alloc>& rhs );
template< class T, class Alloc >
bool operator!=( const c3::stack<T,Alloc>& lhs, const c3::stack<T,Alloc>& rhs );

// 按字典序比较 lhs 与 rhs 的内容。
template< class T, class Alloc >
bool operator<( const c3::stack<T,Alloc>& lhs, const c3::stack<T,Alloc>& rhs );
template< class T, class Alloc >
bool operator<=( const c3::stack<T,Alloc>& lhs, const c3::stack<T,Alloc>& rhs );
template< class T, class Alloc >
bool operator>( const c3::stack<T,Alloc>& lhs, const c3::stack<T,Alloc>& rhs );
template< class T, class Alloc >
bool operator>=( const c3::stack<T,Alloc>& lhs, const c3::stack<T,Alloc>& rhs );
```



## `<algorithm>`

API:
```cpp
// 以不降序排序范围 [first, last) 中的元素。
// 用 operator< 比较元素。
template< class RandomIt >
void sort( RandomIt first, RandomIt last );
// 用给定的二元比较函数 comp 比较元素。
template< class RandomIt, class Compare >
void sort( RandomIt first, RandomIt last, Compare comp );

// 重排元素，使得范围 [first, middle) 含有范围 [first, last) 中已排序的 middle - first 个最小元素。 
// 用 operator< 比较元素。
template< class RandomIt >
void partial_sort( RandomIt first, RandomIt middle, RandomIt last );
// 用给定的二元比较函数 comp 比较元素。
template< class RandomIt, class Compare >
void partial_sort( RandomIt first, RandomIt middle, RandomIt last, Compare comp );


// 以升序排序范围 [first, last) 中的某些元素，存储结果于范围 [d_first, d_last) 。 
template< class InputIt, class RandomIt >
RandomIt partial_sort_copy( InputIt first, InputIt last, RandomIt d_first, RandomIt d_last );
template< class InputIt, class RandomIt, class Compare >
RandomIt partial_sort_copy( InputIt first, InputIt last, RandomIt d_first, RandomIt d_last, Compare comp );


// 检查 [first, last) 中的元素是否以不降序排序。 
// 用 operator< 比较元素。
template< class ForwardIt >
bool is_sorted( ForwardIt first, ForwardIt last );
// 用给定的二元比较函数 comp 比较元素。
template< class ForwardIt, class Compare >
bool is_sorted( ForwardIt first, ForwardIt last, Compare comp );


// 检验范围 [first, last) ，返回始于 first 且其中元素已以升序排序的最大范围的最后迭代器。 
// 用 operator< 比较元素。
template< class ForwardIt >
ForwardIt is_sorted_until( ForwardIt first, ForwardIt last );
// 用给定的二元比较函数 comp 比较元素。
template< class ForwardIt, class Compare >
ForwardIt is_sorted_until( ForwardIt first, ForwardIt last, Compare comp );


// 二分搜索，返回指向范围 [first, last) 中首个不小于（即大于或等于） value 的元素的迭代器，若找不到这种元素则返回 last
// 用 operator< 比较元素
template< class ForwardIt, class T >
ForwardIt lower_bound( ForwardIt first, ForwardIt last, const T& value );
// 用给定的比较函数 comp 。
template< class ForwardIt, class T, class Compare >
ForwardIt lower_bound( ForwardIt first, ForwardIt last, const T& value, Compare comp );


// 二分搜索，返回指向范围 [first, last) 中首个大于 value 的元素的迭代器，若找不到这种元素则返回 last
// 用 operator< 比较元素
template< class ForwardIt, class T >
ForwardIt upper_bound( ForwardIt first, ForwardIt last, const T& value );
// 用给定的比较函数 comp 。
template< class ForwardIt, class T, class Compare >
ForwardIt upper_bound( ForwardIt first, ForwardIt last, const T& value, Compare comp );


// 二分搜索，若等价于 value 的元素出现于范围 [first, last) 中则返回 true，否则返回 false。 
// 用 operator< 比较元素
template< class ForwardIt, class T >
bool binary_search( ForwardIt first, ForwardIt last, const T& value );
// 用给定的比较函数 comp
template< class ForwardIt, class T, class Compare >
bool binary_search( ForwardIt first, ForwardIt last, const T& value, Compare comp );


// 归并二个已排序范围 [first1, last1) 和 [first2, last2) 到始于 d_first 的一个已排序范围中。
// 用 operator< 比较元素
template< class InputIt1, class InputIt2, class OutputIt >
OutputIt merge( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first );
// 用给定的比较函数 comp
template< class InputIt1, class InputIt2, class OutputIt, class Compare>
OutputIt merge( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp );


// 归并二个相继的已排序范围 [first, middle) 及 [middle, last) 为一个已排序范围 [first, last) 。 
// 用 operator< 比较元素
template< class BidirIt >
void inplace_merge( BidirIt first, BidirIt middle, BidirIt last );
// 用给定的比较函数 comp
template< class BidirIt, class Compare>
void inplace_merge( BidirIt first, BidirIt middle, BidirIt last, Compare comp );


// 返回给定值中的较大者。 
// 用 operator< 比较元素
template< class T >
const T& max( const T& a, const T& b );
// 用给定的比较函数 comp
template< class T, class Compare >
const T& max( const T& a, const T& b, Compare comp );


// 返回给定值中的较小者。 
// 用 operator< 比较元素
template< class T >
const T& min( const T& a, const T& b );
// 用给定的比较函数 comp
template< class T, class Compare >
const T& min( const T& a, const T& b, Compare comp );


// 寻找范围 [first, last) 中的最大元素。 
// 用 operator< 比较元素
template< class ForwardIt >
ForwardIt max_element(ForwardIt first, ForwardIt last );
// 用给定的比较函数 comp
template< class ForwardIt, class Compare >
ForwardIt max_element(ForwardIt first, ForwardIt last, Compare comp );


// 寻找范围 [first, last) 中的最小元素。 
// 用 operator< 比较元素
template< class ForwardIt >
ForwardIt min_element(ForwardIt first, ForwardIt last );
// 用给定的比较函数 comp
template< class ForwardIt, class Compare >
ForwardIt min_element(ForwardIt first, ForwardIt last, Compare comp );


// 检查第一个范围 [first1, last1) 是否按字典序小于第二个范围 [first2, last2) 。 
template< class InputIt1, class InputIt2 >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 );
template< class InputIt1, class InputIt2, class Compare >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp );


// 变换范围 [first, last) 为来自所有按相对于 operator< 或 comp 的字典序的下个排列。若这种排列存在则返回 true ，否则变换范围为首个排列，并返回 false 。 
template< class BidirIt >
bool next_permutation( BidirIt first, BidirIt last );
template< class BidirIt, class Compare >
bool next_permutation( BidirIt first, BidirIt last, Compare comp );


// 变换范围 [first, last) 为来自所有按相对于 operator< 或 comp 的字典序的上个排列。若这种排列存在则返回 true ，否则变换范围为末排列，并返回 false 。 
template< class BidirIt >
bool prev_permutation( BidirIt first, BidirIt last );
template< class BidirIt, class Compare >
bool prev_permutation( BidirIt first, BidirIt last, Compare comp );
```

### 使用例：

#### `sort` 和 `binary_search`：
```cpp
#include <algorithm>

bool comp (int a, int b)
{
    return a > b; //降序排列，如果改为 return a < b，则为升序
}

int main()
{
    int a[10];
    for(int i = 0; i < 10; ++i)
        cin >> a[i];

    c3::sort(a, a + 10);  // 升序
    cout << "Integer 5 found? " << c3::binary_search(a, a + 10, 5) << endl;

    for(int i = 0; i < 10; ++i)
        cout << a[i] << ' ';
    cout << endl;

    c3::sort(a, a + 10, comp); // 降序
    cout << "Integer 5 found? " << c3::binary_search(a, a + 10, 5, comp); // 使用和 sort 一致的比较函数

    for(int i = 0; i < 10; ++i)
        cout << a[i] << ' ';
    cout << endl;
    return 0;
}
```