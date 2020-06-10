#ifndef _C3TL_ALGORITHM_H_
#define _C3TL_ALGORITHM_H_

#include "utility.h"

namespace c3
{

// C++11 起 swap 函数定义于 <utility>
// 
// template <class T>
// void swap ( T& a, T& b );

template< class RandomIt >
void sort( RandomIt first, RandomIt last );
template< class RandomIt, class Compare >
void sort( RandomIt first, RandomIt last, Compare comp );

template< class RandomIt >
void partial_sort( RandomIt first, RandomIt middle, RandomIt last );
template< class RandomIt, class Compare >
void partial_sort( RandomIt first, RandomIt middle, RandomIt last, Compare comp );

template< class InputIt, class RandomIt >
RandomIt partial_sort_copy( InputIt first, InputIt last, RandomIt d_first, RandomIt d_last );
template< class InputIt, class RandomIt, class Compare >
RandomIt partial_sort_copy( InputIt first, InputIt last, RandomIt d_first, RandomIt d_last, Compare comp );

template< class ForwardIt >
bool is_sorted( ForwardIt first, ForwardIt last );
template< class ForwardIt, class Compare >
bool is_sorted( ForwardIt first, ForwardIt last, Compare comp );

template< class ForwardIt >
ForwardIt is_sorted_until( ForwardIt first, ForwardIt last );
template< class ForwardIt, class Compare >
ForwardIt is_sorted_until( ForwardIt first, ForwardIt last, Compare comp );


template< class ForwardIt, class T >
ForwardIt lower_bound( ForwardIt first, ForwardIt last, const T& value );
template< class ForwardIt, class T, class Compare >
ForwardIt lower_bound( ForwardIt first, ForwardIt last, const T& value, Compare comp );

template< class ForwardIt, class T >
ForwardIt upper_bound( ForwardIt first, ForwardIt last, const T& value );
template< class ForwardIt, class T, class Compare >
ForwardIt upper_bound( ForwardIt first, ForwardIt last, const T& value, Compare comp );

template< class ForwardIt, class T >
bool binary_search( ForwardIt first, ForwardIt last, const T& value );
template< class ForwardIt, class T, class Compare >
bool binary_search( ForwardIt first, ForwardIt last, const T& value, Compare comp );

template< class InputIt1, class InputIt2, class OutputIt >
OutputIt merge( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first );
template< class InputIt1, class InputIt2, class OutputIt, class Compare>
OutputIt merge( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp );

template< class BidirIt >
void inplace_merge( BidirIt first, BidirIt middle, BidirIt last );
template< class BidirIt, class Compare>
void inplace_merge( BidirIt first, BidirIt middle, BidirIt last, Compare comp );


template< class T >
const T& max( const T& a, const T& b );
template< class T, class Compare >
const T& max( const T& a, const T& b, Compare comp );

template< class T >
const T& min( const T& a, const T& b );
template< class T, class Compare >
const T& min( const T& a, const T& b, Compare comp );



/*
template <class T>
inline void swap ( T& a, T& b )
{
  T c(a);
  a = b;
  b = c;
}
*/

template< class RandomIt >
void sort(RandomIt first, RandomIt last)
{
    if (first >= last)
        return;
    else
    {
        RandomIt ps = first;  //ps指向第一个元素
        RandomIt pe = last - 1;  //pe指向倒数第二个元素
        while (ps < pe)
        {
            while (*ps < *first) && ps < pe)  //右移
            {
                ++ps;
            }
            while (*ps >= *first && ps < pe)  //左移
            {
                --pe;
            }

            if (ps < pe) {
                swap(*ps, *pe);
            }
        }
        if (*pe < *first)
            swap(*first, *pe);
        sort(first, pe);
        sort(pe, last);
    }
}

