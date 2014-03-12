/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#pragma once


namespace Vatee {

#ifdef OS_WIN
typedef wchar_t OsChar;

#define OS_LIT(x) L##x
#else
typedef char OsChar;

#define OS_LIT(x) x
#endif


typedef std::basic_string<OsChar> OsString;

}	// namespace Vatee
