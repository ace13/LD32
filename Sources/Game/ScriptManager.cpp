#include "ScriptManager.hpp"
#include "ScriptExtensions.hpp"
#include "ScriptObject.hpp"
#include "../Util/Path.hpp"

#include <scripthelper/scripthelper.h>
#include <serializer/serializer.h>

#include <algorithm>
#include <fstream>
#include <vector>

#ifdef _WIN32
#include <direct.h>
#else
#include <limits.h>
#include <cstdlib>
#endif

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

	class BytecodeStore : public asIBinaryStream
	{
	public:
		BytecodeStore() : mTellg(0) { }

		void Read(void *ptr, asUINT size)
		{
			char* data = (char*)ptr;
			std::memcpy(data, &mStore[0] + mTellg, size);
			mTellg += size;
		}
		void Write(const void *ptr, asUINT size)
		{
			const char* data = (const char*)ptr;

			for (uint32_t i = 0; i < size; ++i)
				mStore.push_back(data[i]);
		}

	private:
		std::vector<char> mStore;
		size_t mTellg;
	};

	std::string normalizePath(const std::string& unnormalized)
	{
		std::string path = unnormalized;

#ifdef _WIN32
		std::replace(path.begin(), path.end(), '/', '\\');
#endif

		return Util::getAbsolutePath(path);
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
	std::ifstream ifs(file.c_str());
	if (!ifs)
		return false;

	ifs.seekg(0, std::ios::end);
	size_t len = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	std::vector<char> data(len, 0);
	ifs.read(&data[0], len);

	if (!ifs.bad())
		return loadScriptFromMemory(file, &data[0], strlen(&data[0]));

	return false;
}
bool ScriptManager::loadScriptFromMemory(const std::string& path, const char* data, size_t size)
{
	std::string file = normalizePath(path);

	bool reload = mLoadedScripts[file].DirectlyLoaded;
	mLoadedScripts[file].Timestamp = Util::ClockImpl::now();

	if (reload)
	{
		auto oldMod = mEngine->GetModule(file.c_str());

		CSerializer serial;
		addGeneralSerializerTypes(&serial);
		AS_SFML::addSFMLSerializers(&serial);

		for (auto& obj : mObjects)
		{
			auto asObj = obj->getObject();

			if (asObj->GetObjectType()->GetModule() == oldMod)
				serial.AddExtraObjectToStore(asObj);
		}

		mBuilder.StartNewModule(mEngine, "::memory::");
		mBuilder.AddSectionFromMemory(file.c_str(), data, size);
		int r = mBuilder.BuildModule();
		if (r < 0)
			return false;

		BytecodeStore store;
		auto mod = mBuilder.GetModule();

		mod->SaveByteCode(&store);

		serial.Store(oldMod);

		oldMod->Discard();

		mod = mEngine->GetModule(file.c_str(), asGM_ALWAYS_CREATE);
		mod->LoadByteCode(&store);

		serial.Restore(mod);
		for (auto& obj : mObjects)
		{
			auto asObj = obj->getObject();

			if (asObj->GetObjectType()->GetModule() == oldMod)
				obj->setObject((asIScriptObject*)serial.GetPointerToRestoredObject(asObj));
		}

		mEngine->GarbageCollect(asGC_FULL_CYCLE | asGC_DESTROY_GARBAGE);
	}
	else
	{
		mBuilder.StartNewModule(mEngine, file.c_str());
		mBuilder.AddSectionFromMemory(file.c_str(), data, size);

		int r = mBuilder.BuildModule();
		if (r < 0)
			return false;

		mLoadedScripts[file].DirectlyLoaded = true;
	}

	return true;
}

void ScriptManager::defineWord(const std::string& word)
{
	mBuilder.DefineWord(word.c_str());
}
void ScriptManager::checkForUpdates()
{
	std::list<std::string> checked;
	static std::function<void(const std::string& file)> recursiveLoader = [&](const std::string& file)
	{
		if (std::find(checked.cbegin(), checked.cend(), file) != checked.end())
			return;

		checked.push_back(file);
		auto& loaded = mLoadedScripts[file];

		for (auto& includee : loaded.IncludedFrom)
			recursiveLoader(includee);

		if (loaded.DirectlyLoaded)
			loadScriptFromFile(file);
	};

	std::string file;
	while (mWatcher.pollChange(file))
	{
		file = normalizePath(file);

		if (mLoadedScripts.count(file) == 0)
			continue;

		recursiveLoader(file);
	}
}

ScriptObject* ScriptManager::createObject(const std::string& file, const std::string& name, Kunlaboro::EntitySystem& es)
{
	std::string path = normalizePath(file);
	if (mLoadedScripts.count(path) == 0)
		if (!loadScriptFromFile(path))
			return nullptr;

	auto obj = static_cast<Game::ScriptObject*>(es.createComponent("Game.ScriptObject"));

	auto mod = mEngine->GetModule(path.c_str());
	auto type = mod->GetObjectTypeByName(name.c_str());

	if (type)
		obj->setObject((asIScriptObject*)mEngine->CreateScriptObject(type));

	return obj;
}

asIScriptEngine* ScriptManager::getEngine()
{
	return mEngine;
}

void ScriptManager::notifyNewObject(ScriptObject* obj)
{
	mObjects.push_back(obj);
}

void ScriptManager::notifyObjectRemoved(ScriptObject* obj)
{
	auto it = std::find(mObjects.begin(), mObjects.end(), obj);
	if (it != mObjects.end())
		mObjects.erase(it);
}


ScriptManager::ScriptFileData::ScriptFileData() : Timestamp(Util::ClockImpl::now()), DirectlyLoaded(false)
{

}
