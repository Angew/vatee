# Copyright Petr Kmoch 2014.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file ../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

add_subdirectory(generator)

if(BUILD_TESTING)
	add_subdirectory(tests)
endif()
