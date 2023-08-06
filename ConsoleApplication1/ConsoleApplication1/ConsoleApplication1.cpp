#include "listDir.h"


void main()
{
	vector<path> paths;

	for (directory_iterator it("C:\\"); it != directory_iterator(); ++it)
	{
		if (std::filesystem::is_directory(it->status()))
		{
			paths.push_back(it->path());
		}
	}

	FileMonitor fileSink;
	listDirs(paths, fileSink);
	fileSink.print();
}