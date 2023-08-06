#include "listDir.h"






void main()
{
	vector<path> paths;
	FileMonitor directory_to_visit;

	for (directory_iterator it("D:\\"); it != directory_iterator(); ++it)
	{
		if (std::filesystem::is_directory(it->status()))
		{
			paths.push_back(it->path());
			directory_to_visit.push_back(it->path().string());
		}
	}
	get_files(directory_to_visit, "TV_a.FBX");
}