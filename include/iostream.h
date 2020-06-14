//
// Created on 2020 - 06 - 05
// Written by: TSH
//


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

istream cin(std::cin.rdbuf());
ostream cout(std::cout.rdbuf());
ostream cerr(std::cerr.rdbuf());
ostream clog(std::clog.rdbuf());

wistream wcin(std::wcin.rdbuf());
wostream wcout(std::wcout.rdbuf());
wostream wcerr(std::wcerr.rdbuf());
wostream wclog(std::wclog.rdbuf());

template< class CharT >
c3::basic_ostream<CharT>& endl( c3::basic_ostream<CharT>& os ) {
    return std::endl(os);
}
	
template< class CharT >
c3::basic_ostream<CharT>& flush( c3::basic_ostream<CharT>& os ) {
    return std::flush(os);
}
	

} // namespace c3

#endif // _C3TL_IOSTREAM_H_
