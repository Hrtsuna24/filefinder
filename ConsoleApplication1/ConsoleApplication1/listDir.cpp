#include "listDir.h"

void listDir(string path, FileMonitor& fileSink)
{
    for (directory_iterator dirIter(path);
        dirIter != directory_iterator(); ++dirIter)
    {
        if (std::filesystem::is_regular_file(dirIter->status()))
        {
            fileSink.push_back(dirIter->path().string());
        }
    }
}

void listDirs(vector<path> paths, FileMonitor& fileSink)
{
    vector<future<void>> futures;
    for (const path& pth : paths)
    {
        cout << pth << '\n';

        futures.emplace_back(async(listDir, pth.string(), ref(fileSink)));
    }

    //barier
    for (future<void>& fut : futures)
    {
        fut.wait();
    }
}

//vector<string> listDir(path const& dir)
//{
//    vector<string> files;
//    
//    for (directory_iterator dirIter;
//        dirIter != directory_iterator(); ++dirIter)
//    {
//        if (std::filesystem::is_regular_file(dirIter->status()))
//        {
//            files.push_back(dirIter->path().string());
//        }
//    }
//
//    return files;
//}
//
//vector<string> listDirs(vector<path> const& paths)
//{
//    vector<future<vector<string>>> futures;
//    for (const path& pth : paths)
//    {
//        cout << pth << '\n';
//
//        futures.emplace_back(async(listDir, ref(pth)));
//    }
//
//    vector<string> allFiles;
//    for(future<vector<string>>& fut : futures)
//    {
//        vector<string> files = fut.get();
//        std::move(files.begin(), files.end(), std::back_inserter(allFiles));
//    }
//
//    return allFiles;
//}
