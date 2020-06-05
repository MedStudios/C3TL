#ifndef _C3TL_IOSTREAM_H_
#define _C3TL_IOSTREAM_H_

#include <iostream>

namespace c3
{

// 未实现部分的重定向
typedef istream    std::istream;
typedef ostream    std::ostream;
typedef wistream   std::wistream;
typedef wostream   std::wostream;

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