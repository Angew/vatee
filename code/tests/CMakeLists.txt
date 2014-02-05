# Copyright Petr Kmoch 2014.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file ../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

add_executable(test_basic0_stable basic0.cpp)
target_include_directories(test_basic0_stable PUBLIC ${PROJECT_SOURCE_DIR}/code/include)

add_test(
	NAME Basic0-Stable
	COMMAND test_basic0_stable
)
set_property(
	TEST Basic0-Stable
	PROPERTY LABELS Stable Pack0
)
