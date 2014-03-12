/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include "common.hpp"

#include "filesystem.hpp"

#include <Windows.h>

#include <wchar.h>


namespace Vatee {

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//
// Directory operations
//
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
bool makeDirectory(OsString directory)
{
	std::replace(directory.begin(), directory.end(), L'/', L'\\');
	{
		wchar_t *buffer = _wfullpath(NULL, directory.c_str(), 32767);
		try {
			directory = buffer;
		} catch (...) {
			free(buffer);
			throw;
		}
		free(buffer);
	}
	size_t idxSep;
	assert(directory.size() >= 2);
	if (directory[1] == L':') {
		idxSep = directory.find(L'\\', 3);
	} else {
		assert(directory[0] == L'\\' && directory[1] == L'\\');
		idxSep = directory.find(L'\\', 2);
		if (idxSep == directory.npos) {
			return false;
		}
		idxSep = directory.find(L'\\', idxSep + 1);
	}
	if (idxSep == directory.npos)
		return false;
	directory = L"\\\\?\\" + directory;
	idxSep += 4;
	do {
		directory[idxSep] = 0;
		bool ok = !!CreateDirectoryW(directory.c_str(), NULL);
		if (!ok) {
			
		}
	} while(idxSep != directory.npos);
}

}	// namespace Vatee