/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include "common.hpp"

#include "filesystem.hpp"
#include "os-win.hpp"

#include <Windows.h>

#include <cwchar>


namespace Vatee {

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//
// Helpers
//
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
Os::String getFullPath(Os::String path)
{
	std::replace(path.begin(), path.end(), L'/', L'\\');
	{
		Os::Char *buffer = _wfullpath(NULL, path.c_str(), Os::maxPathLength);
		if (!buffer) {
			return Os::String();
		}
		try {
			path = buffer;
		} catch (...) {
			free(buffer);
			throw;
		}
		free(buffer);
	}
	return path;
}


//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//
// Directory operations
//
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
bool makeDirectory(Os::String directory)
{
	directory = getFullPath(directory);
	if (directory.empty()) {
		return false;
	}
	assert(directory.size() >= 2);
	size_t idxSep;
	const Os::String *prefix;
	if (directory[1] == L':') {
		prefix = &Os::rawPathPrefix;
		idxSep = directory.find(L'\\', 3);
	} else {
		assert(directory[0] == L'\\' && directory[1] == L'\\');
		prefix = &Os::rawPathUncPrefix;
		idxSep = directory.find(L'\\', 2);
		if (idxSep == directory.npos) {
			return false;
		}
		idxSep = directory.find(L'\\', idxSep + 1);
	}
	directory = *prefix + directory;
	idxSep += prefix->size();
	std::vector<size_t> separators;
	while (idxSep != directory.npos) {
		separators.push_back(idxSep);
		idxSep = directory.find(L'\\', idxSep + 1);
	}
	if (separators.back() == directory.size() - 1) {
		separators.pop_back();
	}
	size_t retries = 0;
	const size_t maxRetries = 5;
	for (std::vector<size_t>::const_iterator itSep = separators.begin(); itSep != separators.end();) {
		directory[*itSep] = 0;
		bool ok = !!CreateDirectoryW(directory.c_str(), NULL);
		if (!ok) {
			switch (GetLastError()) {
				case ERROR_ALREADY_EXISTS:
					ok = true;
					break;
				case ERROR_PATH_NOT_FOUND:
					if (++retries > maxRetries) {
						return false;
					}
					assert(itSep != separators.begin());
					--itSep;
					break;
				default:
					return false;
			}
		}
		if (ok) {
			directory[*itSep++] = L'\\';
		}
	}
	return true;
}

}	// namespace Vatee