/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include "common.hpp"

#include "generator.hpp"


namespace Vatee {

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
