/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#pragma once


#include "config.hpp"


namespace Vatee {

class TextParser;

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//
// Class FileText
//
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
class FileText
{
	std::unique_ptr<TextParser> parser;
	std::function<std::string (const std::string&)> convertNewline;

public:
	FileText(Config::NewlineStyle newlineInput, Config::NewlineStyle newlineOutput);

	void openInFile(const std::string &fileName);

	void openOutFile(const std::string &fileName);

	void closeInFile();

	void closeOutFile();

	bool getLine(std::string &line);

	void putLine(std::string line);
};

}	//namespace Vatee
