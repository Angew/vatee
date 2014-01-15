/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include "common.hpp"

#include "io.hpp"


namespace Vatee {

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//
// Class TextParser
//
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
class TextParser
{
public:
	virtual ~TextParser() {}

	static std::unique_ptr<TextParser> create(Config::NewlineStyle newlineStyle);

	bool getLine(std::string &line, std::string &newline);
};
//--------------------------------------------------------------------------------------------------
// Class FixedNewlineParser
//--------------------------------------------------------------------------------------------------
class FixedNewlineParser : public TextParser
{
	std::string newline;
public:
	explicit FixedNewlineParser(std::string newline) : newline(newline) {}
};
//--------------------------------------------------------------------------------------------------
// Class AnyNewlineParser
//--------------------------------------------------------------------------------------------------
class AnyNewlineParser : public TextParser
{
};
//--------------------------------------------------------------------------------------------------
// Construction
//--------------------------------------------------------------------------------------------------
/*static*/ std::unique_ptr<TextParser> TextParser::create(Config::NewlineStyle newlineStyle)
{
	switch (newlineStyle)
	{
		case Config::Newline_Any:
			return std::unique_ptr<TextParser>(new AnyNewlineParser());
		case Config::Newline_Cr:
			return std::unique_ptr<TextParser>(new FixedNewlineParser("\r"));
		case Config::Newline_Lf:
			return std::unique_ptr<TextParser>(new FixedNewlineParser("\n"));
		case Config::Newline_CrLf:
			return std::unique_ptr<TextParser>(new FixedNewlineParser("\r\n"));
		default:
			throw std::invalid_argument("Bad value of Vatee::Config::NewlineStyle");
	}
}



//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//
// Class FileText
//
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
// Construction
//--------------------------------------------------------------------------------------------------
FileText::FileText(Config::NewlineStyle newlineInput, Config::NewlineStyle newlineOutput)
	:	parser(TextParser::create(newlineInput))
	, convertNewline([=]() -> std::function<std::string (const std::string&)> {
		static const std::string cr("\r");
		static const std::string lf("\n");
		static const std::string crlf("\r\n");
		switch (newlineOutput)
		{
			case Config::Newline_Any:
				return [](const std::string &nl) { return nl; };
			case Config::Newline_Cr:
				return [&](const std::string &) { return cr; };
			case Config::Newline_Lf:
				return [&](const std::string &) { return lf; };
			case Config::Newline_CrLf:
				return [&](const std::string &) { return crlf; };
			default:
				throw std::invalid_argument("Bad value of Vatee::Config::NewlineStyle");
		}
	}())
{}

}	//namespace Vatee
