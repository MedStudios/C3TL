//
// Created on 2020 - 06 - 11
// Written by: TSH
//

#ifndef _C3TL_UTILITY_H_
#define _C3TL_UTILITY_H_

#include <utility>

namespace c3
{

template <class T>
using remove_reference = std::remove_reference<T>;




template <class T>
void swap ( T& a, T& b );

template< class T >
typename remove_reference<T>::type&& move( T&& t ) noexcept;



template< class T >
typename remove_reference<T>::type&& move( T&& t ) noexcept {
   	return std::move(t);
}

template <class T>
void swap ( T& a, T& b ) {
  T c(c3::move(a));
  a = c3::move(b);
  b = c3::move(c);
}

} // namespace c3


#endif // _C3TL_UTILITY_H_