template< class RandomIt, class Compare >
void sort( RandomIt first, RandomIt last, Compare comp )
{
    if (first >= last)
        return;
    else
    {
        RandomIt ps = first;  //ps指向第一个元素
        RandomIt pe = last - 1;  //pe指向倒数第二个元素
        while (ps < pe)
        {
            while (comp(*ps, *first) && ps < pe)  //右移
            {
                ++ps;
            }
            while (!comp(*ps, *first) && ps < pe)  //左移
            {
                --pe;
            }

            if (ps < pe) {
                swap(*ps, *pe);
            }
        }
        if (comp(*pe, *first))
            swap(*first, *pe);
        sort(first, pe);
        sort(pe, last);
    }
}

template< class RandomIt >
void partial_sort(RandomIt first, RandomIt middle, RandomIt last)  
{
    sort(first, last);
}

template< class RandomIt, class Compare >
void partial_sort( RandomIt first, RandomIt middle, RandomIt last, Compare comp )
{
    sort(first, last, comp);
}

template< class InputIt, class RandomIt >
RandomIt partial_sort_copy(InputIt first, InputIt last, RandomIt d_first, RandomIt d_last)
{
    if (last - first != d_last - d_first)
        return d_first;
    memcpy(d_first, first, sizeof(*first) * (last - first));
    sort(d_first, d_last);
    return d_last;
}

template< class InputIt, class RandomIt, class Compare >
RandomIt partial_sort_copy( InputIt first, InputIt last, RandomIt d_first, RandomIt d_last, Compare comp )
{
    if (last - first != d_last - d_first)
        return d_first;
    memcpy(d_first, first, sizeof(*first) * (last - first));
    sort(d_first, d_last, comp);
    return d_last;
}

template< class RandomIt >
bool is_sorted(RandomIt first, RandomIt last)
{
    return is_sorted_until(first, last) == last;
}

template< class RandomIt, class Compare >
bool is_sorted(RandomIt first, RandomIt last, Compare comp)
{
    return is_sorted_until(first, last, comp) == last;
}

template< class RandomIt >
RandomIt is_sorted_until(RandomIt first, RandomIt last)
{
    if (first == NULL || last == NULL || last >= first)
        return first;
    for (RandomIt p = first; p != last - 1; ++p)
    {
        if (*p > *(p + 1))
        {
            return p + 1;
        }
    }
    return last;
}

template< class RandomIt, class Compare >
RandomIt is_sorted_until(RandomIt first, RandomIt last, Compare comp)
{
    if (first == NULL || last == NULL || last >= first)
        return first;
    for (RandomIt p = first; p != last - 1; ++p)
    {
        if (comp(*p, *(p + 1)) || *p == *(p + 1))
        {
            continue;
        }
        return p + 1;
    }
    return last;
}



template< class ForwardIt, class T >
ForwardIt lower_bound( ForwardIt first, ForwardIt last, const T& value ) {
    if (last <= first)
        return false;

    unsigned int lo = 0;
    unsigned int hi = last - first - 1;
    unsigned int pos = hi + 1; //所求值在数组中的位置
    while (lo < hi)
    {
		unsigned int mid = (lo + hi) / 2;
        if (first[mid] < value)
            lo = mid + 1;
        else
			hi = mid;
        pos = lo;
    }
    return first + pos;
}

template< class ForwardIt, class T, class Compare >
ForwardIt lower_bound( ForwardIt first, ForwardIt last, const T& value, Compare comp ) {
    if (last <= first)
        return false;

    unsigned int lo = 0;
    unsigned int hi = last - first - 1;
    unsigned int pos = hi + 1; //所求值在数组中的位置
    while (lo < hi)
    {
		unsigned int mid = (lo + hi) / 2;
        if (comp(first[mid], value))
            lo = mid + 1;
        else
			hi = mid;
        pos = lo;
    }
    return first + pos;
}

