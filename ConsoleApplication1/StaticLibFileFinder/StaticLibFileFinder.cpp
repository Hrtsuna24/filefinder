// StaticLibFileFinder.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "fnStaticLibFileFinder.h"
#include "FileMonitor.h"
#include <filesystem>
#include <array>
// TODO: This is an example of a library function

using std::filesystem::path;
using std::filesystem::directory_iterator;
using std::future;
using std::cout;
using std::async;
using std::ref;

void fnStaticLibFileFinder(const std::string& serachingIn, const std::string& target)
{
	FileMonitor directory_to_visit;

	for (directory_iterator it(serachingIn); it != directory_iterator(); ++it)
	{
		if (std::filesystem::is_directory(it->status()))
		{
			directory_to_visit.push_back(it->path().string());
		}

	}
	std::array<future<void>, 8> futures;
	bool serching = true;
	for (int i = 0; i < 8; i++)
	{
		futures[i] = async([&directory_to_visit, &target, &serching]() -> void
			{
				while (!directory_to_visit.isEmpty() && serching)
				{
					directory_iterator currentDirr;
					std::string str;
					try
					{
						str = directory_to_visit.back();
						currentDirr = directory_iterator(str);

					}
					catch (const std::filesystem::filesystem_error& fe)
					{
						continue;
					}
					std::for_each(
						std::filesystem::begin(currentDirr),
						std::filesystem::end(currentDirr),
						[&directory_to_visit, &target, &serching](const std::filesystem::directory_entry& file) -> void//
						{
							//find target file
							if (file.path().filename().string().compare(target) == 0)
							{
								directory_to_visit.print(file.path().string());
								//directory_to_visit.clear();
								serching = false;
								return;
							}
							if (std::filesystem::is_directory(file))
							{
								directory_to_visit.push_front(file.path().string());
							}
						});
				}
			});
	}

	//barier
	for (future<void>& fut : futures)
	{
		fut.wait();
	}
}
