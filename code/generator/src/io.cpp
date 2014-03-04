/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include "common.hpp"

#include "io.hpp"


namespace Vatee {

namespace {

std::string computeIndentString(size_t spaceCount)
{
	if (spaceCount == 0) {
		return "\t";
	} else {
		return std::string(spaceCount, ' ');
	}
}


std::string computeNewlineString(Config::NewlineStyle style)
{
	switch (style) {
		case Config::Newline_Lf:
			return "\n";
		case Config::Newline_Cr:
			return "\r";
		case Config::Newline_CrLf:
			return "\r\n";
		NO_DEFAULT()
	}
}

}	//namespace


struct FileWriter::Controller
{
	void (FileWriter::*operation)();

	Controller(void (FileWriter::*operation)()) : operation(operation) {}
};


namespace FileWriterControllers {

const FileWriter::Controller
	indent(&FileWriter::writeIndent)
	, nl(&FileWriter::writeNewline)
	, tab(&FileWriter::increaseIndent)
	, untab(&FileWriter::decreaseIndent)
	, mle(&FileWriter::writeMacroLineEnd)
;

}	//namespace FileWriterControllers


FileWriter::FileWriter(const Config &config)
	: directory(config.getDestDir() + "/")
	, oneIndent(computeIndentString(config.getIndentSpaceCount()))
	, newline(computeNewlineString(config.getNewlineStyle()))
{}
//--------------------------------------------------------------------------------------------------
void FileWriter::open(const std::string &fileName, const std::string &subDirectory)
{
	std::ostringstream pathConstructor;
	pathConstructor << directory;
	if (!subDirectory.empty())
		pathConstructor << subDirectory << '/';
	pathConstructor << fileName;
	std::string fullPath = pathConstructor.str();
	file.open(fullPath.c_str(), std::ios::binary);
	if (!file)
		throw std::ios_base::failure("Error opening " + fullPath);
}
//--------------------------------------------------------------------------------------------------
void FileWriter::close()
{
	file.close();
}
//--------------------------------------------------------------------------------------------------
template <>
void FileWriter::write(const Controller &controller)
{
	(this->*(controller.operation))();
}
//--------------------------------------------------------------------------------------------------
void FileWriter::writeIndent()
{
	file << currentIndent;
}
//--------------------------------------------------------------------------------------------------
void FileWriter::writeNewline()
{
	file << newline;
}
//--------------------------------------------------------------------------------------------------
void FileWriter::increaseIndent()
{
	currentIndent += oneIndent;
}
//--------------------------------------------------------------------------------------------------
void FileWriter::decreaseIndent()
{
	assert(currentIndent.size() >= oneIndent.size());
	currentIndent.erase(currentIndent.end() - oneIndent.size(), currentIndent.end());
}
//--------------------------------------------------------------------------------------------------
void FileWriter::writeMacroLineEnd()
{
	file << " \\" << newline;
}

}	//namespace Vatee