template< class ForwardIt, class T >
ForwardIt upper_bound( ForwardIt first, ForwardIt last, const T& value ) {
    if (last <= first)
        return false;

    unsigned int lo = 0;
    unsigned int hi = last - first - 1;
    unsigned int pos = hi + 1; //所求值在数组中的位置
    while (lo < hi)
    {
		unsigned int mid = (lo + hi) / 2;
        if (first[mid] <= value)
            lo = mid + 1;
        else
			hi = mid;
        pos = lo;
    }
    return first + pos;
}
template< class ForwardIt, class T, class Compare >
ForwardIt upper_bound( ForwardIt first, ForwardIt last, const T& value, Compare comp ) {
    if (last <= first)
        return false;

    unsigned int lo = 0;
    unsigned int hi = last - first - 1;
    unsigned int pos = hi + 1; //所求值在数组中的位置
    while (lo < hi)
    {
		unsigned int mid = (lo + hi) / 2;
        if (comp(first[mid], value) || first[mid] == value)
            lo = mid + 1;
        else
			hi = mid;
        pos = lo;
    }
    return first + pos;
}
template< class ForwardIt, class T >
bool binary_search( ForwardIt first, ForwardIt last, const T& value ) {
    if (last <= first)
        return false;

    unsigned int lo = 0;
    unsigned int hi = (unsigned int)(last - first - 1);
    while (lo < hi)
    {
		unsigned int mid = (lo + hi) / 2;
        if (first[mid] <= value)
            lo = mid + 1;
        else
			hi = mid;
        pos = lo;
    }
    if (first[lo] == value)
        return true;
    else
        return false;
}

template< class ForwardIt, class T, class Compare >
bool binary_search( ForwardIt first, ForwardIt last, const T& value, Compare comp ) {
    if (last <= first)
        return false;

    unsigned int lo = 0;
    unsigned int hi = last - first - 1;
    while (lo < hi)
    {
        unsigned int mid = (lo + hi) / 2;
        if ( comp(first[mid], value) )
            lo = mid + 1;
        else
            hi = mid;
    }
    if (first[lo] == value)
        return true;
    else
        return false;
}

template< class InputIt1, class InputIt2, class OutputIt >
OutputIt merge( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first ) {
    OutputIt itd = d_first;
    InputIt1 it1 = first1, it2 = first2;
    while(true) {
        if (it1 == last1) {
            while (it2 != last2)
                *(itd++) = *(it2++);
            break;
        }
        if (it2 == last2) {
            while (it1 != last1)
                *(itd++) = *(it1++);
            break;
        }
        if (*it1 < *it2) {
            *itd = *it1;
            ++it1;
        }
        else {
            *itd = *it2;
            ++it2;
        }
        ++itd;
    }
    return itd;
}

template< class InputIt1, class InputIt2, class OutputIt, class Compare>
OutputIt merge( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp ) {
    OutputIt itd = d_first;
    InputIt1 it1 = first1, it2 = first2;
    while(true) {
        if (it1 == last1) {
            while (it2 != last2)
                *(itd++) = *(it2++);
            break;
        }
        if (it2 == last2) {
            while (it1 != last1)
                *(itd++) = *(it1++);
            break;
        }
        if ( comp(*it1, *it2) ) {
            *itd = *it1;
            ++it1;
        }
        else {
            *itd = *it2;
            ++it2;
        }
        ++itd;
    }
    return itd;
}

template< class BidirIt >
void inplace_merge( BidirIt first, BidirIt middle, BidirIt last ) {
    sort( first, last );
}

template< class BidirIt, class Compare>
void inplace_merge( BidirIt first, BidirIt middle, BidirIt last, Compare comp ) {
    sort( first, last, comp );
}


template< class T >
inline const T& max( const T& a, const T& b ) {
    return (a < b) ? b : a;
}
template< class T, class Compare >
inline const T& max( const T& a, const T& b, Compare comp ) {
    return comp(a, b) ? b : a;
}

template< class T >
inline const T& min( const T& a, const T& b ) {
    return (a < b) ? a : b;
}
template< class T, class Compare >
inline const T& min( const T& a, const T& b, Compare comp ) {
    return comp(a, b) ? a : b;
}





} // namespace c3

#endif // _C3TL_ALGORITHM_H_