# Copyright Petr Kmoch 2014.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 2.8.12)
project(vatee)

set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
	set(defInstallCmakeDir CMake)
else()
	set(defInstallCmakeDir lib/CMake/vatee)
endif()
set(INSTALL_CMAKE_DIR ${defInstallCmakeDir} CACHE PATH "Installation directory for CMake files")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for binaries")

enable_testing()
option(BUILD_TESTING "Generate tests" ON)

add_subdirectory(code)
