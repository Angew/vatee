/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include "common.hpp"

#include "config.hpp"


namespace Vatee {

std::string Config::getSourceDir() const
{
	return VATEE_GENERATOR_DEFAULT_SOURCE_DIR;
}
//--------------------------------------------------------------------------------------------------
std::string Config::getDestDir() const
{
	return VATEE_GENERATOR_DEFAULT_DEST_DIR;
}
//--------------------------------------------------------------------------------------------------
Config::NewlineStyle Config::getNewlineInput() const
{
	return Newline_Any;
}
//--------------------------------------------------------------------------------------------------
Config::NewlineStyle Config::getNewlineOutput() const
{
#ifdef _WIN32
	return Newline_CrLf;
#else
	return Newline_Lf;
#endif
}
//--------------------------------------------------------------------------------------------------
size_t Config::getMaxArity() const
{
	return 10;
}
//--------------------------------------------------------------------------------------------------
size_t Config::getMaxPackNumber() const
{
	return 0;
}

}	//namespace Vatee
