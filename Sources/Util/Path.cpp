#include "Path.hpp"

#ifdef _WIN32
#include <algorithm>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <direct.h>
#elif __linux__
#include <dirent.h>
#include <climits>
#include <cstdlib>
#include <cstring>
// Very beautiful.
#define MAX_PATH 4096
#else
#error "This no work on OS X :("
#endif

void Util::setSaneCWD()
{
#ifdef _WIN32
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string path = buffer;
	size_t loc = path.find_last_of('\\');
	if (loc != std::string::npos)
		path.erase(loc, path.size() - loc);
	_chdir(path.c_str());
#else

#endif
}


#ifdef _WIN32
std::string Util::getAbsolutePath(const std::string& inp)
{
	std::string path = inp;

#ifdef _WIN32
	std::replace(path.begin(), path.end(), '/', '\\');
#endif

	char temp[_MAX_PATH];
	return (_fullpath(temp, path.c_str(), _MAX_PATH) ? std::string(temp) : std::string());
}
#else
std::string Util::getAbsolutePath(const std::string& path)
{
	char temp[PATH_MAX];
	return (realpath(path.c_str(), temp) ? std::string(temp) : std::string());
}
#endif

std::list<std::string> Util::getFilesInDir(const std::string& relative)
{
	std::string path = getAbsolutePath(relative);
	std::list<std::string> ret;

#ifdef _WIN32
	WIN32_FIND_DATA findData;
	HANDLE findHandle = FindFirstFile((path + "\\*").c_str(), &findData); 
	if (findHandle == INVALID_HANDLE_VALUE)
		return ret;

	do
	{
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;

		ret.push_back(relative + "/" + findData.cFileName);
	} while (FindNextFile(findHandle, &findData) != 0);

	FindClose(findHandle);
#else
	DIR *pDIR;
	struct dirent *entry;
	if (!(pDIR = opendir(path.c_str())))
		return ret;

	while (entry = readdir(pDIR))
	{
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;

		ret.push_back(relative + "/" + entry->d_name);
	}

	closedir(pDIR);
#endif

	return ret;
}
