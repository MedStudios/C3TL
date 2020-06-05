#ifndef _C3TL_IOSTREAM_H_
#define _C3TL_IOSTREAM_H_

#include <iostream>

namespace c3
{

// 未实现部分的重定向
typedef std::istream    istream;
typedef std::ostream    ostream;
typedef std::wistream   wistream;
typedef std::wostream   wostream;

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