/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include "common.hpp"

#include "os-win.hpp"

#include <windows.h>


namespace Vatee {

namespace Os {

namespace {

String getProgramDir_init()
{
	Char buffer[maxPathLength];
	size_t len = GetModuleFileNameW(NULL, buffer, maxPathLength);
	if (!len)
		return L".";
	Char *from = buffer, *to = buffer + len;
	assert(*to == 0);
	if (len >= rawPathPrefix.size() && std::equal(rawPathPrefix.begin(), rawPathPrefix.end(), from)) {
		from += rawPathPrefix.size();
		if (len >= rawPathUncPrefix.size() && std::equal(rawPathUncInfix.begin(), rawPathUncInfix.end(), from)) {
			// keep the leading backslashes
			from += rawPathUncInfix.size() - 2;
			*from = L'\\';
		}
	}
	return String(from, to);
}

}	// namespace


String getProgramDir()
{
	static const String dir = getProgramDir_init();
	return dir;
}
//--------------------------------------------------------------------------------------------------
// Lossy narrow
//--------------------------------------------------------------------------------------------------
char LossyNarrow::operator() (Char c) const
{
	typedef std::numeric_limits<char> limit;
	if (c > limit::max() || c < limit::min())
		return '?';
	else
		return static_cast<char>(c);
}
//--------------------------------------------------------------------------------------------------
std::string LossyNarrow::operator() (const String &string) const
{
	std::string result;
	result.reserve(string.size());
	std::transform(string.begin(), string.end(), std::back_inserter(result), *this);
	return result;
}
//--------------------------------------------------------------------------------------------------
// Conversion
//--------------------------------------------------------------------------------------------------
String convert7BitAscii(const std::string &string)
{
	String result;
	result.reserve(string.size());
	std::transform(
		begin(string), end(string), std::back_inserter(result)
		, [](char c) { return static_cast<wchar_t>(c); }
	);
	return result;
}
//--------------------------------------------------------------------------------------------------
std::string convert7BitAscii(const String &string)
{
	std::string result;
	result.reserve(string.size());
	std::transform(
		begin(string), end(string), std::back_inserter(result)
		, [](wchar_t c) { return static_cast<char>(c); }
	);
	return result;
}

}	//namespace Os

}	//namespace Vatee
