/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include "common.hpp"

#include "generator.hpp"


namespace Vatee {

void Generator::generatePack(size_t idxPack, const std::string &packName)
{
	generatePackPublic(idxPack, packName);
	generatePackInternal(idxPack, packName);
}
//--------------------------------------------------------------------------------------------------
void Generator::generatePackPublic(size_t idxPack, const std::string &packName)
{
	using namespace FileWriterControllers;
	std::ostringstream header;
	header << "pack";
	if (!packName.empty()) {
		header << idxPack;
	}
	header << ".hpp";
	std::string headerName = header.str();
	writer.open(headerName);
	writeFileHeader();
	writeIncludeGuard(headerName);
	writeInclude(Internal, "compiler_version.hpp");
	writer << nl;
	writeInclude(Internal, "expansion.hpp");
	writeInclude(Internal, "facility.hpp");
	writer << nl << nl;
	writeExpandMacros(packName);
	writeMacro_Template(packName);
	writer << nl;
	writeMacro_Emulate(packName);
	writeIncludeGuardEnd();
}
//--------------------------------------------------------------------------------------------------
void Generator::generatePackInternal(size_t idxPack, const std::string &packName)
{
	using namespace FileWriterControllers;
	std::ostringstream header;
	header << "emulate";
	if (!packName.empty()) {
		header << idxPack;
	}
	header << ".hpp";
	std::string headerName = header.str();
	writer.open(headerName, "internal");
	writeFileHeader();
	writeIncludeGuard(headerName, "INTERNAL");

	writeIncludeGuardEnd();
}
//--------------------------------------------------------------------------------------------------
void Generator::writeFileHeader()
{
	using namespace FileWriterControllers;
	writer
		<< "/*" << nl
		<< "Copyright Petr Kmoch 2014." << nl
		<< "Distributed under the Boost Software License, Version 1.0." << nl
		<< "(See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)" << nl
		<< "*/" << nl
		<< nl
	;
}
//--------------------------------------------------------------------------------------------------
void Generator::writeIncludeGuard(std::string headerName, std::string scope)
{
	using namespace FileWriterControllers;
	size_t idxPeriod = headerName.find('.');
	assert(headerName.find_last_of('.') == idxPeriod);
	if (idxPeriod != headerName.npos) {
		headerName.erase(idxPeriod);
	}
	assert(!headerName.empty());
	const std::ctype<char> &ctype = std::use_facet<std::ctype<char>>(std::locale::classic());
	ctype.toupper(&headerName[0], &headerName[0] + headerName.size());
	if (!scope.empty())
		scope.append("_");
	writer
		<< "#ifndef VATEE_GUARD_" << scope << headerName << nl
		<< "#define VATEE_GUARD_" << scope << headerName << nl
		<< nl
	;
}
//--------------------------------------------------------------------------------------------------
void Generator::writeInclude(HeaderType headerType, const std::string &headerName)
{
	using namespace FileWriterControllers;
	writer << "#include \"vatee/";
	if (headerType == Internal) {
		writer << "internal/";
	}
	writer << headerName << '"' << nl;
}
//--------------------------------------------------------------------------------------------------
void Generator::writeExpandMacros(const std::string &packName)
{
	writeConfiguredExpandMacros(
		packName
		, std::string(), std::string()
		, "AFTER", true
	);
	writeConfiguredExpandMacros(
		packName
		, "TRAILING_", "VATEE_NONEMPTY" + packName + "_COMMA"
		, "AFTER", true
	);
	writeConfiguredExpandMacros(
		packName
		, std::string(), std::string()
		, "BETWEEN", false
	);
	writeConfiguredExpandMacros(
		packName
		, "TRAILING_", "VATEE_NONEMPTY" + packName + "_COMMA"
		, "BETWEEN", false
	);
}
//--------------------------------------------------------------------------------------------------
void Generator::writeConfiguredExpandMacros(
	const std::string &packName
	, const std::string &namePrefix
	, const std::string &valuePrefix
	, const std::string &nameKind
	, const bool after
)
{
	using namespace FileWriterControllers;
	std::ostringstream macroNameGen;
	macroNameGen << "VATEE_" << namePrefix << "EXPAND" << packName << '_' << nameKind;
	std::string macroName = macroNameGen.str();
	for (size_t arity = (after ? 1 : 2); arity <= config.getMaxArity(); ++arity) {
		writeExpandMacro(macroName, arity, packName, valuePrefix, after);
		writer << nl;
	}
}
//--------------------------------------------------------------------------------------------------
void Generator::writeExpandMacro(
	const std::string &macroName
	, const size_t arity
	, const std::string &packName
	, const std::string &valuePrefix
	, const bool after
)
{
	using namespace FileWriterControllers;
	writer << "#define " << macroName << '_' << arity << "(vatee_arg0";
	for (size_t arg = 1; arg < arity; ++arg) {
		writer << ", vatee_arg" << arg;
	}
	writer << ')' << mle << tab;
	writer << indent << valuePrefix;
	writeExpandMacroCore(arity, packName, after);
	writer << nl << untab;
}
//--------------------------------------------------------------------------------------------------
void Generator::writeExpandMacroCore(
	const size_t arity
	, const std::string &packName
	, const bool after
)
{
	writer << "VATEE_INTERNAL_EXPAND_MACRO(VATEE_PACKSIZE" << packName
		<< ", " << arity + (after ? 1 : 0) << ") (vatee_arg0"
	;
	for (size_t arg = 1; arg < arity; ++arg) {
		writer << ", vatee_arg" << arg;
	}
	if (after) {
		writer << ',';
	}
	writer << " VATEE_INTERNAL_EMPTY)";
}
//--------------------------------------------------------------------------------------------------
void Generator::writeMacro_Template(const std::string &packName)
{
	using namespace FileWriterControllers;
	writer
		<< "#define VATEE_TEMPLATE" << packName << "(vatee_arg0)" << mle << tab
		<< indent << "VATEE_IF_NONEMPTY" << packName << "(template <) "
	;
	writeExpandMacroCore(1, packName, true);
	writer << " VATEE_IF_NONEMPTY" << packName << "(>)" << nl << untab;
}
//--------------------------------------------------------------------------------------------------
void Generator::writeMacro_Emulate(const std::string &packName)
{
	using namespace FileWriterControllers;
	writer
		<< "#define VATEE_EMULATE" << packName
		<< "() \"vatee/internal/emulate" << packName << ".hpp\""
		<< nl
	;
}
//--------------------------------------------------------------------------------------------------
void Generator::writeIncludeGuardEnd()
{
	using namespace FileWriterControllers;
	writer << nl << "#endif" << nl;
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//
// Public
//
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
Generator::Generator(Config config)
	: config(config)
	, writer(this->config)
{}
//--------------------------------------------------------------------------------------------------
void Generator::run()
{
	for (size_t idxPack = 0, idxMax = config.getMaxPackNumber(); idxPack <= idxMax; ++idxPack) {
		std::ostringstream s;
		s << '_' << idxPack;
		generatePack(idxPack, s.str());
	}
}

}	//namespace Vatee
