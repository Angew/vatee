# Copyright Petr Kmoch 2014.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file ../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

# find_package(Boost REQUIRED)

# include_directories(${Boost_INCLUDE_DIRS})

if(MSVC)
	add_compile_options(/Yucommon.hpp /W4 /WX /wd4355)
	add_definitions(-DVATEE_GENERATOR_DEFAULT_DEST_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\")
	set_property(SOURCE src/common.cpp APPEND_STRING PROPERTY COMPILE_FLAGS " /Yccommon.hpp")
endif()

if(WIN32)
	set(OsSuffix -win)
	add_definitions(-DOS_WIN -D_UNICODE -DNOMINMAX -D_SCL_SECURE_NO_WARNINGS)
else()
	set(OsSuffix -posix)
	add_definitions(-DOS_POSIX)
endif()

add_executable(generate_vatee
	src/common.hpp
	src/common.cpp
	src/config.hpp
	src/config.cpp
	src/filesystem.hpp
	src/filesystem${OsSuffix}.cpp
	src/generator.hpp
	src/generator.cpp
	src/io.hpp
	src/io.cpp
	src/main.cpp
	src/os.hpp
	src/os${OsSuffix}.hpp
	src/os${OsSuffix}.cpp
)
