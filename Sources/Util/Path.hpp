#pragma once

#include <list>
#include <string>

namespace Util
{

	extern void setSaneCWD();
	extern std::string getAbsolutePath(const std::string& path);
	extern std::list<std::string> getFilesInDir(const std::string& path);

}