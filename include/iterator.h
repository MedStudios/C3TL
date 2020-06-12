//
// Created on 2020 - 06 - 05
// Written by: TSH
//

#ifndef _C3TL_ITERATOR_H_
#define _C3TL_ITERATOR_H_

#include <iterator>

namespace c3
{

// 未实现部分的重定向
template <typename T>
using reverse_iterator = std::reverse_iterator<T>;

} // namespace c3

#endif // _C3TL_ITERATOR_H_
