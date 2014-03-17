/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#pragma once


#include "config.hpp"

#include "os.hpp"


namespace Vatee {

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//
// Class FileWriter
//
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
class FileWriter
{
	std::ofstream file;
	Os::String directory;
	std::string oneIndent, currentIndent, newline;

public:
	struct Controller;

	explicit FileWriter(const Config &config);

	void open(const Os::String &fileName, const Os::String &subDirectory = Os::String());

	void close();

	template <class T_Arg>
	void write(const T_Arg &arg)
	{
		file << arg;
	}

	void writeIndent();

	void writeNewline();

	void increaseIndent();

	void decreaseIndent();

	void writeMacroLineEnd();
};

template <>
void FileWriter::write(const Controller &controller);


namespace FileWriterControllers {

extern const FileWriter::Controller indent, nl, tab, untab, mle;

}	//namespace FileWriterControllers


template <class T_Arg>
FileWriter& operator<< (FileWriter &writer, const T_Arg &arg)
{
	writer.write(arg);
	return writer;
}

}	//namespace Vatee
