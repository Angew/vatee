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
	using namespace FileWriterControllers;
	std::ostringstream header;
	header << "pack" << packName << ".hpp";
	std::string headerName = header.str();
	writer.open(headerName);
	writeFileHeader();
	writeIncludeGuard(headerName);
	writeInclude(Internal, "compiler_version.hpp");
	writer << nl;
	writeInclude(Internal, "expansion.hpp");
	writeInclude(Internal, "facility.hpp");
	generateExpandMacros(packName);
	#error Continue here
}
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
