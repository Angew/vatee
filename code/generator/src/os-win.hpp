/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#pragma once


#include "os.hpp"


namespace Vatee {

namespace Os {

const String rawPathPrefix(L"\\\\?\\");
const String rawPathUncInfix(L"UNC\\");
const String rawPathUncPrefix(rawPathPrefix + rawPathUncInfix);

const size_t maxPathLength = 32768u;

}	//namespace Os

}	//namespace Vatee
