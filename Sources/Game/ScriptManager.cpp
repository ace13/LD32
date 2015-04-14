#include "ScriptManager.hpp"
#include "ScriptExtensions.hpp"

#include <scripthelper/scripthelper.h>

using namespace Game;

namespace
{
	int include(const char *include, const char *from, CScriptBuilder *builder, void *userParam)
	{
		return 0;
	}

	void MessageCallback(const asSMessageInfo *msg, void *param)
	{
		const char *type = "ERR ";
		if (msg->type == asMSGTYPE_WARNING)
			type = "WARN";
		else if (msg->type == asMSGTYPE_INFORMATION)
			type = "INFO";
		printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
	}
}

ScriptManager* sSingleton = nullptr;

ScriptManager& ScriptManager::Singleton()
{
	if (sSingleton == nullptr)
		sSingleton = new ScriptManager();

	return *sSingleton;
}
ScriptManager::ScriptManager() :
	mEngine(asCreateScriptEngine(ANGELSCRIPT_VERSION)),
	mWatcher("Scripts")
{
	mEngine->SetMessageCallback(asFUNCTION(MessageCallback), nullptr, asCALL_CDECL);

	addGeneralScriptExtensions(mEngine);
	AS_SFML::addSFMLExtensions(mEngine);

	mBuilder.SetIncludeCallback(include, nullptr);
}
ScriptManager::~ScriptManager()
{

}

bool ScriptManager::loadScriptFromFile(const std::string& file)
{
	return false;
}
bool ScriptManager::loadScriptFromMemory(const std::string& file, const char* data, size_t size)
{
	mBuilder.StartNewModule(mEngine, "::memory::");

	mBuilder.AddSectionFromMemory(file.c_str(), data, size);
	int r = mBuilder.BuildModule();

	return false;
}

void ScriptManager::defineWord(const std::string& word)
{
	mBuilder.DefineWord(word.c_str());
}
void ScriptManager::checkForUpdates()
{
	std::string file;
	while (mWatcher.pollChange(file))
	{
		
	}
}