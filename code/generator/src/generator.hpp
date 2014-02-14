/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#pragma once


#include "config.hpp"

#include "io.hpp"


namespace Vatee {

class Generator
{
	Config config;
	FileWriter writer;

	enum HeaderType
	{
		Internal, Public
	};

	void generatePack(size_t idxPack, const std::string &packName);

	void generatePackPublic(size_t idxPack, const std::string &packName);

	void writeFileHeader();

	void writeIncludeGuard(std::string headerName);

	void writeInclude(HeaderType headerType, const std::string &headerName);

	void writeExpandMacros(const std::string &packName);

	void writeConfiguredExpandMacros(
		const std::string &packName
		, const std::string &namePrefix
		, const std::string &valuePrefix
		, const std::string &nameKind
		, bool after
	);

	void writeExpandMacro(
		const std::string &macroName
		, size_t arity
		, const std::string &packName
		, const std::string &valuePrefix
		, bool after
	);

	void writeExpandMacroCore(
		size_t arity
		, const std::string &packName
		, bool after
	);

	void writeMacro_Template(const std::string &packName);

	void writeMacro_Emulate(const std::string &packName);

	void writeIncludeGuardEnd();

public:
	explicit Generator(Config config);

	void run();
};

}	//namespace Vatee
