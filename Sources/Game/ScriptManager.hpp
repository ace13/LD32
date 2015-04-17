#pragma once

#include <Util/FileWatcher.hpp>
#include <Util/Time.hpp>
#include <angelscript.h>
#include <scriptbuilder/scriptbuilder.h>

#include <list>
#include <set>
#include <string>
#include <unordered_map>

namespace Kunlaboro { class EntitySystem; }

namespace Game
{
	class ScriptObject;

	class ScriptManager
	{
	public:
		static ScriptManager& Singleton();
		ScriptManager(const ScriptManager&) = delete;
		~ScriptManager();

		ScriptManager& operator=(const ScriptManager&) = delete;

		bool loadScriptFromFile(const std::string& file);
		bool loadScriptFromMemory(const std::string& file, const char* data, size_t size);

		void defineWord(const std::string& word);
		void checkForUpdates();

		ScriptObject* createObject(const std::string& file, const std::string& name, Kunlaboro::EntitySystem& es);

	private:
		struct ScriptFileData
		{
			ScriptFileData();

			std::set<std::string> IncludedFrom;
			Util::Timestamp Timestamp;
			bool DirectlyLoaded;
		};

		ScriptManager();

		void notifyIncluded(const std::string& file, const std::string& from);

		void notifyNewObject(ScriptObject* obj);
		void notifyObjectRemoved(ScriptObject* obj);

		asIScriptEngine* mEngine;
		CScriptBuilder mBuilder;
		Util::FileWatcher mWatcher;
		std::list<ScriptObject*> mObjects;
		std::unordered_map<std::string, ScriptFileData> mLoadedScripts;

		friend class ScriptObject;
	};

}
