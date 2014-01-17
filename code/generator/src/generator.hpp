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

public:
	explicit Generator(Config config);

	void run();
};

}	//namespace Vatee
