/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#pragma once


namespace Vatee {

class Config
{
public:
	enum NewlineStyle
	{
		Newline_Unspecified
		, Newline_Lf
		, Newline_Cr
		, Newline_CrLf
	};

	std::string getDestDir() const;

	NewlineStyle getNewlineStyle() const;

	size_t getMaxExpandComponents() const;

	size_t getMaxArity() const;

	size_t getMaxPackNumber() const;

	size_t getIndentSpaceCount() const;
};

}	//namespace Vatee
