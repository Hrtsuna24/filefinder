#include "listDir.h"
#include <array>
//void listDir(string path, FileMonitor& fileSink)
//{
//    for (directory_iterator dirIter(path);
//        dirIter != directory_iterator(); ++dirIter)
//    {
//        if (std::filesystem::is_regular_file(dirIter->status()))
//        {
//            fileSink.push_back(dirIter->path().string());
//        }
//    }
//}
//
//void listDirs(vector<path> paths, FileMonitor& fileSink)
//{
//    vector<future<void>> futures;
//    for (const path& pth : paths)
//    {
//        cout << pth << '\n';
//
//        futures.emplace_back(async(listDir, pth.string(), ref(fileSink)));
//    }
//
//    //barier
//    for (future<void>& fut : futures)
//    {
//        fut.wait();
//    }
//}


void get_files(FileMonitor& directory_to_visit, const string& target)
{
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
						//cout << fe.what() << std::endl;
						//directory_to_visit.pop_back();
						continue;
					}
					//directory_to_visit.pop_back();
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
							if (is_directory(file))
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