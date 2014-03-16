/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#pragma once


namespace Vatee {

namespace Os {

#ifdef OS_WIN
typedef wchar_t Char;

	#define OS_LIT(x) L##x
#else
typedef char Char;

	#define OS_LIT(x) x
#endif


typedef std::basic_string<Char> String;


String getProgramDir();

}	// namespace Os

}	// namespace Vatee
