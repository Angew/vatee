/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#pragma once


#include <cassert>
#include <cstddef>
#include <fstream>
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>


using std::size_t;


#define NO_DEFAULT() default: assert(!"Invalid switch argument"); throw std::logic_error("NO_DEFAULT() failure");
