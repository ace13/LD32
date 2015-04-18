#pragma once

#include "Time.hpp"
#include <list>
#include <string>

namespace Util
{

	class FileWatcher
	{
	public:
		FileWatcher(const std::string& folder, bool recursive = true);
		FileWatcher(FileWatcher&& move);
		FileWatcher(const FileWatcher& copy) = delete;
		~FileWatcher();

		FileWatcher& operator=(const FileWatcher& copy) = delete;

		bool pollChange(std::string& file);

		std::string folderName() const;

	private:
		void tick();
		void startWatch();
		void stopWatch();

		struct WatcherData;

		std::string mFolder;
		bool mRecursive;
		std::list<WatcherData*> mWatches;
		std::list<std::string> mChanges;
		Timestamp mLastCheck;
		
#ifdef __linux__
		int mInotify;
        struct WatcherFind;
#endif
	};

}
