#ifndef _C3TL_IOSTREAM_H_
#define _C3TL_IOSTREAM_H_

#include <iostream>

namespace c3
{

// 未实现部分的重定向

template <class T>
using basic_istream = std::basic_istream<T>;
template <class T>
using basic_ostream = std::basic_ostream<T>;

using istream = std::istream;
using ostream = std::ostream;
using wistream = std::wistream;
using wostream = std::wostream;

istream cin = std::cin;
ostream cout = std::cout;
ostream cerr = std::cerr;
ostream clog = std::clog;

wistream wcin = std::wcin;
wostream wcout =  std::wcout;
wostream wcerr = std::wcerr;
wostream wclog = std::wclog;

} // namespace c3

#endif // _C3TL_IOSTREAM_H_