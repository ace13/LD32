#include "Path.hpp"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <direct.h>
#else

#endif

void Util::setSaneCWD()
{
	char buffer[MAX_PATH];
#ifdef _WIN32
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string path = buffer;
	size_t loc = path.find_last_of('\\');
	if (loc != std::string::npos)
		path.erase(loc, path.size() - loc);
	_chdir(path.c_str());
#endif
}


#ifdef _WIN32
std::string Util::getAbsolutePath(const std::string& path)
{
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