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

add_subdirectory(code)
