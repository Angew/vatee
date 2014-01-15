/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include "common.hpp"

#include "config.hpp"
#include "generator.hpp"


int main(int /*argc*/, char * /*argv_p*/[])
{
	Vatee::Config config;
	Vatee::Generator generator(config);
	generator.run();
}
