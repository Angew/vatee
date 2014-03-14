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
// Helpers
//
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
std::wstring getFullPath(std::wstring path)
{
	std::replace(path.begin(), path.end(), L'/', L'\\');
	const size_t maxPathLength = 32767;
	{
		wchar_t *buffer = _wfullpath(NULL, path.c_str(), maxPathLength);
		if (!buffer) {
			return std::wstring();
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
bool makeDirectory(OsString directory)
{
	directory = getFullPath(directory);
	if (directory.empty()) {
		return false;
	}
	assert(directory.size() >= 2);
	size_t idxSep;
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
	const std::wstring utfPrefix(L"\\\\?\\");
	directory = utfPrefix + directory;
	idxSep += utfPrefix.size();
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