/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include "common.hpp"

#include "generator.hpp"


namespace Vatee {

namespace dirInternal {

const auto osName = Os::String(OS_LIT("internal"));
const auto name = std::string("internal");
const auto scope = std::string("INTERNAL");

}	//namespace dirInternal


void Generator::generatePack(size_t idxPack, const std::string &packName)
{
	generatePackPublic(idxPack, packName);
	generatePackInternal(idxPack, packName);
}
//--------------------------------------------------------------------------------------------------
void Generator::generateExpansion()
{
	using namespace FileWriterControllers;
	auto headerName = std::string("expansion.hpp");
	writer.open(Os::convert7BitAscii(headerName), dirInternal::osName);
	writeFileHeader();
	writeIncludeGuard(headerName, dirInternal::scope);
	writeMacro_InternalExpandMacro();
	writer << nl;
	writeInternalExpands();
	writeIncludeGuardEnd();
	writer.close();
}
//--------------------------------------------------------------------------------------------------
void Generator::generatePackPublic(size_t idxPack, const std::string &packName)
{
	using namespace FileWriterControllers;
	std::stringstream header;
	header << "pack";
	if (!packName.empty()) {
		header << idxPack;
	}
	header << ".hpp";
	auto headerName = header.str();
	writer.open(Os::convert7BitAscii(headerName));
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
	writer.close();
}
//--------------------------------------------------------------------------------------------------
void Generator::generatePackInternal(size_t /*idxPack*/, const std::string &packName)
{
	using namespace FileWriterControllers;
	std::ostringstream header;
	header << "emulate" << packName << ".hpp";
	auto headerName = header.str();
	writer.open(Os::convert7BitAscii(headerName), dirInternal::osName);
	writeFileHeader();
	writeEmulation(packName);
	writer.close();
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
	const auto &ctype = std::use_facet<std::ctype<char>>(std::locale::classic());
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
		writer << dirInternal::name << '/';
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
		, "TRAILING_", "VATEE_NONEMPTY" + packName + "_COMMA "
		, "AFTER", true
	);
	writeConfiguredExpandMacros(
		packName
		, std::string(), std::string()
		, "BETWEEN", false
	);
	writeConfiguredExpandMacros(
		packName
		, "TRAILING_", "VATEE_NONEMPTY" + packName + "_COMMA "
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
	auto macroName = macroNameGen.str();
	for (size_t components = (after ? 1 : 2); components <= config.getMaxExpandComponents(); ++components) {
		writeExpandMacro(macroName, components, packName, valuePrefix, after);
		writer << nl;
	}
}
//--------------------------------------------------------------------------------------------------
void Generator::writeExpandMacro(
	const std::string &macroName
	, const size_t components
	, const std::string &packName
	, const std::string &valuePrefix
	, const bool after
)
{
	using namespace FileWriterControllers;
	writer << "#define " << macroName << '_' << components << "(vatee_arg0";
	for (size_t arg = 1; arg < components; ++arg) {
		writer << ", vatee_arg" << arg;
	}
	writer << ')' << mle << tab;
	writer << indent << valuePrefix;
	writeExpandMacroCore(components, packName, after);
	writer << nl << untab;
}
//--------------------------------------------------------------------------------------------------
void Generator::writeExpandMacroCore(
	const size_t components
	, const std::string &packName
	, const bool after
)
{
	writer << "VATEE_INTERNAL_EXPAND_MACRO(VATEE_PACKSIZE" << packName
		<< ", " << components + (after ? 1 : 0) << ") (vatee_arg0"
	;
	for (size_t arg = 1; arg < components; ++arg) {
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
		<< "() \"vatee/" << dirInternal::name << "/emulate" << packName << ".hpp\""
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
void Generator::writeEmulation(const std::string &packName)
{
	using namespace FileWriterControllers;
	for (size_t packSize = 0; packSize <= config.getMaxArity(); ++packSize) {
		writeOneEmulation(packName, packSize);
	}
	writer << "#undef VATEE_EMULATION" << nl;
}
//--------------------------------------------------------------------------------------------------
void Generator::writeOneEmulation(const std::string &packName, size_t packSize)
{
	using namespace FileWriterControllers;
	writer << "// Size " << packSize << nl << nl;
	writer << "#define VATEE_IF_NONEMPTY" << packName << "(...)";
	if (packSize > 0) {
		writer << " __VA_ARGS__";
	}
	writer << nl;
	writer << "#define VATEE_NONEMPTY" << packName << "_COMMA";
	if (packSize > 0) {
		writer << " ,";
	}
	writer << nl;
	writer << "#define VATEE_PACKSIZE" << packName << ' ' << packSize << nl;
	writer << nl << "VATEE_EMULATION" << nl << nl;
	writer
		<< "#undef VATEE_IF_NONEMPTY" << packName << nl
		<< "#undef VATEE_NONEMPTY" << packName << "_COMMA" << nl
		<< "#undef VATEE_PACKSIZE" << packName << nl
		<< nl
	;
}
//--------------------------------------------------------------------------------------------------
void Generator::writeMacro_InternalExpandMacro()
{
	using namespace FileWriterControllers;
	writer
		<< "#define VATEE_INTERNAL_EXPAND_MACRO(vatee_packsize, vatee_args)" << mle << tab
		<< indent << "VATEE_INTERNAL_EXPAND_MACRO_I(vatee_packsize, vatee_args)" << nl << untab
	;
	writer << nl;
	writer
		<< "#define VATEE_INTERNAL_EXPAND_MACRO_I(vatee_packsize, vatee_args)" << mle << tab
		<< indent << "VATEE_INTERNAL_EXPAND_ ## vatee_packsize ## _ ## vatee_args" << nl << untab
	;
	writer << nl;
}
//--------------------------------------------------------------------------------------------------
void Generator::writeInternalExpands()
{
	for (size_t arity = 0; arity <= config.getMaxArity(); ++arity) {
		for (size_t components = 2; components <= config.getMaxExpandComponents(); ++components) {
			writeOneInternalExpand(arity, components);
		}
	}
}
//--------------------------------------------------------------------------------------------------
void Generator::writeOneInternalExpand(const size_t arity, const size_t components)
{
	using namespace FileWriterControllers;
	writer << "#define VATEE_INTERNAL_EXPAND_" << arity << '_' << components << "(vatee_arg0";
	for (size_t i = 1; i < components; ++i) {
		writer << ", vatee_arg" << i;
	}
	writer << ')' << tab;
	{
		bool first = true;
		for (size_t idxArg = 0; idxArg < arity; ++idxArg) {
			writer << mle << indent;
			if (first) {
				first = false;
			} else {
				writer << ", ";
			}
			for (size_t idxComp = 0; idxComp < components - 1; ++idxComp) {
				writer << "vatee_arg" << idxComp << " ## " << idxArg << " ";
			}
			writer << "vatee_arg" << components - 1 << "()";
		}
	}
	writer << nl << untab << nl;
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
	generateExpansion();
}

}	//namespace Vatee
