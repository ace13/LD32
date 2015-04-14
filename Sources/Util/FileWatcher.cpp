#include "FileWatcher.hpp"

#ifdef _WIN32
#include <SFML/System/String.hpp>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cstring>
#elif defined __linux__
#include <unistd.h>
#include <sys/select.h>
#include <sys/inotify.h>
#endif

#include <algorithm>

using namespace Util;

namespace
{
#ifdef _WIN32
	const char separator = '\\';
#elif __linux__
	const char separator = '/';
#endif

#ifdef __linux__
	struct WatcherFind
	{
		int Handle;

		bool operator()(const WatcherData& b) { return Handle == b.Handle; }
};
#endif
}

struct FileWatcher::WatcherData
{
	std::string Folder;
#ifdef _WIN32
	HANDLE DirectoryHandle;
	OVERLAPPED Overlapped;
	char Buffer[1024];
#elif defined __linux__
	int Handle;
#else
#pragma message("No file change checking on OS X, sorry.")
#endif
};

FileWatcher::FileWatcher(const std::string& folder, bool recursive):
	mFolder(folder), mRecursive(recursive)
#ifdef __linux__
	,mInotify(inotify_init())
#endif
{
	startWatch();
}
FileWatcher::FileWatcher(FileWatcher&& move) :
	mFolder(std::move(move.mFolder)), mRecursive(std::move(move.mRecursive)),
	mWatches(std::move(move.mWatches)), mChanges(std::move(move.mChanges)),
	mLastCheck(std::move(move.mLastCheck))
#ifdef __linux__
	, mInotify(std::move(move.mInotify))
#endif
{
#ifdef __linux__
	move.mInotify = 0; // TODO Is this necessary?
#endif
}

FileWatcher::~FileWatcher()
{
	stopWatch();
#ifdef __linux__
	close(mInotify);
#endif
}

bool FileWatcher::pollChange(std::string& file)
{
	if (ClockImpl::now() - mLastCheck > std::chrono::seconds(1))
		tick();

	if (mChanges.empty())
		return false;

	file = mChanges.front();
	mChanges.pop_front();
	return true;
}

std::string FileWatcher::folderName() const
{
	return mFolder;
}

void FileWatcher::tick()
{
	mLastCheck = ClockImpl::now();

#ifdef _WIN32
	for (auto watch : mWatches)
	{
		DWORD bytes = 0;
		GetOverlappedResult(watch->DirectoryHandle, &watch->Overlapped, &bytes, FALSE);
		ResetEvent(watch->Overlapped.hEvent);

		if (bytes > 0)
		{
			int offset = 0;
			while (true)
			{
				FILE_NOTIFY_INFORMATION* pNotify = (FILE_NOTIFY_INFORMATION*)&watch->Buffer[offset];
				offset += pNotify->NextEntryOffset;

				if (pNotify->FileNameLength > 0)
				{
					std::string path;
					if (mFolder != watch->Folder)
						path = watch->Folder.substr(mFolder.size() + 1) + '\\';
					
					sf::String filePath(std::wstring(pNotify->FileName, pNotify->FileNameLength));
					path += filePath;

					if (std::find(mChanges.cbegin(), mChanges.cend(), path) == mChanges.cend())
						mChanges.push_back(path);
				}

				if (pNotify->NextEntryOffset == 0)
					break;
			}

			CancelIo(watch->DirectoryHandle);
			std::memset(watch->Buffer, 0, sizeof(watch->Buffer));
			ReadDirectoryChangesW(watch->DirectoryHandle, &watch->Buffer, sizeof(watch->Buffer), mRecursive, FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_LAST_WRITE, NULL, &watch->Overlapped, NULL);
		}
	}
#elif defined __linux__
	timeval tv;
	tv.tv_sec = tv.tv_usec = 0;

	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(mInotify, &fds);

	select(mInotify + 1, &fds, NULL, NULL, &tv);

	if (FD_ISSET(mInotify, &fds))
	{
		char buffer[1024];

		int i = 0, ret = read(mInotify, buffer, 1024);

		if (ret < 0)
		{
			return;
		}

		while (i < ret)
		{
			inotify_event* ev = (inotify_event*)&buffer[i];
			WatcherFind find = { .Handle = ev->wd };
			auto it = std::find_if(mWatches.cbegin(), mWatches.cend(), find);

			if (ev->len > 0 && it != mWatches.cend())
			{
				std::string path = it->directory + '/' + ev->name;
				if (std::find(mChanges.cbegin(), mChanges.cend(), path) == mChanges.cend())
					mChanges.push_back(path);
			}

			i += sizeof(inotify_event) + ev->len;
		}
	}
#endif
}

void FileWatcher::startWatch()
{
	WatcherData* data = new WatcherData;
	
	data->Folder = mFolder;
#ifdef _WIN32
	data->DirectoryHandle = CreateFileA(mFolder.c_str(), FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL);

	std::memset(&data->Overlapped, 0, sizeof(data->Overlapped));
	data->Overlapped.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	std::memset(data->Buffer, 0, sizeof(data->Buffer));
#elif defined __linux__
	int flags = IN_ATTRIB | IN_CREATE | IN_DELETE | IN_MODIFY | IN_MOVED_FROM | IN_MOVED_TO;
	data->handle = inotify_add_watch(mInotify, mFolder.c_str(), flags);
#endif

	mWatches.push_back(data);

	if (mRecursive)
	{
		// TODO
	}

#ifdef _WIN32
	for (auto watch : mWatches)
		ReadDirectoryChangesW(watch->DirectoryHandle, &watch->Buffer, sizeof(watch->Buffer), mRecursive, FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_LAST_WRITE, NULL, &watch->Overlapped, NULL);
#endif

	tick();
}

void FileWatcher::stopWatch()
{
	for (auto watch : mWatches)
	{
#ifdef _WIN32
		CloseHandle(watch->DirectoryHandle);
		watch->DirectoryHandle = nullptr;
#elif defined __linux__
		inotify_rm_watch(mInotify, watch->Handle);
#endif

		delete watch;
	}

	mWatches.clear();
}