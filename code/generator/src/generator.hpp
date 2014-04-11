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

	//! Top-level function to generate entire pack.
	/*!
		\param packName
			Suffix used as pack name in identifiers and file names.
	*/
	void generatePack(size_t idxPack, const std::string &packName);

	//! Top-level function to generate internal expansion header.
	void generateExpansion();

	//! Generates public header file of the pack.
	void generatePackPublic(size_t idxPack, const std::string &packName);

	//! Generates internal header file of the pack.
	void generatePackInternal(size_t idxPack, const std::string &packName);

	//! Writes legal info comment file header.
	void writeFileHeader();

	//! Writes macro-based include guard.
	void writeIncludeGuard(std::string headerName, std::string scope = std::string());

	//! Writes a #include directive.
	void writeInclude(HeaderType headerType, const std::string &headerName);

	//! Writes all VATEE_EXPAND_* macro definitions.
	void writeExpandMacros(const std::string &packName);

	//! Writes a particular variant of VATEE_EXPAND_* macros.
	void writeConfiguredExpandMacros(
		const std::string &packName
		, const std::string &namePrefix
		, const std::string &valuePrefix
		, const std::string &nameKind
		, bool after
	);

	void writeExpandMacro(
		const std::string &macroName
		, size_t components
		, const std::string &packName
		, const std::string &valuePrefix
		, bool after
	);

	void writeExpandMacroCore(
		size_t components
		, const std::string &packName
		, bool after
	);

	void writeMacro_Template(const std::string &packName);

	void writeMacro_Emulate(const std::string &packName);

	void writeIncludeGuardEnd();

	void writeEmulation(const std::string &packName);

	void writeOneEmulation(const std::string &packName, size_t packSize);

	void writeMacro_InternalExpandMacro();

	void writeInternalExpands();

	void writeOneInternalExpand(size_t arity, size_t components);

public:
	explicit Generator(Config config);

	void run();
};

}	//namespace Vatee
