#ifndef _C3TL_ALGORITHM_H_
#define _C3TL_ALGORITHM_H_

namespace c3
{


template <class T>
void swap ( T& a, T& b );

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





template <class T>
void swap ( T& a, T& b )
{
  T c(a);
  a = b;
  b = c;
}

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








} // namespace c3

#endif // _C3TL_ALGORITHM_H_